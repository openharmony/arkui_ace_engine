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
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {

struct TouchTestResultInfo {
    int32_t nodeId = 0;
    std::string tag;
    std::string inspectorId;
    std::string frameRect;
    int32_t depth = 0;
};

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

class ACE_FORCE_EXPORT TouchEventActuator : public GestureEventActuator, public TouchEventTarget {
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

    void SetOnTouchEvent(TouchEventFunc&& callback)
    {
        if (onTouchEventCallback_) {
            onTouchEventCallback_.Reset();
        }
        onTouchEventCallback_ = MakeRefPtr<TouchEventImpl>(std::move(callback));
    }

    void ClearUserCallback()
    {
        // When the event param is undefined, it will clear the callback.
        if (userCallback_) {
            userCallback_.Reset();
        }
    }
    
    void ClearJSFrameNodeCallback()
    {
        // When the event param is undefined, it will clear the callback.
        if (commonTouchEventCallback_) {
            commonTouchEventCallback_.Reset();
        }
    }

    void OnFlushTouchEventsBegin() override;
    void OnFlushTouchEventsEnd() override;

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

    void AddTouchAfterEvent(const RefPtr<TouchEventImpl>& touchEvent)
    {
        touchAfterEvents_ = std::move(touchEvent);
    }

    void ClearTouchAfterEvent()
    {
        // When the event param is undefined, it will clear the callback.
        if (touchAfterEvents_) {
            touchAfterEvents_.Reset();
        }
    }

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result,
        ResponseLinkResult& responseLinkResult) override
    {
        SetGetEventTargetImpl(getEventTargetImpl);
        SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        result.emplace_back(Claim(this));
    }

    bool DispatchEvent(const TouchEvent& point) override;
    bool HandleEvent(const TouchEvent& point) override;

    void SetJSFrameNodeOnTouchEvent(TouchEventFunc&& callback)
    {
        if (commonTouchEventCallback_) {
            commonTouchEventCallback_.Reset();
        }
        commonTouchEventCallback_ = MakeRefPtr<TouchEventImpl>(std::move(callback));
    }

    void CopyTouchEvent(const RefPtr<TouchEventActuator>& touchEventActuator)
    {
        touchEvents_ = touchEventActuator->touchEvents_;
        userCallback_ = touchEventActuator->userCallback_;
        onTouchEventCallback_ = touchEventActuator->onTouchEventCallback_;
        commonTouchEventCallback_ = touchEventActuator->commonTouchEventCallback_;
    }

    void SetNeedPropagation(bool isNeedPropagation) {
        isNeedPropagation_ = isNeedPropagation;
    }

    bool IsNeedPropagation() const {
        return isNeedPropagation_;
    }

private:
    bool TriggerTouchCallBack(const TouchEvent& changedPoint);
    bool ShouldResponse() override;
    void TriggerCallBacks(TouchEventInfo& event);
    TouchEventInfo CreateTouchEventInfo(const TouchEvent& lastPoint);
    TouchLocationInfo CreateChangedTouchInfo(const TouchEvent& lastPoint, const TouchEvent& event);
    TouchLocationInfo CreateTouchItemInfo(const TouchPoint& pointItem, const TouchEvent& event, TouchType type);
    TouchLocationInfo CreateHistoryTouchItemInfo(const TouchEvent& eventItem, const TouchEvent& event);

    std::list<RefPtr<TouchEventImpl>> touchEvents_;
    RefPtr<TouchEventImpl> touchAfterEvents_;
    RefPtr<TouchEventImpl> userCallback_;
    RefPtr<TouchEventImpl> onTouchEventCallback_;
    RefPtr<TouchEventImpl> commonTouchEventCallback_;
    // isFlushTouchEventsEnd_ means the last one touch event info during one vsync period, used only for web_pattern
    // if isFlushTouchEventsEnd_ is true, web_pattern start to send touch event list to chromium
    bool isFlushTouchEventsEnd_ = false;
    std::map<int32_t, TimeStamp> firstInputTimeWithId_;
    bool isNeedPropagation_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_TOUCH_EVENT_H
