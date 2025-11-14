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
 *
 * Auto-Generated stub implementations for functions defined in cs_table_processing header
 */

#include "cs_table_processing.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CS_HandleTableUpdate()
 * ----------------------------------------------------
 */
CFE_Status_t CS_HandleTableUpdate(void **DefinitionTblPtr, void **ResultsTblPtr, CFE_TBL_Handle_t DefinitionTableHandle,
                                  CFE_TBL_Handle_t ResultsTableHandle, uint16 Table, uint16 NumEntries)
{
    UT_GenStub_SetupReturnBuffer(CS_HandleTableUpdate, CFE_Status_t);

    UT_GenStub_AddParam(CS_HandleTableUpdate, void **, DefinitionTblPtr);
    UT_GenStub_AddParam(CS_HandleTableUpdate, void **, ResultsTblPtr);
    UT_GenStub_AddParam(CS_HandleTableUpdate, CFE_TBL_Handle_t, DefinitionTableHandle);
    UT_GenStub_AddParam(CS_HandleTableUpdate, CFE_TBL_Handle_t, ResultsTableHandle);
    UT_GenStub_AddParam(CS_HandleTableUpdate, uint16, Table);
    UT_GenStub_AddParam(CS_HandleTableUpdate, uint16, NumEntries);

    UT_GenStub_Execute(CS_HandleTableUpdate, Basic, NULL);

    return UT_GenStub_GetReturnValue(CS_HandleTableUpdate, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_ProcessNewAppDefinitionTable()
 * ----------------------------------------------------
 */
void CS_ProcessNewAppDefinitionTable(const CS_Def_App_Table_Entry_t *DefinitionTblPtr,
                                     CS_Res_App_Table_Entry_t *      ResultsTblPtr)
{
    UT_GenStub_AddParam(CS_ProcessNewAppDefinitionTable, const CS_Def_App_Table_Entry_t *, DefinitionTblPtr);
    UT_GenStub_AddParam(CS_ProcessNewAppDefinitionTable, CS_Res_App_Table_Entry_t *, ResultsTblPtr);

    UT_GenStub_Execute(CS_ProcessNewAppDefinitionTable, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_ProcessNewEepromMemoryDefinitionTable()
 * ----------------------------------------------------
 */
void CS_ProcessNewEepromMemoryDefinitionTable(const CS_Def_EepromMemory_Table_Entry_t *DefinitionTblPtr,
                                              CS_Res_EepromMemory_Table_Entry_t *ResultsTblPtr, uint16 NumEntries,
                                              uint16 Table)
{
    UT_GenStub_AddParam(CS_ProcessNewEepromMemoryDefinitionTable, const CS_Def_EepromMemory_Table_Entry_t *,
                        DefinitionTblPtr);
    UT_GenStub_AddParam(CS_ProcessNewEepromMemoryDefinitionTable, CS_Res_EepromMemory_Table_Entry_t *, ResultsTblPtr);
    UT_GenStub_AddParam(CS_ProcessNewEepromMemoryDefinitionTable, uint16, NumEntries);
    UT_GenStub_AddParam(CS_ProcessNewEepromMemoryDefinitionTable, uint16, Table);

    UT_GenStub_Execute(CS_ProcessNewEepromMemoryDefinitionTable, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_ProcessNewTablesDefinitionTable()
 * ----------------------------------------------------
 */
void CS_ProcessNewTablesDefinitionTable(const CS_Def_Tables_Table_Entry_t *DefinitionTblPtr,
                                        CS_Res_Tables_Table_Entry_t *      ResultsTblPtr)
{
    UT_GenStub_AddParam(CS_ProcessNewTablesDefinitionTable, const CS_Def_Tables_Table_Entry_t *, DefinitionTblPtr);
    UT_GenStub_AddParam(CS_ProcessNewTablesDefinitionTable, CS_Res_Tables_Table_Entry_t *, ResultsTblPtr);

    UT_GenStub_Execute(CS_ProcessNewTablesDefinitionTable, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_TableInit()
 * ----------------------------------------------------
 */
CFE_Status_t CS_TableInit(CFE_TBL_Handle_t *DefinitionTableHandle, CFE_TBL_Handle_t *ResultsTableHandle,
                          void **DefinitionTblPtr, void **ResultsTblPtr, uint16 Table, const char *DefinitionTableName,
                          const char *ResultsTableName, uint16 NumEntries, const char *DefinitionTableFileName,
                          const void *DefaultDefTableAddress, uint16 SizeofDefinitionTableEntry,
                          uint16 SizeofResultsTableEntry, CFE_TBL_CallbackFuncPtr_t CallBackFunction)
{
    UT_GenStub_SetupReturnBuffer(CS_TableInit, CFE_Status_t);

    UT_GenStub_AddParam(CS_TableInit, CFE_TBL_Handle_t *, DefinitionTableHandle);
    UT_GenStub_AddParam(CS_TableInit, CFE_TBL_Handle_t *, ResultsTableHandle);
    UT_GenStub_AddParam(CS_TableInit, void **, DefinitionTblPtr);
    UT_GenStub_AddParam(CS_TableInit, void **, ResultsTblPtr);
    UT_GenStub_AddParam(CS_TableInit, uint16, Table);
    UT_GenStub_AddParam(CS_TableInit, const char *, DefinitionTableName);
    UT_GenStub_AddParam(CS_TableInit, const char *, ResultsTableName);
    UT_GenStub_AddParam(CS_TableInit, uint16, NumEntries);
    UT_GenStub_AddParam(CS_TableInit, const char *, DefinitionTableFileName);
    UT_GenStub_AddParam(CS_TableInit, const void *, DefaultDefTableAddress);
    UT_GenStub_AddParam(CS_TableInit, uint16, SizeofDefinitionTableEntry);
    UT_GenStub_AddParam(CS_TableInit, uint16, SizeofResultsTableEntry);
    UT_GenStub_AddParam(CS_TableInit, CFE_TBL_CallbackFuncPtr_t, CallBackFunction);

    UT_GenStub_Execute(CS_TableInit, Basic, NULL);

    return UT_GenStub_GetReturnValue(CS_TableInit, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_ValidateAppChecksumDefinitionTable()
 * ----------------------------------------------------
 */
CFE_Status_t CS_ValidateAppChecksumDefinitionTable(void *TblPtr)
{
    UT_GenStub_SetupReturnBuffer(CS_ValidateAppChecksumDefinitionTable, CFE_Status_t);

    UT_GenStub_AddParam(CS_ValidateAppChecksumDefinitionTable, void *, TblPtr);

    UT_GenStub_Execute(CS_ValidateAppChecksumDefinitionTable, Basic, NULL);

    return UT_GenStub_GetReturnValue(CS_ValidateAppChecksumDefinitionTable, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_ValidateEepromChecksumDefinitionTable()
 * ----------------------------------------------------
 */
CFE_Status_t CS_ValidateEepromChecksumDefinitionTable(void *TblPtr)
{
    UT_GenStub_SetupReturnBuffer(CS_ValidateEepromChecksumDefinitionTable, CFE_Status_t);

    UT_GenStub_AddParam(CS_ValidateEepromChecksumDefinitionTable, void *, TblPtr);

    UT_GenStub_Execute(CS_ValidateEepromChecksumDefinitionTable, Basic, NULL);

    return UT_GenStub_GetReturnValue(CS_ValidateEepromChecksumDefinitionTable, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_ValidateMemoryChecksumDefinitionTable()
 * ----------------------------------------------------
 */
CFE_Status_t CS_ValidateMemoryChecksumDefinitionTable(void *TblPtr)
{
    UT_GenStub_SetupReturnBuffer(CS_ValidateMemoryChecksumDefinitionTable, CFE_Status_t);

    UT_GenStub_AddParam(CS_ValidateMemoryChecksumDefinitionTable, void *, TblPtr);

    UT_GenStub_Execute(CS_ValidateMemoryChecksumDefinitionTable, Basic, NULL);

    return UT_GenStub_GetReturnValue(CS_ValidateMemoryChecksumDefinitionTable, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_ValidateTablesChecksumDefinitionTable()
 * ----------------------------------------------------
 */
CFE_Status_t CS_ValidateTablesChecksumDefinitionTable(void *TblPtr)
{
    UT_GenStub_SetupReturnBuffer(CS_ValidateTablesChecksumDefinitionTable, CFE_Status_t);

    UT_GenStub_AddParam(CS_ValidateTablesChecksumDefinitionTable, void *, TblPtr);

    UT_GenStub_Execute(CS_ValidateTablesChecksumDefinitionTable, Basic, NULL);

    return UT_GenStub_GetReturnValue(CS_ValidateTablesChecksumDefinitionTable, CFE_Status_t);
}
