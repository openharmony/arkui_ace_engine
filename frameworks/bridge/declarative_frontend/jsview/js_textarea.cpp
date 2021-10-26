/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_textarea.h"

#include <vector>

#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/text_field/text_field_component.h"
#include "core/components/text_field/textfield_theme.h"

namespace OHOS::Ace::Framework {

namespace {

const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = { "sans-serif" };
constexpr uint32_t TEXTAREA_MAXLENGTH_VALUE_DEFAULT = std::numeric_limits<uint32_t>::max();

}; // namespace

void JSTextArea::InitDefaultStyle()
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto stack = ViewStackProcessor::GetInstance();
    auto textAreaComponent = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    auto theme = GetTheme<TextFieldTheme>();
    if (!boxComponent || !textAreaComponent || !theme) {
        return;
    }

    textAreaComponent->SetTextMaxLines(TEXTAREA_MAXLENGTH_VALUE_DEFAULT);
    textAreaComponent->SetCursorColor(theme->GetCursorColor());
    textAreaComponent->SetPlaceholderColor(theme->GetPlaceholderColor());
    textAreaComponent->SetFocusBgColor(theme->GetFocusBgColor());
    textAreaComponent->SetFocusPlaceholderColor(theme->GetFocusPlaceholderColor());
    textAreaComponent->SetFocusTextColor(theme->GetFocusTextColor());
    textAreaComponent->SetBgColor(theme->GetBgColor());
    textAreaComponent->SetTextColor(theme->GetTextColor());
    textAreaComponent->SetSelectedColor(theme->GetSelectedColor());
    textAreaComponent->SetHoverColor(theme->GetHoverColor());
    textAreaComponent->SetPressColor(theme->GetPressColor());

    TextStyle textStyle = textAreaComponent->GetTextStyle();
    textStyle.SetTextColor(theme->GetTextColor());
    textStyle.SetFontSize(theme->GetFontSize());
    textStyle.SetFontWeight(theme->GetFontWeight());
    textStyle.SetFontFamilies(INPUT_FONT_FAMILY_VALUE);
    textAreaComponent->SetTextStyle(textStyle);

    textAreaComponent->SetCountTextStyle(theme->GetCountTextStyle());
    textAreaComponent->SetOverCountStyle(theme->GetOverCountStyle());
    textAreaComponent->SetCountTextStyleOuter(theme->GetCountTextStyleOuter());
    textAreaComponent->SetOverCountStyleOuter(theme->GetOverCountStyleOuter());
    textAreaComponent->SetErrorBorderWidth(theme->GetErrorBorderWidth());
    textAreaComponent->SetErrorBorderColor(theme->GetErrorBorderColor());

    RefPtr<Decoration> backDecoration = AceType::MakeRefPtr<Decoration>();
    backDecoration->SetPadding(theme->GetPadding());
    backDecoration->SetBackgroundColor(theme->GetBgColor());
    backDecoration->SetBorderRadius(theme->GetBorderRadius());
    const auto& boxDecoration = boxComponent->GetBackDecoration();
    if (boxDecoration) {
        backDecoration->SetImage(boxDecoration->GetImage());
        backDecoration->SetGradient(boxDecoration->GetGradient());
    }
    textAreaComponent->SetOriginBorder(backDecoration->GetBorder());
    textAreaComponent->SetDecoration(backDecoration);
    textAreaComponent->SetIconSize(theme->GetIconSize());
    textAreaComponent->SetIconHotZoneSize(theme->GetIconHotZoneSize());
    textAreaComponent->SetHeight(theme->GetHeight());

    // text area need to extend height.
    textAreaComponent->SetExtend(true);
    boxComponent->SetHeight(-1.0, DimensionUnit::VP);
}

void JSTextArea::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextArea>::Declare("TextArea");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTextArea>::StaticMethod("create", &JSTextArea::Create, opt);
    JSClass<JSTextArea>::StaticMethod("placeholderColor", &JSTextArea::SetPlaceholderColor);
    JSClass<JSTextArea>::StaticMethod("placeholderFont", &JSTextArea::SetPlaceholderFont);
    JSClass<JSTextArea>::StaticMethod("textAlign", &JSTextArea::SetTextAlign);
    JSClass<JSTextArea>::StaticMethod("caretColor", &JSTextArea::SetCaretColor);
    JSClass<JSTextArea>::StaticMethod("height", &JSTextArea::JsHeight);
    JSClass<JSTextArea>::StaticMethod("onChange", &JSTextArea::SetOnChange);
    JSClass<JSTextArea>::Inherit<JSViewAbstract>();
    JSClass<JSTextArea>::Bind(globalObj);
}

