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

#include "core/components_ng/pattern/grid/grid_pattern.h"

#include "base/log/dump_log.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/grid/grid_adaptive/grid_adaptive_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_paint_method.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

namespace OHOS::Ace::NG {

namespace {
const Color ITEM_FILL_COLOR = Color::TRANSPARENT;

const int32_t MAX_NUM_SIZE = 4;
} // namespace

RefPtr<LayoutAlgorithm> GridPattern::CreateLayoutAlgorithm()
{
    auto gridLayoutProperty = GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, nullptr);
    std::vector<std::string> cols;
    StringUtils::StringSplitter(gridLayoutProperty->GetColumnsTemplate().value_or(""), ' ', cols);
    std::vector<std::string> rows;
    StringUtils::StringSplitter(gridLayoutProperty->GetRowsTemplate().value_or(""), ' ', rows);

    // When rowsTemplate and columnsTemplate is both not setting, use adaptive layout algorithm.
    if (rows.empty() && cols.empty()) {
        return MakeRefPtr<GridAdaptiveLayoutAlgorithm>(info_);
    }

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

    // If only set one of rowTemplate and columnsTemplate, use scrollable layout algorithm.
    const bool disableSkip = IsOutOfBoundary(true) || (ScrollablePattern::AnimateRunning() && !IsBackToTopRunning());
    const bool canOverScrollStart = CanOverScrollStart(GetScrollSource()) || preSpring_;
    const bool canOverScrollEnd = CanOverScrollEnd(GetScrollSource()) || preSpring_;
    if (UseIrregularLayout()) {
        auto algo = MakeRefPtr<GridIrregularLayoutAlgorithm>(
            info_, canOverScrollStart, canOverScrollEnd && (info_.repeatDifference_ == 0));
        algo->SetEnableSkip(!disableSkip);
        algo->SetScrollSource(GetScrollSource());
        return algo;
    }
    RefPtr<GridScrollLayoutAlgorithm> result;
    if (!gridLayoutProperty->GetLayoutOptions().has_value()) {
        result = MakeRefPtr<GridScrollLayoutAlgorithm>(info_, crossCount, mainCount);
    } else {
        result = MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(info_, crossCount, mainCount);
    }
    result->SetCanOverScrollStart(canOverScrollStart);
    result->SetCanOverScrollEnd(canOverScrollEnd && (info_.repeatDifference_ == 0));
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
    info_.repeatDifference_ = 0;
    info_.firstRepeatCount_ = 0;
    info_.childrenCount_ = 0;
    GetRepeatCountInfo(host, info_.repeatDifference_, info_.firstRepeatCount_, info_.childrenCount_);
}

RefPtr<PaintProperty> GridPattern::CreatePaintProperty()
{
    auto defaultDisplayMode = GetDefaultScrollBarDisplayMode();
    auto property = MakeRefPtr<GridPaintProperty>();
    property->UpdateScrollBarMode(defaultDisplayMode);
    return property;
}

RefPtr<NodePaintMethod> GridPattern::CreateNodePaintMethod()
{
    auto paint = MakeRefPtr<GridPaintMethod>(GetAxis() == Axis::HORIZONTAL, IsReverse(), GetScrollBar());
    CHECK_NULL_RETURN(paint, nullptr);
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
#ifdef SUPPORT_DIGITAL_CROWN
        SetDigitalCrownEvent();
#endif
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
        auto itemEvent = itemFrameNode->GetOrCreateEventHub<EventHub>();
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
            iter->second.onSelected = itemPattern->GetOrCreateEventHub<GridItemEventHub>()->GetOnSelect();
            iter->second.selectChangeEvent =
                itemPattern->GetOrCreateEventHub<GridItemEventHub>()->GetSelectChangeEvent();
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

bool GridPattern::IsItemSelected(float offsetX, float offsetY)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto node = host->FindChildByPosition(offsetX, offsetY);
    CHECK_NULL_RETURN(node, false);
    auto itemPattern = node->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN(itemPattern, false);
    return itemPattern->IsSelected();
}

void GridPattern::FireOnScrollStart(bool withPerfMonitor)
{
    ScrollablePattern::RecordScrollEvent(Recorder::EventType::SCROLL_START);
    UIObserverHandler::GetInstance().NotifyScrollEventStateChange(
        AceType::WeakClaim(this), ScrollEventType::SCROLL_START);
    SuggestOpIncGroup(true);
    if (withPerfMonitor) {
        PerfMonitor::GetPerfMonitor()->StartCommercial(PerfConstants::APP_LIST_FLING, PerfActionType::FIRST_MOVE, "");
    }
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
    auto hub = host->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollStart = hub->GetOnScrollStart();
    if (onScrollStart) {
        onScrollStart();
    }
    auto onJSFrameNodeScrollStart = hub->GetJSFrameNodeOnScrollStart();
    if (onJSFrameNodeScrollStart) {
        onJSFrameNodeScrollStart();
    }
}

