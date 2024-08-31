/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "core/components_v2/grid/render_grid_scroll.h"

#include "base/log/event_report.h"
#include "core/common/text_field_manager.h"
#include "core/components_v2/grid/grid_scroll_controller.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace::V2 {

namespace {

const char UNIT_PERCENT[] = "%";
const char UNIT_RATIO[] = "fr";
constexpr int32_t TIME_THRESHOLD = 3 * 1000000; // 3 millisecond
constexpr double JUMP_INDEX_THRESHOLD = 2.0;

} // namespace

RenderGridScroll::~RenderGridScroll()
{
    if (scrollBarProxy_) {
        scrollBarProxy_->UnRegisterScrollableNode(AceType::WeakClaim(this));
    }
}

void RenderGridScroll::Update(const RefPtr<Component>& component)
{
    component_ = AceType::DynamicCast<GridLayoutComponent>(component);
    ACE_DCHECK(component_);
    if (!NeedUpdate(component)) {
        InitScrollBar();
        return;
    }
    useScrollable_ = SCROLLABLE::NO_SCROLL;
    mainSize_ = &rowSize_;
    crossSize_ = &colSize_;
    mainCount_ = &rowCount_;
    crossCount_ = &colCount_;
    crossGap_ = &colGap_;
    mainGap_ = &rowGap_;
    startRankItemIndex_ = 0;
    currentItemIndex_ = 0;
    // maybe change ItemIndex
    ApplyRestoreInfo();
    RenderGridLayout::Update(component);
    FindRefreshParent(AceType::WeakClaim(this));
    InitScrollBar();
    TakeBoundary();
    const RefPtr<GridLayoutComponent> grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (!grid) {
        LOGE("RenderGridLayout update failed.");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }
    scrolledEventFun_ =
        AceAsyncEvent<void(const std::shared_ptr<GridEventInfo>&)>::Create(grid->GetScrolledEvent(), context_);

    scrollBarProxy_ = grid->GetScrollBarProxy();
    InitScrollBarProxy();
}

bool RenderGridScroll::NeedUpdate(const RefPtr<Component>& component)
{
    const RefPtr<GridLayoutComponent> grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (!grid) {
        LOGE("RenderGridLayout update failed.");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return false;
    }
    auto controller = grid->GetController();
    if (controller) {
        controller->SetScrollNode(WeakClaim(this));
    }
    if (!animator_) {
        animator_ = CREATE_ANIMATOR(GetContext());
    }
    cacheCount_ = grid->GetCacheCount();

    if (direction_ != grid->GetDirection() || crossAxisAlign_ != grid->GetFlexAlign() ||
        gridWidth_ != grid->GetWidth() || gridHeight_ != grid->GetHeight() || colsArgs_ != grid->GetColumnsArgs() ||
        rowsArgs_ != grid->GetRowsArgs() || userColGap_ != grid->GetColumnGap() || userRowGap_ != grid->GetRowGap() ||
        rightToLeft_ != grid->GetRightToLeft()) {
        return true;
    }
    return false;
}

void RenderGridScroll::AddChildByIndex(int32_t index, const RefPtr<RenderNode>& renderNode)
{
    auto iter = items_.try_emplace(index, renderNode);
    if (iter.second) {
        AddChild(renderNode);
        RefPtr<RenderGridLayoutItem> node = AceType::DynamicCast<RenderGridLayoutItem>(renderNode);
        if (node) {
            node->SetBoundary();
            node->SetIndex(index);
            node->SetHidden(false);
        }
    }
}

void RenderGridScroll::CreateScrollable()
{
    scrollable_ = nullptr;
    if (useScrollable_ == SCROLLABLE::NO_SCROLL) {
        return;
    }

    auto callback = [weak = AceType::WeakClaim(this)](double offset, int32_t source) {
        auto grid = weak.Upgrade();
        if (!grid) {
            return false;
        }
        // Stop animator of scroll bar.
        auto scrollBarProxy = grid->scrollBarProxy_;
        if (scrollBarProxy) {
            scrollBarProxy->StopScrollBarAnimator();
        }
        return grid->UpdateScrollPosition(offset, source);
    };
    scrollable_ = AceType::MakeRefPtr<Scrollable>(
        callback, useScrollable_ == SCROLLABLE::HORIZONTAL ? Axis::HORIZONTAL : Axis::VERTICAL);
    scrollable_->SetScrollEndCallback([weak = AceType::WeakClaim(this)]() {
        auto grid = weak.Upgrade();
        if (grid) {
            auto proxy = grid->scrollBarProxy_;
            if (proxy) {
                proxy->StartScrollBarAnimator();
            }
            auto scrollBar = grid->scrollBar_;
            if (scrollBar) {
                scrollBar->HandleScrollBarEnd();
            }
        }
    });
    InitializeScrollable(scrollable_);
    scrollable_->Initialize(context_);
}

void RenderGridScroll::CheckJumpToIndex(double offset)
{
    int32_t index = startShowItemIndex_;
    double dtIndex = -offset / estimateAverageHeight_;
    double remainOffset = 0.0;
    if (dtIndex >= 0) {
        auto idx = static_cast<int32_t>(dtIndex);
        index = endShowItemIndex_ + idx;
        if (index >= GetItemTotalCount()) {
            index = GetItemTotalCount() - 1;
        } else {
            remainOffset = -offset - idx * estimateAverageHeight_;
        }
    } else {
        auto idx = static_cast<int32_t>(-dtIndex);
        index = startShowItemIndex_ - idx;
        if (index < 0) {
            index = 0;
        } else {
            remainOffset = -offset + idx * estimateAverageHeight_;
        }
    }
    int32_t rankIndex = GetStartingItem(index);
    if (((index - rankIndex) * estimateAverageHeight_) > (colSize_* JUMP_INDEX_THRESHOLD)) {
        currentOffset_ += offset;
        return;
    }
    ScrollToIndex(rankIndex);
    currentOffset_ = remainOffset + (index - rankIndex) * estimateAverageHeight_;
}

bool RenderGridScroll::UpdateScrollPosition(double offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        return true;
    }

    if (NearZero(offset)) {
        return true;
    }
    if (scrollBar_ && scrollBar_->NeedScrollBar()) {
        scrollBar_->SetActive(SCROLL_FROM_CHILD != source);
    }
    if (reachHead_ && HandleRefreshEffect(offset, source, currentOffset_)) {
        return false;
    }
    if (reachHead_ && reachTail_) {
        return false;
    }

    if (rightToLeft_ && useScrollable_ == SCROLLABLE::HORIZONTAL) {
        offset = -offset;
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
    // If the offset is from the scroll bar and is large, use scroll to index to improve performance
    if (source == SCROLL_FROM_BAR && std::abs(offset) > colSize_ * JUMP_INDEX_THRESHOLD) {
        CheckJumpToIndex(offset);
    } else {
        currentOffset_ += offset;
    }
    MarkNeedLayout(true);
    return true;
}

