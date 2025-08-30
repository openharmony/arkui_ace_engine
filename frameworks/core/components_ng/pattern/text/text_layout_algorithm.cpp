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
#include "base/utils/utf_helper.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/paragraph_util.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t HUNDRED = 100;
constexpr int32_t TWENTY = 20;

uint32_t GetAdaptedMaxLines(const TextStyle& textStyle, const LayoutConstraintF& contentConstraint)
{
    double minTextSizeHeight = textStyle.GetAdaptMinFontSize().ConvertToPxDistribute(
        textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    if (LessOrEqual(minTextSizeHeight, 0.0)) {
        minTextSizeHeight = textStyle.GetFontSize().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }
    double lineHeight = minTextSizeHeight;
    if (textStyle.HasHeightOverride()) {
        lineHeight = textStyle.GetLineHeight().Unit() == DimensionUnit::PERCENT
                            ? textStyle.GetLineHeight().ConvertToPxWithSize(contentConstraint.maxSize.Height())
                            : textStyle.GetLineHeight().ConvertToPxDistribute(
                                textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }
    // plus extraLine to ensure maxlines -1 is the next maxline to try for layout
    uint32_t maxLines = contentConstraint.maxSize.Height() / (lineHeight) + 1;
    return std::max(maxLines, static_cast<uint32_t>(0));
}
}; // namespace

TextLayoutAlgorithm::TextLayoutAlgorithm(
    std::list<RefPtr<SpanItem>> spans, RefPtr<ParagraphManager> pManager, bool isSpanStringMode,
    const TextStyle& textStyle, bool isMarquee)
{
    if (SystemProperties::GetTextTraceEnabled()) {
        ACE_TEXT_SCOPED_TRACE("TextLayoutAlgorithm::TextLayoutAlgorithm[styleUid:%d][isSpanStringMode:%d][size:%d]",
            textStyle.GetTextStyleUid(), isSpanStringMode, static_cast<int32_t>(spans.size()));
    }
    paragraphManager_ = pManager;
    isSpanStringMode_ = isSpanStringMode;
    textStyle_ = textStyle;

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
    ParagraphUtil::ConstructParagraphSpanGroup(spans, spans_, spanStringHasMaxLines_);
}

TextLayoutAlgorithm::TextLayoutAlgorithm() = default;

void TextLayoutAlgorithm::OnReset() {}

std::optional<SizeF> TextLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& constraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto pattern = host->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, std::nullopt);
    auto contentConstraint = CalcContentConstraint(constraint, layoutWrapper);
    ConstructTextStyles(contentConstraint, layoutWrapper, textStyle_);
    if (isSpanStringMode_ && spanStringHasMaxLines_) {
        textStyle_.SetMaxLines(UINT32_MAX);
    }
    // inheritTextStyle_ is used to control spans_ in versions below VERSION_EIGHTEEN, preventing them from
    // adapting to font size automatically.
    inheritTextStyle_ = textStyle_;
    MeasureChildren(layoutWrapper, textStyle_);
    CheckNeedReCreateParagraph(layoutWrapper, textStyle_);
    ACE_SCOPED_TRACE("TextLayoutAlgorithm::MeasureContent[id:%d][needReCreateParagraph:%d][size:%d]", host->GetId(),
        needReCreateParagraph_, static_cast<int32_t>(spans_.size()));
    if (textStyle_.GetTextOverflow() == TextOverflow::MARQUEE) { // create a paragraph with all text in 1 line
        isMarquee_ = true;
        if (paragraphManager_) {
            auto height = paragraphManager_->GetHeight();
            auto heightFinal = static_cast<float>(height + std::fabs(baselineOffset_));
            SetContentHeight(heightFinal);
        }
        auto result = BuildTextRaceParagraph(textStyle_, textLayoutProperty, contentConstraint, layoutWrapper);
        return result;
    }
    if (isSpanStringMode_ && host->LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        BuildParagraph(textStyle_, textLayoutProperty, contentConstraint, layoutWrapper);
    } else {
        if (!AddPropertiesAndAnimations(textStyle_, textLayoutProperty, contentConstraint, layoutWrapper)) {
            return std::nullopt;
        }
    }
    UpdateRelayoutShaderStyle(layoutWrapper);
    baselineOffset_ = textStyle_.GetBaselineOffset().ConvertToPxDistribute(
        textStyle_.GetMinFontScale(), textStyle_.GetMaxFontScale(), textStyle_.IsAllowScale());
    if (NearZero(contentConstraint.maxSize.Height()) || NearZero(contentConstraint.maxSize.Width()) ||
        IsParentSizeNearZero(contentConstraint, layoutWrapper)) {
        return SizeF {};
    }
    CHECK_NULL_RETURN(paragraphManager_, std::nullopt);
