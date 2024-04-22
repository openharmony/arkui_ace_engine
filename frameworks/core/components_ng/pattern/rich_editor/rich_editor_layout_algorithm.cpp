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
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/render/paragraph.h"
#include "base/log/ace_trace.h"

namespace OHOS::Ace::NG {
RichEditorLayoutAlgorithm::RichEditorLayoutAlgorithm(std::list<RefPtr<SpanItem>> spans, ParagraphManager* paragraphs)
    : pManager_(paragraphs)
{
    allSpans_ = spans;
    // split spans into groups by \newline
    auto it = spans.begin();
    while (it != spans.end()) {
        auto span = *it;
        // only checking the last char
        if (StringUtils::ToWstring(span->content).back() == L'\n') {
            span->MarkNeedRemoveNewLine(true);
            std::list<RefPtr<SpanItem>> newGroup;
            newGroup.splice(newGroup.begin(), spans, spans.begin(), std::next(it));
            spans_.push_back(std::move(newGroup));

            it = spans.begin();
            continue;
        }
        span->MarkNeedRemoveNewLine(false);
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
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "spans=%{public}s", SpansToString().c_str());
}

void RichEditorLayoutAlgorithm::AppendNewLineSpan()
{
    auto lastSpan = allSpans_.back();
    CHECK_NULL_VOID(lastSpan);
    if (StringUtils::ToWstring(lastSpan->content).back() == L'\n') {
        std::list<RefPtr<SpanItem>> newGroup;
        auto tailNewLineSpan = AceType::MakeRefPtr<SpanItem>();
        tailNewLineSpan->content = "\n";
        tailNewLineSpan->MarkNeedRemoveNewLine(true);
        CopySpanStyle(lastSpan, tailNewLineSpan);
        newGroup.push_back(tailNewLineSpan);
        spans_.push_back(std::move(newGroup));
    }
}

void RichEditorLayoutAlgorithm::CopySpanStyle(RefPtr<SpanItem> source, RefPtr<SpanItem> target)
{
    if (source->fontStyle->HasFontSize()) {
        target->fontStyle->UpdateFontSize(source->fontStyle->GetFontSizeValue());
    }

    if (source->textLineStyle->HasLeadingMargin()) {
        auto leadingMargin = source->textLineStyle->GetLeadingMarginValue();
        leadingMargin.pixmap.Reset();
        target->textLineStyle->UpdateLeadingMargin(leadingMargin);
    }

    if (source->textLineStyle->HasTextAlign()) {
        target->textLineStyle->UpdateTextAlign(source->textLineStyle->GetTextAlignValue());
    }
}

std::optional<SizeF> RichEditorLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    ACE_SCOPED_TRACE("RichEditorMeasureContent");
    pManager_->Reset();
    SetPlaceholder(layoutWrapper);
    if (spans_.empty()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, std::nullopt);
        auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
        CHECK_NULL_RETURN(richEditorTheme, std::nullopt);
        auto defaultCaretHeight = richEditorTheme->GetDefaultCaretHeight().ConvertToPx();
        auto width = contentConstraint.selfIdealSize.Width().value_or(contentConstraint.maxSize.Width());
        return SizeF(width, defaultCaretHeight);
    }

    SizeF res;
    int32_t lastPlaceholderIndex = 0;
    float textHeight = 0.0f;
    uint32_t paragraphId = 0;
    for (auto&& group : spans_) {
        // layout each paragraph
        ACE_SCOPED_TRACE("LayoutEachParagraph");
        SetSpans(group);
        SetParagraph(nullptr);
        auto size = TextLayoutAlgorithm::MeasureContent(contentConstraint, layoutWrapper);
        if (size) {
            res.SetWidth(std::max(size->Width(), res.Width()));
            res.AddHeight(size->Height());
        }

        // record generated paragraph
        auto&& paragraph = GetParagraph();
        if (!paragraph) {
            continue;
        }
        paragraph->SetParagraphId(paragraphId++);
        float shadowOffset = GetShadowOffset(group);
        res.AddHeight(shadowOffset);
        textHeight += paragraph->GetHeight();
        auto firstSpan = *group.begin();
        auto lastSpan = *group.rbegin();
        if (!firstSpan || !lastSpan) {
            TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "MeasureContent failed. firstSpan or lastSpan is null.");
            continue;
        }
        pManager_->AddParagraph({ .paragraph = paragraph,
            .start = firstSpan->position - StringUtils::ToWstring(firstSpan->content).length(),
            .end = lastSpan->position });
        std::for_each(group.begin(), group.end(), [&](RefPtr<SpanItem>& item) {
            auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(item);
            if (imageSpanItem && imageSpanItem->placeholderIndex >= 0) {
                imageSpanItem->placeholderIndex = lastPlaceholderIndex;
                lastPlaceholderIndex++;
            } else if (auto placeholderSpanItem = AceType::DynamicCast<PlaceholderSpanItem>(item);
                       placeholderSpanItem) {
                placeholderSpanItem->placeholderIndex = lastPlaceholderIndex;
                lastPlaceholderIndex++;
            }
        });
    }
    if (!res.IsPositive()) {
        return std::nullopt;
    }
    UpdateRichTextRect(res, textHeight, layoutWrapper);
    auto contentHeight = res.Height();
    if (contentConstraint.selfIdealSize.Height().has_value()) {
        contentHeight = std::min(contentHeight, contentConstraint.selfIdealSize.Height().value());
    } else {
        contentHeight = std::min(contentHeight, contentConstraint.maxSize.Height());
    }
    return SizeF(res.Width(), contentHeight);
}

