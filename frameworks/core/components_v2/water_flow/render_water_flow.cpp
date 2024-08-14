/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "base/log/event_report.h"
#include "core/components/common/layout/templates_parser.h"
#include "core/components_v2/water_flow/water_flow_scroll_controller.h"

namespace OHOS::Ace::V2 {
namespace {
constexpr int64_t MICROSEC_TO_NANOSEC = 1000;
constexpr int64_t MILLISEC_TO_NANOSEC = 1000000;
constexpr int64_t TIME_THRESHOLD = 3 * MILLISEC_TO_NANOSEC; // milliseconds
constexpr int32_t ANIMATE_DURATION = 800;                   // ms
const RefPtr<CubicCurve> CURVE_SCROLL_TO_TOP = AceType::MakeRefPtr<CubicCurve>(0.0f, 0.3f, 0.2f, 1.0f);
constexpr int32_t DEFAULT_DEPTH = 10;
constexpr double MAX_CONSTRAINT_SCALE = 3.0;
constexpr double CENTER_POINT = 2.0;
constexpr int32_t CACHE_SIZE_SCALE = 3;
const std::string UNIT_AUTO = "auto";
} // namespace

RenderWaterFlow::~RenderWaterFlow()
{
    if (scrollBarProxy_) {
        scrollBarProxy_->UnRegisterScrollableNode(AceType::WeakClaim(this));
    }
}

void RenderWaterFlow::Update(const RefPtr<Component>& component)
{
    component_ = AceType::DynamicCast<V2::WaterFlowComponent>(component);
    if (!component_) {
        LOGE("RenderWaterFlow update failed.");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }

    auto controller = component_->GetController();
    if (controller) {
        controller->SetScrollNode(WeakClaim(this));
    }
    if (!animator_) {
        animator_ = CREATE_ANIMATOR(GetContext());
    }

    updateFlag_ = true;
    direction_ = component_->GetDirection();
    userColGap_ = component_->GetColumnsGap();
    userRowGap_ = component_->GetRowsGap();
    colsArgs_ = component_->GetColumnsArgs();
    rowsArgs_ = component_->GetRowsArgs();
    scrollBarProxy_ = component_->GetScrollBarProxy();
    InitScrollBar();
    InitScrollBarProxy();
    CreateScrollable();
    MarkNeedLayout();
}

void RenderWaterFlow::PerformLayout()
{
    if (RenderNode::GetChildren().empty() && !buildChildByIndex_) {
        return;
    }
    InitialFlowProp();
    // Adjust the view port out of items, caused by scrolling that may occur.
    AdjustViewPort();
    size_t itemIndex = GetNextSupplyedIndex();
    double targetPos = GetTargetPos();
    SupplyItems(itemIndex, targetPos);
    // Adjust the view port out of items, caused by supply items that may occur.
    // (view port at the tail and delete tail item continuously)
    AdjustViewPort();
    UpdateCacheItems();
    LayoutItems(cacheItems_);
    LayoutFooter();
    // Check if reach the tail of waterFlow
    reachTail_ = CheckReachTail();
    // Check if reach the head of waterFlow
    reachHead_ = CheckReachHead();
    if (reachHead_) {
        viewportStartPos_ = 0.0;
    }

    if (!scrollBar_) {
        return;
    }
    scrollBar_->SetScrollable(false);
    if (scrollBar_ && (GetEstimatedHeight() > mainSize_)) {
        scrollBar_->SetScrollable(true);
    }

    if (!lastReachHead_ && reachHead_) {
        waterflowEventFlags_[WaterFlowEvents::REACH_START] = true;
    }
    if (!lastReachTail_ && reachTail_) {
        waterflowEventFlags_[WaterFlowEvents::REACH_END] = true;
    }

    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        SetLayoutSize(GetLayoutParam().Constrain(Size(crossSize_, mainSize_)));
    } else {
        SetLayoutSize(GetLayoutParam().Constrain(Size(mainSize_, crossSize_)));
    }
    HandleScrollEvent();
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
        lastOffset_ = viewportStartPos_;
    } else {
        lastOffset_ = estimateHeight_ + viewportStartPos_ - mainSize_;
    }
    lastReachHead_ = reachHead_;
    lastReachTail_ = reachTail_;
    MarkNeedPredictLayout();
}

void RenderWaterFlow::AddChildByIndex(size_t index, const RefPtr<RenderNode>& renderNode)
{
    auto iter = items_.find(index);
    if (iter != items_.end() && iter->second == nullptr) {
        items_.erase(index);
    }

    auto itor = items_.try_emplace(index, renderNode);
    if (itor.second) {
        AddChild(renderNode);
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
            auto scrollBar = flow->scrollBar_;
            if (scrollBar) {
                scrollBar->HandleScrollBarEnd();
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
        // view port move up
        if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
            if (reachHead_) {
                return false;
            }
        } else {
            if (reachTail_) {
                return false;
            }
        }
    } else {
        // view port move down
        if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
            if (reachTail_) {
                return false;
            }
        } else {
            if (reachHead_) {
                return false;
            }
        }
    }
    viewportStartPos_ -= offset;
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

