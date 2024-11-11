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

#include "core/components_ng/pattern/text/text_pattern.h"
   
#define ACE_UPDATE_SYMBOL_SPAN_PROPERTY(name, value, flag)                                                       \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode()); \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
        spanNode->AddPropertyInfo(flag);                                                                         \
    } while (false)

#define ACE_UPDATE_NODE_SYMBOL_SPAN_PROPERTY(name, value, flag, frameNode)                                       \
    do {                                                                                                         \
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);                                               \
        CHECK_NULL_VOID(spanNode);                                                                               \
        spanNode->Update##name(value);                                                                           \
        spanNode->AddPropertyInfo(flag);                                                                         \
    } while (false)

namespace OHOS::Ace::NG {
void SymbolSpanModelNG::Create(const uint32_t& unicode)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
   
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, nodeId);
    stack->Push(spanNode);

    ACE_UPDATE_SYMBOL_SPAN_PROPERTY(Content, unicode, PropertyInfo::NONE);
}

void SymbolSpanModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_SYMBOL_SPAN_PROPERTY(FontSize, value, PropertyInfo::FONTSIZE);
}

void SymbolSpanModelNG::SetFontWeight(Ace::FontWeight value)
{
    ACE_UPDATE_SYMBOL_SPAN_PROPERTY(FontWeight, value, PropertyInfo::FONTWEIGHT);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateUserFontWeight(true);
}

void SymbolSpanModelNG::SetFontColor(std::vector<Color>& symbolColor)
{
    ACE_UPDATE_SYMBOL_SPAN_PROPERTY(SymbolColorList, symbolColor, PropertyInfo::SYMBOL_COLOR);
}

void SymbolSpanModelNG::SetSymbolRenderingStrategy(const uint32_t renderingStrategy)
{
    ACE_UPDATE_SYMBOL_SPAN_PROPERTY(SymbolRenderingStrategy, renderingStrategy,
        PropertyInfo::SYMBOL_RENDERING_STRATEGY);
}

void SymbolSpanModelNG::SetSymbolEffect(const uint32_t effectStrategy)
{
    ACE_UPDATE_SYMBOL_SPAN_PROPERTY(SymbolEffectStrategy, effectStrategy, PropertyInfo::SYMBOL_EFFECT_STRATEGY);
}

RefPtr<UINode> SymbolSpanModelNG::CreateFrameNode(int32_t nodeId)
{
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, nodeId);
    return spanNode;
}

void SymbolSpanModelNG::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    if (valueOpt.has_value()) {
        spanNode->UpdateFontSize(valueOpt.value());
        spanNode->AddPropertyInfo(PropertyInfo::FONTSIZE);
    } else {
        spanNode->ResetFontSize();
    }
}

void SymbolSpanModelNG::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& valueOpt)
{
    auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
    CHECK_NULL_VOID(spanNode);
    if (valueOpt.has_value()) {
        spanNode->UpdateFontWeight(valueOpt.value());
        spanNode->AddPropertyInfo(PropertyInfo::FONTWEIGHT);
        spanNode->UpdateUserFontWeight(true);
    } else {
        spanNode->ResetFontWeight();
    }
}

void SymbolSpanModelNG::SetFontColor(FrameNode* frameNode, std::vector<Color>& symbolColor)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_SYMBOL_SPAN_PROPERTY(SymbolColorList, symbolColor,
        PropertyInfo::SYMBOL_COLOR, frameNode);
}

void SymbolSpanModelNG::SetSymbolRenderingStrategy(FrameNode* frameNode,
    const std::optional<uint32_t>& renderingStrategy)
{
    CHECK_NULL_VOID(frameNode);
    if (renderingStrategy.has_value()) {
        ACE_UPDATE_NODE_SYMBOL_SPAN_PROPERTY(SymbolRenderingStrategy, renderingStrategy.value(),
            PropertyInfo::SYMBOL_RENDERING_STRATEGY, frameNode);
    } else {
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
        spanNode->ResetSymbolRenderingStrategy();
    }
}

void SymbolSpanModelNG::SetSymbolEffect(FrameNode* frameNode, const std::optional<uint32_t>& effectStrategy)
{
    CHECK_NULL_VOID(frameNode);
    if (effectStrategy.has_value()) {
        ACE_UPDATE_NODE_SYMBOL_SPAN_PROPERTY(SymbolEffectStrategy, effectStrategy.value(),
            PropertyInfo::SYMBOL_EFFECT_STRATEGY, frameNode);
    } else {
        auto spanNode = AceType::DynamicCast<SpanNode>(frameNode);
        spanNode->ResetSymbolEffectStrategy();
    }
}

void SymbolSpanModelNG::InitialSymbol(FrameNode* frameNode, const std::uint32_t& unicode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_SYMBOL_SPAN_PROPERTY(Content, unicode, PropertyInfo::NONE, frameNode);
}
} // namespace OHOS::Ace::NG
