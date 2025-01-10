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
#include <memory>
#include <cstddef>

#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "securec.h"
#include "frameworks/base/json/json_util.h"
#include "frameworks/core/common/card_scope.h"
#include "frameworks/core/common/container.h"

namespace OHOS::Ace {
namespace {
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr uint32_t ERROR_COLOR_ID = -1;

enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000
};
} // namespace
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

napi_value ExtNapiUtils::CreateObject(napi_env env)
{
    napi_value object = nullptr;
    NAPI_CALL(env, napi_create_object(env, &object));
    return object;
}

napi_value ExtNapiUtils::CreateDouble(napi_env env, double value)
{
    napi_value jsValue = nullptr;
    NAPI_CALL(env, napi_create_double(env, value, &jsValue));
    return jsValue;
}

napi_value ExtNapiUtils::CreateFunction(napi_env env,
                                        const char* utf8name, size_t length,
                                        napi_callback cb,
                                        void* data)
{
    napi_value jsfuncValue = nullptr;
    napi_create_function(env, utf8name, length, cb, data, &jsfuncValue);
    return jsfuncValue;
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

bool ExtNapiUtils::ParseLengthMetrics(napi_env env, napi_value param, CalcDimension& result)
{
    if (CheckTypeForNapiValue(env, param, napi_object)) {
        napi_value jsValue = GetNamedProperty(env, param, "value");
        napi_value jsUnit = GetNamedProperty(env, param, "unit");
        double value = 0;
        int32_t unit = static_cast<int32_t>(DimensionUnit::VP);
        if (CheckTypeForNapiValue(env, jsValue, napi_number) && CheckTypeForNapiValue(env, jsUnit, napi_number) &&
            napi_get_value_double(env, jsValue, &value) == napi_ok &&
            napi_get_value_int32(env, jsUnit, &unit) == napi_ok && GreatOrEqual(value, 0.0f)) {
            result = CalcDimension(value, static_cast<DimensionUnit>(unit));
            return true;
        }
    }
    return false;
}

napi_value ExtNapiUtils::GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName)
{
    if (GetValueType(env, object) != napi_object) {
        return CreateUndefined(env);
    }

    napi_value value = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, object, propertyName.c_str(), &value));
    return value;
}

bool ExtNapiUtils::IsArray(napi_env env, napi_value value)
{
    bool isArray = false;
    napi_status ret = napi_is_array(env, value, &isArray);
    if (ret == napi_ok) {
        return isArray;
    }
    return false;
}

napi_value ExtNapiUtils::CreateUndefined(napi_env env)
{
    napi_value undefined = nullptr;
    NAPI_CALL(env, napi_get_undefined(env, &undefined));
    return undefined;
}

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

RefPtr<ThemeConstants> ExtNapiUtils::GetThemeConstants(napi_env env, napi_value value)
{
    napi_value jsBundleName = ExtNapiUtils::GetNamedProperty(env, value, "bundleName");
    napi_value jsModuleName = ExtNapiUtils::GetNamedProperty(env, value, "moduleName");
    std::string bundleName = ExtNapiUtils::GetStringFromValueUtf8(env, jsBundleName);
    std::string moduleName = ExtNapiUtils::GetStringFromValueUtf8(env, jsModuleName);

    auto cardId = CardScope::CurrentId();
    if (cardId != INVALID_CARD_ID) {
        auto container = Container::Current();
        auto weak = container->GetCardPipeline(cardId);
        auto cardPipelineContext = weak.Upgrade();
        CHECK_NULL_RETURN(cardPipelineContext, nullptr);
        auto cardThemeManager = cardPipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(cardThemeManager, nullptr);
        return cardThemeManager->GetThemeConstants(bundleName, moduleName);
    }

    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetThemeConstants(bundleName, moduleName);
}

bool ExtNapiUtils::ParseColor(napi_env env, napi_value value, Color& result)
{
    napi_valuetype valueType = ExtNapiUtils::GetValueType(env, value);
    if (valueType != napi_number && valueType != napi_string && valueType != napi_object) {
        return false;
    }
    if (valueType == napi_number) {
        int32_t colorId = ExtNapiUtils::GetCInt32(env, value);
        result = Color(ColorAlphaAdapt(static_cast<uint32_t>(colorId)));
        return true;
    }
    if (valueType == napi_string) {
        std::string colorString = ExtNapiUtils::GetStringFromValueUtf8(env, value);
        return Color::ParseColorString(colorString, result);
    }
    return ParseColorFromResource(env, value, result);
}

bool ExtNapiUtils::ParseColorFromResource(napi_env env, napi_value value, Color& colorResult)
{
    auto themeConstants = GetThemeConstants(env, value);
    CHECK_NULL_RETURN(themeConstants, false);

    napi_value jsColorId = ExtNapiUtils::GetNamedProperty(env, value, "id");
    napi_value jsParams = ExtNapiUtils::GetNamedProperty(env, value, "params");
    uint32_t colorId = static_cast<uint32_t>(ExtNapiUtils::GetCInt32(env, jsColorId));
    if (!ExtNapiUtils::IsArray(env, jsParams)) {
        return false;
    }
    if (colorId == ERROR_COLOR_ID) {
        uint32_t length;
        napi_get_array_length(env, jsParams, &length);
        auto jsonArray = JsonUtil::CreateArray(true);
        for (uint32_t i = 0; i < length; i++) {
            napi_value elementValue;
            napi_get_element(env, jsParams, i, &elementValue);
            std::string key = std::to_string(i);
            jsonArray->Put(key.c_str(), PutJsonValue(env, elementValue, key));
        }
        std::string strKey = std::to_string(0);
        std::string colorName = jsonArray->GetValue(strKey.c_str())->GetValue(strKey.c_str())->ToString();
        colorResult = themeConstants->GetColorByName(colorName);
        return true;
    }
    napi_value jsType = GetNamedProperty(env, value, "type");
    napi_valuetype valueType = GetValueType(env, jsType);
    if (valueType != napi_null && valueType == napi_number &&
        static_cast<uint32_t>(valueType) == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = themeConstants->GetString(ExtNapiUtils::GetCInt32(env, jsType));
        return Color::ParseColorString(value, colorResult);
    }
    if (valueType != napi_null && valueType == napi_number &&
        static_cast<uint32_t>(valueType) == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = themeConstants->GetInt(ExtNapiUtils::GetCInt32(env, jsType));
        colorResult = Color(ColorAlphaAdapt(value));
        return true;
    }
    colorResult = themeConstants->GetColor(colorId);
    return true;
}

void ExtNapiUtils::SetNamedProperty(napi_env env, napi_value object, const std::string& propertyName, napi_value value)
{
    if (GetValueType(env, object) != napi_object) {
        return;
    }

    napi_set_named_property(env, object, propertyName.c_str(), value);
}

std::unique_ptr<JsonValue> ExtNapiUtils::PutJsonValue(napi_env env, napi_value value, std::string& key)
{
    auto result = JsonUtil::Create(true);
    napi_valuetype valueType = ExtNapiUtils::GetValueType(env, value);
    switch (valueType) {
        case napi_boolean: {
            bool boolValue = ExtNapiUtils::GetBool(env, value);
            result->Put(key.c_str(), boolValue);
            break;
        }
        case napi_number: {
            int32_t intValue = ExtNapiUtils::GetCInt32(env, value);
            result->Put(key.c_str(), intValue);
            break;
        }
        case napi_string: {
            std::string stringValue = ExtNapiUtils::GetStringFromValueUtf8(env, value);
            result->Put(key.c_str(), stringValue.c_str());
            break;
        }
        default:
            break;
    }
    return result;
}

bool ExtNapiUtils::ParseColorMetrics(napi_env env, napi_value param, Color& result)
{
    if (CheckTypeForNapiValue(env, param, napi_object)) {
        napi_value jsToNumeric = GetNamedProperty(env, param, "toNumeric");
        napi_value jsColor;
        uint32_t colorVal = 0;
        if (CheckTypeForNapiValue(env, jsToNumeric, napi_function) &&
            napi_call_function(env, param, jsToNumeric, 0, nullptr, &jsColor) == napi_ok &&
            CheckTypeForNapiValue(env, jsColor, napi_number) &&
            napi_get_value_uint32(env, jsColor, &colorVal) == napi_ok) {
            result.SetValue(colorVal);
            return true;
        }
    }
    return false;
}
} // namespace OHOS::Ace
