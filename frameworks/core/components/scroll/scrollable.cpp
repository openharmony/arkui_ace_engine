/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/scroll/scrollable.h"

#include <chrono>

#include "base/log/ace_trace.h"
#include "base/log/frame_report.h"
#include "base/log/jank_frame_report.h"
#include "base/log/log.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/event/ace_events.h"
#include "core/common/layout_inspector.h"

namespace OHOS::Ace {
namespace {

constexpr double SPRING_SCROLL_MASS = 0.5;
constexpr double SPRING_SCROLL_STIFFNESS = 100.0;
constexpr double SPRING_SCROLL_DAMPING = 15.55635;
constexpr double CAP_COEFFICIENT = 0.45;
constexpr int32_t FIRST_THRESHOLD = 5;
constexpr int32_t SECOND_THRESHOLD = 10;
constexpr double CAP_FIXED_VALUE = 16.0;
constexpr uint32_t DRAG_INTERVAL_TIME = 900;
const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
    AceType::MakeRefPtr<SpringProperty>(SPRING_SCROLL_MASS, SPRING_SCROLL_STIFFNESS, SPRING_SCROLL_DAMPING);
constexpr float SNAP_SCROLL_MASS = 1.0f;
constexpr float SNAP_SCROLL_STIFFNESS = 288.0f;
constexpr float SNAP_SCROLL_DAMPING = 30.0f;
const RefPtr<SpringProperty> SNAP_SCROLL_PROPERTY =
    AceType::MakeRefPtr<SpringProperty>(SNAP_SCROLL_MASS, SNAP_SCROLL_STIFFNESS, SNAP_SCROLL_DAMPING);
#ifndef WEARABLE_PRODUCT
constexpr double FRICTION = 0.6;
constexpr double VELOCITY_SCALE = 1.0;
constexpr double MAX_VELOCITY = 800000.0;
constexpr double MIN_VELOCITY = -800000.0;
constexpr double ADJUSTABLE_VELOCITY = 3000.0;
#else
constexpr double DISTANCE_EPSILON = 1.0;
constexpr double FRICTION = 0.9;
constexpr double VELOCITY_SCALE = 0.8;
constexpr double MAX_VELOCITY = 5000.0;
constexpr double MIN_VELOCITY = -5000.0;
constexpr double ADJUSTABLE_VELOCITY = 0.0;
#endif

#ifdef OHOS_PLATFORM
constexpr int64_t INCREASE_CPU_TIME_ONCE = 4000000000; // 4s(unit: ns)
#endif

} // namespace

// Static Functions.
double Scrollable::sFriction_ = FRICTION;
double Scrollable::sVelocityScale_ = VELOCITY_SCALE;

void Scrollable::SetVelocityScale(double sVelocityScale)
{
    if (LessOrEqual(sVelocityScale, 0.0)) {
        LOGW("Invalid velocity scale: %{public}lf", sVelocityScale);
        return;
    }
    sVelocityScale_ = sVelocityScale;
}

void Scrollable::SetFriction(double sFriction)
{
    if (LessOrEqual(sFriction, 0.0)) {
        LOGW("Invalid friction value: %{public}lf", sFriction);
        return;
    }
    sFriction_ = sFriction;
}

Scrollable::~Scrollable()
{
    // If animation still runs, force stop it.
    controller_->Stop();
    springController_->Stop();
    scrollSnapController_->Stop();
}

void Scrollable::OnFlushTouchEventsBegin()
{
    if (panRecognizer_) {
        panRecognizer_->OnFlushTouchEventsBegin();
    }
}

void Scrollable::OnFlushTouchEventsEnd()
{
    if (panRecognizer_) {
        panRecognizer_->OnFlushTouchEventsEnd();
    }
}

void Scrollable::Initialize(const WeakPtr<PipelineBase>& context)
{
    context_ = context;
    PanDirection panDirection;
    if (axis_ == Axis::VERTICAL) {
        panDirection.type = PanDirection::VERTICAL;
    } else {
        panDirection.type = PanDirection::HORIZONTAL;
    }

    auto actionStart = [weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
                return;
            }
            // Send event to accessibility when scroll start.
            auto context = scroll->GetContext().Upgrade();
            if (context) {
                AccessibilityEvent scrollEvent;
                scrollEvent.nodeId = scroll->nodeId_;
                scrollEvent.eventType = "scrollstart";
                context->SendEventToAccessibility(scrollEvent);
            }
            scroll->HandleDragStart(info);
        }
    };

    auto actionUpdate = [weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
                return;
            }
            scroll->HandleDragUpdate(info);
        }
    };

    auto actionEnd = [weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
                return;
            }
            scroll->HandleDragEnd(info);
            // Send event to accessibility when scroll stop.
            auto context = scroll->GetContext().Upgrade();
            if (context && scroll->IsStopped()) {
                AccessibilityEvent scrollEvent;
                scrollEvent.nodeId = scroll->nodeId_;
                scrollEvent.eventType = "scrollend";
                context->SendEventToAccessibility(scrollEvent);
            }
        }
    };

    auto actionCancel = [weakScroll = AceType::WeakClaim(this)]() {
        auto scroll = weakScroll.Upgrade();
        if (!scroll) {
            return;
        }
        if (scroll->dragCancelCallback_) {
            scroll->dragCancelCallback_();
        }
    };

    if (Container::IsCurrentUseNewPipeline()) {
        const static int32_t PLATFORM_VERSION_TEN = 10;
        float distance = DEFAULT_PAN_DISTANCE;
        auto context = context_.Upgrade();
        if (context && (context->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN)) {
            distance = static_cast<float>(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP).ConvertToPx());
        }
        panRecognizerNG_ = AceType::MakeRefPtr<NG::PanRecognizer>(DEFAULT_PAN_FINGER, panDirection, distance);

        panRecognizerNG_->SetOnActionStart(actionStart);
        panRecognizerNG_->SetOnActionUpdate(actionUpdate);
        panRecognizerNG_->SetOnActionEnd(actionEnd);
        panRecognizerNG_->SetOnActionCancel(actionCancel);
    } else {
        panRecognizer_ =
            AceType::MakeRefPtr<PanRecognizer>(context, DEFAULT_PAN_FINGER, panDirection, DEFAULT_PAN_DISTANCE);
        panRecognizer_->SetOnActionStart(actionStart);
        panRecognizer_->SetOnActionUpdate(actionUpdate);
        panRecognizer_->SetOnActionEnd(actionEnd);
        panRecognizer_->SetOnActionCancel(actionCancel);
    }

    // use RawRecognizer to receive next touch down event to stop animation.
    rawRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();

    rawRecognizer_->SetOnTouchDown([weakScroll = AceType::WeakClaim(this)](const TouchEventInfo&) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->HandleTouchDown();
        }
    });
    rawRecognizer_->SetOnTouchUp([weakScroll = AceType::WeakClaim(this)](const TouchEventInfo&) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->HandleTouchUp();
        }
    });
    rawRecognizer_->SetOnTouchCancel([weakScroll = AceType::WeakClaim(this)](const TouchEventInfo&) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->HandleTouchCancel();
        }
    });

    controller_ = CREATE_ANIMATOR(context);
    springController_ = CREATE_ANIMATOR(context);
    scrollSnapController_ = CREATE_ANIMATOR(context);
    snapController_ = CREATE_ANIMATOR(context);
    snapController_->AddStopListener([weakScroll = AceType::WeakClaim(this)]() {
        auto scroll = weakScroll.Upgrade();
        CHECK_NULL_VOID_NOLOG(scroll);
        scroll->ProcessScrollMotionStop();
        // Send event to accessibility when scroll stop.
        auto context = scroll->GetContext().Upgrade();
        CHECK_NULL_VOID_NOLOG(context && scroll->Idle());
        AccessibilityEvent scrollEvent;
        scrollEvent.nodeId = scroll->nodeId_;
        scrollEvent.eventType = "scrollend";
        context->SendEventToAccessibility(scrollEvent);
    });

    spring_ = GetDefaultOverSpringProperty();
    available_ = true;
}

