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

#ifdef KOALA_ANI

#include <assert.h>
#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <tuple>
#include <unordered_map>

#include "ani.h"
#include "koala-types.h"

template<class T>
struct InteropTypeConverter {
    using InteropType = T;
    static T convertFrom(ani_env* env, InteropType value) = delete;
    static InteropType convertTo(ani_env* env, T value) = delete;
    static void release(ani_env* env, InteropType value, T converted) {}
};

template<>
struct InteropTypeConverter<KByte> {
    using InteropType = ani_byte;
    static inline KByte convertFrom(ani_env* env, InteropType value) {
      return value;
    }
    static inline InteropType convertTo(ani_env* env, KByte value) {
      return value;
    }
    static inline void release(ani_env* env, InteropType value, KByte converted) {}
};

template<>
struct InteropTypeConverter<KBoolean> {
    using InteropType = ani_boolean;
    static inline KBoolean convertFrom(ani_env* env, InteropType value) {
      return value;
    }
    static inline InteropType convertTo(ani_env* env, KBoolean value) {
      return value;
    }
    static inline void release(ani_env* env, InteropType value, KBoolean converted) {}
};

template<>
struct InteropTypeConverter<KInt> {
    using InteropType = ani_int;
    static inline KInt convertFrom(ani_env* env, InteropType value) {
      return value;
    }
    static inline InteropType convertTo(ani_env* env, KInt value) {
      return value;
    }
    static inline void release(ani_env* env, InteropType value, KInt converted) {}
};

template<>
struct InteropTypeConverter<KUInt> {
    using InteropType = ani_int;
    static inline KUInt convertFrom(ani_env* env, InteropType value) {
      return value;
    }
    static inline InteropType convertTo(ani_env* env, KUInt value) {
      return value;
    }
    static inline void release(ani_env* env, InteropType value, KUInt converted) {}
};


template<>
struct InteropTypeConverter<KFloat> {
    using InteropType = ani_float;
    static inline KFloat convertFrom(ani_env* env, InteropType value) {
      return value;
    }
    static inline InteropType convertTo(ani_env* env, KFloat value) {
      return value;
    }
    static inline void release(ani_env* env, InteropType value, KFloat converted) {}
};

template<>
struct InteropTypeConverter<KLong> {
    using InteropType = ani_long;
    static inline KLong convertFrom(ani_env* env, InteropType value) {
      return value;
    }
    static inline InteropType convertTo(ani_env* env, KLong value) {
      return value;
    }
    static inline void release(ani_env* env, InteropType value, KLong converted) {}
};


template<>
struct InteropTypeConverter<KVMObjectHandle> {
    using InteropType = ani_object;
    static inline KVMObjectHandle convertFrom(ani_env* env, InteropType value) {
      return reinterpret_cast<KVMObjectHandle>(value);
    }
    static inline InteropType convertTo(ani_env* env, KVMObjectHandle value) {
      return reinterpret_cast<InteropType>(value);
    }
    static inline void release(ani_env* env, InteropType value, KVMObjectHandle converted) {}
};

template<>
struct InteropTypeConverter<KInteropBuffer> {
    using InteropType = ani_array_byte;
    static inline KInteropBuffer convertFrom(ani_env* env, InteropType value) {
      if (value == nullptr) return KInteropBuffer();
      ani_size length = 0;
      env->Array_GetLength(value, &length);
      KByte* data = new KByte[length];
      env->Array_GetRegion_Byte(value, 0, length, (ani_byte*)data);
      KInteropBuffer result = { 0 };
      result.data = data;
      result.length = length;
      return result;
    }
    static inline InteropType convertTo(ani_env* env, KInteropBuffer value) {
      ani_array_byte result;
      env->Array_New_Byte(value.length, &result);
      env->Array_SetRegion_Byte(result, 0, value.length, reinterpret_cast<const ani_byte*>(value.data));
      value.dispose(value.resourceId);
      return result;
    }
    static inline void release(ani_env* env, InteropType value, KInteropBuffer converted) {
      delete [] (KByte*)converted.data;
    }
};

