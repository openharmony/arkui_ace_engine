/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/font_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_layout_adapter.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_content_modifier.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PARAGRAPH_SAVE_BOUNDARY = 1.0f;
} // namespace
void TextFieldLayoutAlgorithm::ConstructTextStyles(
    const RefPtr<FrameNode>& frameNode, TextStyle& textStyle, std::string& textContent, bool& showPlaceHolder)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto isInlineStyle = pattern->IsNormalInlineState();

    if (!textFieldLayoutProperty->GetValueValue("").empty()) {
        UpdateTextStyle(frameNode, textFieldLayoutProperty, textFieldTheme, textStyle, pattern->IsDisabled());
        textContent = textFieldLayoutProperty->GetValueValue("");
        if (!pattern->IsTextArea() && isInlineStyle) {
            textStyle.SetTextOverflow(TextOverflow::ELLIPSIS);
        }
    } else {
        UpdatePlaceholderTextStyle(
            frameNode, textFieldLayoutProperty, textFieldTheme, textStyle, pattern->IsDisabled());
        textContent = textFieldLayoutProperty->GetPlaceholderValue("");
        showPlaceHolder = true;
    }

    // use for modifier.
    auto contentModifier = pattern->GetContentModifier();
    if (contentModifier) {
        SetPropertyToModifier(textStyle, contentModifier);
        contentModifier->ModifyTextStyle(textStyle);
        contentModifier->SetFontReady(false);
    }
}

SizeF TextFieldLayoutAlgorithm::CalculateConstraintSize(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // constraint size.
    auto idealWidth = contentConstraint.selfIdealSize.Width().value_or(contentConstraint.maxSize.Width());
    auto idealHeight = contentConstraint.selfIdealSize.Height().value_or(contentConstraint.maxSize.Height());
    auto idealSize = SizeF { idealWidth, idealHeight };
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        idealSize.UpdateSizeWhenSmaller(contentConstraint.maxSize);
    } else {
        auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(static_cast<OptionalSize<float>>(idealSize),
            layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
            layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
        idealSize.UpdateSizeWhenSmaller(finalSize.ConvertToSizeT());
    }
    idealWidth = idealSize.Width();
    idealHeight = idealSize.Height();
    return SizeF { idealWidth, idealHeight };
}

std::optional<SizeF> TextFieldLayoutAlgorithm::InlineMeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, const SizeF& idealSize)
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

    if (pattern->IsFocus()) {
        auto safeBoundary = textFieldTheme->GetInlineBorderWidth().ConvertToPx() * 2;
        paragraph_->Layout(idealSize.Width() - safeBoundary - PARAGRAPH_SAVE_BOUNDARY);
        paragraph_->Layout(std::ceil(paragraph_->GetLongestLine()));
    } else {
        paragraph_->Layout(idealSize.Width());
    }
    textRect_.SetSize(SizeF(paragraph_->GetLongestLine(), paragraph_->GetHeight()));
    pattern->SetSingleLineHeight(paragraph_->GetHeight() / paragraph_->GetLineCount());

    auto inlineIdealHieght = idealSize.Height();
    if (pattern->IsFocus()) {
        // The maximum height of the inline mode defaults to a maximum of three rows.
        inlineIdealHieght =
            pattern->GetSingleLineHeight() * textFieldLayoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE);
    }

    return SizeF(
        paragraph_->GetMaxWidth(), std::min(inlineIdealHieght, std::max(preferredHeight_, paragraph_->GetHeight())));
}

SizeF TextFieldLayoutAlgorithm::PlaceHolderMeasureContent(const SizeF& idealSize, float imageWidth)
{
    paragraph_->Layout(idealSize.Width() - imageWidth);
    textRect_.SetSize(SizeF(paragraph_->GetLongestLine(), paragraph_->GetHeight()));

    auto contentWidth = idealSize.Width() - imageWidth;
    if (autoWidth_) {
        contentWidth = std::min(contentWidth, paragraph_->GetLongestLine());
    }
    return SizeF(contentWidth, std::min(idealSize.Height(), std::max(preferredHeight_, paragraph_->GetHeight())));
}

