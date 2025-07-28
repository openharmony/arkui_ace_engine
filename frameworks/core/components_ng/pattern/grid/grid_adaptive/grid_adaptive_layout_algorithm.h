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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ADAPTIVE_GRID_ADAPTIVE_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ADAPTIVE_GRID_ADAPTIVE_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_base_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"

namespace OHOS::Ace::NG {

// Effect when rowsTemplate and columnsTemplate are not setted, this algorithm effect these attribute:
// columnsGap | rowsGap | layoutDirection | maxCount | minCount | cellLength.
class ACE_EXPORT GridAdaptiveLayoutAlgorithm : public GridLayoutBaseAlgorithm {
    DECLARE_ACE_TYPE(GridAdaptiveLayoutAlgorithm, GridLayoutBaseAlgorithm);

public:
    explicit GridAdaptiveLayoutAlgorithm(GridLayoutInfo& gridLayoutInfo)
        : GridLayoutBaseAlgorithm(gridLayoutInfo) {};
    ~GridAdaptiveLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    OffsetF CalculateChildOffset(int32_t index, LayoutWrapper* layoutWrapper);

    // cell size of grid.
    SizeF gridCellSize_;
    // grid cell count in main axis.
    int32_t mainCount_ = 0;
    // grid cell count in cross axis.
    int32_t crossCount_ = 0;
    // total count has shown.
    int32_t displayCount_ = 0;

    int32_t rowCount_ = 0;
    int32_t columnCount_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(GridAdaptiveLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ADAPTIVE_GRID_ADAPTIVE_LAYOUT_ALGORITHM_H
