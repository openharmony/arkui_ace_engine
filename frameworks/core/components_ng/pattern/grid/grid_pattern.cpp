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

#include "core/components_ng/pattern/grid/grid_pattern.h"

#include "base/geometry/axis.h"
#include "base/utils/utils.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/perfmonitor/perf_constants.h"
#include "core/components_ng/pattern/grid/grid_adaptive/grid_adaptive_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;
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
    gridLayoutInfo_.crossCount_ = crossCount;

    // When rowsTemplate and columnsTemplate is both setting, use static layout algorithm.
    if (!rows.empty() && !cols.empty()) {
        return MakeRefPtr<GridLayoutAlgorithm>(gridLayoutInfo_, crossCount, mainCount);
    }

    // When rowsTemplate and columnsTemplate is both not setting, use adaptive layout algorithm.
    if (rows.empty() && cols.empty()) {
        return MakeRefPtr<GridAdaptiveLayoutAlgorithm>(gridLayoutInfo_);
    }

    // If only set one of rowTemplate and columnsTemplate, use scrollable layout algorithm.
    if (!gridLayoutProperty->GetLayoutOptions().has_value()) {
        auto result = MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo_, crossCount, mainCount);
        result->SetCanOverScroll(CanOverScroll(GetScrollSource()));
        return result;
    } else {
        auto result = MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(gridLayoutInfo_, crossCount, mainCount);
        result->SetCanOverScroll(CanOverScroll(GetScrollSource()));
        return result;
    }
}

RefPtr<NodePaintMethod> GridPattern::CreateNodePaintMethod()
{
    auto paint = MakeRefPtr<GridPaintMethod>(GetScrollBar());
    CHECK_NULL_RETURN(paint, nullptr);
    auto scrollBarOverlayModifier = GetScrollBarOverlayModifier();
    if (!scrollBarOverlayModifier) {
        scrollBarOverlayModifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
        SetScrollBarOverlayModifier(scrollBarOverlayModifier);
    }
    paint->SetScrollBarOverlayModifier(scrollBarOverlayModifier);
    auto scrollEffect = GetScrollEdgeEffect();
    if (scrollEffect && scrollEffect->IsFadeEffect()) {
        paint->SetEdgeEffect(scrollEffect);
    }
    return paint;
}

void GridPattern::InitScrollableEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto scrollFrameBeginEvent = eventHub->GetOnScrollFrameBegin();
    SetScrollFrameBeginCallback(scrollFrameBeginEvent);
}

void GridPattern::OnModifyDone()
{
    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(gridLayoutProperty);

    if (multiSelectable_ && !isMouseEventInit_) {
        InitMouseEvent();
    }

    if (!multiSelectable_ && isMouseEventInit_) {
        UninitMouseEvent();
    }

    gridLayoutInfo_.axis_ = gridLayoutProperty->IsVertical() ? Axis::VERTICAL : Axis::HORIZONTAL;
    isConfigScrollable_ = gridLayoutProperty->IsConfiguredScrollable();
    if (!isConfigScrollable_) {
        LOGD("use fixed grid template");
        return;
    }
    SetAxis(gridLayoutInfo_.axis_);
    if (!GetScrollableEvent()) {
        AddScrollEvent();
        InitScrollableEvent();
    }

    auto edgeEffect = gridLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::NONE);
    SetEdgeEffect(edgeEffect);

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
    auto scrollable = GetScrollableEvent()->GetScrollable();
    if (scrollable) {
        scrollable->SetOnContinuousSliding([weak = AceType::WeakClaim(this)]() -> double {
            auto grid = weak.Upgrade();
            return grid->GetMainContentSize();
        });
    }
}

void GridPattern::MultiSelectWithoutKeyboard(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto& children = host->GetFrameChildren();
    for (const auto& weak : children) {
        auto itemFrameNode = weak.Upgrade();
        CHECK_NULL_VOID(itemFrameNode);
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
            auto startMainOffset = mouseStartOffset_.GetMainOffset(gridLayoutInfo_.axis_);
            if (gridLayoutInfo_.axis_ == Axis::VERTICAL) {
                iter->second.rect = itemRect + OffsetF(0, totalOffsetOfMousePressed_ - startMainOffset);
            } else {
                iter->second.rect = itemRect + OffsetF(totalOffsetOfMousePressed_ - startMainOffset, 0);
            }
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

bool GridPattern::IsItemSelected(const MouseInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto node = host->FindChildByPosition(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    CHECK_NULL_RETURN_NOLOG(node, false);
    auto itemPattern = node->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN_NOLOG(itemPattern, false);
    return itemPattern->IsSelected();
}

float GridPattern::GetMainContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetPaddingSize().MainSize(gridLayoutInfo_.axis_);
}

void GridPattern::FireOnScrollStart()
{
    PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_LIST_FLING, PerfActionType::FIRST_MOVE, "");
    if (GetScrollAbort()) {
        return;
    }
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        scrollBar->PlayScrollBarStartAnimation();
    }
    StopScrollBarAnimatorByProxy();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID_NOLOG(hub);
    auto onScrollStart = hub->GetOnScrollStart();
    CHECK_NULL_VOID_NOLOG(onScrollStart);
    onScrollStart();
}

bool GridPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        FireOnScrollStart();
        return true;
    }
    return ScrollablePattern::OnScrollCallback(offset, source);
}

SizeF GridPattern::GetContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    return geometryNode->GetPaddingSize();
}

void GridPattern::CheckRestartSpring()
{
    if (!ScrollableIdle() || !IsOutOfBoundary()) {
        return;
    }
    auto edgeEffect = GetScrollEdgeEffect();
    if (!edgeEffect || !edgeEffect->IsSpringEffect()) {
        return;
    }
    if (AnimateRunning()) {
        return;
    }
    
    FireOnScrollStart();
    edgeEffect->ProcessScrollOver(0);
}

