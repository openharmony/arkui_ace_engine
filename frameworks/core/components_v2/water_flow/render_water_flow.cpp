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

#include "core/components_v2/water_flow/render_water_flow.h"

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/string_utils.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/animation/curve_animation.h"
#include "core/components_v2/water_flow/render_water_flow_item.h"
#include "core/components_v2/water_flow/water_flow_component.h"
#include "core/components_v2/water_flow/water_flow_scroll_controller.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace::V2 {
namespace {
constexpr int32_t TIME_THRESHOLD = 3 * 1000000; // milliseconds
constexpr int32_t DEFAULT_DEPTH = 10;
constexpr bool HORIZONTAL = false;
constexpr bool VERTICAL = true;
constexpr bool FORWARD = false;
constexpr bool REVERSE = true;

// first bool mean if vertical, second bool mean if reverse
// false, false --> RIGHT
// false, true --> LEFT
// true, false --> DOWN
// true, true ---> UP
// This map will adapter the WaterFlow FlexDirection with Key Direction.
const std::map<bool, std::map<bool, std::map<bool, KeyDirection>>> DIRECTION_MAP = {
    { false, // RTL is false
        { { HORIZONTAL, { { FORWARD, KeyDirection::RIGHT }, { REVERSE, KeyDirection::LEFT } } },
            { VERTICAL, { { FORWARD, KeyDirection::DOWN }, { REVERSE, KeyDirection::UP } } } } },
    { true, // RTL is true
        { { HORIZONTAL, { { FORWARD, KeyDirection::LEFT }, { REVERSE, KeyDirection::RIGHT } } },
            { VERTICAL, { { FORWARD, KeyDirection::DOWN }, { REVERSE, KeyDirection::UP } } } } }
};
} // namespace

std::string WaterFlowEventInfo::ToJSONString() const
{
    return std::string("\"waterflow\",{\"first\":").append(std::to_string(scrollIndex_)).append("},null");
}

RenderWaterFlow::~RenderWaterFlow()
{
    if (scrollBarProxy_) {
        scrollBarProxy_->UnRegisterScrollableNode(AceType::WeakClaim(this));
    }
}

void RenderWaterFlow::Update(const RefPtr<Component>& component)
{
    InitScrollBar(component);
    if (!NeedUpdate(component)) {
        return;
    }

    startRankItemIndex_ = 0;
    currentItemIndex_ = 0;
    const RefPtr<V2::WaterFlowComponent> flow = AceType::DynamicCast<V2::WaterFlowComponent>(component);
    if (!flow) {
        LOGE("RenderWaterFlow update failed.");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }

    isVertical_ = true;
    updateFlag_ = true;
    direction_ = flow->GetDirection();
    userColGap_ = flow->GetColumnsGap();
    userRowGap_ = flow->GetRowsGap();
    userMainLength_ = flow->GetMainLength();
    scrollBarProxy_ = flow->GetScrollBarProxy();
    crossCount_ = flow->GetCrossSplice();
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        mainGap_ = NormalizePercentToPx(userRowGap_, true);
        crossGap_ = NormalizePercentToPx(userColGap_, false);
        useScrollable_ = SCROLLABLE::VERTICAL;
    } else {
        crossGap_ = NormalizePercentToPx(userRowGap_, true);
        mainGap_ = NormalizePercentToPx(userColGap_, false);
        useScrollable_ = SCROLLABLE::HORIZONTAL;
    }

    InitScrollBarProxy();
    CreateScrollable();
    MarkNeedLayout();
    LOGD("%{public}s mainCount_:%{public}d crossCount_:%{public}d mainGap_:%{public}f "
         "crossGap_:%{public}f",
        __PRETTY_FUNCTION__, mainCount_, crossCount_, mainGap_, crossGap_);
}

void RenderWaterFlow::CalAndPosItems(double& drawLength, int32_t& main)
{
    for (; main < mainCount_; main++) {
        for (int32_t cross = 0; cross < crossCount_; cross++) {
            auto mainIter = flowMatrix_.find(main);
            if (mainIter == flowMatrix_.end()) {
                LOGD("PerformLayout. main: %{public}d. skip flowMatrix_", main);
                continue;
            }
            auto crossIter = mainIter->second.find(cross);
            if (crossIter == mainIter->second.end()) {
                LOGD("PerformLayout. main: %{public}d, cross: %{public}d. skip flowMatrix_", main, cross);
                continue;
            }
            if (buildChildByIndex_ && (inCache_.count(main) == 0 || !CheckMainFull(main))) {
                bool vail = false;
                SupplyItems(vail, main);
            }
            if (showItem_.count(crossIter->second) != 0) {
                continue;
            }

            showItem_.insert(crossIter->second);
            CheckAndInsertItems(main, crossIter->second);
            auto item = items_.find(crossIter->second);
            if (item != items_.end()) {
                childrenInRect_.push_back(item->second);
                int32_t itemMainSpan = GetItemSpan(item->second, useScrollable_ != SCROLLABLE::HORIZONTAL);
                int32_t itemCrossSpan = GetItemSpan(item->second, useScrollable_ == SCROLLABLE::HORIZONTAL);
                int32_t itemMain = GetItemMainIndex(crossIter->second);
                LOGD("PerformLayout. matrix_ss itemInfo. itemindex:%{public}d, row:%{public}d, col:%{public}d, "
                     "rowSpan:%{public}d,"
                     "colSpan:%{public}d.",
                    crossIter->second, itemMain, cross, itemMainSpan, itemCrossSpan);
                SetChildPosition(item->second, itemMain, cross, itemMainSpan, itemCrossSpan);
            }
        }
        if (main >= startIndex_) {
            drawLength += GetSize(flowCells_) + mainGap_;
        }
        if (GreatOrEqual(drawLength, mainSize_)) {
            break;
        }
    }
}

void RenderWaterFlow::PerformLayout()
{
    if (RenderNode::GetChildren().empty() && !buildChildByIndex_) {
        return;
    }

    // calculate rowSize colSize mainLength
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        mainSize_ = GetLayoutParam().GetMaxSize().Height();
        crossSize_ = GetLayoutParam().GetMaxSize().Width();
        if (NearEqual(mainSize_, Size::INFINITE_SIZE)) {
            mainSize_ = viewPort_.Height();
        }
        if (NearEqual(crossSize_, Size::INFINITE_SIZE)) {
            crossSize_ = viewPort_.Width();
        }
    } else {
        crossSize_ = GetLayoutParam().GetMaxSize().Height();
        mainSize_ = GetLayoutParam().GetMaxSize().Width();
        if (NearEqual(crossSize_, Size::INFINITE_SIZE)) {
            crossSize_ = viewPort_.Height();
        }
        if (NearEqual(mainSize_, Size::INFINITE_SIZE)) {
            mainSize_ = viewPort_.Width();
        }
    }
    mainLength_ = NormalizePercentToPx(userMainLength_, true);
    if (NearZero(mainLength_)) {
        mainLength_ = ParseCrossLength(crossSize_, crossGap_).at(0);
    }

    InitialFlowProp();
    CalculateViewPort();
    showItem_.clear();
    childrenInRect_.clear();
    double drawLength = 0.0 - firstItemOffset_;
    int32_t main = startIndex_ > 0 ? startIndex_ - 1 : startIndex_;
    LOGD("PerformLayout. main: %{public}d. start", main);
    CalAndPosItems(drawLength, main);
    SetLayoutSize(GetLayoutParam().Constrain(Size(crossSize_, mainSize_)));
    endIndex_ = main;
    MarkNeedPredictLayout();
    CalculateWholeSize(drawLength);
    lastOffset_ = startMainPos_ + firstItemOffset_ - currentOffset_;
    LOGD("PerformLayout. offset_ss lastOffset_:%{public}lf, startMainPos_:%{public}lf, firstItemOffset_:%{public}lf,"
         "currentOffset_:%{public}lf",
        lastOffset_, startMainPos_, firstItemOffset_, currentOffset_);
    LOGD("PerformLayout. offset_ss mainCount_:%{public}d", mainCount_);
}

