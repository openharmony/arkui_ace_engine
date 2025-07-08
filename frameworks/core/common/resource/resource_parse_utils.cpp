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

#include "core/common/resource/resource_parse_utils.h"

#include <regex>
#include <cstdint>

#include "base/utils/utf_helper.h"
#include "core/common/card_scope.h"
#include "core/common/container.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif
#include "core/common/color_inverter.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr int32_t UNKNOWN_INSTANCE_ID = -1;
constexpr int32_t UNKNOWN_RESOURCE_ID = -1;
constexpr int32_t UNKNOWN_RESOURCE_TYPE = -1;
const std::regex FLOAT_PATTERN(R"(-?(0|[1-9]\d*)(\.\d+))", std::regex::icase);
bool ResourceParseUtils::isReloading_ = false;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

RefPtr<ThemeConstants> ResourceParseUtils::GetThemeConstants(const RefPtr<ResourceObject>& resObj)
{
    std::string bundleName;
    std::string moduleName;
    if (resObj) {
        bundleName = resObj->GetBundleName();
        moduleName = resObj->GetModuleName();
    }

#if !defined(ACE_UNITTEST)
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
#endif

#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (Container::CurrentId() >= MIN_PLUGIN_SUBCONTAINER_ID) {
        auto pluginContainer = PluginManager::GetInstance().GetPluginSubContainer(Container::CurrentId());
        if (!pluginContainer) {
            return nullptr;
        }
        auto pluginPipelineContext = pluginContainer->GetPipelineContext();
        if (!pluginPipelineContext) {
            return nullptr;
        }
        auto pluginThemeManager = pluginPipelineContext->GetThemeManager();
        if (!pluginThemeManager) {
            return nullptr;
        }
        return pluginThemeManager->GetThemeConstants(bundleName, moduleName);
    }
#endif
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetThemeConstants(bundleName, moduleName);
}

RefPtr<ResourceWrapper> CreateResourceWrapper()
{
    RefPtr<ResourceObject> resObj;
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter(Container::CurrentIdSafely());
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = ResourceParseUtils::GetThemeConstants(resObj);
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

RefPtr<ResourceWrapper> GetOrCreateResourceWrapper(const RefPtr<ResourceObject>& resObj)
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resObj);
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = ResourceParseUtils::GetThemeConstants(resObj);
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

RefPtr<ResourceObject> CompleteResourceObject(const std::unique_ptr<JsonValue>& json)
{
    auto id = json->GetValue("id")->GetInt();
    auto type = json->GetValue("type")->GetInt();
    auto params = json->GetValue("params");

    std::string bundleName;
    std::string moduleName;
    auto bundle = json->GetValue("bundleName");
    auto module = json->GetValue("moduleName");
    if (bundle->IsString() && module->IsString()) {
        bundleName = bundle->ToString();
        moduleName = module->ToString();
    }

    if (!params->IsArray()) {
        return nullptr;
    }

    std::vector<ResourceObjectParams> resObjParamsList;
    auto size = params->GetArraySize();
    for (int32_t i = 0; i < size; i++) {
        auto item = params->GetArrayItem(i);
        ResourceObjectParams resObjParams { .value = item->ToString().c_str() };
        if (item->IsString()) {
            resObjParams.type = ResourceObjectParamType::STRING;
        } else if (item->IsNumber()) {
            if (std::regex_match(item->ToString(), FLOAT_PATTERN)) {
                resObjParams.type = ResourceObjectParamType::FLOAT;
            } else {
                resObjParams.type = ResourceObjectParamType::INT;
            }
        }
        resObjParamsList.push_back(resObjParams);
    }
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(
        id, type, resObjParamsList, bundleName, moduleName, Container::CurrentIdSafely());
    return resourceObject;
}

