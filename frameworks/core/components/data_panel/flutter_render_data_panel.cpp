/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/data_panel/flutter_render_data_panel.h"

#include "flutter/lib/ui/ui_dart_state.h"
#include "third_party/skia/include/core/SkMaskFilter.h"
#include "third_party/skia/include/core/SkShader.h"
#include "third_party/skia/include/effects/Sk1DPathEffect.h"
#include "third_party/skia/include/effects/SkDashPathEffect.h"
#include "third_party/skia/include/effects/SkGradientShader.h"

namespace OHOS::Ace {
namespace {

constexpr double START_COLOR_TRANSITION_EDGE = 30.0;
constexpr double HALF_CIRCLE = 180.0;
constexpr double QUARTER_CIRCLE = 90.0;
constexpr double PRECISION_CORRECTION = 0.5;
constexpr double SCAN_DEGREE = 30;
constexpr int32_t CIRCLE_NUMBER = 50;
constexpr float SHADOW_BLUR_RADIUS = 5.0f;
constexpr double DIAMETER_TO_THICKNESS_RATIO = 0.12;

} // namespace

void PaintTrackBackground(
    const ScopedCanvas& canvas, const Offset& center, double thickness, const Color& color, double diameter)
{
    SkPaint backgroundTrackData;
    SkPath backgroundTrackPath;

    SkRect rect = SkRect::MakeXYWH(center.GetX() - diameter / 2 + thickness / 2,
        center.GetY() - diameter / 2 + thickness / 2, diameter - thickness, diameter - thickness);
    backgroundTrackPath.addArc(rect, 0.0, HALF_CIRCLE * 2);
    backgroundTrackData.setStyle(SkPaint::kStroke_Style);
    backgroundTrackData.setStrokeWidth(thickness);
    backgroundTrackData.setAntiAlias(true);
    backgroundTrackData.setColor(color.GetValue());

    canvas->canvas()->drawPath(backgroundTrackPath, backgroundTrackData);
}

sk_sp<SkShader> BlendSkShader(SkScalar cx, SkScalar cy, const SkColor colors[], const SkScalar pos[], int colorCount,
    SkScalar startAngle, SkScalar drawAngle, const SkMatrix* localMatrix, bool useAnimator = false,
    bool useEffect = false)
{
    // the skia interface is more than 5 params.
    const Color HIGHLIGHT = Color::FromString("#55ffffff");
    const Color SHADOW = Color::FromString("#00ffffff");
    SkColor scanColors[3] = { SHADOW.GetValue(), HIGHLIGHT.GetValue(), SHADOW.GetValue() };
    SkScalar scanPos[3] = { 0, 0.80, 1 };
    sk_sp<SkShader> scanShader;
    sk_sp<SkShader> backgroundShader;
    sk_sp<SkShader> blendShader;

    double scanStartDegree = 0.0;
    double scanEndDegree = drawAngle;
    if (startAngle < SCAN_DEGREE) {
        scanStartDegree = 0.0;
        scanEndDegree = startAngle;
    } else {
        scanStartDegree = startAngle - SCAN_DEGREE;
        scanEndDegree = startAngle;
    }
    if (drawAngle < scanEndDegree + 0.1 * drawAngle) {
        scanColors[1] =
            HIGHLIGHT.ChangeAlpha(((drawAngle - scanEndDegree) / (0.1 * drawAngle)) * HIGHLIGHT.GetAlpha()).GetValue();
    }
#ifdef USE_SYSTEM_SKIA
    backgroundShader =
        SkGradientShader::MakeSweep(cx, cy, colors, pos, 2, SkShader::kDecal_TileMode, 0.0, drawAngle, 0, nullptr);
    scanShader = SkGradientShader::MakeSweep(
        cx, cy, scanColors, scanPos, 3, SkShader::kDecal_TileMode, scanStartDegree, scanEndDegree, 0, nullptr);
    if (useAnimator) {
        blendShader = SkShader::MakeCompose(backgroundShader, scanShader, SkBlendMode::kSrcOver);
    } else {
        blendShader = backgroundShader;
    }
#else
    backgroundShader =
        SkGradientShader::MakeSweep(cx, cy, colors, pos, 2, SkTileMode::kDecal, 0.0, drawAngle, 0, nullptr);
    scanShader = SkGradientShader::MakeSweep(
        cx, cy, scanColors, scanPos, 3, SkTileMode::kDecal, scanStartDegree, scanEndDegree, 0, nullptr);
    if (useAnimator) {
        blendShader = SkShaders::Blend(SkBlendMode::kSrcOver, backgroundShader, scanShader);
    } else {
        blendShader = backgroundShader;
    }
#endif
    return blendShader;
}

void PaintProgress(
    ScopedCanvas& canvas, ArcData arcData, bool useEffect = false, bool useAnimator = false, double percent = 0.0)
{
    double thickness = arcData.thickness;
    double radius = arcData.radius;
    double progress = arcData.progress;
    if (GreatNotEqual(progress, 100.0)) {
        progress = 100.0;
    }
    if (LessNotEqual(progress, 0.0)) {
        progress = 0.0;
    }
    Offset center = arcData.center;
    // for example whole circle is 100 which is divided into 100 piece 360 / 100 = 3.6
    double drawAngle = arcData.wholeAngle * 0.01 * progress;
    double startAngle = arcData.startAngle;

    if (useEffect) {
        radius = radius - SHADOW_BLUR_RADIUS;
    }
    SkPath botPath;
    SkRect rect = SkRect::MakeXYWH(center.GetX() - radius + thickness / 2, center.GetY() - radius + thickness / 2,
        radius * 2 - thickness, radius * 2 - thickness);
    botPath.addArc(rect, 0.0, drawAngle);
    SkColor colors[2] = { arcData.startColor.GetValue(), arcData.endColor.GetValue() };
    SkScalar pos[2] = { 0.0, 1.0 };
    SkPaint gradientPaint;
    gradientPaint.setStyle(SkPaint::kStroke_Style);
    gradientPaint.setStrokeWidth(thickness);
    gradientPaint.setAntiAlias(true);
    if (NearEqual(progress, 0.0)) {
        return;
    }
    SkPaint startCirclePaint;
    startCirclePaint.setStyle(SkPaint::kFill_Style);
    startCirclePaint.setAntiAlias(true);
    startCirclePaint.setColor(arcData.startColor.GetValue());

    SkPaint endCirclePaint;
    endCirclePaint.setStyle(SkPaint::kFill_Style);
    endCirclePaint.setAntiAlias(true);
    endCirclePaint.setColor(arcData.endColor.GetValue());
    // this part is used to draw the circle edge
    if (useEffect) {
        gradientPaint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, SHADOW_BLUR_RADIUS));
        startCirclePaint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, SHADOW_BLUR_RADIUS));
        endCirclePaint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, SHADOW_BLUR_RADIUS));
    }
    canvas->canvas()->save();

    if (progress > 50) {
        // this component contains three parts one edge circle, one half circle and a path region.
        canvas->canvas()->save();
        canvas->canvas()->rotate(startAngle, center.GetX(), center.GetY());
        canvas->canvas()->drawCircle(
            center.GetX(), center.GetY() - radius + thickness / 2, thickness / 2, startCirclePaint);
        canvas->canvas()->restore();

        canvas->canvas()->save();

        gradientPaint.setShader(BlendSkShader(center.GetX(), center.GetY(), colors, pos, 2, percent * drawAngle,
            drawAngle, nullptr, useAnimator, useEffect));
        canvas->canvas()->rotate(startAngle - QUARTER_CIRCLE, center.GetX(), center.GetY());
        canvas->canvas()->drawPath(botPath, gradientPaint);
        canvas->canvas()->restore();

        canvas->canvas()->save();
        canvas->canvas()->rotate(drawAngle + startAngle, center.GetX(), center.GetY());
        canvas->canvas()->drawCircle(
            center.GetX(), center.GetY() - radius + thickness / 2, thickness / 2, endCirclePaint);
        canvas->canvas()->restore();
    } else {
        // this component contains three parts two edge circle and a path region.
        if (progress < START_COLOR_TRANSITION_EDGE) {
            startCirclePaint.setColor(Color::LineColorTransition(
                arcData.endColor, arcData.startColor, progress / START_COLOR_TRANSITION_EDGE).GetValue());
        } else {
            startCirclePaint.setColor(arcData.startColor.GetValue());
        }
        // draw start edge circle
        canvas->canvas()->save();
        canvas->canvas()->rotate(startAngle, center.GetX(), center.GetY());
        canvas->canvas()->drawCircle(
            center.GetX(), center.GetY() - radius + thickness / 2, thickness / 2, startCirclePaint);
        canvas->canvas()->restore();

        // draw end edge circle
        canvas->canvas()->save();
        canvas->canvas()->rotate(startAngle + drawAngle - PRECISION_CORRECTION, center.GetX(), center.GetY());
        SkRect endOval = SkRect::MakeXYWH(center.GetX() - thickness / 2, center.GetY() - radius, thickness, thickness);
        canvas->canvas()->drawArc(endOval, 3 * QUARTER_CIRCLE, HALF_CIRCLE, true, endCirclePaint);
        canvas->canvas()->restore();

        // draw the region between start and end.
        canvas->canvas()->save();
        canvas->canvas()->rotate(startAngle - QUARTER_CIRCLE, center.GetX(), center.GetY());
        if (progress < START_COLOR_TRANSITION_EDGE) {
            colors[0] = Color::LineColorTransition(
                arcData.endColor, arcData.startColor, progress / START_COLOR_TRANSITION_EDGE).GetValue();
            gradientPaint.setShader(BlendSkShader(center.GetX(), center.GetY(), colors, pos, 2, percent * drawAngle,
                drawAngle, nullptr, useAnimator, useEffect));
        } else {
            gradientPaint.setShader(BlendSkShader(center.GetX(), center.GetY(), colors, pos, 2, percent * drawAngle,
                drawAngle, nullptr, useAnimator, useEffect));
        }
        canvas->canvas()->drawPath(botPath, gradientPaint);
        canvas->canvas()->restore();
    }
    canvas->canvas()->restore();
}

