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

export class ArkUINativeModule {
    static {
        loadNativeModuleLibrary("ArkUINativeModule")
    }
    native static _CreateNode(node_t: int32, arg0: int32, arg1: int32): KPointer 
    native static _GetNodeFinalizer(): KPointer 
    native static _GetNodeByViewStack(): KPointer 
    native static _DisposeNode(ptr0: KPointer): void 
    native static _DumpTreeNode(ptr0: KPointer): void 
    native static _AddChild(ptr1: KPointer, ptr2: KPointer): int32 
    native static _RemoveChild(ptr0: KPointer, ptr2: KPointer): void 
    native static _InsertChildAfter(ptr0: KPointer, ptr1: KPointer, ptr2: KPointer): int32 
    native static _InsertChildBefore(ptr0: KPointer, ptr1: KPointer, ptr2: KPointer): int32 
    native static _InsertChildAt(ptr0: KPointer, ptr1: KPointer, arg: int32): int32 
    native static _ApplyModifierFinish(ptr0: KPointer): void 
    native static _MarkDirty(ptr0: KPointer, arg: int32): void 
    native static _IsBuilderNode(ptr0: KPointer): boolean 
    native static _ConvertLengthMetricsUnit(arg0: float32, arg1: int32, arg2: int32): float32 
    native static _SetCustomCallback(ptr0: KPointer, arg: int32): void 
    native static _MeasureLayoutAndDraw(ptr0: KPointer): void 
    native static _MeasureNode(ptr0: KPointer, arr: KFloat32ArrayPtr): int32 
    native static _LayoutNode(ptr0: KPointer, arr: KFloat32ArrayPtr): int32 
    native static _DrawNode(ptr0: KPointer, arr: KFloat32ArrayPtr): int32 
    native static _SetMeasureWidth(ptr0: KPointer, arg: int32): void 
    native static _GetMeasureWidth(ptr0: KPointer): int32 
    native static _SetMeasureHeight(ptr0: KPointer, arg: int32): void 
    native static _GetMeasureHeight(ptr0: KPointer): int32 
    native static _SetX(ptr0: KPointer, arg: int32): void 
    native static _GetX(ptr0: KPointer): int32 
    native static _SetY(ptr0: KPointer, arg: int32): void 
    native static _GetY(ptr0: KPointer): int32 
    native static _SetAlignment(ptr0: KPointer, arg: int32): void 
    native static _GetAlignment(ptr0: KPointer): int32 
    native static _IndexerChecker(ptr0: KPointer): int32 
    native static _SetRangeUpdater(ptr0: KPointer, arg: int32): void 
    native static _SetLazyItemIndexer(ptr0: KPointer, arg: int32): void 
    native static _GetPipelineContext(ptr0: KPointer): KPointer 
    native static _VSyncAwait(pipeline: KPointer): Object 
    native static _SetVsyncCallback(pipeline: KPointer): void 
    native static _UnblockVsyncWait(pipeline: KPointer): void 
    native static _SetChildTotalCount(ptr0: KPointer, arg: int32): void 
    native static _ShowCrash(message: string): void 
    native static _CheckArkoalaGeneratedEvents(result: KUint8ArrayPtr, size: int32): int32 
    native static _InjectEvent(data: KUint8ArrayPtr, size: int32): int32 
    native static _StartPerf(str1: string): void 
    native static _EndPerf(str1: string): void 
    native static _DumpPerf(arg: int32): KPointer 
    native static _CheckCallbackEvent(buffer: KUint8ArrayPtr, bufferLength: int32): int32 
    native static _HoldCallbackResource(resourceId: int32): void 
    native static _ReleaseCallbackResource(resourceId: int32): void 
    native static _LoadUserView(userClass: string, params: string): Object 
}