void Scrollable::SetAxis(Axis axis)
{
    axis_ = axis;
    PanDirection panDirection;
    if (axis_ == Axis::VERTICAL) {
        panDirection.type = PanDirection::VERTICAL;
    } else {
        panDirection.type = PanDirection::HORIZONTAL;
    }
    if (panRecognizer_) {
        panRecognizer_->SetDirection(panDirection);
    }
    if (panRecognizerNG_) {
        panRecognizerNG_->SetDirection(panDirection);
    }
}

void Scrollable::HandleTouchDown()
{
    LOGD("handle touch down");
    isTouching_ = true;
    // If animation still runs, first stop it.
    springController_->Stop();
    if (!controller_->IsStopped()) {
        controller_->Stop();
    } else if (snapController_->IsRunning()) {
        snapController_->Stop();
    } else {
        // Resets values.
        currentPos_ = 0.0;
    }
    if (!scrollSnapController_->IsStopped()) {
        scrollSnapController_->Stop();
    }
    LOGD("handle touch down has already stopped the animation");
}

void Scrollable::HandleTouchUp()
{
    LOGD("handle touch up");
    isTouching_ = false;
    if (outBoundaryCallback_ && !outBoundaryCallback_()) {
        if (scrollSnapController_->IsStopped() && scrollSnapCallback_) {
            scrollSnapCallback_(0.0, 0.0);
        }
        return;
    }
    if (springController_->IsStopped() && scrollOverCallback_) {
        LOGD("need scroll to boundary");
        ProcessScrollOverCallback(0.0);
    }
}

void Scrollable::HandleTouchCancel()
{
    LOGD("handle touch cancel");
    isTouching_ = false;
    if (springController_->IsStopped() && scrollOverCallback_) {
        ProcessScrollOverCallback(0.0);
    }
}

bool Scrollable::IsAnimationNotRunning() const
{
    return !isTouching_ && !controller_->IsRunning() && !springController_->IsRunning() &&
        !scrollSnapController_->IsRunning();
}

bool Scrollable::Idle() const
{
    return !isTouching_ && (controller_->IsStopped() || controller_->GetStatus() == Animator::Status::IDLE) &&
        (springController_->IsStopped() || springController_->GetStatus() == Animator::Status::IDLE) &&
        (scrollSnapController_->IsStopped() || scrollSnapController_->GetStatus() == Animator::Status::IDLE) &&
        (snapController_->IsStopped() || snapController_->GetStatus() == Animator::Status::IDLE);
}

