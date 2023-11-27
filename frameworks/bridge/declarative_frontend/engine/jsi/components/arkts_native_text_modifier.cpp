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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_text_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components/common/properties/text_style.h"
#include "frameworks/core/components_ng/pattern/text/text_model_ng.h"
namespace OHOS::Ace::NG {
namespace {
constexpr Dimension DEFAULT_LINE_HEIGHT = Dimension(0.0, DimensionUnit::PX);
constexpr TextDecoration DEFAULT_TEXT_DECORATION = TextDecoration::NONE;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
const std::vector<OHOS::Ace::TextAlign> TEXT_ALIGNS = { OHOS::Ace::TextAlign::START, OHOS::Ace::TextAlign::CENTER,
    OHOS::Ace::TextAlign::END, OHOS::Ace::TextAlign::JUSTIFY, OHOS::Ace::TextAlign::LEFT, OHOS::Ace::TextAlign::RIGHT };

FontWeight ConvertStrToFontWeight(const char* weight, FontWeight defaultFontWeight = FontWeight::NORMAL)
{
    std::string weightStr(weight);
    return StringUtils::StringToFontWeight(weightStr, defaultFontWeight);
}
} // namespace
void SetFontWeight(NodeHandle node, const char* weight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetFontWeight(frameNode, ConvertStrToFontWeight(weight));
}

void ResetFontWeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetFontWeight(frameNode, Ace::FontWeight::NORMAL);
}

void SetFontStyle(NodeHandle node, uint32_t fontStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (fontStyle < 0 || fontStyle >= FONT_STYLES.size()) {
        return;
    }
    TextModelNG::SetItalicFontStyle(frameNode, FONT_STYLES[fontStyle]);
}

void ResetFontStyle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
}

void SetTextAlign(NodeHandle node, uint32_t testAlign)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (testAlign < 0 || testAlign >= TEXT_ALIGNS.size()) {
        return;
    }
    TextModelNG::SetTextAlign(frameNode, TEXT_ALIGNS[testAlign]);
}

void ResetTextAlign(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
}
void SetFontColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextColor(frameNode, Color(color));
}
void ResetFontColor(NodeHandle node)
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
void SetFontSize(NodeHandle node,  double fontSize, int unit)
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
void ResetFontSize(NodeHandle node)
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

void SetTextLineHeight(NodeHandle node, const double number, const int8_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLineHeight(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetTextLineHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLineHeight(frameNode, DEFAULT_LINE_HEIGHT);
}

void SetTextTextOverflow(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextOverflow value_textOverflow = static_cast<TextOverflow>(value);
    TextModelNG::SetTextOverflow(frameNode, value_textOverflow);
}

void ResetTextTextOverflow(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextOverflow(frameNode, TextOverflow::NONE);
}

void SetTextDecoration(NodeHandle node, const int32_t decoration, const uint32_t color, const int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDecoration(frameNode, static_cast<TextDecoration>(decoration));
    TextModelNG::SetTextDecorationColor(frameNode, Color(color));
    TextModelNG::SetTextDecorationStyle(frameNode, static_cast<TextDecorationStyle>(style));
}

void ResetTextDecoration(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextDecoration(frameNode, DEFAULT_TEXT_DECORATION);
    TextModelNG::SetTextDecorationColor(frameNode, DEFAULT_DECORATION_COLOR);
    TextModelNG::SetTextDecorationStyle(frameNode, DEFAULT_DECORATION_STYLE);
}

ArkUITextModifierAPI GetTextModifier()
{
    static const ArkUITextModifierAPI modifier = { SetFontWeight, ResetFontWeight, SetFontStyle, ResetFontStyle,
        SetTextAlign, ResetTextAlign, SetFontColor, ResetFontColor, SetFontSize, ResetFontSize, SetTextLineHeight,
        ResetTextLineHeight, SetTextTextOverflow, ResetTextTextOverflow, SetTextDecoration, ResetTextDecoration };

    return modifier;
}
} // namespace OHOS::Ace::NG