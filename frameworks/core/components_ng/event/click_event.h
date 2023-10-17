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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CLICK_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CLICK_EVENT_H

#include <list>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/gesture_event_actuator.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {

class GestureEventHub;

class ClickEvent : public AceType {
    DECLARE_ACE_TYPE(ClickEvent, AceType)
public:
    explicit ClickEvent(GestureEventFunc&& callback) : callback_(std::move(callback)) {}
    ~ClickEvent() override = default;

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

    ACE_DISALLOW_COPY_AND_MOVE(ClickEvent);
};

class ACE_EXPORT ClickEventActuator : public GestureEventActuator {
    DECLARE_ACE_TYPE(ClickEventActuator, GestureEventActuator)
public:
    explicit ClickEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub);
    ~ClickEventActuator() override = default;

    void SetUserCallback(GestureEventFunc&& callback)
    {
        TAG_LOGD(AceLogTag::ACE_GESTURE_TAP, "Set usercallback");
        if (userCallback_) {
            userCallback_.Reset();
        }
        userCallback_ = MakeRefPtr<ClickEvent>(std::move(callback));
    }

    void ClearUserCallback()
    {
        // When the event param is undefined, it will clear the callback.
        TAG_LOGD(AceLogTag::ACE_GESTURE_TAP, "Clear user callback");
        if (userCallback_) {
            userCallback_.Reset();
        }
    }

    void AddClickEvent(const RefPtr<ClickEvent>& clickEvent)
    {
        if (clickEvents_.empty()) {
            clickEvents_.emplace_back(clickEvent);
            return;
        }
        if (std::find(clickEvents_.begin(), clickEvents_.end(), clickEvent) == clickEvents_.end()) {
            clickEvents_.emplace_back(clickEvent);
        }
    }

    void RemoveClickEvent(const RefPtr<ClickEvent>& clickEvent)
    {
        clickEvents_.remove(clickEvent);
    }

    bool IsClickEventsEmpty() const
    {
        return clickEvents_.empty();
    }

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result) override;

    GestureEventFunc GetClickEvent();

private:
    WeakPtr<GestureEventHub> gestureEventHub_;
    std::list<RefPtr<ClickEvent>> clickEvents_;
    RefPtr<ClickEvent> userCallback_;
    RefPtr<ClickRecognizer> clickRecognizer_;

    ACE_DISALLOW_COPY_AND_MOVE(ClickEventActuator);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CLICK_EVENT_H
