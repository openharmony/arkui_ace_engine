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

#include "core/components_ng/pattern/marquee/marquee_view.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void MarqueeView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::MARQUEE_COMPONENT_TAG, nodeId, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(std::string(""));
        frameNode->AddChild(textNode);
    } else {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        ACE_DCHECK(textChild);
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        ACE_DCHECK(textLayoutProperty);
        textLayoutProperty->UpdateContent(std::string(""));
    }
    stack->Push(frameNode);
}

void MarqueeView::SetValue(const std::string& value)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_DCHECK(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty);
    textLayoutProperty->UpdateContent(value);
}

void MarqueeView::SetPlayerStatus(bool playerStatus)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, PlayerStatus, playerStatus);
}

void MarqueeView::SetScrollAmount(double scrollAmount)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, ScrollAmount, scrollAmount);
}

void MarqueeView::SetLoop(int32_t loop)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, Loop, loop);
}

void MarqueeView::SetDirection(MarqueeDirection direction)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, Direction, direction);
}

void MarqueeView::SetAllowScale(bool allowScale)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MarqueeLayoutProperty, AllowScale, allowScale);
}

void MarqueeView::SetTextColor(const Color& textColor)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_DCHECK(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(textColor);
}

void MarqueeView::SetFontSize(const Dimension& fontSize)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_DCHECK(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty);
    textLayoutProperty->UpdateFontSize(fontSize);
}

void MarqueeView::SetFontWeight(const FontWeight& fontWeight)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_DCHECK(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty);
    textLayoutProperty->UpdateFontWeight(fontWeight);
}

void MarqueeView::SetFontFamily(const std::vector<std::string>& fontFamilies)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_DCHECK(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty);
    textLayoutProperty->UpdateFontFamily(fontFamilies);
}

void MarqueeView::SetOnStart(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStart(std::move(onChange));
}

void MarqueeView::SetOnBounce(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnBounce(std::move(onChange));
}

void MarqueeView::SetOnFinish(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnFinish(std::move(onChange));
}
} // namespace OHOS::Ace::NG
