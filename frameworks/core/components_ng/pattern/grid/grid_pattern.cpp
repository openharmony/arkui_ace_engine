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

#include "core/components_ng/pattern/grid/grid_pattern.h"

#include "base/log/dump_log.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/grid/grid_adaptive/grid_adaptive_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_utils.h"

namespace OHOS::Ace::NG {

namespace {
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;

const int32_t MAX_NUM_SIZE = 4;

double CalcCoordinatesDistance(double curFocusMain, double curFocusCross, double childMain, double childCross)
{
    return std::sqrt(std::pow((curFocusMain - childMain), 2) + std::pow((curFocusCross - childCross), 2));
}
} // namespace

RefPtr<LayoutAlgorithm> GridPattern::CreateLayoutAlgorithm()
{
    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, nullptr);
    std::vector<std::string> cols;
    StringUtils::StringSplitter(gridLayoutProperty->GetColumnsTemplate().value_or(""), ' ', cols);
    std::vector<std::string> rows;
    StringUtils::StringSplitter(gridLayoutProperty->GetRowsTemplate().value_or(""), ' ', rows);
    auto crossCount = cols.empty() ? Infinity<int32_t>() : static_cast<int32_t>(cols.size());
    auto mainCount = rows.empty() ? Infinity<int32_t>() : static_cast<int32_t>(rows.size());
    if (!gridLayoutProperty->IsVertical()) {
        std::swap(crossCount, mainCount);
    }
    info_.crossCount_ = crossCount;
    if (targetIndex_.has_value()) {
        info_.targetIndex_ = targetIndex_;
    }
    // When rowsTemplate and columnsTemplate is both setting, use static layout algorithm.
    if (!rows.empty() && !cols.empty()) {
        return MakeRefPtr<GridLayoutAlgorithm>(info_, crossCount, mainCount);
    }

    // When rowsTemplate and columnsTemplate is both not setting, use adaptive layout algorithm.
    if (rows.empty() && cols.empty()) {
        return MakeRefPtr<GridAdaptiveLayoutAlgorithm>(info_);
    }

    // If only set one of rowTemplate and columnsTemplate, use scrollable layout algorithm.
    const bool disableSkip = IsOutOfBoundary(true) || ScrollablePattern::AnimateRunning();
    const bool overScroll = CanOverScroll(GetScrollSource()) || forceOverScroll_;
    if (UseIrregularLayout()) {
        auto algo = MakeRefPtr<GridIrregularLayoutAlgorithm>(info_, overScroll);
        algo->SetEnableSkip(!disableSkip);
        return algo;
    }
    RefPtr<GridScrollLayoutAlgorithm> result;
    if (!gridLayoutProperty->GetLayoutOptions().has_value()) {
        result = MakeRefPtr<GridScrollLayoutAlgorithm>(info_, crossCount, mainCount);
    } else {
        result = MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(info_, crossCount, mainCount);
    }
    result->SetCanOverScroll(overScroll);
    result->SetScrollSource(GetScrollSource());
    if (ScrollablePattern::AnimateRunning()) {
        result->SetLineSkipping(!disableSkip);
    }
    return result;
}

void GridPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    info_.childrenCount_ = host->GetTotalChildCount();
}

RefPtr<NodePaintMethod> GridPattern::CreateNodePaintMethod()
{
    auto paint = MakeRefPtr<GridPaintMethod>(GetAxis() == Axis::HORIZONTAL, IsReverse(), GetScrollBar());
    CHECK_NULL_RETURN(paint, nullptr);
    CreateScrollBarOverlayModifier();
    paint->SetScrollBarOverlayModifier(GetScrollBarOverlayModifier());
    auto scrollEffect = GetScrollEdgeEffect();
    if (scrollEffect && scrollEffect->IsFadeEffect()) {
        paint->SetEdgeEffect(scrollEffect);
    }
    if (!gridContentModifier_) {
        gridContentModifier_ = AceType::MakeRefPtr<GridContentModifier>();
    }
    paint->SetContentModifier(gridContentModifier_);
    UpdateFadingEdge(paint);
    return paint;
}

void GridPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(gridLayoutProperty);

    if (multiSelectable_ && !isMouseEventInit_) {
        InitMouseEvent();
    }

    if (!multiSelectable_ && isMouseEventInit_) {
        UninitMouseEvent();
    }

    info_.axis_ = gridLayoutProperty->IsVertical() ? Axis::VERTICAL : Axis::HORIZONTAL;
    isConfigScrollable_ = gridLayoutProperty->IsConfiguredScrollable();
    if (!isConfigScrollable_) {
        return;
    }
    SetAxis(info_.axis_);
    if (!GetScrollableEvent()) {
        AddScrollEvent();
    }

    SetEdgeEffect();

    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetScrollBarProperty()) {
        SetScrollBar(paintProperty->GetScrollBarProperty());
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
    }
    SetAccessibilityAction();
    Register2DragDropManager();
    if (IsNeedInitClickEventRecorder()) {
        Pattern::InitClickEventRecorder();
    }
    auto overlayNode = host->GetOverlayNode();
    if (!overlayNode && paintProperty->GetFadingEdge().value_or(false)) {
        CreateAnalyzerOverlay(host);
    }
}

void GridPattern::MultiSelectWithoutKeyboard(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> children;
    host->GenerateOneDepthVisibleFrame(children);
    for (const auto& itemFrameNode : children) {
        auto itemEvent = itemFrameNode->GetEventHub<EventHub>();
        CHECK_NULL_VOID(itemEvent);
        if (!itemEvent->IsEnabled()) {
            continue;
        }

        auto itemPattern = itemFrameNode->GetPattern<GridItemPattern>();
        CHECK_NULL_VOID(itemPattern);
        if (!itemPattern->Selectable()) {
            continue;
        }
        auto itemGeometry = itemFrameNode->GetGeometryNode();
        CHECK_NULL_VOID(itemGeometry);
        auto context = itemFrameNode->GetRenderContext();
        CHECK_NULL_VOID(context);

        auto itemRect = itemGeometry->GetFrameRect();
        auto iter = itemToBeSelected_.find(itemFrameNode->GetId());
        if (iter == itemToBeSelected_.end()) {
            auto result = itemToBeSelected_.emplace(itemFrameNode->GetId(), ItemSelectedStatus());
            iter = result.first;
            iter->second.onSelected = itemPattern->GetEventHub<GridItemEventHub>()->GetOnSelect();
            iter->second.selectChangeEvent = itemPattern->GetEventHub<GridItemEventHub>()->GetSelectChangeEvent();
        }
        auto startMainOffset = mouseStartOffset_.GetMainOffset(info_.axis_);
        if (info_.axis_ == Axis::VERTICAL) {
            iter->second.rect = itemRect + OffsetF(0, totalOffsetOfMousePressed_ - startMainOffset);
        } else {
            iter->second.rect = itemRect + OffsetF(totalOffsetOfMousePressed_ - startMainOffset, 0);
        }

        if (!selectedZone.IsIntersectWith(itemRect)) {
            itemPattern->MarkIsSelected(false);
            iter->second.selected = false;
            context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        } else {
            itemPattern->MarkIsSelected(true);
            iter->second.selected = true;
            context->OnMouseSelectUpdate(true, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        }
    }

    DrawSelectedZone(selectedZone);
}

void GridPattern::ClearMultiSelect()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> children;
    host->GenerateOneDepthAllFrame(children);
    for (const auto& item : children) {
        if (!AceType::InstanceOf<FrameNode>(item)) {
            continue;
        }

        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        auto itemPattern = itemFrameNode->GetPattern<GridItemPattern>();
        CHECK_NULL_VOID(itemPattern);
        auto selectedStatus = itemToBeSelected_.find(itemFrameNode->GetId());
        if (selectedStatus != itemToBeSelected_.end()) {
            selectedStatus->second.selected = false;
        }
        itemPattern->MarkIsSelected(false);
        auto renderContext = itemFrameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
    }

    ClearSelectedZone();
}

bool GridPattern::IsItemSelected(const GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto node = host->FindChildByPosition(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    CHECK_NULL_RETURN(node, false);
    auto itemPattern = node->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN(itemPattern, false);
    return itemPattern->IsSelected();
}

void GridPattern::FireOnScrollStart()
{
    UIObserverHandler::GetInstance().NotifyScrollEventStateChange(
        AceType::WeakClaim(this), ScrollEventType::SCROLL_START);
    SuggestOpIncGroup(true);
    PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_LIST_FLING, PerfActionType::FIRST_MOVE, "");
    if (GetScrollAbort()) {
        return;
    }
    if (scrollStop_) {
        // onScrollStart triggers immediately on gesture dragStart, but onScrollStop marks scrollStop_ to true on
        // gesture dragEnd, and consumes it/fires onScrollStop after layout. When the user quickly swipes twice, the
        // second onScrollStart can trigger before the first onScrollEnd. In this case, we let the two events annihilate
        // each other and fire neither.
        scrollStop_ = false;
        return;
    }
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        scrollBar->PlayScrollBarAppearAnimation();
    }
    StopScrollBarAnimatorByProxy();
    FireObserverOnScrollStart();
    auto pipeline = GetContext();
    if (pipeline) {
        pipeline->GetFocusManager()->SetNeedTriggerScroll(std::nullopt);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollStart = hub->GetOnScrollStart();
    CHECK_NULL_VOID(onScrollStart);
    onScrollStart();
}

void GridPattern::FireOnReachStart(const OnReachEvent& onReachStart)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (info_.startIndex_ == 0) {
        if (!isInitialized_) {
            FireObserverOnReachStart();
            if (onReachStart) {
                onReachStart();
                AddEventsFiredInfo(ScrollableEventType::ON_REACH_START);
            }
        }
        auto finalOffset = info_.currentHeight_ - info_.prevHeight_;
        if (!NearZero(finalOffset)) {
            bool scrollUpToStart =
                GreatOrEqual(info_.prevHeight_, 0.0) && LessOrEqual(info_.currentHeight_, 0.0);
            bool scrollDownToStart =
                LessNotEqual(info_.prevHeight_, 0.0) && GreatOrEqual(info_.currentHeight_, 0.0);
            if (scrollUpToStart || scrollDownToStart) {
                FireObserverOnReachStart();
                CHECK_NULL_VOID(onReachStart);
                ACE_SCOPED_TRACE("OnReachStart, scrollUpToStart:%u, scrollDownToStart:%u, id:%d, tag:Grid",
                    scrollUpToStart, scrollDownToStart, static_cast<int32_t>(host->GetAccessibilityId()));
                onReachStart();
                AddEventsFiredInfo(ScrollableEventType::ON_REACH_START);
            }
        }
    }
}

void GridPattern::FireOnReachEnd(const OnReachEvent& onReachEnd)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (info_.endIndex_ == (info_.childrenCount_ - 1)) {
        if (!isInitialized_) {
            FireObserverOnReachEnd();
        }
        auto finalOffset = info_.currentHeight_ - info_.prevHeight_;
        if (!NearZero(finalOffset)) {
            bool scrollDownToEnd = LessNotEqual(info_.prevHeight_, endHeight_) &&
                                   GreatOrEqual(info_.currentHeight_, endHeight_);
            bool scrollUpToEnd = GreatNotEqual(info_.prevHeight_, endHeight_) &&
                                 LessOrEqual(info_.currentHeight_, endHeight_);
            if (scrollDownToEnd || scrollUpToEnd) {
                FireObserverOnReachEnd();
                CHECK_NULL_VOID(onReachEnd);
                ACE_SCOPED_TRACE("OnReachEnd, scrollUpToEnd:%u, scrollDownToEnd:%u, id:%d, tag:Grid", scrollUpToEnd,
                    scrollDownToEnd, static_cast<int32_t>(host->GetAccessibilityId()));
                onReachEnd();
                AddEventsFiredInfo(ScrollableEventType::ON_REACH_END);
            }
        }
    }
}

