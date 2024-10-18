/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/multiple_paragraph_layout_algorithm.h"

#include "text_layout_adapter.h"
#include "base/geometry/dimension.h"
#include "base/log/ace_performance_monitor.h"
#include "base/i18n/localization.h"
#include "core/common/font_manager.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/font_collection.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SYMBOL_SPAN_LENGTH = 2;
float GetContentOffsetY(LayoutWrapper* layoutWrapper)
{
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto offsetY = padding.top.value_or(0);
    auto align = Alignment::CENTER;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        offsetY += Alignment::GetAlignPosition(size, content->GetRect().GetSize(), align).GetY();
    }
    return offsetY;
}
} // namespace

void MultipleParagraphLayoutAlgorithm::ConstructTextStyles(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, TextStyle& textStyle)
{
    if (Negative(contentConstraint.maxSize.Width()) || Negative(contentConstraint.maxSize.Height())) {
        return;
    }

    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    auto contentModifier = pattern->GetContentModifier();

    textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    auto fontManager = pipeline->GetFontManager();
    if (fontManager && !(fontManager->GetAppCustomFont().empty()) &&
        !(textLayoutProperty->GetFontFamily().has_value())) {
        textStyle.SetFontFamilies(Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont()));
    }
    if (contentModifier) {
        if (textLayoutProperty->GetIsAnimationNeededValue(true)) {
            SetPropertyToModifier(textLayoutProperty, contentModifier, textStyle);
            contentModifier->ModifyTextStyle(textStyle);
        }
        contentModifier->SetFontReady(false);
    }
    textStyle.SetHalfLeading(textLayoutProperty->GetHalfLeadingValue(pipeline->GetHalfLeading()));
    SetAdaptFontSizeStepToTextStyle(textStyle, textLayoutProperty->GetAdaptFontSizeStep());
    // Register callback for fonts.
    FontRegisterCallback(frameNode, textStyle);

    // Determines whether a foreground color is set or inherited.
    UpdateTextColorIfForeground(frameNode, textStyle);
    textStyle_ = textStyle;
}

void MultipleParagraphLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // child constraint has already been calculated by the UpdateParagraphBySpan method when triggering MeasureContent
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
    auto baselineDistance = 0.0f;
    auto paragraph = GetSingleParagraph();
    if (paragraph) {
        baselineDistance = paragraph->GetAlphabeticBaseline() + std::max(GetBaselineOffset(), 0.0f);
    }
    if (!NearZero(baselineDistance, 0.0f)) {
        baselineDistance += GetContentOffsetY(layoutWrapper);
    }
    layoutWrapper->GetGeometryNode()->SetBaselineDistance(baselineDistance);
}

void MultipleParagraphLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto contentOffset = GetContentOffset(layoutWrapper);
    CHECK_NULL_VOID(paragraphManager_);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    std::vector<int32_t> placeholderIndex;
    GetChildrenPlaceholderIndex(placeholderIndex);
    auto rectsForPlaceholders = paragraphManager_->GetPlaceholderRects();
    if (spans_.empty() || placeholderIndex.empty()) {
        pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, contentOffset);
        return;
    }
    size_t index = 0;
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    // children only contains the image span.
    for (const auto& child : children) {
        if (!child) {
            ++index;
            continue;
        }
        if (index >= placeholderIndex.size() || index < 0) {
            child->SetActive(false);
            continue;
        }
        auto indexTemp = placeholderIndex.at(index);
        if (indexTemp >= static_cast<int32_t>(rectsForPlaceholders.size()) || indexTemp < 0) {
            child->SetActive(false);
            continue;
        }
        child->SetActive(true);
        auto rect = rectsForPlaceholders.at(indexTemp) - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
        auto geometryNode = child->GetGeometryNode();
        if (!geometryNode) {
            ++index;
            continue;
        }
        geometryNode->SetMarginFrameOffset(contentOffset + OffsetF(rect.Left(), rect.Top()));
        child->Layout();
        ++index;
    }
    pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, contentOffset);
}

void MultipleParagraphLayoutAlgorithm::GetChildrenPlaceholderIndex(std::vector<int32_t>& placeholderIndex)
{
    for (auto&& group : spans_) {
        for (const auto& child : group) {
            if (!child) {
                continue;
            }
            if (AceType::InstanceOf<CustomSpanItem>(child)) {
                continue;
            }
            if (AceType::InstanceOf<ImageSpanItem>(child) || AceType::InstanceOf<PlaceholderSpanItem>(child)) {
                placeholderIndex.emplace_back(child->placeholderIndex);
            }
        }
    }
}

