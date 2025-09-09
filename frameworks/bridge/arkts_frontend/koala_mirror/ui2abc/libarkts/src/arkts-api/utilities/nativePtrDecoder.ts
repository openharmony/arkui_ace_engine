/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { int32 } from "@koalaui/common"
import {
    Access,
    ArrayDecoder,
    CallbackRegistry,
    NativeStringBase,
    nullptr,
    pointer,
    providePlatformDefinedData,
    withByteArray
} from "@koalaui/interop"
import { global } from "../static/global"

class NativeString extends NativeStringBase {
    constructor(ptr: pointer) {
        super(ptr)
    }
    protected bytesLength(): int32 {
        return global.interop._StringLength(this.ptr)
    }
    protected getData(data: Uint8Array): void {
        withByteArray(data, Access.WRITE, (dataPtr: pointer) => {
            global.interop._StringData(this.ptr, dataPtr, data.length)
        })
    }
    close(): void {
        global.interop._InvokeFinalizer(this.ptr, global.interop._GetStringFinalizer())
        this.ptr = nullptr
    }
}

providePlatformDefinedData({
    nativeString(ptr: pointer): NativeStringBase {
        return new NativeString(ptr)
    },
    nativeStringArrayDecoder(): ArrayDecoder<NativeStringBase> {
        throw new Error("Not yet implemented")
    },
    callbackRegistry(): CallbackRegistry | undefined {
        return undefined
    }
})

export class NativePtrDecoder extends ArrayDecoder<pointer> {
    getArraySize(blob: pointer) {
        return global.interop._GetPtrVectorSize(blob)
    }
    disposeArray(blob: pointer): void {
        // Improve:
    }
    getArrayElement(blob: pointer, index: int32): pointer {
        return global.interop._GetPtrVectorElement(blob, index)
    }
}