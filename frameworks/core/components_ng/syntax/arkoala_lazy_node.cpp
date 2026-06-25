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

#include "base/log/dump_log.h"
#include "core/components_ng/syntax/arkoala_lazy_node.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/syntax/lazy_for_each_utils.h"

namespace OHOS::Ace::NG {
ArkoalaLazyNode::ArkoalaLazyNode(int32_t nodeId, bool isRepeat) : ForEachBaseNode(
    isRepeat ? V2::JS_REPEAT_ETS_TAG : V2::JS_LAZY_FOR_EACH_ETS_TAG, nodeId), isRepeat_(isRepeat) {}

ArkoalaLazyNode::~ArkoalaLazyNode()
{
    UnregisterWindowStateChangedCallback();
    UnregisterMemoryLevelChangedCallback();
}

void ArkoalaLazyNode::RegisterArkoalaLazyNode()
{
    auto nodePtr = AceType::Claim(this);
    ElementRegister::GetInstance()->AddUINode(nodePtr);
}

void ArkoalaLazyNode::DoSetActiveChildRange(
    int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
    ACE_SYNTAX_SCOPED_TRACE(
        "ArkoalaLazyNode[self:%d].DoSetActiveChildRange start[%d] end[%d] cacheStart[%d] cacheEnd[%d] showCache[%d]",
        GetId(), start, end, cacheStart, cacheEnd, static_cast<int32_t>(showCache));
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH, "ArkoalaLazyNode[self:%{public}d].DoSetActiveChildRange"
        "(%{public}d, %{public}d, %{public}d, %{public}d, %{public}d)",
        GetId(), start, end, cacheStart, cacheEnd, static_cast<int32_t>(showCache));
    if (showCache) {
        start -= cacheStart;
        end += cacheEnd;
        cacheStart = 0;
        cacheEnd = 0;
    }
    const ActiveRangeParam newParam = { start, end, cacheStart, cacheEnd };
    if (newParam == activeRangeParam_) {  // active range not changed, return directly.
        return;
    }
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
        "TRACE DoSetActiveChildRange(%{public}d, %{public}d, %{public}d, %{public}d, %{public}d)",
        start, end, cacheStart, cacheEnd, static_cast<int32_t>(showCache));
    SetNeedBuildAll(false);
    activeRangeParam_ = newParam;
    if (updateRange_) {
        // trigger TS-side
        updateRange_(start, end, cacheStart, cacheEnd, isLoop_);
    }
    // rebuild children of arkoalaLazyNode according to new active range.
    RebuildCache();
}

void ArkoalaLazyNode::RebuildCache()
{
    std::list<RefPtr<UINode>> toRemove;
    for (const auto& [index, node] : node4Index_) {
        CHECK_NULL_CONTINUE(node);
        const auto indexMapped = ConvertFromToIndexRevert(index);
        // range of visible items
        const bool isInActiveRange = IsInActiveRange(indexMapped, activeRangeParam_);
        // range of cached items
        const bool isInCacheRange = IsInCacheRange(indexMapped, activeRangeParam_);
        TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
            "isInActiveRange & isInCacheRange -> [%{public}d, %{public}d] for index %{public}d",
            static_cast<int32_t>(isInActiveRange), static_cast<int32_t>(isInCacheRange), indexMapped);

        if (!isInCacheRange || (!isRepeat_ && !isInActiveRange)) { // LazyForEach need to remove inactive nodes
            if (node->OnRemoveFromParent(true)) { // can be removed from tree immediately.
                RemoveDisappearingChild(node);
            } else {
                AddDisappearingChild(node);
            }
        }
        node->SetActive(isInActiveRange);
        if (isRepeat_) {
            // trigger onReuse/onRecycle
            UpdateIsCache(node, isInCacheRange);
        }
    }

    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH, "RebuildCache DONE. Cache nodes count: %{public}zu", node4Index_.Size());
    RequestSyncTree(); // order a resync from layout
}

void ArkoalaLazyNode::PurgeNode()
{
    std::vector<int32_t> removingIndex;
    for (const auto& [index, node] : node4Index_) {
        const auto indexMapped = ConvertFromToIndexRevert(index);
        if (!IsInCacheRange(indexMapped, activeRangeParam_)) {
            removingIndex.emplace_back(index);
            if (!isRepeat_ && options_.releaseStrategy == LazyForEachReleaseStrategy::PROGRESSIVE) {
                removingNodeList_.push_back(node);
            }
        }
    }
    for (auto i: removingIndex) {
        node4Index_.Remove(i);
    }
}

