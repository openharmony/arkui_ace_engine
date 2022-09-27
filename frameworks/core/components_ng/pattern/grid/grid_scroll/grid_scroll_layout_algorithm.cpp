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

#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"

#include <list>
#include <optional>
#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void GridScrollLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);

    // Step1: Decide size of Grid
    Axis axis = gridLayoutInfo_.axis_;
    auto idealSize = CreateIdealSize(
        gridLayoutProperty->GetLayoutConstraint().value(), axis, gridLayoutProperty->GetMeasureType(), true);
    if (GreatOrEqual(GetMainAxisSize(idealSize, axis), Infinity<float>())) {
        // TODO: use total height of all children as grid's main size when main size of ideal is infinite
        LOGE("size of main axis value is infinity, please check");
        return;
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    MinusPaddingToSize(gridLayoutProperty->CreatePaddingAndBorder(), idealSize);

    InitialItemsCrossSize(gridLayoutProperty, idealSize);

    // Step2: Measure children that can be displayed in viewport of Grid
    float mainSize = GetMainAxisSize(idealSize, axis);
    float crossSize = GetCrossAxisSize(idealSize, axis);
    FillGridViewportAndMeasureChildren(mainSize, crossSize, gridLayoutProperty, layoutWrapper);
    StripItemsOutOfViewport(layoutWrapper);
}

void GridScrollLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto childFrameOffset = OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f));
    childFrameOffset += gridLayoutProperty->IsVertical() ? OffsetF(0.0f, gridLayoutInfo_.currentOffset_)
                                                         : OffsetF(gridLayoutInfo_.currentOffset_, 0.0f);
    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();

    float prevLineHeight = 0.0f;
    for (const auto& line : gridLayoutInfo_.gridMatrix_) {
        auto prevLineOffset = axis_ == Axis::VERTICAL ? OffsetF(0.0, prevLineHeight) : OffsetF(prevLineHeight, 0.0);
        auto offset = childFrameOffset + prevLineOffset;
        if (line.second.empty()) {
            LOGE("line %{public}d should not be empty, please check.", line.first);
            break;
        }
        int32_t itemIdex = -1;
        for (auto iter = line.second.begin(); iter != line.second.end(); iter++) {
            // If item index is the same, must be the same GridItem, need't layout again.
            if (itemIdex == iter->second) {
                continue;
            }
            itemIdex = iter->first;
            auto crossOffset = itemsCrossPosition_.at(iter->second);
            if (axis_ == Axis::VERTICAL) {
                offset.SetX(crossOffset);
            } else {
                offset.SetY(crossOffset);
            }
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(iter->second);
            if (!wrapper) {
                LOGE("item wrapper of index: %{public}d is null, please check.", iter->second);
                continue;
            }
            wrapper->GetGeometryNode()->SetFrameOffset(offset);
            wrapper->Layout(parentOffset);
        }
        prevLineHeight +=
            gridLayoutInfo_.lineHeightMap_[line.first] + GridUtils::GetMainGap(gridLayoutProperty, size, axis_);
    }
}

