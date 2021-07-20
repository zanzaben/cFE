/*************************************************************************
**
**      GSC-18128-1, "Core Flight Executive Version 6.7"
**
**      Copyright (c) 2006-2019 United States Government as represented by
**      the Administrator of the National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      Licensed under the Apache License, Version 2.0 (the "License");
**      you may not use this file except in compliance with the License.
**      You may obtain a copy of the License at
**
**        http://www.apache.org/licenses/LICENSE-2.0
**
**      Unless required by applicable law or agreed to in writing, software
**      distributed under the License is distributed on an "AS IS" BASIS,
**      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**      See the License for the specific language governing permissions and
**      limitations under the License.
**
** File: es_info_test.c
**
** Purpose:
**   Functional test of FS File Utility APIs
**
**   Demonstration of how to register and use the UT assert functions.
**
*************************************************************************/

/*
 * Includes
 */

#include "cfe_test.h"

void TestCalculateCRC2(void)
{
    const char *Data = "Random Stuff";
    uint8       Data2[12];
    uint32      expectedCrc      = 20824;
    uint32      inputCrc         = 345353;
    uint32      expectedBlockCrc = 2688;

    UtPrintf("Testing: CFE_ES_CalculateCRC");

    UtAssert_UINT32_EQ(CFE_ES_CalculateCRC(Data, sizeof(Data), 0, CFE_MISSION_ES_DEFAULT_CRC), expectedCrc);

    memset(Data2, 1, sizeof(Data2));
    UtAssert_UINT32_EQ(CFE_ES_CalculateCRC(&Data2, sizeof(Data2), inputCrc, CFE_MISSION_ES_CRC_16), expectedBlockCrc);

    UtAssert_UINT32_EQ(CFE_ES_CalculateCRC(Data, sizeof(Data), 0, CFE_MISSION_ES_CRC_8), 0);
    UtAssert_UINT32_EQ(CFE_ES_CalculateCRC(Data, sizeof(Data), 0, CFE_MISSION_ES_CRC_32), 0);

    UtAssert_UINT32_EQ(CFE_ES_CalculateCRC(NULL, sizeof(Data), expectedCrc, CFE_MISSION_ES_CRC_16), expectedCrc);
    UtAssert_UINT32_EQ(CFE_ES_CalculateCRC(Data, 0, expectedBlockCrc, CFE_MISSION_ES_CRC_16), expectedBlockCrc);
}

void FSUtilTestSetup(void)
{
    UtTest_Add(TestCalculateCRC2, NULL, NULL, "Test Calculate CRC");
}
