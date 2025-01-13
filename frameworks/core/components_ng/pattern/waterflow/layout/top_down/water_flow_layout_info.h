/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_H

#include <cstdint>
#include <map>
#include <optional>
#include <sstream>

#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_info_base.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace::NG {
struct FlowItemIndex {
    int32_t crossIndex = 0;
    int32_t lastItemIndex = 0;
};

struct FlowItemPosition {
    int32_t crossIndex = 0;
    float startMainPos = 0;
};

class WaterFlowLayoutInfo : public WaterFlowLayoutInfoBase {
    DECLARE_ACE_TYPE(WaterFlowLayoutInfo, WaterFlowLayoutInfoBase);

public:
    WaterFlowLayoutInfo() = default;
    ~WaterFlowLayoutInfo() override = default;

    WaterFlowLayoutMode Mode() const override
    {
        return WaterFlowLayoutMode::TOP_DOWN;
    }
    float Offset() const override
    {
        return currentOffset_;
    }
    int32_t FirstIdx() const override
    {
        return firstIndex_;
    }
    int32_t GetCrossIndex(int32_t itemIndex) const override;

    void UpdateStartIndex() override;
    int32_t GetEndIndexByOffset(float offset) const;
    float GetMaxMainHeight() const;
    float GetContentHeight() const override;
    float EstimateTotalHeight() const override;
    bool IsAllCrossReachEnd(float mainSize) const;

    /**
     * @brief Get the next available cross index to place a new item.
     *
     * @param segmentIdx index of the WaterFlow segment.
     * @return FlowItemIndex
     */
    FlowItemIndex GetCrossIndexForNextItem(int32_t segmentIdx) const;

    bool OverScrollTop() override;
    bool OverScrollBottom() override;
    
    float GetMainHeight(int32_t crossIndex, int32_t itemIndex) const;
    float GetStartMainPos(int32_t crossIndex, int32_t itemIndex) const;
    void Reset() override;
    void Reset(int32_t resetFrom);
    void ResetFooter() override;
    int32_t GetCrossCount() const override;
    int32_t GetMainCount() const override;
    void ClearCacheAfterIndex(int32_t currentIndex);

    bool ReachStart(float prevOffset, bool firstLayout) const override;
    bool ReachEnd(float prevOffset, bool firstLayout) const override;
    bool OutOfBounds() const override;

    OverScrollOffset GetOverScrolledDelta(float delta) const override;
    float CalcOverScroll(float mainSize, float delta) const override;

    void UpdateOffset(float delta) override;

    float CalibrateOffset() override
    {
        /* offset always accurate */
        return 0.0f;
    }

    float CalcTargetPosition(int32_t idx, int32_t crossIdx) const override;

    float GetDelta(float prevPos) const override
    {
        return prevPos - currentOffset_;
    }

    float CurrentPos() const override
    {
        return currentOffset_;
    }
    float TopFinalPos() const override
    {
        return 0.0f;
    };
    float BottomFinalPos(float viewHeight) const override
    {
        float endOffset = viewHeight - GetContentHeight();
        return Negative(endOffset) ? endOffset : 0.0f;
    };

    float JumpToTargetAlign(const std::pair<float, float>& item) const;
    void JumpTo(const std::pair<float, float>& item);

    bool IsMisaligned() const override
    {
        return false;
    }

    /**
     * @brief Init data structures based on new WaterFlow Sections.
     *
     * @param sections vector of Sections info.
     * @param start index of the first modified section, all sections prior to [start] remain the same.
     */
    void InitSegments(const std::vector<WaterFlowSections::Section>& sections, int32_t start) override;

    // set up startPos of next segment after initializing margins_
    void PrepareSegmentStartPos();

    void ResetSegmentStartPos();

    /**
     * @brief Record a new FlowItem in ItemMap and update related data structures.
     *
     * @param idx index of FlowItem.
     * @param pos position of this FlowItem
     * @param height FlowItem height.
     */
    void RecordItem(int32_t idx, const FlowItemPosition& pos, float height);

    /**
     * @brief FInd the first item inside viewport in log_n time using endPosReverseMap_.
     *
     * @return index of the starting item.
     */
    int32_t FastSolveStartIndex() const;

    /**
     * @brief Find the last item inside viewport in log_n time using itemInfos_.
     *
     * @param mainSize main-axis length of viewport.
     * @return index of the item.
     */
    int32_t FastSolveEndIndex(float mainSize) const;

    /**
     * @brief Calculate and set the start position of next segment after filling the tail item of the current segment.
     *
     * @param itemIdx index of the current flow item.
     */
    void SetNextSegmentStartPos(int32_t itemIdx);

    /**
     * @brief Update member variables after measure.
     *
     * @param mainSize waterFlow length on the main axis.
     * @param overScroll whether overScroll is allowed. Might adjust offset if not.
     */
    void Sync(float mainSize, bool canOverScrollStart_, bool canOverScrollEnd_);

    /**
     * @brief Obtain index of last item recorded in Original layout.
     * @note in segmented layout, use itemInfos_ instead.
     */
    int32_t GetLastItem() const;

    void NotifyDataChange(int32_t index, int32_t count) override {};
    void NotifySectionChange(int32_t index) override {};
    void InitSegmentsForKeepPositionMode(const std::vector<WaterFlowSections::Section>& sections,
        const std::vector<WaterFlowSections::Section>& prevSections, int32_t start) override
    {}

    int32_t childrenCount_ = 0;

    float currentOffset_ = 0.0f;
    // 0.0f until itemEnd_ is true
    float maxHeight_ = 0.0f;

    // first index for onScrollIndex
    int32_t firstIndex_ = 0;

    // Map structure: [crossIndex, [index, {mainOffset, itemMainSize}]],
    using ItemMap = std::map<int32_t, std::map<int32_t, std::pair<float, float>>>;

    std::vector<ItemMap> items_ { ItemMap() };

    struct ItemInfo;
    // quick access to FlowItem by index
    std::vector<ItemInfo> itemInfos_;

    /**
     * @brief pair = { item bottom position, item index }.
     * A strictly increasing array of item endPos to speed up startIndex solver.
     * Only add to this map when a new endPos is greater than the last one in array.
     */
    std::vector<std::pair<float, int32_t>> endPosArray_;

    // Stores the start position of each segment.
    std::vector<float> segmentStartPos_ = { 0.0f };

    void PrintWaterFlowItems() const;

private:
    inline float TopMargin() const
    {
        if (margins_.empty()) {
            return 0.0f;
        }
        return (axis_ == Axis::VERTICAL ? margins_.front().top : margins_.front().left).value_or(0.0f);
    }
};

struct WaterFlowLayoutInfo::ItemInfo {
    ItemInfo() = default;
    ItemInfo(int32_t cross, float offset, float size) : crossIdx(cross), mainOffset(offset), mainSize(size) {}
    bool operator==(const ItemInfo& other) const
    {
        return crossIdx == other.crossIdx && mainOffset == other.mainOffset && mainSize == other.mainSize;
    }

    int32_t crossIdx = 0;
    float mainOffset = 0.0f;
    float mainSize = 0.0f;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_H
