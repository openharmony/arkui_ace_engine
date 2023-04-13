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

#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"

#include <unicode/uchar.h>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/font/constants_converter.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/font_collection.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void TextFieldLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    OptionalSizeF frameSize =
        CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT_MAIN_AXIS);
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
    if (pattern->IsTextArea()) {
        if (!layoutConstraint->selfIdealSize.Width().has_value()) {
            frameSize.SetWidth(contentWidth + pattern->GetHorizontalPaddingSum());
        }
        if (!frameSize.Height().has_value()) {
            frameSize.SetHeight(contentHeight + pattern->GetVerticalPaddingSum());
        }
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
        frameRect_ =
            RectF(layoutWrapper->GetGeometryNode()->GetFrameOffset(), layoutWrapper->GetGeometryNode()->GetFrameSize());
        return;
    }
    if (!frameSize.Height().has_value()) {
        frameSize.SetHeight(
            std::min(layoutConstraint->maxSize.Height(), contentHeight + pattern->GetVerticalPaddingSum()));
    }
    auto textfieldLayoutProperty = AceType::DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textfieldLayoutProperty);
    if (textfieldLayoutProperty->GetWidthAutoValue(false)) {
        frameSize.SetWidth(contentWidth + pattern->GetHorizontalPaddingSum());
    }
    frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
    frameRect_ =
        RectF(layoutWrapper->GetGeometryNode()->GetFrameOffset(), layoutWrapper->GetGeometryNode()->GetFrameSize());
}

