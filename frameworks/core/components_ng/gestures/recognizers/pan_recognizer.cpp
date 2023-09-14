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

#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include <map>

#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/event/axis_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t MAX_PAN_FINGERS = 10;
constexpr int32_t DEFAULT_PAN_FINGERS = 1;
constexpr Dimension DISTANCE_PER_MOUSE_DEGREE = LINE_HEIGHT_DESKTOP * LINE_NUMBER_DESKTOP / MOUSE_WHEEL_DEGREES;
constexpr int32_t AXIS_PAN_FINGERS = 1;

} // namespace

PanRecognizer::PanRecognizer(int32_t fingers, const PanDirection& direction, double distance)
    : MultiFingersRecognizer(fingers), direction_(direction), distance_(distance), mouseDistance_(distance),
      newFingers_(fingers_), newDistance_(distance_), newDirection_(direction_)
{
    if ((direction_.type & PanDirection::VERTICAL) == 0) {
        velocityTracker_ = VelocityTracker(Axis::HORIZONTAL);
    } else if ((direction_.type & PanDirection::HORIZONTAL) == 0) {
        velocityTracker_ = VelocityTracker(Axis::VERTICAL);
    }
    if (fingers_ > MAX_PAN_FINGERS || fingers_ < DEFAULT_PAN_FINGERS) {
        LOGW("panRecognizer fingers_ is illegal, change to DEFAULT_PAN_FINGERS.");
        fingers_ = DEFAULT_PAN_FINGERS;
    }
}

PanRecognizer::PanRecognizer(const RefPtr<PanGestureOption>& panGestureOption) : panGestureOption_(panGestureOption)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    uint32_t directNum = panGestureOption->GetDirection().type;
    double distanceNumber = panGestureOption->GetDistance();
    int32_t fingersNumber = panGestureOption->GetFingers();

    distance_ = LessNotEqual(distanceNumber, 0.0) ? DEFAULT_PAN_DISTANCE.ConvertToPx() : distanceNumber;
    fingers_ = fingersNumber;
    if (fingers_ > MAX_PAN_FINGERS || fingers_ < DEFAULT_PAN_FINGERS) {
        LOGW("panRecognizer fingers_ is illegal, change to DEFAULT_PAN_FINGERS.");
        fingers_ = DEFAULT_PAN_FINGERS;
    }

    if (directNum >= PanDirection::NONE && directNum <= PanDirection::ALL) {
        direction_.type = directNum;
    }

    newFingers_ = fingers_;
    newDistance_ = distance_;
    mouseDistance_ = distance_;
    newDirection_ = direction_;

    PanFingersFuncType changeFingers = [weak = AceType::WeakClaim(this)](int32_t fingers) {
        auto panRecognizer = weak.Upgrade();
        CHECK_NULL_VOID(panRecognizer);
        panRecognizer->ChangeFingers(fingers);
    };
    onChangeFingers_ = OnPanFingersFunc(changeFingers);
    panGestureOption_->SetOnPanFingersId(onChangeFingers_);

    PanDirectionFuncType changeDirection = [weak = AceType::WeakClaim(this)](const PanDirection& direction) {
        auto panRecognizer = weak.Upgrade();
        CHECK_NULL_VOID(panRecognizer);
        panRecognizer->ChangeDirection(direction);
    };
    onChangeDirection_ = OnPanDirectionFunc(changeDirection);
    panGestureOption_->SetOnPanDirectionId(onChangeDirection_);

    PanDistanceFuncType changeDistance = [weak = AceType::WeakClaim(this)](double distance) {
        auto panRecognizer = weak.Upgrade();
        CHECK_NULL_VOID(panRecognizer);
        panRecognizer->ChangeDistance(distance);
    };
    onChangeDistance_ = OnPanDistanceFunc(changeDistance);
    panGestureOption_->SetOnPanDistanceId(onChangeDistance_);
}

void PanRecognizer::OnAccepted()
{
    refereeState_ = RefereeState::SUCCEED;
    SendCallbackMsg(onActionStart_);
    SendCallbackMsg(onActionUpdate_);
}

