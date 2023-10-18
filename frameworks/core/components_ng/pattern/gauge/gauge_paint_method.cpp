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
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"
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
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                gauge->Paint(canvas, paintWrapper);
            } else {
                gauge->NewPaint(canvas, paintWrapper);
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
#ifndef USE_ROSEN_DRAWING
    RSPath path;
#else
    RSRecordingPath path;
#endif
    RSRect rRect(data.center.GetX() - data.radius + thickness / 2.0f,
        data.center.GetY() - data.radius + thickness / 2.0f, data.center.GetX() + data.radius - thickness / 2.0f,
        data.center.GetY() + data.radius - thickness / 2.0f);
    path.AddArc(rRect, data.startDegree - 90.0f, data.sweepDegree);
    canvas.DrawPath(path);
    canvas.DetachPen();
}

void GaugePaintMethod::DrawIndicator(RSCanvas& canvas, RenderRingInfo data) const
{
#ifndef USE_ROSEN_DRAWING
    RSPath path;
#else
    RSRecordingPath path;
#endif
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

    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto paddingSize = geometryNode->GetPaddingSize();
    auto left = geometryNode->GetPadding()->left.value_or(0.0f);
    auto top = geometryNode->GetPadding()->top.value_or(0.0f);
    auto radius = std::min(paddingSize.Width(), paddingSize.Height()) / 2.0f;
    RenderRingInfo data;
    data.contentSize = paddingSize;
    data.radius = radius;
    data.center = Offset(offset.GetX() + left + radius, offset.GetY() + top + radius);
    auto theme = pipelineContext->GetTheme<GaugeTheme>();
    data.thickness = theme->GetTrackThickness().ConvertToPx();
    CalculateStartAndSweepDegree(paintProperty, data);
    switch (paintProperty->GetGaugeTypeValue(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT)) {
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
    Color color(Color::BLACK);
    if (paintProperty->HasGradientColors()) {
        color = paintProperty->GetGradientColorsValue().at(0).at(0).first;
    }

    Color backgroundColor = color.ChangeOpacity(MONOCHROME_CIRCULAR_BACKGROUND_COLOR_OPACITY);
    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    auto ratio = GetValueRatio(paintProperty);
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(data.thickness);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                 data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);
    RSPath path;
    path.AddArc(rRect, data.startDegree - QUARTER_CIRCLE + offsetDegree, data.sweepDegree - 2.0f * offsetDegree);

    auto tempSweepDegree = GreatNotEqual(data.sweepDegree * ratio, 2.0f * offsetDegree)
                               ? data.sweepDegree * ratio - 2.0f * offsetDegree
                               : 0.0f;

    PaintMonochromeCircularShadow(canvas, data, color, paintProperty, tempSweepDegree);
    pen.SetColor(backgroundColor.GetValue());
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();

    path.Reset();
    path.AddArc(rRect, data.startDegree - QUARTER_CIRCLE + offsetDegree, tempSweepDegree);
    pen.SetColor(color.GetValue());

    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();

    data.sweepDegree = data.sweepDegree * ratio;
    NewDrawIndicator(canvas, paintProperty, data);
}

void GaugePaintMethod::PaintMonochromeCircularShadow(RSCanvas& canvas, const RenderRingInfo& data, const Color& color,
    const RefPtr<GaugePaintProperty>& paintProperty, const float sweepDegree) const
{
    CHECK_NULL_VOID(paintProperty);
    GaugeShadowOptions shadowOptions;
    if (paintProperty->HasShadowOptions()) {
        shadowOptions = paintProperty->GetShadowOptionsValue();
    }
    if (!shadowOptions.isShadowVisible) {
        return;
    }
    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::NORMAL, shadowOptions.radius));
    RSPen shadowPen;
    shadowPen.SetAntiAlias(true);
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    shadowPen.SetColor(color.GetValue());
    shadowPen.SetFilter(filter);
    shadowPen.SetWidth(data.thickness);
    shadowPen.SetAlphaF(SHADOW_ALPHA);

    RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                 data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);
    RSPath shadowPath;
    shadowPath.AddArc(rRect, data.startDegree - QUARTER_CIRCLE + offsetDegree, sweepDegree);

    canvas.Save();
    canvas.Translate(shadowOptions.offsetX, shadowOptions.offsetY);
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(shadowPath);
    canvas.DetachPen();
    canvas.Restore();
}

