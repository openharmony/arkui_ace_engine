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

#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

#include "ecmascript/napi/include/jsnapi.h"
#include "jsnapi_expo.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "frameworks/base/image/pixel_map.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/core/common/card_scope.h"
#include "frameworks/core/common/resource/resource_configuration.h"
#include "frameworks/core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
namespace {
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

bool ParseLocalizedMargin(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen, ArkUISizeType& result)
{
    if (ArkTSUtils::ParseJsLengthMetrics(vm, value, dimen)) {
        result.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            result.string = dimen.CalcValue().c_str();
        } else {
            result.value = dimen.Value();
        }
        return true;
    }
    return false;
}

void ParseNormalMargin(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen, ArkUISizeType& result)
{
    if (ArkTSUtils::ParseJsDimensionVp(vm, value, dimen)) {
        result.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            result.string = dimen.CalcValue().c_str();
        } else {
            result.value = dimen.Value();
        }
    }
}
}
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr int PARAM_ARR_LENGTH_2 = 2;
const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
const std::regex FLOAT_PATTERN(R"(-?(0|[1-9]\d*)(\.\d+))", std::regex::icase);
const std::string RESOURCE_TOKEN_PATTERN = "(app|sys|\\[.+?\\])\\.(\\S+?)\\.(\\S+)";
const std::string RESOURCE_NAME_PATTERN = "\\[(.+?)\\]";
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr uint32_t RES_TYPE_INDEX = 2;
constexpr int32_t UNKNOWN_RESOURCE_ID = -1;
constexpr int32_t UNKNOWN_RESOURCE_TYPE = -1;
const std::string DEFAULT_STR = "-1";
constexpr  int32_t REPLACEHOLDER_INDEX = 2;
const Color DEFAULT_TEXT_SHADOW_COLOR = Color::BLACK;
constexpr bool DEFAULT_TEXT_SHADOW_FILL = false;
constexpr ShadowType DEFAULT_TEXT_SHADOW_TYPE = ShadowType::COLOR;
constexpr char JS_TEXT_MENU_ID_CLASS_NAME[] = "TextMenuItemId";
const std::string CUSTOM_SYMBOL_SUFFIX = "_CustomSymbol";

uint32_t ArkTSUtils::ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

bool ArkTSUtils::ParseJsColor(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsColor(vm, value, result, resourceObject);
}

bool ArkTSUtils::ParseJsColor(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result,
    RefPtr<ResourceObject>& resourceObject)
{
    if (value->IsNumber()) {
        result = Color(value->Uint32Value(vm));
        return true;
    }
    if (value->IsString(vm)) {
        return Color::ParseColorString(value->ToString(vm)->ToString(vm), result);
    }
    if (value->IsObject(vm)) {
        auto obj = value->ToObject(vm);
        auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
        if (!resId->IsNumber()) {
            return false;
        }
        return ParseJsColorFromResource(vm, value, result, resourceObject);
    }
    return false;
}

bool ArkTSUtils::ParseJsSymbolColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsSymbolColorAlpha(vm, value, result, resourceObject);
}

bool ArkTSUtils::ParseJsSymbolColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result,
    RefPtr<ResourceObject>& resourceObject)
{
    if (!value->IsNumber() && !value->IsString(vm) && !value->IsObject(vm)) {
        return false;
    }
    if (value->IsNumber()) {
        result = Color(ColorAlphaAdapt(value->Uint32Value(vm)));
    } else if (value->IsString(vm)) {
        Color::ParseColorString(value->ToString(vm)->ToString(vm), result);
    } else if (value->IsObject(vm)) {
        ParseJsColorFromResource(vm, value, result, resourceObject);
    }
    return true;
}

bool ArkTSUtils::ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& color,
    std::vector<RefPtr<ResourceObject>>& resObjs)
{
    RefPtr<ResourceObject> resObj;
    bool result = ArkTSUtils::ParseJsColorAlpha(vm, value, color, resObj);
    if (SystemProperties::ConfigChangePerform()) {
        if (resObj) {
            resObjs.push_back(resObj);
        } else {
            resObjs.push_back(nullptr);
        }
    }
    return result;
}

bool ArkTSUtils::ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result, bool fromTheme)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsColorAlpha(vm, value, result, resourceObject, fromTheme);
}

bool ArkTSUtils::ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result,
    RefPtr<ResourceObject>& resourceObject, bool fromTheme)
{
    if (value->IsNumber()) {
        result = Color(ColorAlphaAdapt(value->Uint32Value(vm)));
        return true;
    }
    if (value->IsString(vm)) {
        return Color::ParseColorString(value->ToString(vm)->ToString(vm), result);
    }
    if (value->IsObject(vm)) {
        if (ParseColorMetricsToColor(vm, value, result)) {
            return true;
        }
        return ParseJsColorFromResource(vm, value, result, resourceObject, fromTheme);
    }
    return false;
}

bool ArkTSUtils::ParseJsColorContent(const EcmaVM* vm, const Local<JSValueRef>& value)
{
    if (!value->IsObject(vm)) {
        return false;
    }
    auto obj = value->ToObject(vm);
    auto colorContentValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "colorContent_"));
    return !colorContentValue.IsEmpty() && colorContentValue->IsString(vm) &&
           colorContentValue->ToString(vm)->ToString(vm) == "ORIGIN";
}

bool ArkTSUtils::ParseJsColorAlpha(
    const EcmaVM* vm, const Local<JSValueRef>& value, Color& result, const Color& defaultColor)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsColorAlpha(vm, value, result, defaultColor, resourceObject);
}

bool ArkTSUtils::ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value,
    Color& result, const Color& defaultColor, RefPtr<ResourceObject>& resourceObject)
{
    if (!value->IsNumber() && !value->IsString(vm) && !value->IsObject(vm)) {
        return false;
    }
    if (value->IsNumber()) {
        result = Color(ColorAlphaAdapt(value->Uint32Value(vm)));
        return true;
    }
    if (value->IsString(vm)) {
        return Color::ParseColorString(value->ToString(vm)->ToString(vm), result, defaultColor);
    }
    return ParseJsColorFromResource(vm, value, result, resourceObject);
}

std::string ToString(const EcmaVM* vm,  Local<JSValueRef>& jsVal)
{
    panda::LocalScope scope(vm);
    if (jsVal->IsObject(vm)) {
        return panda::JSON::Stringify(vm, jsVal)->ToString(vm)->ToString(vm);
    }
    return jsVal->ToString(vm)->ToString(vm);
}

RefPtr<ResourceObject> GetResourceObject(const EcmaVM* vm, const Local<JSValueRef>& jsObj)
{
    auto obj = jsObj->ToObject(vm);
    auto id = obj->Get(vm, panda::ExternalStringCache::GetCachedString(vm,
        static_cast<int32_t>(Framework::ArkUIIndex::ID)))->Int32Value(vm);
    auto type = obj->Get(vm, panda::ExternalStringCache::GetCachedString(vm,
        static_cast<int32_t>(Framework::ArkUIIndex::TYPE)))->Int32Value(vm);
    auto args = obj->Get(vm, panda::ExternalStringCache::GetCachedString(vm,
        static_cast<int32_t>(Framework::ArkUIIndex::PARAMS)));

    std::string bundleName;
    std::string moduleName;
    auto bundle = obj->Get(vm, panda::ExternalStringCache::GetCachedString(vm,
        static_cast<int32_t>(Framework::ArkUIIndex::BUNDLE_NAME)));
    auto module = obj->Get(vm, panda::ExternalStringCache::GetCachedString(vm,
        static_cast<int32_t>(Framework::ArkUIIndex::MODULE_NAME)));
    if (bundle->IsString(vm) && module->IsString(vm)) {
        bundleName = bundle->ToString(vm)->ToString(vm);
        moduleName = module->ToString(vm)->ToString(vm);
    }

    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    std::vector<ResourceObjectParams> resObjParamsList;
    auto size = static_cast<int32_t>(params->Length(vm));
    for (int32_t i = 0; i < size; i++) {
        auto item = panda::ArrayRef::GetValueAt(vm, params, i);

        std::string valueString = ToString(vm, item).c_str();

        ResourceObjectParams resObjParams { .value = valueString };
        if (item->IsString(vm)) {
            resObjParams.type = ResourceObjectParamType::STRING;
        } else if (item->IsNumber()) {
            if (std::regex_match(item->ToString(vm)->ToString(vm), FLOAT_PATTERN)) {
                resObjParams.type = OHOS::Ace::ResourceObjectParamType::FLOAT;
            } else {
                resObjParams.type = OHOS::Ace::ResourceObjectParamType::INT;
            }
        }
        resObjParamsList.emplace_back(resObjParams);
    }
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(
        id, type, resObjParamsList, bundleName, moduleName, Container::CurrentIdSafely());
    return resourceObject;
}

RefPtr<OHOS::Ace::ThemeConstants> GetThemeConstants(const EcmaVM* vm, const Local<JSValueRef>& jsObj)
{
    std::string bundleName;
    std::string moduleName;
    if (!jsObj->IsUndefined()) {
        auto obj = jsObj->ToObject(vm);
        auto bundle = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
        auto module = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
        if (bundle->IsString(vm) && module->IsString(vm)) {
            bundleName = bundle->ToString(vm)->ToString(vm);
            moduleName = module->ToString(vm)->ToString(vm);
        }
    }

    auto cardId = CardScope::CurrentId();
    if (cardId != OHOS::Ace::INVALID_CARD_ID) {
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

RefPtr<ResourceWrapper> CreateResourceWrapper(const EcmaVM* vm, const Local<JSValueRef>& jsObj,
    RefPtr<ResourceObject>& resourceObject, bool fromTheme = false)
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject, fromTheme);
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = GetThemeConstants(vm, jsObj);
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

bool IsGetResourceByName(const EcmaVM* vm, const Local<JSValueRef>& jsObj)
{
    auto obj = jsObj->ToObject(vm);
    auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
    if (!args->IsArray(vm)) {
        return false;
    }
    auto bundleName = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
    auto moduleName = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
    if (!bundleName->IsString(vm) || !moduleName->IsString(vm)) {
        return false;
    }
    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    if (params->Length(vm) == 0) {
        return false;
    }
    return true;
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

bool ParseDollarResource(std::string& targetModule, ResourceType& resType,
    std::string& resName, bool isParseType)
{
    std::smatch results;
    std::regex tokenRegex(RESOURCE_TOKEN_PATTERN);
    if (!std::regex_match(resName, results, tokenRegex)) {
        return false;
    }
    targetModule = results[1];
    if (isParseType && !ConvertResourceType(results[RES_TYPE_INDEX], resType)) {
        return false;
    }
    return true;
}

void CompleteResourceObjectFromParams(const EcmaVM* vm, Local<panda::ObjectRef>& jsObj,
    std::string& targetModule, ResourceType& resType, std::string& resName)
{
    auto type = jsObj->Get(vm,
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::TYPE)));
    int32_t typeNum = -1;
    if (type->IsNumber()) {
        typeNum = type->Int32Value(vm);
    }
    auto resId = jsObj->Get(vm,
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::ID)));
    int32_t resIdValue = resId->Int32Value(vm);
    if (resIdValue != UNKNOWN_RESOURCE_ID) {
        return;
    }
    auto args = jsObj->Get(vm,
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::PARAMS)));
    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    auto identity = panda::ArrayRef::GetValueAt(vm, params, 0);
    if (!identity->IsString(vm)) {
        return;
    }
    resName = identity->ToString(vm)->ToString(vm);
    bool isParseDollarResourceSuccess =
        ParseDollarResource(targetModule, resType, resName, typeNum == UNKNOWN_RESOURCE_TYPE);
    if (!isParseDollarResourceSuccess) {
        return;
    }

    auto moduleName = jsObj->Get(vm,
        panda::ExternalStringCache::GetCachedString(vm,
            static_cast<int32_t>(Framework::ArkUIIndex::MODULE_NAME)));
    if (moduleName->IsString(vm) && moduleName->ToString(vm)->ToString(vm).empty()) {
        std::regex resNameRegex(RESOURCE_NAME_PATTERN);
        std::smatch resNameResults;
        if (std::regex_match(targetModule, resNameResults, resNameRegex)) {
            jsObj->Set(vm,
                panda::ExternalStringCache::GetCachedString(vm,
                    static_cast<int32_t>(Framework::ArkUIIndex::MODULE_NAME)),
                panda::StringRef::NewFromUtf8(vm, resNameResults.str(1).c_str()));
        } else {
            jsObj->Set(vm,
                panda::ExternalStringCache::GetCachedString(vm,
                    static_cast<int32_t>(Framework::ArkUIIndex::MODULE_NAME)),
                panda::StringRef::NewFromUtf8(vm, ""));
        }
    }
    if (typeNum == UNKNOWN_RESOURCE_TYPE) {
        jsObj->Set(vm, panda::ExternalStringCache::GetCachedString(vm,
            static_cast<int32_t>(Framework::ArkUIIndex::TYPE)),
            panda::NumberRef::New(vm, static_cast<int32_t>(resType)));
    }
}

