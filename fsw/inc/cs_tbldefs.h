/************************************************************************
 * NASA Docket No. GSC-18,915-1, and identified as “cFS Checksum
 * Application version 2.5.1”
 *
 * Copyright (c) 2021 United States Government as represented by the
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

/**
 * @file
 *   Specification for the CFS Checksum tables.
 */
#ifndef CS_TBLDEFS_H
#define CS_TBLDEFS_H

/**************************************************************************
 **
 ** Include section
 **
 **************************************************************************/
#include <cfe.h>

/**************************************************************************
 **
 ** Macro definitions
 **
 **************************************************************************/

/**
 * \brief table names for definition tables
 * \{
 */
#define CS_DEF_EEPROM_TABLE_NAME "DefEepromTbl"
#define CS_DEF_MEMORY_TABLE_NAME "DefMemoryTbl"
#define CS_DEF_TABLES_TABLE_NAME "DefTablesTbl"
#define CS_DEF_APP_TABLE_NAME    "DefAppTbl"
/**\}*/

/**
 * \brief names for the results tables
 * \{
 */
#define CS_RESULTS_EEPROM_TABLE_NAME "ResEepromTbl"
#define CS_RESULTS_MEMORY_TABLE_NAME "ResMemoryTbl"
#define CS_RESULTS_TABLES_TABLE_NAME "ResTablesTbl"
#define CS_RESULTS_APP_TABLE_NAME    "ResAppTbl"
/**\}*/

/**************************************************************************
 **
 ** Type definitions
 **
 **************************************************************************/

/**
 * \brief Data structure for the EEPROM or Memory definition table
 */
typedef struct
{
    cpuaddr StartAddress;       /**< \brief The Start address to Checksum */
    uint16  State;              /**< \brief Uses the CS_STATE_... defines from above */
    uint16  Filler16;           /** <\brief Padding */
    uint32  NumBytesToChecksum; /**< \brief The number of Bytes to Checksum */
} CS_Def_EepromMemory_Table_Entry_t;

/**
 * \brief Data structure for the Eeporom or Memory results table
 */
typedef struct
{
    cpuaddr StartAddress;       /**< \brief The Start address to Checksum */
    uint16  State;              /**< \brief Uses the CS_STATE_... defines from above */
    uint16  ComputedYet;        /**< \brief Have we computed an Integrity value yet */
    uint32  NumBytesToChecksum; /**< \brief The number of Bytes to Checksum */
    uint32  ComparisonValue;    /**< \brief The Memory Integrity Value */
    uint32  ByteOffset;         /**< \brief Where a previous unfinished calc left off */
    uint32  TempChecksumValue;  /**< \brief The unfinished caluculation */
    uint32  Filler32;           /**< \brief Padding */
} CS_Res_EepromMemory_Table_Entry_t;

/**
 * \brief Data structure for the Tables definition table
 */
typedef struct
{
    uint16 State;                           /**< \brief Uses the CS_STATE_... defines from above */
    char   Name[CFE_TBL_MAX_FULL_NAME_LEN]; /**< \brief name of the table */
} CS_Def_Tables_Table_Entry_t;

/**
 * \brief Data structure for the App definition table
 */
typedef struct
{
    uint16 State;                 /**< \brief Uses the CS_STATE_... defines from above */
    char   Name[OS_MAX_API_NAME]; /**< \brief name of the app */
} CS_Def_App_Table_Entry_t;

/**
 * \brief Data structure for the Tables result table
 */
typedef struct
{
    cpuaddr          StartAddress;                    /**< \brief The Start address to Checksum */
    uint16           State;                           /**< \brief Uses the CS_STATE_... defines from above */
    uint16           ComputedYet;                     /**< \brief Have we computed an Integrity value yet */
    uint32           NumBytesToChecksum;              /**< \brief The number of Bytes to Checksum */
    uint32           ComparisonValue;                 /**< \brief The Memory Integrity Value */
    uint32           ByteOffset;                      /**< \brief Where a previous unfinished calc left off */
    uint32           TempChecksumValue;               /**< \brief The unfinished caluculation */
    CFE_TBL_Handle_t TblHandle;                       /**< \brief handle recieved from CFE_TBL */
    bool             IsCSOwner;                       /**< \brief Is CS the original owner of this table */
    bool             Filler8;                         /**< \brief Padding */
    char             Name[CFE_TBL_MAX_FULL_NAME_LEN]; /**< \brief name of the table */
} CS_Res_Tables_Table_Entry_t;

/**
 * \brief Data structure for the app result table
 */
typedef struct
{
    cpuaddr StartAddress;          /**< \brief The Start address to Checksum */
    uint16  State;                 /**< \brief Uses the CS_STATE_... defines from above */
    uint16  ComputedYet;           /**< \brief Have we computed an Integrity value yet */
    uint32  NumBytesToChecksum;    /**< \brief The number of Bytes to Checksum */
    uint32  ComparisonValue;       /**< \brief The Memory Integrity Value */
    uint32  ByteOffset;            /**< \brief Where a previous unfinished calc left off */
    uint32  TempChecksumValue;     /**< \brief The unfinished caluculation */
    char    Name[OS_MAX_API_NAME]; /**< \brief name of the app */
} CS_Res_App_Table_Entry_t;

#endif