void PaintProgressFilterMask(ScopedCanvas& canvas, ArcData arcData)
{
    if (LessOrEqual(arcData.progress, 0.0)) {
        return;
    }
    if (GreatNotEqual(arcData.progress, 100.0)) {
        arcData.progress = 100.0;
    }
    double thickness = arcData.thickness;
    double radius = arcData.radius - SHADOW_BLUR_RADIUS;
    Offset center = arcData.center;
    SkPaint filterPaint;
    filterPaint.setAntiAlias(true);
    filterPaint.setStrokeCap(SkPaint::kButt_Cap);
    filterPaint.setStrokeWidth(thickness);
    filterPaint.setStyle(SkPaint::kStroke_Style);
    filterPaint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, SHADOW_BLUR_RADIUS));
    SkRect rect = SkRect::MakeXYWH(center.GetX() - radius + thickness / 2, center.GetY() - radius + thickness / 2,
        radius * 2 - thickness, radius * 2 - thickness);
    double startAngle = arcData.startAngle;

    // paint start circle
    SkPaint startCirclePaint;
    startCirclePaint.setStyle(SkPaint::kStrokeAndFill_Style);
    startCirclePaint.setAntiAlias(true);
    startCirclePaint.setColor(arcData.startColor.ChangeAlpha(101).GetValue());
    startCirclePaint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, SHADOW_BLUR_RADIUS));
    SkPath startCircleArch;
    SkRect startCircleArchRect =
        SkRect::MakeXYWH(center.GetX() - thickness / 2, center.GetY() - radius, thickness, thickness);
    canvas->canvas()->drawCircle(
        center.GetX(), center.GetY() - radius + thickness / 2, thickness / 2, startCirclePaint);
    canvas->canvas()->drawPath(startCircleArch, startCirclePaint);

    // paint path
    canvas->canvas()->save();
    canvas->canvas()->rotate(-QUARTER_CIRCLE + 1, center.GetX(), center.GetY());
    double sweepAngle = arcData.progress * 0.01 * arcData.wholeAngle;
    SkPath rainbowFilterPath;
    rainbowFilterPath.addArc(rect, startAngle, sweepAngle);
    // 101 is Opacity 40%
    SkColor colors[2] = { arcData.startColor.ChangeAlpha(101).GetValue(),
        arcData.endColor.ChangeAlpha(101).GetValue() };
    SkScalar pos[2] = { 0.0, 1.0 };
    // kClamp_TileMode
