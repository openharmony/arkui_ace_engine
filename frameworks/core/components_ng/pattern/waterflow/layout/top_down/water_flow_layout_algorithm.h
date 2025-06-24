/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WaterFlowLayoutAlgorithm : public WaterFlowLayoutBase {
    DECLARE_ACE_TYPE(WaterFlowLayoutAlgorithm, WaterFlowLayoutBase);

public:
    explicit WaterFlowLayoutAlgorithm(const RefPtr<WaterFlowLayoutInfo>& layoutInfo) : layoutInfo_(layoutInfo) {}
    ~WaterFlowLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    bool PreloadItem(LayoutWrapper* host, int32_t itemIdx, int64_t deadline) override;

    bool MeasureInNextFrame() const override
    {
        return layoutInfo_->measureInNextFrame_;
    }
private:
    FlowItemPosition GetItemPosition(int32_t index);
    bool MeasureToTarget(LayoutWrapper* layoutWrapper, int32_t startFrom, std::optional<int64_t> cacheDeadline);
    void FillViewport(float mainSize, LayoutWrapper* layoutWrapper);
    void ModifyCurrentOffsetWhenReachEnd(float mainSize, LayoutWrapper* layoutWrapper);
    float ComputeCrossPosition(int32_t crossIndex) const;
    void InitialItemsCrossSize(
        const RefPtr<WaterFlowLayoutProperty>& layoutProperty, const SizeF& frameSize, int32_t childrenCount);
    int32_t GetChildIndexWithFooter(int32_t index) const
    {
        return index + layoutInfo_->footerIndex_ + 1;
    }
    void LayoutFooter(LayoutWrapper* layoutWrapper, const OffsetF& childFrameOffset, bool reverse);

    void SyncPreloadItem(LayoutWrapper* host, int32_t itemIdx) override;

    std::map<int32_t, float> itemsCrossSize_;
    std::map<int32_t, float> itemsCrossPosition_;
    Axis axis_ = Axis::VERTICAL;

    RefPtr<WaterFlowLayoutInfo> layoutInfo_;

    float mainGap_ = 0.0f;
    float crossGap_ = 0.0f;
    float mainSize_ = 0.0f;
    float footerMainSize_ = 0.0f;
    float footerMainStartPos_ = 0.0f;
    bool skipMeasure_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_ALGORITHM_H
