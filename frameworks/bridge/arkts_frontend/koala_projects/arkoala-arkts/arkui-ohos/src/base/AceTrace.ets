/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { KInt } from "@koalaui/interop"

import { ArkUIAniModule } from "../ani/arkts/ArkUIAniModule"

export class AceTrace {

    static attributeSetTraceEnabled: boolean = false

    static GetAttributeSetTraceEnabled(): boolean {
        return AceTrace.attributeSetTraceEnabled
    }

    static updateAttributeSetTraceEnabled() {
        AceTrace.attributeSetTraceEnabled = ArkUIAniModule._GetAttributeSetTraceEnabled()
    }

    static begin(traceName: string) {
        ArkUIAniModule._TraceBegin(traceName)
    }

    static end() {
        ArkUIAniModule._TraceEnd()
    }

    static asyncBegin(traceName: string, taskId: KInt) {
        ArkUIAniModule._AsyncTraceBegin(traceName, taskId)
    }

    static asyncEnd(traceName: string, taskId: KInt) {
        ArkUIAniModule._AsyncTraceEnd(traceName, taskId)
    }

}

export class hiTraceMeter {

    static startTrace(traceName: string, taskId: KInt) {
        ArkUIAniModule._AsyncTraceBegin(traceName, taskId)
    }

    static finishTrace(traceName: string, taskId: KInt) {
        ArkUIAniModule._AsyncTraceEnd(traceName, taskId)
    }

}