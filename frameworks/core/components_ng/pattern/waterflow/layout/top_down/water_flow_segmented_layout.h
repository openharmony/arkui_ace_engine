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

#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"

namespace OHOS::Ace::NG {
// inherited by SegmentedLayout and SWLayout
class WaterFlowSegmentLayoutBase : public WaterFlowLayoutBase {
    DECLARE_ACE_TYPE(WaterFlowSegmentLayoutBase, WaterFlowLayoutBase);

protected:
    void InitEnv(LayoutWrapper* host)
    {
        wrapper_ = host;
        props_ = DynamicCast<WaterFlowLayoutProperty>(host->GetLayoutProperty());
    }

    /**
     * @brief init member variables for segmented WaterFlow with section info.
     *
     * @param options vector of SectionInfo
     * @param margins of each section.
     * @param frameSize of WaterFlow.
     */
    void SegmentedInit(const std::vector<WaterFlowSections::Section>& options,
        const std::vector<PaddingPropertyF>& margins, const SizeF& frameSize);

    /**
     * @brief Check if Sections info align with actual children and if internal data structures are consistent.
     */
    static bool IsSectionValid(const RefPtr<WaterFlowLayoutInfoBase>& info, int32_t childrenCnt);

    /**
     * @return true if the item is a cache item outside viewport.
     */
    inline bool IsCache(const RefPtr<WaterFlowLayoutInfoBase>& info, int32_t itemIdx) const
    {
        return !props_->GetShowCachedItemsValue(false) && (itemIdx < info->startIndex_ || itemIdx > info->endIndex_);
    }

    virtual void MeasureLazyChild(int32_t startIdx, int32_t endIdx) const = 0;

    LayoutWrapper* wrapper_ {};
    RefPtr<WaterFlowLayoutProperty> props_;
    Axis axis_ = Axis::VERTICAL;
    // [segmentIdx, [crossIdx, item's width]]
    std::vector<std::vector<float>> itemsCrossSize_;

    // rowGap and columnGap for each segment
    std::vector<float> crossGaps_;
    std::vector<float> mainGaps_;
};

class WaterFlowSegmentedLayout : public WaterFlowSegmentLayoutBase {
    DECLARE_ACE_TYPE(WaterFlowSegmentedLayout, WaterFlowSegmentLayoutBase);

public:
    explicit WaterFlowSegmentedLayout(const RefPtr<WaterFlowLayoutInfo>& layoutInfo) : info_(layoutInfo) {}
    ~WaterFlowSegmentedLayout() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    bool PreloadItem(LayoutWrapper* host, int32_t itemIdx, int64_t deadline) override;

private:
    /**
     * @brief Initialize member variables from LayoutProperty.
     *
     * @param frameSize of WaterFlow component.
     */
    void Init(const SizeF& frameSize);

    /**
     * @brief check if any items in view have changed height.
     *
     * @return index of the first dirty item. -1 if no dirty item found.
     */
    int32_t CheckDirtyItem() const;

    /**
     * @brief init regular WaterFlow with a single segment.
     *
     * @param frameSize
     */
    void RegularInit(const SizeF& frameSize);
    void InitFooter(float crossSize);

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
     * @param cacheDeadline when called during a cache layout, return early if deadline is reached.
     * @param force explicitly measure items even if their heights are user-defined.
     */
    void MeasureToTarget(int32_t targetIdx, std::optional<int64_t> cacheDeadline, bool force = false);

    /**
     * @brief Helper to measure a single FlowItems.
     *
     * @param idx index of the FlowItem.
     * @param crossIdx column (when vertical) index of the target FlowItem.
     * @param userDefMainSize user-defined main-axis size of the FlowItem.
     * @return LayoutWrapper of the FlowItem.
     */
    RefPtr<LayoutWrapper> MeasureItem(
        int32_t idx, std::pair<int32_t, float> position, float userDefMainSize, bool isCache) const;

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

    void SyncPreloadItem(LayoutWrapper* host, int32_t itemIdx) override;

    void MeasureLazyChild(int32_t startIdx, int32_t endIdx) const override;

    RefPtr<WaterFlowSections> sections_;

    // WaterFlow node's main-axis length
    float mainSize_ = 0.0f;

    // offset to apply after a ResetAndJump
    std::optional<float> postJumpOffset_;

    RefPtr<WaterFlowLayoutInfo> info_;

    ACE_DISALLOW_COPY_AND_MOVE(WaterFlowSegmentedLayout);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_SEGMENTED_LAYOUT_H
