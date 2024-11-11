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

#include "core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/text/multiple_paragraph_layout_algorithm.h"

namespace OHOS::Ace::NG {
RichEditorLayoutAlgorithm::RichEditorLayoutAlgorithm(std::list<RefPtr<SpanItem>> spans, ParagraphManager* paragraphs,
    std::optional<TextStyle> typingTextStyle)
    : pManager_(paragraphs), typingTextStyle_(typingTextStyle)
{
    allSpans_ = spans;
    // split spans into groups by \newline
    auto it = spans.begin();
    while (it != spans.end()) {
        auto span = *it;
        // only checking the last char
        if (StringUtils::ToWstring(span->content).back() == L'\n') {
            span->SetNeedRemoveNewLine(true);
            std::list<RefPtr<SpanItem>> newGroup;
            newGroup.splice(newGroup.begin(), spans, spans.begin(), std::next(it));
            spans_.push_back(std::move(newGroup));

            it = spans.begin();
            continue;
        }
        span->SetNeedRemoveNewLine(false);
        // clear placeholder textstyle,it should be modified by text line
        auto placeholderSpanItem = AceType::DynamicCast<PlaceholderSpanItem>(span);
        if (placeholderSpanItem) {
            TextStyle textStyle;
            placeholderSpanItem->textStyle = textStyle;
        }
        ++it;
    }
    if (!spans.empty()) {
        spans_.push_back(std::move(spans));
    }
    AppendNewLineSpan();
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "spans=%{private}s", SpansToString().c_str());
}

void RichEditorLayoutAlgorithm::AppendNewLineSpan()
{
    auto lastSpan = allSpans_.back();
    CHECK_NULL_VOID(lastSpan);
    if (StringUtils::ToWstring(lastSpan->content).back() == L'\n') {
        std::list<RefPtr<SpanItem>> newGroup;
        auto tailNewLineSpan = AceType::MakeRefPtr<SpanItem>();
        tailNewLineSpan->content = "\n";
        tailNewLineSpan->SetNeedRemoveNewLine(true);
        CopySpanStyle(lastSpan, tailNewLineSpan);
        newGroup.push_back(tailNewLineSpan);
        spans_.push_back(std::move(newGroup));
    }
}

void RichEditorLayoutAlgorithm::CopySpanStyle(RefPtr<SpanItem> source, RefPtr<SpanItem> target)
{
    if (typingTextStyle_.has_value()) {
        auto typingTextStyle = typingTextStyle_.value();
        target->fontStyle->UpdateFontSize(typingTextStyle.GetFontSize());
        target->textLineStyle->UpdateLineHeight(typingTextStyle.GetLineHeight());
        return;
    }
    if (source->fontStyle->HasFontSize()) {
        target->fontStyle->UpdateFontSize(source->fontStyle->GetFontSizeValue());
    }

    if (source->textLineStyle->HasLineHeight()) {
        target->textLineStyle->UpdateLineHeight(source->textLineStyle->GetLineHeightValue());
    }
}

std::optional<SizeF> RichEditorLayoutAlgorithm::MeasureEmptyContentSize(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, {});
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, {});
    auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(richEditorTheme, {});
    auto defaultCaretHeight = richEditorTheme->GetDefaultCaretHeight().ConvertToPx();
    auto width = contentConstraint.selfIdealSize.Width().value_or(contentConstraint.maxSize.Width());
    auto pattern = host->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, {});
    auto presetParagraph = pattern->GetPresetParagraph();
    if (!presetParagraph) {
        pattern->PreferredParagraph();
    }
    auto contentHeight = defaultCaretHeight;
    presetParagraph = pattern->GetPresetParagraph();
    if (presetParagraph) {
        contentHeight = presetParagraph->GetHeight();
    }
    return SizeF(width, static_cast<float>(contentHeight));
}

std::optional<SizeF> RichEditorLayoutAlgorithm::MeasureContentSize(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, {});
    TextStyle textStyle;
    ConstructTextStyles(contentConstraint, layoutWrapper, textStyle);
    CHECK_NULL_RETURN(BuildParagraph(textStyle, layoutProperty, contentConstraint, layoutWrapper), {});
    pManager_->SetParagraphs(GetParagraphs());
    return SizeF(pManager_->GetMaxWidth(), pManager_->GetHeight());
}

std::optional<SizeF> RichEditorLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    ACE_SCOPED_TRACE("RichEditorMeasureContent");
    pManager_->Reset();
    SetPlaceholder(layoutWrapper);
    auto optionalTextSize = spans_.empty()
        ? MeasureEmptyContentSize(contentConstraint, layoutWrapper)
        : MeasureContentSize(contentConstraint, layoutWrapper);
    CHECK_NULL_RETURN(optionalTextSize, {});
    SizeF res = optionalTextSize.value();
    res.AddHeight(spans_.empty() ? 0 : shadowOffset_);
    CHECK_NULL_RETURN(res.IsNonNegative(), {});
    UpdateRichTextRect(optionalTextSize.value(), layoutWrapper);
    auto maxHeight = contentConstraint.selfIdealSize.Height().value_or(contentConstraint.maxSize.Height());
    auto contentHeight = std::min(res.Height(), maxHeight);
    return SizeF(res.Width(), contentHeight);
}

bool RichEditorLayoutAlgorithm::BuildParagraph(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto maxSize = MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint);
    if (!CreateParagraph(textStyle, layoutProperty->GetContent().value_or(""), layoutWrapper, maxSize.Width())) {
        return false;
    }
    CHECK_NULL_RETURN(paragraphManager_, false);
    auto paragraphInfo = paragraphManager_->GetParagraphs();
    for (auto pIter = paragraphInfo.begin(); pIter != paragraphInfo.end(); pIter++) {
        auto paragraph = pIter->paragraph;
        CHECK_NULL_RETURN(paragraph, false);
        paragraph->Layout(maxSize.Width());
    }
    return ParagraphReLayout(contentConstraint);
}

bool RichEditorLayoutAlgorithm::CreateParagraph(
    const TextStyle& textStyle, std::string content, LayoutWrapper* layoutWrapper, double maxWidth)
{
    CHECK_NULL_RETURN(!spans_.empty(), false);
    if (!paragraphManager_) {
        paragraphManager_ = AceType::MakeRefPtr<ParagraphManager>();
    }
    paragraphManager_->Reset();
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    // default paragraph style
    auto paraStyle = GetParagraphStyle(textStyle, content, layoutWrapper);
    return UpdateParagraphBySpan(layoutWrapper, paraStyle, maxWidth, textStyle);
}

RefPtr<RichEditorPattern> RichEditorLayoutAlgorithm::GetRichEditorPattern(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, nullptr);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, nullptr);
    return host->GetPattern<RichEditorPattern>();
}

void RichEditorLayoutAlgorithm::UpdateRichTextRect(const SizeF& textSize, LayoutWrapper* layoutWrapper)
{
    auto pattern = GetRichEditorPattern(layoutWrapper);
    CHECK_NULL_VOID(pattern);
    richTextRect_.SetSize(pattern->IsShowPlaceholder() ? SizeF() : textSize);
}

bool RichEditorLayoutAlgorithm::SetPlaceholder(LayoutWrapper* layoutWrapper)
{
    auto pattern = GetRichEditorPattern(layoutWrapper);
    CHECK_NULL_RETURN(pattern, false);
    return pattern->SetPlaceholder(spans_);
}

