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

#include "base/utils/utf_helper.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "draw/canvas.h"

namespace OHOS::Ace::NG {
namespace {
constexpr TextCase DEFAULT_TEXT_CASE = TextCase::NORMAL;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE_VALUE = Ace::FontStyle::NORMAL;
constexpr Dimension DEFAULT_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
constexpr Dimension DEFAULT_BASELINE_OFFSET { 0.0, DimensionUnit::FP };
std::string g_strValue;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_32 = 32;
constexpr int DEFAULT_LENGTH = 4;
void SetSpanContent(ArkUINodeHandle node, const char* value)
{
    CHECK_NULL_VOID(value);
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    std::string content(value);
    SpanModelNG::InitSpan(uiNode, UtfUtils::Str8DebugToStr16(content));
}

const char* GetSpanContent(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, nullptr);
    g_strValue = UtfUtils::Str16DebugToStr8(SpanModelNG::GetContent(uiNode));
    return g_strValue.c_str();
}

void SetSpanSrc(ArkUINodeHandle node, ArkUI_CharPtr src)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    std::string content(src);
    SpanModelNG::InitSpan(uiNode, UtfUtils::Str8DebugToStr16(content));
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
    SpanModelNG::ResetTextCase(uiNode);
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
    SpanModelNG::ResetFontWeight(uiNode);
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
    SpanModelNG::ResetLineHeight(uiNode);
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
    SpanModelNG::ResetItalicFontStyle(uiNode);
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
    SpanModelNG::ResetFontSize(uiNode);
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
    SpanModelNG::ResetFontFamily(uiNode);
}

void SetSpanDecoration(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style)
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
    decoration->style = static_cast<int32_t>(SpanModelNG::GetTextDecorationStyle(uiNode));
}

void ResetSpanDecoration(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::ResetTextDecoration(uiNode);
    SpanModelNG::ResetTextDecorationStyle(uiNode);
    SpanModelNG::ResetTextDecorationColor(uiNode);
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
    SpanModelNG::ResetTextColor(uiNode);
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
    SpanModelNG::ResetLetterSpacing(uiNode);
}

void SetSpanBaselineOffset(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetBaselineOffset(uiNode, CalcDimension(value, (DimensionUnit)unit));
}

float GetSpanBaselineOffset(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, 0.0f);
    return SpanModelNG::GetBaselineOffset(uiNode).ConvertToVp();
}

void ResetSpanBaselineOffset(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    SpanModelNG::SetBaselineOffset(uiNode, DEFAULT_BASELINE_OFFSET);
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
    SpanModelNG::ResetFont(uiNode);
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
    options->bottomRight= styleOptions.backgroundRadius->radiusBottomRight->Value();
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
    SpanModelNG::ResetTextShadow(frameNode);
}

void SetAccessibilityText(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string valueStr = value;
    SpanModelNG::SetAccessibilityText(frameNode, valueStr);
}

void ResetAccessibilityText(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetAccessibilityText(frameNode, "");
}

void SetAccessibilityDescription(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string valueStr = value;
    SpanModelNG::SetAccessibilityDescription(frameNode, valueStr);
}

void ResetAccessibilityDescription(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetAccessibilityDescription(frameNode, "");
}

void SetAccessibilityLevel(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string valueStr = value;
    SpanModelNG::SetAccessibilityImportance(frameNode, valueStr);
}

void ResetAccessibilityLevel(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SpanModelNG::SetAccessibilityImportance(frameNode, "");
}

