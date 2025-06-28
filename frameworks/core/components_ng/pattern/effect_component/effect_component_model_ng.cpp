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

#include "core/components_ng/pattern/effect_component/effect_component_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
void EffectComponentModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::EFFECT_COMPONENT_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::EFFECT_COMPONENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<EffectComponentPattern>(); });
    stack->Push(frameNode);
}

void EffectComponentModelNG::Create(NG::EffectLayer independentLayer)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::EFFECT_COMPONENT_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::EFFECT_COMPONENT_ETS_TAG, nodeId, [independentLayer]() {
        return AceType::MakeRefPtr<EffectComponentPattern>(independentLayer);
    });
    stack->Push(frameNode);
}

void EffectComponentModelNG::AlwaysSnapshot(bool enable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<EffectComponentPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AlwaysSnapshot(enable);
}
} // namespace OHOS::Ace::NG
