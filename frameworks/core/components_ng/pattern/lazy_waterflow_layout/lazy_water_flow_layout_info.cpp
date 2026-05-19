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

#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_info.h"

#include <algorithm>
#include <cmath>
#include <limits>

#include "base/log/ace_trace.h"
#include "base/json/json_util.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

// Pipeline bridge helpers; kept here so other TUs need not include pipeline_context.h.
void AddLazyWaterFlowPredictTask(PipelineContext* context, std::function<void(int64_t, bool)>&& task)
{
    CHECK_NULL_VOID(context);
    context->AddPredictTask(std::move(task));
}

void SetLazyWaterFlowCallbackNode(FrameNode* frameNode)
{
    PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
}


namespace {
template<typename T>
void EraseFrom(int32_t index, std::unordered_map<int32_t, T>& hashTable)
{
    for (auto it = hashTable.begin(); it != hashTable.end();) {
        if (it->first >= index) {
            it = hashTable.erase(it);
        } else {
            ++it;
        }
    }
}

std::optional<int32_t> TransformIndexOnDataChange(int32_t itemIndex, int32_t changeIndex, int32_t count)
{
    if (itemIndex < 0) {
        return std::nullopt;
    }
    if (count > 0) {
        return itemIndex >= changeIndex ? itemIndex + count : itemIndex;
    }

    const auto deletedCount = -count;
    const auto deleteEnd = changeIndex + deletedCount;
    if (itemIndex < changeIndex) {
        return itemIndex;
    }
    if (itemIndex >= deleteEnd) {
        return itemIndex + count;
    }
    return std::nullopt;
}

void TransformStoredIndex(int32_t& itemIndex, int32_t changeIndex, int32_t count)
{
    auto transformedIndex = TransformIndexOnDataChange(itemIndex, changeIndex, count);
    itemIndex = transformedIndex.value_or(-1);
}

template<typename T>
void TrimIndexedCacheToCount(int32_t totalItemCount, std::unordered_map<int32_t, T>& hashTable)
{
    for (auto it = hashTable.begin(); it != hashTable.end();) {
        if (it->first >= totalItemCount) {
            it = hashTable.erase(it);
        } else {
            ++it;
        }
    }
}

bool HasLaneCrossLensChanged(const std::vector<float>& laneCrossLens, const std::vector<double>& newLaneCrossLens)
{
    if (laneCrossLens.size() != newLaneCrossLens.size()) {
        return true;
    }
    for (size_t index = 0; index < newLaneCrossLens.size(); ++index) {
        if (!NearEqual(laneCrossLens[index], static_cast<float>(newLaneCrossLens[index]))) {
            return true;
        }
    }
    return false;
}

void ResetRangeIndexes(int32_t& startIndex, int32_t& endIndex)
{
    startIndex = -1;
    endIndex = -1;
}

void UpdateRangeIndexes(const std::map<int32_t, LazyWaterFlowItemMainPos>& itemPositions, float rangeStart,
    float rangeEnd, int32_t& startIndex, int32_t& endIndex)
{
    ResetRangeIndexes(startIndex, endIndex);
    for (const auto& [index, pos] : itemPositions) {
        if (pos.endPos <= rangeStart || pos.startPos >= rangeEnd) {
            continue;
        }
        if (startIndex < 0) {
            startIndex = index;
        }
        endIndex = index;
    }
}

void NormalizeLaneStart(LazyWaterFlowLane& lane)
{
    if (!lane.items_.empty() && !NearZero(lane.items_.front().startOffset)) {
        lane.startPos += lane.items_.front().startOffset;
        lane.items_.front().startOffset = 0.0f;
    }
}

float RebuildLaneEndPos(LazyWaterFlowLane& lane, float mainGap)
{
    if (lane.items_.empty()) {
        lane.endPos = lane.startPos;
        return lane.endPos;
    }

    float mainPos = lane.startPos;
    float endPos = lane.startPos;
    for (size_t itemIndex = 0; itemIndex < lane.items_.size(); ++itemIndex) {
        auto itemStart = mainPos + lane.items_[itemIndex].startOffset;
        endPos = itemStart + lane.items_[itemIndex].mainSize;
        mainPos = endPos;
        if (itemIndex + 1 < lane.items_.size()) {
            mainPos += mainGap;
        }
    }
    lane.endPos = endPos;
    return endPos;
}
} // namespace

