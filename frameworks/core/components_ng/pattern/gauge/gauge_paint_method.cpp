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

#include "core/components_ng/pattern/gauge/gauge_paint_method.h"

#include <algorithm>
#include <cmath>

#include "core/common/container.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF_CIRCLE = 180.0f;
constexpr float WHOLE_CIRCLE = 360.0f;
constexpr float QUARTER_CIRCLE = 90.0f;
constexpr float PERCENT_HALF = 0.5f;
constexpr float SEGMENTS_SPACE_PERCENT = 0.008f;
} // namespace

CanvasDrawFunction GaugePaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto gauge = weak.Upgrade();
        if (gauge) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_ELEVEN) {
                gauge->NewPaint(canvas, paintWrapper);
            } else {
                gauge->Paint(canvas, paintWrapper);
            }
        }
    };
    return paintFunc;
}

void GaugePaintMethod::Paint(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<GaugePaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto offset = paintWrapper->GetContentOffset();
    auto contentSize = paintWrapper->GetContentSize();
    RenderRingInfo data;
    data.radius = std::min(contentSize.Width(), contentSize.Height()) / 2.0f;
    data.center = Offset(contentSize.Width() / 2.0f + offset.GetX(), contentSize.Height() / 2.0f + offset.GetY());
    float startAngle = DEFAULT_START_DEGREE;
    float endAngle = DEFAULT_END_DEGREE;
    if (paintProperty->GetStartAngle().has_value() && !std::isnan(paintProperty->GetStartAngle().value())) {
        startAngle = paintProperty->GetStartAngle().value();
    }
    if (paintProperty->GetEndAngle().has_value() && !std::isnan(paintProperty->GetEndAngle().value())) {
        endAngle = paintProperty->GetEndAngle().value();
    }
    float startDegree = startAngle;
    float sweepDegree = endAngle - startAngle;
    if (sweepDegree > 360.0f || sweepDegree < 0.0f) {
        sweepDegree = sweepDegree - floor(sweepDegree / 360.0f) * 360.0f;
    }
    if (NearZero(sweepDegree)) {
        sweepDegree = 360.0f;
    }
    auto theme = pipelineContext->GetTheme<ProgressTheme>();
    data.thickness = theme->GetTrackThickness().ConvertToPx();
    if (paintProperty->GetStrokeWidth().has_value() && paintProperty->GetStrokeWidth()->Value() > 0) {
        data.thickness =
            std::min(static_cast<float>(paintProperty->GetStrokeWidth()->ConvertToPx()), contentSize.Width() / 2);
    }
    std::vector<float> weights;
    if (paintProperty->GetValues().has_value()) {
        weights = paintProperty->GetValuesValue();
    } else {
        weights.push_back(1);
    }
    std::vector<Color> colors;
    if (paintProperty->GetColors().has_value()) {
        colors = paintProperty->GetColorsValue();
    } else {
        colors.push_back(Color::BLACK);
    }
    float min = paintProperty->GetMinValue();
    float max = paintProperty->GetMaxValue();
    float value = paintProperty->GetValueValue();

    if (colors.size() == 0 || colors.size() != weights.size()) {
        LOGE("color size is 0 or is not equal to weight size");
        return;
    }
    float totalWeight = 0.0f;
    for (const auto& weight : weights) {
        totalWeight += weight;
    }
    if (NearEqual(totalWeight, 0.0)) {
        LOGE("total weight is 0.0");
        return;
    }
    float currentStart = 0.0f;
    float highLightStart = 0.0f;
    size_t highLightIndex = 0;
    float ratio = 0.0f;
    if (max < min) {
        min = 0.0f;
        max = 100.0f;
    }
    if (value < min || value > max) {
        value = min;
    }
    if (min < max && value >= min && value <= max) {
        ratio = (value - min) / (max - min);
    }
    for (int32_t index = static_cast<int32_t>(colors.size()) - 1; index >= 0; --index) {
        data.color = colors[index];
        data.color.ChangeAlpha(UNSELECT_ALPHA);
        currentStart += weights[index];
        if (ShouldHighLight(totalWeight - currentStart, weights[index], ratio * totalWeight)) {
            highLightIndex = static_cast<size_t>(index);
            highLightStart = totalWeight - currentStart;
        }
        data.startDegree = startDegree + (1 - currentStart / totalWeight) * sweepDegree;
        data.sweepDegree = (weights[index] / totalWeight) * sweepDegree;
        DrawGauge(canvas, data);
    }
    // draw highlight part
    data.color = colors[highLightIndex];
    data.startDegree = startDegree + (highLightStart / totalWeight) * sweepDegree;
    data.sweepDegree = (weights[highLightIndex] / totalWeight) * sweepDegree;
    DrawGauge(canvas, data);
    data.startDegree = startDegree;
    data.sweepDegree = sweepDegree * ratio;
    DrawIndicator(canvas, data);
}

