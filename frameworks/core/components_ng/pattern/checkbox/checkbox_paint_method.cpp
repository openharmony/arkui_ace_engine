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
#include "core/components_ng/pattern/checkbox/checkbox_paint_method.h"

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
constexpr float CHECKBOX_DOUBLE_RATIO = 2.0f;
constexpr float CHECKBOX_LENGTH_ZERO = 0.0f;
} // namespace

CheckBoxModifier::CheckBoxModifier(bool isSelect, const Color& boardColor, const Color& checkColor,
    const Color& borderColor, const Color& shadowColor, const SizeF& size, const OffsetF& offset, float checkStroke,
    float strokeSize)
{
    animatableBoardColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(boardColor));
    animatableCheckColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(checkColor));
    animatableBorderColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(borderColor));
    animatableShadowColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(shadowColor));
    checkStroke_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(checkStroke);
    strokeSize_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(strokeSize);
    offset_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(offset);
    size_ = AceType::MakeRefPtr<AnimatablePropertySizeF>(size);
    animateTouchHoverColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));

    isSelect_ = AceType::MakeRefPtr<PropertyBool>(isSelect);
    isFocused_ = AceType::MakeRefPtr<PropertyBool>(false);
    enabled_ = AceType::MakeRefPtr<PropertyBool>(true);
    hasBuilder_ = AceType::MakeRefPtr<PropertyBool>(false);
    useContentModifier_ = AceType::MakeRefPtr<PropertyBool>(false);
    checkBoxShape_ = AceType::MakeRefPtr<PropertyInt>(static_cast<int32_t>(CheckBoxStyle::CIRCULAR_STYLE));

    AttachProperty(animatableBoardColor_);
    AttachProperty(animatableCheckColor_);
    AttachProperty(animatableBorderColor_);
    AttachProperty(animatableShadowColor_);
    AttachProperty(animateTouchHoverColor_);
    AttachProperty(checkStroke_);
    AttachProperty(strokeSize_);
    AttachProperty(isSelect_);
    AttachProperty(isFocused_);
    AttachProperty(offset_);
    AttachProperty(size_);
    AttachProperty(enabled_);
    AttachProperty(hasBuilder_);
    AttachProperty(checkBoxShape_);
}

void CheckBoxModifier::InitializeParam()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    borderWidth_ = checkBoxTheme->GetBorderWidth().ConvertToPx();
    borderRadius_ = checkBoxTheme->GetBorderRadius().ConvertToPx();
    whiteBorderRadius_ = checkBoxTheme->GetWhiteBorderRadius().ConvertToPx();
    pointColor_ = checkBoxTheme->GetPointColor();
    activeColor_ = checkBoxTheme->GetActiveColor();
    inactiveColor_ = checkBoxTheme->GetInactiveColor();
    inactivePointColor_ = checkBoxTheme->GetInactivePointColor();
    shadowColor_ = checkBoxTheme->GetShadowColor();
    clickEffectColor_ = checkBoxTheme->GetClickEffectColor();
    hoverColor_ = checkBoxTheme->GetHoverColor();
    hoverRadius_ = checkBoxTheme->GetHoverRadius();
    hotZoneHorizontalPadding_ = checkBoxTheme->GetHotZoneHorizontalPadding();
    hotZoneVerticalPadding_ = checkBoxTheme->GetHotZoneVerticalPadding();
    defaultPaddingSize_ = checkBoxTheme->GetDefaultPaddingSize();
    defaultRoundPaddingSize_ = checkBoxTheme->GetDefaultRoundPaddingSize();
    shadowWidth_ = checkBoxTheme->GetShadowWidth();
    userActiveColor_ = activeColor_;
    hoverDuration_ = checkBoxTheme->GetHoverDuration();
    hoverToTouchDuration_ = checkBoxTheme->GetHoverToTouchDuration();
    touchDuration_ = checkBoxTheme->GetTouchDuration();
    colorAnimationDuration_ = checkBoxTheme->GetColorAnimationDuration();
    focusBoardColor_ = checkBoxTheme->GetFocusBoardColor();
    focusBoardSize_ = checkBoxTheme->GetFocusBoardSize();
    roundFocusBoardSize_ = checkBoxTheme->GetRoundFocusBoardSize();
    borderFocusedColor_ = checkBoxTheme->GetBorderFocusedColor();
    focusedBGColorUnselected_ = checkBoxTheme->GetFocusedBGColorUnselected();
}

