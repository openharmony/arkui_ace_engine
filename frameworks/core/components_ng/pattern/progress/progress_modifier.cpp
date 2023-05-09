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

#include "core/components_ng/pattern/progress/progress_modifier.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t DEFAULT_BORDER_COLOR = 0x33007dff;
constexpr int32_t INT32_TWO = 2;
constexpr int32_t ANGLE_90 = 90;
constexpr int32_t ANGLE_180 = 180;
constexpr int32_t ANGLE_270 = 270;
constexpr int32_t ANGLE_360 = 360;
constexpr float DEFAULT_MAX_VALUE = 100.0f;
constexpr float DEFAULT_SCALE_WIDTH = 10.0f;
constexpr int32_t DEFAULT_SCALE_COUNT = 100;
constexpr double DEFAULT_CAPSULE_BORDER_WIDTH = 0.0;
constexpr float FLOAT_ZERO_FIVE = 0.5f;
constexpr float FLOAT_TWO_ZERO = 2.0f;
constexpr float SWEEPING_MOTION_RESPONSE = 1.62f;
constexpr float SWEEPING_MOTION_DAMPING_RATIO = 0.98f;
constexpr Dimension SWEEP_WIDTH = 80.0_vp;
constexpr float RING_SHADOW_OFFSET_X = 5.0f;
constexpr float RING_SHADOW_OFFSET_Y = 5.0f;
constexpr float RING_SHADOW_BLUR_RADIUS_MIN = 5.0f;
} // namespace
ProgressModifier::ProgressModifier()
    : strokeWidth_(AceType::MakeRefPtr<AnimatablePropertyFloat>(FLOAT_TWO_ZERO)),
      color_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::BLUE)),
      bgColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::GRAY)),
      borderColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(DEFAULT_BORDER_COLOR))),
      capsuleDate_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0f)),
      ringProgressColors_(AceType::MakeRefPtr<AnimatablePropertyVectorColor>(GradientArithmetic())),
      value_(AceType::MakeRefPtr<PropertyFloat>(0.0f)),
      offset_(AceType::MakeRefPtr<PropertyOffsetF>(OffsetF())),
      contentSize_(AceType::MakeRefPtr<PropertySizeF>(SizeF())),
      maxValue_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_MAX_VALUE)),
      scaleWidth_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_SCALE_WIDTH)),
      scaleCount_(AceType::MakeRefPtr<PropertyInt>(DEFAULT_SCALE_COUNT)),
      progressType_(AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(ProgressType::LINEAR))),
      capsuleBorderWidth_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_CAPSULE_BORDER_WIDTH)),
      sweepEffect_(AceType::MakeRefPtr<PropertyBool>(false)),
      paintShadow_(AceType::MakeRefPtr<PropertyBool>(false)),
      progressStatus_(AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(ProgressStatus::PROGRESSING)))
{
    AttachProperty(strokeWidth_);
    AttachProperty(color_);
    AttachProperty(bgColor_);
    AttachProperty(borderColor_);
    AttachProperty(maxValue_);
    AttachProperty(value_);
    AttachProperty(scaleWidth_);
    AttachProperty(scaleCount_);
    AttachProperty(progressType_);
    AttachProperty(capsuleBorderWidth_);
    AttachProperty(sweepEffect_);
    AttachProperty(capsuleDate_);
    AttachProperty(ringProgressColors_);
    AttachProperty(paintShadow_);
    AttachProperty(progressStatus_);
}

void ProgressModifier::onDraw(DrawingContext& context)
{
    ContentDrawWithFunction(context);
}

void ProgressModifier::SetStrokeWidth(float width)
{
    CHECK_NULL_VOID(strokeWidth_);
    strokeWidth_->Set(width);
}

void ProgressModifier::SetColor(LinearColor color)
{
    CHECK_NULL_VOID(color_);
    color_->Set(color);
}

void ProgressModifier::SetBackgroundColor(LinearColor color)
{
    CHECK_NULL_VOID(bgColor_);
    bgColor_->Set(color);
}

void ProgressModifier::SetBorderColor(LinearColor color)
{
    CHECK_NULL_VOID(borderColor_);
    borderColor_->Set(color);
}