void GaugePaintMethod::DrawGauge(RSCanvas& canvas, RenderRingInfo data) const
{
    float thickness = data.thickness;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(data.color.GetValue());
    pen.SetWidth(thickness);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);

    canvas.AttachPen(pen);
    RSPath path;
    RSRect rRect(data.center.GetX() - data.radius + thickness / 2.0f,
        data.center.GetY() - data.radius + thickness / 2.0f, data.center.GetX() + data.radius - thickness / 2.0f,
        data.center.GetY() + data.radius - thickness / 2.0f);
    path.AddArc(rRect, data.startDegree - 90.0f, data.sweepDegree);
    canvas.DrawPath(path);
    canvas.DetachPen();
}

void GaugePaintMethod::DrawIndicator(RSCanvas& canvas, RenderRingInfo data) const
{
    RSPath path;
    float pathStartVertexX = data.center.GetX();
    float pathStartVertexY = data.center.GetY() - data.radius + (data.thickness / 2);
    path.MoveTo(pathStartVertexX, pathStartVertexY);
    path.LineTo(pathStartVertexX - EDGE, pathStartVertexY + EDGE);
    path.LineTo(pathStartVertexX - EDGE, pathStartVertexY + EDGE + HEIGHT_OFFSET);
    path.LineTo(pathStartVertexX + EDGE, pathStartVertexY + EDGE + HEIGHT_OFFSET);
    path.LineTo(pathStartVertexX + EDGE, pathStartVertexY + EDGE);
    path.LineTo(pathStartVertexX, pathStartVertexY);

    canvas.Save();
    canvas.Rotate(data.startDegree + data.sweepDegree, data.center.GetX(), data.center.GetY());
    RSBrush paint;
    paint.SetColor(Color::WHITE.GetValue());
    canvas.AttachBrush(paint);
    canvas.DrawPath(path);
    canvas.DetachBrush();

    RSPen pen;
    pen.SetColor(Color::BLACK.GetValue());
    pen.SetWidth(INDICATOR_STROKE_WIDTH);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();
    canvas.Restore();
}

bool GaugePaintMethod::ShouldHighLight(const float start, const float interval, const float percent) const
{
    if (LessOrEqual(percent, start + interval) && GreatOrEqual(percent, start)) {
        return true;
    }
    return false;
}

void GaugePaintMethod::NewPaint(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    canvas.Save();
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<GaugePaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto offset = paintWrapper->GetContentOffset();
    auto contentSize = paintWrapper->GetContentSize();
    RenderRingInfo data;
    data.contentSize = contentSize;
    data.radius = std::min(contentSize.Width(), contentSize.Height()) * PERCENT_HALF;
    data.center =
        Offset(contentSize.Width() * PERCENT_HALF + offset.GetX(), contentSize.Height() * PERCENT_HALF + offset.GetY());
    auto theme = pipelineContext->GetTheme<ProgressTheme>();
    data.thickness = theme->GetTrackThickness().ConvertToPx();
    CalculateStartAndSweepDegree(paintProperty, data);
    switch (paintProperty->GetGaugeTypeValue()) {
        case GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT: {
            PaintMultiSegmentGradientCircular(canvas, data, paintProperty);
            break;
        }
        case GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT: {
            PaintSingleSegmentGradientCircular(canvas, data, paintProperty);
            break;
        }
        case GaugeType::TYPE_CIRCULAR_MONOCHROME: {
            PaintMonochromeCircular(canvas, data, paintProperty);
            break;
        }
        default:
            // do nothing.
            break;
    }
    canvas.Restore();
}

