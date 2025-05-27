/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

import { KInt, KLong, KBoolean, KFloat, KUInt, KStringPtr, KPointer, KNativePointer, KInt32ArrayPtr, KUint8ArrayPtr, KFloat32ArrayPtr, pointer, KInteropReturnBuffer, KSerializerBuffer, loadNativeModuleLibrary, NativeBuffer } from "@koalaui/interop"
import { int32, int64, float32 } from "@koalaui/common"

export class TestNativeModule {
    private static _isLoaded: boolean = false
    private static _LoadOnce(): boolean {
        if ((this._isLoaded) == (false))
        {
            this._isLoaded = true
            loadNativeModuleLibrary("TestNativeModule", TestNativeModule)
            return true
        }
        return false
    }
    static _TestCallIntNoArgs(arg0: int32): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestCallIntNoArgs(arg0)
        }
        throw new Error("Not implemented")
    }
    static _TestCallIntIntArraySum(arg0: int32, arg1: Int32Array, arg2: int32): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestCallIntIntArraySum(arg0, arg1, arg2)
        }
        throw new Error("Not implemented")
    }
    static _TestCallVoidIntArrayPrefixSum(arg0: int32, arr: Int32Array, arg2: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestCallVoidIntArrayPrefixSum(arg0, arr, arg2)
        }
        throw new Error("Not implemented")
    }
    static _TestCallIntRecursiveCallback(arg0: int32, arr: KSerializerBuffer, arg2: int32): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestCallIntRecursiveCallback(arg0, arr, arg2)
        }
        throw new Error("Not implemented")
    }
    static _TestCallIntMemory(arg0: int32, arg1: int32): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestCallIntMemory(arg0, arg1)
        }
        throw new Error("Not implemented")
    }
    static _TestWithBuffer(buffer: NativeBuffer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestWithBuffer(buffer)
        }
        throw new Error("Not implemented")
    }
    static _TestGetManagedCaller(kind: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestGetManagedCaller(kind)
        }
        throw new Error("Not implemented")
    }
    static _TestGetManagedCallerSync(kind: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestGetManagedCallerSync(kind)
        }
        throw new Error("Not implemented")
    }
    static _TestGetManagedHolder(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestGetManagedHolder()
        }
        throw new Error("Not implemented")
    }
    static _TestGetManagedReleaser(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestGetManagedReleaser()
        }
        throw new Error("Not implemented")
    }
    static _TestReadAndMutateManagedBuffer(arr: Uint8Array, len: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._TestReadAndMutateManagedBuffer(arr, len)
        }
        throw new Error("Not implemented")
    }
}