bool Scrollable::IsStopped() const
{
    return (!springController_ || (springController_->IsStopped()) ||
               (springController_->GetStatus() == Animator::Status::IDLE)) &&
           (!controller_ || (controller_->IsStopped()) || (controller_->GetStatus() == Animator::Status::IDLE)) &&
           (!scrollSnapController_ || (scrollSnapController_->IsStopped()) ||
               (scrollSnapController_->GetStatus() == Animator::Status::IDLE)) &&
           (!snapController_ || (snapController_->IsStopped()) ||
               (snapController_->GetStatus() == Animator::Status::IDLE));
}

bool Scrollable::IsSpringStopped() const
{
    return !springController_ || (springController_->IsStopped());
}

bool Scrollable::IsSnapStopped() const
{
    return !snapController_ || (snapController_->IsStopped()) ||
           (snapController_->GetStatus() == Animator::Status::IDLE);
}

void Scrollable::StopScrollable()
{
    if (controller_) {
        controller_->Stop();
    }
    if (springController_) {
        springController_->Stop();
    }
    if (scrollSnapController_) {
        scrollSnapController_->Stop();
    }
    if (snapController_) {
        snapController_->Stop();
    }
}

void Scrollable::HandleScrollEnd()
{
    if (scrollEndCallback_) {
        scrollEndCallback_();
    }
    auto parent = parent_.Upgrade();
    if (parent && nestedOpt_.NeedParent()) {
        parent->HandleScrollEnd();
    }
}

void Scrollable::HandleDragStart(const OHOS::Ace::GestureEvent& info)
{
    ACE_FUNCTION_TRACE();
    if (continuousDragStatus_) {
        IncreaseContinueDragCount();
        task_.Cancel();
    }
    SetDragStartPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    const auto dragPositionInMainAxis =
        axis_ == Axis::VERTICAL ? info.GetGlobalLocation().GetY() : info.GetGlobalLocation().GetX();
    LOGD("HandleDragStart. LocalLocation: %{public}s, GlobalLocation: %{public}s",
        info.GetLocalLocation().ToString().c_str(), info.GetGlobalLocation().ToString().c_str());
#ifdef OHOS_PLATFORM
    // Increase the cpu frequency when sliding start.
    auto currentTime = GetSysTimestamp();
    auto increaseCpuTime = currentTime - startIncreaseTime_;
    if (!moved_ || increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
        LOGI("HandleDragStart increase cpu frequency, moved_ = %{public}d", moved_);
        startIncreaseTime_ = currentTime;
        ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().BeginListFling();
        }
    }
#endif
    JankFrameReport::SetFrameJankFlag(JANK_RUNNING_SCROLL);
    UpdateScrollPosition(dragPositionInMainAxis, SCROLL_FROM_START);
    auto parent = parent_.Upgrade();
    if (parent && nestedOpt_.NeedParent()) {
        parent->UpdateScrollPosition(dragPositionInMainAxis, SCROLL_FROM_START);
    }
    RelatedEventStart();
    auto node = scrollableNode_.Upgrade();
    if (node) {
        node->DispatchCancelPressAnimation();
    }
}

ScrollResult Scrollable::HandleScrollParentFirst(double& offset, int32_t source, NestedState state)
{
    auto parent = parent_.Upgrade();
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_OVER_SCROLL) {
        if (edgeEffect_ == EdgeEffect::NONE) {
            return parent->HandleScroll(offset, source, NestedState::CHILD_OVER_SCROLL);
        }
        ExecuteScrollFrameBegin(offset, scrollState);
        return { 0, true };
    }
    auto result = parent->HandleScroll(offset, source, NestedState::CHILD_SCROLL);
    offset = result.remain;
    if (NearZero(offset)) {
        canOverScroll_ = false;
        return { 0, false };
    }
    double allOffset = offset;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto remainOffset = std::abs(offset) < std::abs(allOffset) ? allOffset - offset : 0;
    auto overOffsets = overScrollOffsetCallback_(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    remainOffset += overOffset;
    if (NearZero(remainOffset)) {
        canOverScroll_ = false;
        return { 0, false };
    }
    if (state == NestedState::CHILD_SCROLL) {
        offset -= overOffset;
        canOverScroll_ = false;
        return { remainOffset, !NearZero(overOffset) };
    }
    if (edgeEffect_ == EdgeEffect::NONE) {
        result = parent->HandleScroll(remainOffset, source, NestedState::CHILD_OVER_SCROLL);
    }
    canOverScroll_ = !NearZero(overOffset) || (NearZero(offset) && result.reachEdge);
    return { 0, canOverScroll_ };
}

ScrollResult Scrollable::HandleScrollSelfFirst(double& offset, int32_t source, NestedState state)
{
    auto parent = parent_.Upgrade();
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_OVER_SCROLL) {
        auto result = parent->HandleScroll(offset, source, NestedState::CHILD_OVER_SCROLL);
        if (NearZero(result.remain)) {
            offset = 0;
            return result;
        }
        ExecuteScrollFrameBegin(offset, scrollState);
        if (edgeEffect_ == EdgeEffect::NONE) {
            return result;
        }
        return { 0, true };
    }
    double allOffset = offset;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto remainOffset = std::abs(offset) < std::abs(allOffset) ? allOffset - offset : 0;
    auto overOffsets = overScrollOffsetCallback_(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    if (NearZero(overOffset) && NearZero(remainOffset)) {
        canOverScroll_ = false;
        return { 0, false };
    }
    offset -= overOffset;
    auto result = parent->HandleScroll(overOffset + remainOffset, source, NestedState::CHILD_SCROLL);
    if (NearZero(result.remain)) {
        canOverScroll_ = false;
        return { 0, false };
    }
    if (state == NestedState::CHILD_SCROLL) {
        canOverScroll_ = false;
        return result;
    }
    auto overRes = parent->HandleScroll(result.remain, source, NestedState::CHILD_OVER_SCROLL);
    offset += std::abs(overOffset) < std::abs(result.remain) ? overOffset : overRes.remain;
    canOverScroll_ = (!NearZero(overOffset) || NearZero(offset)) && overRes.reachEdge;
    return { 0, canOverScroll_ };
}

