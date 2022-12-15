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
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
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
        isInitialized_ = true;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    if (!scrollableEvent_) {
        InitScrollableEvent();
    } else {
        if (scrollableEvent_->GetAxis() != axis) {
            gestureHub->RemoveScrollableEvent(scrollableEvent_);
            scrollableEvent_->SetAxis(axis);
            gestureHub->AddScrollableEvent(scrollableEvent_);
            if (scrollEffect_) {
                gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
                gestureHub->AddScrollEdgeEffect(GetDirection(), scrollEffect_);
            }
        }
    }

    SetEdgeEffect(gestureHub, listLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING));
    SetScrollBar();
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
    startMainPos_ = listLayoutAlgorithm->GetStartPosition();
    endMainPos_ = listLayoutAlgorithm->GetEndPosition();
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
    ProcessEvent(indexChanged, finalOffset, isJump);
    UpdateScrollBarOffset();

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    return (listLayoutProperty && listLayoutProperty->GetDivider().has_value()) || scrollBar_;
}

void ListPattern::ProcessEvent(bool indexChanged, float finalOffset, bool isJump)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listEventHub = host->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(listEventHub);

    auto onScroll = listEventHub->GetOnScroll();
    if (onScroll && !NearZero(finalOffset)) {
        auto source = GetScrollState();
        auto offsetPX = Dimension(finalOffset);
        auto offsetVP = Dimension(offsetPX.ConvertToVp(), DimensionUnit::VP);
        if (source == SCROLL_FROM_UPDATE) {
            onScroll(offsetVP, V2::ScrollState::SCROLL);
        } else if (source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING) {
            onScroll(offsetVP, V2::ScrollState::FLING);
        } else {
            onScroll(offsetVP, V2::ScrollState::IDLE);
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
        float lastStartPos = startMainPos_ - (currentOffset_ - lastOffset_);
        bool scrollUpToStart = GreatNotEqual(lastStartPos, 0.0) && LessOrEqual(startMainPos_, 0.0);
        bool scrollDownToStart = LessNotEqual(lastStartPos, 0.0) && GreatOrEqual(startMainPos_, 0.0);
        bool jumpToStart = isJump && NearZero(startMainPos_);
        if (scrollUpToStart || scrollDownToStart || jumpToStart) {
            onReachStart();
        }
    }
    auto onReachEnd = listEventHub->GetOnReachEnd();
    if (onReachEnd && (endIndex_ == maxListItemIndex_)) {
        float lastEndPos = endMainPos_ - (currentOffset_ - lastOffset_);
        float mainSize = GetMainContentSize();
        bool scrollUpToEnd = GreatNotEqual(lastEndPos, mainSize) && LessOrEqual(endMainPos_, mainSize);
        bool scrollDownToEnd = LessNotEqual(lastEndPos, mainSize) && GreatOrEqual(endMainPos_, mainSize);
        bool jumpToEnd = isJump && NearEqual(endMainPos_, mainSize);
        if (scrollUpToEnd || scrollDownToEnd || jumpToEnd) {
            onReachEnd();
        }
    }

    if (scrollStop_) {
        auto onScrollStop = listEventHub->GetOnScrollStop();
        if (onScrollStop) {
            onScrollStop();
        }
        scrollStop_ = false;
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

    CHECK_NULL_VOID_NOLOG(scrollableEvent_);
    scrollableEvent_->SetEnabled(scrollable_);
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
    if (IsOutOfBoundary(false)) {
        listLayoutAlgorithm->SetOverScrollFeature();
    }
    auto effect = listLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
    bool canOverScroll = (effect == EdgeEffect::SPRING) && (scrollableEvent_ && !scrollableEvent_->Idle());
    listLayoutAlgorithm->SetCanOverScroll(canOverScroll);
    return listLayoutAlgorithm;
}

bool ListPattern::UpdateCurrentOffset(float offset)
{
    // check edgeEffect is not springEffect
    if (scrollEffect_ && scrollEffect_->IsFadeEffect()) {
        HandleScrollEffect(offset);
    }
    if (!(scrollEffect_ && scrollEffect_->IsSpringEffect()) || !isScrollContent_) {
        if ((startIndex_ == 0) && NonNegative(startMainPos_) && Positive(offset)) {
            return false;
        }
        if (endIndex_ == maxListItemIndex_ && LessOrEqual(endMainPos_, GetMainContentSize()) && Negative(offset)) {
            return false;
        }
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
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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

void ListPattern::ProcessScrollEnd()
{
    isScrollContent_ = true;
    scrollStop_ = true;
    MarkDirtyNodeSelf();
}

float ListPattern::GetMainContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetPaddingSize().MainSize(GetDirection());
}

SizeF ListPattern::GetContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    return geometryNode->GetPaddingSize();
}

Axis ListPattern::GetDirection() const
{
    auto listLayoutProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listLayoutProperty, Axis::VERTICAL);
    return listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
}

bool ListPattern::IsOutOfBoundary(bool useCurrentDelta)
{
    if (itemPosition_.empty()) {
        return false;
    }
    auto startPos = useCurrentDelta ? startMainPos_ - currentDelta_ : startMainPos_;
    auto endPos = useCurrentDelta ? endMainPos_ - currentDelta_ : endMainPos_;
    auto mainSize = GetMainContentSize();
    bool outOfStart = (startIndex_ == 0) && Positive(startPos) && GreatNotEqual(endPos, mainSize);
    bool outOfEnd = (endIndex_ == maxListItemIndex_) && LessNotEqual(endPos, mainSize) && Negative(startPos);
    return outOfStart || outOfEnd;
}

void ListPattern::InitScrollableEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(GetDirection());
    auto task = [weak = WeakClaim(this)](double offset, int32_t source) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->SetScrollState(source);
        if (source != SCROLL_FROM_START) {
            if (!pattern->isScrollContent_ && pattern->scrollBar_) {
                if (source == SCROLL_FROM_UPDATE) {
                    offset = pattern->scrollBar_->CalcPatternOffset(-offset);
                } else {
                    return false;
                }
            }
            return pattern->UpdateCurrentOffset(static_cast<float>(offset));
        }
        return true;
    };
    scrollableEvent_->SetScrollPositionCallback(std::move(task));

    auto scrollEnd = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ProcessScrollEnd();
    };
    scrollableEvent_->SetScrollEndCallback(std::move(scrollEnd));

    auto listEventHub = host->GetEventHub<ListEventHub>();
    auto onScrollBegin = listEventHub->GetOnScrollBegin();
    if (onScrollBegin) {
        auto scrollBeginTask = [weak = WeakClaim(this)](Dimension dx, Dimension dy) {
            ScrollInfo scrollInfo = { dx, dy };
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, scrollInfo);
            auto host = pattern->GetHost();
            CHECK_NULL_RETURN(host, scrollInfo);
            auto listEventHub = host->GetEventHub<ListEventHub>();
            CHECK_NULL_RETURN(listEventHub, scrollInfo);
            auto onScrollBegin = listEventHub->GetOnScrollBegin();
            if (onScrollBegin) {
                scrollInfo = onScrollBegin(dx, dy);
            }
            return scrollInfo;
        };
        scrollableEvent_->SetScrollBeginCallback(std::move(scrollBeginTask));
    }
    auto gestureHub = listEventHub->GetGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

void ListPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(list, 0.0);
        return list->startMainPos_ - list->currentDelta_;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        return list->GetMainContentSize() - (list->endMainPos_ - list->startMainPos_);
    });
    scrollEffect->SetTrailingCallback([]() -> double { return 0.0; });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        return list->GetMainContentSize() - (list->endMainPos_ - list->startMainPos_);
    });
    scrollEffect->SetInitTrailingCallback([]() -> double { return 0.0; });
}

void ListPattern::SetEdgeEffect(const RefPtr<GestureEventHub>& gestureHub, EdgeEffect edgeEffect)
{
    CHECK_NULL_VOID(gestureHub);
    if (scrollEffect_ && (edgeEffect != scrollEffect_->GetEdgeEffect())) {
        gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
        scrollEffect_.Reset();
    }
    if (edgeEffect == EdgeEffect::SPRING && !scrollEffect_) {
        auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
        CHECK_NULL_VOID(springEffect);
        springEffect->SetOutBoundaryCallback([weak = AceType::WeakClaim(this)]() {
            auto list = weak.Upgrade();
            CHECK_NULL_RETURN_NOLOG(list, false);
            return list->IsOutOfBoundary();
        });
        // add callback to springEdgeEffect
        SetEdgeEffectCallback(springEffect);
        scrollEffect_ = springEffect;
        gestureHub->AddScrollEdgeEffect(GetDirection(), scrollEffect_);
    }
    if (edgeEffect == EdgeEffect::FADE && !scrollEffect_) {
        auto fadeEdgeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::GRAY);
        CHECK_NULL_VOID(fadeEdgeEffect);
        fadeEdgeEffect->SetHandleOverScrollCallback([weakScroll = AceType::WeakClaim(this)]() -> void {
            auto list = weakScroll.Upgrade();
            CHECK_NULL_VOID_NOLOG(list);
            auto host = list->GetHost();
            CHECK_NULL_VOID_NOLOG(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        });
        SetEdgeEffectCallback(fadeEdgeEffect);
        fadeEdgeEffect->InitialEdgeEffect();
        scrollEffect_ = fadeEdgeEffect;
        gestureHub->AddScrollEdgeEffect(GetDirection(), scrollEffect_);
    }
}

