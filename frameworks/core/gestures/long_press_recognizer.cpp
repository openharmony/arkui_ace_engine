/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/gestures/long_press_recognizer.h"

#include "core/gestures/gesture_referee.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t LONG_PRESS_TIMEOUT = 500;
constexpr double MAX_THRESHOLD = 5.0;

} // namespace

void LongPressRecognizer::OnAccepted(size_t touchId)
{
    LOGD("long press gesture has been accepted! the touch id is %{public}zu", touchId);
    state_ = DetectState::DETECTED;
    if (onLongPress_) {
        LongPressInfo info(touchId);
        info.SetTimeStamp(trackPoint_.time);
        info.SetGlobalLocation(trackPoint_.GetOffset()).SetLocalLocation(trackPoint_.GetOffset() - coordinateOffset_);
        onLongPress_(info);
    }
}

void LongPressRecognizer::OnRejected(size_t touchId)
{
    LOGD("long press gesture has been rejected! the touch id is %{public}zu", touchId);
    deadlineTimer_.Cancel();
    state_ = DetectState::READY;
}

void LongPressRecognizer::HandleTouchDownEvent(const TouchPoint& event)
{
    LOGD("long press recognizer receives touch down event, begin to detect long press event");
    if ((touchRestrict_.forbiddenType & TouchRestrict::LONG_PRESS) == TouchRestrict::LONG_PRESS) {
        LOGI("the long press is forbidden");
        return;
    }
    if (state_ == DetectState::READY) {
        auto context = context_.Upgrade();
        if (!context) {
            LOGE("fail to detect long press gesture due to context is nullptr");
            return;
        }
        GestureReferee::GetInstance().AddGestureRecognizer(event.id, AceType::Claim(this));
        trackPoint_ = event;
        state_ = DetectState::DETECTING;
        auto&& callback = [weakPtr = AceType::WeakClaim(this)]() {
            auto refPtr = weakPtr.Upgrade();
            if (refPtr) {
                refPtr->HandleOverdueDeadline();
            } else {
                LOGE("fail to handle overdue deadline due to context is nullptr");
            }
        };
        deadlineTimer_.Reset(callback);
        auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        taskExecutor.PostDelayedTask(deadlineTimer_, LONG_PRESS_TIMEOUT);
    } else {
        LOGW("the state is not ready for detecting long press gesture");
    }
}

void LongPressRecognizer::HandleTouchUpEvent(const TouchPoint& event)
{
    LOGD("long press recognizer receives touch up event");
    if (state_ == DetectState::DETECTING) {
        LOGD("this gesture is not long press, try to reject it");
        GestureReferee::GetInstance().Adjudicate(trackPoint_.id, AceType::Claim(this), GestureDisposal::REJECT);
    }
    state_ = DetectState::READY;
}

void LongPressRecognizer::HandleTouchMoveEvent(const TouchPoint& event)
{
    LOGD("long press recognizer receives touch move event");
    if (state_ == DetectState::DETECTING) {
        Offset offset = event.GetOffset() - trackPoint_.GetOffset();
        if (offset.GetDistance() > MAX_THRESHOLD) {
            LOGD("this gesture is not long press, try to reject it");
            GestureReferee::GetInstance().Adjudicate(event.id, AceType::Claim(this), GestureDisposal::REJECT);
        }
    }
}

void LongPressRecognizer::HandleTouchCancelEvent(const TouchPoint& event)
{
    LOGD("long press recognizer receives touch cancel event");
    if (state_ == DetectState::DETECTING) {
        LOGD("cancel long press gesture detect, try to reject it");
        GestureReferee::GetInstance().Adjudicate(event.id, AceType::Claim(this), GestureDisposal::REJECT);
    }
    state_ = DetectState::READY;
}

void LongPressRecognizer::HandleOverdueDeadline()
{
    if (state_ == DetectState::DETECTING) {
        LOGD("this gesture is long press, try to accept it");
        GestureReferee::GetInstance().Adjudicate(trackPoint_.id, AceType::Claim(this), GestureDisposal::ACCEPT);
    } else {
        LOGW("the state is not detecting for accept long press gesture");
    }
}

} // namespace OHOS::Ace