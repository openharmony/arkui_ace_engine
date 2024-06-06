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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_NODE_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NodeContainerNode : public FrameNode {
    DECLARE_ACE_TYPE(NodeContainerNode, FrameNode);

public:
    NodeContainerNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : FrameNode(tag, nodeId, pattern)
    {}
    ~NodeContainerNode() override = default;

    static RefPtr<FrameNode> GetOrCreateNodeContainerNode(int32_t nodeId);

    void OnRecycle() override;
    void OnReuse() override;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_NODE_H