void ProgressModifier::SetProgressType(ProgressType type)
{
    CHECK_NULL_VOID(progressType_);
    progressType_->Set(static_cast<int32_t>(type));
}

void ProgressModifier::StartLightSweepAnimation(ProgressType type, float value)
{
    switch (type) {
        case ProgressType::RING:
            break;
        case ProgressType::CAPSULE:
            StartCapsuleProgressLightSweep(value);
            break;
        default:
            break;
    }
}

void ProgressModifier::StartCapsuleProgressLightSweep(float value)
{
    float curLength = 0.0f;
    auto contentSize = contentSize_->Get();
    if (contentSize.Width() >= contentSize.Height()) {
        curLength = (value / maxValue_->Get()) * contentSize_->Get().Width() + SWEEP_WIDTH.ConvertToPx();
    } else {
        curLength = (value / maxValue_->Get()) * contentSize_->Get().Height() + SWEEP_WIDTH.ConvertToPx();
    }
    
    if (!isSweeping_ && sweepEffect_->Get() && isVisible_) {
        StartCapsuleProgressLightSweepImpl(curLength);
    } else if (!sweepEffect_->Get() || !isVisible_) {
        isSweeping_ = false;
        AnimationOption option = AnimationOption();
        auto curve = AceType::MakeRefPtr<LinearCurve>();
        option.SetCurve(curve);
        option.SetDuration(0);
        option.SetIteration(-1);
        AnimationUtils::Animate(option, [&]() { capsuleDate_->Set(0.0f); });
    } else {
        capsuleDate_->Set(curLength);
        if (!NearEqual(sweepingDateBackup_, curLength)) {
            sweepingDateUpdated_ = true;
        }
    }
    sweepingDateBackup_ = curLength;
}

void ProgressModifier::StartCapsuleProgressLightSweepImpl(float curLength)
{
    isSweeping_ = true;
    capsuleDate_->Set(0.0f);
    AnimationOption option = AnimationOption();
    auto motion =
        AceType::MakeRefPtr<ResponsiveSpringMotion>(SWEEPING_MOTION_RESPONSE, SWEEPING_MOTION_DAMPING_RATIO);
    option.SetCurve(motion);
    option.SetIteration(-1);

    AnimationUtils::Animate(option,
        [curLength, id = Container::CurrentId(), weak = WeakClaim(this)]() {
            ContainerScope scope(id);
            auto modifier = weak.Upgrade();
            CHECK_NULL_VOID(modifier);
            modifier->capsuleDate_->Set(curLength);
        },
        [id = Container::CurrentId(), weak = WeakClaim(this)]() {
            ContainerScope scope(id);
            auto context = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            taskExecutor->PostTask(
                [weak, id]() {
                    ContainerScope scope(id);
                    auto modifier = weak.Upgrade();
                    CHECK_NULL_VOID_NOLOG(modifier);
                    if (modifier->sweepEffect_->Get() && modifier->isVisible_) {
                        if (modifier->sweepingDateUpdated_) {
                            modifier->StartCapsuleProgressLightSweepImpl(modifier->sweepingDateBackup_);
                        }
                        modifier->sweepingDateUpdated_ = false;
                    }
                },
                TaskExecutor::TaskType::UI);
        },
        [id = Container::CurrentId(), weak = WeakClaim(this)]() {
            ContainerScope scope(id);
            auto context = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            taskExecutor->PostTask(
                [weak, id]() {
                    ContainerScope scope(id);
                    auto modifier = weak.Upgrade();
                    CHECK_NULL_VOID_NOLOG(modifier);
                    if (modifier->sweepingDateUpdated_ || !modifier->isVisible_) {
                        if (modifier->isSweeping_) {
                            modifier->isSweeping_ = false;
                            AnimationOption option = AnimationOption();
                            auto curve = AceType::MakeRefPtr<LinearCurve>();
                            option.SetCurve(curve);
                            option.SetDuration(0);
                            option.SetIteration(1);
                            AnimationUtils::Animate(option, [modifier]() { modifier->capsuleDate_->Set(0.0f); });
                        }
                    }
                },
                TaskExecutor::TaskType::UI);
        });
}

