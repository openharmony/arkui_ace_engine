/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_text_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components/common/properties/text_style.h"
#include "frameworks/core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
constexpr Dimension DEFAULT_LINE_HEIGHT = Dimension(0.0, DimensionUnit::PX);
constexpr TextDecoration DEFAULT_TEXT_DECORATION = TextDecoration::NONE;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr TextCase DEFAULT_TEXT_CASE = TextCase::NORMAL;
constexpr uint32_t DEFAULT_MAX_LINE = Infinity<uint32_t>();
constexpr bool DEFAULT_TEXT_DRAGGABLE = false;
constexpr Dimension DEFAULT_MAX_FONT_SIZE;
constexpr Dimension DEFAULT_MIN_FONT_SIZE;
constexpr CopyOptions DEFAULT_COPY_OPTION = CopyOptions::None;
constexpr Dimension DEFAULT_BASELINE_OFFSET = 0.0_fp;
constexpr Dimension DEFAULT_FONT_SIZE = 16.0_fp;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::string DEFAULT_FAMILY = "HarmonyOS Sans";
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
const std::vector<OHOS::Ace::TextAlign> TEXT_ALIGNS = { OHOS::Ace::TextAlign::START, OHOS::Ace::TextAlign::CENTER,
    OHOS::Ace::TextAlign::END, OHOS::Ace::TextAlign::JUSTIFY, OHOS::Ace::TextAlign::LEFT, OHOS::Ace::TextAlign::RIGHT };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };

FontWeight ConvertStrToFontWeight(const char* weight, FontWeight defaultFontWeight = FontWeight::NORMAL)
{
    std::string weightStr(weight);
    return StringUtils::StringToFontWeight(weightStr, defaultFontWeight);
}

namespace {
void SetTextContext(ArkUINodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string content(value);
    TextModelNG::InitText(frameNode, content);
}

void SetFontWeight(ArkUINodeHandle node, const char* weight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetFontWeight(frameNode, ConvertStrToFontWeight(weight));
}

void ResetFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetFontWeight(frameNode, Ace::FontWeight::NORMAL);
}

void SetFontStyle(ArkUINodeHandle node, uint32_t fontStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (fontStyle < 0 || fontStyle >= FONT_STYLES.size()) {
        return;
    }
    TextModelNG::SetItalicFontStyle(frameNode, FONT_STYLES[fontStyle]);
}

void ResetFontStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetItalicFontStyle(frameNode, OHOS::Ace::FontStyle::NORMAL);
}

void SetTextAlign(ArkUINodeHandle node, uint32_t testAlign)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (testAlign < 0 || testAlign >= TEXT_ALIGNS.size()) {
        return;
    }
    TextModelNG::SetTextAlign(frameNode, TEXT_ALIGNS[testAlign]);
}

void ResetTextAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextAlign(frameNode, OHOS::Ace::TextAlign::START);
}

void SetFontColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextColor(frameNode, Color(color));
}

void ResetFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color textColor;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    textColor = theme->GetTextStyle().GetTextColor();
    TextModelNG::SetTextColor(frameNode, textColor);
}

void SetFontSize(ArkUINodeHandle node,  double fontSize, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);

    if (fontSize < 0 || unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC ||
        unitEnum == OHOS::Ace::DimensionUnit::PERCENT) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
        TextModelNG::SetFontSize(frameNode, fontSize);
    } else {
        TextModelNG::SetFontSize(frameNode, Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit)));
    }
}

void ResetFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
    TextModelNG::SetFontSize(frameNode, fontSize);
}

void SetTextLineHeight(ArkUINodeHandle node, const ArkUI_Float64 number, const ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLineHeight(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetTextLineHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLineHeight(frameNode, DEFAULT_LINE_HEIGHT);
}

void SetTextTextOverflow(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextOverflow valueTextOverflow = static_cast<TextOverflow>(value);
    TextModelNG::SetTextOverflow(frameNode, valueTextOverflow);
}

void ResetTextTextOverflow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextOverflow(frameNode, TextOverflow::NONE);
}

