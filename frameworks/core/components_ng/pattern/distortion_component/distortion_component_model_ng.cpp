/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/distortion_component/distortion_component_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/distortion_component/distortion_component_node.h"

namespace OHOS::Ace::NG {
void DistortionComponentModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::DISTORTION_COMPONENT_ETS_TAG, nodeId);
    auto frameNode = DistortionComponentNode::GetOrCreateDistortionComponentNode(
        V2::DISTORTION_COMPONENT_ETS_TAG, nodeId, []() {
            return AceType::MakeRefPtr<DistortionComponentPattern>();
        });
    stack->Push(frameNode);

    // Create content node immediately after parent node is created
    // This ensures content node exists before any children are mounted
    auto pattern = frameNode->GetPattern<DistortionComponentPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->CreateContentNode();
}

void DistortionComponentModelNG::SetDistortion(const DistortionParam& distortion)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<DistortionComponentPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDistortion(distortion);
}

} // namespace OHOS::Ace::NG