#ifdef ENABLE_ROSEN_BACKEND
    auto pipeline = host->GetContext();
    auto fontManager = pipeline == nullptr ? nullptr : pipeline->GetFontManager();
    if (fontManager != nullptr && Rosen::RSUIDirector::IsHybridRenderEnabled()) {
        if (static_cast<uint32_t>(paragraphManager_->GetLineCount()) >=
            Rosen::RSUIDirector::GetHybridRenderTextBlobLenCount()) {
            fontManager->AddHybridRenderNode(host);
        } else {
            fontManager->RemoveHybridRenderNode(host);
        }
    }
#endif
    auto height = paragraphManager_->GetHeight();
    auto maxWidth = paragraphManager_->GetMaxWidth();
    auto longestLine = paragraphManager_->GetLongestLine();
    auto heightFinal = static_cast<float>(height + std::fabs(baselineOffset_));
    SetContentHeight(heightFinal);
    if (contentConstraint.selfIdealSize.Height().has_value()) {
        heightFinal = std::min(heightFinal, contentConstraint.selfIdealSize.Height().value());
    } else {
        heightFinal = std::min(heightFinal, contentConstraint.maxSize.Height());
    }
    if (host->GetTag() == V2::TEXT_ETS_TAG && textLayoutProperty->GetContent().value_or(u"").empty() &&
        NonPositive(longestLine)) {
        ACE_SCOPED_TRACE("TextHeightFinal [%f], TextContentWidth [%f], FontSize [%lf]", heightFinal, maxWidth,
            textStyle_.GetFontSize().ConvertToPxDistribute(
                textStyle_.GetMinFontScale(), textStyle_.GetMaxFontScale(), textStyle_.IsAllowScale()));
        return SizeF {};
    }
    return SizeF(maxWidth, heightFinal);
}

void TextLayoutAlgorithm::UpdateRelayoutShaderStyle(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    if (textStyle_.GetGradient().has_value() && !pattern->GetExternalParagraph()) {
        RelayoutShaderStyle(textLayoutProperty);
    }
}

