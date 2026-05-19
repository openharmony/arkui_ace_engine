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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_ALGORITHM_H

#include <optional>
#include <vector>

#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_info.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_property.h"

namespace OHOS::Ace::NG {

// Sliding-window layout for LazyVWaterFlow. Cross-frame state lives in layoutInfo_.
class ACE_EXPORT LazyWaterFlowLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(LazyWaterFlowLayoutAlgorithm, LayoutAlgorithm);

public:
    explicit LazyWaterFlowLayoutAlgorithm(const RefPtr<LazyWaterFlowLayoutInfo>& info) : layoutInfo_(info) {}

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    int32_t GetTotalItemCount() const
    {
        return totalItemCount_;
    }

    static std::optional<ViewPosReference> GetReferencePos(const RefPtr<FrameNode>& frameNode);

private:
    struct PrevFrameSnapshot {
        LazyWaterFlowAnchorSnapshot anchor;
    };

    struct LayoutRange {
        int32_t start = -1;
        int32_t end = -1;
    };

    struct FillAnchor {
        int32_t fillStart = 0;
        float laneBase = 0.0f;
    };

    void SetFrameSize(LayoutWrapper* layoutWrapper, OptionalSizeF& contentIdealSize, const PaddingPropertyF& padding);
    /**
     * @brief Project the parent viewport into self-local content coords (viewStart_ / viewEnd_ / cacheStartPos_ /
     * cacheEndPos_).
     */
    void UpdateReferencePos(LayoutWrapper* layoutWrapper, std::optional<ViewPosReference>& posRef);
    void UpdateGap(const RefPtr<LazyWaterFlowLayoutProperty>& layoutProperty, const OptionalSizeF& selfIdealSize);
    void UpdateItemConstraints(const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint);
    bool CheckNeedMeasure(const RefPtr<LayoutWrapper>& layoutWrapper, int32_t laneIdx) const;
    float EstimateTotalMainSize(float maxMainSize) const;
    float EstimateBodyHeight(float maxMainSize) const;
    float ResolveFallbackMainSize(LayoutWrapper* layoutWrapper) const;
    bool IsPredictPass() const;
    bool IsDeadlineReached() const;

    void MeasureItems(LayoutWrapper* layoutWrapper);
    /**
     * @brief Refill the lane window from the front/back boundaries.
     *
     * @param resetFrom >= 0 skips Clear* and refills forward; -1 runs the normal pass.
     */
    void RefillLaneWindow(LayoutWrapper* layoutWrapper, int32_t resetFrom, float frontBoundary, float backBoundary,
        float& maxMainSize);
    bool TryKeepEmptyLanesOutsideVisibleContent(float& maxMainSize);
    bool TryTopEdgeAnchorRefill(LayoutWrapper* layoutWrapper, float backBoundary, float& maxMainSize);
    bool TryTopJumpRefill(LayoutWrapper* layoutWrapper, float frontBoundary, float backBoundary, float& maxMainSize);
    void RefillFromEmptyLanes(LayoutWrapper* layoutWrapper, float frontBoundary, float backBoundary,
        float& maxMainSize);
    FillAnchor EstimateFillAnchorFromFront(float frontBoundary) const;
    PrevFrameSnapshot CapturePrevFrameSnapshot() const;
    OffsetF ResolveItemOffset(
        const OffsetF& paddingOffset, int32_t laneIdx, float childCrossSize, float mainPos) const;
    std::optional<LazyWaterFlowItemMainPos> GetRememberedItemPositionInLane(int32_t index, size_t laneIdx) const;
    std::optional<LazyWaterFlowItemMainPos> GetRememberedItemPosition(int32_t index) const;
    bool PrepareMeasureItems(LayoutWrapper* layoutWrapper, PrevFrameSnapshot& prevFrameSnapshot);
    void ShiftLanes(float delta);
    void SyncLaneGeometry();
    float ResolveFrontBoundary() const;
    float ResolveBackBoundary() const;
    /**
     * @brief Decide how to handle a NotifyDataChange before this frame's fill.
     *
     * @return -1 = preserve fast path (run normal Fill); >=0 = tail rebuild from this business index.
     */
    int32_t CheckReset();

    void DetectItemBoundary();
    void AlignFrontTotalOffset();
    void AlignBackMaxHeight();
    bool AreFrontLanesCovered(float bound) const;
    bool AreBackLanesCovered(float bound) const;
    void ClearFront(float bound);
    void ClearBack(float bound);
    void FillFront(LayoutWrapper* layoutWrapper, float bound, int32_t startIndex, int32_t minIndex,
        float& maxMainSize);
    void FillBack(
        LayoutWrapper* layoutWrapper, float bound, int32_t startIndex, int32_t maxIndex, float& maxMainSize);

