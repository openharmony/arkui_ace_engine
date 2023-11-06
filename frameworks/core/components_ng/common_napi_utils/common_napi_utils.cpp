/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/common_napi_utils/common_napi_utils.h"

#include <cstddef>

#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "securec.h"

#include "base/json/json_util.h"
#include "core/common/card_scope.h"
#include "core/common/container.h"

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

NapiAsyncEvnet::NapiAsyncEvnet(napi_env env, napi_value callback)
{
    env_ = env;
    napi_create_reference(env_, callback, 1, &ref_);
}

NapiAsyncEvnet::~NapiAsyncEvnet()
{
    napi_delete_reference(env_, ref_);
}

napi_value NapiAsyncEvnet::Call(int32_t argc, napi_value* argv)
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

napi_env NapiAsyncEvnet::GetEnv()
{
    return env_;
}

napi_value CommonNapiUtils::CreateInt32(napi_env env, int32_t code)
{
    napi_value value = nullptr;
    if (napi_create_int32(env, code, &value) != napi_ok) {
        return nullptr;
    }
    return value;
}

int32_t CommonNapiUtils::GetCInt32(napi_value value, napi_env env)
{
    int32_t num;
    napi_get_value_int32(env, value, &num);
    return num;
}

int64_t CommonNapiUtils::GetCInt64(napi_value value, napi_env env)
{
    int64_t num;
    napi_get_value_int64(env, value, &num);
    return num;
}

napi_value CommonNapiUtils::CreateBoolean(napi_env env, bool value)
{
    napi_value jsValue = nullptr;
    NAPI_CALL(env, napi_get_boolean(env, value, &jsValue));
    return jsValue;
}

bool CommonNapiUtils::GetBool(napi_env env, napi_value value)
{
    bool boolValue = false;
    napi_status ret = napi_get_value_bool(env, value, &boolValue);
    if (ret == napi_ok) {
        return boolValue;
    }
    return false;
}

napi_value CommonNapiUtils::CreateDouble(napi_env env, double value)
{
    napi_value jsValue = nullptr;
    NAPI_CALL(env, napi_create_double(env, value, &jsValue));
    return jsValue;
}

double CommonNapiUtils::GetDouble(napi_env env, napi_value value)
{
    double numberValue = 0;
    napi_status ret = napi_get_value_double(env, value, &numberValue);
    if (ret == napi_ok) {
        return numberValue;
    }
    return 0;
}

size_t CommonNapiUtils::GetCString(napi_value value, napi_env env, char* buffer, size_t bufSize)
{
    size_t valueLength;
    napi_get_value_string_utf8(env, value, buffer, bufSize, &valueLength);
    return valueLength;
}

napi_value CommonNapiUtils::CreateStringUtf8(napi_env env, const std::string& str)
{
    napi_value value = nullptr;
    if (napi_create_string_utf8(env, str.c_str(), strlen(str.c_str()), &value) != napi_ok) {
        return nullptr;
    }
    return value;
}

std::string CommonNapiUtils::GetStringFromValueUtf8(napi_env env, napi_value value)
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

napi_value CommonNapiUtils::CreateNull(napi_env env)
{
    napi_value jsNull = nullptr;
    NAPI_CALL(env, napi_get_null(env, &jsNull));
    return jsNull;
}

napi_value CommonNapiUtils::CreateUndefined(napi_env env)
{
    napi_value undefined = nullptr;
    NAPI_CALL(env, napi_get_undefined(env, &undefined));
    return undefined;
}

napi_valuetype CommonNapiUtils::GetValueType(napi_env env, napi_value value)
{
    if (value == nullptr) {
        return napi_undefined;
    }

    napi_valuetype valueType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, value, &valueType), napi_undefined);
    return valueType;
}

napi_value CommonNapiUtils::CreateObject(napi_env env)
{
    napi_value object = nullptr;
    NAPI_CALL(env, napi_create_object(env, &object));
    return object;
}

void CommonNapiUtils::DefineProperties(
    napi_env env, napi_value object, const std::initializer_list<napi_property_descriptor>& properties)
{
    napi_property_descriptor descriptors[properties.size()];
    std::copy(properties.begin(), properties.end(), descriptors);

    (void)napi_define_properties(env, object, properties.size(), descriptors);
}

