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
#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/common/font_manager.h"
#include "core/components_ng/pattern/text/text_layout_adapter.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text_field/text_field_content_modifier.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PARAGRAPH_SAVE_BOUNDARY = 1.0f;
constexpr uint32_t INLINE_DEFAULT_VIEW_MAXLINE = 3;
constexpr double TEXT_DECORATION_DISABLED_COLOR_ALPHA = 0.2;
constexpr Dimension INLINE_MIN_WITH = 16.0_vp;
} // namespace
void TextFieldLayoutAlgorithm::ConstructTextStyles(
    const RefPtr<FrameNode>& frameNode, TextStyle& textStyle, std::u16string& textContent, bool& showPlaceHolder)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>(frameNode->GetThemeScopeId());
    CHECK_NULL_VOID(textFieldTheme);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto textFieldPaintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textFieldPaintProperty);
    auto isInlineStyle = pattern->IsNormalInlineState();
    auto isTextArea = pattern->IsTextArea();
    UpdateTextStyleFontScale(textFieldLayoutProperty, textStyle, pattern);
    if (!pattern->GetTextUtf16Value().empty()) {
        UpdateTextStyle(frameNode, textFieldLayoutProperty, textFieldTheme, textStyle, pattern->IsDisabled(),
            textFieldPaintProperty->HasTextColorFlagByUser());
        textContent = pattern->GetTextUtf16Value();
        UpdateTextStyleTextOverflowAndWordBreak(textStyle, isTextArea, isInlineStyle, textFieldLayoutProperty);
    } else {
        UpdatePlaceholderTextStyle(
            frameNode, textFieldLayoutProperty, textFieldTheme, textStyle, pattern->IsDisabled(),
            textFieldPaintProperty->GetPlaceholderColorFlagByUserValue(false));
        textContent = textFieldLayoutProperty->GetPlaceholderValue(u"");
        showPlaceHolder = true;
    }

    textIndent_ = textStyle.GetTextIndent();
    auto fontManager = pipeline->GetFontManager();
    if (fontManager && !(fontManager->GetAppCustomFont().empty()) &&
        !(textFieldLayoutProperty->GetFontFamily().has_value())) {
        textStyle.SetFontFamilies(Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont()));
    }
    // use for modifier.
    auto contentModifier = pattern->GetContentModifier();
    CHECK_NULL_VOID(contentModifier);
    SetPropertyToModifier(textStyle, contentModifier);
    contentModifier->ModifyTextStyle(textStyle);
    contentModifier->SetFontReady(false);
}

void TextFieldLayoutAlgorithm::UpdateTextStyleTextOverflowAndWordBreak(TextStyle& textStyle, bool isTextArea,
    bool isInlineStyle, const RefPtr<TextFieldLayoutProperty>& textFieldLayoutProperty)
{
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (textFieldLayoutProperty->HasTextOverflow() &&
        textFieldLayoutProperty->GetTextOverflow() != TextOverflow::DEFAULT) {
        textStyle.SetTextOverflow(textFieldLayoutProperty->GetTextOverflow().value());
    } else {
        auto overflowStyle = (!isTextArea && isInlineStyle) ? TextOverflow::ELLIPSIS : TextOverflow::CLIP;
        textStyle.SetTextOverflow(overflowStyle);
    }

    if (isTextArea || isInlineStyle) {
        textStyle.SetWordBreak(textFieldLayoutProperty->GetWordBreak().value_or(WordBreak::BREAK_WORD));
    }
    // Not Support TextOverflow::MARQUEE Now
    if (textStyle.GetTextOverflow() == TextOverflow::MARQUEE) {
        if (!isTextArea && isInlineStyle) {
            textStyle.SetTextOverflow(TextOverflow::ELLIPSIS);
        } else {
            textStyle.SetTextOverflow(TextOverflow::CLIP);
        }
    }
    if (textFieldLayoutProperty->HasEllipsisMode() && textStyle.GetTextOverflow() == TextOverflow::ELLIPSIS) {
        textStyle.SetEllipsisMode(textFieldLayoutProperty->GetEllipsisModeValue(EllipsisMode::TAIL));
    }
}

void TextFieldLayoutAlgorithm::InlineFocusMeasure(const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper, double& safeBoundary, float& contentWidth)
{
    ApplyIndent(layoutWrapper, contentConstraint.maxSize.Width());
    paragraph_->Layout(
        contentConstraint.maxSize.Width() - static_cast<float>(safeBoundary) - PARAGRAPH_SAVE_BOUNDARY);
    auto longestLine = std::ceil(paragraph_->GetLongestLineWithIndent());
    paragraph_->Layout(std::min(static_cast<float>(longestLine), paragraph_->GetMaxWidth()));
    contentWidth = ConstraintWithMinWidth(
        contentConstraint, layoutWrapper, paragraph_, static_cast<float>(safeBoundary) + PARAGRAPH_SAVE_BOUNDARY);
}

