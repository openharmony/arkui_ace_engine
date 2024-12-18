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

#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"

namespace OHOS::Ace::NG {
namespace {
void UpdateGridItemRowAndColumnInfo(const RefPtr<LayoutWrapper>& itemLayoutWrapper, GridItemIndexInfo irregualItemInfo)
{
    auto gridItemHost = itemLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(gridItemHost);
    auto gridItemPattern = gridItemHost->GetPattern<GridItemPattern>();
    CHECK_NULL_VOID(gridItemPattern);
    gridItemPattern->SetIrregularItemInfo(irregualItemInfo);
}
} // namespace

void GridScrollWithOptionsLayoutAlgorithm::AdjustRowColSpan(
    const RefPtr<LayoutWrapper>& itemLayoutWrapper, LayoutWrapper* layoutWrapper, int32_t itemIndex)
{
    auto result = GetCrossStartAndSpan(layoutWrapper, itemIndex);
    if (info_.axis_ == Axis::VERTICAL) {
        currentItemColStart_ = result.first;
        currentItemColSpan_ = result.second;
        currentItemColEnd_ = currentItemColStart_ + currentItemColSpan_ - 1;
        currentItemRowStart_ = -1;
        currentItemRowEnd_ = -1;
        currentItemRowSpan_ = 1;
    } else {
        currentItemRowStart_ = result.first;
        currentItemRowSpan_ = result.second;
        currentItemRowEnd_ = currentItemRowStart_ + currentItemRowSpan_ - 1;
        currentItemColStart_ = -1;
        currentItemColEnd_ = -1;
        currentItemColSpan_ = 1;
    }

    if (currentItemRowSpan_ > 1 || currentItemColSpan_ > 1) {
        info_.hasBigItem_ = true;
        bool isVertical = info_.axis_ == Axis::VERTICAL;
        GridItemIndexInfo irregualItemInfo;
        irregualItemInfo.mainStart = isVertical ? currentItemRowStart_ : currentItemColStart_;
        irregualItemInfo.mainEnd = isVertical ? currentItemRowEnd_ : currentItemColEnd_;
        irregualItemInfo.mainSpan = isVertical ? currentItemRowSpan_ : currentItemColSpan_;
        irregualItemInfo.crossStart = isVertical ? currentItemColStart_ : currentItemRowStart_;
        irregualItemInfo.crossEnd = isVertical ? currentItemColEnd_ : currentItemRowEnd_;
        irregualItemInfo.crossSpan = isVertical ? currentItemColSpan_ : currentItemRowSpan_;
        UpdateGridItemRowAndColumnInfo(itemLayoutWrapper, irregualItemInfo);
    }
}

void GridScrollWithOptionsLayoutAlgorithm::LargeItemLineHeight(
    const RefPtr<LayoutWrapper>& itemWrapper, bool& /* hasNormalItem */)
{
    auto itemSize = itemWrapper->GetGeometryNode()->GetMarginFrameSize();
    auto itemMainSize = GetMainAxisSize(itemSize, info_.axis_);
    if (LessNotEqual(itemMainSize, 0.0f)) {
        TAG_LOGI(
            AceLogTag::ACE_GRID, "item height of index %{public}d is less than zero", info_.endIndex_ + 1);
        itemMainSize = 0.0f;
    }
    cellAveLength_ = std::max(itemMainSize, cellAveLength_);
}

void GridScrollWithOptionsLayoutAlgorithm::GetTargetIndexInfoWithBenchMark(
    LayoutWrapper* layoutWrapper, bool isTargetBackward, int32_t targetIndex)
{
    int32_t benchmarkIndex = (isTargetBackward && !info_.gridMatrix_.empty())
                                 ? info_.gridMatrix_.rbegin()->second.rbegin()->second + 1
                                 : 0;
    int32_t mainStartIndex = (isTargetBackward && !info_.gridMatrix_.empty())
                                 ? info_.gridMatrix_.rbegin()->first + 1
                                 : 0;
    int32_t currentIndex = benchmarkIndex;
    int32_t headOfMainStartLine = currentIndex;

    while (currentIndex < targetIndex) {
        int32_t crossGridReserve = info_.crossCount_;
        /* go through a new line */
        while ((crossGridReserve > 0) && (currentIndex <= targetIndex)) {
            auto crossPos = GetCrossStartAndSpan(layoutWrapper, currentIndex);
            auto gridSpan = crossPos.second;
            if (crossGridReserve >= gridSpan) {
                crossGridReserve -= gridSpan;
            } else if (info_.crossCount_ >= gridSpan) {
                ++mainStartIndex;
                headOfMainStartLine = currentIndex;
                crossGridReserve = info_.crossCount_ - gridSpan;
            }
            ++currentIndex;
        }
        if (currentIndex > targetIndex) {
            break;
        }
        ++mainStartIndex;
        headOfMainStartLine = currentIndex;
    }
    info_.startMainLineIndex_ = mainStartIndex;
    info_.startIndex_ = headOfMainStartLine;
    info_.endIndex_ = headOfMainStartLine - 1;
    info_.prevOffset_ = 0;
    info_.currentOffset_ = 0;
    info_.ResetPositionFlags();
    info_.gridMatrix_.clear();
    info_.lineHeightMap_.clear();
    info_.irregularItemsPosition_.clear();
}

std::pair<int32_t, int32_t> GridScrollWithOptionsLayoutAlgorithm::GetCrossStartAndSpan(
    LayoutWrapper* layoutWrapper, int32_t itemIndex)
{
    auto layoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, std::make_pair(-1, 1));
    const auto& options = *layoutProperty->GetLayoutOptions();
    if (options.irregularIndexes.empty()) {
        return std::make_pair(itemIndex % crossCount_, 1);
    }