void GridScrollLayoutAlgorithm::InitialItemsCrossSize(
    const RefPtr<GridLayoutProperty>& layoutProperty, const SizeF& frameSize)
{
    itemsCrossSize_.clear();
    auto rowsTemplate = layoutProperty->GetRowsTemplate().value_or("");
    auto columnsTemplate = layoutProperty->GetColumnsTemplate().value_or("");
    axis_ = columnsTemplate.empty() ? Axis::HORIZONTAL : Axis::VERTICAL;
    auto scale = layoutProperty->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(layoutProperty->GetRowsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    auto columnsGap =
        ConvertToPx(layoutProperty->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    std::vector<float> crossLens;
    if (!rowsTemplate.empty()) {
        crossLens = GridUtils::ParseArgs(rowsTemplate, frameSize.Height(), rowsGap);
    } else {
        crossLens = GridUtils::ParseArgs(columnsTemplate, frameSize.Width(), columnsGap);
    }

    int32_t index = 0;
    for (const auto& len : crossLens) {
        itemsCrossSize_.try_emplace(index, len);
        ++index;
    }
}

void GridScrollLayoutAlgorithm::FillGridViewportAndMeasureChildren(
    float mainSize, float crossSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper)
{
    crossIndex_ = 0;
    mainIndex_ = currentMainLineIndex_;
    itemsCrossPosition_.clear();
    float mainLength = gridLayoutInfo_.currentOffset_;

    // Step1: Measure [GridItem] that has been recorded to [gridMatrix_]
    MeasureRecordedItems(mainSize, crossSize, gridLayoutProperty, layoutWrapper, mainLength);

    // Step2: When done measure items in record, request new items to fill blank at end
    FillBlankAtEnd(mainSize, crossSize, gridLayoutProperty, layoutWrapper, mainLength);
    if (gridLayoutInfo_.reachEnd_) { // If it reaches end when [FillBlankAtEnd], modify [currentOffset_]
        ModifyCurrentOffsetWhenReachEnd(mainSize);
        return;
    }

    // Step3: Check if need to fill blank at start (in situation of grid items moving down)
    FillBlankAtStart(mainSize, crossSize, gridLayoutProperty, layoutWrapper, mainLength);
    if (gridLayoutInfo_.reachStart_) {
        gridLayoutInfo_.currentOffset_ = 0.0;
        gridLayoutInfo_.prevOffset_ = 0.0;
    }
}

void GridScrollLayoutAlgorithm::FillBlankAtStart(float mainSize, float crossSize,
    const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper, float& mainLength)
{
    // If [currentOffset_] is none-positive, it means no blank at start
    if (LessOrEqual(gridLayoutInfo_.currentOffset_, 0.0)) {
        return;
    }
    auto blankAtStart = gridLayoutInfo_.currentOffset_;
    while (GreatNotEqual(blankAtStart, 0.0)) {
        float lineHeight = FillNewLineForward(crossSize, mainSize, gridLayoutProperty, layoutWrapper);
        if (GreatNotEqual(lineHeight, 0.0)) {
            gridLayoutInfo_.lineHeightMap_[gridLayoutInfo_.startMainLineIndex_] = lineHeight;
            blankAtStart -= lineHeight;
            continue;
        }
        gridLayoutInfo_.reachStart_ = true;
        break;
    }
    gridLayoutInfo_.currentOffset_ = blankAtStart;
    gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
}

// When a moving up event comes, the [currentOffset_] may have been reduced too much than the items really need to
// be moved up, so we need to modify [currentOffset_] according to previous position.
void GridScrollLayoutAlgorithm::ModifyCurrentOffsetWhenReachEnd(float mainSize)
{
    // Step1. Calculate total length of all items in viewport.
    // [lengthOfItemsInViewport] must be greater than or equal to viewport height
    float lengthOfItemsInViewport = 0.0f;
    for (auto i = gridLayoutInfo_.startMainLineIndex_; i <= gridLayoutInfo_.endMainLineIndex_; i++) {
        lengthOfItemsInViewport += gridLayoutInfo_.lineHeightMap_[i];
    }

    // Step2. Calculate real offset that items can only be moved up by.
    // Hint: [prevOffset_] is a non-positive value
    float realOffsetToMoveUp = lengthOfItemsInViewport - mainSize + gridLayoutInfo_.prevOffset_;

    // Step3. modify [currentOffset_]
    gridLayoutInfo_.currentOffset_ = gridLayoutInfo_.prevOffset_ - realOffsetToMoveUp;
    gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
}

void GridScrollLayoutAlgorithm::FillBlankAtEnd(float mainSize, float crossSize,
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
        gridLayoutInfo_.reachEnd_ = true;
        break;
    };
}

void GridScrollLayoutAlgorithm::MeasureRecordedItems(float mainSize, float crossSize,
    const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper, float& mainLength)
{
    currentMainLineIndex_ = gridLayoutInfo_.startMainLineIndex_ - 1;
    bool runOutOfRecord = false;
    // Measure grid items row by row
    while (LessNotEqual(mainLength, mainSize)) {
        // If [gridMatrix_] does not contain record of line [currentMainLineIndex_], do [FillNewLineBackward]
        auto gridMatrixIter = gridLayoutInfo_.gridMatrix_.find(++currentMainLineIndex_);
        if (gridMatrixIter == gridLayoutInfo_.gridMatrix_.end()) {
            runOutOfRecord = true;
            break;
        }
        float lineHeight = -1.0f;
        int32_t currentIndex = 0;

        for (const auto& gridItemRecord : gridMatrixIter->second) {
            currentIndex = gridItemRecord.second;
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
            if (!itemWrapper) {
                LOGE("GridItem wrapper of index %{public}u null", currentIndex);
                break;
            }
            MeasureChild(mainSize, crossSize, currentIndex, layoutWrapper, itemWrapper);
            auto itemSize = itemWrapper->GetGeometryNode()->GetFrameSize();
            lineHeight = std::max(GetMainAxisSize(itemSize, gridLayoutInfo_.axis_), lineHeight);
            // Record end index. When fill new line, the [endIndex_] will be the first item index to request
            gridLayoutInfo_.endIndex_ = gridItemRecord.second;
        }

        if (lineHeight > 0) { // Means at least one item has been measured
            gridLayoutInfo_.lineHeightMap_[currentMainLineIndex_] = lineHeight;
            mainLength += lineHeight;
        }
        // If a line moves up out of viewport, update [startIndex_], [currentOffset_] and [startMainLineIndex_], and
        // delete record in [gridMatrix_] and [lineHeightMap_]. The strip operation of [gridMatrix_] and
        // [lineHeightMap_] will take place in [StripItemsOutOfViewport].
        // TODO: inactive items
        if (LessOrEqual(mainLength, 0.0)) {
            gridLayoutInfo_.currentOffset_ = mainLength;
            gridLayoutInfo_.startMainLineIndex_ = currentMainLineIndex_ + 1;
            gridLayoutInfo_.startIndex_ = currentIndex + 1;
        }
    }
    // Case 1. if this while-loop breaks due to running out of records, the [currentMainLineIndex_] is larger by 1 than
    // real main line index, so reduce 1.
    // Case 2. if this while-loop stops due to false result of [LessNotEqual(mainLength, mainSize)], the
    // [currentMainLineIndex_] is exactly the real main line index. Update [endMainLineIndex_] when the recorded items
    // are done measured.
    gridLayoutInfo_.endMainLineIndex_ = runOutOfRecord ? --currentMainLineIndex_ : currentMainLineIndex_;
}

float GridScrollLayoutAlgorithm::FillNewLineForward(
    float crossSize, float mainSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper)
{
    // To make the code more convenient to read, we name a param in situation of vertical, for example:
    // 1. [lineHight] means height of a row when the Grid is vertical;
    // 2. [lineHight] means width of a column when the Grid is horizontal;
    // Other params are also named according to this principle.
    float lineHeight = -1.0f;
    auto currentIndex = gridLayoutInfo_.startIndex_;
    // TODO: shoule we use policy of adaptive layout according to size of [GridItem] ?
    if (gridLayoutInfo_.startMainLineIndex_ - 1 < 0) {
        LOGI("startMainLineIndex: %{public}d is already the first line, no forward line to make",
            gridLayoutInfo_.startMainLineIndex_);
        return -1.0f;
    }
    gridLayoutInfo_.startMainLineIndex_--;
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
        // Step2. Measure child
        // TODO: need to use [isScrollable_]
        i += MeasureChild(mainSize, crossSize, currentIndex, layoutWrapper, itemWrapper);

        // Step3. Measure [GridItem]
        auto itemSize = itemWrapper->GetGeometryNode()->GetFrameSize();
        lineHeight = std::max(GetMainAxisSize(itemSize, gridLayoutInfo_.axis_), lineHeight);
        gridLayoutInfo_.startIndex_ = currentIndex;
        doneCreateNewLine = true;
    }
    // If it fails to create new line when [FillNewLineForward] is called, it means that it reaches start
    if (!doneCreateNewLine) {
        gridLayoutInfo_.reachStart_ = true;
    }
    return lineHeight;
}