void ArkoalaLazyNode::RemovingExpiringItem(int64_t deadline)
{
    // step 1: check removingNodeList_ if empty
    if (removingNodeList_.empty()) {
        return;
    }
    // step 2: release nodes while enough time for average release
    int64_t startTimeStamp = 0;
    int64_t endTimeStamp = 0;
    int64_t averageTime = 0;
    int64_t totalTime = 0;
    int32_t count = 0;
    do {
        startTimeStamp = GetSysTimestamp();
        auto ite = removingNodeList_.begin();
        removingNodeList_.erase(ite);
        endTimeStamp = GetSysTimestamp();
        count++;
        totalTime += endTimeStamp - startTimeStamp;
        averageTime = totalTime / count;
    } while (!removingNodeList_.empty() && deadline - endTimeStamp > averageTime);
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
    return GetFrameChildByIndexImpl(indexMapped, needBuild, isCache, addToRenderTree);
}

RefPtr<UINode> ArkoalaLazyNode::GetFrameChildByIndexImpl(
    int32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    auto child = GetChildByIndex(index);
    if (!child && !needBuild) {
        TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
            "child not found and needBuild==false for index %{public}d, return nullptr.", index);
        return nullptr;
    }
    if (!child && createItem_) {
        child = createItem_(index);
    }
    if (!child) {
        TAG_LOGE(AceLogTag::ACE_LAZY_FOREACH, "createItem_ failed to create new node for index %{public}d", index);
        return nullptr;
    }
    node4Index_.Put(index, child);
    sparedIdx_.insert(index);

    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
        "GetChild returns node %{public}s for index %{public}d", DumpUINode(child).c_str(), index);

    if (isCache) {
        child->SetJSViewActive(false, !isRepeat_);
        if (!isRepeat_) {
            child->SetParent(WeakClaim(this));
            bool enableCustomComponentFreeze = LazyForEachUtils::GetEnableCustomComponentFreeze();
            if (options_.customComponentFreezeMode == LazyForEachCustomComponentFreezeMode::DISABLED) {
                enableCustomComponentFreeze = false;
            } else if (options_.customComponentFreezeMode == LazyForEachCustomComponentFreezeMode::ENABLED) {
                enableCustomComponentFreeze = true;
            }
            return child->GetFrameChildByIndex(0, needBuild, enableCustomComponentFreeze);
        }
    } else if (addToRenderTree) {
        child->SetActive(true);
    }
    if (isActive_) {
        child->SetJSViewActive(true, !isRepeat_);
    }

    if (child->GetDepth() != GetDepth() + 1) {
        child->SetDepth(GetDepth() + 1);
    }
    // attach to syntax node and pass context to it.
    child->SetParent(WeakClaim(this));
    if (IsOnMainTree()) {
        child->AttachToMainTree(false, GetContext());
    }
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
    // can not modify l1_cache while iterating
    // GetChildren is overloaded, can not change it to non-const
    // need to order the child.
    if (!moveFromTo_) {
        ForEachL1Node([&](int32_t index, const RefPtr<UINode>& node) -> void { children_.emplace_back(node); });
    } else {
        ForEachL1NodeWithOnMove([&](const RefPtr<UINode>& node) -> void { children_.emplace_back(node); });
    }
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH, "GetChildren rebuilt children_, size=%{public}zu", children_.size());
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
    bool needSync = false;
    for (const auto& [index, node] : node4Index_) {
        if (index >= changeIndex) {
            if (node->OnRemoveFromParent(true)) { // can be removed from tree immediately.
                RemoveDisappearingChild(node);
            } else {
                AddDisappearingChild(node);
            }
            needSync = true;
        }
    }
    node4Index_.RemoveIf([changeIndex](const uint32_t& k, const auto& _) {
        const auto idx = static_cast<int32_t>(k);
        return idx >= changeIndex;
    });
    if (needSync) {  // order a resync from layout
        RequestSyncTree();
    }

    auto parent = GetParentFrameNode();
    int64_t accessibilityId = GetAccessibilityId();
    if (parent) {
        if (isRepeat_ && parent->GetHostTag() == V2::LIST_ETS_TAG) {
            parent->NotifyChange(changeIndex, count, accessibilityId, NotificationType::START_AND_END_CHANGE_POSITION);
        } else if (parent->GetHostTag() == V2::SWIPER_ETS_TAG) {
            parent->NotifyChange(changeIndex, count, accessibilityId, NotificationType::START_AND_END_CHANGE_POSITION);
        } else {
            parent->NotifyChange(changeIndex, count, accessibilityId, type);
        }
        MarkNeedSyncRenderTree(true);
        MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
}