void GridPattern::FireOnReachStart(const OnReachEvent& onReachStart, const OnReachEvent& onJSFrameNodeReachStart)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (info_.startIndex_ != 0) {
        return;
    }
    if (!isInitialized_) {
        FireObserverOnReachStart();
        CHECK_NULL_VOID(onReachStart || onJSFrameNodeReachStart);
        if (onReachStart) {
            onReachStart();
        }
        if (onJSFrameNodeReachStart) {
            onJSFrameNodeReachStart();
        }
        AddEventsFiredInfo(ScrollableEventType::ON_REACH_START);
    }
    auto finalOffset = info_.currentHeight_ - info_.prevHeight_;
    if (!NearZero(finalOffset)) {
        bool scrollUpToStart = GreatOrEqual(info_.prevHeight_, 0.0) && LessOrEqual(info_.currentHeight_, 0.0);
        bool scrollDownToStart = LessNotEqual(info_.prevHeight_, 0.0) && GreatOrEqual(info_.currentHeight_, 0.0);
        if (scrollUpToStart || scrollDownToStart) {
            FireObserverOnReachStart();
            CHECK_NULL_VOID(onReachStart || onJSFrameNodeReachStart);
            ACE_SCOPED_TRACE("OnReachStart, scrollUpToStart:%u, scrollDownToStart:%u, id:%d, tag:Grid",
                scrollUpToStart, scrollDownToStart, static_cast<int32_t>(host->GetAccessibilityId()));
            if (onReachStart) {
                onReachStart();
            }
            if (onJSFrameNodeReachStart) {
                onJSFrameNodeReachStart();
            }
            AddEventsFiredInfo(ScrollableEventType::ON_REACH_START);
        }
    }
}