std::optional<SizeF> TextFieldLayoutAlgorithm::InlineMeasureContent(const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto textFieldLayoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textFieldLayoutProperty, std::nullopt);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto textFieldTheme = pattern->GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, std::nullopt);

    float contentWidth = 0.0f;
    auto safeBoundary = textFieldTheme->GetInlineBorderWidth().ConvertToPx() * 2;
    if (pattern->HasFocus()) {
        InlineFocusMeasure(contentConstraint, layoutWrapper, safeBoundary, contentWidth);
    } else {
        ApplyIndent(layoutWrapper, contentConstraint.maxSize.Width());
        paragraph_->Layout(contentConstraint.maxSize.Width());
        if (autoWidth_) {
            auto paragraphLongestLine = std::ceil(paragraph_->GetLongestLineWithIndent());
            paragraph_->Layout(std::min(static_cast<float>(paragraphLongestLine), paragraph_->GetMaxWidth()));
        }
        contentWidth = ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph_);
        // calc inline status in advance
        auto widthOffSet = contentConstraint.selfIdealSize.Width().has_value()?
            pattern->GetPaddingLeft() + pattern->GetPaddingRight() - safeBoundary : 0.0f - safeBoundary;
        inlineParagraph_->Layout(contentConstraint.maxSize.Width() + widthOffSet
            - safeBoundary - PARAGRAPH_SAVE_BOUNDARY);
        auto longestLine = std::ceil(inlineParagraph_->GetLongestLineWithIndent());
        inlineParagraph_->Layout(std::min(static_cast<float>(longestLine), inlineParagraph_->GetMaxWidth()));
        auto inlineContentWidth = ConstraintWithMinWidth(contentConstraint, layoutWrapper, inlineParagraph_,
            static_cast<float>(safeBoundary) + PARAGRAPH_SAVE_BOUNDARY);
        inlineMeasureItem_.inlineScrollRectOffsetX = contentWidth
            + pattern->GetHorizontalPaddingAndBorderSum() - inlineContentWidth - safeBoundary - PARAGRAPH_SAVE_BOUNDARY;
    }

    textRect_.SetSize(SizeF(GetVisualTextWidth(), paragraph_->GetHeight()));

    auto inlineIdealHeight = contentConstraint.maxSize.Height();
    GetInlineMeasureItem(contentConstraint, layoutWrapper, inlineIdealHeight);
    auto contentHeight = GreatNotEqual(paragraph_->GetLongestLine(), 0.0)
        ? paragraph_->GetHeight() : std::max(preferredHeight_, paragraph_->GetHeight());
    auto minWidth = INLINE_MIN_WITH.ConvertToPx();
    contentWidth = GreatNotEqual(contentWidth, minWidth) ? contentWidth : minWidth;
    return SizeF(contentWidth, std::min(inlineIdealHeight, contentHeight));
}

void TextFieldLayoutAlgorithm::GetInlineMeasureItem(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, float& inlineIdealHeight)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldLayoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);

    if (pattern->HasFocus() && paragraph_->GetLineCount() != 0) {
        pattern->SetSingleLineHeight(paragraph_->GetHeight() / paragraph_->GetLineCount());
        // The maximum height of the inline mode defaults to a maximum of three rows.
        inlineIdealHeight =
            pattern->GetSingleLineHeight() * textFieldLayoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE);
        inlineMeasureItem_.inlineSizeHeight = pattern->GetSingleLineHeight() * std::min(
            static_cast<uint32_t>(paragraph_->GetLineCount()),
                textFieldLayoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE));
    } else {
        // calc inline status in advance
        CalcInlineMeasureItem(layoutWrapper);
    }
}

void TextFieldLayoutAlgorithm::ApplyIndent(LayoutWrapper* layoutWrapper, double width)
{
    if (LessOrEqual(textIndent_.Value(), 0.0)) {
        return;
    }
    // first line indent
    CHECK_NULL_VOID(paragraph_);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto textFieldLayoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);

    double indentValue = 0.0;
    if (textIndent_.Unit() != DimensionUnit::PERCENT) {
        float minFontScale = textFieldLayoutProperty->GetMinFontScale().value_or(0.0f);
        float maxFontScale = textFieldLayoutProperty->GetMaxFontScale().value_or(
            pipeline->GetMaxAppFontScale());
        float fontScale = std::min(pipeline->GetFontScale(), maxFontScale);
        indentValue = Dimension(indentValue).ConvertToPxDistribute(minFontScale, maxFontScale);
        if (!textIndent_.NormalizeToPx(pipeline->GetDipScale(),
            fontScale, pipeline->GetLogicScale(), width, indentValue)) {
            return;
        }
    } else {
        indentValue = width * textIndent_.Value();
    }
    indent_ = static_cast<float>(indentValue);
    std::vector<float> indents;
    // only indent first line
    indents.emplace_back(indent_);
    indents.emplace_back(0.0);
    paragraph_->SetIndents(indents);
}

void TextFieldLayoutAlgorithm::CalcInlineMeasureItem(LayoutWrapper* layoutWrapper)
{
    auto textFieldLayoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto lineCount = inlineParagraph_->GetLineCount() != 0 ? inlineParagraph_->GetLineCount() : 1;
    inlineMeasureItem_.inlineSizeHeight = inlineParagraph_->GetHeight() / lineCount
        * std::min(static_cast<uint32_t>(lineCount),
            textFieldLayoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE));
    inlineMeasureItem_.inlineContentRectHeight = GreatNotEqual(inlineParagraph_->GetLongestLine(), 0.0)
        ? inlineParagraph_->GetHeight() : std::max(preferredHeight_, inlineParagraph_->GetHeight());
    inlineMeasureItem_.inlineLastOffsetY =
        std::max(inlineMeasureItem_.inlineSizeHeight, inlineMeasureItem_.inlineContentRectHeight)
        - std::min(inlineMeasureItem_.inlineSizeHeight, inlineMeasureItem_.inlineContentRectHeight);
}

float TextFieldLayoutAlgorithm::ConstraintWithMinWidth(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper,
    RefPtr<Paragraph>& paragraph, float removeValue)
{
    CHECK_NULL_RETURN(paragraph, 0.0f);
    CHECK_NULL_RETURN(layoutWrapper, 0.0f);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
        !layoutWrapper->GetLayoutProperty()->GetLayoutRect()) {
        const auto& calcLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint();
        if (calcLayoutConstraint && calcLayoutConstraint->minSize.has_value() &&
            calcLayoutConstraint->minSize->Width().has_value() &&
            !contentConstraint.selfIdealSize.Width().has_value()) {
            auto width = std::max(contentConstraint.minSize.Width() - removeValue, paragraph->GetLongestLine());
            if (width != paragraph->GetLongestLine()) {
                paragraph->Layout(width);
            } else {
                if (LessNotEqual(paragraph->GetLongestLine(), paragraph->GetMaxWidth())) {
                    paragraph->Layout(std::ceil(paragraph->GetLongestLine()));
                }
                return contentConstraint.selfIdealSize.Width().has_value() ? paragraph->GetMaxWidth()
                                                                           : GetVisualTextWidth();
            }
        }
    }
    return std::max(paragraph->GetMaxWidth(), 0.0f);
}

