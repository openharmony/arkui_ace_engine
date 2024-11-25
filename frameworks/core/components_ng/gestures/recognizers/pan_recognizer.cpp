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

#include "base/perfmonitor/perf_monitor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t MAX_PAN_FINGERS = 10;
constexpr int32_t DEFAULT_PAN_FINGERS = 1;
constexpr int32_t AXIS_PAN_FINGERS = 1;
constexpr float MIN_SPEED_THRESHOLD = 500.0f;

} // namespace

void PanRecognizer::ForceCleanRecognizer()
{
    MultiFingersRecognizer::ForceCleanRecognizer();
    averageDistance_.Reset();
    touchPointsDistance_.clear();
    isStartTriggered_ = false;
}

PanRecognizer::PanRecognizer(int32_t fingers, const PanDirection& direction, double distance)
    : MultiFingersRecognizer(fingers), direction_(direction), distance_(distance), mouseDistance_(distance),
      newFingers_(fingers_), newDistance_(distance_), newDirection_(direction_)
{
    panVelocity_.SetDirection(direction_.type);
    if (fingers_ > MAX_PAN_FINGERS || fingers_ < DEFAULT_PAN_FINGERS) {
        fingers_ = DEFAULT_PAN_FINGERS;
    }
}

RefPtr<Gesture> PanRecognizer::CreateGestureFromRecognizer() const
{
    return AceType::MakeRefPtr<PanGesture>(fingers_, direction_, distance_);
}

PanRecognizer::PanRecognizer(const RefPtr<PanGestureOption>& panGestureOption) : panGestureOption_(panGestureOption)
{
    uint32_t directNum = panGestureOption->GetDirection().type;
    double distanceNumber = panGestureOption->GetDistance();
    int32_t fingersNumber = panGestureOption->GetFingers();

    distance_ = LessNotEqual(distanceNumber, 0.0) ? DEFAULT_PAN_DISTANCE.ConvertToPx() : distanceNumber;
    fingers_ = fingersNumber;
    if (fingers_ > MAX_PAN_FINGERS || fingers_ < DEFAULT_PAN_FINGERS) {
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
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "Pan accepted, tag = %{public}s",
        node ? node->GetTag().c_str() : "null");
    refereeState_ = RefereeState::SUCCEED;
    SendCallbackMsg(onActionStart_);
    // only report the pan gesture starting for touch event
    DispatchPanStartedToPerf(lastTouchEvent_);
    if (IsEnabled()) {
        isStartTriggered_ = true;
    }
    SendCallbackMsg(onActionUpdate_);
    // if gesture is blocked by double click, recognizer will receive up before onAccepted
    // in this case, recognizer need to send onActionEnd when onAccepted
    if (isTouchEventFinished_) {
        isStartTriggered_ = false;
        SendCallbackMsg(onActionEnd_);
    }
}

void PanRecognizer::OnRejected()
{
    // fix griditem drag interrupted by click while pull moving
    if (refereeState_ != RefereeState::SUCCEED) {
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
    panVelocity_.UpdateTouchPoint(event.id, pesudoTouchEvent, end);
    lastAxisEvent_ = event;
    if (!end) {
        lastAxisEvent_.horizontalAxis = pesudoTouchEvent.x;
        lastAxisEvent_.verticalAxis = pesudoTouchEvent.y;
    }
}

void PanRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    isTouchEventFinished_ = false;
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }

    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, pan %{public}d down, state: %{public}d", event.touchEventId,
        event.id, refereeState_);
    fingers_ = newFingers_;
    distance_ = newDistance_;
    direction_ = newDirection_;

    if (direction_.type == PanDirection::NONE) {
        auto node = GetAttachedNode().Upgrade();
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Pan recognizer direction is none, node tag = %{public}s, id = %{public}s",
            node ? node->GetTag().c_str() : "null", node ? std::to_string(node->GetId()).c_str() : "invalid");
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }
    if (event.sourceType == SourceType::MOUSE && !isAllowMouse_) {
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }
    if (!IsInAttachedNode(event)) {
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (fingersId_.find(event.id) == fingersId_.end()) {
        fingersId_.insert(event.id);
    }

    deviceId_ = event.deviceId;
    deviceType_ = event.sourceType;
    lastTouchEvent_ = event;
    touchPoints_[event.id] = event;
    touchPointsDistance_[event.id] = Offset(0.0, 0.0);
    auto fingerNum = static_cast<int32_t>(touchPoints_.size());

    if (fingerNum >= fingers_) {
        if (refereeState_ == RefereeState::READY) {
            panVelocity_.Reset(event.id);
            UpdateTouchPointInVelocityTracker(event);
            refereeState_ = RefereeState::DETECTING;
        } else {
            TAG_LOGI(AceLogTag::ACE_GESTURE, "Pan gesture refereeState is not READY");
        }
    }
}

