/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "base/geometry/axis.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"

namespace OHOS::Ace::NG {
void ScrollablePattern::SetAxis(Axis axis)
{
    if (axis_ == axis) {
        return;
    }
    axis_ = axis;
    if (scrollBar_) {
        scrollBar_->SetPositionMode(axis_ == Axis::HORIZONTAL ? PositionMode::BOTTOM : PositionMode::RIGHT);
    }
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
        scrollableEvent_->SetAxis(axis);
        gestureHub->AddScrollableEvent(scrollableEvent_);
    }
    if (scrollEffect_) {
        gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
        gestureHub->AddScrollEdgeEffect(GetAxis(), scrollEffect_);
    }
}

const RefPtr<GestureEventHub>& ScrollablePattern::GetGestureHub()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    return hub->GetOrCreateGestureEventHub();
}

const RefPtr<InputEventHub>& ScrollablePattern::GetInputHub()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(host, nullptr);
    return hub->GetOrCreateInputEventHub();
}

bool ScrollablePattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        return true;
    }
    if (scrollBar_ && scrollBar_->IsDriving()) {
        offset = scrollBar_->CalcPatternOffset(offset);
        source = SCROLL_FROM_BAR;
    }
    return UpdateCurrentOffset(offset, source);
}

void ScrollablePattern::DraggedDownScrollEndProcess()
{
    if (!isCoordEventNeedMoveUp_) {
        return;
    }

    if (coordinationEvent_ && !isDraggedDown_ && isReactInParentMovement_) {
        isReactInParentMovement_ = false;
        auto onScrollEnd = coordinationEvent_->GetOnScrollEndEvent();
        if (onScrollEnd) {
            onScrollEnd();
        }
    }
}

bool ScrollablePattern::OnScrollPosition(double offset, int32_t source)
{
    auto isAtTop = (IsAtTop() && Positive(offset));
    auto isDraggedDown = (isDraggedDown_ && isCoordEventNeedMoveUp_);
    if ((isAtTop || isDraggedDown) && (source == SCROLL_FROM_UPDATE) && !isReactInParentMovement_ &&
        (axis_ == Axis::VERTICAL)) {
        isReactInParentMovement_ = true;
        if (coordinationEvent_) {
            auto onScrollStart = coordinationEvent_->GetOnScrollStartEvent();
            if (onScrollStart) {
                onScrollStart();
            }
        }
    }
    if (coordinationEvent_ && source != SCROLL_FROM_UPDATE && isReactInParentMovement_) {
        isReactInParentMovement_ = false;
        auto onScrollEnd = coordinationEvent_->GetOnScrollEndEvent();
        if (onScrollEnd) {
            onScrollEnd();
        }
    }
    if (coordinationEvent_ && isReactInParentMovement_) {
        auto onScroll = coordinationEvent_->GetOnScroll();
        if (onScroll) {
            onScroll(offset);
            DraggedDownScrollEndProcess();
            if (isDraggedDown && Negative(offset) && !OutBoundaryCallback()) {
                return false;
            }
            return scrollEffect_ && scrollEffect_->IsSpringEffect();
        }
    }
    if (source == SCROLL_FROM_START) {
        SetParentScrollable();
        StopScrollBarAnimatorByProxy();
        AbortScrollAnimator();
    } else if (!AnimateStoped()) {
        return false;
    }
    return true;
}

void ScrollablePattern::OnScrollEnd()
{
    if (coordinationEvent_ && isReactInParentMovement_) {
        isReactInParentMovement_ = false;
        auto onScrollEnd = coordinationEvent_->GetOnScrollEndEvent();
        if (onScrollEnd) {
            onScrollEnd();
            return;
        }
    }
    if (scrollBar_) {
        scrollBar_->SetDriving(false);
        scrollBar_->OnScrollEnd();
    }
    StartScrollBarAnimatorByProxy();
}

