/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_textfield.h"

#include <vector>

#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_clipboard_function.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/common/ime/text_input_action.h"
#include "frameworks/core/common/ime/text_input_type.h"
#include "frameworks/core/components/text_field/text_field_component.h"
#include "frameworks/core/components/text_field/textfield_theme.h"

namespace OHOS::Ace::Framework {

const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };

void JSTextField::SetType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("SetType create error, info is non-valid");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    if (!info[0]->IsNumber()) {
        LOGE("The inputType is not number");
        return;
    }
    TextInputType textInputType = static_cast<TextInputType>(info[0]->ToNumber<int32_t>());
    component->SetTextInputType(textInputType);
    component->SetObscure(textInputType == TextInputType::VISIBLE_PASSWORD);
}

void JSTextField::SetPlaceholderColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg(SetPlaceholderColor) is wrong, it is supposed to have atleast 1 argument");
        return;
    }

    Color color;
    if (!ParseJsColor(info[0], color)) {
        LOGE("the info[0] is null");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    if (component) {
        component->SetPlaceholderColor(color);
        component->SetFocusPlaceholderColor(color);
    } else {
        LOGE("The component(SetPlaceholderColor) is null");
    }
}

void JSTextField::SetPlaceholderFont(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("PlaceholderFont create error, info is non-valid");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("The component(SetPlaceholderFont) is null");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto textStyle = component->GetPlaceHoldStyle();

    auto fontSize = paramObject->GetProperty("size");
    if (!fontSize->IsNull()) {
        Dimension size;
        if (!ParseJsDimensionFp(fontSize, size)) {
            LOGE("Parse to dimension FP failed.");
        } else {
            textStyle.SetFontSize(size);
        }
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
    component->SetPlaceHoldStyle(textStyle);
}

void JSTextField::SetEnterKeyType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("The component(SetEnterKeyType) is null");
        return;
    }
    if (!info[0]->IsNumber()) {
        LOGE("Info(SetEnterKeyType) is not number");
        return;
    }
    TextInputAction textInputAction = static_cast<TextInputAction>(info[0]->ToNumber<int32_t>());
    component->SetAction(textInputAction);
}

void JSTextField::SetTextAlign(int32_t value)
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

void JSTextField::SetInputStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg(SetInputStyle) is wrong, it is supposed to have at least 1 argument");
        return;
    }
    
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("textAlign component is not valid");
        return;
    }
    auto styleString = info[0]->ToString();
    if (styleString == "Inline") {
        component->SetInputStyle(InputStyle::INLINE);
    } else {
        component->SetInputStyle(InputStyle::DEFAULT);
    }
}

void JSTextField::SetCaretColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg(SetCareColor) is wrong, it is supposed to have atleast 1 argument");
        return;
    }

    Color color;
    if (!ParseJsColor(info[0], color)) {
        LOGE("info[0] is null");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    if (component) {
        component->SetCursorColor(color);
    } else {
        LOGE("The component(SetCaretColor) is null");
    }
}

void JSTextField::SetMaxLength(uint32_t value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    if (component) {
        component->SetMaxLength(value);
    }
}

void JSTextField::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JSTextField::SetFontSize The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        LOGE("Parse to dimension FP failed!");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("JSTextField::SetFontSize component is not valid");
        return;
    }

    auto textStyle = component->GetEditingStyle();
    textStyle.SetFontSize(fontSize);
    component->SetEditingStyle(textStyle);
}

void JSTextField::SetFontWeight(const std::string& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetEditingStyle();
    textStyle.SetFontWeight(ConvertStrToFontWeight(value));
    component->SetEditingStyle(textStyle);
}

void JSTextField::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        LOGE("Parse to dimension FP failed!");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetEditingStyle();
    textStyle.SetTextColor(textColor);
    component->SetEditingStyle(textStyle);
}

void JSTextField::SetFontStyle(int32_t value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
        auto textStyle = component->GetEditingStyle();
        textStyle.SetFontStyle(FONT_STYLES[value]);
        component->SetEditingStyle(textStyle);
    } else {
        LOGE("TextInput fontStyle(%d) illegal value", value);
    }
}

void JSTextField::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        LOGE("Parse FontFamilies failed");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    auto textStyle = component->GetEditingStyle();
    textStyle.SetFontFamilies(fontFamilies);
    component->SetEditingStyle(textStyle);
}