void GaugePaintMethod::PaintSingleSegmentGradientCircular(
    RSCanvas& canvas, RenderRingInfo data, const RefPtr<GaugePaintProperty>& paintProperty) const
{
    CHECK_NULL_VOID(paintProperty);
    std::vector<RSColorQuad> colors;
    std::vector<float> pos;
    if (paintProperty->HasGradientColors()) {
        auto colorsArray = paintProperty->GetGradientColorsValue().at(0);
        for (const auto& colorStop : colorsArray) {
            colors.emplace_back(colorStop.first.GetValue());
            pos.emplace_back(colorStop.second.Value());
        }
    } else {
        CreateDefaultColor(colors, pos);
    }

    PaintSingleSegmentGradientCircularShadow(canvas, data, paintProperty, colors, pos);
    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(data.thickness);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    pen.SetShaderEffect(RSShaderEffect::CreateSweepGradient(ToRSPoint(PointF(data.center.GetX(), data.center.GetY())),
        colors, pos, RSTileMode::CLAMP, offsetDegree, data.sweepDegree - offsetDegree));

    RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                 data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);

    RSPath path;
    path.AddArc(rRect, offsetDegree, data.sweepDegree - 2.0f * offsetDegree);
    canvas.Rotate(data.startDegree - QUARTER_CIRCLE, data.center.GetX(), data.center.GetY());
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();

    auto ratio = GetValueRatio(paintProperty);
    data.startDegree = QUARTER_CIRCLE;
    data.sweepDegree = data.sweepDegree * ratio;
    NewDrawIndicator(canvas, paintProperty, data);
}

void GaugePaintMethod::PaintSingleSegmentGradientCircularShadow(RSCanvas& canvas, const RenderRingInfo& data,
    const RefPtr<GaugePaintProperty>& paintProperty, const std::vector<RSColorQuad>& colors,
    const std::vector<float>& pos) const
{
    CHECK_NULL_VOID(paintProperty);
    GaugeShadowOptions shadowOptions;
    if (paintProperty->HasShadowOptions()) {
        shadowOptions = paintProperty->GetShadowOptionsValue();
    }
    if (!shadowOptions.isShadowVisible) {
        return;
    }

    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::NORMAL, shadowOptions.radius));
    RSPen shadowPen;
    shadowPen.SetAntiAlias(true);
    shadowPen.SetWidth(data.thickness);
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    shadowPen.SetAlphaF(SHADOW_ALPHA);
    shadowPen.SetFilter(filter);
    shadowPen.SetShaderEffect(
        RSShaderEffect::CreateSweepGradient(ToRSPoint(PointF(data.center.GetX(), data.center.GetY())), colors, pos,
            RSTileMode::CLAMP, offsetDegree, data.sweepDegree - offsetDegree));

    RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                 data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);

    RSPath path;
    path.AddArc(rRect, offsetDegree, data.sweepDegree - 2.0f * offsetDegree);

    canvas.Save();
    canvas.Translate(shadowOptions.offsetX, shadowOptions.offsetY);
    canvas.Rotate(data.startDegree - QUARTER_CIRCLE, data.center.GetX(), data.center.GetY());
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(path);
    canvas.DetachPen();
    canvas.Restore();
}

void GaugePaintMethod::PaintMultiSegmentGradientCircular(
    RSCanvas& canvas, RenderRingInfo data, const RefPtr<GaugePaintProperty>& paintProperty) const
{
    CHECK_NULL_VOID(paintProperty);
    float startDegree = data.startDegree;
    float sweepDegree = data.sweepDegree;
    std::vector<float> weights;
    if (paintProperty->HasValues()) {
        weights = paintProperty->GetValuesValue();
    } else {
        weights.push_back(1);
    }
    std::vector<ColorStopArray> colors;
    if (paintProperty->HasGradientColors()) {
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

    PaintMultiSegmentGradientCircularShadow(canvas, data, paintProperty, colors, weights);

    auto ratio = GetValueRatio(paintProperty);
    data.startDegree = QUARTER_CIRCLE;
    data.sweepDegree = sweepDegree * ratio;
    SingleSegmentGradientInfo info;
    info.isDrawShadow = false;
    canvas.Rotate(startDegree - QUARTER_CIRCLE, data.center.GetX(), data.center.GetY());
    for (size_t index = 0; index < colors.size(); index++) {
        info.drawStartDegree = info.drawStartDegree + info.drawSweepDegree;
        info.drawSweepDegree = (weights[index] / totalWeight) * sweepDegree;
        info.offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
        info.colorStopArray = colors.at(index);
        DrawSingleSegmentGradient(canvas, data, paintProperty, info, index);
    }
    NewDrawIndicator(canvas, paintProperty, data);
}

void GaugePaintMethod::PaintMultiSegmentGradientCircularShadow(RSCanvas& canvas, const RenderRingInfo& data,
    const RefPtr<GaugePaintProperty>& paintProperty, const std::vector<ColorStopArray>& colors,
    const std::vector<float>& weights) const
{
    CHECK_NULL_VOID(paintProperty);
    GaugeShadowOptions shadowOptions;
    if (paintProperty->HasShadowOptions()) {
        shadowOptions = paintProperty->GetShadowOptionsValue();
    }

    if (!shadowOptions.isShadowVisible) {
        return;
    }
    float totalWeight = 0.0f;
    for (const auto& weight : weights) {
        totalWeight += weight;
    }
    canvas.Save();
    canvas.Translate(shadowOptions.offsetX, shadowOptions.offsetY);
    canvas.Rotate(data.startDegree - QUARTER_CIRCLE, data.center.GetX(), data.center.GetY());

    SingleSegmentGradientInfo info;
    info.isDrawShadow = true;
    info.shadowRadius = shadowOptions.radius;
    for (size_t index = 0; index < colors.size(); index++) {
        info.drawStartDegree = info.drawStartDegree + info.drawSweepDegree;
        info.drawSweepDegree = (weights[index] / totalWeight) * data.sweepDegree;
        info.offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
        info.colorStopArray = colors.at(index);
        DrawSingleSegmentGradient(canvas, data, paintProperty, info, index);
    }
    canvas.Restore();
}

void GaugePaintMethod::DrawSingleSegmentGradient(RSCanvas& canvas, const RenderRingInfo& data,
    const RefPtr<GaugePaintProperty>& paintProperty, const SingleSegmentGradientInfo& info, const size_t index) const
{
    auto drawStartDegree = info.drawStartDegree;
    auto drawSweepDegree = info.drawSweepDegree;
    auto offsetDegree = info.offsetDegree;
    std::vector<RSColorQuad> colorValues;
    std::vector<float> pos;
    for (const auto& colorStop : info.colorStopArray) {
        colorValues.emplace_back(colorStop.first.GetValue());
        pos.emplace_back(colorStop.second.Value());
    }

    RSPen pen;
    RSPath path;
    pen.SetAntiAlias(true);
    pen.SetWidth(data.thickness);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                 data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);

    if (info.isDrawShadow) {
        RSFilter filter;
        filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::NORMAL, info.shadowRadius));
        pen.SetFilter(filter);
        pen.SetAlphaF(SHADOW_ALPHA);
    } else {
        NewDrawIndicator(canvas, paintProperty, data);
    }

    if (index != 0) {
        if (!info.isDrawShadow) {
            DrawHighLight(canvas, data, drawStartDegree);
        }
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

void GaugePaintMethod::CalculateStartAndSweepDegree(
    const RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data) const
{
    CHECK_NULL_VOID(paintProperty);
    float startAngle = DEFAULT_START_DEGREE;
    float endAngle = DEFAULT_END_DEGREE;

    if (paintProperty->HasStartAngle() && !std::isnan(paintProperty->GetStartAngleValue())) {
        startAngle = paintProperty->GetStartAngleValue();
    }

    if (paintProperty->HasEndAngle() && !std::isnan(paintProperty->GetEndAngleValue())) {
        endAngle = paintProperty->GetEndAngleValue();
    }

    if (paintProperty->HasStrokeWidth() && (paintProperty->GetStrokeWidth()->Value() > 0)) {
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

    canvas.ClipPath(path2, RSClipOp::DIFFERENCE, true);

    RSPath path3;
    path3.Op(path2, path1, RSPathOp::DIFFERENCE);

    float tempDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF + space);
    RSPath path4;
    path4.MoveTo(data.center.GetX() + (data.radius) * std::cos((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
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

void GaugePaintMethod::NewDrawIndicator(
    RSCanvas& canvas, const RefPtr<GaugePaintProperty>& paintProperty, const RenderRingInfo& data) const
{
    CHECK_NULL_VOID(paintProperty);
    if (!(paintProperty->GetIsShowIndicatorValue(true))) {
        return;
    }
    if (paintProperty->HasIndicatorIconSourceInfo()) {
        NewDrawImageIndicator(canvas, paintProperty, data);
        return;
    }

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<GaugeTheme>();

    Dimension indicatorToTop = paintProperty->GetIndicatorSpaceValue(INDICATOR_DISTANCE_TO_TOP);
    if (GreatNotEqual(indicatorToTop.ConvertToPx(), data.radius)) {
        indicatorToTop = INDICATOR_DISTANCE_TO_TOP;
    }

    float pathStartVertexX = data.center.GetX();
    float pathStartVertexY = data.center.GetY() - data.radius + indicatorToTop.ConvertToPx() -
                             INDICATOR_BORDER_WIDTH_RATIO * data.radius / 2.0f;
    RSPath path;
    CreateDefaultTrianglePath(pathStartVertexX, pathStartVertexY, data.radius, path);
    canvas.Save();
    canvas.Rotate(data.startDegree + data.sweepDegree, data.center.GetX(), data.center.GetY());
    RSPen pen;
    pen.SetBlendMode(RSBlendMode::SRC_OVER);
    pen.SetColor(theme->GetIndicatorBorderColor().GetValue());
    pen.SetAntiAlias(true);
    pen.SetWidth(INDICATOR_BORDER_WIDTH_RATIO_DOUBLE * data.radius);
    pen.SetJoinStyle(RSPen::JoinStyle::ROUND_JOIN);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();

    RSBrush paint;
    paint.SetAntiAlias(true);
    paint.SetColor(theme->GetIndicatorColor().GetValue());
    paint.SetBlendMode(RSBlendMode::SRC_OVER);
    canvas.AttachBrush(paint);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    canvas.Restore();
}

void GaugePaintMethod::NewDrawImageIndicator(
    RSCanvas& canvas, const RefPtr<GaugePaintProperty>& paintProperty, const RenderRingInfo& data) const
{
    CHECK_NULL_VOID(paintProperty);
    canvas.Save();
    canvas.Rotate(data.startDegree + data.sweepDegree, data.center.GetX(), data.center.GetY());
    auto gaugePattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(gaugePattern);
    RefPtr<CanvasImage> indicatorIconCanvasImage = gaugePattern->GetIndicatorIconCanvasImage();
    Dimension indicatorToTop = paintProperty->GetIndicatorSpaceValue(INDICATOR_DISTANCE_TO_TOP);
    if (GreatNotEqual(indicatorToTop.ConvertToPx(), data.radius)) {
        indicatorToTop = INDICATOR_DISTANCE_TO_TOP;
    }

    CHECK_NULL_VOID(indicatorIconCanvasImage);
    auto&& config = indicatorIconCanvasImage->GetPaintConfig();
    config.renderMode_ = ImageRenderMode::ORIGINAL;
    config.imageInterpolation_ = ImageInterpolation::NONE;
    config.imageRepeat_ = ImageRepeat::NO_REPEAT;
    config.imageFit_ = ImageFit::FILL;
    config.isSvg_ = true;
    auto diameter = data.radius * RADIUS_TO_DIAMETER;
    float pathStartVertexX = data.center.GetX();
    float pathStartVertexY = data.center.GetY() - data.radius + indicatorToTop.ConvertToPx();

    const ImagePainter indicatorIconImagePainter(indicatorIconCanvasImage);
    indicatorIconImagePainter.DrawImage(canvas,
        OffsetF(pathStartVertexX - INDICATOR_WIDTH_RADIO * data.radius, pathStartVertexY),
        SizeF(INDICATOR_WIDTH_RADIO * diameter, INDICATOR_HEIGHT_RADIO * diameter));
    canvas.Restore();
}

void GaugePaintMethod::CreateDefaultColor(std::vector<RSColorQuad>& colors, std::vector<float>& pos) const
{
    float space = 0.0f;
    for (const auto& color : GAUGE_DEFAULT_COLOR) {
        colors.emplace_back(color.GetValue());
        pos.emplace_back(space);
        space += 0.5f;
    }
}

void GaugePaintMethod::CreateDefaultTrianglePath(
    float pathStartVertexX, float pathStartVertexY, float radius, RSPath& path) const
{
    auto width = radius * RADIUS_TO_DIAMETER * INDICATOR_WIDTH_RATIO;
    auto height = radius * RADIUS_TO_DIAMETER * INDICATOR_HEIGHT_RATIO;
    auto hypotenuse = std::sqrt(((width / 2.0f) * (width / 2.0f)) + (height * height));
    if (NearZero(hypotenuse)) {
        return;
    }
    auto cornerRadius = radius * RADIUS_TO_DIAMETER * INDICATOR_CORNER_RADIUS_RATIO;
    auto bottomAngle = std::atan(height / (width / 2.0f));

    auto tempTopHypotenuse = cornerRadius / (width / 2.0f) * height;
    auto tempTopWidth = tempTopHypotenuse / hypotenuse * (width / 2.0f);
    auto tempTopHeight = tempTopHypotenuse / hypotenuse * height;

    auto tempBottomHypotenuse = cornerRadius / std::tan(bottomAngle / 2.0f);
    auto tempBottomWidth = tempBottomHypotenuse / hypotenuse * (width / 2.0f);
    auto tempBottomHeight = tempBottomHypotenuse / hypotenuse * height;

    PointF topControlPoint = PointF(pathStartVertexX, pathStartVertexY);
    PointF leftControlPoint = PointF(pathStartVertexX - width / 2.0f, pathStartVertexY + height);
    PointF rightControlPoint = PointF(pathStartVertexX + width / 2.0f, pathStartVertexY + height);

    PointF trianglePoint1 = topControlPoint + OffsetF(-tempTopWidth, tempTopHeight);
    PointF trianglePoint2 = leftControlPoint + OffsetF(tempBottomWidth, -tempBottomHeight);
    PointF trianglePoint3 = leftControlPoint + OffsetF(tempBottomHypotenuse, 0.0f);
    PointF trianglePoint4 = rightControlPoint + OffsetF(-tempBottomHypotenuse, 0.0f);
    PointF trianglePoint5 = rightControlPoint + OffsetF(-tempBottomWidth, -tempBottomHeight);
    PointF trianglePoint6 = topControlPoint + OffsetF(tempTopWidth, tempTopHeight);

    path.MoveTo(trianglePoint1.GetX(), trianglePoint1.GetY());
    path.LineTo(trianglePoint2.GetX(), trianglePoint2.GetY());
    path.QuadTo(leftControlPoint.GetX(), leftControlPoint.GetY(), trianglePoint3.GetX(), trianglePoint3.GetY());
    path.LineTo(trianglePoint4.GetX(), trianglePoint4.GetY());
    path.QuadTo(rightControlPoint.GetX(), rightControlPoint.GetY(), trianglePoint5.GetX(), trianglePoint5.GetY());
    path.LineTo(trianglePoint6.GetX(), trianglePoint6.GetY());
    path.QuadTo(topControlPoint.GetX(), topControlPoint.GetY(), trianglePoint1.GetX(), trianglePoint1.GetY());
}
} // namespace OHOS::Ace::NG