float RichEditorLayoutAlgorithm::GetShadowOffset(const std::list<RefPtr<SpanItem>>& group)
{
    float shadowOffset = 0.0f;
    for (auto& span: group) {
        if (!span->fontStyle || !span->fontStyle->HasTextShadow()) {
            continue;
        }
        auto shadows = span->fontStyle->GetTextShadowValue();
        float upOffsetY = 0.0f;
        float downOffsetY = 0.0f;
        for (const auto& shadow : shadows) {
            auto shadowBlurRadius = shadow.GetBlurRadius() * 2.0f;
            auto shadowOffsetY = shadow.GetOffset().GetY();
            if (LessOrEqual(shadowOffsetY, 0.0f) &&
                LessNotEqual(shadowOffsetY, upOffsetY)) {
                upOffsetY = shadowOffsetY - shadowBlurRadius;
            } else if (GreatOrEqual(shadowOffsetY, 0.0f) &&
                       GreatNotEqual(shadowOffsetY + shadowBlurRadius, downOffsetY)) {
                downOffsetY = shadowOffsetY + shadowBlurRadius;
            }
        }
        shadowOffset = std::max(shadowOffset, downOffsetY - upOffsetY);
    }
    return shadowOffset;
}

void RichEditorLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    MultipleParagraphLayoutAlgorithm::Measure(layoutWrapper);
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    OptionalSizeF idealSize =
        CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (layoutConstraint->maxSize.Width() < layoutConstraint->minSize.Width()) {
        idealSize.SetWidth(layoutConstraint->minSize.Width());
    }
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    frameSize.SetWidth(idealSize.ConvertToSizeT().Width());
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

void RichEditorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto context = layoutWrapper->GetHostNode()->GetContext();
    CHECK_NULL_VOID(context);
    parentGlobalOffset_ = layoutWrapper->GetHostNode()->GetPaintRectOffsetNG() - context->GetRootRect().GetOffset();
    MultipleParagraphLayoutAlgorithm::Layout(layoutWrapper);
}

OffsetF RichEditorLayoutAlgorithm::GetContentOffset(LayoutWrapper* layoutWrapper)
{
    auto contentOffset = SetContentOffset(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, contentOffset);
    auto pattern = host->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, contentOffset);
    richTextRect_.SetOffset(OffsetF(contentOffset.GetX(), pattern->GetTextRect().GetY()));
    return richTextRect_.GetOffset();
}

ParagraphStyle RichEditorLayoutAlgorithm::GetParagraphStyle(
    const TextStyle& textStyle, const std::string& content, LayoutWrapper* layoutWrapper) const
{
    auto style = MultipleParagraphLayoutAlgorithm::GetParagraphStyle(textStyle, content, layoutWrapper);
    style.fontSize = textStyle.GetFontSize().ConvertToPx();
    if (!pManager_->minParagraphFontSize.has_value() ||
        GreatNotEqual(pManager_->minParagraphFontSize.value(), style.fontSize)) {
        pManager_->minParagraphFontSize = style.fontSize;
    }
    return style;
}

void RichEditorLayoutAlgorithm::HandleEmptyParagraph(RefPtr<Paragraph> paragraph,
    const std::list<RefPtr<SpanItem>>& spanGroup)
{
    CHECK_NULL_VOID(paragraph && spanGroup.size() == 1);
    auto spanItem = spanGroup.front();
    CHECK_NULL_VOID(spanItem);
    auto content = spanItem->GetSpanContent(spanItem->GetSpanContent());
    CHECK_NULL_VOID(content.empty());
    auto textStyle = spanItem->GetTextStyle();
    CHECK_NULL_VOID(textStyle);
    paragraph->PushStyle(textStyle.value());
}

RefPtr<SpanItem> RichEditorLayoutAlgorithm::GetParagraphStyleSpanItem(const std::list<RefPtr<SpanItem>>& spanGroup)
{
    auto it = spanGroup.begin();
    while (it != spanGroup.end()) {
        if (!AceType::DynamicCast<PlaceholderSpanItem>(*it)) {
            return *it;
        }
        ++it;
    }
    return *spanGroup.begin();
}

} // namespace OHOS::Ace::NG