void ArkoalaLazyNode::SetJSViewActive(bool active, bool isLazyForEachNode, bool isReuse, bool suppressActiveLifecycle)
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
    children_.clear();
    for (const auto& [index, node] : node4Index_) {
        if (node) {
            RemoveDisappearingChild(node);
            children_.push_back(node);
        }
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
        [weak = AceType::WeakClaim(this)](int64_t deadline, bool /* canUseLongPredictTask */) {
        ACE_SCOPED_TRACE("ArkoalaLazyNode.IdleTask");
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->postUpdateTaskHasBeenScheduled_ = false;
        TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH, "idle task calls GetChildren");
        node->GetChildren();
        node->PurgeNode();
        node->RemovingExpiringItem(deadline);
        if (!node->removingNodeList_.empty()) {
            node->PostIdleTask();
        }
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

void ArkoalaLazyNode::MoveData(int32_t from, int32_t to, bool isNeedUpdate)
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
    if (isNeedUpdate) {
        if (auto frameNode = GetParentFrameNode()) {
            frameNode->ChildrenUpdatedFrom(std::min(from, to));
        }
    }
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
    if (parentNode->GetTag() != V2::LIST_ETS_TAG && parentNode->GetTag() != V2::GRID_ETS_TAG) {
        return;
    }
    if (parentNode->GetTag() == V2::LIST_ETS_TAG) {
        auto pattern = child->GetPattern<ListItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->InitDragManager(AceType::Claim(this));
    } else if (parentNode->GetTag() == V2::GRID_ETS_TAG) {
        auto pattern = child->GetPattern<GridItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->InitDragManager(AceType::Claim(this));
    }
}

