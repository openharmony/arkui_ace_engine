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

#include <cmath>

#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_animation_consts.h"

namespace OHOS::Ace::NG {
FreeScrollController::FreeScrollController(ScrollPattern& pattern) : pattern_(pattern)
{
    offset_ = MakeRefPtr<NodeAnimatablePropertyOffsetF>(OffsetF {}, [this](const OffsetF& _) {
        pattern_.MarkDirty();
    });
    InitializePanRecognizer();
    InitializeTouchEvent();
}
FreeScrollController::~FreeScrollController()
{
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
    freePanGesture_->SetOnActionUpdate([weak = WeakClaim(this)](const GestureEvent& event) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandlePanUpdate(event);
        }
    });
    freePanGesture_->SetOnActionEnd([weak = WeakClaim(this)](const GestureEvent& event) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandlePanEnd(event);
        }
    });

    auto* ctx = pattern_.GetContext();
    CHECK_NULL_VOID(ctx);
    auto theme = ctx->GetTheme<ScrollableTheme>();
    CHECK_NULL_VOID(theme);
    friction_ = theme->GetFriction() * -FRICTION_SCALE;
}

void FreeScrollController::HandlePanUpdate(const GestureEvent& event)
{
    const auto& delta = event.GetDelta();
    offset_->Set(offset_->Get() + OffsetF { delta.GetX(), delta.GetY() });
    pattern_.MarkDirty();
}

void FreeScrollController::HandlePanEnd(const GestureEvent& event)
{
    OffsetF velocity(event.GetVelocity().GetVelocityX(), event.GetVelocity().GetVelocityY());

    AnimationOption option;
    option.SetCurve(MakeRefPtr<ResponsiveSpringMotion>(fabs(2 * M_PI / friction_), 1.0f, 0.0f));
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    option.SetFinishCallbackType(FinishCallbackType::LOGICALLY);

    OffsetF finalPos = offset_->Get() + velocity / friction_;
    ClampFinalPosition(finalPos);

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
        if (controller) {
            controller->HandleTouchEvent(info);
        }
    };

    freeTouch_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    auto hub = pattern_.GetGestureHub();
    CHECK_NULL_VOID(hub);
    hub->AddTouchEvent(freeTouch_);
}

void FreeScrollController::HandleTouchEvent(const TouchEventInfo& info)
{
    switch (info.GetTouches().front().GetTouchType()) {
        case TouchType::DOWN: {
            // pause animation
            AnimationOption option;
            option.SetCurve(Curves::EASE);
            option.SetDuration(0);
            AnimationUtils::StartAnimation(
                option, [this]() { offset_->Set(offset_->Get()); }, nullptr);
            break;
        }
        case TouchType::UP:
        case TouchType::CANCEL:
            // postTask: TryBounceBack();
            break;
        default:
            break;
    }
}

OffsetF FreeScrollController::GetOffset() const
{
    if (offset_) {
        return offset_->Get();
    }
    return {};
}
} // namespace OHOS::Ace::NG