void TextLayoutAlgorithm::RelayoutShaderStyle(const RefPtr<TextLayoutProperty>& layoutProperty)
{
    CHECK_NULL_VOID(paragraphManager_);
    auto paragraphs = paragraphManager_->GetParagraphs();
    if (spans_.empty()) {
        for (auto pIter = paragraphs.begin(); pIter != paragraphs.end(); pIter++) {
            auto paragraph = pIter->paragraph;
            if (!paragraph) {
                continue;
            }
            auto textStyle = textStyle_;
            textStyle.SetForeGroundBrushBitMap();
            paragraph->ReLayoutForeground(textStyle);
        }
        return;
    }
    if (!spans_.empty()) {
        size_t itemIndex = -1;
        for (auto pIter = paragraphs.begin(); pIter != paragraphs.end(); pIter++) {
            ++itemIndex;
            auto paragraph = pIter->paragraph;
            if (!paragraph) {
                continue;
            }
            if (itemIndex >= spans_.size()) {
                return;
            }
            auto spans = spans_[itemIndex];
            TextStyle textStyle;
            if (!spans.empty() && spans.front() && spans.front()->GetTextStyle() &&
                spans.front()->GetTextStyle()->GetGradient().has_value()) {
                textStyle = spans.front()->GetTextStyle().value();
            } else {
                textStyle = textStyle_;
            }
            textStyle.SetForeGroundBrushBitMap();
            paragraph->ReLayoutForeground(textStyle);
        }
    }
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

void TextLayoutAlgorithm::CheckNeedReCreateParagraph(LayoutWrapper* layoutWrapper, const TextStyle& textStyle)
{
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    alwaysReCreateParagraph_ = AlwaysReCreateParagraph(layoutWrapper);
    needReCreateParagraph_ = textLayoutProperty->GetNeedReCreateParagraphValue(false) ||
                             textStyle.NeedReCreateParagraph() || alwaysReCreateParagraph_;
}

void TextLayoutAlgorithm::ResetNeedReCreateParagraph(LayoutWrapper* layoutWrapper)
{
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->ResetNeedReCreateParagraph();
    CHECK_NULL_VOID(!alwaysReCreateParagraph_);
    needReCreateParagraph_ = false;
}

bool TextLayoutAlgorithm::AlwaysReCreateParagraph(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, false);
    return textPattern->GetExternalParagraph() || textPattern->NeedShowAIDetect() || isSpanStringMode_ ||
           textPattern->IsDragging() ||
           textLayoutProperty->GetEllipsisModeValue(EllipsisMode::TAIL) == EllipsisMode::MIDDLE ||
           textPattern->IsSensitiveEnable() ||
           textLayoutProperty->GetSymbolTypeValue(SymbolType::SYSTEM) == SymbolType::CUSTOM;
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
    auto wTextForAI = pattern->GetTextForAI();
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

void TextLayoutAlgorithm::GrayDisplayAISpan(const DragSpanPosition& dragSpanPosition, const std::u16string wTextForAI,
    const TextStyle& textStyle, bool isDragging, const RefPtr<Paragraph>& paragraph)
{
    int32_t dragStart = dragSpanPosition.dragStart;
    int32_t dragEnd = dragSpanPosition.dragEnd;
    int32_t spanStart = dragSpanPosition.spanStart;
    int32_t spanEnd = dragSpanPosition.spanEnd;
    std::vector<std::u16string> contents = {};
    std::u16string firstParagraph = u"";
    std::u16string secondParagraph = u"";
    std::u16string thirdParagraph = u"";
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

std::u16string TextLayoutAlgorithm::StringOutBoundProtection(int32_t position, int32_t length,
    std::u16string wTextForAI)
{
    int32_t wTextForAILength = static_cast<int32_t>(wTextForAI.length());
    if (position >= 0 && position < wTextForAILength && length >= 0 && length <= wTextForAILength - position) {
        return wTextForAI.substr(position, length);
    }
    return u"";
}

bool TextLayoutAlgorithm::CreateParagraph(
    const TextStyle& textStyle, std::u16string content, LayoutWrapper* layoutWrapper, double maxWidth)
{
    if (!paragraphManager_) {
        paragraphManager_ = AceType::MakeRefPtr<ParagraphManager>();
    }
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->ClearCustomSpanPlaceholderInfo();
    if (pattern->IsSensitiveEnable()) {
        UpdateSensitiveContent(content);
    }
    auto useExternalParagraph = pattern->GetExternalParagraph() && !pattern->NeedShowAIDetect();
    auto externalParagraphStyle = pattern->GetExternalParagraphStyle();
    auto paraStyle = ParagraphUtil::GetParagraphStyle(textStyle);
    if (pattern->GetExternalParagraph()) {
        if (!useExternalParagraph && externalParagraphStyle) {
            paraStyle = externalParagraphStyle.value();
        }
    }
    if (frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN) || isSpanStringMode_) {
        paraStyle.fontSize = textStyle.GetFontSize().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }
    paraStyle.leadingMarginAlign = Alignment::CENTER;
    paraStyle.textStyleUid = frameNode->GetId();
    // SymbolGlyph
    if (frameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        paragraphManager_->Reset();
        return UpdateSymbolTextStyle(textStyle, paraStyle, layoutWrapper, frameNode);
    }
    if (spans_.empty() || useExternalParagraph) {
        // only use for text.
        return UpdateSingleParagraph(layoutWrapper, paraStyle, textStyle, content, maxWidth);
    } else {
        paragraphManager_->Reset();
        return UpdateParagraphBySpan(layoutWrapper, paraStyle, maxWidth, textStyle);
    }
}

bool TextLayoutAlgorithm::UpdateSymbolTextStyle(const TextStyle& textStyle, const ParagraphStyle& paraStyle,
    LayoutWrapper* layoutWrapper, RefPtr<FrameNode>& frameNode)
{
    auto&& paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_RETURN(paragraph, false);
    auto layoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    auto symbolSourceInfo = layoutProperty->GetSymbolSourceInfo();
    CHECK_NULL_RETURN(symbolSourceInfo, false);
    auto symbolType = textStyle.GetSymbolType();
    std::vector<std::string> fontFamilies = textStyle.GetFontFamilies();
    if (symbolType == SymbolType::CUSTOM && fontFamilies.empty()) {
        return false;
    }
    paragraph->PushStyle(textStyle);
    if (textStyle.GetSymbolEffectOptions().has_value()) {
        auto symbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
        symbolEffectOptions.Reset();
        layoutProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
    }
    paragraph->AddSymbol(symbolSourceInfo->GetUnicode());
    paragraph->PopStyle();
    paragraph->Build();
    paragraph->SetParagraphSymbolAnimation(frameNode);
    paragraphManager_->AddParagraph({ .paragraph = paragraph, .paragraphStyle = paraStyle, .start = 0, .end = 2 });
    return true;
}

void TextLayoutAlgorithm::CreateParagraphDrag(
    const TextStyle& textStyle, const std::vector<std::u16string>& contents, const RefPtr<Paragraph>& paragraph)
{
    TextStyle dragTextStyle = textStyle;
    Color color = textStyle.GetTextColor().ChangeAlpha(DRAGGED_TEXT_TRANSPARENCY);
    dragTextStyle.SetTextColor(color);
    Color textDecorationColor = textStyle.GetTextDecorationColor().ChangeAlpha(DRAGGED_TEXT_TRANSPARENCY);
    dragTextStyle.SetTextDecorationColor(textDecorationColor);
    std::vector<TextStyle> textStyles { textStyle, dragTextStyle, textStyle };

    CHECK_NULL_VOID(paragraph);
    for (size_t i = 0; i < contents.size(); i++) {
        std::u16string splitStr = contents[i];
        if (splitStr.empty()) {
            continue;
        }
        auto& style = textStyles[i];
        paragraph->PushStyle(style);
        StringUtils::TransformStrCase(splitStr, static_cast<int32_t>(style.GetTextCase()));
        UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(splitStr.data()), splitStr.length(), 0);
        paragraph->AddText(splitStr);
        paragraph->PopStyle();
    }
}

