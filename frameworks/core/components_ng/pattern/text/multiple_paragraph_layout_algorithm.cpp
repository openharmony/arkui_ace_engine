/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/multiple_paragraph_layout_algorithm.h"

#include "text_layout_adapter.h"

#include "base/geometry/dimension.h"
#include "base/i18n/localization.h"
#include "base/log/ace_performance_monitor.h"
#include "base/utils/utf_helper.h"
#include "core/common/font_manager.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/text/paragraph_util.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/font_collection.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SYMBOL_SPAN_LENGTH = 2;
const std::string CUSTOM_SYMBOL_SUFFIX = "_CustomSymbol";
const std::string DEFAULT_SYMBOL_FONTFAMILY = "HM Symbol";
float GetContentOffsetY(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, 0.0f);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    auto size = geometryNode->GetFrameSize();
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    auto offsetY = padding.top.value_or(0);
    auto align = Alignment::CENTER;
    if (layoutProperty->GetPositionProperty()) {
        align = layoutProperty->GetPositionProperty()->GetAlignment().value_or(align);
    }
    const auto& content = geometryNode->GetContent();
    if (content) {
        offsetY += Alignment::GetAlignPosition(size, content->GetRect().GetSize(), align).GetY();
    }
    return offsetY;
}
} // namespace

void MultipleParagraphLayoutAlgorithm::ConstructTextStyles(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, TextStyle& textStyle)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    textStyle.SetTextStyleUid(frameNode->GetId() + 1);
    if (frameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        textStyle.SetSymbolUid(frameNode->GetId() + 1);
        textStyle.isSymbolGlyph_ = true;
    }
    if (Negative(contentConstraint.maxSize.Width()) || Negative(contentConstraint.maxSize.Height())) {
        return;
    }
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    auto contentModifier = pattern->GetContentModifier();

    auto themeScopeId = frameNode->GetThemeScopeId();
    auto content = textLayoutProperty->GetContent().value_or(u"");
    auto textTheme = pipeline->GetTheme<TextTheme>(themeScopeId);
    CHECK_NULL_VOID(textTheme);
    CreateTextStyleUsingTheme(textLayoutProperty, textTheme, textStyle, frameNode->GetTag() == V2::SYMBOL_ETS_TAG);
    textStyle.SetSymbolType(textLayoutProperty->GetSymbolTypeValue(SymbolType::SYSTEM));
    std::vector<std::string> fontFamilies;
    auto fontManager = pipeline->GetFontManager();
    if (fontManager && !(fontManager->GetAppCustomFont().empty()) &&
        !(textLayoutProperty->GetFontFamily().has_value())) {
        fontFamilies = Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont());
    } else {
#ifndef OHOS_STANDARD_SYSTEM
        const std::vector<std::string> defaultFontFamily = {"sans-serif"};
#else
        const std::vector<std::string> defaultFontFamily = textTheme->GetTextStyle().GetFontFamilies();
#endif
        fontFamilies = textLayoutProperty->GetFontFamilyValue(defaultFontFamily);
    }
    UpdateFontFamilyWithSymbol(textStyle, fontFamilies, frameNode->GetTag() == V2::SYMBOL_ETS_TAG);
    UpdateSymbolStyle(textStyle, frameNode->GetTag() == V2::SYMBOL_ETS_TAG);
    auto lineThicknessScale = textLayoutProperty->GetLineThicknessScale().value_or(1.0f);
    textStyle.SetLineThicknessScale(lineThicknessScale);
    auto textColor = textLayoutProperty->GetTextColorValue(textTheme->GetTextStyle().GetTextColor());
    if (contentModifier) {
        if (textLayoutProperty->GetIsAnimationNeededValue(true)) {
            SetPropertyToModifier(textLayoutProperty, contentModifier, textStyle, frameNode, textColor);
            contentModifier->ModifyTextStyle(textStyle, textColor);
        }
        contentModifier->SetFontReady(false);
    }
    UpdateShaderStyle(textLayoutProperty, textStyle);
    textStyle.SetHalfLeading(textLayoutProperty->GetHalfLeadingValue(pipeline->GetHalfLeading()));
    textStyle.SetEnableAutoSpacing(textLayoutProperty->GetEnableAutoSpacingValue(false));
    textStyle.SetParagraphVerticalAlign(
        textLayoutProperty->GetTextVerticalAlignValue(TextVerticalAlign::BASELINE));
    SetAdaptFontSizeStepToTextStyle(textStyle, textLayoutProperty->GetAdaptFontSizeStep());
    FontRegisterCallback(frameNode, textStyle); // Register callback for fonts.
    textStyle.SetTextDirection(ParagraphUtil::GetTextDirection(content, layoutWrapper));
    textStyle.SetLocale(Localization::GetInstance()->GetFontLocale());
    UpdateTextColorIfForeground(frameNode, textStyle, textColor);
    inheritTextStyle_ = textStyle;
}

void MultipleParagraphLayoutAlgorithm::UpdateShaderStyle(
    const RefPtr<TextLayoutProperty>& layoutProperty, TextStyle& textStyle)
{
    if (layoutProperty->HasGradientShaderStyle()) {
        auto gradients = layoutProperty->GetGradientShaderStyle().value_or(Gradient());
        auto gradient = ToGradient(gradients);
        textStyle.SetColorShaderStyle(std::optional<Color>(std::nullopt));
        textStyle.SetGradient(gradient);
    } else if (layoutProperty->HasColorShaderStyle()) {
        std::optional<Color> colors = layoutProperty->GetColorShaderStyle().value_or(Color::TRANSPARENT);
        textStyle.SetGradient(std::nullopt);
        textStyle.SetColorShaderStyle(colors);
    } else {
        textStyle.SetGradient(std::nullopt);
        textStyle.SetColorShaderStyle(std::optional<Color>(std::nullopt));
    }
}