std::optional<SizeF> TextFieldLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto textFieldLayoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textFieldLayoutProperty, std::nullopt);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, std::nullopt);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    TextStyle textStyle;
    std::string textContent;
    bool showPlaceHolder = false;
    auto idealWidth = contentConstraint.selfIdealSize.Width().value_or(contentConstraint.maxSize.Width());
    auto idealHeight = contentConstraint.selfIdealSize.Height().value_or(contentConstraint.maxSize.Height());
    if (!textFieldLayoutProperty->GetValueValue("").empty()) {
        UpdateTextStyle(textFieldLayoutProperty, textFieldTheme, textStyle, pattern->IsDisabled());
        textContent = textFieldLayoutProperty->GetValueValue("");
    } else {
        UpdatePlaceholderTextStyle(textFieldLayoutProperty, textFieldTheme, textStyle, pattern->IsDisabled());
        textContent = textFieldLayoutProperty->GetPlaceholderValue("");
        showPlaceHolder = true;
    }
    auto isPasswordType =
        textFieldLayoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD;
    CreateParagraph(textStyle, textContent, isPasswordType && pattern->GetTextObscured() && !showPlaceHolder);
    if (textStyle.GetMaxLines() == 1 && !showPlaceHolder) {
        // for text input case, need to measure in one line without constraint.
        paragraph_->Layout(std::numeric_limits<double>::infinity());
    } else {
        // for text area or placeholder, max width is content width without password icon
        paragraph_->Layout(idealWidth);
    }
    auto paragraphNewWidth = static_cast<float>(paragraph_->GetMaxIntrinsicWidth());
    if (!NearEqual(paragraphNewWidth, paragraph_->GetMaxWidth()) && !pattern->IsTextArea() && !showPlaceHolder) {
        paragraph_->Layout(std::ceil(paragraphNewWidth));
    }
    auto preferredHeight = static_cast<float>(paragraph_->GetHeight());
    if (textContent.empty()) {
        preferredHeight = pattern->PreferredLineHeight();
    }
    if (pattern->IsTextArea()) {
        auto useHeight = static_cast<float>(paragraph_->GetHeight());
        textRect_.SetSize(SizeF(idealWidth, useHeight));
        return SizeF(idealWidth, std::min(idealHeight, useHeight));
    }
    auto showPasswordIcon = textFieldLayoutProperty->GetShowPasswordIcon().value_or(true);
    // check password image size.
    if (!showPasswordIcon || !isPasswordType) {
        textRect_.SetSize(SizeF(static_cast<float>(paragraph_->GetLongestLine()), preferredHeight));
        imageRect_.Reset();
        if (textFieldLayoutProperty->GetWidthAutoValue(false)) {
            if (LessOrEqual(contentConstraint.minSize.Width(), 0.0f)) {
                idealWidth = std::clamp(textRect_.GetSize().Width(), 0.0f, contentConstraint.maxSize.Width());
            } else if (LessOrEqual(textRect_.Width(), 0.0f)) {
                idealWidth = contentConstraint.minSize.Width();
            } else {
                idealWidth =
                    std::clamp(textRect_.Width(), contentConstraint.minSize.Width(), contentConstraint.maxSize.Width());
            }
        }
        return SizeF(idealWidth, std::min(preferredHeight, idealHeight));
    }
    float imageSize = showPasswordIcon ? pattern->GetIconSize() : 0.0f;
    if (contentConstraint.selfIdealSize.Height()) {
        imageSize = std::min(imageSize, contentConstraint.selfIdealSize.Height().value());
    }

    if (textStyle.GetMaxLines() > 1 || pattern->IsTextArea()) {
        // for textArea, need to delete imageWidth and remeasure.
        paragraph_->Layout(idealWidth - imageSize);
        textRect_.SetSize(SizeF(static_cast<float>(paragraph_->GetLongestLine()), preferredHeight));
        imageRect_.SetSize(SizeF(0.0f, 0.0f));
        return SizeF(idealWidth, imageSize);
    }
    imageRect_.SetSize(SizeF(imageSize, imageSize));
    if (pattern->GetTextObscured() && pattern->GetHidePasswordIconCtx()) {
        pattern->GetHidePasswordIconCtx()->MakeCanvasImage(imageRect_.GetSize(), true, ImageFit::NONE);
    } else if (!pattern->GetTextObscured() && pattern->GetShowPasswordIconCtx()) {
        pattern->GetShowPasswordIconCtx()->MakeCanvasImage(imageRect_.GetSize(), true, ImageFit::NONE);
    }
    preferredHeight = std::min(static_cast<float>(paragraph_->GetHeight()), idealHeight);
    textRect_.SetSize(SizeF(static_cast<float>(paragraph_->GetLongestLine()), static_cast<float>(preferredHeight)));
    return SizeF(idealWidth - imageSize, std::min(idealHeight, preferredHeight));
}

void TextFieldLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
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
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    // Update content position.
    OffsetF contentOffset;
    if (pattern->IsTextArea()) {
        content->SetOffset(pattern->GetUtilPadding().Offset());
        textRect_.SetOffset(pattern->GetTextRect().GetOffset());
        return;
    }
    contentOffset = Alignment::GetAlignPosition(size, contentSize, align);
    content->SetOffset(OffsetF(pattern->GetPaddingLeft(), contentOffset.GetY()));
    // if handler is moving, no need to adjust text rect in pattern
    auto isHandleMoving = pattern->GetCaretUpdateType() == CaretUpdateType::HANDLE_MOVE ||
                          pattern->GetCaretUpdateType() == CaretUpdateType::HANDLE_MOVE_DONE;
    auto needForceCheck = pattern->GetCaretUpdateType() == CaretUpdateType::INPUT ||
                          pattern->GetCaretUpdateType() == CaretUpdateType::DEL;
    auto needToKeepTextRect = isHandleMoving || pattern->GetMouseStatus() == MouseStatus::MOVE || !needForceCheck ||
                              pattern->GetIsMousePressed();
    if (needToKeepTextRect) {
        textRect_.SetOffset(pattern->GetTextRect().GetOffset());
    }
    if (!pattern->IsTextArea() && !needToKeepTextRect) {
        auto textOffset = Alignment::GetAlignPosition(contentSize, textRect_.GetSize(), Alignment::CENTER_LEFT);
        // adjust text rect to the basic padding
        auto textRectOffsetX = pattern->GetPaddingLeft();
        if (!pattern->GetTextEditingValue().text.empty()) {
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
        textRect_.SetOffset(OffsetF(textRectOffsetX, textOffset.GetY()));
    }
    // update image rect.
    if (!imageRect_.IsEmpty()) {
        auto imageOffset = Alignment::GetAlignPosition(size, imageRect_.GetSize(), Alignment::CENTER_RIGHT);
        imageOffset.AddX(-pattern->GetIconRightOffset());
        imageRect_.SetOffset(imageOffset);
    }
}