SizeF TextFieldLayoutAlgorithm::PlaceHolderMeasureContent(const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper, float imageWidth)
{
    paragraph_->Layout(contentConstraint.maxSize.Width() - imageWidth);

    // Adapts to auto width.
    if (autoWidth_) {
        auto minWidth = static_cast<float>(INLINE_MIN_WITH.ConvertToPx());
        paragraph_->Layout(std::max(minWidth, std::ceil(paragraph_->GetLongestLine())));
    }

    auto contentWidth = ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph_, imageWidth);

    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, SizeF());
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, SizeF());
    if (pattern->GetTextInputFlag()) {
        // TextInput's counter is outside the input area
        auto reviseContentWidth = contentWidth + imageWidth;
        CounterNodeMeasure(reviseContentWidth, layoutWrapper);
    } else {
        // TextArea's counter is inside the input area
        CounterNodeMeasure(contentWidth, layoutWrapper);
    }

    float height = 0.0f;
    if (isFontSizeNonPositive_) {
        height = paragraph_->GetHeight();
    } else {
        height = GreatNotEqual(paragraph_->GetLongestLine(), 0.0) ? paragraph_->GetHeight()
                                                                  : std::max(preferredHeight_, paragraph_->GetHeight());
    }

    auto contentHeight = std::min(contentConstraint.maxSize.Height(), height);

    textRect_.SetSize(SizeF(GetVisualTextWidth(), paragraph_->GetHeight()));

    return SizeF(contentWidth, contentHeight);
}

SizeF TextFieldLayoutAlgorithm::TextAreaMeasureContent(const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    ACE_LAYOUT_SCOPED_TRACE("TextAreaMeasureContent");
    ApplyIndent(layoutWrapper, contentConstraint.maxSize.Width());
    paragraph_->Layout(contentConstraint.maxSize.Width());

    auto contentWidth = ConstraintWithMinWidth(contentConstraint, layoutWrapper, paragraph_);

    if (autoWidth_) {
        contentWidth = std::min(contentWidth, paragraph_->GetLongestLineWithIndent());
        auto minWidth = INLINE_MIN_WITH.ConvertToPx();
        contentWidth = GreatNotEqual(contentWidth, minWidth) ? contentWidth : minWidth;
        paragraph_->Layout(std::ceil(contentWidth));
    }

    auto counterNodeHeight = CounterNodeMeasure(contentWidth, layoutWrapper);

    auto height = GreatNotEqual(paragraph_->GetLongestLine(), 0.0)
                      ? paragraph_->GetHeight()
                      : std::max(preferredHeight_, paragraph_->GetHeight());

    auto contentHeight = std::min(contentConstraint.maxSize.Height() - counterNodeHeight, height);

    textRect_.SetSize(SizeF(GetVisualTextWidth(), paragraph_->GetHeight()));
    return SizeF(contentWidth, contentHeight);
}

SizeF TextFieldLayoutAlgorithm::TextInputMeasureContent(const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper, float imageWidth)
{
    ACE_LAYOUT_SCOPED_TRACE("TextInputMeasureContent");
    ApplyIndent(layoutWrapper, contentConstraint.maxSize.Width());
    paragraph_->Layout(std::numeric_limits<double>::infinity());
    float contentWidth = CalculateContentWidth(contentConstraint, layoutWrapper, imageWidth);
    float contentHeight = CalculateContentHeight(contentConstraint);
    textRect_.SetSize(SizeF(std::max(0.0f, paragraph_->GetLongestLine()) + indent_, paragraph_->GetHeight()));
    return SizeF(contentWidth, contentHeight);
}

float TextFieldLayoutAlgorithm::CalculateContentWidth(const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper, float imageWidth)
{
    auto contentWidth = contentConstraint.maxSize.Width() - imageWidth;
    auto textFieldWidth = contentWidth;

    std::optional<SizeF> minSize;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
        !layoutWrapper->GetLayoutProperty()->GetLayoutRect()) {
        const auto &calcLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint();
        if (calcLayoutConstraint && calcLayoutConstraint->minSize.has_value() &&
            calcLayoutConstraint->minSize->Width().has_value() &&
            !contentConstraint.selfIdealSize.Width().has_value()) {
            minSize = contentConstraint.minSize;
        }
    }
    if (minSize.has_value()) {
        auto minWidth = minSize.value().Width();
        paragraph_->Layout(std::max(std::ceil(paragraph_->GetLongestLineWithIndent()), minWidth));
    } else if (autoWidth_) {
        paragraph_->Layout(std::ceil(paragraph_->GetLongestLineWithIndent()));
    } else {
        paragraph_->Layout(std::max(std::ceil(paragraph_->GetLongestLineWithIndent()), textFieldWidth));
    }

    CounterNodeMeasure(contentWidth, layoutWrapper);
    if (autoWidth_) {
        double minWidth = INLINE_MIN_WITH.ConvertToPx();
        contentWidth = GreatNotEqual(contentWidth, minWidth) ? contentWidth : minWidth;
        contentWidth = std::min(contentWidth, std::ceil(paragraph_->GetLongestLineWithIndent()));
    }

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
        !layoutWrapper->GetLayoutProperty()->GetLayoutRect()) {
        const auto &calcLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint();
        if (calcLayoutConstraint && calcLayoutConstraint->minSize.has_value() &&
            calcLayoutConstraint->minSize->Width().has_value() &&
            !contentConstraint.selfIdealSize.Width().has_value()) {
            contentWidth = std::min(contentConstraint.maxSize.Width() - imageWidth,
                std::max(std::ceil(paragraph_->GetLongestLineWithIndent()),
                contentConstraint.minSize.Width() - imageWidth));
        }
    }
    return contentWidth;
}

float TextFieldLayoutAlgorithm::CalculateContentHeight(const LayoutConstraintF& contentConstraint)
{
    auto height = GreatNotEqual(paragraph_->GetLongestLine(), 0.0)
                      ? paragraph_->GetHeight()
                      : std::max(preferredHeight_, paragraph_->GetHeight());

    return std::min(contentConstraint.maxSize.Height(), height);
}

void TextFieldLayoutAlgorithm::CounterLayout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto counterDecorator = pattern->GetCounterDecorator();
    CHECK_NULL_VOID(counterDecorator);
    counterDecorator->LayoutDecorator();
}

void TextFieldLayoutAlgorithm::ErrorLayout(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto errorDecorator = pattern->GetErrorDecorator();
    CHECK_NULL_VOID(errorDecorator);
    errorDecorator->LayoutDecorator();
}

float TextFieldLayoutAlgorithm::CounterNodeMeasure(float contentWidth, LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, 0.0f);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, 0.0f);
    auto counterDecorator = pattern->GetCounterDecorator();
    CHECK_NULL_RETURN(counterDecorator, 0.0f);
    return counterDecorator->MeasureDecorator(contentWidth, textContent_, showPlaceHolder_);
}