void GridPattern::FireOnScrollIndex(bool indexChanged, const ScrollIndexFunc& onScrollIndex)
{
    CHECK_NULL_VOID(indexChanged && onScrollIndex);
    onScrollIndex(info_.startIndex_, info_.endIndex_);
}

SizeF GridPattern::GetContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    return geometryNode->GetPaddingSize();
}

float GridPattern::GetMainGap() const
{
    float mainGap = 0.0;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, info_.axis_);
    return mainGap;
}

bool GridPattern::IsFadingBottom() const
{
    float mainSize = info_.lastMainSize_ - info_.contentEndPadding_;
    if (LessNotEqual(info_.totalHeightOfItemsInView_, mainSize) && info_.startIndex_ == 0) {
        return Positive(info_.currentOffset_);
    } else {
        return !info_.offsetEnd_;
    }
}

bool GridPattern::UpdateCurrentOffset(float offset, int32_t source)
{
    if (!isConfigScrollable_ || !scrollable_) {
        return true;
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    // check edgeEffect is not springEffect
    if (!HandleEdgeEffect(offset, source, GetContentSize())) {
        if (IsOutOfBoundary(true)) {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        return false;
    }
    SetScrollSource(source);
    FireAndCleanScrollingListener();
    if (info_.synced_) {
        info_.prevOffset_ = info_.currentOffset_;
        info_.synced_ = false;
    }
    // When finger moves down, offset is positive.
    // When finger moves up, offset is negative.
    bool irregular = UseIrregularLayout();
    float mainGap = GetMainGap();
    auto itemsHeight = info_.GetTotalHeightOfItemsInView(mainGap, irregular);
    if (info_.offsetEnd_) {
        if (source == SCROLL_FROM_UPDATE) {
            float overScroll = 0.0f;
            if (irregular) {
                overScroll = info_.GetDistanceToBottom(GetMainContentSize(), itemsHeight, mainGap);
            } else {
                overScroll = info_.currentOffset_ - (GetMainContentSize() - itemsHeight);
            }
            auto friction = CalculateFriction(std::abs(overScroll) / GetMainContentSize());
            offset *= friction;
        }
        auto userOffset = FireOnWillScroll(-offset);
        info_.currentOffset_ -= userOffset;

        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

        if (GreatNotEqual(info_.currentOffset_, GetMainContentSize() - itemsHeight)) {
            info_.offsetEnd_ = false;
            info_.reachEnd_ = false;
        }

        return true;
    }
    if (info_.reachStart_) {
        if (source == SCROLL_FROM_UPDATE) {
            auto friction = CalculateFriction(std::abs(info_.currentOffset_) / GetMainContentSize());
            offset *= friction;
        }
        auto userOffset = FireOnWillScroll(-offset);
        info_.currentOffset_ -= userOffset;

        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

        if (LessNotEqual(info_.currentOffset_, 0.0)) {
            info_.reachStart_ = false;
        }
        return true;
    }
    auto userOffset = FireOnWillScroll(-offset);
    info_.currentOffset_ -= userOffset;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
}

bool GridPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto gridLayoutAlgorithm = DynamicCast<GridLayoutBaseAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(gridLayoutAlgorithm, false);
    const auto& gridLayoutInfo = gridLayoutAlgorithm->GetGridLayoutInfo();
    auto eventhub = GetEventHub<GridEventHub>();
    CHECK_NULL_RETURN(eventhub, false);
    Dimension offset(0, DimensionUnit::VP);
    Dimension offsetPx(gridLayoutInfo.currentOffset_, DimensionUnit::PX);
    auto offsetVpValue = offsetPx.ConvertToVp();
    offset.SetValue(offsetVpValue);
    scrollbarInfo_ = eventhub->FireOnScrollBarUpdate(gridLayoutInfo.startIndex_, offset);
    if (!isInitialized_ || info_.startIndex_ != gridLayoutInfo.startIndex_) {
        eventhub->FireOnScrollToIndex(gridLayoutInfo.startIndex_);
    }

    bool indexChanged = (gridLayoutInfo.startIndex_ != info_.startIndex_) ||
                        (gridLayoutInfo.endIndex_ != info_.endIndex_);
    bool offsetEnd = info_.offsetEnd_;
    info_ = gridLayoutInfo;
    info_.synced_ = true;
    AnimateToTarget(scrollAlign_, layoutAlgorithmWrapper);

    info_.reachStart_ =
        info_.startIndex_ == 0 && GreatOrEqual(info_.currentOffset_, 0.0f);

    info_.currentHeight_ = EstimateHeight();
    if (!offsetEnd && info_.offsetEnd_) {
        endHeight_ = info_.currentHeight_;
    }
    ProcessEvent(indexChanged, info_.currentHeight_ - info_.prevHeight_);
    info_.prevHeight_ = info_.currentHeight_;
    info_.extraOffset_.reset();
    SetScrollSource(SCROLL_FROM_NONE);
    UpdateScrollBarOffset();
    if (config.frameSizeChange) {
        if (GetScrollBar() != nullptr) {
            GetScrollBar()->ScheduleDisappearDelayTask();
        }
    }
    CheckRestartSpring(false);
    CheckScrollable();
    MarkSelectedItems();
    isInitialized_ = true;
    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    return paintProperty->GetFadingEdge().value_or(false) || paintProperty->HasContentClip();
}

void GridPattern::CheckScrollable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gridLayoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(gridLayoutProperty);
    if (((info_.endIndex_ - info_.startIndex_ + 1) < info_.childrenCount_) ||
        (info_.GetTotalHeightOfItemsInView(GetMainGap()) > GetMainContentSize())) {
        scrollable_ = true;
    } else {
        scrollable_ = info_.startMainLineIndex_ != 0 || GetAlwaysEnabled();
    }

    SetScrollEnabled(scrollable_);

    if (!gridLayoutProperty->GetScrollEnabled().value_or(scrollable_)) {
        SetScrollEnabled(false);
    }
}

void GridPattern::ProcessEvent(bool indexChanged, float finalOffset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gridEventHub = host->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(gridEventHub);

    auto onScroll = gridEventHub->GetOnScroll();
    PrintOffsetLog(AceLogTag::ACE_GRID, host->GetId(), finalOffset);
    if (onScroll) {
        FireOnScroll(finalOffset, onScroll);
    }
    FireObserverOnDidScroll(finalOffset);
    auto onDidScroll = gridEventHub->GetOnDidScroll();
    if (onDidScroll) {
        FireOnScroll(finalOffset, onDidScroll);
    }
    auto onScrollIndex = gridEventHub->GetOnScrollIndex();
    FireOnScrollIndex(indexChanged, onScrollIndex);
    auto onReachStart = gridEventHub->GetOnReachStart();
    FireOnReachStart(onReachStart);
    auto onReachEnd = gridEventHub->GetOnReachEnd();
    FireOnReachEnd(onReachEnd);
    OnScrollStop(gridEventHub->GetOnScrollStop());
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    CHECK_NULL_VOID(focusHub->IsCurrentFocus());
    if (needTriggerFocus_) {
        if (triggerFocus_) {
            needTriggerFocus_ = false;
            triggerFocus_ = false;
            focusHub->GetNextFocusByStep(keyEvent_);
        } else {
            if (!focusIndex_.has_value()) {
                needTriggerFocus_ = false;
                return;
            }
            triggerFocus_ = true;
            auto child = host->GetOrCreateChildByIndex(focusIndex_.value());
            CHECK_NULL_VOID(child);
            auto childNode = child->GetHostNode();
            auto childFocusHub = childNode->GetFocusHub();
            if (childFocusHub && !childFocusHub->IsCurrentFocus()) {
                childFocusHub->RequestFocusImmediately();
            }
            MarkDirtyNodeSelf();
        }
        return;
    }
    if (indexChanged && focusIndex_.has_value()) {
        FireFocus();
    }
}

void GridPattern::FireFocus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    CHECK_NULL_VOID(focusHub->IsCurrentFocus());
    CHECK_NULL_VOID(focusIndex_.has_value());
    if (IsInViewport(focusIndex_.value())) {
        auto child = host->GetChildByIndex(focusIndex_.value());
        CHECK_NULL_VOID(child);
        auto childNode = child->GetHostNode();
        auto childFocusHub = childNode->GetFocusHub();
        if (!childFocusHub->IsCurrentFocus()) {
            focusHub->SetFocusDependence(FocusDependence::AUTO);
            childFocusHub->RequestFocusImmediately();
            TAG_LOGI(
                AceLogTag::ACE_GRID, "GridItem [%{public}d] scroll into viewport, Requests focus", focusIndex_.value());
        }
    } else {
        focusHub->LostChildFocusToSelf();
    }
}

void GridPattern::MarkDirtyNodeSelf()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void GridPattern::OnScrollEndCallback()
{
    isSmoothScrolling_ = false;
    if (AnimateStoped()) {
        scrollStop_ = true;
        MarkDirtyNodeSelf();
    }
}

std::pair<bool, bool> GridPattern::IsFirstOrLastFocusableChild(int32_t curMainIndex, int32_t curCrossIndex)
{
    std::unordered_set<int32_t> crossIndexSet;
    size_t maxSize = 0;
    for (int32_t index = curMainIndex - curFocusIndexInfo_.mainSpan + 1; index <= curMainIndex; index++) {
        auto tempIndexSet = GetFocusableChildCrossIndexesAt(index);
        if (tempIndexSet.size() > maxSize) {
            maxSize = tempIndexSet.size();
            crossIndexSet = tempIndexSet;
        }
    }
    auto findLesser = std::find_if(crossIndexSet.begin(), crossIndexSet.end(),
        [curCrossIndex](int32_t crossIndex) { return curCrossIndex > crossIndex; });
    auto findGreater = std::find_if(crossIndexSet.begin(), crossIndexSet.end(),
        [curCrossIndex](int32_t crossIndex) { return curCrossIndex < crossIndex; });
    return { curCrossIndex == 0 || findLesser == crossIndexSet.end(),
        curCrossIndex == info_.crossCount_ - 1 || findGreater == crossIndexSet.end() };
}

std::pair<FocusStep, FocusStep> GridPattern::GetFocusSteps(int32_t curMainIndex, int32_t curCrossIndex, FocusStep step)
{
    auto firstStep = FocusStep::NONE;
    auto secondStep = FocusStep::NONE;
    auto isFirstOrLastFocusable = IsFirstOrLastFocusableChild(curMainIndex, curCrossIndex);
    auto isFirstFocusable = isFirstOrLastFocusable.first;
    auto isLastFocusable = isFirstOrLastFocusable.second;
    if (info_.axis_ == Axis::VERTICAL) {
        if (isFirstFocusable && step == FocusStep::SHIFT_TAB) {
            firstStep = FocusStep::UP;
            secondStep = FocusStep::RIGHT_END;
        } else if (isLastFocusable && step == FocusStep::TAB) {
            firstStep = FocusStep::DOWN;
            secondStep = FocusStep::LEFT_END;
        }
    } else if (info_.axis_ == Axis::HORIZONTAL) {
        if (isFirstFocusable && step == FocusStep::SHIFT_TAB) {
            firstStep = FocusStep::LEFT;
            secondStep = FocusStep::DOWN_END;
        } else if (isLastFocusable && step == FocusStep::TAB) {
            firstStep = FocusStep::RIGHT;
            secondStep = FocusStep::UP_END;
        }
    }
    TAG_LOGI(AceLogTag::ACE_GRID, "Get focus steps. First step is %{public}d. Second step is %{public}d", firstStep,
        secondStep);
    return { firstStep, secondStep };
}

