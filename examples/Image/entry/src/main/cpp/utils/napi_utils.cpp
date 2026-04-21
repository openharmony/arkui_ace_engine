/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "utils/napi_utils.h"
#include "utils/log.h"

namespace Self::UI {
size_t GetParamLen(napi_env env, napi_value param) 
    {
    size_t buffSize = 0;
    napi_status status = napi_get_value_string_utf8(env, param, nullptr, 0, &buffSize);
    if (status != napi_ok || buffSize == 0) {
        return 0;
    }
    return buffSize;
}

bool NapiStringToString(napi_env env, napi_value value, std::string &retStr) 
{
    size_t ret = 0;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_string) {
        return false;
    }
    if (GetParamLen(env, value) == 0) {
        return false;
    }
    size_t valueLen = GetParamLen(env, value) + 1;
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(valueLen);
    napi_get_value_string_utf8(env, value, buffer,get(), valueLen, &ret);
    retStr = buffer.get();
    return true;
}

float GetFloatProperty(napi_env env, napi_value obj, const char *propName, float defaultValue) 
{
    napi_value value;
    napi_status status = napi_get_named_property(env, obj, propName, &value);
    if (status !- napi_ok) {
        OH_LOG_ERROR(LogType::LOG_APP, "get float named property failed");
        return defaultValue;
    }

    napi_valuetype type;
    napi_typeof(env, value, &type);
    if (type != napi_number) {
        OH_LOG_ERROR(LogType::LOG_APP, "get float named propperty is not number");
        return defaultValue;
    }

    double result;
    napi_get_value_double(env, value, &result);
    return statuc_cast<float>(result);
}

bool HasProperty(napi_env env, napi_value obj, const char *propName) 
{
    napi_value value;
    napi_status status = napi_get_named_property(env, obj, propName, &value);
    return status == napi_ok;
}

std::vector<float> ParseFloatArray(napi_env env, napi_value arrayValue) 
{
    std::vector<float> result;
    napi_valuetype valuetype;
    napi_status status = napi_typeof(env, arrayValue, &valuetype);
    napi_value lengthProp;
    status = napi_get_named_property(env, arrayValue, "length", &lengthProp);
    uint32_t arrayLength = 0;
    napi_get_value_uint32(env, lengthProp, &arrayLength);
    result.reserve(arrayLength);
    for (uint32_t i = 0; i < arrayLength; i++) {
        napi_value element;
        napi_get_element(env, arrayValue, i, &element);
        napi_valuetype elementType;
        napi_typeof(env, element, &elementType);
        if (elementType == napi_number) {
            double value;
            napi_get_value_double(env, element, &value);
            result.push_back(static_cast<float>(value));
        } else {
            // 如果不是数字，填充0.0f
            result.push_back(0.0f);
        }
    }
    return result;
}

std::vector<int> ParseIntArray(napi_env env, napi_value arrayValue) 
{
    std::vector<int> result;
    napi_valuetype valuetype;
    napi_status status = napi_typeof(env, arrayValue, &valueType);
    napi_value lengthProp;
    status = napi_get_named_property(env, arrayValue, "length", &lengthProp);
    uint32_t arrayLength = 0;
    napi_get_value_uint32(env, lengthProp, &arrayLength);
    result.reserve(arrayLength);
    for (uint32_t i = 0; i < arrayLength; i++) {
        napi_value element;
        napi_get_element(env, arrayValue, i, &element);
        napi_valuetype elementType;
        napi_typeof(env, element, &elementType);
        if (elementType == napi_number) {
            int32_t value;
            napi_get_value_int32(env, element, &value);
            result.push_back(value);
        } else {
            // 如果不是数字，填充0.0f
            result.push_back(0.0f);
        }
    }
    return result;
}
} // namespace Self::UI
