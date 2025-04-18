/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "constants_converter.h"

#include "rosen_text/hm_symbol_txt.h"
#include "rosen_text/typography_create.h"
#include "rosen_text/typography_style.h"

#include "base/i18n/localization.h"

namespace OHOS::Ace::Constants {
namespace {
const std::string FONTWEIGHT = "wght";
constexpr float DEFAULT_MULTIPLE = 100.0f;
constexpr float MIN_FONT_WEIGHT = 100.0f;
constexpr float DEFAULT_FONT_WEIGHT = 400.0f;
constexpr float MAX_FONT_WEIGHT = 900.0f;
constexpr int32_t SCALE_EFFECT = 2;
constexpr int32_t NONE_EFFECT = 0;
constexpr float ORIGINAL_LINE_HEIGHT_SCALE = 1.0f;
const std::string DEFAULT_SYMBOL_FONTFAMILY = "HM Symbol";
} // namespace

Rosen::FontWeight ConvertTxtFontWeight(FontWeight fontWeight)
{
    Rosen::FontWeight convertValue;
    switch (fontWeight) {
        case FontWeight::W100:
        case FontWeight::LIGHTER:
            convertValue = Rosen::FontWeight::W100;
            break;
        case FontWeight::W200:
            convertValue = Rosen::FontWeight::W200;
            break;
        case FontWeight::W300:
            convertValue = Rosen::FontWeight::W300;
            break;
        case FontWeight::W400:
        case FontWeight::NORMAL:
        case FontWeight::REGULAR:
            convertValue = Rosen::FontWeight::W400;
            break;
        case FontWeight::W500:
        case FontWeight::MEDIUM:
            convertValue = Rosen::FontWeight::W500;
            break;
        case FontWeight::W600:
            convertValue = Rosen::FontWeight::W600;
            break;
        case FontWeight::W700:
        case FontWeight::BOLD:
            convertValue = Rosen::FontWeight::W700;
            break;
        case FontWeight::W800:
            convertValue = Rosen::FontWeight::W800;
            break;
        case FontWeight::W900:
        case FontWeight::BOLDER:
            convertValue = Rosen::FontWeight::W900;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "FontWeight setting error! Now using default FontWeight.");
            convertValue = Rosen::FontWeight::W400;
            break;
    }
    return convertValue;
}

Rosen::SymbolType ConvertTxtSymbolType(SymbolType symbolType)
{
    Rosen::SymbolType txtSymbolType;
    switch (symbolType) {
        case SymbolType::SYSTEM:
            txtSymbolType = Rosen::SymbolType::SYSTEM;
            break;
        case SymbolType::CUSTOM:
            txtSymbolType = Rosen::SymbolType::CUSTOM;
            break;
        default:
            LOGE("SymbolType setting error! Now using default SymbolType.");
            txtSymbolType = Rosen::SymbolType::SYSTEM;
            break;
    }
    return txtSymbolType;
}

Rosen::FontStyle ConvertTxtFontStyle(FontStyle fontStyle)
{
    Rosen::FontStyle convertValue;
    switch (fontStyle) {
        case FontStyle::NORMAL:
            convertValue = Rosen::FontStyle::NORMAL;
            break;
        case FontStyle::ITALIC:
            convertValue = Rosen::FontStyle::ITALIC;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "FontStyle setting error! Now using default FontStyle");
            convertValue = Rosen::FontStyle::NORMAL;
            break;
    }
    return convertValue;
}

Rosen::TextBaseline ConvertTxtTextBaseline(TextBaseline textBaseline)
{
    Rosen::TextBaseline convertValue;
    switch (textBaseline) {
        case TextBaseline::ALPHABETIC:
            convertValue = Rosen::TextBaseline::ALPHABETIC;
            break;
        case TextBaseline::IDEOGRAPHIC:
            convertValue = Rosen::TextBaseline::IDEOGRAPHIC;
            break;
        default:
            convertValue = Rosen::TextBaseline::ALPHABETIC;
            break;
    }
    return convertValue;
}

