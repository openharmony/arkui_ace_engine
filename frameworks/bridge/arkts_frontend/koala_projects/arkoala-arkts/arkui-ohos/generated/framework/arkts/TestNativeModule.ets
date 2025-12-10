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

import { KInt, KLong, KBoolean, KFloat, KDouble, KUInt, KStringPtr, KPointer, KNativePointer, KInt32ArrayPtr, KUint8ArrayPtr, KFloat32ArrayPtr, pointer, KInteropReturnBuffer, KSerializerBuffer, loadNativeModuleLibrary, NativeBuffer } from '@koalaui/interop'
import { int32, int64, float32 } from '@koalaui/common'

export class TestNativeModule {
    static {
        loadNativeModuleLibrary("TestNativeModule")
    }
    @ani.unsafe.Direct
    native static _TestCallIntNoArgs(arg0: KInt): KInt
    @ani.unsafe.Quick
    native static _TestCallIntIntArraySum(arg0: KInt, arg1: KInt32ArrayPtr, arg2: KInt): KInt
    @ani.unsafe.Quick
    native static _TestCallVoidIntArrayPrefixSum(arg0: KInt, arr: KInt32ArrayPtr, arg2: KInt): void
    @ani.unsafe.Direct
    native static _TestCallIntRecursiveCallback(arg0: KInt, arr: KSerializerBuffer, arg2: KInt): KInt
    @ani.unsafe.Direct
    native static _TestCallIntMemory(arg0: KInt, arg1: KInt): KInt
    @ani.unsafe.Quick
    native static _TestWithBuffer(buffer: ArrayBuffer): void
    @ani.unsafe.Direct
    native static _TestGetManagedCaller(kind: KInt): KPointer
    @ani.unsafe.Direct
    native static _TestGetManagedCallerSync(kind: KInt): KPointer
    @ani.unsafe.Direct
    native static _TestGetManagedHolder(): KPointer
    @ani.unsafe.Direct
    native static _TestGetManagedReleaser(): KPointer
    @ani.unsafe.Quick
    native static _TestReadAndMutateManagedBuffer(arr: KUint8ArrayPtr, len: KInt): void
}