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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_FILLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_FILLER_H

#include "base/utils/noncopyable.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"

namespace OHOS::Ace::NG {
/**
 * @brief The GridIrregularFiller class is responsible for filling an irregular grid layout with items.
 *
 * It calculates the positions and sizes of the items based on the provided layout information.
 * The GridItems can have varying row and column lengths.
 */
class GridIrregularFiller {
    ACE_DISALLOW_COPY_AND_MOVE(GridIrregularFiller);

public:
    /**
     * @brief Constructs a GridIrregularFiller object.
     * REQUIRES: All indices prior to GridLayoutInfo::startIndex_ should already be in the GridMatrix.
     */
    GridIrregularFiller(GridLayoutInfo* info, LayoutWrapper* wrapper);
    ~GridIrregularFiller() = default;

    struct FillParameters {
        std::vector<float> crossLens; /**< The column widths of items. */
        float targetLen = 0.0f;       /**< The target length of the main axis (total row height to fill). */
        float crossGap = 0.0f;        /**< The cross-axis gap between items. */
        float mainGap = 0.0f;         /**< The main-axis gap between items. */
    };

    /**
     * @brief Fills the grid with items in the forward direction.
     *
     * EFFECT: updates GridLayoutInfo::endIndex_ and GridLayoutInfo::endMainLineIndex_ to the last filled item.
     *
     * @param params The FillParameters object containing the fill parameters.
     * @param startIdx The line index to start filling from.
     * @return The total length filled on the main axis.
     */
    float Fill(const FillParameters& params, int32_t startIdx);

    /**
     * @brief Fills the gridMatrix in forward direction until the target GridItem is included. Measure isn't performed,
     * and lineHeightMap_ isn't updated.
     *
     * EFFECT: updates GridLayoutInfo::endIndex_ to targetIdx and GridLayoutInfo::endMainLineIndex_ to the
     * corresponding line index.
     *
     * @param startingLine The starting line index.
     * @param targetIdx The target GridItem index to fill.
     */
    void FillMatrixOnly(int32_t startingLine, int32_t targetIdx);

    /**
     * @brief Measures the GridItems in the backward direction until the target length is filled.
     *
     * REQUIRES: GridMatrix prior to jumpIndex_ is already filled.
     *
     * @param params The fill parameters for measuring GridItems.
     * @param jumpLineIdx The line index to start measuring backward.
     * @return The total length filled on the main axis.
     */
    float MeasureBackward(const FillParameters& params, int32_t jumpLineIdx);

private:
    /**
     * @brief Fills one GridItem into the Grid.
     */
    void FillOne();

    /**
     * @brief Updates the length of the main axis after filling a row or column. Add heights in range [prevRow, curRow).
     *
     * @param len A reference to the filled length on the main axis.
     * @param prevRow The index of the previous row or column.
     * @param curRow The index of the current row or column.
     * @param mainGap The gap between main axis items.
     */
    void UpdateLength(float& len, int32_t prevRow, int32_t curRow, float mainGap);

    /**
     * @brief Measures a GridItem at endIndex_ and updates the grid layout information.
     *
     * @param params The FillParameters object containing the fill parameters.
     * @param col The column index where the item is being added.
     * @param row The row index where the item is being added.
     */
    void MeasureItem(const FillParameters& params, int32_t col, int32_t row);

    /**
     * @brief Initializes the position of the filler in the grid to GridLayoutInfo::startIndex_.
     *
     * @param lineIdx The line index of the starting position.
     */
    void InitPos(int32_t lineIdx);

    /**
     * @brief Try to find the GridItem with target index in the grid matrix.
     *
     * @param target The target index of the GridItem.
     * @return True if target index is already recorded in the matrix.
     */
    bool FindNextItem(int32_t target);

    /**
     * @brief Advances the position of the filler in the grid.
     *
     * @return True if the position is successfully advanced, false if the end of the grid is reached.
     */
    bool AdvancePos();

    /**
     * @brief Checks if the grid is full based on the target length of the main axis.
     *
     * @param len Currently filled length.
     * @param targetLen The target length of the main axis.
     * @return True if the grid is full, false otherwise.
     */
    inline bool IsFull(float len, float targetLen);

    /**
     * @brief Checks if an item can fit in the grid based on its width and the available space in the current row or
     * column.
     *
     * @param it An iterator pointing to the current row or column in the grid layout information.
     * @param itemWidth The width of the item.
     * @return The cross-axis index where the item can fit. Returns -1 if it can't fit on the current row.
     */
    int32_t FitItem(const decltype(GridLayoutInfo::gridMatrix_)::iterator& it, int32_t itemWidth);

    /**
     * @brief Finds the top row index of an item in the grid.
     *
     * @param row The row index of the item's bottom-left tile.
     * @param col The column index of the item's bottom-left tile.
     * @return The top row index of the GridItem.
     */
    int32_t FindItemTopRow(int32_t row, int32_t col) const;

    int32_t posY_ = 0;  /**< The current row index in the grid. */
    int32_t posX_ = -1; /**< The current column index in the grid. */

    GridLayoutInfo* info_;
    LayoutWrapper* wrapper_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_FILLER_H
