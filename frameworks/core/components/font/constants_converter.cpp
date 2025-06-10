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
#include <cstdint>

#include "rosen_text/hm_symbol_txt.h"
#include "rosen_text/typography_create.h"
#include "rosen_text/typography_style.h"

#include "base/i18n/localization.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/adapter/drawing_decoration_painter.h"
#include "base/geometry/ng/rect_t.h"

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
constexpr float DEFAULT_STROKE_WIDTH = 0.0f;
const std::string DEFAULT_SYMBOL_FONTFAMILY = "HM Symbol";
struct LineSpaceAndHeightInfo {
    double lineHeightScale = 0.0;
    double lineSpacingScale = 0.0;
    bool lineHeightOnly = false;
    bool lineSpacingOnly = false;
};
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

Rosen::TextBadgeType ConvertTxtBadgeType(SuperscriptStyle superscript)
{
    Rosen::TextBadgeType convertValue;
    switch (superscript) {
        case SuperscriptStyle::NORMAL:
            convertValue = Rosen::TextBadgeType::BADGE_NONE;
            break;
        case SuperscriptStyle::SUPERSCRIPT:
            convertValue = Rosen::TextBadgeType::SUPERSCRIPT;
            break;
        case SuperscriptStyle::SUBSCRIPT:
            convertValue = Rosen::TextBadgeType::SUBSCRIPT;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT, "TextBadgeType setting error! Now using default TextBadgeType");
            convertValue = Rosen::TextBadgeType::BADGE_NONE;
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

Rosen::TextVerticalAlign ConvertTxtTextVerticalAlign(TextVerticalAlign textVerticalAlign)
{
    Rosen::TextVerticalAlign convertValue;
    switch (textVerticalAlign) {
        case TextVerticalAlign::BASELINE:
            convertValue = Rosen::TextVerticalAlign::BASELINE;
            break;
        case TextVerticalAlign::BOTTOM:
            convertValue = Rosen::TextVerticalAlign::BOTTOM;
            break;
        case TextVerticalAlign::CENTER:
            convertValue = Rosen::TextVerticalAlign::CENTER;
            break;
        case TextVerticalAlign::TOP:
            convertValue = Rosen::TextVerticalAlign::TOP;
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_FONT,
                "TextVerticalAlign setting error! Now using default TextVerticalAlign");
            convertValue = Rosen::TextVerticalAlign::BASELINE;
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

Rosen::TextDecoration ConvertTxtTextDecoration(const std::vector<TextDecoration>& textDecorations)
{
    Rosen::TextDecoration convertValue = Rosen::TextDecoration::NONE;
    for (TextDecoration textDecoration : textDecorations) {
        switch (textDecoration) {
            case TextDecoration::NONE:
                convertValue = static_cast<Rosen::TextDecoration>(
                    static_cast<uint32_t>(convertValue) | static_cast<uint32_t>(Rosen::TextDecoration::NONE));
                break;
            case TextDecoration::UNDERLINE:
                convertValue = static_cast<Rosen::TextDecoration>(
                    static_cast<uint32_t>(convertValue) | static_cast<uint32_t>(Rosen::TextDecoration::UNDERLINE));
                break;
            case TextDecoration::OVERLINE:
                convertValue = static_cast<Rosen::TextDecoration>(
                    static_cast<uint32_t>(convertValue) | static_cast<uint32_t>(Rosen::TextDecoration::OVERLINE));
                break;
            case TextDecoration::LINE_THROUGH:
                convertValue = static_cast<Rosen::TextDecoration>(
                    static_cast<uint32_t>(convertValue) | static_cast<uint32_t>(Rosen::TextDecoration::LINE_THROUGH));
                break;
            default:
                TAG_LOGW(AceLogTag::ACE_FONT, "TextDecoration setting error! Now using default TextDecoration");
                break;
        }
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

// ConvertTxtStyle helper for LineSpacing and LineHeight etc
void ConvertSpacingAndHeigh(
    const TextStyle& textStyle, const WeakPtr<PipelineBase>& context, Rosen::TextStyle& txtStyle,
    LineSpaceAndHeightInfo& info)
{
    auto pipelineContext = context.Upgrade();
    if (textStyle.GetLineHeight().Unit() == DimensionUnit::PERCENT) {
        info.lineHeightOnly = true;
        info.lineHeightScale = textStyle.GetLineHeight().Value();
    } else {
        double fontSize = txtStyle.fontSize;
        double lineHeight = textStyle.GetLineHeight().Value();
        if (pipelineContext) {
            lineHeight = textStyle.GetLineHeight().ConvertToPxDistribute(
                textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        }
        info.lineHeightOnly = textStyle.HasHeightOverride();
        if (!NearEqual(lineHeight, fontSize) && (lineHeight > 0.0) && (!NearZero(fontSize))) {
            info.lineHeightScale = lineHeight / fontSize;
        } else {
            info.lineHeightScale = 1;
            static const int32_t beginVersion = 6;
            auto isBeginVersion = pipelineContext && pipelineContext->GetMinPlatformVersion() >= beginVersion;
            if (NearZero(lineHeight) || (!isBeginVersion && NearEqual(lineHeight, fontSize))) {
                info.lineHeightOnly = false;
            }
        }
    }
    if (textStyle.GetLineSpacing().Unit() == DimensionUnit::PERCENT) {
        info.lineSpacingOnly = true;
        info.lineSpacingScale = textStyle.GetLineSpacing().Value();
    } else {
        double fontSize = txtStyle.fontSize;
        double lineSpacing = textStyle.GetLineSpacing().Value();
        if (pipelineContext) {
            lineSpacing = textStyle.GetLineSpacing().ConvertToPxDistribute(
                textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale());
        }
        info.lineSpacingOnly = true;
        if (!NearEqual(lineSpacing, fontSize) && (lineSpacing > 0.0) && (!NearZero(fontSize))) {
            info.lineSpacingScale = lineSpacing / fontSize;
        } else {
            info.lineSpacingScale = 1;
            if (NearZero(lineSpacing)) {
                info.lineSpacingOnly = false;
            }
        }
    }
}

void ConvertGradiantColor(
    const TextStyle& textStyle, const WeakPtr<PipelineBase>& context, Rosen::TextStyle& txtStyle,
    OHOS::Ace::FontForegroudGradiantColor & gradiantColor)
{
    RSBrush brush;
    std::vector<Rosen::Drawing::PointF> points = {
        Rosen::Drawing::PointF(gradiantColor.points[0].GetX(), gradiantColor.points[0].GetY()),
        Rosen::Drawing::PointF(gradiantColor.points[1].GetX(), gradiantColor.points[1].GetY())
    };
    std::vector<RSColorQuad> colors;
    std::vector<RSScalar> pos;
    for (size_t i = 0; i < gradiantColor.colors.size(); i++) {
        colors.push_back(ConvertSkColor(gradiantColor.colors[i]));
        // IsValid ensures colors and scalars are same size
        pos.push_back(gradiantColor.scalars[i]);
    }
    brush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(points.at(0), points.at(1), colors, pos, RSTileMode::CLAMP));
    if (txtStyle.foregroundBrush) {
        txtStyle.foregroundBrush->SetShaderEffect(
            RSShaderEffect::CreateLinearGradient(points.at(0), points.at(1), colors, pos, RSTileMode::CLAMP));
    } else {
        txtStyle.foregroundBrush = brush;
    }
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
    txtStyle.badgeType = ConvertTxtBadgeType(textStyle.GetSuperscript());

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
    txtStyle.decorationThicknessScale = static_cast<double>(textStyle.GetLineThicknessScale());
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    txtStyle.halfLeading = textStyle.GetHalfLeading();

    if (textStyle.GetStrokeWidth().Value() != DEFAULT_STROKE_WIDTH) {
        RSPen pen;
        pen.SetWidth(std::abs(textStyle.GetStrokeWidth().ConvertToPxDistribute(
            textStyle.GetMinFontScale(), textStyle.GetMaxFontScale(), textStyle.IsAllowScale())));
        pen.SetColor(textStyle.GetStrokeColor().GetValue());
        txtStyle.foregroundPen = pen;
    }
    if (textStyle.GetStrokeWidth().Value() < DEFAULT_STROKE_WIDTH) {
        RSBrush brush;
        brush.SetColor(textStyle.GetTextColor().GetValue());
        txtStyle.foregroundBrush = brush;
    }
    
    for (auto& spanShadow : textStyle.GetTextShadows()) {
        Rosen::TextShadow txtShadow;
        txtShadow.color = spanShadow.GetColor().GetValue();
        txtShadow.offset.SetX(spanShadow.GetOffset().GetX());
        txtShadow.offset.SetY(spanShadow.GetOffset().GetY());
        txtShadow.blurRadius = spanShadow.GetBlurRadius();
        txtStyle.shadows.emplace_back(txtShadow);
    }

    LineSpaceAndHeightInfo info;
    ConvertSpacingAndHeigh(textStyle, context, txtStyle, info);
    txtStyle.heightOnly = info.lineHeightOnly || info.lineSpacingOnly;
    if (info.lineHeightOnly && info.lineSpacingOnly) {
        txtStyle.heightScale = info.lineHeightScale + info.lineSpacingScale;
    } else if (info.lineHeightOnly && !info.lineSpacingOnly) {
        txtStyle.heightScale = info.lineHeightScale;
    } else if (!info.lineHeightOnly && info.lineSpacingOnly) {
        txtStyle.heightScale = ORIGINAL_LINE_HEIGHT_SCALE + info.lineSpacingScale;
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

    auto gradiantColor = textStyle.GetFontForegroudGradiantColor();
    if (gradiantColor.IsValid()) {
        ConvertGradiantColor(textStyle, context, txtStyle, gradiantColor);
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

NG::Gradient ToGradient(const Gradient& gradient)
{
    NG::Gradient retGradient;
    retGradient.CreateGradientWithType(static_cast<NG::GradientType>(gradient.GetType()));
    if (gradient.GetType() == GradientType::LINEAR) {
        auto angle = gradient.GetLinearGradient().angle;
        if (angle.has_value()) {
            retGradient.GetLinearGradient()->angle = CalcDimension(angle.value().Value());
        }
        auto linearX = gradient.GetLinearGradient().linearX;
        if (linearX.has_value()) {
            retGradient.GetLinearGradient()->linearX = static_cast<NG::GradientDirection>(linearX.value());
        }
        auto linearY = gradient.GetLinearGradient().linearY;
        if (linearY.has_value()) {
            retGradient.GetLinearGradient()->linearY = static_cast<NG::GradientDirection>(linearY.value());
        }
    }
    if (gradient.GetType() == GradientType::RADIAL) {
        auto radialCenterX = gradient.GetRadialGradient().radialCenterX;
        if (radialCenterX.has_value()) {
            retGradient.GetRadialGradient()->radialCenterX = CalcDimension(radialCenterX.value().Value());
        }
        auto radialCenterY = gradient.GetRadialGradient().radialCenterY;
        if (radialCenterY.has_value()) {
            retGradient.GetRadialGradient()->radialCenterY = CalcDimension(radialCenterY.value().Value());
        }
        auto radialVerticalSize = gradient.GetRadialGradient().radialVerticalSize;
        if (radialVerticalSize.has_value()) {
            retGradient.GetRadialGradient()->radialVerticalSize = CalcDimension(radialVerticalSize.value().Value());
        }
        auto radialHorizontalSize = gradient.GetRadialGradient().radialHorizontalSize;
        if (radialVerticalSize.has_value()) {
            retGradient.GetRadialGradient()->radialHorizontalSize = CalcDimension(radialHorizontalSize.value().Value());
        }
    }
    retGradient.SetRepeat(gradient.GetRepeat());
    const auto& colorStops = gradient.GetColors();
    for (const auto& item : colorStops) {
        NG::GradientColor gradientColor;
        gradientColor.SetColor(item.GetColor());
        gradientColor.SetHasValue(item.GetHasValue());
        gradientColor.SetDimension(item.GetDimension());
        retGradient.AddColor(gradientColor);
    }
    return retGradient;
}

void ConvertForegroundPaint(const TextStyle& textStyle, double width, double height, Rosen::TextStyle& txtStyle)
{
    if (!textStyle.GetGradient().has_value()) {
        return;
    }
    txtStyle.textStyleUid = static_cast<unsigned long>(textStyle.GetTextStyleUid());
    txtStyle.relayoutChangeBitmap = textStyle.GetReLayoutTextStyleBitmap();
    auto gradient = textStyle.GetGradient().value();
    GradientType type = gradient.GetType();
    if (type != GradientType::LINEAR && type != GradientType::RADIAL) {
        return;
    }
    RSBrush brush;
    auto shaderEffect =
        NG::DrawingDecorationPainter::CreateGradientShader(ToGradient(gradient), NG::SizeF(width, height));
    brush.SetShaderEffect(shaderEffect);
    txtStyle.foregroundBrush = brush;
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
        case PlaceholderAlignment::FOLLOW_PARAGRAPH:
            convertValue = Rosen::PlaceholderVerticalAlignment::FOLLOW_PARAGRAPH;
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
