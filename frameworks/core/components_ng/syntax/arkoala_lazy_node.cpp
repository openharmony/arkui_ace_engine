/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/syntax/arkoala_lazy_node.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
ArkoalaLazyNode::ArkoalaLazyNode(int32_t nodeId, bool isRepeat) : ForEachBaseNode(
    isRepeat ? V2::JS_REPEAT_ETS_TAG : V2::JS_LAZY_FOR_EACH_ETS_TAG, nodeId), isRepeat_(isRepeat) {}

void ArkoalaLazyNode::DoSetActiveChildRange(
    int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
    ACE_SYNTAX_SCOPED_TRACE(
        "ArkoalaLazyNode[self:%d].DoSetActiveChildRange start[%d] end[%d] cacheStart[%d] cacheEnd[%d] showCache[%d]",
        GetId(), start, end, cacheStart, cacheEnd, static_cast<int32_t>(showCache));
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH, "ArkoalaLazyNode[self:%{public}d].DoSetActiveChildRange"
        "(%{public}d, %{public}d, %{public}d, %{public}d, %{public}d)",
        GetId(), start, end, cacheStart, cacheEnd, static_cast<int32_t>(showCache));
    // range of screen node & preload node
    const RangeType cacheRange { start - cacheStart, end + cacheEnd };
    if (updateRange_) {
        // trigger TS-side
        updateRange_(cacheRange.first, cacheRange.second);
    }

    // range of screen node
    const RangeType activeRange = showCache ? cacheRange : std::make_pair(start, end);
    std::list<RefPtr<UINode>> toRemove;
    for (const auto& [index, node] : node4Index_) {
        if (!node) {
            continue;
        }
        const auto indexMapped = ConvertFromToIndexRevert(index);
        const bool isInCacheRange = IsNodeInRange(indexMapped, cacheRange);
        const bool isInActiveRange = IsNodeInRange(indexMapped, activeRange);
        if (!isInCacheRange || (!isRepeat_ && !isInActiveRange)) { // LazyForEach need to remove inactive nodes
            RemoveChild(node);
        }
        node->SetActive(isInActiveRange);
        if (isRepeat_) {
            // trigger onReuse/onRecycle
            UpdateIsCache(node, isInCacheRange);
        }
    }

    node4Index_.RemoveIf([cacheRange, weak = WeakClaim(this)](const uint32_t& k, const auto& _) {
        const auto idx = static_cast<int32_t>(k);
        auto arkoalaLazyNode = weak.Upgrade();
        CHECK_NULL_RETURN(arkoalaLazyNode, true);
        const auto indexMapped = arkoalaLazyNode->ConvertFromToIndexRevert(idx);
        return !arkoalaLazyNode->IsNodeInRange(indexMapped, cacheRange);
    });
}

void ArkoalaLazyNode::UpdateIsCache(const RefPtr<UINode>& node, bool isCache, bool shouldTrigger)
{
    if (!shouldTrigger) {
        return;
    }
    CHECK_NULL_VOID(node);
    auto child = node->GetFrameChildByIndex(0, false);
    CHECK_NULL_VOID(child);
    if (isCache) {
        if (recycleNodeIds_.erase(child->GetId()) == 0) {
            return;
        }
        child->OnReuse();
    } else {
        if (recycleNodeIds_.emplace(child->GetId()).second == false) {
            return;
        }
        child->OnRecycle();
    }
}