float TextFieldLayoutAlgorithm::GetVisualTextWidth() const
{
    return std::min(paragraph_->GetMaxWidth(), std::max(0.0f, paragraph_->GetLongestLine()));
}

void TextFieldLayoutAlgorithm::UpdateTextStyleFontScale(const RefPtr<TextFieldLayoutProperty>& textFieldLayoutProperty,
    TextStyle& textStyle, const RefPtr<TextFieldPattern>& pattern)
{
    if (textFieldLayoutProperty->HasMaxFontScale()) {
        textStyle.SetMaxFontScale(textFieldLayoutProperty->GetMaxFontScale().value());
    }
    if (textFieldLayoutProperty->HasMinFontScale()) {
        textStyle.SetMinFontScale(textFieldLayoutProperty->GetMinFontScale().value());
    }
}

void TextFieldLayoutAlgorithm::UpdateTextStyleSetTextColor(const RefPtr<FrameNode>& frameNode,
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme,
    TextStyle& textStyle, bool isDisabled, bool isTextColorByUser)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(theme);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasForegroundColor()) {
        auto textColor = renderContext->GetForegroundColor().value();
        if (isDisabled) {
            textColor = textColor.BlendOpacity(theme->GetDisableOpacityRatio());
        }
        textStyle.SetTextColor(textColor);
    } else if (renderContext->HasForegroundColorStrategy()) {
        if (isDisabled) {
            textStyle.SetTextColor(theme->GetDisableTextColor());
        } else {
            textStyle.SetTextColor(Color::BLACK);
        }
    } else {
        if (isDisabled) {
            textStyle.SetTextColor(theme->GetDisableTextColor());
        } else {
            if (!isTextColorByUser) {
                layoutProperty->UpdateTextColor(theme ? theme->GetTextColor() : textStyle.GetTextColor());
            }
            textStyle.SetTextColor(
                layoutProperty->GetTextColorValue(theme ? theme->GetTextColor() : textStyle.GetTextColor()));
        }
    }
}

void TextFieldLayoutAlgorithm::UpdateTextStyle(const RefPtr<FrameNode>& frameNode,
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme,
    TextStyle& textStyle, bool isDisabled, bool isTextColorByUser)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(theme);
    const std::vector<std::string> defaultFontFamily = { "sans-serif" };
    textStyle.SetFontFamilies(layoutProperty->GetFontFamilyValue(defaultFontFamily));
    FontRegisterCallback(frameNode, textStyle.GetFontFamilies());

    Dimension fontSize = theme->GetFontSize();
    if (layoutProperty->HasFontSize() && layoutProperty->GetFontSize().value_or(Dimension()).IsNonNegative()) {
        fontSize = Dimension(layoutProperty->GetFontSizeValue(Dimension()).ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale()));
    }
    textStyle.SetFontSize(fontSize);
    textStyle.SetTextAlign(layoutProperty->GetTextAlignValue(TextAlign::START));
    textStyle.SetLineBreakStrategy(layoutProperty->GetLineBreakStrategyValue(LineBreakStrategy::GREEDY));
    textStyle.SetFontWeight(layoutProperty->GetFontWeightValue(theme->GetFontWeight()));
    UpdateTextStyleSetTextColor(frameNode, layoutProperty, theme, textStyle, isDisabled, isTextColorByUser);
    if (layoutProperty->GetMaxLines()) {
        textStyle.SetMaxLines(layoutProperty->GetMaxLines().value());
    }
    if (layoutProperty->HasItalicFontStyle()) {
        textStyle.SetFontStyle(layoutProperty->GetItalicFontStyle().value());
    }
    if (layoutProperty->HasTextAlign()) {
        textStyle.SetTextAlign(layoutProperty->GetTextAlign().value());
    }
    UpdateTextStyleMore(frameNode, layoutProperty, textStyle, isDisabled);
}

void TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleSetTextColor(
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme, TextStyle& textStyle,
    bool isDisabled, bool isTextColorByUser)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(theme);
    if (isTextColorByUser) {
        auto textColor = layoutProperty->GetPlaceholderTextColorValue(theme->GetPlaceholderColor());
        if (isDisabled) {
            textColor = textColor.BlendOpacity(theme->GetDisableOpacityRatio());
        }
        textStyle.SetTextColor(textColor);
    } else {
        if (isDisabled) {
            textStyle.SetTextColor(theme->GetDisableTextColor());
        } else {
            auto placeholderTextColor = theme ? theme->GetPlaceholderColor() : textStyle.GetTextColor();
            layoutProperty->UpdatePlaceholderTextColor(placeholderTextColor);
            textStyle.SetTextColor(layoutProperty->GetPlaceholderTextColorValue(placeholderTextColor));
        }
    }
}

void TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyle(const RefPtr<FrameNode>& frameNode,
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme, TextStyle& textStyle,
    bool isDisabled, bool isTextColorByUser)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(theme);
    const std::vector<std::string> defaultFontFamily = { "sans-serif" };
    textStyle.SetFontFamilies(layoutProperty->GetPlaceholderFontFamilyValue(defaultFontFamily));
    FontRegisterCallback(frameNode, textStyle.GetFontFamilies());

    Dimension fontSize;
    if (layoutProperty->GetPlaceholderValue(u"").empty()) {
        if (layoutProperty->HasFontSize() && layoutProperty->GetFontSize().value_or(Dimension()).IsNonNegative()) {
            fontSize = layoutProperty->GetFontSizeValue(Dimension());
        } else {
            fontSize = theme->GetFontSize();
        }
    } else {
        if (layoutProperty->HasPlaceholderFontSize() &&
            layoutProperty->GetPlaceholderFontSize().value_or(Dimension()).IsNonNegative()) {
            fontSize = layoutProperty->GetPlaceholderFontSizeValue(Dimension());
        } else {
            fontSize = theme->GetFontSize();
        }
    }

    textStyle.SetFontSize(fontSize);
    textStyle.SetFontWeight(layoutProperty->GetPlaceholderFontWeightValue(theme->GetFontWeight()));
    UpdatePlaceholderTextStyleSetTextColor(layoutProperty, theme, textStyle, isDisabled, isTextColorByUser);
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
    UpdatePlaceholderTextStyleMore(frameNode, layoutProperty, theme, textStyle, isDisabled);
}

