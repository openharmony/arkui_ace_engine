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

#include "core/gestures/slide_recognizer.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace {

namespace {

constexpr int32_t MAX_SLIDE_FINGERS = 10;
constexpr int32_t AXIS_SLIDE_FINGERS = 1;
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

} // namespace

void SlideRecognizer::OnAccepted()
{
    if (slidingEnd_) {
        Reset();
    } else if (slidingCancel_) {
        SendCallbackMsg(onActionCancel_);
        Reset();
    }
}

void SlideRecognizer::OnRejected()
{
    Reset();
}

void SlideRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    fingers_ = newFingers_;
    speed_ = newSpeed_;
    direction_ = newDirection_;

    if (fingers_ > MAX_SLIDE_FINGERS) {
        return;
    }

    if (direction_.type == SwipeDirection::NONE) {
        return;
    }

    touchPoints_[event.id] = event;
    lastTouchEvent_ = event;
    fingersDistance_[event.id] = Offset();
    touchDownTime_ = event.time;

    if (state_ == DetectState::READY) {
        AddToReferee(event.id, AceType::Claim(this));
        if (static_cast<int32_t>(refereePointers_.size()) == fingers_) {
            initialAngle_ = ComputeAngle();
            state_ = DetectState::DETECTING;
        }
    }
}

void SlideRecognizer::HandleTouchDownEvent(const AxisEvent& event)
{
    fingers_ = newFingers_;
    speed_ = newSpeed_;
    direction_ = newDirection_;

    if (fingers_ != AXIS_SLIDE_FINGERS) {
        return;
    }

    if (direction_.type == SwipeDirection::NONE) {
        return;
    }

    axisEventStart_ = event;
    axisVerticalTotal_ = 0.0;
    axisHorizontalTotal_ = 0.0;
    touchDownTime_ = event.time;

    if (state_ == DetectState::READY) {
        initialAngle_ = ComputeAngle(event);
        state_ = DetectState::DETECTING;
    }
}

void SlideRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    auto itr = touchPoints_.find(event.id);
    if (itr == touchPoints_.end()) {
        return;
    }
    auto itf = fingersDistance_.find(event.id);
    if (itf == fingersDistance_.end()) {
        return;
    }

    globalPoint_ = Point(event.x, event.y);
    lastTouchEvent_ = event;
    touchPoints_.erase(itr);
    auto distanceData = fingersDistance_;
    fingersDistance_.erase(itf);
    if (state_ == DetectState::READY) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (state_ == DetectState::DETECTING) {
        size_t inRefereeNum = refereePointers_.size();
        bool inReferee = IsInReferee(static_cast<size_t>(event.id));
        if (inReferee) {
            inRefereeNum--;
        }

        if (static_cast<int32_t>(touchPoints_.size()) < fingers_ || inRefereeNum < 1) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return;
        }

        if (inReferee) {
            DelFromReferee(event.id, AceType::Claim(this));
        }
        return;
    }

    if (static_cast<int32_t>(touchPoints_.size()) <= fingers_) {
        if (refereeState_ == RefereeState::SUCCEED) {
            double averageSpeed = 0.0;
            bool isAvailable = true;
            for (const auto& element : distanceData) {
                Offset offset = element.second;
                double distance = 0.0;
                if ((direction_.type & SwipeDirection::ALL) == SwipeDirection::ALL) {
                    distance = offset.GetDistance();
                } else {
                    if ((direction_.type & SwipeDirection::HORIZONTAL) != 0) {
                        distance = std::abs(offset.GetX());
                    } else if ((direction_.type & SwipeDirection::VERTICAL) != 0) {
                        distance = std::abs(offset.GetY());
                    }
                }
                auto slidingTime = event.time - touchDownTime_;
                auto duration_ms =
                    std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(slidingTime);
                double slidingSpeed = (distance / duration_ms.count()) * 1000;
                if (speed_ >= slidingSpeed) {
                    isAvailable = false;
                    break;
                }
                averageSpeed += slidingSpeed;
            }
            if (isAvailable) {
                resultSpeed_ = averageSpeed / distanceData.size();
                SendCallbackMsg(onAction_);
            }
            Reset();
        } else {
            slidingEnd_ = true;
        }
    }
}

void SlideRecognizer::HandleTouchUpEvent(const AxisEvent& event)
{
    if (fingers_ != AXIS_SLIDE_FINGERS) {
        return;
    }
    globalPoint_ = Point(event.x, event.y);
    if (state_ == DetectState::READY) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (state_ == DetectState::DETECTING) {
        return;
    }

    auto slidingTime = event.time - touchDownTime_;
    auto duration_ms =
        std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, RATIO_US_TO_MS>>>(slidingTime);
    double verticalMoveTotal = axisVerticalTotal_ * DP_PER_LINE_DESKTOP * LINE_NUMBER_DESKTOP / MOUSE_WHEEL_DEGREES;
    double horizontalMoveTotal = axisHorizontalTotal_ * DP_PER_LINE_DESKTOP * LINE_NUMBER_DESKTOP / MOUSE_WHEEL_DEGREES;
    resultSpeed_ = Offset(horizontalMoveTotal, verticalMoveTotal).GetDistance() / duration_ms.count() * RATIO_MS_TO_S;
    if (resultSpeed_ > speed_) {
        SendCallbackMsg(onAction_);
    }
    Reset();
}

void SlideRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    auto itr = touchPoints_.find(event.id);
    if (itr == touchPoints_.end()) {
        return;
    }
    auto itf = fingersDistance_.find(event.id);
    if (itf == fingersDistance_.end()) {
        return;
    }
    globalPoint_ = Point(event.x, event.y);
    lastTouchEvent_ = event;
    if (state_ == DetectState::READY) {
        touchPoints_[event.id] = event;
        return;
    }

    Offset moveDistance = event.GetOffset() - touchPoints_[event.id].GetOffset();
    fingersDistance_[event.id] = itf->second + moveDistance;
    touchPoints_[event.id] = event;
    currentAngle_ = ComputeAngle();
    time_ = event.time;

    if (state_ == DetectState::DETECTING) {
        double diffAngle = fabs((currentAngle_ - initialAngle_));
        if (GreatOrEqual(diffAngle, angle_)) {
            resultAngle_ = ChangeValueRange(currentAngle_ - initialAngle_);
        }
        auto result = ParseFingersOffset();
        if (result == GestureAcceptResult::ACCEPT) {
            state_ = DetectState::DETECTED;
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        } else if (result == GestureAcceptResult::REJECT) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    } else if (state_ == DetectState::DETECTED && refereeState_ == RefereeState::SUCCEED) {
        resultAngle_ = ChangeValueRange(currentAngle_ - initialAngle_);
    }
}

void SlideRecognizer::HandleTouchMoveEvent(const AxisEvent& event)
{
    if (fingers_ != AXIS_SLIDE_FINGERS) {
        return;
    }
    globalPoint_ = Point(event.x, event.y);
    if (state_ == DetectState::READY) {
        axisEventStart_ = event;
        return;
    }

    axisVerticalTotal_ += fabs(event.verticalAxis);
    axisHorizontalTotal_ += fabs(event.horizontalAxis);
    currentAngle_ = ComputeAngle(event);
    time_ = event.time;

    if (state_ == DetectState::DETECTING) {
        if (GreatOrEqual(fabs(currentAngle_), angle_)) {
            resultAngle_ = ChangeValueRange(currentAngle_);
        }
        auto result = ParseAxisOffset();
        if (result == GestureAcceptResult::ACCEPT) {
            state_ = DetectState::DETECTED;
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        } else if (result == GestureAcceptResult::REJECT) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    } else if (state_ == DetectState::DETECTED) {
        resultAngle_ = ChangeValueRange(currentAngle_);
    }
}

void SlideRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    if (state_ == DetectState::READY || state_ == DetectState::DETECTING) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onActionCancel_);
        Reset();
    } else {
        slidingCancel_ = true;
    }
}

void SlideRecognizer::HandleTouchCancelEvent(const AxisEvent& event)
{
    SendCallbackMsg(onActionCancel_);
    Reset();
}

SlideRecognizer::GestureAcceptResult SlideRecognizer::ParseFingersOffset() const
{
    if ((direction_.type & SwipeDirection::ALL) == SwipeDirection::ALL) {
        for (const auto& element : fingersDistance_) {
            Offset offset = element.second;
            double distance = offset.GetDistance();
            if (fabs(distance) < DEFAULT_SLIDE_DISTANCE.ConvertToPx()) {
                return GestureAcceptResult::DETECTING;
            }
        }
        return GestureAcceptResult::ACCEPT;
    }

    for (const auto& element : fingersDistance_) {
        Offset offset = element.second;
        if (fabs(offset.GetX()) > fabs(offset.GetY())) {
            if ((direction_.type & SwipeDirection::HORIZONTAL) != 0) {
                double offsetX = offset.GetX();
                if (fabs(offsetX) < DEFAULT_SLIDE_DISTANCE.ConvertToPx()) {
                    return GestureAcceptResult::DETECTING;
                }
            } else {
                return GestureAcceptResult::REJECT;
            }
        } else {
            if ((direction_.type & SwipeDirection::VERTICAL) != 0) {
                double offsetY = offset.GetY();
                if (fabs(offsetY) < DEFAULT_SLIDE_DISTANCE.ConvertToPx()) {
                    return GestureAcceptResult::DETECTING;
                }
            } else {
                return GestureAcceptResult::REJECT;
            }
        }
    }

    return GestureAcceptResult::ACCEPT;
}

