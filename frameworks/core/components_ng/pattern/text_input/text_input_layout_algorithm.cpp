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

#include "core/components_ng/pattern/text_input/text_input_layout_algorithm.h"

#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
std::optional<SizeF> TextInputLayoutAlgorithm::MeasureContent(
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

    auto isPasswordType =
        textFieldLayoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD;

    // Create paragraph.
    auto disableTextAlign = !pattern->IsTextArea() && !showPlaceHolder_ && !isInlineStyle;
    if (pattern->IsDragging() && !showPlaceHolder_) {
        CreateParagraph(textStyle, pattern->GetDragContents(), textContent_,
            isPasswordType && pattern->GetTextObscured() && !showPlaceHolder_, disableTextAlign);
    } else {
        CreateParagraph(textStyle, textContent_, isPasswordType && pattern->GetTextObscured() && !showPlaceHolder_,
            pattern->GetNakedCharPosition(), disableTextAlign);
    }

    autoWidth_ = textFieldLayoutProperty->GetWidthAutoValue(false);

    // errorParagraph  Layout.
    if (textFieldLayoutProperty->GetShowErrorTextValue(false)) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, std::nullopt);
        auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
        CHECK_NULL_RETURN(textFieldTheme, std::nullopt);
        CreateErrorParagraph(textFieldLayoutProperty->GetErrorTextValue(""), textFieldTheme);
        if (errorParagraph_) {
            errorParagraph_->Layout(std::numeric_limits<double>::infinity());
        }
    }

    // Used for empty text.
    preferredHeight_ = pattern->PreferredLineHeight();

    // Paragraph layout.
    if (isInlineStyle) {
        return InlineMeasureContent(contentConstraint, layoutWrapper);
    } else if (showPlaceHolder_) {
        return PlaceHolderMeasureContent(contentConstraint, layoutWrapper, 0);
    } else {
        return TextInputMeasureContent(contentConstraint, layoutWrapper, 0);
    }
}

void TextInputLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto defaultHeight = static_cast<float>(textFieldTheme->GetHeight().ConvertToPx());

    frameSize.SetWidth(contentWidth + pattern->GetHorizontalPaddingAndBorderSum());

    auto contentConstraint = layoutWrapper->GetLayoutProperty()->CreateContentConstraint();
    if (contentConstraint.selfIdealSize.Height().has_value()) {
        frameSize.SetHeight(contentConstraint.maxSize.Height() + pattern->GetVerticalPaddingAndBorderSum());
    } else {
        auto height = contentHeight + pattern->GetVerticalPaddingAndBorderSum() < defaultHeight
                          ? defaultHeight
                          : contentHeight + pattern->GetVerticalPaddingAndBorderSum();
        frameSize.SetHeight(height);
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    } else {
        auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(frameSize,
            layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
            layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
        frameSize.SetHeight(finalSize.Height());
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
    auto responseArea = pattern->GetResponseArea();
    if (responseArea && content) {
        auto contentConstraint = layoutWrapper->GetLayoutProperty()->CreateContentConstraint();
        auto childWidth = responseArea->Measure(layoutWrapper).Width();
        if (LessOrEqual(contentWidth + childWidth, contentConstraint.maxSize.Width())) {
            frameSize.SetWidth(contentWidth + pattern->GetHorizontalPaddingAndBorderSum() + childWidth);
        } else {
            content->SetSize(SizeF(contentConstraint.maxSize.Width() - childWidth, contentHeight));
            frameSize.SetWidth(contentConstraint.maxSize.Width() + pattern->GetHorizontalPaddingAndBorderSum());
        }
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
    }
}

void TextInputLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
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
    content->SetOffset(OffsetF(pattern->GetPaddingLeft() + pattern->GetBorderLeft(), contentOffset.GetY()));
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (LessOrEqual(textRect_.Width(), contentSize.Width())) {
        // adjust text rect to the basic padding
        float textRectOffsetX = 0.0f;
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            textRectOffsetX = pattern->GetPaddingLeft();
        } else {
            textRectOffsetX = pattern->GetPaddingLeft() + pattern->GetBorderLeft();
        }
        auto isEmptyTextEditValue = pattern->GetTextValue().empty();
        auto isInlineStyle = pattern->IsNormalInlineState();
        if (!isEmptyTextEditValue && !isInlineStyle) {
            switch (layoutProperty->GetTextAlignValue(TextAlign::START)) {
                case TextAlign::START:
                    break;
                case TextAlign::CENTER:
                    textRectOffsetX += (contentSize.Width() - textRect_.Width()) * 0.5f;
                    break;
                case TextAlign::END:
                    textRectOffsetX += contentSize.Width() - textRect_.Width();
                    break;
                default:
                    break;
            }
        }
        textRect_.SetOffset(OffsetF(textRectOffsetX, contentOffset.GetY()));
    } else {
        textRect_.SetOffset({ pattern->GetTextRect().GetOffset().GetX(), contentOffset.GetY() });
    }
    auto responseArea = pattern->GetResponseArea();
    if (responseArea) {
        responseArea->Layout(layoutWrapper);
    }
}

} // namespace OHOS::Ace::NG