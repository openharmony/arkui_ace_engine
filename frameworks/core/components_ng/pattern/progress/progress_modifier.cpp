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

#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"

namespace OHOS::Ace::NG {
constexpr uint32_t DEFAULT_BORDER_COLOR = 0x33007dff;

ProgressModifier::ProgressModifier()
    : strokeWidth_(AceType::MakeRefPtr<AnimatablePropertyFloat>(FLOAT_TWO_ZERO)),
      color_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::BLUE)),
      bgColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::GRAY)),
      borderColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(DEFAULT_BORDER_COLOR))),
      maxValue_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_MAX_VALUE)),
      value_(AceType::MakeRefPtr<PropertyFloat>(0.0f)),
      scaleWidth_(AceType::MakeRefPtr<PropertyFloat>(DEFAULT_SCALE_WIDTH)),
      scaleCount_(AceType::MakeRefPtr<PropertyInt>(DEFAULT_SCALE_COUNT)),
      progressType_(AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(ProgressType::LINEAR)))
{
    AttachProperty(strokeWidth_);
    AttachProperty(color_);
    AttachProperty(bgColor_);
    AttachProperty(borderColor_);
    AttachProperty(maxValue_);
    AttachProperty(value_);
    AttachProperty(scaleWidth_);
    AttachProperty(scaleCount_);
}

void ProgressModifier::onDraw(DrawingContext& context)
{
    ContentDrawWithFunction(context);
}


void ProgressModifier::SetStrokeWidth(float width)
{
    if (strokeWidth_) {
        strokeWidth_->Set(width);
    }
}

void ProgressModifier::SetColor(LinearColor color)
{
    if (color_) {
        color_->Set(color);
    }
}

void ProgressModifier::SetBackgroundColor(LinearColor color)
{
    if (bgColor_) {
        bgColor_->Set(color);
    }
}

void ProgressModifier::SetBorderColor(LinearColor color)
{
    if (borderColor_) {
        borderColor_->Set(color);
    }
}

void ProgressModifier::SetProgressType(ProgressType type)
{
    if (progressType_) {
        progressType_->Set(static_cast<int32_t>(type));
    }
}

void ProgressModifier::SetMaxValue(float value)
{
    if (maxValue_) {
        maxValue_->Set(value);
    }
}

void ProgressModifier::SetValue(float value)
{
    if (value_) {
        value_->Set(value);
    }
}

void ProgressModifier::SetScaleWidth(float value)
{
    if (scaleWidth_) {
        scaleWidth_->Set(value);
    }
}

void ProgressModifier::SetScaleCount(int32_t value)
{
    if (scaleCount_) {
        scaleCount_->Set(value);
    }
}

void ProgressModifier::SetOffset(const OffsetF& offset)
{
    offset_ = offset;
}

void ProgressModifier::SetBorderWidth(const Dimension& width)
{
    capsuleBorderWidth_ = width;
}

void ProgressModifier::ContentDrawWithFunction(DrawingContext& context)
{
    SizeF frameSize(context.width, context.height);
    auto& canvas = context.canvas;
    if (progressType_->Get() == static_cast<int32_t>(ProgressType::LINEAR)) {
        PaintLinear(canvas, offset_, frameSize);
    } else if (progressType_->Get() == static_cast<int32_t>(ProgressType::RING)) {
        PaintRing(canvas, offset_, frameSize);
    } else if (progressType_->Get() == static_cast<int32_t>(ProgressType::SCALE)) {
        PaintScaleRing(canvas, offset_, frameSize);
    } else if (progressType_->Get() == static_cast<int32_t>(ProgressType::MOON)) {
        PaintMoon(canvas, offset_, frameSize);
    } else if (progressType_->Get() == static_cast<int32_t>(ProgressType::CAPSULE)) {
        if (frameSize.Width() >= frameSize.Height()) {
            PaintCapsule(canvas, offset_, frameSize);
        } else {
            PaintVerticalCapsule(canvas, offset_, frameSize);
        }
    } else {
        PaintLinear(canvas, offset_, frameSize);
    }
}

