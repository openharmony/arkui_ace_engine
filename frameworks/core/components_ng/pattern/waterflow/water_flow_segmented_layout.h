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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_SEGMENTED_LAYOUT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_SEGMENTED_LAYOUT_H

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_info.h"

namespace OHOS::Ace::NG {
class WaterFlowSegmentedLayout : public WaterFlowLayoutBase {
    DECLARE_ACE_TYPE(WaterFlowSegmentedLayout, WaterFlowLayoutBase);

public:
    explicit WaterFlowSegmentedLayout(WaterFlowLayoutInfo layoutInfo) : info_(std::move(layoutInfo)) {}
    ~WaterFlowSegmentedLayout() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    WaterFlowLayoutInfo GetLayoutInfo() override
    {
        return std::move(info_);
    }

    void SetCanOverScroll(bool value) override
    {
        overScroll_ = value;
    }

private:
    /**
     * @brief Initialize member variables from LayoutProperty.
     *
     * @param frameSize of WaterFlow component.
     */
    void Init(const SizeF& frameSize);

    /**
     * @brief init member variables for segmented WaterFlow with section info.
     *
     * @param options vector of SectionInfo
     * @param frameSize of WaterFlow.
     */
    void SegmentInit(const std::vector<WaterFlowSections::Section>& options, const SizeF& frameSize);

    /**
     * @brief init regular WaterFlow with a single segment.
     *
     * @param frameSize
     */
    void RegularInit(const SizeF& frameSize);
    void InitFooter(float crossSize);

    /**
     * @brief Measure self before measuring children.
     *
     * @return [idealSize given by parent, whether measure is successful (need to adapt to children size if not)].
     */
    std::pair<SizeF, bool> PreMeasureSelf();

    /**
     * @brief Measure self after measuring children. Only when pre-measure failed.
     *
     * @param size ideal content size from parent.
     */
    void PostMeasureSelf(SizeF size);

    void MeasureOnOffset();

    /**
     * @brief Fills the viewport with new items.
     *
     * WaterFlow's item map only supports orderly forward layout,
     * because the position of a new item always depends on previous items.
     *
     * @param startIdx index of the first new FlowItem.
     */
    void Fill(int32_t startIdx);

    /**
     * @brief Obtain sizes of new FlowItems up to [targetIdx] and record them in ItemMap.
     *
     * If user has defined a size for any FlowItem, use that size instead of calling child->Measure.
     *
     * @param targetIdx index of the last FlowItem to measure.
     */
    void MeasureToTarget(int32_t targetIdx);

    /**
     * @brief Helper to measure a single FlowItems.
     *
     * @param props LayoutProps.
     * @param idx index of the FlowItem.
     * @param crossIdx column (when vertical) index of the target FlowItem.
     * @param userDefMainSize user-defined main-axis size of the FlowItem.
     * @return LayoutWrapper of the FlowItem.
     */
    inline RefPtr<LayoutWrapper> MeasureItem(
        const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, int32_t crossIdx, float userDefMainSize) const;

    /**
     * @brief Layout a FlowItem at [idx].
     *
     * @param idx FlowItem index.
     * @param padding top-left padding of WaterFlow component.
     * @param isReverse need to layout in reverse.
     */
    void LayoutItem(int32_t idx, float crossPos, const OffsetF& padding, bool isReverse);

    void MeasureOnJump(int32_t jumpIdx);

    /**
     * @brief Parse AUTO align value. If jump item is above viewport, use START; if it's below viewport, use END.
     *
     * @param item ItemInfo of the FlowItem to jump to.
     * @return transformed ScrollAlign value.
     */
    ScrollAlign TransformAutoScroll(const WaterFlowLayoutInfo::ItemInfo& item) const;

    /**
     * @brief Calculate the new offset after jumping to the target item.
     *
     * @param item  ItemInfo of the FlowItem to jump to.
     * @return new offset after jumping.
     */
    float SolveJumpOffset(const WaterFlowLayoutInfo::ItemInfo& item) const;

    LayoutWrapper* wrapper_ {};
    RefPtr<WaterFlowSections> sections_;

    // [segmentIdx, [crossIdx, item's width]]
    std::vector<std::vector<float>> itemsCrossSize_;
    Axis axis_ = Axis::VERTICAL;

    // rowGap and columnGap for each segment
    std::vector<float> crossGaps_;
    std::vector<float> mainGaps_;

    // WaterFlow node's main-axis length
    float mainSize_ = 0.0f;

    // offset to apply after a ResetAndJump
    float postJumpOffset_ = 0.0f;

    WaterFlowLayoutInfo info_;

    // true if WaterFlow can be overScrolled
    bool overScroll_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(WaterFlowSegmentedLayout);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_SEGMENTED_LAYOUT_H