void CompleteResourceObjectFromId(const EcmaVM* vm, const Local<JSValueRef>& type, Local<panda::ObjectRef>& jsObj,
    ResourceType& resType, const std::string& resName)
{
    auto args = jsObj->Get(vm,
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::PARAMS)));
    if (!args->IsArray(vm)) {
        return;
    }
    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    auto paramCount = params->Length(vm);
    auto name = panda::StringRef::NewFromUtf8(vm, resName.c_str());
    if (resType == ResourceType::PLURAL || resType == ResourceType::STRING) {
        std::vector<Local<JSValueRef>> tmpParams;
        for (uint32_t i = 0; i < paramCount; i++) {
            auto param = panda::ArrayRef::GetValueAt(vm, params, i);
            tmpParams.insert(tmpParams.end(), param);
        }
        panda::ArrayRef::SetValueAt(vm, params, 0, name);
        uint32_t paramIndex = 1;
        auto firstParam = jsObj->Get(vm,
            panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::TYPE)));
        if (!firstParam->IsNull()) {
            panda::ArrayRef::SetValueAt(vm, params, paramIndex, firstParam);
            paramIndex++;
        }
        for (auto tmpParam : tmpParams) {
            panda::ArrayRef::SetValueAt(vm, params, paramIndex, tmpParam);
            paramIndex++;
        }
    } else {
        panda::ArrayRef::SetValueAt(vm, params, 0, name);
    }
    jsObj->Set(vm, panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::ID)),
                panda::NumberRef::New(vm, UNKNOWN_RESOURCE_ID));
    jsObj->Set(vm, panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::TYPE)),
            panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(resType)));
    if (!jsObj->Has(vm,
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::BUNDLE_NAME)))) {
        jsObj->Set(vm,
            panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::BUNDLE_NAME)),
            panda::StringRef::NewFromUtf8(vm, ""));
    }
    if (!jsObj->Has(vm,
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::MODULE_NAME)))) {
        jsObj->Set(vm,
            panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::MODULE_NAME)),
            panda::StringRef::NewFromUtf8(vm, ""));
    }
}

void ArkTSUtils::CompleteResourceObject(const EcmaVM* vm, Local<panda::ObjectRef>& jsObj)
{
    // dynamic $r raw input format is
    // {"id":"app.xxx.xxx", "params":[], "bundleName":"xxx", "moduleName":"xxx"}
    auto resId = jsObj->Get(vm,
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::ID)));
    ResourceType resType = ResourceType::NONE;
    std::string targetModule;
    std::string resName;
    if (resId->IsString(vm)) {
        auto type = jsObj->Get(vm,
            panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::TYPE)));
        int32_t typeNum = -1;
        if (type->IsNumber()) {
            typeNum = type->Int32Value(vm);
        }
        resName = resId->ToString(vm)->ToString(vm);
        if (!ParseDollarResource(targetModule, resType, resName, typeNum == UNKNOWN_RESOURCE_TYPE)) {
            return;
        }
        CompleteResourceObjectFromId(vm, type, jsObj, resType, resName);
    } else if (resId->IsNumber()) {
        int32_t resIdValue = resId->Int32Value(vm);
        if (resIdValue == -1) {
            CompleteResourceObjectFromParams(vm, jsObj, targetModule, resType, resName);
        }
    }

    std::string bundleName;
    std::string moduleName;
    ArkTSUtils::GetJsMediaBundleInfo(vm, jsObj, bundleName, moduleName);
    if ((bundleName.empty() && !moduleName.empty()) || bundleName == DEFAULT_HAR_BUNDLE_NAME) {
        bundleName = GetBundleNameFromContainer();
        jsObj->Set(vm,
            panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::BUNDLE_NAME)),
            panda::StringRef::NewFromUtf8(vm, bundleName.c_str()));
    }
    if (moduleName == DEFAULT_HAR_MODULE_NAME) {
        moduleName = GetModuleNameFromContainer();
        jsObj->Set(vm,
            panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::MODULE_NAME)),
            panda::StringRef::NewFromUtf8(vm, moduleName.c_str()));
    }
}

bool ArkTSUtils::ParseJsColorFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsObj, Color& result,
    bool fromTheme)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsColorFromResource(vm, jsObj, result, resourceObject, fromTheme);
}

bool ArkTSUtils::ParseJsColorFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsObj, Color& result,
    RefPtr<ResourceObject>& resourceObject, bool fromTheme)
{
    auto obj = jsObj ->ToObject(vm);
    auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (!resId->IsNumber()) {
        return false;
    }

    CompleteResourceObject(vm, obj);
    resourceObject = GetResourceObject(vm, jsObj);
    auto resourceWrapper = CreateResourceWrapper(vm, jsObj, resourceObject, fromTheme);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->Int32Value(vm);
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsObj)) {
            return false;
        }
        auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        result = resourceWrapper->GetColorByName(param->ToString(vm)->ToString(vm));
        return true;
    }
    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (type->IsNull() || !type->IsNumber()) {
        return false;
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->Int32Value(vm));
        return Color::ParseColorString(value, result);
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = resourceWrapper->GetInt(resId->Int32Value(vm));
        result = Color(ColorAlphaAdapt(value));
        return true;
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::COLOR)) {
        result = resourceWrapper->GetColor(resId->ToNumber(vm)->Value());
        result.SetResourceId(resId->Int32Value(vm));
        return true;
    }
    return false;
}

bool ArkTSUtils::ParseColorMetricsToColor(const EcmaVM* vm, const Local<JSValueRef>& jsValue, Color& result)
{
    if (!jsValue->IsObject(vm)) {
        return false;
    }
    auto obj = jsValue->ToObject(vm);
    auto toNumericProp = obj->Get(vm, "toNumeric");
    auto colorSpaceProp = obj->Get(vm, "getColorSpace");
    if (toNumericProp->IsFunction(vm) && colorSpaceProp->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = toNumericProp;
        auto colorVal = func->Call(vm, obj, nullptr, 0);
        result.SetValue(colorVal->Uint32Value(vm));

        func = colorSpaceProp;
        auto colorSpaceVal = func->Call(vm, obj, nullptr, 0);
        if (colorSpaceVal->IsNumber() &&
            colorSpaceVal->Uint32Value(vm) == static_cast<uint32_t>(ColorSpace::DISPLAY_P3)) {
            result.SetColorSpace(ColorSpace::DISPLAY_P3);
        } else {
            result.SetColorSpace(ColorSpace::SRGB);
        }

        return true;
    }
    return false;
}

bool ArkTSUtils::ParseJsDimensionFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsObj,
    DimensionUnit dimensionUnit, CalcDimension& result, RefPtr<ResourceObject>& resourceObject)
{
    auto obj = jsObj->ToObject(vm);
    auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (!resId->IsNumber()) {
        return false;
    }

    CompleteResourceObject(vm, obj);
    resourceObject = GetResourceObject(vm, jsObj);

    auto resourceWrapper = CreateResourceWrapper(vm, jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    auto resIdNum = resId->Int32Value(vm);
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsObj)) {
            return false;
        }
        auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        result = resourceWrapper->GetDimensionByName(param->ToString(vm)->ToString(vm));
        return true;
    }
    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (type->IsNull() || !type->IsNumber()) {
        return false;
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->Int32Value(vm));
        result = StringUtils::StringToCalcDimension(value, false, dimensionUnit);
        return true;
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resId->Int32Value(vm)));
        result = StringUtils::StringToDimensionWithUnit(value, dimensionUnit);
        return true;
    }
    result = resourceWrapper->GetDimension(resId->Int32Value(vm));
    return true;
}

bool ArkTSUtils::ParseJsDimensionFromResourceNG(const EcmaVM* vm, const Local<JSValueRef>& jsObj,
    DimensionUnit dimensionUnit, CalcDimension& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsDimensionFromResourceNG(vm, jsObj, dimensionUnit, result, resourceObject);
}

bool ArkTSUtils::ParseJsDimensionFromResourceNG(const EcmaVM* vm, const Local<JSValueRef>& jsObj,
    DimensionUnit dimensionUnit, CalcDimension& result, RefPtr<ResourceObject>& resourceObject)
{
    auto obj = jsObj->ToObject(vm);
    auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (!resId->IsNumber()) {
        return false;
    }

    CompleteResourceObject(vm, obj);
    resourceObject = GetResourceObject(vm, jsObj);

    auto resourceWrapper = CreateResourceWrapper(vm, jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    auto resIdNum = resId->Int32Value(vm);
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsObj)) {
            return false;
        }
        auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        result = resourceWrapper->GetDimensionByName(param->ToString(vm)->ToString(vm));
        return true;
    }
    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (type->IsNull() || !type->IsNumber()) {
        return false;
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->Int32Value(vm));
        return StringUtils::StringToCalcDimensionNG(value, result, false, dimensionUnit);
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resId->Int32Value(vm)));
        StringUtils::StringToDimensionWithUnitNG(value, result, dimensionUnit);
        return true;
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(resId->Int32Value(vm));
        return true;
    }

    return false;
}

bool ArkTSUtils::ParseStringArray(const EcmaVM* vm, const Local<JSValueRef>& arg,
    std::string* array, int32_t defaultLength)
{
    CHECK_NULL_RETURN(vm, false);
    CHECK_NULL_RETURN(array, false);
    if (defaultLength <= 0) {
        return false;
    }
    auto handle = panda::CopyableGlobal<panda::ArrayRef>(vm, arg);
    if (handle.IsEmpty() || handle->IsUndefined() || handle->IsNull()) {
        return false;
    }
    int32_t length = static_cast<int32_t>(handle->Length(vm));
    if (length != defaultLength) {
        return false;
    }
    for (int32_t i = 0; i < length; i++) {
        auto value = handle->GetValueAt(vm, arg, i);
        if (!ParseJsMedia(vm, value, *(array + i))) {
            *(array + i) = "";
        }
    }
    return true;
}

bool ArkTSUtils::ParseJsDimensionVp(
    const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& result, bool enableCheckInvalidvalue)
{
    return ArkTSUtils::ParseJsDimension(vm, value, result, DimensionUnit::VP, true, enableCheckInvalidvalue);
}

bool ArkTSUtils::ParseJsDimensionVp(const EcmaVM* vm, const Local<JSValueRef>& value,
    CalcDimension& result, RefPtr<ResourceObject>& resourceObject, bool enableCheckInvalidvalue)
{
    return ArkTSUtils::ParseJsDimension(vm, value, result, DimensionUnit::VP, resourceObject, true,
        enableCheckInvalidvalue);
}

bool ArkTSUtils::ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result)
{
    if (value->IsNumber()) {
        result = value->Int32Value(vm);
        return true;
    }
    return false;
}

bool ArkTSUtils::ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, uint32_t &result)
{
    if (value->IsNumber()) {
        result = value->Uint32Value(vm);
        return true;
    }
    // resource ignore by design
    return false;
}

bool ArkTSUtils::ParseJsIntegerWithResource(const EcmaVM* vm, const Local<JSValueRef>& jsValue, int32_t& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsIntegerWithResource(vm, jsValue, result, resourceObject);
}

bool ArkTSUtils::ParseJsIntegerWithResource(const EcmaVM* vm, const Local<JSValueRef>& jsValue, int32_t& result,
    RefPtr<ResourceObject>& resourceObject)
{
    if (!jsValue->IsNumber() && !jsValue->IsObject(vm)) {
        return false;
    }

    if (jsValue->IsNumber()) {
        result = jsValue->Int32Value(vm);
        return true;
    }

    auto jsObj = jsValue->ToObject(vm);
    auto type = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    auto id = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    int32_t resourceType = 0;
    if (!type->IsNumber() || !id->IsNumber()) {
        return false;
    }
    resourceType = type->Int32Value(vm);
    auto resIdNum = id->Int32Value(vm);

    CompleteResourceObject(vm, jsObj);
    resourceObject = GetResourceObject(vm, jsValue);
    auto resourceWrapper = CreateResourceWrapper(vm, jsValue, resourceObject);
    CHECK_NULL_RETURN(resourceWrapper, false);

    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsObj)) {
            return false;
        }
        auto args = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        if (resourceType == static_cast<int32_t>(ResourceType::INTEGER)) {
            result = resourceWrapper->GetIntByName(param->ToString(vm)->ToString(vm));
            return true;
        }
        return false;
    }

    if (resourceType == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = resourceWrapper->GetInt(resIdNum);
        return true;
    }

    return false;
}

bool GetResourceIdAndType(const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj, int32_t& resId, int32_t& resType)
{
    auto id = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    auto type = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (!id->IsNumber() || !type->IsNumber()) {
        return false;
    }

    resId = id->Int32Value(vm);
    resType = type->Int32Value(vm);
    return true;
}

bool ArkTSUtils::ParseResourceToDouble(const EcmaVM* vm, const Local<JSValueRef>& jsValue, double& result,
    RefPtr<ResourceObject>& resourceObject)
{
    auto jsObj = jsValue->ToObject(vm);
    int32_t resId;
    int32_t resType;
    if (jsObj->IsNull() || !GetResourceIdAndType(vm, jsObj, resId, resType)) {
        return false;
    }
    CompleteResourceObject(vm, jsObj);
    resourceObject = GetResourceObject(vm, jsObj);
    auto resourceWrapper = CreateResourceWrapper(vm, jsObj, resourceObject);
    CHECK_NULL_RETURN(resourceWrapper, false);
    if (resId == -1) {
        if (!IsGetResourceByName(vm, jsObj)) {
            return false;
        }
        auto args = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        if (resType == static_cast<int32_t>(ResourceType::STRING)) {
            auto numberString = resourceWrapper->GetStringByName(param->ToString(vm)->ToString(vm));
            return StringUtils::StringToDouble(numberString, result);
        }
        if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
            result = resourceWrapper->GetIntByName(param->ToString(vm)->ToString(vm));
            return true;
        }
        if (resType == static_cast<int32_t>(ResourceType::FLOAT)) {
            result = resourceWrapper->GetDoubleByName(param->ToString(vm)->ToString(vm));
            return true;
        }
        return false;
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::STRING)) {
        auto numberString = resourceWrapper->GetString(resId);
        return StringUtils::StringToDouble(numberString, result);
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = resourceWrapper->GetInt(resId);
        return true;
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDouble(resId);
        return true;
    }
    return false;
}

bool ArkTSUtils::ParseJsDouble(const EcmaVM *vm, const Local<JSValueRef> &value, double &result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsDouble(vm, value, result, resourceObject);
}

bool ArkTSUtils::ParseJsDouble(const EcmaVM *vm, const Local<JSValueRef> &value, double &result,
    RefPtr<ResourceObject>& resourceObject)
{
    if (value->IsNumber()) {
        result = value->ToNumber(vm)->Value();
        return true;
    }
    if (value->IsString(vm)) {
        return StringUtils::StringToDouble(value->ToString(vm)->ToString(vm), result);
    }
    if (value->IsObject(vm)) {
        return ParseResourceToDouble(vm, value, result, resourceObject);
    }
    return false;
}

bool ArkTSUtils::ParseAllBorder(const EcmaVM* vm, const Local<JSValueRef>& args, CalcDimension& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseAllBorder(vm, args, result, resourceObject);
}

bool ArkTSUtils::ParseAllBorder(const EcmaVM* vm, const Local<JSValueRef>& args, CalcDimension& result,
    RefPtr<ResourceObject>& resourceObject)
{
    if (ParseJsDimensionVp(vm, args, result, resourceObject)) {
        if (result.IsNegative()) {
            result.Reset();
        }
        return true;
    } else {
        return false;
    }
}

bool ArkTSUtils::ParseAllRadius(const EcmaVM* vm, const Local<JSValueRef>& args, CalcDimension& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseAllRadius(vm, args, result, resourceObject);
}

bool ArkTSUtils::ParseAllRadius(const EcmaVM* vm, const Local<JSValueRef>& args, CalcDimension& result,
    RefPtr<ResourceObject>& resourceObject)
{
    if (ParseJsDimensionVp(vm, args, result)) {
        if (result.IsNegative()) {
            result.Reset();
        }
        return true;
    } else {
        return false;
    }
}

bool ArkTSUtils::ParseJsDimensionNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit, bool isSupportPercent)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsDimensionNG(vm, jsValue, result, defaultUnit, resourceObject, isSupportPercent);
}

bool ArkTSUtils::ParseJsDimensionNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit, RefPtr<ResourceObject>& resourceObject, bool isSupportPercent)
{
    if (!jsValue->IsNumber() && !jsValue->IsString(vm) && !jsValue->IsObject(vm)) {
        return false;
    }
    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber(vm)->Value(), defaultUnit);
        return true;
    }
    if (jsValue->IsString(vm)) {
        auto value = jsValue->ToString(vm)->ToString(vm);
        if (value.back() == '%' && !isSupportPercent) {
            return false;
        }
        return StringUtils::StringToCalcDimensionNG(jsValue->ToString(vm)->ToString(vm), result, false, defaultUnit);
    }
    if (jsValue->IsObject(vm)) {
        return ParseJsDimensionFromResourceNG(vm, jsValue, defaultUnit, result, resourceObject);
    }
    return false;
}

bool ArkTSUtils::ParseJsDimensionVpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    bool isSupportPercent)
{
    return ArkTSUtils::ParseJsDimensionNG(vm, jsValue, result, DimensionUnit::VP, isSupportPercent);
}

bool ArkTSUtils::ParseJsDimensionVpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    RefPtr<ResourceObject>& resourceObject, bool isSupportPercent)
{
    return ArkTSUtils::ParseJsDimensionNG(vm, jsValue, result, DimensionUnit::VP, resourceObject, isSupportPercent);
}

bool ArkTSUtils::ParseJsDimension(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit, bool isSupportPercent, bool enableCheckInvalidvalue)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsDimension(vm, jsValue, result, defaultUnit, resourceObject,
        isSupportPercent, enableCheckInvalidvalue);
}

bool ArkTSUtils::ParseJsDimension(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit, RefPtr<ResourceObject>& resourceObject,
    bool isSupportPercent, bool enableCheckInvalidvalue)
{
    if (!jsValue->IsNumber() && !jsValue->IsString(vm) && !jsValue->IsObject(vm)) {
        return false;
    }

    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber(vm)->Value(), defaultUnit);
        return true;
    }
    if (jsValue->IsString(vm)) {
        auto stringValue = jsValue->ToString(vm)->ToString(vm);
        if (stringValue.back() == '%' && !isSupportPercent) {
            return false;
        }
        if (enableCheckInvalidvalue && stringValue.find("calc") == std::string::npos) {
            errno = 0;
            char* pEnd = nullptr;
            std::string str = jsValue->ToString(vm)->ToString(vm);
            std::strtod(str.c_str(), &pEnd);
            if (pEnd == str.c_str() || errno == ERANGE) {
                return false;
            }
        }
        result = StringUtils::StringToCalcDimension(jsValue->ToString(vm)->ToString(vm), false, defaultUnit);
        return true;
    }
    if (jsValue->IsObject(vm)) {
        return ParseJsDimensionFromResource(vm, jsValue, defaultUnit, result, resourceObject);
    }
    return false;
}

bool ArkTSUtils::ParseJsDimensionFp(const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result,
    bool isSupportPercent, bool enableCheckInvalidvalue)
{
    return ArkTSUtils::ParseJsDimension(
        vm, jsValue, result, DimensionUnit::FP, isSupportPercent, enableCheckInvalidvalue);
}

bool ArkTSUtils::ParseJsDimensionFp(const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result,
    RefPtr<ResourceObject>& resourceObject, bool isSupportPercent, bool enableCheckInvalidvalue)
{
    return ArkTSUtils::ParseJsDimension(
        vm, jsValue, result, DimensionUnit::FP, resourceObject, isSupportPercent, enableCheckInvalidvalue);
}

bool ArkTSUtils::ParseJsDimensionFpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    bool isSupportPercent)
{
    return ArkTSUtils::ParseJsDimensionNG(vm, jsValue, result, DimensionUnit::FP, isSupportPercent);
}

bool ArkTSUtils::ParseJsDimensionFpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    RefPtr<ResourceObject>& resourceObject, bool isSupportPercent)
{
    return ArkTSUtils::ParseJsDimensionNG(vm, jsValue, result, DimensionUnit::FP, resourceObject, isSupportPercent);
}

bool ArkTSUtils::ParseJsFontFamiliesToString(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsFontFamiliesToString(vm, jsValue, result, resourceObject);
}

bool ArkTSUtils::ParseJsFontFamiliesToString(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& result,
    RefPtr<ResourceObject>& resourceObject)
{
    if (jsValue->IsNull() || jsValue->IsUndefined()) {
        return false;
    }

    if (jsValue->IsString(vm) && jsValue->ToString(vm)->ToString(vm).empty()) {
        return false;
    }

    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(vm, jsValue, fontFamilies, resourceObject)) {
        return false;
    }
    if (fontFamilies.size() > 0) {
        result = "";
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            result += fontFamilies.at(i);
            if (&fontFamilies.at(i) != &fontFamilies.back()) {
                result += ",";
            }
        }
        return true;
    }

    return true;
}

bool ArkTSUtils::ParseJsFontFamilies(
    const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::vector<std::string> &result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsFontFamilies(vm, jsValue, result, resourceObject);
}

bool ArkTSUtils::ParseJsFontFamilies(const EcmaVM *vm, const Local<JSValueRef> &jsValue,
    std::vector<std::string> &result, RefPtr<ResourceObject>& resourceObject)
{
    result.clear();
    if (!jsValue->IsString(vm) && !jsValue->IsObject(vm)) {
        return false;
    }
    if (jsValue->IsString(vm)) {
        result = Framework::ConvertStrToFontFamilies(jsValue->ToString(vm)->ToString(vm));
        return true;
    }
    if (jsValue->IsObject(vm)) {
        auto obj = jsValue->ToObject(vm);
        auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
        if (!resId->IsNumber()) {
            return false;
        }
        return ParseJsFontFamiliesFromResource(vm, jsValue, result, resourceObject);
    }
    return true;
}

bool ArkTSUtils::ParseJsFontFamiliesFromResource(const EcmaVM *vm, const Local<JSValueRef> &jsValue,
    std::vector<std::string> &result, RefPtr<ResourceObject>& resourceObject)
{
    auto jsObj = jsValue->ToObject(vm);
    auto resId = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (!resId->IsNumber()) {
        return false;
    }

    CompleteResourceObject(vm, jsObj);
    resourceObject = GetResourceObject(vm, jsValue);
    auto resourceWrapper = CreateResourceWrapper(vm, jsValue, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->Int32Value(vm);
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsValue)) {
            return false;
        }
        auto args = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        result.emplace_back(resourceWrapper->GetStringByName(param->ToString(vm)->ToString(vm)));
        return true;
    }
    result.emplace_back(resourceWrapper->GetString(resId->Uint32Value(vm)));
    return true;
}

bool ArkTSUtils::ParseJsLengthMetrics(const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result)
{
    RefPtr<ResourceObject> resourceObj;
    return ParseJsLengthMetrics(vm, jsValue, result, resourceObj);
}

bool ArkTSUtils::ParseJsLengthMetrics(const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result,
    RefPtr<ResourceObject>& resourceObj)
{
    if (!jsValue->IsObject(vm)) {
        return false;
    }
    auto jsObj = jsValue->ToObject(vm);
    auto value = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
    if (!value->IsNumber()) {
        return false;
    }
    auto unit = DimensionUnit::VP;
    auto jsUnit = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "unit"));
    if (jsUnit->IsNumber()) {
        unit = static_cast<DimensionUnit>(jsUnit->ToNumber(vm)->Value());
    }
    CalcDimension dimension(value->ToNumber(vm)->Value(), unit);
    result = dimension;
    auto jsRes = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "res"));
    if (SystemProperties::ConfigChangePerform() && !jsRes->IsUndefined() &&
        !jsRes->IsNull() && jsRes->IsObject(vm)) {
        auto jsObjRes = jsRes->ToObject(vm);
        CompleteResourceObject(vm, jsObjRes);
        resourceObj = GetResourceObject(vm, jsObjRes);
    }
    return true;
}

