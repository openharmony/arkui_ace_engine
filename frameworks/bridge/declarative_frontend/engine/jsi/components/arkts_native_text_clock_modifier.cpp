/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_text_clock_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
constexpr Ace::FontWeight DEFAULT_FONT_WEIGHT = Ace::FontWeight::NORMAL;
constexpr Dimension DEFAULT_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
const std::string DEFAULT_FONT_FAMILY = "HarmonyOS Sans";
const char* DEFAULT_TEXT_CLOCK_FORMAT_IN_CARD = "hh:mm";
const char* DEFAULT_TEXT_CLOCK_FORMAT_IN_NOCARD = "aa hh:mm:ss";

void SetTextClockFormat(NodeHandle node, const char* format)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFormat(frameNode, format);
}

void ResetTextClockFormat(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string defaultFormat;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
        PipelineBase::GetCurrentContext()->IsJsCard()) {
        defaultFormat = DEFAULT_TEXT_CLOCK_FORMAT_IN_CARD;
    } else {
        defaultFormat = DEFAULT_TEXT_CLOCK_FORMAT_IN_NOCARD;
    }
    TextClockModelNG::SetFormat(frameNode, defaultFormat);
}

void SetTextClockFontColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontColor(frameNode, Color(color));
}

void ResetTextClockFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    TextClockModelNG::SetFontColor(frameNode, theme->GetTextStyle().GetTextColor());
}

void SetTextClockFontSize(NodeHandle node, double fontSizeValue, int fontSizeUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontSize(frameNode, CalcDimension(fontSizeValue, (DimensionUnit)fontSizeUnit));
}

void ResetTextClockFontSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontSize(frameNode, DEFAULT_FONT_SIZE);
}

void SetTextClockFontStyle(NodeHandle node, uint32_t fontStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontStyle(frameNode, FONT_STYLES[fontStyle]);
}

void ResetTextClockFontStyle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
}

void SetTextClockFontWeight(NodeHandle node, const char* fontWeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontWeightStr = fontWeight;
    TextClockModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeightStr));
}

void ResetTextClockFontWeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextClockModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
}

void SetTextClockFontFamily(NodeHandle node, const char* fontFamily)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    TextClockModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void ResetTextClockFontFamily(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = DEFAULT_FONT_FAMILY;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    TextClockModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

ArkUITextClockModifierAPI GetTextClockModifier()
{
    static const ArkUITextClockModifierAPI modifier = { SetTextClockFormat, ResetTextClockFormat, SetTextClockFontColor,
        ResetTextClockFontColor, SetTextClockFontSize, ResetTextClockFontSize, SetTextClockFontStyle,
        ResetTextClockFontStyle, SetTextClockFontWeight, ResetTextClockFontWeight, SetTextClockFontFamily,
        ResetTextClockFontFamily };

    return modifier;
}
} // namespace OHOS::Ace::NG