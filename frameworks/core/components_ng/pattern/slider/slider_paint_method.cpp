/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include <cstddef>
#include <optional>

#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5f;
constexpr Dimension CIRCLE_SHADOW_WIDTH = 1.0_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_FIRST = 1.3_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_SECOND = 3.2_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_THIRD = 6.6_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_FOURTH = 16.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_FIRST = 0.1_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_SECOND = 3.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_THIRD = 8.0_vp;
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
} // namespace

CanvasDrawFunction SliderPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    auto contentOffset = paintWrapper->GetContentOffset();
    return [weak = WeakClaim(this), paintWrapper, paragraph = paragraph_, isDrawBubble = isDrawBubble_,
               textOffset = textOffset_ + contentOffset](RSCanvas& canvas) {
        auto tip = weak.Upgrade();
        CHECK_NULL_VOID(tip);
        if (isDrawBubble) {
            tip->PaintBubble(canvas, paintWrapper);
            CHECK_NULL_VOID(paragraph);
            paragraph->Paint(canvas, textOffset.GetX(), textOffset.GetY());
        }
    };
}

CanvasDrawFunction SliderPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    auto sliderPaintProperty = DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(sliderPaintProperty, nullptr);
    auto offset = paintWrapper->GetContentOffset();
    centerWidth_ = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                       ? paintWrapper->GetContentSize().Height()
                       : paintWrapper->GetContentSize().Width();
    centerWidth_ *= HALF;
    LinePenAndSize backgroundPenAndSize = GetBackgroundPen(sliderPaintProperty, offset, theme);
    std::optional<MarkerPenAndPath> markerPenAndPath = std::nullopt;
    if (sliderPaintProperty->GetShowSteps().value_or(false)) {
        markerPenAndPath = GetMarkerPen(sliderPaintProperty, offset, theme);
    }
    LinePenAndSize selectPenAndSize = GetSelectPen(sliderPaintProperty, offset, theme);
    CirclePenAndSize circlePenAndSize = GetCirclePen(sliderPaintProperty, offset, theme);
    return [background = backgroundPenAndSize, marker = markerPenAndPath, select = selectPenAndSize,
               circle = circlePenAndSize](RSCanvas& canvas) {
        canvas.AttachPen(background.pen);
        canvas.DrawLine(ToRSPoint(background.start), ToRSPoint(background.end));
        canvas.DetachPen();
        if (marker.has_value()) {
            canvas.AttachPen(marker.value().pen);
            canvas.DrawPath(marker.value().path);
            canvas.DetachPen();
        }
        if (select.start != select.end) {
            canvas.AttachPen(select.pen);
            canvas.DrawLine(ToRSPoint(select.start), ToRSPoint(select.end));
            canvas.DetachPen();
        }
        canvas.AttachPen(circle.pen);
        canvas.DrawCircle(ToRSPoint(circle.center), circle.radius);
        canvas.DetachPen();
        canvas.AttachPen(circle.shadowPen);
        canvas.DrawCircle(ToRSPoint(circle.center), circle.shadowRadius);
        canvas.DetachPen();
    };
}

SliderPaintMethod::LinePenAndSize SliderPaintMethod::GetBackgroundPen(
    const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset,
    const RefPtr<SliderTheme>& theme) const
{
    LinePenAndSize backgroundPenAndSize;
    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    backgroundPenAndSize.pen.SetAntiAlias(true);
    backgroundPenAndSize.pen.SetWidth(parameters_.trackThickness);
    backgroundPenAndSize.pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    backgroundPenAndSize.pen.SetColor(
        ToRSColor(sliderPaintProperty->GetTrackBackgroundColor().value_or(theme->GetTrackBgColor())));
    backgroundPenAndSize.start = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
        ? PointF(startPointX + parameters_.borderBlank, startPointY + centerWidth_)
        : PointF(startPointX + centerWidth_, startPointY + parameters_.borderBlank);
    backgroundPenAndSize.end = sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
        ? PointF(startPointX + parameters_.borderBlank + parameters_.sliderLength, startPointY + centerWidth_)
        : PointF(startPointX + centerWidth_, startPointY + parameters_.borderBlank + parameters_.sliderLength);
    return backgroundPenAndSize;
}