void PanRecognizer::OnRejected()
{
    LOGD("pan gesture has been rejected!");
    // fix griditem drag interrupted by click while pull moving
    if (refereeState_ != RefereeState::SUCCEED) {
        refereeState_ = RefereeState::FAIL;
    }
}

void PanRecognizer::UpdateTouchPointInVelocityTracker(const TouchEvent& event, bool end)
{
    PointF originPoint(event.x, event.y);
    PointF windowPoint = originPoint;
    Transform(windowPoint, originPoint);

    TouchEvent transformEvent = event;
    transformEvent.x = windowPoint.GetX();
    transformEvent.y = windowPoint.GetY();
    velocityTracker_.UpdateTouchPoint(transformEvent, end);
}

void PanRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    LOGI("pan recognizer receives %{public}d touch down event, begin to detect pan event", event.id);
    fingers_ = newFingers_;
    distance_ = newDistance_;
    direction_ = newDirection_;

    if (direction_.type == PanDirection::NONE) {
        LOGI("the direction type is none");
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }
    if (event.sourceType == SourceType::MOUSE && !isAllowMouse_) {
        LOGI("mouse pan is not allowed");
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    deviceId_ = event.deviceId;
    deviceType_ = event.sourceType;
    lastTouchEvent_ = event;
    touchPoints_[event.id] = event;
    touchPointsDistance_[event.id] = Offset(0.0, 0.0);
    if (event.sourceType == SourceType::MOUSE) {
        inputEventType_ = InputEventType::MOUSE_BUTTON;
    } else {
        inputEventType_ = InputEventType::TOUCH_SCREEN;
    }

    auto fingerNum = static_cast<int32_t>(touchPoints_.size());

    if (fingerNum == fingers_) {
        velocityTracker_.Reset();
        UpdateTouchPointInVelocityTracker(event);
        refereeState_ = RefereeState::DETECTING;
    }
}

void PanRecognizer::HandleTouchDownEvent(const AxisEvent& event)
{
    LOGI("pan recognizer receives axis start event, begin to detect pan event");
    fingers_ = newFingers_;
    distance_ = newDistance_;
    direction_ = newDirection_;

    if (fingers_ != AXIS_PAN_FINGERS) {
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (direction_.type == PanDirection::NONE) {
        LOGI("the direction type is none");
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    touchPoints_[event.id] = TouchEvent();
    touchPoints_[event.id].id = event.id;
    touchPoints_[event.id].x = event.x;
    touchPoints_[event.id].y = event.y;
    touchPoints_[event.id].sourceType = event.sourceType;
    touchPoints_[event.id].sourceTool = event.sourceTool;
    deviceId_ = event.deviceId;
    deviceType_ = event.sourceType;
    lastAxisEvent_ = event;
    inputEventType_ = InputEventType::AXIS;
    refereeState_ = RefereeState::DETECTING;
}

void PanRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    LOGI("pan recognizer receives %{public}d touch up event", event.id);
    if (currentFingers_ < fingers_) {
        LOGW("PanGesture current finger number is less than requiried finger number.");
        return;
    }
    globalPoint_ = Point(event.x, event.y);
    lastTouchEvent_ = event;
    UpdateTouchPointInVelocityTracker(event, true);

    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
#ifdef ENABLE_DRAG_FRAMEWORK
        if (isForDrag_ && onActionCancel_ && *onActionCancel_) {
            (*onActionCancel_)();
        }
#endif // ENABLE_DRAG_FRAMEWORK
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        if (static_cast<int32_t>(touchPoints_.size()) == 1) {
            ResSchedReport::GetInstance().ResSchedDataReport("click");
            // last one to fire end.
            SendCallbackMsg(onActionEnd_);
        }
    }
}

void PanRecognizer::HandleTouchUpEvent(const AxisEvent& event)
{
    LOGI("pan recognizer receives axis end event");
    globalPoint_ = Point(event.x, event.y);
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        // AxisEvent is single one.
        SendCallbackMsg(onActionEnd_);
    }
}

void PanRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    LOGD("pan recognizer receives touch move event");
    if (currentFingers_ < fingers_) {
        LOGW("PanGesture current finger number is less than requiried finger number.");
        return;
    }
    globalPoint_ = Point(event.x, event.y);
    lastTouchEvent_ = event;
    PointF originPoint(event.GetOffset().GetX(), event.GetOffset().GetY());
    PointF originTouchPoint(touchPoints_[event.id].GetOffset().GetX(), touchPoints_[event.id].GetOffset().GetY());
    PointF windowPoint = originPoint;
    PointF windowTouchPoint = originTouchPoint;
    Transform(windowPoint, originPoint);
    Transform(windowTouchPoint, originTouchPoint);
    delta_ =
        (Offset(windowPoint.GetX(), windowPoint.GetY()) - Offset(windowTouchPoint.GetX(), windowTouchPoint.GetY()));
    mainDelta_ = GetMainAxisDelta();
    UpdateTouchPointInVelocityTracker(event);
    averageDistance_ += delta_;
    touchPoints_[event.id] = event;
    touchPointsDistance_[event.id] += delta_;
    time_ = event.time;

    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        return;
    }
    if (refereeState_ == RefereeState::DETECTING) {
        auto result = IsPanGestureAccept();
        if (result == GestureAcceptResult::ACCEPT) {
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        } else if (result == GestureAcceptResult::REJECT) {
            LOGW("pan recognizer reject");
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    } else if (refereeState_ == RefereeState::SUCCEED) {
        if ((direction_.type & PanDirection::VERTICAL) == 0) {
            averageDistance_.SetY(0.0);
            for (auto& element : touchPointsDistance_) {
                element.second.SetY(0.0);
            }
        } else if ((direction_.type & PanDirection::HORIZONTAL) == 0) {
            averageDistance_.SetX(0.0);
            for (auto& element : touchPointsDistance_) {
                element.second.SetX(0.0);
            }
        }
        LOGD("pan recognizer detected successful");
        if (isFlushTouchEventsEnd_) {
            SendCallbackMsg(onActionUpdate_);
        }
    }
}

void PanRecognizer::OnFlushTouchEventsBegin()
{
    isFlushTouchEventsEnd_ = false;
}

void PanRecognizer::OnFlushTouchEventsEnd()
{
    isFlushTouchEventsEnd_ = true;
}

void PanRecognizer::HandleTouchMoveEvent(const AxisEvent& event)
{
    LOGD("pan recognizer receives axis update event");
    if (fingers_ != AXIS_PAN_FINGERS) {
        return;
    }
    globalPoint_ = Point(event.x, event.y);
    auto distancePerMouseDegreePx = DISTANCE_PER_MOUSE_DEGREE.ConvertToPx();
    if (direction_.type == PanDirection::ALL || (direction_.type & PanDirection::HORIZONTAL) == 0) {
        // PanRecognizer Direction: Vertical or ALL
        delta_ =
            Offset(-event.horizontalAxis * distancePerMouseDegreePx, -event.verticalAxis * distancePerMouseDegreePx);
    } else if ((direction_.type & PanDirection::VERTICAL) == 0) {
        // PanRecognizer Direction: Horizontal
        if (NearZero(event.horizontalAxis)) {
            delta_ = Offset(-event.verticalAxis * distancePerMouseDegreePx, 0);
        } else {
            delta_ = Offset(
                -event.horizontalAxis * distancePerMouseDegreePx, -event.verticalAxis * distancePerMouseDegreePx);
        }
    }

    mainDelta_ = GetMainAxisDelta();
    averageDistance_ += delta_;
    lastAxisEvent_ = event;
    time_ = event.time;

    if (refereeState_ == RefereeState::DETECTING) {
        auto result = IsPanGestureAccept();
        if (result == GestureAcceptResult::ACCEPT) {
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        } else if (result == GestureAcceptResult::REJECT) {
            LOGW("pan recognizer reject");
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    } else if (refereeState_ == RefereeState::SUCCEED) {
        if ((direction_.type & PanDirection::VERTICAL) == 0) {
            averageDistance_.SetY(0.0);
        } else if ((direction_.type & PanDirection::HORIZONTAL) == 0) {
            averageDistance_.SetX(0.0);
        }

        LOGD("pan recognizer detected successful");
        SendCallbackMsg(onActionUpdate_);
    }
}

void PanRecognizer::HandleTouchCancelEvent(const TouchEvent& /*event*/)
{
    LOGD("pan recognizer receives touch cancel event");
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        // AxisEvent is single one.
        SendCancelMsg();
    }
}

