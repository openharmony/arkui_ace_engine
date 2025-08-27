/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_TYPING_STYLE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_TYPING_STYLE_MANAGER_H

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

namespace OHOS::Ace::NG {

class StyleManager {
public:
    StyleManager() {}
    StyleManager(const WeakPtr<RichEditorPattern>& pattern) : weakPattern_(pattern) {}

    void SetTypingStyle(const std::optional<struct UpdateSpanStyle>& typingStyle,
        const std::optional<TextStyle>& textStyle)
    {
        typingFontStyle_ = typingStyle;
        typingTextStyle_ = textStyle;
    }

    void SetTypingParagraphStyle(std::optional<struct UpdateParagraphStyle>& typingParagraphStyle)
    {
        typingParagraphStyle_ = typingParagraphStyle;
    }

    static void UpdateParagraphStyle(const RefPtr<SpanNode>& spanNode, const struct UpdateParagraphStyle& style)
    {
        CHECK_NULL_VOID(spanNode);
        spanNode->UpdateTextAlign(style.textAlign.value_or(TextAlign::START));
        spanNode->UpdateWordBreak(style.wordBreak.value_or(WordBreak::BREAK_WORD));
        spanNode->UpdateLineBreakStrategy(style.lineBreakStrategy.value_or(LineBreakStrategy::GREEDY));
        spanNode->UpdateTextVerticalAlign(style.textVerticalAlign.value_or(TextVerticalAlign::BASELINE));
        if (style.paragraphSpacing.has_value()) {
            spanNode->UpdateParagraphSpacing(style.paragraphSpacing.value());
        } else {
            spanNode->ResetParagraphSpacing();
        }
        auto leadingMarginValue = spanNode->GetLeadingMarginValue({});
        if (style.leadingMargin.has_value() && !leadingMarginValue.CheckLeadingMargin(style.leadingMargin.value())) {
            spanNode->GetSpanItem()->leadingMargin = *style.leadingMargin;
            spanNode->UpdateLeadingMargin(*style.leadingMargin);
        }
    }

    static void UpdateTextStyle(RefPtr<SpanNode>& spanNode, const struct UpdateSpanStyle& updateSpanStyle)
    {
        CHECK_NULL_VOID(spanNode);
        auto spanItem = spanNode->GetSpanItem();
        CHECK_NULL_VOID(spanItem);
        spanNode->UpdateTextColor(updateSpanStyle.updateTextColor);
        IF_TRUE(updateSpanStyle.updateTextColor.has_value(), spanItem->useThemeFontColor = false);
        spanNode->UpdateFontSize(updateSpanStyle.updateFontSize);
        spanNode->UpdateItalicFontStyle(updateSpanStyle.updateItalicFontStyle);
        spanNode->UpdateFontWeight(updateSpanStyle.updateFontWeight);
        spanNode->UpdateFontFamily(updateSpanStyle.updateFontFamily);

        if (updateSpanStyle.updateTextDecoration.has_value()) {
            spanNode->UpdateTextDecoration({ updateSpanStyle.updateTextDecoration.value() });
        }
        spanNode->UpdateTextDecorationColor(updateSpanStyle.updateTextDecorationColor);
        IF_TRUE(updateSpanStyle.updateTextDecorationColor.has_value(), spanItem->useThemeDecorationColor = false);
        spanNode->UpdateTextDecorationStyle(updateSpanStyle.updateTextDecorationStyle);
        spanNode->UpdateTextShadow(updateSpanStyle.updateTextShadows);

        spanNode->UpdateLetterSpacing(updateSpanStyle.updateLetterSpacing);
        spanNode->UpdateLineHeight(updateSpanStyle.updateLineHeight);
        spanNode->UpdateHalfLeading(updateSpanStyle.updateHalfLeading);
        spanNode->UpdateFontFeature(updateSpanStyle.updateFontFeature);

        UpdateTextBackgroundStyle(spanNode, updateSpanStyle.updateTextBackgroundStyle);
    }

