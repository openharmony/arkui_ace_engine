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
#include "core/components_ng/pattern/list/list_item_pattern.h"
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

    // memorize active range
    caches_.SetLastActiveRange(static_cast<uint32_t>(start), static_cast<uint32_t>(end));

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
            // DoSetActiveChildRange uses int32_t , while other functions use uint32_t
            // need to convert
            if ((start <= index) && (index <= end)) {
                frameNode->SetActive(true);
            } else {
                frameNode->SetActive(false);
            }
            if ((start - cacheStart <= index) && (index <= end + cacheEnd)) {
                return true;
            }
            // active node moved into L2 cached.
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

    // TODO see if loop leads to any changes to active states
    // only in that case do the re-sync , re-assembly of children
    if (needSync) {
        UINode::MarkNeedSyncRenderTree(false);
        children_.clear();
        // re-assemble children_
        PostIdleTask();
    }
}

void RepeatVirtualScrollNode::InvalidateKeyCache()
{
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
    if (!node4Index) {
        return node4Index;
    }

    return caches_.CreateNewNode(forIndex);
}

// FIXME added
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
    // It will get or create new key.
    const auto& key = caches_.GetKey4Index(index);
    if (!key) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to get key for %{public}d", index);
        return nullptr;
    }
    // search if index -> key -> Node exist
    // pair.first tells of key is in L1
    auto node4Index = GetFromCaches(index);
    if (!node4Index && !needBuild) {
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "index %{public}d not in caches && needBuild==false, GetFrameChildByIndex returns nullptr .", index);
        return nullptr;
    }

    // node4Index needs to be created or updated on JS side
    if (!node4Index) {
        // TS to either make new or update existing nodes
        node4Index = CreateOrUpdateFrameChild4Index(index, key.value());

        if (!node4Index) {
            TAG_LOGW(AceLogTag::ACE_REPEAT, "index %{public}d not in caches and failed to build.", index);
            return nullptr;
        }
        // move item to L1 cache.
        caches_.AddKeyToL1(key.value());
    } else {
        // TODO need update existed node4Index with new index.
    }

    // if the item was in L2 cache, remove it from there

    if (isActive_) {
        node4Index->SetJSViewActive(true);
    }

    if (addToRenderTree && !isCache) {
        node4Index->SetActive(true);
    }
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

    return childNode;
}

int32_t RepeatVirtualScrollNode::GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool /*isExpanded*/)
{
    return caches_.GetFrameNodeIndex(node);
}

const std::list<RefPtr<UINode>>& RepeatVirtualScrollNode::GetChildren() const
{
    if (!children_.empty()) {
        return children_;
    }

    // can not modify l1_cache while iterating
    // GetChildren is overloaded, can not change it to non-const
    // need to order the child.
    std::map<int32_t, RefPtr<UINode>> children;
    caches_.ForEachL1IndexUINode(
        [&children](int32_t index, const RefPtr<UINode>& node) -> void { children.emplace(index, node); });
    for (const auto& [index, child] : children) {
        children_.emplace_back(child);
    }
    return children_;
}

void RepeatVirtualScrollNode::RecycleItems(int32_t from, int32_t to)
{
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
    return totalCount_;
}

void RepeatVirtualScrollNode::PostIdleTask()
{
    if (postUpdateTaskHasBeenScheduled_) {
        return;
    }
    postUpdateTaskHasBeenScheduled_ = true;
    auto* context = GetContext();
    CHECK_NULL_VOID(context);

    context->AddPredictTask([weak = AceType::WeakClaim(this)](int64_t /*deadline*/, bool /*canUseLongPredictTask*/) {
        ACE_SCOPED_TRACE("RepeatVirtualScrollNode predict");
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->postUpdateTaskHasBeenScheduled_ = false;
        node->GetChildren();
        node->caches_.Purge();
    });
}

void RepeatVirtualScrollNode::OnConfigurationUpdate(const ConfigurationChange& configurationChange)
{
    if ((configurationChange.colorModeUpdate || configurationChange.fontUpdate)) {
        const auto& children = caches_.GetAllNodes();
        for (const auto& [key, child] : children) {
            if (child) {
                child->UpdateConfigurationUpdate(configurationChange);
            }
        }
    }
}

// FIXME Which of the following methods are actually needed ?

void RepeatVirtualScrollNode::SetOnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    if (onMove && !onMoveEvent_) {
        auto parentNode = GetParentFrameNode();
        if (parentNode) {
            InitAllChildrenDragManager(true);
        } else {
            auto* piplineContext = GetContext();
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
    onMoveEvent_ = std::move(onMove);
}

// FOREAch
void RepeatVirtualScrollNode::MoveData(int32_t from, int32_t to)
{
    if (from == to) {
        return;
    }

    auto idIter = ids_.begin();
    std::advance(idIter, from);
    auto id = *idIter;
    ids_.erase(idIter);
    idIter = ids_.begin();
    std::advance(idIter, to);
    ids_.insert(idIter, id);

    auto& children = ModifyChildren();
    auto fromIter = children.begin();
    std::advance(fromIter, from);
    auto child = *fromIter;
    children.erase(fromIter);
    auto toIter = children.begin();
    std::advance(toIter, to);
    children.insert(toIter, child);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

RefPtr<FrameNode> RepeatVirtualScrollNode::GetFrameNode(int32_t index)
{
    return AceType::DynamicCast<FrameNode>(GetFrameChildByIndex(index, false, false));
}

void RepeatVirtualScrollNode::InitDragManager(const RefPtr<UINode>& child)
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

void RepeatVirtualScrollNode::InitAllChildrenDragManager(bool init)
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
