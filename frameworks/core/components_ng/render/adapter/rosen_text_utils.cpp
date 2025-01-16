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
#include "core/components_ng/render/text_utils.h"

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/paragraph_builder.h"
#include "txt/paragraph_style.h"
#include "txt/paragraph_txt.h"
#else
#include "rosen_text/typography.h"
#include "rosen_text/typography_create.h"
#include "rosen_text/typography_style.h"
#endif

#include "core/components/font/constants_converter.h"
#include "core/components/font/rosen_font_collection.h"
#include "core/components/text/text_theme.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

const std::string FONTWEIGHT = "wght";
const std::u16string ELLIPSIS = u"\u2026";

bool IsApplyIndent(const MeasureContext& context, double& indent)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    if (context.textIndent.value().Unit() != DimensionUnit::PERCENT) {
        indent = context.textIndent.value().ConvertToPx();
        return true;
    } else {
        if (context.constraintWidth.has_value()) {
            indent = context.constraintWidth.value().ConvertToPx() * context.textIndent.value().Value();
            return true;
        }
    }
    return false;
}

void ApplyLineHeightInNumUnit(const MeasureContext& context, Rosen::TextStyle& txtStyle)
{
    auto lineHeight = context.lineHeight.value().ConvertToPx();
    txtStyle.heightOnly = true;
    if (!NearEqual(lineHeight, txtStyle.fontSize) && (lineHeight > 0.0) && (!NearZero(txtStyle.fontSize))) {
        txtStyle.heightScale = lineHeight / txtStyle.fontSize;
    } else {
        txtStyle.heightScale = 1;
        static const int32_t BEGIN_VERSION = 6;
        auto pipelineContext = PipelineBase::GetCurrentContextSafely();
        auto isBeginVersion = pipelineContext && pipelineContext->GetMinPlatformVersion() >= BEGIN_VERSION;
        if (NearZero(lineHeight) || (!isBeginVersion && NearEqual(lineHeight, txtStyle.fontSize))) {
            txtStyle.heightOnly = false;
        }
    }
}

double TextUtils::MeasureText(const MeasureContext& context)
{
    using namespace Constants;
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::ParagraphStyle style;
#else
    Rosen::TypographyStyle style;
#endif
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("fontCollection is null");
        return 0.0;
    }
#ifndef USE_GRAPHIC_TEXT_GINE
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
#else
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
#endif
    std::vector<std::string> fontFamilies;
    if (context.fontSize) {
#ifndef USE_GRAPHIC_TEXT_GINE
        txtStyle.font_size = context.fontSize.value().ConvertToPx();
#else
        txtStyle.fontSize = context.fontSize.value().ConvertToPx();
#endif
    } else {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, 0.0);
        auto textTheme = pipelineContext->GetTheme<TextTheme>();
#ifndef USE_GRAPHIC_TEXT_GINE
        txtStyle.font_size = textTheme->GetTextStyle().GetFontSize().ConvertToPx();
#else
        txtStyle.fontSize = textTheme->GetTextStyle().GetFontSize().ConvertToPx();
#endif
    }
#ifndef USE_GRAPHIC_TEXT_GINE
    txtStyle.font_style = ConvertTxtFontStyle(context.fontStyle);
    FontWeight fontWeightStr = StringUtils::StringToFontWeight(context.fontWeight);
    txtStyle.font_weight = ConvertTxtFontWeight(fontWeightStr);
    StringUtils::StringSplitter(context.fontFamily, ',', fontFamilies);
    txtStyle.font_families = fontFamilies;
    if (context.letterSpacing.has_value()) {
        txtStyle.letter_spacing = context.letterSpacing.value().ConvertToPx();
    }
