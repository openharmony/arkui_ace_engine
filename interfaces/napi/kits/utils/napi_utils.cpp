/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "napi_utils.h"

#include <cstddef>

#include "js_native_api_types.h"

#include "base/utils/string_utils.h"
#include "core/animation/curve.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_wrapper.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Napi {
using namespace OHOS::Ace;
namespace {

const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
constexpr int32_t NAPI_BUF_LENGTH = 256;
constexpr int32_t UNKNOWN_RESOURCE_ID = -1;
std::vector<std::string> RESOURCE_HEADS = { "app", "sys" };
} // namespace

static const std::unordered_map<int32_t, std::string> ERROR_CODE_TO_MSG {
    { Framework::ERROR_CODE_PERMISSION_DENIED, "Permission denied. " },
    { Framework::ERROR_CODE_PARAM_INVALID, "Parameter error. " },
    { Framework::ERROR_CODE_SYSTEMCAP_ERROR, "Capability not supported. " },
    { Framework::ERROR_CODE_INTERNAL_ERROR, "Internal error. " },
    { Framework::ERROR_CODE_URI_ERROR, "Uri error. " },
    { Framework::ERROR_CODE_PAGE_STACK_FULL, "Page stack error. " },
    { Framework::ERROR_CODE_URI_ERROR_LITE, "Uri error. " }
};

void NapiThrow(napi_env env, const std::string& message, int32_t errCode)
{
    napi_value code = nullptr;
    std::string strCode = std::to_string(errCode);
    napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);

    napi_value msg = nullptr;
    auto iter = ERROR_CODE_TO_MSG.find(errCode);
    std::string strMsg = (iter != ERROR_CODE_TO_MSG.end() ? iter->second : "") + message;
    LOGE("napi throw errCode %d strMsg %s", errCode, strMsg.c_str());
    napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);

    napi_value error = nullptr;
    napi_create_error(env, code, msg, &error);
    napi_throw(env, error);
}

void ReplaceHolder(std::string& originStr, const std::vector<std::string>& params, int32_t containCount)
{
    auto size = static_cast<int32_t>(params.size());
    if (containCount == size) {
        return;
    }
    std::string::const_iterator start = originStr.begin();
    std::string::const_iterator end = originStr.end();
    std::smatch matches;
    bool shortHolderType = false;
    bool firstMatch = true;
    int searchTime = 0;
    while (std::regex_search(start, end, matches, RESOURCE_APP_STRING_PLACEHOLDER)) {
        std::string pos = matches[2];
        std::string type = matches[4];
        if (firstMatch) {
            firstMatch = false;
            shortHolderType = pos.length() == 0;
        } else {
            if (static_cast<uint32_t>(shortHolderType) ^ ((uint32_t)(pos.length() == 0))) {
                LOGE("wrong place holder,stop parse string");
                return;
            }
        }

        std::string replaceContentStr;
        std::string::size_type index;
        if (shortHolderType) {
            index = static_cast<uint32_t>(searchTime + containCount);
        } else {
            index = static_cast<uint32_t>(StringUtils::StringToInt(pos) - 1 + containCount);
        }
        replaceContentStr = params[index];

        originStr.replace(matches[0].first - originStr.begin(), matches[0].length(), replaceContentStr);
        start = originStr.begin() + matches.prefix().length() + replaceContentStr.length();
        end = originStr.end();
        searchTime++;
    }
}

size_t GetParamLen(napi_env env, napi_value param)
{
    size_t buffSize = 0;
    napi_status status = napi_get_value_string_utf8(env, param, nullptr, 0, &buffSize);
    if (status != napi_ok || buffSize == 0) {
        return 0;
    }
    return buffSize;
}

bool GetNapiString(napi_env env, napi_value value, std::string& retStr, napi_valuetype& valueType)
{
    size_t ret = 0;
    napi_typeof(env, value, &valueType);
    if (valueType == napi_string) {
        if (GetParamLen(env, value) == 0) {
            return false;
        }
        size_t valueLen = GetParamLen(env, value) + 1;
        std::unique_ptr<char[]> buffer = std::make_unique<char[]>(valueLen);
        napi_get_value_string_utf8(env, value, buffer.get(), valueLen, &ret);
        retStr = buffer.get();
        return true;
    }
    if (valueType == napi_object) {
        ResourceInfo recv;
        if (ParseResourceParam(env, value, recv)) {
            ParseString(recv, retStr);
            return true;
        }
    }
    return false;
}

RefPtr<ThemeConstants> GetThemeConstants(const std::optional<std::string>& bundleName = std::nullopt,
    const std::optional<std::string>& moduleName = std::nullopt)
{
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return nullptr;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        LOGE("pipelineContext is null!");
        return nullptr;
    }
    auto themeManager = pipelineContext->GetThemeManager();
    if (!themeManager) {
        LOGE("themeManager is null!");
        return nullptr;
    }
    if (bundleName.has_value() && moduleName.has_value()) {
        return themeManager->GetThemeConstants(bundleName.value_or(""), moduleName.value_or(""));
    }
    return themeManager->GetThemeConstants();
}

RefPtr<ResourceWrapper> CreateResourceWrapper(const ResourceInfo& info)
{
    auto bundleName = info.bundleName;
    auto moduleName = info.moduleName;

    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        if (bundleName.has_value() && moduleName.has_value()) {
            auto resourceObject = AceType::MakeRefPtr<ResourceObject>(bundleName.value_or(""), moduleName.value_or(""));
            resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
        } else {
            resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter();
        }
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = GetThemeConstants(info.bundleName, info.moduleName);
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

napi_value CreateNapiString(napi_env env, std::string rawStr)
{
    napi_value retVal = nullptr;
    napi_create_string_utf8(env, rawStr.c_str(), rawStr.length(), &retVal);
    return retVal;
}

bool ConvertResourceType(const std::string& typeName, ResourceType& resType)
{
    static const std::unordered_map<std::string, ResourceType> resTypeMap {
        { "color", ResourceType::COLOR },
        { "media", ResourceType::MEDIA },
        { "float", ResourceType::FLOAT },
        { "string", ResourceType::STRING },
        { "plural", ResourceType::PLURAL },
        { "pattern", ResourceType::PATTERN },
        { "boolean", ResourceType::BOOLEAN },
        { "integer", ResourceType::INTEGER },
        { "strarray", ResourceType::STRARRAY },
        { "intarray", ResourceType::INTARRAY },
    };
    auto it = resTypeMap.find(typeName);
    if (it == resTypeMap.end()) {
        return false;
    }
    resType = it->second;
    return true;
}

bool ParseDollarResource(napi_env env, napi_value value, ResourceType& resType, std::string& resName)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_string) {
        return false;
    }
    std::string resPath;
    if (!GetNapiString(env, value, resPath, valueType)) {
        return false;
    }
    std::vector<std::string> tokens;
    StringUtils::StringSplitter(resPath, '.', tokens);
    if (static_cast<int32_t>(tokens.size()) != 3) { // $r format like app.xxx.xxx, has 3 paragraph
        return false;
    }
    if (std::find(RESOURCE_HEADS.begin(), RESOURCE_HEADS.end(), tokens[0]) == RESOURCE_HEADS.end()) {
        return false;
    }
    if (!ConvertResourceType(tokens[1], resType)) {
        return false;
    }
    resName = resPath;
    return true;
}

void CompleteResourceParam(napi_env env, napi_value value)
{
    napi_value idNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_object) {
        return;
    }
    if (napi_get_named_property(env, value, "id", &idNApi) != napi_ok) {
        return;
    }
    std::string resName;
    ResourceType resType;
    if (!ParseDollarResource(env, idNApi, resType, resName)) {
        return;
    }
    bool hasProperty = false;
    napi_value typeIdNApi = nullptr;
    napi_value resourceIdNApi = nullptr;
    napi_value typeKeyNApi = CreateNapiString(env, "type");
    napi_value defaultNameNApi = CreateNapiString(env, "");
    napi_value bundleNameKeyNApi = CreateNapiString(env, "bundleName");
    napi_value moduleNameKeyNApi = CreateNapiString(env, "moduleName");
    napi_create_int32(env, UNKNOWN_RESOURCE_ID, &resourceIdNApi);
    napi_create_int32(env, static_cast<uint32_t>(resType), &typeIdNApi);
    ModifyResourceParam(env, value, resType, resName);
    napi_set_property(env, value, typeKeyNApi, typeIdNApi);
    napi_set_property(env, value, CreateNapiString(env, "id"), resourceIdNApi);
    napi_has_property(env, value, bundleNameKeyNApi, &hasProperty);
    if (!hasProperty) {
        napi_set_property(env, value, bundleNameKeyNApi, defaultNameNApi);
    }
    napi_has_property(env, value, moduleNameKeyNApi, &hasProperty);
    if (!hasProperty) {
        napi_set_property(env, value, moduleNameKeyNApi, defaultNameNApi);
    }
}

void ModifyResourceParam(napi_env env, napi_value value, const ResourceType& resType, const std::string& resName)
{
    // raw input : {"id":"app.xxx.xxx","params":[],"moduleName":"xxx","bundleName":"xxx"}
    // modified output : {"id":-1, "params":["app.xxx.xxx"],"type":xxxx,"moduleName":"xxx","bundleName":"xxx"}
    napi_value paramsNApi = nullptr;
    napi_get_named_property(env, value, "params", &paramsNApi);
    bool isArray = false;
    if (napi_is_array(env, paramsNApi, &isArray) != napi_ok) {
        return;
    }
    if (!isArray) {
        return;
    }
    uint32_t paramCount = 0;
    bool hasProperty = false;
    napi_get_array_length(env, paramsNApi, &paramCount);
    napi_value typeKeyNApi = CreateNapiString(env, "type");
    napi_value resNameNApi = CreateNapiString(env, resName);
    if (resType == ResourceType::PLURAL || resType == ResourceType::STRING) {
        std::vector<napi_value> tmpParams;
        for (uint32_t i = 0; i < paramCount; i++) {
            napi_value param = nullptr;
            napi_get_element(env, paramsNApi, i, &param);
            tmpParams.insert(tmpParams.end(), param);
        }
        napi_set_element(env, paramsNApi, 0, resNameNApi);
        uint32_t paramIndex = 1;
        napi_has_property(env, value, typeKeyNApi, &hasProperty);
        if (hasProperty) {
            napi_value firstParam = nullptr;
            napi_get_property(env, value, typeKeyNApi, &firstParam);
            napi_set_element(env, paramsNApi, paramIndex, firstParam);
            paramIndex++;
        }
        for (auto tmpParam : tmpParams) {
            napi_set_element(env, paramsNApi, paramIndex, tmpParam);
            paramIndex++;
        }
    } else {
        napi_set_element(env, paramsNApi, 0, resNameNApi);
    }
}

void ParseCurveInfo(const std::string& curveString, std::string& curveTypeString, std::vector<float>& curveValue)
{
    if (curveString.back() != ')') {
        return;
    }
    std::string::size_type leftEmbracePosition = curveString.find_last_of('(');
    if (leftEmbracePosition == std::string::npos) {
        return;
    }
    curveTypeString = curveString.substr(0, leftEmbracePosition);
    auto params = curveString.substr(leftEmbracePosition + 1, curveString.length() - leftEmbracePosition - 2);
    if (curveTypeString.empty() || params.empty()) {
        return;
    }
    std::vector<std::string> paramsVector;
    StringUtils::StringSplitter(params, ',', paramsVector);
    for (auto& param : paramsVector) {
        Framework::RemoveHeadTailSpace(param);
        if (param == "true" || param == "start") {
            param = "1.000000";
        }
        if (param == "false" || param == "end") {
            param = "0.000000";
        }
        curveValue.emplace_back(std::stof(param));
    }
}