std::optional<OHOS::Ace::Gradient> MultipleParagraphLayoutAlgorithm::ToGradient(const NG::Gradient& gradient)
{
    OHOS::Ace::Gradient retGradient;
    retGradient.SetType(static_cast<OHOS::Ace::GradientType>(gradient.GetType()));
    if (retGradient.GetType() == OHOS::Ace::GradientType::LINEAR) {
        CHECK_NULL_RETURN(gradient.GetLinearGradient(), std::nullopt);
        auto angle = gradient.GetLinearGradient()->angle;
        if (angle.has_value()) {
            retGradient.GetLinearGradient().angle = ToAnimatableDimension(angle.value());
        }
        auto linearX = gradient.GetLinearGradient()->linearX;
        if (linearX.has_value()) {
            retGradient.GetLinearGradient().linearX = static_cast<OHOS::Ace::GradientDirection>(linearX.value());
        }
        auto linearY = gradient.GetLinearGradient()->linearY;
        if (linearY.has_value()) {
            retGradient.GetLinearGradient().linearY = static_cast<OHOS::Ace::GradientDirection>(linearY.value());
        }
    }
    if (retGradient.GetType() == OHOS::Ace::GradientType::RADIAL) {
        CHECK_NULL_RETURN(gradient.GetRadialGradient(), std::nullopt);
        auto radialCenterX = gradient.GetRadialGradient()->radialCenterX;
        if (radialCenterX.has_value()) {
            retGradient.GetRadialGradient().radialCenterX = ToAnimatableDimension(radialCenterX.value());
        }
        auto radialCenterY = gradient.GetRadialGradient()->radialCenterY;
        if (radialCenterY.has_value()) {
            retGradient.GetRadialGradient().radialCenterY = ToAnimatableDimension(radialCenterY.value());
        }
        auto radialVerticalSize = gradient.GetRadialGradient()->radialVerticalSize;
        if (radialVerticalSize.has_value()) {
            retGradient.GetRadialGradient().radialVerticalSize = ToAnimatableDimension(radialVerticalSize.value());
        }
        auto radialHorizontalSize = gradient.GetRadialGradient()->radialHorizontalSize;
        if (radialVerticalSize.has_value()) {
            retGradient.GetRadialGradient().radialHorizontalSize = ToAnimatableDimension(radialHorizontalSize.value());
        }
    }
    retGradient.SetRepeat(gradient.GetRepeat());
    const auto& colorStops = gradient.GetColors();
    for (const auto& item : colorStops) {
        OHOS::Ace::GradientColor gradientColor;
        gradientColor.SetColor(item.GetColor());
        gradientColor.SetHasValue(item.GetHasValue());
        gradientColor.SetDimension(item.GetDimension());
        retGradient.AddColor(gradientColor);
    }
    return retGradient;
}

AnimatableDimension MultipleParagraphLayoutAlgorithm::ToAnimatableDimension(const Dimension& dimension)
{
    AnimatableDimension result(dimension);
    return result;
}

void MultipleParagraphLayoutAlgorithm::UpdateFontFamilyWithSymbol(TextStyle& textStyle,
    std::vector<std::string>& fontFamilies, bool isSymbol)
{
    if (!isSymbol) {
        textStyle.SetFontFamilies(fontFamilies);
        return;
    }
    auto symbolType = textStyle.GetSymbolType();
    std::vector<std::string> symbolFontFamilies;
    if (symbolType == SymbolType::CUSTOM) {
        for (auto& name : fontFamilies) {
            if (name.find(CUSTOM_SYMBOL_SUFFIX) != std::string::npos) {
                symbolFontFamilies.push_back(name);
                break;
            }
        }
        textStyle.SetFontFamilies(symbolFontFamilies);
    } else {
        symbolFontFamilies.push_back(DEFAULT_SYMBOL_FONTFAMILY);
        textStyle.SetFontFamilies(symbolFontFamilies);
    }
}

void MultipleParagraphLayoutAlgorithm::UpdateSymbolStyle(TextStyle& textStyle, bool isSymbol)
{
    if (!isSymbol) {
        return;
    }
    textStyle.SetRenderStrategy(textStyle.GetRenderStrategy() < 0 ? 0 : textStyle.GetRenderStrategy());
    textStyle.SetEffectStrategy(textStyle.GetEffectStrategy() < 0 ? 0 : textStyle.GetEffectStrategy());
}

void MultipleParagraphLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // child constraint has already been calculated by the UpdateParagraphBySpan method when triggering MeasureContent
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
    MeasureWithFixAtIdealSize(layoutWrapper);
    MeasureWithMatchParent(layoutWrapper);
    auto baselineDistance = 0.0f;
    auto paragraph = GetSingleParagraph();
    if (paragraph) {
        baselineDistance = paragraph->GetAlphabeticBaseline() + std::max(GetBaselineOffset(), 0.0f);
    }
    if (!NearZero(baselineDistance, 0.0f)) {
        baselineDistance += GetContentOffsetY(layoutWrapper);
    }
    layoutWrapper->GetGeometryNode()->SetBaselineDistance(baselineDistance);
}

void MultipleParagraphLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto contentOffset = GetContentOffset(layoutWrapper);
    CHECK_NULL_VOID(paragraphManager_);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetTag() != V2::SYMBOL_ETS_TAG);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    std::vector<int32_t> placeholderIndex;
    GetChildrenPlaceholderIndex(placeholderIndex);
    auto rectsForPlaceholders = paragraphManager_->GetPlaceholderRects();
    if (spans_.empty() || placeholderIndex.empty()) {
        pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, contentOffset);
        return;
    }
    size_t index = 0;
    const auto& children = GetAllChildrenWithBuild(layoutWrapper);
    // children only contains the image span.
    for (const auto& child : children) {
        if (!child) {
            ++index;
            continue;
        }
        if (index >= placeholderIndex.size() || index < 0) {
            child->SetActive(false);
            continue;
        }
        auto indexTemp = placeholderIndex.at(index);
        if (indexTemp >= static_cast<int32_t>(rectsForPlaceholders.size()) || indexTemp < 0) {
            child->SetActive(false);
            continue;
        }
        child->SetActive(true);
        auto rect = rectsForPlaceholders.at(indexTemp) - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
        auto geometryNode = child->GetGeometryNode();
        if (!geometryNode) {
            ++index;
            continue;
        }
        geometryNode->SetMarginFrameOffset(contentOffset + OffsetF(rect.Left(), rect.Top()));
        child->Layout();
        ++index;
    }
    pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, contentOffset);
}

void MultipleParagraphLayoutAlgorithm::GetChildrenPlaceholderIndex(std::vector<int32_t>& placeholderIndex)
{
    for (auto&& group : spans_) {
        for (const auto& child : group) {
            if (!child) {
                continue;
            }
            auto customSpanItem = AceType::DynamicCast<CustomSpanItem>(child);
            if (customSpanItem && !customSpanItem->isFrameNode) {
                continue;
            }
            if (AceType::InstanceOf<ImageSpanItem>(child) || AceType::InstanceOf<PlaceholderSpanItem>(child)) {
                placeholderIndex.emplace_back(child->placeholderIndex);
            }
        }
    }
}

void MultipleParagraphLayoutAlgorithm::FontRegisterCallback(
    const RefPtr<FrameNode>& frameNode, const TextStyle& textStyle)
{
    auto callback = [weakNode = WeakPtr<FrameNode>(frameNode)] {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        auto pattern = frameNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(pattern);
        auto modifier = DynamicCast<TextContentModifier>(pattern->GetContentModifier());
        CHECK_NULL_VOID(modifier);
        modifier->SetFontReady(true);
        TAG_LOGI(AceLogTag::ACE_TEXT, "FontRegisterCallback callback id:%{public}d", frameNode->GetId());
        auto layoutProperty = frameNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->OnPropertyChangeMeasure();
    };
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        bool isCustomFont = false;
        for (const auto& familyName : textStyle.GetFontFamilies()) {
            bool customFont = fontManager->RegisterCallbackNG(frameNode, familyName, callback);
            if (customFont) {
                isCustomFont = true;
            }
        }
        if (isCustomFont || fontManager->IsDefaultFontChanged()) {
            auto pattern = frameNode->GetPattern<TextPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetIsCustomFont(true);
            auto modifier = DynamicCast<TextContentModifier>(pattern->GetContentModifier());
            CHECK_NULL_VOID(modifier);
            modifier->SetIsCustomFont(true);
        }
    }
}

void MultipleParagraphLayoutAlgorithm::UpdateTextColorIfForeground(
    const RefPtr<FrameNode>& frameNode, TextStyle& textStyle, const Color& textColor)
{
    // Determines whether a foreground color is set or inherited.
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext->HasForegroundColor()) {
        if (renderContext->GetForegroundColorValue().GetValue() != textColor.GetValue()) {
            textStyle.SetTextColor(Color::FOREGROUND);
        } else {
            textStyle.SetTextColor(textColor);
        }
    } else if (renderContext->HasForegroundColorStrategy()) {
        textStyle.SetTextColor(Color::FOREGROUND);
    } else {
        textStyle.SetTextColor(textColor);
    }
}

void MultipleParagraphLayoutAlgorithm::SetFontSizePropertyToModifier(const RefPtr<TextLayoutProperty>& layoutProperty,
    const RefPtr<TextContentModifier>& modifier, const TextStyle& textStyle)
{
    auto fontSize = layoutProperty->GetFontSize();
    if (fontSize.has_value()) {
        modifier->SetFontSize(fontSize.value(), textStyle);
    } else {
        // Reset modifier FontSize.
        modifier->SetFontSize(textStyle.GetFontSize(), textStyle, true);
    }
    auto adaptMinFontSize = layoutProperty->GetAdaptMinFontSize();
    if (adaptMinFontSize.has_value()) {
        modifier->SetAdaptMinFontSize(adaptMinFontSize.value(), textStyle);
    } else {
        // Reset modifier MinFontSize.
        modifier->SetAdaptMinFontSize(textStyle.GetAdaptMinFontSize(), textStyle, true);
    }
    auto adaptMaxFontSize = layoutProperty->GetAdaptMaxFontSize();
    if (adaptMaxFontSize.has_value()) {
        modifier->SetAdaptMaxFontSize(adaptMaxFontSize.value(), textStyle);
    } else {
        // Reset modifier MaxFontSize.
        modifier->SetAdaptMaxFontSize(textStyle.GetAdaptMaxFontSize(), textStyle, true);
    }
}

