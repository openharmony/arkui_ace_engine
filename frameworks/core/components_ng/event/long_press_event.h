/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/gesture_event_actuator.h"
#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"

namespace OHOS::Ace::NG {

class GestureEventHub;

class LongPressEvent : public virtual AceType {
    DECLARE_ACE_TYPE(LongPressEvent, AceType);

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

    ACE_DISALLOW_COPY_AND_MOVE(LongPressEvent);
};

class ACE_FORCE_EXPORT LongPressEventActuator : public GestureEventActuator {
    DECLARE_ACE_TYPE(LongPressEventActuator, GestureEventActuator);

public:
    explicit LongPressEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub);
    ~LongPressEventActuator() override = default;

    void SetLongPressEvent(const RefPtr<LongPressEvent>& event, bool isForDrag = false, bool isDisableMouseLeft = false)
    {
        longPressEvent_ = event;
        isForDrag_ = isForDrag;
        isDisableMouseLeft_ = isDisableMouseLeft;
    }

    RefPtr<LongPressRecognizer> GetLongPressRecognizer() const
    {
        return longPressRecognizer_;
    }

    void SetDuration(int32_t duration)
    {
        if (!longPressRecognizer_) {
            longPressRecognizer_ = MakeRefPtr<LongPressRecognizer>(isForDrag_, isDisableMouseLeft_);
        }
        longPressRecognizer_->SetDuration(duration);
    }

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result,
        ResponseLinkResult& responseLinkResult) override;

    GestureEventFunc GetGestureEventFunc();

    void SetLongPressEventType(GestureTypeName typeName);

    virtual void CopyLongPressEvent(const RefPtr<LongPressEventActuator>& longPressEventActuator)
    {
        isForDrag_ = longPressEventActuator->isForDrag_;
        isDisableMouseLeft_ = longPressEventActuator->isDisableMouseLeft_;
        auto originalLongPressRecognizer = longPressEventActuator->longPressRecognizer_;
        if (originalLongPressRecognizer) {
            if (!longPressRecognizer_) {
                longPressRecognizer_ = MakeRefPtr<LongPressRecognizer>(isForDrag_, isDisableMouseLeft_);
            }
            longPressRecognizer_->SetDuration(originalLongPressRecognizer->GetDuration());
        }
    }

    void CopyInnerEvent(const RefPtr<LongPressEventActuator>& longPressEventActuator);

private:
    bool isForDrag_ = false;
    bool isDisableMouseLeft_ = false;
    WeakPtr<GestureEventHub> gestureEventHub_;
    RefPtr<LongPressRecognizer> longPressRecognizer_;
    RefPtr<LongPressEvent> longPressEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(LongPressEventActuator);
};

using MultiSelectHandler = std::function<void(RefPtr<LongPressRecognizer>& longPressRecognizer)>;

class ACE_FORCE_EXPORT LongPressEventActuatorWithMultiSelect : public LongPressEventActuator {
    DECLARE_ACE_TYPE(LongPressEventActuatorWithMultiSelect, LongPressEventActuator);

public:
    explicit LongPressEventActuatorWithMultiSelect(const WeakPtr<GestureEventHub>& gestureEventHub)
        : LongPressEventActuator(gestureEventHub)
    {}
    ~LongPressEventActuatorWithMultiSelect() override = default;

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result,
        ResponseLinkResult& responseLinkResult) override;

    void CopyLongPressEvent(const RefPtr<LongPressEventActuator>& longPressEventActuator) override;

    void SetMultiSelectHandler(MultiSelectHandler&& handler)
    {
        multiSelectHandler_ = handler;
    }

private:
    MultiSelectHandler multiSelectHandler_;
};

class LongPressEventActuatorFactory {
public:
    static RefPtr<LongPressEventActuator> CreateLongPressEventActuator(
        const WeakPtr<GestureEventHub>& gestureEventHub, bool withMultiSelect)
    {
        if (!withMultiSelect) {
            return AceType::MakeRefPtr<LongPressEventActuator>(gestureEventHub);
        } else {
            return AceType::MakeRefPtr<LongPressEventActuatorWithMultiSelect>(gestureEventHub);
        }
    }

    static RefPtr<LongPressEventActuator> CopyLongPressEvent(
        RefPtr<LongPressEventActuator> source, const WeakPtr<GestureEventHub>& gestureEventHub)
    {
        if (!source) {
            return nullptr;
        }
        bool withMultiSelect = AceType::InstanceOf<LongPressEventActuatorWithMultiSelect>(source);
        auto newActuator = CreateLongPressEventActuator(gestureEventHub, withMultiSelect);
        newActuator->CopyLongPressEvent(source);
        return newActuator;
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_LONG_PRESS_EVENT_H
