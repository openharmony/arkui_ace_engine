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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_LAZY_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_LAZY_NODE_H
#include <cstdint>
#include <functional>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/unique_valued_map.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/syntax/for_each_base_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace {
constexpr int64_t CACHE_TASK_DELAY_TIME = 2000000000;
constexpr int32_t MEMORY_LEVEL_LOW = 1;
constexpr int32_t MEMORY_LEVEL_CRITICAL = 2;
}

namespace OHOS::Ace::NG {


struct LazyForEachOptions {
    LazyForEachCustomComponentFreezeMode customComponentFreezeMode;
    LazyForEachReleaseStrategy releaseStrategy;
    LazyForEachMemOptStrategy memOptStrategy;
};

enum class RepeatMemoryOptimizationStrategy : int32_t {
    DEFAULT = 0,
    ENABLE_AUTO_CACHE_OPTIMIZATION = 1,
};

struct ActiveRangeParam {
    int32_t start;
    int32_t end;
    int32_t cacheStart;
    int32_t cacheEnd;

    bool operator==(const ActiveRangeParam& other) const
    {
        return std::tie(start, end, cacheStart, cacheEnd) ==
               std::tie(other.start, other.end, other.cacheStart, other.cacheEnd);
    }
};

/**
 * @brief Backend node representation to access and manage lazy items in Arkoala frontend
 *
 */
class ArkoalaLazyNode : public ForEachBaseNode {
    DECLARE_ACE_TYPE(ArkoalaLazyNode, ForEachBaseNode);

public:
    explicit ArkoalaLazyNode(int32_t id, bool isRepeat = false);
    ~ArkoalaLazyNode() override;
    void RegisterArkoalaLazyNode();

    using CreateItemCb = std::function<RefPtr<UINode>(int32_t)>;
    using UpdateRangeCb = std::function<void(int32_t, int32_t, int32_t, int32_t, bool)>;
    using ClearCacheCb = std::function<void()>;
    using releaseItemByIndexCb = std::function<void(int32_t)>;

    void SetTotalCount(int32_t value)
    {
        totalCount_ = value;
    }

    void SetCallbacks(CreateItemCb create, UpdateRangeCb update, ClearCacheCb clearer, releaseItemByIndexCb release)
    {
        createItem_ = std::move(create);
        updateRange_ = std::move(update);
        clearCache_ = std::move(clearer);
        releaseItemByIndex_ = std::move(release);
    }

    void MoveData(int32_t from, int32_t to, bool isNeedUpdate = false) final;

    RefPtr<FrameNode> GetFrameNode(int32_t index) final;

    RefPtr<UINode> GetChildByIndex(int32_t index);

    RefPtr<UINode> GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree) override;

    void DoRemoveChildInRenderTree(uint32_t index, bool isAll) final
    {
        LOGI("Koala lazyForEach: doRemove called %u. Not implemented", index);
    }
    void DoSetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache) final;

    bool IsAtomicNode() const final
    {
        return false;
    }

    int32_t FrameCount() const final
    {
        return totalCount_;
    }

    void SetIsLoop(bool isLoop)
    {
        isLoop_ = isLoop;
    }

    void SetOptions(LazyForEachOptions options)
    {
        options_ = options;
        if (options_.memOptStrategy == LazyForEachMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION ||
            repeatMemoryOptimizationStrategy_ == RepeatMemoryOptimizationStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION) {
            RegisterWindowStateChangedCallback();
            RegisterMemoryLevelChangedCallback();
            PostMemOptTask();
        }
    }

    /**
     * GetChildren re-assembles children_ and cleanup the L1 cache
     * active items remain in L1 cache and are added to RepeatVirtualScroll.children_
     * inactive items are moved from L1 to L2 cache, not added to children_
     * function returns children_
     * function runs as part of idle task
     */
    const std::list<RefPtr<UINode>>& GetChildren(bool notDetach = false) const override;

    void RecycleItems(int32_t from, int32_t to) final
    {
        /* not implemented yet */
    }

    void OnDataChange(int32_t changeIndex, int32_t count, NotificationType type);

    void SetJSViewActive(bool active = true, bool isLazyForEachNode = false,
        bool isReuse = false, bool suppressActiveLifecycle = false) override;

    void BuildAllChildren();

    // used for drag move operation.
    void SetOnMove(std::function<void(int32_t, int32_t)>&& onMove);
    void SetOnMoveFromTo(std::function<void(int32_t, int32_t)>&& onMoveFromTo);
    void SetItemDragEvent(std::function<void(int32_t)>&& onLongPress, std::function<void(int32_t)>&& onDragStart,
        std::function<void(int32_t, int32_t)>&& onMoveThrough, std::function<void(int32_t)>&& onDrop);
    void FireOnMove(int32_t from, int32_t to) override;
    void InitDragManager(const RefPtr<FrameNode>& childNode);
    void InitAllChildrenDragManager(bool init);
    int32_t GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool isExpanded = true) override;

    void DumpInfo() override;

    void OnWindowShow() override;
    void OnWindowHide() override;
    void OnNotifyMemoryLevel(int32_t level) override;
    void RegisterWindowStateChangedCallback();
    void UnregisterWindowStateChangedCallback();
    void RegisterMemoryLevelChangedCallback();
    void UnregisterMemoryLevelChangedCallback();
    bool CheckParentFrameNodeVisibility();
    void ScheduleCleanCacheTask();
    void ScheduleRestoreCacheTask();
    void TryExecuteScheduledCacheTask();
    void CleanCache(bool syncClean);
    void RestoreCache();
    void SetNeedPrebuild(bool needPrebuild);
    bool GetNeedPrebuild();
    void SetParentVisibility(bool visibility);
    bool GetParentVisibility();
    void PostMemOptTask();

    void SetRepeatMemoryOptimizationStrategy(int32_t strategy);

private:
    RefPtr<UINode> GetFrameChildByIndexImpl(int32_t index, bool needBuild, bool isCache, bool addToRenderTree);
    void RebuildCache();
    bool IsInActiveRange(int32_t index, const ActiveRangeParam& param) const;
    bool IsInCacheRange(int32_t index, const ActiveRangeParam& param) const;
    void UpdateIsCache(const RefPtr<UINode>& node, bool isCache, bool shouldTrigger = true);

    void UpdateMoveFromTo(int32_t from, int32_t to);
    void UpdateItemsForOnMove();
    void ResetMoveFromTo()
    {
        moveFromTo_.reset();
    }

    // convert index by moveFromTo_.
    int32_t ConvertFromToIndex(int32_t index) const;
    // revert converted-index to origin index.
    int32_t ConvertFromToIndexRevert(int32_t index) const;

    void RequestSyncTree();
    void PostIdleTask();

    /**
     * iterate over L1 items and call cbFunc for each
     * cbFunction is NOT allowed to add to or remove items from L1
     */
    void ForEachL1Node(const std::function<void(int32_t index, const RefPtr<UINode>& node)>& cbFunc) const;
    void ForEachL1NodeWithOnMove(const std::function<void(const RefPtr<UINode>& node)>& cbFunc) const;

    std::string DumpUINode(const RefPtr<UINode>& node) const;

    void SetNeedBuildAll(const bool needBuildAll)
    {
        needBuildAll_ = needBuildAll;
    }

    /**
     * Check if the node at given index should be purged from cache.
     * Returns true if the node is not in the cache range and should be removed.
     */
    void PurgeNode();

    void RemovingExpiringItem(int64_t deadline);

    std::list<RefPtr<UINode>> removingNodeList_;

    // false if in LazyForEach, true if in Repeat
    bool isRepeat_ = false;
    // ArkoalaLazyNode is not instance of FrameNode, needs to propagate active state to all items inside
    bool isActive_ = true;
    // true if in Swiper loop mode
    bool isLoop_ = false;
    ActiveRangeParam activeRangeParam_ = { -1, -1, -1, -1 };
    // true if parent isn't scroll container
    bool needBuildAll_ = true;

    UniqueValuedMap<int32_t, RefPtr<UINode>, WeakPtr<UINode>::Hash> node4Index_;
    CreateItemCb createItem_;
    UpdateRangeCb updateRange_;
    ClearCacheCb clearCache_;
    releaseItemByIndexCb releaseItemByIndex_;
    int32_t totalCount_ = 0;

    // re-assembled by GetChildren called from idle task
    mutable std::list<RefPtr<UINode>> children_;

    // for tracking reused/recycled nodes
    std::unordered_set<int32_t> recycleNodeIds_;

    std::unordered_set<int32_t> sparedIdx_;

    // true in the time from requesting idle / predict task until exec predict task.
    bool postUpdateTaskHasBeenScheduled_ = false;

    std::function<void(int32_t, int32_t)> onMoveFromTo_;
    // record (from, to), only valid during dragging item.
    std::optional<std::pair<int32_t, int32_t>> moveFromTo_;
    LazyForEachOptions options_ = { LazyForEachCustomComponentFreezeMode::AUTO, LazyForEachReleaseStrategy::BATCH,
        LazyForEachMemOptStrategy::DEFAULT};
    bool pendingCleanCache_ = false;
    bool pendingRestoreCache_ = false;
    bool isParentVisible_ = false;
    bool needPreBuild_ = false;
    int64_t cacheTaskPostTime_ = 0;
    int64_t setActiveRangeTime_ = 0;

    RepeatMemoryOptimizationStrategy repeatMemoryOptimizationStrategy_ =
      RepeatMemoryOptimizationStrategy::DEFAULT;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_LAZY_NODE_H
