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

RichEditorLayoutAlgorithm::RichEditorLayoutAlgorithm(std::list<RefPtr<SpanItem>> spans,
    RichEditorParagraphManager* paragraphs, std::optional<TextStyle> typingTextStyle,
    LRUMap<std::uintptr_t, RefPtr<Paragraph>>* paraMapPtr)
    : pManager_(paragraphs), typingTextStyle_(typingTextStyle), paraMapPtr_(paraMapPtr)
{
    ACE_SCOPED_TRACE("RichEditorLayoutAlgorithm::Constructor");
    allSpans_ = spans;
    // split spans into groups by \newline
    IF_TRUE(spans.empty() && paraMapPtr_, paraMapPtr_->Clear());
    auto it = spans.begin();
    while (it != spans.end()) {
        auto span = *it;
        // only checking the last char
        if (span->content.back() == u'\n') {
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
            placeholderSpanItem->textStyle_ = textStyle;
        }
        ++it;
    }
    if (!spans.empty()) {
        spans_.push_back(std::move(spans));
    }
    AppendNewLineSpan();
    HandleParagraphCache();
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "spans=%{public}s", SpansToString().c_str());
}

void RichEditorLayoutAlgorithm::HandleParagraphCache()
{
    CHECK_NULL_VOID(paraMapPtr_);
    for (const auto& group : spans_) {
        std::uintptr_t hash = 0;
        bool needReLayout = false;
        for (const auto& child : group) {
            std::uintptr_t intValue = reinterpret_cast<std::uintptr_t>(Referenced::RawPtr(child));
            hash ^= intValue;
            needReLayout |= child->needReLayout;
        }
        if (needReLayout) {
            paraMapPtr_->Erase(hash);
        }
    }
}

std::uintptr_t RichEditorLayoutAlgorithm::Hash(const std::list<RefPtr<SpanItem>>& spanGroup)
{
    std::uintptr_t hash = 0;
    for (const auto& child : spanGroup) {
        hash ^= reinterpret_cast<std::uintptr_t>(Referenced::RawPtr(child));
    }
    return hash;
}

RefPtr<Paragraph> RichEditorLayoutAlgorithm::GetOrCreateParagraph(const std::list<RefPtr<SpanItem>>& group,
    const ParagraphStyle& paraStyle, const std::map<int32_t, AISpan>& aiSpanMap)
{
    ACE_SCOPED_TRACE("RichEditorLayoutAlgorithm::GetOrCreateParagraph");
    if (!paraMapPtr_) {
        useParagraphCache_ = false;
        return Paragraph::CreateRichEditorParagraph(paraStyle, FontCollection::Current());
    }
    auto hash = Hash(group);
    auto it = paraMapPtr_->Get(hash);
    bool findCache = it != paraMapPtr_->End() && it->second != nullptr;
    bool directionChanged = findCache && it->second->GetParagraphStyle().direction != paraStyle.direction;
    bool fontLocaleChanged = findCache && it->second->GetParagraphStyle().fontLocale != paraStyle.fontLocale;
    bool useCache = findCache && !directionChanged && !fontLocaleChanged
        && paraStyle.maxLines == UINT32_MAX && aiSpanMap.empty();
    auto paragraph = useCache ?
        it->second : Paragraph::CreateRichEditorParagraph(paraStyle, FontCollection::Current());

    // caching paragraph
    paraMapPtr_->Put(hash, paragraph);
    useParagraphCache_ = useCache;
    CHECK_NULL_RETURN(!useCache, paragraph);
    for (const auto& child : group) {
        if (!child) {
            continue;
        }
        child->needReLayout = true;
        break;
    }
    return paragraph;
}

void RichEditorLayoutAlgorithm::AppendNewLineSpan()
{
    CHECK_NULL_VOID(!allSpans_.empty());
    auto lastSpan = allSpans_.back();
    CHECK_NULL_VOID(lastSpan);
    if (lastSpan->content.back() == u'\n') {
        std::list<RefPtr<SpanItem>> newGroup;
        auto tailNewLineSpan = AceType::MakeRefPtr<SpanItem>();
        tailNewLineSpan->content = u"\n";
        tailNewLineSpan->SetNeedRemoveNewLine(true);
        tailNewLineSpan->MarkDirty();
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
    } else {
        if (source->fontStyle->HasFontSize()) {
            target->fontStyle->UpdateFontSize(source->fontStyle->GetFontSizeValue());
        }
        if (source->textLineStyle->HasLineHeight()) {
            target->textLineStyle->UpdateLineHeight(source->textLineStyle->GetLineHeightValue());
        }
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
    ACE_SCOPED_TRACE("RichEditorLayoutAlgorithm::MeasureContentSize");
    auto layoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, {});
    TextStyle textStyle;
    ConstructTextStyles(contentConstraint, layoutWrapper, textStyle);
    MeasureChildren(layoutWrapper, textStyle);
    CHECK_NULL_RETURN(BuildParagraph(textStyle, layoutProperty, contentConstraint, layoutWrapper), {});
    pManager_->SetParagraphs(GetParagraphs());
    return SizeF(pManager_->GetMaxWidth(), pManager_->GetHeight());
}

LayoutConstraintF RichEditorLayoutAlgorithm::ReMeasureContent(
    SizeF& textSize, const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    ACE_SCOPED_TRACE("RichEditorLayoutAlgorithm::ReMeasureContent");
    auto newContentConstraint = contentConstraint;
    auto pattern = GetRichEditorPattern(layoutWrapper);
    CHECK_NULL_RETURN(pattern, newContentConstraint);
    auto layoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, newContentConstraint);
    if (pattern->GetMaxLinesHeight() != FLT_MAX && layoutProperty->GetMaxLinesValue(INT32_MAX) == INT32_MAX) {
        newContentConstraint.maxSize.SetHeight(pattern->GetMaxLinesHeight());
        return newContentConstraint;
    }
    if (pattern->GetMaxLines() == INT32_MAX || pManager_->GetHeight() <= 0.0f) {
        return newContentConstraint;
    }
    pattern->SetMaxLinesHeight(pManager_->GetHeight());
    newContentConstraint.maxSize.SetHeight(pattern->GetMaxLinesHeight());
    layoutProperty->UpdateMaxLines(INT32_MAX);
    TextStyle textStyle;
    ConstructTextStyles(newContentConstraint, layoutWrapper, textStyle);
    layoutProperty->UpdateMaxLines(pattern->GetMaxLines());
    CHECK_NULL_RETURN(BuildParagraph(textStyle, layoutProperty, newContentConstraint, layoutWrapper), {});
    pManager_->SetParagraphs(GetParagraphs());
    textSize = SizeF(pManager_->GetMaxWidth(), pManager_->GetHeight());
    return newContentConstraint;
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
    CHECK_NULL_RETURN(optionalTextSize.has_value(), {});
    auto newContentConstraint = ReMeasureContent(optionalTextSize.value(), contentConstraint, layoutWrapper);
    SizeF res = optionalTextSize.value();
    res.AddHeight(spans_.empty() ? 0 : shadowOffset_);
    CHECK_NULL_RETURN(res.IsNonNegative(), {});
    UpdateRichTextRect(optionalTextSize.value(), layoutWrapper);
    auto maxHeight = newContentConstraint.selfIdealSize.Height().value_or(newContentConstraint.maxSize.Height());
    auto contentHeight = std::min(res.Height(), maxHeight);
    return SizeF(res.Width(), contentHeight);
}

bool RichEditorLayoutAlgorithm::BuildParagraph(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    ACE_SCOPED_TRACE("RichEditorLayoutAlgorithm::BuildParagraph");
    auto maxSize = MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint);
    if (!CreateParagraph(textStyle, layoutProperty->GetContent().value_or(u""), layoutWrapper, maxSize.Width())) {
        return false;
    }
    CHECK_NULL_RETURN(paragraphManager_, false);
    auto& paragraphInfo = paragraphManager_->GetParagraphs();

    if (paragraphInfo.size() != spans_.size()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "paragraph size mismatch, %{public}zu vs. %{public}zu",
            paragraphInfo.size(), spans_.size());
    }
    auto pIter = paragraphInfo.begin();
    auto groupIter = spans_.begin();
    while (pIter != paragraphInfo.end() && groupIter != spans_.end()) {
        auto& paragraph = pIter->paragraph;
        CHECK_NULL_CONTINUE(paragraph);
        std::vector<TextStyle> textStyles;
        auto& group = *groupIter;
        bool needReLayout;
        bool needReLayoutParagraph;
        ReLayoutParagraphBySpan(layoutWrapper, textStyles, group, needReLayout, needReLayoutParagraph);
        if (!needReLayout && needReLayoutParagraph) {
            paragraph->ReLayout(maxSize.Width(), pIter->paragraphStyle, textStyles);
        } else {
            paragraph->Layout(maxSize.Width());
        }
        ++pIter;
        ++groupIter;
    }

    if (paraMapPtr_) {
        paraMapPtr_->SetCapacity(paragraphInfo.size());
        paraMapPtr_->SetCapacity(SIZE_MAX);
    }
    return ParagraphReLayout(contentConstraint);
}

void RichEditorLayoutAlgorithm::ReLayoutParagraphBySpan(LayoutWrapper* layoutWrapper,
    std::vector<TextStyle>& textStyles, std::list<RefPtr<SpanItem>>& group,
    bool& needReLayout, bool& needReLayoutParagraph)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    needReLayout = false;
    needReLayoutParagraph = false;
    for (const auto& child : group) {
        if (!child) {
            continue;
        }
        needReLayout |= child->needReLayout;
        needReLayoutParagraph |= child->needReLayoutParagraph;
        ACE_SCOPED_TRACE("RichEditorReLayoutParagraphBySpan[needReLayout:%d][needReLayoutParagraph:%d]",
            needReLayout, needReLayoutParagraph);
        child->ResetReLayout();
        CHECK_NULL_CONTINUE(!needReLayout);
        TextStyle spanTextStyle;
        child->UpdateSpanTextStyle(inheritTextStyle_, frameNode);
        if (child->GetTextStyle().has_value()) {
            spanTextStyle = child->GetTextStyle().value();
        }
        textStyles.emplace_back(spanTextStyle);
    }
}

