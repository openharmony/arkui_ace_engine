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

#include "core/components_ng/pattern/scroll/scroll_view.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scroll/scroll_paint_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"

namespace OHOS::Ace::NG {

void ScrollView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    stack->Push(frameNode);
}

void ScrollView::SetAxis(Axis axis)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ScrollLayoutProperty, Axis, axis);
}

void ScrollView::SetScrollBarWidth(const Dimension &width)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ScrollLayoutProperty, BarWidth, width);
}

void ScrollView::SetScrollBarColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollPaintProperty, ScrollBarColor, color);
}

void ScrollView::SetOnScroll(const EventMarker &onScroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(onScroll);
}

void ScrollView::SetOnScrollEdge(const EventMarker &onScroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(onScroll);
}

void ScrollView::SetOnScrollEnd(const EventMarker &onScrollEnd)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(onScrollEnd);
}
} // namespace OHOS::Ace::NG
