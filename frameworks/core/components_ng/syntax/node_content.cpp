/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/syntax/node_content.h"

#include "core/common/builder_util.h"

namespace OHOS::Ace::NG {

void NodeContent::AttachToNode(UINode* node)
{
    auto slot = nodeSlot_.Upgrade();
    if (slot && (slot != node)) {
        DetachFromNode();
    }
    nodeSlot_ = WeakClaim(node);
    std::list<RefPtr<NG::UINode>> nodes;
    for (const auto& child : children_) {
        node->AddChild(child);
        BuilderUtils::GetBuilderNodes(child, nodes);
    }
    BuilderUtils::AddBuilderToParent(Claim(node), nodes);
    node->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    if (node->IsOnMainTree()) {
        OnAttachToMainTree();
    }
}

void NodeContent::DetachFromNode()
{
    auto slot = nodeSlot_.Upgrade();
    nodeSlot_.Reset();
    if (slot) {
        children_ = slot->GetChildren();
        slot->Clean();
        std::list<RefPtr<NG::UINode>> nodes;
        for (const auto& child : children_) {
            BuilderUtils::GetBuilderNodes(child, nodes);
        }
        BuilderUtils::RemoveBuilderFromParent(slot, nodes);
        if (slot->IsOnMainTree()) {
            OnDetachFromMainTree();
        }
    }
}

void NodeContent::AddNode(UINode* node, int32_t position)
{
    auto slot = nodeSlot_.Upgrade();
    auto child = Claim(node);
    if (slot) {
        slot->AddChild(child, position);
        BuilderUtils::AddBuilderToParent(slot, child);
        slot->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    }
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        return;
    }

    it = children_.begin();
    std::advance(it, position);
    children_.insert(it, child);
}

void NodeContent::RemoveNode(UINode* node)
{
    auto nodeRef = Claim(node);
    auto slot = nodeSlot_.Upgrade();
    if (slot) {
        slot->RemoveChild(nodeRef);
        BuilderUtils::RemoveBuilderFromParent(slot, nodeRef);
        slot->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    }
    auto it = std::find(children_.begin(), children_.end(), nodeRef);
    if (it == children_.end()) {
        return;
    }
    children_.erase(it);
}

void NodeContent::OnAttachToMainTree()
{
    if (onMainTree_) {
        return;
    }
    onMainTree_ = true;
    if (onAttachCallback_) {
        onAttachCallback_();
    }
}

void NodeContent::OnDetachFromMainTree()
{
    if (!onMainTree_) {
        return;
    }
    onMainTree_ = false;
    if (onDetachCallback_) {
        onDetachCallback_();
    }
}

} // namespace OHOS::Ace::NG