void GridPattern::FireOnReachEnd(const OnReachEvent& onReachEnd, const OnReachEvent& onJSFrameNodeReachEnd)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrenCount = info_.childrenCount_ + info_.repeatDifference_;
    if (info_.endIndex_ != (childrenCount - 1)) {
        return;
    }
    if (!isInitialized_) {
        FireObserverOnReachEnd();
    }
    auto finalOffset = info_.currentHeight_ - info_.prevHeight_;
    if (!NearZero(finalOffset)) {
        bool scrollDownToEnd =
            LessNotEqual(info_.prevHeight_, info_.endHeight_) && GreatOrEqual(info_.currentHeight_, info_.endHeight_);
        bool scrollUpToEnd =
            GreatNotEqual(info_.prevHeight_, info_.endHeight_) && LessOrEqual(info_.currentHeight_, info_.endHeight_);
        if (scrollDownToEnd || scrollUpToEnd) {
            FireObserverOnReachEnd();
            CHECK_NULL_VOID(onReachEnd || onJSFrameNodeReachEnd);
            ACE_SCOPED_TRACE("OnReachEnd, scrollUpToEnd:%u, scrollDownToEnd:%u, id:%d, tag:Grid", scrollUpToEnd,
                scrollDownToEnd, static_cast<int32_t>(host->GetAccessibilityId()));
            if (onReachEnd) {
                onReachEnd();
            }
            if (onJSFrameNodeReachEnd) {
                onJSFrameNodeReachEnd();
            }
            AddEventsFiredInfo(ScrollableEventType::ON_REACH_END);
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
    if (info_.startIndex_ == 0 && (info_.endIndex_ == info_.childrenCount_ - 1) &&
        LessNotEqual(info_.totalHeightOfItemsInView_, mainSize)) {
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
            if (GetTotalHeight() <= GetMainContentSize()) {
                overScroll = GetTotalOffset();
            } else if (irregular) {
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
    ScrollablePattern::MarkScrollBarProxyDirty();
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
    auto eventhub = GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_RETURN(eventhub, false);
    Dimension offset(0, DimensionUnit::VP);
    Dimension offsetPx(gridLayoutInfo.currentOffset_, DimensionUnit::PX);
    auto offsetVpValue = offsetPx.ConvertToVp();
    offset.SetValue(offsetVpValue);
    scrollbarInfo_ = eventhub->FireOnScrollBarUpdate(gridLayoutInfo.startIndex_, offset);
    if (!isInitialized_ || info_.startIndex_ != gridLayoutInfo.startIndex_) {
        eventhub->FireOnScrollToIndex(gridLayoutInfo.startIndex_);
    }

    bool indexChanged =
        (gridLayoutInfo.startIndex_ != info_.startIndex_) || (gridLayoutInfo.endIndex_ != info_.endIndex_);
    bool offsetEnd = info_.offsetEnd_;
    info_ = gridLayoutInfo;
    info_.synced_ = true;
    AnimateToTarget(scrollAlign_, layoutAlgorithmWrapper);

    info_.reachStart_ = info_.startIndex_ == 0 && GreatOrEqual(info_.currentOffset_, 0.0f);

    auto curDelta = info_.currentOffset_ - info_.prevOffset_;
    info_.currentHeight_ = EstimateHeight();
    bool sizeDiminished =
        IsOutOfBoundary(true) && !NearZero(curDelta) && (info_.prevHeight_ - info_.currentHeight_ - curDelta > 0.1f);

    if (!offsetEnd && info_.offsetEnd_) {
        bool irregular = UseIrregularLayout();
        float mainGap = GetMainGap();
        auto itemsHeight = info_.GetTotalHeightOfItemsInView(mainGap, irregular);
        auto overScroll = info_.currentOffset_ - (GetMainContentSize() - itemsHeight);
        info_.endHeight_ = info_.currentHeight_ - overScroll;
    }
    ProcessEvent(indexChanged, info_.currentHeight_ - info_.prevHeight_);
    info_.prevHeight_ = info_.currentHeight_;
    info_.extraOffset_.reset();
    UpdateScrollBarOffset();
    SetScrollSource(SCROLL_FROM_NONE);
    if (config.frameSizeChange) {
        if (GetScrollBar() != nullptr) {
            GetScrollBar()->ScheduleDisappearDelayTask();
        }
    }
    if (!preSpring_) {
        CheckRestartSpring(sizeDiminished);
    }
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
    auto gridEventHub = host->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(gridEventHub);
    ACE_SCOPED_TRACE("processed offset:%f, id:%d, tag:%s", finalOffset,
        static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
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
    auto onJSFrameNodeDidScroll = gridEventHub->GetJSFrameNodeOnDidScroll();
    if (onJSFrameNodeDidScroll) {
        FireOnScroll(finalOffset, onJSFrameNodeDidScroll);
    }
    auto onScrollIndex = gridEventHub->GetOnScrollIndex();
    auto onJsFrameNodeScrollIndex = gridEventHub->GetJSFrameNodeOnGridScrollIndex();
    FireOnScrollIndex(indexChanged, onScrollIndex);
    FireOnScrollIndex(indexChanged, onJsFrameNodeScrollIndex);
    if (indexChanged) {
        host->OnAccessibilityEvent(AccessibilityEventType::SCROLLING_EVENT, info_.startIndex_, info_.endIndex_);
    }
    auto onReachStart = gridEventHub->GetOnReachStart();
    auto onJSFrameNodeReachStart = gridEventHub->GetJSFrameNodeOnReachStart();
    FireOnReachStart(onReachStart, onJSFrameNodeReachStart);
    auto onReachEnd = gridEventHub->GetOnReachEnd();
    auto onJSFrameNodeReachEnd = gridEventHub->GetJSFrameNodeOnReachEnd();
    FireOnReachEnd(onReachEnd, onJSFrameNodeReachEnd);
    auto onScrollStop = gridEventHub->GetOnScrollStop();
    auto onJSFrameNodeScrollStop = gridEventHub->GetJSFrameNodeOnScrollStop();
    OnScrollStop(onScrollStop, onJSFrameNodeScrollStop);
    if (isSmoothScrolling_ && scrollStop_) {
        isSmoothScrolling_ = false;
    }
    CHECK_NULL_VOID(isConfigScrollable_);
    focusHandler_.ProcessFocusEvent(keyEvent_, indexChanged);
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

int32_t GridPattern::GetFocusNodeIndex(const RefPtr<FocusHub>& focusNode)
{
    return focusHandler_.GetFocusNodeIndex(focusNode);
}

void GridPattern::ScrollToFocusNodeIndex(int32_t index)
{
    StopAnimate();
    UpdateStartIndex(index);
    auto pipeline = GetContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
    auto tarFocusNodeWeak = focusHandler_.GetChildFocusNodeByIndex(-1, -1, index);
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
    auto scrollToIndex = focusHandler_.GetFocusNodeIndex(focusHub);
    if (scrollToIndex < 0) {
        return false;
    }
    StopAnimate();
    auto ret = UpdateStartIndex(scrollToIndex);
    auto* pipeline = GetContext();
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
        if (focusHandler_.ScrollToLastFocusIndex(event.code)) {
            keyEvent_ = event;
            return true;
        }
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
        return infoPtr->GetTotalHeightFromZeroIndex(info_.startMainLineIndex_, GetMainGap()) - info_.currentOffset_;
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
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    auto viewScopeSize = geometryNode->GetPaddingSize();
    auto props = host->GetLayoutProperty<GridLayoutProperty>();
    auto mainGap = GridUtils::GetMainGap(props, viewScopeSize, info_.axis_);
    if (UseIrregularLayout()) {
        return info_.GetIrregularHeight(mainGap);
    }
    if (props->HasLayoutOptions()) {
        return info_.GetContentHeight(*props->GetLayoutOptions(), info_.childrenCount_, mainGap);
    }
    return info_.GetContentHeight(mainGap);
}

void GridPattern::UpdateScrollBarOffset()
{
    CheckScrollBarOff();
    CHECK_NULL_VOID((GetScrollBar() || GetScrollBarProxy()) && isConfigScrollable_);
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
            auto childrenCount = info_.childrenCount_ + info_.repeatDifference_;
            offset = info.GetContentOffset(layoutProperty->GetLayoutOptions().value(), mainGap);
            estimatedHeight = info.GetContentHeight(layoutProperty->GetLayoutOptions().value(), childrenCount, mainGap);
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
    if (info_.offsetEnd_ && NearZero(overScroll) && info_.repeatDifference_ == 0) {
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
    return info_.GetChildrenCount();
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
    if (insertIndex < 0 || insertIndex >= ((itemIndex == -1) ? (info_.childrenCount_ + 1) : info_.childrenCount_)) {
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
    return scrollable && (info_.IsOutOfStart() || info_.IsOutOfEnd(GetMainGap(), UseIrregularLayout()));
}

float GridPattern::GetEndOffset()
{
    auto& info = info_;
    float contentHeight = info.lastMainSize_ - info.contentEndPadding_;
    const float mainGap = GetMainGap();
    const bool irregular = UseIrregularLayout();
    float heightInView = info.GetTotalHeightOfItemsInView(mainGap, irregular);

    const float totalHeight = GetTotalHeight();
    if (GetAlwaysEnabled() && LessNotEqual(totalHeight, contentHeight)) {
        // overScroll with contentHeight < viewport
        if (irregular) {
            return info.GetHeightInRange(0, info.startMainLineIndex_, mainGap);
        }
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

    preSpring_ = true;
    host->SetActive();
    auto* context = host->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(host);
    }
    preSpring_ = false;
}

void GridPattern::GetEndOverScrollIrregular(OverScrollOffset& offset, float delta) const
{
    const float mainGap = GetMainGap();
    const float viewport = info_.lastMainSize_ - info_.contentEndPadding_;
    float heightInView = info_.totalHeightOfItemsInView_;
    if (info_.HeightSumSmaller(viewport, mainGap)) {
        // content < viewport, use viewport height to calculate overScroll
        heightInView = viewport - info_.GetHeightInRange(0, info_.startMainLineIndex_, mainGap);
    }
    float disToBot = info_.GetDistanceToBottom(viewport, heightInView, mainGap);
    if (!info_.IsOutOfEnd(mainGap, true)) {
        offset.end = std::min(0.0f, disToBot + delta);
    } else if (Negative(delta)) {
        offset.end = delta;
    } else {
        offset.end = std::min(delta, -disToBot);
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
        if (info_.repeatDifference_ == 0) {
            GetEndOverScrollIrregular(offset, static_cast<float>(delta));
        }
        return offset;
    }
    if (info_.endIndex_ == (info_.childrenCount_ + info_.repeatDifference_ - 1)) {
        float endPos = info_.currentOffset_ + info_.totalHeightOfItemsInView_;
        float mainSize = info_.lastMainSize_ - info_.contentEndPadding_;
        if (GreatNotEqual(GetMainContentSize(), info_.currentOffset_ + info_.totalHeightOfItemsInView_)) {
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
    info_.synced_ ? DumpLog::GetInstance().AddDesc("synced:true") : DumpLog::GetInstance().AddDesc("synced:false");
    DumpLog::GetInstance().AddDesc("scrollStop:" + std::to_string(scrollStop_));
    DumpLog::GetInstance().AddDesc("prevHeight:" + std::to_string(info_.prevHeight_));
    DumpLog::GetInstance().AddDesc("currentHeight:" + std::to_string(info_.currentHeight_));
    DumpLog::GetInstance().AddDesc("endHeight:" + std::to_string(info_.endHeight_));
    DumpLog::GetInstance().AddDesc("currentOffset:" + std::to_string(info_.currentOffset_));
    DumpLog::GetInstance().AddDesc("prevOffset:" + std::to_string(info_.prevOffset_));
    DumpLog::GetInstance().AddDesc("lastMainSize:" + std::to_string(info_.lastMainSize_));
    DumpLog::GetInstance().AddDesc("totalHeightOfItemsInView:" + std::to_string(info_.totalHeightOfItemsInView_));
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

void GridPattern::GetEventDumpInfo()
{
    ScrollablePattern::GetEventDumpInfo();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollIndex = hub->GetOnScrollIndex();
    onScrollIndex ? DumpLog::GetInstance().AddDesc("hasOnScrollIndex: true")
                  : DumpLog::GetInstance().AddDesc("hasOnScrollIndex: false");
    auto onJSFrameNodeScrollIndex = hub->GetJSFrameNodeOnGridScrollIndex();
    onJSFrameNodeScrollIndex ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollIndex: true")
                             : DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollIndex: false");
}

void GridPattern::GetEventDumpInfo(std::unique_ptr<JsonValue>& json)
{
    ScrollablePattern::GetEventDumpInfo(json);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollIndex = hub->GetOnScrollIndex();
    json->Put("hasOnScrollIndex", onScrollIndex ? "true" : "false");
    auto onJSFrameNodeScrollIndex = hub->GetJSFrameNodeOnGridScrollIndex();
    json->Put("hasFrameNodeOnScrollIndex", onJSFrameNodeScrollIndex ? "true" : "false");
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
        if (rect.IsInRegion({ x, y })) {
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
        success = infoCopy_ && infoCopy_->GetGridItemAnimatePos(info_, *targetIndex_, align, mainGap, targetPos);
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
    if (NearEqual(targetPos, GetTotalOffset())) {
        isSmoothScrolling_ = false;
        return false;
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

bool GridPattern::IsPredictOutOfCacheRange(int32_t index) const
{
    CHECK_NULL_RETURN(index < info_.GetChildrenCount(), true);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto gridLayoutProperty = host->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, true);
    auto cacheCount = gridLayoutProperty->GetCachedCountValue(info_.defCachedCount_) * info_.crossCount_;
    return index < info_.startIndex_ - cacheCount || index > info_.endIndex_ + cacheCount ||
           (index >= info_.startIndex_ && index <= info_.endIndex_);
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
    json->Put("lastCrossCount",
        info_.lastCrossCount_.has_value() ? std::to_string(info_.lastCrossCount_.value()).c_str() : "null");
    json->Put("reachEnd", info_.reachEnd_);
    json->Put("reachStart", info_.reachStart_);
    json->Put("offsetEnd", info_.offsetEnd_);
    json->Put("hasBigItem", info_.hasBigItem_);
    json->Put("synced", info_.synced_);
    json->Put("scrollStop", std::to_string(scrollStop_).c_str());
    json->Put("prevHeight", info_.prevHeight_);
    json->Put("currentHeight", info_.currentHeight_);
    json->Put("endHeight", info_.endHeight_);
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
    json->Put("ShowCache", std::to_string(property->GetShowCachedItemsValue(false)).c_str());
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

ScopeFocusAlgorithm GridPattern::GetScopeFocusAlgorithm()
{
    auto property = GetLayoutProperty<GridLayoutProperty>();
    if (!property) {
        return ScopeFocusAlgorithm();
    }
    return ScopeFocusAlgorithm(property->IsVertical(), true, ScopeType::OTHERS,
        [wp = WeakClaim(this)](
            FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) -> bool {
            auto grid = wp.Upgrade();
            CHECK_NULL_RETURN(grid, false);
            if (grid->UseIrregularLayout() && (step == FocusStep::TAB || step == FocusStep::SHIFT_TAB)) {
                nextFocusNode = grid->focusHandler_.GetNextFocusSimplified(step, currFocusNode.Upgrade());
            } else {
                nextFocusNode = grid->focusHandler_.GetNextFocusNode(step, currFocusNode);
            }
            return nextFocusNode.Upgrade() != currFocusNode.Upgrade();
        });
}

void GridPattern::HandleOnItemFocus(int32_t index)
{
    focusHandler_.SetFocusIndex(index);
}
} // namespace OHOS::Ace::NG