WeakPtr<FocusHub> GridPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto curFocus = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocus, nullptr);
    auto curFrame = curFocus->GetFrameNode();
    CHECK_NULL_RETURN(curFrame, nullptr);
    auto curPattern = curFrame->GetPattern();
    CHECK_NULL_RETURN(curPattern, nullptr);
    auto curItemPattern = AceType::DynamicCast<GridItemPattern>(curPattern);
    CHECK_NULL_RETURN(curItemPattern, nullptr);
    auto curItemProperty = curItemPattern->GetLayoutProperty<GridItemLayoutProperty>();
    CHECK_NULL_RETURN(curItemProperty, nullptr);
    auto irregularInfo = curItemPattern->GetIrregularItemInfo();
    bool hasIrregularItemInfo = irregularInfo.has_value();

    auto curMainIndex = curItemProperty->GetMainIndex().value_or(-1);
    auto curCrossIndex = curItemProperty->GetCrossIndex().value_or(-1);
    auto curMainSpan =
        hasIrregularItemInfo ? irregularInfo.value().mainSpan : curItemProperty->GetMainSpan(info_.axis_);
    auto curCrossSpan =
        hasIrregularItemInfo ? irregularInfo.value().crossSpan : curItemProperty->GetCrossSpan(info_.axis_);
    auto curMainStart =
        hasIrregularItemInfo ? irregularInfo.value().mainStart : curItemProperty->GetMainStart(info_.axis_);
    auto curCrossStart =
        hasIrregularItemInfo ? irregularInfo.value().crossStart : curItemProperty->GetCrossStart(info_.axis_);
    auto curMainEnd =
        hasIrregularItemInfo ? irregularInfo.value().mainEnd : curItemProperty->GetMainEnd(info_.axis_);
    auto curCrossEnd =
        hasIrregularItemInfo ? irregularInfo.value().crossEnd : curItemProperty->GetCrossEnd(info_.axis_);

    curFocusIndexInfo_.mainIndex = curMainIndex;
    curFocusIndexInfo_.crossIndex = curCrossIndex;
    curFocusIndexInfo_.mainSpan = curMainSpan;
    curFocusIndexInfo_.crossSpan = curCrossSpan;
    curFocusIndexInfo_.mainStart = curMainStart;
    curFocusIndexInfo_.mainEnd = curMainEnd;
    curFocusIndexInfo_.crossStart = curCrossStart;
    curFocusIndexInfo_.crossEnd = curCrossEnd;

    if (curMainIndex < 0 || curCrossIndex < 0) {
        TAG_LOGW(AceLogTag::ACE_GRID, "can't find focused child.");
        return nullptr;
    }
    if (info_.gridMatrix_.find(curMainIndex) == info_.gridMatrix_.end()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Can not find current main index: %{public}d", curMainIndex);
        return nullptr;
    }
    TAG_LOGI(AceLogTag::ACE_GRID,
        "GetNextFocusNode: Current:(%{public}d,%{public}d)-[%{public}d,%{public}d]. Focus: %{public}d", curMainIndex,
        curCrossIndex, curMainSpan, curCrossSpan, step);
    auto focusSteps = GetFocusSteps(curMainIndex, curCrossIndex, step);
    if (focusSteps.first != FocusStep::NONE && focusSteps.second != FocusStep::NONE) {
        auto firstStepRes = GetNextFocusNode(focusSteps.first, currentFocusNode);
        if (!firstStepRes.Upgrade()) {
            return nullptr;
        }
        auto secondStepRes = GetNextFocusNode(focusSteps.second, firstStepRes);
        if (!secondStepRes.Upgrade()) {
            int32_t index = GetIndexByFocusHub(firstStepRes);
            if (index > -1) {
                focusIndex_ = index;
            }
            return firstStepRes;
        }
        int32_t index = GetIndexByFocusHub(secondStepRes);
        if (index > -1) {
            focusIndex_ = index;
        }
        return secondStepRes;
    }
    auto indexes = GetNextIndexByStep(curMainIndex, curCrossIndex, curMainSpan, curCrossSpan, step);
    auto nextMainIndex = indexes.first;
    auto nextCrossIndex = indexes.second;
    while (nextMainIndex >= 0 && nextCrossIndex >= 0) {
        if (info_.gridMatrix_.find(nextMainIndex) == info_.gridMatrix_.end()) {
            TAG_LOGW(AceLogTag::ACE_GRID, "Can not find next main index: %{public}d", nextMainIndex);
            return nullptr;
        }
        auto nextMaxCrossCount = GetCrossCount();
        auto flag = (step == FocusStep::LEFT_END) || (step == FocusStep::RIGHT_END);
        auto weakChild = info_.hasBigItem_ ? SearchIrregularFocusableChild(nextMainIndex, nextCrossIndex)
                                                     : SearchFocusableChildInCross(nextMainIndex, nextCrossIndex,
                                                           nextMaxCrossCount, flag ? -1 : curMainIndex, curCrossIndex);
        auto child = weakChild.Upgrade();
        if (child && child->IsFocusable()) {
            ScrollToFocusNode(weakChild);
            int32_t index = GetIndexByFocusHub(weakChild);
            if (index > -1) {
                focusIndex_ = index;
            }
            return weakChild;
        }
        auto indexes = GetNextIndexByStep(nextMainIndex, nextCrossIndex, 1, 1, step);
        nextMainIndex = indexes.first;
        nextCrossIndex = indexes.second;
    }
    return nullptr;
}

int32_t GridPattern::GetIndexByFocusHub(const WeakPtr<FocusHub>& focusNode)
{
    auto focusHub = focusNode.Upgrade();
    CHECK_NULL_RETURN(focusHub, -1);
    auto node = focusHub->GetFrameNode();
    CHECK_NULL_RETURN(node, -1);
    auto property = AceType::DynamicCast<GridItemLayoutProperty>(node->GetLayoutProperty());
    CHECK_NULL_RETURN(property, -1);
    int32_t crossIndex = property->GetCrossIndex().value_or(-1);
    int32_t mainIndex = property->GetMainIndex().value_or(-1);
    return info_.FindInMatrixByMainIndexAndCrossIndex(mainIndex, crossIndex);
}

