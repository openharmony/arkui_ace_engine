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
#include <unordered_set>

#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/gestures/velocity.h"
#include "core/gestures/velocity_tracker.h"

namespace OHOS::Ace::NG {
enum class PanGestureState : int32_t;

class ACE_FORCE_EXPORT PanRecognizer : public MultiFingersRecognizer {
    DECLARE_ACE_TYPE(PanRecognizer, MultiFingersRecognizer);

public:
    PanRecognizer(int32_t fingers, const PanDirection& direction, double distance, bool isLimitFingerCount = false);
    PanRecognizer(int32_t fingers, const PanDirection& direction, const PanDistanceMap& distanceMap,
        bool isLimitFingerCount = false);
    PanRecognizer(int32_t fingers, const PanDirection& direction, const PanDistanceMapDimension& distanceMap,
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

    void SetDistanceMap(const PanDistanceMap& distanceMap);

    void SetDistanceMap(const PanDistanceMapDimension& distanceMap)
    {
        distanceMap_ = distanceMap;
    }

    PanDistanceMapDimension GetDistanceMap() const
    {
        return distanceMap_;
    }

    void HandlePanGestureAccept(const GestureEvent& info, PanGestureState panGestureState, GestureCallbackType type);

    void SetPanEndCallback(const GestureEventFunc& panEndCallback)
    {
        panEndOnDisableState_ = std::make_unique<GestureEventFunc>(panEndCallback);
    }

    const RefPtr<PanGestureOption>& GetPanGestureOption() const
    {
        return panGestureOption_;
    }

    void SetAngle(double angle)
    {
        angle_ = angle;
    }

    double GetAngle() const
    {
        return angle_;
    }

    // ----- Pan-Gesture-Escape API ---------------------------------------
    // SetCanCoexistWithScroll(true) marks this PanRecognizer as a
    // "multi-selection" Pan that should be allowed to live next to scroll.
    // When such a recognizer crosses the pan threshold for a finger, every
    // other PanRecognizer in the arena is asked to "escape" that finger:
    // they release per-finger state for it and stop receiving events for
    // it, but they remain alive in the arena and continue to compete for
    // *new* fingers (so scroll keeps working with a second finger while
    // multi-selection drives the first one).
    void SetCanCoexistWithScroll(bool value)
    {
        canCoexistWithScroll_ = value;
    }
    bool CanCoexistWithScroll() const
    {
        return canCoexistWithScroll_;
    }

    // Returns the set of finger ids currently tracked by this recognizer.
    std::unordered_set<int32_t> GetCurrentFingerIds() const;

    // Drop one finger from this Pan's tracking state. Called by other
    // recognizers via the escape mechanism. Public because the Referee
    // dispatches it through the polymorphic NGGestureRecognizer hook.
    void OnFingerEscaped(int32_t fingerId) override;

    // Activated externally as well: enables escape mode on this Pan and
    // immediately releases any of the listed fingers that we are tracking.
    void SetEscapeModeForPan(const std::unordered_set<int32_t>& existingFingers);

    // Walk the arena and ask every other PanRecognizer
    // to release the fingers we currently track.
    void FilterCoexistingGestureFingers();

protected:
    std::string GetGestureInfoString() const override;
private:
    class PanVelocity {
    public:
        Velocity GetVelocity();
        double GetMainAxisVelocity();
        void UpdateTouchPoint(int32_t id, const TouchEvent& event, bool end);
        void Reset(int32_t id);
        void ResetAll();
        void SetDirection(int32_t directionType);
        Axis GetDirection();
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
    void HandleCallbackReports(const GestureEvent& info, GestureCallbackType type, PanGestureState panGestureState);
    void HandleReports(const GestureEvent& info, GestureCallbackType type) override;
    GestureJudgeResult TriggerGestureJudgeCallback();
    void UpdateGestureEventInfo(std::shared_ptr<PanGestureEvent>& info);
    void ChangeFingers(int32_t fingers);
    void ChangeDirection(const PanDirection& direction);
    void ChangeDistance(double distance);
    double GetMainAxisDelta();
    RefPtr<DragEventActuator> GetDragEventActuator();
    bool HandlePanAccept();
    bool HandlePanExtAccept();
    void GetGestureEventHalfInfo(GestureEvent* info);
    GestureEvent BuildGestureEventWithCurrentLocalInfo(
        TouchEvent& touchPoint, Offset& localOffset, int32_t& postEventNodeId);
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
    int32_t newFingers_ = 1;
    double newDistance_ = 0.0;
    PanDirection newDirection_;
    PanDistanceMapDimension distanceMap_;
    PanDistanceMapDimension newDistanceMap_;

    AxisEvent lastAxisEvent_;
    Offset averageDistance_;
    std::map<int32_t, Offset> touchPointsDistance_;
    Offset delta_;
    double mainDelta_ = 0.0;
    PanVelocity panVelocity_;
    TimeStamp time_;
    bool isFlushTouchEventsEnd_ = false;
    bool isForDrag_ = false;
    bool isAllowMouse_ = true;
    bool isStartTriggered_ = false;
    Point globalPoint_;
    TouchEvent lastTouchEvent_;
    RefPtr<PanGestureOption> panGestureOption_;

    OnPanFingersFunc onChangeFingers_;
    OnPanDirectionFunc onChangeDirection_;
    OnPanDistanceFunc onChangeDistance_;
    // this callback will be triggered when pan end, but the enable state is false
    std::unique_ptr<GestureEventFunc> panEndOnDisableState_;
    double angle_ = 45.0;

    // Pan-gesture-escape opt-in: when true, this recognizer will push its
    // tracked fingers out of every other PanRecognizer in the arena once it
    // crosses the pan threshold. Default (false) keeps legacy exclusive
    // arena semantics.
    bool canCoexistWithScroll_ = false;
    // Set to true once we issued the escape request, so we do it exactly
    // once per gesture cycle. Re-armed in OnResetStatus().
    bool escapeRequested_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_PAN_RECOGNIZER_H
