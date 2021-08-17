/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/grid_layout/render_grid_scroll_layout.h"

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/animation/curve_animation.h"
#include "core/components/grid_layout/grid_layout_component.h"
#include "core/components/grid_layout/render_grid_layout_item.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace {

const char UNIT_PERCENT[] = "%";
const char UNIT_RATIO[] = "fr";

} // namespace

void RenderGridScrollLayout::Update(const RefPtr<Component>& component)
{
    if (!NeedUpdate(component)) {
        return;
    }

    LOGD("RenderGridScrollLayout::Update");
    useScrollable_ = SCROLLABLE::NO_SCROLL;
    mainSize_ = &rowSize_;
    crossSize_ = &colSize_;
    mainCount_ = &rowCount_;
    crossCount_ = &colCount_;
    crossGap_ = &colGap_;
    mainGap_ = &rowGap_;
    RenderGridLayout::Update(component);
}

bool RenderGridScrollLayout::NeedUpdate(const RefPtr<Component>& component)
{
    const RefPtr<GridLayoutComponent> grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (!grid) {
        LOGE("RenderGridLayout update failed.");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return false;
    }

    if (direction_ != grid->GetDirection() || crossAxisAlign_ != grid->GetFlexAlign() ||
        gridWidth_ != grid->GetWidth() || gridWidth_ != grid->GetWidth() || gridHeight_ != grid->GetHeight() ||
        colsArgs_ != grid->GetColumnsArgs() || rowsArgs_ != grid->GetRowsArgs() ||
        userColGap_ != grid->GetColumnGap() || userRowGap_ != grid->GetRowGap() ||
        rightToLeft_ != grid->GetRightToLeft()) {
        return true;
    };
    return false;
}

void RenderGridScrollLayout::AddChildByIndex(int32_t index, const RefPtr<RenderNode>& renderNode)
{
    auto itor = items_.try_emplace(index, renderNode);
    if (itor.second) {
        AddChild(renderNode);
        RefPtr<RenderGridLayoutItem> node = AceType::DynamicCast<RenderGridLayoutItem>(renderNode);
        if (node) {
            node->SetBoundary();
        }
    }
}

void RenderGridScrollLayout::CreateScrollable()
{
    scrollable_ = nullptr;
    if (useScrollable_ == SCROLLABLE::NO_SCROLL) {
        return;
    }

    auto callback = [weak = AceType::WeakClaim(this)](double offset, int32_t source) {
        auto renderList = weak.Upgrade();
        return renderList ? renderList->UpdateScrollPosition(offset, source) : false;
    };
    scrollable_ = AceType::MakeRefPtr<Scrollable>(
        callback, useScrollable_ == SCROLLABLE::HORIZONTAL ? Axis::HORIZONTAL : Axis::VERTICAL);
    scrollable_->Initialize(context_);
}

bool RenderGridScrollLayout::UpdateScrollPosition(double offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        return true;
    }

    if (NearZero(offset)) {
        return true;
    }

    if (reachHead_ && reachTail_) {
        return false;
    }

    if (offset > 0.0) {
        if (reachHead_) {
            return false;
        }
        reachTail_ = false;
    } else {
        if (reachTail_) {
            return false;
        }
        reachHead_ = false;
    }

    currentOffset_ += offset;
    MarkNeedLayout(true);
    return true;
}

void RenderGridScrollLayout::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (!GetVisible()) {
        return;
    }
    if (!scrollable_ || !scrollable_->Available()) {
        return;
    }
    scrollable_->SetCoordinateOffset(coordinateOffset);
    scrollable_->SetDragTouchRestrict(touchRestrict);
    result.emplace_back(scrollable_);
}

