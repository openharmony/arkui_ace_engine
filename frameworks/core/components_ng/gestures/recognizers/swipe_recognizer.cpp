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

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_SWIPE_FINGERS = 10;
constexpr int32_t RATIO_MS_TO_S = 1000;
constexpr int32_t RATIO_US_TO_MS = 1000;
constexpr double STRAIGHT_ANGLE = 180.0;
constexpr double RIGHT_ANGLE = 90.0;
constexpr double SWIPE_MOVE_LIMITED = 3.0;

double Atan2ToAtan(double angle)
{
    if (GreatNotEqual(angle, RIGHT_ANGLE)) {
        angle -= STRAIGHT_ANGLE;
    } else if (LessOrEqual(angle, -RIGHT_ANGLE)) {
        angle += STRAIGHT_ANGLE;
    }
    return angle;
}

double ComputeAngle(double x, double y)
{
    if (NearZero(x)) {
        const double verticalAngle = RIGHT_ANGLE;
        if (Negative(y)) {
            return -verticalAngle;
        }
        return verticalAngle;
    }
    return atan2(y, x) * STRAIGHT_ANGLE / M_PI;
}
} // namespace

void SwipeRecognizer::OnAccepted()
{
    int64_t acceptTime = GetSysTimestamp();
    int64_t inputTime = acceptTime;
    if (firstInputTime_.has_value()) {
        inputTime = static_cast<int64_t>(firstInputTime_.value().time_since_epoch().count());
    }
    if (SystemProperties::GetTraceInputEventEnabled()) {
        ACE_SCOPED_TRACE("UserEvent InputTime:%lld AcceptTime:%lld InputType:SwipeGesture",
            static_cast<long long>(inputTime), static_cast<long long>(acceptTime));
    }
    firstInputTime_.reset();

    auto node = GetAttachedNode().Upgrade();
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Swipe accepted, tag = %{public}s",
        node ? node->GetTag().c_str() : "null");
    auto lastRefereeState = refereeState_;
    refereeState_ = RefereeState::SUCCEED;
    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    localMatrix_ = NGGestureRecognizer::GetTransformMatrix(GetAttachedNode(), false,
        isPostEventResult_, touchPoint.postEventNodeId);
    SendCallbackMsg(onAction_);
    int64_t overTime = GetSysTimestamp();
    if (SystemProperties::GetTraceInputEventEnabled()) {
        ACE_SCOPED_TRACE("UserEvent InputTime:%lld OverTime:%lld InputType:SwipeGesture",
            static_cast<long long>(inputTime), static_cast<long long>(overTime));
    }
    firstInputTime_.reset();
    if (lastRefereeState != RefereeState::SUCCEED_BLOCKED) {
        ResetStateVoluntarily();
    }
}

void SwipeRecognizer::OnRejected()
{
    SendRejectMsg();
    refereeState_ = RefereeState::FAIL;
    firstInputTime_.reset();
}

void SwipeRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    extraInfo_ = "";
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }

    if (fingers_ > MAX_SWIPE_FINGERS) {
        extraInfo_ += "fingers exceeds the maximum dingers of the swipe gesture.";
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (direction_.type == SwipeDirection::NONE) {
        auto node = GetAttachedNode().Upgrade();
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Swipe recognizer direction is none, node tag = %{public}s, id = %{public}s",
            node ? node->GetTag().c_str() : "null", node ? std::to_string(node->GetId()).c_str() : "invalid");
        extraInfo_ += "swipe direction is NONE.";
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (fingersId_.find(event.id) == fingersId_.end()) {
        fingersId_.insert(event.id);
    }
    touchPoints_[event.id] = event;
    downEvents_[event.id] = event;
    time_ = event.time;
    lastTouchEvent_ = event;

    if (static_cast<int32_t>(touchPoints_.size()) == fingers_) {
        touchDownTime_ = event.time;
        refereeState_ = RefereeState::DETECTING;
    }
}