void PanRecognizer::HandleTouchDownEvent(const AxisEvent& event)
{
    isTouchEventFinished_ = false;
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }
    if (event.isRotationEvent) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, pan %{public}d axis start, state:%{public}d",
        event.touchEventId, event.id, refereeState_);
    fingers_ = newFingers_;
    distance_ = newDistance_;
    direction_ = newDirection_;

    if (fingers_ != AXIS_PAN_FINGERS) {
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (direction_.type == PanDirection::NONE) {
        Adjudicate(Claim(this), GestureDisposal::REJECT);
        return;
    }

    deviceId_ = event.deviceId;
    deviceType_ = event.sourceType;
    lastAxisEvent_ = event;

    touchPoints_[event.id] = TouchEvent();
    UpdateTouchPointWithAxisEvent(event);
    panVelocity_.Reset(event.id);
    auto pesudoTouchEvent = TouchEvent();
    pesudoTouchEvent.time = event.time;
    auto revertAxisValue = event.ConvertToSummationAxisValue(lastAxisEvent_);
    pesudoTouchEvent.x = revertAxisValue.first;
    pesudoTouchEvent.y = revertAxisValue.second;
    panVelocity_.UpdateTouchPoint(event.id, pesudoTouchEvent, false);
    refereeState_ = RefereeState::DETECTING;
}

void PanRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW,
        "Id:%{public}d, pan %{public}d up, state: %{public}d, currentFingers: %{public}d, fingers: %{public}d",
        event.touchEventId, event.id, refereeState_, currentFingers_, fingers_);
    extraInfo_ = "currentFingers: " + std::to_string(currentFingers_) + " fingers: " + std::to_string(fingers_);
    if (fingersId_.find(event.id) != fingersId_.end()) {
        fingersId_.erase(event.id);
    }
    if (currentFingers_ < fingers_) {
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
            auto velocityTrackerIter = panVelocity_.GetVelocityMap().find(event.id);
            if (velocityTrackerIter != panVelocity_.GetVelocityMap().end() &&
                std::abs(panVelocity_.GetMainAxisVelocity()) <= MIN_SPEED_THRESHOLD) {
                velocityTrackerIter->second.DumpVelocityPoints();
            }
            // last one to fire end.
            isStartTriggered_ = false;
            SendCallbackMsg(onActionEnd_);
            averageDistance_.Reset();
            AddOverTimeTrace();
            refereeState_ = RefereeState::READY;
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
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, pan %{public}d axis end, state: %{public}d",
        event.touchEventId, event.id, refereeState_);
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

    auto velocityTrackerIter = panVelocity_.GetVelocityMap().find(event.id);
    if (velocityTrackerIter != panVelocity_.GetVelocityMap().end()) {
        velocityTrackerIter->second.DumpVelocityPoints();
    }
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
        "PanVelocity main axis velocity is %{public}f", panVelocity_.GetMainAxisVelocity());

    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        // AxisEvent is single one.
        isStartTriggered_ = false;
        SendCallbackMsg(onActionEnd_);
        AddOverTimeTrace();
    }
    panVelocity_.ResetAll();
}

void PanRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    isTouchEventFinished_ = false;
    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
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
                SendCallbackMsg(onActionStart_);
                isStartTriggered_ = true;
            }
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
    isTouchEventFinished_ = false;
    if (fingers_ != AXIS_PAN_FINGERS || event.isRotationEvent) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    bool isShiftKeyPressed = false;
    bool hasDifferentDirectionGesture = false;
    if (pipeline) {
        isShiftKeyPressed =
            event.HasKey(KeyCode::KEY_SHIFT_LEFT) || event.HasKey(KeyCode::KEY_SHIFT_RIGHT);
        hasDifferentDirectionGesture = pipeline->HasDifferentDirectionGesture();
    }
    delta_ = event.ConvertToOffset(isShiftKeyPressed, hasDifferentDirectionGesture);
    if (event.sourceTool == SourceTool::MOUSE) {
        if ((direction_.type & PanDirection::HORIZONTAL) == 0) { // Direction is vertical
            delta_.SetX(0.0);
        } else if ((direction_.type & PanDirection::VERTICAL) == 0) { // Direction is horizontal
            delta_.SetY(0.0);
        }
    }

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
            SendCallbackMsg(onActionStart_);
            isStartTriggered_ = true;
        }
        SendCallbackMsg(onActionUpdate_);
    }
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
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, pan %{public}d cancel", event.touchEventId, event.id);
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED && static_cast<int32_t>(touchPoints_.size()) == fingers_) {
        // AxisEvent is single one.
        SendCancelMsg();
        refereeState_ = RefereeState::READY;
    } else if (refereeState_ == RefereeState::SUCCEED) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
            "PanRecognizer touchPoints size not equal fingers_, not send cancel callback.");
    }
}

void PanRecognizer::HandleTouchCancelEvent(const AxisEvent& event)
{
    isTouchEventFinished_ = false;
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "Id:%{public}d, pan axis cancel", event.touchEventId);
    if ((refereeState_ != RefereeState::SUCCEED) && (refereeState_ != RefereeState::FAIL)) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCancelMsg();
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
    auto judgeDistance = distance_;
    if (deviceType_ == SourceType::MOUSE) {
        judgeDistance = mouseDistance_;
    }
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
    auto judgeDistance = distance_;
    if (deviceType_ == SourceType::MOUSE) { // use mouseDistance_
        judgeDistance = mouseDistance_;
    }
    // when version >= 14, if distance_ = 0, panGesture will accept when receive Down event
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN) &&
        NearZero(judgeDistance) && direction_.type != PanDirection::NONE) {
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
        NGGestureRecognizer::Transform(
            rawLastPoint, GetAttachedNode(), false, isPostEventResult_, postEventNodeId);
        return Offset(rawLastPoint.GetX(), rawLastPoint.GetY());
    }
    NGGestureRecognizer::Transform(
        localPoint, GetAttachedNode(), false, isPostEventResult_, postEventNodeId);
    return Offset(localPoint.GetX(), localPoint.GetY());
}

void PanRecognizer::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    touchPoints_.clear();
    averageDistance_.Reset();
    touchPointsDistance_.clear();
    isStartTriggered_ = false;
}

void PanRecognizer::OnSucceedCancel()
{
    SendCancelMsg();
}