bool TextLayoutAlgorithm::ReLayoutParagraphs(
    const TextStyle& textStyle, LayoutWrapper* layoutWrapper, const SizeF& maxSize)
{
    auto needReLayout = textStyle.NeedReLayout();
    ParagraphStyle parStyle;
    std::vector<TextStyle> textStyles;
    if (!spans_.empty() && !isSpanStringMode_ && !needReCreateParagraph_) {
        needReLayout |= ReLayoutParagraphBySpan(layoutWrapper, parStyle, textStyle, textStyles);
        CHECK_NULL_RETURN(!needReCreateParagraph_, false);
    } else if (!needReCreateParagraph_ && needReLayout) {
        auto tempTextStyle = textStyle;
        tempTextStyle.ResetTextBaselineOffset();
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TextLayoutAlgorithm::ReLayoutParagraphs[id:%d][textStyleBitmap:%s]",
                tempTextStyle.GetTextStyleUid(), tempTextStyle.GetReLayoutTextStyleBitmap().to_string().c_str());
        }
        textStyles.emplace_back(tempTextStyle);
        parStyle = ParagraphUtil::GetParagraphStyle(textStyle);
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            parStyle.fontSize = textStyle.GetFontSize().ConvertToPxDistribute(
                textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        }
    }
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    parStyle.textStyleUid = frameNode->GetId();
    CHECK_NULL_RETURN(paragraphManager_, false);
    auto paragraphInfo = paragraphManager_->GetParagraphs();
    for (auto pIter = paragraphInfo.begin(); pIter != paragraphInfo.end(); pIter++) {
        auto paragraph = pIter->paragraph;
        CHECK_NULL_RETURN(paragraph, false);
        if (!needReCreateParagraph_ && needReLayout) {
            paragraph->ReLayout(maxSize.Width(), parStyle, textStyles);
        } else {
            paragraph->Layout(maxSize.Width());
        }
    }
    return true;
}