void GaugePaintMethod::PaintMonochromeCircular(
    RSCanvas& canvas, RenderRingInfo data, const RefPtr<GaugePaintProperty>& paintProperty) const
{
    CHECK_NULL_VOID(paintProperty);
    float startDegree = data.startDegree;
    float sweepDegree = data.sweepDegree;

    Color color = paintProperty->GetGradientColorsValue().at(0).at(0).first;
    Color backgroundColor = color.ChangeOpacity(MONOCHROME_CIRCULAR_BACKGROUND_COLOR_OPACITY);
    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    auto ratio = GetValueRatio(paintProperty);
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(backgroundColor.GetValue());
    pen.SetWidth(data.thickness);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);

    canvas.AttachPen(pen);
    RSPath path;
    RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                 data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);
    path.AddArc(rRect, startDegree - QUARTER_CIRCLE + offsetDegree, sweepDegree - 2.0f * offsetDegree);
    canvas.DrawPath(path);
    canvas.DetachPen();

    pen.SetColor(color.GetValue());
    canvas.AttachPen(pen);
    path.Reset();
    auto tempSweepDegree =
        GreatNotEqual(sweepDegree * ratio, 2.0f * offsetDegree) ? sweepDegree * ratio - 2.0f * offsetDegree : 0.0f;
    path.AddArc(rRect, startDegree - QUARTER_CIRCLE + offsetDegree, tempSweepDegree);
    canvas.DrawPath(path);
    canvas.DetachPen();

    data.sweepDegree = sweepDegree * ratio;
    NewDrawIndicator(canvas, data);
}

void GaugePaintMethod::PaintSingleSegmentGradientCircular(
    RSCanvas& canvas, RenderRingInfo data, const RefPtr<GaugePaintProperty>& paintProperty) const
{
    CHECK_NULL_VOID(paintProperty);
    float startDegree = data.startDegree;
    float sweepDegree = data.sweepDegree;

    std::vector<RSColorQuad> colors;
    std::vector<float> pos;
    auto colorsArray = paintProperty->GetGradientColorsValue().at(0);
    for (const auto& colorStop : colorsArray) {
        colors.emplace_back(colorStop.first.GetValue());
        pos.emplace_back(colorStop.second.Value());
    }

    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(data.thickness);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    pen.SetShaderEffect(RSShaderEffect::CreateSweepGradient(ToRSPoint(PointF(data.center.GetX(), data.center.GetY())),
        colors, pos, RSTileMode::CLAMP, offsetDegree, sweepDegree - offsetDegree));

    RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                 data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);

    RSPath path;
    path.AddArc(rRect, offsetDegree, sweepDegree - 2.0f * offsetDegree);
    canvas.Rotate(startDegree - QUARTER_CIRCLE, data.center.GetX(), data.center.GetY());
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();

    auto ratio = GetValueRatio(paintProperty);
    data.startDegree = QUARTER_CIRCLE;
    data.sweepDegree = sweepDegree * ratio;
    NewDrawIndicator(canvas, data);
}

void GaugePaintMethod::PaintMultiSegmentGradientCircular(
    RSCanvas& canvas, RenderRingInfo data, const RefPtr<GaugePaintProperty>& paintProperty) const
{
    CHECK_NULL_VOID(paintProperty);
    float startDegree = data.startDegree;
    float sweepDegree = data.sweepDegree;
    std::vector<float> weights;
    if (paintProperty->GetValues().has_value()) {
        weights = paintProperty->GetValuesValue();
    } else {
        weights.push_back(1);
    }
    std::vector<ColorStopArray> colors;
    if (paintProperty->GetGradientColors().has_value()) {
        colors = paintProperty->GetGradientColorsValue();
    } else {
        ColorStopArray colorStopArray;
        colorStopArray.emplace_back(std::make_pair(Color::BLACK, Dimension(0.0)));
        colors.push_back(colorStopArray);
    }

    if (colors.size() == 0 || colors.size() != weights.size()) {
        LOGE("color size is 0 or is not equal to weight size");
        return;
    }
    float totalWeight = 0.0f;
    for (const auto& weight : weights) {
        totalWeight += weight;
    }
    if (NearEqual(totalWeight, 0.0)) {
        LOGE("total weight is 0.0");
        return;
    }

    auto ratio = GetValueRatio(paintProperty);
    data.startDegree = QUARTER_CIRCLE;
    data.sweepDegree = sweepDegree * ratio;
    float drawStartDegree = 0.0f;
    float drawSweepDegree = 0.0f;
    canvas.Rotate(startDegree - QUARTER_CIRCLE, data.center.GetX(), data.center.GetY());
    for (size_t index = 0; index < colors.size(); index++) {
        std::vector<RSColorQuad> colorValues;
        std::vector<float> pos;
        auto colorsArray = colors.at(index);
        for (const auto& colorStop : colorsArray) {
            colorValues.emplace_back(colorStop.first.GetValue());
            pos.emplace_back(colorStop.second.Value());
        }

        drawStartDegree = drawStartDegree + drawSweepDegree;
        drawSweepDegree = (weights[index] / totalWeight) * sweepDegree;
        float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);

        RSPen pen;
        RSPath path;
        pen.SetAntiAlias(true);
        pen.SetWidth(data.thickness);
        pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
        RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                     data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                     data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                     data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);

        NewDrawIndicator(canvas, data);
        if (index != 0) {
            DrawHighLight(canvas, data, drawStartDegree);
            pen.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
                ToRSPoint(PointF(data.center.GetX(), data.center.GetY())), colorValues, pos, RSTileMode::CLAMP,
                drawStartDegree - offsetDegree, drawStartDegree + drawSweepDegree - offsetDegree));
            path.AddArc(rRect, drawStartDegree - offsetDegree, drawSweepDegree);
        } else {
            pen.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
                ToRSPoint(PointF(data.center.GetX(), data.center.GetY())), colorValues, pos, RSTileMode::CLAMP,
                drawStartDegree + offsetDegree, drawStartDegree + drawSweepDegree + offsetDegree));
            path.AddArc(rRect, drawStartDegree + offsetDegree, drawSweepDegree - 2.0f * offsetDegree);
        }

        canvas.AttachPen(pen);
        canvas.DrawPath(path);
        canvas.DetachPen();
    }
    NewDrawIndicator(canvas, data);
}

