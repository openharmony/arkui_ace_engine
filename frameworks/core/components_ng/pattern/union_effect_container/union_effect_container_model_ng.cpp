/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/union_effect_container/union_effect_container_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/union_effect_container/union_effect_container_pattern.h"
#include "core/components_ng/property/union_effect_container_options.h"

namespace OHOS::Ace::NG {
void UnionEffectContainerModelNG::Create(const UnionEffectContainerOptions& options)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::UNION_EFFECT_CONTAINER_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::UNION_EFFECT_CONTAINER_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<UnionEffectContainerPattern>(); });
    stack->Push(frameNode);
    auto pattern = frameNode->GetPattern<UnionEffectContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSpacing(options.spacing);
}
} // namespace OHOS::Ace::NG
