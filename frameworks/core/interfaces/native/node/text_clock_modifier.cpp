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
#include "core/components_ng/pattern/text_clock/text_clock_event_hub.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
constexpr Ace::FontWeight DEFAULT_FONT_WEIGHT = Ace::FontWeight::NORMAL;
constexpr Dimension DEFAULT_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
const std::string DEFAULT_FONT_FAMILY_CLOCK = "HarmonyOS Sans";

namespace TextClockModifier {
void SetFormat(ArkUINodeHandle node, ArkUI_CharPtr format)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFormat(frameNode, format);
}

void SetFormatRes(ArkUINodeHandle node, ArkUI_CharPtr format, void* formatRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFormat(frameNode, format);
    if (SystemProperties::ConfigChangePerform()) {
        auto* format = reinterpret_cast<ResourceObject*>(formatRawPtr);
        auto formatResObj = AceType::Claim(format);
        TextClockModelNG::CreateWithFormatResourceObj(frameNode, formatResObj);
    }
}

void ResetFormat(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFormat(frameNode, "");
    if (SystemProperties::ConfigChangePerform()) {
        TextClockModelNG::CreateWithFormatResourceObj(frameNode, nullptr);
    }
}

void SetFontColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontColor(frameNode, Color(color));
}

void SetFontColorRes(ArkUINodeHandle node, ArkUI_Uint32 color, void* fontColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontColor(frameNode, Color(color));
    if (SystemProperties::ConfigChangePerform()) {
        auto* fontColor = reinterpret_cast<ResourceObject*>(fontColorRawPtr);
        auto pathColorResObj = AceType::Claim(fontColor);
        TextClockModelNG::CreateWithTextColorResourceObj(frameNode, pathColorResObj);
    }
}

void ResetFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextClockTheme>();
    CHECK_NULL_VOID(theme);
    TextClockModelNG::SetFontColor(frameNode, theme->GetTextParseFailedColor());
    if (SystemProperties::ConfigChangePerform()) {
        TextClockModelNG::SetFontColorByUser(frameNode, false);
        TextClockModelNG::CreateWithTextColorResourceObj(frameNode, nullptr);
    }
}

void SetFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSizeValue, ArkUI_Int32 fontSizeUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontSize(frameNode, CalcDimension(fontSizeValue, (DimensionUnit)fontSizeUnit));
}

void SetFontSizeRes(ArkUINodeHandle node, ArkUI_Float32 fontSizeValue, ArkUI_Int32 fontSizeUnit, void* fontSizeRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontSize(frameNode, CalcDimension(fontSizeValue, (DimensionUnit)fontSizeUnit));
    if (SystemProperties::ConfigChangePerform()) {
        auto* fontSize = reinterpret_cast<ResourceObject*>(fontSizeRawPtr);
        auto pathFontSizeResObj = AceType::Claim(fontSize);
        TextClockModelNG::CreateWithFontSizeResourceObj(frameNode, pathFontSizeResObj);
    }
}

void ResetFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontSize(frameNode, DEFAULT_FONT_SIZE);
    if (SystemProperties::ConfigChangePerform()) {
        TextClockModelNG::CreateWithFontSizeResourceObj(frameNode, nullptr);
    }
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

void SetFontWeightRes(ArkUINodeHandle node, ArkUI_CharPtr fontWeight, void* fontWeightRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontWeightStr = fontWeight;
    TextClockModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeightStr));
    if (SystemProperties::ConfigChangePerform()) {
        auto* fontWeight = reinterpret_cast<ResourceObject*>(fontWeightRawPtr);
        auto pathFontWeightResObj = AceType::Claim(fontWeight);
        TextClockModelNG::CreateWithFontWeightResourceObj(frameNode, pathFontWeightResObj);
    }
}

void ResetFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
    if (SystemProperties::ConfigChangePerform()) {
        TextClockModelNG::CreateWithFontWeightResourceObj(frameNode, nullptr);
    }
}

void SetFontFamily(ArkUINodeHandle node, ArkUI_CharPtr fontFamily)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    TextClockModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void SetFontFamilyRes(ArkUINodeHandle node, ArkUI_CharPtr fontFamily, void* fontFamilyRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    TextClockModelNG::SetFontFamily(frameNode, fontFamilyResult);
    if (SystemProperties::ConfigChangePerform()) {
        auto* fontFamily = reinterpret_cast<ResourceObject*>(fontFamilyRawPtr);
        auto pathFontFamilyResObj = AceType::Claim(fontFamily);
        TextClockModelNG::CreateWithFontFamilyResourceObj(frameNode, pathFontFamilyResObj);
    }
}

void ResetFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = DEFAULT_FONT_FAMILY_CLOCK;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    TextClockModelNG::SetFontFamily(frameNode, fontFamilyResult);
    if (SystemProperties::ConfigChangePerform()) {
        TextClockModelNG::CreateWithFontFamilyResourceObj(frameNode, nullptr);
    }
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

void ParseShadowRadiusUpdate(const RefPtr<ResourceObject>& radiusResObj, Shadow& shadow)
{
    if (!radiusResObj) {
        return;
    }
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
        double radius = 0.0;
        ResourceParseUtils::ParseResDouble(resObj, radius);
        shadow.SetBlurRadius(std::max(radius, 0.0));
    };
    shadow.AddResource("shadow.radius", radiusResObj, std::move(updateFunc));
}

void ParseShadowColorUpdate(const RefPtr<ResourceObject>& colorResObj, Shadow& shadow)
{
    if (!colorResObj) {
        return;
    }
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
        Color color;
        ResourceParseUtils::ParseResColor(resObj, color);
        shadow.SetColor(color);
    };
    shadow.AddResource("shadow.colorValue", colorResObj, std::move(updateFunc));
}

void ParseShadowOffsetXUpdate(const RefPtr<ResourceObject>& offsetXResObj, Shadow& shadow)
{
    if (!offsetXResObj) {
        return;
    }
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
        CalcDimension xValue;
        ResourceParseUtils::ParseResResource(resObj, xValue);
        shadow.SetOffsetX(xValue.Value());
    };
    shadow.AddResource("shadow.offsetX", offsetXResObj, std::move(updateFunc));
}

void ParseShadowOffsetYUpdate(const RefPtr<ResourceObject>& offsetYResObj, Shadow& shadow)
{
    if (!offsetYResObj) {
        return;
    }
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
        CalcDimension yValue;
        ResourceParseUtils::ParseResResource(resObj, yValue);
        shadow.SetOffsetY(yValue.Value());
    };
    shadow.AddResource("shadow.offsetY", offsetYResObj, std::move(updateFunc));
}

void SetTextShadowRes(
    ArkUINodeHandle node, ArkUITextShadowStruct* shadows, ArkUITextShadowResStruct* shadowsRes, ArkUI_Uint32 length)
{
    CHECK_NULL_VOID(shadows);
    CHECK_NULL_VOID(shadowsRes);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Shadow> shadowList(length);
    for (uint32_t i = 0; i < length; i++) {
        Shadow shadow;
        ArkUITextShadowStruct* shadowStruct = &shadows[i];
        ArkUITextShadowResStruct* shadowResStruct = &shadowsRes[i];
        shadow.SetBlurRadius(shadowStruct->radius);
        shadow.SetShadowType(static_cast<ShadowType>(shadowStruct->type));
        shadow.SetColor(Color(shadowStruct->color));
        shadow.SetOffsetX(shadowStruct->offsetX);
        shadow.SetOffsetY(shadowStruct->offsetY);
        shadow.SetIsFilled(static_cast<bool>(shadowStruct->fill));
        if (SystemProperties::ConfigChangePerform()) {
            auto* radius = shadowResStruct->radiusResObj ?
                reinterpret_cast<ResourceObject*>(shadowResStruct->radiusResObj) : nullptr;
            if (radius) {
                ParseShadowRadiusUpdate(AceType::Claim(radius), shadow);
            }
            auto* color = shadowResStruct->colorResObj ?
                reinterpret_cast<ResourceObject*>(shadowResStruct->colorResObj) : nullptr;
                if (color) {
                ParseShadowColorUpdate(AceType::Claim(color), shadow);
            }
            auto* offsetX = shadowResStruct->offsetXResObj ?
                reinterpret_cast<ResourceObject*>(shadowResStruct->offsetXResObj) : nullptr;
            if (offsetX) {
                ParseShadowOffsetXUpdate(AceType::Claim(offsetX), shadow);
            }
            auto* offsetY = shadowResStruct->offsetYResObj ?
                reinterpret_cast<ResourceObject*>(shadowResStruct->offsetYResObj) : nullptr;
            if (offsetY) {
                ParseShadowOffsetYUpdate(AceType::Claim(offsetY), shadow);
            }
        }
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

void SetTextClockOnDateChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDateChange = reinterpret_cast<ChangeEvent*>(callback);
        TextClockModelNG::SetOnDateChange(frameNode, std::move(*onDateChange));
    } else {
        TextClockModelNG::SetOnDateChange(frameNode, nullptr);
    }
}

void ResetTextClockOnDateChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetOnDateChange(frameNode, nullptr);
}
} // namespace TextClockModifier

namespace NodeModifier {
const ArkUITextClockModifier* GetTextClockModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITextClockModifier modifier = {
        .setFormat = TextClockModifier::SetFormat,
        .setFormatRes = TextClockModifier::SetFormatRes,
        .resetFormat = TextClockModifier::ResetFormat,
        .setFontColor = TextClockModifier::SetFontColor,
        .setFontColorRes = TextClockModifier::SetFontColorRes,
        .resetFontColor = TextClockModifier::ResetFontColor,
        .setFontSize = TextClockModifier::SetFontSize,
        .setFontSizeRes = TextClockModifier::SetFontSizeRes,
        .resetFontSize = TextClockModifier::ResetFontSize,
        .setFontStyle = TextClockModifier::SetFontStyle,
        .resetFontStyle = TextClockModifier::ResetFontStyle,
        .setFontWeight = TextClockModifier::SetFontWeight,
        .setFontWeightRes = TextClockModifier::SetFontWeightRes,
        .resetFontWeight = TextClockModifier::ResetFontWeight,
        .setFontFamily = TextClockModifier::SetFontFamily,
        .setFontFamilyRes = TextClockModifier::SetFontFamilyRes,
        .resetFontFamily = TextClockModifier::ResetFontFamily,
        .setTextShadow = TextClockModifier::SetTextShadow,
        .setTextShadowRes = TextClockModifier::SetTextShadowRes,
        .resetTextShadow = TextClockModifier::ResetTextShadow,
        .setFontFeature = TextClockModifier::SetFontFeature,
        .resetFontFeature = TextClockModifier::ResetFontFeature,
        .setDateTimeOptions = TextClockModifier::SetDateTimeOptions,
        .resetDateTimeOptions = TextClockModifier::ResetDateTimeOptions,
        .setTextClockTimeZoneOffset = TextClockModifier::SetTextClockTimeZoneOffset,
        .setTextClockOnDateChange = TextClockModifier::SetTextClockOnDateChange,
        .resetTextClockOnDateChange = TextClockModifier::ResetTextClockOnDateChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUITextClockModifier* GetCJUITextClockModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITextClockModifier modifier = {
        .setFormat = TextClockModifier::SetFormat,
        .setFormatRes = TextClockModifier::SetFormatRes,
        .resetFormat = TextClockModifier::ResetFormat,
        .setFontColor = TextClockModifier::SetFontColor,
        .setFontColorRes = TextClockModifier::SetFontColorRes,
        .resetFontColor = TextClockModifier::ResetFontColor,
        .setFontSize = TextClockModifier::SetFontSize,
        .setFontSizeRes = TextClockModifier::SetFontSizeRes,
        .resetFontSize = TextClockModifier::ResetFontSize,
        .setFontStyle = TextClockModifier::SetFontStyle,
        .resetFontStyle = TextClockModifier::ResetFontStyle,
        .setFontWeight = TextClockModifier::SetFontWeight,
        .setFontWeightRes = TextClockModifier::SetFontWeightRes,
        .resetFontWeight = TextClockModifier::ResetFontWeight,
        .setFontFamily = TextClockModifier::SetFontFamily,
        .setFontFamilyRes = TextClockModifier::SetFontFamilyRes,
        .resetFontFamily = TextClockModifier::ResetFontFamily,
        .setTextShadow = TextClockModifier::SetTextShadow,
        .setTextShadowRes = TextClockModifier::SetTextShadowRes,
        .resetTextShadow = TextClockModifier::ResetTextShadow,
        .setFontFeature = TextClockModifier::SetFontFeature,
        .resetFontFeature = TextClockModifier::ResetFontFeature,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
