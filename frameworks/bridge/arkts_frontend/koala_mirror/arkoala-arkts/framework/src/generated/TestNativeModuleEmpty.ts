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

export class TestNativeModuleEmpty {
    _TestCallIntNoArgs(arg0: int32): int32 {
        console.log("_TestCallIntNoArgs")
        return 0
    }
    _TestCallIntIntArraySum(arg0: int32, arg1: Int32Array, arg2: int32): int32 {
        console.log("_TestCallIntIntArraySum")
        return 0
    }
    _TestCallVoidIntArrayPrefixSum(arg0: int32, arr: Int32Array, arg2: int32): void {
        console.log("_TestCallVoidIntArrayPrefixSum")
    }
    _TestCallIntRecursiveCallback(arg0: int32, arr: KSerializerBuffer, arg2: int32): int32 {
        console.log("_TestCallIntRecursiveCallback")
        return 0
    }
    _TestCallIntMemory(arg0: int32, arg1: int32): int32 {
        console.log("_TestCallIntMemory")
        return 0
    }
    _TestWithBuffer(buffer: NativeBuffer): void {
        console.log("_TestWithBuffer")
    }
    _TestGetManagedCaller(kind: int32): KPointer {
        console.log("_TestGetManagedCaller")
        return -1
    }
    _TestGetManagedCallerSync(kind: int32): KPointer {
        console.log("_TestGetManagedCallerSync")
        return -1
    }
    _TestGetManagedHolder(): KPointer {
        console.log("_TestGetManagedHolder")
        return -1
    }
    _TestGetManagedReleaser(): KPointer {
        console.log("_TestGetManagedReleaser")
        return -1
    }
    _TestReadAndMutateManagedBuffer(arr: Uint8Array, len: int32): void {
        console.log("_TestReadAndMutateManagedBuffer")
    }
}