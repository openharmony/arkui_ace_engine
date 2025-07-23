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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_GRID_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_GRID_LAYOUT_ALGORITHM_H

#include <utility>

#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout_base_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GridLayoutAlgorithm : public GridLayoutBaseAlgorithm {
    DECLARE_ACE_TYPE(GridLayoutAlgorithm, GridLayoutBaseAlgorithm);

public:
    GridLayoutAlgorithm(GridLayoutInfo gridLayoutInfo, int32_t crossCount, int32_t mainCount)
        : GridLayoutBaseAlgorithm(std::move(gridLayoutInfo)), crossCount_(crossCount), mainCount_(mainCount) {};
    ~GridLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void InitGridCeils(LayoutWrapper* layoutWrapper, const SizeF& idealSize);
    bool CheckGridPlaced(int32_t index, int32_t row, int32_t col, int32_t& rowSpan, int32_t& colSpan);
    void GetNextGrid(int32_t& curRow, int32_t& curCol) const;
    OffsetF ComputeItemPosition(LayoutWrapper* layoutWrapper, int32_t row, int32_t col, int32_t& rowSpan,
        int32_t& colSpan, const RefPtr<LayoutWrapper>& childLayoutWrapper) const;
    LayoutConstraintF CreateChildConstraint(const SizeF& idealSize, const RefPtr<GridLayoutProperty>& layoutProperty,
        int32_t row, int32_t col, int32_t& rowSpan, int32_t& colSpan,
        const RefPtr<LayoutProperty>& childLayoutProperty) const;
    float GetItemSize(int32_t row, int32_t col, bool height) const;
    GridItemRect GetItemRect(const RefPtr<GridLayoutProperty>& gridLayoutProperty,
        const RefPtr<GridItemLayoutProperty>& childLayoutProperty, int32_t index) const;
    void PrintConflictingPositionLog(
        int32_t itemIndex, GridItemRect rect, int32_t rowIndex, int32_t colIndex, int32_t rowSpan, int32_t colSpan);
    void UpdateGridLayoutInfo();

    int32_t crossCount_ = 0;
    int32_t mainCount_ = 0;
    bool isVertical_ = true;
    bool rightToLeft_ = false;

    float rowsGap_ = 0;
    float columnsGap_ = 0;

    // Map structure: [rowIndex, [columnIndex - (width, height)]].
    std::map<int32_t, std::map<int32_t, SizeF>> gridCells_;

    // Map structure: [index, [positionX, positionY]], store position of each item.
    std::map<int32_t, OffsetF> itemsPosition_;

    ACE_DISALLOW_COPY_AND_MOVE(GridLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_GRID_LAYOUT_ALGORITHM_H
