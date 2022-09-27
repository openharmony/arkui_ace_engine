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

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_utils.h"

#ifdef NG_BUILD
#include "ace_shell/shell/common/window_manager.h"
#endif

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
    float crossFrWidth = GetCrossAxisSize(size, gridLayoutInfo_.axis_) / static_cast<float>(crossCount_);

    // For e.g, when a vertical grid has two [GridItem] in first row, [gridMatrix_] is like {[0: {[0: 1fr], [1: 2fr]}]}
    // TODO: Support horizontal Grid
    float prevLineHeight = 0.0f;
    for (const auto& line : gridLayoutInfo_.gridMatrix_) {
        auto offset = childFrameOffset + OffsetF(0.0, prevLineHeight);
        if (line.second.empty()) {
            LOGE("line %{public}d should not be empty, please check.", line.first);
            break;
        }
        float prevItemCrossSize = 0.0f;
        for (auto iter = line.second.begin(); iter != line.second.end(); iter++) {
            offset +=
                gridLayoutProperty->IsVertical() ? OffsetF(prevItemCrossSize, 0.0) : OffsetF(0.0, prevItemCrossSize);
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(iter->first);
            if (!wrapper) {
                LOGE("item wrapper of index: %{public}d is null, please check.", iter->first);
                continue;
            }
            wrapper->GetGeometryNode()->SetFrameOffset(offset);
            wrapper->Layout(parentOffset);
            prevItemCrossSize = static_cast<float>(iter->second) * crossFrWidth;
        }
        prevLineHeight += gridLayoutInfo_.lineHeightMap_[line.first];
    }
}

