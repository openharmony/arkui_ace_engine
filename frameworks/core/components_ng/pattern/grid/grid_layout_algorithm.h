/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"

namespace OHOS::Ace::NG {

// Try not to add more variables in [GridLayoutInfo] because the more state variables, the more problematic and the
// harder it is to maintain
struct GridLayoutInfo {
    Axis axis_ = Axis::VERTICAL;

    float currentOffset_ = 0.0f;
    float prevOffset_ = 0.0f;

    // index of first and last GridItem in viewport
    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;

    // index of first row and last row in viewport (assuming it's a vertical Grid)
    int32_t startMainLineIndex_ = 0;
    int32_t endMainLineIndex_ = 0;

    bool reachEnd_ = false;
    bool reachStart_ = false;

    // in vertical grid, this map is like: [rowIndex: [itemIndex: fractionCount], [itemIndex: fractionCount]]
    // for e.g, when a vertical grid has two [GridItem]s in first row, [gridMatrix_] is like [0: [0: 1fr], [1: 2fr]]
    std::map<int32_t, std::map<int32_t, uint32_t>> gridMatrix_;
    // in vertical grid, this map is like: [rowIndex: rowHeight]
    std::map<int32_t, float> lineHeightMap_;
};

class ACE_EXPORT GridLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(GridLayoutAlgorithm, LayoutAlgorithm);

public:
    GridLayoutAlgorithm(GridLayoutInfo gridLayoutInfo, uint32_t crossCount, uint32_t mainCount)
        : gridLayoutInfo_(std::move(gridLayoutInfo)), crossCount_(crossCount), mainCount_(mainCount) {};
    ~GridLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    GridLayoutInfo GetGridLayoutInfo();

    static void PrintGridMatrix(const std::map<int32_t, std::map<int32_t, uint32_t>>& gridMatrix);
    static void PrintLineHeightMap(const std::map<int32_t, float>& lineHeightMap);

private:
    void FillGridViewportAndMeasureChildren(float mainSize, float crossSize,
        const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper);
    void MeasureRecordedItems(float mainSize, float crossSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        LayoutWrapper* layoutWrapper, float& mainLength);

    // fill end of viewport
    void FillBlankAtStart(float mainSize, float crossSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        LayoutWrapper* layoutWrapper, float& mainLength);
    float FillNewLineForward(float crossSize, float mainSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        LayoutWrapper* layoutWrapper);

    // fill start of viewport
    void FillBlankAtEnd(float mainSize, float crossSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        LayoutWrapper* layoutWrapper, float& mainLength);
    float FillNewLineBackward(float crossSize, float mainSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        LayoutWrapper* layoutWrapper);

    LayoutConstraintF MakeMeasureConstraintForGridItem(float mainSize, float crossSize, uint32_t itemFractionCount,
        const RefPtr<GridLayoutProperty>& gridLayoutProperty) const;
    void StripItemsOutOfViewport(LayoutWrapper* layoutWrapper);
    void ModifyCurrentOffsetWhenReachEnd(float mainSize);

    GridLayoutInfo gridLayoutInfo_;

    uint32_t crossCount_ = 0;
    uint32_t mainCount_ = 0;
    int32_t currentMainLineIndex_ = 0; // it equals to row index in vertical grid

    ACE_DISALLOW_COPY_AND_MOVE(GridLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_ALGORITHM_H