void RenderWaterFlow::SetChildPosition(const RefPtr<RenderNode>& child, size_t itemIndex)
{
    Offset offset;
    double mainPos = 0.0;
    double crossPos = 0.0;
    double mainSize = 0.0;
    auto iter = flowMatrix_.find(itemIndex);
    if (iter != flowMatrix_.end()) {
        mainPos = iter->second.mainPos;
        crossPos = iter->second.crossPos;
        mainSize = iter->second.mainSize;
    }
    // need to support set position with Flex::Direction
    switch (direction_) {
        case FlexDirection::COLUMN:
            // offset.y : item mainPos - viewPort offset
            offset = Offset(crossPos, mainPos - viewportStartPos_);
            break;
        case FlexDirection::COLUMN_REVERSE:
            // offset.y : [viewPort mainSize - (item mainSize + item mainPos)] - viewPort offse
            offset = Offset(crossPos, (mainSize_ - (mainPos + mainSize)) - viewportStartPos_);
            break;
        case FlexDirection::ROW:
            // offset.x : item mainPos - viewPort offset
            offset = Offset(mainPos - viewportStartPos_, crossPos);
            break;
        case FlexDirection::ROW_REVERSE:
            // offset.x : [viewPort mainSize - (item mainSize + item mainPos)] - viewPort offse
            offset = Offset((mainSize_ - (mainPos + mainSize)) - viewportStartPos_, crossPos);
            break;
        default:
            return;
    }
    child->SetPosition(offset);
    child->SetVisible(true);
}

void RenderWaterFlow::GetFlowSize()
{
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
    cacheSize_ = mainSize_ * CACHE_SIZE_SCALE;
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
    if (GreatOrEqual(crossGap_, crossSize_)) {
        crossGap_ = 0.0;
    }
}

void RenderWaterFlow::CallItemConstraintSize()
{
    ItemConstraintSize size;
    auto pipelineContext = GetContext().Upgrade();
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        size.maxCrossSize = std::max(NormalizePercentToPx(component_->GetMaxWidth(), false),
            NormalizePercentToPx(component_->GetMinWidth(), false));
        size.minCrossSize = std::min(NormalizePercentToPx(component_->GetMaxWidth(), false),
            NormalizePercentToPx(component_->GetMinWidth(), false));
        size.maxMainSize = std::max(NormalizePercentToPx(component_->GetMaxHeight(), true),
            NormalizePercentToPx(component_->GetMinHeight(), true));
        size.minMainSize = std::min(NormalizePercentToPx(component_->GetMaxHeight(), true),
            NormalizePercentToPx(component_->GetMinHeight(), true));
        mainMaxConstraintSize_ = MAX_CONSTRAINT_SCALE * pipelineContext->GetRootHeight();
    } else {
        size.maxCrossSize = std::max(NormalizePercentToPx(component_->GetMaxHeight(), true),
            NormalizePercentToPx(component_->GetMinHeight(), true));
        size.minCrossSize = std::min(NormalizePercentToPx(component_->GetMaxHeight(), true),
            NormalizePercentToPx(component_->GetMinHeight(), true));
        size.maxMainSize = std::max(NormalizePercentToPx(component_->GetMaxWidth(), false),
            NormalizePercentToPx(component_->GetMinWidth(), false));
        size.minMainSize = std::min(NormalizePercentToPx(component_->GetMaxWidth(), false),
            NormalizePercentToPx(component_->GetMinWidth(), false));
        mainMaxConstraintSize_ = MAX_CONSTRAINT_SCALE * pipelineContext->GetRootWidth();
    }

    // exchange and make sure the max is larger then the min.
    itemConstraintSize_.maxCrossSize = std::max(size.maxCrossSize, size.minCrossSize);
    itemConstraintSize_.minCrossSize = std::min(size.maxCrossSize, size.minCrossSize);
    itemConstraintSize_.maxMainSize = std::max(size.maxMainSize, size.minMainSize);
    itemConstraintSize_.minMainSize = std::min(size.maxMainSize, size.minMainSize);

    // constraint with 3times of root.
    if (GreatOrEqual(itemConstraintSize_.maxMainSize, mainMaxConstraintSize_)) {
        itemConstraintSize_.maxMainSize = mainMaxConstraintSize_;
    }
    if (GreatOrEqual(itemConstraintSize_.minMainSize, mainMaxConstraintSize_)) {
        itemConstraintSize_.minMainSize = 0.0;
    }
    // constraint with 0, and set with default.
    if (LessOrEqual(itemConstraintSize_.maxMainSize, 0.0)) {
        itemConstraintSize_.maxMainSize = mainMaxConstraintSize_;
    }
    if (LessOrEqual(itemConstraintSize_.minMainSize, 0.0)) {
        itemConstraintSize_.minMainSize = 0.0;
    }
}

void RenderWaterFlow::InitialFlowProp()
{
    // Not first time layout after update, no need to initialize.
    if (!updateFlag_) {
        return;
    }

    // Not valid layout size, no need to initialize.
    auto maxLayoutSize = GetLayoutParam().GetMaxSize();
    if (!maxLayoutSize.IsValid() || maxLayoutSize.IsEmpty()) {
        return;
    }

    GetFlowSize();
    CallGap();
    CallItemConstraintSize();
    crossSideSize_.clear();
    TemplatesParser parser;
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        crossSideSize_ = parser.ParseArgs(WeakClaim(this), PreParseArgs(colsArgs_), crossSize_, crossGap_);
    } else {
        crossSideSize_ = parser.ParseArgs(WeakClaim(this), PreParseArgs(rowsArgs_), crossSize_, crossGap_);
    }
    if (crossSideSize_.empty()) {
        crossSideSize_.push_back(crossSize_);
    }
    // Initialize the crossCount, default is 1
    crossCount_ = crossSideSize_.size();
    InitMainSideEndPos();
    viewportStartPos_ = 0.0;
    RemoveAllChild();
    ClearLayout(0, true);
    if (footer_) {
        RemoveChild(footer_);
        footer_ = nullptr;
    }
    RequestWaterFlowFooter();
    updateFlag_ = false;
}

