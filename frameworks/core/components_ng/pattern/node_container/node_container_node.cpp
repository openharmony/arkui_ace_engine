/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/node_container/node_container_node.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> NodeContainerNode::GetOrCreateNodeContainerNode(int32_t nodeId)
{
    auto frameNode = GetFrameNode(V2::NODE_CONTAINER_ETS_TAG, nodeId);
    if (frameNode) {
        return frameNode;
    }
    auto pattern = AceType::MakeRefPtr<NodeContainerPattern>();
    frameNode = AceType::MakeRefPtr<NodeContainerNode>(V2::NODE_CONTAINER_ETS_TAG, nodeId, pattern);
    ElementRegister::GetInstance()->AddUINode(frameNode);
    frameNode->InitializePatternAndContext();
    return frameNode;
}

void NodeContainerNode::OnRecycle()
{
    for (const auto& destroyCallback : destroyCallbacksMap_) {
        if (destroyCallback.second) {
            destroyCallback.second();
        }
    }
    GetLayoutProperty()->ResetGeometryTransition();
    GetPattern()->OnRecycle();
}

void NodeContainerNode::OnReuse()
{
    auto pattern = GetPattern<NodeContainerPattern>();
    if (pattern) {
        pattern->OnReuse();
    }
    if (SystemProperties::GetDeveloperModeOn()) {
        PaintDebugBoundary(SystemProperties::GetDebugBoundaryEnabled());
    }
}
} // namespace OHOS::Ace::NG
