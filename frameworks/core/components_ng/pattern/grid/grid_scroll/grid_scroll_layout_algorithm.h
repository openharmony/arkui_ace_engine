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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_SCROLL_GRID_SCROLL_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_SCROLL_GRID_SCROLL_LAYOUT_ALGORITHM_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout_base_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GridScrollLayoutAlgorithm : public GridLayoutBaseAlgorithm {
    DECLARE_ACE_TYPE(GridScrollLayoutAlgorithm, GridLayoutBaseAlgorithm);

public:
    GridScrollLayoutAlgorithm(GridLayoutInfo gridLayoutInfo, uint32_t crossCount, uint32_t mainCount)
        : GridLayoutBaseAlgorithm(std::move(gridLayoutInfo)), crossCount_(crossCount), mainCount_(mainCount) {};
    ~GridScrollLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

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

    // Measure grid item which not exist in grid matrix already, need to place it and save to grid matrix.
    int32_t MeasureChild(const SizeF& frameSize, int32_t itemIndex, LayoutWrapper* layoutWrapper,
        const RefPtr<LayoutWrapper>& childLayoutWrapper, bool reverse);
    // Measure grid item which exist in grid matrix already, needn't to place it again.
    int32_t MeasureChildPlaced(const SizeF& frameSize, int32_t itemIndex, int32_t crossStart,
        LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& childLayoutWrapper);

    // Compote position of grid item in cross axis.
    float ComputeItemCrossPosition(LayoutWrapper* layoutWrapper, int32_t crossStart) const;
    // Find next valid cell when current is not valid.
    void GetNextGrid(int32_t& curMain, int32_t& curCross, bool reverse) const;
    // Find a valid cell to place grid item and save to grid matrix.
    bool CheckGridPlaced(int32_t index, int32_t main, int32_t cross, int32_t& mainSpan, int32_t& crossSpan);
    LayoutConstraintF CreateChildConstraint(float mainSize, float crossSize,
        const RefPtr<GridLayoutProperty>& gridLayoutProperty, int32_t crossStart, int32_t crossSpan) const;
    void StripItemsOutOfViewport(LayoutWrapper* layoutWrapper);
    void ModifyCurrentOffsetWhenReachEnd(float mainSize);
    void InitialItemsCrossSize(const RefPtr<GridLayoutProperty>& layoutProperty, const SizeF& frameSize);

    uint32_t crossCount_ = 0;
    uint32_t mainCount_ = 0;
    int32_t currentMainLineIndex_ = 0;        // it equals to row index in vertical grid
    std::map<int32_t, float> itemsCrossSize_; // grid item's size in cross axis.
    Axis axis_ = Axis::VERTICAL;

    // Store current index when place children.
    int32_t mainIndex_ = 0;
    int32_t crossIndex_ = 0;

    // Map structure: [index, crossPosition], store cross position of each item.
    std::map<int32_t, float> itemsCrossPosition_;

    ACE_DISALLOW_COPY_AND_MOVE(GridScrollLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_SCROLL_GRID_SCROLL_LAYOUT_ALGORITHM_H