void GaugePaintMethod::CalculateStartAndSweepDegree(
    const RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data) const
{
    CHECK_NULL_VOID(paintProperty);
    float startAngle = DEFAULT_START_DEGREE;
    float endAngle = DEFAULT_END_DEGREE;

    if (paintProperty->GetStartAngle().has_value() && !std::isnan(paintProperty->GetStartAngle().value())) {
        startAngle = paintProperty->GetStartAngle().value();
    }

    if (paintProperty->GetEndAngle().has_value() && !std::isnan(paintProperty->GetEndAngle().value())) {
        endAngle = paintProperty->GetEndAngle().value();
    }

    if (paintProperty->GetStrokeWidth().has_value() && paintProperty->GetStrokeWidth()->Value() > 0) {
        data.thickness = std::min(static_cast<float>(paintProperty->GetStrokeWidth()->ConvertToPx()),
            data.contentSize.Width() * PERCENT_HALF);
    }

    float sweepDegree = endAngle - startAngle;
    if (GreatNotEqual(sweepDegree, DEFAULT_END_DEGREE) || LessNotEqual(sweepDegree, DEFAULT_START_DEGREE)) {
        sweepDegree = sweepDegree - floor(sweepDegree / WHOLE_CIRCLE) * WHOLE_CIRCLE;
    }

    if (NearZero(sweepDegree)) {
        sweepDegree = WHOLE_CIRCLE;
    }
    data.startDegree = startAngle;
    data.sweepDegree = sweepDegree;
}

void GaugePaintMethod::DrawHighLight(RSCanvas& canvas, const RenderRingInfo& data, const float drawStartDegree) const
{
    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    auto radius = data.radius - data.thickness * PERCENT_HALF;
    auto space = data.radius * 2.0f * SEGMENTS_SPACE_PERCENT;
    RSPath path1;
    path1.AddCircle(data.center.GetX() + radius * std::cos((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                    data.center.GetY() + radius * std::sin((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                    data.thickness * PERCENT_HALF);

    RSPath path2;
    path2.AddCircle(data.center.GetX() + radius * std::cos((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                    data.center.GetY() + radius * std::sin((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                    (data.thickness * PERCENT_HALF + space));

    RSPath path3;
    path3.Op(path2, path1, RSPathOp::DIFFERENCE);

    float tempDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF + space);
    RSPath path4;
    path4.MoveTo(
        data.center.GetX() + (data.radius) * std::cos((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
        data.center.GetY() + (data.radius) * std::sin((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE));
    path4.LineTo(
        data.center.GetX() + (data.radius - data.thickness) *
            std::cos((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
        data.center.GetY() + (data.radius - data.thickness) *
            std::sin((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE));
    path4.LineTo(
        data.center.GetX() + (data.radius - data.thickness) *
            std::cos((drawStartDegree - offsetDegree - tempDegree) * M_PI / HALF_CIRCLE),
        data.center.GetY() + (data.radius - data.thickness) *
            std::sin((drawStartDegree - offsetDegree - tempDegree) * M_PI / HALF_CIRCLE));
    path4.LineTo(
        data.center.GetX() + (data.radius) *
            std::cos((drawStartDegree - offsetDegree - tempDegree) * M_PI / HALF_CIRCLE),
        data.center.GetY() + (data.radius) *
            std::sin((drawStartDegree - offsetDegree - tempDegree) * M_PI / HALF_CIRCLE));

    RSPath path5;
    path5.Op(path3, path4, RSPathOp::DIFFERENCE);
    canvas.ClipPath(path5, RSClipOp::DIFFERENCE, true);

    RSPath path6;
    path6.AddCircle(data.center.GetX() + radius * std::cos((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                    data.center.GetY() + radius * std::sin((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                    data.thickness * PERCENT_HALF);
    canvas.ClipPath(path6, RSClipOp::DIFFERENCE, true);
}

float GaugePaintMethod::GetOffsetDegree(const RenderRingInfo& data, const float oppositeSide) const
{
    return NearEqual(data.radius, data.thickness * PERCENT_HALF)
               ? 0.0f
               : std::tan((oppositeSide) / (data.radius - data.thickness * PERCENT_HALF)) * HALF_CIRCLE / M_PI;
}

float GaugePaintMethod::GetValueRatio(const RefPtr<GaugePaintProperty>& paintProperty) const
{
    CHECK_NULL_RETURN(paintProperty, 0.0f);
    float min = paintProperty->GetMinValue();
    float max = paintProperty->GetMaxValue();
    float value = paintProperty->GetValueValue();

    if (LessOrEqual(max, min)) {
        min = DEFAULT_MIN_VALUE;
        max = DEFAULT_MAX_VALUE;
    }

    value = std::clamp(value, min, max);
    return (value - min) / (max - min);
}

void GaugePaintMethod::NewDrawIndicator(RSCanvas& canvas, const RenderRingInfo& data) const
{
    RSPath path;
    float pathStartVertexX = data.center.GetX();
    float pathStartVertexY = data.center.GetY() - data.radius + INDICATOR_DISTANCE_TO_TOP.ConvertToPx();
    path.MoveTo(pathStartVertexX - CALC_INDICATOR_POINT_TOP_LEFT * data.radius,
        pathStartVertexY + CALC_INDICATOR_POINT_TOP_LEFT * data.radius);
    path.LineTo(pathStartVertexX - CALC_INDICATOR_POINT_BOTTOM_LEFT_X * data.radius,
        pathStartVertexY + CALC_INDICATOR_POINT_BOTTOM_LEFT_Y * data.radius);

    path.QuadTo(pathStartVertexX - CALC_INDICATOR_CONTROL_POINT_LEFT_X * data.radius,
        pathStartVertexY + CALC_INDICATOR_CONTROL_POINT_LEFT_Y * data.radius,
        pathStartVertexX - CALC_INDICATOR_POINT_RIGHT_X * data.radius,
        pathStartVertexY + CALC_INDICATOR_POINT_RIGHT_Y * data.radius);
    path.LineTo(pathStartVertexX + CALC_INDICATOR_POINT_RIGHT_X * data.radius,
        pathStartVertexY + CALC_INDICATOR_POINT_RIGHT_Y * data.radius);

    path.QuadTo(pathStartVertexX + CALC_INDICATOR_CONTROL_POINT_LEFT_X * data.radius,
        pathStartVertexY + CALC_INDICATOR_CONTROL_POINT_RIGHT_X * data.radius,
        pathStartVertexX + CALC_INDICATOR_POINT_BOTTOM_LEFT_X * data.radius,
        pathStartVertexY + CALC_INDICATOR_POINT_BOTTOM_LEFT_Y * data.radius);
    path.LineTo(pathStartVertexX + CALC_INDICATOR_POINT_TOP_LEFT * data.radius,
        pathStartVertexY + CALC_INDICATOR_POINT_TOP_LEFT * data.radius);
    path.QuadTo(pathStartVertexX, pathStartVertexY + CALC_INDICATOR_CONTROL_POINT_RIGHT_Y * data.radius,
        pathStartVertexX - CALC_INDICATOR_POINT_TOP_LEFT * data.radius,
        pathStartVertexY + CALC_INDICATOR_POINT_TOP_LEFT * data.radius);

    canvas.Save();
    canvas.Rotate(data.startDegree + data.sweepDegree, data.center.GetX(), data.center.GetY());
    RSBrush paint;
    paint.SetColor(Color::WHITE.GetValue());
    paint.SetBlendMode(RSBlendMode::SRC_OVER);
    canvas.AttachBrush(paint);
    canvas.DrawPath(path);
    canvas.DetachBrush();

    RSPen pen;
    pen.SetBlendMode(RSBlendMode::SRC_OVER);
    pen.SetColor(Color::BLACK.GetValue());
    pen.SetAntiAlias(true);
    pen.SetWidth(INDICATOR_BORDER_WIDTH_RATIO * data.radius);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();
    canvas.Restore();
}
} // namespace OHOS::Ace::NG
