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

#include "core/event/coasting_axis_event_generator.h"

#include "ui/base/utils/utils.h"

#include "base/geometry/ng/point_t.h"
#include "core/common/container.h"
#include "core/components_ng/event/event_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
constexpr float VELOCITY_SCALE = 2.25f;
constexpr float FRICTION = 1.2f;
constexpr float FRICTION_SCALE = 4.2f;
constexpr double MAX_VELOCITY_VP = 9000.0;                         // 9000 vp/s
constexpr double START_FRICTION_VELOCITY_THRESHOLD = 240.0;        // 240 px/s
constexpr uint32_t COASTING_AXIS_SPRING_ANIMATION_DURATION = 1000; // 1000ms
constexpr float TOUCHPAD_STILL_THRESHOLD = 0.1;
constexpr uint32_t MAX_DIFF_VSYNC_TIME = 100 * 1000 * 1000; // max 100 ms
constexpr uint32_t MIN_DIFF_VSYNC_TIME = 1000 * 1000;       // min 1 ms
constexpr uint64_t NANOS_PER_SECOND = 1000 * 1000 * 1000;   // nanoseconds per second

CoastingAxisEventGenerator::CoastingAxisEventGenerator()
    : animationHandler_(MakeRefPtr<FrictionAnimationHandler>(AceType::WeakClaim(this)))
{}

CoastingAxisEventGenerator::FrictionAnimationHandler::FrictionAnimationHandler(
    WeakPtr<CoastingAxisEventGenerator> generator)
    : generator_(generator)
{
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float position) {
        auto generator = weak.Upgrade();
        CHECK_NULL_VOID(generator);
        generator->UpdateAnimationFrame(position);
    };

    frictionOffsetProperty_ = AceType::MakeRefPtr<NG::NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
}

void CoastingAxisEventGenerator::NotifyAxisEvent(const AxisEvent& event, const RefPtr<NG::FrameNode>& node)
{
    CHECK_NE_VOID(event.sourceType, SourceType::MOUSE);
    if (event.sourceTool == SourceTool::MOUSE) {
        CHECK_EQUAL_VOID(animationHandler_->IsAnimationRunning(), false);
        animationHandler_->StopFrictionAnimation(StopReason::MOUSE_INTERRUPT);
        return;
    }
    if (event.sourceTool == SourceTool::TOUCHPAD) {
        switch (event.action) {
            case AxisAction::BEGIN:
                HandleAxisBeginEvent(event);
                break;
            case AxisAction::UPDATE:
                HandleAxisUpdateEvent(event);
                break;
            case AxisAction::END:
                HandleAxisUpdateEvent(event, true);
                HandleAxisEndEvent(event, node);
                break;
            default:
                break;
        }
    }
}

void CoastingAxisEventGenerator::NotifyStop() const
{
    CHECK_NULL_VOID(animationHandler_);
    CHECK_EQUAL_VOID(animationHandler_->IsAnimationRunning(), false);
    animationHandler_->StopFrictionAnimation(StopReason::TOUCHPAD_OR_MOUSEWHEEL);
}

void CoastingAxisEventGenerator::NotifyTouchTestResult(const TouchTestResult& touchTestResult, const NG::PointF& point)
{
    CHECK_NULL_VOID(animationHandler_);
    CHECK_EQUAL_VOID(animationHandler_->IsAnimationRunning(), false);
    const auto matchIt =
        std::find_if(touchTestResult.begin(), touchTestResult.end(), [&axisResult = axisResult_](const auto& result) {
            return std::any_of(axisResult.begin(), axisResult.end(), [&result](const auto& axisTarget) {
                return axisTarget && axisTarget->GetFrameId() == result->GetNodeId();
            });
        });
    if (matchIt != touchTestResult.end() && *matchIt) {
        touchId_ = (*matchIt)->GetNodeId();
        LOGI("coasting axis match touchTestResult, touchId: %{public}d.", touchId_);
        return;
    }

    const auto hitIt = std::find_if(axisResult_.begin(), axisResult_.end(), [&point](const auto& axisTarget) {
        CHECK_NULL_RETURN(axisTarget, false);
        auto node = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(axisTarget->GetFrameId());
        CHECK_NULL_RETURN(node, false);
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
        return frameNode && frameNode->GetPaintRectWithTransform().IsInRegion(point);
    });

    touchId_ = (hitIt != axisResult_.end() && *hitIt) ? (*hitIt)->GetFrameId() : -1;
    LOGI("coasting axis match region, touchId: %{public}d.", touchId_);
}

