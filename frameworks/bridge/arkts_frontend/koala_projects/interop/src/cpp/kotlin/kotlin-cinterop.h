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

// This header is intended to be used only in Kotlin Native cinterop headers.
// Do not include it elsewhere.

#ifndef _KOTLIN_CINTEROP_H
#define _KOTLIN_CINTEROP_H

#include <stdint.h>

struct KotlinInteropBuffer {
    int32_t length;
    void *data;
};

// All type aliases below are defined using macros so as not to collide with their Kotlin counterparts.
#define KInteropReturnBuffer struct KotlinInteropBuffer
#define KInteropBuffer struct KotlinInteropBuffer

#define KBoolean int8_t
#define KByte uint8_t
#define KShort int16_t
#define KUShort uint16_t
#define KInt int32_t
#define KUInt uint32_t
#define KLong int64_t
#define KULong uint64_t
#define KFloat float
#define KDouble double
#define KInteropNumber double
#define KStringPtr const char *
#define KSerializerBuffer void *
#define KNativePointer void *
#define KByteArray uint8_t *
#define KIntArray int32_t *
#define KFloatArray float *

#define KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, ...) \
    Ret kotlin_##name(__VA_ARGS__);

#define KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, ...) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, void, __VA_ARGS__)

// NORMAL
#define KOALA_INTEROP_0(name, Ret) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret)
#define KOALA_INTEROP_1(name, Ret, P0) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0)
#define KOALA_INTEROP_2(name, Ret, P0, P1) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0, P1)
#define KOALA_INTEROP_3(name, Ret, P0, P1, P2) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0, P1, P2)
#define KOALA_INTEROP_4(name, Ret, P0, P1, P2, P3) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0, P1, P2, P3)
#define KOALA_INTEROP_5(name, Ret, P0, P1, P2, P3, P4) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0, P1, P2, P3, P4)
#define KOALA_INTEROP_6(name, Ret, P0, P1, P2, P3, P4, P5) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0, P1, P2, P3, P4, P5)
#define KOALA_INTEROP_7(name, Ret, P0, P1, P2, P3, P4, P5, P6) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0, P1, P2, P3, P4, P5, P6)
#define KOALA_INTEROP_8(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7)
#define KOALA_INTEROP_9(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8)
#define KOALA_INTEROP_10(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)
#define KOALA_INTEROP_11(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
    KOALA_INTEROP_FUNCTION_DECLARATION(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)
#define KOALA_INTEROP_V0(name) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name)
#define KOALA_INTEROP_V1(name, P0) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0)
#define KOALA_INTEROP_V2(name, P0, P1) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0, P1)
#define KOALA_INTEROP_V3(name, P0, P1, P2) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0, P1, P2)
#define KOALA_INTEROP_V4(name, P0, P1, P2, P3) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0, P1, P2, P3)
#define KOALA_INTEROP_V5(name, P0, P1, P2, P3, P4) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0, P1, P2, P3, P4)
#define KOALA_INTEROP_V6(name, P0, P1, P2, P3, P4, P5) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0, P1, P2, P3, P4, P5)
#define KOALA_INTEROP_V7(name, P0, P1, P2, P3, P4, P5, P6) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0, P1, P2, P3, P4, P5, P6)
#define KOALA_INTEROP_V8(name, P0, P1, P2, P3, P4, P5, P6, P7) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0, P1, P2, P3, P4, P5, P6, P7)
#define KOALA_INTEROP_V9(name, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0, P1, P2, P3, P4, P5, P6, P7, P8)
#define KOALA_INTEROP_V10(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)
#define KOALA_INTEROP_V11(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
    KOALA_INTEROP_VOID_FUNCTION_DECLARATION(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)

// CTX
#define KOALA_INTEROP_CTX_0(name, Ret) \
    KOALA_INTEROP_0(name, Ret)
#define KOALA_INTEROP_CTX_1(name, Ret, P0) \
    KOALA_INTEROP_1(name, Ret, P0)
#define KOALA_INTEROP_CTX_2(name, Ret, P0, P1) \
    KOALA_INTEROP_2(name, Ret, P0, P1)
#define KOALA_INTEROP_CTX_3(name, Ret, P0, P1, P2) \
    KOALA_INTEROP_3(name, Ret, P0, P1, P2)
#define KOALA_INTEROP_CTX_4(name, Ret, P0, P1, P2, P3) \
    KOALA_INTEROP_4(name, Ret, P0, P1, P2, P3)
#define KOALA_INTEROP_CTX_5(name, Ret, P0, P1, P2, P3, P4) \
    KOALA_INTEROP_5(name, Ret, P0, P1, P2, P3, P4)