std::pair<int32_t, int32_t> GridPattern::GetNextIndexByStep(
    int32_t curMainIndex, int32_t curCrossIndex, int32_t curMainSpan, int32_t curCrossSpan, FocusStep step)
{
    auto curMainStart = info_.startMainLineIndex_;
    auto curMainEnd = info_.endMainLineIndex_;
    auto curChildStartIndex = info_.startIndex_;
    auto curChildEndIndex = info_.endIndex_;
    auto childrenCount = info_.childrenCount_;
    auto hasIrregularItems = info_.hasBigItem_;
    if (info_.gridMatrix_.find(curMainIndex) == info_.gridMatrix_.end()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Can not find current main index: %{public}d", curMainIndex);
        return { -1, -1 };
    }
    TAG_LOGI(AceLogTag::ACE_GRID,
        "Current: (%{public}d,%{public}d)-[%{public}d,%{public}d]. axis: %{public}d, step: %{public}d",
        curMainIndex, curCrossIndex, curMainSpan, curCrossSpan, info_.axis_, step);
    auto curMaxCrossCount = GetCrossCount();
    auto nextMainIndex = curMainIndex;
    auto nextCrossIndex = curCrossIndex;
    if ((step == FocusStep::UP_END && info_.axis_ == Axis::HORIZONTAL) ||
        (step == FocusStep::LEFT_END && info_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = 0;
        isLeftEndStep_ = hasIrregularItems ? true : false;
    } else if ((step == FocusStep::DOWN_END && info_.axis_ == Axis::HORIZONTAL) ||
               (step == FocusStep::RIGHT_END && info_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curMaxCrossCount - 1;
        isRightEndStep_ = hasIrregularItems ? true : false;
    } else if (((step == FocusStep::UP || step == FocusStep::SHIFT_TAB) && info_.axis_ == Axis::HORIZONTAL) ||
               ((step == FocusStep::LEFT || step == FocusStep::SHIFT_TAB) && info_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curCrossIndex - 1;
        isLeftStep_ = hasIrregularItems ? true : false;
    } else if ((step == FocusStep::UP && info_.axis_ == Axis::VERTICAL) ||
               (step == FocusStep::LEFT && info_.axis_ == Axis::HORIZONTAL)) {
        nextMainIndex = hasIrregularItems ? curMainIndex - curMainSpan : curMainIndex - 1;
        nextCrossIndex = curCrossIndex + static_cast<int32_t>((curCrossSpan - 1) / 2);
        isUpStep_ = hasIrregularItems ? true : false;
    } else if (((step == FocusStep::DOWN || step == FocusStep::TAB) && info_.axis_ == Axis::HORIZONTAL) ||
               ((step == FocusStep::RIGHT || step == FocusStep::TAB) && info_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curCrossIndex + curCrossSpan;
        isRightStep_ = hasIrregularItems ? true : false;
    } else if ((step == FocusStep::DOWN && info_.axis_ == Axis::VERTICAL) ||
               (step == FocusStep::RIGHT && info_.axis_ == Axis::HORIZONTAL)) {
        nextMainIndex = hasIrregularItems ? curMainIndex + 1 : curMainIndex + curMainSpan;
        nextCrossIndex = curCrossIndex + static_cast<int32_t>((curCrossSpan - 1) / 2);
        isDownStep_ = hasIrregularItems ? true : false;
    } else {
        TAG_LOGW(AceLogTag::ACE_GRID, "Next index return: Invalid step: %{public}d and axis: %{public}d", step,
            info_.axis_);
        return { -1, -1 };
    }
    if (curChildStartIndex == 0 && curMainIndex == 0 && nextMainIndex < curMainIndex) {
        nextMainIndex = curMainIndex;
    }
    if (curChildEndIndex == childrenCount - 1 && curMainIndex == curMainEnd && nextMainIndex > curMainIndex) {
        nextMainIndex = curMainIndex;
    }
    if (nextMainIndex == curMainIndex && nextCrossIndex == curCrossIndex) {
        TAG_LOGI(AceLogTag::ACE_GRID,
            "Next index return: Move stoped. Next index: (%{public}d,%{public}d) is same as current.", nextMainIndex,
            nextCrossIndex);
        ResetAllDirectionsStep();
        return { -1, -1 };
    }
    if (curChildStartIndex != 0 && curMainIndex == curMainStart && nextMainIndex < curMainIndex) {
        // Scroll item up.
        UpdateStartIndex(curChildStartIndex - 1);
        auto pipeline = GetContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    } else if (curChildEndIndex != childrenCount - 1 && curMainIndex == curMainEnd && nextMainIndex > curMainIndex) {
        // Scroll item down.
        UpdateStartIndex(curChildEndIndex + 1);
        auto pipeline = GetContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    }
    curMainStart = info_.startMainLineIndex_;
    curMainEnd = info_.endMainLineIndex_;
    if (nextMainIndex < curMainStart || nextMainIndex > curMainEnd) {
        ResetAllDirectionsStep();
        return { -1, -1 };
    }
    if (nextCrossIndex < 0) {
        ResetAllDirectionsStep();
        return { -1, -1 };
    }
    if (info_.gridMatrix_.find(nextMainIndex) == info_.gridMatrix_.end()) {
        ResetAllDirectionsStep();
        return { -1, -1 };
    }
    auto nextMaxCrossCount = GetCrossCount();
    if (nextCrossIndex >= nextMaxCrossCount) {
        TAG_LOGI(AceLogTag::ACE_GRID,
            "Next index: { %{public}d,%{public}d }. Next cross index is greater than max cross count: %{public}d.",
            nextMainIndex, nextCrossIndex, nextMaxCrossCount - 1);
        if (nextMaxCrossCount - 1 != (curCrossIndex + curCrossSpan - 1)) {
            TAG_LOGI(AceLogTag::ACE_GRID,
                "Current cross index: %{public}d is not the tail item. Return to the tail: { %{public}d,%{public}d }",
                curCrossIndex, nextMainIndex, nextMaxCrossCount - 1);
            return { nextMainIndex, nextMaxCrossCount - 1 };
        }
        ResetAllDirectionsStep();
        TAG_LOGI(AceLogTag::ACE_GRID, "Current cross index: %{public}d is the tail item. No next item can be found!",
            curCrossIndex);
        return { -1, -1 };
    }
    TAG_LOGI(AceLogTag::ACE_GRID, "Next index return: { %{public}d,%{public}d }.", nextMainIndex, nextCrossIndex);
    return { nextMainIndex, nextCrossIndex };
}

WeakPtr<FocusHub> GridPattern::SearchFocusableChildInCross(
    int32_t tarMainIndex, int32_t tarCrossIndex, int32_t maxCrossCount, int32_t curMainIndex, int32_t curCrossIndex)
{
    bool isDirectionLeft = true;
    auto indexLeft = tarCrossIndex;
    auto indexRight = tarCrossIndex;
    if (curMainIndex == tarMainIndex) {
        // Search on the same main index. Do not need search on both left and right side.
        if (tarCrossIndex > curCrossIndex) {
            // Only search on the right side.
            indexLeft = -1;
        } else if (tarCrossIndex < curCrossIndex) {
            // Only search on the left side.
            indexRight = maxCrossCount;
        } else {
            TAG_LOGW(AceLogTag::ACE_GRID, "Invalid search index: (%{public}d,%{public}d). It's same as current.",
                tarMainIndex, tarCrossIndex);
            return nullptr;
        }
    }
    while (indexLeft >= 0 || indexRight < maxCrossCount) {
        int32_t curIndex = indexLeft;
        if (indexLeft < 0) {
            curIndex = indexRight++;
        } else if (indexRight >= maxCrossCount) {
            curIndex = indexLeft--;
        } else {
            curIndex = isDirectionLeft ? indexLeft-- : indexRight++;
            isDirectionLeft = !isDirectionLeft;
        }
        auto weakChild = GetChildFocusNodeByIndex(tarMainIndex, curIndex);
        auto child = weakChild.Upgrade();
        if (child && child->IsFocusable()) {
            TAG_LOGI(AceLogTag::ACE_GRID, "Found child. Index: %{public}d,%{public}d", tarMainIndex, curIndex);
            return weakChild;
        }
    }
    return nullptr;
}

WeakPtr<FocusHub> GridPattern::SearchIrregularFocusableChild(int32_t tarMainIndex, int32_t tarCrossIndex)
{
    double minDistance = std::numeric_limits<double>::max();
    int32_t minMainIndex = std::numeric_limits<int32_t>::max();
    int32_t minCrossIndex = std::numeric_limits<int32_t>::max();
    int32_t maxAreaInMainShadow = -1;
    int32_t maxAreaInCrossShadow = -1;
    WeakPtr<FocusHub> targetFocusHubWeak;

    auto gridFrame = GetHost();
    CHECK_NULL_RETURN(gridFrame, nullptr);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_RETURN(gridFocus, nullptr);
    std::list<RefPtr<FocusHub>> childFocusList;
    gridFocus->FlushChildrenFocusHub(childFocusList);
    for (const auto& childFocus : childFocusList) {
        if (!childFocus->IsFocusable()) {
            continue;
        }
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            continue;
        }
        auto childPattern = childFrame->GetPattern<GridItemPattern>();
        if (!childPattern) {
            continue;
        }
        auto childItemProperty = childFrame->GetLayoutProperty<GridItemLayoutProperty>();
        if (!childItemProperty) {
            continue;
        }
        auto irregularInfo = childPattern->GetIrregularItemInfo();
        bool hasIrregularItemInfo = irregularInfo.has_value();

        auto childMainIndex = childItemProperty->GetMainIndex().value_or(-1);
        auto childCrossIndex = childItemProperty->GetCrossIndex().value_or(-1);
        auto childMainStart = hasIrregularItemInfo ? irregularInfo.value().mainStart
                                                   : childItemProperty->GetMainStart(info_.axis_);
        auto childMainEnd =
            hasIrregularItemInfo ? irregularInfo.value().mainEnd : childItemProperty->GetMainEnd(info_.axis_);
        auto chidCrossStart = hasIrregularItemInfo ? irregularInfo.value().crossStart
                                                   : childItemProperty->GetCrossStart(info_.axis_);
        auto chidCrossEnd = hasIrregularItemInfo ? irregularInfo.value().crossEnd
                                                 : childItemProperty->GetCrossEnd(info_.axis_);
        auto childCrossSpan = hasIrregularItemInfo ? irregularInfo.value().crossSpan
                                                   : childItemProperty->GetCrossSpan(info_.axis_);
        auto childMainSpan = hasIrregularItemInfo ? irregularInfo.value().mainSpan
                                                  : childItemProperty->GetMainSpan(info_.axis_);

        GridItemIndexInfo childInfo;
        childInfo.mainIndex = childMainIndex;
        childInfo.crossIndex = childCrossIndex;
        childInfo.mainStart = childMainStart;
        childInfo.mainEnd = childMainEnd;
        childInfo.crossStart = chidCrossStart;
        childInfo.crossEnd = chidCrossEnd;

        if (childMainIndex < 0 || childCrossIndex < 0) {
            continue;
        }

        if ((isLeftStep_ && ((childCrossIndex == tarCrossIndex && childCrossSpan == 1) ||
                                (chidCrossEnd >= 0 && chidCrossEnd == tarCrossIndex))) ||
            (isRightStep_ && childCrossIndex == tarCrossIndex)) {
            double nearestDistance = GetNearestDistanceFromChildToCurFocusItemInMainAxis(tarCrossIndex, childInfo);
            int32_t intersectAreaSize = CalcIntersectAreaInTargetDirectionShadow(childInfo, true);
            if (LessNotEqual(nearestDistance, minDistance) ||
                (NearEqual(nearestDistance, minDistance) && intersectAreaSize > maxAreaInCrossShadow) ||
                (NearEqual(nearestDistance, minDistance) && intersectAreaSize == maxAreaInCrossShadow &&
                    childMainIndex < minMainIndex)) {
                minDistance = nearestDistance;
                maxAreaInCrossShadow = intersectAreaSize;
                minMainIndex = childMainIndex;
                targetFocusHubWeak = AceType::WeakClaim(AceType::RawPtr(childFocus));
            }
        } else if ((isUpStep_ && childMainIndex == tarMainIndex) ||
                   (isDownStep_ && ((childMainIndex == tarMainIndex && childMainSpan == 1) ||
                                       (childMainStart >= 0 && childMainStart == tarMainIndex)))) {
            double nearestDistance = GetNearestDistanceFromChildToCurFocusItemInCrossAxis(tarMainIndex, childInfo);
            int32_t intersectAreaSize = CalcIntersectAreaInTargetDirectionShadow(childInfo, false);
            if (LessNotEqual(nearestDistance, minDistance) ||
                (NearEqual(nearestDistance, minDistance) && intersectAreaSize > maxAreaInMainShadow) ||
                (NearEqual(nearestDistance, minDistance) && intersectAreaSize == maxAreaInMainShadow &&
                    childCrossIndex < minCrossIndex)) {
                minDistance = nearestDistance;
                minCrossIndex = childCrossIndex;
                maxAreaInMainShadow = intersectAreaSize;
                targetFocusHubWeak = AceType::WeakClaim(AceType::RawPtr(childFocus));
            }
        } else if ((isLeftEndStep_ || isRightEndStep_) &&
                   ((tarMainIndex == childMainIndex && tarCrossIndex == childCrossIndex) ||
                       (childMainStart >= 0 && childMainStart <= tarMainIndex && tarMainIndex <= childMainIndex &&
                           tarCrossIndex == childCrossIndex))) {
            targetFocusHubWeak = AceType::WeakClaim(AceType::RawPtr(childFocus));
        }
    }
    ResetAllDirectionsStep();
    return targetFocusHubWeak;
}

int32_t GridPattern::CalcIntersectAreaInTargetDirectionShadow(GridItemIndexInfo itemIndexInfo, bool isFindInMainAxis)
{
    int32_t curFocusLeftTopX = -1;
    int32_t curFocusLeftTopY = -1;
    int32_t curFocusRightBottonX = -1;
    int32_t curFocusRightBottonY = -1;

    if (isFindInMainAxis) {
        curFocusLeftTopX =
            curFocusIndexInfo_.mainStart == -1 ? curFocusIndexInfo_.mainIndex : curFocusIndexInfo_.mainStart;
        curFocusLeftTopY = 0;
        curFocusRightBottonX =
            curFocusIndexInfo_.mainEnd == -1 ? curFocusIndexInfo_.mainIndex : curFocusIndexInfo_.mainEnd;
        curFocusRightBottonY = GetCrossCount();
    } else {
        curFocusLeftTopX = info_.startMainLineIndex_;
        curFocusLeftTopY =
            curFocusIndexInfo_.crossStart == -1 ? curFocusIndexInfo_.crossIndex : curFocusIndexInfo_.crossStart;
        curFocusRightBottonX = info_.endMainLineIndex_;
        curFocusRightBottonY =
            curFocusIndexInfo_.crossEnd == -1 ? curFocusIndexInfo_.crossIndex : curFocusIndexInfo_.crossEnd;
    }
    int32_t childLeftTopX = itemIndexInfo.mainStart == -1 ? itemIndexInfo.mainIndex : itemIndexInfo.mainStart;
    int32_t childLeftTopY = itemIndexInfo.crossStart == -1 ? itemIndexInfo.crossIndex : itemIndexInfo.crossStart;
    int32_t childRightBottonX = itemIndexInfo.mainEnd == -1 ? itemIndexInfo.mainIndex : itemIndexInfo.mainEnd;
    int32_t childRightBottonY = itemIndexInfo.crossEnd == -1 ? itemIndexInfo.crossIndex : itemIndexInfo.crossEnd;

    int32_t intersectAreaLeftTopX = std::max(curFocusLeftTopX, childLeftTopX);
    int32_t intersectAreaLeftTopY = std::max(curFocusLeftTopY, childLeftTopY);
    int32_t intersectAreaRightBottonX = std::min(curFocusRightBottonX, childRightBottonX);
    int32_t intersectAreaRightBottonY = std::min(curFocusRightBottonY, childRightBottonY);

    int32_t intersectWidth = intersectAreaRightBottonX - intersectAreaLeftTopX + 1;
    int32_t intersectHeight = intersectAreaRightBottonY - intersectAreaLeftTopY + 1;

    return (intersectWidth < 0 || intersectHeight < 0) ? -1 : intersectWidth * intersectHeight;
}

double GridPattern::GetNearestDistanceFromChildToCurFocusItemInMainAxis(
    int32_t targetIndex, GridItemIndexInfo itemIndexInfo)
{
    double minDistance = std::numeric_limits<double>::max();
    auto mainAxisIndex =
        curFocusIndexInfo_.mainStart == -1 ? curFocusIndexInfo_.mainIndex : curFocusIndexInfo_.mainStart;
    auto mainAxisEndIndex =
        curFocusIndexInfo_.mainEnd == -1 ? curFocusIndexInfo_.mainIndex : curFocusIndexInfo_.mainEnd;
    for (int32_t i = mainAxisIndex; i <= mainAxisEndIndex; i++) {
        double childMainIndexDistance =
            CalcCoordinatesDistance(i, curFocusIndexInfo_.crossIndex, itemIndexInfo.mainIndex, targetIndex);
        double childMainStartDistance =
            itemIndexInfo.mainStart == -1
                ? std::numeric_limits<double>::max()
                : CalcCoordinatesDistance(i, curFocusIndexInfo_.crossIndex, itemIndexInfo.mainStart, targetIndex);
        double distance = std::min(childMainIndexDistance, childMainStartDistance);
        if (LessNotEqual(distance, minDistance)) {
            minDistance = distance;
        }
    }
    return minDistance;
}

double GridPattern::GetNearestDistanceFromChildToCurFocusItemInCrossAxis(
    int32_t targetIndex, GridItemIndexInfo itemIndexInfo)
{
    double minDistance = std::numeric_limits<double>::max();
    auto crossAxisIndex =
        curFocusIndexInfo_.crossStart == -1 ? curFocusIndexInfo_.crossIndex : curFocusIndexInfo_.crossStart;
    auto crossAxisEndIndex =
        curFocusIndexInfo_.crossEnd == -1 ? curFocusIndexInfo_.crossIndex : curFocusIndexInfo_.crossEnd;
    for (int32_t i = crossAxisIndex; i <= crossAxisEndIndex; i++) {
        double childCrossIndexDistance =
            CalcCoordinatesDistance(curFocusIndexInfo_.mainIndex, i, targetIndex, itemIndexInfo.crossIndex);
        double childCrossEndDistance =
            itemIndexInfo.crossEnd == -1
                ? std::numeric_limits<double>::max()
                : CalcCoordinatesDistance(curFocusIndexInfo_.mainIndex, i, targetIndex, itemIndexInfo.crossEnd);
        double distance = std::min(childCrossIndexDistance, childCrossEndDistance);
        if (LessNotEqual(distance, minDistance)) {
            minDistance = distance;
        }
    }
    return minDistance;
}

void GridPattern::ResetAllDirectionsStep()
{
    isLeftStep_ = false;
    isRightStep_ = false;
    isUpStep_ = false;
    isDownStep_ = false;
    isLeftEndStep_ = false;
    isRightEndStep_ = false;
}

WeakPtr<FocusHub> GridPattern::GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarCrossIndex, int32_t tarIndex)
{
    auto gridFrame = GetHost();
    CHECK_NULL_RETURN(gridFrame, nullptr);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_RETURN(gridFocus, nullptr);
    std::list<RefPtr<FocusHub>> childFocusList;
    gridFocus->FlushChildrenFocusHub(childFocusList);
    for (const auto& childFocus : childFocusList) {
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            continue;
        }
        auto childPattern = childFrame->GetPattern();
        if (!childPattern) {
            continue;
        }
        auto childItemPattern = AceType::DynamicCast<GridItemPattern>(childPattern);
        if (!childItemPattern) {
            continue;
        }
        auto childItemProperty = childItemPattern->GetLayoutProperty<GridItemLayoutProperty>();
        if (!childItemProperty) {
            continue;
        }
        auto curMainIndex = childItemProperty->GetMainIndex().value_or(-1);
        auto curCrossIndex = childItemProperty->GetCrossIndex().value_or(-1);
        if (tarIndex < 0) {
            auto curMainSpan = childItemProperty->GetMainSpan(info_.axis_);
            auto curCrossSpan = childItemProperty->GetCrossSpan(info_.axis_);
            if (curMainIndex <= tarMainIndex && curMainIndex + curMainSpan > tarMainIndex &&
                curCrossIndex <= tarCrossIndex && curCrossIndex + curCrossSpan > tarCrossIndex) {
                return AceType::WeakClaim(AceType::RawPtr(childFocus));
            }
        } else {
            if (info_.gridMatrix_.find(curMainIndex) == info_.gridMatrix_.end()) {
                TAG_LOGW(AceLogTag::ACE_GRID, "Can not find target main index: %{public}d", curMainIndex);
                continue;
            }
            if (info_.gridMatrix_[curMainIndex].find(curCrossIndex) ==
                info_.gridMatrix_[curMainIndex].end()) {
                TAG_LOGW(AceLogTag::ACE_GRID, "Can not find target cross index: %{public}d", curCrossIndex);
                continue;
            }
            if (info_.gridMatrix_[curMainIndex][curCrossIndex] == tarIndex) {
                return AceType::WeakClaim(AceType::RawPtr(childFocus));
            }
        }
    }
    return nullptr;
}

std::unordered_set<int32_t> GridPattern::GetFocusableChildCrossIndexesAt(int32_t tarMainIndex)
{
    std::unordered_set<int32_t> result;
    auto gridFrame = GetHost();
    CHECK_NULL_RETURN(gridFrame, result);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_RETURN(gridFocus, result);
    std::list<RefPtr<FocusHub>> childFocusList;
    gridFocus->FlushChildrenFocusHub(childFocusList);
    for (const auto& childFocus : childFocusList) {
        if (!childFocus->IsFocusable()) {
            continue;
        }
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            continue;
        }
        auto childPattern = childFrame->GetPattern();
        if (!childPattern) {
            continue;
        }
        auto childItemPattern = AceType::DynamicCast<GridItemPattern>(childPattern);
        if (!childItemPattern) {
            continue;
        }
        auto childItemProperty = childItemPattern->GetLayoutProperty<GridItemLayoutProperty>();
        if (!childItemProperty) {
            continue;
        }
        auto irregularInfo = childItemPattern->GetIrregularItemInfo();
        bool hasIrregularItemInfo = irregularInfo.has_value();
        auto curMainIndex = childItemProperty->GetMainIndex().value_or(-1);
        auto curCrossIndex = childItemProperty->GetCrossIndex().value_or(-1);
        auto curMainStart = hasIrregularItemInfo ? irregularInfo.value().mainStart
                                                 : childItemProperty->GetMainStart(info_.axis_);
        auto curMainEnd =
            hasIrregularItemInfo ? irregularInfo.value().mainEnd : childItemProperty->GetMainEnd(info_.axis_);
        if ((curMainIndex == tarMainIndex) ||
            (curMainStart >= 0 && curMainStart <= tarMainIndex && tarMainIndex <= curMainEnd)) {
            result.emplace(curCrossIndex);
        }
    }
    std::string output;
    for (const auto& index : result) {
        output += std::to_string(index);
    }
    return result;
}