void JSTextArea::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("textarea create error, info is non-valid");
        return;
    }

    RefPtr<TextFieldComponent> textAreaComponent = AceType::MakeRefPtr<TextFieldComponent>();
    textAreaComponent->SetTextInputType(TextInputType::MULTILINE);
    textAreaComponent->SetTextEditController(AceType::MakeRefPtr<TextEditController>());
    textAreaComponent->SetTextFieldController(AceType::MakeRefPtr<TextFieldController>());
    auto paramObject = JSRef<JSObject>::Cast(info[0]);

    std::string placeholder;
    if (ParseJsString(paramObject->GetProperty("placeholder"), placeholder)) {
        textAreaComponent->SetPlaceholder(placeholder);
    }

    std::string text;
    if (ParseJsString(paramObject->GetProperty("text"), text)) {
        textAreaComponent->SetValue(text);
    }
    ViewStackProcessor::GetInstance()->Push(textAreaComponent);
    InitDefaultStyle();
}

void JSTextArea::SetPlaceholderColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg(SetPlaceholderColor) is wrong, it is supposed to have atlease 1 argument");
        return;
    }

    Color placeholderColor;
    if (!ParseJsColor(info[0], placeholderColor)) {
        LOGE("the info[0] is null");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (component) {
        component->SetPlaceholderColor(placeholderColor);
        component->SetFocusPlaceholderColor(placeholderColor);
    } else {
        LOGE("The component(SetPlaceholderColor) is null");
    }
}

void JSTextArea::SetPlaceholderFont(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("PlaceholderFont create error, info is non-valid");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("The component(SetPlaceholderFont) is null");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto textStyle = component->GetTextStyle();

    auto fontSize = paramObject->GetProperty("size");
    if (!fontSize->IsNull()) {
        Dimension size;
        ParseJsDimensionPx(fontSize, size);
        textStyle.SetFontSize(size);
    }

    std::string weight;
    auto fontWeight = paramObject->GetProperty("weight");
    if (!fontWeight->IsNull()) {
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        } else {
            ParseJsString(fontWeight, weight);
        }
        textStyle.SetFontWeight(ConvertStrToFontWeight(weight));
    }

    auto fontFamily = paramObject->GetProperty("family");
    if (!fontFamily->IsNull()) {
        std::vector<std::string> fontFamilies;
        if (ParseJsFontFamilies(fontFamily, fontFamilies)) {
            textStyle.SetFontFamilies(fontFamilies);
        }
    }

    auto style = paramObject->GetProperty("style");
    if (!style->IsNull()) {
        FontStyle fontStyle = static_cast<FontStyle>(style->ToNumber<int32_t>());
        textStyle.SetFontStyle(fontStyle);
    }
    component->SetTextStyle(textStyle);
}

void JSTextArea::SetTextAlign(int32_t value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("textAlign component is not valid");
        return;
    }

    if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
        component->SetTextAlign(TEXT_ALIGNS[value]);
    } else {
        LOGE("the value is error");
    }
}

void JSTextArea::SetCaretColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg(SetCareColor) is wrong, it is supposed to have atlease 1 argument");
        return;
    }

    Color color;
    if (!ParseJsColor(info[0], color)) {
        LOGE("info[0] is null");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (component) {
        component->SetCursorColor(color);
    } else {
        LOGE("The component(SetCaretColor) is null");
    }
}

void JSTextArea::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto textAreaComponent = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    if (!textAreaComponent) {
        LOGE("JSTextArea set height failed, textAreaComponent is null.");
        return;
    }
    textAreaComponent->SetHeight(value);
}

void JSTextArea::SetOnChange(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnChange, info)) {
        LOGW("Failed(OnChange) to bind event");
    }
    info.ReturnSelf();
}

} // namespace OHOS::Ace::Framework