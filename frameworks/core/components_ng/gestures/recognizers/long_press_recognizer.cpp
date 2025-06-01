/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"
#include "core/components_ng/manager/event/json_child_report.h"
#include "core/common/reporter/reporter.h"
#include "core/components_ng/manager/event/json_report.h"
#include "core/components_ng/event/event_constants.h"

#include "core/components_ng/gestures/recognizers/gestures_extra_handler.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double MAX_THRESHOLD = 15.0;
constexpr int32_t MAX_LONGPRESS_FINGERS = 10;
constexpr int32_t DEFAULT_LONGPRESS_FINGERS = 1;
constexpr int32_t DEFAULT_LONGPRESS_DURATION = 500;
} // namespace

LongPressRecognizer::LongPressRecognizer(
    int32_t duration, int32_t fingers, bool repeat, bool isForDrag, bool isDisableMouseLeft, bool isLimitFingerCount)
    : MultiFingersRecognizer(fingers, isLimitFingerCount), duration_(duration), repeat_(repeat), isForDrag_(isForDrag),
      isDisableMouseLeft_(isDisableMouseLeft)
{
    if (fingers_ > MAX_LONGPRESS_FINGERS || fingers_ < DEFAULT_LONGPRESS_FINGERS) {
        fingers_ = DEFAULT_LONGPRESS_FINGERS;
    }
    if (duration_ <= 0) {
        duration_ = DEFAULT_LONGPRESS_DURATION;
    }

    SetOnAccessibility(GetOnAccessibilityEventFunc());
}

void LongPressRecognizer::OnAccepted()
{
    int64_t acceptTime = GetSysTimestamp();
    int64_t inputTime = acceptTime;
    if (firstInputTime_.has_value()) {
        inputTime = static_cast<int64_t>(firstInputTime_.value().time_since_epoch().count());
    }
    if (SystemProperties::GetTraceInputEventEnabled()) {
        ACE_SCOPED_TRACE("UserEvent InputTime:%lld AcceptTime:%lld InputType:LongPressGesture",
            static_cast<long long>(inputTime), static_cast<long long>(acceptTime));
    }

    auto node = GetAttachedNode().Upgrade();
    TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW, "LongPress accepted, tag = %{public}s",
        node ? node->GetTag().c_str() : "null");
    if (onAccessibilityEventFunc_) {
        auto onAccessibilityEventFunc = onAccessibilityEventFunc_;
        onAccessibilityEventFunc(AccessibilityEventType::LONG_PRESS);
    }
    lastRefereeState_ = refereeState_;
    refereeState_ = RefereeState::SUCCEED;
    if (!touchPoints_.empty() && touchPoints_.begin()->second.sourceType == SourceType::MOUSE) {
        std::chrono::nanoseconds nanoseconds(GetSysTimestamp());
        time_ = TimeStamp(nanoseconds);
    }

    TouchEvent touchPoint = {};
    if (!touchPoints_.empty()) {
        touchPoint = touchPoints_.begin()->second;
    }
    localMatrix_ = NGGestureRecognizer::GetTransformMatrix(GetAttachedNode(), false,
        isPostEventResult_, touchPoint.postEventNodeId);
    UpdateFingerListInfo();
    SendCallbackMsg(onAction_, false, GestureCallbackType::START);
    if (isLimitFingerCount_ && hasRepeated_) {
        return;
    }
    if (repeat_) {
        hasRepeated_ = true;
        StartRepeatTimer();
    }
}

void LongPressRecognizer::OnRejected()
{
    if (refereeState_ == RefereeState::SUCCEED) {
        return;
    }
    SendRejectMsg();
    lastRefereeState_ = refereeState_;
    refereeState_ = RefereeState::FAIL;
    firstInputTime_.reset();
}

void LongPressRecognizer::ThumbnailTimer(int32_t time)
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    if (!callback_) {
        return;
    }
    auto&& callback = [weakPtr = AceType::WeakClaim(this), customCallback = callback_]() {
        auto refPtr = weakPtr.Upgrade();
        if (!refPtr) {
            return;
        }
        if (refPtr->refereeState_ == RefereeState::DETECTING) {
            customCallback(Offset(refPtr->globalPoint_.GetX(), refPtr->globalPoint_.GetY()));
        }
    };
    thumbnailTimer_.Reset(callback);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(thumbnailTimer_, time, "ArkUIGestureLongPressThumbnailTimer");
}

void LongPressRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    extraInfo_ = "";
    lastAction_ = static_cast<int32_t>(TouchType::DOWN);
    if (!firstInputTime_.has_value()) {
        firstInputTime_ = event.time;
    }

    if (isDisableMouseLeft_ && event.sourceType == SourceType::MOUSE) {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Mouse left button is disabled for long press recognizer");
        extraInfo_ += "Reject: mouse left button disabled.";
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    int32_t curDuration = duration_;
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (!IsPostEventResult()) {
        int64_t currentTimeStamp = GetSysTimestamp();
        int64_t eventTimeStamp = static_cast<int64_t>(event.time.time_since_epoch().count());
        if (currentTimeStamp > eventTimeStamp) {
            // nanoseconds to millisceond.
            curDuration = curDuration - static_cast<int32_t>((currentTimeStamp - eventTimeStamp) / (1000 * 1000));
            curDuration = curDuration < 0 ? 0 : curDuration;
        }
    }
#endif
    int64_t currentTimeStamp = GetSysTimestamp();
    extraInfo_ += "currentTimeStamp: " + std::to_string(currentTimeStamp);
    extraInfo_ += ", curDuration: " + std::to_string(curDuration);
    extraInfo_ += ", duration_: " + std::to_string(duration_);
    extraInfo_ += ".";
    if (isForDrag_ && event.sourceType == SourceType::MOUSE) {
        curDuration = 0;
    }
    if ((touchRestrict_.forbiddenType & TouchRestrict::LONG_PRESS) == TouchRestrict::LONG_PRESS) {
        extraInfo_ += "Reject: long press forbidden.";
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
    if (fingersId_.find(event.id) == fingersId_.end()) {
        fingersId_.insert(event.id);
    }
    longPressFingerCountForSequence_++;
    globalPoint_ = Point(event.x, event.y);
    touchPoints_[event.id] = event;
    lastTouchEvent_ = event;
    UpdateFingerListInfo();
    if (GetValidFingersCount() == fingers_) {
        if (refereeState_ == RefereeState::SUCCEED && repeat_) {
            StartRepeatTimer();
            return;
        }
        lastRefereeState_ = refereeState_;
        refereeState_ = RefereeState::DETECTING;
        if (useCatchMode_) {
            DeadlineTimer(curDuration, true);
        } else {
            DeadlineTimer(curDuration, false);
        }
    } else {
        PrintCurrentFingersInfo();
    }

    ThumbnailTimer(thumbnailDeadline);
}

void LongPressRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    lastAction_ = static_cast<int32_t>(TouchType::UP);
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    context->RemoveGestureTask(task_);
    if (fingersId_.find(event.id) != fingersId_.end()) {
        fingersId_.erase(event.id);
    }
    if (touchPoints_.find(event.id) != touchPoints_.end()) {
        touchPoints_.erase(event.id);
    }
    longPressFingerCountForSequence_--;
    lastTouchEvent_ = event;
    if (refereeState_ == RefereeState::SUCCEED) {
        if (isLimitFingerCount_ && static_cast<int32_t>(touchPoints_.size()) == fingers_) {
            SendCallbackMsg(onAction_, false, GestureCallbackType::START);
        }
        if (static_cast<int32_t>(touchPoints_.size()) == 0) {
            hasRepeated_ = false;
            SendCallbackMsg(onActionEnd_, false, GestureCallbackType::END);
            int64_t overTime = GetSysTimestamp();
            int64_t inputTime = overTime;
            if (firstInputTime_.has_value()) {
                inputTime = static_cast<int64_t>(firstInputTime_.value().time_since_epoch().count());
            }
            inputTime_ = overTime - inputTime;
            SendCallbackMsg(onActionEnd_, false, GestureCallbackType::END);
            if (SystemProperties::GetTraceInputEventEnabled()) {
                ACE_SCOPED_TRACE("UserEvent InputTime:%lld OverTime:%lld InputType:LongPressGesture",
                    static_cast<long long>(inputTime), static_cast<long long>(overTime));
            }
            firstInputTime_.reset();
            ResetStateVoluntarily();
        }
    } else {
        extraInfo_ += "Reject: received up but not succeed.";
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    }
}

void LongPressRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    lastTouchEvent_.pressedKeyCodes_ = event.pressedKeyCodes_;
    lastAction_ = static_cast<int32_t>(TouchType::MOVE);
    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        return;
    }
    if (IsRefereeFinished()) {
        return;
    }
    Offset offset = event.GetOffset() - touchPoints_[event.id].GetOffset();
    if (offset.GetDistance() > MAX_THRESHOLD) {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "LongPress move over max threshold");
        extraInfo_ += "Reject: move over max threshold.";
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
    touchPoints_[event.id].operatingHand = event.operatingHand;
    lastTouchEvent_ = event;
    UpdateFingerListInfo();
    time_ = event.time;
}

void LongPressRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    if (refereeState_ == RefereeState::FAIL) {
        return;
    }
    lastAction_ = static_cast<int32_t>(TouchType::CANCEL);
    lastTouchEvent_ = event;
    if (touchPoints_.find(event.id) != touchPoints_.end()) {
        touchPoints_.erase(event.id);
    }
    if (refereeState_ == RefereeState::SUCCEED && static_cast<int32_t>(touchPoints_.size()) == 0) {
        SendCallbackMsg(onActionCancel_, false, GestureCallbackType::CANCEL);
        lastRefereeState_ = RefereeState::READY;
        refereeState_ = RefereeState::READY;
    } else if (refereeState_ == RefereeState::SUCCEED) {
        TAG_LOGI(AceLogTag::ACE_INPUTKEYFLOW,
            "LongPressRecognizer touchPoints size not equal 0, not send cancel callback.");
        extraInfo_ += "Reject: received cancel and succeed.";
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    } else {
        extraInfo_ += "Reject: received cancel but not succeed.";
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    }
}

void LongPressRecognizer::HandleOverdueDeadline(bool isCatchMode)
{
    if (refereeState_ != RefereeState::DETECTING) {
        return;
    }
    if (!isCatchMode) {
        OnAccepted();
        return;
    }
    if (gestureInfo_ && gestureInfo_->GetType() == GestureTypeName::DRAG) {
        auto dragEventActuator = GetDragEventActuator();
        CHECK_NULL_VOID(dragEventActuator);
        if (dragEventActuator->IsDragUserReject()) {
            TAG_LOGI(AceLogTag::ACE_GESTURE, "Drag long press reject because of user's reject");
            extraInfo_ += "Reject: user reject.";
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return;
        }
    }
    auto onGestureJudgeBeginResult = TriggerGestureJudgeCallback();
    if (onGestureJudgeBeginResult == GestureJudgeResult::REJECT) {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Long press reject as judge result is reject");
        extraInfo_ += "Reject: judge reject.";
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        if (gestureInfo_ && gestureInfo_->GetType() == GestureTypeName::DRAG) {
            auto dragEventActuator = GetDragEventActuator();
            CHECK_NULL_VOID(dragEventActuator);
            dragEventActuator->SetIsDragUserReject(true);
        }
        return;
    }
    if (CheckLimitFinger()) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
    Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
}

void LongPressRecognizer::DeadlineTimer(int32_t time, bool isCatchMode)
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);

    auto&& callback = [weakPtr = AceType::WeakClaim(this), isCatchMode]() {
        auto refPtr = weakPtr.Upgrade();
        if (refPtr) {
            refPtr->HandleOverdueDeadline(isCatchMode);
        }
    };
    task_ = { WeakClaim(this), GetSysTimestamp(), time, callback };
    context->AddGestureTask(task_);

    auto&& flushCallback = []() {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->RequestFrame();
    };
    deadlineTimer_.Reset(flushCallback);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(deadlineTimer_, time, "ArkUIGestureLongPressDeadlineTimer");
}

void LongPressRecognizer::DoRepeat()
{
    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        return;
    }
    if (static_cast<int32_t>(touchPoints_.size()) > fingers_ && isLimitFingerCount_) {
        return;
    }
    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onAction_, true, GestureCallbackType::START);
        StartRepeatTimer();
    }
}

void LongPressRecognizer::StartRepeatTimer()
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);

    auto&& callback = [weakPtr = AceType::WeakClaim(this)]() {
        auto refPtr = weakPtr.Upgrade();
        if (refPtr) {
            refPtr->DoRepeat();
        }
    };
    timer_.Reset(callback);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(timer_, duration_, "ArkUIGestureLongPressRepeatTimer");
}

void LongPressRecognizer::RemoteRepeatTimer()
{
    longPressFingerCountForSequence_--;
    if (longPressFingerCountForSequence_ < fingers_) {
        timer_.Cancel();
    }
}

double LongPressRecognizer::ConvertPxToVp(double offset) const
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(context, offset);

    double vpOffset = context->ConvertPxToVp(Dimension(offset, DimensionUnit::PX));
    return vpOffset;
}