void RenderGridScrollLayout::SetChildPosition(
    const RefPtr<RenderNode>& child, int32_t main, int32_t cross, int32_t mainSpan, int32_t crossSpan)
{
    // Calculate the position for current child.
    double positionMain = 0.0;
    double positionCross = 0.0;
    for (int32_t i = startIndex_; i < main; ++i) {
        positionMain += GetSize(gridCells_.at(i).at(0));
    }
    positionMain += (main - startIndex_) * (*mainGap_);
    for (int32_t i = 0; i < cross; ++i) {
        positionCross += GetSize(gridCells_.at(main).at(i), false);
    }
    positionCross += cross * (*crossGap_);

    // Calculate the size for current child.
    double mainLen = 0.0;
    double crossLen = 0.0;
    for (int32_t i = 0; i < mainSpan; ++i) {
        mainLen += GetSize(gridCells_.at(main + i).at(0));
    }

    mainLen += (mainSpan - 1) * (*mainGap_);
    for (int32_t i = 0; i < crossSpan; ++i) {
        crossLen += GetSize(gridCells_.at(main).at(cross + i), false);
    }
    crossLen += (crossSpan - 1) * (*crossGap_);

    // If RTL, place the item from right.
    if (rightToLeft_) {
        if (useScrollable_ != SCROLLABLE::HORIZONTAL) {
            positionCross = colSize_ - positionCross - crossLen;
        }
    }

    double mainOffset = (mainLen - GetSize(child->GetLayoutSize())) / 2.0;
    double crosstOffset = (crossLen - GetSize(child->GetLayoutSize(), false)) / 2.0;

    Offset offset;
    if (useScrollable_ != SCROLLABLE::HORIZONTAL) {
        offset = Offset(positionCross + crosstOffset, positionMain + mainOffset - firstItemOffset_);
    } else {
        offset = Offset(positionMain + mainOffset - firstItemOffset_, positionCross + crosstOffset);
    }

    child->SetPosition(offset);
}

int32_t RenderGridScrollLayout::GetItemMainIndex(const RefPtr<RenderNode>& child, bool isMain) const
{
    if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        if (isMain) {
            return GetItemColumnIndex(child);
        } else {
            return GetItemRowIndex(child);
        }
    } else {
        if (isMain) {
            return GetItemRowIndex(child);
        } else {
            return GetItemColumnIndex(child);
        }
    }
}

void RenderGridScrollLayout::SetMainSize(Size& dst, const Size& src)
{
    if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        dst.SetWidth(src.Width());
    } else {
        dst.SetHeight(src.Height());
    }
}

double RenderGridScrollLayout::GetSize(const Size& src, bool isMain) const
{
    if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        return isMain ? src.Width() : src.Height();
    }

    return isMain ? src.Height() : src.Width();
}

bool RenderGridScrollLayout::GetGridSize()
{
    double rowSize = ((gridHeight_ > 0.0) && (gridHeight_ < GetLayoutParam().GetMaxSize().Height()))
                         ? gridHeight_
                         : GetLayoutParam().GetMaxSize().Height();
    double colSize = ((gridWidth_ > 0.0) && (gridWidth_ < GetLayoutParam().GetMaxSize().Width()))
                         ? gridWidth_
                         : GetLayoutParam().GetMaxSize().Width();

    if (NearEqual(rowSize_, Size::INFINITE_SIZE)) {
        if ((rowsArgs_.find(UNIT_PERCENT) != std::string::npos || rowsArgs_.find(UNIT_RATIO) != std::string::npos)) {
            rowSize = viewPort_.Height();
        }
    } else if (rowsArgs_.empty()) {
        useScrollable_ = SCROLLABLE::VERTICAL;
    }
    if (NearEqual(colSize_, Size::INFINITE_SIZE)) {
        if ((colsArgs_.find(UNIT_PERCENT) != std::string::npos || colsArgs_.find(UNIT_RATIO) != std::string::npos)) {
            colSize = viewPort_.Width();
        }
    } else if (colsArgs_.empty()) {
        useScrollable_ = SCROLLABLE::HORIZONTAL;
        mainSize_ = &colSize_;
        crossSize_ = &rowSize_;
        mainCount_ = &colCount_;
        crossCount_ = &rowCount_;
        crossGap_ = &rowGap_;
        mainGap_ = &colGap_;
    }
    LOGD("GetGridSize %lf, %lf   [%lf- %lf]", rowSize, colSize, rowSize_, colSize_);
    if (rowSize != rowSize_ || colSize != colSize_) {
        rowSize_ = rowSize;
        colSize_ = colSize;
        CreateScrollable();
        return true;
    }
    return false;
}