void LazyWaterFlowLayoutInfo::ResetPerFrameState()
{
    posMap_.clear();
    ResetRangeIndexes(startIndex_, endIndex_);
    totalMainSize_ = 0.0f;
    adjustOffset_ = {};
    ResetRangeIndexes(layoutedStartIndex_, layoutedEndIndex_);
    cacheStartPos_ = 0.0f;
    cacheEndPos_ = 0.0f;
    ResetRangeIndexes(cachedStartIndex_, cachedEndIndex_);
    laneEndPos_.clear();
    // totalOffset_ / maxHeight_ are cross-frame; preserved here.
}

std::pair<float, float> LazyWaterFlowLayoutInfo::GetLayoutedRange() const
{
    auto startIter = posMap_.find(layoutedStartIndex_);
    auto endIter = posMap_.find(layoutedEndIndex_);
    return {
        startIter != posMap_.end() ? startIter->second.startPos : 0.0f,
        endIter != posMap_.end() ? endIter->second.endPos : 0.0f,
    };
}

void LazyWaterFlowLayoutInfo::ResetItemSizeCache()
{
    idxToHeight_.clear();
    estimateItemSize_ = -1.0f;
}

void LazyWaterFlowLayoutInfo::ResetAllBoundaryFlags()
{
    itemStart_ = false;
    itemEnd_ = false;
    prevItemStart_ = false;
    prevItemEnd_ = false;
}

void LazyWaterFlowLayoutInfo::ResetBoundaryLatch()
{
    // Only the latch; itemStart_/itemEnd_ are rewritten by DetectItemBoundary this frame.
    prevItemStart_ = false;
    prevItemEnd_ = false;
}

void LazyWaterFlowLayoutInfo::ResetForFullRebuild()
{
    // Triggered when the data source mutates outside the ordered NotifyDataChange flow (or count drops to 0).
    // Per-item caches and the scroll anchor are no longer trustworthy.
    ResetPerFrameState();
    lanes_.clear();
    idxToLane_.clear();
    ResetItemSizeCache();
    hasDataChange_ = false;
    updatedStart_ = -1;
    newStartIndex_ = EMPTY_NEW_START_INDEX;
    totalOffset_ = 0.0f;
    maxHeight_ = 0.0f;
    ResetAllBoundaryFlags();
    ClearPendingAdjustAnchor();
}

void LazyWaterFlowLayoutInfo::TrimToTotalItemCount()
{
    TrimIndexedCacheToCount(totalItemCount_, idxToHeight_);
    TrimIndexedCacheToCount(totalItemCount_, idxToLane_);
    for (auto& lane : lanes_) {
        while (!lane.items_.empty() && lane.items_.back().idx >= totalItemCount_) {
            lane.items_.pop_back();
        }
        if (lane.items_.empty()) {
            lane.endPos = lane.startPos;
        }
    }
}

void LazyWaterFlowLayoutInfo::SetTotalItemCount(int32_t count)
{
    const auto previousCount = totalItemCount_;
    totalItemCount_ = std::max(count, 0);
    // Count change (including drop to zero) means caches can't be reliably migrated; typical caller is
    // LazyForEach Reload bypassing NotifyDataChange.
    if (totalItemCount_ <= 0 || totalItemCount_ != previousCount) {
        ResetForFullRebuild();
        return;
    }
    TrimToTotalItemCount();
}

void LazyWaterFlowLayoutInfo::SetPosMap(int32_t index, const LazyWaterFlowItemMainPos& pos)
{
    if (index < 0) {
        return;
    }
    posMap_[index] = pos;
}

const LazyWaterFlowItemMainPos* LazyWaterFlowLayoutInfo::GetPos(int32_t index) const
{
    if (index < 0) {
        return nullptr;
    }
    auto iter = posMap_.find(index);
    if (iter == posMap_.end()) {
        return nullptr;
    }
    return &(iter->second);
}

void LazyWaterFlowLayoutInfo::CacheItemHeight(int32_t index, float height)
{
    if (index < 0) {
        return;
    }
    idxToHeight_[index] = std::max(height, 0.0f);
}

std::optional<float> LazyWaterFlowLayoutInfo::GetCachedHeight(int32_t index) const
{
    if (index < 0) {
        return std::nullopt;
    }
    auto iter = idxToHeight_.find(index);
    if (iter == idxToHeight_.end()) {
        return std::nullopt;
    }
    return iter->second;
}