#ifdef USE_SYSTEM_SKIA
    filterPaint.setShader(SkGradientShader::MakeSweep(center.GetX(), center.GetY(), colors, pos, 2,
        SkShader::kDecal_TileMode, startAngle, startAngle + sweepAngle, 0, nullptr));
#else
    filterPaint.setShader(SkGradientShader::MakeSweep(center.GetX(), center.GetY(), colors, pos, 2, SkTileMode::kDecal,
        startAngle, startAngle + sweepAngle, 0, nullptr));
#endif
    canvas->canvas()->drawPath(rainbowFilterPath, filterPaint);
    startAngle += sweepAngle;

    // paint end circle
    canvas->canvas()->save();
    SkPaint endCirclePaint;
    endCirclePaint.setStyle(SkPaint::kStrokeAndFill_Style);
    endCirclePaint.setAntiAlias(true);
    endCirclePaint.setColor(arcData.endColor.ChangeAlpha(101).GetValue());
    endCirclePaint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, SHADOW_BLUR_RADIUS));
    SkPath endCircleArch;
    endCircleArch.addArc(startCircleArchRect, 90.0, -180.0);
    canvas->canvas()->rotate(startAngle + QUARTER_CIRCLE, center.GetX(), center.GetY());
    canvas->canvas()->drawPath(endCircleArch, endCirclePaint);
    canvas->canvas()->restore();

    canvas->canvas()->restore();
}