RefPtr<UINode> ArkoalaLazyNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    const auto indexCasted = static_cast<int32_t>(index);
    ACE_SYNTAX_SCOPED_TRACE(
        "ArkoalaLazyNode[self:%d].GetFrameChildByIndex index[%d] needBuild[%d] isCache[%d] addToRenderTree[%d]",
        GetId(), indexCasted, static_cast<int32_t>(needBuild), static_cast<int32_t>(isCache),
        static_cast<int32_t>(addToRenderTree));
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
        "ArkoalaLazyNode[self:%{public}d].GetFrameChildByIndex(%{public}d, %{public}d, %{public}d, %{public}d)",
        GetId(), indexCasted, static_cast<int32_t>(needBuild), static_cast<int32_t>(isCache),
        static_cast<int32_t>(addToRenderTree));

    const auto indexMapped = ConvertFromToIndex(indexCasted);
    auto child = GetChildByIndex(indexMapped);
    if (!child && !needBuild) {
        TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
            "child not found and needBuild==false for index %{public}d, return nullptr.", indexMapped);
        return nullptr;
    }
    if (!child && createItem_) {
        child = createItem_(indexMapped);
    }
    if (!child) {
        TAG_LOGE(AceLogTag::ACE_LAZY_FOREACH,
            "createItem_ failed to create new node for index %{public}d", indexMapped);
        return nullptr;
    }
    node4Index_.Put(indexMapped, child);

    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
        "GetChild returns node %{public}s for index %{public}d", DumpUINode(child).c_str(), indexMapped);

    if (isCache) {
        child->SetJSViewActive(false, !isRepeat_);
        if (!isRepeat_) {
            child->SetParent(WeakClaim(this));
            return child->GetFrameChildByIndex(0, needBuild);
        }
    } else if (addToRenderTree) {
        child->SetActive(true);
    }

    if (isActive_) {
        child->SetJSViewActive(true, !isRepeat_);
    }

    AddChild(child);
    RequestSyncTree();

    auto childNode = child->GetFrameChildByIndex(0, needBuild);
    if (onMoveEvent_) {
        InitDragManager(AceType::DynamicCast<FrameNode>(childNode));
    }
    return childNode;
}

RefPtr<UINode> ArkoalaLazyNode::GetChildByIndex(int32_t index)
{
    auto node = node4Index_.Get(index);
    return node ? node.value() : nullptr;
}

const std::list<RefPtr<UINode>>& ArkoalaLazyNode::GetChildren(bool /* notDetach */) const
{
    if (!children_.empty()) {
        TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH, "GetChildren just returns non-empty children_");
        return children_;
    }
    
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH, "GetChildren rebuild starting ...");
    // can not modify l1_cache while iterating
    // GetChildren is overloaded, can not change it to non-const
    // need to order the child.
    ForEachL1Node([&](int32_t index, const RefPtr<UINode>& node) -> void { children_.emplace_back(node); });

    return children_;
}

void ArkoalaLazyNode::RequestSyncTree()
{
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH, "requesting sync of UI tree");
    UINode::MarkNeedSyncRenderTree();
    children_.clear();
    // re-assemble children_
    PostIdleTask();
}

RefPtr<FrameNode> ArkoalaLazyNode::GetFrameNode(int32_t index)
{
    return AceType::DynamicCast<FrameNode>(GetFrameChildByIndex(index, false, false, false));
}

void ArkoalaLazyNode::OnDataChange(int32_t changeIndex, int32_t count, NotificationType type)
{
    // temp: naive data reset
    for (const auto& [index, node] : node4Index_) {
        if (index >= changeIndex) {
            RemoveChild(node);
        }
    }
    node4Index_.RemoveIf([changeIndex](const uint32_t& k, const auto& _) {
        const auto idx = static_cast<int32_t>(k);
        return idx >= changeIndex;
    });

    auto parent = GetParent();
    int64_t accessibilityId = GetAccessibilityId();
    if (parent) {
        parent->NotifyChange(changeIndex, count, accessibilityId, type);
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }

    // do not call when visible items have not changed
    MarkNeedSyncRenderTree(true);
}

void ArkoalaLazyNode::SetJSViewActive(bool active, bool isLazyForEachNode, bool isReuse)
{
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
        "ArkoalaLazyNode.SetJSViewActive: %{public}s ...", active ? "true" : "false");
    for (const auto& [index, node] : node4Index_) {
        CHECK_NULL_VOID(node);
        node->SetJSViewActive(active);
    }
    isActive_ = active;
}

