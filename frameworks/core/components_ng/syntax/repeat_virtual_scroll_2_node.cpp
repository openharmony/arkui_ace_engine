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

#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

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

using CacheItem = RepeatVirtualScroll2Caches::CacheItem;

// REPEAT
RefPtr<RepeatVirtualScroll2Node> RepeatVirtualScroll2Node::GetOrCreateRepeatNode(int32_t nodeId, uint32_t arrLen,
    uint32_t totalCount, const std::function<std::pair<RIDType, uint32_t>(IndexType)>& onGetRid4Index,
    const std::function<void(IndexType, IndexType)>& onRecycleItems,
    const std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)>& onActiveRange,
    const std::function<void(IndexType, IndexType)>& onMoveFromTo, const std::function<void()>& onPurge)
{
    auto node = ElementRegister::GetInstance()->GetSpecificItemById<RepeatVirtualScroll2Node>(nodeId);
    if (node) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "Repeat(%{public}d).GetOrCreateRepeatNode Found RepeatVirtualScroll2Node",
            static_cast<int32_t>(node->GetId()));
        node->UpdateArrLen(arrLen);
        node->UpdateTotalCount(totalCount);
        return node;
    }
    node = MakeRefPtr<RepeatVirtualScroll2Node>(
        nodeId, arrLen, totalCount, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge);

    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

RepeatVirtualScroll2Node::RepeatVirtualScroll2Node(int32_t nodeId, uint32_t arrLen, int32_t totalCount,
    const std::function<std::pair<RIDType, uint32_t>(IndexType)>& onGetRid4Index,
    const std::function<void(IndexType, IndexType)>& onRecycleItems,
    const std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)>& onActiveRange,
    const std::function<void(IndexType, IndexType)>& onMoveFromTo,
    const std::function<void()>& onPurge)
    : ForEachBaseNode(V2::JS_REPEAT_ETS_TAG, nodeId), arrLen_(arrLen), totalCount_(totalCount), caches_(onGetRid4Index),
      onRecycleItems_(onRecycleItems), onActiveRange_(onActiveRange), onMoveFromTo_(onMoveFromTo),
      onPurge_(onPurge), postUpdateTaskHasBeenScheduled_(false)
{}

void RepeatVirtualScroll2Node::UpdateTotalCount(uint32_t totalCount)
{
    // set active range when deleting all.
    if (totalCount == 0 && totalCount != totalCount_) {
        DoSetActiveChildRange(-1, -1, 0, 0, false);
    }
    totalCount_ = totalCount;
}

void RepeatVirtualScroll2Node::DoSetActiveChildRange(
    int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
    // showCache==true when container needs activate pre-render nodes
    if (showCache) {
        start -= cacheStart;
        end += cacheEnd;
        cacheStart = 0;
        cacheEnd = 0;
    }
    // get normalized active range (with positive indices only)
    // step 1, step 2
    const auto activeRange = CheckActiveRange(start, end, cacheStart, cacheEnd);
    const int32_t nStart = activeRange.first;
    const int32_t nEnd = activeRange.second;

    // step 3: iterate over L1, for each entry check of it is still in active range
    TAG_LOGD(AceLogTag::ACE_REPEAT, "Rebuild L1 on C++ side ...");
    bool needSync = RebuildL1(start, end, nStart, nEnd);

    // step 4: iterate over all UINode sub-trees, only interested in L2 ones
    // for items moved from L1 to L2 but sitl active and on render tree, correct this.
    TAG_LOGD(AceLogTag::ACE_REPEAT, "Checking spare nodes on C++ side ...");
    needSync = ProcessActiveL2Nodes() || needSync;

    // memorize range
    prevActiveRangeStart_ = nStart;
    prevActiveRangeEnd_ = nEnd;
    prevVisibleRangeStart_ = start;
    prevVisibleRangeEnd_ = end;
    forceRunDoSetActiveRange_ = false;

    if (needSync) {
        // step 5: order a resync from layout
        // what these calls exactly do has never been defined for us.
        RequestSyncTree();
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "DoSetActiveChildRange: Repeat(%{public}d): start: %{public}d - end: %{public}d; cacheStart: "
        "%{public}d, cacheEnd: %{public}d: ==> normalized range to keep in L1: %{public}d - %{public}d \n"
        "UINode cache:\n%{public}s\n%{public}s",
        GetId(), start, end, cacheStart, cacheEnd, nStart, nEnd,
        caches_.DumpUINodeCache().c_str(), caches_.DumpL1Rid4Index().c_str());
}

