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

#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"

#include "base/geometry/animatable_dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/box/box_component_helper.h"
#include "core/event/ace_event_handler.h"

namespace OHOS::Ace::Framework {

RefPtr<Decoration> GetBackDecoration()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto decoration = box->GetBackDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
        box->SetBackDecoration(decoration);
    }
    return decoration;
}

void ViewAbstractModelImpl::SetWidth(const Dimension& width)
{
    bool isPercentSize = (width.Unit() == DimensionUnit::PERCENT);
    if (isPercentSize) {
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto renderComponent = AceType::DynamicCast<RenderComponent>(component);
        if (renderComponent) {
            renderComponent->SetIsPercentSize(isPercentSize);
        }
    }

    auto* stack = ViewStackProcessor::GetInstance();
    auto box = stack->GetBoxComponent();
    auto option = stack->GetImplicitAnimationOption();
    if (!stack->IsVisualStateSet()) {
        box->SetWidth(width, option);
    } else {
        box->GetStateAttributes()->AddAttribute<AnimatableDimension>(
            BoxStateAttribute::WIDTH, AnimatableDimension(width, option), stack->GetVisualState());
        if (!box->GetStateAttributes()->HasAttribute(BoxStateAttribute::WIDTH, VisualState::NORMAL)) {
            box->GetStateAttributes()->AddAttribute<AnimatableDimension>(
                BoxStateAttribute::WIDTH, AnimatableDimension(box->GetWidth(), option), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetHeight(const Dimension& height)
{
    bool isPercentSize = (height.Unit() == DimensionUnit::PERCENT);
    if (isPercentSize) {
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto renderComponent = AceType::DynamicCast<RenderComponent>(component);
        if (renderComponent) {
            renderComponent->SetIsPercentSize(isPercentSize);
        }
    }

    auto* stack = ViewStackProcessor::GetInstance();
    auto box = stack->GetBoxComponent();
    auto option = stack->GetImplicitAnimationOption();
    if (!stack->IsVisualStateSet()) {
        box->SetHeight(height, option);
    } else {
        box->GetStateAttributes()->AddAttribute<AnimatableDimension>(
            BoxStateAttribute::HEIGHT, AnimatableDimension(height, option), stack->GetVisualState());
        if (!box->GetStateAttributes()->HasAttribute(BoxStateAttribute::HEIGHT, VisualState::NORMAL)) {
            box->GetStateAttributes()->AddAttribute<AnimatableDimension>(
                BoxStateAttribute::HEIGHT, AnimatableDimension(box->GetHeight(), option), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetMinWidth(const Dimension& minWidth)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    box->SetMinWidth(minWidth);
    flexItem->SetMinWidth(minWidth);
}

void ViewAbstractModelImpl::SetMinHeight(const Dimension& minHeight)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    box->SetMinHeight(minHeight);
    flexItem->SetMinHeight(minHeight);
}

void ViewAbstractModelImpl::SetMaxWidth(const Dimension& maxWidth)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    box->SetMaxWidth(maxWidth);
    flexItem->SetMaxWidth(maxWidth);
}

void ViewAbstractModelImpl::SetMaxHeight(const Dimension& maxHeight)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    box->SetMaxHeight(maxHeight);
    flexItem->SetMaxHeight(maxHeight);
}

void ViewAbstractModelImpl::SetBackgroundColor(const Color& color)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto boxComponent = stack->GetBoxComponent();
    auto option = stack->GetImplicitAnimationOption();
    if (!stack->IsVisualStateSet()) {
        boxComponent->SetColor(color, option);
    } else {
        boxComponent->GetStateAttributes()->AddAttribute<AnimatableColor>(
            BoxStateAttribute::COLOR, AnimatableColor(color, option), stack->GetVisualState());
        if (!boxComponent->GetStateAttributes()->HasAttribute(BoxStateAttribute::COLOR, VisualState::NORMAL)) {
            boxComponent->GetStateAttributes()->AddAttribute<AnimatableColor>(
                BoxStateAttribute::COLOR, AnimatableColor(boxComponent->GetColor(), option), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetBackgroundImage(const std::string& src, RefPtr<ThemeConstants> themeConstant)
{
    auto decoration = GetBackDecoration();
    CHECK_NULL_VOID(decoration);
    auto image = decoration->GetImage();
    if (!image) {
        image = AceType::MakeRefPtr<BackgroundImage>();
    }

    if (themeConstant) {
        image->SetSrc(src, themeConstant);
    } else {
        image->SetParsedSrc(src);
    }

    decoration->SetImage(image);
}

void ViewAbstractModelImpl::SetBackgroundImageRepeat(const ImageRepeat& imageRepeat)
{
    auto decoration = GetBackDecoration();
    CHECK_NULL_VOID(decoration);
    auto image = decoration->GetImage();
    if (!image) {
        image = AceType::MakeRefPtr<BackgroundImage>();
    }
    image->SetImageRepeat(imageRepeat);
    decoration->SetImage(image);
}

void ViewAbstractModelImpl::SetBackgroundImageSize(const BackgroundImageSize& bgImgSize)
{
    auto decoration = GetBackDecoration();
    CHECK_NULL_VOID(decoration);
    auto image = decoration->GetImage();
    if (!image) {
        image = AceType::MakeRefPtr<BackgroundImage>();
    }
    image->SetImageSize(bgImgSize);
    decoration->SetImage(image);
}

void ViewAbstractModelImpl::SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition)
{
    auto decoration = GetBackDecoration();
    CHECK_NULL_VOID(decoration);
    auto image = decoration->GetImage();
    if (!image) {
        image = AceType::MakeRefPtr<BackgroundImage>();
    }
    image->SetImagePosition(bgImgPosition);
    decoration->SetImage(image);
}

void ViewAbstractModelImpl::SetBackgroundBlurStyle(const BlurStyle& bgBlurStyle)
{
    auto decoration = GetBackDecoration();
    CHECK_NULL_VOID(decoration);
    decoration->SetBlurStyle(bgBlurStyle);
}

void ViewAbstractModelImpl::SetPadding(const Dimension& value)
{
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    AnimatableDimension animValue(value);
    animValue.SetAnimationOption(option);
    SetPaddings(animValue, animValue, animValue, animValue);
}

void ViewAbstractModelImpl::SetPaddings(
    const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    Edge padding(left, top, right, bottom, option);
    box->SetPadding(padding);
}

void ViewAbstractModelImpl::SetMargin(const Dimension& value)
{
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    AnimatableDimension animValue(value);
    animValue.SetAnimationOption(option);
    SetMargins(animValue, animValue, animValue, animValue);
}

void ViewAbstractModelImpl::SetMargins(
    const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    Edge margin(left, top, right, bottom, option);
    box->SetMargin(margin);
}

void ViewAbstractModelImpl::SetBorderRadius(const Dimension& value)
{
    SetBorderRadius(value, value, value, value);
}

void ViewAbstractModelImpl::SetBorderRadius(const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight)
{
    auto decoration = GetBackDecoration();
    CHECK_NULL_VOID(decoration);
    Dimension topLeft = radiusTopLeft.has_value() ? radiusTopLeft.value()
                                                  : BoxComponentHelper::GetBorderRadiusTopLeft(decoration).GetX();
    Dimension topRight = radiusTopRight.has_value() ? radiusTopRight.value()
                                                    : BoxComponentHelper::GetBorderRadiusTopRight(decoration).GetX();
    Dimension bottomLeft = radiusBottomLeft.has_value()
                               ? radiusBottomLeft.value()
                               : BoxComponentHelper::GetBorderRadiusBottomLeft(decoration).GetX();
    Dimension bottomRight = radiusBottomRight.has_value()
                                ? radiusBottomRight.value()
                                : BoxComponentHelper::GetBorderRadiusBottomRight(decoration).GetX();
    auto* stack = ViewStackProcessor::GetInstance();
    AnimationOption option = stack->GetImplicitAnimationOption();
    if (!stack->IsVisualStateSet()) {
        BoxComponentHelper::SetBorderRadius(decoration, topLeft, topRight, bottomLeft, bottomRight, option);
    } else {
        auto boxComponent = stack->GetBoxComponent();
        boxComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(
            BoxStateAttribute::BORDER_RADIUS, AnimatableDimension(topLeft, option), stack->GetVisualState());
        if (!boxComponent->GetStateAttributes()->HasAttribute(BoxStateAttribute::BORDER_RADIUS, VisualState::NORMAL)) {
            boxComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(
                BoxStateAttribute::BORDER_RADIUS, AnimatableDimension(topLeft, option), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetBorderColor(const Color& value)
{
    SetBorderColor(value, value, value, value);
}

void ViewAbstractModelImpl::SetBorderColor(const std::optional<Color>& colorLeft,
    const std::optional<Color>& colorRight, const std::optional<Color>& colorTop,
    const std::optional<Color>& colorBottom)
{
    auto decoration = GetBackDecoration();
    CHECK_NULL_VOID(decoration);
    Color leftColor = colorLeft.has_value() ? colorLeft.value() : BoxComponentHelper::GetBorderColorTop(decoration);
    Color rightColor =
        colorRight.has_value() ? colorRight.value() : BoxComponentHelper::GetBorderColorBottom(decoration);
    Color topColor = colorTop.has_value() ? colorTop.value() : BoxComponentHelper::GetBorderColorLeft(decoration);
    Color bottomColor =
        colorBottom.has_value() ? colorBottom.value() : BoxComponentHelper::GetBorderColorRight(decoration);
    auto* stack = ViewStackProcessor::GetInstance();
    AnimationOption option = stack->GetImplicitAnimationOption();
    if (!stack->IsVisualStateSet()) {
        BoxComponentHelper::SetBorderColor(decoration, leftColor, rightColor, topColor, bottomColor, option);
    } else {
        auto boxComponent = stack->GetBoxComponent();
        boxComponent->GetStateAttributes()->AddAttribute<AnimatableColor>(
            BoxStateAttribute::BORDER_COLOR, AnimatableColor(leftColor, option), stack->GetVisualState());
        if (!boxComponent->GetStateAttributes()->HasAttribute(BoxStateAttribute::BORDER_COLOR, VisualState::NORMAL)) {
            boxComponent->GetStateAttributes()->AddAttribute<AnimatableColor>(BoxStateAttribute::BORDER_COLOR,
                AnimatableColor(BoxComponentHelper::GetBorderColor(decoration), option), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetBorderWidth(const Dimension& value)
{
    SetBorderWidth(value, value, value, value);
}

void ViewAbstractModelImpl::SetBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
    const std::optional<Dimension>& top, const std::optional<Dimension>& bottom)
{
    auto decoration = GetBackDecoration();
    CHECK_NULL_VOID(decoration);
    Dimension leftDimen = left.has_value() ? left.value() : BoxComponentHelper::GetBorderLeftWidth(decoration);
    Dimension rightDimen = right.has_value() ? right.value() : BoxComponentHelper::GetBorderRightWidth(decoration);
    Dimension topDimen = top.has_value() ? top.value() : BoxComponentHelper::GetBorderTopWidth(decoration);
    Dimension bottomDimen = bottom.has_value() ? bottom.value() : BoxComponentHelper::GetBorderBottomWidth(decoration);
    auto* stack = ViewStackProcessor::GetInstance();
    AnimationOption option = stack->GetImplicitAnimationOption();
    if (!stack->IsVisualStateSet()) {
        BoxComponentHelper::SetBorderWidth(decoration, leftDimen, rightDimen, topDimen, bottomDimen, option);
    } else {
        auto boxComponent = stack->GetBoxComponent();
        boxComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(
            BoxStateAttribute::BORDER_WIDTH, AnimatableDimension(leftDimen, option), stack->GetVisualState());
        if (!boxComponent->GetStateAttributes()->HasAttribute(BoxStateAttribute::BORDER_WIDTH, VisualState::NORMAL)) {
            boxComponent->GetStateAttributes()->AddAttribute<AnimatableDimension>(BoxStateAttribute::BORDER_WIDTH,
                AnimatableDimension(BoxComponentHelper::GetBorderWidth(decoration), option), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetBorderStyle(const BorderStyle& value)
{
    SetBorderStyle(value, value, value, value);
}

void ViewAbstractModelImpl::SetBorderStyle(const std::optional<BorderStyle>& styleLeft,
    const std::optional<BorderStyle>& styleRight, const std::optional<BorderStyle>& styleTop,
    const std::optional<BorderStyle>& styleBottom)
{
    auto decoration = GetBackDecoration();
    CHECK_NULL_VOID(decoration);
    BorderStyle left = styleLeft ? styleLeft.value() : BoxComponentHelper::GetBorderStyleLeft(decoration);
    BorderStyle right = styleRight ? styleRight.value() : BoxComponentHelper::GetBorderStyleRight(decoration);
    BorderStyle top = styleTop ? styleTop.value() : BoxComponentHelper::GetBorderStyleTop(decoration);
    BorderStyle bottom = styleBottom ? styleBottom.value() : BoxComponentHelper::GetBorderStyleBottom(decoration);
    auto* stack = ViewStackProcessor::GetInstance();
    AnimationOption option = stack->GetImplicitAnimationOption();
    if (!stack->IsVisualStateSet()) {
        BoxComponentHelper::SetBorderStyle(decoration, left, right, top, bottom);
    } else {
        auto boxComponent = stack->GetBoxComponent();
        boxComponent->GetStateAttributes()->AddAttribute<BorderStyle>(
            BoxStateAttribute::BORDER_STYLE, left, stack->GetVisualState());
        if (!boxComponent->GetStateAttributes()->HasAttribute(BoxStateAttribute::BORDER_STYLE, VisualState::NORMAL)) {
            boxComponent->GetStateAttributes()->AddAttribute<BorderStyle>(
                BoxStateAttribute::BORDER_STYLE, BoxComponentHelper::GetBorderStyle(decoration), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetLayoutPriority(int32_t priority)
{
    auto flex = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flex->SetDisplayIndex(priority);
}

void ViewAbstractModelImpl::SetLayoutWeight(int32_t value)
{
    auto flex = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flex->SetFlexWeight(value);
}

void ViewAbstractModelImpl::SetAspectRatio(float ratio)
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    boxComponent->SetAspectRatio(ratio, option);
}

void ViewAbstractModelImpl::SetAlign(const Alignment& alignment)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetAlignment(alignment);
}

AnimatableDimension ToAnimatableDimension(const Dimension& dimension)
{
    AnimatableDimension result(dimension);
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    result.SetAnimationOption(option);
    return result;
}

void ViewAbstractModelImpl::SetPosition(const Dimension& x, const Dimension& y)
{
    auto flexItemComponent = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItemComponent->SetLeft(ToAnimatableDimension(x));
    flexItemComponent->SetTop(ToAnimatableDimension(y));
    flexItemComponent->SetPositionType(PositionType::PTABSOLUTE);
}

void ViewAbstractModelImpl::SetOffset(const Dimension& x, const Dimension& y)
{
    auto flexItemComponent = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItemComponent->SetLeft(ToAnimatableDimension(x));
    flexItemComponent->SetTop(ToAnimatableDimension(y));
    flexItemComponent->SetPositionType(PositionType::PTOFFSET);
}

void ViewAbstractModelImpl::MarkAnchor(const Dimension& x, const Dimension& y)
{
    auto flexItemComponent = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItemComponent->SetAnchorX(ToAnimatableDimension(x));
    flexItemComponent->SetAnchorY(ToAnimatableDimension(y));
}

void ViewAbstractModelImpl::SetScale(float x, float y, float z)
{
    RefPtr<TransformComponent> transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->Scale(x, y, z, option);
}

void ViewAbstractModelImpl::SetPivot(const Dimension& x, const Dimension& y)
{
    RefPtr<TransformComponent> transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    transform->SetOriginDimension(DimensionOffset(x, y));
}

void ViewAbstractModelImpl::SetTranslate(const Dimension& x, const Dimension& y, const Dimension& z)
{
    RefPtr<TransformComponent> transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->Translate(x, y, z, option);
}

void ViewAbstractModelImpl::SetRotate(float x, float y, float z, float angle)
{
    RefPtr<TransformComponent> transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->Rotate(x, y, z, angle, option);
}

void ViewAbstractModelImpl::SetTransformMatrix(const std::vector<float>& matrix)
{
    RefPtr<TransformComponent> transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    transform->Matrix3d(matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5], matrix[6], matrix[7],
        matrix[8], matrix[9], matrix[10], matrix[11], matrix[12], matrix[13], matrix[14], matrix[15], option);
}

void ViewAbstractModelImpl::SetOpacity(double opacity)
{
    auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    auto stack = ViewStackProcessor::GetInstance();
    auto option = stack->GetImplicitAnimationOption();
    if (!stack->IsVisualStateSet()) {
        display->SetOpacity(opacity, option);
    } else {
        display->GetStateAttributes()->AddAttribute<AnimatableDouble>(
            DisplayStateAttribute::OPACITY, AnimatableDouble(opacity, option), stack->GetVisualState());
        if (!display->GetStateAttributes()->HasAttribute(DisplayStateAttribute::OPACITY, VisualState::NORMAL)) {
            display->GetStateAttributes()->AddAttribute<AnimatableDouble>(
                DisplayStateAttribute::OPACITY, AnimatableDouble(display->GetOpacity(), option), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetTransition(const NG::TransitionOptions& transitionOptions)
{
    if (transitionOptions.HasOpacity()) {
        auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
        display->SetTransition(transitionOptions.Type, transitionOptions.GetOpacityValue());
    }
    if (transitionOptions.HasTranslate()) {
        auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
        const auto& value = transitionOptions.GetTranslateValue();
        transform->SetTranslateTransition(transitionOptions.Type, value.x, value.y, value.z);
    }
    if (transitionOptions.HasScale()) {
        auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
        const auto& value = transitionOptions.GetScaleValue();
        transform->SetScaleTransition(transitionOptions.Type, value.xScale, value.yScale, value.zScale);
        transform->SetOriginDimension(DimensionOffset(value.centerX, value.centerY));
    }
    if (transitionOptions.HasRotate()) {
        auto transform = ViewStackProcessor::GetInstance()->GetTransformComponent();
        const auto& value = transitionOptions.GetRotateValue();
        transform->SetRotateTransition(
            transitionOptions.Type, value.xDirection, value.yDirection, value.zDirection, value.angle);
        transform->SetOriginDimension(DimensionOffset(value.centerX, value.centerY));
    }
}

void ViewAbstractModelImpl::SetOverlay(const std::string& text, const std::optional<Alignment>& align,
    const std::optional<Dimension>& offsetX, const std::optional<Dimension>& offsetY)
{
    auto coverageComponent = ViewStackProcessor::GetInstance()->GetCoverageComponent();
    coverageComponent->SetTextVal(text);
    coverageComponent->SetIsOverLay(true);
    if (align.has_value()) {
        coverageComponent->SetAlignment(align.value());
    }
    if (offsetX.has_value()) {
        coverageComponent->SetX(offsetX.value());
    }
    if (offsetY.has_value()) {
        coverageComponent->SetX(offsetY.value());
    }
}

void ViewAbstractModelImpl::SetVisibility(VisibleType visible, std::function<void(int32_t)>&& changeEventFunc)
{
    auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    display->SetVisible(visible);
    auto eventMarker = EventMarker([func = std::move(changeEventFunc)](const BaseEventInfo* info) {
        const auto& param = info->GetType();
        int32_t newValue = StringToInt(param);
        func(newValue);
    });

    display->SetVisibleChangeEvent(eventMarker);
}

void ViewAbstractModelImpl::SetSharedTransition(const SharedTransitionOption& option)
{
    auto sharedTransitionComponent = ViewStackProcessor::GetInstance()->GetSharedTransitionComponent();
    sharedTransitionComponent->SetShareId(option.id);
    TweenOption tweenOption;
    tweenOption.SetCurve(option.curve);
    tweenOption.SetDuration(option.duration);
    tweenOption.SetDelay(option.delay);
    tweenOption.SetMotionPathOption(option.motionPathOption);
    auto sharedTransitionEffect =
        SharedTransitionEffect::GetSharedTransitionEffect(option.type, sharedTransitionComponent->GetShareId());
    sharedTransitionComponent->SetEffect(sharedTransitionEffect);
    sharedTransitionComponent->SetOption(tweenOption);
    if (option.zIndex != 0) {
        sharedTransitionComponent->SetZIndex(option.zIndex);
    }
}

void ViewAbstractModelImpl::SetGeometryTransition(const std::string& id)
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    boxComponent->SetGeometryTransitionId(id);
}

void ViewAbstractModelImpl::SetFlexBasis(const Dimension& value)
{
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetFlexBasis(value);
}

void ViewAbstractModelImpl::SetAlignSelf(FlexAlign value)
{
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetAlignSelf(value);
}

void ViewAbstractModelImpl::SetFlexShrink(float value)
{
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetFlexShrink(value);
}

void ViewAbstractModelImpl::SetFlexGrow(float value)
{
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetFlexGrow(value);
}

void ViewAbstractModelImpl::SetDisplayIndex(int32_t value)
{
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetDisplayIndex(value);
}

void ViewAbstractModelImpl::SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc)
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
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusableComponent) {
        focusableComponent->SetOnClickId(onClickId);
    }
}

void ViewAbstractModelImpl::SetOnTouch(TouchEventFunc&& touchEventFunc)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    CHECK_NULL_VOID(inspector);
    auto impl = inspector->GetInspectorFunctionImpl();
    auto onTouchId = EventMarker(
        [func = std::move(touchEventFunc), impl](BaseEventInfo* info) {
            if (impl) {
                impl->UpdateEventInfo(*info);
            }
            auto* touchInfo = TypeInfoHelper::DynamicCast<TouchEventInfo>(info);
            func(*touchInfo);
        },
        "onTouch");
    auto touchComponent = ViewStackProcessor::GetInstance()->GetTouchListenerComponent();
    touchComponent->SetOnTouchId(onTouchId);
}

void ViewAbstractModelImpl::SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback)
{
    auto onKeyId = EventMarker(
        [func = std::move(onKeyCallback)](BaseEventInfo* info) {
            auto* keyInfo = TypeInfoHelper::DynamicCast<KeyEventInfo>(info);
            func(*keyInfo);
        },
        "onKey", 0);
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(true);
    if (focusableComponent) {
        focusableComponent->SetOnKeyId(onKeyId);
    }
}

void ViewAbstractModelImpl::SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) {}

void ViewAbstractModelImpl::SetOnHover(OnHoverEventFunc&& onHoverEventFunc)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetOnHoverId(onHoverEventFunc);
}

void ViewAbstractModelImpl::SetOnDelete(std::function<void()>&& onDeleteCallback)
{
    auto onDeleteId = EventMarker(std::move(onDeleteCallback));
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusableComponent) {
        focusableComponent->SetOnDeleteId(onDeleteId);
    }
}

void ViewAbstractModelImpl::SetOnAppear(std::function<void()>&& onAppearCallback)
{
    auto onAppearId = EventMarker(std::move(onAppearCallback));
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    CHECK_NULL_VOID(component);
    component->SetOnAppearEventId(onAppearId);
}

void ViewAbstractModelImpl::SetOnDisAppear(std::function<void()>&& onDisAppearCallback)
{
    auto onDisAppearId = EventMarker(std::move(onDisAppearCallback));
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    CHECK_NULL_VOID(component);
    component->SetOnDisappearEventId(onDisAppearId);
}

void ViewAbstractModelImpl::SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    CHECK_NULL_VOID(inspector);
    inspector->SetAccessibilityEvent(EventMarker(std::move(onAccessibilityCallback)));
}

void ViewAbstractModelImpl::SetOnRemoteMessage(RemoteCallback&& onRemoteCallback)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetRemoteMessageEvent(EventMarker(std::move(onRemoteCallback)));
}

void ViewAbstractModelImpl::SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto renderComponent = AceType::DynamicCast<RenderComponent>(component);
    if (renderComponent) {
        renderComponent->SetResponseRegion(responseRegion);
        renderComponent->MarkResponseRegion(true);
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetResponseRegion(responseRegion);
    box->MarkResponseRegion(true);
    if (ViewStackProcessor::GetInstance()->HasClickGestureListenerComponent()) {
        auto click = ViewStackProcessor::GetInstance()->GetClickGestureListenerComponent();
        click->SetResponseRegion(responseRegion);
        click->MarkResponseRegion(true);
    }
    if (ViewStackProcessor::GetInstance()->HasTouchListenerComponent()) {
        auto touch = ViewStackProcessor::GetInstance()->GetTouchListenerComponent();
        touch->SetResponseRegion(responseRegion);
        touch->MarkResponseRegion(true);
    }
}

void ViewAbstractModelImpl::SetEnabled(bool enabled)
{
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    if (mainComponent) {
        mainComponent->SetDisabledStatus(!enabled);
    }

    auto focusComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(!enabled);
    if (focusComponent) {
        focusComponent->SetEnabled(enabled);
    }
}

void ViewAbstractModelImpl::SetTouchable(bool touchable)
{
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    CHECK_NULL_VOID(mainComponent);
    mainComponent->SetTouchable(touchable);
}

void ViewAbstractModelImpl::SetFocusable(bool focusable)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    if (focusableComponent) {
        focusableComponent->SetFocusable(focusable);
    }
}

void ViewAbstractModelImpl::SetFocusNode(bool focus)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusableComponent) {
        focusableComponent->SetFocusNode(!focus);
    }
}

} // namespace OHOS::Ace::Framework
