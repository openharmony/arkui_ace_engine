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

#ifndef _CONVERTORS_NAPI_H_
#define _CONVERTORS_NAPI_H_

#ifdef KOALA_NAPI

#include <unordered_map>
#include <vector>
#include <string>

#ifndef KOALA_NAPI_OHOS
#include <node_api.h>
#else
#include <native_api.h>
#include <native_node_api.h>
#endif
#include "koala-types.h"
#include "interop-types.h"

// TODO: switch to more generic convertors eventually.
template<class T>
struct InteropTypeConverter {
    using InteropType = T;
    static T convertFrom(napi_env env, InteropType value) { return value; }
    static InteropType convertTo(napi_env env, T value) { return value; }
    static void release(napi_env env, InteropType value, T converted) {}
};

template <typename Type>
inline typename InteropTypeConverter<Type>::InteropType makeResult(napi_env env, Type value) {
  return InteropTypeConverter<Type>::convertTo(env, value);
}

template <typename Type>
inline Type getArgument(napi_env env, typename InteropTypeConverter<Type>::InteropType arg) {
  return InteropTypeConverter<Type>::convertFrom(env, arg);
}

template <typename Type>
inline void releaseArgument(napi_env env, typename InteropTypeConverter<Type>::InteropType arg, Type data) {
  InteropTypeConverter<Type>::release(env, arg, data);
}


napi_value makeString(napi_env env, KStringPtr value);
napi_value makeString(napi_env env, const std::string& value);
napi_value makeBoolean(napi_env env, KBoolean value);
napi_value makeInt32(napi_env env, int32_t value);
napi_value makeUInt32(napi_env env, uint32_t value);
napi_value makeInt64(napi_env env, int64_t value);
napi_value makeUInt64(napi_env env, uint64_t value);
napi_value makeFloat32(napi_env env, float value);
napi_value makePointer(napi_env env, void* value);
napi_value makeVoid(napi_env env);

void* getPointer(napi_env env, napi_value value);
void* getSerializerBufferPointer(napi_env env, napi_value value);

template<>
struct InteropTypeConverter<KInteropBuffer> {
    using InteropType = napi_value;
    static KInteropBuffer convertFrom(napi_env env, InteropType value) {
      KInteropBuffer result {};
      bool isArrayBuffer = false;
      napi_is_arraybuffer(env, value, &isArrayBuffer);
      if (isArrayBuffer) {
        napi_get_arraybuffer_info(env, value, &result.data, (size_t*)&result.length);
      } else {
        bool isDataView = false;
        napi_is_dataview(env, value, &isDataView);
        if (isDataView) {
          napi_get_dataview_info(env, value, (size_t*)&result.length, &result.data, nullptr, nullptr);
        }
      }
      return result;
    }
    static InteropType convertTo(napi_env env, KInteropBuffer value) {
      KInteropBuffer* copy = new KInteropBuffer(value);
      napi_value result;
      napi_status status = napi_create_external_arraybuffer(
        env,
        value.data,
        value.length,
        [](napi_env env, void* finalize_data, void* finalize_hint) {
          KInteropBuffer* buffer = reinterpret_cast<KInteropBuffer*>(finalize_hint);
          buffer->dispose(buffer->resourceId);
          delete buffer;
        },
        (void*)copy,
        &result
      );
      if (status != napi_ok) {
        // do smth here
      }
      return result;
    };
    static void release(napi_env env, InteropType value, KInteropBuffer converted) {}
};

template<>
struct InteropTypeConverter<KStringPtr> {
    using InteropType = napi_value;
    static KStringPtr convertFrom(napi_env env, InteropType value) {
        if (value == nullptr) return KStringPtr();
        KStringPtr result;
        size_t length = 0;
        napi_status status = napi_get_value_string_utf8(env, value, nullptr, 0, &length);
        if (status != 0) return result;
        result.resize(length);
        status = napi_get_value_string_utf8(env, value, result.data(), length + 1, nullptr);
        return result;
    }
    static InteropType convertTo(napi_env env, const KStringPtr& value) {
      napi_value result;
      napi_create_string_utf8(env, value.c_str(), value.length(), &result);
      return result;
    }
    static void release(napi_env env, InteropType value, const KStringPtr& converted) {}
};

