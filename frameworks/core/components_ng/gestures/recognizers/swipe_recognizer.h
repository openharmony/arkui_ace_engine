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
#include <map>

#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"

namespace OHOS::Ace::NG {

class SwipeRecognizer : public MultiFingersRecognizer {
    DECLARE_ACE_TYPE(SwipeRecognizer, MultiFingersRecognizer);

public:
    SwipeRecognizer(int32_t fingers, const SwipeDirection& direction, double speed)
        : direction_(direction), speed_(speed), newFingers_(fingers_), newSpeed_(speed_), newDirection_(direction_)
    {
        fingers_ = fingers;
    }

    ~SwipeRecognizer() override = default;

    void OnAccepted() override;
    void OnRejected() override;

private:
    enum class GestureAcceptResult {
        ACCEPT,
        REJECT,
        DETECTING,
    };
    void HandleTouchDownEvent(const TouchEvent& event) override;
    void HandleTouchUpEvent(const TouchEvent& event) override;
    void HandleTouchMoveEvent(const TouchEvent& event) override;
    void HandleTouchCancelEvent(const TouchEvent& event) override;
    void HandleTouchDownEvent(const AxisEvent& event) override;
    void HandleTouchUpEvent(const AxisEvent& event) override;
    void HandleTouchMoveEvent(const AxisEvent& event) override;
    void HandleTouchCancelEvent(const AxisEvent& event) override;
    bool ReconcileFrom(const RefPtr<GestureRecognizer>& recognizer) override;
    GestureAcceptResult ParseFingersOffset() const;
    GestureAcceptResult ParseAxisOffset() const;
    void Reset();
    void SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback);
    void ChangeFingers(int32_t fingers);
    void ChangeDirection(const SwipeDirection& direction);
    void ChangeSpeed(double speed);
    double ComputeAngle();
    double ComputeAngle(AxisEvent event);

    const TouchRestrict& GetTouchRestrict() const
    {
        return touchRestrict_;
    }

    SwipeDirection direction_;
    double speed_ = 0.0;
    WeakPtr<PipelineBase> context_;
    std::map<int32_t, TouchEvent> touchPoints_;
    std::map<int32_t, Offset> fingersDistance_;
    AxisEvent axisEventStart_;
    double axisVerticalTotal_ = 0.0;
    double axisHorizontalTotal_ = 0.0;
    TimeStamp time_;
    TimeStamp touchDownTime_;
    bool slidingEnd_ = false;
    bool slidingCancel_ = false;
    Point globalPoint_;
    OnSwipeFingersFunc onChangeFingers_;
    OnSwipeDirectionFunc onChangeDirection_;
    OnSwipeSpeedFunc onChangeSpeed_;
    int32_t newFingers_ = 1;

    double angle_ = 0.0;
    double initialAngle_ = 0.0;
    double currentAngle_ = 0.0;
    double resultAngle_ = 0.0;
    double resultSpeed_ = 0.0;

    double newSpeed_ = 0.0;
    SwipeDirection newDirection_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_SLIDE_RECOGNIZER_H
