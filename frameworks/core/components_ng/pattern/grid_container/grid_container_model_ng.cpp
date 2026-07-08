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

#include "grid_container_model_ng.h"

#include "grid_container_pattern.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr char GRIDCONTAINER_ETS_TAG[] = "GridContainer";
} // namespace

void GridContainerModelNG::Create(const RefPtr<GridContainerInfo>& containerInfo)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", GRIDCONTAINER_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        GRIDCONTAINER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridContainerLayoutPattern>(); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(GridContainerLayoutProperty, ContainerInfo, *containerInfo);
}

RefPtr<FrameNode> GridContainerModelNG::CreateFrameNode(int32_t nodeId)
{
    auto gridContainerInfo = GridContainerInfo::Builder().Build();
    CHECK_NULL_RETURN(gridContainerInfo, nullptr);

    auto frameNode =
        FrameNode::CreateFrameNode(GRIDCONTAINER_ETS_TAG, nodeId, AceType::MakeRefPtr<GridContainerLayoutPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridContainerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, frameNode);
    layoutProperty->UpdateContainerInfo(*gridContainerInfo);
    return frameNode;
}
} // namespace OHOS::Ace::NG
