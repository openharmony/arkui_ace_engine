/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { ArkUINativeModule } from "@koalaui/arkoala"
import { ArkCommonPeer } from "@arkoala/arkui/generated/common"
// imports required intarfaces (now generation is disabled)
// import { NavigationTitleMode } from "@arkoala/arkui/ArkNavigationInterfaces"

import {
    TEST_COUNT, CALL_COUNT, testString1000, testLength_10_percent,
    testLength_number100, testNumber100
} from "@arkoala/arkui/test_data"
import { withStringResult } from "@koalaui/interop"

enum DumpOptions {
    TOTAL = 0,
    AVERAGE,
    PEAK,
    DETAILS,
    CLEAR
}

export function RunPerformanceTest(testName: string, testCnt: number, callCnt: number, testFunc: () => void) {
    for (let i = 0; i < testCnt; ++i) {
        for (let j = 0; j < callCnt; ++j) {
            ArkUINativeModule._StartPerf("perf_counter_self_cost")
            // do nothing ===> perf_counter_self_cost about 0.838 us.
            ArkUINativeModule._EndPerf("perf_counter_self_cost")
            ArkUINativeModule._StartPerf(testName)
            testFunc()
            ArkUINativeModule._EndPerf(testName)
        }
    }
    console.log(withStringResult(ArkUINativeModule._DumpPerf(DumpOptions.AVERAGE)))
    ArkUINativeModule._DumpPerf(DumpOptions.CLEAR)
}

export function startPerformanceTest() {
    let peer = ArkCommonPeer.create();
    RunPerformanceTest("idlize_restoreIdAttribute_testNumber100", TEST_COUNT, CALL_COUNT, () => {
        peer.restoreIdAttribute(testNumber100)
    })
    RunPerformanceTest("idlize_keyAttribute_testString1000", TEST_COUNT, CALL_COUNT, () => {
        peer.keyAttribute(testString1000)
    })
    RunPerformanceTest("idlize_widthAttribute_testLength_10_percent", TEST_COUNT, CALL_COUNT, () => {
        peer.width0Attribute(testLength_10_percent)
    })
    RunPerformanceTest("idlize_widthAttribute_testLength_number100", TEST_COUNT, CALL_COUNT, () => {
        peer.width0Attribute(testLength_number100)
    })
    RunPerformanceTest("idlize_paddingAttribute", TEST_COUNT, CALL_COUNT, () => {
        peer.paddingAttribute({
            top: testLength_10_percent, right: testLength_10_percent,
            bottom: testLength_10_percent, left: testLength_10_percent
        })
    })
    RunPerformanceTest("idlize_borderAttribute", TEST_COUNT, CALL_COUNT, () => {
        peer.borderAttribute({
            width: 5,
            color: 0,
            radius: 25,
            style: 1 // BorderStyle.Solid
        })
    });
}
