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

#include "base/geometry/dimension.h"
#include "base/log/ace_trace.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "base/utils/utf_helper.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t HUNDRED = 100;
constexpr int32_t TWENTY = 20;
}; // namespace

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
    GetSpanParagraphStyle(nullptr, (*it), pStyle);
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
                GetSpanParagraphStyle(nullptr, next, nextSpanParagraphStyle);
            } else {
                break;
            }
            if (pStyle != nextSpanParagraphStyle ||
                (pStyle.leadingMargin.has_value() && pStyle.leadingMargin->pixmap) || Positive(pStyle.indent.Value()) ||
                pStyle.maxLines != UINT32_MAX) {
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
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    ACE_SCOPED_TRACE("TextLayoutAlgorithm::MeasureContent[id:%d]", host->GetId());
    auto pattern = host->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, std::nullopt);
    CheckNeedReCreateParagraph(textLayoutProperty, pattern);
    TextStyle textStyle;
    ConstructTextStyles(contentConstraint, layoutWrapper, textStyle);
    if (textStyle.GetTextOverflow() == TextOverflow::MARQUEE) { // create a paragraph with all text in 1 line
        isMarquee_ = true;
        auto result = BuildTextRaceParagraph(textStyle, textLayoutProperty, contentConstraint, layoutWrapper);
        ResetNeedReCreateParagraph(textLayoutProperty);
        return result;
    }
    if (isSpanStringMode_) {
        if (spanStringHasMaxLines_) {
            textStyle.SetMaxLines(UINT32_MAX);
        }
        textStyle_ = textStyle;
        BuildParagraph(textStyle, textLayoutProperty, contentConstraint, layoutWrapper);
    } else {
        if (!AddPropertiesAndAnimations(textStyle, textLayoutProperty, contentConstraint, layoutWrapper)) {
            return std::nullopt;
        }
    }
    ResetNeedReCreateParagraph(textLayoutProperty);
    textStyle_ = textStyle;
    baselineOffset_ = textStyle.GetBaselineOffset().ConvertToPxDistribute(
        textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    if (NearZero(contentConstraint.maxSize.Height()) || NearZero(contentConstraint.maxSize.Width())) {
        return SizeF {};
    }
    CHECK_NULL_RETURN(paragraphManager_, std::nullopt);
    auto height = paragraphManager_->GetHeight();
    auto maxWidth = paragraphManager_->GetMaxWidth();
    auto longestLine = paragraphManager_->GetLongestLine();
    auto heightFinal = static_cast<float>(height + std::fabs(baselineOffset_));
    if (contentConstraint.selfIdealSize.Height().has_value()) {
        heightFinal = std::min(heightFinal, contentConstraint.selfIdealSize.Height().value());
    } else {
        heightFinal = std::min(heightFinal, contentConstraint.maxSize.Height());
    }
    if (host->GetTag() == V2::TEXT_ETS_TAG && textLayoutProperty->GetContent().value_or(u"").empty() &&
        NonPositive(longestLine)) {
        ACE_SCOPED_TRACE("TextHeightFinal [%f], TextContentWidth [%f], FontSize [%lf]", heightFinal, maxWidth,
            textStyle.GetFontSize().ConvertToPxDistribute(
                textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale()));
        return SizeF {};
    }
    return SizeF(maxWidth, heightFinal);
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

void TextLayoutAlgorithm::CheckNeedReCreateParagraph(
    const RefPtr<TextLayoutProperty>& textLayoutProperty, const RefPtr<TextPattern>& textPattern)
{
    CHECK_NULL_VOID(textLayoutProperty);
    CHECK_NULL_VOID(textPattern);
    auto useExternalParagraph = textPattern->GetExternalParagraph() && !textPattern->NeedShowAIDetect();
    needReCreateParagraph_ =
        textLayoutProperty->GetNeedReCreateParagraphValue(false) || !spans_.empty() || useExternalParagraph ||
        textPattern->IsDragging() || textLayoutProperty->GetAdaptMaxFontSize().has_value() ||
        textLayoutProperty->GetAdaptMinFontSize().has_value() ||
        textLayoutProperty->GetHeightAdaptivePolicyValue(TextHeightAdaptivePolicy::MAX_LINES_FIRST) !=
            TextHeightAdaptivePolicy::MAX_LINES_FIRST;
}

void TextLayoutAlgorithm::ResetNeedReCreateParagraph(const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->ResetNeedReCreateParagraph();
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
    TextStyle aiSpanStyle = textStyle;
    pattern->ModifyAISpanStyle(aiSpanStyle);
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
        GrayDisplayAISpan(dragSpanPosition, wTextForAI, aiSpanStyle, isDragging, paragraph);
    }
    if (preEnd < wTextForAILength) {
        dragSpanPosition.spanStart = preEnd;
        dragSpanPosition.spanEnd = wTextForAILength;
        GrayDisplayAISpan(dragSpanPosition, wTextForAI, textStyle, isDragging, paragraph);
    }
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
    if (position >= 0 && position < wTextForAILength && length >= 0 && length <= wTextForAILength - position) {
        return StringUtils::ToString(wTextForAI.substr(position, length));
    }
    return "";
}