void SetTextDecoration(ArkUINodeHandle node, const int32_t decoration, const uint32_t color, const int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDecoration(frameNode, static_cast<TextDecoration>(decoration));
    TextModelNG::SetTextDecorationColor(frameNode, Color(color));
    TextModelNG::SetTextDecorationStyle(frameNode, static_cast<TextDecorationStyle>(style));
}

void ResetTextDecoration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDecoration(frameNode, DEFAULT_TEXT_DECORATION);
    TextModelNG::SetTextDecorationColor(frameNode, DEFAULT_DECORATION_COLOR);
    TextModelNG::SetTextDecorationStyle(frameNode, DEFAULT_DECORATION_STYLE);
}

void SetTextTextCase(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextCase(frameNode, static_cast<TextCase>(value));
}

void ResetTextTextCase(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextCase(frameNode, DEFAULT_TEXT_CASE);
}

void SetTextMaxLines(ArkUINodeHandle node, uint32_t maxLine)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMaxLines(frameNode, maxLine);
}

void ResetTextMaxLines(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetMaxLines(frameNode, DEFAULT_MAX_LINE);
}

void SetTextMinFontSize(ArkUINodeHandle node, const ArkUI_Float64 number, const ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMinFontSize(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ReSetTextMinFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMinFontSize(frameNode, DEFAULT_MIN_FONT_SIZE);
}

void SetTextDraggable(ArkUINodeHandle node, uint32_t draggable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetDraggable(frameNode, static_cast<bool>(draggable));
}

void ResetTextDraggable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetDraggable(frameNode, DEFAULT_TEXT_DRAGGABLE);
}

void SetTextMaxFontSize(ArkUINodeHandle node, const ArkUI_Float64 number, const ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMaxFontSize(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetTextMaxFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetAdaptMaxFontSize(frameNode, DEFAULT_MAX_FONT_SIZE);
}

void SetTextFontFamily(ArkUINodeHandle node, const char** fontFamilies, uint32_t length)
{
    CHECK_NULL_VOID(fontFamilies);
    if (length <= 0) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> families;
    for (uint32_t i = 0; i < length; i++) {
        const char* family = *(fontFamilies + i);
        if (family != nullptr) {
            families.emplace_back(std::string(family));
        }
    }
    TextModelNG::SetFontFamily(frameNode, families);
}

void ResetTextFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> families;
    families.emplace_back(DEFAULT_FAMILY);
    TextModelNG::SetFontFamily(frameNode, families);
}

void SetTextCopyOption(ArkUINodeHandle node, const int32_t copyOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetCopyOption(frameNode, static_cast<CopyOptions>(copyOption));
}

void ResetTextCopyOption(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetCopyOption(frameNode, DEFAULT_COPY_OPTION);
}

void SetTextTextShadow(ArkUINodeHandle node, struct TextShadowStruct* shadows, uint32_t length)
{
    CHECK_NULL_VOID(shadows);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Shadow> shadowList(length);
    for (uint32_t i = 0; i < length; i++) {
        Shadow shadow;
        TextShadowStruct* shadowStruct = shadows + i;
        shadow.SetBlurRadius(shadowStruct->radius);
        shadow.SetShadowType(static_cast<ShadowType>(shadowStruct->type));
        shadow.SetColor(Color(shadowStruct->color));
        shadow.SetOffsetX(shadowStruct->offsetX);
        shadow.SetOffsetY(shadowStruct->offsetY);
        shadow.SetIsFilled(static_cast<bool>(shadowStruct->fill));
        shadowList.at(i) = shadow;
    }
    TextModelNG::SetTextShadow(frameNode, shadowList);
}

void ResetTextTextShadow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Shadow shadow;
    shadow.SetOffsetX(0.0);
    shadow.SetOffsetY(0.0);
    TextModelNG::SetTextShadow(frameNode, std::vector<Shadow> { shadow });
}

void SetTextHeightAdaptivePolicy(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetHeightAdaptivePolicy(frameNode, HEIGHT_ADAPTIVE_POLICY[value]);
}

void ResetTextHeightAdaptivePolicy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetHeightAdaptivePolicy(frameNode, TextHeightAdaptivePolicy::MAX_LINES_FIRST);
}

