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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_ROTATION_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_ROTATION_RECOGNIZER_H

#include <cmath>
#include <functional>
#include <map>

#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"

namespace OHOS::Ace::NG {

class RotationRecognizer : public MultiFingersRecognizer {
    DECLARE_ACE_TYPE(RotationRecognizer, MultiFingersRecognizer);

public:
    RotationRecognizer(int32_t fingers, double angle, bool isLimitFingerCount = false);
    ~RotationRecognizer() override = default;

    void OnAccepted() override;
    void OnRejected() override;

    virtual RefPtr<GestureSnapshot> Dump() const override;

    void SetAngle(double angle)
    {
        angle_ = angle;
    }

    double GetAngle()
    {
        return angle_;
    }

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
    double ComputeAngle();
    void OnResetStatus() override;
    void SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback);
    GestureJudgeResult TriggerGestureJudgeCallback();
    static double ChangeValueRange(double value);

    double angle_ = 0.0;
    double initialAngle_ = 0.0;
    double currentAngle_ = 0.0;
    double resultAngle_ = 0.0;
    double lastAngle_ = 0.0;
    bool angleSignChanged_ = false;
    TimeStamp time_;
    AxisEvent lastAxisEvent_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_ROTATION_RECOGNIZER_H