void PaintFilterMask(ScopedCanvas& canvas, ArcData arcData)
{
    PaintProgressFilterMask(canvas, arcData);
}

void PaintRainbowFilterMask(ScopedCanvas& canvas, double factor, const std::vector<Segment>& segments, ArcData arcData)
{
    if (segments.empty()) {
        return;
    }
    double thickness = arcData.thickness;
    double radius = arcData.radius - SHADOW_BLUR_RADIUS;
    Offset center = arcData.center;
    SkPaint filterPaint;
    filterPaint.setAntiAlias(true);
    filterPaint.setStrokeCap(SkPaint::kButt_Cap);
    filterPaint.setStrokeWidth(thickness);
    filterPaint.setStyle(SkPaint::kStroke_Style);
    filterPaint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, SHADOW_BLUR_RADIUS));
    SkRect rect = SkRect::MakeXYWH(center.GetX() - radius + thickness / 2, center.GetY() - radius + thickness / 2,
        radius * 2 - thickness, radius * 2 - thickness);
    double startAngle = arcData.startAngle;

    canvas->canvas()->save();
    canvas->canvas()->rotate(startAngle, center.GetX(), center.GetY());
    SkPaint startCirclePaint;
    startCirclePaint.setStyle(SkPaint::kStrokeAndFill_Style);
    startCirclePaint.setAntiAlias(true);
    startCirclePaint.setColor(segments[0].GetStartColor().ChangeAlpha(101).GetValue());
    startCirclePaint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, SHADOW_BLUR_RADIUS));
    SkPath startCircleArch;
    SkRect startCircleArchRect =
        SkRect::MakeXYWH(center.GetX() - thickness / 2, center.GetY() - radius, thickness, thickness);
    startCircleArch.addArc(startCircleArchRect, 90.0, 180.0);
    canvas->canvas()->drawPath(startCircleArch, startCirclePaint);
    canvas->canvas()->restore();

    canvas->canvas()->save();
    canvas->canvas()->rotate(-QUARTER_CIRCLE + 1, center.GetX(), center.GetY());
    for (const auto& segment : segments) {
        double sweepAngle = segment.GetValue() * 0.01 * arcData.wholeAngle * factor;
        if (GreatNotEqual(sweepAngle, arcData.wholeAngle)) {
            sweepAngle = arcData.wholeAngle;
        }
        SkPath rainbowFilterPath;
        rainbowFilterPath.addArc(rect, startAngle, sweepAngle);
        SkColor colors[2] = { segment.GetStartColor().ChangeAlpha(101).GetValue(),
            segment.GetEndColor().ChangeAlpha(101).GetValue() };
        SkScalar pos[2] = { 0.0, 1.0 };
#ifdef USE_SYSTEM_SKIA
        filterPaint.setShader(SkGradientShader::MakeSweep(center.GetX(), center.GetY(), colors, pos, 2,
            SkShader::kClamp_TileMode, startAngle, startAngle + sweepAngle, 0, nullptr));
#else
        filterPaint.setShader(SkGradientShader::MakeSweep(center.GetX(), center.GetY(), colors, pos, 2,
            SkTileMode::kClamp, startAngle, startAngle + sweepAngle, 0, nullptr));
#endif
        canvas->canvas()->drawPath(rainbowFilterPath, filterPaint);
        startAngle += sweepAngle;
    }
    canvas->canvas()->save();
    SkPaint endCirclePaint;
    endCirclePaint.setStyle(SkPaint::kStrokeAndFill_Style);
    endCirclePaint.setAntiAlias(true);
    endCirclePaint.setColor(segments[segments.size() - 1].GetEndColor().ChangeAlpha(101).GetValue());
    endCirclePaint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, SHADOW_BLUR_RADIUS));
    SkPath endCircleArch;
    endCircleArch.addArc(startCircleArchRect, 90.0, -180.0);
    canvas->canvas()->rotate(startAngle + QUARTER_CIRCLE, center.GetX(), center.GetY());
    canvas->canvas()->drawPath(endCircleArch, endCirclePaint);
    canvas->canvas()->restore();

    canvas->canvas()->restore();
}

