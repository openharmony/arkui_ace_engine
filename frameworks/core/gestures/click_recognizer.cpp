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

#include "core/gestures/click_recognizer.h"

#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "core/gestures/gesture_referee.h"

namespace OHOS::Ace {
namespace {

constexpr double MAX_THRESHOLD = 20.0;

} // namespace

void ClickRecognizer::OnAccepted(size_t touchId)
{
    LOGD("click gesture has been accepted! the touch id is %{public}zu", touchId);
    state_ = DetectState::DETECTED;
    if (onClick_) {
        ClickInfo info(touchId);
        info.SetTimeStamp(touchPoint_.time);
        info.SetGlobalLocation(touchPoint_.GetOffset()).SetLocalLocation(touchPoint_.GetOffset() - coordinateOffset_);
        onClick_(info);
    }
}

void ClickRecognizer::OnRejected(size_t touchId)
{
    LOGD("click gesture has been rejected! the touch id is %{public}zu", touchId);
    state_ = DetectState::READY;
}

void ClickRecognizer::HandleTouchDownEvent(const TouchPoint& event)
{
    LOGD("click recognizer receives touch down event, begin to detect click event");
    if (state_ == DetectState::READY) {
        GestureReferee::GetInstance().AddGestureRecognizer(event.id, AceType::Claim(this));
        touchPoint_ = event;
        state_ = DetectState::DETECTING;
    } else {
        LOGW("the state is not ready for detecting click event");
    }
}

void ClickRecognizer::HandleTouchUpEvent(const TouchPoint& event)
{
    LOGD("click recognizer receives touch up event");
    if (state_ == DetectState::DETECTING) {
        LOGD("this gesture is click, try to accept it");
        GestureReferee::GetInstance().Adjudicate(event.id, AceType::Claim(this), GestureDisposal::ACCEPT);
    }
    state_ = DetectState::READY;
}

void ClickRecognizer::HandleTouchMoveEvent(const TouchPoint& event)
{
    LOGD("click recognizer receives touch move event");
    if (state_ == DetectState::DETECTING) {
        Offset offset = event.GetOffset() - touchPoint_.GetOffset();
        if (offset.GetDistance() > MAX_THRESHOLD) {
            LOGD("this gesture is not click, try to reject it");
            GestureReferee::GetInstance().Adjudicate(event.id, AceType::Claim(this), GestureDisposal::REJECT);
        }
    }
}

void ClickRecognizer::HandleTouchCancelEvent(const TouchPoint& event)
{
    LOGD("click recognizer receives touch cancel event");
    if (state_ == DetectState::DETECTING) {
        LOGD("cancel click gesture detect, try to reject it");
        GestureReferee::GetInstance().Adjudicate(event.id, AceType::Claim(this), GestureDisposal::REJECT);
    }
    state_ = DetectState::READY;
}

} // namespace OHOS::Ace