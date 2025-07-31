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

#pragma once

#ifdef KOALA_JNI

#include <jni.h>
#include <assert.h>

#include <cmath>
#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>

#include "koala-types.h"
#include "securec.h"

#define KOALA_JNI_CALL(type) extern "C" JNIEXPORT type JNICALL

class JniExports {
    std::unordered_map<std::string,
      std::vector<std::tuple<std::string, std::string, void*>>> implementations;

public:
    static JniExports* getInstance();

    std::vector<std::string> getModules();
    void addMethod(const char* module, const char* name, const char* type, void* impl);
    const std::vector<std::tuple<std::string, std::string, void*>>& getMethods(const std::string& module);
};

#define KOALA_QUOTE0(x) #x
#define KOALA_QUOTE(x) KOALA_QUOTE0(x)

#ifdef _MSC_VER
#define MAKE_JNI_EXPORT(module, name, type)                             \
    static void __init_##name() {                               \
        JniExports::getInstance()->addMethod(KOALA_QUOTE(module), "_"#name, type, reinterpret_cast<void *>(Java_org_##name)); \
    }                                                           \
    namespace {                                                 \
      struct __Init_##name {                                    \
        __Init_##name() {  __init_##name(); }                   \
      } __Init_##name##_v;                                      \
    }
#else
#define MAKE_JNI_EXPORT(module, name, type) \
    __attribute__((constructor)) \
    static void __init_jni_##name() { \
        JniExports::getInstance()->addMethod(KOALA_QUOTE(module), "_"#name, type, reinterpret_cast<void *>(Java_org_##name)); \
    }
#endif

template<class T>
struct InteropTypeConverter {
    using InteropType = T;
    static T convertFrom(JNIEnv* env, InteropType value) { return value; }
    static InteropType convertTo(JNIEnv* env, T value) { return value; }
    static void release(JNIEnv* env, InteropType value, T converted) {}
};

template<class T>
struct SlowInteropTypeConverter {
    using InteropType = T;
    static inline T convertFrom(JNIEnv* env, InteropType value) { return value; }
    static inline InteropType convertTo(JNIEnv* env, T value) { return value; }
    static void release(JNIEnv* env, InteropType value, T converted) {}
};

template<>
struct InteropTypeConverter<KStringPtr> {
    using InteropType = jstring;
    static inline KStringPtr convertFrom0(JNIEnv* env, InteropType value) {
        if (value == nullptr) return KStringPtr();
        jboolean isCopy;
        // TODO: use GetStringCritical() instead and utf-8 encode manually.
		    const char* str_value = env->GetStringUTFChars(value, &isCopy);
        int len = env->GetStringUTFLength(value);
        KStringPtr result(str_value, len, false);
        return result;
    }
    static KStringPtr convertFrom(JNIEnv* env, InteropType value) {
        if (value == nullptr) return KStringPtr();
        KStringPtr result;
        // Notice that we use UTF length for buffer size, but counter is expressed in number of Unicode chars.
        result.resize( env->GetStringUTFLength(value));
        env->GetStringUTFRegion(value, 0, env->GetStringLength(value), result.data());
        return result;
    }
    static InteropType convertTo(JNIEnv* env, KStringPtr value) {
      return env->NewStringUTF(value.c_str());
    }
    static inline void release(JNIEnv* env, InteropType value, const KStringPtr& converted) {
    }
};

template<>
struct SlowInteropTypeConverter<KVMObjectHandle> {
    using InteropType = jobject;
    static inline KVMObjectHandle convertFrom(JNIEnv* env, InteropType value) {
        return reinterpret_cast<KVMObjectHandle>(value);
    }
    static InteropType convertTo(JNIEnv* env, KVMObjectHandle value) {
      return reinterpret_cast<jobject>(value);
    }
    static inline void release(JNIEnv* env, InteropType value, KVMObjectHandle converted) {
    }
};

