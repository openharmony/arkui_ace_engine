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

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/font_style.h"
#include "txt/font_weight.h"
#include "txt/paragraph_style.h"
#include "txt/text_decoration.h"
#else
#include "rosen_text/hm_symbol_txt.h"
#include "rosen_text/typography_create.h"
#include "rosen_text/typography_style.h"
#endif

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
} // namespace

#ifndef USE_GRAPHIC_TEXT_GINE
txt::FontWeight ConvertTxtFontWeight(FontWeight fontWeight)
{
    txt::FontWeight convertValue;
    switch (fontWeight) {
        case FontWeight::W100:
        case FontWeight::LIGHTER:
            convertValue = txt::FontWeight::w100;
            break;
        case FontWeight::W200:
            convertValue = txt::FontWeight::w200;
            break;
        case FontWeight::W300:
            convertValue = txt::FontWeight::w300;
            break;
        case FontWeight::W400:
        case FontWeight::NORMAL:
        case FontWeight::REGULAR:
            convertValue = txt::FontWeight::w400;
            break;
        case FontWeight::W500:
        case FontWeight::MEDIUM:
            convertValue = txt::FontWeight::w500;
            break;
        case FontWeight::W600:
            convertValue = txt::FontWeight::w600;
            break;
        case FontWeight::W700:
        case FontWeight::BOLD:
            convertValue = txt::FontWeight::w700;
            break;
        case FontWeight::W800:
            convertValue = txt::FontWeight::w800;
            break;
        case FontWeight::W900:
        case FontWeight::BOLDER:
            convertValue = txt::FontWeight::w900;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "FontWeight set error! use default FontWeight.");
            convertValue = txt::FontWeight::w400;
            break;
    }
    return convertValue;
}
#else
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
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
txt::FontStyle ConvertTxtFontStyle(FontStyle fontStyle)
{
    txt::FontStyle convertValue;
    switch (fontStyle) {
        case FontStyle::NORMAL:
            convertValue = txt::FontStyle::normal;
            break;
        case FontStyle::ITALIC:
            convertValue = txt::FontStyle::italic;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "FontStyle set error! use default FontStyle");
            convertValue = txt::FontStyle::normal;
            break;
    }
    return convertValue;
}
#else
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
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
txt::TextBaseline ConvertTxtTextBaseline(TextBaseline textBaseline)
{
    txt::TextBaseline convertValue;
    switch (textBaseline) {
        case TextBaseline::ALPHABETIC:
            convertValue = txt::TextBaseline::kAlphabetic;
            break;
        case TextBaseline::IDEOGRAPHIC:
            convertValue = txt::TextBaseline::kIdeographic;
            break;
        default:
            convertValue = txt::TextBaseline::kAlphabetic;
            break;
    }
    return convertValue;
}
#else
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
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
txt::TextAlign ConvertTxtTextAlign(TextAlign textAlign)
{
    txt::TextAlign convertValue;
    switch (textAlign) {
        case TextAlign::LEFT:
            convertValue = txt::TextAlign::left;
            break;
        case TextAlign::RIGHT:
            convertValue = txt::TextAlign::right;
            break;
        case TextAlign::CENTER:
            convertValue = txt::TextAlign::center;
            break;
        case TextAlign::JUSTIFY:
            convertValue = txt::TextAlign::justify;
            break;
        case TextAlign::START:
            convertValue = txt::TextAlign::start;
            break;
        case TextAlign::END:
            convertValue = txt::TextAlign::end;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "TextAlign set error! use default TextAlign");
            convertValue = txt::TextAlign::start;
            break;
    }
    return convertValue;
}
#else
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
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
txt::Paragraph::RectHeightStyle ConvertTxtRectHeightStyle(RectHeightStyle heightStyle)
{
    switch (heightStyle) {
        case RectHeightStyle::TIGHT:
            return txt::Paragraph::RectHeightStyle::kTight;
        case RectHeightStyle::MAX:
            return txt::Paragraph::RectHeightStyle::kMax;
        case RectHeightStyle::INCLUDE_LINE_SPACE_MIDDLE:
            return txt::Paragraph::RectHeightStyle::kIncludeLineSpacingMiddle;
        case RectHeightStyle::INCLUDE_LINE_SPACE_TOP:
            return txt::Paragraph::RectHeightStyle::kIncludeLineSpacingTop;
        case RectHeightStyle::INCLUDE_LINE_SPACE_BOTTOM:
            return txt::Paragraph::RectHeightStyle::kIncludeLineSpacingBottom;
        case RectHeightStyle::STRUT:
            return txt::Paragraph::RectHeightStyle::kStrut;
        default:
            return txt::Paragraph::RectHeightStyle::kTight;
    }
}
#else
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
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
txt::Paragraph::RectWidthStyle ConvertTxtRectWidthStyle(RectWidthStyle widthStyle)
{
    switch (widthStyle) {
        case RectWidthStyle::TIGHT:
            return txt::Paragraph::RectWidthStyle::kTight;
        case RectWidthStyle::MAX:
            return txt::Paragraph::RectWidthStyle::kMax;
        default:
            return txt::Paragraph::RectWidthStyle::kTight;
    }
}
#else
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
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
txt::TextDirection ConvertTxtTextDirection(TextDirection textDirection)
#else
Rosen::TextDirection ConvertTxtTextDirection(TextDirection textDirection)
#endif
{
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::TextDirection convertValue;
#else
    Rosen::TextDirection convertValue;
#endif
    switch (textDirection) {
        case TextDirection::RTL:
#ifndef USE_GRAPHIC_TEXT_GINE
            convertValue = txt::TextDirection::rtl;
#else
            convertValue = Rosen::TextDirection::RTL;
#endif
            break;
        case TextDirection::LTR:
#ifndef USE_GRAPHIC_TEXT_GINE
            convertValue = txt::TextDirection::ltr;
#else
            convertValue = Rosen::TextDirection::LTR;
#endif
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "TextDirection setting error! Now using default TextDirection");
#ifndef USE_GRAPHIC_TEXT_GINE
            convertValue = txt::TextDirection::ltr;
#else
            convertValue = Rosen::TextDirection::LTR;
#endif
            break;
    }
    return convertValue;
}