template<>
struct InteropTypeConverter<KInteropNumber> {
    using InteropType = napi_value;
    static KInteropNumber convertFrom(napi_env env, InteropType interopValue) {
        double value = 0.0;
        napi_get_value_double(env, interopValue, &value);
        return KInteropNumber::fromDouble(value);
    }
    static InteropType convertTo(napi_env env, KInteropNumber value) {
      napi_value result;
      napi_create_double(env, value.asDouble(), &result);
      return result;
    }
    static void release(napi_env env, InteropType value, KInteropNumber converted) {}
};

template<>
struct InteropTypeConverter<KSerializerBuffer> {
    using InteropType = napi_value;
    static KSerializerBuffer convertFrom(napi_env env, InteropType value) {
        return (KSerializerBuffer)getSerializerBufferPointer(env, value); // TODO we are receiving Uint8Array from the native side
    }
    static InteropType convertTo(napi_env env, KSerializerBuffer value) {
      return makePointer(env, value);
    }
    static void release(napi_env env, InteropType value, KSerializerBuffer converted) {}
};

template<>
struct InteropTypeConverter<KVMObjectHandle> {
    using InteropType = napi_value;
    static inline KVMObjectHandle convertFrom(napi_env env, InteropType value) {
        return reinterpret_cast<KVMObjectHandle>(value);
    }
    static InteropType convertTo(napi_env env, KVMObjectHandle value) {
      return reinterpret_cast<napi_value>(value);
    }
    static inline void release(napi_env env, InteropType value, KVMObjectHandle converted) {
    }
};

template<>
struct InteropTypeConverter<KInteropReturnBuffer> {
    using InteropType = napi_value;
    static inline KInteropReturnBuffer convertFrom(napi_env env, InteropType value) = delete;
    static void disposer(napi_env env, void* data, void* hint) {
      KInteropReturnBuffer* bufferCopy = (KInteropReturnBuffer*)hint;
      bufferCopy->dispose(bufferCopy->data, bufferCopy->length);
      delete bufferCopy;
    }
    static InteropType convertTo(napi_env env, KInteropReturnBuffer value) {
      napi_value result = nullptr;
      napi_value arrayBuffer = nullptr;
      auto clone = new KInteropReturnBuffer();
      *clone = value;
      napi_create_external_arraybuffer(env, value.data, value.length, disposer, clone, &arrayBuffer);
      napi_create_typedarray(env, napi_uint8_array, value.length, arrayBuffer, 0, &result);
      return result;
    }
    static inline void release(napi_env env, InteropType value, const KInteropReturnBuffer& converted) = delete;
};


#define KOALA_INTEROP_THROW(vmcontext, object, ...) \
   do { \
     napi_env env = (napi_env)vmcontext; \
     napi_handle_scope scope = nullptr; \
     napi_status status = napi_open_handle_scope(env, &scope); \
     napi_throw((napi_env)vmcontext, object); \
     napi_close_handle_scope(env, scope); \
     return __VA_ARGS__;  \
   } while (0)

#define KOALA_INTEROP_THROW_STRING(vmContext, message, ...) \
  do { \
    napi_value value; \
    napi_create_string_utf8((napi_env)vmContext, message, strlen(message), &value); \
    KOALA_INTEROP_THROW(vmContext, value, __VA_ARGS__); \
  } while (0)

#define NAPI_ASSERT_INDEX(info, index, result)              \
    do {                                                    \
        if (static_cast<size_t>(index) >= info.Length()) {  \
          napi_throw_error(info.Env(), nullptr, "No such element");\
          return result;                                  \
        }                                                   \
    } while (0)

// Helpers from node-addon-api
#define KOALA_NAPI_THROW_IF_FAILED(env, status, ...)                                 \
  if ((status) != napi_ok) {                                                   \
    const napi_extended_error_info* errorInfo;                                 \
    napi_get_last_error_info(env, &errorInfo);                                 \
    napi_throw_error(env, nullptr, errorInfo->error_message);                  \
    return __VA_ARGS__;                                                        \
  }
