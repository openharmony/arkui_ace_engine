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
#include "core/components_ng/pattern/grid/grid_layout_info.h"

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
int32_t GridLayoutInfo::GetItemIndexByPosition(int32_t position)
{
    auto iter = positionItemIndexMap_.find(position);
    if (iter != positionItemIndexMap_.end()) {
        return iter->second;
    }
    return position;
}

int32_t GridLayoutInfo::GetPositionByItemIndex(int32_t itemIndex)
{
    auto position = itemIndex;
    auto find = std::find_if(positionItemIndexMap_.begin(), positionItemIndexMap_.end(),
        [itemIndex](const std::pair<int32_t, int32_t>& item) { return item.second == itemIndex; });
    if (find != positionItemIndexMap_.end()) {
        position = find->first;
    }

    return position;
}

int32_t GridLayoutInfo::GetOriginalIndex() const
{
    return currentMovingItemPosition_;
}

void GridLayoutInfo::ClearDragState()
{
    positionItemIndexMap_.clear();
    currentMovingItemPosition_ = -1;
    currentRect_.Reset();
}

void GridLayoutInfo::MoveItemsBack(int32_t from, int32_t to, int32_t itemIndex)
{
    auto lastItemIndex = itemIndex;
    for (int32_t i = from; i <= to; ++i) {
        int32_t mainIndex = (i - startIndex_) / crossCount_ + startMainLineIndex_;
        int32_t crossIndex = (i - startIndex_) % crossCount_;
        if (i == from) {
            gridMatrix_[mainIndex][crossIndex] = itemIndex;
        } else {
            auto index = GetItemIndexByPosition(i - 1);
            gridMatrix_[mainIndex][crossIndex] = index;
            positionItemIndexMap_[i - 1] = lastItemIndex;
            lastItemIndex = index;
        }
    }
    positionItemIndexMap_[from] = itemIndex;
    positionItemIndexMap_[to] = lastItemIndex;
    currentMovingItemPosition_ = from;
}

void GridLayoutInfo::MoveItemsForward(int32_t from, int32_t to, int32_t itemIndex)
{
    for (int32_t i = from; i <= to; ++i) {
        int32_t mainIndex = (i - startIndex_) / crossCount_ + startMainLineIndex_;
        int32_t crossIndex = (i - startIndex_) % crossCount_;
        if (i == to) {
            gridMatrix_[mainIndex][crossIndex] = itemIndex;
        } else {
            auto index = GetItemIndexByPosition(i + 1);
            gridMatrix_[mainIndex][crossIndex] = index;
            positionItemIndexMap_[i] = index;
        }
    }
    positionItemIndexMap_[to] = itemIndex;
    currentMovingItemPosition_ = to;
}

void GridLayoutInfo::SwapItems(int32_t itemIndex, int32_t insertIndex)
{
    currentMovingItemPosition_ = currentMovingItemPosition_ == -1 ? itemIndex : currentMovingItemPosition_;
    auto insertPositon = insertIndex;
    // drag from another grid
    if (itemIndex == -1) {
        if (currentMovingItemPosition_ == -1) {
            MoveItemsBack(insertPositon, childrenCount_, itemIndex);
            return;
        }
    } else {
        insertPositon = GetPositionByItemIndex(insertIndex);
    }

    if (currentMovingItemPosition_ > insertPositon) {
        MoveItemsBack(insertPositon, currentMovingItemPosition_, itemIndex);
        return;
    }

    if (insertPositon > currentMovingItemPosition_) {
        MoveItemsForward(currentMovingItemPosition_, insertPositon, itemIndex);
    }
}

void GridLayoutInfo::UpdateEndLine(float mainSize, float mainGap)
{
    if (mainSize >= lastMainSize_) {
        return;
    }
    for (auto i = startMainLineIndex_; i < endMainLineIndex_; ++i) {
        mainSize -= (lineHeightMap_[i] + mainGap);
        if (LessOrEqual(mainSize + mainGap, 0)) {
            endMainLineIndex_ = i;
            break;
        }
    }
}

void GridLayoutInfo::UpdateEndIndex(float overScrollOffset, float mainSize, float mainGap)
{
    auto remainSize = mainSize - overScrollOffset;
    for (auto i = startMainLineIndex_; i < endMainLineIndex_; ++i) {
        remainSize -= (lineHeightMap_[i] + mainGap);
        if (LessOrEqual(remainSize + mainGap, 0)) {
            auto endLine = gridMatrix_.find(i);
            CHECK_NULL_VOID(endLine != gridMatrix_.end());
            CHECK_NULL_VOID(!endLine->second.empty());
            endIndex_ = endLine->second.rbegin()->second;
            break;
        }
    }
}

float GridLayoutInfo::GetCurrentOffsetOfRegularGrid(float mainGap) const
{
    float defaultHeight = GetCurrentLineHeight();
    auto lines = startIndex_ / crossCount_;
    float res = 0.0f;
    for (int i = 0; i < lines; ++i) {
        auto it = lineHeightMap_.find(i);
        res += (it != lineHeightMap_.end() ? it->second : defaultHeight) + mainGap;
    }
    return res - currentOffset_;
}

float GridLayoutInfo::GetContentOffset(float mainGap) const
{
    if (!hasBigItem_) {
        return GetCurrentOffsetOfRegularGrid(mainGap);
    }

    float heightSum = 0;
    int32_t itemCount = 0;
    float height = 0;
    auto fromStart = false;
    for (const auto& item : lineHeightMap_) {
        auto line = gridMatrix_.find(item.first);
        if (line == gridMatrix_.end()) {
            continue;
        }
        if (line->second.empty()) {
            continue;
        }
        auto lineStart = line->second.begin()->second;
        auto lineEnd = line->second.rbegin()->second;
        itemCount += (lineEnd - lineStart + 1);
        heightSum += item.second + mainGap;
        fromStart = item.first == 0 ? true : fromStart;
    }
    if (itemCount == 0) {
        return 0;
    }
    auto averageHeight = heightSum / itemCount;
    height = startIndex_ * averageHeight - currentOffset_;
    if (itemCount >= (childrenCount_ - 1) || (fromStart && itemCount >= startIndex_)) {
        height = GetStartLineOffset(mainGap);
    }
    return height;
}

float GridLayoutInfo::GetContentHeight(float mainGap) const
{
    if (!hasBigItem_) {
        float lineHeight = GetCurrentLineHeight();
        float res = 0.0f;
        auto lines = (childrenCount_) / crossCount_;
        for (int i = 0; i < lines; ++i) {
            auto it = lineHeightMap_.find(i);
            res += (it != lineHeightMap_.end() ? it->second : lineHeight) + mainGap;
        }
        if (childrenCount_ % crossCount_ == 0) {
            return res - mainGap;
        }
        auto lastLine = lineHeightMap_.find(lines);
        return res + (lastLine != lineHeightMap_.end() ? lastLine->second : lineHeight);
    }
    float heightSum = 0;
    int32_t itemCount = 0;
    float estimatedHeight = 0;
    for (const auto& item : lineHeightMap_) {
        auto line = gridMatrix_.find(item.first);
        if (line == gridMatrix_.end()) {
            continue;
        }
        if (line->second.empty()) {
            continue;
        }
        auto lineStart = line->second.begin()->second;
        auto lineEnd = line->second.rbegin()->second;
        itemCount += (lineEnd - lineStart + 1);
        heightSum += item.second + mainGap;
    }
    if (itemCount == 0) {
        return 0;
    }
    auto averageHeight = heightSum / itemCount;
    if (itemCount >= (childrenCount_ - 1)) {
        estimatedHeight = heightSum - mainGap;
    } else {
        estimatedHeight = heightSum + (childrenCount_ - itemCount) * averageHeight;
    }
    return estimatedHeight;
}