void RenderGridScroll::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (!GetVisible()) {
        return;
    }
    if (!scrollable_) {
        return;
    }
    if (scrollable_->Available() && scrollBar_ && scrollBar_->InBarRegion(globalPoint_ - coordinateOffset)) {
        scrollBar_->AddScrollBarController(coordinateOffset, result);
    } else {
        scrollable_->SetCoordinateOffset(coordinateOffset);
        scrollable_->SetDragTouchRestrict(touchRestrict);
    }
    result.emplace_back(scrollable_);
}

bool RenderGridScroll::IsChildrenTouchEnable()
{
    return scrollable_->IsMotionStop();
}

void RenderGridScroll::SetChildPosition(
    const RefPtr<RenderNode>& child, int32_t main, int32_t cross, int32_t mainSpan, int32_t crossSpan)
{
    // Calculate the position for current child.
    double positionMain = 0.0;
    double positionCross = 0.0;
    if (main < startIndex_) {
        positionMain -= GetSize(gridCells_.at(main).at(0));
        positionMain += (main - startIndex_) * (*mainGap_);
    } else {
        for (int32_t i = startIndex_; i < main; ++i) {
            positionMain += GetSize(gridCells_.at(i).at(0));
        }
        positionMain += (main - startIndex_) * (*mainGap_);
    }

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
        } else {
            positionMain = colSize_ - positionMain - mainLen;
        }
    }

    double mainOffset = (mainLen - GetSize(child->GetLayoutSize())) / 2.0;
    double crossOffset = (crossLen - GetSize(child->GetLayoutSize(), false)) / 2.0;

    Offset offset;
    if (useScrollable_ != SCROLLABLE::HORIZONTAL) {
        offset = Offset(positionCross + crossOffset, positionMain + mainOffset - firstItemOffset_);
    } else {
        if (rightToLeft_) {
            offset = Offset(positionMain + mainOffset + firstItemOffset_, positionCross + crossOffset);
        } else {
            offset = Offset(positionMain + mainOffset - firstItemOffset_, positionCross + crossOffset);
        }
    }

    child->SetPosition(offset);
}

int32_t RenderGridScroll::GetItemMainIndex(const RefPtr<RenderNode>& child, bool isMain) const
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

void RenderGridScroll::SetMainSize(Size& dst, const Size& src)
{
    if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        dst.SetWidth(src.Width());
    } else {
        dst.SetHeight(src.Height());
    }
}

double RenderGridScroll::GetSize(const Size& src, bool isMain) const
{
    if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        return isMain ? src.Width() : src.Height();
    }

    return isMain ? src.Height() : src.Width();
}

void RenderGridScroll::SizeChangeOffset(double newWindowHeight)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto textFieldManager = AceType::DynamicCast<TextFieldManager>(context->GetTextFieldManager());
    // only need to offset vertical lists
    if (textFieldManager && (useScrollable_ == SCROLLABLE::VERTICAL)) {
        // only when textField is onFocus
        if (!textFieldManager->GetOnFocusTextField().Upgrade()) {
            return;
        }
        auto position = textFieldManager->GetClickPosition().GetY();
        double offset = newWindowHeight + GetGlobalOffset().GetY() - position;
        if (LessOrEqual(offset, 0.0)) {
            // negative offset to scroll down
            textFieldOffset_ = offset;
        }
    }
}

bool RenderGridScroll::GetGridSize()
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
    if (rowSize != rowSize_ || colSize != colSize_) {
        rowSize_ = rowSize;
        colSize_ = colSize;
        CreateScrollable();
        SizeChangeOffset(rowSize);
        return true;
    }
    return false;
}

void RenderGridScroll::BuildGrid(std::vector<double>& main, std::vector<double>& cross)
{
    if (useScrollable_ == SCROLLABLE::NO_SCROLL) {
        main = ParseArgs(GetRowTemplate(), rowSize_, rowGap_);
        cross = ParseArgs(GetColumnsTemplate(), colSize_, colGap_);
    } else if (useScrollable_ == SCROLLABLE::VERTICAL) {
        cross = ParseArgs(GetColumnsTemplate(), colSize_, colGap_);
        int32_t col = 0;
        for (auto width : cross) {
            metaData_[col] = Size(width, Size::INFINITE_SIZE);
            ++col;
        }
    } else if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        cross = ParseArgs(GetRowTemplate(), rowSize_, rowGap_);
        int32_t row = 0;
        for (auto height : cross) {
            metaData_[row] = Size(Size::INFINITE_SIZE, height);
            ++row;
        }
    }
}

void RenderGridScroll::InitialGridProp()
{
    // Not first time layout after update, no need to initial.
    if (!GetGridSize() && !updateFlag_) {
        return;
    }
    ACE_SCOPED_TRACE("InitialGridProp");
    OnDataSourceUpdated(0);
    rowGap_ = NormalizePercentToPx(userRowGap_, true);
    colGap_ = NormalizePercentToPx(userColGap_, false);
    std::vector<double> main;
    std::vector<double> cross;
    BuildGrid(main, cross);

    // Initialize the columnCount and rowCount, default is 1
    *crossCount_ = cross.size();
    *mainCount_ = main.size();
    gridCells_.clear();
    items_.clear();
    UpdateAccessibilityAttr();
    if (buildChildByIndex_) {
        int32_t endIndex = -1;
        while (endIndex < currentItemIndex_) {
            if (!Rank(*mainCount_, *mainCount_ == 0 ? startRankItemIndex_ : -1)) {
                // When [firstLineToBottom_] does not equal to [std::nullopt], it indicates that this [InitialGridProp]
                // is called after [ScrollToIndex].
                // This is the case when it scrolls to the last line and the last line is not full.
                // So we need to add a line to [*mainCount_].
                (*mainCount_) += firstLineToBottom_ ? 1 : 0;
                break;
            }
            (*mainCount_)++;
            auto mainIter = gridMatrix_.find(*mainCount_ - 1);
            if (mainIter == gridMatrix_.end()) {
                break;
            }
            for (int32_t crossIndex = *crossCount_ - 1; crossIndex >= 0; crossIndex--) {
                auto iter = mainIter->second.find(crossIndex);
                if (iter != mainIter->second.end()) {
                    endIndex = iter->second;
                    break;
                }
            }
        }
        currentItemIndex_ = 0;

        SupplyItems(*mainCount_ > 0 ? *mainCount_ - 1 : 0);
        startIndex_ = *mainCount_ > 0 ? *mainCount_ - 1 : 0;

        if (NearZero(currentOffset_)) {
            needCalculateViewPort_ = true;
        }
    }
    updateFlag_ = false;
    if (firstLineToBottom_ && firstLineToBottom_.value()) {
        // calculate the distance from the first line to the last line
        currentOffset_ = *mainSize_ - GetSize(gridCells_.at(0).at(0));
        needCalculateViewPort_ = false;
    }
    firstLineToBottom_ = std::nullopt;
}

