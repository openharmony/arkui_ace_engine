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

#include "core/components_ng/pattern/data_panel/data_panel_paint_method.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/rect.h"
#include "base/geometry/rrect.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {

// TODO move to theme
constexpr float START_COLOR_TRANSITION_EDGE = 30.0f;
constexpr float FIXED_WIDTH = 1.0f;
constexpr float HALF_CIRCLE = 180.0f;
constexpr float QUARTER_CIRCLE = 90.0f;
constexpr float DIAMETER_TO_THICKNESS_RATIO = 0.12;

} // namespace

CanvasDrawFunction DataPanelPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto dataPanel = weak.Upgrade();
        if (dataPanel) {
            dataPanel->Paint(canvas, paintWrapper);
        }
    };
    return paintFunc;
}

void DataPanelPaintMethod::Paint(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<DataPanelPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto type = paintProperty->GetDataPanelType();
    if (type.has_value() && type.value() == 1) {
        PaintLinearProgress(canvas, paintWrapper);
        return;
    }
    ArcData arcData;
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    arcData.center = Offset(frameSize.Width() / 2.0f, frameSize.Height() / 2.0f);
    arcData.radius = std::min(frameSize.Width(), frameSize.Height()) / 2.0f;
    auto theme = themeManager->GetTheme<DataPanelTheme>();
    auto colors = theme->GetColorsArray();
    auto defaultThickness = theme->GetThickness().ConvertToPx();
    if (defaultThickness >= arcData.radius) {
        arcData.thickness = arcData.radius * DIAMETER_TO_THICKNESS_RATIO;
    } else {
        arcData.thickness = defaultThickness;
    }
    arcData.wholeAngle = 360.0f;
    arcData.startAngle = 0.0f;
    auto dataValues = paintProperty->GetValues();
    std::vector<double> values = dataValues.value();
    PaintTrackBackground(canvas, arcData, Color::GRAY);
    double proportions = 1.0;
    auto max = paintProperty->GetMax();
    double maxValue = max.value();
    if (LessOrEqual(maxValue, 0.0)) {
        maxValue = 100.0;
    }
    double totalValue = 0.0;
    for (uint32_t i = 0; i < values.size(); i++) {
        totalValue += values[i];
    }
    if (GreatNotEqual(totalValue, maxValue)) {
        proportions = 100.0f / totalValue;
    } else {
        proportions = 100.0f / maxValue;
    }
    arcData.maxValue = maxValue;
    bool useEffect_ = false;
    auto effect_ = paintProperty->GetEffect();
    if (effect_.has_value()) {
        useEffect_ = effect_.value();
    }
    // TODO add closeEffct
    if (useEffect_ && GreatNotEqual(totalValue, 0.0)) {
    }

    totalValue = totalValue * proportions;
    for (int32_t i = static_cast<int32_t>(values.size()) - 1; i >= 0; i--) {
        arcData.startColor = colors[i].first;
        arcData.endColor = colors[i].second;
        arcData.progress = totalValue;
        PaintProgress(canvas, arcData, useEffect_, false, 0.0);
        totalValue -= values[i] * proportions;
    }
}

