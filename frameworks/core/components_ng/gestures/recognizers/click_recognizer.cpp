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

#include "core/components_ng/gestures/recognizers/click_recognizer.h"

#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

int32_t MULTI_FINGER_TIMEOUT = 300;
constexpr int32_t MULTI_FINGER_TIMEOUT_TOUCH = 300;
constexpr int32_t MULTI_FINGER_TIMEOUT_MOUSE = 300;
int32_t MULTI_TAP_TIMEOUT = 300;
constexpr int32_t MULTI_TAP_TIMEOUT_TOUCH = 350;
constexpr int32_t MULTI_TAP_TIMEOUT_MOUSE = 300;
int32_t MULTI_TAP_SLOP = 100;
constexpr int32_t MULTI_TAP_SLOP_TOUCH = 30;
constexpr int32_t MULTI_TAP_SLOP_MOUSE = 15;
#ifndef WEARABLE_PRODUCT
double MAX_THRESHOLD = 20.0;
constexpr double MAX_THRESHOLD_TOUCH = 20.0;
#else
constexpr double MAX_THRESHOLD = 12.0;
constexpr double MAX_THRESHOLD_TOUCH = 12.0;
#endif
constexpr int32_t MAX_THRESHOLD_MOUSE = 15;
constexpr int32_t MAX_TAP_FINGERS = 10;

} // namespace

void ClickRecognizer::InitGlobalValue(SourceType sourceType)
{
    switch (sourceType) {
        case SourceType::TOUCH:
            MULTI_FINGER_TIMEOUT = MULTI_FINGER_TIMEOUT_TOUCH;
            MULTI_TAP_TIMEOUT = MULTI_TAP_TIMEOUT_TOUCH;
            MULTI_TAP_SLOP = MULTI_TAP_SLOP_TOUCH;
            MAX_THRESHOLD = MAX_THRESHOLD_TOUCH;
            break;
        case SourceType::MOUSE:
        case SourceType::TOUCH_PAD:
            MULTI_FINGER_TIMEOUT = MULTI_FINGER_TIMEOUT_MOUSE;
            MULTI_TAP_TIMEOUT = MULTI_TAP_TIMEOUT_MOUSE;
            MULTI_TAP_SLOP = MULTI_TAP_SLOP_MOUSE;
            MAX_THRESHOLD = MAX_THRESHOLD_MOUSE;
            break;
        default:
            LOGI("Unrecognized input source type: %{public}d", sourceType);
    }
}

void ClickRecognizer::OnAccepted()
{
    LOGI("Click gesture has been accepted!");
    if (onAccessibilityEventFunc_) {
        onAccessibilityEventFunc_(AccessibilityEventType::CLICK);
    }
    refereeState_ = RefereeState::SUCCEED;
    ResSchedReport::GetInstance().ResSchedDataReport("click");
    if (onClick_) {
        TouchEvent touchPoint = {};
        if (!touchPoints_.empty()) {
            touchPoint = touchPoints_.begin()->second;
        }

        ClickInfo info(touchPoint.id);
        info.SetTimeStamp(touchPoint.time);
        info.SetGlobalLocation(touchPoint.GetOffset()).SetLocalLocation(touchPoint.GetOffset() - coordinateOffset_);
        info.SetSourceDevice(deviceType_);
        info.SetDeviceId(deviceId_);
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
        info.SetForce(touchPoint.force);
        if (touchPoint.tiltX.has_value()) {
            info.SetTiltX(touchPoint.tiltX.value());
        }
        if (touchPoint.tiltY.has_value()) {
            info.SetTiltY(touchPoint.tiltY.value());
        }
        info.SetSourceTool(touchPoint.sourceTool);
        onClick_(info);
    }

    if (remoteMessage_) {
        TouchEvent touchPoint = {};
        if (!touchPoints_.empty()) {
            touchPoint = touchPoints_.begin()->second;
        }

        ClickInfo info(touchPoint.id);
        info.SetTimeStamp(touchPoint.time);
        info.SetGlobalLocation(touchPoint.GetOffset()).SetLocalLocation(touchPoint.GetOffset() - coordinateOffset_);
        remoteMessage_(info);
    }
    UpdateFingerListInfo(coordinateOffset_);
    SendCallbackMsg(onAction_);
}

void ClickRecognizer::OnRejected()
{
    LOGD("click gesture has been rejected!");
    refereeState_ = RefereeState::FAIL;
}

