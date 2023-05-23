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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WaterFlowLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(WaterFlowLayoutAlgorithm, LayoutAlgorithm);

public:
    explicit WaterFlowLayoutAlgorithm(WaterFlowLayoutInfo layoutInfo) : layoutInfo_(std::move(layoutInfo)) {}
    ~WaterFlowLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    WaterFlowLayoutInfo GetLayoutInfo()
    {
        return std::move(layoutInfo_);
    }

private:
    FlowItemPosition GetItemPosition(int32_t index);
    void FillViewport(float mainSize, LayoutWrapper* layoutWrapper);
    void ModifyCurrentOffsetWhenReachEnd(float mainSize, LayoutWrapper* layoutWrapper);
    LayoutConstraintF CreateChildConstraint(int32_t crossIndex, const RefPtr<WaterFlowLayoutProperty>& layoutProperty,
        const RefPtr<LayoutWrapper>& childLayoutWrapper);
    float ComputeCrossPosition(int32_t crossIndex) const;
    void InitialItemsCrossSize(
        const RefPtr<WaterFlowLayoutProperty>& layoutProperty, const SizeF& frameSize, int32_t childrenCount);
    int32_t GetChildIndexWithFooter(int32_t index) const
    {
        return index + layoutInfo_.footerIndex_ + 1;
    }
    float MeasuerFooter(LayoutWrapper* layoutWrapper);

    std::map<int32_t, float> itemsCrossSize_;
    std::map<int32_t, float> itemsCrossPosition_;
    Axis axis_ = Axis::VERTICAL;

    float mainGap_ = 0.0f;
    float crossGap_ = 0.0f;
    float mainSize_ = 0.0f;
    float footerMainSize_ = 0.0f;
    WaterFlowLayoutInfo layoutInfo_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_ALGORITHM_H