template<>
struct SlowInteropTypeConverter<KStringPtr> {
    using InteropType = jstring;
    static inline KStringPtr convertFrom(JNIEnv* env, InteropType value) {
        if (value == nullptr) return KStringPtr();
        jboolean isCopy;
		    const char* str_value = env->GetStringUTFChars(value, &isCopy);
        int len = env->GetStringLength(value);
        KStringPtr result(str_value, len, false);
        return result;
    }
    static InteropType convertTo(JNIEnv* env, KStringPtr value) {
      return env->NewStringUTF(value.c_str());
    }
    static inline void release(JNIEnv* env, InteropType value, const KStringPtr& converted) {
      env->ReleaseStringUTFChars(value, converted.data());
    }
};

template<>
struct SlowInteropTypeConverter<KInteropBuffer> {
    using InteropType = jarray;
    static inline KInteropBuffer convertFrom(JNIEnv* env, InteropType value) {
        if (value == nullptr) return KInteropBuffer();
        KInteropBuffer result({env->GetArrayLength(value), reinterpret_cast<KByte*>(env->GetPrimitiveArrayCritical(value, nullptr))});
        return result;
    }
    static InteropType convertTo(JNIEnv* env, KInteropBuffer value) {
      jarray result = env->NewByteArray(value.length);
      void* data = env->GetPrimitiveArrayCritical(result, nullptr);
      if (memcpy_s(data, value.length, value.data, value.length) != 0) {
        return;
      }
      env->ReleasePrimitiveArrayCritical(result, data, 0);
      return result;
    }
    static inline void release(JNIEnv* env, InteropType value, const KInteropBuffer& converted) {
      env->ReleasePrimitiveArrayCritical(value, converted.data, 0);
    }
};

template<>
struct SlowInteropTypeConverter<KInteropReturnBuffer> {
    using InteropType = jarray;
    static inline KInteropReturnBuffer convertFrom(JNIEnv* env, InteropType value) = delete;
    static InteropType convertTo(JNIEnv* env, KInteropReturnBuffer value) {
      jarray result = env->NewByteArray(value.length);
      void* data = env->GetPrimitiveArrayCritical(result, nullptr);
      if (memcpy_s(data, value.length, value.data, value.length) != 0) {
        return;
      }
      env->ReleasePrimitiveArrayCritical(result, data, 0);
      value.dispose(value.data, value.length);
      return result;
    }
    static inline void release(JNIEnv* env, InteropType value, const KInteropReturnBuffer& converted) = delete;
};

template<>
struct InteropTypeConverter<KByte*> {
    using InteropType = jbyteArray;
    static inline KByte* convertFrom(JNIEnv* env, InteropType value) {
        return value ? reinterpret_cast<KByte*>(env->GetPrimitiveArrayCritical(value, nullptr)) : nullptr;
    }
    static InteropType convertTo(JNIEnv* env, KByte* value) = delete;
    static inline void release(JNIEnv* env, InteropType value, KByte* converted) {
        if (converted) env->ReleasePrimitiveArrayCritical(value, converted, 0);
    }
};

template<>
struct SlowInteropTypeConverter<KByte*> {
    using InteropType = jbyteArray;
    static inline KByte* convertFrom(JNIEnv* env, InteropType value) {
        return value ? reinterpret_cast<KByte*>(env->GetByteArrayElements(value, nullptr)) : nullptr;
    }
    static InteropType convertTo(JNIEnv* env, KByte* value) = delete;
    static inline void release(JNIEnv* env, InteropType value, KByte* converted) {
        if (converted) env->ReleaseByteArrayElements(value, reinterpret_cast<jbyte*>(converted), 0);
    }
};

template<>
struct InteropTypeConverter<KInt*> {
    using InteropType = jintArray;
    static KInt* convertFrom(JNIEnv* env, InteropType value) {
        return value ? reinterpret_cast<KInt*>(env->GetPrimitiveArrayCritical(value, nullptr)) : nullptr;
    }
    static InteropType convertTo(JNIEnv* env, KInt* value) = delete;
    static void release(JNIEnv* env, InteropType value, KInt* converted) {
         env->ReleasePrimitiveArrayCritical(value, converted, 0);
    }
};