void MultipleParagraphLayoutAlgorithm::GetSpanParagraphStyle(
    LayoutWrapper* layoutWrapper, const RefPtr<SpanItem>& spanItem, ParagraphStyle& pStyle)
{
    const auto& lineStyle = spanItem->textLineStyle;
    CHECK_NULL_VOID(lineStyle);
    if (lineStyle->HasTextAlign()) {
        pStyle.align = lineStyle->GetTextAlignValue();
    }
    if (lineStyle->HasMaxLines()) {
        pStyle.maxLines = lineStyle->GetMaxLinesValue();
    }
    if (lineStyle->HasWordBreak()) {
        pStyle.wordBreak = lineStyle->GetWordBreakValue();
    }
    if (lineStyle->HasEllipsisMode()) {
        pStyle.ellipsisMode = lineStyle->GetEllipsisModeValue();
    }
    if (lineStyle->HasTextOverflow()) {
        pStyle.textOverflow = lineStyle->GetTextOverflowValue();
    }
    if (lineStyle->HasTextIndent()) {
        pStyle.indent = lineStyle->GetTextIndentValue();
    }
    if (lineStyle->HasLineBreakStrategy()) {
        pStyle.lineBreakStrategy = lineStyle->GetLineBreakStrategyValue();
    }
    if (lineStyle->HasLeadingMargin()) {
        pStyle.leadingMargin = lineStyle->GetLeadingMarginValue();
    }
    if (lineStyle->HasLineHeight()) {
        pStyle.lineHeight = lineStyle->GetLineHeightValue();
    }
    if (layoutWrapper) {
        pStyle.direction = GetTextDirection(spanItem->content, layoutWrapper);
    } else {
        pStyle.direction = GetTextDirectionByContent(spanItem->content);
    }
}

void MultipleParagraphLayoutAlgorithm::FontRegisterCallback(
    const RefPtr<FrameNode>& frameNode, const TextStyle& textStyle)
{
    auto callback = [weakNode = WeakPtr<FrameNode>(frameNode)] {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        auto pattern = frameNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(pattern);
        auto modifier = DynamicCast<TextContentModifier>(pattern->GetContentModifier());
        CHECK_NULL_VOID(modifier);
        modifier->SetFontReady(true);
    };
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        bool isCustomFont = false;
        for (const auto& familyName : textStyle.GetFontFamilies()) {
            bool customFont = fontManager->RegisterCallbackNG(frameNode, familyName, callback);
            if (customFont) {
                isCustomFont = true;
            }
        }
        if (isCustomFont || fontManager->IsDefaultFontChanged()) {
            auto pattern = frameNode->GetPattern<TextPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetIsCustomFont(true);
            auto modifier = DynamicCast<TextContentModifier>(pattern->GetContentModifier());
            CHECK_NULL_VOID(modifier);
            modifier->SetIsCustomFont(true);
        }
    }
}

void MultipleParagraphLayoutAlgorithm::UpdateTextColorIfForeground(
    const RefPtr<FrameNode>& frameNode, TextStyle& textStyle)
{
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext && renderContext->HasForegroundColorStrategy()) {
        textStyle.SetTextColor(Color::FOREGROUND);
    }
}

void MultipleParagraphLayoutAlgorithm::SetFontSizePropertyToModifier(const RefPtr<TextLayoutProperty>& layoutProperty,
    const RefPtr<TextContentModifier>& modifier, const TextStyle& textStyle)
{
    auto fontSize = layoutProperty->GetFontSize();
    if (fontSize.has_value()) {
        modifier->SetFontSize(fontSize.value(), textStyle);
    } else {
        // Reset modifier FontSize.
        modifier->SetFontSize(textStyle.GetFontSize(), textStyle, true);
    }
    auto adaptMinFontSize = layoutProperty->GetAdaptMinFontSize();
    if (adaptMinFontSize.has_value()) {
        modifier->SetAdaptMinFontSize(adaptMinFontSize.value(), textStyle);
    } else {
        // Reset modifier MinFontSize.
        modifier->SetAdaptMinFontSize(textStyle.GetAdaptMinFontSize(), textStyle, true);
    }
    auto adaptMaxFontSize = layoutProperty->GetAdaptMaxFontSize();
    if (adaptMaxFontSize.has_value()) {
        modifier->SetAdaptMaxFontSize(adaptMaxFontSize.value(), textStyle);
    } else {
        // Reset modifier MaxFontSize.
        modifier->SetAdaptMaxFontSize(textStyle.GetAdaptMaxFontSize(), textStyle, true);
    }
}

