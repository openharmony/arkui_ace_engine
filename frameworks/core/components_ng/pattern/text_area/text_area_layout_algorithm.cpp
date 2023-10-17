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
    std::string textContent;
    bool showPlaceHolder = false;
    ConstructTextStyles(frameNode, textStyle, textContent, showPlaceHolder);

    auto isInlineStyle = pattern->IsNormalInlineState();

    // Create paragraph.
    if (pattern->IsDragging() && !showPlaceHolder) {
        CreateParagraph(textStyle, pattern->GetDragContents(), textContent, false);
    } else {
        CreateParagraph(textStyle, textContent, false, pattern->GetNakedCharPosition());
    }

    // constraint size.
    auto contentIdealSize = CalculateConstraintSize(contentConstraint, layoutWrapper);

    // CounterNode measureContent.
    if (textFieldLayoutProperty->GetShowCounterValue(false) && textFieldLayoutProperty->HasMaxLength() &&
        !isInlineStyle) {
        auto counterNodeLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
        if (counterNodeLayoutWrapper) {
            auto textLength = static_cast<uint32_t>(showPlaceHolder ? 0 : StringUtils::ToWstring(textContent).length());
            auto maxLength = static_cast<uint32_t>(textFieldLayoutProperty->GetMaxLength().value());
            LayoutConstraintF textContentConstraint;
            textContentConstraint.UpdateIllegalSelfIdealSizeWithCheck(
                OptionalSizeF(contentIdealSize.Width(), std::nullopt));
            CounterNodeMeasureContent(textLength, maxLength, textContentConstraint, counterNodeLayoutWrapper);
            auto height = counterNodeLayoutWrapper->GetGeometryNode()->GetFrameSize().Height();
            contentIdealSize.SetHeight(std::max(contentIdealSize.Height() - height, 0.0f));
        }
    }

    // Used for empty text.
    preferredHeight_ = pattern->PreferredLineHeight();

    // Paragraph layout.}
    if (isInlineStyle) {
        return InlineMeasureContent(contentConstraint, layoutWrapper, contentIdealSize);
    } else if (showPlaceHolder) {
        return PlaceHolderMeasureContent(contentIdealSize);
    } else {
        return TextAreaMeasureContent(contentIdealSize);
    }
}

void TextAreaLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    OptionalSizeF frameSize =
        CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT_MAIN_AXIS);
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    const auto& calcLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint();
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
        frameSize.SetWidth(contentWidth + pattern->GetHorizontalPaddingSum() + PARAGRAPH_SAVE_BOUNDARY);
        frameSize.SetHeight(contentHeight + pattern->GetVerticalPaddingSum() + PARAGRAPH_SAVE_BOUNDARY);
    } else {
        auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(textFieldLayoutProperty);
        if (!frameSize.Width().has_value()) {
            // If width is not set, select the maximum value of minWidth and maxWidth to layoutConstraint
            if (calcLayoutConstraint && calcLayoutConstraint->maxSize.has_value() &&
                calcLayoutConstraint->maxSize.value().Width().has_value()) {
                frameSize.SetHeight(
                    std::min(layoutConstraint->maxSize.Width(), contentWidth + pattern->GetHorizontalPaddingSum()));
            } else if (!calcLayoutConstraint) {
                // If calcLayoutConstraint has not set, use the LayoutConstraint initial value
                frameSize.SetWidth(contentWidth + pattern->GetHorizontalPaddingSum());
            } else {
                // If maxWidth is not set and calcLayoutConstraint is set, set minWidth to layoutConstraint
                frameSize.SetWidth(layoutConstraint->minSize.Width());
            }
        }
        if (!frameSize.Height().has_value()) {
            // Like width
            if (calcLayoutConstraint && calcLayoutConstraint->maxSize.has_value() &&
                calcLayoutConstraint->maxSize.value().Height().has_value()) {
                frameSize.SetHeight(
                    std::min(layoutConstraint->maxSize.Height(), contentHeight + pattern->GetVerticalPaddingSum()));
            } else if (!calcLayoutConstraint || NearZero(layoutConstraint->minSize.Height())) {
                // calcLayoutConstraint initialized once when setting width, set minHeight=0,
                // so add "minHeight=0" to the constraint.
                frameSize.SetHeight(
                    std::min(layoutConstraint->maxSize.Height(), contentHeight + pattern->GetVerticalPaddingSum()));
            } else {
                frameSize.SetHeight(
                    std::max(layoutConstraint->minSize.Height(), contentHeight + pattern->GetVerticalPaddingSum()));
            }
        }

        if (textFieldLayoutProperty->GetWidthAutoValue(false)) {
            frameSize.SetWidth(std::min(contentWidth, textRect_.Width()) + pattern->GetHorizontalPaddingSum());
        }

        // Here's what happens when the height or width is set at list one
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
        } else {
            auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(frameSize,
                layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
                layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
            frameSize.SetWidth(finalSize.Width());
            frameSize.SetHeight(finalSize.Height());
        }
        if (layoutConstraint->maxSize.Height() < layoutConstraint->minSize.Height()) {
            frameSize.SetHeight(layoutConstraint->minSize.Height());
        }
        if (layoutConstraint->maxSize.Width() < layoutConstraint->minSize.Width()) {
            frameSize.SetWidth(layoutConstraint->minSize.Width());
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
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentSize = content->GetRect().GetSize();
    auto layoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto context = layoutWrapper->GetHostNode()->GetContext();
    CHECK_NULL_VOID(context);
    parentGlobalOffset_ = layoutWrapper->GetHostNode()->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    auto align = Alignment::CENTER;
    bool hasAlign = false;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
        hasAlign = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().has_value();
    }
    // Update content position.
    OffsetF contentOffset = Alignment::GetAlignPosition(size, contentSize, align);
    auto isInlineStyle = pattern->IsNormalInlineState();
    if (hasAlign) {
        if (isInlineStyle) {
            content->SetOffset(OffsetF(pattern->GetUtilPadding().Offset().GetX(), contentOffset.GetY()));
        } else {
            content->SetOffset(OffsetF(pattern->GetUtilPadding().Offset().GetX() + pattern->GetBorderLeft(),
                contentOffset.GetY() + pattern->GetBorderTop()));
        }

        OffsetF textRectOffSet = Alignment::GetAlignPosition(size, textRect_.GetSize(), align);
        if (LessOrEqual(textRect_.Height(), content->GetRect().Height())) {
            textRect_.SetOffset(OffsetF(pattern->GetTextRect().GetOffset().GetX(), textRectOffSet.GetY()));
        } else {
            textRect_.SetOffset(pattern->GetTextRect().GetOffset());
        }
    } else {
        if (isInlineStyle) {
            content->SetOffset(pattern->GetUtilPadding().Offset());
        } else {
            content->SetOffset(OffsetF(pattern->GetUtilPadding().Offset().GetX() + pattern->GetBorderLeft(),
                pattern->GetUtilPadding().Offset().GetY() + pattern->GetBorderTop()));
        }
        textRect_.SetOffset(pattern->GetTextRect().GetOffset());
    }

    // CounterNode Layout.
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