std::string GetReplaceContentStr(int pos, const std::string& type,
    const std::vector<ResourceObjectParams> params, int32_t containCount)
{
    auto index = pos + containCount;
    if (index < 0 || (index >= static_cast<int32_t>(params.size()))) {
        return std::string();
    }

    auto item = params[index].value;
    auto itemType = params[index].type;
    auto entityReson = JsonUtil::ParseJsonString(item.value());
    if (type == "d") {
        if (itemType == ResourceObjectParamType::INT ||
            itemType == ResourceObjectParamType::FLOAT) {
            return item.value();
        } else if (itemType == ResourceObjectParamType::NONE) {
            auto resObj = CompleteResourceObject(entityReson);
            int32_t result = 0;
            ResourceParseUtils::ParseResInteger(resObj, result);
            return std::to_string(result);
        }
    } else if (type == "s") {
        if (itemType == ResourceObjectParamType::STRING) {
            return item.value();
        } else if (itemType == ResourceObjectParamType::NONE) {
            auto resObj = CompleteResourceObject(entityReson);
            std::string result;
            ResourceParseUtils::ParseResString(resObj, result);
            return result;
        }
    } else if (type == "f") {
        if (itemType == ResourceObjectParamType::INT ||
            itemType == ResourceObjectParamType::FLOAT) {
            return item.value();
        } else if (itemType == ResourceObjectParamType::NONE) {
            auto resObj = CompleteResourceObject(entityReson);
            double result = 0.0;
            ResourceParseUtils::ParseResDouble(resObj, result);
            return std::to_string(result);
        }
    }
    return std::string();
}

void ReplaceHolder(std::string& originStr, const std::vector<ResourceObjectParams> params, int32_t containCount)
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
    const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
    while (std::regex_search(start, end, matches, RESOURCE_APP_STRING_PLACEHOLDER)) {
        std::string pos = matches[2];
        std::string type = matches[4];
        if (firstMatch) {
            firstMatch = false;
            shortHolderType = pos.length() == 0;
        } else {
            if (shortHolderType ^ (pos.length() == 0)) {
                return;
            }
        }

        std::string replaceContentStr;
        if (shortHolderType) {
            replaceContentStr = GetReplaceContentStr(searchTime, type, params, containCount);
        } else {
            replaceContentStr = GetReplaceContentStr(StringUtils::StringToInt(pos) - 1, type, params, containCount);
        }

        originStr.replace(matches[0].first - originStr.begin(), matches[0].length(), replaceContentStr);
        start = originStr.begin() + matches.prefix().length() + replaceContentStr.length();
        end = originStr.end();
        searchTime++;
    }
}

bool ResourceParseUtils::ParseResInteger(const RefPtr<ResourceObject>& resObj, uint32_t& result)
{
    return ParseResInteger<uint32_t>(resObj, result);
}

bool ResourceParseUtils::ParseResInteger(const RefPtr<ResourceObject>& resObj, int32_t& result)
{
    return ParseResInteger<int32_t>(resObj, result);
}

bool ResourceParseUtils::ParseResIntegerArray(const RefPtr<ResourceObject>& resObj, std::vector<uint32_t>& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resType = resObj->GetType();
    if (resType == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }

    auto resourceWrapper = GetOrCreateResourceWrapper(resObj);
    if (!resourceWrapper) {
        return false;
    }

    auto resId = resObj->GetId();
    if (resId == -1) {
        auto params = resObj->GetParams();
        if (params.empty()) {
            return false;
        }
        if (resType == static_cast<int32_t>(ResourceType::INTARRAY)) {
            result = resourceWrapper->GetIntArrayByName(params[0].value.value());
            return true;
        }
        return false;
    }
    if (resType == static_cast<int32_t>(ResourceType::INTARRAY)) {
        result = resourceWrapper->GetIntArray(resId);
        return true;
    }
    return false;
}

bool ResourceParseUtils::ParseResStrArray(const RefPtr<ResourceObject>& resObj, std::vector<std::string>& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resType = resObj->GetType();
    if (resType == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }

    auto resourceWrapper = GetOrCreateResourceWrapper(resObj);
    if (!resourceWrapper) {
        return false;
    }

    auto resId = resObj->GetId();
    if (resId == -1) {
        auto params = resObj->GetParams();
        if (params.empty()) {
            return false;
        }
        if (resType == static_cast<int32_t>(ResourceType::STRARRAY)) {
            result = resourceWrapper->GetStringArrayByName(params[0].value.value());
            return true;
        }
        return false;
    }
    if (resType == static_cast<int32_t>(ResourceType::STRARRAY)) {
        result = resourceWrapper->GetStringArray(resId);
        return true;
    }
    return false;
}

