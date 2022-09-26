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

#include "core/components_ng/pattern/slider/slider_paint_method.h"

#include <algorithm>
#include <cmath>

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction SliderPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto sliderPaintProperty = DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(sliderPaintProperty, nullptr);
    auto offset = paintWrapper->GetContentOffset();
    centerWidth_ = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                       ? paintWrapper->GetContentSize().Height()
                       : paintWrapper->GetContentSize().Width();
    centerWidth_ *= HALF;
    LinePenAndSize backgroundPenAndSize = GetBackgroundPen(sliderPaintProperty, offset);
    MarkerPenAndPath markerPenAndPath = GetMarkerPen(sliderPaintProperty, offset);
    LinePenAndSize selectPenAndSize = GetSelectPen(sliderPaintProperty, offset);
    CirclePenAndSize circlePenAndSize = GetCirclePen(sliderPaintProperty, offset);
    return [background = backgroundPenAndSize, marker = markerPenAndPath, select = selectPenAndSize,
               circle = circlePenAndSize](RSCanvas& canvas) {
        canvas.AttachPen(background.pen);
        canvas.DrawLine(ToRSPonit(background.start), ToRSPonit(background.end));
        canvas.DetachPen();
        canvas.AttachPen(marker.pen);
        canvas.DrawPath(marker.path);
        canvas.DetachPen();
        canvas.AttachPen(select.pen);
        canvas.DrawLine(ToRSPonit(select.start), ToRSPonit(select.end));
        canvas.DetachPen();
        canvas.AttachPen(circle.pen);
        canvas.DrawCircle(ToRSPonit(circle.center), circle.radius);
        canvas.DetachPen();
    };
}

SliderPaintMethod::LinePenAndSize SliderPaintMethod::GetBackgroundPen(
    const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset) const
{
    LinePenAndSize backgroundPenAndSize;
    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    backgroundPenAndSize.pen.SetAntiAlias(true);
    backgroundPenAndSize.pen.SetWidth(parameters_.trackThickness);
    backgroundPenAndSize.pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    backgroundPenAndSize.pen.SetColor(ToRSColor(sliderPaintProperty->GetTrackBackgroundColor().value_or(Color::BLACK)));
    backgroundPenAndSize.start = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                                     ? PointF(startPointX + parameters_.borderBlank, startPointY + centerWidth_)
                                     : PointF(startPointX + centerWidth_, startPointY + parameters_.borderBlank);
    backgroundPenAndSize.end = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
            ? PointF(startPointX + parameters_.borderBlank + parameters_.sliderLength, startPointY + centerWidth_)
            : PointF(startPointX + centerWidth_, startPointY + parameters_.borderBlank + parameters_.sliderLength);
    return backgroundPenAndSize;
}

SliderPaintMethod::MarkerPenAndPath SliderPaintMethod::GetMarkerPen(
    const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset) const
{
    MarkerPenAndPath markerPenAndPath;
    markerPenAndPath.pen.SetColor(ToRSColor(sliderPaintProperty->GetMarkerColor().value_or(Color::BLACK)));
    markerPenAndPath.pen.SetWidth(
        static_cast<float>(sliderPaintProperty->GetMarkerSize().value_or(0.0_vp).ConvertToPx()));
    markerPenAndPath.pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);

    auto stepsLength = parameters_.sliderLength * parameters_.stepRatio;
    if (sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        float dyOffset = offset.GetY() + centerWidth_;
        float start = offset.GetX() + parameters_.borderBlank;
        float end = start + parameters_.sliderLength;
        float current = start;
        while (LessOrEqual(current, end)) {
            float dxOffset = std::clamp(current, start, end);
            markerPenAndPath.path.MoveTo(dxOffset, dyOffset);
            markerPenAndPath.path.LineTo(dxOffset, dyOffset);
            current += stepsLength;
        }
    } else {
        float dxOffset = offset.GetX() + centerWidth_;
        float start = offset.GetY() + parameters_.borderBlank;
        float end = start + parameters_.sliderLength;
        float current = start;
        while (LessOrEqual(current, end)) {
            float dyOffset = std::clamp(current, start, end);
            markerPenAndPath.path.MoveTo(dxOffset, dyOffset);
            markerPenAndPath.path.LineTo(dxOffset, dyOffset);
            current += stepsLength;
        }
    }
    return markerPenAndPath;
}

