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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
void SymbolModelNG::Create(const std::uint32_t& unicode)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto symbolNode = FrameNode::GetOrCreateFrameNode(
        V2::SYMBOL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });

    stack->Push(symbolNode);
    
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolSourceInfo, SymbolSourceInfo{unicode});
}

void SymbolModelNG::SetFontWeight(const Ace::FontWeight& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontWeight, value);
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
} // namespace OHOS::Ace::NG
