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

#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"
#include "core/components_ng/event/event_constants.h"
#include "core/common/reporter/reporter.h"
#include "core/components_ng/manager/event/json_child_report.h"
#include "core/components_ng/manager/event/json_report.h"

#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t MAX_ROTATION_FINGERS = 5;
constexpr int32_t DEFAULT_ROTATION_FINGERS = 2;
constexpr double ONE_CIRCLE = 360.0;
constexpr double QUARTER_CIRCLE = 90.0;
constexpr double RANGE_MIN = -180.0;
constexpr double RANGE_MAX = 180.0;

} // namespace

RotationRecognizer::RotationRecognizer(
    int32_t fingers, double angle, bool isLimitFingerCount)
    : MultiFingersRecognizer(fingers, isLimitFingerCount), angle_(angle)
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
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "ROTATE RACC, T: %{public}s",
        node ? node->GetTag().c_str() : "null");
    lastRefereeState_ = refereeState_;
    refereeState_ = RefereeState::SUCCEED;
    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    bool needPostEvent = isPostEventResult_ || touchPoint.passThrough;
    localMatrix_ = NGGestureRecognizer::GetTransformMatrix(
        GetAttachedNode(), false, needPostEvent, touchPoint.postEventNodeId);
    SendCallbackMsg(onActionStart_, GestureCallbackType::START);
    isNeedResetVoluntarily_ = false;
}

void RotationRecognizer::OnRejected()
{
    if (refereeState_ != RefereeState::SUCCEED) {
        lastRefereeState_ = refereeState_;
        refereeState_ = RefereeState::FAIL;
    }
    SendRejectMsg();
    firstInputTime_.reset();
}

void RotationRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    extraInfo_ = "";
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }

    if (static_cast<int32_t>(activeFingers_.size()) >= DEFAULT_ROTATION_FINGERS) {
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
        lastRefereeState_ = refereeState_;
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
    lastAxisEvent_ = event;
    touchPoints_[event.id] = TouchEvent();
    UpdateTouchPointWithAxisEvent(event);
    if (refereeState_ == RefereeState::READY) {
        initialAngle_ = event.rotateAxisAngle;
        lastRefereeState_ = refereeState_;
        refereeState_ = RefereeState::DETECTING;
    }
}

void RotationRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    if (fingersId_.find(event.id) != fingersId_.end()) {
        fingersId_.erase(event.id);
    }
    if (isNeedResetVoluntarily_ && currentFingers_ == 1) {
        ResetStateVoluntarily();
        isNeedResetVoluntarily_ = false;
        activeFingers_.remove(event.id);
        return;
    }
    if (!IsActiveFinger(event.id)) {
        return;
    }
    touchPoints_[event.id] = event;
    if (static_cast<int32_t>(activeFingers_.size()) < DEFAULT_ROTATION_FINGERS &&
        refereeState_ != RefereeState::SUCCEED) {
        extraInfo_ += "activeFinger size not satisify.";
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        activeFingers_.remove(event.id);
        return;
    }
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        extraInfo_ += "refereeState is not satisify.";
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        activeFingers_.remove(event.id);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED &&
        static_cast<int32_t>(activeFingers_.size()) == DEFAULT_ROTATION_FINGERS) {
        SendCallbackMsg(onActionEnd_, GestureCallbackType::END);
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
        isNeedResetVoluntarily_ = true;
    }
    activeFingers_.remove(event.id);
}

void RotationRecognizer::HandleTouchUpEvent(const AxisEvent& event)
{
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
        SendCallbackMsg(onActionEnd_, GestureCallbackType::END);
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
            if (CheckLimitFinger()) {
                extraInfo_ += " isLFC: " + std::to_string(isLimitFingerCount_);
                return;
            }
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
        if (static_cast<int32_t>(touchPoints_.size()) > fingers_ && isLimitFingerCount_) {
            return;
        }
        SendCallbackMsg(onActionUpdate_, GestureCallbackType::UPDATE);
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
        SendCallbackMsg(onActionUpdate_, GestureCallbackType::UPDATE);
    }
}

void RotationRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    extraInfo_ += "cancel received.";
    if (!IsActiveFinger(event.id)) {
        return;
    }
    touchPoints_[event.id] = event;
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED &&
        static_cast<int32_t>(activeFingers_.size()) == DEFAULT_ROTATION_FINGERS) {
        SendCallbackMsg(onActionCancel_, GestureCallbackType::CANCEL);
        lastRefereeState_ = RefereeState::READY;
        refereeState_ = RefereeState::READY;
    } else if (refereeState_ == RefereeState::SUCCEED) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
            "RotationRecognizer touchPoints size not equal fingers_, not send cancel callback.");
    }
}

