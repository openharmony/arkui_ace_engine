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

#include "base/perf/socperf_client.h"
#include "base/thread/frame_trace_adapter.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/gestures/base_gesture_event.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/event/ace_events.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double MAX_THRESHOLD = 15.0;
constexpr int32_t MAX_LONGPRESS_FINGERS = 10;
constexpr int32_t DEFAULT_LONGPRESS_FINGERS = 1;
constexpr int32_t DEFAULT_LONGPRESS_DURATION = 500;
} // namespace

LongPressRecognizer::LongPressRecognizer(
    int32_t duration, int32_t fingers, bool repeat, bool isForDrag, bool isDisableMouseLeft)
    : MultiFingersRecognizer(fingers), duration_(duration), repeat_(repeat), isForDrag_(isForDrag),
      isDisableMouseLeft_(isDisableMouseLeft)
{
    if (fingers_ > MAX_LONGPRESS_FINGERS || fingers_ < DEFAULT_LONGPRESS_FINGERS) {
        fingers_ = DEFAULT_LONGPRESS_FINGERS;
    }
    if (duration_ <= 0) {
        duration_ = DEFAULT_LONGPRESS_DURATION;
    }
}

void LongPressRecognizer::OnAccepted()
{
    auto node = GetAttachedNode().Upgrade();
    TAG_LOGI(AceLogTag::ACE_GESTURE, "Long press gesture has been accepted, node tag = %{public}s, id = %{public}s",
        node ? node->GetTag().c_str() : "null", node ? std::to_string(node->GetId()).c_str() : "invalid");
    if (onAccessibilityEventFunc_) {
        onAccessibilityEventFunc_(AccessibilityEventType::LONG_PRESS);
    }
    refereeState_ = RefereeState::SUCCEED;
    if (onLongPress_ && !touchPoints_.empty()) {
        TouchEvent trackPoint = touchPoints_.begin()->second;
        PointF localPoint(trackPoint.GetOffset().GetX(), trackPoint.GetOffset().GetY());
        NGGestureRecognizer::Transform(localPoint, GetAttachedNode());
        LongPressInfo info(trackPoint.id);
        info.SetTimeStamp(time_);
        info.SetScreenLocation(trackPoint.GetScreenOffset());
        info.SetGlobalLocation(trackPoint.GetOffset()).SetLocalLocation(Offset(localPoint.GetX(), localPoint.GetY()));
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
        onLongPress_(info);
    }

    UpdateFingerListInfo();
    SendCallbackMsg(onActionUpdate_, false);
    SendCallbackMsg(onAction_, false, true);
    if (repeat_) {
        StartRepeatTimer();
    }
}

void LongPressRecognizer::OnRejected()
{
    TAG_LOGI(AceLogTag::ACE_GESTURE, "Long press gesture has been rejected");
    refereeState_ = RefereeState::FAIL;
}

void LongPressRecognizer::ThumbnailTimer(int32_t time)
{
    auto context = PipelineContext::GetCurrentContext();
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
    taskExecutor.PostDelayedTask(thumbnailTimer_, time);
}

void LongPressRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    if (isDisableMouseLeft_ && event.sourceType == SourceType::MOUSE) {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Mouse left button is disabled for long press recognizer");
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    TAG_LOGI(AceLogTag::ACE_GESTURE,
        "Long press recognizer receives %{public}d touch down event, begin to detect long press event", event.id);
    int32_t curDuration = duration_;
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    int64_t currentTimeStamp = GetSysTimestamp();
    int64_t eventTimeStamp = static_cast<int64_t>(event.time.time_since_epoch().count());
    if (currentTimeStamp > eventTimeStamp) {
        TAG_LOGI(
            AceLogTag::ACE_GESTURE, "CurrentTimeStamp is larger than eventTimeStamp, need to minus time spent waiting");
        // nanoseconds to millisceond.
        curDuration = curDuration - static_cast<int32_t>((currentTimeStamp - eventTimeStamp) / (1000 * 1000));
        if (curDuration < 0) {
            curDuration = 0;
        }
    }
#endif

    if (isForDrag_ && event.sourceType == SourceType::MOUSE) {
        curDuration = 0;
    }
    if ((touchRestrict_.forbiddenType & TouchRestrict::LONG_PRESS) == TouchRestrict::LONG_PRESS) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
    globalPoint_ = Point(event.x, event.y);
    touchPoints_[event.id] = event;
    UpdateFingerListInfo();
    auto pointsCount = static_cast<int32_t>(touchPoints_.size());

    if (pointsCount == fingers_) {
        refereeState_ = RefereeState::DETECTING;
        if (useCatchMode_) {
            DeadlineTimer(curDuration, true);
        } else {
            DeadlineTimer(curDuration, false);
        }
    }

    ThumbnailTimer(thumbnailDeadline);
}

void LongPressRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    TAG_LOGI(AceLogTag::ACE_GESTURE, "Long press recognizer receives touch up event");
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->RemoveGestureTask(task_);
    if (touchPoints_.find(event.id) != touchPoints_.end()) {
        touchPoints_.erase(event.id);
    }
    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onActionUpdate_, false);
        if (static_cast<int32_t>(touchPoints_.size()) == 0) {
            SendCallbackMsg(onActionEnd_, false);
        }
    } else {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    }
}

void LongPressRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        return;
    }
    if (IsRefereeFinished()) {
        return;
    }
    Offset offset = event.GetOffset() - touchPoints_[event.id].GetOffset();
    if (offset.GetDistance() > MAX_THRESHOLD) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
    UpdateFingerListInfo();
    time_ = event.time;
}

void LongPressRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    TAG_LOGI(AceLogTag::ACE_GESTURE, "long press recognizer receives touch cancel event");
    if (IsRefereeFinished()) {
        return;
    }
    if (refereeState_ == RefereeState::SUCCEED) {
        SendCancelMsg();
    } else {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    }
}