SkColor ConvertSkColor(Color color)
{
    return color.GetValue();
}

#ifndef USE_GRAPHIC_TEXT_GINE
txt::TextDecoration ConvertTxtTextDecoration(TextDecoration textDecoration)
{
    txt::TextDecoration convertValue = txt::TextDecoration::kNone;
    switch (textDecoration) {
        case TextDecoration::NONE:
            convertValue = txt::TextDecoration::kNone;
            break;
        case TextDecoration::UNDERLINE:
            convertValue = txt::TextDecoration::kUnderline;
            break;
        case TextDecoration::OVERLINE:
            convertValue = txt::TextDecoration::kOverline;
            break;
        case TextDecoration::LINE_THROUGH:
            convertValue = txt::TextDecoration::kLineThrough;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "TextDecoration set error! use default TextDecoration");
            break;
    }
    return convertValue;
}
#else
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
#endif
#ifndef USE_GRAPHIC_TEXT_GINE
txt::TextDecorationStyle ConvertTxtTextDecorationStyle(TextDecorationStyle textDecorationStyle)
{
    txt::TextDecorationStyle convertValue = txt::TextDecorationStyle::kSolid;
    switch (textDecorationStyle) {
        case TextDecorationStyle::SOLID:
            convertValue = txt::TextDecorationStyle::kSolid;
            break;
        case TextDecorationStyle::DOUBLE:
            convertValue = txt::TextDecorationStyle::kDouble;
            break;
        case TextDecorationStyle::DOTTED:
            convertValue = txt::TextDecorationStyle::kDotted;
            break;
        case TextDecorationStyle::DASHED:
            convertValue = txt::TextDecorationStyle::kDashed;
            break;
        case TextDecorationStyle::WAVY:
            convertValue = txt::TextDecorationStyle::kWavy;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "TextDecorationStyle set error! use default TextDecorationStyle");
            break;
    }
    return convertValue;
}
#else
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
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
void ConvertTxtStyle(const TextStyle& textStyle, const WeakPtr<PipelineBase>& context, txt::TextStyle& txtStyle)
{
    txtStyle.color = ConvertSkColor(textStyle.GetTextColor());
    txtStyle.font_weight = ConvertTxtFontWeight(textStyle.GetFontWeight());
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
    // Font size must be px when transferring to txt::TextStyle
    if (pipelineContext) {
        txtStyle.font_size = pipelineContext->NormalizeToPx(textStyle.GetFontSize());
        if (textStyle.IsAllowScale() && textStyle.GetFontSize().Unit() == DimensionUnit::FP) {
            txtStyle.font_size =
                pipelineContext->NormalizeToPx(textStyle.GetFontSize() * pipelineContext->GetFontScale());
        }
    } else {
        txtStyle.font_size = textStyle.GetFontSize().Value();
    }
    txtStyle.font_style = ConvertTxtFontStyle(textStyle.GetFontStyle());

    if (textStyle.GetWordSpacing().Unit() == DimensionUnit::PERCENT) {
        txtStyle.word_spacing = textStyle.GetWordSpacing().Value() * txtStyle.font_size;
    } else {
        if (pipelineContext) {
            txtStyle.word_spacing = pipelineContext->NormalizeToPx(textStyle.GetWordSpacing());
        } else {
            txtStyle.word_spacing = textStyle.GetWordSpacing().Value();
        }
    }
    if (pipelineContext) {
        txtStyle.letter_spacing = pipelineContext->NormalizeToPx(textStyle.GetLetterSpacing());
    }
    txtStyle.text_baseline = ConvertTxtTextBaseline(textStyle.GetTextBaseline());
    txtStyle.decoration = ConvertTxtTextDecoration(textStyle.GetTextDecoration());
    txtStyle.decoration_style = ConvertTxtTextDecorationStyle(textStyle.GetTextDecorationStyle());
    txtStyle.decoration_color = ConvertSkColor(textStyle.GetTextDecorationColor());
    txtStyle.font_families = textStyle.GetFontFamilies();
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    txtStyle.half_leading = textStyle.GetHalfLeading();

    for (auto& spanShadow : textStyle.GetTextShadows()) {
        txt::TextShadow txtShadow;
        txtShadow.color = spanShadow.GetColor().GetValue();
#ifndef USE_ROSEN_DRAWING
        txtShadow.offset.fX = static_cast<SkScalar>(spanShadow.GetOffset().GetX());
        txtShadow.offset.fY = static_cast<SkScalar>(spanShadow.GetOffset().GetY());
#else
        txtShadow.offset.SetX(static_cast<SkScalar>(spanShadow.GetOffset().GetX()));
        txtShadow.offset.SetY(static_cast<SkScalar>(spanShadow.GetOffset().GetY()));
#endif
        txtShadow.blur_sigma = spanShadow.GetBlurRadius();

        txtStyle.text_shadows.emplace_back(txtShadow);
    }

    if (textStyle.GetLineHeight().Unit() == DimensionUnit::PERCENT) {
        txtStyle.has_height_override = true;
        txtStyle.height = textStyle.GetLineHeight().Value();
    } else {
        double fontSize = txtStyle.font_size;
        double lineHeight = textStyle.GetLineHeight().Value();
        if (pipelineContext) {
            lineHeight = pipelineContext->NormalizeToPx(textStyle.GetLineHeight());
        }
        txtStyle.has_height_override = textStyle.HasHeightOverride();
        if (!NearEqual(lineHeight, fontSize) && (lineHeight > 0.0) && (!NearZero(fontSize))) {
            txtStyle.height = lineHeight / fontSize;
        } else {
            txtStyle.height = 1;
            static const int32_t BEGIN_VERSION = 6;
            auto isBeginVersion = pipelineContext && pipelineContext->GetMinPlatformVersion() >= BEGIN_VERSION;
            if (NearZero(lineHeight) || (!isBeginVersion && NearEqual(lineHeight, fontSize))) {
                txtStyle.has_height_override = false;
            }
        }
    }

    // set font variant
    auto fontFeatures = textStyle.GetFontFeatures();
    if (!fontFeatures.empty()) {
        txt::FontFeatures features;
        for (auto iter = fontFeatures.begin(); iter != fontFeatures.end(); ++iter) {
            features.SetFeature(iter->first, iter->second);
        }
        txtStyle.font_features = features;
    }
}