napi_value ParseCurve(napi_env env, napi_value value, std::string& curveTypeString, std::vector<float>& curveValue)
{
    CHECK_NULL_RETURN(value, nullptr);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    NAPI_ASSERT(env, valueType == napi_object || valueType == napi_string, "The type of curve is incorrect");
    if (valueType == napi_object) {
        napi_value curveObjectNApi = nullptr;
        napi_get_named_property(env, value, "__curveString", &curveObjectNApi);
        value = curveObjectNApi;
    }

    size_t paramLen = 0;
    napi_status status = napi_get_value_string_utf8(env, value, nullptr, 0, &paramLen);
    NAPI_ASSERT(env, paramLen > 0 && paramLen < NAPI_BUF_LENGTH && status == napi_ok, "paramLen error");
    char params[NAPI_BUF_LENGTH] = { 0 };
    status = napi_get_value_string_utf8(env, value, params, paramLen + 1, &paramLen);
    NAPI_ASSERT(env, status == napi_ok, "Parse curve failed");

    RefPtr<Curve> curve;
    const std::string domAnimationDefaultCurveString = "ease-in-out";
    if (params[0] == '\0') {
        curve = Framework::CreateCurve(domAnimationDefaultCurveString);
    } else {
        curve = Framework::CreateCurve(params);
    }
    std::string curveString = curve->ToString();
    LOGI("curveString %{public}s", curveString.c_str());
    ParseCurveInfo(curveString, curveTypeString, curveValue);
    LOGI("curveTypeString %{public}s", curveTypeString.c_str());
    return nullptr;
}

napi_valuetype GetValueType(napi_env env, napi_value value)
{
    if (value == nullptr) {
        return napi_undefined;
    }

    napi_valuetype valueType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, value, &valueType), napi_undefined);
    return valueType;
}

std::optional<std::string> GetStringFromValueUtf8(napi_env env, napi_value value)
{
    static constexpr size_t maxLength = 2048;
    if (GetValueType(env, value) != napi_string) {
        return std::nullopt;
    }

    size_t paramLen = 0;
    napi_status status = napi_get_value_string_utf8(env, value, nullptr, 0, &paramLen);
    if (paramLen == 0 || paramLen > maxLength || status != napi_ok) {
        return std::nullopt;
    }
    char params[maxLength] = { 0 };
    status = napi_get_value_string_utf8(env, value, params, paramLen + 1, &paramLen);
    if (status != napi_ok) {
        return std::nullopt;
    }
    return params;
}

bool GetIntProperty(napi_env env, napi_value value, const std::string& key, int32_t& result)
{
    CHECK_NULL_RETURN(value, false);
    napi_valuetype valueType = napi_undefined;
    napi_value propertyNApi = nullptr;
    napi_get_named_property(env, value, key.c_str(), &propertyNApi);
    if (valueType != napi_number) {
        LOGE("The type of property is incorrect");
        return false;
    }
    int32_t property = 0;
    napi_status status = napi_get_value_int32(env, propertyNApi, &property);
    if (status != napi_ok) {
        LOGE("Get property failed");
        return false;
    }
    return true;
}

static uint32_t CompleteColorAlphaIfIncomplete(uint32_t origin)
{
    constexpr uint32_t colorAlphaOffset = 24;
    constexpr uint32_t colorAlphaDefaultValue = 0xFF000000;
    uint32_t result = origin;
    if ((origin >> colorAlphaOffset) == 0) {
        result = origin | colorAlphaDefaultValue;
    }
    return result;
}