double RenderGridScroll::BuildLazyGridLayout(int32_t index, double sizeNeed)
{
    if (!buildChildByIndex_ || index < 0 || NearZero(sizeNeed)) {
        return 0.0;
    }
    double size = 0.0;
    int32_t startIndex = index;
    while (size < sizeNeed) {
        auto suppleSize = SupplyItems(startIndex);
        if (NearZero(suppleSize)) {
            break;
        }
        *mainCount_ = ++startIndex;
        size += suppleSize + *mainGap_;
    }
    return size;
}

bool RenderGridScroll::CheckGridPlaced(
    int32_t index, int32_t main, int32_t cross, int32_t& mainSpan, int32_t& crossSpan)
{
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
    return true;
}

void RenderGridScroll::LayoutChild(const RefPtr<RenderNode>& child, int32_t main, int32_t cross, int32_t mainSpan,
    int32_t crossSpan, bool needPosition)
{
    auto gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(child);
    if (!gridLayoutItem) {
        LOGE("child of GridScroll is not GridLayoutItem!");
        return;
    }
    Dimension itemMainSize;
    if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        itemMainSize = gridLayoutItem->GetGridItemWidth();
    } else {
        itemMainSize = gridLayoutItem->GetGridItemHeight();
    }
    bool itemMainIsPercent = itemMainSize.Unit() == DimensionUnit::PERCENT;
    child->Layout(MakeInnerLayoutParam(main, cross, mainSpan, crossSpan, itemMainIsPercent));
    SetMainSize(gridCells_.at(main).at(cross), child->GetLayoutSize());
    if (GetSize(gridCells_.at(main).at(0)) < GetSize(gridCells_.at(main).at(cross))) {
        SetMainSize(gridCells_.at(main).at(0), gridCells_.at(main).at(cross));
    }
    if (!needPosition) {
        return;
    }
    if (useScrollable_ != SCROLLABLE::HORIZONTAL) {
        child->SetPosition(Offset(0, *mainSize_ + *mainGap_));
    } else {
        child->SetPosition(Offset(*mainSize_ + *mainGap_, 0));
    }
}

void RenderGridScroll::GetNextGrid(int32_t& curMain, int32_t& curCross) const
{
    ++curCross;
    if (curCross >= *crossCount_) {
        curCross = 0;
        ++curMain;
    }
}

void RenderGridScroll::GetPreviousGrid(int32_t& curMain, int32_t& curCross)
{
    --curCross;
    if (curCross < 0) {
        curCross = *crossCount_;
        --curMain;
    }
}

