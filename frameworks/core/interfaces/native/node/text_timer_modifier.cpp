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
#include "core/interfaces/native/node/text_timer_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"

namespace OHOS::Ace::NG {
constexpr Dimension DEFAULT_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
const std::vector<std::string> DEFAULT_FONT_FAMILY = { "HarmonyOS Sans" };
const std::string DEFAULT_FORMAT = "HH:mm:ss.SS";
constexpr Ace::FontWeight DEFAULT_FONT_WEIGHT = Ace::FontWeight::NORMAL;

namespace TextTimerModifier {
void SetFontColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontColor(frameNode, Color(color));
}

void ResetFontColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    TextTimerModelNG::SetFontColor(frameNode, theme->GetTextStyle().GetTextColor());
}

void SetFontSize(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontSize(frameNode, Dimension(value, static_cast<DimensionUnit>(unit)));
}

void ResetFontSize(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontSize(frameNode, DEFAULT_FONT_SIZE);
}

void SetFontStyle(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontStyle(frameNode, static_cast<Ace::FontStyle>(value));
}

void ResetFontStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontStyle(frameNode, OHOS::Ace::FontStyle::NORMAL);
}

void SetFontWeight(ArkUINodeHandle node, ArkUI_CharPtr fontWeight)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontWeightStr = fontWeight;
    TextTimerModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeightStr));
}

void ResetFontWeight(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
}

void SetFontFamily(ArkUINodeHandle node, ArkUI_CharPtr fontFamily)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    TextTimerModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void ResetFontFamily(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontFamily(frameNode, DEFAULT_FONT_FAMILY);
}

void SetFormat(ArkUINodeHandle node, ArkUI_CharPtr format)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string formatStr = format;
    std::smatch result;
    std::regex pattern("(([YyMdD]+))");
    if (std::regex_search(formatStr, result, pattern)) {
        if (!result.empty()) {
            formatStr = DEFAULT_FORMAT;
        }
    }

    std::string target = "HmsS:.";
    for (auto ch : formatStr) {
        if (target.find(ch) == std::string::npos) {
            formatStr = DEFAULT_FORMAT;
        }
    }

    auto pos = formatStr.find("hh");
    if (pos != std::string::npos) {
        formatStr.replace(pos, sizeof("hh") - 1, "HH");
    }
    TextTimerModelNG::SetFormat(frameNode, formatStr);
}

void ResetFormat(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFormat(frameNode, DEFAULT_FORMAT);
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
    TextTimerModelNG::SetTextShadow(frameNode, shadowList);
}

void ResetTextShadow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Shadow shadow;
    shadow.SetOffsetX(0.0);
    shadow.SetOffsetY(0.0);
    TextTimerModelNG::SetTextShadow(frameNode, std::vector<Shadow> { shadow });
}

void setTextTimerOptions(ArkUINodeHandle node, ArkUI_Bool isCountDown, ArkUI_Float64 count)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetIsCountDown(frameNode, isCountDown);
    if (isCountDown) {
        TextTimerModelNG::SetInputCount(frameNode, count);
    }
}
} // namespace TextTimerModifier

namespace NodeModifier {
const ArkUITextTimerModifier* GetTextTimerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITextTimerModifier modifier = {
        .setFontColor = TextTimerModifier::SetFontColor,
        .resetFontColor = TextTimerModifier::ResetFontColor,
        .setFontSize = TextTimerModifier::SetFontSize,
        .resetFontSize = TextTimerModifier::ResetFontSize,
        .setFontStyle = TextTimerModifier::SetFontStyle,
        .resetFontStyle = TextTimerModifier::ResetFontStyle,
        .setFontWeight = TextTimerModifier::SetFontWeight,
        .resetFontWeight = TextTimerModifier::ResetFontWeight,
        .setFontFamily = TextTimerModifier::SetFontFamily,
        .resetFontFamily = TextTimerModifier::ResetFontFamily,
        .setFormat = TextTimerModifier::SetFormat,
        .resetFormat = TextTimerModifier::ResetFormat,
        .setTextShadow = TextTimerModifier::SetTextShadow,
        .resetTextShadow = TextTimerModifier::ResetTextShadow,
        .setTextTimerOptions = TextTimerModifier::setTextTimerOptions,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUITextTimerModifier* GetCJUITextTimerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITextTimerModifier modifier = {
        .setFontColor = TextTimerModifier::SetFontColor,
        .resetFontColor = TextTimerModifier::ResetFontColor,
        .setFontSize = TextTimerModifier::SetFontSize,
        .resetFontSize = TextTimerModifier::ResetFontSize,
        .setFontStyle = TextTimerModifier::SetFontStyle,
        .resetFontStyle = TextTimerModifier::ResetFontStyle,
        .setFontWeight = TextTimerModifier::SetFontWeight,
        .resetFontWeight = TextTimerModifier::ResetFontWeight,
        .setFontFamily = TextTimerModifier::SetFontFamily,
        .resetFontFamily = TextTimerModifier::ResetFontFamily,
        .setFormat = TextTimerModifier::SetFormat,
        .resetFormat = TextTimerModifier::ResetFormat,
        .setTextShadow = TextTimerModifier::SetTextShadow,
        .resetTextShadow = TextTimerModifier::ResetTextShadow,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