template<>
struct SlowInteropTypeConverter<KInt*> {
    using InteropType = jintArray;
    static KInt* convertFrom(JNIEnv* env, InteropType value) {
        return value ? reinterpret_cast<KInt*>(env->GetIntArrayElements(value, nullptr)) : nullptr;
    }
    static InteropType convertTo(JNIEnv* env, KInt* value) = delete;
    static void release(JNIEnv* env, InteropType value, KInt* converted) {
         env->ReleaseIntArrayElements(value, reinterpret_cast<jint*>(converted), 0);
    }
};

template<>
struct InteropTypeConverter<KFloat*> {
    using InteropType = jfloatArray;
    static KFloat* convertFrom(JNIEnv* env, InteropType value) {
        return value ? reinterpret_cast<KFloat*>(env->GetPrimitiveArrayCritical(value, nullptr)) : nullptr;
    }
    static InteropType convertTo(JNIEnv* env, KFloat* value) = delete;
    static void release(JNIEnv* env, InteropType value, KFloat* converted) {
        env->ReleasePrimitiveArrayCritical(value, converted, 0);
    }
};

template<>
struct SlowInteropTypeConverter<KFloat*> {
    using InteropType = jfloatArray;
    static KFloat* convertFrom(JNIEnv* env, InteropType value) {
        return value ? reinterpret_cast<KFloat*>(env->GetFloatArrayElements(value, nullptr)) : nullptr;
    }
    static InteropType convertTo(JNIEnv* env, KFloat* value) = delete;
    static void release(JNIEnv* env, InteropType value, KFloat* converted) {
        env->ReleaseFloatArrayElements(value, reinterpret_cast<jfloat*>(converted), 0);
    }
};

template<>
struct InteropTypeConverter<KNativePointer> {
    using InteropType = jlong;
    static KNativePointer convertFrom(JNIEnv* env, InteropType value) {
      return reinterpret_cast<KNativePointer>(value);
    }
    static InteropType convertTo(JNIEnv* env, KNativePointer value) {
      return reinterpret_cast<jlong>(value);
    }
    static inline void release(JNIEnv* env, InteropType value, KNativePointer converted) {}
};

template<>
struct SlowInteropTypeConverter<KNativePointer> {
    using InteropType = jlong;
    static KNativePointer convertFrom(JNIEnv* env, InteropType value) {
      return reinterpret_cast<KNativePointer>(value);
    }
    static InteropType convertTo(JNIEnv* env, KNativePointer value) {
      return reinterpret_cast<jlong>(value);
    }
    static void release(JNIEnv* env, InteropType value, KNativePointer converted) {}
};

template<>
struct InteropTypeConverter<KInteropNumber> {
    using InteropType = jdouble;
    static KInteropNumber convertFrom(JNIEnv* env, InteropType value) {
        return KInteropNumber::fromDouble(value);
    }
    static InteropType convertTo(JNIEnv* env, KInteropNumber value) {
        return value.asDouble();
    }
    static inline void release(JNIEnv* env, InteropType value, KInteropNumber converted) {}
};

template<>
struct SlowInteropTypeConverter<KInteropNumber> {
    using InteropType = jdouble;
    static KInteropNumber convertFrom(JNIEnv* env, InteropType value) {
        return KInteropNumber::fromDouble(value);
    }
    static InteropType convertTo(JNIEnv* env, KInteropNumber value) {
        return value.asDouble();
    }
    static void release(JNIEnv* env, InteropType value, KInteropNumber converted) {}
};

template<>
struct InteropTypeConverter<KLength> {
    using InteropType = jstring;
    static KLength convertFrom(JNIEnv* env, InteropType value) {
        KLength result { 0 };

        if (value == nullptr) {
            result.type = -1; // ARK_RUNTIME_UNEXPECTED
            return result;
        }
        jboolean isCopy;
        const char* str_value = env->GetStringUTFChars(value, &isCopy);
        int len = env->GetStringLength(value);
        KStringPtr kStr(str_value, len, false);
        parseKLength(kStr, &result);
        env->ReleaseStringUTFChars(value, str_value);
        result.type = 2; // ARK_RUNTIME_STRING
        result.resource = 0;

        return result;
    }
    static InteropType convertTo(JNIEnv* env, KLength value) = delete;
    static inline void release(JNIEnv* env, InteropType value, KLength converted) {}
};