LayoutConstraintF TextFieldLayoutAlgorithm::CalculateContentMaxSizeWithCalculateConstraint(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto textFieldContentConstraint = contentConstraint;
    CHECK_NULL_RETURN(layoutWrapper, textFieldContentConstraint);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, textFieldContentConstraint);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, textFieldContentConstraint);
    auto idealWidth = contentConstraint.selfIdealSize.Width().value_or(contentConstraint.maxSize.Width());
    auto idealHeight = contentConstraint.selfIdealSize.Height().value_or(contentConstraint.maxSize.Height());
    auto maxIdealSize = SizeF { idealWidth, idealHeight };
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
        !layoutWrapper->GetLayoutProperty()->GetLayoutRect()) {
        auto frameIdealSize = maxIdealSize + SizeF(pattern->GetHorizontalPaddingAndBorderSum(),
                                                 pattern->GetVerticalPaddingAndBorderSum());
        auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(static_cast<OptionalSize<float>>(frameIdealSize),
            layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
            layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
        finalSize.SetWidth(
            finalSize.Width().value_or(frameIdealSize.Width()) - pattern->GetHorizontalPaddingAndBorderSum());
        finalSize.SetHeight(
            finalSize.Height().value_or(frameIdealSize.Height()) - pattern->GetVerticalPaddingAndBorderSum());
        maxIdealSize.UpdateSizeWhenSmaller(finalSize.ConvertToSizeT());
        maxIdealSize.UpdateSizeWhenLarger(textFieldContentConstraint.minSize);
    }
    textFieldContentConstraint.maxSize = maxIdealSize;
    return textFieldContentConstraint;
}

LayoutConstraintF TextFieldLayoutAlgorithm::CalculateFrameSizeConstraint(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    LayoutConstraintF frameSizeConstraintF = contentConstraint;
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, frameSizeConstraintF);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, frameSizeConstraintF);
    auto border = pattern->GetBorderWidthProperty();
    auto left = pattern->GetBorderLeft(border) + pattern->GetPaddingLeft();
    auto right = pattern->GetBorderRight(border) + pattern->GetPaddingRight();
    auto top = pattern->GetBorderTop(border) + pattern->GetPaddingTop();
    auto bottom = pattern->GetBorderBottom(border) + pattern->GetPaddingBottom();
    frameSizeConstraintF.maxSize.AddPadding(left, right, top, bottom);
    frameSizeConstraintF.minSize.AddPadding(left, right, top, bottom);
    return frameSizeConstraintF;
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
    CHECK_NULL_VOID(fontManager);
    bool isCustomFont = false;
    for (const auto& familyName : fontFamilies) {
        bool customFont = fontManager->RegisterCallbackNG(frameNode, familyName, callback);
        if (customFont) {
            isCustomFont = true;
        }
    }
    if (isCustomFont || fontManager->IsDefaultFontChanged()) {
        auto pattern = frameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsCustomFont(true);
        auto modifier = DynamicCast<TextFieldContentModifier>(pattern->GetContentModifier());
        CHECK_NULL_VOID(modifier);
        modifier->SetIsCustomFont(true);
    }
}

ParagraphStyle TextFieldLayoutAlgorithm::GetParagraphStyle(
    const TextStyle& textStyle, const std::u16string& content, const float fontSize) const
{
    return {
        .direction = GetTextDirection(content, direction_),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = textStyle.GetWordBreak(),
        .ellipsisMode = textStyle.GetEllipsisMode(),
        .lineBreakStrategy = textStyle.GetLineBreakStrategy(),
        .textOverflow = textStyle.GetTextOverflow(),
        .fontSize = fontSize
    };
}

void TextFieldLayoutAlgorithm::CreateParagraph(const TextStyle& textStyle, std::u16string content, bool needObscureText,
    int32_t nakedCharPosition, CreateParagraphData paragraphData)
{
    auto paraStyle = GetParagraphStyle(textStyle, content, paragraphData.fontSize);
    if (!paragraphData.disableTextAlign) {
        paraStyle.align = textStyle.GetTextAlign();
    }
    paragraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_VOID(paragraph_);
    paragraph_->PushStyle(textStyle);
    StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    auto displayText = TextFieldPattern::CreateDisplayText(content, nakedCharPosition,
        needObscureText, theme->IsShowPasswordDirectly());
    UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(displayText.data()), displayText.length(), 0);
    paragraph_->AddText(displayText);
    paragraph_->Build();
}

void TextFieldLayoutAlgorithm::CreateParagraph(const TextStyle& textStyle, const std::vector<std::u16string>& contents,
    const std::u16string& content, bool needObscureText, CreateParagraphData paragraphData)
{
    TextStyle dragTextStyle = textStyle;
    Color color = textStyle.GetTextColor().ChangeAlpha(DRAGGED_TEXT_TRANSPARENCY);
    dragTextStyle.SetTextColor(color);
    std::vector<TextStyle> textStyles { textStyle, dragTextStyle, textStyle };

    auto style = textStyles.begin();
    ParagraphStyle paraStyle { .direction = GetTextDirection(content, direction_),
        .maxLines = style->GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = style->GetWordBreak(),
        .ellipsisMode = textStyle.GetEllipsisMode(),
        .lineBreakStrategy = textStyle.GetLineBreakStrategy(),
        .textOverflow = style->GetTextOverflow(),
        .fontSize = paragraphData.fontSize };
    if (!paragraphData.disableTextAlign) {
        paraStyle.align = style->GetTextAlign();
    }
    paragraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_VOID(paragraph_);
    for (size_t i = 0; i < contents.size(); i++) {
        std::u16string splitStr = contents[i];
        if (splitStr.empty()) {
            continue;
        }
        if (style->GetMaxLines() == 1) {
            std::replace(splitStr.begin(), splitStr.end(), u'\n', u' ');
        }
        auto& style = textStyles[i];
        paragraph_->PushStyle(style);
        StringUtils::TransformStrCase(splitStr, static_cast<int32_t>(style.GetTextCase()));
        if (needObscureText) {
            paragraph_->AddText(
                TextFieldPattern::CreateObscuredText(static_cast<int32_t>(splitStr.length())));
        } else {
            UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(splitStr.data()), splitStr.length(), 0);
            paragraph_->AddText(splitStr);
        }
        paragraph_->PopStyle();
    }
    paragraph_->Build();
}

