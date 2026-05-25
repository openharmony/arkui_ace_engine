/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_INFO_H

#include <cstdint>
#include <deque>
#include <map>
#include <memory>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_pattern.h"

namespace OHOS::Ace {

class JsonValue;

namespace NG {

class LazyWaterFlowLayoutAlgorithm;
class LazyWaterFlowLayoutPattern;

struct LazyWaterFlowItemMainPos {
    int32_t laneIdx = 0;
    float startPos = 0.0f;
    float endPos = 0.0f;
};

struct LazyWaterFlowLaneItem {
    int32_t idx = -1;
    float mainSize = 0.0f;
    // Leading offset relative to the previous item / lane head; SyncItemPositions collapses the head
    // item's startOffset into lane.startPos.
    float startOffset = 0.0f;
};

struct LazyWaterFlowLane {
    float startPos = 0.0f;
    float endPos = 0.0f;
    std::deque<LazyWaterFlowLaneItem> items_;
};

// Visible-range anchor snapshot. Shared between LayoutInfo's pending* (captured pre-NotifyDataChange) and
// Algorithm's PrevFrameSnapshot (captured at Measure entry); UpdateAdjustOffset diffs new positions against it.
struct LazyWaterFlowAnchorSnapshot {
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    std::optional<LazyWaterFlowItemMainPos> startPos;
    std::optional<LazyWaterFlowItemMainPos> endPos;
    float totalMainSize = 0.0f;
};

// State backend shared by Algorithm and Pattern: lane geometry, data-change decisions, total-height
// estimates, visible / cache index windows.
class ACE_EXPORT LazyWaterFlowLayoutInfo : public AceType {
    DECLARE_ACE_TYPE(LazyWaterFlowLayoutInfo, AceType);

public:
    // newStartIndex_ sentinels:
    //   EMPTY   -- no data change captured this frame.
    //   INVALID -- change touched the retained window; index-remap fast path no longer applies.
    static constexpr int32_t EMPTY_NEW_START_INDEX = -1;
    static constexpr int32_t INVALID_NEW_START_INDEX = -2;

    void ResetPerFrameState();
    void ResetItemSizeCache();
    void SetTotalItemCount(int32_t count);
    void SetPosMap(int32_t index, const LazyWaterFlowItemMainPos& pos);
    const LazyWaterFlowItemMainPos* GetPos(int32_t index) const;
    void CacheItemHeight(int32_t index, float height);
    std::optional<float> GetCachedHeight(int32_t index) const;
    void EstimateItemSize();
    float GetAverageItemHeight() const;
    void NotifyDataChange(int32_t index, int32_t count);
    void ClearDataChanges();
    /**
     * @brief Update lane cross-sizes and report whether a topology rebuild is needed.
     *
     * @return true when caller must follow up with ResetLanes (lanes_ already cleared internally).
     */
    bool UpdateLaneCrossLens(const std::vector<double>& laneCrossLens);
    void UpdateVisibleRange(float viewStart, float viewEnd);
    void UpdateCachedRange(float cacheStart, float cacheEnd);
    /**
     * @brief Forward gap between min(lane.endPos) and cacheEndPos_; signals Pattern to post a predict task.
     */
    bool NeedPredict() const;
    void DumpAdvanceInfo();
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json);
    void ResetLanes(int32_t laneCount, std::optional<float> laneBasePos);
    /**
     * @brief Reset lane base while preserving lane count.
     *
     * @param laneBasePos nullopt prefers the retained front lane's startPos (falls back to 0 when all empty).
     */
    void ResetWithLaneOffset(std::optional<float> laneBasePos);
    /**
     * @brief Shift lane.items_[i].idx by (newStartIndex_ - StartIndex()) to complete the index-remap preserve.
     */
    void UpdateLanesIndex(int32_t updateIdx = 0);
    /**
     * @brief Flatten lane-local state into posMap_ and refresh laneEndPos_.
     */
    void SyncItemPositions(float mainGap);
    int32_t StartIndex() const;
    int32_t EndIndex() const;
    /**
     * @brief Truncate every lane's tail starting at index; refresh idxToLane_ / idxToHeight_.
     */
    void ClearDataFrom(int32_t index, float mainGap);
    const LazyWaterFlowLane* GetLane(int32_t itemIdx) const;
    LazyWaterFlowLane* GetMutableLane(int32_t itemIdx);

