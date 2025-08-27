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

#include "core/components_ng/pattern/text_area/text_area_layout_algorithm.h"

#include <optional>

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PARAGRAPH_SAVE_BOUNDARY = 1.0f;
constexpr uint32_t DEFAULT_MINLINES = 1;
} // namespace
std::optional<SizeF> TextAreaLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto textFieldLayoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);

    // Construct text style.
    TextStyle textStyle;
    ConstructTextStyles(frameNode, textStyle, textContent_, showPlaceHolder_);

    auto isInlineStyle = pattern->IsNormalInlineState();
    isInlineFocus_ = isInlineStyle && pattern->HasFocus();
    if (!isInlineStyle && textFieldLayoutProperty->HasNormalMaxViewLines()) {
        UpdateTextAreaMaxLines(textStyle, textFieldLayoutProperty);
    }

    if (isInlineStyle && textFieldLayoutProperty->HasTextOverflow()) {
        if (textFieldLayoutProperty->HasTextOverflowMaxLines()) {
            textStyle.SetMaxLines(textFieldLayoutProperty->GetTextOverflowMaxLinesValue());
        } else if (textFieldLayoutProperty->HasNormalMaxViewLines()) {
            textStyle.SetMaxLines(textFieldLayoutProperty->GetNormalMaxViewLines().value());
        }
    }

    direction_ = textFieldLayoutProperty->GetLayoutDirection();

    // Create paragraph.
    pattern->SetAdaptFontSize(std::nullopt);
    auto textFieldContentConstraint = CalculateContentMaxSizeWithCalculateConstraint(contentConstraint, layoutWrapper);
    if (IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, textFieldContentConstraint)) {
        if (!AddAdaptFontSizeAndAnimations(textStyle, textFieldLayoutProperty, textFieldContentConstraint,
            layoutWrapper)) {
            return std::nullopt;
        }
        pattern->SetAdaptFontSize(textStyle.GetFontSize());
    } else {
        CreateParagraphEx(textStyle, textContent_, contentConstraint, layoutWrapper);
    }

    autoWidth_ = textFieldLayoutProperty->GetWidthAutoValue(false);

    if (textContent_.empty()) {
        // Used for empty text.
        preferredHeight_ = pattern->PreferredLineHeight(true);
    }
    std::optional<SizeF> contentSize;
    // Paragraph layout.}
    if (isInlineStyle) {
        auto fontSize = textStyle.GetFontSize().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        auto paragraphData = CreateParagraphData { false, fontSize };
        CreateInlineParagraph(textStyle, textContent_, false, pattern->GetNakedCharPosition(), paragraphData);
        contentSize = InlineMeasureContent(textFieldContentConstraint, layoutWrapper);
    } else if (showPlaceHolder_) {
        contentSize = PlaceHolderMeasureContent(textFieldContentConstraint, layoutWrapper);
        if (textFieldLayoutProperty->GetShowCounterValue(false) && textFieldLayoutProperty->HasMaxLength() &&
            paragraph_->GetLineCount() > 1 && isPlaceHolderOverSize_ &&
            pattern->IsTextArea() && !pattern->IsNormalInlineState()) {
                contentSize = ReMeasureContentForPlaceholder(textFieldContentConstraint, layoutWrapper,
                    textStyle, textFieldContentConstraint);
            }
    } else {
        contentSize = TextAreaMeasureContent(textFieldContentConstraint, layoutWrapper);
    }
    CalcMeasureContentWithMinLines(contentSize, layoutWrapper, contentConstraint);
    return contentSize;
}

std::optional<SizeF> TextAreaLayoutAlgorithm::ReMeasureContentForPlaceholder(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper,
    TextStyle& textStyle, LayoutConstraintF& textFieldContentConstraint)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto textFieldLayoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textFieldLayoutProperty, std::nullopt);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto lineCount = paragraph_->GetLineCount() != 0 ? paragraph_->GetLineCount() : 1;

    float height = 0.0f;
    if (isFontSizeNonPositive_) {
        height = paragraph_->GetHeight();
    } else {
        height = GreatNotEqual(paragraph_->GetLongestLine(), 0.0) ? paragraph_->GetHeight()
                                                                  : std::max(preferredHeight_, paragraph_->GetHeight());
    }
    auto paragraphHeight = height / lineCount;
    auto contentHeight = std::min(contentConstraint.maxSize.Height(), height);
    auto contentWidth = ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph_);

    auto counterNodeHeight = CounterNodeMeasure(contentWidth, layoutWrapper);
    // new height consider counter
    contentHeight = std::max(std::min(contentConstraint.maxSize.Height() - counterNodeHeight, height), 0.0f);

    auto targetLines = 1.0f;
    if (!NearEqual(paragraphHeight, 0.0f)) {
        targetLines = std::max(targetLines, contentHeight / paragraphHeight);
    }

    textStyle.SetMaxLines(static_cast<uint32_t>(targetLines)); // replace with new maxlines for ellipsis

    if (IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, textFieldContentConstraint)) {
        if (!AddAdaptFontSizeAndAnimations(textStyle, textFieldLayoutProperty, textFieldContentConstraint,
            layoutWrapper)) {
            return std::nullopt;
        }
        pattern->SetAdaptFontSize(textStyle.GetFontSize());
    } else {
        CreateParagraphEx(textStyle, textContent_, contentConstraint, layoutWrapper);
    }

    return PlaceHolderMeasureContent(textFieldContentConstraint, layoutWrapper);
}

void TextAreaLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    OptionalSizeF frameSize;
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    float contentWidth = 0.0f;
    float contentHeight = 0.0f;
    if (content) {
        auto contentSize = content->GetRect().GetSize();
        contentWidth = contentSize.Width();
        contentHeight = contentSize.Height();
    }
    // Add children height;
    auto counterDecorator = pattern->GetCounterDecorator();
    if (counterDecorator && !pattern->IsNormalInlineState()) {
        contentHeight += counterDecorator->GetDecoratorHeight();
    }

    auto finalWidth = 0;
    if (pattern->IsNormalInlineState() && pattern->HasFocus()) {
        finalWidth = contentWidth + pattern->GetHorizontalPaddingAndBorderSum() + PARAGRAPH_SAVE_BOUNDARY;
        frameSize.SetWidth(finalWidth);
        frameSize.SetHeight(contentHeight + pattern->GetVerticalPaddingAndBorderSum() + PARAGRAPH_SAVE_BOUNDARY);
    } else {
        // The width after MeasureContent is already optimal, but the height needs to be constrained in Measure.
        finalWidth = contentWidth + pattern->GetHorizontalPaddingAndBorderSum();
        frameSize.SetWidth(finalWidth);
        ConstraintHeight(layoutWrapper, frameSize, contentHeight);
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

void TextAreaLayoutAlgorithm::ConstraintHeight(LayoutWrapper* layoutWrapper, OptionalSizeF& frameSize,
    float contentHeight)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto contentConstraint = layoutWrapper->GetLayoutProperty()->CreateContentConstraint();
    auto textFieldContentConstraint =
        CalculateContentMaxSizeWithCalculateConstraint(contentConstraint, layoutWrapper);
    if (textFieldContentConstraint.selfIdealSize.Height().has_value()) {
        frameSize.SetHeight(textFieldContentConstraint.maxSize.Height() + pattern->GetVerticalPaddingAndBorderSum());
    } else {
        frameSize.SetHeight(contentHeight + pattern->GetVerticalPaddingAndBorderSum());
    }

    // Height is constrained by the CalcLayoutConstraint.
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    } else if (!layoutWrapper->GetLayoutProperty()->GetLayoutRect()) {
        auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(frameSize,
            layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
            layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
        frameSize.SetHeight(finalSize.Height());
    }
}

void TextAreaLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize() -
                SizeF(pattern->GetHorizontalPaddingAndBorderSum(), pattern->GetVerticalPaddingAndBorderSum());

    // Remove counterNode height.
    auto counterDecorator = pattern->GetCounterDecorator();
    if (counterDecorator && !pattern->IsNormalInlineState()) {
        size.SetHeight(size.Height() - counterDecorator->GetDecoratorHeight());
    }

    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto layoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto context = layoutWrapper->GetHostNode()->GetContext();
    CHECK_NULL_VOID(context);
    parentGlobalOffset_ = layoutWrapper->GetHostNode()->GetPaintRectOffset(false, true) -
        context->GetRootRect().GetOffset();
    auto align = Alignment::TOP_CENTER;

    auto border = pattern->GetBorderWidthProperty();
    auto offsetBase = OffsetF(pattern->GetPaddingLeft() + pattern->GetBorderLeft(border),
        pattern->GetPaddingTop() + pattern->GetBorderTop(border));
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    // Update text position.
    if (LessOrEqual(textRect_.Height(), content->GetRect().Height())) {
        auto textRect = textRect_.GetSize();
        if (LessOrEqual(textRect.Height(), 0.0)) {
            textRect.SetHeight(content->GetRect().Height());
        }
        OffsetF textRectOffSet = Alignment::GetAlignPosition(size, textRect, align);
        textRect_.SetOffset(OffsetF(0.0f, textRectOffSet.GetY()) + offsetBase);
        content->SetOffset(OffsetF(0.0f, textRectOffSet.GetY()) + offsetBase);
    } else {
        textRect_.SetOffset(
            showPlaceHolder_ ? offsetBase : OffsetF(offsetBase.GetX(), pattern->GetTextRect().GetOffset().GetY()));
        content->SetOffset(offsetBase);
    }
    // CounterNode Layout.
    auto isInlineStyle = pattern->IsNormalInlineState();
    if (layoutProperty->GetShowCounterValue(false) && layoutProperty->HasMaxLength() && !isInlineStyle) {
        TextFieldLayoutAlgorithm::CounterLayout(layoutWrapper);
    }
}

bool TextAreaLayoutAlgorithm::CreateParagraphEx(const TextStyle& textStyle, const std::u16string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto isInlineStyle = pattern->IsNormalInlineState();
    auto fontSize = textStyle.GetFontSize().ConvertToPxDistribute(
        textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    auto paragraphData = CreateParagraphData { false, fontSize };
    if (pattern->IsDragging() && !showPlaceHolder_ && !isInlineStyle) {
        CreateParagraph(textStyle, pattern->GetDragContents(), content, false, paragraphData);
    } else {
        CreateParagraph(textStyle, content, false, pattern->GetNakedCharPosition(), paragraphData);
    }
    return true;
}

void TextAreaLayoutAlgorithm::CalcMeasureContentWithMinLines(
    std::optional<SizeF>& size, LayoutWrapper* layoutWrapper, const LayoutConstraintF& contentConstraint)
{
    CHECK_NULL_VOID(layoutWrapper);
    if (!size.has_value()) {
        return;
    }
    auto textFieldLayoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (!(textFieldLayoutProperty && textFieldLayoutProperty->HasMinLines() &&
            textFieldLayoutProperty->GetMinLines().value() >= DEFAULT_MINLINES)) {
        return;
    }
    auto paragraph = GetParagraph();
    CHECK_NULL_VOID(paragraph);
    auto paragraphHeight = paragraph->GetHeight();
    if (LessOrEqual(paragraphHeight, 0.0)) {
        return;
    }
    auto lineCount = std::max(static_cast<uint32_t>(paragraph->GetLineCount()), DEFAULT_MINLINES);
    auto perLineHeight = paragraphHeight / lineCount;
    auto minLines = textFieldLayoutProperty->GetMinLines().value();
    if (textFieldLayoutProperty->HasNormalMaxViewLines()) {
        minLines = std::min(minLines, textFieldLayoutProperty->GetNormalMaxViewLines().value());
    }
    auto finalMinHeight = perLineHeight * minLines;
    finalMinHeight = std::clamp(finalMinHeight, contentConstraint.minSize.Height(), contentConstraint.maxSize.Height());
    if (GreatNotEqual(finalMinHeight, size.value().Height())) {
        size.value().SetHeight(finalMinHeight);
    }
}
} // namespace OHOS::Ace::NG