template <typename Type>
inline Type getArgument(JNIEnv* env, typename InteropTypeConverter<Type>::InteropType arg) {
  return InteropTypeConverter<Type>::convertFrom(env, arg);
}

template <typename Type>
inline void releaseArgument(JNIEnv* env, typename InteropTypeConverter<Type>::InteropType arg, Type& data) {
  InteropTypeConverter<Type>::release(env, arg, data);
}

#ifndef KOALA_INTEROP_MODULE
#error KOALA_INTEROP_MODULE is undefined
#endif

#define KOALA_INTEROP_0(name, Ret) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance) { \
      KOALA_MAYBE_LOG(name) \
      return InteropTypeConverter<Ret>::convertTo(env, impl_##name()); \
  } \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret)

#define KOALA_INTEROP_1(name, Ret, P0) \
   KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) \
   Java_org_##name(JNIEnv* env, jclass instance, \
    InteropTypeConverter<P0>::InteropType _p0) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0)); \
      releaseArgument(env, _p0, p0); \
      return rv; \
  } \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0)

#define KOALA_INTEROP_2(name, Ret, P0, P1) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1)

#define KOALA_INTEROP_3(name, Ret, P0, P1, P2) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2)

#define KOALA_INTEROP_4(name, Ret, P0, P1, P2, P3) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3)

#define KOALA_INTEROP_5(name, Ret, P0, P1, P2, P3, P4) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3, p4)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4)

#define KOALA_INTEROP_6(name, Ret, P0, P1, P2, P3, P4, P5) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3, p4, p5)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5)

#define KOALA_INTEROP_7(name, Ret, P0, P1, P2, P3, P4, P5, P6) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5, \
    InteropTypeConverter<P6>::InteropType _p6) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3, p4, p5, p6)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6)

#define KOALA_INTEROP_8(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7)

#define KOALA_INTEROP_9(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7, \
  InteropTypeConverter<P8>::InteropType _p8) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8)

#define KOALA_INTEROP_10(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7, \
  InteropTypeConverter<P8>::InteropType _p8, \
  InteropTypeConverter<P9>::InteropType _p9) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9)

#define KOALA_INTEROP_11(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7, \
  InteropTypeConverter<P8>::InteropType _p8, \
  InteropTypeConverter<P9>::InteropType _p9, \
  InteropTypeConverter<P10>::InteropType _p10) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      P10 p10 = getArgument<P10>(env, _p10); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
      releaseArgument(env, _p10, p10); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10)

#define KOALA_INTEROP_12(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5, \
    InteropTypeConverter<P6>::InteropType _p6, \
    InteropTypeConverter<P7>::InteropType _p7, \
    InteropTypeConverter<P8>::InteropType _p8, \
    InteropTypeConverter<P9>::InteropType _p9, \
    InteropTypeConverter<P10>::InteropType _p10, \
    InteropTypeConverter<P11>::InteropType _p11) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      P10 p10 = getArgument<P10>(env, _p10); \
      P11 p11 = getArgument<P11>(env, _p11); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
      releaseArgument(env, _p10, p10); \
      releaseArgument(env, _p11, p11); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11)

#define KOALA_INTEROP_13(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5, \
    InteropTypeConverter<P6>::InteropType _p6, \
    InteropTypeConverter<P7>::InteropType _p7, \
    InteropTypeConverter<P8>::InteropType _p8, \
    InteropTypeConverter<P9>::InteropType _p9, \
    InteropTypeConverter<P10>::InteropType _p10, \
    InteropTypeConverter<P11>::InteropType _p11, \
    InteropTypeConverter<P12>::InteropType _p12) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      P10 p10 = getArgument<P10>(env, _p10); \
      P11 p11 = getArgument<P11>(env, _p11); \
      P12 p12 = getArgument<P12>(env, _p12); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
      releaseArgument(env, _p10, p10); \
      releaseArgument(env, _p11, p11); \
      releaseArgument(env, _p12, p12); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9"|" #P10 "|" #P11 "|" #P12)

#define KOALA_INTEROP_14(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  KOALA_JNI_CALL(InteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5, \
    InteropTypeConverter<P6>::InteropType _p6, \
    InteropTypeConverter<P7>::InteropType _p7, \
    InteropTypeConverter<P8>::InteropType _p8, \
    InteropTypeConverter<P9>::InteropType _p9, \
    InteropTypeConverter<P10>::InteropType _p10, \
    InteropTypeConverter<P11>::InteropType _p11, \
    InteropTypeConverter<P12>::InteropType _p12, \
    InteropTypeConverter<P13>::InteropType _p13) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      P10 p10 = getArgument<P10>(env, _p10); \
      P11 p11 = getArgument<P11>(env, _p11); \
      P12 p12 = getArgument<P12>(env, _p12); \
      P13 p13 = getArgument<P13>(env, _p13); \
      auto rv = InteropTypeConverter<Ret>::convertTo(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
      releaseArgument(env, _p10, p10); \
      releaseArgument(env, _p11, p11); \
      releaseArgument(env, _p12, p12); \
      releaseArgument(env, _p13, p13); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9"|" #P10 "|" #P11 "|" #P12 "|" #P13)


#define KOALA_INTEROP_V0(name) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance) { \
      KOALA_MAYBE_LOG(name) \
      impl_##name(); \
  } \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void")

#define KOALA_INTEROP_V1(name, P0) \
   KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
    InteropTypeConverter<P0>::InteropType _p0) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      impl_##name(p0); \
      releaseArgument(env, _p0, p0); \
  } \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0)

#define KOALA_INTEROP_V2(name, P0, P1) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
   InteropTypeConverter<P0>::InteropType _p0, \
   InteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      impl_##name(p0, p1); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1)

#define KOALA_INTEROP_V3(name, P0, P1, P2) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
   InteropTypeConverter<P0>::InteropType _p0, \
   InteropTypeConverter<P1>::InteropType _p1, \
   InteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      impl_##name(p0, p1, p2); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2)

#define KOALA_INTEROP_V4(name, P0, P1, P2, P3) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      impl_##name(p0, p1, p2, p3); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3)

#define KOALA_INTEROP_V5(name, P0, P1, P2, P3, P4) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      impl_##name(p0, p1, p2, p3, p4); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4)

#define KOALA_INTEROP_V6(name, P0, P1, P2, P3, P4, P5) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      impl_##name(p0, p1, p2, p3, p4, p5); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5)

#define KOALA_INTEROP_V7(name, P0, P1, P2, P3, P4, P5, P6) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6)

#define KOALA_INTEROP_V8(name, P0, P1, P2, P3, P4, P5, P6, P7) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7)

#define KOALA_INTEROP_V9(name, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5, \
    InteropTypeConverter<P6>::InteropType _p6, \
    InteropTypeConverter<P7>::InteropType _p7, \
    InteropTypeConverter<P8>::InteropType _p8) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8)

#define KOALA_INTEROP_V10(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7, \
  InteropTypeConverter<P8>::InteropType _p8, \
  InteropTypeConverter<P9>::InteropType _p9) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9)

#define KOALA_INTEROP_V11(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7, \
  InteropTypeConverter<P8>::InteropType _p8, \
  InteropTypeConverter<P9>::InteropType _p9, \
  InteropTypeConverter<P10>::InteropType _p10) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      P10 p10 = getArgument<P10>(env, _p10); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
      releaseArgument(env, _p10, p10); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10)

#define KOALA_INTEROP_V12(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7, \
  InteropTypeConverter<P8>::InteropType _p8, \
  InteropTypeConverter<P9>::InteropType _p9, \
  InteropTypeConverter<P10>::InteropType _p10, \
  InteropTypeConverter<P11>::InteropType _p11) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      P10 p10 = getArgument<P10>(env, _p10); \
      P11 p11 = getArgument<P11>(env, _p11); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
      releaseArgument(env, _p10, p10); \
      releaseArgument(env, _p11, p11); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11)

#define KOALA_INTEROP_V13(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7, \
  InteropTypeConverter<P8>::InteropType _p8, \
  InteropTypeConverter<P9>::InteropType _p9, \
  InteropTypeConverter<P10>::InteropType _p10, \
  InteropTypeConverter<P11>::InteropType _p11, \
  InteropTypeConverter<P12>::InteropType _p12) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      P10 p10 = getArgument<P10>(env, _p10); \
      P11 p11 = getArgument<P11>(env, _p11); \
      P12 p12 = getArgument<P12>(env, _p12); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
      releaseArgument(env, _p10, p10); \
      releaseArgument(env, _p11, p11); \
      releaseArgument(env, _p12, p12); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11 "|" #P12)

#define KOALA_INTEROP_V14(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7, \
  InteropTypeConverter<P8>::InteropType _p8, \
  InteropTypeConverter<P9>::InteropType _p9, \
  InteropTypeConverter<P10>::InteropType _p10, \
  InteropTypeConverter<P11>::InteropType _p11, \
  InteropTypeConverter<P12>::InteropType _p12, \
  InteropTypeConverter<P13>::InteropType _p13) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      P10 p10 = getArgument<P10>(env, _p10); \
      P11 p11 = getArgument<P11>(env, _p11); \
      P12 p12 = getArgument<P12>(env, _p12); \
      P13 p13 = getArgument<P13>(env, _p13); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
      releaseArgument(env, _p10, p10); \
      releaseArgument(env, _p11, p11); \
      releaseArgument(env, _p12, p12); \
      releaseArgument(env, _p13, p13); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11 "|" #P12 "|" #P13)

#define KOALA_INTEROP_V15(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
  InteropTypeConverter<P0>::InteropType _p0, \
  InteropTypeConverter<P1>::InteropType _p1, \
  InteropTypeConverter<P2>::InteropType _p2, \
  InteropTypeConverter<P3>::InteropType _p3, \
  InteropTypeConverter<P4>::InteropType _p4, \
  InteropTypeConverter<P5>::InteropType _p5, \
  InteropTypeConverter<P6>::InteropType _p6, \
  InteropTypeConverter<P7>::InteropType _p7, \
  InteropTypeConverter<P8>::InteropType _p8, \
  InteropTypeConverter<P9>::InteropType _p9, \
  InteropTypeConverter<P10>::InteropType _p10, \
  InteropTypeConverter<P11>::InteropType _p11, \
  InteropTypeConverter<P12>::InteropType _p12, \
  InteropTypeConverter<P13>::InteropType _p13, \
  InteropTypeConverter<P14>::InteropType _p14) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      P5 p5 = getArgument<P5>(env, _p5); \
      P6 p6 = getArgument<P6>(env, _p6); \
      P7 p7 = getArgument<P7>(env, _p7); \
      P8 p8 = getArgument<P8>(env, _p8); \
      P9 p9 = getArgument<P9>(env, _p9); \
      P10 p10 = getArgument<P10>(env, _p10); \
      P11 p11 = getArgument<P11>(env, _p11); \
      P12 p12 = getArgument<P12>(env, _p12); \
      P13 p13 = getArgument<P13>(env, _p13); \
      P14 p14 = getArgument<P14>(env, _p14); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      releaseArgument(env, _p7, p7); \
      releaseArgument(env, _p8, p8); \
      releaseArgument(env, _p9, p9); \
      releaseArgument(env, _p10, p10); \
      releaseArgument(env, _p11, p11); \
      releaseArgument(env, _p12, p12); \
      releaseArgument(env, _p13, p13); \
      releaseArgument(env, _p14, p14); \
}  \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11 "|" #P12 "|" #P13 "|" #P14)

#define KOALA_INTEROP_CTX_0(name, Ret) \
   KOALA_JNI_CALL(SlowInteropTypeConverter<Ret>::InteropType) \
   Java_org_##name(JNIEnv* env, jclass instance) { \
      KOALA_MAYBE_LOG(name) \
      KVMContext ctx = (KVMContext)env; \
      auto rv = SlowInteropTypeConverter<Ret>::convertTo(env, impl_##name(ctx)); \
      return rv; \
  } \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret)

