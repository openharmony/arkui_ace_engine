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

import { KInt, KLong, KBoolean, KFloat, KUInt, KStringPtr, KPointer, KNativePointer, KInt32ArrayPtr, KUint8ArrayPtr, KFloat32ArrayPtr, pointer, KInteropReturnBuffer, KSerializerBuffer, loadNativeModuleLibrary, NativeBuffer, withByteArray, Access, callCallback, nullptr, InteropNativeModule, providePlatformDefinedData, NativeStringBase, ArrayDecoder, CallbackRegistry } from "@koalaui/interop"
import { int32, int64, float32 } from "@koalaui/common"

export class ArkUINativeModule {
    private static _isLoaded: boolean = false
    private static _LoadOnce(): boolean {
        if ((this._isLoaded) == (false))
        {
            this._isLoaded = true
            loadNativeModuleLibrary("ArkUINativeModule", ArkUINativeModule)
            return true
        }
        return false
    }
    static _CreateNode(node_t: int32, arg0: int32, arg1: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._CreateNode(node_t, arg0, arg1)
        }
        throw new Error("Not implemented")
    }
    static _GetNodeFinalizer(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GetNodeFinalizer()
        }
        throw new Error("Not implemented")
    }
    static _GetNodeByViewStack(): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GetNodeByViewStack()
        }
        throw new Error("Not implemented")
    }
    static _DisposeNode(ptr0: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DisposeNode(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _DumpTreeNode(ptr0: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._DumpTreeNode(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _AddChild(ptr1: KPointer, ptr2: KPointer): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._AddChild(ptr1, ptr2)
        }
        throw new Error("Not implemented")
    }
    static _RemoveChild(ptr0: KPointer, ptr2: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._RemoveChild(ptr0, ptr2)
        }
        throw new Error("Not implemented")
    }
    static _InsertChildAfter(ptr0: KPointer, ptr1: KPointer, ptr2: KPointer): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._InsertChildAfter(ptr0, ptr1, ptr2)
        }
        throw new Error("Not implemented")
    }
    static _InsertChildBefore(ptr0: KPointer, ptr1: KPointer, ptr2: KPointer): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._InsertChildBefore(ptr0, ptr1, ptr2)
        }
        throw new Error("Not implemented")
    }
    static _InsertChildAt(ptr0: KPointer, ptr1: KPointer, arg: int32): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._InsertChildAt(ptr0, ptr1, arg)
        }
        throw new Error("Not implemented")
    }
    static _ApplyModifierFinish(ptr0: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ApplyModifierFinish(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _MarkDirty(ptr0: KPointer, arg: number): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MarkDirty(ptr0, arg)
        }
        throw new Error("Not implemented")
    }
    static _IsBuilderNode(ptr0: KPointer): number {
        if ((this._LoadOnce()) == (true))
        {
            return this._IsBuilderNode(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _ConvertLengthMetricsUnit(arg0: float32, arg1: int32, arg2: int32): float32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._ConvertLengthMetricsUnit(arg0, arg1, arg2)
        }
        throw new Error("Not implemented")
    }
    static _SetCustomCallback(ptr0: KPointer, arg: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SetCustomCallback(ptr0, arg)
        }
        throw new Error("Not implemented")
    }
    static _MeasureLayoutAndDraw(ptr0: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._MeasureLayoutAndDraw(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _MeasureNode(ptr0: KPointer, arr: KFloat32ArrayPtr): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._MeasureNode(ptr0, arr)
        }
        throw new Error("Not implemented")
    }
    static _LayoutNode(ptr0: KPointer, arr: KFloat32ArrayPtr): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._LayoutNode(ptr0, arr)
        }
        throw new Error("Not implemented")
    }
    static _DrawNode(ptr0: KPointer, arr: KFloat32ArrayPtr): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._DrawNode(ptr0, arr)
        }
        throw new Error("Not implemented")
    }
    static _SetMeasureWidth(ptr0: KPointer, arg: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SetMeasureWidth(ptr0, arg)
        }
        throw new Error("Not implemented")
    }
    static _GetMeasureWidth(ptr0: KPointer): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._GetMeasureWidth(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _SetMeasureHeight(ptr0: KPointer, arg: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SetMeasureHeight(ptr0, arg)
        }
        throw new Error("Not implemented")
    }
    static _GetMeasureHeight(ptr0: KPointer): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._GetMeasureHeight(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _SetX(ptr0: KPointer, arg: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SetX(ptr0, arg)
        }
        throw new Error("Not implemented")
    }
    static _GetX(ptr0: KPointer): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._GetX(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _SetY(ptr0: KPointer, arg: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SetY(ptr0, arg)
        }
        throw new Error("Not implemented")
    }
    static _GetY(ptr0: KPointer): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._GetY(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _SetAlignment(ptr0: KPointer, arg: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SetAlignment(ptr0, arg)
        }
        throw new Error("Not implemented")
    }
    static _GetAlignment(ptr0: KPointer): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._GetAlignment(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _IndexerChecker(ptr0: KPointer): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._IndexerChecker(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _SetRangeUpdater(ptr0: KPointer, arg: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SetRangeUpdater(ptr0, arg)
        }
        throw new Error("Not implemented")
    }
    static _SetLazyItemIndexer(ptr0: KPointer, arg: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SetLazyItemIndexer(ptr0, arg)
        }
        throw new Error("Not implemented")
    }
    static _GetPipelineContext(ptr0: KPointer): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._GetPipelineContext(ptr0)
        }
        throw new Error("Not implemented")
    }
    static _VSyncAwait(pipeline: KPointer): Object {
        if ((this._LoadOnce()) == (true))
        {
            return this._VSyncAwait(pipeline)
        }
        throw new Error("Not implemented")
    }
    static _SetVsyncCallback(pipeline: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SetVsyncCallback(pipeline)
        }
        throw new Error("Not implemented")
    }
    static _UnblockVsyncWait(pipeline: KPointer): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._UnblockVsyncWait(pipeline)
        }
        throw new Error("Not implemented")
    }
    static _SetChildTotalCount(ptr0: KPointer, arg: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._SetChildTotalCount(ptr0, arg)
        }
        throw new Error("Not implemented")
    }
    static _ShowCrash(message: string): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ShowCrash(message)
        }
        throw new Error("Not implemented")
    }
    static _StartPerf(str1: string): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._StartPerf(str1)
        }
        throw new Error("Not implemented")
    }
    static _EndPerf(str1: string): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._EndPerf(str1)
        }
        throw new Error("Not implemented")
    }
    static _DumpPerf(arg: int32): KPointer {
        if ((this._LoadOnce()) == (true))
        {
            return this._DumpPerf(arg)
        }
        throw new Error("Not implemented")
    }
    static _CheckCallbackEvent(buffer: KSerializerBuffer, bufferLength: int32): int32 {
        if ((this._LoadOnce()) == (true))
        {
            return this._CheckCallbackEvent(buffer, bufferLength)
        }
        throw new Error("Not implemented")
    }
    static _HoldCallbackResource(resourceId: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._HoldCallbackResource(resourceId)
        }
        throw new Error("Not implemented")
    }
    static _ReleaseCallbackResource(resourceId: int32): void {
        if ((this._LoadOnce()) == (true))
        {
            return this._ReleaseCallbackResource(resourceId)
        }
        throw new Error("Not implemented")
    }
    static _LoadUserView(userClass: string, params: string): Object {
        if ((this._LoadOnce()) == (true))
        {
            return this._LoadUserView(userClass, params)
        }
        throw new Error("Not implemented")
    }
}
class NativeString extends NativeStringBase {
    constructor(ptr: KPointer) {
        super(ptr)
    }
    protected bytesLength(): int32 {
        return InteropNativeModule._StringLength(this.ptr)
    }
    protected getData(data: Uint8Array): void {
        withByteArray(data, Access.WRITE, (dataPtr: KUint8ArrayPtr) => {
            InteropNativeModule._StringData(this.ptr, dataPtr, data.length)
        })
    }
    close(): void {
        InteropNativeModule._InvokeFinalizer(this.ptr, InteropNativeModule._GetStringFinalizer())
        this.ptr = nullptr
    }
}

providePlatformDefinedData({
    nativeString(ptr: KPointer): NativeStringBase { return new NativeString(ptr) },
    nativeStringArrayDecoder(): ArrayDecoder<NativeStringBase> { throw new Error("Not implemented") },
    callbackRegistry(): CallbackRegistry | undefined { return undefined }
})