void MultipleParagraphLayoutAlgorithm::SetDecorationPropertyToModifier(const RefPtr<TextLayoutProperty>& layoutProperty,
    const RefPtr<TextContentModifier>& modifier, const TextStyle& textStyle)
{
    auto textDecorationColor = layoutProperty->GetTextDecorationColor();
    if (textDecorationColor.has_value()) {
        modifier->SetTextDecorationColor(textDecorationColor.value());
    } else {
        modifier->SetTextDecorationColor(textStyle.GetTextDecorationColor(), true);
    }
    auto textDecorationStyle = layoutProperty->GetTextDecorationStyle();
    if (textDecorationStyle.has_value()) {
        modifier->SetTextDecorationStyle(textDecorationStyle.value());
    } else {
        modifier->SetTextDecorationStyle(textStyle.GetTextDecorationStyle(), true);
    }
    auto textDecoration = layoutProperty->GetTextDecoration();
    if (textDecoration.has_value()) {
        modifier->SetTextDecoration(textDecoration.value());
    } else {
        modifier->SetTextDecoration(textStyle.GetTextDecoration(), true);
    }
}

void MultipleParagraphLayoutAlgorithm::SetPropertyToModifier(const RefPtr<TextLayoutProperty>& layoutProperty,
    const RefPtr<TextContentModifier>& modifier, const TextStyle& textStyle)
{
    SetFontSizePropertyToModifier(layoutProperty, modifier, textStyle);
    auto fontFamily = layoutProperty->GetFontFamily();
    if (fontFamily.has_value()) {
        modifier->SetFontFamilies(fontFamily.value());
    }
    auto fontWeight = layoutProperty->GetFontWeight();
    if (fontWeight.has_value()) {
        modifier->SetFontWeight(fontWeight.value());
    } else {
        modifier->SetFontWeight(textStyle.GetFontWeight(), true);
    }
    auto textColor = layoutProperty->GetTextColor();
    if (textColor.has_value()) {
        modifier->SetTextColor(textColor.value());
    } else {
        modifier->SetTextColor(textStyle.GetTextColor(), true);
    }
    auto textShadow = layoutProperty->GetTextShadow();
    if (textShadow.has_value()) {
        modifier->SetTextShadow(textShadow.value());
    } else {
        modifier->SetTextShadow(textStyle.GetTextShadows());
    }
    SetDecorationPropertyToModifier(layoutProperty, modifier, textStyle);
    auto baselineOffset = layoutProperty->GetBaselineOffset();
    if (baselineOffset.has_value()) {
        modifier->SetBaselineOffset(baselineOffset.value(), textStyle);
    } else {
        modifier->SetBaselineOffset(textStyle.GetBaselineOffset(), textStyle, true);
    }
}

RefPtr<Paragraph> MultipleParagraphLayoutAlgorithm::GetSingleParagraph() const
{
    CHECK_NULL_RETURN(paragraphManager_, nullptr);
    CHECK_NULL_RETURN(!paragraphManager_->GetParagraphs().empty(), nullptr);
    auto paragraphInfo = paragraphManager_->GetParagraphs().front();
    auto paragraph = paragraphInfo.paragraph;
    CHECK_NULL_RETURN(paragraph, nullptr);
    return paragraph;
}

OffsetF MultipleParagraphLayoutAlgorithm::SetContentOffset(LayoutWrapper* layoutWrapper)
{
    OffsetF contentOffset(0.0f, 0.0f);
    CHECK_NULL_RETURN(layoutWrapper, contentOffset);

    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }

    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        contentOffset = Alignment::GetAlignPosition(size, content->GetRect().GetSize(), align) + paddingOffset;
        content->SetOffset(contentOffset);
    }
    return contentOffset;
}

void MultipleParagraphLayoutAlgorithm::SetAdaptFontSizeStepToTextStyle(
    TextStyle& textStyle, const std::optional<Dimension>& adaptFontSizeStep)
{
    textStyle.SetAdaptFontSizeStep(adaptFontSizeStep.value_or(Dimension(1.0, DimensionUnit::PX)));
}

