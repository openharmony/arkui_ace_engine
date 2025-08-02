/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scroll/free_scroll_controller.h"

#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/axis/axis_animator.h"
#include "core/components_ng/pattern/scrollable/scrollable_animation_consts.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {
FreeScrollController::FreeScrollController(ScrollPattern& pattern) : pattern_(pattern)
{
    offset_ = MakeRefPtr<NodeAnimatablePropertyOffsetF>(OffsetF {}, [weak = WeakClaim(this)](const OffsetF& newOffset) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandleOffsetUpdate(newOffset);
        }
    });
    auto* renderCtx = pattern_.GetRenderContext();
    CHECK_NULL_VOID(renderCtx);
    renderCtx->AttachNodeAnimatableProperty(offset_);

    InitializePanRecognizer();
    InitializeTouchEvent();
}

FreeScrollController::~FreeScrollController()
{
    if (offset_) {
        auto* renderCtx = pattern_.GetRenderContext();
        CHECK_NULL_VOID(renderCtx);
        renderCtx->DetachNodeAnimatableProperty(offset_);
    }
    if (freeTouch_) {
        auto hub = pattern_.GetGestureHub();
        CHECK_NULL_VOID(hub);
        hub->RemoveTouchEvent(freeTouch_);
    }
}

void FreeScrollController::InitializePanRecognizer()
{
    PanDirection panDirection { .type = PanDirection::ALL };
    const double distance = SystemProperties::GetScrollableDistance();
    PanDistanceMap distanceMap;

    if (Positive(distance)) {
        distanceMap[SourceTool::UNKNOWN] = distance;
    } else {
        distanceMap[SourceTool::UNKNOWN] = DEFAULT_PAN_DISTANCE.ConvertToPx();
        distanceMap[SourceTool::PEN] = DEFAULT_PEN_PAN_DISTANCE.ConvertToPx();
    }

    freePanGesture_ = MakeRefPtr<PanRecognizer>(DEFAULT_PAN_FINGER, panDirection, distanceMap);
    freePanGesture_->SetOnActionStart([weak = WeakClaim(this)](const GestureEvent& event) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandlePanStart(event);
        }
    });
    freePanGesture_->SetOnActionUpdate([weak = WeakClaim(this)](const GestureEvent& event) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandlePanUpdate(event);
        }
    });
    const auto endCallback = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandlePanEndOrCancel(event);
        }
    };
    freePanGesture_->SetOnActionEnd(endCallback);
    freePanGesture_->SetOnActionCancel(endCallback);
    freePanGesture_->SetRecognizerType(GestureTypeName::PAN_GESTURE);
    freePanGesture_->SetIsSystemGesture(true);
    freePanGesture_->SetIsAllowMouse(false);
    freePanGesture_->SetSysGestureJudge(
        [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
            if (gestureInfo->GetInputEventType() == InputEventType::AXIS &&
                (info->IsKeyPressed(KeyCode::KEY_CTRL_LEFT) || info->IsKeyPressed(KeyCode::KEY_CTRL_RIGHT))) {
                return GestureJudgeResult::REJECT;
            }
            return GestureJudgeResult::CONTINUE;
        });
}

