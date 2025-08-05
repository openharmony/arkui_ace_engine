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

#ifndef CONVERTORS_KOTLIN_H
#define CONVERTORS_KOTLIN_H

#ifdef KOALA_KOTLIN

#include <exception>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "koala-types.h"
#include "interop-logging.h"
#include "interop-utils.h"

struct KotlinInteropBuffer {
    int32_t length;
    void *data;
};

template<class T>
struct InteropTypeConverter {
    using InteropType = T;
    static T convertFrom(InteropType value) = delete;
    static InteropType convertTo(T value) = delete;
    static void release(InteropType value, T converted) {}
};

template<>
struct InteropTypeConverter<KByte> {
    using InteropType = uint8_t;
    static inline KByte convertFrom(InteropType value) {
      return value;
    }
    static inline InteropType convertTo(KByte value) {
      return value;
    }
    static inline void release(InteropType value, KByte converted) {}
};

template<>
struct InteropTypeConverter<KBoolean> {
    using InteropType = int8_t;
    static inline KBoolean convertFrom(InteropType value) {
      return value;
    }
    static inline InteropType convertTo(KBoolean value) {
      return value;
    }
    static inline void release(InteropType value, KBoolean converted) {}
};

template<>
struct InteropTypeConverter<KInt> {
    using InteropType = int32_t;
    static inline KInt convertFrom(InteropType value) {
      return value;
    }
    static inline InteropType convertTo(KInt value) {
      return value;
    }
    static inline void release(InteropType value, KInt converted) {}
};

template<>
struct InteropTypeConverter<KUInt> {
    using InteropType = uint32_t;
    static inline KUInt convertFrom(InteropType value) {
      return value;
    }
    static inline InteropType convertTo(KUInt value) {
      return value;
    }
    static inline void release(InteropType value, KUInt converted) {}
};


template<>
struct InteropTypeConverter<KFloat> {
    using InteropType = float;
    static inline KFloat convertFrom(InteropType value) {
      return value;
    }
    static inline InteropType convertTo(KFloat value) {
      return value;
    }
    static inline void release(InteropType value, KFloat converted) {}
};

template<>
struct InteropTypeConverter<KLong> {
    using InteropType = int64_t;
    static inline KLong convertFrom(InteropType value) {
      return value;
    }
    static inline InteropType convertTo(KLong value) {
      return value;
    }
    static inline void release(InteropType value, KLong converted) {}
};

template<>
struct InteropTypeConverter<KVMObjectHandle> {
    using InteropType = void*;
    static inline KVMObjectHandle convertFrom(InteropType value) {
      return reinterpret_cast<KVMObjectHandle>(value);
    }
    static inline InteropType convertTo(KVMObjectHandle value) {
      return reinterpret_cast<InteropType>(value);
    }
    static inline void release(InteropType value, KVMObjectHandle converted) {}
};

// Improve: do we really need this converter?
template<>
struct InteropTypeConverter<KInteropBuffer> {
    using InteropType = KotlinInteropBuffer;
    static inline KInteropBuffer convertFrom(InteropType value) {
      KInteropBuffer result = { 0 };
      result.data = value.data;
      result.length = value.length;
      return result;
    }
    static inline InteropType convertTo(KInteropBuffer value) {
      // Improve: can we use KInteropBuffer::data without copying?
      void *data = nullptr;
      if (value.length > 0) {
        data = malloc(value.length);
        if (!data) {
          INTEROP_FATAL("Cannot allocate memory");
        }
        interop_memcpy(data, value.length, value.data, value.length);
      }
      InteropType result = {
        .length = static_cast<int32_t>(value.length),
        .data = data,
      };
      value.dispose(value.resourceId);
      return result;
    }
    static inline void release(InteropType value, KInteropBuffer converted) {}
};

template<>
struct InteropTypeConverter<KSerializerBuffer> {
    using InteropType = void*;
    static KSerializerBuffer convertFrom(InteropType value) {
      return reinterpret_cast<KSerializerBuffer>(value);
    }
    static InteropType convertTo(KSerializerBuffer value) = delete;
    static inline void release(InteropType value, KSerializerBuffer converted) {}
};

template<>
struct InteropTypeConverter<KInteropReturnBuffer> {
    using InteropType = KotlinInteropBuffer;
    static inline KInteropReturnBuffer convertFrom(InteropType value) = delete;
    static inline InteropType convertTo(KInteropReturnBuffer value) {
      InteropType result = {
        .length = value.length,
        .data = value.data,
      };
      return result;
    };
    static inline void release(InteropType value, KInteropReturnBuffer converted) {}
};

template<>
struct InteropTypeConverter<KStringPtr> {
    using InteropType = const char*;
    static KStringPtr convertFrom(InteropType value) {
        return KStringPtr(value);
    }
    static InteropType convertTo(const KStringPtr& value) {
      // Improve: can we return KStringPtr::_value without copying?
      if (!value.c_str()) {
        return nullptr;
      }
      size_t bufferSize = value.length() + 1;
      char *result = reinterpret_cast<char*>(malloc(bufferSize));
      if (!result) {
        INTEROP_FATAL("Cannot allocate memory");
      }
      interop_strcpy(result, bufferSize, value.c_str());
      return result;
    }
    static void release(InteropType value, const KStringPtr& converted) {}
};

template<>
struct InteropTypeConverter<KNativePointer> {
    using InteropType = void*;
    static KNativePointer convertFrom(InteropType value) {
      return value;
    }
    static InteropType convertTo(KNativePointer value) {
      return value;
    }
    static void release(InteropType value, KNativePointer converted) {}
};

template<>
struct InteropTypeConverter<KInt*> {
    using InteropType = KInt*;
    static KInt* convertFrom(InteropType value) {
      return value;
    }
    static InteropType convertTo(KInt* value) = delete;
    static void release(InteropType value, KInt* converted) {}
};

template<>
struct InteropTypeConverter<KFloat*> {
    using InteropType = KFloat*;
    static KFloat* convertFrom(InteropType value) {
      return value;
    }
    static InteropType convertTo(KFloat* value) = delete;
    static void release(InteropType value, KFloat* converted) {}
};

template<>
struct InteropTypeConverter<KByte*> {
    using InteropType = KByte*;
    static KByte* convertFrom(InteropType value) {
      return value;
    }
    static InteropType convertTo(KByte* value) = delete;
    static void release(InteropType value, KByte* converted) {}
};

template <> struct InteropTypeConverter<KInteropNumber> {
  using InteropType = double;
  static KInteropNumber convertFrom(InteropType value) {
    return KInteropNumber::fromDouble(value);
  }
  static InteropType convertTo(KInteropNumber value) {
    return value.asDouble();
  }
  static void release(InteropType value, KInteropNumber converted) {}
};

template <typename Type>
inline typename InteropTypeConverter<Type>::InteropType makeResult(Type value) {
  return InteropTypeConverter<Type>::convertTo(value);
}

template <typename Type>
inline Type getArgument(typename InteropTypeConverter<Type>::InteropType arg) {
  return InteropTypeConverter<Type>::convertFrom(arg);
}

template <typename Type>
inline void releaseArgument(typename InteropTypeConverter<Type>::InteropType arg, Type& data) {
  InteropTypeConverter<Type>::release(arg, data);
}

#define KOALA_QUOTE0(x) #x
#define KOALA_QUOTE(x) KOALA_QUOTE0(x)

#define KOTLIN_EXPORT extern "C"

#define KOTLIN_PREFIX(name) kotlin_##name

#define KOALA_INTEROP_0(name, Ret) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)() { \
      KOALA_MAYBE_LOG(name)                       \
      return makeResult<Ret>(impl_##name()); \
  }

#define KOALA_INTEROP_1(name, Ret, P0) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
   InteropTypeConverter<P0>::InteropType _p0) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      auto rv = makeResult<Ret>(impl_##name(p0)); \
      releaseArgument(_p0, p0); \
      return rv; \
  }

#define KOALA_INTEROP_2(name, Ret, P0, P1) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      return rv; \
  }

#define KOALA_INTEROP_3(name, Ret, P0, P1, P2) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      return rv; \
  }

#define KOALA_INTEROP_4(name, Ret, P0, P1, P2, P3) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      return rv; \
  }

#define KOALA_INTEROP_5(name, Ret, P0, P1, P2, P3, P4) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3, p4)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      return rv; \
  }