LayoutParam RenderWaterFlow::MakeInnerLayoutParam(size_t itemIndex)
{
    LayoutParam innerLayout;
    double crossSize = 0.0;
    size_t crossIndex = 0;
    auto iter = flowMatrix_.find(itemIndex);
    if (iter != flowMatrix_.end()) {
        crossSize = iter->second.crossSize;
    } else {
        crossIndex = GetLastMainBlankCross();
        if (crossIndex < crossSideSize_.size()) {
            crossSize = crossSideSize_[crossIndex];
        }
    }
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        innerLayout.SetMinSize(Size(crossSize, 0));
        innerLayout.SetMaxSize(Size(crossSize, Size::INFINITE_SIZE));
    } else {
        innerLayout.SetMinSize(Size(0, crossSize));
        innerLayout.SetMaxSize(Size(Size::INFINITE_SIZE, crossSize));
    }
    return innerLayout;
}

void RenderWaterFlow::SupplyItems(size_t startIndex, double targetPos)
{
    size_t itemCrossIndex = 0;
    FlowStyle itemFlowStyle;
    while (LessNotEqual(GetLastMainBlankPos().GetY(), targetPos)) {
        if (items_.find(startIndex) == items_.end()) {
            if (!buildChildByIndex_(startIndex)) {
                break;
            }
        }

        auto flowItem = GetFlowItemByChild(items_[startIndex]);
        if (flowItem == nullptr) {
            startIndex++;
            continue;
        }
        flowItem->SetNeedRender(false);
        flowItem->Layout(MakeInnerLayoutParam(startIndex));
        flowItem->SetVisible(false);
        itemCrossIndex = GetLastMainBlankCross();
        itemFlowStyle.mainPos = GetLastMainBlankPos().GetY();
        itemFlowStyle.crossPos = GetLastMainBlankPos().GetX();
        itemFlowStyle.mainSize = GetMainSize(flowItem);
        itemFlowStyle = ConstraintItemSize(itemFlowStyle, itemCrossIndex);
        flowMatrix_.emplace(std::make_pair(startIndex, itemFlowStyle));
        if (itemsByCrossIndex_.size() > itemCrossIndex) {
            itemsByCrossIndex_.at(itemCrossIndex).emplace_back(startIndex);
        }
        if (itemCrossIndex < mainSideEndPos_.size()) {
            mainSideEndPos_[itemCrossIndex] +=
                Positive(itemFlowStyle.mainSize) ? (itemFlowStyle.mainSize + mainGap_) : itemFlowStyle.mainSize;
        }

        // reach the valid target index
        if (targetIndex_ >= 0 && static_cast<size_t>(targetIndex_) == startIndex) {
            targetPos = itemFlowStyle.mainPos + mainSize_;
        }
        startIndex++;
    }
    targetIndex_ = -1;
}

void RenderWaterFlow::LayoutItems(std::set<size_t>& items)
{
    LayoutParam innerLayoutParam;
    for (const auto& itemIndex : items) {
        if (items_.find(itemIndex) == items_.end()) {
            if (!buildChildByIndex_(itemIndex)) {
                continue;
            }
        }
        innerLayoutParam = MakeInnerLayoutParam(itemIndex);
        auto flowItem = GetFlowItemByChild(items_[itemIndex]);
        if (flowItem == nullptr) {
            continue;
        }
        flowItem->Layout(innerLayoutParam);
        SetChildPosition(flowItem, itemIndex);
    }
}

void RenderWaterFlow::GetFooterSize(double mainSize, double crossSize)
{
    if (!footer_ || NonPositive(mainSize) || NonPositive(crossSize)) {
        LOGE("footer is null");
        return;
    }
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        footerMaxSize_.SetWidth(std::min(crossSize, crossSize_));
        footerMaxSize_.SetHeight(std::min(mainSize, mainSize_));
    } else {
        footerMaxSize_.SetWidth(std::min(mainSize, mainSize_));
        footerMaxSize_.SetHeight(std::min(crossSize, crossSize_));
    }
}

void RenderWaterFlow::LayoutFooter()
{
    if (!footer_) {
        LOGE("footer is null");
        return;
    }
    footer_->SetVisible(false);
    LayoutParam innerLayoutParam;
    innerLayoutParam.SetMaxSize(footerMaxSize_);
    footer_->Layout(innerLayoutParam);
    SetFooterPosition();
}