namespace {
using State = FreeScrollController::State;
ScrollSource ToScrollSource(State state)
{
    switch (state) {
        case State::IDLE:
            return ScrollSource::SCROLLER;
        case State::DRAG:
            return ScrollSource::DRAG;
        case State::FLING:
            return ScrollSource::FLING;
        case State::EXTERNAL_FLING:
            return ScrollSource::SCROLLER_ANIMATION;
        case State::BOUNCE:
            return ScrollSource::EDGE_EFFECT;
        default:
            return ScrollSource::OTHER_USER_INPUT; // Default to IDLE if unknown
    }
}

ScrollState ToScrollState(State state)
{
    switch (state) {
        case State::IDLE:
            return ScrollState::IDLE;
        case State::DRAG:
            return ScrollState::SCROLL;
        case State::FLING:
        case State::EXTERNAL_FLING:
        case State::BOUNCE:
            return ScrollState::FLING;
        default:
            return ScrollState::IDLE; // Default to IDLE if unknown
    }
}

bool InAnimation(State state)
{
    return state == State::FLING || state == State::EXTERNAL_FLING || state == State::BOUNCE;
}

/**
 * @return ratio (non-negative) between overScroll and viewport length.
 */
float GetGamma(float offset, float scrollableDistance, float viewLength)
{
    if (NearZero(viewLength)) {
        return 1.0f;
    }
    if (Positive(offset)) {
        return offset / viewLength;
    }
    if (LessNotEqual(offset, -scrollableDistance)) {
        return -(scrollableDistance + offset) / viewLength;
    }
    return 0.0f;
}

float GetFriction(const ScrollPattern& pattern)
{
    auto friction = static_cast<float>(pattern.GetFriction());
    if (NonPositive(friction)) {
        auto* ctx = pattern.GetContext();
        CHECK_NULL_RETURN(ctx, 0.0f);
        auto theme = ctx->GetTheme<ScrollableTheme>();
        CHECK_NULL_RETURN(theme, 0.0f);
        friction = theme->GetFriction();
    }
    return friction * -FRICTION_SCALE;
}

AnimationOption CreateSpringOption(float friction)
{
    if (NearZero(friction)) {
        TAG_LOGW(AceLogTag::ACE_SCROLL, "CreateSpringOption called with zero friction, returning default option.");
        return {};
    }
    const auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(fabs(2 * ACE_PI / friction), 1.0f, 0.0f);
    AnimationOption option(curve, CUSTOM_SPRING_ANIMATION_DURATION);
    option.SetFinishCallbackType(FinishCallbackType::LOGICALLY);
    return option;
}

constexpr float EDGE_FRICTION = 10;
} // namespace

void FreeScrollController::HandlePanStart(const GestureEvent& event)
{
    state_ = State::DRAG;
    FireOnScrollStart();
    if (axisAnimator_ && !Scrollable::IsMouseWheelScroll(event)) {
        axisAnimator_->StopAxisAnimation();
    }
}

void FreeScrollController::HandlePanUpdate(const GestureEvent& event)
{
    size_t fingers = event.GetFingerList().size();
    auto dx = static_cast<float>(event.GetDelta().GetX());
    auto dy = static_cast<float>(event.GetDelta().GetY());
    if (fingers > 1) {
        dx /= fingers;
        dy /= fingers;
    }
    const float newX = offset_->Get().GetX() + dx;
    const float newY = offset_->Get().GetY() + dy;
    const auto scrollableArea = pattern_.GetViewPortExtent() - pattern_.GetViewSize();

    const float gammaX = GetGamma(newX, scrollableArea.Width(), pattern_.GetViewSize().Width());
    const float gammaY = GetGamma(newY, scrollableArea.Height(), pattern_.GetViewSize().Height());
    // apply friction if overScrolling
    OffsetF deltaF { NearZero(gammaX) ? dx : dx * pattern_.CalculateFriction(gammaX),
        NearZero(gammaY) ? dy : dy * pattern_.CalculateFriction(gammaY) };
    deltaF = FireOnWillScroll(deltaF, ScrollState::SCROLL, ScrollSource::DRAG);
    const auto newOffset = offset_->Get() + deltaF;
    CheckCrashEdge(newOffset, scrollableArea);
    if (Scrollable::IsMouseWheelScroll(event)) {
        AnimateOnMouseScroll(deltaF); // use animation to make mouse wheel scroll smoother
        return;
    }
    offset_->Set(newOffset);
    pattern_.MarkDirty();
}

void FreeScrollController::HandlePanEndOrCancel(const GestureEvent& event)
{
    state_ = State::IDLE;
    if (Scrollable::IsMouseWheelScroll(event)) {
        FireOnScrollEnd(); // no fling animation in mouse wheel scroll
        return;
    }
    const auto& src = event.GetVelocity();
    OffsetF velocity { static_cast<float>(src.GetVelocityX()), static_cast<float>(src.GetVelocityY()) };
    Fling(velocity);
    if (state_ == State::IDLE) {
        // If the state is IDLE, it means no fling animation is running.
        // We can fire the onScrollEnd event here.
        FireOnScrollEnd();
    }
}

