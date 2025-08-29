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

#include "core/components_ng/pattern/list/list_item_pattern.h"
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
    from_ = -1;
    to_ = -1;

    auto frameNode = GetParentFrameNode();
    if (frameNode) {
        frameNode->ChildrenUpdatedFrom(0);
    }
}

void RepeatNode::RecycleChild(uint32_t index)
{
    if (index < tempChildrenOfRepeat_.size()) {
        auto& node = tempChildrenOfRepeat_.at(index);
        node->OnRecycle();
    }
}

void RepeatNode::ReuseChild(uint32_t index)
{
    if (index < tempChildrenOfRepeat_.size()) {
        auto& node = tempChildrenOfRepeat_.at(index);
        node->OnReuse();
    }
}

void RepeatNode::AfterAddChild()
{
    if (!ModifyChildren().empty()) {
        InitDragManager(ModifyChildren().back());
    }
}

// RepeatNode only
void RepeatNode::MoveChild(uint32_t fromIndex)
{
    if (from_ >= 0) {
        // from_ to_ exist, need adjust index.
        if (fromIndex == static_cast<uint32_t>(from_)) {
            fromIndex = static_cast<uint32_t>(to_);
        } else if (fromIndex > static_cast<uint32_t>(from_) && fromIndex <= static_cast<uint32_t>(to_)) {
            fromIndex--;
        } else if (fromIndex < static_cast<uint32_t>(from_) && fromIndex >= static_cast<uint32_t>(to_)) {
            fromIndex++;
        }
    }

    // copy child from tempChildrenOfRepeat_[fromIndex] and append to children_
    if (fromIndex < tempChildrenOfRepeat_.size()) {
        auto& node = tempChildrenOfRepeat_.at(fromIndex);
        AddChild(node, DEFAULT_NODE_SLOT, true);
    }
}

// Repeat
void RepeatNode::SetOnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    if (onMove && !onMoveEvent_) {
        auto parentNode = GetParentFrameNode();
        if (parentNode) {
            InitAllChildrenDragManager(true);
        } else {
            auto piplineContext = GetContext();
            CHECK_NULL_VOID(piplineContext);
            auto taskExecutor = piplineContext->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [weak = WeakClaim(this)]() mutable {
                    auto forEach = weak.Upgrade();
                    CHECK_NULL_VOID(forEach);
                    forEach->InitAllChildrenDragManager(true);
                },
                TaskExecutor::TaskType::UI, "ArkUIInitAllChildrenDragManager");
        }
    } else if (!onMove && onMoveEvent_) {
        InitAllChildrenDragManager(false);
    }
    onMoveEvent_ = onMove;
}

void RepeatNode::SetItemDragHandler(std::function<void(int32_t)>&& onLongPress,
    std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
    std::function<void(int32_t)>&& onDrop)
{
    if (onMoveEvent_) {
        onLongPressEvent_ = onLongPress;
        onDragStartEvent_ = onDragStart;
        onMoveThroughEvent_ = onMoveThrough;
        onDropEvent_ = onDrop;
    }
}

// FOREACH
void RepeatNode::MoveData(int32_t from, int32_t to)
{
    if (from == to || from < 0 || to < 0) {
        return;
    }

    if (from_ < 0) {
        from_ = from;
    }

    to_ = to;

    if (from_ == to_) {
        from_ = -1;
        to_ = -1;
    }
    auto& children = ModifyChildren();
    auto fromIter = children.begin();
    std::advance(fromIter, from);
    auto child = *fromIter;
    TraversingCheck(child);
    children.erase(fromIter);
    auto toIter = children.begin();
    std::advance(toIter, to);
    children.insert(toIter, child);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
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
    CHECK_NULL_VOID(onMoveEvent_);
    CHECK_NULL_VOID(child);
    auto childNode = AceType::DynamicCast<FrameNode>(child->GetFrameChildByIndex(0, false));
    CHECK_NULL_VOID(childNode);
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        return;
    }
    auto pattern = childNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitDragManager(AceType::Claim(this));
}

void RepeatNode::InitAllChildrenDragManager(bool init)
{
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        onMoveEvent_ = nullptr;
        return;
    }
    const auto& children = GetChildren();
    for (const auto& child : children) {
        if (!child || (child->GetChildren().size() != 1)) {
            continue;
        }
        auto listItem = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
        if (!listItem) {
            continue;
        }
        auto pattern = listItem->GetPattern<ListItemPattern>();
        if (!pattern) {
            continue;
        }
        if (init) {
            pattern->InitDragManager(AceType::Claim(this));
        } else {
            pattern->DeInitDragManager();
        }
    }
}

} // namespace OHOS::Ace::NG
