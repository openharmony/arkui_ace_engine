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

#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"

namespace OHOS::Ace::NG {
enum class PanGestureState : int32_t;

class ACE_FORCE_EXPORT PanRecognizer : public MultiFingersRecognizer {
    DECLARE_ACE_TYPE(PanRecognizer, MultiFingersRecognizer);

public:
    PanRecognizer(int32_t fingers, const PanDirection& direction, double distance, bool isLimitFingerCount = false);
    PanRecognizer(int32_t fingers, const PanDirection& direction, const PanDistanceMap& distanceMap,
        bool isLimitFingerCount = false);

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

    Axis GetAxisDirection() override;

    void SetDirection(const PanDirection& direction);

    void SetIsForDrag(bool isForDrag)
    {
        isForDrag_ = isForDrag;
    }

    void SetMouseDistance(double distance);

    void SetIsAllowMouse(bool isAllowMouse)
    {
        isAllowMouse_ = isAllowMouse;
    }

    virtual RefPtr<GestureSnapshot> Dump() const override;
    RefPtr<Gesture> CreateGestureFromRecognizer() const override;
    void ForceCleanRecognizer() override;
    void DumpVelocityInfo(int32_t fingerId);

    double GetDistance() const;
    double GetDistanceConfigFor(SourceTool sourceTool = SourceTool::UNKNOWN) const;

    PanDirection GetDirection() const
    {
        return direction_;
    }

    void SetDistanceMap(const PanDistanceMap& distanceMap)
    {
        distanceMap_ = distanceMap;
    }

    PanDistanceMap GetDistanceMap() const
    {
        return distanceMap_;
    }

    void HandlePanGestureAccept(
        const GestureEvent& info, PanGestureState panGestureState, const std::unique_ptr<GestureEventFunc>& callback);
    
    void SetPanEndCallback(const GestureEventFunc& panEndCallback)
    {
        panEndOnDisableState_ = std::make_unique<GestureEventFunc>(panEndCallback);
    }

private:
    class PanVelocity {
    public:
        Velocity GetVelocity();
        double GetMainAxisVelocity();
        void UpdateTouchPoint(int32_t id, const TouchEvent& event, bool end);
        void Reset(int32_t id);
        void ResetAll();
        void SetDirection(int32_t directionType);
        const std::map<int32_t, VelocityTracker>& GetVelocityMap() const
        {
            return trackerMap_;
        }

    private:
        int32_t GetFastestTracker(std::function<double(VelocityTracker&)>&& func);
        std::map<int32_t, VelocityTracker> trackerMap_;
        Axis axis_ = Axis::FREE;
    };

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
    GestureAcceptResult IsPanGestureAcceptInAllDirection(double judgeDistance) const;
    GestureAcceptResult IsPanGestureAcceptInHorizontalDirection(double judgeDistance) const;
    GestureAcceptResult IsPanGestureAcceptInVerticalDirection(double judgeDistance) const;
    bool JudgeVerticalDistance() const;
    bool CalculateTruthFingers(bool isDirectionUp) const;
    void UpdateTouchPointInVelocityTracker(const TouchEvent& touchEvent);
    void UpdateAxisPointInVelocityTracker(const AxisEvent& event, bool end = false);
    void UpdateTouchEventInfo(const TouchEvent& event);
    Offset GetRawGlobalLocation(int32_t postEventNodeId);

    void SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback, GestureCallbackType type);
    GestureJudgeResult TriggerGestureJudgeCallback();
    void ChangeFingers(int32_t fingers);
    void ChangeDirection(const PanDirection& direction);
    void ChangeDistance(double distance);
    double GetMainAxisDelta();
    RefPtr<DragEventActuator> GetDragEventActuator();
    bool HandlePanAccept();
    void GetGestureEventHalfInfo(GestureEvent* info);
    GestureEvent GetGestureEventInfo();
    void ResetDistanceMap();

    void OnResetStatus() override;
    void OnSucceedCancel() override;

    void AddOverTimeTrace();

    void DispatchPanStartedToPerf(const TouchEvent& event);

    const TouchRestrict& GetTouchRestrict() const
    {
        return touchRestrict_;
    }

    void UpdateAxisDeltaTransform(const AxisEvent& event);

    PanDirection direction_;
    double distance_ = 0.0;
    double mouseDistance_ = 0.0;
    AxisEvent lastAxisEvent_;
    Offset averageDistance_;
    std::map<int32_t, Offset> touchPointsDistance_;
    Offset delta_;
    double mainDelta_ = 0.0;
    PanVelocity panVelocity_;
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
    bool isForDrag_ = false;
    bool isAllowMouse_ = true;
    bool isStartTriggered_ = false;
    // this callback will be triggered when pan end, but the enable state is false
    std::unique_ptr<GestureEventFunc> panEndOnDisableState_;
    PanDistanceMap distanceMap_;
    PanDistanceMap newDistanceMap_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_PAN_RECOGNIZER_H
