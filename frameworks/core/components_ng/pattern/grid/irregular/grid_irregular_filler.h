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

#include <unordered_set>

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
        float crossGap = 0.0f;        /**< The cross-axis gap between items. */
        float mainGap = 0.0f;         /**< The main-axis gap between items. */
    };

    struct FillResult {
        float length = 0.0f;           /**< The total length filled on the main axis. */
        int32_t endMainLineIndex = -1; /**< The last line filled to reach target length. */
        int32_t endIndex = -1;         /**< The index of the last item measured. */
    };

    /**
     * @brief Fills the grid with items in the forward direction.
     *
     * @param params The FillParameters object containing the fill parameters.
     * @param targetLen The target length of the main axis (total row height to fill).
     * @param startingLine The line index to start filling from.
     */
    FillResult Fill(const FillParameters& params, float targetLen, int32_t startingLine);

    /**
     * @brief Fills the grid with items in the forward direction until targetIdx is measured.
     *
     * @param params The FillParameters object containing the fill parameters.
     * @param targetIdx The target index to fill up to.
     * @param startingLine The line index to start filling from.
     */
    void FillToTarget(const FillParameters& params, int32_t targetIdx, int32_t startingLine);

    /**
     * @brief Fills the gridMatrix in forward direction until the target GridItem is included. Measure isn't performed,
     * and lineHeightMap_ isn't updated.
     *
     * @param targetIdx The target GridItem index to fill.
     *
     * @return Line index of the last filled line.
     */
    int32_t FillMatrixOnly(int32_t targetIdx);

    /**
     * @brief Fills the gridMatrix in forward direction until lines prior to [targetLine] are all filled.
     * Measure isn't performed, and lineHeightMap_ isn't updated.
     *
     * @param startingLine The starting line index.
     * @param targetLine The target GridItem index to fill up to.
     *
     * @return Last item index filled to reach [targetLine].
     */
    int32_t FillMatrixByLine(int32_t startingLine, int32_t targetLine);

    /**
     * @brief Measures the GridItems in the backward direction until the target length is filled.
     *
     * REQUIRES: GridMatrix prior to startingLine is already filled.
     *
     * @param params The fill parameters for measuring GridItems.
     * @param targetLen The target length of the main axis (total row height to fill).
     * @param startingLine The line index to start measuring backward.
     * @return The total length filled on the main axis.
     */
    float MeasureBackward(const FillParameters& params, float targetLen, int32_t startingLine);

    /**
     * @brief Measures the GridItems in the backward direction until the target line is measured.
     *
     * REQUIRES: GridMatrix prior to startingLine is already filled.
     *
     * @param params The fill parameters for measuring GridItems.
     * @param targetLine The target line index to fill backward to.
     * @param startingLine The line index to start measuring backward.
     */
    void MeasureBackwardToTarget(const FillParameters& params, int32_t targetLine, int32_t startingLine);

    /**
     * @brief Check if the line contains non-top-left tiles of irregular items (represented by idx < 0 in the matrix).
     * These items would be skipped in a a regular forward Fill, so we need to use a backward traversal to measure them.
     * If the line doesn't contain any irregulars, no measure is performed in this function.
     *
     * REQUIRES: GridMatrix prior to [line] is already filled.
     *
     * @param params FillParameters
     * @param line index to prepare and measure.
     */
    void MeasureLineWithIrregulars(const FillParameters& params, int32_t line);

    /**
     * @brief Measures a GridItem and updates the grid layout information.
     *
     * @param params The FillParameters object containing the fill parameters.
     * @param itemIdx The index of the GridItem.
     * @param col The column index where the item is being added.
     * @param row The row index where the item is being added.
     * @return item height and LayoutConstraint
     */
    std::pair<float, LayoutConstraintF> MeasureItem(
        const FillParameters& params, int32_t itemIdx, int32_t col, int32_t row, bool isCache);

    void MeasureItem(const FillParameters& params, LayoutWrapper* child, int32_t itemIdx, int32_t col, int32_t row);

private:
    std::pair<float, LayoutConstraintF> MeasureItemInner(
        const FillParameters& params, LayoutWrapper* node, int32_t itemIdx, int32_t col, int32_t row);

    /**
     * @brief Fills one GridItem into the Grid.
     *
     * @param idx Item index to fill in the matrix.
     */
    void FillOne(int32_t idx);

    /**
     * @brief Updates the length of the main axis. Add heights in range [row, rowBound).
     * Return immediately when [targetLen] is reached.
     *
     * @param len A reference to the filled length on the main axis.
     * @param row A reference to the current row index.
     * @param rowBound Upper bound of row index to add heights.
     * @return true if len >= targetLen after adding height of [row]. At this point, row = last
     */
    bool UpdateLength(float& len, float targetLen, int32_t& row, int32_t rowBound, float mainGap) const;

    /**
     * @brief Initializes the position of the filler in the grid to GridLayoutInfo::startIndex_.
     *
     * @param lineIdx The line index of the starting position.
     * REQUIRES: lineIdx is a valid startMainLineIndex_,
     * i.e. the top-left corner of an item resides in the first column.
     * @return startIndex_ - 1
     */
    int32_t InitPos(int32_t lineIdx);

    /**
     * @brief Initializes the position of the filler to the last item above [lineIdx] in gridMatrix_.
     *
     * @param lineIdx The line index to start traversing backwards (inclusive).
     * @return index of the last item.
     */
    int32_t InitPosToLastItem(int32_t lineIdx);

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
     * @brief Checks if an item can fit in the grid based on its width and the available space in the current row or
     * column.
     *
     * @param it An iterator pointing to the current row or column in the grid layout information.
     * @param itemWidth The width of the item.
     * @return The cross-axis index where the item can fit. Returns -1 if it can't fit on the current row.
     */
    int32_t FitItem(const decltype(GridLayoutInfo::gridMatrix_)::iterator& it, int32_t itemWidth);

    /**
     * @brief Implementation of MeasureBackward algorithm on each row.
     *
     * @param measured unordered_set to record items that are already measured.
     * @param params Fill Parameters needed for measure.
     */
    void BackwardImpl(std::unordered_set<int32_t>& measured, const FillParameters& params);

    /**
     * @brief Finds the top row index of an item in the grid.
     *
     * @param row The row index of the item's bottom-left tile.
     * @param col The column index of the item's bottom-left tile.
     * @return The top row index of the GridItem.
     */
    int32_t FindItemTopRow(int32_t row, int32_t col) const;

    /**
     * @brief Update item info to the newly filled GridItem.
     *
     * @param idx index of item in Grid
     * @param row row index of item's top-left corner
     * @param col column index of item's top-left corner
     * @param size size of the item.
     */
    void SetItemInfo(const LayoutWrapper* item, int32_t idx, int32_t row, int32_t col, GridItemSize size);

    int32_t posY_ = 0;  /**< The current row index in the grid. */
    int32_t posX_ = -1; /**< The current column index in the grid. */

    GridLayoutInfo* info_;
    LayoutWrapper* wrapper_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_IRREGULAR_FILLER_H