void MultipleParagraphLayoutAlgorithm::SetDecorationPropertyToModifier(const RefPtr<TextLayoutProperty>& layoutProperty,
    const RefPtr<TextContentModifier>& modifier, const TextStyle& textStyle)
{
    auto textDecorationColor = layoutProperty->GetTextDecorationColor();
    if (textDecorationColor.has_value()) {
        modifier->SetTextDecorationColor(textDecorationColor.value());
    } else {
        modifier->SetTextDecorationColor(textStyle.GetTextDecorationColor(), true);
    }
    auto textDecoration = layoutProperty->GetTextDecoration();
    if (textDecoration.has_value()) {
        auto value = textDecoration.value().size() > 0 ? textDecoration.value()[0] : TextDecoration::NONE;
        modifier->SetTextDecoration(value, false);
    } else {
        modifier->SetTextDecoration(textStyle.GetTextDecorationFirst(), true);
    }
}

void MultipleParagraphLayoutAlgorithm::SetPropertyToModifier(const RefPtr<TextLayoutProperty>& layoutProperty,
    const RefPtr<TextContentModifier>& modifier, const TextStyle& textStyle, const RefPtr<FrameNode>& frameNode,
    const Color& textColor)
{
    SetFontSizePropertyToModifier(layoutProperty, modifier, textStyle);
    auto fontWeight = layoutProperty->GetFontWeight();
    if (fontWeight.has_value()) {
        modifier->SetFontWeight(fontWeight.value());
    } else {
        modifier->SetFontWeight(textStyle.GetFontWeight(), true);
    }
    auto propTextColor = layoutProperty->GetTextColor();
    if (propTextColor.has_value()) {
        modifier->SetTextColor(propTextColor.value());
    } else {
        modifier->SetTextColor(textColor, true);
    }
    if (frameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto symbolColors = layoutProperty->GetSymbolColorList();
        if (symbolColors && symbolColors.has_value()) {
            modifier->SetSymbolColor(symbolColors.value());
        } else {
            modifier->SetSymbolColor(textStyle.GetSymbolColorList(), true);
        }
    }
    auto textShadow = layoutProperty->GetTextShadow();
    if (textShadow.has_value()) {
        modifier->SetTextShadow(textShadow.value());
    } else {
        modifier->SetTextShadow(textStyle.GetTextShadows());
    }
    SetDecorationPropertyToModifier(layoutProperty, modifier, textStyle);
    auto baselineOffset = layoutProperty->GetBaselineOffset();
    if (baselineOffset.has_value()) {
        modifier->SetBaselineOffset(baselineOffset.value(), textStyle);
    } else {
        modifier->SetBaselineOffset(textStyle.GetBaselineOffset(), textStyle, true);
    }
    auto lineHeight = layoutProperty->GetLineHeight();
    if (lineHeight.has_value()) {
        if (lineHeight->Unit() == DimensionUnit::PERCENT) {
            modifier->SetLineHeight(lineHeight.value(), textStyle, true);
        } else {
            modifier->SetLineHeight(lineHeight.value(), textStyle);
        }
    } else {
        modifier->SetLineHeight(textStyle.GetLineHeight(), textStyle, true);
    }
}

RefPtr<Paragraph> MultipleParagraphLayoutAlgorithm::GetSingleParagraph() const
{
    CHECK_NULL_RETURN(paragraphManager_, nullptr);
    CHECK_NULL_RETURN(!paragraphManager_->GetParagraphs().empty(), nullptr);
    auto paragraphInfo = paragraphManager_->GetParagraphs().front();
    auto paragraph = paragraphInfo.paragraph;
    CHECK_NULL_RETURN(paragraph, nullptr);
    return paragraph;
}

OffsetF MultipleParagraphLayoutAlgorithm::SetContentOffset(LayoutWrapper* layoutWrapper)
{
    OffsetF contentOffset(0.0f, 0.0f);
    CHECK_NULL_RETURN(layoutWrapper, contentOffset);

    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }

    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        contentOffset = Alignment::GetAlignPosition(size, content->GetRect().GetSize(), align) + paddingOffset;
        content->SetOffset(contentOffset);
    }
    return contentOffset;
}

void MultipleParagraphLayoutAlgorithm::SetAdaptFontSizeStepToTextStyle(
    TextStyle& textStyle, const std::optional<Dimension>& adaptFontSizeStep)
{
    textStyle.SetAdaptFontSizeStep(adaptFontSizeStep.value_or(Dimension(1.0, DimensionUnit::PX)));
}

bool MultipleParagraphLayoutAlgorithm::ParagraphReLayout(const LayoutConstraintF& contentConstraint)
{
    // Confirmed specification: The width of the text paragraph covers the width of the component, so this code is
    // generally not allowed to be modified
    CHECK_NULL_RETURN(paragraphManager_, false);
    auto paragraphs = paragraphManager_->GetParagraphs();
    float paragraphNewWidth =
        std::min(std::min(paragraphManager_->GetTextWidthIncludeIndent(), paragraphManager_->GetMaxWidth()),
            GetMaxMeasureSize(contentConstraint).Width());
    paragraphNewWidth =
        std::clamp(paragraphNewWidth, contentConstraint.minSize.Width(), contentConstraint.maxSize.Width());
    if (!contentConstraint.selfIdealSize.Width() || IsNeedParagraphReLayout()) {
        for (auto pIter = paragraphs.begin(); pIter != paragraphs.end(); pIter++) {
            auto paragraph = pIter->paragraph;
            CHECK_NULL_RETURN(paragraph, false);
            if (SystemProperties::GetTextTraceEnabled()) {
                ACE_TEXT_SCOPED_TRACE("ParagraphReLayout[NewWidth:%f][MaxWidth:%f][IndentWidth:%f][Constraint:%s]",
                    paragraphNewWidth, paragraph->GetMaxWidth(), paragraphManager_->GetTextWidthIncludeIndent(),
                    contentConstraint.ToString().c_str());
            }
            if (!NearEqual(paragraphNewWidth, paragraph->GetMaxWidth())) {
                int32_t id = -1;
                if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
                    id = Container::CurrentId();
                }
                OTHER_DURATION(id);
                paragraph->Layout(std::ceil(paragraphNewWidth));
            }
        }
    }
    return true;
}

