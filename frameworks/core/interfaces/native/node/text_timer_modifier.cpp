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
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"
#include "core/pipeline/base/element_register.h"

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
} // namespace TextTimerModifier

namespace NodeModifier {
const ArkUITextTimerModifier* GetTextTimerModifier()
{
    static const ArkUITextTimerModifier modifier = {
        TextTimerModifier::SetFontColor,
        TextTimerModifier::ResetFontColor,
        TextTimerModifier::SetFontSize,
        TextTimerModifier::ResetFontSize,
        TextTimerModifier::SetFontStyle,
        TextTimerModifier::ResetFontStyle,
        TextTimerModifier::SetFontWeight,
        TextTimerModifier::ResetFontWeight,
        TextTimerModifier::SetFontFamily,
        TextTimerModifier::ResetFontFamily,
        TextTimerModifier::SetFormat,
        TextTimerModifier::ResetFormat
    };

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG