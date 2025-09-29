/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/pattern/ability_component/ability_component_model_ng.h"

#include "frameworks/core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void AbilityComponentModelNG::Create(const std::string& bundleName, const std::string& abilityName)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::ABILITY_COMPONENT_ETS_TAG,  nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::ABILITY_COMPONENT_ETS_TAG, nodeId,
        [bundleName, abilityName]() { return AceType::MakeRefPtr<AbilityComponentPattern>(bundleName, abilityName); });
    stack->Push(frameNode);
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(nodeId);
}

void AbilityComponentModelNG::SetWant(const std::string& want)
{
    ACE_UPDATE_PAINT_PROPERTY(AbilityComponentRenderProperty, Want, want);
}

void AbilityComponentModelNG::SetOnConnect(std::function<void()>&& onConnect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<AbilityComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnConnect(std::move(onConnect));
}

void AbilityComponentModelNG::SetOnDisConnect(std::function<void()>&& onDisConnect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<AbilityComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDisConnect(std::move(onDisConnect));
}
} // namespace OHOS::Ace::NG
