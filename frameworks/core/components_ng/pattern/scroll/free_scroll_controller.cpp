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

namespace OHOS::Ace::NG {
FreeScrollController::FreeScrollController(ScrollPattern& pattern) : pattern_(pattern)
{
    offset_ = MakeRefPtr<NodeAnimatablePropertyOffsetF>(OffsetF {}, [weak = WeakClaim(this)](const OffsetF& _) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->pattern_.MarkDirty();
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
            controller->duringPan_ = true;
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
 * @return ratio (non-negative) between overScroll and contentLength.
 */
float GetGamma(float offset, float contentLength)
{
    if (NearZero(contentLength)) {
        return 1.0f;
    }
    if (Positive(offset)) {
        return offset / contentLength;
    }
    if (LessNotEqual(offset, -contentLength)) {
        return (contentLength + offset) / contentLength;
    }
    return 0.0f;
}
} // namespace

void FreeScrollController::HandlePanUpdate(const GestureEvent& event)
{
    const auto dx = static_cast<float>(event.GetDelta().GetX());
    const auto dy = static_cast<float>(event.GetDelta().GetY());
    const float newX = offset_->Get().GetX() + dx;
    const float newY = offset_->Get().GetY() + dy;
    const auto& viewSize = pattern_.GetViewSize();

    const float gammaX = GetGamma(newX, viewSize.Width());
    const float gammaY = GetGamma(newY, viewSize.Height());
    // apply friction if overScrolling
    OffsetF deltaF { NearZero(gammaX) ? dx : dx * pattern_.CalculateFriction(gammaX),
        NearZero(gammaY) ? dy : dy * pattern_.CalculateFriction(gammaY) };
    offset_->Set(offset_->Get() + deltaF);
    pattern_.MarkDirty();
}

void FreeScrollController::HandlePanEndOrCancel(const GestureEvent& event)
{
    duringPan_ = false;
    const auto& src = event.GetVelocity();
    OffsetF velocity { static_cast<float>(src.GetVelocityX()), static_cast<float>(src.GetVelocityY()) };
    TryScrollAnimation(velocity);
}

void FreeScrollController::TryScrollAnimation(const OffsetF& velocity)
{
    const auto curve = MakeRefPtr<ResponsiveSpringMotion>(fabs(2 * ACE_PI / friction_), 1.0f, 0.0f);
    AnimationOption option(curve, CUSTOM_SPRING_ANIMATION_DURATION);

    OffsetF finalPos = offset_->Get() + velocity / friction_;
    ClampFinalPosition(finalPos);

    if (finalPos == offset_->Get()) {
        // No movement, no need to animate.
        return;
    }
    offset_->AnimateWithVelocity(option, finalPos, velocity, nullptr);
}

void FreeScrollController::ClampFinalPosition(OffsetF& finalPos) const
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
    // pause animation
    AnimationOption option;
    option.SetCurve(Curves::EASE);
    option.SetDuration(0);
    AnimationUtils::StartAnimation(
        option, [this]() { offset_->Set(offset_->Get()); }, nullptr);
}

void FreeScrollController::HandleTouchUpOrCancel()
{
    if (duringPan_) {
        return;
    }
    // animate if out of bounds
    TryScrollAnimation({});
}

OffsetF FreeScrollController::GetOffset() const
{
    if (offset_) {
        return offset_->Get();
    }
    return {};
}
} // namespace OHOS::Ace::NG
