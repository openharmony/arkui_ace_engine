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
#include "js_native_api_types.h"

namespace OHOS::Ace::Napi {
namespace {

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

const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
constexpr size_t MAX_STRING_BUFF_SIZE = 1024;

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
    if (status != napi_ok || buffSize == 0 || buffSize >= MAX_STRING_BUFF_SIZE) {
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

bool ParseResourceParam(napi_env env, napi_value value, ResourceInfo& info)
{
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
    auto themeConstants = GetThemeConstants(info.bundleName, info.moduleName);
    if (!themeConstants) {
        LOGE("themeConstants is nullptr");
        return false;
    }

    if (info.type == static_cast<int>(ResourceType::PLURAL)) {
        auto count = StringUtils::StringToDouble(info.params[0]);
        auto pluralResults = themeConstants->GetStringArray(info.resId);
        auto pluralChoice = Localization::GetInstance()->PluralRulesFormat(count);
        auto iter = std::find(pluralResults.begin(), pluralResults.end(), pluralChoice);
        std::string originStr;
        if (iter != pluralResults.end() && ++iter != pluralResults.end()) {
            originStr = *iter;
        }
        ReplaceHolder(originStr, info.params, 1);
        result = originStr;
    } else if (info.type == static_cast<int>(ResourceType::RAWFILE)) {
        auto fileName = info.params[0];
        result = themeConstants->GetRawfile(fileName);
    } else if (info.type == static_cast<int>(ResourceType::FLOAT)) {
        result = DimensionToString(themeConstants->GetDimension(info.resId));
    } else {
        auto originStr = themeConstants->GetString(info.resId);
        ReplaceHolder(originStr, info.params, 0);
        result = originStr;
    }
    return true;
}

std::string ErrorToMessage(int32_t code)
{
    auto iter = ERROR_CODE_TO_MSG.find(code);
    return (iter != ERROR_CODE_TO_MSG.end()) ? iter->second : "";
}

} // namespace OHOS::Ace::Napi
