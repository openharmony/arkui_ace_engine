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

#include "core/components_ng/pattern/grid/grid_layout_controller.h"

#include "base/geometry/ng/size_t.h"
#include "core/components/declaration/common/event.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void GridLayoutController::FillGridViewportAndMeasureChildren(
    float mainSize, float crossSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper)
{
    float mainLength = currentOffset_;

    // Step1: Measure [GridItem] that has been recorded to [gridMatrix_]
    MeasureRecordedItems(mainSize, crossSize, gridLayoutProperty, layoutWrapper, mainLength);

    // Step2: When done measure items in record, request new items to fill blank at end
    FillBlankAtEnd(mainSize, crossSize, gridLayoutProperty, layoutWrapper, mainLength);
    if (reachEnd_) { // If it reaches end when [FillBlankAtEnd], modify [currentOffset_]
        ModifyCurrentOffsetWhenReachEnd(mainSize);
        return;
    }

    // Step3: Check if need to fill blank at start (in situation of grid items moving down)
    FillBlankAtStart(mainSize, crossSize, gridLayoutProperty, layoutWrapper, mainLength);
    if (reachStart_) {
        currentOffset_ = 0.0;
        prevOffset_ = 0.0;
    }
}

void GridLayoutController::FillBlankAtStart(float mainSize, float crossSize,
    const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper, float& mainLength)
{
    if (LessOrEqual(currentOffset_, 0.0)) { // If [currentOffset_] is none-positive, it means no blank at start
        return;
    }
    auto blankAtStart = currentOffset_;
    while (GreatNotEqual(blankAtStart, 0.0)) {
        float lineHeight = FillNewLineForward(crossSize, mainSize, gridLayoutProperty, layoutWrapper);
        if (GreatNotEqual(lineHeight, 0.0)) {
            lineHeightMap_[startMainLineIndex_] = lineHeight;
            blankAtStart -= lineHeight;
            continue;
        }
        reachStart_ = true;
        break;
    }
    currentOffset_ = blankAtStart;
    prevOffset_ = currentOffset_;
}

// When a moving up event comes, the [currrentOffset_] may have been reduced too much than the items really need to
// be moved up, so we need to modify [currrentOffset_] accrording to previous position.
void GridLayoutController::ModifyCurrentOffsetWhenReachEnd(float mainSize)
{
    // Step1. Calculate total length of all items in viewport. [lengthOfItemsInViewport] must be greater than or equal
    // to viewport height
    float lengthOfItemsInViewport = 0.0f;
    for (auto i = startMainLineIndex_; i <= endMainLineIndex_; i++) {
        lengthOfItemsInViewport += lineHeightMap_[i];
    }

    // Step2. Calculate real offset that items can only be moved up by.
    float realOffsetToMoveUp =
        lengthOfItemsInViewport - mainSize + prevOffset_; // Hint: [prevOffset_] is a non-positive value

    // Step3. modify [currentOffset_]
    currentOffset_ = prevOffset_ - realOffsetToMoveUp;
    prevOffset_ = currentOffset_;
}

void GridLayoutController::FillBlankAtEnd(float mainSize, float crossSize,
    const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper, float& mainLength)
{
    // When [mainLength] is still less than [mainSize], do [FillNewLineBackward] repeatedly until filling up the lower
    // part of the viewport
    while (LessNotEqual(mainLength, mainSize)) {
        float lineHeight = FillNewLineBackward(crossSize, mainSize, gridLayoutProperty, layoutWrapper);
        if (GreatNotEqual(lineHeight, 0.0)) {
            mainLength += lineHeight;
            continue;
        }
        reachEnd_ = true;
        break;
    };
}

