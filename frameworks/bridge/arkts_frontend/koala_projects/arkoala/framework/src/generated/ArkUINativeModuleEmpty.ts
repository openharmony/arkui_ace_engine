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

import { KInt, KLong, KBoolean, KFloat, KUInt, KStringPtr, KPointer, KNativePointer, KInt32ArrayPtr, KUint8ArrayPtr, KFloat32ArrayPtr, pointer, KInteropReturnBuffer } from "@koalaui/interop"
import { int32, float32 } from "@koalaui/common"

export class ArkUINativeModuleEmpty {
    _CreateNode(node_t: int32, arg0: int32, arg1: int32): KPointer {
        console.log("_CreateNode")
        return -1
    }
    _GetNodeFinalizer(): KPointer {
        console.log("_GetNodeFinalizer")
        return -1
    }
    _GetNodeByViewStack(): KPointer {
        console.log("_GetNodeByViewStack")
        return -1
    }
    _DisposeNode(ptr0: KPointer): void {
        console.log("_DisposeNode")
    }
    _DumpTreeNode(ptr0: KPointer): void {
        console.log("_DumpTreeNode")
    }
    _AddChild(ptr1: KPointer, ptr2: KPointer): int32 {
        console.log("_AddChild")
        return 0
    }
    _RemoveChild(ptr0: KPointer, ptr2: KPointer): void {
        console.log("_RemoveChild")
    }
    _InsertChildAfter(ptr0: KPointer, ptr1: KPointer, ptr2: KPointer): int32 {
        console.log("_InsertChildAfter")
        return 0
    }
    _InsertChildBefore(ptr0: KPointer, ptr1: KPointer, ptr2: KPointer): int32 {
        console.log("_InsertChildBefore")
        return 0
    }
    _InsertChildAt(ptr0: KPointer, ptr1: KPointer, arg: int32): int32 {
        console.log("_InsertChildAt")
        return 0
    }
    _ApplyModifierFinish(ptr0: KPointer): void {
        console.log("_ApplyModifierFinish")
    }
    _MarkDirty(ptr0: KPointer, arg: number): void {
        console.log("_MarkDirty")
    }
    _IsBuilderNode(ptr0: KPointer): number {
        console.log("_IsBuilderNode")
        return 1
    }
    _ConvertLengthMetricsUnit(arg0: float32, arg1: int32, arg2: int32): float32 {
        console.log("_ConvertLengthMetricsUnit")
        return 0
    }
    _SetCustomCallback(ptr0: KPointer, arg: int32): void {
        console.log("_SetCustomCallback")
    }
    _MeasureLayoutAndDraw(ptr0: KPointer): void {
        console.log("_MeasureLayoutAndDraw")
    }
    _MeasureNode(ptr0: KPointer, arr: KFloat32ArrayPtr): int32 {
        console.log("_MeasureNode")
        return 0
    }
    _LayoutNode(ptr0: KPointer, arr: KFloat32ArrayPtr): int32 {
        console.log("_LayoutNode")
        return 0
    }
    _DrawNode(ptr0: KPointer, arr: KFloat32ArrayPtr): int32 {
        console.log("_DrawNode")
        return 0
    }
    _SetMeasureWidth(ptr0: KPointer, arg: int32): void {
        console.log("_SetMeasureWidth")
    }
    _GetMeasureWidth(ptr0: KPointer): int32 {
        console.log("_GetMeasureWidth")
        return 0
    }
    _SetMeasureHeight(ptr0: KPointer, arg: int32): void {
        console.log("_SetMeasureHeight")
    }
    _GetMeasureHeight(ptr0: KPointer): int32 {
        console.log("_GetMeasureHeight")
        return 0
    }
    _SetX(ptr0: KPointer, arg: int32): void {
        console.log("_SetX")
    }
    _GetX(ptr0: KPointer): int32 {
        console.log("_GetX")
        return 0
    }
    _SetY(ptr0: KPointer, arg: int32): void {
        console.log("_SetY")
    }
    _GetY(ptr0: KPointer): int32 {
        console.log("_GetY")
        return 0
    }
    _SetAlignment(ptr0: KPointer, arg: int32): void {
        console.log("_SetAlignment")
    }
    _GetAlignment(ptr0: KPointer): int32 {
        console.log("_GetAlignment")
        return 0
    }
    _IndexerChecker(ptr0: KPointer): int32 {
        console.log("_IndexerChecker")
        return 0
    }
    _SetRangeUpdater(ptr0: KPointer, arg: int32): void {
        console.log("_SetRangeUpdater")
    }
    _SetLazyItemIndexer(ptr0: KPointer, arg: int32): void {
        console.log("_SetLazyItemIndexer")
    }
    _GetPipelineContext(ptr0: KPointer): KPointer {
        console.log("_GetPipelineContext")
        return -1
    }
    _VSyncAwait(pipeline: KPointer): Object {
        console.log("_VSyncAwait")
        return new Object()
    }
    _SetVsyncCallback(pipeline: KPointer): void {
        console.log("_SetVsyncCallback")
    }
    _UnblockVsyncWait(pipeline: KPointer): void {
        console.log("_UnblockVsyncWait")
    }
    _SetChildTotalCount(ptr0: KPointer, arg: int32): void {
        console.log("_SetChildTotalCount")
    }
    _ShowCrash(message: string): void {
        console.log("_ShowCrash")
    }
    _StartPerf(str1: string): void {
        console.log("_StartPerf")
    }
    _EndPerf(str1: string): void {
        console.log("_EndPerf")
    }
    _DumpPerf(arg: int32): KPointer {
        console.log("_DumpPerf")
        return -1
    }
    _CheckCallbackEvent(buffer: Uint8Array, bufferLength: int32): int32 {
        console.log("_CheckCallbackEvent")
        return 0
    }
    _HoldCallbackResource(resourceId: int32): void {
        console.log("_HoldCallbackResource")
    }
    _ReleaseCallbackResource(resourceId: int32): void {
        console.log("_ReleaseCallbackResource")
    }
    _LoadUserView(userClass: string, params: string): Object {
        console.log("_LoadUserView")
        return new Object()
    }
}