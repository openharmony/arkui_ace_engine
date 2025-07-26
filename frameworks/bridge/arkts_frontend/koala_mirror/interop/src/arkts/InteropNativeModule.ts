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

import { int32, int64 } from "@koalaui/common";
import { KPointer, KUint8ArrayPtr, KInt, KSerializerBuffer } from "./InteropTypes";
import { callCallback } from "./callback"
import { loadNativeModuleLibrary } from "./loadLibraries"

export class InteropNativeModule {
    static {
        loadNativeModuleLibrary("InteropNativeModule")
    }
    static callCallbackFromNative(id: KInt, args: KSerializerBuffer, length: KInt): KInt {
        return callCallback(id, args, length)
    }
    native static _GetGroupedLog(index: int32): KPointer
    native static _StartGroupedLog(index: int32): void
    native static _StopGroupedLog(index: int32): void
    native static _AppendGroupedLog(index: int32, message: string): void
    native static _PrintGroupedLog(index: int32): void
    native static _GetStringFinalizer(): KPointer
    native static _InvokeFinalizer(ptr1: KPointer, ptr2: KPointer): void
    native static _IncrementNumber(value: number): number
    native static _GetPtrVectorElement(ptr1: KPointer, arg: int32): KPointer
    native static _StringLength(ptr1: KPointer): int32
    native static _StringData(ptr1: KPointer, arr: KUint8ArrayPtr, i: int32): void
    native static _StringMake(str1: string): KPointer
    native static _GetPtrVectorSize(ptr1: KPointer): int32
    @ani.unsafe.Quick
    native static _ManagedStringWrite(str1: string, arr: KPointer, arg: int32): int32
    native static _NativeLog(str1: string): void
    @ani.unsafe.Quick
    native static _Utf8ToString(data: KPointer, offset: int32, length: int32): string
    native static _StdStringToString(cstring: KPointer): string
    @ani.unsafe.Direct
    native static _CheckCallbackEvent(buffer: KSerializerBuffer, bufferLength: int32): int32
    native static _HoldCallbackResource(resourceId: int32): void
    native static _ReleaseCallbackResource(resourceId: int32): void
    native static _CallCallback(callbackKind: int32, args: KSerializerBuffer, argsSize: int32): void
    native static _CallCallbackSync(callbackKind: int32, args: KSerializerBuffer, argsSize: int32): void
    native static _CallCallbackResourceHolder(holder: KPointer, resourceId: int32): void
    native static _CallCallbackResourceReleaser(releaser: KPointer, resourceId: int32): void
    native static _LoadVirtualMachine(arg0: int32, arg1: string, arg2: string): int32
    native static _RunApplication(arg0: int32, arg1: int32): boolean
    native static _StartApplication(appUrl: string, appParams: string): KPointer
    native static _EmitEvent(eventType: int32, target: int32, arg0: int32, arg1: int32): string
    native static _CallForeignVM(context:KPointer, callback: int32, data: KSerializerBuffer, dataLength: int32): int32
    native static _SetForeignVMContext(context: KPointer): void
    native static _RestartWith(page: string): void
    @ani.unsafe.Direct
    native static _ReadByte(data: KPointer, index: int64, length: int64): int32
    @ani.unsafe.Direct
    native static _WriteByte(data: KPointer, index: int64, length: int64, value: int32): void
    @ani.unsafe.Direct
    native static _Malloc(length: int64): KPointer
    @ani.unsafe.Direct
    native static _Free(data: KPointer): void
    @ani.unsafe.Quick
    native static _CopyArray(data: KPointer, length: int64, args: KUint8ArrayPtr): void
    native static _ReportMemLeaks(): void
}

