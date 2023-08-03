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
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Color SELECT_FILL_COLOR = Color(0x1A000000);
constexpr Color SELECT_STROKE_COLOR = Color(0x33FFFFFF);
} // namespace

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

RefPtr<GestureEventHub> ScrollablePattern::GetGestureHub()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    return hub->GetOrCreateGestureEventHub();
}

RefPtr<InputEventHub> ScrollablePattern::GetInputHub()
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
        scrollBar_->ScheduleDisapplearDelayTask();
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

    auto calePredictSnapOffsetCallback = [weak = WeakClaim(this)](float delta) -> std::optional<float> {
        auto pattern = weak.Upgrade();
        std::optional<float> predictSnapOffset;
        CHECK_NULL_RETURN_NOLOG(pattern, predictSnapOffset);
        return pattern->CalePredictSnapOffset(delta);
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
    bool isAtTop = IsAtTop();
    bool isAtBottom = IsAtBottom();
    // check edgeEffect is not springEffect
    if (scrollEffect_ && scrollEffect_->IsFadeEffect() && (source == SCROLL_FROM_UPDATE ||
        source == SCROLL_FROM_ANIMATION)) {    // handle edge effect
        if ((isAtTop && Positive(offset)) || (isAtBottom && Negative(offset))) {
            scrollEffect_->HandleOverScroll(GetAxis(), -offset, size);
        }
    }
    if (!(scrollEffect_ && scrollEffect_->IsSpringEffect() && (source == SCROLL_FROM_UPDATE ||
        source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING))) {
        if (isAtTop && Positive(offset)) {
            animateOverScroll_ = false;
            return false;
        }
        if (isAtBottom && Negative(offset)) {
            animateOverScroll_ = false;
            return false;
        }
    }
    animateOverScroll_ = (source == SCROLL_FROM_ANIMATION_CONTROLLER) && (isAtTop || isAtBottom);
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
    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnScrollCallback(static_cast<float>(offset), source);
    };
    scrollBar_->SetScrollPositionCallback(std::move(scrollCallback));
    auto scrollEnd = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollEnd();
        pattern->OnScrollEndCallback();
    };
    scrollBar_->SetScrollEndCallback(std::move(scrollEnd));
    gestureHub->AddTouchEvent(scrollBar_->GetTouchEvent());
    inputHub->AddOnMouseEvent(scrollBar_->GetMouseEvent());
    CHECK_NULL_VOID(scrollableEvent_);
    scrollableEvent_->SetInBarRegionCallback(
        [weak = AceType::WeakClaim(AceType::RawPtr(scrollBar_))](const PointF& point, SourceType source) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_RETURN_NOLOG(scrollBar, false);
            if (source == SourceType::MOUSE) {
                return scrollBar->InBarActiveRegion(Point(point.GetX(), point.GetY()));
            }
            return scrollBar->InBarTouchRegion(Point(point.GetX(), point.GetY()));
        }
    );
    scrollableEvent_->SetBarCollectTouchTargetCallback([weak = AceType::WeakClaim(AceType::RawPtr(scrollBar_))]
        (const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(scrollBar);
            scrollBar->OnCollectTouchTarget(coordinateOffset, getEventTargetImpl, result);
        }
    );
}

void ScrollablePattern::SetScrollBar(DisplayMode displayMode)
{
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    if (displayMode == DisplayMode::OFF) {
        if (scrollBar_) {
            auto gestureHub = GetGestureHub();
            if (gestureHub) {
                gestureHub->RemoveTouchEvent(scrollBar_->GetTouchEvent());
            }
            scrollBar_.Reset();
            if (overlayModifier_) {
                overlayModifier_->SetOpacity(0);
            }
        }
        return;
    }
    DisplayMode oldDisplayMode = DisplayMode::OFF;
    if (!scrollBar_) {
        scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
        // set the scroll bar style
        if (GetAxis() == Axis::HORIZONTAL) {
            scrollBar_->SetPositionMode(PositionMode::BOTTOM);
        }
        RegisterScrollBarEventTask();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        oldDisplayMode = scrollBar_->GetDisplayMode();
    }

    if (oldDisplayMode != displayMode) {
        scrollBar_->SetDisplayMode(displayMode);
        if (overlayModifier_ && scrollBar_->IsScrollable()) {
            overlayModifier_->SetOpacity(UINT8_MAX);
        }
        scrollBar_->ScheduleDisapplearDelayTask();
    }
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
        bool scrollable = GreatNotEqual(estimatedHeight, mainSize) && IsScrollable();
        if (scrollBar_->IsScrollable() != scrollable) {
            scrollBar_->SetScrollable(scrollable);
            if (overlayModifier_) {
                overlayModifier_->SetOpacity(scrollable ? UINT8_MAX : 0);
            }
            if (scrollable) {
                scrollBar_->ScheduleDisapplearDelayTask();
            }
        }
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

void ScrollablePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
    host->GetRenderContext()->UpdateClipEdge(true);
}

void ScrollablePattern::UninitMouseEvent()
{
    if (!mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mouseEventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);
    mouseEventHub->RemoveOnMouseEvent(mouseEvent_);
    ClearMultiSelect();
    isMouseEventInit_ = false;
}

void ScrollablePattern::InitMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mouseEventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);
    if (!mouseEvent_) {
        auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->HandleMouseEventWithoutKeyboard(info);
            }
        };
        mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    }
    mouseEventHub->AddOnMouseEvent(mouseEvent_);
    isMouseEventInit_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetNotifyInDraggedCallback([wp = WeakClaim(this)]() {
        auto pattern = wp.Upgrade();
        if (pattern && pattern->mousePressed_) {
            pattern->OnMouseRelease();
        }
    });
}

