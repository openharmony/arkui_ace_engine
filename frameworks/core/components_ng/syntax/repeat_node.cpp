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

#include "core/components_ng/syntax/repeat_node.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

// REPEAT
RefPtr<RepeatNode> RepeatNode::GetOrCreateRepeatNode(int32_t nodeId)
{
    auto node = ElementRegister::GetInstance()->GetSpecificItemById<RepeatNode>(nodeId);
    if (node) {
        return node;
    }
    node = MakeRefPtr<RepeatNode>(nodeId);
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

// REPEAT
void RepeatNode::CreateTempItems()
{
    std::swap(ids_, tempIds_);
    TraversingCheck();
    std::swap(ModifyChildren(), tempChildren_);

    tempChildrenOfRepeat_ = std::vector<RefPtr<UINode>>(tempChildren_.begin(), tempChildren_.end());
}

// RepeatNode only
void RepeatNode::FinishRepeatRender(std::list<int32_t>& removedElmtId)
{
    ACE_SCOPED_TRACE("RepeatNode::FinishRepeatRender");

    // Required to build unordered_set of RefPtr<UINodes>
    struct Hash {
        size_t operator()(const RefPtr<UINode>& node) const
        {
            return node->GetId();
        }
    };

    // includes "newly-added" and "reused" children
    const auto& children = GetChildren();

    std::unordered_set<RefPtr<UINode>, Hash>
        newNodeSet(children.begin(), children.end());

    // remove "unused" children
    for (const auto& oldNode: tempChildrenOfRepeat_) {
        if (newNodeSet.find(oldNode) == newNodeSet.end()) {
            // Adding silently, so that upon removal node is a part the tree.
            AddChild(oldNode, DEFAULT_NODE_SLOT, true);
            // Remove and trigger all Detach callback.
            RemoveChild(oldNode, true);
            // Collect IDs of removed nodes starting from 'oldNode' (incl.)
            CollectRemovedChildren({ oldNode }, removedElmtId, false);
        }
    }

    tempChildren_.clear();
    tempChildrenOfRepeat_.clear();

    auto frameNode = GetParentFrameNode();
    if (frameNode) {
        frameNode->ChildrenUpdatedFrom(0);
    }
}

// RepeatNode only
void RepeatNode::MoveChild(uint32_t fromIndex)
{
    // copy child from tempChildrenOfRepeat_[fromIndex] and append to children_
    if (fromIndex < tempChildrenOfRepeat_.size()) {
        auto& node = tempChildrenOfRepeat_.at(fromIndex);
        AddChild(node, DEFAULT_NODE_SLOT, true);
    }
}

// Repeat
void RepeatNode::SetOnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
   // To do
}

// FOREACH
void RepeatNode::MoveData(int32_t from, int32_t to)
{
    // To do
}

void RepeatNode::FlushUpdateAndMarkDirty()
{
    tempIds_.clear();
    // mark parent dirty to flush measure.
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

// STATE_MGMT_NOTE called from where ?
RefPtr<FrameNode> RepeatNode::GetFrameNode(int32_t index)
{
    return AceType::DynamicCast<FrameNode>(GetFrameChildByIndex(index, false, false));
}

void RepeatNode::InitDragManager(const RefPtr<UINode>& child)
{
    // To do
}

void RepeatNode::InitAllChildrenDragManager(bool init)
{
    // To do
}

} // namespace OHOS::Ace::NG
