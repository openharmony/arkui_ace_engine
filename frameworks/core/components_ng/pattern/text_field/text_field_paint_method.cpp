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
#include "core/components_ng/pattern/text_field/text_field_paint_method.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/rect.h"
#include "base/geometry/rrect.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
TextFieldPaintMethod::TextFieldPaintMethod(const WeakPtr<Pattern>& pattern,
    const RefPtr<TextFieldOverlayModifier>& textFieldOverlayModifier,
    const RefPtr<TextFieldContentModifier>& textFieldContentModifier,
    const RefPtr<TextFieldForegroundModifier>& textFieldForegroundModifier)
    : pattern_(pattern), textFieldOverlayModifier_(textFieldOverlayModifier),
      textFieldContentModifier_(textFieldContentModifier), textFieldForegroundModifier_(textFieldForegroundModifier)
{}

RefPtr<Modifier> TextFieldPaintMethod::GetContentModifier(PaintWrapper* paintWrapper)
{
    return textFieldContentModifier_;
}

void TextFieldPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    CHECK_NULL_VOID(textFieldContentModifier_);
    auto paintProperty = DynamicCast<TextFieldPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    OffsetF contentOffset = paintWrapper->GetContentOffset();
    SizeF contentSize = paintWrapper->GetContentSize();
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    if (textFieldPattern->GetContChange()) {
        textFieldContentModifier_->ChangeDragStatus();
        textFieldPattern->ResetContChange();
    }

    auto textFieldLayoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto textValue = textFieldPattern->GetTextUtf16Value();
    auto isPasswordType = textFieldPattern->IsInPasswordMode();
    auto showPlaceHolder = textFieldLayoutProperty->GetValueValue(u"").empty();
    auto needObscureText = isPasswordType && textFieldPattern->GetTextObscured() && !showPlaceHolder;
    auto frameNode = textFieldPattern->GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    auto text = TextFieldPattern::CreateDisplayText(
        textValue, textFieldPattern->GetNakedCharPosition(), needObscureText, theme->IsShowPasswordDirectly());
    auto displayText = text;
    textFieldContentModifier_->SetTextValue(displayText);
    textFieldContentModifier_->SetPlaceholderValue(textFieldPattern->GetPlaceHolder());

    auto currentTextRectOffsetX = textFieldPattern->GetTextRect().GetX();
    auto currentTextRectOffsetY =
        textFieldPattern->IsTextArea() ? textFieldPattern->GetTextRect().GetY() : contentOffset.GetY();
    if (textFieldContentModifier_->GetTextRectX() != currentTextRectOffsetX ||
        (textFieldPattern->IsTextArea() ? textFieldContentModifier_->GetTextRectY()
                                        : textFieldContentModifier_->GetContentOffsetY()) != currentTextRectOffsetY) {
        auto searchField = DynamicCast<SearchTextFieldPattern>(textFieldPattern);
        if (searchField) {
            auto parentFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetParent());
            CHECK_NULL_VOID(parentFrameNode);
            auto searchPattern = parentFrameNode->GetPattern<SearchPattern>();
            CHECK_NULL_VOID(searchPattern);
            auto textFieldOffset = searchPattern->GetTextFieldOffset();
            currentTextRectOffsetX += textFieldOffset.GetX();
            currentTextRectOffsetY += textFieldOffset.GetY();
        }
        auto eventHub = frameNode->GetOrCreateEventHub<TextFieldEventHub>();
        eventHub->FireOnScrollChangeEvent(currentTextRectOffsetX, currentTextRectOffsetY);
    }
    textFieldContentModifier_->SetContentOffset(contentOffset);
    textFieldContentModifier_->SetContentSize(contentSize);
    textFieldContentModifier_->SetTextRectY(textFieldPattern->GetTextRect().GetY());
    textFieldContentModifier_->SetTextRectX(textFieldPattern->GetTextRect().GetX());
    textFieldContentModifier_->SetTextAlign(textFieldPattern->GetTextAlign());
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    textFieldContentModifier_->SetTextObscured(textFieldPattern->GetTextObscured());
    textFieldContentModifier_->SetShowErrorState(
        layoutProperty->GetShowErrorTextValue(false) && !textFieldPattern->IsNormalInlineState());
    textFieldContentModifier_->SetErrorTextValue(layoutProperty->GetErrorTextValue(u""));
    textFieldContentModifier_->SetShowUnderlineState(layoutProperty->GetShowUnderlineValue(false));
    DoTextFadeoutIfNeed(paintWrapper);
    PropertyChangeFlag flag = 0;
    if (textFieldContentModifier_->NeedMeasureUpdate(flag)) {
        frameNode->MarkDirtyNode(flag);
    }
}

RefPtr<Modifier> TextFieldPaintMethod::GetOverlayModifier(PaintWrapper* paintWrapper)
{
    return textFieldOverlayModifier_;
}

void TextFieldPaintMethod::SetShowUnderlineWidth()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto textFieldLayoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (textFieldLayoutProperty->HasShowUnderline() && textFieldLayoutProperty->GetShowUnderlineValue()) {
        textFieldOverlayModifier_->SetUnderlineWidth(textFieldPattern->GetUnderlineWidth());
        textFieldOverlayModifier_->SetUnderlineColor(textFieldPattern->GetUnderlineColor());
    } else {
        textFieldOverlayModifier_->SetUnderlineWidth(0.0f);
    }
}

void TextFieldPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    CHECK_NULL_VOID(textFieldOverlayModifier_);

    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto paintProperty = DynamicCast<TextFieldPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto frameNode = textFieldPattern->GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);

    OffsetF contentOffset = paintWrapper->GetContentOffset();
    textFieldOverlayModifier_->SetContentOffset(contentOffset);
    SizeF contentSize = paintWrapper->GetContentSize();
    textFieldOverlayModifier_->SetContentSize(contentSize);
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    textFieldOverlayModifier_->SetFrameSize(frameSize);
    auto currentOffset = textFieldPattern->GetCurrentOffset();
    textFieldOverlayModifier_->SetCurrentOffset(currentOffset);

    auto cursorVisible = textFieldPattern->GetCursorVisible();
    textFieldOverlayModifier_->SetCursorVisible(cursorVisible);
    auto cursorRect = textFieldPattern->GetCaretRect();
    textFieldOverlayModifier_->SetCursorOffset(cursorRect.GetOffset());
    textFieldOverlayModifier_->SetCursorWidth(cursorRect.Width());
    auto cursorColor = paintProperty->GetCursorColorValue(theme->GetCursorColor());
    textFieldOverlayModifier_->SetCursorColor(cursorColor);

    SetFloatingCursor();

    InputStyle inputStyle = paintProperty->GetInputStyleValue(InputStyle::DEFAULT);
    textFieldOverlayModifier_->SetInputStyle(inputStyle);

    auto selectedColor = paintProperty->GetSelectedBackgroundColorValue(theme->GetSelectedColor());
    textFieldOverlayModifier_->SetSelectedBackGroundColor(selectedColor);

    SetShowUnderlineWidth();

    textFieldOverlayModifier_->SetShowSelect(textFieldPattern->GetShowSelect());
    textFieldOverlayModifier_->SetChangeSelectedRects(textFieldPattern->NeedPaintSelect());
    auto textSelectController = textFieldPattern->GetTextSelectController();
    CHECK_NULL_VOID(textSelectController);
    textSelectController->FireSelectEvent();

    textFieldOverlayModifier_->SetTextRect(textFieldPattern->GetTextRect());
    textFieldOverlayModifier_->SetShowPreviewTextDecoration(textFieldPattern->GetIsPreviewText());
    textFieldOverlayModifier_->SetPreviewTextRects(textFieldPattern->NeedDrawPreviewText());
    auto previewDecorationColor = paintProperty->GetCursorColorValue(textFieldPattern->GetPreviewDecorationColor());
    textFieldOverlayModifier_->SetPreviewTextDecorationColor(previewDecorationColor);
    textFieldOverlayModifier_->SetPreviewTextStyle(textFieldPattern->GetPreviewTextStyle());
    UpdateScrollBar();
}

void TextFieldPaintMethod::SetFloatingCursor()
{
    CHECK_NULL_VOID(textFieldOverlayModifier_);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    if (!textFieldOverlayModifier_->GetFloatCaretLanding()) {
        auto floatingCursorRect = textFieldPattern->GetFloatingCaretRect();
        textFieldOverlayModifier_->SetFloatingCursorOffset(floatingCursorRect.GetOffset());
    }
    auto floatingCursorVisible = textFieldPattern->GetFloatingCursorVisible();
    textFieldOverlayModifier_->SetFloatingCursorVisible(floatingCursorVisible);
    auto showOriginCursor = textFieldPattern->GetShowOriginCursor();
    textFieldOverlayModifier_->SetShowOriginCursor(showOriginCursor);
}

void TextFieldPaintMethod::DoTextFadeoutIfNeed(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    CHECK_NULL_VOID(textFieldContentModifier_);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto textFieldTheme = textFieldPattern->GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    auto frameNode = textFieldPattern->GetHost();
    CHECK_NULL_VOID(frameNode);
    if ((textFieldTheme->TextFadeoutEnabled() && textFieldPattern->GetTextFadeoutCapacity())) {
        auto paragraph = textFieldPattern->GetParagraph();
        CHECK_NULL_VOID(paragraph);
        auto paintContentWidth = paintWrapper->GetContentSize().Width();
        auto textFadeoutEnabled =
            GreatNotEqual(paintContentWidth, 0.0) &&
            GreatNotEqual(paragraph->GetTextWidth() + textFieldPattern->GetTextParagraphIndent(), paintContentWidth);
        textFieldContentModifier_->SetTextFadeoutEnabled(textFadeoutEnabled);
    }
}

void TextFieldPaintMethod::UpdateScrollBar()
{
    auto scrollBar = scrollBar_.Upgrade();
    if (!scrollBar || !scrollBar->NeedPaint()) {
        return;
    }
    if (scrollBar->GetPositionModeUpdate()) {
        textFieldOverlayModifier_->SetPositionMode(scrollBar->GetPositionMode());
    }
    OffsetF fgOffset(scrollBar->GetActiveRect().Left(), scrollBar->GetActiveRect().Top());
    textFieldOverlayModifier_->StartBarAnimation(scrollBar->GetHoverAnimationType(),
        scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(), scrollBar->GetActiveRect());
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    textFieldOverlayModifier_->SetBarColor(scrollBar->GetForegroundColor());
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}

RefPtr<Modifier> TextFieldPaintMethod::GetForegroundModifier(PaintWrapper* paintWrapper)
{
    return textFieldForegroundModifier_;
}

void TextFieldPaintMethod::UpdateForegroundModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(textFieldForegroundModifier_);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto paintProperty = textFieldPattern->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    textFieldForegroundModifier_->SetInnerBorderWidth(
        static_cast<float>(paintProperty->GetInnerBorderWidthValue(Dimension()).ConvertToPx()));
}
} // namespace OHOS::Ace::NG
