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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_SLIDE_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_SLIDE_RECOGNIZER_H

#include <cmath>
#include <functional>
#include <optional>

#include "base/utils/type_definition.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {

class SwipeRecognizer : public MultiFingersRecognizer {
    DECLARE_ACE_TYPE(SwipeRecognizer, MultiFingersRecognizer);

public:
    SwipeRecognizer(int32_t fingers, const SwipeDirection& direction, double speed)
        : MultiFingersRecognizer(fingers), direction_(direction), speed_(speed)
    {}
    ~SwipeRecognizer() override = default;

    void OnAccepted() override;
    void OnRejected() override;

    Axis GetAxisDirection() override
    {
        switch (direction_.type) {
            case SwipeDirection::HORIZONTAL:
                return Axis::HORIZONTAL;
            case SwipeDirection::VERTICAL:
                return Axis::VERTICAL;
            case SwipeDirection::ALL:
                return Axis::FREE;
            default:
                return Axis::NONE;
        }
    }

    virtual RefPtr<GestureSnapshot> Dump() const override;

private:
    void HandleTouchDownEvent(const TouchEvent& event) override;
    void HandleTouchUpEvent(const TouchEvent& event) override;
    void HandleTouchMoveEvent(const TouchEvent& event) override;
    void HandleTouchCancelEvent(const TouchEvent& event) override;
    void HandleTouchDownEvent(const AxisEvent& event) override;
    void HandleTouchUpEvent(const AxisEvent& event) override;
    void HandleTouchMoveEvent(const AxisEvent& event) override;
    void HandleTouchCancelEvent(const AxisEvent& event) override;
    bool ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer) override;

    void OnResetStatus() override;

    void SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback);
    GestureJudgeResult TriggerGestureJudgeCallback();

    bool CheckAngle(double angle);

    SwipeDirection direction_;
    double speed_ = 0.0;
    TouchEvent lastTouchEvent_;
    std::map<int32_t, TouchEvent> downEvents_;

    AxisEvent axisEventStart_;
    AxisEvent lastAxisEvent_;
    Offset axisOffset_;

    TimeStamp time_;
    TimeStamp touchDownTime_;

    Point globalPoint_;

    std::optional<double> prevAngle_;

    double resultSpeed_ = 0.0;

    std::set<int32_t> matchedTouch_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_SLIDE_RECOGNIZER_H
