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
#include "view_abstract.h"

#include <regex>

#include "cj_lambda.h"

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/extensions/events/on_area_change_extension.h"
#include "core/gestures/long_press_gesture.h"
#include "core/pipeline/base/constants.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {
namespace {
const char DEFAULT_HAR_BUNDLE_NAME[] = "__harDefaultBundleName__";
const char DEFAULT_HAR_MODULE_NAME[] = "__harDefaultModuleName__";
const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
const std::regex FLOAT_PATTERN(R"(-?(0|[1-9]\d*)(\.\d+))", std::regex::icase);
const std::string RESOURCE_TOKEN_PATTERN = "(app|sys|\\[.+?\\])\\.(\\S+?)\\.(\\S+)";
const std::string RESOURCE_NAME_PATTERN = "\\[(.+?)\\]";
constexpr int32_t UNKNOWN_RESOURCE_ID = -1;
constexpr int32_t UNKNOWN_RESOURCE_TYPE = -1;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

std::string GetBundleNameFromContainer()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, "");
    return container->GetBundleName();
}

std::string GetModuleNameFromContainer()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, "");
    return container->GetModuleName();
}

void CompleteResourceObjectFromParams(
    int32_t resId, NativeResourceObject& obj, std::string& targetModule, ResourceType& resType, std::string& resName)
{
    auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
    if (!params->IsArray()) {
        LOGE("Resource params type error.");
        return;
    }
    if (resId != UNKNOWN_RESOURCE_ID) {
        return;
    }
    auto identityValue = params->GetArrayItem(0);
    if (!identityValue->IsString()) {
        return;
    }
    auto identity = identityValue->GetString();
    if (!ViewAbstract::ParseDollarResource(
            identity, targetModule, resType, resName, obj.type == UNKNOWN_RESOURCE_TYPE)) {
        return;
    }
    std::regex resNameRegex(RESOURCE_NAME_PATTERN);
    std::smatch resNameResults;
    if (std::regex_match(targetModule, resNameResults, resNameRegex)) {
        obj.moduleName = std::string(resNameResults[1]).c_str();
    }
    if (obj.type == UNKNOWN_RESOURCE_TYPE) {
        obj.type = static_cast<int32_t>(resType);
    }
}

std::string GetReplaceContentStr(
    int pos, const std::string& type, std::unique_ptr<JsonValue>& params, int32_t containCount)
{
    auto index = pos + containCount;
    if (index < 0) {
        return std::string();
    }
    auto item = params->GetArrayItem(index);
    if (type == "d") {
        if (item->IsNumber()) {
            return std::to_string(item->GetInt());
        }
    } else if (type == "s") {
        if (item->IsString()) {
            return item->GetString();
        }
    } else if (type == "f") {
        if (item->IsNumber()) {
            return std::to_string(item->GetDouble());
        }
    }
    return std::string();
}

void ReplaceHolder(std::string& originStr, std::unique_ptr<JsonValue>& params, int32_t containCount)
{
    auto size = params->GetArraySize();
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
} // namespace

RefPtr<ResourceObject> GetResourceObject(const NativeResourceObject& obj)
{
    auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
    if (!params->IsArray()) {
        return nullptr;
    }
    std::vector<ResourceObjectParams> resObjParamsList;
    auto size = params->GetArraySize();
    for (int32_t i = 0; i < size; i++) {
        auto item = params->GetArrayItem(i);
        ResourceObjectParams resObjParams {};
        if (item->IsString()) {
            resObjParams.value = item->GetString();
            resObjParams.type = ResourceObjectParamType::STRING;
        } else if (item->IsNumber()) {
            if (std::regex_match(std::to_string(item->GetDouble()), FLOAT_PATTERN)) {
                resObjParams.value = std::to_string(item->GetDouble());
                resObjParams.type = ResourceObjectParamType::FLOAT;
            } else {
                resObjParams.value = std::to_string(item->GetInt());
                resObjParams.type = ResourceObjectParamType::INT;
            }
        }
        resObjParamsList.push_back(resObjParams);
    }
    auto resourceObject =
        AceType::MakeRefPtr<ResourceObject>(obj.id, obj.type, resObjParamsList, obj.bundleName, obj.moduleName);
    return resourceObject;
}

