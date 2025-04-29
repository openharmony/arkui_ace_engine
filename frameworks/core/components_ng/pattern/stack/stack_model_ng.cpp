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

#include "core/components_ng/pattern/stack/stack_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"

namespace OHOS::Ace::NG {

void StackModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::STACK_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StackPattern>(); });
    stack->Push(frameNode);
    frameNode->SetExclusiveEventForChild(true);
}

void StackModelNG::Create(Alignment alignment)
{
    Create();
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, alignment);
}

RefPtr<FrameNode> StackModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG, nodeId, AceType::MakeRefPtr<StackPattern>());
    frameNode->SetExclusiveEventForChild(true);
    return frameNode;
}

void StackModelNG::SetAlignment(Alignment alignment)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, alignment);
}

void StackModelNG::SetAlignment(FrameNode* frameNode, Alignment alignment)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, Alignment, alignment, frameNode);
}

Alignment StackModelNG::GetAlignment(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, Alignment::CENTER);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, Alignment::CENTER);
    CHECK_NULL_RETURN(layoutProperty->GetPositionProperty(), Alignment::CENTER);
    return layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER);
}
} // namespace OHOS::Ace::NG
