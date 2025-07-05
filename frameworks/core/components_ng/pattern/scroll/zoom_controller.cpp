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
    pinchGesture_ = MakeRefPtr<PinchGesture>(1, DEFAULT_PAN_DISTANCE.ConvertToPx());
    pinchGesture_->SetOnActionStartId([weak = AceType::WeakClaim(this)](GestureEvent& info) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->HandleZoomStart(info);
    });
    pinchGesture_->SetOnActionUpdateId([weak = AceType::WeakClaim(this)](GestureEvent& info) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->HandleZoomUpdate(info);
    });
    auto endCallback = [weak = AceType::WeakClaim(this)](GestureEvent& info) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->HandleZoomEnd(info);
    };
    pinchGesture_->SetOnActionEndId(endCallback);
    pinchGesture_->SetOnActionCancelId(endCallback);
    auto gestureHub = pattern_.GetGestureHub();
    if (gestureHub) {
        gestureHub->AddGesture(pinchGesture_);
    }
}

void ZoomController::DeinitializePinchGesture()
{
    auto gestureHub = pattern_.GetGestureHub();
    if (gestureHub) {
        gestureHub->RemoveGesture(pinchGesture_);
    }
    pinchGesture_.Reset();
}

void ZoomController::HandleZoomStart(GestureEvent& info)
{
    zoomScaleStart_ = pattern_.GetZoomScale();
    auto hub = pattern_.GetOrCreateEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(hub);
    hub->FireOnZoomStart();
}

void ZoomController::HandleZoomUpdate(GestureEvent& info)
{
    float scale = info.GetScale() * zoomScaleStart_;
    float minScale = std::min(pattern_.minZoomScale_, pattern_.maxZoomScale_);
    scale = std::clamp(scale, minScale, pattern_.maxZoomScale_);
    pattern_.UpdateZoomScale(scale);
    UpdateOffset(scale, pattern_.GetZoomScale(), GetCenterPoint(info));
}

void ZoomController::HandleZoomEnd(GestureEvent& info)
{
    auto hub = pattern_.GetOrCreateEventHub<ScrollEventHub>();
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
    CHECK_NULL_VOID(pattern_.freeScroll_);
    auto currOffset = pattern_.freeScroll_->GetOffset();
    float dx = (currOffset.GetX() - centerOffset.GetX()) * (prevScale / scale - 1);
    float dy = (currOffset.GetY() - centerOffset.GetY()) * (prevScale / scale - 1);
    pattern_.freeScroll_->UpdateOffset(OffsetF(dx, dy));
}
} // namespace OHOS::Ace::NG
