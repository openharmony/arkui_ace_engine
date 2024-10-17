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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_SW_LAYOUT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_SW_LAYOUT_H

#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"
#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_segmented_layout.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT WaterFlowLayoutSW : public WaterFlowSegmentLayoutBase {
    DECLARE_ACE_TYPE(WaterFlowLayoutSW, WaterFlowSegmentLayoutBase);

public:
    explicit WaterFlowLayoutSW(const RefPtr<WaterFlowLayoutInfoSW>& info) : info_(info) {}
    void Measure(LayoutWrapper* wrapper) override;
    void Layout(LayoutWrapper* wrapper) override;

    void SetCanOverScroll(bool value) override
    {
        overScroll_ = value;
    }

    void StartCacheLayout() override;
    bool PreloadItem(LayoutWrapper* host, int32_t itemIdx, int64_t deadline) override;
    void EndCacheLayout() override;

private:
    void Init(const SizeF& frameSize);
    /* init WaterFlow without Sections */
    void SingleInit(const SizeF& frameSize);
    void CheckReset();

    void MeasureOnOffset(float delta);

    void ApplyDelta(float delta);

    void MeasureToTarget(int32_t targetIdx);

    /**
     * @brief When the item is within or close to viewport, layout is preserved and we merely apply an offset.
     * When jumping to an item further away, the current layout would be reset for better layout performance.
     *
     * @param jumpIdx
     * @param align ScrollAlign
     * @param mainSize of the viewport
     */
    void MeasureOnJump(int32_t jumpIdx, ScrollAlign align);

    /**
     * @brief Helper to perform jumping to an item.
     *
     * @param noSkip true if we can directly apply offset to reach the target.
     */
    void Jump(int32_t jumpIdx, ScrollAlign align, bool noSkip);

    /**
     * @brief convert Auto align to other Align types.
     *
     * @param inView true if item is between startIndex and endIndex.
     * @return converted ScrollAlign type.
     */
    ScrollAlign ParseAutoAlign(int32_t jumpIdx, bool inView);

    /**
     * @brief fills the viewport backward until [viewportBound] is reached / idx < minChildIdx.
     *
     * @param viewportBound boundary to fill towards.
     * @param idx first item index to fill with.
     * @param minChildIdx smallest item index to fill before stopping.
     */
    void FillFront(float viewportBound, int32_t idx, int32_t minChildIdx);
    /**
     * @brief fills backward with one section.
     *
     * @return true if fillFront should end. False implies section is completely filled or idx < minChildIdx.
     */
    bool FillFrontSection(float viewportBound, int32_t& idx, int32_t minChildIdx);
    /**
     * @brief fills the viewport backward with cached idx -> lane mapping.
     */
    void RecoverFront(float viewportBound, int32_t& idx, int32_t minChildIdx);
    /**
     * @brief Append Item in the front of a lane.
     * @return endPos of next item in the filled lane.
     */
    float FillFrontHelper(float itemLen, int32_t idx, size_t laneIdx);
    /**
     * @brief Clear items above the viewport.
     * Iterate by index to keep item range continuous.
     */
    void ClearFront();

    /**
     * @brief fills the viewport forward until [viewportBound] is reached / idx > maxChildIdx.
     *
     * @param viewportBound boundary to fill towards.
     * @param idx first item index to fill with.
     * @param maxChildIdx greatest item index to fill before stopping.
     */
    void FillBack(float viewportBound, int32_t idx, int32_t maxChildIdx);
    /**
     * @brief fills forward with one section.
     *
     * @return true if fillBack should end. False implies section is completely filled or idx > maxChildIdx.
     */
    bool FillBackSection(float viewportBound, int32_t& idx, int32_t maxChildIdx);
    /**
     * @brief fills the viewport forward with cached idx -> lane mapping.
     */
    void RecoverBack(float viewportBound, int32_t& idx, int32_t maxChildIdx);
    /**
     * @brief Append Item to a lane.
     * @return startPos of next item in the filled lane.
     */
    float FillBackHelper(float itemLen, int32_t idx, size_t laneIdx);
    /**
     * @brief Clear items below the viewport.
     *
     * @param bound of the viewport
     */
    void ClearBack(float bound);

    void AdjustOverScroll();

    /**
     * @brief If need to match children size, adjust self size after measuring children.
     */
    void PostMeasureSelf(float selfCrossLen);

    float MeasureChild(const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, size_t lane) const;

    /**
     * @brief Fill cache items back to lanes_ to prepare for Layout phase.
     * (These items were removed during ClearFront / ClearBack)
     */
    void RecoverCacheItems(int32_t cacheCount);
    /**
     * @param itemIdx to recover.
     * @param front true if recovering an item before startIndex_.
     * @return true if item is successfully recovered.
     */
    bool RecoverCachedHelper(int32_t itemIdx, bool front);

    /**
     * @brief Measure all items in view to check if any item's height changed.
     */
    bool ItemHeightChanged() const;

    /**
     * @brief Layout a single section of items
     *
     * @param idx section index.
     * @param paddingOffset WaterFlow padding, need to add to the child offset.
     * @param selfCrossLen cross length of WaterFlow.
     * @param reverse true if reverse layout
     * @param rtl true if layout right to left
     */
    void LayoutSection(size_t idx, const OffsetF& paddingOffset, float selfCrossLen, bool reverse, bool rtl);
    void LayoutFooter(const OffsetF& paddingOffset, bool reverse);

    void SyncPreloadItem(LayoutWrapper* host, int32_t itemIdx) override;
    /**
     * @brief shared implementation to preload a cache item.
     * @return true if the item is successfully preloaded.
     */
    bool PreloadItemImpl(int32_t itemIdx);

    // convert FlowItem's index to children node index.
    inline int32_t nodeIdx(int32_t idx) const;

    RefPtr<WaterFlowLayoutInfoSW> info_;
    RefPtr<WaterFlowSections> sections_;

    int32_t itemCnt_ = 0; // total number of FlowItems (excluding footer)
    float mainLen_ = 0.0f;
    std::optional<int64_t> cacheDeadline_; // cache layout deadline

    bool overScroll_ = true;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_SW_LAYOUT_H