void RenderGridScrollLayout::BuildGrid(std::vector<double>& main, std::vector<double>& cross)
{
    if (useScrollable_ == SCROLLABLE::NO_SCROLL) {
        main = ParseArgs(PreParseRows(), rowSize_, rowGap_);
        cross = ParseArgs(PreParseCols(), colSize_, colGap_);
    } else if (useScrollable_ == SCROLLABLE::VERTICAL) {
        cross = ParseArgs(PreParseCols(), colSize_, colGap_);
        int32_t col = 0;
        for (auto width : cross) {
            metaData_[col] = Size(width, Size::INFINITE_SIZE);
            ++col;
        }
    } else if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        cross = ParseArgs(PreParseRows(), rowSize_, rowGap_);
        int32_t row = 0;
        for (auto height : cross) {
            metaData_[row] = Size(Size::INFINITE_SIZE, height);
            ++row;
        }
    }

    if (main.empty()) {
        main.push_back(*mainSize_);
    }
    if (cross.empty()) {
        cross.push_back(*crossSize_);
    }
}

void RenderGridScrollLayout::InitialGridProp()
{
    // Not first time layout after update, no need to initial.
    if (!GetGridSize() && !updateFlag_) {
        return;
    }
    ACE_SCOPED_TRACE("InitialGridProp");
    rowGap_ = NormalizePercentToPx(userRowGap_, true);
    colGap_ = NormalizePercentToPx(userColGap_, false);
    gridMatrix_.clear();
    std::vector<double> main;
    std::vector<double> cross;
    BuildGrid(main, cross);

    // Initialize the columnCount and rowCount, default is 1
    *crossCount_ = cross.size();
    *mainCount_ = main.size();
    gridCells_.clear();
    if (useScrollable_ != SCROLLABLE::NO_SCROLL) {
        gridCells_[0] = metaData_;
    }
    UpdateAccessibilityAttr();
    if (buildChildByIndex_) {
        if (startIndex_ > 0) {
            for (int32_t main = 0; main < startIndex_; main++) {
                SupplementItems(main);
            }
            BuildLazyGridLayout(startIndex_, *mainSize_ + firstItemOffset_);
        } else {
            BuildLazyGridLayout(0, *mainSize_);
        }

    } else {
        BuildNoLazyGridLayout();
    }
    updateFlag_ = false;
}

double RenderGridScrollLayout::BuildLazyGridLayout(int32_t index, double sizeNeed)
{
    if (!buildChildByIndex_ || index < 0 || NearZero(sizeNeed)) {
        return 0.0;
    }

    double size = 0.0;
    int32_t startIndex = index;
    while (size < sizeNeed) {
        auto suppleSize = SupplementItems(startIndex);
        if (NearZero(suppleSize)) {
            break;
        }
        *mainCount_ = ++startIndex;
        size += suppleSize + *mainGap_;
    }

    return size;
}