void PanRecognizer::HandleTouchCancelEvent(const AxisEvent& /*event*/)
{
    LOGD("pan recognizer receives touch cancel event");
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCancelMsg();
    }
}

bool PanRecognizer::CalculateTruthFingers(bool isDirectionUp) const
{
    int32_t totalFingers = 0;
    float totalDistance = 0.0f;
    for (auto& element : touchPointsDistance_) {
        auto each_point_move = element.second.GetY();
        if (GreatNotEqual(each_point_move, 0.0) && isDirectionUp) {
            totalFingers++;
            totalDistance += each_point_move;
        } else if (LessNotEqual(each_point_move, 0.0) && !isDirectionUp) {
            totalFingers++;
            totalDistance -= each_point_move;
        }
    }
    auto judgeDistance = distance_;
    if (deviceType_ == SourceType::MOUSE) {
        judgeDistance = mouseDistance_;
    }
    return GreatNotEqual(totalDistance, judgeDistance) && totalFingers >= fingers_;
}

PanRecognizer::GestureAcceptResult PanRecognizer::IsPanGestureAccept() const
{
    auto judgeDistance = distance_;
    if (deviceType_ == SourceType::MOUSE) { // use mouseDistance_
        judgeDistance = mouseDistance_;
    }

    if ((direction_.type & PanDirection::ALL) == PanDirection::ALL) {
        double offset = averageDistance_.GetDistance();
        if (fabs(offset) < judgeDistance) {
            return GestureAcceptResult::DETECTING;
        }
        return GestureAcceptResult::ACCEPT;
    }

    if (fabs(averageDistance_.GetX()) > fabs(averageDistance_.GetY())) {
        if ((direction_.type & PanDirection::HORIZONTAL) != 0) {
            double offset = averageDistance_.GetX();
            if (fabs(offset) < judgeDistance) {
                return GestureAcceptResult::DETECTING;
            }
            if ((direction_.type & PanDirection::LEFT) == 0 && offset < 0) {
                return GestureAcceptResult::REJECT;
            }
            if ((direction_.type & PanDirection::RIGHT) == 0 && offset > 0) {
                return GestureAcceptResult::REJECT;
            }
            return GestureAcceptResult::ACCEPT;
        }
        return GestureAcceptResult::DETECTING;
    }
    if ((direction_.type & PanDirection::VERTICAL) != 0) {
        double offset = averageDistance_.GetY();
        if (fabs(offset) < judgeDistance) {
            return GestureAcceptResult::DETECTING;
        }
        if ((direction_.type & PanDirection::UP) == 0) {
            return CalculateTruthFingers(true) ? GestureAcceptResult::ACCEPT : GestureAcceptResult::REJECT;
        }
        if ((direction_.type & PanDirection::DOWN) == 0) {
            return CalculateTruthFingers(false) ? GestureAcceptResult::ACCEPT : GestureAcceptResult::REJECT;
        }
        return GestureAcceptResult::ACCEPT;
    }
    return GestureAcceptResult::DETECTING;
}

void PanRecognizer::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    touchPoints_.clear();
    averageDistance_.Reset();
    touchPointsDistance_.clear();
}

void PanRecognizer::OnSucceedCancel()
{
    SendCancelMsg();
}

void PanRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback)
{
    if (callback && *callback) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        UpdateFingerListInfo(coordinateOffset_);
        info.SetFingerList(fingerList_);
        info.SetOffsetX(averageDistance_.GetX());
        info.SetOffsetY(averageDistance_.GetY());
        TouchEvent touchPoint = {};
        if (!touchPoints_.empty()) {
            touchPoint = touchPoints_.begin()->second;
        }
#ifdef ENABLE_DRAG_FRAMEWORK
        info.SetPointerId(touchPoint.id);
#endif // ENABLE_DRAG_FRAMEWORK
        info.SetGlobalPoint(globalPoint_)
            .SetLocalLocation(Offset(globalPoint_.GetX(), globalPoint_.GetY()) - coordinateOffset_);
        info.SetDeviceId(deviceId_);
        info.SetSourceDevice(deviceType_);
        info.SetTargetDisplayId(touchPoint.targetDisplayId);
        info.SetDelta(delta_);
        info.SetMainDelta(mainDelta_);
        if (inputEventType_ == InputEventType::AXIS) {
            info.SetScreenLocation(lastAxisEvent_.GetScreenOffset());
            info.SetVelocity(Velocity());
            info.SetMainVelocity(0.0);
            info.SetSourceTool(lastAxisEvent_.sourceTool);
        } else {
            info.SetScreenLocation(lastTouchEvent_.GetScreenOffset());
            info.SetVelocity(velocityTracker_.GetVelocity());
            info.SetMainVelocity(velocityTracker_.GetMainAxisVelocity());
            info.SetSourceTool(lastTouchEvent_.sourceTool);
        }
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
        if (recognizerTarget_.has_value()) {
            info.SetTarget(recognizerTarget_.value());
        }
        info.SetInputEventType(inputEventType_);
        info.SetForce(lastTouchEvent_.force);
        if (lastTouchEvent_.tiltX.has_value()) {
            info.SetTiltX(lastTouchEvent_.tiltX.value());
        }
        if (lastTouchEvent_.tiltY.has_value()) {
            info.SetTiltY(lastTouchEvent_.tiltY.value());
        }
        (*callback)(info);
    }
}

bool PanRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    RefPtr<PanRecognizer> curr = AceType::DynamicCast<PanRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (curr->fingers_ != fingers_ || curr->priorityMask_ != priorityMask_) {
        ResetStatus();
        return false;
    }

    direction_.type = curr->direction_.type;
    newDirection_.type = curr->newDirection_.type;
    distance_ = curr->distance_;
    newDistance_ = curr->newDistance_;
    mouseDistance_ = curr->mouseDistance_;

    onActionStart_ = std::move(curr->onActionStart_);
    onActionUpdate_ = std::move(curr->onActionUpdate_);
    onActionEnd_ = std::move(curr->onActionEnd_);
    onActionCancel_ = std::move(curr->onActionCancel_);

    return true;
}

void PanRecognizer::SetDirection(const PanDirection& direction)
{
    ChangeDirection(direction);
    if ((direction_.type & PanDirection::VERTICAL) == 0) {
        velocityTracker_.SetMainAxis(Axis::HORIZONTAL);
    } else if ((direction_.type & PanDirection::HORIZONTAL) == 0) {
        velocityTracker_.SetMainAxis(Axis::VERTICAL);
    }
}

void PanRecognizer::ChangeFingers(int32_t fingers)
{
    if (fingers_ != fingers) {
        newFingers_ = fingers;
    }
}

void PanRecognizer::ChangeDirection(const PanDirection& direction)
{
    if (direction_.type != direction.type) {
        direction_.type = direction.type;
        newDirection_.type = direction.type;
    }
}

void PanRecognizer::ChangeDistance(double distance)
{
    if (distance_ != distance) {
        if (refereeState_ == RefereeState::READY || refereeState_ == RefereeState::DETECTING) {
            distance_ = distance;
        }
        newDistance_ = distance;
        mouseDistance_ = distance;
    }
}

double PanRecognizer::GetMainAxisDelta()
{
    switch (direction_.type) {
        case PanDirection::ALL:
            return delta_.GetDistance();
        case PanDirection::HORIZONTAL:
            return delta_.GetX();
        case PanDirection::VERTICAL:
            return delta_.GetY();
        default:
            return 0.0;
    }
}

} // namespace OHOS::Ace::NG
