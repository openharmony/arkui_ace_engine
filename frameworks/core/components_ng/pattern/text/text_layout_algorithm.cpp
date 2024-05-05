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

#include "core/components_ng/pattern/text/text_layout_algorithm.h"

#include <limits>

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/render/font_collection.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

TextLayoutAlgorithm::TextLayoutAlgorithm(
    std::list<RefPtr<SpanItem>> spans, RefPtr<ParagraphManager> pManager, bool isSpanStringMode, bool isMarquee)
{
    paragraphManager_ = pManager;
    isSpanStringMode_ = isSpanStringMode;

    if (!isSpanStringMode) {
        if (!spans.empty()) {
            spans_.emplace_back(std::move(spans));
        }
        return;
    }
    if (spans.empty()) {
        return;
    }
    if (isMarquee) {
        for (const auto& span : spans) {
            span->SetNeedRemoveNewLine(false);
        }
        spans_.emplace_back(std::move(spans));
        return;
    }
    ConstructParagraphSpanGroup(spans);
    if (!spans.empty()) {
        auto maxlines = spans.front()->textLineStyle->GetMaxLines().value_or(UINT32_MAX);
        spanStringHasMaxLines_ |= maxlines != UINT32_MAX;
        spans_.emplace_back(std::move(spans));
    }
}

TextLayoutAlgorithm::TextLayoutAlgorithm() = default;

void TextLayoutAlgorithm::ConstructParagraphSpanGroup(std::list<RefPtr<SpanItem>>& spans)
{
    // split spans into groups by mew paragraph style
    auto it = spans.begin();
    ParagraphStyle pStyle;
    GetSpanParagraphStyle((*it)->textLineStyle, pStyle);
    while (it != spans.end()) {
        auto spanItem = *it;
        if (!spanItem) {
            ++it;
            continue;
        }
        spanItem->SetNeedRemoveNewLine(false);
        auto wContent = StringUtils::ToWstring(spanItem->content);
        if (wContent.back() == L'\n') {
            if (std::next(it) == spans.end()) {
                break;
            }
            auto next = *(std::next(it));
            ParagraphStyle nextSpanParagraphStyle;
            if (next) {
                GetSpanParagraphStyle(next->textLineStyle, nextSpanParagraphStyle);
            } else {
                break;
            }
            if (pStyle != nextSpanParagraphStyle ||
                (pStyle.leadingMargin.has_value() && pStyle.leadingMargin->pixmap)) {
                std::list<RefPtr<SpanItem>> newGroup;
                spanItem->SetNeedRemoveNewLine(true);
                newGroup.splice(newGroup.begin(), spans, spans.begin(), std::next(it));
                spanStringHasMaxLines_ |= pStyle.maxLines != UINT32_MAX;
                spans_.emplace_back(std::move(newGroup));
                it = spans.begin();
                pStyle = nextSpanParagraphStyle;
                continue;
            }
        }
        ++it;
    }
}

void TextLayoutAlgorithm::OnReset() {}