void FreeScrollController::Fling(const OffsetF& velocity)
{
    const bool outOfBounds = ClampPosition(offset_->Get()) != offset_->Get();
    const float friction = outOfBounds ? EDGE_FRICTION : GetFriction(pattern_);
    if (NearZero(friction)) {
        TAG_LOGW(AceLogTag::ACE_SCROLL, "Fling called with zero friction, skipping fling animation.");
        return;
    }

    OffsetF finalPos = offset_->Get() + velocity * FLING_SCALE_K / friction;
    if (outOfBounds) {
        finalPos = ClampPosition(finalPos);
    } // when not out of bounds, finalPos doesn't need clamping because we would clamp it later during the
      // animation when we reach edge and increase friction.

    if (finalPos == offset_->Get()) {
        // No movement, no need to animate.
        return;
    }
    state_ = State::FLING;
    offset_->AnimateWithVelocity(CreateSpringOption(friction), finalPos, velocity, [weak = WeakClaim(this)]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        if (self->state_ == State::BOUNCE) {
            return; // don't trigger if we transitioned to BOUNCE state
        }
        self->HandleAnimationEnd();
    });
}

void FreeScrollController::HandleOffsetUpdate(const OffsetF& currentValue)
{
    pattern_.MarkDirty();
    if (state_ == State::DRAG) {
        return; // callbacks and checks already handled in HandlePanUpdate
    }

    FireOnWillScroll(currentValue - actualOffset_, ToScrollState(state_), ToScrollSource(state_));
    const bool reachedEdge = CheckCrashEdge(currentValue, pattern_.GetViewPortExtent() - pattern_.GetViewSize());
    if (state_ == State::FLING && reachedEdge) {
        // change friction during animation and transition to BOUNCE animation
        const auto finalPos = ClampPosition(offset_->GetStagingValue());
        AnimationUtils::Animate(
            CreateSpringOption(EDGE_FRICTION),
            [weak = WeakPtr(offset_), finalPos]() {
                auto prop = weak.Upgrade();
                CHECK_NULL_VOID(prop);
                prop->Set(finalPos);
            },
            [weak = WeakClaim(this)]() {
                auto self = weak.Upgrade();
                CHECK_NULL_VOID(self);
                self->HandleAnimationEnd();
            });
        state_ = State::BOUNCE;
    }
}

void FreeScrollController::HandleAnimationEnd()
{
    state_ = State::IDLE;
    FireOnScrollEnd();
}

OffsetF FreeScrollController::ClampPosition(const OffsetF& finalPos) const
{
    OffsetF clampedPos = finalPos;
    clampedPos.SetX(std::clamp(clampedPos.GetX(), std::min(-pattern_.GetScrollableDistance(), 0.0f), 0.0f));

    float verticalLimit = -(pattern_.GetViewPortExtent().Height() - pattern_.GetViewSize().Height());
    clampedPos.SetY(std::clamp(clampedPos.GetY(), std::min(verticalLimit, 0.0f), 0.0f));
    return clampedPos;
}

void FreeScrollController::InitializeTouchEvent()
{
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);

        switch (info.GetTouches().front().GetTouchType()) {
            case TouchType::DOWN:
                controller->HandleTouchDown();
                break;
            case TouchType::UP:
            case TouchType::CANCEL:
                controller->HandleTouchUpOrCancel();
                break;
            default:
                break;
        }
    };

    freeTouch_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    auto hub = pattern_.GetGestureHub();
    CHECK_NULL_VOID(hub);
    hub->AddTouchEvent(freeTouch_);
}

void FreeScrollController::HandleTouchDown()
{
    if (state_ == State::DRAG) {
        return; // ignore touch down of second finger
    }
    StopScrollAnimation();
}

void FreeScrollController::StopScrollAnimation()
{
    AnimationOption option;
    option.SetCurve(Curves::EASE);
    option.SetDuration(0);
    AnimationUtils::StartAnimation(
        option, [this]() { offset_->Set(offset_->Get()); }, nullptr);
    state_ = State::IDLE;
}

void FreeScrollController::HandleTouchUpOrCancel()
{
    if (state_ == State::IDLE) {
        // animate if currently out of bounds
        Fling({});
    }
}

void FreeScrollController::HandleAxisAnimationFrame(float newOffset)
{
    if (InAnimation(state_)) { // can't update offset if in animation
        return;
    }
    auto offset = offset_->Get();
    mouseWheelScrollIsVertical_ ? offset.SetY(newOffset) : offset.SetX(newOffset);
    offset_->Set(ClampPosition(offset));
}