float GridPattern::GetMainGap()
{
    float mainGap = 0.0;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, gridLayoutInfo_.axis_);
    return mainGap;
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
        if (IsOutOfBoundary()) {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        return false;
    }
    SetScrollSource(source);

    // When finger moves down, offset is positive.
    // When finger moves up, offset is negative.
    auto itemsHeight = gridLayoutInfo_.GetTotalHeightOfItemsInView(GetMainGap());
    if (gridLayoutInfo_.offsetEnd_) {
        if (source == SCROLL_FROM_UPDATE) {
            auto overScroll = gridLayoutInfo_.currentOffset_ - (GetMainContentSize() - itemsHeight);
            auto friction = CalculateFriction(std::abs(overScroll) / GetMainContentSize());
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.currentOffset_ = gridLayoutInfo_.currentOffset_ + offset * friction;
        } else {
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.currentOffset_ += offset;
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

        if (GreatOrEqual(gridLayoutInfo_.currentOffset_, GetMainContentSize() - itemsHeight)) {
            gridLayoutInfo_.offsetEnd_ = false;
            gridLayoutInfo_.reachEnd_ = false;
        }
        return true;
    }
    if (gridLayoutInfo_.reachStart_) {
        if (source == SCROLL_FROM_UPDATE) {
            auto friction = CalculateFriction(std::abs(gridLayoutInfo_.currentOffset_) / GetMainContentSize());
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.currentOffset_ = gridLayoutInfo_.currentOffset_ + offset * friction;
        } else {
            gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
            gridLayoutInfo_.currentOffset_ += offset;
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

        if (LessOrEqual(gridLayoutInfo_.currentOffset_, 0.0)) {
            gridLayoutInfo_.reachStart_ = false;
        }
        return true;
    }
    // maybe no measure after last update
    if (LessNotEqual(std::abs(gridLayoutInfo_.currentOffset_), gridLayoutInfo_.lastMainSize_)) {
        gridLayoutInfo_.prevOffset_ = gridLayoutInfo_.currentOffset_;
    }
    gridLayoutInfo_.currentOffset_ += offset;
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
    if (firstShow_ || gridLayoutInfo_.startIndex_ != gridLayoutInfo.startIndex_) {
        eventhub->FireOnScrollToIndex(gridLayoutInfo.startIndex_);
        firstShow_ = false;
    }

    bool indexChanged = (gridLayoutInfo.startIndex_ != gridLayoutInfo_.startIndex_) ||
                        (gridLayoutInfo.endIndex_ != gridLayoutInfo_.endIndex_);
    bool offsetEnd = gridLayoutInfo_.offsetEnd_;
    float currentOffset = gridLayoutInfo_.currentOffset_;
    bool reachEnd = gridLayoutInfo_.reachEnd_;
    bool reachStart = gridLayoutInfo_.reachStart_;
    gridLayoutInfo_ = gridLayoutInfo;
    gridLayoutInfo_.childrenCount_ = dirty->GetTotalChildCount();
    currentHeight_ = EstimateHeight();
    ProcessEvent(indexChanged, currentHeight_ - prevHeight_, currentOffset, offsetEnd, reachEnd, reachStart);
    prevFinalOffset_ = currentHeight_ - prevHeight_;
    prevHeight_ = currentHeight_;
    SetScrollSource(SCROLL_FROM_NONE);
    UpdateScrollBarOffset();
    if (config.frameSizeChange) {
        if (GetScrollBar() != nullptr) {
            GetScrollBar()->ScheduleDisapplearDelayTask();
        }
    }
    CheckRestartSpring();
    CheckScrollable();
    MarkSelectedItems();
    return false;
}

void GridPattern::CheckScrollable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gridLayoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID(gridLayoutProperty);
    if (((gridLayoutInfo_.endIndex_ - gridLayoutInfo_.startIndex_ + 1) < gridLayoutInfo_.childrenCount_) ||
        (gridLayoutInfo_.GetTotalHeightOfItemsInView(GetMainGap()) > GetMainContentSize())) {
        scrollable_ = true;
    } else {
        if (gridLayoutInfo_.startMainLineIndex_ != 0) {
            scrollable_ = true;
        } else {
            scrollable_ = false;
        }
    }

    SetScrollEnable(scrollable_);

    if (!gridLayoutProperty->GetScrollEnabled().value_or(scrollable_)) {
        SetScrollEnable(false);
    }
}