ScrollResult Scrollable::HandleScrollSelfOnly(double& offset, int32_t source, NestedState state)
{
    double allOffset = offset;
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto remainOffset = allOffset - offset;
    auto overOffsets = overScrollOffsetCallback_(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    remainOffset += overOffset;
    if (NearZero(remainOffset)) {
        canOverScroll_ = false;
        return { 0, false };
    }
    bool canOverScroll = false;
    if (state == NestedState::CHILD_SCROLL) {
        offset -= overOffset;
    } else if (state == NestedState::GESTURE) {
        canOverScroll = !NearZero(overOffset) && edgeEffect_ != EdgeEffect::NONE;
    } else if (edgeEffect_ != EdgeEffect::NONE) {
        remainOffset = 0;
    }
    canOverScroll_ = canOverScroll;
    return { remainOffset, !NearZero(overOffset) };
}

ScrollResult Scrollable::HandleScrollParallel(double& offset, int32_t source, NestedState state)
{
    auto remainOffset = 0.0;
    auto parent = parent_.Upgrade();
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_OVER_SCROLL) {
        if (edgeEffect_ == EdgeEffect::NONE) {
            auto result = parent->HandleScroll(offset, source, NestedState::CHILD_OVER_SCROLL);
            remainOffset = result.remain;
            offset = 0;
        } else {
            ExecuteScrollFrameBegin(offset, scrollState);
        }
        return { remainOffset, true };
    }

    bool canOverScroll = false;
    double parentOffset = offset;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto result = parent->HandleScroll(parentOffset, source, NestedState::CHILD_SCROLL);

    auto overOffsets = overScrollOffsetCallback_(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    if (!NearZero(overOffset) && result.reachEdge) {
        if (state == NestedState::CHILD_SCROLL) {
            remainOffset = overOffset;
            offset = offset - overOffset;
        } else if (edgeEffect_ == EdgeEffect::NONE) {
            parent->HandleScroll(result.remain, source, NestedState::CHILD_OVER_SCROLL);
            canOverScroll = true;
            offset = offset - overOffset;
        } else {
            canOverScroll = true;
        }
    } else if (!NearZero(overOffset)) {
        offset = offset - overOffset;
    }
    canOverScroll_ = canOverScroll;
    return { remainOffset, !NearZero(overOffset) && result.reachEdge };
}

ScrollResult Scrollable::HandleScroll(double offset, int32_t source, NestedState state)
{
    if (!overScrollOffsetCallback_) {
        ExecuteScrollBegin(offset);
        ExecuteScrollFrameBegin(offset, ScrollState::SCROLL);
        moved_ = UpdateScrollPosition(offset, source);
        canOverScroll_ = false;
        return { 0, false };
    }
    ScrollResult result = { 0, false };
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    auto parent = parent_.Upgrade();
    auto overOffsets = overScrollOffsetCallback_(offset);
    double backOverOffset = offset > 0 ? overOffsets.end : overOffsets.start;
    if (NearZero(offset) || !NearZero(backOverOffset)) {
        ExecuteScrollFrameBegin(offset, scrollState);
    } else if (parent && ((offset < 0 && nestedOpt_.forward == NestedScrollMode::PARENT_FIRST) ||
        (offset > 0 && nestedOpt_.backward == NestedScrollMode::PARENT_FIRST))) {
        result = HandleScrollParentFirst(offset, source, state);
    } else if (parent && ((offset < 0 && nestedOpt_.forward == NestedScrollMode::SELF_FIRST) ||
        (offset > 0 && nestedOpt_.backward == NestedScrollMode::SELF_FIRST))) {
        result = HandleScrollSelfFirst(offset, source, state);
    } else if (parent && ((offset < 0 && nestedOpt_.forward == NestedScrollMode::PARALLEL) ||
        (offset > 0 && nestedOpt_.backward == NestedScrollMode::PARALLEL))) {
        result = HandleScrollParallel(offset, source, state);
    } else {
        result = HandleScrollSelfOnly(offset, source, state);
    }
    moved_ = UpdateScrollPosition(offset, source);
    return result;
}

void Scrollable::HandleDragUpdate(const GestureEvent& info)
{
    ACE_FUNCTION_TRACE();
    if (!NearZero(info.GetMainVelocity()) && dragCount_ >= FIRST_THRESHOLD) {
        if (Negative(lastVelocity_ / info.GetMainVelocity())) {
            ResetContinueDragCount();
        }
    }
    if (!springController_->IsStopped() || !controller_->IsStopped() || !scrollSnapController_->IsStopped() ||
        !snapController_->IsStopped()) {
        // If animation still runs, first stop it.
        isDragUpdateStop_ = true;
        controller_->Stop();
        springController_->Stop();
        scrollSnapController_->Stop();
        snapController_->Stop();
        currentPos_ = 0.0;
    }
#ifdef OHOS_PLATFORM
    // Handle the case where you keep sliding past limit time(4s).
    auto currentTime = GetSysTimestamp();
    auto increaseCpuTime = currentTime - startIncreaseTime_;
    if (increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
        LOGI("HandleDragUpdate increase cpu frequency, moved_ = %{public}d", moved_);
        startIncreaseTime_ = currentTime;
        ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().BeginListFling();
        }
    }
#endif
    LOGD("handle drag update, offset is %{public}lf", info.GetMainDelta());
    auto mainDelta = info.GetMainDelta();
    if (RelatedScrollEventPrepare(Offset(0.0, mainDelta))) {
        return;
    }
    auto source = info.GetInputEventType() == InputEventType::AXIS ? SCROLL_FROM_AXIS : SCROLL_FROM_UPDATE;
    HandleScroll(mainDelta, source, NestedState::GESTURE);
}

