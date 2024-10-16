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

#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

// REPEAT
RefPtr<RepeatVirtualScrollNode> RepeatVirtualScrollNode::GetOrCreateRepeatNode(int32_t nodeId, uint32_t totalCount,
    const std::map<std::string, std::pair<bool, uint32_t>>& templateCachedCountMap,
    const std::function<void(uint32_t)>& onCreateNode,
    const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range,
    const std::function<void(int32_t, int32_t)>& onSetActiveRange)
{
    auto node = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScrollNode>(nodeId);
    if (node) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "Found RepeatVirtualScrollNode");
        node->UpdateTotalCount(totalCount);
        return node;
    }
    node = MakeRefPtr<RepeatVirtualScrollNode>(
        nodeId, totalCount, templateCachedCountMap, onCreateNode, onUpdateNode, onGetKeys4Range, onGetTypes4Range,
        onSetActiveRange);

    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

RepeatVirtualScrollNode::RepeatVirtualScrollNode(int32_t nodeId, int32_t totalCount,
    const std::map<std::string, std::pair<bool, uint32_t>>& templateCachedCountMap,
    const std::function<void(uint32_t)>& onCreateNode,
    const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range,
    const std::function<void(int32_t, int32_t)>& onSetActiveRange)
    : ForEachBaseNode(V2::JS_REPEAT_ETS_TAG, nodeId), totalCount_(totalCount),
      caches_(templateCachedCountMap, onCreateNode, onUpdateNode, onGetKeys4Range, onGetTypes4Range),
      onSetActiveRange_(onSetActiveRange),
      postUpdateTaskHasBeenScheduled_(false)
{
}

void RepeatVirtualScrollNode::UpdateTotalCount(uint32_t totalCount)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "UpdateTotalCount: %{public}d", totalCount);
    totalCount_ = totalCount;
}

void RepeatVirtualScrollNode::DoSetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "DoSetActiveChildRange: Repeat(nodeId): %{public}d: start: %{public}d - end: %{public}d; cacheStart: "
        "%{public}d, cacheEnd: %{public}d: ==> keep in L1: %{public}d - %{public}d,",
        GetId(), start, end, cacheStart, cacheEnd, start - cacheStart, end + cacheEnd);

    ACE_SCOPED_TRACE("Repeat.DoSetActiveChildRange start [%d] - end [%d; cacheStart: [%d], cacheEnd: [%d]",
        start, end, cacheStart, cacheEnd);

    // get normalized active range (with positive indices only)
    const auto divisor = (totalCount_ > 0) ? totalCount_ : std::numeric_limits<int>::max();
    const auto nStart = (start - cacheStart + totalCount_) % divisor;
    const auto nEnd = (end + cacheEnd + totalCount_) % divisor;

    // memorize active range
    caches_.SetLastActiveRange(nStart, nEnd);

    // notify TS side
    onSetActiveRange_(nStart, nEnd);

    bool needSync = caches_.RebuildL1([start, end, cacheStart, cacheEnd, this](
        int32_t index, const RefPtr<UINode>& node) -> bool {
        if (node == nullptr) {
            return false;
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(node->GetFrameChildByIndex(0, true));
        if (!frameNode) {
            return false;
        }
        if (CheckNode4IndexInL1(index, start, end, cacheStart, cacheEnd, frameNode)) {
            // keep in Repeat L1
            TAG_LOGD(AceLogTag::ACE_REPEAT, "...in visible, index %{public}d -> nodeId %{public}d: keep in Repeat L1",
                static_cast<int32_t>(index), frameNode->GetId());
            return true;
        }
        TAG_LOGD(AceLogTag::ACE_REPEAT, "...out of visible, index %{public}d -> nodeId %{public}d: SetActive(false), "
            "detach, move to spare items L2", index, frameNode->GetId());

        // move active node into L2 cached. check transition flag.
        if (node->OnRemoveFromParent(true)) {
            // OnRemoveFromParent returns true means the child can be removed from tree immediately.
            RemoveDisappearingChild(node);
        } else {
            AddDisappearingChild(node);
        }

        return false;
    });
    if (needSync) {
        UINode::MarkNeedSyncRenderTree(false);
        children_.clear();
        PostIdleTask();
    }
}