void FlutterRenderProgressDataPanel::Paint(RenderContext& context, const Offset& offset)
{
    if (type_ == ChartType::LOADING) {
        if (useEffect_) {
            PaintEffectedLoadingProgress(context, offset);
        } else {
            PaintEffectedLoadingProgress(context, offset);
        }
    } else {
        PaintRingProgress(context, offset);
    }
}

void FlutterRenderProgressDataPanel::PaintEffectedLoadingProgress(RenderContext& context, const Offset& offset)
{
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        return;
    }
    const Offset& center = offset + Offset(GetLayoutSize().Width() / 2, GetLayoutSize().Height() / 2);
    double diameter = std::min(GetLayoutSize().Width(), GetLayoutSize().Height());
    double thickness = NormalizeToPx(thickness_);
    if (autoScale_) {
        thickness = diameter * DIAMETER_TO_THICKNESS_RATIO;
    }
    if (LessOrEqual(diameter, thickness)) {
        LOGE("Loading diameter error: %{public}lf thickness: %{public}lf. thickness is reduce to 1/10 of the diameter",
            diameter, thickness);
        thickness = diameter * 0.1;
    }
    PaintTrackBackground(canvas, center, thickness, backgroundTrack_, diameter);

    SkPaint circlePaint;
    circlePaint.setStyle(SkPaint::kFill_Style);
    circlePaint.setAntiAlias(true);
    double angle = sweepDegree_;
    double dx = 0.0;
    double dy = 0.0;
    double radius = diameter / 2 - thickness / 2;
    double animateAngle = rotateAngle_;
    if (animateAngle - angle < 0.0) {
        angle = animateAngle;
    }
    canvas->canvas()->save();
    canvas->canvas()->rotate(animateAngle, center.GetX(), center.GetY()); // animate
    for (int i = 0; i < CIRCLE_NUMBER; i++) {
        dx = radius * std::sin((CIRCLE_NUMBER - i) * (angle / CIRCLE_NUMBER) * M_PI / 180.0);
        dy = radius * std::cos((CIRCLE_NUMBER - i) * (angle / CIRCLE_NUMBER) * M_PI / 180.0);
        circlePaint.setColor(
            Color::LineColorTransition(GetStartColor(), GetEndColor(), static_cast<double>(i) / CIRCLE_NUMBER)
                .GetValue());
        canvas->canvas()->drawCircle(center.GetX() - dx, center.GetY() - dy, thickness / 2, circlePaint);
    }
    canvas->canvas()->restore();
}

void FlutterRenderProgressDataPanel::PaintLoadingProgress(RenderContext& context, const Offset& offset)
{
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        return;
    }
    const Offset& center = offset + Offset(GetLayoutSize().Width() / 2, GetLayoutSize().Height() / 2);
    double diameter = std::min(GetLayoutSize().Width(), GetLayoutSize().Height());
    double thickness = NormalizeToPx(thickness_);
    if (autoScale_) {
        thickness = diameter * DIAMETER_TO_THICKNESS_RATIO;
    }
    if (LessOrEqual(diameter, thickness)) {
        LOGE("Loading diameter error: %{public}lf thickness: %{public}lf. thickness is reduce to 1/10 of the diameter",
            diameter, thickness);
        thickness = diameter * 0.1;
    }
    double animateAngle = rotateAngle_ - sweepDegree_;

    SkPaint botPaint;
    SkPath botPath;
    SkRect rect = SkRect::MakeXYWH(center.GetX() - diameter / 2 + thickness / 2,
        center.GetY() - diameter / 2 + thickness / 2, diameter - thickness, diameter - thickness);
    botPath.addArc(rect, 0, sweepDegree_);

    SkColor colors[2] = { GetStartColor().GetValue(), GetEndColor().GetValue() };
    SkScalar pos[2] = { 0.0, 1.0 };
    canvas->canvas()->rotate(-QUARTER_CIRCLE, center.GetX(), center.GetY());
    botPaint.setStrokeCap(SkPaint::kRound_Cap);
    botPaint.setStyle(SkPaint::kStroke_Style);
    botPaint.setStrokeWidth(thickness);
    botPaint.setAntiAlias(true);