float GridScrollLayoutAlgorithm::FillNewLineBackward(
    float crossSize, float mainSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper)
{
    // To make the code more convenient to read, we name a param in situation of vertical, for example:
    // 1. [lineHight] means height of a row when the Grid is vertical;
    // 2. [lineHight] means width of a column when the Grid is horizontal;
    // Other params are also named according to this principle.
    float lineHeight = -1.0f;
    auto currentIndex = gridLayoutInfo_.endIndex_ + 1;
    currentMainLineIndex_++; // if it fails to fill a new line backward, do [currentMainLineIndex_--]
    // TODO: shoule we use policy of adaptive layout according to size of [GridItem] ?
    bool doneFillLine = false;
    for (uint32_t i = 0; i < crossCount_; i++) {
        // Step1. Get wrapper of [GridItem]
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
        if (!itemWrapper) {
            LOGE("GridItem wrapper of index %{public}u null", currentIndex);
            break;
        }
        // Step2. Measure child
        i += MeasureChild(mainSize, crossSize, currentIndex, layoutWrapper, itemWrapper);

        // Step3. Measure [GridItem]
        auto itemSize = itemWrapper->GetGeometryNode()->GetFrameSize();
        lineHeight = std::max(GetMainAxisSize(itemSize, gridLayoutInfo_.axis_), lineHeight);
        gridLayoutInfo_.endIndex_ = currentIndex;
        currentIndex++;
        doneFillLine = true;
    }
    if (!doneFillLine) {
        // If it fails to fill a new line backward, do [currentMainLineIndex_--]
        currentMainLineIndex_--;
    } else {
        gridLayoutInfo_.lineHeightMap_[currentMainLineIndex_] = lineHeight;
        gridLayoutInfo_.endMainLineIndex_ = currentMainLineIndex_;
    }
    return lineHeight;
}
void GridScrollLayoutAlgorithm::StripItemsOutOfViewport(LayoutWrapper* layoutWrapper)
{
    // Erase records that are out of viewport.
    if (gridLayoutInfo_.lineHeightMap_.empty() || gridLayoutInfo_.gridMatrix_.empty()) {
        return;
    }
    std::list<int32_t> removeRows;
    for (const auto& [rowIndex, columnMap] : gridLayoutInfo_.gridMatrix_) {
        // 1. Erase records that are on top of viewport.
        if (rowIndex < gridLayoutInfo_.startMainLineIndex_) {
            for (auto&& [columnIndex, itemIndex] : columnMap) {
                layoutWrapper->RemoveChildInRenderTree(itemIndex);
            }
            removeRows.emplace_back(rowIndex);
        }
        // 1. Erase records that are on bottom of viewport.
        if (rowIndex > gridLayoutInfo_.endMainLineIndex_) {
            for (auto&& [columnIndex, itemIndex] : columnMap) {
                layoutWrapper->RemoveChildInRenderTree(itemIndex);
            }
            removeRows.emplace_back(rowIndex);
        }
    }
    for (const auto& index : removeRows) {
        gridLayoutInfo_.gridMatrix_.erase(index);
        gridLayoutInfo_.lineHeightMap_.erase(index);
    }
    LOGD("grid item size : %{public}d", static_cast<int32_t>(gridLayoutInfo_.gridMatrix_.size()));
}

