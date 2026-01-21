/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "ark_native_engine.h"
#include "arkts_utils.h"
#include "ecmascript/napi/include/jsnapi.h"
#include "jsnapi_expo.h"
#include "native_engine.h"
#include "ui/base/utils/utils.h"

#include "base/utils/utils.h"
#include "base/i18n/localization.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "frameworks/base/image/pixel_map.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "frameworks/core/common/card_scope.h"
#include "frameworks/core/common/resource/resource_configuration.h"
#include "frameworks/core/common/resource/resource_parse_utils.h"
#include "frameworks/core/components/text_overlay/text_overlay_theme.h"
#include "frameworks/core/components/theme/shadow_theme.h"

using namespace OHOS::Ace::Framework;
namespace OHOS::Ace::NG {
namespace {
const char TOP_PROPERTY[] = "top";
const char RIGHT_PROPERTY[] = "right";
const char BOTTOM_PROPERTY[] = "bottom";
const char LEFT_PROPERTY[] = "left";
const char END_PROPERTY[] = "end";
const char START_PROPERTY[] = "start";
const char TOP_START_PROPERTY[] = "topStart";
const char TOP_END_PROPERTY[] = "topEnd";
const char BOTTOM_START_PROPERTY[] = "bottomStart";
const char BOTTOM_END_PROPERTY[] = "bottomEnd";

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

enum class MenuItemType {
    COPY,
    PASTE,
    CUT,
    SELECT_ALL,
    AUTO_FILL,
    PASSWORD_VAULT,
    UNKNOWN,
    CAMERA_INPUT,
    AI_WRITER,
    TRANSLATE,
    SHARE,
    SEARCH,
    ASK_CELIA,
    AI_MENU_OPTION
};

MenuItemType StringToMenuItemType(std::string_view id)
{
    static const std::unordered_map<std::string_view, MenuItemType> keyMenuItemMap = {
        { "OH_DEFAULT_COPY", MenuItemType::COPY },
        { "OH_DEFAULT_PASTE", MenuItemType::PASTE },
        { "OH_DEFAULT_CUT", MenuItemType::CUT },
        { "OH_DEFAULT_SELECT_ALL", MenuItemType::SELECT_ALL },
        { "OH_DEFAULT_AUTO_FILL", MenuItemType::AUTO_FILL },
        { "OH_DEFAULT_PASSWORD_VAULT", MenuItemType::PASSWORD_VAULT },
        { "OH_DEFAULT_CAMERA_INPUT", MenuItemType::CAMERA_INPUT },
        { "OH_DEFAULT_AI_WRITE", MenuItemType::AI_WRITER },
        { "OH_DEFAULT_TRANSLATE", MenuItemType::TRANSLATE },
        { "OH_DEFAULT_SHARE", MenuItemType::SHARE },
        { "OH_DEFAULT_SEARCH", MenuItemType::SEARCH },
        { "OH_DEFAULT_ASK_CELIA", MenuItemType::ASK_CELIA },
        { "OH_DEFAULT_AI_MENU_PHONE", MenuItemType::AI_MENU_OPTION },
        { "OH_DEFAULT_AI_MENU_URL", MenuItemType::AI_MENU_OPTION },
        { "OH_DEFAULT_AI_MENU_EMAIL", MenuItemType::AI_MENU_OPTION },
        { "OH_DEFAULT_AI_MENU_ADDRESS", MenuItemType::AI_MENU_OPTION },
        { "OH_DEFAULT_AI_MENU_DATETIME", MenuItemType::AI_MENU_OPTION }
    };

    auto item = keyMenuItemMap.find(id);
    return item != keyMenuItemMap.end() ? item->second : MenuItemType::UNKNOWN;
}

void UpdateSubMenuItemsInfo(std::vector<NG::MenuOptionsParam>& subMenuOptionsParam)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    for (auto& subMenuItem : subMenuOptionsParam) {
        auto opType = StringToMenuItemType(subMenuItem.id);
        switch (opType) {
            case MenuItemType::PASSWORD_VAULT:
                subMenuItem.symbolId = theme->GetPasswordVaultSymbolId();
                break;
            default:
                subMenuItem.labelInfo = subMenuItem.labelInfo.value_or("");
                subMenuItem.symbolId = subMenuItem.symbolId.value_or(0);
                break;
        }
    }
}

void UpdateInfoById(NG::MenuOptionsParam& menuOptionsParam, std::string_view id)
{
    auto opType = StringToMenuItemType(id);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    switch (opType) {
        case MenuItemType::COPY:
            menuOptionsParam.labelInfo = theme->GetCopyLabelInfo();
            menuOptionsParam.symbolId = theme->GetCopySymbolId();
            break;
        case MenuItemType::PASTE:
            menuOptionsParam.labelInfo = theme->GetPasteLabelInfo();
            menuOptionsParam.symbolId = theme->GetPasteSymbolId();
            break;
        case MenuItemType::CUT:
            menuOptionsParam.labelInfo = theme->GetCutLabelInfo();
            menuOptionsParam.symbolId = theme->GetCutSymbolId();
            break;
        case MenuItemType::SELECT_ALL:
            menuOptionsParam.labelInfo = theme->GetSelectAllLabelInfo();
            menuOptionsParam.symbolId = theme->GetCopyAllSymbolId();
            break;
        case MenuItemType::AUTO_FILL:
            menuOptionsParam.symbolId = theme->GetAutoFillSymbolId();
            UpdateSubMenuItemsInfo(menuOptionsParam.subMenuItems);
            break;
        case MenuItemType::CAMERA_INPUT:
            menuOptionsParam.symbolId = theme->GetCameraInputSymbolId();
            break;
        case MenuItemType::AI_WRITER:
            menuOptionsParam.symbolId = theme->GetAIWriteSymbolId();
            break;
        case MenuItemType::TRANSLATE:
            menuOptionsParam.symbolId = theme->GetTranslateSymbolId();
            break;
        case MenuItemType::SHARE:
            menuOptionsParam.symbolId = theme->GetShareSymbolId();
            break;
        case MenuItemType::SEARCH:
            menuOptionsParam.symbolId = theme->GetSearchSymbolId();
            break;
        case MenuItemType::ASK_CELIA:
            menuOptionsParam.symbolId = theme->GetAskCeliaSymbolId();
            break;
        case MenuItemType::AI_MENU_OPTION:
            menuOptionsParam.symbolId = theme->GetAIMenuSymbolId();
            break;
        default:
            menuOptionsParam.labelInfo = menuOptionsParam.labelInfo.value_or("");
            menuOptionsParam.symbolId = menuOptionsParam.symbolId.value_or(0);
            break;
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
constexpr int32_t FLOAT_PRECISION = 6;
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

NodeInfo ArkTSUtils::MakeNativeNodeInfo(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    if (!frameNode) {
        return { "", ColorMode::COLOR_MODE_UNDEFINED };
    }
    return { frameNode ? frameNode->GetTag() : "",
        frameNode ? frameNode->GetLocalColorMode() : ColorMode::COLOR_MODE_UNDEFINED };
}

bool ArkTSUtils::CheckDarkResource(const RefPtr<ResourceObject>& resObj)
{
    if (!SystemProperties::GetResourceDecoupling() || !resObj) {
        return false;
    }
    auto resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resObj);
    CHECK_NULL_RETURN(resourceAdapter, false);

    int32_t resId = resObj->GetId();
    bool hasDarkRes = false;
    auto params = resObj->GetParams();
    if (resId == -1 && !params.empty() && params.back().value.has_value()) {
        std::vector<std::string> splitter;
        StringUtils::StringSplitter(params.back().value.value(), '.', splitter);
        hasDarkRes = resourceAdapter->ExistDarkResByName(splitter.back(),
            std::to_string(resObj->GetType()));
    } else {
        hasDarkRes = resourceAdapter->ExistDarkResById(std::to_string(resId));
    }
    return hasDarkRes;
}

void ArkTSUtils::CompleteResourceObjectFromColor(RefPtr<ResourceObject>& resObj,
    Color& color, bool state, const NodeInfo& nodeInfo)
{
    if (!state || !SystemProperties::ConfigChangePerform()) {
        return;
    }

    auto instanceId = Container::CurrentIdSafely();
    auto invertFunc = ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeInfo.nodeTag);
    CHECK_NULL_VOID(invertFunc);

    if (nodeInfo.localColorMode == ColorMode::LIGHT) {
        resObj = nullptr;
        return;
    }
    bool hasDarkRes = CheckDarkResource(resObj);
    if (nodeInfo.localColorMode == ColorMode::DARK) {
        if (!hasDarkRes) {
            color = Color(invertFunc(color.GetValue()));
        }
        resObj = nullptr;
        return;
    }
    auto colorMode = Container::CurrentColorMode();
    Color curColor = color;
    if ((colorMode == ColorMode::DARK) && !hasDarkRes) {
        color = Color(invertFunc(color.GetValue()));
    }
    if (!resObj) {
        resObj = AceType::MakeRefPtr<ResourceObject>();
        resObj->SetIsResource(false);
        resObj->SetInstanceId(instanceId);
    }
    resObj->SetNodeTag(nodeInfo.nodeTag);
    resObj->SetColorMode(colorMode);
    resObj->SetHasDarkRes(hasDarkRes);
    resObj->SetColor((colorMode == ColorMode::DARK) ? curColor : color);
}

void ArkTSUtils::CompleteResourceObjectFromColor(RefPtr<ResourceObject>& resObj, Color& color, bool state)
{
    if (!state || !SystemProperties::ConfigChangePerform()) {
        return;
    }

    auto node = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(node);

    auto instanceId = Container::CurrentIdSafely();
    auto nodeTag = node->GetTag();
    auto invertFunc = ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeTag);
    CHECK_NULL_VOID(invertFunc);

    auto localColorMode = node->GetLocalColorMode();
    if (localColorMode == ColorMode::LIGHT) {
        resObj = nullptr;
        return;
    }
    bool hasDarkRes = CheckDarkResource(resObj);
    if (localColorMode == ColorMode::DARK) {
        if (!hasDarkRes) {
            color = Color(invertFunc(color.GetValue()));
        }
        resObj = nullptr;
        return;
    }
    auto colorMode = Container::CurrentColorMode();
    Color curColor = color;
    if ((colorMode == ColorMode::DARK) && !hasDarkRes) {
        color = Color(invertFunc(color.GetValue()));
    }
    if (!resObj) {
        resObj = AceType::MakeRefPtr<ResourceObject>();
        resObj->SetIsResource(false);
        resObj->SetInstanceId(instanceId);
    }
    resObj->SetNodeTag(nodeTag);
    resObj->SetColorMode(colorMode);
    resObj->SetHasDarkRes(hasDarkRes);
    resObj->SetColor(((colorMode == ColorMode::DARK) ? curColor : color));
}

bool ArkTSUtils::ParseJsColor(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result)
{
    RefPtr<ResourceObject> resourceObject;
    NodeInfo nodeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED };
    return ParseJsColor(vm, value, result, resourceObject, nodeInfo);
}

bool ArkTSUtils::ParseJsColor(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result,
    RefPtr<ResourceObject>& resourceObject, const NodeInfo& nodeInfo)
{
    bool state = false;
    if (value->IsNumber()) {
        result = Color(value->Uint32Value(vm));
        CompleteResourceObjectFromColor(resourceObject, result, true, nodeInfo);
        return true;
    }
    if (value->IsString(vm)) {
        state = Color::ParseColorString(value->ToString(vm)->ToString(vm), result);
        CompleteResourceObjectFromColor(resourceObject, result, state, nodeInfo);
        return state;
    }
    if (value->IsObject(vm)) {
        auto obj = value->ToObject(vm);
        auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
        if (!resId->IsNumber()) {
            return false;
        }
        state = ParseJsColorFromResource(vm, value, result, resourceObject);
        CompleteResourceObjectFromColor(resourceObject, result, state, nodeInfo);
        return state;
    }
    return state;
}

bool ArkTSUtils::ParseJsColor(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, Color& result, RefPtr<ResourceObject>& resObj)
{
    bool state = false;
    if (jsValue->IsNumber()) {
        result = Color(ColorAlphaAdapt(jsValue->ToNumber(vm)->Int32Value(vm)));
        CompleteResourceObjectFromColor(resObj, result, true);
        return true;
    }
    if (jsValue->IsString(vm)) {
        state = Color::ParseColorString(jsValue->ToString(vm)->ToString(vm), result);
        CompleteResourceObjectFromColor(resObj, result, state);
        return state;
    }
    if (jsValue->IsObject(vm)) {
        if (ParseColorMetricsToColor(vm, jsValue, result, resObj)) {
            CompleteResourceObjectFromColor(resObj, result, true);
            return true;
        }
        state = ParseJsColorFromResource(vm, jsValue, result, resObj);
        CompleteResourceObjectFromColor(resObj, result, state);
        return state;
    }
    return state;
}

bool ArkTSUtils::ParseJsSymbolColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result)
{
    RefPtr<ResourceObject> resourceObject;
    NodeInfo nodeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED };
    return ParseJsSymbolColorAlpha(vm, value, result, resourceObject, nodeInfo);
}

bool ArkTSUtils::ParseJsSymbolColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result,
    RefPtr<ResourceObject>& resourceObject, const NodeInfo& nodeInfo)
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
    CompleteResourceObjectFromColor(resourceObject, result, true, nodeInfo);
    return true;
}

