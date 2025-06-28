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
#include "core/components_ng/pattern/rich_editor/style_manager.h"
#include "core/components_ng/pattern/text/multiple_paragraph_layout_algorithm.h"
#include "core/components_ng/pattern/text/paragraph_util.h"

namespace {
constexpr int32_t CHILDREN_SIZE = 1;
}

namespace OHOS::Ace::NG {

RichEditorLayoutAlgorithm::RichEditorLayoutAlgorithm(std::list<RefPtr<SpanItem>> spans,
    RichEditorParagraphManager* paragraphs, LRUMap<std::uintptr_t, RefPtr<Paragraph>>* paraMapPtr,
    std::unique_ptr<StyleManager>& styleManager, bool needShowPlaceholder, AISpanLayoutInfo aiSpanLayoutInfo)
    : pManager_(paragraphs), paraMapPtr_(paraMapPtr), styleManager_(styleManager),
    needShowPlaceholder_(needShowPlaceholder)
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
    HandleAISpan(allSpans_, aiSpanLayoutInfo);
    HandleParagraphCache();
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "spans=%{public}s", SpansToString().c_str());
}

void RichEditorLayoutAlgorithm::HandleAISpan(
    const std::list<RefPtr<SpanItem>>& spans, const AISpanLayoutInfo& aiSpanLayoutInfo)
{
    ACE_SCOPED_TRACE("RichEditorLayoutAlgorithm::HandleAISpan");
    bool needShowAIDetect = aiSpanLayoutInfo.needShowAIDetect;
    if (!needShowAIDetect) {
        for (const auto& span : spans) {
            CHECK_NULL_CONTINUE(span->aiSpanResultCount != 0);
            span->aiSpanResultCount = 0;
            span->needReLayout = true;
        }
        return;
    }

    // need show ai detect

    // 1. record ai result count
    std::vector<int> aiSpanCounts;
    aiSpanCounts.reserve(spans.size());
    for (const auto& span : spans) {
        aiSpanCounts.push_back(span->aiSpanResultCount);
        span->aiSpanResultCount = 0;
    }

    // 2. update ai result count
    HandleAISpan(spans, aiSpanLayoutInfo.aiSpanMap);

    // 3. mark need relayout if result count changed
    auto spanIter = spans.begin();
    auto countsIter = aiSpanCounts.begin();
    for (; spanIter != spans.end() && countsIter != aiSpanCounts.end(); ++spanIter, ++countsIter) {
        auto& span = (*spanIter);
        IF_TRUE(span->aiSpanResultCount != 0, span->needReLayout |= span->needReLayoutParagraph);
        IF_TRUE(span->aiSpanResultCount != (*countsIter), span->needReLayout = true);
    }
}

void RichEditorLayoutAlgorithm::HandleAISpan(
    const std::list<RefPtr<SpanItem>>& spans, const std::map<int32_t, AISpan>& aiSpanMap)
{
    auto spanIter = spans.begin();
    auto aiSpanIter = aiSpanMap.begin();
    while (spanIter != spans.end() && aiSpanIter != aiSpanMap.end()) {
        const AISpan& aiSpan = aiSpanIter->second;
        const RefPtr<SpanItem>& span = *spanIter;

        bool hasIntersection = span->rangeStart < aiSpan.end && aiSpan.start < span->position;
        if (hasIntersection) {
            ++span->aiSpanResultCount;
            IF_TRUE(aiSpan.end <= span->position, ++aiSpanIter);
            IF_TRUE(span->position <= aiSpan.end, ++spanIter);
            continue;
        }

        if (!hasIntersection) {
            bool aiSpanRangeAhead = aiSpan.start >= span->position;
            bool spanRangeAhead = aiSpan.end <= span->rangeStart;
            IF_TRUE(aiSpanRangeAhead, ++spanIter);
            IF_TRUE(spanRangeAhead, ++aiSpanIter);
            continue;
        }

        TAG_LOGE(AceLogTag::ACE_RICH_TEXT,
            "HandleAISpan range error, aiSpanRange=[%{public}d,%{public}d], spanRange=[%{public}d,%{public}d]",
            aiSpan.start, aiSpan.end, span->rangeStart, span->position);
        ++aiSpanIter;
        ++spanIter;
    }
}