#else
    txtStyle.fontStyle = ConvertTxtFontStyle(context.fontStyle);
    FontWeight fontWeightStr = StringUtils::StringToFontWeight(context.fontWeight);
    txtStyle.fontWeight = ConvertTxtFontWeight(fontWeightStr);
    auto fontWeightValue = (static_cast<int32_t>(ConvertTxtFontWeight(fontWeightStr)) + 1) * 100;
    auto pipelineContext = PipelineBase::GetCurrentContextSafely();
    if (pipelineContext) {
        fontWeightValue = fontWeightValue * pipelineContext->GetFontWeightScale();
    }
    txtStyle.fontVariations.SetAxisValue(FONTWEIGHT, fontWeightValue);
    StringUtils::StringSplitter(context.fontFamily, ',', fontFamilies);
    txtStyle.fontFamilies = fontFamilies;
    if (context.letterSpacing.has_value()) {
        txtStyle.letterSpacing = context.letterSpacing.value().ConvertToPx();
    }
#endif

    builder->PushStyle(txtStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    builder->AddText(StringUtils::Str8ToStr16(context.textContent));
    auto paragraph = builder->Build();
#else
    builder->AppendText(StringUtils::Str8ToStr16(context.textContent));
    auto paragraph = builder->CreateTypography();
#endif
    if (!paragraph) {
        return 0.0;
    }
    paragraph->Layout(Size::INFINITE_SIZE);
#ifndef USE_GRAPHIC_TEXT_GINE
    return std::ceil(paragraph->GetLongestLine());
#else
    return std::ceil(paragraph->GetActualWidth());
#endif
}

Size TextUtils::MeasureTextSize(const MeasureContext& context)
{
    using namespace Constants;
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("fontCollection is null");
        return Size(0.0, 0.0);
    }
    ACE_TEXT_SCOPED_TRACE("MeasureTextSizeInner");
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(context.textAlign);
#else
    Rosen::TypographyStyle style;
    style.textAlign = ConvertTxtTextAlign(context.textAlign);
#endif
    if (context.textOverlayFlow == TextOverflow::ELLIPSIS) {
#ifndef USE_GRAPHIC_TEXT_GINE
        style.ellipsis = ELLIPSIS;
#else
        style.ellipsis = ELLIPSIS;
#endif
    }
    if (GreatNotEqual(context.maxlines, 0.0)) {
#ifndef USE_GRAPHIC_TEXT_GINE
        style.max_lines = context.maxlines;
#else
        style.maxLines = context.maxlines;
#endif
    }
#ifndef USE_GRAPHIC_TEXT_GINE
    style.word_break_type = static_cast<minikin::WordBreakType>(context.wordBreak);
#else
    style.wordBreakType = static_cast<Rosen::WordBreakType>(context.wordBreak);
#endif
#ifndef USE_GRAPHIC_TEXT_GINE
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
#else
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
#endif
    std::vector<std::string> fontFamilies;
    if (context.fontSize.has_value()) {
#ifndef USE_GRAPHIC_TEXT_GINE
        txtStyle.font_size = context.fontSize.value().ConvertToPx();
#else
        txtStyle.fontSize = context.fontSize.value().ConvertToPx();
#endif
    } else {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, Size(0.0, 0.0));
        auto textTheme = pipelineContext->GetTheme<TextTheme>();
#ifndef USE_GRAPHIC_TEXT_GINE
        txtStyle.font_size = textTheme->GetTextStyle().GetFontSize().ConvertToPx();
#else
        txtStyle.fontSize = textTheme->GetTextStyle().GetFontSize().ConvertToPx();
#endif
    }
#ifndef USE_GRAPHIC_TEXT_GINE
    txtStyle.font_style = ConvertTxtFontStyle(context.fontStyle);
#else
    txtStyle.fontStyle = ConvertTxtFontStyle(context.fontStyle);
#endif
    FontWeight fontWeightStr = StringUtils::StringToFontWeight(context.fontWeight);
#ifndef USE_GRAPHIC_TEXT_GINE
    txtStyle.font_weight = ConvertTxtFontWeight(fontWeightStr);
#else
    txtStyle.fontWeight = ConvertTxtFontWeight(fontWeightStr);
    auto fontWeightValue = (static_cast<int32_t>(ConvertTxtFontWeight(fontWeightStr)) + 1) * 100;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    if (pipelineContext) {
        fontWeightValue = fontWeightValue * pipelineContext->GetFontWeightScale();
    }
    txtStyle.fontVariations.SetAxisValue(FONTWEIGHT, fontWeightValue);
