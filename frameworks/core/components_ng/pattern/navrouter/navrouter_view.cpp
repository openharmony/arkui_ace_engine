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

#include "core/components_ng/pattern/navrouter/navrouter_view.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/navrouter/navrouter_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void NavRouterView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        V2::NAVROUTER_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    stack->Push(navRouterNode);
}

void NavRouterView::SetOnStateChange(std::function<void(bool)>&& onStateChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navRouterEventHub = AceType::DynamicCast<NavRouterEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navRouterEventHub);
    navRouterEventHub->SetOnStateChange(std::move(onStateChange));
}

} // namespace OHOS::Ace::NG