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
    static T convertFrom(ani_env* env, InteropType value) { return value; }
    static InteropType convertTo(ani_env* env, T value) { return value; }
    static void release(ani_env* env, InteropType value, T converted) {}
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
        ani_size count;
        env->String_GetUTF8SubString(value, 0, lengthUtf16, result.data(), result.length(), &count);
        return result;
    }
    static InteropType convertTo(ani_env* env, const KStringPtr& value) {
      ani_string result;
      env->String_NewUTF8(value.c_str(), value.length(), &result);
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
    using InteropType = ani_fixedarray_int;
    static KInt* convertFrom(ani_env* env, InteropType value) {
      if (!value) return nullptr;
      ani_size length = 0;
      env->FixedArray_GetLength(value, &length);
      KInt* result = new KInt[length];
      env->FixedArray_GetRegion_Int(value, 0, length, result);
      return result;
    }
    static InteropType convertTo(ani_env* env, KInt* value) = delete;
    static void release(ani_env* env, InteropType value, KInt* converted) {
      if (converted) delete [] converted;
    }
};

template<>
struct InteropTypeConverter<KFloat*> {
    using InteropType = ani_fixedarray_float;
    static KFloat* convertFrom(ani_env* env, InteropType value) {
      if (!value) return nullptr;
      ani_size length = 0;
      env->FixedArray_GetLength(value, &length);
      KFloat* result = new KFloat[length];
      env->FixedArray_GetRegion_Float(value, 0, length, result);
      return result;
    }
    static InteropType convertTo(ani_env* env, KFloat* value) = delete;
    static void release(ani_env* env, InteropType value, KFloat* converted) {
      if (converted) delete [] converted;
    }
};

template<>
struct InteropTypeConverter<KByte*> {
    using InteropType = ani_fixedarray_byte;
    static KByte* convertFrom(ani_env* env, InteropType value) {
      if (!value) return nullptr;
      ani_size length = 0;
      env->FixedArray_GetLength(value, &length);
      KByte* result = new KByte[length];
      env->FixedArray_GetRegion_Byte(value, 0, length, (ani_byte*)result);
      return result;
    }
    static InteropType convertTo(ani_env* env, KByte* value) = delete;
    static void release(ani_env* env, InteropType value, KByte* converted) {
      if (converted) delete [] converted;
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
    // TODO: implement me
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
        AniExports::getInstance()->setClasspath(KOALA_QUOTE(module), classpath); \
    }                                                                                         \
    namespace {                                                                               \
      struct __Init_classpath_##module {                                                      \
        __Init_classpath_##module() {  __init_classpath_##module(); }                         \
      } __Init_classpath_##module##_v;                                                        \
    }
#else
#define MAKE_ANI_EXPORT(module, name, type, flag) \
    __attribute__((constructor)) \
    static void __init_ets_##name() { \
        AniExports::getInstance()->addMethod(KOALA_QUOTE(module), "_"#name, type, reinterpret_cast<void *>(Ani_##name), flag); \
    }
#define KOALA_ANI_INTEROP_MODULE_CLASSPATH(module, classpath)                                 \
    __attribute__((constructor))                                                              \
    static void __init_ani_classpath_##module() {                                             \
        AniExports::getInstance()->setClasspath(KOALA_QUOTE(module), classpath); \
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

bool setKoalaEtsNapiCallbackDispatcher(
    ani_env* ani_env,
    ani_class clazz,
    const char* dispatcherMethodName,
    const char* dispactherMethodSig
);
void getKoalaEtsNapiCallbackDispatcher(ani_class* clazz, ani_method* method);

#if 0
#define KOALA_INTEROP_CALL_VOID(venv, id, length, args)                               \
{                                                                                     \
  ani_class clazz = nullptr;                                                          \
  ani_method method = nullptr;                                                        \
  getKoalaEtsNapiCallbackDispatcher(&clazz, &method);                                 \
  ani_env* ani_env = reinterpret_cast<ani_env*>(vmContext);                              \
  ani_env->PushLocalFrame(1);                                                          \
  ani_fixedarray_byte args_ets = ani_env->NewByteArray(length);                              \
  ani_env->SetByteArrayRegion(args_ets, 0, length, reinterpret_cast<ets_byte*>(args)); \
  ani_env->CallStaticIntMethod(clazz, method, id, args_ets, length);                   \
  ani_env->GetByteArrayRegion(args_ets, 0, length, reinterpret_cast<ets_byte*>(args)); \
  ani_env->PopLocalFrame(nullptr);                                                     \
}

#define KOALA_INTEROP_CALL_INT(venv, id, length, args)                                \
{                                                                                     \
  ani_class clazz = nullptr;                                                          \
  ani_method method = nullptr;                                                        \
  getKoalaEtsNapiCallbackDispatcher(&clazz, &method);                                 \
  ani_env* ani_env = reinterpret_cast<ani_env*>(venv);                              \
  ani_env->PushLocalFrame(1);                                                          \
  ani_fixedarray_byte args_ets = ani_env->NewByteArray(length);                              \
  ani_env->SetByteArrayRegion(args_ets, 0, length, reinterpret_cast<ets_byte*>(args)); \
  int32_t rv = ani_env->CallStaticIntMethod(clazz, method, id, args_ets, length);      \
  ani_env->GetByteArrayRegion(args_ets, 0, length, reinterpret_cast<ets_byte*>(args)); \
  ani_env->PopLocalFrame(nullptr);                                                     \
  return rv;                                                                          \
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
    const static ani_class errorClass = env->FindClass("std/core/Error"); \
    env->ThrowErrorNew(errorClass, message); \
  } while (0)
#else

#define KOALA_INTEROP_CALL_VOID(venv, id, length, args)
#define KOALA_INTEROP_CALL_INT(venv, id, length, args) { return 0; }
#define KOALA_INTEROP_CALL_VOID_INTS32(venv, id, argc, args) { return; }
#define KOALA_INTEROP_CALL_INT_INTS32(venv, id, argc, args) { return 0; }
#define KOALA_INTEROP_THROW(vmContext, object, ...) { return __VA_ARGS__; }
#define KOALA_INTEROP_THROW_STRING(vmContext, message, ...) { return __VA_ARGS__; }
#endif

#endif // KOALA_ETS_NAPI
