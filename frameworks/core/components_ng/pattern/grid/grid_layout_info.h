/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::NG {
constexpr int32_t EMPTY_JUMP_INDEX = -2;
constexpr float HALF = 0.5f;

// Try not to add more variables in [GridLayoutInfo] because the more state variables, the more problematic and the
// harder it is to maintain
struct GridLayoutInfo {
    float GetTotalHeightOfItemsInView(float mainGap)
    {
        float lengthOfItemsInViewport = 0.0;
        for (auto i = startMainLineIndex_; i <= endMainLineIndex_; i++) {
            if (GreatOrEqual(lineHeightMap_[i], 0)) {
                lengthOfItemsInViewport += (lineHeightMap_[i] + mainGap);
            }
        }
        return lengthOfItemsInViewport - mainGap;
    }

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

    void UpdateEndLine(float mainSize, float mainGap);
    // for overScroll at top
    void UpdateEndIndex(float overScrollOffset, float mainSize, float mainGap);

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

    float GetTotalLineHeight(float mainGap) const
    {
        float totalHeight = 0.0f;
        for (auto iter = lineHeightMap_.begin(); iter != lineHeightMap_.end(); ++iter) {
            totalHeight += (iter->second + mainGap);
        }
        return totalHeight - mainGap;
    }

    /**
     * @brief Finds the index of the last item in the grid matrix, and update startIndex_ and startMainLineIndex_ to
     * that last item.
     *
     */
    void UpdateStartIdxToLastItem();

    /**
     * @brief Tries to find the item between startMainLine and endMainLine.
     *
     * @param target The target item to find.
     * @return The line index of the found item.
     */
    int32_t FindItemInRange(int32_t target) const;

    /**
     * @brief clears gridMatrix_ and lineHeightMap_ starting from line [idx]
     *
     * @param idx starting line index
     */
    void ClearMapsToEnd(int32_t idx);

    /**
     * @brief clears gridMatrix_ and lineHeightMap_ in range [0, idx)
     *
     * @param idx ending line index, exclusive.
     */
    void ClearMapsFromStart(int32_t idx);

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
    float GetContentHeight(float mainGap) const;
    float GetContentOffset(const GridLayoutOptions& options, float mainGap) const;
    float GetContentHeight(const GridLayoutOptions& options, float mainGap) const;
    float GetCurrentLineHeight() const;

    bool GetLineIndexByIndex(int32_t targetIndex, int32_t& targetLineIndex) const;
    float GetTotalHeightFromZeroIndex(int32_t targetLineIndex, float mainGap) const;

    bool GetGridItemAnimatePos(const GridLayoutInfo& currentGridLayoutInfo, int32_t targetIndex, ScrollAlign align,
        float mainGap, float& targetPos);
    Axis axis_ = Axis::VERTICAL;

    float currentOffset_ = 0.0f; // offset on the current top GridItem on [startMainLineIndex_]
    float prevOffset_ = 0.0f;
    float lastMainSize_ = 0.0f;
    float totalHeightOfItemsInView_ = 0.0f;

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
    int32_t crossCount_ = 0;
    int32_t childrenCount_ = 0;
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

    bool offsetEnd_ = false; // true if last GridItem is fully within the viewport

    // Grid has GridItem whose columnEnd - columnStart > 0
    bool hasBigItem_;

    bool offsetUpdated_ = false;
    std::optional<int32_t> targetIndex_;

private:
    float GetCurrentOffsetOfRegularGrid(float mainGap) const;
    int32_t GetItemIndexByPosition(int32_t position);
    int32_t GetPositionByItemIndex(int32_t itemIndex);
    void MoveItemsBack(int32_t from, int32_t to, int32_t itemIndex);
    void MoveItemsForward(int32_t from, int32_t to, int32_t itemIndex);
    int32_t currentMovingItemPosition_ = -1;
    std::map<int32_t, int32_t> positionItemIndexMap_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_ALGORITHM_H
