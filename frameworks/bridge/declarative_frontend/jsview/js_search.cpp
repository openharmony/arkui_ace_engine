/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_search.h"

#include <optional>
#include <string>
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "bridge/declarative_frontend/engine/functions/js_common_event_function.h"
#include "bridge/declarative_frontend/engine/functions/js_cited_event_function.h"
#include "bridge/declarative_frontend/engine/functions/js_event_function.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/jsview/js_text_editable_controller.h"
#include "bridge/declarative_frontend/jsview/js_textfield.h"
#include "bridge/declarative_frontend/jsview/js_textinput.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/search_model_impl.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components/search/search_theme.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<SearchModel> SearchModel::instance_ = nullptr;
std::mutex SearchModel::mutex_;

SearchModel* SearchModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::SearchModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::SearchModelNG instance;
        return &instance;
    } else {
        static Framework::SearchModelImpl instance;
        return &instance;
    }
#endif
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
constexpr double DEFAULT_OPACITY = 0.2;
const int32_t DEFAULT_ALPHA = 255;
constexpr TextDecorationStyle DEFAULT_TEXT_DECORATION_STYLE = TextDecorationStyle::SOLID;
const char* TOP_START_PROPERTY = "topStart";
const char* TOP_END_PROPERTY = "topEnd";
const char* BOTTOM_START_PROPERTY = "bottomStart";
const char* BOTTOM_END_PROPERTY = "bottomEnd";

bool ParseJsLengthMetrics(const JSRef<JSObject>& obj, CalcDimension& result)
{
    auto value = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::VALUE));
    if (!value->IsNumber()) {
        return false;
    }
    auto unit = DimensionUnit::VP;
    auto jsUnit = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::UNIT));
    if (jsUnit->IsNumber()) {
        unit = static_cast<DimensionUnit>(jsUnit->ToNumber<int32_t>());
    }
    CalcDimension dimension(value->ToNumber<double>(), unit);
    result = dimension;
    return true;
}
} // namespace

void JSSearch::JSBind(BindingTarget globalObj)
{
    JSClass<JSSearch>::Declare("Search");
    MethodOptions opt = MethodOptions::NONE;

    JSClass<JSSearch>::StaticMethod("create", &JSSearch::Create, opt);
    JSClass<JSSearch>::StaticMethod("searchButton", &JSSearch::SetSearchButton, opt);
    JSClass<JSSearch>::StaticMethod("searchIcon", &JSSearch::SetSearchIcon, opt);
    JSClass<JSSearch>::StaticMethod("cancelButton", &JSSearch::SetCancelButton, opt);
    JSClass<JSSearch>::StaticMethod("fontColor", &JSSearch::SetTextColor, opt);
    JSClass<JSSearch>::StaticMethod("backgroundColor", &JSSearch::SetBackgroundColor, opt);
    JSClass<JSSearch>::StaticMethod("caretStyle", &JSSearch::SetCaret, opt);
    JSClass<JSSearch>::StaticMethod("placeholderColor", &JSSearch::SetPlaceholderColor, opt);
    JSClass<JSSearch>::StaticMethod("placeholderFont", &JSSearch::SetPlaceholderFont, opt);
    JSClass<JSSearch>::StaticMethod("textFont", &JSSearch::SetTextFont, opt);
    JSClass<JSSearch>::StaticMethod("textAlign", &JSSearch::SetTextAlign, opt);
    JSClass<JSSearch>::StaticMethod("onSubmit", &JSSearch::OnSubmit, opt);
    JSClass<JSSearch>::StaticMethod("onChange", &JSSearch::OnChange, opt);
    JSClass<JSSearch>::StaticMethod("onTextSelectionChange", &JSSearch::SetOnTextSelectionChange);
    JSClass<JSSearch>::StaticMethod("onContentScroll", &JSSearch::SetOnScroll);
    JSClass<JSSearch>::StaticMethod("border", &JSSearch::JsBorder);
    JSClass<JSSearch>::StaticMethod("borderWidth", &JSSearch::JsBorderWidth);
    JSClass<JSSearch>::StaticMethod("borderColor", &JSSearch::JsBorderColor);
    JSClass<JSSearch>::StaticMethod("borderStyle", &JSSearch::JsBorderStyle);
    JSClass<JSSearch>::StaticMethod("borderRadius", &JSSearch::JsBorderRadius);
    JSClass<JSSearch>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSearch>::StaticMethod("height", &JSSearch::SetHeight);
    JSClass<JSSearch>::StaticMethod("width", &JSViewAbstract::JsWidth);
    JSClass<JSSearch>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSearch>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSearch>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSearch>::StaticMethod("requestKeyboardOnFocus", &JSSearch::SetEnableKeyboardOnFocus);
    JSClass<JSSearch>::StaticMethod("enableKeyboardOnFocus", &JSSearch::SetEnableKeyboardOnFocus);
    JSClass<JSSearch>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSSearch>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSearch>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSSearch>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSearch>::StaticMethod("onCopy", &JSSearch::SetOnCopy);
    JSClass<JSSearch>::StaticMethod("onCut", &JSSearch::SetOnCut);
    JSClass<JSSearch>::StaticMethod("onPaste", &JSSearch::SetOnPaste);
    JSClass<JSSearch>::StaticMethod("copyOption", &JSSearch::SetCopyOption);
    JSClass<JSSearch>::StaticMethod("selectionMenuHidden", &JSSearch::SetSelectionMenuHidden);
    JSClass<JSSearch>::StaticMethod("customKeyboard", &JSSearch::SetCustomKeyboard);
    JSClass<JSSearch>::StaticMethod("enterKeyType", &JSSearch::SetEnterKeyType);
    JSClass<JSSearch>::StaticMethod("maxLength", &JSSearch::SetMaxLength);
    JSClass<JSSearch>::StaticMethod("type", &JSSearch::SetType);
    JSClass<JSSearch>::StaticMethod("dragPreviewOptions", &JSSearch::SetDragPreviewOptions);
    JSClass<JSSearch>::StaticMethod("editMenuOptions", &JSSearch::EditMenuOptions);
    JSClass<JSSearch>::StaticMethod("strokeWidth", &JSSearch::SetStrokeWidth);
    JSClass<JSSearch>::StaticMethod("strokeColor", &JSSearch::SetStrokeColor);
    JSClass<JSSearch>::StaticMethod("margin", &JSSearch::JsMargin);
    JSBindMore();
    JSClass<JSSearch>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSSearch::JSBindMore()
{
    JSClass<JSSearch>::StaticMethod("decoration", &JSSearch::SetDecoration);
    JSClass<JSSearch>::StaticMethod("minFontSize", &JSSearch::SetMinFontSize);
    JSClass<JSSearch>::StaticMethod("maxFontSize", &JSSearch::SetMaxFontSize);
    JSClass<JSSearch>::StaticMethod("minFontScale", &JSSearch::SetMinFontScale);
    JSClass<JSSearch>::StaticMethod("maxFontScale", &JSSearch::SetMaxFontScale);
    JSClass<JSSearch>::StaticMethod("letterSpacing", &JSSearch::SetLetterSpacing);
    JSClass<JSSearch>::StaticMethod("lineHeight", &JSSearch::SetLineHeight);
    JSClass<JSSearch>::StaticMethod("halfLeading", &JSSearch::SetHalfLeading);
    JSClass<JSSearch>::StaticMethod("fontFeature", &JSSearch::SetFontFeature);
    JSClass<JSSearch>::StaticMethod("id", &JSSearch::SetId);
    JSClass<JSSearch>::StaticMethod("key", &JSSearch::SetKey);
    JSClass<JSSearch>::StaticMethod("selectedBackgroundColor", &JSSearch::SetSelectedBackgroundColor);
    JSClass<JSSearch>::StaticMethod("inputFilter", &JSSearch::SetInputFilter);
    JSClass<JSSearch>::StaticMethod("onEditChange", &JSSearch::SetOnEditChange);
    JSClass<JSSearch>::StaticMethod("textIndent", &JSSearch::SetTextIndent);
    JSClass<JSSearch>::StaticMethod("onWillInsert", &JSSearch::OnWillInsertValue);
    JSClass<JSSearch>::StaticMethod("onDidInsert", &JSSearch::OnDidInsertValue);
    JSClass<JSSearch>::StaticMethod("onWillDelete", &JSSearch::OnWillDelete);
    JSClass<JSSearch>::StaticMethod("onDidDelete", &JSSearch::OnDidDelete);
    JSClass<JSSearch>::StaticMethod("enablePreviewText", &JSSearch::SetEnablePreviewText);
    JSClass<JSSearch>::StaticMethod("enableHapticFeedback", &JSSearch::SetEnableHapticFeedback);
    JSClass<JSSearch>::StaticMethod("autoCapitalizationMode", &JSSearch::SetCapitalizationMode);
    JSClass<JSSearch>::StaticMethod("stopBackPress", &JSSearch::SetStopBackPress);
    JSClass<JSSearch>::StaticMethod("keyboardAppearance", &JSSearch::SetKeyboardAppearance);
    JSClass<JSSearch>::StaticMethod("onWillChange", &JSSearch::SetOnWillChange);
    JSClass<JSSearch>::StaticMethod("enableAutoSpacing", &JSSearch::SetEnableAutoSpacing);
    JSClass<JSSearch>::StaticMethod("onWillAttachIME", &JSSearch::SetOnWillAttachIME);
}

void ParseSearchValueObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    JsEventCallback<void(const std::u16string&)> onChangeEvent(
        info.GetExecutionContext(), JSRef<JSFunc>::Cast(changeEventVal));
    SearchModel::GetInstance()->SetOnChangeEvent(std::move(onChangeEvent));
}