void FreeScrollController::AnimateOnMouseScroll(const OffsetF& delta)
{
    mouseWheelScrollIsVertical_ = NearZero(delta.GetX());
    if (!axisAnimator_) {
        axisAnimator_ = MakeRefPtr<AxisAnimator>(
            [wk = WeakClaim(this)](float newOffset) { // animation frame callback
                auto self = wk.Upgrade();
                CHECK_NULL_VOID(self);
                self->HandleAxisAnimationFrame(newOffset);
            },
            nullptr, nullptr);
        axisAnimator_->Initialize(WeakClaim(pattern_.GetContext()));
    }
    Axis axis = mouseWheelScrollIsVertical_ ? Axis::VERTICAL : Axis::HORIZONTAL;
    axisAnimator_->OnAxis(delta.GetMainOffset(axis), offset_->Get().GetMainOffset(axis));
}

OffsetF FreeScrollController::GetOffset() const
{
    if (offset_) {
        return offset_->Get();
    }
    return {};
}

void FreeScrollController::OnLayoutFinished(const OffsetF& adjustedOffset, const SizeF& scrollableArea)
{
    if (offset_ && offset_->Get() != adjustedOffset &&
        !InAnimation(state_)) { // modifying animatableProperty during animation not allowed
        offset_->Set(adjustedOffset);
    }
    if (adjustedOffset != actualOffset_) {
        // Fire onDidScroll only if the offset has changed.
        FireOnDidScroll(adjustedOffset - actualOffset_, ToScrollState(state_));
        actualOffset_ = adjustedOffset;
    }
    auto props = pattern_.GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(props);
    if (scrollableArea.IsNonNegative()) {
        enableScroll_ = props->GetScrollEnabled().value_or(true);
    } else {
        enableScroll_ = props->GetScrollEnabled().value_or(true) && pattern_.GetAlwaysEnabled();
    }
    if (freePanGesture_) {
        freePanGesture_->SetEnabled(enableScroll_);
    }
}

void FreeScrollController::SetOffset(OffsetF newPos, bool allowOverScroll)
{
    if (InAnimation(state_)) {
        StopScrollAnimation();
    }
    if (!allowOverScroll) {
        newPos = ClampPosition(newPos);
    }
    if (newPos != offset_->Get()) {
        offset_->Set(newPos);
    }
}

namespace {
Dimension ToVp(float value)
{
    return Dimension { Dimension(value).ConvertToVp(), DimensionUnit::VP };
}
} // namespace

OffsetF FreeScrollController::FireOnWillScroll(const OffsetF& delta, ScrollState state, ScrollSource source) const
{
    auto eventHub = pattern_.GetOrCreateEventHub<ScrollEventHub>();
    CHECK_NULL_RETURN(eventHub, delta);
    const auto& onScroll = eventHub->GetOnWillScrollEvent();
    const auto& frameCb = eventHub->GetJSFrameNodeOnScrollWillScroll();

    // delta sign is reversed in user space
    std::optional<TwoDimensionScrollResult> res;
    if (onScroll) {
        res = onScroll(ToVp(-delta.GetX()), ToVp(-delta.GetY()), state, source);
    }
    if (frameCb) {
        if (res) {
            // use the result from JS callback if available
            res = frameCb(res->xOffset, res->yOffset, state, source);
        } else {
            res = frameCb(ToVp(-delta.GetX()), ToVp(-delta.GetY()), state, source);
        }
    }
    if (!res) {
        return delta;
    }
    auto* context = pattern_.GetContext();
    CHECK_NULL_RETURN(context, delta);
    return { -context->NormalizeToPx(res->xOffset), -context->NormalizeToPx(res->yOffset) };
}

void FreeScrollController::FireOnDidScroll(const OffsetF& delta, ScrollState state) const
{
    auto eventHub = pattern_.GetOrCreateEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    const auto& onScroll = eventHub->GetOnDidScrollEvent();
    const auto& frameCb = eventHub->GetJSFrameNodeOnScrollDidScroll();
    if (onScroll) {
        onScroll(ToVp(-delta.GetX()), ToVp(-delta.GetY()), state);
    }
    if (frameCb) {
        frameCb(ToVp(-delta.GetX()), ToVp(-delta.GetY()), state);
    }
}