ParagraphStyle MultipleParagraphLayoutAlgorithm::GetParagraphStyle(
    const TextStyle& textStyle, const std::string& content, LayoutWrapper* layoutWrapper) const
{
    return { .direction = GetTextDirection(content, layoutWrapper),
        .align = textStyle.GetTextAlign(),
        .maxLines = static_cast<int32_t>(textStyle.GetMaxLines()) < 0 ? UINT32_MAX : textStyle.GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = textStyle.GetWordBreak(),
        .ellipsisMode = textStyle.GetEllipsisMode(),
        .lineBreakStrategy = textStyle.GetLineBreakStrategy(),
        .textOverflow = textStyle.GetTextOverflow(),
        .indent = textStyle.GetTextIndent()
        };
}

TextDirection MultipleParagraphLayoutAlgorithm::GetTextDirection(
    const std::string& content, LayoutWrapper* layoutWrapper)
{
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, TextDirection::LTR);

    auto direction = textLayoutProperty->GetLayoutDirection();
    if (direction == TextDirection::LTR || direction == TextDirection::RTL) {
        return direction;
    }

    return GetTextDirectionByContent(content);
}

TextDirection MultipleParagraphLayoutAlgorithm::GetTextDirectionByContent(const std::string& content)
{
    bool isRTL = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto textDirection = isRTL ? TextDirection::RTL : TextDirection::LTR;
    auto showingTextForWString = StringUtils::ToWstring(content);
    for (const auto& charOfShowingText : showingTextForWString) {
        if (TextLayoutadapter::IsLeftToRight(charOfShowingText)) {
            return TextDirection::LTR;
        } else if (TextLayoutadapter::IsRightToLeft(charOfShowingText)) {
            return TextDirection::RTL;
        } else if (TextLayoutadapter::IsRightTOLeftArabic(charOfShowingText)) {
            return TextDirection::RTL;
        }
    }
    return textDirection;
}

bool MultipleParagraphLayoutAlgorithm::ParagraphReLayout(const LayoutConstraintF& contentConstraint)
{
    ACE_TEXT_SCOPED_TRACE("ParagraphReLayout");
    // Confirmed specification: The width of the text paragraph covers the width of the component, so this code is
    // generally not allowed to be modified
    CHECK_NULL_RETURN(paragraphManager_, false);
    auto paragraphs = paragraphManager_->GetParagraphs();
    float paragraphNewWidth =
        std::min(std::min(paragraphManager_->GetTextWidthIncludeIndent(), paragraphManager_->GetMaxWidth()),
            GetMaxMeasureSize(contentConstraint).Width());
    paragraphNewWidth =
        std::clamp(paragraphNewWidth, contentConstraint.minSize.Width(), contentConstraint.maxSize.Width());
    if (!contentConstraint.selfIdealSize.Width()) {
        for (auto pIter = paragraphs.begin(); pIter != paragraphs.end(); pIter++) {
            auto paragraph = pIter->paragraph;
            CHECK_NULL_RETURN(paragraph, false);
            if (!NearEqual(paragraphNewWidth, paragraph->GetMaxWidth())) {
                OTHER_DURATION();
                paragraph->Layout(std::ceil(paragraphNewWidth));
            }
        }
    }
    return true;
}

