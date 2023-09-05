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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_PAN_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_PAN_RECOGNIZER_H

#include <map>
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"

namespace OHOS::Ace::NG {

class PanRecognizer : public MultiFingersRecognizer {
    DECLARE_ACE_TYPE(PanRecognizer, MultiFingersRecognizer);

public:
    PanRecognizer(int32_t fingers, const PanDirection& direction, double distance);

    explicit PanRecognizer(const RefPtr<PanGestureOption>& panGestureOption);

    ~PanRecognizer() override
    {
        if (panGestureOption_ == nullptr) {
            return;
        }
        panGestureOption_->GetOnPanFingersIds().erase(onChangeFingers_.GetId());
        panGestureOption_->GetOnPanDirectionIds().erase(onChangeDirection_.GetId());
        panGestureOption_->GetOnPanDistanceIds().erase(onChangeDistance_.GetId());
    }

    void OnAccepted() override;
    void OnRejected() override;

    void OnFlushTouchEventsBegin() override;
    void OnFlushTouchEventsEnd() override;

    void SetDirection(const PanDirection& direction);

    void SetIsForDrag(bool isForDrag)
    {
        isForDrag_ = isForDrag;
    }

    void SetMouseDistance(double distance)
    {
        mouseDistance_ = distance;
    }

    void SetIsAllowMouse(bool isAllowMouse)
    {
        isAllowMouse_ = isAllowMouse;
    }

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

    bool ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer) override;
    GestureAcceptResult IsPanGestureAccept() const;
    bool CalculateTruthFingers(bool isDirectionUp) const;

    void SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback);
    void ChangeFingers(int32_t fingers);
    void ChangeDirection(const PanDirection& direction);
    void ChangeDistance(double distance);
    double GetMainAxisDelta();

    void OnResetStatus() override;
    void OnSucceedCancel() override;

    const TouchRestrict& GetTouchRestrict() const
    {
        return touchRestrict_;
    }

    PanDirection direction_;
    double distance_ = 0.0;
    double mouseDistance_ = 0.0;
    AxisEvent lastAxisEvent_;
    Offset averageDistance_;
    std::map<int32_t, Offset> touchPointsDistance_;
    Offset delta_;
    double mainDelta_ = 0.0;
    VelocityTracker velocityTracker_;
    TimeStamp time_;

    Point globalPoint_;
    TouchEvent lastTouchEvent_;
    RefPtr<PanGestureOption> panGestureOption_;
    OnPanFingersFunc onChangeFingers_;
    OnPanDirectionFunc onChangeDirection_;
    OnPanDistanceFunc onChangeDistance_;

    int32_t newFingers_ = 1;
    double newDistance_ = 0.0;
    PanDirection newDirection_;
    bool isFlushTouchEventsEnd_ = false;
    InputEventType inputEventType_ = InputEventType::TOUCH_SCREEN;
    bool isForDrag_ = false;
    bool isAllowMouse_ = true;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_PAN_RECOGNIZER_H
