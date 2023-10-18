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
constexpr uint32_t COUNTER_TEXT_MAXLINE = 1;
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

    // Create paragraph.
    if (pattern->IsDragging() && !showPlaceHolder_) {
        CreateParagraph(textStyle, pattern->GetDragContents(), textContent_, false);
    } else {
        CreateParagraph(textStyle, textContent_, false, pattern->GetNakedCharPosition());
    }

    // Used for empty text.
    preferredHeight_ = pattern->PreferredLineHeight();

    // Paragraph layout.}
    if (isInlineStyle) {
        return InlineMeasureContent(contentConstraint, layoutWrapper);
    } else if (showPlaceHolder_) {
        return PlaceHolderMeasureContent(contentConstraint, layoutWrapper);
    } else {
        return TextAreaMeasureContent(contentConstraint, layoutWrapper);
    }
}

float TextAreaLayoutAlgorithm::CounterNodeMeasure(float contentWidth, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, 0.0f);
    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, 0.0f);
    auto isInlineStyle = pattern->IsNormalInlineState();
    if (textFieldLayoutProperty->GetShowCounterValue(false) && textFieldLayoutProperty->HasMaxLength() &&
        !isInlineStyle) {
        auto counterNodeLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
        if (counterNodeLayoutWrapper) {
            auto textLength =
                static_cast<uint32_t>(showPlaceHolder_ ? 0 : StringUtils::ToWstring(textContent_).length());
            auto maxLength = static_cast<uint32_t>(textFieldLayoutProperty->GetMaxLength().value());
            LayoutConstraintF textContentConstraint;
            textContentConstraint.UpdateIllegalSelfIdealSizeWithCheck(OptionalSizeF(contentWidth, std::nullopt));
            CounterNodeMeasureContent(textLength, maxLength, textContentConstraint, counterNodeLayoutWrapper);
            return counterNodeLayoutWrapper->GetGeometryNode()->GetFrameSize().Height();
        }
    }
    return 0.0f;
}

void TextAreaLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
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
    auto counterNodeLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    if (counterNodeLayoutWrapper) {
        auto counterSize = counterNodeLayoutWrapper->GetGeometryNode()->GetFrameSize();
        contentHeight += counterSize.Height();
    }

    if (pattern->IsNormalInlineState() && pattern->IsFocus()) {
        frameSize.SetWidth(contentWidth + pattern->GetHorizontalPaddingAndBorderSum() + PARAGRAPH_SAVE_BOUNDARY);
        frameSize.SetHeight(contentHeight + pattern->GetVerticalPaddingAndBorderSum() + PARAGRAPH_SAVE_BOUNDARY);
    } else {
        // The width after MeasureContent is already optimal, but the height needs to be constrained in Measure.
        frameSize.SetWidth(contentWidth + pattern->GetHorizontalPaddingAndBorderSum());
        auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(textFieldLayoutProperty);
        auto contentConstraint = layoutWrapper->GetLayoutProperty()->CreateContentConstraint();
        if (contentConstraint.selfIdealSize.Height().has_value()) {
            frameSize.SetHeight(contentConstraint.maxSize.Height() + pattern->GetVerticalPaddingAndBorderSum());
        } else {
            frameSize.SetHeight(contentHeight + pattern->GetVerticalPaddingAndBorderSum());
        }
        // Height is constrained by the CalcLayoutConstraint.
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
        } else {
            auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(frameSize,
                layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
                layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
            frameSize.SetHeight(finalSize.Height());
        }
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

void TextAreaLayoutAlgorithm::CounterNodeMeasureContent(uint32_t textLength, uint32_t maxLength,
    const LayoutConstraintF& contentConstraint, RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    TextStyle countTextStyle = (textLength != maxLength) ? theme->GetCountTextStyle() : theme->GetOverCountTextStyle();
    auto textNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);

    std::string counterText = std::to_string(textLength) + "/" + std::to_string(maxLength);
    textLayoutProperty->UpdateContent(counterText);
    textLayoutProperty->UpdateFontSize(countTextStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(countTextStyle.GetTextColor());
    textLayoutProperty->UpdateFontWeight(countTextStyle.GetFontWeight());
    textLayoutProperty->UpdateTextAlign(TextAlign::END);
    textLayoutProperty->UpdateMaxLines(COUNTER_TEXT_MAXLINE);

    layoutWrapper->Measure(contentConstraint);
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
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto layoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto context = layoutWrapper->GetHostNode()->GetContext();
    CHECK_NULL_VOID(context);
    parentGlobalOffset_ = layoutWrapper->GetHostNode()->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    auto align = Alignment::TOP_CENTER;

    auto offsetBase = OffsetF(
        pattern->GetPaddingLeft() + pattern->GetBorderLeft(), pattern->GetPaddingTop() + pattern->GetBorderTop());
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    // Update text position.
    if (LessOrEqual(textRect_.Height(), content->GetRect().Height())) {
        OffsetF textRectOffSet = Alignment::GetAlignPosition(size, textRect_.GetSize(), align);
        textRect_.SetOffset(OffsetF(0.0f, textRectOffSet.GetY()) + offsetBase);
        content->SetOffset(OffsetF(0.0f, textRectOffSet.GetY()) + offsetBase);
    } else {
        textRect_.SetOffset(pattern->GetTextRect().GetOffset());
        content->SetOffset(offsetBase);
    }
    // CounterNode Layout.
    auto isInlineStyle = pattern->IsNormalInlineState();
    if (layoutProperty->GetShowCounterValue(false) && layoutProperty->HasMaxLength() && !isInlineStyle) {
        CounterLayout(layoutWrapper);
    }
}

void TextAreaLayoutAlgorithm::CounterLayout(LayoutWrapper* layoutWrapper)
{
    auto counterNodeLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    if (counterNodeLayoutWrapper) {
        auto frameNode = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(pattern);
        auto frameRect = layoutWrapper->GetGeometryNode()->GetFrameRect();
        auto textGeometryNode = counterNodeLayoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
        const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
        CHECK_NULL_VOID(content);
        textGeometryNode->SetFrameOffset(OffsetF(content->GetRect().GetX(),
            frameRect.Height() - pattern->GetPaddingBottom() - textGeometryNode->GetFrameRect().Height()));
        counterNodeLayoutWrapper->Layout();
    }
}

} // namespace OHOS::Ace::NG