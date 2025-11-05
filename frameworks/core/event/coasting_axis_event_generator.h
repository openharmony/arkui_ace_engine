/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_COASTING_AXIS_EVENT_GENERATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_COASTING_AXIS_EVENT_GENERATOR_H

#include "core/components_ng/base/modifier.h"
#include "core/event/axis_event.h"
#include "core/gestures/velocity_tracker.h"

namespace OHOS::Ace {
class CoastingAxisEventGenerator : public AceType {
    DECLARE_ACE_TYPE(CoastingAxisEventGenerator, AceType);

public:
    CoastingAxisEventGenerator();
    ~CoastingAxisEventGenerator() override = default;

    void NotifyAxisEvent(const AxisEvent& event, const RefPtr<NG::FrameNode>& node);
    void NotifyStop() const;
    void NotifyTouchTestResult(const TouchTestResult& touchTestResult, const NG::PointF& point);
    void SetAxisToTouchConverter(std::function<TouchEvent(const AxisEvent&)>&& axisToTouchConverter)
    {
        axisToTouchConverter_ = std::move(axisToTouchConverter);
    }
    bool IsAnimationRunning() const
    {
        CHECK_NULL_RETURN(animationHandler_, false);
        return animationHandler_->IsAnimationRunning();
    }

private:
    enum class StopReason : uint8_t {
        UNKNOWN_REASON,
        MOUSE_INTERRUPT,
        TOUCH_INTERRUPT,
        VELOCITY_THRESHOLD,
        POSITION_TARGET_REACHED,
        TOUCHPAD_OR_MOUSEWHEEL,
    };

    class FrictionAnimationHandler : public AceType {
        DECLARE_ACE_TYPE(FrictionAnimationHandler, AceType);

    public:
        explicit FrictionAnimationHandler(WeakPtr<CoastingAxisEventGenerator> generator);

        void StartFrictionAnimation();
        void StopFrictionAnimation(StopReason reason = StopReason::UNKNOWN_REASON);
        void UpdateAnimationFrame(float position);
        void ResetHandler();
        bool IsAnimationRunning() const
        {
            return phase_ != CoastingAxisPhase::NONE;
        }

    private:
        void CalculateFinalPosition();
        void DispatchCoastingAxisUpdateEvent(CoastingAxisPhase phase, float deltaX, float deltaY, uint64_t timestamp);
        void DispatchCoastingAxisEvent(CoastingAxisPhase phase, float deltaX, float deltaY, uint64_t timestamp);
        std::string GetStopReasonText(StopReason reason) const;

        WeakPtr<CoastingAxisEventGenerator> generator_;
        CoastingAxisPhase phase_ = CoastingAxisPhase::NONE;
        RefPtr<NG::NodeAnimatablePropertyFloat> frictionOffsetProperty_;
        double finalPosition_ = 0.0;
        double velocityRatioX_ = 0.0;
        double velocityRatioY_ = 0.0;
        uint64_t lastVsyncTime_ = 0;
        double lastPosition_ = 0.0;
    };

    void AxisTest(const AxisEvent& event, const RefPtr<NG::FrameNode>& node);
    double GetMainOffset(const Offset& offset) const;
    void HandleAxisBeginEvent(const AxisEvent& event);
    void HandleAxisUpdateEvent(const AxisEvent& event, bool end = false);
    void HandleAxisEndEvent(const AxisEvent& event, const RefPtr<NG::FrameNode>& node);
    void ResetState();

    AxisTestResult axisResult_;
    int32_t touchId_ = -1;
    AxisEvent lastAxisEvent_;
    VelocityTracker velocityTracker_;
    Axis axis_ = Axis::FREE;
    Offset axisDirection_;
    std::function<TouchEvent(const AxisEvent&)> axisToTouchConverter_;
    RefPtr<FrictionAnimationHandler> animationHandler_;
    double mainVelocity_ = 0.0;
    double originVelocity_ = 0.0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_COASTING_AXIS_EVENT_GENERATOR_H