void TextFieldLayoutAlgorithm::UpdateTextStyle(const RefPtr<TextFieldLayoutProperty>& layoutProperty,
    const RefPtr<TextFieldTheme>& theme, TextStyle& textStyle, bool isDisabled)
{
    const std::vector<std::string> defaultFontFamily = { "sans-serif" };
    textStyle.SetFontFamilies(layoutProperty->GetFontFamilyValue(defaultFontFamily));

    Dimension fontSize;
    if (layoutProperty->HasFontSize() && layoutProperty->GetFontSizeValue(Dimension()).IsNonNegative()) {
        fontSize = layoutProperty->GetFontSizeValue(Dimension());
    } else {
        fontSize = theme ? theme->GetFontSize() : textStyle.GetFontSize();
    }
    textStyle.SetFontSize(fontSize);
    textStyle.SetTextAlign(layoutProperty->GetTextAlignValue(TextAlign::START));
    textStyle.SetFontWeight(
        layoutProperty->GetFontWeightValue(theme ? theme->GetFontWeight() : textStyle.GetFontWeight()));
    if (isDisabled) {
        textStyle.SetTextColor(theme ? theme->GetDisableTextColor() : textStyle.GetTextColor());
    } else {
        textStyle.SetTextColor(
            layoutProperty->GetTextColorValue(theme ? theme->GetTextColor() : textStyle.GetTextColor()));
    }
    if (layoutProperty->GetMaxLines()) {
        textStyle.SetMaxLines(layoutProperty->GetMaxLines().value());
    }
    if (layoutProperty->HasItalicFontStyle()) {
        textStyle.SetFontStyle(layoutProperty->GetItalicFontStyle().value());
    }
    if (layoutProperty->HasTextAlign()) {
        textStyle.SetTextAlign(layoutProperty->GetTextAlign().value());
    }
}

void TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyle(const RefPtr<TextFieldLayoutProperty>& layoutProperty,
    const RefPtr<TextFieldTheme>& theme, TextStyle& textStyle, bool isDisabled)
{
    const std::vector<std::string> defaultFontFamily = { "sans-serif" };
    textStyle.SetFontFamilies(layoutProperty->GetFontFamilyValue(defaultFontFamily));
    Dimension fontSize;
    if (layoutProperty->HasPlaceholderFontSize() &&
        layoutProperty->GetPlaceholderFontSizeValue(Dimension()).IsNonNegative()) {
        fontSize = layoutProperty->GetPlaceholderFontSizeValue(Dimension());
    } else {
        fontSize = theme ? theme->GetFontSize() : textStyle.GetFontSize();
    }
    textStyle.SetFontSize(fontSize);
    textStyle.SetFontWeight(
        layoutProperty->GetPlaceholderFontWeightValue(theme ? theme->GetFontWeight() : textStyle.GetFontWeight()));
    if (isDisabled) {
        textStyle.SetTextColor(theme ? theme->GetDisableTextColor() : textStyle.GetTextColor());
    } else {
        textStyle.SetTextColor(layoutProperty->GetPlaceholderTextColorValue(
            theme ? theme->GetPlaceholderColor() : textStyle.GetTextColor()));
    }
    if (layoutProperty->HasPlaceholderMaxLines()) {
        textStyle.SetMaxLines(layoutProperty->GetPlaceholderMaxLines().value());
    }
    if (layoutProperty->HasPlaceholderItalicFontStyle()) {
        textStyle.SetFontStyle(layoutProperty->GetPlaceholderItalicFontStyle().value());
    }
    if (layoutProperty->HasPlaceholderTextAlign()) {
        textStyle.SetTextAlign(layoutProperty->GetPlaceholderTextAlign().value());
    }
    textStyle.SetTextOverflow(TextOverflow::ELLIPSIS);
    textStyle.SetTextAlign(layoutProperty->GetTextAlignValue(TextAlign::START));
}