void RenderWaterFlow::SetFooterPosition()
{
    if (!footer_) {
        return;
    }
    Offset offset;
    auto width = footerMaxSize_.Width();
    auto height = footerMaxSize_.Height();
    auto footerCurrentPos = GetTailPos();
    switch (direction_) {
        case FlexDirection::COLUMN:
            offset = Offset((crossSize_ - width) / CENTER_POINT, footerCurrentPos - viewportStartPos_);
            if (GreatOrEqual(offset.GetY(), mainSize_)) {
                return;
            }
            break;
        case FlexDirection::COLUMN_REVERSE:
            offset = Offset((crossSize_ - width) / CENTER_POINT, footerCurrentPos - viewportStartPos_ - height);
            if (LessOrEqual(offset.GetY(), -height)) {
                return;
            }
            break;
        case FlexDirection::ROW:
            offset = Offset(footerCurrentPos - viewportStartPos_, (crossSize_ - height) / CENTER_POINT);
            if (GreatOrEqual(offset.GetX(), mainSize_)) {
                return;
            }
            break;
        case FlexDirection::ROW_REVERSE:
            offset = Offset(footerCurrentPos - viewportStartPos_ - width, (crossSize_ - height) / CENTER_POINT);
            if (LessOrEqual(offset.GetX(), -width)) {
                return;
            }
            break;
        default:
            return;
    }
    footer_->SetPosition(offset);
    footer_->SetVisible(true);
}

void RenderWaterFlow::UpdateCacheItems()
{
    cacheItems_.clear();
    double itemMainMinPos = 0.0;
    double itemMainMaxPos = 0.0;
    double viewportEndPos = viewportStartPos_ + mainSize_ + cacheSize_;
    for (const auto& item : flowMatrix_) {
        if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
            itemMainMinPos = item.second.mainPos;
            itemMainMaxPos = item.second.mainPos + item.second.mainSize;
        } else {
            itemMainMinPos = (mainSize_ - (item.second.mainPos + item.second.mainSize));
            itemMainMaxPos = (mainSize_ - (item.second.mainPos + item.second.mainSize)) + item.second.mainSize;
        }
        if (!(GreatNotEqual(itemMainMinPos, viewportEndPos) ||
                LessNotEqual(itemMainMaxPos, viewportStartPos_ - cacheSize_))) {
            cacheItems_.emplace(item.first);
        }
    }
}

std::set<size_t> RenderWaterFlow::GetShowItems()
{
    std::set<size_t> showItems;
    showItems.clear();
    double itemMainMinPos = 0.0;
    double itemMainMaxPos = 0.0;
    double viewportEndPos = viewportStartPos_ + mainSize_;
    for (const auto& item : cacheItems_) {
        auto iter = flowMatrix_.find(item);
        if (iter != flowMatrix_.end()) {
            if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
                itemMainMinPos = iter->second.mainPos;
                itemMainMaxPos = iter->second.mainPos + iter->second.mainSize;
            } else {
                itemMainMinPos = (mainSize_ - (iter->second.mainPos + iter->second.mainSize));
                itemMainMaxPos = (mainSize_ - (iter->second.mainPos + iter->second.mainSize)) + iter->second.mainSize;
            }
            if (!(GreatNotEqual(itemMainMinPos, viewportEndPos) || LessNotEqual(itemMainMaxPos, viewportStartPos_))) {
                showItems.emplace(item);
            }
        }
    }
    return showItems;
}

void RenderWaterFlow::DealCache()
{
    std::set<size_t> deleteItem;
    double itemMainMinPos = 0.0;
    double itemMainMaxPos = 0.0;
    double cacheStartPos = viewportStartPos_ - cacheSize_;
    double cacheEndPos = viewportStartPos_ + mainSize_ + cacheSize_;
    for (const auto& item : items_) {
        auto iter = flowMatrix_.find(item.first);
        if (iter != flowMatrix_.end()) {
            if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
                itemMainMinPos = iter->second.mainPos;
                itemMainMaxPos = iter->second.mainPos + iter->second.mainSize;
            } else {
                itemMainMinPos = (mainSize_ - (iter->second.mainPos + iter->second.mainSize));
                itemMainMaxPos = (mainSize_ - (iter->second.mainPos + iter->second.mainSize)) + iter->second.mainSize;
            }
            if (GreatNotEqual(itemMainMinPos, cacheEndPos) || LessNotEqual(itemMainMaxPos, cacheStartPos)) {
                deleteItem.emplace(item.first);
            }
        }
    }

    for (const auto& item : deleteItem) {
        DeleteItems(item);
    }
}

void RenderWaterFlow::DeleteItems(size_t index)
{
    if (!deleteChildByIndex_) {
        return;
    }

    auto iter = items_.find(index);
    if (iter == items_.end()) {
        return;
    }
    deleteChildByIndex_(index);
    RemoveChildByIndex(index);
}

void RenderWaterFlow::ClearLayout(size_t index, bool clearAll)
{
    cacheItems_.clear();
    reachHead_ = false;
    reachTail_ = false;
    lastOffset_ = 0.0;
    ClearFlowMatrix(index, clearAll);
    ClearItemsByCrossIndex(index, clearAll);
    UpdateMainSideEndPos();
}

void RenderWaterFlow::ClearItems(size_t index)
{
    for (auto item = items_.begin(); item != items_.end();) {
        if (index <= item->first) {
            item->second->SetVisible(false);
            item = items_.erase(item);
        } else {
            item++;
        }
    }
}

void RenderWaterFlow::OnDataSourceUpdated(size_t index)
{
    if (items_.empty() && updateFlag_) {
        return;
    }

    if (!getTotalCount_) {
        return;
    }

    totalCount_ = getTotalCount_();
    ClearItems(index);
    ClearLayout(index);
    MarkNeedLayout();
}