void TextFieldLayoutAlgorithm::CreateInlineParagraph(const TextStyle& textStyle, std::u16string content,
    bool needObscureText, int32_t nakedCharPosition, CreateParagraphData paragraphData)
{
    auto paraStyle = GetParagraphStyle(textStyle, content, paragraphData.fontSize);
    if (!paragraphData.disableTextAlign) {
        paraStyle.align = textStyle.GetTextAlign();
    }
    paraStyle.maxLines = -1;
    inlineParagraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_VOID(paragraph_);
    inlineParagraph_->PushStyle(textStyle);
    StringUtils::TransformStrCase(content, static_cast<int32_t>(textStyle.GetTextCase()));
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    auto displayText = TextFieldPattern::CreateDisplayText(content, nakedCharPosition,
        needObscureText, theme->IsShowPasswordDirectly());
    UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(displayText.data()), displayText.length(), 0);
    inlineParagraph_->AddText(displayText);
    inlineParagraph_->Build();
}

TextDirection TextFieldLayoutAlgorithm::GetTextDirection(const std::u16string& content, TextDirection direction)
{
    if (direction == TextDirection::LTR || direction == TextDirection::RTL) {
        return direction;
    }

    bool isRTL = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto textDirection = isRTL ? TextDirection::RTL : TextDirection::LTR;
    for (const auto& charOfShowingText : content) {
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

RefPtr<Paragraph> TextFieldLayoutAlgorithm::GetParagraph() const
{
    return paragraph_;
}

void TextFieldLayoutAlgorithm::GetSuitableSize(SizeF& maxSize, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textFieldTheme = pattern->GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    auto safeBoundary = textFieldTheme->GetInlineBorderWidth().ConvertToPx() * 2;
    if (pattern->HasFocus() && pattern->IsInlineMode()) {
        maxSize.SetWidth(maxSize.Width() - static_cast<float>(safeBoundary) - PARAGRAPH_SAVE_BOUNDARY);
    }
}

float TextFieldLayoutAlgorithm::GetTextFieldDefaultHeight()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto height = textFieldTheme->GetHeight();
    return static_cast<float>(height.ConvertToPx());
}

void TextFieldLayoutAlgorithm::SetPropertyToModifier(
    const TextStyle& textStyle, RefPtr<TextFieldContentModifier> modifier)
{
    CHECK_NULL_VOID(modifier);
    modifier->SetFontFamilies(textStyle.GetFontFamilies());
    modifier->SetFontSize(textStyle.GetFontSize(), textStyle);
    if (textStyle.GetAdaptTextSize()) {
        modifier->SetAdaptMinFontSize(textStyle.GetAdaptMinFontSize(), textStyle);
        modifier->SetAdaptMaxFontSize(textStyle.GetAdaptMaxFontSize(), textStyle);
    }
    modifier->SetFontWeight(textStyle.GetFontWeight());
    modifier->SetTextColor(textStyle.GetTextColor());
    modifier->SetFontStyle(textStyle.GetFontStyle());
    modifier->SetTextOverflow(textStyle.GetTextOverflow());
    modifier->SetTextDecoration(textStyle.GetTextDecoration(), textStyle.GetTextDecorationColor(),
        textStyle.GetTextDecorationStyle());
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

bool TextFieldLayoutAlgorithm::AddAdaptFontSizeAndAnimations(TextStyle& textStyle,
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);
    bool hasHeightOverride = textStyle.HasHeightOverride();
    auto lineHeight = textStyle.GetLineHeight();
    SetAdaptFontSizeLineHeight(lineHeight, textStyle);
    textStyle.SetLineHeight(Dimension(), false);
    bool result = false;
    const std::u16string& text = textContent_.empty() ? u"a" : textContent_;
    switch (layoutProperty->GetHeightAdaptivePolicyValue(TextHeightAdaptivePolicy::MAX_LINES_FIRST)) {
        case TextHeightAdaptivePolicy::MAX_LINES_FIRST:
            if (pattern->IsInlineMode()) {
                result = AdaptInlineFocusMinFontSize(textStyle, text, 1.0_fp, contentConstraint, layoutWrapper);
            } else {
                result = AdaptMinFontSize(textStyle, text, 1.0_fp, contentConstraint, layoutWrapper);
            }
            break;
        case TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST:
            if (pattern->IsInlineMode()) {
                result = AdaptInlineFocusFontSize(textStyle, text, 1.0_fp, contentConstraint, layoutWrapper);
            } else {
                result = AdaptMinFontSize(textStyle, text, 1.0_fp, contentConstraint, layoutWrapper);
            }
            break;
        case TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST:
            if (pattern->IsInlineMode()) {
                result = AdaptInlineFocusFontSize(textStyle, text, 1.0_fp, contentConstraint, layoutWrapper);
            } else {
                result = AdaptMaxFontSize(textStyle, text, 1.0_fp, contentConstraint, layoutWrapper);
            }
            break;
        default:
            break;
    }
    textStyle.SetLineHeight(lineHeight, hasHeightOverride);
    if (result && (hasHeightOverride || textContent_.empty())) {
        return CreateParagraphAndLayout(textStyle, textContent_, contentConstraint, layoutWrapper, false);
    }
    return result;
}

bool TextFieldLayoutAlgorithm::IsNeedAdaptFontSize(const TextStyle& textStyle,
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const LayoutConstraintF& contentConstraint)
{
    if (!textStyle.GetAdaptTextSize()) {
        return false;
    }
    auto adaptivePolicy = layoutProperty->GetHeightAdaptivePolicyValue(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    if ((adaptivePolicy != TextHeightAdaptivePolicy::MAX_LINES_FIRST) &&
        (adaptivePolicy != TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST) &&
        (adaptivePolicy != TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST)) {
        return false;
    }
    return TextAdaptFontSizer::IsNeedAdaptFontSize(textStyle, contentConstraint);
}

bool TextFieldLayoutAlgorithm::AdaptInlineFocusFontSize(TextStyle& textStyle, const std::u16string& content,
    const Dimension& stepUnit, const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint);
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(minFontSize, 0.0)) {
        return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper, false);
    }
    double stepSize = 0.0;
    GetAdaptFontSizeStep(textStyle, stepSize, stepUnit, contentConstraint);
    auto tag = static_cast<int32_t>((maxFontSize - minFontSize) / stepSize);
    auto length = tag + 1 + (GreatNotEqual(maxFontSize, minFontSize + stepSize * tag) ? 1 : 0);
    int32_t left = 0;
    int32_t right = length - 1;
    float fontSize = 0.0f;
    auto newContentConstraint = BuildInfinityLayoutConstraint(contentConstraint);
    auto maxSize = GetMaxMeasureSize(contentConstraint);
    GetSuitableSize(maxSize, layoutWrapper);
    while (left <= right) {
        int32_t mid = left + (right - left) / 2;
        fontSize = static_cast<float>((mid == length - 1) ? (maxFontSize) : (minFontSize + stepSize * mid));
        textStyle.SetFontSize(Dimension(fontSize));
        if (!CreateParagraphAndLayout(textStyle, content, newContentConstraint, layoutWrapper)) {
            return false;
        }
        if (!IsInlineFocusAdaptExceedLimit(maxSize)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    fontSize = static_cast<float>((left - 1 == length - 1) ? (maxFontSize) : (minFontSize + stepSize * (left - 1)));
    fontSize = LessNotEqual(fontSize, minFontSize) ? minFontSize : fontSize;
    fontSize = GreatNotEqual(fontSize, maxFontSize) ? maxFontSize : fontSize;
    textStyle.SetFontSize(Dimension(fontSize));
    return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper);
}

