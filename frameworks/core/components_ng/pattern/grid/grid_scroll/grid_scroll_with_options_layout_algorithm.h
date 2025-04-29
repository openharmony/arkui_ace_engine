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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_SCROLL_GRID_SCROLL_WITH_OPTIONS_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_SCROLL_GRID_SCROLL_WITH_OPTIONS_LAYOUT_ALGORITHM_H

#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GridScrollWithOptionsLayoutAlgorithm : public GridScrollLayoutAlgorithm {
    DECLARE_ACE_TYPE(GridScrollWithOptionsLayoutAlgorithm, GridScrollLayoutAlgorithm);

public:
    GridScrollWithOptionsLayoutAlgorithm(GridLayoutInfo gridLayoutInfo, uint32_t crossCount, uint32_t mainCount)
        : GridScrollLayoutAlgorithm(gridLayoutInfo, crossCount, mainCount) {};
    ~GridScrollWithOptionsLayoutAlgorithm() override = default;

private:
    void SkipLargeOffset(float mainSize, LayoutWrapper* layoutWrapper) override;
    void SkipIrregularLines(LayoutWrapper* layoutWrapper, bool forward) override;

    void LargeItemLineHeight(const RefPtr<LayoutWrapper>& itemWrapper) override;

    void GetTargetIndexInfoWithBenchMark(
        LayoutWrapper* layoutWrapper, bool isTargetBackward, int32_t targetIndex) override;

    void AdjustRowColSpan(
        const RefPtr<LayoutWrapper>& itemLayoutWrapper, LayoutWrapper* layoutWrapper, int32_t itemIndex) override;

    std::pair<int32_t, int32_t> GetCrossStartAndSpan(const GridLayoutOptions& options, int32_t itemIndex);

    std::pair<int32_t, int32_t> GetCrossStartAndSpanWithUserFunction(
        int32_t itemIndex, const GridLayoutOptions& options, int32_t firstIrregularIndex);

    void UpdateRealGridItemPositionInfo(
        const RefPtr<LayoutWrapper>& itemLayoutWrapper, int32_t mainIndex, int32_t crossIndex) override
    {}

    void UpdateMainLineOnReload(int32_t startIdx) override
    {
        /* With irregular items, mainLineIndex can't be determined by simple calculation. */
    }

    void FillOneLineForwardWithoutUpdatingStartIndex(
        float crossSize, float mainSize, LayoutWrapper* layoutWrapper) override
    {}

    std::pair<int32_t, int32_t> CalculateCachedCount(LayoutWrapper* layoutWrapper, int32_t cachedCount) override;
    int32_t CalculateStartCachedCount(const GridLayoutOptions& options, int32_t cachedCount);
    int32_t CalculateEndCachedCount(const GridLayoutOptions& options, int32_t cachedCount);

    void PreloadItems(LayoutWrapper* layoutWrapper) override;
    static bool PredictBuildItem(FrameNode& host, int32_t itemIdx, const GridPredictLayoutParam& param,
        std::map<int32_t, std::pair<int32_t, int32_t>> itemCrossMap);

    ACE_DISALLOW_COPY_AND_MOVE(GridScrollWithOptionsLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_SCROLL_GRID_SCROLL_WITH_OPTIONS_LAYOUT_ALGORITHM_H