#endif
    StringUtils::StringSplitter(context.fontFamily, ',', fontFamilies);
#ifndef USE_GRAPHIC_TEXT_GINE
    txtStyle.font_families = fontFamilies;
#else
    txtStyle.fontFamilies = fontFamilies;
#endif
    if (context.letterSpacing.has_value()) {
#ifndef USE_GRAPHIC_TEXT_GINE
        txtStyle.letter_spacing = context.letterSpacing.value().ConvertToPx();
#else
        txtStyle.letterSpacing = context.letterSpacing.value().ConvertToPx();
#endif
    }
    if (context.lineHeight.has_value()) {
        if (context.lineHeight->Unit() == DimensionUnit::PERCENT) {
#ifndef USE_GRAPHIC_TEXT_GINE
            txtStyle.has_height_override = true;
            txtStyle.height = context.lineHeight->Value();
#else
            txtStyle.heightOnly = true;
            txtStyle.heightScale = context.lineHeight->Value();
#endif
        } else {
#ifndef USE_GRAPHIC_TEXT_GINE
            auto lineHeight = context.lineHeight.value().ConvertToPx();
            if (!NearEqual(lineHeight, txtStyle.font_size) && (lineHeight > 0.0) && (!NearZero(txtStyle.font_size))) {
                txtStyle.height = lineHeight / txtStyle.font_size;
                txtStyle.has_height_override = true;
            }
#else
            ApplyLineHeightInNumUnit(context, txtStyle);
#endif
        }
    }
    builder->PushStyle(txtStyle);
    std::string content = context.textContent;
    StringUtils::TransformStrCase(content, static_cast<int32_t>(context.textCase));
#ifndef USE_GRAPHIC_TEXT_GINE
    builder->AddText(StringUtils::Str8ToStr16(content));
    auto paragraph = builder->Build();
#else
    builder->AppendText(StringUtils::Str8ToStr16(content));
    auto paragraph = builder->CreateTypography();
#endif
    if (!paragraph) {
        return Size(0.0, 0.0);
    }
    if (context.textIndent.has_value() && !LessOrEqual(context.textIndent.value().Value(), 0.0)) {
        double indent = 0.0;
        // first line indent
        if (IsApplyIndent(context, indent)) {
            std::vector<float> indents;
            // only indent first line
            indents.emplace_back(static_cast<float>(indent));
            indents.emplace_back(0.0);
            paragraph->SetIndents(indents);
        }
    }
    if (context.constraintWidth.has_value()) {
        paragraph->Layout(context.constraintWidth.value().ConvertToPx());
    } else {
        paragraph->Layout(Size::INFINITE_SIZE);
    }
    double textWidth = 0.0;
#ifndef USE_GRAPHIC_TEXT_GINE
    auto* paragraphTxt = static_cast<txt::ParagraphTxt*>(paragraph.get());
#else
    auto* paragraphTxt = static_cast<Rosen::Typography*>(paragraph.get());
#endif
    if (paragraphTxt->GetLineCount() == 1 && !context.isReturnActualWidth) {
#ifndef USE_GRAPHIC_TEXT_GINE
        textWidth = std::max(paragraph->GetLongestLine(), paragraph->GetMaxIntrinsicWidth());
#else
        textWidth = std::max(paragraph->GetActualWidth(), paragraph->GetMaxIntrinsicWidth());
#endif
    } else {
#ifndef USE_GRAPHIC_TEXT_GINE
        textWidth = paragraph->GetLongestLine();
#else
        textWidth = paragraph->GetActualWidth();
#endif
    }
    auto sizeWidth = std::min(paragraph->GetMaxWidth(), textWidth);
    sizeWidth =
        context.constraintWidth.has_value() ? context.constraintWidth.value().ConvertToPx() : std::ceil(sizeWidth);

    float baselineOffset = 0.0;
    if (context.baselineOffset.has_value()) {
        baselineOffset = static_cast<float>(context.baselineOffset.value().ConvertToPx());
    }
    float heightFinal = static_cast<float>(paragraph->GetHeight()) + std::fabs(baselineOffset);

    return Size(sizeWidth, heightFinal);
}

} // namespace OHOS::Ace::NG