/**
 * check whether the node is in L1 cache. called from ReBuildL1
 *
 * index: node index
 * nStart: first return value of CheckActiveRange
 * nEnd: second return value of CheckActiveRange
 * cacheItem: repeat cache item of index
 */
bool RepeatVirtualScroll2Node::CheckNode4IndexInL1(int32_t index, int32_t nStart, int32_t nEnd, CacheItem& cacheItem)
{
    auto totalCount = static_cast<int32_t>(totalCount_);
    bool remainInL1 = (nStart <= index && index <= nEnd); // cover scenario 1 & 2 & 4
    if (isLoop_) {
        remainInL1 = remainInL1 ||
            (nStart > nEnd && (nStart <= index || index <= nEnd)) || // cover scenario 3.2 & 3.4
            (nStart < 0 && index >= nStart + totalCount) || // cover scenario 3.1
            (nEnd >= totalCount && index <= nEnd - totalCount); // cover scenario 3.3
    }
    cacheItem->isL1_ = remainInL1;
    if (!remainInL1) {
        cacheItem->isOnRenderTree_ = false;
    }
    return remainInL1;
}

/**
 * pre-process active range. called from DoSetActiveChildRange
 *
 * start: start index on the screen, may be negative or greater than totalCount
 * end: end index on the screen, may be negative or greater than totalCount
 * cacheStart: cachedCount above - depends on container
 * cacheEnd: cachedCount below - depends on container
 *
 * possible scenarios (only one repeat in scroll container):
 * - scenario 1: List/Swiper-no-Loop
 *   - 1.1 screen: [0 1 2] 3 4 5.., DoSetActiveChildRange params: (0,2,0,2), nStart&nEnd: (0,4)
 *   - 1.2 screen: ..1 2 [3 4 5] 6 7, DoSetActiveChildRange params: (3,5,2,2), nStart&nEnd: (1,7)
 *   - 1.3 screen: ..5 6 [7 8 9], DoSetActiveChildRange params: (7,9,2,0), nStart&nEnd: (5,9)
 * - scenario 2: Grid/WaterFlow
 *   - 2.1 screen: [0 1 2] 3 4 5.., DoSetActiveChildRange params: (0,2,2,2), nStart&nEnd: (0,4)
 *   - 2.2 screen: ..1 2 [3 4 5] 6 7, DoSetActiveChildRange params: (3,5,2,2), nStart&nEnd: (1,7)
 *   - 2.3 screen: ..5 6 [7 8 9], DoSetActiveChildRange params: (7,9,2,2), nStart&nEnd: (5,9)
 * - scenario 3: Swiper-Loop
 *   - 3.1 screen: ..8 9 [0 1 2] 3 4.., DoSetActiveChildRange params: (0,2,2,2), nStart&nEnd: (-2,4)
 *   - 3.2 screen: ..7 8 [9 0 1] 2 3.., DoSetActiveChildRange params: (9,1,2,2), nStart&nEnd: (7,3)
 *   - 3.3 screen: ..5 6 [7 8 9] 0 1.., DoSetActiveChildRange params: (8,2,2,2), nStart&nEnd: (5,11)
 *   - 3.4 screen(overlapped): 2 [3 0] 1, DoSetActiveChildRange params: (3,0,2,2), nStart&nEnd: (2,1)
 *
 * possible scenarios (multiple components in scroll container, X indicates a non-repeat child):
 * - scenario 4: List/Grid/WaterFlow/Swiper-no-Loop
 *   - 4.1 screen: ..[X X 0 1 2] 3 4.., DoSetActiveChildRange params: (-2,3,2,2), nStart&nEnd: (0,4)
 *   - 4.2 screen: ..[X X X] 0 1 2.., DoSetActiveChildRange params: (-5,-1,2,2), nStart&nEnd: (0,1)
 *   - 4.3 screen: ..[X X X] X X 0 1.., DoSetActiveChildRange params: (-5,-3,2,2), nStart&nEnd: (NaN)
 *   - 4.4 screen: ..0 1 [2 3 4 X X].., DoSetActiveChildRange params: (2,6,2,2), nStart&nEnd: (0,4)
 *   - 4.5 screen: ..0 1 [X X X].., DoSetActiveChildRange params: (2,5,2,2), nStart&nEnd: (0,1)
 *   - 4.6 screen: ..0 1 X X [X X X].., DoSetActiveChildRange params: (4,6,2,2), nStart&nEnd: (NaN)
 * - scenario 5: Swiper-Loop. Currently it isn't allowed to be used.
 */
