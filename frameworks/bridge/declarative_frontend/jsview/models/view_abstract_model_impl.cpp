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
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components/common/properties/decoration.h"
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

RefPtr<Decoration> GetFrontDecoration()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto decoration = box->GetFrontDecoration();
    if (!decoration) {
        decoration = AceType::MakeRefPtr<Decoration>();
        box->SetFrontDecoration(decoration);
    }

    return decoration;
}

AnimatableDimension ToAnimatableDimension(const Dimension& dimension)
{
    AnimatableDimension result(dimension);
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    result.SetAnimationOption(option);
    return result;
}

Gradient ToGradient(const NG::Gradient& gradient)
{
    Gradient retGradient;
    retGradient.SetType(static_cast<GradientType>(gradient.GetType()));
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    if (retGradient.GetType() == GradientType::LINEAR) {
        auto angle = gradient.GetLinearGradient()->angle;
        if (angle.has_value()) {
            retGradient.GetLinearGradient().angle = ToAnimatableDimension(angle.value());
        }
        auto linearX = gradient.GetLinearGradient()->linearX;
        if (linearX.has_value()) {
            retGradient.GetLinearGradient().linearX = static_cast<GradientDirection>(linearX.value());
        }
        auto linearY = gradient.GetLinearGradient()->linearY;
        if (linearY.has_value()) {
            retGradient.GetLinearGradient().linearY = static_cast<GradientDirection>(linearY.value());
        }
    }

    if (retGradient.GetType() == GradientType::RADIAL) {
        auto radialCenterX = gradient.GetRadialGradient()->radialCenterX;
        if (radialCenterX.has_value()) {
            retGradient.GetRadialGradient().radialCenterX = ToAnimatableDimension(radialCenterX.value());
        }
        auto radialCenterY = gradient.GetRadialGradient()->radialCenterY;
        if (radialCenterY.has_value()) {
            retGradient.GetRadialGradient().radialCenterY = ToAnimatableDimension(radialCenterY.value());
        }
        auto radialVerticalSize = gradient.GetRadialGradient()->radialVerticalSize;
        if (radialVerticalSize.has_value()) {
            retGradient.GetRadialGradient().radialVerticalSize = ToAnimatableDimension(radialVerticalSize.value());
        }
        auto radialHorizontalSize = gradient.GetRadialGradient()->radialHorizontalSize;
        if (radialVerticalSize.has_value()) {
            retGradient.GetRadialGradient().radialHorizontalSize = ToAnimatableDimension(radialHorizontalSize.value());
        }
    }

    if (retGradient.GetType() == GradientType::SWEEP) {
        auto centerX = gradient.GetSweepGradient()->centerX;
        if (centerX.has_value()) {
            retGradient.GetSweepGradient().centerX = ToAnimatableDimension(centerX.value());
        }
        auto centerY = gradient.GetSweepGradient()->centerY;
        if (centerY.has_value()) {
            retGradient.GetSweepGradient().centerY = ToAnimatableDimension(centerY.value());
        }
        auto startAngle = gradient.GetSweepGradient()->startAngle;
        if (startAngle.has_value()) {
            retGradient.GetSweepGradient().startAngle = ToAnimatableDimension(startAngle.value());
        }
        auto endAngle = gradient.GetSweepGradient()->endAngle;
        if (endAngle.has_value()) {
            retGradient.GetSweepGradient().endAngle = ToAnimatableDimension(endAngle.value());
        }
        auto rotation = gradient.GetSweepGradient()->rotation;
        if (rotation.has_value()) {
            retGradient.GetSweepGradient().rotation = ToAnimatableDimension(rotation.value());
        }
    }

    retGradient.SetRepeat(gradient.GetRepeat());
    const auto& colorStops = gradient.GetColors();

    for (const auto& item : colorStops) {
        GradientColor gradientColor;
        gradientColor.SetColor(item.GetColor());
        gradientColor.SetHasValue(item.GetHasValue());
        gradientColor.SetDimension(item.GetDimension());
        retGradient.AddColor(gradientColor);
    }
    return retGradient;
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

void ViewAbstractModelImpl::SetLayoutDirection(TextDirection value)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetTextDirection(value);
    box->SetInspectorDirection(value);
    if (value == TextDirection::AUTO) {
        box->SetTextDirection(
            AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR);
    }
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

void ViewAbstractModelImpl::SetAlignRules(const std::map<AlignDirection, AlignRule>& alignRules)
{
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetAlignRules(alignRules);
}

void ViewAbstractModelImpl::SetUseAlign(
    AlignDeclarationPtr declaration, AlignDeclaration::Edge edge, const std::optional<Dimension>& offset)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetAlignDeclarationPtr(declaration);
    box->SetUseAlignSide(edge);
    if (offset.has_value()) {
        box->SetUseAlignOffset(offset.value());
    }
}

void ViewAbstractModelImpl::SetGrid(std::optional<uint32_t> span, std::optional<int32_t> offset,
    const RefPtr<GridContainerInfo>& info, GridSizeType type)
{
    if (info != nullptr) {
        auto builder = ViewStackProcessor::GetInstance()->GetBoxComponent()->GetGridColumnInfoBuilder();
        builder->SetParent(info);
        if (span.has_value()) {
            if (type == GridSizeType::UNDEFINED) {
                builder->SetColumns(span.value());
            } else {
                builder->SetSizeColumn(type, span.value());
            }
        }
        if (offset.has_value()) {
            if (type == GridSizeType::UNDEFINED) {
                builder->SetOffset(offset.value());
            } else {
                builder->SetOffset(offset.value(), type);
            }
        }
    }
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

void ViewAbstractModelImpl::SetOpacity(double opacity, bool passThrough)
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
    if (passThrough && ViewStackProcessor::GetInstance()->HasDisplayComponent()) {
        auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
        display->DisableLayer(true);
    }
}

void ViewAbstractModelImpl::SetTransition(const NG::TransitionOptions& transitionOptions, bool passThrough)
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
    if (passThrough && ViewStackProcessor::GetInstance()->HasDisplayComponent()) {
        auto display = ViewStackProcessor::GetInstance()->GetDisplayComponent();
        display->DisableLayer(true);
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

void ViewAbstractModelImpl::SetMotionPath(const MotionPathOption& option)
{
    if (option.GetRotate()) {
        ViewStackProcessor::GetInstance()->GetTransformComponent();
    }
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetMotionPathOption(option);
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

void ViewAbstractModelImpl::SetZIndex(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto renderComponent = AceType::DynamicCast<RenderComponent>(component);
    if (renderComponent) {
        renderComponent->SetZIndex(value);
    }
}

void ViewAbstractModelImpl::SetLinearGradient(const NG::Gradient& gradient)
{
    auto lineGradient = ToGradient(gradient);
    auto* stack = ViewStackProcessor::GetInstance();
    if (!stack->IsVisualStateSet()) {
        auto decoration = GetBackDecoration();
        if (decoration) {
            decoration->SetGradient(lineGradient);
        }
    } else {
        auto boxComponent = stack->GetBoxComponent();
        boxComponent->GetStateAttributes()->AddAttribute<Gradient>(
            BoxStateAttribute::GRADIENT, lineGradient, stack->GetVisualState());
        if (!boxComponent->GetStateAttributes()->HasAttribute(BoxStateAttribute::GRADIENT, VisualState::NORMAL)) {
            boxComponent->GetStateAttributes()->AddAttribute<Gradient>(
                BoxStateAttribute::GRADIENT, GetBackDecoration()->GetGradient(), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetSweepGradient(const NG::Gradient& gradient)
{
    auto sweepGradient = ToGradient(gradient);
    auto* stack = ViewStackProcessor::GetInstance();
    if (!stack->IsVisualStateSet()) {
        auto decoration = GetBackDecoration();
        if (decoration) {
            decoration->SetGradient(sweepGradient);
        }
    } else {
        auto boxComponent = stack->GetBoxComponent();
        boxComponent->GetStateAttributes()->AddAttribute<Gradient>(
            BoxStateAttribute::GRADIENT, sweepGradient, stack->GetVisualState());
        if (!boxComponent->GetStateAttributes()->HasAttribute(BoxStateAttribute::GRADIENT, VisualState::NORMAL)) {
            boxComponent->GetStateAttributes()->AddAttribute<Gradient>(
                BoxStateAttribute::GRADIENT, GetBackDecoration()->GetGradient(), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetRadialGradient(const NG::Gradient& gradient)
{
    auto radialGradient = ToGradient(gradient);
    auto* stack = ViewStackProcessor::GetInstance();
    if (!stack->IsVisualStateSet()) {
        auto decoration = GetBackDecoration();
        if (decoration) {
            decoration->SetGradient(radialGradient);
        }
    } else {
        auto boxComponent = stack->GetBoxComponent();
        boxComponent->GetStateAttributes()->AddAttribute<Gradient>(
            BoxStateAttribute::GRADIENT, radialGradient, stack->GetVisualState());
        if (!boxComponent->GetStateAttributes()->HasAttribute(BoxStateAttribute::GRADIENT, VisualState::NORMAL)) {
            boxComponent->GetStateAttributes()->AddAttribute<Gradient>(
                BoxStateAttribute::GRADIENT, GetBackDecoration()->GetGradient(), VisualState::NORMAL);
        }
    }
}

void ViewAbstractModelImpl::SetClipPath(const RefPtr<BasicShape>& shape)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto clipPath = AceType::MakeRefPtr<ClipPath>();
    clipPath->SetBasicShape(shape);
    box->SetClipPath(clipPath);
}

void ViewAbstractModelImpl::SetEdgeClip(bool isClip)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetBoxClipFlag(isClip);
}

void ViewAbstractModelImpl::SetMask(const RefPtr<BasicShape>& shape)
{
    auto maskPath = AceType::MakeRefPtr<MaskPath>();
    maskPath->SetBasicShape(shape);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetMask(maskPath);
}

void ViewAbstractModelImpl::SetBackdropBlur(const Dimension& radius)
{
    auto decoration = GetBackDecoration();
    decoration->SetBlurRadius(ToAnimatableDimension(radius));
}

void ViewAbstractModelImpl::SetFrontBlur(const Dimension& radius)
{
    auto decoration = GetFrontDecoration();
    decoration->SetBlurRadius(ToAnimatableDimension(radius));
}

void ViewAbstractModelImpl::SetBackShadow(const std::vector<Shadow>& shadows)
{
    auto backDecoration = GetBackDecoration();
    backDecoration->SetShadows(shadows);
}

void ViewAbstractModelImpl::SetColorBlend(const Color& value)
{
    auto decoration = GetFrontDecoration();
    decoration->SetColorBlend(value);
}

void ViewAbstractModelImpl::SetWindowBlur(float progress, WindowBlurStyle blurStyle)
{
    auto decoration = GetBackDecoration();
    decoration->SetWindowBlurProgress(progress);
    decoration->SetWindowBlurStyle(blurStyle);
}

void ViewAbstractModelImpl::SetBrightness(const Dimension& value)
{
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetBrightness(value);
}

void ViewAbstractModelImpl::SetGrayScale(const Dimension& value)
{
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetGrayScale(value);
}

void ViewAbstractModelImpl::SetContrast(const Dimension& value)
{
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetContrast(value);
}

void ViewAbstractModelImpl::SetSaturate(const Dimension& value)
{
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetSaturate(value);
}

void ViewAbstractModelImpl::SetSepia(const Dimension& value)
{
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetSepia(value);
}

void ViewAbstractModelImpl::SetInvert(const Dimension& value)
{
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetInvert(value);
}

void ViewAbstractModelImpl::SetHueRotate(float value)
{
    auto frontDecoration = GetFrontDecoration();
    frontDecoration->SetHueRotate(value);
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

void ViewAbstractModelImpl::SetOnFocusMove(std::function<void(int32_t)>&& onFocusMoveCallback)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusableComponent) {
        focusableComponent->SetOnFocusMove(onFocusMoveCallback);
    }
}

void ViewAbstractModelImpl::SetOnFocus(OnFocusFunc&& onFocusCallback)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(true);
    if (focusableComponent) {
        focusableComponent->SetOnFocus(onFocusCallback);
    }
}

void ViewAbstractModelImpl::SetOnBlur(OnBlurFunc&& onBlurCallback)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(true);
    if (focusableComponent) {
        focusableComponent->SetOnBlur(onBlurCallback);
    }
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

void ViewAbstractModelImpl::SetTabIndex(int32_t index)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(true);
    if (focusableComponent) {
        focusableComponent->SetFocusable(true);
        focusableComponent->SetTabIndex(index);
    }
}

void ViewAbstractModelImpl::SetFocusOnTouch(bool isSet)
{
    auto touchComponent = ViewStackProcessor::GetInstance()->GetTouchListenerComponent();
    if (!touchComponent) {
        LOGE("Touch listener component get failed!");
        return;
    }
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(true);
    if (!focusableComponent) {
        LOGE("focusable component get failed!");
        return;
    }
    focusableComponent->SetIsFocusOnTouch(isSet);
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    if (!component) {
        LOGE("main component get failed!");
        return;
    }
    component->SetIsFocusOnTouch(isSet);
}

void ViewAbstractModelImpl::SetDefaultFocus(bool isSet)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(true);
    if (!focusableComponent) {
        LOGE("focusable component get failed!");
        return;
    }
    focusableComponent->SetIsDefaultFocus(isSet);
}

void ViewAbstractModelImpl::SetGroupDefaultFocus(bool isSet)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(true);
    if (!focusableComponent) {
        LOGE("focusable component get failed!");
        return;
    }
    focusableComponent->SetIsDefaultGroupFocus(isSet);
}

void ViewAbstractModelImpl::SetInspectorId(const std::string& inspectorId)
{
    auto component = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    if (component) {
        component->SetInspectorKey(inspectorId);
    }

    if (!AceType::InstanceOf<TextSpanComponent>(ViewStackProcessor::GetInstance()->GetMainComponent())) {
        auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
        if (flexItem) {
            flexItem->SetInspectorKey(inspectorId);
        }
    }

    if (!AceType::InstanceOf<TextSpanComponent>(ViewStackProcessor::GetInstance()->GetMainComponent())) {
        auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
        if (focusableComponent) {
            focusableComponent->SetInspectorKey(inspectorId);
        }
    }
}

void ViewAbstractModelImpl::SetRestoreId(int32_t restoreId)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    if (component) {
        component->SetRestoreId(restoreId);
    }
}

void ViewAbstractModelImpl::SetDebugLine(const std::string& line)
{
#if defined(PREVIEW)
    auto component = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    if (component) {
        component->SetDebugLine(line);
    }
#endif
}

void ViewAbstractModelImpl::SetHoverEffect(HoverEffectType hoverEffect)
{
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    if (!boxComponent) {
        LOGE("boxComponent is null");
        return;
    }
    boxComponent->SetMouseAnimationType(static_cast<HoverAnimationType>(hoverEffect));
}

void ViewAbstractModelImpl::SetHitTestMode(NG::HitTestMode hitTestMode)
{
    auto mode = static_cast<HitTestMode>(hitTestMode);
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    if (component) {
        component->SetHitTestMode(mode);
    }
}

void ViewAbstractModelImpl::SetAccessibilityGroup(bool accessible)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    if (!inspector) {
        LOGE("this component does not have inspector");
        return;
    }
    inspector->SetAccessibilityGroup(accessible);
}

void ViewAbstractModelImpl::SetAccessibilityText(const std::string& text)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    if (!inspector) {
        LOGE("this component does not have inspector");
        return;
    }
    inspector->SetAccessibilitytext(text);
}

void ViewAbstractModelImpl::SetAccessibilityDescription(const std::string& description)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    if (!inspector) {
        LOGE("this component does not have inspector");
        return;
    }
    inspector->SetAccessibilityDescription(description);
}

void ViewAbstractModelImpl::SetAccessibilityImportance(const std::string& importance)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    if (!inspector) {
        LOGE("this component does not have inspector");
        return;
    }
    inspector->SetAccessibilityImportance(importance);
}

} // namespace OHOS::Ace::Framework