#define KOALA_NAPI_THROW_IF_FAILED_VOID(env, status)                                 \
  if ((status) != napi_ok) {                                                   \
    const napi_extended_error_info* errorInfo;                                 \
    napi_get_last_error_info(env, &errorInfo);                                 \
    napi_throw_error(env, nullptr, errorInfo->error_message);                  \
    return;                                                        \
  }

class CallbackInfo {
public:
  CallbackInfo(napi_env env, napi_callback_info info) : _env(env) {
    size_t size = 0;
    napi_status status;
    status = napi_get_cb_info(env, info, &size, nullptr, nullptr, nullptr);
    KOALA_NAPI_THROW_IF_FAILED_VOID(env, status);
    if (size > 0) {
      args.resize(size);  // TODO statically allocate small array for common case with few arguments passed
      status = napi_get_cb_info(env, info, &size, args.data(), nullptr, nullptr);
      KOALA_NAPI_THROW_IF_FAILED_VOID(env, status);
    }
  }

  napi_value operator[](size_t idx) const {
    if (idx >= Length()) {
      napi_value result;
      napi_get_undefined(_env, &result);
      return result;
    }
    return args[idx];
  }

  napi_env Env() const {
    return _env;
  }

  size_t Length() const {
    return args.size();
  }
private:
  napi_env _env;
  std::vector<napi_value> args;
};

template <typename ElemType>
inline napi_typedarray_type getNapiType() = delete;

template <>
inline napi_typedarray_type getNapiType<float>() {
  return napi_float32_array;
}

template <>
inline napi_typedarray_type getNapiType<int8_t>() {
  return napi_int8_array;
}

template <>
inline napi_typedarray_type getNapiType<uint8_t>() {
  return napi_uint8_array;
}

template <>
inline napi_typedarray_type getNapiType<int16_t>() {
  return napi_int16_array;
}

template <>
inline napi_typedarray_type getNapiType<uint16_t>() {
  return napi_uint16_array;
}

template <>
inline napi_typedarray_type getNapiType<int32_t>() {
  return napi_int32_array;
}

template <>
inline napi_typedarray_type getNapiType<uint32_t>() {
  return napi_uint32_array;
}

template <>
inline napi_typedarray_type getNapiType<KNativePointer>() {
  return napi_biguint64_array;
}

napi_valuetype getValueTypeChecked(napi_env env, napi_value value);
bool isTypedArray(napi_env env, napi_value value);

template <typename ElemType>
inline ElemType* getTypedElements(napi_env env, napi_value value) {
  napi_valuetype valueType = getValueTypeChecked(env, value);
  if (valueType == napi_null) {
    return nullptr;
  }
  if (!isTypedArray(env, value)) {
    napi_throw_error(env, nullptr, "Expected TypedArray");
    return nullptr;
  }
  napi_value arrayBuffer;
  void* data = nullptr;
  size_t byteLength;
  size_t byteOffset;
  napi_typedarray_type type;
  napi_status status = napi_get_typedarray_info(env,
                                                value,
                                                &type,
                                                &byteLength,
                                                &data,
                                                &arrayBuffer,
                                                &byteOffset);
  KOALA_NAPI_THROW_IF_FAILED(env, status, nullptr);
  if (type != getNapiType<ElemType>()) {
    printf("Array type mismatch. Expected %d got %d\n", getNapiType<ElemType>(), type);
    napi_throw_error(env, nullptr, "Array type mismatch");
    return nullptr;
  }
  return reinterpret_cast<ElemType*>(data);
}

template <typename ElemType>
inline ElemType* getTypedElements(const CallbackInfo& info, int index) {
    NAPI_ASSERT_INDEX(info, index, nullptr);
    return getTypedElements<ElemType>(info.Env(), info[index]);
}

inline uint8_t* getUInt8Elements(const CallbackInfo& info, int index) {
  return getTypedElements<uint8_t>(info, index);
}

inline int8_t* getInt8Elements(const CallbackInfo& info, int index) {
  return getTypedElements<int8_t>(info, index);
}

inline uint16_t* getUInt16Elements(const CallbackInfo& info, int index) {
  return getTypedElements<uint16_t>(info, index);
}