void RichEditorLayoutAlgorithm::HandleParagraphCache()
{
    CHECK_NULL_VOID(paraMapPtr_);
    for (const auto& group : spans_) {
        std::uintptr_t hash = 0;
        bool needReLayout = false;
        for (const auto& child : group) {
            std::uintptr_t intValue = reinterpret_cast<std::uintptr_t>(RawPtr(child));
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
        hash ^= reinterpret_cast<std::uintptr_t>(RawPtr(child));
    }
    return hash;
}

RefPtr<Paragraph> RichEditorLayoutAlgorithm::GetOrCreateParagraph(const std::list<RefPtr<SpanItem>>& group,
    const ParagraphStyle& paraStyle, const std::map<int32_t, AISpan>& aiSpanMap)
{
    if (!paraMapPtr_) {
        useParagraphCache_ = false;
        return Paragraph::CreateRichEditorParagraph(paraStyle, FontCollection::Current());
    }
    auto hash = Hash(group);
    auto it = paraMapPtr_->Get(hash);
    bool findCache = it != paraMapPtr_->End() && it->second != nullptr;
    bool directionChanged = findCache && it->second->GetParagraphStyle().direction != paraStyle.direction;
    bool fontLocaleChanged = findCache && it->second->GetParagraphStyle().fontLocale != paraStyle.fontLocale;
    bool useCache = findCache && !directionChanged && !fontLocaleChanged && paraStyle.maxLines == UINT32_MAX;
    auto paragraph = useCache ?
        it->second : Paragraph::CreateRichEditorParagraph(paraStyle, FontCollection::Current());

    // caching paragraph
    paraMapPtr_->Put(hash, paragraph);
    useParagraphCache_ = useCache;
    IF_TRUE(useParagraphCache_, ++cacheHitCount_);
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
    RefPtr<SpanItem> lastSpan = allSpans_.empty() ? nullptr : allSpans_.back();
    bool afterNewLine = !allSpans_.empty() && lastSpan && lastSpan->content.back() == u'\n';
    bool emptyAndNoPlaceholder = allSpans_.empty() && !needShowPlaceholder_;
    bool needNewLineSpan = afterNewLine || emptyAndNoPlaceholder;
    if (needNewLineSpan) {
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
    if (source) {
        target->fontStyle->UpdateFontSize(source->fontStyle->GetFontSize());
        target->textLineStyle->UpdateLineHeight(source->textLineStyle->GetLineHeight());
        if (source->textLineStyle->HasLeadingMargin()) {
            auto leadingMargin = source->textLineStyle->GetLeadingMarginValue();
            leadingMargin.pixmap.Reset();
            target->textLineStyle->UpdateLeadingMargin(leadingMargin);
        }
        target->textLineStyle->UpdateTextAlign(source->textLineStyle->GetTextAlign());
    }
    styleManager_->UpdateTextStyleByTypingStyle(target);
    styleManager_->UpdateStyleByTypingParagraphStyle(target);
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
        UpdateConstraintByLayoutPolicy(textSize, newContentConstraint, layoutWrapper);
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

void RichEditorLayoutAlgorithm::UpdateConstraintByLayoutPolicy(
    const SizeF& textSize, LayoutConstraintF& constraint, LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value() && layoutPolicy->IsHeightFix());
    const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(calcLayoutConstraint);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint.has_value());
    const auto& percentReference = layoutConstraint->percentReference;
    auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(OptionalSizeF(textSize), calcLayoutConstraint,
        percentReference);
    IF_TRUE(finalSize.Height().has_value(), constraint.maxSize.SetHeight(finalSize.Height().value()));
}

std::optional<SizeF> RichEditorLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    ACE_SCOPED_TRACE("RichEditorMeasureContent");
    pManager_->Reset();
    SetPlaceholder(layoutWrapper);
    auto optionalTextSize = MeasureContentSize(contentConstraint, layoutWrapper);
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
    UpdateMaxSizeByLayoutPolicy(contentConstraint, layoutWrapper, maxSize);
    cacheHitCount_ = 0;
    if (!CreateParagraph(textStyle, layoutProperty->GetContent().value_or(u""), layoutWrapper, maxSize.Width())) {
        return false;
    }
    CHECK_NULL_RETURN(paragraphManager_, false);
    AceScopedTrace scopedTrace("LayoutParagraph[cacheHit=%d][hitRate=%.4f]",
        cacheHitCount_, (float) cacheHitCount_ / spans_.size());
    auto& paragraphInfo = paragraphManager_->GetParagraphs();

    if (paragraphInfo.size() != spans_.size()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "paragraph size mismatch, %{public}zu vs. %{public}zu",
            paragraphInfo.size(), spans_.size());
    }
    auto pIter = paragraphInfo.begin();
    auto groupIter = spans_.begin();
    while (pIter != paragraphInfo.end() && groupIter != spans_.end()) {
        ACE_SCOPED_TRACE("LayoutOrReLayoutParagraph[range:%d,%d]", pIter->start, pIter->end);
        auto& paragraph = pIter->paragraph;
        CHECK_NULL_CONTINUE(paragraph);
        std::vector<TextStyle> textStyles;
        auto& group = *groupIter;
        bool needReLayout = false;
        bool needReLayoutParagraph = false;
        ReLayoutParagraphBySpan(layoutWrapper, textStyles, group, needReLayout, needReLayoutParagraph);
        if (!needReLayout && needReLayoutParagraph) {
            ACE_SCOPED_TRACE("ReLayoutParagraph");
            paragraph->ReLayout(maxSize.Width(), pIter->paragraphStyle, textStyles);
        } else {
            ACE_SCOPED_TRACE("LayoutParagraph");
            paragraph->Layout(maxSize.Width());
        }
        ++pIter;
        ++groupIter;
    }
    ReLayoutParagraphByLayoutPolicy(layoutWrapper, maxSize.Width());

    if (paraMapPtr_) {
        paraMapPtr_->SetCapacity(paragraphInfo.size());
        paraMapPtr_->SetCapacity(SIZE_MAX);
    }
    return ParagraphReLayout(contentConstraint);
}

void RichEditorLayoutAlgorithm::UpdateMaxSizeByLayoutPolicy(const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper, SizeF& maxSize)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value() && layoutPolicy->IsWidthFix());
    auto parentIdealWidth = contentConstraint.parentIdealSize.Width();
    CHECK_NULL_VOID(parentIdealWidth.has_value() && NearEqual(maxSize.Width(), parentIdealWidth.value()));
    maxSize.SetWidth(std::numeric_limits<float>::max());
}

void RichEditorLayoutAlgorithm::ReLayoutParagraphByLayoutPolicy(LayoutWrapper* layoutWrapper, float maxWidth)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value() && layoutPolicy->IsWidthAdaptive());
    CHECK_NULL_VOID(paragraphManager_);
    auto maxParagraphWidth = paragraphManager_->GetLongestLineWithIndent();
    CHECK_NULL_VOID(GreatNotEqual(maxWidth, maxParagraphWidth));
    paragraphManager_->LayoutParagraphs(maxParagraphWidth);
}

void RichEditorLayoutAlgorithm::ReLayoutParagraphBySpan(LayoutWrapper* layoutWrapper,
    std::vector<TextStyle>& textStyles, std::list<RefPtr<SpanItem>>& group,
    bool& needReLayout, bool& needReLayoutParagraph)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    textStyles.reserve(group.size());
    for (const auto& child : group) {
        if (!child) {
            continue;
        }
        needReLayout |= child->needReLayout;
        needReLayoutParagraph |= child->needReLayoutParagraph;
        child->ResetReLayout();
        CHECK_NULL_CONTINUE(!needReLayout);
        child->UpdateSpanTextStyle(inheritTextStyle_, frameNode);
        if (child->GetTextStyle().has_value()) {
            textStyles.emplace_back(child->GetTextStyle().value());
        } else {
            textStyles.emplace_back(TextStyle());
        }
    }
}