void ScrollablePattern::AddScrollEvent()
{
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(GetAxis());
    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (!pattern->OnScrollPosition(offset, source)) {
            return false;
        }
        return pattern->OnScrollCallback(static_cast<float>(offset), source);
    };
    scrollableEvent_->SetScrollPositionCallback(std::move(scrollCallback));
    auto scrollEnd = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollEnd();
        pattern->OnScrollEndCallback();
    };
    scrollableEvent_->SetScrollEndCallback(std::move(scrollEnd));
    auto mouseLeftButtonScroll = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->IsScrollBarPressed();
    };
    scrollableEvent_->SetMouseLeftButtonScroll(std::move(mouseLeftButtonScroll));
    scrollableEvent_->SetFriction(friction_);
    gestureHub->AddScrollableEvent(scrollableEvent_);

    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_VOID_NOLOG(scrollable);
    auto func = [weak = AceType::WeakClaim(this)](double offset) -> OverScrollOffset {
        auto pattern = weak.Upgrade();
        if (pattern) {
            return pattern->GetOverScrollOffset(offset);
        }
        return { 0, 0 };
    };
    scrollable->SetOverScrollOffsetCallback(std::move(func));
    scrollable->SetNestedScrollOptions(nestedScroll_);

    auto scrollSnap = [weak = WeakClaim(this)](double targetOffset, double velocity) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnScrollSnapCallback(targetOffset, velocity);
    };
    scrollable->SetOnScrollSnapCallback(scrollSnap);

    auto calePredictSnapOffsetCallback = [weak = WeakClaim(this)](
                                             float finalOffset, float velocity) -> std::optional<float> {
        auto pattern = weak.Upgrade();
        std::optional<float> predictSnapOffset;
        CHECK_NULL_RETURN_NOLOG(pattern, predictSnapOffset);
        return pattern->CalePredictSnapOffset(finalOffset, velocity);
    };
    scrollable->SetCalePredictSnapOffsetCallback(std::move(calePredictSnapOffsetCallback));

    auto needScrollSnapToSideCallback = [weak = WeakClaim(this)](float delta) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->NeedScrollSnapToSide(delta);
    };
    scrollable->SetNeedScrollSnapToSideCallback(std::move(needScrollSnapToSideCallback));
}

void ScrollablePattern::SetEdgeEffect(EdgeEffect edgeEffect)
{
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollEffect_ && (edgeEffect != scrollEffect_->GetEdgeEffect())) {
        gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
        scrollEffect_.Reset();
    }
    if (edgeEffect == EdgeEffect::SPRING && !scrollEffect_) {
        auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
        CHECK_NULL_VOID(springEffect);
        springEffect->SetOutBoundaryCallback([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN_NOLOG(pattern, false);
            return pattern->OutBoundaryCallback();
        });
        // add callback to springEdgeEffect
        SetEdgeEffectCallback(springEffect);
        scrollEffect_ = springEffect;
        gestureHub->AddScrollEdgeEffect(GetAxis(), scrollEffect_);
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
        gestureHub->AddScrollEdgeEffect(GetAxis(), scrollEffect_);
    }
    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_VOID_NOLOG(scrollable);
    scrollable->SetEdgeEffect(edgeEffect);
}

bool ScrollablePattern::HandleEdgeEffect(float offset, int32_t source, const SizeF& size)
{
    // check edgeEffect is not springEffect
    if (scrollEffect_ && scrollEffect_->IsFadeEffect() && (source == SCROLL_FROM_UPDATE ||
        source == SCROLL_FROM_ANIMATION)) {    // handle edge effect
        if ((IsAtTop() && Positive(offset)) || (IsAtBottom() && Negative(offset))) {
            scrollEffect_->HandleOverScroll(GetAxis(), -offset, size);
        }
    }
    if (!(scrollEffect_ && scrollEffect_->IsSpringEffect() && (source == SCROLL_FROM_UPDATE ||
        source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING))) {
        if (IsAtTop() && Positive(offset)) {
            return false;
        }
        if (IsAtBottom() && Negative(offset)) {
            return false;
        }
    }
    return true;
}