bool RichEditorLayoutAlgorithm::CreateParagraph(
    const TextStyle& textStyle, std::u16string content, LayoutWrapper* layoutWrapper, double maxWidth)
{
    CHECK_NULL_RETURN(!spans_.empty(), false);
    ACE_SCOPED_TRACE("RichEditorLayoutAlgorithm::CreateParagraph");
    if (!paragraphManager_) {
        paragraphManager_ = AceType::MakeRefPtr<ParagraphManager>();
    }
    paragraphManager_->Reset();
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    // default paragraph style
    auto paraStyle = GetEditorParagraphStyle(textStyle, content, layoutWrapper);
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
    CHECK_NULL_VOID(layoutConstraint.has_value());
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

ParagraphStyle RichEditorLayoutAlgorithm::GetEditorParagraphStyle(
    const TextStyle& textStyle, const std::u16string& content, LayoutWrapper* layoutWrapper) const
{
    auto style = MultipleParagraphLayoutAlgorithm::GetParagraphStyle(textStyle);
    style.fontSize = textStyle.GetFontSize().ConvertToPx();
    style.maxLines = textStyle.GetMaxLines();
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
    CHECK_NULL_VOID(textStyle.has_value());
    paragraph->PushStyle(textStyle.value());
}

RefPtr<SpanItem> RichEditorLayoutAlgorithm::GetParagraphStyleSpanItem(const std::list<RefPtr<SpanItem>>& spanGroup)
{
    CHECK_NULL_RETURN(!spanGroup.empty(), nullptr);
    auto it = spanGroup.begin();
    while (it != spanGroup.end()) {
        if (!AceType::DynamicCast<PlaceholderSpanItem>(*it)) {
            return *it;
        }
        ++it;
    }
    return *spanGroup.begin();
}

std::string RichEditorLayoutAlgorithm::SpansToString()
{
    std::stringstream ss;
    for (const auto& list : spans_) {
        ss << "[";
        for_each(list.begin(), list.end(), [&ss](const RefPtr<SpanItem>& item) {
#ifndef IS_RELEASE_VERSION
            ss << "(" << StringUtils::RestoreEscape(UtfUtils::Str16DebugToStr8(item->content)) << ")";
#endif
            ss << "[" << item->rangeStart << ":" << item->position << "],";
        });
        ss << "], ";
    }
    return ss.str();
}

void RichEditorLayoutAlgorithm::AddTextSpanToParagraph(const RefPtr<SpanItem>& child, int32_t& spanTextLength,
    const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph)
{
    if (!useParagraphCache_) {
        MultipleParagraphLayoutAlgorithm::AddTextSpanToParagraph(child, spanTextLength, frameNode, paragraph);
        return;
    }
    spanTextLength += static_cast<int32_t>(child->content.length());
}

void RichEditorLayoutAlgorithm::AddImageToParagraph(RefPtr<ImageSpanItem>& child, const RefPtr<LayoutWrapper>& iterItem,
    const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength)
{
    if (!useParagraphCache_) {
        MultipleParagraphLayoutAlgorithm::AddImageToParagraph(child, iterItem, paragraph, spanTextLength);
        return;
    }
    spanTextLength += static_cast<int32_t>(child->content.length());
    child->placeholderIndex = currentParagraphPlaceholderCount_++;
    child->placeholderIndex += preParagraphsPlaceholderCount_;
}

void RichEditorLayoutAlgorithm::AddPlaceHolderToParagraph(RefPtr<PlaceholderSpanItem>& child,
    const RefPtr<LayoutWrapper>& layoutWrapper, const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength)
{
    if (!useParagraphCache_) {
        MultipleParagraphLayoutAlgorithm::AddPlaceHolderToParagraph(child, layoutWrapper, paragraph, spanTextLength);
        return;
    }
    spanTextLength += static_cast<int32_t>(child->content.length());
    child->placeholderIndex = currentParagraphPlaceholderCount_++;
    child->placeholderIndex += preParagraphsPlaceholderCount_;
}

void RichEditorLayoutAlgorithm::UpdateParagraphByCustomSpan(RefPtr<CustomSpanItem>& child,
    const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength, CustomSpanPlaceholderInfo& customSpanPlaceholder)
{
    if (!useParagraphCache_) {
        MultipleParagraphLayoutAlgorithm::UpdateParagraphByCustomSpan(
            child, paragraph, spanTextLength, customSpanPlaceholder);
        return;
    }
    spanTextLength += static_cast<int32_t>(child->content.length());
    child->placeholderIndex = currentParagraphPlaceholderCount_++;
    child->placeholderIndex += preParagraphsPlaceholderCount_;
    if (child->onDraw.has_value()) {
        customSpanPlaceholder.onDraw = child->onDraw.value();
    }
    customSpanPlaceholder.customSpanIndex = child->placeholderIndex;
}

void RichEditorLayoutAlgorithm::AddSymbolSpanToParagraph(const RefPtr<SpanItem>& child, int32_t& spanTextLength,
    const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph)
{
    if (!useParagraphCache_) {
        MultipleParagraphLayoutAlgorithm::AddSymbolSpanToParagraph(child, spanTextLength, frameNode, paragraph);
        return;
    }
    spanTextLength += static_cast<int32_t>(child->content.length());
}
} // namespace OHOS::Ace::NG