void SetTextTextIndent(ArkUINodeHandle node, const struct StringAndDouble* textIndentStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension result;
    if (textIndentStruct->valueStr != nullptr) {
        result = StringUtils::StringToCalcDimension(textIndentStruct->valueStr, true, DimensionUnit::FP);
    } else {
        result = CalcDimension(textIndentStruct->value, DimensionUnit::FP);
    }
    TextModelNG::SetTextIndent(frameNode, result);
}

void ResetTextTextIndent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextIndent(frameNode, CalcDimension(0, DimensionUnit::FP));
}

void SetTextBaselineOffset(ArkUINodeHandle node, const struct StringAndDouble* offset)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension result(offset->value, DimensionUnit::FP);
    if (offset->valueStr != nullptr) {
        result = StringUtils::StringToCalcDimension(offset->valueStr, false, DimensionUnit::FP);
    }
    TextModelNG::SetBaselineOffset(frameNode, result);
}

void ResetTextBaselineOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetBaselineOffset(frameNode, DEFAULT_BASELINE_OFFSET);
}

void SetTextLetterSpacing(ArkUINodeHandle node, const struct StringAndDouble* letterSpacingStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    CalcDimension letterSpacing;
    if (letterSpacingStruct->valueStr != nullptr) {
        if (std::string(letterSpacingStruct->valueStr).back() == '%') {
            TextModelNG::SetLetterSpacing(frameNode, letterSpacing);
            return;
        } else {
            letterSpacing = StringUtils::StringToCalcDimension(
                std::string(letterSpacingStruct->valueStr), false, DimensionUnit::FP);
        }
    } else {
        letterSpacing = CalcDimension(letterSpacingStruct->value, DimensionUnit::FP);
    }
    TextModelNG::SetLetterSpacing(frameNode, letterSpacing);
}

void ResetTextLetterSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension letterSpacing(0.0, DimensionUnit::FP);
    TextModelNG::SetLetterSpacing(frameNode, letterSpacing);
}

void SetTextFont(ArkUINodeHandle node, const struct ArkUIFontStruct *fontInfo)
{
    CHECK_NULL_VOID(fontInfo);
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = Dimension(fontInfo->fontSizeNumber, static_cast<DimensionUnit>(fontInfo->fontSizeUnit));
    font.fontStyle = static_cast<Ace::FontStyle>(fontInfo->fontStyle);
    font.fontWeight = static_cast<FontWeight>(fontInfo->fontWeight);
    std::vector<std::string> families;
    if (fontInfo->fontFamilies && fontInfo->familyLength > 0) {
        families.resize(fontInfo->familyLength);
        for (uint32_t i = 0; i < fontInfo->familyLength; i++) {
            families.at(i) = std::string(*(fontInfo->fontFamilies + i));
        }
    }
    font.fontFamilies = families;
    TextModelNG::SetFont(frameNode, font);
}

void ResetTextFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = DEFAULT_FONT_SIZE;
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    std::vector<std::string> families;
    families.emplace_back(DEFAULT_FAMILY);
    font.fontFamilies = families;
    TextModelNG::SetFont(frameNode, font);
}
}

namespace NodeModifier {
const ArkUITextModifier* GetTextModifier()
{
    static const ArkUITextModifier modifier = { SetTextContext, SetFontWeight, ResetFontWeight, SetFontStyle,
        ResetFontStyle, SetTextAlign, ResetTextAlign, SetFontColor, ResetFontColor, SetFontSize, ResetFontSize,
        SetTextLineHeight, ResetTextLineHeight, SetTextTextOverflow, ResetTextTextOverflow, SetTextDecoration,
        ResetTextDecoration, SetTextTextCase, ResetTextTextCase, SetTextMaxLines, ResetTextMaxLines, SetTextMinFontSize,
        ReSetTextMinFontSize, SetTextDraggable, ResetTextDraggable, SetTextMaxFontSize, ResetTextMaxFontSize,
        SetTextFontFamily, ResetTextFontFamily, SetTextCopyOption, ResetTextCopyOption, SetTextTextShadow,
        ResetTextTextShadow, SetTextHeightAdaptivePolicy, ResetTextHeightAdaptivePolicy, SetTextTextIndent,
        ResetTextTextIndent, SetTextBaselineOffset, ResetTextBaselineOffset, SetTextLetterSpacing,
        ResetTextLetterSpacing, SetTextFont, ResetTextFont };

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG