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
 * Message access APIs
 */

#ifndef _cfe_msg_
#define _cfe_msg_

/*
 * Includes
 */
#include "common_types.h"
#include "cfe_mission_cfg.h"
#include "cfe_sb.h"

/** @defgroup CFEAPIMSGChecksum cFE Message Checksum Control APIs
 * @{
 */

/*****************************************************************************/
/**
** \brief Gets the checksum field from a software bus message.
**
** \par Description
**          This routine gets the checksum (or other message integrity check
**          value) from a software bus message.  The contents and location of
**          this field will depend on the underlying implementation of software
**          bus messages.  It may be a checksum, a CRC, or some other algorithm.
**          Users should not call this function as part of a message integrity
**          check (call #CFE_SB_ValidateChecksum instead).
**
** \par Assumptions, External Events, and Notes:
**          - If the underlying implementation of software bus messages does not
**            include a checksum field, then this routine will return a zero.
**
** \param[in]  MsgPtr      A pointer to the buffer that contains the software bus message.
**                         This must point to the first byte of the message header.
**
** \return The checksum included in the software bus message header (if present), otherwise,
**         returns a checksum value of zero.
**/
uint16 CFE_MSG_GetChecksum(CFE_SB_MsgPtr_t MsgPtr);

/*****************************************************************************/
/**
** \brief Calculates and sets the checksum of a software bus message
**
** \par Description
**          This routine calculates the checksum of a software bus message according
**          to an implementation-defined algorithm.  Then, it sets the checksum field
**          in the message with the calculated value.  The contents and location of
**          this field will depend on the underlying implementation of software bus
**          messages.  It may be a checksum, a CRC, or some other algorithm.
**
** \par Assumptions, External Events, and Notes:
**          - If the underlying implementation of software bus messages does not
**            include a checksum field, then this routine will do nothing.
**
** \param[in]  MsgPtr      A pointer to the buffer that contains the software bus message.
**                         This must point to the first byte of the message header.
**/
void CFE_MSG_GenerateChecksum(CFE_SB_MsgPtr_t MsgPtr);

/*****************************************************************************/
/**
** \brief Validates the checksum of a software bus message.
**
** \par Description
**          This routine calculates the expected checksum of a software bus message
**          according to an implementation-defined algorithm.  Then, it checks the
**          calculated value against the value in the message's checksum.  If the
**          checksums do not match, this routine will generate an event message
**          reporting the error.
**
** \par Assumptions, External Events, and Notes:
**          - If the underlying implementation of software bus messages does not
**            include a checksum field, then this routine will always return \c true.
**
** \param[in]  MsgPtr      A pointer to the buffer that contains the software bus message.
**                         This must point to the first byte of the message header.
**
** \return Boolean checksum result
** \retval true  The checksum field in the packet is valid.
** \retval false The checksum field in the packet is not valid or the message type is wrong.
**/
bool CFE_MSG_ValidateChecksum(CFE_SB_MsgPtr_t MsgPtr);
/**@}*/

/** @defgropu CFEAPIMSGCmdCode cFE Message Command Code APIs
 * @{
 */

/*****************************************************************************/
/**
** \brief Sets the command code field in a software bus message.
**
** \par Description
**          This routine sets the command code of a software bus message (if SB
**          messages are implemented as CCSDS packets, this will be the function code).
**
** \par Assumptions, External Events, and Notes:
**          - If the underlying implementation of software bus messages does not
**            include a command code field, then this routine will do nothing to
**            the message contents and will return #CFE_SB_WRONG_MSG_TYPE.
**
** \param[in]  MsgPtr      A pointer to the buffer that contains the software bus message.
**                         This must point to the first byte of the message header.
**
** \param[in]  CmdCode     The command code to include in the message.
**
** \return Execution status, see \ref CFEReturnCodes
** \retval #CFE_SUCCESS           \copybrief CFE_SUCCESS
** \retval #CFE_SB_WRONG_MSG_TYPE \copybrief CFE_SB_WRONG_MSG_TYPE
**
**/
int32 CFE_MSG_SetCmdCode(CFE_SB_MsgPtr_t MsgPtr,
                         uint16 CmdCode);

/*****************************************************************************/
/**
** \brief Gets the command code field from a software bus message.
**
** \par Description
**          This routine gets the command code from a software bus message (if
**          SB messages are implemented as CCSDS packets, this will be the function
**          code).
**
** \par Assumptions, External Events, and Notes:
**          - If the underlying implementation of software bus messages does not
**            include a command code field, then this routine will return a zero.
**
** \param[in]  MsgPtr      A pointer to the buffer that contains the software bus message.
**                         This must point to the first byte of the message header.
**
** \return The command code included in the software bus message header (if present).
**         Otherwise, returns a command code value of zero.
**/
uint16 CFE_MSG_GetCmdCode(CFE_SB_MsgPtr_t MsgPtr);

/**@}*/

/** @defgropu CFEAPIMSGTime cFE Message Time APIs
 * @{
 */

/*****************************************************************************/
/**
** \brief Gets the time field from a software bus message.
**
** \par Description
**          This routine gets the time from a software bus message.
**
** \par Assumptions, External Events, and Notes:
**          - If the underlying implementation of software bus messages does not
**            include a time field, then this routine will return a zero time.
**          - Note default implementation of command messages do not have a time field.
**
** \param[in]  MsgPtr      A pointer to the buffer that contains the software bus message.
**                         This must point to the first byte of the message header.
** \param[out] Time        Time from the message
**
** \return Execution status, see \ref CFEReturnCodes
** \retval #CFE_SUCCESS           \copybrief CFE_SUCCESS
** \retval #CFE_SB_WRONG_MSG_TYPE \copybrief CFE_SB_WRONG_MSG_TYPE
**/
int32 CFE_MSG_GetMsgTime(CFE_TIME_SysTime_t *Time, CFE_SB_MsgPtr_t MsgPtr);

/*****************************************************************************/
/**
** \brief Sets the time field in a software bus message.
**
** \par Description
**          This routine sets the time of a software bus message.  Most applications
**          will want to use #CFE_SB_TimeStampMsg instead of this function.  But,
**          when needed, #CFE_SB_SetMsgTime can be used to send a group of SB messages
**          with identical time stamps.
**
** \par Assumptions, External Events, and Notes:
**          - If the underlying implementation of software bus messages does not include
**            a time field, then this routine will do nothing to the message contents
**            and will return #CFE_SB_WRONG_MSG_TYPE.
**          - Note default implementation of command messages do not have a time field
**            and will trigger the #CFE_SB_WRONG_MSG_TYPE error
**
** \param[in]  MsgPtr      A pointer to the buffer that contains the software bus message.
**                         This must point to the first byte of the message header.
**
** \param[in]  Time        The time to include in the message.  This will usually be a time
**                         returned by the function #CFE_TIME_GetTime.
**
** \return Execution status, see \ref CFEReturnCodes
** \retval #CFE_SUCCESS           \copybrief CFE_SUCCESS
** \retval #CFE_SB_WRONG_MSG_TYPE \copybrief CFE_SB_WRONG_MSG_TYPE
**/
int32 CFE_MSG_SetMsgTime(CFE_SB_MsgPtr_t MsgPtr,
                       CFE_TIME_SysTime_t Time);

/**@}*/


#endif /* _cfe_msg_ */
