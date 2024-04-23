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

#pragma once

#include <cstdint>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/node_content.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ContentSlotNode : public UINode {
    DECLARE_ACE_TYPE(ContentSlotNode, UINode);

public:
    static RefPtr<ContentSlotNode> GetOrCreateContentSlot(int32_t nodeId);

    explicit ContentSlotNode(int32_t nodeId) : UINode(V2::JS_NODE_SLOT_ETS_TAG, nodeId) {}
    ~ContentSlotNode() override = default;

    bool IsAtomicNode() const override
    {
        return true;
    }

    void AttachNodeContent(NodeContent* content)
    {
        CHECK_NULL_VOID(content);
        if (content_ && (RawPtr(content_) != content)) {
            content_->DetachFromNode();
        }
        content_ = content;
        content_->AttachToNode(this);
    }

    void DetachNodeContent()
    {
        if (content_) {
            content_->DetachFromNode();
        }
        content_ = nullptr;
    }

    void OnAttachToMainTree(bool recursive) override
    {
        UINode::OnAttachToMainTree(recursive);
        if (content_) {
            content_->OnAttachToMainTree();
        }
    }

    void OnDetachFromMainTree(bool recursive) override
    {
        UINode::OnDetachFromMainTree(recursive);
        if (content_) {
            content_->OnDetachFromMainTree();
        }
    }

private:
    RefPtr<NodeContent> content_;

    ACE_DISALLOW_COPY_AND_MOVE(ContentSlotNode);
};

} // namespace OHOS::Ace::NG
