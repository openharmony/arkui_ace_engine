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

#include "core/components_ng/pattern/list/list_pattern.h"

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/animation/bilateral_spring_node.h"
#include "core/animation/spring_model.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension CHAIN_INTERVAL_DEFAULT = 20.0_vp;
constexpr double CHAIN_SPRING_MASS = 1.0;
constexpr double CHAIN_SPRING_DAMPING = 30.0;
constexpr double CHAIN_SPRING_STIFFNESS = 228;
constexpr Color SELECT_FILL_COLOR = Color(0x1A000000);
constexpr Color SELECT_STROKE_COLOR = Color(0x33FFFFFF);
constexpr Color ITEM_FILL_COLOR = Color(0x1A0A59f7);
} // namespace

void ListPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
}

void ListPattern::OnModifyDone()
{
    if (!isInitialized_) {
        jumpIndex_ = GetLayoutProperty<ListLayoutProperty>()->GetInitialIndex().value_or(0);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    SetAxis(axis);
    if (!GetScrollableEvent()) {
        InitScrollableEvent();
    }

    SetEdgeEffect(listLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING));
    auto listPaintProperty = host->GetPaintProperty<ListPaintProperty>();
    SetScrollBar(listPaintProperty->GetBarDisplayMode().value_or(DisplayMode::OFF));
    SetChainAnimation(listLayoutProperty->GetChainAnimation().value_or(false));
    if (multiSelectable_ && !isMouseEventInit_) {
        InitMouseEvent();
    }
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID_NOLOG(focusHub);
    InitOnKeyEvent(focusHub);
}

bool ListPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    bool isJump = false;
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto listLayoutAlgorithm = DynamicCast<ListLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(listLayoutAlgorithm, false);
    itemPosition_ = listLayoutAlgorithm->GetItemPosition();
    maxListItemIndex_ = listLayoutAlgorithm->GetMaxListItemIndex();
    if (jumpIndex_) {
        estimateOffset_ = listLayoutAlgorithm->GetEstimateOffset();
        if (!itemPosition_.empty()) {
            currentOffset_ = itemPosition_.begin()->second.startPos;
        }
        isJump = true;
        jumpIndex_.reset();
    }
    auto finalOffset = listLayoutAlgorithm->GetCurrentOffset();
    spaceWidth_ = listLayoutAlgorithm->GetSpaceWidth();
    lastOffset_ = currentOffset_;
    currentOffset_ = currentOffset_ - finalOffset;
    currentDelta_ = 0.0f;
    float prevStartOffset = startMainPos_;
    float prevEndOffset = endMainPos_ - contentMainSize_;
    contentMainSize_ = listLayoutAlgorithm->GetContentMainSize();
    startMainPos_ = listLayoutAlgorithm->GetStartPosition();
    endMainPos_ = listLayoutAlgorithm->GetEndPosition();
    crossMatchChild_ = listLayoutAlgorithm->IsCrossMatchChild();
    itemGroupList_.swap(listLayoutAlgorithm->GetItemGroupList());
    auto lanesLayoutAlgorithm = DynamicCast<ListLanesLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    if (lanesLayoutAlgorithm) {
        lanesLayoutAlgorithm->SwapLanesItemRange(lanesItemRange_);
        lanes_ = lanesLayoutAlgorithm->GetLanes();
    }
    CheckScrollable();

    bool indexChanged =
        (startIndex_ != listLayoutAlgorithm->GetStartIndex()) || (endIndex_ != listLayoutAlgorithm->GetEndIndex());
    startIndex_ = listLayoutAlgorithm->GetStartIndex();
    endIndex_ = listLayoutAlgorithm->GetEndIndex();
    ProcessEvent(indexChanged, finalOffset, isJump, prevStartOffset, prevEndOffset);
    UpdateScrollBarOffset();
    CheckRestartSpring();

    DrivenRender(dirty);

    isInitialized_ = true;
    return true;
}

