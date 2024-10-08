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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_SW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_SW_H

#include <algorithm>
#include <deque>
#include <vector>

#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_info_base.h"

namespace OHOS::Ace::NG {
constexpr int32_t EMPTY_NEW_START_INDEX = -1;
constexpr int32_t INVALID_NEW_START_INDEX = -2;
/**
 * @brief Layout data structure for Sliding Window version of WaterFlowLayout
 */
class WaterFlowLayoutInfoSW : public WaterFlowLayoutInfoBase {
    DECLARE_ACE_TYPE(WaterFlowLayoutInfoSW, WaterFlowLayoutInfoBase);

public:
    WaterFlowLayoutMode Mode() const override
    {
        return WaterFlowLayoutMode::SLIDING_WINDOW;
    }

    float Offset() const override
    {
        return totalOffset_;
    }
    int32_t FirstIdx() const override
    {
        return startIndex_;
    }

    void UpdateOffset(float delta) override
    {
        delta_ += delta;
        synced_ = false;
    }

    float CalibrateOffset() override;

    int32_t GetCrossIndex(int32_t itemIndex) const override;

    OverScrollOffset GetOverScrolledDelta(float delta) const override;

    float CalcOverScroll(float mainSize, float delta) const override;

    bool ReachStart(float prevPos, bool firstLayout) const override;

    bool ReachEnd(float prevPos, bool firstLayout) const override;

    bool OutOfBounds() const override;

    float GetContentHeight() const override;

    float CalcTargetPosition(int32_t idx, int32_t crossIdx) const override;

    float GetDelta(float prevPos) const override
    {
        return prevPos - totalOffset_;
    }

    int32_t GetMainCount() const override;
    int32_t GetCrossCount() const override
    {
        if (lanes_.empty()) {
            return 0;
        }
        return lanes_[0].size();
    }

    float CurrentPos() const override
    {
        return 0.0f;
    }
    float TopFinalPos() const override;
    float BottomFinalPos(float viewHeight) const override;

    void Reset() override;

    bool IsMisaligned() const override;

    void InitSegments(const std::vector<WaterFlowSections::Section>& sections, int32_t start) override;

    /**
     * @brief reset layout data and setting up a base position for each lane.
     *
     * @param laneBasePos base value for lane's start&end position.
     * When not provided, lane positions are not modified.
     */
    void ResetWithLaneOffset(std::optional<float> laneBasePos);

    void BeginUpdate()
    {
        synced_ = false;
    }
    /**
     * @brief synchronize data after update is completed.
     *
     * @param itemCnt number of FlowItems.
     * @param mainSize main-axis length of the viewport.
     * @param mainGap main-axis gap between items.
     */
    void Sync(int32_t itemCnt, float mainSize, const std::vector<float>& mainGap);

    /**
     * @brief Mark beginning of cache item layout and save current lanes_ state.
     *
     */
    void BeginCacheUpdate();
    /**
     * @brief mark synced and restore lanes_ after cache item layout
     */
    void EndCacheUpdate();

    /**
     * @brief Calculates distance from the item's top edge to the top of the viewport.
     *
     * @param item index
     * @return positive result when item's top edge is below viewport.
     */
    float DistanceToTop(int32_t item, float mainGap) const;

    /**
     * @brief Calculates distance from the item's bottom edge to the bottom of the viewport.
     *
     * @param item index
     * @param mainSize of the viewport
     * @return positive result when item's bottom edge is above viewport.
     */
    float DistanceToBottom(int32_t item, float mainSize, float mainGap) const;

    int32_t StartIndex() const;
    int32_t EndIndex() const;
    inline bool ItemInView(int32_t idx) const
    {
        return !lanes_.empty() && idx >= StartIndex() && idx <= EndIndex();
    }
    /**
     * @param idx of the item.
     * @return true the item is approximately within 1 full-viewport distance.
     */
    bool ItemCloseToView(int32_t idx) const;

