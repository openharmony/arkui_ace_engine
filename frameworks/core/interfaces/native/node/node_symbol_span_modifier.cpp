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
#include "frameworks/core/components_ng/pattern/text/span_node.h"

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
    if (SystemProperties::ConfigChangePerform()) {
        auto spanNode = AceType::DynamicCast<NG::SpanNode>(frameNode);
        CHECK_NULL_VOID(spanNode);
        spanNode->UnregisterResource("symbolColor");
    }
}

void SetSymbolSpanFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSize, ArkUI_Int32 unit, void* fontSizeRawPtr)
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
        auto fontSizeVal = Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit));
        SymbolSpanModelNG::SetFontSize(frameNode, fontSizeVal);
        NodeModifier::ProcessResourceObj<CalcDimension>(frameNode, "fontSize", fontSizeVal, fontSizeRawPtr);
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
    if (SystemProperties::ConfigChangePerform()) {
        auto spanNode = AceType::DynamicCast<NG::SpanNode>(frameNode);
        CHECK_NULL_VOID(spanNode);
        spanNode->UnregisterResource("fontSize");
    }
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

void SetCustomSymbolSpanId(ArkUINodeHandle node, ArkUI_Uint32 symbolId, ArkUI_CharPtr fontFamily)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolSpanModelNG::InitialCustomSymbol(frameNode, symbolId, fontFamily);
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
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISymbolSpanModifier modifier = {
        .setSymbolSpanFontColor = SetSymbolSpanFontColor,
        .resetSymbolSpanFontColor = ResetSymbolSpanFontColor,
        .setSymbolSpanFontSize = SetSymbolSpanFontSize,
        .resetSymbolSpanFontSize = ResetSymbolSpanFontSize,
        .setSymbolSpanFontWeightStr = SetSymbolSpanFontWeightStr,
        .setSymbolSpanFontWeight = SetSymbolSpanFontWeight,
        .resetSymbolSpanFontWeight = ResetSymbolSpanFontWeight,
        .setSymbolSpanRenderingStrategy = SetSymbolSpanRenderingStrategy,
        .resetSymbolSpanRenderingStrategy = ResetSymbolSpanRenderingStrategy,
        .setSymbolSpanEffectStrategy = SetSymbolSpanEffectStrategy,
        .resetSymbolSpanEffectStrategy = ResetSymbolSpanEffectStrategy,
        .setSymbolSpanId = SetSymbolSpanId,
        .setCustomSymbolSpanId = SetCustomSymbolSpanId,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUISymbolSpanModifier* GetCJUISymbolSpanModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUISymbolSpanModifier modifier = {
        .setSymbolSpanFontColor = SetSymbolSpanFontColor,
        .resetSymbolSpanFontColor = ResetSymbolSpanFontColor,
        .setSymbolSpanFontSize = SetSymbolSpanFontSize,
        .resetSymbolSpanFontSize = ResetSymbolSpanFontSize,
        .setSymbolSpanFontWeightStr = SetSymbolSpanFontWeightStr,
        .setSymbolSpanFontWeight = SetSymbolSpanFontWeight,
        .resetSymbolSpanFontWeight = ResetSymbolSpanFontWeight,
        .setSymbolSpanRenderingStrategy = SetSymbolSpanRenderingStrategy,
        .resetSymbolSpanRenderingStrategy = ResetSymbolSpanRenderingStrategy,
        .setSymbolSpanEffectStrategy = SetSymbolSpanEffectStrategy,
        .resetSymbolSpanEffectStrategy = ResetSymbolSpanEffectStrategy,
        .setSymbolSpanId = SetSymbolSpanId,
        .setCustomSymbolSpanId = SetCustomSymbolSpanId,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

template<typename T>
void ProcessResourceObj(UINode* uinode, std::string key, T value, void* objRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    CHECK_NULL_VOID(uinode);
    auto spanNode = AceType::DynamicCast<NG::SpanNode>(uinode);
    CHECK_NULL_VOID(spanNode);
    if (objRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(objRawPtr));
        spanNode->RegisterResource<T>(key, resObj, value);
    } else {
        spanNode->UnregisterResource(key);
    }
}

template void ProcessResourceObj<CalcDimension>(UINode* uinode, std::string key, CalcDimension value, void* objRawPtr);
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
