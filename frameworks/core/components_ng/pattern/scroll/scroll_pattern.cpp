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

#include "core/components_ng/pattern/scroll/scroll_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_paint_property.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t SCROLL_NONE = 0;
constexpr int32_t SCROLL_TOUCH_DOWN = 1;
constexpr int32_t SCROLL_TOUCH_UP = 2;
constexpr float SCROLL_RATIO = 0.52f;
constexpr float SCROLL_BY_SPEED = 250.0f; // move 250 pixels per second
constexpr float SCROLL_MAX_TIME = 300.0f; // Scroll Animate max time 0.3 second
constexpr float UNIT_CONVERT = 1000.0f;    // 1s convert to 1000ms

float CalculateFriction(float gamma)
{
    return static_cast<float>(SCROLL_RATIO * std::pow(1.0 - gamma, SQUARE));
}

float CalculateOffsetByFriction(float extentOffset, float delta, float friction)
{
    if (NearZero(friction)) {
        return delta;
    }
    float deltaToLimit = extentOffset / friction;
    if (delta < deltaToLimit) {
        return delta * friction;
    }
    return extentOffset + delta - deltaToLimit;
}

} // namespace

void ScrollPattern::SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy)
{
    if (!scrollBarProxy) {
        return;
    }
    auto scrollFunction = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (!pattern || pattern->GetAxis() == Axis::NONE) {
                return false;
            }
            float adjustOffset = static_cast<float>(offset);
            pattern->AdjustOffset(adjustOffset, source);
            return pattern->UpdateCurrentOffset(adjustOffset, source);
        }
        return true;
        };
    scrollBarProxy->RegisterScrollableNode({ AceType::WeakClaim(this), std::move(scrollFunction) });
    scrollBarProxy_ = scrollBarProxy;
}

void ScrollPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void ScrollPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = host->GetPaintProperty<ScrollPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    if (axis_ == axis && scrollableEvent_) {
        LOGD("Direction not changed, need't resister scroll event again.");
        return;
    }

    axis_ = axis;
    // scrollPosition callback
    auto offsetTask = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (!pattern || pattern->GetAxis() == Axis::NONE) {
                return false;
            }
            float adjustOffset = static_cast<float>(offset);
            pattern->AdjustOffset(adjustOffset, source);
            return pattern->UpdateCurrentOffset(adjustOffset, source);
        }
        return true;
    };

    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(axis);
    scrollableEvent_->SetScrollPositionCallback(std::move(offsetTask));

    RegisterScrollEventTask();
    RegisterScrollBarEventTask();
    gestureHub->AddScrollEdgeEffect(axis_, scrollEffect_);
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

void ScrollPattern::RegisterScrollEventTask()
{
    auto eventHub = GetHost()->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onScrollEvent = eventHub->GetOnScrollEvent();
    if (onScrollEvent) {
        scrollableEvent_->SetOnScrollCallback(std::move(onScrollEvent));
    }
    auto scrollBeginEvent = eventHub->GetScrollBeginEvent();
    if (scrollBeginEvent) {
        scrollableEvent_->SetScrollBeginCallback(std::move(scrollBeginEvent));
    }
    auto scrollEndEvent = eventHub->GetScrollEndEvent();
    if (scrollEndEvent) {
        scrollableEvent_->SetScrollEndCallback(std::move(scrollEndEvent));
    }
}

void ScrollPattern::RegisterScrollBarEventTask()
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
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto paintProperty = host->GetPaintProperty<ScrollPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        auto scrollBar = paintProperty->GetScrollBar();
        CHECK_NULL_VOID(scrollBar);
        CHECK_NULL_VOID(info.GetTouches().size());
        auto touch = info.GetTouches().front();
        if (touch.GetTouchType() == TouchType::DOWN) {
            if (scrollBar->InBarRegion({ touch.GetLocalLocation().GetX(), touch.GetLocalLocation().GetY()})) {
                scrollBar->SetPressed(true);
                pattern->SetScrollContent(false);
            } else {
                scrollBar->SetPressed(false);
                pattern->SetScrollContent(true);
            }
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            scrollBar->SetPressed(false);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
        });
    gestureHub->AddTouchEvent(touchEvent_);
}