void GridPattern::ProcessEvent(
    bool indexChanged, float finalOffset, float currentOffset, bool offsetEnd, bool reachEnd, bool reachStart)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gridEventHub = host->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(gridEventHub);

    auto onScroll = gridEventHub->GetOnScroll();
    auto scrollSource = GetScrollSource();
    if (scrollStop_ && !GetScrollAbort()) {
        auto offsetPX = Dimension(finalOffset);
        auto offsetVP = Dimension(offsetPX.ConvertToVp(), DimensionUnit::VP);
        if (onScroll) {
            if (scrollSource == SCROLL_FROM_UPDATE || scrollSource == SCROLL_FROM_AXIS ||
                scrollSource == SCROLL_FROM_BAR) {
                onScroll(offsetVP, ScrollState::SCROLL);
                onScroll(0.0_vp, ScrollState::IDLE);
            } else if (scrollSource == SCROLL_FROM_ANIMATION || scrollSource == SCROLL_FROM_ANIMATION_SPRING ||
                       scrollSource == SCROLL_FROM_ANIMATION_CONTROLLER || scrollSource == SCROLL_FROM_BAR_FLING) {
                onScroll(offsetVP, ScrollState::FLING);
                onScroll(0.0_vp, ScrollState::IDLE);
            } else {
                onScroll(offsetVP, ScrollState::IDLE);
            }
        }
    } else if (onScroll && !NearZero(finalOffset)) {
        auto offsetPX = Dimension(finalOffset);
        auto offsetVP = Dimension(offsetPX.ConvertToVp(), DimensionUnit::VP);
        if (scrollSource == SCROLL_FROM_UPDATE || scrollSource == SCROLL_FROM_AXIS || scrollSource == SCROLL_FROM_BAR) {
            onScroll(offsetVP, ScrollState::SCROLL);
        } else if (scrollSource == SCROLL_FROM_ANIMATION || scrollSource == SCROLL_FROM_ANIMATION_SPRING ||
                   scrollSource == SCROLL_FROM_ANIMATION_CONTROLLER || scrollSource == SCROLL_FROM_BAR_FLING) {
            onScroll(offsetVP, ScrollState::FLING);
        } else {
            onScroll(offsetVP, ScrollState::IDLE);
        }
    }

    if (indexChanged) {
        auto onScrollIndex = gridEventHub->GetOnScrollIndex();
        if (onScrollIndex) {
            onScrollIndex(gridLayoutInfo_.startIndex_, gridLayoutInfo_.endIndex_);
        }
    }

    auto onReachStart = gridEventHub->GetOnReachStart();
    if (onReachStart && gridLayoutInfo_.startIndex_ == 0) {
        if ((scrollSource == SCROLL_FROM_UPDATE || scrollSource == SCROLL_FROM_ANIMATION_SPRING) &&
            gridLayoutInfo_.reachStart_ && !reachStart &&
            (!NearZero(gridLayoutInfo_.currentOffset_) || Negative(finalOffset))) {
            onReachStart();
            initialIndex_ = true;
        }
        if (scrollSource == SCROLL_FROM_ANIMATION &&
            ((gridLayoutInfo_.reachStart_ && !reachStart) ||
                (NearZero(gridLayoutInfo_.currentOffset_) && NearZero(currentOffset) &&
                    Negative(gridLayoutInfo_.prevOffset_)))) {
            onReachStart();
            initialIndex_ = true;
        }
        if (scrollSource == SCROLL_FROM_UPDATE && NearZero(gridLayoutInfo_.currentOffset_) && NearZero(currentOffset) &&
            Negative(gridLayoutInfo_.prevOffset_)) {
            onReachStart();
            initialIndex_ = true;
        }
        if (scrollSource == SCROLL_FROM_AXIS && !gridLayoutInfo_.reachStart_ && !reachStart &&
            NearZero(gridLayoutInfo_.currentOffset_) && Negative(finalOffset)) {
            onReachStart();
            initialIndex_ = true;
        }
        if (scrollSource == SCROLL_FROM_ANIMATION_SPRING && NearZero(gridLayoutInfo_.currentOffset_)) {
            onReachStart();
            initialIndex_ = true;
        }
        if (scrollSource == SCROLL_FROM_JUMP && Negative(finalOffset) && NearZero(gridLayoutInfo_.currentOffset_) &&
            (NearZero(gridLayoutInfo_.prevOffset_) || Negative(gridLayoutInfo_.prevOffset_))) {
            onReachStart();
            initialIndex_ = true;
        }
        if ((scrollSource == SCROLL_FROM_BAR || scrollSource == SCROLL_FROM_BAR_FLING) && gridLayoutInfo_.reachStart_ &&
            !reachStart && NearZero(gridLayoutInfo_.currentOffset_) && Negative(finalOffset)) {
            onReachStart();
            initialIndex_ = true;
        }
        if (scrollSource == SCROLL_FROM_ANIMATION_CONTROLLER && NearZero(gridLayoutInfo_.currentOffset_) &&
            ((!gridLayoutInfo_.reachStart_ && !NearZero(finalOffset)) || gridLayoutInfo_.reachStart_)) {
            onReachStart();
            initialIndex_ = true;
        }
    }
    if (onReachStart && !initialIndex_ && gridLayoutInfo_.startIndex_ == 0) {
        onReachStart();
        initialIndex_ = true;
    }

    auto onReachEnd = gridEventHub->GetOnReachEnd();
    if (onReachEnd && gridLayoutInfo_.endIndex_ == (gridLayoutInfo_.childrenCount_ - 1)) {
        if (scrollSource == SCROLL_FROM_UPDATE && Positive(finalOffset) && gridLayoutInfo_.offsetEnd_ && !offsetEnd) {
            onReachEnd();
        }
        if (scrollSource == SCROLL_FROM_ANIMATION && gridLayoutInfo_.reachEnd_ && !reachEnd &&
            Positive(prevFinalOffset_)) {
            onReachEnd();
        }
        if (scrollSource == SCROLL_FROM_UPDATE && Positive(prevFinalOffset_) && NearZero(finalOffset) &&
            !gridLayoutInfo_.offsetEnd_ && !offsetEnd) {
            onReachEnd();
        }
        if (scrollSource == SCROLL_FROM_AXIS && gridLayoutInfo_.reachEnd_ && !reachEnd && Positive(finalOffset)) {
            onReachEnd();
        }
        if (scrollSource == SCROLL_FROM_ANIMATION_SPRING && !gridLayoutInfo_.reachEnd_ && !gridLayoutInfo_.offsetEnd_) {
            onReachEnd();
        }
        if (scrollSource == SCROLL_FROM_JUMP && gridLayoutInfo_.offsetEnd_ && gridLayoutInfo_.reachEnd_) {
            onReachEnd();
        }
        if (scrollSource == SCROLL_FROM_ANIMATION_CONTROLLER && gridLayoutInfo_.offsetEnd_ && !offsetEnd) {
            onReachEnd();
        }
        if ((scrollSource == SCROLL_FROM_BAR || scrollSource == SCROLL_FROM_BAR_FLING) && Positive(finalOffset) &&
            !NearZero(gridLayoutInfo_.currentOffset_) && gridLayoutInfo_.offsetEnd_ && !offsetEnd) {
            onReachEnd();
        }
        if (scrollSource == SCROLL_FROM_NONE && reachEnd && gridLayoutInfo_.reachEnd_ && !gridLayoutInfo_.offsetEnd_ &&
            !offsetEnd && Positive(prevFinalOffset_)) {
            onReachEnd();
        }
    }

    if (scrollStop_) {
        auto onScrollStop = gridEventHub->GetOnScrollStop();
        if (!GetScrollAbort()) {
            if (onScrollStop) {
                SetScrollSource(SCROLL_FROM_NONE);
                onScrollStop();
            }
            auto scrollBar = GetScrollBar();
            if (scrollBar) {
                scrollBar->ScheduleDisapplearDelayTask();
            }
            StartScrollBarAnimatorByProxy();
        }
        if (!GetScrollAbort()) {
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_LIST_FLING, false);
        }
        scrollStop_ = false;
        SetScrollAbort(false);
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
    scrollStop_ = true;
    MarkDirtyNodeSelf();
}