#define KOALA_INTEROP_6(name, Ret, P0, P1, P2, P3, P4, P5) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5) { \
        KOALA_MAYBE_LOG(name) \
        P0 p0 = getArgument<P0>(_p0); \
        P1 p1 = getArgument<P1>(_p1); \
        P2 p2 = getArgument<P2>(_p2); \
        P3 p3 = getArgument<P3>(_p3); \
        P4 p4 = getArgument<P4>(_p4); \
        P5 p5 = getArgument<P5>(_p5); \
        auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3, p4, p5)); \
        releaseArgument(_p0, p0); \
        releaseArgument(_p1, p1); \
        releaseArgument(_p2, p2); \
        releaseArgument(_p3, p3); \
        releaseArgument(_p4, p4); \
        releaseArgument(_p5, p5); \
        return rv; \
    }

#define KOALA_INTEROP_7(name, Ret, P0, P1, P2, P3, P4, P5, P6) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5, \
    InteropTypeConverter<P6>::InteropType _p6) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3, p4, p5, p6)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      return rv; \
  }

#define KOALA_INTEROP_8(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5, \
    InteropTypeConverter<P6>::InteropType _p6, \
    InteropTypeConverter<P7>::InteropType _p7) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3, p4, p5, p6, p7)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      return rv; \
  }

#define KOALA_INTEROP_9(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      return rv; \
  }

#define KOALA_INTEROP_10(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
      return rv; \
   }

#define KOALA_INTEROP_11(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      P10 p10 = getArgument<P10>(_p10); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
      releaseArgument(_p10, p10); \
      return rv; \
  }

#define KOALA_INTEROP_12(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      P10 p10 = getArgument<P10>(_p10); \
      P11 p11 = getArgument<P11>(_p11); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
      releaseArgument(_p10, p10); \
      releaseArgument(_p11, p11); \
      return rv; \
  }

#define KOALA_INTEROP_13(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      P10 p10 = getArgument<P10>(_p10); \
      P11 p11 = getArgument<P11>(_p11); \
      P12 p12 = getArgument<P12>(_p12); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
      releaseArgument(_p10, p10); \
      releaseArgument(_p11, p11); \
      releaseArgument(_p12, p12); \
      return rv; \
  }

#define KOALA_INTEROP_14(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      P10 p10 = getArgument<P10>(_p10); \
      P11 p11 = getArgument<P11>(_p11); \
      P12 p12 = getArgument<P12>(_p12); \
      P13 p13 = getArgument<P13>(_p13); \
      auto rv = makeResult<Ret>(impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
      releaseArgument(_p10, p10); \
      releaseArgument(_p11, p11); \
      releaseArgument(_p12, p12); \
      releaseArgument(_p13, p13); \
      return rv; \
    }

#define KOALA_INTEROP_V0(name) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)() { \
      KOALA_MAYBE_LOG(name)                   \
      impl_##name(); \
  }

#define KOALA_INTEROP_V1(name, P0) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
  InteropTypeConverter<P0>::InteropType _p0) { \
    KOALA_MAYBE_LOG(name)              \
    P0 p0 = getArgument<P0>(_p0); \
    impl_##name(p0); \
    releaseArgument(_p0, p0); \
  }

#define KOALA_INTEROP_V2(name, P0, P1) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      impl_##name(p0, p1); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
   }

#define KOALA_INTEROP_V3(name, P0, P1, P2) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      impl_##name(p0, p1, p2); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
  }

#define KOALA_INTEROP_V4(name, P0, P1, P2, P3) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      impl_##name(p0, p1, p2, p3); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
}

#define KOALA_INTEROP_V5(name, P0, P1, P2, P3, P4) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      impl_##name(p0, p1, p2, p3, p4); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
}

#define KOALA_INTEROP_V6(name, P0, P1, P2, P3, P4, P5) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      impl_##name(p0, p1, p2, p3, p4, p5); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
  }

#define KOALA_INTEROP_V7(name, P0, P1, P2, P3, P4, P5, P6) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5, \
    InteropTypeConverter<P6>::InteropType _p6) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
  }