float GridLayoutInfo::GetContentOffset(const GridLayoutOptions& options, float mainGap) const
{
    if (startIndex_ == 0) {
        return -currentOffset_;
    }
    if (options.irregularIndexes.empty() || startIndex_ < *(options.irregularIndexes.begin())) {
        return GetCurrentOffsetOfRegularGrid(mainGap);
    }
    if (options.getSizeByIndex) {
        return GetContentOffset(mainGap);
    }
    auto firstIrregularIndex = *(options.irregularIndexes.begin());
    auto lastIndex = firstIrregularIndex;
    float irregularHeight = 0.0f;
    float regularHeight = 0.0f;
    for (const auto& item : lineHeightMap_) {
        auto line = gridMatrix_.find(item.first);
        if (line == gridMatrix_.end() || line->second.empty()) {
            continue;
        }
        auto lineStart = line->second.begin()->second;
        if (options.irregularIndexes.find(lineStart) != options.irregularIndexes.end()) {
            irregularHeight = item.second;
        } else {
            regularHeight = item.second;
        }
        if (!(NearZero(irregularHeight) || NearZero(regularHeight))) {
            break;
        }
    }

    // get line count
    float totalOffset =
        (firstIrregularIndex >= 1) ? ((firstIrregularIndex - 1) / crossCount_ + 1) * (regularHeight + mainGap) : 0;
    for (int32_t idx : options.irregularIndexes) {
        if (startIndex_ < idx) {
            totalOffset += ((startIndex_ - lastIndex - 1) / crossCount_) * (regularHeight + mainGap);
            lastIndex = idx;
            break;
        }
        if (startIndex_ > idx) {
            totalOffset += irregularHeight + mainGap;
        }
        totalOffset +=
            (idx - 1 > lastIndex) ? ((idx - 1 - lastIndex - 1) / crossCount_ + 1) * (regularHeight + mainGap) : 0;
        lastIndex = idx;
        if (startIndex_ == idx) {
            break;
        }
    }
    totalOffset +=
        startIndex_ > lastIndex ? ((startIndex_ - lastIndex - 1) / crossCount_) * (regularHeight + mainGap) : 0;
    return totalOffset - currentOffset_;
}

float GridLayoutInfo::GetContentHeight(const GridLayoutOptions& options, float mainGap) const
{
    if (options.irregularIndexes.empty()) {
        return GetContentHeight(mainGap);
    }
    if (options.getSizeByIndex) {
        return GetContentHeight(mainGap);
    }
    float irregularHeight = 0.0f;
    float regularHeight = 0.0f;
    for (const auto& item : lineHeightMap_) {
        auto line = gridMatrix_.find(item.first);
        if (line == gridMatrix_.end()) {
            continue;
        }
        if (line->second.empty()) {
            continue;
        }
        auto lineStart = line->second.begin()->second;
        if (options.irregularIndexes.find(lineStart) != options.irregularIndexes.end()) {
            irregularHeight = item.second;
        } else {
            regularHeight = item.second;
        }
        if (!(NearZero(irregularHeight) || NearZero(regularHeight))) {
            break;
        }
    }
    // get line count
    auto firstIrregularIndex = *(options.irregularIndexes.begin());
    auto lastIndex = firstIrregularIndex;
    float totalHeight =
        (firstIrregularIndex >= 1) ? ((firstIrregularIndex - 1) / crossCount_ + 1) * (regularHeight + mainGap) : 0;
    for (int32_t idx : options.irregularIndexes) {
        if (idx >= childrenCount_) {
            break;
        }
        totalHeight += irregularHeight + mainGap;
        totalHeight +=
            (idx - lastIndex) > 1 ? ((idx - 1 - lastIndex) / crossCount_ + 1) * (regularHeight + mainGap) : 0;
        lastIndex = idx;
    }

    totalHeight += (childrenCount_ - 1 > lastIndex)
                       ? ((childrenCount_ - 1 - lastIndex) / crossCount_) * (regularHeight + mainGap)
                       : 0;
    totalHeight -= mainGap;
    return totalHeight;
}

float GridLayoutInfo::GetCurrentLineHeight() const
{
    auto currentLineHeight = lineHeightMap_.find(startMainLineIndex_);
    auto currentLineMatrix = gridMatrix_.find(startMainLineIndex_);
    // if current line exist, find it
    if (currentLineHeight != lineHeightMap_.end() && currentLineMatrix != gridMatrix_.end() &&
        !currentLineMatrix->second.empty()) {
        return currentLineHeight->second;
    }

    // otherwise return the first line in cache
    for (const auto& item : lineHeightMap_) {
        auto line = gridMatrix_.find(item.first);
        if (line == gridMatrix_.end()) {
            continue;
        }
        if (line->second.empty()) {
            continue;
        }
        return item.second;
    }
    return 0.0f;
}