void LongPressRecognizer::SendCallbackMsg(
    const std::unique_ptr<GestureEventFunc>& callback, bool isRepeat, GestureCallbackType type)
{
    std::string callbackName = GetCallbackName(callback);
    ACE_SCOPED_TRACE("LongPressRecognizer %s", callbackName.c_str());
    auto extraHandlingResult = GestureExtraHandler::IsGestureShouldBeAbandoned(AceType::Claim(this));
    if ((gestureInfo_ && gestureInfo_->GetDisposeTag()) || extraHandlingResult ||
        (!isOnActionTriggered_ && type != GestureCallbackType::START)) {
        return;
    }
    if (type == GestureCallbackType::END || type == GestureCallbackType::CANCEL) {
        isOnActionTriggered_ = false;
    }
    if (type == GestureCallbackType::START) {
        isOnActionTriggered_ = true;
    }
    if (callback && *callback) {
        GestureEvent info;
        info.SetLastAction(lastAction_);
        info.SetGestureTypeName(GestureTypeName::LONG_PRESS_GESTURE);
        info.SetTimeStamp(time_);
        info.SetRepeat(isRepeat);
        info.SetFingerList(fingerList_);
        info.SetSourceDevice(deviceType_);
        info.SetDeviceId(deviceId_);
        info.SetTargetDisplayId(lastTouchEvent_.targetDisplayId);
        info.SetGlobalPoint(globalPoint_);
        info.SetScreenLocation(lastTouchEvent_.GetScreenOffset());
        info.SetGlobalLocation(lastTouchEvent_.GetOffset())
            .SetLocalLocation(lastTouchEvent_.GetOffset() - coordinateOffset_);
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
        info.SetSourceTool(lastTouchEvent_.sourceTool);
        info.SetPointerEvent(lastPointEvent_);
        Platform::UpdatePressedKeyCodes(lastTouchEvent_.pressedKeyCodes_);
        info.SetPressedKeyCodes(lastTouchEvent_.pressedKeyCodes_);
        info.SetInputEventType(inputEventType_);
        info.CopyConvertInfoFrom(lastTouchEvent_.convertInfo);
        // callback may be overwritten in its invoke so we copy it first
        auto callbackFunction = *callback;
        callbackFunction(info);
        HandleReports(info, type);
        if (type == GestureCallbackType::START && longPressRecorder_ && *longPressRecorder_) {
            (*longPressRecorder_)(info);
        }
    }
}

void LongPressRecognizer::HandleReports(const GestureEvent& info, GestureCallbackType type)
{
    if (type != GestureCallbackType::END) {
        return;
    }
    auto frameNode = GetAttachedNode().Upgrade();
    CHECK_NULL_VOID(frameNode);
    LongPressJsonReport longPressReport;
    longPressReport.SetCallbackType(type);
    longPressReport.SetGestureType(GetRecognizerType());
    longPressReport.SetId(frameNode->GetId());
    longPressReport.SetDuration(inputTime_);
    longPressReport.SetPoint(info.GetGlobalPoint());
    Reporter::GetInstance().HandleUISessionReporting(longPressReport);
}

void LongPressRecognizer::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    timer_.Cancel();
    deadlineTimer_.Cancel();
    localMatrix_.clear();
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    context->RemoveGestureTask(task_);
    globalPoint_ = Point();
    hasRepeated_ = false;
    longPressFingerCountForSequence_ = 0;
    isOnActionTriggered_ = false;
}

bool LongPressRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    RefPtr<LongPressRecognizer> curr = AceType::DynamicCast<LongPressRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (curr->duration_ != duration_ || curr->fingers_ != fingers_ || curr->repeat_ != repeat_ ||
        curr->priorityMask_ != priorityMask_) {
        if (refereeState_ == RefereeState::SUCCEED && static_cast<int32_t>(touchPoints_.size()) > 0) {
            ACE_SCOPED_TRACE("LongPressRecognizer onActionCancel");
            SendCallbackMsg(onActionCancel_, false, GestureCallbackType::CANCEL);
        }
        ResetStatus();
        return false;
    }
    isLimitFingerCount_ = curr->isLimitFingerCount_;

    onAction_ = std::move(curr->onAction_);
    onActionEnd_ = std::move(curr->onActionEnd_);
    onActionCancel_ = std::move(curr->onActionCancel_);
    ReconcileGestureInfoFrom(recognizer);
    return true;
}

