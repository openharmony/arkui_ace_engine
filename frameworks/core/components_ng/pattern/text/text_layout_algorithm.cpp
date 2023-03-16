/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "text_layout_adapter.h"

#include "base/geometry/dimension.h"
#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/font_collection.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
/**
 * The baseline information needs to be calculated based on contentOffsetY.
 */
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

TextLayoutAlgorithm::TextLayoutAlgorithm() = default;

void TextLayoutAlgorithm::OnReset() {}

std::optional<SizeF> TextLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, std::nullopt);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto contentModifier = pattern->GetContentModifier();

    if (!contentConstraint.maxSize.IsPositive()) {
        return std::nullopt;
    }

    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    if (contentModifier) {
        SetPropertyToModifier(textLayoutProperty, contentModifier);
        contentModifier->ModifyTextStyle(textStyle);
    }

    // Determines whether a foreground color is set or inherited.
    UpdateTextColorIfForeground(frameNode, textStyle);

    if (textStyle.GetTextOverflow() == TextOverflow::MARQUEE) {
        return BuildTextRaceParagraph(textStyle, textLayoutProperty, contentConstraint, pipeline);
    }

    bool result = false;
    switch (textLayoutProperty->GetHeightAdaptivePolicyValue(TextHeightAdaptivePolicy::MAX_LINES_FIRST)) {
        case TextHeightAdaptivePolicy::MAX_LINES_FIRST:
            result = BuildParagraph(textStyle, textLayoutProperty, contentConstraint, pipeline);
            break;
        case TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST:
            result = BuildParagraphAdaptUseMinFontSize(textStyle, textLayoutProperty, contentConstraint, pipeline);
            break;
        case TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST:
            result = BuildParagraphAdaptUseLayoutConstraint(textStyle, textLayoutProperty, contentConstraint, pipeline);
            break;
        default:
            break;
    }
    if (result == false) {
        return std::nullopt;
    }
    textStyle_ = textStyle;

    auto height = static_cast<float>(paragraph_->GetHeight());
    double baselineOffset = 0.0;
    textStyle.GetBaselineOffset().NormalizeToPx(
        pipeline->GetDipScale(), pipeline->GetFontScale(), pipeline->GetLogicScale(), height, baselineOffset);

    baselineOffset_ = static_cast<float>(baselineOffset);

    float heightFinal =
        std::min(static_cast<float>(height + std::fabs(baselineOffset)), contentConstraint.maxSize.Height());

    return SizeF(paragraph_->GetMaxWidth(), heightFinal);
}

void TextLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::Measure(layoutWrapper);
    auto baselineDistance = 0.0f;
    if (paragraph_) {
        baselineDistance = paragraph_->GetAlphabeticBaseline() + std::max(GetBaselineOffset(), 0.0f);
    }
    if (!NearZero(baselineDistance, 0.0f)) {
        baselineDistance += GetContentOffsetY(layoutWrapper);
    }
    layoutWrapper->GetGeometryNode()->SetBaselineDistance(baselineDistance);
}

bool TextLayoutAlgorithm::CreateParagraph(const TextStyle& textStyle, std::string content)
{
    ParagraphStyle paraStyle = { .direction = GetTextDirection(content),
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    paragraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_RETURN(paragraph_, false);
    paragraph_->PushStyle(textStyle);

    if (spanItemChildren_.empty()) {
        StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
        paragraph_->AddText(StringUtils::Str8ToStr16(content));
    } else {
        int32_t spanTextLength = 0;
        for (const auto& child : spanItemChildren_) {
            if (child) {
                child->UpdateParagraph(paragraph_);
                child->positon = spanTextLength + StringUtils::ToWstring(child->content).length();
                spanTextLength += StringUtils::ToWstring(child->content).length();
            }
        }
    }
    paragraph_->Build();
    return true;
}

bool TextLayoutAlgorithm::CreateParagraphAndLayout(
    const TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint)
{
    if (!CreateParagraph(textStyle, content)) {
        return false;
    }
    CHECK_NULL_RETURN(paragraph_, false);
    auto maxSize = GetMaxMeasureSize(contentConstraint);
    paragraph_->Layout(maxSize.Width());
    return true;
}

bool TextLayoutAlgorithm::AdaptMinTextSize(TextStyle& textStyle, const std::string& content,
    const LayoutConstraintF& contentConstraint, const RefPtr<PipelineContext>& pipeline)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    if (!textStyle.GetAdaptMaxFontSize().NormalizeToPx(pipeline->GetDipScale(), pipeline->GetFontScale(),
            pipeline->GetLogicScale(), contentConstraint.maxSize.Height(), maxFontSize)) {
        return false;
    }
    if (!textStyle.GetAdaptMinFontSize().NormalizeToPx(pipeline->GetDipScale(), pipeline->GetFontScale(),
            pipeline->GetLogicScale(), contentConstraint.maxSize.Height(), minFontSize)) {
        return false;
    }
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(minFontSize, 0.0)) {
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint)) {
            LOGE("fail to initialize text paragraph when adapt min text size.");
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
    auto maxSize = GetMaxMeasureSize(contentConstraint);
    while (GreatOrEqual(maxFontSize, minFontSize)) {
        textStyle.SetFontSize(Dimension(maxFontSize));
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint)) {
            return false;
        }
        if (!DidExceedMaxLines(maxSize)) {
            break;
        }
        maxFontSize -= stepSize;
    }
    return true;
}