void SwipeRecognizer::HandleTouchDownEvent(const AxisEvent& event)
{
    extraInfo_ = "";
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }
    if (direction_.type == SwipeDirection::NONE) {
        extraInfo_ += "swipe direction is NONE in axis case.";
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    axisEventStart_ = event;
    lastAxisEvent_ = event;
    touchPoints_[event.id] = TouchEvent();
    UpdateTouchPointWithAxisEvent(event);
    axisOffset_.Reset();
    touchDownTime_ = event.time;
    time_ = event.time;
    refereeState_ = RefereeState::DETECTING;
}

void SwipeRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    if (fingersId_.find(event.id) != fingersId_.end()) {
        fingersId_.erase(event.id);
    }
    globalPoint_ = Point(event.x, event.y);
    touchPoints_[event.id] = event;
    time_ = event.time;
    lastTouchEvent_ = event;
    if (IsRefereeFinished()) {
        return;
    }
    if (refereeState_ == RefereeState::READY) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    auto offset = event.GetOffset() - downEvents_[event.id].GetOffset();
    // nanoseconds duration to seconds.
    std::chrono::duration<double> duration = event.time - touchDownTime_;
    auto seconds = duration.count();
    resultSpeed_ = LessOrEqual(seconds, 0.0) ? 0.0 : offset.GetDistance() / seconds;
    if (resultSpeed_ < speed_) {
        if (currentFingers_ - 1 + static_cast<int32_t>(matchedTouch_.size()) < fingers_) {
            TAG_LOGI(AceLogTag::ACE_GESTURE, "The result speed %{public}f is less than duration %{public}f",
                resultSpeed_, speed_);
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    } else {
        matchedTouch_.insert(event.id);
        if (static_cast<int32_t>(matchedTouch_.size()) != fingers_) {
            Adjudicate(AceType::Claim(this), GestureDisposal::PENDING);
            return;
        }
        auto onGestureJudgeBeginResult = TriggerGestureJudgeCallback();
        if (onGestureJudgeBeginResult == GestureJudgeResult::REJECT) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return;
        }
        if (CheckLimitFinger()) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return;
        }
        Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
    }
}

void SwipeRecognizer::HandleTouchUpEvent(const AxisEvent& event)
{
    globalPoint_ = Point(event.x, event.y);
    touchPoints_[event.id] = TouchEvent();
    UpdateTouchPointWithAxisEvent(event);
    time_ = event.time;
    lastAxisEvent_ = event;
    if ((refereeState_ != RefereeState::DETECTING) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::DETECTING) {
        if (NearZero(axisOffset_.GetX()) && NearZero(axisOffset_.GetY())) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return;
        }
        if (event.sourceTool == SourceTool::MOUSE) {
            resultSpeed_ = 0.0;
            auto onGestureJudgeBeginResult = TriggerGestureJudgeCallback();
            if (onGestureJudgeBeginResult == GestureJudgeResult::REJECT) {
                Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
                return;
            }
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
            return;
        }
        auto duration = event.time - touchDownTime_;
        auto duration_ms =
            std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, RATIO_US_TO_MS>>>(duration);
        resultSpeed_ = LessOrEqual(duration_ms.count(), 0.0)
                           ? 0.0
                           : axisOffset_.GetDistance() / duration_ms.count() * RATIO_MS_TO_S;
        if (resultSpeed_ < speed_) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        } else {
            auto onGestureJudgeBeginResult = TriggerGestureJudgeCallback();
            if (onGestureJudgeBeginResult == GestureJudgeResult::REJECT) {
                Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
                return;
            }
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
    }
}

void SwipeRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    if (currentFingers_ < fingers_) {
        return;
    }
    if (refereeState_ != RefereeState::DETECTING) {
        return;
    }
    globalPoint_ = Point(event.x, event.y);
    time_ = event.time;
    lastTouchEvent_ = event;
    PointF curLocalPoint(event.x, event.y);
    PointF lastLocalPoint(touchPoints_[event.id].x, touchPoints_[event.id].y);
    TransformForRecognizer(curLocalPoint, GetAttachedNode(), false,
        isPostEventResult_, event.postEventNodeId);
    TransformForRecognizer(lastLocalPoint, GetAttachedNode(), false,
        isPostEventResult_, event.postEventNodeId);
    Offset moveDistance(curLocalPoint.GetX() - lastLocalPoint.GetX(), curLocalPoint.GetY() - lastLocalPoint.GetY());
    touchPoints_[event.id] = event;
    if (NearZero(moveDistance.GetX()) && NearZero(moveDistance.GetY())) {
        return;
    }
    if (moveDistance.GetDistance() < SWIPE_MOVE_LIMITED) {
        // if move distance is smaller than MOVE_LIMITED, no need to calculate Angle.
        return;
    }
    double newAngle = ComputeAngle(moveDistance.GetX(), moveDistance.GetY());
    if (CheckAngle(newAngle)) {
        prevAngle_ = newAngle;
        return;
    }
    extraInfo_ += "swipe move event angle doesn't meet the requirement.";
    Adjudicate(Claim(this), GestureDisposal::REJECT);
}