LayoutConstraintF TextFieldLayoutAlgorithm::BuildInfinityLayoutConstraint(const LayoutConstraintF& contentConstraint)
{
    auto newContentConstraint = contentConstraint;
    newContentConstraint.maxSize = { std::numeric_limits<double>::infinity(),
        std::numeric_limits<double>::infinity() };
    if (newContentConstraint.selfIdealSize.Width()) {
        newContentConstraint.selfIdealSize.SetWidth(std::numeric_limits<double>::infinity());
    }
    if (newContentConstraint.selfIdealSize.Height()) {
        newContentConstraint.selfIdealSize.SetHeight(std::numeric_limits<double>::infinity());
    }
    return newContentConstraint;
}

bool TextFieldLayoutAlgorithm::IsInlineFocusAdaptExceedLimit(const SizeF& maxSize)
{
    auto paragraph = GetParagraph();
    CHECK_NULL_RETURN(paragraph, false);
    bool didExceedMaxLines = false;
    didExceedMaxLines |= GreatNotEqual(paragraph->GetHeight() / paragraph->GetLineCount(),
        maxSize.Height());
    didExceedMaxLines |= GreatNotEqual(paragraph->GetLongestLine(), maxSize.Width());
    didExceedMaxLines |= IsAdaptFontSizeExceedLineHeight(paragraph);
    return didExceedMaxLines;
}

bool TextFieldLayoutAlgorithm::AdaptInlineFocusMinFontSize(TextStyle& textStyle, const std::u16string& content,
    const Dimension& stepUnit, const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    GetAdaptMaxMinFontSize(textStyle, maxFontSize, minFontSize, contentConstraint);
    if (LessNotEqual(maxFontSize, minFontSize) || LessOrEqual(minFontSize, 0.0)) {
        return CreateParagraphAndLayout(textStyle, content, contentConstraint, layoutWrapper, false);
    }
    double stepSize = 0.0;
    GetAdaptFontSizeStep(textStyle, stepSize, stepUnit, contentConstraint);
    auto textFieldLayoutProperty = DynamicCast<TextFieldLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(textFieldLayoutProperty, false);
    auto maxViewLines = textFieldLayoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE);
    auto newContentConstraint = BuildInlineFocusLayoutConstraint(contentConstraint, layoutWrapper);
    auto maxSize = GetMaxMeasureSize(contentConstraint);
    GetSuitableSize(maxSize, layoutWrapper);
    while (GreatOrEqual(maxFontSize, minFontSize)) {
        textStyle.SetFontSize(Dimension(maxFontSize));
        if (!CreateParagraphAndLayout(textStyle, content, newContentConstraint, layoutWrapper)) {
            return false;
        }
        if (!IsInlineFocusAdaptMinExceedLimit(maxSize, maxViewLines)) {
            break;
        }
        maxFontSize -= stepSize;
    }
    return true;
}

LayoutConstraintF TextFieldLayoutAlgorithm::BuildInlineFocusLayoutConstraint(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, contentConstraint);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, contentConstraint);
    auto textFieldTheme = pattern->GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, contentConstraint);
    auto safeBoundary = textFieldTheme->GetInlineBorderWidth().ConvertToPx() * 2;
    auto inlineBoundary = static_cast<float>(safeBoundary) + PARAGRAPH_SAVE_BOUNDARY;
    auto newContentConstraint = contentConstraint;
    newContentConstraint.maxSize.SetWidth(newContentConstraint.maxSize.Width() - inlineBoundary);
    if (newContentConstraint.selfIdealSize.Width()) {
        newContentConstraint.selfIdealSize.SetWidth(newContentConstraint.selfIdealSize.Width().value() -
            inlineBoundary);
    }
    return newContentConstraint;
}

bool TextFieldLayoutAlgorithm::IsInlineFocusAdaptMinExceedLimit(const SizeF& maxSize, uint32_t maxViewLines)
{
    auto paragraph = GetParagraph();
    CHECK_NULL_RETURN(paragraph, false);
    bool didExceedMaxLines = paragraph->DidExceedMaxLines();
    didExceedMaxLines = didExceedMaxLines || ((maxViewLines > 0) && (paragraph->GetLineCount() > maxViewLines));
    didExceedMaxLines = didExceedMaxLines || GreatNotEqual(paragraph->GetHeight() / paragraph->GetLineCount(),
        maxSize.Height());
    didExceedMaxLines = didExceedMaxLines || GreatNotEqual(paragraph->GetLongestLine(), maxSize.Width());
    didExceedMaxLines = didExceedMaxLines || IsAdaptFontSizeExceedLineHeight(paragraph);
    return didExceedMaxLines;
}

