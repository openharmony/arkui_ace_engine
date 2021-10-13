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

#include "frameworks/bridge/declarative_frontend/jsview/js_textarea.h"

#include<vector>
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/text_field/render_text_field.h"
#include "core/components/text_field/text_field_component.h"
#include "core/components/text_field/text_field_element.h"
#include "core/components/text_field/textfield_theme.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

namespace {

const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<std::string> INPUT_FONT_FAMILY_VALUE = {"sans-serif"};
constexpr uint32_t TEXTAREA_MAXLENGTH_VALUE_DEFAULT = std::numeric_limits<uint32_t>::max();
constexpr Dimension BOX_HOVER_RADIUS = 18.0_vp;

}; // namespace

void JSTextArea::PrepareSpecializedComponent()
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto stack = ViewStackProcessor::GetInstance();
    auto textAreaComponent = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    std::vector<InputOption> inputOptions;
    if (!boxComponent || !textAreaComponent) {
        return;
    }
    boxComponent->SetMouseAnimationType(HoverAnimationType::OPACITY);
    textAreaComponent->SetInputOptions(inputOptions);
    textAreaComponent->SetImageFill(Color::RED);
    UpdateDecoration();
    boxComponent->SetPadding(Edge());
    boxComponent->SetDeliverMinToChild(true);
    auto theme = GetTheme<TextFieldTheme>();
    if (boxComponent->GetHeightDimension().Value() < 0.0 && theme) {
        boxComponent->SetHeight(theme->GetHeight().Value(), theme->GetHeight().Unit());
    }
    textAreaComponent->SetHeight(boxComponent->GetHeightDimension());
    if (textAreaComponent->IsExtend()) {
        boxComponent->SetHeight(-1.0, DimensionUnit::PX);
    }
}

void JSTextArea::UpdateDecoration()
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto stack = ViewStackProcessor::GetInstance();
    auto textAreaComponent = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    auto theme = GetTheme<TextFieldTheme>();
    Radius defaultRadius_;
    bool hasBoxRadius = false;

    if (!boxComponent || !textAreaComponent) {
        return;
    }
    RefPtr<Decoration> backDecoration = boxComponent->GetBackDecoration();
    RefPtr<Decoration> decoration = textAreaComponent->GetDecoration();
    if (backDecoration) {
        Border boxBorder = backDecoration->GetBorder();
        if (decoration) {
            if (hasBoxRadius) {
                decoration->SetBorder(boxBorder);
            } else {
                Border border = decoration->GetBorder();
                border.SetLeftEdge(boxBorder.Left());
                border.SetRightEdge(boxBorder.Right());
                border.SetTopEdge(boxBorder.Top());
                border.SetBottomEdge(boxBorder.Bottom());
                decoration->SetBorder(border);
            }
            textAreaComponent->SetOriginBorder(decoration->GetBorder());
        }

        if (backDecoration->GetImage() || backDecoration->GetGradient().IsValid()) {
            backDecoration->SetBackgroundColor(Color::TRANSPARENT);
            Border border;
            if (!hasBoxRadius) {
                border.SetBorderRadius(defaultRadius_);
            } else {
                border.SetTopLeftRadius(boxBorder.TopLeftRadius());
                border.SetTopRightRadius(boxBorder.TopRightRadius());
                border.SetBottomLeftRadius(boxBorder.BottomLeftRadius());
                border.SetBottomRightRadius(boxBorder.BottomRightRadius());
            }
            backDecoration->SetBorder(border);
        } else {
            backDecoration = AceType::MakeRefPtr<Decoration>();
            backDecoration->SetBorderRadius(Radius(BOX_HOVER_RADIUS));
            boxComponent->SetBackDecoration(backDecoration);
        }
    }
}

void JSTextArea::InitializeStyle()
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto stack = ViewStackProcessor::GetInstance();
    auto textAreaComponent = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    auto theme = GetTheme<TextFieldTheme>();
    TextStyle textStyle;
    if (!boxComponent || !textAreaComponent || !theme) {
        return;
    }
    textAreaComponent->SetTextMaxLines(TEXTAREA_MAXLENGTH_VALUE_DEFAULT);
    textAreaComponent->SetCursorColor(theme->GetCursorColor());
    textAreaComponent->SetTextInputType(TextInputType::MULTILINE);
    textAreaComponent->SetPlaceholderColor(theme->GetPlaceholderColor());
    textAreaComponent->SetFocusBgColor(theme->GetFocusBgColor());
    textAreaComponent->SetFocusPlaceholderColor(theme->GetFocusPlaceholderColor());
    textAreaComponent->SetFocusTextColor(theme->GetFocusTextColor());
    textAreaComponent->SetBgColor(theme->GetBgColor());
    textAreaComponent->SetTextColor(theme->GetTextColor());
    textAreaComponent->SetSelectedColor(theme->GetSelectedColor());
    textAreaComponent->SetHoverColor(theme->GetHoverColor());
    textAreaComponent->SetPressColor(theme->GetPressColor());
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
    Radius defaultRadius;
    defaultRadius = theme->GetBorderRadius();
    backDecoration->SetBorderRadius(defaultRadius);
    if (boxComponent->GetBackDecoration()) {
        backDecoration->SetImage(boxComponent->GetBackDecoration()->GetImage());
        backDecoration->SetGradient(boxComponent->GetBackDecoration()->GetGradient());
    }
    textAreaComponent->SetDecoration(backDecoration);
    textAreaComponent->SetIconSize(theme->GetIconSize());
    textAreaComponent->SetIconHotZoneSize(theme->GetIconHotZoneSize());
    boxComponent->SetBackDecoration(backDecoration);
    boxComponent->SetPadding(theme->GetPadding());
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
    auto paramObject = JSRef<JSObject>::Cast(info[0]);

    std::string placeholder;
    if (ParseJsString(paramObject->GetProperty("placeholder"), placeholder)) {
        textAreaComponent->SetPlaceholder(placeholder);
    }

    textAreaComponent->SetExtend(true);
    std::string text;
    if (ParseJsString(paramObject->GetProperty("text"), text)) {
        textAreaComponent->SetValue(text);
    }
    ViewStackProcessor::GetInstance()->Push(textAreaComponent);
    InitializeStyle();
    PrepareSpecializedComponent();
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
    if (ParseJsString(paramObject->GetProperty("weight"), weight)) {
        textStyle.SetFontWeight(ConvertStrToFontWeight(weight));
    }

    auto font = paramObject->GetProperty("family");
    if (!font->IsNull()) {
        std::vector<std::string> fontFamilies;
        if (ParseJsFontFamilies(font, fontFamilies)) {
            textStyle.SetFontFamilies(fontFamilies);
        }
    }

    auto style = paramObject->GetProperty("style");
    if (!style->IsNull()) {
        FontStyle fontStyle = static_cast<FontStyle>(style->ToNumber<int32_t>());
        textStyle.SetFontStyle(fontStyle);
    }
    component->SetTextStyle(std::move(textStyle));
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

void JSTextArea::SetOnChange(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnChange, info)) {
        LOGW("Failed(OnChange) to bind event");
    }
    info.ReturnSelf();
}

} // namespace OHOS::Ace::Framework