void GridPattern::ScrollToFocusNode(const WeakPtr<FocusHub>& focusNode)
{
    StopAnimate();
    auto nextFocus = focusNode.Upgrade();
    CHECK_NULL_VOID(nextFocus);
    UpdateStartIndex(GetFocusNodeIndex(nextFocus));
}

int32_t GridPattern::GetFocusNodeIndex(const RefPtr<FocusHub>& focusNode)
{
    auto tarFrame = focusNode->GetFrameNode();
    CHECK_NULL_RETURN(tarFrame, -1);
    auto tarPattern = tarFrame->GetPattern();
    CHECK_NULL_RETURN(tarPattern, -1);
    auto tarItemPattern = AceType::DynamicCast<GridItemPattern>(tarPattern);
    CHECK_NULL_RETURN(tarItemPattern, -1);
    auto tarItemProperty = tarItemPattern->GetLayoutProperty<GridItemLayoutProperty>();
    CHECK_NULL_RETURN(tarItemProperty, -1);
    auto tarMainIndex = tarItemProperty->GetMainIndex().value_or(-1);
    auto tarCrossIndex = tarItemProperty->GetCrossIndex().value_or(-1);
    if (info_.gridMatrix_.find(tarMainIndex) == info_.gridMatrix_.end()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Can not find target main index: %{public}d", tarMainIndex);
        if (tarMainIndex == 0) {
            return 0;
        }
        return info_.childrenCount_ - 1;
    }
    if (info_.gridMatrix_[tarMainIndex].find(tarCrossIndex) ==
        info_.gridMatrix_[tarMainIndex].end()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Can not find target cross index: %{public}d", tarCrossIndex);
        if (tarMainIndex == 0) {
            return 0;
        }
        return info_.childrenCount_ - 1;
    }
    return info_.gridMatrix_[tarMainIndex][tarCrossIndex];
}

void GridPattern::ScrollToFocusNodeIndex(int32_t index)
{
    StopAnimate();
    UpdateStartIndex(index);
    auto pipeline = GetContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
    auto tarFocusNodeWeak = GetChildFocusNodeByIndex(-1, -1, index);
    auto tarFocusNode = tarFocusNodeWeak.Upgrade();
    if (tarFocusNode) {
        tarFocusNode->RequestFocusImmediately();
    }
}

bool GridPattern::ScrollToNode(const RefPtr<FrameNode>& focusFrameNode)
{
    CHECK_NULL_RETURN(focusFrameNode, false);
    auto focusHub = focusFrameNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    auto scrollToIndex = GetFocusNodeIndex(focusHub);
    if (scrollToIndex < 0) {
        return false;
    }
    StopAnimate();
    auto ret = UpdateStartIndex(scrollToIndex);
    auto pipeline = GetContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
    return ret;
}

ScrollOffsetAbility GridPattern::GetScrollOffsetAbility()
{
    return { [wp = WeakClaim(this)](float moveOffset) -> bool {
                auto pattern = wp.Upgrade();
                CHECK_NULL_RETURN(pattern, false);
                pattern->ScrollBy(-moveOffset);
                return true;
            },
        GetAxis() };
}

std::function<bool(int32_t)> GridPattern::GetScrollIndexAbility()
{
    return [wp = WeakClaim(this)](int32_t index) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (index == FocusHub::SCROLL_TO_HEAD) {
            pattern->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
        } else if (index == FocusHub::SCROLL_TO_TAIL) {
            pattern->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
        } else {
            pattern->UpdateStartIndex(index);
        }
        return true;
    };
}

void GridPattern::ScrollBy(float offset)
{
    StopAnimate();
    UpdateCurrentOffset(-offset, SCROLL_FROM_JUMP);
    // AccessibilityEventType::SCROLL_END
}

void GridPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    ScrollablePattern::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("multiSelectable", multiSelectable_ ? "true" : "false", filter);
    json->PutExtAttr("supportAnimation", supportAnimation_ ? "true" : "false", filter);
}

void GridPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    focusHub->SetOnFocusInternal([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusEvent();
        }
    });

    focusHub->SetOnBlurInternal([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleBlurEvent();
        }
    });
}

void GridPattern::HandleFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    CHECK_NULL_VOID(focusHub->IsCurrentFocus());

    auto child = focusHub->GetLastWeakFocusNode();
    auto childFocusHub = child.Upgrade();
    CHECK_NULL_VOID(childFocusHub);
    int32_t index = GetIndexByFocusHub(childFocusHub);
    if (index >= 0) {
        focusIndex_ = index;
        TAG_LOGI(AceLogTag::ACE_GRID, "Grid on focus with index: %{public}d", index);
    }
}

void GridPattern::HandleBlurEvent()
{
    TAG_LOGI(AceLogTag::ACE_GRID, "Grid lost focus");
}

bool GridPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((event.code == KeyCode::KEY_PAGE_DOWN) || (event.code == KeyCode::KEY_PAGE_UP)) {
        ScrollPage(event.code == KeyCode::KEY_PAGE_UP);
    }

    if (FocusHub::IsFocusStepKey(event.code)) {
        if (ScrollToLastFocusIndex(event.code)) {
            keyEvent_ = event;
            return true;
        }
    }
    return false;
}