bool ResourceParseUtils::ParseResFontFamilies(const RefPtr<ResourceObject>& resObj, std::vector<std::string>& result)
{
    CHECK_NULL_RETURN(resObj, false);
    result.clear();
    auto resourceWrapper = GetOrCreateResourceWrapper(resObj);
    if (!resourceWrapper) {
        return false;
    }

    auto resId = resObj->GetId();
    if (resId == -1) {
        auto params = resObj->GetParams();
        if (params.empty()) {
            return false;
        }
        result.emplace_back(resourceWrapper->GetStringByName(params[0].value.value()));
        return true;
    }
    result.emplace_back(resourceWrapper->GetString(resId));
    return true;
}

void ResourceParseUtils::InvertColorWithResource(const RefPtr<ResourceObject>& resObj, Color& result,
    const ColorMode& colorMode)
{
    if (!isReloading_ || (resObj->GetColorMode() == ColorMode::COLOR_MODE_UNDEFINED)) {
        return;
    }
    if ((colorMode == ColorMode::DARK) && !resObj->HasDarkResource()) {
        result = ColorInverter::Invert(result, resObj->GetInstanceId(), resObj->GetNodeTag());
    }
    resObj->SetColorMode(colorMode);
}

bool ResourceParseUtils::ParseResColorWithName(const RefPtr<ResourceObject>& resObj, Color& result,
    RefPtr<ResourceWrapper>& resourceWrapper, const ColorMode& colorMode)
{
    auto params = resObj->GetParams();
    if (params.empty()) {
        return false;
    }
    result = resourceWrapper->GetColorByName(params[0].value.value());
    InvertColorWithResource(resObj, result, colorMode);
    return true;
}

bool ResourceParseUtils::ParseResColor(const RefPtr<ResourceObject>& resObj, Color& result)
{
    CHECK_NULL_RETURN(resObj, false);

    auto colorMode = Container::CurrentColorMode();
    if (!resObj->IsResource()) {
        if (resObj->GetColorMode() == ColorMode::COLOR_MODE_UNDEFINED) {
            return false;
        }
        if (isReloading_ && (colorMode == ColorMode::DARK)) {
            result = ColorInverter::Invert(resObj->GetColor(), resObj->GetInstanceId(), resObj->GetNodeTag());
        } else {
            result = resObj->GetColor();
        }
        resObj->SetColorMode(colorMode);
        return true;
    }

    if (resObj->GetInstanceId() == UNKNOWN_INSTANCE_ID) {
        resObj->SetInstanceId(Container::CurrentIdSafely());
    }
    auto resourceWrapper = GetOrCreateResourceWrapper(resObj);
    CHECK_NULL_RETURN(resourceWrapper, false);
    auto resId = resObj->GetId();
    if (resId == -1) {
        return ParseResColorWithName(resObj, result, resourceWrapper, colorMode);
    }

    auto type = resObj->GetType();
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId);
        bool state = Color::ParseColorString(value, result);
        InvertColorWithResource(resObj, result, colorMode);
        return state;
    }
    if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = resourceWrapper->GetInt(resId);
        result = Color(ColorAlphaAdapt(value));
        InvertColorWithResource(resObj, result, colorMode);
        return true;
    }
    if (type == static_cast<int32_t>(ResourceType::COLOR)) {
        result = resourceWrapper->GetColor(resId);
        result.SetResourceId(resId);
        InvertColorWithResource(resObj, result, colorMode);
        return true;
    }
    return false;
}

bool ResourceParseUtils::ParseResString(const RefPtr<ResourceObject>& resObj, std::u16string& result)
{
    CHECK_NULL_RETURN(resObj, false);
    std::string u8Result;
    bool ret = ParseResString(resObj, u8Result);
    if (ret) {
        result = UtfUtils::Str8DebugToStr16(u8Result);
        return true;
    }
    return false;
}

