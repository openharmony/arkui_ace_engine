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

#ifndef BRIDGE_CUSTOM_H
#define BRIDGE_CUSTOM_H

#include <kotlin/kotlin-cinterop.h>

// Node
KOALA_INTEROP_DIRECT_3(CreateNode, KNativePointer, KInt, KInt, KInt)
KOALA_INTEROP_DIRECT_0(GetNodeFinalizer, KNativePointer)
KOALA_INTEROP_DIRECT_0(GetNodeByViewStack, KNativePointer)
KOALA_INTEROP_DIRECT_V1(DisposeNode, KNativePointer)
KOALA_INTEROP_DIRECT_V1(DumpTreeNode, KNativePointer)
KOALA_INTEROP_DIRECT_2(AddChild, KInt, KNativePointer, KNativePointer)
KOALA_INTEROP_DIRECT_V2(RemoveChild, KNativePointer, KNativePointer)
KOALA_INTEROP_DIRECT_3(InsertChildAfter, KInt, KNativePointer, KNativePointer, KNativePointer)
KOALA_INTEROP_DIRECT_3(InsertChildBefore, KInt, KNativePointer, KNativePointer, KNativePointer)
KOALA_INTEROP_DIRECT_3(InsertChildAt, KInt, KNativePointer, KNativePointer, KInt)
KOALA_INTEROP_DIRECT_V1(ApplyModifierFinish, KNativePointer)
KOALA_INTEROP_V2(MarkDirty, KNativePointer, KUInt)
KOALA_INTEROP_DIRECT_1(IsBuilderNode, KBoolean, KNativePointer)
KOALA_INTEROP_DIRECT_3(ConvertLengthMetricsUnit, KFloat, KFloat, KInt, KInt)
KOALA_INTEROP_CTX_V2(SetCustomCallback, KNativePointer, KInt)
KOALA_INTEROP_CTX_V1(MeasureLayoutAndDraw, KNativePointer)
KOALA_INTEROP_CTX_2(MeasureNode, KInt, KNativePointer, KFloatArray)
KOALA_INTEROP_CTX_2(LayoutNode, KInt, KNativePointer, KFloatArray)
KOALA_INTEROP_CTX_2(DrawNode, KInt, KNativePointer, KFloatArray)
KOALA_INTEROP_DIRECT_V2(SetMeasureWidth, KNativePointer, KInt)
KOALA_INTEROP_DIRECT_1(GetMeasureWidth, KInt, KNativePointer)
KOALA_INTEROP_DIRECT_V2(SetMeasureHeight, KNativePointer, KInt)
KOALA_INTEROP_DIRECT_1(GetMeasureHeight, KInt, KNativePointer)
KOALA_INTEROP_DIRECT_V2(SetX, KNativePointer, KInt)
KOALA_INTEROP_DIRECT_1(GetX, KInt, KNativePointer)
KOALA_INTEROP_DIRECT_V2(SetY, KNativePointer, KInt)
KOALA_INTEROP_DIRECT_1(GetY, KInt, KNativePointer)
KOALA_INTEROP_DIRECT_V2(SetAlignment, KNativePointer, KInt)
KOALA_INTEROP_DIRECT_1(GetAlignment, KInt, KNativePointer)
KOALA_INTEROP_CTX_1(IndexerChecker, KInt, KNativePointer)
KOALA_INTEROP_DIRECT_V2(SetRangeUpdater, KNativePointer, KInt)
KOALA_INTEROP_CTX_V2(SetLazyItemIndexer, KNativePointer, KInt)
KOALA_INTEROP_DIRECT_1(GetPipelineContext, KNativePointer, KNativePointer)
KOALA_INTEROP_CTX_1(VSyncAwait, KNativePointer, KNativePointer)
KOALA_INTEROP_DIRECT_V1(SetVsyncCallback, KNativePointer)
KOALA_INTEROP_V1(UnblockVsyncWait, KNativePointer)
KOALA_INTEROP_DIRECT_V2(SetChildTotalCount, KNativePointer, KInt)
KOALA_INTEROP_V1(ShowCrash, KStringPtr)
KOALA_INTEROP_V1(StartPerf, KStringPtr)
KOALA_INTEROP_V1(EndPerf, KStringPtr)
KOALA_INTEROP_1(DumpPerf, KNativePointer, KInt)
KOALA_INTEROP_DIRECT_2(CheckCallbackEvent, KInt, KSerializerBuffer, KInt)
KOALA_INTEROP_V1(HoldCallbackResource, KInt)
KOALA_INTEROP_V1(ReleaseCallbackResource, KInt)

// Test
KOALA_INTEROP_CTX_1(TestCallIntNoArgs, KInt, KInt)
KOALA_INTEROP_CTX_3(TestCallIntIntArraySum, KInt, KInt, KInt*, KInt)
KOALA_INTEROP_CTX_V3(TestCallVoidIntArrayPrefixSum, KInt, KInt*, KInt)
KOALA_INTEROP_CTX_3(TestCallIntRecursiveCallback, KInt, KInt, KSerializerBuffer, KInt)
KOALA_INTEROP_CTX_2(TestCallIntMemory, KInt, KInt, KInt)
KOALA_INTEROP_V1(TestWithBuffer, KInteropBuffer)
KOALA_INTEROP_1(TestGetManagedCaller, KNativePointer, KInt)
KOALA_INTEROP_1(TestGetManagedCallerSync, KNativePointer, KInt)
KOALA_INTEROP_0(TestGetManagedHolder, KNativePointer)
KOALA_INTEROP_0(TestGetManagedReleaser, KNativePointer)
KOALA_INTEROP_V2(TestReadAndMutateManagedBuffer, KByte*, KInt)

%CUSTOM_API%

#endif /* BRIDGE_CUSTOM_H */
