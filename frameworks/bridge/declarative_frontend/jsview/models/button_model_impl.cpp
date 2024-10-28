/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/models/button_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/box/box_component_helper.h"
#include "core/components/button/button_component.h"
#include "core/components/padding/padding_component.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::Framework {
void ButtonModelImpl::SetFontSize(const Dimension& fontSize)
{
    auto textComponent = GetTextComponent();
    if (textComponent) {
        auto textStyle = textComponent->GetTextStyle();
        textStyle.SetFontSize(fontSize);
        textStyle.SetAdaptTextSize(fontSize, fontSize);
        textComponent->SetTextStyle(textStyle);
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    if (!buttonComponent) {
        return;
    }
    if (buttonComponent->NeedResetHeight()) {
        ResetButtonHeight();
    }
}

void ButtonModelImpl::SetFontWeight(const Ace::FontWeight& fontWeight)
{
    auto textComponent = GetTextComponent();
    if (textComponent) {
        auto textStyle = textComponent->GetTextStyle();
        textStyle.SetFontWeight(fontWeight);
        textComponent->SetTextStyle(textStyle);
    }
}

void ButtonModelImpl::SetFontStyle(const Ace::FontStyle& fontStyle)
{
    auto textComponent = GetTextComponent();
    if (textComponent) {
        auto textStyle = textComponent->GetTextStyle();
        textStyle.SetFontStyle(fontStyle);
        textComponent->SetTextStyle(textStyle);
    }
}

void ButtonModelImpl::SetFontFamily(const std::vector<std::string>& fontFamily)
{
    auto textComponent = GetTextComponent();
    if (textComponent) {
        auto textStyle = textComponent->GetTextStyle();
        textStyle.SetFontFamilies(fontFamily);
        textComponent->SetTextStyle(textStyle);
    }
}

void ButtonModelImpl::SetFontColor(const Color& textColor)
{
    auto textComponent = GetTextComponent();
    if (textComponent) {
        auto textStyle = textComponent->GetTextStyle();
        textStyle.SetTextColor(textColor);
        textComponent->SetTextStyle(textStyle);
    }
}

void ButtonModelImpl::SetType(const int value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    if (buttonComponent) {
        buttonComponent->SetType((ButtonType)value);
    }
}

void ButtonModelImpl::SetStateEffect(const bool stateEffect)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    if (buttonComponent) {
        buttonComponent->SetStateEffect(stateEffect);
    }
}

void ButtonModelImpl::CreateWithLabel(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren)
{
    if (para.parseSuccess.value()) {
        auto textComponent = AceType::MakeRefPtr<TextComponent>(para.label.value());
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        auto textStyle = buttonTheme ? buttonTheme->GetTextStyle() : textComponent->GetTextStyle();
        textStyle.SetMaxLines(buttonTheme ? buttonTheme->GetTextMaxLines() : 1);
        textStyle.SetTextOverflow(TextOverflow::ELLIPSIS);
        textComponent->SetTextStyle(textStyle);
        auto padding = AceType::MakeRefPtr<PaddingComponent>();
        padding->SetPadding(buttonTheme ? buttonTheme->GetPadding() : Edge());
        padding->SetChild(textComponent);
        Component::MergeRSNode(padding, textComponent);
        buttonChildren.emplace_back(padding);
    }
}

void ButtonModelImpl::Create(const CreateWithPara& para, std::list<RefPtr<Component>>& buttonChildren)
{
    auto buttonComponent = AceType::MakeRefPtr<ButtonComponent>(buttonChildren);
    ViewStackProcessor::GetInstance()->ClaimElementId(buttonComponent);
    buttonComponent->SetHasCustomChild(false);
    buttonComponent->SetCatchMode(false);
    SetDefaultAttributes(buttonComponent);
    SetTypeAndStateEffect(para.type, para.stateEffect, buttonComponent);
    ViewStackProcessor::GetInstance()->Push(buttonComponent);
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    if (focusableComponent) {
        focusableComponent->SetFocusable(true);
    }
    auto focusNodeComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusNodeComponent) {
        focusNodeComponent->SetFocusNode(false);
    }

    buttonComponent->SetMouseAnimationType(HoverAnimationType::SCALE);
}

