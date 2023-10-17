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

#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"

#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t MAX_ROTATION_FINGERS = 5;
constexpr int32_t DEFAULT_ROTATION_FINGERS = 2;

} // namespace

RotationRecognizer::RotationRecognizer(int32_t fingers, double angle) : MultiFingersRecognizer(fingers), angle_(angle)
{
    if (fingers_ > MAX_ROTATION_FINGERS || fingers_ < DEFAULT_ROTATION_FINGERS) {
        fingers_ = DEFAULT_ROTATION_FINGERS;
    }
}

void RotationRecognizer::OnAccepted()
{
    TAG_LOGD(AceLogTag::ACE_GESTURE_RECOGNIZER, "Rotation gesture has been accepted!");
    refereeState_ = RefereeState::SUCCEED;
    SendCallbackMsg(onActionStart_);
}

void RotationRecognizer::OnRejected()
{
    TAG_LOGD(AceLogTag::ACE_GESTURE_RECOGNIZER, "Rotation gesture has been rejected!");
    refereeState_ = RefereeState::FAIL;
}

void RotationRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    TAG_LOGD(AceLogTag::ACE_GESTURE_RECOGNIZER, "Rotation recognizer receives touch down event, begin to detect rotation event");
    if (fingers_ > MAX_ROTATION_FINGERS) {
        fingers_ = DEFAULT_ROTATION_FINGERS;
    }

    touchPoints_[event.id] = event;

    if (static_cast<int32_t>(touchPoints_.size()) >= fingers_) {
        initialAngle_ = ComputeAngle();
        refereeState_ = RefereeState::DETECTING;
    }
}

void RotationRecognizer::HandleTouchUpEvent(const TouchEvent& /*event*/)
{
    TAG_LOGD(AceLogTag::ACE_GESTURE_RECOGNIZER, "Rotation recognizer receives touch up event");
    if (currentFingers_ < fingers_) {
        TAG_LOGW(AceLogTag::ACE_GESTURE_RECOGNIZER, "RotationGesture current finger number is less than requiried finger number");
        return;
    }
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        info.SetAngle(resultAngle_);
        SendCallbackMsg(onActionEnd_);
    }
}

void RotationRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    TAG_LOGD(AceLogTag::ACE_GESTURE_RECOGNIZER, "Rotation recognizer receives touch move event");
    if (currentFingers_ < fingers_) {
        TAG_LOGW(AceLogTag::ACE_GESTURE_RECOGNIZER, "RotationGesture current finger number is less than requiried finger number");
        return;
    }
    touchPoints_[event.id] = event;
    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        return;
    }
    if (static_cast<int32_t>(touchPoints_.size()) >= fingers_) {
        currentAngle_ = ComputeAngle();
    }
    time_ = event.time;

    if (refereeState_ == RefereeState::DETECTING) {
        double diffAngle = fabs((currentAngle_ - initialAngle_));
        if (GreatOrEqual(diffAngle, angle_)) {
            resultAngle_ = ChangeValueRange(currentAngle_ - initialAngle_);
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
    } else if (refereeState_ == RefereeState::SUCCEED) {
        resultAngle_ = ChangeValueRange(currentAngle_ - initialAngle_);
        SendCallbackMsg(onActionUpdate_);
    }
}

void RotationRecognizer::HandleTouchCancelEvent(const TouchEvent& /*event*/)
{
    TAG_LOGD(AceLogTag::ACE_GESTURE_RECOGNIZER, "Rotation recognizer receives touch cancel event");
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCancelMsg();
    }
}

double RotationRecognizer::ComputeAngle()
{
    double fx = touchPoints_[0].x;
    double fy = touchPoints_[0].y;
    double sx = touchPoints_[1].x;
    double sy = touchPoints_[1].y;
    double angle = atan2(fy - sy, fx - sx) * 180.0 / M_PI;
    return angle;
}

// Map the value range to -180 to 180
double RotationRecognizer::ChangeValueRange(double value)
{
    double result = 0.0;
    if (LessOrEqual(value, -180.0)) {
        result = value + 360.0;
    } else if (GreatNotEqual(value, 180.0)) {
        result = value - 360.0;
    } else {
        result = value;
    }

    return result;
}

void RotationRecognizer::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    initialAngle_ = 0.0;
    currentAngle_ = 0.0;
    resultAngle_ = 0.0;
}

void RotationRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback)
{
    if (callback && *callback) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        UpdateFingerListInfo(coordinateOffset_);
        info.SetFingerList(fingerList_);
        info.SetAngle(resultAngle_);
        info.SetDeviceId(deviceId_);
        info.SetSourceDevice(deviceType_);
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
        if (recognizerTarget_.has_value()) {
            info.SetTarget(recognizerTarget_.value());
        }
        TouchEvent touchPoint = {};
        if (!touchPoints_.empty()) {
            touchPoint = touchPoints_.begin()->second;
        }
        info.SetForce(touchPoint.force);
        if (touchPoint.tiltX.has_value()) {
            info.SetTiltX(touchPoint.tiltX.value());
        }
        if (touchPoint.tiltY.has_value()) {
            info.SetTiltY(touchPoint.tiltY.value());
        }
        info.SetSourceTool(touchPoint.sourceTool);
        // callback may be overwritten in its invoke so we copy it first
        auto callbackFunction = *callback;
        callbackFunction(info);
    }
}

bool RotationRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    RefPtr<RotationRecognizer> curr = AceType::DynamicCast<RotationRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (curr->fingers_ != fingers_ || !NearEqual(curr->angle_, angle_) || curr->priorityMask_ != priorityMask_) {
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