bool ResourceParseUtils::ParseResStringObj(const std::vector<ResourceObjectParams>& params,
    RefPtr<ResourceWrapper>& resourceWrapper, std::string& result, int32_t type)
{
    if (params.empty()) {
        return false;
    }
    auto param = params[0];
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetStringByName(param.value.value());
        ReplaceHolder(originStr, params, 1);
        result = originStr;
    } else if (type == static_cast<int32_t>(ResourceType::PLURAL)) {
        auto countJsVal = params[1];
        int count = 0;
        if (!IsNumberType(static_cast<int32_t>(countJsVal.type))) {
            return false;
        }
        count = StringUtils::StringToInt(countJsVal.value.value());
        auto pluralStr = resourceWrapper->GetPluralStringByName(param.value.value(), count);
        ReplaceHolder(pluralStr, params, 2); // params[2] applys pluralStr.
        result = pluralStr;
    } else {
        return false;
    }
    return true;
}

bool ResourceParseUtils::ParseResString(const RefPtr<ResourceObject>& resObj, std::string& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto type = resObj->GetType();
    if (type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto params = resObj->GetParams();
    auto resourceWrapper = GetOrCreateResourceWrapper(resObj);
    if (!resourceWrapper) {
        return false;
    }
    auto resIdNum = resObj->GetId();
    if (resIdNum == -1) {
        return ResourceParseUtils::ParseResStringObj(params, resourceWrapper, result, type);
    }
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetString(resIdNum);
        ReplaceHolder(originStr, params, 0);
        result = originStr;
    } else if (type == static_cast<int32_t>(ResourceType::PLURAL)) {
        if (params.empty()) {
            return false;
        }
        auto countJsVal = params[0];
        int count = 0;
        if (!IsNumberType(static_cast<int32_t>(countJsVal.type))) {
            return false;
        }
        count = StringUtils::StringToInt(countJsVal.value.value());
        auto pluralStr = resourceWrapper->GetPluralString(resIdNum, count);
        ReplaceHolder(pluralStr, params, 1);
        result = pluralStr;
    } else if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = std::to_string(resourceWrapper->GetDouble(resIdNum));
    } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = std::to_string(resourceWrapper->GetInt(resIdNum));
    } else {
        return false;
    }
    return true;
}

bool ResourceParseUtils::ParseResMedia(const RefPtr<ResourceObject>& resObj, std::string& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto type = resObj->GetType();
    auto resIdNum = resObj->GetId();
    if (type != UNKNOWN_RESOURCE_TYPE) {
        auto resourceWrapper = GetOrCreateResourceWrapper(resObj);
        if (!resourceWrapper) {
            return false;
        }
        if (type == static_cast<int32_t>(ResourceType::RAWFILE)) {
            auto params = resObj->GetParams();
            if (!params.size()) {
                return false;
            }
            auto fileName = params[0];
            if (fileName.type != ResourceObjectParamType::STRING) {
                return false;
            }
            result = resourceWrapper->GetRawfile(fileName.value.value());
            return true;
        }
        if (resIdNum == -1) {
            auto params = resObj->GetParams();
            if (!params.size()) {
                return false;
            }
            if (type == static_cast<int32_t>(ResourceType::MEDIA)) {
                result = resourceWrapper->GetMediaPathByName(params[0].value.value());
                return true;
            }
            if (type == static_cast<int32_t>(ResourceType::STRING)) {
                result = resourceWrapper->GetStringByName(params[0].value.value());
                return true;
            }
            return false;
        } else if (type == static_cast<int32_t>(ResourceType::MEDIA)) {
            result = resourceWrapper->GetMediaPath(resIdNum);
            return true;
        } else if (type == static_cast<int32_t>(ResourceType::STRING)) {
            result = resourceWrapper->GetString(resIdNum);
            return true;
        }
    }
    return false;
}