ActiveRangeType RepeatVirtualScroll2Node::CheckActiveRange(
    int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd)
{
    const int32_t signed_totalCount = static_cast<int32_t>(totalCount_);
    int32_t nStart = start - cacheStart;
    int32_t nEnd = end + cacheEnd;

    if (start > end && nStart <= nEnd) { // cover scenario 3.4
        // nStart & nEnd overlapped. must keep nStart > nEnd, otherwise CheckNode4IndexInL1
        //      cannot determine swiper-loop scenario
        const int32_t divider = 2;
        nStart = signed_totalCount / divider + 1;
        nEnd = signed_totalCount / divider;
    }
    if (!isLoop_) {
        if (nStart >= signed_totalCount || nEnd < 0) { // no active node on screen
            nStart = INT32_MAX;
            nEnd = INT32_MAX;
        } else { // cover scenario 1 & 2 & 4
            // keep 0 <= nStart <= nEnd <= totalCount - 1
            nStart = std::max(nStart, 0);
            nEnd = std::min(std::max(nEnd, nStart), signed_totalCount - 1);
        }
    }

    if (!needRecordFirstFrameChild_ && (minFrameChildIndex_ != nStart || maxFrameChildIndex_ != nEnd)) {
        forceRunDoSetActiveRange_ = true;
    }
    needRecordFirstFrameChild_ = true;

    // step 1: if range unchanged skip full run unless forced (rerender will force run once)
    if (!forceRunDoSetActiveRange_ && (prevActiveRangeStart_ == nStart && prevActiveRangeEnd_ == nEnd) &&
        (prevVisibleRangeStart_ == start && prevVisibleRangeEnd_ == end)) {
        // skip executing if range has no changed
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "DoSetActiveChildRange: Repeat(nodeId): %{public}d: start: %{public}d - end: %{public}d; cacheStart: "
            "%{public}d, cacheEnd: %{public}d: ==> normalized range to keep in L1: %{public}d - %{public}d is "
            "unchanged. Skipping.",
            GetId(), start, end, cacheStart, cacheEnd, nStart, nEnd);
        return {nStart, nEnd};
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "REPEAT TRACE DoSetActiveChildRange: Repeat(nodeId): %{public}d: start: %{public}d - end: %{public}d; "
        "cacheStart: %{public}d, cacheEnd: %{public}d: ==> normalized range to keep in L1: %{public}d - %{public}d,",
        GetId(), start, end, cacheStart, cacheEnd, nStart, nEnd);

    // swap the ViewStackProcessor for secondary and push this node
    // call sequence is C++ -> TS -> JS
    // for TS -> JS to find 'this' node, we need to put 'this' to the 2nd
    // ViewStackProcessor
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    auto* viewStack = NG::ViewStackProcessor::GetInstance();
    viewStack->Push(Referenced::Claim(this));

    ACE_SCOPED_TRACE("Repeat.DoSetActiveChildRange start[%d]-end[%d], cacheStart[%d], cacheEnd[%d]. keep in [%d]-[%d]",
        start, end, cacheStart, cacheEnd, nStart, nEnd);

    // step 2. call TS side
    onActiveRange_(nStart, nEnd, start, end, isLoop_, forceRunDoSetActiveRange_);

    return {nStart, nEnd};
}