void JSTextField::SetInputFilter(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    std::string inputFilter;
    if (!ParseJsString(info[0], inputFilter)) {
        LOGE("Parse inputFilter failed");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is not valid");
        return;
    }

    component->SetInputFilter(inputFilter);

    if (info[1]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsClipboardFunction>(JSRef<JSFunc>::Cast(info[1]));
        auto resultId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(info);
        };
        component->SetOnError(resultId);
    }
}

void JSTextField::SetShowPasswordIcon(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        LOGE("The info is wrong, it is supposed to be an boolean");
        return;
    }

    bool isShowPasswordIcon = info[0]->ToBoolean();
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is not valid");
        return;
    }
    component->SetShowPasswordIcon(isShowPasswordIcon);
}

void JSTextField::SetBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg(SetBackgroundColor) is wrong, it is supposed to have atleast 1 argument");
        return;
    }

    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor)) {
        LOGE("the info[0] is null");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (component) {
        component->SetBgColor(backgroundColor);
    } else {
        LOGE("The component(SetPlaceholderColor) is null");
    }
}

void JSTextField::JsHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        LOGE("Parse to dimension VP failed!");
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        LOGE("dimension value: %{public}f is invalid!", value.Value());
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto textInputComponent = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    if (!textInputComponent) {
        LOGE("JSTextInput set height failed, textInputComponent is null.");
        return;
    }
    textInputComponent->SetHeight(value);
}

void JSTextField::JsPadding(const JSCallbackInfo& info)
{
    if (!info[0]->IsString() && !info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGE("arg is not a string, number or object.");
        return;
    }
    Edge padding;
    if (info[0]->IsNumber() || info[0]->IsString()) {
        Dimension edgeValue;
        if (ParseJsDimensionVp(info[0], edgeValue)) {
            padding = Edge(edgeValue);
        }
    }
    if (info[0]->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
        Dimension left = Dimension(0.0, DimensionUnit::VP);
        Dimension top = Dimension(0.0, DimensionUnit::VP);
        Dimension right = Dimension(0.0, DimensionUnit::VP);
        Dimension bottom = Dimension(0.0, DimensionUnit::VP);
        ParseJsDimensionVp(object->GetProperty("left"), left);
        ParseJsDimensionVp(object->GetProperty("top"), top);
        ParseJsDimensionVp(object->GetProperty("right"), right);
        ParseJsDimensionVp(object->GetProperty("bottom"), bottom);
        padding = Edge(left, top, right, bottom);
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<TextFieldComponent>(stack->GetMainComponent());
    if (component) {
        auto decoration = component->GetDecoration();
        decoration->SetPadding(padding);
    }
}

void JSTextField::JsBorder(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        LOGE("args is not a object. %s", info[0]->ToString().c_str());
        return;
    }
    RefPtr<Decoration> decoration = nullptr;
    auto component = AceType::DynamicCast<TextFieldComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        decoration = component->GetDecoration();
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    auto valueWidth = object->GetProperty("width");
    if (!valueWidth->IsUndefined()) {
        ParseBorderWidth(valueWidth, decoration);
    }
    auto valueColor = object->GetProperty("color");
    if (!valueColor->IsUndefined()) {
        ParseBorderColor(valueColor, decoration);
    }
    auto valueRadius = object->GetProperty("radius");
    if (!valueRadius->IsUndefined()) {
        ParseBorderRadius(valueRadius, decoration);
    }
    auto valueStyle = object->GetProperty("style");
    if (!valueStyle->IsUndefined()) {
        ParseBorderStyle(valueStyle, decoration);
    }
    if (component) {
        component->SetOriginBorder(decoration->GetBorder());
    }
    info.ReturnSelf();
}

void JSTextField::JsBorderWidth(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("args need a string or number or object");
        return;
    }
    RefPtr<Decoration> decoration = nullptr;
    auto component = AceType::DynamicCast<TextFieldComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        decoration = component->GetDecoration();
    }
    JSViewAbstract::ParseBorderWidth(info[0], decoration);
    if (component) {
        component->SetOriginBorder(decoration->GetBorder());
    }
}

void JSTextField::JsBorderColor(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("args need a string or number or object");
        return;
    }
    RefPtr<Decoration> decoration = nullptr;
    auto component = AceType::DynamicCast<TextFieldComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        decoration = component->GetDecoration();
    }
    JSViewAbstract::ParseBorderColor(info[0], decoration);
    if (component) {
        component->SetOriginBorder(decoration->GetBorder());
    }
}

void JSTextField::JsBorderStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject() && !info[0]->IsNumber()) {
        LOGE("args need a string or number or object");
        return;
    }
    RefPtr<Decoration> decoration = nullptr;
    auto component = AceType::DynamicCast<TextFieldComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        decoration = component->GetDecoration();
    }
    JSViewAbstract::ParseBorderStyle(info[0], decoration);
    if (component) {
        component->SetOriginBorder(decoration->GetBorder());
    }
}

void JSTextField::JsBorderRadius(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject() && !info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("args need a string or number or object");
        return;
    }
    RefPtr<Decoration> decoration = nullptr;
    auto component = AceType::DynamicCast<TextFieldComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        decoration = component->GetDecoration();
    }
    JSViewAbstract::ParseBorderRadius(info[0], decoration);
    if (component) {
        component->SetOriginBorder(decoration->GetBorder());
    }
}

void JSTextField::JsHoverEffect(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        LOGE("info[0] is not a number");
        return;
    }
    auto component = AceType::DynamicCast<TextFieldComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        component->SetHoverAnimationType(static_cast<HoverAnimationType>(info[0]->ToNumber<int32_t>()));
    }
}

void JSTextField::SetOnEditChanged(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnEditChanged, info)) {
        LOGW("Failed(OnEditChanged) to bind event");
    }
    info.ReturnSelf();
}

void JSTextField::SetOnSubmit(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnSubmit, info)) {
        LOGW("Failed(OnSubmit) to bind event");
    }
    info.ReturnSelf();
}

void JSTextField::SetOnChange(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnChange, info)) {
        LOGW("Failed(OnChange) to bind event");
    }
    info.ReturnSelf();
}

void JSTextField::SetOnCopy(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnCopy, info)) {
        LOGW("Failed(OnCopy) to bind event");
    }
    info.ReturnSelf();
}

void JSTextField::SetOnCut(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnCut, info)) {
        LOGW("Failed(OnCut) to bind event");
    }
    info.ReturnSelf();
}

void JSTextField::SetOnPaste(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnPaste, info)) {
        LOGW("Failed(OnPaste) to bind event");
    }
    info.ReturnSelf();
}

void JSTextField::SetOnClick(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnClick, info)) {
        LOGW("Failed(OnPaste) to bind event");
    }
    info.ReturnSelf();
}

void JSTextField::SetCopyOption(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto copyOptions = CopyOptions::None;
    if (info[0]->IsNumber()) {
        auto emunNumber = info[0]->ToNumber<int>();
        copyOptions = static_cast<CopyOptions>(emunNumber);
    }
    LOGI("copy option: %{public}d", copyOptions);
    JSViewSetProperty(&TextFieldComponent::SetCopyOption, copyOptions);
}

void JSTextField::UpdateDecoration(const RefPtr<BoxComponent>& boxComponent,
    const RefPtr<TextFieldComponent>& component, const Border& boxBorder,
    const OHOS::Ace::RefPtr<OHOS::Ace::TextFieldTheme>& textFieldTheme)
{
    if (!textFieldTheme) {
        LOGE("UpdateDecoration: textFieldTheme is null.");
        return;
    }

    RefPtr<Decoration> decoration = component->GetDecoration();
    RefPtr<Decoration> boxDecoration = boxComponent->GetBackDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
    }
    if (boxDecoration) {
        Border border = decoration->GetBorder();
        border.SetLeftEdge(boxBorder.Left());
        border.SetRightEdge(boxBorder.Right());
        border.SetTopEdge(boxBorder.Top());
        border.SetBottomEdge(boxBorder.Bottom());
        border.SetBorderRadius(textFieldTheme->GetBorderRadius());
        decoration->SetBorder(border);
        component->SetOriginBorder(decoration->GetBorder());

        if (boxDecoration->GetImage() || boxDecoration->GetGradient().IsValid()) {
            // clear box properties except background image and radius.
            boxDecoration->SetBackgroundColor(Color::TRANSPARENT);
            Border border;
            border.SetBorderRadius(textFieldTheme->GetBorderRadius());
            boxDecoration->SetBorder(border);
        }
    } else {
        boxDecoration = AceType::MakeRefPtr<Decoration>();
        boxDecoration->SetBorderRadius(textFieldTheme->GetBorderRadius());
        boxComponent->SetBackDecoration(boxDecoration);
    }
}

} // namespace OHOS::Ace::Framework