    /**
     * @return maximum end position of items in lanes_.
     */
    float EndPos() const;
    inline float EndPosWithMargin() const
    {
        return EndPos() + BotMargin();
    }
    /**
     * @return minimum start position of items in lanes_.
     */
    float StartPos() const;
    inline float StartPosWithMargin() const
    {
        return StartPos() - TopMargin();
    }

    void ClearDataFrom(int32_t idx, const std::vector<float>& mainGap);

    inline float TopMargin() const
    {
        if (margins_.empty()) {
            return 0.0f;
        }
        return (axis_ == Axis::VERTICAL ? margins_.front().top : margins_.front().left).value_or(0.0f);
    }
    inline float BotMargin() const
    {
        if (margins_.empty()) {
            return 0.0f;
        }
        return (axis_ == Axis::VERTICAL ? margins_.back().bottom : margins_.back().right).value_or(0.0f);
    }

    /**
     * @brief prepare lanes in the current section.
     *
     * @param idx current item index
     * @param fillBack true if preparing in the forward direction (prevIdx < curIdx).
     */
    void PrepareSectionPos(int32_t idx, bool fillBack);

    void NotifyDataChange(int32_t index, int32_t count) override;
    void UpdateLanesIndex(int32_t updateIdx);
    void InitSegmentsForKeepPositionMode(const std::vector<WaterFlowSections::Section>& sections,
        const std::vector<WaterFlowSections::Section>& prevSections, int32_t start) override;

    struct Lane;
    /**
     * @brief lanes in multiple sections.
     * REQUIRES: In stable state (outside update phase), only items inside viewport are in lanes_.
     */
    std::vector<std::vector<Lane>> lanes_;
    /**
     * @brief mapping of all items previously or currently in lanes_.
     * REQUIRES: All items in lanes_ are in idxToLane_.
     */
    std::unordered_map<int32_t, size_t> idxToLane_;

    float delta_ = 0.0f;
    /* Record total offset when continuously scrolling. No longer accurate after jump. Reset when reach top */
    float totalOffset_ = 0.0f;

    std::vector<float> mainGap_; // update this at the end of a layout

    // maximum content height encountered so far, mainly for comparing content and viewport height
    float maxHeight_ = 0.0f;
    float footerHeight_ = 0.0f;

    // record the new startIndex_ after changing the datasource, corresponding to the old startIndex_.
    int32_t newStartIndex_ = EMPTY_NEW_START_INDEX;

private:
    inline void PrepareJump();

    void InitSegmentTails(const std::vector<WaterFlowSections::Section>& sections);
    void InitLanes(const std::vector<WaterFlowSections::Section>& sections, const int32_t start);

    /**
     * @brief prepare newStartIndex_
     *
     * @return false if the value of newStartIndex_ is INVALID.
     */
    bool PrepareNewStartIndex();

    /**
     * @brief Adjust Lanes_ when the change happens in front of lane.
     *
     * @param sections the new sections after change.
     * @param start segment index of the first change section.
     * @param prevSegIdx segment index of original startIndex_ belongs to.
     *
     * @return true if adjust successfully.
     */
    bool AdjustLanes(const std::vector<WaterFlowSections::Section>& sections,
        const WaterFlowSections::Section& prevSection, int32_t start, int32_t prevSegIdx);

    void ClearData();

    std::unique_ptr<decltype(lanes_)> savedLanes_; // temporarily store current lanes_ state in Cache Item operations.

    /* cache */
    float startPos_ = 0.0f;
    float endPos_ = 0.0f;

    bool synced_ = false;

    struct ItemInfo;
};

struct WaterFlowLayoutInfoSW::ItemInfo {
    int32_t idx = -1;
    float mainSize = 0.0f;
};

struct WaterFlowLayoutInfoSW::Lane {
    std::string ToString() const;

    float startPos = 0.0f;
    float endPos = 0.0f;
    std::deque<ItemInfo> items_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_SW_H
