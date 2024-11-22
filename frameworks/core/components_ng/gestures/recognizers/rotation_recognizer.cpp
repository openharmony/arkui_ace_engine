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

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t MAX_ROTATION_FINGERS = 5;
constexpr int32_t DEFAULT_ROTATION_FINGERS = 2;
constexpr double ONE_CIRCLE = 360.0;
constexpr double QUARTER_CIRCLE = 90.0;
constexpr double RANGE_MIN = -180.0;
constexpr double RANGE_MAX = 180.0;

} // namespace

RotationRecognizer::RotationRecognizer(int32_t fingers, double angle) : MultiFingersRecognizer(fingers), angle_(angle)
{
    if (fingers_ > MAX_ROTATION_FINGERS || fingers_ < DEFAULT_ROTATION_FINGERS) {
        fingers_ = DEFAULT_ROTATION_FINGERS;
    }
}

void RotationRecognizer::OnAccepted()
{
    int64_t acceptTime = GetSysTimestamp();
    int64_t inputTime = acceptTime;
    if (firstInputTime_.has_value()) {
        inputTime = static_cast<int64_t>(firstInputTime_.value().time_since_epoch().count());
    }
    if (SystemProperties::GetTraceInputEventEnabled()) {
        ACE_SCOPED_TRACE("UserEvent InputTime:%lld AcceptTime:%lld InputType:RotationGesture",
            static_cast<long long>(inputTime), static_cast<long long>(acceptTime));
    }
    
    auto node = GetAttachedNode().Upgrade();
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Rotation accepted, tag = %{public}s",
        node ? node->GetTag().c_str() : "null");
    refereeState_ = RefereeState::SUCCEED;
    SendCallbackMsg(onActionStart_);
}

void RotationRecognizer::OnRejected()
{
    if (refereeState_ != RefereeState::SUCCEED) {
        refereeState_ = RefereeState::FAIL;
    }
    SendRejectMsg();
    firstInputTime_.reset();
}

void RotationRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, rotation %{public}d down, state: %{public}d",
        event.touchEventId, event.id, refereeState_);
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }

    if (static_cast<int32_t>(activeFingers_.size()) >= DEFAULT_ROTATION_FINGERS) {
        return;
    }
    if (!IsInAttachedNode(event)) {
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }
    if (fingers_ > MAX_ROTATION_FINGERS) {
        fingers_ = DEFAULT_ROTATION_FINGERS;
    }

    if (fingersId_.find(event.id) == fingersId_.end()) {
        fingersId_.insert(event.id);
    }
    activeFingers_.emplace_back(event.id);
    touchPoints_[event.id] = event;

    if (static_cast<int32_t>(activeFingers_.size()) >= DEFAULT_ROTATION_FINGERS) {
        initialAngle_ = ComputeAngle();
        refereeState_ = RefereeState::DETECTING;
    }
}

void RotationRecognizer::HandleTouchDownEvent(const AxisEvent& event)
{
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }
    if (!event.isRotationEvent) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, rotation axis start, state: %{public}d", event.touchEventId,
        refereeState_);
    lastAxisEvent_ = event;
    touchPoints_[event.id] = TouchEvent();
    UpdateTouchPointWithAxisEvent(event);
    if (refereeState_ == RefereeState::READY) {
        initialAngle_ = event.rotateAxisAngle;
        refereeState_ = RefereeState::DETECTING;
    }
}

void RotationRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    if (fingersId_.find(event.id) != fingersId_.end()) {
        fingersId_.erase(event.id);
    }
    if (!IsActiveFinger(event.id)) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, rotation %{public}d up, state: %{public}d",
        event.touchEventId, event.id, refereeState_);
    if (static_cast<int32_t>(activeFingers_.size()) < DEFAULT_ROTATION_FINGERS &&
        refereeState_ != RefereeState::SUCCEED) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        activeFingers_.remove(event.id);
        return;
    }
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        activeFingers_.remove(event.id);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED &&
        static_cast<int32_t>(activeFingers_.size()) == DEFAULT_ROTATION_FINGERS) {
        SendCallbackMsg(onActionEnd_);
        int64_t overTime = GetSysTimestamp();
        int64_t inputTime = overTime;
        if (firstInputTime_.has_value()) {
            inputTime = static_cast<int64_t>(firstInputTime_.value().time_since_epoch().count());
        }
        if (SystemProperties::GetTraceInputEventEnabled()) {
            ACE_SCOPED_TRACE("UserEvent InputTime:%lld OverTime:%lld InputType:RotationGesture",
                static_cast<long long>(inputTime), static_cast<long long>(overTime));
        }
        firstInputTime_.reset();
    }
    activeFingers_.remove(event.id);
}

void RotationRecognizer::HandleTouchUpEvent(const AxisEvent& event)
{
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, rotation axis end, state: %{public}d", event.touchEventId,
        refereeState_);
    // if rotation recognizer received another axisEvent, no need to active.
    if (!event.isRotationEvent) {
        return;
    }
    UpdateTouchPointWithAxisEvent(event);
    lastAxisEvent_ = event;
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onActionEnd_);
        int64_t overTime = GetSysTimestamp();
        int64_t inputTime = overTime;
        if (firstInputTime_.has_value()) {
            inputTime = static_cast<int64_t>(firstInputTime_.value().time_since_epoch().count());
        }
        if (SystemProperties::GetTraceInputEventEnabled()) {
            ACE_SCOPED_TRACE("UserEvent InputTime:%lld OverTime:%lld InputType:RotationGesture",
                static_cast<long long>(inputTime), static_cast<long long>(overTime));
        }
        firstInputTime_.reset();
    }
}

void RotationRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    if (!IsActiveFinger(event.id) || currentFingers_ < fingers_) {
        touchPoints_[event.id] = event;
        lastAngle_ = 0.0;
        angleSignChanged_ = false;
        return;
    }
    touchPoints_[event.id] = event;
    currentAngle_ = ComputeAngle();
    time_ = event.time;
    if (static_cast<int32_t>(activeFingers_.size()) < DEFAULT_ROTATION_FINGERS) {
        lastAngle_ = 0.0;
        angleSignChanged_ = false;
        return;
    }

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

void RotationRecognizer::HandleTouchMoveEvent(const AxisEvent& event)
{
    if (!event.isRotationEvent) {
        return;
    }
    UpdateTouchPointWithAxisEvent(event);
    currentAngle_ = event.rotateAxisAngle;
    lastAxisEvent_ = event;
    time_ = event.time;
    if (refereeState_ == RefereeState::DETECTING) {
        double diffAngle = fabs((currentAngle_ - initialAngle_));
        if (GreatNotEqual(diffAngle, angle_)) {
            resultAngle_ = ChangeValueRange(currentAngle_ - initialAngle_);
            auto onGestureJudgeBeginResult = TriggerGestureJudgeCallback();
            if (onGestureJudgeBeginResult == GestureJudgeResult::REJECT) {
                Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
                return;
            }
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
    } else if (refereeState_ == RefereeState::SUCCEED) {
        resultAngle_ = ChangeValueRange(currentAngle_ - initialAngle_);
        SendCallbackMsg(onActionUpdate_);
    }
}

void RotationRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    if (!IsActiveFinger(event.id)) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, rotation %{public}d cancel", event.touchEventId, event.id);
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED &&
        static_cast<int32_t>(activeFingers_.size()) == DEFAULT_ROTATION_FINGERS) {
        SendCancelMsg();
        refereeState_ = RefereeState::READY;
    } else if (refereeState_ == RefereeState::SUCCEED) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
            "RotationRecognizer touchPoints size not equal fingers_, not send cancel callback.");
    }
}

void RotationRecognizer::HandleTouchCancelEvent(const AxisEvent& event)
{
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, rotation axis cancel", event.touchEventId);
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
    while (LessOrEqual(value, RANGE_MIN)) {
        value += ONE_CIRCLE;
    }
    while (GreatNotEqual(value, RANGE_MAX)) {
        value -= ONE_CIRCLE;
    }
    return value;
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
        if (inputEventType_ == InputEventType::AXIS) {
            info.SetVerticalAxis(lastAxisEvent_.verticalAxis);
            info.SetHorizontalAxis(lastAxisEvent_.horizontalAxis);
            info.SetSourceTool(lastAxisEvent_.sourceTool);
            info.SetPressedKeyCodes(lastAxisEvent_.pressedCodes);
        } else {
            info.SetSourceTool(touchPoint.sourceTool);
            info.SetPressedKeyCodes(touchPoint.pressedKeyCodes_);
        }
        info.SetPointerEvent(lastPointEvent_);
        info.SetInputEventType(inputEventType_);
        // callback may be overwritten in its invoke so we copy it first
        auto callbackFunction = *callback;
        callbackFunction(info);
    }
}

GestureJudgeResult RotationRecognizer::TriggerGestureJudgeCallback()
{
    auto targetComponent = GetTargetComponent();
    CHECK_NULL_RETURN(targetComponent, GestureJudgeResult::CONTINUE);
    auto gestureRecognizerJudgeFunc = targetComponent->GetOnGestureRecognizerJudgeBegin();
    auto callback = targetComponent->GetOnGestureJudgeBeginCallback();
    if (!callback && !gestureRecognizerJudgeFunc) {
        return GestureJudgeResult::CONTINUE;
    }
    auto info = std::make_shared<RotationGestureEvent>();
    info->SetTimeStamp(time_);
    info->SetDeviceId(deviceId_);
    UpdateFingerListInfo();
    info->SetFingerList(fingerList_);
    info->SetAngle(resultAngle_);
    info->SetSourceDevice(deviceType_);
    info->SetTarget(GetEventTarget().value_or(EventTarget()));
    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    info->SetForce(touchPoint.force);
    if (gestureInfo_) {
        gestureInfo_->SetInputEventType(inputEventType_);
    }
    if (touchPoint.tiltX.has_value()) {
        info->SetTiltX(touchPoint.tiltX.value());
    }
    if (touchPoint.tiltY.has_value()) {
        info->SetTiltY(touchPoint.tiltY.value());
    }
    info->SetSourceTool(touchPoint.sourceTool);
    if (gestureRecognizerJudgeFunc) {
        return gestureRecognizerJudgeFunc(info, Claim(this), responseLinkRecognizer_);
    }
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
        if (refereeState_ == RefereeState::SUCCEED &&
            static_cast<int32_t>(activeFingers_.size()) == DEFAULT_ROTATION_FINGERS) {
            SendCancelMsg();
        }
        ResetStatus();
        return false;
    }

    onActionStart_ = std::move(curr->onActionStart_);
    onActionUpdate_ = std::move(curr->onActionUpdate_);
    onActionEnd_ = std::move(curr->onActionEnd_);
    onActionCancel_ = std::move(curr->onActionCancel_);
    ReconcileGestureInfoFrom(recognizer);
    return true;
}

RefPtr<GestureSnapshot> RotationRecognizer::Dump() const
{
    RefPtr<GestureSnapshot> info = NGGestureRecognizer::Dump();
    std::stringstream oss;
    oss << "angle: " << angle_ << ", "
        << "fingers: " << fingers_ << ", "
        << DumpGestureInfo();
    info->customInfo = oss.str();
    return info;
}

} // namespace OHOS::Ace::NG