std::optional<SizeF> TextLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    TextStyle textStyle;
    ConstructTextStyles(contentConstraint, layoutWrapper, textStyle);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, std::nullopt);

    if (textStyle.GetTextOverflow() == TextOverflow::MARQUEE) { // create a paragraph with all text in 1 line
        return BuildTextRaceParagraph(textStyle, textLayoutProperty, contentConstraint, layoutWrapper);
    }

    if (isSpanStringMode_) {
        if (spanStringHasMaxLines_) {
            textStyle.SetMaxLines(UINT32_MAX);
        }
        BuildParagraph(textStyle, textLayoutProperty, contentConstraint, layoutWrapper);
    } else {
        if (!AddPropertiesAndAnimations(textStyle, textLayoutProperty, contentConstraint, layoutWrapper)) {
            return std::nullopt;
        }
    }

    textStyle_ = textStyle;
    baselineOffset_ = static_cast<float>(textStyle.GetBaselineOffset().ConvertToPx());
    if (NearZero(contentConstraint.maxSize.Height()) || NearZero(contentConstraint.maxSize.Width())) {
        return SizeF {};
    }
    CHECK_NULL_RETURN(paragraphManager_, std::nullopt);
    auto height = paragraphManager_->GetHeight();

    auto heightFinal = static_cast<float>(height + std::fabs(baselineOffset_));
    if (contentConstraint.selfIdealSize.Height().has_value()) {
        heightFinal = std::min(heightFinal, contentConstraint.selfIdealSize.Height().value());
    } else {
        heightFinal = std::min(heightFinal, contentConstraint.maxSize.Height());
    }
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    if (frameNode->GetTag() == V2::TEXT_ETS_TAG && textLayoutProperty->GetContent().value_or("").empty() &&
        NonPositive(paragraphManager_->GetLongestLine())) {
        // text content is empty
        ACE_SCOPED_TRACE("TextHeightFinal [%f], TextContentWidth [%f], FontSize [%lf]", heightFinal,
            paragraphManager_->GetMaxWidth(), textStyle.GetFontSize().ConvertToPx());
        return SizeF {};
    }
    return SizeF(paragraphManager_->GetMaxWidth(), heightFinal);
}

bool TextLayoutAlgorithm::AddPropertiesAndAnimations(TextStyle& textStyle,
    const RefPtr<TextLayoutProperty>& textLayoutProperty, const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    bool result = false;
    switch (textLayoutProperty->GetHeightAdaptivePolicyValue(TextHeightAdaptivePolicy::MAX_LINES_FIRST)) {
        case TextHeightAdaptivePolicy::MAX_LINES_FIRST:
            result = BuildParagraph(textStyle, textLayoutProperty, contentConstraint, layoutWrapper);
            break;
        case TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST:
            result = BuildParagraphAdaptUseMinFontSize(textStyle, textLayoutProperty, contentConstraint, layoutWrapper);
            break;
        case TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST:
            result =
                BuildParagraphAdaptUseLayoutConstraint(textStyle, textLayoutProperty, contentConstraint, layoutWrapper);
            break;
        default:
            break;
    }
    return result;
}

void TextLayoutAlgorithm::UpdateParagraphForAISpan(
    const TextStyle& textStyle, LayoutWrapper* layoutWrapper, const RefPtr<Paragraph>& paragraph)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    auto textForAI = pattern->GetTextForAI();
    auto wTextForAI = StringUtils::ToWstring(textForAI);
    int32_t wTextForAILength = static_cast<int32_t>(wTextForAI.length());
    int32_t preEnd = 0;
    DragSpanPosition dragSpanPosition;
    dragSpanPosition.dragStart = pattern->GetRecoverStart();
    dragSpanPosition.dragEnd = pattern->GetRecoverEnd();
    bool isDragging = pattern->IsDragging();
    TextStyle aiSpanTextStyle = textStyle;
    ResetAiSpanTextStyle(frameNode, aiSpanTextStyle);
    for (auto kv : pattern->GetAISpanMap()) {
        if (preEnd >= wTextForAILength) {
            break;
        }
        auto aiSpan = kv.second;
        if (aiSpan.start < preEnd) {
            TAG_LOGI(AceLogTag::ACE_TEXT, "Error prediction");
            continue;
        }
        if (preEnd < aiSpan.start) {
            dragSpanPosition.spanStart = preEnd;
            dragSpanPosition.spanEnd = aiSpan.start;
            GrayDisplayAISpan(dragSpanPosition, wTextForAI, textStyle, isDragging, paragraph);
        }
        preEnd = aiSpan.end;
        dragSpanPosition.spanStart = aiSpan.start;
        dragSpanPosition.spanEnd = aiSpan.end;
        GrayDisplayAISpan(dragSpanPosition, wTextForAI, aiSpanTextStyle, isDragging, paragraph);
    }
    if (preEnd < wTextForAILength) {
        dragSpanPosition.spanStart = preEnd;
        dragSpanPosition.spanEnd = wTextForAILength;
        GrayDisplayAISpan(dragSpanPosition, wTextForAI, textStyle, isDragging, paragraph);
    }
}