bool TextLayoutAlgorithm::CreateParagraphAndLayout(TextStyle& textStyle, const std::u16string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, bool needLayout)
{
    auto maxSize = MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint);
    auto needReLayout = textStyle.NeedReLayout();
    if (SystemProperties::GetTextTraceEnabled()) {
        ACE_TEXT_SCOPED_TRACE("TextLayoutAlgorithm::CreateParagraphAndLayout[contentConstraint:%s][maxSize:%s][Len:%d]["
                              "needReCreateParagraph:%d][needReLayout:%d][fontSize:%s][fontColor:%s]",
            contentConstraint.ToString().c_str(), maxSize.ToString().c_str(), static_cast<int32_t>(content.length()),
            needReCreateParagraph_, needReLayout, textStyle.GetFontSize().ToString().c_str(),
            textStyle.GetTextColor().ColorToString().c_str());
    }
    if (needReCreateParagraph_ && !CreateParagraph(textStyle, content, layoutWrapper, maxSize.Width())) {
        return false;
    }

    if (needReCreateParagraph_) {
        CHECK_NULL_RETURN(LayoutParagraphs(maxSize.Width()), false);
    } else {
        auto frameNode = layoutWrapper->GetHostNode();
        CHECK_NULL_RETURN(frameNode, false);
        auto pattern = frameNode->GetPattern<TextPattern>();
        CHECK_NULL_RETURN(pattern, false);
        pattern->RelayoutResetOrUpdateTextEffect();
        if (!ReLayoutParagraphs(textStyle, layoutWrapper, maxSize)) {
            CHECK_NULL_RETURN(CreateParagraph(textStyle, content, layoutWrapper, maxSize.Width()), false);
            CHECK_NULL_RETURN(LayoutParagraphs(maxSize.Width()), false);
        }
    }
    // Reset the flag after each paragraph layout.
    ResetNeedReCreateParagraph(layoutWrapper);
    textStyle.ResetReCreateAndReLayoutBitmap();
    return true;
}