void LazyWaterFlowLayoutInfo::EstimateItemSize()
{
    if (idxToHeight_.empty()) {
        estimateItemSize_ = -1.0f;
        return;
    }
    float totalSize = 0.0f;
    for (const auto& [index, size] : idxToHeight_) {
        totalSize += size;
    }
    estimateItemSize_ = totalSize / static_cast<float>(idxToHeight_.size());
}

float LazyWaterFlowLayoutInfo::GetAverageItemHeight() const
{
    float totalSize = 0.0f;
    size_t itemCount = 0;
    if (!idxToHeight_.empty()) {
        for (const auto& [index, size] : idxToHeight_) {
            totalSize += size;
        }
        itemCount = idxToHeight_.size();
    } else {
        for (const auto& lane : lanes_) {
            for (const auto& item : lane.items_) {
                totalSize += item.mainSize;
                ++itemCount;
            }
        }
    }
    return itemCount == 0 ? 0.0f : totalSize / static_cast<float>(itemCount);
}

float LazyWaterFlowLayoutInfo::ResolveLaneFrontPos() const
{
    if (lanes_.empty()) {
        return 0.0f;
    }
    float frontPos = std::numeric_limits<float>::max();
    for (const auto& lane : lanes_) {
        frontPos = std::min(frontPos, lane.startPos);
    }
    return frontPos;
}

float LazyWaterFlowLayoutInfo::EstimateSectionHeight(
    float average, int32_t startBound, int32_t endBound, float mainGap) const
{
    // Per-lane absorbed = (sum_heights + count * gap) / cross. Trailing gap matches what ClearFront adds to
    // lane.startPos when a front item is recycled. No "+ average" trailing-row term because in self-local
    // content coords it would inflate totalOffset_ in steady state.
    if (startBound > endBound || lanes_.empty()) {
        return 0.0f;
    }
    const size_t crossCnt = std::max(lanes_.size(), static_cast<size_t>(1));
    float sumHeights = 0.0f;
    for (int32_t i = startBound; i <= endBound; ++i) {
        sumHeights += GetCachedHeight(i).value_or(average);
    }
    const auto count = static_cast<float>(endBound - startBound + 1);
    const auto cross = static_cast<float>(crossCnt);
    return std::max((sumHeights + count * mainGap) / cross, 0.0f);
}

void LazyWaterFlowLayoutInfo::EstimateTotalOffset(int32_t prevStart, int32_t startIdx, float mainGap)
{
    // Materialize the prefix delta into lane geometry by shifting every lane by -(newOffset - prevOffset).
    // Lanes stay in self-local content coords; totalOffset_ tracks the cumulative shift.
    const float average = GetAverageItemHeight();
    const float frontPos = ResolveLaneFrontPos();
    const float prevOffset = totalOffset_;
    float newOffset = frontPos;
    if (startIdx > 0 && Positive(average)) {
        newOffset -= EstimateSectionHeight(average, 0, startIdx - 1, mainGap);
    }
    // Monotonic filter: don't let a noisy average reverse the implied direction. Skip when prevStart ==
    // startIdx (Reset/ClearDataFrom paths) since the filter would clamp the freshly computed value.
    if (prevStart >= 0 && Positive(average) && prevStart != startIdx) {
        if (prevStart < startIdx) {
            newOffset = std::min(newOffset, prevOffset - average);
        } else {
            newOffset = std::max(newOffset, prevOffset + average);
        }
    }
    const float shift = -(newOffset - prevOffset);
    if (!NearZero(shift)) {
        for (auto& lane : lanes_) {
            lane.startPos += shift;
            lane.endPos += shift;
        }
    }
    totalOffset_ = newOffset;
}

void LazyWaterFlowLayoutInfo::FinalizeAfterDataChangeReset(int32_t prevStart, int32_t newStart, float mainGap)
{
    EstimateTotalOffset(prevStart, newStart, mainGap);
    ResetBoundaryLatch();
}