void JSSearch::SetDragPreviewOptions(const JSCallbackInfo& info)
{
    NG::DragPreviewOption option = JSViewAbstract::ParseDragPreviewOptions(info);
    SearchModel::GetInstance()->SetDragPreviewOptions(option);
}

void JSSearch::SetFontFeature(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsString() && !info[0]->IsObject()) {
        return;
    }
    std::string fontFeatureSettings = info[0]->ToString();
    SearchModel::GetInstance()->SetFontFeature(ParseFontFeatureSettings(fontFeatureSettings));
}

void JSSearch::Create(const JSCallbackInfo& info)
{
    std::optional<std::u16string> key;
    std::optional<std::u16string> tip;
    std::optional<std::string> src;
    JSTextEditableController* jsController = nullptr;
    JSRef<JSVal> changeEventVal;
    bool placeholderResult = false;
    bool textResult = false;
    std::u16string placeholder;
    std::u16string text;
    RefPtr<ResourceObject> placeholderObject;
    RefPtr<ResourceObject> textObject;
    if (info[0]->IsObject()) {
        auto param = JSRef<JSObject>::Cast(info[0]);
        if (param->GetProperty("placeholder")->IsUndefined()) {
            tip = u"";
        }
        placeholderResult = ParseJsString(param->GetProperty("placeholder"), placeholder, placeholderObject);
        if (placeholderResult) {
            tip = placeholder;
        }

        JSRef<JSVal> textValue = param->GetProperty("value");
        if (textValue->IsObject()) {
            JSRef<JSObject> valueObj = JSRef<JSObject>::Cast(textValue);
            changeEventVal = valueObj->GetProperty("changeEvent");
            if (changeEventVal->IsFunction()) {
                textValue = valueObj->GetProperty("value");
            }
            textResult = ParseJsString(textValue, text, textObject);
            if (textResult) {
                key = text;
            }
        } else if (param->GetProperty("$value")->IsFunction()) {
            changeEventVal = param->GetProperty("$value");
            textResult = ParseJsString(textValue, text, textObject);
            if (textResult) {
                key = text;
            }
        } else if (param->HasProperty("value") && textValue->IsUndefined()) {
            key = u"";
        } else {
            textResult = ParseJsString(textValue, text, textObject);
            if (textResult) {
                key = text;
            }
        }
        std::string icon;
        if (ParseJsString(param->GetProperty("icon"), icon)) {
            src = icon;
        }
        auto controllerObj = param->GetProperty("controller");
        if (!controllerObj->IsUndefined() && !controllerObj->IsNull() && controllerObj->IsObject()) {
            jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextEditableController>();
        }
    }
    auto controller = SearchModel::GetInstance()->Create(key, tip, src);
    if (jsController) {
        jsController->SetController(controller);
    }
    SearchModel::GetInstance()->SetFocusable(true);
    SearchModel::GetInstance()->SetFocusNode(true);
    if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction()) {
        ParseSearchValueObject(info, changeEventVal);
    }
    if (placeholderResult && SystemProperties::ConfigChangePerform()) {
        if (placeholderObject) {
            RegisterResource<std::u16string>("placeholder", placeholderObject, placeholder);
        } else {
            UnregisterResource("placeholder");
        }
    }

    if (textResult && SystemProperties::ConfigChangePerform()) {
        if (textObject) {
            RegisterResource<std::u16string>("text", textObject, text);
        } else {
            UnregisterResource("text");
        }
    }
}

void JSSearch::SetSelectedBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color selectedColor;
    RefPtr<ResourceObject> resourceObject;
    UnregisterResource("selectedBackgroundColor");
    if (!ParseJsColor(info[0], selectedColor, resourceObject)) {
        SearchModel::GetInstance()->ResetSelectedBackgroundColor();
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<Color>("selectedBackgroundColor", resourceObject, selectedColor);
    }
    // Alpha = 255 means opaque
    if (selectedColor.GetAlpha() == DEFAULT_ALPHA) {
        // Default setting of 20% opacity
        selectedColor = selectedColor.ChangeOpacity(DEFAULT_OPACITY);
    }
    SearchModel::GetInstance()->SetSelectedBackgroundColor(selectedColor);
}

void JSSearch::SetEnableKeyboardOnFocus(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || !info[0]->IsBoolean()) {
        SearchModel::GetInstance()->RequestKeyboardOnFocus(true);
        return;
    }
    SearchModel::GetInstance()->RequestKeyboardOnFocus(info[0]->ToBoolean());
}

void JSSearch::SetId(const JSCallbackInfo& info)
{
    JSViewAbstract::JsId(info);
    JSRef<JSVal> arg = info[0];
    std::string id;
    if (arg->IsString()) {
        id = arg->ToString();
    }
    SearchModel::GetInstance()->UpdateInspectorId(id);
}

void JSSearch::SetKey(const std::string& key)
{
    JSViewAbstract::JsKey(key);
    SearchModel::GetInstance()->UpdateInspectorId(key);
}

void JSSearch::SetSearchButtonOptions(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    Color fontColor = theme->GetSearchButtonTextColor();
    if (info.Length() < 2 || !info[1]->IsObject()) { // 2 : args num
        SearchModel::GetInstance()->SetSearchButtonFontSize(theme->GetButtonFontSize());
        SearchModel::GetInstance()->ResetSearchButtonFontColor();
        return;
    }
    
    auto param = JSRef<JSObject>::Cast(info[1]);
    // set button font size, unit FP
    auto fontSize = param->GetProperty("fontSize");
    RefPtr<ResourceObject> fontSizeObject;
    UnregisterResource("searchButtonFontSize");
    CalcDimension size = theme->GetButtonFontSize();
    if (ParseJsDimensionVpNG(fontSize, size, fontSizeObject) && size.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(size.Value(), 0.0)) {
        ParseJsDimensionFp(fontSize, size, fontSizeObject);
    } else {
        size = theme->GetButtonFontSize();
    }
    if (SystemProperties::ConfigChangePerform() && fontSizeObject) {
        RegisterResource<CalcDimension>("searchButtonFontSize", fontSizeObject, size);
    }
    SearchModel::GetInstance()->SetSearchButtonFontSize(size);
    
    auto fontColorProp = param->GetProperty("fontColor");
    RefPtr<ResourceObject> colorObject;
    if (fontColorProp->IsUndefined() || fontColorProp->IsNull() ||
        !ParseJsColor(fontColorProp, fontColor, colorObject)) {
        SearchModel::GetInstance()->ResetSearchButtonFontColor();
    } else {
        SearchModel::GetInstance()->SetSearchButtonFontColor(fontColor);
    }
    if (SystemProperties::ConfigChangePerform() && fontSizeObject) {
        RegisterResource<Color>("searchButtonFontColor", colorObject, fontColor);
    } else {
        UnregisterResource("searchButtonFontColor");
    }

    auto autoDisable = param->GetProperty("autoDisable");
    if (autoDisable->IsUndefined() || autoDisable->IsNull() || !autoDisable->IsBoolean()) {
        SearchModel::GetInstance()->SetSearchButtonAutoDisable(false);
    } else {
        SearchModel::GetInstance()->SetSearchButtonAutoDisable(autoDisable->ToBoolean());
    }
}

