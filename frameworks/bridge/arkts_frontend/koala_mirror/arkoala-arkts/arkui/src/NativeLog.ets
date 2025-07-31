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
import { InteropNativeModule } from "@koalaui/interop"
import { int32, float32, int8Array } from "@koalaui/common"
import { TEST_LOG_NUMBER } from "./Application"
import { memo } from "@koalaui/runtime/annotations"

export class NativeLog {
    static Default: NativeLog = new NativeLog()
    private _isStarted: boolean = false
    startNativeLog(group: int32) {
        this._isStarted = true
        InteropNativeModule._StartGroupedLog(group)
    }

    stopNativeLog(group: int32) {
        this._isStarted = false
        InteropNativeModule._StopGroupedLog(group)
    }

    appendNativeLog(group: int32, message: string) {
        if (!this._isStarted) {
            this.startNativeLog(group)
        }
        InteropNativeModule._AppendGroupedLog(group, message)
    }

    getNativeLog(group: int32): string {
        let ptr = InteropNativeModule._GetGroupedLog(group)
        let length = InteropNativeModule._StringLength(ptr)
        let data = int8Array(length);
        // @ts-ignore
        InteropNativeModule._StringData(ptr, data, length)
        InteropNativeModule._InvokeFinalizer(ptr, InteropNativeModule._GetStringFinalizer())

        let result = new StringBuilder("")
        for (let i = 0; i < length; i++) {
            result.append(String.fromCharCode(data[i])) // Attention. This code causes native crash in arm64.
        }
        return result.toString()
    }

    printNativeLog(group: int32) {
        InteropNativeModule._PrintGroupedLog(group)
    }
}

export function nLog(...data: (object|int32|float32|boolean|string|undefined)[]): void {
    let result = new StringBuilder("")
    for (let i = 0; i < data.length; i++) {
        const fragment = data[i] == undefined ? "undefined" : data[i]!.toString()
        if (fragment == "") return
        result.append(fragment)
        if (i < data.length -1 ) {
            result.append(" ")
        }
        result.append("\n")
    }
    NativeLog.Default.appendNativeLog(TEST_LOG_NUMBER, result.toString())
}

@memo
export function uiLog(message: string): void {
    nLog(message)
}