    static void UpdateTextBackgroundStyle(RefPtr<SpanNode>& spanNode, const std::optional<TextBackgroundStyle>& style)
    {
        CHECK_NULL_VOID(style.has_value());
        TextBackgroundStyle backgroundStyle = style.value();
        backgroundStyle.needCompareGroupId = false;
        if (backgroundStyle == spanNode->GetTextBackgroundStyle()) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "text background style is same");
            return;
        }
        backgroundStyle.needCompareGroupId = true;
        spanNode->SetTextBackgroundStyle(backgroundStyle);
    }

    bool UpdateStyleByTypingParagraphStyle(RefPtr<SpanNode>& spanNode)
    {
        CHECK_NULL_RETURN(spanNode && typingParagraphStyle_.has_value(), false);
        UpdateParagraphStyle(spanNode, typingParagraphStyle_.value());
        return true;
    }

    bool UpdateStyleByTypingParagraphStyle(RefPtr<SpanItem>& spanItem)
    {
        CHECK_NULL_RETURN(spanItem && typingParagraphStyle_.has_value(), false);
        auto spanNode = AceType::MakeRefPtr<SpanNode>(ElementRegister::GetInstance()->MakeUniqueId());
        spanNode->SetSpanItem(spanItem);
        return UpdateStyleByTypingParagraphStyle(spanNode);
    }

    void UpdateTextStyleByTypingStyle(RefPtr<SpanNode>& spanNode)
    {
        CHECK_NULL_VOID(spanNode && typingFontStyle_.has_value());
        UpdateTextStyle(spanNode, typingFontStyle_.value());
    }

    void UpdateTextStyleByTypingStyle(RefPtr<SpanItem>& spanItem)
    {
        CHECK_NULL_VOID(spanItem && typingFontStyle_.has_value());
        auto spanNode = AceType::MakeRefPtr<SpanNode>(ElementRegister::GetInstance()->MakeUniqueId());
        spanNode->SetSpanItem(spanItem);
        UpdateTextStyleByTypingStyle(spanNode);
    }

    static RefPtr<FontSpan> CreateFontSpanByTextStyle(
        const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle, int32_t length)
    {
        Font font;
        if (updateSpanStyle.updateFontWeight.has_value()) {
            font.fontWeight = textStyle.GetFontWeight();
        }
        if (updateSpanStyle.updateFontSize.has_value()) {
            font.fontSize = textStyle.GetFontSize();
        }
        if (updateSpanStyle.updateItalicFontStyle.has_value()) {
            font.fontStyle = textStyle.GetFontStyle();
        }
        if (updateSpanStyle.updateFontFamily.has_value()) {
            font.fontFamilies = textStyle.GetFontFamilies();
        }
        if (updateSpanStyle.updateTextColor.has_value()) {
            font.fontColor = textStyle.GetTextColor();
        }
        return AceType::MakeRefPtr<FontSpan>(font, 0, length);
    }

    static RefPtr<DecorationSpan> CreateDecorationSpanByTextStyle(
        const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle, int32_t length)
    {
        TextDecoration type = TextDecoration::NONE;
        std::optional<Color> colorOption;
        std::optional<TextDecorationStyle> styleOption;
        std::optional<TextDecorationOptions> options;
        if (updateSpanStyle.updateTextDecoration.has_value()) {
            type = textStyle.GetTextDecorationFirst();
        }
        if (updateSpanStyle.updateTextDecorationColor.has_value()) {
            colorOption = textStyle.GetTextDecorationColor();
        }
        if (updateSpanStyle.updateTextDecorationStyle.has_value()) {
            styleOption = textStyle.GetTextDecorationStyle();
        }
        return AceType::MakeRefPtr<DecorationSpan>(
            std::vector<TextDecoration>({type}), colorOption, styleOption, options, 0, length);
    }

    bool NeedTypingParagraphStyle(const RefPtr<MutableSpanString>& styledString, int32_t changeStart, int32_t changeLength)
    {
        CHECK_NULL_RETURN(styledString && typingParagraphStyle_.has_value(), false);
        auto length = styledString->GetLength();
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "length=%{public}d, changeStart=%{public}d, changeLength=%{public}d",
            length, changeStart, changeLength);
        CHECK_NULL_RETURN(length > 0 && changeLength != length, true);
        CHECK_NULL_RETURN(changeStart + changeLength == length || changeStart == length, false);
        auto& string = styledString->GetU16string();
        if (changeStart > length || changeStart <= 0) {
            TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "NeedTypingParagraphStyle, error, changeStart=%{public}d, length=%{public}d",
                changeStart, length);
            return false;
        }
        bool lastNewLine = string[changeStart - 1] == u'\n';
        CHECK_NULL_RETURN(!lastNewLine, true);
        return false;
    }

    bool NeedTypingParagraphStyle(const std::list<RefPtr<SpanItem>>& spans, const RichEditorChangeValue& changeValue)
    {
        // empty
        CHECK_NULL_RETURN(!spans.empty(), true);

        auto contentLength = spans.back()->position;
        const auto& rangeBefore = changeValue.GetRangeBefore();
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "rangeBefore=[%{public}d, %{public}d], contentLength=%{public}d",
            rangeBefore.start, rangeBefore.end, contentLength);

        // delete to empty
        if (rangeBefore.start == 0 && rangeBefore.end == contentLength) {
            return true;
        }

        // insert in last new line
        if (rangeBefore.start == rangeBefore.end) {
            return spans.back()->content.back() == u'\n';
        }

        // delete to last new line
        if (rangeBefore.end == contentLength) {
            for (auto& span : spans) {
                if (rangeBefore.start > span->position) {
                    continue;
                }
                if ((rangeBefore.start) == span->position && span->content.back() == u'\n') {
                    return true;
                }
            }
        }
        return false;
    }

    bool NeedTypingParagraphStyle(const std::list<RefPtr<SpanItem>>& spans, int32_t caretPosition)
    {
        // empty
        CHECK_NULL_RETURN(!spans.empty(), true);

        // insert in last new Line
        auto contentLength = spans.back()->position;
        if (caretPosition == contentLength && spans.back()->content.back() == u'\n') {
            return true;
        }
        return false;

    }

    bool UseTypingParaStyle(const std::list<RefPtr<SpanItem>>& spans, const RichEditorChangeValue& changeValue)
    {
        return typingParagraphStyle_.has_value() && NeedTypingParagraphStyle(spans, changeValue);
    }

    bool UseTypingParaStyle(const std::list<RefPtr<SpanItem>>& spans, int32_t caretPosition)
    {
        return typingParagraphStyle_.has_value() && NeedTypingParagraphStyle(spans, caretPosition);

    }

    RefPtr<SpanString> CreateStyledStringByTypingStyle(const std::u16string& insertValue, const RefPtr<MutableSpanString>& styledString, int32_t changeStart, int32_t changeLength)
    {
        bool hasTypingStyle = typingFontStyle_.has_value();
        bool needTypingParagraphStyle = NeedTypingParagraphStyle(styledString, changeStart, changeLength);
        CHECK_NULL_RETURN(hasTypingStyle || needTypingParagraphStyle, {});

        auto insertStyledString = AceType::MakeRefPtr<SpanString>(insertValue);
        std::vector<RefPtr<SpanBase>> spans;
        int length = insertStyledString->GetLength();
        IF_TRUE(hasTypingStyle, HandleStyledStringByTypingTextStyle(length, spans));
        IF_TRUE(needTypingParagraphStyle, HandleStyledStringByTypingParagraphStyle(length, spans));
        insertStyledString->BindWithSpans(spans);
        return insertStyledString;
    }

    void HandleStyledStringByTypingTextStyle(int length, std::vector<RefPtr<SpanBase>>& spans)
    {
        CHECK_NULL_VOID(typingTextStyle_.has_value() && typingFontStyle_.has_value());
        auto& textStyle = typingTextStyle_.value();
        auto& updateSpanStyle = typingFontStyle_.value();
        spans.push_back(CreateFontSpanByTextStyle(updateSpanStyle, textStyle, length));
        spans.push_back(CreateDecorationSpanByTextStyle(updateSpanStyle, textStyle, length));
        if (updateSpanStyle.updateTextShadows.has_value()) {
            spans.push_back(AceType::MakeRefPtr<TextShadowSpan>(textStyle.GetTextShadows(), 0, length));
        }
        if (updateSpanStyle.updateLineHeight.has_value()) {
            spans.push_back(AceType::MakeRefPtr<LineHeightSpan>(textStyle.GetLineHeight(), 0, length));
        }
        if (updateSpanStyle.updateHalfLeading.has_value()) {
            spans.push_back(AceType::MakeRefPtr<HalfLeadingSpan>(textStyle.GetHalfLeading(), 0, length));
        }
        if (updateSpanStyle.updateLetterSpacing.has_value()) {
            spans.push_back(AceType::MakeRefPtr<LetterSpacingSpan>(textStyle.GetLetterSpacing(), 0, length));
        }
        if (updateSpanStyle.updateTextBackgroundStyle.has_value()) {
            spans.push_back(AceType::MakeRefPtr<BackgroundColorSpan>(textStyle.GetTextBackgroundStyle(), 0, length));
        }
    }
    
    void HandleStyledStringByTypingParagraphStyle(int length, std::vector<RefPtr<SpanBase>>& spans)
    {
        CHECK_NULL_VOID(typingParagraphStyle_.has_value());
        auto& typingParagraphStyle = typingParagraphStyle_.value();
        SpanParagraphStyle spanParagraphStyle;
        spanParagraphStyle.align = typingParagraphStyle.textAlign;
        spanParagraphStyle.wordBreak = typingParagraphStyle.wordBreak;
        spanParagraphStyle.leadingMargin = typingParagraphStyle.leadingMargin;
        spanParagraphStyle.paragraphSpacing = typingParagraphStyle.paragraphSpacing;
        spanParagraphStyle.textVerticalAlign = typingParagraphStyle.textVerticalAlign;
        spans.push_back(AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, length));
    }

    std::optional<struct UpdateParagraphStyle> GetTypingParagraphStyle()
    {
        return typingParagraphStyle_;
    }

    bool HasTypingParagraphStyle()
    {
        return typingParagraphStyle_.has_value();
    }

private:
    std::optional<struct UpdateSpanStyle> typingFontStyle_;
    std::optional<TextStyle> typingTextStyle_;
    std::optional<struct UpdateParagraphStyle> typingParagraphStyle_;
    WeakPtr<RichEditorPattern> weakPattern_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_TYPING_STYLE_MANAGER_H