void JSSearch::SetSearchButton(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    std::string buttonValue = "";
    UnregisterResource("searchButtonValue");
    if (info[0]->IsString()) {
        buttonValue = info[0]->ToString();
    } else {
        RefPtr<ResourceObject> resourceObject;
        ParseJsString(info[0], buttonValue, resourceObject);
        if (SystemProperties::ConfigChangePerform() && resourceObject) {
            RegisterResource<std::string>("searchButtonValue", resourceObject, buttonValue);
        }
    }
    SearchModel::GetInstance()->SetSearchButton(buttonValue);
    SetSearchButtonOptions(info);
}

void JSSearch::SetSearchIcon(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || info[0]->IsNull()) {
        SetSearchDefaultIcon();
        return;
    }
    if (info[0]->IsObject()) {
        auto param = JSRef<JSObject>::Cast(info[0]);
        bool isSymbolIcon = param->HasProperty("fontColor"); // only SymbolGlyph has fontColor property
        if (isSymbolIcon) {
            SetSearchSymbolIcon(info);
        } else {
            SetSearchImageIcon(info);
        }
    }
}

void JSSearch::SetCancelDefaultIcon()
{
    SearchModel::GetInstance()->SetCancelDefaultIcon();
}

void JSSearch::SetCancelSymbolIcon(const JSCallbackInfo& info)
{
    if (info[0]->IsObject()) {
        std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
        auto param = JSRef<JSObject>::Cast(info[0]);
        auto iconProp = param->GetProperty("icon");
        SetSymbolOptionApply(info, iconSymbol, iconProp);
        SearchModel::GetInstance()->SetCancelSymbolIcon(iconSymbol);
    }
}

void JSSearch::SetCancelImageIcon(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    auto theme = GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    auto iconJsVal = param->GetProperty("icon");
    if (!iconJsVal->IsObject()) {
        return;
    }
    auto iconParam = JSRef<JSObject>::Cast(iconJsVal);

    // set icon size
    CalcDimension iconSize;
    auto iconSizeProp = iconParam->GetProperty("size");
    RefPtr<ResourceObject> sizeObject;
    UnregisterResource("cancelButtonIconSize");
    if (!iconSizeProp->IsUndefined() && !iconSizeProp->IsNull() &&
        ParseJsDimensionVpNG(iconSizeProp, iconSize, sizeObject)) {
        if (LessNotEqual(iconSize.Value(), 0.0) || iconSize.Unit() == DimensionUnit::PERCENT) {
            iconSize = theme->GetIconHeight();
        }
    } else {
        iconSize = theme->GetIconHeight();
    }
    if (SystemProperties::ConfigChangePerform() && sizeObject) {
        RegisterResource<CalcDimension>("cancelButtonIconSize", sizeObject, iconSize);
    }

    // set icon src
    std::string iconSrc;
    RefPtr<ResourceObject> srcObject;
    UnregisterResource("cancelButtonIconSrc");
    auto iconSrcProp = iconParam->GetProperty("src");
    if (iconSrcProp->IsUndefined() || iconSrcProp->IsNull() || !ParseJsMedia(iconSrcProp, iconSrc, srcObject)) {
        iconSrc = "";
    }
    if (SystemProperties::ConfigChangePerform() && srcObject) {
        RegisterResource<std::string>("cancelButtonIconSrc", srcObject, iconSrc);
    }

    // set icon color
    Color iconColor;
    RefPtr<ResourceObject> colorObject;
    UnregisterResource("cancelButtonIconColor");
    NG::IconOptions cancelIconOptions;
    auto iconColorProp = iconParam->GetProperty("color");
    if (!iconColorProp->IsUndefined() && !iconColorProp->IsNull() &&
        ParseJsColor(iconColorProp, iconColor, colorObject)) {
        SearchModel::GetInstance()->SetCancelIconColor(iconColor);
        cancelIconOptions = NG::IconOptions(iconColor, iconSize, iconSrc, "", "");
    } else {
        SearchModel::GetInstance()->ResetCancelIconColor();
        cancelIconOptions = NG::IconOptions(iconSize, iconSrc, "", "");
    }
    if (SystemProperties::ConfigChangePerform() && colorObject) {
        RegisterResource<Color>("cancelButtonIconColor", colorObject, iconColor);
    }
    SearchModel::GetInstance()->SetCancelImageIcon(cancelIconOptions);
}

void JSSearch::SetSearchDefaultIcon()
{
    SearchModel::GetInstance()->SetSearchDefaultIcon();
}

void JSSearch::SetSearchSymbolIcon(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    SetSymbolOptionApply(info, iconSymbol, info[0]);
    SearchModel::GetInstance()->SetSearchSymbolIcon(iconSymbol);
}

void JSSearch::SetSearchImageIcon(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    auto theme = GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);

    // set icon size
    CalcDimension size;
    auto sizeProp = param->GetProperty("size");
    RefPtr<ResourceObject> sizeObject;
    UnregisterResource("searchIconSize");
    if (!sizeProp->IsUndefined() && !sizeProp->IsNull() &&
        ParseJsDimensionVpNG(sizeProp, size, sizeObject)) {
        if (LessNotEqual(size.Value(), 0.0) || size.Unit() == DimensionUnit::PERCENT) {
            size = theme->GetIconHeight();
        }
    } else {
        size = theme->GetIconHeight();
    }
    if (SystemProperties::ConfigChangePerform() && sizeObject) {
        RegisterResource<CalcDimension>("searchIconSize", sizeObject, size);
    }
    // set icon src
    std::string src;
    RefPtr<ResourceObject> mediaObject;
    UnregisterResource("searchButtonIconSrc");
    auto srcPathProp = param->GetProperty("src");
    if (srcPathProp->IsUndefined() || srcPathProp->IsNull() || !ParseJsMedia(srcPathProp, src, mediaObject)) {
        src = "";
    }
    if (SystemProperties::ConfigChangePerform() && mediaObject) {
        RegisterResource<std::string>("searchButtonIconSrc", mediaObject, src);
    }
    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(srcPathProp, bundleName, moduleName);
    // set icon color
    Color colorVal;
    RefPtr<ResourceObject> colorObject;
    UnregisterResource("searchIconColor");
    NG::IconOptions searchIconOptions;
    auto colorProp = param->GetProperty("color");
    if (!colorProp->IsUndefined() && !colorProp->IsNull() && ParseJsColor(colorProp, colorVal, colorObject)) {
        SearchModel::GetInstance()->SetSearchIconColor(colorVal);
        searchIconOptions = NG::IconOptions(colorVal, size, src, bundleName, moduleName);
    } else {
        SearchModel::GetInstance()->ResetSearchIconColor();
        searchIconOptions = NG::IconOptions(size, src, bundleName, moduleName);
    }
    if (SystemProperties::ConfigChangePerform() && colorObject) {
        RegisterResource<Color>("searchIconColor", colorObject, colorVal);
    }
    SearchModel::GetInstance()->SetSearchImageIcon(searchIconOptions);
}

static CancelButtonStyle ConvertStrToCancelButtonStyle(const std::string& value)
{
    if (value == "CONSTANT") {
        return CancelButtonStyle::CONSTANT;
    } else if (value == "INVISIBLE") {
        return CancelButtonStyle::INVISIBLE;
    } else {
        return CancelButtonStyle::INPUT;
    }
}

void JSSearch::SetCancelButton(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    auto theme = GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);

    // set style
    std::string styleStr;
    CancelButtonStyle cancelButtonStyle;
    auto styleProp = param->GetProperty("style");
    if (!styleProp->IsUndefined() && !styleProp->IsNull() && ParseJsString(styleProp, styleStr)) {
        cancelButtonStyle = ConvertStrToCancelButtonStyle(styleStr);
    } else {
        cancelButtonStyle = theme->GetCancelButtonStyle();
    }
    SearchModel::GetInstance()->SetCancelButtonStyle(cancelButtonStyle);

    auto iconProp = param->GetProperty("icon");
    if (iconProp->IsUndefined() || iconProp->IsNull()) {
        SetCancelDefaultIcon();
    } else {
        SetIconStyle(info);
    }
}

void JSSearch::SetIconStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    auto param = JSRef<JSObject>::Cast(info[0]);
    auto iconJsVal = param->GetProperty("icon");
    if (!iconJsVal->IsObject()) {
        return;
    }

    auto iconParam = JSRef<JSObject>::Cast(iconJsVal);
    bool isSymbolIcon = iconParam->HasProperty("fontColor"); // only SymbolGlyph has fontColor property
    if (isSymbolIcon) {
        SetCancelSymbolIcon(info);
    } else {
        SetCancelImageIcon(info);
    }
}

void JSSearch::SetTextColor(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);

    auto value = JSRef<JSVal>::Cast(info[0]);
    Color colorVal;
    RefPtr<ResourceObject> resourceObject;
    UnregisterResource("fontColor");
    if (!ParseJsColor(value, colorVal, resourceObject)) {
        SearchModel::GetInstance()->ResetTextColor();
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<Color>("fontColor", resourceObject, colorVal);
    }
    SearchModel::GetInstance()->SetTextColor(colorVal);
}

void JSSearch::SetBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color colorVal;
    if (!ParseJsColor(info[0], colorVal)) {
        SearchModel::GetInstance()->ResetBackgroundColor();
        return;
    }
    SearchModel::GetInstance()->SetBackgroundColor(colorVal);
}

void JSSearch::SetCaret(const JSCallbackInfo& info)
{
    if (info[0]->IsObject()) {
        auto param = JSRef<JSObject>::Cast(info[0]);
        auto textFieldTheme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);

        // set caret width
        CalcDimension caretWidth = textFieldTheme->GetCursorWidth();
        auto caretWidthProp = param->GetProperty("width");
        RefPtr<ResourceObject> widthObject;
        UnregisterResource("caretWidth");
        if (!ParseJsDimensionVpNG(caretWidthProp, caretWidth, widthObject, false) ||
            LessNotEqual(caretWidth.Value(), 0.0)) {
            caretWidth = textFieldTheme->GetCursorWidth();
        }
        if (SystemProperties::ConfigChangePerform() && widthObject) {
            RegisterResource<CalcDimension>("caretWidth", widthObject, caretWidth);
        }
        SearchModel::GetInstance()->SetCaretWidth(caretWidth);

        // set caret color
        Color caretColor;
        RefPtr<ResourceObject> colorObject;
        UnregisterResource("caretColor");
        auto caretColorProp = param->GetProperty("color");
        if (caretColorProp->IsUndefined() || caretColorProp->IsNull() ||
            !ParseJsColor(caretColorProp, caretColor, colorObject)) {
            SearchModel::GetInstance()->ResetCaretColor();
            return;
        }
        if (SystemProperties::ConfigChangePerform() && widthObject) {
            RegisterResource<Color>("caretColor", colorObject, caretColor);
        }
        SearchModel::GetInstance()->SetCaretColor(caretColor);
    }
}

void JSSearch::SetInputFilter(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto tmpInfo = info[0];
    auto errInfo = info[1];
    std::string inputFilter;
    if (tmpInfo->IsUndefined()) {
        UnregisterResource("inputFilter");
        SearchModel::GetInstance()->SetInputFilter(inputFilter, nullptr);
        return;
    }

    RefPtr<ResourceObject> resourceObject;
    if (!ParseJsString(tmpInfo, inputFilter, resourceObject)) {
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<std::string>("inputFilter", resourceObject, inputFilter);
    } else {
        UnregisterResource("inputFilter");
    }

    if (!CheckRegexValid(inputFilter)) {
        inputFilter = "";
    }
    if (info.Length() > 1 && errInfo->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsClipboardFunction>(JSRef<JSFunc>::Cast(errInfo));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto resultId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            const std::u16string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            PipelineContext::SetCallBackNode(node);
            func->Execute(info);
        };
        SearchModel::GetInstance()->SetInputFilter(inputFilter, resultId);
        return;
    }
    SearchModel::GetInstance()->SetInputFilter(inputFilter, nullptr);
}

void JSSearch::SetOnEditChange(const JSCallbackInfo& info)
{
    auto tmpInfo = info[0];
    CHECK_NULL_VOID(tmpInfo->IsFunction());
    JsEventCallback<void(bool)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(tmpInfo));
    SearchModel::GetInstance()->SetOnEditChanged(std::move(callback));
}

void JSSearch::SetTextIndent(const JSCallbackInfo& info)
{
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    UnregisterResource("textIndent");
    if (!ParseJsDimensionVpNG(info[0], value, resourceObject, true)) {
        value.Reset();
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<CalcDimension>("textIndent", resourceObject, value);
    }
    SearchModel::GetInstance()->SetTextIndent(value);
}

void JSSearch::SetPlaceholderColor(const JSCallbackInfo& info)
{
    auto value = JSRef<JSVal>::Cast(info[0]);
    Color colorVal;
    RefPtr<ResourceObject> resourceObject;
    UnregisterResource("placeholderColor");
    if (!ParseJsColor(value, colorVal, resourceObject)) {
        SearchModel::GetInstance()->ResetPlaceholderColor();
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<Color>("placeholderColor", resourceObject, colorVal);
    }
    SearchModel::GetInstance()->SetPlaceholderColor(colorVal);
}

void JSSearch::SetPlaceholderFont(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    auto theme = GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    auto themeFontSize = theme->GetFontSize();
    Font font;
    auto fontSize = param->GetProperty("size");
    RefPtr<ResourceObject> resourceObject;
    UnregisterResource("placeholderFontSize");
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        font.fontSize = themeFontSize;
    } else {
        auto versionTenOrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
        CalcDimension size;
        if ((versionTenOrLarger ?
            ParseJsDimensionVpNG(fontSize, size, resourceObject) :
            ParseJsDimensionVp(fontSize, size, resourceObject)) &&
            size.Unit() != DimensionUnit::PERCENT) {
            ParseJsDimensionFp(fontSize, size, resourceObject);
            font.fontSize = size;
        } else {
            font.fontSize = themeFontSize;
        }
        if (SystemProperties::ConfigChangePerform() && resourceObject) {
            RegisterResource<CalcDimension>("placeholderFontSize", resourceObject, size);
        }
    }
    
    auto weight = param->GetProperty("weight");
    if (!weight->IsNull()) {
        std::string weightVal;
        if (weight->IsNumber()) {
            weightVal = std::to_string(weight->ToNumber<int32_t>());
        } else {
            ParseJsString(weight, weightVal);
        }
        font.fontWeight = ConvertStrToFontWeight(weightVal);
    }

    auto family = param->GetProperty("family");
    if (!family->IsNull() && family->IsString()) {
        auto familyVal = family->ToString();
        font.fontFamilies = ConvertStrToFontFamilies(familyVal);
    }

    auto style = param->GetProperty("style");
    if (!style->IsNull() && style->IsNumber()) {
        FontStyle styleVal = static_cast<FontStyle>(style->ToNumber<int32_t>());
        font.fontStyle = styleVal;
    }
    SearchModel::GetInstance()->SetPlaceholderFont(font);
}

void JSSearch::SetTextFont(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    auto themeFontSize = theme->GetFontSize();
    auto themeFontWeight = theme->GetFontWeight();
    Font font { .fontWeight = themeFontWeight, .fontSize = themeFontSize, .fontStyle = Ace::FontStyle::NORMAL };
    if (info.Length() < 1 || !info[0]->IsObject()) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            SearchModel::GetInstance()->SetTextFont(font);
        }
        return;
    }
    auto param = JSRef<JSObject>::Cast(info[0]);
    auto fontSize = param->GetProperty("size");
    CalcDimension size = themeFontSize;
    RefPtr<ResourceObject> resourceObject;
    UnregisterResource("fontSize");
    if (ParseJsDimensionVpNG(fontSize, size, resourceObject) && size.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(size.Value(), 0.0)) {
        ParseJsDimensionFp(fontSize, size, resourceObject);
    } else {
        size = themeFontSize;
    }
    font.fontSize = size;
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<CalcDimension>("fontSize", resourceObject, size);
    }

    auto weight = param->GetProperty("weight");
    if (!weight->IsNull()) {
        std::string weightVal;
        if (weight->IsNumber()) {
            weightVal = std::to_string(weight->ToNumber<int32_t>());
        } else {
            ParseJsString(weight, weightVal);
        }
        font.fontWeight = ConvertStrToFontWeight(weightVal);
    }

    auto family = param->GetProperty("family");
    if (!family->IsNull() && family->IsString()) {
        auto familyVal = family->ToString();
        font.fontFamilies = ConvertStrToFontFamilies(familyVal);
    }

    auto style = param->GetProperty("style");
    if (!style->IsNull() && style->IsNumber()) {
        FontStyle styleVal = static_cast<FontStyle>(style->ToNumber<int32_t>());
        font.fontStyle = styleVal;
    }
    SearchModel::GetInstance()->SetTextFont(font);
}

void JSSearch::SetTextAlign(int32_t value)
{
    if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
        SearchModel::GetInstance()->SetTextAlign(TEXT_ALIGNS[value]);
    }
}

void JSSearch::JsBorder(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        CalcDimension borderWidth;
        ViewAbstractModel::GetInstance()->SetBorderWidth(borderWidth);
        ViewAbstractModel::GetInstance()->SetBorderColor(Color::BLACK);
        ViewAbstractModel::GetInstance()->SetBorderRadius(borderWidth);
        ViewAbstractModel::GetInstance()->SetBorderStyle(BorderStyle::SOLID);
        ViewAbstractModel::GetInstance()->SetDashGap(Dimension(-1));
        ViewAbstractModel::GetInstance()->SetDashWidth(Dimension(-1));
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);

    auto valueWidth = object->GetProperty(static_cast<int32_t>(ArkUIIndex::WIDTH));
    if (!valueWidth->IsUndefined()) {
        JSViewAbstract::ParseBorderWidth(valueWidth);
    }

    // use default value when undefined.
    JSViewAbstract::ParseBorderColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::COLOR)));

    auto valueRadius = object->GetProperty(static_cast<int32_t>(ArkUIIndex::RADIUS));
    if (!valueRadius->IsUndefined()) {
        JSViewAbstract::ParseBorderRadius(valueRadius);
        SearchModel::GetInstance()->SetBackBorderRadius();
    }
    // use default value when undefined.
    JSViewAbstract::ParseBorderStyle(object->GetProperty(static_cast<int32_t>(ArkUIIndex::STYLE)));

    auto dashGap = object->GetProperty("dashGap");
    if (!dashGap->IsUndefined()) {
        JSViewAbstract::ParseDashGap(dashGap);
    }
    auto dashWidth = object->GetProperty("dashWidth");
    if (!dashWidth->IsUndefined()) {
        JSViewAbstract::ParseDashWidth(dashWidth);
    }

    SearchModel::GetInstance()->SetBackBorder();
    info.ReturnSelf();
}

void JSSearch::JsBorderWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorderWidth(info);
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        return;
    }
    SearchModel::GetInstance()->SetBackBorder();
}

void JSSearch::JsBorderColor(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorderColor(info);
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        return;
    }
    SearchModel::GetInstance()->SetBackBorder();
}

void JSSearch::JsBorderStyle(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorderStyle(info);
    if (!info[0]->IsObject() && !info[0]->IsNumber()) {
        return;
    }
    SearchModel::GetInstance()->SetBackBorder();
}

void JSSearch::GetBorderRadiusByLengthMetrics(const char* key, JSRef<JSObject>& object,
    std::optional<CalcDimension>& radius)
{
    if (object->HasProperty(key) && object->GetProperty(key)->IsObject()) {
        JSRef<JSObject> startObj = JSRef<JSObject>::Cast(object->GetProperty(key));
        CalcDimension value;
        ParseJsLengthMetrics(startObj, value);
        radius = value;
    }
}

bool JSSearch::ParseAllBorderRadiuses(JSRef<JSObject>& object, CalcDimension& topLeft,
    CalcDimension& topRight, CalcDimension& bottomLeft, CalcDimension& bottomRight)
{
    if (object->HasProperty(TOP_START_PROPERTY) || object->HasProperty(TOP_END_PROPERTY) ||
        object->HasProperty(BOTTOM_START_PROPERTY) || object->HasProperty(BOTTOM_END_PROPERTY)) {
        std::optional<CalcDimension> topStart;
        std::optional<CalcDimension> topEnd;
        std::optional<CalcDimension> bottomStart;
        std::optional<CalcDimension> bottomEnd;
        GetBorderRadiusByLengthMetrics(TOP_START_PROPERTY, object, topStart);
        GetBorderRadiusByLengthMetrics(TOP_END_PROPERTY, object, topEnd);
        GetBorderRadiusByLengthMetrics(BOTTOM_START_PROPERTY, object, bottomStart);
        GetBorderRadiusByLengthMetrics(BOTTOM_END_PROPERTY, object, bottomEnd);
        topLeft = topStart.has_value() ? topStart.value() : topLeft;
        topRight = topEnd.has_value() ? topEnd.value() : topRight;
        bottomLeft = bottomStart.has_value() ? bottomStart.value() : bottomLeft;
        bottomRight = bottomEnd.has_value() ? bottomEnd.value() : bottomRight;
        return true;
    }
    JSViewAbstract::ParseJsDimensionVp(object->GetProperty("topLeft"), topLeft);
    JSViewAbstract::ParseJsDimensionVp(object->GetProperty("topRight"), topRight);
    JSViewAbstract::ParseJsDimensionVp(object->GetProperty("bottomLeft"), bottomLeft);
    JSViewAbstract::ParseJsDimensionVp(object->GetProperty("bottomRight"), bottomRight);
    return false;
}

void JSSearch::ParseBorderRadius(const JSRef<JSVal>& args)
{
    CalcDimension borderRadius;
    if (ParseJsDimensionVp(args, borderRadius)) {
        ViewAbstractModel::GetInstance()->SetBorderRadius(borderRadius);
    } else if (args->IsObject()) {
        auto textFieldTheme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);
        auto borderRadiusTheme = textFieldTheme->GetBorderRadius();
        NG::BorderRadiusProperty defaultBorderRadius {
            borderRadiusTheme.GetX(), borderRadiusTheme.GetY(),
            borderRadiusTheme.GetY(), borderRadiusTheme.GetX(),
        };

        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension topLeft = defaultBorderRadius.radiusTopLeft.value();
        CalcDimension topRight = defaultBorderRadius.radiusTopRight.value();
        CalcDimension bottomLeft = defaultBorderRadius.radiusBottomLeft.value();
        CalcDimension bottomRight = defaultBorderRadius.radiusBottomRight.value();
        if (ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight)) {
            ViewAbstractModel::GetInstance()->SetBorderRadius(
                JSViewAbstract::GetLocalizedBorderRadius(topLeft, topRight, bottomLeft, bottomRight));
                return;
        }
        ViewAbstractModel::GetInstance()->SetBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
    }
}

void JSSearch::JsBorderRadius(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    static std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING,
        JSCallbackInfoType::NUMBER, JSCallbackInfoType::OBJECT };
    if (!CheckJSCallbackInfo("JsBorderRadius", jsValue, checkList)) {
        auto textFieldTheme = GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);
        auto borderRadiusTheme = textFieldTheme->GetBorderRadius();
        NG::BorderRadiusProperty defaultBorderRadius {
            borderRadiusTheme.GetX(), borderRadiusTheme.GetY(),
            borderRadiusTheme.GetY(), borderRadiusTheme.GetX(),
        };
        ViewAbstractModel::GetInstance()->SetBorderRadius(defaultBorderRadius);
        return;
    }
    ParseBorderRadius(jsValue);
    SearchModel::GetInstance()->SetBackBorderRadius();
}

void JSSearch::CreateJsSearchCommonEvent(const JSCallbackInfo &info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }
    auto jsTextFunc = AceType::MakeRefPtr<JsCommonEventFunction<NG::TextFieldCommonEvent, 2>>(
        JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc), node = targetNode](
                        const std::u16string& value, NG::TextFieldCommonEvent& event) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onSubmit");
        PipelineContext::SetCallBackNode(node);
        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        objectTemplate->SetInternalFieldCount(2);
        JSRef<JSObject> object = objectTemplate->NewInstance();
        object->SetProperty<std::u16string>("text", event.GetText());
        object->SetPropertyObject(
            "keepEditableState", JSRef<JSFunc>::New<FunctionCallback>(JSTextField::JsKeepEditableState));
        object->Wrap<NG::TextFieldCommonEvent>(&event);
        JSRef<JSVal> stringValue = JSRef<JSVal>::Make(ToJSValue(value));
        JSRef<JSVal> dataObject = JSRef<JSVal>::Cast(object);
        JSRef<JSVal> param[2] = {stringValue, dataObject};
        func->Execute(param);
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onSubmit");
    };
    SearchModel::GetInstance()->SetOnSubmit(std::move(callback));
}