SliderPaintMethod::MarkerPenAndPath SliderPaintMethod::GetMarkerPen(
    const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset,
    const RefPtr<SliderTheme>& theme) const
{
    MarkerPenAndPath markerPenAndPath;
    markerPenAndPath.pen.SetAntiAlias(true);
    markerPenAndPath.pen.SetColor(ToRSColor(theme->GetMarkerColor()));
    markerPenAndPath.pen.SetWidth(static_cast<float>(theme->GetMarkerSize().ConvertToPx()));
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
    const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset,
    const RefPtr<SliderTheme>& theme) const
{
    LinePenAndSize selectPenAndSize;

    float sliderSelectLength =
        std::clamp(parameters_.sliderLength * parameters_.valueRatio, 0.0f, parameters_.sliderLength);
    CHECK_NULL_RETURN_NOLOG(!NearZero(sliderSelectLength), selectPenAndSize);
    selectPenAndSize.pen.SetAntiAlias(true);
    selectPenAndSize.pen.SetWidth(parameters_.trackThickness);
    selectPenAndSize.pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    selectPenAndSize.pen.SetColor(
        ToRSColor(sliderPaintProperty->GetSelectColor().value_or(theme->GetTrackSelectedColor())));

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
        selectPenAndSize.end =
            sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                ? PointF(offset.GetX() + parameters_.borderBlank + parameters_.sliderLength - sliderSelectLength,
                        offset.GetY() + centerWidth_)
                : PointF(offset.GetX() + centerWidth_,
                        offset.GetY() + parameters_.borderBlank + parameters_.sliderLength - sliderSelectLength);
    }
    return selectPenAndSize;
}

SliderPaintMethod::CirclePenAndSize SliderPaintMethod::GetCirclePen(
    const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset,
    const RefPtr<SliderTheme>& theme) const
{
    float sliderSelectLength =
        std::clamp(parameters_.sliderLength * parameters_.valueRatio, 0.0f, parameters_.sliderLength);
    CirclePenAndSize circlePenAndSize;
    circlePenAndSize.pen.SetAntiAlias(true);
    circlePenAndSize.pen.SetColor(ToRSColor(sliderPaintProperty->GetBlockColor().value_or(theme->GetBlockColor())));
    circlePenAndSize.pen.SetWidth(parameters_.blockDiameter * HALF);
    if (!sliderPaintProperty->GetReverse().value_or(false)) {
        circlePenAndSize.center =
            sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                ? PointF(offset.GetX() + parameters_.borderBlank + sliderSelectLength, offset.GetY() + centerWidth_)
                : PointF(offset.GetX() + centerWidth_, offset.GetY() + parameters_.borderBlank + sliderSelectLength);
    } else {
        circlePenAndSize.center =
            sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                ? PointF(offset.GetX() + parameters_.borderBlank + parameters_.sliderLength - sliderSelectLength,
                        offset.GetY() + centerWidth_)
                : PointF(offset.GetX() + centerWidth_,
                        offset.GetY() + parameters_.borderBlank + parameters_.sliderLength - sliderSelectLength);
    }
    circlePenAndSize.radius = parameters_.blockDiameter * HALF * HALF;

    circlePenAndSize.shadowPen.SetAntiAlias(true);
    Color shadowColor = theme->GetBlockOuterStrokeEdgeColor();
    shadowColor = parameters_.mouseHoverFlag_ ? theme->GetBlockHoverColor() : shadowColor;
    shadowColor = parameters_.mousePressedFlag_ ? theme->GetBlockPressedColor() : shadowColor;
    circlePenAndSize.shadowPen.SetColor(ToRSColor(shadowColor));
    auto shadowWidth = parameters_.hotFlag || parameters_.mouseHoverFlag_
                           ? parameters_.hotCircleShadowWidth
                           : static_cast<float>(CIRCLE_SHADOW_WIDTH.ConvertToPx());
    circlePenAndSize.shadowPen.SetWidth(shadowWidth);
    circlePenAndSize.shadowRadius = (parameters_.blockDiameter + shadowWidth) * HALF;
    return circlePenAndSize;
}