void ListPattern::HandleScrollEffect(float offset)
{
    bool reachStart = (startIndex_ == 0) && NearZero(startMainPos_);
    bool reachEnd = (endIndex_ == maxListItemIndex_) && NearEqual(endMainPos_, GetMainContentSize());
    // handle edge effect
    if ((reachStart && Positive(offset)) || (reachEnd && Negative(offset))) {
        scrollEffect_->HandleOverScroll(GetDirection(), -offset, GetContentSize());
    }
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
        HandleDirectionKey(event.code);
        return true;
    }
    return false;
}

bool ListPattern::HandleDirectionKey(KeyCode code)
{
    if ((GetDirection() == Axis::VERTICAL && code == KeyCode::KEY_DPAD_UP) ||
        (GetDirection() == Axis::HORIZONTAL && code == KeyCode::KEY_DPAD_LEFT)) {
        auto nextIndex = std::clamp(scrollIndex_ - 1, 0, maxListItemIndex_);
        if (nextIndex == scrollIndex_) {
            return false;
        }
        scrollIndex_ = nextIndex;
        LOGD("Scroll to next index: %{public}d", scrollIndex_);
        // Need to update: current selection
        ScrollToIndex(scrollIndex_, ScrollIndexAlignment::ALIGN_TOP);
        return true;
    }
    if ((GetDirection() == Axis::VERTICAL && code == KeyCode::KEY_DPAD_DOWN) ||
        (GetDirection() == Axis::HORIZONTAL && code == KeyCode::KEY_DPAD_RIGHT)) {
        auto nextIndex = std::clamp(scrollIndex_ + 1, 0, maxListItemIndex_);
        if (nextIndex == scrollIndex_) {
            return false;
        }
        scrollIndex_ = nextIndex;
        LOGD("Scroll to previous index: %{public}d", scrollIndex_);
        // Need to update: current selection
        ScrollToIndex(scrollIndex_, ScrollIndexAlignment::ALIGN_BUTTON);
        return true;
    }
    return false;
}

void ListPattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve)
{
    LOGI("AnimateTo:%f, duration:%f", position, duration);
    if (!animator_) {
        animator_ = AceType::MakeRefPtr<Animator>(PipelineBase::GetCurrentContext());
    }
    if (!animator_->IsStopped()) {
        animator_->Stop();
    }
    animator_->ClearInterpolators();

    auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(GetTotalOffset(), position, curve);
    animation->AddListener([weakScroll = AceType::WeakClaim(this)](float value) {
        auto list = weakScroll.Upgrade();
        CHECK_NULL_VOID_NOLOG(list);
        list->SetScrollState(SCROLL_FROM_JUMP);
        list->UpdateCurrentOffset(list->GetTotalOffset() - value);
    });
    animator_->AddInterpolator(animation);
    animator_->SetDuration(static_cast<int32_t>(duration));
    animator_->Play();
}

void ListPattern::ScrollTo(float position)
{
    LOGI("ScrollTo:%{public}f", position);
    SetScrollState(SCROLL_FROM_JUMP);
    UpdateCurrentOffset(GetTotalOffset() - position);
}

void ListPattern::ScrollToIndex(int32_t index, ScrollIndexAlignment align)
{
    LOGI("ScrollToIndex:%{public}d", index);
    if (index >= 0 && index <= maxListItemIndex_) {
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
        ScrollToIndex(maxListItemIndex_, ScrollIndexAlignment::ALIGN_BUTTON);
    }
}

bool ListPattern::ScrollPage(bool reverse)
{
    LOGI("ScrollPage:%{public}d", reverse);
    float distance = reverse ? GetMainContentSize() : -GetMainContentSize();
    SetScrollState(SCROLL_FROM_JUMP);
    UpdateCurrentOffset(distance);
    return true;
}