bool ResourceParseUtils::ParseResBool(const RefPtr<ResourceObject>& resObj, bool& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto type = resObj->GetType();
    if (type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }

    auto resourceWrapper = GetOrCreateResourceWrapper(resObj);
    if (!resourceWrapper) {
        return false;
    }
    auto resIdNum = resObj->GetId();
    if (resIdNum == -1) {
        auto params = resObj->GetParams();
        if (!params.size()) {
            return false;
        }
        if (type == static_cast<int32_t>(ResourceType::BOOLEAN)) {
            result = resourceWrapper->GetBooleanByName(params[0].value.value());
            return true;
        }
        return false;
    }
    if (type == static_cast<int32_t>(ResourceType::BOOLEAN)) {
        result = resourceWrapper->GetBoolean(resIdNum);
        return true;
    }
    return false;
}

bool ResourceParseUtils::ParseResourceToDouble(const RefPtr<ResourceObject>& resObj, double& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resourceWrapper = GetOrCreateResourceWrapper(resObj);
    if (!resourceWrapper) {
        return false;
    }
    auto resIdNum = resObj->GetId();
    auto type = resObj->GetType();
    auto params = resObj->GetParams();
    if (resIdNum == -1) {
        if (params.empty()) {
            return false;
        }
        auto param = params[0];
        if (type == static_cast<int32_t>(ResourceType::STRING)) {
            auto numberStr = resourceWrapper->GetStringByName(param.value.value());
            return StringUtils::StringToDouble(numberStr, result);
        } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
            result = resourceWrapper->GetIntByName(param.value.value());
            return true;
        } else if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
            result = resourceWrapper->GetDoubleByName(param.value.value());
            return true;
        }
        return false;
    }
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto numberStr = resourceWrapper->GetString(resIdNum);
        return StringUtils::StringToDouble(numberStr, result);
    } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = resourceWrapper->GetInt(resIdNum);
        return true;
    } else if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDouble(resIdNum);
        return true;
    }
    return false;
}

bool ResourceParseUtils::ParseResDouble(const RefPtr<ResourceObject>& resObj, double& result)
{
    return ParseResourceToDouble(resObj, result);
}

bool ResourceParseUtils::ParseResDimensionFpNG(const RefPtr<ResourceObject>& resObj, CalcDimension& result,
    bool isSupportPercent)
{
    return ParseResDimensionNG(resObj, result, DimensionUnit::FP, isSupportPercent);
}

bool ResourceParseUtils::ParseResDimensionVpNG(const RefPtr<ResourceObject>& resObj, CalcDimension& result,
    bool isSupportPercent)
{
    return ParseResDimensionNG(resObj, result, DimensionUnit::VP, isSupportPercent);
}

bool ResourceParseUtils::ParseResDimensionNG(
    const RefPtr<ResourceObject>& resObj, CalcDimension& result, DimensionUnit defaultUnit, bool isSupportPercent)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resourceWrapper = GetOrCreateResourceWrapper(resObj);
    if (!resourceWrapper) {
        return false;
    }
    auto resIdNum = resObj->GetId();
    auto type = resObj->GetType();
    auto params = resObj->GetParams();
    if (resIdNum == -1) {
        if (params.empty()) {
            return false;
        }
        auto param = params[0];
        if (type == static_cast<int32_t>(ResourceType::STRING)) {
            auto value = resourceWrapper->GetStringByName(param.value.value());
            return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
        } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceWrapper->GetIntByName(param.value.value()));
            StringUtils::StringToDimensionWithUnitNG(value, result, defaultUnit);
            return true;
        }
        result = resourceWrapper->GetDimensionByName(param.value.value());
        return true;
    }
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resIdNum);
        return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
    } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resIdNum));
        StringUtils::StringToDimensionWithUnitNG(value, result, defaultUnit);
        return true;
    } else if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(resIdNum);
        return true;
    }
    return false;
}

bool ResourceParseUtils::ParseResDimensionVp(const RefPtr<ResourceObject>& resObj, CalcDimension& result)
{
    // 'vp' -> the value varies with pixel density of device.
    return ParseResDimension(resObj, result, DimensionUnit::VP);
}

bool ResourceParseUtils::ParseResDimensionFp(const RefPtr<ResourceObject>& resObj, CalcDimension& result)
{
    // the 'fp' unit is used for text scenes.
    return ParseResDimension(resObj, result, DimensionUnit::FP);
}

