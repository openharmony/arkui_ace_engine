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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_LAYOUT_RANGE_SOLVER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_LAYOUT_RANGE_SOLVER_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"

namespace OHOS::Ace::NG {
/**
 * @brief The GridLayoutRangeSolver class is responsible for solving the layout range of a grid with irregular items.
 *
 * It calculates the starting row information based on currentOffset and lineHeights.
 */
class GridLayoutRangeSolver {
public:
    GridLayoutRangeSolver(GridLayoutInfo* info, LayoutWrapper* wrapper);
    ~GridLayoutRangeSolver() = default;

    /**
     * @brief Structure to store the information of the starting row.
     */
    struct StartingRowInfo {
        int32_t row;  /**< Row index of the starting row. */
        float pos;    /**< Main position of the starting row in the contentRect. */
        float height; /**< Height of the starting row. */
    };

    /**
     * @brief Finds the starting row.
     *
     * @param mainGap The main-axis gap between GridItems.
     * @return The StartingRowInfo object containing the starting row information.
     */
    StartingRowInfo FindStartingRow(float mainGap);

private:
    /**
     * @brief Adds the next rows to the layout.
     *
     * Because of irregular items, we might add multiples rows in a single iteration.
     *
     * @param mainGap The gap between rows.
     * @param row The index of the next row.
     * @return A pair containing the number of rows added and the total height of the added rows.
     */
    std::pair<int32_t, float> AddNextRows(float mainGap, int32_t row);

    const GridLayoutInfo* info_;
    const LayoutWrapper* wrapper_;
    const GridLayoutOptions* opts_;

    ACE_DISALLOW_COPY_AND_MOVE(GridLayoutRangeSolver);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_LAYOUT_RANGE_SOLVER_H