    /**
     * @brief Recompute totalOffset_ from the retained front lane and virtual prefix.
     */
    void EstimateTotalOffset(int32_t prevStart, int32_t startIdx, float mainGap);
    /**
     * @brief Retained window geometry + average-based estimate for items past EndIndex().
     */
    float EstimateTotalHeight(float mainGap) const;
    /**
     * @brief Average-based absorbed length of items [startBound, endBound] across all lanes.
     */
    float EstimateSectionHeight(float average, int32_t startBound, int32_t endBound, float mainGap) const;

    void ResetAllBoundaryFlags();
    void ResetBoundaryLatch();

    /**
     * @brief Shared epilogue for CheckReset's data-change action paths: EstimateTotalOffset + ResetBoundaryLatch.
     */
    void FinalizeAfterDataChangeReset(int32_t prevStart, int32_t newStart, float mainGap);

private:
    std::pair<float, float> GetLayoutedRange() const;
    void CapturePendingAdjustAnchor();
    void ClearPendingAdjustAnchor();
    bool PrepareNewStartIndex();
    void InvalidateChangedItemCache(int32_t index);
    void AdjustUpdateIdxForDataChange(int32_t index, int32_t count);
    void ShiftUpdateIdxForStructuralChange(int32_t index, int32_t count);
    int32_t DeriveWindowDirtyCandidate(int32_t index, int32_t count) const;
    void TransformItemSizeCacheAfterDataChange(int32_t index, int32_t count);
    /**
     * @brief Re-key lanes_ / idxToLane_ when topology is stable. Mutually exclusive with the
     * preserveByIndexRemap branch (UpdateLanesIndex applies the same diff later).
     */
    void TransformLaneCacheAfterDataChange(int32_t index, int32_t count);
    void TransformStoredIndexesAfterDataChange(int32_t index, int32_t count);
    void ResetForFullRebuild();
    void TrimToTotalItemCount();
    float ResolveLaneFrontPos() const;

    // ---------------------------- State fields ----------------------------

    std::map<int32_t, LazyWaterFlowItemMainPos> posMap_;
    std::unordered_map<int32_t, float> idxToHeight_;
    std::vector<LazyWaterFlowLane> lanes_;
    std::unordered_map<int32_t, size_t> idxToLane_;
    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    int32_t totalItemCount_ = 0;
    // Header / footer main-axis sizes; the header counts toward the lane internal coords' baseline at 0.
    float headerMainSize_ = 0.0f;
    float footerMainSize_ = 0.0f;
    float totalMainSize_ = 0.0f;
    float estimateItemSize_ = -1.0f;
    AdjustOffset adjustOffset_ {};
    int32_t layoutedStartIndex_ = -1;
    int32_t layoutedEndIndex_ = -1;
    float cacheStartPos_ = 0.0f;
    float cacheEndPos_ = 0.0f;
    // Real viewport plus parent-provided viewExt, excluding this component's own cache expansion.
    float extendedViewStartPos_ = 0.0f;
    float extendedViewEndPos_ = Infinity<float>();
    int32_t cachedStartIndex_ = -1;
    int32_t cachedEndIndex_ = -1;
    // Set => current Measure is a PredictPass; Algorithm enables deadline checks.
    std::optional<int64_t> deadline_;
    std::vector<float> crossLens_;
    std::vector<float> laneEndPos_;
    bool hasDataChange_ = false;
    int32_t updatedStart_ = -1;
    // Where StartIndex() maps to after this frame's accumulated changes. See sentinel comment above.
    int32_t newStartIndex_ = EMPTY_NEW_START_INDEX;
    // Logical offset of the retained window's front relative to the virtual content origin.
    float totalOffset_ = 0.0f;
    // Greatest content height ever observed (high-water). Reset when a preserve-unsafe change forces rebuild.
    float maxHeight_ = 0.0f;
    // Boundary edge-trigger: itemStart_ / itemEnd_ are this frame's observation; prev* are the cross-frame latch.
    bool itemStart_ = false;
    bool itemEnd_ = false;
    bool prevItemStart_ = false;
    bool prevItemEnd_ = false;
    bool hasPendingAdjustAnchor_ = false;
    LazyWaterFlowAnchorSnapshot pendingAnchor_;
    std::map<int32_t, LazyWaterFlowItemMainPos> pendingVisiblePositions_;

    friend class LazyWaterFlowLayoutAlgorithm;
    friend class LazyWaterFlowLayoutPattern;
};

} // namespace NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_INFO_H