void TextLayoutAlgorithm::ResetAiSpanTextStyle(const RefPtr<FrameNode>& frameNode, TextStyle& aiSpanTextStyle)
{
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto hyerlinkTheme = pipeline->GetTheme<HyperlinkTheme>();
    CHECK_NULL_VOID(hyerlinkTheme);
    auto hyerlinkColor = hyerlinkTheme->GetTextColor();
    aiSpanTextStyle.SetTextColor(hyerlinkColor);
    aiSpanTextStyle.SetTextDecoration(TextDecoration::UNDERLINE);
    aiSpanTextStyle.SetTextDecorationColor(hyerlinkColor);
    aiSpanTextStyle.SetTextDecorationStyle(TextDecorationStyle::SOLID);
}

void TextLayoutAlgorithm::GrayDisplayAISpan(const DragSpanPosition& dragSpanPosition, const std::wstring wTextForAI,
    const TextStyle& textStyle, bool isDragging, const RefPtr<Paragraph>& paragraph)
{
    int32_t dragStart = dragSpanPosition.dragStart;
    int32_t dragEnd = dragSpanPosition.dragEnd;
    int32_t spanStart = dragSpanPosition.spanStart;
    int32_t spanEnd = dragSpanPosition.spanEnd;
    std::vector<std::string> contents = {};
    std::string firstParagraph = "";
    std::string secondParagraph = "";
    std::string thirdParagraph = "";
    if (dragStart > spanEnd || dragEnd < spanStart || !isDragging) {
        firstParagraph = StringOutBoundProtection(spanStart, spanEnd - spanStart, wTextForAI);
    } else if (spanStart <= dragStart && spanEnd >= dragStart && spanEnd <= dragEnd) {
        firstParagraph = StringOutBoundProtection(spanStart, dragStart - spanStart, wTextForAI);
        secondParagraph = StringOutBoundProtection(dragStart, spanEnd - dragStart, wTextForAI);
    } else if (spanStart >= dragStart && spanEnd <= dragEnd) {
        secondParagraph = StringOutBoundProtection(spanStart, spanEnd - spanStart, wTextForAI);
    } else if (spanStart <= dragStart && spanEnd >= dragEnd) {
        firstParagraph = StringOutBoundProtection(spanStart, dragStart - spanStart, wTextForAI);
        secondParagraph = StringOutBoundProtection(dragStart, dragEnd - dragStart, wTextForAI);
        thirdParagraph = StringOutBoundProtection(dragEnd, spanEnd - dragEnd, wTextForAI);
    } else {
        secondParagraph = StringOutBoundProtection(spanStart, dragEnd - spanStart, wTextForAI);
        thirdParagraph = StringOutBoundProtection(dragEnd, spanEnd - dragEnd, wTextForAI);
    }
    contents = { firstParagraph, secondParagraph, thirdParagraph };
    CreateParagraphDrag(textStyle, contents, paragraph);
}

std::string TextLayoutAlgorithm::StringOutBoundProtection(int32_t position, int32_t length, std::wstring wTextForAI)
{
    int32_t wTextForAILength = static_cast<int32_t>(wTextForAI.length());
    if (position >= wTextForAILength || length > wTextForAILength - position) {
        return "";
    } else {
        return StringUtils::ToString(wTextForAI.substr(position, length));
    }
}