void ConvertTxtStyle(const TextStyle& textStyle, txt::TextStyle& txtStyle) {}

void ConvertSymbolTxtStyle(const TextStyle& textStyle, txt::TextStyle& txtStyle)
{
    if (!textStyle.isSymbolGlyph_) {
        return;
    }

    txtStyle.isSymbolGlyph = true;
    const std::vector<Color>& symbolColor = textStyle.GetSymbolColorList();
    std::vector<Rosen::Drawing::Color> symbolColors;
    for (size_t i = 0; i < symbolColor.size(); i++) {
        symbolColors.emplace_back(ConvertSkColor(symbolColor[i]));
    }
    txtStyle.symbol.SetRenderColor(symbolColors);
    txtStyle.symbol.SetRenderMode(textStyle.GetRenderStrategy());
    if (textStyle.GetSymbolEffectOptions().has_value()) {
        auto options = textStyle.GetSymbolEffectOptions().value();
        auto effectType = options.GetEffectType();
        txtStyle.symbol.SetSymbolEffect(static_cast<uint32_t>(effectType));
        if (effectType == SymbolEffectType::HIERARCHICAL && options.GetFillStyle().has_value()) {
            txtStyle.symbol.SetAnimationMode(static_cast<uint16_t>(options.GetFillStyle().value()));
        } else {
            if (options.GetScopeType().has_value()) {
                txtStyle.symbol.SetAnimationMode(static_cast<uint16_t>(options.GetScopeType().value()));
            }
        }
        if (options.GetCommonSubType().has_value()) {
            auto commonType = static_cast<uint16_t>(options.GetCommonSubType().value());
            txtStyle.symbol.SetCommonSubType(commonType == 1 ? Rosen::Drawing::DrawingCommonSubType::UP
                                                             : Rosen::Drawing::DrawingCommonSubType::DOWN);
        }
        txtStyle.symbol.SetAnimationStart(options.GetIsTxtActive());
    } else {
        auto effectStrategy = textStyle.GetEffectStrategy();
        if (effectStrategy < NONE_EFFECT || effectStrategy > SCALE_EFFECT) {
            effectStrategy = NONE_EFFECT;
        }
        txtStyle.symbol.SetSymbolEffect(effectStrategy);
        txtStyle.symbol.SetAnimationStart(true);
    }
    txtStyle.fontFamilies.push_back("HM Symbol");
}
#else
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
    txtStyle.color = ConvertSkColor(textStyle.GetTextColor());
    txtStyle.fontWeight = ConvertTxtFontWeight(textStyle.GetFontWeight());
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
    txtStyle.fontFamilies.push_back("HM Symbol");
}
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
Rect ConvertSkRect(SkRect skRect)
{
    Rect result;
    result.SetLeft(skRect.fLeft);
    result.SetTop(skRect.fTop);
    result.SetWidth(skRect.width());
    result.SetHeight(skRect.height());
    return result;
}
#else
Rect ConvertSkRect(const Rosen::Drawing::RectF& skRect)
{
    Rect result;
    result.SetLeft(skRect.GetLeft());
    result.SetTop(skRect.GetTop());
    result.SetWidth(skRect.GetWidth());
    result.SetHeight(skRect.GetHeight());
    return result;
}
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
txt::PlaceholderAlignment ConvertPlaceholderAlignment(PlaceholderAlignment textDecoration)
{
    txt::PlaceholderAlignment convertValue = txt::PlaceholderAlignment::kBaseline;
    switch (textDecoration) {
        case PlaceholderAlignment::BASELINE:
            convertValue = txt::PlaceholderAlignment::kBaseline;
            break;
        case PlaceholderAlignment::ABOVEBASELINE:
            convertValue = txt::PlaceholderAlignment::kAboveBaseline;
            break;
        case PlaceholderAlignment::BELOWBASELINE:
            convertValue = txt::PlaceholderAlignment::kBelowBaseline;
            break;
        case PlaceholderAlignment::TOP:
            convertValue = txt::PlaceholderAlignment::kTop;
            break;
        case PlaceholderAlignment::BOTTOM:
            convertValue = txt::PlaceholderAlignment::kBottom;
            break;
        case PlaceholderAlignment::MIDDLE:
            convertValue = txt::PlaceholderAlignment::kMiddle;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "PlaceholderAlignment set error! use default PlaceholderAlignment");
            break;
    }
    return convertValue;
}
#else
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
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
void ConvertPlaceholderRun(const PlaceholderRun& span, txt::PlaceholderRun& txtSpan)
#else
void ConvertPlaceholderRun(const PlaceholderRun& span, Rosen::PlaceholderSpan& txtSpan)
#endif
{
    txtSpan.width = span.width;
    txtSpan.height = span.height;
    txtSpan.alignment = ConvertPlaceholderAlignment(span.alignment);
    txtSpan.baseline = ConvertTxtTextBaseline(span.baseline);
#ifndef USE_GRAPHIC_TEXT_GINE
    txtSpan.baseline_offset = span.baseline_offset;
#else
    txtSpan.baselineOffset = span.baseline_offset;
#endif
}

} // namespace OHOS::Ace::Constants
