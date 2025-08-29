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

#include "core/components_ng/event/event_constants.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"

#include "base/perfmonitor/perf_monitor.h"
#include "base/ressched/ressched_report.h"
#include "base/ressched/ressched_touch_optimizer.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/manager/event/json_child_report.h"
#include "core/common/reporter/reporter.h"
#include "core/components_ng/manager/event/json_report.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t MAX_PAN_FINGERS = 10;
constexpr int32_t DEFAULT_PAN_FINGERS = 1;
constexpr int32_t AXIS_PAN_FINGERS = 1;
constexpr float MIN_SPEED_THRESHOLD = 500.0f;
constexpr float TOUCHPAD_STILL_THRESHOLD = 0.1;

} // namespace

void PanRecognizer::ForceCleanRecognizer()
{
    MultiFingersRecognizer::ForceCleanRecognizer();
    averageDistance_.Reset();
    touchPointsDistance_.clear();
    localMatrix_.clear();
    isStartTriggered_ = false;
    ResSchedTouchOptimizer::GetInstance().SetSlideAcceptOffset(averageDistance_);
}

PanRecognizer::PanRecognizer(int32_t fingers, const PanDirection& direction, double distance, bool isLimitFingerCount)
    : MultiFingersRecognizer(fingers, isLimitFingerCount), direction_(direction), distance_(distance),
    mouseDistance_(distance), newFingers_(fingers_), newDistance_(distance_), newDirection_(direction_)
{
    distanceMap_[SourceTool::UNKNOWN] = Dimension(
        Dimension(distance_, DimensionUnit::PX).ConvertToVp(), DimensionUnit::VP);
    newDistanceMap_[SourceTool::UNKNOWN] = Dimension(
        Dimension(distance_, DimensionUnit::PX).ConvertToVp(), DimensionUnit::VP);
    panVelocity_.SetDirection(direction_.type);
    if (fingers_ > MAX_PAN_FINGERS || fingers_ < DEFAULT_PAN_FINGERS) {
        fingers_ = DEFAULT_PAN_FINGERS;
    }
}

PanRecognizer::PanRecognizer(
    int32_t fingers, const PanDirection& direction, const PanDistanceMap& distanceMap, bool isLimitFingerCount)
    : MultiFingersRecognizer(fingers, isLimitFingerCount), direction_(direction), newFingers_(fingers_),
      newDirection_(direction_)
{
    SetDistanceMap(distanceMap);
    panVelocity_.SetDirection(direction_.type);
    if (fingers_ > MAX_PAN_FINGERS || fingers_ < DEFAULT_PAN_FINGERS) {
        fingers_ = DEFAULT_PAN_FINGERS;
    }
}

PanRecognizer::PanRecognizer(int32_t fingers, const PanDirection& direction,
    const PanDistanceMapDimension& distanceMap, bool isLimitFingerCount)
    : MultiFingersRecognizer(fingers, isLimitFingerCount), direction_(direction), newFingers_(fingers_),
      newDirection_(direction_), distanceMap_(distanceMap), newDistanceMap_(distanceMap)
{
    panVelocity_.SetDirection(direction_.type);
    if (fingers_ > MAX_PAN_FINGERS || fingers_ < DEFAULT_PAN_FINGERS) {
        fingers_ = DEFAULT_PAN_FINGERS;
    }
}

RefPtr<Gesture> PanRecognizer::CreateGestureFromRecognizer() const
{
    return AceType::MakeRefPtr<PanGesture>(fingers_, direction_, distanceMap_, isLimitFingerCount_);
}

void PanRecognizer::ResetDistanceMap()
{
    for (auto& iter : distanceMap_) {
        distanceMap_[iter.first] = LessNotEqual(iter.second.ConvertToPx(), 0.0) ? DEFAULT_PAN_DISTANCE : iter.second;
    }
    if (distanceMap_.find(SourceTool::UNKNOWN) == distanceMap_.end()) {
        distanceMap_[SourceTool::UNKNOWN] = DEFAULT_PAN_DISTANCE;
    }
}

PanRecognizer::PanRecognizer(const RefPtr<PanGestureOption>& panGestureOption) : panGestureOption_(panGestureOption)
{
    uint32_t directNum = panGestureOption->GetDirection().type;
    int32_t fingersNumber = panGestureOption->GetFingers();
    bool isLimitFingerCount = panGestureOption->GetIsLimitFingerCount();

    fingers_ = fingersNumber;
    isLimitFingerCount_ = isLimitFingerCount;
    if (fingers_ > MAX_PAN_FINGERS || fingers_ < DEFAULT_PAN_FINGERS) {
        fingers_ = DEFAULT_PAN_FINGERS;
    }

    if (directNum >= PanDirection::NONE && directNum <= PanDirection::ALL) {
        direction_.type = directNum;
    }

    distanceMap_ = panGestureOption->GetPanDistanceMap();
    ResetDistanceMap();
    newDistanceMap_ = distanceMap_;
    newFingers_ = fingers_;
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
    ResSchedTouchOptimizer::GetInstance().SetSlideAccepted(true);
    int64_t acceptTime = GetSysTimestamp();
    int64_t inputTime = acceptTime;
    if (firstInputTime_.has_value()) {
        inputTime = static_cast<int64_t>(firstInputTime_.value().time_since_epoch().count());
    }
    if (SystemProperties::GetTraceInputEventEnabled()) {
        ACE_SCOPED_TRACE("UserEvent InputTime:%lld AcceptTime:%lld InputType:PanGesture",
            static_cast<long long>(inputTime), static_cast<long long>(acceptTime));
    }

    auto node = GetAttachedNode().Upgrade();
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
        "PAN RACC, T: %{public}s, DIS x %{public}f, y %{public}f",
        node ? node->GetTag().c_str() : "null", averageDistance_.GetX(), averageDistance_.GetY());
    lastRefereeState_ = refereeState_;
    refereeState_ = RefereeState::SUCCEED;
    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    localMatrix_ = NGGestureRecognizer::GetTransformMatrix(GetAttachedNode(), false,
        isPostEventResult_, touchPoint.postEventNodeId);
    SendCallbackMsg(onActionStart_, GestureCallbackType::START);
    isNeedResetVoluntarily_ = false;
    // only report the pan gesture starting for touch event
    DispatchPanStartedToPerf(lastTouchEvent_);
    if (IsEnabled()) {
        isStartTriggered_ = true;
    }
    SendCallbackMsg(onActionUpdate_, GestureCallbackType::UPDATE);
    // if gesture is blocked by double click, recognizer will receive up before onAccepted
    // in this case, recognizer need to send onActionEnd when onAccepted
    if (isTouchEventFinished_) {
        isStartTriggered_ = false;
        SendCallbackMsg(onActionEnd_, GestureCallbackType::END);
    }
    ResSchedTouchOptimizer::GetInstance().SetSlideAcceptOffset(averageDistance_);
}