RefPtr<ResourceObject> GetResourceObjectByBundleAndModule(const NativeResourceObject& obj)
{
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(obj.bundleName, obj.moduleName);
    return resourceObject;
}

RefPtr<ResourceWrapper> CreateResourceWrapper(const NativeResourceObject& obj, RefPtr<ResourceObject>& resourceObject)
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = ViewAbstract::GetThemeConstants(obj.bundleName, obj.moduleName);
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

RefPtr<ResourceWrapper> CreateResourceWrapper()
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter();
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = ViewAbstract::GetThemeConstants();
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

RefPtr<ThemeConstants> ViewAbstract::GetThemeConstants(const std::string& bundleName, const std::string& moduleName)
{
    auto currentObj = Container::Current();
    if (!currentObj) {
        LOGW("container is null");
        return nullptr;
    }
    auto pipelineContext = currentObj->GetPipelineContext();
    if (!pipelineContext) {
        LOGE("pipeline context is null!");
        return nullptr;
    }
    auto themeManager = pipelineContext->GetThemeManager();
    if (!themeManager) {
        LOGE("theme manager is null!");
        return nullptr;
    }
    return themeManager->GetThemeConstants(bundleName, moduleName);
}

void ViewAbstract::CjEnabled(bool enabled)
{
    ViewAbstractModel::GetInstance()->SetEnabled(enabled);
}

void ViewAbstract::CompleteResourceObject(NativeResourceObject& obj, std::string& bundleName, std::string& moduleName)
{
    int32_t resId = UNKNOWN_RESOURCE_ID;
    CompleteResourceObjectInner(obj, bundleName, moduleName, resId);
}

void ViewAbstract::CompleteResourceObjectWithBundleName(
    NativeResourceObject& obj, std::string& bundleName, std::string& moduleName, int32_t& resId)
{
    CompleteResourceObjectInner(obj, bundleName, moduleName, resId);
}

void ViewAbstract::CompleteResourceObjectInner(
    NativeResourceObject& obj, std::string& bundleName, std::string& moduleName, int32_t& resIdValue)
{
    ResourceType resType;
    std::string targetModule;
    std::string resName;
    resIdValue = obj.id;
    if (resIdValue == UNKNOWN_RESOURCE_ID) {
        CompleteResourceObjectFromParams(resIdValue, obj, targetModule, resType, resName);
    }
    bundleName = obj.bundleName;
    moduleName = obj.moduleName;

    if ((bundleName.empty() && !moduleName.empty()) || bundleName == DEFAULT_HAR_BUNDLE_NAME) {
        bundleName = GetBundleNameFromContainer();
        obj.bundleName = bundleName.c_str();
    }
    if (moduleName == DEFAULT_HAR_MODULE_NAME) {
        moduleName = GetModuleNameFromContainer();
        obj.moduleName = moduleName.c_str();
    }
}

bool ViewAbstract::ConvertResourceType(const std::string& typeName, ResourceType& resType)
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
        { "symbol", ResourceType::SYMBOL },
    };
    auto it = resTypeMap.find(typeName);
    if (it == resTypeMap.end()) {
        return false;
    }
    resType = it->second;
    return true;
}

bool ViewAbstract::ParseDollarResource(const std::string& resPath, std::string& targetModule, ResourceType& resType,
    std::string& resName, bool isParseType)
{
    std::smatch results;
    std::regex tokenRegex(RESOURCE_TOKEN_PATTERN);
    if (!std::regex_match(resPath, results, tokenRegex)) {
        return false;
    }
    targetModule = results[1];
    std::string typeName = results[2];
    if (isParseType && !ConvertResourceType(typeName, resType)) {
        return false;
    }
    resName = resPath;
    return true;
}