bool TextLayoutAlgorithm::LayoutParagraphs(float maxWidth)
{
    CHECK_NULL_RETURN(paragraphManager_, false);
    auto paragraphInfo = paragraphManager_->GetParagraphs();
    for (auto pIter = paragraphInfo.begin(); pIter != paragraphInfo.end(); pIter++) {
        auto paragraph = pIter->paragraph;
        CHECK_NULL_RETURN(paragraph, false);
        paragraph->Layout(maxWidth);
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
    if (NonPositive(contentConstraint.maxSize.Width())) {
        textStyle.SetFontSize(Dimension(minFontSize));
        return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper);
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
            TAG_LOGW(AceLogTag::ACE_TEXT,
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
    CHECK_NULL_RETURN(paragraphManager_, false);
    RefPtr<Paragraph> oldParagraph;
    auto externalParagraph = pattern->GetExternalParagraph();
    RefPtr<Paragraph> paragraph;
    if (externalParagraph) {
        paragraph = Paragraph::Create(externalParagraph.value());
    } else {
        paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
        auto paragraphs = paragraphManager_->GetParagraphs();
        if (!paragraphs.empty()) {
            oldParagraph = paragraphs.front().paragraph;
        }
    }
    paragraphManager_->Reset();
    CHECK_NULL_RETURN(paragraph, false);
    auto textStyleTmp = textStyle;
    textStyleTmp.ResetTextBaselineOffset();
    paragraph->PushStyle(textStyleTmp);
    if (pattern->NeedShowAIDetect()) {
        UpdateParagraphForAISpan(textStyle, layoutWrapper, paragraph);
    } else {
        if (pattern->IsDragging()) {
            auto dragContents = pattern->GetDragContents();
            CreateParagraphDrag(textStyleTmp, dragContents, paragraph);
        } else {
            auto value = content;
            StringUtils::TransformStrCase(value, static_cast<int32_t>(textStyle.GetTextCase()));
            UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(value.data()), value.length(), 0);
            paragraph->AddText(value);
        }
    }
    paragraph->Build();
    if (paragraph) {
        CreateOrUpdateTextEffect(oldParagraph, paragraph, pattern, content);
    }
    ParagraphUtil::ApplyIndent(paraStyle, paragraph, maxWidth, textStyle, GetIndentMaxWidth(maxWidth));
    paragraphManager_->AddParagraph({ .paragraph = paragraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = content.length() });
    return true;
}

void TextLayoutAlgorithm::CreateOrUpdateTextEffect(const RefPtr<Paragraph>& oldParagraph,
    const RefPtr<Paragraph>& newParagraph, const RefPtr<TextPattern>& textPattern, const std::u16string& content)
{
    bool needUpdateTypography = false;
    auto textEffect = textPattern->GetOrCreateTextEffect(content, needUpdateTypography);
    CHECK_NULL_VOID(textEffect);
    auto frameNode = textPattern->GetHost();
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::GetTextTraceEnabled()) {
        ACE_TEXT_SCOPED_TRACE(
            "TextLayoutAlgorithm::CreateOrUpdateTextEffect[id:%d][needUpdateTypography:%d][content:%s]",
            frameNode->GetId(), needUpdateTypography, UtfUtils::Str16DebugToStr8(content).c_str());
    }
    newParagraph->SetParagraphSymbolAnimation(frameNode);
    if (needUpdateTypography && oldParagraph) {
        std::vector<std::pair<RefPtr<Paragraph>, RefPtr<Paragraph>>> paragraphs;
        auto pair = std::make_pair(oldParagraph, newParagraph);
        paragraphs.emplace_back(pair);
        textEffect->UpdateTypography(paragraphs);
    } else if (!needUpdateTypography) {
        std::vector<RefPtr<Paragraph>> paragraphs;
        paragraphs.emplace_back(newParagraph);
        textEffect->AppendTypography(paragraphs);
    }
}

bool TextLayoutAlgorithm::BuildParagraph(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    if (!textStyle.GetAdaptTextSize() ||
        (!spans_.empty() && host->LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN))) {
        if (!CreateParagraphAndLayout(
            textStyle, layoutProperty->GetContent().value_or(u""), contentConstraint, layoutWrapper)) {
            TAG_LOGE(AceLogTag::ACE_TEXT, "create paragraph error");
            return false;
        }
    } else {
        if (!AdaptMinTextSize(
            textStyle, layoutProperty->GetContent().value_or(u""), contentConstraint, layoutWrapper)) {
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
    return ParagraphReLayout(contentConstraint);
}

bool TextLayoutAlgorithm::BuildParagraphAdaptUseLayoutConstraint(TextStyle& textStyle,
    const RefPtr<TextLayoutProperty>& layoutProperty, const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    // Create the paragraph and obtain the height.
    if (!BuildParagraph(textStyle, layoutProperty, contentConstraint, layoutWrapper)) {
        return false;
    }

    CHECK_NULL_RETURN(paragraphManager_, false);
    if (textStyle.GetMaxLines() == UINT32_MAX) {
        uint32_t maxLines = GetAdaptedMaxLines(textStyle, contentConstraint);
        textStyle.SetMaxLines(maxLines);
    }
    auto lineCount = static_cast<uint32_t>(paragraphManager_->GetLineCount());
    lineCount = std::max(std::min(textStyle.GetMaxLines(), lineCount), static_cast<uint32_t>(0));
    textStyle.SetMaxLines(lineCount);
    auto disableAdaptTextSize = textStyle.GetAdaptTextSize();
    if (disableAdaptTextSize) {
        textStyle.DisableAdaptTextSize();
    }

    auto height = static_cast<float>(paragraphManager_->GetHeight());
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
            if (disableAdaptTextSize) {
                textStyle.SetAdaptTextSize(true);
            }
            return false;
        }
        if (adaptCount % HUNDRED == 0) {
            auto host = layoutWrapper->GetHostNode();
            CHECK_NULL_RETURN(host, {});
            TAG_LOGW(AceLogTag::ACE_TEXT,
                "AdaptLayout:%{public}d, [id:%{public}d, height:%{public}f, constraint:%{public}s, "
                "maxlines:%{public}d]",
                adaptCount, host->GetId(), height, contentConstraint.ToString().c_str(), maxLines);
        }
        adaptCount++;
        height = static_cast<float>(paragraphManager_->GetHeight());
    }
    if (disableAdaptTextSize) {
        textStyle.SetAdaptTextSize(true);
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
        textStyle.ResetReCreateAndReLayoutBitmap();
    } else {
        if (!AdaptMinTextSize(textStyle, content, contentConstraint, layoutWrapper)) {
            return std::nullopt;
        }
    }
    layoutProperty->OnPropertyChangeMeasure();

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
    UpdateRelayoutShaderStyle(layoutWrapper);

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