SlideRecognizer::GestureAcceptResult SlideRecognizer::ParseAxisOffset() const
{
    if ((direction_.type & SwipeDirection::ALL) == SwipeDirection::ALL) {
        double distance = Offset(axisHorizontalTotal_, axisVerticalTotal_).GetDistance();
        if (fabs(distance) < DEFAULT_SLIDE_DISTANCE.ConvertToPx()) {
            return GestureAcceptResult::DETECTING;
        }
        return GestureAcceptResult::ACCEPT;
    }

    if (axisHorizontalTotal_ > axisVerticalTotal_) {
        if ((direction_.type & SwipeDirection::HORIZONTAL) != 0) {
            if (axisHorizontalTotal_ < DEFAULT_SLIDE_DISTANCE.ConvertToPx()) {
                return GestureAcceptResult::DETECTING;
            }
        } else {
            return GestureAcceptResult::REJECT;
        }
    } else {
        if ((direction_.type & SwipeDirection::VERTICAL) != 0) {
            if (axisVerticalTotal_ < DEFAULT_SLIDE_DISTANCE.ConvertToPx()) {
                return GestureAcceptResult::DETECTING;
            }
        } else {
            return GestureAcceptResult::REJECT;
        }
    }

    return GestureAcceptResult::ACCEPT;
}

void SlideRecognizer::Reset()
{
    axisHorizontalTotal_ = 0.0;
    axisVerticalTotal_ = 0.0;
    touchPoints_.clear();
    fingersDistance_.clear();
    resultSpeed_ = 0.0;
    state_ = DetectState::READY;
    slidingEnd_ = false;
    slidingCancel_ = false;
}

void SlideRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback)
{
    if (callback && *callback) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        info.SetGlobalPoint(globalPoint_);
        info.SetAngle(resultAngle_);
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

bool SlideRecognizer::ReconcileFrom(const RefPtr<GestureRecognizer>& recognizer)
{
    RefPtr<SlideRecognizer> curr = AceType::DynamicCast<SlideRecognizer>(recognizer);
    if (!curr) {
        Reset();
        return false;
    }

    if (curr->fingers_ != fingers_ || !NearEqual(curr->angle_, angle_) || curr->priorityMask_ != priorityMask_) {
        Reset();
        return false;
    }

    direction_.type = curr->direction_.type;
    newDirection_.type = curr->newDirection_.type;
    speed_ = curr->speed_;
    newSpeed_ = curr->newSpeed_;

    onAction_ = std::move(curr->onAction_);

    return true;
}

void SlideRecognizer::ChangeFingers(int32_t fingers)
{
    if (fingers_ != fingers) {
        newFingers_ = fingers;
    }
}

void SlideRecognizer::ChangeDirection(const SwipeDirection& direction)
{
    if (direction_.type != direction.type) {
        direction_.type = direction.type;
        newDirection_.type = direction.type;
    }
}

void SlideRecognizer::ChangeSpeed(double speed)
{
    if (speed_ != speed) {
        if (state_ == DetectState::READY || state_ == DetectState::DETECTING) {
            speed_ = speed;
        }
        newSpeed_ = speed;
    }
}

double SlideRecognizer::ComputeAngle()
{
    double fx = touchPoints_[0].x;
    double fy = touchPoints_[0].y;
    double sx = touchPoints_[1].x;
    double sy = touchPoints_[1].y;
    return atan2(fy - sy, fx - sx) * ANGLE_SUM_OF_TRIANGLE / ACE_PI;
}

double SlideRecognizer::ComputeAngle(AxisEvent event)
{
    return atan2(event.verticalAxis, event.horizontalAxis) * ANGLE_SUM_OF_TRIANGLE / ACE_PI;
}

} // namespace OHOS::Ace
