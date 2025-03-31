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
import { InteropNativeModule } from "@koalaui/interop"
import { int32, int8Array } from "@koalaui/common"

export type UserViewBuilder =
/** @memo */
() => void

export class UserView {
    constructor() {}
    getBuilder(): UserViewBuilder {
        throw new Error("User must override this method");
    }

    // TODO: these native functions are here temporary.
    static startNativeLog(group: int32) {
        InteropNativeModule._StartGroupedLog(group)
    }

    static stopNativeLog(group: int32) {
        InteropNativeModule._StopGroupedLog(group)
    }

    static getNativeLog(group: int32): string {
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

    static printNativeLog(group: int32) {
        InteropNativeModule._PrintGroupedLog(group)
    }
}

export class EntryPoint {
    constructor() {}
    /** @memo */
    entry(): void {
    }
}
