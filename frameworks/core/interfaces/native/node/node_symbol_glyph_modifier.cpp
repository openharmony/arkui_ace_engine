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
#include "core/interfaces/native/node/node_symbol_glyph_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "frameworks/core/components/common/properties/text_style.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
FontWeight ConvertStrToFontWeight(ArkUI_CharPtr weight, FontWeight defaultFontWeight = FontWeight::NORMAL)
{
    std::string weightStr(weight);
    return StringUtils::StringToFontWeight(weightStr, defaultFontWeight);
}

void SetFontColor(ArkUINodeHandle node, ArkUI_Uint32* color, int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Color> colorArray;
    for (int32_t i = 0; i < size; i) {
        colorArray.emplace_back(Color(colorArray[i]));
    }
    SymbolModelNG::SetFontColor(frameNode, colorArray);
}

void ResetFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    Color fontColor = theme->GetTextStyle().GetTextColor();
    std::vector<Color> colorArray = { fontColor };
    SymbolModelNG::SetFontColor(frameNode, colorArray);
}

void SetFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSize, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);

    if (fontSize < 0 || unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC ||
        unitEnum == OHOS::Ace::DimensionUnit::PERCENT) {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
        SymbolModelNG::SetFontSize(frameNode, fontSize);
    } else {
        SymbolModelNG::SetFontSize(frameNode, Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit)));
    }
}

void ResetFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
    SymbolModelNG::SetFontSize(frameNode, fontSize);
}

void SetFontWeightStr(ArkUINodeHandle node, ArkUI_CharPtr weight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetFontWeight(frameNode, ConvertStrToFontWeight(weight));
}

void SetFontWeight(ArkUINodeHandle node, ArkUI_Int32 weight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetFontWeight(frameNode, static_cast<FontWeight>(weight));
}

void ResetFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetFontWeight(frameNode, Ace::FontWeight::NORMAL);
}

void SetRenderingStrategy(ArkUINodeHandle node, ArkUI_Uint32 renderingStrategy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetRenderingStrategy(frameNode, renderingStrategy);
}

void ResetRenderingStrategy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetRenderingStrategy(frameNode, 0);
}

void SetEffectStrategy(ArkUINodeHandle node, ArkUI_Uint32 effectStrategy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetSymbolEffect(frameNode, effectStrategy);
}

void ResetEffectStrategy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetSymbolEffect(frameNode, 0);
}

void SetSymbolId(ArkUINodeHandle node, ArkUI_Uint32 symbolId)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::InitialSymbol(frameNode, symbolId);
}
}

namespace NodeModifier {
const ArkUISymbolGlyphModifier* GetSymbolGlyphModifier()
{
    static const ArkUISymbolGlyphModifier modifier = {
        SetFontColor,
        ResetFontColor,
        SetFontSize,
        ResetFontSize,
        SetFontWeightStr,
        SetFontWeight,
        ResetFontWeight,
        SetRenderingStrategy,
        ResetRenderingStrategy,
        SetEffectStrategy,
        ResetEffectStrategy,
        SetSymbolId,
    };

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG