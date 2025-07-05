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
#include "core/components_ng/pattern/scrollable/scrollable_animation_consts.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {
void FreeScrollController::HandleAnimationUpdate(const OffsetF& currentValue)
{
    FireOnWillScroll(currentValue - prevOffset_, ScrollState::FLING, ScrollSource::FLING);
    pattern_.MarkDirty();
}

FreeScrollController::FreeScrollController(ScrollPattern& pattern) : pattern_(pattern)
{
    offset_ = MakeRefPtr<NodeAnimatablePropertyOffsetF>(OffsetF {}, [weak = WeakClaim(this)](const OffsetF& newOffset) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandleAnimationUpdate(newOffset);
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

    auto* ctx = pattern_.GetContext();
    CHECK_NULL_VOID(ctx);
    auto theme = ctx->GetTheme<ScrollableTheme>();
    CHECK_NULL_VOID(theme);
    friction_ = theme->GetFriction() * -FRICTION_SCALE;
}

namespace {
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
} // namespace

void FreeScrollController::HandlePanStart(const GestureEvent& event)
{
    state_ = ScrollState::SCROLL;
    pattern_.FireOnScrollStart();
}

void FreeScrollController::HandlePanUpdate(const GestureEvent& event)
{
    const auto dx = static_cast<float>(event.GetDelta().GetX());
    const auto dy = static_cast<float>(event.GetDelta().GetY());
    const float newX = offset_->Get().GetX() + dx;
    const float newY = offset_->Get().GetY() + dy;
    const auto scrollableArea = pattern_.GetViewPortExtent() - pattern_.GetViewSize();

    const float gammaX = GetGamma(newX, scrollableArea.Width(), pattern_.GetViewSize().Width());
    const float gammaY = GetGamma(newY, scrollableArea.Height(), pattern_.GetViewSize().Height());
    // apply friction if overScrolling
    OffsetF deltaF { NearZero(gammaX) ? dx : dx * pattern_.CalculateFriction(gammaX),
        NearZero(gammaY) ? dy : dy * pattern_.CalculateFriction(gammaY) };
    deltaF = FireOnWillScroll(deltaF, ScrollState::SCROLL, ScrollSource::DRAG);
    offset_->Set(offset_->Get() + deltaF);
    pattern_.MarkDirty();
}

void FreeScrollController::HandlePanEndOrCancel(const GestureEvent& event)
{
    state_ = ScrollState::IDLE;
    const auto& src = event.GetVelocity();
    OffsetF velocity { static_cast<float>(src.GetVelocityX()), static_cast<float>(src.GetVelocityY()) };
    TryScrollAnimation(velocity);
}

void FreeScrollController::TryScrollAnimation(const OffsetF& velocity)
{
    const auto curve = MakeRefPtr<ResponsiveSpringMotion>(fabs(2 * ACE_PI / friction_), 1.0f, 0.0f);
    AnimationOption option(curve, CUSTOM_SPRING_ANIMATION_DURATION);
    option.SetFinishCallbackType(FinishCallbackType::LOGICALLY);

    OffsetF finalPos = offset_->Get() + velocity / friction_;
    ClampPosition(finalPos);

    if (finalPos == offset_->Get()) {
        // No movement, no need to animate.
        return;
    }
    state_ = ScrollState::FLING;
    offset_->AnimateWithVelocity(option, finalPos, velocity, [weak = WeakClaim(this)]() {
        auto self = weak.Upgrade();
        if (self) {
            self->state_ = ScrollState::IDLE;
        }
    });
}

void FreeScrollController::ClampPosition(OffsetF& finalPos) const
{
    finalPos.SetX(std::clamp(finalPos.GetX(), std::min(-pattern_.GetScrollableDistance(), 0.0f), 0.0f));

    float verticalLimit = -(pattern_.GetViewPortExtent().Height() - pattern_.GetViewSize().Height());
    finalPos.SetY(std::clamp(finalPos.GetY(), std::min(verticalLimit, 0.0f), 0.0f));
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
    StopScrollAnimation();
}

void FreeScrollController::StopScrollAnimation()
{
    AnimationOption option;
    option.SetCurve(Curves::EASE);
    option.SetDuration(0);
    AnimationUtils::StartAnimation(
        option, [this]() { offset_->Set(offset_->Get()); }, nullptr);
    state_ = ScrollState::IDLE;
}

void FreeScrollController::HandleTouchUpOrCancel()
{
    if (state_ == ScrollState::IDLE) {
        // animate if currently out of bounds
        TryScrollAnimation({});
    }
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
    if (offset_ && offset_->Get() != adjustedOffset && state_ != ScrollState::FLING) {
        offset_->Set(adjustedOffset);
    }
    if (adjustedOffset != prevOffset_) {
        // Fire onDidScroll only if the offset has changed.
        FireOnDidScroll(adjustedOffset - prevOffset_, state_);
        prevOffset_ = adjustedOffset;
    }
    auto props = pattern_.GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(props);
    if (scrollableArea.IsNonNegative()) {
        enableScroll_ = props->GetScrollEnabled().value_or(true);
    } else {
        enableScroll_ = props->GetScrollEnabled().value_or(true) && pattern_.GetAlwaysEnabled();
    }
}

void FreeScrollController::UpdateOffset(const OffsetF& delta)
{
    if (state_ == ScrollState::FLING) {
        StopScrollAnimation();
    }
    auto newOffset = offset_->Get() + delta;
    ClampPosition(newOffset); // overScroll not allowed
    offset_->Set(newOffset);
    if (newOffset != offset_->Get()) {
        pattern_.MarkDirty();
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
    auto onScroll = eventHub->GetOnWillScrollEvent();
    if (!onScroll) {
        onScroll = eventHub->GetJSFrameNodeOnScrollWillScroll();
    }
    CHECK_NULL_RETURN(onScroll, delta);

    // delta sign is reversed in user space
    const auto res = onScroll(ToVp(-delta.GetX()), ToVp(-delta.GetY()), state, source);
    auto* context = pattern_.GetContext();
    CHECK_NULL_RETURN(context, delta);
    return { -context->NormalizeToPx(res.xOffset), -context->NormalizeToPx(res.yOffset) };
}

void FreeScrollController::FireOnDidScroll(const OffsetF& delta, ScrollState state) const
{
    auto eventHub = pattern_.GetOrCreateEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onScroll = eventHub->GetOnDidScrollEvent();
    if (!onScroll) {
        onScroll = eventHub->GetJSFrameNodeOnScrollDidScroll();
    }
    CHECK_NULL_VOID(onScroll);
    onScroll(ToVp(-delta.GetX()), ToVp(-delta.GetY()), state);
}
} // namespace OHOS::Ace::NG