void ListPattern::ProcessEvent(
    bool indexChanged, float finalOffset, bool isJump, float prevStartOffset, float prevEndOffset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listEventHub = host->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(listEventHub);

    paintStateFlag_ = !NearZero(finalOffset) && !isJump;
    isFramePaintStateValid_ = true;

    auto onScroll = listEventHub->GetOnScroll();
    if (onScroll && !NearZero(finalOffset) && !isJump) {
        auto source = GetScrollState();
        auto offsetPX = Dimension(finalOffset);
        auto offsetVP = Dimension(offsetPX.ConvertToVp(), DimensionUnit::VP);
        if (source == SCROLL_FROM_UPDATE) {
            onScroll(offsetVP, ScrollState::SCROLL);
        } else if (source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING) {
            onScroll(offsetVP, ScrollState::FLING);
        } else {
            onScroll(offsetVP, ScrollState::IDLE);
        }
    }

    if (indexChanged) {
        auto onScrollIndex = listEventHub->GetOnScrollIndex();
        if (onScrollIndex) {
            onScrollIndex(startIndex_, endIndex_);
        }
    }

    auto onReachStart = listEventHub->GetOnReachStart();
    if (onReachStart && (startIndex_ == 0)) {
        bool scrollUpToStart = Positive(prevStartOffset) && NonPositive(startMainPos_);
        bool scrollDownToStart = (Negative(prevStartOffset) || !isInitialized_) && NonNegative(startMainPos_);
        if (scrollUpToStart || scrollDownToStart) {
            onReachStart();
        }
    }
    auto onReachEnd = listEventHub->GetOnReachEnd();
    if (onReachEnd && (endIndex_ == maxListItemIndex_)) {
        float endOffset = endMainPos_ - contentMainSize_;
        bool scrollUpToEnd = (Positive(prevEndOffset) || !isInitialized_) && NonPositive(endOffset);
        bool scrollDownToEnd = Negative(prevEndOffset) && NonNegative(endOffset);
        if (scrollUpToEnd || scrollDownToEnd) {
            onReachEnd();
        }
    }

    if (scrollStop_) {
        auto onScrollStop = listEventHub->GetOnScrollStop();
        if (!scrollAbort_ && onScrollStop) {
            onScrollStop();
        }
        scrollStop_ = false;
        scrollAbort_ = false;
    }
}

void ListPattern::DrivenRender(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    auto listPaintProperty = host->GetPaintProperty<ListPaintProperty>();
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto stickyStyle = listLayoutProperty->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    auto barDisplayMode = listPaintProperty->GetBarDisplayMode().value_or(DisplayMode::OFF);
    auto chainAnimation = listLayoutProperty->GetChainAnimation().value_or(false);
    bool drivenRender = !(axis != Axis::VERTICAL || barDisplayMode != DisplayMode::OFF ||
        stickyStyle != V2::StickyStyle::NONE || chainAnimation || !scrollable_);

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->MarkDrivenRender(drivenRender);
    if (drivenRender && isFramePaintStateValid_) {
        // Mark items
        int32_t indexStep = 0;
        int32_t startIndex = itemPosition_.empty() ? 0 : itemPosition_.begin()->first;
        for (auto& pos : itemPosition_) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos.first);
            CHECK_NULL_VOID(wrapper);
            auto itemHost = wrapper->GetHostNode();
            CHECK_NULL_VOID(itemHost);
            auto itemRenderContext = itemHost->GetRenderContext();
            CHECK_NULL_VOID(itemRenderContext);
            itemRenderContext->MarkDrivenRenderItemIndex(startIndex + indexStep);
            indexStep++;
        }
        renderContext->MarkDrivenRenderFramePaintState(paintStateFlag_);
        isFramePaintStateValid_ = false;
    }
}

void ListPattern::CheckScrollable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    if (itemPosition_.empty()) {
        scrollable_ = false;
    } else {
        if ((itemPosition_.begin()->first == 0) && (itemPosition_.rbegin()->first == maxListItemIndex_)) {
            scrollable_ = GreatNotEqual((endMainPos_ - startMainPos_), GetMainContentSize());
        } else {
            scrollable_ = true;
        }
    }

    SetScrollEnable(scrollable_);
}