void ScrollablePattern::HandleMouseEventWithoutKeyboard(const MouseInfo& info)
{
    if (info.GetButton() != MouseButton::LEFT_BUTTON) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    if (manager->IsDragged()) {
        if (mousePressed_) {
            OnMouseRelease();
        }
        return;
    }

    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    if (info.GetAction() == MouseAction::PRESS) {
        if (!IsItemSelected(info)) {
            ClearMultiSelect();
        }
        mouseStartOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        mousePressOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        totalOffsetOfMousePressed_ = mousePressOffset_.GetMainOffset(axis_) + GetTotalOffset();
        mousePressed_ = true;
        // do not select when click
    } else if (info.GetAction() == MouseAction::MOVE) {
        if (!mousePressed_) {
            return;
        }
        lastMouseMove_ = info;
        const static double FRAME_SELECTION_DISTANCE =
            pipeline->NormalizeToPx(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP));
        auto delta = OffsetF(mouseOffsetX, mouseOffsetY) - mousePressOffset_;
        if (Offset(delta.GetX(), delta.GetY()).GetDistance() > FRAME_SELECTION_DISTANCE) {
            mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
            MultiSelectWithoutKeyboard(selectedZone);
        }
        SelectWithScroll();
    } else if (info.GetAction() == MouseAction::RELEASE) {
        OnMouseRelease();
    }
}

void ScrollablePattern::SelectWithScroll()
{
    auto offset = GetOutOfScrollableOffset();
    if (NearZero(offset)) {
        return;
    }

    if (AnimateRunning()) {
        return;
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

    if (!selectMotion_) {
        selectMotion_ = AceType::MakeRefPtr<SelectMotion>(offset, [weak = WeakClaim(this)]() -> bool {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN_NOLOG(pattern, true);
            return pattern->ShouldSelectScrollBeStopped();
        });
        selectMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double offset) {
            auto pattern = weakScroll.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateCurrentOffset(offset, SCROLL_FROM_AXIS);
        });
    } else {
        selectMotion_->Reset(offset);
    }

    animator_->PlayMotion(selectMotion_);
}

void ScrollablePattern::OnMouseRelease()
{
    mouseStartOffset_.Reset();
    mouseEndOffset_.Reset();
    mousePressed_ = false;
    ClearSelectedZone();
    lastMouseMove_.SetLocalLocation(Offset::Zero());
}

void ScrollablePattern::ClearSelectedZone()
{
    DrawSelectedZone(RectF());
}

RectF ScrollablePattern::ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset)
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

void ScrollablePattern::DrawSelectedZone(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(selectedZone, SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

void ScrollablePattern::MarkSelectedItems()
{
    if (multiSelectable_ && mousePressed_) {
        auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
        if (!selectedZone.IsEmpty()) {
            MultiSelectWithoutKeyboard(selectedZone);
        }
    }
}

bool ScrollablePattern::ShouldSelectScrollBeStopped()
{
    if (!mousePressed_) {
        return true;
    }
    auto offset = GetOutOfScrollableOffset();
    if (NearZero(offset)) {
        return true;
    }

    // avoid start position move when offset is bigger then item height
    auto currentMainStartOffset = mouseStartOffset_.GetMainOffset(axis_);
    if (Positive(offset)) {
        if (LessNotEqual(totalOffsetOfMousePressed_, currentMainStartOffset + offset)) {
            offset = totalOffsetOfMousePressed_ - currentMainStartOffset;
        }
    } else {
        auto hostSize = GetHostFrameSize();
        CHECK_NULL_RETURN_NOLOG(hostSize.has_value(), true);
        auto minStartOffset = -(GetTotalHeight() - totalOffsetOfMousePressed_ - hostSize->MainSize(axis_));
        if (GreatNotEqual(minStartOffset, currentMainStartOffset + offset)) {
            offset = minStartOffset - currentMainStartOffset;
        }
    }

    if (axis_ == Axis::VERTICAL) {
        mouseStartOffset_.AddY(offset);
    } else {
        mouseStartOffset_.AddX(offset);
    }
    if (selectMotion_) {
        selectMotion_->Reset(offset);
    }
    return false;
};

float ScrollablePattern::GetOutOfScrollableOffset() const
{
    auto offset = 0.0f;
    auto mouseMainOffset = static_cast<float>(
        axis_ == Axis::VERTICAL ? lastMouseMove_.GetLocalLocation().GetY() : lastMouseMove_.GetLocalLocation().GetX());
    auto hostSize = GetHostFrameSize();
    CHECK_NULL_RETURN_NOLOG(hostSize.has_value(), offset);
    auto mainTop = 0.0f;
    auto mainBottom = hostSize->MainSize(axis_);
    if (GreatOrEqual(mouseMainOffset, mainTop) && LessOrEqual(mouseMainOffset, mainBottom)) {
        return offset;
    }
    if (GreatNotEqual(mouseMainOffset, mainBottom)) {
        if (IsAtBottom()) {
            return offset;
        }
        offset = mainBottom - mouseMainOffset;
    }
    if (LessNotEqual(mouseMainOffset, mainTop)) {
        if (IsAtTop()) {
            return offset;
        }
        offset = mainTop - mouseMainOffset;
    }
    return offset;
}
} // namespace OHOS::Ace::NG
