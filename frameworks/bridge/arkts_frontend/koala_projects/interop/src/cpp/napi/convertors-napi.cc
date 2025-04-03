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
#include <cstdint>
#include <cstring>
#include <vector>
#include <string>

#include "interop-logging.h"
#define KOALA_INTEROP_MODULE InteropNativeModule
#include "convertors-napi.h"


// Adapter for NAPI_MODULE
#define NODE_API_MODULE_ADAPTER(modname, regfunc)                                      \
  static napi_value __napi_##regfunc(napi_env env, napi_value exports) {       \
    return Napi::RegisterModule(env, exports, regfunc);                        \
  }                                                                            \
  NAPI_MODULE(modname, __napi_##regfunc)

napi_valuetype getValueTypeChecked(napi_env env, napi_value value) {
    napi_valuetype type;
    napi_status status = napi_typeof(env, value, &type);
    KOALA_NAPI_THROW_IF_FAILED(env, status, napi_undefined);
    return type;
}

bool isTypedArray(napi_env env, napi_value value) {
    bool result = false;
    napi_status status = napi_is_typedarray(env, value, &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, false);
    return result;
}

KBoolean getBoolean(napi_env env, napi_value value) {
    if (getValueTypeChecked(env, value) == napi_valuetype::napi_boolean) {
        bool result = false;
        napi_get_value_bool(env, value, &result);
        return static_cast<KBoolean>(result);
    }
    return static_cast<KBoolean>(getInt32(env, value) != 0);
}

KInt getInt32(napi_env env, napi_value value) {
    if (getValueTypeChecked(env, value) != napi_valuetype::napi_number) {
        napi_throw_error(env, nullptr, "Expected Number");
        return 0;
    }
    int32_t result = false;
    napi_get_value_int32(env, value, &result);
    return static_cast<KInt>(result);
}

KUInt getUInt32(napi_env env, napi_value value) {
    if (getValueTypeChecked(env, value) != napi_valuetype::napi_number) {
        napi_throw_error(env, nullptr, "Expected Number");
        return 0;
    }
    uint32_t result = false;
    napi_get_value_uint32(env, value, &result);
    return static_cast<KUInt>(result);
}

KFloat getFloat32(napi_env env, napi_value value) {
    if (getValueTypeChecked(env, value) != napi_valuetype::napi_number) {
        napi_throw_error(env, nullptr, "Expected Number");
        return 0.0f;
    }
    double result = false;
    napi_get_value_double(env, value, &result);
    return static_cast<KFloat>(static_cast<float>(result));
}

KDouble getFloat64(napi_env env, napi_value value) {
    if (getValueTypeChecked(env, value) != napi_valuetype::napi_number) {
        napi_throw_error(env, nullptr, "Expected Number");
        return 0.0;
    }
    double result = false;
    napi_get_value_double(env, value, &result);
    return static_cast<KDouble>(result);
}

KStringPtr getString(napi_env env, napi_value value) {
  KStringPtr result {};
  napi_valuetype valueType = getValueTypeChecked(env, value);
  if (valueType == napi_valuetype::napi_null || valueType == napi_valuetype::napi_undefined) {
    return result;
  }

  if (valueType != napi_valuetype::napi_string) {
    napi_throw_error(env, nullptr, "Expected String");
    return result;
  }

  size_t length = 0;
  napi_status status = napi_get_value_string_utf8(env, value, nullptr, 0, &length);
  if (status != 0) return result;
  result.resize(length);
  status = napi_get_value_string_utf8(env, value, result.data(), length + 1, nullptr);
  return result;
}

KNativePointer getPointer(napi_env env, napi_value value) {
    napi_valuetype valueType = getValueTypeChecked(env, value);
    if (valueType == napi_valuetype::napi_external) {
        KNativePointer result = nullptr;
        napi_status status = napi_get_value_external(env, value, &result);
        KOALA_NAPI_THROW_IF_FAILED(env, status, nullptr);
        return result;
    }

    if (valueType != napi_valuetype::napi_bigint) {
        napi_throw_error(env, nullptr, "cannot be coerced to pointer");
        return nullptr;
    }

    bool isWithinRange = true;
    uint64_t ptrU64 = 0;
    napi_status status = napi_get_value_bigint_uint64(env, value, &ptrU64, &isWithinRange);
    KOALA_NAPI_THROW_IF_FAILED(env, status, nullptr);
    if (!isWithinRange) {
        napi_throw_error(env, nullptr, "cannot be coerced to uint64, value is too large");
        return nullptr;
    }
    return reinterpret_cast<KNativePointer>(ptrU64);
}

KLong getInt64(napi_env env, napi_value value) {
    if (getValueTypeChecked(env, value) != napi_valuetype::napi_bigint) {
        napi_throw_error(env, nullptr, "cannot be coerced to int64");
        return -1;
    }

    bool isWithinRange = true;
    int64_t ptr64 = 0;
    napi_get_value_bigint_int64(env, value, &ptr64, &isWithinRange);
    if (!isWithinRange) {
        napi_throw_error(env, nullptr, "cannot be coerced to int64, value is too large");
        return -1;
    }
    return static_cast<KLong>(ptr64);
}

KULong getUInt64(napi_env env, napi_value value) {
    if (getValueTypeChecked(env, value) != napi_valuetype::napi_bigint) {
        napi_throw_error(env, nullptr, "cannot be coerced to uint64");
        return -1;
    }

    bool isWithinRange = true;
    uint64_t ptr64 = 0;
    napi_get_value_bigint_uint64(env, value, &ptr64, &isWithinRange);
    if (!isWithinRange) {
        napi_throw_error(env, nullptr, "cannot be coerced to uint64, value is too large");
        return -1;
    }
    return static_cast<KULong>(ptr64);
}

napi_value makeString(napi_env env, const KStringPtr& value) {
    napi_value result;
    napi_status status;
    status = napi_create_string_utf8(env, value.isNull() ? "" : value.data(), value.length(), &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

napi_value makeString(napi_env env, const std::string& value) {
    napi_value result;
    napi_status status;
    status = napi_create_string_utf8(env, value.c_str(), value.length(), &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

napi_value makeBoolean(napi_env env, int8_t value) {
    napi_value result;
    napi_status status;
    status = napi_get_boolean(env,  value != 0, &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

napi_value makeInt32(napi_env env, int32_t value) {
    napi_value result;
    napi_status status;
    status = napi_create_int32(env,  value, &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

napi_value makeUInt32(napi_env env, uint32_t value) {
    napi_value result;
    napi_status status;
    status = napi_create_uint32(env,  value, &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

napi_value makeInt64(napi_env env, int64_t value) {
    napi_value result;
    napi_status status;
    status = napi_create_bigint_int64(env, value, &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

napi_value makeUInt64(napi_env env, uint64_t value) {
    napi_value result;
    napi_status status;
    status = napi_create_bigint_uint64(env, value, &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

napi_value makeFloat32(napi_env env, float value) {
    napi_value result;
    napi_status status;
    status = napi_create_double(env,  value, &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

napi_value makePointer(napi_env env, void* value) {
    napi_value result;
    napi_status status;
    status = napi_create_bigint_uint64(env, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(value)), &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

napi_value makeVoid(napi_env env) {
    napi_value result;
    napi_status status;
    status = napi_get_undefined(env, &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

napi_value makeObject(napi_env env, napi_value object) {
    napi_value result;
    napi_status status;
    status = napi_create_object(env, &result);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    return result;
}

#if _MSC_VER >= 1932 // Visual Studio 2022 version 17.2+
#    pragma comment(linker, "/alternatename:__imp___std_init_once_complete=__imp_InitOnceComplete")
#    pragma comment(linker, "/alternatename:__imp___std_init_once_begin_initialize=__imp_InitOnceBeginInitialize")
#endif

Exports* Exports::getInstance() {
    static Exports *instance = nullptr;
    if (instance == nullptr) {
        instance = new Exports();
    }
    return instance;
}

std::vector<std::string> Exports::getModules() {
    std::vector<std::string> result;
    for (auto it = implementations.begin(); it != implementations.end(); ++it) {
        result.push_back(it->first);
    }
    return result;
}

void Exports::addMethod(const char* module, const char* name, napi_type_t impl) {
    auto it = implementations.find(module);
    if (it == implementations.end()) {
        it = implementations.insert(std::make_pair(module, std::vector<std::pair<std::string, napi_type_t>>())).first;
    }
    it->second.push_back(std::make_pair(name, impl));

}

const std::vector<std::pair<std::string, napi_type_t>>& Exports::getMethods(const std::string& module) {
    auto it = implementations.find(module);
    if (it == implementations.end()) {
        LOGE("Module %s is not registered", module.c_str());
        INTEROP_FATAL("Fatal error");
    }
    return it->second;
}

//
// Callback dispatcher
//
// TODO Should we get rid of explicit Node_* declrations and hide the naming convention behind the macro definitions?

static napi_ref g_koalaNapiCallbackDispatcher = nullptr;

// TODO: shall we pass name in globalThis instead of object reference?
napi_value Node_SetCallbackDispatcher(napi_env env, napi_callback_info cbinfo) {
    fprintf(stderr, "Node_SetCallbackDispatcher!\n");

    CallbackInfo info(env, cbinfo);
    napi_value dispatcher = info[0];
    napi_value result = makeVoid(env);
    napi_status status = napi_create_reference(env, dispatcher, 1, &g_koalaNapiCallbackDispatcher);
    KOALA_NAPI_THROW_IF_FAILED(env, status, result);

    return result;
}
MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, SetCallbackDispatcher)

napi_value Node_CleanCallbackDispatcher(napi_env env, napi_callback_info cbinfo) {
    napi_value result = makeVoid(env);
    if (g_koalaNapiCallbackDispatcher) {
        napi_status status = napi_delete_reference(env, g_koalaNapiCallbackDispatcher);
        g_koalaNapiCallbackDispatcher = nullptr;
        KOALA_NAPI_THROW_IF_FAILED(env, status, result);
    }
    return result;
}
MAKE_NODE_EXPORT(KOALA_INTEROP_MODULE, CleanCallbackDispatcher)

napi_value getKoalaNapiCallbackDispatcher(napi_env env) {
    if (!g_koalaNapiCallbackDispatcher) {
        abort();
    }
    napi_value value;
    napi_status status = napi_get_reference_value(env, g_koalaNapiCallbackDispatcher, &value);
    KOALA_NAPI_THROW_IF_FAILED(env, status, makeVoid(env));
    return value;
}

//
// Module initialization
//

using ModuleRegisterCallback = napi_value (*)(napi_env env, napi_value exports);

/**
 * Sets a new callback and returns its previous value.
 */
ModuleRegisterCallback ProvideModuleRegisterCallback(ModuleRegisterCallback value = nullptr) {
    static const ModuleRegisterCallback DEFAULT_CB = [](napi_env env, napi_value exports) { return exports; };
    static ModuleRegisterCallback curCallback = DEFAULT_CB;

    ModuleRegisterCallback prevCallback = curCallback;
    curCallback = value ? value : DEFAULT_CB;
    return prevCallback;
}

static constexpr bool splitModules = true;

static napi_value InitModule(napi_env env, napi_value exports) {
    LOG("InitModule: " QUOTE(INTEROP_LIBRARY_NAME) "\n");
    Exports* inst = Exports::getInstance();
    napi_status status;
    napi_value target = exports;
    for (const auto &module : inst->getModules()) {
        if (splitModules) {
            status = napi_create_object(env, &target);
            KOALA_NAPI_THROW_IF_FAILED(env, status, exports);
            status = napi_set_named_property(env, exports, module.c_str(), target);
            KOALA_NAPI_THROW_IF_FAILED(env, status, exports);
        }

        for (const auto &impl : inst->getMethods(module)) {
            napi_value implFunc;
            status = napi_create_function(env, impl.first.c_str(), NAPI_AUTO_LENGTH, impl.second, nullptr, &implFunc);
            KOALA_NAPI_THROW_IF_FAILED(env, status, exports);
            status = napi_set_named_property(env, target, impl.first.c_str(), implFunc);
            KOALA_NAPI_THROW_IF_FAILED(env, status, exports);
        }
    }
    return ProvideModuleRegisterCallback()(env, exports);
}

NAPI_MODULE(INTEROP_LIBRARY_NAME, InitModule)