void Scrollable::HandleDragEnd(const GestureEvent& info)
{
    LOGD("handle drag end, position is %{public}lf and %{public}lf, velocity is %{public}lf",
        info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY(), info.GetMainVelocity());
    controller_->ClearAllListeners();
    springController_->ClearAllListeners();
    scrollSnapController_->ClearAllListeners();
    isDragUpdateStop_ = false;
    touchUp_ = false;
    scrollPause_ = false;
    lastVelocity_ = info.GetMainVelocity();
    double correctVelocity = std::clamp(info.GetMainVelocity(), MIN_VELOCITY + slipFactor_, MAX_VELOCITY - slipFactor_);
    SetDragEndPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    correctVelocity = correctVelocity * sVelocityScale_ * GetGain(GetDragOffset());
    currentVelocity_ = correctVelocity;
    std::optional<float> predictSnapOffset;
    lastPos_ = GetDragOffset();
    JankFrameReport::ClearFrameJankFlag(JANK_RUNNING_SCROLL);
    if (dragEndCallback_) {
        dragEndCallback_();
    }
    RelatedEventEnd();
    double mainPosition = GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY()));
    if (!moved_ || info.GetInputEventType() == InputEventType::AXIS) {
        LOGI("It is not moved now,  no need to handle drag end motion");
        if (calePredictSnapOffsetCallback_) {
            predictSnapOffset = calePredictSnapOffsetCallback_(0.0f);
            if (predictSnapOffset.has_value() && !NearZero(predictSnapOffset.value())) {
                currentPos_ = mainPosition;
                ProcessScrollSnapSpringMotion(predictSnapOffset.value(), correctVelocity);
                return;
            }
        }
        HandleScrollEnd();
        currentVelocity_ = 0.0;
#ifdef OHOS_PLATFORM
        LOGI("springController stop increase cpu frequency");
        ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndListFling();
        }
#endif
    } else if (!overScrollOffsetCallback_ && outBoundaryCallback_ && outBoundaryCallback_() && scrollOverCallback_) {
        ProcessScrollOverCallback(correctVelocity);
    } else if (canOverScroll_) {
        HandleOverScroll(correctVelocity);
    } else {
        if (springController_ && !springController_->IsStopped()) {
            springController_->Stop();
        }
        StopSnapController();
        LOGD("[scrollMotion]position(%{public}lf), velocity(%{public}lf)", mainPosition, correctVelocity);
        double friction = friction_ > 0 ? friction_ : sFriction_;
        if (motion_) {
            motion_->Reset(friction, mainPosition, correctVelocity);
        } else {
            motion_ = AceType::MakeRefPtr<FrictionMotion>(friction, mainPosition, correctVelocity);
            motion_->AddListener([weakScroll = AceType::WeakClaim(this)](double value) {
                auto scroll = weakScroll.Upgrade();
                if (scroll) {
                    scroll->ProcessScrollMotion(value);
                }
            });
        }
        if (calePredictSnapOffsetCallback_) {
            predictSnapOffset = calePredictSnapOffsetCallback_(motion_->GetFinalPosition() - mainPosition);
            if (predictSnapOffset.has_value() && !NearZero(predictSnapOffset.value())) {
                currentPos_ = mainPosition;
                ProcessScrollSnapSpringMotion(predictSnapOffset.value(), correctVelocity);
                return;
            }
        }

        if (scrollSnapCallback_ &&
            scrollSnapCallback_(motion_->GetFinalPosition() - mainPosition, correctVelocity)) {
            currentVelocity_ = 0.0;
            return;
        }

        // change motion param when list item need to be center of screen on watch
        FixScrollMotion(mainPosition);

        // Resets values.
        currentPos_ = mainPosition;
        currentVelocity_ = 0.0;

        // Starts motion.
        controller_->ClearStopListeners();
        controller_->AddStopListener([weak = AceType::WeakClaim(this)]() {
            auto scroll = weak.Upgrade();
            if (scroll) {
                scroll->ProcessScrollMotionStop();
                // Send event to accessibility when scroll stop.
                auto context = scroll->GetContext().Upgrade();
                if (context && scroll->Idle()) {
                    AccessibilityEvent scrollEvent;
                    scrollEvent.nodeId = scroll->nodeId_;
                    scrollEvent.eventType = "scrollend";
                    context->SendEventToAccessibility(scrollEvent);
                }
            }
        });
        controller_->PlayMotion(motion_);
    }
    SetDelayedTask();
}

