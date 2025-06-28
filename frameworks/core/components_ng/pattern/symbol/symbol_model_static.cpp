/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "base/utils/utils.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"
#include "core/components_ng/pattern/symbol/symbol_model_static.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

void SymbolModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize)
{
    if (fontSize.has_value()) {
        SymbolModelNG::SetFontSize(frameNode, fontSize.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            TextLayoutProperty, FontSize, PROPERTY_UPDATE_MEASURE, frameNode);
        frameNode->GetLayoutProperty<TextLayoutProperty>()->OnPropertyChangeMeasure();
    }
}

void SymbolModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& fontWeight)
{
    CHECK_NULL_VOID(frameNode);
    if (fontWeight.has_value()) {
        SymbolModelNG::SetFontWeight(frameNode, fontWeight.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(TextLayoutProperty, FontWeight, PROPERTY_UPDATE_MEASURE, frameNode);
        frameNode->GetLayoutProperty<TextLayoutProperty>()->OnPropertyChangeMeasure();
    }
}

void SymbolModelStatic::SetRenderingStrategy(FrameNode* frameNode, const std::optional<uint32_t>& renderingStrategy)
{
    CHECK_NULL_VOID(frameNode);
    if (renderingStrategy.has_value()) {
        SymbolModelNG::SetRenderingStrategy(frameNode, renderingStrategy.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            TextLayoutProperty, SymbolRenderingStrategy, PROPERTY_UPDATE_MEASURE_SELF, frameNode);
        frameNode->GetLayoutProperty<TextLayoutProperty>()->OnPropertyChangeMeasure();
    }
}

void SymbolModelStatic::SetSymbolEffect(FrameNode* frameNode, const std::optional<uint32_t>& effectStrategy)
{
    CHECK_NULL_VOID(frameNode);
    if (effectStrategy.has_value()) {
        SymbolModelNG::SetSymbolEffect(frameNode, effectStrategy.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(TextLayoutProperty, SymbolEffectStrategy,
            PROPERTY_UPDATE_MEASURE_SELF, frameNode);
        frameNode->GetLayoutProperty<TextLayoutProperty>()->OnPropertyChangeMeasure();
    }
}

void SymbolModelStatic::SetMinFontScale(FrameNode* frameNode, const std::optional<float>& optValue)
{
    CHECK_NULL_VOID(frameNode);
    if (optValue) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, MinFontScale, optValue.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, MinFontScale, frameNode);
    }
}

void SymbolModelStatic::SetMaxFontScale(FrameNode* frameNode, const std::optional<float>& optValue)
{
    CHECK_NULL_VOID(frameNode);
    if (optValue) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, MaxFontScale, optValue.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TextLayoutProperty, MaxFontScale, frameNode);
    }
}

} // namespace OHOS::Ace::NG
