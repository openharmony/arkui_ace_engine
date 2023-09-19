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

#include "core/components_ng/pattern/text_field/text_field_overlay_modifier.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_painter.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"

namespace OHOS::Ace::NG {
TextFieldOverlayModifier::TextFieldOverlayModifier(
    const WeakPtr<OHOS::Ace::NG::Pattern>& pattern, WeakPtr<ScrollEdgeEffect>&& edgeEffect)
    : pattern_(pattern), edgeEffect_(edgeEffect)
{
    cursorColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color()));
    cursorWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(static_cast<float>(CURSOR_WIDTH.ConvertToPx()));
    selectedColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color()));
    cursorVisible_ = AceType::MakeRefPtr<PropertyBool>(false);
    contentSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    contentOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(OffsetF());
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    cursorOffset_ = AceType::MakeRefPtr<PropertyOffsetF>(textFieldPattern->GetCaretOffset());
    frameSize_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    currentOffset_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    flag_ = AceType::MakeRefPtr<PropertyInt>(0);
    underlineWidth_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    underlineColor_ = AceType::MakeRefPtr<PropertyColor>(Color());
    showCounter_ = AceType::MakeRefPtr<PropertyBool>(false);

    AttachProperty(cursorColor_);
    AttachProperty(cursorWidth_);
    AttachProperty(selectedColor_);
    AttachProperty(cursorVisible_);
    AttachProperty(contentSize_);
    AttachProperty(contentOffset_);
    AttachProperty(cursorOffset_);
    AttachProperty(frameSize_);
    AttachProperty(currentOffset_);
    AttachProperty(flag_);
    AttachProperty(underlineWidth_);
    AttachProperty(underlineColor_);
    AttachProperty(showCounter_);
}

void TextFieldOverlayModifier::onDraw(DrawingContext& context)
{
    PaintCursor(context);
    PaintSelection(context);
    PaintScrollBar(context);
    PaintEdgeEffect(frameSize_->Get(), context.canvas);
    PaintUnderline(context.canvas);
}

void TextFieldOverlayModifier::PaintUnderline(RSCanvas& canvas) const
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!(layoutProperty->GetShowUnderlineValue(false) && textFieldPattern->IsUnspecifiedOrTextType())) {
        return;
    }
    auto textRect = textFieldPattern->GetContentRect();
    auto textFrameRect = textFieldPattern->GetFrameRect();
    Point leftPoint, rightPoint;
    leftPoint.SetX(textRect.Left());
    leftPoint.SetY(textFrameRect.Bottom() - textFrameRect.Top());
    rightPoint.SetX(textRect.Right());
    rightPoint.SetY(textFrameRect.Bottom() - textFrameRect.Top());
    RSPen pen;
    pen.SetColor(ToRSColor(underlineColor_->Get()));
    pen.SetWidth(underlineWidth_->Get());
    pen.SetAntiAlias(true);
    canvas.AttachPen(pen);
    canvas.DrawLine(
        ToRSPoint(PointF(leftPoint.GetX(), leftPoint.GetY())), ToRSPoint(PointF(rightPoint.GetX(), rightPoint.GetY())));
    canvas.DetachPen();
}

void TextFieldOverlayModifier::PaintSelection(DrawingContext& context) const
{
    auto& canvas = context.canvas;
    canvas.Save();
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    if (!textFieldPattern->IsSelected()) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextFieldTheme>();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(selectedColor_->Get()));
    canvas.AttachBrush(brush);
    auto contentOffset = textFieldPattern->GetContentRect().GetOffset();
    auto paintOffset = contentOffset - OffsetF(0.0f, textFieldPattern->GetBaseLineOffset());
    auto textBoxes = textFieldPattern->GetTextBoxes();
    auto textRect = textFieldPattern->GetTextRect();
    bool isTextArea = textFieldPattern->IsTextArea();
    float clipRectHeight = 0.0f;
    if (showCounter_->Get() && textFieldPattern->GetCounterParagraph() &&
        !textFieldPattern->GetIsCounterIdealHeight()) {
        clipRectHeight = paintOffset.GetY() + contentSize_->Get().Height() - textFieldPattern->GetCountHeight();
    } else {
        clipRectHeight = paintOffset.GetY() + contentSize_->Get().Height();
    }
    RSRect clipInnerRect;
    if (inputStyle_ == InputStyle::DEFAULT || isTextArea) {
        clipInnerRect = RSRect(
            paintOffset.GetX(), paintOffset.GetY(), paintOffset.GetX() + contentSize_->Get().Width() +
            textFieldPattern->GetInlinePadding(), clipRectHeight);
        canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    } else {
        clipInnerRect = RSRect(paintOffset.GetX(), 0.0f, paintOffset.GetX() + contentSize_->Get().Width(),
            textFieldPattern->GetFrameRect().Height());
        canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    }
    // for default style, selection height is equal to the content height
    for (const auto& textBox : textBoxes) {
#ifndef USE_GRAPHIC_TEXT_GINE
        canvas.DrawRect(RSRect(textBox.rect_.GetLeft() + (isTextArea ? contentOffset.GetX() : textRect.GetX()),
            inputStyle_ == InputStyle::DEFAULT || isTextArea
                ? (textBox.rect_.GetTop() + (isTextArea ? textRect.GetY() : contentOffset.GetY()))
                : 0.0f,
            textBox.rect_.GetRight() + (isTextArea ? contentOffset.GetX() : textRect.GetX()),
            inputStyle_ == InputStyle::DEFAULT || isTextArea
                ? (textBox.rect_.GetBottom() + (isTextArea ? textRect.GetY() : contentOffset.GetY()))
                : textFieldPattern->GetFrameRect().Height()));
#else
        canvas.DrawRect(RSRect(textBox.rect.GetLeft() + (isTextArea ? contentOffset.GetX() : textRect.GetX()),
            inputStyle_ == InputStyle::DEFAULT || isTextArea
                ? (textBox.rect.GetTop() + (isTextArea ? textRect.GetY() : contentOffset.GetY()))
                : 0.0f,
            textBox.rect.GetRight() + (isTextArea ? contentOffset.GetX() : textRect.GetX()),
            inputStyle_ == InputStyle::DEFAULT || isTextArea
                ? (textBox.rect.GetBottom() + (isTextArea ? textRect.GetY() : contentOffset.GetY()))
                : textFieldPattern->GetFrameRect().Height()));
#endif
    }
    canvas.Restore();
}

