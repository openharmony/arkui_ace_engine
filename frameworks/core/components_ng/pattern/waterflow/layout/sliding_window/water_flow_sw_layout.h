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
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT WaterFlowSWLayout : public WaterFlowLayoutBase {
    DECLARE_ACE_TYPE(WaterFlowSWLayout, WaterFlowLayoutBase);

public:
    explicit WaterFlowSWLayout(const RefPtr<WaterFlowLayoutInfoSW>& info) : info_(info) {}
    void Measure(LayoutWrapper* wrapper) override;
    void Layout(LayoutWrapper* wrapper) override;

    void SetCanOverScroll(bool value) override
    {
        overScroll_ = value;
    }

private:
    void Init(const SizeF& frameSize);
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
     * @brief fills the viewport backward with cached idx -> lane mapping.
     */
    void RecoverFront(float viewportBound, int32_t& idx, int32_t minChildIdx);
    /**
     * @return new startPos of the filled lane.
     */
    float FillFrontHelper(const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, size_t laneIdx);
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
     * @brief fills the viewport backward with cached idx -> lane mapping.
     */
    void RecoverBack(float viewportBound, int32_t& idx, int32_t maxChildIdx);
    /**
     * @return new endPos of the filled lane.
     */
    float FillBackHelper(const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, size_t laneIdx);
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

    float MeasureChild(const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, size_t lane);

    void LayoutFooter(const OffsetF& paddingOffset, bool reverse);

    // convert FlowItem's index to children node index.
    inline int32_t nodeIdx(int32_t idx) const;

    LayoutWrapper* wrapper_ {};
    RefPtr<WaterFlowLayoutInfoSW> info_;

    int32_t itemCnt_ = 0;
    Axis axis_ {};
    std::vector<float> itemCrossSize_;
    float mainLen_ = 0.0f;
    float mainGap_ = 0.0f;
    float crossGap_ = 0.0f;

    bool overScroll_ = true;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_SW_LAYOUT_H
