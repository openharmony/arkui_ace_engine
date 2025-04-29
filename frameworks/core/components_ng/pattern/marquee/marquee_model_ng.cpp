/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/marquee/marquee_model_ng.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
constexpr int32_t TEXT_MAX_LINES = 1;
void MarqueeModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::MARQUEE_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::MARQUEE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateMaxLines(1);
        frameNode->AddChild(textNode);
    } else {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        CHECK_NULL_VOID(textChild);
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateMaxLines(1);
    }
    stack->Push(frameNode);
}

void MarqueeModelNG::SetValue(const std::optional<std::string>& srcValue)
{
    if (srcValue.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, Src, srcValue.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(MarqueeLayoutProperty, Src, PROPERTY_UPDATE_MEASURE);
    }
}

void MarqueeModelNG::SetPlayerStatus(const std::optional<bool>& playerStatus)
{
    if (playerStatus.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(MarqueePaintProperty, PlayerStatus, playerStatus.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(MarqueePaintProperty, PlayerStatus, PROPERTY_UPDATE_RENDER);
    }
}

void MarqueeModelNG::SetScrollAmount(const std::optional<double>& scrollAmount)
{
    if (scrollAmount.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(MarqueePaintProperty, ScrollAmount, scrollAmount.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(MarqueePaintProperty, ScrollAmount, PROPERTY_UPDATE_RENDER);
    }
}

void MarqueeModelNG::SetLoop(const std::optional<int32_t>& loop)
{
    if (loop.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(MarqueePaintProperty, Loop, loop.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(MarqueePaintProperty, Loop, PROPERTY_UPDATE_RENDER);
    }
}

void MarqueeModelNG::SetDirection(const std::optional<MarqueeDirection>& direction)
{
    if (direction.has_value()) {
        ACE_UPDATE_PAINT_PROPERTY(MarqueePaintProperty, Direction, direction.value());
    } else {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(MarqueePaintProperty, Direction, PROPERTY_UPDATE_RENDER);
    }
}

void MarqueeModelNG::SetAllowScale(const std::optional<bool>& allowScale)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, AllowScale, allowScale.value_or(true));
    CHECK_NULL_VOID(textChild);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, AllowScale, allowScale.value_or(true), textChild);
}

void MarqueeModelNG::SetTextColor(const std::optional<Color>& textColor)
{
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, textColor.value_or(Color()));
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
    if (textColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, FontColor, textColor.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(MarqueeLayoutProperty, FontColor, PROPERTY_UPDATE_MEASURE);
    }
}

void MarqueeModelNG::SetFontSize(const std::optional<Dimension>& fontSize)
{
    if (fontSize.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, FontSize, fontSize.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(MarqueeLayoutProperty, FontSize, PROPERTY_UPDATE_MEASURE);
    }
}

void MarqueeModelNG::SetFontWeight(const std::optional<FontWeight>& fontWeight)
{
    if (fontWeight.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, FontWeight, fontWeight.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(MarqueeLayoutProperty, FontWeight, PROPERTY_UPDATE_MEASURE);
    }
}

void MarqueeModelNG::SetFontFamily(const std::optional<std::vector<std::string>>& fontFamilies)
{
    if (fontFamilies.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, FontFamily, fontFamilies.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(MarqueeLayoutProperty, FontFamily, PROPERTY_UPDATE_MEASURE);
    }
}

void MarqueeModelNG::SetMarqueeUpdateStrategy(const std::optional<MarqueeUpdateStrategy>& marqueeUpdateStrategy)
{
    if (marqueeUpdateStrategy.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, MarqueeUpdateStrategy, marqueeUpdateStrategy.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(MarqueeLayoutProperty, MarqueeUpdateStrategy, PROPERTY_UPDATE_NORMAL);
    }
}

void MarqueeModelNG::SetOnStart(std::function<void()>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStart(std::move(onChange));
}

void MarqueeModelNG::SetOnBounce(std::function<void()>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnBounce(std::move(onChange));
}

void MarqueeModelNG::SetOnFinish(std::function<void()>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFinish(std::move(onChange));
}

RefPtr<FrameNode> MarqueeModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::MARQUEE_ETS_TAG, nodeId, AceType::MakeRefPtr<MarqueePattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(textNode, nullptr);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(textLayoutProperty, nullptr);
        textLayoutProperty->UpdateMaxLines(TEXT_MAX_LINES);
        frameNode->AddChild(textNode);
    } else {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        CHECK_NULL_RETURN(textChild, nullptr);
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(textLayoutProperty, nullptr);
        textLayoutProperty->UpdateMaxLines(TEXT_MAX_LINES);
    }
    return frameNode;
}