GestureEvent PanRecognizer::GetGestureEventInfo()
{
    GestureEvent info;
    info.SetTimeStamp(time_);
    UpdateFingerListInfo();
    info.SetDeviceId(deviceId_);
    info.SetFingerList(fingerList_);
    info.SetSourceDevice(deviceType_);
    info.SetOffsetX((direction_.type & PanDirection::HORIZONTAL) == 0 ? 0.0 : averageDistance_.GetX());
    info.SetOffsetY((direction_.type & PanDirection::VERTICAL) == 0 ? 0.0 : averageDistance_.GetY());
    info.SetDelta(delta_);
    info.SetVelocity(panVelocity_.GetVelocity());
    info.SetMainVelocity(panVelocity_.GetMainAxisVelocity());
    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    PointF localPoint(globalPoint_.GetX(), globalPoint_.GetY());
    NGGestureRecognizer::Transform(
        localPoint, GetAttachedNode(), false, isPostEventResult_, touchPoint.postEventNodeId);
    info.SetRawGlobalLocation(GetRawGlobalLocation(touchPoint.postEventNodeId));
    info.SetPointerId(touchPoint.id);
    info.SetTargetDisplayId(touchPoint.targetDisplayId);
    info.SetIsInterpolated(touchPoint.isInterpolated);
    info.SetInputXDeltaSlope(touchPoint.inputXDeltaSlope);
    info.SetInputYDeltaSlope(touchPoint.inputYDeltaSlope);
    info.SetMainDelta(mainDelta_ / static_cast<double>(touchPoints_.size()));
    if (inputEventType_ == InputEventType::AXIS) {
        info.SetScreenLocation(lastAxisEvent_.GetScreenOffset());
        info.SetSourceTool(lastAxisEvent_.sourceTool);
        info.SetVerticalAxis(lastAxisEvent_.verticalAxis);
        info.SetHorizontalAxis(lastAxisEvent_.horizontalAxis);
        info.SetPressedKeyCodes(lastAxisEvent_.pressedCodes);
    } else {
        info.SetScreenLocation(lastTouchEvent_.GetScreenOffset());
        info.SetSourceTool(lastTouchEvent_.sourceTool);
        info.SetPressedKeyCodes(lastTouchEvent_.pressedKeyCodes_);
    }
    info.SetGlobalPoint(globalPoint_).SetLocalLocation(Offset(localPoint.GetX(), localPoint.GetY()));
    info.SetTarget(GetEventTarget().value_or(EventTarget()));
    info.SetInputEventType(inputEventType_);
    info.SetForce(lastTouchEvent_.force);
    info.SetTiltX(lastTouchEvent_.tiltX.value_or(0.0));
    info.SetTiltY(lastTouchEvent_.tiltY.value_or(0.0));
    info.SetPointerEvent(lastPointEvent_);
    info.SetIsPostEventResult(isPostEventResult_);
    info.SetPostEventNodeId(lastTouchEvent_.postEventNodeId);
    return info;
}

void PanRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback)
{
    if (callback && *callback && IsEnabled()) {
        GestureEvent info = GetGestureEventInfo();
        // callback may be overwritten in its invoke so we copy it first
        auto callbackFunction = *callback;
        callbackFunction(info);
    }
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
    } else {
        info->SetVelocity(panVelocity_.GetVelocity());
        info->SetMainVelocity(panVelocity_.GetMainAxisVelocity());
        info->SetSourceTool(lastTouchEvent_.sourceTool);
    }
    info->SetTarget(GetEventTarget().value_or(EventTarget()));
    info->SetForce(lastTouchEvent_.force);
    if (lastTouchEvent_.tiltX.has_value()) {
        info->SetTiltX(lastTouchEvent_.tiltX.value());
    }
    if (lastTouchEvent_.tiltY.has_value()) {
        info->SetTiltY(lastTouchEvent_.tiltY.value());
    }
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

bool PanRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    RefPtr<PanRecognizer> curr = AceType::DynamicCast<PanRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (curr->fingers_ != fingers_ || curr->priorityMask_ != priorityMask_) {
        if (refereeState_ == RefereeState::SUCCEED && static_cast<int32_t>(touchPoints_.size()) >= fingers_) {
            SendCancelMsg();
        }
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

RefPtr<GestureSnapshot> PanRecognizer::Dump() const
{
    RefPtr<GestureSnapshot> info = NGGestureRecognizer::Dump();
    std::stringstream oss;
    oss << "direction: " << direction_.type << ", "
        << "isForDrag: " << isForDrag_ << ", "
        << "distance: " << distance_ << ", "
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
    trackerMap_[id].UpdateTouchPoint(event, end);
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
    NGGestureRecognizer::Transform(windowPoint, GetAttachedNode(), false, isPostEventResult_, event.postEventNodeId);
    NGGestureRecognizer::Transform(
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
} // namespace OHOS::Ace::NG