void GridLayoutInfo::UpdateStartIdxToLastItem()
{
    // find last index in gridMatrix
    for (auto line = gridMatrix_.rbegin(); line != gridMatrix_.rend(); ++line) {
        const auto& row = line->second;
        for (auto c = row.rbegin(); c != row.rend(); ++c) {
            if (c->second != -1) {
                startIndex_ = c->second;
                startMainLineIndex_ = line->first;
                return;
            }
        }
    }
    startIndex_ = 0;
    startMainLineIndex_ = 0;
}

int32_t GridLayoutInfo::FindItemInRange(int32_t target) const
{
    if (gridMatrix_.empty()) {
        return -1;
    }
    for (int r = startMainLineIndex_; r <= endMainLineIndex_; ++r) {
        const auto& row = gridMatrix_.at(r);
        for (auto it : row) {
            if (it.second == target) {
                return r;
            }
        }
    }
    return -1;
}

// Use the index to get the line number where the item is located
bool GridLayoutInfo::GetLineIndexByIndex(int32_t targetIndex, int32_t& targetLineIndex) const
{
    for (auto [lineIndex, lineMap] : gridMatrix_) {
        for (auto [crossIndex, index] : lineMap) {
            if (index == targetIndex) {
                targetLineIndex = lineIndex;
                return true;
            }
        }
    }
    return false;
}

// get the total height of all rows from zero before the targetLineIndex
float GridLayoutInfo::GetTotalHeightFromZeroIndex(int32_t targetLineIndex, float mainGap) const
{
    auto targetPos = 0.f;
    for (auto [lineIndex, lineHeight] : lineHeightMap_) {
        if (targetLineIndex > lineIndex) {
            targetPos += lineHeight + mainGap;
        } else {
            break;
        }
    }
    return targetPos;
}

// Based on the index from zero and align, gets the position to scroll to
bool GridLayoutInfo::GetGridItemAnimatePos(const GridLayoutInfo& currentGridLayoutInfo, int32_t targetIndex,
    ScrollAlign align, float mainGap, float& targetPos)
{
    int32_t startMainLineIndex = currentGridLayoutInfo.startMainLineIndex_;
    int32_t endMainLineIndex = currentGridLayoutInfo.endMainLineIndex_;
    float lastMainSize = currentGridLayoutInfo.lastMainSize_;
    int32_t targetLineIndex = -1;
    // Pre-check
    // Get the line number where the index is located. If targetIndex does not exist, it is returned.
    CHECK_NULL_RETURN(GetLineIndexByIndex(targetIndex, targetLineIndex), false);

    // Get the total height of the targetPos from row 0 to targetLineIndex-1.
    targetPos = GetTotalHeightFromZeroIndex(targetLineIndex, mainGap);

    // Find the target row and get the altitude information
    auto targetItem = lineHeightMap_.find(targetLineIndex);

    // Make sure that the target line has height information
    CHECK_NULL_RETURN(targetItem != lineHeightMap_.end(), false);
    auto targetLineHeight = targetItem->second;

    // Depending on align, calculate where you need to scroll to
    switch (align) {
        case ScrollAlign::START:
        case ScrollAlign::NONE:
            break;
        case ScrollAlign::CENTER: {
            targetPos -= ((lastMainSize - targetLineHeight) * HALF);
            break;
        }
        case ScrollAlign::END: {
            targetPos -= (lastMainSize - targetLineHeight);
            break;
        }
        case ScrollAlign::AUTO: {
            // When the row height is greater than the screen height and occupies the entire screen height, do nothing
            if (startMainLineIndex == targetLineIndex && endMainLineIndex == targetLineIndex) {
                return false;
            }

            if (startMainLineIndex >= targetLineIndex) {
            } else if (targetLineIndex >= endMainLineIndex) {
                targetPos -= (lastMainSize - targetLineHeight);
            } else {
                return false;
            }
            break;
        }
    }
    return true;
}
} // namespace OHOS::Ace::NG