LayoutConstraintF GridScrollLayoutAlgorithm::CreateChildConstraint(float mainSize, float crossSize,
    const RefPtr<GridLayoutProperty>& gridLayoutProperty, int32_t crossStart, int32_t crossSpan) const
{
    float itemMainSize =
        gridLayoutProperty->IsConfiguredScrollable() ? Infinity<float>() : mainSize / static_cast<float>(mainCount_);

    auto frameSize = axis_ == Axis::VERTICAL ? SizeF(crossSize, mainSize) : SizeF(mainSize, crossSize);
    float itemCrossSize = GridUtils::GetCrossGap(gridLayoutProperty, frameSize, axis_) * (crossSpan - 1);
    for (int32_t index = 0; index < crossSpan; ++index) {
        int32_t crossIndex = (crossStart + index) % static_cast<int32_t>(crossCount_);
        if (crossIndex >= 0 && crossIndex < static_cast<int32_t>(itemsCrossSize_.size())) {
            itemCrossSize += itemsCrossSize_.at(crossIndex);
        }
    }

    SizeF itemIdealSize =
        gridLayoutProperty->IsVertical() ? SizeF(itemCrossSize, itemMainSize) : SizeF(itemMainSize, itemCrossSize);
    auto itemConstraint = gridLayoutProperty->CreateChildConstraint();

    // The percent size of GridItem is based on the fraction size, for e.g., if a GridItem has width of "50%" in Grid
    // configured with columnsTemplate = "1fr 1fr", rowsTemplate = "1fr 1fr",
    // then the GridItem width = [width of 1fr] * 50%,
    // [itemFractionCount] is now only in direction of cross axis
    float widthPercentBase =
        GreatOrEqual(crossCount_, Infinity<uint32_t>()) ? itemConstraint.percentReference.Width() : itemCrossSize;
    float heightPercentBase = GreatOrEqual(mainCount_, Infinity<uint32_t>())
                                  ? itemConstraint.percentReference.Height()
                                  : itemConstraint.percentReference.Height() / static_cast<float>(mainCount_);
    itemConstraint.percentReference = SizeF(widthPercentBase, heightPercentBase);
    itemConstraint.maxSize = itemIdealSize;
    itemConstraint.UpdateIllegalSelfIdealSizeWithCheck(axis_ == Axis::VERTICAL
                                                           ? OptionalSizeF(itemCrossSize, std::nullopt)
                                                           : OptionalSizeF(std::nullopt, itemCrossSize));
    return itemConstraint;
}