#define KOALA_INTEROP_CTX_V0(name) \
    KOALA_INTEROP_V0(name)
#define KOALA_INTEROP_CTX_V1(name, P0) \
    KOALA_INTEROP_V1(name, P0)
#define KOALA_INTEROP_CTX_V2(name, P0, P1) \
    KOALA_INTEROP_V2(name, P0, P1)
#define KOALA_INTEROP_CTX_V3(name, P0, P1, P2) \
    KOALA_INTEROP_V3(name, P0, P1, P2)
#define KOALA_INTEROP_CTX_V4(name, P0, P1, P2, P3) \
    KOALA_INTEROP_V4(name, P0, P1, P2, P3)
#define KOALA_INTEROP_CTX_V5(name, P0, P1, P2, P3, P4) \
    KOALA_INTEROP_V5(name, P0, P1, P2, P3, P4)

// DIRECT
#define KOALA_INTEROP_DIRECT_0(name, Ret) \
    KOALA_INTEROP_0(name, Ret)
#define KOALA_INTEROP_DIRECT_1(name, Ret, P0) \
    KOALA_INTEROP_1(name, Ret, P0)
#define KOALA_INTEROP_DIRECT_2(name, Ret, P0, P1) \
    KOALA_INTEROP_2(name, Ret, P0, P1)
#define KOALA_INTEROP_DIRECT_3(name, Ret, P0, P1, P2) \
    KOALA_INTEROP_3(name, Ret, P0, P1, P2)
#define KOALA_INTEROP_DIRECT_4(name, Ret, P0, P1, P2, P3) \
    KOALA_INTEROP_4(name, Ret, P0, P1, P2, P3)
#define KOALA_INTEROP_DIRECT_5(name, Ret, P0, P1, P2, P3, P4) \
    KOALA_INTEROP_5(name, Ret, P0, P1, P2, P3, P4)
#define KOALA_INTEROP_DIRECT_6(name, Ret, P0, P1, P2, P3, P4, P5) \
    KOALA_INTEROP_6(name, Ret, P0, P1, P2, P3, P4, P5)
#define KOALA_INTEROP_DIRECT_7(name, Ret, P0, P1, P2, P3, P4, P5, P6) \
    KOALA_INTEROP_7(name, Ret, P0, P1, P2, P3, P4, P5, P6)
#define KOALA_INTEROP_DIRECT_8(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7) \
    KOALA_INTEROP_8(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7)
#define KOALA_INTEROP_DIRECT_9(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
    KOALA_INTEROP_9(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8)
#define KOALA_INTEROP_DIRECT_10(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
    KOALA_INTEROP_10(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)
#define KOALA_INTEROP_DIRECT_11(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
    KOALA_INTEROP_11(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)
#define KOALA_INTEROP_DIRECT_V0(name) \
    KOALA_INTEROP_V0(name)
#define KOALA_INTEROP_DIRECT_V1(name, P0) \
    KOALA_INTEROP_V1(name, P0)
#define KOALA_INTEROP_DIRECT_V2(name, P0, P1) \
    KOALA_INTEROP_V2(name, P0, P1)
#define KOALA_INTEROP_DIRECT_V3(name, P0, P1, P2) \
    KOALA_INTEROP_V3(name, P0, P1, P2)
#define KOALA_INTEROP_DIRECT_V4(name, P0, P1, P2, P3) \
    KOALA_INTEROP_V4(name, P0, P1, P2, P3)
#define KOALA_INTEROP_DIRECT_V5(name, P0, P1, P2, P3, P4) \
    KOALA_INTEROP_V5(name, P0, P1, P2, P3, P4)
#define KOALA_INTEROP_DIRECT_V6(name, P0, P1, P2, P3, P4, P5) \
    KOALA_INTEROP_V6(name, P0, P1, P2, P3, P4, P5)
#define KOALA_INTEROP_DIRECT_V7(name, P0, P1, P2, P3, P4, P5, P6) \
    KOALA_INTEROP_V7(name, P0, P1, P2, P3, P4, P5, P6)
#define KOALA_INTEROP_DIRECT_V8(name, P0, P1, P2, P3, P4, P5, P6, P7) \
    KOALA_INTEROP_V8(name, P0, P1, P2, P3, P4, P5, P6, P7)
#define KOALA_INTEROP_DIRECT_V9(name, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
    KOALA_INTEROP_V9(name, P0, P1, P2, P3, P4, P5, P6, P7, P8)
#define KOALA_INTEROP_DIRECT_V10(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
    KOALA_INTEROP_V10(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)
#define KOALA_INTEROP_DIRECT_V11(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
    KOALA_INTEROP_V11(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)

#endif /* _KOTLIN_CINTEROP_H */