double RenderWaterFlow::GetEstimatedHeight()
{
    estimateHeight_ =
        std::min(std::max(estimateHeight_, (std::abs(viewportStartPos_) + mainSize_)), GetLastMainPos().GetY());
    return estimateHeight_;
}

void RenderWaterFlow::InitScrollBar()
{
    if (!component_) {
        LOGE("RenderWaterFlow update failed.");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }

    if (scrollBar_) {
        scrollBar_->SetDisplayMode(component_->GetScrollBarDisplayMode());
        scrollBar_->Reset();
        return;
    }

    const RefPtr<ScrollBarTheme> theme = GetTheme<ScrollBarTheme>();
    if (!theme) {
        return;
    }

    RefPtr<WaterFlowScrollController> controller = AceType::MakeRefPtr<WaterFlowScrollController>();
    scrollBar_ = AceType::MakeRefPtr<ScrollBar>(component_->GetScrollBarDisplayMode(), theme->GetShapeMode());
    scrollBar_->SetScrollBarController(controller);

    // set the scroll bar style
    scrollBar_->SetMinHeight(theme->GetMinHeight());
    scrollBar_->SetMinDynamicHeight(theme->GetMinDynamicHeight());
    scrollBar_->SetForegroundColor(theme->GetForegroundColor());
    scrollBar_->SetBackgroundColor(theme->GetBackgroundColor());
    scrollBar_->SetPadding(theme->GetPadding());
    scrollBar_->SetInactiveWidth(theme->GetNormalWidth());
    scrollBar_->SetNormalWidth(theme->GetNormalWidth());
    scrollBar_->SetActiveWidth(theme->GetActiveWidth());
    scrollBar_->SetTouchWidth(theme->GetTouchWidth());
    switch (direction_) {
        case FlexDirection::COLUMN:
        case FlexDirection::COLUMN_REVERSE:
            useScrollable_ = SCROLLABLE::VERTICAL;
            scrollBar_->SetPositionMode(PositionMode::RIGHT);
            break;
        case FlexDirection::ROW:
        case FlexDirection::ROW_REVERSE:
            useScrollable_ = SCROLLABLE::HORIZONTAL;
            scrollBar_->SetPositionMode(PositionMode::BOTTOM);
            break;
        default:
            break;
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
            return;
        }
        flow->scrollBarOpacity_ = value;
        flow->MarkNeedLayout(true);
    };
    auto&& scrollEndCallback = [weakFlow = AceType::WeakClaim(this)]() {
        auto flow = weakFlow.Upgrade();
        if (!flow) {
            return;
        }
    };
    auto&& scrollCallback = [weakScroll = AceType::WeakClaim(this)](double value, int32_t source) {
        auto flow = weakScroll.Upgrade();
        if (!flow) {
            return false;
        }
        return flow->UpdateScrollPosition(value, source);
    };
    scrollBar_->SetCallBack(scrollCallback, barEndCallback, scrollEndCallback);
}

void RenderWaterFlow::ScrollToIndex(int32_t index)
{
    if (useScrollable_ == SCROLLABLE::NO_SCROLL || index < 0) {
        LOGW("Not supported.");
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is null");
        return;
    }

    auto iter = flowMatrix_.find(index);
    if (iter == flowMatrix_.end()) {
        targetIndex_ = index;
        size_t itemIndex = GetNextSupplyedIndex();
        SupplyItems(itemIndex, GetTargetPos());
        iter = flowMatrix_.find(index);
        if (iter == flowMatrix_.end()) {
            LOGE("scrollToIndex[item:%{public}d] failed.", index);
            return;
        }
    }

    double scrollToPos = 0.0;
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
        scrollToPos = iter->second.mainPos;
    } else {
        scrollToPos = (mainSize_ - (iter->second.mainPos + iter->second.mainSize)) + iter->second.mainSize - mainSize_;
    }
    AnimateToPos(scrollToPos, ANIMATE_DURATION, CURVE_SCROLL_TO_TOP);
}

void RenderWaterFlow::DoJump(double position, int32_t source)
{
    UpdateScrollPosition(viewportStartPos_ - position, source);
}

void RenderWaterFlow::OnPredictLayout(int64_t deadline)
{
    if (!NeedPredictLayout()) {
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    if (!context->IsTransitionStop()) {
        MarkNeedPredictLayout();
        return;
    }

    auto startTime = GetSysTimestamp(); // unit: ns
    DealCache();
    if (GetSysTimestamp() - startTime + TIME_THRESHOLD > deadline * MICROSEC_TO_NANOSEC) {
        MarkNeedPredictLayout();
        return;
    }

    // just need supply forward the main side, backwards already supply and keep in flowMatrix.
    size_t itemIndex = GetNextSupplyedIndex();
    SupplyItems(itemIndex, GetCacheTargetPos());
    UpdateCacheItems();
    LayoutItems(cacheItems_);
    dVPStartPosBackup_ = viewportStartPos_;
    totalCountBack_ = getTotalCount_();
    MarkNeedPredictLayout();
}

bool RenderWaterFlow::IsAxisScrollable(AxisDirection direction)
{
    bool ret = true;
    switch (direction_) {
        case FlexDirection::COLUMN:
            if ((direction == AxisDirection::UP && reachHead_) ||
                (direction == AxisDirection::DOWN && reachTail_)) {
                ret = false;
            }
            break;
        case FlexDirection::ROW:
            if ((direction == AxisDirection::LEFT && reachHead_) ||
                (direction == AxisDirection::RIGHT && reachTail_)) {
                ret = false;
            }
            break;
        case FlexDirection::COLUMN_REVERSE:
            if ((direction == AxisDirection::DOWN && reachHead_) ||
                (direction == AxisDirection::UP && reachTail_)) {
                ret = false;
            }
            break;
        case FlexDirection::ROW_REVERSE:
            if ((direction == AxisDirection::RIGHT && reachHead_) ||
                (direction == AxisDirection::LEFT && reachTail_)) {
                ret = false;
            }
            break;
        default:
            ret = false;
            break;
    }
    if (direction == AxisDirection::NONE) {
        ret = false;
    }
    return ret;
}

void RenderWaterFlow::HandleAxisEvent(const AxisEvent& event)
{
    double degree = 0.0;
    if (!NearZero(event.horizontalAxis)) {
        degree = event.horizontalAxis;
    } else if (!NearZero(event.verticalAxis)) {
        degree = event.verticalAxis;
    }
    double offset =
        PipelineBase::Vp2PxWithCurrentDensity(DP_PER_LINE_DESKTOP * LINE_NUMBER_DESKTOP * degree / MOUSE_WHEEL_DEGREES);
    UpdateScrollPosition(-offset, SCROLL_FROM_ROTATE);
}

WeakPtr<RenderNode> RenderWaterFlow::CheckAxisNode()
{
    return AceType::WeakClaim<RenderNode>(this);
}

void RenderWaterFlow::OnChildAdded(const RefPtr<RenderNode>& renderNode)
{
    Offset offset;
    switch (direction_) {
        case FlexDirection::COLUMN:
            offset.SetX(crossSize_ / CENTER_POINT);
            offset.SetY(mainSize_ + cacheSize_);
            break;
        case FlexDirection::ROW:
            offset.SetX(mainSize_ + cacheSize_);
            offset.SetY(crossSize_ / CENTER_POINT);
            break;
        case FlexDirection::COLUMN_REVERSE:
            offset.SetX(crossSize_ / CENTER_POINT);
            offset.SetY(0.0 - cacheSize_);
            break;
        case FlexDirection::ROW_REVERSE:
            offset.SetX(0.0 - cacheSize_);
            offset.SetY(crossSize_ / CENTER_POINT);
            break;
        default:
            break;
    }
    // set default position for animateTo(covering animation)
    renderNode->SetPosition(offset);
    RenderNode::OnChildAdded(renderNode);
}

bool RenderWaterFlow::IsUseOnly()
{
    return true;
}

RefPtr<RenderWaterFlowItem> RenderWaterFlow::GetFlowItemByChild(const RefPtr<RenderNode>& child)
{
    int32_t depth = DEFAULT_DEPTH;
    auto item = child;
    auto flowItem = AceType::DynamicCast<RenderWaterFlowItem>(item);
    while (!flowItem && depth > 0) {
        if (!item || item->GetChildren().empty()) {
            return nullptr;
        }
        item = item->GetChildren().front();
        flowItem = AceType::DynamicCast<RenderWaterFlowItem>(item);
        --depth;
    }
    return flowItem;
}

void RenderWaterFlow::OutputMatrix() {}

void RenderWaterFlow::RequestWaterFlowFooter()
{
    auto generator = itemGenerator_.Upgrade();
    footer_ = generator ? generator->RequestWaterFlowFooter() : RefPtr<RenderNode>();
    if (footer_) {
        AddChild(footer_);
        footer_->Layout(GetLayoutParam());
        footer_->SetVisible(false);
        auto mainSize = GetMainSize(footer_);
        auto crossSize = GetCrossSize(footer_);
        if (NonPositive(mainSize) || NonPositive(crossSize)) {
            RemoveChild(footer_);
            footer_ = nullptr;
        } else {
            GetFooterSize(mainSize, crossSize);
        }
    }
}

size_t RenderWaterFlow::GetLastSupplyedIndex()
{
    return flowMatrix_.empty() ? 0 : (--flowMatrix_.end())->first;
}

size_t RenderWaterFlow::GetNextSupplyedIndex()
{
    size_t index = 0;
    if (!flowMatrix_.empty()) {
        index = (--flowMatrix_.end())->first;
        index++;
    }
    return index;
}

double RenderWaterFlow::GetLastSupplyedMainSize()
{
    double result = 0.0;
    if (flowMatrix_.empty()) {
        return result;
    }
    size_t index = GetLastSupplyedIndex();
    auto iter = flowMatrix_.find(index);
    if (iter != flowMatrix_.end()) {
        result = iter->second.mainSize + iter->second.mainPos;
    }
    return result;
}

Offset RenderWaterFlow::GetLastMainBlankPos()
{
    Offset pos;
    size_t crossIndex = 0;
    if (mainSideEndPos_.empty() || mainSideEndPos_.size() != crossSideSize_.size()) {
        return pos;
    }
    pos.SetY(mainSideEndPos_.at(0));
    for (size_t i = 0; i < mainSideEndPos_.size(); i++) {
        if (LessNotEqual(mainSideEndPos_.at(i), pos.GetY())) {
            pos.SetY(mainSideEndPos_.at(i));
            crossIndex = i;
        }
    }
    pos.SetX(GetCrossEndPos(crossIndex));
    return pos;
}

size_t RenderWaterFlow::GetLastMainBlankCross()
{
    double pos = 0.0;
    size_t crossIndex = 0;
    if (mainSideEndPos_.empty()) {
        return crossIndex;
    }
    pos = mainSideEndPos_.at(0);
    for (size_t i = 0; i < mainSideEndPos_.size(); i++) {
        if (LessNotEqual(mainSideEndPos_.at(i), pos)) {
            pos = mainSideEndPos_.at(i);
            crossIndex = i;
        }
    }
    return crossIndex;
}

Offset RenderWaterFlow::GetLastMainPos()
{
    Offset pos(0.0, 0.0);
    size_t crossIndex = 0;
    if (mainSideEndPos_.empty() || mainSideEndPos_.size() != crossSideSize_.size()) {
        return pos;
    }
    double tempMainSidePos = mainSideEndPos_.at(0);
    for (size_t i = 0; i < mainSideEndPos_.size(); i++) {
        if (GreatNotEqual(mainSideEndPos_.at(i), tempMainSidePos)) {
            tempMainSidePos = mainSideEndPos_.at(i);
            crossIndex = i;
        }
    }
    pos.SetY(mainSideEndPos_.at(crossIndex) - mainGap_);
    pos.SetX(GetCrossEndPos(crossIndex));
    return pos;
}

double RenderWaterFlow::GetCrossEndPos(size_t crossIndex)
{
    double pos = 0.0;
    if (crossIndex >= crossSideSize_.size()) {
        return pos;
    }
    for (size_t i = 0; i < crossIndex; i++) {
        pos += crossSideSize_[i];
    }
    if (crossIndex > 0) {
        pos += crossIndex * crossGap_;
    }

    return pos;
}

double RenderWaterFlow::GetMainSize(const RefPtr<RenderNode>& item) const
{
    double size = 0.0;
    if (!item) {
        return size;
    }
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        size = item->GetLayoutSize().Height();
    } else {
        size = item->GetLayoutSize().Width();
    }

    return size;
}

