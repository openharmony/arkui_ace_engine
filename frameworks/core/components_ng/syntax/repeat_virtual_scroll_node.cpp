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
    // FIXME lijunfeng  , yeyinglong:  can you advise how to enable LOGD output ? We are not using DevEco but use hilog
    // directly?
    LOGE("DoSetActiveChildRange: nodeId: %{public}d: start: %{public}d, end: %{public}d, cacheStart: %{public}d, "
         "cacheEnd: %{public}d",
        (int)GetId(), (int)start, (int)end, (int)cacheStart, (int)cacheEnd);

    // memorize active range
    caches_.setLastActiveRange(static_cast<uint32_t>(start), static_cast<uint32_t>(end));

    // caches_.forEachL1IndexUINode([&](int32_t index, RefPtr<UINode> node) -> void {
    bool needSync =
        caches_.rebuildL1([start, end, cacheStart, cacheEnd](int32_t index, const RefPtr<UINode>& node) -> bool {
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
            node->DetachFromMainTree();
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
    LOGE("InvalidateKeyCache triggered by Repeat rerender: nodeId: %{public}d .", (int)GetId());

    // empty the cache index -> key
    // C++ will need to ask all new keys from JS side
    caches_.invalidateKeyAndTTypeCaches();
    children_.clear();

    if (auto frameNode = GetParentFrameNode()) {
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
RefPtr<UINode> RepeatVirtualScrollNode::CreateOrUpdateFrameChild4Index(uint32_t forIndex, std::string forKey)
{
    RefPtr<UINode> frameNode4Index = caches_.updateFromL2(forIndex);
    if (frameNode4Index != nullptr) {
        LOGE("Item update for index %{public}d - key %{public}s, node: %{public}s", forIndex, forKey.c_str(),
            caches_.dumpUINode(frameNode4Index).c_str());
        return frameNode4Index;
    }

    LOGE("Requesting new item build for index index %{public}d -> key %{public}s  from TS side ...", (int)forIndex,
        forKey.c_str());

    frameNode4Index = caches_.createNewNode(forIndex);

    LOGE("For index %{public}d item builder success, made node %{public}s(%{public}d) .", forIndex,
        frameNode4Index->GetTag().c_str(), frameNode4Index->GetId());

    return frameNode4Index;
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
    const auto pair = caches_.getKey4Index(index);
    if (!pair.first) {
        // FIXME error msg
        return nullptr;
    }
    const std::string key = pair.second;

    LOGE("nodeId: %{public}d: GetFrameChildByIndex(index: %{public}d, key %{public}s, needBuild:  %{public}d, "
         "isCache: "
         "%{public}d, "
         "addToRenderTree: %{public}d) ...",
        (int)GetId(), (int)index, key.c_str(), (int)needBuild, (int)isCache, (int)addToRenderTree);

    // search if index -> key -> Node exist
    // pair.first tells of key is in L1
    auto nodePair = GetFromCaches(index);
    RefPtr<UINode> frameNode4Index = nodePair.second;
    if ((frameNode4Index == nullptr) && !needBuild) {
        LOGE("index %{public}d not in caches && needBuild==false, GetFrameChildByIndex returns nullptr .", index);
        return nullptr;
    }

    if (frameNode4Index == nullptr) {
        // TS to either make new or update existing nodes
        frameNode4Index = CreateOrUpdateFrameChild4Index(index, key);

        if (frameNode4Index == nullptr) {
            return nullptr;
        }

        LOGE("index %{public}d item builder made new FrameNode %{public}d, further processing ...", index,
            frameNode4Index->GetId());
    } // frameNode4Index needs to be created or updated on JS side

    // if the item was in L2 cache, remove it from there

    if (isActive_) {
        // FIXME lijunfeng, yeyinglong: review is handling active state of RepeatVirtualScroll and its children handled
        // correctly?
        frameNode4Index->SetJSViewActive(true);
    }

    if (addToRenderTree && !isCache) {
        LOGE("index %{public}d ,FrameNode %{public}d: addToRenderTree==true -> setActive and adding to L1 cache", index,
            frameNode4Index->GetId());

        frameNode4Index->SetActive(true);
    } else {
        LOGE("index %{public}d, FrameNode %{public}d: addToRenderTree==false  -> NO setActive, "
             "add to L2 cache",
            index, frameNode4Index->GetId());
    }
    if (caches_.isInL1Cache(key)) {
        return frameNode4Index->GetFrameChildByIndex(0, needBuild);
    }
    caches_.addKeyToL1(key);
    if (frameNode4Index->GetDepth() != GetDepth() + 1) {
        frameNode4Index->SetDepth(GetDepth() + 1);
    }
    MarkNeedSyncRenderTree();
    frameNode4Index->SetParent(WeakClaim(this));

    // FIXME why do this if addToRenderTree == false ?
    if (IsOnMainTree()) {
        frameNode4Index->AttachToMainTree(false, GetContext());
    }

    children_.clear();
    // re-assemble children_
    PostIdleTask();

    auto childNode = frameNode4Index->GetFrameChildByIndex(0, needBuild);
    if (onMoveEvent_) {
        InitDragManager(AceType::DynamicCast<FrameNode>(childNode));
    }

    LOGE("index %{public}d, Node %{public}d, its child is %{public}d, returning child.", (int)index,
        (int)frameNode4Index->GetId(), (int)childNode->GetId());

    return childNode;
}

int32_t RepeatVirtualScrollNode::GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool isExpanded)
{
    if (!isExpanded) {
        return UINode::GetFrameNodeIndex(node, isExpanded);
    }
    return caches_.GetFrameNodeIndex(node);
}

const std::list<RefPtr<UINode>>& RepeatVirtualScrollNode::GetChildren() const
{
    if (!children_.empty()) {
        LOGE("GetChildren just returns non-empty children_");
        return children_;
    }

    // FIXME in logs we can see this function gets called , sems like gets called while its executing
    LOGE("GetChildren children_ reassembly ....");

    // self is mutable this
    auto* self = const_cast<RepeatVirtualScrollNode*>(this);

    // can not modify l1_cache while iterating
    // GetChildren is overloaded, can not change it to non-const
    self->caches_.forEachL1IndexUINode(
        [self](int32_t index, RefPtr<UINode> node) -> void { self->children_.emplace_back(node); }); // rebuild Lambda

    for (auto& c : children_) {
        LOGE("   child: NodeId %{public}d", (int)c->GetId());
    }
    return children_;
}

// FIXME , TODO haoyu function does not get called
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
    // FIXME min L2 size is 1,  what is data size is 0? Does it pose an issue?
    LOGE("FrameCount returns %{public}d", (int)totalCount_);
    return totalCount_;
}

void RepeatVirtualScrollNode::PostIdleTask()
{
    if (postUpdateTaskHasBeenScheduled_) {
        return;
    }
    LOGE("Posting idle task");
    postUpdateTaskHasBeenScheduled_ = true;
    auto context = GetContext();
    CHECK_NULL_VOID(context);

    context->AddPredictTask([weak = AceType::WeakClaim(this)](int64_t deadline, bool canUseLongPredictTask) {
        ACE_SCOPED_TRACE("LazyForEach predict");
        LOGE("Exec Predict idle task");
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->postUpdateTaskHasBeenScheduled_ = false;

        LOGE("idle task calls GetChildren");
        node->GetChildren();

        LOGE(" ============ before caches.purge ============= ");
        LOGE("%{public}s", node->caches_.dumpL1().c_str());
        LOGE("%{public}s", node->caches_.dumpL2().c_str());
        LOGE("%{public}s", node->caches_.dumpKey4Index().c_str());
        LOGE("%{public}s", node->caches_.dumpTType4Index().c_str());
        LOGE("%{public}s", node->caches_.dumpUINode4Key4TType().c_str());

        if (node->caches_.purge()) {
            LOGE(" ============ after caches.purge ============= ");
            LOGE("%{public}s", node->caches_.dumpL1().c_str());
            LOGE("%{public}s", node->caches_.dumpL2().c_str());
            LOGE("%{public}s", node->caches_.dumpKey4Index().c_str());
            LOGE("%{public}s", node->caches_.dumpTType4Index().c_str());
            LOGE("%{public}s", node->caches_.dumpUINode4Key4TType().c_str());
        }
        // TODO haoyu: initiate prediction
        // expected outcome: RecycleItems(int32_t from, int32_t to); gets called
    });
}

// FIXME Which of the following methods are actually needed ?

void RepeatVirtualScrollNode::SetOnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    if (onMove && !onMoveEvent_) {
        auto parentNode = GetParentFrameNode();
        if (parentNode) {
            InitAllChildrenDragManager(true);
        } else {
            auto piplineContext = PipelineContext::GetCurrentContext();
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

// FIXME called from where ?
RefPtr<FrameNode> RepeatVirtualScrollNode::GetFrameNode(int32_t index)
{
    // FIXME ????
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
