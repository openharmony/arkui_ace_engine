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

#include "core/components_ng/pattern/slider/slider_content_modifier.h"

#include <optional>

#include "base/geometry/ng/offset_t.h"
#include "core/animation/curves.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5f;
constexpr Dimension CIRCLE_SHADOW_WIDTH = 1.0_vp;
} // namespace
SliderContentModifier::SliderContentModifier()
    : trackThickness_(AceType::MakeRefPtr<AnimatablePropertyFloat>(.0f)),
      trackBackgroundColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT))),
      selectColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT))),
      blockColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT))),
      boardColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT)))
{
    backgroundPenAndSize.start = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
    backgroundPenAndSize.end = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
    selectPenAndSize.start = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
    selectPenAndSize.end = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
    circlePenAndSize.center = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
    circlePenAndSize.radius = AceType::MakeRefPtr<PropertyFloat>(.0f);
    circlePenAndSize.shadowRadius = AceType::MakeRefPtr<PropertyFloat>(.0f);
    AttachProperty(backgroundPenAndSize.start);
    AttachProperty(backgroundPenAndSize.end);
    AttachProperty(selectPenAndSize.start);
    AttachProperty(selectPenAndSize.end);
    AttachProperty(circlePenAndSize.center);
    AttachProperty(circlePenAndSize.radius);
    AttachProperty(circlePenAndSize.shadowRadius);
    AttachProperty(trackThickness_);
    AttachProperty(trackBackgroundColor_);
    AttachProperty(selectColor_);
    AttachProperty(blockColor_);
    AttachProperty(boardColor_);
}

void SliderContentModifier::onDraw(DrawingContext& context)
{
    auto& canvas = context.canvas;
    auto background = backgroundPenAndSize;
    auto select = selectPenAndSize;
    auto circle = circlePenAndSize;
    canvas.AttachPen(background.pen);
    canvas.DrawLine(RSPoint(background.start->Get().GetX(), background.start->Get().GetY()),
        RSPoint(background.end->Get().GetX(), background.end->Get().GetY()));
    canvas.DetachPen();
    if (isShowStep_) {
        canvas.AttachPen(markerPenAndPath.pen);
        canvas.DrawPath(markerPenAndPath.path);
        canvas.DetachPen();
    }
    if (select.start->Get() != select.end->Get()) {
        canvas.AttachPen(select.pen);
        canvas.DrawLine(RSPoint(select.start->Get().GetX(), select.start->Get().GetY()),
            RSPoint(select.end->Get().GetX(), select.end->Get().GetY()));
        canvas.DetachPen();
    }
    canvas.AttachPen(circle.pen);
    canvas.DrawCircle(RSPoint(circle.center->Get().GetX(), circle.center->Get().GetY()), circle.radius->Get());
    canvas.DetachPen();
    canvas.AttachPen(circle.shadowPen);
    canvas.DrawCircle(RSPoint(circle.center->Get().GetX(), circle.center->Get().GetY()), circle.shadowRadius->Get());
    canvas.DetachPen();
}

void SliderContentModifier::UpdateData(const RefPtr<SliderPaintProperty>& paintProperty, const SizeF& contentSize,
    const OffsetF& contentOffset, const RefPtr<SliderTheme>& theme)
{
    directionAxis_ = paintProperty->GetDirectionValue(Axis::HORIZONTAL);
    reverse_ = paintProperty->GetReverseValue(false);
    SetSelectColor(paintProperty->GetSelectColor().value_or(theme->GetTrackSelectedColor()));
    SetTrackBackgroundColor(paintProperty->GetTrackBackgroundColor().value_or(theme->GetTrackBgColor()));
    SetBlockColor(paintProperty->GetBlockColor().value_or(theme->GetBlockColor()));
    centerWidth_ = directionAxis_ == Axis::HORIZONTAL ? contentSize.Height() : contentSize.Width();
    centerWidth_ *= HALF;
    isShowStep_ = false;
}

void SliderContentModifier::GetBackgroundPen(
    const Parameters& parameters, const OffsetF& offset, const RefPtr<SliderTheme>& theme)
{
    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    backgroundPenAndSize.pen.SetAntiAlias(true);
    backgroundPenAndSize.pen.SetWidth(trackThickness_->Get());
    backgroundPenAndSize.pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    backgroundPenAndSize.pen.SetColor(ToRSColor(trackBackgroundColor_->Get()));
    auto start = directionAxis_ == Axis::HORIZONTAL
                     ? PointF(startPointX + parameters.borderBlank, startPointY + centerWidth_)
                     : PointF(startPointX + centerWidth_, startPointY + parameters.borderBlank);
    auto end = directionAxis_ == Axis::HORIZONTAL
                   ? PointF(startPointX + parameters.borderBlank + parameters.sliderLength, startPointY + centerWidth_)
                   : PointF(startPointX + centerWidth_, startPointY + parameters.borderBlank + parameters.sliderLength);
    SetBackgroundSize(start, end);
}