bool RepeatVirtualScroll2Node::RebuildL1(int32_t start, int32_t end, int32_t nStart, int32_t nEnd)
{
    return caches_.RebuildL1(
        [&, start, end, nStart, nEnd, weak = WeakClaim(this)](int32_t index, CacheItem& cacheItem) -> bool {
            auto repeatNode = weak.Upgrade();
            CHECK_NULL_RETURN(repeatNode, false);
            const auto node = cacheItem->node_;
            if (!node) {
                return false;
            }
            auto frameNode = AceType::DynamicCast<FrameNode>(node->GetFrameChildByIndex(0, true));
            if (!frameNode) {
                return false;
            }
            if (((start <= index) && (index <= end)) ||
                ((end < start) && (index <= end || start <= index))) {
                    TAG_LOGD(AceLogTag::ACE_REPEAT,
                        "in range: index %{public}d -> child nodeId %{public}d: SetActive(true)",
                        index, frameNode->GetId());
                    frameNode->SetActive(true);
                    cacheItem->isActive_ = true;
            } else {
                TAG_LOGD(AceLogTag::ACE_REPEAT,
                    "out of range: index %{public}d -> child nodeId %{public}d: SetActive(false)",
                    index, frameNode->GetId());
                // SetActive to false will remove node from RS tree.
                // If the node is deleted by animateTo, then animation will not display.
                if (!AnimationUtils::IsImplicitAnimationOpen()) {
                    frameNode->SetActive(false);
                }
                cacheItem->isActive_ = false;
            }

            if (repeatNode->CheckNode4IndexInL1(index, nStart, nEnd, cacheItem)) {
                // keep in Repeat L1
                TAG_LOGD(AceLogTag::ACE_REPEAT,
                    "in L1: index %{public}d, node %{public}s with child id %{public}d: SetActive(True)",
                    index, caches_.DumpUINode(cacheItem->node_).c_str(), static_cast<int32_t>(frameNode->GetId()));
                return true;
            }

            TAG_LOGD(AceLogTag::ACE_REPEAT,
                "out of L1: index %{public}d, node %{public}s with child id %{public}d",
                index, caches_.DumpUINode(cacheItem->node_).c_str(), frameNode->GetId());

            if (node->OnRemoveFromParent(true)) {
                // OnRemoveFromParent returns true means the child can be removed from tree immediately.
                repeatNode->RemoveDisappearingChild(node);
            } else {
                repeatNode->AddDisappearingChild(node);
            }
            return false;
        }
    );
}

bool RepeatVirtualScroll2Node::ProcessActiveL2Nodes()
{
    bool needSync = false;
    caches_.ForEachCacheItem([&](RIDType rid, const CacheItem& cacheItem) {
        if (caches_.GetL1Index4RID(rid) != std::nullopt) {
            // in L1
            return;
        }
        if (!cacheItem->isActive_ && !cacheItem->isOnRenderTree_) {
            return;
        }
        // spare item is still active or on render tree
        // two cases when this can happen:
        // 1. remove from L1 by RecycleItems
        // 2. Repeat.rerender
        auto frameNode = AceType::DynamicCast<FrameNode>(cacheItem->node_->GetFrameChildByIndex(0, true));
        if (frameNode && cacheItem->isActive_) {
            // SetActive to false will remove node from RS tree.
            // If the node is deleted by animateTo, then animation will not display.
            if (!AnimationUtils::IsImplicitAnimationOpen()) {
                frameNode->SetActive(false);
            }
            cacheItem->isActive_ = false;
            needSync = true;
            TAG_LOGD(AceLogTag::ACE_REPEAT,
                "spare node %{public}s: apply SetActive(false)",
                caches_.DumpCacheItem(cacheItem).c_str());
        }
        if (cacheItem->node_->OnRemoveFromParent(true)) {
            // OnRemoveFromParent returns true means the child can be removed from tree immediately.
            RemoveDisappearingChild(cacheItem->node_);
        } else {
            // else move child into disappearing children, skip syncing render tree
            AddDisappearingChild(cacheItem->node_);
        }
        cacheItem->isOnRenderTree_ = false;
        needSync = true;
        TAG_LOGD(AceLogTag::ACE_REPEAT, "spare nodes %{public}s: removed node from render tree",
            caches_.DumpCacheItem(cacheItem).c_str());
    });

    return needSync;
}

void RepeatVirtualScroll2Node::RequestSyncTree()
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "requesting sync of UI tree");
    UINode::MarkNeedSyncRenderTree(false);
    children_.clear();
    // re-assemble children_
    PostIdleTask();
}

/**
 * Currently NOT IN USE
 * to do: if called by List, remember to adapt moveFromTo_.
 */
