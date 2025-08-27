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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_NODE_CONTENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_NODE_CONTENT_H

#include <functional>
#include <list>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {

class NodeContent : public AceType {
    DECLARE_ACE_TYPE(NodeContent, AceType);
public:
    NodeContent() = default;
    ~NodeContent() override = default;

    void AttachToNode(UINode* node);
    void DetachFromNode();

    void AddNode(UINode* node, int32_t position = -1);
    void RemoveNode(UINode* node);

    void OnAttachToMainTree();

    void OnDetachFromMainTree();

    void SetAttachToMainTreeCallback(std::function<void()>&& callback)
    {
        onAttachCallback_ = std::move(callback);
    }

    void SetDetachFromMainTreeCallback(std::function<void()>&& callback)
    {
        onDetachCallback_ = std::move(callback);
    }

    void* GetUserData() const
    {
        return userData_;
    }

    void SetUserData(void* userData)
    {
        userData_ = userData;
    }

    WeakPtr<UINode> GetContentSlot()
    {
        return nodeSlot_;
    }

    void AddBuilderToSlot();
private:
    WeakPtr<UINode> nodeSlot_;
    std::list<RefPtr<UINode>> children_;
    std::function<void()> onAttachCallback_;
    std::function<void()> onDetachCallback_;
    void* userData_ = nullptr;

    bool onMainTree_ = false;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_NODE_CONTENT_H
