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
#include "core/interfaces/native/node/node_span_modifier.h"

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_size.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
constexpr TextCase DEFAULT_TEXT_CASE = TextCase::NORMAL;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE_VALUE = Ace::FontStyle::NORMAL;
constexpr Dimension DEFAULT_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
constexpr TextDecoration DEFAULT_TEXT_DECORATION = TextDecoration::NONE;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
constexpr Dimension DEFAULT_LETTER_SPACING_VALUE { 0.0, DimensionUnit::FP };
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
const std::string DEFAULT_FONT_FAMILY = "HarmonyOS Sans";

void SetSpanContent(ArkUINodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string content(value);
    SpanModelNG::InitSpan(frameNode, content);
}

void SetSpanTextCase(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetTextCase(frameNode, static_cast<TextCase>(value));
}

void ResetSpanTextCase(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetTextCase(frameNode, DEFAULT_TEXT_CASE);
}

void SetSpanFontWeight(ArkUINodeHandle node, const char* value)a
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(value));
}

void ResetSpanFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
}

void SetSpanLineHeight(ArkUINodeHandle node, const double number, const int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetLineHeight(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ReSetSpanLineHeight(ArkUINodeHandle node)
{
    return;
}

void SetSpanFontStyle(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetItalicFontStyle(frameNode, static_cast<Ace::FontStyle>(value));
}

void ReSetSpanFontStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetItalicFontStyle(frameNode, DEFAULT_FONT_STYLE_VALUE);
}

void SetSpanFontSize(ArkUINodeHandle node, const double number, const int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetFontSize(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetSpanFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetFontSize(frameNode, DEFAULT_FONT_SIZE);
}

void SetSpanFontFamily(ArkUINodeHandle node, const char** fontFamilies, uint32_t length)
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
    SpanModelNG::SetFontFamily(frameNode, families);
}

void ResetSpanFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> families;
    families.emplace_back(DEFAULT_FONT_FAMILY);
    SpanModelNG::SetFontFamily(frameNode, families);
}

void SetSpanDecoration(ArkUINodeHandle node, const int32_t decoration, const uint32_t color, const uint32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetTextDecoration(frameNode, static_cast<TextDecoration>(decoration));
    SpanModelNG::SetTextDecorationStyle(frameNode, static_cast<TextDecorationStyle>(style));
    SpanModelNG::SetTextDecorationColor(frameNode, Color(color));
}

void ResetSpanDecoration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetTextDecoration(frameNode, DEFAULT_TEXT_DECORATION);
    SpanModelNG::SetTextDecorationStyle(frameNode, DEFAULT_DECORATION_STYLE);
    SpanModelNG::SetTextDecorationColor(frameNode, DEFAULT_DECORATION_COLOR);
}

void SetSpanFontColor(ArkUINodeHandle node, uint32_t textColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetTextColor(frameNode, Color(textColor));
}

void ResetSpanFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    uint32_t textColor = theme->GetTextStyle().GetTextColor().GetValue();
    SpanModelNG::SetTextColor(frameNode, Color(textColor));
}

void SetSpanLetterSpacing(ArkUINodeHandle node, const struct StringAndDouble* letterSpacingValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension result;
    if (letterSpacingValue->valueStr != nullptr) {
        result = StringUtils::StringToDimensionWithUnit(std::string(letterSpacingValue->valueStr), DimensionUnit::FP);
    } else {
        result = Dimension(letterSpacingValue->value, DimensionUnit::FP);
    }
    SpanModelNG::SetLetterSpacing(frameNode, result);
}

void ResetSpanLetterSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetLetterSpacing(frameNode, DEFAULT_LETTER_SPACING_VALUE);
}

void SetSpanFont(ArkUINodeHandle node, const struct ArkUIFontStruct* fontInfo)
{
    CHECK_NULL_VOID(fontInfo);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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
    SpanModelNG::SetFont(frameNode, font);
}

void ResetSpanFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = DEFAULT_FONT_SIZE;
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    std::vector<std::string> families;
    families.emplace_back(DEFAULT_FONT_FAMILY);
    font.fontFamilies = families;
    SpanModelNG::SetFont(frameNode, font);
}
} // namespace

namespace NodeModifier {
const ArkUISpanModifier* GetSpanModifier()
{
    static const ArkUISpanModifier modifier = { SetSpanContent, SetSpanTextCase, ResetSpanTextCase, SetSpanFontWeight,
        ResetSpanFontWeight, SetSpanLineHeight, ReSetSpanLineHeight, SetSpanFontStyle, ReSetSpanFontStyle,
        SetSpanFontSize, ResetSpanFontSize, SetSpanFontFamily, ResetSpanFontFamily, SetSpanDecoration,
        ResetSpanDecoration, SetSpanFontColor, ResetSpanFontColor, SetSpanLetterSpacing, ResetSpanLetterSpacing,
        SetSpanFont, ResetSpanFont };
    return &modifier;
}
} // namespace NodeModifier

} // namespace OHOS::Ace::NG