RefPtr<LayoutAlgorithm> ListPattern::CreateLayoutAlgorithm()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm;
    if (listLayoutProperty->HasLanes() || listLayoutProperty->HasLaneMinLength() ||
        listLayoutProperty->HasLaneMaxLength()) {
        auto lanesLayoutAlgorithm = MakeRefPtr<ListLanesLayoutAlgorithm>();
        if ((listLayoutProperty->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT) == 0) {
            lanesLayoutAlgorithm->SwapLanesItemRange(lanesItemRange_);
        }
        lanesLayoutAlgorithm->SetLanes(lanes_);
        listLayoutAlgorithm.Swap(lanesLayoutAlgorithm);
    } else {
        listLayoutAlgorithm.Swap(MakeRefPtr<ListLayoutAlgorithm>());
    }
    if (jumpIndex_) {
        listLayoutAlgorithm->SetIndex(jumpIndex_.value());
        listLayoutAlgorithm->SetIndexAlignment(scrollIndexAlignment_);
    }
    listLayoutAlgorithm->SetCurrentDelta(currentDelta_);
    listLayoutAlgorithm->SetItemsPosition(itemPosition_);
    listLayoutAlgorithm->SetPrevContentMainSize(contentMainSize_);
    if (IsOutOfBoundary(false)) {
        listLayoutAlgorithm->SetOverScrollFeature();
    }
    auto effect = listLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
    bool canOverScroll = (effect == EdgeEffect::SPRING) && !ScrollableIdle() && scrollState_ != SCROLL_FROM_BAR;
    listLayoutAlgorithm->SetCanOverScroll(canOverScroll);
    if (chainAnimation_) {
        listLayoutAlgorithm->SetChainOffsetCallback([weak = AceType::WeakClaim(this)](int32_t index) {
            auto list = weak.Upgrade();
            CHECK_NULL_RETURN(list, 0.0f);
            return list->GetChainDelta(index);
        });
        if (!listLayoutProperty->GetSpace().has_value() && chainAnimation_) {
            listLayoutAlgorithm->SetChainInterval(CHAIN_INTERVAL_DEFAULT.ConvertToPx());
        }
    }
    return listLayoutAlgorithm;
}

bool ListPattern::IsAtTop() const
{
    return (startIndex_ == 0) && NonNegative(startMainPos_ + GetChainDelta(0));
}

bool ListPattern::IsAtBottom() const
{
    return endIndex_ == maxListItemIndex_ && LessOrEqual(endMainPos_ + GetChainDelta(endIndex_), GetMainContentSize());
}

bool ListPattern::OutBoundaryCallback()
{
    bool outBoundary = IsAtTop() || IsAtBottom();
    if (!dragFromSpring_ && outBoundary && chainAnimation_) {
        chainAnimation_->SetOverDrag(false);
        auto delta = chainAnimation_->SetControlIndex(IsAtTop() ? 0 : maxListItemIndex_);
        currentDelta_ -= delta;
        dragFromSpring_ = true;
    }
    return outBoundary;
}

bool ListPattern::UpdateCurrentOffset(float offset, int32_t source)
{
    SetScrollState(source);
    // check edgeEffect is not springEffect
    if (!HandleEdgeEffect(offset, source, GetContentSize())) {
        return false;
    }
    currentDelta_ = currentDelta_ - offset;
    MarkDirtyNodeSelf();
    if (!IsOutOfBoundary() || !scrollable_) {
        return true;
    }

    // over scroll in drag update from normal to over scroll.
    float overScroll = 0.0f;
    // over scroll in drag update during over scroll.
    auto startPos = startMainPos_ - currentDelta_;
    if ((itemPosition_.begin()->first == 0) && Positive(startPos)) {
        overScroll = startPos;
    } else {
        overScroll = GetMainContentSize() - (endMainPos_ - currentDelta_);
    }

    if (scrollState_ == SCROLL_FROM_UPDATE) {
        // adjust offset.
        auto friction = CalculateFriction(std::abs(overScroll) / GetMainContentSize());
        currentDelta_ = currentDelta_ * friction;
    }
    return true;
}

