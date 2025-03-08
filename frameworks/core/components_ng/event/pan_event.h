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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_PAN_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_PAN_EVENT_H

#include <list>
#include <utility>

#include "base/memory/referenced.h"
#include "core/components_ng/event/gesture_event_actuator.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"

namespace OHOS::Ace::NG {

class GestureEventHub;
class PanRecognizer;

class PanEvent : public virtual AceType {
    DECLARE_ACE_TYPE(PanEvent, AceType)
public:
    PanEvent(GestureEventFunc&& actionStart, GestureEventFunc&& actionUpdate, GestureEventFunc&& actionEnd,
        GestureEventNoParameter&& actionCancel)
        : actionStart_(std::move(actionStart)), actionUpdate_(std::move(actionUpdate)),
          actionEnd_(std::move(actionEnd)), actionCancel_(std::move(actionCancel))
    {}
    ~PanEvent() override = default;

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

class ACE_FORCE_EXPORT PanEventActuator : public GestureEventActuator {
    DECLARE_ACE_TYPE(PanEventActuator, GestureEventActuator)
public:
    PanEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub, PanDirection direction, int32_t fingers,
        float distance);
    ~PanEventActuator() override = default;

    void ReplacePanEvent(const RefPtr<PanEvent>& panEvent)
    {
        if (userCallback_) {
            userCallback_.Reset();
        }
        userCallback_ = panEvent;
    }

    void AddPanEvent(const RefPtr<PanEvent>& panEvent)
    {
        if (panEvents_.empty()) {
            panEvents_.emplace_back(panEvent);
            return;
        }
        if (std::find(panEvents_.begin(), panEvents_.end(), panEvent) == panEvents_.end()) {
            panEvents_.emplace_back(panEvent);
        }
    }

    void RemovePanEvent(const RefPtr<PanEvent>& panEvent)
    {
        panEvents_.remove(panEvent);
    }

    void SetPanEventType(GestureTypeName typeName);

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result,
        ResponseLinkResult& responseLinkResult) override;

    PanDirection GetDirection() const
    {
        return direction_;
    }

    void SetIsAllowMouse(bool isAllowMouse) const
    {
        CHECK_NULL_VOID(panRecognizer_);
        panRecognizer_->SetIsAllowMouse(isAllowMouse);
    }

    bool IsPanEventEmpty() const
    {
        return panEvents_.empty();
    }

    void SetExcludedAxis(bool isExcludedAxis)
    {
        isExcludedAxis_ = isExcludedAxis;
    }

    void DumpVelocityInfo(int32_t fingerId);

private:
    WeakPtr<GestureEventHub> gestureEventHub_;
    std::list<RefPtr<PanEvent>> panEvents_;
    RefPtr<PanEvent> userCallback_;
    RefPtr<PanRecognizer> panRecognizer_;
    bool isExcludedAxis_ = false;

    PanDirection direction_;
    int32_t fingers_ = 1;
    float distance_ = 0.0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_PAN_EVENT_H