const TextStyle& TextLayoutAlgorithm::GetTextStyle() const
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

bool TextLayoutAlgorithm::DidExceedMaxLines(const SizeF& maxSize)
{
    CHECK_NULL_RETURN(paragraphManager_, false);
    bool didExceedMaxLines = paragraphManager_->DidExceedMaxLinesInner();
    didExceedMaxLines = didExceedMaxLines || GreatNotEqual(paragraphManager_->GetHeight(), maxSize.Height());
    didExceedMaxLines =
        didExceedMaxLines || GreatNotEqual(paragraphManager_->GetLongestLineWithIndent(), maxSize.Width());
    return didExceedMaxLines;
}

bool TextLayoutAlgorithm::IsAdaptExceedLimit(const SizeF& maxSize)
{
    CHECK_NULL_RETURN(paragraphManager_, false);
    return (paragraphManager_->GetLineCount() > 1) || paragraphManager_->DidExceedMaxLinesInner() ||
           GreatNotEqual(paragraphManager_->GetLongestLineWithIndent(), maxSize.Width());
}

bool TextLayoutAlgorithm::IsParentSizeNearZero(const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto widthPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, true);
    if (widthPolicy == LayoutCalPolicy::MATCH_PARENT &&
        (contentConstraint.parentIdealSize.Width().has_value() &&
            NearZero(contentConstraint.parentIdealSize.Width().value()))) {
        return true;
    }
    auto heightPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, false);
    if (heightPolicy == LayoutCalPolicy::MATCH_PARENT &&
        (contentConstraint.parentIdealSize.Height().has_value() &&
            NearZero(contentConstraint.parentIdealSize.Height().value()))) {
        return true;
    }
    return false;
}

bool TextLayoutAlgorithm::IsFixIdealSizeAndNoMaxSize(LayoutWrapper* layoutWrapper, bool isWidth)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto layoutPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, isWidth);
    if (layoutPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_RETURN(layoutProperty, false);
        const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
        CHECK_NULL_RETURN(calcLayoutConstraint, false);
        return isWidth ? !calcLayoutConstraint->maxSize->Width().has_value()
                       : !calcLayoutConstraint->maxSize->Height().has_value();
    }
    return false;
}