void ListPattern::MarkDirtyNodeSelf()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!crossMatchChild_) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
    for (const auto& weak : itemGroupList_) {
        auto itemGroup = weak.Upgrade();
        if (!itemGroup) {
            continue;
        }
        auto layoutProperty = itemGroup->GetLayoutProperty();
        if (layoutProperty) {
            layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }
}

void ListPattern::OnScrollEndCallback()
{
    scrollStop_ = true;
    MarkDirtyNodeSelf();
}

float ListPattern::GetMainContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetPaddingSize().MainSize(GetAxis());
}

SizeF ListPattern::GetContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    return geometryNode->GetPaddingSize();
}

bool ListPattern::IsOutOfBoundary(bool useCurrentDelta)
{
    if (itemPosition_.empty()) {
        return false;
    }
    auto startPos = useCurrentDelta ? startMainPos_ - currentDelta_ : startMainPos_;
    auto endPos = useCurrentDelta ? endMainPos_ - currentDelta_ : endMainPos_;
    auto mainSize = GetMainContentSize();
    if (startIndex_ == 0) {
        startPos += GetChainDelta(0);
    }
    if (endIndex_ == maxListItemIndex_) {
        endPos += GetChainDelta(endIndex_);
    }
    bool outOfStart = (startIndex_ == 0) && Positive(startPos) && GreatNotEqual(endPos, mainSize);
    bool outOfEnd = (endIndex_ == maxListItemIndex_) && LessNotEqual(endPos, mainSize) && Negative(startPos);
    return outOfStart || outOfEnd;
}

void ListPattern::FireOnScrollStart()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID_NOLOG(hub);
    auto onScrollStart = hub->GetOnScrollStart();
    CHECK_NULL_VOID_NOLOG(onScrollStart);
    onScrollStart();
}

void ListPattern::FireOnScrollStop()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollStop = hub->GetOnScrollStop();
    CHECK_NULL_VOID_NOLOG(onScrollStop);
    onScrollStop();
}

bool ListPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        ProcessDragStart(offset);
        auto item = swiperItem_.Upgrade();
        if (item) {
            item->SwiperReset();
        }
        if (animator_ && !animator_->IsStopped()) {
            FireOnScrollStop();
            scrollAbort_ = true;
            animator_->Stop();
        }
        FireOnScrollStart();
        return true;
    }
    auto scrollBar = GetScrollBar();
    if (scrollBar && scrollBar->IsDriving()) {
        offset = scrollBar->CalcPatternOffset(offset);
        source = SCROLL_FROM_BAR;
    } else {
        ProcessDragUpdate(offset, source);
    }
    return UpdateCurrentOffset(offset, source);
}

void ListPattern::InitScrollableEvent()
{
    AddScrollEvent();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listEventHub = host->GetEventHub<ListEventHub>();
    auto onScrollBegin = listEventHub->GetOnScrollBegin();
    auto onScrollFrameBegin = listEventHub->GetOnScrollFrameBegin();
    auto scrollableEvent = GetScrollableEvent();
    CHECK_NULL_VOID(scrollableEvent);
    if (onScrollBegin) {
        scrollableEvent->SetScrollBeginCallback(std::move(onScrollBegin));
    }
    if (onScrollFrameBegin) {
        scrollableEvent->SetScrollFrameBeginCallback(std::move(onScrollFrameBegin));
    }
}

void ListPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(list, 0.0);
        return list->startMainPos_ + list->GetChainDelta(list->startIndex_) - list->currentDelta_;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        auto endPos = list->endMainPos_ + list->GetChainDelta(list->endIndex_);
        auto startPos = list->startMainPos_ + list->GetChainDelta(list->startIndex_);
        return list->GetMainContentSize() - (endPos - startPos);
    });
    scrollEffect->SetTrailingCallback([]() -> double { return 0.0; });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        auto endPos = list->endMainPos_ + list->GetChainDelta(list->endIndex_);
        auto startPos = list->startMainPos_ + list->GetChainDelta(list->startIndex_);
        return list->GetMainContentSize() - (endPos - startPos);
    });
    scrollEffect->SetInitTrailingCallback([]() -> double { return 0.0; });
}