void PanRecognizer::OnRejected()
{
    // fix griditem drag interrupted by click while pull moving
    if (refereeState_ != RefereeState::SUCCEED) {
        lastRefereeState_ = refereeState_;
        refereeState_ = RefereeState::FAIL;
    }
    SendRejectMsg();
    firstInputTime_.reset();
}

void PanRecognizer::UpdateTouchPointInVelocityTracker(const TouchEvent& touchEvent)
{
    auto updateTask = [this](const TouchEvent& event) {
        bool end = event.type == TouchType::UP;
        PointF windowPoint(event.x, event.y);
        TouchEvent transformEvent = event;
        auto container = Container::Current();
        if (container && container->IsUIExtensionWindow()) {
            auto historyEvent = Platform::GetTouchEventOriginOffset(end ? lastTouchEvent_ : event);
            windowPoint.SetX(historyEvent.GetX());
            windowPoint.SetY(historyEvent.GetY());
            transformEvent.time = Platform::GetTouchEventOriginTimeStamp(end ? lastTouchEvent_ : event);
        }
        NGGestureRecognizer::Transform(windowPoint, GetAttachedNode(), false,
            isPostEventResult_, event.postEventNodeId);

        transformEvent.x = windowPoint.GetX();
        transformEvent.y = windowPoint.GetY();
        panVelocity_.UpdateTouchPoint(event.id, transformEvent, end);
    };
    if (touchEvent.history.empty()) {
        updateTask(touchEvent);
        return;
    }
    for (const auto& historyEvent: touchEvent.history) {
        updateTask(historyEvent);
    }
}

void PanRecognizer::UpdateAxisPointInVelocityTracker(const AxisEvent& event, bool end)
{
    auto pesudoTouchEvent = TouchEvent();
    pesudoTouchEvent.time = event.time;
    auto revertAxisValue = event.ConvertToSummationAxisValue(lastAxisEvent_);
    pesudoTouchEvent.x = revertAxisValue.first;
    pesudoTouchEvent.y = revertAxisValue.second;
    pesudoTouchEvent.sourceTool = event.sourceTool;
    panVelocity_.UpdateTouchPoint(event.id, pesudoTouchEvent, end);
    lastAxisEvent_ = event;
    if (!end) {
        lastAxisEvent_.horizontalAxis = pesudoTouchEvent.x;
        lastAxisEvent_.verticalAxis = pesudoTouchEvent.y;
    }
}

void PanRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    ResSchedTouchOptimizer::GetInstance().SetSlideAccepted(false);
    extraInfo_ = "";
    lastAction_ = inputEventType_ == InputEventType::TOUCH_SCREEN ? static_cast<int32_t>(TouchType::DOWN)
                                                                  : static_cast<int32_t>(MouseAction::PRESS);
    isTouchEventFinished_ = false;
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }

    fingers_ = newFingers_;
    distance_ = newDistance_;
    direction_ = newDirection_;
    distanceMap_ = newDistanceMap_;

    if (direction_.type == PanDirection::NONE) {
        auto node = GetAttachedNode().Upgrade();
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Pan recognizer direction is none, "
            "node tag = %{public}s, id = " SEC_PLD(%{public}s) ".",
            node ? node->GetTag().c_str() : "null",
            SEC_PARAM(node ? std::to_string(node->GetId()).c_str() : "invalid"));
        extraInfo_ += "direction is NONE.";
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }
    if (event.sourceType == SourceType::MOUSE && !isAllowMouse_) {
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        extraInfo_ += "mouse event is not allowed.";
        return;
    }

    if (fingersId_.find(event.id) == fingersId_.end()) {
        fingersId_.insert(event.id);
    }

    deviceId_ = event.deviceId;
    deviceType_ = event.sourceType;
    deviceTool_ = event.sourceTool;
    lastTouchEvent_ = event;
    touchPoints_[event.id] = event;
    touchPointsDistance_[event.id] = Offset(0.0, 0.0);
    auto fingerNum = static_cast<int32_t>(touchPoints_.size());

    if (fingerNum >= fingers_) {
        if (refereeState_ == RefereeState::READY) {
            panVelocity_.Reset(event.id);
            UpdateTouchPointInVelocityTracker(event);
            lastRefereeState_ = refereeState_;
            refereeState_ = RefereeState::DETECTING;
        } else {
            TAG_LOGI(AceLogTag::ACE_GESTURE, "Pan gesture refereeState is not READY");
        }
    }
    HandlePanExtAccept();
}