bool ArkTSUtils::ParseJsMedia(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsMedia(vm, jsValue, result, resourceObject);
}

bool ArkTSUtils::ParseJsMedia(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string& result,
    RefPtr<ResourceObject>& resourceObject)
{
    if (!jsValue->IsObject(vm) && !jsValue->IsString(vm)) {
        return false;
    }
    if (jsValue->IsString(vm)) {
        result = jsValue->ToString(vm)->ToString(vm);
        return true;
    }
    if (jsValue->IsObject(vm)) {
        auto obj = jsValue->ToObject(vm);
        CompleteResourceObject(vm, obj);
        auto resId = obj->Get(vm,
            panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::ID)));
        if (!resId->IsNumber()) {
            return false;
        }
        return ParseJsMediaFromResource(vm, jsValue, result, resourceObject);
    }
    return false;
}

bool ArkTSUtils::ParseJsMediaFromResource(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string& result,
    RefPtr<ResourceObject>& resourceObject)
{
    auto jsObj = jsValue->ToObject(vm);
    auto type = jsObj->Get(vm,
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::TYPE)));
    auto resId = jsObj->Get(vm,
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::ID)));
    if (!resId->IsNull() && !type->IsNull() && type->IsNumber() && resId->IsNumber()) {
        resourceObject = GetResourceObject(vm, jsValue);
        auto resourceWrapper = CreateResourceWrapper(vm, jsValue, resourceObject);
        CHECK_NULL_RETURN(resourceWrapper, false);

        if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::RAWFILE)) {
            auto args = jsObj->Get(vm, panda::ExternalStringCache::GetCachedString(vm,
                static_cast<int32_t>(Framework::ArkUIIndex::PARAMS)));
            if (!args->IsArray(vm)) {
                return false;
            }
            Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
            auto fileName = panda::ArrayRef::GetValueAt(vm, params, 0);
            if (!fileName->IsString(vm)) {
                return false;
            }
            result = resourceWrapper->GetRawfile(fileName->ToString(vm)->ToString(vm));
            return true;
        }
        auto resIdNum = resId->Int32Value(vm);
        if (resIdNum == -1) {
            if (!IsGetResourceByName(vm, jsValue)) {
                return false;
            }
            auto args = jsObj->Get(vm, panda::ExternalStringCache::GetCachedString(vm,
                static_cast<int32_t>(Framework::ArkUIIndex::PARAMS)));
            if (!args->IsArray(vm)) {
                return false;
            }
            Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
            auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
            if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::MEDIA)) {
                result = resourceWrapper->GetMediaPathByName(param->ToString(vm)->ToString(vm));
                return true;
            }
            return false;
        }
        if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::MEDIA)) {
            result = resourceWrapper->GetMediaPath(resId->Uint32Value(vm));
            return true;
        }
        return false;
    }
    return false;
}

void ArkTSUtils::GetStringFromJS(const EcmaVM *vm, const Local<JSValueRef> &value, std::string& result)
{
    result = DEFAULT_STR;
    if (!value->IsNull() && value->IsString(vm)) {
        result = value->ToString(vm)->ToString(vm);
    }
    if (value->IsObject(vm)) {
        ParseJsStringFromResource(vm, value, result);
    }
}

bool ArkTSUtils::ParseJsIntegerArray(const EcmaVM* vm, Local<JSValueRef> values, std::vector<uint32_t>& result)
{
    if (!values->IsArray(vm) && !values->IsObject(vm)) {
        return false;
    }

    Local<panda::ArrayRef> valueArray = static_cast<Local<panda::ArrayRef>>(values);
    for (size_t i = 0; i < valueArray->Length(vm); i++) {
        Local<JSValueRef> value = valueArray->GetValueAt(vm, values, i);
        if (value->IsNumber()) {
            result.emplace_back(value->Uint32Value(vm));
        } else if (value->IsObject(vm)) {
            uint32_t singleResInt;
            if (ParseJsInteger(vm, value, singleResInt)) {
                result.emplace_back(singleResInt);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

bool ArkTSUtils::ParseJsString(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsString(vm, jsValue, result, resourceObject);
}

bool ArkTSUtils::ParseJsString(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& result,
    RefPtr<ResourceObject>& resourceObject)
{
    if (!jsValue->IsString(vm) && !jsValue->IsObject(vm)) {
        return false;
    }
    if (jsValue->IsString(vm)) {
        result = jsValue->ToString(vm)->ToString(vm);
        return true;
    }
    if (jsValue->IsObject(vm)) {
        return ArkTSUtils::ParseJsStringFromResource(vm, jsValue, result, resourceObject);
    }
    return false;
}

std::string GetReplaceContentStr(
    const EcmaVM* vm, int32_t pos, const std::string& type, Local<panda::ArrayRef> params, int32_t containCount)
{
    int32_t index = pos + containCount;
    if (index < 0) {
        return std::string();
    }
    auto item = panda::ArrayRef::GetValueAt(vm, params, static_cast<uint32_t>(index));
    if (type == "d") {
        if (item->IsNumber()) {
            return std::to_string(item->Int32Value(vm));
        }
    } else if (type == "s") {
        if (item->IsString(vm)) {
            return item->ToString(vm)->ToString(vm);
        }
    } else if (type == "f") {
        if (item->IsNumber()) {
            return std::to_string(item->ToNumber(vm)->Value());
        }
    }
    return std::string();
}

void ReplaceHolder(const EcmaVM* vm, std::string& originStr, const Local<panda::ArrayRef>& params, int32_t containCount)
{
    auto size = static_cast<int32_t>(params->Length(vm));
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
            if (static_cast<uint32_t>(shortHolderType) ^ static_cast<uint32_t>(pos.length() == 0)) {
                return;
            }
        }

        std::string replaceContentStr;
        if (shortHolderType) {
            replaceContentStr = GetReplaceContentStr(vm, searchTime, type, params, containCount);
        } else {
            replaceContentStr = GetReplaceContentStr(vm, StringUtils::StringToInt(pos) - 1, type, params, containCount);
        }

        originStr.replace(matches[0].first - originStr.begin(), matches[0].length(), replaceContentStr);
        start = originStr.begin() + matches.prefix().length() + replaceContentStr.length();
        end = originStr.end();
        searchTime++;
    }
}

bool FillResultForResIdNumIsNegative(const EcmaVM* vm, const Local<JSValueRef>& type, const Local<JSValueRef>& params,
    std::string& result, const RefPtr<ResourceWrapper>& resourceWrapper)
{
    auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
    if (type->Uint32Value(vm) == static_cast<uint32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetStringByName(param->ToString(vm)->ToString(vm));
        ReplaceHolder(vm, originStr, params, 1);
        result = originStr;
    } else if (type->Uint32Value(vm) == static_cast<uint32_t>(ResourceType::PLURAL)) {
        auto countJsVal = panda::ArrayRef::GetValueAt(vm, params, 1);
        int count = 0;
        if (!countJsVal->IsNumber()) {
            return false;
        }
        count = countJsVal->ToNumber(vm)->Value();
        auto pluralStr = resourceWrapper->GetPluralStringByName(param->ToString(vm)->ToString(vm), count);
        ReplaceHolder(vm, pluralStr, params, REPLACEHOLDER_INDEX);
        result = pluralStr;
    } else {
        return false;
    }
    return true;
}

bool ArkTSUtils::ParseJsStringFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsStringFromResource(vm, jsValue, result, resourceObject);
}

bool ArkTSUtils::ParseJsStringFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& result,
    RefPtr<ResourceObject>& resourceObject)
{
    auto obj = jsValue->ToObject(vm);
    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
    if (!type->IsNumber() || !resId->IsNumber() || !args->IsArray(vm)) {
        return false;
    }

    CompleteResourceObject(vm, obj);
    resourceObject = GetResourceObject(vm, obj);
    auto resourceWrapper = CreateResourceWrapper(vm, obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    auto resIdNum = resourceObject->GetId();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, obj)) {
            return false;
        }
        return FillResultForResIdNumIsNegative(vm, type, params, result, resourceWrapper);
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetString(resId->Uint32Value(vm));
        ReplaceHolder(vm, originStr, params, 0);
        result = originStr;
    } else if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::PLURAL)) {
        auto countJsVal = panda::ArrayRef::GetValueAt(vm, params, 0);
        int count = 0;
        if (!countJsVal->IsNumber()) {
            return false;
        }
        count = countJsVal->ToNumber(vm)->Value();
        auto pluralStr = resourceWrapper->GetPluralString(resId->ToNumber(vm)->Value(), count);
        ReplaceHolder(vm, pluralStr, params, 1);
        result = pluralStr;
    } else if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::FLOAT)) {
        result = std::to_string(resourceWrapper->GetDouble(resId->Uint32Value(vm)));
    } else if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::INTEGER)) {
        result = std::to_string(resourceWrapper->GetInt(resId->Uint32Value(vm)));
    } else {
        return false;
    }
    return true;
}

bool ArkTSUtils::ParseJsResource(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsResource(vm, jsValue, result, resourceObject);
}

bool ArkTSUtils::ParseJsResource(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    RefPtr<ResourceObject>& resourceObject)
{
    if (!jsValue->IsObject(vm)) {
        return false;
    }
    auto jsObj = jsValue->ToObject(vm);
    CompleteResourceObject(vm, jsObj);
    resourceObject = GetResourceObject(vm, jsValue);
    auto resourceWrapper = CreateResourceWrapper(vm, jsValue, resourceObject);
    CHECK_NULL_RETURN(resourceWrapper, false);
    
    auto type = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    auto id = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    uint32_t resourceType = 0;
    if (type->IsNull() || !type->IsNumber() || id->IsNull() || !id->IsNumber()) {
        return false;
    } else {
        resourceType = type->Uint32Value(vm);
    }
    if (resourceType == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(id->Uint32Value(vm));
        return StringUtils::StringToCalcDimensionNG(value, result, false);
    }
    if (resourceType == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(id->Uint32Value(vm)));
        StringUtils::StringToDimensionWithUnitNG(value, result);
        return true;
    }

    if (resourceType == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(id->Uint32Value(vm));
        return true;
    }
    return false;
}

void ArkTSUtils::GetJsMediaBundleInfo(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& bundleName, std::string& moduleName)
{
    if (!jsValue->IsObject(vm) || jsValue->IsString(vm)) {
        return;
    }
    auto jsObj = jsValue->ToObject(vm);
    if (!jsObj->IsUndefined()) {
        auto bundle = jsObj->Get(vm, panda::ExternalStringCache::GetCachedString(vm,
            static_cast<int32_t>(Framework::ArkUIIndex::BUNDLE_NAME)));
        auto module = jsObj->Get(vm, panda::ExternalStringCache::GetCachedString(vm,
            static_cast<int32_t>(Framework::ArkUIIndex::MODULE_NAME)));
        if (bundle->IsString(vm) && module->IsString(vm)) {
            bundleName = bundle->ToString(vm)->ToString(vm);
            moduleName = module->ToString(vm)->ToString(vm);
        }
    }
}

bool ArkTSUtils::ParseJsColorStrategy(
    const EcmaVM* vm, const Local<JSValueRef>& value, ForegroundColorStrategy& strategy)
{
    if (value->IsString(vm)) {
        std::string colorStr = value->ToString(vm)->ToString(vm);
        if (colorStr.compare("invert") == 0) {
            strategy = ForegroundColorStrategy::INVERT;
            return true;
        }
    }
    return false;
}

bool ArkTSUtils::GetJsPasswordIcon(const EcmaVM *vm, const Local<JSValueRef> &jsOnIconSrc,
    const Local<JSValueRef> &jsOffIconSrc, PasswordIcon& result)
{
    result.showResult = "";
    result.hideResult = "";
    result.showBundleName = "";
    result.hideBundleName = "";
    result.showModuleName = "";
    result.hideModuleName = "";

    if (!jsOnIconSrc->IsString(vm) && !jsOnIconSrc->IsObject(vm)
        && !jsOffIconSrc->IsString(vm) && !jsOffIconSrc->IsObject(vm)) {
        return false;
    }

    if (jsOnIconSrc->IsString(vm)) {
        result.showResult = jsOnIconSrc->ToString(vm)->ToString(vm);
    }

    if (jsOnIconSrc->IsObject(vm)) {
        auto obj = jsOnIconSrc->ToObject(vm);
        std::string bundleName;
        std::string moduleName;
        auto bundle = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
        auto module = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
        if (bundle->IsString(vm) && module->IsString(vm)) {
            result.showBundleName = bundle->ToString(vm)->ToString(vm);
            result.showModuleName = module->ToString(vm)->ToString(vm);
        }
        ParseJsMedia(vm, jsOnIconSrc, result.showResult);
    }

    if (jsOffIconSrc->IsString(vm)) {
        result.hideResult = jsOffIconSrc->ToString(vm)->ToString(vm);
    }

    if (jsOffIconSrc->IsObject(vm)) {
        auto obj = jsOffIconSrc->ToObject(vm);
        std::string bundleName;
        std::string moduleName;
        auto bundle = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
        auto module = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
        if (bundle->IsString(vm) && module->IsString(vm)) {
            result.hideBundleName = bundle->ToString(vm)->ToString(vm);
            result.hideModuleName = module->ToString(vm)->ToString(vm);
        }
        ParseJsMedia(vm, jsOffIconSrc, result.hideResult);
    }
    return true;
}