void GridPattern::OnScrollStartCallback()
{
    FireOnScrollStart();
}

std::pair<bool, bool> GridPattern::IsFirstOrLastFocusableChild(int32_t curMainIndex, int32_t curCrossIndex)
{
    auto crossIndexSet = GetFocusableChildCrossIndexesAt(curMainIndex);
    auto findLesser = std::find_if(crossIndexSet.begin(), crossIndexSet.end(),
        [curCrossIndex](int32_t crossIndex) { return curCrossIndex > crossIndex; });
    auto findGreater = std::find_if(crossIndexSet.begin(), crossIndexSet.end(),
        [curCrossIndex](int32_t crossIndex) { return curCrossIndex < crossIndex; });
    return { findLesser == crossIndexSet.end(), findGreater == crossIndexSet.end() };
}

std::pair<FocusStep, FocusStep> GridPattern::GetFocusSteps(int32_t curMainIndex, int32_t curCrossIndex, FocusStep step)
{
    auto firstStep = FocusStep::NONE;
    auto secondStep = FocusStep::NONE;
    auto isFirstOrLastFocusable = IsFirstOrLastFocusableChild(curMainIndex, curCrossIndex);
    auto isFirstFocusable = isFirstOrLastFocusable.first;
    auto isLastFocusable = isFirstOrLastFocusable.second;
    if (gridLayoutInfo_.axis_ == Axis::VERTICAL) {
        if (isFirstFocusable && step == FocusStep::SHIFT_TAB) {
            firstStep = FocusStep::UP;
            secondStep = FocusStep::RIGHT_END;
        } else if (isLastFocusable && step == FocusStep::TAB) {
            firstStep = FocusStep::DOWN;
            secondStep = FocusStep::LEFT_END;
        }
    } else if (gridLayoutInfo_.axis_ == Axis::HORIZONTAL) {
        if (isFirstFocusable && step == FocusStep::SHIFT_TAB) {
            firstStep = FocusStep::LEFT;
            secondStep = FocusStep::DOWN_END;
        } else if (isLastFocusable && step == FocusStep::TAB) {
            firstStep = FocusStep::RIGHT;
            secondStep = FocusStep::UP_END;
        }
    }
    LOGI("Get focus steps. First step is %{public}d. Second step is %{public}d", firstStep, secondStep);
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

    auto curMainIndex = curItemProperty->GetMainIndex().value_or(-1);
    auto curCrossIndex = curItemProperty->GetCrossIndex().value_or(-1);
    auto curMainSpan = curItemProperty->GetMainSpan(gridLayoutInfo_.axis_);
    auto curCrossSpan = curItemProperty->GetCrossSpan(gridLayoutInfo_.axis_);
    if (curMainIndex < 0 || curCrossIndex < 0) {
        LOGE("can't find focused child.");
        return nullptr;
    }
    if (gridLayoutInfo_.gridMatrix_.find(curMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
        LOGE("Can not find current main index: %{public}d", curMainIndex);
        return nullptr;
    }
    LOGI("GetNextFocusNode: Current focused item is (%{public}d,%{public}d)-[%{public}d,%{public}d]. Focus step is "
         "%{public}d",
        curMainIndex, curCrossIndex, curMainSpan, curCrossSpan, step);
    auto focusSteps = GetFocusSteps(curMainIndex, curCrossIndex, step);
    if (focusSteps.first != FocusStep::NONE && focusSteps.second != FocusStep::NONE) {
        auto firstStepRes = GetNextFocusNode(focusSteps.first, currentFocusNode);
        if (!firstStepRes.Upgrade()) {
            return nullptr;
        }
        auto secondStepRes = GetNextFocusNode(focusSteps.second, firstStepRes);
        if (!secondStepRes.Upgrade()) {
            return firstStepRes;
        }
        return secondStepRes;
    }
    auto indexes = GetNextIndexByStep(curMainIndex, curCrossIndex, curMainSpan, curCrossSpan, step);
    auto nextMainIndex = indexes.first;
    auto nextCrossIndex = indexes.second;
    while (nextMainIndex >= 0 && nextCrossIndex >= 0) {
        if (gridLayoutInfo_.gridMatrix_.find(nextMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
            LOGE("Can not find next main index: %{public}d", nextMainIndex);
            return nullptr;
        }
        auto nextMaxCrossCount = GetCrossCount();
        auto flag = (step == FocusStep::LEFT_END) || (step == FocusStep::RIGHT_END);
        auto weakChild = SearchFocusableChildInCross(
            nextMainIndex, nextCrossIndex, nextMaxCrossCount, flag ? -1 : curMainIndex, curCrossIndex);
        auto child = weakChild.Upgrade();
        if (child && child->IsFocusable()) {
            ScrollToFocusNode(weakChild);
            return weakChild;
        }
        auto indexes = GetNextIndexByStep(nextMainIndex, nextCrossIndex, 1, 1, step);
        nextMainIndex = indexes.first;
        nextCrossIndex = indexes.second;
    }
    return nullptr;
}

std::pair<int32_t, int32_t> GridPattern::GetNextIndexByStep(
    int32_t curMainIndex, int32_t curCrossIndex, int32_t curMainSpan, int32_t curCrossSpan, FocusStep step)
{
    LOGI("Current item: (%{public}d,%{public}d)-[%{public}d,%{public}d]. Grid axis: %{public}d, step: %{public}d",
        curMainIndex, curCrossIndex, curMainSpan, curCrossSpan, gridLayoutInfo_.axis_, step);
    auto curMainStart = gridLayoutInfo_.startMainLineIndex_;
    auto curMainEnd = gridLayoutInfo_.endMainLineIndex_;
    auto curChildStartIndex = gridLayoutInfo_.startIndex_;
    auto curChildEndIndex = gridLayoutInfo_.endIndex_;
    auto childrenCount = gridLayoutInfo_.childrenCount_;
    if (gridLayoutInfo_.gridMatrix_.find(curMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
        LOGE("Can not find current main index: %{public}d", curMainIndex);
        return { -1, -1 };
    }
    auto curMaxCrossCount = GetCrossCount();
    LOGD("Current main index start-end: %{public}d-%{public}d, Current cross count: %{public}d, Current child "
         "index start-end: %{public}d-%{public}d, Total children count: %{public}d",
        curMainStart, curMainEnd, curMaxCrossCount, curChildStartIndex, curChildEndIndex, childrenCount);

    auto nextMainIndex = curMainIndex;
    auto nextCrossIndex = curCrossIndex;
    if ((step == FocusStep::UP_END && gridLayoutInfo_.axis_ == Axis::HORIZONTAL) ||
        (step == FocusStep::LEFT_END && gridLayoutInfo_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = 0;
    } else if ((step == FocusStep::DOWN_END && gridLayoutInfo_.axis_ == Axis::HORIZONTAL) ||
               (step == FocusStep::RIGHT_END && gridLayoutInfo_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curMaxCrossCount - 1;
    } else if (((step == FocusStep::UP || step == FocusStep::SHIFT_TAB) && gridLayoutInfo_.axis_ == Axis::HORIZONTAL) ||
               ((step == FocusStep::LEFT || step == FocusStep::SHIFT_TAB) && gridLayoutInfo_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curCrossIndex - 1;
    } else if ((step == FocusStep::UP && gridLayoutInfo_.axis_ == Axis::VERTICAL) ||
               (step == FocusStep::LEFT && gridLayoutInfo_.axis_ == Axis::HORIZONTAL)) {
        nextMainIndex = curMainIndex - 1;
        nextCrossIndex = curCrossIndex + static_cast<int32_t>((curCrossSpan - 1) / 2);
    } else if (((step == FocusStep::DOWN || step == FocusStep::TAB) && gridLayoutInfo_.axis_ == Axis::HORIZONTAL) ||
               ((step == FocusStep::RIGHT || step == FocusStep::TAB) && gridLayoutInfo_.axis_ == Axis::VERTICAL)) {
        nextMainIndex = curMainIndex;
        nextCrossIndex = curCrossIndex + curCrossSpan;
    } else if ((step == FocusStep::DOWN && gridLayoutInfo_.axis_ == Axis::VERTICAL) ||
               (step == FocusStep::RIGHT && gridLayoutInfo_.axis_ == Axis::HORIZONTAL)) {
        nextMainIndex = curMainIndex + curMainSpan;
        nextCrossIndex = curCrossIndex + static_cast<int32_t>((curCrossSpan - 1) / 2);
    } else {
        LOGE("Next index return: Invalid step: %{public}d and axis: %{public}d", step, gridLayoutInfo_.axis_);
        return { -1, -1 };
    }
    if (curChildStartIndex == 0 && curMainIndex == 0 && nextMainIndex < curMainIndex) {
        LOGD("Item reach at grid top and next main index less than current main index. Reset next main index.");
        nextMainIndex = curMainIndex;
    }
    if (curChildEndIndex == childrenCount - 1 && curMainIndex == curMainEnd && nextMainIndex > curMainIndex) {
        LOGD("Item reach at grid top and next main index greater than current main index. Reset next main index.");
        nextMainIndex = curMainIndex;
    }
    if (nextMainIndex == curMainIndex && nextCrossIndex == curCrossIndex) {
        LOGI("Next index return: Move stoped. Next index: (%{public}d,%{public}d) is same as current.", nextMainIndex,
            nextCrossIndex);
        return { -1, -1 };
    }
    if (curChildStartIndex != 0 && curMainIndex == curMainStart && nextMainIndex < curMainIndex) {
        // Scroll item up.
        LOGD("Item donot reach top and next main index is less than current. Do UpdateStartIndex(%{public}d)",
            curChildStartIndex - 1);
        UpdateStartIndex(curChildStartIndex - 1);
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    } else if (curChildEndIndex != childrenCount - 1 && curMainIndex == curMainEnd && nextMainIndex > curMainIndex) {
        // Scroll item down.
        LOGD("Item donot reach bottom and next main index is greater than current. Do UpdateStartIndex(%{public}d)",
            curChildEndIndex + 1);
        UpdateStartIndex(curChildEndIndex + 1);
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    }
    curMainStart = gridLayoutInfo_.startMainLineIndex_;
    curMainEnd = gridLayoutInfo_.endMainLineIndex_;
    if (nextMainIndex < curMainStart || nextMainIndex > curMainEnd) {
        LOGW("Next index return: Error. Next main index is out of range(%{public}d,%{public}d)", curMainStart,
            curMainEnd);
        return { -1, -1 };
    }
    if (nextCrossIndex < 0) {
        LOGW("Next index return: Error. Next cross index is less than 0.");
        return { -1, -1 };
    }
    if (gridLayoutInfo_.gridMatrix_.find(nextMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
        LOGE("Can not find next main index: %{public}d", nextMainIndex);
        return { -1, -1 };
    }
    auto nextMaxCrossCount = GetCrossCount();
    if (nextCrossIndex >= nextMaxCrossCount) {
        LOGI("Next index: { %{public}d,%{public}d }. Next cross index is greater than max cross count: %{public}d.",
            nextMainIndex, nextCrossIndex, nextMaxCrossCount - 1);
        if (nextMaxCrossCount - 1 != curCrossIndex) {
            LOGI("Current cross index: %{public}d is not the tail item. Return to the tail: { %{public}d,%{public}d }",
                curCrossIndex, nextMainIndex, nextMaxCrossCount - 1);
            return { nextMainIndex, nextMaxCrossCount - 1 };
        }
        LOGW("Current cross index: %{public}d is the tail item. No next item can be found!", curCrossIndex);
        return { -1, -1 };
    }
    LOGI("Next index return: { %{public}d,%{public}d }.", nextMainIndex, nextCrossIndex);
    return { nextMainIndex, nextCrossIndex };
}

WeakPtr<FocusHub> GridPattern::SearchFocusableChildInCross(
    int32_t tarMainIndex, int32_t tarCrossIndex, int32_t maxCrossCount, int32_t curMainIndex, int32_t curCrossIndex)
{
    LOGD("Search child from index: (%{public}d,%{public}d). Current index: (%{public}d,%{public}d)", tarMainIndex,
        tarCrossIndex, curMainIndex, curCrossIndex);
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
            LOGE("Invalid search index: (%{public}d,%{public}d). It's same as current.", tarMainIndex, tarCrossIndex);
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
            LOGI("Found child. Index: %{public}d,%{public}d", tarMainIndex, curIndex);
            return weakChild;
        }
    }
    LOGD("Child can not be found.");
    return nullptr;
}

WeakPtr<FocusHub> GridPattern::GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarCrossIndex, int32_t tarIndex)
{
    LOGD("Get target item location is (%{public}d,%{public}d / %{public}d)", tarMainIndex, tarCrossIndex, tarIndex);
    auto gridFrame = GetHost();
    CHECK_NULL_RETURN(gridFrame, nullptr);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_RETURN(gridFocus, nullptr);
    auto childFocusList = gridFocus->GetChildren();
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
            auto curMainSpan = childItemProperty->GetMainSpan(gridLayoutInfo_.axis_);
            auto curCrossSpan = childItemProperty->GetCrossSpan(gridLayoutInfo_.axis_);
            if (curMainIndex <= tarMainIndex && curMainIndex + curMainSpan > tarMainIndex &&
                curCrossIndex <= tarCrossIndex && curCrossIndex + curCrossSpan > tarCrossIndex) {
                return AceType::WeakClaim(AceType::RawPtr(childFocus));
            }
        } else {
            if (gridLayoutInfo_.gridMatrix_.find(curMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
                LOGE("Can not find target main index: %{public}d", curMainIndex);
                continue;
            }
            if (gridLayoutInfo_.gridMatrix_[curMainIndex].find(curCrossIndex) ==
                gridLayoutInfo_.gridMatrix_[curMainIndex].end()) {
                LOGE("Can not find target cross index: %{public}d", curCrossIndex);
                continue;
            }
            if (gridLayoutInfo_.gridMatrix_[curMainIndex][curCrossIndex] == tarIndex) {
                return AceType::WeakClaim(AceType::RawPtr(childFocus));
            }
        }
    }
    LOGD("Item at location(%{public}d,%{public}d / %{public}d) can not found.", tarMainIndex, tarCrossIndex, tarIndex);
    return nullptr;
}

std::unordered_set<int32_t> GridPattern::GetFocusableChildCrossIndexesAt(int32_t tarMainIndex)
{
    std::unordered_set<int32_t> result;
    auto gridFrame = GetHost();
    CHECK_NULL_RETURN(gridFrame, result);
    auto gridFocus = gridFrame->GetFocusHub();
    CHECK_NULL_RETURN(gridFocus, result);
    auto childFocusList = gridFocus->GetChildren();
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
        auto curMainIndex = childItemProperty->GetMainIndex().value_or(-1);
        auto curCrossIndex = childItemProperty->GetCrossIndex().value_or(-1);
        if (curMainIndex == tarMainIndex) {
            result.emplace(curCrossIndex);
        }
    }
    std::string output;
    for (const auto& index : result) {
        output += std::to_string(index);
    }
    LOGD("Focusable child cross index list at main(%{public}d) is { %{public}s }", tarMainIndex, output.c_str());
    return result;
}

void GridPattern::ScrollToFocusNode(const WeakPtr<FocusHub>& focusNode)
{
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
    if (gridLayoutInfo_.gridMatrix_.find(tarMainIndex) == gridLayoutInfo_.gridMatrix_.end()) {
        LOGE("Can not find target main index: %{public}d", tarMainIndex);
        if (tarMainIndex == 0) {
            return 0;
        }
        return gridLayoutInfo_.childrenCount_ - 1;
    }
    if (gridLayoutInfo_.gridMatrix_[tarMainIndex].find(tarCrossIndex) ==
        gridLayoutInfo_.gridMatrix_[tarMainIndex].end()) {
        LOGE("Can not find target cross index: %{public}d", tarCrossIndex);
        if (tarMainIndex == 0) {
            return 0;
        }
        return gridLayoutInfo_.childrenCount_ - 1;
    }
    return gridLayoutInfo_.gridMatrix_[tarMainIndex][tarCrossIndex];
}

void GridPattern::ScrollToFocusNodeIndex(int32_t index)
{
    UpdateStartIndex(index);
    auto pipeline = PipelineContext::GetCurrentContext();
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
    CHECK_NULL_RETURN_NOLOG(focusFrameNode, false);
    auto focusHub = focusFrameNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    auto scrollToIndex = GetFocusNodeIndex(focusHub);
    if (scrollToIndex < 0) {
        return false;
    }
    auto ret = UpdateStartIndex(scrollToIndex);
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
    return ret;
}

void GridPattern::ScrollBy(float offset)
{
    StopAnimate();
    UpdateCurrentOffset(-offset, SCROLL_FROM_JUMP);
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
}

void GridPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    Pattern::ToJsonValue(json);
    json->Put("multiSelectable", multiSelectable_ ? "true" : "false");
    json->Put("supportAnimation", supportAnimation_ ? "true" : "false");
    json->Put("friction", GetFriction());
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
}

bool GridPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((event.code == KeyCode::KEY_PAGE_DOWN) || (event.code == KeyCode::KEY_PAGE_UP)) {
        ScrollPage(event.code == KeyCode::KEY_PAGE_UP);
    }
    return false;
}