double RenderWaterFlow::GetCrossSize(const RefPtr<RenderNode>& item) const
{
    double size = 0.0;
    if (!item) {
        return size;
    }

    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::COLUMN_REVERSE) {
        size = item->GetLayoutSize().Width();
    } else {
        size = item->GetLayoutSize().Height();
    }

    return size;
}

FlowStyle RenderWaterFlow::ConstraintItemSize(FlowStyle item, size_t crossIndex)
{
    FlowStyle result = item;
    if (GreatNotEqual(result.mainSize, itemConstraintSize_.maxMainSize)) {
        result.mainSize = itemConstraintSize_.maxMainSize;
    }
    if (LessNotEqual(result.mainSize, itemConstraintSize_.minMainSize)) {
        result.mainSize = itemConstraintSize_.minMainSize;
    }
    if (crossIndex < crossSideSize_.size()) {
        result.crossSize = crossSideSize_[crossIndex];
    }
    return result;
}

bool RenderWaterFlow::CheckReachHead()
{
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
        return LessOrEqual(viewportStartPos_, 0.0);
    }
    return LessOrEqual(0.0, viewportStartPos_);
}

bool RenderWaterFlow::CheckReachTail()
{
    double tailPos = GetTailPos();
    double footerOffset = 0.0;
    if (footer_) {
        switch (direction_) {
            case FlexDirection::COLUMN:
            case FlexDirection::COLUMN_REVERSE:
                footerOffset = footerMaxSize_.Height();
                break;
            case FlexDirection::ROW:
            case FlexDirection::ROW_REVERSE:
                footerOffset = footerMaxSize_.Width();
                break;
            default:
                break;
        }
    }
    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
        return (GreatOrEqual((viewportStartPos_) + mainSize_, tailPos + footerOffset));
    }
    return (GreatOrEqual(tailPos - footerOffset, viewportStartPos_));
}

void RenderWaterFlow::AdjustViewPort()
{
    double tailPos = GetTailPos();
    double footerOffset = 0.0;
    if (footer_) {
        switch (direction_) {
            case FlexDirection::COLUMN:
            case FlexDirection::COLUMN_REVERSE:
                footerOffset = footerMaxSize_.Height();
                break;
            case FlexDirection::ROW:
            case FlexDirection::ROW_REVERSE:
                footerOffset = footerMaxSize_.Width();
                break;
            default:
                break;
        }
    }

    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
        // Correct the position of view port to avoid oversize offset from scroller
        viewportStartPos_ = std::max(viewportStartPos_, 0.0);
        if (GreatOrEqual((viewportStartPos_) + mainSize_, tailPos + footerOffset)) {
            viewportStartPos_ = std::max((tailPos + footerOffset - mainSize_), 0.0);
        }
    } else {
        // Correct the position of view port to avoid oversize offset from scroller
        viewportStartPos_ = std::min(viewportStartPos_, 0.0);
        if (GreatOrEqual(tailPos - footerOffset, viewportStartPos_)) {
            viewportStartPos_ = std::min(tailPos - footerOffset, 0.0);
        }
    }
}