template<>
struct InteropTypeConverter<KSerializerBuffer> {
    using InteropType = ani_long;
    static KSerializerBuffer convertFrom(ani_env* env, InteropType value) {
      return reinterpret_cast<KSerializerBuffer>(static_cast<intptr_t>(value));
    }
    static InteropType convertTo(ani_env* env, KSerializerBuffer value) = delete;
    static inline void release(ani_env* env, InteropType value, KSerializerBuffer converted) {}
};

template<>
struct InteropTypeConverter<KInteropReturnBuffer> {
    using InteropType = ani_array_byte;
    static inline KInteropReturnBuffer convertFrom(ani_env* env, InteropType value) = delete;
    static inline InteropType convertTo(ani_env* env, KInteropReturnBuffer value) {
      ani_array_byte result;
      env->Array_New_Byte(value.length, &result);
      env->Array_SetRegion_Byte(result, 0, value.length, reinterpret_cast<const ani_byte*>(value.data));
      value.dispose(value.data, value.length);
      return result;
    };
    static inline void release(ani_env* env, InteropType value, KInteropReturnBuffer converted) {}
};

template<>
struct InteropTypeConverter<KStringPtr> {
    using InteropType = ani_string;
    static KStringPtr convertFrom(ani_env* env, InteropType value) {
        if (value == nullptr) return KStringPtr();
        KStringPtr result;
        // Notice that we use UTF length for buffer size, but counter is expressed in number of Unicode chars.
        ani_size lengthUtf8 = 0;
        env->String_GetUTF8Size(value, &lengthUtf8);
        result.resize(lengthUtf8);
        ani_size lengthUtf16 = 0;
        env->String_GetUTF16Size(value, &lengthUtf16);
        ani_size count = 0;
        env->String_GetUTF8SubString(value, 0, lengthUtf16, result.data(), lengthUtf8 + 1, &count);
        result.data()[lengthUtf8] = 0;
        return result;
    }
    static InteropType convertTo(ani_env* env, const KStringPtr& value) {
      ani_string result = nullptr;
      env->String_NewUTF8(value.c_str(), value.length() - 1 /* drop zero terminator */, &result);
      return result;
    }
    static void release(ani_env* env, InteropType value, const KStringPtr& converted) {}
};

template<>
struct InteropTypeConverter<KNativePointer> {
    using InteropType = ani_long;
    static KNativePointer convertFrom(ani_env* env, InteropType value) {
      return reinterpret_cast<KNativePointer>(value);
    }
    static InteropType convertTo(ani_env* env, KNativePointer value) {
      return reinterpret_cast<ani_long>(value);
    }
    static void release(ani_env* env, InteropType value, KNativePointer converted) {}
};

template<>
struct InteropTypeConverter<KInt*> {
    using InteropType = ani_array_int;
    static KInt* convertFrom(ani_env* env, InteropType value) {
      if (!value) return nullptr;
      KInt* result = nullptr;
      //env->Array_Pin(value, (void**)&result);
      ani_size length = 0;
      env->Array_GetLength(value, &length);
      KInt* data = new KInt[length];
      env->Array_GetRegion_Int(value, 0, length, (ani_int*)data);
      return data;
    }
    static InteropType convertTo(ani_env* env, KInt* value) = delete;
    static void release(ani_env* env, InteropType value, KInt* converted) {
      if (converted) {
        ani_size length = 0;
        env->Array_GetLength(value, &length);
        env->Array_SetRegion_Int(value, 0, length, (ani_int*)converted);
      }
      //if (converted) env->Array_Unpin(value, converted);
      delete [] converted;
    }
};

template<>
struct InteropTypeConverter<KFloat*> {
    using InteropType = ani_array_float;
    static KFloat* convertFrom(ani_env* env, InteropType value) {
      if (!value) return nullptr;
      //KFloat* result = nullptr;
      //env->Array_Pin(value, (void**)&result);
      ani_size length = 0;
      env->Array_GetLength(value, &length);
      KFloat* data = new KFloat[length];
      env->Array_GetRegion_Float(value, 0, length, (ani_float*)data);
      return data;
    }
    static InteropType convertTo(ani_env* env, KFloat* value) = delete;
    static void release(ani_env* env, InteropType value, KFloat* converted) {
      if (converted) {
        ani_size length = 0;
        env->Array_GetLength(value, &length);
        env->Array_SetRegion_Float(value, 0, length, (ani_float*)converted);
      }
      //if (converted) env->Array_Unpin(value, converted);
      delete [] converted;
    }
};