bool RichEditorLayoutAlgorithm::CreateParagraph(
    const TextStyle& textStyle, std::u16string content, LayoutWrapper* layoutWrapper, double maxWidth)
{
    CHECK_NULL_RETURN(!spans_.empty(), false);
    ACE_SCOPED_TRACE("RichEditorLayoutAlgorithm::CreateParagraph[groupSize:%zu]", spans_.size());
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
    UpdateFrameSizeWithLayoutPolicy(layoutWrapper, frameSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);

    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.size() != CHILDREN_SIZE) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Measure, children size error, size=%{public}zu", children.size());
        return;
    }
    auto contentLayoutWrapper = children.front();
    if (!contentLayoutWrapper) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Measure, contentLayoutWrapper is null");
        return;
    }
    auto contentNode = contentLayoutWrapper->GetHostNode();
    if (!contentNode || contentNode->GetTag() != V2::RICH_EDITOR_CONTENT_ETS_TAG) {
    TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Measure, contentNode is %{public}s",
        contentNode ? contentNode->GetTag().c_str() : "null");
        return;
    }
    contentLayoutWrapper->Measure(layoutConstraint);
}

void RichEditorLayoutAlgorithm::UpdateFrameSizeWithLayoutPolicy(LayoutWrapper* layoutWrapper, SizeF& frameSize)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_VOID(calcLayoutConstraint);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint.has_value());
    const auto& percentReference = layoutConstraint->percentReference;
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value() && layoutPolicy->IsAdaptive());
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentSize = content->GetRect().GetSize();
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    AddPaddingToSize(padding, contentSize);
    auto fixIdealSize = UpdateOptionSizeByCalcLayoutConstraint(OptionalSizeF(contentSize), calcLayoutConstraint,
        percentReference);
    bool widthAdaptive = layoutPolicy->IsWidthAdaptive() && fixIdealSize.Width().has_value();
    bool heightAdaptive = layoutPolicy->IsHeightAdaptive() && fixIdealSize.Height().has_value();
    IF_TRUE(widthAdaptive, frameSize.SetWidth(fixIdealSize.Width().value()));
    IF_TRUE(heightAdaptive, frameSize.SetHeight(fixIdealSize.Height().value()));
}

void RichEditorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto context = layoutWrapper->GetHostNode()->GetContext();
    CHECK_NULL_VOID(context);
    parentGlobalOffset_ = layoutWrapper->GetHostNode()->GetPaintRectOffsetNG() - context->GetRootRect().GetOffset();
    MultipleParagraphLayoutAlgorithm::Layout(layoutWrapper);

    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.size() != CHILDREN_SIZE) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Layout, children size error, size=%{public}zu", children.size());
        return;
    }
    auto contentLayoutWrapper = children.front();
    if (!contentLayoutWrapper) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Measure, contentLayoutWrapper is null");
        return;
    }
    auto contentNode = contentLayoutWrapper->GetHostNode();
    if (!contentNode || contentNode->GetTag() != V2::RICH_EDITOR_CONTENT_ETS_TAG) {
    TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Layout, contentNode is %{public}s",
        contentNode ? contentNode->GetTag().c_str() : "null");
        return;
    }
    contentLayoutWrapper->SetActive(true);
    contentLayoutWrapper->Layout();
}

ChildrenListWithGuard RichEditorLayoutAlgorithm::GetAllChildrenWithBuild(LayoutWrapper* layoutWrapper)
{
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.size() != CHILDREN_SIZE) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "GetAllChildrenWithBuild, children size=%{public}zu", children.size());
        return children;
    }
    auto& contentLayoutWrapper = *(children.begin());
    CHECK_NULL_RETURN(contentLayoutWrapper, children);
    return contentLayoutWrapper->GetAllChildrenWithBuild();
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
    auto style = ParagraphUtil::GetParagraphStyle(textStyle);
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