bool ScrollPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<ScrollLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    currentOffset_ = layoutAlgorithm->GetCurrentOffset();
    scrollableDistance_ = layoutAlgorithm->GetScrollableDistance();
    viewPortLength_ = layoutAlgorithm->GetViewPort();
    viewPort_ = layoutAlgorithm->GetViewPortSize();
    viewPortExtent_ = layoutAlgorithm->GetViewPortExtent();

    return false;
}

bool ScrollPattern::IsAtTop() const
{
    return GreatOrEqual(currentOffset_, 0.0);
}

bool ScrollPattern::IsAtBottom() const
{
    bool atBottom = LessOrEqual(currentOffset_, -scrollableDistance_);
    // TODO: ignore ReachMaxCount
    return atBottom;
}

bool ScrollPattern::ScrollPageCheck(float delta, int32_t source)
{
    return true;
}

void ScrollPattern::HandleScrollEffect() {}

void ScrollPattern::HandleScrollBarOutBoundary() {}

void ScrollPattern::AdjustOffset(float& delta, int32_t source)
{
    if (!isScrollContent_) {
        delta *= -1.0f; // revert if operate scroll bar
    }
    if (NearZero(delta) || NearZero(viewPortLength_) || source == SCROLL_FROM_ANIMATION ||
        source == SCROLL_FROM_ANIMATION_SPRING) {
        return;
    }
    // the distance above the top, if lower than top, it is zero
    float overscrollPastStart = 0.0f;
    // the distance below the bottom, if higher than bottom, it is zero
    float overscrollPastEnd = 0.0f;
    float overscrollPast = 0.0f;
    // TODO: not consider rowReverse or colReverse
    overscrollPastStart = std::max(currentOffset_, 0.0f);
    overscrollPastEnd = std::max(-scrollableDistance_ - currentOffset_, 0.0f);
    // do not adjust offset if direction opposite from the overScroll direction when out of boundary
    if ((overscrollPastStart > 0.0f && delta < 0.0f) || (overscrollPastEnd > 0.0f && delta > 0.0f)) {
        return;
    }
    overscrollPast = std::max(overscrollPastStart, overscrollPastEnd);
    if (overscrollPast == 0.0f) {
        return;
    }
    float friction = CalculateFriction((overscrollPast - std::abs(delta)) / viewPortLength_);
    float direction = delta > 0.0f ? 1.0f : -1.0f;
    delta = direction * CalculateOffsetByFriction(overscrollPast, std::abs(delta), friction);
}

void ScrollPattern::ValidateOffset(int32_t source)
{
    if (scrollableDistance_ <= 0.0f) {
        return;
    }

    // restrict position between top and bottom
    if (!scrollEffect_ || scrollEffect_->IsRestrictBoundary() || source == SCROLL_FROM_JUMP ||
        source == SCROLL_FROM_BAR || source == SCROLL_FROM_ROTATE) {
        if (axis_ == Axis::HORIZONTAL) {
            if (IsRowReverse()) {
                currentOffset_ = std::clamp(currentOffset_, 0.0f, scrollableDistance_);
            } else {
                currentOffset_ = std::clamp(currentOffset_, -scrollableDistance_, 0.0f);
            }
        } else {
            currentOffset_ = std::clamp(currentOffset_, -scrollableDistance_, 0.0f);
        }
    }
}

void ScrollPattern::HandleScrollPosition(float scroll, int32_t scrollState)
{
    if (!scrollableEvent_) {
        return;
    }
    const auto& onScroll = scrollableEvent_->GetOnScrollCallback();
    if (onScroll) {
        // not consider async call
        Dimension scrollX(0, DimensionUnit::VP);
        Dimension scrollY(0, DimensionUnit::VP);
        Dimension scrollPx(scroll, DimensionUnit::PX);
        auto scrollVpValue = scrollPx.ConvertToVp();
        if (axis_ == Axis::HORIZONTAL) {
            scrollX.SetValue(scrollVpValue);
        } else {
            scrollY.SetValue(scrollVpValue);
        }
        onScroll(scrollX, scrollY);
    }
}

bool ScrollPattern::IsCrashTop() const
{
    bool scrollUpToReachTop = LessNotEqual(lastOffset_, 0.0) && GreatOrEqual(currentOffset_, 0.0);
    bool scrollDownToReachTop = GreatNotEqual(lastOffset_, 0.0) && LessOrEqual(currentOffset_, 0.0);
    return scrollUpToReachTop || scrollDownToReachTop;
}

bool ScrollPattern::IsCrashBottom() const
{
    float minExtent = -scrollableDistance_;
    bool scrollDownToReachEnd = GreatNotEqual(lastOffset_, minExtent) && LessOrEqual(currentOffset_, minExtent);
    bool scrollUpToReachEnd = LessNotEqual(lastOffset_, minExtent) && GreatOrEqual(currentOffset_, minExtent);
    return (scrollUpToReachEnd || scrollDownToReachEnd) && ReachMaxCount();
}

bool ScrollPattern::IsScrollOutOnEdge(float delta) const
{
    if ((IsAtBottom() && delta < 0.0f) || (IsAtTop() && delta > 0.0f)) {
        if (!scrollEffect_ || scrollEffect_->IsNoneEffect()) {
            return true;
        }
    }
    return false;
}

void ScrollPattern::HandleCrashTop() const
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    const auto& onScrollEdge = eventHub->GetScrollEdgeEvent();
    if (!onScrollEdge) {
        return;
    }
    // not consider async call
    if (axis_ == Axis::HORIZONTAL) {
        onScrollEdge(ScrollEdge::LEFT);
        return;
    }
    onScrollEdge(ScrollEdge::TOP);
}

void ScrollPattern::HandleCrashBottom() const
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    const auto& onScrollEdge = eventHub->GetScrollEdgeEvent();
    if (!onScrollEdge) {
        return;
    }
    if (axis_ == Axis::HORIZONTAL) {
        onScrollEdge(ScrollEdge::RIGHT);
        return;
    }
    onScrollEdge(ScrollEdge::BOTTOM);
}

bool ScrollPattern::UpdateCurrentOffset(float delta, int32_t source)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (NearZero(delta)) {
        return false;
    }
    // TODO: ignore handle refresh
    if (IsScrollOutOnEdge(delta)) {
        return false;
    }
    if (!ScrollPageCheck(delta, source)) {
        return false;
    }
    // TODO: scrollBar effect!!
    lastOffset_ = currentOffset_;
    currentOffset_ += delta;
    HandleScrollEffect();
    ValidateOffset(source);
    bool next = true;
    int32_t touchState = SCROLL_NONE;
    if (source == SCROLL_FROM_UPDATE) {
        touchState = SCROLL_TOUCH_DOWN;
    } else if (source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING) {
        touchState = SCROLL_TOUCH_UP;
    }
    HandleScrollPosition(-delta, touchState);
    if (IsCrashTop()) {
        HandleCrashTop();
        next = false;
    } else if (IsCrashBottom()) {
        HandleCrashBottom();
        next = false;
    }
    if (scrollEffect_ && !scrollEffect_->IsRestrictBoundary()) {
        next = true;
    }
    // inner scroll bar
    auto paintProperty = GetPaintProperty<ScrollPaintProperty>();
    if (paintProperty && lastOffset_ != currentOffset_) {
        paintProperty->UpdateScrollBarOffset(currentOffset_, viewPortExtent_);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    // outer scrollbar
    if (source != SCROLL_FROM_BAR && scrollBarProxy_ && lastOffset_ != currentOffset_) {
        scrollBarProxy_->NotifyScrollBar(AceType::WeakClaim(this));
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    return next;
}

void ScrollPattern::CreateOrStopAnimator()
{
    if (!animator_) {
        animator_ = AceType::MakeRefPtr<Animator>(PipelineBase::GetCurrentContext());
        return;
    }
    if (!animator_->IsStopped()) {
        animator_->Stop();
    }
    animator_->ClearInterpolators();
}

void ScrollPattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool limitDuration,
    const std::function<void()>& onFinish)
{
    LOGD("scroll pattern, from %{public}f to %{public}f", currentOffset_, position);
    CreateOrStopAnimator();
    // TODO: no accessibility event
    auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(currentOffset_, position, curve);
    animation->AddListener([weakScroll = AceType::WeakClaim(this)](float value) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->DoJump(value);
        }
    });
    animator_->AddInterpolator(animation);
    animator_->SetDuration(static_cast<int32_t>(limitDuration ? std::min(duration, SCROLL_MAX_TIME) : duration));
    animator_->ClearStopListeners();
    animator_->Play();
    // TODO: expand stop listener
    animator_->AddStopListener([onFinish]() {
        if (onFinish) {
            onFinish();
        }
    });
}

void ScrollPattern::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    if (scrollEdgeType == ScrollEdgeType::SCROLL_NONE) {
        return;
    }
    float distance = scrollEdgeType == ScrollEdgeType::SCROLL_TOP ? -currentOffset_ :
        (-scrollableDistance_ - currentOffset_);
    ScrollBy(distance, distance, smooth);
}

void ScrollPattern::ScrollBy(float pixelX, float pixelY, bool smooth, const std::function<void()>& onFinish)
{
    float distance = (axis_ == Axis::VERTICAL) ? pixelY : pixelX;
    if (NearZero(distance)) {
        return;
    }
    float position = currentOffset_ + distance;
    if (smooth) {
        AnimateTo(position, fabs(distance) * UNIT_CONVERT / SCROLL_BY_SPEED, Curves::EASE_OUT, true, onFinish);
        return;
    }
    JumpToPosition(position);
}

bool ScrollPattern::ScrollPage(bool reverse, bool smooth, const std::function<void()>& onFinish)
{
    float distance = reverse ? viewPortLength_ : -viewPortLength_;
    ScrollBy(distance, distance, smooth, onFinish);
    return true;
}

void ScrollPattern::JumpToPosition(float position, int32_t source)
{
    // If an animation is playing, stop it.
    if (animator_) {
        if (!animator_->IsStopped()) {
            animator_->Stop();
        }
        animator_->ClearInterpolators();
    }
    DoJump(position, source);
}

void ScrollPattern::DoJump(float position, int32_t source)
{
    float setPosition = (axis_ == Axis::HORIZONTAL && IsRowReverse()) ? -position : position;
    if (!NearEqual(currentOffset_, setPosition)) {
        UpdateCurrentOffset(setPosition - currentOffset_, source);
    }
}

void ScrollPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            return scroll->GetCurrentPosition();
        }
        return 0.0;
    });
    scrollEffect->SetLeadingCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto scroll = weakScroll.Upgrade();
        if (scroll && !scroll->IsRowReverse() && !scroll->IsColReverse()) {
            return -scroll->GetScrollableDistance();
        }
        return 0.0;
    });
    scrollEffect->SetTrailingCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto scroll = weakScroll.Upgrade();
        if (scroll && (scroll->IsRowReverse() || scroll->IsColReverse())) {
            return scroll->GetScrollableDistance();
        }
        return 0.0;
    });
    scrollEffect->SetInitLeadingCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto scroll = weakScroll.Upgrade();
        if (scroll && !scroll->IsRowReverse() && !scroll->IsColReverse()) {
            return -scroll->GetScrollableDistance();
        }
        return 0.0;
    });
    scrollEffect->SetInitTrailingCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto scroll = weakScroll.Upgrade();
        if (scroll && (scroll->IsRowReverse() || scroll->IsColReverse())) {
            return scroll->GetScrollableDistance();
        }
        return 0.0;
    });
}

void ScrollPattern::RemoveScrollEdgeEffect()
{
    if (!scrollEffect_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
}

void ScrollPattern::SetScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    if (scrollEffect && scrollEffect->IsSpringEffect()) {
        auto springEffect = AceType::DynamicCast<ScrollSpringEffect>(scrollEffect);
        CHECK_NULL_VOID(springEffect);
        springEffect->SetOutBoundaryCallback([weakScroll = AceType::WeakClaim(this)]() {
            auto scroll = weakScroll.Upgrade();
            if (scroll) {
                return scroll->IsOutOfBoundary();
            }
            return false;
        });
        // add callback to springEdgeEffect
        SetEdgeEffectCallback(scrollEffect);
    }
    RemoveScrollEdgeEffect();
    scrollEffect_ = scrollEffect;
}

bool ScrollPattern::IsOutOfBoundary() const
{
    return (IsAtTop() || IsAtBottom());
}

} // namespace OHOS::Ace::NG
