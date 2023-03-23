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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_GROUP_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_GROUP_NODE_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GroupNode : public FrameNode {
    DECLARE_ACE_TYPE(GroupNode, FrameNode);

public:
    GroupNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : FrameNode(tag, nodeId, pattern, isRoot) {}
    ~GroupNode() override = default;
    virtual void AddChildToGroup(const RefPtr<UINode>& children, int32_t slot = DEFAULT_NODE_SLOT) {};
    virtual void DeleteChildFromGroup(int32_t slot = DEFAULT_NODE_SLOT) {};
    // The function is only used for fast preview.
    void FastPreviewUpdateChild(int32_t slot, const RefPtr<UINode>& newChild) override
    {
        DeleteChildFromGroup(slot);
        AddChildToGroup(newChild, slot);
    }
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_GROUP_NODE_H