void ScrollablePattern::RegisterScrollBarEventTask()
{
    CHECK_NULL_VOID(scrollBar_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = GetGestureHub();
    auto inputHub = GetInputHub();
    CHECK_NULL_VOID(gestureHub);
    CHECK_NULL_VOID(inputHub);
    scrollBar_->SetGestureEvent();
    scrollBar_->SetMouseEvent();
    scrollBar_->SetMarkNeedRenderFunc([weak = AceType::WeakClaim(AceType::RawPtr(host))]() {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        host->MarkNeedRenderOnly();
    });
    gestureHub->AddTouchEvent(scrollBar_->GetTouchEvent());
    inputHub->AddOnMouseEvent(scrollBar_->GetMouseEvent());
}

void ScrollablePattern::SetScrollBar(DisplayMode displayMode)
{
    if (displayMode == DisplayMode::OFF) {
        if (scrollBar_) {
            auto gestureHub = GetGestureHub();
            if (gestureHub) {
                gestureHub->RemoveTouchEvent(scrollBar_->GetTouchEvent());
            }
            scrollBar_->MarkNeedRender();
            scrollBar_.Reset();
        }
        return;
    }
    if (!scrollBar_) {
        scrollBar_ = AceType::MakeRefPtr<ScrollBar>(displayMode);
        // set the scroll bar style
        if (GetAxis() == Axis::HORIZONTAL) {
            scrollBar_->SetPositionMode(PositionMode::BOTTOM);
        }
        RegisterScrollBarEventTask();
    } else if (scrollBar_->GetDisplayMode() != displayMode) {
        scrollBar_->SetDisplayMode(displayMode);
    }
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID_NOLOG(renderContext);
    if (renderContext->HasBorderRadius()) {
        auto borderRadius = renderContext->GetBorderRadius().value();
        if (!(borderRadius == scrollBar_->GetHostBorderRadius())) {
            scrollBar_->SetHostBorderRadius(borderRadius);
            scrollBar_->CalcReservedHeight();
        }
    }
}

void ScrollablePattern::SetScrollBar(const std::unique_ptr<ScrollBarProperty>& property)
{
    if (!property) {
        SetScrollBar(DisplayMode::AUTO);
        return;
    }
    auto displayMode = property->GetScrollBarMode().value_or(DisplayMode::AUTO);
    SetScrollBar(displayMode);
    if (scrollBar_) {
        auto barColor = property->GetScrollBarColor();
        if (barColor) {
            scrollBar_->SetForegroundColor(barColor.value());
        }
        auto barWidth = property->GetScrollBarWidth();
        if (barWidth) {
            scrollBar_->SetInactiveWidth(barWidth.value());
            scrollBar_->SetNormalWidth(barWidth.value());
            scrollBar_->SetActiveWidth(barWidth.value());
            scrollBar_->SetTouchWidth(barWidth.value());
            scrollBar_->SetIsUserNormalWidth(true);
        } else {
            scrollBar_->SetIsUserNormalWidth(false);
        }
    }
}

void ScrollablePattern::UpdateScrollBarRegion(float offset, float estimatedHeight, Size viewPort, Offset viewOffset)
{
    // inner scrollbar, viewOffset is padding offset
    if (scrollBar_) {
        auto mainSize = axis_ == Axis::VERTICAL ? viewPort.Height() : viewPort.Width();
        bool scrollable = GreatNotEqual(estimatedHeight, mainSize);
        scrollBar_->SetScrollable(IsScrollable() && scrollable);
        Offset scrollOffset = { offset, offset }; // fit for w/h switched.
        scrollBar_->UpdateScrollBarRegion(viewOffset, viewPort, scrollOffset, estimatedHeight);
        scrollBar_->MarkNeedRender();
    }

    // outer scrollbar
    if (scrollBarProxy_) {
        estimatedHeight_ = estimatedHeight - (GetAxis() == Axis::VERTICAL ? viewPort.Height() : viewPort.Width());
        barOffset_ = -offset;
        scrollBarProxy_->NotifyScrollBar(AceType::WeakClaim(this));
    }
}

void ScrollablePattern::SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy)
{
    CHECK_NULL_VOID(scrollBarProxy);
    auto scrollFunction = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (!pattern || pattern->GetAxis() == Axis::NONE) {
                return false;
            }
            return pattern->UpdateCurrentOffset(offset, SCROLL_FROM_BAR);
        }
        return true;
    };
    ScrollableNodeInfo nodeInfo = { AceType::WeakClaim(this), std::move(scrollFunction) };
    scrollBarProxy->RegisterScrollableNode(nodeInfo);
    scrollBarProxy_ = scrollBarProxy;
}

void ScrollablePattern::SetNestedScroll(const NestedScrollOptions& nestedOpt)
{
    nestedScroll_ = nestedOpt;
    CHECK_NULL_VOID_NOLOG(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_VOID_NOLOG(scrollable);
    scrollable->SetNestedScrollOptions(nestedScroll_);
}

void ScrollablePattern::SetFriction(double friction)
{
    if (LessOrEqual(friction, 0.0)) {
        friction = FRICTION;
    }
    friction_ = friction;
    if (scrollableEvent_) {
        scrollableEvent_->SetFriction(friction_);
    }
}

RefPtr<ScrollablePattern> ScrollablePattern::GetParentScrollable()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        auto pattern = frameNode->GetPattern<ScrollablePattern>();
        if (!pattern) {
            continue;
        }
        if (pattern->GetAxis() != GetAxis()) {
            continue;
        }
        return pattern;
    }
    return nullptr;
}