bool RenderWaterFlow::NeedUpdate(const RefPtr<Component>& component)
{
    const RefPtr<V2::WaterFlowComponent> flow = AceType::DynamicCast<V2::WaterFlowComponent>(component);
    if (!flow) {
        LOGE("RenderWaterFlow update failed.");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return false;
    }
    auto controller = flow->GetController();
    if (controller) {
        controller->SetScrollNode(WeakClaim(this));
    }
    if (!animator_) {
        animator_ = AceType::MakeRefPtr<Animator>(GetContext());
    }

    if (direction_ != flow->GetDirection() || crossAxisAlign_ != flow->GetFlexAlign() ||
        userColGap_ != flow->GetColumnsGap() || userRowGap_ != flow->GetRowsGap() ||
        rightToLeft_ != flow->GetRightToLeft()) {
        return true;
    };
    return false;
}

void RenderWaterFlow::AddChildByIndex(int32_t index, const RefPtr<RenderNode>& renderNode)
{
    auto iter = items_.find(index);
    if (iter != items_.end() && iter->second == nullptr) {
        items_.erase(index);
        itemSpanCache_.erase(index);
    }
    auto itor = items_.try_emplace(index, renderNode);
    if (itor.second) {
        AddChild(renderNode);
        SetItemCalSizeNeeded(renderNode, true);
        RefPtr<RenderWaterFlowItem> node = AceType::DynamicCast<RenderWaterFlowItem>(renderNode);
        if (node) {
            node->SetBoundary();
            node->SetIndex(index);
            node->SetHidden(false);
        }
        Span span;
        span.rowSpan = node->GetRowSpan();
        span.colSpan = node->GetColumnSpan();
        itemSpanCache_.emplace(std::make_pair(index, span));
    }
}

void RenderWaterFlow::CreateScrollable()
{
    scrollable_ = nullptr;
    if (useScrollable_ == SCROLLABLE::NO_SCROLL) {
        return;
    }

    auto callback = [weak = AceType::WeakClaim(this)](double offset, int32_t source) {
        auto flow = weak.Upgrade();
        if (!flow) {
            return false;
        }
        // Stop animator of scroll bar.
        auto scrollBarProxy = flow->scrollBarProxy_;
        if (scrollBarProxy) {
            scrollBarProxy->StopScrollBarAnimator();
        }
        return flow->UpdateScrollPosition(offset, source);
    };
    scrollable_ = AceType::MakeRefPtr<Scrollable>(
        callback, useScrollable_ == SCROLLABLE::HORIZONTAL ? Axis::HORIZONTAL : Axis::VERTICAL);
    scrollable_->SetScrollEndCallback([weak = AceType::WeakClaim(this)]() {
        auto flow = weak.Upgrade();
        if (flow) {
            auto proxy = flow->scrollBarProxy_;
            if (proxy) {
                proxy->StartScrollBarAnimator();
            }
        }
    });
    scrollable_->Initialize(context_);
}

bool RenderWaterFlow::UpdateScrollPosition(double offset, int32_t source)
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

    currentOffset_ += Round(offset);
    MarkNeedLayout(true);
    return true;
}

void RenderWaterFlow::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (!GetVisible()) {
        return;
    }
    if (!scrollable_ || !scrollable_->Available()) {
        return;
    }
    if (scrollBar_ && scrollBar_->InBarRegion(globalPoint_ - coordinateOffset)) {
        scrollBar_->AddScrollBarController(coordinateOffset, result);
    } else {
        scrollable_->SetCoordinateOffset(coordinateOffset);
        scrollable_->SetDragTouchRestrict(touchRestrict);
        result.emplace_back(scrollable_);
    }
    result.emplace_back(scrollable_);
}

bool RenderWaterFlow::IsChildrenTouchEnable()
{
    bool ret = scrollable_->IsMotionStop();
    return ret;
}

void RenderWaterFlow::SetChildPosition(
    const RefPtr<RenderNode>& child, int32_t main, int32_t cross, int32_t mainSpan, int32_t crossSpan)
{
    // Calculate the position for current child.
    double positionMain = 0.0;
    double positionCross = 0.0;
    if (main < startIndex_) {
        positionMain -= GetSize(flowCells_) * (startIndex_ - main);
        positionMain += (main - startIndex_) * mainGap_;
    } else {
        positionMain += GetSize(flowCells_) * (main - startIndex_);
        positionMain += (main - startIndex_) * mainGap_;
    }

    positionCross += GetSize(flowCells_, false) * cross;
    positionCross += cross * crossGap_;

    // Calculate the size for current child.
    double mainLen = 0.0;
    double crossLen = 0.0;
    mainLen += GetSize(flowCells_) * mainSpan;
    mainLen += (mainSpan - 1) * mainGap_;
    crossLen += GetSize(flowCells_, false) * crossSpan;
    crossLen += (crossSpan - 1) * crossGap_;

    // If RTL, place the item from right.
    if (rightToLeft_) {
        if (useScrollable_ != SCROLLABLE::HORIZONTAL) {
            positionCross = crossSize_ - positionCross - crossLen;
        }
    }

    double mainOffset = (mainLen - GetSize(child->GetLayoutSize())) / 2.0;
    double crossOffset = (crossLen - GetSize(child->GetLayoutSize(), false)) / 2.0;

    Offset offset;
    if (useScrollable_ != SCROLLABLE::HORIZONTAL) {
        offset = Offset(positionCross + crossOffset, positionMain + mainOffset - firstItemOffset_);
    } else {
        offset = Offset(positionMain + mainOffset - firstItemOffset_, positionCross + crossOffset);
    }

    child->SetPosition(offset);
}

double RenderWaterFlow::GetSize(const Size& src, bool isMain) const
{
    if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        return isMain ? src.Width() : src.Height();
    }

    return isMain ? src.Height() : src.Width();
}