void ArkoalaLazyNode::BuildAllChildren()
{
    for (int32_t i = 0; i < FrameCount(); i++) {
        GetFrameChildByIndex(i, true, false, false);
    }
}

void ArkoalaLazyNode::PostIdleTask()
{
    if (postUpdateTaskHasBeenScheduled_) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH, "ArkoalaLazyNode[self:%{public}d].PostIdleTask", GetId());
    postUpdateTaskHasBeenScheduled_ = true;
    auto* context = GetContext();
    CHECK_NULL_VOID(context);

    context->AddPredictTask(
        [weak = AceType::WeakClaim(this)](int64_t /* deadline */, bool /* canUseLongPredictTask */) {
        ACE_SCOPED_TRACE("ArkoalaLazyNode.IdleTask");
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->postUpdateTaskHasBeenScheduled_ = false;
        TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH, "idle task calls GetChildren");
        node->GetChildren();
    });
}

void ArkoalaLazyNode::SetOnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    if (onMove && !onMoveEvent_) {
        TAG_LOGI(AceLogTag::ACE_LAZY_FOREACH, "activate onMove");
        InitAllChildrenDragManager(true);
    } else if (!onMove && onMoveEvent_) {
        TAG_LOGI(AceLogTag::ACE_LAZY_FOREACH, "deactivate onMove");
        InitAllChildrenDragManager(false);
    }
    onMoveEvent_ = onMove;
}

void ArkoalaLazyNode::SetOnMoveFromTo(std::function<void(int32_t, int32_t)>&& onMoveFromTo)
{
    onMoveFromTo_ = onMoveFromTo;
}