bool MultipleParagraphLayoutAlgorithm::ReLayoutParagraphBySpan(LayoutWrapper* layoutWrapper, ParagraphStyle& paraStyle,
    const TextStyle& textStyle, std::vector<TextStyle>& textStyles)
{
    CHECK_NULL_RETURN(!spans_.empty(), false);
    auto spans = spans_.front();
    ParagraphStyle spanParagraphStyle = paraStyle;
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    bool reLayout = false;
    int32_t index = 0;
    InheritParentTextStyle(textStyle);
    for (const auto& child : spans) {
        if (!child) {
            continue;
        }
        TextStyle spanTextStyle;
        needReCreateParagraph_ |= child->UpdateSpanTextStyle(inheritTextStyle_, frameNode);
        auto style = child->GetTextStyle();
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE(
                "ReLayoutParagraphBySpan[id:%d][needReCreateParagraph_:%d][textStyleBitmap:%s][textColor:%s]",
                child->nodeId_, needReCreateParagraph_,
                style.has_value() ? style->GetReLayoutTextStyleBitmap().to_string().c_str() : "Na",
                style.has_value() ? style->GetTextColor().ColorToString().c_str() : "Na");
        }
        CHECK_NULL_RETURN(!needReCreateParagraph_, false);
        if (child->GetTextStyle().has_value()) {
            spanTextStyle = child->GetTextStyle().value();
        }
        if (index == 0) {
            auto direction = ParagraphUtil::GetTextDirection(child->content, layoutWrapper);
            spanTextStyle.SetTextDirection(direction);
            spanTextStyle.SetLocale(Localization::GetInstance()->GetFontLocale());
            paraStyle = ParagraphUtil::GetParagraphStyle(spanTextStyle);
        }
        reLayout |= spanTextStyle.NeedReLayout();
        textStyles.emplace_back(spanTextStyle);
        child->ResetReCreateAndReLayout();
        index++;
    }
    return reLayout;
}

bool MultipleParagraphLayoutAlgorithm::ImageSpanMeasure(const RefPtr<ImageSpanItem>& imageSpanItem,
    const RefPtr<LayoutWrapper>& layoutWrapper, const LayoutConstraintF& layoutConstrain, const TextStyle& textStyle)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, true);
    auto id = frameNode->GetId();
    int32_t targetId = imageSpanItem->nodeId_;
    if (!isSpanStringMode_) {
        CHECK_NULL_RETURN(id == targetId, true);
    }
    layoutWrapper->Measure(layoutConstrain);
    PlaceholderStyle placeholderStyle;
    auto baselineOffset = Dimension(0.0f);
    auto imageLayoutProperty = DynamicCast<ImageLayoutProperty>(layoutWrapper->GetLayoutProperty());
    if (imageLayoutProperty) {
        placeholderStyle.verticalAlign = imageLayoutProperty->GetVerticalAlign().value_or(VerticalAlign::BOTTOM);
        baselineOffset = imageLayoutProperty->GetBaselineOffset().value_or(Dimension(0.0f));
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    placeholderStyle.width = geometryNode->GetMarginFrameSize().Width();
    placeholderStyle.height = geometryNode->GetMarginFrameSize().Height();
    placeholderStyle.baselineOffset = baselineOffset.ConvertToPxDistribute(
        textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    return imageSpanItem->UpdatePlaceholderRun(placeholderStyle);
}

bool MultipleParagraphLayoutAlgorithm::CustomSpanMeasure(
    const RefPtr<CustomSpanItem>& customSpanItem, LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto theme = context->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto width = 0.0f;
    auto height = 0.0f;
    auto fontSize = theme->GetTextStyle().GetFontSize().ConvertToVp() * context->GetFontScale();
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutProperty);
    auto fontSizeOpt = textLayoutProperty->GetFontSize();
    if (fontSizeOpt.has_value()) {
        fontSize = fontSizeOpt.value().ConvertToVp() * context->GetFontScale();
    }
    if (customSpanItem->onMeasure.has_value()) {
        auto onMeasure = customSpanItem->onMeasure.value();
        CustomSpanMetrics customSpanMetrics = onMeasure({ fontSize });
        width = static_cast<float>(customSpanMetrics.width * context->GetDipScale());
        height = static_cast<float>(
            customSpanMetrics.height.value_or(fontSize / context->GetFontScale()) * context->GetDipScale());
    }
    PlaceholderStyle placeholderStyle;
    placeholderStyle.width = width;
    placeholderStyle.height = height;
    placeholderStyle.verticalAlign = VerticalAlign::NONE;
    return customSpanItem->UpdatePlaceholderRun(placeholderStyle);
}