bool MultipleParagraphLayoutAlgorithm::UpdateParagraphBySpan(LayoutWrapper* layoutWrapper,
    ParagraphStyle paraStyle, double maxWidth, const TextStyle& textStyle)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    const auto& layoutConstrain = layoutProperty->CreateChildConstraint();
    auto placeHolderLayoutConstrain = layoutConstrain;
    placeHolderLayoutConstrain.maxSize.SetHeight(Infinity<float>());
    placeHolderLayoutConstrain.percentReference.SetHeight(0);
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    auto iterItems = children.begin();
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto aiSpanMap = pattern->GetAISpanMap();
    int32_t spanTextLength = 0;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholderInfo;
    int32_t paragraphIndex = -1;
    preParagraphsPlaceholderCount_ = 0;
    currentParagraphPlaceholderCount_ = 0;
    paragraphFontSize_ = paraStyle.fontSize;
    auto maxLines = static_cast<int32_t>(paraStyle.maxLines);
    for (auto&& group : spans_) {
        ParagraphStyle spanParagraphStyle = paraStyle;
        RefPtr<SpanItem> paraStyleSpanItem = GetParagraphStyleSpanItem(group);
        if (paraStyleSpanItem) {
            GetSpanParagraphStyle(layoutWrapper, paraStyleSpanItem, spanParagraphStyle);
            if (paraStyleSpanItem->fontStyle->HasFontSize()) {
                spanParagraphStyle.fontSize = paraStyleSpanItem->fontStyle->GetFontSizeValue().ConvertToPxDistribute(
                    textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
            }
        }
        if (paraStyle.maxLines != UINT32_MAX && !spanStringHasMaxLines_ && isSpanStringMode_) {
            if (!paragraphManager_->GetParagraphs().empty()) {
                maxLines -= static_cast<int32_t>(paragraphManager_->GetParagraphs().back().paragraph->GetLineCount());
            }
            spanParagraphStyle.maxLines = std::max(maxLines, 0);
        }
        auto&& paragraph = Paragraph::Create(spanParagraphStyle, FontCollection::Current());
        CHECK_NULL_RETURN(paragraph, false);
        auto paraStart = spanTextLength;
        paragraphIndex++;
        for (const auto& child : group) {
            if (!child) {
                continue;
            }
            child->paragraphIndex = paragraphIndex;
            child->SetTextPattern(pattern);
            switch (child->spanItemType) {
                case SpanItemType::NORMAL:
                    child->aiSpanMap = aiSpanMap;
                    AddTextSpanToParagraph(child, spanTextLength, frameNode, paragraph);
                    aiSpanMap = child->aiSpanMap;
                    break;
                case SpanItemType::IMAGE: {
                    if (iterItems == children.end() || !(*iterItems)) {
                        continue;
                    }
                    auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(child);
                    if (!imageSpanItem) {
                        continue;
                    }
                    AddImageToParagraph(
                        imageSpanItem, (*iterItems), layoutConstrain, paragraph, spanTextLength, textStyle);
                    auto imageNode = (*iterItems)->GetHostNode();
                    imageNodeList.emplace_back(WeakClaim(RawPtr(imageNode)));
                    iterItems++;
                    break;
                }
                case SpanItemType::CustomSpan: {
                    auto customSpanItem = AceType::DynamicCast<CustomSpanItem>(child);
                    if (!customSpanItem) {
                        continue;
                    }
                    CustomSpanPlaceholderInfo customSpanPlaceholder;
                    customSpanPlaceholder.paragraphIndex = paragraphIndex;
                    UpdateParagraphByCustomSpan(
                        customSpanItem, layoutWrapper, paragraph, spanTextLength, customSpanPlaceholder);
                    customSpanPlaceholderInfo.emplace_back(customSpanPlaceholder);
                    break;
                }
                case SpanItemType::PLACEHOLDER: {
                    if (iterItems == children.end() || !(*iterItems)) {
                        continue;
                    }
                    auto placeholderSpanItem = AceType::DynamicCast<PlaceholderSpanItem>(child);
                    if (!placeholderSpanItem) {
                        continue;
                    }
                    AddPlaceHolderToParagraph(
                        placeholderSpanItem, (*iterItems), placeHolderLayoutConstrain, paragraph, spanTextLength);
                    iterItems++;
                    break;
                }
                case SpanItemType::SYMBOL:
                    AddSymbolSpanToParagraph(child, spanTextLength, frameNode, paragraph);
            }
        }
        preParagraphsPlaceholderCount_ += currentParagraphPlaceholderCount_;
        currentParagraphPlaceholderCount_ = 0;
        shadowOffset_ += GetShadowOffset(group);
        HandleEmptyParagraph(paragraph, group);
        paragraph->Build();
        ApplyIndent(spanParagraphStyle, paragraph, maxWidth, textStyle);
        UpdateSymbolSpanEffect(frameNode, paragraph, group);
        if (paraStyle.maxLines != UINT32_MAX && !spanStringHasMaxLines_ && isSpanStringMode_) {
            paragraph->Layout(static_cast<float>(maxWidth));
        }
        paragraphManager_->AddParagraph({ .paragraph = paragraph,
            .paragraphStyle = spanParagraphStyle,
            .start = paraStart,
            .end = spanTextLength });
    }
    pattern->SetImageSpanNodeList(imageNodeList);
    pattern->InitCustomSpanPlaceholderInfo(customSpanPlaceholderInfo);
    return true;
}