Rosen::TextAlign ConvertTxtTextAlign(TextAlign textAlign)
{
    Rosen::TextAlign convertValue;
    switch (textAlign) {
        case TextAlign::LEFT:
            convertValue = Rosen::TextAlign::LEFT;
            break;
        case TextAlign::RIGHT:
            convertValue = Rosen::TextAlign::RIGHT;
            break;
        case TextAlign::CENTER:
            convertValue = Rosen::TextAlign::CENTER;
            break;
        case TextAlign::JUSTIFY:
            convertValue = Rosen::TextAlign::JUSTIFY;
            break;
        case TextAlign::START:
            convertValue = Rosen::TextAlign::START;
            break;
        case TextAlign::END:
            convertValue = Rosen::TextAlign::END;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "TextAlign setting error! Now using default TextAlign");
            convertValue = Rosen::TextAlign::START;
            break;
    }
    return convertValue;
}

Rosen::TextRectHeightStyle ConvertTxtRectHeightStyle(RectHeightStyle heightStyle)
{
    switch (heightStyle) {
        case RectHeightStyle::TIGHT:
            return Rosen::TextRectHeightStyle::TIGHT;
        case RectHeightStyle::MAX:
            return Rosen::TextRectHeightStyle::COVER_TOP_AND_BOTTOM;
        case RectHeightStyle::INCLUDE_LINE_SPACE_MIDDLE:
            return Rosen::TextRectHeightStyle::COVER_HALF_TOP_AND_BOTTOM;
        case RectHeightStyle::INCLUDE_LINE_SPACE_TOP:
            return Rosen::TextRectHeightStyle::COVER_TOP;
        case RectHeightStyle::INCLUDE_LINE_SPACE_BOTTOM:
            return Rosen::TextRectHeightStyle::COVER_BOTTOM;
        case RectHeightStyle::STRUT:
            return Rosen::TextRectHeightStyle::FOLLOW_BY_STRUT;
        default:
            return Rosen::TextRectHeightStyle::TIGHT;
    }
}

Rosen::TextRectWidthStyle ConvertTxtRectWidthStyle(RectWidthStyle widthStyle)
{
    switch (widthStyle) {
        case RectWidthStyle::TIGHT:
            return Rosen::TextRectWidthStyle::TIGHT;
        case RectWidthStyle::MAX:
            return Rosen::TextRectWidthStyle::MAX;
        default:
            return Rosen::TextRectWidthStyle::TIGHT;
    }
}

Rosen::TextDirection ConvertTxtTextDirection(TextDirection textDirection)
{
    Rosen::TextDirection convertValue;
    switch (textDirection) {
        case TextDirection::RTL:
            convertValue = Rosen::TextDirection::RTL;
            break;
        case TextDirection::LTR:
            convertValue = Rosen::TextDirection::LTR;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "TextDirection setting error! Now using default TextDirection");
            convertValue = Rosen::TextDirection::LTR;
            break;
    }
    return convertValue;
}

SkColor ConvertSkColor(Color color)
{
    return color.GetValue();
}

Rosen::TextDecoration ConvertTxtTextDecoration(TextDecoration textDecoration)
{
    Rosen::TextDecoration convertValue = Rosen::TextDecoration::NONE;
    switch (textDecoration) {
        case TextDecoration::NONE:
            convertValue = Rosen::TextDecoration::NONE;
            break;
        case TextDecoration::UNDERLINE:
            convertValue = Rosen::TextDecoration::UNDERLINE;
            break;
        case TextDecoration::OVERLINE:
            convertValue = Rosen::TextDecoration::OVERLINE;
            break;
        case TextDecoration::LINE_THROUGH:
            convertValue = Rosen::TextDecoration::LINE_THROUGH;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "TextDecoration setting error! Now using default TextDecoration");
            break;
    }
    return convertValue;
}
Rosen::TextDecorationStyle ConvertTxtTextDecorationStyle(TextDecorationStyle textDecorationStyle)
{
    Rosen::TextDecorationStyle convertValue = Rosen::TextDecorationStyle::SOLID;
    switch (textDecorationStyle) {
        case TextDecorationStyle::SOLID:
            convertValue = Rosen::TextDecorationStyle::SOLID;
            break;
        case TextDecorationStyle::DOUBLE:
            convertValue = Rosen::TextDecorationStyle::DOUBLE;
            break;
        case TextDecorationStyle::DOTTED:
            convertValue = Rosen::TextDecorationStyle::DOTTED;
            break;
        case TextDecorationStyle::DASHED:
            convertValue = Rosen::TextDecorationStyle::DASHED;
            break;
        case TextDecorationStyle::WAVY:
            convertValue = Rosen::TextDecorationStyle::WAVY;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "TextDecorationStyle setting error! Now using default TextDecorationStyle");
            break;
    }
    return convertValue;
}

double NormalizeToPx(const Dimension& dimension)
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * SystemProperties::GetResolution());
    }
    return dimension.Value();
}

void ConvertTxtStyle(const TextStyle& textStyle, Rosen::TextStyle& txtStyle)
{
    txtStyle.color = ConvertSkColor(textStyle.GetTextColor());
    txtStyle.fontWeight = ConvertTxtFontWeight(textStyle.GetFontWeight());

    txtStyle.fontSize = NormalizeToPx(textStyle.GetFontSize());

    txtStyle.fontStyle = ConvertTxtFontStyle(textStyle.GetFontStyle());

    if (textStyle.GetWordSpacing().Unit() == DimensionUnit::PERCENT) {
        txtStyle.wordSpacing = textStyle.GetWordSpacing().Value() * txtStyle.fontSize;
    } else {
        txtStyle.wordSpacing = NormalizeToPx(textStyle.GetWordSpacing());
    }

    txtStyle.letterSpacing = NormalizeToPx(textStyle.GetLetterSpacing());
    txtStyle.baseLineShift = -NormalizeToPx(textStyle.GetBaselineOffset());
    txtStyle.fontFamilies = textStyle.GetFontFamilies();
    ConvertSymbolTxtStyle(textStyle, txtStyle);
    txtStyle.baseline = ConvertTxtTextBaseline(textStyle.GetTextBaseline());
    txtStyle.decoration = ConvertTxtTextDecoration(textStyle.GetTextDecoration());
    txtStyle.decorationColor = ConvertSkColor(textStyle.GetTextDecorationColor());
    txtStyle.decorationStyle = ConvertTxtTextDecorationStyle(textStyle.GetTextDecorationStyle());
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    txtStyle.halfLeading = textStyle.GetHalfLeading();

    for (auto& spanShadow : textStyle.GetTextShadows()) {
        Rosen::TextShadow txtShadow;
        txtShadow.color = spanShadow.GetColor().GetValue();
        txtShadow.offset.SetX(spanShadow.GetOffset().GetX());
        txtShadow.offset.SetY(spanShadow.GetOffset().GetY());
        txtShadow.blurRadius = spanShadow.GetBlurRadius();
        txtStyle.shadows.emplace_back(txtShadow);
    }

    if (textStyle.GetLineHeight().Unit() == DimensionUnit::PERCENT) {
        txtStyle.heightOnly = true;
        txtStyle.heightScale = textStyle.GetLineHeight().Value();
    } else {
        double fontSize = txtStyle.fontSize;
        double lineHeight = textStyle.GetLineHeight().Value();

        lineHeight = NormalizeToPx(textStyle.GetLineHeight());

        txtStyle.heightOnly = textStyle.HasHeightOverride();
        if (!NearEqual(lineHeight, fontSize) && (lineHeight > 0.0) && (!NearZero(fontSize))) {
            txtStyle.heightScale = lineHeight / fontSize;
        } else {
            txtStyle.heightScale = 1;
            if (NearZero(lineHeight) || NearEqual(lineHeight, fontSize)) {
                txtStyle.heightOnly = false;
            }
        }
    }

    // set font variant
    auto fontFeatures = textStyle.GetFontFeatures();
    if (!fontFeatures.empty()) {
        Rosen::FontFeatures features;
        for (auto iter = fontFeatures.begin(); iter != fontFeatures.end(); ++iter) {
            features.SetFeature(iter->first, iter->second);
        }
        txtStyle.fontFeatures = features;
    }
    auto textBackgroundStyle = textStyle.GetTextBackgroundStyle();
    CHECK_NULL_VOID(textBackgroundStyle.has_value());
    txtStyle.styleId = textBackgroundStyle->groupId;
    if (textBackgroundStyle->backgroundColor.has_value()) {
        txtStyle.backgroundRect.color = textBackgroundStyle->backgroundColor.value().GetValue();
    }
    auto radius = textBackgroundStyle->backgroundRadius;
    CHECK_NULL_VOID(radius.has_value());
    auto radiusConverter = [](const std::optional<Dimension>& radius) -> double {
        CHECK_NULL_RETURN(radius.has_value(), 0);
        return NormalizeToPx(radius.value());
    };
    txtStyle.backgroundRect.leftTopRadius = radiusConverter(radius->radiusTopLeft);
    txtStyle.backgroundRect.rightTopRadius = radiusConverter(radius->radiusTopRight);
    txtStyle.backgroundRect.leftBottomRadius = radiusConverter(radius->radiusBottomLeft);
    txtStyle.backgroundRect.rightBottomRadius = radiusConverter(radius->radiusBottomRight);
}

