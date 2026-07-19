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
#include "core/common/container.h"
#include "core/common/color_inverter.h"
#include "core/common/resource/resource_manager.h"
#include "core/components/theme/resource_adapter.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr int32_t UNKNOWN_INSTANCE_ID = -1;
constexpr int32_t UNKNOWN_RESOURCE_ID = -1;
constexpr int32_t UNKNOWN_RESOURCE_TYPE = -1;
const std::regex FLOAT_PATTERN(R"(-?(0|[1-9]\d*)(\.\d+))", std::regex::icase);
bool ResourceParseUtilsBase::needReload_ = false;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

RefPtr<ResourceAdapter> CreateResourceAdapter()
{
    return ResourceManager::GetInstance().GetResourceAdapter(Container::CurrentIdSafely());
}

RefPtr<ResourceAdapter> GetOrCreateResourceAdapter(const RefPtr<ResourceObject>& resObj)
{
    return ResourceManager::GetInstance().GetOrCreateResourceAdapter(resObj);
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

void ResourceParseUtilsBase::CompleteResourceObjectFromColor(
    RefPtr<ResourceObject>& resObj, Color& color, const NG::NodeInfo& nodeInfo)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto instanceId = Container::CurrentIdSafely();
    auto invertFunc = ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeInfo.nodeTag);
    CHECK_NULL_VOID(invertFunc);

    auto colorMode = Container::CurrentColorMode();
    Color curColor = color;
    if (colorMode == ColorMode::DARK && nodeInfo.allowForceDark) {
        color = Color(invertFunc(color.GetValue()));
    }
    resObj = AceType::MakeRefPtr<ResourceObject>();
    resObj->SetIsResource(false);
    resObj->SetInstanceId(instanceId);
    resObj->SetNodeTag(nodeInfo.nodeTag);
    resObj->SetColorMode(colorMode);
    resObj->SetHasDarkRes(false);
    resObj->SetColor(((colorMode == ColorMode::DARK) ? curColor : color));
}

NG::NodeInfo ResourceParseUtils::MakeNativeNodeInfo(NG::UINode* uiNode)
{
    if (!uiNode) {
        return { "", ColorMode::COLOR_MODE_UNDEFINED, true };
    }
    return { uiNode->GetTag(), uiNode->GetLocalColorMode(), uiNode->GetForceDarkAllowed() };
}

bool ResourceParseUtilsBase::ParseResInteger(const RefPtr<ResourceObject>& resObj, uint32_t& result)
{
    return ResourceParseUtils::ParseResInteger<uint32_t>(resObj, result);
}

bool ResourceParseUtilsBase::ParseResInteger(const RefPtr<ResourceObject>& resObj, int32_t& result)
{
    return ResourceParseUtils::ParseResInteger<int32_t>(resObj, result);
}

bool ResourceParseUtilsBase::ParseResIntegerArray(const RefPtr<ResourceObject>& resObj, std::vector<uint32_t>& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resType = resObj->GetType();
    if (resType == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }

    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    if (!resourceAdapter) {
        return false;
    }

    auto resId = resObj->GetId();
    if (resId == -1) {
        auto params = resObj->GetParams();
        if (params.empty()) {
            return false;
        }
        if (resType == static_cast<int32_t>(ResourceType::INTARRAY)) {
            result = resourceAdapter->GetIntArrayByName(params[0].value.value());
            return true;
        }
        return false;
    }
    if (resType == static_cast<int32_t>(ResourceType::INTARRAY)) {
        result = resourceAdapter->GetIntArray(resId);
        return true;
    }
    return false;
}

bool ResourceParseUtilsBase::ParseResStrArray(const RefPtr<ResourceObject>& resObj, std::vector<std::string>& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resType = resObj->GetType();
    if (resType == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }

    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    if (!resourceAdapter) {
        return false;
    }

    auto resId = resObj->GetId();
    if (resId == -1) {
        auto params = resObj->GetParams();
        if (params.empty()) {
            return false;
        }
        if (resType == static_cast<int32_t>(ResourceType::STRARRAY)) {
            result = resourceAdapter->GetStringArrayByName(params[0].value.value());
            return true;
        }
        return false;
    }
    if (resType == static_cast<int32_t>(ResourceType::STRARRAY)) {
        result = resourceAdapter->GetStringArray(resId);
        return true;
    }
    return false;
}

bool ResourceParseUtilsBase::ParseResFontFamilies(
    const RefPtr<ResourceObject>& resObj, std::vector<std::string>& result)
{
    CHECK_NULL_RETURN(resObj, false);
    result.clear();
    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    if (!resourceAdapter) {
        return false;
    }

    auto resId = resObj->GetId();
    if (resId == -1) {
        auto params = resObj->GetParams();
        if (params.empty()) {
            return false;
        }
        result.emplace_back(resourceAdapter->GetStringByName(params[0].value.value()));
        return true;
    }
    result.emplace_back(resourceAdapter->GetString(resId));
    return true;
}