bool ArkTSUtils::ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& color,
    std::vector<RefPtr<ResourceObject>>& resObjs, const NodeInfo& nodeInfo)
{
    RefPtr<ResourceObject> resObj;
    bool result = ArkTSUtils::ParseJsColorAlpha(vm, value, color, resObj, nodeInfo);
    if (SystemProperties::ConfigChangePerform()) {
        if (resObj) {
            resObjs.push_back(resObj);
        } else {
            resObjs.push_back(nullptr);
        }
    }
    return result;
}

bool ArkTSUtils::ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result)
{
    RefPtr<ResourceObject> resourceObject;
    NodeInfo nodeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED };
    return ParseJsColorAlpha(vm, value, result, resourceObject, nodeInfo);
}

bool ArkTSUtils::ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result,
    RefPtr<ResourceObject>& resourceObject, const NodeInfo& nodeInfo)
{
    bool state = false;
    if (value->IsNumber()) {
        result = Color(ColorAlphaAdapt(value->Uint32Value(vm)));
        CompleteResourceObjectFromColor(resourceObject, result, true, nodeInfo);
        return true;
    }
    if (value->IsString(vm)) {
        state = Color::ParseColorString(value->ToString(vm)->ToString(vm), result);
        CompleteResourceObjectFromColor(resourceObject, result, state, nodeInfo);
        return state;
    }
    if (value->IsObject(vm)) {
        if (ParseColorMetricsToColor(vm, value, result, resourceObject)) {
            CompleteResourceObjectFromColor(resourceObject, result, true, nodeInfo);
            return true;
        }
        state = ParseJsColorFromResource(vm, value, result, resourceObject);
        CompleteResourceObjectFromColor(resourceObject, result, state, nodeInfo);
        return state;
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
    NodeInfo nodeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED };
    return ParseJsColorAlpha(vm, value, result, defaultColor, resourceObject, nodeInfo);
}

bool ArkTSUtils::ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value,
    Color& result, const Color& defaultColor, RefPtr<ResourceObject>& resourceObject,
    const NodeInfo& nodeInfo)
{
    bool state = false;
    if (!value->IsNumber() && !value->IsString(vm) && !value->IsObject(vm)) {
        return state;
    }
    if (value->IsNumber()) {
        result = Color(ColorAlphaAdapt(value->Uint32Value(vm)));
        CompleteResourceObjectFromColor(resourceObject, result, true, nodeInfo);
        return true;
    }
    if (value->IsString(vm)) {
        state = Color::ParseColorString(value->ToString(vm)->ToString(vm), result, defaultColor);
        CompleteResourceObjectFromColor(resourceObject, result, state, nodeInfo);
        return state;
    }
    state = ParseJsColorFromResource(vm, value, result, resourceObject);
    CompleteResourceObjectFromColor(resourceObject, result, state, nodeInfo);
    return state;
}

std::string ToString(const EcmaVM* vm,  Local<JSValueRef>& jsVal)
{
    panda::LocalScope scope(vm);
    if (jsVal->IsObject(vm)) {
        return panda::JSON::Stringify(vm, jsVal)->ToString(vm)->ToString(vm);
    }
    return jsVal->ToString(vm)->ToString(vm);
}

RefPtr<ResourceObject> ArkTSUtils::GetResourceObject(const EcmaVM* vm, const Local<JSValueRef>& jsObj)
{
    auto obj = jsObj->ToObject(vm);
    return GetResourceObject(vm, obj);
}

RefPtr<ResourceObject> ArkTSUtils::GetResourceObject(const EcmaVM* vm, const Local<panda::ObjectRef>& obj)
{
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
        CHECK_NULL_RETURN(container, nullptr);
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
    RefPtr<ResourceObject>& resourceObject)
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
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

void CompleteResourceObjectFromParams(const EcmaVM* vm, Local<panda::ObjectRef>& jsObj, std::string& targetModule,
    ResourceType& resType, std::string& resName, int32_t resIdValue, int32_t typeNum)
{
    if (resIdValue != UNKNOWN_RESOURCE_ID && typeNum != UNKNOWN_RESOURCE_TYPE) {
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

    auto type = jsObj->Get(
        vm, panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(Framework::ArkUIIndex::TYPE)));
    int32_t typeNum = UNKNOWN_RESOURCE_TYPE;
    if (type->IsNumber()) {
        typeNum = type->Int32Value(vm);
    }

    std::string targetModule;
    std::string resName;
    if (resId->IsString(vm)) {
        resName = resId->ToString(vm)->ToString(vm);
        if (!ParseDollarResource(targetModule, resType, resName, typeNum == UNKNOWN_RESOURCE_TYPE)) {
            return;
        }
        CompleteResourceObjectFromId(vm, type, jsObj, resType, resName);
    } else if (resId->IsNumber()) {
        int32_t resIdValue = resId->Int32Value(vm);
        if (resIdValue == -1 || typeNum == UNKNOWN_RESOURCE_TYPE) {
            CompleteResourceObjectFromParams(vm, jsObj, targetModule, resType, resName, resIdValue, typeNum);
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

bool ArkTSUtils::ParseJsColorFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsObj, Color& result)
{
    RefPtr<ResourceObject> resourceObject;
    return ParseJsColorFromResource(vm, jsObj, result, resourceObject);
}

bool ArkTSUtils::ParseJsColorFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsObj, Color& result,
    RefPtr<ResourceObject>& resourceObject)
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
    RefPtr<ResourceObject> resourceObject;
    return ParseColorMetricsToColor(vm, jsValue, result, resourceObject);
}

bool ArkTSUtils::ParseColorMetricsToColor(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, Color& result, RefPtr<ResourceObject>& resourceObject)
{
    if (!jsValue->IsObject(vm)) {
        return false;
    }
    auto obj = jsValue->ToObject(vm);
    auto toNumericProp = obj->Get(vm, "toNumeric");
    auto colorSpaceProp = obj->Get(vm, "getColorSpace");
    auto jsRes = obj->Get(vm, "res_");
    if (SystemProperties::ConfigChangePerform() && !jsRes->IsUndefined() &&
        !jsRes->IsNull() && jsRes->IsObject(vm)) {
        auto jsObjRes = jsRes->ToObject(vm);
        CompleteResourceObject(vm, jsObjRes);
        resourceObject = GetResourceObject(vm, jsObjRes);
    }
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
        return ParseJsDimensionFromResourceByName(vm, obj, dimensionUnit, resourceObject, resourceWrapper, result);
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

bool ArkTSUtils::ParseJsDimensionFromResourceByName(const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj,
    DimensionUnit dimensionUnit, const RefPtr<ResourceObject>& resourceObject,
    const RefPtr<ResourceWrapper>& resourceWrapper, CalcDimension& result)
{
    if (!IsGetResourceByName(vm, jsObj)) {
        return false;
    }
    auto args = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
    if (!args->IsArray(vm)) {
        return false;
    }
    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
    auto resName = param->ToString(vm)->ToString(vm);

    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetStringByName(resName);
        result = StringUtils::StringToCalcDimension(value, false, dimensionUnit);
        return true;
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetIntByName(resName));
        result = StringUtils::StringToDimensionWithUnit(value, dimensionUnit);
        return true;
    }
    result = resourceWrapper->GetDimensionByName(resName);
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
        return ParseJsDimensionNGFromResourceByName(vm, obj, dimensionUnit, resourceObject, resourceWrapper, result);
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

bool ArkTSUtils::ParseJsDimensionNGFromResourceByName(const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj,
    DimensionUnit dimensionUnit, const RefPtr<ResourceObject>& resourceObject,
    const RefPtr<ResourceWrapper>& resourceWrapper, CalcDimension& result)
{
    if (!IsGetResourceByName(vm, jsObj)) {
        return false;
    }
    auto args = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
    if (!args->IsArray(vm)) {
        return false;
    }
    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
    auto resName = param->ToString(vm)->ToString(vm);

    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetStringByName(resName);
        return StringUtils::StringToCalcDimensionNG(value, result, false, dimensionUnit);
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetIntByName(resName));
        StringUtils::StringToDimensionWithUnitNG(value, result, dimensionUnit);
        return true;
    }
    result = resourceWrapper->GetDimensionByName(resName);
    return true;
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

bool ArkTSUtils::ParseResponseRegionTool(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, ResponseRegionSupportedTool& toolType)
{
    if (!jsValue->IsNumber()) {
        return false;
    }
    auto typeNum = jsValue->ToNumber(vm)->Value();
    if (0 <= typeNum && typeNum < static_cast<int32_t>(NG::ResponseRegionSupportedTool::TOOLCNT)) {
        toolType = static_cast<NG::ResponseRegionSupportedTool>(typeNum);
    } else {
        toolType = NG::ResponseRegionSupportedTool::ALL;
    }
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

std::string ArkTSUtils::GetLocalizedNumberStr(const EcmaVM* vm, Local<panda::ArrayRef> item, const std::string& type)
{
    auto localization = Localization::GetInstance();
    if (!localization) {
        return std::string();
    }

    if (type == "d" && item->IsNumber()) {
        std::string numStr = std::to_string(item->Int32Value(vm));
        std::string result;
        return localization->LocalizeNumber(numStr, result, 0) ? result : std::string();
    }

    if (type == "f" && item->IsNumber()) {
        std::string numStr = std::to_string(item->ToNumber(vm)->Value());
        std::string result;
        return localization->LocalizeNumber(numStr, result, FLOAT_PRECISION) ? result : std::string();
    }

    return std::string();
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
            std::string result = ArkTSUtils::GetLocalizedNumberStr(vm, item, type);
            return result.empty() ? std::to_string(item->Int32Value(vm)) : result;
        }
    } else if (type == "s") {
        if (item->IsString(vm)) {
            return item->ToString(vm)->ToString(vm);
        }
    } else if (type == "f") {
        if (item->IsNumber()) {
            std::string result = ArkTSUtils::GetLocalizedNumberStr(vm, item, type);
            return result.empty() ? std::to_string(item->ToNumber(vm)->Value()) : result;
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

bool FillResultForResIdNumIsNegative(const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj,
    const Local<JSValueRef>& type, const Local<JSValueRef>& params, std::string& result,
    const RefPtr<ResourceWrapper>& resourceWrapper)
{
    auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
    if (type->Uint32Value(vm) == static_cast<uint32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetStringByName(param->ToString(vm)->ToString(vm));
        auto startIndex = ArkTSUtils::GetStringFormatStartIndex(vm, jsObj);
        ReplaceHolder(vm, originStr, params, startIndex + 1);
        result = originStr;
    } else if (type->Uint32Value(vm) == static_cast<uint32_t>(ResourceType::PLURAL)) {
        auto countJsVal = panda::ArrayRef::GetValueAt(vm, params, 1);
        int count = 0;
        if (!countJsVal->IsNumber()) {
            return false;
        }
        count = countJsVal->ToNumber(vm)->Value();
        auto pluralStr = resourceWrapper->GetPluralStringByName(param->ToString(vm)->ToString(vm), count);
        auto startIndex = ArkTSUtils::GetStringFormatStartIndex(vm, jsObj);
        ReplaceHolder(vm, pluralStr, params, startIndex + REPLACEHOLDER_INDEX);
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
    CompleteResourceObject(vm, obj);

    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
    if (!type->IsNumber() || !resId->IsNumber() || !args->IsArray(vm)) {
        return false;
    }

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
        return FillResultForResIdNumIsNegative(vm, obj, type, params, result, resourceWrapper);
    }
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetString(resId->Uint32Value(vm));
        auto startIndex = GetStringFormatStartIndex(vm, obj);
        ReplaceHolder(vm, originStr, params, startIndex);
        result = originStr;
    } else if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::PLURAL)) {
        auto startIndex = GetStringFormatStartIndex(vm, obj);
        auto countJsVal = panda::ArrayRef::GetValueAt(vm, params, startIndex);
        int count = 0;
        if (!countJsVal->IsNumber()) {
            return false;
        }
        count = countJsVal->ToNumber(vm)->Value();
        auto pluralStr = resourceWrapper->GetPluralString(resId->ToNumber(vm)->Value(), count);
        ReplaceHolder(vm, pluralStr, params, startIndex + 1);
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
        result.isSet = true;
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
        result.isSet = true;
    }
}

void ArkTSUtils::ParsePadding(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen,
    ArkUISizeType& result, std::vector<RefPtr<ResourceObject>>& resObjs)
{
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParsePadding(vm, value, dimen, result, resObj);
    if (SystemProperties::ConfigChangePerform()) {
        resObjs.push_back(resObj);
    }
}

void ArkTSUtils::ParseMargin(
    const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen, ArkUISizeType& result)
{
    RefPtr<ResourceObject> resObj;
    ParseMargin(vm, value,  dimen, result, resObj);
}

void ArkTSUtils::ParseMargin(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen,
    ArkUISizeType& result, RefPtr<ResourceObject>& resObj)
{
    if (ArkTSUtils::ParseJsDimensionVp(vm, value, dimen, resObj)) {
        result.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            result.string = dimen.CalcValue().c_str();
        } else {
            result.value = dimen.Value();
        }
        result.isSet = true;
    }
}