template<>
struct InteropTypeConverter<KByte*> {
    using InteropType = ani_array_byte;
    static KByte* convertFrom(ani_env* env, InteropType value) {
      if (!value) return nullptr;
      //KByte* result = nullptr;
      //env->Array_Pin(value, (void**)&result);
      ani_size length = 0;
      env->Array_GetLength(value, &length);
      KByte* data = new KByte[length];
      env->Array_GetRegion_Byte(value, 0, length, (ani_byte*)data);
      return data;
    }
    static InteropType convertTo(ani_env* env, KByte* value) = delete;
    static void release(ani_env* env, InteropType value, KByte* converted) {
      if (converted) {
        ani_size length = 0;
        env->Array_GetLength(value, &length);
        env->Array_SetRegion_Byte(value, 0, length, (ani_byte*)converted);
      }
      // if (converted) env->Array_Unpin(value, converted);
      delete[] converted;
    }
};

template <> struct InteropTypeConverter<KInteropNumber> {
  using InteropType = ani_double;
  static KInteropNumber convertFrom(ani_env *env, InteropType value) {
    return KInteropNumber::fromDouble(value);
  }
  static InteropType convertTo(ani_env *env, KInteropNumber value) {
    return value.asDouble();
  }
  static void release(ani_env *env, InteropType value,
                      KInteropNumber converted) {}
};

template<>
struct InteropTypeConverter<KLength> {
  using InteropType = ani_ref;
  static KLength convertFrom(ani_env* env, InteropType value) {
    static ani_class double_class = nullptr;
    static ani_class int_class = nullptr;
    static ani_class string_class = nullptr;
    static ani_class resource_class = nullptr;
    if (!double_class) {
      env->FindClass("Lstd/core/Double;", &double_class);
    }
    if (!int_class) {
      env->FindClass("Lstd/core/Int;", &int_class);
    }
    if (!string_class) {
      env->FindClass("Lstd/core/String;", &string_class);
    }
    if (!resource_class) {
      env->FindClass("L@koalaui/arkts-arkui/generated/ArkResourceInterfaces/Resource;", &resource_class);
    }

    const ani_object valueObj = reinterpret_cast<ani_object>(value);

    ani_boolean isInstanceOf;
    env->Object_InstanceOf(valueObj, double_class, &isInstanceOf);
    if (isInstanceOf) {
      static ani_method double_p = nullptr;
      if (!double_p) env->Class_FindMethod(double_class, "unboxed", ":D", &double_p);
      ani_double result;
      env->Object_CallMethod_Double(valueObj, double_p, &result);
      return KLength{ 1, (KFloat) result, 1, 0 };
    }

    env->Object_InstanceOf(valueObj, int_class, &isInstanceOf);
    if (isInstanceOf) {
      static ani_method int_p = nullptr;
      if (!int_p) env->Class_FindMethod(int_class, "unboxed", ":I", &int_p);
      ani_int result;
      env->Object_CallMethod_Int(valueObj, int_p, &result);
      return KLength{ 1, (KFloat) result, 1, 0 };
    }

    env->Object_InstanceOf(valueObj, string_class, &isInstanceOf);
    if (isInstanceOf) {
      KStringPtr ptr = InteropTypeConverter<KStringPtr>::convertFrom(env, reinterpret_cast<ani_string>(value));
      KLength length { 0 };
      parseKLength(ptr, &length);
      length.type = 2;
      length.resource = 0;
      return length;
    }

    env->Object_InstanceOf(valueObj, resource_class, &isInstanceOf);
    if (isInstanceOf) {
      static ani_method resource_p = nullptr;
      if (!resource_p) env->Class_FindMethod(resource_class, "<get>id",":D", &resource_p);
      ani_double result;
      env->Object_CallMethod_Double(valueObj, resource_p, &result);
      return KLength{ 3, 0, 1, (KInt) result };
    }

    return KLength( { 0, 0, 0, 0});
  }
  static InteropType convertTo(ani_env* env, KLength value) = delete;
  static void release(ani_env* env, InteropType value, const KLength& converted) {}
};

template <typename Type>
inline typename InteropTypeConverter<Type>::InteropType makeResult(ani_env* env, Type value) {
  return InteropTypeConverter<Type>::convertTo(env, value);
}