void RepeatVirtualScroll2Node::DoSetActiveChildRange(
    const std::set<int32_t>& activeItems, const std::set<int32_t>& cachedItems, int32_t baseIndex)
{
    // Function currently unused
    // when taking to use, need to update and align to 1st version of DoSetActiveChildRange above
    // the call to TS is missing!

    bool needSync = caches_.RebuildL1([&activeItems, &cachedItems, baseIndex, weak = WeakClaim(this)](
        int32_t index, CacheItem& cacheItem) -> bool {
            auto repeatNode = weak.Upgrade();
            CHECK_NULL_RETURN(repeatNode, false);
            auto frameNode = AceType::DynamicCast<FrameNode>(cacheItem->node_->GetFrameChildByIndex(0, true));
            if (!frameNode) {
                return false;
            }
            if (activeItems.find(index + baseIndex) != activeItems.end()) {
                frameNode->SetActive(true);
                cacheItem->isL1_ = true;
                cacheItem->isActive_ = true;
                cacheItem->isOnRenderTree_ = true;
                return true;
            } else {
                frameNode->SetActive(false);
                cacheItem->isActive_ = false;
            }
            if (cachedItems.find(index + baseIndex) != cachedItems.end()) {
                cacheItem->isL1_ = true;
                return true;
            }

            cacheItem->isOnRenderTree_ = false;
            cacheItem->isL1_ = false;
            if (cacheItem->node_->OnRemoveFromParent(true)) {
                repeatNode->RemoveDisappearingChild(cacheItem->node_);
            } else {
                repeatNode->AddDisappearingChild(cacheItem->node_);
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

// TS calls this function at the end of rerender to update caches.l1Rid4Index_
// forceRunDoSetActiveRange_ indicates that following DoSetActiveChildRange
// must do a full run even if range is unchanged (which is typically the case).
void RepeatVirtualScroll2Node::UpdateL1Rid4Index(std::map<int32_t, uint32_t>& l1Rd4Index)
{
    caches_.UpdateL1Rid4Index(l1Rd4Index);

    // run next DoSetActiveChild range even if range unchanged
    forceRunDoSetActiveRange_ = true;
}

// fromRepeatItemIndex may not need adapt moveFromTo_
void RepeatVirtualScroll2Node::RequestContainerReLayout(IndexType fromRepeatItemIndex)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "RequestContainerReLayout triggered by Repeat rerender: nodeId: %{public}d."
        "Start re-layout from child index(%{public}d) + startIndex(%{public}d)",
        GetId(), static_cast<int32_t>(fromRepeatItemIndex), startIndex_);

    children_.clear();

    if (fromRepeatItemIndex != INT_MIN) {
        // container children starting from index 0 need to be updated
        if (auto frameNode = GetParentFrameNode()) {
            frameNode->ChildrenUpdatedFrom(fromRepeatItemIndex + startIndex_);
        }
    }

    // do not call when visible items have not changed
    MarkNeedSyncRenderTree(true);

    // do not call when visible items have not changed
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

void RepeatVirtualScroll2Node::NotifyContainerLayoutChange(int32_t index, int32_t count,
    NG::UINode::NotificationType notificationType)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "NotifyContainerLayoutChange triggered by Repeat rerender: nodeId: %{public}d "
        "index: %{public}d, count: %{public}d notificationType: %{public}d",
        static_cast<int32_t>(GetId()), index, count, static_cast<int32_t>(notificationType));

    int64_t accessibilityId = GetAccessibilityId();

    children_.clear();

    auto frameNode = GetParentFrameNode();
    if (frameNode && frameNode->GetTag() == V2::LIST_ETS_TAG) {
        frameNode->NotifyChange(index + startIndex_, count, accessibilityId, notificationType);
    }
}

// called from container layout
// index N-th item
// needBuild: true - if found in cache, then return, if not in cache then return newly build
//            false: - if found in cache, then return, if not found in cache then return nullptr
// isCache: true indicates prebuild item (only used by List/Grid/Waterflow, this item should go to L2 cache,
//          do not add to the tree,
//          isCache==false this item is for display or near display area
// addToRenderTree: true  - set it to active state, call SetActive
RefPtr<UINode> RepeatVirtualScroll2Node::GetFrameChildByIndex(
    uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "nodeId: %{public}d: GetFrameChildByIndex(index: %{public}d, "
        "needBuild:  %{public}d, isCache: %{public}d, "
        "addToRenderTree: %{public}d).",
        static_cast<int32_t>(GetId()), static_cast<int32_t>(index), static_cast<int32_t>(needBuild),
        static_cast<int32_t>(isCache), static_cast<int32_t>(addToRenderTree));

    ACE_SCOPED_TRACE("Repeat.GetFrameChildByIndex index[%d], needBuild[%d] isCache[%d] addToRenderTree[%d]",
        static_cast<int32_t>(index), static_cast<int32_t>(needBuild),
        static_cast<int32_t>(isCache), static_cast<int32_t>(addToRenderTree));

    if (prevRecycleFrom_ > 0 && prevRecycleFrom_ <= static_cast<IndexType>(index) &&
        static_cast<IndexType>(index) < prevRecycleTo_) {
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "REPEAT TRACE ABNORMAL... layout requesting index %{public}d) that was just informed to be recycled.",
            static_cast<int32_t>(index));
    }

    return GetFrameChildByIndexImpl(index, needBuild, isCache, addToRenderTree);
}