bool MultipleParagraphLayoutAlgorithm::PlaceholderSpanMeasure(const RefPtr<PlaceholderSpanItem>& placeholderSpanItem,
    const RefPtr<LayoutWrapper>& layoutWrapper, const LayoutConstraintF& layoutConstrain)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, true);
    auto id = frameNode->GetId();
    int32_t targetId = placeholderSpanItem->placeholderSpanNodeId;
    CHECK_NULL_RETURN(id == targetId, true);
    // find the Corresponding ImageNode for every ImageSpanItem
    layoutWrapper->Measure(layoutConstrain);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    PlaceholderStyle placeholderStyle;
    placeholderStyle.width = geometryNode->GetMarginFrameSize().Width();
    placeholderStyle.height = geometryNode->GetMarginFrameSize().Height();
    placeholderStyle.verticalAlign = VerticalAlign::NONE;
    return placeholderSpanItem->UpdatePlaceholderRun(placeholderStyle);
}

void MultipleParagraphLayoutAlgorithm::MeasureChildren(LayoutWrapper* layoutWrapper, const TextStyle& textStyle)
{
    CHECK_NULL_VOID(!spans_.empty());
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& layoutConstrain = layoutProperty->CreateChildConstraint();
    auto placeHolderLayoutConstrain = layoutConstrain;
    placeHolderLayoutConstrain.maxSize.SetHeight(Infinity<float>());
    placeHolderLayoutConstrain.percentReference.SetHeight(0);
    const auto& children = GetAllChildrenWithBuild(layoutWrapper);
    auto iterItems = children.begin();
    bool needReCreateParagraph = false;
    int32_t itemIndex = -1;
    for (const auto& group : spans_) {
        for (const auto& child : group) {
            itemIndex++;
            if (!child) {
                needReCreateParagraph = true;
                continue;
            }
            needReCreateParagraph |= child->CheckSpanNeedReCreate(itemIndex);
            switch (child->spanItemType) {
                case SpanItemType::NORMAL:
                    break;
                case SpanItemType::IMAGE: {
                    if (iterItems == children.end() || !(*iterItems)) {
                        continue;
                    }
                    auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(child);
                    if (!imageSpanItem) {
                        continue;
                    }
                    needReCreateParagraph |= ImageSpanMeasure(imageSpanItem, (*iterItems), layoutConstrain, textStyle);
                    ++iterItems;
                    break;
                }
                case SpanItemType::CustomSpan: {
                    auto customSpanItem = AceType::DynamicCast<CustomSpanItem>(child);
                    if (!customSpanItem) {
                        continue;
                    }
                    needReCreateParagraph |= CustomSpanMeasure(customSpanItem, layoutWrapper);
                    if (customSpanItem->isFrameNode) {
                        ++iterItems; // CAPI custom span is frameNode，need to move the iterator backwards
                    }
                    break;
                }
                case SpanItemType::PLACEHOLDER: {
                    if (iterItems == children.end() || !(*iterItems)) {
                        continue;
                    }
                    auto placeholderSpanItem = AceType::DynamicCast<PlaceholderSpanItem>(child);
                    if (!placeholderSpanItem) {
                        continue;
                    }
                    needReCreateParagraph |=
                        PlaceholderSpanMeasure(placeholderSpanItem, (*iterItems), placeHolderLayoutConstrain);
                    ++iterItems;
                    break;
                }
                case SpanItemType::SYMBOL:
                    break;
            }
        }
    }
    CHECK_NULL_VOID(needReCreateParagraph);
    layoutProperty->OnPropertyChangeMeasure();
}

ChildrenListWithGuard MultipleParagraphLayoutAlgorithm::GetAllChildrenWithBuild(LayoutWrapper* layoutWrapper)
{
    return layoutWrapper->GetAllChildrenWithBuild();
}