inline int16_t* getInt16Elements(const CallbackInfo& info, int index) {
  return getTypedElements<int16_t>(info, index);
}

inline uint32_t* getUInt32Elements(const CallbackInfo& info, int index) {
  return getTypedElements<uint32_t>(info, index);
}

inline uint32_t* getUInt32Elements(napi_env env, napi_value value) {
    return getTypedElements<uint32_t>(env, value);
}

inline int32_t* getInt32Elements(const CallbackInfo& info, int index) {
  return getTypedElements<int32_t>(info, index);
}

inline float* getFloat32Elements(const CallbackInfo& info, int index) {
  return getTypedElements<float>(info, index);
}

inline KNativePointer* getPointerElements(const CallbackInfo& info, int index) {
  return getTypedElements<KNativePointer>(info, index);
}

inline void* getSerializerBufferPointer(napi_env env, napi_value value) {
  return getTypedElements<uint8_t>(env, value);
}

KInt getInt32(napi_env env, napi_value value);
inline int32_t getInt32(const CallbackInfo& info, int index) {
  NAPI_ASSERT_INDEX(info, index, 0);
  return getInt32(info.Env(), info[index]);
}
KUInt getUInt32(napi_env env, napi_value value);
inline uint32_t getUInt32(const CallbackInfo& info, int index) {
  NAPI_ASSERT_INDEX(info, index, 0);
  return getUInt32(info.Env(), info[index]);
}
KFloat getFloat32(napi_env env, napi_value value);
inline float getFloat32(const CallbackInfo& info, int index) {
  NAPI_ASSERT_INDEX(info, index, 0.0f);
  return getFloat32(info.Env(), info[index]);
}
KDouble getFloat64(napi_env env, napi_value value);
inline KDouble getFloat64(const CallbackInfo& info, int index) {
  NAPI_ASSERT_INDEX(info, index, 0.0);
  return getFloat64(info.Env(), info[index]);
}
KStringPtr getString(napi_env env, napi_value value);
inline KStringPtr getString(const CallbackInfo& info, int index) {
  NAPI_ASSERT_INDEX(info, index, KStringPtr());
  return getString(info.Env(), info[index]);
}
inline void* getPointer(const CallbackInfo& info, int index) {
    NAPI_ASSERT_INDEX(info, index, nullptr);
    return getPointer(info.Env(), info[index]);
}
KULong getUInt64(napi_env env, napi_value value);
inline KULong getUInt64(const CallbackInfo& info, int index) {
    NAPI_ASSERT_INDEX(info, index, 0);
    return getUInt64(info.Env(), info[index]);
}
KLong getInt64(napi_env env, napi_value value);
inline KLong getInt64(const CallbackInfo& info, int index) {
    NAPI_ASSERT_INDEX(info, index, 0);
    return getInt64(info.Env(), info[index]);
}
KBoolean getBoolean(napi_env env, napi_value value);
inline KBoolean getBoolean(const CallbackInfo& info, int index) {
  NAPI_ASSERT_INDEX(info, index, false);
  return getBoolean(info.Env(), info[index]);
}

template <typename Type>
inline Type getArgument(const CallbackInfo& info, int index) = delete;

template <>
inline KBoolean getArgument<KBoolean>(const CallbackInfo& info, int index) {
  return getBoolean(info, index);
}

template <>
inline KUInt getArgument<uint32_t>(const CallbackInfo& info, int index) {
  return getUInt32(info, index);
}

template <>
inline KInt getArgument<int32_t>(const CallbackInfo& info, int index) {
  return getInt32(info, index);
}

template <>
inline KInteropNumber getArgument<KInteropNumber>(const CallbackInfo& info, int index) {
  NAPI_ASSERT_INDEX(info, index, { 0 });
  return getArgument<KInteropNumber>(info.Env(), info[index]);
}

template <>
inline KSerializerBuffer getArgument<KSerializerBuffer>(const CallbackInfo& info, int index) {
  NAPI_ASSERT_INDEX(info, index, nullptr);
  return getArgument<KSerializerBuffer>(info.Env(), info[index]);
}