void ListPattern::CheckRestartSpring()
{
    if (!ScrollableIdle() || !IsOutOfBoundary()) {
        return;
    }
    auto edgeEffect = GetScrollEdgeEffect();
    if (!edgeEffect || !edgeEffect->IsSpringEffect()) {
        return;
    }
    FireOnScrollStart();
    edgeEffect->ProcessScrollOver(0);
}

void ListPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool ListPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_PAGE_DOWN) {
        LOGD("Keycode is PgDn. Scroll to next page");
        ScrollPage(false);
        return true;
    }
    if (event.code == KeyCode::KEY_PAGE_UP) {
        LOGD("Keycode is PgDn. Scroll to next page");
        ScrollPage(true);
        return true;
    }
    if (event.IsDirectionalKey()) {
        return HandleDirectionKey(event.code);
    }
    return false;
}

bool ListPattern::HandleDirectionKey(KeyCode code)
{
    if ((GetAxis() == Axis::VERTICAL && code == KeyCode::KEY_DPAD_UP) ||
        (GetAxis() == Axis::HORIZONTAL && code == KeyCode::KEY_DPAD_LEFT)) {
        auto nextIndex = std::clamp(scrollIndex_ - 1, 0, maxListItemIndex_);
        if (nextIndex == scrollIndex_) {
            return false;
        }
        scrollIndex_ = nextIndex;
        LOGD("Scroll to next index: %{public}d", scrollIndex_);
        // Need to update: current selection
        ScrollToIndex(scrollIndex_, ScrollIndexAlignment::ALIGN_TOP);
        return false;
    }
    if ((GetAxis() == Axis::VERTICAL && code == KeyCode::KEY_DPAD_DOWN) ||
        (GetAxis() == Axis::HORIZONTAL && code == KeyCode::KEY_DPAD_RIGHT)) {
        auto nextIndex = std::clamp(scrollIndex_ + 1, 0, maxListItemIndex_);
        if (nextIndex == scrollIndex_) {
            return false;
        }
        scrollIndex_ = nextIndex;
        LOGD("Scroll to previous index: %{public}d", scrollIndex_);
        // Need to update: current selection
        ScrollToIndex(scrollIndex_, ScrollIndexAlignment::ALIGN_BUTTON);
        return false;
    }
    return false;
}

void ListPattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve)
{
    LOGI("AnimateTo:%f, duration:%f", position, duration);
    if (!IsScrollableStopped()) {
        scrollAbort_ = true;
        StopScrollable();
    }
    if (!animator_) {
        animator_ = AceType::MakeRefPtr<Animator>(PipelineBase::GetCurrentContext());
    }
    if (!animator_->IsStopped()) {
        scrollAbort_ = true;
        animator_->Stop();
    }
    if (scrollAbort_) {
        FireOnScrollStop();
    }
    animator_->ClearInterpolators();

    auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(GetTotalOffset(), position, curve);
    animation->AddListener([weakScroll = AceType::WeakClaim(this)](float value) {
        auto list = weakScroll.Upgrade();
        CHECK_NULL_VOID_NOLOG(list);
        list->SetScrollState(SCROLL_FROM_JUMP);
        list->UpdateCurrentOffset(list->GetTotalOffset() - value, SCROLL_FROM_JUMP);
    });
    animator_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto list = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(list);
        list->scrollStop_ = true;
    });
    animator_->AddInterpolator(animation);
    animator_->SetDuration(static_cast<int32_t>(duration));
    animator_->Play();
    FireOnScrollStart();
}

void ListPattern::StopAnimate()
{
    if (!IsScrollableStopped()) {
        StopScrollable();
    }
    if (animator_ && !animator_->IsStopped()) {
        animator_->Stop();
    }
}

void ListPattern::ScrollTo(float position)
{
    LOGI("ScrollTo:%{public}f", position);
    StopAnimate();
    SetScrollState(SCROLL_FROM_JUMP);
    UpdateCurrentOffset(GetTotalOffset() - position, SCROLL_FROM_JUMP);
}

