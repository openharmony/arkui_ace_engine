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

#include "core/components_ng/pattern/ability_component/ability_component_view.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/ability_component/ability_component_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void AbilityComponentView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::ABILITY_COMPONENT_TAG, nodeId, []() { return AceType::MakeRefPtr<AbilityComponentPattern>(); });
    stack->Push(frameNode);
}

void AbilityComponentView::SetWidth(Dimension value)
{
    ACE_UPDATE_PAINT_PROPERTY(AbilityComponentRenderProperty, Width, value);
}

void AbilityComponentView::SetHeight(Dimension value)
{
    ACE_UPDATE_PAINT_PROPERTY(AbilityComponentRenderProperty, Height, value);
}

void AbilityComponentView::SetOpacity(Dimension value)
{
    ACE_UPDATE_PAINT_PROPERTY(AbilityComponentRenderProperty, Opacity, value);
}

void AbilityComponentView::SetWant(const std::string& want)
{
    ACE_UPDATE_PAINT_PROPERTY(AbilityComponentRenderProperty, Want, want);
}

void AbilityComponentView::SetOnConnect(ConnectEvent&& onConnect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<AbilityComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnConnect(std::move(onConnect));
}

void AbilityComponentView::SetOnDisConnect(DisConnectEvent&& onDisConnect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<AbilityComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnConnect(std::move(onDisConnect));
}
} // namespace OHOS::Ace::NG
