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

#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"

#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_SWIPE_FINGERS = 10;
constexpr int32_t RATIO_MS_TO_S = 1000;
constexpr int32_t RATIO_US_TO_MS = 1000;
constexpr double ANGLE_SUM_OF_TRIANGLE = 180.0;

double ChangeValueRange(double value)
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

double ComputeAngle(double x, double y)
{
    return ChangeValueRange(atan2(y, x) * ANGLE_SUM_OF_TRIANGLE / M_PI);
}
} // namespace

void SwipeRecognizer::OnAccepted()
{
    refereeState_ = RefereeState::SUCCEED;
    SendCallbackMsg(onAction_);
}

void SwipeRecognizer::OnRejected()
{
    LOGD("swipe gesture has been rejected!");
    refereeState_ = RefereeState::FAIL;
}

void SwipeRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    LOGD("swipe recognizer receives touch down event, begin to detect swipe event");
    if (fingers_ > MAX_SWIPE_FINGERS) {
        LOGW("the fingers is larger than max");
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (direction_.type == SwipeDirection::NONE) {
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    touchPoints_[event.id] = event;
    downEvents_[event.id] = event;
    time_ = event.time;
    lastTouchEvent_ = event;

    if (static_cast<int32_t>(touchPoints_.size()) > fingers_) {
        LOGW("the finger is larger than the defined finger");
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (static_cast<int32_t>(touchPoints_.size()) == fingers_) {
        touchDownTime_ = event.time;
        refereeState_ = RefereeState::DETECTING;
    }
}

void SwipeRecognizer::HandleTouchDownEvent(const AxisEvent& event)
{
    LOGD("swipe recognizer receives touch down event, begin to detect swipe event");
    if (direction_.type == SwipeDirection::NONE) {
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    axisEventStart_ = event;
    axisVerticalTotal_ = 0.0;
    axisHorizontalTotal_ = 0.0;
    touchDownTime_ = event.time;
    time_ = event.time;
    refereeState_ = RefereeState::DETECTING;
}

void SwipeRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    LOGD("swipe recognizer receives touch up event");
    globalPoint_ = Point(event.x, event.y);
    time_ = event.time;
    lastTouchEvent_ = event;
    if ((refereeState_ != RefereeState::DETECTING) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::DETECTING) {
        auto offset = event.GetOffset() - touchPoints_[event.id].GetOffset();
        // nanoseconds duration to seconds.
        std::chrono::duration<double> duration = event.time - touchDownTime_;
        auto seconds = duration.count();
        resultSpeed_ = offset.GetDistance() / seconds;
        if (resultSpeed_ < speed_) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        } else {
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
    }
}

void SwipeRecognizer::HandleTouchUpEvent(const AxisEvent& event)
{
    LOGD("swipe recognizer receives touch up event");
    globalPoint_ = Point(event.x, event.y);
    time_ = event.time;
    if ((refereeState_ != RefereeState::DETECTING) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::DETECTING) {
        auto slidingTime = event.time - touchDownTime_;
        auto duration_ms =
            std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, RATIO_US_TO_MS>>>(slidingTime);
        double verticalMoveTotal = axisVerticalTotal_ * DP_PER_LINE_DESKTOP * LINE_NUMBER_DESKTOP / MOUSE_WHEEL_DEGREES;
        double horizontalMoveTotal =
            axisHorizontalTotal_ * DP_PER_LINE_DESKTOP * LINE_NUMBER_DESKTOP / MOUSE_WHEEL_DEGREES;
        resultSpeed_ =
            Offset(horizontalMoveTotal, verticalMoveTotal).GetDistance() / duration_ms.count() * RATIO_MS_TO_S;
        if (resultSpeed_ < speed_) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        } else {
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
    }
}

void SwipeRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    LOGD("swipe recognizer receives touch move event");
    globalPoint_ = Point(event.x, event.y);
    time_ = event.time;
    lastTouchEvent_ = event;
    Offset moveDistance = event.GetOffset() - touchPoints_[event.id].GetOffset();
    touchPoints_[event.id] = event;
    if (refereeState_ == RefereeState::DETECTING) {
        double newAngle = ComputeAngle(moveDistance.GetX(), moveDistance.GetY());
        if (CheckAngle(newAngle)) {
            prevAngle_ = newAngle;
            return;
        }
        Adjudicate(Claim(this), GestureDisposal::REJECT);
    }
}

void SwipeRecognizer::HandleTouchMoveEvent(const AxisEvent& event)
{
    LOGD("swipe recognizer receives axis move event");
    globalPoint_ = Point(event.x, event.y);
    time_ = event.time;
    axisVerticalTotal_ += fabs(event.verticalAxis);
    axisHorizontalTotal_ += fabs(event.horizontalAxis);
}

void SwipeRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    LOGD("swipe recognizer receives touch cancel event");
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        LOGD("cancel swipe gesture detect, try to reject it");
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCancelMsg();
    }
}

void SwipeRecognizer::HandleTouchCancelEvent(const AxisEvent& event)
{
    HandleTouchCancelEvent(TouchEvent());
}

bool SwipeRecognizer::CheckAngle(double angle)
{
    const double angleDiffDuration = 15;
    const double axisDiffDuration = 45;
    if (prevAngle_.has_value()) {
        if (std::abs(prevAngle_.value() - angle) > angleDiffDuration) {
            return false;
        }
    }
    if ((direction_.type & SwipeDirection::HORIZONTAL) == SwipeDirection::HORIZONTAL) {
        if (std::abs(angle) > axisDiffDuration) {
            return false;
        }
    }
    if ((direction_.type & SwipeDirection::VERTICAL) == SwipeDirection::HORIZONTAL) {
        const double axisVertical = 90;
        if (std::abs(angle - axisVertical) > axisDiffDuration) {
            return false;
        }
    }
    return true;
}

void SwipeRecognizer::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    axisHorizontalTotal_ = 0.0;
    axisVerticalTotal_ = 0.0;
    resultSpeed_ = 0.0;
}

void SwipeRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback)
{
    if (callback && *callback) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        info.SetGlobalPoint(globalPoint_);
        if (deviceType_ == SourceType::MOUSE) {
            info.SetSpeed(0.0);
        } else {
            info.SetSpeed(resultSpeed_);
        }
        info.SetSourceDevice(deviceType_);
        info.SetDeviceId(deviceId_);
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
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

bool SwipeRecognizer::ReconcileFrom(const RefPtr<GestureRecognizer>& recognizer)
{
    RefPtr<SwipeRecognizer> curr = AceType::DynamicCast<SwipeRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (curr->fingers_ != fingers_ || (curr->direction_.type != direction_.type) || !NearZero(curr->speed_ - speed_)) {
        ResetStatus();
        return false;
    }

    onAction_ = std::move(curr->onAction_);
    return true;
}

} // namespace OHOS::Ace::NG