float LazyWaterFlowLayoutInfo::EstimateTotalHeight(float mainGap) const
{
    if (totalItemCount_ <= 0) {
        return 0.0f;
    }
    // Lanes are in self-local content coords (EstimateTotalOffset already materialized any prefix delta), so
    // windowHeight = max(lane.endPos) is content-coord directly.
    // Lanes are in self-local content coords (EstimateTotalOffset already absorbed any prefix delta).
    const int32_t measuredEnd = EndIndex();
    const int32_t measuredStart = StartIndex();
    float windowEndPos = 0.0f;
    for (const auto& lane : lanes_) {
        windowEndPos = std::max(windowEndPos, lane.endPos);
    }
    const float windowHeight = windowEndPos;
    if (measuredEnd < 0 || measuredStart < 0) {
        const float average = GetAverageItemHeight();
        if (!Positive(average) || lanes_.empty()) {
            return std::max(windowHeight, maxHeight_);
        }
        const auto laneCount = static_cast<float>(std::max(lanes_.size(), static_cast<size_t>(1)));
        const float height = static_cast<float>(totalItemCount_) * (average + mainGap) / laneCount;
        return std::max({ windowHeight, maxHeight_, height });
    }
    if (measuredEnd >= totalItemCount_ - 1) {
        return std::max(windowHeight, maxHeight_);
    }

    const float average = GetAverageItemHeight();
    if (!Positive(average)) {
        return std::max(windowHeight, maxHeight_);
    }
    const float suffixHeight = EstimateSectionHeight(average, measuredEnd + 1, totalItemCount_ - 1, mainGap);
    return std::max(windowHeight + suffixHeight, maxHeight_);
}

void LazyWaterFlowLayoutInfo::NotifyDataChange(int32_t index, int32_t count)
{
    auto normalizedIndex = std::max(index, 0);
    CapturePendingAdjustAnchor();

    // A structural change strictly in front of the retained window is preservable by index remap; a change at
    // or inside the window forces remeasure via updatedStart_.
    bool preserveByIndexRemap = false;
    if (PrepareNewStartIndex()) {
        const bool changeTouchesRetainedWindow = (count == 0 && normalizedIndex <= EndIndex()) ||
            (count > 0 && newStartIndex_ < normalizedIndex) ||
            (count < 0 && newStartIndex_ <= normalizedIndex - count - 1);
        if (changeTouchesRetainedWindow) {
            // Flush any unapplied preserve delta before invalidating, so CheckReset rebuilds against accurate idx.
            UpdateLanesIndex(normalizedIndex);
            newStartIndex_ = INVALID_NEW_START_INDEX;
        } else {
            newStartIndex_ += count;
            preserveByIndexRemap = true;
        }
    }

    AdjustUpdateIdxForDataChange(normalizedIndex, count);
    posMap_.clear();
    if (count == 0) {
        // Refresh path. Pop a tail-item dirty so SyncLaneGeometry retracts lane.endPos; otherwise stale mainSize
        // feeds the parent a wrong total height. Mid-lane dirties keep their slot to preserve idx monotonicity.
        InvalidateChangedItemCache(normalizedIndex);
        for (auto& lane : lanes_) {
            if (!lane.items_.empty() && lane.items_.back().idx == normalizedIndex) {
                lane.items_.pop_back();
                break;
            }
        }
        EstimateItemSize();
        hasDataChange_ = true;
        return;
    }

    TransformItemSizeCacheAfterDataChange(normalizedIndex, count);
    if (!preserveByIndexRemap) {
        // Preserve mode defers the remap to UpdateLanesIndex (from CheckReset); shifting here would collapse
        // the newStartIndex_ - StartIndex() diff and make UpdateLanesIndex a no-op.
        TransformLaneCacheAfterDataChange(normalizedIndex, count);
    }
    TransformStoredIndexesAfterDataChange(normalizedIndex, count);
    totalItemCount_ = std::max(totalItemCount_ + count, 0);
    if (totalItemCount_ <= 0) {
        SetTotalItemCount(0);
        return;
    }
    hasDataChange_ = true;
}

bool LazyWaterFlowLayoutInfo::PrepareNewStartIndex()
{
    if (newStartIndex_ == EMPTY_NEW_START_INDEX) {
        const auto windowStart = StartIndex();
        newStartIndex_ = windowStart < 0 ? INVALID_NEW_START_INDEX : windowStart;
    }
    return newStartIndex_ >= 0;
}

void LazyWaterFlowLayoutInfo::InvalidateChangedItemCache(int32_t index)
{
    idxToLane_.erase(index);
    idxToHeight_.erase(index);
}

void LazyWaterFlowLayoutInfo::ShiftUpdateIdxForStructuralChange(int32_t index, int32_t count)
{
    // Delete clamps to delete-start when updatedStart_ lands inside the deleted range. count==0 is handled by
    // DeriveWindowDirtyCandidate so refresh outside the window cannot pull updatedStart_ back.
    if (updatedStart_ < 0) {
        return;
    }
    if (count > 0) {
        if (index <= updatedStart_) {
            updatedStart_ += count;
        }
        return;
    }
    if (count < 0) {
        const int32_t deleteEnd = index + (-count) - 1;
        if (deleteEnd < updatedStart_) {
            updatedStart_ += count;
        } else if (index <= updatedStart_) {
            updatedStart_ = index;
        }
    }
}