void ArkTSUtils::ParsePadding(
    const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen, ArkUISizeType& result)
{
    if (ArkTSUtils::ParseJsDimensionVp(vm, value, dimen)) {
        if (LessOrEqual(dimen.Value(), 0.0)) {
            dimen.SetValue(0.0);
            dimen.SetUnit(DimensionUnit::VP);
        }
        result.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            result.string = dimen.CalcValue().c_str();
        } else {
            result.value = dimen.Value();
        }
    }
}

void ArkTSUtils::ParsePadding(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen,
                              ArkUISizeType& result, RefPtr<ResourceObject>& resObj)
{
    if (ArkTSUtils::ParseJsDimensionVp(vm, value, dimen, resObj)) {
        if (LessOrEqual(dimen.Value(), 0.0)) {
            dimen.SetValue(0.0);
            dimen.SetUnit(DimensionUnit::VP);
        }
        result.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            result.string = dimen.CalcValue().c_str();
        } else {
            result.value = dimen.Value();
        }
    }
}

panda::Local<panda::ObjectRef> ArkTSUtils::GetContext(EcmaVM* vm)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, panda::JSValueRef::Undefined(vm));
    return NapiValueToLocalValue(frontend->GetContextValue());
}

bool ArkTSUtils::ParseResponseRegion(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, ArkUI_Float32* regionValues,
    int32_t* regionUnits, uint32_t length)
{
    if (jsValue->IsUndefined() || !jsValue->IsArray(vm)) {
        return false;
    }

    Local<panda::ArrayRef> transArray = static_cast<Local<panda::ArrayRef>>(jsValue);
    for (uint32_t i = 0; i < length; i = i + 4) { // 4: dimension length
        Local<JSValueRef> x = transArray->GetValueAt(vm, jsValue, i);
        Local<JSValueRef> y = transArray->GetValueAt(vm, jsValue, i + 1);
        Local<JSValueRef> width = transArray->GetValueAt(vm, jsValue, i + 2); // 2: width value
        Local<JSValueRef> height = transArray->GetValueAt(vm, jsValue, i + 3); // 3: height value
        CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
        CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
        auto s1 = width->ToString(vm)->ToString(vm);
        auto s2 = height->ToString(vm)->ToString(vm);
        if (s1.find('-') != std::string::npos) {
            width = OHOS::Ace::Framework::ToJSValue("100%");
        }
        if (s2.find('-') != std::string::npos) {
            height = OHOS::Ace::Framework::ToJSValue("100%");
        }
        if (!ArkTSUtils::ParseJsDimensionNG(vm, x, xDimen, DimensionUnit::VP)) {
            xDimen = CalcDimension(0.0, DimensionUnit::VP);
        }
        if (!ArkTSUtils::ParseJsDimensionNG(vm, y, yDimen, DimensionUnit::VP)) {
            yDimen = CalcDimension(0.0, DimensionUnit::VP);
        }
        if (!ArkTSUtils::ParseJsDimensionNG(vm, width, widthDimen, DimensionUnit::VP)) {
            widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
        }
        if (!ArkTSUtils::ParseJsDimensionNG(vm, height, heightDimen, DimensionUnit::VP)) {
            heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
        }
        regionValues[i] = static_cast<ArkUI_Float32>(xDimen.Value());
        regionUnits[i] = static_cast<int32_t>(xDimen.Unit());
        regionValues[i + 1] = static_cast<ArkUI_Float32>(yDimen.Value());
        regionUnits[i + 1] = static_cast<int32_t>(yDimen.Unit());
        regionValues[i + 2] = static_cast<ArkUI_Float32>(widthDimen.Value()); // 2: width value
        regionUnits[i + 2] = static_cast<int32_t>(widthDimen.Unit()); // 2: width Unit
        regionValues[i + 3] = static_cast<ArkUI_Float32>(heightDimen.Value()); // 3: height value
        regionUnits[i + 3] = static_cast<int32_t>(heightDimen.Unit()); // 3: height Unit
    }
    return true;
}

uint32_t ArkTSUtils::parseShadowColor(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    RefPtr<ResourceObject> resObj;
    return parseShadowColorWithResObj(vm, jsValue, resObj);
}

uint32_t ArkTSUtils::parseShadowColorWithResObj(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
    RefPtr<ResourceObject>& resObj)
{
    Color color = DEFAULT_TEXT_SHADOW_COLOR;
    if (!ParseJsColorAlpha(vm, jsValue, color, resObj)) {
        color = DEFAULT_TEXT_SHADOW_COLOR;
    }
    return color.GetValue();
};

uint32_t ArkTSUtils::parseShadowFill(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    if (jsValue->IsBoolean()) {
        return static_cast<uint32_t>(jsValue->ToBoolean(vm)->Value());
    }
    return static_cast<uint32_t>(DEFAULT_TEXT_SHADOW_FILL);
};

uint32_t ArkTSUtils::parseShadowType(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    if (jsValue->IsInt()) {
        return jsValue->Uint32Value(vm);
    }
    return static_cast<uint32_t>(DEFAULT_TEXT_SHADOW_TYPE);
};

double ArkTSUtils::parseShadowRadius(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    RefPtr<ResourceObject> resObj;
    return parseShadowRadiusWithResObj(vm, jsValue, resObj);
}

double ArkTSUtils::parseShadowRadiusWithResObj(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
    RefPtr<ResourceObject>& resObj)
{
    double radius = 0.0;
    ArkTSUtils::ParseJsDouble(vm, jsValue, radius, resObj);
    if (LessNotEqual(radius, 0.0)) {
        radius = 0.0;
    }
    return radius;
};

double ArkTSUtils::parseShadowOffset(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    RefPtr<ResourceObject> resObj;
    return parseShadowOffsetWithResObj(vm, jsValue, resObj);
}

double ArkTSUtils::parseShadowOffsetWithResObj(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
    RefPtr<ResourceObject>& resObj)
{
    CalcDimension offset;
    if (ArkTSUtils::ParseJsResource(vm, jsValue, offset, resObj)) {
        return offset.Value();
    } else if (ArkTSUtils::ParseJsDimensionVp(vm, jsValue, offset, resObj)) {
        return offset.Value();
    }
    return 0.0;
};

void ArkTSUtils::ParseOuterBorder(
    EcmaVM* vm, const Local<JSValueRef>& args, std::optional<CalcDimension>& optionalDimension)
{
    RefPtr<ResourceObject> resObj;
    ParseOuterBorder(vm, args, optionalDimension, resObj);
}

void ArkTSUtils::ParseOuterBorder(EcmaVM* vm, const Local<JSValueRef>& args,
    std::optional<CalcDimension>& optionalDimension, RefPtr<ResourceObject>& resObj)
{
    CalcDimension valueDim;
    auto outerBorder = ArkTSUtils::ParseJsDimensionVp(vm, args, valueDim, resObj, false);
    if (!args->IsUndefined() && outerBorder) {
        if (valueDim.IsNegative() || valueDim.Unit() == DimensionUnit::PERCENT) {
            valueDim.Reset();
        }
        optionalDimension = valueDim;
    }
}

void ArkTSUtils::ParseOuterBorderForDashParams(
    EcmaVM* vm, const Local<JSValueRef>& args, std::optional<CalcDimension>& optionalDimension)
{
    RefPtr<ResourceObject> resObj;
    ParseOuterBorderForDashParams(vm, args, optionalDimension, resObj);
}

void ArkTSUtils::ParseOuterBorderForDashParams(EcmaVM* vm, const Local<JSValueRef>& args,
    std::optional<CalcDimension>& optionalDimension, RefPtr<ResourceObject>& resObj)
{
    CalcDimension valueDim;
    if (!args->IsUndefined()) {
        if (ArkTSUtils::ParseJsLengthMetrics(vm, args, valueDim)) {
            if (valueDim.Unit() == DimensionUnit::PERCENT) {
                valueDim.Reset();
            }
            optionalDimension = valueDim;
        } else if (ArkTSUtils::ParseJsDimensionVpNG(vm, args, valueDim, resObj, false)) {
            if (valueDim.IsNegative() || valueDim.Unit() == DimensionUnit::PERCENT) {
                valueDim.Reset();
            }
            optionalDimension = valueDim;
        }
    }
}

void ArkTSUtils::PushOuterBorderDimensionVector(
    const std::optional<CalcDimension>& valueDim, std::vector<ArkUI_Float32>& values, std::vector<ArkUI_Int32>& units)
{
    if (valueDim.has_value()) {
        values.emplace_back(static_cast<ArkUI_Float32>(valueDim.value().Value()));
        units.emplace_back(static_cast<ArkUI_Float32>(valueDim.value().Unit()));
    } else {
        values.emplace_back(0);
        units.emplace_back(0);
    }
}

void ArkTSUtils::ParseJsSymbolFontFamilyName(const EcmaVM *vm, const Local<JSValueRef> &jsValue,
    std::string& customFamilyName)
{
    if (jsValue->IsNull() || jsValue->IsUndefined()) {
        return;
    }
    auto jsObj = jsValue->ToObject(vm);
    CompleteResourceObject(vm, jsObj);
    auto resId = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (resId->IsNull() || !resId->IsNumber()) {
        return;
    }
    auto resourceObject = GetResourceObject(vm, jsValue);
    if (!resourceObject) {
        return;
    }
    std::string bundleName = resourceObject->GetBundleName();
    std::string moduleName = resourceObject->GetModuleName();
    customFamilyName = bundleName + "_" + moduleName + CUSTOM_SYMBOL_SUFFIX;
    std::replace(customFamilyName.begin(), customFamilyName.end(), '.', '_');
}

bool ArkTSUtils::ParseJsSymbolId(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::uint32_t& symbolId)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsSymbolId(vm, jsValue, symbolId, resourceObject);
}

bool ArkTSUtils::ParseJsSymbolId(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::uint32_t& symbolId,
    RefPtr<ResourceObject>& resourceObject)
{
    if (jsValue->IsNull() || jsValue->IsUndefined()) {
        symbolId = 0;
        return false;
    }
    auto jsObj = jsValue->ToObject(vm);
    CompleteResourceObject(vm, jsObj);
    auto resId = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (resId->IsNull() || !resId->IsNumber()) {
        return false;
    }
    resourceObject = GetResourceObject(vm, jsValue);
    if (!resourceObject) {
        return false;
    }
    auto resourceWrapper = CreateResourceWrapper(vm, jsValue, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    auto strValue = resourceWrapper->GetString(resId->Uint32Value(vm));
    if (!strValue.empty()) {
        auto customSymbolId = static_cast<uint32_t>(strtol(strValue.c_str(), nullptr, 16));
        symbolId = customSymbolId;
        return true;
    }
    auto resIdNum = resId->Int32Value(vm);
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsObj)) {
            return false;
        }
        auto args = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        auto symbol = resourceWrapper->GetSymbolByName(param->ToString(vm)->ToString(vm).c_str());
        if (!symbol) {
            return false;
        }
        symbolId = symbol;
        return true;
    }
 
    auto symbol = resourceWrapper->GetSymbolById(resId->Uint32Value(vm));
    if (!symbol) {
        return false;
    }
    symbolId = symbol;
    return true;
}

BorderStyle ArkTSUtils::ConvertBorderStyle(int32_t value)
{
    auto style = static_cast<BorderStyle>(value);
    if (style < BorderStyle::SOLID || style > BorderStyle::NONE) {
        style = BorderStyle::SOLID;
    }
    return style;
}

