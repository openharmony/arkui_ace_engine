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

#include "frameworks/core/components_ng/pattern/symbol/symbol_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
FontWeight ConvertStrToFontWeight(ArkUI_CharPtr weight, FontWeight defaultFontWeight = FontWeight::NORMAL)
{
    std::string weightStr(weight);
    return StringUtils::StringToFontWeight(weightStr, defaultFontWeight);
}

FontWeight ConvertIntToFontWeight(ArkUI_Int32 weight)
{
    static const std::unordered_map<ArkUI_Int32, FontWeight> fontWeightMap = {
        {100, FontWeight::W100},
        {200, FontWeight::W200},
        {300, FontWeight::W300},
        {400, FontWeight::W400},
        {500, FontWeight::W500},
        {600, FontWeight::W600},
        {700, FontWeight::W700},
        {800, FontWeight::W800},
        {900, FontWeight::W900},
    };
    auto weightFindIter = fontWeightMap.find(weight);
    if (weightFindIter != fontWeightMap.end()) {
        return weightFindIter->second;
    }
    return FontWeight::NORMAL;
}

void SetFontColor(ArkUINodeHandle node, ArkUI_Uint32* color, int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Color> colorArray;
    for (int32_t i = 0; i < size; i++) {
        colorArray.emplace_back(Color(color[i]));
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
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("symbolColor");
    }
}

void SetFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSize, ArkUI_Int32 unit, void* fontSizeRawPtr)
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
        auto fontSizeVal = Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit));
        SymbolModelNG::SetFontSize(frameNode, fontSizeVal);
        NodeModifier::ProcessResourceObj<CalcDimension>(frameNode, "FontSize", fontSizeVal, fontSizeRawPtr);
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
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("FontSize");
    }
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
    SymbolModelNG::SetFontWeight(frameNode, ConvertIntToFontWeight(weight));
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

void SetSymbolGlyphInitialize(ArkUINodeHandle node, ArkUI_Uint32 symbolId)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetSymbolGlyphInitialize(frameNode, symbolId);
}

void SetCustomSymbolGlyphInitialize(ArkUINodeHandle node, ArkUI_Uint32 symbolId, ArkUI_CharPtr fontFamily)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontFamilyStr(fontFamily);
    SymbolModelNG::SetCustomSymbolGlyphInitialize(frameNode, symbolId, fontFamilyStr.c_str());
}

void ResetSymbolGlyphInitialize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetSymbolGlyphInitialize(frameNode, 0);
}

void UpdateSymbolEffect(ArkUINodeHandle node, ArkUI_Uint32 symbolEffectType, ArkUI_Bool isActive,
    ArkUI_Int16 isTxtActiveSource)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::UpdateSymbolEffect(frameNode, symbolEffectType, isActive, isTxtActiveSource);
}

void SetMinFontScale(ArkUINodeHandle node, ArkUI_Float32 minFontScale, void* scaleRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (LessOrEqual(minFontScale, 0.0f)) {
        SymbolModelNG::SetMinFontScale(frameNode, 0.0f);
        return;
    }
    if (GreatOrEqual(minFontScale, 1.0f)) {
        SymbolModelNG::SetMinFontScale(frameNode, 1.0f);
        return;
    }
    SymbolModelNG::SetMinFontScale(frameNode, minFontScale);
    NodeModifier::ProcessResourceObj<float>(frameNode, "MinFontScale", minFontScale, scaleRawPtr);
}

void ResetMinFontScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetMinFontScale(frameNode, 1.0f);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("MinFontScale");
    }
}

void SetMaxFontScale(ArkUINodeHandle node, ArkUI_Float32 maxFontScale, void* scaleRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (LessOrEqual(maxFontScale, 1.0f)) {
        SymbolModelNG::SetMaxFontScale(frameNode, 1.0f);
        return;
    }
    SymbolModelNG::SetMaxFontScale(frameNode, maxFontScale);
    NodeModifier::ProcessResourceObj<float>(frameNode, "MaxFontScale", maxFontScale, scaleRawPtr);
}

void ResetMaxFontScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetMaxFontScale(frameNode, 1.0f);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("MaxFontScale");
    }
}
}

namespace NodeModifier {
const ArkUISymbolGlyphModifier* GetSymbolGlyphModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISymbolGlyphModifier modifier = {
        .setFontColor = SetFontColor,
        .resetFontColor = ResetFontColor,
        .setFontSize = SetFontSize,
        .resetFontSize = ResetFontSize,
        .setFontWeightStr = SetFontWeightStr,
        .setFontWeight = SetFontWeight,
        .resetFontWeight = ResetFontWeight,
        .setRenderingStrategy = SetRenderingStrategy,
        .resetRenderingStrategy = ResetRenderingStrategy,
        .setEffectStrategy = SetEffectStrategy,
        .resetEffectStrategy = ResetEffectStrategy,
        .setSymbolGlyphInitialize = SetSymbolGlyphInitialize,
        .setCustomSymbolGlyphInitialize = SetCustomSymbolGlyphInitialize,
        .resetSymbolGlyphInitialize = ResetSymbolGlyphInitialize,
        .updateSymbolEffect = UpdateSymbolEffect,
        .setMinFontScale = SetMinFontScale,
        .resetMinFontScale = ResetMinFontScale,
        .setMaxFontScale = SetMaxFontScale,
        .resetMaxFontScale = ResetMaxFontScale,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUISymbolGlyphModifier* GetCJUISymbolGlyphModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUISymbolGlyphModifier modifier = {
        .setFontColor = SetFontColor,
        .resetFontColor = ResetFontColor,
        .setFontSize = SetFontSize,
        .resetFontSize = ResetFontSize,
        .setFontWeightStr = SetFontWeightStr,
        .setFontWeight = SetFontWeight,
        .resetFontWeight = ResetFontWeight,
        .setRenderingStrategy = SetRenderingStrategy,
        .resetRenderingStrategy = ResetRenderingStrategy,
        .setEffectStrategy = SetEffectStrategy,
        .resetEffectStrategy = ResetEffectStrategy,
        .setSymbolGlyphInitialize = SetSymbolGlyphInitialize,
        .resetSymbolGlyphInitialize = ResetSymbolGlyphInitialize,
        .setMinFontScale = SetMinFontScale,
        .resetMinFontScale = ResetMinFontScale,
        .setMaxFontScale = SetMaxFontScale,
        .resetMaxFontScale = ResetMaxFontScale,
        .setCustomSymbolGlyphInitialize = SetCustomSymbolGlyphInitialize,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

template<typename T>
void ProcessResourceObj(FrameNode* frameNode, std::string key, T value, void* objRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (objRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(objRawPtr));
        pattern->RegisterResource<T>(key, resObj, value);
    } else {
        pattern->UnRegisterResource(key);
    }
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
