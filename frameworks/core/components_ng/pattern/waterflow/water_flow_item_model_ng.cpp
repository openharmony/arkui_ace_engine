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

#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_node.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_pattern.h"

namespace OHOS::Ace::NG {
void WaterFlowItemModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::FLOW_ITEM_ETS_TAG, nodeId);
    auto frameNode = WaterFlowItemNode::GetOrCreateFlowItem(
        V2::FLOW_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WaterFlowItemPattern>(); });
    stack->Push(frameNode);
}

RefPtr<FrameNode> WaterFlowItemModelNG::CreateFrameNode(int32_t nodeId)
{
    return WaterFlowItemNode::CreateFlowItem(
        V2::FLOW_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<WaterFlowItemPattern>());
}
} // namespace OHOS::Ace::NG