void PanRecognizer::HandleTouchDownEvent(const AxisEvent& event)
{
    extraInfo_ = "";
    lastAction_ = static_cast<int32_t>(AxisAction::BEGIN);
    isTouchEventFinished_ = false;
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }
    if (event.isRotationEvent) {
        return;
    }
    fingers_ = newFingers_;
    distance_ = newDistance_;
    direction_ = newDirection_;
    distanceMap_ = newDistanceMap_;

    if (fingers_ != AXIS_PAN_FINGERS) {
        extraInfo_ += "fingers does not meet the requirements of the axis event.";
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (direction_.type == PanDirection::NONE) {
        extraInfo_ += "direction is NONE in axis case.";
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    deviceId_ = event.deviceId;
    deviceType_ = event.sourceType;
    deviceTool_ = event.sourceTool;
    lastAxisEvent_ = event;

    touchPoints_[event.id] = TouchEvent();
    UpdateTouchPointWithAxisEvent(event);
    panVelocity_.Reset(event.id);
    auto pesudoTouchEvent = TouchEvent();
    pesudoTouchEvent.time = event.time;
    auto revertAxisValue = event.ConvertToSummationAxisValue(lastAxisEvent_);
    pesudoTouchEvent.x = revertAxisValue.first;
    pesudoTouchEvent.y = revertAxisValue.second;
    pesudoTouchEvent.sourceTool = event.sourceTool;
    panVelocity_.UpdateTouchPoint(event.id, pesudoTouchEvent, false);
    lastRefereeState_ = refereeState_;
    refereeState_ = RefereeState::DETECTING;
}

void PanRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    ResSchedTouchOptimizer::GetInstance().SetSlideAccepted(true);
    extraInfo_ = "currentFingers: " + std::to_string(currentFingers_) + " fingers: " + std::to_string(fingers_);
    lastAction_ = inputEventType_ == InputEventType::TOUCH_SCREEN ? static_cast<int32_t>(TouchType::UP)
                                                                  : static_cast<int32_t>(MouseAction::RELEASE);
    fingersId_.erase(event.id);
    if (currentFingers_ < fingers_) {
        if (isNeedResetVoluntarily_ && currentFingers_ == 1) {
            ResetStateVoluntarily();
            isNeedResetVoluntarily_ = false;
        }
        return;
    }

    // In CrossPlatform, MOVE point has sampled, but the UP point is original coordinate,
    // and participating in the Velocity calculation may cause abnormal rates
    if (currentFingers_ == fingers_ && SystemProperties::IsNeedResampleTouchPoints()) {
        UpdateTouchPointInVelocityTracker(event);
    } else if (currentFingers_ > fingers_) {
        panVelocity_.Reset(event.id);
        UpdateTouchPointInVelocityTracker(event);
    }
    UpdateTouchEventInfo(event);

    if ((currentFingers_ <= fingers_) &&
        (refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        if (currentFingers_ == fingers_) {
            if (std::abs(panVelocity_.GetMainAxisVelocity()) <= MIN_SPEED_THRESHOLD) {
                DumpVelocityInfo(event.id);
            }
            // last one to fire end.
            isStartTriggered_ = false;
            SendCallbackMsg(onActionEnd_, GestureCallbackType::END);
            averageDistance_.Reset();
            ResSchedTouchOptimizer::GetInstance().SetSlideAcceptOffset(averageDistance_);
            AddOverTimeTrace();
            lastRefereeState_ = RefereeState::READY;
            refereeState_ = RefereeState::READY;
            if (currentFingers_ > 1) {
                isNeedResetVoluntarily_ = true;
            } else {
                ResetStateVoluntarily();
            }
        }
    }

    // Clear All fingers' velocity when fingersId is empty.
    if (fingersId_.empty()) {
        panVelocity_.ResetAll();
        isTouchEventFinished_ = true;
    }
}

void PanRecognizer::HandleTouchUpEvent(const AxisEvent& event)
{
    isTouchEventFinished_ = false;
    lastAction_ = static_cast<int32_t>(AxisAction::END);
    // if axisEvent received rotateEvent, no need to active Pan recognizer.
    if (event.isRotationEvent) {
        return;
    }

    if (event.sourceTool == SourceTool::MOUSE) {
        delta_ = event.ConvertToOffset();
        mainDelta_ = GetMainAxisDelta();
        averageDistance_ += delta_;
    }

    globalPoint_ = Point(event.x, event.y);

    touchPoints_[event.id] = TouchEvent();
    UpdateTouchPointWithAxisEvent(event);
    UpdateAxisPointInVelocityTracker(event, true);
    time_ = event.time;

    DumpVelocityInfo(event.id);
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
        "PanVelocity main axis velocity is %{public}f", panVelocity_.GetMainAxisVelocity());

    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        // AxisEvent is single one.
        isStartTriggered_ = false;
        SendCallbackMsg(onActionEnd_, GestureCallbackType::END);
        AddOverTimeTrace();
    }
    panVelocity_.ResetAll();
}

void PanRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    isTouchEventFinished_ = false;
    lastAction_ = inputEventType_ == InputEventType::TOUCH_SCREEN ? static_cast<int32_t>(TouchType::MOVE)
                                                                  : static_cast<int32_t>(MouseAction::MOVE);
    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        return;
    }

    if (refereeState_ == RefereeState::FAIL) {
        return;
    }
    UpdateTouchEventInfo(event);
    UpdateTouchPointInVelocityTracker(event);
    if (refereeState_ == RefereeState::DETECTING) {
        auto result = IsPanGestureAccept();
        if (result == GestureAcceptResult::ACCEPT) {
            if (HandlePanAccept()) {
                return;
            }
        } else if (result == GestureAcceptResult::REJECT) {
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
        if (isFlushTouchEventsEnd_) {
            if (!isStartTriggered_ && IsEnabled()) {
                SendCallbackMsg(onActionStart_, GestureCallbackType::START);
                isStartTriggered_ = true;
            }
            if (static_cast<int32_t>(touchPoints_.size()) > fingers_ && isLimitFingerCount_) {
                return;
            }
            SendCallbackMsg(onActionUpdate_, GestureCallbackType::UPDATE);
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

void PanRecognizer::UpdateAxisDeltaTransform(const AxisEvent& event)
{
    if (event.sourceTool == SourceTool::MOUSE) {
        if ((direction_.type & PanDirection::HORIZONTAL) == 0) { // Direction is vertical
            delta_.SetX(0.0);
        } else if ((direction_.type & PanDirection::VERTICAL) == 0) { // Direction is horizontal
            delta_.SetY(0.0);
        }
    } else if (event.sourceTool == SourceTool::TOUCHPAD) {
        PointF originPoint(lastAxisEvent_.horizontalAxis, lastAxisEvent_.verticalAxis);
        PointF finalPoint(originPoint.GetX() + delta_.GetX(), originPoint.GetY() + delta_.GetY());
        NGGestureRecognizer::Transform(originPoint, GetAttachedNode(), false, false, -1);
        NGGestureRecognizer::Transform(finalPoint, GetAttachedNode(), false, false, -1);
        delta_ = Offset(finalPoint.GetX(), finalPoint.GetY()) - Offset(originPoint.GetX(), originPoint.GetY());
    }
}

void PanRecognizer::HandleTouchMoveEvent(const AxisEvent& event)
{
    isTouchEventFinished_ = false;
    lastAction_ = static_cast<int32_t>(AxisAction::UPDATE);
    if (fingers_ != AXIS_PAN_FINGERS || event.isRotationEvent) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    bool isShiftKeyPressed = false;
    bool hasDifferentDirectionGesture = false;
    if (pipeline) {
        isShiftKeyPressed = event.HasKey(KeyCode::KEY_SHIFT_LEFT) || event.HasKey(KeyCode::KEY_SHIFT_RIGHT);
        hasDifferentDirectionGesture = pipeline->HasDifferentDirectionGesture();
    }
    delta_ = event.ConvertToOffset(isShiftKeyPressed, hasDifferentDirectionGesture);
    UpdateAxisDeltaTransform(event);
    globalPoint_ = Point(event.x, event.y);
    mainDelta_ = GetMainAxisDelta();
    averageDistance_ += delta_;

    UpdateTouchPointWithAxisEvent(event);
    UpdateAxisPointInVelocityTracker(event);
    time_ = event.time;

    if (refereeState_ == RefereeState::DETECTING) {
        auto result = IsPanGestureAccept();
        if (result == GestureAcceptResult::ACCEPT) {
            if (HandlePanAccept()) {
                return;
            }
        } else if (result == GestureAcceptResult::REJECT) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    } else if (refereeState_ == RefereeState::SUCCEED) {
        if ((direction_.type & PanDirection::VERTICAL) == 0) {
            averageDistance_.SetY(0.0);
        } else if ((direction_.type & PanDirection::HORIZONTAL) == 0) {
            averageDistance_.SetX(0.0);
        }
        if (!isStartTriggered_ && IsEnabled()) {
            SendCallbackMsg(onActionStart_, GestureCallbackType::START);
            isStartTriggered_ = true;
        }
        SendCallbackMsg(onActionUpdate_, GestureCallbackType::UPDATE);
    }
}

bool PanRecognizer::HandlePanExtAccept()
{
    if (onActionExtUpdate_ && *onActionExtUpdate_) {
        auto callbackFunction = *onActionExtUpdate_;
        GestureEvent info = GetGestureEventInfo();
        callbackFunction(info);
    }
    return true;
}

bool PanRecognizer::HandlePanAccept()
{
    if (gestureInfo_ && gestureInfo_->GetType() == GestureTypeName::DRAG) {
        auto dragEventActuator = GetDragEventActuator();
        CHECK_NULL_RETURN(dragEventActuator, true);
        if (dragEventActuator->IsDragUserReject()) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return true;
        }
    }
    if (CheckLimitFinger()) {
        extraInfo_ += " isLFC: " + std::to_string(isLimitFingerCount_);
        return false;
    }
    if (TriggerGestureJudgeCallback() == GestureJudgeResult::REJECT) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        if (gestureInfo_ && gestureInfo_->GetType() == GestureTypeName::DRAG) {
            auto dragEventActuator = GetDragEventActuator();
            CHECK_NULL_RETURN(dragEventActuator, true);
            dragEventActuator->SetIsDragUserReject(true);
        }
        return true;
    }
    if (IsBridgeMode()) {
        OnAccepted();
        return false;
    }
    Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
    return false;
}

void PanRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    ResSchedTouchOptimizer::GetInstance().SetSlideAccepted(true);
    extraInfo_ += "cancel received.";
    lastAction_ = inputEventType_ == InputEventType::TOUCH_SCREEN ? static_cast<int32_t>(TouchType::CANCEL)
                                                                  : static_cast<int32_t>(MouseAction::CANCEL);
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED && currentFingers_ == fingers_) {
        // AxisEvent is single one.
        SendCallbackMsg(onActionCancel_, GestureCallbackType::CANCEL);
        lastRefereeState_ = RefereeState::READY;
        refereeState_ = RefereeState::READY;
    } else if (refereeState_ == RefereeState::SUCCEED) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
            "PanRecognizer touchPoints size not equal fingers_, not send cancel callback.");
    }
}

void PanRecognizer::HandleTouchCancelEvent(const AxisEvent& event)
{
    extraInfo_ += "cancel received.";
    isTouchEventFinished_ = false;
    lastAction_ = static_cast<int32_t>(AxisAction::CANCEL);
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onActionCancel_, GestureCallbackType::CANCEL);
    }
}

bool PanRecognizer::JudgeVerticalDistance() const
{
    if (direction_.type == PanDirection::VERTICAL) {
        return true;
    }
    for (const auto& element : touchPointsDistance_) {
        auto each_point_move = element.second.GetY();
        if ((((direction_.type & PanDirection::DOWN) == 0) && GreatOrEqual(each_point_move, 0.0)) ||
            ((((direction_.type & PanDirection::UP) == 0) && LessOrEqual(each_point_move, 0.0)))) {
            continue;
        }
        return true;
    }
    return false;
}

bool PanRecognizer::CalculateTruthFingers(bool isDirectionUp) const
{
    float totalDistance = 0.0f;
    for (auto& element : touchPointsDistance_) {
        auto each_point_move = element.second.GetY();
        if (GreatNotEqual(each_point_move, 0.0) && isDirectionUp) {
            totalDistance += each_point_move;
        } else if (LessNotEqual(each_point_move, 0.0) && !isDirectionUp) {
            totalDistance -= each_point_move;
        }
    }
    auto judgeDistance = GetDistanceConfigFor(deviceTool_);
    return GreatOrEqual(totalDistance, judgeDistance) && static_cast<int32_t>(touchPointsDistance_.size()) >= fingers_;
}

PanRecognizer::GestureAcceptResult PanRecognizer::IsPanGestureAcceptInAllDirection(double judgeDistance) const
{
    double offset = averageDistance_.GetDistance();
    if (fabs(offset) < judgeDistance) {
        return GestureAcceptResult::DETECTING;
    }
    return GestureAcceptResult::ACCEPT;
}