void ArkTSUtils::ParseMargin(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen,
    ArkUISizeType& result, std::vector<RefPtr<ResourceObject>>& resObjs)
{
    RefPtr<ResourceObject> resObj;
    ArkTSUtils::ParseMargin(vm, value, dimen, result, resObj);
    if (SystemProperties::ConfigChangePerform()) {
        resObjs.push_back(resObj);
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
bool ArkTSUtils::CheckLengthMetrics(EcmaVM* vm, const Local<panda::ObjectRef>& jsObject)
{
    if (jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "start")) ||
        jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "end")) ||
        jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "topStart")) ||
        jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "topEnd")) ||
        jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "bottomStart")) ||
        jsObject->Has(vm, panda::StringRef::NewFromUtf8(vm, "bottomEnd"))) {
        return true;
    }
    auto jsTop = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "top"));
    if (jsTop->IsObject(vm)) {
        auto topObj = jsTop->ToObject(vm);
        if (topObj->Has(vm, panda::StringRef::NewFromUtf8(vm, "value"))) {
            return true;
        }
    }
    auto jsBottom = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "bottom"));
    if (jsBottom->IsObject(vm)) {
        auto bottomObj = jsBottom->ToObject(vm);
        if (bottomObj->Has(vm, panda::StringRef::NewFromUtf8(vm, "value"))) {
            return true;
        }
    }
    return false;
}

bool ArkTSUtils::ParseLocalizedMargin(
    const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen, ArkUISizeType& result)
{
    if (ArkTSUtils::ParseJsLengthMetrics(vm, value, dimen)) {
        result.unit = static_cast<int8_t>(dimen.Unit());
        if (dimen.CalcValue() != "") {
            result.string = dimen.CalcValue().c_str();
        } else {
            result.value = dimen.Value();
        }
        result.isSet = true;
        return true;
    }
    return false;
}

bool ArkTSUtils::ParseLocalizedPadding(
    const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen, ArkUISizeType& result)
{
    if (ArkTSUtils::ParseJsLengthMetrics(vm, value, dimen)) {
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
        result.isSet = true;
        return true;
    }
    return false;
}

bool ArkTSUtils::ParseJsDimensionRect(const EcmaVM* vm, const Local<panda::JSValueRef>& jsValue, DimensionRect& result)
{
    result.SetOffset(DimensionOffset(CalcDimension(0, DimensionUnit::VP), CalcDimension(0, DimensionUnit::VP)));
    result.SetSize(DimensionSize(CalcDimension(1, DimensionUnit::PERCENT), CalcDimension(1, DimensionUnit::PERCENT)));
    if (!jsValue->IsObject(vm)) {
        return true;
    }
    auto obj = jsValue->ToObject(vm);
    auto x = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "x"));
    auto y = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "y"));
    auto width = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    auto height = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
    CalcDimension xDimen = result.GetOffset().GetX();
    CalcDimension yDimen = result.GetOffset().GetY();
    CalcDimension widthDimen = result.GetWidth();
    CalcDimension heightDimen = result.GetHeight();
    auto s1 = width->ToString(vm)->ToString(vm);
    auto s2 = height->ToString(vm)->ToString(vm);
    if (s1.find('-') != std::string::npos) {
        width = OHOS::Ace::Framework::ToJSValue("100%");
    }
    if (s2.find('-') != std::string::npos) {
        height = OHOS::Ace::Framework::ToJSValue("100%");
    }
    if (ArkTSUtils::ParseJsDimensionNG(vm, x, xDimen, DimensionUnit::VP)) {
        auto offset = result.GetOffset();
        offset.SetX(xDimen);
        result.SetOffset(offset);
    }
    if (ArkTSUtils::ParseJsDimensionNG(vm, y, yDimen, DimensionUnit::VP)) {
        auto offset = result.GetOffset();
        offset.SetY(yDimen);
        result.SetOffset(offset);
    }
    if (ArkTSUtils::ParseJsDimensionNG(vm, width, widthDimen, DimensionUnit::VP)) {
        if (widthDimen.Unit() == DimensionUnit::PERCENT && widthDimen.Value() < 0) {
            return true;
        }
        result.SetWidth(widthDimen);
    }
    if (ArkTSUtils::ParseJsDimensionNG(vm, height, heightDimen, DimensionUnit::VP)) {
        if (heightDimen.Unit() == DimensionUnit::PERCENT && heightDimen.Value() < 0) {
            return true;
        }
        result.SetHeight(heightDimen);
    }
    return true;
}

bool ArkTSUtils::ParseJsResponseRegion(
    const EcmaVM* vm, const Local<panda::JSValueRef>& jsValue, ArkUI_Float32* values, int32_t* units, uint32_t length)
{
    if (!jsValue->IsArray(vm) && !jsValue->IsObject(vm)) {
        return false;
    }
    const uint32_t DIMENSION_LENGTH = 4;
    if (jsValue->IsArray(vm)) {
        auto transArray = static_cast<Local<panda::ArrayRef>>(jsValue);
        uint32_t arrayLength = transArray->Length(vm);
        for (uint32_t i = 0; i < arrayLength; i++) {
            CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
            CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
            DimensionOffset offsetDimen(xDimen, yDimen);
            DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
            if (ArkTSUtils::ParseJsDimensionRect(vm, transArray->GetValueAt(vm, jsValue, i), dimenRect)) {
                values[DIMENSION_LENGTH * i] = static_cast<ArkUI_Float32>(dimenRect.GetOffset().GetX().Value());
                units[DIMENSION_LENGTH * i] = static_cast<int32_t>(dimenRect.GetOffset().GetX().Unit());
                values[DIMENSION_LENGTH * i + NUM_1] = static_cast<ArkUI_Float32>(dimenRect.GetOffset().GetY().Value());
                units[DIMENSION_LENGTH * i + NUM_1] = static_cast<int32_t>(dimenRect.GetOffset().GetY().Unit());
                values[DIMENSION_LENGTH * i + NUM_2] = static_cast<ArkUI_Float32>(dimenRect.GetWidth().Value());
                units[DIMENSION_LENGTH * i + NUM_2] = static_cast<int32_t>(dimenRect.GetWidth().Unit());
                values[DIMENSION_LENGTH * i + NUM_3] = static_cast<ArkUI_Float32>(dimenRect.GetHeight().Value());
                units[DIMENSION_LENGTH * i + NUM_3] = static_cast<int32_t>(dimenRect.GetHeight().Unit());
            } else {
                return false;
            }
        }
        return true;
    }
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
    if (ArkTSUtils::ParseJsDimensionRect(vm, jsValue, dimenRect)) {
        values[NUM_0] = static_cast<ArkUI_Float32>(dimenRect.GetOffset().GetX().Value());
        units[NUM_0] = static_cast<int32_t>(dimenRect.GetOffset().GetX().Unit());
        values[NUM_1] = static_cast<ArkUI_Float32>(dimenRect.GetOffset().GetY().Value());
        units[NUM_1] = static_cast<int32_t>(dimenRect.GetOffset().GetY().Unit());
        values[NUM_2] = static_cast<ArkUI_Float32>(dimenRect.GetWidth().Value());
        units[NUM_2] = static_cast<int32_t>(dimenRect.GetWidth().Unit());
        values[NUM_3] = static_cast<ArkUI_Float32>(dimenRect.GetHeight().Value());
        units[NUM_3] = static_cast<int32_t>(dimenRect.GetHeight().Unit());
        return true;
    }
    return false;
}

bool ArkTSUtils::HandleCallbackJobs(
    const EcmaVM* vm, panda::TryCatch& trycatch, const Local<JSValueRef>& resultException)
{
    JSNApi::ExecutePendingJob(vm);
    auto runtime =
        std::static_pointer_cast<Framework::ArkJSRuntime>(Framework::JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (resultException.IsEmpty() || trycatch.HasCaught()) {
        LOGW("after call jsFunction hasError, empty: %{public}d, caught: %{public}d", resultException.IsEmpty(),
            trycatch.HasCaught());
        runtime->HandleUncaughtException(trycatch);
        return false;
    }
    return true;
}

uint32_t ArkTSUtils::parseShadowColor(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    RefPtr<ResourceObject> resObj;
    return parseShadowColorWithResObj(vm, jsValue, resObj);
}

uint32_t ArkTSUtils::parseShadowColorWithResObj(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
    RefPtr<ResourceObject>& resObj, const std::optional<NodeInfo>& nodeInfo)
{
    Color color = DEFAULT_TEXT_SHADOW_COLOR;
    static const NodeInfo defaultNodeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED };
    if (!ParseJsColorAlpha(vm, jsValue, color, resObj,
        (nodeInfo.has_value() ? nodeInfo.value() : defaultNodeInfo))) {
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
    RefPtr<ResourceObject>& resObj, const std::optional<NodeInfo>& nodeInfo)
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
    RefPtr<ResourceObject>& resObj, const std::optional<NodeInfo>& nodeInfo)
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
    if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::STRING)) {
        auto strValue = resourceWrapper->GetString(resId->Uint32Value(vm));
        if (!strValue.empty()) {
            auto customSymbolId = static_cast<uint32_t>(strtol(strValue.c_str(), nullptr, 16));
            symbolId = customSymbolId;
            return true;
        }
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

double ArkTSUtils::GetArrayLength(const EcmaVM* vm, Local<panda::ArrayRef> array)
{
    auto arrayLength = 0;
    if (array->IsProxy(vm)) {
        arrayLength = array->Get(vm, "length")->IsNumber() ? array->Get(vm, "length")->ToNumber(vm)->Value() : 0;
    } else {
        arrayLength = array->Length(vm);
    }
    return arrayLength;
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

void ArkTSUtils::ThrowBusinessError(const EcmaVM* vm, const std::string& msg, int32_t code)
{
    auto errorVal = panda::Exception::Error(vm, panda::StringRef::NewFromUtf8(vm, msg.c_str()));
    auto codeVal = panda::NumberRef::New(vm, static_cast<int32_t>(code));
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

Local<JSValueRef> ArkTSUtils::JsGetPinchAxisScaleValue(ArkUIRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo =
        static_cast<AxisInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(info->GetVM(), 0));
    if (!eventInfo) {
        return JSValueRef::Undefined(info->GetVM());
    }
    return panda::NumberRef::New(info->GetVM(), eventInfo->GetPinchAxisScale());
}

Local<JSValueRef> ArkTSUtils::JsHasAxis(ArkUIRuntimeCallInfo* info)
{
    Local<JSValueRef> thisObj = info->GetThisRef();
    auto eventInfo =
        static_cast<AxisInfo*>(panda::Local<panda::ObjectRef>(thisObj)->GetNativePointerField(info->GetVM(), 0));
    if (!eventInfo) {
        return JSValueRef::Undefined(info->GetVM());
    }
    auto vm = info->GetVM();
    auto param = info->GetCallArgRef(0);
    AxisType axisType;
    if (!param->IsNumber()) {
        return panda::BooleanRef::New(info->GetVM(), false);
    }
    axisType = static_cast<AxisType>(param->ToNumber(vm)->Value());
    return panda::BooleanRef::New(info->GetVM(), eventInfo->HasAxis(axisType));
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
        WrapMenuParams(vm, menuParams, menuItems, true);
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

void ArkTSUtils::ParseMenuItemsSymbolId(
    const EcmaVM* vm, const Local<JSValueRef>& jsStartIcon, NG::MenuOptionsParam& menuOptionsParam)
{
    if (StringToMenuItemType(menuOptionsParam.id) == MenuItemType::UNKNOWN) {
        uint32_t symbolId = 0;
        RefPtr<ResourceObject> resourceObject;
        if (jsStartIcon->IsNumber()) {
            symbolId = jsStartIcon->ToNumber(vm)->Value();
            menuOptionsParam.symbolId = symbolId;
            return;
        }
        if (ParseJsSymbolId(vm, jsStartIcon, symbolId, resourceObject)) {
            menuOptionsParam.symbolId = symbolId;
        }
    } else {
        UpdateInfoById(menuOptionsParam, menuOptionsParam.id);
    }
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
        ParseMenuItemsSymbolId(vm, jsStartIcon, menuOptionsParam);
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
        UpdateInfoById(menuOptionsParam, menuOptionsParam.id);
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

bool ArkTSUtils::ParseJsIgnoresLayoutSafeAreaEdges(
    const EcmaVM* vm, const Local<JSValueRef>& value, std::vector<ArkUI_Int32>& edges)
{
    if (!value->IsArray(vm)) {
        return false;
    }
    auto array = panda::Local<panda::ArrayRef>(value);
    auto length = array->Length(vm);
    for (uint32_t index = 0; index < length; index++) {
        auto item = panda::ArrayRef::GetValueAt(vm, array, index);
        ArkUI_Int32 edge;
        if (!ArkTSUtils::ParseJsInt32(vm, item, edge)) {
            return false;
        }
        edges.push_back(edge);
    }
    return true;
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
    std::vector<ArkUIInt32orFloat32>& colors, std::vector<RefPtr<ResourceObject>>& vectorResObj,
    const NodeInfo& nodeInfo)
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
        if (!ArkTSUtils::ParseJsColorAlpha(vm, colorParams, color, resObj, nodeInfo)) {
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
    NodeInfo nodeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED };
    ArkTSUtils::ParseGradientColorStops(vm, value, colors, vectorResObj, nodeInfo);
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

bool ArkTSUtils::ParseContentTransitionEffect(
    const EcmaVM* vm, const Local<JSValueRef>& value, ContentTransitionType& contentTransitionType)
{
    if (!value->IsObject(vm)) {
        return false;
    }
    auto obj = value->ToObject(vm);
    auto typeValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "contentTransitionType_"));
    if (typeValue.IsEmpty() || !typeValue->IsString(vm)) {
        return false;
    }
    static const std::unordered_map<std::string, ContentTransitionType> contentTransitionTypeMap {
        { "IDENTITY", ContentTransitionType::IDENTITY },
        { "OPACITY", ContentTransitionType::OPACITY },
    };
    auto typeValueStr = typeValue->ToString(vm)->ToString(vm);
    auto it = contentTransitionTypeMap.find(typeValueStr);
    if (it == contentTransitionTypeMap.end()) {
        return false;
    }
    contentTransitionType = it->second;
    return true;
}

bool ArkTSUtils::GetResourceId(
    const std::string& resName, const std::string& bundleName, const std::string& moduleName, int32_t& resId)
{
    auto resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, Container::CurrentIdSafelyWithCheck());
    auto resAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resObj);
    CHECK_NULL_RETURN(resAdapter, false);
    resId = resAdapter->GetResId(resName);
    return true;
}