void ResourceParseUtilsBase::InvertColorWithResource(const RefPtr<ResourceObject>& resObj, Color& result,
    const ColorMode& colorMode)
{
    if (!needReload_ || (resObj->GetColorMode() == ColorMode::COLOR_MODE_UNDEFINED)) {
        return;
    }
    if ((colorMode == ColorMode::DARK) && !resObj->HasDarkResource()) {
        result = ColorInverter::Invert(result, resObj->GetInstanceId(), resObj->GetNodeTag());
    }
    resObj->SetColorMode(colorMode);
}

bool ResourceParseUtilsBase::ParseResColorWithName(const RefPtr<ResourceObject>& resObj, Color& result,
    RefPtr<ResourceAdapter>& resourceAdapter, const ColorMode& colorMode)
{
    CHECK_NULL_RETURN(resourceAdapter, false);
    auto params = resObj->GetParams();
    if (params.empty()) {
        return false;
    }
    result = resourceAdapter->GetColorByName(params[0].value.value());
    InvertColorWithResource(resObj, result, colorMode);
    return true;
}

bool ResourceParseUtilsBase::ParseResColor(const RefPtr<ResourceObject>& resObj, Color& result, bool adaptMaterial)
{
    CHECK_NULL_RETURN(resObj, false);

    auto colorMode = Container::CurrentColorMode();
    if (!resObj->IsResource()) {
        if (resObj->GetColorMode() == ColorMode::COLOR_MODE_UNDEFINED) {
            return false;
        }
        if (needReload_ && (colorMode == ColorMode::DARK)) {
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
    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    CHECK_NULL_RETURN(resourceAdapter, false);
    auto resId = resObj->GetId();
    if (resId == -1) {
        return ParseResColorWithName(resObj, result, resourceAdapter, colorMode);
    }

    auto type = resObj->GetType();
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceAdapter->GetString(resId);
        bool state = Color::ParseColorString(value, result);
        InvertColorWithResource(resObj, result, colorMode);
        return state;
    }
    if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = resourceAdapter->GetInt(resId);
        result = Color(ColorAlphaAdapt(value));
        InvertColorWithResource(resObj, result, colorMode);
        return true;
    }
    if (type == static_cast<int32_t>(ResourceType::COLOR)) {
        result = resourceAdapter->GetColor(resId);
        result.SetResourceId(resId);
        if (adaptMaterial) {
            result.FillColorPlaceholderIfNeed(resId);
        }
        InvertColorWithResource(resObj, result, colorMode);
        return true;
    }
    return false;
}

bool ResourceParseUtilsBase::ParseResColorWithColorMode(const RefPtr<ResourceObject>& resObj, Color& result,
    const ColorMode& colorMode)
{
    CHECK_NULL_RETURN(resObj, false);
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, false);
    if (resObj->GetInstanceId() == UNKNOWN_INSTANCE_ID) {
        resObj->SetInstanceId(container->GetInstanceId());
    }
    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    auto colorModeValue = resourceAdapter ? resourceAdapter->GetResourceColorMode() : container->GetColorMode();
    ResourceManager::GetInstance().UpdateColorMode(
        container->GetBundleName(), container->GetModuleName(), container->GetInstanceId(), colorMode);
    bool state = ParseResColor(resObj, result);
    ResourceManager::GetInstance().UpdateColorMode(
        container->GetBundleName(), container->GetModuleName(), container->GetInstanceId(), colorModeValue);
    return state;
}

bool ResourceParseUtilsBase::ParseResString(const RefPtr<ResourceObject>& resObj, std::u16string& result)
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

bool ResourceParseUtilsBase::ParseResStringObj(const std::vector<ResourceObjectParams>& params,
    RefPtr<ResourceAdapter>& resourceAdapter, std::string& result, int32_t type)
{
    if (params.empty()) {
        return false;
    }
    CHECK_NULL_RETURN(resourceAdapter, false);
    auto param = params[0];
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto originStr = resourceAdapter->GetStringByName(param.value.value());
        ReplaceHolder(originStr, params, 1);
        result = originStr;
    } else if (type == static_cast<int32_t>(ResourceType::PLURAL)) {
        auto countJsVal = params[1];
        int count = 0;
        if (!IsNumberType(static_cast<int32_t>(countJsVal.type))) {
            return false;
        }
        count = StringUtils::StringToInt(countJsVal.value.value());
        auto pluralStr = resourceAdapter->GetPluralStringByName(param.value.value(), count);
        ReplaceHolder(pluralStr, params, 2); // params[2] applys pluralStr.
        result = pluralStr;
    } else if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = std::to_string(resourceAdapter->GetDoubleByName(param.value.value()));
    } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = std::to_string(resourceAdapter->GetIntByName(param.value.value()));
    } else {
        return false;
    }
    return true;
}

bool ResourceParseUtilsBase::ParseResString(const RefPtr<ResourceObject>& resObj, std::string& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto type = resObj->GetType();
    if (type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto params = resObj->GetParams();
    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    if (!resourceAdapter) {
        return false;
    }
    auto resIdNum = resObj->GetId();
    if (resIdNum == -1) {
        return ResourceParseUtilsBase::ParseResStringObj(params, resourceAdapter, result, type);
    }
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto originStr = resourceAdapter->GetString(resIdNum);
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
        auto pluralStr = resourceAdapter->GetPluralString(resIdNum, count);
        ReplaceHolder(pluralStr, params, 1);
        result = pluralStr;
    } else if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = std::to_string(resourceAdapter->GetDouble(resIdNum));
    } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = std::to_string(resourceAdapter->GetInt(resIdNum));
    } else {
        return false;
    }
    return true;
}

bool ResourceParseUtilsBase::ParseResMedia(const RefPtr<ResourceObject>& resObj, std::string& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto type = resObj->GetType();
    auto resIdNum = resObj->GetId();
    if (type != UNKNOWN_RESOURCE_TYPE) {
        auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
        if (!resourceAdapter) {
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
            result = resourceAdapter->GetRawfile(fileName.value.value());
            return true;
        }
        if (resIdNum == -1) {
            auto params = resObj->GetParams();
            if (!params.size()) {
                return false;
            }
            if (type == static_cast<int32_t>(ResourceType::MEDIA)) {
                result = resourceAdapter->GetMediaPathByName(params[0].value.value());
                return true;
            }
            if (type == static_cast<int32_t>(ResourceType::STRING)) {
                result = resourceAdapter->GetStringByName(params[0].value.value());
                return true;
            }
            return false;
        } else if (type == static_cast<int32_t>(ResourceType::MEDIA)) {
            result = resourceAdapter->GetMediaPath(resIdNum);
            return true;
        } else if (type == static_cast<int32_t>(ResourceType::STRING)) {
            result = resourceAdapter->GetString(resIdNum);
            return true;
        }
    }
    return false;
}

bool ResourceParseUtilsBase::ParseResBool(const RefPtr<ResourceObject>& resObj, bool& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto type = resObj->GetType();
    if (type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }

    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    if (!resourceAdapter) {
        return false;
    }
    auto resIdNum = resObj->GetId();
    if (resIdNum == -1) {
        auto params = resObj->GetParams();
        if (!params.size()) {
            return false;
        }
        if (type == static_cast<int32_t>(ResourceType::BOOLEAN)) {
            result = resourceAdapter->GetBooleanByName(params[0].value.value());
            return true;
        }
        return false;
    }
    if (type == static_cast<int32_t>(ResourceType::BOOLEAN)) {
        result = resourceAdapter->GetBoolean(resIdNum);
        return true;
    }
    return false;
}

bool ResourceParseUtilsBase::ParseResourceToDouble(const RefPtr<ResourceObject>& resObj, double& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    if (!resourceAdapter) {
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
            auto numberStr = resourceAdapter->GetStringByName(param.value.value());
            return StringUtils::StringToDouble(numberStr, result);
        } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
            result = resourceAdapter->GetIntByName(param.value.value());
            return true;
        } else if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
            result = resourceAdapter->GetDoubleByName(param.value.value());
            return true;
        }
        return false;
    }
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto numberStr = resourceAdapter->GetString(resIdNum);
        return StringUtils::StringToDouble(numberStr, result);
    } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = resourceAdapter->GetInt(resIdNum);
        return true;
    } else if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceAdapter->GetDouble(resIdNum);
        return true;
    }
    return false;
}

bool ResourceParseUtilsBase::ParseResDouble(const RefPtr<ResourceObject>& resObj, double& result)
{
    return ParseResourceToDouble(resObj, result);
}

bool ResourceParseUtilsBase::ParseResDimensionFpNG(const RefPtr<ResourceObject>& resObj, CalcDimension& result,
    bool isSupportPercent)
{
    return ParseResDimensionNG(resObj, result, DimensionUnit::FP, isSupportPercent);
}

bool ResourceParseUtilsBase::ParseResDimensionVpNG(const RefPtr<ResourceObject>& resObj, CalcDimension& result,
    bool isSupportPercent)
{
    return ParseResDimensionNG(resObj, result, DimensionUnit::VP, isSupportPercent);
}

bool ResourceParseUtilsBase::ParseResDimensionNG(
    const RefPtr<ResourceObject>& resObj, CalcDimension& result, DimensionUnit defaultUnit, bool isSupportPercent)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    if (!resourceAdapter) {
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
            auto value = resourceAdapter->GetStringByName(param.value.value());
            return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
        } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceAdapter->GetIntByName(param.value.value()));
            StringUtils::StringToDimensionWithUnitNG(value, result, defaultUnit);
            return true;
        }
        result = resourceAdapter->GetDimensionByName(param.value.value());
        return true;
    }
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceAdapter->GetString(resIdNum);
        return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
    } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceAdapter->GetInt(resIdNum));
        StringUtils::StringToDimensionWithUnitNG(value, result, defaultUnit);
        return true;
    } else if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceAdapter->GetDimension(resIdNum);
        return true;
    }
    return false;
}

bool ResourceParseUtilsBase::ParseResDimensionVp(const RefPtr<ResourceObject>& resObj, CalcDimension& result)
{
    // 'vp' -> the value varies with pixel density of device.
    return ParseResDimension(resObj, result, DimensionUnit::VP);
}

bool ResourceParseUtilsBase::ParseResDimensionFp(const RefPtr<ResourceObject>& resObj, CalcDimension& result)
{
    // the 'fp' unit is used for text scenes.
    return ParseResDimension(resObj, result, DimensionUnit::FP);
}

bool ResourceParseUtilsBase::ParseResDimensionPx(const RefPtr<ResourceObject>& resObj, CalcDimension& result)
{
    return ParseResDimension(resObj, result, DimensionUnit::PX);
}

bool ResourceParseUtilsBase::ParseResDimension(
    const RefPtr<ResourceObject>& resObj, CalcDimension& result, DimensionUnit defaultUnit)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    if (!resourceAdapter) {
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
            auto value = resourceAdapter->GetStringByName(param.value.value());
            result = StringUtils::StringToCalcDimension(value, false, defaultUnit);
            return true;
        } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceAdapter->GetIntByName(param.value.value()));
            result = StringUtils::StringToDimensionWithUnit(value, defaultUnit);
            return true;
        }
        result = resourceAdapter->GetDimensionByName(param.value.value());
        return true;
    }
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceAdapter->GetString(resIdNum);
        result = StringUtils::StringToCalcDimension(value, false, defaultUnit);
        return true;
    } else if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceAdapter->GetInt(resIdNum));
        result = StringUtils::StringToDimensionWithUnit(value, defaultUnit);
        return true;
    }
    result = resourceAdapter->GetDimension(resIdNum);
    return true;
}

bool ResourceParseUtilsBase::ParseResResource(const RefPtr<ResourceObject>& resObj, CalcDimension& result)
{
    CHECK_NULL_RETURN(resObj, false);
    auto resIdNum = resObj->GetId();
    auto type = resObj->GetType();
    if (type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto resourceAdapter = GetOrCreateResourceAdapter(resObj);
    CHECK_NULL_RETURN(resourceAdapter, false);
    if (resIdNum == UNKNOWN_RESOURCE_ID) {
        auto params = resObj->GetParams();
        if (params.empty()) {
            return false;
        }
        auto param = params[0];
        if (type == static_cast<int32_t>(ResourceType::STRING)) {
            auto value = resourceAdapter->GetStringByName(param.value.value());
            return StringUtils::StringToCalcDimensionNG(value, result, false);
        }
        if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceAdapter->GetIntByName(param.value.value()));
            StringUtils::StringToDimensionWithUnitNG(value, result);
            return true;
        }
        if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
            result = resourceAdapter->GetDimensionByName(param.value.value());
            return true;
        }
        return false;
    }
    if (type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceAdapter->GetString(resIdNum);
        return StringUtils::StringToCalcDimensionNG(value, result, false);
    }
    if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceAdapter->GetInt(resIdNum));
        StringUtils::StringToDimensionWithUnitNG(value, result);
        return true;
    }
    if (type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceAdapter->GetDimension(resIdNum);
        return true;
    }
    return false;
}

template<class T>
bool ResourceParseUtilsBase::ConvertFromResObjNG(const RefPtr<ResourceObject>& resObj, T& result)
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
bool ResourceParseUtilsBase::ConvertFromResObj(const RefPtr<ResourceObject>& resObj, T& result)
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

template bool ACE_FORCE_EXPORT ResourceParseUtilsBase::ConvertFromResObjNG<Dimension>(
    const RefPtr<ResourceObject>& resObj, Dimension& result);
}