bool MultipleParagraphLayoutAlgorithm::UpdateParagraphBySpan(
    LayoutWrapper* layoutWrapper, ParagraphStyle paraStyle, double maxWidth, const TextStyle& textStyle)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    InheritParentTextStyle(textStyle);
    const auto& children = GetAllChildrenWithBuild(layoutWrapper);
    auto iterItems = children.begin();
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto aiSpanMap = pattern->GetAISpanMap();
    int32_t spanTextLength = 0;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholderInfo;
    int32_t paragraphIndex = -1;
    preParagraphsPlaceholderCount_ = 0;
    currentParagraphPlaceholderCount_ = 0;
    auto maxLines = static_cast<int32_t>(paraStyle.maxLines);
    for (auto groupIt = spans_.begin(); groupIt != spans_.end(); groupIt++) {
        auto& group = *(groupIt);
        ParagraphStyle spanParagraphStyle = paraStyle;
        if (paraStyle.maxLines != UINT32_MAX) {
            if (!paragraphManager_->GetParagraphs().empty()) {
                maxLines -= static_cast<int32_t>(paragraphManager_->GetParagraphs().back().paragraph->GetLineCount());
            }
            spanParagraphStyle.maxLines = std::max(maxLines, 0);
        }
        RefPtr<SpanItem> paraStyleSpanItem = GetParagraphStyleSpanItem(group);
        if (paraStyleSpanItem) {
            ParagraphUtil::GetSpanParagraphStyle(layoutWrapper, paraStyleSpanItem, spanParagraphStyle);
            if (paraStyleSpanItem->fontStyle->HasFontSize()) {
                spanParagraphStyle.fontSize = paraStyleSpanItem->fontStyle->GetFontSizeValue().ConvertToPxDistribute(
                    textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
            }
            spanParagraphStyle.isEndAddParagraphSpacing =
                paraStyleSpanItem->textLineStyle->HasParagraphSpacing() &&
                Positive(paraStyleSpanItem->textLineStyle->GetParagraphSpacingValue().ConvertToPx()) &&
                std::next(groupIt) != spans_.end();
            spanParagraphStyle.isFirstParagraphLineSpacing = (groupIt == spans_.begin());
        }
        auto&& paragraph = GetOrCreateParagraph(group, spanParagraphStyle, aiSpanMap);
        CHECK_NULL_RETURN(paragraph, false);
        auto paraStart = spanTextLength;
        paragraphIndex++;
        for (const auto& child : group) {
            if (!child) {
                continue;
            }
            child->paragraphIndex = paragraphIndex;
            child->SetTextPattern(pattern);
            switch (child->spanItemType) {
                case SpanItemType::NORMAL:
                    child->aiSpanMap = aiSpanMap;
                    AddTextSpanToParagraph(child, spanTextLength, frameNode, paragraph);
                    aiSpanMap = child->aiSpanMap;
                    break;
                case SpanItemType::IMAGE: {
                    if (iterItems == children.end() || !(*iterItems)) {
                        continue;
                    }
                    auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(child);
                    if (!imageSpanItem) {
                        continue;
                    }
                    AddImageToParagraph(imageSpanItem, (*iterItems), paragraph, spanTextLength);
                    auto imageNode = (*iterItems)->GetHostNode();
                    imageNodeList.emplace_back(WeakClaim(RawPtr(imageNode)));
                    iterItems++;
                    break;
                }
                case SpanItemType::CustomSpan: {
                    auto customSpanItem = AceType::DynamicCast<CustomSpanItem>(child);
                    if (!customSpanItem) {
                        continue;
                    }
                    CustomSpanPlaceholderInfo customSpanPlaceholder;
                    customSpanPlaceholder.paragraphIndex = paragraphIndex;
                    UpdateParagraphByCustomSpan(customSpanItem, paragraph, spanTextLength, customSpanPlaceholder);
                    customSpanPlaceholderInfo.emplace_back(customSpanPlaceholder);
                    if (customSpanItem->isFrameNode) {
                        iterItems++; // CAPI custom span is frameNode，need to move the iterator backwards
                    }
                    break;
                }
                case SpanItemType::PLACEHOLDER: {
                    if (iterItems == children.end() || !(*iterItems)) {
                        continue;
                    }
                    auto placeholderSpanItem = AceType::DynamicCast<PlaceholderSpanItem>(child);
                    if (!placeholderSpanItem) {
                        continue;
                    }
                    AddPlaceHolderToParagraph(placeholderSpanItem, (*iterItems), paragraph, spanTextLength);
                    iterItems++;
                    break;
                }
                case SpanItemType::SYMBOL:
                    AddSymbolSpanToParagraph(child, spanTextLength, frameNode, paragraph);
            }
            child->ResetReCreateAndReLayout();
        }
        preParagraphsPlaceholderCount_ += currentParagraphPlaceholderCount_;
        currentParagraphPlaceholderCount_ = 0;
        shadowOffset_ += GetShadowOffset(group);
        if (!useParagraphCache_) {
            HandleEmptyParagraph(paragraph, group);
            paragraph->Build();
            ParagraphUtil::ApplyIndent(spanParagraphStyle, paragraph, maxWidth, textStyle);
            UpdateSymbolSpanEffect(frameNode, paragraph, group);
        }
        if (paraStyle.maxLines != UINT32_MAX) {
            paragraph->Layout(static_cast<float>(maxWidth));
        }
        paragraphManager_->AddParagraph({ .paragraph = paragraph,
            .paragraphStyle = spanParagraphStyle,
            .start = paraStart,
            .end = spanTextLength });
    }
    pattern->SetImageSpanNodeList(imageNodeList);
    pattern->InitCustomSpanPlaceholderInfo(customSpanPlaceholderInfo);
    return true;
}

void MultipleParagraphLayoutAlgorithm::InheritParentTextStyle(const TextStyle& textStyle)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        inheritTextStyle_ = textStyle;
    }
    inheritTextStyle_.SetMaxLines(textStyle.GetMaxLines());
    inheritTextStyle_.ResetTextBaselineOffset();
}

void MultipleParagraphLayoutAlgorithm::AddSymbolSpanToParagraph(const RefPtr<SpanItem>& child, int32_t& spanTextLength,
    const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph)
{
    child->SetIsParentText(frameNode->GetTag() == V2::TEXT_ETS_TAG);
    auto pattern = frameNode->GetPattern<TextPattern>();
    child->UpdateSymbolSpanParagraph(frameNode, inheritTextStyle_, paragraph, pattern && pattern->IsDragging());
    spanTextLength += SYMBOL_SPAN_LENGTH;
    child->length = SYMBOL_SPAN_LENGTH;
    child->position = spanTextLength;
    child->content = u"  ";
}

void MultipleParagraphLayoutAlgorithm::AddTextSpanToParagraph(const RefPtr<SpanItem>& child, int32_t& spanTextLength,
    const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph)
{
    child->length = child->content.length();
    spanTextLength += static_cast<int32_t>(child->length);
    child->position = spanTextLength;
    child->UpdateParagraph(frameNode, paragraph, inheritTextStyle_, isMarquee_);
}

void MultipleParagraphLayoutAlgorithm::AddImageToParagraph(RefPtr<ImageSpanItem>& imageSpanItem,
    const RefPtr<LayoutWrapper>& layoutWrapper, const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto id = frameNode->GetId();
    int32_t targetId = imageSpanItem->nodeId_;
    if (!isSpanStringMode_) {
        CHECK_NULL_VOID(id == targetId);
    }
    imageSpanItem->placeholderIndex = imageSpanItem->UpdateParagraph(frameNode, paragraph, inheritTextStyle_);
    currentParagraphPlaceholderCount_++;
    imageSpanItem->placeholderIndex += preParagraphsPlaceholderCount_;
    imageSpanItem->content = u" ";
    spanTextLength += 1;
    imageSpanItem->position = spanTextLength;
    imageSpanItem->length = 1;
}