bool ParseColorFromResourceObject(napi_env env, napi_value value, Color& colorResult)
{
    ResourceInfo resourceInfo;
    if (!ParseResourceParam(env, value, resourceInfo)) {
        LOGE("Parse color from resource failed");
        return false;
    }
    auto themeConstants = GetThemeConstants(resourceInfo.bundleName, resourceInfo.moduleName);
    if (themeConstants == nullptr) {
        LOGE("themeConstants is nullptr");
        return false;
    }
    if (resourceInfo.type == static_cast<int32_t>(ResourceType::STRING)) {
        auto colorString = themeConstants->GetString(resourceInfo.type);
        return Color::ParseColorString(colorString, colorResult);
    }
    if (resourceInfo.type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto colorInt = themeConstants->GetInt(resourceInfo.type);
        colorResult = Color(CompleteColorAlphaIfIncomplete(colorInt));
        return true;
    }
    colorResult = themeConstants->GetColor(resourceInfo.resId);
    return true;
}

bool ParseColor(napi_env env, napi_value value, Color& result)
{
    napi_valuetype valueType = GetValueType(env, value);
    if (valueType != napi_number && valueType != napi_string && valueType != napi_object) {
        return false;
    }
    if (valueType == napi_number) {
        int32_t colorId = 0;
        napi_get_value_int32(env, value, &colorId);
        result = Color(CompleteColorAlphaIfIncomplete(static_cast<uint32_t>(colorId)));
        return true;
    }
    if (valueType == napi_string) {
        std::optional<std::string> colorString = GetStringFromValueUtf8(env, value);
        if (!colorString.has_value()) {
            LOGE("Parse color from string failed");
        }
        return Color::ParseColorString(colorString.value(), result);
    }

    return ParseColorFromResourceObject(env, value, result);
}

bool ParseResourceParam(napi_env env, napi_value value, ResourceInfo& info)
{
    CompleteResourceParam(env, value);
    napi_value idNApi = nullptr;
    napi_value typeNApi = nullptr;
    napi_value paramsNApi = nullptr;
    napi_value bundleNameNApi = nullptr;
    napi_value moduleNameNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, value, "id", &idNApi);
        napi_get_named_property(env, value, "type", &typeNApi);
        napi_get_named_property(env, value, "params", &paramsNApi);
        napi_get_named_property(env, value, "bundleName", &bundleNameNApi);
        napi_get_named_property(env, value, "moduleName", &moduleNameNApi);
    } else {
        return false;
    }

    napi_typeof(env, idNApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, idNApi, &info.resId);
    }

    napi_typeof(env, typeNApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, typeNApi, &info.type);
    }

    bool isArray = false;
    if (napi_is_array(env, paramsNApi, &isArray) != napi_ok) {
        return false;
    }

    if (!isArray) {
        return false;
    }

    uint32_t arrayLength = 0;
    napi_get_array_length(env, paramsNApi, &arrayLength);

    for (uint32_t i = 0; i < arrayLength; i++) {
        size_t ret = 0;
        napi_value indexValue = nullptr;
        napi_get_element(env, paramsNApi, i, &indexValue);
        napi_typeof(env, indexValue, &valueType);
        if (valueType == napi_string) {
            size_t strLen = GetParamLen(env, indexValue) + 1;
            std::unique_ptr<char[]> indexStr = std::make_unique<char[]>(strLen);
            napi_get_value_string_utf8(env, indexValue, indexStr.get(), strLen, &ret);
            info.params.emplace_back(indexStr.get());
        } else if (valueType == napi_number) {
            int32_t num;
            napi_get_value_int32(env, indexValue, &num);
            info.params.emplace_back(std::to_string(num));
        }
    }

    napi_typeof(env, bundleNameNApi, &valueType);
    if (valueType == napi_string) {
        size_t ret = 0;
        size_t strLen = GetParamLen(env, bundleNameNApi) + 1;
        std::unique_ptr<char[]> bundleNameStr = std::make_unique<char[]>(strLen);
        napi_get_value_string_utf8(env, bundleNameNApi, bundleNameStr.get(), strLen, &ret);
        info.bundleName = bundleNameStr.get();
    }

    napi_typeof(env, moduleNameNApi, &valueType);
    if (valueType == napi_string) {
        size_t ret = 0;
        size_t strLen = GetParamLen(env, moduleNameNApi) + 1;
        std::unique_ptr<char[]> moduleNameStr = std::make_unique<char[]>(strLen);
        napi_get_value_string_utf8(env, moduleNameNApi, moduleNameStr.get(), strLen, &ret);
        info.moduleName = moduleNameStr.get();
    }

    return true;
}

