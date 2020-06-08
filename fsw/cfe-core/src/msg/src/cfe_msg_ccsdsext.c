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
 * Message CCSDS extended header initializations
 */
#include "cfe_msg_api.h"
#include "cfe_msg_priv.h"
#include "cfe_msg_defaults.h"
#include "cfe_error.h"

/* CCSDS Extended definitions */
#define CFE_MSG_EDSVER_SHIFT   11     /**< \brief CCSDS EDS version shift */
#define CFE_MSG_EDSVER_MASK    0xF800 /**< \brief CCSDS EDS version mask */
#define CFE_MSG_ENDIAN_SHIFT   10     /**< \brief CCSDS endian shift */
#define CFE_MSG_ENDIAN_MASK    0x0400 /**< \brief CCSDS endiam mask, little endian when set */
#define CFE_MSG_PLAYBACK_SHIFT 9      /**< \brief CCSDS playback shift */
#define CFE_MSG_PLAYBACK_MASK  0x0200 /**< \brief CCSDS playback flag, playback when set */
#define CFE_MSG_SUBSYS_MASK    0x01FF /**< \brief CCSDS Subsystem mask */

/******************************************************************************
 * CCSDS extended header initialization - See header file for details
 */
void CFE_MSG_SetDefaultCCSDSExt(CFE_MSG_Message_t *MsgPtr)
{

    CFE_MSG_SetEDSVersion(MsgPtr, (CFE_MSG_EDSVersion_t)CFE_PLATFORM_EDSVER);

#if (CFE_PLATFORM_ENDIAN == CCSDS_LITTLE_ENDIAN)
    CFE_MSG_SetEndian(MsgPtr, CFE_MSG_Endian_Little);
#else
    CFE_MSG_SetEndian(MsgPtr, CFE_MSG_Endian_Big);
#endif

    /* Default bits of the subsystem, for whatever isn't set by MsgId */
    CFE_MSG_SetSubsystem(MsgPtr, (CFE_MSG_Subsystem_t)CFE_PLATFORM_DEFAULT_SUBSYS);
    CFE_MSB_SetSystem(MsgPtr, (CFE_MSG_System_t)CFE_MISSION_SPACECRAFT_ID);

}