void SliderContentModifier::GetMarkerPen(
    const Parameters& parameters, const OffsetF& offset, const RefPtr<SliderTheme>& theme)
{
    markerPenAndPath.pen.SetAntiAlias(true);
    markerPenAndPath.pen.SetColor(ToRSColor(theme->GetMarkerColor()));
    markerPenAndPath.pen.SetWidth(static_cast<float>(theme->GetMarkerSize().ConvertToPx()));
    markerPenAndPath.pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);

    auto stepsLength = parameters.sliderLength * parameters.stepRatio;
    if (directionAxis_ == Axis::HORIZONTAL) {
        float dyOffset = offset.GetY() + centerWidth_;
        float start = offset.GetX() + parameters.borderBlank;
        float end = start + parameters.sliderLength;
        float current = start;
        while (LessOrEqual(current, end)) {
            float dxOffset = std::clamp(current, start, end);
            markerPenAndPath.path.MoveTo(dxOffset, dyOffset);
            markerPenAndPath.path.LineTo(dxOffset, dyOffset);
            current += stepsLength;
        }
    } else {
        float dxOffset = offset.GetX() + centerWidth_;
        float start = offset.GetY() + parameters.borderBlank;
        float end = start + parameters.sliderLength;
        float current = start;
        while (LessOrEqual(current, end)) {
            float dyOffset = std::clamp(current, start, end);
            markerPenAndPath.path.MoveTo(dxOffset, dyOffset);
            markerPenAndPath.path.LineTo(dxOffset, dyOffset);
            current += stepsLength;
        }
    }
    isShowStep_ = true;
}

void SliderContentModifier::GetSelectPen(
    const Parameters& parameters, const OffsetF& offset, const RefPtr<SliderTheme>& theme)
{
    float sliderSelectLength =
        std::clamp(parameters.sliderLength * parameters.valueRatio, 0.0f, parameters.sliderLength);
    selectPenAndSize.pen.SetAntiAlias(true);
    selectPenAndSize.pen.SetWidth(trackThickness_->Get());
    selectPenAndSize.pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    selectPenAndSize.pen.SetColor(ToRSColor(selectColor_->Get()));
    PointF start;
    PointF end;
    if (!reverse_) {
        start = 
            directionAxis_ == Axis::HORIZONTAL ?
                PointF(offset.GetX() + parameters.borderBlank, offset.GetY() + centerWidth_) :
                PointF(offset.GetX() + centerWidth_, offset.GetY() + parameters.borderBlank);
        end = 
            directionAxis_ == Axis::HORIZONTAL ?
                PointF(offset.GetX() + parameters.borderBlank + sliderSelectLength, offset.GetY() + centerWidth_) :
                PointF(offset.GetX() + centerWidth_, offset.GetY() + parameters.borderBlank + sliderSelectLength);
    } else {
        start =
            directionAxis_ == Axis::HORIZONTAL ?
                PointF(offset.GetX() + parameters.borderBlank + parameters.sliderLength, offset.GetY() + centerWidth_) :
                PointF(offset.GetX() + centerWidth_, offset.GetY() + parameters.borderBlank + parameters.sliderLength);
        end = 
            directionAxis_ == Axis::HORIZONTAL ?
                PointF(offset.GetX() + parameters.borderBlank + parameters.sliderLength - sliderSelectLength,
                    offset.GetY() + centerWidth_) :
                PointF(offset.GetX() + centerWidth_,
                    offset.GetY() + parameters.borderBlank + parameters.sliderLength - sliderSelectLength);
    }
    SetSelectSize(start, end, theme);
}

void SliderContentModifier::GetCirclePen(
    const Parameters& parameters, const OffsetF& offset, const RefPtr<SliderTheme>& theme)
{
    float sliderSelectLength =
        std::clamp(parameters.sliderLength * parameters.valueRatio, 0.0f, parameters.sliderLength);
    circlePenAndSize.pen.SetAntiAlias(true);
    circlePenAndSize.pen.SetColor(ToRSColor(blockColor_->Get()));
    circlePenAndSize.pen.SetWidth(parameters.blockDiameter * HALF);
    PointF center;
    if (!reverse_) {
        center =
            directionAxis_ == Axis::HORIZONTAL
                ? PointF(offset.GetX() + parameters.borderBlank + sliderSelectLength, offset.GetY() + centerWidth_)
                : PointF(offset.GetX() + centerWidth_, offset.GetY() + parameters.borderBlank + sliderSelectLength);
    } else {
        center = directionAxis_ == Axis::HORIZONTAL
                     ? PointF(offset.GetX() + parameters.borderBlank + parameters.sliderLength - sliderSelectLength,
                           offset.GetY() + centerWidth_)
                     : PointF(offset.GetX() + centerWidth_,
                           offset.GetY() + parameters.borderBlank + parameters.sliderLength - sliderSelectLength);
    }
    SetCircleCenter(center, theme);
    auto circleRadius = parameters.blockDiameter * HALF * HALF;
    SetCircleRadius(circleRadius);

    circlePenAndSize.shadowPen.SetAntiAlias(true);
    // The shadowColor is used to paint slider'block edge when hovered or pressed.
    // Outer slider's block needs to be painted with 1vp width edge when not hovered or not pressed,
    // which color is from theme's BlockOuterEdgeColor.
    Color shadowColor = theme->GetBlockOuterEdgeColor();
    shadowColor = parameters.mouseHoverFlag_ ? theme->GetBlockHoverColor() : shadowColor;
    shadowColor = parameters.mousePressedFlag_ ? theme->GetBlockPressedColor() : shadowColor;
    // add animate color
    SetBoardColor(LinearColor(shadowColor),
        parameters.mousePressedFlag_ ? static_cast<int32_t>(theme->GetPressAnimationDuration())
                                     : static_cast<int32_t>(theme->GetHoverAnimationDuration()),
        parameters.mousePressedFlag_ ? Curves::SHARP : Curves::FRICTION);
    circlePenAndSize.shadowPen.SetColor(ToRSColor(shadowColor));
    auto shadowWidth = parameters.hotFlag || parameters.mouseHoverFlag_
                           ? parameters.hotCircleShadowWidth
                           : static_cast<float>(CIRCLE_SHADOW_WIDTH.ConvertToPx());
    circlePenAndSize.shadowPen.SetWidth(shadowWidth);
    auto shadowRadius = (parameters.blockDiameter + shadowWidth) * HALF;
    SetCircleShadowRadius(shadowRadius);
}
} // namespace OHOS::Ace::NG
