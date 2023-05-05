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
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t DEFAULT_BORDER_COLOR = 0x33007dff;
constexpr int32_t INT32_TWO = 2;
constexpr int32_t ANGLE_90 = 90;
constexpr int32_t ANGLE_180 = 180;
constexpr int32_t ANGLE_270 = 270;
constexpr float DEFAULT_MAX_VALUE = 100.0f;
constexpr float DEFAULT_SCALE_WIDTH = 10.0f;
constexpr int32_t DEFAULT_SCALE_COUNT = 100;
constexpr double DEFAULT_CAPSULE_BORDER_WIDTH = 0.0;
constexpr float FLOAT_ZERO_FIVE = 0.5f;
constexpr float FLOAT_TWO_ZERO = 2.0f;
constexpr float SPRING_MOTION_RESPONSE = 0.314f;
constexpr float SPRING_MOTION_DAMPING_FRACTION = 0.95f;
} // namespace
ProgressModifier::ProgressModifier()
    : strokeWidth_(AceType::MakeRefPtr<AnimatablePropertyFloat>(FLOAT_TWO_ZERO)),
      color_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::BLUE)),
      bgColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::GRAY)),
      borderColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(DEFAULT_BORDER_COLOR))),
      capsuleDate_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0f)),
      value_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0f)),
      offset_(AceType::MakeRefPtr<PropertyOffsetF>(OffsetF())),
      contentSize_(AceType::MakeRefPtr<PropertySizeF>(SizeF())),
      maxValue_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_MAX_VALUE)),
      scaleWidth_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_SCALE_WIDTH)),
      scaleCount_(AceType::MakeRefPtr<PropertyInt>(DEFAULT_SCALE_COUNT)),
      progressType_(AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(ProgressType::LINEAR))),
      capsuleBorderWidth_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_CAPSULE_BORDER_WIDTH)),
      sweepEffect_(AceType::MakeRefPtr<PropertyBool>(false))
{
    AttachProperty(strokeWidth_);
    AttachProperty(color_);
    AttachProperty(bgColor_);
    AttachProperty(borderColor_);
    AttachProperty(maxValue_);
    AttachProperty(value_);
    AttachProperty(scaleWidth_);
    AttachProperty(scaleCount_);
    AttachProperty(capsuleBorderWidth_);
    AttachProperty(sweepEffect_);
    AttachProperty(capsuleDate_);
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

void ProgressModifier::SetMaxValue(float value)
{
    CHECK_NULL_VOID(maxValue_);
    maxValue_->Set(value);
}

void ProgressModifier::SetValue(float value)
{
    CHECK_NULL_VOID(value_);
    if (NearZero(value)) {
        value_->Set(value);
    } else {
        AnimationOption option = AnimationOption();
        auto motion =
            AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRING_MOTION_RESPONSE, SPRING_MOTION_DAMPING_FRACTION);
        option.SetCurve(motion);
        AnimationUtils::Animate(option, [&]() { value_->Set(value); });
    }
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
        CHECK_NULL_VOID(!NearEqual(dateLength, 0.0));
        canvas.AttachBrush(brush);
        auto offsetY = offset.GetY() + (contentSize.Height() - strokeWidth_->Get()) / INT32_TWO;
        canvas.DrawRoundRect(
            { { offset.GetX(), offsetY, contentSize.Width() + offset.GetX(),
                                   strokeWidth_->Get() + offsetY },
            radius, radius });
        // progress selected part
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
        CHECK_NULL_VOID(!NearEqual(dateLength, 0.0));
        canvas.AttachBrush(brush);
        auto offsetX = offset.GetX() + (contentSize.Width() - strokeWidth_->Get()) / INT32_TWO;
        canvas.DrawRoundRect(
            { { offsetX, offset.GetY(), strokeWidth_->Get() + offsetX,
                                   contentSize.Height() + offset.GetY() },
            radius, radius });
        // progress selected part
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
    static int32_t totalDegree = 360;
    PointF centerPt = PointF(contentSize.Width() / INT32_TWO, contentSize.Height() / INT32_TWO) + offset;
    double radius = std::min(contentSize.Width() / INT32_TWO, contentSize.Height() / INT32_TWO);
    RSPen pen;
    pen.SetAntiAlias(true);
    double widthOfLine = strokeWidth_->Get();
    if (widthOfLine >= radius) {
        LOGI("strokeWidth is lager than radius,  auto set strokeWidth as half of radius");
        widthOfLine = radius / INT32_TWO;
    }
    radius = radius - widthOfLine / INT32_TWO;
    pen.SetWidth(widthOfLine);
    pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
    pen.SetColor(ToRSColor(bgColor_->Get()));
    canvas.AttachPen(pen);
    canvas.DrawCircle(ToRSPoint(centerPt), radius);
    // progress selected part
    pen.SetColor(ToRSColor((color_->Get())));
    canvas.AttachPen(pen);
    double angle = (value_->Get() / maxValue_->Get()) * totalDegree;
    canvas.DrawArc(
        { centerPt.GetX() - radius, centerPt.GetY() - radius, centerPt.GetX() + radius, centerPt.GetY() + radius },
        ANGLE_270, angle);
}

void ProgressModifier::PaintScaleRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const
{
    static int32_t totalDegree = 360;
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
        ANGLE_270, totalDegree);
    // start to draw cur value progress
    pen.SetColor(ToRSColor((color_->Get())));
    canvas.AttachPen(pen);
    double angle = (value_->Get() / maxValue_->Get()) * totalDegree;
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
}
} // namespace OHOS::Ace::NG