bool TextLayoutAlgorithm::DidExceedMaxLines(const SizeF& maxSize)
{
    CHECK_NULL_RETURN(paragraph_, false);
    bool didExceedMaxLines = paragraph_->DidExceedMaxLines();
    didExceedMaxLines = didExceedMaxLines || GreatNotEqual(paragraph_->GetHeight(), maxSize.Height());
    didExceedMaxLines = didExceedMaxLines || GreatNotEqual(paragraph_->GetLongestLine(), maxSize.Width());
    return didExceedMaxLines;
}

TextDirection TextLayoutAlgorithm::GetTextDirection(const std::string& content)
{
    TextDirection textDirection = TextDirection::LTR;
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

float TextLayoutAlgorithm::GetTextWidth() const
{
    CHECK_NULL_RETURN(paragraph_, 0.0);
    return paragraph_->GetTextWidth();
}

const RefPtr<Paragraph>& TextLayoutAlgorithm::GetParagraph()
{
    return paragraph_;
}

float TextLayoutAlgorithm::GetBaselineOffset() const
{
    return baselineOffset_;
}

SizeF TextLayoutAlgorithm::GetMaxMeasureSize(const LayoutConstraintF& contentConstraint) const
{
    auto maxSize = contentConstraint.selfIdealSize;
    maxSize.UpdateIllegalSizeWithCheck(contentConstraint.maxSize);
    return maxSize.ConvertToSizeT();
}

std::list<RefPtr<SpanItem>>&& TextLayoutAlgorithm::GetSpanItemChildren()
{
    return std::move(spanItemChildren_);
}

bool TextLayoutAlgorithm::BuildParagraph(TextStyle& textStyle, const RefPtr<TextLayoutProperty>& layoutProperty,
    const LayoutConstraintF& contentConstraint, const RefPtr<PipelineContext>& pipeline)
{
    if (!textStyle.GetAdaptTextSize()) {
        if (!CreateParagraphAndLayout(textStyle, layoutProperty->GetContent().value_or(""), contentConstraint)) {
            return false;
        }
    } else {
        if (!AdaptMinTextSize(textStyle, layoutProperty->GetContent().value_or(""), contentConstraint, pipeline)) {
            return false;
        }
    }

    // Confirmed specification: The width of the text paragraph covers the width of the component, so this code is
    // generally not allowed to be modified
    if (!contentConstraint.selfIdealSize.Width()) {
        float paragraphNewWidth = std::min(GetTextWidth(), paragraph_->GetMaxWidth());
        paragraphNewWidth =
            std::clamp(paragraphNewWidth, contentConstraint.minSize.Width(), contentConstraint.maxSize.Width());
        if (!NearEqual(paragraphNewWidth, paragraph_->GetMaxWidth())) {
            paragraph_->Layout(std::ceil(paragraphNewWidth));
        }
    }
    return true;
}

bool TextLayoutAlgorithm::BuildParagraphAdaptUseMinFontSize(TextStyle& textStyle,
    const RefPtr<TextLayoutProperty>& layoutProperty, const LayoutConstraintF& contentConstraint,
    const RefPtr<PipelineContext>& pipeline)
{
    return AdaptMaxTextSize(textStyle, layoutProperty->GetContent().value_or(""), contentConstraint, pipeline);
}

bool TextLayoutAlgorithm::BuildParagraphAdaptUseLayoutConstraint(TextStyle& textStyle,
    const RefPtr<TextLayoutProperty>& layoutProperty, const LayoutConstraintF& contentConstraint,
    const RefPtr<PipelineContext>& pipeline)
{
    // Create the paragraph and obtain the height.
    if (!BuildParagraph(textStyle, layoutProperty, contentConstraint, pipeline)) {
        return false;
    }
    auto height = static_cast<float>(paragraph_->GetHeight());
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

        if (!BuildParagraph(textStyle, layoutProperty, contentConstraint, pipeline)) {
            return false;
        }
    }
    // Reducing the value of MaxLines to make sure the parapraph could be layout in the constraint of height.
    height = static_cast<float>(paragraph_->GetHeight());
    while (GreatNotEqual(height, contentConstraint.maxSize.Height())) {
        auto maxLines = textStyle.GetMaxLines();
        if (maxLines == 0) {
            break;
        } else {
            maxLines = textStyle.GetMaxLines() - 1;
            textStyle.SetMaxLines(maxLines);
        }
        if (!BuildParagraph(textStyle, layoutProperty, contentConstraint, pipeline)) {
            return false;
        }
        height = static_cast<float>(paragraph_->GetHeight());
    }
    return true;
}