void CheckBoxModifier::PaintCheckBox(RSCanvas& canvas, const OffsetF& paintOffset, const SizeF& contentSize) const
{
    DrawFocusBoard(canvas, contentSize, paintOffset);
    DrawTouchAndHoverBoard(canvas, contentSize, paintOffset);
    RSPen pen;
    pen.SetWidth(borderWidth_);
    pen.SetAntiAlias(true);
    RSPen shadowPen = RSPen(pen);
    RSBrush brush;
    brush.SetColor(ToRSColor(animatableBoardColor_->Get()));
    brush.SetAntiAlias(true);
    if (!enabled_->Get()) {
        brush.SetColor(
            ToRSColor(animatableBoardColor_->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
    }
    if (isFocused_->Get() && !isSelect_->Get()) {
        brush.SetColor(ToRSColor(focusedBGColorUnselected_));
    }
    DrawBackboard(canvas, paintOffset, brush, contentSize);
    pen.SetColor(ToRSColor(animatableBorderColor_->Get()));
    if (!enabled_->Get()) {
        pen.SetColor(
            ToRSColor(animatableBorderColor_->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
    }
    if (!isSelect_->Get() && isFocused_->Get() && !hasUnselectedColor_) {
        pen.SetColor(ToRSColor(borderFocusedColor_));
    }
    if (enabled_->Get() || !isSelect_->Get()) {
        DrawBorder(canvas, paintOffset, pen, contentSize);
    }
    pen.SetColor(ToRSColor(animatableCheckColor_->Get()));
    shadowPen.SetColor(ToRSColor(animatableShadowColor_->Get()));
    if (!hasBuilder_->Get()) {
        DrawCheck(canvas, paintOffset, pen, shadowPen, contentSize);
    }
}

void CheckBoxModifier::DrawFocusBoard(RSCanvas& canvas, const SizeF& size, const OffsetF& offset) const
{
    RSBrush brush;
    if (isFocused_->Get()) {
        brush.SetColor(ToRSColor(focusBoardColor_));
    } else {
        brush.SetColor(ToRSColor(Color::TRANSPARENT));
    }
    brush.SetAntiAlias(true);
    auto bgSizeOffset = (checkBoxShape_->Get() == static_cast<int32_t>(CheckBoxStyle::SQUARE_STYLE)) ?
        focusBoardSize_.ConvertToPx() : roundFocusBoardSize_.ConvertToPx();
    float originX = offset.GetX() - bgSizeOffset;
    float originY = offset.GetY() - bgSizeOffset;
    float endX = offset.GetX() + bgSizeOffset + size.Width();
    float endY = offset.GetY() + bgSizeOffset + size.Height();
    float useFocusBoardRadoius = whiteBorderRadius_ + bgSizeOffset;
    auto rrect = RSRoundRect({ originX, originY, endX, endY }, useFocusBoardRadoius, useFocusBoardRadoius);

    canvas.AttachBrush(brush);
    DrawRectOrCircle(canvas, rrect);
    canvas.DetachBrush();
}

void CheckBoxModifier::DrawTouchAndHoverBoard(RSCanvas& canvas, const SizeF& size, const OffsetF& offset) const
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
    auto defaultPadding = (checkBoxShape_->Get() == static_cast<int32_t>(CheckBoxStyle::SQUARE_STYLE)) ?
        defaultPaddingSize_.ConvertToPx() : defaultRoundPaddingSize_.ConvertToPx();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        originX = offset.GetX() - defaultPadding;
        originY = offset.GetY() - defaultPadding;
        endX = size.Width() + originX + CHECKBOX_DOUBLE_RATIO * defaultPadding;
        endY = size.Height() + originY + CHECKBOX_DOUBLE_RATIO * defaultPadding;
    } else {
        originX = offset.GetX() - hotZoneHorizontalPadding_.ConvertToPx();
        originY = offset.GetY() - hotZoneVerticalPadding_.ConvertToPx();
        endX = size.Width() + originX + CHECKBOX_DOUBLE_RATIO * hotZoneHorizontalPadding_.ConvertToPx();
        endY = size.Height() + originY + CHECKBOX_DOUBLE_RATIO * hotZoneVerticalPadding_.ConvertToPx();
    }
    auto rrect = RSRoundRect({ originX, originY, endX, endY }, hoverRadius_.ConvertToPx(), hoverRadius_.ConvertToPx());
    canvas.AttachBrush(brush);
    DrawRectOrCircle(canvas, rrect);
    canvas.DetachBrush();
}

void CheckBoxModifier::DrawBorder(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const
{
    float originX = origin.GetX() + borderWidth_ / CHECKBOX_DOUBLE_RATIO;
    float originY = origin.GetY() + borderWidth_ / CHECKBOX_DOUBLE_RATIO;
    float endX = originX + paintSize.Width() - borderWidth_;
    float endY = originY + paintSize.Height() - borderWidth_;
    auto rrect = RSRoundRect({ originX, originY, endX, endY }, borderRadius_, borderRadius_);
    canvas.AttachPen(pen);
    DrawRectOrCircle(canvas, rrect);
    canvas.DetachPen();
}

void CheckBoxModifier::DrawBackboard(
    RSCanvas& canvas, const OffsetF& origin, RSBrush& brush, const SizeF& paintSize) const
{
    float originX = origin.GetX();
    float originY = origin.GetY();
    float endX = originX + paintSize.Width();
    float endY = originY + paintSize.Height();
    auto rrect = RSRoundRect({ originX, originY, endX, endY }, borderRadius_, borderRadius_);
    canvas.AttachBrush(brush);
    DrawRectOrCircle(canvas, rrect);
    canvas.DetachBrush();
}

void CheckBoxModifier::DrawCheck(
    RSCanvas& canvas, const OffsetF& origin, RSPen& pen, RSPen& shadowPen, const SizeF& paintSize) const
{
    if (strokeSize_->Get() == CHECKBOX_LENGTH_ZERO || checkStroke_->Get() == CHECKBOX_LENGTH_ZERO) {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkbox draw check zero %{public}f %{public}f", strokeSize_->Get(),
            checkStroke_->Get());
        return;
    }
#ifndef USE_ROSEN_DRAWING
    RSPath path;
#else
    RSRecordingPath path;
#endif
    float originX = origin.GetX();
    float originY = origin.GetY();
    float strokeSize = strokeSize_->Get();
    const Offset start = Offset(strokeSize * CHECK_MARK_START_X_POSITION, strokeSize * CHECK_MARK_START_Y_POSITION);
    const Offset middle = Offset(strokeSize * CHECK_MARK_MIDDLE_X_POSITION, strokeSize * CHECK_MARK_MIDDLE_Y_POSITION);
    const Offset end = Offset(strokeSize * CHECK_MARK_END_X_POSITION, strokeSize * CHECK_MARK_END_Y_POSITION);
    path.MoveTo(originX + start.GetX() + (paintSize.Width() - strokeSize) / CHECKBOX_DOUBLE_RATIO,
        originY + start.GetY() + (paintSize.Height() - strokeSize) / CHECKBOX_DOUBLE_RATIO);
    path.LineTo(originX + middle.GetX() + (paintSize.Width() - strokeSize) / CHECKBOX_DOUBLE_RATIO,
        originY + middle.GetY() + (paintSize.Height() - strokeSize) / CHECKBOX_DOUBLE_RATIO);
    path.MoveTo(originX + middle.GetX() + (paintSize.Width() - strokeSize) / CHECKBOX_DOUBLE_RATIO,
        originY + middle.GetY() + (paintSize.Height() - strokeSize) / CHECKBOX_DOUBLE_RATIO);
    path.LineTo(originX + end.GetX() + (paintSize.Width() - strokeSize) / CHECKBOX_DOUBLE_RATIO,
        originY + end.GetY() + (paintSize.Height() - strokeSize) / CHECKBOX_DOUBLE_RATIO);
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    shadowPen.SetWidth(checkStroke_->Get() + shadowWidth_.ConvertToPx() * CHECKBOX_DOUBLE_RATIO);
    pen.SetWidth(checkStroke_->Get());
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(path);
    canvas.DetachPen();
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();
}

void CheckBoxModifier::DrawRectOrCircle(RSCanvas& canvas, const RSRoundRect& rrect) const
{
    if (CheckBoxStyle::SQUARE_STYLE == checkBoxStyle_) {
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