void PaintBezier(bool isLeft, Axis axis, RSPath& path, const OffsetF& arrowCenter, const OffsetF& arrowEdge)
{
    if (isLeft) {
        path.MoveTo(arrowCenter.GetX(), arrowCenter.GetY());
        if (axis == Axis::HORIZONTAL) {
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()));
        } else {
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()));
        }
        path.LineTo(arrowEdge.GetX(), arrowEdge.GetY());
    } else {
        path.MoveTo(arrowEdge.GetX(), arrowEdge.GetY());
        if (axis == Axis::HORIZONTAL) {
            path.LineTo(arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()), arrowCenter.GetX(),
                arrowCenter.GetY());
        } else {
            path.LineTo(arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx()),
                arrowCenter.GetX() - static_cast<float>(BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx()));
            path.QuadTo(arrowCenter.GetX() + static_cast<float>(BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx()),
                arrowCenter.GetY() - static_cast<float>(BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx()), arrowCenter.GetX(),
                arrowCenter.GetY());
        }
    }
}

void SliderPaintMethod::PaintBubble(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    auto paintProperty = DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto contentOffset = paintWrapper->GetContentOffset();
    auto offset = bubbleOffset_ + contentOffset;
    auto arrowHeight = static_cast<float>(ARROW_HEIGHT.ConvertToPx());
    RSPath path;
    OffsetF arrowCenter;
    OffsetF clockwiseFirstPoint;
    OffsetF clockwiseSecondPoint;
    float circularRadius = 0.0f;
    OffsetF clockwiseThirdPoint;
    OffsetF clockwiseFourthPoint;
    auto axis = paintProperty->GetDirection().value_or(Axis::HORIZONTAL);
    if (axis == Axis::HORIZONTAL) {
        arrowCenter = { offset.GetX() + bubbleSize_.Width() * HALF, offset.GetY() + bubbleSize_.Height() };
        float bottomLineLength = bubbleSize_.Width() - (bubbleSize_.Height() - arrowHeight);
        clockwiseFirstPoint = { arrowCenter.GetX() - bottomLineLength * HALF, arrowCenter.GetY() - arrowHeight };
        clockwiseSecondPoint = { clockwiseFirstPoint.GetX(), offset.GetY() };
        circularRadius = (clockwiseFirstPoint.GetY() - clockwiseSecondPoint.GetY()) * HALF;
        clockwiseThirdPoint = { clockwiseSecondPoint.GetX() + bottomLineLength, clockwiseSecondPoint.GetY() };
        clockwiseFourthPoint = { clockwiseThirdPoint.GetX(), offset.GetY() + circularRadius * 2 };
    } else {
        arrowCenter = { offset.GetX() + bubbleSize_.Width(), offset.GetY() + bubbleSize_.Height() * HALF };
        float bottomLineLength = bubbleSize_.Height() - (bubbleSize_.Width() - arrowHeight);
        clockwiseFirstPoint = { arrowCenter.GetX() - arrowHeight, arrowCenter.GetY() + bottomLineLength * HALF };
        clockwiseSecondPoint = { offset.GetX(), clockwiseFirstPoint.GetY() };
        circularRadius = (clockwiseFirstPoint.GetX() - clockwiseSecondPoint.GetX()) * HALF;
        clockwiseThirdPoint = { clockwiseSecondPoint.GetX(), clockwiseSecondPoint.GetY() - bottomLineLength };
        clockwiseFourthPoint = { offset.GetX() + circularRadius * 2, clockwiseThirdPoint.GetY() };
    }
    path.MoveTo(arrowCenter.GetX(), arrowCenter.GetY());
    PaintBezier(
        true, axis, path, arrowCenter, clockwiseFirstPoint);
    path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION, clockwiseSecondPoint.GetX(),
        clockwiseSecondPoint.GetY());
    path.LineTo(clockwiseThirdPoint.GetX(), clockwiseThirdPoint.GetY());
    path.ArcTo(circularRadius, circularRadius, 0.0f, RSPathDirection::CW_DIRECTION, clockwiseFourthPoint.GetX(),
        clockwiseFourthPoint.GetY());
    PaintBezier(
        false, axis, path, arrowCenter, clockwiseFourthPoint);
    RSPen pen;
    pen.SetColor(ToRSColor(paintProperty->GetTipColor().value_or(Color::BLACK)));
    pen.SetAntiAlias(true);
    RSBrush brush;
    brush.SetColor(ToRSColor(paintProperty->GetTipColor().value_or(Color::BLACK)));
    canvas.AttachPen(pen);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.ClipPath(path, RSClipOp::INTERSECT);
}
} // namespace OHOS::Ace::NG