    RefPtr<LayoutWrapper> GetExistingChildWrapper(LayoutWrapper* layoutWrapper, int32_t rawIndex) const;
    RefPtr<LayoutWrapper> GetOrCreateChildWrapper(
        LayoutWrapper* layoutWrapper, int32_t rawIndex, bool maybeVisible) const;
    void UpdateMeasuredLaneItem(int32_t index, int32_t laneIdx, const RefPtr<LayoutWrapper>& child,
        float childMainSize, const std::optional<float>& cachedSize);
    std::optional<float> MeasureChild(
        LayoutWrapper* layoutWrapper, int32_t index, int32_t laneIdx, float referencePos, ReferenceEdge referenceEdge);
    void ReMeasureItemsInLane(LayoutWrapper* layoutWrapper, int32_t laneIdx);
    void ReMeasureItems(LayoutWrapper* layoutWrapper);
    LayoutConstraintF CreateChildConstraintForItem(const RefPtr<LayoutWrapper>& child, int32_t laneIdx,
        float referencePos, ReferenceEdge referenceEdge) const;
    bool CanRenderChildInDeadline(const RefPtr<LayoutWrapper>& child) const;
    void FinishMeasureItems(
        LayoutWrapper* layoutWrapper, const PrevFrameSnapshot& prevFrameSnapshot, float maxMainSize);
    void UpdateMeasuredRanges();
    /**
     * @brief Translate totalDelta into AdjustOffset. Prefer end-anchor when valid, else start-anchor.
     */
    void UpdateAdjustOffset(const PrevFrameSnapshot& prevFrameSnapshot);
    bool TryUpdateEndAnchorAdjust(const PrevFrameSnapshot& prevFrameSnapshot, float totalDelta);
    void UpdateStartAnchorAdjust(const PrevFrameSnapshot& prevFrameSnapshot);
    void UpdateVisibleAdjustOffset(float totalDelta);

    void LayoutItems(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset);
    LayoutRange GetLayoutRange(const RefPtr<FrameNode>& host) const;
    bool NeedVisibleRangeForChild(const RefPtr<UINode>& child) const;
    bool NeedVisibleRangeForChildren(const RefPtr<FrameNode>& host) const;
    bool ShouldReuseCachedOffscreenSize(LayoutWrapper* layoutWrapper, bool maybeVisible, bool hasCachedSize) const;
    void LayoutBusinessItems(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset,
        const LayoutRange& range);
    void LayoutBusinessItem(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset, int32_t businessIndex);
    bool IsValidItemPosition(const LazyWaterFlowItemMainPos* itemPos) const;
    RefPtr<LayoutWrapper> GetLayoutChild(LayoutWrapper* layoutWrapper, int32_t businessIndex, bool isVisible) const;
    void ClearUnlayoutedBusinessItems(LayoutWrapper* layoutWrapper, const LayoutRange& range) const;
    void UpdateActiveChildRange(LayoutWrapper* layoutWrapper, int32_t visibleStart, int32_t visibleEnd,
        int32_t cachedStart, int32_t cachedEnd) const;
    void UpdateBusinessActiveRangeOnChildren(const RefPtr<FrameNode>& host, int32_t activeStart, int32_t activeEnd,
        int32_t cacheStart, int32_t cacheEnd) const;
    ActiveChildSets BuildActiveChildSets(int32_t rawStart, int32_t rawEnd) const;

    // ---------------------------- State fields ----------------------------

    int32_t totalItemCount_ = 0;
    // Host main-axis padding size from last Layout pass; bounded fallback for viewEnd_, also END-anchor
    // referencePos compensation when the parent frame shrunk between frames.
    float realMainSize_ = 0.0f;
    float totalMainSize_ = 0.0f;
    float crossSize_ = 0.0f;
    float mainGap_ = 0.0f;
    float crossGap_ = 0.0f;
    // Real viewport in self-local content coords. Infinity = parent provides no bounded upper edge.
    float viewStart_ = 0.0f;
    float viewEnd_ = Infinity<float>();
    // Real viewport plus parent-provided viewExt; the child cache window expands from this range.
    float extendedViewStart_ = 0.0f;
    float extendedViewEnd_ = Infinity<float>();
    // Cache window per side, as a fraction of the parent viewport main size.
    float cacheSize_ = 0.5f;
    float cacheStartPos_ = 0.0f;
    float cacheEndPos_ = Infinity<float>();
    std::vector<double> crossLens_;
    std::vector<double> crossPos_;
    std::vector<float> laneEndPos_;
    std::vector<LayoutConstraintF> childLayoutConstraints_;
    TextDirection layoutDirection_ = TextDirection::LTR;
    RefPtr<LazyWaterFlowLayoutInfo> layoutInfo_;
    ReferenceEdge referenceEdge_ = ReferenceEdge::START;
    bool isPredictPass_ = false;
    bool laneTopologyChanged_ = false;
    // RefillLaneWindow took the top-anchor short-circuit (lanes re-based to 0). UpdateStartAnchorAdjust must
    // skip the anchor diff so the pure internal coord re-base does not leak as a parent scroll shift.
    bool topAnchorRebased_ = false;
    // Viewport is fully outside known content; keep the visible window empty and preserve last total height.
    bool keepEmptyLanesOutsideContent_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_ALGORITHM_H