PanRecognizer::GestureAcceptResult PanRecognizer::IsPanGestureAcceptInHorizontalDirection(double judgeDistance) const
{
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

PanRecognizer::GestureAcceptResult PanRecognizer::IsPanGestureAcceptInVerticalDirection(double judgeDistance) const
{
    if ((direction_.type & PanDirection::VERTICAL) != 0) {
        double offset = averageDistance_.GetY();
        if (fabs(offset) < judgeDistance) {
            return GestureAcceptResult::DETECTING;
        }
        if (inputEventType_ == InputEventType::AXIS) {
            if ((direction_.type & PanDirection::UP) == 0 && offset < 0) {
                return GestureAcceptResult::REJECT;
            }
            if ((direction_.type & PanDirection::DOWN) == 0 && offset > 0) {
                return GestureAcceptResult::REJECT;
            }
        } else {
            if (!JudgeVerticalDistance()) {
                return GestureAcceptResult::REJECT;
            }
            if ((direction_.type & PanDirection::UP) == 0) {
                return CalculateTruthFingers(true) ? GestureAcceptResult::ACCEPT : GestureAcceptResult::REJECT;
            }
            if ((direction_.type & PanDirection::DOWN) == 0) {
                return CalculateTruthFingers(false) ? GestureAcceptResult::ACCEPT : GestureAcceptResult::REJECT;
            }
        }
        return GestureAcceptResult::ACCEPT;
    }
    return GestureAcceptResult::DETECTING;
}

PanRecognizer::GestureAcceptResult PanRecognizer::IsPanGestureAccept() const
{
    auto judgeDistance = GetDistanceConfigFor(deviceTool_);
    if (NearZero(judgeDistance) && direction_.type != PanDirection::NONE) {
        return GestureAcceptResult::ACCEPT;
    }
    if ((direction_.type & PanDirection::ALL) == PanDirection::ALL) {
        return IsPanGestureAcceptInAllDirection(judgeDistance);
    }
    if (fabs(averageDistance_.GetX()) > fabs(averageDistance_.GetY())) {
        return IsPanGestureAcceptInHorizontalDirection(judgeDistance);
    }
    return IsPanGestureAcceptInVerticalDirection(judgeDistance);
}

Offset PanRecognizer::GetRawGlobalLocation(int32_t postEventNodeId)
{
    PointF localPoint(globalPoint_.GetX(), globalPoint_.GetY());
    if (!lastTouchEvent_.history.empty() && (gestureInfo_ && gestureInfo_->GetType() == GestureTypeName::BOXSELECT)) {
        auto lastPoint = lastTouchEvent_.history.back();
        PointF rawLastPoint(lastPoint.GetOffset().GetX(), lastPoint.GetOffset().GetY());
        TransformForRecognizer(
            rawLastPoint, GetAttachedNode(), false, isPostEventResult_, postEventNodeId);
        return Offset(rawLastPoint.GetX(), rawLastPoint.GetY());
    }
    TransformForRecognizer(
        localPoint, GetAttachedNode(), false, isPostEventResult_, postEventNodeId);
    return Offset(localPoint.GetX(), localPoint.GetY());
}

void PanRecognizer::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    touchPoints_.clear();
    averageDistance_.Reset();
    touchPointsDistance_.clear();
    panVelocity_.ResetAll();
    isStartTriggered_ = false;
    localMatrix_.clear();
    delta_ = Offset();
    globalPoint_ = Point();
    mainDelta_ = 0.0;
    isFlushTouchEventsEnd_ = false;
    isForDrag_ = false;
    isStartTriggered_ = false;
    ResSchedTouchOptimizer::GetInstance().SetSlideAcceptOffset(averageDistance_);
}

void PanRecognizer::OnSucceedCancel()
{
    SendCallbackMsg(onActionCancel_, GestureCallbackType::CANCEL);
}

void PanRecognizer::GetGestureEventHalfInfo(GestureEvent* info)
{
    info->SetDeviceId(deviceId_);
    info->SetFingerList(fingerList_);
    info->SetSourceDevice(deviceType_);
    info->SetOffsetX((direction_.type & PanDirection::HORIZONTAL) == 0 ? 0.0 : averageDistance_.GetX());
    info->SetOffsetY((direction_.type & PanDirection::VERTICAL) == 0 ? 0.0 : averageDistance_.GetY());
    info->SetDelta(delta_);
    info->SetVelocity(panVelocity_.GetVelocity());
    info->SetGestureTypeName(GestureTypeName::PAN_GESTURE);
    info->SetMainVelocity(panVelocity_.GetMainAxisVelocity());
}

GestureEvent PanRecognizer::GetGestureEventInfo()
{
    GestureEvent info;
    info.SetTimeStamp(time_);
    UpdateFingerListInfo();
    GetGestureEventHalfInfo(&info);
    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    PointF localPoint(globalPoint_.GetX(), globalPoint_.GetY());
    TransformForRecognizer(
        localPoint, GetAttachedNode(), false, isPostEventResult_, touchPoint.postEventNodeId);
    info.SetRawGlobalLocation(GetRawGlobalLocation(touchPoint.postEventNodeId));
    info.SetPointerId(inputEventType_ == InputEventType::AXIS ? lastAxisEvent_.id : lastTouchEvent_.id);
    info.SetTargetDisplayId(touchPoint.targetDisplayId);
    info.SetIsInterpolated(touchPoint.isInterpolated);
    info.SetInputXDeltaSlope(touchPoint.inputXDeltaSlope);
    info.SetInputYDeltaSlope(touchPoint.inputYDeltaSlope);
    info.SetMainDelta((ResSchedTouchOptimizer::GetInstance().HandleMainDelta(mainDelta_,
        static_cast<double>(touchPoints_.size()), touchPoints_)));
    if (inputEventType_ == InputEventType::AXIS) {
        info.SetScreenLocation(lastAxisEvent_.GetScreenOffset());
        info.SetGlobalDisplayLocation(lastAxisEvent_.GetGlobalDisplayOffset());
        info.SetSourceTool(lastAxisEvent_.sourceTool);
        info.SetVerticalAxis(lastAxisEvent_.verticalAxis);
        info.SetHorizontalAxis(lastAxisEvent_.horizontalAxis);
        info.SetPressedKeyCodes(lastAxisEvent_.pressedCodes);
        info.SetPointerEventId(lastAxisEvent_.touchEventId);
        info.CopyConvertInfoFrom(lastAxisEvent_.convertInfo);
        info.SetPassThrough(lastAxisEvent_.passThrough);
    } else {
        info.SetScreenLocation(lastTouchEvent_.GetScreenOffset());
        info.SetGlobalDisplayLocation(lastTouchEvent_.GetGlobalDisplayOffset());
        info.SetSourceTool(lastTouchEvent_.sourceTool);
        info.SetPressedKeyCodes(lastTouchEvent_.pressedKeyCodes_);
        info.SetPointerEventId(lastTouchEvent_.touchEventId);
        info.CopyConvertInfoFrom(lastTouchEvent_.convertInfo);
        info.SetPassThrough(lastTouchEvent_.passThrough);
    }
    info.SetGlobalPoint(globalPoint_).SetLocalLocation(Offset(localPoint.GetX(), localPoint.GetY()));
    info.SetTarget(GetEventTarget().value_or(EventTarget()));
    info.SetInputEventType(inputEventType_);
    info.SetForce(lastTouchEvent_.force);
    info.SetTiltX(lastTouchEvent_.tiltX.value_or(0.0));
    info.SetTiltY(lastTouchEvent_.tiltY.value_or(0.0));
    info.SetRollAngle(lastTouchEvent_.rollAngle.value_or(0.0));
    info.SetPointerEvent(lastPointEvent_);
    info.SetIsPostEventResult(isPostEventResult_);
    info.SetPostEventNodeId(lastTouchEvent_.postEventNodeId);
    info.SetLastAction(lastAction_);
    return info;
}

void PanRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback, GestureCallbackType type)
{
    std::string callbackName = GetCallbackName(callback);
    if (type == GestureCallbackType::START || type == GestureCallbackType::END || type == GestureCallbackType::CANCEL) {
        std::string callbackTypeStr = (type == GestureCallbackType::START) ? "START" :
            (type == GestureCallbackType::END) ? "END" : "CANCEL";
        extraInfo_ += " " + callbackTypeStr
            + " cBk: " + std::to_string((callback && *callback))
            + " isE: "  + std::to_string(IsEnabled())
            + " gIn: " + std::to_string((!gestureInfo_ || !gestureInfo_->GetDisposeTag()));
    }
    ACE_SCOPED_TRACE("PanRecognizer %s, mainDelta: %f", callbackName.c_str(), mainDelta_);
    if ((type == GestureCallbackType::END || type == GestureCallbackType::CANCEL) && !IsEnabled()) {
        if (panEndOnDisableState_ && *panEndOnDisableState_ && (!gestureInfo_ || !gestureInfo_->GetDisposeTag())) {
            GestureEvent info = GetGestureEventInfo();
            // callback may be overwritten in its invoke so we copy it first
            auto callbackFunction = *panEndOnDisableState_;
            callbackFunction(info);
            HandleReports(info, type);
            localMatrix_.clear();
            return;
        }
    }
    if (callback && *callback && IsEnabled() && (!gestureInfo_ || !gestureInfo_->GetDisposeTag())) {
        GestureEvent info = GetGestureEventInfo();
        // callback may be overwritten in its invoke so we copy it first
        auto callbackFunction = *callback;
        HandleCallbackReports(info, type, PanGestureState::BEFORE);
        callbackFunction(info);
        HandleCallbackReports(info, type, PanGestureState::AFTER);
    }
    if (type == GestureCallbackType::END || type == GestureCallbackType::CANCEL) {
        localMatrix_.clear();
    }
}

void PanRecognizer::HandleCallbackReports(
    const GestureEvent& info, GestureCallbackType type, PanGestureState panGestureState)
{
    if (panGestureState == PanGestureState::BEFORE) {
        HandleGestureAccept(info, type, GestureListenerType::PAN);
    } else if (panGestureState == PanGestureState::AFTER) {
        HandleReports(info, type);
    }
    HandlePanGestureAccept(info, panGestureState, type);
}

void PanRecognizer::HandleReports(const GestureEvent& info, GestureCallbackType type)
{
    if (type == GestureCallbackType::ACTION || type == GestureCallbackType::UPDATE) {
        return;
    }
    auto frameNode = GetAttachedNode().Upgrade();
    CHECK_NULL_VOID(frameNode);
    PanJsonReport panReport;
    panReport.SetCallbackType(type);
    panReport.SetGestureType(GetRecognizerType());
    panReport.SetId(frameNode->GetId());
    panReport.SetPanDirection(static_cast<int32_t>(direction_.type));
    panReport.SetPoint(info.GetGlobalPoint());
    Reporter::GetInstance().HandleUISessionReporting(panReport);
}

GestureJudgeResult PanRecognizer::TriggerGestureJudgeCallback()
{
    auto targetComponent = GetTargetComponent();
    CHECK_NULL_RETURN(targetComponent, GestureJudgeResult::CONTINUE);
    auto gestureRecognizerJudgeFunc = targetComponent->GetOnGestureRecognizerJudgeBegin();
    auto callback = targetComponent->GetOnGestureJudgeBeginCallback();
    auto callbackNative = targetComponent->GetOnGestureJudgeNativeBeginCallback();
    if (!callback && !callbackNative && !sysJudge_ && !gestureRecognizerJudgeFunc) {
        return GestureJudgeResult::CONTINUE;
    }
    auto info = std::make_shared<PanGestureEvent>();
    UpdateFingerListInfo();
    UpdateGestureEventInfo(info);
    if (gestureInfo_) {
        gestureInfo_->SetInputEventType(inputEventType_);
    }
    if (gestureRecognizerJudgeFunc &&
        gestureRecognizerJudgeFunc(info, Claim(this), responseLinkRecognizer_) == GestureJudgeResult::REJECT) {
        return GestureJudgeResult::REJECT;
    }
    if (!gestureRecognizerJudgeFunc && callback && callback(gestureInfo_, info) == GestureJudgeResult::REJECT) {
        // If outer callback exits, prioritize checking outer callback. If outer reject, return reject.
        return GestureJudgeResult::REJECT;
    }
    if (callbackNative && callbackNative(gestureInfo_, info) == GestureJudgeResult::REJECT) {
        // If outer callback doesn't exit or accept, check inner callback. If inner reject, return reject.
        return GestureJudgeResult::REJECT;
    }
    if (sysJudge_ && sysJudge_(gestureInfo_, info) == GestureJudgeResult::REJECT) {
        return GestureJudgeResult::REJECT;
    }
    return GestureJudgeResult::CONTINUE;
}