GestureEventFunc LongPressRecognizer::GetLongPressActionFunc()
{
    auto callback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto longPressRecognizer = weak.Upgrade();
        CHECK_NULL_VOID(longPressRecognizer);
        if (longPressRecognizer->onAction_) {
            (*(longPressRecognizer->onAction_))(info);
        }
        if (longPressRecognizer->onActionEnd_) {
            (*(longPressRecognizer->onActionEnd_))(info);
        }
    };
    return callback;
}

RefPtr<GestureSnapshot> LongPressRecognizer::Dump() const
{
    RefPtr<GestureSnapshot> info = NGGestureRecognizer::Dump();
    std::stringstream oss;
    oss << "duration: " << duration_ << ", "
        << "isForDrag: " << isForDrag_ << ", "
        << "repeat: " << repeat_ << ", "
        << "fingers: " << fingers_ << ", "
        << DumpGestureInfo();
    info->customInfo = oss.str();
    return info;
}

void LongPressRecognizer::PrintCurrentFingersInfo() const
{
    std::string log = "Fingers number = ";
    log += std::to_string(GetValidFingersCount());
    log += " fingers_ = ";
    log += std::to_string(fingers_);
    log += ". ";
    for (const auto& iter : touchPoints_) {
        log += "Event id = ";
        log += std::to_string(iter.first);
        log += ", event type = ";
        log += std::to_string(static_cast<int32_t>(iter.second.type));
        log += "; ";
    }
    TAG_LOGI(AceLogTag::ACE_GESTURE, "Finger info : %{public}s", log.c_str());
}

GestureJudgeResult LongPressRecognizer::TriggerGestureJudgeCallback()
{
    auto targetComponent = GetTargetComponent();
    CHECK_NULL_RETURN(targetComponent, GestureJudgeResult::CONTINUE);
    auto gestureRecognizerJudgeFunc = targetComponent->GetOnGestureRecognizerJudgeBegin();
    auto callback = targetComponent->GetOnGestureJudgeBeginCallback();
    auto callbackNative = targetComponent->GetOnGestureJudgeNativeBeginCallback();
    if (!callback && !callbackNative && !gestureRecognizerJudgeFunc) {
        return GestureJudgeResult::CONTINUE;
    }
    auto info = std::make_shared<LongPressGestureEvent>();
    info->SetTimeStamp(time_);
    info->SetDeviceId(deviceId_);
    info->SetRepeat(repeat_);
    info->SetFingerList(fingerList_);
    TouchEvent trackPoint = {};
    if (!touchPoints_.empty()) {
        trackPoint = touchPoints_.begin()->second;
    }
    info->SetSourceDevice(deviceType_);
    info->SetTarget(GetEventTarget().value_or(EventTarget()));
    info->SetForce(trackPoint.force);
    if (gestureInfo_) {
        gestureInfo_->SetInputEventType(inputEventType_);
    }
    if (trackPoint.tiltX.has_value()) {
        info->SetTiltX(trackPoint.tiltX.value());
    }
    if (trackPoint.tiltY.has_value()) {
        info->SetTiltY(trackPoint.tiltY.value());
    }
    if (trackPoint.rollAngle.has_value()) {
        info->SetRollAngle(trackPoint.rollAngle.value());
    }
    info->SetSourceTool(trackPoint.sourceTool);
    info->SetRawInputEventType(inputEventType_);
    info->SetRawInputEvent(lastPointEvent_);
    info->SetRawInputDeviceId(deviceId_);
    info->SetLastAction(lastAction_);
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
    return GestureJudgeResult::CONTINUE;
}

RefPtr<DragEventActuator> LongPressRecognizer::GetDragEventActuator()
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

void LongPressRecognizer::ForceCleanRecognizer()
{
    MultiFingersRecognizer::ForceCleanRecognizer();
    timer_.Cancel();
    deadlineTimer_.Cancel();
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    context->RemoveGestureTask(task_);
    longPressFingerCountForSequence_ = 0;
    isOnActionTriggered_ = false;
}

OnAccessibilityEventFunc LongPressRecognizer::GetOnAccessibilityEventFunc()
{
    auto callback = [weak = WeakClaim(this)](AccessibilityEventType eventType) {
        auto recognizer = weak.Upgrade();
        CHECK_NULL_VOID(recognizer);
        auto node = recognizer->GetAttachedNode().Upgrade();
        CHECK_NULL_VOID(node);
        node->OnAccessibilityEvent(eventType);
    };
    return callback;
}

} // namespace OHOS::Ace::NG