RefPtr<UINode> RepeatVirtualScroll2Node::GetFrameChildByIndexImpl(
    uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    std::pair<uint32_t, CacheItem> resultPair = caches_.GetFrameChild(index, needBuild);
    const bool hasNoNode = ((resultPair.first == OnGetRid4IndexResult::NO_NODE)
        || (resultPair.second == nullptr)
        || (resultPair.second->node_ == nullptr));

    if (hasNoNode && !needBuild) {
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "GetFrameChild(%{public}d) not in caches && needBuild==false, GetFrameChildByIndex returns nullptr .",
            static_cast<IndexType>(index));
        return nullptr;
    }

    // node for index needs to be created or updated on JS side
    if (hasNoNode) {
        TAG_LOGE(AceLogTag::ACE_REPEAT,
            "GetFrameChild(%{public}d) failed to create new or update existing node. Non-recoverable error.",
            static_cast<IndexType>(index));
        return nullptr;
    }

    updateFrameChildIndexRecord(index);

    CacheItem& cacheItem4Index = resultPair.second;

    TAG_LOGD(AceLogTag::ACE_REPEAT, "GetFrameChild(%{public}d) returns node %{public}s.",
        static_cast<IndexType>(index), caches_.DumpUINode(cacheItem4Index->node_).c_str());

    cacheItem4Index->node_->UpdateThemeScopeId(GetThemeScopeId());

    if (isActive_) {
        cacheItem4Index->node_->SetJSViewActive(true);
    }

    if (addToRenderTree && !isCache) {
        cacheItem4Index->node_->SetActive(true);
        cacheItem4Index->isActive_ = true;
    }

    if (cacheItem4Index->isOnRenderTree_ && (resultPair.first == OnGetRid4IndexResult::UNCHANGED_NODE)) {
        return cacheItem4Index->node_->GetFrameChildByIndex(0, needBuild);
    }

    // put to render tree
    cacheItem4Index->isOnRenderTree_ = true;

    if (cacheItem4Index->node_->GetDepth() != GetDepth() + 1) {
        cacheItem4Index->node_->SetDepth(GetDepth() + 1);
    }
    // attach to repeat node and pass context to it.
    cacheItem4Index->node_->SetParent(WeakClaim(this));
    if (IsOnMainTree()) {
        cacheItem4Index->node_->AttachToMainTree(false, GetContext());
        // node attached to main tree should not be in disappearing children
        RemoveDisappearingChild(cacheItem4Index->node_);
    }

    MarkNeedSyncRenderTree();
    children_.clear();
    // re-assemble children_
    PostIdleTask();

    auto childNode = cacheItem4Index->node_->GetFrameChildByIndex(0, needBuild);
    if (onMoveEvent_) {
        InitDragManager(AceType::DynamicCast<FrameNode>(childNode));
    }

    return childNode;
}

void RepeatVirtualScroll2Node::updateFrameChildIndexRecord(uint32_t index)
{
    if (needRecordFirstFrameChild_) {
        minFrameChildIndex_ = index;
        maxFrameChildIndex_ = index;
        needRecordFirstFrameChild_ = false;
    } else {
        minFrameChildIndex_ = std::min(minFrameChildIndex_, index);
        maxFrameChildIndex_ = std::max(maxFrameChildIndex_, index);
    }
}

int32_t RepeatVirtualScroll2Node::GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool /*isExpanded*/)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "GetFrameNodeIndex.");
    const std::optional<IndexType>& indexOpt = caches_.GetL1Index4Node(node);
    return indexOpt.has_value() ? indexOpt.value() : -1;
}

const std::list<RefPtr<UINode>>& RepeatVirtualScroll2Node::GetChildren(bool /*notDetach*/) const
{
    if (!children_.empty()) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "Repeat(%{public}d).GetChildren just returns non-empty children_",
            static_cast<int32_t>(GetId()));
        return children_;
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT, "GetChildren rebuild starting ...");

    // can not modify l1_cache while iterating
    // GetChildren is overloaded, can not change it to non-const
    // need to order the child.
    if (!caches_.IsMoveFromToExist()) {
        caches_.ForEachL1Node(
            [&](IndexType index, RIDType rid, const RefPtr<UINode>& node) -> void { children_.emplace_back(node); });
    } else {
        caches_.ForEachL1NodeWithOnMove([&](const RefPtr<UINode>& node) -> void { children_.emplace_back(node); });
    }

    return children_;
}

