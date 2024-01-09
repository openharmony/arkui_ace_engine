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
#include "core/components_ng/gestures/base_gesture_event.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t MAX_ROTATION_FINGERS = 5;
constexpr int32_t DEFAULT_ROTATION_FINGERS = 2;
constexpr double ONE_CIRCLE = 360.0;
constexpr double QUARTER_CIRCLE = 90.0;

} // namespace

RotationRecognizer::RotationRecognizer(int32_t fingers, double angle) : MultiFingersRecognizer(fingers), angle_(angle)
{
    if (fingers_ > MAX_ROTATION_FINGERS || fingers_ < DEFAULT_ROTATION_FINGERS) {
        fingers_ = DEFAULT_ROTATION_FINGERS;
    }
}

void RotationRecognizer::OnAccepted()
{
    auto node = GetAttachedNode().Upgrade();
    TAG_LOGI(AceLogTag::ACE_GESTURE, "Rotation gesture has been accepted, node tag = %{public}s, id = %{public}s",
        node ? node->GetTag().c_str() : "null", node ? std::to_string(node->GetId()).c_str() : "invalid");
    refereeState_ = RefereeState::SUCCEED;
    SendCallbackMsg(onActionStart_);
}

void RotationRecognizer::OnRejected()
{
    TAG_LOGI(AceLogTag::ACE_GESTURE, "Rotation gesture has been rejected");
    if (refereeState_ != RefereeState::SUCCEED) {
        refereeState_ = RefereeState::FAIL;
    }
}

void RotationRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    if (static_cast<int32_t>(activeFingers_.size()) >= DEFAULT_ROTATION_FINGERS) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_GESTURE, "Rotation recognizer receives touch down event, begin to detect rotation event");
    if (fingers_ > MAX_ROTATION_FINGERS) {
        fingers_ = DEFAULT_ROTATION_FINGERS;
    }

    activeFingers_.emplace_back(event.id);
    touchPoints_[event.id] = event;

    if (static_cast<int32_t>(activeFingers_.size()) >= DEFAULT_ROTATION_FINGERS) {
        initialAngle_ = ComputeAngle();
        refereeState_ = RefereeState::DETECTING;
    }
}

void RotationRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    if (!IsActiveFinger(event.id)) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_GESTURE, "Rotation recognizer receives touch up event");
    if (static_cast<int32_t>(activeFingers_.size()) < DEFAULT_ROTATION_FINGERS &&
        refereeState_ != RefereeState::SUCCEED) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED &&
        static_cast<int32_t>(activeFingers_.size()) == DEFAULT_ROTATION_FINGERS) {
        SendCallbackMsg(onActionEnd_);
    }
    activeFingers_.remove(event.id);
}

void RotationRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    if (!IsActiveFinger(event.id) || currentFingers_ < fingers_) {
        lastAngle_ = 0.0;
        angleSignChanged_ = false;
        return;
    }
    touchPoints_[event.id] = event;
    if (static_cast<int32_t>(activeFingers_.size()) < DEFAULT_ROTATION_FINGERS) {
        lastAngle_ = 0.0;
        angleSignChanged_ = false;
        return;
    }
    currentAngle_ = ComputeAngle();
    time_ = event.time;

    if (refereeState_ == RefereeState::DETECTING) {
        auto trueAngle = currentAngle_;
        if (currentAngle_ * lastAngle_ < 0 && fabs(currentAngle_) > QUARTER_CIRCLE) {
            angleSignChanged_ = !angleSignChanged_;
        }
        if (angleSignChanged_) {
            if (initialAngle_ > 0.0) {
                trueAngle += ONE_CIRCLE;
            } else {
                trueAngle -= ONE_CIRCLE;
            }
        }
        lastAngle_ = currentAngle_;
        double diffAngle = fabs((trueAngle - initialAngle_));
        if (GreatOrEqual(diffAngle, angle_)) {
            lastAngle_ = 0.0;
            angleSignChanged_ = false;
            resultAngle_ = ChangeValueRange(currentAngle_ - initialAngle_);
            auto onGestureJudgeBeginResult = TriggerGestureJudgeCallback();
            if (onGestureJudgeBeginResult == GestureJudgeResult::REJECT) {
                Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
                return;
            }
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
    } else if (refereeState_ == RefereeState::SUCCEED) {
        lastAngle_ = 0.0;
        angleSignChanged_ = false;
        resultAngle_ = ChangeValueRange(currentAngle_ - initialAngle_);
        SendCallbackMsg(onActionUpdate_);
    }
}

void RotationRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    if (!IsActiveFinger(event.id)) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_GESTURE, "Rotation recognizer receives touch cancel event");
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
    auto sId = activeFingers_.begin();
    auto fId = sId++;

    double fx = touchPoints_[*fId].x;
    double fy = touchPoints_[*fId].y;
    double sx = touchPoints_[*sId].x;
    double sy = touchPoints_[*sId].y;
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
    lastAngle_ = 0.0;
    angleSignChanged_ = false;
}

void RotationRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback)
{
    if (callback && *callback) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        UpdateFingerListInfo();
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

GestureJudgeResult RotationRecognizer::TriggerGestureJudgeCallback()
{
    auto targetComponent = GetTargetComponent();
    CHECK_NULL_RETURN(targetComponent, GestureJudgeResult::CONTINUE);
    auto callback = targetComponent->GetOnGestureJudgeBeginCallback();
    CHECK_NULL_RETURN(callback, GestureJudgeResult::CONTINUE);
    auto info = std::make_shared<RotationGestureEvent>();
    info->SetTimeStamp(time_);
    UpdateFingerListInfo();
    info->SetFingerList(fingerList_);
    info->SetAngle(resultAngle_);
    info->SetSourceDevice(deviceType_);
    info->SetTarget(GetEventTarget().value_or(EventTarget()));
    if (recognizerTarget_.has_value()) {
        info->SetTarget(recognizerTarget_.value());
    }
    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    info->SetForce(touchPoint.force);
    if (touchPoint.tiltX.has_value()) {
        info->SetTiltX(touchPoint.tiltX.value());
    }
    if (touchPoint.tiltY.has_value()) {
        info->SetTiltY(touchPoint.tiltY.value());
    }
    info->SetSourceTool(touchPoint.sourceTool);
    return callback(gestureInfo_, info);
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