bool GridPattern::IsInViewport(int32_t index) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto gridLayoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, true);
    int32_t cacheCount = gridLayoutProperty->GetCachedCountValue(info_.defCachedCount_) * info_.crossCount_;
    bool showCachedItems = gridLayoutProperty->GetShowCachedItemsValue(false);
    if (!showCachedItems) {
        return index >= info_.startIndex_ && index <= info_.endIndex_;
    }
    return index >= info_.startIndex_ - cacheCount && index <= info_.endIndex_ + cacheCount;
}

bool GridPattern::ScrollToLastFocusIndex(KeyCode keyCode)
{
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(pipeline->GetIsFocusActive(), false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    CHECK_NULL_RETURN(focusHub->IsCurrentFocus(), false);
    CHECK_NULL_RETURN(focusIndex_.has_value(), false);

    if (!IsInViewport(focusIndex_.value())) {
        StopAnimate();
        needTriggerFocus_ = true;
        // If focused item is above viewport and the current keyCode type is UP, scroll forward one more line
        if (focusIndex_.value() < info_.startIndex_ && keyCode == KeyCode::KEY_DPAD_UP &&
            focusIndex_.value() - GetCrossCount() >= 0) {
            UpdateStartIndex(focusIndex_.value() - GetCrossCount());
        // If focused item is below viewport and the current keyCode type is DOWN, scroll backward one more line
        } else if (focusIndex_.value() > info_.endIndex_ && keyCode == KeyCode::KEY_DPAD_DOWN &&
                   focusIndex_.value() + GetCrossCount() < GetChildrenCount()) {
            UpdateStartIndex(focusIndex_.value() + GetCrossCount());
        } else {
            UpdateStartIndex(focusIndex_.value());
        }
        return true;
    }
    return false;
}

void GridPattern::ScrollPage(bool reverse, bool smooth, AccessibilityScrollType scrollType)
{
    float distance = reverse ? GetMainContentSize() : -GetMainContentSize();
    if (scrollType == AccessibilityScrollType::SCROLL_HALF) {
        distance = distance / 2.f;
    }
    if (smooth) {
        float position = -info_.currentHeight_ + distance;
        ScrollablePattern::AnimateTo(-position, -1, nullptr, true, false, false);
        return;
    } else {
        if (!isConfigScrollable_) {
            return;
        }
        StopAnimate();
        UpdateCurrentOffset(distance, SCROLL_FROM_JUMP);
    }
    // AccessibilityEventType::SCROLL_END
}

bool GridPattern::UpdateStartIndex(int32_t index)
{
    if (!isConfigScrollable_) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    info_.jumpIndex_ = index;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    // AccessibilityEventType::SCROLL_END
    SetScrollSource(SCROLL_FROM_JUMP);
    return true;
}

bool GridPattern::UpdateStartIndex(int32_t index, ScrollAlign align)
{
    info_.scrollAlign_ = align;
    return UpdateStartIndex(index);
}

void GridPattern::OnAnimateStop()
{
    if (!GetIsDragging() || GetScrollAbort()) {
        scrollStop_ = true;
        MarkDirtyNodeSelf();
    }
}

void GridPattern::AnimateTo(
    float position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll, bool useTotalOffset)
{
    if (!isConfigScrollable_) {
        return;
    }
    ScrollablePattern::AnimateTo(position, duration, curve, smooth, canOverScroll);
}

void GridPattern::ScrollTo(float position)
{
    if (!isConfigScrollable_) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_GRID, "ScrollTo:%{public}f", position);
    StopAnimate();
    UpdateCurrentOffset(GetTotalOffset() - position, SCROLL_FROM_JUMP);
    // AccessibilityEventType::SCROLL_END
}

float GridPattern::EstimateHeight() const
{
    if (!isConfigScrollable_) {
        return 0.0f;
    }
    // During the scrolling animation, the exact current position is used. Other times use the estimated location
    if (isSmoothScrolling_) {
        const auto* infoPtr = UseIrregularLayout() ? &info_ : infoCopy_.get();
        CHECK_NULL_RETURN(infoPtr, 0.0f);
        int32_t lineIndex = 0;
        infoPtr->GetLineIndexByIndex(info_.startIndex_, lineIndex);
        return infoPtr->GetTotalHeightFromZeroIndex(lineIndex, GetMainGap()) - info_.currentOffset_;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    const auto& info = info_;
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    auto mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, info.axis_);
    if (UseIrregularLayout()) {
        return info.GetIrregularOffset(mainGap);
    }
    if (!layoutProperty->GetLayoutOptions().has_value()) {
        return info.GetContentOffset(mainGap);
    }

    return info.GetContentOffset(layoutProperty->GetLayoutOptions().value(), mainGap);
}

float GridPattern::GetAverageHeight() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    const auto& info = info_;
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();

    float heightSum = 0;
    int32_t itemCount = 0;
    auto mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, info.axis_);
    for (const auto& item : info.lineHeightMap_) {
        auto line = info.gridMatrix_.find(item.first);
        if (line == info.gridMatrix_.end()) {
            continue;
        }
        if (line->second.empty()) {
            continue;
        }
        auto lineStart = line->second.begin()->second;
        auto lineEnd = line->second.rbegin()->second;
        itemCount += (lineEnd - lineStart + 1);
        heightSum += item.second + mainGap;
    }
    if (itemCount == 0) {
        return 0;
    }
    return heightSum / itemCount;
}

float GridPattern::GetTotalHeight() const
{
    if (scrollbarInfo_.first.has_value() && scrollbarInfo_.second.has_value()) {
        return scrollbarInfo_.second.value();
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    auto mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, info_.axis_);
    if (UseIrregularLayout()) {
        return info_.GetIrregularHeight(mainGap);
    }
    return info_.GetContentHeight(mainGap);
}

void GridPattern::UpdateScrollBarOffset()
{
    CheckScrollBarOff();
    if ((!GetScrollBar() && !GetScrollBarProxy()) || !isConfigScrollable_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    const auto& info = info_;
    float offset = 0;
    float estimatedHeight = 0.f;
    if (scrollbarInfo_.first.has_value() && scrollbarInfo_.second.has_value()) {
        offset = scrollbarInfo_.first.value();
        estimatedHeight = scrollbarInfo_.second.value();
    } else {
        auto viewScopeSize = geometryNode->GetPaddingSize();
        auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
        auto mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, info.axis_);
        if (UseIrregularLayout()) {
            offset = info.GetIrregularOffset(mainGap);
            estimatedHeight = info.GetIrregularHeight(mainGap);
        } else if (!layoutProperty->GetLayoutOptions().has_value()) {
            offset = info.GetContentOffset(mainGap);
            estimatedHeight = info.GetContentHeight(mainGap);
        } else {
            offset = info.GetContentOffset(layoutProperty->GetLayoutOptions().value(), mainGap);
            estimatedHeight =
                info.GetContentHeight(layoutProperty->GetLayoutOptions().value(), info.childrenCount_, mainGap);
        }
    }
    if (info.startMainLineIndex_ != 0 && info.startIndex_ == 0) {
        for (int32_t lineIndex = info.startMainLineIndex_ - 1; lineIndex >= 0; lineIndex--) {
            offset += info.lineHeightMap_.find(lineIndex)->second;
        }
    }
    auto viewSize = geometryNode->GetFrameSize();
    auto overScroll = 0.0f;
    if (info_.reachStart_ && Positive(info_.currentOffset_)) {
        overScroll = info_.currentOffset_;
    } else {
        overScroll = info_.lastMainSize_ - estimatedHeight + offset;
        overScroll = Positive(overScroll) ? overScroll : 0.0f;
    }
    if (info_.offsetEnd_ && NearZero(overScroll)) {
        offset = estimatedHeight - info_.lastMainSize_;
    }
    HandleScrollBarOutBoundary(overScroll);
    UpdateScrollBarRegion(offset, estimatedHeight, Size(viewSize.Width(), viewSize.Height()), Offset(0.0f, 0.0f));
}

DisplayMode GridPattern::GetDefaultScrollBarDisplayMode() const
{
    auto defaultDisplayMode = DisplayMode::OFF;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        defaultDisplayMode = DisplayMode::AUTO;
    }
    return defaultDisplayMode;
}

int32_t GridPattern::GetOriginalIndex() const
{
    return info_.GetOriginalIndex();
}

int32_t GridPattern::GetCrossCount() const
{
    return info_.crossCount_;
}

int32_t GridPattern::GetChildrenCount() const
{
    return info_.childrenCount_;
}

void GridPattern::ClearDragState()
{
    info_.ClearDragState();
    MarkDirtyNodeSelf();
}

void GridPattern::UpdateRectOfDraggedInItem(int32_t insertIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> children;
    host->GenerateOneDepthAllFrame(children);
    for (const auto& item : children) {
        auto itemPattern = item->GetPattern<GridItemPattern>();
        CHECK_NULL_VOID(itemPattern);
        auto itemProperty = itemPattern->GetLayoutProperty<GridItemLayoutProperty>();
        CHECK_NULL_VOID(itemProperty);
        auto mainIndex = itemProperty->GetMainIndex().value_or(-1);
        auto crossIndex = itemProperty->GetCrossIndex().value_or(-1);
        if (mainIndex * info_.crossCount_ + crossIndex == insertIndex) {
            auto size = item->GetRenderContext()->GetPaintRectWithTransform();
            size.SetOffset(item->GetTransformRelativeOffset());
            info_.currentRect_ = size;
            break;
        }
    }
}

void GridPattern::MoveItems(int32_t itemIndex, int32_t insertIndex)
{
    if (insertIndex < 0 ||
        insertIndex >= ((itemIndex == -1) ? (info_.childrenCount_ + 1) : info_.childrenCount_)) {
        return;
    }

    if (itemIndex == -1) {
        UpdateRectOfDraggedInItem(insertIndex);
    }

    info_.SwapItems(itemIndex, insertIndex);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto pipeline = GetContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
}

bool GridPattern::IsOutOfBoundary(bool /*useCurrentDelta*/)
{
    const bool scrollable = GetAlwaysEnabled() || (info_.startIndex_ > 0) ||
                            (info_.endIndex_ < info_.childrenCount_ - 1) ||
                            GreatNotEqual(info_.totalHeightOfItemsInView_, info_.lastMainSize_);
    return scrollable &&
           (info_.IsOutOfStart() || info_.IsOutOfEnd(GetMainGap(), UseIrregularLayout()));
}

float GridPattern::GetEndOffset()
{
    auto& info = info_;
    float contentHeight = info.lastMainSize_ - info.contentEndPadding_;
    const float mainGap = GetMainGap();
    const bool irregular = UseIrregularLayout();
    float heightInView = info.GetTotalHeightOfItemsInView(mainGap, irregular);

    if (GetAlwaysEnabled() && info.HeightSumSmaller(contentHeight, mainGap)) {
        // overScroll with contentHeight < viewport
        if (irregular) {
            return info.GetHeightInRange(0, info.startMainLineIndex_, mainGap);
        }
        float totalHeight = info.GetTotalLineHeight(mainGap);
        return totalHeight - heightInView;
    }

    if (!irregular) {
        return contentHeight - heightInView;
    }
    float disToBot = info_.GetDistanceToBottom(contentHeight, heightInView, mainGap);
    return info_.currentOffset_ - disToBot;
}

void GridPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto grid = weak.Upgrade();
        CHECK_NULL_RETURN(grid, 0.0);
        if (!grid->info_.synced_) {
            grid->SyncLayoutBeforeSpring();
        }
        return grid->info_.currentOffset_;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto grid = weak.Upgrade();
        CHECK_NULL_RETURN(grid, 0.0);
        return grid->GetEndOffset();
    });
    scrollEffect->SetTrailingCallback([]() -> double { return 0.0; });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto grid = weak.Upgrade();
        CHECK_NULL_RETURN(grid, 0.0);
        return grid->GetEndOffset();
    });
    scrollEffect->SetInitTrailingCallback([]() -> double { return 0.0; });
}

