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

#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"

#include <string>

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_split/linear_split_pattern.h"
#include "core/components_ng/pattern/linear_split/linear_split_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void LinearSplitModelNG::Create(SplitType splitType)
{
    std::string tag = splitType == SplitType::ROW_SPLIT ? V2::ROW_SPLIT_ETS_TAG : V2::COLUMN_SPLIT_ETS_TAG;
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        tag, nodeId, [splitType]() { return AceType::MakeRefPtr<LinearSplitPattern>(splitType); });
    stack->Push(frameNode);
    ACE_UPDATE_RENDER_CONTEXT(ClipEdge, true);
}

void LinearSplitModelNG::SetResizeable(NG::SplitType splitType, bool resizeable)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LinearSplitLayoutProperty, Resizeable, resizeable);
}

void LinearSplitModelNG::SetDivider(NG::SplitType splitType, const ItemDivider& divider)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LinearSplitLayoutProperty, Divider, divider);
}

} // namespace OHOS::Ace::NG