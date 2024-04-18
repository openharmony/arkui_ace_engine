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
std::string g_strValue;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int DEFAULT_LENGTH = 4;
void SetSpanContent(ArkUINodeHandle node, const char* value)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    std::string content(value);
    SpanModelNG::InitSpan(uiNode, content);
}

const char* GetSpanContent(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, nullptr);
    g_strValue = SpanModelNG::GetContent(uiNode);
    return g_strValue.c_str();
}

void SetSpanTextCase(ArkUINodeHandle node, int32_t value)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetTextCase(uiNode, static_cast<TextCase>(value));
}

int32_t GetSpanTextCase(ArkUINodeHandle node)
{
    auto defaultTextCase = static_cast<int32_t>(DEFAULT_TEXT_CASE);
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, defaultTextCase);
    return static_cast<int32_t>(SpanModelNG::GetTextCase(uiNode));
}

void ResetSpanTextCase(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetTextCase(uiNode, DEFAULT_TEXT_CASE);
}

void SetSpanFontWeightStr(ArkUINodeHandle node, const char* value)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetFontWeight(uiNode, Framework::ConvertStrToFontWeight(value));
}

void SetSpanFontWeight(ArkUINodeHandle node, ArkUI_Int32 fontWeight)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetFontWeight(uiNode, static_cast<FontWeight>(fontWeight));
}

int32_t GetSpanFontWeight(ArkUINodeHandle node)
{
    int32_t defaultFontWeight = static_cast<int32_t>(DEFAULT_FONT_WEIGHT);
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, defaultFontWeight);
    return static_cast<int32_t>(SpanModelNG::GetFontWeight(uiNode));
}

void ResetSpanFontWeight(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetFontWeight(uiNode, DEFAULT_FONT_WEIGHT);
}

void SetSpanLineHeight(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetLineHeight(uiNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

float GetSpanLineHeight(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, 0.0f);
    return SpanModelNG::GetTextLineHeight(uiNode).ConvertToVp();
}

void ResetSpanLineHeight(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    Dimension value(0.0f);
    SpanModelNG::SetLineHeight(uiNode, value);
}

void SetSpanFontStyle(ArkUINodeHandle node, int32_t value)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetItalicFontStyle(uiNode, static_cast<Ace::FontStyle>(value));
}

int32_t GetSpanFontStyle(ArkUINodeHandle node)
{
    int32_t defaultFontStyle = static_cast<int32_t>(DEFAULT_FONT_STYLE_VALUE);
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, defaultFontStyle);
    return static_cast<int32_t>(SpanModelNG::GetFontStyle(uiNode));
}

void ResetSpanFontStyle(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetItalicFontStyle(uiNode, DEFAULT_FONT_STYLE_VALUE);
}

void SetSpanFontSize(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetFontSize(uiNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

float GetSpanFontSize(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, DEFAULT_FONT_SIZE.Value());
    return SpanModelNG::GetFontSize(uiNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

void ResetSpanFontSize(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetFontSize(uiNode, DEFAULT_FONT_SIZE);
}

void SetSpanFontFamily(ArkUINodeHandle node, const char** fontFamilies, uint32_t length)
{
    CHECK_NULL_VOID(fontFamilies);
    if (length <= 0) {
        return;
    }
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    std::vector<std::string> families;
    for (uint32_t i = 0; i < length; i++) {
        const char* family = *(fontFamilies + i);
        if (family != nullptr) {
            families.emplace_back(std::string(family));
        }
    }
    SpanModelNG::SetFontFamily(uiNode, families);
}

void ResetSpanFontFamily(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    std::vector<std::string> families;
    families.emplace_back(DEFAULT_FONT_FAMILY);
    SpanModelNG::SetFontFamily(uiNode, families);
}

void SetSpanDecoration(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Uint32 style)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetTextDecoration(uiNode, static_cast<TextDecoration>(decoration));
    SpanModelNG::SetTextDecorationStyle(uiNode, static_cast<TextDecorationStyle>(style));
    SpanModelNG::SetTextDecorationColor(uiNode, Color(color));
}

void GetSpanDecoration(ArkUINodeHandle node, ArkUITextDecorationType* decoration)
{
    CHECK_NULL_VOID(decoration);
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    decoration->decorationType = static_cast<int32_t>(SpanModelNG::GetTextDecoration(uiNode));
    decoration->color = SpanModelNG::GetTextDecorationColor(uiNode).GetValue();
}

void ResetSpanDecoration(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetTextDecoration(uiNode, DEFAULT_TEXT_DECORATION);
    SpanModelNG::SetTextDecorationStyle(uiNode, DEFAULT_DECORATION_STYLE);
    SpanModelNG::SetTextDecorationColor(uiNode, DEFAULT_DECORATION_COLOR);
}

void SetSpanFontColor(ArkUINodeHandle node, uint32_t textColor)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetTextColor(uiNode, Color(textColor));
}

uint32_t GetSpanFontColor(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, Color::BLACK.GetValue());
    return SpanModelNG::GetFontColor(uiNode).GetValue();
}

void ResetSpanFontColor(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    uint32_t textColor = theme->GetTextStyle().GetTextColor().GetValue();
    SpanModelNG::SetTextColor(uiNode, Color(textColor));
}

void SetSpanLetterSpacing(ArkUINodeHandle node, const struct ArkUIStringAndFloat* letterSpacingValue)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    Dimension result;
    if (letterSpacingValue->valueStr != nullptr) {
        result = StringUtils::StringToDimensionWithUnit(std::string(letterSpacingValue->valueStr), DimensionUnit::FP);
    } else {
        result = Dimension(letterSpacingValue->value, DimensionUnit::FP);
    }
    SpanModelNG::SetLetterSpacing(uiNode, result);
}