void GridScrollLayoutAlgorithm::FillGridViewportAndMeasureChildren(
    float mainSize, float crossSize, const RefPtr<GridLayoutProperty>& gridLayoutProperty, LayoutWrapper* layoutWrapper)
{
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
    if (LessOrEqual(
            gridLayoutInfo_.currentOffset_, 0.0)) { // If [currentOffset_] is none-positive, it means no blank at start
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

// When a moving up event comes, the [currrentOffset_] may have been reduced too much than the items really need to
// be moved up, so we need to modify [currrentOffset_] accrording to previous position.
void GridScrollLayoutAlgorithm::ModifyCurrentOffsetWhenReachEnd(float mainSize)
{
    // Step1. Calculate total length of all items in viewport. [lengthOfItemsInViewport] must be greater than or equal
    // to viewport height
    float lengthOfItemsInViewport = 0.0f;
    for (auto i = gridLayoutInfo_.startMainLineIndex_; i <= gridLayoutInfo_.endMainLineIndex_; i++) {
        lengthOfItemsInViewport += gridLayoutInfo_.lineHeightMap_[i];
    }

    // Step2. Calculate real offset that items can only be moved up by.
    float realOffsetToMoveUp =
        lengthOfItemsInViewport - mainSize + gridLayoutInfo_.prevOffset_; // Hint: [prevOffset_] is a non-positive value

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
    while (LessNotEqual(mainLength, mainSize)) { // Measure grid items row by row
        auto gridMatrixIter = gridLayoutInfo_.gridMatrix_.find(++currentMainLineIndex_);
        if (gridMatrixIter == gridLayoutInfo_.gridMatrix_.end()) {
            runOutOfRecord = true;
            break; // If [gridMatrix_] does not contain record of line [currentMainLineIndex_], do [FillNewLineBackward]
        }
        float lineHeight = -1.0f;
        int32_t currentIndex = 0;

        // One record is like [0: 1fr] or [1: 2fr]
        for (const auto& gridItemRecord : gridMatrixIter->second) {
            currentIndex = gridItemRecord.first;
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
            if (!itemWrapper) {
                LOGE("GridItem wrapper of index %{public}u null", currentIndex);
                break;
            }
            itemWrapper->Measure(
                MakeMeasureConstraintForGridItem(mainSize, crossSize, gridItemRecord.second, gridLayoutProperty));
            auto itemSize = itemWrapper->GetGeometryNode()->GetFrameSize();
            lineHeight = std::max(GetMainAxisSize(itemSize, gridLayoutInfo_.axis_), lineHeight);
            // Record end index. When fill new line, the [endIndex_] will be the first item index to request
            gridLayoutInfo_.endIndex_ = gridItemRecord.first;
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
    // To make the code more convinient to read, we name a param in situation of vertical, for exacmple:
    // 1. [lineHight] means height of a row when the Grid is vertical;
    // 2. [lineHight] means width of a column when the Grid is horizontal;
    // Other params are also named according to this principle.
    float lineHeight = -1.0f;
    auto currentIndex = gridLayoutInfo_.startIndex_;
    // TODO: need to consider [colunmStart]\[columsEnd] of [GridItem]
    // TODO: shoule we use policy of adaptive layout according to size of [GridItem] ?
    if (gridLayoutInfo_.startMainLineIndex_ - 1 < 0) {
        LOGI("startMainLineIndex: %{public}d is alreay the first line, no forward line to make",
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
        // Step2. Make constraint and measure child
        // TODO: need to consider [colunmStart]\[columsEnd] of [GridItem]
        // TODO: need to use [isScrollable_]
        itemWrapper->Measure(MakeMeasureConstraintForGridItem(mainSize, crossSize, 1, gridLayoutProperty));

        // Step3. Measure [GridItem]
        auto itemSize = itemWrapper->GetGeometryNode()->GetFrameSize();
        lineHeight = std::max(GetMainAxisSize(itemSize, gridLayoutInfo_.axis_), lineHeight);
        // TODO: get [colunmStart]\[columsEnd] of [GridItem]
        gridLayoutInfo_.gridMatrix_[gridLayoutInfo_.startMainLineIndex_][currentIndex] = 1;
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
    // TODO: need to consider [colunmStart]\[columsEnd] of [GridItem]
    // TODO: shoule we use policy of adaptive layout according to size of [GridItem] ?
    bool doneFillLine = false;
    for (uint32_t i = 0; i < crossCount_; i++) {
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
        lineHeight = std::max(GetMainAxisSize(itemSize, gridLayoutInfo_.axis_), lineHeight);
        // TODO: get [colunmStart]\[columsEnd] of [GridItem]
        gridLayoutInfo_.gridMatrix_[currentMainLineIndex_][currentIndex] = 1;
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
    // Erase records that are out of viewport
    // 1. Erase records that are on top of viewport
    if (gridLayoutInfo_.lineHeightMap_.empty() || gridLayoutInfo_.gridMatrix_.empty()) {
        return;
    }
    std::list<int32_t> removeRows;
    for (const auto& [rowIndex, rowIndexMap] : gridLayoutInfo_.gridMatrix_) {
        if (rowIndex < gridLayoutInfo_.startMainLineIndex_) {
            for (auto&& [index, fr] : rowIndexMap) {
                layoutWrapper->RemoveChildInRenderTree(index);
            }
            removeRows.emplace_back(rowIndex);
        }
        if (rowIndex > gridLayoutInfo_.endMainLineIndex_) {
            for (auto&& [index, fr] : rowIndexMap) {
                layoutWrapper->RemoveChildInRenderTree(index);
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

LayoutConstraintF GridScrollLayoutAlgorithm::MakeMeasureConstraintForGridItem(float mainSize, float crossSize,
    uint32_t itemFractionCount, const RefPtr<GridLayoutProperty>& gridLayoutProperty) const
{
    float itemMainSize =
        gridLayoutProperty->IsConfiguredScrollable() ? Infinity<float>() : mainSize / static_cast<float>(mainCount_);
    float fractionWidth = crossSize / static_cast<float>(crossCount_);
    float itemCrossSize = fractionWidth * static_cast<float>(itemFractionCount);
    SizeF itemIdealSize =
        gridLayoutProperty->IsVertical() ? SizeF(itemCrossSize, itemMainSize) : SizeF(itemMainSize, itemCrossSize);
    auto itemConstraint = gridLayoutProperty->CreateChildConstraint();

    // The percent size of GridItem is based on the fraction size, for e.g., if a GridItem has width of "50%" in Grid
    // configured with columnsTemplate = "1fr 1fr", rowsTemplate = "1fr 1fr", then tht GridItem width = [width of 1fr] *
    // 50%
    // [itemFractionCount] is now only in direction of cross axis
    // TODO: consider rowStart/rowEnd
    float widthPercentBase =
        GreatOrEqual(crossCount_, Infinity<uint32_t>())
            ? itemConstraint.percentReference.Width()
            : itemConstraint.percentReference.Width() / static_cast<float>(crossCount_ * itemFractionCount);
    float heightPercentBase = GreatOrEqual(mainCount_, Infinity<uint32_t>())
                                  ? itemConstraint.percentReference.Height()
                                  : itemConstraint.percentReference.Height() / static_cast<float>(mainCount_);
    itemConstraint.percentReference = SizeF(widthPercentBase, heightPercentBase);
    itemConstraint.maxSize = itemIdealSize;
    return itemConstraint;
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