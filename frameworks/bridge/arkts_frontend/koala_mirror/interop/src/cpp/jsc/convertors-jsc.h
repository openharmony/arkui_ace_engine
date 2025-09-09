/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef CONVERTORS_JSC_H
#define CONVERTORS_JSC_H

#if defined(linux)
#include <JavaScriptCore/JavaScript.h> // For IDE completion
#else
#include <JavaScriptCore/JavaScriptCore.h>
#endif
#include <_types/_uint8_t.h>
#include <vector>
#include <string>
#include <iostream>

#include "koala-types.h"
#include "interop-logging.h"

template <typename ElemType>
inline ElemType* getTypedElements(JSContextRef context, const JSValueRef arguments) {
  if (JSValueIsNull(context, arguments)) {
      return nullptr;
  }
  if (JSValueIsUndefined(context, arguments)) {
      ASSERT(false);
      return nullptr;
  }
  JSValueRef exception {};
  ElemType* data = reinterpret_cast<ElemType*>(JSObjectGetTypedArrayBytesPtr(context,
        JSValueToObject(context, arguments, &exception), &exception));
  return data;
}

template <typename ElemType>
inline ElemType* getTypedElements(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getTypedElements<ElemType>(context, arguments[index]);
}

uint8_t* getUInt8Elements(JSContextRef context, const JSValueRef arguments);
int32_t* getInt32Elements(JSContextRef context, const JSValueRef arguments);
uint32_t* getUInt32Elements(JSContextRef context, const JSValueRef arguments);
float* getFloat32Elements(JSContextRef context, const JSValueRef arguments);
KByte* getByteElements(JSContextRef context, const JSValueRef arguments);
KUShort* getUShortElements(JSContextRef context, const JSValueRef arguments);
KShort* getShortElements(JSContextRef context, const JSValueRef arguments);
KNativePointerArray getPointerElements(JSContextRef context, const JSValueRef arguments);
KStringArray getKStringArray(JSContextRef context, const JSValueRef arguments);

uint8_t getUInt8(JSContextRef context, JSValueRef value);
int32_t getInt32(JSContextRef context, JSValueRef value);
uint32_t getUInt32(JSContextRef context, JSValueRef value);
KNativePointer getPointer(JSContextRef context, JSValueRef value);
KFloat getFloat(JSContextRef context, JSValueRef value);
KStringPtr getString(JSContextRef context, JSValueRef value);
KBoolean getBoolean(JSContextRef context, JSValueRef value);
KStringPtr getString(JSContextRef context, JSValueRef value);

template <typename Type>
inline Type getArgument(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) = delete;

template <>
inline int32_t getArgument<int32_t>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getInt32(context, arguments[index]);
}

template <>
inline uint32_t getArgument<uint32_t>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getUInt32(context, arguments[index]);
}

template <>
inline uint8_t getArgument<uint8_t>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getUInt8(context, arguments[index]);
}

template <>
inline KNativePointer getArgument<KNativePointer>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getPointer(context, arguments[index]);
}

template <>
inline KFloat getArgument<KFloat>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getFloat(context, arguments[index]);
}

template <>
inline KStringPtr getArgument<KStringPtr>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getString(context, arguments[index]);
}

template <>
inline KBoolean getArgument<KBoolean>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getBoolean(context, arguments[index]);
}

template <>
inline KInt* getArgument<KInt*>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getInt32Elements(context, arguments[index]);
}

template <>
inline float* getArgument<float*>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getFloat32Elements(context, arguments[index]);
}

template <>
inline KByte* getArgument<KByte*>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getByteElements(context, arguments[index]);
}

template <>
inline KStringArray getArgument<KStringArray>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getKStringArray(context, arguments[index]);
}

template <>
inline KUShort* getArgument<KUShort*>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getUShortElements(context, arguments[index]);
}

template <>
inline KNativePointerArray getArgument<KNativePointerArray>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getPointerElements(context, arguments[index]);
}

template <>
inline KShort* getArgument<KShort*>(JSContextRef context, size_t argumentCount, const JSValueRef arguments[], int index) {
  ASSERT(index < argumentCount);
  return getShortElements(context, arguments[index]);
}

JSValueRef makeInt32(JSContextRef context, int32_t value);
JSValueRef makeUInt32(JSContextRef context, uint32_t value);
JSValueRef makePointer(JSContextRef context, KNativePointer value);
JSValueRef makeFloat(JSContextRef context, KFloat value);
JSValueRef makeBoolean(JSContextRef context, KBoolean value);
JSValueRef makeVoid(JSContextRef context);

template <typename Type>
inline JSValueRef makeResult(JSContextRef context, Type value) = delete;

template <>
inline JSValueRef makeResult<int32_t>(JSContextRef context, int32_t value) {
  return makeInt32(context, value);
}