void CoastingAxisEventGenerator::HandleAxisBeginEvent(const AxisEvent& event)
{
    lastAxisEvent_ = event;
    velocityTracker_.Reset();
    axisDirection_.Reset();
    axisDirection_ = Offset(event.horizontalAxis, event.verticalAxis);
    auto pseudoTouchEvent = TouchEvent();
    pseudoTouchEvent.time = event.time;
    auto revertAxisValue = event.ConvertToSummationAxisValue(lastAxisEvent_);
    pseudoTouchEvent.x = revertAxisValue.first;
    pseudoTouchEvent.y = revertAxisValue.second;
    pseudoTouchEvent.sourceTool = event.sourceTool;
    velocityTracker_.UpdateTouchPoint(pseudoTouchEvent, false, TOUCHPAD_STILL_THRESHOLD);
}

void CoastingAxisEventGenerator::HandleAxisUpdateEvent(const AxisEvent& event, bool end)
{
    auto pseudoTouchEvent = TouchEvent();
    pseudoTouchEvent.time = event.time;
    auto revertAxisValue = event.ConvertToSummationAxisValue(lastAxisEvent_);
    pseudoTouchEvent.x = revertAxisValue.first;
    pseudoTouchEvent.y = revertAxisValue.second;
    pseudoTouchEvent.sourceTool = event.sourceTool;
    velocityTracker_.UpdateTouchPoint(pseudoTouchEvent, end, TOUCHPAD_STILL_THRESHOLD);
    if (!end) {
        axisDirection_ = Offset(event.horizontalAxis, event.verticalAxis);
        lastAxisEvent_ = event;
        lastAxisEvent_.horizontalAxis = pseudoTouchEvent.x;
        lastAxisEvent_.verticalAxis = pseudoTouchEvent.y;
    }
}

void CoastingAxisEventGenerator::HandleAxisEndEvent(const AxisEvent& event, const RefPtr<NG::FrameNode>& node)
{
    axis_ = Axis::FREE;
    if (NearZero(lastAxisEvent_.horizontalAxis) && !NearZero(lastAxisEvent_.verticalAxis)) {
        axis_ = Axis::VERTICAL;
    } else if (NearZero(lastAxisEvent_.verticalAxis) && !NearZero(lastAxisEvent_.horizontalAxis)) {
        axis_ = Axis::HORIZONTAL;
    }

    velocityTracker_.SetMainAxis(axis_);
    auto mainVelocity = velocityTracker_.GetMainAxisVelocity();
    originVelocity_ = mainVelocity;
    auto density = PipelineBase::GetCurrentDensity();
    mainVelocity = VELOCITY_SCALE * mainVelocity;
    if (LessOrEqual(std::abs(mainVelocity), START_FRICTION_VELOCITY_THRESHOLD)) {
        LOGI("coasting axis velocity: %{public}f too small, do not start animation", mainVelocity);
        ResetState();
        return;
    }

    auto maxVelocity = MAX_VELOCITY_VP * density;
    mainVelocity_ = std::clamp(mainVelocity, -maxVelocity, maxVelocity);
    AxisTest(event, node);
}