void Scrollable::SetDelayedTask()
{
    SetContinuousDragStatus(true);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    task_.Reset([weak = WeakClaim(this)] {
        auto drag = weak.Upgrade();
        if (drag) {
            drag->ResetContinueDragCount();
            drag->SetContinuousDragStatus(false);
        }
    });
    taskExecutor.PostDelayedTask(task_, DRAG_INTERVAL_TIME);
}

double Scrollable::ComputeCap(int dragCount)
{
    if (dragCount < FIRST_THRESHOLD) {
        return 1.0;
    }
    auto cap = ComputeCap(dragCount - 1) + CAP_COEFFICIENT * (dragCount - 1);
    return cap;
}

double Scrollable::GetGain(double delta)
{
    auto cap = 1.0;
    auto gain = 1.0;
    if (!continuousSlidingCallback_) {
        return gain;
    }
    auto screenHeight = continuousSlidingCallback_();
    if (delta == 0 || screenHeight == 0) {
        return gain;
    }
    if (dragCount_ >= FIRST_THRESHOLD && dragCount_ < SECOND_THRESHOLD) {
        if (Negative(lastPos_ / delta)) {
            ResetContinueDragCount();
            return gain;
        }
        cap = ComputeCap(dragCount_);
        gain = (LessNotEqual(cap, std::abs(delta) / screenHeight * (dragCount_ - 1))) ? cap :
            std::abs(delta) / screenHeight * (dragCount_ - 1);
    } else if (dragCount_ >= SECOND_THRESHOLD) {
        if (Negative(lastPos_ / delta)) {
            ResetContinueDragCount();
            return gain;
        }
        cap = CAP_FIXED_VALUE;
        gain = (LessNotEqual(cap, std::abs(delta) / screenHeight * (dragCount_ - 1))) ? cap :
            std::abs(delta) / screenHeight * (dragCount_ - 1);
    }
    return gain;
}

void Scrollable::ExecuteScrollBegin(double& mainDelta)
{
    auto context = context_.Upgrade();
    if (!scrollBeginCallback_ || !context) {
        return;
    }

    ScrollInfo scrollInfo;
    if (axis_ == Axis::VERTICAL) {
        scrollInfo = scrollBeginCallback_(0.0_vp, Dimension(mainDelta / context->GetDipScale(), DimensionUnit::VP));
        mainDelta = context->NormalizeToPx(scrollInfo.dy);
    } else if (axis_ == Axis::HORIZONTAL) {
        scrollInfo = scrollBeginCallback_(Dimension(mainDelta / context->GetDipScale(), DimensionUnit::VP), 0.0_vp);
        mainDelta = context->NormalizeToPx(scrollInfo.dx);
    }
}

void Scrollable::ExecuteScrollFrameBegin(double& mainDelta, ScrollState state)
{
    auto context = context_.Upgrade();
    if (!scrollFrameBeginCallback_ || !context) {
        return;
    }

    auto offset = Dimension(mainDelta / context->GetDipScale(), DimensionUnit::VP);
    auto scrollRes = scrollFrameBeginCallback_(-offset, state);
    mainDelta = -context->NormalizeToPx(scrollRes.offset);
}

void Scrollable::FixScrollMotion(double position)
{
#ifdef WEARABLE_PRODUCT
    if (motion_ && needCenterFix_ && watchFixCallback_) {
        double finalPoisition = watchFixCallback_(motion_->GetFinalPosition(), position);
        LOGD("final position before fix(%{public}lf), need to fix to position(%{public}lf)",
            motion_->GetFinalPosition(), finalPoisition);
        if (!NearEqual(finalPoisition, motion_->GetFinalPosition(), DISTANCE_EPSILON)) {
            double velocity = motion_->GetVelocityByFinalPosition(finalPoisition);
            double friction = friction_ > 0 ? friction_ : sFriction_;
            motion_->Reset(friction, position, velocity);

            // fix again when velocity is less than velocity threshold
            if (!NearEqual(finalPoisition, motion_->GetFinalPosition(), DISTANCE_EPSILON)) {
                velocity = motion_->GetVelocityByFinalPosition(finalPoisition, 0.0);
                motion_->Reset(friction, position, velocity, 0.0);
            }
            LOGD("final position after fix (%{public}lf), ", motion_->GetFinalPosition());
        }
    }
#endif
};

void Scrollable::StartScrollSnapMotion(float predictSnapOffset, float scrollSnapVelocity)
{
    auto start = currentPos_;
    auto end = currentPos_ + predictSnapOffset;
    scrollSnapMotion_ = AceType::MakeRefPtr<SpringMotion>(start, end, scrollSnapVelocity, DEFAULT_OVER_SPRING_PROPERTY);

    scrollSnapMotion_->AddListener([weakScroll = AceType::WeakClaim(this), start, end](double position) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->ProcessScrollSnapMotion(position);
        }
    });
    scrollSnapController_->ClearStopListeners();
    scrollSnapController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto scroll = weak.Upgrade();
        CHECK_NULL_VOID(scroll);
        scroll->OnAnimateStop();
    });
    scrollSnapController_->PlayMotion(scrollSnapMotion_);
}