void ScrollablePattern::SetParentScrollable()
{
    CHECK_NULL_VOID_NOLOG(scrollableEvent_);
    CHECK_NULL_VOID_NOLOG(scrollableEvent_->GetScrollable());
    if (nestedScroll_.NeedParent()) {
        auto parent = GetParentScrollable();
        CHECK_NULL_VOID_NOLOG(parent);
        CHECK_NULL_VOID_NOLOG(parent->scrollableEvent_);
        auto parentScrollable = parent->scrollableEvent_->GetScrollable();
        scrollableEvent_->GetScrollable()->SetParent(parentScrollable);
    } else {
        scrollableEvent_->GetScrollable()->SetParent(nullptr);
    }
}

void ScrollablePattern::StopAnimate()
{
    if (!IsScrollableStopped()) {
        StopScrollable();
    }
    if (animator_ && !animator_->IsStopped()) {
        animator_->Stop();
    }
}

void ScrollablePattern::ScrollTo(float position)
{
    StopAnimate();
    UpdateCurrentOffset(GetTotalOffset() - position, SCROLL_FROM_JUMP);
}

void ScrollablePattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth)
{
    LOGI("AnimateTo:%f, duration:%f", position, duration);
    if (!IsScrollableStopped()) {
        scrollAbort_ = true;
        StopScrollable();
    }
    if (!animator_) {
        animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
        animator_->AddStopListener([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(pattern);
            pattern->OnAnimateStop();
        });
    } else if (!animator_->IsStopped()) {
        scrollAbort_ = true;
        animator_->Stop();
    }
    animator_->ClearInterpolators();

    if (smooth) {
        PlaySpringAnimation(position, DEFAULT_SCROLL_TO_VELOCITY, DEFAULT_SCROLL_TO_MASS,
            DEFAULT_SCROLL_TO_STIFFNESS, DEFAULT_SCROLL_TO_DAMPING);
    } else if (AceType::InstanceOf<InterpolatingSpring>(curve)) {
        auto springCurve = AceType::DynamicCast<InterpolatingSpring>(curve);
        float velocity = springCurve->GetVelocity();
        float mass = springCurve->GetMass();
        float stiffness = springCurve->GetStiffness();
        float damping = springCurve->GetDamping();
        PlaySpringAnimation(position, velocity, mass, stiffness, damping);
    } else {
        auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(GetTotalOffset(), position, curve);
        animation->AddListener([weakScroll = AceType::WeakClaim(this)](float value) {
            auto pattern = weakScroll.Upgrade();
            CHECK_NULL_VOID_NOLOG(pattern);
            if (!pattern->UpdateCurrentOffset(pattern->GetTotalOffset() - value, SCROLL_FROM_ANIMATION_CONTROLLER)) {
                pattern->animator_->Stop();
            }
        });
        animator_->AddInterpolator(animation);
        animator_->SetDuration(static_cast<int32_t>(duration));
        animator_->Play();
    }
}

void ScrollablePattern::PlaySpringAnimation(
    float position, float velocity, float mass, float stiffness, float damping)
{
    auto start = GetTotalOffset();
    const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
    AceType::MakeRefPtr<SpringProperty>(mass, stiffness, damping);
    if (!springMotion_) {
        const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
            AceType::MakeRefPtr<SpringProperty>(mass, stiffness, damping);
        springMotion_ = AceType::MakeRefPtr<SpringMotion>(start, position, velocity, DEFAULT_OVER_SPRING_PROPERTY);
    } else {
        springMotion_->Reset(start, position, velocity, DEFAULT_OVER_SPRING_PROPERTY);
        springMotion_->ClearListeners();
    }
    springMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double position) {
        auto pattern = weakScroll.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->UpdateCurrentOffset(pattern->GetTotalOffset() - position, SCROLL_FROM_ANIMATION_CONTROLLER)) {
            pattern->animator_->Stop();
        }
    });
    animator_->PlayMotion(springMotion_);
}
} // namespace OHOS::Ace::NG