bool RepeatVirtualScrollNode::CheckNode4IndexInL1(int32_t index, int32_t start, int32_t end,
    int32_t cacheStart, int32_t cacheEnd, RefPtr<FrameNode>& frameNode)
{
    if (((start <= index) && (index <= end)) || ((end < start) && (index <= end || start <= index))) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "...in range: index %{public}d -> nodeId %{public}d: SetActive(true)",
            index, static_cast<int32_t>(frameNode->GetId()));
        frameNode->SetActive(true);
    } else {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "...out of range: index %{public}d -> nodeId %{public}d: SetActive(false)",
            index, frameNode->GetId());
        frameNode->SetActive(false);
    }

    auto totalCount = static_cast<int32_t>(totalCount_);
    if ((start - cacheStart <= index) && (index <= end + cacheEnd)) {
        return true;
    }
    if (isLoop_) {
        if (((end < start) && (start - cacheStart <= index || index <= end + cacheEnd)) ||
            ((start - cacheStart < 0) && (index >= start - cacheStart + totalCount)) ||
            ((end + cacheEnd >= totalCount) && (index <= end + cacheEnd - totalCount))) {
            return true;
        }
    }
    return false;
}

void RepeatVirtualScrollNode::DropFromL1(const std::string& key)
{
    RefPtr<UINode> node = caches_.DropFromL1(key);
    if (node == nullptr) {
        return;
    }

    auto frameNode = AceType::DynamicCast<FrameNode>(node->GetFrameChildByIndex(0, true));
    if (!frameNode) {
        frameNode->SetActive(false);
    }
    // move active node into L2 cached.
    // check transition flag.
    if (node->OnRemoveFromParent(true)) {
        // OnRemoveFromParent returns true means the child can be removed from tree immediately.
        RemoveDisappearingChild(node);
    } else {
        // else move child into disappearing children, skip syncing render tree
        AddDisappearingChild(node);
    }

    UINode::MarkNeedSyncRenderTree(false);
    children_.clear();
    // re-assemble children_
    PostIdleTask();
}

void RepeatVirtualScrollNode::DoSetActiveChildRange(
    const std::set<int32_t>& activeItems, const std::set<int32_t>& cachedItems, int32_t baseIndex)
{
    // Notify TS side. Verify line below when DoSetActiveChildRange() will start to be used.
    // Call onSetActiveRange_ here;

    bool needSync =
        caches_.RebuildL1([&activeItems, &cachedItems, baseIndex, this](int32_t index, RefPtr<UINode> node) -> bool {
            if (node == nullptr) {
                return false;
            }
            auto frameNode = AceType::DynamicCast<FrameNode>(node->GetFrameChildByIndex(0, true));
            if (!frameNode) {
                return false;
            }
            if (activeItems.find(index + baseIndex) != activeItems.end()) {
                frameNode->SetActive(true);
                return true;
            } else {
                frameNode->SetActive(false);
            }
            if (cachedItems.find(index + baseIndex) != cachedItems.end()) {
                return true;
            }
            if (node->OnRemoveFromParent(true)) {
                RemoveDisappearingChild(node);
            } else {
                AddDisappearingChild(node);
            }

            return false;
        });
    if (needSync) {
        UINode::MarkNeedSyncRenderTree(false);
        children_.clear();
        PostIdleTask();
    }
}

void RepeatVirtualScrollNode::UpdateRenderState(bool visibleItemsChanged)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "UpdateRenderState triggered by Repeat rerender: nodeId: %{public}d, visibleItemsChanged: %{public}d",
        static_cast<int32_t>(GetId()), visibleItemsChanged);

    if (visibleItemsChanged) {
        // empty the cache index -> key
        // C++ will need to ask all new keys from JS side
        caches_.InvalidateKeyAndTTypeCaches();
        children_.clear();

        if (auto frameNode = GetParentFrameNode()) {
            frameNode->ChildrenUpdatedFrom(0);
        }
    } else {
        auto lastIndexInActiveRange = caches_.GetLastActiveRange().second;
        TAG_LOGD(AceLogTag::ACE_REPEAT, "lastIndexInActiveRange:%{public}d", lastIndexInActiveRange);

        if (auto frameNode = GetParentFrameNode()) {
            frameNode->ChildrenUpdatedFrom(lastIndexInActiveRange + 1);
        }
    }

    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