bool ArkTSUtils::HasGetter(const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj, int32_t propertyIndex)
{
    auto stringRef = panda::ExternalStringCache::GetCachedString(vm, propertyIndex);
    panda::PropertyAttribute propertyAttribute;
    jsObj->GetOwnProperty(vm, stringRef, propertyAttribute);
    return propertyAttribute.HasGetter();
}

int32_t ArkTSUtils::GetStringFormatStartIndex(const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj)
{
    if (HasGetter(vm, jsObj, static_cast<int32_t>(Framework::ArkUIIndex::ID))) {
        return 1;
    }
    return 0;
}

void ArkTSUtils::ParseMarginOrPaddingCorner(const EcmaVM* vm, const Local<JSValueRef>& value,
    std::optional<CalcDimension>& top, std::optional<CalcDimension>& bottom, std::optional<CalcDimension>& left,
    std::optional<CalcDimension>& right)
{
    CalcDimension leftDimen;
    if (ParseJsDimensionVp(vm, GetProperty(vm, value, static_cast<int32_t>(Framework::ArkUIIndex::LEFT)), leftDimen)) {
        left = leftDimen;
    }
    CalcDimension rightDimen;
    if (ParseJsDimensionVp(
            vm, GetProperty(vm, value, static_cast<int32_t>(Framework::ArkUIIndex::RIGHT)), rightDimen)) {
        right = rightDimen;
    }
    CalcDimension topDimen;
    if (ParseJsDimensionVp(vm, GetProperty(vm, value, static_cast<int32_t>(Framework::ArkUIIndex::TOP)), topDimen)) {
        top = topDimen;
    }
    CalcDimension bottomDimen;
    if (ParseJsDimensionVp(
            vm, GetProperty(vm, value, static_cast<int32_t>(Framework::ArkUIIndex::BOTTOM)), bottomDimen)) {
        bottom = bottomDimen;
    }
}

bool ArkTSUtils::HasProperty(const EcmaVM* vm, const Local<panda::ObjectRef>& obj, const std::string& propertyName)
{
    CHECK_NULL_RETURN(vm, false);
    auto stringRef = panda::StringRef::NewFromUtf8(vm, propertyName.c_str());
    return obj->Has(vm, stringRef);
}

Local<JSValueRef> ArkTSUtils::GetProperty(
    const EcmaVM* vm, const Local<panda::ObjectRef>& obj, const std::string& propertyName)
{
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto stringRef = panda::StringRef::NewFromUtf8(vm, propertyName.c_str());
    return obj->Get(vm, stringRef);
}

Local<JSValueRef> ArkTSUtils::GetProperty(const EcmaVM* vm, const Local<panda::ObjectRef>& obj, int32_t propertyIndex)
{
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    return obj->Get(vm, panda::ExternalStringCache::GetCachedString(vm, propertyIndex));
}

bool ArkTSUtils::CheckJavaScriptScope(const EcmaVM* vm)
{
    return !(Framework::JsiDeclarativeEngineInstance::GetCurrentRuntime() == nullptr || vm == nullptr);
}

template<class T>
bool ArkTSUtils::ConvertFromJSValueNG(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, T& result, RefPtr<ResourceObject>& resObj)
{
    if constexpr (std::is_same_v<T, bool>) {
        if (jsValue->IsBoolean()) {
            result = jsValue->ToBoolean(vm);
            return true;
        }
        result = false;
    } else if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
        double value;
        if (ParseJsDouble(vm, jsValue, value, resObj)) {
            result = static_cast<T>(value);
            return true;
        }
        result = 0;
    } else if constexpr (std::is_same_v<T, std::string>) {
        if (jsValue->IsString(vm)) {
            result = jsValue->ToString(vm);
            return true;
        }
    } else if constexpr (std::is_same_v<T, Dimension>) {
        CalcDimension calc;
        bool ret = ParseJsDimensionVpNG(vm, jsValue, calc, resObj);
        result = calc;
        return ret;
    } else if constexpr (std::is_same_v<T, CalcDimension>) {
        return ParseJsDimensionVpNG(vm, jsValue, result, resObj);
    } else if constexpr (std::is_same_v<T, NG::CalcLength>) {
        return ParseJsLengthVpNG(vm, jsValue, result, resObj);
    } else if constexpr (std::is_same_v<T, Color>) {
        return ParseJsColor(vm, jsValue, result, resObj);
    }
    return false;
}

template<class T>
bool ArkTSUtils::ConvertFromJSValue(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, T& result, RefPtr<ResourceObject>& resObj)
{
    if constexpr (std::is_same_v<T, bool>) {
        if (jsValue->IsBoolean()) {
            result = jsValue->ToBoolean(vm);
            return true;
        }
        result = false;
    } else if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
        double value;
        if (ParseJsDouble(vm, jsValue, value, resObj)) {
            result = static_cast<T>(value);
            return true;
        }
        result = 0;
    } else if constexpr (std::is_same_v<T, std::string>) {
        if (jsValue->IsString(vm)) {
            result = jsValue->ToString(vm);
            return true;
        }
    } else if constexpr (std::is_same_v<T, Dimension>) {
        CalcDimension calc;
        bool ret = ParseJsDimensionVp(vm, jsValue, calc, resObj);
        result = calc;
        return ret;
    } else if constexpr (std::is_same_v<T, CalcDimension>) {
        return ParseJsDimensionVp(vm, jsValue, result, resObj);
    } else if constexpr (std::is_same_v<T, Color>) {
        NodeInfo nodeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED };
        return ParseJsColor(vm, jsValue, result, resObj, nodeInfo);
    }
    return false;
}

void ArkTSUtils::ParseStepOptionsMap(
    const EcmaVM* vm, const Local<JSValueRef>& optionsArg, StepOptions& optionsMap)
{
    Local<panda::MapRef> StepMapRef(optionsArg);
    int32_t StepMapSize = StepMapRef->GetSize(vm);
    for (int32_t i = 0; i < StepMapSize; i++) {
        auto number = StepMapRef->GetKey(vm, i)->ToNumber(vm)->Value();
        auto itemAccessibility = StepMapRef->GetValue(vm, i)->ToString(vm)->ToString(vm);
        optionsMap[static_cast<int32_t>(number)] = itemAccessibility;
    }
}

ACE_FORCE_EXPORT RefPtr<BasicShape> ArkTSUtils::GetJSBasicShape(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    Framework::JSShapeAbstract* shapeAbstract =
        Framework::JSRef<Framework::JSObject>::Cast(Framework::JSRef<Framework::JSObject>::Make(jsValue))
            ->Unwrap<Framework::JSShapeAbstract>();
    if (shapeAbstract == nullptr) {
        return nullptr;
    }
    return shapeAbstract->GetBasicShape();
}

template<typename T>
Local<JSValueRef> ArkTSUtils::ToJsValueWithVM(const EcmaVM* vm, T val)
{
    if constexpr (std::is_same_v<T, bool>) {
        return panda::BooleanRef::New(vm, val);
    } else if constexpr (std::is_same_v<T, int64_t>) {
        return panda::NumberRef::New(vm, val);
    } else if constexpr (std::is_integral<T>::value && std::is_signed<T>::value) {
        return panda::IntegerRef::New(vm, val);
    } else if constexpr (std::is_unsigned_v<T>) {
        return panda::IntegerRef::NewFromUnsigned(vm, val);
    } else if constexpr (std::is_floating_point_v<T>) {
        return panda::NumberRef::New(vm, val);
    } else if constexpr (std::is_same_v<T, std::string>) {
        return panda::StringRef::NewFromUtf8(vm, val.c_str());
    } else if constexpr (std::is_same_v<T, const char*>) {
        return panda::StringRef::NewFromUtf8(vm, val);
    } else if constexpr (std::is_same_v<T, std::u16string>) {
        return panda::StringRef::NewFromUtf16(vm, val.c_str());
    }

    return panda::JSValueRef::Undefined(vm);
}

template<class T>
Local<JSValueRef> ArkTSUtils::ConvertToJSValue(const EcmaVM* vm, T&& value)
{
    using ValueType = std::remove_cv_t<std::remove_reference_t<T>>;
    if constexpr (std::is_arithmetic_v<ValueType> || std::is_same_v<ValueType, std::string> ||
                  std::is_same_v<ValueType, std::u16string>) {
        return ToJsValueWithVM(vm, std::forward<T>(value));
    } else if constexpr (std::is_enum_v<ValueType>) {
        return ToJsValueWithVM(vm, static_cast<std::make_signed_t<ValueType>>(value));
    } else if constexpr (std::is_same_v<ValueType, Dimension> || std::is_same_v<ValueType, CalcDimension>) {
        if (value.Unit() == DimensionUnit::VP) {
            return ToJsValueWithVM(vm, value.Value());
        } else {
            LOGE("Failed to convert to JS value with dimension which it not using 'VP' unit");
            return Local<JSValueRef>();
        }
    } else {
        LOGE("Failed to convert to JS value");
        return Local<JSValueRef>();
    }
}

template<class T>
void ArkTSUtils::ConvertToJSValuesImpl(
    const EcmaVM* vm, std::vector<Local<JSValueRef>>& result, T&& value)
{
    result.emplace_back(ConvertToJSValue(vm, std::forward<T>(value)));
}

template<class T, class V, class... Args>
void ArkTSUtils::ConvertToJSValuesImpl(
    const EcmaVM* vm, std::vector<Local<JSValueRef>>& result, T&& value, V&& nextValue, Args&&... args)
{
    result.emplace_back(ConvertToJSValue(vm, std::forward<T>(value)));
    ConvertToJSValuesImpl(vm, result, std::forward<V>(nextValue), std::forward<Args>(args)...);
}

template<class... Args>
std::vector<Local<JSValueRef>> ArkTSUtils::ConvertToJSValues(const EcmaVM* vm, Args... args)
{
    std::vector<Local<JSValueRef>> result;
    ConvertToJSValuesImpl(vm, result, args...);
    return result;
}

template ACE_FORCE_EXPORT Local<JSValueRef> ArkTSUtils::ToJsValueWithVM<double>(const EcmaVM* vm, double);
template ACE_FORCE_EXPORT Local<JSValueRef> ArkTSUtils::ToJsValueWithVM<int32_t>(const EcmaVM* vm, int32_t);

template ACE_FORCE_EXPORT bool ArkTSUtils::ConvertFromJSValue<Color>(
    const EcmaVM*, const Local<JSValueRef>&, Color&, RefPtr<ResourceObject>&);
template ACE_FORCE_EXPORT bool ArkTSUtils::ConvertFromJSValueNG<Dimension>(
    const EcmaVM*, const Local<JSValueRef>&, Dimension&, RefPtr<ResourceObject>&);

template ACE_FORCE_EXPORT Local<JSValueRef> ArkTSUtils::ConvertToJSValue<CalcDimension>(
    const EcmaVM* vm, CalcDimension&& value);
template ACE_FORCE_EXPORT Local<JSValueRef> ArkTSUtils::ConvertToJSValue<Dimension>(
    const EcmaVM* vm, Dimension&& value);
template ACE_FORCE_EXPORT Local<JSValueRef> ArkTSUtils::ConvertToJSValue<ScrollState>(
    const EcmaVM* vm, ScrollState&& value);
template ACE_FORCE_EXPORT Local<JSValueRef> ArkTSUtils::ConvertToJSValue<int32_t>(const EcmaVM* vm, int32_t&& value);

template ACE_FORCE_EXPORT void ArkTSUtils::ConvertToJSValuesImpl<ScrollState>(
    const EcmaVM*, std::vector<Local<JSValueRef>>&, ScrollState&&);
template ACE_FORCE_EXPORT void ArkTSUtils::ConvertToJSValuesImpl<int32_t>(
    const EcmaVM*, std::vector<Local<JSValueRef>>&, int32_t&&);

template ACE_FORCE_EXPORT void ArkTSUtils::ConvertToJSValuesImpl<CalcDimension, ScrollState>(
    const EcmaVM*, std::vector<Local<JSValueRef>>&, CalcDimension&&, ScrollState&&);
template ACE_FORCE_EXPORT void ArkTSUtils::ConvertToJSValuesImpl<Dimension, ScrollState>(
    const EcmaVM*, std::vector<Local<JSValueRef>>&, Dimension&&, ScrollState&&);