void Scrollable::ProcessScrollSnapSpringMotion(float scrollSnapDelta, float scrollSnapVelocity)
{
    LOGD("ProcessScrollSnapSpringMotion scrollSnapDelta:%{public}f, scrollSnapVelocity:%{public}f", scrollSnapDelta,
        scrollSnapVelocity);
    if (!snapController_) {
        snapController_ = AceType::MakeRefPtr<Animator>(PipelineBase::GetCurrentContext());
        snapController_->AddStopListener([weakScroll = AceType::WeakClaim(this)]() {
            auto scroll = weakScroll.Upgrade();
            CHECK_NULL_VOID_NOLOG(scroll);
            scroll->ProcessScrollMotionStop();
            // Send event to accessibility when scroll stop.
            auto context = scroll->GetContext().Upgrade();
            CHECK_NULL_VOID_NOLOG(context && scroll->Idle());
            AccessibilityEvent scrollEvent;
            scrollEvent.nodeId = scroll->nodeId_;
            scrollEvent.eventType = "scrollend";
            context->SendEventToAccessibility(scrollEvent);
        });
    }
    if (!snapMotion_) {
        snapMotion_ = AceType::MakeRefPtr<SpringMotion>(
            currentPos_, scrollSnapDelta + currentPos_, scrollSnapVelocity, SNAP_SCROLL_PROPERTY);
        snapMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](float position) {
            auto scroll = weakScroll.Upgrade();
            if (scroll) {
                scroll->ProcessScrollMotion(position);
            }
        });
    } else {
        snapMotion_->Reset(currentPos_, scrollSnapDelta + currentPos_, scrollSnapVelocity, SNAP_SCROLL_PROPERTY);
    }
    snapController_->PlayMotion(snapMotion_);
}

void Scrollable::UpdateScrollSnapStartOffset(double offset)
{
    if (scrollSnapMotion_ && scrollSnapController_ && scrollSnapController_->IsRunning()) {
        scrollSnapController_->ClearStopListeners();
        scrollSnapController_->Stop();
        auto currPos = scrollSnapMotion_->GetCurrentPosition();
        auto endPos = scrollSnapMotion_->GetEndValue();
        auto velocity = scrollSnapMotion_->GetCurrentVelocity();
        scrollSnapMotion_->Reset(currPos + offset, endPos, velocity, DEFAULT_OVER_SPRING_PROPERTY);
        scrollSnapController_->PlayMotion(scrollSnapMotion_);
        scrollSnapController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->OnAnimateStop();
        });
    }
}

void Scrollable::ProcessScrollSnapMotion(double position)
{
    LOGD("[scroll] currentPos_(%{public}lf), position(%{public}lf)", currentPos_, position);
    currentVelocity_ = scrollSnapMotion_->GetCurrentVelocity();
    if (NearEqual(currentPos_, position)) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION_SPRING);
    } else {
        moved_ = UpdateScrollPosition(position - currentPos_, SCROLL_FROM_ANIMATION_SPRING);
        if (!moved_) {
            scrollSnapController_->Stop();
        } else if (!touchUp_) {
            if (scrollTouchUpCallback_) {
                scrollTouchUpCallback_();
            }
            touchUp_ = true;
        }
    }
    currentPos_ = scrollSnapMotion_->GetCurrentPosition();
}

void Scrollable::OnAnimateStop()
{
    if (moved_) {
        HandleScrollEnd();
    }
    currentVelocity_ = 0.0;
    if (isTouching_ || isDragUpdateStop_) {
        return;
    }
    moved_ = false;
#ifdef OHOS_PLATFORM
    LOGI("springController stop increase cpu frequency");
    ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndListFling();
    }
#endif
    if (scrollEnd_) {
        scrollEnd_();
    }
    // Send event to accessibility when scroll stop.
    auto context = GetContext().Upgrade();
    if (context) {
        AccessibilityEvent scrollEvent;
        scrollEvent.nodeId = nodeId_;
        scrollEvent.eventType = "scrollend";
        context->SendEventToAccessibility(scrollEvent);
    }
#if !defined(PREVIEW)
    LayoutInspector::SupportInspector();
#endif
}

void Scrollable::StartSpringMotion(
    double mainPosition, double mainVelocity, const ExtentPair& extent, const ExtentPair& initExtent)
{
    LOGD("[scroll] position(%{public}lf), mainVelocity(%{public}lf), minExtent(%{public}lf), maxExtent(%{public}lf), "
         "initMinExtent(%{public}lf), initMaxExtent(%{public}lf",
        mainPosition, mainVelocity, extent.Leading(), extent.Trailing(), initExtent.Leading(), initExtent.Trailing());
    scrollMotion_ = AceType::MakeRefPtr<ScrollMotion>(mainPosition, mainVelocity, extent, initExtent, spring_);
    if (!scrollMotion_->IsValid()) {
        LOGE("scrollMotion is invalid, no available spring motion.");
        return;
    }
    scrollMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double position) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->ProcessSpringMotion(position);
        }
    });
    currentPos_ = mainPosition;
    springController_->ClearStopListeners();
    springController_->PlayMotion(scrollMotion_);
    springController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto scroll = weak.Upgrade();
        CHECK_NULL_VOID(scroll);
        scroll->OnAnimateStop();
    });
}

void Scrollable::ProcessScrollMotionStop()
{
    if (needScrollSnapChange_ && calePredictSnapOffsetCallback_) {
        needScrollSnapChange_ = false;
        auto predictSnapOffset = calePredictSnapOffsetCallback_(motion_->GetFinalPosition() - currentPos_);
        if (predictSnapOffset.has_value() && !NearZero(predictSnapOffset.value())) {
            ProcessScrollSnapSpringMotion(predictSnapOffset.value(), currentVelocity_);
            return;
        }
    }
    // spring effect special process
    if (scrollPause_) {
        scrollPause_ = false;
        HandleOverScroll(currentVelocity_);
    } else {
        currentVelocity_ = 0.0;
        if (isDragUpdateStop_) {
            return;
        }
        moved_ = false;
        HandleScrollEnd();
#ifdef OHOS_PLATFORM
        LOGI("controller stop increase cpu frequency");
        ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndListFling();
        }
#endif
        if (scrollEnd_) {
            scrollEnd_();
        }
#if !defined(PREVIEW)
        LayoutInspector::SupportInspector();
#endif
    }
}

void Scrollable::ProcessSpringMotion(double position)
{
    LOGD("[scroll] currentPos_(%{public}lf), position(%{public}lf)", currentPos_, position);
    currentVelocity_ = scrollMotion_->GetCurrentVelocity();
    if (NearEqual(currentPos_, position)) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION_SPRING);
    } else {
        moved_ = UpdateScrollPosition(position - currentPos_, SCROLL_FROM_ANIMATION_SPRING);
        if (!moved_) {
            springController_->Stop();
        } else if (!touchUp_) {
            if (scrollTouchUpCallback_) {
                scrollTouchUpCallback_();
            }
            touchUp_ = true;
        }
    }
    currentPos_ = position;
}

void Scrollable::ProcessScrollMotion(double position)
{
    if (motion_) {
        currentVelocity_ = motion_->GetCurrentVelocity();
    }
    if (needScrollSnapToSideCallback_) {
        needScrollSnapChange_ = needScrollSnapToSideCallback_(position - currentPos_);
    }
    LOGD("[scrolling] position(%{public}lf), currentVelocity_(%{public}lf), needScrollSnapChange_(%{public}u)",
        position, currentVelocity_, needScrollSnapChange_);
    if ((NearEqual(currentPos_, position))) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION);
    } else {
        // UpdateScrollPosition return false, means reach to scroll limit.
        auto mainDelta = position - currentPos_;
        HandleScroll(mainDelta, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
        if (!moved_) {
            controller_->Stop();
        } else if (!touchUp_) {
            if (scrollTouchUpCallback_) {
                scrollTouchUpCallback_();
            }
            touchUp_ = true;
        }
    }
    currentPos_ = position;

    // spring effect special process
    if ((IsSnapStopped() && canOverScroll_) || needScrollSnapChange_ ||
        (!overScrollOffsetCallback_ && (outBoundaryCallback_ && outBoundaryCallback_()))) {
        scrollPause_ = true;
        controller_->Stop();
    }
}

bool Scrollable::UpdateScrollPosition(const double offset, int32_t source) const
{
    bool ret = true;
    if (callback_) {
        ret = callback_(offset, source);
    }
    return ret;
}

void Scrollable::ProcessScrollOverCallback(double velocity)
{
    if (outBoundaryCallback_ && !outBoundaryCallback_() && !canOverScroll_) {
        return;
    }
    // In the case of chain animation enabled, you need to switch the control point first,
    // and then correct the offset value in notification process
    if (notifyScrollOverCallback_) {
        notifyScrollOverCallback_(velocity);
    }
    // then use corrected offset to make scroll motion.
    if (scrollOverCallback_) {
        scrollOverCallback_(velocity);
    }
}

bool Scrollable::HandleOverScroll(double velocity)
{
    auto parent = parent_.Upgrade();
    if (!parent || !nestedOpt_.NeedParent()) {
        if (edgeEffect_ != EdgeEffect::NONE) {
            ProcessScrollOverCallback(velocity);
            return true;
        }
        if (scrollEndCallback_) {
            scrollEndCallback_();
        }
        return false;
    }
    // parent handle over scroll first
    if ((velocity < 0 && (nestedOpt_.forward == NestedScrollMode::SELF_FIRST)) ||
        (velocity > 0 && (nestedOpt_.backward == NestedScrollMode::SELF_FIRST))) {
        if (parent->HandleOverScroll(velocity)) {
            if (scrollEndCallback_) {
                scrollEndCallback_();
            }
            return true;
        }
        if (edgeEffect_ != EdgeEffect::NONE) {
            ProcessScrollOverCallback(velocity);
            return true;
        }
    }

    // self handle over scroll first
    if (edgeEffect_ != EdgeEffect::NONE) {
        ProcessScrollOverCallback(velocity);
        return true;
    }
    if (scrollEndCallback_) {
        scrollEndCallback_();
    }
    return parent->HandleOverScroll(velocity);
}

void Scrollable::SetSlipFactor(double SlipFactor)
{
    slipFactor_ = std::clamp(SlipFactor, -ADJUSTABLE_VELOCITY, ADJUSTABLE_VELOCITY);
}

const RefPtr<SpringProperty>& Scrollable::GetDefaultOverSpringProperty()
{
    return DEFAULT_OVER_SPRING_PROPERTY;
}

} // namespace OHOS::Ace