void MarqueeModelNG::SetAllowScale(FrameNode* frameNode, const bool allowScale)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MarqueeLayoutProperty, AllowScale, allowScale, frameNode);
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(textChild);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, AllowScale, allowScale, textChild);
}

void MarqueeModelNG::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& fontWeight)
{
    CHECK_NULL_VOID(frameNode);
    if (fontWeight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MarqueeLayoutProperty, FontWeight, fontWeight.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(MarqueeLayoutProperty, FontWeight,
            PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void MarqueeModelNG::SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& fontFamilies)
{
    CHECK_NULL_VOID(frameNode);
    if (fontFamilies.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MarqueeLayoutProperty, FontFamily, fontFamilies.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(MarqueeLayoutProperty, FontFamily,
            PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void MarqueeModelNG::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize)
{
    if (fontSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MarqueeLayoutProperty, FontSize, fontSize.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            MarqueeLayoutProperty, FontSize, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void MarqueeModelNG::SetTextColor(FrameNode* frameNode, const std::optional<Color>& textColor)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, textColor.value_or(Color()), frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
    if (textColor.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MarqueeLayoutProperty, FontColor, textColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            MarqueeLayoutProperty, FontColor, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void MarqueeModelNG::SetMarqueeUpdateStrategy(
    FrameNode* frameNode, const std::optional<MarqueeUpdateStrategy>& marqueeUpdateStrategy)
{
    CHECK_NULL_VOID(frameNode);
    if (marqueeUpdateStrategy.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            MarqueeLayoutProperty, MarqueeUpdateStrategy, marqueeUpdateStrategy.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            MarqueeLayoutProperty, MarqueeUpdateStrategy, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void MarqueeModelNG::SetOnStart(FrameNode* frameNode, std::function<void()>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStart(std::move(onChange));
}

void MarqueeModelNG::SetOnBounce(FrameNode* frameNode, std::function<void()>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnBounce(std::move(onChange));
}

void MarqueeModelNG::SetOnFinish(FrameNode* frameNode, std::function<void()>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFinish(std::move(onChange));
}

void MarqueeModelNG::SetMarqueeFrameRateRange(
    FrameNode* frameNode, const RefPtr<FrameRateRange>& rateRange, MarqueeDynamicSyncSceneType type)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMarqueeFrameRateRange(rateRange, type);
}

void MarqueeModelNG::SetValue(FrameNode* frameNode, const std::optional<std::string>& srcValue)
{
    if (srcValue.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MarqueeLayoutProperty, Src, srcValue.value(), frameNode);
    }
}

void MarqueeModelNG::ResetValue(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(MarqueeLayoutProperty, Src, PROPERTY_UPDATE_MEASURE, frameNode);
}

void MarqueeModelNG::SetPlayerStatus(FrameNode* frameNode, const std::optional<bool>& playerStatus)
{
    if (playerStatus.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(MarqueePaintProperty, PlayerStatus, playerStatus.value(), frameNode);
    }
}

void MarqueeModelNG::ResetPlayerStatus(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(MarqueePaintProperty, PlayerStatus, PROPERTY_UPDATE_RENDER, frameNode);
}

void MarqueeModelNG::SetScrollAmount(FrameNode* frameNode, const std::optional<double>& scrollAmount)
{
    if (scrollAmount.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(MarqueePaintProperty, ScrollAmount, scrollAmount.value(), frameNode);
    }
}

void MarqueeModelNG::ResetScrollAmount(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(MarqueePaintProperty, ScrollAmount, PROPERTY_UPDATE_RENDER, frameNode);
}

void MarqueeModelNG::SetLoop(FrameNode* frameNode, const std::optional<int32_t>& loop)
{
    if (loop.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(MarqueePaintProperty, Loop, loop.value(), frameNode);
    }
}

void MarqueeModelNG::ResetLoop(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(MarqueePaintProperty, Loop, PROPERTY_UPDATE_RENDER, frameNode);
}

void MarqueeModelNG::SetDirection(FrameNode* frameNode, const std::optional<MarqueeDirection>& direction)
{
    if (direction.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(MarqueePaintProperty, Direction, direction.value(), frameNode);
    }
}

void MarqueeModelNG::ResetDirection(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(MarqueePaintProperty, Direction, PROPERTY_UPDATE_RENDER, frameNode);
}
} // namespace OHOS::Ace::NG