LayoutConstraintF TextLayoutAlgorithm::CalcContentConstraint(
    const LayoutConstraintF& constraint, LayoutWrapper* layoutWrapper)
{
    LayoutConstraintF contentConstraint = constraint;
    CHECK_NULL_RETURN(layoutWrapper, contentConstraint);
    auto widthPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, true);
    isFixIdealSizeAndNoMaxWidth_ = IsFixIdealSizeAndNoMaxSize(layoutWrapper, true);
    if (widthPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        auto maxCalcWidth = GetCalcLayoutConstraintLength(layoutWrapper, true, true);
        if (maxCalcWidth) {
            contentConstraint.maxSize.SetWidth(maxCalcWidth.value());
        } else {
            contentConstraint.maxSize.SetWidth(std::numeric_limits<double>::infinity());
        }
    } else if (widthPolicy == LayoutCalPolicy::MATCH_PARENT && constraint.parentIdealSize.Width().has_value()) {
        contentConstraint.selfIdealSize.SetWidth(constraint.parentIdealSize.Width().value());
    }
    auto heightPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, false);
    if (heightPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        auto maxCalcHeight = GetCalcLayoutConstraintLength(layoutWrapper, true, false);
        if (maxCalcHeight) {
            contentConstraint.maxSize.SetHeight(maxCalcHeight.value());
        } else {
            contentConstraint.maxSize.SetHeight(std::numeric_limits<double>::infinity());
        }
    } else if (heightPolicy == LayoutCalPolicy::MATCH_PARENT && constraint.parentIdealSize.Height().has_value()) {
        contentConstraint.selfIdealSize.SetHeight(constraint.parentIdealSize.Height().value());
    }
    cachedCalcContentConstraint_ = contentConstraint;
    return contentConstraint;
}

bool TextLayoutAlgorithm::IsNeedParagraphReLayout() const
{
    return isFixIdealSizeAndNoMaxWidth_;
}

double TextLayoutAlgorithm::GetIndentMaxWidth(double width) const
{
    if (isFixIdealSizeAndNoMaxWidth_ && cachedCalcContentConstraint_.has_value()) {
        return cachedCalcContentConstraint_.value().maxSize.Width();
    }
    return width;
}

std::optional<float> TextLayoutAlgorithm::GetCalcLayoutConstraintLength(
    LayoutWrapper* layoutWrapper, bool isMax, bool isWidth)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    const auto& layoutCalcConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(layoutCalcConstraint, std::nullopt);
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, std::nullopt);
    auto calcLayoutConstraintMaxMinSize = isMax ? layoutCalcConstraint->maxSize : layoutCalcConstraint->minSize;
    CHECK_NULL_RETURN(calcLayoutConstraintMaxMinSize, std::nullopt);
    auto optionalCalcLength =
        isWidth ? calcLayoutConstraintMaxMinSize->Width() : calcLayoutConstraintMaxMinSize->Height();
    auto percentLength =
        isWidth ? layoutConstraint->percentReference.Width() : layoutConstraint->percentReference.Height();
    CHECK_NULL_RETURN(optionalCalcLength, std::nullopt);
    return ConvertToPx(optionalCalcLength, ScaleProperty::CreateScaleProperty(), percentLength);
}

void TextLayoutAlgorithm::MeasureWithFixAtIdealSize(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto widthPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, true);
    auto heightPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, false);
    if (widthPolicy != LayoutCalPolicy::FIX_AT_IDEAL_SIZE && heightPolicy != LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        return;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto& content = geometryNode->GetContent();
    CHECK_NULL_VOID(content);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto contentSize = content->GetRect().GetSize();
    AddPaddingToSize(padding, contentSize);
    OptionalSizeF frameSize;
    frameSize.UpdateIllegalSizeWithCheck(contentSize);
    frameSize = UpdateOptionSizeByCalcLayoutConstraint(
        frameSize, layoutProperty->GetCalcLayoutConstraint(), layoutProperty->GetLayoutConstraint()->percentReference);
    auto fixSize = frameSize.ConvertToSizeT();
    auto measureSize = geometryNode->GetFrameSize();
    if (widthPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        measureSize.SetWidth(fixSize.Width());
    }
    if (heightPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        measureSize.SetHeight(fixSize.Height());
    }
    geometryNode->SetFrameSize(measureSize);
}

void TextLayoutAlgorithm::MeasureWidthLayoutCalPolicy(LayoutWrapper* layoutWrapper)
{
    MeasureWithFixAtIdealSize(layoutWrapper);
}
} // namespace OHOS::Ace::NG
