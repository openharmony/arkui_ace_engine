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

#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"

#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"

namespace OHOS::Ace::NG {
void NavRouterModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVROUTER_VIEW_ETS_TAG, nodeId);
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        V2::NAVROUTER_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    stack->Push(navRouterNode);
}

void NavRouterModelNG::SetOnStateChange(std::function<void(bool isActivated)>&& onStateChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navRouterEventHub = AceType::DynamicCast<NavRouterEventHub>(frameNode->GetOrCreateEventHub<EventHub>());
    CHECK_NULL_VOID(navRouterEventHub);
    navRouterEventHub->SetOnStateChange(std::move(onStateChange));
}

void NavRouterModelNG::SetNavRouteMode(int32_t mode)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto navRouterGroupNode = AceType::DynamicCast<NavRouterGroupNode>(frameNode);
    CHECK_NULL_VOID(navRouterGroupNode);
    auto navRouterPattern = navRouterGroupNode->GetPattern<NavRouterPattern>();
    CHECK_NULL_VOID(navRouterPattern);
    navRouterPattern->SetNavRouteMode(static_cast<NG::NavRouteMode>(mode));
}

void NavRouterModelNG::SetNavRouteMode(FrameNode* frameNode, int32_t mode)
{
    CHECK_NULL_VOID(frameNode);
    auto navRouterGroupNode = AceType::DynamicCast<NavRouterGroupNode>(frameNode);
    CHECK_NULL_VOID(navRouterGroupNode);
    auto navRouterPattern = navRouterGroupNode->GetPattern<NavRouterPattern>();
    CHECK_NULL_VOID(navRouterPattern);
    navRouterPattern->SetNavRouteMode(static_cast<NG::NavRouteMode>(mode));
}

void NavRouterModelNG::SetOnStateChange(FrameNode* frameNode, std::function<void(bool isActivated)>&& onStateChange)
{
    CHECK_NULL_VOID(frameNode);
    auto navRouterEventHub = AceType::DynamicCast<NavRouterEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navRouterEventHub);
    navRouterEventHub->SetOnStateChange(std::move(onStateChange));
}
} // namespace OHOS::Ace::NG