template <typename Type>
inline Type getArgument(ani_env* env, typename InteropTypeConverter<Type>::InteropType arg) {
  return InteropTypeConverter<Type>::convertFrom(env, arg);
}

template <typename Type>
inline void releaseArgument(ani_env* env, typename InteropTypeConverter<Type>::InteropType arg, Type& data) {
  InteropTypeConverter<Type>::release(env, arg, data);
}

template<class T>
struct DirectInteropTypeConverter {
    using InteropType = T;
    static T convertFrom(InteropType value) { return value; }
    static InteropType convertTo(T value) { return value; }
};

template<>
struct DirectInteropTypeConverter<KNativePointer> {
    using InteropType = ani_long;
    static KNativePointer convertFrom(InteropType value) {
      return reinterpret_cast<KNativePointer>(value);
    }
    static InteropType convertTo(KNativePointer value) {
      return reinterpret_cast<ani_long>(value);
    }
};

template<>
struct DirectInteropTypeConverter<KSerializerBuffer> {
    using InteropType = ani_long;
    static KSerializerBuffer convertFrom(InteropType value) {
      return reinterpret_cast<KSerializerBuffer>(static_cast<intptr_t>(value));
    }
    static InteropType convertTo(KSerializerBuffer value) = delete;
};

template <>
struct DirectInteropTypeConverter<KInteropNumber> {
  using InteropType = ani_double;
  static KInteropNumber convertFrom(InteropType value) {
    return KInteropNumber::fromDouble(value);
  }
  static InteropType convertTo(KInteropNumber value) {
    return value.asDouble();
  }
};

#define ANI_SLOW_NATIVE_FLAG 1

class AniExports {
    std::unordered_map<std::string,
        std::vector<std::tuple<std::string, std::string, void*, int>>> implementations;
    std::unordered_map<std::string, std::string> classpaths;

public:
    static AniExports* getInstance();

    std::vector<std::string> getModules();
    void addMethod(const char* module, const char* name, const char* type, void* impl, int flags);
    const std::vector<std::tuple<std::string, std::string, void*, int>>& getMethods(const std::string& module);

    void setClasspath(const char* module, const char* classpath);
    const std::string& getClasspath(const std::string& module);
};

#define KOALA_QUOTE0(x) #x
#define KOALA_QUOTE(x) KOALA_QUOTE0(x)

#ifdef _MSC_VER
#define MAKE_ANI_EXPORT(module, name, type, flag)                             \
    static void __init_##name() {                               \
        AniExports::getInstance()->addMethod(KOALA_QUOTE(module), "_"#name, type, reinterpret_cast<void *>(Ani_##name), flag); \
    }                                                           \
    namespace {                                                 \
      struct __Init_##name {                                    \
        __Init_##name() {  __init_##name(); }                   \
      } __Init_##name##_v;                                      \
    }
#define KOALA_ANI_INTEROP_MODULE_CLASSPATH(module, classpath)                                 \
    static void __init_classpath_##module() {                                                 \
        AniExports::getInstance()->setClasspath(KOALA_QUOTE(module), "L" classpath ";"); \
    }                                                                                         \
    namespace {                                                                               \
      struct __Init_classpath_##module {                                                      \
        __Init_classpath_##module() {  __init_classpath_##module(); }                         \
      } __Init_classpath_##module##_v;                                                        \
    }
#else
#define MAKE_ANI_EXPORT(module, name, type, flag) \
    __attribute__((constructor)) \
    static void __init_ani_##name() { \
        AniExports::getInstance()->addMethod(KOALA_QUOTE(module), "_"#name, type, reinterpret_cast<void *>(Ani_##name), flag); \
    }
#define KOALA_ANI_INTEROP_MODULE_CLASSPATH(module, classpath)                                 \
    __attribute__((constructor))                                                              \
    static void __init_ani_classpath_##module() {                                             \
        AniExports::getInstance()->setClasspath(KOALA_QUOTE(module), "L" classpath ";"); \
    }
#endif

#define KOALA_INTEROP_0(name, Ret) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz) { \
      KOALA_MAYBE_LOG(name)                       \
      return makeResult<Ret>(env, impl_##name()); \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret, 0)

#define KOALA_INTEROP_1(name, Ret, P0) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
   InteropTypeConverter<P0>::InteropType _p0) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      auto rv = makeResult<Ret>(env, impl_##name(p0)); \
      releaseArgument(env, _p0, p0); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0, 0)