    auto firstIrregularIndex = *(options.irregularIndexes.begin());
    if (itemIndex < firstIrregularIndex) {
        return std::make_pair(itemIndex % crossCount_, 1);
    }

    // without function
    if (!options.getSizeByIndex) {
        if (options.irregularIndexes.find(itemIndex) != options.irregularIndexes.end()) {
            return std::make_pair(0, crossCount_);
        }
        int32_t crossStart = -1;
        auto iter = options.irregularIndexes.upper_bound(itemIndex);
        auto crossCount = static_cast<int32_t>(crossCount_);
        if (iter == options.irregularIndexes.end()) {
            crossStart = (itemIndex - (*(options.irregularIndexes.rbegin()) + 1)) % crossCount;
        } else {
            if (iter != options.irregularIndexes.begin()) {
                crossStart = (itemIndex - (*(--iter) + 1)) % crossCount;
            } else {
                crossStart = itemIndex % crossCount;
            }
        }
        return std::make_pair(crossStart, 1);
    }

    return GetCrossStartAndSpanWithUserFunction(itemIndex, options, firstIrregularIndex);
}

static void JumpToLastIrregularItem(
    const std::map<int32_t, int32_t>& irregularItemsPosition, int32_t& sum, int32_t& lastIndex, int32_t targetIndex)
{
    if (irregularItemsPosition.empty()) {
        return;
    }

    auto iter = irregularItemsPosition.lower_bound(targetIndex);
    if (iter == irregularItemsPosition.begin()) {
        return;
    }
    if (iter != irregularItemsPosition.end()) {
        --iter;
        sum = iter->second;
        lastIndex = iter->first;
    } else {
        auto lastIter = irregularItemsPosition.rbegin();
        sum = lastIter->second;
        lastIndex = lastIter->first;
    }
}

static void ResetInvalidCrossSpan(uint32_t crossCount, int32_t& crossSpan)
{
    if (crossSpan > static_cast<int32_t>(crossCount) || crossSpan <= 0) {
        crossSpan = 1;
    }
}