bool RenderWaterFlow::GetFlowSize()
{
    double rowSize = ((flowHeight_ > 0.0) && (flowHeight_ < GetLayoutParam().GetMaxSize().Height()))
                         ? flowHeight_
                         : GetLayoutParam().GetMaxSize().Height();
    double colSize = ((flowWidth_ > 0.0) && (flowWidth_ < GetLayoutParam().GetMaxSize().Width()))
                         ? flowWidth_
                         : GetLayoutParam().GetMaxSize().Width();
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        useScrollable_ = SCROLLABLE::VERTICAL;
        if (NearEqual(mainSize_, Size::INFINITE_SIZE)) {
            mainSize_ = viewPort_.Height();
        }
        if (NearEqual(crossSize_, Size::INFINITE_SIZE)) {
            crossSize_ = viewPort_.Width();
        }
        LOGD("GetFlowSize %lf, %lf   [%lf- %lf]", rowSize, colSize, mainSize_, crossSize_);
        if (rowSize != mainSize_ || colSize != crossSize_) {
            mainSize_ = rowSize;
            crossSize_ = colSize;
            CreateScrollable();
            return true;
        }
    } else {
        useScrollable_ = SCROLLABLE::HORIZONTAL;
        if (NearEqual(mainSize_, Size::INFINITE_SIZE)) {
            mainSize_ = viewPort_.Width();
        }
        if (NearEqual(crossSize_, Size::INFINITE_SIZE)) {
            crossSize_ = viewPort_.Height();
        }
        LOGD("GetFlowSize %lf, %lf   [%lf- %lf]", rowSize, colSize, mainSize_, crossSize_);
        if (rowSize != crossSize_ || colSize != mainSize_) {
            crossSize_ = rowSize;
            mainSize_ = colSize;
            CreateScrollable();
            return true;
        }
    }
    return false;
}

void RenderWaterFlow::BuildFlow(std::vector<double>& cross)
{
    cross = ParseCrossLength(crossSize_, crossGap_);
    if (useScrollable_ == SCROLLABLE::VERTICAL) {
        flowCells_ = Size(cross.at(0), mainLength_);
    } else if (useScrollable_ == SCROLLABLE::HORIZONTAL) {
        flowCells_ = Size(mainLength_, cross.at(0));
    }
}

void RenderWaterFlow::CallGap()
{
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        mainGap_ = NormalizePercentToPx(userRowGap_, true);
        crossGap_ = NormalizePercentToPx(userColGap_, false);
    } else {
        crossGap_ = NormalizePercentToPx(userRowGap_, true);
        mainGap_ = NormalizePercentToPx(userColGap_, false);
    }
}

void RenderWaterFlow::InitialFlowProp()
{
    // Not first time layout after update, no need to initial.
    if (!GetFlowSize() && !updateFlag_) {
        return;
    }
    OnDataSourceUpdated(-1);
    CallGap();
    std::vector<double> cross;
    BuildFlow(cross);
    // Initialize the columnCount and rowCount, default is 1
    crossCount_ = static_cast<int32_t>(cross.size());
    if (crossCount_ < 0) {
        return;
    }
    UpdateAccessibilityAttr();

    if (!buildChildByIndex_) {
        LOGE("%{public}s. buildChildByIndex_ is null.", __PRETTY_FUNCTION__);
        return;
    }

    int32_t endIndex = -1;
    mainCount_ = GetItemMainIndex(startRankItemIndex_);
    if (mainCount_ < 0) {
        mainCount_ = 0;
    }
    while (endIndex < currentItemIndex_) {
        Rank(mainCount_, startRankItemIndex_);
        mainCount_++;
        auto mainItor = flowMatrix_.find(mainCount_ - 1);
        if (mainItor == flowMatrix_.end()) {
            break;
        }
        for (int32_t crossIndex = crossCount_ - 1; crossIndex >= 0; crossIndex--) {
            auto iter = mainItor->second.find(crossIndex);
            if (iter != mainItor->second.end()) {
                endIndex = iter->second;
                break;
            }
        }
    }
    startRankItemIndex_ = 0;
    currentItemIndex_ = 0;
    bool vail = false;
    SupplyItems(vail, ((mainCount_ > 0) ? (mainCount_ - 1) : 0));
    startIndex_ = (mainCount_ > 0) ? (mainCount_ - 1) : 0;
    if (NearZero(currentOffset_)) {
        needCalculateViewPort_ = true;
    }

    updateFlag_ = false;
    if (firstLineToBottom_ && firstLineToBottom_.value()) {
        // calculate the distance from the first line to the last line
        currentOffset_ = mainSize_ - GetSize(flowCells_);
        needCalculateViewPort_ = false;
    }
    firstLineToBottom_ = std::nullopt;
}

double RenderWaterFlow::BuildLazyFlowLayout(int32_t index, double sizeNeed)
{
    if (!buildChildByIndex_ || index < 0 || NearZero(sizeNeed)) {
        return 0.0;
    }
    double size = 0.0;
    int32_t startIndex = index;
    while (ceil(size) < ceil(sizeNeed)) {
        bool vail = false;
        auto suppleSize = SupplyItems(vail, startIndex);
        if (NearZero(suppleSize)) {
            break;
        }
        mainCount_ = ++startIndex;
        size += suppleSize + mainGap_;
    }
    return size;
}

void RenderWaterFlow::CalculateCrossSpan(
    int32_t mainIndex, int32_t cross, int32_t crossSpan, int32_t& calculateCrossSpan)
{
    auto mainIter = flowMatrix_.find(mainIndex);
    if (mainIter != flowMatrix_.end()) {
        int32_t tempCrossSpan = 0;
        for (int32_t j = 0; j < crossSpan; j++) {
            if ((mainIter->second.find(j + cross) == mainIter->second.end()) && (crossCount_ > (j + cross))) {
                tempCrossSpan = j + 1;
            } else if (tempCrossSpan > 0) {
                break;
            }
        }
        if ((calculateCrossSpan == 0) || (calculateCrossSpan >= tempCrossSpan)) {
            calculateCrossSpan = tempCrossSpan;
        }
    } else {
        // check if the first flowitem's crossSpan of the row is large then crossCount_
        if (crossCount_ < crossSpan && calculateCrossSpan == 0) {
            calculateCrossSpan = crossCount_;
        }
    }
}

bool RenderWaterFlow::CheckFlowPlaced(int32_t index, int32_t main, int32_t cross, int32_t& mainSpan, int32_t& crossSpan)
{
    auto mainIter = flowMatrix_.find(main);
    if (mainIter != flowMatrix_.end()) {
        auto crossIter = mainIter->second.find(cross);
        if (crossIter != mainIter->second.end()) {
            return false;
        }
    }
    int32_t calculateCrossSpan = 0;
    for (int32_t i = 0; i < mainSpan; i++) {
        CalculateCrossSpan(i + main, cross, crossSpan, calculateCrossSpan);
    }
    if ((calculateCrossSpan != 0) && (calculateCrossSpan != crossSpan)) {
        auto iter = itemSpanCache_.find(index);
        if (iter != itemSpanCache_.end()) {
            itemSpanCache_.erase(index);
        }
        Span span;
        span.rowSpan = mainSpan;
        span.colSpan = calculateCrossSpan;
        itemSpanCache_.emplace(std::make_pair(index, span));
        crossSpan = calculateCrossSpan;
    }

    for (int32_t i = main; i < main + mainSpan; ++i) {
        std::map<int32_t, int32_t> mainMap;
        auto iter = flowMatrix_.find(i);
        if (iter != flowMatrix_.end()) {
            mainMap = iter->second;
        }
        for (int32_t j = cross; j < cross + crossSpan; ++j) {
            mainMap.emplace(std::make_pair(j, index));
        }
        flowMatrix_[i] = mainMap;
    }

    std::map<int32_t, int32_t> flowMap;
    auto iterFlow = flowMatrixByIndex_.find(index);
    if (iterFlow != flowMatrixByIndex_.end()) {
        flowMap = iterFlow->second;
    }
    for (int32_t i = main; i < main + mainSpan; ++i) {
        for (int32_t j = cross; j < cross + crossSpan; ++j) {
            flowMap.emplace(std::make_pair(i, j));
        }
    }
    flowMatrixByIndex_[index] = flowMap;

    LOGD("CheckFlowPlaced done %{public}d %{public}d %{public}d %{public}d %{public}d", index, main, cross, mainSpan,
        crossSpan);
    return true;
}

