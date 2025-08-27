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

#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_animation_consts.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr int32_t DEFAULT_PINCH_FINGER = 2;
    constexpr Dimension DEFAULT_PINCH_DISTANCE = 5.0_vp;
    constexpr float MAX_OVER_SCALE = 2.0f;
    constexpr float MIN_OVER_SCALE = 0.5f;
    constexpr float ANIMATION_CURVE_VELOCITY = 0.0f;    // The move animation spring curve velocity is 0.0
    constexpr float ANIMATION_CURVE_MASS = 1.0f;        // The move animation spring curve mass is 1.0
    constexpr float ANIMATION_CURVE_STIFFNESS = 188.0f; // The move animation spring curve stiffness is 188.0
    constexpr float ANIMATION_CURVE_DAMPING = 24.0f;    // The move animation spring curve damping is 24.0
}
ZoomController::ZoomController(ScrollPattern& pattern) : pattern_(pattern)
{
    InitializePinchGesture();
}

ZoomController::~ZoomController()
{
    DeinitializePinchGesture();
}

void ZoomController::InitializePinchGesture()
{
    pinchGesture_ = MakeRefPtr<PinchRecognizer>(DEFAULT_PINCH_FINGER, DEFAULT_PINCH_DISTANCE.ConvertToPx());
    pinchGesture_->SetOnActionStart([weak = AceType::WeakClaim(this)](GestureEvent& info) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->HandleZoomStart(info);
    });
    pinchGesture_->SetOnActionUpdate([weak = AceType::WeakClaim(this)](GestureEvent& info) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->HandleZoomUpdate(info);
    });
    auto endCallback = [weak = AceType::WeakClaim(this)](GestureEvent& info) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->HandleZoomEnd(info);
    };
    pinchGesture_->SetOnActionEnd(endCallback);
    pinchGesture_->SetOnActionCancel(endCallback);
    pinchGesture_->SetRecognizerType(GestureTypeName::PINCH_GESTURE);
    pinchGesture_->SetIsSystemGesture(true);
}

void ZoomController::DeinitializePinchGesture()
{
    pinchGesture_.Reset();
}

void ZoomController::HandleZoomStart(GestureEvent& info)
{
    zoomScaleStart_ = pattern_.GetZoomScale();
    auto hub = pattern_.GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(hub);
    hub->FireOnZoomStart();
}

void ZoomController::HandleZoomUpdate(GestureEvent& info)
{
    float scale = info.GetScale() * zoomScaleStart_;
    float maxScale = pattern_.maxZoomScale_;
    float minScale = std::min(pattern_.minZoomScale_, pattern_.maxZoomScale_);
    if (!pattern_.enableBouncesZoom_ ||
        info.GetInputEventType() == InputEventType::AXIS) {
        scale = std::clamp(scale, minScale, maxScale);
    } else if (scale > maxScale && scale > 0) {
        auto friction = (1.0f - MAX_OVER_SCALE) * maxScale / scale + MAX_OVER_SCALE;
        scale = maxScale * friction;
    } else if (scale < minScale && minScale > 0) {
        auto friction = (1.0f - MIN_OVER_SCALE) * scale / minScale + MIN_OVER_SCALE;
        scale = minScale * friction;
    }
    UpdateOffset(scale, pattern_.GetZoomScale(), GetCenterPoint(info));
    pattern_.UpdateZoomScale(scale);
}

void ZoomController::HandleZoomEnd(GestureEvent& info)
{
    float maxScale = pattern_.maxZoomScale_;
    float minScale = std::min(pattern_.minZoomScale_, pattern_.maxZoomScale_);
    float scale = pattern_.GetZoomScale();
    bool needAnimate = false;
    if (scale > maxScale) {
        scale = maxScale;
        needAnimate = true;
    } else if (scale < minScale) {
        scale = minScale;
        needAnimate = true;
    }
    if (needAnimate) {
        OffsetF centerOffset = GetCenterPoint(info);
        UpdateOffset(scale, pattern_.GetZoomScale(), centerOffset);
        pattern_.UpdateZoomScale(scale);
        AnimationOption option;
        option.SetDuration(400); /* 400: duration */
        auto curve = MakeRefPtr<SpringCurve>(
            ANIMATION_CURVE_VELOCITY, ANIMATION_CURVE_MASS, ANIMATION_CURVE_STIFFNESS, ANIMATION_CURVE_DAMPING);
        option.SetCurve(curve);
        AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
            auto zoomCtrl = weak.Upgrade();
            CHECK_NULL_VOID(zoomCtrl);
            auto pipeline = zoomCtrl->pattern_.GetContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->FlushUITasks();
        });
    }
    auto hub = pattern_.GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(hub);
    hub->FireOnZoomStop();
}

OffsetF ZoomController::GetCenterPoint(GestureEvent& info)
{
    std::size_t size = info.GetFingerList().size();
    if (size > 0) {
        Offset offset;
        for (auto& info : info.GetFingerList()) {
            offset += info.localLocation_;
        }
        return OffsetF(offset.GetX() / size, offset.GetY() / size);
    }
    return {};
}

void ZoomController::UpdateOffset(float scale, float prevScale, OffsetF centerOffset)
{
    if (prevScale > 0) {
        CHECK_NULL_VOID(pattern_.freeScroll_);
        auto currOffset = pattern_.freeScroll_->GetOffset();
        float dx = (centerOffset.GetX() - currOffset.GetX()) * (1 - scale / prevScale);
        float dy = (centerOffset.GetY() - currOffset.GetY()) * (1 - scale / prevScale);
        pattern_.FreeScrollBy(OffsetF(dx, dy));
    }
}
} // namespace OHOS::Ace::NG