void ButtonModelImpl::CreateWithChild(const CreateWithPara& para)
{
    std::list<RefPtr<Component>> buttonChildren;
    auto buttonComponent = AceType::MakeRefPtr<ButtonComponent>(buttonChildren);
    ViewStackProcessor::GetInstance()->ClaimElementId(buttonComponent);
    buttonComponent->SetHasCustomChild(true);
    buttonComponent->SetCatchMode(false);
    SetDefaultAttributes(buttonComponent);
    SetTypeAndStateEffect(para.type, para.stateEffect, buttonComponent);
    ViewStackProcessor::GetInstance()->Push(buttonComponent);
    JSInteractableView::SetFocusable(true);
    JSInteractableView::SetFocusNode(true);
    buttonComponent->SetMouseAnimationType(HoverAnimationType::SCALE);
    if (buttonComponent->NeedResetHeight()) {
        ResetButtonHeight();
    }
}

void ButtonModelImpl::Padding(const NG::PaddingProperty& paddingNew, const Edge& paddingOld)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    if (component) {
        auto paddingChild = AceType::DynamicCast<PaddingComponent>(component->GetChildren().front());
        if (paddingChild) {
            paddingChild->SetPadding(paddingOld);
        }
        if (component->NeedResetHeight()) {
            ResetButtonHeight();
        }
    }
}

void ButtonModelImpl::OnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc,
    double distanceThreshold)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    CHECK_NULL_VOID(inspector);
    auto impl = inspector->GetInspectorFunctionImpl();
    RefPtr<Gesture> tapGesture = AceType::MakeRefPtr<TapGesture>(1, 1);
    tapGesture->SetOnActionId([func = std::move(tapEventFunc), impl](GestureEvent& info) {
        if (impl) {
            impl->UpdateEventInfo(info);
        }
        func(info);
    });
    auto click = ViewStackProcessor::GetInstance()->GetBoxComponent();
    click->SetOnClick(tapGesture);

    auto onClickId = EventMarker([func = std::move(clickEventFunc), impl](const BaseEventInfo* info) {
        const auto* clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
        if (!clickInfo) {
            return;
        }
        auto newInfo = *clickInfo;
        if (impl) {
            impl->UpdateEventInfo(newInfo);
        }
        func(clickInfo);
    });
    auto buttonComponent =
        AceType::DynamicCast<ButtonComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (buttonComponent) {
        buttonComponent->SetKeyEnterEventId(onClickId);
    }
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusableComponent) {
        focusableComponent->SetOnClickId(onClickId);
    }
}

void ButtonModelImpl::BackgroundColor(const Color& color, const bool& colorFlag)
{
    if (!colorFlag) {
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    CHECK_NULL_VOID(buttonComponent);

    if (!stack->IsVisualStateSet()) {
        buttonComponent->SetBackgroundColor(color);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        if (buttonTheme) {
            Color blendColor = buttonTheme->GetClickedColor();
            buttonComponent->SetClickedColor(buttonComponent->GetBackgroundColor().BlendColor(blendColor));
        }
    } else {
        buttonComponent->GetStateAttributes()->AddAttribute<AnimatableColor>(
            ButtonStateAttribute::COLOR, AnimatableColor(color, option), stack->GetVisualState());
        if (!buttonComponent->GetStateAttributes()->HasAttribute(ButtonStateAttribute::COLOR, VisualState::NORMAL)) {
            buttonComponent->GetStateAttributes()->AddAttribute<AnimatableColor>(ButtonStateAttribute::COLOR,
                AnimatableColor(buttonComponent->GetBackgroundColor(), option), VisualState::NORMAL);
        }
    }
}

void ButtonModelImpl::SetWidth(const Dimension& width)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    AnimationOption option = stack->GetImplicitAnimationOption();
    CHECK_NULL_VOID(buttonComponent);
    if (!stack->IsVisualStateSet()) {
        buttonComponent->SetWidth(width, stack->GetImplicitAnimationOption());
    } else {
        buttonComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(
            ButtonStateAttribute::WIDTH, AnimatableDimension(width, option), stack->GetVisualState());
        if (!buttonComponent->GetStateAttributes()->HasAttribute(ButtonStateAttribute::WIDTH, VisualState::NORMAL)) {
            buttonComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(ButtonStateAttribute::WIDTH,
                AnimatableDimension(buttonComponent->GetWidth(), option), VisualState::NORMAL);
        }
    }
}

void ButtonModelImpl::SetHeight(const Dimension& height)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    auto option = stack->GetImplicitAnimationOption();
    CHECK_NULL_VOID(buttonComponent);
    buttonComponent->IsNeedResetHeight(false);
    if (!stack->IsVisualStateSet()) {
        buttonComponent->SetHeight(height, option);
        buttonComponent->SetDeclareHeight(true);
    } else {
        buttonComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(
            ButtonStateAttribute::HEIGHT, AnimatableDimension(height, option), stack->GetVisualState());
        if (!buttonComponent->GetStateAttributes()->HasAttribute(ButtonStateAttribute::HEIGHT, VisualState::NORMAL)) {
            buttonComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(ButtonStateAttribute::HEIGHT,
                AnimatableDimension(buttonComponent->GetHeight(), option), VisualState::NORMAL);
        }
    }
}

void ButtonModelImpl::SetAspectRatio(const double& ratio)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    CHECK_NULL_VOID(buttonComponent);
    buttonComponent->SetAspectRatio(ratio);
}

void ButtonModelImpl::SetSize(const std::optional<Dimension>& width, const std::optional<Dimension>& height)
{
    if (width.has_value()) {
        SetWidth(width.value());
    } else {
        SetHeight(height.value());
    }
}

void ButtonModelImpl::SetBorderRadius(const Dimension& radius)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    auto option = stack->GetImplicitAnimationOption();
    CHECK_NULL_VOID(buttonComponent);
    buttonComponent->SetRadiusState(true);
    if (!stack->IsVisualStateSet()) {
        buttonComponent->SetRectRadius(radius);
        ViewAbstractModel::GetInstance()->SetBorderRadius(radius);
    } else {
        buttonComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(
            ButtonStateAttribute::RADIUS, AnimatableDimension(radius, option), stack->GetVisualState());
        auto boxComponent = stack->GetBoxComponent();
        boxComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(
            BoxStateAttribute::BORDER_RADIUS, AnimatableDimension(radius, option), stack->GetVisualState());

        if (!buttonComponent->GetStateAttributes()->HasAttribute(ButtonStateAttribute::RADIUS, VisualState::NORMAL)) {
            buttonComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(ButtonStateAttribute::RADIUS,
                AnimatableDimension(buttonComponent->GetRectRadius(), option), VisualState::NORMAL);
            auto defaultRadius = BoxComponentHelper::GetBorderRadius(boxComponent->GetBackDecoration());
            boxComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(BoxStateAttribute::BORDER_RADIUS,
                AnimatableDimension(defaultRadius.GetX(), option), VisualState::NORMAL);
        }
    }
}

RefPtr<TextComponent> ButtonModelImpl::GetTextComponent()
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    if (buttonComponent == nullptr) {
        LOGE("Button component create failed");
        return nullptr;
    }
    auto paddingComponent = AceType::DynamicCast<PaddingComponent>(buttonComponent->GetChildren().front());
    if (!paddingComponent) {
        LOGE("Padding component create failed");
        return nullptr;
    }
    auto textComponent = AceType::DynamicCast<TextComponent>(paddingComponent->GetChild());
    return textComponent;
}

void ButtonModelImpl::ResetButtonHeight()
{
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    if (buttonComponent) {
        if (buttonComponent->GetType() == ButtonType::CIRCLE) {
            return;
        }
        const Dimension initialHeight = Dimension(-1.0, DimensionUnit::VP);
        buttonComponent->SetHeight(initialHeight);
    }
}

void ButtonModelImpl::SetTypeAndStateEffect(const std::optional<ButtonType>& type,
    const std::optional<bool>& stateEffect, const RefPtr<ButtonComponent>& buttonComponent)
{
    if (type.has_value()) {
        buttonComponent->SetType(type.value());
    } else {
        // undefined use capsule type.
        buttonComponent->SetType(ButtonType::CAPSULE);
    }

    if (stateEffect.has_value()) {
        buttonComponent->SetStateEffect(stateEffect.value());
    }
}

void ButtonModelImpl::SetDefaultAttributes(const RefPtr<ButtonComponent>& buttonComponent)
{
    buttonComponent->SetType(ButtonType::CAPSULE);
    buttonComponent->SetDeclarativeFlag(true);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    buttonComponent->SetHeight(buttonTheme->GetHeight());
    buttonComponent->SetBackgroundColor(buttonTheme->GetBgColor());
    buttonComponent->SetClickedColor(buttonComponent->GetBackgroundColor().BlendColor(buttonTheme->GetClickedColor()));
    buttonComponent->SetHoverColor(buttonTheme->GetHoverColor());
}

void ButtonModelImpl::SetRemoteMessage(RemoteCallback&& remoteCallback)
{
    EventMarker remoteMessageEventId(std::move(remoteCallback));
    auto stack = ViewStackProcessor::GetInstance();
    auto buttonComponent = AceType::DynamicCast<ButtonComponent>(stack->GetMainComponent());
    if (buttonComponent) {
        buttonComponent->SetRemoteMessageEventId(remoteMessageEventId);
    }
}
} // namespace OHOS::Ace::Framework