template ACE_FORCE_EXPORT void ArkTSUtils::ConvertToJSValuesImpl<int32_t, int32_t>(
    const EcmaVM*, std::vector<Local<JSValueRef>>&, int32_t&&, int32_t&&);

template ACE_FORCE_EXPORT std::vector<Local<JSValueRef>> ArkTSUtils::ConvertToJSValues<CalcDimension, ScrollState>(
    const EcmaVM*, CalcDimension, ScrollState);
template ACE_FORCE_EXPORT std::vector<Local<JSValueRef>> ArkTSUtils::ConvertToJSValues<Dimension, ScrollState>(
    const EcmaVM*, Dimension, ScrollState);
template ACE_FORCE_EXPORT std::vector<Local<JSValueRef>> ArkTSUtils::ConvertToJSValues<int32_t, int32_t>(
    const EcmaVM*, int32_t, int32_t);
RefPtr<BasicShape> ArkTSUtils::GetBasicShape(const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj)
{
    Framework::JSShapeAbstract* jsShapeAbstract =
        static_cast<Framework::JSShapeAbstract*>(jsObj->GetNativePointerField(vm, 0));
    CHECK_NULL_RETURN(jsShapeAbstract, nullptr);
    return jsShapeAbstract->GetBasicShape();
}

bool ArkTSUtils::IsJsView(const EcmaVM* vm, const Local<JSValueRef>& value)
{
    return value->IsBoolean() && value->ToBoolean(vm)->Value();
}

bool ArkTSUtils::GetNativeNode(const EcmaVM* vm, const Local<JSValueRef>& value, ArkUINodeHandle& nativeNode)
{
    if (value->IsNativePointer(vm)) {
        nativeNode = nodePtr(value->ToNativePointer(vm)->Value());
        return true;
    }
    if (IsJsView(vm, value)) {
        nativeNode = nullptr;
        return true;
    }

    return false;
}

void ArkTSUtils::ParseShadowOffsetXY(const EcmaVM* vm, const Local<JSValueRef>& jsObj, Shadow& shadow)
{
    CalcDimension offsetX;
    RefPtr<ResourceObject> xResObj;
    if (ArkTSUtils::ParseJsResource(vm, ArkTSUtils::GetProperty(vm, jsObj, "offsetX"), offsetX, xResObj)) {
        if (SystemProperties::ConfigChangePerform() && xResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& xResObj, Shadow& shadow) {
                CalcDimension xValue;
                ResourceParseUtils::ParseResResource(xResObj, xValue);
                shadow.SetOffsetX(xValue.Value());
            };
            shadow.AddResource("shadow.offsetX", xResObj, std::move(updateFunc));
        }
        shadow.SetOffsetX(offsetX.Value());
    } else {
        if (ParseJsDimensionVp(vm, GetProperty(vm, jsObj, "offsetX"), offsetX)) {
            shadow.SetOffsetX(offsetX.Value());
        }
    }
    CalcDimension offsetY;
    RefPtr<ResourceObject> yResObj;
    auto jsOffsetY = GetProperty(vm, jsObj, static_cast<int32_t>(Framework::ArkUIIndex::OFFSET_Y));
    if (ParseJsResource(vm, jsOffsetY, offsetY, yResObj)) {
        if (yResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& yResObj, Shadow& shadow) {
                CalcDimension yValue;
                ResourceParseUtils::ParseResResource(yResObj, yValue);
                shadow.SetOffsetY(yValue.Value());
            };
            shadow.AddResource("shadow.offsetY", yResObj, std::move(updateFunc));
        }
        shadow.SetOffsetY(offsetY.Value());
    } else {
        if (ParseJsDimensionVp(vm, jsOffsetY, offsetY)) {
            shadow.SetOffsetY(offsetY.Value());
        }
    }
}

void ArkTSUtils::ParseShadowPropsUpdate(
    const EcmaVM* vm, const Local<JSValueRef>& jsObj, double& radius, Shadow& shadow)
{
    if (jsObj->IsUndefined()) {
        return;
    }
    RefPtr<ResourceObject> radiusResObj;
    ParseJsDouble(
        vm, GetProperty(vm, jsObj, static_cast<int32_t>(Framework::ArkUIIndex::RADIUS)), radius, radiusResObj);
    if (SystemProperties::ConfigChangePerform() && radiusResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& radiusResObj, Shadow& shadow) {
            double radius = 0.0;
            ResourceParseUtils::ParseResDouble(radiusResObj, radius);
            if (LessNotEqual(radius, 0.0)) {
                radius = 0.0;
            }
            shadow.SetBlurRadius(radius);
        };
        shadow.AddResource("shadow.radius", radiusResObj, std::move(updateFunc));
    }
}

bool ArkTSUtils::GetShadowFromTheme(
    const EcmaVM* vm, ShadowStyle shadowStyle, Shadow& shadow, const bool configChangePerform)
{
    CHECK_NULL_RETURN(vm, false);
    ViewAbstractModel::GetInstance()->RemoveResObj("shadowStyle");
    auto colorMode = Container::CurrentColorMode();
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);

    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    if (!shadowTheme) {
        return false;
    }
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    if (configChangePerform) {
        auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_RETURN(frameNode, false);
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_RETURN(pattern, false);
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto&& updateFunc = [shadowStyle, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto colorMode = Container::CurrentColorMode();
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
            if (!shadowTheme) {
                return;
            }
            Shadow shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
            ACE_UPDATE_NODE_RENDER_CONTEXT(BackShadow, shadow, frameNode);
        };
        updateFunc(resObj);
        pattern->AddResObj("shadowStyle", resObj, std::move(updateFunc));
        return false;
    }
    return true;
}

bool ArkTSUtils::ParseJsShadowColorStrategy(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, ShadowColorStrategy& strategy)
{
    CHECK_NULL_RETURN(vm, false);
    if (jsValue->IsString(vm)) {
        std::string colorStr = jsValue->ToString(vm)->ToString(vm);
        if (colorStr.compare("average") == 0) {
            strategy = ShadowColorStrategy::AVERAGE;
            return true;
        } else if (colorStr.compare("primary") == 0) {
            strategy = ShadowColorStrategy::PRIMARY;
            return true;
        }
    }
    return false;
}

void ArkTSUtils::ParseBlurOption(const EcmaVM* vm, const Local<JSValueRef>& jsBlurOption, BlurOption& blurOption)
{
    auto blurOptionProperty = GetProperty(vm, jsBlurOption, "grayscale");
    if (blurOptionProperty->IsArray(vm)) {
        Local<panda::ArrayRef> params = blurOptionProperty->ToObject(vm);
        auto grey1 = panda::ArrayRef::GetValueAt(vm, params, 0)->ToNumber(vm)->Int32Value(vm);
        auto grey2 = panda::ArrayRef::GetValueAt(vm, params, 1)->ToNumber(vm)->Int32Value(vm);
        std::vector<float> greyVec(2); // 2 number
        greyVec[0] = grey1;
        greyVec[1] = grey2;
        blurOption.grayscale = greyVec;
    }
}

void ArkTSUtils::ParseInactiveColor(const EcmaVM* vm, const Local<JSValueRef>& jsOption, BlurStyleOption& styleOption)
{
    RefPtr<ResourceObject> inactiveColorResObj;
    if (ParseJsColor(vm, GetProperty(vm, jsOption, "inactiveColor"), styleOption.inactiveColor, inactiveColorResObj)) {
        styleOption.isValidColor = true;
    }

    if (SystemProperties::ConfigChangePerform() && inactiveColorResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, BlurStyleOption& styleOption) {
            Color inactiveColorValue;
            ResourceParseUtils::ParseResColor(resObj, inactiveColorValue);
            styleOption.inactiveColor = inactiveColorValue;
            styleOption.isValidColor = true;
        };
        styleOption.AddResource(
            "backgroundBlurStyle.backgroundBlurStyleOptions.inactiveColor", inactiveColorResObj, std::move(updateFunc));
    }
}

void ArkTSUtils::ParseBlurStyleOption(const EcmaVM* vm, const Local<JSValueRef>& jsOption, BlurStyleOption& styleOption)
{
    if (jsOption->IsUndefined()) {
        return;
    }
    auto colorMode = static_cast<int32_t>(ThemeColorMode::SYSTEM);
    ParseJsInt32(vm, GetProperty(vm, jsOption, "colorMode"), colorMode);
    if (colorMode >= static_cast<int32_t>(ThemeColorMode::SYSTEM) &&
        colorMode <= static_cast<int32_t>(ThemeColorMode::DARK)) {
        styleOption.colorMode = static_cast<ThemeColorMode>(colorMode);
    }
    auto adaptiveColor = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    ParseJsInt32(vm, GetProperty(vm, jsOption, "adaptiveColor"), adaptiveColor);
    if (adaptiveColor >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        adaptiveColor <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        styleOption.adaptiveColor = static_cast<AdaptiveColor>(adaptiveColor);
    }

    // policy
    auto policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    ParseJsInt32(vm, GetProperty(vm, jsOption, "policy"), policy);
    if (policy >= static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) &&
        policy <= static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        styleOption.policy = static_cast<BlurStyleActivePolicy>(policy);
    }

    // blurType
    auto blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    ParseJsInt32(vm, GetProperty(vm, jsOption, "type"), blurType);
    if (blurType >= static_cast<int32_t>(BlurType::WITHIN_WINDOW) &&
        blurType <= static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        styleOption.blurType = static_cast<BlurType>(blurType);
    }

    // inactiveColor
    ParseInactiveColor(vm, jsOption, styleOption);

    // scale
    if (GetProperty(vm, jsOption, "scale")->IsNumber()) {
        double scale = GetProperty(vm, jsOption, "scale")->ToNumber(vm)->Int32Value(vm);
        styleOption.scale = std::clamp(scale, 0.0, 1.0);
    }

    if (GetProperty(vm, jsOption, "blurOptions")->IsObject(vm)) {
        auto jsBlurOption = GetProperty(vm, jsOption, "blurOptions")->ToObject(vm);
        BlurOption blurOption;
        ParseBlurOption(vm, jsBlurOption, blurOption);
        styleOption.blurOption = blurOption;
    }
}

void ArkTSUtils::JsOpacity(const EcmaVM* vm, const Local<JSValueRef>& jsOpacity)
{
    ViewAbstractModel::GetInstance()->RemoveResObj("viewAbstract.opacity");
    double opacity = 0.0;
    RefPtr<ResourceObject> opacityResObj;
    if (!ParseJsDouble(vm, jsOpacity, opacity, opacityResObj)) {
        ViewAbstractModel::GetInstance()->SetOpacity(1.0f);
        return;
    }
    if (SystemProperties::ConfigChangePerform() && opacityResObj) {
        ViewAbstractModel::GetInstance()->CreateWithOpacityResourceObj(opacityResObj);
        return;
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        opacity = std::clamp(opacity, 0.0, 1.0);
    } else {
        if (opacity > 1.0 || LessNotEqual(opacity, 0.0)) {
            opacity = 1.0;
        }
    }
    ViewAbstractModel::GetInstance()->SetOpacity(opacity);
}

void ArkTSUtils::GetEffectOptionColor(const EcmaVM* vm, const Local<JSValueRef>& jsOption, EffectOption& effectOption)
{
    if (!SystemProperties::ConfigChangePerform()) {
        ParseJsColor(vm, GetProperty(vm, jsOption, "color"), effectOption.color);
    } else {
        RefPtr<ResourceObject> colorResObj;
        ParseJsColor(vm, GetProperty(vm, jsOption, "color"), effectOption.color, colorResObj);
        if (colorResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, EffectOption& effectOption) {
                Color effectOptionColor;
                ResourceParseUtils::ParseResColor(colorResObj, effectOptionColor);
                effectOption.color = effectOptionColor;
            };
            effectOption.AddResource("backgroundEffect.color", colorResObj, std::move(updateFunc));
        }
    }
}

void ArkTSUtils::GetEffectOptionInactiveColorUpdate(
    const RefPtr<ResourceObject>& inactiveColorObj, EffectOption& effectOption)
{
    if (inactiveColorObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& inactiveColorObj, EffectOption& effectOption) {
            Color effectOptionInactiveColor;
            ResourceParseUtils::ParseResColor(inactiveColorObj, effectOptionInactiveColor);
            effectOption.inactiveColor = effectOptionInactiveColor;
        };
        effectOption.AddResource("backgroundEffect.inactiveColor", inactiveColorObj, std::move(updateFunc));
    }
}

void ArkTSUtils::GetEffectOptionInactiveColor(
    const EcmaVM* vm, const Local<JSValueRef>& jsOption, EffectOption& effectOption)
{
    if (!SystemProperties::ConfigChangePerform()) {
        if (ParseJsColor(vm, GetProperty(vm, jsOption, "inactiveColor"), effectOption.inactiveColor)) {
            effectOption.isValidColor = true;
        }
    } else {
        RefPtr<ResourceObject> inactiveColorObj;
        if (ParseJsColor(
                vm, GetProperty(vm, jsOption, "inactiveColor"), effectOption.inactiveColor, inactiveColorObj)) {
            GetEffectOptionInactiveColorUpdate(inactiveColorObj, effectOption);
            effectOption.isValidColor = true;
        }
    }
}

void ArkTSUtils::ParseEffectOption(const EcmaVM* vm, const Local<JSValueRef>& jsOption, EffectOption& effectOption)
{
    CHECK_NULL_VOID(vm);
    CalcDimension radius;
    if (!ParseJsDimensionVp(vm, GetProperty(vm, jsOption, "radius"), radius) || LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    effectOption.radius = radius;

    double saturation = 1.0f;
    if (GetProperty(vm, jsOption, "saturation")->IsNumber()) {
        saturation = GetProperty(vm, jsOption, "saturation")->ToNumber(vm)->Value();
        saturation = (saturation > 0.0f || NearZero(saturation)) ? saturation : 1.0f;
    }
    effectOption.saturation = saturation;

    double brightness = 1.0f;
    if (GetProperty(vm, jsOption, "brightness")->IsNumber()) {
        brightness = GetProperty(vm, jsOption, "brightness")->ToNumber(vm)->Int32Value(vm);
        brightness = (brightness > 0.0f || NearZero(brightness)) ? brightness : 1.0f;
    }
    effectOption.brightness = brightness;

    GetEffectOptionColor(vm, jsOption, effectOption);

    auto adaptiveColorValue = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    ParseJsInt32(vm, GetProperty(vm, jsOption, "adaptiveColor"), adaptiveColorValue);
    if (adaptiveColorValue >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
        adaptiveColorValue <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
        adaptiveColor = static_cast<AdaptiveColor>(adaptiveColorValue);
    }
    effectOption.adaptiveColor = adaptiveColor;

    // policy
    auto policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    ParseJsInt32(vm, GetProperty(vm, jsOption, "policy"), policy);
    if (policy >= static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) &&
        policy <= static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        effectOption.policy = static_cast<BlurStyleActivePolicy>(policy);
    }

    // blurType
    auto blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    ParseJsInt32(vm, GetProperty(vm, jsOption, "type"), blurType);
    if (blurType >= static_cast<int32_t>(BlurType::WITHIN_WINDOW) &&
        blurType <= static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        effectOption.blurType = static_cast<BlurType>(blurType);
    }

    // inactiveColor
    GetEffectOptionInactiveColor(vm, jsOption, effectOption);

    BlurOption blurOption;
    if (GetProperty(vm, jsOption, "blurOptions")->IsObject(vm)) {
        auto jsBlurOption = GetProperty(vm, jsOption, "blurOptions")->ToString(vm);
        ParseBlurOption(vm, jsBlurOption, blurOption);
        effectOption.blurOption = blurOption;
    }
}

template<typename T>
T ArkTSUtils::GetPropertyValue(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, int32_t propertyIndex, T defaultValue)
{
    static_assert(
        !std::is_const_v<T> && !std::is_reference_v<T>, "Cannot convert value to reference or cv-qualified types!");

    Local<panda::StringRef> stringRef = panda::ExternalStringCache::GetCachedString(vm, propertyIndex);
    auto jsObj = jsValue->ToObject(vm);
    Local<JSValueRef> valueRef = jsObj->Get(vm, stringRef);
    if constexpr (std::is_same<T, bool>::value) {
        return valueRef->IsBoolean() ? valueRef->BooleaValue(vm) : defaultValue;
    } else if constexpr (std::is_arithmetic<T>::value) {
        return valueRef->IsNumber() ? Framework::JsiValueConvertor::fromJsiValue<T>(vm, valueRef) : defaultValue;
    } else if constexpr (std::is_same_v<T, std::string>) {
        return valueRef->IsString(vm) ? valueRef->ToString(vm)->ToString(vm) : defaultValue;
    } else {
        LOGW("Get property value failed.");
    }
    return defaultValue;
}

bool ArkTSUtils::ParseShadowProps(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, Shadow& shadow, const bool configChangePerform, bool needResObj)
{
    CHECK_NULL_RETURN(vm, false);
    int32_t shadowStyle = 0;
    if (ArkTSUtils::ParseJsIntegerWithResource(vm, jsValue, shadowStyle)) {
        auto style = static_cast<ShadowStyle>(shadowStyle);
        return GetShadowFromTheme(vm, style, shadow, configChangePerform);
    }
    if (!jsValue->IsObject(vm)) {
        return false;
    }
    auto jsObj = jsValue->ToObject(vm);
    double radius = 0.0;
    ParseShadowPropsUpdate(vm, jsObj, radius, shadow);
    if (LessNotEqual(radius, 0.0)) {
        radius = 0.0;
    }
    shadow.SetBlurRadius(radius);
    ParseShadowOffsetXY(vm, jsObj, shadow);

    Color color;
    ShadowColorStrategy shadowColorStrategy;
    auto jsColor = ArkTSUtils::GetProperty(vm, jsObj, static_cast<int32_t>(Framework::ArkUIIndex::COLOR));
    RefPtr<ResourceObject> colorResObj;
    if (ParseJsShadowColorStrategy(vm, jsColor, shadowColorStrategy)) {
        shadow.SetShadowColorStrategy(shadowColorStrategy);
    } else if (ArkTSUtils::ParseJsColor(vm, jsColor, color, colorResObj)) {
        if (needResObj && colorResObj) {
            auto jsObj = jsColor->ToObject(vm);
            CompleteResourceObject(vm, jsObj);
            colorResObj = GetResourceObject(vm, jsObj);
        }
        if ((SystemProperties::ConfigChangePerform() || needResObj) && colorResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, Shadow& shadow) {
                Color colorValue;
                ResourceParseUtils::ParseResColor(colorResObj, colorValue);
                shadow.SetColor(colorValue);
            };
            shadow.AddResource("shadow.colorValue", colorResObj, std::move(updateFunc));
        }
        shadow.SetColor(color);
    }

    int32_t type = static_cast<int32_t>(ShadowType::COLOR);
    ArkTSUtils::ParseJsIntegerWithResource(
        vm, ArkTSUtils::GetProperty(vm, jsObj, static_cast<int32_t>(Framework::ArkUIIndex::TYPE)), type);
    if (type != static_cast<int32_t>(ShadowType::BLUR)) {
        type = static_cast<int32_t>(ShadowType::COLOR);
    }
    shadow.SetShadowType(static_cast<ShadowType>(type));
    bool isFilled = GetPropertyValue<bool>(vm, jsObj, static_cast<int32_t>(Framework::ArkUIIndex::FILL), false);
    shadow.SetIsFilled(isFilled);
    return true;
}

void GetBorderRadiusByLengthMetrics(
    EcmaVM* vm, const char* key, const panda::Local<panda::ObjectRef>& object, CalcDimension& radius)
{
    if (object->Has(vm, panda::StringRef::NewFromUtf8(vm, key))) {
        panda::Local<panda::JSValueRef> propertyValue = object->Get(vm, panda::StringRef::NewFromUtf8(vm, key));
        if (propertyValue->IsObject(vm)) {
            panda::Local<panda::ObjectRef> startObj = propertyValue->ToObject(vm);
            ArkTSUtils::ParseJsLengthMetrics(vm, startObj, radius);
        }
    }
}

void GetBorderRadiusResObj(EcmaVM* vm, const char* key, panda::Local<panda::ObjectRef> object, CalcDimension& radius,
    RefPtr<ResourceObject>& resObj)
{
    auto property = object->Get(vm, panda::StringRef::NewFromUtf8(vm, key));
    ArkTSUtils::ParseJsDimensionVp(vm, property, radius, resObj);
}

bool ArkTSUtils::ParseAllBorderRadiuses(EcmaVM* vm, panda::Local<panda::ObjectRef> object,
    BorderRadiusOption& borderRadius, std::shared_ptr<TextBackgroundStyle>& textBackgroundStyle)
{
    if (object->Has(vm, panda::StringRef::NewFromUtf8(vm, TOP_START_PROPERTY)) ||
        object->Has(vm, panda::StringRef::NewFromUtf8(vm, TOP_END_PROPERTY)) ||
        object->Has(vm, panda::StringRef::NewFromUtf8(vm, BOTTOM_START_PROPERTY)) ||
        object->Has(vm, panda::StringRef::NewFromUtf8(vm, BOTTOM_END_PROPERTY))) {
        CalcDimension topStart;
        CalcDimension topEnd;
        CalcDimension bottomStart;
        CalcDimension bottomEnd;
        GetBorderRadiusByLengthMetrics(vm, TOP_START_PROPERTY, object, topStart);
        GetBorderRadiusByLengthMetrics(vm, TOP_END_PROPERTY, object, topEnd);
        GetBorderRadiusByLengthMetrics(vm, BOTTOM_START_PROPERTY, object, bottomStart);
        GetBorderRadiusByLengthMetrics(vm, BOTTOM_END_PROPERTY, object, bottomEnd);
        borderRadius.topLeft = topStart;
        borderRadius.topRight = topEnd;
        borderRadius.bottomLeft = bottomStart;
        borderRadius.bottomRight = bottomEnd;
        return true;
    }
    RefPtr<ResourceObject> resObjTopLeft;
    RefPtr<ResourceObject> resObjTopRight;
    RefPtr<ResourceObject> resObjBottomLeft;
    RefPtr<ResourceObject> resObjBottomRight;
    GetBorderRadiusResObj(vm, "topLeft", object, borderRadius.topLeft, resObjTopLeft);
    GetBorderRadiusResObj(vm, "topRight", object, borderRadius.topRight, resObjTopRight);
    GetBorderRadiusResObj(vm, "bottomLeft", object, borderRadius.bottomLeft, resObjBottomLeft);
    GetBorderRadiusResObj(vm, "bottomRight", object, borderRadius.bottomRight, resObjBottomRight);

    ArkTSUtils::RegisterTextBackgroundStyleResource(
        textBackgroundStyle, resObjTopLeft, resObjTopRight, resObjBottomLeft, resObjBottomRight);
    return false;
}

#define ADDRESOURCE_UPDATE_FUNC(property, resObj, radiusMember, resourceName)                 \
    RefPtr<ResourceObject> resObj;                                                            \
    auto value##property = object->Get(vm, panda::StringRef::NewFromUtf8(vm, #property));               \
    ArkTSUtils::ParseJsDimensionVp(vm, value##property, property, resObj);                              \
    if (resObj) {                                                                             \
        auto&& updateFunc = [](const RefPtr<ResourceObject>&(resObj),                         \
                                NG::BorderRadiusProperty& borderRadiusProperty) {             \
            CalcDimension property;                                                           \
            ResourceParseUtils::ParseResDimensionVp(resObj, property);                        \
            if (LessNotEqual((property).Value(), 0.0f)) {                                     \
                (property).Reset();                                                           \
            }                                                                                 \
            borderRadiusProperty.radiusMember = property;                                     \
        };                                                                                    \
        borderRadius.AddResource(resourceName, resObj, std::move(updateFunc));                \
    }

inline panda::Local<panda::StringRef> GetCachedString(EcmaVM* vm, Framework::ArkUIIndex index)
{
    return panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(index));
}

void ParseAllBorderRadiuses(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& object, NG::BorderRadiusProperty& borderRadius)
{
    CalcDimension topLeft;
    CalcDimension topRight;
    CalcDimension bottomLeft;
    CalcDimension bottomRight;
    bool hasSetBorderRadius = false;
    if (object->Has(vm, GetCachedString(vm, Framework::ArkUIIndex::TOP_START)) ||
        object->Has(vm, GetCachedString(vm, Framework::ArkUIIndex::TOP_END)) ||
        object->Has(vm, GetCachedString(vm, Framework::ArkUIIndex::BOTTOM_START)) ||
        object->Has(vm, GetCachedString(vm, Framework::ArkUIIndex::BOTTOM_END))) {
        CalcDimension topStart;
        CalcDimension topEnd;
        CalcDimension bottomStart;
        CalcDimension bottomEnd;
        GetBorderRadiusByLengthMetrics(vm, TOP_START_PROPERTY, object, topStart);
        GetBorderRadiusByLengthMetrics(vm, TOP_END_PROPERTY, object, topEnd);
        GetBorderRadiusByLengthMetrics(vm, BOTTOM_START_PROPERTY, object, bottomStart);
        GetBorderRadiusByLengthMetrics(vm, BOTTOM_END_PROPERTY, object, bottomEnd);
        topLeft = topStart;
        topRight = topEnd;
        bottomLeft = bottomStart;
        bottomRight = bottomEnd;
        hasSetBorderRadius = true;
    } else {
        ADDRESOURCE_UPDATE_FUNC(topLeft, topLeftResObj, radiusTopLeft, "borderRadius.topLeft");
        ADDRESOURCE_UPDATE_FUNC(topRight, topRightResObj, radiusTopRight, "borderRadius.topRight");
        ADDRESOURCE_UPDATE_FUNC(bottomLeft, bottomLeftResObj, radiusBottomLeft, "borderRadius.bottomLeft");
        ADDRESOURCE_UPDATE_FUNC(bottomRight, bottomRightResObj, radiusBottomRight, "borderRadius.bottomRight");
    }
    if (LessNotEqual(topLeft.Value(), 0.0f)) {
        topLeft.Reset();
    }
    if (LessNotEqual(topRight.Value(), 0.0f)) {
        topRight.Reset();
    }
    if (LessNotEqual(bottomLeft.Value(), 0.0f)) {
        bottomLeft.Reset();
    }
    if (LessNotEqual(bottomRight.Value(), 0.0f)) {
        bottomRight.Reset();
    }
    auto isRtl = hasSetBorderRadius && AceApplicationInfo::GetInstance().IsRightToLeft();
    borderRadius.radiusTopLeft = isRtl ? topRight : topLeft;
    borderRadius.radiusTopRight = isRtl ? topLeft : topRight;
    borderRadius.radiusBottomLeft = isRtl ? bottomRight : bottomLeft;
    borderRadius.radiusBottomRight = isRtl ? bottomLeft : bottomRight;
    borderRadius.multiValued = true;
}

