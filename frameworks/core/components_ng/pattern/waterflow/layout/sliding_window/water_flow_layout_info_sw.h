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

#include <deque>
#include <vector>

#include "core/components_ng/pattern/waterflow/water_flow_layout_algorithm_base.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_info_base.h"

namespace OHOS::Ace::NG {

/**
 * @brief Layout Data structure for Sliding Window version of WaterFlowLayout
 */
class WaterFlowLayoutInfoSW : public WaterFlowLayoutInfoBase {
    DECLARE_ACE_TYPE(WaterFlowLayoutInfoSW, WaterFlowLayoutInfoBase);

public:
    WaterFlowLayoutMode mode() const override
    {
        return WaterFlowLayoutMode::SLIDING_WINDOW;
    }

    float offset() const override;
    int32_t firstIdx() const override
    {
        return startIndex_;
    }

    void UpdateOffset(float delta) override
    {
        delta_ = delta;
    }

    int32_t GetCrossIndex(int32_t itemIndex) const override
    {
        if (idxToLane_.count(itemIndex)) {
            return static_cast<int32_t>(idxToLane_.at(itemIndex));
        }
        return -1;
    }

    OverScrollOffset GetOverScrolledDelta(float delta) const override;

    float CalcOverScroll(float mainSize, float delta) const override;

    bool ReachStart(float prevPos, bool firstLayout) const override;

    bool ReachEnd(float prevPos) const override;

    bool OutOfBounds() const override;

    float GetContentHeight() const override;

    float CalcTargetPosition(int32_t idx, int32_t crossIdx) const override;

    float GetDelta(float prevPos) const override
    {
        return offset() - prevPos;
    }

    int32_t GetMainCount() const override;
    int32_t GetCrossCount() const override
    {
        return lanes_.size();
    }

    void Reset() override;

    void Sync(float mainSize, float mainGap);

    /**
     * @brief Calculates distance from the item's top edge to the top of the viewport.
     * 
     * @param item idx
     * @param mainGap 
     * @return positive result when item's top edge is below viewport.
     */
    float DistanceToTop(int32_t item, float mainGap) const;

    /**
     * @brief Calculates distance from the item's bottom edge to the bottom of the viewport.
     * 
     * @param item idx
     * @param mainSize of the viewport
     * @param mainGap 
     * @return positive result when item's bottom edge is above viewport.
     */
    float DistanceToBottom(int32_t item, float mainSize, float mainGap) const;

    struct Lane;
    std::vector<Lane> lanes_;
    std::unordered_map<size_t, size_t> idxToLane_;

    float delta_ = 0.0f;
    float mainGap_ = 0.0f; // update this at the end of a layout

    struct ItemInfo;

private:
    inline float EndPos() const;
    inline float StartPos() const;
};

struct WaterFlowLayoutInfoSW::ItemInfo {
    int32_t idx = -1;
    float mainSize = 0.0f;
};

struct WaterFlowLayoutInfoSW::Lane {
    float startPos = 0.0f;
    float endPos = 0.0f;
    std::deque<ItemInfo> items_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_SW_H