bool ResourceParseUtils::ParseResDimensionPx(const RefPtr<ResourceObject>& resObj, CalcDimension& result)
{
    return ParseResDimension(resObj, result, DimensionUnit::PX);
}

bool ResourceParseUtils::ParseResDimension(
    const RefPtr<ResourceObject>& resObj, CalcDimension& result, DimensionUnit defaultUnit)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resourceWrapper = GetOrCreateResourceWrapper(resObj);
    if (!resourceWrapper) {
        return false;
    }
    auto resIdNum = resObj->GetId();
    auto type = resObj->GetType();
    if (type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto params = resObj->GetParams();
    if (resIdNum == -1) {
        if (params.empty()) {
            return false;
        }
        auto param = params[0];
        if (type == static_cast<int32_t>(ResourceType::STRING)) {
            auto value = resourceWrapper->GetStringByName(param.value.value());
            result = StringUtils::StringToCalcDimension(value, false, defaultUnit);
            return true;
        } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceWrapper->GetIntByName(param.value.value()));
            result = StringUtils::StringToDimensionWithUnit(value, defaultUnit);
            return true;
        }
        result = resourceWrapper->GetDimensionByName(param.value.value());
        return true;
    }
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resIdNum);
        result = StringUtils::StringToCalcDimension(value, false, defaultUnit);
        return true;
    } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resIdNum));
        result = StringUtils::StringToDimensionWithUnit(value, defaultUnit);
        return true;
    }
    result = resourceWrapper->GetDimension(resIdNum);
    return true;
}

bool ResourceParseUtils::ParseResResource(const RefPtr<ResourceObject>& resObj, CalcDimension& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resIdNum = resObj->GetId();
    auto type = resObj->GetType();
    if (type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    resIdNum = resIdNum == UNKNOWN_RESOURCE_ID ? 0 : resIdNum;

    auto resourceWrapper = CreateResourceWrapper();
    CHECK_NULL_RETURN(resourceWrapper, false);
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resIdNum);
        return StringUtils::StringToCalcDimensionNG(value, result, false);
    }
    if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resIdNum));
        StringUtils::StringToDimensionWithUnitNG(value, result);
        return true;
    }

    if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(resIdNum);
        return true;
    }
    return false;
}

template<class T>
bool ResourceParseUtils::ConvertFromResObjNG(const RefPtr<ResourceObject>& resObj, T& result)
{
    CHECK_NULL_RETURN(resObj, false);
    if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
        double value;
        if (ParseResDouble(resObj, value)) {
            result = static_cast<T>(value);
            return true;
        }
        result = 0;
    } else if constexpr (std::is_same_v<T, Dimension>) {
        CalcDimension calc;
        bool ret = ParseResDimensionVpNG(resObj, calc);
        result = calc;
        return ret;
    } else if constexpr (std::is_same_v<T, CalcDimension>) {
        return ParseResDimensionVpNG(resObj, result);
    } else if constexpr (std::is_same_v<T, Color>) {
        return ParseResColor(resObj, result);
    }
    return false;
}

template<class T>
bool ResourceParseUtils::ConvertFromResObj(const RefPtr<ResourceObject>& resObj, T& result)
{
    CHECK_NULL_RETURN(resObj, false);
    if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
        double value;
        if (ParseResDouble(resObj, value)) {
            result = static_cast<T>(value);
            return true;
        }
        result = 0;
    } else if constexpr (std::is_same_v<T, Dimension>) {
        CalcDimension calc;
        bool ret = ParseResDimensionVp(resObj, calc);
        result = calc;
        return ret;
    } else if constexpr (std::is_same_v<T, CalcDimension>) {
        return ParseResDimensionVp(resObj, result);
    } else if constexpr (std::is_same_v<T, Color>) {
        return ParseResColor(resObj, result);
    }
    return false;
}

template bool ResourceParseUtils::ConvertFromResObjNG<Dimension>(
    const RefPtr<ResourceObject>& resObj, Dimension& result);
}
