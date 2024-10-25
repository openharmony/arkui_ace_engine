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

#include "base/utils/utils.h"
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
    std::replace(textContent_.begin(), textContent_.end(), '\n', ' ');

    auto isInlineStyle = pattern->IsNormalInlineState();

    direction_ = textFieldLayoutProperty->GetLayoutDirection();

    // Create paragraph.
    pattern->SetAdaptFontSize(std::nullopt);
    auto disableTextAlign = !pattern->IsTextArea() && !showPlaceHolder_ && !isInlineStyle;
    textFieldContentConstraint_ = CalculateContentMaxSizeWithCalculateConstraint(contentConstraint, layoutWrapper);
    auto contentConstraintWithoutResponseArea =
        BuildLayoutConstraintWithoutResponseArea(textFieldContentConstraint_, layoutWrapper);
    if (IsNeedAdaptFontSize(textStyle, textFieldLayoutProperty, textFieldContentConstraint_)) {
        if (!AddAdaptFontSizeAndAnimations(
            textStyle, textFieldLayoutProperty, contentConstraintWithoutResponseArea, layoutWrapper)) {
            return std::nullopt;
        }
        pattern->SetAdaptFontSize(textStyle.GetFontSize());
    } else {
        CreateParagraphEx(textStyle, textContent_, contentConstraint, layoutWrapper);
    }

    autoWidth_ = textFieldLayoutProperty->GetWidthAutoValue(false);
    isFontSizeNonPositive_ = IsFontSizeNonPositive(textStyle);

    if (textContent_.empty()) {
        // Used for empty text.
        preferredHeight_ = pattern->PreferredLineHeight(true);
    }

    // Paragraph layout.
    if (isInlineStyle) {
        auto fontSize = pattern->FontSizeConvertToPx(textStyle.GetFontSize());
        auto paragraphData = CreateParagraphData { disableTextAlign, fontSize };
        CreateInlineParagraph(textStyle, textContent_, false, pattern->GetNakedCharPosition(), paragraphData);
        return InlineMeasureContent(contentConstraintWithoutResponseArea, layoutWrapper);
    }
    if (showPlaceHolder_) {
        return PlaceHolderMeasureContent(contentConstraintWithoutResponseArea, layoutWrapper, 0);
    }
    return TextInputMeasureContent(contentConstraintWithoutResponseArea, layoutWrapper, 0);
}