void CommonNapiUtils::DefineClass(napi_env env, napi_value exports,
    const std::initializer_list<napi_property_descriptor>& properties, const std::string& className)
{
    auto constructor = [](napi_env env, napi_callback_info info) -> napi_value {
        napi_value thisVal = nullptr;
        NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVal, nullptr));

        return thisVal;
    };

    napi_value jsConstructor = nullptr;

    napi_property_descriptor descriptors[properties.size()];
    std::copy(properties.begin(), properties.end(), descriptors);

    NAPI_CALL_RETURN_VOID(env, napi_define_class(env, className.c_str(), NAPI_AUTO_LENGTH, constructor, nullptr,
                                   properties.size(), descriptors, &jsConstructor));

    SetNamedProperty(env, exports, className, jsConstructor);
}

void CommonNapiUtils::SetNamedProperty(
    napi_env env, napi_value object, const std::string& propertyName, napi_value value)
{
    if (GetValueType(env, object) != napi_object) {
        return;
    }

    napi_set_named_property(env, object, propertyName.c_str(), value);
}

napi_value CommonNapiUtils::GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName)
{
    if (GetValueType(env, object) != napi_object) {
        return CreateUndefined(env);
    }

    napi_value value = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, object, propertyName.c_str(), &value));
    return value;
}

bool CommonNapiUtils::HasNamedProperty(napi_env env, napi_value object, const std::string& propertyName)
{
    if (GetValueType(env, object) != napi_object) {
        return false;
    }

    bool hasProperty = false;
    NAPI_CALL_BASE(env, napi_has_named_property(env, object, propertyName.c_str(), &hasProperty), false);
    return hasProperty;
}

bool CommonNapiUtils::GetPropertyNames(napi_env env, napi_value object, std::vector<std::string>& nameList)
{
    napi_value names = nullptr;
    NAPI_CALL_BASE(env, napi_get_property_names(env, object, &names), false);
    uint32_t length = 0;
    NAPI_CALL_BASE(env, napi_get_array_length(env, names, &length), false);
    for (uint32_t index = 0; index < length; ++index) {
        napi_value name = nullptr;
        if (napi_get_element(env, names, index, &name) != napi_ok) {
            continue;
        }
        if (GetValueType(env, name) != napi_string) {
            continue;
        }
        nameList.emplace_back(GetStringFromValueUtf8(env, name));
    }
    return true;
}

bool CommonNapiUtils::IsArray(napi_env env, napi_value value)
{
    bool isArray = false;
    napi_status ret = napi_is_array(env, value, &isArray);
    if (ret == napi_ok) {
        return isArray;
    }
    return false;
}

napi_value CommonNapiUtils::CreateArray(napi_env env)
{
    napi_value value = nullptr;
    NAPI_CALL(env, napi_create_array(env, &value));
    return value;
}

void CommonNapiUtils::SetSelementToArray(napi_env env, napi_value array, int index, napi_value value)
{
    napi_set_element(env, array, index, value);
}

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

RefPtr<ThemeConstants> CommonNapiUtils::GetThemeConstants(napi_env env, napi_value value)
{
    napi_value jsBundleName = CommonNapiUtils::GetNamedProperty(env, value, "bundleName");
    napi_value jsModuleName = CommonNapiUtils::GetNamedProperty(env, value, "moduleName");
    std::string bundleName = CommonNapiUtils::GetStringFromValueUtf8(env, jsBundleName);
    std::string moduleName = CommonNapiUtils::GetStringFromValueUtf8(env, jsModuleName);

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

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetThemeConstants(bundleName, moduleName);
}

std::unique_ptr<JsonValue> CommonNapiUtils::PutJsonValue(napi_env env, napi_value value, std::string& key)
{
    auto result = JsonUtil::Create(true);
    napi_valuetype valueType = CommonNapiUtils::GetValueType(env, value);
    switch (valueType) {
        case napi_boolean: {
            bool boolValue = CommonNapiUtils::GetBool(env, value);
            result->Put(key.c_str(), boolValue);
            break;
        }
        case napi_number: {
            int32_t intValue = CommonNapiUtils::GetCInt32(value, env);
            result->Put(key.c_str(), intValue);
            break;
        }
        case napi_string: {
            std::string stringValue = CommonNapiUtils::GetStringFromValueUtf8(env, value);
            result->Put(key.c_str(), stringValue.c_str());
            break;
        }
        default:
            break;
    }
    return result;
}