bool TextLayoutAlgorithm::CreateParagraph(
    const TextStyle& textStyle, std::u16string content, LayoutWrapper* layoutWrapper, double maxWidth)
{
    if (!paragraphManager_) {
        paragraphManager_ = AceType::MakeRefPtr<ParagraphManager>();
    }
    paragraphManager_->Reset();
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->ClearCustomSpanPlaceholderInfo();
    if (pattern->IsSensitiveEnalbe()) {
        UpdateSensitiveContent(content);
    }
    auto useExternalParagraph = pattern->GetExternalParagraph() && !pattern->NeedShowAIDetect();
    auto externalParagraphStyle = pattern->GetExternalParagraphStyle();
    auto paraStyle = GetParagraphStyle(textStyle, content, layoutWrapper);
    if (pattern->GetExternalParagraph()) {
        if (!useExternalParagraph && externalParagraphStyle) {
            paraStyle = externalParagraphStyle.value();
        }
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) || isSpanStringMode_) {
        paraStyle.fontSize = textStyle.GetFontSize().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }
    paraStyle.leadingMarginAlign = Alignment::CENTER;
    // SymbolGlyph
    if (frameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        return UpdateSymbolTextStyle(textStyle, paraStyle, layoutWrapper, frameNode);
    }
    if (spans_.empty() || useExternalParagraph) {
        // only use for text.
        return UpdateSingleParagraph(layoutWrapper, paraStyle, textStyle, content, maxWidth);
    } else {
        return UpdateParagraphBySpan(layoutWrapper, paraStyle, maxWidth, textStyle);
    }
}

bool TextLayoutAlgorithm::UpdateSymbolTextStyle(const TextStyle& textStyle, const ParagraphStyle& paraStyle,
    LayoutWrapper* layoutWrapper, RefPtr<FrameNode>& frameNode)
{
    auto &&paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
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
    if (symbolTextStyle.GetSymbolEffectOptions().has_value()) {
        auto symbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
        symbolEffectOptions.Reset();
        layoutProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
        if (symbolTextStyle.GetSymbolEffectOptions().has_value()) {
            auto symboloptiOns = symbolTextStyle.GetSymbolEffectOptions().value();
            symboloptiOns.Reset();
        }
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
    Color textDecorationColor = textStyle.GetTextDecorationColor().ChangeAlpha(DRAGGED_TEXT_TRANSPARENCY);
    dragTextStyle.SetTextDecorationColor(textDecorationColor);
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

bool TextLayoutAlgorithm::CreateParagraphAndLayout(const TextStyle& textStyle, const std::u16string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, bool needLayout)
{
    auto maxSize = MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint);
    ACE_TEXT_SCOPED_TRACE("CreateParagraphAndLayout[maxSize:%s][Len:%d][needReCreateParagraph:%d]",
        maxSize.ToString().c_str(), static_cast<int32_t>(content.length()), needReCreateParagraph_);
    if (needReCreateParagraph_ && !CreateParagraph(textStyle, content, layoutWrapper, maxSize.Width())) {
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
    return SetContentOffset(layoutWrapper);
}

bool TextLayoutAlgorithm::AdaptMinTextSize(TextStyle& textStyle, const std::u16string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    ACE_TEXT_SCOPED_TRACE("TextLayoutAlgorithm::AdaptMinTextSize[Length:%d]", static_cast<int32_t>(content.length()));
    // IsNeedAdaptFontSize
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint);
    if (!IsNeedAdaptFontSize(maxFontSize, minFontSize)) {
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper)) {
            TAG_LOGW(AceLogTag::ACE_TEXT, "create paragraph fail, contentConstraint:%{public}s",
                contentConstraint.ToString().c_str());
            return false;
        }
        return true;
    }
    // Get suitableSize and set
    auto ret = GetSuitableSize(textStyle, content, contentConstraint, layoutWrapper);
    if (!ret.first) {
        textStyle.SetFontSize(Dimension(minFontSize));
        return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper);
    } else if (ret.first && NearEqual(textStyle.GetFontSize().Value(), ret.second)) {
        return true; // The font is already set, no need to call CreateParagraphAndLayout again.
    } else {
        textStyle.SetFontSize(Dimension(ret.second));
        return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper);
    }
}