bool ArkTSUtils::ParseAllBorderRadiuses(
    EcmaVM* vm, panda::Local<panda::ObjectRef> object, BorderRadiusOption& borderRadius)
{
    std::shared_ptr<TextBackgroundStyle> textBackgroundStyle = std::make_shared<TextBackgroundStyle>();
    return ParseAllBorderRadiuses(vm, object, borderRadius, textBackgroundStyle);
}

void RegisterRadiusesResObj(
    const std::string& key, NG::BorderRadiusProperty& borderRadius, const RefPtr<ResourceObject>& resObj)
{
    if (!resObj) {
        return;
    }
    auto updateFunc = [key](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadius) {
        CalcDimension result;
        ResourceParseUtils::ParseResDimensionVp(resObj, result);
        if (key == "borderRadius.topLeft") {
            borderRadius.radiusTopLeft = result;
        } else if (key == "borderRadius.topRight") {
            borderRadius.radiusTopRight = result;
        } else if (key == "borderRadius.bottomLeft") {
            borderRadius.radiusBottomLeft = result;
        } else if (key == "borderRadius.bottomRight") {
            borderRadius.radiusBottomRight = result;
        }
    };
    borderRadius.AddResource(key, resObj, std::move(updateFunc));
}

void ParseAllBorderRadiusesResObj(NG::BorderRadiusProperty& borderRadius, const RefPtr<ResourceObject>& topLeftResObj,
    const RefPtr<ResourceObject>& topRightResObj, const RefPtr<ResourceObject>& bottomLeftResObj,
    const RefPtr<ResourceObject>& bottomRightResObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    borderRadius.resMap_.clear();
    RegisterRadiusesResObj("borderRadius.topLeft", borderRadius, topLeftResObj);
    RegisterRadiusesResObj("borderRadius.topRight", borderRadius, topRightResObj);
    RegisterRadiusesResObj("borderRadius.bottomLeft", borderRadius, bottomLeftResObj);
    RegisterRadiusesResObj("borderRadius.bottomRight", borderRadius, bottomRightResObj);
}

NG::BorderRadiusProperty ArkTSUtils::BorderRadiusProperty(EcmaVM* vm, panda::Local<panda::ObjectRef> object,
    BorderRadiusOption& borderRadius)
{
    NG::BorderRadiusProperty borderRadiusProperty;
    if (SystemProperties::ConfigChangePerform()) {
        return borderRadiusProperty;
    }
    RefPtr<ResourceObject> topLeftResObj;
    RefPtr<ResourceObject> topRightResObj;
    RefPtr<ResourceObject> bottomLeftResObj;
    RefPtr<ResourceObject> bottomRightResObj;

    GetBorderRadiusResObj(vm, "topLeft", object, borderRadius.topLeft, topLeftResObj);
    GetBorderRadiusResObj(vm, "topRight", object, borderRadius.topRight, topRightResObj);
    GetBorderRadiusResObj(vm, "bottomLeft", object, borderRadius.bottomLeft, bottomLeftResObj);
    GetBorderRadiusResObj(vm, "bottomRight", object, borderRadius.bottomRight, bottomRightResObj);
    borderRadiusProperty.radiusTopLeft = borderRadius.topLeft;
    borderRadiusProperty.radiusTopRight = borderRadius.topRight;
    borderRadiusProperty.radiusBottomLeft = borderRadius.bottomLeft;
    borderRadiusProperty.radiusBottomRight = borderRadius.bottomRight;
    borderRadiusProperty.multiValued = true;
    ParseAllBorderRadiusesResObj(
        borderRadiusProperty, topLeftResObj, topRightResObj, bottomLeftResObj, bottomRightResObj);
    return borderRadiusProperty;
}

BorderStyleOption ArkTSUtils::ParseBorderStyle(EcmaVM* vm, panda::Local<panda::ObjectRef> object)
{
    BorderStyleOption borderStyleOption;
    std::optional<BorderStyle> styleLeft;
    std::optional<BorderStyle> styleRight;
    std::optional<BorderStyle> styleTop;
    std::optional<BorderStyle> styleBottom;
    auto leftValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::LEFT));
    if (leftValue->IsNumber()) {
        styleLeft = ArkTSUtils::ConvertBorderStyle(leftValue->ToNumber(vm)->Int32Value(vm));
    }
    auto rightValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::RIGHT));
    if (rightValue->IsNumber()) {
        styleRight = ArkTSUtils::ConvertBorderStyle(rightValue->ToNumber(vm)->Int32Value(vm));
    }
    auto topValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::TOP));
    if (topValue->IsNumber()) {
        styleTop = ArkTSUtils::ConvertBorderStyle(topValue->ToNumber(vm)->Int32Value(vm));
    }
    auto bottomValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::BOTTOM));
    if (bottomValue->IsNumber()) {
        styleBottom = ArkTSUtils::ConvertBorderStyle(bottomValue->ToNumber(vm)->Int32Value(vm));
    }
    borderStyleOption.styleLeft = styleLeft;
    borderStyleOption.styleRight = styleRight;
    borderStyleOption.styleTop = styleTop;
    borderStyleOption.styleBottom = styleBottom;
    return borderStyleOption;
}

LayoutCalPolicy ArkTSUtils::ParseLayoutPolicy(const std::string& layoutPolicy)
{
    if (layoutPolicy == "matchParent") {
        return LayoutCalPolicy::MATCH_PARENT;
    }
    if (layoutPolicy == "wrapContent") {
        return LayoutCalPolicy::WRAP_CONTENT;
    }
    if (layoutPolicy == "fixAtIdealSize") {
        return LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    }
    return LayoutCalPolicy::NO_MATCH;
}

void CheckDimensionUnit(CalcDimension& checkDimension, bool notPercent, bool notNegative)
{
    if (notPercent && checkDimension.Unit() == DimensionUnit::PERCENT) {
        checkDimension.Reset();
        return;
    }
    if (notNegative && checkDimension.IsNegative()) {
        checkDimension.Reset();
        return;
    }
}

void ParseEdgeWidths(EcmaVM* vm, const panda::Local<panda::ObjectRef>& object, CommonCalcDimension& commonCalcDimension,
    bool notNegative)
{
    CalcDimension left;
    auto leftValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::LEFT));
    if (ArkTSUtils::ParseJsDimensionVp(vm, leftValue, left)) {
        CheckDimensionUnit(left, true, notNegative);
        commonCalcDimension.left = left;
    }
    CalcDimension right;
    auto rightValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::RIGHT));
    if (ArkTSUtils::ParseJsDimensionVp(vm, rightValue, right)) {
        CheckDimensionUnit(right, true, notNegative);
        commonCalcDimension.right = right;
    }
    CalcDimension top;
    auto topValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::TOP));
    if (ArkTSUtils::ParseJsDimensionVp(vm, topValue, top)) {
        CheckDimensionUnit(top, true, notNegative);
        commonCalcDimension.top = top;
    }
    CalcDimension bottom;
    auto bottomValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::BOTTOM));
    if (ArkTSUtils::ParseJsDimensionVp(vm, bottomValue, bottom)) {
        CheckDimensionUnit(bottom, true, notNegative);
        commonCalcDimension.bottom = bottom;
    }
}

bool ArkTSUtils::ParseCommonEdgeWidths(EcmaVM* vm, const panda::Local<panda::ObjectRef>& object,
    CommonCalcDimension& commonCalcDimension, bool notNegative)
{
    if (ArkTSUtils::CheckLengthMetrics(vm, object)) {
        LocalizedCalcDimension localizedCalcDimension;
        ParseLocalizedEdgeWidths(vm, object, localizedCalcDimension, notNegative);
        commonCalcDimension.top = localizedCalcDimension.top;
        commonCalcDimension.bottom = localizedCalcDimension.bottom;
        commonCalcDimension.left = localizedCalcDimension.start;
        commonCalcDimension.right = localizedCalcDimension.end;
        return true;
    }
    if (!SystemProperties::ConfigChangePerform()) {
        ParseEdgeWidths(vm, object, commonCalcDimension, notNegative);
    }
    return false;
}

void RegisterEdgesWidthResObj(
    const std::string& key, NG::BorderWidthProperty& borderWidth, const RefPtr<ResourceObject>& resObj)
{
    if (!resObj) {
        return;
    }
    auto updateFunc = [key](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& borderWidth) {
        CalcDimension result;
        ResourceParseUtils::ParseResDimensionVp(resObj, result);
        if (key == "borderWidth.left") {
            borderWidth.leftDimen = result;
        } else if (key == "borderWidth.right") {
            borderWidth.rightDimen = result;
        } else if (key == "borderWidth.top") {
            borderWidth.topDimen = result;
        } else if (key == "borderWidth.bottom") {
            borderWidth.bottomDimen = result;
        }
        borderWidth.multiValued = true;
    };
    borderWidth.AddResource(key, resObj, std::move(updateFunc));
}

void ParseEdgeWidthsResObjFunc(NG::BorderWidthProperty& borderWidth, RefPtr<ResourceObject> leftResObj,
    RefPtr<ResourceObject> rightResObj, RefPtr<ResourceObject> topResObj, RefPtr<ResourceObject> bottomResObj)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    borderWidth.resMap_.clear();
    RegisterEdgesWidthResObj("borderWidth.left", borderWidth, leftResObj);
    RegisterEdgesWidthResObj("borderWidth.right", borderWidth, rightResObj);
    RegisterEdgesWidthResObj("borderWidth.top", borderWidth, topResObj);
    RegisterEdgesWidthResObj("borderWidth.bottom", borderWidth, bottomResObj);
}

void ArkTSUtils::ParseEdgeWidthsResObj(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& object, NG::BorderWidthProperty& borderWidth, bool notNegative)
{
    CalcDimension left;
    RefPtr<ResourceObject> leftResObj;
    auto leftValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::LEFT));
    if (ArkTSUtils::ParseJsDimensionVp(vm, leftValue, left, leftResObj)) {
        CheckDimensionUnit(left, true, notNegative);
        borderWidth.leftDimen = left;
        borderWidth.multiValued = true;
    }
    CalcDimension right;
    RefPtr<ResourceObject> rightResObj;
    auto rightValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::RIGHT));
    if (ArkTSUtils::ParseJsDimensionVp(vm, rightValue, right, rightResObj)) {
        CheckDimensionUnit(right, true, notNegative);
        borderWidth.rightDimen = right;
        borderWidth.multiValued = true;
    }
    CalcDimension top;
    RefPtr<ResourceObject> topResObj;
    auto topValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::TOP));
    if (ArkTSUtils::ParseJsDimensionVp(vm, topValue, top, topResObj)) {
        CheckDimensionUnit(top, true, notNegative);
        borderWidth.topDimen = top;
        borderWidth.multiValued = true;
    }
    CalcDimension bottom;
    RefPtr<ResourceObject> bottomResObj;
    auto bottomValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::BOTTOM));
    if (ArkTSUtils::ParseJsDimensionVp(vm, bottomValue, bottom, bottomResObj)) {
        CheckDimensionUnit(bottom, true, notNegative);
        borderWidth.bottomDimen = bottom;
        borderWidth.multiValued = true;
    }
    ParseEdgeWidthsResObjFunc(borderWidth, leftResObj, rightResObj, topResObj, bottomResObj);
}

void ArkTSUtils::ParseLocalizedEdgeWidths(EcmaVM* vm, const panda::Local<panda::ObjectRef>& object,
    LocalizedCalcDimension& localizedCalcDimension, bool notNegative)
{
    auto jsStart = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::START));
    if (jsStart->IsObject(vm)) {
        auto startObj = jsStart->ToObject(vm);
        CalcDimension calcDimension;
        if (ArkTSUtils::ParseJsLengthMetrics(vm, startObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, true, notNegative);
            localizedCalcDimension.start = calcDimension;
        }
    }
    auto jsEnd = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::END));
    if (jsEnd->IsObject(vm)) {
        auto endObj = jsEnd->ToObject(vm);
        CalcDimension calcDimension;
        if (ArkTSUtils::ParseJsLengthMetrics(vm, endObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, true, notNegative);
            localizedCalcDimension.end = calcDimension;
        }
    }
    auto jsTop = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::TOP));
    if (jsTop->IsObject(vm)) {
        auto topObj = jsTop->ToObject(vm);
        CalcDimension calcDimension;
        if (ArkTSUtils::ParseJsLengthMetrics(vm, topObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, true, notNegative);
            localizedCalcDimension.top = calcDimension;
        }
    }
    auto jsBottom = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::BOTTOM));
    if (jsBottom->IsObject(vm)) {
        auto bottomObj = jsBottom->ToObject(vm);
        CalcDimension calcDimension;
        if (ArkTSUtils::ParseJsLengthMetrics(vm, bottomObj, calcDimension)) {
            CheckDimensionUnit(calcDimension, true, notNegative);
            localizedCalcDimension.bottom = calcDimension;
        }
    }
}