void GridScrollLayoutAlgorithm::GetNextGrid(int32_t& curMain, int32_t& curCross) const
{
    ++curCross;
    if (curCross >= static_cast<int32_t>(crossCount_)) {
        curCross = 0;
        ++curMain;
    }
}

int32_t GridScrollLayoutAlgorithm::MeasureChild(float mainSize, float crossSize, int32_t itemIndex,
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& childLayoutWrapper)
{
    auto gridLayoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(gridLayoutProperty, 0);
    auto childLayoutProperty = DynamicCast<GridItemLayoutProperty>(childLayoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(childLayoutProperty, 0);
    auto mainCount = static_cast<int32_t>(mainCount_);
    auto crossCount = static_cast<int32_t>(crossCount_);
    int32_t itemRowStart = childLayoutProperty->GetRowStart().value_or(-1);
    int32_t itemColStart = childLayoutProperty->GetColumnStart().value_or(-1);
    int32_t itemRowSpan = std::max(childLayoutProperty->GetRowEnd().value_or(-1) - itemRowStart + 1, 1);
    int32_t itemColSpan = std::max(childLayoutProperty->GetColumnEnd().value_or(-1) - itemColStart + 1, 1);
    auto mainStart = axis_ == Axis::VERTICAL ? itemRowStart : itemColStart;
    auto crossStart = axis_ == Axis::VERTICAL ? itemColStart : itemRowStart;
    auto mainSpan = axis_ == Axis::VERTICAL ? itemRowSpan : itemColSpan;
    auto crossSpan = axis_ == Axis::VERTICAL ? itemColSpan : itemRowSpan;

    if (itemRowStart >= 0 && itemRowStart < mainCount && itemColStart >= 0 && itemColStart < crossCount &&
        CheckGridPlaced(itemIndex, mainStart, crossStart, mainSpan, crossSpan)) {
        childLayoutWrapper->Measure(
            CreateChildConstraint(mainSize, crossSize, gridLayoutProperty, crossStart, crossSpan));
        itemsCrossPosition_.try_emplace(itemIndex, ComputeItemCrossPosition(layoutWrapper, crossStart));
    } else {
        while (!CheckGridPlaced(itemIndex, mainIndex_, crossIndex_, mainSpan, crossSpan)) {
            GetNextGrid(mainIndex_, crossIndex_);
            if (mainIndex_ >= mainCount || crossIndex_ >= crossCount) {
                break;
            }
        }
        if (mainIndex_ >= mainCount || crossIndex_ >= crossCount) {
            return 0;
        }
        childLayoutWrapper->Measure(
            CreateChildConstraint(mainSize, crossSize, gridLayoutProperty, crossIndex_, crossSpan));
        itemsCrossPosition_.try_emplace(itemIndex, ComputeItemCrossPosition(layoutWrapper, crossIndex_));
    }
    return crossSpan - 1;
}

bool GridScrollLayoutAlgorithm::CheckGridPlaced(
    int32_t index, int32_t main, int32_t cross, int32_t& mainSpan, int32_t& crossSpan)
{
    // If start position is already exist in gridMatrix, place grid item fail.
    auto mainIter = gridLayoutInfo_.gridMatrix_.find(main);
    if (mainIter != gridLayoutInfo_.gridMatrix_.end()) {
        auto crossIter = mainIter->second.find(cross);
        if (crossIter != mainIter->second.end()) {
            return false;
        }
    }

    // If cross length of grid item if out of range,  place grid item fail.
    if (cross + crossSpan > static_cast<int32_t>(crossCount_)) {
        return false;
    }

    // If any grid item is already exist in gridMatrix, place grid item fail.
    for (int32_t i = 0; i < mainSpan; i++) {
        mainIter = gridLayoutInfo_.gridMatrix_.find(i + main);
        if (mainIter == gridLayoutInfo_.gridMatrix_.end()) {
            continue;
        }
        for (int32_t j = 0; j < crossSpan; j++) {
            auto crossIter = mainIter->second.find(j + cross);
            if (crossIter != mainIter->second.end()) {
                return false;
            }
        }
    }

    // Padding grid matrix for grid item's range.
    for (int32_t i = main; i < main + mainSpan; ++i) {
        std::map<int32_t, int32_t> mainMap;
        auto iter = gridLayoutInfo_.gridMatrix_.find(i);
        if (iter != gridLayoutInfo_.gridMatrix_.end()) {
            mainMap = iter->second;
        }
        for (int32_t j = cross; j < cross + crossSpan; ++j) {
            mainMap.emplace(std::make_pair(j, index));
        }
        gridLayoutInfo_.gridMatrix_[i] = mainMap;
    }
    return true;
}

float GridScrollLayoutAlgorithm::ComputeItemCrossPosition(LayoutWrapper* layoutWrapper, int32_t crossStart) const
{
    auto layoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, 0);
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto scale = layoutProperty->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(layoutProperty->GetRowsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    auto columnsGap =
        ConvertToPx(layoutProperty->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto crossGap = axis_ == Axis::VERTICAL ? columnsGap : rowsGap;

    float position = 0.0f;
    for (int32_t index = 0; index < crossStart; ++index) {
        if (index >= 0 && index < static_cast<int32_t>(itemsCrossSize_.size())) {
            position += itemsCrossSize_.at(index);
        }
    }
    position += crossStart * crossGap;
    return position;
}

GridLayoutInfo GridScrollLayoutAlgorithm::GetGridLayoutInfo()
{
    return std::move(gridLayoutInfo_);
}

// only for debug use
void GridScrollLayoutAlgorithm::PrintGridMatrix(const std::map<int32_t, std::map<int32_t, uint32_t>>& gridMatrix)
{
    for (const auto& record : gridMatrix) {
        for (const auto& item : record.second) {
            LOGD("grid matrix -- line: %{public}d, item: %{public}d, fr: %{public}d", record.first, item.first,
                item.second);
        }
    }
}

// only for debug use
void GridScrollLayoutAlgorithm::PrintLineHeightMap(const std::map<int32_t, float>& lineHeightMap)
{
    for (const auto& record : lineHeightMap) {
        LOGD("line height -- line: %{public}d, lineHeight: %{public}f", record.first, record.second);
    }
}

} // namespace OHOS::Ace::NG