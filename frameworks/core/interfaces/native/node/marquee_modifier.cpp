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
#include "core/interfaces/native/node/marquee_modifier.h"

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

void SetMarqueeFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSize, int unit)
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

void ResetMarqueeFontSize(ArkUINodeHandle node)
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

void SetMarqueeFontColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetTextColor(frameNode, Color(color));
}
void ResetMarqueeFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt;
    MarqueeModelNG::SetTextColor(frameNode, colorOpt);
}
void SetMarqueeAllowScale(ArkUINodeHandle node, ArkUI_Bool allowScale)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetAllowScale(frameNode, allowScale);
}

void ResetMarqueeAllowScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetAllowScale(frameNode, DEFAULT_ALLOW_SCALE);
}

void SetMarqueeFontWeight(ArkUINodeHandle node, const char* fontWeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeight));
}

void ResetMarqueeFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
}

void SetMarqueeFontFamily(ArkUINodeHandle node, const char* fontFamily)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    MarqueeModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void ResetMarqueeFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = DEFAULT_FONT_FAMILY;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    MarqueeModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void SetMarqueeUpdateStrategy(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetMarqueeUpdateStrategy(frameNode, static_cast<OHOS::Ace::MarqueeUpdateStrategy>(value));
}

void ResetMarqueeUpdateStrategy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetMarqueeUpdateStrategy(frameNode, OHOS::Ace::MarqueeUpdateStrategy::DEFAULT);
}

namespace NodeModifier {
const ArkUIMarqueeModifier* GetMarqueeModifier()
{
    static const ArkUIMarqueeModifier modifier = { SetMarqueeFontSize, ResetMarqueeFontSize, SetMarqueeFontColor,
        ResetMarqueeFontColor, SetMarqueeAllowScale, ResetMarqueeAllowScale, SetMarqueeFontWeight,
        ResetMarqueeFontWeight, SetMarqueeFontFamily, ResetMarqueeFontFamily, SetMarqueeUpdateStrategy,
        ResetMarqueeUpdateStrategy };
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