void SwipeRecognizer::HandleTouchMoveEvent(const AxisEvent& event)
{
    if (refereeState_ != RefereeState::DETECTING) {
        return;
    }
    globalPoint_ = Point(event.x, event.y);
    time_ = event.time;
    lastAxisEvent_ = event;
    UpdateTouchPointWithAxisEvent(event);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    bool isShiftKeyPressed = false;
    bool hasDifferentDirectionGesture = false;
    if (pipeline) {
        isShiftKeyPressed =
            event.HasKey(KeyCode::KEY_SHIFT_LEFT) || event.HasKey(KeyCode::KEY_SHIFT_RIGHT);
        hasDifferentDirectionGesture = pipeline->HasDifferentDirectionGesture();
    }
    auto currentOffset = event.ConvertToOffset(isShiftKeyPressed, hasDifferentDirectionGesture);
    if (event.sourceTool == SourceTool::MOUSE) {
        if (direction_.type == SwipeDirection::VERTICAL) {
            currentOffset.SetX(0.0);
        } else if (direction_.type == SwipeDirection::HORIZONTAL) {
            currentOffset.SetY(0.0);
        }
    }
    if (NearZero(currentOffset.GetX()) && NearZero(currentOffset.GetY())) {
        return;
    }
    axisOffset_ += currentOffset;
    double newAngle = ComputeAngle(currentOffset.GetX(), currentOffset.GetY());
    if (CheckAngle(newAngle)) {
        prevAngle_ = newAngle;
        return;
    }
    extraInfo_ += "swipe move event angle doesn't meet the requirement in axis case.";
    Adjudicate(Claim(this), GestureDisposal::REJECT);
}

void SwipeRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onActionCancel_);
    }
}

void SwipeRecognizer::HandleTouchCancelEvent(const AxisEvent& event)
{
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onActionCancel_);
    }
}

bool SwipeRecognizer::CheckAngle(double angle)
{
    const double axisDiffDuration = RIGHT_ANGLE / 2;
    angle = Atan2ToAtan(angle);
    if (prevAngle_.has_value()) {
        auto diffValue = std::abs(Atan2ToAtan(prevAngle_.value())) - std::abs(angle);
        if (diffValue > axisDiffDuration) {
            return false;
        }
    }
    if (direction_.type == SwipeDirection::HORIZONTAL) {
        if (std::abs(angle) > axisDiffDuration) {
            return false;
        }
    }
    if (direction_.type == SwipeDirection::VERTICAL) {
        const double axisVertical = RIGHT_ANGLE;
        auto diffValue = std::abs(angle) - axisVertical;
        if (std::abs(diffValue) > axisDiffDuration) {
            return false;
        }
    }
    return true;
}

void SwipeRecognizer::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    axisOffset_.Reset();
    resultSpeed_ = 0.0;
    lastTouchEvent_ = TouchEvent();
    downEvents_.clear();
    time_ = TimeStamp();
    touchDownTime_ = TimeStamp();
    globalPoint_ = Point();
    prevAngle_ = std::nullopt;
    matchedTouch_.clear();
    localMatrix_.clear();
}

void SwipeRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback)
{
    if (gestureInfo_ && gestureInfo_->GetDisposeTag()) {
        return;
    }
    if (callback && *callback) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        UpdateFingerListInfo();
        info.SetFingerList(fingerList_);
        info.SetGlobalPoint(globalPoint_);
        info.SetSpeed(resultSpeed_);
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
        if (lastTouchEvent_.rollAngle.has_value()) {
            info.SetRollAngle(lastTouchEvent_.rollAngle.value());
        }
        if (inputEventType_ == InputEventType::AXIS) {
            info.SetVerticalAxis(lastAxisEvent_.verticalAxis);
            info.SetHorizontalAxis(lastAxisEvent_.horizontalAxis);
            info.SetSourceTool(lastAxisEvent_.sourceTool);
            info.SetPressedKeyCodes(lastAxisEvent_.pressedCodes);
        } else {
            info.SetSourceTool(lastTouchEvent_.sourceTool);
            info.SetPressedKeyCodes(lastTouchEvent_.pressedKeyCodes_);
        }
        info.SetPointerEvent(lastPointEvent_);
        if (prevAngle_) {
            info.SetAngle(prevAngle_.value());
        }
        info.SetInputEventType(inputEventType_);
        // callback may be overwritten in its invoke so we copy it first
        auto callbackFunction = *callback;
        callbackFunction(info);
    }
}

GestureJudgeResult SwipeRecognizer::TriggerGestureJudgeCallback()
{
    auto targetComponent = GetTargetComponent();
    CHECK_NULL_RETURN(targetComponent, GestureJudgeResult::CONTINUE);
    auto gestureRecognizerJudgeFunc = targetComponent->GetOnGestureRecognizerJudgeBegin();
    auto callback = targetComponent->GetOnGestureJudgeBeginCallback();
    if (!callback && !gestureRecognizerJudgeFunc) {
        return GestureJudgeResult::CONTINUE;
    }
    auto info = std::make_shared<SwipeGestureEvent>();
    info->SetTimeStamp(time_);
    info->SetDeviceId(deviceId_);
    UpdateFingerListInfo();
    info->SetFingerList(fingerList_);
    if (deviceType_ == SourceType::MOUSE) {
        info->SetSpeed(0.0);
    } else {
        info->SetSpeed(resultSpeed_);
    }
    info->SetSourceDevice(deviceType_);
    info->SetTarget(GetEventTarget().value_or(EventTarget()));
    info->SetForce(lastTouchEvent_.force);
    if (gestureInfo_) {
        gestureInfo_->SetInputEventType(inputEventType_);
    }
    if (lastTouchEvent_.tiltX.has_value()) {
        info->SetTiltX(lastTouchEvent_.tiltX.value());
    }
    if (lastTouchEvent_.tiltY.has_value()) {
        info->SetTiltY(lastTouchEvent_.tiltY.value());
    }
    if (lastTouchEvent_.rollAngle.has_value()) {
        info->SetRollAngle(lastTouchEvent_.rollAngle.value());
    }
    info->SetSourceTool(
        inputEventType_ == InputEventType::AXIS ? lastAxisEvent_.sourceTool : lastTouchEvent_.sourceTool);
    if (prevAngle_) {
        info->SetAngle(prevAngle_.value());
    }
    if (gestureRecognizerJudgeFunc) {
        return gestureRecognizerJudgeFunc(info, Claim(this), responseLinkRecognizer_);
    }
    return callback(gestureInfo_, info);
}

bool SwipeRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    RefPtr<SwipeRecognizer> curr = AceType::DynamicCast<SwipeRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (curr->fingers_ != fingers_ || (curr->direction_.type != direction_.type) || !NearZero(curr->speed_ - speed_) ||
        priorityMask_ != curr->priorityMask_) {
        ResetStatus();
        return false;
    }
    isLimitFingerCount_ = curr->isLimitFingerCount_;

    onAction_ = std::move(curr->onAction_);
    ReconcileGestureInfoFrom(recognizer);
    return true;
}

RefPtr<GestureSnapshot> SwipeRecognizer::Dump() const
{
    RefPtr<GestureSnapshot> info = NGGestureRecognizer::Dump();
    std::stringstream oss;
    oss << "direction: " << direction_.type << ", "
        << "speed: " << speed_ << ", "
        << "fingers: " << fingers_ << ", "
        << DumpGestureInfo();
    info->customInfo = oss.str();
    return info;
}

} // namespace OHOS::Ace::NG
