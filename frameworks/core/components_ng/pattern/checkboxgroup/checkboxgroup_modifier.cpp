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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_modifier.h"

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint8_t ENABLED_ALPHA = 255;
constexpr uint8_t DISABLED_ALPHA = 102;
constexpr float CHECK_MARK_START_X_POSITION = 0.25f;
constexpr float CHECK_MARK_START_Y_POSITION = 0.49f;
constexpr float CHECK_MARK_MIDDLE_X_POSITION = 0.44f;
constexpr float CHECK_MARK_MIDDLE_Y_POSITION = 0.68f;
constexpr float CHECK_MARK_END_X_POSITION = 0.76f;
constexpr float CHECK_MARK_END_Y_POSITION = 0.33f;
constexpr float CHECK_MARK_PART_START_X_POSITION = 0.20f;
constexpr float CHECK_MARK_PART_END_Y_POSITION = 0.80f;
constexpr float CHECK_MARK_PART_Y_POSITION = 0.50f;
constexpr float CHECKBOX_GROUP_DOUBLE_RATIO = 2.0f;
constexpr float CHECKBOX_GROUP_LENGTH_ZERO = 0.0f;
} // namespace

CheckBoxGroupModifier::CheckBoxGroupModifier(const Parameters& parameters)
{
    activeColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.activeColor));
    pointColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.pointColor));
    inactiveColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(parameters.inactiveColor));
    checkMarkPaintSize_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(parameters.checkMarkPaintSize);
    checkStroke_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(parameters.checkStroke);
    enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(parameters.uiStatus));
    status_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::UNSELECTED));
    offset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    size_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    animateTouchHoverColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    inactivePointColor_ = AceType::MakeRefPtr<PropertyColor>(parameters.inactivePointColor);

    borderWidth_ = parameters.borderWidth;
    borderRadius_ = parameters.borderRadius;
    shadowColor_ = parameters.shadowColor;
    clickEffectColor_ = parameters.clickEffectColor;
    hoverColor_ = parameters.hoverColor;
    hoverRadius_ = parameters.hoverRadius;
    hotZoneHorizontalPadding_ = parameters.hotZoneHorizontalPadding;
    defaultPaddingSize_ = parameters.defaultPaddingSize;
    hoverPaddingSize_ = parameters.hoverPaddingSize;
    showCircleDial_ = parameters.showCircleDial;
    hotZoneVerticalPadding_ = parameters.hotZoneVerticalPadding;
    shadowWidth_ = parameters.shadowWidth;
    hoverDuration_ = parameters.hoverDuration;
    hoverToTouchDuration_ = parameters.hoverToTouchDuration;
    checkBoxGroupShape_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(CheckBoxStyle::CIRCULAR_STYLE));
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        checkBoxGroupStyle_ = CheckBoxStyle::CIRCULAR_STYLE;
    } else {
        checkBoxGroupStyle_ = CheckBoxStyle::SQUARE_STYLE;
    }
    AttachProperty(activeColor_);
    AttachProperty(pointColor_);
    AttachProperty(inactiveColor_);
    AttachProperty(inactivePointColor_);
    AttachProperty(checkMarkPaintSize_);
    AttachProperty(checkStroke_);
    AttachProperty(enabled_);
    AttachProperty(uiStatus_);
    AttachProperty(status_);
    AttachProperty(offset_);
    AttachProperty(size_);
    AttachProperty(animateTouchHoverColor_);
    AttachProperty(checkBoxGroupShape_);
}

