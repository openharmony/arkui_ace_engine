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

#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/templates_parser.h"
#include "core/pipeline_ng/pipeline_context.h"
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

    InitialItemsCrossSize(gridLayoutProperty, idealSize, layoutWrapper->GetTotalChildCount());

    // Step2: Measure children that can be displayed in viewport of Grid
    float mainSize = GetMainAxisSize(idealSize, axis);
    float crossSize = GetCrossAxisSize(idealSize, axis);
    if (!NearEqual(mainSize, gridLayoutInfo_.lastMainSize_)) {
        gridLayoutInfo_.ResetPositionFlags();
        UpdateOffsetOnVirtualKeyboardHeightChange(layoutWrapper, mainSize);
    }
    FillGridViewportAndMeasureChildren(mainSize, crossSize, layoutWrapper);

    // update cache info.
    layoutWrapper->SetCacheCount(static_cast<int32_t>(gridLayoutProperty->GetCachedCountValue(1) * crossCount_));

    AdaptToChildMainSize(layoutWrapper, gridLayoutProperty, mainSize, idealSize);

    // reset offsetEnd after scroll to moveToEndLineIndex_
    gridLayoutInfo_.offsetEnd_ = moveToEndLineIndex_ > 0
                                     ? (gridLayoutInfo_.endIndex_ + 1 >= layoutWrapper->GetTotalChildCount())
                                     : gridLayoutInfo_.offsetEnd_;
}

void GridScrollLayoutAlgorithm::UpdateOffsetOnVirtualKeyboardHeightChange(LayoutWrapper* layoutWrapper, float mainSize)
{
    if (GreatOrEqual(mainSize, gridLayoutInfo_.lastMainSize_)) {
        return;
    }
    // only need to offset vertical grid
    if (gridLayoutInfo_.axis_ != Axis::VERTICAL) {
        return;
    }

    auto grid = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(grid);
    auto focusHub = grid->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    // textField not in Grid
    if (!focusHub->IsCurrentFocus()) {
        return;
    }

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    // only when textField is onFocus
    auto focused = textFieldManager->GetOnFocusTextField().Upgrade();
    CHECK_NULL_VOID(focused);
    auto position = textFieldManager->GetClickPosition().GetY();
    auto gridOffset = grid->GetTransformRelativeOffset();
    auto offset = mainSize + gridOffset.GetY() - position;
    if (LessOrEqual(offset, 0.0)) {
        // negative offset to scroll down
        auto lineHeight = gridLayoutInfo_.GetAverageLineHeight();
        if (GreatNotEqual(lineHeight, 0)) {
            offset = floor(offset / lineHeight) * lineHeight;
        }
        gridLayoutInfo_.currentOffset_ += offset;
        LOGI("update offset on virtual keyboard height change, %{public}f", offset);
    }
}

void GridScrollLayoutAlgorithm::AdaptToChildMainSize(LayoutWrapper* layoutWrapper,
    RefPtr<GridLayoutProperty>& gridLayoutProperty, float mainSize, const SizeF& idealSize)
{
    gridLayoutInfo_.lastMainSize_ = mainSize;
    // grid with columnsTemplate/rowsTemplate and maxCount
    if (!gridLayoutProperty->HasMaxCount()) {
        return;
    }

    std::optional<CalcLength> mainAxisIdealSize;
    const auto& selfLayoutConstraint = gridLayoutProperty->GetCalcLayoutConstraint();
    if (selfLayoutConstraint && selfLayoutConstraint->selfIdealSize.has_value()) {
        mainAxisIdealSize = axis_ == Axis::HORIZONTAL ? selfLayoutConstraint->selfIdealSize->Width()
                                                      : selfLayoutConstraint->selfIdealSize->Height();
    }

    if (!mainAxisIdealSize.has_value()) {
        float lengthOfItemsInViewport = 0;
        for (auto i = gridLayoutInfo_.startMainLineIndex_; i <= gridLayoutInfo_.endMainLineIndex_; i++) {
            lengthOfItemsInViewport += (gridLayoutInfo_.lineHeightMap_[i] + mainGap_);
        }
        lengthOfItemsInViewport -= mainGap_;
        auto gridMainSize = std::min(lengthOfItemsInViewport, mainSize);
        // should use minCount * cellLength ?
        if (axis_ == Axis::HORIZONTAL) {
            gridMainSize = std::max(gridMainSize, gridLayoutProperty->GetLayoutConstraint()->minSize.Width());
            layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(gridMainSize, idealSize.Height()));
        } else {
            gridMainSize = std::max(gridMainSize, gridLayoutProperty->GetLayoutConstraint()->minSize.Height());
            layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(idealSize.Width(), gridMainSize));
        }
        gridLayoutInfo_.lastMainSize_ = gridMainSize;
        LOGI("gridMainSize:%{public}f", gridMainSize);
    }
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

    float prevLineHeight = 0.0f;
    layoutWrapper->RemoveAllChildInRenderTree();
    LargeItemForwardLineHeight(gridLayoutInfo_.startMainLineIndex_, layoutWrapper);
    for (auto i = gridLayoutInfo_.startMainLineIndex_; i <= gridLayoutInfo_.endMainLineIndex_; i++) {
        const auto& line = gridLayoutInfo_.gridMatrix_.find(i);
        if (line == gridLayoutInfo_.gridMatrix_.end()) {
            continue;
        }

        auto prevLineOffset = axis_ == Axis::VERTICAL ? OffsetF(0.0, prevLineHeight) : OffsetF(prevLineHeight, 0.0);
        if (line->second.empty()) {
            LOGE("line %{public}d should not be empty, please check.", line->first);
            break;
        }
        int32_t itemIdex = -1;
        float lineHeight = gridLayoutInfo_.lineHeightMap_[line->first];
        for (auto iter = line->second.begin(); iter != line->second.end(); iter++) {
            // If item index is the same, must be the same GridItem, need't layout again.
            if (itemIdex == iter->second) {
                continue;
            }
            itemIdex = iter->second;
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(itemIdex);
            auto crossIter = itemsCrossPosition_.find(itemIdex);
            if (crossIter == itemsCrossPosition_.end()) {
                LOGI("item %{public}d not in cross position", itemIdex);
                continue;
            }
            auto crossOffset = crossIter->second;
            auto offset = childFrameOffset + prevLineOffset;
            offset = CalculateLargeItemOffset(offset, itemIdex, i, iter->first);
            if (axis_ == Axis::VERTICAL) {
                offset.SetX(crossOffset);
            } else {
                offset.SetY(crossOffset);
            }
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(itemIdex);
            if (!wrapper) {
                LOGE("Layout item wrapper of index: %{public}d is null, please check.", itemIdex);
                continue;
            }
            auto frSize = itemsCrossSize_.at(iter->first);
            SizeF blockSize = gridLayoutProperty->IsVertical() ? SizeF(frSize, lineHeight) : SizeF(lineHeight, frSize);
            auto translate = Alignment::GetAlignPosition(
                blockSize, wrapper->GetGeometryNode()->GetMarginFrameSize(), Alignment::TOP_CENTER);
            wrapper->GetGeometryNode()->SetMarginFrameOffset(offset + translate);
            wrapper->Layout();
            auto layoutProperty = wrapper->GetLayoutProperty();
            CHECK_NULL_VOID(layoutProperty);
            auto gridItemLayoutProperty = AceType::DynamicCast<GridItemLayoutProperty>(layoutProperty);
            CHECK_NULL_VOID(gridItemLayoutProperty);
            gridItemLayoutProperty->UpdateMainIndex(line->first);
            gridItemLayoutProperty->UpdateCrossIndex(iter->first);
        }
        prevLineHeight += gridLayoutInfo_.lineHeightMap_[line->first] + mainGap_;
    }
    gridLayoutInfo_.totalHeightOfItemsInView_ = gridLayoutInfo_.GetTotalHeightOfItemsInView(mainGap_);
}