void ArkoalaLazyNode::InitAllChildrenDragManager(bool init)
{
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG && parentNode->GetTag() != V2::GRID_ETS_TAG) {
        return;
    }
    for (const auto& [index, child] : node4Index_) {
        if (!child) {
            continue;
        }
        auto childNode = child->GetFrameChildByIndex(0, false);
        auto item = AceType::DynamicCast<FrameNode>(childNode);
        if (!item) {
            continue;
        }

        if (parentNode->GetTag() == V2::LIST_ETS_TAG) {
            auto pattern = item->GetPattern<ListItemPattern>();
            if (!pattern) {
                continue;
            }
            if (init) {
                pattern->InitDragManager(AceType::Claim(this));
            } else {
                pattern->DeInitDragManager();
            }
        } else if (parentNode->GetTag() == V2::GRID_ETS_TAG) {
            auto pattern = item->GetPattern<GridItemPattern>();
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
}

bool ArkoalaLazyNode::IsInActiveRange(int32_t index, const ActiveRangeParam& param) const
{
    if (isLoop_ && param.start > param.end) {
        return index >= param.start || index <= param.end;
    }
    return index >= param.start && index <= param.end;
}

bool ArkoalaLazyNode::IsInCacheRange(int32_t index, const ActiveRangeParam& param) const
{
    const auto total = totalCount_;
    if (total <= 0 || index < 0 || index >= total) {
        return false;
    }

    // calculate cache boundaries
    int32_t cacheStartBound = param.start - param.cacheStart;
    int32_t cacheEndBound = param.end + param.cacheEnd;

    if (!isLoop_) {
        // non-loop mode: simple calmping
        int32_t actualStart = std::max(0, cacheStartBound);
        int32_t actualEnd = std::min(total - 1, cacheEndBound);
        return index >= actualStart && index <= actualEnd;
    } else {
        // loop mode
        auto normalize = [total](int32_t idx) -> int32_t {
            return (idx % total + total) % total;
        };

        int32_t normIndex = normalize(index);
        int32_t normStart = normalize(param.start);
        int32_t normEnd = normalize(param.end);

        // check if visible region is wrapped
        bool isWrapped = normStart > normEnd;
        if (isWrapped) {
            // wrapped case: visible region is [start, totalCount-1] + [0, end]
            // cache region is [start-cacheStart, totalCount-1] + [0, end+cacheEnd]
            // full coverage condition: cache regions connect or overlap
            if (cacheStartBound <= cacheEndBound + 1) {
                return true;
            }
        } else {
            // normal case: check if cache region covers entire list
            if (cacheEndBound - cacheStartBound + 1 >= total) {
                return true;
            }
        }

        // non-full coverage case
        int32_t normCacheStart = normalize(cacheStartBound);
        int32_t normCacheEnd = normalize(cacheEndBound);
        if (normCacheStart <= normCacheEnd) {
            // single continuous region
            return normIndex >= normCacheStart && normIndex <= normCacheEnd;
        } else {
            // two regions: [0, normCacheEnd] + [normCacheStart, totalCount-1]
            return normIndex <= normCacheEnd || normIndex >= normCacheStart;
        }
    }
}

void ArkoalaLazyNode::ForEachL1Node(
    const std::function<void(int32_t index, const RefPtr<UINode>& node)>& cbFunc) const
{
    for (auto it = node4Index_.begin(); it != node4Index_.end(); ++it) {
        const auto index = it->first;
        const RefPtr<UINode> node = it->second;
        CHECK_NULL_CONTINUE(node);
        if (needBuildAll_ || isRepeat_ || IsInActiveRange(index, activeRangeParam_)) {
            // LazyForEach only return nodes in container
            cbFunc(index, node);
        }
    }
}

void ArkoalaLazyNode::ForEachL1NodeWithOnMove(const std::function<void(const RefPtr<UINode>& node)>& cbFunc) const
{
    std::map<int32_t, int32_t> mappedNode4Index;
    for (auto it = node4Index_.begin(); it != node4Index_.end(); ++it) {
        const auto index = it->first;
        const auto mappedIndex = ConvertFromToIndexRevert(index);
        if (needBuildAll_ || isRepeat_ || IsInActiveRange(mappedIndex, activeRangeParam_)) {
            // LazyForEach only return nodes in container
            mappedNode4Index.emplace(mappedIndex, index);
        }
    }
    for (const auto& iter : mappedNode4Index) {
        const auto index = iter.second;
        const auto nodePtr = node4Index_.Get(index);
        if (nodePtr) {
            cbFunc(nodePtr.value());
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

void ArkoalaLazyNode::OnWindowShow()
{
    ScheduleRestoreCacheTask();
}

void ArkoalaLazyNode::OnWindowHide()
{
    CleanCache(true);
}

void ArkoalaLazyNode::OnNotifyMemoryLevel(int32_t level)
{
    if (level == MEMORY_LEVEL_LOW || level == MEMORY_LEVEL_CRITICAL) {
        CleanCache(false);
    }
}

void ArkoalaLazyNode::RegisterWindowStateChangedCallback()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddWindowStateChangedCallback(GetId());
}

void ArkoalaLazyNode::UnregisterWindowStateChangedCallback()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->RemoveWindowStateChangedCallback(GetId());
}

void ArkoalaLazyNode::RegisterMemoryLevelChangedCallback()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddNodesToNotifyMemoryLevel(GetId());
}

void ArkoalaLazyNode::UnregisterMemoryLevelChangedCallback()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->RemoveNodesToNotifyMemoryLevel(GetId());
}

bool ArkoalaLazyNode::CheckParentFrameNodeVisibility()
{
    auto parent = GetParentFrameNode();
    CHECK_NULL_RETURN(parent, false);
    auto context = GetContext();
    CHECK_NULL_RETURN(context, false);
    return !(parent->IsDisappearOrNoVisibleArea(context->GetVsyncTime()));
}

void ArkoalaLazyNode::ScheduleCleanCacheTask()
{
    pendingRestoreCache_ = false;
    CHECK_EQUAL_VOID(pendingCleanCache_, true);
    pendingCleanCache_ = true;
    cacheTaskPostTime_ = GetSysTimestamp();
}

void ArkoalaLazyNode::ScheduleRestoreCacheTask()
{
    pendingCleanCache_ = false;
    CHECK_EQUAL_VOID(pendingRestoreCache_, true);
    pendingRestoreCache_ = true;
    cacheTaskPostTime_ = GetSysTimestamp();
    PostMemOptTask();
}

void ArkoalaLazyNode::TryExecuteScheduledCacheTask()
{
    CHECK_EQUAL_VOID(pendingCleanCache_ || pendingRestoreCache_, false);
    auto timeStamp = GetSysTimestamp();
    CHECK_EQUAL_VOID(timeStamp - cacheTaskPostTime_ < CACHE_TASK_DELAY_TIME, true);
    if (pendingCleanCache_) {
        CHECK_EQUAL_VOID(timeStamp - setActiveRangeTime_ < CACHE_TASK_DELAY_TIME, true);
        CleanCache(false);
    } else if (pendingRestoreCache_) {
        if (!CheckParentFrameNodeVisibility()) {
            pendingCleanCache_ = false;
            pendingRestoreCache_ = false;
            return;
        }
        RestoreCache();
    }
}