TextStyle MultipleParagraphLayoutAlgorithm::InheritParentTextStyle()
{
    TextStyle textStyle = textStyle_.value_or(TextStyle());
    textStyle.ResetTextBaseline();
    return textStyle;
}

void MultipleParagraphLayoutAlgorithm::AddSymbolSpanToParagraph(const RefPtr<SpanItem>& child, int32_t& spanTextLength,
    const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph)
{
    child->SetIsParentText(frameNode->GetTag() == V2::TEXT_ETS_TAG);
    child->UpdateSymbolSpanParagraph(frameNode, InheritParentTextStyle(), paragraph);
    spanTextLength += SYMBOL_SPAN_LENGTH;
    child->length = SYMBOL_SPAN_LENGTH;
    child->position = spanTextLength;
    child->content = "  ";
}

void MultipleParagraphLayoutAlgorithm::AddTextSpanToParagraph(const RefPtr<SpanItem>& child, int32_t& spanTextLength,
    const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph)
{
    child->length = StringUtils::ToWstring(child->content).length();
    spanTextLength += static_cast<int32_t>(child->length);
    child->position = spanTextLength;
    child->UpdateParagraph(frameNode, paragraph, InheritParentTextStyle(), PlaceholderStyle(), isMarquee_);
}

void MultipleParagraphLayoutAlgorithm::AddImageToParagraph(RefPtr<ImageSpanItem>& imageSpanItem,
    const RefPtr<LayoutWrapper>& layoutWrapper, const LayoutConstraintF& layoutConstrain,
    const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength, const TextStyle& textStyle)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto id = frameNode->GetId();
    int32_t targetId = imageSpanItem->imageNodeId;
    if (!isSpanStringMode_) {
        CHECK_NULL_VOID(id == targetId);
    }
    layoutWrapper->Measure(layoutConstrain);
    PlaceholderStyle placeholderStyle;
    auto baselineOffset = Dimension(0.0f);
    auto imageLayoutProperty = DynamicCast<ImageLayoutProperty>(layoutWrapper->GetLayoutProperty());
    if (imageLayoutProperty) {
        placeholderStyle.verticalAlign = imageLayoutProperty->GetVerticalAlign().value_or(VerticalAlign::BOTTOM);
        baselineOffset = imageLayoutProperty->GetBaselineOffset().value_or(Dimension(0.0f));
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    placeholderStyle.width = geometryNode->GetMarginFrameSize().Width();
    placeholderStyle.height = geometryNode->GetMarginFrameSize().Height();
    placeholderStyle.paragraphFontSize = Dimension(paragraphFontSize_);
    if (NearZero(baselineOffset.Value())) {
        imageSpanItem->placeholderIndex =
            imageSpanItem->UpdateParagraph(frameNode, paragraph, InheritParentTextStyle(), placeholderStyle);
    } else {
        placeholderStyle.baselineOffset = baselineOffset.ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        imageSpanItem->placeholderIndex =
            imageSpanItem->UpdateParagraph(frameNode, paragraph, InheritParentTextStyle(), placeholderStyle);
    }
    currentParagraphPlaceholderCount_++;
    imageSpanItem->placeholderIndex += preParagraphsPlaceholderCount_;
    imageSpanItem->content = " ";
    spanTextLength += 1;
    imageSpanItem->position = spanTextLength;
    imageSpanItem->length = 1;
}

void MultipleParagraphLayoutAlgorithm::AddPlaceHolderToParagraph(RefPtr<PlaceholderSpanItem>& placeholderSpanItem,
    const RefPtr<LayoutWrapper>& layoutWrapper, const LayoutConstraintF& layoutConstrain,
    const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto id = frameNode->GetId();
    int32_t targetId = placeholderSpanItem->placeholderSpanNodeId;
    CHECK_NULL_VOID(id == targetId);
    // find the Corresponding ImageNode for every ImageSpanItem
    layoutWrapper->Measure(layoutConstrain);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    PlaceholderStyle placeholderStyle;
    placeholderStyle.width = geometryNode->GetMarginFrameSize().Width();
    placeholderStyle.height = geometryNode->GetMarginFrameSize().Height();
    placeholderStyle.verticalAlign = VerticalAlign::NONE;
    placeholderSpanItem->placeholderIndex =
        placeholderSpanItem->UpdateParagraph(frameNode, paragraph, InheritParentTextStyle(), placeholderStyle);
    currentParagraphPlaceholderCount_++;
    placeholderSpanItem->placeholderIndex += preParagraphsPlaceholderCount_;
    placeholderSpanItem->content = " ";
    spanTextLength += 1;
    placeholderSpanItem->length = 1;
    placeholderSpanItem->position = spanTextLength;
}

