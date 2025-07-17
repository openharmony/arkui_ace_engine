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

#include "core/components_ng/pattern/linear_split/linear_split_model_ng_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_split/linear_split_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> LinearSplitModelNGStatic::CreateFrameNode(int32_t nodeId, SplitType splitType)
{
    std::string tag = splitType == SplitType::ROW_SPLIT ? V2::ROW_SPLIT_ETS_TAG : V2::COLUMN_SPLIT_ETS_TAG;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        tag, nodeId, [splitType]() { return AceType::MakeRefPtr<LinearSplitPattern>(splitType); });
    return frameNode;
}

void LinearSplitModelNGStatic::SetDivider(FrameNode* frameNode, NG::SplitType splitType,
    const std::optional<ColumnSplitDivider>& optDivider)
{
    CHECK_NULL_VOID(frameNode);
    if (optDivider) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearSplitLayoutProperty, Divider, optDivider.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(LinearSplitLayoutProperty, Divider, frameNode);
    }
}
}