void RenderWaterFlow::LayoutChild(const RefPtr<RenderNode>& child, int32_t main, int32_t cross, int32_t mainSpan,
    int32_t crossSpan, bool needPosition)
{
    child->Layout(MakeInnerLayoutParam(main, cross, mainSpan, crossSpan));
    SetItemCalSizeNeeded(child, false);

    if (!needPosition) {
        return;
    }
    if (useScrollable_ != SCROLLABLE::HORIZONTAL) {
        child->SetPosition(Offset(0, mainSize_ + mainGap_));
    } else {
        child->SetPosition(Offset(mainSize_ + mainGap_, 0));
    }
}

void RenderWaterFlow::GetNextFlow(int32_t& curMain, int32_t& curCross) const
{
    ++curCross;
    if (curCross >= crossCount_) {
        curCross = 0;
        ++curMain;
    }
}

void RenderWaterFlow::GetPreviousFlow(int32_t& curMain, int32_t& curCross)
{
    --curCross;
    if (curCross < 0) {
        curCross = crossCount_;
        --curMain;
    }
}

LayoutParam RenderWaterFlow::MakeInnerLayoutParam(
    int32_t main, int32_t cross, int32_t mainSpan, int32_t crossSpan) const
{
    LayoutParam innerLayout;
    double mainLen = 0.0;
    double crossLen = 0.0;
    mainLen += GetSize(flowCells_) * mainSpan;
    mainLen += (mainSpan - 1) * mainGap_;

    crossLen += GetSize(flowCells_, false) * crossSpan;
    crossLen += (crossSpan - 1) * crossGap_;

    Size size;
    LOGD("mainLen: %{public}lf", mainLen);
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
        innerLayout.SetMinSize(size);
    }
    return innerLayout;
}

void RenderWaterFlow::LoadForward()
{
    auto firstItem = 0;
    decltype(flowMatrix_) flowMatrix(std::move(flowMatrix_));

    int32_t count = 0;
    int32_t endIndex = -1;
    while (endIndex < startRankItemIndex_ - 1) {
        if (!Rank(count, count == 0 ? firstItem : -1)) {
            break;
        }
        count++;
        auto mainItor = flowMatrix_.find(count - 1);
        if (mainItor == flowMatrix_.end()) {
            break;
        }
        for (int32_t cross = crossCount_ - 1; cross >= 0; cross--) {
            auto iter = mainItor->second.find(cross);
            if (iter != mainItor->second.end()) {
                endIndex = iter->second;
                break;
            }
        }
    }
    startRankItemIndex_ = firstItem;
    if (count == 0) {
        return;
    }
    for (const auto& item : flowMatrix) {
        flowMatrix_[item.first + count] = item.second;
    }

    decltype(inCache_) inCache(std::move(inCache_));
    for (const auto& item : inCache) {
        LOGD("LoadForward inCache_.insert mainIndex: %{public}d.", item + count);
        inCache_.insert(item + count);
    }

    mainCount_ += count;
    startIndex_ += count;
}