void JSSearch::OnSubmit(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
#ifdef NG_BUILD
    CreateJsSearchCommonEvent(info);
#else
    if (Container::IsCurrentUseNewPipeline()) {
        CreateJsSearchCommonEvent(info);
    } else {
        JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(jsValue));
        SearchModel::GetInstance()->SetOnSubmit(std::move(callback));
    }
#endif
}

JSRef<JSVal> JSSearch::CreateJsOnChangeObj(const PreviewText& previewText)
{
    JSRef<JSObject> previewTextObj = JSRef<JSObject>::New();
    previewTextObj->SetProperty<int32_t>("offset", previewText.offset);
    previewTextObj->SetProperty<std::u16string>("value", previewText.value);
    return JSRef<JSVal>::Cast(previewTextObj);
}

void JSSearch::OnChange(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsChangeFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(jsValue));
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsChangeFunc)](
        const ChangeValueInfo& changeValueInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onChange");
        JSRef<JSVal> valueObj = JSRef<JSVal>::Make(ToJSValue(changeValueInfo.value));
        auto previewTextObj = CreateJsOnChangeObj(changeValueInfo.previewText);
        auto optionsObj = JSRef<JSObject>::New();
        auto rangeBeforeObj = JSRef<JSObject>::New();
        rangeBeforeObj->SetProperty<int32_t>("start", changeValueInfo.rangeBefore.start);
        rangeBeforeObj->SetProperty<int32_t>("end", changeValueInfo.rangeBefore.end);
        optionsObj->SetPropertyObject("rangeBefore", rangeBeforeObj);
        auto rangeAfterObj = JSRef<JSObject>::New();
        rangeAfterObj->SetProperty<int32_t>("start", changeValueInfo.rangeAfter.start);
        rangeAfterObj->SetProperty<int32_t>("end", changeValueInfo.rangeAfter.end);
        optionsObj->SetPropertyObject("rangeAfter", rangeAfterObj);
        optionsObj->SetProperty<std::u16string>("oldContent", changeValueInfo.oldContent);
        auto oldPreviewTextObj = CreateJsOnChangeObj(changeValueInfo.oldPreviewText);
        optionsObj->SetPropertyObject("oldPreviewText", oldPreviewTextObj);
        JSRef<JSVal> argv[] = { valueObj, previewTextObj, optionsObj };
        func->ExecuteJS(3, argv);
    };
    SearchModel::GetInstance()->SetOnChange(std::move(onChange));
}

void JSSearch::SetOnTextSelectionChange(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(int32_t, int32_t)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    SearchModel::GetInstance()->SetOnTextSelectionChange(std::move(callback));
}

void JSSearch::SetOnScroll(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(float, float)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    SearchModel::GetInstance()->SetOnScroll(std::move(callback));
}

void JSSearch::SetHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    CalcDimension value;
    auto versionTenOrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
    if (versionTenOrLarger ? !ParseJsDimensionVpNG(info[0], value) : !ParseJsDimensionVp(info[0], value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    SearchModel::GetInstance()->SetHeight(value);
}

void JSSearch::SetOnCopy(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::u16string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    SearchModel::GetInstance()->SetOnCopy(std::move(callback));
}

void JSSearch::SetOnCut(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::u16string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    SearchModel::GetInstance()->SetOnCut(std::move(callback));
}

JSRef<JSVal> JSSearch::CreateJSTextCommonEvent(NG::TextCommonEvent& event)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> object = objectTemplate->NewInstance();
    object->SetPropertyObject("preventDefault", JSRef<JSFunc>::New<FunctionCallback>(JsPreventDefault));
    object->Wrap<NG::TextCommonEvent>(&event);
    return JSRef<JSVal>::Cast(object);
}

void JSSearch::SetOnPaste(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    auto jsTextFunc = AceType::MakeRefPtr<JsCitedEventFunction<NG::TextCommonEvent, 2>>(
        JSRef<JSFunc>::Cast(info[0]), CreateJSTextCommonEvent);

    auto onPaste = [execCtx = info.GetExecutionContext(), func = std::move(jsTextFunc)](
                       const std::u16string& val, NG::TextCommonEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onPaste");
        func->Execute(val, info);
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onPaste");
    };
    SearchModel::GetInstance()->SetOnPasteWithEvent(std::move(onPaste));
}

void JSSearch::SetCopyOption(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    if (info[0]->IsUndefined()) {
        SearchModel::GetInstance()->SetCopyOption(CopyOptions::Local);
        return;
    }
    auto copyOptions = CopyOptions::Local;
    if (info[0]->IsNumber()) {
        auto emunNumber = info[0]->ToNumber<int>();
        copyOptions = static_cast<CopyOptions>(emunNumber);
    }
    SearchModel::GetInstance()->SetCopyOption(copyOptions);
}

JSRef<JSVal> JSSearch::CreateJsAboutToIMEInputObj(const InsertValueInfo& insertValue)
{
    JSRef<JSObject> aboutToIMEInputObj = JSRef<JSObject>::New();
    aboutToIMEInputObj->SetProperty<int32_t>("insertOffset", insertValue.insertOffset);
    aboutToIMEInputObj->SetProperty<std::u16string>("insertValue", insertValue.insertValue);
    return JSRef<JSVal>::Cast(aboutToIMEInputObj);
}

void JSSearch::OnWillInsertValue(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsAboutToIMEInputFunc = AceType::MakeRefPtr<JsEventFunction<InsertValueInfo, 1>>(
        JSRef<JSFunc>::Cast(jsValue), CreateJsAboutToIMEInputObj);
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToIMEInputFunc)](
                        const InsertValueInfo& insertValue) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, true);
        auto ret = func->ExecuteWithValue(insertValue);
        if (ret->IsBoolean()) {
            return ret->ToBoolean();
        }
        return true;
    };
    SearchModel::GetInstance()->SetOnWillInsertValueEvent(std::move(callback));
}

JSRef<JSVal> JSSearch::CreateJsDeleteToIMEObj(const DeleteValueInfo& deleteValueInfo)
{
    JSRef<JSObject> aboutToIMEInputObj = JSRef<JSObject>::New();
    aboutToIMEInputObj->SetProperty<int32_t>("deleteOffset", deleteValueInfo.deleteOffset);
    aboutToIMEInputObj->SetProperty<int32_t>("direction", static_cast<int32_t>(deleteValueInfo.direction));
    aboutToIMEInputObj->SetProperty<std::u16string>("deleteValue", deleteValueInfo.deleteValue);
    return JSRef<JSVal>::Cast(aboutToIMEInputObj);
}

void JSSearch::OnDidInsertValue(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsAboutToIMEInputFunc = AceType::MakeRefPtr<JsEventFunction<InsertValueInfo, 1>>(
        JSRef<JSFunc>::Cast(jsValue), CreateJsAboutToIMEInputObj);
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToIMEInputFunc)](
                        const InsertValueInfo& insertValue) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->ExecuteWithValue(insertValue);
    };
    SearchModel::GetInstance()->SetOnDidInsertValueEvent(std::move(callback));
}

void JSSearch::OnWillDelete(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsAboutToIMEInputFunc =
        AceType::MakeRefPtr<JsEventFunction<DeleteValueInfo, 1>>(JSRef<JSFunc>::Cast(jsValue), CreateJsDeleteToIMEObj);
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToIMEInputFunc)](
                        const DeleteValueInfo& deleteValue) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, true);
        auto ret = func->ExecuteWithValue(deleteValue);
        if (ret->IsBoolean()) {
            return ret->ToBoolean();
        }
        return true;
    };
    SearchModel::GetInstance()->SetOnWillDeleteEvent(std::move(callback));
}