void GridScrollLayoutAlgorithm::InitialItemsCrossSize(
    const RefPtr<GridLayoutProperty>& layoutProperty, const SizeF& frameSize, int32_t childrenCount)
{
    itemsCrossSize_.clear();
    auto rowsTemplate = layoutProperty->GetRowsTemplate().value_or("");
    auto columnsTemplate = layoutProperty->GetColumnsTemplate().value_or("");
    axis_ = columnsTemplate.empty() ? Axis::HORIZONTAL : Axis::VERTICAL;
    auto scale = layoutProperty->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(layoutProperty->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap =
        ConvertToPx(layoutProperty->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    mainGap_ = axis_ == Axis::HORIZONTAL ? columnsGap : rowsGap;
    crossGap_ = axis_ == Axis::VERTICAL ? columnsGap : rowsGap;
    auto padding = layoutProperty->CreatePaddingAndBorder();
    crossPaddingOffset_ = axis_ == Axis::HORIZONTAL ? padding.top.value_or(0) : padding.left.value_or(0);

    auto crossSize = frameSize.CrossSize(axis_);
    std::vector<double> crossLens;
    if (!rowsTemplate.empty()) {
        crossLens = ParseTemplateArgs(GridUtils::ParseArgs(rowsTemplate), crossSize, crossGap_, childrenCount);
    } else {
        crossLens = ParseTemplateArgs(GridUtils::ParseArgs(columnsTemplate), crossSize, crossGap_, childrenCount);
    }
    if (crossLens.empty()) {
        crossLens.push_back(crossSize);
    }

    if (crossCount_ != crossLens.size()) {
        crossCount_ = crossLens.size();
        gridLayoutInfo_.crossCount_ = crossCount_;
    }

    int32_t index = 0;
    for (const auto& len : crossLens) {
        itemsCrossSize_.try_emplace(index, len);
        ++index;
    }
}

void GridScrollLayoutAlgorithm::FillGridViewportAndMeasureChildren(
    float mainSize, float crossSize, LayoutWrapper* layoutWrapper)
{
    itemsCrossPosition_.clear();
    UpdateGridLayoutInfo(layoutWrapper, mainSize);
    SkipForwardLines(mainSize, layoutWrapper);
    SkipBackwardLines(mainSize, layoutWrapper);

    if (!gridLayoutInfo_.lastCrossCount_) {
        gridLayoutInfo_.lastCrossCount_ = crossCount_;
    }

    if (gridLayoutInfo_.lastCrossCount_ != crossCount_ || layoutWrapper->GetHostNode()->GetChildrenUpdated() != -1 ||
        gridLayoutInfo_.IsResetted()) {
        gridLayoutInfo_.lastCrossCount_ = crossCount_;
        gridLayoutInfo_.lineHeightMap_.clear();
        gridLayoutInfo_.gridMatrix_.clear();
        gridLayoutInfo_.endIndex_ = -1;
        gridLayoutInfo_.endMainLineIndex_ = 0;
        gridLayoutInfo_.ResetPositionFlags();
        isChildrenUpdated_ = true;

        int32_t currentItemIndex = gridLayoutInfo_.startIndex_;
        auto firstItem = GetStartingItem(layoutWrapper, currentItemIndex);
        gridLayoutInfo_.startIndex_ = firstItem;
        currentMainLineIndex_ = (firstItem == 0 ? 0 : gridLayoutInfo_.startMainLineIndex_) - 1;
        gridLayoutInfo_.endIndex_ = firstItem - 1;
        LOGI("data reload begin, firstItem:%{public}d, currentItemIndex:%{public}d", firstItem, currentItemIndex);
        while (gridLayoutInfo_.endIndex_ < currentItemIndex) {
            auto lineHeight = FillNewLineBackward(crossSize, mainSize, layoutWrapper, false);
            if (LessNotEqual(lineHeight, 0.0)) {
                gridLayoutInfo_.reachEnd_ = true;
                break;
            }
        }
        gridLayoutInfo_.startMainLineIndex_ = currentMainLineIndex_;
        gridLayoutInfo_.UpdateStartIndexByStartLine();
        // FillNewLineBackward sometimes make startIndex_ > currentItemIndex
        while (gridLayoutInfo_.startIndex_ > currentItemIndex &&
               gridLayoutInfo_.gridMatrix_.find(gridLayoutInfo_.startMainLineIndex_) !=
                   gridLayoutInfo_.gridMatrix_.end()) {
            gridLayoutInfo_.startMainLineIndex_--;
            gridLayoutInfo_.UpdateStartIndexByStartLine();
        }
        LOGI("data reload end, startIndex_:%{public}d, startMainLineIndex_:%{public}d", gridLayoutInfo_.startIndex_,
            gridLayoutInfo_.startMainLineIndex_);
    }

    if (gridLayoutInfo_.scrollAlign_ == ScrollAlign::CENTER || gridLayoutInfo_.scrollAlign_ == ScrollAlign::END) {
        UpdateCurrentOffsetForJumpTo(layoutWrapper, mainSize);
    }
    gridLayoutInfo_.jumpIndex_ = -1;
    gridLayoutInfo_.scrollAlign_ = ScrollAlign::AUTO;

    // Step1: Measure [GridItem] that has been recorded to [gridMatrix_]
    float mainLength = MeasureRecordedItems(mainSize, crossSize, layoutWrapper);

    // Step2: When done measure items in record, request new items to fill blank at end
    FillBlankAtEnd(mainSize, crossSize, layoutWrapper, mainLength);
    if (gridLayoutInfo_.reachEnd_) { // If it reaches end when [FillBlankAtEnd], modify [currentOffset_]
        ModifyCurrentOffsetWhenReachEnd(mainSize);
    }

    // Step3: Check if need to fill blank at start (in situation of grid items moving down)
    auto haveNewLineAtStart = FillBlankAtStart(mainSize, crossSize, layoutWrapper);
    if (gridLayoutInfo_.reachStart_) {
        auto offset = gridLayoutInfo_.currentOffset_;
        if (!canOverScroll_) {
            gridLayoutInfo_.currentOffset_ = 0.0;
            gridLayoutInfo_.prevOffset_ = 0.0;
        }
        if (!haveNewLineAtStart) {
            return;
        }
        // we need lastline if blank at start is not fully filled when start line is shorter
        mainLength -= offset;
        currentMainLineIndex_ = gridLayoutInfo_.endMainLineIndex_;
        if (UseCurrentLines(mainSize, crossSize, layoutWrapper, mainLength)) {
            FillBlankAtEnd(mainSize, crossSize, layoutWrapper, mainLength);
            if (gridLayoutInfo_.reachEnd_) {
                ModifyCurrentOffsetWhenReachEnd(mainSize);
            }
        }
    }

    layoutWrapper->GetHostNode()->ChildrenUpdatedFrom(-1);
}

bool GridScrollLayoutAlgorithm::FillBlankAtStart(float mainSize, float crossSize, LayoutWrapper* layoutWrapper)
{
    bool fillNewLine = false;
    // If [currentOffset_] is non-positive, it means no blank at start
    if (LessOrEqual(gridLayoutInfo_.currentOffset_, 0.0)) {
        return fillNewLine;
    }
    auto blankAtStart = gridLayoutInfo_.currentOffset_;
    while (GreatNotEqual(blankAtStart, 0.0)) {
        float lineHeight = FillNewLineForward(crossSize, mainSize, layoutWrapper);
        if (GreatNotEqual(lineHeight, 0.0)) {
            gridLayoutInfo_.lineHeightMap_[gridLayoutInfo_.startMainLineIndex_] = lineHeight;
            blankAtStart -= (lineHeight + mainGap_);
            fillNewLine = true;
            continue;
        }
        gridLayoutInfo_.reachStart_ = true;
        break;
    }
    gridLayoutInfo_.currentOffset_ = blankAtStart;
    gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
    return fillNewLine;
}

// When a moving up event comes, the [currentOffset_] may have been reduced too much than the items really need to
// be moved up, so we need to modify [currentOffset_] according to previous position.
void GridScrollLayoutAlgorithm::ModifyCurrentOffsetWhenReachEnd(float mainSize)
{
    // Step1. Calculate total length of all items with main gap in viewport.
    // [lengthOfItemsInViewport] must be greater than or equal to viewport height
    float lengthOfItemsInViewport = gridLayoutInfo_.GetTotalHeightOfItemsInView(mainGap_);
    // scroll forward
    if (LessNotEqual(gridLayoutInfo_.prevOffset_, gridLayoutInfo_.currentOffset_)) {
        if (!canOverScroll_) {
            gridLayoutInfo_.reachEnd_ = false;
            return;
        } else if (!isChildrenUpdated_) {
            if (LessNotEqual(lengthOfItemsInViewport, mainSize)) {
                return;
            }
        }
    }
    // Step2. Calculate real offset that items can only be moved up by.
    // Hint: [prevOffset_] is a non-positive value
    if (LessNotEqual(lengthOfItemsInViewport, mainSize) && gridLayoutInfo_.startIndex_ == 0) {
        if (!canOverScroll_ || isChildrenUpdated_) {
            gridLayoutInfo_.currentOffset_ = 0;
            gridLayoutInfo_.prevOffset_ = 0;
        }
        return;
    }

    // last grid item is not fully showed
    if (GreatOrEqual(gridLayoutInfo_.currentOffset_ + lengthOfItemsInViewport, mainSize)) {
        return;
    }

    // Step3. modify [currentOffset_]
    if (!canOverScroll_) {
        float realOffsetToMoveUp = lengthOfItemsInViewport - mainSize + gridLayoutInfo_.prevOffset_;
        gridLayoutInfo_.currentOffset_ = gridLayoutInfo_.prevOffset_ - realOffsetToMoveUp;
        gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
    }
    gridLayoutInfo_.offsetEnd_ = true;
}

void GridScrollLayoutAlgorithm::FillBlankAtEnd(
    float mainSize, float crossSize, LayoutWrapper* layoutWrapper, float& mainLength)
{
    if (GreatNotEqual(mainLength, mainSize)) {
        return;
    }
    // When [mainLength] is still less than [mainSize], do [FillNewLineBackward] repeatedly until filling up the lower
    // part of the viewport
    while (LessNotEqual(mainLength, mainSize)) {
        float lineHeight = FillNewLineBackward(crossSize, mainSize, layoutWrapper, false);
        if (GreatOrEqual(lineHeight, 0.0)) {
            mainLength += lineHeight;
            continue;
        }
        gridLayoutInfo_.reachEnd_ = true;
        return;
    };
    // last line make LessNotEqual(mainLength, mainSize) and continue is reach end too
    gridLayoutInfo_.reachEnd_ = gridLayoutInfo_.endIndex_ == layoutWrapper->GetTotalChildCount() - 1;
}

OffsetF GridScrollLayoutAlgorithm::CalculateLargeItemOffset(
    OffsetF currOffset, int32_t itemIndex, int32_t currLineIndex, int32_t currentCrossIndex)
{
    OffsetF offset = currOffset;
    for (int32_t lastCrossIndex = currLineIndex - 1; lastCrossIndex >= 0; lastCrossIndex--) {
        auto LastGridMatrixIter = gridLayoutInfo_.gridMatrix_.find(lastCrossIndex);
        if (LastGridMatrixIter == gridLayoutInfo_.gridMatrix_.end()) {
            continue;
        }
        auto lastGridItemRecord = LastGridMatrixIter->second;
        auto lastLineCrossItem = lastGridItemRecord.find(currentCrossIndex);
        if (lastLineCrossItem == lastGridItemRecord.end()) {
            continue;
        }
        if (lastLineCrossItem->second == itemIndex) {
            offset -= axis_ == Axis::VERTICAL ? OffsetF(0, gridLayoutInfo_.lineHeightMap_[lastCrossIndex] + mainGap_)
                                              : OffsetF(gridLayoutInfo_.lineHeightMap_[lastCrossIndex] + mainGap_, 0.0);
        } else {
            break;
        }
    }

    return offset;
}

bool GridScrollLayoutAlgorithm::NeedAdjust(const RefPtr<GridItemLayoutProperty>& itemLayoutProperty)
{
    bool needAdjust = false;
    if (itemLayoutProperty->GetRowStart().has_value()) {
        currentItemRowStart_ = itemLayoutProperty->GetRowStart().value_or(-1);
        if ((currentItemRowStart_ < 0) || (currentItemRowStart_ >= static_cast<int32_t>(mainCount_))) {
            needAdjust = true;
        }
    }
    if (itemLayoutProperty->GetRowEnd().has_value()) {
        currentItemRowEnd_ = itemLayoutProperty->GetRowEnd().value_or(-1);
        if ((currentItemRowEnd_ < 0) || (currentItemRowEnd_ >= static_cast<int32_t>(mainCount_))) {
            needAdjust = true;
        }
    }
    if (itemLayoutProperty->GetColumnStart().has_value()) {
        currentItemColStart_ = itemLayoutProperty->GetColumnStart().value_or(-1);
        if ((currentItemColStart_ < 0) || (currentItemColStart_ >= static_cast<int32_t>(crossCount_))) {
            needAdjust = true;
        }
    }
    if (itemLayoutProperty->GetColumnEnd().has_value()) {
        currentItemColEnd_ = itemLayoutProperty->GetColumnEnd().value_or(-1);
        if ((currentItemColEnd_ < 0) || (currentItemColEnd_ >= static_cast<int32_t>(crossCount_))) {
            needAdjust = true;
        }
    }
    return needAdjust;
}

void GridScrollLayoutAlgorithm::AdjustRowColSpan(const RefPtr<LayoutWrapper>& itemLayoutWrapper)
{
    auto itemLayoutProperty = DynamicCast<GridItemLayoutProperty>(itemLayoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(itemLayoutProperty);
    bool needAdjust = false;
    currentItemRowSpan_ = 1;
    currentItemColSpan_ = 1;
    currentItemRowStart_ = -1;
    currentItemColStart_ = -1;
    currentItemColEnd_ = -1;
    currentItemRowEnd_ = -1;
    needAdjust = NeedAdjust(itemLayoutProperty);
    if (!needAdjust) {
        currentItemRowSpan_ = std::max(currentItemRowEnd_ - currentItemRowStart_ + 1, 1);
        currentItemColSpan_ = std::max(currentItemColEnd_ - currentItemColStart_ + 1, 1);
    } else {
        currentItemRowStart_ = -1;
        currentItemColStart_ = -1;
        currentItemColEnd_ = -1;
        currentItemRowEnd_ = -1;
    }
    if ((currentItemRowStart_ == -1 && currentItemRowEnd_ != -1) ||
        (currentItemRowEnd_ == -1 && currentItemRowStart_ != -1) ||
        (currentItemColStart_ == -1 && currentItemColEnd_ != -1) ||
        (currentItemColEnd_ == -1 && currentItemColStart_ != -1)) {
        currentItemRowSpan_ = 1;
        currentItemColSpan_ = 1;
        currentItemRowStart_ = -1;
        currentItemColStart_ = -1;
        currentItemColEnd_ = -1;
        currentItemRowEnd_ = -1;
    }
    if (currentItemRowSpan_ > 1 || currentItemColSpan_ > 1) {
        gridLayoutInfo_.hasBigItem_ = true;
    }
}

void GridScrollLayoutAlgorithm::LargeItemLineHeight(const RefPtr<LayoutWrapper>& itemWrapper, bool& hasNormalItem)
{
    AdjustRowColSpan(itemWrapper);
    auto mainSpan = axis_ == Axis::VERTICAL ? currentItemRowSpan_ : currentItemColSpan_;
    auto itemSize = itemWrapper->GetGeometryNode()->GetMarginFrameSize();
    if (mainSpan == 1) {
        cellAveLength_ = std::max(GetMainAxisSize(itemSize, gridLayoutInfo_.axis_), cellAveLength_);
        hasNormalItem = true;
    }

    if ((mainSpan > 1) && !hasNormalItem) {
        cellAveLength_ = std::max(GetMainAxisSize(itemSize, gridLayoutInfo_.axis_) / mainSpan, cellAveLength_);
    }
}

bool GridScrollLayoutAlgorithm::IsIndexInMatrix(int32_t index, int32_t& startLine)
{
    auto iter = std::find_if(gridLayoutInfo_.gridMatrix_.begin(), gridLayoutInfo_.gridMatrix_.end(),
        [index, &startLine](const std::pair<int32_t, std::map<int32_t, int32_t>>& item) {
            for (auto& subitem : item.second) {
                if (subitem.second == index) {
                    startLine = item.first;
                    return true;
                }
            }
            return false;
        });
    return (iter != gridLayoutInfo_.gridMatrix_.end());
}

void GridScrollLayoutAlgorithm::GetTargetIndexInfoWithBenchMark(
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
            auto currentWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex, false);
            CHECK_NULL_VOID(currentWrapper);
            auto layoutProperty = DynamicCast<GridItemLayoutProperty>(currentWrapper->GetLayoutProperty());
            CHECK_NULL_VOID(layoutProperty);
            auto gridSpan = layoutProperty->GetCrossSpan(gridLayoutInfo_.axis_);
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
}

void GridScrollLayoutAlgorithm::UpdateGridLayoutInfo(LayoutWrapper* layoutWrapper, float mainSize)
{
    /* 1. Have gotten gridLayoutInfo_.startMainLineIndex_ and directly jump to it */
    if (gridLayoutInfo_.jumpIndex_ < 0) {
        return;
    }
    /* 2. Need to find out the startMainLineIndex according to startIndex */
    int32_t targetIndex = gridLayoutInfo_.jumpIndex_;
    /* 2.1 invalid targetIndex */
    if (layoutWrapper->GetTotalChildCount() <= targetIndex) {
        return;
    }

    switch (gridLayoutInfo_.scrollAlign_) {
        case ScrollAlign::START:
        case ScrollAlign::END:
        case ScrollAlign::CENTER:
            ScrollToIndexStart(layoutWrapper, targetIndex);
            return;
        default:
            ScrollToIndexAuto(layoutWrapper, mainSize, targetIndex);
    }
}

void GridScrollLayoutAlgorithm::ScrollToIndexAuto(LayoutWrapper* layoutWrapper, float mainSize, int32_t targetIndex)
{
    int32_t startLine = 0;
    if (IsIndexInMatrix(targetIndex, startLine)) {
        if (startLine < gridLayoutInfo_.endMainLineIndex_ && startLine > gridLayoutInfo_.startMainLineIndex_) {
            return;
        }

        if (startLine >= gridLayoutInfo_.endMainLineIndex_) {
            auto totalViewHeight = gridLayoutInfo_.GetTotalHeightOfItemsInView(mainGap_);
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.currentOffset_ -= (totalViewHeight - mainSize + gridLayoutInfo_.currentOffset_);
            for (int32_t i = gridLayoutInfo_.endMainLineIndex_ + 1; i <= startLine; ++i) {
                gridLayoutInfo_.currentOffset_ -= (mainGap_ + gridLayoutInfo_.lineHeightMap_[i]);
            }
            gridLayoutInfo_.ResetPositionFlags();
            return;
        }

        // startLine <= gridLayoutInfo_.startMainLineIndex_
        gridLayoutInfo_.startMainLineIndex_ = startLine;
        gridLayoutInfo_.UpdateStartIndexByStartLine();
        gridLayoutInfo_.prevOffset_ = 0;
        gridLayoutInfo_.currentOffset_ = 0;
        gridLayoutInfo_.ResetPositionFlags();
        return;
    }

    /* 2.3 targetIndex is out of the matrix */
    if (gridLayoutInfo_.gridMatrix_.empty()) {
        LOGW("no grid for jump to index:%{public}d", targetIndex);
        return;
    }
    bool isTargetBackward = true;
    if (targetIndex < gridLayoutInfo_.gridMatrix_.begin()->second.begin()->second) {
        isTargetBackward = false;
    } else if (targetIndex > gridLayoutInfo_.gridMatrix_.rbegin()->second.rbegin()->second) {
        isTargetBackward = true;
    } else {
        return;
    }
    auto grid = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(grid);
    grid->ChildrenUpdatedFrom(0);
    GetTargetIndexInfoWithBenchMark(layoutWrapper, isTargetBackward, targetIndex);
    moveToEndLineIndex_ = isTargetBackward ? targetIndex : moveToEndLineIndex_;
}

void GridScrollLayoutAlgorithm::ScrollToIndexStart(LayoutWrapper* layoutWrapper, int32_t targetIndex)
{
    int32_t startLine = 0;
    /* targetIndex is in the matrix */
    if (IsIndexInMatrix(targetIndex, startLine)) {
        if (startLine == gridLayoutInfo_.startMainLineIndex_) {
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.currentOffset_ = 0;
            gridLayoutInfo_.ResetPositionFlags();
            return;
        }

        gridLayoutInfo_.startMainLineIndex_ = startLine;
        gridLayoutInfo_.UpdateStartIndexByStartLine();
        gridLayoutInfo_.prevOffset_ = 0;
        gridLayoutInfo_.currentOffset_ = 0;
        gridLayoutInfo_.ResetPositionFlags();
        return;
    }
    /* targetIndex is out of the matrix */
    if (gridLayoutInfo_.gridMatrix_.empty()) {
        LOGW("no grid for jump to index:%{public}d", targetIndex);
        return;
    }
    bool isTargetBackward = true;
    if (targetIndex < gridLayoutInfo_.gridMatrix_.begin()->second.begin()->second) {
        isTargetBackward = false;
    } else if (targetIndex > gridLayoutInfo_.gridMatrix_.rbegin()->second.rbegin()->second) {
        isTargetBackward = true;
    } else {
        return;
    }
    auto grid = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(grid);
    grid->ChildrenUpdatedFrom(0);
    GetTargetIndexInfoWithBenchMark(layoutWrapper, isTargetBackward, targetIndex);
}

void GridScrollLayoutAlgorithm::UpdateCurrentOffsetForJumpTo(LayoutWrapper* layoutWrapper, float mainSize)
{
    int32_t startLine = 0;
    /* targetIndex is in the matrix */
    if (IsIndexInMatrix(gridLayoutInfo_.jumpIndex_, startLine)) {
        // scroll to end of the screen
        gridLayoutInfo_.currentOffset_ = mainSize - gridLayoutInfo_.lineHeightMap_[startLine];
        // scroll to center of the screen
        if (gridLayoutInfo_.scrollAlign_ == ScrollAlign::CENTER) {
            gridLayoutInfo_.currentOffset_ /= 2;
        }
        gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
        return;
    }
    /* targetIndex is out of the matrix */
    LOGW("can not find jumpIndex in Grid Matrix :%{public}d", gridLayoutInfo_.jumpIndex_);
}   

float GridScrollLayoutAlgorithm::MeasureRecordedItems(float mainSize, float crossSize, LayoutWrapper* layoutWrapper)
{
    currentMainLineIndex_ = gridLayoutInfo_.startMainLineIndex_ - 1;
    float mainLength = gridLayoutInfo_.currentOffset_;
    // already at start line, do not use offset for mainLength
    if (gridLayoutInfo_.startMainLineIndex_ == 0 && GreatNotEqual(mainLength, 0)) {
        mainLength = 0;
    }
    UseCurrentLines(mainSize, crossSize, layoutWrapper, mainLength);
    return mainLength;
}

bool GridScrollLayoutAlgorithm::UseCurrentLines(
    float mainSize, float crossSize, LayoutWrapper* layoutWrapper, float& mainLength)
{
    bool runOutOfRecord = false;
    // Measure grid items row by row
    int32_t tempEndIndex = -1;
    while (LessNotEqual(mainLength, mainSize)) {
        // If [gridMatrix_] does not contain record of line [currentMainLineIndex_], do [FillNewLineBackward]
        auto gridMatrixIter = gridLayoutInfo_.gridMatrix_.find(++currentMainLineIndex_);
        if ((gridMatrixIter == gridLayoutInfo_.gridMatrix_.end()) ||
            (gridLayoutInfo_.lineHeightMap_.find(currentMainLineIndex_) == gridLayoutInfo_.lineHeightMap_.end())) {
            runOutOfRecord = true;
            break;
        }
        int32_t currentIndex = -1;
        bool hasNormalItem = false;
        cellAveLength_ = -1.0f;
        for (const auto& gridItemRecord : gridMatrixIter->second) {
            if (currentIndex == gridItemRecord.second) {
                continue;
            }
            currentIndex = gridItemRecord.second;
            if (currentIndex == -1) {
                // move from another grid
                continue;
            }
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
            if (!itemWrapper) {
                LOGE("GridItem wrapper of index %{public}u null", currentIndex);
                break;
            }
            auto frameSize = axis_ == Axis::VERTICAL ? SizeF(crossSize, mainSize) : SizeF(mainSize, crossSize);
            AdjustRowColSpan(itemWrapper);
            auto crossStart = axis_ == Axis::VERTICAL ? currentItemColStart_ : currentItemRowStart_;
            if (crossStart == -1) {
                MeasureChildPlaced(frameSize, currentIndex, gridItemRecord.first, layoutWrapper, itemWrapper);
            } else {
                MeasureChildPlaced(frameSize, currentIndex, crossStart, layoutWrapper, itemWrapper);
            }
            // Record end index. When fill new line, the [endIndex_] will be the first item index to request
            LargeItemLineHeight(itemWrapper, hasNormalItem);
            tempEndIndex = std::max(currentIndex, tempEndIndex);
            gridLayoutInfo_.endIndex_ = tempEndIndex;
        }

        if (GreatOrEqual(cellAveLength_, 0.0)) { // Means at least one item has been measured
            gridLayoutInfo_.lineHeightMap_[currentMainLineIndex_] = cellAveLength_;
            mainLength += (cellAveLength_ + mainGap_);
        }
        // If a line moves up out of viewport, update [startIndex_], [currentOffset_] and [startMainLineIndex_]
        if (LessNotEqual(mainLength, 0.0)) {
            gridLayoutInfo_.currentOffset_ = mainLength;
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.startMainLineIndex_ = currentMainLineIndex_ + 1;
            gridLayoutInfo_.UpdateStartIndexByStartLine();
        }
    }
    // Case 1. if this while-loop breaks due to running out of records, the [currentMainLineIndex_] is larger by 1 than
    // real main line index, so reduce 1.
    // Case 2. if this while-loop stops due to false result of [LessNotEqual(mainLength, mainSize)], the
    // [currentMainLineIndex_] is exactly the real main line index. Update [endMainLineIndex_] when the recorded items
    // are done measured.
    gridLayoutInfo_.endMainLineIndex_ = runOutOfRecord ? --currentMainLineIndex_ : currentMainLineIndex_;
    // reset reachEnd_ if any line at bottom is out of viewport
    // last line make LessNotEqual(mainLength, mainSize) and continue is reach end too
    gridLayoutInfo_.reachEnd_ = gridLayoutInfo_.endIndex_ == layoutWrapper->GetTotalChildCount() - 1;
    return runOutOfRecord;
}

void GridScrollLayoutAlgorithm::SkipForwardLines(float mainSize, LayoutWrapper* layoutWrapper)
{
    if (!GreatOrEqual(gridLayoutInfo_.currentOffset_ - gridLayoutInfo_.prevOffset_, mainSize)) {
        return;
    }

    // skip lines in matrix
    while (GreatOrEqual(gridLayoutInfo_.currentOffset_, mainSize)) {
        auto line = gridLayoutInfo_.gridMatrix_.find(gridLayoutInfo_.startMainLineIndex_ - 1);
        if (line == gridLayoutInfo_.gridMatrix_.end()) {
            break;
        }
        auto lineHeight = gridLayoutInfo_.lineHeightMap_.find(gridLayoutInfo_.startMainLineIndex_ - 1);
        if (lineHeight == gridLayoutInfo_.lineHeightMap_.end()) {
            break;
        }
        gridLayoutInfo_.startMainLineIndex_--;
        gridLayoutInfo_.startIndex_ = line->second.begin()->second;
        gridLayoutInfo_.currentOffset_ -= lineHeight->second;
    }

    // skip lines not in matrix
    if (GreatOrEqual(gridLayoutInfo_.currentOffset_, mainSize) && gridLayoutInfo_.startIndex_ > 0) {
        auto grid = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(grid);
        auto pattern = grid->GetPattern<GridPattern>();
        CHECK_NULL_VOID(pattern);
        auto estimatedHeight = pattern->GetScrollableDistance();
        // no scroller
        if (LessOrEqual(estimatedHeight, 0)) {
            return;
        }
        auto averageHeight = estimatedHeight / gridLayoutInfo_.childrenCount_;
        int32_t estimatedIndex = (gridLayoutInfo_.currentOffset_) / averageHeight;
        gridLayoutInfo_.startIndex_ = std::max(gridLayoutInfo_.startIndex_ - estimatedIndex, 0);
        gridLayoutInfo_.currentOffset_ = gridLayoutInfo_.prevOffset_;
        LOGI("estimatedIndex:%{public}d", gridLayoutInfo_.startIndex_);
        grid->ChildrenUpdatedFrom(0);
    }
}

void GridScrollLayoutAlgorithm::SkipBackwardLines(float mainSize, LayoutWrapper* layoutWrapper)
{
    if (!GreatOrEqual(gridLayoutInfo_.prevOffset_ - gridLayoutInfo_.currentOffset_, mainSize)) {
        return;
    }

    // grid size change from big to small
    gridLayoutInfo_.UpdateEndLine(mainSize, mainGap_);

    // skip lines in matrix
    while (GreatOrEqual(-gridLayoutInfo_.currentOffset_, mainSize)) {
        auto line = gridLayoutInfo_.gridMatrix_.find(gridLayoutInfo_.endMainLineIndex_ + 1);
        if (line == gridLayoutInfo_.gridMatrix_.end()) {
            break;
        }
        auto lineHeight = gridLayoutInfo_.lineHeightMap_.find(gridLayoutInfo_.endMainLineIndex_ + 1);
        if (lineHeight == gridLayoutInfo_.lineHeightMap_.end()) {
            break;
        }
        gridLayoutInfo_.startMainLineIndex_++;
        gridLayoutInfo_.endMainLineIndex_++;
        gridLayoutInfo_.currentOffset_ += lineHeight->second;
    }
    gridLayoutInfo_.UpdateStartIndexByStartLine();

    // skip lines not in matrix
    if (GreatOrEqual(-gridLayoutInfo_.currentOffset_, mainSize)) {
        auto grid = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(grid);
        auto pattern = grid->GetPattern<GridPattern>();
        CHECK_NULL_VOID(pattern);
        auto estimatedHeight = pattern->GetScrollableDistance();
        // no scroller
        if (LessOrEqual(estimatedHeight, 0)) {
            return;
        }
        auto averageHeight = estimatedHeight / gridLayoutInfo_.childrenCount_;
        int32_t estimatedIndex = (gridLayoutInfo_.currentOffset_) / averageHeight;
        gridLayoutInfo_.startIndex_ =
            std::min(gridLayoutInfo_.startIndex_ - estimatedIndex, gridLayoutInfo_.childrenCount_);
        gridLayoutInfo_.currentOffset_ = gridLayoutInfo_.prevOffset_;
        LOGI("estimatedIndex:%{public}d, currentOffset_:%{public}f", gridLayoutInfo_.startIndex_,
            gridLayoutInfo_.currentOffset_);
        grid->ChildrenUpdatedFrom(0);
    }
}

float GridScrollLayoutAlgorithm::FillNewLineForward(float crossSize, float mainSize, LayoutWrapper* layoutWrapper)
{
    // To make the code more convenient to read, we name a param in situation of vertical, for example:
    // 1. [lineHight] means height of a row when the Grid is vertical;
    // 2. [lineHight] means width of a column when the Grid is horizontal;
    // Other params are also named according to this principle.
    cellAveLength_ = -1.0f;
    auto currentIndex = gridLayoutInfo_.startIndex_;
    bool hasNormalItem = false;
    // TODO: shoule we use policy of adaptive layout according to size of [GridItem] ?
    if (gridLayoutInfo_.startMainLineIndex_ - 1 < 0) {
        if (currentIndex == 0) {
            LOGI("startMainLineIndex: %{public}d is already the first line, no forward line to make",
                gridLayoutInfo_.startMainLineIndex_);
            return cellAveLength_;
        }
        // add more than one line
        UpdateMatrixForAddedItems();
    }
    gridLayoutInfo_.startMainLineIndex_--;
    bool doneCreateNewLine = false;
    auto gridMatrixIter = gridLayoutInfo_.gridMatrix_.find(gridLayoutInfo_.startMainLineIndex_);
    if (gridMatrixIter == gridLayoutInfo_.gridMatrix_.end()) {
        AddForwardLines(currentIndex, crossSize, mainSize, layoutWrapper);
    }
    gridMatrixIter = gridLayoutInfo_.gridMatrix_.find(gridLayoutInfo_.startMainLineIndex_);
    if (gridMatrixIter == gridLayoutInfo_.gridMatrix_.end()) {
        return cellAveLength_;
    }

    // need to obtain the item node in order and by step one in LazyLayoutWrapperBuilder::OnGetOrCreateWrapperByIndex
    for (auto itemIter = gridMatrixIter->second.rbegin(); itemIter != gridMatrixIter->second.rend(); ++itemIter) {
        currentIndex = itemIter->second;

        // Step1. Get wrapper of [GridItem]
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
        if (!itemWrapper) {
            LOGE("GridItem wrapper of index %{public}u null", currentIndex);
            break;
        }
        // Step2. Measure child
        // TODO: need to use [isScrollable_]
        auto frameSize = axis_ == Axis::VERTICAL ? SizeF(crossSize, mainSize) : SizeF(mainSize, crossSize);
        AdjustRowColSpan(itemWrapper);
        auto crossStart = axis_ == Axis::VERTICAL ? currentItemColStart_ : currentItemRowStart_;
        if (crossStart == -1) {
            MeasureChildPlaced(frameSize, currentIndex, itemIter->first, layoutWrapper, itemWrapper);
        } else {
            MeasureChildPlaced(frameSize, currentIndex, crossStart, layoutWrapper, itemWrapper);
        }
        // Step3. Measure [GridItem]
        LargeItemLineHeight(itemWrapper, hasNormalItem);
        gridLayoutInfo_.startIndex_ = currentIndex;
    }

    doneCreateNewLine = GreatOrEqual(cellAveLength_, 0.0);
    // If it fails to create new line when [FillNewLineForward] is called, it means that it reaches start
    gridLayoutInfo_.reachStart_ = !doneCreateNewLine;

    return cellAveLength_;
}

void GridScrollLayoutAlgorithm::UpdateMatrixForAddedItems()
{
    decltype(gridLayoutInfo_.lineHeightMap_) gridLineHeightMap(std::move(gridLayoutInfo_.lineHeightMap_));
    decltype(gridLayoutInfo_.gridMatrix_) gridMatrix(std::move(gridLayoutInfo_.gridMatrix_));
    for (const auto& item : gridMatrix) {
        gridLayoutInfo_.gridMatrix_[item.first + 1] = item.second;
    }
    for (const auto& item : gridLineHeightMap) {
        gridLayoutInfo_.lineHeightMap_[item.first + 1] = item.second;
    }
    gridLayoutInfo_.startMainLineIndex_ = gridLayoutInfo_.startMainLineIndex_ + 1;
    gridLayoutInfo_.endMainLineIndex_ = gridLayoutInfo_.endMainLineIndex_ + 1;
    LOGI("add more than one line startMainLineIndex_:%{public}d", gridLayoutInfo_.startMainLineIndex_);
}

void GridScrollLayoutAlgorithm::AddForwardLines(
    int32_t currentIndex, float crossSize, float mainSize, LayoutWrapper* layoutWrapper)
{
    auto endMainLineIndex = gridLayoutInfo_.endMainLineIndex_;
    auto endIndex = gridLayoutInfo_.endIndex_;
    auto firstItem = GetStartingItem(layoutWrapper, currentIndex - 1);
    auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(firstItem);
    AdjustRowColSpan(itemWrapper);
    auto mainSpan = axis_ == Axis::VERTICAL ? currentItemRowSpan_ : currentItemColSpan_;
    auto measureNumber = 0;
    currentMainLineIndex_ = (firstItem == 0 ? 0 : gridLayoutInfo_.startMainLineIndex_) - 1;
    gridLayoutInfo_.endIndex_ = firstItem - 1;
    // firstItem may be more than one line ahead, use new matrix to save and merge to old matrix
    decltype(gridLayoutInfo_.lineHeightMap_) gridLineHeightMap(std::move(gridLayoutInfo_.lineHeightMap_));
    decltype(gridLayoutInfo_.gridMatrix_) gridMatrix(std::move(gridLayoutInfo_.gridMatrix_));
    bool addLine = false;
    while (gridLayoutInfo_.endIndex_ < currentIndex - 1 || mainSpan > measureNumber) {
        auto newLineHeight = FillNewLineBackward(crossSize, mainSize, layoutWrapper, true);
        measureNumber++;
        if (LessNotEqual(newLineHeight, 0.0)) {
            gridLayoutInfo_.reachEnd_ = true;
            break;
        }
        addLine = true;
    }
    if (!addLine) {
        return;
    }
    // merge matrix
    auto forwardLines = gridLayoutInfo_.endMainLineIndex_ - gridLayoutInfo_.startMainLineIndex_;
    if (forwardLines >= 0) {
        auto begin = gridLayoutInfo_.gridMatrix_.begin()->first;
        if (gridLayoutInfo_.endMainLineIndex_ - begin <= begin) {
            for (auto i = begin; i <= gridLayoutInfo_.endMainLineIndex_; i++) {
                gridMatrix.emplace(i - forwardLines, std::move(gridLayoutInfo_.gridMatrix_[i]));
                gridLineHeightMap.emplace(i - forwardLines, gridLayoutInfo_.lineHeightMap_[i]);
            }
            gridMatrix.swap(gridLayoutInfo_.gridMatrix_);
            gridLineHeightMap.swap(gridLayoutInfo_.lineHeightMap_);
        } else {
            for (auto i = gridLayoutInfo_.startMainLineIndex_ + 1; i <= gridMatrix.rbegin()->first; i++) {
                gridLayoutInfo_.gridMatrix_.emplace(forwardLines + i, std::move(gridMatrix[i]));
                gridLayoutInfo_.lineHeightMap_.emplace(forwardLines + i, gridLineHeightMap[i]);
            }
        }
    } else {
        // delete more than one line items
        for (auto i = gridLayoutInfo_.startMainLineIndex_ + 1; i <= gridMatrix.rbegin()->first; i++) {
            gridLayoutInfo_.gridMatrix_.emplace(forwardLines + i, std::move(gridMatrix[i]));
            gridLayoutInfo_.lineHeightMap_.emplace(forwardLines + i, gridLineHeightMap[i]);
        }
    }

    gridLayoutInfo_.startMainLineIndex_ = gridLayoutInfo_.endMainLineIndex_ - (forwardLines > 0 ? forwardLines : 0);
    gridLayoutInfo_.endMainLineIndex_ = endMainLineIndex + (forwardLines < 0 ? forwardLines : 0);
    gridLayoutInfo_.endIndex_ = endIndex;
    LOGI("after load forward:start main line %{public}d end main line %{public}d", gridLayoutInfo_.startMainLineIndex_,
        gridLayoutInfo_.endMainLineIndex_);
}

float GridScrollLayoutAlgorithm::FillNewLineBackward(
    float crossSize, float mainSize, LayoutWrapper* layoutWrapper, bool reverse)
{
    // To make the code more convenient to read, we name a param in situation of vertical, for example:
    // 1. [lineHight] means height of a row when the Grid is vertical;
    // 2. [lineHight] means width of a column when the Grid is horizontal;
    // Other params are also named according to this principle.
    cellAveLength_ = -1.0f;
    if (moveToEndLineIndex_ > 0 && gridLayoutInfo_.endIndex_ >= moveToEndLineIndex_) {
        LOGI("scroll to end line with index:%{public}d", moveToEndLineIndex_);
        return cellAveLength_;
    }
    auto currentIndex = gridLayoutInfo_.endIndex_ + 1;
    currentMainLineIndex_++; // if it fails to fill a new line backward, do [currentMainLineIndex_--]
    lastCross_ = 0;
    bool hasNormalItem = false;
    // TODO: shoule we use policy of adaptive layout according to size of [GridItem] ?

    for (uint32_t i = 0; i < crossCount_; i++) {
        // already finish first line forward
        if (reverse && currentIndex >= gridLayoutInfo_.startIndex_) {
            break;
        }
        // Step1. Get wrapper of [GridItem]
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
        if (!itemWrapper) {
            LOGE("GridItem wrapper of index %{public}u null", currentIndex);
            LargeItemNextLineHeight(currentMainLineIndex_, layoutWrapper);
            break;
        }
        // Step2. Measure child
        auto frameSize = axis_ == Axis::VERTICAL ? SizeF(crossSize, mainSize) : SizeF(mainSize, crossSize);
        auto crossSpan = MeasureNewChild(frameSize, currentIndex, layoutWrapper, itemWrapper, false);
        if (crossSpan < 0) {
            cellAveLength_ = LessNotEqual(cellAveLength_, 0.0)
                                 ? gridLayoutInfo_.lineHeightMap_.find(currentMainLineIndex_ - 1)->second
                                 : cellAveLength_;
            --currentIndex;
            break;
        }
        i = lastCross_ - 1;
        // Step3. Measure [GridItem]
        LargeItemLineHeight(itemWrapper, hasNormalItem);

        gridLayoutInfo_.endIndex_ = currentIndex;
        currentIndex++;
    }

    gridLayoutInfo_.lineHeightMap_[currentMainLineIndex_] = cellAveLength_;
    gridLayoutInfo_.endMainLineIndex_ = currentMainLineIndex_;
    return cellAveLength_;
}

void GridScrollLayoutAlgorithm::LargeItemNextLineHeight(int32_t currentLineIndex, LayoutWrapper* layoutWrapper)
{
    auto gridMatrixIter = gridLayoutInfo_.gridMatrix_.find(currentLineIndex);
    bool hasNormalItem = false;
    auto currentIndex = 0;
    if (gridMatrixIter != gridLayoutInfo_.gridMatrix_.end()) {
        for (auto itemIter = gridMatrixIter->second.rbegin(); itemIter != gridMatrixIter->second.rend(); ++itemIter) {
            currentIndex = itemIter->second;
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
            if (!itemWrapper) {
                break;
            }
            LargeItemLineHeight(itemWrapper, hasNormalItem);
        }
    }
}

void GridScrollLayoutAlgorithm::LargeItemForwardLineHeight(int32_t currentLineIndex, LayoutWrapper* layoutWrapper)
{
    auto lineIndex = currentLineIndex;
    auto gridMatrixIter = gridLayoutInfo_.gridMatrix_.find(lineIndex);
    if (gridMatrixIter == gridLayoutInfo_.gridMatrix_.end()) {
        return;
    }
    auto currentIndex = -1;

    lineIndex = CalculateLineIndexForLargeItem(gridMatrixIter, currentIndex, lineIndex, layoutWrapper);
    CalculateLineHeightForLargeItem(lineIndex, currentLineIndex, gridMatrixIter, layoutWrapper);
}

int32_t GridScrollLayoutAlgorithm::CalculateLineIndexForLargeItem(
    std::map<int32_t, std::map<int32_t, int32_t>>::iterator gridMatrixIter, int32_t currentIndex, int32_t lineIndex,
    LayoutWrapper* layoutWrapper)
{
    for (const auto& gridItemRecord : gridMatrixIter->second) {
        if (currentIndex == gridItemRecord.second || gridItemRecord.second == -1) {
            continue;
        }
        currentIndex = gridItemRecord.second;
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
        if (!itemWrapper) {
            break;
        }
        AdjustRowColSpan(itemWrapper);
        for (int32_t lastCrossIndex = lineIndex - 1; lastCrossIndex >= 0; lastCrossIndex--) {
            auto lastGridMatrixIter = gridLayoutInfo_.gridMatrix_.find(lastCrossIndex);
            if (lastGridMatrixIter == gridLayoutInfo_.gridMatrix_.end()) {
                continue;
            }
            auto lastGridItemRecord = lastGridMatrixIter->second;
            auto lastLineCrossItem = lastGridItemRecord.find(gridItemRecord.first);
            if (lastLineCrossItem == lastGridItemRecord.end()) {
                continue;
            }
            if (lastLineCrossItem->second == currentIndex) {
                lineIndex--;
            } else {
                break;
            }
        }
    }
    return lineIndex;
}

void GridScrollLayoutAlgorithm::CalculateLineHeightForLargeItem(int32_t lineIndex, int32_t currentLineIndex,
    std::map<int32_t, std::map<int32_t, int32_t>>::iterator gridMatrixIter, LayoutWrapper* layoutWrapper)
{
    for (int32_t i = lineIndex; i <= currentLineIndex; i++) {
        auto currentGridMatrixIter = gridLayoutInfo_.gridMatrix_.find(i);
        if (currentGridMatrixIter == gridLayoutInfo_.gridMatrix_.end()) {
            continue;
        }
        bool hasNormalItem = false;
        auto currentIndex = 0;
        cellAveLength_ = -1.0f;
        for (auto itemIter = gridMatrixIter->second.rbegin(); itemIter != gridMatrixIter->second.rend(); ++itemIter) {
            if (currentIndex == itemIter->second) {
                continue;
            }
            currentIndex = itemIter->second;
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
            if (!itemWrapper) {
                break;
            }
            LargeItemLineHeight(itemWrapper, hasNormalItem);
            gridLayoutInfo_.lineHeightMap_[i] = cellAveLength_;
        }
    }
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
    if (axis_ == Axis::VERTICAL) {
        itemConstraint.percentReference = SizeF(widthPercentBase, itemConstraint.percentReference.Height());
    } else {
        itemConstraint.percentReference = SizeF(itemConstraint.percentReference.Width(), heightPercentBase);
    }
    itemConstraint.maxSize = itemIdealSize;
    itemConstraint.UpdateIllegalSelfMarginSizeWithCheck(axis_ == Axis::VERTICAL
                                                            ? OptionalSizeF(itemCrossSize, std::nullopt)
                                                            : OptionalSizeF(std::nullopt, itemCrossSize));
    return itemConstraint;
}

bool GridScrollLayoutAlgorithm::GetNextGrid(int32_t& curMain, int32_t& curCross, bool reverse) const
{
    if (!reverse) {
        ++curCross;
        if (curCross >= static_cast<int32_t>(crossCount_)) {
            return false;
        }
        return true;
    }

    --curCross;
    if (curCross < 0) {
        return false;
    }
    return true;
}

int32_t GridScrollLayoutAlgorithm::MeasureNewChild(const SizeF& frameSize, int32_t itemIndex,
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& childLayoutWrapper, bool reverse)
{
    auto mainCount = static_cast<int32_t>(mainCount_);
    auto crossCount = static_cast<int32_t>(crossCount_);
    AdjustRowColSpan(childLayoutWrapper);
    auto mainSpan = axis_ == Axis::VERTICAL ? currentItemRowSpan_ : currentItemColSpan_;
    auto crossSpan = axis_ == Axis::VERTICAL ? currentItemColSpan_ : currentItemRowSpan_;
    auto crossStart = axis_ == Axis::VERTICAL ? currentItemColStart_ : currentItemRowStart_;
    if (crossSpan > crossCount) {
        LOGW("item %{public}d can not be placed in grid: cross count:%{public}d, cross span:%{public}d", itemIndex,
            crossCount, crossSpan);
        return crossSpan;
    }
    int32_t mainIndex = currentMainLineIndex_;

    if (crossStart >= 0 && crossStart < crossCount) {
        if (crossStart < lastCross_) {
            return -1;
        } else if (CheckGridPlaced(itemIndex, mainIndex, crossStart, mainSpan, crossSpan)) {
            MeasureChild(layoutWrapper, frameSize, childLayoutWrapper, crossStart, crossSpan);
            itemsCrossPosition_.try_emplace(itemIndex, ComputeItemCrossPosition(layoutWrapper, crossStart));
        } else {
            return -1;
        }
    } else {
        int32_t crossIndex = crossStart >= 0 ? crossStart : lastCross_;

        while (!CheckGridPlaced(itemIndex, mainIndex, crossIndex, mainSpan, crossSpan)) {
            if (GetNextGrid(mainIndex, crossIndex, reverse) == false) {
                return -1;
            }
            if (mainIndex >= mainCount || crossIndex >= crossCount) {
                break;
            }
        }

        MeasureChild(layoutWrapper, frameSize, childLayoutWrapper, crossIndex, crossSpan);
        itemsCrossPosition_.try_emplace(itemIndex, ComputeItemCrossPosition(layoutWrapper, crossIndex));
    }
    return crossSpan;
}

int32_t GridScrollLayoutAlgorithm::MeasureChildPlaced(const SizeF& frameSize, int32_t itemIndex, int32_t crossStart,
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& childLayoutWrapper)
{
    AdjustRowColSpan(childLayoutWrapper);
    auto crossSpan = axis_ == Axis::VERTICAL ? currentItemColSpan_ : currentItemRowSpan_;
    if (static_cast<uint32_t>(crossStart + crossSpan) > crossCount_) {
        LOGI("item %{public}d cross not enough, start:%{public}d, span:%{public}d", itemIndex, crossStart, crossSpan);
        return 0;
    }

    MeasureChild(layoutWrapper, frameSize, childLayoutWrapper, crossStart, crossSpan);
    itemsCrossPosition_.try_emplace(itemIndex, ComputeItemCrossPosition(layoutWrapper, crossStart));
    return crossSpan;
}

void GridScrollLayoutAlgorithm::MeasureChild(LayoutWrapper* layoutWrapper, const SizeF& frameSize,
    const RefPtr<LayoutWrapper>& childLayoutWrapper, int32_t crossStart, int32_t crossSpan)
{
    auto gridLayoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto mainSize = GetMainAxisSize(frameSize, gridLayoutInfo_.axis_);
    auto crossSize = GetCrossAxisSize(frameSize, gridLayoutInfo_.axis_);
    childLayoutWrapper->Measure(CreateChildConstraint(mainSize, crossSize, gridLayoutProperty, crossStart, crossSpan));
}

bool GridScrollLayoutAlgorithm::CheckGridPlaced(
    int32_t index, int32_t main, int32_t cross, int32_t mainSpan, int32_t crossSpan)
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
    lastCross_ = cross + crossSpan;

    return true;
}

float GridScrollLayoutAlgorithm::ComputeItemCrossPosition(LayoutWrapper* layoutWrapper, int32_t crossStart) const
{
    float position = 0.0f;
    for (int32_t index = 0; index < crossStart; ++index) {
        if (index >= 0 && index < static_cast<int32_t>(itemsCrossSize_.size())) {
            position += itemsCrossSize_.at(index);
        }
    }
    position += crossStart * crossGap_ + crossPaddingOffset_;
    return position;
}

int32_t GridScrollLayoutAlgorithm::GetStartingItem(LayoutWrapper* layoutWrapper, int32_t currentIndex)
{
    int32_t firstIndex = 0;
    currentIndex =
        currentIndex < layoutWrapper->GetTotalChildCount() ? currentIndex : layoutWrapper->GetTotalChildCount() - 1;
    auto index = currentIndex;
    if (gridLayoutInfo_.hasBigItem_) {
        while (index > 0) {
            auto childLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
            if (!childLayoutWrapper) {
                LOGE("GridItem wrapper of index %{public}u null", index);
                break;
            }
            auto childLayoutProperty = DynamicCast<GridItemLayoutProperty>(childLayoutWrapper->GetLayoutProperty());
            CHECK_NULL_RETURN(childLayoutProperty, 0);
            auto crossIndex = childLayoutProperty->GetCustomCrossIndex(axis_);
            if (crossIndex == 0) {
                firstIndex = index;
                break;
            }
            --index;
        }
    } else {
        while (index > 0) {
            // need to obtain the item node in order and by step one
            auto childLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
            if (!childLayoutWrapper) {
                LOGE("GridItem wrapper of index %{public}u null", index);
                break;
            }
            auto childLayoutProperty = DynamicCast<GridItemLayoutProperty>(childLayoutWrapper->GetLayoutProperty());
            CHECK_NULL_RETURN(childLayoutProperty, 0);
            auto crossIndex = childLayoutProperty->GetCustomCrossIndex(axis_);
            // Grid may change from no big item to has big item
            if (crossIndex >= 0) {
                gridLayoutInfo_.hasBigItem_ = true;
                return GetStartingItem(layoutWrapper, currentIndex);
            }
            if (index % gridLayoutInfo_.crossCount_ == 0) {
                firstIndex = index;
                break;
            }
            --index;
        }
    }
    return firstIndex;
}

// only for debug use
void GridScrollLayoutAlgorithm::PrintGridMatrix(
    const std::map<int32_t, std::map<int32_t, int32_t>>& gridMatrix, const std::map<int32_t, float>& positions)
{
    for (const auto& record : gridMatrix) {
        for (const auto& item : record.second) {
            float position = -1;
            auto iter = positions.find(item.second);
            if (iter != positions.end()) {
                position = iter->second;
            }
            LOGI("grid matrix -- line: %{public}d, item: %{public}d, fr: %{public}d, position: %{public}f",
                record.first, item.first, item.second, position);
        }
    }
}

// only for debug use
void GridScrollLayoutAlgorithm::PrintLineHeightMap(const std::map<int32_t, float>& lineHeightMap)
{
    for (const auto& record : lineHeightMap) {
        LOGI("line height -- line: %{public}d, lineHeight: %{public}f", record.first, record.second);
    }
}

} // namespace OHOS::Ace::NG
