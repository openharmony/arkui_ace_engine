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
#include "core/components/text_field/text_field_component.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

namespace {

const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };

}; // namespace

void JSTextArea::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextArea>::Declare("TextArea");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTextArea>::StaticMethod("create", &JSTextArea::Create, opt);
    JSClass<JSTextArea>::StaticMethod("placeholderColor", &JSTextArea::SetPlaceholderColor);
    JSClass<JSTextArea>::StaticMethod("placeholderFont", &JSTextArea::SetPlaceholderFont);
    JSClass<JSTextArea>::StaticMethod("textAlign", &JSTextArea::SetTextAlign);
    JSClass<JSTextArea>::StaticMethod("caretColor", &JSTextArea::SetCaretColor);
    JSClass<JSTextArea>::StaticMethod("correction", &JSTextArea::SetCorrection);
    JSClass<JSTextArea>::StaticMethod("onChange", &JSTextArea::SetOnChange);
    JSClass<JSTextArea>::Inherit<JSViewAbstract>();
    JSClass<JSTextArea>::Bind(globalObj);
}

void JSTextArea::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("textarea create error, info is non-vaild");
        return;
    }

    RefPtr<TextFieldComponent> textAreaComponent = AceType::MakeRefPtr<TextFieldComponent>();
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto placeholder = paramObject->GetProperty("placeholder");
    if (placeholder->IsString()) {
        textAreaComponent->SetPlaceholder(placeholder->ToString());
    }

    auto text = paramObject->GetProperty("text");
    if (text->IsString()) {
        textAreaComponent->SetValue(text->ToString());
    }
    ViewStackProcessor::GetInstance()->Push(textAreaComponent);
}

void JSTextArea::SetPlaceholderColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsString()) {
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
    }
}

void JSTextArea::SetPlaceholderFont(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("PlaceholderFont create error, info is non-vaild");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    auto paramObject = JSRef<JSObject>::Cast(info[0]);

    auto fontSize = paramObject->GetProperty("size");
    Dimension value;
    ParseJsDimensionPx(fontSize, value);
    auto textStyle = component->GetTextStyle();
    textStyle.SetFontSize(value);

    auto weight = paramObject->GetProperty("weight");
    if (!weight->IsNumber()) {
        LOGE("Info(weight) is not number");
        return;
    }
    FontWeight fontWeight = static_cast<FontWeight>(weight->ToNumber<int32_t>());
    textStyle.SetFontWeight(fontWeight);

    std::vector<std::string> fontFamilies;
    std::string fontFamily;
    if (ParseJsString(paramObject->GetProperty("fontFamily"), fontFamily)) {
        fontFamilies.push_back(fontFamily);
        textStyle.SetFontFamilies(fontFamilies);
    } else {
        LOGE("Family have a big problem");
    }

    auto style = paramObject->GetProperty("style");
    if (!style->IsNumber()) {
        LOGE("Info(style is not number");
        return;
    }
    FontStyle fontStyle = static_cast<FontStyle>(style->ToNumber<int32_t>());
    textStyle.SetFontStyle(fontStyle);
    component->SetTextStyle(std::move(textStyle));
}

void JSTextArea::SetTextAlign(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        LOGE("Info(textAlign) is not number!");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is not valid");
        return;
    }
    auto textStyle = component->GetTextStyle();
    TextAlign textAlign = static_cast<TextAlign>(info[0]->ToNumber<int32_t>());
    textStyle.SetTextAlign(textAlign);
    component->SetTextStyle(std::move(textStyle));
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

void JSTextArea::SetCorrection(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg(SetCorrection) is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsBoolean()) {
        LOGE("arg is(SetCorrection) not bool.");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::TextFieldComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("The(SetCorrection) Component is null");
        return;
    }
    component->SetCorrection(info[0]->ToBoolean());
}

void JSTextArea::SetOnChange(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&TextFieldComponent::SetOnChange, info)) {
        LOGW("Failed(OnChange) to bind event");
    }
    info.ReturnSelf();
}

} // namespace OHOS::Ace::Framework
