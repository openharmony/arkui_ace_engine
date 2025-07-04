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

#include "core/components_ng/pattern/symbol/symbol_model_ng.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
void SymbolModelNG::Create(const std::uint32_t& unicode)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto nodeId = stack->ClaimNodeId();
    auto symbolNode = FrameNode::GetOrCreateFrameNode(
        V2::SYMBOL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });

    stack->Push(symbolNode);
    
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolSourceInfo, SymbolSourceInfo{unicode});
}

RefPtr<FrameNode> SymbolModelNG::CreateFrameNode(int32_t nodeId)
{
    auto symbolNode = FrameNode::GetOrCreateFrameNode(
        V2::SYMBOL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    return symbolNode;
}

void SymbolModelNG::SetFontWeight(const Ace::FontWeight& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontWeight, value);
}

void SymbolModelNG::SetFontFamilies(std::vector<std::string>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontFamily, value);
}

void SymbolModelNG::SetSymbolType(SymbolType value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolType, value);
}

void SymbolModelNG::SetFontSize(const CalcDimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, value);
}

void SymbolModelNG::SetSymbolRenderingStrategy(const std::uint32_t renderingStrategy)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolRenderingStrategy, renderingStrategy);
}

void SymbolModelNG::SetFontColor(std::vector<Color>& symbolColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolColorList, symbolColor);
}

void SymbolModelNG::SetSymbolEffect(const std::uint32_t effectStrategy)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolEffectStrategy, effectStrategy);
}

void SymbolModelNG::SetClipEdge()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SymbolModelNG::SetSymbolEffectOptions(SymbolEffectOptions& symbolEffectOptions)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto lastSymbolEffectOptions = property->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    symbolEffectOptions.UpdateFlags(lastSymbolEffectOptions);
    bool isLoopAnimation = false;
    if (symbolEffectOptions.GetEffectType() == SymbolEffectType::PULSE ||
        (symbolEffectOptions.GetEffectType() == SymbolEffectType::HIERARCHICAL &&
            symbolEffectOptions.GetFillStyle() == FillStyle::ITERATIVE)) {
        isLoopAnimation = symbolEffectOptions.GetIsTxtActive();
    }
    property->SetIsLoopAnimation(isLoopAnimation);
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolEffectOptions, symbolEffectOptions);
}

void SymbolModelNG::SetMinFontScale(const float value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, MinFontScale, value);
}

void SymbolModelNG::SetMaxFontScale(const float value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, MaxFontScale, value);
}

void SymbolModelNG::RegisterSymbolFontColorResource(const std::string& key,
    std::vector<Color>& symbolColor, const std::vector<std::pair<int32_t, RefPtr<ResourceObject>>>& resObjArr)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    for (auto i = 0; i < static_cast<int32_t>(resObjArr.size()); ++i) {
        auto resObjIndex = resObjArr[i].first;
        auto resObj = resObjArr[i].second;
        auto storeKey = key + "_" + std::to_string(resObjIndex);
        pattern->EmplaceSymbolColorIndex(resObjIndex);
        auto&& updateFunc = [weak = AceType::WeakClaim(frameNode), storeKey, resObjIndex]
            (const RefPtr<ResourceObject>& resObj) {
            auto host = weak.Upgrade();
            CHECK_NULL_VOID(host);
            auto layoutProperty = host->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            Color fontColor;
            ResourceParseUtils::ParseResColor(resObj, fontColor);
            auto colorVec = layoutProperty->GetSymbolColorList();
            if (colorVec.has_value() && GreatNotEqual(colorVec.value().size(), resObjIndex)) {
                auto colorVecArr = colorVec.value();
                colorVecArr[resObjIndex] = fontColor;
                layoutProperty->UpdateSymbolColorList(colorVecArr);
            }
        };

        pattern->AddResObj(storeKey, resObj, std::move(updateFunc));
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolColorList, symbolColor);
}

void SymbolModelNG::SetFontColor(FrameNode* frameNode, const std::vector<Color>& symbolColor)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolColorList, symbolColor, frameNode);
}

void SymbolModelNG::SetFontSize(FrameNode* frameNode, const Dimension& value)
{
    if (!value.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, Dimension(), frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, value, frameNode);
}

void SymbolModelNG::SetFontWeight(FrameNode* frameNode, Ace::FontWeight value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontWeight, value, frameNode);
}

void SymbolModelNG::SetRenderingStrategy(FrameNode* frameNode, const std::uint32_t renderingStrategy)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolRenderingStrategy, renderingStrategy, frameNode);
}

void SymbolModelNG::SetSymbolEffect(FrameNode* frameNode, const std::uint32_t effectStrategy)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolEffectStrategy, effectStrategy, frameNode);
}

void SymbolModelNG::InitialSymbol(FrameNode* frameNode, const std::uint32_t& unicode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolSourceInfo, SymbolSourceInfo{unicode}, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolType, SymbolType::SYSTEM, frameNode);
}

void SymbolModelNG::InitialCustomSymbol(FrameNode* frameNode, const std::uint32_t& unicode, const char* fontFamilyName)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolSourceInfo, SymbolSourceInfo{unicode}, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolType, SymbolType::CUSTOM, frameNode);
    std::vector<std::string> fontFamilyNames;
    fontFamilyNames.push_back(fontFamilyName);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontFamily, fontFamilyNames, frameNode);
}

void SymbolModelNG::SetSymbolEffectOptions(FrameNode* frameNode, SymbolEffectOptions& symbolEffectOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto lastSymbolEffectOptions = property->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    symbolEffectOptions.UpdateFlags(lastSymbolEffectOptions);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolEffectOptions, symbolEffectOptions, frameNode);
}

void SymbolModelNG::SetSymbolGlyphInitialize(FrameNode* frameNode, const std::uint32_t& symbolId)
{
    InitialSymbol(frameNode, symbolId);
}

void SymbolModelNG::SetCustomSymbolGlyphInitialize(FrameNode* frameNode, const std::uint32_t& symbolId,
    const char* fontFamilyName)
{
    InitialCustomSymbol(frameNode, symbolId, fontFamilyName);
}

void SymbolModelNG::SetMinFontScale(FrameNode* frameNode, const float value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, MinFontScale, value, frameNode);
}

void SymbolModelNG::SetMaxFontScale(FrameNode* frameNode, const float value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, MaxFontScale, value, frameNode);
}

void SymbolModelNG::UpdateSymbolEffect(FrameNode* frameNode, const std::uint32_t symbolEffectType, const bool isActive,
    const std::int16_t isTxtActiveSource)
{
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto symbolEffectOptions = property->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    symbolEffectOptions.SetEffectType(SymbolEffectType(symbolEffectType));
    symbolEffectOptions.SetIsTxtActive(isActive);
    symbolEffectOptions.SetIsTxtActiveSource(isTxtActiveSource);
    property->UpdateSymbolEffectOptions(symbolEffectOptions);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SymbolModelNG::SetSymbolShadow(const SymbolShadow& symbolShadow)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolShadow, symbolShadow);
}

void SymbolModelNG::SetSymbolShadow(FrameNode* frameNode, const SymbolShadow& symbolShadow)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolShadow, symbolShadow, frameNode);
}

void SymbolModelNG::SetShaderStyle(const std::vector<SymbolGradient>& shaderStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, ShaderStyle, shaderStyle);
}

void SymbolModelNG::SetShaderStyle(FrameNode* frameNode, const std::vector<SymbolGradient>& shaderStyle)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, ShaderStyle, shaderStyle, frameNode);
}
} // namespace OHOS::Ace::NG