void RenderGridScrollLayout::BuildNoLazyGridLayout()
{
    int32_t mainIndex = 0;
    int32_t crossIndex = 0;
    int32_t itemIndex = 0;
    reachTail_ = false;
    items_.clear();
    for (const auto& item : RenderGridLayout::GetChildren()) {
        auto child = item;
        auto gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(child);
        while (!gridLayoutItem) {
            if (child->GetChildren().empty()) {
                break;
            }
            child = child->GetChildren().front();
            gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(child);
        }

        if (!gridLayoutItem) {
            continue;
        }
        gridLayoutItem->SetBoundary();

        int32_t itemMain = GetItemMainIndex(item, true);
        int32_t itemCross = GetItemMainIndex(item, false);
        int32_t itemMainSpan = GetItemSpan(gridLayoutItem, useScrollable_ != SCROLLABLE::HORIZONTAL);
        int32_t itemCrossSpan = GetItemSpan(gridLayoutItem, useScrollable_ == SCROLLABLE::HORIZONTAL);
        if (itemMainSpan > *mainCount_ || itemCrossSpan > *crossCount_) {
            continue;
        }
        if (itemMain >= 0 && itemCross >= 0 && itemCross < *crossCount_ &&
            CheckGridPlaced(itemIndex, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
            LayoutChild(item, itemMain, itemCross, itemMainSpan, itemCrossSpan);
        } else {
            while (!CheckGridPlaced(itemIndex, mainIndex, crossIndex, itemMainSpan, itemCrossSpan)) {
                GetNextGird(mainIndex, crossIndex);
                if (mainIndex >= *mainCount_) {
                    for (int32_t i = *mainCount_; mainIndex >= *mainCount_; i++) {
                        gridCells_[(*mainCount_)++] = metaData_;
                    }
                }
                if (crossIndex >= *crossCount_) {
                    break;
                }
            }
            if (mainIndex >= *mainCount_ || crossIndex >= *crossCount_) {
                DisableChild(item, itemIndex);
                continue;
            }
            LayoutChild(item, mainIndex, crossIndex, itemMainSpan, itemCrossSpan);
        }
        SetItemIndex(item, itemIndex); // Set index for focus adjust.
        items_[itemIndex] = item;
        ++itemIndex;
    }
}

bool RenderGridScrollLayout::CheckGridPlaced(
    int32_t index, int32_t main, int32_t cross, int32_t& mainSpan, int32_t& crossSpan)
{
    LOGD("CheckGridPlaced %{public}d %{public}d %{public}d %{public}d %{public}d", index, main, cross, mainSpan,
        crossSpan);
    auto mainIter = gridMatrix_.find(main);
    if (mainIter != gridMatrix_.end()) {
        auto crossIter = mainIter->second.find(cross);
        if (crossIter != mainIter->second.end()) {
            return false;
        }
    }
    if (cross + crossSpan > *crossCount_) {
        return false;
    }

    for (int32_t i = 0; i < mainSpan; i++) {
        mainIter = gridMatrix_.find(i + main);
        if (mainIter != gridMatrix_.end()) {
            for (int32_t j = 0; j < crossSpan; j++) {
                if (mainIter->second.find(j + cross) != mainIter->second.end()) {
                    return false;
                }
            }
        }
    }

    for (int32_t i = main; i < main + mainSpan; ++i) {
        std::map<int32_t, int32_t> mainMap;
        auto iter = gridMatrix_.find(i);
        if (iter != gridMatrix_.end()) {
            mainMap = iter->second;
        }
        for (int32_t j = cross; j < cross + crossSpan; ++j) {
            mainMap.emplace(std::make_pair(j, index));
        }
        gridMatrix_[i] = mainMap;
    }
    LOGD("CheckGridPlaced done %{public}d %{public}d %{public}d %{public}d %{public}d", index, main, cross, mainSpan,
        crossSpan);
    return true;
}

void RenderGridScrollLayout::LayoutChild(
    const RefPtr<RenderNode>& child, int32_t main, int32_t cross, int32_t mainSpan, int32_t crossSpan)
{
    child->Layout(MakeInnerLayoutParam(main, cross, mainSpan, crossSpan));
    SetMainSize(gridCells_.at(main).at(cross), child->GetLayoutSize());
    if (GetSize(gridCells_.at(main).at(0)) < GetSize(gridCells_.at(main).at(cross))) {
        SetMainSize(gridCells_.at(main).at(0), gridCells_.at(main).at(cross));
    }
}

void RenderGridScrollLayout::GetNextGird(int32_t& curMain, int32_t& curCross) const
{
    ++curCross;
    if (curCross >= *crossCount_) {
        curCross = 0;
        ++curMain;
    }
}

LayoutParam RenderGridScrollLayout::MakeInnerLayoutParam(
    int32_t main, int32_t cross, int32_t mainSpan, int32_t crossSpan) const
{
    LayoutParam innerLayout;
    double mainLen = 0.0;
    double crossLen = 0.0;
    for (int32_t i = 0; i < mainSpan; ++i) {
        mainLen += GetSize(gridCells_.at(main + i).at(cross));
    }
    mainLen += (mainSpan - 1) * (*mainGap_);
    for (int32_t i = 0; i < crossSpan; ++i) {
        crossLen += GetSize(gridCells_.at(main).at(cross + i), false);
    }
    crossLen += (crossSpan - 1) * (*crossGap_);

    Size size;
    if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        size = Size(mainLen, crossLen);
    } else {
        size = Size(crossLen, mainLen);
    }
    if (crossAxisAlign_ == FlexAlign::STRETCH) {
        innerLayout.SetMinSize(size);
        innerLayout.SetMaxSize(size);
    } else {
        innerLayout.SetMaxSize(size);
    }
    return innerLayout;
}