void GridPattern::SyncLayoutBeforeSpring()
{
    auto& info = info_;
    if (info.synced_) {
        return;
    }
    if (!UseIrregularLayout()) {
        const float delta = info.currentOffset_ - info.prevOffset_;
        if (!info.lineHeightMap_.empty() && LessOrEqual(delta, -info_.lastMainSize_)) {
            // old layout can't handle large overScroll offset. Avoid by skipping this layout.
            // Spring animation plays immediately afterwards, so losing this frame's offset is fine
            info.currentOffset_ = info.prevOffset_;
            info.synced_ = true;
            return;
        }
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    forceOverScroll_ = true;
    host->SetActive();
    auto context = host->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(host);
    }
    forceOverScroll_ = false;
}

void GridPattern::GetEndOverScrollIrregular(OverScrollOffset& offset, float delta) const
{
    const auto& info = info_;
    float contentHeight = std::max(GetMainContentSize(), info.totalHeightOfItemsInView_);
    float disToBot = info.GetDistanceToBottom(
        info.lastMainSize_ - info.contentEndPadding_, contentHeight, GetMainGap());
    if (!info.offsetEnd_) {
        offset.end = std::min(0.0f, disToBot + static_cast<float>(delta));
    } else if (Negative(delta)) {
        offset.end = delta;
    } else {
        offset.end = std::min(static_cast<float>(delta), -disToBot);
    }
}

OverScrollOffset GridPattern::GetOverScrollOffset(double delta) const
{
    OverScrollOffset offset = { 0, 0 };
    if (info_.startIndex_ == 0 && info_.startMainLineIndex_ == 0) {
        auto startPos = info_.currentOffset_;
        auto newStartPos = startPos + delta;
        if (startPos > 0 && newStartPos > 0) {
            offset.start = delta;
        }
        if (startPos > 0 && newStartPos <= 0) {
            offset.start = -startPos;
        }
        if (startPos <= 0 && newStartPos > 0) {
            offset.start = newStartPos;
        }
    }
    if (UseIrregularLayout()) {
        GetEndOverScrollIrregular(offset, static_cast<float>(delta));
        return offset;
    }
    if (info_.endIndex_ == info_.childrenCount_ - 1) {
        float endPos = info_.currentOffset_ + info_.totalHeightOfItemsInView_;
        float mainSize = info_.lastMainSize_ - info_.contentEndPadding_;
        if (GreatNotEqual(
                GetMainContentSize(), info_.currentOffset_ + info_.totalHeightOfItemsInView_)) {
            endPos = info_.currentOffset_ + GetMainContentSize();
        }
        float newEndPos = endPos + delta;
        if (endPos < mainSize && newEndPos < mainSize) {
            offset.end = delta;
        }
        if (endPos < mainSize && newEndPos >= mainSize) {
            offset.end = mainSize - endPos;
        }
        if (endPos >= mainSize && newEndPos < mainSize) {
            offset.end = newEndPos - mainSize;
        }
    }
    return offset;
}

void GridPattern::DumpAdvanceInfo()
{
    auto property = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(property);
    ScrollablePattern::DumpAdvanceInfo();
    if (!property->HasLayoutOptions()) {
        DumpLog::GetInstance().AddDesc("GridLayoutOptions:null");
    } else {
        DumpLog::GetInstance().AddDesc("GridLayoutOptions:true");
        DumpLog::GetInstance().AddDesc(GetIrregularIndexesString());
    }
    supportAnimation_ ? DumpLog::GetInstance().AddDesc("supportAnimation:true")
                      : DumpLog::GetInstance().AddDesc("supportAnimation:false");
    isConfigScrollable_ ? DumpLog::GetInstance().AddDesc("isConfigScrollable:true")
                        : DumpLog::GetInstance().AddDesc("isConfigScrollable:false");
    info_.lastCrossCount_.has_value()
        ? DumpLog::GetInstance().AddDesc("lastCrossCount:" + std::to_string(info_.lastCrossCount_.value()))
        : DumpLog::GetInstance().AddDesc("lastCrossCount:null");
    info_.reachEnd_ ? DumpLog::GetInstance().AddDesc("reachEnd:true")
                              : DumpLog::GetInstance().AddDesc("reachEnd:false");
    info_.reachStart_ ? DumpLog::GetInstance().AddDesc("reachStart:true")
                                : DumpLog::GetInstance().AddDesc("reachStart:false");
    info_.offsetEnd_ ? DumpLog::GetInstance().AddDesc("offsetEnd:true")
                               : DumpLog::GetInstance().AddDesc("offsetEnd:false");
    info_.hasBigItem_ ? DumpLog::GetInstance().AddDesc("hasBigItem:true")
                                : DumpLog::GetInstance().AddDesc("hasBigItem:false");
    info_.synced_ ? DumpLog::GetInstance().AddDesc("synced:true")
                            : DumpLog::GetInstance().AddDesc("synced:false");
    DumpLog::GetInstance().AddDesc("scrollStop:" + std::to_string(scrollStop_));
    DumpLog::GetInstance().AddDesc("prevHeight:" + std::to_string(info_.prevHeight_));
    DumpLog::GetInstance().AddDesc("currentHeight:" + std::to_string(info_.currentHeight_));
    DumpLog::GetInstance().AddDesc("endHeight:" + std::to_string(endHeight_));
    DumpLog::GetInstance().AddDesc("currentOffset:" + std::to_string(info_.currentOffset_));
    DumpLog::GetInstance().AddDesc("prevOffset:" + std::to_string(info_.prevOffset_));
    DumpLog::GetInstance().AddDesc("lastMainSize:" + std::to_string(info_.lastMainSize_));
    DumpLog::GetInstance().AddDesc(
        "totalHeightOfItemsInView:" + std::to_string(info_.totalHeightOfItemsInView_));
    DumpLog::GetInstance().AddDesc("startIndex:" + std::to_string(info_.startIndex_));
    DumpLog::GetInstance().AddDesc("endIndex:" + std::to_string(info_.endIndex_));
    DumpLog::GetInstance().AddDesc("jumpIndex:" + std::to_string(info_.jumpIndex_));
    DumpLog::GetInstance().AddDesc("crossCount:" + std::to_string(info_.crossCount_));
    DumpLog::GetInstance().AddDesc("childrenCount:" + std::to_string(info_.childrenCount_));
    DumpLog::GetInstance().AddDesc("RowsTemplate:", property->GetRowsTemplate()->c_str());
    DumpLog::GetInstance().AddDesc("ColumnsTemplate:", property->GetColumnsTemplate()->c_str());
    property->GetRowsGap().has_value()
        ? DumpLog::GetInstance().AddDesc("RowsGap:" + std::to_string(property->GetRowsGap().value().Value()))
        : DumpLog::GetInstance().AddDesc("RowsGap:null");
    property->GetColumnsGap().has_value()
        ? DumpLog::GetInstance().AddDesc("ColumnsGap:" + std::to_string(property->GetColumnsGap().value().Value()))
        : DumpLog::GetInstance().AddDesc("ColumnsGap:null");
    property->GetCachedCount().has_value()
        ? DumpLog::GetInstance().AddDesc("CachedCount:" + std::to_string(property->GetCachedCount().value()))
        : DumpLog::GetInstance().AddDesc("CachedCount:null");
    property->GetMaxCount().has_value()
        ? DumpLog::GetInstance().AddDesc("MaxCount:" + std::to_string(property->GetMaxCount().value()))
        : DumpLog::GetInstance().AddDesc("MaxCount:null");
    property->GetMinCount().has_value()
        ? DumpLog::GetInstance().AddDesc("MinCount:" + std::to_string(property->GetMinCount().value()))
        : DumpLog::GetInstance().AddDesc("MinCount:null");
    property->GetCellLength().has_value()
        ? DumpLog::GetInstance().AddDesc("CellLength:" + std::to_string(property->GetCellLength().value()))
        : DumpLog::GetInstance().AddDesc("CellLength:null");
    property->GetEditable().has_value()
        ? DumpLog::GetInstance().AddDesc("Editable:" + std::to_string(property->GetEditable().value()))
        : DumpLog::GetInstance().AddDesc("Editable:null");
    property->GetScrollEnabled().has_value()
        ? DumpLog::GetInstance().AddDesc("ScrollEnabled:" + std::to_string(property->GetScrollEnabled().value()))
        : DumpLog::GetInstance().AddDesc("ScrollEnabled:null");
    switch (property->GetAlignItems().value_or(GridItemAlignment::DEFAULT)) {
        case GridItemAlignment::STRETCH: {
            DumpLog::GetInstance().AddDesc("AlignItems:GridItemAlignment.STRETCH");
            break;
        }
        default: {
            DumpLog::GetInstance().AddDesc("AlignItems:GridItemAlignment.DEFAULT");
            break;
        }
    }
    switch (info_.scrollAlign_) {
        case ScrollAlign::NONE: {
            DumpLog::GetInstance().AddDesc("ScrollAlign:NONE");
            break;
        }
        case ScrollAlign::CENTER: {
            DumpLog::GetInstance().AddDesc("ScrollAlign:CENTER");
            break;
        }
        case ScrollAlign::END: {
            DumpLog::GetInstance().AddDesc("ScrollAlign:END");
            break;
        }
        case ScrollAlign::START: {
            DumpLog::GetInstance().AddDesc("ScrollAlign:START");
            break;
        }
        case ScrollAlign::AUTO: {
            DumpLog::GetInstance().AddDesc("ScrollAlign:AUTO");
            break;
        }
        default: {
            break;
        }
    }
    if (!info_.gridMatrix_.empty()) {
        DumpLog::GetInstance().AddDesc("-----------start print gridMatrix------------");
        std::string res = std::string("");
        for (auto item : info_.gridMatrix_) {
            res.append(std::to_string(item.first));
            res.append(": ");
            for (auto index : item.second) {
                res.append("[")
                    .append(std::to_string(index.first))
                    .append(",")
                    .append(std::to_string(index.second))
                    .append("] ");
            }
            DumpLog::GetInstance().AddDesc(res);
            res.clear();
        }
        DumpLog::GetInstance().AddDesc("-----------end print gridMatrix------------");
    }
    if (!info_.lineHeightMap_.empty()) {
        DumpLog::GetInstance().AddDesc("-----------start print lineHeightMap------------");
        for (auto item : info_.lineHeightMap_) {
            DumpLog::GetInstance().AddDesc(std::to_string(item.first).append(" :").append(std::to_string(item.second)));
        }
        DumpLog::GetInstance().AddDesc("-----------end print lineHeightMap------------");
    }
    if (!info_.irregularItemsPosition_.empty()) {
        DumpLog::GetInstance().AddDesc("-----------start print irregularItemsPosition_------------");
        for (auto item : info_.irregularItemsPosition_) {
            DumpLog::GetInstance().AddDesc(std::to_string(item.first).append(" :").append(std::to_string(item.second)));
        }
        DumpLog::GetInstance().AddDesc("-----------end print irregularItemsPosition_------------");
    }
}

std::string GridPattern::GetIrregularIndexesString() const
{
    auto property = GetLayoutProperty<GridLayoutProperty>();
    if (!property || !property->HasLayoutOptions()) {
        return std::string("");
    }
    const auto& options = *property->GetLayoutOptions();
    if (options.irregularIndexes.empty()) {
        return std::string("");
    }
    std::string irregularIndexes = std::string("IrregularIndexes: [");
    int count = 0;
    for (const auto& index : options.irregularIndexes) {
        if (count > 0) {
            irregularIndexes.append(", ");
        }
        irregularIndexes.append(std::to_string(index));
        count++;
        if (count == MAX_NUM_SIZE) {
            irregularIndexes.append("...");
            break;
        }
    }
    irregularIndexes.append("]");
    return irregularIndexes;
}

