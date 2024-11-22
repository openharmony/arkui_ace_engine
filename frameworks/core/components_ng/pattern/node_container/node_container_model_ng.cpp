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
#include "core/components_ng/pattern/node_container/node_container_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/node_container/node_container_node.h"

namespace OHOS::Ace::NG {
void NodeContainerModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = NodeContainerNode::GetOrCreateNodeContainerNode(nodeId);
    stack->Push(frameNode);

    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::TOP_LEFT);
}

void NodeContainerModelNG::SetMakeFunction(std::function<RefPtr<UINode>()>&& makeFunc)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->SetMakeFunction(std::move(makeFunc));
}

void NodeContainerModelNG::SetOnResize(std::function<void(const SizeF& size)>&& resizeFunc)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->SetOnResize(std::move(resizeFunc));
}

void NodeContainerModelNG::SetOnAppear(std::function<void()>&& onAppearCallback)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<NodeContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetControllerAboutToAppear(std::move(onAppearCallback));
}

void NodeContainerModelNG::SetOnDisAppear(std::function<void()>&& onDisAppearCallback)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<NodeContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetControllerAboutToDisappear(std::move(onDisAppearCallback));
}

void NodeContainerModelNG::SetOnTouchEvent(TouchEventFunc&& touchEventFunc)
{
    auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetOnTouchEvent(std::move(touchEventFunc));
}

void NodeContainerModelNG::BindController(std::function<void()>&& resetFunc)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->BindController(std::move(resetFunc));
}

void NodeContainerModelNG::ResetController()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->ResetController();
}

void NodeContainerModelNG::FireMakeNode()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = AceType::DynamicCast<NodeContainerPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->RemakeNode();
}
} // namespace OHOS::Ace::NG