#define KOALA_INTEROP_V8(name, P0, P1, P2, P3, P4, P5, P6, P7) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4, \
    InteropTypeConverter<P5>::InteropType _p5, \
    InteropTypeConverter<P6>::InteropType _p6, \
    InteropTypeConverter<P7>::InteropType _p7) { \
      KOALA_MAYBE_LOG(name) \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
  }

#define KOALA_INTEROP_V9(name, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
  }

#define KOALA_INTEROP_V10(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
}

#define KOALA_INTEROP_V11(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      P10 p10 = getArgument<P10>(_p10); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
      releaseArgument(_p10, p10); \
  }

#define KOALA_INTEROP_V12(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      P10 p10 = getArgument<P10>(_p10); \
      P11 p11 = getArgument<P11>(_p11); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
      releaseArgument(_p10, p10); \
      releaseArgument(_p11, p11); \
}

#define KOALA_INTEROP_V13(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      P10 p10 = getArgument<P10>(_p10); \
      P11 p11 = getArgument<P11>(_p11); \
      P12 p12 = getArgument<P12>(_p12); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
      releaseArgument(_p10, p10); \
      releaseArgument(_p11, p11); \
      releaseArgument(_p12, p12); \
}

#define KOALA_INTEROP_V14(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      P10 p10 = getArgument<P10>(_p10); \
      P11 p11 = getArgument<P11>(_p11); \
      P12 p12 = getArgument<P12>(_p12); \
      P13 p13 = getArgument<P13>(_p13); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
      releaseArgument(_p10, p10); \
      releaseArgument(_p11, p11); \
      releaseArgument(_p12, p12); \
      releaseArgument(_p13, p13); \
}

#define KOALA_INTEROP_V15(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14) \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
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
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      P5 p5 = getArgument<P5>(_p5); \
      P6 p6 = getArgument<P6>(_p6); \
      P7 p7 = getArgument<P7>(_p7); \
      P8 p8 = getArgument<P8>(_p8); \
      P9 p9 = getArgument<P9>(_p9); \
      P10 p10 = getArgument<P10>(_p10); \
      P11 p11 = getArgument<P11>(_p11); \
      P12 p12 = getArgument<P12>(_p12); \
      P13 p13 = getArgument<P13>(_p13); \
      P14 p14 = getArgument<P14>(_p14); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      releaseArgument(_p5, p5); \
      releaseArgument(_p6, p6); \
      releaseArgument(_p7, p7); \
      releaseArgument(_p8, p8); \
      releaseArgument(_p9, p9); \
      releaseArgument(_p10, p10); \
      releaseArgument(_p11, p11); \
      releaseArgument(_p12, p12); \
      releaseArgument(_p13, p13); \
      releaseArgument(_p14, p14); \
}

#define KOALA_INTEROP_CTX_0(name, Ret) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)() { \
      KOALA_MAYBE_LOG(name)                   \
      KVMContext ctx = (KVMContext)nullptr; \
      auto rv = makeResult<Ret>(impl_##name(ctx)); \
      return rv; \
  }

#define KOALA_INTEROP_CTX_1(name, Ret, P0) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      KVMContext ctx = (KVMContext)nullptr; \
      auto rv = makeResult<Ret>(impl_##name(ctx, p0)); \
      releaseArgument(_p0, p0); \
      return rv; \
  }

#define KOALA_INTEROP_CTX_2(name, Ret, P0, P1) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      KVMContext ctx = (KVMContext)nullptr; \
      auto rv = makeResult<Ret>(impl_##name(ctx, p0, p1)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      return rv; \
  }

#define KOALA_INTEROP_CTX_3(name, Ret, P0, P1, P2) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      KVMContext ctx = (KVMContext)nullptr; \
      auto rv = makeResult<Ret>(impl_##name(ctx, p0, p1, p2)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      return rv; \
  }

#define KOALA_INTEROP_CTX_4(name, Ret, P0, P1, P2, P3) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      KVMContext ctx = (KVMContext)nullptr; \
      auto rv = makeResult<Ret>(impl_##name(ctx, p0, p1, p2, p3)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      return rv; \
  }

#define KOALA_INTEROP_CTX_5(name, Ret, P0, P1, P2, P3, P4) \
  KOTLIN_EXPORT InteropTypeConverter<Ret>::InteropType KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      KVMContext ctx = (KVMContext)nullptr; \
      auto rv = makeResult<Ret>(impl_##name(ctx, p0, p1, p2, p3, p4)); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
      return rv; \
  }

