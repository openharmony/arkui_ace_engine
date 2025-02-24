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

/**
 * Repeat virtual scroll framework implementation design
 * outline of RepeatVirtualScroll2Node and RepeatVirtualScroll2Caches C++ helper class
 * for documentation of TS see state_mgmt/src/lib/partial_update/pu_repeat_virtual_scroll_impl.ts
 *
 * 1. scenario: scroll
 * ===================
 *
 * Container Layout calls RepeatVirtualScroll2Node::RecycleItems(int32_t from, int32_t to)
 * 1.1 forwards the call to TS onRecycleItems_(from, to)
 *
 * Layout calls RepeatVirtualScroll2Node::GetFrameChildByIndex(index, ....) several times
 * 2.1 forward call to RepeatVirtualScroll2Caches::GetFrameChild(index)
 * 2.2 if UINode for this index in L1, use it
 * 2.3 if no UINode for this index in L1, call TS by calling onGetRid4Index_(index) lambda
 *   three result cases for onGetRid4Index_ function:
 *   - TS has newly rendered UINode sub-tree, add the cache and the L1, return UINode
 *   - TS has update a UINode subtree, add to L1, return UINode
 *   - TS failed to JS render, return nullptr
 *
 * Layout calls RepeatVirtualScroll2Node::DoSetActiveChildRange(....)
 * 3.1 if range unchanged and not force run full activeRange after rerender, skip.
 * 3.2 forward call to TS by calling onActiveRange_ lambda
 * 3.3 iterate over L1 to check or each UINode if still in active range.
 * 3.4 iterate over entire (L1 + L2) cache to set active status and remove from render tree
 *     of items moved to L2 by rerender.
 *
 * 4. purge (idle task) triggered by DoSetActiveChildRange
 * 4.1 iterate the cache and enforce cache size limits (forwards to TS)
 *
 * 2. scenario Repeat rerender
 * ============================
 *
 * owning ViewV2.Updateelement calls __RepeatVirtualScrollImpl.rerender()
 * all processing on TS side, see TS documentation
 * rerender finishes with updateL1Rid4Index call C++ as shown below.
 *
 *  C++ lambdas to call these TS functions
 *     onGetRid4Index: (forIndex: number) => [number, number],
 *     onRecycleItems: (fromIndex: number, toIndex: number) => void,
 *     onActiveRange: (fromIndex: number, toIndex: number, isLoop: boolean) => void,
 *     onMoveFromTo: (moveFrom: number, moveTo: number) => void,
 *     onPurge: () => void;
 *     onMoveHandler: (from: number, to: number) => void;
 *
 * C++ functions exposed to JS
 * (compare RepeatVirtualScrollNative class in pu_foreach.d.ts, JS interface in js_virtual_scroll.cpp/h,
 *  model implementation in virtual_scroll_model_ng.cpp/h)
 *
 * TS RemoveNode(rid: number): void  -->  C++ RepeatVirtualScroll2Node::RemoveNode(rid)   used by onPurge
 * TS setInvalid(repeatElmtId: number, rid: number): void;  --> RepeatVirtualScroll2Node::SetInvalid(rid)
 * TS requestContainerReLayout(repeatElmtId: number, totalCount: number,
 *     invalidateContainerLayoutFromChildIndex: number): void -->
 *       C++ RepeatVirtualScroll2Node::SetTotalCount(totalCount)
 *       C++ RepeatVirtualScroll2Node::RequestContainerReLayout(invalidateContainerLayoutFromChildIndex)
 * TS  updateL1Rid4Index(repeatElmtId: number, totalCount: number, invalidateContainerLayoutFromChildIndex: number,
 *    l1rid4index: Array<Array<number>>): void -->
 *    C++ RepeatVirtualScroll2Node::SetTotalCount(totalCount)
 *    C++ RepeatVirtualScroll2Node::UpdateL1Rid4Index(std::map<int32_t, uint32_t>& l1Rd4Index);
 *    C++ RepeatVirtualScroll2Node::RequestContainerReLayout(invalidateContainerLayoutFromChildIndex)
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_NODE_H

#include <cstdint>
#include <list>
#include <string>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/for_each_base_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_caches.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RepeatVirtualScroll2Node : public ForEachBaseNode {
    DECLARE_ACE_TYPE(RepeatVirtualScroll2Node, ForEachBaseNode);

public:
    static RefPtr<RepeatVirtualScroll2Node> GetOrCreateRepeatNode(int32_t nodeId, uint32_t totalCount,
        const std::function<std::pair<RIDType, uint32_t>(IndexType)>& onGetRid4Index,
        const std::function<void(IndexType, IndexType)>& onRecycleItems,
        const std::function<void(int32_t, int32_t, bool)>& onActiveRange,
        const std::function<void(IndexType, IndexType)>& onMoveFromTo,
        const std::function<void()>& onPurge);

    RepeatVirtualScroll2Node(int32_t nodeId, int32_t totalCount,
        const std::function<std::pair<RIDType, uint32_t>(IndexType)>& onGetRid4Index,
        const std::function<void(IndexType, IndexType)>& onRecycleItems,
        const std::function<void(int32_t, int32_t, bool)>& onActiveRange,
        const std::function<void(IndexType, IndexType)>& onMoveFromTo,
        const std::function<void()>& onPurge);

    ~RepeatVirtualScroll2Node() override = default;

    void UpdateTotalCount(uint32_t totalCount)
    {
        totalCount_ = totalCount;
    }

    // Number of children that Repeat can product
    // returns TotalCount
    int32_t FrameCount() const override;

    // called from TS upon Repeat rerender
    // tell the Container to invalid its layout
    // incl re-layout of children start from startIndex
    void RequestContainerReLayout(IndexType startIndex);

    /**
     * GetChildren re-assembles children_ and cleanup the L1 cache
     * active items remain in L1 cache and are added to RepeatVirtualScroll.children_
     * inactive items are moved from L1 to L2 cache, not added to children_
     * function returns children_
     * function runs as part of idle task
     */
    const std::list<RefPtr<UINode>>& GetChildren(bool notDetach = false) const override;

    /**
     * scenario: called by layout informs:
     *   - start: the first visible index
     *   - end: the last visible index
     *   - cacheStart: number of items cached before start
     *   - cacheEnd: number of items cached after end
     *
     * Total L1 cache includes items from start-cacheStart to end+cacheEnd,
     * but the active items are only start...end.
     *
     * those items with index in range [ start ... end ] are marked active
     * those out of range marked inactive.
     *
     * those items out of cached range are removed from L1
     * requests idle task
     */
    void DoSetActiveChildRange(
        int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache = false) override;

    /**
     * those items with index in cachedItems are marked active
     * those items with index in cachedItems are marked inactive
     * baseIndex is repeat first node index
     */
    void DoSetActiveChildRange(
        const std::set<int32_t>& activeItems, const std::set<int32_t>& cachedItems, int32_t baseIndex) override;

    // largely unknown when it is expected to be called
    // meant to inform which items with index [ from .. to ] can be recycled / updated
    void RecycleItems(int32_t from, int32_t to) override;

    // Called by parent generate frame child.
    void SetNodeIndexOffset(int32_t start, int32_t count) override;

    /** Called by Layout to request ListItem and child subtree
     for given index
     either returns existing item for index from L1 or L2 cache, or gets a new item created
     update of L2 cache item to new index)
     result is in L1 cache if isCache is false, and L2 cache if isCache is true.

     meaning of parameters
     needBuild: true - if found in cache, then return, if not in cache then return newly build
                false: - if found in cache, then return, if not found in cache then return nullptr
     isCache: true indicates prebuild item (only used by List/Grid/Waterflow, this item should go to L2 cache,
            do not add to the tree,
            isCaxche==false this item is for display or near display area
    addToRenderTree: true  - set it to active state, call SetActive
    */
    RefPtr<UINode> GetFrameChildByIndex(
        uint32_t index, bool needBuild, bool isCache = false, bool addToRenderTree = false) override;

    bool IsAtomicNode() const override
    {
        return false;
    }

    // used for drag move operation.
    void SetOnMove(std::function<void(int32_t, int32_t)>&& onMove);
    void MoveData(int32_t from, int32_t to) override;
    void FireOnMove(int32_t from, int32_t to) override;
    void InitDragManager(const RefPtr<FrameNode>& childNode);
    void InitAllChildrenDragManager(bool init);
    RefPtr<FrameNode> GetFrameNode(int32_t index) override;
    int32_t GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool isExpanded = true) override;

    void OnConfigurationUpdate(const ConfigurationChange& configurationChange) override;

    void SetJSViewActive(bool active = true, bool isLazyForEachNode = false, bool isReuse = false) override;
    void PaintDebugBoundaryTreeAll(bool flag) override;

    void RemoveNode(RIDType rid)
    {
        caches_.RemoveNode(rid);
    }

    void SetInvalid(RIDType rid)
    {
        caches_.SetInvalid(rid);
    }

    //  TS call JS to update caches.l1Rid4Index_
    // and invalidate container layout following a
    // Repeat.rerender
    void UpdateL1Rid4Index(std::map<int32_t, uint32_t>& l1Rd4Index);


    void SetIsLoop(bool isLoop)
    {
        isLoop_ = isLoop;
    }