bool GridPattern::HandleDirectionKey(KeyCode code)
{
    if (code == KeyCode::KEY_DPAD_UP) {
        // Need to update: current selection
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN) {
        // Need to update: current selection
        return true;
    }
    return false;
}

void GridPattern::SetPositionController(const RefPtr<ScrollableController>& controller)
{
    positionController_ = DynamicCast<GridPositionController>(controller);
    if (controller) {
        controller->SetScrollPattern(AceType::WeakClaim<GridPattern>(this));
    }
}

void GridPattern::ScrollPage(bool reverse)
{
    StopAnimate();
    if (!isConfigScrollable_) {
        return;
    }
    if (!reverse) {
        LOGD("PgDn. Scroll offset is %{public}f", -GetMainContentSize());
        UpdateCurrentOffset(-GetMainContentSize(), SCROLL_FROM_JUMP);
    } else {
        LOGD("PgUp. Scroll offset is %{public}f", GetMainContentSize());
        UpdateCurrentOffset(GetMainContentSize(), SCROLL_FROM_JUMP);
    }
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
}

bool GridPattern::UpdateStartIndex(int32_t index)
{
    if (!isConfigScrollable_) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    gridLayoutInfo_.jumpIndex_ = index;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    SetScrollSource(SCROLL_FROM_JUMP);
    return true;
}