void ArkoalaLazyNode::SetItemDragEvent(std::function<void(int32_t)>&& onLongPress,
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

void ArkoalaLazyNode::MoveData(int32_t from, int32_t to)
{
    if (from == to) {
        return;
    }
    // move the child in children_ list.
    auto& children = ModifyChildren();
    if (children.empty()) {
        TAG_LOGE(AceLogTag::ACE_LAZY_FOREACH, "children is empty.");
        return;
    }
    auto startIter = children.begin();
    auto startOpt = node4Index_.GetKey(*startIter);
    if (!startOpt.has_value()) {
        TAG_LOGW(AceLogTag::ACE_LAZY_FOREACH, "cannot find start child in items.");
        return;
    }
    int32_t childrenStartIndex = ConvertFromToIndexRevert(startOpt.value());
    auto fromIter = children.begin();
    std::advance(fromIter, from - childrenStartIndex);
    if (fromIter == children.end()) {
        TAG_LOGW(AceLogTag::ACE_LAZY_FOREACH, "from index out of range.");
        return;
    }
    auto child = *fromIter;
    TraversingCheck(child);
    fromIter = children.erase(fromIter);
    std::advance(fromIter, to - from);
    children.insert(fromIter, child);
    
    UpdateMoveFromTo(from, to);
    onMoveFromTo_(from, to);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

int32_t ArkoalaLazyNode::GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool /*isExpanded*/)
{
    if (node == nullptr) {
        TAG_LOGI(AceLogTag::ACE_LAZY_FOREACH, "GetFrameNodeIndex node is null");
        return -1;
    }
    // todo: if repeat and lazyforeach can be distinguished, index can be get directly from node4Index_ map.
    for (const auto& [index, iterNode] : node4Index_) {
        if (!iterNode) {
            continue;
        }
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(iterNode->GetFrameChildByIndex(0, false));
        if (frameNode == node) {
            return ConvertFromToIndexRevert(index);
        }
    }
    return -1;
}

void ArkoalaLazyNode::UpdateMoveFromTo(int32_t from, int32_t to)
{
    if (moveFromTo_) {
        moveFromTo_.value().second = to;
        if (moveFromTo_.value().second == moveFromTo_.value().first) {
            moveFromTo_.reset();
        }
    } else {
        moveFromTo_ = { from, to };
    }
}

void ArkoalaLazyNode::FireOnMove(int32_t from, int32_t to)
{
    // 1. update node4Index_ map.
    UpdateItemsForOnMove();
    // 2. reset moveFromTo_.
    ResetMoveFromTo();
    // 3. call onMoveFromTo_ to notify TS to update its _activeItems.
    // -1 used to reset moveFromTo_ in TS.
    onMoveFromTo_(-1, -1);
    // 4. call base class to fire onMove event defined by user.
    ForEachBaseNode::FireOnMove(from, to);
}

void ArkoalaLazyNode::UpdateItemsForOnMove()
{
    if (!moveFromTo_) {
        return;
    }

    int32_t from = moveFromTo_.value().first;
    int32_t to = moveFromTo_.value().second;
    if (from == to) {
        return;
    }

    int32_t rangeStart = std::min(from, to);
    int32_t rangeEnd = std::max(from, to);
    UniqueValuedMap<int32_t, RefPtr<UINode>, WeakPtr<UINode>::Hash> tempItems = std::move(node4Index_);
    node4Index_.Clear();
    for (const auto& [index, node] : tempItems) {
        if (!node) {
            continue;
        }
        if (index < rangeStart || index > rangeEnd) {
            node4Index_.Put(index, node);
            continue;
        }
        int32_t newIndex = ConvertFromToIndexRevert(index);
        node4Index_.Put(newIndex, node);
    }
}

int32_t ArkoalaLazyNode::ConvertFromToIndex(int32_t index) const
{
    if (!moveFromTo_) {
        return index;
    }
    if (moveFromTo_.value().second == index) {
        return moveFromTo_.value().first;
    }
    if (moveFromTo_.value().first <= index && index < moveFromTo_.value().second) {
        return index + 1;
    }
    if (moveFromTo_.value().second < index && index <= moveFromTo_.value().first) {
        return index - 1;
    }
    return index;
}

int32_t ArkoalaLazyNode::ConvertFromToIndexRevert(int32_t index) const
{
    if (!moveFromTo_) {
        return index;
    }
    if (moveFromTo_.value().first == index) {
        return moveFromTo_.value().second;
    }
    if (moveFromTo_.value().first < index && index <= moveFromTo_.value().second) {
        return index - 1;
    }
    if (moveFromTo_.value().second <= index && index < moveFromTo_.value().first) {
        return index + 1;
    }
    return index;
}

void ArkoalaLazyNode::InitDragManager(const RefPtr<FrameNode>& child)
{
    CHECK_NULL_VOID(child);
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        return;
    }
    auto pattern = child->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitDragManager(AceType::Claim(this));
}

void ArkoalaLazyNode::InitAllChildrenDragManager(bool init)
{
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        return;
    }
    for (const auto& [index, child] : node4Index_) {
        if (!child) {
            continue;
        }
        auto childNode = child->GetFrameChildByIndex(0, false);
        auto listItem = AceType::DynamicCast<FrameNode>(childNode);
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

void ArkoalaLazyNode::ForEachL1Node(
    const std::function<void(int32_t index, const RefPtr<UINode>& node)>& cbFunc) const
{
    for (auto it = node4Index_.begin(); it != node4Index_.end(); ++it) {
        if (const RefPtr<UINode> node = it->second) {
            cbFunc(static_cast<int32_t>(it->first), node);
        }
    }
}

void ArkoalaLazyNode::DumpInfo()
{
    if (isRepeat_) {
        DumpLog::GetInstance().AddDesc("VirtualScroll: true");
    }
}

std::string ArkoalaLazyNode::DumpUINode(const RefPtr<UINode>& node) const
{
    return (node == nullptr)
        ? "UINode: nullptr" : "UINode: " + node->GetTag() + "(" + std::to_string(node->GetId()) + ")";
}
} // namespace OHOS::Ace::NG