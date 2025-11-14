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
 * Auto-Generated stub implementations for functions defined in cs_app header
 */

#include "cs_app.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CS_AppInit()
 * ----------------------------------------------------
 */
CFE_Status_t CS_AppInit(void)
{
    UT_GenStub_SetupReturnBuffer(CS_AppInit, CFE_Status_t);

    UT_GenStub_Execute(CS_AppInit, Basic, NULL);

    return UT_GenStub_GetReturnValue(CS_AppInit, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_AppMain()
 * ----------------------------------------------------
 */
void CS_AppMain(void)
{

    UT_GenStub_Execute(CS_AppMain, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_AppPipe()
 * ----------------------------------------------------
 */
CFE_Status_t CS_AppPipe(const CFE_SB_Buffer_t *BufPtr)
{
    UT_GenStub_SetupReturnBuffer(CS_AppPipe, CFE_Status_t);

    UT_GenStub_AddParam(CS_AppPipe, const CFE_SB_Buffer_t *, BufPtr);

    UT_GenStub_Execute(CS_AppPipe, Basic, NULL);

    return UT_GenStub_GetReturnValue(CS_AppPipe, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_CreateRestoreStatesFromCDS()
 * ----------------------------------------------------
 */
CFE_Status_t CS_CreateRestoreStatesFromCDS(void)
{
    UT_GenStub_SetupReturnBuffer(CS_CreateRestoreStatesFromCDS, CFE_Status_t);

    UT_GenStub_Execute(CS_CreateRestoreStatesFromCDS, Basic, NULL);

    return UT_GenStub_GetReturnValue(CS_CreateRestoreStatesFromCDS, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_HousekeepingCmd()
 * ----------------------------------------------------
 */
void CS_HousekeepingCmd(const CS_NoArgsCmd_t *CmdPtr)
{
    UT_GenStub_AddParam(CS_HousekeepingCmd, const CS_NoArgsCmd_t *, CmdPtr);

    UT_GenStub_Execute(CS_HousekeepingCmd, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_ProcessCmd()
 * ----------------------------------------------------
 */
void CS_ProcessCmd(const CFE_SB_Buffer_t *BufPtr)
{
    UT_GenStub_AddParam(CS_ProcessCmd, const CFE_SB_Buffer_t *, BufPtr);

    UT_GenStub_Execute(CS_ProcessCmd, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CS_UpdateCDS()
 * ----------------------------------------------------
 */
void CS_UpdateCDS(void)
{

    UT_GenStub_Execute(CS_UpdateCDS, Basic, NULL);
}
