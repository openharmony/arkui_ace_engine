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

#include "core/components_ng/pattern/text/symbol_span_model_ng.h"

#include "core/components_ng/pattern/text/symbol_span_model_static.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#define ACE_UPDATE_NODE_SYMBOL_SPAN_PROPERTY(name, value, frameNode)                                             \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);                                               \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
    } while (false)

#define ACE_RESET_NODE_SPAN_PROPERTY(name, frameNode)                                                            \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);                                               \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Reset##name();                                                                                 \
    } while (false)

namespace OHOS::Ace::NG {
RefPtr<UINode> SymbolSpanModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, nodeId);
    return spanNode;
}

void SymbolSpanModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    if (valueOpt.has_value()) {
        SymbolSpanModelNG::SetFontSize(frameNode, valueOpt.value());
        return;
    }
    ACE_RESET_NODE_SPAN_PROPERTY(FontSize, frameNode);
}

void SymbolSpanModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& valueOpt)
{
    if (valueOpt.has_value()) {
        SymbolSpanModelNG::SetFontWeight(frameNode, valueOpt.value());
        return;
    }
    ACE_RESET_NODE_SPAN_PROPERTY(FontWeight, frameNode);
}

void SymbolSpanModelStatic::SetSymbolRenderingStrategy(FrameNode* frameNode,
    const std::optional<uint32_t>& renderingStrategy)
{
    if (renderingStrategy.has_value()) {
        SymbolSpanModelNG::SetSymbolRenderingStrategy(frameNode, renderingStrategy.value());
        return;
    }
    ACE_RESET_NODE_SPAN_PROPERTY(SymbolRenderingStrategy, frameNode);
}

void SymbolSpanModelStatic::SetSymbolEffect(FrameNode* frameNode, const std::optional<uint32_t>& effectStrategy)
{
    if (effectStrategy.has_value()) {
        SymbolSpanModelNG::SetSymbolEffect(frameNode, effectStrategy.value());
        return;
    }
    ACE_RESET_NODE_SPAN_PROPERTY(SymbolEffectStrategy, frameNode);
}

} // namespace OHOS::Ace::NG