void JSSearch::OnDidDelete(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsAboutToIMEInputFunc =
        AceType::MakeRefPtr<JsEventFunction<DeleteValueInfo, 1>>(JSRef<JSFunc>::Cast(jsValue), CreateJsDeleteToIMEObj);
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToIMEInputFunc)](
                        const DeleteValueInfo& deleteValue) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->ExecuteWithValue(deleteValue);
    };
    SearchModel::GetInstance()->SetOnDidDeleteEvent(std::move(callback));
}

void JSSearch::SetSelectionMenuHidden(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || !info[0]->IsBoolean()) {
        SearchModel::GetInstance()->SetSelectionMenuHidden(false);
        return;
    }
    SearchModel::GetInstance()->SetSelectionMenuHidden(info[0]->ToBoolean());
}

void JSSearch::SetCustomKeyboard(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && (info[0]->IsUndefined() || info[0]->IsNull())) {
        SearchModel::GetInstance()->SetCustomKeyboard(nullptr);
        return;
    }
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    bool supportAvoidance = false;
    if (info.Length() == 2 && info[1]->IsObject()) { //  2 here refers to the number of parameters
        auto paramObject = JSRef<JSObject>::Cast(info[1]);
        auto isSupportAvoidance = paramObject->GetProperty("supportAvoidance");
        if (!isSupportAvoidance->IsNull() && isSupportAvoidance->IsBoolean()) {
            supportAvoidance = isSupportAvoidance->ToBoolean();
        }
    }
    std::function<void()> buildFunc;
    if (JSTextField::ParseJsCustomKeyboardBuilder(info, 0, buildFunc)) {
        SearchModel::GetInstance()->SetCustomKeyboard(std::move(buildFunc), supportAvoidance);
    }
}

void JSSearch::SetType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsUndefined()) {
        SearchModel::GetInstance()->SetType(TextInputType::UNSPECIFIED);
        return;
    }
    if (!info[0]->IsNumber()) {
        return;
    }
    TextInputType textInputType = CastToTextInputType(info[0]->ToNumber<int32_t>());
    SearchModel::GetInstance()->SetType(textInputType);
}

void JSSearchController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextEditableController>::Declare("SearchController");
    JSTextEditableController::JSBind(globalObj);
}

void JSSearch::SetEnterKeyType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsUndefined()) {
        SearchModel::GetInstance()->SetSearchEnterKeyType(TextInputAction::SEARCH);
        return;
    }
    if (!info[0]->IsNumber()) {
        return;
    }
    TextInputAction textInputAction = CastToTextInputAction(info[0]->ToNumber<int32_t>());
    SearchModel::GetInstance()->SetSearchEnterKeyType(textInputAction);
}

void JSSearch::SetCapitalizationMode(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    auto autoCapitalizationMode = AutoCapitalizationMode::NONE;
    if (jsValue->IsUndefined() || !jsValue->IsNumber() || jsValue->IsNull()) {
        SearchModel::GetInstance()->SetSearchCapitalizationMode(autoCapitalizationMode);
        return;
    }
    if (jsValue->IsNumber()) {
        auto emunNumber = jsValue->ToNumber<int32_t>();
        autoCapitalizationMode = CastToAutoCapitalizationMode(emunNumber);
    }
    SearchModel::GetInstance()->SetSearchCapitalizationMode(autoCapitalizationMode);
}

void JSSearch::SetMaxLength(const JSCallbackInfo& info)
{
    int32_t maxLength = 0;
    if (info[0]->IsUndefined()) {
        SearchModel::GetInstance()->ResetMaxLength();
        return;
    } else if (!info[0]->IsNumber()) {
        SearchModel::GetInstance()->ResetMaxLength();
        return;
    }
    maxLength = info[0]->ToNumber<int32_t>();
    if (std::isinf(info[0]->ToNumber<float>())) {
        maxLength = INT32_MAX; // Infinity
    }
    if (GreatOrEqual(maxLength, 0)) {
        SearchModel::GetInstance()->SetMaxLength(maxLength);
    } else {
        SearchModel::GetInstance()->ResetMaxLength();
    }
}

void JSSearch::SetDecoration(const JSCallbackInfo& info)
{
    auto tmpInfo = info[0];
    if (!tmpInfo->IsObject()) {
        SearchModel::GetInstance()->SetTextDecoration(TextDecoration::NONE);
        SearchModel::GetInstance()->SetTextDecorationColor(Color::BLACK);
        SearchModel::GetInstance()->SetTextDecorationStyle(TextDecorationStyle::SOLID);
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(tmpInfo);
    JSRef<JSVal> typeValue = obj->GetProperty("type");
    JSRef<JSVal> colorValue = obj->GetProperty("color");
    JSRef<JSVal> styleValue = obj->GetProperty("style");

    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    TextDecoration textDecoration = theme->GetTextDecoration();
    if (typeValue->IsNumber()) {
        textDecoration = static_cast<TextDecoration>(typeValue->ToNumber<int32_t>());
    }
    Color result = theme->GetTextStyle().GetTextDecorationColor();
    RefPtr<ResourceObject> resourceObject;
    auto ret = ParseJsColor(colorValue, result, Color::BLACK, resourceObject);
    if (ret && SystemProperties::ConfigChangePerform()) {
        if (resourceObject) {
            RegisterResource<Color>("decorationColor", resourceObject, result);
        } else {
            UnregisterResource("decorationColor");
        }
    }
    std::optional<TextDecorationStyle> textDecorationStyle;
    if (styleValue->IsNumber()) {
        textDecorationStyle = static_cast<TextDecorationStyle>(styleValue->ToNumber<int32_t>());
    } else {
        textDecorationStyle = DEFAULT_TEXT_DECORATION_STYLE;
    }
    SearchModel::GetInstance()->SetTextDecoration(textDecoration);
    SearchModel::GetInstance()->SetTextDecorationColor(result);
    if (textDecorationStyle) {
        SearchModel::GetInstance()->SetTextDecorationStyle(textDecorationStyle.value());
    }
}

void JSSearch::SetMinFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension minFontSize;
    RefPtr<ResourceObject> resourceObject;
    UnregisterResource("minFontSize");
    if (!ParseJsDimensionFpNG(info[0], minFontSize, resourceObject, false)) {
        SearchModel::GetInstance()->SetAdaptMinFontSize(CalcDimension());
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<CalcDimension>("minFontSize", resourceObject, minFontSize);
    }
    if (minFontSize.IsNegative()) {
        minFontSize = CalcDimension();
    }
    SearchModel::GetInstance()->SetAdaptMinFontSize(minFontSize);
}

void JSSearch::SetMaxFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();

    RefPtr<ResourceObject> resourceObject;
    UnregisterResource("maxFontSize");
    if (!ParseJsDimensionFpNG(info[0], maxFontSize, resourceObject, false)) {
        maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
        SearchModel::GetInstance()->SetAdaptMaxFontSize(maxFontSize);
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<CalcDimension>("maxFontSize", resourceObject, maxFontSize);
    }
    if (maxFontSize.IsNegative()) {
        maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
    }
    SearchModel::GetInstance()->SetAdaptMaxFontSize(maxFontSize);
}

void JSSearch::SetMinFontScale(const JSCallbackInfo& info)
{
    double minFontScale = 0.0;
    RefPtr<ResourceObject> resourceObject;
    if (info.Length() < 1 || !ParseJsDouble(info[0], minFontScale, resourceObject)) {
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<float>("minFontScale", resourceObject, minFontScale);
    } else {
        UnregisterResource("minFontScale");
    }
    if (LessOrEqual(minFontScale, 0.0f)) {
        SearchModel::GetInstance()->SetMinFontScale(0.0f);
        return;
    }
    if (GreatOrEqual(minFontScale, 1.0f)) {
        SearchModel::GetInstance()->SetMinFontScale(1.0f);
        return;
    }
    SearchModel::GetInstance()->SetMinFontScale(static_cast<float>(minFontScale));
}

void JSSearch::SetMaxFontScale(const JSCallbackInfo& info)
{
    double maxFontScale = 0.0;
    RefPtr<ResourceObject> resourceObject;
    if (info.Length() < 1 || !ParseJsDouble(info[0], maxFontScale, resourceObject)) {
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<float>("maxFontScale", resourceObject, maxFontScale);
    } else {
        UnregisterResource("maxFontScale");
    }
    if (LessOrEqual(maxFontScale, 1.0f)) {
        SearchModel::GetInstance()->SetMaxFontScale(1.0f);
        return;
    }
    SearchModel::GetInstance()->SetMaxFontScale(static_cast<float>(maxFontScale));
}

