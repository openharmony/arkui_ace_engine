/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_NODE_H

#include <cstdint>
#include <list>
#include <string>
#include <functional>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/for_each_base_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_caches.h"

namespace OHOS::Ace::NG {
struct OffscreenItems {
    int32_t from = -1;
    int32_t to = -1;
};

class ACE_EXPORT RepeatVirtualScrollNode : public ForEachBaseNode {
    DECLARE_ACE_TYPE(RepeatVirtualScrollNode, ForEachBaseNode);

public:
    static RefPtr<RepeatVirtualScrollNode> GetOrCreateRepeatNode(int32_t nodeId, uint32_t totalCount,
        const std::map<std::string, std::pair<bool, uint32_t>>& templateCachedCountMap,
        const std::function<void(uint32_t)>& onCreateNode,
        const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
        const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
        const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range,
        const std::function<void(int32_t, int32_t)>& onSetActiveRange);

    RepeatVirtualScrollNode(int32_t nodeId, int32_t totalCount,
        const std::map<std::string, std::pair<bool, uint32_t>>& templateCacheCountMap,
        const std::function<void(uint32_t)>& onCreateNode,
        const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
        const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
        const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range,
        const std::function<void(int32_t, int32_t)>& onSetActiveRange);

    ~RepeatVirtualScrollNode() override = default;

    void UpdateTotalCount(uint32_t totalCount);

    // Number of children that Repeat can product
    // returns TotalCount
    int32_t FrameCount() const override;

    // called from TS upon Repeat rerender
    void UpdateRenderState(bool visibleItemsChanged);

    /**
     * GetChildren re-assembles children_ and cleanup the L1 cache
     * active items remain in L1 cache and are added to RepeatVirtualScroll.children_
     * inactive items are moved from L1 to L2 cache, not added to children_
     * function returns children_
     * function runs as part of idle task
     */
    const std::list<RefPtr<UINode>>& GetChildren(bool notDetach = false) const override;

    void OnRecycle() override;
    void OnReuse() override;

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
    RefPtr<FrameNode> GetFrameNode(int32_t index) override;
    int32_t GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool isExpanded = true) override;
    void InitDragManager(const RefPtr<UINode>& childNode);
    void InitAllChildrenDragManager(bool init);

    void OnConfigurationUpdate(const ConfigurationChange& configurationChange) override;

    void SetJSViewActive(bool active = true, bool isLazyForEachNode = false, bool isReuse = false) override
    {
        const auto& children = caches_.GetAllNodes();
        for (const auto& [key, child] : children) {
            child.item->SetJSViewActive(active);
        }
        isActive_ = active;
    }
    void PaintDebugBoundaryTreeAll(bool flag) override
    {
        const auto& children = caches_.GetAllNodes();
        for (const auto& [key, child] : children) {
            child.item->PaintDebugBoundaryTreeAll(flag);
        }
    }
    void SetIsLoop(bool isLoop)
    {
        isLoop_ = isLoop;
    }
protected:
    void UpdateChildrenFreezeState(bool isFreeze, bool isForceUpdateFreezeVaule = false) override;
private:
    void PostIdleTask();

    // try to find entry for given index in L1 or L2 cache
    RefPtr<UINode> GetFromCaches(uint32_t forIndex)
    {
        return caches_.GetCachedNode4Index(forIndex);
    }

    // get farthest (from L1 indexes) index in L2 cache or -1
    int32_t GetFarthestL2CacheIndex();

    // drop UINode with given key from L1 but keep in L2
    // detach from tree and request tree sync
    void DropFromL1(const std::string& key);

    // check whether UINode (index) is in the L1 cache range
    bool CheckNode4IndexInL1(int32_t index, int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd,
        RefPtr<FrameNode>& frameNode);

    // process params sent by parent
    void CheckActiveRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd);

    // RepeatVirtualScrollNode is not instance of FrameNode
    // needs to propagate active state to all items inside
    bool isActive_ = true;

    // size of data source when all data items loaded
    uint32_t totalCount_ = 0;

    // loop property of the parent container
    bool isLoop_ = false;

    // caches:
    mutable RepeatVirtualScrollCaches caches_;

    // get active child range
    std::function<void(int32_t, int32_t)> onSetActiveRange_;

    // used by one of the unknown functions
    std::list<std::string> ids_;

    // re-assembled by GetChildren called from idle task
    mutable std::list<RefPtr<UINode>> children_;

    // true in the time from requesting idle / predict task until exec predict tsk.
    bool postUpdateTaskHasBeenScheduled_;

    // STATE_MGMT_NOTE: What are these?
    OffscreenItems offscreenItems_;
    int32_t startIndex_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(RepeatVirtualScrollNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_NODE_H
