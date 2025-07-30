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
        int32_t row; /**< Row index of the starting row. */
        int32_t idx; /**< Index of the starting GridItem in the starting row. */
        float pos;   /**< Main position of the starting row in ViewBox. The new currentOffset_ */
    };
    /**
     * @brief Finds the starting row based on GridLayoutInfo::currentOffset_.
     *
     * @param mainGap The main-axis gap between GridItems.
     * @return The StartingRowInfo object containing the starting row information.
     */
    StartingRowInfo FindStartingRow(float mainGap);

    struct RangeInfo {
        int32_t startRow = 0; /**< Row index of the starting row. */
        int32_t startIdx = 0; /**< Index of the starting GridItem in layout range. */
        float pos = 0.0f;     /**< Main position of the starting row in ViewBox. The new currentOffset_ */
        int32_t endRow = 0;   /**< Row index of the last row in layout range. */
        int32_t endIdx = -1;  /**< index of the last GridItem in layout range. */
    };
    /**
     * @brief Finds the layout range when jumping to a new index.
     *
     * @param jumpIdx The item index.
     * @param jumpLineIdx The index of the jump line.
     * @param mainGap The main gap between rows.
     * @return The layout range info after jumping to the target line.
     */
    RangeInfo FindRangeOnJump(int32_t jumpIdx, int32_t jumpLineIdx, float mainGap);

    /**
     * @brief Solves the forward end index for a given target length and starting line index.
     *
     * @param mainGap The main gap between grid items.
     * @param targetLen The target length for the forward traversal.
     * @param line The starting line index.
     * @return { ending line index, ending GridItem index }
     */
    std::pair<int32_t, int32_t> SolveForwardForEndIdx(float mainGap, float targetLen, int32_t line);

private:
    /**
     * @brief Find the starting row after offsetting by [targetLen] going forward (scrolling down).
     *
     * @param mainGap The gap length between rows.
     * @param targetLen The target length to offset.
     * @param idx The index of the current starting row
     */
    StartingRowInfo SolveForward(float mainGap, float targetLen, int32_t idx);

    /**
     * @brief Find the new starting row after offsetting by [targetLen] going backward (scrolling up).
     *
     * @param mainGap The gap length between rows.
     * @param targetLen The target length to offset.
     * @param idx The index of the current starting row
     */
    StartingRowInfo SolveBackward(float mainGap, float targetLen, int32_t idx);

    /**
     * @brief Looks for multi-row items in the row.
     *
     * @param idx The current row index.
     * @return [first row occupied by items in the current row, the corresponding item index].
     */
    std::pair<int32_t, int32_t> CheckMultiRow(int32_t idx);

    const GridLayoutInfo* info_;
    const LayoutWrapper* wrapper_;
    const GridLayoutOptions* opts_;

    ACE_DISALLOW_COPY_AND_MOVE(GridLayoutRangeSolver);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_LAYOUT_RANGE_SOLVER_H