void ClickRecognizer::HandleTouchDownEvent(const TouchEvent& event)
{
    if (IsRefereeFinished()) {
        LOGD("referee has already receives the result");
        return;
    }
    InitGlobalValue(event.sourceType);
    LOGI("click recognizer receives %{public}d touch down event, begin to detect click event, current finger info: "
         "%{public}d, %{public}d",
        event.id, equalsToFingers_, currentTouchPointsNum_);
    if (fingers_ > MAX_TAP_FINGERS) {
        LOGE("finger is lager than max fingers");
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (currentTouchPointsNum_ >= fingers_) {
        LOGI("current down finger is larger than defined, %{public}d, %{public}d", currentTouchPointsNum_, fingers_);
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    }

    // The last recognition sequence has been completed, reset the timer.
    if (tappedCount_ > 0 && currentTouchPointsNum_ == 0) {
        tapDeadlineTimer_.Cancel();
    }
    ++currentTouchPointsNum_;
    touchPoints_[event.id] = event;
    if (fingers_ > currentTouchPointsNum_) {
        // waiting for multi-finger press
        DeadlineTimer(fingerDeadlineTimer_, MULTI_FINGER_TIMEOUT);
    } else {
        // Turn off the multi-finger press deadline timer
        fingerDeadlineTimer_.Cancel();
        equalsToFingers_ = true;
        if (ExceedSlop()) {
            LOGE("fail to detect multi finger tap due to offset is out of slop");
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
    }
}

void ClickRecognizer::HandleTouchUpEvent(const TouchEvent& event)
{
    if (IsRefereeFinished()) {
        LOGD("referee has already receives the result");
        return;
    }
    InitGlobalValue(event.sourceType);
    LOGI("click recognizer receives %{public}d touch up event, current finger info: %{public}d, %{public}d", event.id,
        equalsToFingers_, currentTouchPointsNum_);
    touchPoints_[event.id] = event;
    --currentTouchPointsNum_;
    // Check whether multi-finger taps are completed in count_ times
    if (equalsToFingers_ && (currentTouchPointsNum_ == 0)) {
        // Turn off the multi-finger lift deadline timer
        fingerDeadlineTimer_.Cancel();
        focusPoint_ = ComputeFocusPoint();
        tappedCount_++;

        if (tappedCount_ == count_) {
            LOGI("this gesture is click, try to accept it");
            time_ = event.time;
            if (useCatchMode_) {
                Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
            } else {
                OnAccepted();
            }
            return;
        }
        equalsToFingers_ = false;
        // waiting for multi-finger lift
        DeadlineTimer(tapDeadlineTimer_, MULTI_TAP_TIMEOUT);
    }

    if (refereeState_ != RefereeState::PENDING) {
        Adjudicate(AceType::Claim(this), GestureDisposal::PENDING);
    }

    if (currentTouchPointsNum_ < fingers_ && equalsToFingers_) {
        DeadlineTimer(fingerDeadlineTimer_, MULTI_FINGER_TIMEOUT);
    }
}

void ClickRecognizer::HandleTouchMoveEvent(const TouchEvent& event)
{
    if (IsRefereeFinished()) {
        LOGD("referee has already receives the result");
        return;
    }
    InitGlobalValue(event.sourceType);
    LOGD("click recognizer receives touch move event");
    Offset offset = event.GetOffset() - touchPoints_[event.id].GetOffset();
    if (offset.GetDistance() > MAX_THRESHOLD) {
        LOGI("this gesture is out of offset, try to reject it");
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    }
}

void ClickRecognizer::HandleTouchCancelEvent(const TouchEvent& event)
{
    if (IsRefereeFinished()) {
        LOGD("referee has already receives the result");
        return;
    }
    InitGlobalValue(event.sourceType);
    LOGI("click recognizer receives touch cancel event");
    Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
}

void ClickRecognizer::HandleOverdueDeadline()
{
    if (currentTouchPointsNum_ < fingers_ || tappedCount_ < count_) {
        LOGI("the state is not detecting for accept multi-finger tap gesture, finger number is %{public}d, tappedCount "
             "is %{public}d",
            currentTouchPointsNum_, tappedCount_);
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
    }
}

void ClickRecognizer::DeadlineTimer(CancelableCallback<void()>& deadlineTimer, int32_t time)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    auto&& callback = [weakPtr = AceType::WeakClaim(this)]() {
        auto refPtr = weakPtr.Upgrade();
        if (refPtr) {
            refPtr->HandleOverdueDeadline();
        } else {
            LOGE("fail to handle overdue deadline due to context is nullptr");
        }
    };

    deadlineTimer.Reset(callback);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    taskExecutor.PostDelayedTask(deadlineTimer, time);
}

Offset ClickRecognizer::ComputeFocusPoint()
{
    Offset sumOfPoints;
    for (auto& element : touchPoints_) {
        sumOfPoints = sumOfPoints + element.second.GetOffset();
    }
    Offset focusPoint = sumOfPoints / touchPoints_.size();
    return focusPoint;
}

bool ClickRecognizer::ExceedSlop()
{
    if (tappedCount_ > 0 && tappedCount_ < count_) {
        Offset currentFocusPoint = ComputeFocusPoint();
        Offset slop = currentFocusPoint - focusPoint_;
        if (GreatOrEqual(slop.GetDistance(), MULTI_TAP_SLOP)) {
            return true;
        }
    }
    return false;
}

void ClickRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& onAction)
{
    if (onAction && *onAction) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        info.SetFingerList(fingerList_);
        TouchEvent touchPoint = {};
        if (!touchPoints_.empty()) {
            touchPoint = touchPoints_.begin()->second;
        }
        info.SetGlobalLocation(touchPoint.GetOffset()).SetLocalLocation(touchPoint.GetOffset() - coordinateOffset_);
        info.SetSourceDevice(deviceType_);
        info.SetDeviceId(deviceId_);
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
        if (recognizerTarget_.has_value()) {
            info.SetTarget(recognizerTarget_.value());
        }
        info.SetForce(touchPoint.force);
        if (touchPoint.tiltX.has_value()) {
            info.SetTiltX(touchPoint.tiltX.value());
        }
        if (touchPoint.tiltY.has_value()) {
            info.SetTiltY(touchPoint.tiltY.value());
        }
        info.SetSourceTool(touchPoint.sourceTool);
#ifdef SECURITY_COMPONENT_ENABLE
        info.SetDisplayX(touchPoint.screenX);
        info.SetDisplayY(touchPoint.screenY);
        info.SetEnhanceData(touchPoint.enhanceData_);
#endif
        (*onAction)(info);
    }
}

bool ClickRecognizer::ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    RefPtr<ClickRecognizer> curr = AceType::DynamicCast<ClickRecognizer>(recognizer);
    if (!curr) {
        ResetStatus();
        return false;
    }

    if (curr->count_ != count_ || curr->fingers_ != fingers_ || curr->priorityMask_ != priorityMask_) {
        ResetStatus();
        return false;
    }

    onAction_ = std::move(curr->onAction_);
    return true;
}

} // namespace OHOS::Ace::NG
