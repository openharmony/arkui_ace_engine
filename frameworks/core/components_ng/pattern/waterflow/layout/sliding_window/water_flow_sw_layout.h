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
#include "core/components_ng/pattern/waterflow/water_flow_layout_algorithm.h"

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

    void ApplyOffset(float mainSize, float offset);

    void MeasureToTarget(int32_t targetIdx);

    /**
     * @brief When the item is within or close to viewport, layout is preserved and we merely apply an offset.
     * But when jumping to an item further away, the current layout would be reset, and a new layout happens from that index.
     *
     * @param jumpIdx
     * @param align ScrollAlign
     * @param mainSize of the viewport
     */
    void MeasureOnJump(int32_t jumpIdx, ScrollAlign align, float mainSize);

    ScrollAlign ParseAutoAlign(int32_t jumpIdx, float mainSize, bool inView);

    /**
     * @brief fills the viewport backward until either condition is not satisfied.
     *
     * @param viewportBound 
     * @param minChildIdx smallest item index to fill before stopping.
     */
    void FillFront(float viewportBound, int32_t minChildIdx);

    /**
     * @brief fills the viewport forward until either condition is not satisfied.
     *
     * @param viewportBound 
     * @param maxChildIdx greatest item index to fill before stopping.
     */
    void FillBack(float viewportBound, int32_t maxChildIdx);

    void ClearFront();
    void ClearBack(float mainSize);

    void AdjustOverScroll(float mainSize);

    float MeasureChild(const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, size_t lane);

    void CheckReset();

    LayoutWrapper* wrapper_ {};
    RefPtr<WaterFlowLayoutInfoSW> info_;

    Axis axis_ {};
    std::vector<float> itemCrossSize_;
    float mainSize_ = 0.0f;
    float mainGap_ = 0.0f;
    float crossGap_ = 0.0f;

    bool overScroll_ = true;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_SW_LAYOUT_H