bool TextLayoutAlgorithm::CreateParagraph(
    const TextStyle& textStyle, std::string content, LayoutWrapper* layoutWrapper, double maxWidth)
{
    if (!paragraphManager_) {
        paragraphManager_ = AceType::MakeRefPtr<ParagraphManager>();
    }
    paragraphManager_->Reset();
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, false);
    if (pattern->IsSensitiveEnalbe()) {
        UpdateSensitiveContent(content);
    }
    // default paragraph style
    auto paraStyle = GetParagraphStyle(textStyle, content, layoutWrapper);
    if ((Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && spans_.empty()) || isSpanStringMode_) {
        paraStyle.fontSize = textStyle.GetFontSize().ConvertToPx();
    }
    paraStyle.leadingMarginAlign = Alignment::CENTER;

    // SymbolGlyph
    if (frameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        return UpdateSymbolTextStyle(textStyle, paraStyle, layoutWrapper, frameNode);
    }
    if (spans_.empty()) {
        // only use for text.
        return UpdateSingleParagraph(layoutWrapper, paraStyle, textStyle, content, maxWidth);
    } else {
        return UpdateParagraphBySpan(layoutWrapper, paraStyle, maxWidth);
    }
}

bool TextLayoutAlgorithm::UpdateSymbolTextStyle(const TextStyle& textStyle, const ParagraphStyle& paraStyle,
    LayoutWrapper* layoutWrapper, RefPtr<FrameNode>& frameNode)
{
    auto && paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_RETURN(paragraph, false);
    auto layoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    auto symbolSourceInfo = layoutProperty->GetSymbolSourceInfo();
    CHECK_NULL_RETURN(symbolSourceInfo, false);
    TextStyle symbolTextStyle = textStyle;
    symbolTextStyle.isSymbolGlyph_ = true;
    symbolTextStyle.SetRenderStrategy(
        symbolTextStyle.GetRenderStrategy() < 0 ? 0 : symbolTextStyle.GetRenderStrategy());
    symbolTextStyle.SetEffectStrategy(
        symbolTextStyle.GetEffectStrategy() < 0 ? 0 : symbolTextStyle.GetEffectStrategy());
    symbolTextStyle.SetFontFamilies({ "HM Symbol" });
    paragraph->PushStyle(symbolTextStyle);
    auto symbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    symbolEffectOptions.Reset();
    layoutProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
    if (symbolTextStyle.GetSymbolEffectOptions().has_value()) {
        auto symboloptiOns = symbolTextStyle.GetSymbolEffectOptions().value();
        symboloptiOns.Reset();
    }
    paragraph->AddSymbol(symbolSourceInfo->GetUnicode());
    paragraph->PopStyle();
    paragraph->Build();
    paragraph->SetParagraphSymbolAnimation(frameNode);
    paragraphManager_->AddParagraph({ .paragraph = paragraph, .paragraphStyle = paraStyle, .start = 0, .end = 2 });
    return true;
}

void TextLayoutAlgorithm::CreateParagraphDrag(
    const TextStyle& textStyle, const std::vector<std::string>& contents, const RefPtr<Paragraph>& paragraph)
{
    TextStyle dragTextStyle = textStyle;
    Color color = textStyle.GetTextColor().ChangeAlpha(DRAGGED_TEXT_TRANSPARENCY);
    dragTextStyle.SetTextColor(color);
    std::vector<TextStyle> textStyles { textStyle, dragTextStyle, textStyle };

    CHECK_NULL_VOID(paragraph);
    for (size_t i = 0; i < contents.size(); i++) {
        std::string splitStr = contents[i];
        if (splitStr.empty()) {
            continue;
        }
        auto& style = textStyles[i];
        paragraph->PushStyle(style);
        StringUtils::TransformStrCase(splitStr, static_cast<int32_t>(style.GetTextCase()));
        paragraph->AddText(StringUtils::Str8ToStr16(splitStr));
        paragraph->PopStyle();
    }
}

bool TextLayoutAlgorithm::CreateParagraphAndLayout(const TextStyle& textStyle, const std::string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, bool needLayout)
{
    auto maxSize = MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint);
    if (!CreateParagraph(textStyle, content, layoutWrapper, maxSize.Width())) {
        return false;
    }
    CHECK_NULL_RETURN(paragraphManager_, false);
    auto paragraphInfo = paragraphManager_->GetParagraphs();
    for (auto pIter = paragraphInfo.begin(); pIter != paragraphInfo.end(); pIter++) {
        auto paragraph = pIter->paragraph;
        CHECK_NULL_RETURN(paragraph, false);
        paragraph->Layout(maxSize.Width());
    }
    return true;
}

