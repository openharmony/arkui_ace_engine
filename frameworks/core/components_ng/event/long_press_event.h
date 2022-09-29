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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_LONG_PRESS_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_LONG_PRESS_EVENT_H

#include <list>

#include "base/memory/referenced.h"
#include "core/components_ng/event/gesture_event_actuator.h"
#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {

class GestureEventHub;

class LongPressEvent : public Referenced {
public:
    explicit LongPressEvent(GestureEventFunc&& callback) : callback_(std::move(callback)) {}
    ~LongPressEvent() override = default;

    const GestureEventFunc& GetGestureEventFunc() const
    {
        return callback_;
    }

    void operator()(GestureEvent& info) const
    {
        if (callback_) {
            callback_(info);
        }
    }

private:
    GestureEventFunc callback_;
};

class ACE_EXPORT LongPressEventActuator : public GestureEventActuator {
    DECLARE_ACE_TYPE(LongPressEventActuator, GestureEventActuator)
public:
    explicit LongPressEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub);
    ~LongPressEventActuator() override = default;

    void AddLongPressEvent(const RefPtr<LongPressEvent>& event)
    {
        if (longPressEvents_.empty()) {
            longPressEvents_.emplace_back(event);
            return;
        }
        if (std::find(longPressEvents_.begin(), longPressEvents_.end(), event) == longPressEvents_.end()) {
            longPressEvents_.emplace_back(event);
        }
    }

    void RemoveLongPressEvent(const RefPtr<LongPressEvent>& event)
    {
        longPressEvents_.remove(event);
    }

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result) override;

private:
    WeakPtr<GestureEventHub> gestureEventHub_;
    RefPtr<LongPressRecognizer> longPressRecognizer_;
    std::list<RefPtr<LongPressEvent>> longPressEvents_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_LONG_PRESS_EVENT_H
