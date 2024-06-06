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

#include <functional>
#include <utility>

#include "base/log/ace_trace.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

// REPEAT
RefPtr<RepeatVirtualScrollNode> RepeatVirtualScrollNode::GetOrCreateRepeatNode(int32_t nodeId,
    uint32_t totalCount,
    const std::map<std::string, uint32_t>& templateCacheCountMap,
    const std::function<void(uint32_t)>& onCreateNode,
    const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range)
{
    auto node = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScrollNode>(nodeId);
    if (node) {
        LOGE("Guido found RepeatVirtualScrollNode");
        node->UpdateTotalCount(totalCount);
        return node;
    }
    node = MakeRefPtr<RepeatVirtualScrollNode>(
        nodeId, totalCount, templateCacheCountMap, onCreateNode, onUpdateNode,
        onGetKeys4Range, onGetTypes4Range);

    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

RepeatVirtualScrollNode::RepeatVirtualScrollNode(int32_t nodeId,
    int32_t totalCount,
    const std::map<std::string, uint32_t>& templateCacheCountMap,
    const std::function<void(uint32_t)>& onCreateNode,
    const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range)
    : ForEachBaseNode(V2::JS_REPEAT_ETS_TAG, nodeId), totalCount_(totalCount),
      caches_(/* FIXME hard coded L2 size */ 2, onGetKeys4Range, onGetTypes4Range), onCreateNode_(onCreateNode),
      onUpdateNode_(onUpdateNode)
{
    // no precut task scheduled
    postUpdateTaskHasBeenScheduled_ = false;
}

void RepeatVirtualScrollNode::DoSetActiveChildRange(int32_t start, int32_t end)
{
    // FIXME lijunfeng  , yeyinglong:  can you advise how to enable LOGD output ? We are not using DevEco but use hilog directly?
    LOGE("DoSetActiveChildRange: nodeId: %{public}d: start: %{public}d, end: %{public}d", (int)GetId(), (int)start,
        (int)end);
    caches_.forEachL1IndexUINode([&](int32_t index, RefPtr<UINode> node) -> void {
        if (node == nullptr) {
            return;
        }
        // leads to infinite loop GetFrameChildByIndex(0, true, false, false ));
        auto frameNode = AceType::DynamicCast<FrameNode>(node->GetFirstChild());
        if (frameNode) {
            // DoSetActiveChildRange uses int32_t , while other functions use uint32_t
            // need to convert
            if ((start <= index) && (index <= end)) {
                LOGE("  ... in range: index %{public}d -> nodeId  %{public}d: SetActive(True)", index,
                    frameNode->GetId());
                frameNode->SetActive(true);
            } else {
                LOGE("  ... out of range: index %{public}d -> nodeId  %{public}d: SetActive(false)", index,
                    frameNode->GetId());
                frameNode->SetActive(false);
            }
        }
    });

    // TODO see if loop leads to any changes to active states
    // only in that case do the re-sync , re-assembly of children
    UINode::MarkNeedSyncRenderTree(false);

    children_.clear();
    // re-assemble children_
    PostIdleTask();
}

void RepeatVirtualScrollNode::InvalidateKeyCache() {
    LOGE("InvalidateKeyCache triggered by Repeat rerender: nodeId: %{public}d .", (int)GetId() );

    // empty the cache index -> key
    // C++ will need to ask all new keys from JS side
    caches_.resetKeyGenCache();
    caches_.updateL1Keys([&](uint32_t index) {
        const auto pair = caches_.getKey4Index(index);
        if (pair.first) {
            return pair.second;
        } else {
            // FIXME what to return for index for which there is no more a key?
            return std::string("____invalid_key__"); 
        }
    });

    children_.clear();

   if (auto frameNode = GetParentFrameNode()) {
        frameNode->ChildrenUpdatedFrom(0);
    }

    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}


RefPtr<UINode> RepeatVirtualScrollNode::GetFromCaches(uint32_t forIndex, std::string key)
{
    auto frameNode4Index = caches_.getL1Node4Index(forIndex);
    if (frameNode4Index != nullptr) {
        LOGE("index %{public}d found in L1 cache, returning", (int)forIndex);
        return frameNode4Index;
    }

    if (caches_.hasKeyL2(key)) {
        frameNode4Index = caches_.getUINode4Key(key);
    }
    if (frameNode4Index != nullptr) {
        LOGE("index %{public}d found in L2 cache, returning", (int)forIndex);
        return frameNode4Index;
    }

    LOGE("index %{public}d not found in L1 or L2 cache, GetFromCaches returns nullptr", (int)forIndex);
    return nullptr;
}

// get farthest (from L1 indexes) index in L2 cache or -1
/* 
int32_t RepeatVirtualScrollNode::GetFarthestL2CacheIndex()
{
    if (l2_cache_.map().empty() || l1_cache_.map().empty()) {
        return -1;
    }
    // std::map keys are always sorted
    auto l1_min = l1_cache_.map().begin()->first;
    auto l1_max = l1_cache_.map().rbegin()->first;
    auto l2_min = l2_cache_.map().begin()->first;
    auto l2_max = l2_cache_.map().rbegin()->first;

    // get farthest index in L2 cache
    int32_t d0 = l1_min - l2_min;
    int32_t d1 = l2_max - l1_max;
    int32_t index = (d0 <= 0 && d1 <= 0) ? -1 : ((d0 > d1) ? l2_min : l2_max);

    LOGE("pikalov l1(%{public}d, %{public}d), l2(%{public}d, %{public}d), index = %{public}d",
        l1_min, l1_max, l2_min, l2_max, index);

    return index;
}

// request TS to make new or update existing node subtree 
// TODO onCreateNode_ so far always makes new item (wriong function name!)
=======
// request TS to make new or update existing node subtree
// TODO requestUpdate_ so far always makes new item (wriong function name!)
*/

// on C++ side check if L2 item exists (rendered fromIndex) that should be updated
// if yes, tell TS to update fromIndex to forIndex
// if no, tell TS to make new item for forIndex
RefPtr<UINode> RepeatVirtualScrollNode::CreateOrUpdateFrameChild4Index(
    uint32_t forIndex, std::string forKey, bool addToCache)
{
    //int32_t fromIndex = GetFarthestL2CacheIndex();
    //if (fromIndex != -1) {
    //    const std::list<std::string> keys = onGetKeys4Range(fromIndex, fromIndex);
    //    if (!keys.empty()) {
    //      const std::string fromKey = keys.front();
    //      LOGE("Requesting item UPDATE fromKey index %{public}s, forIndex %{public}d from TS side ...",
    //            fromKey.c_str(), (int)forIndex);
    //      onUpdateNode_(fromKey, forIndex);
    //    }
    //}

    auto pair = caches_.deQueueKeyL2();
    if (pair.first) {
        const auto updateFromKey = pair.second;
        const auto updateNode = caches_.getUINode4Key(updateFromKey);
        if (updateNode != nullptr) { // security check node ref exists
            LOGE("Item update from key %{public}s, node %{public}s for index %{public}d -> new key %{public}s "
                 "(isCache=%{public}d)"
                 "from TS side ...",
                updateFromKey.c_str(), caches_.dumpUINodeWithKey(updateFromKey).c_str(), (int)forIndex, forKey.c_str(),
                (int)addToCache);

            // call TS onCreateNode_
            onUpdateNode_(updateFromKey, forIndex);

            LOGE("Item update from key %{public}s, node %{public}s for index %{public}d -> new key %{public}s "
                 "(isCache=%{public}d)"
                 "from TS side - DONE",
                updateFromKey.c_str(), caches_.dumpUINodeWithKey(updateFromKey).c_str(), (int)forIndex, forKey.c_str(),
                (int)addToCache);

            // updateNode has UI for 'firKey' now, no longer for 'updateFromKey'
            caches_.addUINodeByKey(forKey, updateNode);
            caches_.dropUINode4Key(updateFromKey);
            // FIXME need to add to L1?

            return updateNode;
        }
    }

    LOGE("Requesting new item build for index index %{public}d -> key %{public}s (isCache=%{public}d) from TS side ...",
        (int)forIndex, forKey.c_str(), (int)addToCache);

    // swap the ViewStackProcessor instance for secondary while we run the item builder function
    // so that its results can easily be obtained from it, does not disturb main ViewStackProcessor
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    auto* viewStack = NG::ViewStackProcessor::GetInstance();

    // call TS onCreateNode_
    onCreateNode_(forIndex);

    const auto frameNode4Index = viewStack->Finish();
    if (frameNode4Index == nullptr) {
        LOGE("For index %{public}d -> key %{public}s item builder FAILED to gen FrameNode. ERROR", forIndex,
            forKey.c_str());
        return nullptr;
    }
    LOGE("For index %{public}d item builder success, made node %{public}s(%{public}d) .", forIndex,
        frameNode4Index->GetTag().c_str(), frameNode4Index->GetId());

    // caller is responsible to add key to L1 or L2 cache
    caches_.addUINodeByIndex(forIndex, frameNode4Index);
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

    LOGE("nodeId: %{public}d: GetFrameChildByIndex(index: %{public}d, key %{public}s, needBuild:  %{public}d, isCache: "
         "%{public}d, "
         "addToRenderTree: %{public}d) ...",
        (int)GetId(), (int)index, key.c_str(), (int)needBuild, (int)isCache, (int)addToRenderTree);

    // search in L1 then in L2 cache:
    auto frameNode4Index = GetFromCaches(index, key);
    if ((frameNode4Index == nullptr) && !needBuild) {
        LOGE("index %{public}d not in caches && needBuild==false, GetFrameChildByIndex returns nullptr .", index);
        return nullptr;
    }

    if (frameNode4Index == nullptr) {
        // TS to either make new or update existing nodes
        frameNode4Index = CreateOrUpdateFrameChild4Index(index, key, isCache);

        if (frameNode4Index == nullptr) {
            return nullptr;
        }

        if (isCache) {
            // the item for index has been pre-build just to add it to L2 cache
            caches_.moveAndQueueKeyL2(index, key);
            frameNode4Index->SetParent(WeakClaim(this));
            frameNode4Index->SetJSViewActive(false);

            LOGE("index %{public}d item builder made or updated FrameNode %{public}d, isCache==true, adding the Node "
                 "to L2 "
                 "cache, no further processing, returning the node.",
                index, frameNode4Index->GetId());

            return frameNode4Index->GetFrameChildByIndex(0, needBuild);
        }

        LOGE("index %{public}d item builder made new FrameNode %{public}d, further processing ...", index,
            frameNode4Index->GetId());
    } // frameNode4Index needs to be created or updated on JS side

    // if the item was in L2 cache, remove it from there

    if (isActive_) {
        // FIXME lijunfeng, yeyinglong: review is handling active state of RepeatVirtualScroll and its children handled correctly?
        frameNode4Index->SetJSViewActive(true);
    }

    if (addToRenderTree) {
        LOGE("index %{public}d ,FrameNode %{public}d: addToRenderTree==true -> setActive and adding to L1 cache", index,
            frameNode4Index->GetId());

        frameNode4Index->SetActive(true);
        caches_.addOrMoveKeyToL1(index, key);
    } else {
        LOGE("index %{public}d, FrameNode %{public}d: addToRenderTree==false  -> NO setActive, "
             "add to L2 cache",
            index, frameNode4Index->GetId());

        // not set to active
        caches_.moveAndQueueKeyL2(index, key);
    }

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
    self->caches_.rebuildL1([self](int32_t index, RefPtr<UINode> node) -> bool {
        auto frameNode = AceType::DynamicCast<FrameNode>(
            node->GetFirstChild()); // leads to infinite loop GetFrameChildByIndex(0, true, false, false ));
        if (frameNode == nullptr) {
            // FIXME lijunfeng  , yeyinglong: how to handle error?
            return false;
        }

        if (frameNode->IsActive()) {
            LOGE("L1 cache entry index %{public}d nodeId %{public}d  isActive==true, adding to children_", (int)index,
                node->GetId());
            self->children_.emplace_back(node);
            return true; // will keep in L1 cache
        } else {
            LOGE("L1 cache entry index %{public}d nodeId %{public}d  isActive==false, moving to L2 cache, detaching "
                 "from tree",
                (int)index, node->GetId());
            // FIXME  lijunfeng , yeyinglong: add animated removal from tree
            node->DetachFromMainTree();
            return false; // will move to L2 cache
        }
    }); // rebuild Lambda

    LOGE("GetChildren() result: children_ count = %{public}d, includes:", children_.size());
    for (auto& c : children_) {
        LOGE("   child: NodeId %{public}d", (int)c->GetId());
    }
    return children_;
}

// FIXME , TODO haoyu function does not get called
void RepeatVirtualScrollNode::RecycleItems(int32_t from, int32_t to)
{
    LOGE("from: %{public}d, to: %{public}d", from, to);
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
        LOGE("%{public}s", node->caches_.dumpUINode4Key().c_str());

        if (node->caches_.purge()) {
            LOGE(" ============ after caches.purge ============= ");
            LOGE("%{public}s", node->caches_.dumpL1().c_str());
            LOGE("%{public}s", node->caches_.dumpL2().c_str());
            LOGE("%{public}s", node->caches_.dumpKey4Index().c_str());
            LOGE("%{public}s", node->caches_.dumpUINode4Key().c_str());
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
