/*
**  GSC-18128-1, "Core Flight Executive Version 6.7"
**
**  Copyright (c) 2006-2019 United States Government as represented by
**  the Administrator of the National Aeronautics and Space Administration.
**  All Rights Reserved.
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**    http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
*/

/******************************************************************************
** File: cfe_sb_util.c
**
** Purpose:
**      This file contains 'access' macros and functions for reading and
**      writing message header fields.
**
** Author:   R.McGraw/SSI
**
******************************************************************************/


/*
** Include Files
*/

#include "cfe_sb.h"
#include "ccsds.h"
#include "osapi.h"
#include "cfe_error.h"
#include "cfe_msg_api.h"

#include <string.h>

/*
 * Function: CFE_SB_InitMsg - See API and header file for details
 */
void CFE_SB_InitMsg(void           *MsgPtr,
                    CFE_SB_MsgId_t MsgId,
                    uint16         Length,
                    bool        Clear )
{

   CFE_MSG_Init((CFE_MSG_Message_t *)MsgPtr, MsgId, Length, Clear);

} /* end CFE_SB_InitMsg */

/* TODO deprecate */
#if 0
/******************************************************************************
**  Function:  CFE_SB_MsgHdrSize()
**
**  Purpose:
**    Get the size of a message header.
**
**  Arguments:
**    *MsgPtr - Pointer to a SB message 
**
**  Return:
**     Size of Message Header.
*/
uint16 CFE_SB_MsgHdrSize(const CFE_SB_Msg_t *MsgPtr)
{

    uint16 size;
    const CCSDS_PriHdr_t  *HdrPtr;

    HdrPtr = (const CCSDS_PriHdr_t *) MsgPtr;

    /* if secondary hdr is not present... */
    /* Since all cFE messages must have a secondary hdr this check is not needed */
    if(CCSDS_RD_SHDR(*HdrPtr) == 0){
        size = sizeof(CCSDS_PriHdr_t);

    }else if(CCSDS_RD_TYPE(*HdrPtr) == CCSDS_CMD){

        size = CFE_SB_CMD_HDR_SIZE;

    }else{

        size = CFE_SB_TLM_HDR_SIZE;
  
    }

   return size;

}/* end CFE_SB_MsgHdrSize */


/*
 * Function: CFE_SB_GetUserData - See API and header file for details
 */
void *CFE_SB_GetUserData(CFE_SB_MsgPtr_t MsgPtr)
{
    uint8           *BytePtr;
    uint16          HdrSize;

    BytePtr = (uint8 *)MsgPtr;
    HdrSize = CFE_SB_MsgHdrSize(MsgPtr);

    return (BytePtr + HdrSize);
}/* end CFE_SB_GetUserData */


/*
 * Function: CFE_SB_GetUserDataLength - See API and header file for details
 */
uint16 CFE_SB_GetUserDataLength(const CFE_SB_Msg_t *MsgPtr)
{
    uint16 TotalMsgSize;
    uint16 HdrSize;

    TotalMsgSize = CFE_SB_GetTotalMsgLength(MsgPtr);
    HdrSize = CFE_SB_MsgHdrSize(MsgPtr);

    return (TotalMsgSize - HdrSize);
}/* end CFE_SB_GetUserDataLength */


/*
 * Function: CFE_SB_SetUserDataLength - See API and header file for details
 */
void CFE_SB_SetUserDataLength(CFE_SB_MsgPtr_t MsgPtr, uint16 DataLength)
{
    uint32 TotalMsgSize, HdrSize;

    HdrSize = CFE_SB_MsgHdrSize(MsgPtr);
    TotalMsgSize = HdrSize + DataLength;
    CCSDS_WR_LEN(MsgPtr->Hdr,TotalMsgSize);

}/* end CFE_SB_SetUserDataLength */
#endif

/*
 * Function: CFE_SB_GetTotalMsgLength - See API and header file for details
 */
uint16 CFE_SB_GetTotalMsgLength(const CFE_SB_Msg_t *MsgPtr)
{

    CFE_MSG_Size_t size;

    /* Doesn't check return, TODO deprecate self */
    CFE_MSG_GetSize(MsgPtr, &size);

    /* Known bug that this API can't return maximum ccsds size */
    return (uint16)size;

}/* end CFE_SB_GetTotalMsgLength */


/*
 * Function: CFE_SB_SetTotalMsgLength - See API and header file for details
 */
void CFE_SB_SetTotalMsgLength(CFE_SB_MsgPtr_t MsgPtr,uint16 TotalLength)
{

    /* Doesn't check return, TODO deprecate self */
    CFE_MSG_SetSize(MsgPtr, TotalLength);

}/* end CFE_SB_SetTotalMsgLength */


/*
 * Function: CFE_SB_GetMsgTime - See API and header file for details
 */
CFE_TIME_SysTime_t CFE_SB_GetMsgTime(CFE_SB_MsgPtr_t MsgPtr)
{
    CFE_TIME_SysTime_t TimeFromMsg;

    CFE_MSG_GetMsgTime(MsgPtr, &TimeFromMsg);

    return TimeFromMsg;

}/* end CFE_SB_GetMsgTime */


/*
 * Function: CFE_SB_SetMsgTime - See API and header file for details
 */
