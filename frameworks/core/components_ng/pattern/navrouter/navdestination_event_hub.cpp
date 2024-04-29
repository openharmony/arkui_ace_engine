/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "frameworks/core/components_ng/pattern/navrouter/navdestination_event_hub.h"

#include "core/common/container.h"
#include "frameworks/core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.h"
namespace OHOS::Ace::NG {
void NavDestinationEventHub::FireOnDisappear()
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navDestination);
    if (navDestination->GetIsAnimated()) {
        FireDisappearCallback();
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddAfterLayoutTask([weakDestination = WeakPtr<NavDestinationGroupNode>(navDestination)]() {
        auto destination = weakDestination.Upgrade();
        CHECK_NULL_VOID(destination);
        auto eventHub = destination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireDisappearCallback();
        auto pattern = destination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetCustomNode(nullptr);
    });
}

void NavDestinationEventHub::FireAutoSave()
{
    auto node = GetFrameNode();
    CHECK_NULL_VOID(node);
    if (!node->NeedRequestAutoSave()) {
        return;
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    container->RequestAutoSave(node);
}
}