int32_t LazyWaterFlowLayoutInfo::DeriveWindowDirtyCandidate(int32_t index, int32_t count) const
{
    // Result is in POST-transform index space (matches CheckReset).
    const int32_t windowStart = StartIndex();
    const int32_t windowEnd = EndIndex();
    if (windowStart < 0 || windowEnd < windowStart) {
        return -1;
    }
    if (count > 0) {
        return (index > windowStart && index <= windowEnd) ? index : -1;
    }
    if (count < 0) {
        const int32_t deleteEnd = index + (-count) - 1;
        // Delete spanning the front anchor: candidate=index lets CheckReset pick ResetWithLaneOffset.
        if ((index <= windowStart && deleteEnd >= windowStart) ||
            (index > windowStart && index <= windowEnd)) {
            return index;
        }
        return -1;
    }
    return index <= windowEnd ? index : -1;
}

void LazyWaterFlowLayoutInfo::AdjustUpdateIdxForDataChange(int32_t index, int32_t count)
{
    ShiftUpdateIdxForStructuralChange(index, count);
    const int32_t candidate = DeriveWindowDirtyCandidate(index, count);
    if (candidate < 0) {
        return;
    }
    if (updatedStart_ < 0 || candidate < updatedStart_) {
        updatedStart_ = candidate;
    }
}

void LazyWaterFlowLayoutInfo::TransformItemSizeCacheAfterDataChange(int32_t index, int32_t count)
{
    if (idxToHeight_.empty()) {
        return;
    }

    std::unordered_map<int32_t, float> transformedSizes;
    for (const auto& [itemIndex, size] : idxToHeight_) {
        auto transformedIndex = TransformIndexOnDataChange(itemIndex, index, count);
        if (!transformedIndex.has_value()) {
            continue;
        }
        transformedSizes[transformedIndex.value()] = size;
    }
    idxToHeight_ = std::move(transformedSizes);
    EstimateItemSize();
}

void LazyWaterFlowLayoutInfo::TransformLaneCacheAfterDataChange(int32_t index, int32_t count)
{
    if (lanes_.empty()) {
        std::unordered_map<int32_t, size_t> transformedIdxToLane;
        for (const auto& [itemIndex, laneIdx] : idxToLane_) {
            auto transformedIndex = TransformIndexOnDataChange(itemIndex, index, count);
            if (transformedIndex.has_value()) {
                transformedIdxToLane[transformedIndex.value()] = laneIdx;
            }
        }
        idxToLane_ = std::move(transformedIdxToLane);
        return;
    }

    std::unordered_map<int32_t, size_t> transformedIdxToLane;
    for (size_t laneIdx = 0; laneIdx < lanes_.size(); ++laneIdx) {
        auto& lane = lanes_[laneIdx];
        std::deque<LazyWaterFlowLaneItem> transformedItems;
        for (auto item : lane.items_) {
            auto transformedIndex = TransformIndexOnDataChange(item.idx, index, count);
            if (!transformedIndex.has_value()) {
                continue;
            }
            item.idx = transformedIndex.value();
            transformedItems.push_back(item);
            transformedIdxToLane[item.idx] = laneIdx;
        }
        lane.items_ = std::move(transformedItems);
        if (lane.items_.empty()) {
            lane.endPos = lane.startPos;
        }
    }
    idxToLane_ = std::move(transformedIdxToLane);
}

void LazyWaterFlowLayoutInfo::TransformStoredIndexesAfterDataChange(int32_t index, int32_t count)
{
    TransformStoredIndex(startIndex_, index, count);
    TransformStoredIndex(endIndex_, index, count);
    TransformStoredIndex(layoutedStartIndex_, index, count);
    TransformStoredIndex(layoutedEndIndex_, index, count);
    TransformStoredIndex(cachedStartIndex_, index, count);
    TransformStoredIndex(cachedEndIndex_, index, count);
    TransformStoredIndex(pendingAnchor_.startIndex, index, count);
    TransformStoredIndex(pendingAnchor_.endIndex, index, count);
    std::map<int32_t, LazyWaterFlowItemMainPos> transformedVisiblePositions;
    for (const auto& [itemIndex, pos] : pendingVisiblePositions_) {
        auto transformedIndex = TransformIndexOnDataChange(itemIndex, index, count);
        if (transformedIndex.has_value()) {
            transformedVisiblePositions[transformedIndex.value()] = pos;
        }
    }
    pendingVisiblePositions_ = std::move(transformedVisiblePositions);
}

