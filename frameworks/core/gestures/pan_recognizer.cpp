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

#include "core/gestures/pan_recognizer.h"

#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "core/gestures/gesture_referee.h"

namespace OHOS::Ace {

namespace {

constexpr int32_t MAX_PAN_FINGERS = 10;

} // namespace

void PanRecognizer::OnAccepted()
{
    SendCallbackMsg(onActionStart_);

    if (pendingEnd_) {
        LOGD("pan gesture recognizer has pending end event when waiting to be accepted");
        SendCallbackMsg(onActionEnd_);
        Reset();
    } else if (pendingCancel_) {
        SendCancelMsg();
        Reset();
    }
}

void PanRecognizer::OnRejected()
{
    LOGD("pan gesture has been rejected!");
    Reset();
}

void PanRecognizer::HandleTouchDownEvent(const TouchPoint& event)
{
    LOGD("pan recognizer receives touch down event, begin to detect pan event");
    if (fingers_ > MAX_PAN_FINGERS) {
        return;
    }

    touchPoints_[event.id] = event;

    if (state_ == DetectState::READY) {
        AddToReferee(event.id, AceType::Claim(this));
        if (static_cast<int32_t>(refereePointers_.size()) == fingers_) {
            state_ = DetectState::DETECTING;
        }
    }
}

void PanRecognizer::HandleTouchUpEvent(const TouchPoint& event)
{
    LOGD("pan recognizer receives touch up event");
    auto itr = touchPoints_.find(event.id);
    if (itr == touchPoints_.end()) {
        return;
    }

    globalPoint_ = Point(event.x, event.y);
    touchPoints_.erase(itr);

    if (state_ == DetectState::READY) {
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (state_ == DetectState::DETECTING) {
        size_t inRefereeNum = refereePointers_.size();
        bool inReferee = IsInReferee(static_cast<size_t>(event.id));
        if (inReferee) {
            inRefereeNum--;
        }

        if (static_cast<int32_t>(touchPoints_.size()) < fingers_ || inRefereeNum < 1) {
            LOGD("this gesture is not pan, try to reject it");
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
            return;
        }

        if (inReferee) {
            DelFromReferee(event.id, AceType::Claim(this));
        }
        return;
    }

    if (static_cast<int32_t>(touchPoints_.size()) < fingers_) {
        if (refereeState_ == RefereeState::SUCCEED) {
            SendCallbackMsg(onActionEnd_);
            Reset();
        } else {
            pendingEnd_ = true;
        }
    }
}

void PanRecognizer::HandleTouchMoveEvent(const TouchPoint& event)
{
    LOGD("pan recognizer receives touch move event");
    auto itr = touchPoints_.find(event.id);
    if (itr == touchPoints_.end()) {
        return;
    }

    globalPoint_ = Point(event.x, event.y);
    if (state_ == DetectState::READY) {
        touchPoints_[event.id] = event;
        return;
    }

    Offset moveDistance = (event.GetOffset() - touchPoints_[event.id].GetOffset()) / touchPoints_.size();
    averageDistance_ += moveDistance;
    touchPoints_[event.id] = event;
    time_ = event.time;

    if (state_ == DetectState::DETECTING) {
        double offsetInMainDirection = GetOffsetInMainDirection();

        if (IsPanGestureAccept(offsetInMainDirection)) {
            state_ = DetectState::DETECTED;
            Adjudicate(AceType::Claim(this), GestureDisposal::ACCEPT);
        }
    } else if (state_ == DetectState::DETECTED && refereeState_ == RefereeState::SUCCEED) {
        if (direction_ == Direction::HORIZONTAL) {
            averageDistance_.SetY(0.0);
        } else if (direction_ == Direction::VERTICAL) {
            averageDistance_.SetX(0.0);
        }

        SendCallbackMsg(onActionUpdate_);
    }
}

void PanRecognizer::HandleTouchCancelEvent(const TouchPoint& event)
{
    LOGD("pan recognizer receives touch cancel event");
    if (state_ == DetectState::READY || state_ == DetectState::DETECTING) {
        LOGD("cancel pan gesture detect, try to reject it");
        Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        return;
    }

    if (refereeState_ == RefereeState::SUCCEED) {
        SendCancelMsg();
        Reset();
    } else {
        pendingCancel_ = true;
    }
}

double PanRecognizer::GetOffsetInMainDirection()
{
    double offset = 0.0;
    if (direction_ == Direction::ALL) {
        offset = averageDistance_.GetDistance();
    } else if (direction_ == Direction::HORIZONTAL) {
        offset = averageDistance_.GetX();
    } else {
        offset = averageDistance_.GetY();
    }
    return offset;
}

bool PanRecognizer::IsPanGestureAccept(double offset) const
{
    if (fabs(offset) < distance_) {
        return false;
    }

    if (direction_ == Direction::HORIZONTAL) {
        uint32_t flag = offset > 0 ? TouchRestrict::SWIPE_RIGHT : TouchRestrict::SWIPE_LEFT;
        if ((touchRestrict_.forbiddenType & flag) != flag) {
            return true;
        }
    } else if (direction_ == Direction::VERTICAL) {
        uint32_t flag = offset > 0 ? TouchRestrict::SWIPE_DOWN : TouchRestrict::SWIPE_UP;
        if ((touchRestrict_.forbiddenType & flag) != flag) {
            return true;
        }
    } else {
        return true;
    }
    return false;
}

void PanRecognizer::Reset()
{
    touchPoints_.clear();
    averageDistance_.Reset();
    state_ = DetectState::READY;
    pendingEnd_ = false;
    pendingCancel_ = false;
}

void PanRecognizer::SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback)
{
    if (callback && *callback) {
        GestureEvent info;
        info.SetTimeStamp(time_);
        info.SetOffsetX(ConvertPxToVp(averageDistance_.GetX()));
        info.SetOffsetY(ConvertPxToVp(averageDistance_.GetY()));
        info.SetGlobalPoint(globalPoint_);
        (*callback)(info);
    }
}

double PanRecognizer::ConvertPxToVp(double offset) const
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to detect tap gesture due to context is nullptr");
        return offset;
    }
    double vpOffset = context->ConvertPxToVp(Dimension(offset, DimensionUnit::PX));
    return vpOffset;
}

bool PanRecognizer::ReconcileFrom(const RefPtr<GestureRecognizer>& recognizer)
{
    RefPtr<PanRecognizer> curr = AceType::DynamicCast<PanRecognizer>(recognizer);
    if (!curr) {
        Reset();
        return false;
    }

    if (curr->fingers_ != fingers_ || curr->direction_ != direction_ || curr->distance_ != distance_ ||
        curr->priorityMask_ != priorityMask_) {
        Reset();
        return false;
    }

    onActionStart_ = std::move(curr->onActionStart_);
    onActionUpdate_ = std::move(curr->onActionUpdate_);
    onActionEnd_ = std::move(curr->onActionEnd_);
    onActionCancel_ = std::move(curr->onActionCancel_);

    return true;
}

} // namespace OHOS::Ace