void RenderGridScrollLayout::CaculateViewPort()
{
    while (!NearZero(currentOffset_)) {
        if (currentOffset_ > 0) {
            // move to top/left of first row/column
            if (!NearZero(firstItemOffset_)) {
                currentOffset_ += GetSize(gridCells_.at(startIndex_++).at(0)) + *mainGap_ - firstItemOffset_;
                firstItemOffset_ = 0.0;
            }
            // Move up
            while (startIndex_ > 0 && currentOffset_ > 0) {
                currentOffset_ -= GetSize(gridCells_.at(startIndex_-- - 1).at(0)) + *mainGap_;
            }
            if (currentOffset_ < 0) {
                firstItemOffset_ -= currentOffset_;
            } else {
                reachHead_ = true;
            }
            currentOffset_ = 0.0;
        } else {
            if (!NearZero(firstItemOffset_)) {
                currentOffset_ -= firstItemOffset_;
                firstItemOffset_ = 0.0;
            }
            // Move down
            while (startIndex_ < *mainCount_ && currentOffset_ < 0) {
                currentOffset_ += GetSize(gridCells_.at(startIndex_++).at(0)) + *mainGap_;
            }
            if (currentOffset_ > 0) {
                firstItemOffset_ = GetSize(gridCells_.at(--startIndex_).at(0)) + *mainGap_ - currentOffset_;
            }
            currentOffset_ = 0.0;

            auto blank = CalculateBlankOfEnd();
            if (GreatOrEqual(0.0, blank)) {
                return;
            }

            // request new item.
            blank -= BuildLazyGridLayout(*mainCount_, blank);
            if (blank < 0) {
                return;
            }

            // Move up
            while (blank > 0 && startIndex_ > 0) {
                blank -= GetSize(gridCells_.at(--startIndex_).at(0)) + *mainGap_;
            }
            if (blank < 0) {
                firstItemOffset_ -= blank;
            } else {
                firstItemOffset_ = 0;
            }
            reachTail_ = true;
        }
    }
}

double RenderGridScrollLayout::CalculateBlankOfEnd()
{
    double drawLength = 0.0 - firstItemOffset_;
    for (int32_t main = startIndex_; main < *mainCount_; main++) {
        drawLength += GetSize(gridCells_.at(main).at(0)) + *mainGap_;
        if (GreatOrEqual(drawLength, *mainSize_)) {
            break;
        }
    }
    return *mainSize_ - drawLength;
}

