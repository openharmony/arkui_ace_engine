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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_RECOGNIZER_H

#include "core/gestures/touch_event.h"

namespace OHOS::Ace {

enum class DetectState { READY, DETECTING, DETECTED };

class GestureRecognizer : public TouchEventTarget {
    DECLARE_ACE_TYPE(GestureRecognizer, TouchEventTarget);

public:
    // Called when request of handling gesture sequence is accepted by gesture referee.
    virtual void OnAccepted(size_t touchId) = 0;

    // Called when request of handling gesture sequence is rejected by gesture referee.
    virtual void OnRejected(size_t touchId) = 0;

    bool DispatchEvent(const TouchPoint& point) override
    {
        return true;
    }
    bool HandleEvent(const TouchPoint& point) final;

    // Coordinate offset is used to calculate the local location of the touch point in the render node.
    void SetCoordinateOffset(const Offset& coordinateOffset)
    {
        coordinateOffset_ = coordinateOffset;
    }

    // Gets the coordinate offset to calculate the local location of the touch point by manually.
    const Offset& GetCoordinateOffset() const
    {
        return coordinateOffset_;
    }

protected:
    virtual void HandleTouchDownEvent(const TouchPoint& event) = 0;
    virtual void HandleTouchUpEvent(const TouchPoint& event) = 0;
    virtual void HandleTouchMoveEvent(const TouchPoint& event) = 0;
    virtual void HandleTouchCancelEvent(const TouchPoint& event) = 0;

    Offset coordinateOffset_;
    DetectState state_ { DetectState::READY };
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_RECOGNIZER_H
