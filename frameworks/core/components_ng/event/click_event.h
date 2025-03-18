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

    void SetSysJudge(const GestureJudgeFunc& sysJudge)
    {
        sysJudge_ = sysJudge;
    }

    bool HasSysGestureJudge() const
    {
        return sysJudge_.has_value();
    }

    std::optional<GestureJudgeFunc> GetSysJudge() const
    {
        if (sysJudge_.has_value()) {
            return sysJudge_.value();
        }
        return nullptr;
    }

private:
    GestureEventFunc callback_;

    std::optional<GestureJudgeFunc> sysJudge_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(ClickEvent);
};

class ACE_EXPORT ClickEventActuator : public GestureEventActuator {
    DECLARE_ACE_TYPE(ClickEventActuator, GestureEventActuator)
public:
    explicit ClickEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub);
    ~ClickEventActuator() override = default;

    void SetUserCallback(GestureEventFunc&& callback)
    {
        userCallback_ = MakeRefPtr<ClickEvent>(std::move(callback));
    }

    void ClearUserCallback()
    {
        // When the event param is undefined, it will clear the callback.
        if (userCallback_) {
            userCallback_.Reset();
        }
    }

    bool IsUserClickable() const
    {
        return userCallback_ != nullptr;
    }

    bool IsComponentClickable() const
    {
        return !(clickEvents_.empty() && !clickAfterEvents_ && !userCallback_ && !jsFrameNodeCallback_);
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

    void AddDistanceThreshold(double distanceThreshold)
    {
        distanceThreshold_ = distanceThreshold;
        if (distanceThreshold_ <= 0) {
            distanceThreshold_ = std::numeric_limits<double>::infinity();
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

    void AddClickAfterEvent(const RefPtr<ClickEvent>& clickEvent)
    {
        clickAfterEvents_ = std::move(clickEvent);
    }

    void ClearClickAfterEvent()
    {
        // When the event param is undefined, it will clear the callback.
        if (clickAfterEvents_) {
            clickAfterEvents_.Reset();
        }
    }

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result,
        ResponseLinkResult& responseLinkResult) override;

    GestureEventFunc GetClickEvent();
    std::optional<GestureJudgeFunc> GetSysJudgeFunc() const;

    const RefPtr<ClickRecognizer>& GetClickRecognizer()
    {
        if (!clickRecognizer_) {
            clickRecognizer_ = MakeRefPtr<ClickRecognizer>();
        }
        return clickRecognizer_;
    }

    void SetJSFrameNodeCallback(GestureEventFunc&& callback)
    {
        if (jsFrameNodeCallback_) {
            jsFrameNodeCallback_.Reset();
        }
        jsFrameNodeCallback_ = MakeRefPtr<ClickEvent>(std::move(callback));
        if (!clickRecognizer_) {
            clickRecognizer_ = MakeRefPtr<ClickRecognizer>();
        }
    }

    void ClearJSFrameNodeCallback()
    {
        // When the event param is undefined, it will clear the callback.
        if (jsFrameNodeCallback_) {
            jsFrameNodeCallback_.Reset();
        }
    }

    void CopyClickEvent(const RefPtr<ClickEventActuator>& clickEventActuator)
    {
        clickEvents_ = clickEventActuator->clickEvents_;
        userCallback_ = clickEventActuator->userCallback_;
        jsFrameNodeCallback_ = clickEventActuator->jsFrameNodeCallback_;
        if (clickEventActuator->clickRecognizer_) {
            clickRecognizer_ = MakeRefPtr<ClickRecognizer>();
        }
    }
    
private:
    WeakPtr<GestureEventHub> gestureEventHub_;
    std::list<RefPtr<ClickEvent>> clickEvents_;
    RefPtr<ClickEvent> clickAfterEvents_;
    RefPtr<ClickEvent> userCallback_;
    RefPtr<ClickEvent> jsFrameNodeCallback_;
    RefPtr<ClickRecognizer> clickRecognizer_;
    double distanceThreshold_ = std::numeric_limits<double>::infinity();

    ACE_DISALLOW_COPY_AND_MOVE(ClickEventActuator);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CLICK_EVENT_H
