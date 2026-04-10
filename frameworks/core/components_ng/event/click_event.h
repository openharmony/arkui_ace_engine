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
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/gesture_event_actuator.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "ui/gestures/gesture_event.h"
#include "core/components_ng/event/target_component.h"

namespace OHOS::Ace {

class ClickInfo;

} // namespace OHOS::Ace

namespace OHOS::Ace::NG {

class GestureEventHub;
class ClickRecognizer;

class ClickEvent : public AceType {
    DECLARE_ACE_TYPE(ClickEvent, AceType);
public:
    explicit ClickEvent(GestureEventFunc&& callback) : callback_(std::move(callback)) {}
    ~ClickEvent() override = default;

    const GestureEventFunc& GetGestureEventFunc() const
    {
        return callback_;
    }

    void operator()(GestureEvent& info) const;

    void SetSysJudge(const GestureJudgeFunc& sysJudge)
    {
        sysJudge_ = sysJudge;
    }

    bool HasSysGestureJudge() const
    {
        return sysJudge_.has_value();
    }

    std::optional<GestureJudgeFunc> GetSysJudge() const;

private:
    GestureEventFunc callback_;

    std::optional<GestureJudgeFunc> sysJudge_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(ClickEvent);
};

class ACE_FORCE_EXPORT ClickEventActuator : public GestureEventActuator {
    DECLARE_ACE_TYPE(ClickEventActuator, GestureEventActuator);
public:
    explicit ClickEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub);
    ~ClickEventActuator() override = default;

    void SetUserCallback(GestureEventFunc&& callback);

    void ClearUserCallback();

    bool IsUserClickable() const
    {
        return userCallback_ != nullptr;
    }

    bool IsComponentClickable() const;

    void AddClickEvent(const RefPtr<ClickEvent>& clickEvent);

    void AddDistanceThreshold(double distanceThreshold);
    void AddDistanceThreshold(Dimension distanceThreshold);

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

    void ClearClickAfterEvent();

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

    void SetJSFrameNodeCallback(GestureEventFunc&& callback);

    void ClearJSFrameNodeCallback();

    void CopyClickEvent(const RefPtr<ClickEventActuator>& clickEventActuator);
    
private:
    WeakPtr<GestureEventHub> gestureEventHub_;
    std::list<RefPtr<ClickEvent>> clickEvents_;
    RefPtr<ClickEvent> clickAfterEvents_;
    RefPtr<ClickEvent> userCallback_;
    RefPtr<ClickEvent> jsFrameNodeCallback_;
    RefPtr<ClickRecognizer> clickRecognizer_;
    Dimension distanceThreshold_ = Dimension(std::numeric_limits<double>::infinity(), DimensionUnit::PX);

    ACE_DISALLOW_COPY_AND_MOVE(ClickEventActuator);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CLICK_EVENT_H