/**
 * brief: Find the optimal font size within the range [minFontSize, maxFontSize].
 * return: std::pair<bool, double>
 *         - first: A boolean indicating whether a suitable size was found (true if found, false otherwise).
 *         - second: The optimal font size if found, valid only when first is true.
 */
std::pair<bool, double> TextLayoutAlgorithm::GetSuitableSize(TextStyle& textStyle, const std::u16string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint);
    auto step = Dimension(1.0, DimensionUnit::PX);

    if (GreatNotEqual(textStyle.GetAdaptFontSizeStep().Value(), 0.0)) {
        step = textStyle.GetAdaptFontSizeStep();
    }
    double stepSize = step.ConvertToPxDistribute(textStyle.GetMinFontScale(),
        textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    if (NearEqual(stepSize, 0.0)) {
        return {false, 0.0};
    }
    int32_t stepCount = (maxFontSize - minFontSize) / stepSize;

    // Compare time complexity: stepCount/2 < log(stepCount)+1, exp2 is fast.
    if (step.GetAdaptDimensionUnit(step) != DimensionUnit::PX && exp2(stepCount / 2 - 1) < stepCount) {
        return GetSuitableSizeLD(textStyle, content, contentConstraint, layoutWrapper, stepSize);
    } else {
        return GetSuitableSizeBS(textStyle, content, contentConstraint, layoutWrapper, stepSize);
    }
}

std::pair<bool, double> TextLayoutAlgorithm::GetSuitableSizeLD(TextStyle& textStyle, const std::u16string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, double stepSize)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint);
    auto maxSize = MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint);

    if (NearEqual(stepSize, 0.0)) {
        return {false, 0.0};
    }
    double suitableSize = maxFontSize;
    uint32_t suitCount = 0;
    while (GreatOrEqual(suitableSize, minFontSize)) {
        textStyle.SetFontSize(Dimension(suitableSize));
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper)) {
            return {false, 0.0};
        }
        if (!DidExceedMaxLines(maxSize)) {
            return {true, suitableSize};
        }
        if (suitCount % HUNDRED == 0) {
            auto host = layoutWrapper->GetHostNode();
            CHECK_NULL_RETURN(host, {});
            TAG_LOGI(AceLogTag::ACE_TEXT,
                "suit layout:%{public}d, [id:%{public}d, suitSize:%{public}f, minFontSize:%{public}f, "
                "stepSize:%{public}f]",
                suitCount, host->GetId(), suitableSize, minFontSize, stepSize);
        }
        suitCount++;
        suitableSize -= stepSize;
    }
    return {false, 0.0};
}

std::pair<bool, double> TextLayoutAlgorithm::GetSuitableSizeBS(TextStyle& textStyle, const std::u16string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, double stepSize)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint);
    auto maxSize = MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint);

    // Boundary check: for efficiency and to ensure the optimal size is within [minFontSize, maxFontSize].
    textStyle.SetFontSize(Dimension(maxFontSize));
    if (!CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper)) {
        TAG_LOGW(AceLogTag::ACE_TEXT, "GetSuitableSizeBS create paragraph fail");
        return {false, 0.0};
    }
    if (!DidExceedMaxLines(maxSize)) {
        return {true, maxFontSize};
    }

    if (NearEqual(stepSize, 0.0)) {
        return {false, 0.0};
    }
    int32_t stepCount = (maxFontSize - minFontSize) / stepSize;

    // Binary search: to find the optimal size within [minFontSize, maxFontSize].
    int32_t leftBound = 0;
    int32_t rightBound = stepCount;
    int32_t mid = (leftBound + rightBound) / 2;
    uint32_t suitCount = 0;
    while (leftBound < rightBound) {
        double suitSz = minFontSize + mid * stepSize;
        textStyle.SetFontSize(Dimension(suitSz));
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper)) {
            return {false, 0.0};
        }
        if (!DidExceedMaxLines(maxSize)) {
            leftBound = mid;
        } else {
            rightBound = mid - 1;
        }
        if (suitCount % TWENTY == 0) {
            auto host = layoutWrapper->GetHostNode();
            CHECK_NULL_RETURN(host, {});
            TAG_LOGI(AceLogTag::ACE_TEXT,
                "suit layout:%{public}d, [id:%{public}d, suitSz:%{public}f, stepCount:%{public}d, stepSize:%{public}f]",
                suitCount, host->GetId(), suitSz, stepCount, stepSize);
        }
        suitCount++;
        mid = (leftBound + rightBound + 1) / 2;
    }
    return {true, minFontSize + leftBound * stepSize};
}

float TextLayoutAlgorithm::GetBaselineOffset() const
{
    return baselineOffset_;
}

bool TextLayoutAlgorithm::UpdateSingleParagraph(LayoutWrapper* layoutWrapper, ParagraphStyle paraStyle,
    const TextStyle& textStyle, const std::u16string& content, double maxWidth)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    ACE_TEXT_SCOPED_TRACE("TextLayoutAlgorithm::UpdateSingleParagraph[id:%d][length:%d][w:%f]", host->GetId(),
        static_cast<int32_t>(content.length()), maxWidth);
    auto pattern = host->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto externalParagraph = pattern->GetExternalParagraph();
    RefPtr<Paragraph> paragraph;
    if (externalParagraph) {
        paragraph = Paragraph::Create(externalParagraph.value());
    } else {
        paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    }
    CHECK_NULL_RETURN(paragraph, false);
    auto textStyleTmp = textStyle;
    textStyleTmp.ResetTextBaseline();
    paragraph->PushStyle(textStyleTmp);
    if (pattern->NeedShowAIDetect()) {
        UpdateParagraphForAISpan(textStyle, layoutWrapper, paragraph);
    } else {
        if (pattern->IsDragging()) {
            auto dragContents = pattern->GetDragContents();
            CreateParagraphDrag(textStyle, dragContents, paragraph);
        } else {
            auto value = content;
            StringUtils::TransformStrCase(value, static_cast<int32_t>(textStyle.GetTextCase()));
            UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(value.data()), value.length(), 0);
            paragraph->AddText(value);
        }
    }
    paragraph->Build();
    ApplyIndent(paraStyle, paragraph, maxWidth, textStyle);
    paragraphManager_->AddParagraph({ .paragraph = paragraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = content.length() });
    return true;
}

bool TextLayoutAlgorithm::BuildParagraph(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto pattern = host->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->DumpRecord("TextLayout BuildParagraph id:" + std::to_string(host->GetId()));
    if (!textStyle.GetAdaptTextSize() || !spans_.empty()) {
        if (!CreateParagraphAndLayout(textStyle, layoutProperty->GetContent().value_or(u""), contentConstraint,
            layoutWrapper)) {
            TAG_LOGW(AceLogTag::ACE_TEXT, "BuildParagraph fail, contentConstraint:%{public}s",
                contentConstraint.ToString().c_str());
            return false;
        }
    } else {
        if (!AdaptMinTextSize(textStyle, layoutProperty->GetContent().value_or(u""), contentConstraint,
            layoutWrapper)) {
            return false;
        }
    }
    return ParagraphReLayout(contentConstraint);
}

bool TextLayoutAlgorithm::BuildParagraphAdaptUseMinFontSize(TextStyle& textStyle,
    const RefPtr<TextLayoutProperty>& layoutProperty, const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    if (!AdaptMaxTextSize(textStyle, layoutProperty->GetContent().value_or(u""), contentConstraint, layoutWrapper)) {
        return false;
    }
    auto paragraph = GetSingleParagraph();
    CHECK_NULL_RETURN(paragraph, false);
    // Confirmed specification: The width of the text paragraph covers the width of the component, so this code is
    // generally not allowed to be modified
    if (!contentConstraint.selfIdealSize.Width()) {
        float paragraphNewWidth = std::min(std::min(paragraph->GetTextWidth(), paragraph->GetMaxWidth()),
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
    auto lineCount = static_cast<uint32_t>(paragraph->GetLineCount());
    lineCount = std::max(std::min(textStyle.GetMaxLines(), lineCount), static_cast<uint32_t>(0));
    textStyle.SetMaxLines(lineCount);
    textStyle.DisableAdaptTextSize();

    auto height = static_cast<float>(paragraph->GetHeight());
    uint32_t adaptCount = 0;
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
        if (adaptCount % HUNDRED == 0) {
            auto host = layoutWrapper->GetHostNode();
            CHECK_NULL_RETURN(host, {});
            TAG_LOGI(AceLogTag::ACE_TEXT,
                "AdaptLayout:%{public}d, [id:%{public}d, height:%{public}f, constraint:%{public}s, "
                "maxlines:%{public}d]",
                adaptCount, host->GetId(), height, contentConstraint.ToString().c_str(), maxLines);
        }
        adaptCount++;
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
    std::u16string content = layoutProperty->GetContent().value_or(u"");
    std::replace(content.begin(), content.end(), u'\n', u' ');
    if (!textStyle.GetAdaptTextSize()) {
        if (!CreateParagraph(textStyle, content, layoutWrapper)) {
            return std::nullopt;
        }
    } else {
        if (!AdaptMinTextSize(textStyle, content, contentConstraint, layoutWrapper)) {
            return std::nullopt;
        }
    }

    textStyle_ = textStyle;
    auto paragraph = GetSingleParagraph();
    // layout the paragraph to the width of text
    paragraph->Layout(std::numeric_limits<float>::max());
    float paragraphWidth = paragraph->GetLongestLineWithIndent();
    if (contentConstraint.selfIdealSize.Width().has_value()) {
        paragraphWidth = std::max(contentConstraint.selfIdealSize.Width().value(), paragraphWidth);
    } else {
        paragraphWidth = std::max(contentConstraint.minSize.Width(), paragraphWidth);
    }
    paragraphWidth = std::ceil(paragraphWidth);
    paragraph->Layout(paragraphWidth);

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    // calculate the content size
    auto height = static_cast<float>(paragraph->GetHeight());
    baselineOffset_ = static_cast<float>(
        layoutProperty->GetBaselineOffsetValue(Dimension())
            .ConvertToPxDistribute(textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale()));
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

bool TextLayoutAlgorithm::AdaptMaxTextSize(TextStyle& textStyle, const std::u16string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    constexpr Dimension ADAPT_UNIT = 1.0_fp;
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, false);
    auto step = textLayoutProperty->GetAdaptFontSizeStepValue(ADAPT_UNIT);
    return AdaptMaxFontSize(textStyle, content, step, contentConstraint, layoutWrapper);
}

void TextLayoutAlgorithm::UpdateSensitiveContent(std::u16string& content)
{
    std::replace_if(
        content.begin(), content.end(),
        [](char16_t ch) {
            return ch != u'\n';
        }, u'-');
}

std::optional<TextStyle> TextLayoutAlgorithm::GetTextStyle() const
{
    return textStyle_;
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