void ConvertTxtStyle(const TextStyle& textStyle, const WeakPtr<PipelineBase>& context, Rosen::TextStyle& txtStyle)
{
    txtStyle.relayoutChangeBitmap = textStyle.GetReLayoutTextStyleBitmap();
    txtStyle.textStyleUid  = static_cast<unsigned long>(textStyle.GetTextStyleUid());
    txtStyle.color = ConvertSkColor(textStyle.GetTextColor());
    txtStyle.fontWeight = ConvertTxtFontWeight(textStyle.GetFontWeight());
    txtStyle.symbol.SetSymbolType(ConvertTxtSymbolType(textStyle.GetSymbolType()));
    auto fontWeightValue = (static_cast<int32_t>(
            ConvertTxtFontWeight(textStyle.GetFontWeight())) + 1) * DEFAULT_MULTIPLE;
    auto pipelineContext = context.Upgrade();
    if (pipelineContext) {
        fontWeightValue = fontWeightValue * pipelineContext->GetFontWeightScale();
    }
    if (textStyle.GetEnableVariableFontWeight()) {
        fontWeightValue = textStyle.GetVariableFontWeight();
        if (LessNotEqual(fontWeightValue, MIN_FONT_WEIGHT) || GreatNotEqual(fontWeightValue, MAX_FONT_WEIGHT)) {
            fontWeightValue = DEFAULT_FONT_WEIGHT;
        }
    }
    txtStyle.fontVariations.SetAxisValue(FONTWEIGHT, fontWeightValue);
    // Font size must be px when transferring to Rosen::TextStyle
    txtStyle.fontSize = textStyle.GetFontSize().ConvertToPxDistribute(
        textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    txtStyle.fontStyle = ConvertTxtFontStyle(textStyle.GetFontStyle());

    if (textStyle.GetWordSpacing().Unit() == DimensionUnit::PERCENT) {
        txtStyle.wordSpacing = textStyle.GetWordSpacing().Value() * txtStyle.fontSize;
    } else {
        if (pipelineContext) {
            txtStyle.wordSpacing = textStyle.GetWordSpacing().ConvertToPxDistribute(
                textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        } else {
            txtStyle.wordSpacing = textStyle.GetWordSpacing().Value();
        }
    }
    if (pipelineContext) {
        txtStyle.letterSpacing = textStyle.GetLetterSpacing().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        txtStyle.baseLineShift = -textStyle.GetBaselineOffset().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    }

    txtStyle.fontFamilies = textStyle.GetFontFamilies();
    ConvertSymbolTxtStyle(textStyle, txtStyle);
    txtStyle.baseline = ConvertTxtTextBaseline(textStyle.GetTextBaseline());
    txtStyle.decoration = ConvertTxtTextDecoration(textStyle.GetTextDecoration());
    txtStyle.decorationColor = ConvertSkColor(textStyle.GetTextDecorationColor());
    txtStyle.decorationStyle = ConvertTxtTextDecorationStyle(textStyle.GetTextDecorationStyle());
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    txtStyle.halfLeading = textStyle.GetHalfLeading();

    for (auto& spanShadow : textStyle.GetTextShadows()) {
        Rosen::TextShadow txtShadow;
        txtShadow.color = spanShadow.GetColor().GetValue();
        txtShadow.offset.SetX(spanShadow.GetOffset().GetX());
        txtShadow.offset.SetY(spanShadow.GetOffset().GetY());
        txtShadow.blurRadius = spanShadow.GetBlurRadius();
        txtStyle.shadows.emplace_back(txtShadow);
    }

    double lineHeightScale = 0.0;
    double lineSpacingScale = 0.0;
    bool lineHeightOnly = false;
    bool lineSpacingOnly = false;
    if (textStyle.GetLineHeight().Unit() == DimensionUnit::PERCENT) {
        lineHeightOnly = true;
        lineHeightScale = textStyle.GetLineHeight().Value();
    } else {
        double fontSize = txtStyle.fontSize;
        double lineHeight = textStyle.GetLineHeight().Value();
        if (pipelineContext) {
            lineHeight = textStyle.GetLineHeight().ConvertToPxDistribute(
                textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        }
        lineHeightOnly = textStyle.HasHeightOverride();
        if (!NearEqual(lineHeight, fontSize) && (lineHeight > 0.0) && (!NearZero(fontSize))) {
            lineHeightScale = lineHeight / fontSize;
        } else {
            lineHeightScale = 1;
            static const int32_t BEGIN_VERSION = 6;
            auto isBeginVersion = pipelineContext && pipelineContext->GetMinPlatformVersion() >= BEGIN_VERSION;
            if (NearZero(lineHeight) || (!isBeginVersion && NearEqual(lineHeight, fontSize))) {
                lineHeightOnly = false;
            }
        }
    }
    if (textStyle.GetLineSpacing().Unit() == DimensionUnit::PERCENT) {
        lineSpacingOnly = true;
        lineSpacingScale = textStyle.GetLineSpacing().Value();
    } else {
        double fontSize = txtStyle.fontSize;
        double lineSpacing = textStyle.GetLineSpacing().Value();
        if (pipelineContext) {
            lineSpacing = textStyle.GetLineSpacing().ConvertToPxDistribute(
                textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        }
        lineSpacingOnly = true;
        if (!NearEqual(lineSpacing, fontSize) && (lineSpacing > 0.0) && (!NearZero(fontSize))) {
            lineSpacingScale = lineSpacing / fontSize;
        } else {
            lineSpacingScale = 1;
            if (NearZero(lineSpacing)) {
                lineSpacingOnly = false;
            }
        }
    }

    txtStyle.heightOnly = lineHeightOnly || lineSpacingOnly;
    if (lineHeightOnly && lineSpacingOnly) {
        txtStyle.heightScale = lineHeightScale + lineSpacingScale;
    } else if (lineHeightOnly && !lineSpacingOnly) {
        txtStyle.heightScale = lineHeightScale;
    } else if (!lineHeightOnly && lineSpacingOnly) {
        txtStyle.heightScale = ORIGINAL_LINE_HEIGHT_SCALE + lineSpacingScale;
    } else {
        txtStyle.heightScale = 1;
    }

    // set font variant
    auto fontFeatures = textStyle.GetFontFeatures();
    if (!fontFeatures.empty()) {
        Rosen::FontFeatures features;
        for (auto iter = fontFeatures.begin(); iter != fontFeatures.end(); ++iter) {
            features.SetFeature(iter->first, iter->second);
        }
        txtStyle.fontFeatures = features;
    }
    auto textBackgroundStyle = textStyle.GetTextBackgroundStyle();
    CHECK_NULL_VOID(textBackgroundStyle.has_value());
    txtStyle.styleId = textBackgroundStyle->groupId;
    if (textBackgroundStyle->backgroundColor.has_value()) {
        txtStyle.backgroundRect.color = textBackgroundStyle->backgroundColor.value().GetValue();
    }
    auto radius = textBackgroundStyle->backgroundRadius;
    CHECK_NULL_VOID(radius.has_value());
    auto radiusConverter = [context = pipelineContext, textStyle](const std::optional<Dimension>& radius) -> double {
        CHECK_NULL_RETURN(radius.has_value(), 0);
        CHECK_NULL_RETURN(context, radius->Value());
        return radius.value().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
    };
    txtStyle.backgroundRect.leftTopRadius = radiusConverter(radius->radiusTopLeft);
    txtStyle.backgroundRect.rightTopRadius = radiusConverter(radius->radiusTopRight);
    txtStyle.backgroundRect.leftBottomRadius = radiusConverter(radius->radiusBottomLeft);
    txtStyle.backgroundRect.rightBottomRadius = radiusConverter(radius->radiusBottomRight);
}

void ConvertSymbolTxtStyle(const TextStyle& textStyle, Rosen::TextStyle& txtStyle)
{
    if (!textStyle.isSymbolGlyph_) {
        return;
    }

    txtStyle.isSymbolGlyph = true;
    txtStyle.symbol.SetRenderMode(textStyle.GetRenderStrategy());
    const std::vector<Color>& symbolColor = textStyle.GetSymbolColorList();
    std::vector<Rosen::Drawing::Color> symbolColors;
    for (size_t i = 0; i < symbolColor.size(); i++) {
        symbolColors.emplace_back(ConvertSkColor(symbolColor[i]));
    }
    txtStyle.symbol.SetRenderColor(symbolColors);
    if (textStyle.GetSymbolEffectOptions().has_value()) {
        auto options = textStyle.GetSymbolEffectOptions().value();
        auto effectType = options.GetEffectType();
        txtStyle.symbol.SetSymbolEffect(static_cast<uint32_t>(effectType));
        txtStyle.symbol.SetAnimationStart(options.GetIsTxtActive());
        if (options.GetCommonSubType().has_value()) {
            auto commonType = static_cast<uint16_t>(options.GetCommonSubType().value());
            txtStyle.symbol.SetCommonSubType(commonType == 1 ? Rosen::Drawing::DrawingCommonSubType::UP
                                                             : Rosen::Drawing::DrawingCommonSubType::DOWN);
        }
        if (effectType == SymbolEffectType::HIERARCHICAL && options.GetFillStyle().has_value()) {
            txtStyle.symbol.SetAnimationMode(static_cast<uint16_t>(options.GetFillStyle().value()));
        } else {
            if (options.GetScopeType().has_value()) {
                txtStyle.symbol.SetAnimationMode(static_cast<uint16_t>(options.GetScopeType().value()));
            }
        }
    } else {
        auto effectStrategyValue = textStyle.GetEffectStrategy();
        if (effectStrategyValue < NONE_EFFECT || effectStrategyValue > SCALE_EFFECT) {
            effectStrategyValue = NONE_EFFECT;
        }
        txtStyle.symbol.SetSymbolEffect(effectStrategyValue);
        txtStyle.symbol.SetAnimationStart(true);
    }
    if (txtStyle.symbol.GetSymbolType() != Rosen::SymbolType::CUSTOM) {
        txtStyle.fontFamilies.push_back(DEFAULT_SYMBOL_FONTFAMILY);
    }
    txtStyle.symbol.SetSymbolBitmap(textStyle.GetReLayoutSymbolStyleBitmap());
    txtStyle.symbol.SetSymbolUid(textStyle.GetSymbolUid());
}

Rect ConvertSkRect(const Rosen::Drawing::RectF& skRect)
{
    Rect result;
    result.SetLeft(skRect.GetLeft());
    result.SetTop(skRect.GetTop());
    result.SetWidth(skRect.GetWidth());
    result.SetHeight(skRect.GetHeight());
    return result;
}

Rosen::PlaceholderVerticalAlignment ConvertPlaceholderAlignment(PlaceholderAlignment textDecoration)
{
    Rosen::PlaceholderVerticalAlignment convertValue = Rosen::PlaceholderVerticalAlignment::OFFSET_AT_BASELINE;
    switch (textDecoration) {
        case PlaceholderAlignment::BASELINE:
            convertValue = Rosen::PlaceholderVerticalAlignment::OFFSET_AT_BASELINE;
            break;
        case PlaceholderAlignment::ABOVEBASELINE:
            convertValue = Rosen::PlaceholderVerticalAlignment::ABOVE_BASELINE;
            break;
        case PlaceholderAlignment::BELOWBASELINE:
            convertValue = Rosen::PlaceholderVerticalAlignment::BELOW_BASELINE;
            break;
        case PlaceholderAlignment::TOP:
            convertValue = Rosen::PlaceholderVerticalAlignment::TOP_OF_ROW_BOX;
            break;
        case PlaceholderAlignment::BOTTOM:
            convertValue = Rosen::PlaceholderVerticalAlignment::BOTTOM_OF_ROW_BOX;
            break;
        case PlaceholderAlignment::MIDDLE:
            convertValue = Rosen::PlaceholderVerticalAlignment::CENTER_OF_ROW_BOX;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "PlaceholderAlignment setting error! Now using default PlaceholderAlignment");
            break;
    }
    return convertValue;
}

void ConvertPlaceholderRun(const PlaceholderRun& span, Rosen::PlaceholderSpan& txtSpan)
{
    txtSpan.width = span.width;
    txtSpan.height = span.height;
    txtSpan.alignment = ConvertPlaceholderAlignment(span.alignment);
    txtSpan.baseline = ConvertTxtTextBaseline(span.baseline);
    txtSpan.baselineOffset = span.baseline_offset;
}

float GetVariableFontWeight(FontWeight fontWeight)
{
    return (static_cast<int32_t>(ConvertTxtFontWeight(fontWeight)) + 1) * DEFAULT_MULTIPLE;
}
} // namespace OHOS::Ace::Constants