bool ArkTSUtils::IsBorderWidthObjUndefined(EcmaVM* vm, const panda::Local<panda::JSValueRef>& args)
{
    if (!args->IsObject(vm)) {
        return false;
    }
    panda::Local<panda::ObjectRef> obj = args->ToObject(vm);
    if (obj->IsUndefined()) {
        return true;
    }
    // filter dynamic $r raw input
    if (obj->Has(vm, panda::StringRef::NewFromUtf8(vm, "id"))) {
        return false;
    }
    if ((!obj->Has(vm, panda::StringRef::NewFromUtf8(vm, TOP_PROPERTY)) ||
            obj->Get(vm, panda::StringRef::NewFromUtf8(vm, TOP_PROPERTY))->IsUndefined()) &&
        (!obj->Has(vm, panda::StringRef::NewFromUtf8(vm, RIGHT_PROPERTY)) ||
            obj->Get(vm, panda::StringRef::NewFromUtf8(vm, RIGHT_PROPERTY))->IsUndefined()) &&
        (!obj->Has(vm, panda::StringRef::NewFromUtf8(vm, BOTTOM_PROPERTY)) ||
            obj->Get(vm, panda::StringRef::NewFromUtf8(vm, BOTTOM_PROPERTY))->IsUndefined()) &&
        (!obj->Has(vm, panda::StringRef::NewFromUtf8(vm, LEFT_PROPERTY)) ||
            obj->Get(vm, panda::StringRef::NewFromUtf8(vm, LEFT_PROPERTY))->IsUndefined()) &&
        (!obj->Has(vm, panda::StringRef::NewFromUtf8(vm, START_PROPERTY)) ||
            obj->Get(vm, panda::StringRef::NewFromUtf8(vm, START_PROPERTY))->IsUndefined()) &&
        (!obj->Has(vm, panda::StringRef::NewFromUtf8(vm, END_PROPERTY)) ||
            obj->Get(vm, panda::StringRef::NewFromUtf8(vm, END_PROPERTY))->IsUndefined())) {
        return true;
    }

    return false;
}

void RegisterLocalizedBorderColor(
    const std::string& key, NG::BorderColorProperty& borderColors, const RefPtr<ResourceObject>& resObj)
{
    if (!resObj) {
        return;
    }
    auto updateFunc = [key](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
        Color result;
        ResourceParseUtils::ParseResColor(resObj, result);
        if (key == "borderColor.start") {
            borderColors.startColor = result;
        } else if (key == "borderColor.end") {
            borderColors.endColor = result;
        } else if (key == "borderColor.top") {
            borderColors.topColor = result;
        } else if (key == "borderColor.bottom") {
            borderColors.bottomColor = result;
        }
    };
    borderColors.AddResource(key, resObj, std::move(updateFunc));
}

NG::BorderColorProperty ArkTSUtils::GetLocalizedBorderColor(const CommonColor& commonColor)
{
    NG::BorderColorProperty borderColors;
    borderColors.startColor = commonColor.left;
    borderColors.endColor = commonColor.right;
    borderColors.topColor = commonColor.top;
    borderColors.bottomColor = commonColor.bottom;
    if (!SystemProperties::ConfigChangePerform()) {
        return borderColors;
    }
    RegisterLocalizedBorderColor("borderColor.start", borderColors, commonColor.leftResObj);
    RegisterLocalizedBorderColor("borderColor.end", borderColors, commonColor.rightResObj);
    RegisterLocalizedBorderColor("borderColor.top", borderColors, commonColor.topResObj);
    RegisterLocalizedBorderColor("borderColor.bottom", borderColors, commonColor.bottomResObj);
    borderColors.multiValued = true;
    return borderColors;
}

void ParseEdgeColors(EcmaVM* vm, const panda::Local<panda::ObjectRef>& object, CommonColor& commonColor)
{
    Color left;
    RefPtr<ResourceObject> leftResObj;
    auto leftValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::LEFT));
    if (ArkTSUtils::ParseJsColor(vm, leftValue, left, leftResObj)) {
        commonColor.left = left;
    }
    Color right;
    RefPtr<ResourceObject> rightResObj;
    auto rightValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::RIGHT));
    if (ArkTSUtils::ParseJsColor(vm, rightValue, right, rightResObj)) {
        commonColor.right = right;
    }
    Color top;
    RefPtr<ResourceObject> topResObj;
    auto topValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::TOP));
    if (ArkTSUtils::ParseJsColor(vm, topValue, top, topResObj)) {
        commonColor.top = top;
    }
    Color bottom;
    RefPtr<ResourceObject> bottomResObj;
    auto bottomValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::BOTTOM));
    if (ArkTSUtils::ParseJsColor(vm, bottomValue, bottom, bottomResObj)) {
        commonColor.bottom = bottom;
    }
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (leftResObj) {
        commonColor.leftResObj = leftResObj;
    }
    if (rightResObj) {
        commonColor.rightResObj = rightResObj;
    }
    if (topResObj) {
        commonColor.topResObj = topResObj;
    }
    if (bottomResObj) {
        commonColor.bottomResObj = bottomResObj;
    }
}

void ParseLocalizedEdgeColors(EcmaVM* vm, const panda::Local<panda::ObjectRef>& object, LocalizedColor& localizedColor)
{
    Color start;
    RefPtr<ResourceObject> startResObj;
    auto startValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::START));
    if (ArkTSUtils::ParseJsColor(vm, startValue, start, startResObj)) {
        localizedColor.start = start;
    }
    Color end;
    RefPtr<ResourceObject> endResObj;
    auto endValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::END));
    if (ArkTSUtils::ParseJsColor(vm, endValue, end, endResObj)) {
        localizedColor.end = end;
    }
    Color top;
    RefPtr<ResourceObject> topResObj;
    auto topValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::TOP));
    if (ArkTSUtils::ParseJsColor(vm, topValue, top, topResObj)) {
        localizedColor.top = top;
    }
    Color bottom;
    RefPtr<ResourceObject> bottomResObj;
    auto bottomValue = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::BOTTOM));
    if (ArkTSUtils::ParseJsColor(vm, bottomValue, bottom, bottomResObj)) {
        localizedColor.bottom = bottom;
    }
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (startResObj) {
        localizedColor.startResObj = startResObj;
    }
    if (endResObj) {
        localizedColor.endResObj = endResObj;
    }
    if (topResObj) {
        localizedColor.topResObj = topResObj;
    }
    if (bottomResObj) {
        localizedColor.bottomResObj = bottomResObj;
    }
}

bool ArkTSUtils::ParseCommonEdgeColors(EcmaVM* vm, const panda::Local<panda::ObjectRef>& object,
    CommonColor& commonColor)
{
    if (object->Has(vm, GetCachedString(vm, Framework::ArkUIIndex::START)) ||
        object->Has(vm, GetCachedString(vm, Framework::ArkUIIndex::END))) {
        LocalizedColor localizedColor;
        ParseLocalizedEdgeColors(vm, object, localizedColor);
        commonColor.top = localizedColor.top;
        commonColor.bottom = localizedColor.bottom;
        commonColor.left = localizedColor.start;
        commonColor.right = localizedColor.end;
        commonColor.topResObj = localizedColor.topResObj;
        commonColor.bottomResObj = localizedColor.bottomResObj;
        commonColor.leftResObj = localizedColor.startResObj;
        commonColor.rightResObj = localizedColor.endResObj;
        return true;
    }
    ParseEdgeColors(vm, object, commonColor);
    return false;
}

NG::BorderColorProperty ArkTSUtils::GetBorderColor(const CommonColor& commonColor)
{
    NG::BorderColorProperty borderColors;
    borderColors.leftColor = commonColor.left;
    borderColors.rightColor = commonColor.right;
    borderColors.topColor = commonColor.top;
    borderColors.bottomColor = commonColor.bottom;
    if (!SystemProperties::ConfigChangePerform()) {
        return borderColors;
    }
    if (commonColor.leftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.leftColor = result;
        };
        borderColors.AddResource("borderColor.left", commonColor.leftResObj, std::move(updateFunc));
    }
    if (commonColor.rightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.rightColor = result;
        };
        borderColors.AddResource("borderColor.right", commonColor.rightResObj, std::move(updateFunc));
    }
    if (commonColor.topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.topColor = result;
        };
        borderColors.AddResource("borderColor.top", commonColor.topResObj, std::move(updateFunc));
    }
    if (commonColor.bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.bottomColor = result;
        };
        borderColors.AddResource("borderColor.bottom", commonColor.bottomResObj, std::move(updateFunc));
    }
    borderColors.multiValued = true;
    return borderColors;
}

void ParseLocalizedMarginOrLocalizedPaddingCorner(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& object, LocalizedCalcDimension& localizedCalcDimension)
{
    auto jsStart = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::START));
    if (jsStart->IsObject(vm)) {
        panda::Local<panda::ObjectRef> startObj = jsStart->ToObject(vm);
        CalcDimension calcDimension;
        if (ArkTSUtils::ParseJsLengthMetrics(vm, startObj, calcDimension)) {
            localizedCalcDimension.start = calcDimension;
        }
    }
    auto jsEnd = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::END));
    if (jsEnd->IsObject(vm)) {
        panda::Local<panda::ObjectRef> endObj = jsEnd->ToObject(vm);
        CalcDimension calcDimension;
        if (ArkTSUtils::ParseJsLengthMetrics(vm, endObj, calcDimension)) {
            localizedCalcDimension.end = calcDimension;
        }
    }
    auto jsTop = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::TOP));
    if (jsTop->IsObject(vm)) {
        panda::Local<panda::ObjectRef> topObj = jsTop->ToObject(vm);
        CalcDimension calcDimension;
        if (ArkTSUtils::ParseJsLengthMetrics(vm, topObj, calcDimension)) {
            localizedCalcDimension.top = calcDimension;
        }
    }
    auto jsBottom = object->Get(vm, GetCachedString(vm, Framework::ArkUIIndex::BOTTOM));
    if (jsBottom->IsObject(vm)) {
        panda::Local<panda::ObjectRef> bottomObj = jsBottom->ToObject(vm);
        CalcDimension calcDimension;
        if (ArkTSUtils::ParseJsLengthMetrics(vm, bottomObj, calcDimension)) {
            localizedCalcDimension.bottom = calcDimension;
        }
    }
}

void ArkTSUtils::ParseMarginOrPaddingCorner(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& obj, CommonCalcDimension& commonCalcDimension)
{
    CalcDimension leftDimen;
    RefPtr<ResourceObject> leftResObj;
    auto leftValue = GetCachedString(vm, Framework::ArkUIIndex::LEFT);
    if (ArkTSUtils::ParseJsDimensionVp(vm, obj->Get(vm, leftValue), leftDimen, leftResObj)) {
        commonCalcDimension.left = leftDimen;
    }
    CalcDimension rightDimen;
    RefPtr<ResourceObject> rightResObj;
    auto rightValue = GetCachedString(vm, Framework::ArkUIIndex::RIGHT);
    if (ArkTSUtils::ParseJsDimensionVp(vm, obj->Get(vm, rightValue), rightDimen, rightResObj)) {
        commonCalcDimension.right = rightDimen;
    }
    CalcDimension topDimen;
    RefPtr<ResourceObject> topResObj;
    auto topValue = GetCachedString(vm, Framework::ArkUIIndex::TOP);
    if (ArkTSUtils::ParseJsDimensionVp(vm, obj->Get(vm, topValue), topDimen, topResObj)) {
        commonCalcDimension.top = topDimen;
    }
    CalcDimension bottomDimen;
    RefPtr<ResourceObject> bottomResObj;
    auto bottomValue = GetCachedString(vm, Framework::ArkUIIndex::BOTTOM);
    if (ArkTSUtils::ParseJsDimensionVp(vm, obj->Get(vm, bottomValue), bottomDimen, bottomResObj)) {
        commonCalcDimension.bottom = bottomDimen;
    }
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    if (leftResObj) {
        commonCalcDimension.leftResObj = leftResObj;
    }
    if (rightResObj) {
        commonCalcDimension.rightResObj = rightResObj;
    }
    if (topResObj) {
        commonCalcDimension.topResObj = topResObj;
    }
    if (bottomResObj) {
        commonCalcDimension.bottomResObj = bottomResObj;
    }
}

bool ArkTSUtils::ParseCommonMarginOrPaddingCorner(
    EcmaVM* vm, const panda::Local<panda::ObjectRef>& object, CommonCalcDimension& commonCalcDimension)
{
    if (ArkTSUtils::CheckLengthMetrics(vm, object)) {
        LocalizedCalcDimension localizedCalcDimension;
        ParseLocalizedMarginOrLocalizedPaddingCorner(vm, object, localizedCalcDimension);
        commonCalcDimension.top = localizedCalcDimension.top;
        commonCalcDimension.bottom = localizedCalcDimension.bottom;
        commonCalcDimension.left = localizedCalcDimension.start;
        commonCalcDimension.right = localizedCalcDimension.end;
        return true;
    }
    if (SystemProperties::ConfigChangePerform()) {
        ParseMarginOrPaddingCorner(vm, object, commonCalcDimension);
    } else {
        ParseMarginOrPaddingCorner(vm, object, commonCalcDimension.top, commonCalcDimension.bottom,
            commonCalcDimension.left, commonCalcDimension.right);
    }
    return false;
}
} // namespace OHOS::Ace::NG
