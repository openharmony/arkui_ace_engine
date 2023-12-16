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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_marquee_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr bool DEFAULT_ALLOW_SCALE = true;
constexpr Ace::FontWeight DEFAULT_FONT_WEIGHT = Ace::FontWeight::NORMAL;
const std::string DEFAULT_FONT_FAMILY = "cursive";
void SetMarqueeFontSize(NodeHandle node, double fontSize, int unit)
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
        MarqueeModelNG::SetFontSize(frameNode, fontSize);
    } else {
        MarqueeModelNG::SetFontSize(frameNode, Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit)));
    }
}

void ResetMarqueeFontSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
    MarqueeModelNG::SetFontSize(frameNode, fontSize);
}

void SetMarqueeFontColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetTextColor(frameNode, Color(color));
}
void ResetMarqueeFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt;
    MarqueeModelNG::SetTextColor(frameNode, colorOpt);
}
void SetMarqueeAllowScale(NodeHandle node, bool allowScale)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetAllowScale(frameNode, allowScale);
}

void ResetMarqueeAllowScale(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetAllowScale(frameNode, DEFAULT_ALLOW_SCALE);
}

void SetMarqueeFontWeight(NodeHandle node, const char* fontWeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeight));
}

void ResetMarqueeFontWeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
}

void SetMarqueeFontFamily(NodeHandle node, const char* fontFamily)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    MarqueeModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void ResetMarqueeFontFamily(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = DEFAULT_FONT_FAMILY;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    MarqueeModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

ArkUIMarqueeModifierAPI GetMarqueeModifier()
{
    static const ArkUIMarqueeModifierAPI modifier = { SetMarqueeFontSize, ResetMarqueeFontSize, SetMarqueeFontColor,
        ResetMarqueeFontColor, SetMarqueeAllowScale, ResetMarqueeAllowScale, SetMarqueeFontWeight,
        ResetMarqueeFontWeight, SetMarqueeFontFamily, ResetMarqueeFontFamily };
    return modifier;
}
} // namespace OHOS::Ace::NG