void MultipleParagraphLayoutAlgorithm::AddPlaceHolderToParagraph(RefPtr<PlaceholderSpanItem>& placeholderSpanItem,
    const RefPtr<LayoutWrapper>& layoutWrapper, const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto id = frameNode->GetId();
    int32_t targetId = placeholderSpanItem->placeholderSpanNodeId;
    CHECK_NULL_VOID(id == targetId);
    placeholderSpanItem->placeholderIndex =
        placeholderSpanItem->UpdateParagraph(frameNode, paragraph, inheritTextStyle_);
    currentParagraphPlaceholderCount_++;
    placeholderSpanItem->placeholderIndex += preParagraphsPlaceholderCount_;
    placeholderSpanItem->content = u" ";
    spanTextLength += 1;
    placeholderSpanItem->length = 1;
    placeholderSpanItem->position = spanTextLength;
}

void MultipleParagraphLayoutAlgorithm::UpdateParagraphByCustomSpan(RefPtr<CustomSpanItem>& customSpanItem,
    const RefPtr<Paragraph>& paragraph, int32_t& spanTextLength, CustomSpanPlaceholderInfo& customSpanPlaceholder)
{
    customSpanItem->placeholderIndex = customSpanItem->UpdateParagraph(nullptr, paragraph, inheritTextStyle_);
    currentParagraphPlaceholderCount_++;
    customSpanItem->placeholderIndex += preParagraphsPlaceholderCount_;
    customSpanItem->content = u" ";
    spanTextLength += 1;
    customSpanItem->length = 1;
    customSpanItem->position = spanTextLength;
    if (customSpanItem->onDraw.has_value()) {
        customSpanPlaceholder.onDraw = customSpanItem->onDraw.value();
    }
    customSpanPlaceholder.customSpanIndex = customSpanItem->placeholderIndex;
}

void MultipleParagraphLayoutAlgorithm::UpdateSymbolSpanEffect(
    RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& paragraph, const std::list<RefPtr<SpanItem>>& spans)
{
    for (const auto& child : spans) {
        if (!child || child->unicode == 0) {
            continue;
        }
        if (child->GetTextStyle()->isSymbolGlyph_) {
            paragraph->SetParagraphSymbolAnimation(frameNode);
            return;
        }
    }
}

SizeF MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(const LayoutConstraintF& contentConstraint)
{
    auto maxSize = contentConstraint.selfIdealSize;
    maxSize.UpdateIllegalSizeWithCheck(contentConstraint.maxSize);
    return maxSize.ConvertToSizeT();
}

void MultipleParagraphLayoutAlgorithm::MeasureWithFixAtIdealSize(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto widthPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, true);
    auto heightPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, false);
    if (widthPolicy != LayoutCalPolicy::FIX_AT_IDEAL_SIZE && heightPolicy != LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        return;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto& content = geometryNode->GetContent();
    CHECK_NULL_VOID(content);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto contentSize = content->GetRect().GetSize();
    AddPaddingToSize(padding, contentSize);
    OptionalSizeF frameSize;
    frameSize.UpdateIllegalSizeWithCheck(contentSize);
    frameSize = UpdateOptionSizeByCalcLayoutConstraint(
        frameSize, layoutProperty->GetCalcLayoutConstraint(), layoutProperty->GetLayoutConstraint()->percentReference);
    auto fixSize = frameSize.ConvertToSizeT();
    auto measureSize = geometryNode->GetFrameSize();
    if (widthPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        measureSize.SetWidth(fixSize.Width());
    }
    if (heightPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        measureSize.SetHeight(fixSize.Height());
    }
    geometryNode->SetFrameSize(measureSize);
}

void MultipleParagraphLayoutAlgorithm::MeasureWithMatchParent(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicyProperty = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicyProperty);
    auto widthLayoutPolicy = layoutPolicyProperty.value().widthLayoutPolicy_;
    auto heightLayoutPolicy = layoutPolicyProperty.value().heightLayoutPolicy_;
    if (widthLayoutPolicy != LayoutCalPolicy::MATCH_PARENT && heightLayoutPolicy != LayoutCalPolicy::MATCH_PARENT) {
        return;
    }
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(layoutConstraint.value(),
        widthLayoutPolicy.value_or(LayoutCalPolicy::NO_MATCH), heightLayoutPolicy.value_or(LayoutCalPolicy::NO_MATCH),
        Axis::HORIZONTAL);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    OptionalSizeF frameSize(geometryNode->GetFrameSize());
    frameSize.UpdateSizeWithCheck(layoutPolicySize.ConvertToSizeT());
    auto constraintSize = UpdateOptionSizeByCalcLayoutConstraint(
        frameSize, layoutProperty->GetCalcLayoutConstraint(), layoutConstraint->percentReference);
    if (widthLayoutPolicy == LayoutCalPolicy::MATCH_PARENT) {
        layoutWrapper->GetGeometryNode()->SetFrameWidth(constraintSize.ConvertToSizeT().Width());
    }
    if (heightLayoutPolicy == LayoutCalPolicy::MATCH_PARENT) {
        layoutWrapper->GetGeometryNode()->SetFrameHeight(constraintSize.ConvertToSizeT().Height());
    }
}
} // namespace OHOS::Ace::NG