bool GridPattern::UpdateStartIndex(int32_t index, ScrollAlign align)
{
    gridLayoutInfo_.scrollAlign_ = align;
    return UpdateStartIndex(index);
}

void GridPattern::OnAnimateStop()
{
    scrollStop_ = true;
    MarkDirtyNodeSelf();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
}

void GridPattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth)
{
    if (!isConfigScrollable_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_START);
    ScrollablePattern::AnimateTo(position, duration, curve, smooth);
    FireOnScrollStart();
}

void GridPattern::ScrollTo(float position)
{
    if (!isConfigScrollable_) {
        return;
    }
    LOGI("ScrollTo:%{public}f", position);
    StopAnimate();
    UpdateCurrentOffset(GetTotalOffset() - position, SCROLL_FROM_JUMP);
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
}

float GridPattern::EstimateHeight() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN_NOLOG(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN_NOLOG(geometryNode, 0.0);
    const auto& info = gridLayoutInfo_;
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();

    float heightSum = 0;
    int32_t itemCount = 0;
    float height = 0;
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
    auto averageHeight = heightSum / itemCount;
    height = info.startIndex_ * averageHeight - info.currentOffset_;
    if (itemCount >= (info.childrenCount_ - 1)) {
        height = info.GetStartLineOffset(mainGap);
    }
    return height;
}