void GridLayoutController::MeasureRecordedItems(float mainSize, float crossSize,
    const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper, float& mainLength)
{
    currentMainLineIndex_ = startMainLineIndex_ - 1;
    bool runOutOfRecord = false;
    while (LessNotEqual(mainLength, mainSize)) { // Measure grid items row by row
        auto gridMatrixIter = gridMatrix_.find(++currentMainLineIndex_);
        if (gridMatrixIter == gridMatrix_.end()) {
            runOutOfRecord = true;
            break; // If [gridMatrix_] does not contain record of line [currentMainLineIndex_], do [FillNewLineBackward]
        }
        float lineHeight = -1.0f;
        // One record is like [0: 1fr] or [1: 2fr]
        for (const auto& gridItemRecord : gridMatrixIter->second) {
            currentIndex_ = gridItemRecord.first;
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex_);
            if (!itemWrapper) {
                LOGE("GridItem wrapper of index %{public}u null", currentIndex_);
                break;
            }
            itemWrapper->Measure(
                MakeMeasureConstraintForGridItem(mainSize, crossSize, gridItemRecord.second, gridLayoutProperty));
            auto itemSize = itemWrapper->GetGeometryNode()->GetFrameSize();
            lineHeight = std::max(GetMainAxisSize(itemSize, GetAxis()), lineHeight);
            // Record end index. When fill new line, the [endIndex_] will be the first item index to request
            endIndex_ = gridItemRecord.first;
        }
        if (lineHeight > 0) { // Means at least one item has been measured
            lineHeightMap_[currentMainLineIndex_] = lineHeight;
            mainLength += lineHeight;
        }
        // If a line moves up out of viewport, update [startIndex_], [currentOffset_] and [startMainLineIndex_], and
        // delete record in [gridMatrix_] and [lineHeightMap_]. The strip operation of [gridMatrix_] and
        // [lineHeightMap_] will take place in [StripItemsOutOfViewport].
        // TODO: inactive items
        if (LessOrEqual(mainLength, 0.0)) {
            currentOffset_ = mainLength;
            startMainLineIndex_ = currentMainLineIndex_ + 1;
            startIndex_ = currentIndex_ + 1;
        }
    }
    // Case 1. if this while-loop breaks due to running out of records, the [currentMainLineIndex_] is larger by 1 than
    // real main line index, so reduce 1.
    // Case 2. if this while-loop stops due to false result of [LessNotEqual(mainLength, mainSize)], the
    // [currentMainLineIndex_] is exactly the real main line index. Update [endMainLineIndex_] when the recorded items
    // are done measured.
    endMainLineIndex_ = runOutOfRecord ? --currentMainLineIndex_ : currentMainLineIndex_;
}

float GridLayoutController::FillNewLineForward(
    float crossSize, float mainSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper)
{
    // To make the code more convinient to read, we name a param in situation of vertical, for exacmple:
    // 1. [lineHight] means height of a row when the Grid is vertical;
    // 2. [lineHight] means width of a column when the Grid is horizontal;
    // Other params are also named according to this principle.
    float lineHeight = -1.0f;
    float measuredItemsWidth = 0.0f;
    auto currentIndex = startIndex_;
    // TODO: need to consider [colunmStart]\[columsEnd] of [GridItem]
    // TODO: shoule we use policy of adaptive layout according to size of [GridItem] ?
    if (startMainLineIndex_ - 1 < 0) {
        LOGI("startMainLineIndex: %{public}d is alreay the first line, no forward line to make", startMainLineIndex_);
        return -1.0f;
    }
    startMainLineIndex_--;
    bool doneCreateNewLine = false;
    for (uint32_t i = 0; i < crossCount_; i++) {
        if (currentIndex-- < 0) {
            break;
        }
        // Step1. Get wrapper of [GridItem]
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
        if (!itemWrapper) {
            LOGE("GridItem wrapper of index %{public}u null", currentIndex);
            break;
        }
        // Step2. Make constraint and measure child
        // TODO: need to consider [colunmStart]\[columsEnd] of [GridItem]
        // TODO: need to use [isScrollable_]
        itemWrapper->Measure(MakeMeasureConstraintForGridItem(mainSize, crossSize, 1, gridLayoutProperty));

        // Step3. Measure [GridItem]
        auto itemSize = itemWrapper->GetGeometryNode()->GetFrameSize();
        LOGE("startMainLineIndex_: %u, currentIndex: %d, itemSize: %s", startMainLineIndex_, currentIndex,
            itemSize.ToString().c_str());
        measuredItemsWidth += GetCrossAxisSize(itemSize, GetAxis());
        lineHeight = std::max(GetMainAxisSize(itemSize, GetAxis()), lineHeight);
        gridMatrix_[startMainLineIndex_][currentIndex] = 1; // TODO: get [colunmStart]\[columsEnd] of [GridItem]
        startIndex_ = currentIndex;
        doneCreateNewLine = true;
    }
    // If it fails to create new line when [FillNewLineForward] is called, it means that it reaches start
    if (!doneCreateNewLine) {
        reachStart_ = true;
    }
    return lineHeight;
}