void RichEditorLayoutAlgorithm::UpdateRichTextRect(
    const SizeF& res, const float& textHeight, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->IsShowPlaceholder()) {
        richTextRect_.SetSize(SizeF(0.0f, 0.0f));
    } else {
        richTextRect_.SetSize(SizeF(res.Width(), textHeight));
    }
}

void RichEditorLayoutAlgorithm::SetPlaceholder(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetPlaceholder(spans_);
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
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    OptionalSizeF frameSize =
        CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (layoutConstraint->maxSize.Width() < layoutConstraint->minSize.Width()) {
        frameSize.SetWidth(layoutConstraint->minSize.Width());
    }
    TextLayoutAlgorithm::Measure(layoutWrapper);
}

void RichEditorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto context = layoutWrapper->GetHostNode()->GetContext();
    CHECK_NULL_VOID(context);
    parentGlobalOffset_ = layoutWrapper->GetHostNode()->GetPaintRectOffset() - context->GetRootRect().GetOffset();

    SetSpans(allSpans_);
    TextLayoutAlgorithm::Layout(layoutWrapper);
}

OffsetF RichEditorLayoutAlgorithm::GetContentOffset(LayoutWrapper* layoutWrapper)
{
    auto contentOffset = TextLayoutAlgorithm::GetContentOffset(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, contentOffset);
    auto pattern = host->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, contentOffset);
    richTextRect_.SetOffset(OffsetF(contentOffset.GetX(), pattern->GetTextRect().GetY()));
    return richTextRect_.GetOffset();
}

void RichEditorLayoutAlgorithm::GetPlaceholderRects(std::vector<RectF>& rects)
{
    rects = pManager_->GetPlaceholderRects();
}

ParagraphStyle RichEditorLayoutAlgorithm::GetParagraphStyle(
    const TextStyle& textStyle, const std::string& content, LayoutWrapper* layoutWrapper) const
{
    auto style = TextLayoutAlgorithm::GetParagraphStyle(textStyle, content, layoutWrapper);
    style.fontSize = textStyle.GetFontSize().ConvertToPx();
    if (!pManager_->minParagraphFontSize.has_value() ||
        GreatNotEqual(pManager_->minParagraphFontSize.value(), style.fontSize)) {
        pManager_->minParagraphFontSize = style.fontSize;
    }
    const auto& spanItem = GetFirstTextSpanItem();
    CHECK_NULL_RETURN(spanItem, style);
    auto& lineStyle = spanItem->textLineStyle;
    CHECK_NULL_RETURN(lineStyle, style);
    if (lineStyle->propTextAlign) {
        style.align = *(lineStyle->propTextAlign);
    }
    if (lineStyle->propWordBreak) {
        style.wordBreak = *(lineStyle->propWordBreak);
    }
    if (lineStyle->propLineBreakStrategy) {
        style.lineBreakStrategy = *(lineStyle->propLineBreakStrategy);
    }
    if (lineStyle->propTextIndent) {
        style.leadingMargin = std::make_optional<LeadingMargin>();
        style.leadingMargin->size = SizeF(lineStyle->propTextIndent->ConvertToPx(), 0.0f);
    }
    if (lineStyle->propLeadingMargin) {
        if (!style.leadingMargin) {
            style.leadingMargin = std::make_optional<LeadingMargin>();
        }
        style.leadingMargin->size = lineStyle->propLeadingMargin->size;
        style.leadingMargin->pixmap = lineStyle->propLeadingMargin->pixmap;
    }

    return style;
}

RefPtr<SpanItem> RichEditorLayoutAlgorithm::GetFirstTextSpanItem() const
{
    auto& spanGroup = GetSpans();
    auto it = spanGroup.begin();
    while (it != spanGroup.end()) {
        if (!DynamicCast<PlaceholderSpanItem>(*it)) {
            return *it;
        }
        ++it;
    }
    return *spanGroup.begin();
}

int32_t RichEditorLayoutAlgorithm::GetPreviousLength() const
{
    auto&& paragraphs = pManager_->GetParagraphs();
    if (paragraphs.empty()) {
        return 0;
    }
    return paragraphs.back().end;
}
} // namespace OHOS::Ace::NG