std::string GridPattern::ProvideRestoreInfo()
{
    return std::to_string(info_.startIndex_);
}

void GridPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    info_.jumpIndex_ = StringUtils::StringToInt(restoreInfo);
    info_.scrollAlign_ = ScrollAlign::START;
}

Rect GridPattern::GetItemRect(int32_t index) const
{
    if (index < 0 || index < info_.startIndex_ || index > info_.endIndex_) {
        return Rect();
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, Rect());
    auto item = host->GetChildByIndex(index);
    CHECK_NULL_RETURN(item, Rect());
    auto itemGeometry = item->GetGeometryNode();
    CHECK_NULL_RETURN(itemGeometry, Rect());
    return Rect(itemGeometry->GetFrameRect().GetX(), itemGeometry->GetFrameRect().GetY(),
        itemGeometry->GetFrameRect().Width(), itemGeometry->GetFrameRect().Height());
}

int32_t GridPattern::GetItemIndex(double x, double y) const
{
    for (int32_t index = info_.startIndex_; index <= info_.endIndex_; ++index) {
        Rect rect = GetItemRect(index);
        if (rect.IsInRegion({x, y})) {
            return index;
        }
    }
    return -1;
}

void GridPattern::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset)
{
    SetScrollSource(SCROLL_FROM_JUMP);
    StopAnimate();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t totalChildCount = host->TotalChildCount();
    if (((index >= 0) && (index < totalChildCount)) || (index == LAST_ITEM)) {
        if (extraOffset.has_value()) {
            info_.extraOffset_ = -extraOffset.value();
        }
        if (smooth) {
            SetExtraOffset(extraOffset);
            targetIndex_ = index;
            scrollAlign_ = align;
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        } else {
            UpdateStartIndex(index, align);
        }
    }
    FireAndCleanScrollingListener();
}

void GridPattern::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    if (UseIrregularLayout() && scrollEdgeType == ScrollEdgeType::SCROLL_BOTTOM) {
        ScrollToIndex(LAST_ITEM, smooth);
        // for irregular layout, last item might not be at bottom
        info_.jumpIndex_ = JUMP_TO_BOTTOM_EDGE;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }
    ScrollablePattern::ScrollToEdge(scrollEdgeType, smooth);
}

// Turn on the scrolling animation
void GridPattern::AnimateToTarget(ScrollAlign align, const RefPtr<LayoutAlgorithmWrapper>& algo)
{
    if (targetIndex_.has_value()) {
        AnimateToTargetImpl(align, algo);
        targetIndex_.reset();
    }
}

// scroll to the item where the index is located
bool GridPattern::AnimateToTargetImpl(ScrollAlign align, const RefPtr<LayoutAlgorithmWrapper>& algo)
{
    const float mainGap = GetMainGap();
    float targetPos = 0.0f;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto&& extraOffset = GetExtraOffset();
    bool success = true;
    if (UseIrregularLayout()) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto size = GridLayoutUtils::GetItemSize(&info_, RawPtr(host), *targetIndex_);
        targetPos = info_.GetAnimatePosIrregular(*targetIndex_, size.rows, align, mainGap);
        if (Negative(targetPos)) {
            success = false;
        }
    } else {
        auto gridScrollLayoutAlgorithm = DynamicCast<GridScrollLayoutAlgorithm>(algo->GetLayoutAlgorithm());
        infoCopy_ = gridScrollLayoutAlgorithm->MoveInfoCopy();
        // Based on the index, align gets the position to scroll to
        success = infoCopy_ && infoCopy_->GetGridItemAnimatePos(
            info_, *targetIndex_, align, mainGap, targetPos);
    }
    if (!success) {
        if (NearZero(extraOffset.value_or(0.0f))) {
            return false;
        }
        targetPos = GetTotalOffset();
    }

    isSmoothScrolling_ = true;
    if (extraOffset.has_value()) {
        ACE_SCOPED_TRACE(
            "AnimateToTargetImpl, success:%u, targetPos:%f, extraOffset:%f", success, targetPos, *extraOffset);
        targetPos += *extraOffset;
        ResetExtraOffset();
    } else {
        ACE_SCOPED_TRACE("AnimateToTargetImpl, targetPos:%f", targetPos);
    }
    AnimateTo(targetPos, -1, nullptr, true);
    return true;
}

std::vector<RefPtr<FrameNode>> GridPattern::GetVisibleSelectedItems()
{
    std::vector<RefPtr<FrameNode>> children;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, children);
    for (int32_t index = info_.startIndex_; index <= info_.endIndex_; ++index) {
        auto item = host->GetChildByIndex(index);
        if (!AceType::InstanceOf<FrameNode>(item)) {
            continue;
        }
        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        auto itemPattern = itemFrameNode->GetPattern<GridItemPattern>();
        if (!itemPattern) {
            continue;
        }
        if (!itemPattern->IsSelected()) {
            continue;
        }
        children.emplace_back(itemFrameNode);
    }
    return children;
}

void GridPattern::StopAnimate()
{
    ScrollablePattern::StopAnimate();
    isSmoothScrolling_ = false;
}

bool GridPattern::IsPredictOutOfRange(int32_t index) const
{
    CHECK_NULL_RETURN(info_.reachEnd_, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto gridLayoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, true);
    auto cacheCount = gridLayoutProperty->GetCachedCountValue(info_.defCachedCount_) * info_.crossCount_;
    return index < info_.startIndex_ - cacheCount || index > info_.endIndex_ + cacheCount;
}

inline bool GridPattern::UseIrregularLayout() const
{
    return irregular_ || (SystemProperties::GetGridIrregularLayoutEnabled() &&
                             GetLayoutProperty<GridLayoutProperty>()->HasLayoutOptions());
}

bool GridPattern::IsReverse() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto gridLayoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, false);
    return gridLayoutProperty->IsReverse();
}

void GridPattern::BuildScrollAlignInfo(std::unique_ptr<JsonValue>& json)
{
    switch (info_.scrollAlign_) {
        case ScrollAlign::NONE: {
            json->Put("ScrollAlign", "NONE");
            break;
        }
        case ScrollAlign::CENTER: {
            json->Put("ScrollAlign", "CENTER");
            break;
        }
        case ScrollAlign::END: {
            json->Put("ScrollAlign", "END");
            break;
        }
        case ScrollAlign::START: {
            json->Put("ScrollAlign", "START");
            break;
        }
        case ScrollAlign::AUTO: {
            json->Put("ScrollAlign", "AUTO");
            break;
        }
        default: {
            break;
        }
    }
}

void GridPattern::BuildGridLayoutInfo(std::unique_ptr<JsonValue>& json)
{
    if (!info_.gridMatrix_.empty()) {
        std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
        std::string res = std::string("");
        for (auto item : info_.gridMatrix_) {
            for (auto index : item.second) {
                res.append("[")
                    .append(std::to_string(index.first))
                    .append(",")
                    .append(std::to_string(index.second))
                    .append("] ");
            }
            children->Put(std::to_string(item.first).c_str(), res.c_str());
            res.clear();
        }
        children->Put("gridMatrix", children);
    }
    if (!info_.lineHeightMap_.empty()) {
        std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
        for (auto item : info_.lineHeightMap_) {
            children->Put(std::to_string(item.first).c_str(), std::to_string(item.second).c_str());
        }
        children->Put("lineHeightMap", children);
    }
    if (!info_.irregularItemsPosition_.empty()) {
        std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
        for (auto item : info_.irregularItemsPosition_) {
            children->Put(std::to_string(item.first).c_str(), std::to_string(item.second).c_str());
        }
        children->Put("irregularItemsPosition_", children);
    }
}

void GridPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    auto property = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(property);
    ScrollablePattern::DumpAdvanceInfo(json);
    json->Put("GridLayoutOptions", property->HasLayoutOptions() ? GetIrregularIndexesString().c_str() : "null");
    json->Put("supportAnimation", supportAnimation_);
    json->Put("isConfigScrollable", isConfigScrollable_);
    json->Put("lastCrossCount", info_.lastCrossCount_.has_value()
                                    ? std::to_string(info_.lastCrossCount_.value()).c_str()
                                    : "null");
    json->Put("reachEnd", info_.reachEnd_);
    json->Put("reachStart", info_.reachStart_);
    json->Put("offsetEnd", info_.offsetEnd_);
    json->Put("hasBigItem", info_.hasBigItem_);
    json->Put("synced", info_.synced_);
    json->Put("scrollStop", std::to_string(scrollStop_).c_str());
    json->Put("prevHeight", info_.prevHeight_);
    json->Put("currentHeight", info_.currentHeight_);
    json->Put("endHeight", endHeight_);
    json->Put("currentOffset", std::to_string(info_.currentOffset_).c_str());
    json->Put("prevOffset", std::to_string(info_.prevOffset_).c_str());
    json->Put("lastMainSize", std::to_string(info_.lastMainSize_).c_str());
    json->Put("totalHeightOfItemsInView", std::to_string(info_.totalHeightOfItemsInView_).c_str());
    json->Put("startIndex", info_.startIndex_);
    json->Put("endIndex", info_.endIndex_);
    json->Put("jumpIndex", info_.jumpIndex_);
    json->Put("crossCount", info_.crossCount_);
    json->Put("childrenCount", info_.childrenCount_);
    json->Put("RowsTemplate", property->GetRowsTemplate()->c_str());
    json->Put("ColumnsTemplate", property->GetColumnsTemplate()->c_str());
    json->Put("CachedCount",
        property->GetCachedCount().has_value() ? std::to_string(property->GetCachedCount().value()).c_str() : "null");
    json->Put("MaxCount",
        property->GetMaxCount().has_value() ? std::to_string(property->GetMaxCount().value()).c_str() : "null");
    json->Put("MinCount",
        property->GetMinCount().has_value() ? std::to_string(property->GetMinCount().value()).c_str() : "null");
    json->Put("CellLength",
        property->GetCellLength().has_value() ? std::to_string(property->GetCellLength().value()).c_str() : "null");
    json->Put("Editable",
        property->GetEditable().has_value() ? std::to_string(property->GetEditable().value()).c_str() : "null");
    json->Put("ScrollEnabled", property->GetScrollEnabled().has_value()
                                   ? std::to_string(property->GetScrollEnabled().value()).c_str()
                                   : "null");

    json->Put("AlignItems", property->GetAlignItems() ? "GridItemAlignment.STRETCH" : "GridItemAlignment.DEFAULT");
    BuildScrollAlignInfo(json);
    BuildGridLayoutInfo(json);
}

SizeF GridPattern::GetChildrenExpandedSize()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, SizeF());
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    auto viewSize = geometryNode->GetFrameSize();
    MinusPaddingToSize(padding, viewSize);

    auto axis = GetAxis();
    float estimatedHeight = 0.f;
    const auto& info = info_;
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, info.axis_);
    if (UseIrregularLayout()) {
        estimatedHeight = info.GetIrregularHeight(mainGap);
    } else if (!layoutProperty->GetLayoutOptions().has_value()) {
        estimatedHeight = info.GetContentHeight(mainGap);
    } else {
        estimatedHeight =
            info.GetContentHeight(layoutProperty->GetLayoutOptions().value(), info.childrenCount_, mainGap);
    }

    if (axis == Axis::VERTICAL) {
        return SizeF(viewSize.Width(), estimatedHeight);
    } else if (axis == Axis::HORIZONTAL) {
        return SizeF(estimatedHeight, viewSize.Height());
    }
    return SizeF();
}
} // namespace OHOS::Ace::NG