void LongPressRecognizer::HandleOverdueDeadline(bool isCatchMode)
{
    auto attachedNode = GetAttachedNode();
    if (attachedNode.Invalid()) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
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
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return;
        }
    }
    auto onGestureJudgeBeginResult = TriggerGestureJudgeCallback();
    if (onGestureJudgeBeginResult == GestureJudgeResult::REJECT) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        if (gestureInfo_ && gestureInfo_->GetType() == GestureTypeName::DRAG) {
            auto dragEventActuator = GetDragEventActuator();
            CHECK_NULL_VOID(dragEventActuator);
            dragEventActuator->SetIsDragUserReject(true);
        }
        return;
    }
    Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
}

void LongPressRecognizer::DeadlineTimer(int32_t time, bool isCatchMode)
{
    auto context = PipelineContext::GetCurrentContext();
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
    taskExecutor.PostDelayedTask(deadlineTimer_, time);
}

void LongPressRecognizer::DoRepeat()
{
    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        return;
    }
    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onAction_, true, true);
        StartRepeatTimer();
    }
}

void LongPressRecognizer::StartRepeatTimer()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    auto&& callback = [weakPtr = AceType::WeakClaim(this)]() {
        auto refPtr = weakPtr.Upgrade();
        if (refPtr) {
            refPtr->DoRepeat();
        }
    };
    timer_.Reset(callback);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(timer_, duration_);
}

double LongPressRecognizer::ConvertPxToVp(double offset) const
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, offset);

    double vpOffset = context->ConvertPxToVp(Dimension(offset, DimensionUnit::PX));
    return vpOffset;
}

void LongPressRecognizer::SendCallbackMsg(
    const std::unique_ptr<GestureEventFunc>& callback, bool isRepeat, bool isOnAction)
{
    if (callback && *callback) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        info.SetRepeat(isRepeat);
        info.SetFingerList(fingerList_);
        TouchEvent trackPoint = {};
        if (!touchPoints_.empty()) {
            trackPoint = touchPoints_.begin()->second;
        }
        info.SetSourceDevice(deviceType_);
        info.SetDeviceId(deviceId_);
        info.SetTargetDisplayId(trackPoint.targetDisplayId);
        info.SetGlobalPoint(globalPoint_);
        info.SetScreenLocation(trackPoint.GetScreenOffset());
        info.SetGlobalLocation(trackPoint.GetOffset()).SetLocalLocation(trackPoint.GetOffset() - coordinateOffset_);
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
        if (recognizerTarget_.has_value()) {
            info.SetTarget(recognizerTarget_.value());
        }
        info.SetForce(trackPoint.force);
        if (trackPoint.tiltX.has_value()) {
            info.SetTiltX(trackPoint.tiltX.value());
        }
        if (trackPoint.tiltY.has_value()) {
            info.SetTiltY(trackPoint.tiltY.value());
        }
        info.SetSourceTool(trackPoint.sourceTool);
        // callback may be overwritten in its invoke so we copy it first
        auto callbackFunction = *callback;
        callbackFunction(info);
        if (isOnAction && longPressRecorder_ && *longPressRecorder_) {
            (*longPressRecorder_)(info);
        }
    }
}

void LongPressRecognizer::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    timer_.Cancel();
    deadlineTimer_.Cancel();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->RemoveGestureTask(task_);
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
        ResetStatus();
        return false;
    }

    onAction_ = std::move(curr->onAction_);
    onActionEnd_ = std::move(curr->onActionEnd_);
    onActionCancel_ = std::move(curr->onActionCancel_);

    return true;
}

GestureEventFunc LongPressRecognizer::GetLongPressActionFunc()
{
    auto callback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto longPressRecognizer = weak.Upgrade();
        CHECK_NULL_VOID(longPressRecognizer);
        if (longPressRecognizer->onActionUpdate_) {
            (*(longPressRecognizer->onActionUpdate_))(info);
        }
        if (longPressRecognizer->onAction_) {
            (*(longPressRecognizer->onAction_))(info);
        }
        if (longPressRecognizer->onActionUpdate_) {
            (*(longPressRecognizer->onActionUpdate_))(info);
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
        << "fingers: " << fingers_;
    info->customInfo = oss.str();
    return info;
}

GestureJudgeResult LongPressRecognizer::TriggerGestureJudgeCallback()
{
    auto targetComponent = GetTargetComponent();
    CHECK_NULL_RETURN(targetComponent, GestureJudgeResult::CONTINUE);
    auto callback = targetComponent->GetOnGestureJudgeBeginCallback();
    CHECK_NULL_RETURN(callback, GestureJudgeResult::CONTINUE);
    auto info = std::make_shared<LongPressGestureEvent>();
    info->SetTimeStamp(time_);
    info->SetRepeat(repeat_);
    info->SetFingerList(fingerList_);
    TouchEvent trackPoint = {};
    if (!touchPoints_.empty()) {
        trackPoint = touchPoints_.begin()->second;
    }
    info->SetSourceDevice(deviceType_);
    info->SetTarget(GetEventTarget().value_or(EventTarget()));
    if (recognizerTarget_.has_value()) {
        info->SetTarget(recognizerTarget_.value());
    }
    info->SetForce(trackPoint.force);
    if (trackPoint.tiltX.has_value()) {
        info->SetTiltX(trackPoint.tiltX.value());
    }
    if (trackPoint.tiltY.has_value()) {
        info->SetTiltY(trackPoint.tiltY.value());
    }
    info->SetSourceTool(trackPoint.sourceTool);
    return callback(gestureInfo_, info);
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

} // namespace OHOS::Ace::NG