void ProgressModifier::SetRingProgressColor(const Gradient& color)
{
    CHECK_NULL_VOID(ringProgressColors_);
    ringProgressColors_->Set(GradientArithmetic(color));
}

void ProgressModifier::SetPaintShadow(bool paintShadow)
{
    CHECK_NULL_VOID(paintShadow_);
    paintShadow_->Set(paintShadow);
}

void ProgressModifier::SetProgressStatus(ProgressStatus status)
{
    CHECK_NULL_VOID(progressStatus_);
    progressStatus_->Set(static_cast<int32_t>(status));
}

void ProgressModifier::SetMaxValue(float value)
{
    CHECK_NULL_VOID(maxValue_);
    maxValue_->Set(value);
}

void ProgressModifier::SetValue(float value)
{
    CHECK_NULL_VOID(value_);
    value_->Set(value);

    StartLightSweepAnimation(ProgressType(progressType_->Get()), value);
}

void ProgressModifier::SetScaleWidth(float value)
{
    CHECK_NULL_VOID(scaleWidth_);
    scaleWidth_->Set(value);
}

void ProgressModifier::SetScaleCount(int32_t value)
{
    CHECK_NULL_VOID(scaleCount_);
    scaleCount_->Set(value);
}

void ProgressModifier::SetContentOffset(const OffsetF& offset)
{
    CHECK_NULL_VOID(offset_);
    offset_->Set(offset);
}

void ProgressModifier::SetContentSize(const SizeF& contentSize)
{
    CHECK_NULL_VOID(contentSize_);
    contentSize_->Set(contentSize);
}

void ProgressModifier::SetBorderWidth(float width)
{
    capsuleBorderWidth_->Set(width);
}

void ProgressModifier::SetSweepEffect(bool value)
{
    sweepEffect_->Set(value);
}

void ProgressModifier::ContentDrawWithFunction(DrawingContext& context)
{
    auto contentSize = contentSize_->Get();
    auto& canvas = context.canvas;
    if (progressType_->Get() == static_cast<int32_t>(ProgressType::LINEAR)) {
        PaintLinear(canvas, offset_->Get(), contentSize);
    } else if (progressType_->Get() == static_cast<int32_t>(ProgressType::RING)) {
        PaintRing(canvas, offset_->Get(), contentSize);
    } else if (progressType_->Get() == static_cast<int32_t>(ProgressType::SCALE)) {
        PaintScaleRing(canvas, offset_->Get(), contentSize);
    } else if (progressType_->Get() == static_cast<int32_t>(ProgressType::MOON)) {
        PaintMoon(canvas, offset_->Get(), contentSize);
    } else if (progressType_->Get() == static_cast<int32_t>(ProgressType::CAPSULE)) {
        if (contentSize.Width() >= contentSize.Height()) {
            PaintCapsule(canvas, offset_->Get(), contentSize);
        } else {
            PaintVerticalCapsule(canvas, offset_->Get(), contentSize);
        }
    } else {
        PaintLinear(canvas, offset_->Get(), contentSize);
    }
}

void ProgressModifier::PaintLinear(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(bgColor_->Get()));
    double radius = strokeWidth_->Get() / INT32_TWO;
    if (contentSize.Width() >= contentSize.Height()) {
        double barLength = contentSize.Width() - radius * INT32_TWO;
        CHECK_NULL_VOID(!NearEqual(barLength, 0.0));
        double dateLength = barLength * value_->Get() / maxValue_->Get();
        canvas.AttachBrush(brush);
        auto offsetY = offset.GetY() + (contentSize.Height() - strokeWidth_->Get()) / INT32_TWO;
        canvas.DrawRoundRect(
            { { offset.GetX(), offsetY, contentSize.Width() + offset.GetX(),
                                   strokeWidth_->Get() + offsetY },
            radius, radius });
        // progress selected part
        CHECK_NULL_VOID(!NearEqual(dateLength, 0.0));
        brush.SetColor(ToRSColor((color_->Get())));
        canvas.AttachBrush(brush);
        canvas.DrawRoundRect(
            { { offset.GetX(), offsetY, dateLength + offset.GetX() + strokeWidth_->Get(),
                                   strokeWidth_->Get() + offsetY },
            radius, radius });
    } else {
        double barLength = contentSize.Height() - radius * INT32_TWO;
        CHECK_NULL_VOID(!NearEqual(barLength, 0.0));
        double dateLength = barLength * value_->Get() / maxValue_->Get();
        canvas.AttachBrush(brush);
        auto offsetX = offset.GetX() + (contentSize.Width() - strokeWidth_->Get()) / INT32_TWO;
        canvas.DrawRoundRect(
            { { offsetX, offset.GetY(), strokeWidth_->Get() + offsetX,
                                   contentSize.Height() + offset.GetY() },
            radius, radius });
        // progress selected part
        CHECK_NULL_VOID(!NearEqual(dateLength, 0.0));
        brush.SetColor(ToRSColor((color_->Get())));
        canvas.AttachBrush(brush);
        canvas.DrawRoundRect(
            { { offsetX, offset.GetY(), strokeWidth_->Get() + offsetX,
                                   dateLength + offset.GetY() + strokeWidth_->Get() },
            radius, radius });
    }
}