double RenderGridScrollLayout::SupplementItems(int32_t index, bool needGridLayout)
{
    ACE_SCOPED_TRACE("SupplementItems %d", index);
    auto itor = gridCells_.try_emplace(index, metaData_);
    if (!itor.second && !needGridLayout) {
        auto iter = gridMatrix_.find(index);
        if (iter != gridMatrix_.end()) {
            for (const auto& item : iter->second) {
                if (items_.find(item.second) == items_.end()) {
                    if (buildChildByIndex_(item.second)) {
                        int32_t itemRowSpan = GetItemSpan(items_[item.second], true);
                        int32_t itemColSpan = GetItemSpan(items_[item.second], false);
                        LayoutChild(items_[item.second], index, item.first, itemRowSpan, itemColSpan);
                    }
                }
            }
            inCache_.insert(index);
            return NearEqual(GetSize(gridCells_[index][0]), Size::INFINITE_SIZE) ? 0.0 : GetSize(gridCells_[index][0]);
        }
    }
    int32_t itemIndex = 0;
    if (index > 0) {
        for (int32_t cross = *crossCount_ - 1; cross >= 0; cross--) {
            auto iter = gridMatrix_[index - 1].find(cross);
            if (iter != gridMatrix_[index - 1].end()) {
                itemIndex = iter->second + 1;
                break;
            }
        }
    }
    bool isFilled = false;
    int32_t mainIndex = index;
    int32_t crossIndex = 0;

    while (!isFilled && (items_.find(itemIndex) != items_.end() || buildChildByIndex_(itemIndex))) {
        auto item = items_[itemIndex];
        int32_t itemMain = GetItemMainIndex(item, true);
        int32_t itemCross = GetItemMainIndex(item, false);
        int32_t itemMainSpan = GetItemSpan(item, useScrollable_ != SCROLLABLE::HORIZONTAL);
        int32_t itemCrossSpan = GetItemSpan(item, useScrollable_ == SCROLLABLE::HORIZONTAL);
        if (itemCrossSpan > *crossCount_) {
            itemIndex++;
            continue;
        }
        LOGD("itemRow %d itemCol %d   itemRowSpan %d itemColSpan %d", itemMain, itemCross, itemMainSpan, itemCrossSpan);
        if (itemMain >= 0 && itemCross >= 0 && itemCross < *crossCount_ &&
            CheckGridPlaced(itemIndex, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
            LayoutChild(item, itemMain, itemCross, itemMainSpan, itemCrossSpan);
        } else {
            while (!CheckGridPlaced(itemIndex, mainIndex, crossIndex, itemMainSpan, itemCrossSpan)) {
                GetNextGird(mainIndex, crossIndex);
                if (mainIndex > index) {
                    isFilled = true;
                    break;
                }
            }
            if (!isFilled) {
                LayoutChild(item, mainIndex, crossIndex, itemMainSpan, itemCrossSpan);
            }
        }
        itemIndex++;
    }
    inCache_.insert(index);
    return NearEqual(GetSize(gridCells_[index][0]), Size::INFINITE_SIZE) ? 0.0 : GetSize(gridCells_[index][0]);
}

void RenderGridScrollLayout::PerformLayout()
{
    if (rowsArgs_.empty() && colsArgs_.empty()) {
        return;
    }
    if (RenderGridLayout::GetChildren().empty() && !buildChildByIndex_) {
        return;
    }
    InitialGridProp();
    CaculateViewPort();
    showItem_.clear();
    childrenInRect_.clear();
    double drawLength = 0.0 - firstItemOffset_;
    int32_t main = startIndex_;
    for (; main < *mainCount_; main++) {
        if (gridCells_.find(main) == gridCells_.end()) {
            break;
        }
        for (int32_t cross = 0; cross < *crossCount_; cross++) {
            auto mainIter = gridMatrix_.find(main);
            if (mainIter == gridMatrix_.end()) {
                continue;
            }
            auto crossIter = mainIter->second.find(cross);
            if (crossIter == mainIter->second.end()) {
                continue;
            }
            if (buildChildByIndex_ && inCache_.count(main) == 0) {
                SupplementItems(main);
            }
            if (showItem_.count(crossIter->second) == 0) {
                showItem_.insert(crossIter->second);
                auto item = items_.find(crossIter->second);
                if (item != items_.end()) {
                    childrenInRect_.push_back(item->second);
                    int32_t itemMainSpan = GetItemSpan(item->second, useScrollable_ != SCROLLABLE::HORIZONTAL);
                    int32_t itemCrosspan = GetItemSpan(item->second, useScrollable_ == SCROLLABLE::HORIZONTAL);
                    SetChildPosition(item->second, main, cross, itemMainSpan, itemCrosspan);
                }
            }
        }
        drawLength += GetSize(gridCells_.at(main).at(0)) + *mainGap_;
        if (GreatOrEqual(drawLength, *mainSize_)) {
            break;
        }
    }
    SetLayoutSize(GetLayoutParam().Constrain(Size(colSize_, rowSize_)));
    endIndex_ = main;
    if (buildChildByIndex_ && deleteChildByIndex_) {
        DealCache(startIndex_, endIndex_);
    }
}

void RenderGridScrollLayout::DealCache(int32_t start, int32_t end)
{
    ACE_SCOPED_TRACE("DealCache[%d - %d]", start, end);
    for (int32_t i = start - 2; i >= 0; i--) {
        if (inCache_.count(i) != 0) {
            DeleteItems(i, false);
        } else {
            break;
        }
    }

    for (int32_t i = end + 2;; i++) {
        if (inCache_.count(i) != 0) {
            DeleteItems(i, true);
        } else {
            break;
        }
    }

    if (start >= 1 && inCache_.count(start - 1) == 0) {
        SupplementItems(start - 1);
    }
    if (inCache_.count(end + 1) == 0) {
        SupplementItems(end + 1);
    }
}

void RenderGridScrollLayout::DeleteItems(int32_t index, bool isTail)
{
    if (!deleteChildByIndex_) {
        return;
    }

    auto iter = gridMatrix_.find(index);
    if (iter == gridMatrix_.end()) {
        return;
    }
    auto iterCloser = gridMatrix_.find(index + (isTail ? 1 : -1));
    for (const auto& item : iter->second) {
        if (iterCloser != gridMatrix_.end() && iterCloser->second.find(item.second) != iterCloser->second.end()) {
            continue;
        }
        deleteChildByIndex_(item.second);
        RemoveChildByIndex(item.second);
    }

    inCache_.erase(index);
}

void RenderGridScrollLayout::ClearLayout()
{
    showItem_.clear();
    childrenInRect_.clear();
    inCache_.clear();

    updateFlag_ = true;
    reachHead_ = false;
    reachTail_ = false;
    startMainPos_ = 0.0;
    endMainPos_ = 0.0;
    currentOffset_ = 0.0;
    firstItemOffset_ = 0.0;
    startIndex_ = 0;
    endIndex_ = -1;

    colCount_ = 0;
    rowCount_ = 0;

    gridMatrix_.clear();
    gridCells_.clear();
}

void RenderGridScrollLayout::ClearItems()
{
    decltype(items_) items(std::move(items_));
    for (const auto& item : items) {
        deleteChildByIndex_(item.second);
        RemoveChildByIndex(item.second);
    }
}

void RenderGridScrollLayout::GetMinAndMaxIndex(int32_t& min, int32_t& max)
{
    for (const auto& item : items_) {
        if (item.first < min) {
            min = item.first;
        }
        if (item.first > max) {
            max = item.first;
        }
    }
}

int32_t RenderGridScrollLayout::GetItemMainIndex(int32_t index)
{
    for (const auto& main : gridMatrix_) {
        for (const auto& cross : main.second) {
            if (cross.second == index) {
                return main.first;
            }
        }
    }
    return -1;
}

void RenderGridScrollLayout::OnReload()
{
    ClearItems();
    ClearLayout();
    MarkNeedLayout();
}
void RenderGridScrollLayout::OnItemAdded(int32_t index)
{
    if (items_.empty()) {
        return;
    }

    int32_t min = -1;
    int32_t max = std::numeric_limits<int32_t>::max();
    GetMinAndMaxIndex(min, max);

    if (index <= max) {
        decltype(items_) items(std::move(items_));
        for (const auto& item : items) {
            if (item.first >= index) {
                items_.emplace(std::make_pair(item.first + 1, item.second));
            } else {
                items_.emplace(std::make_pair(item.first, item.second));
            }
        }
        MarkNeedLayout();
    }

    int32_t mainIndex = GetItemMainIndex(index);
    if (mainIndex == -1) {
        return;
    }

    for (int32_t main = mainIndex; main < *mainCount_; main++) {
        gridMatrix_.erase(main);
        gridCells_.erase(main);
    }
    for (int32_t main = mainIndex; main < endIndex_; main++) {
        SupplementItems(main);
    }
}

void RenderGridScrollLayout::OnItemDeleted(int32_t index)
{
    if (items_.empty()) {
        return;
    }
    RemoveChildByIndex(index);
    int32_t min = -1;
    int32_t max = std::numeric_limits<int32_t>::max();
    GetMinAndMaxIndex(min, max);

    if (index <= max) {
        decltype(items_) items(std::move(items_));
        for (const auto& item : items) {
            if (item.first >= index) {
                items_.emplace(std::make_pair(item.first - 1, item.second));
            } else {
                items_.emplace(std::make_pair(item.first, item.second));
            }
        }
        MarkNeedLayout();
    }

    int32_t mainIndex = GetItemMainIndex(index);
    if (mainIndex == -1) {
        return;
    }

    for (int32_t main = mainIndex; main < *mainCount_; main++) {
        gridMatrix_.erase(main);
        gridCells_.erase(main);
    }
    for (int32_t main = mainIndex; main < endIndex_; main++) {
        SupplementItems(main);
    }
}

void RenderGridScrollLayout::OnItemChanged(int32_t index)
{
    if (items_.empty()) {
        return;
    }
    if (!buildChildByIndex_ || !deleteChildByIndex_) {
        return;
    }
    int32_t min = -1;
    int32_t max = std::numeric_limits<int32_t>::max();
    GetMinAndMaxIndex(min, max);
    if (index <= max) {
        MarkNeedLayout();
    }
    const auto& iter = items_.find(index);
    if (iter != items_.end()) {
        buildChildByIndex_(index);
        auto item = AceType::DynamicCast<RenderGridLayoutItem>(iter->second);
        if (item && item->ForceRebuild()) {
            deleteChildByIndex_(index);
            RemoveChildByIndex(index);
        }
    }

    int32_t mainIndex = GetItemMainIndex(index);
    if (mainIndex == -1) {
        return;
    }

    for (int32_t main = mainIndex; main < *mainCount_; main++) {
        gridMatrix_.erase(main);
        gridCells_.erase(main);
    }
    for (int32_t main = mainIndex; main < endIndex_; main++) {
        SupplementItems(main);
    }
}

void RenderGridScrollLayout::OnItemMoved(int32_t from, int32_t to)
{
    int32_t min = -1;
    int32_t max = std::numeric_limits<int32_t>::max();
    GetMinAndMaxIndex(min, max);
    if (from <= max || to <= max) {
        MarkNeedLayout();
    }
    int32_t front = from > to ? to : from;

    RemoveChildByIndex(from);
    RemoveChildByIndex(to);

    int32_t mainIndex = GetItemMainIndex(front);
    if (mainIndex == -1) {
        return;
    }

    for (int32_t main = mainIndex; main < *mainCount_; main++) {
        gridMatrix_.erase(main);
        gridCells_.erase(main);
    }
    for (int32_t main = mainIndex; main < endIndex_; main++) {
        SupplementItems(main);
    }
}

void RenderGridScrollLayout::UpdateTouchRect()
{
    touchRect_.SetSize(GetLayoutSize());
    touchRect_.SetOffset(GetPosition());
    ownTouchRect_ = touchRect_;
}

} // namespace OHOS::Ace