void ArkTSUtils::PushOuterBorderDimensionVector(const std::optional<CalcDimension>& valueDim,
    std::vector<ArkUI_Float32> &options)
{
    options.push_back(static_cast<ArkUI_Float32>(valueDim.has_value()));
    if (valueDim.has_value()) {
        options.push_back(static_cast<ArkUI_Float32>(valueDim.value().Value()));
        options.push_back(static_cast<ArkUI_Float32>(valueDim.value().Unit()));
    } else {
        options.push_back(0);
        options.push_back(0);
    }
}

void ArkTSUtils::ParseOuterBorderWidth(
    ArkUIRuntimeCallInfo *runtimeCallInfo, EcmaVM *vm, std::vector<ArkUI_Float32> &values)
{
    Local<JSValueRef> leftArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> rightArgs = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> topArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> bottomArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    std::optional<CalcDimension> leftDim;
    std::optional<CalcDimension> rightDim;
    std::optional<CalcDimension> topDim;
    std::optional<CalcDimension> bottomDim;

    ParseOuterBorder(vm, leftArgs, leftDim);
    ParseOuterBorder(vm, rightArgs, rightDim);
    ParseOuterBorder(vm, topArgs, topDim);
    ParseOuterBorder(vm, bottomArgs, bottomDim);

    PushOuterBorderDimensionVector(leftDim, values);
    PushOuterBorderDimensionVector(rightDim, values);
    PushOuterBorderDimensionVector(topDim, values);
    PushOuterBorderDimensionVector(bottomDim, values);
}

void ArkTSUtils::PushOuterBorderColorVector(const std::optional<Color>& valueColor, std::vector<uint32_t> &options)
{
    options.push_back(static_cast<uint32_t>(valueColor.has_value()));
    if (valueColor.has_value()) {
        options.push_back(static_cast<uint32_t>(valueColor.value().GetValue()));
    } else {
        options.push_back(0);
    }
}

void ArkTSUtils::ParseOuterBorderColor(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<uint32_t>& values, int32_t argsIndex)
{
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);

    std::optional<Color> leftColor;
    std::optional<Color> rightColor;
    std::optional<Color> topColor;
    std::optional<Color> bottomColor;

    Color left;
    if (!leftArg->IsUndefined() && ArkTSUtils::ParseJsColorAlpha(vm, leftArg, left)) {
        leftColor = left;
    }
    Color right;
    if (!rightArg->IsUndefined() && ArkTSUtils::ParseJsColorAlpha(vm, rightArg, right)) {
        rightColor = right;
    }
    Color top;
    if (!topArg->IsUndefined() && ArkTSUtils::ParseJsColorAlpha(vm, topArg, top)) {
        topColor = top;
    }
    Color bottom;
    if (!bottomArg->IsUndefined() && ArkTSUtils::ParseJsColorAlpha(vm, bottomArg, bottom)) {
        bottomColor = bottom;
    }

    PushOuterBorderColorVector(leftColor, values);
    PushOuterBorderColorVector(rightColor, values);
    PushOuterBorderColorVector(topColor, values);
    PushOuterBorderColorVector(bottomColor, values);
}

void ArkTSUtils::ParseOuterBorderRadius(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& values, int32_t argsIndex)
{
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);

    std::optional<CalcDimension> topLeftOptional;
    std::optional<CalcDimension> topRightOptional;
    std::optional<CalcDimension> bottomLeftOptional;
    std::optional<CalcDimension> bottomRightOptional;

    ParseOuterBorder(vm, topLeftArgs, topLeftOptional);
    ParseOuterBorder(vm, topRightArgs, topRightOptional);
    ParseOuterBorder(vm, bottomLeftArgs, bottomLeftOptional);
    ParseOuterBorder(vm, bottomRightArgs, bottomRightOptional);

    PushOuterBorderDimensionVector(topLeftOptional, values);
    PushOuterBorderDimensionVector(topRightOptional, values);
    PushOuterBorderDimensionVector(bottomLeftOptional, values);
    PushOuterBorderDimensionVector(bottomRightOptional, values);
}

void ArkTSUtils::SetTextBackgroundStyle(std::shared_ptr<TextBackgroundStyle> style, Color color,
    RefPtr<ResourceObject>& colorResObj, const ArkUI_Float32* values, const ArkUI_Int32* units)
{
    CHECK_NULL_VOID(style);
    if (SystemProperties::ConfigChangePerform() && colorResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, TextBackgroundStyle& textBackgroundStyle) {
            Color color;
            ResourceParseUtils::ParseResColor(colorResObj, color);
            textBackgroundStyle.backgroundColor = color;
        };
        style->AddResource("textBackgroundStyle.color", colorResObj, std::move(updateFunc));
    }
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    borderRadius.radiusTopRight = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    borderRadius.radiusBottomLeft = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    borderRadius.radiusBottomRight = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    style->backgroundColor = Color(color);
    style->backgroundRadius = borderRadius;
    style->backgroundRadius->multiValued = true;
}

void ArkTSUtils::RegisterTextBackgroundStyleResource(std::shared_ptr<TextBackgroundStyle> textBackgroundStyle,
    RefPtr<ResourceObject>& resObjTopLeft, RefPtr<ResourceObject>& resObjTopRight,
    RefPtr<ResourceObject>& resObjBottomLeft, RefPtr<ResourceObject>& resObjBottomRight)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    CHECK_NULL_VOID(textBackgroundStyle);
    if (resObjTopLeft) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObjTopLeft,
            TextBackgroundStyle& textBackgroundStyle) {
            CalcDimension radius;
            ResourceParseUtils::ParseResDimensionVp(resObjTopLeft, radius);
            textBackgroundStyle.backgroundRadius->radiusTopLeft = radius;
            textBackgroundStyle.backgroundRadius->multiValued = true;
        };
        textBackgroundStyle->AddResource("textBackgroundStyle.radiusTopLeft", resObjTopLeft,
            std::move(updateFunc));
    }
    if (resObjTopRight) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObjTopRight,
            TextBackgroundStyle& textBackgroundStyle) {
            CalcDimension radius;
            ResourceParseUtils::ParseResDimensionVp(resObjTopRight, radius);
            textBackgroundStyle.backgroundRadius->radiusTopRight = radius;
            textBackgroundStyle.backgroundRadius->multiValued = true;
        };
        textBackgroundStyle->AddResource("textBackgroundStyle.radiusTopRight", resObjTopRight,
            std::move(updateFunc));
    }
    if (resObjBottomLeft) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObjBottomLeft,
            TextBackgroundStyle& textBackgroundStyle) {
            CalcDimension radius;
            ResourceParseUtils::ParseResDimensionVp(resObjBottomLeft, radius);
            textBackgroundStyle.backgroundRadius->radiusBottomLeft = radius;
            textBackgroundStyle.backgroundRadius->multiValued = true;
        };
        textBackgroundStyle->AddResource("textBackgroundStyle.radiusBottomLeft", resObjBottomLeft,
            std::move(updateFunc));
    }
    if (resObjBottomRight) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObjBottomRight,
            TextBackgroundStyle& textBackgroundStyle) {
            CalcDimension radius;
            ResourceParseUtils::ParseResDimensionVp(resObjBottomRight, radius);
            textBackgroundStyle.backgroundRadius->radiusBottomRight = radius;
            textBackgroundStyle.backgroundRadius->multiValued = true;
        };
        textBackgroundStyle->AddResource("textBackgroundStyle.radiusBottomRight", resObjBottomRight,
            std::move(updateFunc));
    }
}

void ArkTSUtils::ParseOuterBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo,
    EcmaVM* vm, std::vector<ArkUI_Float32>& values, std::vector<ArkUI_Int32>& units, int32_t argsIndex)
{
    std::shared_ptr<TextBackgroundStyle> style = std::make_shared<TextBackgroundStyle>();
    ParseOuterBorderRadius(runtimeCallInfo, vm, values, units, argsIndex, style);
}

void ArkTSUtils::ParseOuterBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo,
    EcmaVM* vm, std::vector<ArkUI_Float32>& values, std::vector<ArkUI_Int32>& units, int32_t argsIndex,
    std::shared_ptr<TextBackgroundStyle> textBackgroundStyle)
{
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);

    std::optional<CalcDimension> topLeftOptional;
    std::optional<CalcDimension> topRightOptional;
    std::optional<CalcDimension> bottomLeftOptional;
    std::optional<CalcDimension> bottomRightOptional;

    RefPtr<ResourceObject> resObjTopLeft;
    RefPtr<ResourceObject> resObjTopRight;
    RefPtr<ResourceObject> resObjBottomLeft;
    RefPtr<ResourceObject> resObjBottomRight;

    ParseOuterBorder(vm, topLeftArgs, topLeftOptional, resObjTopLeft);
    ParseOuterBorder(vm, topRightArgs, topRightOptional, resObjTopRight);
    ParseOuterBorder(vm, bottomLeftArgs, bottomLeftOptional, resObjBottomLeft);
    ParseOuterBorder(vm, bottomRightArgs, bottomRightOptional, resObjBottomRight);

    PushOuterBorderDimensionVector(topLeftOptional, values, units);
    PushOuterBorderDimensionVector(topRightOptional, values, units);
    PushOuterBorderDimensionVector(bottomLeftOptional, values, units);
    PushOuterBorderDimensionVector(bottomRightOptional, values, units);

    RegisterTextBackgroundStyleResource(textBackgroundStyle, resObjTopLeft, resObjTopRight, resObjBottomLeft,
        resObjBottomRight);
}

void ArkTSUtils::PushOuterBorderStyleVector(const std::optional<BorderStyle>& value, std::vector<uint32_t> &options)
{
    options.push_back(static_cast<uint32_t>(value.has_value()));
    if (value.has_value()) {
        options.push_back(static_cast<uint32_t>(value.value()));
    } else {
        options.push_back(NUM_0);
    }
}

void ArkTSUtils::ParseOuterBorderStyle(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<uint32_t>& values, int32_t argsIndex)
{
    std::optional<BorderStyle> styleLeft;
    std::optional<BorderStyle> styleRight;
    std::optional<BorderStyle> styleTop;
    std::optional<BorderStyle> styleBottom;

    auto topArg = runtimeCallInfo->GetCallArgRef(argsIndex);
    auto rightArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    auto bottomArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    auto leftArg = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);

    if (!topArg->IsUndefined() && topArg->IsNumber()) {
        styleTop = ConvertBorderStyle(topArg->Int32Value(vm));
    }
    if (!rightArg->IsUndefined() && rightArg->IsNumber()) {
        styleRight = ConvertBorderStyle(rightArg->Int32Value(vm));
    }
    if (!bottomArg->IsUndefined() && bottomArg->IsNumber()) {
        styleBottom = ConvertBorderStyle(bottomArg->Int32Value(vm));
    }
    if (!leftArg->IsUndefined() && leftArg->IsNumber()) {
        styleLeft = ConvertBorderStyle(leftArg->Int32Value(vm));
    }

    PushOuterBorderStyleVector(styleLeft, values);
    PushOuterBorderStyleVector(styleRight, values);
    PushOuterBorderStyleVector(styleTop, values);
    PushOuterBorderStyleVector(styleBottom, values);
}

void ArkTSUtils::SetBorderWidthArray(const EcmaVM* vm, const Local<JSValueRef>& args, ArkUI_Float32 values[],
    int units[], int index)
{
    CalcDimension borderDimension;
    if (!args->IsUndefined()) {
        if (ArkTSUtils::ParseAllBorder(vm, args, borderDimension)) {
            values[index] = borderDimension.Value();
            units[index] = static_cast<int>(borderDimension.Unit());
        } else {
            values[index] = 0;
            units[index] = static_cast<int>(DimensionUnit::VP);
        }
    } else {
        values[index] = -1;
        units[index] = static_cast<int>(DimensionUnit::INVALID);
    }
}

ArkUISizeType ArkTSUtils::ParseJsToArkUISize(const EcmaVM *vm, const Local<JSValueRef> &arg,
    RefPtr<ResourceObject>& resObj)
{
    ArkUISizeType size = { 0.0, static_cast<int8_t>(DimensionUnit::VP), nullptr };
    CalcDimension dimen(0, DimensionUnit::VP);
    if (ArkTSUtils::ParseJsDimensionVp(vm, arg, dimen, resObj)) {
        size.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            size.string = dimen.CalcValue().c_str();
        } else {
            size.value = dimen.Value();
        }
    }
    return size;
}

