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

void ReplaceHolder(std::string& originStr, std::vector<std::string>& params, int32_t containCount)
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

size_t GetParamLen(napi_value param)
{
    auto nativeValue = reinterpret_cast<NativeValue*>(param);
    auto resultValue = nativeValue->ToString();
    auto nativeString = reinterpret_cast<NativeString*>(resultValue->GetInterface(NativeString::INTERFACE_ID));
    size_t len = nativeString->GetLength();
    return len;
}

bool GetNapiString(napi_env env, napi_value value, std::string& retStr, napi_valuetype& valueType)
{
    size_t ret = 0;
    napi_typeof(env, value, &valueType);
    if (valueType == napi_string) {
        size_t valueLen = GetParamLen(value) + 1;
        std::unique_ptr<char[]> buffer = std::make_unique<char[]>(valueLen);
        napi_get_value_string_utf8(env, value, buffer.get(), valueLen, &ret);
        retStr = buffer.get();
        return true;
    }
    if (valueType == napi_object) {
        int32_t id = 0;
        int32_t type = 0;
        std::vector<std::string> params;
        if (ParseResourceParam(env, value, id, type, params)) {
            ParseString(id, type, params, retStr);
            return true;
        }
    }
    return false;
}

RefPtr<ThemeConstants> GetThemeConstants()
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
    return themeManager->GetThemeConstants();
}

bool ParseResourceParam(napi_env env, napi_value value, int32_t& id, int32_t& type, std::vector<std::string>& params)
{
    napi_value idNApi = nullptr;
    napi_value typeNApi = nullptr;
    napi_value paramsNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, value, "id", &idNApi);
        napi_get_named_property(env, value, "type", &typeNApi);
        napi_get_named_property(env, value, "params", &paramsNApi);
    } else {
        return false;
    }

    napi_typeof(env, idNApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, idNApi, &id);
    }

    napi_typeof(env, typeNApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, typeNApi, &type);
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
            size_t strLen = GetParamLen(indexValue) + 1;
            std::unique_ptr<char[]> indexStr = std::make_unique<char[]>(strLen);
            napi_get_value_string_utf8(env, indexValue, indexStr.get(), strLen, &ret);
            params.emplace_back(indexStr.get());
        } else if (valueType == napi_number) {
            int32_t num;
            napi_get_value_int32(env, indexValue, &num);
            params.emplace_back(std::to_string(num));
        }
    }
    return true;
}

bool ParseString(int32_t resId, int32_t type, std::vector<std::string>& params, std::string& result)
{
    auto themeConstants = GetThemeConstants();
    if (!themeConstants) {
        LOGE("themeConstants is nullptr");
        return false;
    }

    if (type == static_cast<int>(ResourceType::PLURAL)) {
        auto count = StringUtils::StringToDouble(params[0]);
        auto pluralResults = themeConstants->GetStringArray(resId);
        auto pluralChoice = Localization::GetInstance()->PluralRulesFormat(count);
        auto iter = std::find(pluralResults.begin(), pluralResults.end(), pluralChoice);
        std::string originStr;
        if (iter != pluralResults.end() && ++iter != pluralResults.end()) {
            originStr = *iter;
        }
        ReplaceHolder(originStr, params, 1);
        result = originStr;
    } else if (type == static_cast<int>(ResourceType::RAWFILE)) {
        auto fileName = params[0];
        result = themeConstants->GetRawfile(fileName);
    } if (type == static_cast<int>(ResourceType::FLOAT)) {
        result = std::to_string(themeConstants->GetDouble(resId));
    } else {
        auto originStr = themeConstants->GetString(resId);
        ReplaceHolder(originStr, params, 0);
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
