/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_LONG_PRESS_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_LONG_PRESS_RECOGNIZER_H

#include <functional>

#include "base/thread/cancelable_callback.h"
#include "core/accessibility/accessibility_utils.h"
#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"

namespace OHOS::Ace::NG {
using OnAccessibilityEventFunc = std::function<void(AccessibilityEventType)>;

class GestureEventHub;
class LongPressInfo : public TouchLocationInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LongPressInfo, TouchLocationInfo);

public:
    explicit LongPressInfo(int32_t fingerId) : TouchLocationInfo("onLongPress", fingerId) {}
    ~LongPressInfo() override = default;
};

using OnLongPress = std::function<void(const LongPressInfo&)>;
using LongPressCallback = std::function<void(const GestureEvent&)>;
using LongPressNoParamCallback = std::function<void()>;

class ACE_FORCE_EXPORT LongPressRecognizer : public MultiFingersRecognizer {
    DECLARE_ACE_TYPE(LongPressRecognizer, MultiFingersRecognizer);

public:
    explicit LongPressRecognizer() = default;
    LongPressRecognizer(int32_t duration, int32_t fingers, bool repeat,
        bool isForDrag = false, bool isDisableMouseLeft = false, bool isLimitFingerCount = false);

    LongPressRecognizer(bool isForDrag = false, bool isDisableMouseLeft = false)
        : isForDrag_(isForDrag), isDisableMouseLeft_(isDisableMouseLeft)
    {}
    ~LongPressRecognizer() override = default;

    void OnAccepted() override;
    void OnRejected() override;

    bool HasAction() const
    {
        if (onAction_ && *onAction_) {
            return true;
        }
        return false;
    }

    void SetOnLongPressRecorder(const GestureEventFunc& recorder)
    {
        longPressRecorder_ = std::make_unique<GestureEventFunc>(recorder);
    }

    void SetUseCatchMode(bool useCatchMode)
    {
        useCatchMode_ = useCatchMode;
    }

    void SetDuration(int32_t duration)
    {
        duration_ = duration;
    }

    int32_t GetDuration() const
    {
        return duration_;
    }

    void SetGestureHub(WeakPtr<GestureEventHub> gestureHub)
    {
        gestureHub_ = gestureHub;
    }

    void SetThumbnailDeadline(int32_t deadlineTime)
    {
        thumbnailDeadline = deadlineTime;
    }

    void SetThumbnailCallback(std::function<void(Offset)>&& callback)
    {
        callback_ = std::move(callback);
    }

    bool HasThumbnailCallback()
    {
        return static_cast<bool>(callback_);
    }

    void SetOnAccessibility(OnAccessibilityEventFunc onAccessibilityEvent)
    {
        onAccessibilityEventFunc_ = std::move(onAccessibilityEvent);
    }

    GestureEventFunc GetLongPressActionFunc();

    virtual RefPtr<GestureSnapshot> Dump() const override;

    void PrintCurrentFingersInfo() const;

private:
    void HandleTouchDownEvent(const TouchEvent& event) override;
    void HandleTouchUpEvent(const TouchEvent& event) override;
    void HandleTouchMoveEvent(const TouchEvent& event) override;
    void HandleTouchCancelEvent(const TouchEvent& event) override;
    bool ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer) override;
    void HandleOverdueDeadline(bool isCatchMode);
    void DeadlineTimer(int32_t time, bool isCatchMode);
    void DoRepeat();
    void StartRepeatTimer();
    void SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback, bool isRepeat, bool isOnAction = false);
    GestureJudgeResult TriggerGestureJudgeCallback();
    void OnResetStatus() override;
    double ConvertPxToVp(double offset) const;
    void ThumbnailTimer(int32_t time);
    RefPtr<DragEventActuator> GetDragEventActuator();

    TouchEvent lastTouchEvent_;
    WeakPtr<GestureEventHub> gestureHub_;
    CancelableCallback<void()> thumbnailTimer_;
    int32_t thumbnailDeadline = 150;
    CancelableCallback<void()> deadlineTimer_;
    CancelableCallback<void()> timer_;
    std::function<void(Offset)> callback_;
    int32_t duration_ = 500;
    bool repeat_ = false;
    TimeStamp time_;
    bool useCatchMode_ = true;
    bool isForDrag_ = false;
    bool isDisableMouseLeft_ = false;
    Point globalPoint_;
    DelayedTask task_;
    OnAccessibilityEventFunc onAccessibilityEventFunc_ = nullptr;
    std::unique_ptr<GestureEventFunc> longPressRecorder_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_LONG_PRESS_RECOGNIZER_H