#define KOALA_INTEROP_CTX_V0(name)  \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)() { \
      KOALA_MAYBE_LOG(name)                   \
      KVMContext ctx = (KVMContext)nullptr; \
      impl_##name(ctx); \
  }

#define KOALA_INTEROP_CTX_V1(name, P0)  \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      KVMContext ctx = (KVMContext)nullptr; \
      impl_##name(ctx, p0); \
      releaseArgument(_p0, p0); \
  }

#define KOALA_INTEROP_CTX_V2(name, P0, P1)  \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      KVMContext ctx = (KVMContext)nullptr; \
      impl_##name(ctx, p0, p1); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
  }

#define KOALA_INTEROP_CTX_V3(name, P0, P1, P2)  \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      KVMContext ctx = (KVMContext)nullptr; \
      impl_##name(ctx, p0, p1, p2); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
  }

#define KOALA_INTEROP_CTX_V4(name, P0, P1, P2, P3)  \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      KVMContext ctx = (KVMContext)nullptr; \
      impl_##name(ctx, p0, p1, p2, p3); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
  }

#define KOALA_INTEROP_CTX_V5(name, P0, P1, P2, P3, P4)  \
  KOTLIN_EXPORT void KOTLIN_PREFIX(name)( \
    InteropTypeConverter<P0>::InteropType _p0, \
    InteropTypeConverter<P1>::InteropType _p1, \
    InteropTypeConverter<P2>::InteropType _p2, \
    InteropTypeConverter<P3>::InteropType _p3, \
    InteropTypeConverter<P4>::InteropType _p4) { \
      KOALA_MAYBE_LOG(name)                   \
      P0 p0 = getArgument<P0>(_p0); \
      P1 p1 = getArgument<P1>(_p1); \
      P2 p2 = getArgument<P2>(_p2); \
      P3 p3 = getArgument<P3>(_p3); \
      P4 p4 = getArgument<P4>(_p4); \
      KVMContext ctx = (KVMContext)nullptr; \
      impl_##name(ctx, p0, p1, p2, p3, p4); \
      releaseArgument(_p0, p0); \
      releaseArgument(_p1, p1); \
      releaseArgument(_p2, p2); \
      releaseArgument(_p3, p3); \
      releaseArgument(_p4, p4); \
  }

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

void callKoalaKotlinCallbackVoid(KInt id, KInt length, KSerializerBuffer buffer);
KInt callKoalaKotlinCallbackInt(KInt id, KInt length, KSerializerBuffer buffer);

#define KOALA_INTEROP_CALL_VOID(venv, id, length, args)                                                 \
{                                                                                                       \
  callKoalaKotlinCallbackVoid(id, length, reinterpret_cast<KSerializerBuffer>(args));                   \
}

#define KOALA_INTEROP_CALL_INT(venv, id, length, args)                                                  \
{                                                                                                       \
  KInt result = callKoalaKotlinCallbackInt(id, length, reinterpret_cast<KSerializerBuffer>(args));      \
  return result;                                                                                        \
}

#define KOALA_INTEROP_CALL_VOID_INTS32(venv, id, argc, args) KOALA_INTEROP_CALL_VOID(venv, id, (argc) * sizeof(int32_t), args)
#define KOALA_INTEROP_CALL_INT_INTS32(venv, id, argc, args) KOALA_INTEROP_CALL_INT(venv, id, (argc) * sizeof(int32_t), args)

// Improve:
#define KOALA_INTEROP_THROW(vmContext, object, ...)                                                     \
  do {                                                                                                  \
    KOALA_MAYBE_LOG("KOALA_INTEROP_THROW")                                                              \
    std::terminate();                                                                                   \
  } while (0)

// Improve:
#define KOALA_INTEROP_THROW_STRING(vmContext, message, ...)                                             \
  do {                                                                                                  \
    KOALA_MAYBE_LOG("KOALA_INTEROP_THROW_STRING")                                                       \
    KOALA_MAYBE_LOG(message)                                                                            \
    std::terminate();                                                                                   \
  } while (0)

#endif // KOALA_KOTLIN

#endif // CONVERTORS_KOTLIN_H