void PanRecognizer::UpdateGestureEventInfo(std::shared_ptr<PanGestureEvent>& info)
{
    info->SetFingerList(fingerList_);
    info->SetTimeStamp(time_);
    info->SetDeviceId(deviceId_);
    info->SetOffsetX((direction_.type & PanDirection::HORIZONTAL) == 0 ? 0.0 : averageDistance_.GetX());
    info->SetOffsetY((direction_.type & PanDirection::VERTICAL) == 0 ? 0.0 : averageDistance_.GetY());
    info->SetSourceDevice(deviceType_);
    if (inputEventType_ == InputEventType::AXIS) {
        info->SetVelocity(Velocity());
        info->SetMainVelocity(0.0);
        info->SetSourceTool(lastAxisEvent_.sourceTool);
        info->SetVerticalAxis(lastAxisEvent_.verticalAxis);
        info->SetHorizontalAxis(lastAxisEvent_.horizontalAxis);
        info->SetPressedKeyCodes(lastAxisEvent_.pressedCodes);
        info->SetTargetDisplayId(lastAxisEvent_.targetDisplayId);
    } else {
        info->SetVelocity(panVelocity_.GetVelocity());
        info->SetMainVelocity(panVelocity_.GetMainAxisVelocity());
        info->SetSourceTool(lastTouchEvent_.sourceTool);
        info->SetPressedKeyCodes(lastTouchEvent_.pressedKeyCodes_);
        info->SetTargetDisplayId(lastTouchEvent_.targetDisplayId);
    }
    info->SetTarget(GetEventTarget().value_or(EventTarget()));
    info->SetForce(lastTouchEvent_.force);
    info->SetRawInputEventType(inputEventType_);
    info->SetRawInputEvent(lastPointEvent_);
    info->SetRawInputDeviceId(deviceId_);
    info->SetLastAction(lastAction_);
    if (lastTouchEvent_.tiltX.has_value()) {
        info->SetTiltX(lastTouchEvent_.tiltX.value());
    }
    if (lastTouchEvent_.tiltY.has_value()) {
        info->SetTiltY(lastTouchEvent_.tiltY.value());
    }
    if (lastTouchEvent_.rollAngle.has_value()) {
        info->SetRollAngle(lastTouchEvent_.rollAngle.value());
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
        if (refereeState_ == RefereeState::SUCCEED && static_cast<int32_t>(touchPoints_.size()) >= fingers_) {
            SendCallbackMsg(onActionCancel_, GestureCallbackType::CANCEL);
        }
        ResetStatus();
        return false;
    }

    direction_.type = curr->direction_.type;
    newDirection_.type = curr->newDirection_.type;
    distance_ = curr->distance_;
    newDistance_ = curr->newDistance_;
    mouseDistance_ = curr->mouseDistance_;
    distanceMap_ = curr->distanceMap_;
    newDistanceMap_ = curr->newDistanceMap_;
    isLimitFingerCount_ = curr->isLimitFingerCount_;

    onActionStart_ = std::move(curr->onActionStart_);
    onActionUpdate_ = std::move(curr->onActionUpdate_);
    onActionExtUpdate_ = std::move(curr->onActionExtUpdate_);
    onActionEnd_ = std::move(curr->onActionEnd_);
    onActionCancel_ = std::move(curr->onActionCancel_);
    ReconcileGestureInfoFrom(recognizer);
    return true;
}

Axis PanRecognizer::GetAxisDirection()
{
    auto hasHorizontal = direction_.type & PanDirection::HORIZONTAL;
    auto hasVertical = direction_.type & PanDirection::VERTICAL;
    if (direction_.type == PanDirection::ALL || (hasHorizontal && hasVertical)) {
        return Axis::FREE;
    }
    if (hasHorizontal) {
        return Axis::HORIZONTAL;
    }
    if (hasVertical) {
        return Axis::VERTICAL;
    }
    return Axis::NONE;
}

void PanRecognizer::SetDirection(const PanDirection& direction)
{
    ChangeDirection(direction);
    panVelocity_.SetDirection(direction_.type);
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
        auto node = GetAttachedNode().Upgrade();
        TAG_LOGD(AceLogTag::ACE_GESTURE, "Pan change direction from %{public}d to %{public}d, tag = %{public}s",
            static_cast<int32_t>(direction_.type), static_cast<int32_t>(direction.type),
            node ? node->GetTag().c_str() : "null");
        direction_.type = direction.type;
        newDirection_.type = direction.type;
    }
}

void PanRecognizer::ChangeDistance(double distance)
{
    if (GetDistanceConfigFor(SourceTool::UNKNOWN) != distance) {
        distanceMap_.clear();
        newDistanceMap_.clear();
        if (refereeState_ == RefereeState::READY || refereeState_ == RefereeState::DETECTING) {
            distanceMap_[SourceTool::UNKNOWN] = Dimension(
                Dimension(distance, DimensionUnit::PX).ConvertToVp(), DimensionUnit::VP);
            distance_ = distance;
        }
        newDistanceMap_[SourceTool::UNKNOWN] = Dimension(
            Dimension(distance, DimensionUnit::PX).ConvertToVp(), DimensionUnit::VP);
        newDistance_ = distance;
        mouseDistance_ = distance;
    }
}

void PanRecognizer::SetMouseDistance(double distance)
{
    Dimension distanceDimension = Dimension(
        Dimension(distance, DimensionUnit::PX).ConvertToVp(), DimensionUnit::VP);
    distanceMap_[SourceTool::MOUSE] = distanceDimension;
    distanceMap_[SourceTool::TOUCHPAD] = distanceDimension;
    newDistanceMap_[SourceTool::MOUSE] = distanceDimension;
    newDistanceMap_[SourceTool::TOUCHPAD] = distanceDimension;
    mouseDistance_ = distance;
}

double PanRecognizer::GetDistance() const
{
    return GetDistanceConfigFor(deviceTool_);
}

double PanRecognizer::GetDistanceConfigFor(SourceTool sourceTool) const
{
    if (distanceMap_.find(sourceTool) != distanceMap_.end()) {
        return distanceMap_.at(sourceTool).ConvertToPx();
    }
    if (distanceMap_.find(SourceTool::UNKNOWN) != distanceMap_.end()) {
        return distanceMap_.at(SourceTool::UNKNOWN).ConvertToPx();
    }
    return distance_;
}