ArkUI_CharPtr GetSpanFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    std::vector<std::string> fontFamilies = SpanModelNG::GetSpanFontFamily(frameNode);
    std::string families;
    //set index start
    uint32_t index = 0;
    for (auto& family : fontFamilies) {
        families += family;
        if (index != fontFamilies.size() - 1) {
            families += ",";
        }
        index++;
    }
    g_strValue = families;
    return g_strValue.c_str();
}
} // namespace
namespace NodeModifier {
const ArkUISpanModifier* GetSpanModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISpanModifier modifier = {
        .setSpanSrc = SetSpanSrc,
        .setContent = SetSpanContent,
        .setSpanTextCase = SetSpanTextCase,
        .resetSpanTextCase = ResetSpanTextCase,
        .setSpanFontWeight = SetSpanFontWeight,
        .resetSpanFontWeight = ResetSpanFontWeight,
        .setSpanLineHeight = SetSpanLineHeight,
        .resetSpanLineHeight = ResetSpanLineHeight,
        .setSpanFontStyle = SetSpanFontStyle,
        .resetSpanFontStyle = ResetSpanFontStyle,
        .setSpanFontSize = SetSpanFontSize,
        .resetSpanFontSize = ResetSpanFontSize,
        .setSpanFontFamily = SetSpanFontFamily,
        .resetSpanFontFamily = ResetSpanFontFamily,
        .setSpanDecoration = SetSpanDecoration,
        .resetSpanDecoration = ResetSpanDecoration,
        .setSpanFontColor = SetSpanFontColor,
        .resetSpanFontColor = ResetSpanFontColor,
        .setSpanLetterSpacing = SetSpanLetterSpacing,
        .resetSpanLetterSpacing = ResetSpanLetterSpacing,
        .setSpanBaselineOffset = SetSpanBaselineOffset,
        .resetSpanBaselineOffset = ResetSpanBaselineOffset,
        .setSpanFont = SetSpanFont,
        .resetSpanFont = ResetSpanFont,
        .setSpanFontWeightStr = SetSpanFontWeightStr,
        .getSpanContent = GetSpanContent,
        .getSpanDecoration = GetSpanDecoration,
        .getSpanFontColor = GetSpanFontColor,
        .getSpanFontSize = GetSpanFontSize,
        .getSpanFontStyle = GetSpanFontStyle,
        .getSpanFontWeight = GetSpanFontWeight,
        .getSpanLineHeight = GetSpanLineHeight,
        .getSpanTextCase = GetSpanTextCase,
        .getSpanLetterSpacing = GetSpanLetterSpacing,
        .getSpanBaselineOffset = GetSpanBaselineOffset,
        .setSpanTextBackgroundStyle = SetSpanTextBackgroundStyle,
        .resetSpanTextBackgroundStyle = ResetSpanTextBackgroundStyle,
        .getSpanTextBackgroundStyle = GetSpanTextBackgroundStyle,
        .setTextShadow = SetTextTextShadow,
        .resetTextShadow = ResetTextTextShadow,
        .getTextShadows = GetTextShadow,
        .getSpanFontFamily = GetSpanFontFamily,
        .setAccessibilityText = SetAccessibilityText,
        .resetAccessibilityText = ResetAccessibilityText,
        .setAccessibilityDescription = SetAccessibilityDescription,
        .resetAccessibilityDescription = ResetAccessibilityDescription,
        .setAccessibilityLevel = SetAccessibilityLevel,
        .resetAccessibilityLevel = ResetAccessibilityLevel,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUISpanModifier* GetCJUISpanModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUISpanModifier modifier = {
        .setSpanSrc = SetSpanSrc,
        .setContent = SetSpanContent,
        .setSpanTextCase = SetSpanTextCase,
        .resetSpanTextCase = ResetSpanTextCase,
        .setSpanFontWeight = SetSpanFontWeight,
        .resetSpanFontWeight = ResetSpanFontWeight,
        .setSpanLineHeight = SetSpanLineHeight,
        .resetSpanLineHeight = ResetSpanLineHeight,
        .setSpanFontStyle = SetSpanFontStyle,
        .resetSpanFontStyle = ResetSpanFontStyle,
        .setSpanFontSize = SetSpanFontSize,
        .resetSpanFontSize = ResetSpanFontSize,
        .setSpanFontFamily = SetSpanFontFamily,
        .resetSpanFontFamily = ResetSpanFontFamily,
        .setSpanDecoration = SetSpanDecoration,
        .resetSpanDecoration = ResetSpanDecoration,
        .setSpanFontColor = SetSpanFontColor,
        .resetSpanFontColor = ResetSpanFontColor,
        .setSpanLetterSpacing = SetSpanLetterSpacing,
        .resetSpanLetterSpacing = ResetSpanLetterSpacing,
        .setSpanBaselineOffset = SetSpanBaselineOffset,
        .resetSpanBaselineOffset = ResetSpanBaselineOffset,
        .setSpanFont = SetSpanFont,
        .resetSpanFont = ResetSpanFont,
        .setSpanFontWeightStr = SetSpanFontWeightStr,
        .getSpanContent = GetSpanContent,
        .getSpanDecoration = GetSpanDecoration,
        .getSpanFontColor = GetSpanFontColor,
        .getSpanFontSize = GetSpanFontSize,
        .getSpanFontStyle = GetSpanFontStyle,
        .getSpanFontWeight = GetSpanFontWeight,
        .getSpanLineHeight = GetSpanLineHeight,
        .getSpanTextCase = GetSpanTextCase,
        .getSpanLetterSpacing = GetSpanLetterSpacing,
        .getSpanBaselineOffset = GetSpanBaselineOffset,
        .setSpanTextBackgroundStyle = SetSpanTextBackgroundStyle,
        .resetSpanTextBackgroundStyle = ResetSpanTextBackgroundStyle,
        .getSpanTextBackgroundStyle = GetSpanTextBackgroundStyle,
        .setTextShadow = SetTextTextShadow,
        .resetTextShadow = ResetTextTextShadow,
        .getTextShadows = GetTextShadow,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

void SetCustomSpanOnMeasure(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<CustomSpanNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::function<CustomSpanMetrics(CustomSpanMeasureInfo)> onMeasureFunc =
        [node, extraParam](CustomSpanMeasureInfo customSpanMeasureInfo) -> CustomSpanMetrics {
        ArkUICustomNodeEvent event;
        event.kind = ArkUIAPINodeFlags::CUSTOM_MEASURE;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.numberData[0].f32 = customSpanMeasureInfo.fontSize;
        event.numberReturnData[0].f32 = 0.0f;
        event.numberReturnData[1].f32 = 0.0f;
        SendArkUIAsyncCustomEvent(&event);
        float width = std::max(event.numberReturnData[0].f32, 0.0f);
        float height = std::max(event.numberReturnData[1].f32, 0.0f);
        return { width, height };
    };
    frameNode->GetSpanItem()->onMeasure = onMeasureFunc;
}

void SetCustomSpanOnDraw(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<CustomSpanNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::function<void(NG::DrawingContext&, CustomSpanOptions)> onDrawFunc =
        [node, extraParam](NG::DrawingContext& context, CustomSpanOptions customSpanOptions) {
        auto canvas = reinterpret_cast<uintptr_t>(&context.canvas);
        ArkUICustomNodeEvent event;
        event.kind = ArkUIAPINodeFlags::CUSTOM_DRAW;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.data[NUM_0] = (ArkUI_Int32)(canvas & 0xffffffff);
        event.data[NUM_1] =
            (ArkUI_Int32)((static_cast<uint64_t>(canvas) >> NUM_32) & 0xffffffff);
        event.data[NUM_2] = context.width;
        event.data[NUM_3] = context.height;
        event.canvas = reinterpret_cast<intptr_t>(&context.canvas);
        event.numberData[0].f32 = customSpanOptions.x;
        event.numberData[1].f32 = customSpanOptions.lineTop;
        event.numberData[2].f32 = customSpanOptions.lineBottom;
        event.numberData[3].f32 = customSpanOptions.baseline;
        // clip
        context.canvas.Save();
        auto clipInnerRect = RSRect(0, 0, context.width, context.height);
        context.canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
        SendArkUIAsyncCustomEvent(&event);
        context.canvas.Restore();
    };
    frameNode->GetSpanItem()->onDraw = onDrawFunc;
}
} // namespace NodeModifier

} // namespace OHOS::Ace::NG