float GetSpanLetterSpacing(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, 0.0f);
    return SpanModelNG::GetLetterSpacing(uiNode).ConvertToVp();
}

void ResetSpanLetterSpacing(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetLetterSpacing(uiNode, DEFAULT_LETTER_SPACING_VALUE);
}

void SetSpanFont(ArkUINodeHandle node, const struct ArkUIFontStruct* fontInfo)
{
    CHECK_NULL_VOID(fontInfo);
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
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
    SpanModelNG::SetFont(uiNode, font);
}

void ResetSpanFont(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    Font font;
    font.fontSize = DEFAULT_FONT_SIZE;
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    std::vector<std::string> families;
    families.emplace_back(DEFAULT_FONT_FAMILY);
    font.fontFamilies = families;
    SpanModelNG::SetFont(uiNode, font);
}

void SetSpanTextBackgroundStyle(
    ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    TextBackgroundStyle font;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    borderRadius.radiusTopRight = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    borderRadius.radiusBottomLeft = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    borderRadius.radiusBottomRight = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    font.backgroundColor = Color(color);
    font.backgroundRadius = borderRadius;
    font.backgroundRadius->multiValued = true;
    SpanModelNG::SetTextBackgroundStyle(uiNode, font);
}

void ResetSpanTextBackgroundStyle(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    TextBackgroundStyle font;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    font.backgroundColor = Color(0x00000000);
    font.backgroundRadius = borderRadius;
    font.backgroundRadius->multiValued = true;
    SpanModelNG::SetTextBackgroundStyle(uiNode, font);
}

void GetSpanTextBackgroundStyle(ArkUINodeHandle node, ArkUITextBackgroundStyleOptions* options)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    auto styleOptions = SpanModelNG::GetSpanTextBackgroundStyle(uiNode);
    options->color = styleOptions.backgroundColor->GetValue();
    options->topLeft = styleOptions.backgroundRadius->radiusTopLeft->Value();
    options->topRight = styleOptions.backgroundRadius->radiusTopRight->Value();
    options->bottomLeft = styleOptions.backgroundRadius->radiusBottomLeft->Value();
    options->bottomLeft = styleOptions.backgroundRadius->radiusBottomLeft->Value();
}

void SetTextTextShadow(ArkUINodeHandle node, struct ArkUITextShadowStruct* shadows, ArkUI_Uint32 length)
{
    CHECK_NULL_VOID(shadows);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Shadow> shadowList(length);
    for (uint32_t i = 0; i < length; i++) {
        Shadow shadow;
        ArkUITextShadowStruct* shadowStruct = shadows + i;
        shadow.SetBlurRadius(shadowStruct->radius);
        shadow.SetShadowType(static_cast<ShadowType>(shadowStruct->type));
        shadow.SetColor(Color(shadowStruct->color));
        shadow.SetOffsetX(shadowStruct->offsetX);
        shadow.SetOffsetY(shadowStruct->offsetY);
        shadow.SetIsFilled(static_cast<bool>(shadowStruct->fill));
        shadowList.at(i) = shadow;
    }
    SpanModelNG::SetTextShadow(frameNode, shadowList);
}

void GetTextShadow(ArkUINodeHandle node, ArkUITextShadowStruct* shadow, uint32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ArkUITextShadowStruct> shadowArray;
    auto textShadowVector = SpanModelNG::GetTextShadow(frameNode);
    for (uint32_t i = 0; i < size; i++) {
        if (i < textShadowVector.size()) {
            *(shadow + i) = { static_cast<float>(textShadowVector[i].GetBlurRadius()),
                static_cast<int32_t>(textShadowVector[i].GetShadowType()), textShadowVector[i].GetColor().GetValue(),
                textShadowVector[i].GetOffset().GetX(), textShadowVector[i].GetOffset().GetY(),
                textShadowVector[i].GetIsFilled() };
        } else {
            *(shadow + i) = { 0.0f, static_cast<int32_t>(ShadowType::COLOR), Color::TRANSPARENT.GetValue(), 0.0f, 0.0f,
                0 };
        }
    }
}

void ResetTextTextShadow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Shadow shadow;
    shadow.SetOffsetX(0.0);
    shadow.SetOffsetY(0.0);
    SpanModelNG::SetTextShadow(frameNode, std::vector<Shadow> { shadow });
}
} // namespace
namespace NodeModifier {
const ArkUISpanModifier* GetSpanModifier()
{
    static const ArkUISpanModifier modifier = { SetSpanContent, SetSpanTextCase, ResetSpanTextCase, SetSpanFontWeight,
        ResetSpanFontWeight, SetSpanLineHeight, ResetSpanLineHeight, SetSpanFontStyle, ResetSpanFontStyle,
        SetSpanFontSize, ResetSpanFontSize, SetSpanFontFamily, ResetSpanFontFamily, SetSpanDecoration,
        ResetSpanDecoration, SetSpanFontColor, ResetSpanFontColor, SetSpanLetterSpacing, ResetSpanLetterSpacing,
        SetSpanFont, ResetSpanFont, SetSpanFontWeightStr, GetSpanContent, GetSpanDecoration, GetSpanFontColor,
        GetSpanFontSize, GetSpanFontStyle, GetSpanFontWeight, GetSpanLineHeight, GetSpanTextCase, GetSpanLetterSpacing,
        SetSpanTextBackgroundStyle, ResetSpanTextBackgroundStyle, GetSpanTextBackgroundStyle, SetTextTextShadow,
        ResetTextTextShadow, GetTextShadow };
    return &modifier;
}
} // namespace NodeModifier

} // namespace OHOS::Ace::NG