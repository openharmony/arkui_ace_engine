/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_DRAG_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_DRAG_EVENT_H

#include <list>

#include "base/memory/referenced.h"
#include "core/components_ng/event/gesture_event_actuator.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/gestures/recognizers/sequenced_recognizer.h"

namespace OHOS::Ace::NG {

class GestureEventHub;
class PanRecognizer;
class LongPressRecognizer;

class DragEvent : public Referenced {
public:
    DragEvent(GestureEventFunc&& actionStart, GestureEventFunc&& actionUpdate, GestureEventFunc&& actionEnd,
        GestureEventNoParameter&& actionCancel)
        : actionStart_(std::move(actionStart)), actionUpdate_(std::move(actionUpdate)),
          actionEnd_(std::move(actionEnd)), actionCancel_(std::move(actionCancel))
    {}
    ~DragEvent() override = default;

    const GestureEventFunc& GetActionStartEventFunc() const
    {
        return actionStart_;
    }

    const GestureEventFunc& GetActionUpdateEventFunc() const
    {
        return actionUpdate_;
    }

    const GestureEventFunc& GetActionEndEventFunc() const
    {
        return actionEnd_;
    }

    const GestureEventNoParameter& GetActionCancelEventFunc() const
    {
        return actionCancel_;
    }

private:
    GestureEventFunc actionStart_;
    GestureEventFunc actionUpdate_;
    GestureEventFunc actionEnd_;
    GestureEventNoParameter actionCancel_;
};

class ACE_EXPORT DragEventActuator : public GestureEventActuator {
    DECLARE_ACE_TYPE(DragEventActuator, GestureEventActuator)
public:
    DragEventActuator(
        const WeakPtr<GestureEventHub>& gestureEventHub, PanDirection direction, int32_t fingers, float distance);
    ~DragEventActuator() override = default;

    void ReplaceDragEvent(const RefPtr<DragEvent>& dragEvent)
    {
        if (userCallback_) {
            userCallback_.Reset();
        }
        userCallback_ = dragEvent;
    }

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result) override;

    PanDirection GetDirection() const
    {
        return direction_;
    }

private:
    WeakPtr<GestureEventHub> gestureEventHub_;
    RefPtr<DragEvent> userCallback_;
    RefPtr<PanRecognizer> panRecognizer_;
    RefPtr<LongPressRecognizer> longPressRecognizer_;
    RefPtr<SequencedRecognizer> SequencedRecognizer_;

    PanDirection direction_;
    int32_t fingers_ = 1;
    float distance_ = 0.0f;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_DRAG_EVENT_H
