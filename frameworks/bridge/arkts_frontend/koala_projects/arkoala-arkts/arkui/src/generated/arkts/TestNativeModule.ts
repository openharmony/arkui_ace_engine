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

import { KInt, KBoolean, KFloat, KUInt, KStringPtr, KPointer, KNativePointer, KInt32ArrayPtr, KUint8ArrayPtr, KFloat32ArrayPtr, pointer, KInteropReturnBuffer, NativeBuffer, loadNativeModuleLibrary } from "@koalaui/interop"
import { int32, float32 } from "@koalaui/common"

export class TestNativeModule {
    static {
        loadNativeModuleLibrary("TestNativeModule")
    }
    native static _TestCallIntNoArgs(arg0: int32): int32 
    native static _TestCallIntIntArraySum(arg0: int32, arg1: KInt32ArrayPtr, arg2: int32): int32 
    native static _TestCallVoidIntArrayPrefixSum(arg0: int32, arr: KInt32ArrayPtr, arg2: int32): void 
    native static _TestCallIntRecursiveCallback(arg0: int32, arr: KUint8ArrayPtr, arg2: int32): int32 
    native static _TestCallIntMemory(arg0: int32, arg1: int32): int32 
    native static _Test_SetEventsApi(): void 
    native static _Test_Common_OnChildTouchTest(arr: KUint8ArrayPtr, arg: int32): void 
    native static _Test_List_OnScrollVisibleContentChange(arr: KUint8ArrayPtr, arg: int32): void 
    native static _Test_TextPicker_OnAccept(arr: KUint8ArrayPtr, arg: int32): void 
    native static _TestWithBuffer(buffer: NativeBuffer): void 
    native static _TestSetArkoalaCallbackCaller(): void 
    native static _TestSetArkoalaCallbackCallerSync(): void 
    native static _TestGetManagedCaller(kind: int32): KPointer 
    native static _TestGetManagedCallerSync(kind: int32): KPointer 
    native static _TestGetManagedHolder(): KPointer 
    native static _TestGetManagedReleaser(): KPointer 
    native static _TestReadAndMutateManagedBuffer(arr: KUint8ArrayPtr, len: int32): void 
}