bool CommonNapiUtils::ParseColorFromResource(napi_env env, napi_value value, Color& colorResult)
{
    auto themeConstants = GetThemeConstants(env, value);
    CHECK_NULL_RETURN(themeConstants, false);

    napi_value jsColorId = CommonNapiUtils::GetNamedProperty(env, value, "id");
    napi_value jsParams = CommonNapiUtils::GetNamedProperty(env, value, "params");
    uint32_t colorId = CommonNapiUtils::GetCInt32(jsColorId, env);
    if (!CommonNapiUtils::IsArray(env, jsParams)) {
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
        const char* jsonKey = std::to_string(0).c_str();
        std::string colorName = jsonArray->GetValue(jsonKey)->GetValue(jsonKey)->ToString();
        colorResult = themeConstants->GetColorByName(colorName);
        return true;
    }
    napi_value jsType = GetNamedProperty(env, value, "type");
    napi_valuetype valueType = GetValueType(env, jsType);
    if (valueType != napi_null && valueType == napi_number &&
        valueType == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = themeConstants->GetString(CommonNapiUtils::GetCInt32(jsType, env));
        return Color::ParseColorString(value, colorResult);
    }
    if (valueType != napi_null && valueType == napi_number &&
        valueType == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = themeConstants->GetInt(CommonNapiUtils::GetCInt32(jsType, env));
        colorResult = Color(ColorAlphaAdapt(value));
        return true;
    }
    colorResult = themeConstants->GetColor(colorId);
    return true;
}

bool CommonNapiUtils::ParseColor(napi_env env, napi_value value, Color& result)
{
    napi_valuetype valueType = CommonNapiUtils::GetValueType(env, value);
    if (valueType != napi_number && valueType != napi_string && valueType != napi_object) {
        return false;
    }
    if (valueType == napi_number) {
        int32_t colorId = CommonNapiUtils::GetCInt32(value, env);
        result = Color(ColorAlphaAdapt((uint32_t)colorId));
        return true;
    }
    if (valueType == napi_string) {
        std::string colorString = CommonNapiUtils::GetStringFromValueUtf8(env, value);
        return Color::ParseColorString(colorString, result);
    }
    return ParseColorFromResource(env, value, result);
}

bool CommonNapiUtils::GetDimensionResult(napi_env env, napi_value value, CalcDimension& result)
{
    napi_valuetype valueType = GetValueType(env, value);
    if (valueType == napi_number) {
        double radius = GetDouble(env, value);
        result = CalcDimension(radius, DimensionUnit::VP);
        return true;
    }
    if (valueType == napi_string) {
        std::string dimensionString = GetStringFromValueUtf8(env, value);
        result = StringUtils::StringToCalcDimension(dimensionString, false, DimensionUnit::VP);
        return true;
    }
    auto themeConstants = GetThemeConstants(env, value);
    CHECK_NULL_RETURN(themeConstants, false);

    napi_value jsDimensionId = GetNamedProperty(env, value, "id");
    napi_value jsParams = GetNamedProperty(env, value, "params");
    uint32_t dimensionId = GetCInt32(jsDimensionId, env);
    if (!IsArray(env, jsParams)) {
        return false;
    }
    if (dimensionId == ERROR_COLOR_ID) {
        uint32_t length;
        napi_get_array_length(env, jsParams, &length);
        auto jsonArray = JsonUtil::CreateArray(true);
        for (uint32_t i = 0; i < length; i++) {
            napi_value elementValue;
            napi_get_element(env, jsParams, i, &elementValue);
            std::string key = std::to_string(i);
            jsonArray->Put(key.c_str(), PutJsonValue(env, elementValue, key));
        }
        const char* jsonKey = std::to_string(0).c_str();
        std::string dimensionName = jsonArray->GetValue(jsonKey)->GetValue(jsonKey)->ToString();
        result = themeConstants->GetDimensionByName(dimensionName);
        return true;
    }

    napi_value jsType = GetNamedProperty(env, value, "type");
    napi_valuetype temp = GetValueType(env, jsType);
    uint32_t type = GetCInt32(jsType, env);
    if (temp != napi_null && temp == napi_number && type == static_cast<uint32_t>(ResourceType::STRING)) {
        auto dimensionValue = themeConstants->GetString(dimensionId);
        result = StringUtils::StringToCalcDimension(dimensionValue, false, DimensionUnit::VP);
        return true;
    }
    if (temp != napi_null && temp == napi_number && type == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto dimensionValue = std::to_string(themeConstants->GetInt(dimensionId));
        result = StringUtils::StringToDimensionWithUnit(dimensionValue, DimensionUnit::VP);
        return true;
    }

    result = themeConstants->GetDimension(dimensionId);
    return true;
}
} // namespace OHOS::Ace