OffsetF TextLayoutAlgorithm::GetContentOffset(LayoutWrapper* layoutWrapper)
{
    SetContentOffset(layoutWrapper);
    return OffsetF(0.0f, 0.0f);
}

bool TextLayoutAlgorithm::AdaptMinTextSize(TextStyle& textStyle, const std::string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    if (!textStyle.GetAdaptMaxFontSize().NormalizeToPx(pipeline->GetDipScale(), pipeline->GetFontScale(),
            pipeline->GetLogicScale(), contentConstraint.maxSize.Height(), maxFontSize)) {
        return false;
    }
    if (!textStyle.GetAdaptMinFontSize().NormalizeToPx(pipeline->GetDipScale(), pipeline->GetFontScale(),
            pipeline->GetLogicScale(), contentConstraint.maxSize.Height(), minFontSize)) {
        return false;
    }
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(minFontSize, 0.0)) {
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper)) {
            TAG_LOGE(AceLogTag::ACE_TEXT, "create paragraph error");
            return false;
        }
        return true;
    }
    constexpr Dimension ADAPT_UNIT = 1.0_fp;
    Dimension step = ADAPT_UNIT;
    if (GreatNotEqual(textStyle.GetAdaptFontSizeStep().Value(), 0.0)) {
        step = textStyle.GetAdaptFontSizeStep();
    }
    double stepSize = 0.0;
    if (!step.NormalizeToPx(pipeline->GetDipScale(), pipeline->GetFontScale(), pipeline->GetLogicScale(),
            contentConstraint.maxSize.Height(), stepSize)) {
        return false;
    }
    auto maxSize = MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint);
    while (GreatOrEqual(maxFontSize, minFontSize)) {
        textStyle.SetFontSize(Dimension(maxFontSize));
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper)) {
            TAG_LOGE(AceLogTag::ACE_TEXT, "create paragraph error");
            return false;
        }
        if (!DidExceedMaxLines(maxSize)) {
            break;
        }
        maxFontSize -= stepSize;
    }
    return true;
}

float TextLayoutAlgorithm::GetBaselineOffset() const
{
    return baselineOffset_;
}

bool TextLayoutAlgorithm::UpdateSingleParagraph(LayoutWrapper* layoutWrapper, ParagraphStyle paraStyle,
    const TextStyle& textStyle, const std::string& content, double maxWidth)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto && paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_RETURN(paragraph, false);
    paragraph->PushStyle(textStyle);
    if (pattern->NeedShowAIDetect()) {
        UpdateParagraphForAISpan(textStyle, layoutWrapper, paragraph);
    } else {
        if (pattern->IsDragging()) {
            auto dragContents = pattern->GetDragContents();
            CreateParagraphDrag(textStyle, dragContents, paragraph);
        } else {
            auto value = content;
            StringUtils::TransformStrCase(value, static_cast<int32_t>(textStyle.GetTextCase()));
            paragraph->AddText(StringUtils::Str8ToStr16(value));
        }
    }
    paragraph->Build();
    ApplyIndent(paraStyle, paragraph, maxWidth);
    paragraphManager_->AddParagraph({ .paragraph = paragraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = StringUtils::Str8ToStr16(content).length() });
    return true;
}

bool TextLayoutAlgorithm::BuildParagraph(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    if (!textStyle.GetAdaptTextSize() || !spans_.empty()) {
        if (!CreateParagraphAndLayout(
                textStyle, layoutProperty->GetContent().value_or(""), contentConstraint, layoutWrapper)) {
            TAG_LOGE(AceLogTag::ACE_TEXT, "create paragraph error");
            return false;
        }
    } else {
        if (!AdaptMinTextSize(textStyle, layoutProperty->GetContent().value_or(""), contentConstraint, layoutWrapper)) {
            return false;
        }
    }
    return ParagraphReLayout(contentConstraint);
}

