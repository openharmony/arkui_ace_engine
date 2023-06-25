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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_TOUCH_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_TOUCH_EVENT_H

#include <list>

#include "base/memory/referenced.h"
#include "core/components_ng/event/gesture_event_actuator.h"

namespace OHOS::Ace::NG {

class GestureEventHub;

class TouchEventImpl : public virtual AceType {
    DECLARE_ACE_TYPE(TouchEventImpl, AceType)
public:
    explicit TouchEventImpl(TouchEventFunc&& callback) : callback_(std::move(callback)) {}
    ~TouchEventImpl() override = default;

    const TouchEventFunc& GetTouchEventCallback() const
    {
        return callback_;
    }

    void operator()(TouchEventInfo& info) const
    {
        if (callback_) {
            callback_(info);
        }
    }

private:
    TouchEventFunc callback_;
};

class TouchEventActuator : public GestureEventActuator, public TouchEventTarget {
    DECLARE_ACE_TYPE(TouchEventActuator, GestureEventActuator, TouchEventTarget)
public:
    TouchEventActuator() = default;
    ~TouchEventActuator() override = default;

    void ReplaceTouchEvent(TouchEventFunc&& callback)
    {
        if (userCallback_) {
            userCallback_.Reset();
        }
        userCallback_ = MakeRefPtr<TouchEventImpl>(std::move(callback));
    }

    void ClearUserCallback()
    {
        // When the event param is undefined, it will clear the callback.
        LOGI("Clear user callback.");
        if (userCallback_) {
            userCallback_.Reset();
        }
    }

    void AddTouchEvent(const RefPtr<TouchEventImpl>& touchEvent)
    {
        if (touchEvents_.empty()) {
            touchEvents_.emplace_back(touchEvent);
            return;
        }
        if (std::find(touchEvents_.begin(), touchEvents_.end(), touchEvent) == touchEvents_.end()) {
            touchEvents_.emplace_back(touchEvent);
        }
    }

    void RemoveTouchEvent(const RefPtr<TouchEventImpl>& touchEvent)
    {
        touchEvents_.remove(touchEvent);
    }

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result) override
    {
        SetGetEventTargetImpl(getEventTargetImpl);
        SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        result.emplace_back(Claim(this));
    }

    bool DispatchEvent(const TouchEvent& point) override;
    bool HandleEvent(const TouchEvent& point) override;

private:
    bool TriggerTouchCallBack(const TouchEvent& changedPoint);

    std::list<RefPtr<TouchEventImpl>> touchEvents_;
    RefPtr<TouchEventImpl> userCallback_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_TOUCH_EVENT_H
