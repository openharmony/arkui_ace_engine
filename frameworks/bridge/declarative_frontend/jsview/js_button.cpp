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

#include "frameworks/bridge/declarative_frontend/jsview/js_button.h"

#include "base/geometry/dimension.h"
#include "base/log/ace_trace.h"
#include "core/components/button/button_component.h"
#include "core/components/button/button_theme.h"
#include "core/components/padding/padding_component.h"
#include "core/components/text/text_component.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSButton::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    auto padingComponent = AceType::DynamicCast<PaddingComponent>(buttonComponent->GetChildren().front());

    // Ignore for image button
    if (buttonComponent == nullptr || padingComponent == nullptr) {
        return;
    }
    auto textComponent = AceType::DynamicCast<TextComponent>(padingComponent->GetChild());
    if (textComponent) {
        auto textStyle = textComponent->GetTextStyle();
        textStyle.SetFontSize(fontSize);
        textStyle.SetAdaptTextSize(fontSize, fontSize);
        textComponent->SetTextStyle(std::move(textStyle));
    }
}

void JSButton::SetFontWeight(std::string value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    auto padingComponent = AceType::DynamicCast<PaddingComponent>(buttonComponent->GetChildren().front());

    // Ignore for image button
    if (buttonComponent == nullptr || padingComponent == nullptr) {
        return;
    }
    auto textComponent = AceType::DynamicCast<TextComponent>(padingComponent->GetChild());
    if (textComponent) {
        auto textStyle = textComponent->GetTextStyle();
        textStyle.SetFontWeight(ConvertStrToFontWeight(value));
        textComponent->SetTextStyle(std::move(textStyle));
    }
}

void JSButton::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    auto padingComponent = AceType::DynamicCast<PaddingComponent>(buttonComponent->GetChildren().front());

    // Ignore for image button
    if (buttonComponent == nullptr || padingComponent == nullptr) {
        return;
    }
    auto textComponent = AceType::DynamicCast<TextComponent>(padingComponent->GetChild());
    if (textComponent) {
        auto textStyle = textComponent->GetTextStyle();
        textStyle.SetTextColor(textColor);
        textComponent->SetTextStyle(std::move(textStyle));
    }
}

void JSButton::SetType(int value)
{
    if ((ButtonType)value == ButtonType::CAPSULE || (ButtonType)value == ButtonType::CIRCLE ||
        (ButtonType)value == ButtonType::ARC || (ButtonType)value == ButtonType::NORMAL) {
        auto stack = ViewStackProcessor::GetInstance();
        auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
        buttonComponent->SetType((ButtonType)value);
    } else {
        LOGE("Setting button to non valid ButtonType %d", value);
    }
}

void JSButton::SetStateEffect(bool stateEffect)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    buttonComponent->SetStateEffect(stateEffect);
}

void JSButton::JSBind(BindingTarget globalObj)
{
    JSClass<JSButton>::Declare("Button");
    JSClass<JSButton>::StaticMethod("fontColor", &JSButton::SetTextColor, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("fontSize", &JSButton::SetFontSize, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("fontWeight", &JSButton::SetFontWeight, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("type", &JSButton::SetType, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("stateEffect", &JSButton::SetStateEffect, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("onClick", &JSButton::JsOnClick);
    JSClass<JSButton>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSButton>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSButton>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSButton>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSButton>::StaticMethod("backgroundColor", &JSButton::JsBackgroundColor);
    JSClass<JSButton>::StaticMethod("width", &JSButton::JsWidth);
    JSClass<JSButton>::StaticMethod("height", &JSButton::JsHeight);
    JSClass<JSButton>::StaticMethod("borderRadius", &JSButton::JsRadius);
    JSClass<JSButton>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSButton>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSButton>::StaticMethod("size", &JSButton::JsSize);

    JSClass<JSButton>::StaticMethod("createWithLabel", &JSButton::CreateWithLabel, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("createWithChild", &JSButton::CreateWithChild, MethodOptions::NONE);
    JSClass<JSButton>::Inherit<JSContainerBase>();
    JSClass<JSButton>::Inherit<JSViewAbstract>();
    JSClass<JSButton>::Bind<>(globalObj);
}

void JSButton::CreateWithLabel(const JSCallbackInfo& info)
{
    std::list<RefPtr<Component>> buttonChildren;
    std::string label;
    if (ParseJsString(info[0], label)) {
        auto textComponent = AceType::MakeRefPtr<TextComponent>(label);
        auto buttonTheme = GetTheme<ButtonTheme>();
        auto textStyle = buttonTheme ? buttonTheme->GetTextStyle() : textComponent->GetTextStyle();
        textComponent->SetTextStyle(std::move(textStyle));
        auto padding = AceType::MakeRefPtr<PaddingComponent>();
        padding->SetPadding(buttonTheme ? buttonTheme->GetPadding() : Edge());
        padding->SetChild(textComponent);
        buttonChildren.emplace_back(padding);
    }
    auto buttonComponent = AceType::MakeRefPtr<ButtonComponent>(buttonChildren);
    SetDefaultAttributes(buttonComponent);
    if (info[0]->IsObject() || ((info.Length() > 1) && info[1]->IsObject())) {
        auto obj = info[0]->IsObject() ? JSRef<JSObject>::Cast(info[0]) : JSRef<JSObject>::Cast(info[1]);
        SetTypeAndStateEffect(obj, buttonComponent);
    }
    ViewStackProcessor::GetInstance()->Push(buttonComponent);
    JSInteractableView::SetFocusNode(true);
}

void JSButton::CreateWithChild(const JSCallbackInfo& info)
{
    std::list<RefPtr<Component>> buttonChildren;
    auto buttonComponent = AceType::MakeRefPtr<ButtonComponent>(buttonChildren);
    SetDefaultAttributes(buttonComponent);
    if (info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        SetTypeAndStateEffect(obj, buttonComponent);
    }
    ViewStackProcessor::GetInstance()->Push(buttonComponent);
    JSInteractableView::SetFocusNode(true);
}

void JSButton::SetDefaultAttributes(const RefPtr<ButtonComponent>& buttonComponent)
{
    buttonComponent->SetType(ButtonType::CAPSULE);
    buttonComponent->SetDeclarativeFlag(true);
    auto buttonTheme = GetTheme<ButtonTheme>();
    if (!buttonTheme) {
        return;
    }
    buttonComponent->SetHeight(buttonTheme->GetHeight());
    buttonComponent->SetBackgroundColor(buttonTheme->GetBgColor());
    buttonComponent->SetClickedColor(buttonComponent->GetBackgroundColor().BlendColor(buttonTheme->GetClickedColor()));
}

void JSButton::SetTypeAndStateEffect(const JSRef<JSObject>& obj, const RefPtr<ButtonComponent>& buttonComponent)
{
    auto type = obj->GetProperty("type");
    if (type->IsNumber()) {
        auto buttonType = (ButtonType)type->ToNumber<int32_t>();
        buttonComponent->SetType(buttonType);
    }
    auto stateEffect = obj->GetProperty("stateEffect");
    if (stateEffect->IsBoolean()) {
        buttonComponent->SetStateEffect(stateEffect->ToBoolean());
    }
}

void JSButton::JsOnClick(const JSCallbackInfo& info)
{
    LOGD("JSButton JsOnClick");
    if (info[0]->IsFunction()) {
        JSRef<JSFunc> clickFunction = JSRef<JSFunc>::Cast(info[0]);
        auto onClickFunc = AceType::MakeRefPtr<JsClickFunction>(clickFunction);
        EventMarker clickEventId(
            [execCtx = info.GetExecutionContext(), func = std::move(onClickFunc)](const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
                func->Execute(*clickInfo);
            });

        auto buttonComponent =
            AceType::DynamicCast<ButtonComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        buttonComponent->SetClickedEventId(clickEventId);
    }
}

void JSButton::JsBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    buttonComponent->SetBackgroundColor(backgroundColor);
    auto buttonTheme = GetTheme<ButtonTheme>();
    if (buttonTheme) {
        Color blendColor = buttonTheme->GetClickedColor();
        buttonComponent->SetClickedColor(buttonComponent->GetBackgroundColor().BlendColor(blendColor));
    }
    info.ReturnSelf();
}

void JSButton::JsWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    Dimension value = GetSizeValue(info);
    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto option = stack->GetImplicitAnimationOption();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    buttonComponent->SetWidth(value, option);
}

void JSButton::JsHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    Dimension value = GetSizeValue(info);
    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto option = stack->GetImplicitAnimationOption();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    buttonComponent->SetHeight(value, option);
}

void JSButton::JsSize(const JSCallbackInfo& info)
{
    if (info.Length() < 0) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> widthValue = sizeObj->GetProperty("width");
    Dimension width;
    if (ParseJsDimensionVp(widthValue, width)) {
        buttonComponent->SetWidth(width);
    }
    JSRef<JSVal> heightValue = sizeObj->GetProperty("height");
    Dimension height;
    if (ParseJsDimensionVp(heightValue, height)) {
        buttonComponent->SetHeight(height);
    }
}

void JSButton::JsRadius(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension radius;
    if (!ParseJsDimensionVp(info[0], radius)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    buttonComponent->SetRadiusState(true);
    buttonComponent->SetRectRadius(radius);
    JSViewAbstract::SetBorderRadius(radius, stack->GetImplicitAnimationOption());
}

Dimension JSButton::GetSizeValue(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return Dimension(-1.0);
    }
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return Dimension(-1.0);
    }
    return value;
}

} // namespace OHOS::Ace::Framework