void ProgressModifier::PaintLinear(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(bgColor_->Get()));
    double radius = strokeWidth_->Get() / INT32_TWO;
    if (frameSize.Width() >= frameSize.Height()) {
        double dateLength = frameSize.Width() * value_->Get() / maxValue_->Get();
        canvas.AttachBrush(brush);
        canvas.DrawRoundRect(
            { { offset.GetX(), offset.GetY(), frameSize.Width() + offset.GetX(), strokeWidth_->Get() + offset.GetY() },
                radius, radius });
        brush.SetColor(ToRSColor((color_->Get())));
        canvas.AttachBrush(brush);
        if (!NearEqual(dateLength, 0.0)) {
            canvas.DrawRoundRect(
                { { offset.GetX(), offset.GetY(), dateLength + offset.GetX(), strokeWidth_->Get() + offset.GetY() },
                    radius, radius });
        }
    } else {
        double dateLength = frameSize.Height() * value_->Get() / maxValue_->Get();
        canvas.AttachBrush(brush);
        canvas.DrawRoundRect(
            { { offset.GetX(), offset.GetY(), strokeWidth_->Get() + offset.GetX(), frameSize.Height() + offset.GetY() },
                radius, radius });
        brush.SetColor(ToRSColor((color_->Get())));
        canvas.AttachBrush(brush);
        if (!NearEqual(dateLength, 0.0)) {
            canvas.DrawRoundRect(
                { { offset.GetX(), offset.GetY(), strokeWidth_->Get() + offset.GetX(), dateLength + offset.GetY() },
                    radius, radius });
        }
    }
}

void ProgressModifier::PaintRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const
{
    static int32_t totalDegree = 360;
    PointF centerPt = PointF(frameSize.Width() / INT32_TWO, frameSize.Height() / INT32_TWO) + offset;
    double radius = std::min(frameSize.Width() / INT32_TWO, frameSize.Height() / INT32_TWO);
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
    pen.SetColor(ToRSColor((color_->Get())));
    canvas.AttachPen(pen);
    double angle = (value_->Get() / maxValue_->Get()) * totalDegree;
    canvas.DrawArc(
        { centerPt.GetX() - radius, centerPt.GetY() - radius, centerPt.GetX() + radius, centerPt.GetY() + radius },
        ANGLE_270, angle);
}

void ProgressModifier::PaintScaleRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const
{
    static int32_t totalDegree = 360;
    PointF centerPt = PointF(frameSize.Width() / INT32_TWO, frameSize.Height() / INT32_TWO) + offset;
    double radius = std::min(frameSize.Width() / INT32_TWO, frameSize.Height() / INT32_TWO);
    double lengthOfScale = strokeWidth_->Get();
    if (lengthOfScale > radius) {
        LOGI("strokeWidth is lager than radius,  auto set strokeWidth as half of radius");
        lengthOfScale = radius / INT32_TWO;
    }
    double pathDistance = FLOAT_TWO_ZERO * M_PI * radius / scaleCount_->Get();
    if (scaleWidth_->Get() > pathDistance) {
        LOGI("scaleWidth is lager than pathDistance,  auto changeto paint ring");
        PaintRing(canvas, offset, frameSize);
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
    pen.SetColor(ToRSColor((color_->Get())));
    canvas.AttachPen(pen);
    double angle = (value_->Get() / maxValue_->Get()) * totalDegree;
    canvas.DrawArc(
        { centerPt.GetX() - radius, centerPt.GetY() - radius, centerPt.GetX() + radius, centerPt.GetY() + radius },
        ANGLE_270, angle);
}

void ProgressModifier::PaintMoon(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const
{
    static int32_t totalDegree = 1;
    PointF centerPt = PointF(frameSize.Width() / INT32_TWO, frameSize.Height() / INT32_TWO) + offset;
    double radius = std::min(frameSize.Width() / INT32_TWO, frameSize.Height() / INT32_TWO);
    RSBrush brush;
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
            centerPt.GetY() + radius }, ANGLE_270, -ANGLE_180);
        canvas.DrawPath(path);
    } else {
        double progressOffset = radius * (angle - FLOAT_ZERO_FIVE) / FLOAT_ZERO_FIVE;
        path.MoveTo(centerPt.GetX(), centerPt.GetY() - radius);
        // startAngle:270  sweepAngle:180
        path.AddArc(
            { centerPt.GetX() - progressOffset, centerPt.GetY() - radius, centerPt.GetX() + progressOffset,
            centerPt.GetY() + radius }, ANGLE_270, ANGLE_180);
        canvas.DrawPath(path);
    }
}

void ProgressModifier::PaintCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const
{
    static int32_t totalDegree = 1;
    SizeF contentSize = frameSize;
    double radiusBig = std::min((contentSize.Width() - capsuleBorderWidth_.ConvertToPx()) / INT32_TWO,
        (contentSize.Height() - capsuleBorderWidth_.ConvertToPx()) / INT32_TWO);
    double offsetXBig = offset.GetX() + capsuleBorderWidth_.ConvertToPx() / INT32_TWO;
    double offsetYBig = offset.GetY() + capsuleBorderWidth_.ConvertToPx() / INT32_TWO;
    contentSize.SetWidth(frameSize.Width() - capsuleBorderWidth_.ConvertToPx()*INT32_TWO);
    contentSize.SetHeight(frameSize.Height() - capsuleBorderWidth_.ConvertToPx()*INT32_TWO);
    double radius = std::min(contentSize.Width() / INT32_TWO, contentSize.Height() / INT32_TWO);
    double offsetX = offset.GetX() + capsuleBorderWidth_.ConvertToPx();
    double offsetY = offset.GetY() + capsuleBorderWidth_.ConvertToPx();
    double progressWidth = (value_->Get() / maxValue_->Get()) * totalDegree * contentSize.Width();
    RSBrush brush;
    RSPen pen;
    brush.SetAlpha(true);
    brush.SetColor(ToRSColor(bgColor_->Get()));
    pen.SetWidth(capsuleBorderWidth_.ConvertToPx());
    pen.SetAntiAlias(true);
    pen.SetColor(ToRSColor(borderColor_->Get()));
    canvas.AttachPen(pen);
    canvas.DrawRoundRect(
        { { offsetXBig, offsetYBig, frameSize.Width() - capsuleBorderWidth_.ConvertToPx() + offsetXBig,
        frameSize.Height() - capsuleBorderWidth_.ConvertToPx() + offsetYBig }, radiusBig, radiusBig });
    canvas.DetachPen();
    RSPath path;
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(
        { { offsetX, offsetY, contentSize.Width() + offsetX, contentSize.Height() + offsetY }, radius, radius });
    brush.SetColor(ToRSColor((color_->Get())));
    canvas.AttachBrush(brush);
    path.AddArc(
        { offsetX, offsetY, INT32_TWO*radius + offsetX, contentSize.Height() + offsetY }, ANGLE_90, ANGLE_180);
    if (LessNotEqual(progressWidth, radius)) {
        // startAngle:270  sweepAngle:-180
        path.AddArc(
            { offsetX + progressWidth, offsetY, INT32_TWO * radius - progressWidth + offsetX,
            contentSize.Height() + offsetY }, ANGLE_270, -ANGLE_180);
    } else if (GreatNotEqual(progressWidth, contentSize.Width() - radius)) {
        path.AddRect(
            { offsetX + radius, offsetY, contentSize.Width() + offsetX - radius, contentSize.Height() + offsetY });
        // startAngle:270  sweepAngle:180
        path.AddArc(
            { offsetX + (contentSize.Width() - radius) * FLOAT_TWO_ZERO - progressWidth, offsetY,
            offsetX + progressWidth, contentSize.Height() + offsetY }, ANGLE_270, ANGLE_180);
    } else {
        path.AddRect(
            { radius + offsetX, offsetY, progressWidth + offsetX, contentSize.Height() + offsetY });
    }
    canvas.DrawPath(path);
    canvas.Restore();
}

