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

#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"

#include "base/log/log_wrapper.h"
#include "base/log/event_report.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
namespace {
void AddCacheItemsInFront(
    int32_t startIdx, LayoutWrapper* host, int32_t cacheCnt, std::list<GridPreloadItem>& buildList)
{
    for (int32_t i = 1; i <= cacheCnt; ++i) {
        int32_t item = startIdx - i;
        if (item < 0) {
            break;
        }
        if (!host->GetChildByIndex(item, true)) {
            buildList.emplace_back(item, true);
        }
    }
}
} // namespace

void GridScrollLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    wrapper_ = layoutWrapper;
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);

    // Pre-recycle
    ScrollableUtils::RecycleItemsOutOfBoundary(
        info_.axis_, info_.currentOffset_ - info_.prevOffset_, info_.startIndex_, info_.endIndex_, layoutWrapper);

    // Step1: Decide size of Grid
    Axis axis = info_.axis_;
    frameSize_ = CreateIdealSize(
        gridLayoutProperty->GetLayoutConstraint().value(), axis, gridLayoutProperty->GetMeasureType(), true);
    if (NearZero(GetMainAxisSize(frameSize_, axis))) {
        TAG_LOGW(AceLogTag::ACE_GRID, "size of main axis value is 0, please check");
        return;
    }
    bool matchChildren = GreaterOrEqualToInfinity(GetMainAxisSize(frameSize_, axis));
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize_);
    MinusPaddingToSize(gridLayoutProperty->CreatePaddingAndBorder(), frameSize_);
    info_.contentEndPadding_ = ScrollableUtils::CheckHeightExpansion(gridLayoutProperty, axis);
    frameSize_.AddHeight(info_.contentEndPadding_);
    auto&& safeAreaOpts = gridLayoutProperty->GetSafeAreaExpandOpts();
    expandSafeArea_ = safeAreaOpts && safeAreaOpts->Expansive();
    auto host = layoutWrapper->GetHostNode();
    if (host) {
        auto pipeline = host->GetContext();
        if (pipeline && pipeline->GetPixelRoundMode() == PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE) {
            frameSize_.SetWidth(round(frameSize_.Width()));
            frameSize_.SetHeight(round(frameSize_.Height()));
        }
    }

    InitialItemsCrossSize(gridLayoutProperty, frameSize_, info_.GetChildrenCount());

    // Step2: Measure children that can be displayed in viewport of Grid
    float mainSize = GetMainAxisSize(frameSize_, axis);
    float crossSize = GetCrossAxisSize(frameSize_, axis);
    if (!NearEqual(mainSize, info_.lastMainSize_)) {
        UpdateOffsetOnVirtualKeyboardHeightChange(layoutWrapper, mainSize);
        UpdateOffsetOnHeightChangeDuringAnimation(layoutWrapper, mainSize);
        info_.ResetPositionFlags();
    }
    FillGridViewportAndMeasureChildren(mainSize, crossSize, layoutWrapper);

    if (gridLayoutProperty->GetAlignItems().value_or(GridItemAlignment::DEFAULT) == GridItemAlignment::STRETCH) {
        GridLayoutBaseAlgorithm::AdjustChildrenHeight(layoutWrapper);
    }

    // update cache info.
    const int32_t cacheCnt =
        static_cast<int32_t>(gridLayoutProperty->GetCachedCountValue(info_.defCachedCount_) * crossCount_);
    layoutWrapper->SetCacheCount(cacheCnt);

    info_.lastMainSize_ = mainSize;
    info_.lastCrossSize_ = crossSize;
    AdaptToChildMainSize(layoutWrapper, gridLayoutProperty, mainSize, frameSize_, matchChildren);

    // reset offsetEnd after scroll to moveToEndLineIndex_
    info_.offsetEnd_ = moveToEndLineIndex_ > 0 ? (info_.endIndex_ + 1 >= info_.GetChildrenCount()) : info_.offsetEnd_;

    if (SystemProperties::GetGridCacheEnabled()) {
        const bool sync = gridLayoutProperty->GetShowCachedItemsValue(false);
        if (sync) {
            SyncPreload(
                layoutWrapper, gridLayoutProperty->GetCachedCountValue(info_.defCachedCount_), crossSize, mainSize);
            return;
        }

        FillCacheLineAtEnd(mainSize, crossSize, layoutWrapper);
        AddCacheItemsInFront(info_.startIndex_, layoutWrapper, cacheCnt, predictBuildList_);
        if (!predictBuildList_.empty()) {
            PreloadItems(layoutWrapper);
            predictBuildList_.clear();
        }
    }
}

void GridScrollLayoutAlgorithm::PreloadItems(LayoutWrapper* layoutWrapper)
{
    GridLayoutUtils::PreloadGridItems(layoutWrapper->GetHostNode()->GetPattern<GridPattern>(),
        std::move(predictBuildList_),
        [param = GridPredictLayoutParam { cachedChildConstraint_, itemsCrossSize_, crossGap_ }](
            const RefPtr<FrameNode>& host, int32_t itemIdx) {
            CHECK_NULL_RETURN(host, false);
            return PredictBuildItem(*host, itemIdx, param);
        });
}

void GridScrollLayoutAlgorithm::UpdateOffsetOnVirtualKeyboardHeightChange(LayoutWrapper* layoutWrapper, float mainSize)
{
    if (GreatOrEqual(mainSize, info_.lastMainSize_)) {
        return;
    }
    // only need to offset vertical grid
    if (info_.axis_ != Axis::VERTICAL) {
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

    auto context = grid->GetContext();
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
        auto lineHeight = info_.GetAverageLineHeight();
        if (GreatNotEqual(lineHeight, 0)) {
            offset = floor(offset / lineHeight) * lineHeight;
        }
        info_.currentOffset_ += offset;
        TAG_LOGI(AceLogTag::ACE_GRID, "update offset on virtual keyboard height change, %{public}f", offset);
    }
}

void GridScrollLayoutAlgorithm::AdaptToChildMainSize(LayoutWrapper* layoutWrapper,
    RefPtr<GridLayoutProperty>& gridLayoutProperty, float mainSize, SizeF idealSize, bool matchChildren)
{
    if (!matchChildren) {
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

        if (mainAxisIdealSize.has_value()) {
            return;
        }
    }

    auto lengthOfItemsInViewport = info_.GetTotalHeightOfItemsInView(mainGap_);
    auto gridMainSize = std::min(lengthOfItemsInViewport, mainSize);
    gridMainSize = std::max(gridMainSize, GetMainAxisSize(gridLayoutProperty->GetLayoutConstraint()->minSize, axis_));
    idealSize.SetMainSize(gridMainSize, axis_);
    AddPaddingToSize(gridLayoutProperty->CreatePaddingAndBorder(), idealSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    info_.lastMainSize_ = gridMainSize;
    TAG_LOGI(AceLogTag::ACE_GRID, "gridMainSize:%{public}f", gridMainSize);
}

void GridScrollLayoutAlgorithm::UpdateOffsetOnHeightChangeDuringAnimation(LayoutWrapper* layoutWrapper, float mainSize)
{
    // If only the height of the Grid is changed, keep the prevOffset_ and currentOffset_ equal.
    ResetOffsetWhenHeightChanged();
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->IsScrollableSpringMotionRunning()) {
        if (info_.reachStart_) {
            return;
        }
        float totalHeight = info_.GetContentHeight(mainGap_);
        if (info_.lastMainSize_ < totalHeight) {
            info_.currentOffset_ += (mainSize - info_.lastMainSize_);
            info_.endHeight_ -= (mainSize - info_.lastMainSize_);
            return;
        }
        if (info_.lastMainSize_ >= totalHeight && mainSize < info_.lastMainSize_ && mainSize <= totalHeight) {
            info_.currentOffset_ += mainSize - totalHeight;
            info_.endHeight_ -= mainSize - totalHeight;
        }
    }
}

void GridScrollLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto props = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    childFrameOffset_ = OffsetF(0.0f, padding.top.value_or(0.0f));
    childFrameOffset_ += OffsetF(0.0f, info_.currentOffset_, axis_);
    bool isRtl = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection() == TextDirection::RTL;
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    if (info_.hasMultiLineItem_) {
        layoutWrapper->RemoveAllChildInRenderTree();
    }
    LargeItemForwardLineHeight(info_.startMainLineIndex_, layoutWrapper);
    const int32_t cacheCount = props->GetCachedCountValue(info_.defCachedCount_);
    if (!props->HasCachedCount()) {
        info_.UpdateDefaultCachedCount();
    }
    int32_t cacheStart = 0;
    int32_t cacheEnd = 0; // number of cache items at tail
    const bool showCached = props->GetShowCachedItemsValue(false);

    const int32_t start = info_.startMainLineIndex_ - cacheCount;
    const int32_t end = info_.endMainLineIndex_ + cacheCount;
    float mainPos = -info_.GetHeightInRange(start, info_.startMainLineIndex_, mainGap_);
    for (auto i = start; i <= end; ++i) {
        const bool inRange = i >= info_.startMainLineIndex_ && i <= info_.endMainLineIndex_;
        const bool isCache = !showCached && !inRange;
        const auto& line = info_.gridMatrix_.find(i);
        if (line == info_.gridMatrix_.end()) {
            continue;
        }

        auto prevLineOffset = OffsetF(0.0f, mainPos, axis_);
        if (line->second.empty()) {
            TAG_LOGW(AceLogTag::ACE_GRID, "line %{public}d should not be empty, please check.", line->first);
            continue;
        }
        int32_t itemIdex = -1;
        float lineHeight = info_.lineHeightMap_[line->first];
        Alignment align = axis_ == Axis::VERTICAL ? Alignment::TOP_CENTER : Alignment::CENTER_LEFT;
        if (props->GetPositionProperty()) {
            align = props->GetPositionProperty()->GetAlignment().value_or(align);
        }
        for (auto iter = line->second.begin(); iter != line->second.end(); ++iter) {
            // If item index is the same, must be the same GridItem, need't layout again.
            if (itemIdex == iter->second) {
                continue;
            }
            itemIdex = iter->second;
            auto crossIter = itemsCrossPosition_.find(itemIdex);
            if (crossIter == itemsCrossPosition_.end()) {
                crossIter = itemsCrossPosition_.emplace(itemIdex, ComputeItemCrossPosition(iter->first)).first;
            }
            auto crossOffset = crossIter->second;
            auto offset = childFrameOffset_ + prevLineOffset;
            offset = CalculateLargeItemOffset(offset, itemIdex, i, iter->first);
            if (axis_ == Axis::VERTICAL) {
                offset.SetX(crossOffset);
            } else {
                offset.SetY(crossOffset);
            }
            auto wrapper = isCache ? layoutWrapper->GetChildByIndex(itemIdex, true)
                                   : layoutWrapper->GetOrCreateChildByIndex(itemIdex);
            if (!wrapper) {
                continue;
            }
            if (inRange) {
                startIndex = startIndex == -1 ? itemIdex : std::min(startIndex, itemIdex);
                endIndex = std::max(itemIdex, endIndex);
            }
            auto frSize = itemsCrossSize_.find(iter->first);
            if (frSize == itemsCrossSize_.end()) {
                continue;
            }
            if (i < info_.startMainLineIndex_) {
                ++cacheStart;
            } else if (i > info_.endMainLineIndex_) {
                ++cacheEnd;
            }
            SizeF blockSize = SizeF(frSize->second, lineHeight, axis_);
            auto translate = OffsetF(0.0f, 0.0f);
            auto childSize = wrapper->GetGeometryNode()->GetMarginFrameSize();
            translate = Alignment::GetAlignPosition(blockSize, childSize, align);

            if (isRtl) {
                offset.SetX(size.Width() - offset.GetX() - childSize.Width());
            }
            offset += OffsetF(padding.left.value_or(0.0f), 0.0f);
            wrapper->GetGeometryNode()->SetMarginFrameOffset(offset + translate);
            const bool forceLayout =
                info_.hasMultiLineItem_ || expandSafeArea_ || wrapper->CheckNeedForceMeasureAndLayout();
            if (!isCache && forceLayout) {
                wrapper->Layout();
            } else {
                SyncGeometry(wrapper);
            }
            auto frameNode = DynamicCast<FrameNode>(wrapper);
            if (frameNode) {
                frameNode->MarkAndCheckNewOpIncNode();
            }
            auto gridItemProp = DynamicCast<GridItemLayoutProperty>(wrapper->GetLayoutProperty());
            CHECK_NULL_CONTINUE(gridItemProp);
            gridItemProp->UpdateIndex(itemIdex);
            gridItemProp->UpdateMainIndex(line->first);
            gridItemProp->UpdateCrossIndex(iter->first);
            UpdateRealGridItemPositionInfo(wrapper, line->first, iter->first);
        }
        mainPos += info_.lineHeightMap_[line->first] + mainGap_;
    }
    info_.totalHeightOfItemsInView_ = info_.GetTotalHeightOfItemsInView(mainGap_);

    if (startIndex == -1 && endIndex == -1) {
        startIndex = endIndex = info_.GetChildrenCount();
    }
    if (!info_.hasMultiLineItem_) {
        if (!showCached || !info_.reachEnd_) {
            auto cache = CalculateCachedCount(layoutWrapper, cacheCount);
            cacheStart = cache.first;
            cacheEnd = cache.second; // only use counting method when last line not completely filled
        }
        layoutWrapper->SetActiveChildRange(startIndex, endIndex, cacheStart, cacheEnd, showCached);
        info_.times_ = (info_.times_ + 1) % GRID_CHECK_INTERVAL;
        if (info_.times_ == 0) {
            info_.CheckGridMatrix(cacheCount);
        }
    }
    UpdateOverlay(layoutWrapper);
}