bool ViewAbstract::ParseCjString(NativeResourceObject& obj, std::string& result)
{
    std::string bundleName;
    std::string moduleName;
    CompleteResourceObject(obj, bundleName, moduleName);
    if (obj.type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto resourceObject = GetResourceObjectByBundleAndModule(obj);
    auto resourceWrapper = CreateResourceWrapper(obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
    if (!params->IsArray()) {
        LOGE("Resource params type error.");
        return false;
    }
    if (obj.id == UNKNOWN_RESOURCE_ID) {
        if (!obj.paramsJsonStr) {
            return false;
        }
        auto param = params->GetArrayItem(0);
        if (obj.type == static_cast<int32_t>(ResourceType::STRING)) {
            auto originStr = resourceWrapper->GetStringByName(param->GetString());
            ReplaceHolder(originStr, params, 1);
            result = originStr;
        } else if (obj.type == static_cast<int32_t>(ResourceType::PLURAL)) {
            auto countVal = params->GetArrayItem(1);
            if (!countVal->IsNumber()) {
                return false;
            }
            int count = countVal->GetInt();
            auto pluralStr = resourceWrapper->GetPluralStringByName(param->GetString(), count);
            ReplaceHolder(pluralStr, params, 2);
            result = pluralStr;
        } else {
            return false;
        }
        return true;
    }
    if (obj.type == static_cast<int32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetString(static_cast<uint32_t>(obj.id));
        ReplaceHolder(originStr, params, 0);
        result = originStr;
    } else if (obj.type == static_cast<int32_t>(ResourceType::PLURAL)) {
        auto countVal = params->GetArrayItem(0);
        if (!countVal->IsNumber()) {
            return false;
        }
        int count = countVal->GetInt();
        auto pluralStr = resourceWrapper->GetPluralString(static_cast<uint32_t>(obj.id), count);
        ReplaceHolder(pluralStr, params, 1);
        result = pluralStr;
    } else if (obj.type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = std::to_string(resourceWrapper->GetDouble(static_cast<uint32_t>(obj.id)));
    } else if (obj.type == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = std::to_string(resourceWrapper->GetInt(static_cast<uint32_t>(obj.id)));
    } else {
        return false;
    }
    return true;
}

bool ViewAbstract::ParseCjMedia(NativeResourceObject& obj, std::string& result)
{
    std::string bundleName;
    std::string moduleName;
    CompleteResourceObject(obj, bundleName, moduleName);
    return ParseCjMediaInternal(obj, result);
}

bool ViewAbstract::ParseCjMediaInternal(NativeResourceObject& obj, std::string& result)
{
    if (obj.type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto resourceObject = GetResourceObjectByBundleAndModule(obj);
    auto resourceWrapper = CreateResourceWrapper(obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    if (obj.type == static_cast<int32_t>(ResourceType::RAWFILE)) {
        auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
        if (!params->IsArray()) {
            return false;
        }
        auto param = params->GetArrayItem(0);
        if (!param->IsString()) {
            return false;
        }
        auto fileName = param->GetString();
        result = resourceWrapper->GetRawfile(fileName);
        return true;
    }
    if (obj.id == -1) {
        if (!obj.paramsJsonStr) {
            return false;
        }
        auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
        if (!params->IsArray()) {
            return false;
        }
        auto param = params->GetArrayItem(0);
        if (obj.type == static_cast<int32_t>(ResourceType::MEDIA)) {
            result = resourceWrapper->GetMediaPathByName(param->GetString());
            return true;
        }
        if (obj.type == static_cast<int32_t>(ResourceType::STRING)) {
            result = resourceWrapper->GetStringByName(param->GetString());
            return true;
        }
        return false;
    } else if (obj.type == static_cast<int32_t>(ResourceType::MEDIA)) {
        result = resourceWrapper->GetMediaPath(static_cast<uint32_t>(obj.id));
        return true;
    } else if (obj.type == static_cast<int32_t>(ResourceType::STRING)) {
        result = resourceWrapper->GetString(static_cast<uint32_t>(obj.id));
        return true;
    }
    return false;
}

bool ViewAbstract::ParseCjSymbolId(NativeResourceObject& obj, uint32_t& result)
{
    std::string bundleName;
    std::string moduleName;
    CompleteResourceObject(obj, bundleName, moduleName);
    if (obj.type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto resourceObject = GetResourceObjectByBundleAndModule(obj);
    auto resourceWrapper = CreateResourceWrapper(obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    if (obj.type == static_cast<int32_t>(ResourceType::SYMBOL)) {
        result = resourceWrapper->GetSymbolById(static_cast<uint32_t>(obj.id));
        return true;
    }
    return false;
}

bool ViewAbstract::ParseCjColor(NativeResourceObject& obj, Color& result)
{
    std::string bundleName;
    std::string moduleName;
    CompleteResourceObject(obj, bundleName, moduleName);
    if (obj.type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto resourceObject = GetResourceObjectByBundleAndModule(obj);
    auto resourceWrapper = CreateResourceWrapper(obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    if (obj.id == -1) {
        if (!obj.paramsJsonStr) {
            return false;
        }
        auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
        if (!params->IsArray()) {
            return false;
        }
        auto param = params->GetArrayItem(0);
        result = resourceWrapper->GetColorByName(param->GetString());
        return true;
    }
    if (obj.type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(static_cast<uint32_t>(obj.id));
        return Color::ParseColorString(value, result);
    }
    if (obj.type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = resourceWrapper->GetInt(static_cast<uint32_t>(obj.id));
        result = Color(ColorAlphaAdapt(value));
        return true;
    }
    if (obj.type == static_cast<int32_t>(ResourceType::COLOR)) {
        result = resourceWrapper->GetColor(static_cast<uint32_t>(obj.id));
        result.SetResourceId(static_cast<uint32_t>(obj.id));
        return true;
    }
    return false;
}

bool ViewAbstract::ParseCjDimension(
    NativeResourceObject& obj, CalcDimension& result, DimensionUnit defaultUnit, bool isSupportPercent)
{
    std::string bundleName;
    std::string moduleName;
    CompleteResourceObject(obj, bundleName, moduleName);
    if (obj.type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto resourceObject = GetResourceObjectByBundleAndModule(obj);
    auto resourceWrapper = CreateResourceWrapper(obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    if (obj.id == -1) {
        if (!obj.paramsJsonStr) {
            return false;
        }
        auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
        if (!params->IsArray()) {
            return false;
        }
        auto param = params->GetArrayItem(0);
        if (obj.type == static_cast<int32_t>(ResourceType::STRING)) {
            auto value = resourceWrapper->GetStringByName(param->GetString());
            return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
        }
        if (obj.type == static_cast<int32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceWrapper->GetIntByName(param->GetString()));
            return StringUtils::StringToDimensionWithUnitNG(value, result, defaultUnit);
        }
        result = resourceWrapper->GetDimensionByName(param->GetString());
        return true;
    }
    if (obj.type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(static_cast<uint32_t>(obj.id));
        return StringUtils::StringToCalcDimensionNG(value, result, false, defaultUnit);
    }
    if (obj.type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(static_cast<uint32_t>(obj.id)));
        return StringUtils::StringToDimensionWithUnitNG(value, result, defaultUnit);
    }
    if (obj.type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(static_cast<uint32_t>(obj.id));
        return true;
    }
    return false;
}

bool ViewAbstract::ParseCjDimensionVP(NativeResourceObject& obj, CalcDimension& result, bool isSupportPercent)
{
    return ParseCjDimension(obj, result, DimensionUnit::VP, isSupportPercent);
}

bool ViewAbstract::ParseCjDimensionFP(NativeResourceObject& obj, CalcDimension& result, bool isSupportPercent)
{
    return ParseCjDimension(obj, result, DimensionUnit::FP, isSupportPercent);
}

bool ViewAbstract::ParseCjDouble(NativeResourceObject& obj, double& result)
{
    std::string bundleName;
    std::string moduleName;
    CompleteResourceObject(obj, bundleName, moduleName);
    if (obj.type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto resourceObject = GetResourceObjectByBundleAndModule(obj);
    auto resourceWrapper = CreateResourceWrapper(obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    if (obj.id == -1) {
        if (!obj.paramsJsonStr) {
            return false;
        }
        auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
        if (!params->IsArray()) {
            return false;
        }
        auto param = params->GetArrayItem(0);
        if (obj.type == static_cast<int32_t>(ResourceType::STRING)) {
            auto value = resourceWrapper->GetStringByName(param->GetString());
            return StringUtils::StringToDouble(value, result);
        }
        if (obj.type == static_cast<int32_t>(ResourceType::FLOAT)) {
            result = resourceWrapper->GetDoubleByName(param->GetString());
            return true;
        }
        if (obj.type == static_cast<int32_t>(ResourceType::INTEGER)) {
            result = resourceWrapper->GetIntByName(param->GetString());
            return true;
        }
        return false;
    }
    if (obj.type == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(static_cast<uint32_t>(obj.id));
        return StringUtils::StringToDouble(value, result);
    }
    if (obj.type == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDouble(static_cast<uint32_t>(obj.id));
        return true;
    }
    if (obj.type == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = resourceWrapper->GetInt(static_cast<uint32_t>(obj.id));
        return true;
    }
    return false;
}

bool ViewAbstract::ParseCjInteger(NativeResourceObject& obj, int32_t& result)
{
    return ParseCjInteger<int32_t>(obj, result);
}

bool ViewAbstract::ParseCjInteger(NativeResourceObject& obj, uint32_t& result)
{
    return ParseCjInteger<uint32_t>(obj, result);
}

bool ViewAbstract::ParseCjBool(NativeResourceObject& obj, bool& result)
{
    std::string bundleName;
    std::string moduleName;
    CompleteResourceObject(obj, bundleName, moduleName);
    if (obj.type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto resourceObject = GetResourceObjectByBundleAndModule(obj);
    auto resourceWrapper = CreateResourceWrapper(obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    if (obj.id == -1) {
        if (!obj.paramsJsonStr) {
            return false;
        }
        auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
        if (!params->IsArray()) {
            return false;
        }
        auto param = params->GetArrayItem(0);
        if (obj.type == static_cast<int32_t>(ResourceType::BOOLEAN)) {
            result = resourceWrapper->GetBooleanByName(param->GetString());
            return true;
        }
        return false;
    }

    if (obj.type == static_cast<int32_t>(ResourceType::BOOLEAN)) {
        result = resourceWrapper->GetBoolean(static_cast<uint32_t>(obj.id));
        return true;
    }
    return false;
}

bool ViewAbstract::ParseCjIntegerArray(NativeResourceObject& obj, std::vector<uint32_t>& result)
{
    std::string bundleName;
    std::string moduleName;
    CompleteResourceObject(obj, bundleName, moduleName);
    if (obj.type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto resourceObject = GetResourceObjectByBundleAndModule(obj);
    auto resourceWrapper = CreateResourceWrapper(obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    if (obj.id == -1) {
        if (!obj.paramsJsonStr) {
            return false;
        }
        auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
        if (!params->IsArray()) {
            return false;
        }
        auto param = params->GetArrayItem(0);
        if (obj.type == static_cast<int32_t>(ResourceType::INTARRAY)) {
            result = resourceWrapper->GetIntArrayByName(param->GetString());
            return true;
        }
        return false;
    }
    if (obj.type == static_cast<int32_t>(ResourceType::INTARRAY)) {
        result = resourceWrapper->GetIntArray(static_cast<uint32_t>(obj.id));
        return true;
    }
    return false;
}

bool ViewAbstract::ParseCjStringArray(NativeResourceObject& obj, std::vector<std::string>& result)
{
    std::string bundleName;
    std::string moduleName;
    CompleteResourceObject(obj, bundleName, moduleName);
    if (obj.type == UNKNOWN_RESOURCE_TYPE) {
        return false;
    }
    auto resourceObject = GetResourceObjectByBundleAndModule(obj);
    auto resourceWrapper = CreateResourceWrapper(obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    if (obj.id == -1) {
        if (!obj.paramsJsonStr) {
            return false;
        }
        auto params = JsonUtil::ParseJsonString(obj.paramsJsonStr);
        if (!params->IsArray()) {
            return false;
        }
        auto param = params->GetArrayItem(0);
        if (obj.type == static_cast<int32_t>(ResourceType::STRARRAY)) {
            result = resourceWrapper->GetStringArrayByName(param->GetString());
            return true;
        }
        return false;
    }
    if (obj.type == static_cast<int32_t>(ResourceType::STRARRAY)) {
        result = resourceWrapper->GetStringArray(static_cast<uint32_t>(obj.id));
        return true;
    }
    return false;
}

void ViewAbstract::ParseOnCreateMenu(CjOnCreateMenu& cjOnCreateMenu, NG::OnCreateMenuCallback& onCreateMenuCallback)
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(cjOnCreateMenu), node = frameNode, instanceId = Container::CurrentId()](
                          const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        std::vector<NG::MenuOptionsParam> menuParams;
        CHECK_NULL_RETURN(pipelineContext, menuParams);
        pipelineContext->UpdateCurrentActiveNode(node);
        auto cjMenuItems = new std::vector<FfiTextMenuItem>(systemMenuItems.size());
        for (size_t i = 0; i < systemMenuItems.size(); i++) {
            FfiTextMenuItem item;
            auto content = systemMenuItems[i].menuOptionsParam.content;
            auto icon = systemMenuItems[i].menuOptionsParam.icon;
            item.content = content.has_value() ? Utils::MallocCString(content.value()) : Utils::MallocCString("");
            item.icon = icon.has_value() ? Utils::MallocCString(icon.value()) : Utils::MallocCString("");
            item.id = Utils::MallocCString(systemMenuItems[i].menuOptionsParam.id);
            (*cjMenuItems)[i] = item;
        }
        auto vectorResult = func(cjMenuItems);
        auto menuItemsArray = reinterpret_cast<std::vector<FfiTextMenuItem>*>(vectorResult);
        for (size_t i = 0; i < menuItemsArray->size(); i++) {
            auto ffiMenuItem = (*menuItemsArray)[i];
            NG::MenuOptionsParam menuOptionsParam;
            menuOptionsParam.content =
                ffiMenuItem.content.value ? std::make_optional(ffiMenuItem.content.value) : std::nullopt;
            menuOptionsParam.icon = ffiMenuItem.icon.value ? std::make_optional(ffiMenuItem.icon.value) : std::nullopt;
            menuOptionsParam.id = ffiMenuItem.id.value;
            menuParams.emplace_back(menuOptionsParam);
        }
        delete menuItemsArray;
        return menuParams;
    };
    onCreateMenuCallback = cjCallback;
}

void ViewAbstract::ParseOnMenuItemClick(
    CjOnMenuItemClick& cjOnMenuItemClick, NG::OnMenuItemClickCallback& onMenuItemClick)
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(cjOnMenuItemClick), node = frameNode,
                          instanceId = Container::CurrentId()](NG::MenuItemParam menuOptionsParam) -> bool {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
        auto content = menuOptionsParam.menuOptionsParam.content;
        auto icon = menuOptionsParam.menuOptionsParam.icon;
        FfiTextMenuItem ffiTextMenuItem;
        ffiTextMenuItem.content =
            content.has_value() ? Utils::MallocCString(content.value()) : Utils::MallocCString("");
        ffiTextMenuItem.icon = icon.has_value() ? Utils::MallocCString(icon.value()) : Utils::MallocCString("");
        ffiTextMenuItem.id = Utils::MallocCString(menuOptionsParam.menuOptionsParam.id);
        return func(ffiTextMenuItem, menuOptionsParam.start, menuOptionsParam.end);
    };
    onMenuItemClick = cjCallback;
}

bool ViewAbstract::ParseEditMenuOptions(CjOnCreateMenu& cjOnCreateMenu, CjOnMenuItemClick& cjOnMenuItemClick,
    NG::OnCreateMenuCallback& onCreateMenuCallback, NG::OnMenuItemClickCallback& onMenuItemClick)
{
    ParseOnCreateMenu(cjOnCreateMenu, onCreateMenuCallback);
    ParseOnMenuItemClick(cjOnMenuItemClick, onMenuItemClick);
    return true;
}
} // namespace OHOS::Ace::Framework
