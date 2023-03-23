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

#include "base/utils/utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/render/drawing.h"
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
constexpr float CHECK_MARK_LEFT_ANIMATION_PERCENT = 0.45;
constexpr float CHECK_MARK_RIGHT_ANIMATION_PERCENT = 0.55;
constexpr float DEFAULT_MAX_CHECKBOX_SHAPE_SCALE = 1.0;
constexpr float DEFAULT_MIN_CHECKBOX_SHAPE_SCALE = 0.0;
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
    shapeScale_ = AceType::MakeRefPtr<PropertyFloat>(DEFAULT_MAX_CHECKBOX_SHAPE_SCALE);
    isTouch_ = AceType::MakeRefPtr<PropertyBool>(false);
    isHover_ = AceType::MakeRefPtr<PropertyBool>(false);
    enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    uiStatus_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(parameters.uiStatus));
    status_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int>(UIStatus::UNSELECTED));
    offset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    size_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());

    borderWidth_ = parameters.borderWidth;
    borderRadius_ = parameters.borderRadius;
    shadowColor_ = parameters.shadowColor;
    clickEffectColor_ = parameters.clickEffectColor;
    hoverColor_ = parameters.hoverColor;
    inactivePointColor_ = parameters.inactivePointColor;
    hoverRadius_ = parameters.hoverRadius;
    hotZoneHorizontalPadding_ = parameters.hotZoneHorizontalPadding;
    hotZoneVerticalPadding_ = parameters.hotZoneVerticalPadding;
    shadowWidth_ = parameters.shadowWidth;

    AttachProperty(activeColor_);
    AttachProperty(pointColor_);
    AttachProperty(inactiveColor_);
    AttachProperty(checkMarkPaintSize_);
    AttachProperty(checkStroke_);
    AttachProperty(shapeScale_);
    AttachProperty(isTouch_);
    AttachProperty(isHover_);
    AttachProperty(enabled_);
    AttachProperty(uiStatus_);
    AttachProperty(status_);
    AttachProperty(offset_);
    AttachProperty(size_);
}