void ProgressModifier::PaintVerticalCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const
{
    static int32_t totalDegree = 1;
    SizeF contentSize = frameSize;
    double radiusBig = std::min((contentSize.Width() - capsuleBorderWidth_.ConvertToPx()) / INT32_TWO,
        (contentSize.Height() - capsuleBorderWidth_.ConvertToPx())/ INT32_TWO);
    double offsetXBig = offset.GetX() + capsuleBorderWidth_.ConvertToPx() / INT32_TWO;
    double offsetYBig = offset.GetY() + capsuleBorderWidth_.ConvertToPx() / INT32_TWO;
    contentSize.SetWidth(frameSize.Width() - capsuleBorderWidth_.ConvertToPx()*INT32_TWO);
    contentSize.SetHeight(frameSize.Height() - capsuleBorderWidth_.ConvertToPx() * INT32_TWO);
    double radius = std::min(contentSize.Width() / INT32_TWO, contentSize.Height() / INT32_TWO);
    double offsetX = offset.GetX() + capsuleBorderWidth_.ConvertToPx();
    double offsetY = offset.GetY() + capsuleBorderWidth_.ConvertToPx();
    double progressWidth = (value_->Get() / maxValue_->Get()) * totalDegree * contentSize.Height();
    RSBrush brush;
    RSPen pen;
    pen.SetWidth(capsuleBorderWidth_.ConvertToPx());
    pen.SetAntiAlias(true);
    pen.SetColor(ToRSColor(borderColor_->Get()));
    canvas.AttachPen(pen);
    canvas.DrawRoundRect(
        { { offsetXBig, offsetYBig, frameSize.Width() - capsuleBorderWidth_.ConvertToPx() + offsetXBig,
            frameSize.Height() - capsuleBorderWidth_.ConvertToPx() + offsetYBig }, radiusBig, radiusBig });
    canvas.DetachPen();
    brush.SetAlpha(true);
    brush.SetColor(ToRSColor(bgColor_->Get()));
    RSPath path;
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(
        { { offsetX, offsetY, contentSize.Width() + offsetX, contentSize.Height() + offsetY }, radius, radius });
    brush.SetColor(ToRSColor((color_->Get())));
    canvas.AttachBrush(brush);
    path.AddArc(
        { offsetX, offsetY, contentSize.Width() + offsetX, contentSize.Width() + offsetY }, 0, -ANGLE_180);
    if (LessNotEqual(progressWidth, radius)) {
        // startAngle:180  sweepAngle:180
        path.AddArc(
            { offsetX, offsetY + progressWidth, contentSize.Width() + offsetX,
            contentSize.Width() - progressWidth + offsetY }, ANGLE_180, ANGLE_180);
    } else if (GreatNotEqual(progressWidth, contentSize.Height() - radius)) {
        path.AddRect(
            { offsetX, offsetY + radius, contentSize.Width() + offsetX, contentSize.Height() - radius + offsetY });
        // startAngle:180  sweepAngle:-180
        path.AddArc(
            { offsetX, offsetY + (contentSize.Height() - radius) * FLOAT_TWO_ZERO - progressWidth,
            contentSize.Width() + offsetX, progressWidth + offsetY }, ANGLE_180, -ANGLE_180);
    } else {
        path.AddRect(
            { offsetX, radius + offsetY, offsetX + contentSize.Width(), progressWidth + offsetY });
    }
    canvas.DrawPath(path);
    canvas.Restore();
}
} // namespace OHOS::Ace::NG