void CheckBoxGroupModifier::PaintCheckBox(
    DrawingContext& context, const OffsetF& paintOffset, const SizeF& contentSize) const
{
    auto& canvas = context.canvas;
    auto color = activeColor_;

    RSPen pen;
    RSBrush brush;
    pen.SetWidth(borderWidth_);
    pen.SetAntiAlias(true);
    DrawTouchAndHoverBoard(canvas, contentSize, paintOffset);
    RSPen shadowPen = RSPen(pen);
    shadowPen.SetColor(ToRSColor(shadowColor_));
    if (static_cast<CheckBoxGroupPaintProperty::SelectStatus>(status_->Get()) ==
        CheckBoxGroupPaintProperty::SelectStatus::PART) {
        PaintCheckBoxGroupPartStatus(canvas, paintOffset, brush, pen, contentSize);
        return;
    }
    if (static_cast<UIStatus>(uiStatus_->Get()) == UIStatus::OFF_TO_ON ||
        static_cast<UIStatus>(uiStatus_->Get()) == UIStatus::PART_TO_ON) {
        brush.SetColor(ToRSColor(color->Get()));
        brush.SetAntiAlias(true);
        pen.SetColor(ToRSColor(pointColor_->Get()));
        if (!enabled_->Get()) {
            brush.SetColor(ToRSColor(color->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        }
        DrawActiveBorder(canvas, paintOffset, brush, contentSize);
        DrawCheck(canvas, paintOffset, pen, shadowPen, contentSize);
    } else {
        brush.SetColor(ToRSColor(inactivePointColor_->Get()));
        pen.SetColor(ToRSColor(inactiveColor_->Get()));
        if (!enabled_->Get()) {
            brush.SetColor(
                ToRSColor(inactivePointColor_->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
            pen.SetColor(
                ToRSColor(inactiveColor_->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        }
        DrawUnselectedBorder(canvas, paintOffset, brush, contentSize);
        DrawUnselected(canvas, paintOffset, pen, contentSize);
    }
}

void CheckBoxGroupModifier::PaintCheckBoxGroupPartStatus(
    RSCanvas& canvas, const OffsetF& paintOffset, RSBrush& brush, RSPen& pen, const SizeF& paintSize) const
{
    auto color = activeColor_;
    brush.SetColor(ToRSColor(color->Get()));
    brush.SetAntiAlias(true);
    pen.SetColor(ToRSColor(pointColor_->Get()));
    if (!enabled_->Get()) {
        brush.SetColor(ToRSColor(color->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
    }
    DrawActiveBorder(canvas, paintOffset, brush, paintSize);
    DrawPart(canvas, paintOffset, pen, paintSize);
}

void CheckBoxGroupModifier::DrawCheck(
    RSCanvas& canvas, const OffsetF& origin, RSPen& pen, RSPen& shadowPen, const SizeF& paintSize) const
{
    if (checkMarkPaintSize_->Get() == CHECKBOX_GROUP_LENGTH_ZERO || checkStroke_->Get() == CHECKBOX_GROUP_LENGTH_ZERO) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    RSPath path;
#else
    RSRecordingPath path;
#endif
    float originX = origin.GetX();
    float originY = origin.GetY();
    float strokeSize = checkMarkPaintSize_->Get();
    const Offset start = Offset(strokeSize * CHECK_MARK_START_X_POSITION, strokeSize * CHECK_MARK_START_Y_POSITION);
    const Offset middle = Offset(strokeSize * CHECK_MARK_MIDDLE_X_POSITION, strokeSize * CHECK_MARK_MIDDLE_Y_POSITION);
    const Offset end = Offset(strokeSize * CHECK_MARK_END_X_POSITION, strokeSize * CHECK_MARK_END_Y_POSITION);
    path.MoveTo(originX + start.GetX() + (paintSize.Width() - strokeSize) / CHECKBOX_GROUP_DOUBLE_RATIO,
        originY + start.GetY() + (paintSize.Height() - strokeSize) / CHECKBOX_GROUP_DOUBLE_RATIO);
    path.LineTo(originX + middle.GetX() + (paintSize.Width() - strokeSize) / CHECKBOX_GROUP_DOUBLE_RATIO,
        originY + middle.GetY() + (paintSize.Height() - strokeSize) / CHECKBOX_GROUP_DOUBLE_RATIO);
    path.MoveTo(originX + middle.GetX() + (paintSize.Width() - strokeSize) / CHECKBOX_GROUP_DOUBLE_RATIO,
        originY + middle.GetY() + (paintSize.Height() - strokeSize) / CHECKBOX_GROUP_DOUBLE_RATIO);
    path.LineTo(originX + end.GetX() + (paintSize.Width() - strokeSize) / CHECKBOX_GROUP_DOUBLE_RATIO,
        originY + end.GetY() + (paintSize.Height() - strokeSize) / CHECKBOX_GROUP_DOUBLE_RATIO);
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    shadowPen.SetWidth(checkStroke_->Get() + shadowWidth_.ConvertToPx() * CHECKBOX_GROUP_DOUBLE_RATIO);
    pen.SetWidth(checkStroke_->Get());
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(path);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
#ifdef USE_ROSEN_DRAWING
    canvas.DetachPen();
#endif
}

void CheckBoxGroupModifier::DrawUnselected(
    RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const
{
    float originX = origin.GetX() + borderWidth_ / CHECKBOX_GROUP_DOUBLE_RATIO;
    float originY = origin.GetY() + borderWidth_ / CHECKBOX_GROUP_DOUBLE_RATIO;
    float endX = originX + paintSize.Width() - borderWidth_;
    float endY = originY + paintSize.Height() - borderWidth_;
    RSRect rect(originX, originY, endX, endY);
    auto rrect = RSRoundRect(rect, borderRadius_, borderRadius_);
    canvas.AttachPen(pen);
    DrawRectOrCircle(canvas, rrect);
#ifdef USE_ROSEN_DRAWING
    canvas.DetachPen();
#endif
}

void CheckBoxGroupModifier::DrawActiveBorder(
    RSCanvas& canvas, const OffsetF& paintOffset, RSBrush& brush, const SizeF& paintSize) const
{
    float originX = paintOffset.GetX();
    float originY = paintOffset.GetY();
    float endX = originX + paintSize.Width();
    float endY = originY + paintSize.Height();
    RSRect rect(originX, originY, endX, endY);
    auto rrect = RSRoundRect(rect, borderRadius_, borderRadius_);
    canvas.AttachBrush(brush);
    DrawRectOrCircle(canvas, rrect);
    canvas.DetachBrush();
}

void CheckBoxGroupModifier::DrawUnselectedBorder(
    RSCanvas& canvas, const OffsetF& paintOffset, RSBrush& brush, const SizeF& paintSize) const
{
    float originX = paintOffset.GetX() + borderWidth_;
    float originY = paintOffset.GetY() + borderWidth_;
    float endX = originX + paintSize.Width() - CHECKBOX_GROUP_DOUBLE_RATIO * borderWidth_;
    float endY = originY + paintSize.Height() - CHECKBOX_GROUP_DOUBLE_RATIO * borderWidth_;
    RSRect rect(originX, originY, endX, endY);
    auto rrect = RSRoundRect(rect, borderRadius_, borderRadius_);
    canvas.AttachBrush(brush);
    DrawRectOrCircle(canvas, rrect);
#ifdef USE_ROSEN_DRAWING
    canvas.DetachBrush();
#endif
}

void CheckBoxGroupModifier::DrawPart(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const
{
    if (checkMarkPaintSize_->Get() == CHECKBOX_GROUP_LENGTH_ZERO || checkStroke_->Get() == CHECKBOX_GROUP_LENGTH_ZERO) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    RSPath path;
#else
    RSRecordingPath path;
#endif
    RSPen shadowPen;
    float originX = origin.GetX();
    float originY = origin.GetY();
    const Offset start = Offset(checkMarkPaintSize_->Get() * CHECK_MARK_PART_START_X_POSITION,
        checkMarkPaintSize_->Get() * CHECK_MARK_PART_Y_POSITION);
    const Offset end = Offset(checkMarkPaintSize_->Get() * CHECK_MARK_PART_END_Y_POSITION,
        checkMarkPaintSize_->Get() * CHECK_MARK_PART_Y_POSITION);
    path.MoveTo(originX + start.GetX() + (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO,
        originY + start.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO);
    path.LineTo(originX + end.GetX() + (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO,
        originY + end.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO);
    shadowPen.SetColor(ToRSColor(shadowColor_));
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    shadowPen.SetWidth(checkStroke_->Get() + shadowWidth_.ConvertToPx() * CHECKBOX_GROUP_DOUBLE_RATIO);
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(path);
    pen.SetWidth(checkStroke_->Get());
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
#ifdef USE_ROSEN_DRAWING
    canvas.DetachPen();
#endif
}

void CheckBoxGroupModifier::DrawTouchAndHoverBoard(RSCanvas& canvas, const SizeF& size, const OffsetF& offset) const
{
    if (HoverEffectType::NONE == hoverEffectType_) {
        return;
    }
    RSBrush brush;
    brush.SetColor(ToRSColor(animateTouchHoverColor_->Get()));
    brush.SetAntiAlias(true);
    float originX;
    float originY;
    float endX;
    float endY;
    auto paddingPx = (showCircleDial_ ? hoverPaddingSize_.ConvertToPx() : defaultPaddingSize_.ConvertToPx());
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        originX = offset.GetX() - paddingPx;
        originY = offset.GetY() - paddingPx;
        endX = size.Width() + originX +
            CHECKBOX_GROUP_DOUBLE_RATIO * paddingPx;
        endY = size.Height() + originY +
            CHECKBOX_GROUP_DOUBLE_RATIO * paddingPx;
    } else {
        originX = offset.GetX() - hotZoneHorizontalPadding_.ConvertToPx();
        originY = offset.GetY() - hotZoneVerticalPadding_.ConvertToPx();
        endX = size.Width() + originX + CHECKBOX_GROUP_DOUBLE_RATIO * hotZoneHorizontalPadding_.ConvertToPx();
        endY = size.Height() + originY + CHECKBOX_GROUP_DOUBLE_RATIO * hotZoneVerticalPadding_.ConvertToPx();
    }
    auto rrect = RSRoundRect({ originX, originY, endX, endY }, hoverRadius_.ConvertToPx(), hoverRadius_.ConvertToPx());
    canvas.AttachBrush(brush);
    DrawRectOrCircle(canvas, rrect);
#ifdef USE_ROSEN_DRAWING
    canvas.DetachBrush();
#endif
}

void CheckBoxGroupModifier::DrawRectOrCircle(RSCanvas& canvas, const RSRoundRect& rrect) const
{
    if (CheckBoxStyle::SQUARE_STYLE == checkBoxGroupStyle_) {
        canvas.DrawRoundRect(rrect);
    } else {
        RSScalar halfDenominator = 2.0f;
        RSRect rect = rrect.GetRect();
        RSScalar x = (rect.GetLeft() + rect.GetRight()) / halfDenominator;
        RSScalar y = (rect.GetTop() + rect.GetBottom()) / halfDenominator;
        RSPoint centerPt(x, y);
        RSScalar radius = std::min(rect.GetWidth(), rect.GetHeight()) / halfDenominator;
        canvas.DrawCircle(centerPt, radius);
    }
}
} // namespace OHOS::Ace::NG
