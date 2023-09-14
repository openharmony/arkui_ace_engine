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
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
RichEditorLayoutAlgorithm::RichEditorLayoutAlgorithm(std::list<RefPtr<SpanItem>> spans, ParagraphManager* paragraphs)
    : pManager_(paragraphs)
{
    // split spans into groups by \newline
    auto it = spans.begin();
    while (it != spans.end()) {
        auto span = *it;
        // only checking the last char
        if (StringUtils::ToWstring(span->content).back() == L'\n') {
            std::list<RefPtr<SpanItem>> newGroup;
            newGroup.splice(newGroup.begin(), spans, spans.begin(), std::next(it));
            spans_.push_back(std::move(newGroup));

            it = spans.begin();
            continue;
        }
        ++it;
    }
    if (!spans.empty()) {
        spans_.push_back(std::move(spans));
    }
}

std::optional<SizeF> RichEditorLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    if (spans_.empty()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, std::nullopt);
        auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
        auto defaultCaretHeight = richEditorTheme->GetDefaultCaretHeight().ConvertToPx();
        return SizeF(contentConstraint.selfIdealSize.Width().value(), defaultCaretHeight);
    }

    SizeF res;
    for (auto&& group : spans_) {
        // layout each paragraph
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
        auto firstSpan = *group.begin();
        pManager_->AddParagraph({ .paragraph = paragraph,
            .start = firstSpan->position - StringUtils::ToWstring(firstSpan->content).length(),
            .end = (*group.rbegin())->position });
    }
    if (!res.IsPositive()) {
        return std::nullopt;
    }
    return res;
}

void RichEditorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto context = layoutWrapper->GetHostNode()->GetContext();
    CHECK_NULL_VOID(context);
    parentGlobalOffset_ = layoutWrapper->GetHostNode()->GetPaintRectOffset() - context->GetRootRect().GetOffset();

    // merge spans
    std::list<RefPtr<SpanItem>> allSpans;
    for (auto&& group : spans_) {
        allSpans.splice(allSpans.end(), group);
    }
    SetSpans(allSpans);
    TextLayoutAlgorithm::Layout(layoutWrapper);
}

void RichEditorLayoutAlgorithm::GetPlaceholderRects(std::vector<Rect>& rects)
{
    rects = pManager_->GetPlaceholderRects();
}

ParagraphStyle RichEditorLayoutAlgorithm::GetParagraphStyle(
    const TextStyle& textStyle, const std::string& content) const
{
    auto style = TextLayoutAlgorithm::GetParagraphStyle(textStyle, content);
    style.fontSize = textStyle.GetFontSize().ConvertToPx();
    auto&& spanGroup = GetSpans();
    auto&& lineStyle = spanGroup.front()->textLineStyle;
    CHECK_NULL_RETURN(lineStyle, style);
    if (lineStyle->propTextAlign) {
        style.align = *(lineStyle->propTextAlign);
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

int32_t RichEditorLayoutAlgorithm::GetPreviousLength() const
{
    auto&& paragraphs = pManager_->GetParagraphs();
    if (paragraphs.empty()) {
        return 0;
    }
    return paragraphs.back().end;
}
} // namespace OHOS::Ace::NG