double RenderWaterFlow::GetTailPos()
{
    double result = 0.0;
    if (!getTotalCount_) {
        return result;
    }

    if (flowMatrix_.empty()) {
        if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
            return result;
        }
        return mainSize_;
    }

    if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
        result = DBL_MAX;
    } else {
        result = -DBL_MAX;
    }

    totalCount_ = getTotalCount_();
    auto iter = flowMatrix_.find(totalCount_ - 1);
    if (iter != flowMatrix_.end()) {
        if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
            result = GetLastMainPos().GetY();
        } else {
            result = mainSize_ - GetLastMainPos().GetY();
        }
    }
    return result;
}

double RenderWaterFlow::GetTargetPos()
{
    double result = 0.0;
    // valid targetIndex_
    if (targetIndex_ >= 0) {
        auto iter = flowMatrix_.find(targetIndex_);
        if (iter != flowMatrix_.end()) {
            result = iter->second.mainPos;
        } else {
            result = DBL_MAX;
        }
    } else {
        if (direction_ == FlexDirection::COLUMN || direction_ == FlexDirection::ROW) {
            result = viewportStartPos_ + mainSize_;
        } else {
            result = -viewportStartPos_ + mainSize_;
        }
    }
    return result;
}

double RenderWaterFlow::GetCacheTargetPos() const
{
    return viewportStartPos_ + mainSize_ + cacheSize_;
}

void RenderWaterFlow::AnimateToPos(const double& position, int32_t duration, const RefPtr<Curve>& curve)
{
    if (!animator_->IsStopped()) {
        animator_->Stop();
    }
    animator_->ClearInterpolators();
    auto animation = AceType::MakeRefPtr<CurveAnimation<double>>(viewportStartPos_, position, curve);
    animation->AddListener([weakScroll = AceType::WeakClaim(this)](double value) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->DoJump(value, SCROLL_FROM_ANIMATION);
        }
    });
    animator_->AddInterpolator(animation);
    animator_->SetDuration(duration);
    animator_->ClearStopListeners();
    animator_->Play();
}

void RenderWaterFlow::ClearFlowMatrix(size_t index, bool clearAll)
{
    if (!clearAll) {
        for (auto it = flowMatrix_.begin(); it != flowMatrix_.end();) {
            if (it->first >= index) {
                it = flowMatrix_.erase(it);
            } else {
                it++;
            }
        }
    } else {
        flowMatrix_.clear();
    }
}

void RenderWaterFlow::ClearItemsByCrossIndex(size_t index, bool clearAll)
{
    if (!clearAll) {
        for (auto& cross : itemsByCrossIndex_) {
            for (auto item = cross.begin(); item != cross.end();) {
                if (*item >= index) {
                    item = cross.erase(item);
                } else {
                    item++;
                }
            }
        }
    } else {
        itemsByCrossIndex_.clear();
        std::vector<size_t> item;
        for (size_t i = 0; i < crossCount_; i++) {
            itemsByCrossIndex_.emplace_back(item);
        }
    }
}

void RenderWaterFlow::UpdateMainSideEndPos()
{
    if (mainSideEndPos_.size() != itemsByCrossIndex_.size()) {
        return;
    }

    for (size_t i = 0; i < mainSideEndPos_.size(); i++) {
        int32_t maxIndex = -1;
        for (size_t j : itemsByCrossIndex_[i]) {
            maxIndex = std::max(maxIndex, static_cast<int32_t>(j));
        }
        auto iter = flowMatrix_.find(maxIndex);
        if (iter != flowMatrix_.end()) {
            mainSideEndPos_.at(i) = iter->second.mainPos + iter->second.mainSize + mainGap_;
        } else {
            mainSideEndPos_.at(i) = 0.0;
        }
    }
}

void RenderWaterFlow::InitMainSideEndPos()
{
    mainSideEndPos_.clear();
    for (size_t i = 0; i < crossCount_; i++) {
        mainSideEndPos_.emplace_back(0.0);
    }
}

void RenderWaterFlow::RemoveAllChild()
{
    items_.clear();
    ClearChildren();
}

bool RenderWaterFlow::NeedPredictLayout()
{
    return !(updateFlag_ || (NearEqual(dVPStartPosBackup_, viewportStartPos_) &&
       (totalCountBack_ == getTotalCount_())));
}

std::string RenderWaterFlow::PreParseArgs(const std::string& args)
{
    if (args.empty() || args.find(UNIT_AUTO) == std::string::npos) {
        return args;
    }
    std::string rowsArgs;
    std::vector<std::string> strs;
    StringUtils::StringSplitter(args, ' ', strs);
    std::string current;
    size_t rowArgSize = strs.size();
    for (size_t i = 0; i < rowArgSize; ++i) {
        current = strs[i];
        // "auto" means 1fr in waterflow
        if (strs[i] == std::string(UNIT_AUTO)) {
            current = "1fr";
        }
        rowsArgs += ' ' + current;
    }
    return rowsArgs;
}

void RenderWaterFlow::HandleScrollEvent()
{
    for (auto& event : waterflowEventFlags_) {
        switch (event.first) {
            case WaterFlowEvents::REACH_START:
                if (event.second) {
                    ResumeEventCallback(component_, &WaterFlowComponent::GetOnReachStart);
                    event.second = false;
                }
                break;
            case WaterFlowEvents::REACH_END:
                if (event.second) {
                    ResumeEventCallback(component_, &WaterFlowComponent::GetOnReachEnd);
                    event.second = false;
                }
                break;
            default:
                LOGW("This event does not handle in here, please check. event number: %{public}d", event.first);
                break;
        }
    }
}
} // namespace OHOS::Ace::V2