std::string DimensionToString(Dimension dimension)
{
    static const int32_t unitsNum = 6;
    static const int32_t percentIndex = 3;
    static const int32_t percentUnit = 100;
    static std::array<std::string, unitsNum> units = { "px", "vp", "fp", "%", "lpx", "auto" };
    auto unit = dimension.Unit();
    auto value = dimension.Value();
    if (unit == DimensionUnit::NONE) {
        return StringUtils::DoubleToString(value).append("none");
    }
    if (units[static_cast<int>(unit)] == units[percentIndex]) {
        return StringUtils::DoubleToString(value * percentUnit).append(units[static_cast<int>(unit)]);
    }
    return StringUtils::DoubleToString(value).append(units[static_cast<int>(unit)]);
}

bool ParseString(const ResourceInfo& info, std::string& result)
{
    auto resourceWrapper = CreateResourceWrapper(info);

    if (info.type == static_cast<int>(ResourceType::PLURAL)) {
        std::string pluralResults;
        if (info.resId == UNKNOWN_RESOURCE_ID) {
            auto count = StringUtils::StringToInt(info.params[1]);
            pluralResults = resourceWrapper->GetPluralStringByName(info.params[0], count);
            ReplaceHolder(pluralResults, info.params, 2); // plural holder in index 2
        } else {
            auto count = StringUtils::StringToInt(info.params[0]);
            pluralResults = resourceWrapper->GetPluralString(info.resId, count);
            ReplaceHolder(pluralResults, info.params, 1);
        }
        result = pluralResults;
        return true;
    }
    if (info.type == static_cast<int>(ResourceType::RAWFILE)) {
        auto fileName = info.params[0];
        result = resourceWrapper->GetRawfile(fileName);
        return true;
    }
    if (info.type == static_cast<int>(ResourceType::FLOAT)) {
        if (info.resId == UNKNOWN_RESOURCE_ID) {
            result = DimensionToString(resourceWrapper->GetDimensionByName(info.params[0]));
        } else {
            result = DimensionToString(resourceWrapper->GetDimension(info.resId));
        }
        return true;
    }
    if (info.type == static_cast<int>(ResourceType::STRING)) {
        std::string originStr;
        if (info.resId == UNKNOWN_RESOURCE_ID) {
            originStr = resourceWrapper->GetStringByName(info.params[0]);
            ReplaceHolder(originStr, info.params, 1);
        } else {
            originStr = resourceWrapper->GetString(info.resId);
            ReplaceHolder(originStr, info.params, 0);
        }
        result = originStr;
        return true;
    }
    return true;
}

std::string ErrorToMessage(int32_t code)
{
    auto iter = ERROR_CODE_TO_MSG.find(code);
    return (iter != ERROR_CODE_TO_MSG.end()) ? iter->second : "";
}

bool GetSingleParam(napi_env env, napi_callback_info info, napi_value* argv, napi_valuetype& valueType)
{
    size_t argc = 1;
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc != 1) {
        return false;
    }
    napi_typeof(env, argv[0], &valueType);
    return true;
}

// (Color | number | string | undifened)
std::optional<Color> GetOptionalColor(napi_env env, napi_value argv, napi_valuetype& valueType)
{
    if (valueType == napi_number) {
        uint32_t num;
        uint32_t alpha = 0xff000000;
        napi_get_value_uint32(env, argv, &num);
        if ((num & alpha) == 0) {
            num |= alpha;
        }
        return Color(num);
    } else if (valueType == napi_string) {
        std::string str;
        bool result = GetNapiString(env, argv, str, valueType);
        Color color;
        if (!result || !Color::ParseColorString(str, color)) {
            return std::nullopt;
        }
        return color;
    } else {
        return std::nullopt;
    }
}

} // namespace OHOS::Ace::Napi