#define KOALA_INTEROP_CTX_1(name, Ret, P0) \
   KOALA_JNI_CALL(SlowInteropTypeConverter<Ret>::InteropType) \
   Java_org_##name(JNIEnv* env, jclass instance, \
    SlowInteropTypeConverter<P0>::InteropType _p0) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      KVMContext ctx = (KVMContext)env; \
      auto rv = SlowInteropTypeConverter<Ret>::convertTo(env, impl_##name(ctx, p0)); \
      releaseArgument(env, _p0, p0); \
      return rv; \
  } \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0)

#define KOALA_INTEROP_CTX_2(name, Ret, P0, P1) \
  KOALA_JNI_CALL(SlowInteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  SlowInteropTypeConverter<P0>::InteropType _p0, \
  SlowInteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      KVMContext ctx = (KVMContext)env; \
      auto rv = SlowInteropTypeConverter<Ret>::convertTo(env, impl_##name(ctx, p0, p1)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1)

#define KOALA_INTEROP_CTX_3(name, Ret, P0, P1, P2) \
  KOALA_JNI_CALL(SlowInteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  SlowInteropTypeConverter<P0>::InteropType _p0, \
  SlowInteropTypeConverter<P1>::InteropType _p1, \
  SlowInteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      KVMContext ctx = (KVMContext)env; \
      auto rv = SlowInteropTypeConverter<Ret>::convertTo(env, impl_##name(ctx, p0, p1, p2)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2)

#define KOALA_INTEROP_CTX_4(name, Ret, P0, P1, P2, P3) \
  KOALA_JNI_CALL(SlowInteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  SlowInteropTypeConverter<P0>::InteropType _p0, \
  SlowInteropTypeConverter<P1>::InteropType _p1, \
  SlowInteropTypeConverter<P2>::InteropType _p2, \
  SlowInteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      KVMContext ctx = (KVMContext)env; \
      auto rv = SlowInteropTypeConverter<Ret>::convertTo(env, impl_##name(ctx, p0, p1, p2, p3)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3)

#define KOALA_INTEROP_CTX_5(name, Ret, P0, P1, P2, P3, P4) \
  KOALA_JNI_CALL(SlowInteropTypeConverter<Ret>::InteropType) Java_org_##name(JNIEnv* env, jclass instance, \
  SlowInteropTypeConverter<P0>::InteropType _p0, \
  SlowInteropTypeConverter<P1>::InteropType _p1, \
  SlowInteropTypeConverter<P2>::InteropType _p2, \
  SlowInteropTypeConverter<P3>::InteropType _p3, \
  SlowInteropTypeConverter<P4>::InteropType _p4) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      KVMContext ctx = (KVMContext)env; \
      auto rv = SlowInteropTypeConverter<Ret>::convertTo(env, impl_##name(ctx, p0, p1, p2, p3, p4)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      return rv; \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4)

#define KOALA_INTEROP_CTX_V0(name) \
   KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance) { \
      KOALA_MAYBE_LOG(name) \
      KVMContext ctx = (KVMContext)env; \
      impl_##name(ctx); \
  } \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void")

#define KOALA_INTEROP_CTX_V1(name, P0) \
   KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
    SlowInteropTypeConverter<P0>::InteropType _p0) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      KVMContext ctx = (KVMContext)env; \
      impl_##name(ctx, p0); \
      releaseArgument(env, _p0, p0); \
  } \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0)

#define KOALA_INTEROP_CTX_V2(name, P0, P1) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
   SlowInteropTypeConverter<P0>::InteropType _p0, \
   SlowInteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      KVMContext ctx = (KVMContext)env; \
      impl_##name(ctx, p0, p1); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1)

#define KOALA_INTEROP_CTX_V3(name, P0, P1, P2) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
   SlowInteropTypeConverter<P0>::InteropType _p0, \
   SlowInteropTypeConverter<P1>::InteropType _p1, \
   SlowInteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      KVMContext ctx = (KVMContext)env; \
      impl_##name(ctx, p0, p1, p2); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2)

#define KOALA_INTEROP_CTX_V4(name, P0, P1, P2, P3) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
   SlowInteropTypeConverter<P0>::InteropType _p0, \
   SlowInteropTypeConverter<P1>::InteropType _p1, \
   SlowInteropTypeConverter<P2>::InteropType _p2, \
   SlowInteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      KVMContext ctx = (KVMContext)env; \
      impl_##name(ctx, p0, p1, p2, p3); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3)

#define KOALA_INTEROP_CTX_V5(name, P0, P1, P2, P3, P4) \
  KOALA_JNI_CALL(void) Java_org_##name(JNIEnv* env, jclass instance, \
   SlowInteropTypeConverter<P0>::InteropType _p0, \
   SlowInteropTypeConverter<P1>::InteropType _p1, \
   SlowInteropTypeConverter<P2>::InteropType _p2, \
   SlowInteropTypeConverter<P3>::InteropType _p3, \
   SlowInteropTypeConverter<P4>::InteropType _p4) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      KVMContext ctx = (KVMContext)env; \
      impl_##name(ctx, p0, p1, p2, p3, p4); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
} \
MAKE_JNI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4)

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