bool TextInputLayoutAlgorithm::IsFontSizeNonPositive(const TextStyle& textStyle) const
{
    return textStyle.GetFontSize().IsNonPositive();
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
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto defaultHeight = GetDefaultHeightByType(layoutWrapper);

    auto responseAreaWidth = 0.0f;
    if (pattern->GetCleanNodeResponseArea()) {
        responseAreaWidth += pattern->GetCleanNodeResponseArea()->GetFrameSize().Width();
    }
    if (pattern->GetResponseArea()) {
        responseAreaWidth += pattern->GetResponseArea()->GetFrameSize().Width();
    }
    frameSize.SetWidth(contentWidth + pattern->GetHorizontalPaddingAndBorderSum() + responseAreaWidth);

    if (textFieldContentConstraint_.selfIdealSize.Height().has_value()) {
        if (LessOrEqual(contentWidth, 0)) {
            frameSize.SetHeight(textFieldContentConstraint_.maxSize.Height());
        } else {
            frameSize.SetHeight(
                textFieldContentConstraint_.maxSize.Height() + pattern->GetVerticalPaddingAndBorderSum());
        }
    } else {
        auto height = LessNotEqual(contentHeight, defaultHeight)
                          ? defaultHeight + pattern->GetVerticalPaddingAndBorderSum()
                          : contentHeight + pattern->GetVerticalPaddingAndBorderSum();
        frameSize.SetHeight(height);
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    } else if (!layoutWrapper->GetLayoutProperty()->GetLayoutRect()) {
        auto frameSizeConstraint = CalculateFrameSizeConstraint(textFieldContentConstraint_, layoutWrapper);
        auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(frameSize,
            layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
            layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
        frameSize.SetHeight(finalSize.Height());
        frameSize.Constrain(frameSizeConstraint.minSize, frameSizeConstraint.maxSize);
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

void TextInputLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize() -
                SizeF(pattern->GetHorizontalPaddingAndBorderSum(), pattern->GetVerticalPaddingAndBorderSum());
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    SizeT<float> contentSize = content->GetRect().GetSize();
    auto layoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    PipelineContext* context = layoutWrapper->GetHostNode()->GetContext();
    CHECK_NULL_VOID(context);
    parentGlobalOffset_ = layoutWrapper->GetHostNode()->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    Alignment align = Alignment::CENTER;
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto hasAlign = false;
    if (layoutProperty->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
        hasAlign = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().has_value();
    }

    OffsetF offsetBase = OffsetF(pattern->GetPaddingLeft() + pattern->GetBorderLeft(),
        pattern->GetPaddingTop() + pattern->GetBorderTop());

    auto responseArea = pattern->GetResponseArea();
    auto cleanNodeResponseArea = pattern->GetCleanNodeResponseArea();
    auto unitNodeWidth = 0.0f;
    if (responseArea) {
        int32_t childIndex = frameNode->GetChildIndex(responseArea->GetFrameNode());
        responseArea->Layout(layoutWrapper, childIndex, unitNodeWidth);
    }
    if (cleanNodeResponseArea) {
        int32_t childIndex = frameNode->GetChildIndex(cleanNodeResponseArea->GetFrameNode());
        cleanNodeResponseArea->Layout(layoutWrapper, childIndex, unitNodeWidth);
    }

    UpdateContentPositionParams params = {
        .isRTL = isRTL,
        .offsetBase = offsetBase,
        .size = size,
        .contentSize = contentSize,
        .align = align,
        .responseArea = responseArea,
        .cleanResponseArea = cleanNodeResponseArea
    };
    UpdateContentPosition(params, content);

    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    UpdateTextRectParams updateTextRectParams = {
        .layoutProperty = layoutProperty,
        .pattern = pattern,
        .contentSize = contentSize,
        .isRTL = isRTL,
        .responseArea = responseArea,
        .cleanResponseArea = cleanNodeResponseArea,
        .contentOffset = content->GetRect().GetOffset()
    };
    UpdateTextRect(updateTextRectParams);

    bool isInlineStyle = pattern->IsNormalInlineState();
    if (layoutProperty->GetShowCounterValue(false) && layoutProperty->HasMaxLength() && !isInlineStyle) {
        TextFieldLayoutAlgorithm::CounterLayout(layoutWrapper);
    }
}

void TextInputLayoutAlgorithm::UpdateContentPosition(const UpdateContentPositionParams &params,
    const std::unique_ptr<GeometryProperty> &content)
{
    OffsetF contentOffset =
        params.offsetBase + Alignment::GetAlignPosition(params.size, params.contentSize, params.align);
    auto offsetBaseX = params.offsetBase.GetX();
    if (params.isRTL) {
        if (params.responseArea) {
            offsetBaseX += params.responseArea->GetAreaRect().Width();
        }
        if (params.cleanResponseArea) {
            offsetBaseX += params.cleanResponseArea->GetAreaRect().Width();
        }
    }
    content->SetOffset(OffsetF(offsetBaseX, contentOffset.GetY()));
}

void TextInputLayoutAlgorithm::UpdateTextRect(const UpdateTextRectParams& params)
{
    if (LessOrEqual(textRect_.Width(), params.contentSize.Width())) {
        float textRectOffsetX = 0.0f;
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            textRectOffsetX = params.pattern->GetPaddingLeft();
        } else {
            textRectOffsetX = params.pattern->GetPaddingLeft() + params.pattern->GetBorderLeft();
        }
        bool isEmptyTextEditValue = params.pattern->GetTextValue().empty();
        bool isInlineStyle = params.pattern->IsNormalInlineState();
        if (!isEmptyTextEditValue && !isInlineStyle) {
            TextAlign textAlign = params.layoutProperty->GetTextAlignValue(TextAlign::START);
            params.pattern->CheckTextAlignByDirection(textAlign, direction_);
        }
        if (params.isRTL) {
            if (params.responseArea) {
                RectF responseAreaRect = params.responseArea->GetAreaRect();
                textRectOffsetX += responseAreaRect.Width();
            }
            if (params.cleanResponseArea) {
                RectF cleanResponseAreaRect = params.cleanResponseArea->GetAreaRect();
                textRectOffsetX += cleanResponseAreaRect.Width();
            }
            textRect_.SetOffset(OffsetF(textRectOffsetX, params.contentOffset.GetY()));
        } else {
            textRect_.SetOffset(OffsetF(textRectOffsetX, params.contentOffset.GetY()));
        }
    } else {
        textRect_.SetOffset({ params.pattern->GetTextRect().GetOffset().GetX(), params.contentOffset.GetY() });
    }
}

float TextInputLayoutAlgorithm::GetDefaultHeightByType(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    return static_cast<float>(textFieldTheme->GetContentHeight().ConvertToPx());
}

bool TextInputLayoutAlgorithm::CreateParagraphEx(const TextStyle& textStyle, const std::string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto isInlineStyle = pattern->IsNormalInlineState();
    auto isPasswordType = pattern->IsInPasswordMode();
    auto disableTextAlign = false;
    auto fontSize = pattern->FontSizeConvertToPx(textStyle.GetFontSize());
    auto paragraphData = CreateParagraphData { disableTextAlign, fontSize };

    if (pattern->IsDragging() && !showPlaceHolder_ && !isInlineStyle) {
        CreateParagraph(textStyle, pattern->GetDragContents(), content,
            isPasswordType && pattern->GetTextObscured() && !showPlaceHolder_, paragraphData);
    } else {
        CreateParagraph(textStyle, content, isPasswordType && pattern->GetTextObscured() && !showPlaceHolder_,
            pattern->GetNakedCharPosition(), paragraphData);
    }
    return true;
}

LayoutConstraintF TextInputLayoutAlgorithm::BuildLayoutConstraintWithoutResponseArea(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, contentConstraint);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, contentConstraint);

    auto responseArea = pattern->GetResponseArea();
    auto cleanNodeResponseArea = pattern->GetCleanNodeResponseArea();
    float childWidth = 0.0f;
    if (responseArea) {
        auto childIndex = frameNode->GetChildIndex(responseArea->GetFrameNode());
        childWidth += responseArea->Measure(layoutWrapper, childIndex).Width();
    }
    if (cleanNodeResponseArea) {
        auto childIndex = frameNode->GetChildIndex(cleanNodeResponseArea->GetFrameNode());
        childWidth += cleanNodeResponseArea->Measure(layoutWrapper, childIndex).Width();
    }

    auto newLayoutConstraint = contentConstraint;
    newLayoutConstraint.maxSize.SetWidth(std::max(newLayoutConstraint.maxSize.Width() - childWidth, 0.0f));
    newLayoutConstraint.minSize.SetWidth(std::max(newLayoutConstraint.minSize.Width() - childWidth, 0.0f));
    if (newLayoutConstraint.selfIdealSize.Width()) {
        newLayoutConstraint.selfIdealSize.SetWidth(newLayoutConstraint.selfIdealSize.Width().value() - childWidth);
    }
    return newLayoutConstraint;
}
} // namespace OHOS::Ace::NG