void CoastingAxisEventGenerator::AxisTest(const AxisEvent& event, const RefPtr<NG::FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(axisToTouchConverter_);
    CHECK_NULL_VOID(animationHandler_);
    const NG::PointF point { event.x, event.y };
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = event.sourceType;
    touchRestrict.hitTestType = SourceType::MOUSE;
    touchRestrict.inputEventType = InputEventType::AXIS;
    touchRestrict.touchEvent = axisToTouchConverter_(event);
    touchRestrict.isCoastingAxisEvent = true;
    node->AxisTest(point, point, point, touchRestrict, axisResult_);
    if (axisResult_.empty()) {
        LOGI("coasting axis no target to handle axis event");
        ResetState();
        return;
    }
    animationHandler_->StartFrictionAnimation();
}

void CoastingAxisEventGenerator::ResetState()
{
    velocityTracker_.Reset();
    lastAxisEvent_ = AxisEvent();
    mainVelocity_ = 0;
    originVelocity_ = 0;
    axis_ = Axis::FREE;
    axisResult_.clear();
    touchId_ = -1;
    axisDirection_.Reset();
}

double CoastingAxisEventGenerator::GetMainOffset(const Offset& offset) const
{
    switch (axis_) {
        case Axis::FREE:
            return std::sqrt((offset.GetX() * offset.GetX()) + (offset.GetY() * offset.GetY()));
        case Axis::HORIZONTAL:
            return offset.GetX();
        case Axis::VERTICAL:
            return offset.GetY();
        default:
            return 0.0;
    }
}

void CoastingAxisEventGenerator::FrictionAnimationHandler::DispatchCoastingAxisUpdateEvent(
    CoastingAxisPhase phase, float deltaX, float deltaY, uint64_t timestamp)
{
    auto generator = generator_.Upgrade();
    CHECK_NULL_VOID(generator);
    CHECK_NE_VOID(phase, CoastingAxisPhase::UPDATE);
    auto touchId = generator->touchId_;
    generator->touchId_ = -1;
    auto it = generator->axisResult_.begin();
    while (it != generator->axisResult_.end() && !*it) {
        it = generator->axisResult_.erase(it);
    }
    if (it != generator->axisResult_.end() && (*it)->GetFrameId() == touchId) {
        StopFrictionAnimation(StopReason::TOUCH_INTERRUPT);
        return;
    }
    auto touchIt = generator->axisResult_.end();
    for (auto it = generator->axisResult_.begin(); it != generator->axisResult_.end(); ++it) {
        if ((*it) && (*it)->GetFrameId() == touchId) {
            touchIt = it;
            break;
        }
    }
    if (touchIt == generator->axisResult_.end()) {
        DispatchCoastingAxisEvent(phase, deltaX, deltaY, timestamp);
        return;
    }
    CoastingAxisInfo info;
    info.SetPhase(phase);
    info.SetHorizontalAxis(deltaX);
    info.SetVerticalAxis(deltaY);
    info.SetTimeStamp(TimeStamp(std::chrono::nanoseconds(timestamp)));
    info.SetStopPropagation(true);
    for (auto it = generator->axisResult_.begin(); it != touchIt; ++it) {
        if ((*it) && (*it)->HandleCoastingAxisEvent(info)) {
            generator->axisResult_.erase(touchIt, generator->axisResult_.end());
            return;
        }
    }
    CoastingAxisInfo endInfo;
    endInfo.SetPhase(CoastingAxisPhase::END);
    endInfo.SetHorizontalAxis(0);
    endInfo.SetVerticalAxis(0);
    endInfo.SetTimeStamp(TimeStamp(std::chrono::nanoseconds(timestamp)));
    endInfo.SetStopPropagation(true);
    for (auto it = touchIt; it != generator->axisResult_.end(); ++it) {
        if ((*it) && (*it)->HandleCoastingAxisEvent(endInfo)) {
            generator->axisResult_.erase(touchIt, generator->axisResult_.end());
            return;
        }
    }
}

