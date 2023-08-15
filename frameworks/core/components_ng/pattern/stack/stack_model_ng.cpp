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

#include "base/log/ace_trace.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void StackModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StackPattern>(); });
    stack->Push(frameNode);
}

void StackModelNG::Create(Alignment alignment)
{
    Create();
    ACE_UPDATE_LAYOUT_PROPERTY(StackLayoutProperty, AlignmentContent, alignment);
}

void StackModelNG::SetAlignment(Alignment alignment)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, alignment);
    ACE_UPDATE_LAYOUT_PROPERTY(StackLayoutProperty, Alignment, alignment);
}

void StackModelNG::SetAlignmentContent(Alignment alignment)
{
    ACE_UPDATE_LAYOUT_PROPERTY(StackLayoutProperty, AlignmentContent, alignment);
}
} // namespace OHOS::Ace::NG