template <>
inline JSValueRef makeResult<uint32_t>(JSContextRef context, uint32_t value) {
  return makeUInt32(context, value);
}

template <>
inline JSValueRef makeResult<KNativePointer>(JSContextRef context, KNativePointer value) {
  return makePointer(context, value);
}

template <>
inline JSValueRef makeResult<KFloat>(JSContextRef context, KFloat value) {
  return makeFloat(context, value);
}

template <>
inline JSValueRef makeResult<KBoolean>(JSContextRef context, KBoolean value) {
  return makeBoolean(context, value);
}

typedef JSValueRef (*jsc_type_t)(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);

class Exports {
    std::vector<std::pair<std::string, jsc_type_t>> implementations;

public:
    static Exports* getInstance();

    void addImpl(const char* name, jsc_type_t impl) {
        implementations.push_back(std::make_pair(name, impl));
    }

    const std::vector<std::pair<std::string, jsc_type_t>>& getImpls() {
        return implementations;
    }
};

void InitExports(JSGlobalContextRef globalContext);

#define MAKE_JSC_EXPORT(name) \
    __attribute__((constructor)) \
    static void __init_##name() { \
        Exports::getInstance()->addImpl("_"#name, Jsc_##name); \
    }

#define MAKE_JSC_EXPORT_V1(name) \
    __attribute__((constructor)) \
    static void __init_##name() { \
        Exports::getInstance()->addImpl(#name, Jsc_##name); \
    }

#define KOALA_INTEROP_0(name, Ret) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
      KOALA_MAYBE_LOG(name)                       \
      return makeResult<Ret>(ctx, impl_##name()); \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_1(name, Ret, P0) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
      KOALA_MAYBE_LOG(name)                                            \
      P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0); \
      return makeResult<Ret>(ctx, impl_##name(p0));                    \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_2(name, Ret, P0, P1) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    return makeResult<Ret>(ctx, impl_##name(p0, p1));                  \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_3(name, Ret, P0, P1, P2) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2));         \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_4(name, Ret, P0, P1, P2, P3) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3));             \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_5(name, Ret, P0, P1, P2, P3, P4) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3,p4));          \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_6(name, Ret, P0, P1, P2, P3, P4, P5) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3,p4,p5));       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_7(name, Ret, P0, P1, P2, P3, P4, P5, P6) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3,p4,p5,p6));    \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_8(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3,p4,p5,p6,p7)); \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_9(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8)); \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_10(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    P9 p9 = getArgument<P9>(ctx, argumentCount, arguments, 9);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9)); \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_11(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    P9 p9 = getArgument<P9>(ctx, argumentCount, arguments, 9);  \
    P10 p10 = getArgument<P10>(ctx, argumentCount, arguments, 10);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10)); \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_12(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    P9 p9 = getArgument<P9>(ctx, argumentCount, arguments, 9);  \
    P10 p10 = getArgument<P10>(ctx, argumentCount, arguments, 10);  \
    P11 p11 = getArgument<P11>(ctx, argumentCount, arguments, 11);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11)); \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_13(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    P9 p9 = getArgument<P9>(ctx, argumentCount, arguments, 9);  \
    P10 p10 = getArgument<P10>(ctx, argumentCount, arguments, 10);  \
    P11 p11 = getArgument<P11>(ctx, argumentCount, arguments, 11);  \
    P12 p12 = getArgument<P12>(ctx, argumentCount, arguments, 12);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12)); \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_14(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    P9 p9 = getArgument<P9>(ctx, argumentCount, arguments, 9);  \
    P10 p10 = getArgument<P10>(ctx, argumentCount, arguments, 10);  \
    P11 p11 = getArgument<P11>(ctx, argumentCount, arguments, 11);  \
    P12 p12 = getArgument<P12>(ctx, argumentCount, arguments, 12);  \
    P13 p13 = getArgument<P13>(ctx, argumentCount, arguments, 13);  \
    return makeResult<Ret>(ctx, impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13)); \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V0(name) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                       \
    impl_##name();                                                     \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V1(name, P0) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                       \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    impl_##name(p0);                                                   \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V2(name, P0, P1) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    impl_##name(p0,p1);                                                 \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V3(name, P0, P1, P2) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                       \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    impl_##name(p0,p1,p2);                                             \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V4(name, P0, P1, P2, P3) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    impl_##name(p0,p1,p2,p3);                                           \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V5(name, P0, P1, P2, P3, P4) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    impl_##name(p0,p1,p2,p3,p4);                                        \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V6(name, P0, P1, P2, P3, P4, P5) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    impl_##name(p0,p1,p2,p3,p4,p5);                                     \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V7(name, P0, P1, P2, P3, P4, P5, P6) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    impl_##name(p0,p1,p2,p3,p4,p5,p6);                                  \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V8(name, P0, P1, P2, P3, P4, P5, P6, P7) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    impl_##name(p0,p1,p2,p3,p4,p5,p6,p7);                               \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V9(name, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8);                            \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V10(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    P9 p9 = getArgument<P9>(ctx, argumentCount, arguments, 9);  \
    impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9);                         \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V11(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    P9 p9 = getArgument<P9>(ctx, argumentCount, arguments, 9);  \
    P10 p10 = getArgument<P10>(ctx, argumentCount, arguments, 10);  \
    impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10);                         \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V12(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    P9 p9 = getArgument<P9>(ctx, argumentCount, arguments, 9);  \
    P10 p10 = getArgument<P10>(ctx, argumentCount, arguments, 10);  \
    P11 p11 = getArgument<P11>(ctx, argumentCount, arguments, 11);  \
    impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11);                     \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V13(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    P9 p9 = getArgument<P9>(ctx, argumentCount, arguments, 9);  \
    P10 p10 = getArgument<P10>(ctx, argumentCount, arguments, 10);  \
    P11 p11 = getArgument<P11>(ctx, argumentCount, arguments, 11);  \
    P12 p12 = getArgument<P12>(ctx, argumentCount, arguments, 12);  \
    impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12);                 \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_V14(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    P4 p4 = getArgument<P4>(ctx, argumentCount, arguments, 4);  \
    P5 p5 = getArgument<P5>(ctx, argumentCount, arguments, 5);  \
    P6 p6 = getArgument<P6>(ctx, argumentCount, arguments, 6);  \
    P7 p7 = getArgument<P7>(ctx, argumentCount, arguments, 7);  \
    P8 p8 = getArgument<P8>(ctx, argumentCount, arguments, 8);  \
    P9 p9 = getArgument<P9>(ctx, argumentCount, arguments, 9);  \
    P10 p10 = getArgument<P10>(ctx, argumentCount, arguments, 10);  \
    P11 p11 = getArgument<P11>(ctx, argumentCount, arguments, 11);  \
    P12 p12 = getArgument<P12>(ctx, argumentCount, arguments, 12);  \
    P13 p13 = getArgument<P13>(ctx, argumentCount, arguments, 13);  \
    impl_##name(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13);             \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

// Improve: implement properly
#define KOALA_INTEROP_CTX_3(name, Ret, P0, P1, P2)                                                                                                                 \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception) \
  {                                                                                                                                                                \
    printf("Improve: implement KOALA_INTEROP_CTX_3 for jsc");                                                                                                         \
    KOALA_MAYBE_LOG(name)                                                                                                                                          \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);                                                                                                     \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);                                                                                                     \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);                                                                                                     \
    return makeResult<Ret>(ctx, impl_##name(nullptr, p0, p1, p2));                                                                                                          \
  }                                                                                                                                                                \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_CTX_4(name, Ret, P0, P1, P2, P4)                                                                                                             \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception) \
  {                                                                                                                                                                \
    printf("Improve: implement KOALA_INTEROP_CTX_4 for jsc");                                                                                                         \
    KOALA_MAYBE_LOG(name)                                                                                                                                          \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);                                                                                                     \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);                                                                                                     \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);                                                                                                     \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);                                                                                                     \
    return makeResult<Ret>(ctx, impl_##name(nullptr, p0, p1, p2, p3));                                                                                             \
  }                                                                                                                                                                \
  MAKE_JSC_EXPORT(name)

// Improve: implement properly
#define KOALA_INTEROP_CTX_V3(name, P0, P1, P2) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    printf("Improve: implement KOALA_INTEROP_CTX_V3 for jsc"); \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    impl_##name(nullptr, p0, p1, p2);             \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

#define KOALA_INTEROP_CTX_V4(name, P0, P1, P2, P3) \
  JSValueRef Jsc_##name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) { \
    printf("Improve: implement KOALA_INTEROP_CTX_V4 for jsc"); \
    KOALA_MAYBE_LOG(name)                                             \
    P0 p0 = getArgument<P0>(ctx, argumentCount, arguments, 0);  \
    P1 p1 = getArgument<P1>(ctx, argumentCount, arguments, 1);  \
    P2 p2 = getArgument<P2>(ctx, argumentCount, arguments, 2);  \
    P3 p3 = getArgument<P3>(ctx, argumentCount, arguments, 3);  \
    impl_##name(nullptr, p0, p1, p2, p3);             \
    return makeVoid(ctx);                                       \
  } \
  MAKE_JSC_EXPORT(name)

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

#define KOALA_INTEROP_THROW(vmContext, object, ...) \
   do { \
     /* Improve: implement*/ ASSERT(false); \
     return __VA_ARGS__; \
   } while (0)

#define KOALA_INTEROP_THROW_STRING(vmContext, message, ...) \
   do { \
      ASSERT(false); /* Improve: implement*/ \
     return __VA_ARGS__; \
   } while (0)

#endif // CONVERTORS_JSC_H