void RotationRecognizer::HandleTouchCancelEvent(const AxisEvent& event)
{
    extraInfo_ += "cancel received.";
    UpdateTouchPointWithAxisEvent(event);
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onActionCancel_, GestureCallbackType::CANCEL);
    }
}

double RotationRecognizer::ComputeAngle()
{
    if (static_cast<int32_t>(activeFingers_.size()) < DEFAULT_ROTATION_FINGERS) {
        return 0.0;
    }
    auto sId = activeFingers_.begin();
    auto fId = sId++;

    double fx = touchPoints_[*fId].x;
    double fy = touchPoints_[*fId].y;
    double sx = touchPoints_[*sId].x;
    double sy = touchPoints_[*sId].y;
    double angle = atan2(fy - sy, fx - sx) * 180.0 / ACE_PI;
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
    localMatrix_.clear();
}

void RotationRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback, GestureCallbackType type)
{
    std::string callbackName = GetCallbackName(callback);
    ACE_SCOPED_TRACE("RotationRecognizer %s, resultAngle_: %f", callbackName.c_str(), resultAngle_);
    if (gestureInfo_ && gestureInfo_->GetDisposeTag()) {
        return;
    }
    if (callback && *callback) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        UpdateFingerListInfo();
        info.SetFingerList(fingerList_);
        info.SetAngle(resultAngle_);
        info.SetDeviceId(deviceId_);
        info.SetSourceDevice(deviceType_);
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
        info.SetGestureTypeName(GestureTypeName::ROTATION_GESTURE);
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
        if (touchPoint.rollAngle.has_value()) {
            info.SetRollAngle(touchPoint.rollAngle.value());
        }
        if (inputEventType_ == InputEventType::AXIS) {
            info.SetVerticalAxis(lastAxisEvent_.verticalAxis);
            info.SetHorizontalAxis(lastAxisEvent_.horizontalAxis);
            info.SetSourceTool(lastAxisEvent_.sourceTool);
            info.SetPressedKeyCodes(lastAxisEvent_.pressedCodes);
            info.CopyConvertInfoFrom(lastAxisEvent_.convertInfo);
        } else {
            info.SetSourceTool(touchPoint.sourceTool);
            info.SetPressedKeyCodes(touchPoint.pressedKeyCodes_);
            info.CopyConvertInfoFrom(touchPoint.convertInfo);
        }
        info.SetPointerEvent(lastPointEvent_);
        info.SetInputEventType(inputEventType_);
        // callback may be overwritten in its invoke so we copy it first
        auto callbackFunction = *callback;
        HandleGestureAccept(info, type, GestureListenerType::ROTATION);
        callbackFunction(info);
        HandleReports(info, type);
    }
}

void RotationRecognizer::HandleReports(const GestureEvent& info, GestureCallbackType type)
{
    if (type == GestureCallbackType::ACTION || type == GestureCallbackType::UPDATE) {
        return;
    }
    auto frameNode = GetAttachedNode().Upgrade();
    CHECK_NULL_VOID(frameNode);
    RotationJsonReport rotationReport;
    rotationReport.SetCallbackType(type);
    rotationReport.SetGestureType(GetRecognizerType());
    rotationReport.SetId(frameNode->GetId());
    rotationReport.SetFingerList(info.GetFingerList());
    rotationReport.SetAngle(info.GetAngle());
    Reporter::GetInstance().HandleUISessionReporting(rotationReport);
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
    if (touchPoint.rollAngle.has_value()) {
        info->SetRollAngle(touchPoint.rollAngle.value());
    }
    info->SetSourceTool(touchPoint.sourceTool);
    info->SetRawInputEventType(inputEventType_);
    info->SetRawInputEvent(lastPointEvent_);
    info->SetRawInputDeviceId(deviceId_);
    info->SetPressedKeyCodes(lastAxisEvent_.pressedCodes);
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
            SendCallbackMsg(onActionCancel_, GestureCallbackType::CANCEL);
        }
        ResetStatus();
        return false;
    }
    isLimitFingerCount_ = curr->isLimitFingerCount_;

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
