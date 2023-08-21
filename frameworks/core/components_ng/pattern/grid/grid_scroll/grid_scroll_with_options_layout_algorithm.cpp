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

#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"

namespace OHOS::Ace::NG {
void GridScrollWithOptionsLayoutAlgorithm::AdjustRowColSpan(
    const RefPtr<LayoutWrapper>& /* itemLayoutWrapper */, LayoutWrapper* layoutWrapper, int32_t itemIndex)
{
    auto result = GetCrossStartAndSpan(layoutWrapper, itemIndex);
    if (gridLayoutInfo_.axis_ == Axis::VERTICAL) {
        currentItemColStart_ = result.first;
        currentItemColSpan_ = result.second;
        currentItemColEnd_ = currentItemColStart_ + currentItemColSpan_ - 1;
        currentItemRowStart_ = -1;
        currentItemRowEnd_ = -1;
        currentItemRowSpan_ = 1;
    } else {
        currentItemRowStart_ = result.first;
        currentItemRowSpan_ = result.second;
        currentItemRowEnd_ = currentItemColStart_ + currentItemColSpan_ - 1;
        currentItemColStart_ = -1;
        currentItemColEnd_ = -1;
        currentItemColSpan_ = 1;
    }
}

void GridScrollWithOptionsLayoutAlgorithm::LargeItemLineHeight(
    const RefPtr<LayoutWrapper>& itemWrapper, bool& /* hasNormalItem */)
{
    auto itemSize = itemWrapper->GetGeometryNode()->GetMarginFrameSize();
    cellAveLength_ = std::max(GetMainAxisSize(itemSize, gridLayoutInfo_.axis_), cellAveLength_);
}

void GridScrollWithOptionsLayoutAlgorithm::GetTargetIndexInfoWithBenchMark(
    LayoutWrapper* layoutWrapper, bool isTargetBackward, int32_t targetIndex)
{
    int32_t benchmarkIndex = isTargetBackward ? gridLayoutInfo_.gridMatrix_.rbegin()->second.rbegin()->second + 1 : 0;
    int32_t mainStartIndex = isTargetBackward ? gridLayoutInfo_.gridMatrix_.rbegin()->first + 1 : 0;
    int32_t currentIndex = benchmarkIndex;
    int32_t headOfMainStartLine = currentIndex;

    while (currentIndex < targetIndex) {
        int32_t crossGridReserve = gridLayoutInfo_.crossCount_;
        /* go through a new line */
        while ((crossGridReserve > 0) && (currentIndex <= targetIndex)) {
            auto crossPos = GetCrossStartAndSpan(layoutWrapper, targetIndex);
            auto gridSpan = crossPos.second;
            if (crossGridReserve >= gridSpan) {
                crossGridReserve -= gridSpan;
            } else if (gridLayoutInfo_.crossCount_ >= gridSpan) {
                ++mainStartIndex;
                headOfMainStartLine = currentIndex;
                crossGridReserve = gridLayoutInfo_.crossCount_ - gridSpan;
            }
            ++currentIndex;
        }
        if (currentIndex > targetIndex) {
            break;
        }
        ++mainStartIndex;
        headOfMainStartLine = currentIndex;
    }
    gridLayoutInfo_.startMainLineIndex_ = mainStartIndex;
    gridLayoutInfo_.startIndex_ = headOfMainStartLine;
    gridLayoutInfo_.endIndex_ = headOfMainStartLine - 1;
    gridLayoutInfo_.prevOffset_ = 0;
    gridLayoutInfo_.currentOffset_ = 0;
    gridLayoutInfo_.ResetPositionFlags();
    gridLayoutInfo_.gridMatrix_.clear();
    gridLayoutInfo_.lineHeightMap_.clear();
    gridLayoutInfo_.irregularItemsPosition_.clear();
}

std::pair<int32_t, int32_t> GridScrollWithOptionsLayoutAlgorithm::GetCrossStartAndSpan(
    LayoutWrapper* layoutWrapper, int32_t itemIndex)
{
    auto layoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, std::make_pair(-1, 1));
    auto options = layoutProperty->GetLayoutOptions().value();
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
        auto iter = std::find_if(options.irregularIndexes.begin(), options.irregularIndexes.end(),
            [itemIndex](int32_t index) { return index > itemIndex; });
        if (iter == options.irregularIndexes.end()) {
            crossStart = (itemIndex - (*(options.irregularIndexes.rbegin()) + 1)) % crossCount_;
        } else {
            if (iter != options.irregularIndexes.begin()) {
                crossStart = (itemIndex - (*(--iter) + 1)) % crossCount_;
            } else {
                crossStart = itemIndex % crossCount_;
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

    auto iter = std::find_if(irregularItemsPosition.begin(), irregularItemsPosition.end(),
        [targetIndex](const std::pair<int32_t, int32_t>& item) { return item.first >= targetIndex; });
    if (iter == irregularItemsPosition.begin()) {
        return;
    }
    if (iter != irregularItemsPosition.end()) {
        --iter;
        sum = iter->second - 1;
        lastIndex = iter->first;
    } else {
        auto lastIter = irregularItemsPosition.rbegin();
        sum = lastIter->second - 1;
        lastIndex = lastIter->first;
    }
}

std::pair<int32_t, int32_t> GridScrollWithOptionsLayoutAlgorithm::GetCrossStartAndSpanWithUserFunction(
    int32_t itemIndex, const GridLayoutOptions& options, int32_t firstIrregularIndex)
{
    auto sum = firstIrregularIndex;
    auto lastIndex = firstIrregularIndex;
    JumpToLastIrregularItem(gridLayoutInfo_.irregularItemsPosition_, sum, lastIndex, itemIndex);
    auto iter = options.irregularIndexes.find(lastIndex);
    if (iter == options.irregularIndexes.end()) {
        iter = options.irregularIndexes.begin();
    }
    for (; iter != options.irregularIndexes.end(); ++iter) {
        auto index = *iter;
        if (index >= itemIndex) {
            break;
        }

        if (index >= lastIndex) {
            continue;
        }

        auto crossSpan = options.getSizeByIndex(index).GetCorssSize(gridLayoutInfo_.axis_);
        if (crossSpan > crossCount_ || crossSpan <= 0) {
            LOGI("crossSpan invalid, use 1");
            crossSpan = 1;
        }
        auto irregularStart = (sum + index - lastIndex) % crossCount_;
        // put it into next line
        if (irregularStart + crossSpan > crossCount_) {
            sum += (crossCount_ - irregularStart);
        }
        sum += (index - lastIndex - 1);
        sum += crossSpan;
        lastIndex = index;
    }
    sum += (itemIndex - lastIndex);
    auto crossStart = sum % crossCount_;
    bool isRegularItem = (options.irregularIndexes.find(itemIndex) == options.irregularIndexes.end());
    auto crossSpan = isRegularItem ? 1 : options.getSizeByIndex(itemIndex).GetCorssSize(gridLayoutInfo_.axis_);
    if (crossSpan > crossCount_ || crossSpan <= 0) {
        LOGI("crossSpan invalid, use 1");
        crossSpan = 1;
    }
    if (crossStart + crossSpan > crossCount_) {
        sum += (crossCount_ - crossStart);
        crossStart = 0;
    }
    if (!isRegularItem) {
        sum += crossSpan;
        gridLayoutInfo_.irregularItemsPosition_.emplace(itemIndex, sum);
    }
    return std::make_pair(crossStart, crossSpan);
}

void GridScrollWithOptionsLayoutAlgorithm::SkipLargeOffset(float mainSize, LayoutWrapper* layoutWrapper)
{
    SkipForwardLines(mainSize, layoutWrapper);
    SkipBackwardLines(mainSize, layoutWrapper);
}
} // namespace OHOS::Ace::NG