void CoastingAxisEventGenerator::FrictionAnimationHandler::DispatchCoastingAxisEvent(
    CoastingAxisPhase phase, float deltaX, float deltaY, uint64_t timestamp)
{
    auto generator = generator_.Upgrade();
    CHECK_NULL_VOID(generator);
    CoastingAxisInfo info;
    info.SetPhase(phase);
    info.SetHorizontalAxis(deltaX);
    info.SetVerticalAxis(deltaY);
    info.SetTimeStamp(TimeStamp(std::chrono::nanoseconds(timestamp)));
    info.SetStopPropagation(true);

    for (const auto& axisTarget : generator->axisResult_) {
        if (axisTarget && axisTarget->HandleCoastingAxisEvent(info)) {
            return;
        }
    }
}

void CoastingAxisEventGenerator::FrictionAnimationHandler::StartFrictionAnimation()
{
    auto generator = generator_.Upgrade();
    CHECK_NULL_VOID(generator);
    CHECK_NULL_VOID(frictionOffsetProperty_);
    CHECK_EQUAL_VOID(generator->axisResult_.empty(), true);

    CalculateFinalPosition();
    auto axisEventTarget = generator->axisResult_.front();
    CHECK_NULL_VOID(axisEventTarget);
    auto node = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(axisEventTarget->GetFrameId());
    CHECK_NULL_VOID(node);
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->AttachNodeAnimatableProperty(frictionOffsetProperty_);

    double startPosition =
        Round(generator->GetMainOffset(Offset(generator->lastAxisEvent_.x, generator->lastAxisEvent_.y)));
    lastPosition_ = startPosition;
    frictionOffsetProperty_->Set(startPosition);

    float response = fabs(2 * ACE_PI / (FRICTION_SCALE * FRICTION));
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(response, 1.0f, 0.0f);
    AnimationOption option;
    option.SetCurve(curve);
    option.SetDuration(COASTING_AXIS_SPRING_ANIMATION_DURATION);
    option.SetFinishCallbackType(FinishCallbackType::LOGICALLY);
    frictionOffsetProperty_->SetThresholdType(ThresholdType::LAYOUT);
    frictionOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    finalPosition_ = finalPosition_ + startPosition;
    LOGI("coasting axis start animation, velocity:%{public}f, startPosition:%{public}f, finalPosition:%{public}f",
        generator->mainVelocity_, startPosition, finalPosition_);
    frictionOffsetProperty_->AnimateWithVelocity(option, finalPosition_, generator->mainVelocity_, nullptr);
    phase_ = CoastingAxisPhase::BEGIN;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    context->RequestFrame();
    lastVsyncTime_ = context->GetVsyncTime();
}

void CoastingAxisEventGenerator::FrictionAnimationHandler::StopFrictionAnimation(StopReason reason)
{
    CHECK_EQUAL_VOID(phase_, CoastingAxisPhase::NONE);
    auto generator = generator_.Upgrade();
    CHECK_NULL_VOID(generator);
    LOGI("coasting axis stop animation, reason:%{public}s", GetStopReasonText(reason).c_str());

    uint64_t currentVsync = static_cast<uint64_t>(GetSysTimestamp());
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    if (context) {
        currentVsync = context->GetVsyncTime();
    }
    if (phase_ == CoastingAxisPhase::BEGIN) {
        DispatchCoastingAxisEvent(CoastingAxisPhase::BEGIN, 0.0f, 0.0f, currentVsync);
    }
    phase_ = CoastingAxisPhase::NONE;
    DispatchCoastingAxisEvent(CoastingAxisPhase::END, 0.0f, 0.0f, currentVsync);
    generator->ResetState();
    ResetHandler();
    CHECK_NULL_VOID(frictionOffsetProperty_);
    AnimationOption option;
    option.SetCurve(Curves::EASE);
    option.SetDuration(0);
    AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this)] {
            auto handler = weak.Upgrade();
            CHECK_NULL_VOID(handler);
            handler->frictionOffsetProperty_->Set(handler->lastPosition_);
        },
        nullptr);
}