void FreeScrollController::FireOnScrollStart() const
{
    auto eventHub = pattern_.GetOrCreateEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    const auto& onScrollStart = eventHub->GetOnScrollStart();
    const auto& frameCb = eventHub->GetJSFrameNodeOnScrollStart();
    if (onScrollStart) {
        onScrollStart();
    }
    if (frameCb) {
        frameCb();
    }
    pattern_.AddEventsFiredInfo(ScrollableEventType::ON_SCROLL_START);
    if (auto scrollBar = pattern_.Get2DScrollBar()) {
        scrollBar->OnScrollStart();
    }
}

void FreeScrollController::FireOnScrollEnd() const
{
    auto eventHub = pattern_.GetOrCreateEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    const auto& onScrollStop = eventHub->GetOnScrollStop();
    const auto& frameCb = eventHub->GetJSFrameNodeOnScrollStop();
    if (onScrollStop) {
        onScrollStop();
    }
    if (frameCb) {
        frameCb();
    }
    pattern_.AddEventsFiredInfo(ScrollableEventType::ON_SCROLL_STOP);
    if (auto scrollBar = pattern_.Get2DScrollBar()) {
        scrollBar->OnScrollEnd();
    }
}

void FreeScrollController::FireOnScrollEdge(const std::vector<ScrollEdge>& edges) const
{
    auto eventHub = pattern_.GetOrCreateEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    const auto& onScrollEdge = eventHub->GetScrollEdgeEvent();
    CHECK_NULL_VOID(onScrollEdge);
    for (auto&& edge : edges) {
        onScrollEdge(edge);
    }
    pattern_.AddEventsFiredInfo(ScrollableEventType::ON_SCROLL_EDGE);
}

bool FreeScrollController::CheckCrashEdge(const OffsetF& newOffset, const SizeF& scrollableArea) const
{
    CHECK_NULL_RETURN(offset_, false);
    std::vector<ScrollEdge> edges;
    const auto checkEdge = [&](float prev, float curr, float minVal, ScrollEdge edgeMin, ScrollEdge edgeMax) {
        if (Negative(prev) && NonNegative(curr)) {
            edges.emplace_back(edgeMin);
        } else if (GreatNotEqual(prev, minVal) && LessOrEqual(curr, minVal)) {
            edges.emplace_back(edgeMax);
        }
    };

    checkEdge(actualOffset_.GetX(), newOffset.GetX(), -scrollableArea.Width(), ScrollEdge::LEFT, ScrollEdge::RIGHT);
    checkEdge(actualOffset_.GetY(), newOffset.GetY(), -scrollableArea.Height(), ScrollEdge::TOP, ScrollEdge::BOTTOM);

    if (!edges.empty()) {
        FireOnScrollEdge(edges);
        return true;
    }
    return false;
}

using std::optional;
void FreeScrollController::ScrollTo(OffsetF finalPos, const optional<float>& velocity, optional<int32_t> duration,
    RefPtr<Curve> curve, bool allowOverScroll)
{
    StopScrollAnimation();
    if (!allowOverScroll) {
        finalPos = ClampPosition(finalPos);
    }
    if (finalPos == offset_->Get()) {
        // No movement, no need to animate.
        return;
    }

    if (!curve) {
        curve = MakeRefPtr<InterpolatingSpring>(velocity.value_or(DEFAULT_SCROLL_TO_VELOCITY), DEFAULT_SCROLL_TO_MASS,
            DEFAULT_SCROLL_TO_STIFFNESS, DEFAULT_SCROLL_TO_DAMPING);
    }
    AnimationUtils::StartAnimation(
        { curve, duration.value_or(CUSTOM_SPRING_ANIMATION_DURATION) },
        [weak = WeakPtr(offset_), finalPos]() {
            auto prop = weak.Upgrade();
            CHECK_NULL_VOID(prop);
            prop->Set(finalPos);
        },
        [weak = WeakClaim(this)]() {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            self->HandleAnimationEnd();
        });
    state_ = State::EXTERNAL_FLING;
    FireOnScrollStart();
}
} // namespace OHOS::Ace::NG