bool setKoalaJniCallbackDispatcher(
    JNIEnv* env,
    jclass clazz,
    const char* dispatcherMethodName,
    const char* dispactherMethodSig
);
void getKoalaJniCallbackDispatcher(jclass* clazz, jmethodID* method);

#define KOALA_INTEROP_CALL_VOID(venv, id, length, args)                            \
{                                                                                  \
  jclass clazz = nullptr;                                                          \
  jmethodID method = nullptr;                                                      \
  getKoalaJniCallbackDispatcher(&clazz, &method);                                  \
  JNIEnv* jniEnv = reinterpret_cast<JNIEnv*>(venv);                                \
  jniEnv->PushLocalFrame(1);                                                       \
  jbyteArray args_jni = jniEnv->NewByteArray(length);                              \
  jniEnv->SetByteArrayRegion(args_jni, 0, length, reinterpret_cast<jbyte*>(args)); \
  jniEnv->CallStaticIntMethod(clazz, method, id, args_jni, length);                \
  jniEnv->GetByteArrayRegion(args_jni, 0, length, reinterpret_cast<jbyte*>(args)); \
  jniEnv->PopLocalFrame(nullptr);                                                  \
}

#define KOALA_INTEROP_CALL_INT(venv, id, length, args)                             \
{                                                                                  \
  jclass clazz = nullptr;                                                          \
  jmethodID method = nullptr;                                                      \
  getKoalaJniCallbackDispatcher(&clazz, &method);                                  \
  JNIEnv* jniEnv = reinterpret_cast<JNIEnv*>(venv);                                \
  jniEnv->PushLocalFrame(1);                                                       \
  jbyteArray args_jni = jniEnv->NewByteArray(length);                              \
  jniEnv->SetByteArrayRegion(args_jni, 0, length, reinterpret_cast<jbyte*>(args)); \
  int32_t rv = jniEnv->CallStaticIntMethod(clazz, method, id, args_jni, length);   \
  jniEnv->GetByteArrayRegion(args_jni, 0, length, reinterpret_cast<jbyte*>(args)); \
  jniEnv->PopLocalFrame(nullptr);                                                  \
  return rv;                                                                       \
}

#define KOALA_INTEROP_CALL_VOID_INTS32(venv, id, argc, args) KOALA_INTEROP_CALL_VOID(venv, id, (argc) * sizeof(int32_t), args)
#define KOALA_INTEROP_CALL_INT_INTS32(venv, id, argc, args) KOALA_INTEROP_CALL_INT(venv, id, (argc) * sizeof(int32_t), args)

#define KOALA_INTEROP_THROW(vmContext, object, ...) \
   do { \
     JNIEnv* env = reinterpret_cast<JNIEnv*>(vmContext); \
     env->Throw(object); \
     return __VA_ARGS__; \
   } while (0)

#define KOALA_INTEROP_THROW_STRING(vmContext, message, ...) \
  do { \
    JNIEnv* env = reinterpret_cast<JNIEnv*>(vmContext); \
    const static jclass errorClass = env->FindClass("java/lang/RuntimeException"); \
    env->ThrowNew(errorClass, message); \
  } while (0)

#endif  // KOALA_JNI_CALL
