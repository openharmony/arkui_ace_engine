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
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/data_panel/data_panel_modifer.h"
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
constexpr Color BACKGROUND_COLOR = Color(0x4C000000);
constexpr float SHADOW_BLUR_RADIUS = 5.0f;

} // namespace

DataPanelModifier::DataPanelModifier() : date_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0))
{
    AttachProperty(date_);
}

void PaintRainbowFilterMask(RSCanvas& canvas, double factor, ArcData arcData)
{
    float thickness = arcData.thickness;
    float radius = arcData.radius - SHADOW_BLUR_RADIUS;
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

    // 101 is Opacity 40%
    std::vector<RSColorQuad> colors { arcData.startColor.ChangeAlpha(101).GetValue(),
        arcData.endColor.ChangeAlpha(101).GetValue() };
    std::vector<float> pos { 0.0f, 1.0f };
    RSPen gradientPaint;
    gradientPaint.SetWidth(thickness);
    gradientPaint.SetAntiAlias(true);
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::NORMAL, 5.0f));
    gradientPaint.SetFilter(filter);
    RSPath path;
    RSRect rRect(center.GetX() - radius + thickness / 2, center.GetY() - radius + thickness / 2,
        center.GetX() + radius - thickness / 2, center.GetY() + radius - thickness / 2);
    path.AddArc(rRect, startAngle, drawAngle);

    RSBrush startCirclePaint;
    startCirclePaint.SetAntiAlias(true);
    startCirclePaint.SetColor(arcData.startColor.ChangeAlpha(101).GetValue());
    startCirclePaint.SetFilter(filter);

    RSBrush endCirclePaint;
    endCirclePaint.SetAntiAlias(true);
    endCirclePaint.SetColor(arcData.endColor.ChangeAlpha(101).GetValue());
    endCirclePaint.SetFilter(filter);

    if (progress < START_COLOR_TRANSITION_EDGE) {
        startCirclePaint.SetColor(Color::LineColorTransition(arcData.endColor.ChangeAlpha(101),
            arcData.startColor.ChangeAlpha(101), progress / START_COLOR_TRANSITION_EDGE)
                                      .GetValue());
        colors[0] = Color::LineColorTransition(arcData.endColor.ChangeAlpha(101), arcData.startColor.ChangeAlpha(101),
            progress / START_COLOR_TRANSITION_EDGE)
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

void DataPanelModifier::PaintCircle(DrawingContext& context, OffsetF offset, float date) const
{
    RSCanvas canvas = context.canvas;

    canvas.Save();
    canvas.Translate(offset.GetX(), offset.GetY());
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    ArcData arcData;
    arcData.center = Offset(context.width / 2.0f, context.height / 2.0f);
    arcData.radius = std::min(context.width, context.height) / 2.0f;
    auto theme = pipelineContext->GetTheme<DataPanelTheme>();
    auto colors = theme->GetColorsArray();
    auto defaultThickness = theme->GetThickness().ConvertToPx();
    if (defaultThickness >= arcData.radius) {
        arcData.thickness = arcData.radius * DIAMETER_TO_THICKNESS_RATIO;
    } else {
        arcData.thickness = defaultThickness;
    }
    arcData.wholeAngle = 360.0f;
    arcData.startAngle = 0.0f;
    PaintTrackBackground(canvas, arcData, BACKGROUND_COLOR);
    double proportions = 1.0;
    double maxValue = max_;
    if (LessOrEqual(maxValue, 0.0)) {
        maxValue = 100.0;
    }
    double totalValue = 0.0;
    float factor = 1.0;
    for (uint32_t i = 0; i < values_.size(); i++) {
        totalValue += values_[i];
    }
    if (GreatNotEqual(totalValue, maxValue)) {
        factor = maxValue / totalValue;
        proportions = 100.0f / totalValue;
    } else {
        proportions = 100.0f / maxValue;
    }
    totalValue = totalValue * proportions;
    for (int32_t i = static_cast<int32_t>(values_.size()) - 1; i >= 0; i--) {
        arcData.startColor = colors[i].first;
        arcData.endColor = colors[i].second;
        if (effect_ && GreatNotEqual(totalValue, 0.0)) {
            arcData.progress = totalValue * date;
            PaintRainbowFilterMask(canvas, factor * date, arcData);
        } else {
            arcData.progress = totalValue;
        }
        PaintProgress(canvas, arcData, effect_, false, 0.0);
        totalValue -= values_[i] * proportions;
    }
    canvas.Restore();
}

void DataPanelModifier::PaintLinearProgress(DrawingContext& context, OffsetF offset) const
{
    auto canvas = context.canvas;
    auto totalWidth = context.width;
    auto spaceWidth = SystemProperties::Vp2Px(FIXED_WIDTH);
    auto segmentWidthSum = 0.0;
    for (uint32_t i = 0; i < values_.size(); i++) {
        segmentWidthSum += values_[i];
    }
    auto segmentSize = 0.0;
    if (segmentWidthSum == max_) {
        segmentSize = static_cast<double>(values_.size() - 1);
    } else {
        segmentSize = static_cast<double>(values_.size());
    }
    for (uint32_t i = 0; i < values_.size(); i++) {
        if (NearEqual(values_[i], 0.0)) {
            segmentSize -= 1;
        }
    }
    float scaleMaxValue = 0.0f;
    if (max_ > 0) {
        scaleMaxValue = (totalWidth - segmentSize * spaceWidth) / max_;
    }
    auto height = context.height;
    auto widthSegment = offset.GetX();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto theme = pipelineContext->GetTheme<DataPanelTheme>();
    auto colors = theme->GetColorsArray();
    PaintBackground(canvas, offset, totalWidth, height);

    for (uint32_t i = 0; i < values_.size(); i++) {
        if (values_[i] > 0) {
            auto segmentWidth = values_[i];
            if (NearEqual(segmentWidth, 0.0)) {
                continue;
            }
            auto startColor = colors[i].first;
            auto endColor = colors[i].second;
            PaintColorSegment(canvas, offset, segmentWidth * scaleMaxValue, widthSegment, height, startColor, endColor);
            widthSegment += values_[i] * scaleMaxValue;
            PaintSpace(canvas, offset, spaceWidth, widthSegment, height);
            widthSegment += spaceWidth;
        }
    }
}

void DataPanelModifier::PaintBackground(RSCanvas& canvas, OffsetF offset, float totalWidth, float height) const
{
    RSBrush brush;
    brush.SetColor(ToRSColor(BACKGROUND_COLOR));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    RSRect rRect(offset.GetX(), offset.GetY(), totalWidth + offset.GetX(), height + offset.GetY());
    RSRoundRect rrRect(rRect, height, height);
    canvas.ClipRoundRect(rrRect, RSClipOp::INTERSECT);
    canvas.DrawRect(rRect);
    canvas.DetachBrush();
}

void DataPanelModifier::PaintColorSegment(RSCanvas& canvas, OffsetF offset, float segmentWidth, float xSegment,
    float height, const Color segmentStartColor, const Color segmentEndColor) const
{
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

void DataPanelModifier::PaintSpace(RSCanvas& canvas, OffsetF offset, float spaceWidth, float xSpace, float height) const
{
    RSBrush brush;
    RSRect rect(xSpace, offset.GetY(), xSpace + spaceWidth, offset.GetY() + height);
    brush.SetColor(ToRSColor(Color::WHITE));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawRect(rect);
    canvas.DetachBrush();
}

void DataPanelModifier::PaintTrackBackground(RSCanvas& canvas, ArcData arcData, const Color color) const
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

void DataPanelModifier::PaintProgress(
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