void JSSearch::SetLetterSpacing(const JSCallbackInfo& info)
{
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    if (!ParseJsDimensionFpNG(info[0], value, resourceObject, false)) {
        value.Reset();
        SearchModel::GetInstance()->SetLetterSpacing(value);
        UnregisterResource("letterSpacing");
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<CalcDimension>("letterSpacing", resourceObject, value);
    }
    SearchModel::GetInstance()->SetLetterSpacing(value);
}

void JSSearch::SetLineHeight(const JSCallbackInfo& info)
{
    CalcDimension value;
    RefPtr<ResourceObject> resourceObject;
    if (!ParseJsDimensionFpNG(info[0], value, resourceObject)) {
        value.Reset();
        SearchModel::GetInstance()->SetLineHeight(value);
        UnregisterResource("lineHeight");
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resourceObject) {
        RegisterResource<CalcDimension>("lineHeight", resourceObject, value);
    }
    if (value.IsNegative()) {
        value.Reset();
    }
    SearchModel::GetInstance()->SetLineHeight(value);
}

void JSSearch::SetHalfLeading(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto jsValue = info[0];
    bool halfLeading = jsValue->IsBoolean() ? jsValue->ToBoolean() : false;
    SearchModel::GetInstance()->SetHalfLeading(halfLeading);
}

void JSSearch::EditMenuOptions(const JSCallbackInfo& info)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    JSViewAbstract::ParseEditMenuOptions(info, onCreateMenuCallback, onMenuItemClick, onPrepareMenuCallback);
    SearchModel::GetInstance()->SetSelectionMenuOptions(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick), std::move(onPrepareMenuCallback));
}

void JSSearch::SetEnablePreviewText(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    if (!jsValue->IsBoolean()) {
        SearchModel::GetInstance()->SetEnablePreviewText(true);
        return;
    }
    SearchModel::GetInstance()->SetEnablePreviewText(jsValue->ToBoolean());
}

void JSSearch::SetEnableHapticFeedback(const JSCallbackInfo& info)
{
    bool state = true;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        state = info[0]->ToBoolean();
    }
    SearchModel::GetInstance()->SetEnableHapticFeedback(state);
}

void JSSearch::SetStopBackPress(const JSCallbackInfo& info)
{
    bool isStopBackPress = true;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        isStopBackPress = info[0]->ToBoolean();
    }
    SearchModel::GetInstance()->SetStopBackPress(isStopBackPress);
}

void JSSearch::SetKeyboardAppearance(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        SearchModel::GetInstance()->SetKeyboardAppearance(
            static_cast<KeyboardAppearance>(KeyboardAppearance::NONE_IMMERSIVE));
        return;
    }
    auto keyboardAppearance = info[0]->ToNumber<uint32_t>();
    if (keyboardAppearance < static_cast<uint32_t>(KeyboardAppearance::NONE_IMMERSIVE) ||
        keyboardAppearance > static_cast<uint32_t>(KeyboardAppearance::DARK_IMMERSIVE)) {
        SearchModel::GetInstance()->SetKeyboardAppearance(
            static_cast<KeyboardAppearance>(KeyboardAppearance::NONE_IMMERSIVE));
        return;
    }
    SearchModel::GetInstance()->SetKeyboardAppearance(
        static_cast<KeyboardAppearance>(keyboardAppearance));
}

JSRef<JSVal> JSSearch::CreateJsOnWillChangeObj(const ChangeValueInfo& changeValueInfo)
{
    JSRef<JSObject> ChangeValueInfo = JSRef<JSObject>::New();
    ChangeValueInfo->SetProperty<std::u16string>("content", changeValueInfo.value);

    auto previewTextObj = CreateJsOnChangeObj(changeValueInfo.previewText);
    ChangeValueInfo->SetPropertyObject("previewText", previewTextObj);

    auto optionsObj = JSRef<JSObject>::New();
    auto rangeBeforeObj = JSRef<JSObject>::New();
    rangeBeforeObj->SetProperty<int32_t>("start", changeValueInfo.rangeBefore.start);
    rangeBeforeObj->SetProperty<int32_t>("end", changeValueInfo.rangeBefore.end);
    optionsObj->SetPropertyObject("rangeBefore", rangeBeforeObj);
    auto rangeAfterObj = JSRef<JSObject>::New();
    rangeAfterObj->SetProperty<int32_t>("start", changeValueInfo.rangeAfter.start);
    rangeAfterObj->SetProperty<int32_t>("end", changeValueInfo.rangeAfter.end);
    optionsObj->SetPropertyObject("rangeAfter", rangeAfterObj);
    optionsObj->SetProperty<std::u16string>("oldContent", changeValueInfo.oldContent);
    auto oldPreviewTextObj = CreateJsOnChangeObj(changeValueInfo.oldPreviewText);
    optionsObj->SetPropertyObject("oldPreviewText", oldPreviewTextObj);

    ChangeValueInfo->SetPropertyObject("options", optionsObj);
    return JSRef<JSVal>::Cast(ChangeValueInfo);
}

void JSSearch::SetOnWillChange(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsChangeFunc = AceType::MakeRefPtr<JsEventFunction<ChangeValueInfo, 1>>(
        JSRef<JSFunc>::Cast(jsValue), CreateJsOnWillChangeObj);
    auto onWillChange = [execCtx = info.GetExecutionContext(), func = std::move(jsChangeFunc)](
        const ChangeValueInfo& changeValue) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, true);
        ACE_SCORING_EVENT("onWillChange");
        auto ret = func->ExecuteWithValue(changeValue);
        if (ret->IsBoolean()) {
            return ret->ToBoolean();
        }
        return true;
    };
    SearchModel::GetInstance()->SetOnWillChangeEvent(std::move(onWillChange));
}

void JSSearch::SetStrokeWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension value;
    if (!ParseLengthMetricsToDimension(info[0], value)) {
        value.Reset();
    }
    SearchModel::GetInstance()->SetStrokeWidth(value);
}

void JSSearch::SetStrokeColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color strokeColor;
    if (!ParseJsColor(info[0], strokeColor)) {
        SearchModel::GetInstance()->ResetStrokeColor();
        return;
    }
    SearchModel::GetInstance()->SetStrokeColor(strokeColor);
}

void JSSearch::SetEnableAutoSpacing(const JSCallbackInfo& info)
{
    bool enabled = false;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        enabled = info[0]->ToBoolean();
    }
    SearchModel::GetInstance()->SetEnableAutoSpacing(enabled);
}

void JSSearch::SetOnWillAttachIME(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsOnWillAttachIMEFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(jsValue));
    auto onWillAttachIME = [execCtx = info.GetExecutionContext(), func = std::move(jsOnWillAttachIMEFunc)](
        const IMEClient& imeClientInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onWillAttachIME");
        JSRef<JSObject> imeClientObj = JSRef<JSObject>::New();
        imeClientObj->SetProperty<int32_t>("nodeId", imeClientInfo.nodeId);
        JSRef<JSVal> argv[] = { imeClientObj };
        func->ExecuteJS(1, argv);
    };
    SearchModel::GetInstance()->SetOnWillAttachIME(std::move(onWillAttachIME));
}

void JSSearch::SetKeyboardAppearanceConfig(const JSCallbackInfo& info)
{
    EcmaVM* vm = info.GetVm();
    CHECK_NULL_VOID(vm);
    auto jsTargetNode = info[0];
    auto* targetNodePtr = jsTargetNode->GetLocalHandle()->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(targetNodePtr);
    CHECK_NULL_VOID(frameNode);
    if (!info[1]->IsObject()) {
        return;
    }
    NG::KeyboardAppearanceConfig config = JSTextField::ParseKeyboardAppearanceConfig(JSRef<JSObject>::Cast(info[1]));
    NG::SearchModelNG::SetKeyboardAppearanceConfig(frameNode, config);
}

void JSSearch::UnregisterResource(const std::string& key)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
}

void JSSearch::JsMargin(const JSCallbackInfo& info)
{
    JSViewAbstract::JsMargin(info);
    SearchModel::GetInstance()->SetUserMargin();
}
} // namespace OHOS::Ace::Framework