void LazyWaterFlowLayoutInfo::ClearDataChanges()
{
    hasDataChange_ = false;
    updatedStart_ = -1;
    newStartIndex_ = EMPTY_NEW_START_INDEX;
    ClearPendingAdjustAnchor();
}

void LazyWaterFlowLayoutInfo::ClearPendingAdjustAnchor()
{
    hasPendingAdjustAnchor_ = false;
    pendingAnchor_ = {};
    pendingVisiblePositions_.clear();
}

void LazyWaterFlowLayoutInfo::CapturePendingAdjustAnchor()
{
    if (hasPendingAdjustAnchor_) {
        return;
    }
    // Both explicit anchors and the full visible set are kept so the diff stays robust under reordering.
    hasPendingAdjustAnchor_ = true;
    pendingAnchor_.startIndex = startIndex_;
    pendingAnchor_.endIndex = endIndex_;
    pendingAnchor_.totalMainSize = totalMainSize_;
    pendingAnchor_.startPos.reset();
    pendingAnchor_.endPos.reset();
    auto startIter = posMap_.find(startIndex_);
    if (startIter != posMap_.end()) {
        pendingAnchor_.startPos = startIter->second;
    }
    auto endIter = posMap_.find(endIndex_);
    if (endIter != posMap_.end()) {
        pendingAnchor_.endPos = endIter->second;
    }
    pendingVisiblePositions_.clear();
    auto [layoutedStart, layoutedEnd] = GetLayoutedRange();
    for (const auto& [index, pos] : posMap_) {
        if (pos.endPos > layoutedStart && pos.startPos < layoutedEnd) {
            pendingVisiblePositions_[index] = pos;
        }
    }
    if (pendingVisiblePositions_.empty()) {
        if (pendingAnchor_.startPos.has_value()) {
            pendingVisiblePositions_[pendingAnchor_.startIndex] = pendingAnchor_.startPos.value();
        }
        if (pendingAnchor_.endPos.has_value()) {
            pendingVisiblePositions_[pendingAnchor_.endIndex] = pendingAnchor_.endPos.value();
        }
    }
}

bool LazyWaterFlowLayoutInfo::UpdateLaneCrossLens(const std::vector<double>& laneCrossLens)
{
    const bool changed = HasLaneCrossLensChanged(crossLens_, laneCrossLens);
    if (changed) {
        crossLens_.assign(laneCrossLens.begin(), laneCrossLens.end());
    }
    return changed || lanes_.empty() || lanes_.size() != crossLens_.size();
}

void LazyWaterFlowLayoutInfo::UpdateVisibleRange(float viewStart, float viewEnd)
{
    ACE_SCOPED_TRACE("LazyWaterFlowLayoutInfo::UpdateVisibleRange");
    if (totalItemCount_ <= 0 || posMap_.empty()) {
        ResetRangeIndexes(startIndex_, endIndex_);
        return;
    }
    // Non-finite viewEnd: parent has no finite upper bound, so expand to all of posMap_.
    if (!std::isfinite(viewEnd)) {
        startIndex_ = posMap_.begin()->first;
        endIndex_ = posMap_.rbegin()->first;
        return;
    }
    if (viewEnd <= viewStart) {
        ResetRangeIndexes(startIndex_, endIndex_);
        return;
    }

    UpdateRangeIndexes(posMap_, viewStart, viewEnd, startIndex_, endIndex_);
}

void LazyWaterFlowLayoutInfo::UpdateCachedRange(float cacheStart, float cacheEnd)
{
    cacheStartPos_ = cacheStart;
    cacheEndPos_ = cacheEnd;
    if (totalItemCount_ <= 0 || posMap_.empty()) {
        ResetRangeIndexes(cachedStartIndex_, cachedEndIndex_);
        return;
    }
    if (!std::isfinite(cacheEnd) || cacheEnd <= cacheStart) {
        cachedStartIndex_ = posMap_.begin()->first;
        cachedEndIndex_ = posMap_.rbegin()->first;
        return;
    }

    UpdateRangeIndexes(posMap_, cacheStart, cacheEnd, cachedStartIndex_, cachedEndIndex_);
}

bool LazyWaterFlowLayoutInfo::NeedPredict() const
{
    if (!std::isfinite(cacheEndPos_) || totalItemCount_ <= 0) {
        return false;
    }
    const bool extendedViewOverlapsContent = GreatNotEqual(extendedViewEndPos_, 0.0f) &&
        (!Positive(totalMainSize_) || LessNotEqual(extendedViewStartPos_, totalMainSize_));
    // An empty offscreen child cannot start its own predict loop from cache overlap alone.
    if (posMap_.empty()) {
        return extendedViewOverlapsContent;
    }
    auto hasBackwardGap = false;
    if (cachedStartIndex_ > 0) {
        auto iter = posMap_.find(cachedStartIndex_);
        hasBackwardGap = iter != posMap_.end() && GreatNotEqual(iter->second.startPos, cacheStartPos_);
    }
    auto hasForwardGap = false;
    if (cachedEndIndex_ >= 0 && cachedEndIndex_ < totalItemCount_ - 1) {
        if (!laneEndPos_.empty()) {
            auto minLaneEnd = *std::min_element(laneEndPos_.begin(), laneEndPos_.end());
            hasForwardGap = LessNotEqual(minLaneEnd, cacheEndPos_);
        } else {
            auto iter = posMap_.find(cachedEndIndex_);
            hasForwardGap = iter != posMap_.end() && LessNotEqual(iter->second.endPos, cacheEndPos_);
        }
    }
    if (!extendedViewOverlapsContent && startIndex_ < 0 && endIndex_ < 0) {
        // Once parent predict has started an offscreen cache window, let idle predict finish that window.
        const bool hasStartedOffscreenCache = cachedStartIndex_ >= 0 && cachedEndIndex_ >= cachedStartIndex_;
        return hasStartedOffscreenCache && (hasBackwardGap || hasForwardGap);
    }
    return hasBackwardGap || hasForwardGap;
}

void LazyWaterFlowLayoutInfo::ResetLanes(int32_t laneCount, std::optional<float> laneBasePos)
{
    lanes_.assign(std::max(laneCount, 0), LazyWaterFlowLane {});
    auto basePos = laneBasePos.value_or(0.0f);
    for (auto& lane : lanes_) {
        lane.startPos = basePos;
        lane.endPos = basePos;
        lane.items_.clear();
    }
    idxToLane_.clear();
    posMap_.clear();
    laneEndPos_.assign(lanes_.size(), basePos);
    ResetAllBoundaryFlags();
    ResetItemSizeCache();
    ClearPendingAdjustAnchor();
    totalOffset_ = 0.0f;
    maxHeight_ = 0.0f;
}

void LazyWaterFlowLayoutInfo::ResetWithLaneOffset(std::optional<float> laneBasePos)
{
    auto basePos = laneBasePos;
    if (!basePos.has_value()) {
        for (const auto& lane : lanes_) {
            if (!lane.items_.empty()) {
                basePos = lane.startPos;
                break;
            }
        }
        if (!basePos.has_value()) {
            basePos = 0.0f;
        }
    }
    for (auto& lane : lanes_) {
        lane.startPos = basePos.value();
        lane.endPos = basePos.value();
        lane.items_.clear();
    }
    idxToLane_.clear();
    posMap_.clear();
    laneEndPos_.assign(lanes_.size(), basePos.value());
}

void LazyWaterFlowLayoutInfo::UpdateLanesIndex(int32_t /*updateIdx*/)
{
    if (newStartIndex_ < 0) {
        return;
    }
    const int32_t prevStart = StartIndex();
    if (prevStart < 0) {
        return;
    }
    idxToLane_.clear();
    const int32_t diff = newStartIndex_ - prevStart;
    for (size_t laneIdx = 0; laneIdx < lanes_.size(); ++laneIdx) {
        for (auto& item : lanes_[laneIdx].items_) {
            item.idx += diff;
            idxToLane_[item.idx] = laneIdx;
        }
    }
    startIndex_ = StartIndex();
    endIndex_ = EndIndex();
}