float GridPattern::GetAverageHeight() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN_NOLOG(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN_NOLOG(geometryNode, 0.0);
    const auto& info = gridLayoutInfo_;
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
    auto host = GetHost();
    CHECK_NULL_RETURN_NOLOG(host, 0.0f);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN_NOLOG(geometryNode, 0.0f);
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    float heightSum = 0;
    int32_t itemCount = 0;
    float estimatedHeight = 0.f;
    if (scrollbarInfo_.first.has_value() && scrollbarInfo_.second.has_value()) {
        estimatedHeight = scrollbarInfo_.second.value();
    } else {
        auto mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, gridLayoutInfo_.axis_);
        for (const auto& item : gridLayoutInfo_.lineHeightMap_) {
            auto line = gridLayoutInfo_.gridMatrix_.find(item.first);
            if (line == gridLayoutInfo_.gridMatrix_.end()) {
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
        auto averageHeight = heightSum / itemCount;
        if (itemCount >= (gridLayoutInfo_.childrenCount_ - 1)) {
            estimatedHeight = heightSum - mainGap;
        } else {
            estimatedHeight = heightSum + (gridLayoutInfo_.childrenCount_ - itemCount) * averageHeight;
        }
    }
    return estimatedHeight;
}

void GridPattern::UpdateScrollBarOffset()
{
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    const auto& info = gridLayoutInfo_;
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto layoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    float heightSum = 0;
    int32_t itemCount = 0;
    float offset = 0;
    float estimatedHeight = 0.f;
    if (scrollbarInfo_.first.has_value() && scrollbarInfo_.second.has_value()) {
        offset = scrollbarInfo_.first.value();
        estimatedHeight = scrollbarInfo_.second.value();
    } else {
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
        auto averageHeight = itemCount == 0 ? 0.0 : heightSum / itemCount;
        offset = info.startIndex_ * averageHeight - info.currentOffset_;
        if (itemCount >= (info.childrenCount_ - 1)) {
            estimatedHeight = heightSum - mainGap;
            offset = info.GetStartLineOffset(mainGap);
        } else {
            estimatedHeight = heightSum + (info.childrenCount_ - itemCount) * averageHeight;
        }
    }
    auto viewSize = geometryNode->GetFrameSize();
    if (info.startMainLineIndex_ != 0 && info.startIndex_ == 0) {
        for (int32_t lineIndex = info.startMainLineIndex_ - 1; lineIndex >= 0; lineIndex--) {
            offset += info.lineHeightMap_.find(lineIndex)->second;
        }
    }
    UpdateScrollBarRegion(offset, estimatedHeight, Size(viewSize.Width(), viewSize.Height()), Offset(0.0, 0.0));
}

RefPtr<PaintProperty> GridPattern::CreatePaintProperty()
{
    auto defaultDisplayMode = DisplayMode::OFF;
    const static int32_t PLATFORM_VERSION_TEN = 10;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    if (pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        defaultDisplayMode = DisplayMode::AUTO;
    }
    auto property = MakeRefPtr<ScrollablePaintProperty>();
    // default "scrollBar" attribute of Grid is BarState.Off
    property->UpdateScrollBarMode(defaultDisplayMode);
    return property;
}

int32_t GridPattern::GetOriginalIndex() const
{
    return gridLayoutInfo_.GetOriginalIndex();
}

int32_t GridPattern::GetCrossCount() const
{
    return gridLayoutInfo_.crossCount_;
}

int32_t GridPattern::GetChildrenCount() const
{
    return gridLayoutInfo_.childrenCount_;
}

void GridPattern::ClearDragState()
{
    gridLayoutInfo_.ClearDragState();
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
        if (mainIndex * gridLayoutInfo_.crossCount_ + crossIndex == insertIndex) {
            auto size = item->GetRenderContext()->GetPaintRectWithTransform();
            size.SetOffset(item->GetTransformRelativeOffset());
            gridLayoutInfo_.currentRect_ = size;
            break;
        }
    }
}