#ifdef USE_SYSTEM_SKIA
    botPaint.setShader(SkGradientShader::MakeSweep(center.GetX(), center.GetY(), colors, pos, 2,
        SkShader::kDecal_TileMode, 0.0,
        sweepDegree_ + 2 * PRECISION_CORRECTION + 180.0 / M_PI * std::asin(thickness / ((diameter) / 2)), 0, nullptr));
#else
    botPaint.setShader(SkGradientShader::MakeSweep(center.GetX(), center.GetY(), colors, pos, 2, SkTileMode::kDecal,
        0.0, sweepDegree_ + 2 * PRECISION_CORRECTION + 180.0 / M_PI * std::asin(thickness / ((diameter) / 2)), 0,
        nullptr));
#endif
    canvas->canvas()->save();
    PaintTrackBackground(canvas, center, thickness, backgroundTrack_, diameter);
    canvas->canvas()->rotate(animateAngle, center.GetX(), center.GetY()); // animate
    canvas->canvas()->drawPath(botPath, botPaint);
    canvas->canvas()->restore();
}

void FlutterRenderProgressDataPanel::PaintRingProgress(RenderContext& context, const Offset& offset)
{
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        return;
    }
    // whole circle is divided into 100 piece 360 / 100 = 3.6
    ArcData arcData;
    arcData.progress = GetProgress();
    arcData.center = offset + Offset(GetLayoutSize().Width() / 2, GetLayoutSize().Height() / 2);
    arcData.thickness = NormalizeToPx(thickness_);
    arcData.radius = std::min(GetLayoutSize().Width(), GetLayoutSize().Height()) / 2;
    if (autoScale_) {
        arcData.thickness = arcData.radius * 2 * DIAMETER_TO_THICKNESS_RATIO;
    }
    arcData.startColor = GetStartColor();
    arcData.endColor = GetEndColor();
    PaintTrackBackground(canvas, arcData.center, arcData.thickness, backgroundTrack_, arcData.radius * 2);
    if (useEffect_) {
        PaintFilterMask(canvas, arcData);
    }
    PaintProgress(canvas, arcData, false, useEffect_, percent_);
}

RefPtr<RenderNode> RenderProgressDataPanel::Create()
{
    return AceType::MakeRefPtr<FlutterRenderProgressDataPanel>();
}

RefPtr<RenderNode> RenderPercentageDataPanel::Create()
{
    return AceType::MakeRefPtr<FlutterRenderPercentageDataPanel>();
}

void FlutterRenderPercentageDataPanel::Paint(RenderContext& context, const Offset& offset)
{
    ArcData arcData;
    arcData.center = offset + Offset(GetLayoutSize().Width() / 2, GetLayoutSize().Height() / 2);
    arcData.thickness = NormalizeToPx(thickness_);
    arcData.radius = std::min(GetLayoutSize().Width(), GetLayoutSize().Height()) / 2;
    if (autoScale_) {
        arcData.thickness = arcData.radius * 2 * DIAMETER_TO_THICKNESS_RATIO;
    }
    arcData.wholeAngle = GetSweepDegree();
    arcData.startAngle = GetStartDegree();
    double totalValue = GetTotalValue();
    auto segments = GetSegments();
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        return;
    }
    PaintTrackBackground(canvas, arcData.center, arcData.thickness, backgroundTrack_, arcData.radius * 2);
    double factor = 1.0;
    if (GreatNotEqual(totalValue, 100.0)) {
        factor = 100.0 / totalValue;
    }
    if (useEffect_ && GreatNotEqual(totalValue, 0.0)) {
        PaintRainbowFilterMask(canvas, factor * animationPercent_, segments, arcData);
    }
    totalValue = totalValue * factor;
    for (int i = segments.size() - 1; i >= 0; i--) {
        const auto& segment = segments[i];
        arcData.startColor = segment.GetStartColor();
        arcData.endColor = segment.GetEndColor();
        arcData.progress = totalValue * animationPercent_;
        PaintProgress(canvas, arcData);
        totalValue -= segment.GetValue() * factor;
    }
}

} // namespace OHOS::Ace