SizeF TextFieldLayoutAlgorithm::TextAreaMeasureContent(const SizeF& idealSize)
{
    paragraph_->Layout(idealSize.Width());
    textRect_.SetSize(SizeF(idealSize.Width(), paragraph_->GetHeight()));
    return SizeF(idealSize.Width(), std::min(idealSize.Height(), std::max(preferredHeight_, paragraph_->GetHeight())));
}

SizeF TextFieldLayoutAlgorithm::TextInputMeasureConetnt(const SizeF& idealSize, float imageWidth)
{
    paragraph_->Layout(std::numeric_limits<double>::infinity());
    paragraph_->Layout(std::ceil(paragraph_->GetLongestLine()));
    textRect_.SetSize(SizeF(static_cast<float>(paragraph_->GetLongestLine()), paragraph_->GetHeight()));
    auto contentWidth = idealSize.Width() - imageWidth;
    if (autoWidth_) {
        contentWidth = std::min(contentWidth, paragraph_->GetLongestLine());
    }
    return SizeF(contentWidth, std::min(idealSize.Height(), std::max(preferredHeight_, paragraph_->GetHeight())));
}

void TextFieldLayoutAlgorithm::ErrorTextMeasureContent(const std::string& content, const RefPtr<TextFieldTheme>& theme)
{
    // errorParagraph  Layout.
    CreateErrorParagraph(content, theme);
    if (errorParagraph_) {
        errorParagraph_->Layout(std::numeric_limits<double>::infinity());
    }
}

void TextFieldLayoutAlgorithm::UpdateTextStyle(const RefPtr<FrameNode>& frameNode,
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme, TextStyle& textStyle,
    bool isDisabled)
{
    const std::vector<std::string> defaultFontFamily = { "sans-serif" };
    textStyle.SetFontFamilies(layoutProperty->GetFontFamilyValue(defaultFontFamily));
    FontRegisterCallback(frameNode, textStyle.GetFontFamilies());

    Dimension fontSize;
    if (layoutProperty->HasFontSize() && layoutProperty->GetFontSize().value_or(Dimension()).IsNonNegative()) {
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
        if (layoutProperty->GetShowUnderlineValue(false) &&
            layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::UNSPECIFIED) {
            textStyle.SetTextColor(theme ? theme->GetTextColorDisable() : textStyle.GetTextColor());
        }
    } else {
        auto renderContext = frameNode->GetRenderContext();
        if (renderContext->HasForegroundColor()) {
            textStyle.SetTextColor(renderContext->GetForegroundColor().value());
        } else if (renderContext->HasForegroundColorStrategy()) {
            textStyle.SetTextColor(Color::BLACK);
        } else {
            textStyle.SetTextColor(
                layoutProperty->GetTextColorValue(theme ? theme->GetTextColor() : textStyle.GetTextColor()));
        }
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

void TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyle(const RefPtr<FrameNode>& frameNode,
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme, TextStyle& textStyle,
    bool isDisabled)
{
    const std::vector<std::string> defaultFontFamily = { "sans-serif" };
    textStyle.SetFontFamilies(layoutProperty->GetPlaceholderFontFamilyValue(defaultFontFamily));
    FontRegisterCallback(frameNode, textStyle.GetFontFamilies());

    Dimension fontSize;
    if (layoutProperty->GetPlaceholderValue("").empty()) {
        if (layoutProperty->HasFontSize() && layoutProperty->GetFontSize().value_or(Dimension()).IsNonNegative()) {
            fontSize = layoutProperty->GetFontSizeValue(Dimension());
        } else {
            fontSize = theme ? theme->GetFontSize() : textStyle.GetFontSize();
        }
    } else {
        if (layoutProperty->HasPlaceholderFontSize() &&
            layoutProperty->GetPlaceholderFontSize().value_or(Dimension()).IsNonNegative()) {
            fontSize = layoutProperty->GetPlaceholderFontSizeValue(Dimension());
        } else {
            fontSize = theme ? theme->GetFontSize() : textStyle.GetFontSize();
        }
    }

    textStyle.SetFontSize(fontSize);
    textStyle.SetFontWeight(
        layoutProperty->GetPlaceholderFontWeightValue(theme ? theme->GetFontWeight() : textStyle.GetFontWeight()));
    if (isDisabled) {
        textStyle.SetTextColor(theme ? theme->GetDisableTextColor() : textStyle.GetTextColor());
        if (layoutProperty->GetShowUnderlineValue(false) &&
            layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::UNSPECIFIED) {
            textStyle.SetTextColor(theme ? theme->GetTextColorDisable() : textStyle.GetTextColor());
        }
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

void TextFieldLayoutAlgorithm::FontRegisterCallback(
    const RefPtr<FrameNode>& frameNode, const std::vector<std::string>& fontFamilies)
{
    auto callback = [weakNode = WeakPtr<FrameNode>(frameNode)] {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(pattern);
        auto modifier = DynamicCast<TextFieldContentModifier>(pattern->GetContentModifier());
        CHECK_NULL_VOID(modifier);
        modifier->SetFontReady(true);
    };
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        bool isCustomFont = false;
        for (const auto& familyName : fontFamilies) {
            bool customFont = fontManager->RegisterCallbackNG(frameNode, familyName, callback);
            if (customFont) {
                isCustomFont = true;
            }
        }
        fontManager->AddVariationNodeNG(frameNode);
        if (isCustomFont) {
            auto pattern = frameNode->GetPattern<TextFieldPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetIsCustomFont(true);
            auto modifier = DynamicCast<TextFieldContentModifier>(pattern->GetContentModifier());
            CHECK_NULL_VOID(modifier);
            modifier->SetIsCustomFont(true);
        }
    }
}

ParagraphStyle TextFieldLayoutAlgorithm::GetParagraphStyle(const TextStyle& textStyle, const std::string& content) const
{
    return { .direction = GetTextDirection(content),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow(),
        .fontSize = textStyle.GetFontSize().ConvertToPx() };
}

void TextFieldLayoutAlgorithm::CreateParagraph(const TextStyle& textStyle, std::string content, bool needObscureText,
    int32_t nakedCharPosition, bool disableTextAlign)
{
    auto paraStyle = GetParagraphStyle(textStyle, content);
    if (!disableTextAlign) {
        paraStyle.align = textStyle.GetTextAlign();
    }
    paragraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_VOID(paragraph_);
    paragraph_->PushStyle(textStyle);
    StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    auto displayText = TextFieldPattern::CreateDisplayText(content, nakedCharPosition, needObscureText);
    paragraph_->AddText(displayText);
    paragraph_->Build();
}

void TextFieldLayoutAlgorithm::CreateParagraph(const TextStyle& textStyle, const std::vector<std::string>& contents,
    const std::string& content, bool needObscureText, bool disableTextAlign)
{
    TextStyle dragTextStyle = textStyle;
    Color color = textStyle.GetTextColor().ChangeAlpha(DRAGGED_TEXT_OPACITY);
    dragTextStyle.SetTextColor(color);
    std::vector<TextStyle> textStyles { textStyle, dragTextStyle, textStyle };

    auto style = textStyles.begin();
    ParagraphStyle paraStyle { .direction = GetTextDirection(content),
        .maxLines = style->GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = style->GetWordBreak(),
        .textOverflow = style->GetTextOverflow(),
        .fontSize = style->GetFontSize().ConvertToPx() };
    if (!disableTextAlign) {
        paraStyle.align = style->GetTextAlign();
    }
    paragraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_VOID(paragraph_);
    for (size_t i = 0; i < contents.size(); i++) {
        std::string splitStr = contents[i];
        if (splitStr.empty()) {
            continue;
        }
        auto& style = textStyles[i];
        paragraph_->PushStyle(style);
        StringUtils::TransformStrCase(splitStr, static_cast<int32_t>(style.GetTextCase()));
        if (needObscureText) {
            paragraph_->AddText(
                TextFieldPattern::CreateObscuredText(static_cast<int32_t>(StringUtils::ToWstring(splitStr).length())));
        } else {
            paragraph_->AddText(StringUtils::Str8ToStr16(splitStr));
        }
        paragraph_->PopStyle();
    }
    paragraph_->Build();
}

void TextFieldLayoutAlgorithm::CreateErrorParagraph(const std::string& content, const RefPtr<TextFieldTheme>& theme)
{
    CHECK_NULL_VOID(theme);
    TextStyle errorTextStyle = theme->GetErrorTextStyle();
    std::string errorText = content;
    ParagraphStyle paraStyle { .align = TextAlign::START,
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .fontSize = errorTextStyle.GetFontSize().ConvertToPx() };
    errorParagraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_VOID(errorParagraph_);
    errorParagraph_->PushStyle(errorTextStyle);
    StringUtils::TransformStrCase(errorText, static_cast<int32_t>(errorTextStyle.GetTextCase()));
    errorParagraph_->AddText(StringUtils::Str8ToStr16(errorText));
    errorParagraph_->Build();
}

TextDirection TextFieldLayoutAlgorithm::GetTextDirection(const std::string& content)
{
    TextDirection textDirection = TextDirection::LTR;
    auto showingTextForWString = StringUtils::ToWstring(content);
    for (const auto& charOfShowingText : showingTextForWString) {
        if (TextLayoutadapter::IsLeftToRight(charOfShowingText)) {
            return TextDirection::LTR;
        }
        if (TextLayoutadapter::IsRightToLeft(charOfShowingText) ||
            TextLayoutadapter::IsRightTOLeftArabic(charOfShowingText)) {
            return TextDirection::RTL;
        }
    }
    return textDirection;
}

const RefPtr<Paragraph>& TextFieldLayoutAlgorithm::GetParagraph() const
{
    return paragraph_;
}

const RefPtr<Paragraph>& TextFieldLayoutAlgorithm::GetErrorParagraph() const
{
    return errorParagraph_;
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

void TextFieldLayoutAlgorithm::SetPropertyToModifier(
    const TextStyle& textStyle, RefPtr<TextFieldContentModifier> modifier)
{
    CHECK_NULL_VOID(modifier);
    modifier->SetFontFamilies(textStyle.GetFontFamilies());
    modifier->SetFontSize(textStyle.GetFontSize());
    modifier->SetFontWeight(textStyle.GetFontWeight());
    modifier->SetTextColor(textStyle.GetTextColor());
    modifier->SetFontStyle(textStyle.GetFontStyle());
}

void TextFieldLayoutAlgorithm::UpdateUnitLayout(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto children = frameNode->GetChildren();
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentSize = content->GetRect().GetSize();
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto layoutProperty = AceType::DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    if (!children.empty() && layoutProperty->GetShowUnderlineValue(false) &&
        layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::UNSPECIFIED) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
        CHECK_NULL_VOID(childWrapper);
        auto textGeometryNode = childWrapper->GetGeometryNode();
        CHECK_NULL_VOID(textGeometryNode);
        auto childFrameSize = textGeometryNode->GetFrameSize();
        unitWidth_ = childFrameSize.Width();
        textGeometryNode->SetFrameOffset(
            OffsetF({ content->GetRect().GetX() + contentSize.Width() - childFrameSize.Width(), 0.0 }));
        if (childFrameSize.Height() < size.Height()) {
            childWrapper->GetGeometryNode()->SetFrameSize(SizeF({ unitWidth_, size.Height() }));
        }
        childWrapper->Layout();
    }
}
} // namespace OHOS::Ace::NG