template <>
inline KLength getArgument<KLength>(const CallbackInfo& info, int index) {
  KLength result { 0 };
  NAPI_ASSERT_INDEX(info, index, result);
  auto value = info[index];
  napi_valuetype type;
  auto status = napi_typeof(info.Env(), value, &type);
  if (status != 0) return result;
  switch (type) {
    case napi_number: {
      result.value = getFloat32(info.Env(), value);
      result.unit = 1;
      result.type = 0;
      break;
    }
    case napi_string: {
      KStringPtr string = getString(info.Env(), value);
      parseKLength(string, &result);
      result.type = 1;
      result.resource = 0;
      break;
    }
    case napi_object: {
      result.value = 0;
      result.unit = 1;
      result.type = 2;
      napi_value field;
      napi_status status = napi_get_named_property(info.Env(), value, "id", &field);
      if (status == 0) {
        status = napi_get_value_int32(info.Env(), field, &result.resource);
        if (status != 0) result.resource = 0;
      } else {
        result.resource = 0;
      }
      break;
    }
    default:
      INTEROP_FATAL("Error, unexpected KLength type");
  }
  return result;
}


template <>
inline KInteropBuffer getArgument<KInteropBuffer>(const CallbackInfo& info, int index) {
  NAPI_ASSERT_INDEX(info, index, {});
  return getArgument<KInteropBuffer>((napi_env)info.Env(), (napi_value)info[index]);
}

template <>
inline KFloat getArgument<KFloat>(const CallbackInfo& info, int index) {
  return getFloat32(info, index);
}

template <>
inline KDouble getArgument<KDouble>(const CallbackInfo& info, int index) {
  return getFloat64(info, index);
}

template <>
inline KNativePointer getArgument<KNativePointer>(const CallbackInfo& info, int index) {
  return getPointer(info, index);
}

template <>
inline KLong getArgument<KLong>(const CallbackInfo& info, int index) {
  return getInt64(info, index);
}

template <>
inline KULong getArgument<KULong>(const CallbackInfo& info, int index) {
  return getUInt64(info, index);
}

template <>
inline KNativePointerArray getArgument<KNativePointerArray>(const CallbackInfo& info, int index) {
  return getPointerElements(info, index);
}

template <>
inline uint8_t* getArgument<uint8_t*>(const CallbackInfo& info, int index) {
  return getUInt8Elements(info, index);
}

template <>
inline const uint8_t* getArgument<const uint8_t*>(const CallbackInfo& info, int index) {
  return getUInt8Elements(info, index);
}

template <>
inline int8_t* getArgument<int8_t*>(const CallbackInfo& info, int index) {
  return getInt8Elements(info, index);
}

template <>
inline int16_t* getArgument<int16_t*>(const CallbackInfo& info, int index) {
  return getInt16Elements(info, index);
}

template <>
inline uint16_t* getArgument<uint16_t*>(const CallbackInfo& info, int index) {
  return getUInt16Elements(info, index);
}

template <>
inline int32_t* getArgument<int32_t*>(const CallbackInfo& info, int index) {
  return getInt32Elements(info, index);
}

template <>
inline uint32_t* getArgument<uint32_t*>(const CallbackInfo& info, int index) {
  return getUInt32Elements(info, index);
}

template <>
inline float* getArgument<float*>(const CallbackInfo& info, int index) {
  return getFloat32Elements(info, index);
}

template <>
inline KStringPtr getArgument<KStringPtr>(const CallbackInfo& info, int index) {
  return getString(info, index);
}

inline napi_value makeVoid(const CallbackInfo& info) {
  return makeVoid(info.Env());
}

template <typename Type>
inline napi_value makeResult(const CallbackInfo& info, Type value) = delete;

template <>
inline napi_value makeResult<KBoolean>(const CallbackInfo& info, KBoolean value) {
  return makeBoolean(info.Env(), value);
}

template <>
inline napi_value makeResult<int32_t>(const CallbackInfo& info, int32_t value) {
  return makeInt32(info.Env(), value);
}

template <>
inline napi_value makeResult<uint32_t>(const CallbackInfo& info, uint32_t value) {
  return makeUInt32(info.Env(), value);
}

template <>
inline napi_value makeResult<KLong>(const CallbackInfo& info, int64_t value) {
  return makeInt64(info.Env(), value);
}