std::optional<SizeF> TextLayoutAlgorithm::BuildTextRaceParagraph(TextStyle& textStyle,
    const RefPtr<TextLayoutProperty>& layoutProperty, const LayoutConstraintF& contentConstraint,
    const RefPtr<PipelineContext>& pipeline)
{
    // create a paragraph with all text in 1 line
    textStyle.SetTextOverflow(TextOverflow::CLIP);
    textStyle.SetMaxLines(1);
    textStyle.SetTextAlign(TextAlign::START);
    if (!CreateParagraph(textStyle, layoutProperty->GetContent().value_or(""))) {
        return std::nullopt;
    }
    if (!paragraph_) {
        return std::nullopt;
    }

    // layout the paragraph to the width of text
    paragraph_->Layout(std::numeric_limits<float>::max());
    float paragraphWidth = paragraph_->GetTextWidth();
    paragraph_->Layout(paragraphWidth);

    textStyle_ = textStyle;

    // calculate the content size
    auto height = static_cast<float>(paragraph_->GetHeight());
    double baselineOffset = 0.0;
    if (layoutProperty->GetBaselineOffsetValue(Dimension())
            .NormalizeToPx(
                pipeline->GetDipScale(), pipeline->GetFontScale(), pipeline->GetLogicScale(), height, baselineOffset)) {
        baselineOffset_ = static_cast<float>(baselineOffset);
    }
    float heightFinal =
        std::min(static_cast<float>(height + std::fabs(baselineOffset)), contentConstraint.maxSize.Height());

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

void TextLayoutAlgorithm::SetPropertyToModifier(
    const RefPtr<TextLayoutProperty>& layoutProperty, RefPtr<TextContentModifier> modifier)
{
    auto fontSize = layoutProperty->GetFontSize();
    if (fontSize.has_value()) {
        modifier->SetFontSize(fontSize.value());
    }
    auto fontWeight = layoutProperty->GetFontWeight();
    if (fontWeight.has_value()) {
        modifier->SetFontWeight(fontWeight.value());
    }
    auto textColor = layoutProperty->GetTextColor();
    if (textColor.has_value()) {
        modifier->SetTextColor(textColor.value());
    }
    auto textShadow = layoutProperty->GetTextShadow();
    if (textShadow.has_value()) {
        modifier->SetTextShadow(textShadow.value());
    }
    auto textDecorationColor = layoutProperty->GetTextDecorationColor();
    if (textDecorationColor.has_value()) {
        modifier->SetTextDecorationColor(textDecorationColor.value());
    }
    auto textDecoration = layoutProperty->GetTextDecoration();
    if (textDecoration.has_value()) {
        modifier->SetTextDecoration(textDecoration.value());
    }
    auto baselineOffset = layoutProperty->GetBaselineOffset();
    if (baselineOffset.has_value()) {
        modifier->SetBaselineOffset(baselineOffset.value());
    }
}

bool TextLayoutAlgorithm::AdaptMaxTextSize(TextStyle& textStyle, const std::string& content,
    const LayoutConstraintF& contentConstraint, const RefPtr<PipelineContext>& pipeline)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    if (!textStyle.GetAdaptMaxFontSize().NormalizeToPx(
        pipeline->GetDipScale(), pipeline->GetFontScale(), pipeline->GetLogicScale(),
        contentConstraint.maxSize.Height(), maxFontSize)) {
        return false;
    }
    if (!textStyle.GetAdaptMinFontSize().NormalizeToPx(
        pipeline->GetDipScale(), pipeline->GetFontScale(), pipeline->GetLogicScale(),
        contentConstraint.maxSize.Height(), minFontSize)) {
        return false;
    }
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(minFontSize, 0.0)) {
        // minFontSize or maxFontSize is invalid
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint)) {
            LOGE("fail to initialize text paragraph when adapt min text size.");
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
    RefPtr<Paragraph> paragraph;
    auto maxSize = GetMaxMeasureSize(contentConstraint);
    // Use the minFontSize to layout the paragraph. While using the minFontSize, if the paragraph could be layout in 1
    // line, then increase the font size and try to layout using the maximum available fontsize.
    while (LessOrEqual(minFontSize, maxFontSize)) {
        textStyle.SetFontSize(Dimension(minFontSize));
        if (!CreateParagraphAndLayout(textStyle, content, contentConstraint)) {
            return false;
        }
        if (paragraph_->GetLineCount() > 1 || GreatNotEqual(paragraph_->GetLongestLine(), maxSize.Width())) {
            if (paragraph != nullptr) {
                paragraph_ = paragraph;
            }
            break;
        }
        minFontSize += stepSize;
        paragraph = paragraph_;
    }
    return true;
}

std::optional<TextStyle> TextLayoutAlgorithm::GetTextStyle() const
{
    return textStyle_;
}

void TextLayoutAlgorithm::UpdateTextColorIfForeground(const RefPtr<FrameNode>& frameNode, TextStyle& textStyle)
{
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext->HasForegroundColor() || renderContext->HasForegroundColorStrategy()) {
        textStyle.SetTextColor(Color::FOREGROUND);
    }
}
} // namespace OHOS::Ace::NG