// STATE_MGMT_NOTE: added
// index N-th item
// needBuild: true - if found in cache, then return, if not in cache then return newly build
//            false: - if found in cache, then return, if not found in cache then return nullptr
// isCache: true indicates prebuild item (only used by List/Grid/Waterflow, this item should go to L2 cache,
//          do not add to the tree,
//          isCache==false this item is for display or near display area
// addToRenderTree: true  - set it to active state, call SetActive
RefPtr<UINode> RepeatVirtualScrollNode::GetFrameChildByIndex(
    uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "index:%{public}d", static_cast<int32_t>(index));

    ACE_SCOPED_TRACE("Repeat.GetFrameChildByIndex index[%d], needBuild[%d] isCache[%d] "
                     "addToRenderTree[%d]",
        index, static_cast<int32_t>(needBuild), static_cast<int32_t>(isCache), static_cast<int32_t>(addToRenderTree));

    // whether child is reused or created
    bool isChildReused = true;

    const auto& key = caches_.GetKey4Index(index, true);
    if (!key) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to get key for %{public}d", index);
        return nullptr;
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "nodeId: %{public}d: GetFrameChildByIndex(index: %{public}d, "
        "key %{public}s, needBuild:  %{public}d, isCache: %{public}d, "
        "addToRenderTree: %{public}d) ...", static_cast<int32_t>(GetId()),
        static_cast<int32_t>(index), key->c_str(), static_cast<int32_t>(needBuild),
        static_cast<int32_t>(isCache), static_cast<int32_t>(addToRenderTree));

    // search if index -> key -> Node exist
    // will update the same key item if needs.
    auto node4Index = GetFromCaches(index);
    if (!node4Index && !needBuild) {
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "index %{public}d -> key '%{public}s' not in caches && needBuild==false, "
            "GetFrameChildByIndex returns nullptr .",
            static_cast<int32_t>(index), key->c_str());
        return nullptr;
    }

    // node4Index needs to be created or updated on JS side
    if (!node4Index) {
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "index %{public}d -> key '%{public}s' not in caches && needBuild==true, calling "
            "CreateOrUpdateFrameChild4Index ....",
            static_cast<int32_t>(index), key->c_str());

        // ask TS to update a Node, if possible
        // if no suitable node, request to crete a new node
        node4Index = caches_.UpdateFromL2(index);
        if (!node4Index) {
            node4Index = caches_.CreateNewNode(index);
            isChildReused = false;
        }

        if (!node4Index) {
            TAG_LOGW(AceLogTag::ACE_REPEAT, "index %{public}d -> key '%{public}s' not in caches and failed to build.",
                static_cast<int32_t>(index), key->c_str());
            return nullptr;
        }
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "index %{public}d  -> key '%{public}s', needBuild==true, node: %{public}s .",
        static_cast<int32_t>(index), key->c_str(), caches_.DumpUINode(node4Index).c_str());

    if (isActive_) {
        node4Index->SetJSViewActive(true);
    }

    if (addToRenderTree && !isCache) {
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "index %{public}d isCache==false setActive and adding to L1 cache",
            static_cast<int32_t>(index));
        node4Index->SetActive(true);
    }

    if (caches_.IsInL1Cache(key.value())) {
        return node4Index->GetFrameChildByIndex(0, needBuild);
    }

    // if the item was in L2 cache, move item to L1 cache.
    caches_.AddKeyToL1(key.value(), isChildReused);

    if (node4Index->GetDepth() != GetDepth() + 1) {
        node4Index->SetDepth(GetDepth() + 1);
    }
    // attach to repeat node and pass context to it.
    node4Index->SetParent(WeakClaim(this));
    if (IsOnMainTree()) {
        node4Index->AttachToMainTree(false, GetContext());
    }

    MarkNeedSyncRenderTree();
    children_.clear();
    // re-assemble children_
    PostIdleTask();

    auto childNode = node4Index->GetFrameChildByIndex(0, needBuild);
    if (childNode && onMoveEvent_) {
        InitDragManager(AceType::DynamicCast<FrameNode>(childNode));
    }

    // this is new node or node from L2 cache
    if (childNode) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "index %{public}d, its child is %{public}d, returning child.",
            static_cast<int32_t>(index), static_cast<int32_t>(childNode->GetId()));
    }

    return childNode;
}