void ProgressModifier::PaintRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const
{
    auto centerPt = PointF(contentSize.Width() / 2, contentSize.Height() / 2) + offset;
    auto radius = std::min(contentSize.Width() / 2, contentSize.Height() / 2);
    auto angle = (value_->Get() / maxValue_->Get()) * ANGLE_360;
    auto thickness = strokeWidth_->Get();
    if (thickness >= radius) {
        LOGI("strokeWidth is lager than radius,  auto set strokeWidth as half of radius");
        thickness = radius / 2;
    }
    // The shadowBlurSigma is an empirical value. If it is greater than thickness / 5, the shadow will be cut by
    // the canvas boundary.
    auto shadowBlurSigma = std::max(thickness / 5, RING_SHADOW_BLUR_RADIUS_MIN);
    auto shadowBlurOffset = thickness / 2 + std::max(RING_SHADOW_OFFSET_X, RING_SHADOW_OFFSET_Y);
    radius = radius - thickness / 2 - shadowBlurOffset;

    RingProgressData ringData;
    ringData.centerPt = centerPt;
    ringData.radius = radius;
    ringData.angle = angle;
    ringData.thickness = thickness;
    ringData.shadowBlurSigma = shadowBlurSigma;

    PaintRingBackground(canvas, ringData);

    if (NearZero(angle)) {
        return;
    }

    if (paintShadow_->Get()) {
        PaintRingProgressOrShadow(canvas, ringData, true);
    }

    PaintRingProgressOrShadow(canvas, ringData, false);
}

void ProgressModifier::PaintRingBackground(RSCanvas& canvas, const RingProgressData& ringProgressData) const
{
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(ringProgressData.thickness);
    pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
    pen.SetColor(ToRSColor(bgColor_->Get()));

    canvas.Save();
    canvas.AttachPen(pen);
    canvas.DrawCircle(ToRSPoint(ringProgressData.centerPt), ringProgressData.radius);
    canvas.DetachPen();
    canvas.Restore();
}

