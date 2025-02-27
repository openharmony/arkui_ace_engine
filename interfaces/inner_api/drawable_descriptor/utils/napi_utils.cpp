/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#include <mutex>
#include <vector>

#include "base/resource.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
Resource NapiUtils::ParseJsResource(napi_env env, napi_value value)
{
    napi_value jsId = GetNamedProperty(env, value, "id");
    napi_value jsType = GetNamedProperty(env, value, "type");
    napi_value jsBundleName = GetNamedProperty(env, value, "bundleName");
    napi_value jsModuleName = GetNamedProperty(env, value, "moduleName");

    auto id = ParseJsInt(env, jsId);
    auto type = ParseJsInt(env, jsType);
    auto bundleName = ParseJsString(env, jsBundleName);
    auto moduleName = ParseJsString(env, jsModuleName);

    std::vector<ResourceObjectParams> params;

    // parse the params of the resource
    return Resource(id, type, params, bundleName, moduleName);
}

std::string NapiUtils::ParseJsString(napi_env env, napi_value value)
{
    static constexpr size_t max_length = 2048;
    if (ParseJsType(env, value) != napi_string) {
        return {};
    }
    std::string result;
    size_t stringLength = 0;
    NAPI_CALL_BASE(env, napi_get_value_string_utf8(env, value, nullptr, 0, &stringLength), result);
    if (stringLength == 0 || stringLength > max_length) {
        return result;
    }
    std::vector<char> buffer(stringLength + 1, 0);
    size_t length = 0;
    NAPI_CALL_BASE(env, napi_get_value_string_utf8(env, value, buffer.data(), buffer.size(), &length), result);
    if (length > 0) {
        result.append(buffer.data(), length);
    }
    return result;
}

napi_valuetype NapiUtils::ParseJsType(napi_env env, napi_value value)
{
    if (value == nullptr) {
        return napi_undefined;
    }

    napi_valuetype valueType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, value, &valueType), napi_undefined);
    return valueType;
}

int32_t NapiUtils::ParseJsInt(napi_env env, napi_value value)
{
    int32_t num;
    napi_get_value_int32(env, value, &num);
    return num;
}

napi_value NapiUtils::GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName)
{
    napi_value value = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, object, propertyName.c_str(), &value));
    return value;
}

bool NapiUtils::IsArray(napi_env env, napi_value value)
{
    bool isArray = false;
    napi_status ret = napi_is_array(env, value, &isArray);
    if (ret == napi_ok) {
        return isArray;
    }
    return false;
}

bool NapiUtils::ParseJsBool(napi_env env, napi_value value)
{
    bool boolValue = false;
    napi_status ret = napi_get_value_bool(env, value, &boolValue);
    if (ret == napi_ok) {
        return boolValue;
    }
    return false;
}

napi_value NapiUtils::CreateString(napi_env env, const char* str)
{
    napi_value value = nullptr;
    if (napi_create_string_utf8(env, str, strlen(str), &value) != napi_ok) {
        return nullptr;
    }
    return value;
}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS