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
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/auto_fill_controller.h"
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
    std::replace(textContent_.begin(), textContent_.end(), u'\n', u' ');

    auto isInlineStyle = pattern->IsNormalInlineState();
    isInlineFocus_ = isInlineStyle && pattern->HasFocus();

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
        auto fontSize = textStyle.GetFontSize().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        auto paragraphData = CreateParagraphData { disableTextAlign, fontSize };
        CreateInlineParagraph(textStyle, textContent_, false, pattern->GetNakedCharPosition(), paragraphData);
        return InlineMeasureContent(contentConstraintWithoutResponseArea, layoutWrapper);
    } else if (showPlaceHolder_) {
        return PlaceHolderMeasureContent(contentConstraintWithoutResponseArea, layoutWrapper, 0);
    } else {
        return TextInputMeasureContent(contentConstraintWithoutResponseArea, layoutWrapper, 0);
    }
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
    MeasureAutoFillIcon(layoutWrapper);
    MeasureCounterWithPolicy(layoutWrapper, responseAreaWidth + pattern->GetHorizontalPaddingAndBorderSum());
}

void TextInputLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetFrameSize() -
                SizeF(pattern->GetHorizontalPaddingAndBorderSum(), pattern->GetVerticalPaddingAndBorderSum());
    const auto& content = geometryNode->GetContent();
    CHECK_NULL_VOID(content);
    SizeT<float> contentSize = content->GetRect().GetSize();
    auto layoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    PipelineContext* context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    parentGlobalOffset_ = frameNode->GetPaintRectOffset(false, true) - context->GetRootRect().GetOffset();
    Alignment align = Alignment::CENTER;
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (layoutProperty->GetPositionProperty()) {
        align = layoutProperty->GetPositionProperty()->GetAlignment().value_or(align);
    }
    auto border = pattern->GetBorderWidthProperty();
    OffsetF offsetBase = OffsetF(pattern->GetPaddingLeft() + pattern->GetBorderLeft(border),
        pattern->GetPaddingTop() + pattern->GetBorderTop(border));

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
    if (pattern->IsShowError()) {
        TextFieldLayoutAlgorithm::ErrorLayout(layoutWrapper);
    }
    LayoutAutoFillIcon(layoutWrapper);
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
            auto border = params.pattern->GetBorderWidthProperty();
            textRectOffsetX = params.pattern->GetPaddingLeft() + params.pattern->GetBorderLeft(border);
        }
        bool isEmptyTextEditValue = params.pattern->GetTextUtf16Value().empty();
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