void ListPattern::ScrollToIndex(int32_t index, ScrollIndexAlignment align)
{
    LOGI("ScrollToIndex:%{public}d", index);
    StopAnimate();
    if (index >= 0 || index == ListLayoutAlgorithm::LAST_ITEM) {
        jumpIndex_ = index;
        scrollIndexAlignment_ = align;
        MarkDirtyNodeSelf();
    }
}

void ListPattern::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    LOGI("ScrollToEdge:%{public}zu", scrollEdgeType);
    if (scrollEdgeType == ScrollEdgeType::SCROLL_TOP) {
        ScrollToIndex(0, ScrollIndexAlignment::ALIGN_TOP);
    } else if (scrollEdgeType == ScrollEdgeType::SCROLL_BOTTOM) {
        ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, ScrollIndexAlignment::ALIGN_BUTTON);
    }
}

bool ListPattern::ScrollPage(bool reverse)
{
    LOGI("ScrollPage:%{public}d", reverse);
    StopAnimate();
    float distance = reverse ? GetMainContentSize() : -GetMainContentSize();
    SetScrollState(SCROLL_FROM_JUMP);
    UpdateCurrentOffset(distance, SCROLL_FROM_JUMP);
    return true;
}

void ListPattern::ScrollBy(float offset)
{
    StopAnimate();
    SetScrollState(SCROLL_FROM_JUMP);
    UpdateCurrentOffset(-offset, SCROLL_FROM_JUMP);
}

Offset ListPattern::GetCurrentOffset() const
{
    if (GetAxis() == Axis::HORIZONTAL) {
        return {GetTotalOffset(), 0.0};
    }
    return {0.0, GetTotalOffset()};
}

void ListPattern::UpdateScrollBarOffset()
{
    if (itemPosition_.empty()) {
        return;
    }
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    SizeF ContentSize = GetContentSize();
    Size size(ContentSize.Width(), ContentSize.Height());
    float itemsSize = itemPosition_.rbegin()->second.endPos - itemPosition_.begin()->second.startPos + spaceWidth_;
    float currentOffset = itemsSize / itemPosition_.size() * itemPosition_.begin()->first - startMainPos_;
    Offset scrollOffset = { currentOffset, currentOffset }; // fit for w/h switched.
    auto estimatedHeight = itemsSize / itemPosition_.size() * (maxListItemIndex_ + 1);

    UpdateScrollBarRegion(currentOffset, estimatedHeight, size);
}

void ListPattern::SetChainAnimation(bool enable)
{
    if (!enable) {
        chainAnimation_.Reset();
        return;
    }
    if (!chainAnimation_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
        CHECK_NULL_VOID(listLayoutProperty);
        auto space = listLayoutProperty->GetSpace().value_or(CHAIN_INTERVAL_DEFAULT).ConvertToPx();
        springProperty_ =
            AceType::MakeRefPtr<SpringProperty>(CHAIN_SPRING_MASS, CHAIN_SPRING_STIFFNESS, CHAIN_SPRING_DAMPING);
        chainAnimation_ =
            AceType::MakeRefPtr<ChainAnimation>(space, space * 2, space / 2, springProperty_); /* 2:double */
        chainAnimation_->SetAnimationCallback([weak = AceType::WeakClaim(this)]() {
            auto list = weak.Upgrade();
            CHECK_NULL_VOID(list);
            list->MarkDirtyNodeSelf();
        });
    }
}

