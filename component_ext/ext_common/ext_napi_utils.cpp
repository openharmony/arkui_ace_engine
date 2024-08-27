/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ext_napi_utils.h"

#include "securec.h"

namespace OHOS::Ace {

NapiAsyncEvent::NapiAsyncEvent(napi_env env, napi_value callback)
{
    env_ = env;
    napi_create_reference(env_, callback, 1, &ref_);
}

NapiAsyncEvent::~NapiAsyncEvent()
{
    napi_delete_reference(env_, ref_);
}

napi_value NapiAsyncEvent::Call(int32_t argc, napi_value* argv)
{
    napi_value result = nullptr;
    napi_handle_scope scope;
    napi_open_handle_scope(env_, &scope);
    if (scope == nullptr) {
        napi_close_handle_scope(env_, scope);
        return result;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, ref_, &callback);
    napi_value undefined = nullptr;
    napi_get_undefined(env_, &undefined);
    napi_call_function(env_, undefined, callback, argc, argv, &result);
    napi_close_handle_scope(env_, scope);
    return result;
}

napi_env NapiAsyncEvent::GetEnv()
{
    return env_;
}

napi_value ExtNapiUtils::CreateInt32(napi_env env, int32_t code)
{
    napi_value value = nullptr;
    if (napi_create_int32(env, code, &value) != napi_ok) {
        return nullptr;
    }
    return value;
}

int32_t ExtNapiUtils::GetCInt32(napi_env env, napi_value value)
{
    int32_t num = 0;
    napi_get_value_int32(env, value, &num);
    return num;
}

int64_t ExtNapiUtils::GetCInt64(napi_env env, napi_value value)
{
    int64_t num = 0;
    napi_get_value_int64(env, value, &num);
    return num;
}

napi_value ExtNapiUtils::CreateNull(napi_env env)
{
    napi_value jsNull = nullptr;
    NAPI_CALL(env, napi_get_null(env, &jsNull));
    return jsNull;
}

bool ExtNapiUtils::GetBool(napi_env env, napi_value value)
{
    bool boolValue = false;
    napi_status ret = napi_get_value_bool(env, value, &boolValue);
    if (ret == napi_ok) {
        return boolValue;
    }
    return false;
}

napi_valuetype ExtNapiUtils::GetValueType(napi_env env, napi_value value)
{
    if (value == nullptr) {
        return napi_undefined;
    }

    napi_valuetype valueType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, value, &valueType), napi_undefined);
    return valueType;
}

std::string ExtNapiUtils::GetStringFromValueUtf8(napi_env env, napi_value value)
{
    static constexpr size_t max_length = 2048;
    if (GetValueType(env, value) != napi_string) {
        return {};
    }

    std::string result;
    size_t stringLength = 0;
    NAPI_CALL_BASE(env, napi_get_value_string_utf8(env, value, nullptr, 0, &stringLength), result);
    if (stringLength == 0 || stringLength > max_length) {
        return result;
    }

    auto deleter = [](char* s) { free(reinterpret_cast<void*>(s)); };
    char* strTmp = static_cast<char*>(malloc(stringLength + 1));
    if (strTmp == nullptr) {
        return result;
    }
    std::unique_ptr<char, decltype(deleter)> str(strTmp, deleter);
    if (memset_s(str.get(), stringLength + 1, 0, stringLength + 1) != EOK) {
        return result;
    }
    size_t length = 0;
    NAPI_CALL_BASE(env, napi_get_value_string_utf8(env, value, str.get(), stringLength + 1, &length), result);
    if (length > 0) {
        result.append(str.get(), length);
    }
    return result;
}

bool ExtNapiUtils::CheckTypeForNapiValue(napi_env env, napi_value param, napi_valuetype expectType)
{
    napi_valuetype valueType = napi_undefined;

    if (napi_typeof(env, param, &valueType) != napi_ok) {
        return false;
    }

    return valueType == expectType;
}
}
