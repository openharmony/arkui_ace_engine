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
import { KPointer, KSerializerBuffer, KStringPtr, KUint8ArrayPtr } from "./InteropTypes";
import { loadNativeModuleLibrary } from "./loadLibraries";

export class InteropNativeModule {
    public static _SetCallbackDispatcher(dispatcher: (id: int32, args: Uint8Array, length: int32) => int32): void { throw "method not loaded" }
    public static _CleanCallbackDispatcher(): void { throw "method not loaded" }

    public static _GetGroupedLog(index: int32): KPointer { throw "method not loaded" }
    public static _StartGroupedLog(index: int32): void { throw "method not loaded" }
    public static _StopGroupedLog(index: int32): void { throw "method not loaded" }
    public static _AppendGroupedLog(index: int32, message: string): void { throw "method not loaded" }
    public static _PrintGroupedLog(index: int32): void { throw "method not loaded" }
    public static _GetStringFinalizer(): KPointer { throw "method not loaded" }
    public static _IncrementNumber(value: number): number { throw "method not loaded" }
    public static _InvokeFinalizer(ptr1: KPointer, ptr2: KPointer): void { throw "method not loaded" }
    public static _GetPtrVectorElement(ptr1: KPointer, arg: int32): KPointer { throw "method not loaded" }
    public static _StringLength(ptr1: KPointer): int32 { throw "method not loaded" }
    public static _StringData(ptr1: KPointer, array: KUint8ArrayPtr, arrayLength: int32): void { throw "method not loaded" }
    public static _StringMake(str1: KStringPtr): KPointer { throw "method not loaded" }
    public static _GetPtrVectorSize(ptr1: KPointer): int32 { throw "method not loaded" }
    public static _ManagedStringWrite(str1: string, array: Uint8Array, arrayLength: int32, arg: int32): int32 { throw "method not loaded" }
    public static _NativeLog(str1: string): void { throw "method not loaded" }
    public static _Utf8ToString(data: KSerializerBuffer, offset: int32, length: int32): string { throw "method not loaded" }
    public static _StdStringToString(cstring: KPointer): string { throw "method not loaded" }
    public static _CheckCallbackEvent(buffer: KSerializerBuffer, bufferLength: int32): int32 { throw "method not loaded" }
    public static _HoldCallbackResource(resourceId: int32): void { throw "method not loaded" }
    public static _ReleaseCallbackResource(resourceId: int32): void { throw "method not loaded" }
    public static _CallCallback(callbackKind: int32, args: KSerializerBuffer, argsSize: int32): void { throw "method not loaded" }
    public static _CallCallbackSync(callbackKind: int32, args: KSerializerBuffer, argsSize: int32): void { throw "method not loaded" }
    public static _CallCallbackResourceHolder(holder: KPointer, resourceId: int32): void { throw "method not loaded" }
    public static _CallCallbackResourceReleaser(releaser: KPointer, resourceId: int32): void { throw "method not loaded" }
    public static _CallbackAwait(pipeline: KPointer): Object { throw "method not loaded" }
    public static _UnblockCallbackWait(pipeline: KPointer): void { throw "method not loaded" }
    public static _MaterializeBuffer(data: KPointer, length: bigint, resourceId: int32, hold: KPointer, release: KPointer): ArrayBuffer { throw "method not loaded" }
    public static _GetNativeBufferPointer(data: ArrayBuffer): KPointer { throw "method not loaded" }

    public static _LoadVirtualMachine(arg0: int32, arg1: string, arg2: string, arg3: string): int32 { throw "method not loaded" }
    public static _RunApplication(arg0: int32, arg1: int32): number { throw "method not loaded" }
    public static _StartApplication(appUrl: string, appParams: string): KPointer { throw "method not loaded" }
    public static _EmitEvent(eventType: int32, target: int32, arg0: int32, arg1: int32): string { throw "method not loaded" }
    public static _CallForeignVM(foreignContext: KPointer, kind: int32, args: KSerializerBuffer, argsSize: int32): int32 { throw "method not loaded" }
    public static _SetForeignVMContext(context: KPointer): void { throw "method not loaded" }
    public static _Malloc(length: int64): KPointer { throw "method not loaded" }
    public static _GetMallocFinalizer(): KPointer { throw "method not loaded" }
    public static _ReadByte(data: KPointer, index: int32, length: bigint): int32 { throw "method not loaded" }
    public static _WriteByte(data: KPointer, index: int32, length: bigint, value: int32): void  { throw "method not loaded" }
    public static _CopyArray(data: KPointer, length: int64, args: KUint8ArrayPtr): void { throw "method not loaded" }
}

export function loadInteropNativeModule() {
    loadNativeModuleLibrary("InteropNativeModule", InteropNativeModule)
}