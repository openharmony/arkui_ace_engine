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
#include "rosen_text/typography_style.h"
#include "rosen_text/typography_create.h"
#endif

#include "base/i18n/localization.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace::Constants {

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
            LOGW("FontWeight setting error! Now using default FontWeight.");
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
            LOGW("FontWeight setting error! Now using default FontWeight.");
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
            LOGW("FontStyle setting error! Now using default FontStyle");
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
            LOGW("FontStyle setting error! Now using default FontStyle");
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
            LOGD("TextBaseline setting error! Now using default TextBaseline");
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
            LOGD("TextBaseline setting error! Now using default TextBaseline");
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
            LOGW("TextAlign setting error! Now using default TextAlign");
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
            LOGW("TextAlign setting error! Now using default TextAlign");
            convertValue = Rosen::TextAlign::START;
            break;
    }
    return convertValue;
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
            LOGW("TextDirection setting error! Now using default TextDirection");
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
            LOGW("TextDecoration setting error! Now using default TextDecoration");
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
            LOGW("TextDecoration setting error! Now using default TextDecoration");
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
            LOGW("TextDecorationStyle setting error! Now using default TextDecorationStyle");
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
            LOGW("TextDecorationStyle setting error! Now using default TextDecorationStyle");
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
    // Font size must be px when transferring to txt::TextStyle
    auto pipelineContext = context.Upgrade();
    if (pipelineContext) {
        txtStyle.font_size = pipelineContext->NormalizeToPx(textStyle.GetFontSize());
        if (textStyle.IsAllowScale() || textStyle.GetFontSize().Unit() == DimensionUnit::FP) {
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
#if defined (FLUTTER_2_5) || defined (NEW_SKIA)
        txtShadow.blur_sigma = spanShadow.GetBlurRadius();
#else
        txtShadow.blur_radius = spanShadow.GetBlurRadius();
#endif
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
            LOGD("use default text style height value.");
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
#else
void ConvertTxtStyle(const TextStyle& textStyle, const WeakPtr<PipelineBase>& context, Rosen::TextStyle& txtStyle)
{
    txtStyle.color = ConvertSkColor(textStyle.GetTextColor());
    txtStyle.fontWeight = ConvertTxtFontWeight(textStyle.GetFontWeight());
    // Font size must be px when transferring to Rosen::TextStyle
    auto pipelineContext = context.Upgrade();
    if (pipelineContext) {
        txtStyle.fontSize = pipelineContext->NormalizeToPx(textStyle.GetFontSize());
        if (textStyle.IsAllowScale() || textStyle.GetFontSize().Unit() == DimensionUnit::FP) {
            txtStyle.fontSize =
                pipelineContext->NormalizeToPx(textStyle.GetFontSize() * pipelineContext->GetFontScale());
        }
    } else {
        txtStyle.fontSize = textStyle.GetFontSize().Value();
    }
    txtStyle.fontStyle = ConvertTxtFontStyle(textStyle.GetFontStyle());

    if (textStyle.GetWordSpacing().Unit() == DimensionUnit::PERCENT) {
        txtStyle.wordSpacing = textStyle.GetWordSpacing().Value() * txtStyle.fontSize;
    } else {
        if (pipelineContext) {
            txtStyle.wordSpacing = pipelineContext->NormalizeToPx(textStyle.GetWordSpacing());
        } else {
            txtStyle.wordSpacing = textStyle.GetWordSpacing().Value();
        }
    }
    if (pipelineContext) {
        txtStyle.letterSpacing = pipelineContext->NormalizeToPx(textStyle.GetLetterSpacing());
    }
    txtStyle.baseline = ConvertTxtTextBaseline(textStyle.GetTextBaseline());
    txtStyle.decoration = ConvertTxtTextDecoration(textStyle.GetTextDecoration());
    txtStyle.decorationColor = ConvertSkColor(textStyle.GetTextDecorationColor());
    txtStyle.fontFamilies = textStyle.GetFontFamilies();
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();

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
        if (pipelineContext) {
            lineHeight = pipelineContext->NormalizeToPx(textStyle.GetLineHeight());
        }
        txtStyle.heightOnly = textStyle.HasHeightOverride();
        if (!NearEqual(lineHeight, fontSize) && (lineHeight > 0.0) && (!NearZero(fontSize))) {
            txtStyle.heightScale = lineHeight / fontSize;
        } else {
            LOGD("use default text style height value.");
            txtStyle.heightScale = 1;
            static const int32_t BEGIN_VERSION = 6;
            auto isBeginVersion = pipelineContext && pipelineContext->GetMinPlatformVersion() >= BEGIN_VERSION;
            if (NearZero(lineHeight) || (!isBeginVersion && NearEqual(lineHeight, fontSize))) {
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
Rect ConvertSkRect(const Rosen::Drawing::RectF &skRect)
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
            LOGW("PlaceholderAlignment setting error! Now using default PlaceholderAlignment");
            break;
    }
    return convertValue;
}
#else
Rosen::PlaceholderVerticalAlignment ConvertPlaceholderAlignment(PlaceholderAlignment textDecoration)
{
    Rosen::PlaceholderVerticalAlignment convertValue =
        Rosen::PlaceholderVerticalAlignment::OFFSET_AT_BASELINE;
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
            LOGW("PlaceholderAlignment setting error! Now using default PlaceholderAlignment");
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
