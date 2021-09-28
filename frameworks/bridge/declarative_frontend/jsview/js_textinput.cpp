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

#include "frameworks/bridge/declarative_frontend/jsview/js_textinput.h"

#include <vector>

#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/common/ime/text_input_action.h"
#include "frameworks/core/common/ime/text_input_type.h"
#include "frameworks/core/components/text_field/render_text_field.h"
#include "frameworks/core/components/text_field/text_field_component.h"
#include "frameworks/core/components/text_field/text_field_element.h"

namespace OHOS::Ace::Framework {

void JSTextInput::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextInput>::Declare("TextInput");
    MethodOptions opt = MethodOptions::NONE;

    JSClass<JSTextInput>::StaticMethod("create", &JSTextInput::Create, opt);
    JSClass<JSTextInput>::StaticMethod("type", &JSTextInput::SetType);
    JSClass<JSTextInput>::StaticMethod("placeholderColor", &JSTextInput::SetPlaceholderColor);
    JSClass<JSTextInput>::StaticMethod("placeholderFont", &JSTextInput::SetPlaceholderFont);
    JSClass<JSTextInput>::StaticMethod("enterKeyType", &JSTextInput::SetEnterKeyType);
    JSClass<JSTextInput>::StaticMethod("caretColor", &JSTextInput::SetCaretColor);
    JSClass<JSTextInput>::StaticMethod("onEditChanged", &JSTextInput::SetOnEditChanged);
    JSClass<JSTextInput>::StaticMethod("onSubmit", &JSTextInput::SetOnSubmit);
    JSClass<JSTextInput>::StaticMethod("onChange", &JSTextInput::SetOnChange);
    
    JSClass<JSTextInput>::Inherit<JSViewAbstract>();
    JSClass<JSTextInput>::Bind(globalObj);
}

void JSTextInput::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("text-input create error, info is non-vaild");
        return;
    }

    RefPtr<TextFieldComponent> textInputComponent = AceType::MakeRefPtr<TextFieldComponent>();
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto placeholder = paramObject->GetProperty("placeholder");
    if (placeholder->IsString()) {
        textInputComponent->SetPlaceholder(placeholder->ToString());
    }

    auto text = paramObject->GetProperty("text");
    if (text->IsString()) {
        textInputComponent->SetValue(text->ToString());
    }
    ViewStackProcessor::GetInstance()->Push(textInputComponent);
}

void JSTextInput::SetType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("SetType create error, info is non-valid");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!info[0]->IsNumber()) {
        LOGE("The inputType is not number");
        return;
    }
    TextInputType textInputType = static_cast<TextInputType>(info[0]->ToNumber<int32_t>());
    component->SetTextInputType(textInputType);
    component->SetObscure(textInputType == TextInputType::VISIBLE_PASSWORD);
}

void JSTextInput::SetPlaceholderColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg(SetPlaceholderColor) is wrong, it is supposed to have atlease 1 argument");
        return;
    }

    Color color;
    if (!ParseJsColor(info[0], color)) {
        LOGE("the info[0] is null");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (component) {
        component->SetPlaceholderColor(color);
    } else {
        LOGE("The component(SetPlaceholderColor) is null");
        return;
    }
}

void JSTextInput::SetPlaceholderFont(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("PlaceholderFont create error, info is non-vaild");
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

    auto weight = paramObject->GetProperty("weight");
    if (!weight->IsNull()) {
        FontWeight fontWeight = static_cast<FontWeight>(weight->ToNumber<int32_t>());
        textStyle.SetFontWeight(fontWeight);
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

void JSTextInput::SetEnterKeyType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
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

void JSTextInput::SetCaretColor(const JSCallbackInfo& info)
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
        return;
    }
}

void JSTextInput::SetOnEditChanged(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnEditChanged, info)) {
        LOGW("Failed(OnEditChanged) to bind event");
    }
    info.ReturnSelf();
}

void JSTextInput::SetOnSubmit(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnSubmit, info)) {
        LOGW("Failed(OnSubmit) to bind event");
    }
    info.ReturnSelf();
}

void JSTextInput::SetOnChange(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnChange, info)) {
        LOGW("Failed(OnChange) to bind event");
    }
    info.ReturnSelf();
}

} // namespace OHOS::Ace::Framework