#define KOALA_INTEROP_2(name, Ret, P0, P1) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1, 0)

#define KOALA_INTEROP_3(name, Ret, P0, P1, P2) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2, 0)

#define KOALA_INTEROP_4(name, Ret, P0, P1, P2, P3) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3, 0)

#define KOALA_INTEROP_5(name, Ret, P0, P1, P2, P3, P4) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
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
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3, p4)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4, 0)

#define KOALA_INTEROP_6(name, Ret, P0, P1, P2, P3, P4, P5) \
InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
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
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3, p4, p5)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5, 0)

#define KOALA_INTEROP_7(name, Ret, P0, P1, P2, P3, P4, P5, P6) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
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
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3, p4, p5, p6)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      releaseArgument(env, _p5, p5); \
      releaseArgument(env, _p6, p6); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6, 0)

#define KOALA_INTEROP_8(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, \
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
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7)); \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7, 0)

#define KOALA_INTEROP_9(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
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
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8)); \
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
  MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8, 0)

#define KOALA_INTEROP_10(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
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
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)); \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9, 0)

#define KOALA_INTEROP_11(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
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
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)); \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10, 0)

#define KOALA_INTEROP_12(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
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
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)); \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11, 0)

#define KOALA_INTEROP_13(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
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
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)); \
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
  MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11 "|" #P12, 0)

#define KOALA_INTEROP_14(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
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
      auto rv = makeResult<Ret>(env, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)); \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11 "|" #P12 "|" #P13, 0)

#define KOALA_INTEROP_V0(name) \
  void Ani_##name(ani_env *env) { \
      KOALA_MAYBE_LOG(name)                   \
      impl_##name(); \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void", 0)

#define KOALA_INTEROP_V1(name, P0) \
  void Ani_##name(ani_env *env, ani_class clazz, \
  InteropTypeConverter<P0>::InteropType _p0) { \
    KOALA_MAYBE_LOG(name)              \
    P0 p0 = getArgument<P0>(env, _p0); \
    impl_##name(p0); \
    releaseArgument(env, _p0, p0); \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0, 0)

#define KOALA_INTEROP_V2(name, P0, P1) \
  void Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      impl_##name(p0, p1); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
   } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1, 0)

#define KOALA_INTEROP_V3(name, P0, P1, P2) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2, 0)

#define KOALA_INTEROP_V4(name, P0, P1, P2, P3) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3, 0)

#define KOALA_INTEROP_V5(name, P0, P1, P2, P3, P4) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4, 0)

#define KOALA_INTEROP_V6(name, P0, P1, P2, P3, P4, P5) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5, 0)

#define KOALA_INTEROP_V7(name, P0, P1, P2, P3, P4, P5, P6) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6, 0)

#define KOALA_INTEROP_V8(name, P0, P1, P2, P3, P4, P5, P6, P7) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7, 0)

#define KOALA_INTEROP_V9(name, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8, 0)

#define KOALA_INTEROP_V10(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9, 0)

#define KOALA_INTEROP_V11(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10, 0)

#define KOALA_INTEROP_V12(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11, 0)

#define KOALA_INTEROP_V13(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11 "|" #P12, 0)

#define KOALA_INTEROP_V14(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11 "|" #P12 "|" #P13, 0)

#define KOALA_INTEROP_V15(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14) \
  void Ani_##name(ani_env *env, ani_class clazz, \
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
} \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10 "|" #P11 "|" #P12 "|" #P13 "|" #P14, 0)

