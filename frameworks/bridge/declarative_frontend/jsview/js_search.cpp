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

#include "bridge/declarative_frontend/jsview/js_search.h"

#include <optional>
#include <string>
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_search_theme.h"
#include "bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
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
    JSBindMore();
    JSClass<JSSearch>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSSearch::JSBindMore()
{
    JSClass<JSSearch>::StaticMethod("decoration", &JSSearch::SetDecoration);
    JSClass<JSSearch>::StaticMethod("minFontSize", &JSSearch::SetMinFontSize);
    JSClass<JSSearch>::StaticMethod("maxFontSize", &JSSearch::SetMaxFontSize);
    JSClass<JSSearch>::StaticMethod("letterSpacing", &JSSearch::SetLetterSpacing);
    JSClass<JSSearch>::StaticMethod("lineHeight", &JSSearch::SetLineHeight);
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
}

void ParseSearchValueObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    JsEventCallback<void(const std::string&)> onChangeEvent(
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
    std::optional<std::string> key;
    std::optional<std::string> tip;
    std::optional<std::string> src;
    JSTextEditableController* jsController = nullptr;
    JSRef<JSVal> changeEventVal;
    if (info[0]->IsObject()) {
        auto param = JSRef<JSObject>::Cast(info[0]);
        std::string placeholder;
        if (param->GetProperty("placeholder")->IsUndefined()) {
            tip = "";
        }
        if (ParseJsString(param->GetProperty("placeholder"), placeholder)) {
            tip = placeholder;
        }
        std::string text;
        JSRef<JSVal> textValue = param->GetProperty("value");
        if (textValue->IsObject()) {
            JSRef<JSObject> valueObj = JSRef<JSObject>::Cast(textValue);
            changeEventVal = valueObj->GetProperty("changeEvent");
            if (changeEventVal->IsFunction()) {
                textValue = valueObj->GetProperty("value");
            }
            if (ParseJsString(textValue, text)) {
                key = text;
            }
        } else if (param->HasProperty("value") && textValue->IsUndefined()) {
            key = "";
        } else {
            if (ParseJsString(textValue, text)) {
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
    JSSeacrhTheme::ApplyTheme();
}

void JSSearch::SetSelectedBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color selectedColor;
    if (!ParseJsColor(info[0], selectedColor)) {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        selectedColor = theme->GetSelectedColor();
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

void JSSearch::SetSearchButton(const JSCallbackInfo& info)
{
    auto theme = GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    std::string buttonValue = "";
    if (info[0]->IsString()) {
        buttonValue = info[0]->ToString();
    }
    SearchModel::GetInstance()->SetSearchButton(buttonValue);
    // set font color
    Color fontColor = theme->GetSearchButtonTextColor();
    if (info[1]->IsObject()) {
        auto param = JSRef<JSObject>::Cast(info[1]);

        // set button font size, unit FP
        auto fontSize = param->GetProperty("fontSize");
        CalcDimension size = theme->GetFontSize();
        if (ParseJsDimensionVpNG(fontSize, size) && size.Unit() != DimensionUnit::PERCENT &&
            GreatOrEqual(size.Value(), 0.0)) {
            ParseJsDimensionFp(fontSize, size);
        } else {
            size = theme->GetFontSize();
        }
        SearchModel::GetInstance()->SetSearchButtonFontSize(size);

        auto fontColorProp = param->GetProperty("fontColor");
        if (fontColorProp->IsUndefined() || fontColorProp->IsNull() || !ParseJsColor(fontColorProp, fontColor)) {
            if (!JSSeacrhTheme::ObtainSearchButtonFontColor(fontColor)) {
                SearchModel::GetInstance()->SetSearchButtonFontColor(fontColor);
            }
        } else {
            SearchModel::GetInstance()->SetSearchButtonFontColor(fontColor);
        }
        
        auto autoDisable = param->GetProperty("autoDisable");
        if (autoDisable->IsUndefined() || autoDisable->IsNull() || !autoDisable->IsBoolean()) {
            SearchModel::GetInstance()->SetSearchButtonAutoDisable(false);
        } else {
            SearchModel::GetInstance()->SetSearchButtonAutoDisable(autoDisable->ToBoolean());
        }
    } else {
        SearchModel::GetInstance()->SetSearchButtonFontSize(theme->GetFontSize());
        if (!JSSeacrhTheme::ObtainSearchButtonFontColor(fontColor)) {
            SearchModel::GetInstance()->SetSearchButtonFontColor(fontColor);
        }
    }
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
    if (!iconSizeProp->IsUndefined() && !iconSizeProp->IsNull() && ParseJsDimensionVpNG(iconSizeProp, iconSize)) {
        if (LessNotEqual(iconSize.Value(), 0.0) || iconSize.Unit() == DimensionUnit::PERCENT) {
            iconSize = theme->GetIconHeight();
        }
    } else {
        iconSize = theme->GetIconHeight();
    }

    // set icon src
    std::string iconSrc;
    auto iconSrcProp = iconParam->GetProperty("src");
    if (iconSrcProp->IsUndefined() || iconSrcProp->IsNull() || !ParseJsMedia(iconSrcProp, iconSrc)) {
        iconSrc = "";
    }

    // set icon color
    Color iconColor = theme->GetSearchIconColor();
    auto iconColorProp = iconParam->GetProperty("color");
    if (!iconColorProp->IsUndefined() && !iconColorProp->IsNull() && ParseJsColor(iconColorProp, iconColor)) {
        NG::IconOptions cancelIconOptions = NG::IconOptions(iconColor, iconSize, iconSrc, "", "");
        SearchModel::GetInstance()->SetCancelImageIcon(cancelIconOptions);
    } else {
        NG::IconOptions cancelIconOptions = NG::IconOptions(iconSize, iconSrc, "", "");
        SearchModel::GetInstance()->SetCancelImageIcon(cancelIconOptions);
    }
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
    if (!sizeProp->IsUndefined() && !sizeProp->IsNull() && ParseJsDimensionVpNG(sizeProp, size)) {
        if (LessNotEqual(size.Value(), 0.0) || size.Unit() == DimensionUnit::PERCENT) {
            size = theme->GetIconHeight();
        }
    } else {
        size = theme->GetIconHeight();
    }

    // set icon src
    std::string src;
    auto srcPathProp = param->GetProperty("src");
    if (srcPathProp->IsUndefined() || srcPathProp->IsNull() || !ParseJsMedia(srcPathProp, src)) {
        src = "";
    }
    // set icon color
    Color colorVal = theme->GetSearchIconColor();
    auto colorProp = param->GetProperty("color");
    if (!colorProp->IsUndefined() && !colorProp->IsNull()) {
        ParseJsColor(colorProp, colorVal);
    }

    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(srcPathProp, bundleName, moduleName);
    NG::IconOptions searchIconOptions = NG::IconOptions(colorVal, size, src, bundleName, moduleName);
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
    if (!ParseJsColor(value, colorVal)) {
        colorVal = theme->GetTextColor();
    }
    SearchModel::GetInstance()->SetTextColor(colorVal);
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
        if (!ParseJsDimensionVpNG(caretWidthProp, caretWidth, false) || LessNotEqual(caretWidth.Value(), 0.0)) {
            caretWidth = textFieldTheme->GetCursorWidth();
        }
        SearchModel::GetInstance()->SetCaretWidth(caretWidth);

        // set caret color
        Color caretColor;
        auto caretColorProp = param->GetProperty("color");
        if (caretColorProp->IsUndefined() || caretColorProp->IsNull() || !ParseJsColor(caretColorProp, caretColor)) {
            caretColor = textFieldTheme->GetCursorColor();
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
        SearchModel::GetInstance()->SetInputFilter(inputFilter, nullptr);
        return;
    }
    if (!ParseJsString(tmpInfo, inputFilter)) {
        return;
    }
    if (!CheckRegexValid(inputFilter)) {
        inputFilter = "";
    }
    if (info.Length() > 1 && errInfo->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsClipboardFunction>(JSRef<JSFunc>::Cast(errInfo));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto resultId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            const std::string& info) {
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
    if (!ParseJsDimensionVpNG(info[0], value, true)) {
        value.Reset();
    }
    SearchModel::GetInstance()->SetTextIndent(value);
}

void JSSearch::SetPlaceholderColor(const JSCallbackInfo& info)
{
    auto value = JSRef<JSVal>::Cast(info[0]);
    Color colorVal;
    if (!ParseJsColor(value, colorVal)) {
        auto theme = GetTheme<SearchTheme>();
        CHECK_NULL_VOID(theme);
        colorVal = theme->GetPlaceholderColor();
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
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        font.fontSize = themeFontSize;
    } else {
        auto versionTenOrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
        CalcDimension size;
        if ((versionTenOrLarger ? ParseJsDimensionVpNG(fontSize, size) : ParseJsDimensionVp(fontSize, size)) &&
            size.Unit() != DimensionUnit::PERCENT) {
            ParseJsDimensionFp(fontSize, size);
            font.fontSize = size;
        } else {
            font.fontSize = themeFontSize;
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
    if (ParseJsDimensionVpNG(fontSize, size) && size.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(size.Value(), 0.0)) {
        ParseJsDimensionFp(fontSize, size);
    } else {
        size = themeFontSize;
    }
    font.fontSize = size;

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
        ParseBorderRadius(valueRadius);
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
                        const std::string& value, NG::TextFieldCommonEvent& event) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onSubmit");
        PipelineContext::SetCallBackNode(node);
        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        objectTemplate->SetInternalFieldCount(2);
        JSRef<JSObject> object = objectTemplate->NewInstance();
        object->SetProperty<std::string>("text", event.GetText());
        object->SetPropertyObject(
            "keepEditableState", JSRef<JSFunc>::New<FunctionCallback>(JSTextField::JsKeepEditableState));
        object->Wrap<NG::TextFieldCommonEvent>(&event);
        JSRef<JSVal> stringValue = JSRef<JSVal>::Make(ToJSValue(value));
        JSRef<JSVal> dataObject = JSRef<JSVal>::Cast(object);
        JSRef<JSVal> param[2] = {stringValue, dataObject};
        func->Execute(param);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        UiSessionManager::GetInstance().ReportComponentChangeEvent("event", "onSubmit");
#endif
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
    previewTextObj->SetProperty<std::string>("value", previewText.value);
    return JSRef<JSVal>::Cast(previewTextObj);
}

void JSSearch::OnChange(const JSCallbackInfo& info)
{
    auto jsValue = info[0];
    CHECK_NULL_VOID(jsValue->IsFunction());
    auto jsChangeFunc =
        AceType::MakeRefPtr<JsCitedEventFunction<PreviewText, 2>>(JSRef<JSFunc>::Cast(jsValue), CreateJsOnChangeObj);
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsChangeFunc)](
                        const std::string& val, PreviewText& previewText) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onChange");
        func->Execute(val, previewText);
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
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
    SearchModel::GetInstance()->SetOnCopy(std::move(callback));
}

void JSSearch::SetOnCut(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    JsEventCallback<void(const std::string&)> callback(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0]));
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
                       const std::string& val, NG::TextCommonEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onPaste");
        func->Execute(val, info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        UiSessionManager::GetInstance().ReportComponentChangeEvent("event", "onPaste");
#endif
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
    aboutToIMEInputObj->SetProperty<std::string>("insertValue", insertValue.insertValue);
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
    aboutToIMEInputObj->SetProperty<std::string>("deleteValue", deleteValueInfo.deleteValue);
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
    do {
        auto tmpInfo = info[0];
        if (!tmpInfo->IsObject()) {
            SearchModel::GetInstance()->SetTextDecoration(TextDecoration::NONE);
            SearchModel::GetInstance()->SetTextDecorationColor(Color::BLACK);
            SearchModel::GetInstance()->SetTextDecorationStyle(TextDecorationStyle::SOLID);
            break;
        }
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(tmpInfo);
        JSRef<JSVal> typeValue = obj->GetProperty("type");
        JSRef<JSVal> colorValue = obj->GetProperty("color");
        JSRef<JSVal> styleValue = obj->GetProperty("style");

        auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<SearchTheme>();
        CHECK_NULL_VOID(theme);
        TextDecoration textDecoration = theme->GetTextStyle().GetTextDecoration();
        if (typeValue->IsNumber()) {
            textDecoration = static_cast<TextDecoration>(typeValue->ToNumber<int32_t>());
        }
        Color result = theme->GetTextStyle().GetTextDecorationColor();
        ParseJsColor(colorValue, result, Color::BLACK);
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
    } while (false);
}

void JSSearch::SetMinFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension minFontSize;
    if (!ParseJsDimensionFpNG(info[0], minFontSize, false)) {
        SearchModel::GetInstance()->SetAdaptMinFontSize(CalcDimension());
        return;
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
    if (!ParseJsDimensionFpNG(info[0], maxFontSize, false)) {
        maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
        SearchModel::GetInstance()->SetAdaptMaxFontSize(maxFontSize);
        return;
    }
    if (maxFontSize.IsNegative()) {
        maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
    }
    SearchModel::GetInstance()->SetAdaptMaxFontSize(maxFontSize);
}

void JSSearch::SetLetterSpacing(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionFpNG(info[0], value, false)) {
        value.Reset();
        SearchModel::GetInstance()->SetLetterSpacing(value);
        return;
    }
    SearchModel::GetInstance()->SetLetterSpacing(value);
}

void JSSearch::SetLineHeight(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionFpNG(info[0], value)) {
        value.Reset();
        SearchModel::GetInstance()->SetLineHeight(value);
        return;
    }
    if (value.IsNegative()) {
        value.Reset();
    }
    SearchModel::GetInstance()->SetLineHeight(value);
}

void JSSearch::EditMenuOptions(const JSCallbackInfo& info)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    JSViewAbstract::ParseEditMenuOptions(info, onCreateMenuCallback, onMenuItemClick);
    SearchModel::GetInstance()->SetSelectionMenuOptions(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
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
} // namespace OHOS::Ace::Framework