void CheckBoxGroupModifier::PaintCheckBox(
    DrawingContext& context, const OffsetF& paintOffset, const SizeF& contentSize) const
{
    auto canvas = context.canvas;
    auto color = activeColor_;

    RSPen pen;
    RSBrush brush;
    pen.SetWidth(borderWidth_);
    pen.SetAntiAlias(true);
    if (isTouch_->Get()) {
        LOGI("Touch effect is to be realized here");
    }
    if (isHover_->Get()) {
        DrawHoverBoard(canvas, contentSize, paintOffset);
    }
    if (CheckBoxGroupPaintProperty::SelectStatus(status_->Get()) == CheckBoxGroupPaintProperty::SelectStatus::PART) {
        PaintCheckBoxGroupPartStatus(canvas, paintOffset, brush, pen, contentSize);
        return;
    }
    if (UIStatus(uiStatus_->Get()) == UIStatus::OFF_TO_ON || UIStatus(uiStatus_->Get()) == UIStatus::PART_TO_ON) {
        brush.SetColor(ToRSColor(color->Get()));
        brush.SetAntiAlias(true);
        pen.SetColor(ToRSColor(pointColor_->Get()));
        if (!enabled_->Get()) {
            brush.SetColor(ToRSColor(color->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        }
        DrawActiveBorder(canvas, paintOffset, brush, contentSize);
        DrawAnimationOffToOn(canvas, paintOffset, pen, contentSize);
    } else if (UIStatus(uiStatus_->Get()) == UIStatus::ON_TO_OFF) {
        brush.SetColor(ToRSColor(color->Get()));
        brush.SetAntiAlias(true);
        pen.SetColor(ToRSColor(pointColor_->Get()));
        if (!enabled_->Get()) {
            brush.SetColor(ToRSColor(color->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        }
        DrawActiveBorder(canvas, paintOffset, brush, contentSize);
        DrawAnimationOnToOff(canvas, paintOffset, pen, contentSize);
    } else if (UIStatus(uiStatus_->Get()) == UIStatus::UNSELECTED ||
               UIStatus(uiStatus_->Get()) == UIStatus::PART_TO_OFF) {
        brush.SetColor(ToRSColor(inactivePointColor_));
        pen.SetColor(ToRSColor(inactiveColor_->Get()));
        if (!enabled_->Get()) {
            brush.SetColor(
                ToRSColor(inactivePointColor_.BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
            pen.SetColor(
                ToRSColor(inactiveColor_->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
        }
        DrawUnselectedBorder(canvas, paintOffset, brush, contentSize);
        DrawUnselected(canvas, paintOffset, pen, contentSize);
    }
}

void CheckBoxGroupModifier::PaintCheckBoxGroupPartStatus(
    RSCanvas& canvas, const OffsetF& paintOffset, RSBrush& brush, RSPen pen, const SizeF& paintSize) const
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
    canvas.DrawRoundRect(rrect);
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
    canvas.DrawRoundRect(rrect);
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
    canvas.DrawRoundRect(rrect);
}

void CheckBoxGroupModifier::DrawPart(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const
{
    if (checkMarkPaintSize_->Get() == CHECKBOX_GROUP_LENGTH_ZERO || checkStroke_->Get() == CHECKBOX_GROUP_LENGTH_ZERO) {
        return;
    }
    RSPath path;
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
}

void CheckBoxGroupModifier::DrawMark(RSCanvas& canvas, RSPath& path, RSPen& pen) const
{
    if (checkMarkPaintSize_->Get() == CHECKBOX_GROUP_LENGTH_ZERO || checkStroke_->Get() == CHECKBOX_GROUP_LENGTH_ZERO) {
        return;
    }
    RSPen shadowPen = RSPen(pen);
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    shadowPen.SetWidth(checkStroke_->Get() + shadowWidth_.ConvertToPx() * CHECKBOX_GROUP_DOUBLE_RATIO);
    shadowPen.SetColor(ToRSColor(shadowColor_));
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(path);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
}

void CheckBoxGroupModifier::DrawAnimationOffToOn(
    RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const
{
    RSPath path;
    float originX = origin.GetX();
    float originY = origin.GetY();
    const Offset start = Offset(checkMarkPaintSize_->Get() * CHECK_MARK_START_X_POSITION,
        checkMarkPaintSize_->Get() * CHECK_MARK_START_Y_POSITION);
    const Offset middle = Offset(checkMarkPaintSize_->Get() * CHECK_MARK_MIDDLE_X_POSITION,
        checkMarkPaintSize_->Get() * CHECK_MARK_MIDDLE_Y_POSITION);
    const Offset end = Offset(
        checkMarkPaintSize_->Get() * CHECK_MARK_END_X_POSITION, checkMarkPaintSize_->Get() * CHECK_MARK_END_Y_POSITION);

    float deltaX = middle.GetX() - start.GetX();
    float deltaY = middle.GetY() - start.GetY();
    path.MoveTo(originX + start.GetX() + (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO,
        originY + start.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO);
    pen.SetWidth(checkStroke_->Get());
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    float ratio = DEFAULT_MIN_CHECKBOX_SHAPE_SCALE;
    if (shapeScale_->Get() < CHECK_MARK_LEFT_ANIMATION_PERCENT) {
        ratio = shapeScale_->Get() / CHECK_MARK_LEFT_ANIMATION_PERCENT;
        path.LineTo(originX + start.GetX() +
                        (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO + deltaX * ratio,
            originY + start.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO +
                deltaY * ratio);
    } else {
        path.LineTo(
            originX + middle.GetX() + (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO,
            originY + middle.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO);
    }
    DrawMark(canvas, path, pen);
    if (shapeScale_->Get() > CHECK_MARK_LEFT_ANIMATION_PERCENT) {
        deltaX = end.GetX() - middle.GetX();
        deltaY = middle.GetY() - end.GetY();
        path.MoveTo(
            originX + middle.GetX() + (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO,
            originY + middle.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO);
        if (shapeScale_->Get() == DEFAULT_MAX_CHECKBOX_SHAPE_SCALE) {
            path.LineTo(
                originX + (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO + end.GetX(),
                originY + end.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO);
        } else {
            ratio = (shapeScale_->Get() - CHECK_MARK_LEFT_ANIMATION_PERCENT) / CHECK_MARK_RIGHT_ANIMATION_PERCENT;
            path.LineTo(originX + (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO +
                            middle.GetX() + deltaX * ratio,
                originY + middle.GetY() +
                    (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO - deltaY * ratio);
        }
        DrawMark(canvas, path, pen);
    }
}

void CheckBoxGroupModifier::DrawAnimationOnToOff(RSCanvas& canvas, const OffsetF& origin, RSPen& pen,
    const SizeF& paintSize) const
{
    if (shapeScale_->Get() == DEFAULT_MIN_CHECKBOX_SHAPE_SCALE ||
        checkMarkPaintSize_->Get() == CHECKBOX_GROUP_LENGTH_ZERO || checkStroke_->Get() == CHECKBOX_GROUP_LENGTH_ZERO) {
        return;
    }
    RSPath path;
    RSPen shadowPen = RSPen(pen);
    float originX = origin.GetX();
    float originY = origin.GetY();
    const Offset start = Offset(checkMarkPaintSize_->Get() * CHECK_MARK_START_X_POSITION,
        checkMarkPaintSize_->Get() * CHECK_MARK_START_Y_POSITION);
    const Offset middle = Offset(checkMarkPaintSize_->Get() * CHECK_MARK_MIDDLE_X_POSITION,
        checkMarkPaintSize_->Get() * CHECK_MARK_MIDDLE_Y_POSITION);
    const Offset end = Offset(
        checkMarkPaintSize_->Get() * CHECK_MARK_END_X_POSITION, checkMarkPaintSize_->Get() * CHECK_MARK_END_Y_POSITION);
    const Offset middlePoint = Offset(checkMarkPaintSize_->Get() / CHECKBOX_GROUP_DOUBLE_RATIO,
        checkMarkPaintSize_->Get() / CHECKBOX_GROUP_DOUBLE_RATIO);
    float deltaX = middlePoint.GetX() - start.GetX();
    float deltaY = middlePoint.GetY() - start.GetY();
    float ratio = DEFAULT_MAX_CHECKBOX_SHAPE_SCALE - shapeScale_->Get();
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    shadowPen.SetWidth(checkStroke_->Get() + shadowWidth_.ConvertToPx() * CHECKBOX_GROUP_DOUBLE_RATIO);
    shadowPen.SetColor(ToRSColor(shadowColor_));
    pen.SetWidth(checkStroke_->Get());
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    path.MoveTo(originX + start.GetX() +
                    (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO + deltaX * ratio,
        originY + start.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO +
            deltaY * ratio);
    deltaX = middlePoint.GetX() - middle.GetX();
    deltaY = middle.GetY() - middlePoint.GetY();
    path.LineTo(originX + middle.GetX() +
                    (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO + deltaX * ratio,
        originY + middle.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO -
            deltaY * ratio);
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(path);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    path.MoveTo(originX + middle.GetX() +
                    (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO + deltaX * ratio,
        originY + middle.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO -
            deltaY * ratio);
    deltaX = end.GetX() - middlePoint.GetX();
    deltaY = middlePoint.GetY() - end.GetY();
    path.LineTo(originX + end.GetX() + (paintSize.Width() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO -
                    deltaX * ratio,
        originY + end.GetY() + (paintSize.Height() - checkMarkPaintSize_->Get()) / CHECKBOX_GROUP_DOUBLE_RATIO +
            deltaY * ratio);
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(path);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
}

void CheckBoxGroupModifier::DrawTouchBoard(RSCanvas& canvas, const SizeF& size, const OffsetF& offset) const
{
    RSBrush brush;
    brush.SetColor(ToRSColor(Color(clickEffectColor_)));
    brush.SetAntiAlias(true);
    float originX = offset.GetX() - hotZoneHorizontalPadding_.ConvertToPx();
    float originY = offset.GetY() - hotZoneVerticalPadding_.ConvertToPx();
    float endX = size.Width() + originX + CHECKBOX_GROUP_DOUBLE_RATIO * hotZoneHorizontalPadding_.ConvertToPx();
    float endY = size.Height() + originY + CHECKBOX_GROUP_DOUBLE_RATIO * hotZoneVerticalPadding_.ConvertToPx();
    RSRect rect(originX, originY, endX, endY);
    auto rrect = RSRoundRect(rect, hoverRadius_.ConvertToPx(), hoverRadius_.ConvertToPx());
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(rrect);
}

void CheckBoxGroupModifier::DrawHoverBoard(RSCanvas& canvas, const SizeF& size, const OffsetF& offset) const
{
    RSBrush brush;
    brush.SetColor(ToRSColor(Color(hoverColor_)));
    brush.SetAntiAlias(true);
    float originX = offset.GetX() - hotZoneHorizontalPadding_.ConvertToPx();
    float originY = offset.GetY() - hotZoneVerticalPadding_.ConvertToPx();
    float endX = size.Width() + originX + CHECKBOX_GROUP_DOUBLE_RATIO * hotZoneHorizontalPadding_.ConvertToPx();
    float endY = size.Height() + originY + CHECKBOX_GROUP_DOUBLE_RATIO * hotZoneVerticalPadding_.ConvertToPx();
    RSRect rect(originX, originY, endX, endY);
    auto rrect = RSRoundRect(rect, hoverRadius_.ConvertToPx(), hoverRadius_.ConvertToPx());
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(rrect);
}
} // namespace OHOS::Ace::NG
