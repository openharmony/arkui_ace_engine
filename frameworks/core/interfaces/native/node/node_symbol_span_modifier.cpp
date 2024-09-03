/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "frameworks/core/interfaces/native/node/node_symbol_span_modifier.h"

#include "frameworks/core/components_ng/pattern/text/symbol_span_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
FontWeight ConvertStrToFontWeight(ArkUI_CharPtr weight, FontWeight defaultFontWeight = FontWeight::NORMAL)
{
    std::string weightStr(weight);
    return StringUtils::StringToFontWeight(weightStr, defaultFontWeight);
}

void SetSymbolSpanFontColor(ArkUINodeHandle node, ArkUI_Uint32* color, int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Color> colorArray;
    for (int32_t i = 0; i < size; i++) {
        colorArray.emplace_back(Color(color[i]));
    }
    SymbolSpanModelNG::SetFontColor(frameNode, colorArray);
}

void ResetSymbolSpanFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    Color fontColor = theme->GetTextStyle().GetTextColor();
    std::vector<Color> colorArray = { fontColor };
    SymbolSpanModelNG::SetFontColor(frameNode, colorArray);
}

void SetSymbolSpanFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSize, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);

    if (fontSize < 0 || unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC ||
        unitEnum == OHOS::Ace::DimensionUnit::PERCENT) {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
        SymbolSpanModelNG::SetFontSize(frameNode, fontSize);
    } else {
        SymbolSpanModelNG::SetFontSize(frameNode, Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit)));
    }
}

void ResetSymbolSpanFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
    SymbolSpanModelNG::SetFontSize(frameNode, fontSize);
}

void SetSymbolSpanFontWeightStr(ArkUINodeHandle node, ArkUI_CharPtr weight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolSpanModelNG::SetFontWeight(frameNode, ConvertStrToFontWeight(weight));
}

void SetSymbolSpanFontWeight(ArkUINodeHandle node, ArkUI_Int32 weight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolSpanModelNG::SetFontWeight(frameNode, static_cast<FontWeight>(weight));
}

void ResetSymbolSpanFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolSpanModelNG::SetFontWeight(frameNode, Ace::FontWeight::NORMAL);
}

void SetSymbolSpanRenderingStrategy(ArkUINodeHandle node, ArkUI_Uint32 renderingStrategy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolSpanModelNG::SetSymbolRenderingStrategy(frameNode, renderingStrategy);
}

void ResetSymbolSpanRenderingStrategy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolSpanModelNG::SetSymbolRenderingStrategy(frameNode, 0);
}

void SetSymbolSpanEffectStrategy(ArkUINodeHandle node, ArkUI_Uint32 effectStrategy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolSpanModelNG::SetSymbolEffect(frameNode, effectStrategy);
}

void ResetSymbolSpanEffectStrategy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolSpanModelNG::SetSymbolEffect(frameNode, 0);
}

void SetSymbolSpanId(ArkUINodeHandle node, ArkUI_Uint32 symbolId)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolSpanModelNG::InitialSymbol(frameNode, symbolId);
}
}

namespace NodeModifier {
const ArkUISymbolSpanModifier* GetSymbolSpanModifier()
{
    static const ArkUISymbolSpanModifier modifier = {
        SetSymbolSpanFontColor,
        ResetSymbolSpanFontColor,
        SetSymbolSpanFontSize,
        ResetSymbolSpanFontSize,
        SetSymbolSpanFontWeightStr,
        SetSymbolSpanFontWeight,
        ResetSymbolSpanFontWeight,
        SetSymbolSpanRenderingStrategy,
        ResetSymbolSpanRenderingStrategy,
        SetSymbolSpanEffectStrategy,
        ResetSymbolSpanEffectStrategy,
        SetSymbolSpanId
    };

    return &modifier;
}

const CJUISymbolSpanModifier* GetCJUISymbolSpanModifier()
{
    static const CJUISymbolSpanModifier modifier = {
        SetSymbolSpanFontColor,
        ResetSymbolSpanFontColor,
        SetSymbolSpanFontSize,
        ResetSymbolSpanFontSize,
        SetSymbolSpanFontWeightStr,
        SetSymbolSpanFontWeight,
        ResetSymbolSpanFontWeight,
        SetSymbolSpanRenderingStrategy,
        ResetSymbolSpanRenderingStrategy,
        SetSymbolSpanEffectStrategy,
        ResetSymbolSpanEffectStrategy,
        SetSymbolSpanId
    };

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG