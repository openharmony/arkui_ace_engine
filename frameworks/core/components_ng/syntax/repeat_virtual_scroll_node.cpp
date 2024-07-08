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

#include <cstdint>
#include <functional>
#include <utility>

#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

// REPEAT
RefPtr<RepeatVirtualScrollNode> RepeatVirtualScrollNode::GetOrCreateRepeatNode(int32_t nodeId, uint32_t totalCount,
    const std::map<std::string, uint32_t>& templateCachedCountMap, const std::function<void(uint32_t)>& onCreateNode,
    const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range)
{
    auto node = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScrollNode>(nodeId);
    if (node) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "Found RepeatVirtualScrollNode");
        node->UpdateTotalCount(totalCount);
        return node;
    }
    node = MakeRefPtr<RepeatVirtualScrollNode>(
        nodeId, totalCount, templateCachedCountMap, onCreateNode, onUpdateNode, onGetKeys4Range, onGetTypes4Range);

    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

RepeatVirtualScrollNode::RepeatVirtualScrollNode(int32_t nodeId, int32_t totalCount,
    const std::map<std::string, uint32_t>& templateCachedCountMap, const std::function<void(uint32_t)>& onCreateNode,
    const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range)
    : ForEachBaseNode(V2::JS_REPEAT_ETS_TAG, nodeId), totalCount_(totalCount),
      caches_(templateCachedCountMap, onCreateNode, onUpdateNode, onGetKeys4Range, onGetTypes4Range),
      postUpdateTaskHasBeenScheduled_(false)
{
    // no preduct task scheduled
}

void RepeatVirtualScrollNode::DoSetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "DoSetActiveChildRange: nodeId: %{public}d: start: %{public}d, end: %{public}d, cacheStart: %{public}d, "
        "cacheEnd: %{public}d",
        GetId(), start, end, cacheStart, cacheEnd);

    // STATE_MGMT_NOTE: Guido REview: I believe should use cacheStart and cacheEnd here, not start and end
    // memorize active range
    caches_.SetLastActiveRange(static_cast<uint32_t>(start), static_cast<uint32_t>(end));

    // STATE_MGMT_NOTE: Guido REview: I believe should use cacheStart and cacheEnd here, not start and end
    bool needSync =
        caches_.RebuildL1([start, end, cacheStart, cacheEnd, this](int32_t index, const RefPtr<UINode>& node) -> bool {
            if (node == nullptr) {
                return false;
            }
            // Get the first child of FrameNode.
            auto frameNode = AceType::DynamicCast<FrameNode>(node->GetFrameChildByIndex(0, true));
            if (!frameNode) {
                return false;
            }

            if (((start <= index) && (index <= end)) || ((end < start) && (index <= end || start <= index))) {
                TAG_LOGD(AceLogTag::ACE_REPEAT,
                    "  ... in range: index %{public}d -> nodeId  %{public}d: SetActive(True)",
                    index, frameNode->GetId());
                frameNode->SetActive(true);
            } else {
                TAG_LOGD(AceLogTag::ACE_REPEAT,
                    "  ... out of range: index %{public}d -> nodeId  %{public}d: SetActive(false)",
                    index, frameNode->GetId());
                frameNode->SetActive(false);
            }
            if (((start - cacheStart <= index) && (index <= end + cacheEnd)) ||
                ((end < start) && (index <= end + cacheEnd || start - cacheStart <= index))) {
                // keep in L1
                return true;
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
            return false;
        });

    if (needSync) {
        UINode::MarkNeedSyncRenderTree(false);
        children_.clear();
        // re-assemble children_
        PostIdleTask();
    }
}

void RepeatVirtualScrollNode::DropFromL1(std::string key)
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

void RepeatVirtualScrollNode::InvalidateKeyCache()
{
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "InvalidateKeyCache triggered by Repeat rerender: nodeId: %{public}d .",
        (int)GetId());
    // empty the cache index -> key
    // C++ will need to ask all new keys from JS side
    caches_.InvalidateKeyAndTTypeCaches();
    children_.clear();

    auto frameNode = GetParentFrameNode();
    if (frameNode) {
        frameNode->ChildrenUpdatedFrom(0);
    }

    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

/**
 * a index -> key -> node does not exists, caller has verified before calling this function
 *
 * Ask TS to update a Node, if possible
 * If no suitable node, request to crete a new node
 */