private:
    RefPtr<UINode> GetFrameChildByIndexImpl(
        uint32_t index, bool needBuild, bool isCache, bool addToRenderTree);

    bool RebuildL1(int32_t start, int32_t end, int32_t nStart, int32_t nEnd);
    bool ProcessActiveL2Nodes();

    void RequestSyncTree();
    void PostIdleTask();

    // tell TS to purge nodes exceeding cachedCount
    void Purge();

    // check whether index is in the L1 cache range
    bool CheckNode4IndexInL1(
        int32_t index, int32_t nStart, int32_t nEnd, RepeatVirtualScroll2Caches::CacheItem& cacheItem);

    // process params sent by parent
    ActiveRangeType CheckActiveRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd);

    // RepeatVirtualScroll2Node is not instance of FrameNode
    // needs to propagate active state to all items inside
    bool isActive_ = true;

    // size of data source when all data items loaded
    uint32_t totalCount_ = 0;

    // loop property of the parent container
    bool isLoop_ = false;
    
    // caches:
    mutable RepeatVirtualScroll2Caches caches_;

    // used by one of the unknown functions
    std::list<std::string> ids_;

    // re-assembled by GetChildren called from idle task
    mutable std::list<RefPtr<UINode>> children_;

    int32_t startIndex_ = 0;

    // memorize parameters of previous DoSetActiveRange class
    // to skip processing if params unchanged
    int32_t prevActiveRangeStart_ = 0;
    int32_t prevActiveRangeEnd_ = -1;

    // remove from final version
    int32_t prevRecycleFrom_ = -1;
    int32_t prevRecycleTo_ = -1;

    // run next DoSetActiveChild range even if range unchanged
    bool forceRunDoSetActiveRange_ = false;

    std::function<void(IndexType, IndexType)> onRecycleItems_;
    std::function<void(int32_t, int32_t, bool)> onActiveRange_;
    std::function<void(IndexType, IndexType)> onMoveFromTo_;
    std::function<void()> onPurge_;

    // true in the time from requesting idle / predict task until exec predict tsk.
    bool postUpdateTaskHasBeenScheduled_;

    ACE_DISALLOW_COPY_AND_MOVE(RepeatVirtualScroll2Node);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_NODE_H