void ListPattern::ProcessDragStart(float startPosition)
{
    CHECK_NULL_VOID(chainAnimation_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto globalOffset = host->GetOffsetRelativeToWindow();
    int32_t index = -1;
    auto offset = startPosition - GetMainAxisOffset(globalOffset, GetAxis());
    for (auto & pos : itemPosition_) {
        if (offset <= pos.second.endPos) {
            index = pos.first;
            break;
        }
    }
    if (index == -1 && !itemPosition_.empty()) {
        index = itemPosition_.rbegin()->first + 1;
    }
    dragFromSpring_ = false;
    chainAnimation_->SetControlIndex(index);
    chainAnimation_->SetMaxIndex(maxListItemIndex_);
}

void ListPattern::ProcessDragUpdate(float dragOffset, int32_t source)
{
    CHECK_NULL_VOID(chainAnimation_);
    if (NearZero(dragOffset)) {
        return;
    }
    bool overDrag = (source == SCROLL_FROM_UPDATE) && (IsAtTop() || IsAtBottom());
    chainAnimation_->SetDelta(-dragOffset, overDrag);
}

float ListPattern::GetChainDelta(int32_t index) const
{
    CHECK_NULL_RETURN_NOLOG(chainAnimation_, 0.0f);
    return chainAnimation_->GetValue(index);
}

void ListPattern::InitMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mouseEventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);
    mouseEventHub->SetMouseEvent([weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEventWithoutKeyboard(info);
        }
    });
    isMouseEventInit_ = true;
}

void ListPattern::HandleMouseEventWithoutKeyboard(const MouseInfo& info)
{
    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    if (info.GetButton() == MouseButton::LEFT_BUTTON) {
        if (info.GetAction() == MouseAction::PRESS) {
            mouseStartOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
            MultiSelectWithoutKeyboard(selectedZone);
        } else if (info.GetAction() == MouseAction::MOVE) {
            mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
            MultiSelectWithoutKeyboard(selectedZone);
        } else if (info.GetAction() == MouseAction::RELEASE) {
            mouseStartOffset_.Reset();
            mouseEndOffset_.Reset();
            ClearSelectedZone();
        }
    }
}

void ListPattern::MultiSelectWithoutKeyboard(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> childrens;
    host->GenerateOneDepthVisibleFrame(childrens);
    for (const auto& item : childrens) {
        auto itemPattern = item->GetPattern<ListItemPattern>();
        CHECK_NULL_VOID(itemPattern);
        if (!itemPattern->Selectable()) {
            continue;
        }

        auto itemGeometry = item->GetGeometryNode();
        CHECK_NULL_VOID(itemGeometry);
        auto context = item->GetRenderContext();
        CHECK_NULL_VOID(context);

        auto itemRect = itemGeometry->GetFrameRect();
        if (!selectedZone.IsIntersectWith(itemRect)) {
            itemPattern->MarkIsSelected(false);
            context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        } else {
            itemPattern->MarkIsSelected(true);
            context->OnMouseSelectUpdate(true, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        }
    }

    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(selectedZone, SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

void ListPattern::ClearSelectedZone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(RectF(), SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

RectF ListPattern::ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset)
{
    RectF selectedZone;
    if (startOffset.GetX() <= endOffset.GetX()) {
        if (startOffset.GetY() <= endOffset.GetY()) {
            // bottom right
            selectedZone = RectF(startOffset.GetX(), startOffset.GetY(), endOffset.GetX() - startOffset.GetX(),
                endOffset.GetY() - startOffset.GetY());
        } else {
            // top right
            selectedZone = RectF(startOffset.GetX(), endOffset.GetY(), endOffset.GetX() - startOffset.GetX(),
                startOffset.GetY() - endOffset.GetY());
        }
    } else {
        if (startOffset.GetY() <= endOffset.GetY()) {
            // bottom left
            selectedZone = RectF(endOffset.GetX(), startOffset.GetY(), startOffset.GetX() - endOffset.GetX(),
                endOffset.GetY() - startOffset.GetY());
        } else {
            // top left
            selectedZone = RectF(endOffset.GetX(), endOffset.GetY(), startOffset.GetX() - endOffset.GetX(),
                startOffset.GetY() - endOffset.GetY());
        }
    }

    return selectedZone;
}

void ListPattern::SetSwiperItem(WeakPtr<ListItemPattern> swiperItem)
{
    if (swiperItem_ != swiperItem) {
        auto item = swiperItem_.Upgrade();
        if (item) {
            item->SwiperReset();
        }
        swiperItem_ = std::move(swiperItem);
    }
}

void ListPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("multiSelectable", multiSelectable_);
}
} // namespace OHOS::Ace::NG
