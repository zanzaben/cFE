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

/*
 * Message header field not Zero or F
 */

/*
 * Includes
 */
#include "test_cfe_msg_ccsdspri.h"
#include "test_msg_utils.h"
#include "cfe_msg_api.h"

/* TODO update for cfe msg module, not gateway checks */

unsigned int Test_MSG_NotZero(const CFE_MSG_Message_t *MsgPtr)
{
    unsigned int               bits = 0;
    CFE_MSG_HeaderVersion_t    hdrver;
    bool                       hassec;
    CFE_MSG_Type_t             type;
    CFE_MSG_ApId_t             apid;
    CFE_MSG_SegmentationFlag_t segflag;
    CFE_MSG_SequenceCount_t    seqcnt;
    CFE_MSG_Size_t             size;
    CFE_MSG_SecHdrVersion_t    secver;
    CFE_MSG_PlaybackFlag_t     pback;
    CFE_MSG_Route_t            route;
    bool                       dtn;
    CFE_MSG_QOS_t              qos;
    CFE_MSG_FcnCode_t          fcncode;
    CFE_MSG_Source_t           source;
    CFE_TIME_SysTime_t         time;

    /* Primary */
    CFE_MSG_GetHeaderVersion(MsgPtr, &hdrver);
    if (hdrver != 0)
        bits |= MSG_HDRVER_FLAG;
    CFE_MSG_GetType(MsgPtr, &type);
    if (type != CFE_MSG_Type_Tlm)
        bits |= MSG_TYPE_FLAG;
    CFE_MSG_GetHasSecondaryHeader(MsgPtr, &hassec);
    if (hassec)
        bits |= MSG_HASSEC_FLAG;
    CFE_MSG_GetApId(MsgPtr, &apid);
    if (apid != 0)
        bits |= MSG_APID_FLAG;
    CFE_MSG_GetSegmentationFlag(MsgPtr, &segflag);
    if (segflag != CFE_MSG_SegFlag_Continue)
        bits |= MSG_SEGMENT_FLAG;
    CFE_MSG_GetSequenceCount(MsgPtr, &seqcnt);
    if (seqcnt != 0)
        bits |= MSG_SEQUENCE_FLAG;
    CFE_MSG_GetSize(MsgPtr, &size);
    if (size != TEST_MSG_SIZE_OFFSET)
        bits |= MSG_LENGTH_FLAG;

    /* Extended */
    CFE_MSG_GetSecHdrVersion(MsgPtr, &secver);
    if (secver != 0)
        bits |= MSG_SECHDRVER_FLAG;
    CFE_MSG_GetPlaybackFlag(MsgPtr, &pback);
    if (pback != CFE_MSG_PlayFlag_Original)
        bits |= MSG_PBACK_FLAG;
    CFE_MSG_GetRoute(MsgPtr, &route);
    if (route != 0)
        bits |= MSG_ROUTE_FLAG;
    CFE_MSG_GetDTN(MsgPtr, &dtn);
    if (dtn)
        bits |= MSG_DTN_FLAG;
    CFE_MSG_GetQOS(MsgPtr, &qos);
    if (qos != 0)
        bits |= MSG_QOS_FLAG;

    /* Secondary */
    CFE_MSG_GetFcnCode(MsgPtr, &fcncode); // TODO check status
    if (fcncode != 0)
        bits |= MSG_FCNCODE_FLAG;
    CFE_MSG_GetSource(MsgPtr, &source);
    if (source != 0)
        bits |= MSG_SOURCE_FLAG;
    CFE_MSG_GetMsgTime(MsgPtr, &time);
    if (time.Seconds != 0 || time.Subseconds != 0)
        bits |= MSG_TIME_FLAG;

    return bits;
}

unsigned int Test_MSG_NotF(const CFE_MSG_Message_t *MsgPtr)
{
    unsigned int               bits = 0;
    CFE_MSG_HeaderVersion_t    hdrver;
    bool                       hassec;
    CFE_MSG_Type_t             type;
    CFE_MSG_ApId_t             apid;
    CFE_MSG_SegmentationFlag_t segflag;
    CFE_MSG_SequenceCount_t    seqcnt;
    CFE_MSG_Size_t             size;
    CFE_MSG_SecHdrVersion_t    secver;
    CFE_MSG_PlaybackFlag_t     pback;
    CFE_MSG_Route_t            route;
    bool                       dtn;
    CFE_MSG_QOS_t              qos;
    CFE_MSG_FcnCode_t          fcncode;
    CFE_MSG_Source_t           source;
    CFE_TIME_SysTime_t         time;

    /* Primary */
    CFE_MSG_GetHeaderVersion(MsgPtr, &hdrver);
    if (hdrver != 0x7)
        bits |= MSG_HDRVER_FLAG;
    CFE_MSG_GetType(MsgPtr, &type);
    if (type != CFE_MSG_Type_Cmd)
        bits |= MSG_TYPE_FLAG;
    CFE_MSG_GetHasSecondaryHeader(MsgPtr, &hassec);
    if (!hassec)
        bits |= MSG_HASSEC_FLAG;
    CFE_MSG_GetApId(MsgPtr, &apid);
    if (apid != 0x7FF)
        bits |= MSG_APID_FLAG;
    CFE_MSG_GetSegmentationFlag(MsgPtr, &segflag);
    if (segflag != CFE_MSG_SegFlag_Unsegmented)
        bits |= MSG_SEGMENT_FLAG;
    CFE_MSG_GetSequenceCount(MsgPtr, &seqcnt);
    if (seqcnt != 0x3FFF)
        bits |= MSG_SEQUENCE_FLAG;
    CFE_MSG_GetSize(MsgPtr, &size);
    if (size != 0xFFFF + TEST_MSG_SIZE_OFFSET)
        bits |= MSG_LENGTH_FLAG;

    /* Extended */
    CFE_MSG_GetSecHdrVersion(MsgPtr, &secver);
    if (secver != 0xF)
        bits |= MSG_SECHDRVER_FLAG;
    CFE_MSG_GetPlaybackFlag(MsgPtr, &pback);
    if (pback != CFE_MSG_PlayFlag_Playback)
        bits |= MSG_PBACK_FLAG;
    CFE_MSG_GetRoute(MsgPtr, &route);
    if (route != 0x3F)
        bits |= MSG_ROUTE_FLAG;
    CFE_MSG_GetDTN(MsgPtr, &dtn);
    if (!dtn)
        bits |= MSG_DTN_FLAG;
    CFE_MSG_GetQOS(MsgPtr, &qos);
    if (qos != 0xF)
        bits |= MSG_QOS_FLAG;

    /* Secondary */
    CFE_MSG_GetFcnCode(MsgPtr, &fcncode); // TODO check status
    if (fcncode != 0xFF)
        bits |= MSG_FCNCODE_FLAG;
    CFE_MSG_GetSource(MsgPtr, &source);
    if (source != 0xFF)
        bits |= MSG_SOURCE_FLAG;
    CFE_MSG_GetMsgTime(MsgPtr, &time);
    if (time.Seconds != 0xFFFFFFFF || time.Subseconds != 0xFFFF0000)
        bits |= MSG_TIME_FLAG;

    return bits;
}