int32_t RepeatVirtualScrollNode::GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool /*isExpanded*/)
{
    return caches_.GetFrameNodeIndex(node);
}

const std::list<RefPtr<UINode>>& RepeatVirtualScrollNode::GetChildren(bool /*notDetach*/) const
{
    if (!children_.empty()) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "GetChildren just returns non-empty children_");
        return children_;
    }

    // can not modify l1_cache while iterating
    // GetChildren is overloaded, can not change it to non-const
    // need to order the child.
    std::map<int32_t, RefPtr<UINode>> children;
    caches_.ForEachL1IndexUINode(
        [&children](int32_t index, const RefPtr<UINode>& node) -> void { children.emplace(index, node); });
    for (const auto& [index, child] : children) {
        const_cast<RepeatVirtualScrollNode*>(this)->RemoveDisappearingChild(child);
        children_.emplace_back(child);
    }
    return children_;
}

void RepeatVirtualScrollNode::UpdateChildrenFreezeState(bool isFreeze, bool isForceUpdateFreezeVaule)
{
    const auto& allChildren = caches_.GetAllNodes();
    for (auto& child : allChildren) {
        if (child.second.item) {
            child.second.item->SetFreeze(isFreeze);
        }
    }
}

void RepeatVirtualScrollNode::RecycleItems(int32_t from, int32_t to)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "Repeat(%{public}d: Layout prediction instructs to move Repeat items from index %{public}d up to smaller than "
        "%{public}d to the reusable items cache",
        static_cast<int32_t>(GetId()), from - startIndex_, to - startIndex_);

    offscreenItems_.from = from;
    offscreenItems_.to = to;
    for (auto i = from; i < to; i++) {
        if (i >= startIndex_ && i < startIndex_ + static_cast<int32_t>(totalCount_)) {
            caches_.RecycleItemsByIndex(i - startIndex_);
        }
    }
}

void RepeatVirtualScrollNode::SetNodeIndexOffset(int32_t start, int32_t /*count*/)
{
    startIndex_ = start;
}

int32_t RepeatVirtualScrollNode::FrameCount() const
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "FrameCount returns %{public}d",
        static_cast<int32_t>(totalCount_));
    return totalCount_;
}

void RepeatVirtualScrollNode::PostIdleTask()
{
    if (postUpdateTaskHasBeenScheduled_) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT, "Posting idle task");
    postUpdateTaskHasBeenScheduled_ = true;
    auto* context = GetContext();
    CHECK_NULL_VOID(context);

    context->AddPredictTask([weak = AceType::WeakClaim(this)](int64_t /*deadline*/, bool /*canUseLongPredictTask*/) {
        ACE_SCOPED_TRACE("Repeat.IdleTask");
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->postUpdateTaskHasBeenScheduled_ = false;
        TAG_LOGD(AceLogTag::ACE_REPEAT, "idle task calls GetChildren");
        node->GetChildren();
        node->caches_.Purge();
        TAG_LOGD(AceLogTag::ACE_REPEAT, " ============ after caches.purge ============= ");
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpL1().c_str());
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpL2().c_str());
    });
}

void RepeatVirtualScrollNode::OnConfigurationUpdate(const ConfigurationChange& configurationChange)
{
    if ((configurationChange.colorModeUpdate || configurationChange.fontUpdate)) {
        const auto& children = caches_.GetAllNodes();
        for (const auto& [key, child] : children) {
            if (child.item) {
                child.item->UpdateConfigurationUpdate(configurationChange);
            }
        }
    }
}

void RepeatVirtualScrollNode::SetOnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    // To do
}

// FOREAch
void RepeatVirtualScrollNode::MoveData(int32_t from, int32_t to) {}

RefPtr<FrameNode> RepeatVirtualScrollNode::GetFrameNode(int32_t index)
{
    return AceType::DynamicCast<FrameNode>(GetFrameChildByIndex(index, false, false));
}

void RepeatVirtualScrollNode::InitDragManager(const RefPtr<UINode>& child)
{
    // To do
}

void RepeatVirtualScrollNode::InitAllChildrenDragManager(bool init)
{
    // To do
}

} // namespace OHOS::Ace::NG