void RenderWaterFlow::CalculateViewPortSceneOne()
{
    // move to top/left of first row/column
    if (!NearZero(firstItemOffset_)) {
        if (inCache_.find(startIndex_ + 1) != inCache_.end()) {
            currentOffset_ += GetSize(flowCells_) + mainGap_ - firstItemOffset_;
            startIndex_++;
        }
        firstItemOffset_ = 0.0;
    }
    // Move up
    while (ceil(currentOffset_) > 0) {
        if (startIndex_ > 0) {
            currentOffset_ -= GetSize(flowCells_) + mainGap_;
            startIndex_--;
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
}

bool RenderWaterFlow::CalculateViewPortSceneTwo(bool& NeedContinue)
{
    NeedContinue = false;
    if (!NearZero(firstItemOffset_)) {
        currentOffset_ -= firstItemOffset_;
        firstItemOffset_ = 0.0;
    }
    // Move down
    while (startIndex_ < mainCount_ && (ceil(currentOffset_) < 0 || needCalculateViewPort_)) {
        currentOffset_ += GetSize(flowCells_) + mainGap_;
        startIndex_++;
    }
    needCalculateViewPort_ = false;
    if (currentOffset_ > 0) {
        firstItemOffset_ = GetSize(flowCells_) + mainGap_ - currentOffset_;
        currentOffset_ = 0.0;
        startIndex_--;
    } else if (!GreatOrEqual(0.0, BuildLazyFlowLayout(mainCount_, -currentOffset_))) {
        NeedContinue = true;
        return true;
    }
    currentOffset_ = 0.0;
    auto blank = CalculateBlankOfEnd();
    if (GreatOrEqual(0.0, blank)) {
        return false;
    }
    // request new item.
    blank -= BuildLazyFlowLayout(mainCount_, blank);
    if (blank <= 0) {
        return false;
    }
    blank = blank - firstItemOffset_;
    firstItemOffset_ = 0;
    // Move up
    while (ceil(blank) > 0) {
        if (startIndex_ == 0 && startRankItemIndex_ > 0) {
            LoadForward();
        }
        if (startIndex_ == 0) {
            break;
        }
        if (inCache_.find(startIndex_ - 1) == inCache_.end()) {
            bool vail = false;
            SupplyItems(vail, startIndex_ - 1);
        }
        blank -= GetSize(flowCells_) + mainGap_;
        startIndex_--;
    }
    firstItemOffset_ -= blank;
    if (firstItemOffset_ < 0) {
        firstItemOffset_ = 0;
    }
    reachTail_ = true;
    return true;
}

void RenderWaterFlow::CalculateViewPort()
{
    while (!NearZero(currentOffset_) || needCalculateViewPort_) {
        if (currentOffset_ > 0) {
            CalculateViewPortSceneOne();
        } else {
            bool needSkip = false;
            if (!CalculateViewPortSceneTwo(needSkip)) {
                return;
            }
            if (needSkip) {
                continue;
            }
        }
    }
}

double RenderWaterFlow::CalculateBlankOfEnd()
{
    double drawLength = 0.0 - firstItemOffset_;
    for (int32_t main = startIndex_; main < mainCount_; main++) {
        drawLength += GetSize(flowCells_) + mainGap_;
        if (GreatOrEqual(drawLength, mainSize_)) {
            break;
        }
    }
    return mainSize_ - drawLength;
}

bool RenderWaterFlow::CheckMainFull(int32_t mainIndex)
{
    auto mainItor = flowMatrix_.find(mainIndex);
    if (mainItor == flowMatrix_.end()) {
        return false;
    }

    if (crossCount_ < 0 || (mainItor->second.size() < static_cast<size_t>(crossCount_))) {
        return false;
    }

    return true;
}

double RenderWaterFlow::SupplyItems(
    bool& vailSupplyItem, int32_t mainIndex, int32_t itemIndex, bool needPosition, bool needRank)
{
    LOGD("%{public}s called mainIndex: %{public}d.", __PRETTY_FUNCTION__, mainIndex);
    loadingIndex_ = -1;
    ACE_SCOPED_TRACE("SupplyItems %d", mainIndex);
    auto mainItor = flowMatrix_.find(mainIndex);
    if (mainItor != flowMatrix_.end()) {
        if (crossCount_ < 0 || (mainItor->second.size() == static_cast<size_t>(crossCount_))) {
            needRank = false;
        }
    }

    if ((inCache_.find(mainIndex) == inCache_.end() || !CheckMainFull(mainIndex)) && (mainIndex != 0) && needRank) {
        Rank(mainIndex, itemIndex);
    }

    vailSupplyItem = false;

    auto iter = flowMatrix_.find(mainIndex);
    if (iter != flowMatrix_.end()) {
        int32_t frontIndex = -1;
        for (const auto& item : iter->second) {
            if (item.second == frontIndex) {
                continue;
            }
            if (((items_.find(item.second) != items_.end() && items_[item.second] != nullptr) ||
                    buildChildByIndex_(item.second)) &&
                GetItemCalSizeNeeded(items_[item.second])) {
                LOGD("SupplyItems resize() itemIndex: %{public}d", item.second);
                int32_t itemRowSpan = GetItemSpan(items_[item.second], true);
                int32_t itemColSpan = GetItemSpan(items_[item.second], false);
                int32_t itemMain = -1;
                int32_t itemCross = -1;
                if (!GetItemMainCrossIndex(item.second, itemMain, itemCross)) {
                    itemMain = mainIndex;
                    itemCross = item.first;
                }
                if (useScrollable_ == SCROLLABLE::VERTICAL) {
                    LayoutChild(items_[item.second], itemMain, itemCross, itemRowSpan, itemColSpan, needPosition);
                } else {
                    LayoutChild(items_[item.second], itemMain, itemCross, itemColSpan, itemRowSpan, needPosition);
                }
                vailSupplyItem = true;
            }
            frontIndex = item.second;
        }
        LOGD("SupplyItems inCache_.insert mainIndex: %{public}d.", mainIndex);
        inCache_.insert(mainIndex);
        return NearEqual(GetSize(flowCells_), Size::INFINITE_SIZE) ? 0.0 : GetSize(flowCells_);
    }
    return 0.0;
}

int32_t RenderWaterFlow::CalItemIndexInRank(int32_t mainIndex)
{
    int32_t itemIndex = -1;
    for (int32_t i = 1; (mainIndex - i) >= 0; i++) {
        auto mainItor = flowMatrix_.find(mainIndex - i);
        if (mainItor == flowMatrix_.end()) {
            continue;
        }
        for (int32_t cross = crossCount_ - 1; cross >= 0; cross--) {
            auto iter = mainItor->second.find(cross);
            if (iter == mainItor->second.end()) {
                continue;
            }
            if (itemIndex == -1) {
                // fine the first itemIndex
                itemIndex = iter->second + 1;
            } else if (itemIndex <= iter->second + 1) {
                // fine the max ID of itemIndex in the last line
                itemIndex = iter->second + 1;
            }
        }
        if (static_cast<int32_t>(mainItor->second.size()) == (crossCount_ - 1)) {
            // search to the end, then the row of flowMatrix_ is all layouted
            break;
        }
    }
    return itemIndex;
}

bool RenderWaterFlow::Rank(int32_t mainIndex, int32_t itemIndex)
{
    LOGD("%{public}s called. mainIndex:%{public}d itemIndex:%{public}d", __PRETTY_FUNCTION__, mainIndex, itemIndex);

    if (inCache_.find(mainIndex) != inCache_.end() && CheckMainFull(mainIndex)) {
        return true;
    }
    ACE_SCOPED_TRACE("Rank [%d]", mainIndex);

    if (itemIndex == -1) {
        itemIndex = CalItemIndexInRank(mainIndex);
    }

    if (itemIndex == -1) {
        LOGE("failed, itemIndex = -1, mainIndex = %d", mainIndex);
        return false;
    }
    bool isFilled = false;
    int32_t index = mainIndex;
    int32_t crossIndex = 0;
    bool placed = false;
    while (!isFilled) {
        int32_t itemMainSpan = -1;
        int32_t itemCrossSpan = -1;
        if (flowMatrixByIndex_.find(itemIndex) != flowMatrixByIndex_.end()) {
            itemIndex++;
            continue;
        }

        if (!GetItemSpanFromCache(itemIndex, itemMainSpan, itemCrossSpan)) {
            return false;
        }
        while (!CheckFlowPlaced(itemIndex, mainIndex, crossIndex, itemMainSpan, itemCrossSpan)) {
            GetNextFlow(mainIndex, crossIndex); // crossIndex++
            if (mainIndex > index) {
                isFilled = true;
                break;
            }
        }
        if (!isFilled) {
            placed = true;
        }
        itemIndex++;
    }
    return true;
}

void RenderWaterFlow::DealCache(int32_t start, int32_t end)
{
    if (loadingIndex_ != -1) {
        return;
    }

    std::set<int32_t> deleteItem;
    for (const auto& item : inCache_) {
        if (!(item < start - cacheCount_ || item > end + cacheCount_)) {
            continue;
        }
        // check all item of inCache_ is in viewport, if in viewport the cacheCount_ can't be delete
        bool deleteEnable = true;
        auto iter = flowMatrix_.find(item);
        if (iter != flowMatrix_.end()) {
            for (const auto& eachItem : iter->second) {
                auto eachItemStartMain = GetItemMainIndex(eachItem.second);
                if (items_[eachItem.second] == nullptr) {
                    continue;
                }
                auto eachItemEndMain =
                    eachItemStartMain + GetItemSpan(items_[eachItem.second], useScrollable_ != SCROLLABLE::HORIZONTAL);
                if (!(eachItemEndMain < (start - cacheCount_) || eachItemStartMain > (end + cacheCount_))) {
                    deleteEnable = false;
                    break;
                }
            }
        }

        if (deleteEnable) {
            deleteItem.insert(item);
        }
    }

    for (const auto& item : deleteItem) {
        DeleteItems(item, false);
    }
    LOGD("DealCache end: %{public}d, start: %{public}d", end, start);
    for (int32_t i = 1; i <= cacheCount_; i++) {
        if (inCache_.count(i + end) == 0 || !CheckMainFull(i + end)) {
            loadingIndex_ = i + end;
            LOGD("DealCache loadingIndex_: %{public}d.", loadingIndex_);
            break;
        }
        if (start >= i && ((inCache_.count(start - i) == 0) || !CheckMainFull(start - i))) {
            loadingIndex_ = start - i;
            break;
        }
    }
}

void RenderWaterFlow::DeleteItems(int32_t index, bool isTail)
{
    LOGD("%{public}s called. index: %{public}d", __PRETTY_FUNCTION__, index);
    if (!deleteChildByIndex_) {
        return;
    }

    auto iter = flowMatrix_.find(index);
    if (iter == flowMatrix_.end()) {
        return;
    }
    for (const auto& item : iter->second) {
        deleteChildByIndex_(item.second);
        RemoveChildByIndex(item.second);
    }

    inCache_.erase(index);
}

void RenderWaterFlow::ClearLayout(int32_t index)
{
    currentOffset_ = 0.0;
    showItem_.clear();
    childrenInRect_.clear();
    updateFlag_ = true;
    reachHead_ = false;
    reachTail_ = false;
    startMainPos_ = 0.0;
    endMainPos_ = 0.0;
    firstItemOffset_ = 0.0;
    endIndex_ = -1;
    mainScrollExtent_ = 0.0;
    lastOffset_ = 0.0;
    estimateHeight_ = 0.0;
    if (index > -1) {
        int32_t main = GetItemMainIndex(index);
        size_t rows = flowMatrix_.size();
        DeleteItemsInMatrix(rows, index);
        for (auto it = inCache_.begin(); it != inCache_.end();) {
            if (*it >= main) {
                inCache_.erase(it++);
            } else {
                it++;
            }
        }
        auto itFirst1 = itemSpanCache_.find(index);
        if (itFirst1 != itemSpanCache_.end()) {
            itemSpanCache_.erase(itFirst1, itemSpanCache_.end());
        }
        auto itFirst3 = flowMatrixByIndex_.find(index);
        if (itFirst3 != flowMatrixByIndex_.end()) {
            flowMatrixByIndex_.erase(itFirst3, flowMatrixByIndex_.end());
        }
        if (main <= startIndex_) {
            startIndex_ = main;
        }
    } else {
        startIndex_ = 0;
        inCache_.clear();
        flowMatrix_.clear();
        flowMatrixByIndex_.clear();
        itemSpanCache_.clear();
    }
}

void RenderWaterFlow::ClearItems(int32_t index)
{
    decltype(items_) items(std::move(items_));
    for (const auto& item : items) {
        if (index <= item.first) {
            deleteChildByIndex_(item.first);
            RemoveChildByIndex(item.first);
        }
    }
    loadingIndex_ = -1;
}

int32_t RenderWaterFlow::GetItemMainIndex(int32_t index) const
{
    auto iter = flowMatrixByIndex_.find(index);
    if (iter != flowMatrixByIndex_.end()) {
        return iter->second.begin()->first;
    }
    return -1;
}

bool RenderWaterFlow::GetItemMainCrossIndex(int32_t index, int32_t& mainIndex, int32_t& crossIndex)
{
    auto iter = flowMatrixByIndex_.find(index);
    if (iter != flowMatrixByIndex_.end()) {
        mainIndex = iter->second.begin()->first;
        crossIndex = iter->second.begin()->second;
        return true;
    }
    return false;
}

void RenderWaterFlow::OnDataSourceUpdated(int32_t index)
{
    LOGD("OnDataSourceUpdated called. index:%{public}d", index);
    if (items_.empty() && updateFlag_) {
        return;
    }

    ACE_SCOPED_TRACE("OnDataSourceUpdated %d", index);
    auto items = flowMatrix_.find(startIndex_);
    if (items != flowMatrix_.end() && items->second.size() > 0) {
        currentItemIndex_ = items->second.begin()->second;
    }
    if (index >= 0) {
        startRankItemIndex_ = index;
    } else {
        startRankItemIndex_ = 0;
    }
    auto offset = firstItemOffset_;
    ClearItems(index);
    ClearLayout(index);
    currentOffset_ = -offset;
    MarkNeedLayout();
}

bool RenderWaterFlow::CheckEndShowItemPlace(int32_t index)
{
    int32_t main = 0;
    int32_t cross = 0;
    if (!GetItemMainCrossIndex(index, main, cross)) {
        return false;
    }
    int32_t itemMainSpan = GetItemSpan(items_[index], useScrollable_ != SCROLLABLE::HORIZONTAL);
    int32_t mainIndex = main;
    for (; mainIndex < (main + itemMainSpan); mainIndex++) {
        auto items = flowMatrix_.find(mainIndex);
        if (items == flowMatrix_.end()) {
            return false;
        }
        if (crossCount_ < 0 || (items->second.size() < static_cast<size_t>(crossCount_))) {
            return true;
        }
    }
    auto itemsNext = flowMatrix_.find(mainIndex);
    if (itemsNext == flowMatrix_.end()) {
        return true;
    }
    auto item = itemsNext->second.find(cross);
    if (item == itemsNext->second.end()) {
        return true;
    }
    return false;
}

void RenderWaterFlow::CalculateWholeSize(double drawLength)
{
    if (flowMatrix_.empty()) {
        return;
    }
    if (totalCountFlag_) {
        int32_t lastRow = flowMatrix_.rbegin()->first;
        int32_t totalRows = mainCount_;
        lastRow++;
        totalRows++;
        if (lastRow > totalRows) {
            totalRows = lastRow;
        }
        double drawLength2 = totalRows * mainLength_ + (totalRows - 1) * mainGap_;
        if (lastRow <= totalRows && lastRow > 0) {
            mainScrollExtent_ = (lastRow * drawLength2) / totalRows;
        }
        estimateHeight_ = mainScrollExtent_;
        totalCountFlag_ = false;
    }
    bool isScrollable = false;
    if (estimateHeight_ > mainSize_) {
        isScrollable = true;
    }
    if (scrollBar_) {
        scrollBar_->SetScrollable(isScrollable);
    }
    // get the start position in flow
    LOGD("offset_ss startIndex_: %{public}d.", startIndex_);
    startMainPos_ = GetSize(flowCells_) * (startIndex_) + mainGap_ * (startIndex_ - 1);
    scrollBarExtent_ = GetSize(flowCells_) * (mainCount_) + mainGap_ * (mainCount_ - 1);
    if (!isScrollable) {
        currentOffset_ = 0.0;
    }
}

double RenderWaterFlow::GetEstimatedHeight()
{
    if (reachTail_) {
        // reach the end og flow, update the total scroll bar length
        estimateHeight_ = scrollBarExtent_;
    } else {
        estimateHeight_ = std::max(estimateHeight_, scrollBarExtent_);
    }
    return estimateHeight_;
}

void RenderWaterFlow::InitScrollBar(const RefPtr<Component>& component)
{
    const RefPtr<V2::WaterFlowComponent> flow = AceType::DynamicCast<V2::WaterFlowComponent>(component);
    if (!flow) {
        LOGE("RenderWaterFlow update failed.");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }

    if (!flow->GetController()) {
        flow->SetScrollBarDisplayMode(DisplayMode::OFF);
    }

    const RefPtr<ScrollBarTheme> theme = GetTheme<ScrollBarTheme>();
    if (!theme) {
        return;
    }
    if (scrollBar_) {
        scrollBar_->Reset();
    } else {
        RefPtr<WaterFlowScrollController> controller = AceType::MakeRefPtr<WaterFlowScrollController>();
        scrollBar_ = AceType::MakeRefPtr<ScrollBar>(flow->GetScrollBarDisplayMode(), theme->GetShapeMode());
        scrollBar_->SetScrollBarController(controller);
    }
    // set the scroll bar style
    scrollBar_->SetReservedHeight(theme->GetReservedHeight());
    scrollBar_->SetMinHeight(theme->GetMinHeight());
    scrollBar_->SetMinDynamicHeight(theme->GetMinDynamicHeight());
    auto& scrollBarColor = flow->GetScrollBarColor();
    if (!scrollBarColor.empty()) {
        scrollBarColor_ = Color::FromString(scrollBarColor);
    } else {
        scrollBarColor_ = theme->GetForegroundColor();
    }
    scrollBar_->SetForegroundColor(scrollBarColor_);
    scrollBar_->SetBackgroundColor(theme->GetBackgroundColor());
    scrollBar_->SetPadding(theme->GetPadding());
    scrollBar_->SetScrollable(true);
    if (!flow->GetScrollBarWidth().empty()) {
        const auto& width = StringUtils::StringToDimension(flow->GetScrollBarWidth());
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
    scrollBar_->InitScrollBar(AceType::WeakClaim(this), GetContext());
    SetScrollBarCallback();
}

void RenderWaterFlow::InitScrollBarProxy()
{
    if (!scrollBarProxy_) {
        return;
    }
    auto&& scrollCallback = [weakScroll = AceType::WeakClaim(this)](double value, int32_t source) {
        auto flow = weakScroll.Upgrade();
        if (!flow) {
            LOGE("render flow is released");
            return false;
        }
        return flow->UpdateScrollPosition(value, source);
    };
    scrollBarProxy_->UnRegisterScrollableNode(AceType::WeakClaim(this));
    scrollBarProxy_->RegisterScrollableNode({ AceType::WeakClaim(this), scrollCallback });
}

void RenderWaterFlow::SetScrollBarCallback()
{
    if (!scrollBar_ || !scrollBar_->NeedScrollBar()) {
        return;
    }
    auto&& barEndCallback = [weakFlow = AceType::WeakClaim(this)](int32_t value) {
        auto flow = weakFlow.Upgrade();
        if (!flow) {
            LOGE("render flow is released");
            return;
        }
        flow->scrollBarOpacity_ = value;
        flow->MarkNeedLayout(true);
    };
    auto&& scrollEndCallback = [weakFlow = AceType::WeakClaim(this)]() {
        auto flow = weakFlow.Upgrade();
        if (!flow) {
            LOGE("render flow is released");
            return;
        }
        LOGD("trigger scroll end callback");
    };
    auto&& scrollCallback = [weakScroll = AceType::WeakClaim(this)](double value, int32_t source) {
        auto flow = weakScroll.Upgrade();
        if (!flow) {
            LOGE("render flow is released");
            return false;
        }
        return flow->UpdateScrollPosition(value, source);
    };
    scrollBar_->SetCallBack(scrollCallback, barEndCallback, scrollEndCallback);
}

bool RenderWaterFlow::AnimateTo(const Dimension& position, float duration, const RefPtr<Curve>& curve)
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

Offset RenderWaterFlow::CurrentOffset()
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

void RenderWaterFlow::ScrollToEdge(OHOS::Ace::ScrollEdgeType edgeType, bool smooth)
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
    startRankItemIndex_ = 0;
    ClearItems();
    ClearLayout();
    MarkNeedLayout();
}

void RenderWaterFlow::DoJump(double position, int32_t source)
{
    double delta = position - animateDelta_;
    UpdateScrollPosition(delta, source);
    animateDelta_ = position;
}

void RenderWaterFlow::OnPaintFinish()
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

void RenderWaterFlow::OnPredictLayout(int64_t deadline)
{
    if (updateFlag_) {
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    if (!context->IsTransitionStop()) {
        LOGD("In page transition, skip predict.");
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
    LOGD("OnPredictLayout loadingIndex_: %{public}d.", loadingIndex_);
    ACE_SCOPED_TRACE("OnPredictLayout %d", loadingIndex_);
    if (GetSysTimestamp() + TIME_THRESHOLD > deadline) {
        MarkNeedPredictLayout();
        return;
    }
    bool vail = false;
    SupplyItems(vail, loadingIndex_, -1);
    if (vail) {
        MarkNeedPredictLayout();
    } else {
        loadingIndex_ = -1;
    }
}

bool RenderWaterFlow::IsAxisScrollable(AxisDirection direction)
{
    if (isVertical_) {
        if (direction == AxisDirection::UP && reachHead_) {
            return false;
        } else if (direction == AxisDirection::DOWN && reachTail_) {
            return false;
        } else if (direction == AxisDirection::NONE) {
            return false;
        }
    } else {
        if (direction == AxisDirection::LEFT && reachHead_) {
            return false;
        } else if (direction == AxisDirection::RIGHT && reachTail_) {
            return false;
        } else if (direction == AxisDirection::NONE) {
            return false;
        }
    }
    return true;
}

void RenderWaterFlow::HandleAxisEvent(const AxisEvent& event)
{
    double degree = 0.0f;
    if (!NearZero(event.horizontalAxis)) {
        degree = event.horizontalAxis;
    } else if (!NearZero(event.verticalAxis)) {
        degree = event.verticalAxis;
    }
    double offset = SystemProperties::Vp2Px(DP_PER_LINE_DESKTOP * LINE_NUMBER_DESKTOP * degree / MOUSE_WHEEL_DEGREES);
    UpdateScrollPosition(-offset, SCROLL_FROM_ROTATE);
}

WeakPtr<RenderNode> RenderWaterFlow::CheckAxisNode()
{
    return AceType::WeakClaim<RenderNode>(this);
}

std::vector<double> RenderWaterFlow::ParseCrossLength(double size, double gap)
{
    std::vector<double> lens;
    double crossLength = (size - (crossCount_ - 1) * gap) / crossCount_;
    for (int32_t i = 0; i < crossCount_; i++) {
        lens.push_back(crossLength);
    }

    return lens;
}

void RenderWaterFlow::OnChildAdded(const RefPtr<RenderNode>& renderNode)
{
    RenderNode::OnChildAdded(renderNode);
}

bool RenderWaterFlow::IsUseOnly()
{
    return true;
}

int32_t RenderWaterFlow::RequestNextFocus(bool vertical, bool reverse)
{
    KeyDirection key = DIRECTION_MAP.at(rightToLeft_).at(vertical).at(reverse);
    int32_t index = focusMove(key);
    if (index < 0) {
        return index;
    }
    return focusIndex_;
}

void RenderWaterFlow::UpdateFocusInfo(int32_t focusIndex)
{
    if (focusIndex < 0) {
        LOGW("Invalid focus index, update focus info failed.");
        return;
    }
    if (focusIndex != focusIndex_) {
        LOGD("Update focus index from %{public}d to %{public}d", focusIndex_, focusIndex);
        focusIndex_ = focusIndex;
        auto iter = flowMatrixByIndex_.find(focusIndex);
        if (iter != flowMatrixByIndex_.end()) {
            focusRow_ = iter->second.begin()->first;
            focusCol_ = iter->second.begin()->second;
        }
    }
}

int32_t RenderWaterFlow::GetItemSpan(const RefPtr<RenderNode>& child, bool isRow) const
{
    int32_t depth = DEFAULT_DEPTH;
    int32_t span = -1;
    auto item = child;
    auto flowItem = AceType::DynamicCast<RenderWaterFlowItem>(item);
    while (!flowItem && depth > 0) {
        if (!item || item->GetChildren().empty()) {
            return span;
        }
        item = item->GetChildren().front();
        flowItem = AceType::DynamicCast<RenderWaterFlowItem>(item);
        --depth;
    }
    if (flowItem) {
        if (isRow) {
            span = flowItem->GetRowSpan();
        } else {
            auto crossItor = itemSpanCache_.find(GetIndexByNode(child));
            if (crossItor != itemSpanCache_.end()) {
                span = crossItor->second.colSpan;
            } else {
                span = flowItem->GetColumnSpan();
            }
        }
    }
    return span < 1 ? 1 : span;
}

bool RenderWaterFlow::GetItemSpanFromCache(int32_t index, int32_t& rowSpan, int32_t& colSpan)
{
    auto itor = itemSpanCache_.find(index);
    if (itor != itemSpanCache_.end()) {
        rowSpan = itor->second.rowSpan;
        colSpan = itor->second.colSpan;
    } else {
        auto item = items_.find(index);
        if (item != items_.end()) {
            rowSpan = GetItemSpan(item->second, useScrollable_ != SCROLLABLE::HORIZONTAL);
            colSpan = GetItemSpan(item->second, useScrollable_ == SCROLLABLE::HORIZONTAL);
        } else {
            if (!getChildSpanByIndex_(index, useScrollable_ == SCROLLABLE::HORIZONTAL, rowSpan, colSpan)) {
                return false;
            }
        }
        Span span;
        span.rowSpan = rowSpan;
        span.colSpan = colSpan;
        itemSpanCache_.emplace(std::make_pair(index, span));
    }

    return true;
}

int32_t RenderWaterFlow::GetIndexByNode(const RefPtr<RenderNode>& child) const
{
    for (const auto& item : items_) {
        if (item.second == child) {
            return item.first;
        }
    }
    return -1;
}

int32_t RenderWaterFlow::GetIndexByFlow(int32_t row, int32_t column) const
{
    LOGD("%{public}s begin. row: %{public}d, column: %{public}d", __PRETTY_FUNCTION__, row, column);
    auto rowIter = flowMatrix_.find(row);
    if (rowIter != flowMatrix_.end()) {
        auto colIter = rowIter->second.find(column);
        if (colIter != rowIter->second.end()) {
            return colIter->second;
        }
    }
    return -1;
}

// Handle direction key move
int32_t RenderWaterFlow::focusMove(KeyDirection direction)
{
    int32_t nextRow = focusRow_ < 0 ? 0 : focusRow_;
    int32_t nextCol = focusCol_ < 0 ? 0 : focusCol_;
    int32_t next = focusIndex_;
    while (focusIndex_ == next || next < 0) {
        switch (direction) {
            case KeyDirection::UP:
                --nextRow;
                break;
            case KeyDirection::DOWN:
                ++nextRow;
                break;
            case KeyDirection::LEFT:
                --nextCol;
                break;
            case KeyDirection::RIGHT:
                ++nextCol;
                break;
            default:
                return -1;
        }
        if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
            if (nextRow < 0 || nextCol < 0 || nextRow >= mainCount_ || nextCol >= crossCount_) {
                return -1;
            }
        } else {
            if (nextRow < 0 || nextCol < 0 || nextRow >= crossCount_ || nextCol >= mainCount_) {
                return -1;
            }
        }

        next = GetIndexByFlow(nextRow, nextCol);
    }
    LOGD("PreFocus:%{public}d CurrentFocus:%{public}d", focusIndex_, next);
    focusRow_ = nextRow;
    focusCol_ = nextCol;
    focusIndex_ = next;
    return next;
}

void RenderWaterFlow::UpdateAccessibilityAttr()
{
    auto refPtr = accessibilityNode_.Upgrade();
    if (!refPtr) {
        LOGD("accessibility node is not enabled.");
        return;
    }
    auto collectionInfo = refPtr->GetCollectionInfo();
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        collectionInfo.rows = mainCount_;
        collectionInfo.columns = crossCount_;
    } else {
        collectionInfo.rows = crossCount_;
        collectionInfo.columns = mainCount_;
    }

    refPtr->SetCollectionInfo(collectionInfo);
}

void RenderWaterFlow::SetItemCalSizeNeeded(const RefPtr<RenderNode>& child, bool need)
{
    int32_t depth = DEFAULT_DEPTH;
    auto item = child;
    auto flowItem = AceType::DynamicCast<RenderWaterFlowItem>(item);
    while (!flowItem && depth > 0) {
        if (!item || item->GetChildren().empty()) {
            flowItem->SetCalSizeNeeded(need);
            return;
        }
        item = item->GetChildren().front();
        flowItem = AceType::DynamicCast<RenderWaterFlowItem>(item);
        --depth;
    }
    if (flowItem) {
        flowItem->SetCalSizeNeeded(need);
    }
}

bool RenderWaterFlow::GetItemCalSizeNeeded(const RefPtr<RenderNode>& child) const
{
    int32_t depth = DEFAULT_DEPTH;
    bool need = false;
    auto item = child;
    auto flowItem = AceType::DynamicCast<RenderWaterFlowItem>(item);
    while (!flowItem && depth > 0) {
        if (!item || item->GetChildren().empty()) {
            return need;
        }
        item = item->GetChildren().front();
        flowItem = AceType::DynamicCast<RenderWaterFlowItem>(item);
        --depth;
    }
    if (flowItem) {
        need = flowItem->GetCalSizeNeeded();
    }
    return need;
}

void RenderWaterFlow::CheckAndInsertItems(int32_t mainIndex, int32_t itemIndex)
{
    auto item = items_.find(itemIndex);
    if (((item != items_.end()) && (item->second == nullptr)) || (item == items_.end())) {
        bool vail = false;
        SupplyItems(vail, mainIndex, itemIndex);
    }
}

void RenderWaterFlow::OutputMatrix(int32_t rows, bool before)
{
    if (before) {
        LOGD("matrix_ss OutputMatrix before");
    } else {
        LOGD("matrix_ss OutputMatrix after");
    }
    int32_t cols[5];
    for (int32_t i = 0; i < rows; i++) {
        auto iterMain = flowMatrix_.find(i);
        if (iterMain == flowMatrix_.end()) {
            LOGD("matrix_ss matrix: %{public}d  %{public}d  %{public}d  %{public}d  %{public}d", -1, -1, -1, -1, -1);
            continue;
        }
        std::map<int32_t, int32_t> crossMap = iterMain->second;
        for (int32_t j = 0; j < crossCount_; j++) {
            auto iterCell = crossMap.find(j);
            if (iterCell != crossMap.end()) {
                cols[j] = iterCell->second;
            } else {
                cols[j] = -1;
            }
        }
    }
}

bool RenderWaterFlow::DeleteItemsInMatrix(size_t rows, int32_t itemIndex)
{
    bool deleteMainBeDelete = true;
    int32_t main = -1;
    int32_t cross = -1;
    if (!GetItemMainCrossIndex(itemIndex, main, cross)) {
        deleteMainBeDelete = false;
        return deleteMainBeDelete;
    }
    for (size_t i = 0; i < rows; i++) {
        auto iter5 = flowMatrix_.find(i);
        if (iter5 == flowMatrix_.end()) {
            continue;
        }
        std::map<int32_t, int32_t> mainMap2 = iter5->second;
        for (int32_t j = 0; j < crossCount_; j++) {
            auto iter6 = mainMap2.find(j);
            if (iter6 == mainMap2.end()) {
                continue;
            }
            if (iter6->second >= itemIndex) {
                mainMap2.erase(j);
            }
        }
        if (mainMap2.size() > 0) {
            flowMatrix_[i] = mainMap2;
        } else {
            flowMatrix_.erase(i);
        }
    }
    auto iter7 = flowMatrix_.find(main);
    if (iter7 != flowMatrix_.end()) {
        std::map<int32_t, int32_t> mainMap = iter7->second;
        for (int32_t k = 0; k < cross; k++) {
            auto iteminf = mainMap.find(k);
            if (iteminf == mainMap.end()) {
                continue;
            }

            int32_t Index = iteminf->second;
            int32_t mainIndex = GetItemMainIndex(Index);
            if (mainIndex == main) {
                deleteMainBeDelete = false;
                break;
            }
        }
    }
    return deleteMainBeDelete;
}
} // namespace OHOS::Ace::V2
