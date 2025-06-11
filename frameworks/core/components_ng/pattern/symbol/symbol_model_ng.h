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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYMBOL_SYMBOL_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYMBOL_SYMBOL_MODEL_NG_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/symbol/symbol_effect_options.h"
#include "core/components_ng/pattern/symbol/symbol_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SymbolModelNG : public SymbolModel {
public:
    void Create(const std::uint32_t& unicode) override;
    void SetFontWeight(const Ace::FontWeight& value) override;
    void SetFontSize(const CalcDimension& value) override;
    void SetSymbolRenderingStrategy(const std::uint32_t renderingStrategy) override;
    void SetFontColor(std::vector<Color>& symbolColor) override;
    void SetSymbolEffect(const std::uint32_t effectStrategy) override;
    void SetClipEdge() override;
    void SetSymbolEffectOptions(NG::SymbolEffectOptions& symbolEffectOptions) override;
    void SetMinFontScale(const float value) override;
    void SetMaxFontScale(const float value) override;

    void RegisterSymbolFontColorResource(const std::string& key, std::vector<Color>& symbolColor,
        const std::vector<std::pair<int32_t, RefPtr<ResourceObject>>>& resObjArr) override;

    void SetFontFamilies(std::vector<std::string>& familyNames) override;
    void SetSymbolType(SymbolType value) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetFontColor(FrameNode* frameNode, const std::vector<Color>& symbolColor);
    static void SetFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetFontWeight(FrameNode* frameNode, Ace::FontWeight value);
    static void SetRenderingStrategy(FrameNode* frameNode, const std::uint32_t renderingStrategy);
    static void SetSymbolEffect(FrameNode* frameNode, const std::uint32_t effectStrategy);
    static void InitialSymbol(FrameNode* frameNode, const std::uint32_t& unicode);
    static void InitialCustomSymbol(FrameNode* frameNode, const std::uint32_t& unicode, const char* fontFamilyName);
    static void SetSymbolEffectOptions(FrameNode* frameNode, NG::SymbolEffectOptions& symbolEffectOptions);
    static void SetSymbolGlyphInitialize(FrameNode* framwNode, const std::uint32_t& symbolId);
    static void SetCustomSymbolGlyphInitialize(FrameNode* frameNode, const std::uint32_t& symbolId,
        const char* fontFamilyName);
    static void SetMinFontScale(FrameNode* frameNode, const float value);
    static void SetMaxFontScale(FrameNode* frameNode, const float value);
    static void UpdateSymbolEffect(FrameNode* frameNode, const std::uint32_t symbolEffectType, const bool isActive,
        const std::int16_t isTxtActiveSource);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYMBOL_SYMBOL_MODEL_NG_H