void DataPanelPaintMethod::PaintLinearProgress(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    auto offset = paintWrapper->GetContentOffset();
    auto totalWidth = frameSize.Width();
    auto paintProperty = DynamicCast<DataPanelPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto max = paintProperty->GetMax();
    auto spaceWidth = SystemProperties::Vp2Px(FIXED_WIDTH);
    auto segmentWidthSum = 0.0;
    auto values = paintProperty->GetValues();
    std::vector<double> data_values = values.value();
    for (uint32_t i = 0; i < data_values.size(); i++) {
        segmentWidthSum += data_values[i];
    }
    auto segmentSize = 0.0;
    if (segmentWidthSum == max.value()) {
        segmentSize = static_cast<double>(data_values.size() - 1);
    } else {
        segmentSize = static_cast<double>(data_values.size());
    }
    for (uint32_t i = 0; i < data_values.size(); i++) {
        if (NearEqual(data_values[i], 0.0)) {
            segmentSize -= 1;
        }
    }
    float scaleMaxValue = 0.0f;
    if (max.value() > 0) {
        scaleMaxValue = (totalWidth - segmentSize * spaceWidth) / max.value();
    }
    auto height = frameSize.Height();
    auto widthSegment = offset.GetX();
    auto container = Container::Current();
    auto pipelineContext = container->GetPipelineContext();
    auto themeManager = pipelineContext->GetThemeManager();
    auto theme = themeManager->GetTheme<DataPanelTheme>();
    auto colors = theme->GetColorsArray();
    PaintBackground(canvas, paintWrapper, totalWidth, height);

    for (uint32_t i = 0; i < data_values.size(); i++) {
        if (data_values[i] > 0) {
            auto segmentWidth = data_values[i];
            if (NearEqual(segmentWidth, 0.0)) {
                continue;
            }
            auto startColor = colors[i].first;
            auto endColor = colors[i].second;
            PaintColorSegment(
                canvas, paintWrapper, segmentWidth * scaleMaxValue, widthSegment, height, startColor, endColor);
            widthSegment += data_values[i] * scaleMaxValue;
            PaintSpace(canvas, paintWrapper, spaceWidth, widthSegment, height);
            widthSegment += spaceWidth;
        }
    }
}

void DataPanelPaintMethod::PaintBackground(
    RSCanvas& canvas, PaintWrapper* paintWrapper, float totalWidth, float height) const
{
    auto offset = paintWrapper->GetContentOffset();
    RSBrush brush;
    brush.SetColor(ToRSColor(Color::GRAY));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    RSRect rRect(offset.GetX(), offset.GetY(), totalWidth + offset.GetX(), height + offset.GetY());
    RSRoundRect rrRect(rRect, height, height);
    canvas.ClipRoundRect(rrRect, RSClipOp::INTERSECT);
    canvas.DrawRect(rRect);
    canvas.DetachBrush();
}

void DataPanelPaintMethod::PaintColorSegment(RSCanvas& canvas, PaintWrapper* paintWrapper, float segmentWidth,
    float xSegment, float height, const Color segmentStartColor, const Color segmentEndColor) const
{
    auto offset = paintWrapper->GetContentOffset();
    RSBrush brush;
    RSRect rect(xSegment, offset.GetY(), xSegment + segmentWidth, offset.GetY() + height);
    RSPoint segmentStartPoint;
    segmentStartPoint.SetX(rect.GetLeft());
    segmentStartPoint.SetY(rect.GetTop());
    RSPoint segmentEndPoint;
    segmentEndPoint.SetX(rect.GetRight());
    segmentEndPoint.SetY(rect.GetBottom());
    RSPoint segmentPoint[2] = { segmentStartPoint, segmentEndPoint };
    RSColor segmentColor[2] = { segmentStartColor.GetValue(), segmentEndColor.GetValue() };
    std::vector<float> pos { 0.0f, 1.0f };
    std::vector<RSColorQuad> colors { segmentStartColor.GetValue(), segmentEndColor.GetValue() };
    brush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(segmentStartPoint, segmentEndPoint, colors, pos, RSTileMode::CLAMP));
    canvas.AttachBrush(brush);
    canvas.DrawRect(rect);
    canvas.DetachBrush();
}

void DataPanelPaintMethod::PaintSpace(
    RSCanvas& canvas, PaintWrapper* paintWrapper, float spaceWidth, float xSpace, float height) const
{
    auto offset = paintWrapper->GetContentOffset();
    RSBrush brush;
    RSRect rect(xSpace, offset.GetY(), xSpace + spaceWidth, offset.GetY() + height);
    brush.SetColor(ToRSColor(Color::WHITE));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawRect(rect);
    canvas.DetachBrush();
}

void DataPanelPaintMethod::PaintTrackBackground(RSCanvas& canvas, ArcData arcData, const Color color) const
{
    RSPen backgroundTrackData;
    RSPath backgroundTrackPath;
    auto center = arcData.center;
    float thickness = arcData.thickness;
    float radius = arcData.radius;

    RSRect rect(center.GetX() - radius + thickness / 2, center.GetY() - radius + thickness / 2,
        center.GetX() + radius - thickness / 2, center.GetY() + radius - thickness / 2);

    backgroundTrackPath.AddArc(rect, 0.0, HALF_CIRCLE * 2);
    backgroundTrackData.SetColor(ToRSColor(color));
    backgroundTrackData.SetAntiAlias(true);
    backgroundTrackData.SetWidth(thickness);

    canvas.AttachPen(backgroundTrackData);
    canvas.DrawPath(backgroundTrackPath);
    canvas.DetachPen();
}