bool ArkTSUtils::CheckKeysPressed(
    const EcmaVM* vm, const std::vector<KeyCode>& pressedKeyCodes, std::vector<std::string>& checkKeyCodes)
{
    auto hasKeyCode = [pressedKeyCodes](const KeyCode& keyCode) -> bool {
        auto it = std::find(pressedKeyCodes.begin(), pressedKeyCodes.end(), keyCode);
        return it != pressedKeyCodes.end();
    };
    for (auto& checkKeyCode : checkKeyCodes) {
        if (checkKeyCode == "ctrl") {
            if (!hasKeyCode(KeyCode::KEY_CTRL_LEFT) && !hasKeyCode(KeyCode::KEY_CTRL_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "shift") {
            if (!hasKeyCode(KeyCode::KEY_SHIFT_LEFT) && !hasKeyCode(KeyCode::KEY_SHIFT_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "alt") {
            if (!hasKeyCode(KeyCode::KEY_ALT_LEFT) && !hasKeyCode(KeyCode::KEY_ALT_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "fn") {
            if (!hasKeyCode(KeyCode::KEY_FN)) {
                return false;
            }
        } else {
            ThrowError(vm, "indicate the keys are illegal", ERROR_CODE_PARAM_INVALID);
            return false;
        }
    }
    return true;
}

void ArkTSUtils::ThrowError(const EcmaVM* vm, const std::string& msg, int32_t code)
{
    auto errorVal = panda::Exception::Error(vm, panda::StringRef::NewFromUtf8(vm, msg.c_str()));
    auto codeVal = panda::Exception::Error(vm, panda::StringRef::NewFromUtf8(vm, std::to_string(code).c_str()));
    Local<panda::StringRef> codeKey = panda::StringRef::NewFromUtf8(vm, "code");
    Local<panda::ObjectRef> errorObj(errorVal);
    errorObj->Set(vm, codeKey, codeVal);
    panda::JSNApi::ThrowException(vm, errorObj);
}

Local<JSValueRef> ArkTSUtils::GetModifierKeyState(
    ArkUIRuntimeCallInfo* info, const std::vector<KeyCode>& pressedKeyCodes)
{
    auto vm = info->GetVM();
    auto param = info->GetCallArgRef(0);
    if (!param->IsArray(vm)) {
        ThrowError(vm, "indicate the keys are illegal", ERROR_CODE_PARAM_INVALID);
        return JSValueRef::Undefined(vm);
    }
    std::vector<std::string> checkKeyCodes;
    std::vector<std::string> validKeyCodes = { "ctrl", "shift", "alt", "fn" };
    auto paramArray = panda::Local<panda::ArrayRef>(param);
    auto length = paramArray->Length(vm);
    for (size_t i = 0; i < length; i++) {
        auto value = panda::ArrayRef::GetValueAt(vm, paramArray, i);
        auto code = value->ToString(vm)->ToString(vm);
        std::transform(code.begin(), code.end(), code.begin(), [](char& c) { return std::tolower(c); });
        auto it = std::find(validKeyCodes.begin(), validKeyCodes.end(), code.c_str());
        if (it == validKeyCodes.end()) {
            ThrowError(vm, "indicate the keys are illegal", ERROR_CODE_PARAM_INVALID);
            return JSValueRef::Undefined(info->GetVM());
        } else {
            checkKeyCodes.emplace_back(code);
        }
    }
    if (checkKeyCodes.empty()) {
        ThrowError(vm, "indicate the keys are illegal", ERROR_CODE_PARAM_INVALID);
        return JSValueRef::Undefined(vm);
    }
    if (ArkTSUtils::CheckKeysPressed(vm, pressedKeyCodes, checkKeyCodes)) {
        return panda::BooleanRef::New(vm, true);
    } else {
        return panda::BooleanRef::New(vm, false);
    }
}

Local<JSValueRef> ArkTSUtils::JsGetModifierKeyState(ArkUIRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo = static_cast<BaseEventInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(
        info->GetVM(), 0));
    if (!eventInfo) {
        return JSValueRef::Undefined(info->GetVM());
    }
    auto pressedKeyCodes = eventInfo->GetPressedKeyCodes();
    return ArkTSUtils::GetModifierKeyState(info, pressedKeyCodes);
}

Local<JSValueRef> ArkTSUtils::JsGetHorizontalAxisValue(ArkUIRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo =
        static_cast<AxisInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(info->GetVM(), 0));
    if (!eventInfo) {
        return JSValueRef::Undefined(info->GetVM());
    }
    return panda::NumberRef::New(info->GetVM(), eventInfo->GetHorizontalAxis());
}

Local<JSValueRef> ArkTSUtils::JsGetVerticalAxisValue(ArkUIRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo =
        static_cast<AxisInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(info->GetVM(), 0));
    if (!eventInfo) {
        return JSValueRef::Undefined(info->GetVM());
    }
    return panda::NumberRef::New(info->GetVM(), eventInfo->GetVerticalAxis());
}

bool ArkTSUtils::IsDrawable(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    if (!jsValue->IsObject(vm)) {
        return false;
    }
    auto jsObj = jsValue->ToObject(vm);
    if (jsObj->IsUndefined()) {
        return false;
    }

    // if jsObject has function getPixelMap, it's a DrawableDescriptor object
    auto func = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "getPixelMap"));
    return (!func->IsNull() && func->IsFunction(vm));
}

RefPtr<PixelMap> ArkTSUtils::GetDrawablePixmap(const EcmaVM* vm, Local<JSValueRef> obj)
{
    return PixelMap::GetFromDrawable(UnwrapNapiValue(vm, obj));
}

Rosen::BrightnessBlender* ArkTSUtils::CreateRSBrightnessBlenderFromNapiValue(const EcmaVM* vm, Local<JSValueRef> obj)
{
    auto blenderPtr = static_cast<Rosen::BrightnessBlender*>(UnwrapNapiValue(vm, obj));
    return blenderPtr;
}

void* ArkTSUtils::UnwrapNapiValue(const EcmaVM* vm, const Local<JSValueRef>& obj)
{
    if (!obj->IsObject(vm)) {
        LOGE("info is not an object when try CreateFromNapiValue");
        return nullptr;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    auto nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);
    JSValueWrapper valueWrapper = obj;

    Framework::ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value napiValue = nativeEngine->ValueToNapiValue(valueWrapper);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, napiValue, &valueType);
    if (valueType != napi_object) {
        LOGE("napiValue is not napi_object");
        return nullptr;
    }
    void* objectNapi = nullptr;
    napi_unwrap(env, napiValue, &objectNapi);
    return objectNapi;
}

#if !defined(PREVIEW)
RefPtr<PixelMap> ArkTSUtils::CreatePixelMapFromNapiValue(const EcmaVM* vm, Local<JSValueRef> obj)
{
    if (!obj->IsObject(vm)) {
        return nullptr;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    if (!engine) {
        return nullptr;
    }
    auto* nativeEngine = engine->GetNativeEngine();
    if (nativeEngine == nullptr) {
        return nullptr;
    }
    JSValueWrapper valueWrapper = obj;

    Framework::ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value napiValue = nativeEngine->ValueToNapiValue(valueWrapper);

    Framework::PixelMapNapiEntry pixelMapNapiEntry = Framework::JsEngine::GetPixelMapNapiEntry();
    if (!pixelMapNapiEntry) {
        return nullptr;
    }

    void* pixmapPtrAddr = pixelMapNapiEntry(reinterpret_cast<napi_env>(nativeEngine), napiValue);
    if (pixmapPtrAddr == nullptr) {
        return nullptr;
    }
    return PixelMap::CreatePixelMap(pixmapPtrAddr);
}
#endif

bool ArkTSUtils::ParseSelectionMenuOptions(ArkUIRuntimeCallInfo* info, const EcmaVM* vm,
    NG::OnCreateMenuCallback& onCreateMenuCallback, NG::OnMenuItemClickCallback& onMenuItemClickCallback,
    NG::OnPrepareMenuCallback& onPrepareMenuCallback)
{
    Local<JSValueRef> firstArg = info->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = info->GetCallArgRef(NUM_1);
    if (!secondArg->IsObject(vm) || secondArg->IsUndefined()) {
        return false;
    }
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, false);
    auto menuOptionsObject = secondArg->ToObject(vm);
    auto jsValueOnCreateMenu = menuOptionsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "onCreateMenu"));
    ParseOnCreateMenu(vm, frameNode, jsValueOnCreateMenu, onCreateMenuCallback);
    auto jsValueOnMenuItemClick = menuOptionsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "onMenuItemClick"));
    ParseOnMenuItemClick(vm, frameNode, jsValueOnMenuItemClick, onMenuItemClickCallback);
    auto jsValueOnPrepareMenu = menuOptionsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "onPrepareMenu"));
    ParseOnPrepareMenu(vm, frameNode, jsValueOnPrepareMenu, onPrepareMenuCallback);
    return true;
}

Local<panda::ArrayRef> ArkTSUtils::CreateJsSystemMenuItems(
    const EcmaVM* vm, const std::vector<NG::MenuItemParam>& systemMenuItems)
{
    Local<panda::ArrayRef> systemMenuItemsArray = panda::ArrayRef::New(vm);
    uint32_t idx = 0;
    for (const auto& item : systemMenuItems) {
        systemMenuItemsArray->SetValueAt(vm, systemMenuItemsArray, idx++, CreateJsTextMenuItem(vm, item));
    }
    return systemMenuItemsArray;
}

Local<panda::ObjectRef> ArkTSUtils::CreateJsTextMenuItem(const EcmaVM* vm, const NG::MenuItemParam& menuItemParam)
{
    Local<panda::ObjectRef> obj = CreateJsTextMenuId(vm, menuItemParam.menuOptionsParam.id);
    const char* keys[] = { "content", "id", "labelInfo", "icon" };
    auto hasSymbol =
        menuItemParam.menuOptionsParam.symbolId.has_value() && menuItemParam.menuOptionsParam.symbolId.value() != 0;
    auto contentRef = panda::StringRef::NewFromUtf8(vm, menuItemParam.menuOptionsParam.content.value_or("").c_str());
    auto labelRef = panda::StringRef::NewFromUtf8(vm, menuItemParam.menuOptionsParam.labelInfo.value_or("").c_str());
    if (hasSymbol) {
        Local<JSValueRef> values[] = { contentRef, obj, labelRef,
            panda::NumberRef::New(vm, menuItemParam.menuOptionsParam.symbolId.value()) };
        return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    }
    Local<JSValueRef> values[] = { contentRef, obj, labelRef,
        panda::StringRef::NewFromUtf8(vm, menuItemParam.menuOptionsParam.icon.value_or("").c_str()) };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
}

Local<panda::ObjectRef> ArkTSUtils::CreateJsTextMenuId(const EcmaVM* vm, const std::string& id)
{
    Local<panda::ObjectRef> empty = panda::ObjectRef::New(vm);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, empty);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, empty);
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    napi_value global = nullptr;
    napi_status ret = napi_get_global(env, &global);
    if (ret != napi_ok) {
        return empty;
    }
    napi_value constructor = nullptr;
    ret = napi_get_named_property(env, global, JS_TEXT_MENU_ID_CLASS_NAME, &constructor);
    if (ret != napi_ok) {
        return empty;
    }

    napi_value obj = nullptr;
    napi_value menuId = nullptr;

    ret = napi_create_string_utf8(env, id.c_str(), id.length(), &menuId);
    if (ret != napi_ok) {
        return empty;
    }
    ret = napi_new_instance(env, constructor, NUM_1, &menuId, &obj);
    if (ret != napi_ok) {
        return empty;
    }

    auto value = Framework::JsConverter::ConvertNapiValueToJsVal(obj);
    if (!value->IsObject()) {
        return empty;
    }

    return value->GetLocalHandle();
}

void ArkTSUtils::ParseOnCreateMenu(const EcmaVM* vm, FrameNode* frameNode, const Local<JSValueRef>& jsValueOnCreateMenu,
    NG::OnCreateMenuCallback& onCreateMenuCallback)
{
    if (jsValueOnCreateMenu.IsEmpty() || !jsValueOnCreateMenu->IsFunction(vm)) {
        return;
    }
    panda::Local<panda::FunctionRef> func = jsValueOnCreateMenu->ToObject(vm);
    auto containerId = Container::CurrentId();
    auto jsCallback = [vm, node = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func), containerId](
                          const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
        ContainerScope scope(containerId);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        std::vector<NG::MenuOptionsParam> menuParams;
        auto textMenuItemArrayObj = CreateJsSystemMenuItems(vm, systemMenuItems);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { textMenuItemArrayObj };
        auto menuItems = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (!menuItems->IsArray(vm)) {
            return menuParams;
        }
        WrapMenuParams(vm, menuParams, menuItems, false);
        return menuParams;
    };
    onCreateMenuCallback = jsCallback;
}

