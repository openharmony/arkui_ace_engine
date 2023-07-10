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

#include "rosen_text/typography_style.h"
#include "rosen_text/typography_create.h"

#include "base/i18n/localization.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace::Constants {

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
            LOGW("TextDirection setting error! Now using default TextDirection");
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
            LOGW("TextDecoration setting error! Now using default TextDecoration");
            break;
    }
    return convertValue;
}

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
#if defined (FLUTTER_2_5) || defined (NEW_SKIA)
#else
        txtShadow.blurRadius = spanShadow.GetBlurRadius();
#endif
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

Rect ConvertSkRect(const Rosen::Drawing::RectF &skRect)
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

void ConvertPlaceholderRun(const PlaceholderRun& span, Rosen::PlaceholderSpan& txtSpan)
{
    txtSpan.width = span.width;
    txtSpan.height = span.height;
    txtSpan.alignment = ConvertPlaceholderAlignment(span.alignment);
    txtSpan.baseline = ConvertTxtTextBaseline(span.baseline);
    txtSpan.baselineOffset = span.baseline_offset;
}
} // namespace OHOS::Ace::Constants