void GridPattern::MoveItems(int32_t itemIndex, int32_t insertIndex)
{
    if (insertIndex < 0 ||
        insertIndex >= ((itemIndex == -1) ? (gridLayoutInfo_.childrenCount_ + 1) : gridLayoutInfo_.childrenCount_)) {
        return;
    }

    if (itemIndex == -1) {
        UpdateRectOfDraggedInItem(insertIndex);
    }

    gridLayoutInfo_.SwapItems(itemIndex, insertIndex);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
}

bool GridPattern::IsOutOfBoundary()
{
    bool outOfStart = gridLayoutInfo_.reachStart_ && Positive(gridLayoutInfo_.currentOffset_);
    float endPos = gridLayoutInfo_.currentOffset_ + gridLayoutInfo_.totalHeightOfItemsInView_;
    bool outOfEnd = (gridLayoutInfo_.endIndex_ == gridLayoutInfo_.childrenCount_ - 1) &&
        LessNotEqual(endPos, gridLayoutInfo_.lastMainSize_);
    bool scrollable = (gridLayoutInfo_.startIndex_ > 0) ||
        (gridLayoutInfo_.endIndex_ < gridLayoutInfo_.childrenCount_ - 1) ||
        GreatNotEqual(gridLayoutInfo_.totalHeightOfItemsInView_, gridLayoutInfo_.lastMainSize_);
    return (outOfStart || outOfEnd) && scrollable;
}

void GridPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto grid = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(grid, 0.0);
        return grid->gridLayoutInfo_.currentOffset_;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto grid = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(grid, 0.0);
        return grid->GetMainContentSize() - grid->gridLayoutInfo_.GetTotalHeightOfItemsInView(grid->GetMainGap());
    });
    scrollEffect->SetTrailingCallback([]() -> double { return 0.0; });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto grid = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(grid, 0.0);
        return grid->GetMainContentSize() - grid->gridLayoutInfo_.GetTotalHeightOfItemsInView(grid->GetMainGap());
    });
    scrollEffect->SetInitTrailingCallback([]() -> double { return 0.0; });
}

bool GridPattern::OutBoundaryCallback()
{
    return IsOutOfBoundary();
}

OverScrollOffset GridPattern::GetOverScrollOffset(double delta) const
{
    OverScrollOffset offset = { 0, 0 };
    if (gridLayoutInfo_.startIndex_ == 0) {
        auto startPos = gridLayoutInfo_.currentOffset_;
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
    if (gridLayoutInfo_.endIndex_ == gridLayoutInfo_.childrenCount_ - 1) {
        auto endPos = gridLayoutInfo_.currentOffset_ + gridLayoutInfo_.totalHeightOfItemsInView_;
        auto newEndPos = endPos + delta;
        if (endPos < gridLayoutInfo_.lastMainSize_ && newEndPos < gridLayoutInfo_.lastMainSize_) {
            offset.end = delta;
        }
        if (endPos < gridLayoutInfo_.lastMainSize_ && newEndPos >= gridLayoutInfo_.lastMainSize_) {
            offset.end = gridLayoutInfo_.lastMainSize_ - endPos;
        }
        if (endPos >= gridLayoutInfo_.lastMainSize_ && newEndPos < gridLayoutInfo_.lastMainSize_) {
            offset.end = newEndPos - gridLayoutInfo_.lastMainSize_;
        }
    }
    return offset;
}

void GridPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->IsScrollable()) {
            return;
        }
        pattern->ScrollPage(false);
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->IsScrollable()) {
            return;
        }
        pattern->ScrollPage(true);
    });
}

void GridPattern::DumpInfo()
{
    LOGI("reachStart:%{public}d,reachEnd:%{public}d,offsetEnd:%{public}d", gridLayoutInfo_.reachStart_,
        gridLayoutInfo_.reachEnd_, gridLayoutInfo_.offsetEnd_);
    auto property = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_VOID_NOLOG(property);
    LOGI("startIndex:%{public}d,endIndex:%{public}d,startMainLine:%{public}d,endMainLine:%{public}d,cachedCount:%{"
         "public}d",
        gridLayoutInfo_.startIndex_, gridLayoutInfo_.endIndex_, gridLayoutInfo_.startMainLineIndex_,
        gridLayoutInfo_.endMainLineIndex_, property->GetCachedCountValue(1));
}
} // namespace OHOS::Ace::NG