float GridLayoutController::FillNewLineBackward(
    float crossSize, float mainSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper)
{
    // To make the code more convinient to read, we name a param in situation of vertical, for exacmple:
    // 1. [lineHight] means height of a row when the Grid is vertical;
    // 2. [lineHight] means width of a column when the Grid is horizontal;
    // Other params are also named according to this principle.
    float lineHeight = -1.0f;
    float measuredItemsWidth = 0.0f;
    auto currentIndex = endIndex_ + 1;
    currentMainLineIndex_++; // if it fails to fill a new line backward, do [currentMainLineIndex_--]
    // TODO: need to consider [colunmStart]\[columsEnd] of [GridItem]
    // TODO: shoule we use policy of adaptive layout according to size of [GridItem] ?
    bool doneFillLine = false;
    for (uint32_t i = 0; i < crossCount_; i++) {
        // Step1. Get wrapper of [GridItem]
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
        if (!itemWrapper) {
            LOGE("GridItem wrapper of index %{public}u "
                 "null---------------reachEnd----------------------------------------",
                currentIndex);
            break;
        }
        // Step2. Make constraint and measure child
        // TODO: need to consider [colunmStart]\[columsEnd] of [GridItem]
        // TODO: need to use [isScrollable_]
        itemWrapper->Measure(MakeMeasureConstraintForGridItem(mainSize, crossSize, 1, gridLayoutProperty));

        // Step3. Measure [GridItem]
        auto itemSize = itemWrapper->GetGeometryNode()->GetFrameSize();
        measuredItemsWidth += GetCrossAxisSize(itemSize, GetAxis());
        lineHeight = std::max(GetMainAxisSize(itemSize, GetAxis()), lineHeight);
        gridMatrix_[currentMainLineIndex_][currentIndex] = 1; // TODO: get [colunmStart]\[columsEnd] of [GridItem]
        endIndex_ = currentIndex;
        currentIndex++;
        doneFillLine = true;
    }
    if (!doneFillLine) {
        currentMainLineIndex_--; // If it fails to fill a new line backward, do [currentMainLineIndex_--]
    } else {
        lineHeightMap_[currentMainLineIndex_] = lineHeight;
        endMainLineIndex_ = currentMainLineIndex_;
    }
    return lineHeight;
}
void GridLayoutController::StripItemsOutOfViewport()
{
    // Erase records that are out of viewport
    // TODO: add cache and inactive item
    // 1. Erase records that are on top of viewport
    if (lineHeightMap_.empty() || gridMatrix_.empty()) {
        return;
    }
    int32_t startIndexInMap = lineHeightMap_.begin()->first;
    for (int32_t i = startIndexInMap; i < startMainLineIndex_; i++) {
        lineHeightMap_.erase(i);
        gridMatrix_.erase(i);
    }

    // 2. Erase records that are under viewport
    if (lineHeightMap_.empty() || gridMatrix_.empty()) {
        return;
    }
    for (int32_t i = endMainLineIndex_ + 1; i < lineHeightMap_.size(); i++) {
        lineHeightMap_.erase(i);
        gridMatrix_.erase(i);
    }
}

bool GridLayoutController::UpdateScrollPosition(float offset, int32_t source)
{
    // When finger moves down, offset is positive.
    // When finger moves up, offset is negative.
    if (reachEnd_) {
        if (LessOrEqual(offset, 0)) {
            return false;
        }
        reachEnd_ = false;
    }
    if (reachStart_) {
        if (GreatOrEqual(offset, 0.0)) {
            return false;
        }
        reachStart_ = false;
    }
    currentOffset_ += offset;
    return true;
}

LayoutConstraintF GridLayoutController::MakeMeasureConstraintForGridItem(float mainSize, float crossSize,
    uint32_t itemFractionCount, const RefPtr<GridLayoutProperty>& gridLayoutProperty) const
{
    float itemMainSize = isConfiguredScrollable_ ? Infinity<float>() : mainSize / static_cast<float>(mainCount_);
    float fractionWidth = crossSize / static_cast<float>(crossCount_);
    float itemCrossSize = fractionWidth * static_cast<float>(itemFractionCount);
    SizeF itemIdealSize = isVertical_ ? SizeF(itemCrossSize, itemMainSize) : SizeF(itemMainSize, itemCrossSize);
    auto itemConstraint = gridLayoutProperty->CreateChildConstraint().value_or(LayoutConstraintF());
    itemConstraint.parentIdealSize = itemIdealSize;
    itemConstraint.maxSize = itemIdealSize;
    itemConstraint.minSize = SizeF();
    return itemConstraint;
}

Axis GridLayoutController::GetAxis() const
{
    return isVertical_ ? Axis::VERTICAL : Axis::HORIZONTAL;
}

// only for debug use
void GridLayoutController::PrintGridMatrix() const
{
    for (const auto& record : gridMatrix_) {
        for (const auto& item : record.second) {
            LOGD("grid matrix -- line: %{public}d, item: %{public}d, fr: %{public}d", record.first, item.first,
                item.second);
        }
    }
}

// only for debug use
void GridLayoutController::PrintLineHeightMap() const
{
    for (const auto& record : lineHeightMap_) {
        LOGD("line height -- line: %{public}d, lineHeight: %{public}f", record.first, record.second);
    }
}

} // namespace OHOS::Ace::NG