bool TextLayoutAlgorithm::BuildParagraphAdaptUseMinFontSize(TextStyle& textStyle,
    const RefPtr<TextLayoutProperty>& layoutProperty, const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    if (!AdaptMaxTextSize(textStyle, layoutProperty->GetContent().value_or(""), contentConstraint, layoutWrapper)) {
        return false;
    }
    auto paragraph = GetSingleParagraph();
    CHECK_NULL_RETURN(paragraph, false);
    // Confirmed specification: The width of the text paragraph covers the width of the component, so this code is
    // generally not allowed to be modified
    if (!contentConstraint.selfIdealSize.Width()) {
        float paragraphNewWidth = std::min(std::min(paragraph->GetTextWidth(), paragraph->GetMaxWidth()) + indent_,
            MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint).Width());
        paragraphNewWidth =
            std::clamp(paragraphNewWidth, contentConstraint.minSize.Width(), contentConstraint.maxSize.Width());
        if (!NearEqual(paragraphNewWidth, paragraph->GetMaxWidth())) {
            paragraph->Layout(std::ceil(paragraphNewWidth));
        }
    }

    return true;
}

bool TextLayoutAlgorithm::BuildParagraphAdaptUseLayoutConstraint(TextStyle& textStyle,
    const RefPtr<TextLayoutProperty>& layoutProperty, const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    // Create the paragraph and obtain the height.
    if (!BuildParagraph(textStyle, layoutProperty, contentConstraint, layoutWrapper)) {
        return false;
    }
    auto paragraph = GetSingleParagraph();
    CHECK_NULL_RETURN(paragraph, false);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto height = static_cast<float>(paragraph->GetHeight());
    double minTextSizeHeight = 0.0;
    textStyle.GetAdaptMinFontSize().NormalizeToPx(
        pipeline->GetDipScale(), pipeline->GetFontScale(), pipeline->GetLogicScale(), height, minTextSizeHeight);
    if (LessOrEqual(minTextSizeHeight, 0.0)) {
        textStyle.GetFontSize().NormalizeToPx(
            pipeline->GetDipScale(), pipeline->GetFontScale(), pipeline->GetLogicScale(), height, minTextSizeHeight);
    }
    if (textStyle.GetMaxLines() == UINT32_MAX) {
        double baselineOffset = 0.0;
        textStyle.GetBaselineOffset().NormalizeToPx(pipeline->GetDipScale(), pipeline->GetFontScale(),
            pipeline->GetLogicScale(), contentConstraint.maxSize.Height(), baselineOffset);
        double lineHeight = minTextSizeHeight;
        if (textStyle.HasHeightOverride()) {
            textStyle.GetLineHeight().NormalizeToPx(pipeline->GetDipScale(), pipeline->GetFontScale(),
                pipeline->GetLogicScale(), minTextSizeHeight, lineHeight);
        }
        uint32_t maxLines = (contentConstraint.maxSize.Height() - baselineOffset - minTextSizeHeight) / (lineHeight);
        textStyle.SetMaxLines(maxLines);
        textStyle.DisableAdaptTextSize();

        if (!BuildParagraph(textStyle, layoutProperty, contentConstraint, layoutWrapper)) {
            return false;
        }
    }
    // Reducing the value of MaxLines to make sure the parapraph could be layout in the constraint of height.
    paragraph = GetSingleParagraph();
    height = static_cast<float>(paragraph->GetHeight());
    while (GreatNotEqual(height, contentConstraint.maxSize.Height())) {
        auto maxLines = textStyle.GetMaxLines();
        if (maxLines == 0) {
            break;
        } else {
            maxLines = textStyle.GetMaxLines() - 1;
            textStyle.SetMaxLines(maxLines);
        }
        if (!BuildParagraph(textStyle, layoutProperty, contentConstraint, layoutWrapper)) {
            return false;
        }
        paragraph = GetSingleParagraph();
        height = static_cast<float>(paragraph->GetHeight());
    }
    return true;
}