LayoutParam RenderGridScroll::MakeInnerLayoutParam(
    int32_t main, int32_t cross, int32_t mainSpan, int32_t crossSpan, bool itemIsPercentUnit) const
{
    LayoutParam innerLayout;
    double mainLen = 0.0;
    double crossLen = 0.0;
    if (itemIsPercentUnit) {
        auto maxMainSize = GetSize(GetLayoutParam().GetMaxSize());
        mainLen += Size::IsValueInfinite(maxMainSize) ? GetSize(viewPort_) : maxMainSize;
    } else {
        for (int32_t i = 0; i < mainSpan; ++i) {
            if (gridCells_.find(main + i) != gridCells_.end() &&
                gridCells_.at(main + i).find(cross) != gridCells_.at(main + i).end()) {
                mainLen += GetSize(gridCells_.at(main + i).at(cross));
            }
        }
        mainLen += (mainSpan - 1) * (*mainGap_);
    }
    for (int32_t i = 0; i < crossSpan; ++i) {
        if (gridCells_.find(main) != gridCells_.end() &&
            gridCells_.at(main).find(cross + i) != gridCells_.at(main).end()) {
            crossLen += GetSize(gridCells_.at(main).at(cross + i), false);
        }
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

void RenderGridScroll::LoadForward()
{
    auto firstItem = GetStartingItem(startRankItemIndex_ - 1);

    decltype(gridCells_) gridCells(std::move(gridCells_));
    decltype(gridMatrix_) gridMatrix(std::move(gridMatrix_));

    int32_t count = 0;
    int32_t endIndex = -1;
    while (endIndex < startRankItemIndex_ - 1) {
        if (!Rank(count, count == 0 ? firstItem : -1)) {
            break;
        }
        count++;
        auto mainIter = gridMatrix_.find(count - 1);
        if (mainIter == gridMatrix_.end()) {
            break;
        }
        for (int32_t cross = *crossCount_ - 1; cross >= 0; cross--) {
            auto iter = mainIter->second.find(cross);
            if (iter != mainIter->second.end()) {
                endIndex = iter->second;
                break;
            }
        }
    }
    startRankItemIndex_ = firstItem;
    if (count == 0) {
        return;
    }
    for (const auto& item : gridMatrix) {
        gridMatrix_[item.first + count] = item.second;
    }
    for (const auto& item : gridCells) {
        gridCells_[item.first + count] = item.second;
    }

    decltype(inCache_) inCache(std::move(inCache_));
    for (const auto& item : inCache) {
        inCache_.insert(item + count);
    }

    *mainCount_ += count;
    startIndex_ += count;
}

void RenderGridScroll::CalculateViewPort()
{
    if (textFieldOffset_) {
        currentOffset_ += textFieldOffset_.value();
        textFieldOffset_.reset();
    }
    while (!NearZero(currentOffset_) || needCalculateViewPort_) {
        if (currentOffset_ > 0) {
            // [currentOffset_] > 0  means grid items are going to move down
            // move to top/left of first row/column
            if (!NearZero(firstItemOffset_)) {
                if (gridCells_.find(startIndex_ + 1) != gridCells_.end()) {
                    currentOffset_ += GetSize(gridCells_.at(startIndex_++).at(0)) + *mainGap_ - firstItemOffset_;
                }
                firstItemOffset_ = 0.0;
            }
            while (currentOffset_ > 0) {
                if (startIndex_ > 0) {
                    if (gridCells_.find(startIndex_ - 1) == gridCells_.end()) {
                        SupplyItems(startIndex_ - 1);
                    }
                    currentOffset_ -= GetSize(gridCells_.at(startIndex_-- - 1).at(0)) + *mainGap_;
                }
                if (startIndex_ == 0 && startRankItemIndex_ > 0 && currentOffset_ > 0) {
                    LoadForward();
                }
                if (startIndex_ == 0) {
                    break;
                }
            }
            if (currentOffset_ < 0) {
                firstItemOffset_ -= currentOffset_;
            } else {
                if (startIndex_ == 0) {
                    reachHead_ = true;
                }
            }
            currentOffset_ = 0.0;

            auto blank = CalculateBlankOfEnd();
            if (GreatOrEqual(0.0, blank)) {
                return;
            }
            // request new item until the blank is filled up
            blank -= BuildLazyGridLayout(*mainCount_, blank);
            if (LessOrEqual(blank, 0)) {
                return;
            }
        } else {
            // [currentOffset_] <= 0  means grid items are going to move up.
            if (!NearZero(firstItemOffset_)) {
                currentOffset_ -= firstItemOffset_;
                firstItemOffset_ = 0.0;
            }
            // step1: move [currentOffset_] to the last one of [gridCells_]
            while (startIndex_ < *mainCount_ && (currentOffset_ < 0 || needCalculateViewPort_)) {
                currentOffset_ += GetSize(gridCells_.at(startIndex_++).at(0)) + *mainGap_;
            }
            needCalculateViewPort_ = false;
            // step2: if [currentOffset_] is positive, it means that we've had enough grid items
            if (currentOffset_ > 0) {
                firstItemOffset_ = GetSize(gridCells_.at(--startIndex_).at(0)) + *mainGap_ - currentOffset_;
                currentOffset_ = 0.0;
            } else {
                // step3: if [currentOffset_] is non-positive, it means we need to build more grid items
                if (!GreatOrEqual(0.0, BuildLazyGridLayout(*mainCount_, -currentOffset_))) {
                    continue;
                }
            }
            currentOffset_ = 0.0;
            auto blank = CalculateBlankOfEnd();
            if (GreatOrEqual(0.0, blank)) {
                return;
            }
            // request new item until the blank is filled up
            blank -= BuildLazyGridLayout(*mainCount_, blank);
            if (LessOrEqual(blank, 0)) {
                return;
            }
            blank = blank - firstItemOffset_;
            firstItemOffset_ = 0;
            // Move up
            while (blank > 0) {
                if (startIndex_ == 0 && startRankItemIndex_ > 0) {
                    LoadForward();
                }
                if (startIndex_ == 0) {
                    break;
                }
                if (gridCells_.find(startIndex_ - 1) == gridCells_.end()) {
                    SupplyItems(startIndex_ - 1);
                }
                blank -= GetSize(gridCells_.at(--startIndex_).at(0)) + *mainGap_;
            }
            firstItemOffset_ -= blank;
            if (firstItemOffset_ < 0) {
                firstItemOffset_ = 0;
            }
            reachTail_ = true;
        }
    }
}

double RenderGridScroll::CalculateBlankOfEnd()
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

double RenderGridScroll::SupplyItems(int32_t mainIndex, int32_t itemIndex, bool needPosition)
{
    ACE_SCOPED_TRACE("SupplyItems %d", mainIndex);
    if (loadingIndex_ == mainIndex) {
        loadingIndex_ = -1;
    }
    if (gridMatrix_.find(mainIndex) == gridMatrix_.end()) {
        Rank(mainIndex, itemIndex);
    }
    gridCells_.try_emplace(mainIndex, metaData_);
    auto iter = gridMatrix_.find(mainIndex);
    if (iter != gridMatrix_.end()) {
        int32_t frontIndex = -1;
        for (const auto& item : iter->second) {
            if (item.second != frontIndex) {
                if (items_.find(item.second) != items_.end() || buildChildByIndex_(item.second)) {
                    int32_t itemRowSpan = GetItemSpan(items_[item.second], true);
                    int32_t itemColSpan = GetItemSpan(items_[item.second], false);
                    LayoutChild(items_[item.second], mainIndex, item.first, itemRowSpan, itemColSpan, needPosition);
                }
            }
            frontIndex = item.second;
        }
        inCache_.insert(mainIndex);
        return NearEqual(GetSize(gridCells_[mainIndex][0]), Size::INFINITE_SIZE) ? 0.0
                                                                                 : GetSize(gridCells_[mainIndex][0]);
    }
    return 0.0;
}

bool RenderGridScroll::Rank(int32_t mainIndex, int32_t itemIndex)
{
    if (gridMatrix_.find(mainIndex) != gridMatrix_.end()) {
        return true;
    }
    ACE_SCOPED_TRACE("Rank [%d]", mainIndex);
    if (itemIndex == -1) {
        auto mainIter = gridMatrix_.find(mainIndex - 1);
        if (mainIter != gridMatrix_.end()) {
            for (int32_t cross = *crossCount_ - 1; cross >= 0; cross--) {
                auto iter = mainIter->second.find(cross);
                if (iter != mainIter->second.end()) {
                    itemIndex = iter->second + 1;
                    break;
                }
            }
        }
    }
    if (itemIndex == -1) {
        LOGE("failed, itemIndex = -1, mainIndex = %d", mainIndex);
        return false;
    }

    bool isFilled = false;
    int32_t index = mainIndex;
    int32_t crossIndex = 0;
    while (!isFilled) {
        int32_t itemMain = -1;
        int32_t itemCross = -1;
        int32_t itemMainSpan = -1;
        int32_t itemCrossSpan = -1;
        auto item = items_.find(itemIndex);
        if (item != items_.end()) {
            itemMain = GetItemMainIndex(item->second, true);
            itemCross = GetItemMainIndex(item->second, false);
            itemMainSpan = GetItemSpan(item->second, useScrollable_ != SCROLLABLE::HORIZONTAL);
            itemCrossSpan = GetItemSpan(item->second, useScrollable_ == SCROLLABLE::HORIZONTAL);
        } else {
            if (!getChildSpanByIndex_(itemIndex, useScrollable_ == SCROLLABLE::HORIZONTAL, itemMain, itemCross,
                    itemMainSpan, itemCrossSpan)) {
                return false;
            }
        }

        if (itemCrossSpan > *crossCount_) {
            itemIndex++;
            continue;
        }
        if (itemMain >= 0 && itemCross >= 0 && itemCross < *crossCount_ &&
            CheckGridPlaced(itemIndex, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
        } else {
            while (!CheckGridPlaced(itemIndex, mainIndex, crossIndex, itemMainSpan, itemCrossSpan)) {
                GetNextGrid(mainIndex, crossIndex);
                if (mainIndex > index) {
                    isFilled = true;
                    break;
                }
            }
        }
        itemIndex++;
    }
    return true;
}

void RenderGridScroll::PerformLayout()
{
    if (rowsArgs_.empty() && colsArgs_.empty()) {
        return;
    }
    if (RenderGridLayout::GetChildren().empty() && !buildChildByIndex_) {
        return;
    }
    InitialGridProp();
    CalculateViewPort();
    showItem_.clear();
    childrenInRect_.clear();
    double drawLength = 0.0 - firstItemOffset_;
    int32_t main = startIndex_ > 0 ? startIndex_ - 1 : startIndex_;
    for (; main < *mainCount_; main++) {
        if (gridCells_.find(main) == gridCells_.end()) {
            continue;
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
                SupplyItems(main);
            }
            if (showItem_.count(crossIter->second) == 0) {
                showItem_.insert(crossIter->second);
                auto item = items_.find(crossIter->second);
                if (item != items_.end()) {
                    childrenInRect_.push_back(item->second);
                    int32_t itemMainSpan = GetItemSpan(item->second, useScrollable_ != SCROLLABLE::HORIZONTAL);
                    int32_t itemCrossSpan = GetItemSpan(item->second, useScrollable_ == SCROLLABLE::HORIZONTAL);
                    SetChildPosition(item->second, main, cross, itemMainSpan, itemCrossSpan);
                }
            }
        }
        if (main >= startIndex_) {
            drawLength += GetSize(gridCells_.at(main).at(0)) + *mainGap_;
        }
        if (GreatOrEqual(drawLength, *mainSize_)) {
            break;
        }
    }
    SetLayoutSize(GetLayoutParam().Constrain(Size(colSize_, rowSize_)));
    endIndex_ = main;
    MarkNeedPredictLayout();
    CalculateWholeSize(drawLength);

    if (rightToLeft_ && useScrollable_ == SCROLLABLE::HORIZONTAL) {
        lastOffset_ = estimateHeight_ - viewPort_.Width() - (startMainPos_ + firstItemOffset_ + currentOffset_);
    } else {
        lastOffset_ = estimatePos_ + startMainPos_ + firstItemOffset_ + currentOffset_;
    }

    int32_t firstIndex = GetIndexByPosition(0);
    if (lastFirstIndex_ != firstIndex) {
        if (!animatorJumpFlag_) {
            OnScrolled(firstIndex);
        }
        lastFirstIndex_ = firstIndex;
    }
    animatorJumpFlag_ = false;
}

void RenderGridScroll::DealCache(int32_t start, int32_t end)
{
    if (loadingIndex_ != -1) {
        return;
    }

    if (!inRankCache_.empty()) {
        std::set<int32_t> rankCache(std::move(inRankCache_));
        if (deleteChildByIndex_) {
            for (auto index : rankCache) {
                if (items_.find(index) == items_.end()) {
                    deleteChildByIndex_(index);
                }
            }
        }
    }

    std::set<int32_t> deleteItem;
    for (const auto& item : inCache_) {
        if (item < start - cacheCount_ || item > end + cacheCount_) {
            deleteItem.insert(item);
        }
    }

    for (const auto& item : deleteItem) {
        DeleteItems(item, false);
    }

    for (int32_t i = 1; i <= cacheCount_; i++) {
        if (inCache_.count(i + end) == 0) {
            loadingIndex_ = i + end;
            break;
        }

        if (start >= i && inCache_.count(start - i) == 0) {
            loadingIndex_ = start - i;
            break;
        }
    }
}

void RenderGridScroll::DeleteItems(int32_t index, bool isTail)
{
    if (!deleteChildByIndex_) {
        return;
    }

    auto iter = gridMatrix_.find(index);
    if (iter == gridMatrix_.end()) {
        return;
    }
    for (const auto& item : iter->second) {
        deleteChildByIndex_(item.second);
        RemoveChildByIndex(item.second);
    }

    inCache_.erase(index);
}

void RenderGridScroll::ClearLayout(bool needReservedPlace)
{
    if (needReservedPlace) {
        RecordLocation();
    } else {
        currentOffset_ = 0.0;
    }
    showItem_.clear();
    childrenInRect_.clear();
    inCache_.clear();

    updateFlag_ = true;
    reachHead_ = false;
    reachTail_ = false;
    startMainPos_ = 0.0;
    firstItemOffset_ = 0.0;
    startIndex_ = 0;
    endIndex_ = -1;
    lastOffset_ = 0.0;
    estimatePos_ = 0.0;
    estimateAverageHeight_ = 0.0;
    estimateHeight_ = 0.0;

    colCount_ = 0;
    rowCount_ = 0;

    gridMatrix_.clear();
    gridCells_.clear();
}

void RenderGridScroll::RecordLocation()
{
    double positionMain = 0.0;

    for (int32_t i = 0; i < startIndex_; ++i) {
        if (i < static_cast<int32_t>(gridCells_.size())) {
            positionMain += GetSize(gridCells_.at(i).at(0));
        }
    }
    positionMain += (startIndex_) * (*mainGap_);
    currentOffset_ += -positionMain - firstItemOffset_;
}

void RenderGridScroll::ClearItems()
{
    decltype(items_) items(std::move(items_));
    for (const auto& item : items) {
        if (item.first < startRankItemIndex_) {
            deleteChildByIndex_(item.first);
        } else {
            inRankCache_.emplace(item.first);
        }
        RemoveChildByIndex(item.first);
    }
    loadingIndex_ = -1;
}

int32_t RenderGridScroll::GetItemMainIndex(int32_t index)
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

int32_t RenderGridScroll::GetStartingItem(int32_t first)
{
    int32_t firstIndex = 0;
    int32_t index = first;
    int32_t itemMain = -1;
    int32_t itemCross = -1;
    int32_t itemMainSpan = -1;
    int32_t itemCrossSpan = -1;
    while (index > 0) {
        if (getChildSpanByIndex_(
                index, useScrollable_ == SCROLLABLE::HORIZONTAL, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
            if (itemCross == 0) {
                firstIndex = index;
                break;
            }
        }

        index--;
    }
    return firstIndex;
}

void RenderGridScroll::OnDataSourceUpdated(int32_t index)
{
    if (items_.empty() && updateFlag_) {
        return;
    }
    ACE_SCOPED_TRACE("OnDataSourceUpdated %d", index);
    auto items = gridMatrix_.find(startIndex_);
    if (items != gridMatrix_.end() && !items->second.empty()) {
        currentItemIndex_ = items->second.begin()->second;
    }
    startRankItemIndex_ = GetStartingItem(currentItemIndex_);
    auto offset = firstItemOffset_;
    ClearItems();
    ClearLayout(false);

    currentOffset_ = -offset;
    MarkNeedLayout();
}

void RenderGridScroll::CalculateWholeSize(double drawLength)
{
    if (gridMatrix_.empty() || gridCells_.empty()) {
        return;
    }
    if (totalCountFlag_) {
        int currentItemCount = 0;
        auto lastRow = gridMatrix_.rbegin()->second;
        if (!lastRow.empty()) {
            currentItemCount = lastRow.rbegin()->second;
        }
        if (currentItemCount != 0) {
            totalCountFlag_ = false;
        }
    }
    double scrollBarExtent = 0.0;
    double itemCount = 0;
    startMainPos_ = 0.0;
    for (int index = 0; index < *mainCount_; index++) {
        if (index == startIndex_) {
            // get the start position in grid
            startMainPos_ = scrollBarExtent;
        }
        if (gridCells_.find(index) == gridCells_.end()) {
            continue;
        }
        itemCount += gridCells_.at(index).size();
        scrollBarExtent += GetSize(gridCells_.at(index).at(0)) + *mainGap_;
    }
    if (itemCount > 0 && !gridCells_.empty()) {
        estimateAverageHeight_ = scrollBarExtent / itemCount;
        estimateHeight_ = estimateAverageHeight_ * GetItemTotalCount();
        auto result = gridMatrix_.find(gridCells_.begin()->first);
        if (result != gridMatrix_.end()) {
            int32_t startItem = result->second.begin()->second;
            estimatePos_ = estimateAverageHeight_ * startItem;
        }
    }

    bool isScrollable = false;
    if (estimateHeight_ > GetSize(GetLayoutSize()) || scrollBarExtent > GetSize(GetLayoutSize())) {
        isScrollable = true;
    }
    if (scrollBar_) {
        scrollBar_->SetScrollable(isScrollable);
    }
    if (!isScrollable) {
        currentOffset_ = 0.0;
    }
}

void RenderGridScroll::ScrollPage(bool reverse, bool smooth)
{
    if (!reverse) {
        UpdateScrollPosition(-GetSize(GetLayoutSize()), SCROLL_FROM_JUMP);
    } else {
        UpdateScrollPosition(GetSize(GetLayoutSize()), SCROLL_FROM_JUMP);
    }
}

double RenderGridScroll::GetEstimatedHeight()
{
    return estimateHeight_;
}

void RenderGridScroll::InitScrollBar()
{
    if (!component_) {
        LOGE("InitScrollBar failed, component_ is null.");
        return;
    }
    if (scrollBar_) {
        scrollBar_->SetDisplayMode(component_->GetScrollBar());
        if (!component_->GetScrollBarWidth().empty()) {
            const auto& width = StringUtils::StringToDimension(component_->GetScrollBarWidth());
            scrollBar_->SetInactiveWidth(width);
            scrollBar_->SetNormalWidth(width);
            scrollBar_->SetActiveWidth(width);
            scrollBar_->SetTouchWidth(width);
        }
        if (!component_->GetScrollBarColor().empty()) {
            scrollBarColor_ = Color::FromString(component_->GetScrollBarColor());
            scrollBar_->SetForegroundColor(scrollBarColor_);
        }
        scrollBar_->Reset();
        return;
    }

    const RefPtr<ScrollBarTheme> theme = GetTheme<ScrollBarTheme>();
    if (!theme) {
        return;
    }
    RefPtr<GridScrollController> controller = AceType::MakeRefPtr<GridScrollController>();
    scrollBar_ = AceType::MakeRefPtr<ScrollBar>(component_->GetScrollBar(), theme->GetShapeMode());
    scrollBar_->SetScrollBarController(controller);

    // set the scroll bar style
    scrollBar_->SetReservedHeight(theme->GetReservedHeight());
    scrollBar_->SetMinHeight(theme->GetMinHeight());
    scrollBar_->SetMinDynamicHeight(theme->GetMinDynamicHeight());
    auto& scrollBarColor = component_->GetScrollBarColor();
    if (!scrollBarColor.empty()) {
        scrollBarColor_ = Color::FromString(scrollBarColor);
    } else {
        scrollBarColor_ = theme->GetForegroundColor();
    }
    scrollBar_->SetForegroundColor(scrollBarColor_);
    scrollBar_->SetBackgroundColor(theme->GetBackgroundColor());
    scrollBar_->SetPadding(theme->GetPadding());
    scrollBar_->SetScrollable(true);
    if (!component_->GetScrollBarWidth().empty()) {
        const auto& width = StringUtils::StringToDimension(component_->GetScrollBarWidth());
        scrollBar_->SetInactiveWidth(width);
        scrollBar_->SetNormalWidth(width);
        scrollBar_->SetActiveWidth(width);
        scrollBar_->SetTouchWidth(width);
    } else {
        scrollBar_->SetInactiveWidth(theme->GetNormalWidth());
        scrollBar_->SetNormalWidth(theme->GetNormalWidth());
        scrollBar_->SetActiveWidth(theme->GetActiveWidth());
        scrollBar_->SetTouchWidth(theme->GetTouchWidth());
    }
    if (!isVertical_) {
        scrollBar_->SetPositionMode(PositionMode::BOTTOM);
    } else {
        if (rightToLeft_) {
            scrollBar_->SetPositionMode(PositionMode::LEFT);
        }
    }
    scrollBar_->InitScrollBar(AceType::WeakClaim(this), GetContext());
    SetScrollBarCallback();
}

void RenderGridScroll::InitScrollBarProxy()
{
    if (!scrollBarProxy_) {
        return;
    }
    auto&& scrollCallback = [weakScroll = AceType::WeakClaim(this)](double value, int32_t source) {
        auto grid = weakScroll.Upgrade();
        if (!grid) {
            LOGE("render grid is released");
            return false;
        }
        return grid->UpdateScrollPosition(value, source);
    };
    scrollBarProxy_->UnRegisterScrollableNode(AceType::WeakClaim(this));
    scrollBarProxy_->RegisterScrollableNode({ AceType::WeakClaim(this), scrollCallback });
}

void RenderGridScroll::SetScrollBarCallback()
{
    if (!scrollBar_ || !scrollBar_->NeedScrollBar()) {
        return;
    }
    auto&& barEndCallback = [weakGrid = AceType::WeakClaim(this)](int32_t value) {
        auto grid = weakGrid.Upgrade();
        if (!grid) {
            LOGE("render grid is released");
            return;
        }
        grid->scrollBarOpacity_ = value;
        grid->MarkNeedRender();
    };
    auto&& scrollEndCallback = [weakGrid = AceType::WeakClaim(this)]() {
        auto grid = weakGrid.Upgrade();
        if (!grid) {
            LOGE("render grid is released");
            return;
        }
    };
    auto&& scrollCallback = [weakScroll = AceType::WeakClaim(this)](double value, int32_t source) {
        auto grid = weakScroll.Upgrade();
        if (!grid) {
            LOGE("render grid is released");
            return false;
        }
        return grid->UpdateScrollPosition(value, source);
    };
    scrollBar_->SetCallBack(scrollCallback, barEndCallback, scrollEndCallback);
}

void RenderGridScroll::ScrollToIndex(int32_t index)
{
    if (useScrollable_ == SCROLLABLE::NO_SCROLL || index < 0) {
        LOGW("Not supported.");
        return;
    }
    auto inputIdx = GetItemMainIndex(index);
    if (inputIdx < endIndex_ && inputIdx > startIndex_) {
        LOGI("already in map, not need to jump.");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is null");
        return;
    }
    startRankItemIndex_ = GetStartingItem(index);
    // Build items
    if ((index < startShowItemIndex_ || index > endShowItemIndex_) &&
        (index - startRankItemIndex_ < static_cast<int32_t>(metaData_.size()))) {
        // do not need layout transition
        auto option = context->GetExplicitAnimationOption();
        context->SaveExplicitAnimationOption(AnimationOption());
        firstLineToBottom_.emplace(index > endShowItemIndex_);
        if (scrollable_ && !scrollable_->IsStopped()) {
            scrollable_->StopScrollable();
        }
        ClearItems();
        ClearLayout(false);
        currentOffset_ = 0;
        MarkNeedLayout();
        context->SaveExplicitAnimationOption(option);
        return;
    }

    if (index < startShowItemIndex_) {
        BuildItemsForwardByRange(index, startShowItemIndex_);
    } else if (index > endShowItemIndex_) {
        BuildItemsBackwardByRange(endShowItemIndex_, index);
    }

    // when scrollLength > 0, it means grid items moving forward
    // when scrollLength < 0, it means grid items moving backward
    currentOffset_ = -CalculateScrollLength(index);
    PerformLayout();
    MarkNeedRender();
}

double RenderGridScroll::CalculateScrollLength(int32_t index)
{
    double scrollLength = 0.0;
    auto inputIndex = GetItemMainIndex(index);
    do {
        if (inputIndex >= endIndex_) {
            // when inputIndex >= endIndex_, grid items need to move forward (i.e. jump backward)
            double originalTotalLen = 0; // total length from startIndex_ to endIndex_
            for (int32_t i = startIndex_; i <= endIndex_; ++i) {
                if (gridCells_.find(i) != gridCells_.end()) {
                    originalTotalLen += GetSize(gridCells_.at(i).at(0)) + *mainGap_;
                }
            }
            // reduce a mainGap because the last item need to be placed to the bottom of viewport
            originalTotalLen -= (*mainGap_ + firstItemOffset_);
            // [itemLengthOutOfViewport] is the length of grid items that is out of viewport
            double itemLengthOutOfViewport = originalTotalLen - GetSize(GetLayoutSize());
            double newlyBuiltItemLength = 0;
            for (int32_t i = endIndex_; i < inputIndex; ++i) {
                SupplyItems(i, index);
                if (i != inputIndex) {
                    newlyBuiltItemLength += GetSize(gridCells_.at(i).at(0)) + *mainGap_;
                }
            }
            // grid items move forward by scrollLength
            scrollLength = itemLengthOutOfViewport + newlyBuiltItemLength;
            break;
        }
        if (inputIndex <= startIndex_) {
            // when inputIndex <= startIndex_, grid items need to move backward (i.e. jump forward)
            double newlyBuiltItemLength = 0;
            for (int32_t i = startIndex_; i >= inputIndex; --i) {
                SupplyItems(i, index, i != inputIndex);
                if (i != inputIndex) {
                    newlyBuiltItemLength -= (GetSize(gridCells_.at(i).at(0)) + *mainGap_);
                }
            }
            scrollLength = newlyBuiltItemLength - firstItemOffset_;
            break;
        }
        LOGE("branch: [startIndex_ < inputIndex < endIndex_] should not be entered here, please check.");
    } while (0);
    return scrollLength;
}

void RenderGridScroll::BuildItemsBackwardByRange(int32_t startItemIdx, int32_t endItemIdx)
{
    if (startItemIdx >= endItemIdx) {
        return;
    }
    auto itemIndex = startItemIdx;
    auto end = endItemIdx;
    while (itemIndex <= end) {
        if (GetItemMainIndex(itemIndex) != -1) {
            ++itemIndex;
            continue;
        }
        int32_t itemMain = -1;
        int32_t itemCross = -1;
        int32_t itemMainSpan = -1;
        int32_t itemCrossSpan = -1;
        if (!GetItemPropsByIndex(itemIndex, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
            return;
        }
        if (itemCrossSpan > *crossCount_) {
            itemIndex++;
            continue;
        }
        if (itemMain >= 0 && itemCross >= 0 && itemCross < *crossCount_ &&
            CheckGridPlaced(itemIndex, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
        } else {
            // itemMain < 0 means this item is not placed, place it to the end of the gridMatrix_.
            if (itemMain < 0) {
                itemMain = gridMatrix_.rbegin()->first;
                itemCross = gridMatrix_.rbegin()->second.rbegin()->first;
                GetNextGrid(itemMain, itemCross);
                while (!CheckGridPlaced(itemIndex, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
                    GetNextGrid(itemMain, itemCross);
                }
            }
        }
        itemIndex++;
    }
    // Check current end main line is placed completely or not.
    int32_t lastCross = gridMatrix_.rbegin()->second.rbegin()->first;
    ++end;
    for (int32_t crossIndex = lastCross + 1; crossIndex < *crossCount_; ++crossIndex) {
        int32_t itemMain = -1;
        int32_t itemCross = -1;
        int32_t itemMainSpan = -1;
        int32_t itemCrossSpan = -1;
        if (!GetItemPropsByIndex(end, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
            return;
        }
        if (itemCrossSpan > *crossCount_) {
            ++end;
            continue;
        }
        itemMain = gridMatrix_.rbegin()->first;
        itemCross = itemCross == -1 ? crossIndex : itemCross;
        CheckGridPlaced(end, itemMain, itemCross, itemMainSpan, itemCrossSpan);
        ++end;
    }
}

void RenderGridScroll::BuildItemsForwardByRange(int32_t startItemIdx, int32_t endItemIdx)
{
    if (startItemIdx <= endItemIdx) {
        return;
    }
    auto itemIndex = startItemIdx;
    auto end = endItemIdx;
    while (itemIndex >= end) {
        if (GetItemMainIndex(itemIndex) != -1) {
            --itemIndex;
            continue;
        }
        int32_t itemMain = -1;
        int32_t itemCross = -1;
        int32_t itemMainSpan = -1;
        int32_t itemCrossSpan = -1;
        if (!GetItemPropsByIndex(itemIndex, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
            return;
        }
        if (itemCrossSpan > *crossCount_) {
            --itemIndex;
            continue;
        }
        if (itemMain >= 0 && itemCross >= 0 && itemCross < *crossCount_ &&
            CheckGridPlaced(itemIndex, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
        } else {
            // itemMain < 0 means this item is not placed, place it to the front of the gridMatrix_.
            if (itemMain < 0) {
                itemMain = gridMatrix_.begin()->first;
                itemCross = gridMatrix_.begin()->second.begin()->first;
                GetPreviousGrid(itemMain, itemCross);
                while (!CheckGridPlaced(itemIndex, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
                    GetPreviousGrid(itemMain, itemCross);
                }
            }
        }
        --itemIndex;
    }
    // Check current front main line is placed completely or not.
    int32_t firstCross = gridMatrix_.begin()->second.begin()->first;
    --end;
    for (int32_t crossIndex = firstCross - 1; crossIndex >= 0; --crossIndex) {
        int32_t itemMain = -1;
        int32_t itemCross = -1;
        int32_t itemMainSpan = -1;
        int32_t itemCrossSpan = -1;
        if (!GetItemPropsByIndex(end, itemMain, itemCross, itemMainSpan, itemCrossSpan)) {
            return;
        }
        if (itemCrossSpan > *crossCount_) {
            --end;
            continue;
        }
        itemMain = gridMatrix_.begin()->first;
        itemCross = itemCross == -1 ? crossIndex : itemCross;
        CheckGridPlaced(end, itemMain, itemCross, itemMainSpan, itemCrossSpan);
        --end;
    }
}

bool RenderGridScroll::AnimateTo(const Dimension& position, float duration, const RefPtr<Curve>& curve)
{
    if (!animator_->IsStopped()) {
        animator_->Stop();
    }
    animator_->ClearInterpolators();
    animateDelta_ = 0.0;
    auto animation = AceType::MakeRefPtr<CurveAnimation<double>>(GetCurrentOffset(), NormalizeToPx(position), curve);
    animation->AddListener([weakScroll = AceType::WeakClaim(this)](double value) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->DoJump(value, SCROLL_FROM_JUMP);
        }
    });
    animator_->AddInterpolator(animation);
    animator_->SetDuration(duration);
    animator_->ClearStopListeners();
    animator_->AddStopListener([weakScroll = AceType::WeakClaim(this)]() {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->animateDelta_ = 0.0;
        }
    });
    animator_->Play();
    return true;
}

Offset RenderGridScroll::CurrentOffset()
{
    auto ctx = GetContext().Upgrade();
    if (!ctx) {
        return useScrollable_ == SCROLLABLE::HORIZONTAL ? Offset(GetCurrentOffset(), 0.0)
                                                        : Offset(0.0, GetCurrentOffset());
    }
    auto mainOffset = ctx->ConvertPxToVp(Dimension(GetCurrentOffset(), DimensionUnit::PX));
    Offset currentOffset = useScrollable_ == SCROLLABLE::HORIZONTAL ? Offset(mainOffset, 0.0) : Offset(0.0, mainOffset);
    return currentOffset;
}

bool RenderGridScroll::GetItemPropsByIndex(
    int32_t itemIndex, int32_t& itemMain, int32_t& itemCross, int32_t& itemMainSpan, int32_t& itemCrossSpan)
{
    auto item = items_.find(itemIndex);
    if (item != items_.end()) {
        itemMain = GetItemMainIndex(item->second, true);
        itemCross = GetItemMainIndex(item->second, false);
        itemMainSpan = GetItemSpan(item->second, useScrollable_ != SCROLLABLE::HORIZONTAL);
        itemCrossSpan = GetItemSpan(item->second, useScrollable_ == SCROLLABLE::HORIZONTAL);
    } else {
        if (!getChildSpanByIndex_(itemIndex, useScrollable_ == SCROLLABLE::HORIZONTAL, itemMain, itemCross,
                itemMainSpan, itemCrossSpan)) {
            LOGW("Not valid.");
            return false;
        }
    }
    return true;
}

void RenderGridScroll::ScrollToEdge(OHOS::Ace::ScrollEdgeType edgeType, bool smooth)
{
    if (edgeType != ScrollEdgeType::SCROLL_TOP) {
        LOGW("Not supported yet");
        return;
    }
    if (items_.empty() && updateFlag_) {
        return;
    }
    if (scrollable_ && !scrollable_->IsStopped()) {
        scrollable_->StopScrollable();
    }
    currentItemIndex_ = 0;
    startRankItemIndex_ = GetStartingItem(currentItemIndex_);
    ClearItems();
    ClearLayout(false);
    MarkNeedLayout();
}

void RenderGridScroll::DoJump(double position, int32_t source)
{
    double delta = position - animateDelta_;
    UpdateScrollPosition(delta, source);
    animateDelta_ = position;
}

int32_t RenderGridScroll::GetIndexByPosition(double position) const
{
    int32_t index = 0;
    double startPosition = 0.0;
    double endPosition = 0.0;

    for (const auto& item : childrenInRect_) {
        if (!item || item->GetChildren().empty()) {
            continue;
        }
        auto gridItem = AceType::DynamicCast<RenderGridLayoutItem>(item);
        if (!gridItem) {
            break;
        }
        startPosition = item->GetPosition().GetY();
        endPosition = item->GetPosition().GetY() + item->GetLayoutSize().Height();
        if ((position > startPosition && position < endPosition) || NearEqual(position, startPosition) ||
            startPosition > position) {
            return gridItem->GetIndex();
        }
    }
    return index;
}

void RenderGridScroll::OnScrolled(int32_t scrolled) const
{
    if (scrolledEventFun_) {
        auto event = std::make_shared<GridEventInfo>(scrolled);
        if (event) {
            scrolledEventFun_(event);
        }
    }
}

void RenderGridScroll::OnPaintFinish()
{
    RenderNode::OnPaintFinish();
    if (showItem_.empty()) {
        return;
    }
    auto currentStartItemCount = *showItem_.begin();
    auto currentEndItemCount = *showItem_.rbegin();
    if ((startShowItemIndex_ != currentStartItemCount) || (endShowItemIndex_ != currentEndItemCount)) {
        startShowItemIndex_ = currentStartItemCount;
        endShowItemIndex_ = currentEndItemCount;
    }
}

void RenderGridScroll::OnPredictLayout(int64_t deadline)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    if (!context->IsTransitionStop()) {
        LOGI("In page transition, skip predict.");
        return;
    }
    if (loadingIndex_ == -1) {
        DealCache(startIndex_, endIndex_);
        if (loadingIndex_ == -1) {
            if (startIndex_ == 0 && startRankItemIndex_ > 0) {
                LoadForward();
                MarkNeedPredictLayout();
            }
            return;
        }
    }
    ACE_SCOPED_TRACE("OnPredictLayout %d", loadingIndex_);
    if (gridMatrix_.find(loadingIndex_) != gridMatrix_.end() || Rank(loadingIndex_)) {
        auto iter = gridMatrix_.find(loadingIndex_);
        if (iter != gridMatrix_.end()) {
            for (const auto& item : iter->second) {
                if (items_.find(item.second) == items_.end()) {
                    if (!buildChildByIndex_(item.second)) {
                        break;
                    }
                }
                // Stop predictLayout less than 3 milliseconds before the next vsync arrives.
                if (GetSysTimestamp() + TIME_THRESHOLD > deadline) {
                    MarkNeedPredictLayout();
                    return;
                }
            }
            SupplyItems(loadingIndex_);
        }
        MarkNeedPredictLayout();
    } else {
        loadingIndex_ = -1;
    }
}

bool RenderGridScroll::IsAxisScrollable(AxisDirection direction)
{
    return (((AxisEvent::IsDirectionUp(direction) || AxisEvent::IsDirectionLeft(direction)) && !reachHead_) ||
            ((AxisEvent::IsDirectionLeft(direction) || AxisEvent::IsDirectionRight(direction)) && !reachTail_));
}

void RenderGridScroll::HandleAxisEvent(const AxisEvent& event)
{
}

std::string RenderGridScroll::ProvideRestoreInfo()
{
    int32_t currentItemIndex = 0;
    auto items = gridMatrix_.find(startIndex_);
    if (items != gridMatrix_.end() && !items->second.empty()) {
        currentItemIndex = items->second.begin()->second;
    }

    if (currentItemIndex > 0) {
        return std::to_string(currentItemIndex);
    }
    return "";
}

void RenderGridScroll::ApplyRestoreInfo()
{
    if (GetRestoreInfo().empty()) {
        return;
    }
    currentItemIndex_ = StringUtils::StringToInt(GetRestoreInfo());
    startRankItemIndex_ = GetStartingItem(currentItemIndex_);
    SetRestoreInfo("");
}

} // namespace OHOS::Ace::V2