// called by container layout
// instructs range of L1 items to move to L2, make available for update
// unfortunately, layout gets it occasionally wrong during fast scroll
// makes subsequent GetFrameChildByIndex on an index inside recycle range.
// call forwards to TS onRecycleItems_
void RepeatVirtualScroll2Node::RecycleItems(int32_t from, int32_t to)
{
    if (from + 1 >= to) {
        return;
    }
    if (from == prevRecycleFrom_ && to == prevRecycleTo_) {
        return;
    }
    
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "REPEAT TRACE Repeat(%{public}d: RecycleItems(from: %{public}d to: %{public}d), startIndex: "
        "%{public}d: repeatItem "
        "%{public}d up to smaller than "
        "%{public}d to the reusable items cache",
        static_cast<int32_t>(GetId()), from, to, startIndex_, from - startIndex_, to - startIndex_);

    // swap the ViewStackProcessor instance for secondary and push this node
    // call sequence is C++ -> TS -> JS
    // for TS -> JS to find 'this' node, we need to put 'this' to the 2nd
    // ViewStackProcessor
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    auto* viewStack = NG::ViewStackProcessor::GetInstance();
    viewStack->Push(Referenced::Claim(this));

    onRecycleItems_(from - startIndex_, to - startIndex_);
    
    prevRecycleFrom_ = from;
    prevRecycleTo_ = to;

    TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s \n %{public}s", caches_.DumpUINodeCache().c_str(),
        caches_.DumpL1Rid4Index().c_str());
}

// Purge scheduled as idle task by DoSetActiveChildRange
// enforces L2 cache size limits at the end of processing 'cycle'
// means: L2 cache limits are allowed to be exceeded during one execution 'cycle'
// RecycleItems >>> GetFrameChildByIndex >>> DoSetActiveChildRange >> Purge
// justification: must allow items are put from L1 to L2 but updated and put back to L1 during same cycle
void RepeatVirtualScroll2Node::Purge()
{
    // swap the ViewStackProcessor instance for secondary and push this node
    // call sequence is C++ -> TS -> JS
    // for TS -> JS to find 'this' node, we need to put 'this' to the 2nd
    // ViewStackProcessor
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    auto* viewStack = NG::ViewStackProcessor::GetInstance();
    viewStack->Push(Referenced::Claim(this));

    onPurge_();
}

void RepeatVirtualScroll2Node::SetNodeIndexOffset(int32_t start, int32_t /*count*/)
{
    startIndex_ = start;
}

// called by components, returns min(array length, app-defined totalCount)
// rerender updated app-defined totalCount to totalCount_, array length to arrLen_
// if use onLazyLoading, the value of arrLen transferred from TS side is always equal to totalCount
int32_t RepeatVirtualScroll2Node::FrameCount() const
{
    auto frameCount = std::min(arrLen_, totalCount_);
    TAG_LOGD(AceLogTag::ACE_REPEAT, "FrameCount returns %{public}d", static_cast<int32_t>(frameCount));
    return frameCount;
}

void RepeatVirtualScroll2Node::PostIdleTask()
{
    if (postUpdateTaskHasBeenScheduled_) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT, "Repeat(%{public}d).PostIdleTask Posting idle task",
        static_cast<int32_t>(GetId()));
    postUpdateTaskHasBeenScheduled_ = true;
    auto* context = GetContext();
    CHECK_NULL_VOID(context);

    context->AddPredictTask([weak = AceType::WeakClaim(this)](int64_t /*deadline*/, bool /*canUseLongPredictTask*/) {
        ACE_SCOPED_TRACE("Repeat.IdleTask");
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->postUpdateTaskHasBeenScheduled_ = false;
        TAG_LOGD(AceLogTag::ACE_REPEAT, "Repeat(%{public}d).PostIdleTask idle task calls GetChildren",
            static_cast<int32_t>(node->GetId()));
        node->GetChildren();

        TAG_LOGD(AceLogTag::ACE_REPEAT, "idle task calls Purge");
        node->Purge();
        if (node->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            node->FreezeSpareNode();
        }

        TAG_LOGD(AceLogTag::ACE_REPEAT, " ============ after caches.purge ============= ");
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpUINodeCache().c_str());
        TAG_LOGD(AceLogTag::ACE_REPEAT, "%{public}s", node->caches_.DumpL1Rid4Index().c_str());
        TAG_LOGD(AceLogTag::ACE_REPEAT, " ============ done caches.purge ============= ");
    });
}

