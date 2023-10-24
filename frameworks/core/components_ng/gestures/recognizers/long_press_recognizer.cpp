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
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/event/ace_events.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/render/render_context.h"

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
        LOGW("longPressRecognizer fingers_ is illegal, change to DEFAULT_LONGPRESS_FINGERS.");
        fingers_ = DEFAULT_LONGPRESS_FINGERS;
    }
    if (duration_ <= 0) {
        LOGW("longPressRecognizer duration_ is illegal, change to DEAULT_LONGPRESS_DURATION.");
        duration_ = DEFAULT_LONGPRESS_DURATION;
    }
}

void LongPressRecognizer::OnAccepted()
{
    if (onAccessibilityEventFunc_) {
        onAccessibilityEventFunc_(AccessibilityEventType::LONG_PRESS);
    }
    refereeState_ = RefereeState::SUCCEED;
    if (onLongPress_ && !touchPoints_.empty()) {
        TouchEvent trackPoint = touchPoints_.begin()->second;
        LongPressInfo info(trackPoint.id);
        info.SetTimeStamp(time_);
        info.SetScreenLocation(trackPoint.GetScreenOffset());
        info.SetGlobalLocation(trackPoint.GetOffset()).SetLocalLocation(trackPoint.GetOffset() - coordinateOffset_);
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
        onLongPress_(info);
    }

    UpdateFingerListInfo(coordinateOffset_);
    SendCallbackMsg(onActionUpdate_, false);
    SendCallbackMsg(onAction_, false);
    if (repeat_) {
        StartRepeatTimer();
    }
}

void LongPressRecognizer::OnRejected()
{
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
            LOGI("fail to get thumbnail pixelMap due to context is nullptr");
            return;
        }
        if (refPtr->refereeState_ == RefereeState::DETECTING) {
            customCallback(Offset(refPtr->globalPoint_.GetX(), refPtr->globalPoint_.GetY()));
        } else {
            LOGW("the state is not detecting for accept long press gesture");
        }
    };
    thumbnailTimer_.Reset(callback);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(thumbnailTimer_, time);
}

void LongPressRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    if (isDisableMouseLeft_ && event.sourceType == SourceType::MOUSE) {
        LOGI("mouse left button is disabled for long press recognizer.");
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    LOGI("long press recognizer receives %{public}d touch down event, begin to detect long press event", event.id);
    int32_t curDuration = duration_;
#ifndef PREVIEW
    int64_t currentTimeStamp = GetSysTimestamp();
    int64_t eventTimeStamp = static_cast<int64_t>(event.time.time_since_epoch().count());
    if (currentTimeStamp > eventTimeStamp) {
        LOGI("currentTimeStamp is larger than eventTimeStamp, need to minus time spent waiting");
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
        LOGI("the long press is forbidden");
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }
    globalPoint_ = Point(event.x, event.y);
    touchPoints_[event.id] = event;
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

void LongPressRecognizer::HandleTouchUpEvent(const TouchEvent& /*event*/)
{
    LOGD("long press recognizer receives touch up event");
    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        LOGW("LongPressGesture current finger number is less than requiried finger number.");
        return;
    }
    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onActionUpdate_, false);
        if (static_cast<int32_t>(touchPoints_.size()) == fingers_) {
            SendCallbackMsg(onActionEnd_, false);
        }
    } else {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    }
}

void LongPressRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    LOGD("long press recognizer receives touch move event");
    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        LOGW("LongPressGesture current finger number is less than requiried finger number.");
        return;
    }
    if (IsRefereeFinished()) {
        LOGD("referee has already receives the result");
        return;
    }
    Offset offset = event.GetOffset() - touchPoints_[event.id].GetOffset();
    if (offset.GetDistance() > MAX_THRESHOLD) {
        LOGD("this gesture is not long press, try to reject it");
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    time_ = event.time;
}

void LongPressRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    LOGD("long press recognizer receives touch cancel event");
    if (IsRefereeFinished()) {
        LOGD("referee has already receives the result");
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
    if (refereeState_ == RefereeState::DETECTING) {
        LOGI("this gesture is long press, try to accept it");
        if (isCatchMode) {
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        } else {
            OnAccepted();
        }
    } else {
        LOGW("the state is not detecting for accept long press gesture");
    }
}

void LongPressRecognizer::DeadlineTimer(int32_t time, bool isCatchMode)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    auto&& callback = [weakPtr = AceType::WeakClaim(this), isCatchMode]() {
        auto refPtr = weakPtr.Upgrade();
        if (refPtr) {
            refPtr->HandleOverdueDeadline(isCatchMode);
        } else {
            LOGI("fail to handle overdue deadline due to context is nullptr");
        }
    };
    deadlineTimer_.Reset(callback);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(deadlineTimer_, time);
}

void LongPressRecognizer::DoRepeat()
{
    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        return;
    }
    if (refereeState_ == RefereeState::SUCCEED) {
        SendCallbackMsg(onAction_, true);
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
        } else {
            LOGW("fail to handle overdue deadline due to context is nullptr");
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

void LongPressRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback, bool isRepeat)
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
    }
}

void LongPressRecognizer::OnResetStatus()
{
    MultiFingersRecognizer::OnResetStatus();
    timer_.Cancel();
    deadlineTimer_.Cancel();
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

} // namespace OHOS::Ace::NG
