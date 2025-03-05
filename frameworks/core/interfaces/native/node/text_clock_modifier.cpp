/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/interfaces/native/node/text_clock_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"

namespace OHOS::Ace::NG {
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
constexpr Ace::FontWeight DEFAULT_FONT_WEIGHT = Ace::FontWeight::NORMAL;
constexpr Dimension DEFAULT_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
const std::string DEFAULT_FONT_FAMILY = "HarmonyOS Sans";

namespace TextClockModifier {
void SetFormat(ArkUINodeHandle node, ArkUI_CharPtr format)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFormat(frameNode, format);
}

void ResetFormat(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFormat(frameNode, "");
}

void SetFontColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontColor(frameNode, Color(color));
}

void ResetFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    TextClockModelNG::SetFontColor(frameNode, theme->GetTextParseFailedColor());
}

void SetFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSizeValue, ArkUI_Int32 fontSizeUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontSize(frameNode, CalcDimension(fontSizeValue, (DimensionUnit)fontSizeUnit));
}

void ResetFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontSize(frameNode, DEFAULT_FONT_SIZE);
}

void SetFontStyle(ArkUINodeHandle node, ArkUI_Uint32 fontStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontStyle(frameNode, FONT_STYLES[fontStyle]);
}

void ResetFontStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
}

void SetFontWeight(ArkUINodeHandle node, ArkUI_CharPtr fontWeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontWeightStr = fontWeight;
    TextClockModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeightStr));
}

void ResetFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
}

void SetFontFamily(ArkUINodeHandle node, ArkUI_CharPtr fontFamily)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    TextClockModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void ResetFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = DEFAULT_FONT_FAMILY;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    TextClockModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void SetTextShadow(ArkUINodeHandle node, struct ArkUITextShadowStruct* shadows, ArkUI_Uint32 length)
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
    TextClockModelNG::SetTextShadow(frameNode, shadowList);
}

void ResetTextShadow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Shadow shadow;
    shadow.SetOffsetX(0.0);
    shadow.SetOffsetY(0.0);
    TextClockModelNG::SetTextShadow(frameNode, std::vector<Shadow> { shadow });
}

void SetFontFeature(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = value;
    TextClockModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void ResetFontFeature(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = "";
    TextClockModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void SetDateTimeOptions(ArkUINodeHandle node, ArkUI_Int32 hourType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ZeroPrefixType hour = static_cast<ZeroPrefixType>(hourType);
    TextClockModelNG::SetDateTimeOptions(frameNode, hour);
}

void ResetDateTimeOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ZeroPrefixType hourType = ZeroPrefixType::AUTO;
    TextClockModelNG::SetDateTimeOptions(frameNode, hourType);
}

void SetTextClockTimeZoneOffset(ArkUINodeHandle node, ArkUI_Float32 timeZoneOffset)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetHoursWest(frameNode, timeZoneOffset);
}
} // namespace TextClockModifier

namespace NodeModifier {
const ArkUITextClockModifier* GetTextClockModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITextClockModifier modifier = {
        .setFormat = TextClockModifier::SetFormat,
        .resetFormat = TextClockModifier::ResetFormat,
        .setFontColor = TextClockModifier::SetFontColor,
        .resetFontColor = TextClockModifier::ResetFontColor,
        .setFontSize = TextClockModifier::SetFontSize,
        .resetFontSize = TextClockModifier::ResetFontSize,
        .setFontStyle = TextClockModifier::SetFontStyle,
        .resetFontStyle = TextClockModifier::ResetFontStyle,
        .setFontWeight = TextClockModifier::SetFontWeight,
        .resetFontWeight = TextClockModifier::ResetFontWeight,
        .setFontFamily = TextClockModifier::SetFontFamily,
        .resetFontFamily = TextClockModifier::ResetFontFamily,
        .setTextShadow = TextClockModifier::SetTextShadow,
        .resetTextShadow = TextClockModifier::ResetTextShadow,
        .setFontFeature = TextClockModifier::SetFontFeature,
        .resetFontFeature = TextClockModifier::ResetFontFeature,
        .setDateTimeOptions = TextClockModifier::SetDateTimeOptions,
        .resetDateTimeOptions = TextClockModifier::ResetDateTimeOptions,
        .setTextClockTimeZoneOffset = TextClockModifier::SetTextClockTimeZoneOffset,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUITextClockModifier* GetCJUITextClockModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITextClockModifier modifier = {
        .setFormat = TextClockModifier::SetFormat,
        .resetFormat = TextClockModifier::ResetFormat,
        .setFontColor = TextClockModifier::SetFontColor,
        .resetFontColor = TextClockModifier::ResetFontColor,
        .setFontSize = TextClockModifier::SetFontSize,
        .resetFontSize = TextClockModifier::ResetFontSize,
        .setFontStyle = TextClockModifier::SetFontStyle,
        .resetFontStyle = TextClockModifier::ResetFontStyle,
        .setFontWeight = TextClockModifier::SetFontWeight,
        .resetFontWeight = TextClockModifier::ResetFontWeight,
        .setFontFamily = TextClockModifier::SetFontFamily,
        .resetFontFamily = TextClockModifier::ResetFontFamily,
        .setTextShadow = TextClockModifier::SetTextShadow,
        .resetTextShadow = TextClockModifier::ResetTextShadow,
        .setFontFeature = TextClockModifier::SetFontFeature,
        .resetFontFeature = TextClockModifier::ResetFontFeature,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