void TextFieldLayoutAlgorithm::CreateParagraph(const TextStyle& textStyle, std::string content, bool needObscureText)
{
    RSParagraphStyle paraStyle;
    paraStyle.textDirection_ = ToRSTextDirection(GetTextDirection(content));
    paraStyle.textAlign_ = ToRSTextAlign(textStyle.GetTextAlign());
    paraStyle.maxLines_ = textStyle.GetMaxLines();
    paraStyle.locale_ = Localization::GetInstance()->GetFontLocale();
    paraStyle.wordBreakType_ = ToRSWordBreakType(textStyle.GetWordBreak());
    paraStyle.fontSize_ = textStyle.GetFontSize().ConvertToPx();
    paraStyle.fontFamily_ = textStyle.GetFontFamilies().at(0);
    if (textStyle.GetTextOverflow() == TextOverflow::ELLIPSIS) {
        paraStyle.ellipsis_ = StringUtils::Str8ToStr16(StringUtils::ELLIPSIS);
    }
    auto builder = RSParagraphBuilder::CreateRosenBuilder(paraStyle, RSFontCollection::GetInstance(false));
    builder->PushStyle(ToRSTextStyle(PipelineContext::GetCurrentContext(), textStyle));
    StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    if (!content.empty() && needObscureText) {
        builder->AddText(
            TextFieldPattern::CreateObscuredText(static_cast<int32_t>(StringUtils::ToWstring(content).length())));
    } else {
        builder->AddText(StringUtils::Str8ToStr16(content));
    }
    builder->Pop();

    auto paragraph = builder->Build();
    paragraph_.reset(paragraph.release());
}

TextDirection TextFieldLayoutAlgorithm::GetTextDirection(const std::string& content)
{
    TextDirection textDirection = TextDirection::LTR;
    auto showingTextForWString = StringUtils::ToWstring(content);
    for (const auto& charOfShowingText : showingTextForWString) {
        if (u_charDirection(charOfShowingText) == UCharDirection::U_LEFT_TO_RIGHT) {
            textDirection = TextDirection::LTR;
        } else if (u_charDirection(charOfShowingText) == UCharDirection::U_RIGHT_TO_LEFT) {
            textDirection = TextDirection::RTL;
        } else if (u_charDirection(charOfShowingText) == UCharDirection::U_RIGHT_TO_LEFT_ARABIC) {
            textDirection = TextDirection::RTL;
        }
    }
    return textDirection;
}

const std::shared_ptr<RSParagraph>& TextFieldLayoutAlgorithm::GetParagraph()
{
    return paragraph_;
}

float TextFieldLayoutAlgorithm::GetTextFieldDefaultHeight()
{
    const auto defaultHeight = 40.0_vp;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, defaultHeight.ConvertToPx());
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, defaultHeight.ConvertToPx());
    auto height = textFieldTheme->GetHeight();
    return static_cast<float>(height.ConvertToPx());
}

float TextFieldLayoutAlgorithm::GetTextFieldDefaultImageHeight()
{
    const auto defaultHeight = 40.0_vp;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, defaultHeight.ConvertToPx());
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, defaultHeight.ConvertToPx());
    auto height = textFieldTheme->GetIconHotZoneSize();
    return static_cast<float>(height.ConvertToPx());
}

} // namespace OHOS::Ace::NG