void ProgressModifier::PaintRingProgressOrShadow(
    RSCanvas& canvas, const RingProgressData& ringProgressData, bool isShadow) const
{
    PointF centerPt = ringProgressData.centerPt;
    auto radius = ringProgressData.radius;
    auto angle = ringProgressData.angle;
    auto thickness = ringProgressData.thickness;
    double halfThickness = thickness / 2;

    std::vector<RSColorQuad> colors;
    std::vector<float> pos;
    auto gradientColors = ringProgressColors_->Get().GetGradient().GetColors();
    for (size_t i = 0; i < gradientColors.size(); i++) {
        colors.emplace_back(gradientColors[i].GetLinearColor().GetValue());
        pos.emplace_back(gradientColors[i].GetDimension().Value());
    }

    RSPen pen;
    pen.SetWidth(thickness);
    RSBrush startCirclePaint;
    startCirclePaint.SetAntiAlias(true);
    startCirclePaint.SetColor(gradientColors.back().GetLinearColor().GetValue());
    RSBrush endCirclePaint;
    endCirclePaint.SetAntiAlias(true);
    endCirclePaint.SetColor(gradientColors.front().GetLinearColor().GetValue());

    if (isShadow) {
        centerPt = centerPt + OffsetF(RING_SHADOW_OFFSET_X, RING_SHADOW_OFFSET_Y);
        RSFilter filter;
        filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::NORMAL, ringProgressData.shadowBlurSigma));
        pen.SetFilter(filter);
        startCirclePaint.SetFilter(filter);
        endCirclePaint.SetFilter(filter);
    }

    RSRect edgeRect(centerPt.GetX() - halfThickness, centerPt.GetY() - radius - halfThickness,
        centerPt.GetX() + halfThickness, centerPt.GetY() - radius + halfThickness);
    // Paint begin-side semicircle
    canvas.Save();
    canvas.Rotate(angle, centerPt.GetX(), centerPt.GetY());
    canvas.AttachBrush(startCirclePaint);
    canvas.DrawArc(edgeRect, -ANGLE_90, ANGLE_180);
    canvas.DetachBrush();
    canvas.Restore();

    // Paint progress arc
    canvas.Save();
    canvas.Rotate(-ANGLE_90, centerPt.GetX(), centerPt.GetY());
    pen.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
        ToRSPoint(PointF(centerPt.GetX(), centerPt.GetY())), colors, pos, RSTileMode::CLAMP, 0, angle));
    canvas.AttachPen(pen);
    canvas.DrawArc(
        { centerPt.GetX() - radius, centerPt.GetY() - radius,
          centerPt.GetX() + radius, centerPt.GetY() + radius },
        0, angle);
    canvas.DetachPen();
    canvas.Restore();

    // Paint end-side semicircle
    canvas.Save();
    canvas.AttachBrush(endCirclePaint);
    canvas.DrawArc(edgeRect, ANGLE_90, ANGLE_180);
    canvas.DetachBrush();
    canvas.Restore();
}

void ProgressModifier::PaintScaleRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const
{
    PointF centerPt = PointF(contentSize.Width() / INT32_TWO, contentSize.Height() / INT32_TWO) + offset;
    double radius = std::min(contentSize.Width() / INT32_TWO, contentSize.Height() / INT32_TWO);
    double lengthOfScale = strokeWidth_->Get();
    double pathDistance = FLOAT_TWO_ZERO * M_PI * radius / scaleCount_->Get();
    if (scaleWidth_->Get() > pathDistance) {
        LOGI("scaleWidth is lager than pathDistance,  auto changeto paint ring");
        PaintRing(canvas, offset, contentSize);
        return;
    }
    double widthOfLine = scaleWidth_->Get();
    RSPen pen;
    RSPath path;
    pen.SetWidth(widthOfLine);
    path.AddRoundRect(
        { 0, 0, widthOfLine, lengthOfScale }, widthOfLine / INT32_TWO, widthOfLine / INT32_TWO,
        RSPathDirection::CW_DIRECTION);
    pen.SetAntiAlias(true);
    pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
    pen.SetPathEffect(RSPathEffect::CreatePathDashEffect(path, pathDistance, 0.0f, RSPathDashStyle::ROTATE));
    pen.SetColor(ToRSColor(bgColor_->Get()));
    canvas.AttachPen(pen);
    canvas.DrawArc(
        { centerPt.GetX() - radius, centerPt.GetY() - radius, centerPt.GetX() + radius, centerPt.GetY() + radius },
        ANGLE_270, ANGLE_360);
    // start to draw cur value progress
    pen.SetColor(ToRSColor((color_->Get())));
    canvas.AttachPen(pen);
    double angle = (value_->Get() / maxValue_->Get()) * ANGLE_360;
    canvas.DrawArc(
        { centerPt.GetX() - radius, centerPt.GetY() - radius, centerPt.GetX() + radius, centerPt.GetY() + radius },
        ANGLE_270, angle);
}

