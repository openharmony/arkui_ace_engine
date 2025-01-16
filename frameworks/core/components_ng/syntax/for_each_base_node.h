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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_BASE_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_BASE_NODE_H

#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ForEachBaseNode : public UINode {
    DECLARE_ACE_TYPE(ForEachBaseNode, UINode);

public:
    ForEachBaseNode(const std::string& tag, int32_t nodeId, bool isRoot = false) : UINode(tag, nodeId, isRoot) {}
    virtual void MoveData(int32_t from, int32_t to) = 0;
    virtual RefPtr<FrameNode> GetFrameNode(int32_t index) = 0;
    virtual void RecycleItems(int32_t from, int32_t to) {}
    virtual void FireOnMove(int32_t from, int32_t to)
    {
        if (from != to && onMoveEvent_) {
            onMoveEvent_(from, to);
        }
    }

    bool IsSyntaxNode() const override
    {
        return true;
    }

protected:
    std::function<void(int32_t, int32_t)> onMoveEvent_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_BASE_NODE_H