bool TextInputLayoutAlgorithm::CreateParagraphEx(const TextStyle& textStyle, const std::u16string& content,
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
    auto fontSize =
        textStyle.GetFontSize().ConvertToPxDistribute(textStyle.GetMinFontScale(), textStyle.GetMaxFontScale());
    auto paragraphData = CreateParagraphData { disableTextAlign, fontSize };
    auto autofillController = pattern->GetAutoFillController();
    CHECK_NULL_RETURN(autofillController, false);
    auto autoFillAnimationStatus = autofillController->GetAutoFillAnimationStatus();
    if (autoFillAnimationStatus != AutoFillAnimationStatus::INIT) {
        CreateAutoFillParagraph(textStyle, content, isPasswordType && pattern->GetTextObscured(),
            pattern->GetNakedCharPosition(), paragraphData);
        autofillController->SetAutoFillOriginTextColor(textStyle.GetTextColor());
    } else {
        if (pattern->IsDragging() && !showPlaceHolder_ && !isInlineStyle) {
            CreateParagraph(textStyle, pattern->GetDragContents(), content,
                isPasswordType && pattern->GetTextObscured() && !showPlaceHolder_, paragraphData);
        } else {
            CreateParagraph(textStyle, content, isPasswordType && pattern->GetTextObscured() && !showPlaceHolder_,
                pattern->GetNakedCharPosition(), paragraphData);
        }
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

void TextInputLayoutAlgorithm::MeasureAutoFillIcon(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto textFieldlayoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(textFieldlayoutProperty);
    auto autofillController = textFieldPattern->GetAutoFillController();
    CHECK_NULL_VOID(autofillController);
    auto weakAutoFillIcon = autofillController->GetAutoFillIconNode();
    auto autoFillIcon =  weakAutoFillIcon.Upgrade();
    CHECK_NULL_VOID(autoFillIcon);
    auto autoFillIconIndex = frameNode->GetChildIndex(autoFillIcon);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(autoFillIconIndex);
    CHECK_NULL_VOID(childWrapper);
    auto iconGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(iconGeometryNode);
    auto iconLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(iconLayoutProperty);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto iconSize = iconLayoutProperty->GetFontSize().value_or(textFieldTheme->GetAutoFillIconSize());
    auto iconHeight = iconSize.ConvertToPx();
    CalcSize iconCalcSize;
    iconCalcSize.SetWidth(CalcLength(iconHeight));
    iconCalcSize.SetHeight(CalcLength(iconHeight));
    iconLayoutProperty->UpdateUserDefinedIdealSize(iconCalcSize);
    auto childLayoutConstraint = textFieldlayoutProperty->CreateChildConstraint();
    childWrapper->Measure(childLayoutConstraint);
    autoFillIconSizeMeasure_ = iconGeometryNode->GetFrameSize();
}

void TextInputLayoutAlgorithm::LayoutAutoFillIcon(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto textFieldlayoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(textFieldlayoutProperty);
    auto isRTL = textFieldlayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto textFieldGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);
    auto textFieldSize = textFieldGeometryNode->GetFrameSize();
    auto textFieldFrameWidth = textFieldSize.Width();
    auto textFieldFrameHeight = textFieldSize.Height();
    auto autofillController = textFieldPattern->GetAutoFillController();
    CHECK_NULL_VOID(autofillController);
    auto weakAutoFillIcon = autofillController->GetAutoFillIconNode();
    auto autoFillIcon =  weakAutoFillIcon.Upgrade();
    CHECK_NULL_VOID(autoFillIcon);
    auto autoFillIconIndex = frameNode->GetChildIndex(autoFillIcon);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(autoFillIconIndex);
    CHECK_NULL_VOID(childWrapper);
    auto iconGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(iconGeometryNode);
    auto iconFrameWidth = autoFillIconSizeMeasure_.Width();
    auto iconFrameHeight = autoFillIconSizeMeasure_.Height();

    auto padding = textFieldlayoutProperty->CreatePaddingAndBorder();
    auto leftOffset = padding.left.value_or(0.0f);
    auto rightOffset = padding.right.value_or(0.0f);
    float iconHorizontalOffset = isRTL ? textFieldFrameWidth - iconFrameWidth - rightOffset : leftOffset;
    // Vertically center-align text
    auto half = 2.0f;
    float iconVerticalOffset = textRect_.Top() + textRect_.Height() / half - autoFillIconSizeMeasure_.Height() / half;
    // Vertically center-align textinput
    if (GreatOrEqual(iconFrameHeight, textFieldFrameHeight)) {
        iconVerticalOffset = -(iconFrameHeight - textFieldFrameHeight) / half;
    } else if (LessNotEqual(iconVerticalOffset, 0.0f)) {
        iconVerticalOffset = 0.0f;
    } else if (GreatNotEqual(iconVerticalOffset + iconFrameHeight, textFieldFrameHeight)) {
        iconVerticalOffset = iconVerticalOffset - (iconVerticalOffset + iconFrameHeight - textFieldFrameHeight);
    }

    OffsetF iconOffset(iconHorizontalOffset, iconVerticalOffset);
    iconGeometryNode->SetMarginFrameOffset(iconOffset);
    childWrapper->Layout();
}

void TextInputLayoutAlgorithm::MeasureCounterWithPolicy(LayoutWrapper* layoutWrapper, float nonContentWidth)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto widthLayoutPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, true);
    if (widthLayoutPolicy != LayoutCalPolicy::NO_MATCH) {
        auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
        auto counterWidth = frameSize.Width() - nonContentWidth;
        CounterNodeMeasure(counterWidth, layoutWrapper);
    }
}
} // namespace OHOS::Ace::NG