void MultipleParagraphLayoutAlgorithm::UpdateParagraphByCustomSpan(RefPtr<CustomSpanItem>& customSpanItem,
    LayoutWrapper* layoutWrapper, const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength,
    CustomSpanPlaceholderInfo& customSpanPlaceholder)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    auto fontSize = theme->GetTextStyle().GetFontSize().ConvertToVp() * context->GetFontScale();
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutProperty);
    auto fontSizeOpt = textLayoutProperty->GetFontSize();
    if (fontSizeOpt.has_value()) {
        fontSize = fontSizeOpt.value().ConvertToVp() * context->GetFontScale();
    }
    auto width = 0.0f;
    auto height = 0.0f;
    if (customSpanItem->onMeasure.has_value()) {
        auto onMeasure = customSpanItem->onMeasure.value();
        CustomSpanMetrics customSpanMetrics = onMeasure({ fontSize });
        width = static_cast<float>(customSpanMetrics.width * context->GetDipScale());
        height = static_cast<float>(
            customSpanMetrics.height.value_or(fontSize / context->GetFontScale()) * context->GetDipScale());
    }
    PlaceholderStyle placeholderStyle;
    placeholderStyle.width = width;
    placeholderStyle.height = height;
    placeholderStyle.verticalAlign = VerticalAlign::NONE;
    customSpanItem->placeholderIndex =
        customSpanItem->UpdateParagraph(nullptr, paragraph, InheritParentTextStyle(), placeholderStyle);
    currentParagraphPlaceholderCount_++;
    customSpanItem->placeholderIndex += preParagraphsPlaceholderCount_;
    customSpanItem->content = " ";
    spanTextLength += 1;
    customSpanItem->length = 1;
    customSpanItem->position = spanTextLength;
    if (customSpanItem->onDraw.has_value()) {
        customSpanPlaceholder.onDraw = customSpanItem->onDraw.value();
    }
    customSpanPlaceholder.customSpanIndex = customSpanItem->placeholderIndex;
}

void MultipleParagraphLayoutAlgorithm::ApplyIndent(
    ParagraphStyle& paragraphStyle, const RefPtr<Paragraph>& paragraph, double width, const TextStyle& textStyle)
{
    auto indentValue = paragraphStyle.indent;
    CHECK_NULL_VOID(paragraph);
    double value = 0.0;
    if (GreatNotEqual(indentValue.Value(), 0.0)) {
        // first line indent
        auto pipeline = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(pipeline);
        if (indentValue.Unit() != DimensionUnit::PERCENT) {
            value = indentValue.ConvertToPxDistribute(
                textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        } else {
            value = static_cast<float>(width * indentValue.Value());
            paragraphStyle.indent = Dimension(value);
        }
    }
    auto indent = static_cast<float>(value);
    auto leadingMarginValue = 0.0f;
    std::vector<float> indents;
    if (paragraphStyle.leadingMargin.has_value()) {
        leadingMarginValue = paragraphStyle.leadingMargin->size.Width().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }
    indents.emplace_back(indent + leadingMarginValue);
    indents.emplace_back(leadingMarginValue);
    indent_ = std::max(indent_, indent);
    paragraph->SetIndents(indents);
}

void MultipleParagraphLayoutAlgorithm::UpdateSymbolSpanEffect(
    RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph, const std::list<RefPtr<SpanItem>>& spans)
{
    for (const auto& child : spans) {
        if (!child || child->unicode == 0) {
            continue;
        }
        if (child->GetTextStyle()->isSymbolGlyph_) {
            paragraph->SetParagraphSymbolAnimation(frameNode);
            return;
        }
    }
}

SizeF MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(const LayoutConstraintF& contentConstraint)
{
    auto maxSize = contentConstraint.selfIdealSize;
    maxSize.UpdateIllegalSizeWithCheck(contentConstraint.maxSize);
    return maxSize.ConvertToSizeT();
}
} // namespace OHOS::Ace::NG
