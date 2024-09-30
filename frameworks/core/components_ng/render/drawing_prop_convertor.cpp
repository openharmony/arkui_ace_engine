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

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace {
namespace {
constexpr uint8_t UINT32_LEFT_SHIFT_24 = 24;
constexpr uint8_t UINT32_LEFT_SHIFT_16 = 16;
constexpr uint8_t UINT32_LEFT_SHIFT_8 = 8;
} // namespace
RSColor ToRSColor(const Color& color)
{
    return RSColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

RSColor ToRSColor(const LinearColor& color)
{
    return RSColor(
        (static_cast<uint32_t>(std::clamp<int16_t>(color.GetAlpha(), 0, UINT8_MAX)) << UINT32_LEFT_SHIFT_24) |
        (static_cast<uint32_t>(std::clamp<int16_t>(color.GetRed(), 0, UINT8_MAX)) << UINT32_LEFT_SHIFT_16) |
        (static_cast<uint32_t>(std::clamp<int16_t>(color.GetGreen(), 0, UINT8_MAX)) << UINT32_LEFT_SHIFT_8) |
        (static_cast<uint32_t>(std::clamp<int16_t>(color.GetBlue(), 0, UINT8_MAX))));
}

RSRect ToRSRect(const NG::RectF& rect)
{
    return RSRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
}

RSPoint ToRSPoint(const NG::PointF& point)
{
    return RSPoint(point.GetX(), point.GetY());
}

RSPen::CapStyle ToRSCapStyle(const LineCap& lineCap)
{
    RSPen::CapStyle capStyle;
    switch (lineCap) {
        case LineCap::SQUARE:
            capStyle = RSPen::CapStyle::SQUARE_CAP;
            break;
        case LineCap::ROUND:
            capStyle = RSPen::CapStyle::ROUND_CAP;
            break;
        default:
            capStyle = RSPen::CapStyle::FLAT_CAP;
            break;
    }
    return capStyle;
}

RSTextDirection ToRSTextDirection(const TextDirection& txtDir)
{
    RSTextDirection rsTxtDir = RSTextDirection::LTR;
    if (txtDir == TextDirection::LTR) {
        rsTxtDir = RSTextDirection::LTR;
    } else if (txtDir == TextDirection::RTL) {
        rsTxtDir = RSTextDirection::RTL;
    }
    return rsTxtDir;
}

RSTextAlign ToRSTextAlign(const TextAlign& align)
{
    // should keep enum same with rosen.
    RSTextAlign textAlign = RSTextAlign::START;
    switch (align) {
        case TextAlign::LEFT:
            textAlign = RSTextAlign::LEFT;
            break;
        case TextAlign::RIGHT:
            textAlign = RSTextAlign::RIGHT;
            break;
        case TextAlign::CENTER:
            textAlign = RSTextAlign::CENTER;
            break;
        case TextAlign::JUSTIFY:
            textAlign = RSTextAlign::JUSTIFY;
            break;
        case TextAlign::START:
            textAlign = RSTextAlign::START;
            break;
        case TextAlign::END:
            textAlign = RSTextAlign::END;
            break;
        default:
            textAlign = RSTextAlign::START;
            break;
    }
    return textAlign;
}

RSFontWeight ToRSFontWeight(FontWeight fontWeight)
{
    RSFontWeight rsFontWeight = RSFontWeight::W400;
    switch (fontWeight) {
        case FontWeight::W100:
        case FontWeight::LIGHTER:
            rsFontWeight = RSFontWeight::W100;
            break;
        case FontWeight::W200:
            rsFontWeight = RSFontWeight::W200;
            break;
        case FontWeight::W300:
            rsFontWeight = RSFontWeight::W300;
            break;
        case FontWeight::W400:
        case FontWeight::NORMAL:
        case FontWeight::REGULAR:
            rsFontWeight = RSFontWeight::W400;
            break;
        case FontWeight::W500:
        case FontWeight::MEDIUM:
            rsFontWeight = RSFontWeight::W500;
            break;
        case FontWeight::W600:
            rsFontWeight = RSFontWeight::W600;
            break;
        case FontWeight::W700:
        case FontWeight::BOLD:
            rsFontWeight = RSFontWeight::W700;
            break;
        case FontWeight::W800:
            rsFontWeight = RSFontWeight::W800;
            break;
        case FontWeight::W900:
        case FontWeight::BOLDER:
            rsFontWeight = RSFontWeight::W900;
            break;
        default:
            rsFontWeight = RSFontWeight::W400;
            break;
    }
    return rsFontWeight;
}

RSWordBreakType ToRSWordBreakType(const WordBreak& wordBreak)
{
    // should keep enum same with rosen.
    return static_cast<RSWordBreakType>(wordBreak);
}

RSEllipsisMode ToRSEllipsisMode(EllipsisMode value)
{
    // should keep enum same with rosen.
    return static_cast<RSEllipsisMode>(value);
}

RSTextDecoration ToRSTextDecoration(TextDecoration textDecoration)
{
    RSTextDecoration rsTextDecoration = RSTextDecoration::NONE;
    switch (textDecoration) {
        case TextDecoration::OVERLINE:
            rsTextDecoration = RSTextDecoration::OVERLINE;
            break;
        case TextDecoration::LINE_THROUGH:
#ifndef USE_GRAPHIC_TEXT_GINE
            rsTextDecoration = RSTextDecoration::LINETHROUGH;
#else
            rsTextDecoration = RSTextDecoration::LINE_THROUGH;
#endif
            break;
        case TextDecoration::UNDERLINE:
            rsTextDecoration = RSTextDecoration::UNDERLINE;
            break;
        default:
            rsTextDecoration = RSTextDecoration::NONE;
            break;
    }
    return rsTextDecoration;
}

RSTextDecorationStyle ToRSTextDecorationStyle(TextDecorationStyle textDecorationStyle)
{
    RSTextDecorationStyle rsTextDecorationStyle = RSTextDecorationStyle::SOLID;
    switch (textDecorationStyle) {
        case TextDecorationStyle::DOUBLE:
            rsTextDecorationStyle = RSTextDecorationStyle::DOUBLE;
            break;
        case TextDecorationStyle::DOTTED:
            rsTextDecorationStyle = RSTextDecorationStyle::DOTTED;
            break;
        case TextDecorationStyle::DASHED:
            rsTextDecorationStyle = RSTextDecorationStyle::DASHED;
            break;
        case TextDecorationStyle::WAVY:
            rsTextDecorationStyle = RSTextDecorationStyle::WAVY;
            break;
        default:
            rsTextDecorationStyle = RSTextDecorationStyle::SOLID;
            break;
    }
    return rsTextDecorationStyle;
}

RSTextStyle ToRSTextStyle(const RefPtr<PipelineBase>& context, const TextStyle& textStyle)
{
    RSTextStyle rsTextStyle;
#ifndef USE_GRAPHIC_TEXT_GINE
    rsTextStyle.color_ = ToRSColor(textStyle.GetTextColor());
    rsTextStyle.decoration_ = ToRSTextDecoration(textStyle.GetTextDecoration());
    rsTextStyle.decorationStyle_ = ToRSTextDecorationStyle(textStyle.GetTextDecorationStyle());
    rsTextStyle.decorationColor_ = ToRSColor(textStyle.GetTextDecorationColor());
#else
    rsTextStyle.color = ToRSColor(textStyle.GetTextColor());
    rsTextStyle.decoration = ToRSTextDecoration(textStyle.GetTextDecoration());
    rsTextStyle.decorationColor = ToRSColor(textStyle.GetTextDecorationColor());
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
    rsTextStyle.fontWeight_ = ToRSFontWeight(textStyle.GetFontWeight());
    rsTextStyle.fontStyle_ = static_cast<RSFontStyle>(textStyle.GetFontStyle());
    rsTextStyle.textBaseline_ = static_cast<RSTextBaseline>(textStyle.GetTextBaseline());
    rsTextStyle.fontFamilies_ = textStyle.GetFontFamilies();
#else
    rsTextStyle.fontWeight = ToRSFontWeight(textStyle.GetFontWeight());
    rsTextStyle.fontStyle = static_cast<RSFontStyle>(textStyle.GetFontStyle());
    rsTextStyle.baseline = static_cast<RSTextBaseline>(textStyle.GetTextBaseline());
    rsTextStyle.fontFamilies = textStyle.GetFontFamilies();
#endif
    if (textStyle.GetTextOverflow() == TextOverflow::ELLIPSIS) {
#ifndef USE_GRAPHIC_TEXT_GINE
        rsTextStyle.ellipsis_ = StringUtils::Str8ToStr16(StringUtils::ELLIPSIS);
#else
        rsTextStyle.ellipsis = StringUtils::Str8ToStr16(StringUtils::ELLIPSIS);
#endif
    }
    if (context) {
#ifndef USE_GRAPHIC_TEXT_GINE
        rsTextStyle.fontSize_ = context->NormalizeToPx(textStyle.GetFontSize());
#else
        rsTextStyle.fontSize = context->NormalizeToPx(textStyle.GetFontSize());
#endif
        if (textStyle.IsAllowScale() || textStyle.GetFontSize().Unit() == DimensionUnit::FP) {
#ifndef USE_GRAPHIC_TEXT_GINE
            rsTextStyle.fontSize_ = context->NormalizeToPx(textStyle.GetFontSize() * context->GetFontScale());
#else
            rsTextStyle.fontSize = context->NormalizeToPx(textStyle.GetFontSize() * context->GetFontScale());
#endif
        }
    } else {
#ifndef USE_GRAPHIC_TEXT_GINE
        rsTextStyle.fontSize_ = textStyle.GetFontSize().Value();
#else
        rsTextStyle.fontSize = textStyle.GetFontSize().Value();
#endif
    }
    if (context) {
#ifndef USE_GRAPHIC_TEXT_GINE
        rsTextStyle.letterSpacing_ = context->NormalizeToPx(textStyle.GetLetterSpacing());
#else
        rsTextStyle.letterSpacing = context->NormalizeToPx(textStyle.GetLetterSpacing());
#endif
    }
    if (textStyle.GetWordSpacing().Unit() == DimensionUnit::PERCENT) {
#ifndef USE_GRAPHIC_TEXT_GINE
        rsTextStyle.wordSpacing_ = textStyle.GetWordSpacing().Value() * rsTextStyle.fontSize_;
#else
        rsTextStyle.wordSpacing = textStyle.GetWordSpacing().Value() * rsTextStyle.fontSize;
#endif
    } else {
        if (context) {
#ifndef USE_GRAPHIC_TEXT_GINE
            rsTextStyle.wordSpacing_ = context->NormalizeToPx(textStyle.GetWordSpacing());
#else
            rsTextStyle.wordSpacing = context->NormalizeToPx(textStyle.GetWordSpacing());
#endif
        } else {
#ifndef USE_GRAPHIC_TEXT_GINE
            rsTextStyle.wordSpacing_ = textStyle.GetWordSpacing().Value();
#else
            rsTextStyle.wordSpacing = textStyle.GetWordSpacing().Value();
#endif
        }
    }

    if (textStyle.GetLineHeight().Unit() == DimensionUnit::PERCENT) {
#ifndef USE_GRAPHIC_TEXT_GINE
        rsTextStyle.hasHeightOverride_ = true;
        rsTextStyle.height_ = textStyle.GetLineHeight().Value();
#else
        rsTextStyle.heightOnly = true;
        rsTextStyle.heightScale = textStyle.GetLineHeight().Value();
#endif
    } else {
#ifndef USE_GRAPHIC_TEXT_GINE
        double fontSize = rsTextStyle.fontSize_;
#else
        double fontSize = rsTextStyle.fontSize;
#endif
        double lineHeight = textStyle.GetLineHeight().Value();
        if (context) {
            lineHeight = context->NormalizeToPx(textStyle.GetLineHeight());
        }
#ifndef USE_GRAPHIC_TEXT_GINE
        rsTextStyle.hasHeightOverride_ = textStyle.HasHeightOverride();
#else
        rsTextStyle.heightOnly = textStyle.HasHeightOverride();
#endif
        if (!NearEqual(lineHeight, fontSize) && (lineHeight > 0.0) && (!NearZero(fontSize))) {
#ifndef USE_GRAPHIC_TEXT_GINE
            rsTextStyle.height_ = lineHeight / fontSize;
#else
            rsTextStyle.heightScale = lineHeight / fontSize;
#endif
        } else {
#ifndef USE_GRAPHIC_TEXT_GINE
            rsTextStyle.height_ = 1;
#else
            rsTextStyle.heightScale = 1;
#endif
            static const int32_t BEGIN_VERSION = 6;
            auto isBeginVersion = context && context->GetMinPlatformVersion() >= BEGIN_VERSION;
            if (NearZero(lineHeight) || (!isBeginVersion && NearEqual(lineHeight, fontSize))) {
#ifndef USE_GRAPHIC_TEXT_GINE
                rsTextStyle.hasHeightOverride_ = false;
#else
                rsTextStyle.heightOnly = false;
#endif
            }
        }
    }
    return rsTextStyle;
}
} // namespace OHOS::Ace
