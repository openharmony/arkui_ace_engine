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

#include "core/components_ng/event/pan_event.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

PanEventActuator::PanEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub, PanDirection direction,
    int32_t fingers, float distance)
    : gestureEventHub_(gestureEventHub), direction_(direction), fingers_(fingers), distance_(distance)
{
    if (fingers_ < DEFAULT_PAN_FINGER) {
        fingers_ = DEFAULT_PAN_FINGER;
    }

    if (LessNotEqual(distance_, 0.0)) {
        distance_ = DEFAULT_PAN_DISTANCE.ConvertToPx();
    }

    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    panRecognizer_ = MakeRefPtr<PanRecognizer>(fingers_, direction_, distance_);
}

void PanEventActuator::OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, ResponseLinkResult& responseLinkResult)
{
    if (panEvents_.empty() && !userCallback_) {
        return;
    }

    auto actionStart = [weak = WeakClaim(this)](GestureEvent& info) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        // In the actionStart callback, actuator->panEvents_ may be modified
        auto copyPanEvents = actuator->panEvents_;
        for (const auto& panEvent : copyPanEvents) {
            auto actionStart = panEvent->GetActionStartEventFunc();
            if (actionStart) {
                actionStart(info);
            }
        }

        // Trigger pan start event setted by user.
        auto userCallback = actuator->userCallback_;
        CHECK_NULL_VOID(userCallback);
        auto userActionStart = userCallback->GetActionStartEventFunc();
        if (userActionStart) {
            userActionStart(info);
        }
    };
    panRecognizer_->SetOnActionStart(actionStart);

    auto actionUpdate = [weak = WeakClaim(this)](GestureEvent& info) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        // In the actionUpdate callback, actuator->panEvents_ may be modified
        auto copyPanEvents = actuator->panEvents_;
        for (const auto& panEvent : copyPanEvents) {
            auto actionUpdate = panEvent->GetActionUpdateEventFunc();
            if (actionUpdate) {
                actionUpdate(info);
            }
        }

        // Trigger pan update event  setted by user.
        auto userCallback = actuator->userCallback_;
        CHECK_NULL_VOID(userCallback);
        auto userActionUpdate = userCallback->GetActionUpdateEventFunc();
        if (userActionUpdate) {
            userActionUpdate(info);
        }
    };
    panRecognizer_->SetOnActionUpdate(actionUpdate);

    auto actionEnd = [weak = WeakClaim(this)](GestureEvent& info) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        // In the actionEnd callback, actuator->panEvents_ may be modified
        auto copyPanEvents = actuator->panEvents_;
        for (const auto& panEvent : copyPanEvents) {
            auto actionEnd = panEvent->GetActionEndEventFunc();
            if (actionEnd) {
                actionEnd(info);
            }
        }

        // Trigger pan end event  setted by user.
        auto userCallback = actuator->userCallback_;
        CHECK_NULL_VOID(userCallback);
        auto userActionEnd = userCallback->GetActionEndEventFunc();
        if (userActionEnd) {
            userActionEnd(info);
        }
    };
    panRecognizer_->SetOnActionEnd(actionEnd);

    auto actionCancel = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        // In the actionCancel callback, actuator->panEvents_ may be modified
        auto copyPanEvents = actuator->panEvents_;
        for (const auto& panEvent : copyPanEvents) {
            auto actionCancel = panEvent->GetActionCancelEventFunc();
            if (actionCancel) {
                actionCancel();
            }
        }

        // Trigger pan end event  setted by user.
        auto userCallback = actuator->userCallback_;
        CHECK_NULL_VOID(userCallback);
        auto userActionCancel = userCallback->GetActionCancelEventFunc();
        if (userActionCancel) {
            userActionCancel();
        }
    };
    panRecognizer_->SetOnActionCancel(actionCancel);
    panRecognizer_->SetIsSystemGesture(true);
    panRecognizer_->SetRecognizerType(GestureTypeName::PAN_GESTURE);

    panRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    panRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    result.emplace_back(panRecognizer_);
    responseLinkResult.emplace_back(panRecognizer_);
}

void PanEventActuator::SetPanEventType(GestureTypeName typeName)
{
    if (panEvents_.empty()) {
        return;
    }
    auto gestureInfo = panRecognizer_->GetOrCreateGestureInfo();
    CHECK_NULL_VOID(gestureInfo);
    gestureInfo->SetType(typeName);
    gestureInfo->SetIsSystemGesture(true);
}

} // namespace OHOS::Ace::NG
