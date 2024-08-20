/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_RECOGNIZER_H

#include <functional>

#include "base/thread/cancelable_callback.h"
#include "core/gestures/multi_fingers_recognizer.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/core/gestures/click_info.h"

namespace OHOS::Ace {

class ClickRecognizer : public MultiFingersRecognizer {
    DECLARE_ACE_TYPE(ClickRecognizer, MultiFingersRecognizer);

public:
    ClickRecognizer() = default;
    ClickRecognizer(const WeakPtr<PipelineBase>& context, int32_t fingers,
        int32_t count, double distanceThreshold = std::numeric_limits<double>::infinity())
        : count_(count), context_(context)
    {
        fingers_ = fingers;
        distanceThreshold_ = distanceThreshold;
    }
    explicit ClickRecognizer(const WeakPtr<PipelineBase>& context) : context_(context) {}
    ~ClickRecognizer() override = default;

    void OnAccepted() override;
    void OnRejected() override;

    void SetOnClick(const ClickCallback& onClick)
    {
        onClick_ = onClick;
    }

    void SetRemoteMessage(const ClickCallback& remoteMessage)
    {
        remoteMessage_ = remoteMessage;
    }

    void SetUseCatchMode(bool useCatchMode)
    {
        useCatchMode_ = useCatchMode;
    }

private:
    void HandleTouchDownEvent(const TouchEvent& event) override;
    void HandleTouchUpEvent(const TouchEvent& event) override;
    void HandleTouchMoveEvent(const TouchEvent& event) override;
    void HandleTouchCancelEvent(const TouchEvent& event) override;
    bool ReconcileFrom(const RefPtr<GestureRecognizer>& recognizer) override;
    void HandleOverdueDeadline();
    void DeadlineTimer(CancelableCallback<void()>& deadlineTimer, int32_t time);
    Offset ComputeFocusPoint();
    void Reset();
    void SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback);
    bool ExceedSlop();
    void InitGlobalValue(SourceType deviceId);

    int32_t count_ = 1;
    double distanceThreshold_ = std::numeric_limits<double>::infinity();
    // number of fingers which put on the screen
    int32_t pointsCount_ = 0;
    int32_t tappedCount_ = 0;
    // Check whether the pointsCount_ has reached the configured value
    bool equalsToFingers_ = false;
    // the time when gesture recognition is successful
    TimeStamp time_;
    Offset focusPoint_;
    ClickCallback onClick_;
    ClickCallback remoteMessage_;
    bool useCatchMode_ = true;
    WeakPtr<PipelineBase> context_;
    CancelableCallback<void()> fingerDeadlineTimer_;
    CancelableCallback<void()> tapDeadlineTimer_;
    std::map<int32_t, TouchEvent> touchPoints_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_RECOGNIZER_H