void ArkTSUtils::ParseOnPrepareMenu(const EcmaVM* vm, FrameNode* frameNode,
    const Local<JSValueRef>& jsValueOnPrepareMenu, NG::OnPrepareMenuCallback& onPrepareMenuCallback)
{
    if (jsValueOnPrepareMenu.IsEmpty() || !jsValueOnPrepareMenu->IsFunction(vm)) {
        return;
    }
    panda::Local<panda::FunctionRef> func = jsValueOnPrepareMenu->ToObject(vm);
    auto containerId = Container::CurrentId();
    auto jsCallback = [vm, node = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func), containerId](
                          const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
        ContainerScope scope(containerId);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        std::vector<NG::MenuOptionsParam> menuParams;
        auto textMenuItemArrayObj = CreateJsSystemMenuItems(vm, systemMenuItems);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { textMenuItemArrayObj };
        auto menuItems = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (!menuItems->IsArray(vm)) {
            return menuParams;
        }
        WrapMenuParams(vm, menuParams, menuItems, true);
        return menuParams;
    };
    onPrepareMenuCallback = jsCallback;
}

void ArkTSUtils::WrapMenuParams(const EcmaVM* vm, std::vector<NG::MenuOptionsParam>& menuParams,
    const Local<JSValueRef>& menuItems, bool enableLabelInfo)
{
    auto menuItemsArray = Local<panda::ArrayRef>(menuItems);
    auto length = menuItemsArray->Length(vm);
    for (uint32_t index = 0; index < length; index++) {
        Local<JSValueRef> menuItem = panda::ArrayRef::GetValueAt(vm, menuItemsArray, index);
        if (!menuItem->IsObject(vm)) {
            continue;
        }
        auto menuItemObject = menuItem->ToObject(vm);
        NG::MenuOptionsParam menuOptionsParam;
        auto jsContent = menuItemObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "content"));
        std::string content;
        ParseJsString(vm, jsContent, content);
        menuOptionsParam.content = content;
        auto jsStartIcon = menuItemObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "icon"));
        std::string icon;
        ParseJsMedia(vm, jsStartIcon, icon);
        menuOptionsParam.icon = icon;
        auto jsTextMenuId = menuItemObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
        std::string id;
        if (jsTextMenuId->IsObject(vm)) {
            auto textMenuIdObject = jsTextMenuId->ToObject(vm);
            auto jsId = textMenuIdObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
            ParseJsString(vm, jsId, id);
        }
        menuOptionsParam.id = id;
        if (enableLabelInfo) {
            auto jsLabelInfo = menuItemObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "labelInfo"));
            std::string labelInfo;
            ParseJsString(vm, jsLabelInfo, labelInfo);
            menuOptionsParam.labelInfo = labelInfo;
        }
        menuParams.emplace_back(menuOptionsParam);
    }
}

void ArkTSUtils::ParseOnMenuItemClick(const EcmaVM* vm, FrameNode* frameNode,
    const Local<JSValueRef>& jsValueOnMenuItemClick, NG::OnMenuItemClickCallback& onMenuItemClickCallback)
{
    if (jsValueOnMenuItemClick.IsEmpty() || !jsValueOnMenuItemClick->IsFunction(vm)) {
        return;
    }
    panda::Local<panda::FunctionRef> func = jsValueOnMenuItemClick->ToObject(vm);
    auto containerId = Container::CurrentId();
    auto jsCallback = [vm, node = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func), containerId](
                          const NG::MenuItemParam& menuOptionsParam) -> bool {
        ContainerScope scope(containerId);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        auto paramArrayObj = CreateJsOnMenuItemClick(vm, menuOptionsParam);
        if (paramArrayObj->Length(vm) != PARAM_ARR_LENGTH_2) {
            return false;
        }
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
            panda::ArrayRef::GetValueAt(vm, paramArrayObj, 0), panda::ArrayRef::GetValueAt(vm, paramArrayObj, 1)
        };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return false;
    };
    onMenuItemClickCallback = jsCallback;
}

Local<panda::ArrayRef> ArkTSUtils::CreateJsOnMenuItemClick(const EcmaVM* vm, const NG::MenuItemParam& menuItemParam)
{
    Local<panda::ArrayRef> paramsArray = panda::ArrayRef::New(vm);
    paramsArray->SetValueAt(vm, paramsArray, 0, CreateJsTextMenuItem(vm, menuItemParam));
    paramsArray->SetValueAt(vm, paramsArray, 1, CreateJsTextRange(vm, menuItemParam));
    return paramsArray;
}

Local<panda::ObjectRef> ArkTSUtils::CreateJsTextRange(const EcmaVM* vm, const NG::MenuItemParam& menuItemParam)
{
    const char* keys[] = { "start", "end" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, menuItemParam.start),
        panda::NumberRef::New(vm, menuItemParam.end) };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
}

Local<panda::ArrayRef> ArkTSUtils::ChoosePointToJSValue(const EcmaVM* vm, std::vector<int> input)
{
    Local<panda::ArrayRef> arr = panda::ArrayRef::New(vm);
    for (size_t i = 0; i < input.size(); i++) {
        arr->SetValueAt(vm, arr, i, ToJSValueWithVM(vm, input[i]));
    }
    return arr;
}

void ArkTSUtils::ParseJsAngle(const EcmaVM *vm, const Local<JSValueRef> &value, std::optional<float> &angle)
{
    if (value->IsNumber()) {
        angle = static_cast<float>(value->ToNumber(vm)->Value());
        return;
    }
    if (value->IsString(vm)) {
        angle = static_cast<float>(StringUtils::StringToDegree(value->ToString(vm)->ToString(vm)));
        return;
    }
    return;
}

bool ArkTSUtils::ParseJsInt32(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result)
{
    if (value->IsNumber()) {
        result = value->Int32Value(vm);
        return true;
    }
    if (value->IsString(vm)) {
        result = StringUtils::StringToInt(value->ToString(vm)->ToString(vm));
        return true;
    }

    return false;
}

void ArkTSUtils::ParseGradientCenter(
    const EcmaVM* vm, const Local<JSValueRef>& value, std::vector<ArkUIInt32orFloat32>& values)
{
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    ArkTSUtils::ParseGradientCenter(vm, value, values, vectorResObj);
}

void ArkTSUtils::ParseGradientCenter(const EcmaVM* vm, const Local<JSValueRef>& value,
    std::vector<ArkUIInt32orFloat32>& values, std::vector<RefPtr<ResourceObject>>& vectorResObj)
{
    bool hasValueX = false;
    bool hasValueY = false;
    CalcDimension valueX;
    CalcDimension valueY;
    if (value->IsArray(vm)) {
        auto array = panda::Local<panda::ArrayRef>(value);
        auto length = array->Length(vm);
        if (length == NUM_2) {
            RefPtr<ResourceObject> xResObj;
            RefPtr<ResourceObject> yResObj;
            hasValueX =
                ArkTSUtils::ParseJsDimensionVp(vm, panda::ArrayRef::GetValueAt(vm, array, NUM_0), valueX,
                xResObj, false);
            hasValueY =
                ArkTSUtils::ParseJsDimensionVp(vm, panda::ArrayRef::GetValueAt(vm, array, NUM_1), valueY,
                yResObj, false);
            if (xResObj) {
                vectorResObj.push_back(xResObj);
            } else {
                vectorResObj.push_back(nullptr);
            }
            if (yResObj) {
                vectorResObj.push_back(yResObj);
            } else {
                vectorResObj.push_back(nullptr);
            }
        }
    }
    values.push_back({.i32 = static_cast<ArkUI_Int32>(hasValueX)});
    values.push_back({.f32 = static_cast<ArkUI_Float32>(valueX.Value())});
    values.push_back({.i32 = static_cast<ArkUI_Int32>(valueX.Unit())});
    values.push_back({.i32 = static_cast<ArkUI_Int32>(hasValueY)});
    values.push_back({.f32 = static_cast<ArkUI_Float32>(valueY.Value())});
    values.push_back({.i32 = static_cast<ArkUI_Int32>(valueY.Unit())});
}

void ArkTSUtils::ParseGradientColorStops(const EcmaVM *vm, const Local<JSValueRef>& value,
    std::vector<ArkUIInt32orFloat32>& colors, std::vector<RefPtr<ResourceObject>>& vectorResObj)
{
    if (!value->IsArray(vm)) {
        return;
    }
    auto array = panda::Local<panda::ArrayRef>(value);
    auto length = array->Length(vm);
    for (uint32_t index = 0; index < length; index++) {
        auto item = panda::ArrayRef::GetValueAt(vm, array, index);
        if (!item->IsArray(vm)) {
            continue;
        }
        auto itemArray = panda::Local<panda::ArrayRef>(item);
        auto itemLength = itemArray->Length(vm);
        if (itemLength < NUM_1) {
            continue;
        }
        Color color;
        auto colorParams = panda::ArrayRef::GetValueAt(vm, itemArray, NUM_0);
        RefPtr<ResourceObject> resObj;
        if (!ArkTSUtils::ParseJsColorAlpha(vm, colorParams, color, resObj)) {
            continue;
        }
        if (SystemProperties::ConfigChangePerform()) {
            if (resObj) {
                vectorResObj.push_back(resObj);
            } else {
                vectorResObj.push_back(nullptr);
            }
        }
        bool hasDimension = false;
        double dimension = 0.0;
        if (itemLength > NUM_1) {
            auto stopDimension = panda::ArrayRef::GetValueAt(vm, itemArray, NUM_1);
            if (ArkTSUtils::ParseJsDouble(vm, stopDimension, dimension)) {
                hasDimension = true;
            }
        }
        colors.push_back({.u32 = static_cast<ArkUI_Uint32>(color.GetValue())});
        colors.push_back({.i32 = static_cast<ArkUI_Int32>(hasDimension)});
        colors.push_back({.f32 = static_cast<ArkUI_Float32>(dimension)});
    }
}

void ArkTSUtils::ParseGradientColorStops(
    const EcmaVM* vm, const Local<JSValueRef>& value, std::vector<ArkUIInt32orFloat32>& colors)
{
    std::vector<RefPtr<ResourceObject>> vectorResObj;
    ArkTSUtils::ParseGradientColorStops(vm, value, colors, vectorResObj);
}

void ArkTSUtils::ParseGradientAngle(
    const EcmaVM* vm, const Local<JSValueRef>& value, std::vector<ArkUIInt32orFloat32>& values)
{
    std::optional<float> degree;
    ParseJsAngle(vm, value, degree);
    auto angleHasValue = degree.has_value();
    auto angleValue = angleHasValue ? degree.value() : 0.0f;
    degree.reset();
    values.push_back({ .i32 = static_cast<ArkUI_Int32>(angleHasValue) });
    values.push_back({ .f32 = static_cast<ArkUI_Float32>(angleValue) });
}

bool ArkTSUtils::ParseMargin(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUISizeType& top, ArkUISizeType& right,
    ArkUISizeType& bottom, ArkUISizeType& left)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, false);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    CalcDimension topDimen(0, DimensionUnit::VP);
    CalcDimension rightDimen(0, DimensionUnit::VP);
    CalcDimension bottomDimen(0, DimensionUnit::VP);
    CalcDimension leftDimen(0, DimensionUnit::VP);
    bool isLengthMetrics = false;
    if (secondArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedMargin(vm, secondArg, topDimen, top);
    }
    if (thirdArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedMargin(vm, thirdArg, rightDimen, right);
    }
    if (forthArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedMargin(vm, forthArg, bottomDimen, bottom);
    }
    if (fifthArg->IsObject(vm)) {
        isLengthMetrics |= ParseLocalizedMargin(vm, fifthArg, leftDimen, left);
    }
    if (isLengthMetrics) {
        return true;
    }
    ParseNormalMargin(vm, secondArg, topDimen, top);
    ParseNormalMargin(vm, thirdArg, rightDimen, right);
    ParseNormalMargin(vm, forthArg, bottomDimen, bottom);
    ParseNormalMargin(vm, fifthArg, leftDimen, left);
    return false;
}
} // namespace OHOS::Ace::NG