template <>
inline napi_value makeResult<KULong>(const CallbackInfo& info, uint64_t value) {
  return makeUInt64(info.Env(), value);
}

template <>
inline napi_value makeResult<float>(const CallbackInfo& info, float value) {
  return makeFloat32(info.Env(), value);
}

template <>
inline napi_value makeResult<KNativePointer>(const CallbackInfo& info, KNativePointer value) {
  return makePointer(info.Env(), value);
}

template <>
inline napi_value makeResult<KVMObjectHandle>(const CallbackInfo& info, KVMObjectHandle value) {
  return InteropTypeConverter<KVMObjectHandle>::convertTo(info.Env(), value);
}

template <>
inline napi_value makeResult<KStringPtr>(const CallbackInfo& info, KStringPtr value) {
  return InteropTypeConverter<KStringPtr>::convertTo(info.Env(), value);
}

template <>
inline napi_value makeResult<KInteropBuffer>(const CallbackInfo& info, KInteropBuffer value) {
  return InteropTypeConverter<KInteropBuffer>::convertTo(info.Env(), value);
}

template <>
inline napi_value makeResult<KInteropReturnBuffer>(const CallbackInfo& info, KInteropReturnBuffer value) {
  return InteropTypeConverter<KInteropReturnBuffer>::convertTo(info.Env(), value);
}

template <>
inline napi_value makeResult<KInteropNumber>(const CallbackInfo& info, KInteropNumber value) {
  return InteropTypeConverter<KInteropNumber>::convertTo(info.Env(), value);
}

typedef napi_value (*napi_type_t)(napi_env, napi_callback_info);

class Exports {
    std::unordered_map<std::string,
      std::vector<std::pair<std::string, napi_type_t>>> implementations;

public:
    static Exports* getInstance();

    std::vector<std::string> getModules();
    void addMethod(const char* module, const char* name, napi_type_t impl);
    const std::vector<std::pair<std::string, napi_type_t>>& getMethods(const std::string& module);
};

#define __QUOTE(x) #x
#define QUOTE(x) __QUOTE(x)

#ifdef _MSC_VER
#define MAKE_NODE_EXPORT(module, name)                                  \
    static void __init_##name() {                               \
        Exports::getInstance()->addMethod(QUOTE(module), "_"#name, Node_##name); \
    }                                                           \
    namespace {                                                 \
      struct __Init_##name {                                    \
        __Init_##name() {  __init_##name(); }                   \
      } __Init_##name##_v;                                      \
    }
#else
#define MAKE_NODE_EXPORT(module, name) \
    __attribute__((constructor)) \
    static void __init_##name() { \
        Exports::getInstance()->addMethod(QUOTE(module), "_"#name, Node_##name); \
    }
#endif

#ifndef KOALA_INTEROP_MODULE
#error KOALA_INTEROP_MODULE is undefined
#endif

