/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

#include <string.h>
#include "cfe.h"
#include "cs_app.h"

#include "cs_platform_cfg.h"
#include "cs_eventids.h"
#include "cs_utils.h"
#include "cs_compute.h"
#include "cs_eeprom_cmds.h"
#include "cs_table_cmds.h"
#include "cs_memory_cmds.h"
#include "cs_app_cmds.h"
#include "cs_cmds.h"
#include "cs_init.h"
#include "cs_table_processing.h"

#include "hammer.h"
#include "glue.h"
#include "static_alloc.h"

#define CRC_INPUT_SIZE     192

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CS Software Bus Setup                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CFE_Status_t CS_SbInit(void)
{
    CFE_Status_t Result = CFE_SUCCESS;

    /* Initialize housekeeping packet */
    CFE_MSG_Init(CFE_MSG_PTR(CS_AppData.HkPacket.TelemetryHeader),
                 CFE_SB_ValueToMsgId(CS_HK_TLM_MID),
                 sizeof(CS_HkPacket_t));

    /* Create Software Bus message pipe */
    Result = CFE_SB_CreatePipe(&CS_AppData.CmdPipe, CS_PIPE_DEPTH, CS_CMD_PIPE_NAME);
    if (Result != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CS_CR_PIPE_ERR_EID,
                          CFE_EVS_EventType_ERROR,
                          "Software Bus Create Pipe for command returned: 0x%08X",
                          (unsigned int)Result);
    }
    else
    {
        /* Subscribe to Housekeeping request commands */
        Result = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(CS_SEND_HK_MID), CS_AppData.CmdPipe);

        if (Result != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(CS_INIT_SB_SUBSCRIBE_HK_ERR_EID,
                              CFE_EVS_EventType_ERROR,
                              "Software Bus subscribe to housekeeping returned: 0x%08X",
                              (unsigned int)Result);
        }
        else
        {
            /* Subscribe to background checking schedule */
            Result = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(CS_BACKGROUND_CYCLE_MID), CS_AppData.CmdPipe);

            if (Result != CFE_SUCCESS)
            {
                CFE_EVS_SendEvent(CS_INIT_SB_SUBSCRIBE_BACK_ERR_EID,
                                  CFE_EVS_EventType_ERROR,
                                  "Software Bus subscribe to background cycle returned: 0x%08X",
                                  (unsigned int)Result);
            }
        }

        if (Result == CFE_SUCCESS)
        {
            /* Subscribe to CS Internal command packets */
            Result = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(CS_CMD_MID), CS_AppData.CmdPipe);
            if (Result != CFE_SUCCESS)
            {
                CFE_EVS_SendEvent(CS_INIT_SB_SUBSCRIBE_CMD_ERR_EID,
                                  CFE_EVS_EventType_ERROR,
                                  "Software Bus subscribe to command returned: 0x%08X",
                                  (unsigned int)Result);
            }
        }
    }
    return Result;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CS Table Initialization                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CFE_Status_t CS_InitAllTables(void)
{
    static const CS_TableWrapper_t TABLE_INITIALIZERS[CS_NUM_TABLES] = {
        [CS_ChecksumType_CFECORE] =
            {
                .BaselineValue = &CS_AppData.HkPacket.Payload.CfeCoreBaseline,
                .ResEntrySize  = sizeof(CS_Res_EepromMemory_Table_Entry_t),
                .ResAddr       = &CS_AppData.CfeCoreCodeSeg,
                .NumEntries    = 1,
            },
        [CS_ChecksumType_OSCORE] =
            {
                .BaselineValue = &CS_AppData.HkPacket.Payload.OSBaseline,
                .ResEntrySize  = sizeof(CS_Res_EepromMemory_Table_Entry_t),
                .ResAddr       = &CS_AppData.OSCodeSeg,
                .NumEntries    = 1,
            },
        [CS_ChecksumType_EEPROM_TABLE] =
            {
                .DefTableName         = CS_DEF_EEPROM_TABLE_NAME,
                .ResTableName         = CS_RESULTS_EEPROM_TABLE_NAME,
                .GlobalState          = &CS_AppData.HkPacket.Payload.EepromCSState,
                .NumEntries           = CS_MAX_NUM_EEPROM_TABLE_ENTRIES,
                .DefEntrySize         = sizeof(CS_Def_EepromMemory_Table_Entry_t),
                .ResEntrySize         = sizeof(CS_Res_EepromMemory_Table_Entry_t),
                .DefStateOffset       = offsetof(CS_Def_EepromMemory_Table_Entry_t, State),
                .UpdateHandler        = CS_ProcessNewEepromMemoryDefinitionTable,
                .DefaultDefinitionPtr = CS_AppData.DefaultEepromDefTable,
            },
        [CS_ChecksumType_MEMORY_TABLE] =
            {
                .DefTableName         = CS_DEF_MEMORY_TABLE_NAME,
                .ResTableName         = CS_RESULTS_MEMORY_TABLE_NAME,
                .GlobalState          = &CS_AppData.HkPacket.Payload.MemoryCSState,
                .NumEntries           = CS_MAX_NUM_MEMORY_TABLE_ENTRIES,
                .DefEntrySize         = sizeof(CS_Def_EepromMemory_Table_Entry_t),
                .ResEntrySize         = sizeof(CS_Res_EepromMemory_Table_Entry_t),
                .DefStateOffset       = offsetof(CS_Def_EepromMemory_Table_Entry_t, State),
                .UpdateHandler        = CS_ProcessNewEepromMemoryDefinitionTable,
                .DefaultDefinitionPtr = CS_AppData.DefaultMemoryDefTable,
            },
        [CS_ChecksumType_TABLES_TABLE] =
            {
                .DefTableName         = CS_DEF_TABLES_TABLE_NAME,
                .ResTableName         = CS_RESULTS_TABLES_TABLE_NAME,
                .GlobalState          = &CS_AppData.HkPacket.Payload.TablesCSState,
                .NumEntries           = CS_MAX_NUM_TABLES_TABLE_ENTRIES,
                .DefEntrySize         = sizeof(CS_Def_Tables_Table_Entry_t),
                .ResEntrySize         = sizeof(CS_Res_Tables_Table_Entry_t),
                .DefStateOffset       = offsetof(CS_Def_Tables_Table_Entry_t, State),
                .UpdateHandler        = CS_ProcessNewTablesDefinitionTable,
                .DefaultDefinitionPtr = CS_AppData.DefaultTablesDefTable,
            },
        [CS_ChecksumType_APP_TABLE] = {
            .DefTableName         = CS_DEF_APP_TABLE_NAME,
            .ResTableName         = CS_RESULTS_APP_TABLE_NAME,
            .GlobalState          = &CS_AppData.HkPacket.Payload.AppCSState,
            .NumEntries           = CS_MAX_NUM_APP_TABLE_ENTRIES,
            .DefEntrySize         = sizeof(CS_Def_App_Table_Entry_t),
            .ResEntrySize         = sizeof(CS_Res_App_Table_Entry_t),
            .DefStateOffset       = offsetof(CS_Def_App_Table_Entry_t, State),
            .UpdateHandler        = CS_ProcessNewAppDefinitionTable,
            .DefaultDefinitionPtr = CS_AppData.DefaultAppDefTable,
        }};

    static const char *const TABLE_FILENAME_MAP[CS_NUM_TABLES] = {
        [CS_ChecksumType_EEPROM_TABLE] = CS_DEF_EEPROM_TABLE_FILENAME,
        [CS_ChecksumType_MEMORY_TABLE] = CS_DEF_MEMORY_TABLE_FILENAME,
        [CS_ChecksumType_TABLES_TABLE] = CS_DEF_TABLES_TABLE_FILENAME,
        [CS_ChecksumType_APP_TABLE]    = CS_DEF_APP_TABLE_FILENAME
    };

    static const CFE_TBL_CallbackFuncPtr_t TABLE_CALLBACK_MAP[CS_NUM_TABLES] = {
        [CS_ChecksumType_EEPROM_TABLE] = CS_ValidateEepromChecksumDefinitionTable,
        [CS_ChecksumType_MEMORY_TABLE] = CS_ValidateMemoryChecksumDefinitionTable,
        [CS_ChecksumType_TABLES_TABLE] = CS_ValidateTablesChecksumDefinitionTable,
        [CS_ChecksumType_APP_TABLE]    = CS_ValidateAppChecksumDefinitionTable
    };

    static const uint16 TABLE_EVENTID_MAP[CS_NUM_TABLES] = { [CS_ChecksumType_EEPROM_TABLE] = CS_INIT_EEPROM_ERR_EID,
                                                             [CS_ChecksumType_MEMORY_TABLE] = CS_INIT_MEMORY_ERR_EID,
                                                             [CS_ChecksumType_TABLES_TABLE] = CS_INIT_TABLES_ERR_EID,
                                                             [CS_ChecksumType_APP_TABLE]    = CS_INIT_APP_ERR_EID };

    CFE_Status_t              ResultAll;
    CFE_Status_t              Result;
    const char               *LoadFilename;
    CFE_TBL_CallbackFuncPtr_t ValidationFunc;
    CS_TableWrapper_t        *tw;
    CS_ChecksumType_Enum_t    TableId;
    uint16                    ErrorEventID;

    ResultAll = CFE_SUCCESS;
    tw        = CS_AppData.Tbl;

    for (TableId = 0; TableId < CS_NUM_TABLES; ++TableId)
    {
        *tw            = TABLE_INITIALIZERS[TableId];
        LoadFilename   = TABLE_FILENAME_MAP[TableId];
        ValidationFunc = TABLE_CALLBACK_MAP[TableId];
        ErrorEventID   = TABLE_EVENTID_MAP[TableId];

        /* If this table needs to be loaded via table services, do that now */
        Result = CS_TableInit(tw, LoadFilename, ValidationFunc);
        if (Result != CFE_SUCCESS)
        {
            /* If the init did not work then make sure the global status is set to disabled */
            if (tw->GlobalState)
            {
                *tw->GlobalState = CS_ChecksumState_DISABLED;
            }

            if (ErrorEventID != 0)
            {
                CFE_EVS_SendEvent(ErrorEventID,
                                  CFE_EVS_EventType_ERROR,
                                  "Table initialization failed for %s: 0x%08X",
                                  CS_GetTableTypeAsString(tw),
                                  (unsigned int)Result);
            }

            ResultAll = Result;
        }

        ++tw;
    }

    return ResultAll;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CS Segment Initialization                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CS_InitSegments(void)
{
    int32   ResultSegment = OS_SUCCESS;
    uint32  CFESize;
    cpuaddr CFEAddress;
    uint32  KernelSize;
    cpuaddr KernelAddress;

    CS_Res_EepromMemory_Table_Entry_t *CodeSeg;

    /* Initalize the CFE core segments */
    ResultSegment = CFE_PSP_GetCFETextSegmentInfo(&CFEAddress, &CFESize);
    CodeSeg       = CS_GetCfeCoreCodeSegResTable();

    if (ResultSegment != OS_SUCCESS)
    {
        CodeSeg->StartAddress       = 0;
        CodeSeg->NumBytesToChecksum = 0;
        CodeSeg->ComputedYet        = false;
        CodeSeg->ComparisonValue    = 0;
        CodeSeg->ByteOffset         = 0;
        CodeSeg->TempChecksumValue  = 0;
        CodeSeg->State              = CS_ChecksumState_DISABLED;

        CFE_EVS_SendEvent(CS_CFE_TEXT_SEG_INF_EID, CFE_EVS_EventType_INFORMATION, "CFE Text Segment disabled");
    }
    else
    {
        CodeSeg->StartAddress       = CFEAddress;
        CodeSeg->NumBytesToChecksum = CFESize;
        CodeSeg->ComputedYet        = false;
        CodeSeg->ComparisonValue    = 0;
        CodeSeg->ByteOffset         = 0;
        CodeSeg->TempChecksumValue  = 0;
        CodeSeg->State              = CS_ChecksumState_ENABLED;
    }

    /* Initialize the OS Core code segment*/

    ResultSegment = CFE_PSP_GetKernelTextSegmentInfo(&KernelAddress, &KernelSize);
    CodeSeg       = CS_GetOSCodeSegResTable();

    if (ResultSegment != OS_SUCCESS)
    {
        CodeSeg->StartAddress       = 0;
        CodeSeg->NumBytesToChecksum = 0;
        CodeSeg->ComputedYet        = false;
        CodeSeg->ComparisonValue    = 0;
        CodeSeg->ByteOffset         = 0;
        CodeSeg->TempChecksumValue  = 0;
        CodeSeg->State              = CS_ChecksumState_DISABLED;

        CFE_EVS_SendEvent(CS_OS_TEXT_SEG_INF_EID,
                          CFE_EVS_EventType_INFORMATION,
                          "OS Text Segment disabled due to platform");
    }
    else
    {
        CodeSeg->StartAddress       = KernelAddress;
        CodeSeg->NumBytesToChecksum = KernelSize;
        CodeSeg->ComputedYet        = false;
        CodeSeg->ComparisonValue    = 0;
        CodeSeg->ByteOffset         = 0;
        CodeSeg->TempChecksumValue  = 0;
        CodeSeg->State              = CS_ChecksumState_ENABLED;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CS Parser Initialization                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**************************************************************************
 **
 ** Functions
 **
 **************************************************************************/
/*----------------------------------------------------------------
 *
 * Local crc-16 function(s)
 * TODO:  Put them in a separate cFS library?
 *
 *-----------------------------------------------------------------*/
uint32 CS_ComputeCRC_Algo_16_ARC(const void *DataPtr, size_t DataLength, uint32 InputCRC)
{
    size_t       i;
    uint16       Index;
    uint16       Crc;
    const uint8 *BufPtr;

    static const uint16 CrcTable[256] = {

        0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241, 0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1,
        0xC481, 0x0440, 0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40, 0x0A00, 0xCAC1, 0xCB81, 0x0B40,
        0xC901, 0x09C0, 0x0880, 0xC841, 0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40, 0x1E00, 0xDEC1,
        0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41, 0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
        0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040, 0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1,
        0xF281, 0x3240, 0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441, 0x3C00, 0xFCC1, 0xFD81, 0x3D40,
        0xFF01, 0x3FC0, 0x3E80, 0xFE41, 0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840, 0x2800, 0xE8C1,
        0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41, 0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
        0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640, 0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0,
        0x2080, 0xE041, 0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240, 0x6600, 0xA6C1, 0xA781, 0x6740,
        0xA501, 0x65C0, 0x6480, 0xA441, 0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41, 0xAA01, 0x6AC0,
        0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840, 0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
        0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40, 0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1,
        0xB681, 0x7640, 0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041, 0x5000, 0x90C1, 0x9181, 0x5140,
        0x9301, 0x53C0, 0x5280, 0x9241, 0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440, 0x9C01, 0x5CC0,
        0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40, 0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
        0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40, 0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0,
        0x4C80, 0x8C41, 0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641, 0x8201, 0x42C0, 0x4380, 0x8341,
        0x4100, 0x81C1, 0x8081, 0x4040

    };

    i      = DataLength;
    BufPtr = (const uint8 *)DataPtr;
    Crc    = InputCRC;

    while (i > 0)
    {
        /*
         * It is assumed that the supplied buffer is in a
         * directly-accessible memory space that does not
         * require special logic to access
         */
        Index = *BufPtr;
        Index = ((Crc ^ Index) & 0x00FF);
        Crc   = ((Crc >> 8) & 0x00FF) ^ CrcTable[Index];

        --i;
        ++BufPtr;
    }

    return Crc;
}

HParsedToken* act_crc_buffer(const HParseResult *p, void *user_data){

    uint32_t *crc = (uint32_t *)user_data;

    *crc = CS_ComputeCRC_Algo_16_ARC(
        p->ast->token_data.bytes.token,
        p->ast->token_data.bytes.len,
        *crc);

    return NULL;

}

void CS_InitParsers(void)
{
    h_static_alloc_init();
    h_default_allocator = h_grammar_allocator;
    h_default_parse_allocator = h_parse_allocator;

    H_ADRULE(crc_buffer, h_bytes(CRC_INPUT_SIZE),
            &CS_AppData.crc_final_value);

    CS_AppData.parser = h_sequence(crc_buffer, h_end_p(), NULL);


}