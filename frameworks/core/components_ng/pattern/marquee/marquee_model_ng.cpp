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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/marquee/marquee_paint_property.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
void MarqueeModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
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
    if (allowScale.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, AllowScale, allowScale.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(MarqueeLayoutProperty, AllowScale, PROPERTY_UPDATE_MEASURE);
    }
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

void MarqueeModelNG::SetOnStart(std::function<void()>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStart(std::move(onChange));
}

void MarqueeModelNG::SetOnBounce(std::function<void()>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnBounce(std::move(onChange));
}

void MarqueeModelNG::SetOnFinish(std::function<void()>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFinish(std::move(onChange));
}
} // namespace OHOS::Ace::NG