void DataPanelPaintMethod::PaintProgress(
    RSCanvas& canvas, ArcData arcData, bool useEffect, bool useAnimator, float percent) const
{
    float thickness = arcData.thickness;
    float radius = arcData.radius;
    float progress = arcData.progress;
    if (GreatNotEqual(progress, 100.0f)) {
        progress = 100.0f;
    }
    if (LessNotEqual(progress, 0.0f)) {
        progress = 0.0f;
    }
    if (NearEqual(progress, 0.0f)) {
        return;
    }
    Offset center = arcData.center;
    PointF centerPt = PointF(center.GetX(), center.GetY() - radius + thickness / 2);

    // for example whole circle is 100 which is divided into 100 piece 360 / 100 = 3.6
    float drawAngle = arcData.wholeAngle * 0.01 * progress;
    float startAngle = arcData.startAngle;
    std::vector<RSColorQuad> colors { arcData.startColor.GetValue(), arcData.endColor.GetValue() };
    std::vector<float> pos { 0.0f, 1.0f };
    RSPen gradientPaint;
    gradientPaint.SetWidth(thickness);
    gradientPaint.SetAntiAlias(true);
    RSPath path;
    RSRect rRect(center.GetX() - radius + thickness / 2, center.GetY() - radius + thickness / 2,
        center.GetX() + radius - thickness / 2, center.GetY() + radius - thickness / 2);
    path.AddArc(rRect, startAngle, drawAngle);

    RSBrush startCirclePaint;
    startCirclePaint.SetAntiAlias(true);
    startCirclePaint.SetColor(arcData.startColor.GetValue());

    RSBrush endCirclePaint;
    endCirclePaint.SetAntiAlias(true);
    endCirclePaint.SetColor(arcData.endColor.GetValue());

    if (progress < START_COLOR_TRANSITION_EDGE) {
        startCirclePaint.SetColor(
            Color::LineColorTransition(arcData.endColor, arcData.startColor, progress / START_COLOR_TRANSITION_EDGE)
                .GetValue());
        colors[0] =
            Color::LineColorTransition(arcData.endColor, arcData.startColor, progress / START_COLOR_TRANSITION_EDGE)
                .GetValue();
        gradientPaint.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
            ToRSPonit(PointF(center.GetX(), center.GetY())), colors, pos, RSTileMode::CLAMP, 0, drawAngle));
    } else {
        gradientPaint.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
            ToRSPonit(PointF(center.GetX(), center.GetY())), colors, pos, RSTileMode::CLAMP, 0, drawAngle));
    }

    canvas.Save();
    canvas.AttachBrush(startCirclePaint);
    RSRect edgeRect(center.GetX() - thickness / 2, center.GetY() - radius, center.GetX() + thickness / 2,
        center.GetY() - radius + thickness);
    canvas.DrawArc(edgeRect, QUARTER_CIRCLE, HALF_CIRCLE);
    canvas.DetachBrush();
    canvas.Restore();

    canvas.Save();
    canvas.Rotate(-QUARTER_CIRCLE, center.GetX(), center.GetY());
    gradientPaint.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
        ToRSPonit(PointF(center.GetX(), center.GetY())), colors, pos, RSTileMode::CLAMP, 0, drawAngle));
    canvas.AttachPen(gradientPaint);
    canvas.DrawPath(path);
    canvas.DetachPen();
    canvas.Restore();

    canvas.Save();
    canvas.Rotate(drawAngle, center.GetX(), center.GetY());
    canvas.AttachBrush(endCirclePaint);
    canvas.DrawArc(edgeRect, -QUARTER_CIRCLE, HALF_CIRCLE);
    canvas.DetachBrush();
    canvas.Restore();
}

} // namespace OHOS::Ace::NG