#define KOALA_INTEROP_CTX_0(name, Ret) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz) { \
      KOALA_MAYBE_LOG(name)                   \
      KVMContext ctx = (KVMContext)env; \
      auto rv = makeResult<Ret>(env, impl_##name(ctx)); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_1(name, Ret, P0) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
   InteropTypeConverter<P0>::InteropType _p0) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      KVMContext ctx = (KVMContext)env; \
      auto rv = makeResult<Ret>(env, impl_##name(ctx, p0)); \
      releaseArgument(env, _p0, p0); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_2(name, Ret, P0, P1) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      KVMContext ctx = (KVMContext)env; \
      auto rv = makeResult<Ret>(env, impl_##name(ctx, p0, p1)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_3(name, Ret, P0, P1, P2) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      KVMContext ctx = (KVMContext)env; \
      auto rv = makeResult<Ret>(env, impl_##name(ctx, p0, p1, p2)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_4(name, Ret, P0, P1, P2, P3) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      KVMContext ctx = (KVMContext)env; \
      auto rv = makeResult<Ret>(env, impl_##name(ctx, p0, p1, p2, p3)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_5(name, Ret, P0, P1, P2, P3, P4) \
  InteropTypeConverter<Ret>::InteropType Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      P3 p3 = getArgument<P3>(env, _p3); \
      P4 p4 = getArgument<P4>(env, _p4); \
      KVMContext ctx = (KVMContext)env; \
      auto rv = makeResult<Ret>(env, impl_##name(ctx, p0, p1, p2, p3, p4)); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
      releaseArgument(env, _p3, p3); \
      releaseArgument(env, _p4, p4); \
      return rv; \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_V0(name)  \
  void Ani_##name(ani_env *env, ani_class clazz) { \
      KOALA_MAYBE_LOG(name)                   \
      KVMContext ctx = (KVMContext)env; \
      impl_##name(ctx); \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void", ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_V1(name, P0)  \
  void Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      KVMContext ctx = (KVMContext)env; \
      impl_##name(ctx, p0); \
      releaseArgument(env, _p0, p0); \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_V2(name, P0, P1)  \
  void Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      KVMContext ctx = (KVMContext)env; \
      impl_##name(ctx, p0, p1); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_V3(name, P0, P1, P2)  \
  void Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(env, _p0); \
      P1 p1 = getArgument<P1>(env, _p1); \
      P2 p2 = getArgument<P2>(env, _p2); \
      KVMContext ctx = (KVMContext)env; \
      impl_##name(ctx, p0, p1, p2); \
      releaseArgument(env, _p0, p0); \
      releaseArgument(env, _p1, p1); \
      releaseArgument(env, _p2, p2); \
  } \
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_V4(name, P0, P1, P2, P3)  \
  void Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name)                   \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_CTX_V5(name, P0, P1, P2, P3, P4)  \
  void Ani_##name(ani_env *env, ani_class clazz, \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4) { \
      KOALA_MAYBE_LOG(name)                   \
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
MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4, ANI_SLOW_NATIVE_FLAG)

#define KOALA_INTEROP_DIRECT_0(name, Ret) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name()); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret, 0)
#define KOALA_INTEROP_DIRECT_1(name, Ret, P0) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0, 0)
#define KOALA_INTEROP_DIRECT_2(name, Ret, P0, P1) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1, 0)
#define KOALA_INTEROP_DIRECT_3(name, Ret, P0, P1, P2) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2, 0)
#define KOALA_INTEROP_DIRECT_4(name, Ret, P0, P1, P2, P3) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3, 0)
#define KOALA_INTEROP_DIRECT_5(name, Ret, P0, P1, P2, P3, P4) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4, 0)
#define KOALA_INTEROP_DIRECT_6(name, Ret, P0, P1, P2, P3, P4, P5) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5, 0)
#define KOALA_INTEROP_DIRECT_7(name, Ret, P0, P1, P2, P3, P4, P5, P6) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5, \
        InteropTypeConverter<P6>::InteropType p6 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5), DirectInteropTypeConverter<P6>::convertFrom(p6))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6, 0)
#define KOALA_INTEROP_DIRECT_8(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5, \
        InteropTypeConverter<P6>::InteropType p6, \
        InteropTypeConverter<P7>::InteropType p7 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5), DirectInteropTypeConverter<P6>::convertFrom(p6), DirectInteropTypeConverter<P7>::convertFrom(p7))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7, 0)
#define KOALA_INTEROP_DIRECT_9(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5, \
        InteropTypeConverter<P6>::InteropType p6, \
        InteropTypeConverter<P7>::InteropType p7, \
        InteropTypeConverter<P8>::InteropType p8 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5), DirectInteropTypeConverter<P6>::convertFrom(p6), DirectInteropTypeConverter<P7>::convertFrom(p7), DirectInteropTypeConverter<P8>::convertFrom(p8))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8, 0)
#define KOALA_INTEROP_DIRECT_10(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5, \
        InteropTypeConverter<P6>::InteropType p6, \
        InteropTypeConverter<P7>::InteropType p7, \
        InteropTypeConverter<P8>::InteropType p8, \
        InteropTypeConverter<P9>::InteropType p9 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5), DirectInteropTypeConverter<P6>::convertFrom(p6), DirectInteropTypeConverter<P7>::convertFrom(p7), DirectInteropTypeConverter<P8>::convertFrom(p8), DirectInteropTypeConverter<P9>::convertFrom(p9))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9, 0)
#define KOALA_INTEROP_DIRECT_11(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
    inline InteropTypeConverter<Ret>::InteropType Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5, \
        InteropTypeConverter<P6>::InteropType p6, \
        InteropTypeConverter<P7>::InteropType p7, \
        InteropTypeConverter<P8>::InteropType p8, \
        InteropTypeConverter<P9>::InteropType p9, \
        InteropTypeConverter<P10>::InteropType p10 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        return DirectInteropTypeConverter<Ret>::convertTo(impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5), DirectInteropTypeConverter<P6>::convertFrom(p6), DirectInteropTypeConverter<P7>::convertFrom(p7), DirectInteropTypeConverter<P8>::convertFrom(p8), DirectInteropTypeConverter<P9>::convertFrom(p9), DirectInteropTypeConverter<P10>::convertFrom(p10))); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, #Ret "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10, 0)
#define KOALA_INTEROP_DIRECT_V0(name) \
    inline void Ani_##name( \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void", 0)
#define KOALA_INTEROP_DIRECT_V1(name, P0) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0, 0)
#define KOALA_INTEROP_DIRECT_V2(name, P0, P1) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0 "|" #P1, 0)
#define KOALA_INTEROP_DIRECT_V3(name, P0, P1, P2) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0 "|" #P1 "|" #P2, 0)
#define KOALA_INTEROP_DIRECT_V4(name, P0, P1, P2, P3) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0 "|" #P1 "|" #P2 "|" #P3, 0)
#define KOALA_INTEROP_DIRECT_V5(name, P0, P1, P2, P3, P4) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4, 0)
#define KOALA_INTEROP_DIRECT_V6(name, P0, P1, P2, P3, P4, P5) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5, 0)
#define KOALA_INTEROP_DIRECT_V7(name, P0, P1, P2, P3, P4, P5, P6) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5, \
        InteropTypeConverter<P6>::InteropType p6 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5), DirectInteropTypeConverter<P6>::convertFrom(p6)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6, 0)
#define KOALA_INTEROP_DIRECT_V8(name, P0, P1, P2, P3, P4, P5, P6, P7) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5, \
        InteropTypeConverter<P6>::InteropType p6, \
        InteropTypeConverter<P7>::InteropType p7 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5), DirectInteropTypeConverter<P6>::convertFrom(p6), DirectInteropTypeConverter<P7>::convertFrom(p7)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7, 0)
#define KOALA_INTEROP_DIRECT_V9(name, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5, \
        InteropTypeConverter<P6>::InteropType p6, \
        InteropTypeConverter<P7>::InteropType p7, \
        InteropTypeConverter<P8>::InteropType p8 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5), DirectInteropTypeConverter<P6>::convertFrom(p6), DirectInteropTypeConverter<P7>::convertFrom(p7), DirectInteropTypeConverter<P8>::convertFrom(p8)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8, 0)
#define KOALA_INTEROP_DIRECT_V10(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5, \
        InteropTypeConverter<P6>::InteropType p6, \
        InteropTypeConverter<P7>::InteropType p7, \
        InteropTypeConverter<P8>::InteropType p8, \
        InteropTypeConverter<P9>::InteropType p9 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5), DirectInteropTypeConverter<P6>::convertFrom(p6), DirectInteropTypeConverter<P7>::convertFrom(p7), DirectInteropTypeConverter<P8>::convertFrom(p8), DirectInteropTypeConverter<P9>::convertFrom(p9)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9, 0)