void ProgressModifier::PaintMoon(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const
{
    static int32_t totalDegree = 1;
    PointF centerPt = PointF(contentSize.Width() / INT32_TWO, contentSize.Height() / INT32_TWO) + offset;
    double radius = std::min(contentSize.Width() / INT32_TWO, contentSize.Height() / INT32_TWO);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetAlpha(true);
    brush.SetColor(ToRSColor(bgColor_->Get()));
    double angle = (value_->Get() / maxValue_->Get()) * totalDegree;
    RSPath path;
    canvas.AttachBrush(brush);
    canvas.DrawCircle(ToRSPoint(centerPt), radius);
    brush.SetColor(ToRSColor((color_->Get())));
    canvas.AttachBrush(brush);
    path.AddArc(
        { centerPt.GetX() - radius, centerPt.GetY() - radius, centerPt.GetX() + radius, centerPt.GetY() + radius },
        ANGLE_90, ANGLE_180);
    if (angle <= FLOAT_ZERO_FIVE) {
        double progressOffset = radius - radius * angle / FLOAT_ZERO_FIVE;
        path.MoveTo(centerPt.GetX(), centerPt.GetY() - radius);
        // startAngle:270  sweepAngle:-180
        path.AddArc(
            { centerPt.GetX() - progressOffset, centerPt.GetY() - radius, centerPt.GetX() + progressOffset,
                        centerPt.GetY() + radius },
            ANGLE_270, -ANGLE_180);
        canvas.DrawPath(path);
    } else {
        double progressOffset = radius * (angle - FLOAT_ZERO_FIVE) / FLOAT_ZERO_FIVE;
        path.MoveTo(centerPt.GetX(), centerPt.GetY() - radius);
        // startAngle:270  sweepAngle:180
        path.AddArc(
            { centerPt.GetX() - progressOffset, centerPt.GetY() - radius, centerPt.GetX() + progressOffset,
                        centerPt.GetY() + radius },
            ANGLE_270, ANGLE_180);
        canvas.DrawPath(path);
    }
}

void ProgressModifier::PaintCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const
{
    auto borderWidth = capsuleBorderWidth_->Get();
    if (GreatNotEqual(2 * borderWidth, contentSize.Height())) {
        borderWidth = contentSize.Height() / 2;
    }
    static int32_t totalDegree = 1;
    auto capsuleSize = contentSize;
    double radiusBig = std::min((capsuleSize.Width() - borderWidth) / INT32_TWO,
        (capsuleSize.Height() - borderWidth) / INT32_TWO);
    double offsetXBig = offset.GetX() + borderWidth / INT32_TWO;
    double offsetYBig = offset.GetY() + borderWidth / INT32_TWO;
    capsuleSize.SetWidth(contentSize.Width() - borderWidth * INT32_TWO);
    capsuleSize.SetHeight(contentSize.Height() - borderWidth * INT32_TWO);
    double radius = std::min(capsuleSize.Width() / INT32_TWO, capsuleSize.Height() / INT32_TWO);
    double offsetX = offset.GetX() + borderWidth;
    double offsetY = offset.GetY() + borderWidth;
    double progressWidth = (value_->Get() / maxValue_->Get()) * totalDegree * capsuleSize.Width();
    RSBrush brush;
    brush.SetAntiAlias(true);
    RSPen pen;
    brush.SetAlpha(true);
    brush.SetColor(ToRSColor(bgColor_->Get()));
    pen.SetWidth(borderWidth);
    pen.SetAntiAlias(true);
    pen.SetColor(ToRSColor(borderColor_->Get()));
    canvas.AttachPen(pen);
    if (!NearZero(borderWidth)) {
        canvas.DrawRoundRect(
            { { offsetXBig, offsetYBig, contentSize.Width() - borderWidth + offsetXBig,
                contentSize.Height() - borderWidth + offsetYBig },
                radiusBig, radiusBig });
    }
    canvas.DetachPen();
    RSPath path;
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(
        { { offsetX, offsetY, capsuleSize.Width() + offsetX, capsuleSize.Height() + offsetY }, radius, radius });
    brush.SetColor(ToRSColor((color_->Get())));
    canvas.AttachBrush(brush);
    path.AddArc(
        { offsetX, offsetY, INT32_TWO * radius + offsetX, capsuleSize.Height() + offsetY }, ANGLE_90, ANGLE_180);
    if (LessNotEqual(progressWidth, radius)) {
        // startAngle:270  sweepAngle:-180
        path.AddArc(
            { offsetX + progressWidth, offsetY, INT32_TWO * radius - progressWidth + offsetX,
                        capsuleSize.Height() + offsetY },
            ANGLE_270, -ANGLE_180);
    } else if (GreatNotEqual(progressWidth, capsuleSize.Width() - radius)) {
        path.AddRect(
            { offsetX + radius, offsetY, capsuleSize.Width() + offsetX - radius, capsuleSize.Height() + offsetY });
        // startAngle:270  sweepAngle:180
        path.AddArc(
            { offsetX + (capsuleSize.Width() - radius) * FLOAT_TWO_ZERO - progressWidth, offsetY,
                        offsetX + progressWidth, capsuleSize.Height() + offsetY },
            ANGLE_270, ANGLE_180);
    } else {
        path.AddRect(
            { radius + offsetX, offsetY, progressWidth + offsetX, capsuleSize.Height() + offsetY });
    }
    canvas.DrawPath(path);
    canvas.Restore();

    PaintCapsuleLightSweep(canvas, capsuleSize, offset, path, false);
}

void ProgressModifier::PaintVerticalCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const
{
    auto borderWidth = capsuleBorderWidth_->Get();
    if (GreatNotEqual(2 * borderWidth, contentSize.Width())) {
        borderWidth = contentSize.Width() / 2;
    }
    static int32_t totalDegree = 1;
    SizeF capsuleSize = contentSize;
    double radiusBig = std::min((capsuleSize.Width() - borderWidth) / INT32_TWO,
        (capsuleSize.Height() - borderWidth) / INT32_TWO);
    double offsetXBig = offset.GetX() + borderWidth / INT32_TWO;
    double offsetYBig = offset.GetY() + borderWidth / INT32_TWO;
    capsuleSize.SetWidth(contentSize.Width() - borderWidth * INT32_TWO);
    capsuleSize.SetHeight(contentSize.Height() - borderWidth * INT32_TWO);
    double radius = std::min(capsuleSize.Width() / INT32_TWO, capsuleSize.Height() / INT32_TWO);
    double offsetX = offset.GetX() + borderWidth;
    double offsetY = offset.GetY() + borderWidth;
    double progressWidth = (value_->Get() / maxValue_->Get()) * totalDegree * capsuleSize.Height();
    RSBrush brush;
    brush.SetAntiAlias(true);
    RSPen pen;
    pen.SetWidth(borderWidth);
    pen.SetAntiAlias(true);
    pen.SetColor(ToRSColor(borderColor_->Get()));
    canvas.AttachPen(pen);
    if (!NearZero(borderWidth)) {
        canvas.DrawRoundRect(
            { { offsetXBig, offsetYBig, contentSize.Width() - borderWidth + offsetXBig,
                contentSize.Height() - borderWidth + offsetYBig },
                radiusBig, radiusBig });
    }
    canvas.DetachPen();
    brush.SetAlpha(true);
    brush.SetColor(ToRSColor(bgColor_->Get()));
    RSPath path;
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(
        { { offsetX, offsetY, capsuleSize.Width() + offsetX, capsuleSize.Height() + offsetY }, radius, radius });
    brush.SetColor(ToRSColor((color_->Get())));
    canvas.AttachBrush(brush);
    path.AddArc(
        { offsetX, offsetY, capsuleSize.Width() + offsetX, capsuleSize.Width() + offsetY }, 0, -ANGLE_180);
    if (LessNotEqual(progressWidth, radius)) {
        // startAngle:180  sweepAngle:180
        path.AddArc(
            { offsetX, offsetY + progressWidth, capsuleSize.Width() + offsetX,
                        capsuleSize.Width() - progressWidth + offsetY },
            ANGLE_180, ANGLE_180);
    } else if (GreatNotEqual(progressWidth, capsuleSize.Height() - radius)) {
        path.AddRect(
            { offsetX, offsetY + radius, capsuleSize.Width() + offsetX, capsuleSize.Height() - radius + offsetY });
        // startAngle:180  sweepAngle:-180
        path.AddArc(
            { offsetX, offsetY + (capsuleSize.Height() - radius) * FLOAT_TWO_ZERO - progressWidth,
                        capsuleSize.Width() + offsetX, progressWidth + offsetY },
            ANGLE_180, -ANGLE_180);
    } else {
        path.AddRect(
            { offsetX, radius + offsetY, offsetX + capsuleSize.Width(), progressWidth + offsetY });
    }
    canvas.DrawPath(path);
    canvas.Restore();

    PaintCapsuleLightSweep(canvas, capsuleSize, offset, path, true);
}

void ProgressModifier::PaintCapsuleLightSweep(
    RSCanvas& canvas, const SizeF& contentSize, const OffsetF& offset, const RSPath& path, bool isVertical) const
{
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(1);
    auto gradient = CreateGradient();
    std::vector<RSColorQuad> colors;
    std::vector<float> pos;
    RSBrush brush;
    auto gradientColors = gradient.GetColors();
    for (size_t i = 0; i < gradientColors.size(); i++) {
        colors.emplace_back(gradientColors[i].GetColor().GetValue());
        pos.emplace_back(gradientColors[i].GetDimension().Value());
    }

    float endPos = capsuleDate_->Get();
    if (isVertical) {
        brush.SetShaderEffect(RSShaderEffect::CreateLinearGradient(
            ToRSPoint(PointF(offset.GetX() + contentSize.Width() / 2,
            offset.GetY() + endPos - SWEEP_WIDTH.ConvertToPx() + capsuleBorderWidth_->Get())),
            ToRSPoint(PointF(offset.GetX() + contentSize.Width() / 2,
            offset.GetY() + endPos - capsuleBorderWidth_->Get())),
            colors, pos, RSTileMode::CLAMP));
    } else {
        brush.SetShaderEffect(RSShaderEffect::CreateLinearGradient(
            ToRSPoint(PointF(offset.GetX() + endPos - SWEEP_WIDTH.ConvertToPx() + capsuleBorderWidth_->Get(),
            offset.GetY() + contentSize.Height() / 2)),
            ToRSPoint(PointF(offset.GetX() + endPos - capsuleBorderWidth_->Get(),
            offset.GetY() + contentSize.Height() / 2)),
            colors, pos, RSTileMode::CLAMP));
    }
    
    auto offsetX = offset.GetX();
    auto offsetY = offset.GetY();
    canvas.Save();
    canvas.ClipPath(path, RSClipOp::INTERSECT, true);
    canvas.AttachBrush(brush);
    if (isVertical) {
        canvas.DrawRect(
            { offsetX + capsuleBorderWidth_->Get(),
            offsetY + endPos - SWEEP_WIDTH.ConvertToPx() + capsuleBorderWidth_->Get(),
            offsetX + contentSize.Width() + capsuleBorderWidth_->Get(),
            offsetY + endPos - capsuleBorderWidth_->Get()});
    } else {
        canvas.DrawRect(
            { offsetX + endPos - SWEEP_WIDTH.ConvertToPx() + capsuleBorderWidth_->Get(),
            offsetY + capsuleBorderWidth_->Get(), offsetX + endPos + capsuleBorderWidth_->Get(),
            offsetY + contentSize.Height() + capsuleBorderWidth_->Get()});
    }
    canvas.DetachPen();
    canvas.Restore();
}

Gradient ProgressModifier::CreateGradient() const
{
    Gradient gradient;
    Color lightSweepColorBase = Color::WHITE;
    Color lightSweepColorEnd = lightSweepColorBase.ChangeOpacity(0.0);
    GradientColor gradientColorEnd;
    gradientColorEnd.SetColor(lightSweepColorEnd);
    gradientColorEnd.SetDimension(Dimension(0.0, DimensionUnit::VP));
    gradient.AddColor(gradientColorEnd);

    Color lightSweepColorMiddle = lightSweepColorBase.ChangeOpacity(0.2);
    GradientColor gradientColorMiddle;
    gradientColorMiddle.SetColor(lightSweepColorMiddle);
    gradientColorMiddle.SetDimension(SWEEP_WIDTH);
    gradient.AddColor(gradientColorMiddle);
    return gradient;
}
} // namespace OHOS::Ace::NG
