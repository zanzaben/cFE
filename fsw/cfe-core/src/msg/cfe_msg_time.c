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
 *  Time field access functions
 */
#include "cfe_sb.h"
#include "cfe_msg.h"
#include "cfe_error.h"
#include <string.h>

/******************************************************************************
 * Set message time - See API and header file for details
 */
int32 CFE_MSG_SetMsgTime(CFE_SB_MsgPtr_t MsgPtr, CFE_TIME_SysTime_t NewTime)
{

    int32 Result = CFE_SB_WRONG_MSG_TYPE;

    CFE_SB_TlmHdr_t *TlmHdrPtr;

    /* declare format specific vars */
    #if (CFE_MISSION_SB_PACKET_TIME_FORMAT == CFE_MISSION_SB_TIME_32_16_SUBS)
    uint16 LocalSubs16;
    #elif (CFE_MISSION_SB_PACKET_TIME_FORMAT == CFE_MISSION_SB_TIME_32_32_M_20)
    uint32 LocalSubs32;
    #endif

    /* cannot set time if msg type is a command or msg has no secondary hdr */
    if ((CCSDS_RD_TYPE(MsgPtr->Hdr) != CCSDS_CMD) && (CCSDS_RD_SHDR(MsgPtr->Hdr) != 0)) {

        /* copy time data to/from packets to eliminate alignment issues */
        TlmHdrPtr = (CFE_SB_TlmHdr_t *) MsgPtr;

        #if (CFE_MISSION_SB_PACKET_TIME_FORMAT == CFE_MISSION_SB_TIME_32_16_SUBS)

        /* convert time from CFE_TIME_SysTime_t format to packet format */
        LocalSubs16 = (uint16) (NewTime.Subseconds >> 16);
        memcpy(&TlmHdrPtr->Tlm.Sec.Time[0], &NewTime.Seconds, 4);
        memcpy(&TlmHdrPtr->Tlm.Sec.Time[4], &LocalSubs16, 2);
        Result = CFE_SUCCESS;

        #elif (CFE_MISSION_SB_PACKET_TIME_FORMAT == CFE_MISSION_SB_TIME_32_32_SUBS)

        /* no conversion necessary -- packet format = CFE_TIME_SysTime_t format */
        memcpy(&TlmHdrPtr->Tlm.Sec.Time[0], &NewTime.Seconds, 4);
        memcpy(&TlmHdrPtr->Tlm.Sec.Time[4], &NewTime.Subseconds, 4);
        Result = CFE_SUCCESS;

        #elif (CFE_MISSION_SB_PACKET_TIME_FORMAT == CFE_MISSION_SB_TIME_32_32_M_20)

        /* convert time from CFE_TIME_SysTime_t format to packet format */
        LocalSubs32 = CFE_TIME_Sub2MicroSecs(NewTime.Subseconds) << 12;
        memcpy(&TlmHdrPtr->Tlm.Sec.Time[0], &NewTime.Seconds, 4);
        memcpy(&TlmHdrPtr->Tlm.Sec.Time[4], &LocalSubs32, 4);
        Result = CFE_SUCCESS;

        #endif
    }

    return Result;
}

/******************************************************************************
 * Get message time -  See API and header file for details
 */
int32 CFE_MSG_GetMsgTime(CFE_TIME_SysTime_t *Time, CFE_SB_MsgPtr_t MsgPtr)
{

    int32 status = CFE_SB_WRONG_MSG_TYPE;
    uint32 LocalSecs32 = 0;
    uint32 LocalSubs32 = 0;

    #if (CFE_MISSION_SB_PACKET_TIME_FORMAT == CFE_MISSION_SB_TIME_32_16_SUBS)
    uint16 LocalSubs16;
    #endif

    CFE_SB_TlmHdr_t *TlmHdrPtr;

    /* if msg type is a command or msg has no secondary hdr, time = 0 */
    if ((CCSDS_RD_TYPE(MsgPtr->Hdr) != CCSDS_CMD) && (CCSDS_RD_SHDR(MsgPtr->Hdr) != 0)) {

        /* copy time data to/from packets to eliminate alignment issues */
        TlmHdrPtr = (CFE_SB_TlmHdr_t *)MsgPtr;

        #if (CFE_MISSION_SB_PACKET_TIME_FORMAT == CFE_MISSION_SB_TIME_32_16_SUBS)

        memcpy(&LocalSecs32, &TlmHdrPtr->Tlm.Sec.Time[0], 4);
        memcpy(&LocalSubs16, &TlmHdrPtr->Tlm.Sec.Time[4], 2);
        /* convert packet data into CFE_TIME_SysTime_t format */
        LocalSubs32 = ((uint32) LocalSubs16) << 16;

        #elif (CFE_MISSION_SB_PACKET_TIME_FORMAT == CFE_MISSION_SB_TIME_32_32_SUBS)

        memcpy(&LocalSecs32, &TlmHdrPtr->Tlm.Sec.Time[0], 4);
        memcpy(&LocalSubs32, &TlmHdrPtr->Tlm.Sec.Time[4], 4);
        /* no conversion necessary -- packet format = CFE_TIME_SysTime_t format */

        #elif (CFE_MISSION_SB_PACKET_TIME_FORMAT == CFE_MISSION_SB_TIME_32_32_M_20)

        memcpy(&LocalSecs32, &TlmHdrPtr->Tlm.Sec.Time[0], 4);
        memcpy(&LocalSubs32, &TlmHdrPtr->Tlm.Sec.Time[4], 4);
        /* convert packet data into CFE_TIME_SysTime_t format */
        LocalSubs32 = CFE_TIME_Micro2SubSecs((LocalSubs32 >> 12));

        #endif

        status = CFE_SUCCESS;
    }

    /* return the packet time converted to CFE_TIME_SysTime_t format */
    Time->Seconds    = LocalSecs32;
    Time->Subseconds = LocalSubs32;

    return status;

}
