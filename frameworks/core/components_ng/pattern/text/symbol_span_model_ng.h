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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SYMBOL_SPAN_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SYMBOL_SPAN_MODEL_NG_H

#include <functional>
#include <string>

#include "core/components_ng/pattern/text/symbol_span_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SymbolSpanModelNG : public SymbolSpanModel {
public:
    void Create(const uint32_t& unicode) override;

    void SetFontSize(const Dimension& value) override;
    void SetFontWeight(FontWeight value) override;
    void SetFontColor(std::vector<Color>& symbolColor) override;
    void SetSymbolRenderingStrategy(const uint32_t renderingStrategy) override;
    void SetSymbolEffect(const uint32_t effectStrategy) override;
    void SetFontFamilies(std::vector<std::string>& familyNames) override;
    void SetSymbolType(SymbolType value) override;

    static void SetFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetFontWeight(FrameNode* frameNode, FontWeight value);
    static void SetFontColor(FrameNode* frameNode, std::vector<Color>& symbolColor);
    static void SetSymbolRenderingStrategy(FrameNode* frameNode, const uint32_t renderingStrategy);
    static void SetSymbolEffect(FrameNode* frameNode, const uint32_t effectStrategy);
    static void InitialSymbol(FrameNode* frameNode, const std::uint32_t& symbolId);
    static void InitialCustomSymbol(FrameNode* frameNode, const std::uint32_t& unicode, const char* fontFamilyName);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SYMBOL_SPAN_MODEL_NG_H