SliderPaintMethod::LinePenAndSize SliderPaintMethod::GetSelectPen(
    const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset) const
{
    LinePenAndSize selectPenAndSize;

    float sliderSelectLength =
        std::clamp(parameters_.sliderLength * parameters_.valueRatio, 0.0f, parameters_.sliderLength);

    selectPenAndSize.pen.SetAntiAlias(true);
    selectPenAndSize.pen.SetWidth(parameters_.trackThickness);
    selectPenAndSize.pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    selectPenAndSize.pen.SetColor(ToRSColor(sliderPaintProperty->GetSelectColor().value_or(Color::BLACK)));

    if (!sliderPaintProperty->GetReverse().value_or(false)) {
        selectPenAndSize.start = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                                     ? PointF(offset.GetX() + parameters_.borderBlank, offset.GetY() + centerWidth_)
                                     : PointF(offset.GetX() + centerWidth_, offset.GetY() + parameters_.borderBlank);
        selectPenAndSize.end = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                ? PointF(offset.GetX() + parameters_.borderBlank + sliderSelectLength, offset.GetY() + centerWidth_)
                : PointF(offset.GetX() + centerWidth_, offset.GetY() + parameters_.borderBlank + sliderSelectLength);
    } else {
        selectPenAndSize.start = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
            ? PointF(offset.GetX() + parameters_.borderBlank + parameters_.sliderLength, offset.GetY() + centerWidth_)
            : PointF(offset.GetX() + centerWidth_, offset.GetY() + parameters_.borderBlank + parameters_.sliderLength);
        selectPenAndSize.end = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
            ? PointF(offset.GetX() + parameters_.borderBlank + parameters_.sliderLength - sliderSelectLength,
                offset.GetY() + centerWidth_)
            : PointF(offset.GetX() + centerWidth_,
                offset.GetY() + parameters_.borderBlank + parameters_.sliderLength - sliderSelectLength);
    }
    return selectPenAndSize;
}

SliderPaintMethod::CirclePenAndSize SliderPaintMethod::GetCirclePen(
    const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset) const
{
    float sliderSelectLength =
        std::clamp(parameters_.sliderLength * parameters_.valueRatio, 0.0f, parameters_.sliderLength);
    CirclePenAndSize circlePenAndSize;
    circlePenAndSize.pen.SetColor(ToRSColor(sliderPaintProperty->GetBlockColor().value_or(Color::BLACK)));
    circlePenAndSize.pen.SetWidth(parameters_.blockDiameter * HALF);
    if (!sliderPaintProperty->GetReverse().value_or(false)) {
        circlePenAndSize.center = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                ? PointF(offset.GetX() + parameters_.borderBlank + sliderSelectLength, offset.GetY() + centerWidth_)
                : PointF(offset.GetX() + centerWidth_, offset.GetY() + parameters_.borderBlank + sliderSelectLength);
    } else {
        circlePenAndSize.center = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                ? PointF(offset.GetX() + parameters_.borderBlank + parameters_.sliderLength - sliderSelectLength,
                    offset.GetY() + centerWidth_)
                : PointF(offset.GetX() + centerWidth_,
                    offset.GetY() + parameters_.borderBlank + parameters_.sliderLength - sliderSelectLength);
    }
    circlePenAndSize.radius = parameters_.blockDiameter * HALF * HALF;
    return circlePenAndSize;
}

} // namespace OHOS::Ace::NG