void ArkoalaLazyNode::CleanCache(bool syncClean)
{
    if (isRepeat_ &&
        repeatMemoryOptimizationStrategy_ == RepeatMemoryOptimizationStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION) {
        clearCache_();
        return;
    }
    if (!isRepeat_ && options_.memOptStrategy == LazyForEachMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION) {
        auto weak = AceType::WeakClaim(this);
        const auto activeRange = activeRangeParam_;
        // delete nodes in preload area
        node4Index_.RemoveIf([weak, activeRange](const uint32_t& k, const auto& _) {
            auto node = weak.Upgrade();
            CHECK_NULL_RETURN(node, false);
            auto willRelease = !node->IsInActiveRange(static_cast<int32_t>(k), activeRange);
            if (willRelease) {
                node->releaseItemByIndex_(k);
            }
            return willRelease;
        });
        if (updateRange_) {
            // trigger TS-side
            updateRange_(activeRangeParam_.start, activeRangeParam_.end, 0, 0, isLoop_);
        }
    }
    
    pendingCleanCache_ = false;
    pendingRestoreCache_ = false;
    if (!syncClean) {
        PostIdleTask();
    }
}

void ArkoalaLazyNode::RestoreCache()
{
    if (!isRepeat_ &&
        options_.memOptStrategy == LazyForEachMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION) {
        for (auto i = 0;i < totalCount_; i++) {
            if (IsInCacheRange(i, activeRangeParam_) && !IsInActiveRange(i, activeRangeParam_)) {
                GetFrameChildByIndex(i, true, true, false);
            }
        }
        return;
    }
    if (isRepeat_ &&
        repeatMemoryOptimizationStrategy_ == RepeatMemoryOptimizationStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION) {
        for (auto i: sparedIdx_) {
            if (!IsInCacheRange(i, activeRangeParam_)) {
                GetFrameChildByIndex(i, true, true, false);
            }
        }
        if (updateRange_) {
            // trigger TS-side
            updateRange_(activeRangeParam_.start, activeRangeParam_.end, activeRangeParam_.cacheStart,
                activeRangeParam_.cacheEnd, isLoop_);
        }
    }
    pendingCleanCache_ = false;
    pendingRestoreCache_ = false;
    PostIdleTask();
}

void ArkoalaLazyNode::SetNeedPrebuild(bool needPrebuild)
{
    needPreBuild_ = needPrebuild;
}

bool ArkoalaLazyNode::GetNeedPrebuild()
{
    return needPreBuild_;
}

void ArkoalaLazyNode::SetParentVisibility(bool visibility)
{
    isParentVisible_ = visibility;
}
bool ArkoalaLazyNode::GetParentVisibility()
{
    return isParentVisible_;
}

void ArkoalaLazyNode::PostMemOptTask()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    const uint32_t delay = 1000; // 1 seconds in milliseconds
    auto weakNode = AceType::WeakClaim(this);
    taskExecutor->PostDelayedTask(
        [weakNode]() {
            auto node = weakNode.Upgrade();
            CHECK_NULL_VOID(node);
            auto visible = node->CheckParentFrameNodeVisibility();
            if (visible != node->GetParentVisibility()) {
                node->SetParentVisibility(visible);
                visible ? node->ScheduleRestoreCacheTask() : node->ScheduleCleanCacheTask();
            }
            node->TryExecuteScheduledCacheTask();
            node->PostMemOptTask();
        },
        TaskExecutor::TaskType::UI,
        delay,
        "LazyForEachMemOptTask");
}

void ArkoalaLazyNode::SetRepeatMemoryOptimizationStrategy(int32_t strategy)
{
    if (!isRepeat_) {
        return;
    }
    repeatMemoryOptimizationStrategy_ = strategy == 1?
        RepeatMemoryOptimizationStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION: RepeatMemoryOptimizationStrategy::DEFAULT;
    if (options_.memOptStrategy == LazyForEachMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION ||
        repeatMemoryOptimizationStrategy_ == RepeatMemoryOptimizationStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION) {
        RegisterWindowStateChangedCallback();
        RegisterMemoryLevelChangedCallback();
        PostMemOptTask();
    }
}
} // namespace OHOS::Ace::NG