void CoastingAxisEventGenerator::FrictionAnimationHandler::UpdateAnimationFrame(float position)
{
    auto generator = generator_.Upgrade();
    CHECK_NULL_VOID(generator);
    CHECK_EQUAL_VOID(phase_, CoastingAxisPhase::NONE);

    if (NearEqual(finalPosition_, position, 1.0)) {
        StopFrictionAnimation(StopReason::POSITION_TARGET_REACHED);
        return;
    }
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    uint64_t currentVsync = context->GetVsyncTime();
    uint64_t diff = currentVsync - lastVsyncTime_;

    if (diff < MAX_DIFF_VSYNC_TIME && diff > MIN_DIFF_VSYNC_TIME) {
        auto delta = std::abs(position - lastPosition_);
        generator->mainVelocity_ = delta / diff * NANOS_PER_SECOND;
        auto deltaX = delta * velocityRatioX_;
        auto deltaY = delta * velocityRatioY_;
        if (NearZero(generator->mainVelocity_, START_FRICTION_VELOCITY_THRESHOLD)) {
            StopFrictionAnimation(StopReason::VELOCITY_THRESHOLD);
        } else {
            if (phase_ == CoastingAxisPhase::BEGIN) {
                DispatchCoastingAxisEvent(phase_, static_cast<float>(deltaX), static_cast<float>(deltaY), currentVsync);
                phase_ = CoastingAxisPhase::UPDATE;
            } else {
                DispatchCoastingAxisUpdateEvent(
                    phase_, static_cast<float>(deltaX), static_cast<float>(deltaY), currentVsync);
            }
        }
    }

    lastVsyncTime_ = currentVsync;
    lastPosition_ = position;
}

void CoastingAxisEventGenerator::FrictionAnimationHandler::ResetHandler()
{
    phase_ = CoastingAxisPhase::NONE;
    finalPosition_ = 0.0;
    velocityRatioX_ = 0.0;
    velocityRatioY_ = 0.0;
    lastVsyncTime_ = 0;
    lastPosition_ = 0.0;
}

void CoastingAxisEventGenerator::FrictionAnimationHandler::CalculateFinalPosition()
{
    auto generator = generator_.Upgrade();
    CHECK_NULL_VOID(generator);

    finalPosition_ = generator->mainVelocity_ / (FRICTION * FRICTION_SCALE);

    if (NearZero(generator->originVelocity_)) {
        velocityRatioX_ = 0.0;
        velocityRatioY_ = 0.0;
    } else {
        auto velocity = generator->velocityTracker_.GetVelocity();
        double rawVelocityX = velocity.GetVelocityX();
        double rawVelocityY = velocity.GetVelocityY();
        velocityRatioX_ = GreatOrEqual(generator->axisDirection_.GetX(), 0)
                              ? abs(rawVelocityX / generator->originVelocity_)
                              : -abs(rawVelocityX / generator->originVelocity_);
        velocityRatioY_ = GreatOrEqual(generator->axisDirection_.GetY(), 0)
                              ? abs(rawVelocityY / generator->originVelocity_)
                              : -abs(rawVelocityY / generator->originVelocity_);
    }
}

std::string CoastingAxisEventGenerator::FrictionAnimationHandler::GetStopReasonText(StopReason reason) const
{
    switch (reason) {
        case StopReason::MOUSE_INTERRUPT:
            return "interrupted by mouse event";
        case StopReason::TOUCH_INTERRUPT:
            return "interrupted by touch event";
        case StopReason::VELOCITY_THRESHOLD:
            return "velocity below threshold";
        case StopReason::POSITION_TARGET_REACHED:
            return "target position reached";
        case StopReason::TOUCHPAD_OR_MOUSEWHEEL:
            return "touchpad interaction begin or mouse wheel scroll";
        default:
            return "unknown reason";
    }
}
} // namespace OHOS::Ace