void GridScrollLayoutAlgorithm::SyncGeometry(RefPtr<LayoutWrapper>& wrapper)
{
    CHECK_NULL_VOID(wrapper);
    auto host = wrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    host->ForceSyncGeometryNode();
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
    crossPaddingOffset_ = axis_ == Axis::HORIZONTAL ? padding.top.value_or(0) : 0.0f;

    auto crossSize = frameSize.CrossSize(axis_);
    std::vector<double> crossLens;
    std::pair<std::vector<double>, double> cross;
    if (!rowsTemplate.empty()) {
        cross = ParseTemplateArgs(GridUtils::ParseArgs(rowsTemplate), crossSize, crossGap_, childrenCount);
    } else {
        cross = ParseTemplateArgs(GridUtils::ParseArgs(columnsTemplate), crossSize, crossGap_, childrenCount);
    }
    crossLens = cross.first;
    crossGap_ = cross.second;

    if (crossLens.empty()) {
        crossLens.push_back(crossSize);
    }

    if (crossCount_ != crossLens.size()) {
        crossCount_ = crossLens.size();
        info_.crossCount_ = static_cast<int32_t>(crossCount_);
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
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto gridPattern = host->GetPattern<GridPattern>();
    CHECK_NULL_VOID(gridPattern);
    itemsCrossPosition_.clear();
    UpdateGridLayoutInfo(layoutWrapper, mainSize);
    if (info_.targetIndex_.has_value()) {
        // Complete the gridLayoutInfo to get a complete set of data from 0 to targetIndex for the GridView. Make sure
        // that the index of the matrix_ and heightMap_ is incremented from 0 to targetIndex and sequentially
        SupplyAllData2ZeroIndex(mainSize, crossSize, layoutWrapper);
    }
    if (enableSkipping_) {
        SkipLargeOffset(mainSize, layoutWrapper);
    }

    if (!info_.lastCrossCount_) {
        info_.lastCrossCount_ = crossCount_;
        reason_ = GridReloadReason::INIT;
    }

    CheckReset(mainSize, crossSize, layoutWrapper);

    UpdateCurrentOffsetForJumpTo(mainSize);
    info_.jumpIndex_ = EMPTY_JUMP_INDEX;
    info_.scrollAlign_ = ScrollAlign::AUTO;

    // Step1: Measure [GridItem] that has been recorded to [gridMatrix_]
    float mainLength = MeasureRecordedItems(mainSize, crossSize, layoutWrapper);

    // Step2: When done measure items in record, request new items to fill blank at end
    FillBlankAtEnd(mainSize, crossSize, layoutWrapper, mainLength);
    if (info_.reachEnd_) { // If it reaches end when [FillBlankAtEnd], modify [currentOffset_]
        ModifyCurrentOffsetWhenReachEnd(mainSize, layoutWrapper);
    }

    // Step3: Check if need to fill blank at start (in situation of grid items moving down)
    auto haveNewLineAtStart = FillBlankAtStart(mainSize, crossSize, layoutWrapper);
    if (info_.reachStart_) {
        auto offset = info_.currentOffset_;
        if ((NonNegative(offset) && !canOverScrollStart_) || (NonPositive(offset) && !canOverScrollEnd_)) {
            info_.currentOffset_ = 0.0;
            info_.prevOffset_ = 0.0;
        }
        if (!haveNewLineAtStart) {
            if (canOverScrollStart_) {
                info_.UpdateEndIndex(offset, mainSize, mainGap_);
            }
            layoutWrapper->GetHostNode()->ChildrenUpdatedFrom(-1);
            return;
        }
        // we need lastline if blank at start is not fully filled when start line is shorter
        mainLength -= offset;
        currentMainLineIndex_ = info_.endMainLineIndex_;
        if (UseCurrentLines(mainSize, crossSize, layoutWrapper, mainLength)) {
            FillBlankAtEnd(mainSize, crossSize, layoutWrapper, mainLength);
            if (info_.reachEnd_) {
                ModifyCurrentOffsetWhenReachEnd(mainSize, layoutWrapper);
            }
        }
    }
    layoutWrapper->GetHostNode()->ChildrenUpdatedFrom(-1);
    if (info_.targetIndex_.has_value()) {
        info_.targetIndex_.reset();
    } else {
        if (info_.extraOffset_.has_value()) {
            info_.UpdateStartIndexForExtralOffset(mainGap_, mainSize);
            ACE_SCOPED_TRACE(
                "UpdateStartIndexForExtralOffset startIndex:%d, endIndex:%d, currentOffset:%f, mainSize:%f, mainGap:%f",
                info_.startIndex_, info_.endIndex_, info_.currentOffset_, mainSize, mainGap_);
        }
    }
}

void GridScrollLayoutAlgorithm::ReloadToStartIndex(float mainSize, float crossSize, LayoutWrapper* layoutWrapper)
{
    const int32_t currentItemIndex = info_.startIndex_;
    // adjust startMainLine based on the new cross count
    UpdateMainLineOnReload(currentItemIndex);
    auto firstItem = GetStartingItem(layoutWrapper, currentItemIndex);
    info_.startIndex_ = firstItem;
    currentMainLineIndex_ = (firstItem == 0 ? 0 : info_.startMainLineIndex_) - 1;
    info_.endIndex_ = firstItem - 1;
    TAG_LOGI(AceLogTag::ACE_GRID,
        "data reload begin, firstItem:%{public}d, currentItemIndex:%{public}d, reason:%{public}s", firstItem,
        currentItemIndex, GetReloadReasonStr(reason_).c_str());
    while (info_.endIndex_ < currentItemIndex) {
        auto lineHeight = FillNewLineBackward(crossSize, mainSize, layoutWrapper, false);
        if (LessNotEqual(lineHeight, 0.0)) {
            info_.reachEnd_ = true;
            break;
        }
    }
    info_.startMainLineIndex_ = currentMainLineIndex_;
    info_.UpdateStartIndexByStartLine();
    // FillNewLineBackward sometimes make startIndex_ > currentItemIndex
    while (info_.startIndex_ > currentItemIndex &&
           info_.gridMatrix_.find(info_.startMainLineIndex_) != info_.gridMatrix_.end()) {
        info_.startMainLineIndex_--;
        info_.UpdateStartIndexByStartLine();
    }
    TAG_LOGI(AceLogTag::ACE_GRID, "data reload end, startIndex_:%{public}d, startMainLineIndex_:%{public}d",
        info_.startIndex_, info_.startMainLineIndex_);
    reason_ = GridReloadReason::DATA_RELOAD;
}

void GridScrollLayoutAlgorithm::ReloadFromUpdateIdxToStartIndex(
    float mainSize, float crossSize, int32_t updateLineIndex, LayoutWrapper* layoutWrapper)
{
    const int32_t currentItemIndex = info_.startIndex_;
    auto firstItem = layoutWrapper->GetHostNode()->GetChildrenUpdated();
    info_.startIndex_ = firstItem;
    // first "-1" means trying to fill from last line;second "-1" because it will fill next line in FillNewLineBackward
    currentMainLineIndex_ = std::max(updateLineIndex - 1, 0) - 1;
    info_.endIndex_ = firstItem - 1;

    while (info_.endIndex_ < currentItemIndex) {
        auto lineHeight = FillNewLineBackward(crossSize, mainSize, layoutWrapper, false);
        if (LessNotEqual(lineHeight, 0.0)) {
            info_.reachEnd_ = true;
            break;
        }
    }
    info_.startMainLineIndex_ = currentMainLineIndex_;
    info_.UpdateStartIndexByStartLine();
    // FillNewLineBackward sometimes make startIndex_ > currentItemIndex
    while (info_.startIndex_ > currentItemIndex &&
           info_.gridMatrix_.find(info_.startMainLineIndex_) != info_.gridMatrix_.end()) {
        info_.startMainLineIndex_--;
        info_.UpdateStartIndexByStartLine();
    }
    TAG_LOGI(AceLogTag::ACE_GRID, "data reload end, startIndex_:%{public}d, startMainLineIndex_:%{public}d",
        info_.startIndex_, info_.startMainLineIndex_);
}

bool GridScrollLayoutAlgorithm::FillBlankAtStart(float mainSize, float crossSize, LayoutWrapper* layoutWrapper)
{
    bool fillNewLine = false;
    // If [currentOffset_] is non-positive, it means no blank at start
    if (LessOrEqual(info_.currentOffset_, 0.0)) {
        return fillNewLine;
    }
    auto blankAtStart = info_.currentOffset_;
    while (GreatNotEqual(blankAtStart, 0.0) || info_.startIndex_ > info_.GetChildrenCount() - 1) {
        float lineHeight = FillNewLineForward(crossSize, mainSize, layoutWrapper);
        if (GreatOrEqual(lineHeight, 0.0)) {
            info_.lineHeightMap_[info_.startMainLineIndex_] = lineHeight;
            blankAtStart -= (lineHeight + mainGap_);
            fillNewLine = true;
            continue;
        }
        info_.reachStart_ = true;
        break;
    }

    FillOneLineForwardWithoutUpdatingStartIndex(crossSize, mainSize, layoutWrapper);

    info_.currentOffset_ = blankAtStart;
    info_.prevOffset_ = info_.currentOffset_;
    return fillNewLine;
}

// If there is a multi-line item in the current line and its starting line is not within this line,
// it may result in an incomplete layout.
void GridScrollLayoutAlgorithm::FillOneLineForwardWithoutUpdatingStartIndex(
    float crossSize, float mainSize, LayoutWrapper* layoutWrapper)
{
    if (info_.gridMatrix_.empty()) {
        return;
    }
    auto startLine = info_.gridMatrix_.find(info_.startMainLineIndex_);
    if (startLine == info_.gridMatrix_.end() || startLine->second.empty()) {
        return;
    }
    if (startLine->second.size() < crossCount_ && info_.startIndex_ > 0) {
        auto tempStartIndex = info_.startIndex_;
        auto tempStartMainLineIndex = info_.startMainLineIndex_;
        auto tempCurrentMainLineIndex = currentMainLineIndex_;
        auto tempReachStart = info_.reachStart_;

        float lineHeight = FillNewLineForward(crossSize, mainSize, layoutWrapper);
        if (GreatOrEqual(lineHeight, 0.0)) {
            info_.lineHeightMap_[info_.startMainLineIndex_] = lineHeight;
        }

        info_.startIndex_ = tempStartIndex;
        info_.startMainLineIndex_ = tempStartMainLineIndex;
        currentMainLineIndex_ = tempCurrentMainLineIndex;
        info_.reachStart_ = tempReachStart;
    }
}

// When a moving up event comes, the [currentOffset_] may have been reduced too much than the items really need to
// be moved up, so we need to modify [currentOffset_] according to previous position.
void GridScrollLayoutAlgorithm::ModifyCurrentOffsetWhenReachEnd(float mainSize, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto gridPattern = host->GetPattern<GridPattern>();
    CHECK_NULL_VOID(gridPattern);
    // use original size in order to add end spacing
    mainSize -= info_.contentEndPadding_;
    // Step1. Calculate total length of all items with main gap in viewport.
    // [lengthOfItemsInViewport] must be greater than or equal to viewport height
    float lengthOfItemsInViewport = info_.GetTotalHeightOfItemsInView(mainGap_);
    // scroll forward
    if (LessNotEqual(info_.prevOffset_, info_.currentOffset_)) {
        if ((NonNegative(info_.currentOffset_) && !canOverScrollStart_) ||
            (NonPositive(info_.currentOffset_) && !canOverScrollEnd_)) {
            info_.reachEnd_ = false;
            return;
        } else if (!isChildrenUpdated_) {
            if (LessNotEqual(lengthOfItemsInViewport, mainSize)) {
                return;
            }
        }
    }
    // Step2. Calculate real offset that items can only be moved up by.
    // Hint: [prevOffset_] is a non-positive value
    if (LessNotEqual(lengthOfItemsInViewport, mainSize) && info_.startIndex_ == 0) {
        if (((NonNegative(info_.currentOffset_) && !canOverScrollStart_) ||
                (NonPositive(info_.currentOffset_) && !canOverScrollEnd_)) ||
            isChildrenUpdated_) {
            info_.currentOffset_ = 0;
            info_.prevOffset_ = 0;
        }
        info_.reachStart_ = true;
        info_.offsetEnd_ = LessOrEqual(info_.currentOffset_ + lengthOfItemsInViewport, mainSize);
        return;
    }

    // last grid item is not fully showed
    if (GreatNotEqual(info_.currentOffset_ + lengthOfItemsInViewport, mainSize)) {
        info_.offsetEnd_ = false;
        return;
    }

    if (info_.hasMultiLineItem_ && info_.endIndex_ == info_.GetChildrenCount() - 1) {
        if (!CheckLastLineItemFullyShowed(layoutWrapper)) {
            info_.offsetEnd_ = false;
            return;
        }
    }

    // Step3. modify [currentOffset_]
    if (!canOverScrollEnd_) {
        float realOffsetToMoveUp = lengthOfItemsInViewport - mainSize + info_.prevOffset_;
        info_.currentOffset_ = info_.prevOffset_ - realOffsetToMoveUp;
        info_.prevOffset_ = info_.currentOffset_;
    }
    info_.offsetEnd_ = true;
}

void GridScrollLayoutAlgorithm::FillBlankAtEnd(
    float mainSize, float crossSize, LayoutWrapper* layoutWrapper, float& mainLength)
{
    // fill current line first
    FillCurrentLine(mainSize, crossSize, layoutWrapper);

    if (GreatNotEqual(mainLength, mainSize)) {
        if (IsScrollToEndLine()) {
            TAG_LOGI(AceLogTag::ACE_GRID, "scroll to end line with index:%{public}d", moveToEndLineIndex_);
            // scrollToIndex(AUTO) on first layout
            moveToEndLineIndex_ = -1;
        }
        return;
    }
    // When [mainLength] is still less than [mainSize], do [FillNewLineBackward] repeatedly until filling up the lower
    // part of the viewport
    while (LessNotEqual(mainLength, mainSize)) {
        float lineHeight = FillNewLineBackward(crossSize, mainSize, layoutWrapper, false);
        if (GreatOrEqual(lineHeight, 0.0)) {
            mainLength += (lineHeight + mainGap_);
            continue;
        }
        info_.reachEnd_ = true;
        return;
    };
    // last line make LessNotEqual(mainLength, mainSize) and continue is reach end too
    info_.reachEnd_ = info_.endIndex_ == info_.GetChildrenCount() - 1;
}

void GridScrollLayoutAlgorithm::FillCurrentLine(float mainSize, float crossSize, LayoutWrapper* layoutWrapper)
{
    auto mainIter = info_.gridMatrix_.find(currentMainLineIndex_);
    if (mainIter != info_.gridMatrix_.end() && mainIter->second.size() < crossCount_) {
        bool doneFillCurrentLine = false;
        auto currentIndex = info_.endIndex_ + 1;
        cellAveLength_ = -1.0f;
        lastCross_ = 0;
        auto childrenCount = info_.GetChildrenCount();
        for (uint32_t i = mainIter->second.size(); i < crossCount_; i++) {
            // Step1. Get wrapper of [GridItem]
            if (currentIndex >= childrenCount) {
                break;
            }
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
            if (!itemWrapper) {
                break;
            }
            // Step2. Measure child
            auto frameSize = axis_ == Axis::VERTICAL ? SizeF(crossSize, mainSize) : SizeF(mainSize, crossSize);
            auto childState = MeasureNewChild(frameSize, currentIndex, layoutWrapper, itemWrapper, false);
            if (childState == -1) {
                cellAveLength_ = LessNotEqual(cellAveLength_, 0.0)
                                     ? info_.lineHeightMap_.find(currentMainLineIndex_ - 1)->second
                                     : cellAveLength_;
                --currentIndex;
                break;
            }
            i += static_cast<uint32_t>(childState) - 1;
            // Step3. Measure [GridItem]
            LargeItemLineHeight(itemWrapper);
            info_.endIndex_ = currentIndex;
            currentIndex++;
            doneFillCurrentLine = true;
        }
        if (doneFillCurrentLine) {
            info_.lineHeightMap_[currentMainLineIndex_] = cellAveLength_;
        }
    }
}

OffsetF GridScrollLayoutAlgorithm::CalculateLargeItemOffset(
    OffsetF currOffset, int32_t itemIndex, int32_t currLineIndex, int32_t currentCrossIndex)
{
    OffsetF offset = currOffset;
    for (int32_t lastCrossIndex = currLineIndex - 1; lastCrossIndex >= 0; lastCrossIndex--) {
        auto lastGridMatrixIter = info_.gridMatrix_.find(lastCrossIndex);
        if (lastGridMatrixIter == info_.gridMatrix_.end()) {
            continue;
        }
        const auto& lastGridItemRecord = lastGridMatrixIter->second;
        auto lastLineCrossItem = lastGridItemRecord.find(currentCrossIndex);
        if (lastLineCrossItem == lastGridItemRecord.end()) {
            continue;
        }
        if (lastLineCrossItem->second == itemIndex) {
            offset -= axis_ == Axis::VERTICAL ? OffsetF(0, info_.lineHeightMap_[lastCrossIndex] + mainGap_)
                                              : OffsetF(info_.lineHeightMap_[lastCrossIndex] + mainGap_, 0.0);
        } else {
            break;
        }
    }

    return offset;
}

bool GridScrollLayoutAlgorithm::NeedAdjust(const RefPtr<GridItemLayoutProperty>& itemLayoutProperty)
{
    bool needAdjust = false;
    auto main = axis_ == Axis::VERTICAL ? mainCount_ : crossCount_;
    auto cross = axis_ == Axis::VERTICAL ? crossCount_ : mainCount_;
    if (itemLayoutProperty->GetRowStart().has_value()) {
        currentItemRowStart_ = itemLayoutProperty->GetRowStart().value_or(-1);
        if ((currentItemRowStart_ < 0) || (currentItemRowStart_ >= static_cast<int32_t>(main))) {
            needAdjust = true;
        }
    }
    if (itemLayoutProperty->GetRowEnd().has_value()) {
        currentItemRowEnd_ = itemLayoutProperty->GetRowEnd().value_or(-1);
        if ((currentItemRowEnd_ < 0) || (currentItemRowEnd_ >= static_cast<int32_t>(main))) {
            needAdjust = true;
        }
    }
    if (itemLayoutProperty->GetColumnStart().has_value()) {
        currentItemColStart_ = itemLayoutProperty->GetColumnStart().value_or(-1);
        if ((currentItemColStart_ < 0) || (currentItemColStart_ >= static_cast<int32_t>(cross))) {
            needAdjust = true;
        }
    }
    if (itemLayoutProperty->GetColumnEnd().has_value()) {
        currentItemColEnd_ = itemLayoutProperty->GetColumnEnd().value_or(-1);
        if ((currentItemColEnd_ < 0) || (currentItemColEnd_ >= static_cast<int32_t>(cross))) {
            needAdjust = true;
        }
    }
    return needAdjust;
}

void GridScrollLayoutAlgorithm::AdjustRowColSpan(
    const RefPtr<LayoutWrapper>& itemLayoutWrapper, LayoutWrapper* /* layoutWrapper */, int32_t /* itemIndex */)
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
        info_.hasBigItem_ = true;
    }
    int32_t mainSpan = axis_ == Axis::VERTICAL ? currentItemRowSpan_ : currentItemColSpan_;
    if (mainSpan > 1) {
        info_.hasMultiLineItem_ = true;
    }

    itemLayoutProperty->UpdateRealRowSpan(currentItemRowSpan_);
    itemLayoutProperty->UpdateRealColumnSpan(currentItemColSpan_);
}