void PanRecognizer::SetDistanceMap(const PanDistanceMap& distanceMap)
{
    distanceMap_.clear();
    newDistanceMap_.clear();
    for (auto& iter : distanceMap) {
        auto distanceDimension = Dimension(
            Dimension(iter.second, DimensionUnit::PX).ConvertToVp(), DimensionUnit::VP);
        distanceMap_[iter.first] = distanceDimension;
        newDistanceMap_[iter.first] = distanceDimension;
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

RefPtr<GestureSnapshot> PanRecognizer::Dump() const
{
    RefPtr<GestureSnapshot> info = NGGestureRecognizer::Dump();
    std::stringstream oss;
    oss << "direction: " << direction_.type << ", "
        << "isForDrag: " << isForDrag_ << ", "
        << "distanceMap: [";
    for (auto iter : distanceMap_) {
        oss << "sourceTool: " << std::to_string(static_cast<int32_t>(iter.first)) << ", "
            << "distance: " << iter.second.ConvertToPx() << ", ";
    }
    oss << "], distance: " << GetDistanceConfigFor(deviceTool_) << ", "
        << "fingers: " << fingers_ << ", "
        << DumpGestureInfo();
    info->customInfo = oss.str();
    return info;
}

RefPtr<DragEventActuator> PanRecognizer::GetDragEventActuator()
{
    auto targetComponent = GetTargetComponent();
    CHECK_NULL_RETURN(targetComponent, nullptr);
    auto uiNode = targetComponent->GetUINode().Upgrade();
    CHECK_NULL_RETURN(uiNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureEventHub, nullptr);
    return gestureEventHub->GetDragEventActuator();
}

int32_t PanRecognizer::PanVelocity::GetFastestTracker(std::function<double(VelocityTracker&)>&& func)
{
    int32_t maxId = -1;
    double maxV = 0.0;
    for (auto& [id, tracker] : trackerMap_) {
        double v = std::abs(func(tracker));
        if (v > maxV) {
            maxId = id;
            maxV = v;
        }
    }
    return maxId;
}

Velocity PanRecognizer::PanVelocity::GetVelocity()
{
    auto&& func = [](VelocityTracker& tracker) { return tracker.GetVelocity().GetVelocityValue(); };
    int32_t id = GetFastestTracker(func);
    return (id != -1) ? trackerMap_[id].GetVelocity() : Velocity();
}

double PanRecognizer::PanVelocity::GetMainAxisVelocity()
{
    auto&& func = [axis = axis_](VelocityTracker& tracker) {
        tracker.SetMainAxis(axis);
        return tracker.GetMainAxisVelocity();
    };
    int32_t id = GetFastestTracker(func);
    return (id != -1) ? trackerMap_[id].GetMainAxisVelocity() : 0.0;
}

void PanRecognizer::PanVelocity::UpdateTouchPoint(int32_t id, const TouchEvent& event, bool end)
{
    trackerMap_[id].UpdateTouchPoint(event, end,
        event.sourceTool == SourceTool::TOUCHPAD ? TOUCHPAD_STILL_THRESHOLD : VelocityTracker::TOUCH_STILL_THRESHOLD);
}

void PanRecognizer::PanVelocity::Reset(int32_t id)
{
    trackerMap_.erase(id);
}

void PanRecognizer::PanVelocity::ResetAll()
{
    trackerMap_.clear();
}

void PanRecognizer::PanVelocity::SetDirection(int32_t directionType)
{
    auto axis = Axis::FREE;
    if ((directionType & PanDirection::VERTICAL) == 0) {
        axis = Axis::HORIZONTAL;
    } else if ((directionType & PanDirection::HORIZONTAL) == 0) {
        axis = Axis::VERTICAL;
    }
    axis_ = axis;
}

void PanRecognizer::AddOverTimeTrace()
{
    int64_t overTime = GetSysTimestamp();
    int64_t inputTime = overTime;
    if (firstInputTime_.has_value()) {
        inputTime = static_cast<int64_t>(firstInputTime_.value().time_since_epoch().count());
    }
    if (SystemProperties::GetTraceInputEventEnabled()) {
        ACE_SCOPED_TRACE("UserEvent InputTime:%lld OverTime:%lld InputType:PanGesture",
            static_cast<long long>(inputTime), static_cast<long long>(overTime));
    }
    firstInputTime_.reset();
}

void PanRecognizer::UpdateTouchEventInfo(const TouchEvent& event)
{
    globalPoint_ = Point(event.x, event.y);
    lastTouchEvent_ = event;
    PointF windowPoint(event.GetOffset().GetX(), event.GetOffset().GetY());
    PointF windowTouchPoint(touchPoints_[event.id].GetOffset().GetX(), touchPoints_[event.id].GetOffset().GetY());
    TransformForRecognizer(windowPoint, GetAttachedNode(), false, isPostEventResult_, event.postEventNodeId);
    TransformForRecognizer(
        windowTouchPoint, GetAttachedNode(), false, isPostEventResult_, event.postEventNodeId);
    delta_ =
        (Offset(windowPoint.GetX(), windowPoint.GetY()) - Offset(windowTouchPoint.GetX(), windowTouchPoint.GetY()));

    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_GESTURE, "Delta is x %{public}f, y %{public}f ", delta_.GetX(), delta_.GetY());
    }
    mainDelta_ = GetMainAxisDelta();
    averageDistance_ += delta_ / static_cast<double>(touchPoints_.size());
    touchPoints_[event.id] = event;
    touchPointsDistance_[event.id] += delta_;
    time_ = event.time;
}

void PanRecognizer::DispatchPanStartedToPerf(const TouchEvent& event)
{
    int64_t inputTime = event.time.time_since_epoch().count();
    if (inputTime <= 0 || event.sourceType != SourceType::TOUCH) {
        return;
    }
    PerfMonitor* pMonitor = PerfMonitor::GetPerfMonitor();
    if (pMonitor == nullptr) {
        return;
    }
    pMonitor->RecordInputEvent(FIRST_MOVE, PERF_TOUCH_EVENT, inputTime);
}

void PanRecognizer::DumpVelocityInfo(int32_t fingerId)
{
    auto velocityTrackerIter = panVelocity_.GetVelocityMap().find(fingerId);
    if (velocityTrackerIter != panVelocity_.GetVelocityMap().end()) {
        velocityTrackerIter->second.DumpVelocityPoints();
    } else {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Dump velocity fail with fingerId:%{public}d", fingerId);
    }
}

void PanRecognizer::HandlePanGestureAccept(
    const GestureEvent& info, PanGestureState panGestureState, GestureCallbackType type)
{
    if (type == GestureCallbackType::START) {
        currentCallbackState_ = CurrentCallbackState::START;
        auto node = GetAttachedNode().Upgrade();
        UIObserverHandler::GetInstance().NotifyPanGestureStateChange(
            info, Claim(this), node, { panGestureState, currentCallbackState_ });
    } else if (type == GestureCallbackType::END) {
        currentCallbackState_ = CurrentCallbackState::END;
        auto node = GetAttachedNode().Upgrade();
        UIObserverHandler::GetInstance().NotifyPanGestureStateChange(
            info, Claim(this), node, { panGestureState, currentCallbackState_ });
    }
}
} // namespace OHOS::Ace::NG