void RepeatVirtualScroll2Node::FreezeSpareNode()
{
    caches_.ForEachCacheItem([](RIDType rid, const CacheItem& cachedItem) {
        if (cachedItem && !cachedItem->isL1_) {
            auto& node = cachedItem->node_;
            if (node) {
                TAG_LOGD(AceLogTag::ACE_REPEAT,
                    "spare node %{public}s(%{public}d): apply SetJSViewActive(false)",
                    node->GetTag().c_str(), static_cast<int32_t>(node->GetId()));
                node->SetJSViewActive(false);
            }
        }
    });
}

void RepeatVirtualScroll2Node::OnConfigurationUpdate(const ConfigurationChange& configurationChange)
{
    if ((configurationChange.colorModeUpdate || configurationChange.fontUpdate)) {
        caches_.ForEachCacheItem([&configurationChange](RIDType rid, const CacheItem& cacheItem) {
            if (cacheItem->node_ != nullptr) {
                cacheItem->node_->UpdateConfigurationUpdate(configurationChange);
            }
        });
    }
}

void RepeatVirtualScroll2Node::NotifyColorModeChange(uint32_t colorMode)
{
    caches_.ForEachCacheItem([colorMode, this](RIDType rid, const CacheItem& cacheItem) {
      if (cacheItem->node_ != nullptr) {
          cacheItem->node_->SetMeasureAnyway(GetRerenderable());
          cacheItem->node_->NotifyColorModeChange(colorMode);
      }
    });
}

void RepeatVirtualScroll2Node::SetJSViewActive(bool active, bool isLazyForEachNode, bool isReuse)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "SetJSViewActive ...");
    caches_.ForEachCacheItem([active](RIDType rid, const CacheItem& cacheItem) {
        if (cacheItem->node_ != nullptr) {
            cacheItem->node_->SetJSViewActive(active);
        }
    });
    isActive_ = active;
}

void RepeatVirtualScroll2Node::PaintDebugBoundaryTreeAll(bool flag)
{
    caches_.ForEachCacheItem([flag](RIDType rid, const CacheItem& cacheItem) {
        if (cacheItem->node_ != nullptr) {
            cacheItem->node_->PaintDebugBoundaryTreeAll(flag);
        }
    });
}

void RepeatVirtualScroll2Node::SetOnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    if (onMove && !onMoveEvent_) {
        TAG_LOGI(AceLogTag::ACE_REPEAT, "activate onMove");
        InitAllChildrenDragManager(true);
    } else if (!onMove && onMoveEvent_) {
        TAG_LOGI(AceLogTag::ACE_REPEAT, "deactivate onMove");
        InitAllChildrenDragManager(false);
    }
    onMoveEvent_ = onMove;
}

void RepeatVirtualScroll2Node::SetItemDragHandler(std::function<void(int32_t)>&& onLongPress,
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

void RepeatVirtualScroll2Node::MoveData(int32_t from, int32_t to)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "MoveData from: %{public}d to: %{public}d.", from, to);
    caches_.UpdateMoveFromTo(from, to);
    onMoveFromTo_(from, to);
    children_.clear();
    PostIdleTask();
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void RepeatVirtualScroll2Node::FireOnMove(int32_t from, int32_t to)
{
    TAG_LOGI(AceLogTag::ACE_REPEAT, "FireOnMove from: %{public}d to: %{public}d.", from, to);
    caches_.ResetMoveFromTo();
    // -1 used to reset moveFromTo_ in TS.
    onMoveFromTo_(-1, -1);
    ForEachBaseNode::FireOnMove(from, to);
}


void RepeatVirtualScroll2Node::InitDragManager(const RefPtr<FrameNode>& child)
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

void RepeatVirtualScroll2Node::InitAllChildrenDragManager(bool init)
{
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        return;
    }
    const auto& children = GetChildren();
    for (const auto& child : children) {
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

RefPtr<FrameNode> RepeatVirtualScroll2Node::GetFrameNode(int32_t index)
{
    return AceType::DynamicCast<FrameNode>(GetFrameChildByIndex(index, false, false));
}
} // namespace OHOS::Ace::NG