#define KOALA_INTEROP_DIRECT_V11(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
    inline void Ani_##name( \
        InteropTypeConverter<P0>::InteropType p0, \
        InteropTypeConverter<P1>::InteropType p1, \
        InteropTypeConverter<P2>::InteropType p2, \
        InteropTypeConverter<P3>::InteropType p3, \
        InteropTypeConverter<P4>::InteropType p4, \
        InteropTypeConverter<P5>::InteropType p5, \
        InteropTypeConverter<P6>::InteropType p6, \
        InteropTypeConverter<P7>::InteropType p7, \
        InteropTypeConverter<P8>::InteropType p8, \
        InteropTypeConverter<P9>::InteropType p9, \
        InteropTypeConverter<P10>::InteropType p10 \
    ) { \
        KOALA_MAYBE_LOG(name) \
        impl_##name(DirectInteropTypeConverter<P0>::convertFrom(p0), DirectInteropTypeConverter<P1>::convertFrom(p1), DirectInteropTypeConverter<P2>::convertFrom(p2), DirectInteropTypeConverter<P3>::convertFrom(p3), DirectInteropTypeConverter<P4>::convertFrom(p4), DirectInteropTypeConverter<P5>::convertFrom(p5), DirectInteropTypeConverter<P6>::convertFrom(p6), DirectInteropTypeConverter<P7>::convertFrom(p7), DirectInteropTypeConverter<P8>::convertFrom(p8), DirectInteropTypeConverter<P9>::convertFrom(p9), DirectInteropTypeConverter<P10>::convertFrom(p10)); \
    } \
    MAKE_ANI_EXPORT(KOALA_INTEROP_MODULE, name, "void" "|" #P0 "|" #P1 "|" #P2 "|" #P3 "|" #P4 "|" #P5 "|" #P6 "|" #P7 "|" #P8 "|" #P9 "|" #P10, 0)

bool setKoalaANICallbackDispatcher(
    ani_env* ani_env,
    ani_class clazz,
    const char* dispatcherMethodName,
    const char* dispactherMethodSig
);
void getKoalaANICallbackDispatcher(ani_class* clazz, ani_static_method* method);

// TODO: maybe use CreateArrayBufferExternal here instead, no need for allocations.
#define KOALA_INTEROP_CALL_VOID(venv, id, length, args)                                \
{                                                                                      \
  ani_class clazz = nullptr;                                                           \
  ani_static_method method = nullptr;                                                  \
  getKoalaANICallbackDispatcher(&clazz, &method);                                      \
  ani_env* env = reinterpret_cast<ani_env*>(venv);                            \
  ani_int result = 0;                                                                  \
  env->Class_CallStaticMethod_Int(clazz, method, &result, id, args, length); \
}

#define KOALA_INTEROP_CALL_INT(venv, id, length, args)                                       \
{                                                                                            \
    ani_class clazz = nullptr;                                                               \
    ani_static_method method = nullptr;                                                      \
    getKoalaANICallbackDispatcher(&clazz, &method);                                          \
    ani_env* env = reinterpret_cast<ani_env*>(venv);                                         \
    ani_int result = 0;                                                                      \
    env->Class_CallStaticMethod_Int(clazz, method, &result, id, args, length);       \
    return result;                                                                           \
}

#define KOALA_INTEROP_CALL_VOID_INTS32(venv, id, argc, args) KOALA_INTEROP_CALL_VOID(venv, id, (argc) * sizeof(int32_t), args)
#define KOALA_INTEROP_CALL_INT_INTS32(venv, id, argc, args) KOALA_INTEROP_CALL_INT(venv, id, (argc) * sizeof(int32_t), args)

#define KOALA_INTEROP_THROW(vmContext, object, ...) \
   do { \
     ani_env* env = reinterpret_cast<ani_env*>(vmContext); \
     env->ThrowError(object); \
     return __VA_ARGS__;  \
   } while (0)

#define KOALA_INTEROP_THROW_STRING(vmContext, message, ...) \
  do { \
    ani_env* env = reinterpret_cast<ani_env*>(vmContext); \
    ani_class errorClass = nullptr; \
    env->FindClass("Lstd/core/Error;", &errorClass); \
    ani_method errorCtor = nullptr; \
    env->Class_FindMethod(errorClass, "<init>", "Lstd/core/Error;", &errorCtor); \
    ani_error messageObject = nullptr; \
    env->Object_New(errorClass, errorCtor, (ani_object*)&messageObject, message); \
    env->ThrowError(messageObject); \
  } while (0)

#endif // KOALA_ANI