void TextFieldOverlayModifier::PaintCursor(DrawingContext& context) const
{
    auto& canvas = context.canvas;
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    if (!cursorVisible_->Get() || textFieldPattern->GetSelectMode() == SelectionMode::SELECT_ALL) {
        return;
    }
    canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(cursorColor_->Get()));
    canvas.AttachBrush(brush);
    auto paintOffset = contentOffset_->Get() - OffsetF(0.0f, textFieldPattern->GetBaseLineOffset());
    float clipRectHeight = 0.0f;
    if (showCounter_->Get() && textFieldPattern->GetCounterParagraph() &&
        !textFieldPattern->GetIsCounterIdealHeight()) {
        clipRectHeight = paintOffset.GetY() + contentSize_->Get().Height() - textFieldPattern->GetCountHeight();
    } else {
        clipRectHeight = paintOffset.GetY() + contentSize_->Get().Height();
    }
    RSRect clipInnerRect(paintOffset.GetX(), paintOffset.GetY(),
        // add extra clip space for cases such as auto width
        paintOffset.GetX() + contentSize_->Get().Width() + cursorWidth_->Get() * 2.0f -
        textFieldPattern->GetUnitWidth(), clipRectHeight);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    auto caretRect = textFieldPattern->GetCaretRect();
    canvas.DrawRect(RSRect(cursorOffset_->Get().GetX(), caretRect.GetY(),
        cursorOffset_->Get().GetX() + static_cast<float>(cursorWidth_->Get()), caretRect.GetY() + caretRect.Height()));
    canvas.DetachBrush();
    canvas.Restore();
}

void TextFieldOverlayModifier::PaintEdgeEffect(const SizeF& frameSize, RSCanvas& canvas)
{
    auto edgeEffect = edgeEffect_.Upgrade();
    CHECK_NULL_VOID(edgeEffect);
    edgeEffect->Paint(canvas, frameSize, { 0.0f, 0.0f });
}

void TextFieldOverlayModifier::PaintScrollBar(DrawingContext& context)
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    if (textFieldPattern->GetScrollBarVisible()) {
        ScrollBarOverlayModifier::onDraw(context);
    }
}

void TextFieldOverlayModifier::SetCursorColor(Color& value)
{
    cursorColor_->Set(LinearColor(value));
}

void TextFieldOverlayModifier::SetCursorWidth(float value)
{
    cursorWidth_->Set(value);
}

void TextFieldOverlayModifier::SetSelectedBackGroundColor(Color& value)
{
    selectedColor_->Set(LinearColor(value));
}

void TextFieldOverlayModifier::SetCursorVisible(bool value)
{
    cursorVisible_->Set(value);
}

void TextFieldOverlayModifier::SetContentSize(SizeF& value)
{
    contentSize_->Set(value);
}

void TextFieldOverlayModifier::SetContentOffset(OffsetF& value)
{
    contentOffset_->Set(value);
}

void TextFieldOverlayModifier::SetCursorOffset(OffsetF& value)
{
    cursorOffset_->Set(value);
}

void TextFieldOverlayModifier::SetInputStyle(InputStyle& value)
{
    inputStyle_ = value;
}

void TextFieldOverlayModifier::SetFrameSize(const SizeF& value)
{
    frameSize_->Set(value);
}

void TextFieldOverlayModifier::SetCurrentOffset(float value)
{
    currentOffset_->Set(value);
}

void TextFieldOverlayModifier::SetRedrawFlag(int32_t value)
{
    flag_->Set(value);
}

void TextFieldOverlayModifier::SetUnderlineWidth(float value)
{
    underlineWidth_->Set(value);
}

void TextFieldOverlayModifier::SetUnderlineColor(const Color& value)
{
    underlineColor_->Set(value);
}

void TextFieldOverlayModifier::SetShowCounter(bool value)
{
    showCounter_->Set(value);
}

void TextFieldOverlayModifier::SetScrollBar(const RefPtr<ScrollBar>& scrollBar)
{
    scrollBar_ = scrollBar;
}
} // namespace OHOS::Ace::NG