#define MAKE_INTEROP_NODE_EXPORT(name) MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_0(name, Ret) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                        \
      CallbackInfo info(env, cbinfo);              \
      return makeResult<Ret>(info, impl_##name()); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_1(name, Ret, P0) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      return makeResult<Ret>(info, impl_##name(p0)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_2(name, Ret, P0, P1) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      return makeResult<Ret>(info, impl_##name(p0, p1)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_3(name, Ret, P0, P1, P2) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_4(name, Ret, P0, P1, P2, P3) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_5(name, Ret, P0, P1, P2, P3, P4) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3, p4)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_6(name, Ret, P0, P1, P2, P3, P4, P5) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3, p4, p5)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_7(name, Ret, P0, P1, P2, P3, P4, P5, P6) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3, p4, p5, p6)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_8(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_9(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_10(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_11(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      P10 p10 = getArgument<P10>(info, 10); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_12(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      P10 p10 = getArgument<P10>(info, 10); \
      P11 p11 = getArgument<P11>(info, 11); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_13(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      P10 p10 = getArgument<P10>(info, 10); \
      P11 p11 = getArgument<P11>(info, 11); \
      P12 p12 = getArgument<P12>(info, 12); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_14(name, Ret, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      P10 p10 = getArgument<P10>(info, 10); \
      P11 p11 = getArgument<P11>(info, 11); \
      P12 p12 = getArgument<P12>(info, 12); \
      P13 p13 = getArgument<P13>(info, 13); \
      return makeResult<Ret>(info, impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V0(name) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      impl_##name(); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V1(name, P0) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      impl_##name(p0); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V2(name, P0, P1) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      impl_##name(p0, p1); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V3(name, P0, P1, P2) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      impl_##name(p0, p1, p2); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V4(name, P0, P1, P2, P3) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      impl_##name(p0, p1, p2, p3); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V5(name, P0, P1, P2, P3, P4) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      impl_##name(p0, p1, p2, p3, p4); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V6(name, P0, P1, P2, P3, P4, P5) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      impl_##name(p0, p1, p2, p3, p4, p5); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V7(name, P0, P1, P2, P3, P4, P5, P6) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V8(name, P0, P1, P2, P3, P4, P5, P6, P7) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V9(name, P0, P1, P2, P3, P4, P5, P6, P7, P8) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(impl_##name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V10(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V11(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(impl_##name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      P10 p10 = getArgument<P10>(info, 10); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V12(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(impl_##name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      P10 p10 = getArgument<P10>(info, 10); \
      P11 p11 = getArgument<P11>(info, 11); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V13(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(impl_##name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      P10 p10 = getArgument<P10>(info, 10); \
      P11 p11 = getArgument<P11>(info, 11); \
      P12 p12 = getArgument<P12>(info, 12); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V14(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      P10 p10 = getArgument<P10>(info, 10); \
      P11 p11 = getArgument<P11>(info, 11); \
      P12 p12 = getArgument<P12>(info, 12); \
      P13 p13 = getArgument<P13>(info, 13); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_V15(name, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      P5 p5 = getArgument<P5>(info, 5); \
      P6 p6 = getArgument<P6>(info, 6); \
      P7 p7 = getArgument<P7>(info, 7); \
      P8 p8 = getArgument<P8>(info, 8); \
      P9 p9 = getArgument<P9>(info, 9); \
      P10 p10 = getArgument<P10>(info, 10); \
      P11 p11 = getArgument<P11>(info, 11); \
      P12 p12 = getArgument<P12>(info, 12); \
      P13 p13 = getArgument<P13>(info, 13); \
      P14 p14 = getArgument<P14>(info, 14); \
      impl_##name(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_0(name, Ret) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(impl_##name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      return makeResult<Ret>(info, impl_##name(ctx)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_1(name, Ret, P0) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(impl_##name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      P0 p0 = getArgument<P0>(info, 0); \
      return makeResult<Ret>(info, impl_##name(ctx, p0)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_2(name, Ret, P0, P1) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      return makeResult<Ret>(info, impl_##name(ctx, p0, p1)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_3(name, Ret, P0, P1, P2) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      return makeResult<Ret>(info, impl_##name(ctx, p0, p1, p2)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_4(name, Ret, P0, P1, P2, P3) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      return makeResult<Ret>(info, impl_##name(ctx, p0, p1, p2, p3)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_5(name, Ret, P0, P1, P2, P3, P4) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      return makeResult<Ret>(info, impl_##name(ctx, p0, p1, p2, p3, p4)); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_V0(name) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      impl_##name(ctx); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)


#define KOALA_INTEROP_CTX_V1(name, P0) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      P0 p0 = getArgument<P0>(info, 0); \
      impl_##name(ctx, p0); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_V2(name, P0, P1) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      impl_##name(ctx, p0, p1); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_V3(name, P0, P1, P2) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      impl_##name(ctx, p0, p1, p2); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_V4(name, P0, P1, P2, P3) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      impl_##name(ctx, p0, p1, p2, p3); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define KOALA_INTEROP_CTX_V5(name, P0, P1, P2, P3, P4) \
  napi_value Node_##name(napi_env env, napi_callback_info cbinfo) { \
      KOALA_MAYBE_LOG(name)                   \
      CallbackInfo info(env, cbinfo);              \
      KVMContext ctx = reinterpret_cast<KVMContext>((napi_env)info.Env()); \
      P0 p0 = getArgument<P0>(info, 0); \
      P1 p1 = getArgument<P1>(info, 1); \
      P2 p2 = getArgument<P2>(info, 2); \
      P3 p3 = getArgument<P3>(info, 3); \
      P4 p4 = getArgument<P4>(info, 4); \
      impl_##name(ctx, p0, p1, p2, p3, p4); \
      return makeVoid(info); \
  } \
  MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, name)

#define NODEJS_GET_AND_THROW_LAST_ERROR(env)                                 \
    do {                                                                     \
        const napi_extended_error_info *error_info;                          \
        napi_get_last_error_info((env), &error_info);                        \
        bool is_pending;                                                     \
        napi_is_exception_pending((env), &is_pending);                       \
        /* If an exception is already pending, don't rethrow it */           \
        if (!is_pending) {                                                   \
            const char* error_message = error_info->error_message != NULL ?  \
            error_info->error_message :                                      \
            "empty error message";                                           \
            napi_throw_error((env), NULL, error_message);                    \
        }                                                                    \
    } while (0)

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

napi_value getKoalaNapiCallbackDispatcher(napi_env env);
// TODO: can/shall we cache bridge reference?

#define KOALA_INTEROP_CALL_VOID(venv, id, length, args)                            \
{                                                                                  \
  napi_env env = reinterpret_cast<napi_env>(venv);                                 \
  napi_value bridge = getKoalaNapiCallbackDispatcher(env),                         \
     global = nullptr, return_val = nullptr;                                       \
  napi_handle_scope scope = nullptr;                                               \
  napi_open_handle_scope(env, &scope);                                             \
  napi_status status = napi_get_global(env, &global);                              \
  napi_value node_args[3];                                                         \
  napi_create_int32(env, id, &node_args[0]);                                       \
  napi_value buffer = nullptr;                                                     \
  napi_create_external_arraybuffer(env,                                            \
    args, length,                                                                  \
    [](napi_env, void* data, void* hint) {}, nullptr, &buffer);                    \
  napi_create_typedarray(env, napi_uint8_array, length, buffer, 0, &node_args[1]); \
  napi_create_int32(env, length, &node_args[2]);                                   \
  status = napi_call_function(env, global, bridge, 3, node_args, &return_val);     \
  if (status != napi_ok) NODEJS_GET_AND_THROW_LAST_ERROR((env));                   \
  napi_close_handle_scope(env, scope);                                             \
}

#define KOALA_INTEROP_CALL_INT(venv, id, length, args)                             \
{                                                                                  \
  napi_env env = reinterpret_cast<napi_env>(venv);                                 \
  napi_value bridge = getKoalaNapiCallbackDispatcher(env),                         \
     global = nullptr, return_val = nullptr;                                       \
  napi_handle_scope scope = nullptr;                                               \
  napi_open_handle_scope(env, &scope);                                             \
  napi_status status = napi_get_global(env, &global);                              \
  napi_value node_args[3];                                                         \
  napi_create_int32(env, id, &node_args[0]);                                       \
  napi_value buffer = nullptr;                                                     \
  napi_create_external_arraybuffer(env,                                            \
    args, length,                                                                  \
    [](napi_env, void* data, void* hint) {}, nullptr, &buffer);                    \
  napi_create_typedarray(env, napi_uint8_array, length, buffer, 0, &node_args[1]); \
  napi_create_int32(env, length, &node_args[2]);                                   \
  status = napi_call_function(env, global, bridge, 3, node_args, &return_val);     \
  if (status != napi_ok) NODEJS_GET_AND_THROW_LAST_ERROR((env));                   \
  int result;                                                                      \
  status = napi_get_value_int32(env, return_val, &result);                         \
  napi_close_handle_scope(env, scope);                                             \
  return result;                                                                   \
}

#define KOALA_INTEROP_CALL_VOID_INTS32(venv, id, argc, args) KOALA_INTEROP_CALL_VOID(venv, id, (argc) * sizeof(int32_t), args)
#define KOALA_INTEROP_CALL_INT_INTS32(venv, id, argc, args) KOALA_INTEROP_CALL_INT(venv, id, (argc) * sizeof(int32_t), args)

#endif // KOALA_NAPI

#endif // _CONVERTORS_NAPI_H_