void GridScrollLayoutAlgorithm::LargeItemLineHeight(const RefPtr<LayoutWrapper>& itemWrapper)
{
    AdjustRowColSpan(itemWrapper, nullptr, 0);
    auto mainSpan = axis_ == Axis::VERTICAL ? currentItemRowSpan_ : currentItemColSpan_;
    auto itemSize = itemWrapper->GetGeometryNode()->GetMarginFrameSize();
    if (mainSpan == 1) {
        cellAveLength_ = std::max(GetMainAxisSize(itemSize, info_.axis_), cellAveLength_);
    }

    if (mainSpan > 1) {
        cellAveLength_ =
            std::max((GetMainAxisSize(itemSize, info_.axis_) - (mainGap_ * (mainSpan - 1))) / mainSpan, cellAveLength_);
    }
}

bool GridScrollLayoutAlgorithm::IsIndexInMatrix(int32_t index, int32_t& startLine)
{
    auto iter = std::find_if(info_.gridMatrix_.begin(), info_.gridMatrix_.end(),
        [index, &startLine](const std::pair<int32_t, std::map<int32_t, int32_t>>& item) {
            for (auto& subitem : item.second) {
                if (subitem.second == index) {
                    startLine = item.first;
                    return true;
                }
            }
            return false;
        });
    return (iter != info_.gridMatrix_.end());
}

void GridScrollLayoutAlgorithm::GetTargetIndexInfoWithBenchMark(
    LayoutWrapper* layoutWrapper, bool isTargetBackward, int32_t targetIndex)
{
    int32_t benchmarkIndex =
        (isTargetBackward && !info_.gridMatrix_.empty()) ? info_.gridMatrix_.rbegin()->second.rbegin()->second + 1 : 0;
    int32_t mainStartIndex =
        (isTargetBackward && !info_.gridMatrix_.empty()) ? info_.gridMatrix_.rbegin()->first + 1 : 0;
    int32_t currentIndex = benchmarkIndex;
    int32_t headOfMainStartLine = currentIndex;
    auto childrenCount = info_.GetChildrenCount();

    while (currentIndex < targetIndex) {
        int32_t crossGridReserve = info_.crossCount_;
        /* go through a new line */
        while ((crossGridReserve > 0) && (currentIndex <= targetIndex)) {
            if (currentIndex >= childrenCount) {
                return;
            }
            auto currentWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex, false);
            CHECK_NULL_VOID(currentWrapper);
            auto layoutProperty = DynamicCast<GridItemLayoutProperty>(currentWrapper->GetLayoutProperty());
            CHECK_NULL_VOID(layoutProperty);
            auto gridSpan = layoutProperty->GetCrossSpan(info_.axis_);
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

void GridScrollLayoutAlgorithm::UpdateGridLayoutInfo(LayoutWrapper* layoutWrapper, float mainSize)
{
    /* 1. Have gotten info_.startMainLineIndex_ and directly jump to it */
    if (info_.jumpIndex_ < 0 && info_.jumpIndex_ != LAST_ITEM) {
        return;
    }
    auto childrenCount = info_.GetChildrenCount();
    if (info_.jumpIndex_ == LAST_ITEM) {
        info_.jumpIndex_ = childrenCount - 1;
    }
    /* 2. Need to find out the startMainLineIndex according to startIndex */
    int32_t targetIndex = info_.jumpIndex_;
    /* 2.1 invalid targetIndex */
    childrenCount = HasLayoutOptions(layoutWrapper) ? childrenCount + info_.repeatDifference_ : childrenCount;
    if (childrenCount <= targetIndex) {
        return;
    }

    canOverScrollStart_ = false;
    canOverScrollEnd_ = false;
    switch (info_.scrollAlign_) {
        case ScrollAlign::START:
        case ScrollAlign::END:
        case ScrollAlign::CENTER:
            ScrollToIndexStart(layoutWrapper, targetIndex);
            return;
        default:
            ScrollToIndexAuto(layoutWrapper, mainSize, targetIndex);
    }
}

bool GridScrollLayoutAlgorithm::IsScrollToEndLine() const
{
    return moveToEndLineIndex_ > 0 && info_.endIndex_ >= moveToEndLineIndex_;
}

bool GridScrollLayoutAlgorithm::IsEndLineInScreenWithGap(
    int32_t targetLine, float totalViewHeight, float mainSize) const
{
    return targetLine == info_.endMainLineIndex_ && LessOrEqual(totalViewHeight + info_.currentOffset_, mainSize);
}

void GridScrollLayoutAlgorithm::ScrollToIndexAuto(LayoutWrapper* layoutWrapper, float mainSize, int32_t targetIndex)
{
    int32_t startLine = 0;
    if (IsIndexInMatrix(targetIndex, startLine)) {
        auto& info = info_;
        if (startLine == info.startMainLineIndex_ && info.startMainLineIndex_ == info.endMainLineIndex_) {
            // startLine occupies the whole viewport
            return;
        }
        if (startLine < info_.endMainLineIndex_ && startLine > info_.startMainLineIndex_) {
            return;
        }

        if (startLine >= info_.endMainLineIndex_) {
            auto totalViewHeight = info_.GetTotalHeightOfItemsInView(mainGap_);
            if (IsEndLineInScreenWithGap(startLine, totalViewHeight, mainSize)) {
                return;
            }
            // When ScrollAlign::AUTO and startLine is greater than endMainLineIndex, the effect of
            // ScrollToIndex is the same as ScrollAlign::END.
            info_.scrollAlign_ = ScrollAlign::END;
        }

        // startLine <= info_.startMainLineIndex_
        info_.startMainLineIndex_ = startLine;
        info_.UpdateStartIndexByStartLine();
        info_.prevOffset_ = 0;
        info_.currentOffset_ = 0;
        info_.ResetPositionFlags();
        return;
    }

    /* 2.3 targetIndex is out of the matrix */
    bool isTargetBackward = true;
    if (!info_.gridMatrix_.empty()) {
        if (targetIndex < info_.gridMatrix_.begin()->second.begin()->second) {
            isTargetBackward = false;
        } else if (targetIndex > info_.gridMatrix_.rbegin()->second.rbegin()->second) {
            isTargetBackward = true;
        } else {
            return;
        }
    }
    auto grid = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(grid);
    grid->ChildrenUpdatedFrom(0);
    reason_ = GridReloadReason::SCROLL_TO_INDEX;
    GetTargetIndexInfoWithBenchMark(layoutWrapper, isTargetBackward, targetIndex);
    moveToEndLineIndex_ = isTargetBackward ? targetIndex : moveToEndLineIndex_;
}

void GridScrollLayoutAlgorithm::ScrollToIndexStart(LayoutWrapper* layoutWrapper, int32_t targetIndex)
{
    int32_t startLine = 0;
    /* targetIndex is in the matrix */
    if (IsIndexInMatrix(targetIndex, startLine)) {
        if (startLine == info_.startMainLineIndex_) {
            info_.prevOffset_ = info_.currentOffset_;
            info_.currentOffset_ = 0;
            info_.ResetPositionFlags();
            return;
        }

        info_.startMainLineIndex_ = startLine;
        info_.UpdateStartIndexByStartLine();
        info_.prevOffset_ = 0;
        info_.currentOffset_ = 0;
        info_.ResetPositionFlags();
        return;
    }
    /* targetIndex is out of the matrix */
    bool isTargetBackward = true;
    if (!info_.gridMatrix_.empty()) {
        if (targetIndex < info_.gridMatrix_.begin()->second.begin()->second) {
            isTargetBackward = false;
        } else if (targetIndex > info_.gridMatrix_.rbegin()->second.rbegin()->second) {
            isTargetBackward = true;
        } else {
            return;
        }
    }
    auto grid = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(grid);
    grid->ChildrenUpdatedFrom(0);
    reason_ = GridReloadReason::SCROLL_TO_INDEX;
    GetTargetIndexInfoWithBenchMark(layoutWrapper, isTargetBackward, targetIndex);
}

void GridScrollLayoutAlgorithm::UpdateCurrentOffsetForJumpTo(float mainSize)
{
    if (info_.scrollAlign_ == ScrollAlign::CENTER || info_.scrollAlign_ == ScrollAlign::END) {
        int32_t startLine = 0;
        /* targetIndex is in the matrix */
        if (IsIndexInMatrix(info_.jumpIndex_, startLine)) {
            // scroll to end of the screen
            info_.currentOffset_ = mainSize - info_.lineHeightMap_[startLine] - info_.contentEndPadding_;
            // scroll to center of the screen
            if (info_.scrollAlign_ == ScrollAlign::CENTER) {
                info_.currentOffset_ /= 2;
            }
            info_.prevOffset_ = info_.currentOffset_;
        } else {
            /* targetIndex is out of the matrix */
            TAG_LOGW(AceLogTag::ACE_GRID, "can not find jumpIndex in Grid Matrix :%{public}d", info_.jumpIndex_);
        }
    }
    if (info_.extraOffset_.has_value() && !info_.targetIndex_.has_value()) {
        info_.currentOffset_ += info_.extraOffset_.value();
        info_.prevOffset_ = info_.currentOffset_;
    }
}

float GridScrollLayoutAlgorithm::MeasureRecordedItems(float mainSize, float crossSize, LayoutWrapper* layoutWrapper)
{
    currentMainLineIndex_ = info_.startMainLineIndex_ - 1;
    float mainLength = info_.currentOffset_;
    // already at start line, do not use offset for mainLength
    if (info_.startMainLineIndex_ == 0 && GreatNotEqual(mainLength, 0)) {
        mainLength = 0;
    }
    UseCurrentLines(mainSize, crossSize, layoutWrapper, mainLength);
    return mainLength;
}

namespace {
inline bool OneLineMovesOffViewportFromAbove(float mainLength, float lineHeight)
{
    return LessNotEqual(mainLength, 0.0) || (NearZero(mainLength) && GreatNotEqual(lineHeight, 0.0f));
}
} // namespace

namespace {
inline void UpdateStartIndexByStartLine(GridLayoutInfo& info_)
{
    auto startLine = info_.gridMatrix_.find(info_.startMainLineIndex_);
    if (startLine != info_.gridMatrix_.end() && !startLine->second.empty()) {
        info_.startIndex_ = startLine->second.begin()->second;
        return;
    }

    if (info_.endIndex_ < info_.childrenCount_ - 1) {
        info_.startIndex_ = info_.endIndex_ + 1;
    }
}
} // namespace

bool GridScrollLayoutAlgorithm::MeasureExistingLine(int32_t line, float& mainLength, int32_t& endIdx)
{
    auto it = info_.gridMatrix_.find(line);
    if (it == info_.gridMatrix_.end() || info_.lineHeightMap_.find(line) == info_.lineHeightMap_.end()) {
        return false;
    }
    int32_t idx = -1;
    cellAveLength_ = -1.0f;
    for (const auto& cell : it->second) {
        if (idx == cell.second) {
            continue;
        }
        idx = cell.second;
        if (idx == -1) {
            // move from another grid
            continue;
        }
        auto item = wrapper_->GetOrCreateChildByIndex(idx);
        if (!item) {
            break;
        }
        AdjustRowColSpan(item, wrapper_, idx);
        auto crossStart = axis_ == Axis::VERTICAL ? currentItemColStart_ : currentItemRowStart_;
        if (crossStart == -1) {
            MeasureChildPlaced(frameSize_, idx, cell.first, wrapper_, item);
        } else {
            MeasureChildPlaced(frameSize_, idx, crossStart, wrapper_, item);
        }
        // Record end index. When fill new line, the [endIndex_] will be the first item index to request
        LargeItemLineHeight(item);
        endIdx = std::max(idx, endIdx);
        info_.endIndex_ = endIdx;
    }

    if (NonNegative(cellAveLength_)) { // Means at least one item has been measured
        info_.lineHeightMap_[line] = cellAveLength_;
        mainLength += cellAveLength_ + mainGap_;
    }
    // If a line moves up out of viewport, update [startIndex_], [currentOffset_] and [startMainLineIndex_]
    if (OneLineMovesOffViewportFromAbove(mainLength, cellAveLength_)) {
        info_.currentOffset_ = mainLength;
        info_.prevOffset_ = info_.currentOffset_;
        info_.startMainLineIndex_ = line + 1;
        UpdateStartIndexByStartLine(info_);
    }
    return true;
}

bool GridScrollLayoutAlgorithm::UseCurrentLines(
    float mainSize, float crossSize, LayoutWrapper* layoutWrapper, float& mainLength)
{
    bool runOutOfRecord = false;
    // Measure grid items row by row
    int32_t tempEndIndex = -1;
    while (LessNotEqual(mainLength, mainSize)) {
        if (!MeasureExistingLine(++currentMainLineIndex_, mainLength, tempEndIndex)) {
            runOutOfRecord = true;
            break;
        }
    }
    // Case 1. if this while-loop breaks due to running out of records, the [currentMainLineIndex_] is larger by 1 than
    // real main line index, so reduce 1.
    // Case 2. if this while-loop stops due to false result of [LessNotEqual(mainLength, mainSize)], the
    // [currentMainLineIndex_] is exactly the real main line index. Update [endMainLineIndex_] when the recorded items
    // are done measured.
    info_.endMainLineIndex_ = runOutOfRecord ? --currentMainLineIndex_ : currentMainLineIndex_;
    // reset reachEnd_ if any line at bottom is out of viewport
    // last line make LessNotEqual(mainLength, mainSize) and continue is reach end too
    info_.reachEnd_ = info_.endIndex_ == info_.GetChildrenCount() - 1;
    if (info_.reachEnd_) {
        if (LessNotEqual(info_.GetTotalHeightOfItemsInView(mainGap_) + info_.currentOffset_, mainSize)) {
            // skip clearing cache if overScrolling
            return runOutOfRecord;
        }
    } else {
        info_.offsetEnd_ = false;
    }
    return runOutOfRecord;
}

void GridScrollLayoutAlgorithm::SkipLargeOffset(float mainSize, LayoutWrapper* layoutWrapper)
{
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);
    auto cacheCount = gridLayoutProperty->GetCachedCountValue(info_.defCachedCount_);
    cacheCount = std::max(cacheCount, 1);
    SkipForwardLines(cacheCount * mainSize, layoutWrapper);
    SkipBackwardLines(cacheCount * mainSize, layoutWrapper);
}

void GridScrollLayoutAlgorithm::SkipForwardLines(float mainSize, LayoutWrapper* layoutWrapper)
{
    if (!GreatOrEqual(info_.currentOffset_ - info_.prevOffset_, mainSize)) {
        return;
    }
    // skip lines in matrix
    while (GreatOrEqual(info_.currentOffset_, mainSize)) {
        auto line = info_.gridMatrix_.find(info_.startMainLineIndex_ - 1);
        if (line == info_.gridMatrix_.end()) {
            break;
        }
        auto lineHeight = info_.lineHeightMap_.find(info_.startMainLineIndex_ - 1);
        if (lineHeight == info_.lineHeightMap_.end()) {
            break;
        }
        --info_.startMainLineIndex_;
        info_.startIndex_ = line->second.begin()->second;
        info_.currentOffset_ -= lineHeight->second + mainGap_;
        info_.currentHeight_ -= lineHeight->second + mainGap_;
    }

    // skip lines not in matrix
    if (GreatOrEqual(info_.currentOffset_, mainSize) && info_.startIndex_ > 0) {
        if (!info_.hasBigItem_) {
            SkipRegularLines(true);
        } else {
            SkipIrregularLines(layoutWrapper, true);
        }
        info_.startIndex_ = std::clamp(info_.startIndex_, 0, info_.GetChildrenCount() - 1);
        TAG_LOGI(AceLogTag::ACE_GRID, "estimatedIndex:%{public}d", info_.startIndex_);
        auto grid = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(grid);
        grid->ChildrenUpdatedFrom(0);
        reason_ = GridReloadReason::SKIP_LARGE_OFFSET;
    }
}

void GridScrollLayoutAlgorithm::SkipBackwardLines(float mainSize, LayoutWrapper* layoutWrapper)
{
    if (!GreatOrEqual(info_.prevOffset_ - info_.currentOffset_, mainSize)) {
        return;
    }

    if (!SkipLargeLineHeightLines(mainSize)) {
        return;
    }

    // grid size change from big to small
    info_.UpdateEndLine(mainSize, mainGap_);

    // skip lines in matrix
    while (GreatOrEqual(-info_.currentOffset_, mainSize)) {
        auto line = info_.gridMatrix_.find(info_.endMainLineIndex_ + 1);
        if (line == info_.gridMatrix_.end()) {
            break;
        }
        auto lineHeight = info_.lineHeightMap_.find(info_.endMainLineIndex_ + 1);
        if (lineHeight == info_.lineHeightMap_.end()) {
            break;
        }
        ++info_.startMainLineIndex_;
        ++info_.endMainLineIndex_;
        info_.currentOffset_ += lineHeight->second + mainGap_;
        info_.currentHeight_ += lineHeight->second + mainGap_;
    }
    info_.UpdateStartIndexByStartLine();

    // skip lines not in matrix
    if (GreatOrEqual(-info_.currentOffset_, mainSize)) {
        if (!info_.hasBigItem_) {
            SkipRegularLines(false);
        } else {
            SkipIrregularLines(layoutWrapper, false);
        }
        info_.startIndex_ = std::clamp(info_.startIndex_, 0, info_.GetChildrenCount() - 1);
        TAG_LOGI(AceLogTag::ACE_GRID, "estimatedIndex:%{public}d, currentOffset:%{public}f", info_.startIndex_,
            info_.currentOffset_);
        auto grid = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(grid);
        grid->ChildrenUpdatedFrom(0);
        reason_ = GridReloadReason::SKIP_LARGE_OFFSET;
    }
}

void GridScrollLayoutAlgorithm::SkipRegularLines(bool forward)
{
    auto lineHeight = info_.GetAverageLineHeight() + mainGap_;
    if (LessOrEqual(lineHeight, 0.0)) {
        return;
    }
    int32_t estimatedLines = info_.currentOffset_ / lineHeight;
    if (forward && info_.startIndex_ < estimatedLines * static_cast<int32_t>(crossCount_)) {
        info_.startIndex_ = 0;
        info_.currentOffset_ = 0;
    } else {
        info_.startIndex_ -= estimatedLines * static_cast<int32_t>(crossCount_);
        info_.currentOffset_ -= lineHeight * estimatedLines;
    }
}

void GridScrollLayoutAlgorithm::SkipIrregularLines(LayoutWrapper* layoutWrapper, bool forward)
{
    auto grid = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(grid);
    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    auto averageHeight = pattern->GetAverageHeight();
    if (LessOrEqual(averageHeight, 0.0)) {
        return;
    }
    int32_t estimatedIndex = (info_.currentOffset_) / averageHeight;
    info_.startIndex_ = std::min(info_.startIndex_ - estimatedIndex, info_.GetChildrenCount());
    info_.currentOffset_ = info_.prevOffset_;
}

float GridScrollLayoutAlgorithm::FillNewLineForward(float crossSize, float mainSize, LayoutWrapper* layoutWrapper)
{
    // To make the code more convenient to read, we name a param in situation of vertical, for example:
    // 1. [lineHight] means height of a row when the Grid is vertical;
    // 2. [lineHight] means width of a column when the Grid is horizontal;
    // Other params are also named according to this principle.
    cellAveLength_ = -1.0f;
    auto currentIndex = info_.startIndex_;
    if (info_.startMainLineIndex_ - 1 < 0) {
        if (currentIndex == 0) {
            return cellAveLength_;
        }
        // add more than one line
        UpdateMatrixForAddedItems();
    }
    info_.startMainLineIndex_--;
    bool doneCreateNewLine = false;
    auto gridMatrixIter = info_.gridMatrix_.find(info_.startMainLineIndex_);
    if (gridMatrixIter == info_.gridMatrix_.end()) {
        AddForwardLines(currentIndex, crossSize, mainSize, layoutWrapper);
    }
    gridMatrixIter = info_.gridMatrix_.find(info_.startMainLineIndex_);
    if (gridMatrixIter == info_.gridMatrix_.end()) {
        return cellAveLength_;
    }

    // need to obtain the item node in order and by step one in LazyLayoutWrapperBuilder::OnGetOrCreateWrapperByIndex
    for (auto itemIter = gridMatrixIter->second.rbegin(); itemIter != gridMatrixIter->second.rend(); ++itemIter) {
        currentIndex = itemIter->second;

        // Step1. Get wrapper of [GridItem]
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
        if (!itemWrapper) {
            break;
        }
        // Step2. Measure child
        auto frameSize = axis_ == Axis::VERTICAL ? SizeF(crossSize, mainSize) : SizeF(mainSize, crossSize);
        AdjustRowColSpan(itemWrapper, layoutWrapper, currentIndex);
        auto crossStart = axis_ == Axis::VERTICAL ? currentItemColStart_ : currentItemRowStart_;
        if (crossStart == -1) {
            MeasureChildPlaced(frameSize, currentIndex, itemIter->first, layoutWrapper, itemWrapper);
        } else {
            MeasureChildPlaced(frameSize, currentIndex, crossStart, layoutWrapper, itemWrapper);
        }
        // Step3. Measure [GridItem]
        LargeItemLineHeight(itemWrapper);
        info_.startIndex_ = currentIndex;
    }

    doneCreateNewLine = GreatOrEqual(cellAveLength_, 0.0);
    // If it fails to create new line when [FillNewLineForward] is called, it means that it reaches start
    info_.reachStart_ = !doneCreateNewLine;

    return cellAveLength_;
}

void GridScrollLayoutAlgorithm::UpdateMatrixForAddedItems()
{
    decltype(info_.lineHeightMap_) gridLineHeightMap(std::move(info_.lineHeightMap_));
    decltype(info_.gridMatrix_) gridMatrix(std::move(info_.gridMatrix_));
    for (const auto& item : gridMatrix) {
        info_.gridMatrix_[item.first + 1] = item.second;
    }
    for (const auto& item : gridLineHeightMap) {
        info_.lineHeightMap_[item.first + 1] = item.second;
    }
    info_.startMainLineIndex_ = info_.startMainLineIndex_ + 1;
    info_.endMainLineIndex_ = info_.endMainLineIndex_ + 1;
    TAG_LOGI(AceLogTag::ACE_GRID, "add more than one line startMainLineIndex_:%{public}d", info_.startMainLineIndex_);
}

void GridScrollLayoutAlgorithm::AddForwardLines(
    int32_t currentIndex, float crossSize, float mainSize, LayoutWrapper* layoutWrapper)
{
    auto endMainLineIndex = info_.endMainLineIndex_;
    auto endIndex = info_.endIndex_;
    auto firstItem = GetStartingItem(layoutWrapper, currentIndex - 1);
    auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(firstItem);
    CHECK_NULL_VOID(itemWrapper);
    AdjustRowColSpan(itemWrapper, layoutWrapper, firstItem);
    auto mainSpan = axis_ == Axis::VERTICAL ? currentItemRowSpan_ : currentItemColSpan_;
    auto measureNumber = 0;
    currentMainLineIndex_ = (firstItem == 0 ? 0 : info_.startMainLineIndex_) - 1;
    info_.endIndex_ = firstItem - 1;
    // firstItem may be more than one line ahead, use new matrix to save and merge to old matrix
    decltype(info_.lineHeightMap_) gridLineHeightMap(std::move(info_.lineHeightMap_));
    decltype(info_.gridMatrix_) gridMatrix(std::move(info_.gridMatrix_));
    bool addLine = false;
    float newLineHeight = -1.0f;
    while (info_.endIndex_ < currentIndex - 1 || mainSpan > measureNumber) {
        newLineHeight = FillNewLineBackward(crossSize, mainSize, layoutWrapper, true);
        measureNumber++;
        if (LessNotEqual(newLineHeight, 0.0)) {
            info_.reachEnd_ = true;
            break;
        }
        addLine = true;
    }
    if (!addLine) {
        return;
    }
    // merge matrix
    auto forwardLines = info_.endMainLineIndex_ - info_.startMainLineIndex_;
    if (forwardLines >= 0) {
        auto begin = info_.gridMatrix_.begin()->first;
        if (info_.endMainLineIndex_ - begin <= begin) {
            for (auto i = begin; i <= info_.endMainLineIndex_; i++) {
                gridMatrix.emplace(i - forwardLines, std::move(info_.gridMatrix_[i]));
                gridLineHeightMap.emplace(i - forwardLines, info_.lineHeightMap_[i]);
            }
            gridMatrix.swap(info_.gridMatrix_);
            gridLineHeightMap.swap(info_.lineHeightMap_);

            MergeRemainingLines(gridMatrix, forwardLines);
        } else {
            for (auto i = info_.startMainLineIndex_ + 1; i <= gridMatrix.rbegin()->first; i++) {
                info_.gridMatrix_.emplace(forwardLines + i, std::move(gridMatrix[i]));
                info_.lineHeightMap_.emplace(forwardLines + i, gridLineHeightMap[i]);
            }
        }
    } else {
        // delete more than one line items
        for (auto i = info_.startMainLineIndex_ + 1; i <= gridMatrix.rbegin()->first; i++) {
            info_.gridMatrix_.emplace(forwardLines + i, std::move(gridMatrix[i]));
            info_.lineHeightMap_.emplace(forwardLines + i, gridLineHeightMap[i]);
        }
    }

    info_.startMainLineIndex_ = info_.endMainLineIndex_ - (forwardLines > 0 ? forwardLines : 0);
    info_.endMainLineIndex_ = endMainLineIndex + (forwardLines < 0 ? forwardLines : 0);
    info_.endIndex_ = endIndex;
    TAG_LOGI(AceLogTag::ACE_GRID,
        "after load forward:start main line %{public}d end main line %{public}d, new line height:%{public}f, "
        "gridMainSize:%{public}f",
        info_.startMainLineIndex_, info_.endMainLineIndex_, newLineHeight, mainSize);
}

float GridScrollLayoutAlgorithm::FillNewLineBackward(
    float crossSize, float mainSize, LayoutWrapper* layoutWrapper, bool reverse)
{
    // To make the code more convenient to read, we name a param in situation of vertical, for example:
    // 1. [lineHight] means height of a row when the Grid is vertical;
    // 2. [lineHight] means width of a column when the Grid is horizontal;
    // Other params are also named according to this principle.
    cellAveLength_ = -1.0f;
    if (IsScrollToEndLine()) {
        TAG_LOGI(AceLogTag::ACE_GRID, "scroll to end line with index:%{public}d", moveToEndLineIndex_);
        // scrollToIndex(AUTO) on first layout
        moveToEndLineIndex_ = -1;
        return cellAveLength_;
    }
    auto currentIndex = info_.endIndex_ + 1;
    currentMainLineIndex_++; // if it fails to fill a new line backward, do [currentMainLineIndex_--]
    if (info_.gridMatrix_.find(currentMainLineIndex_) != info_.gridMatrix_.end()) {
        cellAveLength_ = info_.lineHeightMap_.find(currentMainLineIndex_ - 1)->second;
    }
    lastCross_ = 0;
    bool doneFillLine = false;

    for (uint32_t i = 0; i < crossCount_; i++) {
        // already finish first line forward
        if ((reverse && currentIndex >= info_.startIndex_)) {
            break;
        }
        if (currentIndex >= info_.GetChildrenCount()) {
            TAG_LOGW(ACE_GRID, "can not get item at:%{public}d, total items:%{public}d", currentIndex,
                info_.GetChildrenCount());
            break;
        }
        // Step1. Get wrapper of [GridItem]
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
        if (!itemWrapper) {
            if (currentIndex < info_.GetChildrenCount()) {
                TAG_LOGW(ACE_GRID, "can not get item at:%{public}d, total items:%{public}d", currentIndex,
                    info_.GetChildrenCount());
                std::string subErrorType = "can not get item at:" + std::to_string(currentIndex) +
                                           ", total items:" + std::to_string(info_.GetChildrenCount());
                EventReport::ReportScrollableErrorEvent("Grid", ScrollableErrorType::GET_CHILD_FAILED, subErrorType);
            }
            LargeItemNextLineHeight(currentMainLineIndex_, layoutWrapper);
            break;
        }
        // Step2. Measure child
        auto frameSize = axis_ == Axis::VERTICAL ? SizeF(crossSize, mainSize) : SizeF(mainSize, crossSize);
        auto crossSpan = MeasureNewChild(frameSize, currentIndex, layoutWrapper, itemWrapper, false);
        if (crossSpan < 0) {
            cellAveLength_ = LessNotEqual(cellAveLength_, 0.0)
                                 ? info_.lineHeightMap_.find(currentMainLineIndex_ - 1)->second
                                 : cellAveLength_;
            --currentIndex;
            break;
        }
        i = static_cast<uint32_t>(lastCross_ - 1);
        // Step3. Measure [GridItem]
        LargeItemLineHeight(itemWrapper);

        info_.endIndex_ = currentIndex;
        currentIndex++;
        doneFillLine = true;
    }

    if (doneFillLine || info_.gridMatrix_.find(currentMainLineIndex_) != info_.gridMatrix_.end()) {
        info_.lineHeightMap_[currentMainLineIndex_] = cellAveLength_;
        info_.endMainLineIndex_ = currentMainLineIndex_;
    } else {
        currentMainLineIndex_--;
    }
    return cellAveLength_;
}

void GridScrollLayoutAlgorithm::LargeItemNextLineHeight(int32_t currentLineIndex, LayoutWrapper* layoutWrapper)
{
    auto gridMatrixIter = info_.gridMatrix_.find(currentLineIndex);
    auto currentIndex = 0;
    if (gridMatrixIter != info_.gridMatrix_.end()) {
        for (auto itemIter = gridMatrixIter->second.rbegin(); itemIter != gridMatrixIter->second.rend(); ++itemIter) {
            currentIndex = itemIter->second;
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
            if (!itemWrapper) {
                break;
            }
            LargeItemLineHeight(itemWrapper);
        }
    }
}

void GridScrollLayoutAlgorithm::LargeItemForwardLineHeight(int32_t currentLineIndex, LayoutWrapper* layoutWrapper)
{
    auto lineIndex = currentLineIndex;
    auto gridMatrixIter = info_.gridMatrix_.find(lineIndex);
    if (gridMatrixIter == info_.gridMatrix_.end()) {
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
        AdjustRowColSpan(itemWrapper, layoutWrapper, currentIndex);
        for (int32_t lastCrossIndex = lineIndex - 1; lastCrossIndex >= 0; lastCrossIndex--) {
            auto lastGridMatrixIter = info_.gridMatrix_.find(lastCrossIndex);
            if (lastGridMatrixIter == info_.gridMatrix_.end()) {
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
        auto currentGridMatrixIter = info_.gridMatrix_.find(i);
        if (currentGridMatrixIter == info_.gridMatrix_.end()) {
            continue;
        }
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
            LargeItemLineHeight(itemWrapper);
            auto line = info_.lineHeightMap_.find(i);
            if (line == info_.lineHeightMap_.end() || line->second < cellAveLength_) {
                info_.lineHeightMap_[i] = cellAveLength_;
            }
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
            itemCrossSize += GetOrDefault(itemsCrossSize_, crossIndex, 0.0f);
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
    AdjustRowColSpan(childLayoutWrapper, layoutWrapper, itemIndex);
    auto mainSpan = axis_ == Axis::VERTICAL ? currentItemRowSpan_ : currentItemColSpan_;
    auto crossSpan = axis_ == Axis::VERTICAL ? currentItemColSpan_ : currentItemRowSpan_;
    auto crossStart = axis_ == Axis::VERTICAL ? currentItemColStart_ : currentItemRowStart_;
    if (crossSpan > crossCount) {
        TAG_LOGW(AceLogTag::ACE_GRID,
            "item %{public}d can not be placed in grid: cross count:%{public}d, cross span:%{public}d", itemIndex,
            crossCount, crossSpan);
        return crossSpan;
    }
    int32_t mainIndex = currentMainLineIndex_;

    if (crossStart >= 0 && crossStart < crossCount) {
        if (crossStart < lastCross_) {
            return -1;
        } else if (CheckGridPlaced(itemIndex, mainIndex, crossStart, mainSpan, crossSpan)) {
            MeasureChild(layoutWrapper, frameSize, childLayoutWrapper, crossStart, crossSpan);
            itemsCrossPosition_.try_emplace(itemIndex, ComputeItemCrossPosition(crossStart));
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
        itemsCrossPosition_.try_emplace(itemIndex, ComputeItemCrossPosition(crossIndex));
    }
    if (mainSpan > 1 || crossSpan > 1) {
        for (int i = mainIndex; i < mainSpan; i++) {
            info_.irregularLines_[i] = true;
        }
    }
    return crossSpan;
}

int32_t GridScrollLayoutAlgorithm::MeasureChildPlaced(const SizeF& frameSize, int32_t itemIndex, int32_t crossStart,
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& childLayoutWrapper)
{
    AdjustRowColSpan(childLayoutWrapper, layoutWrapper, itemIndex);
    auto crossSpan = axis_ == Axis::VERTICAL ? currentItemColSpan_ : currentItemRowSpan_;
    if (static_cast<uint32_t>(crossStart + crossSpan) > crossCount_) {
        TAG_LOGI(AceLogTag::ACE_GRID, "item %{public}d cross not enough, start:%{public}d, span:%{public}d", itemIndex,
            crossStart, crossSpan);
        return 0;
    }
    auto mainSpan = axis_ == Axis::HORIZONTAL ? currentItemColSpan_ : currentItemRowSpan_;
    if (crossSpan > 1 || mainSpan > 1) {
        for (int i = currentMainLineIndex_; i < mainSpan; i++) {
            info_.irregularLines_[i] = true;
        }
    }

    MeasureChild(layoutWrapper, frameSize, childLayoutWrapper, crossStart, crossSpan);
    itemsCrossPosition_.try_emplace(itemIndex, ComputeItemCrossPosition(crossStart));
    return crossSpan;
}

bool GridScrollLayoutAlgorithm::CheckNeedMeasure(
    const RefPtr<LayoutWrapper>& layoutWrapper, const LayoutConstraintF& layoutConstraint) const
{
    auto childLayoutProperty = AceType::DynamicCast<GridItemLayoutProperty>(layoutWrapper->GetLayoutProperty());
    if (childLayoutProperty && childLayoutProperty->GetNeedStretch() && info_.clearStretch_) {
        childLayoutProperty->SetNeedStretch(false);
        if (axis_ == Axis::VERTICAL) {
            childLayoutProperty->ClearUserDefinedIdealSize(false, true);
        } else {
            childLayoutProperty->ClearUserDefinedIdealSize(true, false);
        }
        return true;
    }

    if (expandSafeArea_ || layoutWrapper->CheckNeedForceMeasureAndLayout()) {
        return true;
    }

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    auto constraint = geometryNode->GetParentLayoutConstraint();
    CHECK_NULL_RETURN(constraint, true);
    return constraint->maxSize != layoutConstraint.maxSize ||
           constraint->percentReference != layoutConstraint.percentReference ||
           constraint->selfIdealSize.CrossSize(axis_) != layoutConstraint.selfIdealSize.CrossSize(axis_);
}

void GridScrollLayoutAlgorithm::MeasureChild(LayoutWrapper* layoutWrapper, const SizeF& frameSize,
    const RefPtr<LayoutWrapper>& childLayoutWrapper, int32_t crossStart, int32_t crossSpan)
{
    auto gridLayoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto mainSize = GetMainAxisSize(frameSize, info_.axis_);
    auto crossSize = GetCrossAxisSize(frameSize, info_.axis_);
    auto childConstraint = CreateChildConstraint(mainSize, crossSize, gridLayoutProperty, crossStart, crossSpan);
    if (!CheckNeedMeasure(childLayoutWrapper, childConstraint)) {
        return;
    }
    auto childLayoutProperty = childLayoutWrapper->GetLayoutProperty();
    if (!childLayoutProperty) {
        childLayoutWrapper->Measure(childConstraint);
        return;
    }

    auto oldConstraint = childLayoutProperty->GetLayoutConstraint();
    if (oldConstraint.has_value() && !NearEqual(GetCrossAxisSize(oldConstraint.value().maxSize, axis_),
                                         GetCrossAxisSize(childConstraint.maxSize, axis_))) {
        auto layoutAlgorithmWrapper = childLayoutWrapper->GetLayoutAlgorithm();
        if (layoutAlgorithmWrapper->SkipMeasure()) {
            layoutAlgorithmWrapper->SetNeedMeasure();
            if (layoutAlgorithmWrapper->GetLayoutAlgorithm() == nullptr) {
                layoutAlgorithmWrapper->SetLayoutAlgorithm(
                    childLayoutWrapper->GetHostNode()->GetPattern()->CreateLayoutAlgorithm());
            }
        }
    }
    childLayoutWrapper->Measure(childConstraint);
}

bool GridScrollLayoutAlgorithm::CheckGridPlaced(
    int32_t index, int32_t main, int32_t cross, int32_t mainSpan, int32_t crossSpan)
{
    // If start position is already exist in gridMatrix, place grid item fail.
    auto mainIter = info_.gridMatrix_.find(main);
    if (mainIter != info_.gridMatrix_.end()) {
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
        mainIter = info_.gridMatrix_.find(i + main);
        if (mainIter == info_.gridMatrix_.end()) {
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
        auto iter = info_.gridMatrix_.find(i);
        if (iter != info_.gridMatrix_.end()) {
            mainMap = iter->second;
        }
        for (int32_t j = cross; j < cross + crossSpan; ++j) {
            mainMap.emplace(std::make_pair(j, index));
        }
        info_.gridMatrix_[i] = mainMap;
    }
    lastCross_ = cross + crossSpan;

    return true;
}

float GridScrollLayoutAlgorithm::ComputeItemCrossPosition(int32_t crossStart) const
{
    float position = 0.0f;
    for (int32_t index = 0; index < crossStart; ++index) {
        if (index >= 0 && index < static_cast<int32_t>(itemsCrossSize_.size())) {
            position += GetOrDefault(itemsCrossSize_, index, 0.0f);
        }
    }
    position += crossStart * crossGap_ + crossPaddingOffset_;
    return position;
}

int32_t GridScrollLayoutAlgorithm::GetStartingItem(LayoutWrapper* layoutWrapper, int32_t currentIndex)
{
    int32_t firstIndex = 0;
    currentIndex = currentIndex < info_.GetChildrenCount() ? currentIndex : info_.GetChildrenCount() - 1;
    auto index = currentIndex;
    if (info_.hasBigItem_) {
        while (index > 0) {
            auto childLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
            if (!childLayoutWrapper) {
                TAG_LOGW(AceLogTag::ACE_GRID, "item [%{public}d] does not exist, reload to [0]", index);
                break;
            }

            AdjustRowColSpan(childLayoutWrapper, layoutWrapper, index);
            auto crossIndex = axis_ == Axis::VERTICAL ? currentItemColStart_ : currentItemRowStart_;
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
                TAG_LOGW(AceLogTag::ACE_GRID, "item [%{public}d] does not exist, reload to [0]", index);
                break;
            }
            AdjustRowColSpan(childLayoutWrapper, layoutWrapper, index);
            auto crossIndex = axis_ == Axis::VERTICAL ? currentItemColStart_ : currentItemRowStart_;
            // Grid may change from no big item to has big item
            if (crossIndex >= 0) {
                info_.hasBigItem_ = true;
                return GetStartingItem(layoutWrapper, currentIndex);
            }
            if (index % info_.crossCount_ == 0) {
                firstIndex = index;
                break;
            }
            --index;
        }
    }
    return firstIndex;
}

void GridScrollLayoutAlgorithm::SupplyAllData2ZeroIndex(float mainSize, float crossSize, LayoutWrapper* layoutWrapper)
{
    // Save the global variable at this moment.
    auto tempGridLayoutInfo = info_;

    // When the data is supplied again, there is an update of the original global variable info_. Therefore,
    // each time you supply the data, you must re-complete the data based on the current screen data
    auto startLineIndex = tempGridLayoutInfo.startMainLineIndex_;
    auto startIndex = tempGridLayoutInfo.startIndex_;
    auto endLineIndex = tempGridLayoutInfo.endMainLineIndex_;
    auto endIndex = tempGridLayoutInfo.endIndex_;
    auto targetIndex = tempGridLayoutInfo.targetIndex_;
    // Remove redundant data that is visible off-screen. This is the key to completing data accurately
    DeleteItemsOutOfScope(info_.lineHeightMap_, startLineIndex, endLineIndex);
    DeleteItemsOutOfScope(info_.gridMatrix_, startLineIndex, endLineIndex);

    // The continuous grid information is saved and used in the GridPattern to calculate the scroll distance
    // Complete all data with indexes from startIndex to 0
    if (startIndex > 0) {
        // The start line when completing the data
        currentMainLineIndex_ = startLineIndex;
        float lineHeight = 0.0f;
        do {
            lineHeight = FillNewLineForward(crossSize, mainSize, layoutWrapper);
        } while (GreatOrEqual(lineHeight, 0.0));
    }

    // Complete the data from endIndex+1 to targetIndex_
    auto lineHeight = 0.f;
    if (endIndex < targetIndex) {
        // The start line when completing the data
        currentMainLineIndex_ = endLineIndex;
        int32_t targetLineIndex = 0;
        do {
            lineHeight = FillNewLineBackward(crossSize, mainSize, layoutWrapper, false);
        } while (!(LessNotEqual(lineHeight, 0.0) || IsIndexInMatrix(targetIndex.value(), targetLineIndex)));
    }

    if (info_.extraOffset_.has_value() && Negative(info_.extraOffset_.value())) {
        auto extraOffset = -info_.extraOffset_.value();
        info_.GetLineIndexByIndex(targetIndex.value(), currentMainLineIndex_);
        lineHeight = info_.lineHeightMap_[currentMainLineIndex_];
        auto heightForExtraOffset = lineHeight + mainGap_;
        while (GreatOrEqual(extraOffset, heightForExtraOffset) && !Negative(lineHeight)) {
            lineHeight = FillNewLineBackward(crossSize, mainSize, layoutWrapper, false);
            heightForExtraOffset += (lineHeight + mainGap_);
        }
        ACE_SCOPED_TRACE(
            "SupplyAllData2ZeroIndex, extraOffset_:%f, heightForExtraOffset:%f, LineIndexForExtraOffset:%d",
            extraOffset, heightForExtraOffset, currentMainLineIndex_);
    }

    // Once the data is completed, the global variables need to be returned
    infoCopy_ = std::make_unique<GridLayoutInfo>(info_);
    info_ = tempGridLayoutInfo;
}

void GridScrollLayoutAlgorithm::FillCacheLineAtEnd(float mainSize, float crossSize, LayoutWrapper* layoutWrapper)
{
    auto gridLayoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto cacheCount = gridLayoutProperty->GetCachedCountValue(info_.defCachedCount_);
    if (info_.reachEnd_ || cacheCount == 0) {
        return;
    }
    auto tempEndIndex = info_.endIndex_;
    auto tempEndMainLineIndex = info_.endMainLineIndex_;
    auto tempCurrentMainLineIndex = currentMainLineIndex_;
    currentMainLineIndex_ = info_.endMainLineIndex_;

    for (; currentMainLineIndex_ <= tempEndMainLineIndex + cacheCount; currentMainLineIndex_++) {
        float lineHeight = FillNewCacheLineBackward(crossSize, mainSize, layoutWrapper, currentMainLineIndex_);
        if (LessNotEqual(lineHeight, 0.0)) {
            break;
        }
    }
    info_.endIndex_ = tempEndIndex;
    info_.endMainLineIndex_ = tempEndMainLineIndex;
    currentMainLineIndex_ = tempCurrentMainLineIndex;

    if (!predictBuildList_.empty()) {
        CreateCachedChildConstraint(layoutWrapper, mainSize, crossSize);
    }
}

float GridScrollLayoutAlgorithm::FillNewCacheLineBackward(
    float crossSize, float mainSize, LayoutWrapper* layoutWrapper, int32_t currentLine)
{
    // To make the code more convenient to read, we name a param in situation of vertical, for example:
    // 1. [lineHight] means height of a row when the Grid is vertical;
    // 2. [lineHight] means width of a column when the Grid is horizontal;
    // Other params are also named according to this principle.
    cellAveLength_ = -1.0f;
    auto currentIndex = info_.endIndex_ + 1;

    // if it fails to fill a new line backward, do [currentLine--]
    auto line = info_.gridMatrix_.find(currentLine);
    auto childrenCount = info_.GetChildrenCount();
    if (info_.gridMatrix_.find(currentLine) != info_.gridMatrix_.end()) {
        if (line->second.size() < crossCount_) {
            lastCross_ = 0;
            for (const auto& elem : line->second) {
                if (elem.second > info_.endIndex_) {
                    info_.endIndex_ = elem.second;
                }
            }
            auto currentIndex = info_.endIndex_ + 1;
            for (uint32_t i = line->second.size(); i < crossCount_; i++) {
                // Step1. Get wrapper of [GridItem]
                CHECK_NULL_RETURN(currentIndex < childrenCount, -1.0f);
                auto itemWrapper = layoutWrapper->GetChildByIndex(currentIndex, true);
                if (!itemWrapper || itemWrapper->CheckNeedForceMeasureAndLayout()) {
                    for (uint32_t y = i; y < crossCount_ && currentIndex < childrenCount; y++) {
                        predictBuildList_.emplace_back(currentIndex++);
                    }
                    if (GreatOrEqual(cellAveLength_, 0.0f) &&
                        info_.lineHeightMap_.find(currentLine) == info_.lineHeightMap_.end()) {
                        info_.lineHeightMap_[currentLine] = cellAveLength_;
                    }
                    return -1.0f;
                }
                // Step2. Measure child
                auto frameSize = axis_ == Axis::VERTICAL ? SizeF(crossSize, mainSize) : SizeF(mainSize, crossSize);
                auto childState = MeasureCachedChild(frameSize, currentIndex, layoutWrapper, itemWrapper);
                if (childState == -1) {
                    cellAveLength_ = LessNotEqual(cellAveLength_, 0.0)
                                         ? info_.lineHeightMap_.find(currentLine - 1)->second
                                         : cellAveLength_;
                    --currentIndex;
                    break;
                }
                i += static_cast<uint32_t>(childState) - 1;
                // Step3. Measure [GridItem]
                LargeItemLineHeight(itemWrapper);
                info_.endIndex_ = currentIndex;
                currentIndex++;
            }
        }
        CompleteItemCrossPosition(layoutWrapper, line->second);
        for (const auto& elem : line->second) {
            if (elem.second > info_.endIndex_) {
                info_.endIndex_ = elem.second;
            }
        }
        if (NonNegative(cellAveLength_)) {
            info_.lineHeightMap_[currentLine] = cellAveLength_;
            return cellAveLength_;
        }
        return GetOrDefault(info_.lineHeightMap_, currentLine, -1.f);
    }

    lastCross_ = 0;
    bool doneFillLine = false;

    for (uint32_t i = 0; i < crossCount_; i++) {
        if (currentIndex >= childrenCount) {
            break;
        }
        // Step1. Get wrapper of [GridItem]
        auto itemWrapper = layoutWrapper->GetChildByIndex(currentIndex, true);
        if (!itemWrapper || itemWrapper->CheckNeedForceMeasureAndLayout()) {
            for (uint32_t x = i; x < crossCount_ && currentIndex < childrenCount; x++) {
                predictBuildList_.emplace_back(currentIndex++);
            }
            if (GreatOrEqual(cellAveLength_, 0.0f) &&
                info_.lineHeightMap_.find(currentLine) == info_.lineHeightMap_.end()) {
                info_.lineHeightMap_[currentLine] = cellAveLength_;
            }
            return -1.0f;
        }
        // // Step2. Measure child
        auto frameSize = axis_ == Axis::VERTICAL ? SizeF(crossSize, mainSize) : SizeF(mainSize, crossSize);
        auto crossSpan = MeasureCachedChild(frameSize, currentIndex, layoutWrapper, itemWrapper);
        if (crossSpan < 0) {
            cellAveLength_ =
                LessNotEqual(cellAveLength_, 0.0) ? info_.lineHeightMap_.find(currentLine - 1)->second : cellAveLength_;
            --currentIndex;
            break;
        }
        i = static_cast<uint32_t>(lastCross_ - 1);
        // // Step3. Measure [GridItem]
        LargeItemLineHeight(itemWrapper);

        info_.endIndex_ = currentIndex;
        currentIndex++;
        doneFillLine = true;
    }

    if (doneFillLine || info_.gridMatrix_.find(currentLine) != info_.gridMatrix_.end()) {
        info_.lineHeightMap_[currentLine] = cellAveLength_;
        info_.endMainLineIndex_ = currentLine;
    } else {
        return -1.0f;
    }
    return cellAveLength_;
}

int32_t GridScrollLayoutAlgorithm::MeasureCachedChild(const SizeF& frameSize, int32_t itemIndex,
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& childLayoutWrapper)
{
    auto mainCount = static_cast<int32_t>(mainCount_);
    auto crossCount = static_cast<int32_t>(crossCount_);
    AdjustRowColSpan(childLayoutWrapper, layoutWrapper, itemIndex);
    auto mainSpan = axis_ == Axis::VERTICAL ? currentItemRowSpan_ : currentItemColSpan_;
    auto crossSpan = axis_ == Axis::VERTICAL ? currentItemColSpan_ : currentItemRowSpan_;
    auto crossStart = axis_ == Axis::VERTICAL ? currentItemColStart_ : currentItemRowStart_;
    if (crossSpan > crossCount) {
        return crossSpan;
    }
    int32_t mainIndex = currentMainLineIndex_;

    if (crossStart >= 0 && crossStart < crossCount) {
        if (crossStart < lastCross_) {
            return -1;
        } else if (CheckGridPlaced(itemIndex, mainIndex, crossStart, mainSpan, crossSpan)) {
            itemsCrossPosition_.try_emplace(itemIndex, ComputeItemCrossPosition(crossStart));
        } else {
            return -1;
        }
    } else {
        int32_t crossIndex = crossStart >= 0 ? crossStart : lastCross_;

        while (!CheckGridPlaced(itemIndex, mainIndex, crossIndex, mainSpan, crossSpan)) {
            if (GetNextGrid(mainIndex, crossIndex, false) == false) {
                return -1;
            }
            if (mainIndex >= mainCount || crossIndex >= crossCount) {
                break;
            }
        }

        itemsCrossPosition_.try_emplace(itemIndex, ComputeItemCrossPosition(crossIndex));
    }
    if (crossSpan > 1 || mainSpan > 1) {
        for (int i = currentMainLineIndex_; i < mainSpan; i++) {
            info_.irregularLines_[i] = true;
        }
    }
    return crossSpan;
}

void GridScrollLayoutAlgorithm::CompleteItemCrossPosition(
    LayoutWrapper* layoutWrapper, const std::map<int32_t, int32_t>& items)
{
    for (auto&& item : items) {
        auto currentIndex = item.second;
        auto itemWrapper = layoutWrapper->GetChildByIndex(currentIndex, true);
        if (!itemWrapper) {
            if (predictBuildList_.back().idx < currentIndex) {
                predictBuildList_.emplace_front(currentIndex);
            } else if (predictBuildList_.front().idx > currentIndex) {
                predictBuildList_.emplace_back(currentIndex);
            }
        }
        itemsCrossPosition_.try_emplace(currentIndex, ComputeItemCrossPosition(item.first));
    }
}

namespace {
LayoutConstraintF GenerateCacheItemConstraint(
    const GridItemLayoutProperty& itemProp, Axis axis, const GridPredictLayoutParam& param)
{
    auto constraint = param.layoutConstraint;
    int32_t crossSpan = itemProp.GetCrossSpan(axis);
    int32_t crossStart = itemProp.GetCrossStart(axis);
    if (crossSpan > 1) {
        float itemCrossSize = param.crossGap * (crossSpan - 1);
        for (int32_t index = 0; index < crossSpan; ++index) {
            int32_t crossIndex = (crossStart + index) % static_cast<int32_t>(param.itemsCrossSizes.size());
            if (crossIndex >= 0 && crossIndex < static_cast<int32_t>(param.itemsCrossSizes.size())) {
                itemCrossSize += GetOrDefault(param.itemsCrossSizes, crossIndex, 0.0f);
            }
        }
        constraint.maxSize.SetCrossSize(itemCrossSize, axis);
        constraint.selfIdealSize.SetCrossSize(itemCrossSize, axis);
    }
    return constraint;
}

/* revert layout range in GridLayoutInfo when this object destructs */
class TempLayoutRange {
public:
    explicit TempLayoutRange(GridLayoutInfo& info)
        : subStart_(info.startIndex_), subStartLine_(info.startMainLineIndex_), subEnd_(info.endIndex_),
          subEndLine_(info.endMainLineIndex_), info_(info)
    {}
    ~TempLayoutRange()
    {
        const int32_t diff = CalcDiff();
        info_.startIndex_ = subStart_;
        info_.startMainLineIndex_ = subStartLine_ - diff;
        info_.endIndex_ = subEnd_;
        info_.endMainLineIndex_ = subEndLine_ - diff;
    }

    const int32_t subStart_;
    const int32_t subStartLine_;
    const int32_t subEnd_;
    const int32_t subEndLine_;

private:
    GridLayoutInfo& info_;

    /**
     * @brief after SyncPreload, need adjust startMainLineIdx and endMainLineIdx according to startIndex_.
     * Because in AddForwardLines, it may change the gridMatrix_ and make the original start/endMainLineIdx invalid.
     */
    int32_t CalcDiff()
    {
        if (subStartLine_ > subEndLine_) {
            // need not adjust when there has no items in viewport.
            return 0;
        }
        auto newStartMainLineIdx = subStartLine_;
        info_.GetLineIndexByIndex(subStart_, newStartMainLineIdx);
        return subStartLine_ - newStartMainLineIdx;
    }

    ACE_DISALLOW_COPY_AND_MOVE(TempLayoutRange);
};
} // namespace

void GridScrollLayoutAlgorithm::SyncPreload(
    LayoutWrapper* wrapper, int32_t cacheLineCnt, float crossSize, float mainSize)
{
    TempLayoutRange scope(info_);
    for (int32_t i = 0; i < cacheLineCnt; ++i) {
        FillNewLineForward(crossSize, mainSize, wrapper);

        float len = 0.0f;
        int32_t endIdx = info_.endIndex_;
        int32_t line = scope.subEndLine_ + i + 1;
        if (!MeasureExistingLine(line, len, endIdx)) {
            currentMainLineIndex_ = line - 1;
            FillNewLineBackward(crossSize, mainSize, wrapper, false);
        }
    }
}

bool GridScrollLayoutAlgorithm::PredictBuildItem(FrameNode& host, int32_t itemIdx, const GridPredictLayoutParam& param)
{
    // build callback
    auto wrapper = host.GetOrCreateChildByIndex(itemIdx, false, true);
    CHECK_NULL_RETURN(wrapper, false);
    auto itemProperty = DynamicCast<GridItemLayoutProperty>(wrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(itemProperty, false);
    const Axis axis = host.GetPattern<GridPattern>()->GetAxis();

    auto constraint = GenerateCacheItemConstraint(*itemProperty, axis, param);
    wrapper->SetActive(false);
    auto frameNode = wrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    frameNode->GetGeometryNode()->SetParentLayoutConstraint(constraint);
    FrameNode::ProcessOffscreenNode(frameNode);
    return true;
}

void GridScrollLayoutAlgorithm::CreateCachedChildConstraint(
    LayoutWrapper* layoutWrapper, float mainSize, float crossSize)
{
    auto gridLayoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    cachedChildConstraint_ = CreateChildConstraint(mainSize, crossSize, gridLayoutProperty, 0, 1);
}

void GridScrollLayoutAlgorithm::UpdateMainLineOnReload(int32_t startIdx)
{
    auto& info = info_;
    if (!info.hasBigItem_) {
        info.startMainLineIndex_ = startIdx / info.crossCount_;
    }
}

std::pair<bool, bool> GridScrollLayoutAlgorithm::GetResetMode(LayoutWrapper* layoutWrapper, int32_t updateIdx)
{
    if (info_.IsOutOfEnd(mainGap_, false) // avoid reset during overScroll
        || updateIdx == -1) {
        return { 0, 0 };
    }
    bool outOfMatrix = false;
    if (updateIdx != -1 && updateIdx < info_.startIndex_) {
        int32_t startLine = 0;
        outOfMatrix = !IsIndexInMatrix(updateIdx, startLine);
    }
    auto hasOptions = HasLayoutOptions(layoutWrapper);
    return { !info_.hasBigItem_ || outOfMatrix || hasOptions, info_.hasBigItem_ && !outOfMatrix && !hasOptions };
}

void GridScrollLayoutAlgorithm::CheckReset(float mainSize, float crossSize, LayoutWrapper* layoutWrapper)
{
    int32_t updateIdx = layoutWrapper->GetHostNode()->GetChildrenUpdated();
    // [resetFromStart,resetFromUpdate]
    std::pair<bool, bool> resetMode = GetResetMode(layoutWrapper, updateIdx);
    if (info_.lastCrossCount_ != crossCount_ || resetMode.first || info_.IsResetted()) {
        if (info_.lastCrossCount_ != crossCount_) {
            reason_ = GridReloadReason::CROSS_COUNT_CHANGE;
        }
        info_.lastCrossCount_ = crossCount_;
        info_.lineHeightMap_.clear();
        info_.gridMatrix_.clear();
        info_.irregularItemsPosition_.clear();
        info_.endIndex_ = -1;
        info_.endMainLineIndex_ = 0;
        info_.prevOffset_ = info_.currentOffset_;
        info_.ResetPositionFlags();
        info_.clearStretch_ = true;
        isChildrenUpdated_ = true;
        info_.hasMultiLineItem_ = false;
        info_.times_ = 0;
        ResetFocusedIndex(layoutWrapper);
        if (info_.GetChildrenCount() > 0) {
            ReloadToStartIndex(mainSize, crossSize, layoutWrapper);
        } else {
            info_.startIndex_ = 0;
            info_.startMainLineIndex_ = 0;
        }
        if (IsScrollToEndLine()) {
            info_.currentOffset_ = mainSize - info_.lineHeightMap_[info_.endMainLineIndex_];
            info_.prevOffset_ = info_.currentOffset_;
        }
    } else if (resetMode.second) {
        isChildrenUpdated_ = true;
        info_.irregularItemsPosition_.clear();
        info_.ResetPositionFlags();
        info_.clearStretch_ = true;
        info_.prevOffset_ = info_.currentOffset_;
        ResetFocusedIndex(layoutWrapper);
        auto it = info_.FindInMatrix(updateIdx);
        it = info_.FindStartLineInMatrix(it, updateIdx);
        if (it != info_.gridMatrix_.end()) {
            const int32_t line = it->first;
            info_.ClearMatrixToEnd(updateIdx, line);
            info_.ClearHeightsFromMatrix(line);
            if (updateIdx <= info_.startIndex_) {
                ReloadFromUpdateIdxToStartIndex(mainSize, crossSize, line, layoutWrapper);
            }
        }
    }
}

bool GridScrollLayoutAlgorithm::CheckLastLineItemFullyShowed(LayoutWrapper* layoutWrapper)
{
    auto lastLine = info_.gridMatrix_.find(info_.endMainLineIndex_);
    if (lastLine != info_.gridMatrix_.end()) {
        for (const auto [corssIndex, itemIndex] : lastLine->second) {
            auto itemWrapper = layoutWrapper->GetChildByIndex(itemIndex);
            if (!itemWrapper) {
                continue;
            }
            auto itemLayoutProperty = DynamicCast<GridItemLayoutProperty>(itemWrapper->GetLayoutProperty());
            if (!itemLayoutProperty) {
                continue;
            }
            if (itemLayoutProperty->GetMainSpan(axis_) == 1) {
                continue;
            }
            auto it = info_.FindStartLineInMatrix(lastLine, itemIndex);
            if (it == info_.gridMatrix_.end()) {
                continue;
            }
            int32_t startLine = it->first;
            if (startLine + itemLayoutProperty->GetMainSpan(axis_) > info_.endMainLineIndex_ + 1) {
                return false;
            }
        }
    }
    return true;
}

bool GridScrollLayoutAlgorithm::IsIrregularLine(int32_t lineIndex) const
{
    auto irregular = info_.irregularLines_.find(lineIndex);
    if (irregular != info_.irregularLines_.end() && irregular->second) {
        return true;
    }
    return false;
}

void GridScrollLayoutAlgorithm::ResetOffsetWhenHeightChanged()
{
    if (scrollSource_ == SCROLL_FROM_NONE) {
        info_.prevOffset_ = info_.currentOffset_;
    }
}

void GridScrollLayoutAlgorithm::MergeRemainingLines(
    std::map<int32_t, std::map<int32_t, int32_t>> matrix, int32_t forwardLines)
{
    for (const auto& line : matrix) {
        if (line.second.empty()) {
            continue;
        }
        for (const auto& [crossIndex, index] : line.second) {
            info_.gridMatrix_[line.first - forwardLines][crossIndex] = index;
        }
    }
}

bool GridScrollLayoutAlgorithm::SkipLargeLineHeightLines(float mainSize)
{
    bool needSkip = false;
    for (int32_t line = info_.startMainLineIndex_; line <= info_.endMainLineIndex_; line++) {
        auto iter = info_.lineHeightMap_.find(line);
        if (iter != info_.lineHeightMap_.end() && iter->second >= mainSize) {
            needSkip = true;
            break;
        }
    }
    if (needSkip) {
        auto totalViewHeight = info_.GetTotalHeightOfItemsInView(mainGap_);
        auto needSkipHeight = totalViewHeight + info_.prevOffset_ + mainGap_;
        if (GreatOrEqual(needSkipHeight, -info_.currentOffset_)) {
            return false;
        }

        auto endLine = info_.gridMatrix_.find(info_.endMainLineIndex_ + 1);
        if (endLine != info_.gridMatrix_.end() && !endLine->second.empty()) {
            info_.currentOffset_ += needSkipHeight;
            info_.endMainLineIndex_++;
            info_.startMainLineIndex_ = info_.endMainLineIndex_;
        }
    }
    return true;
}

bool GridScrollLayoutAlgorithm::HasLayoutOptions(LayoutWrapper* layoutWrapper)
{
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(gridLayoutProperty, false);
    return gridLayoutProperty->GetLayoutOptions().has_value();
}
} // namespace OHOS::Ace::NG