int32 CFE_SB_SetMsgTime(CFE_SB_MsgPtr_t MsgPtr, CFE_TIME_SysTime_t NewTime)
{

    return CFE_MSG_SetMsgTime(MsgPtr, NewTime);

}/* end CFE_SB_SetMsgTime */


/*
 * Function: CFE_SB_TimeStampMsg - See API and header file for details
 */
void CFE_SB_TimeStampMsg(CFE_SB_MsgPtr_t MsgPtr)
{
    CFE_SB_SetMsgTime(MsgPtr,CFE_TIME_GetTime());

}/* end CFE_SB_TimeStampMsg */


/*
 * Function: CFE_SB_GetCmdCode - See API and header file for details
 */
uint16 CFE_SB_GetCmdCode(CFE_SB_MsgPtr_t MsgPtr)
{

    CFE_MSG_FcnCode_t fc;

    CFE_MSG_GetFcnCode(MsgPtr, &fc);

    return fc;

}/* end CFE_SB_GetCmdCode */


/*
 * Function: CFE_SB_SetCmdCode - See API and header file for details
 */
int32 CFE_SB_SetCmdCode(CFE_SB_MsgPtr_t MsgPtr,
                      uint16 CmdCode)
{

    return CFE_MSG_SetFcnCode(MsgPtr, CmdCode);

}/* end CFE_SB_SetCmdCode */

/* TODO remove */
#if 0
/*
 * Function: CFE_SB_GetChecksum - See API and header file for details
 */
uint16 CFE_SB_GetChecksum(CFE_SB_MsgPtr_t MsgPtr)
{

    CFE_SB_CmdHdr_t     *CmdHdrPtr;

    /* if msg type is telemetry or there is no secondary hdr... */
    if((CCSDS_RD_TYPE(MsgPtr->Hdr) == CCSDS_TLM)||(CCSDS_RD_SHDR(MsgPtr->Hdr) == 0)){
        return 0;
    }/* end if */

    /* cast the input pointer to a Cmd Msg pointer */
    CmdHdrPtr = (CFE_SB_CmdHdr_t *)MsgPtr;

    return CCSDS_RD_CHECKSUM(CmdHdrPtr->Cmd.Sec);

}/* end CFE_SB_GetChecksum */
#endif

/*
 * Function: CFE_SB_GenerateChecksum - See API and header file for details
 */
void CFE_SB_GenerateChecksum(CFE_SB_MsgPtr_t MsgPtr)
{

    CFE_MSG_GenerateChecksum(MsgPtr);

}/* end CFE_SB_GenerateChecksum */


/*
 * Function: CFE_SB_ValidateChecksum - See API and header file for details
 */
bool CFE_SB_ValidateChecksum(CFE_SB_MsgPtr_t MsgPtr)
{
    bool isvalid;

    CFE_MSG_ValidateChecksum(MsgPtr, &isvalid);

    return isvalid;

}/* end CFE_SB_ValidateChecksum */


/*
 * Function: CFE_SB_MessageStringGet - See API and header file for details
 */
int32 CFE_SB_MessageStringGet(char *DestStringPtr, const char *SourceStringPtr, const char *DefaultString, uint32 DestMaxSize, uint32 SourceMaxSize)
{
    int32 Result;

    /*
     * Error in caller if DestMaxSize == 0.
     * Cannot terminate the string, since there is no place for the NUL
     * In this case, do nothing
     */
    if (DestMaxSize == 0)
    {
        Result = CFE_SB_BAD_ARGUMENT;
    }
    else
    {
        Result = 0;

        /*
         * Check if should use the default, which is if
         * the source string has zero length (first char is NUL).
         */
        if (DefaultString != NULL && (SourceMaxSize == 0 || *SourceStringPtr == 0))
        {
            SourceStringPtr = DefaultString;
            SourceMaxSize = DestMaxSize;
        }

        /* Reserve 1 character for the required NUL */
        --DestMaxSize;

        while (SourceMaxSize > 0 && *SourceStringPtr != 0 && DestMaxSize > 0)
        {
            *DestStringPtr = *SourceStringPtr;
            ++DestStringPtr;
            ++SourceStringPtr;
            --SourceMaxSize;
            --DestMaxSize;

            ++Result;
        }

        /* Put the NUL in the last character */
        *DestStringPtr = 0;
    }

    return Result;
}


/*
 * Function: CFE_SB_MessageStringSet - See API and header file for details
 */
int32 CFE_SB_MessageStringSet(char *DestStringPtr, const char *SourceStringPtr, uint32 DestMaxSize, uint32 SourceMaxSize)
{
    int32 Result;

    Result = 0;

    while (SourceMaxSize > 0 && *SourceStringPtr != 0 && DestMaxSize > 0)
    {
        *DestStringPtr = *SourceStringPtr;
        ++DestStringPtr;
        ++SourceStringPtr;
        ++Result;
        --DestMaxSize;
        --SourceMaxSize;
    }

    /*
     * Pad the remaining space with NUL chars,
     * but this should NOT be included in the final size
     */
    while (DestMaxSize > 0)
    {
        /* Put the NUL in the last character */
        *DestStringPtr = 0;
        ++DestStringPtr;
        --DestMaxSize;
    }

    return Result;
}
