/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_EVENT_MANAGER_FRAME_NODE_ON_TREE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_EVENT_MANAGER_FRAME_NODE_ON_TREE_H

#define private public
#define protected public

#include "core/components_ng/base/frame_node.h"
namespace OHOS::Ace::NG {
class FrameNodeOnTree : public FrameNode {

    DECLARE_ACE_TYPE(FrameNodeOnTree, FrameNode);
public:

    FrameNodeOnTree(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern,
        bool isRoot = false, bool isLayoutNode = false) : FrameNode(tag, nodeId, pattern, isRoot, false)
    {
        onMainTree_ = true;
    }

    static RefPtr<FrameNode> CreateFrameNode(
        const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
    {
        auto frameNode = FrameNode::CreateFrameNode(tag, nodeId, pattern, isRoot);
        frameNode->onMainTree_ = true;
        return frameNode;
    }

    static RefPtr<FrameNode> GetOrCreateFrameNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
    {
        auto frameNode = FrameNode::GetOrCreateFrameNode(tag, nodeId, patternCreator);
        frameNode->onMainTree_ = true;
        return frameNode;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_EVENT_MANAGER_FRAME_NODE_ON_TREE_H