bool TextFieldLayoutAlgorithm::CreateParagraphAndLayout(const TextStyle& textStyle, const std::u16string& content,
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, bool needLayout)
{
    if (!CreateParagraphEx(textStyle, content, contentConstraint, layoutWrapper)) {
        return false;
    }
    ACE_LAYOUT_SCOPED_TRACE("CreateParagraphAndLayout[needLayout:%d]", needLayout);
    if (needLayout) {
        CHECK_NULL_RETURN(paragraph_, false);
        auto maxSize = GetMaxMeasureSize(contentConstraint);
        ApplyIndent(layoutWrapper, maxSize.Width());
        paragraph_->Layout(std::max(0.0f, maxSize.Width()));
    }
    return true;
}

void TextFieldLayoutAlgorithm::UpdateTextStyleLineHeight(const RefPtr<FrameNode>& frameNode,
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, TextStyle& textStyle)
{
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (layoutProperty->HasLineHeight()) {
        auto heightValue = layoutProperty->GetLineHeightValue(Dimension());
        if (heightValue.Unit() == DimensionUnit::PERCENT) {
            textStyle.SetLineHeight(heightValue);
        } else {
            textStyle.SetLineHeight(
                Dimension(heightValue.ConvertToPxDistribute(textStyle.GetMinFontScale(), textStyle.GetMaxFontScale())));
        }
        textStyle.SetHalfLeading(layoutProperty->GetHalfLeading().value_or(pipeline->GetHalfLeading()));
    }
}

void TextFieldLayoutAlgorithm::UpdateTextStyleMore(const RefPtr<FrameNode>& frameNode,
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, TextStyle& textStyle, bool isDisabled)
{
    if (layoutProperty->HasTextIndent()) {
        textStyle.SetTextIndent(layoutProperty->GetTextIndent().value());
    }
    if (layoutProperty->HasAdaptMinFontSize()) {
        textStyle.SetAdaptMinFontSize(layoutProperty->GetAdaptMinFontSize().value());
    }
    if (layoutProperty->HasAdaptMaxFontSize()) {
        textStyle.SetAdaptMaxFontSize(layoutProperty->GetAdaptMaxFontSize().value());
    }
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (pattern->IsInPasswordMode()) {
        return;
    }
    if (layoutProperty->HasTextDecoration()) {
        textStyle.SetTextDecoration(layoutProperty->GetTextDecoration().value());
    }
    if (layoutProperty->HasTextDecorationColor()) {
        if (isDisabled) {
            textStyle.SetTextDecorationColor(layoutProperty->GetTextDecorationColor().value()
                .BlendOpacity(TEXT_DECORATION_DISABLED_COLOR_ALPHA));
        } else {
            textStyle.SetTextDecorationColor(layoutProperty->GetTextDecorationColor().value());
        }
    }
    if (layoutProperty->HasTextDecorationStyle()) {
        textStyle.SetTextDecorationStyle(layoutProperty->GetTextDecorationStyle().value());
    }
    if (layoutProperty->HasLetterSpacing()) {
        textStyle.SetLetterSpacing(layoutProperty->GetLetterSpacing().value());
    }
    UpdateTextStyleLineHeight(frameNode, layoutProperty, textStyle);
    if (layoutProperty->HasFontFeature()) {
        textStyle.SetFontFeatures(layoutProperty->GetFontFeature().value());
    }
    if (layoutProperty->HasLineSpacing()) {
        textStyle.SetLineSpacing(layoutProperty->GetLineSpacing().value());
    }
}

void TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyleMore(const RefPtr<FrameNode>& frameNode,
    const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme,
    TextStyle& placeholderTextStyle, bool isDisabled)
{
    if (layoutProperty->GetPlaceholderValue(u"").empty()) {
        if (layoutProperty->HasAdaptMinFontSize()) {
            placeholderTextStyle.SetAdaptMinFontSize(layoutProperty->GetAdaptMinFontSize().value());
        }
        if (layoutProperty->HasAdaptMaxFontSize()) {
            placeholderTextStyle.SetAdaptMaxFontSize(layoutProperty->GetAdaptMaxFontSize().value());
        }
    }
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (pattern->IsInPasswordMode()) {
        return;
    }
    if (layoutProperty->HasLineHeight()) {
        auto heightValue = layoutProperty->GetLineHeightValue(Dimension());
        if (heightValue.Unit() == DimensionUnit::PERCENT) {
            placeholderTextStyle.SetLineHeight(heightValue);
        } else {
            placeholderTextStyle.SetLineHeight(
                Dimension(heightValue.ConvertToPxDistribute(placeholderTextStyle.GetMinFontScale(),
                    placeholderTextStyle.GetMaxFontScale())));
        }
        placeholderTextStyle.SetHalfLeading(layoutProperty->GetHalfLeading().value_or(pipeline->GetHalfLeading()));
    }
    if (layoutProperty->HasMaxFontScale()) {
        placeholderTextStyle.SetMaxFontScale(layoutProperty->GetMaxFontScale().value());
    }
    if (layoutProperty->HasMinFontScale()) {
        placeholderTextStyle.SetMinFontScale(layoutProperty->GetMinFontScale().value());
    }
    placeholderTextStyle.SetLineSpacing(theme->GetPlaceholderLineSpacing());
}

bool TextFieldLayoutAlgorithm::DidExceedMaxLines(const SizeF& maxSize)
{
    auto paragraph = GetParagraph();
    CHECK_NULL_RETURN(paragraph, false);
    return paragraph->DidExceedMaxLines() ||
        GreatNotEqual(paragraph->GetHeight(), maxSize.Height()) ||
        GreatNotEqual(paragraph->GetLongestLine(), maxSize.Width()) ||
        IsAdaptFontSizeExceedLineHeight(paragraph);
}

bool TextFieldLayoutAlgorithm::IsAdaptExceedLimit(const SizeF& maxSize)
{
    auto paragraph = GetParagraph();
    CHECK_NULL_RETURN(paragraph, false);
    return (paragraph->GetLineCount() > 1) || paragraph->DidExceedMaxLines() ||
        GreatNotEqual(paragraph->GetLongestLine(), maxSize.Width()) ||
        IsAdaptFontSizeExceedLineHeight(paragraph) ||
           GreatNotEqual(paragraph->GetHeight(), maxSize.Height());
}
} // namespace OHOS::Ace::NG