RefPtr<UINode> RepeatVirtualScrollNode::CreateOrUpdateFrameChild4Index(uint32_t forIndex, const std::string& forKey)
{
    RefPtr<UINode> node4Index = caches_.UpdateFromL2(forIndex);
    if (node4Index) {
        return node4Index;
    }

    return caches_.CreateNewNode(forIndex);
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
    TAG_LOGD(AceLogTag::ACE_REPEAT, "index:%{public}d", (int)index);

    // It will get or create new key.
    const auto& key = caches_.GetKey4Index(index, true);
    if (!key) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to get key for %{public}d", index);
        return nullptr;
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "nodeId: %{public}d: GetFrameChildByIndex(index: %{public}d, "
        "key %{public}s, needBuild:  %{public}d, isCache: %{public}d, "
        "addToRenderTree: %{public}d) ...",
        (int)GetId(), (int)index, key->c_str(),
        (int)needBuild, (int)isCache, (int)addToRenderTree);

    // search if index -> key -> Node exist
    // will update the same key item if needs.
    auto node4Index = GetFromCaches(index);
    if (!node4Index && !needBuild) {
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "index %{public}d -> key '%{public}s' not in caches && needBuild==false, "
            "GetFrameChildByIndex returns nullptr .",
            index, key->c_str());
        return nullptr;
    }

    // node4Index needs to be created or updated on JS side
    if (!node4Index) {
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "index %{public}d -> key '%{public}s' not in caches && needBuild==true, calling "
            "CreateOrUpdateFrameChild4Index ....",
            index, key->c_str());

        // TS to either make new or update existing nodes
        node4Index = CreateOrUpdateFrameChild4Index(index, key.value());

        if (!node4Index) {
            TAG_LOGW(AceLogTag::ACE_REPEAT, "index %{public}d -> key '%{public}s' not in caches and failed to build.",
                index, key->c_str());
            return nullptr;
        }
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "index %{public}d  -> key '%{public}s', needBuild==true, node: %{public}s .",
        index, key->c_str(), caches_.DumpUINode(node4Index).c_str());

    if (isActive_) {
        node4Index->SetJSViewActive(true);
    }

    if (addToRenderTree && !isCache) {
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "index %{public}d isCache==false setActive and adding to L1 cache",
            index);
        node4Index->SetActive(true);
    }

    if (caches_.IsInL1Cache(key.value())) {
        return node4Index->GetFrameChildByIndex(0, needBuild);
    }

    // if the item was in L2 cache, move item to L1 cache.
    caches_.AddKeyToL1(key.value());
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
    if (onMoveEvent_) {
        InitDragManager(AceType::DynamicCast<FrameNode>(childNode));
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT, "index %{public}d, its child is %{public}d, returning child.", (int)index,
        (int)childNode->GetId());

    return childNode;
}

int32_t RepeatVirtualScrollNode::GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool /*isExpanded*/)
{
    return caches_.GetFrameNodeIndex(node);
}

const std::list<RefPtr<UINode>>& RepeatVirtualScrollNode::GetChildren() const
{
    if (!children_.empty()) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "GetChildren just returns non-empty children_");
        return children_;
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT, "Before rebuilding L1 ...");
    TAG_LOGD(AceLogTag::ACE_REPEAT, "L1: \n %{public}s", caches_.DumpL1().c_str());
    TAG_LOGD(AceLogTag::ACE_REPEAT, "L2: \n %{public}s", caches_.DumpL2().c_str());

    // can not modify l1_cache while iterating
    // GetChildren is overloaded, can not change it to non-const
    // need to order the child.
    std::map<int32_t, RefPtr<UINode>> children;
    caches_.ForEachL1IndexUINode(
        [&children](int32_t index, const RefPtr<UINode>& node) -> void { children.emplace(index, node); });
    for (const auto& [index, child] : children) {
        children_.emplace_back(child);
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT, "After rebuilding L1 ...");
    TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", caches_.DumpL1().c_str());
    TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", caches_.DumpL2().c_str());
    return children_;
}

void RepeatVirtualScrollNode::RecycleItems(int32_t from, int32_t to)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "from: %{public}d, to: %{public}d",
        from, to);
    offscreenItems_.from = from;
    offscreenItems_.to = to;
    for (auto i = from; i < to; i++) {
        if (i >= startIndex_ && i < startIndex_ + totalCount_) {
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
    TAG_LOGD(AceLogTag::ACE_REPEAT, "FrameCount returns %{public}d", (int)totalCount_);
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
        ACE_SCOPED_TRACE("RepeatVirtualScrollNode predict");
        TAG_LOGD(AceLogTag::ACE_REPEAT, "Exec Predict idle task");
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->postUpdateTaskHasBeenScheduled_ = false;
        TAG_LOGD(AceLogTag::ACE_REPEAT, "idle task calls GetChildren");
        node->GetChildren();
        TAG_LOGD(AceLogTag::ACE_REPEAT, " ============ before caches.purge ============= ");
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpL1().c_str());
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpL2().c_str());
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpKey4Index().c_str());
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpUINode4Key().c_str());
        node->caches_.Purge();
        TAG_LOGD(AceLogTag::ACE_REPEAT, " ============ after caches.purge ============= ");
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpL1().c_str());
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpL2().c_str());
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpKey4Index().c_str());
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpUINode4Key().c_str());
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
