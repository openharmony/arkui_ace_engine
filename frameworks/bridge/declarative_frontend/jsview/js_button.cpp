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
namespace {

constexpr Dimension TEXT_FONT_SIZE = 16.0_fp;
constexpr Dimension TEXT_FONT_MIN_SIZE = 12.0_fp;
constexpr Dimension BUTTON_DEFAULT_WIDTH = 150.0_vp;
constexpr Dimension BUTTON_DEFAULT_HEIGHT = 40.0_vp;
constexpr uint32_t CLICKED_BLEND_COLOR = 0x19000000;

} // namespace

void JSButton::SetFontSize(double value)
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
        auto fontSize = Dimension(value, DimensionUnit::FP);
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

void JSButton::SetTextColor(std::string value)
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
        textStyle.SetTextColor(Color::FromString(value));
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
    JSClass<JSButton>::StaticMethod("color", &JSButton::SetTextColor, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("fontSize", &JSButton::SetFontSize, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("fontWeight", &JSButton::SetFontWeight, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("type", &JSButton::SetType, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("stateEffect", &JSButton::SetStateEffect, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("onClick", &JSButton::JsOnClick);
    JSClass<JSButton>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
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
    if (info[0]->IsString()) {
        std::string label = info[0]->ToString();
        auto textComponent = AceType::MakeRefPtr<TextComponent>(label);
        auto textStyle = textComponent->GetTextStyle();
        textStyle.SetAdaptTextSize(TEXT_FONT_SIZE, TEXT_FONT_MIN_SIZE);
        textComponent->SetTextStyle(std::move(textStyle));
        auto padding = AceType::MakeRefPtr<PaddingComponent>();
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
    buttonComponent->SetWidth(BUTTON_DEFAULT_WIDTH);
    buttonComponent->SetHeight(BUTTON_DEFAULT_HEIGHT);
    buttonComponent->SetDeclarativeFlag(true);
    buttonComponent->SetBackgroundColor(Color::GRAY);
    buttonComponent->SetClickedColor(buttonComponent->GetBackgroundColor().BlendColor(Color(CLICKED_BLEND_COLOR)));
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
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
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
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsString() && !info[0]->IsNumber()) {
        LOGE("arg is not a string or number.");
        return;
    }

    Color color;
    if (info[0]->IsString()) {
        color = Color::FromString(info[0]->ToString());
    } else if (info[0]->IsNumber()) {
        color = Color(ColorAlphaAdapt(info[0]->ToNumber<uint32_t>()));
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    buttonComponent->SetBackgroundColor(color);
    buttonComponent->SetClickedColor(buttonComponent->GetBackgroundColor().BlendColor(Color(CLICKED_BLEND_COLOR)));
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
    if (!widthValue->IsNull() && !widthValue->IsEmpty()) {
        Dimension width;
        if (widthValue->IsNumber()) {
            width = Dimension(widthValue->ToNumber<double>(), DimensionUnit::VP);
            buttonComponent->SetWidth(width);
        } else if (widthValue->IsString()) {
            width = StringUtils::StringToDimension(widthValue->ToString(), true);
            buttonComponent->SetWidth(width);
        }
    }

    JSRef<JSVal> heightValue = sizeObj->GetProperty("height");
    if (!heightValue->IsNull() && !heightValue->IsEmpty()) {
        Dimension height;
        if (heightValue->IsNumber()) {
            height = Dimension(heightValue->ToNumber<double>(), DimensionUnit::VP);
            buttonComponent->SetHeight(height);
        } else if (heightValue->IsString()) {
            height = StringUtils::StringToDimension(heightValue->ToString(), true);
            buttonComponent->SetHeight(height);
        }
    }
}

void JSButton::JsRadius(const JSCallbackInfo& info)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    auto radius = ParseDimension(info);
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

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return Dimension(-1.0);
    }

    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(info[0]->ToString(), true);
    }

    return value;
}

} // namespace OHOS::Ace::Framework