Offset ListPattern::GetCurrentOffset() const
{
    if (GetDirection() == Axis::HORIZONTAL) {
        return {GetTotalOffset(), 0.0};
    }
    return {0.0, GetTotalOffset()};
}

void ListPattern::SetScrollBar()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listPaintProperty = host->GetPaintProperty<ListPaintProperty>();
    auto displayMode = listPaintProperty->GetBarDisplayMode().value_or(DisplayMode::OFF);
    if (displayMode == DisplayMode::OFF) {
        if (scrollBar_) {
            scrollBar_.Reset();
        }
        if (touchEvent_) {
            auto hub = host->GetEventHub<EventHub>();
            CHECK_NULL_VOID(hub);
            auto gestureHub = hub->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(gestureHub);
            gestureHub->RemoveTouchEvent(touchEvent_);
            touchEvent_.Reset();
        }
    } else if (!scrollBar_) {
        scrollBar_ = AceType::MakeRefPtr<ScrollBar>(displayMode);
        // set the scroll bar style
        if (GetDirection() == Axis::HORIZONTAL) {
            scrollBar_->SetPositionMode(PositionMode::BOTTOM);
        }
        RegisterScrollBarEventTask();
    } else if (scrollBar_->GetDisplayMode() != displayMode) {
        scrollBar_->SetDisplayMode(displayMode);
    } else {
        return;
    }

    if (isInitialized_) {
        UpdateScrollBarOffset();
    }
}

void ListPattern::UpdateScrollBarOffset()
{
    if (itemPosition_.empty()) {
        return;
    }
    if (!scrollBar_ && !scrollBarProxy_) {
        return;
    }
    SizeF ContentSize = GetContentSize();
    Size size(ContentSize.Width(), ContentSize.Height());
    float itemsSize = itemPosition_.rbegin()->second.endPos - itemPosition_.begin()->second.startPos + spaceWidth_;
    float currentOffset = itemsSize / itemPosition_.size() * itemPosition_.begin()->first - startMainPos_;
    Offset scrollOffset = { currentOffset, currentOffset }; // fit for w/h switched.
    auto estimatedHeight = itemsSize / itemPosition_.size() * (maxListItemIndex_ + 1);

    // inner scrollbar
    if (scrollBar_) {
        scrollBar_->SetDriving(!isScrollContent_);
        scrollBar_->UpdateScrollBarRegion(Offset(), size, scrollOffset, estimatedHeight);
    }

    // outer scrollbar
    if (scrollBarProxy_) {
        scrollableDistance_ = estimatedHeight - GetMainContentSize();
        currentPosition_ = -currentOffset;
        scrollBarProxy_->NotifyScrollBar(AceType::WeakClaim(this));
    }
}

void ListPattern::RegisterScrollBarEventTask()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (touchEvent_) {
        gestureHub->RemoveTouchEvent(touchEvent_);
    }
    touchEvent_ = MakeRefPtr<TouchEventImpl>([weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto scrollBar = pattern->scrollBar_;
        CHECK_NULL_VOID(scrollBar);
        if (info.GetTouches().empty()) {
            return;
        }
        auto touch = info.GetTouches().front();
        if (touch.GetTouchType() == TouchType::DOWN) {
            Point point(touch.GetLocalLocation().GetX(), touch.GetLocalLocation().GetY());
            if (scrollBar->InBarRegion(point)) {
                scrollBar->SetPressed(true);
                pattern->isScrollContent_ = false;
            } else {
                scrollBar->SetPressed(false);
                pattern->isScrollContent_ = true;
            }
            pattern->MarkDirtyNodeSelf();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            scrollBar->SetPressed(false);
            pattern->MarkDirtyNodeSelf();
        }
    });
    gestureHub->AddTouchEvent(touchEvent_);
}

void ListPattern::SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy)
{
    CHECK_NULL_VOID(scrollBarProxy);
    auto scrollFunction = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (!pattern || pattern->GetDirection() == Axis::NONE) {
                return false;
            }
            pattern->SetScrollState(source);
            return pattern->UpdateCurrentOffset(offset);
        }
        return true;
    };
    ScrollableNodeInfo nodeInfo = { AceType::WeakClaim(this), std::move(scrollFunction) };
    scrollBarProxy->RegisterScrollableNode(nodeInfo);
    scrollBarProxy_ = scrollBarProxy;
}

} // namespace OHOS::Ace::NG