static void InitIrregularItemsPosition(std::map<int32_t, int32_t>& irregularItemsPosition,
    const GridLayoutOptions& options, int32_t firstIrregularIndex, Axis axis, int32_t crossCount)
{
    if (irregularItemsPosition.empty()) {
        auto sum = firstIrregularIndex;
        auto crossSpan = options.getSizeByIndex(firstIrregularIndex).GetCrossSize(axis);
        ResetInvalidCrossSpan(crossCount, crossSpan);
        // first irregular item in new line
        if (crossCount != 0) {
            auto crossStart = sum % crossCount;
            if (crossStart + crossSpan > crossCount) {
                sum += (crossCount - crossStart);
            }
        }
        irregularItemsPosition.emplace(firstIrregularIndex, sum + crossSpan);
    }
}

std::pair<int32_t, int32_t> GridScrollWithOptionsLayoutAlgorithm::GetCrossStartAndSpanWithUserFunction(
    int32_t itemIndex, const GridLayoutOptions& options, int32_t firstIrregularIndex)
{
    auto crossCount = static_cast<int32_t>(crossCount_);
    InitIrregularItemsPosition(
        info_.irregularItemsPosition_, options, firstIrregularIndex, info_.axis_, crossCount);
    auto sum = firstIrregularIndex;
    auto lastIndex = firstIrregularIndex;
    JumpToLastIrregularItem(info_.irregularItemsPosition_, sum, lastIndex, itemIndex);
    auto iter = options.irregularIndexes.find(lastIndex);
    if (iter == options.irregularIndexes.end()) {
        iter = options.irregularIndexes.begin();
    }
    for (; iter != options.irregularIndexes.end(); ++iter) {
        auto index = *iter;
        if (index >= itemIndex) {
            break;
        }

        if (index == lastIndex) {
            continue;
        }

        auto crossSpan = options.getSizeByIndex(index).GetCrossSize(info_.axis_);
        ResetInvalidCrossSpan(crossCount_, crossSpan);
        auto irregularStart = (sum + index - lastIndex - 1) % crossCount;
        // put it into next line
        if (irregularStart + crossSpan > crossCount) {
            sum += (crossCount - irregularStart);
        }
        sum += (index - lastIndex - 1);
        sum += crossSpan;
        lastIndex = index;
        info_.irregularItemsPosition_.emplace(index, sum);
    }
    sum += ((itemIndex > lastIndex) ? (itemIndex - lastIndex - 1) : 0);
    auto crossStart = sum % crossCount;
    bool isRegularItem = (options.irregularIndexes.find(itemIndex) == options.irregularIndexes.end());
    auto crossSpan = isRegularItem ? 1 : options.getSizeByIndex(itemIndex).GetCrossSize(info_.axis_);
    ResetInvalidCrossSpan(crossCount_, crossSpan);
    if (crossStart + crossSpan > crossCount) {
        sum += (crossCount - crossStart);
        crossStart = 0;
    }
    if (!isRegularItem) {
        sum += crossSpan;
        info_.irregularItemsPosition_.emplace(itemIndex, sum);
    }
    return std::make_pair(crossStart, crossSpan);
}

void GridScrollWithOptionsLayoutAlgorithm::SkipLargeOffset(float mainSize, LayoutWrapper* layoutWrapper)
{
    SkipForwardLines(mainSize, layoutWrapper);
    SkipBackwardLines(mainSize, layoutWrapper);
}

void GridScrollWithOptionsLayoutAlgorithm::SkipIrregularLines(LayoutWrapper* layoutWrapper, bool forward)
{
    auto layoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& options = *layoutProperty->GetLayoutOptions();
    if (options.irregularIndexes.empty()) {
        return SkipRegularLines(forward);
    }
    if (options.getSizeByIndex) {
        return GridScrollLayoutAlgorithm::SkipIrregularLines(layoutWrapper, forward);
    }

    info_.SkipStartIndexByOffset(options, mainGap_);
}
} // namespace OHOS::Ace::NG
