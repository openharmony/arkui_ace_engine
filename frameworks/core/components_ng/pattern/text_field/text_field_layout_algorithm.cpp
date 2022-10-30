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

#include <algorithm>
#include <optional>
#include <unicode/uchar.h>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/font/constants_converter.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
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
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    float contentHeight = 0.0f;
    if (content) {
        auto contentSize = content->GetRect().GetSize();
        contentHeight = contentSize.Height();
    }
    if (!frameSize.Height().has_value()) {
        frameSize.SetHeight(std::max(GetTextFieldDefaultHeight(), contentHeight));
    }
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
    if (!textFieldLayoutProperty->GetValueValue("").empty()) {
        UpdateTextStyle(textFieldLayoutProperty, textFieldTheme, textStyle);
        textContent = textFieldLayoutProperty->GetValueValue("");
    } else {
        UpdatePlaceholderTextStyle(textFieldLayoutProperty, textFieldTheme, textStyle);
        textContent = textFieldLayoutProperty->GetPlaceholderValue("");
    }
    CreateParagraph(textStyle, textContent);

    float imageSize = 0.0f;
    auto showPasswordIcon = textFieldLayoutProperty->GetShowPasswordIcon().value_or(false);
    imageSize = showPasswordIcon ? GetTextFieldDefaultImageHeight() : 0.0f;
    if (contentConstraint.selfIdealSize.Height()) {
        imageSize = std::min(imageSize, contentConstraint.selfIdealSize.Height().value());
    }
    auto horizontalPaddingSum = pattern->GetHorizontalPaddingSum();
    if (textStyle.GetMaxLines() == 1) {
        // for text input case, need to measure in one line without constraint.
        paragraph_->Layout(Infinity<float>());
    } else {
        // for text area, max width is content width without password icon
        paragraph_->Layout(contentConstraint.maxSize.Width() - horizontalPaddingSum);
    }
    auto paragraphNewWidth = static_cast<float>(paragraph_->GetMaxIntrinsicWidth());
    if (!NearEqual(paragraphNewWidth, paragraph_->GetMaxWidth())) {
        paragraph_->Layout(std::ceil(paragraphNewWidth));
    }
    auto height = std::min(static_cast<float>(paragraph_->GetHeight()), contentConstraint.maxSize.Height());
    // check password image size.
    if (!showPasswordIcon) {
        textRect_.SetSize(SizeF(std::min(static_cast<float>(paragraph_->GetLongestLine()),
            contentConstraint.maxSize.Width() - horizontalPaddingSum),
            height));
        imageRect_.SetSize(SizeF());
        auto contentSize = contentConstraint.maxSize;
        MinusPaddingToSize(pattern->GetUtilPadding(), contentSize);
        return SizeF(contentSize.Width(), height);
    }

    float imageHeight = 0.0f;
    imageHeight = GetTextFieldDefaultImageHeight();
    if (contentConstraint.selfIdealSize.Height()) {
        imageHeight = std::min(imageHeight, contentConstraint.selfIdealSize.Height().value());
    }
    if (textStyle.GetMaxLines() > 1) {
        // for textArea, need to delete imageWidth and remeasure.
        paragraph_->Layout(contentConstraint.maxSize.Width() - imageHeight);
        textRect_.SetSize(SizeF(contentConstraint.maxSize.Width(), contentConstraint.maxSize.Height()));
        imageRect_.SetSize(SizeF(0.0f, 0.0f));
        return SizeF(contentConstraint.maxSize.Width(), imageHeight);
    }
    height = std::min(static_cast<float>(paragraph_->GetHeight()), contentConstraint.maxSize.Height());
    textRect_.SetSize(SizeF(std::min(static_cast<float>(paragraph_->GetLongestLine()),
                                contentConstraint.maxSize.Width() - horizontalPaddingSum - imageSize),
        static_cast<float>(height)));
    imageRect_.SetSize(SizeF(imageSize, imageSize));
    return SizeF(contentConstraint.maxSize.Width(), std::max(imageSize, height));
}

void TextFieldLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto frameNode = layoutWrapper->GetHostNode();
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto left = pattern->GetPaddingLeft();
    auto align = Alignment::CENTER;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    // Update content position.
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentSize = content->GetRect().GetSize();
    auto contentOffset = Alignment::GetAlignPosition(size, contentSize, align);
    content->SetOffset(OffsetF(left, contentOffset.GetY()));
    // update text rect.
    auto textOffset = Alignment::GetAlignPosition(contentSize, textRect_.GetSize(), Alignment::CENTER_LEFT);
    // adjust text rect to the basic padding first
    textRect_.SetOffset(OffsetF(left, textOffset.GetY()));
    // update image rect.
    if (!imageRect_.IsEmpty()) {
        auto imageOffset = Alignment::GetAlignPosition(contentSize, imageRect_.GetSize(), Alignment::CENTER_RIGHT);
        imageRect_.SetOffset(imageOffset);
    }
}

void TextFieldLayoutAlgorithm::UpdateTextStyle(
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme, TextStyle& textStyle)
{
    const std::vector<std::string> defaultFontFamily = { "sans-serif" };
    textStyle.SetFontFamilies(layoutProperty->GetFontFamilyValue(defaultFontFamily));
    textStyle.SetFontSize(layoutProperty->GetFontSizeValue(theme ? theme->GetFontSize() : textStyle.GetFontSize()));
    textStyle.SetFontWeight(
        layoutProperty->GetFontWeightValue(theme ? theme->GetFontWeight() : textStyle.GetFontWeight()));
    textStyle.SetTextColor(layoutProperty->GetTextColorValue(theme ? theme->GetTextColor() : textStyle.GetTextColor()));
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

void TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyle(
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme, TextStyle& textStyle)
{
    const std::vector<std::string> defaultFontFamily = { "sans-serif" };
    textStyle.SetFontFamilies(layoutProperty->GetFontFamilyValue(defaultFontFamily));
    textStyle.SetFontSize(
        layoutProperty->GetPlaceholderFontSizeValue(theme ? theme->GetFontSize() : textStyle.GetFontSize()));
    textStyle.SetFontWeight(
        layoutProperty->GetPlaceholderFontWeightValue(theme ? theme->GetFontWeight() : textStyle.GetFontWeight()));
    textStyle.SetTextColor(
        layoutProperty->GetPlaceholderTextColorValue(theme ? theme->GetPlaceholderColor() : textStyle.GetTextColor()));
    if (layoutProperty->HasPlaceholderMaxLines()) {
        textStyle.SetMaxLines(layoutProperty->GetPlaceholderMaxLines().value());
    }
    if (layoutProperty->HasPlaceholderItalicFontStyle()) {
        textStyle.SetFontStyle(layoutProperty->GetPlaceholderItalicFontStyle().value());
    }
    if (layoutProperty->HasPlaceholderTextAlign()) {
        textStyle.SetTextAlign(layoutProperty->GetPlaceholderTextAlign().value());
    }
}

void TextFieldLayoutAlgorithm::CreateParagraph(const TextStyle& textStyle, std::string content)
{
    RSParagraphStyle paraStyle;
    paraStyle.textDirection_ = ToRSTextDirection(GetTextDirection(content));
    paraStyle.textAlign_ = ToRSTextAlign(textStyle.GetTextAlign());
    paraStyle.maxLines_ = textStyle.GetMaxLines();
    paraStyle.locale_ = Localization::GetInstance()->GetFontLocale();
    paraStyle.wordBreakType_ = ToRSWordBreakType(textStyle.GetWordBreak());
    if (textStyle.GetTextOverflow() == TextOverflow::ELLIPSIS) {
        paraStyle.ellipsis_ = RSParagraphStyle::ELLIPSIS;
    }

    auto builder = RSParagraphBuilder::CreateRosenBuilder(paraStyle, RSFontCollection::GetInstance(false));
    builder->PushStyle(ToRSTextStyle(PipelineContext::GetCurrentContext(), textStyle));
    StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    builder->AddText(StringUtils::Str8ToStr16(content));
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