std::optional<SizeF> TextLayoutAlgorithm::BuildTextRaceParagraph(TextStyle& textStyle,
    const RefPtr<TextLayoutProperty>& layoutProperty, const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    // create a paragraph with all text in 1 line
    textStyle.SetTextOverflow(TextOverflow::CLIP);
    textStyle.SetMaxLines(1);
    textStyle.SetTextIndent(Dimension(0.0f));

    if (!textStyle.GetAdaptTextSize()) {
        if (!CreateParagraph(textStyle, layoutProperty->GetContent().value_or(""), layoutWrapper)) {
            return std::nullopt;
        }
    } else {
        if (!AdaptMinTextSize(textStyle, layoutProperty->GetContent().value_or(""), contentConstraint, layoutWrapper)) {
            return std::nullopt;
        }
    }
    textStyle_ = textStyle;
    auto paragraph = GetSingleParagraph();

    // layout the paragraph to the width of text
    paragraph->Layout(std::numeric_limits<float>::max());
    float paragraphWidth = paragraph->GetLongestLine();
    if (contentConstraint.selfIdealSize.Width().has_value()) {
        paragraphWidth = std::max(contentConstraint.selfIdealSize.Width().value(), paragraphWidth);
    } else {
        paragraphWidth = std::max(contentConstraint.minSize.Width(), paragraphWidth);
    }
    paragraphWidth = std::ceil(paragraphWidth);
    paragraph->Layout(paragraphWidth);

    auto pipeline = PipelineContext::GetCurrentContext();
    // calculate the content size
    auto height = static_cast<float>(paragraph->GetHeight());
    baselineOffset_ = static_cast<float>(layoutProperty->GetBaselineOffsetValue(Dimension()).ConvertToPx());
    float heightFinal =
        std::min(static_cast<float>(height + std::fabs(baselineOffset_)), contentConstraint.maxSize.Height());

    float widthFinal = paragraphWidth;
    if (contentConstraint.selfIdealSize.Width().has_value()) {
        if (contentConstraint.selfIdealSize.Width().value() < paragraphWidth) {
            widthFinal = contentConstraint.selfIdealSize.Width().value();
        }
    } else if (contentConstraint.maxSize.Width() < paragraphWidth) {
        widthFinal = contentConstraint.maxSize.Width();
    }
    return SizeF(widthFinal, heightFinal);
}

bool TextLayoutAlgorithm::AdaptMaxTextSize(TextStyle& textStyle, const std::string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    constexpr Dimension ADAPT_UNIT = 1.0_fp;
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, false);
    auto step = textLayoutProperty->GetAdaptFontSizeStepValue(ADAPT_UNIT);
    return AdaptMaxFontSize(textStyle, content, step, contentConstraint, layoutWrapper);
}

std::optional<TextStyle> TextLayoutAlgorithm::GetTextStyle() const
{
    return textStyle_;
}

void TextLayoutAlgorithm::UpdateSensitiveContent(std::string& content)
{
    std::replace_if(
        content.begin(), content.end(),
        [](char c) {
            return c != '\n';
        }, '-');
}

size_t TextLayoutAlgorithm::GetLineCount() const
{
    size_t count = 0;
    CHECK_NULL_RETURN(paragraphManager_, 0);
    auto paragraphInfo = paragraphManager_->GetParagraphs();
    for (auto pIter = paragraphInfo.begin(); pIter != paragraphInfo.end(); pIter++) {
        auto paragraph = pIter->paragraph;
        CHECK_NULL_RETURN(paragraph, 0);
        count += paragraph->GetLineCount();
    }
    return count;
}
} // namespace OHOS::Ace::NG
