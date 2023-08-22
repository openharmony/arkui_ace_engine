/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/gestures/recognizers/pinch_recognizer.h"

#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "base/ressched/ressched_report.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t MAX_PINCH_FINGERS = 5;
constexpr int32_t DEFAULT_PINCH_FINGERS = 2;
constexpr Dimension DEFAULT_PINCH_DISTANCE = Dimension(5.0, DimensionUnit::VP);
constexpr double SCALE_PER_AXIS_EVENT = 0.1f;

} // namespace

PinchRecognizer::PinchRecognizer(int32_t fingers, double distance)
    : MultiFingersRecognizer(fingers), distance_(distance)
{
    if (fingers_ > MAX_PINCH_FINGERS || fingers_ < DEFAULT_PINCH_FINGERS) {
        LOGW("pinchRecognizer fingers_ is illegal, change to DEFAULT_PINCH_FINGERS.");
        fingers_ = DEFAULT_PINCH_FINGERS;
    }
    if (distance_ <= 0) {
        distance_ = DEFAULT_PINCH_DISTANCE.ConvertToPx();
    }
}

void PinchRecognizer::OnAccepted()
{
    ResSchedReport::GetInstance().ResSchedDataReport("click");
    refereeState_ = RefereeState::SUCCEED;
    SendCallbackMsg(onActionStart_);
}

void PinchRecognizer::OnRejected()
{
    LOGD("pinch gesture has been rejected!");
    refereeState_ = RefereeState::FAIL;
}

bool PinchRecognizer::IsCtrlBeingPressed()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    return pipeline->IsKeyInPressed(KeyCode::KEY_CTRL_LEFT) || pipeline->IsKeyInPressed(KeyCode::KEY_CTRL_RIGHT);
}

void PinchRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    LOGD("pinch recognizer receives touch down event, begin to detect pinch event");
    if (IsRefereeFinished()) {
        LOGD("referee has already receives the result");
        return;
    }

    touchPoints_[event.id] = event;
    lastTouchEvent_ = event;

    if (static_cast<int32_t>(touchPoints_.size()) >= fingers_) {
        initialDev_ = ComputeAverageDeviation();
        pinchCenter_ = ComputePinchCenter();
        refereeState_ = RefereeState::DETECTING;
    }
}

void PinchRecognizer::HandleTouchDownEvent(const AxisEvent& event)
{
    LOGD("pinch recognizer receives axis start event, begin to detect pinch event");
    if (IsRefereeFinished()) {
        LOGD("referee has already receives the result");
        return;
    }

    if (refereeState_ == RefereeState::READY) {
        scale_ = 1.0f;
        pinchCenter_ = Offset(event.x, event.y);
        refereeState_ = RefereeState::DETECTING;
    }
}

void PinchRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    LOGD("pinch recognizer receives touch up event");
    if (currentFingers_ != fingers_) {
        return;
    }

    if (isPinchEnd_) {
        return;
    }

    lastTouchEvent_ = event;
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onActionEnd_);
        isPinchEnd_ = true;
    }
}

void PinchRecognizer::HandleTouchUpEvent(const AxisEvent& event)
{
    LOGD("pinch recognizer receives axis end event");

    if (isPinchEnd_) {
        return;
    }
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onActionEnd_);
        isPinchEnd_ = true;
    }
}

void PinchRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    LOGD("pinch recognizer receives touch move event");
    if (currentFingers_ != fingers_) {
        return;
    }

    touchPoints_[event.id] = event;
    lastTouchEvent_ = event;
    currentDev_ = ComputeAverageDeviation();
    time_ = event.time;

    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        return;
    }
    if (refereeState_ == RefereeState::DETECTING) {
        if (GreatOrEqual(fabs(currentDev_ - initialDev_), distance_)) {
            scale_ = currentDev_ / initialDev_;
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
    } else if (refereeState_ == RefereeState::SUCCEED) {
        scale_ = currentDev_ / initialDev_;
        if (isFlushTouchEventsEnd_) {
            SendCallbackMsg(onActionUpdate_);
        }
    }
}

void PinchRecognizer::OnFlushTouchEventsBegin()
{
    isFlushTouchEventsEnd_ = false;
}

void PinchRecognizer::OnFlushTouchEventsEnd()
{
    isFlushTouchEventsEnd_ = true;
}

void PinchRecognizer::HandleTouchMoveEvent(const AxisEvent& event)
{
    LOGD("pinch recognizer receives axis update event");

    if (isPinchEnd_) {
        return;
    }
    if (NearZero(event.pinchAxisScale) && !IsCtrlBeingPressed()) {
        if (refereeState_ == RefereeState::DETECTING) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return;
        }
        if (refereeState_ == RefereeState::SUCCEED) {
            refereeState_ = RefereeState::READY;
            SendCallbackMsg(onActionEnd_);
            isPinchEnd_ = true;
            return;
        }
    }

    time_ = event.time;
    if (refereeState_ == RefereeState::DETECTING || refereeState_ == RefereeState::SUCCEED) {
        if (event.pinchAxisScale != 0.0) {
            scale_ = event.pinchAxisScale;
        } else {
            if (GreatNotEqual(event.verticalAxis, 0.0) || GreatNotEqual(event.horizontalAxis, 0.0)) {
                scale_ -= SCALE_PER_AXIS_EVENT;
            } else if (LessNotEqual(event.verticalAxis, 0.0) || LessNotEqual(event.horizontalAxis, 0)) {
                scale_ += SCALE_PER_AXIS_EVENT;
            }
            if (LessNotEqual(scale_, 0.0)) {
                scale_ = 0.0;
            }
        }
        if (refereeState_ == RefereeState::DETECTING) {
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
        SendCallbackMsg(onActionUpdate_);
    }
}

void PinchRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    LOGD("pinch recognizer receives touch cancel event");
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCancelMsg();
    }
}

void PinchRecognizer::HandleTouchCancelEvent(const AxisEvent& event)
{
    LOGD("pinch recognizer receives axis cancel event");
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCancelMsg();
    }
}

double PinchRecognizer::ComputeAverageDeviation()
{
    // compute the coordinate of focal point
    double sumOfX = 0.0;
    double sumOfY = 0.0;
    for (auto& element : touchPoints_) {
        sumOfX = sumOfX + element.second.x;
        sumOfY = sumOfY + element.second.y;
    }
    double focalX = sumOfX / touchPoints_.size();
    double focalY = sumOfY / touchPoints_.size();

    // compute average deviation
    double devX = 0.0;
    double devY = 0.0;
    for (auto& element : touchPoints_) {
        devX = devX + fabs(element.second.x - focalX);
        devY = devY + fabs(element.second.y - focalY);
    }
    double aveDevX = devX / touchPoints_.size();
    double aveDevY = devY / touchPoints_.size();

    // compute zoom distance
    double zoomDistance = sqrt(pow(aveDevX, 2) + pow(aveDevY, 2));

    return zoomDistance;
}

Offset PinchRecognizer::ComputePinchCenter()
{
    double sumOfX = 0.0;
    double sumOfY = 0.0;
    for (auto& element : touchPoints_) {
        sumOfX = sumOfX + element.second.x;
        sumOfY = sumOfY + element.second.y;
    }
    double focalX = sumOfX / touchPoints_.size();
    double focalY = sumOfY / touchPoints_.size();

    Offset pinchCenter = Offset(focalX, focalY);

    return pinchCenter;
}

void PinchRecognizer::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    isPinchEnd_ = false;
}

void PinchRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback)
{
    if (callback && *callback) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        UpdateFingerListInfo(coordinateOffset_);
        info.SetFingerList(fingerList_);
        info.SetScale(scale_);
        info.SetPinchCenter(pinchCenter_);
        info.SetDeviceId(deviceId_);
        info.SetSourceDevice(deviceType_);
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
        if (recognizerTarget_.has_value()) {
            info.SetTarget(recognizerTarget_.value());
        }
        info.SetForce(lastTouchEvent_.force);
        if (lastTouchEvent_.tiltX.has_value()) {
            info.SetTiltX(lastTouchEvent_.tiltX.value());
        }
        if (lastTouchEvent_.tiltY.has_value()) {
            info.SetTiltY(lastTouchEvent_.tiltY.value());
        }
        info.SetSourceTool(lastTouchEvent_.sourceTool);
        (*callback)(info);
    }
}

bool PinchRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    RefPtr<PinchRecognizer> curr = AceType::DynamicCast<PinchRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (curr->fingers_ != fingers_ || curr->distance_ != distance_ || curr->priorityMask_ != priorityMask_) {
        ResetStatus();
        return false;
    }

    onActionStart_ = std::move(curr->onActionStart_);
    onActionUpdate_ = std::move(curr->onActionUpdate_);
    onActionEnd_ = std::move(curr->onActionEnd_);
    onActionCancel_ = std::move(curr->onActionCancel_);

    return true;
}

} // namespace OHOS::Ace::NG
