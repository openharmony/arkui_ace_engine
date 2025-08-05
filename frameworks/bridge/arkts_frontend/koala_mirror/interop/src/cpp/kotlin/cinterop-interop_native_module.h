/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef CINTEROP_INTEROP_NATIVE_MODULE_H
#define CINTEROP_INTEROP_NATIVE_MODULE_H

// This header is intended to be used only in Kotlin Native cinterop headers.
// Do not include it elsewhere.

#include "kotlin-cinterop.h"

KOALA_INTEROP_1(GetGroupedLog, KNativePointer, KInt)
KOALA_INTEROP_V1(StartGroupedLog, KInt)
KOALA_INTEROP_V1(StopGroupedLog, KInt)
KOALA_INTEROP_V2(AppendGroupedLog, KInt, KStringPtr)
KOALA_INTEROP_V1(PrintGroupedLog, KInt)
KOALA_INTEROP_0(GetStringFinalizer, KNativePointer)
KOALA_INTEROP_V2(InvokeFinalizer, KNativePointer, KNativePointer)
KOALA_INTEROP_1(IncrementNumber, KInteropNumber, KInteropNumber)
KOALA_INTEROP_2(GetPtrVectorElement, KNativePointer, KNativePointer, KInt)
KOALA_INTEROP_1(StringLength, KInt, KNativePointer)
KOALA_INTEROP_V3(StringData, KNativePointer, KByte*, KInt)
KOALA_INTEROP_1(StringMake, KNativePointer, KStringPtr)
KOALA_INTEROP_1(GetPtrVectorSize, KInt, KNativePointer)
KOALA_INTEROP_4(ManagedStringWrite, KInt, KStringPtr, KSerializerBuffer, KInt, KInt)
KOALA_INTEROP_V1(NativeLog, KStringPtr)
KOALA_INTEROP_CTX_3(Utf8ToString, KStringPtr, KNativePointer, KInt, KInt)
KOALA_INTEROP_CTX_1(StdStringToString, KStringPtr, KNativePointer)
KOALA_INTEROP_DIRECT_2(CheckCallbackEvent, KInt, KSerializerBuffer, KInt)
KOALA_INTEROP_V1(ReleaseCallbackResource, KInt)
KOALA_INTEROP_V1(HoldCallbackResource, KInt)
KOALA_INTEROP_V3(CallCallback, KInt, KSerializerBuffer, KInt)
KOALA_INTEROP_CTX_V3(CallCallbackSync, KInt, KSerializerBuffer, KInt)
KOALA_INTEROP_V2(CallCallbackResourceHolder, KNativePointer, KInt)
KOALA_INTEROP_V2(CallCallbackResourceReleaser, KNativePointer, KInt)
KOALA_INTEROP_CTX_4(LoadVirtualMachine, KInt, KInt, KStringPtr, KStringPtr, KStringPtr)
KOALA_INTEROP_2(RunApplication, KBoolean, KInt, KInt)
KOALA_INTEROP_2(StartApplication, KNativePointer, KStringPtr, KStringPtr)
KOALA_INTEROP_CTX_4(EmitEvent, KStringPtr, KInt, KInt, KInt, KInt)
KOALA_INTEROP_4(CallForeignVM, KInt, KNativePointer, KInt, KSerializerBuffer, KInt)
KOALA_INTEROP_V1(SetForeignVMContext, KNativePointer)
KOALA_INTEROP_V1(RestartWith, KStringPtr)
KOALA_INTEROP_DIRECT_3(ReadByte, KInt, KNativePointer, KLong, KLong)
KOALA_INTEROP_DIRECT_V4(WriteByte, KNativePointer, KLong, KLong, KInt)
KOALA_INTEROP_DIRECT_1(Malloc, KNativePointer, KLong)
KOALA_INTEROP_DIRECT_0(GetMallocFinalizer, KNativePointer)
KOALA_INTEROP_DIRECT_V1(Free, KNativePointer)
KOALA_INTEROP_V3(CopyArray, KNativePointer, KLong, KByte*)
KOALA_INTEROP_V0(ReportMemLeaks)

KOALA_INTEROP_V1(SetKoalaKotlinCallbackDispatcher, KNativePointer)

#endif  // CINTEROP_INTEROP_NATIVE_MODULE_H
