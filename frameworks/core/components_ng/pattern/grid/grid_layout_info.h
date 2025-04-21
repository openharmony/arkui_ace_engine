/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_INFO_H

#include <map>
#include <optional>

#include "base/geometry/axis.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace::NG {

struct GridPredictLayoutParam {
    LayoutConstraintF layoutConstraint;
    std::map<int32_t, float> itemsCrossSizes;
    float crossGap = 0.0f;
};

struct GridPreloadItem {
    explicit GridPreloadItem(int32_t idx) : idx(idx) {}
    GridPreloadItem(int32_t idx, bool buildOnly) : idx(idx), buildOnly(buildOnly) {}

    bool operator==(const GridPreloadItem& other) const
    {
        return idx == other.idx && buildOnly == other.buildOnly;
    }

    int32_t idx = -1;
    bool buildOnly = false; // true if item only needs to be created, not measure / layout
};

/**
 * @brief callback to build a grid item at [itemIdx] in an IdleTask
 * @returns true if the built item needs Grid to perform a layout.
 */
using BuildGridItemCallback = std::function<bool(const RefPtr<FrameNode>& host, int32_t itemIdx)>;

constexpr int32_t EMPTY_JUMP_INDEX = -2;
constexpr int32_t JUMP_TO_BOTTOM_EDGE = -3;
constexpr float HALF = 0.5f;

// Try not to add more variables in [GridLayoutInfo] because the more state variables, the more problematic and the
// harder it is to maintain
struct GridLayoutInfo {
    /**
     * @param prune
     * @if true, try eliminate lines that are above viewport.
     * @else trust startMainLineIndex_ to determine the viewport.
     *
     * @return height in view range.
     */
    float GetTotalHeightOfItemsInView(float mainGap, bool prune = false) const;

    using HeightMapIt = std::map<int32_t, float>::const_iterator;
    /**
     * @brief skip starting lines that are outside viewport in LayoutIrregular
     *
     * @return [iterator to the first line in view, offset of that first line]
     */
    std::pair<HeightMapIt, float> SkipLinesAboveView(float mainGap) const;

    void UpdateStartIndexByStartLine()
    {
        auto startLine = gridMatrix_.find(startMainLineIndex_);
        if (startLine == gridMatrix_.end()) {
            return;
        }
        if (startLine->second.empty()) {
            return;
        }
        startIndex_ = startLine->second.begin()->second;
    }

    void UpdateStartIndexForExtralOffset(float mainGap, float mainSize);

    void UpdateEndLine(float mainSize, float mainGap);
    // for overScroll at top
    void UpdateEndIndex(float overScrollOffset, float mainSize, float mainGap);
    bool IsOutOfStart() const;
    /**
     * @brief Determine out of boundary condition for overScroll
     *
     * @param irregular whether running irregular layout.
     * @return true if the end of content is above viewport.
     */
    bool IsOutOfEnd(float mainGap, bool irregular) const;

    void SwapItems(int32_t itemIndex, int32_t insertIndex);
    int32_t GetOriginalIndex() const;
    void ClearDragState();

    float GetAverageLineHeight()
    {
        float totalHeight = 0;
        int32_t totalRow = 0;
        for (const auto& record : lineHeightMap_) {
            if (record.second > 0) {
                totalRow++;
                totalHeight += record.second;
            }
        }
        return totalRow > 0 ? totalHeight / totalRow : 0;
    }

    // should only be used when all children of Grid are in gridMatrix_
    float GetStartLineOffset(float mainGap) const
    {
        float totalHeight = 0;
        for (auto iter = lineHeightMap_.begin(); iter != lineHeightMap_.end() && iter->first < startMainLineIndex_;
             ++iter) {
            totalHeight += (iter->second + mainGap);
        }
        return totalHeight - currentOffset_;
    }

    float GetTotalLineHeight(float mainGap, bool removeLastGap = true) const
    {
        float totalHeight = 0.0f;
        for (auto iter : lineHeightMap_) {
            totalHeight += (iter.second + mainGap);
        }
        return (removeLastGap) ? totalHeight - mainGap : totalHeight;
    }