void LazyWaterFlowLayoutInfo::SyncItemPositions(float mainGap)
{
    posMap_.clear();
    laneEndPos_.assign(lanes_.size(), 0.0f);
    for (size_t laneIdx = 0; laneIdx < lanes_.size(); ++laneIdx) {
        auto& lane = lanes_[laneIdx];
        NormalizeLaneStart(lane);
        float mainPos = lane.startPos;
        float endPos = lane.startPos;
        for (size_t itemIndex = 0; itemIndex < lane.items_.size(); ++itemIndex) {
            const auto& item = lane.items_[itemIndex];
            auto itemStart = mainPos + item.startOffset;
            auto itemEnd = itemStart + item.mainSize;
            const int32_t writeIdx = item.idx;
            posMap_[writeIdx] = {
                static_cast<int32_t>(laneIdx),
                itemStart,
                itemEnd,
            };
            idxToLane_[writeIdx] = laneIdx;
            endPos = itemEnd;
            mainPos = itemEnd;
            if (itemIndex + 1 < lane.items_.size()) {
                mainPos += mainGap;
            }
        }
        lane.endPos = lane.items_.empty() ? lane.startPos : endPos;
        laneEndPos_[laneIdx] = lane.items_.empty() ? lane.endPos : lane.endPos + mainGap;
    }
}

int32_t LazyWaterFlowLayoutInfo::StartIndex() const
{
    auto minIdx = Infinity<int32_t>();
    for (const auto& lane : lanes_) {
        if (lane.items_.empty()) {
            continue;
        }
        minIdx = std::min(minIdx, lane.items_.front().idx);
    }
    return minIdx == Infinity<int32_t>() ? -1 : minIdx;
}

int32_t LazyWaterFlowLayoutInfo::EndIndex() const
{
    int32_t maxIdx = -1;
    for (const auto& lane : lanes_) {
        if (lane.items_.empty()) {
            continue;
        }
        maxIdx = std::max(maxIdx, lane.items_.back().idx);
    }
    return maxIdx;
}

void LazyWaterFlowLayoutInfo::ClearDataFrom(int32_t index, float mainGap)
{
    EraseFrom(index, idxToLane_);
    EraseFrom(index, idxToHeight_);
    for (auto& lane : lanes_) {
        while (!lane.items_.empty() && lane.items_.back().idx >= index) {
            lane.items_.pop_back();
        }
        if (lane.items_.empty()) {
            lane.endPos = lane.startPos;
            continue;
        }
        RebuildLaneEndPos(lane, mainGap);
    }
}

const LazyWaterFlowLane* LazyWaterFlowLayoutInfo::GetLane(int32_t itemIdx) const
{
    auto it = idxToLane_.find(itemIdx);
    if (it == idxToLane_.end() || it->second >= lanes_.size()) {
        return nullptr;
    }
    return &lanes_[it->second];
}

LazyWaterFlowLane* LazyWaterFlowLayoutInfo::GetMutableLane(int32_t itemIdx)
{
    return const_cast<LazyWaterFlowLane*>(GetLane(itemIdx));
}

void LazyWaterFlowLayoutInfo::DumpAdvanceInfo()
{
    DumpLog::GetInstance().AddDesc("itemStartIndex:" + std::to_string(startIndex_));
    DumpLog::GetInstance().AddDesc("itemEndIndex:" + std::to_string(endIndex_));
    DumpLog::GetInstance().AddDesc("itemTotalCount:" + std::to_string(totalItemCount_));
    DumpLog::GetInstance().AddDesc("estimatedItemSize:" + std::to_string(estimateItemSize_));
    DumpLog::GetInstance().AddDesc("totalMainSize:" + std::to_string(totalMainSize_));
    DumpLog::GetInstance().AddDesc("layoutedStartIndex:" + std::to_string(layoutedStartIndex_));
    DumpLog::GetInstance().AddDesc("layoutedEndIndex:" + std::to_string(layoutedEndIndex_));
    DumpLog::GetInstance().AddDesc("cachedStartIndex:" + std::to_string(cachedStartIndex_));
    DumpLog::GetInstance().AddDesc("cachedEndIndex:" + std::to_string(cachedEndIndex_));
}

void LazyWaterFlowLayoutInfo::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(json);
    json->Put("itemStartIndex", startIndex_);
    json->Put("itemEndIndex", endIndex_);
    json->Put("itemTotalCount", totalItemCount_);
    json->Put("estimatedItemSize", estimateItemSize_);
    json->Put("totalMainSize", totalMainSize_);
    json->Put("layoutedStartIndex", layoutedStartIndex_);
    json->Put("layoutedEndIndex", layoutedEndIndex_);
    json->Put("cachedStartIndex", cachedStartIndex_);
    json->Put("cachedEndIndex", cachedEndIndex_);
}

} // namespace OHOS::Ace::NG