    /**
     * @brief set up jumpIndex_ and align_ to jump to the bottom edge of content.
     */
    void PrepareJumpToBottom();

    /**
     * @brief optimized function (early exit) to compare total height to [other].
     * @param other height to compare to.
     * @return true if total height is less than [other].
     */
    bool HeightSumSmaller(float other, float mainGap) const;

    /**
     * @return height sum of lines in range [startLine, endLine).
     */
    float GetHeightInRange(int32_t startLine, int32_t endLine, float mainGap) const;

    struct EndIndexInfo {
        int32_t itemIdx = -1; /**< Index of the last item. */
        int32_t y = -1;       /**< Main-axis position (line index) of the item. */
        int32_t x = -1;       /**< Cross-axis position (column index) of the item. */
    };
    /**
     * @brief Traverse the matrix backward to find the last item index, starting from Line [endLine].
     *
     * Intended to work on irregular layout.
     * @param endLine index of the line to start traversing.
     * @return last item index above endLine (inclusive) and the position it resides in.
     */
    EndIndexInfo FindEndIdx(int32_t endLine) const;

    /**
     * REQUIRES: Item is between startIndex_ and endIndex_. Otherwise, the result is undefined.
     *
     * @param line starting line of the item.
     * @param mainGap The gap between lines.
     * @return position of the item's top edge relative to the viewport.
     */
    inline float GetItemTopPos(int32_t line, float mainGap) const
    {
        return currentOffset_ + GetHeightInRange(startMainLineIndex_, line, mainGap);
    }

    /**
     * REQUIRES: Item is between startIndex_ and endIndex_. Otherwise, the result is undefined.
     *
     * @param line starting line of the item.
     * @param itemHeight The number of rows the item occupies.
     * @param mainGap The gap between items in the main axis.
     * @return position of the item's bottom edge relative to the viewport.
     */
    inline float GetItemBottomPos(int32_t line, int32_t itemHeight, float mainGap) const
    {
        return currentOffset_ + GetHeightInRange(startMainLineIndex_, line + itemHeight, mainGap) - mainGap;
    }

    /**
     * @brief Perform a binary search to find item with [index] in the gridMatrix_.
     *
     * @param index target item index
     * @return iterator to that item, or map::end if not found.
     */
    std::map<int32_t, std::map<int32_t, int32_t>>::const_iterator FindInMatrix(int32_t index) const;

    /**
     * @param itemIdx
     * @return position [col, row] of the item. [-1, -1] if item is not in matrix.
     */
    std::pair<int32_t, int32_t> GetItemPos(int32_t itemIdx) const;

    /**
     * @brief Tries to find the item between startMainLine and endMainLine.
     *
     * @param target The target item to find.
     * @return The line index and column index of the found item.
     */
    std::pair<int32_t, int32_t> FindItemInRange(int32_t target) const;

    /**
     * @brief Find the offset and line index of an item's center point.
     *
     * @param startLine starting line index of this item.
     * @param lineCnt number of rows the item occupies.
     * @return [lineIdx, offset relative to this line] of the center point.
     */
    std::pair<int32_t, float> FindItemCenter(int32_t startLine, int32_t lineCnt, float mainGap) const;

    /**
     * @brief clears lineHeightMap_ and gridMatrix_ starting from line [idx]
     *
     * @param idx starting line index
     */
    void ClearMapsToEnd(int32_t idx);

    /**
     * @brief clears lineHeightMap_ and gridMatrix_ in range [0, idx)
     *
     * @param idx ending line index, exclusive.
     */
    void ClearMapsFromStart(int32_t idx);

    /**
     * @brief clears lineHeightMap_ starting from line [idx]
     *
     * @param idx starting line index
     */
    void ClearHeightsToEnd(int32_t idx);

    /**
     * @brief clear gridMatrix_ in range [idx, end)
     *
     * REQUIRES: idx and lineIdx have to match each other.
     * @param idx item index to start clearing from.
     * @param lineIdx already-found line index of the target item.
     */
    void ClearMatrixToEnd(int32_t idx, int32_t lineIdx);

    void ResetPositionFlags()
    {
        reachEnd_ = false;
        reachStart_ = false;
        offsetEnd_ = false;
    }

    bool IsResetted() const
    {
        return startIndex_ != 0 && gridMatrix_.empty();
    }

    void SetScrollAlign(ScrollAlign align)
    {
        scrollAlign_ = align;
    }

    float GetContentOffset(float mainGap) const;
    /**
     * @brief Get the total height of grid content. Use estimation when lineHeights are not available. Can handle
     * bigItems.
     *
     * @param mainGap
     * @return total height
     */
    float GetContentHeight(float mainGap) const;
    float GetContentOffset(const GridLayoutOptions& options, float mainGap) const;

    /**
     * @brief Get the content height of Grid in range [0, endIdx).
     *
     * IF: Irregular items always take up the whole line (no getSizeByIdx callback).
     * THEN: Assumes that all irregular lines have the same height, and all other regular lines have the same height.
     * ELSE: Call a more versatile algorithm.
     * REQUIRES:
     * 1. all irregular lines must have the same height.
     * 2. all regular items must have the same height.
     *
     * @param options contains irregular item.
     * @param endIdx ending item index (exclusive).
     * @param mainGap gap between lines.
     * @return total height of the content.
     */
    float GetContentHeight(const GridLayoutOptions& options, int32_t endIdx, float mainGap) const;
    void SkipStartIndexByOffset(const GridLayoutOptions& options, float mainGap);
    float GetCurrentLineHeight() const;

    /**
     * @brief Get Content Offset when using irregular layout.
     */
    float GetIrregularOffset(float mainGap) const;
    /**
     * @brief Get total content height when using irregular layout.
     */
    float GetIrregularHeight(float mainGap) const;

    bool GetLineIndexByIndex(int32_t targetIndex, int32_t& targetLineIndex) const;
    float GetTotalHeightFromZeroIndex(int32_t targetLineIndex, float mainGap) const;

    /**
     * @brief Calculate the distance from content's end to the viewport bottom.
     *
     * REQUIRES: currentOffset_ is valid from last layout.
     * @param mainSize of the viewport.
     * @param heightInView total height of items inside the viewport.
     * @param mainGap gap between lines along the main axis.
     * @return Positive when content's end is below viewport. Return [mainSize] if last line is not in viewport.
     */
    float GetDistanceToBottom(float mainSize, float heightInView, float mainGap) const;

    /**
     * @brief Transforms scrollAlign_ into other ScrollAlign values, based on current position of
     * target item.
     *
     * @param height number of rows the item occupies.
     * @param mainSize The main-axis length of the grid.
     * @return ScrollAlign value transformed from AUTO.
     */
    ScrollAlign TransformAutoScrollAlign(int32_t itemIdx, int32_t height, float mainSize, float mainGap) const;

    /**
     * @param targetIdx target item's index.
     * @param height number of rows the item occupies.
     * @return item position to scroll to through animation.
     */
    float GetAnimatePosIrregular(int32_t targetIdx, int32_t height, ScrollAlign align, float mainGap) const;

    bool GetGridItemAnimatePos(const GridLayoutInfo& currentGridLayoutInfo, int32_t targetIndex, ScrollAlign align,
        float mainGap, float& targetPos);

    using MatIter = std::map<int32_t, std::map<int32_t, int32_t>>::const_iterator;
    MatIter FindStartLineInMatrix(MatIter iter, int32_t index) const;
    void ClearHeightsFromMatrix(int32_t lineIdx);

    void UpdateDefaultCachedCount();

    int32_t FindInMatrixByMainIndexAndCrossIndex(int32_t mainIndex, int32_t crossIndex) const;

    // Only used for debugging.
    void PrintMatrix();
    void PrintLineHeight();

    bool CheckGridMatrix(int32_t cachedCount);

    int32_t GetChildrenCount() const
    {
        return firstRepeatCount_ > 0 ? firstRepeatCount_ : childrenCount_;
    }

    Axis axis_ = Axis::VERTICAL;

    float currentOffset_ = 0.0f; // offset on the current top GridItem on [startMainLineIndex_]
    float prevOffset_ = 0.0f;
    float currentHeight_ = 0.0f; // height from first item to current top GridItem on [startMainLineIndex_]
    float prevHeight_ = 0.0f;
    float lastMainSize_ = 0.0f;
    float lastCrossSize_ = 0.0f;
    float totalHeightOfItemsInView_ = 0.0f;
    float avgLineHeight_ = 0.0f;

    // additional padding to accommodate navigation bar when SafeArea is expanded
    float contentEndPadding_ = 0.0f;

    std::optional<int32_t> lastCrossCount_;
    // index of first and last GridItem in viewport
    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;

    // index of first row and last row in viewport (assuming it's a vertical Grid)
    int32_t startMainLineIndex_ = 0;
    int32_t endMainLineIndex_ = 0;

    int32_t jumpIndex_ = EMPTY_JUMP_INDEX;
    std::optional<float> extraOffset_;
    int32_t crossCount_ = 0;
    int32_t childrenCount_ = 0;
    int32_t firstRepeatCount_ = 0;
    int32_t repeatDifference_ = 0;
    ScrollAlign scrollAlign_ = ScrollAlign::AUTO;

    // Map structure: [mainIndex, [crossIndex, index]],
    // when vertical, mainIndex is rowIndex and crossIndex is columnIndex.
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix_;
    // in vertical grid, this map is like: [rowIndex: rowHeight]
    std::map<int32_t, float> lineHeightMap_;

    // Map structure: [index, last cell]
    std::map<int32_t, int32_t> irregularItemsPosition_;

    // rect of grid item dragged in
    RectF currentRect_;

    bool reachEnd_ = false; // true if last GridItem appears in the viewPort
    bool reachStart_ = false;

    bool offsetEnd_ = false; // true if content bottom is truly reached

    // Grid has GridItem whose columnEnd - columnStart > 0
    bool hasBigItem_;

    // Grid has GridItem whose rowEnd - rowStart > 0
    bool hasMultiLineItem_;
    // false when offset is updated but layout hasn't happened, so data is out of sync
    bool synced_ = false;

    std::optional<int32_t> targetIndex_;

    std::map<int32_t, bool> irregularLines_;

    bool clearStretch_ = false;

    // default cached count
    int32_t defCachedCount_ = 1;

    int32_t times_ = 0;

    float endHeight_ = 0.0f;

private:
    float GetCurrentOffsetOfRegularGrid(float mainGap) const;
    float GetContentHeightOfRegularGrid(float mainGap) const;
    int32_t GetItemIndexByPosition(int32_t position);
    int32_t GetPositionByItemIndex(int32_t itemIndex);
    void MoveItemsBack(int32_t from, int32_t to, int32_t itemIndex);
    void MoveItemsForward(int32_t from, int32_t to, int32_t itemIndex);
    void GetLineHeights(
        const GridLayoutOptions& options, float mainGap, float& regularHeight, float& irregularHeight) const;

    /**
     * @brief Find the number of GridItems in range [startLine, endLine].
     *
     * REQUIRES: gridMatrix_ is valid in range [startLine, endLine].
     * @return number of GridItems
     */
    int32_t FindItemCount(int32_t startLine, int32_t endLine) const;

    int32_t currentMovingItemPosition_ = -1;
    std::map<int32_t, int32_t> positionItemIndexMap_;
    float lastIrregularMainSize_ = 0.0f; // maybe no irregular item in current gridMatrix_
    float lastRegularMainSize_ = 0.0f;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_ALGORITHM_H
