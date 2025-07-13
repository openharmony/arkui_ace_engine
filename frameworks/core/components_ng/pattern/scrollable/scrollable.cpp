/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/scrollable.h"

#include "base/log/jank_frame_report.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/ressched/ressched_report.h"
#include "core/common/layout_inspector.h"
#include "core/components_ng/pattern/scrollable/scrollable_animation_consts.h"
#include "core/components_ng/pattern/scrollable/scrollable_theme.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "base/log/event_report.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
namespace {

constexpr double CAP_COEFFICIENT = 0.45;
constexpr int32_t FIRST_THRESHOLD = 4;
constexpr int32_t SECOND_THRESHOLD = 10;
constexpr double CAP_FIXED_VALUE = 16.0;
constexpr uint32_t DRAG_INTERVAL_TIME = 400;
constexpr uint32_t MULTI_FLING_DISTANCE = 125;

#ifndef WEARABLE_PRODUCT
constexpr double FRICTION = 0.6;
constexpr double API11_FRICTION = 0.7;
constexpr double API12_FRICTION = 0.75;
constexpr double SLOW_FRICTION_THRESHOLD = 3000.0;
constexpr double SLOW_FRICTION = 1.0;
constexpr double VELOCITY_SCALE = 1.0;
constexpr double SLOW_VELOCITY_SCALE = 1.2;
constexpr double NEW_VELOCITY_SCALE = 1.5;
constexpr double ADJUSTABLE_VELOCITY = 3000.0;
#else
constexpr double DISTANCE_EPSILON = 1.0;
constexpr double FRICTION = 0.9;
constexpr double VELOCITY_SCALE = 0.8;
constexpr double ADJUSTABLE_VELOCITY = 0.0;
#endif
constexpr uint64_t MILLOS_PER_NANO_SECONDS = 1000 * 1000 * 1000;
constexpr uint64_t MIN_DIFF_VSYNC = 1000 * 1000; // min is 1ms
constexpr float DEFAULT_THRESHOLD = 0.75f;
constexpr float DEFAULT_SPRING_RESPONSE = 0.416f;
constexpr float DEFAULT_SPRING_DAMP = 0.99f;
constexpr uint32_t MAX_VSYNC_DIFF_TIME = 100 * 1000 * 1000; // max 100 ms
constexpr float START_FRICTION_VELOCITY_THRESHOLD = 240.0f;
constexpr float FRICTION_VELOCITY_THRESHOLD = 120.0f;
constexpr float SPRING_ACCURACY = 0.1;
constexpr float DEFAULT_MINIMUM_AMPLITUDE_PX = 1.0f;
constexpr float SCROLL_SNAP_MIN_STEP_THRESHOLD = 10.0f;
constexpr float SCROLL_SNAP_MIN_STEP = 1.0f;
#ifdef OHOS_PLATFORM
constexpr int64_t INCREASE_CPU_TIME_ONCE = 4000000000; // 4s(unit: ns)
#endif

#ifdef SUPPORT_DIGITAL_CROWN
constexpr double ANGULAR_VELOCITY_FACTOR  = 0.001f;
constexpr float ANGULAR_VELOCITY_SLOW = 0.07f;
constexpr float ANGULAR_VELOCITY_MEDIUM = 0.2f;
constexpr float ANGULAR_VELOCITY_FAST = 0.54f;
constexpr float DISPLAY_CONTROL_RATIO_VERY_SLOW = 1.19f;
constexpr float DISPLAY_CONTROL_RATIO_SLOW = 1.87f;
constexpr float DISPLAY_CONTROL_RATIO_MEDIUM = 1.67f;
constexpr float DISPLAY_CONTROL_RATIO_FAST = 1.59f;
constexpr float CROWN_SENSITIVITY_LOW = 0.8f;
constexpr float CROWN_SENSITIVITY_MEDIUM = 1.0f;
constexpr float CROWN_SENSITIVITY_HIGH = 1.2f;
constexpr float RESPONSIVE_SPRING_AMPLITUDE_RATIO = 0.00025f;

constexpr float CROWN_START_FRICTION_VELOCITY_THRESHOLD = 6.0f;
#else
constexpr float RESPONSIVE_SPRING_AMPLITUDE_RATIO = 0.001f;
#endif
} // namespace

double Scrollable::GetVelocityScale()
{
    return Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_VELOCITY_SCALE
                                                                                    : VELOCITY_SCALE;
}

Scrollable::~Scrollable()
{
    // If animation still runs, force stop it.
    if (!IsStopped()) {
        PerfMonitor::GetPerfMonitor()->EndCommercial(PerfConstants::APP_LIST_FLING, false);
        AceAsyncTraceEndCommercial(0, (TRAILING_ANIMATION + std::to_string(nodeId_) + std::string(" ") +
            nodeTag_).c_str());
        if (!context_.Invalid()) {
            auto context = context_.Upgrade();
            context->SetUiDvsyncSwitch(false);
        }
    }
    StopFrictionAnimation();
    StopSpringAnimation();
    StopSnapAnimation();
}

void Scrollable::Initialize(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    weakHost_ = host;
    auto pipeline = host->GetContextRefPtr();
    context_ = pipeline;
    InitPanRecognizerNG();
    available_ = true;
    CHECK_NULL_VOID(pipeline);
    auto scrollableTheme = pipeline->GetTheme<ScrollableTheme>();
    CHECK_NULL_VOID(scrollableTheme);
    flingVelocityScale_ = pipeline->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)
                              ? scrollableTheme->GetFlingVelocityScale()
                              : VELOCITY_SCALE;
    springVelocityScale_ = pipeline->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)
                               ? scrollableTheme->GetSpringVelocityScale()
                               : VELOCITY_SCALE;
    ratio_ = scrollableTheme->GetRatio();
    springResponse_ = scrollableTheme->GetSpringResponse();
    touchPadVelocityScaleRate_ = scrollableTheme->GetTouchPadVelocityScaleRate();
    if (friction_ == -1) {
        if (pipeline->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
            defaultFriction_ = scrollableTheme->GetFriction();
        } else if (pipeline->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            defaultFriction_ = API12_FRICTION;
        } else if (pipeline->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
            defaultFriction_ = API11_FRICTION;
        } else {
            defaultFriction_ = FRICTION;
        }
    }
}

void Scrollable::InitAxisAnimator()
{
    CHECK_NULL_VOID(!axisAnimator_);
    auto axisAnimationCallback = [weak = WeakClaim(this)](float offset) {
        auto scrollable = weak.Upgrade();
        CHECK_NULL_VOID(scrollable);
        scrollable->ReportToDragFRCScene(scrollable->currentVelocity_, NG::SceneStatus::RUNNING);
        scrollable->ProcessScrollMotion(offset, SCROLL_FROM_AXIS);
    };
    auto axisAnimationStartCallback = [weak = WeakClaim(this)](float position) {
        auto scrollable = weak.Upgrade();
        CHECK_NULL_VOID(scrollable && scrollable->onScrollStartRec_);
        scrollable->ReportToDragFRCScene(scrollable->currentVelocity_, NG::SceneStatus::START);
        scrollable->onScrollStartRec_(position);
    };
    auto axisAnimationFinishCallback = [weak = WeakClaim(this)]() {
        auto scrollable = weak.Upgrade();
        CHECK_NULL_VOID(scrollable);
        scrollable->ReportToDragFRCScene(scrollable->currentVelocity_, NG::SceneStatus::END);
        scrollable->ProcessScrollMotionStop();
    };
    axisAnimator_ = AceType::MakeRefPtr<AxisAnimator>(std::move(axisAnimationCallback),
        std::move(axisAnimationStartCallback), std::move(axisAnimationFinishCallback));
    axisAnimator_->Initialize(context_);
}

void Scrollable::InitPanRecognizerNG()
{
    PanDirection panDirection;
    panDirection.type = axis_ == Axis::VERTICAL ? PanDirection::VERTICAL : PanDirection::HORIZONTAL;
    double distance = SystemProperties::GetScrollableDistance();
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, distance } };
    if (LessOrEqual(distance, 0.0)) {
        distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
            { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    }
    panRecognizerNG_ =
        AceType::MakeRefPtr<NG::PanRecognizer>(DEFAULT_PAN_FINGER, panDirection, distanceMap);
    panRecognizerNG_->SetIsAllowMouse(false);
    SetOnActionStart();
    SetOnActionUpdate();
    SetOnActionEnd();
    SetOnActionCancel();
    SetPanEndCallback();
}

void Scrollable::SetOnActionStart()
{
    CHECK_NULL_VOID(panRecognizerNG_);
    auto actionStart = [weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        CHECK_NULL_VOID(scroll);
        scroll->HandleDragStart(info);
    };
    panRecognizerNG_->SetOnActionStart(actionStart);
}

void Scrollable::SetOnActionUpdate()
{
    CHECK_NULL_VOID(panRecognizerNG_);
    auto actionUpdate = [weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        CHECK_NULL_VOID(scroll);
        scroll->HandleDragUpdate(info);
    };
    panRecognizerNG_->SetOnActionUpdate(actionUpdate);
}

void Scrollable::SetOnActionEnd()
{
    CHECK_NULL_VOID(panRecognizerNG_);
    auto actionEnd = [weakScroll = AceType::WeakClaim(this)](GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        CHECK_NULL_VOID(scroll);
        scroll->HandleDragEnd(info);
        scroll->ProcessPanActionEndEvents(info);
        scroll->isDragging_ = false;
    };
    panRecognizerNG_->SetOnActionEnd(actionEnd);
}

void Scrollable::SetPanEndCallback()
{
    CHECK_NULL_VOID(panRecognizerNG_);
    auto panEndCallback = [weakScroll = AceType::WeakClaim(this)](GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            auto tempInfo = info;
            tempInfo.SetMainDelta(0.0);
            tempInfo.SetMainVelocity(0.0);
            ACE_SCOPED_TRACE("Trigger PanEndCallback, id:%d, tag:%s", scroll->nodeId_, scroll->nodeTag_.c_str());
            scroll->HandleDragEnd(tempInfo, true);
            scroll->ProcessPanActionEndEvents(tempInfo);
            scroll->isDragging_ = false;
        }
    };
    panRecognizerNG_->SetPanEndCallback(panEndCallback);
}

void Scrollable::ProcessPanActionEndEvents(const GestureEvent& info)
{
    CHECK_NULL_VOID(!panActionEndEvents_.empty());
    std::for_each(panActionEndEvents_.begin(), panActionEndEvents_.end(), [info](GestureEventFunc& event) {
        auto gestureInfo = info;
        event(gestureInfo);
    });
}

void Scrollable::SetOnActionCancel()
{
    CHECK_NULL_VOID(panRecognizerNG_);
    auto actionCancel = [weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        CHECK_NULL_VOID(scroll);
        if (scroll->dragCancelCallback_) {
            scroll->dragCancelCallback_();
        }
        GestureEvent nullInfo;
        scroll->HandleDragEnd(nullInfo);
        if (scroll->panActionEndEvents_.empty()) {
            scroll->isDragging_ = false;
            return;
        }
        std::for_each(scroll->panActionEndEvents_.begin(), scroll->panActionEndEvents_.end(),
            [nullInfo](GestureEventFunc& event) {
                auto gestureInfo = nullInfo;
                event(gestureInfo);
            });
        scroll->isDragging_ = false;
    };
    panRecognizerNG_->SetOnActionCancel(actionCancel);
}

#ifdef SUPPORT_DIGITAL_CROWN
void Scrollable::ListenDigitalCrownEvent(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetFocusHub();
    CHECK_NULL_VOID(focusHub);

    auto onCrownEvent = [weakScroll = AceType::WeakClaim(this), weakNode = AceType::WeakClaim(AceType::RawPtr(
        frameNode))](const CrownEvent& event) -> bool {
        auto scroll = weakScroll.Upgrade();
        CHECK_NULL_RETURN(scroll, false);
        auto node = weakNode.Upgrade();
        CHECK_NULL_RETURN(node, false);

        auto centerOffset = node->GetGeometryNode()->GetContentRect().Center();
        scroll->HandleCrownEvent(event, centerOffset);
        return true;
    };
    focusHub->SetOnCrownEventInternal(std::move(onCrownEvent));

    focusHub->SetOnBlurReasonInternal([weak = WeakClaim(this)](const BlurReason& blurReason) {
        auto scroll = weak.Upgrade();
        CHECK_NULL_VOID(scroll);
        GestureEvent info;
        info.SetSourceDevice(SourceType::CROWN);
        info.SetSourceTool(SourceTool::UNKNOWN);
        scroll->HandleCrownActionCancel(info);
    });
}

double Scrollable::GetCrownRotatePx(const CrownEvent& event) const
{
    double velocity = std::abs(event.angularVelocity * ANGULAR_VELOCITY_FACTOR);
    double px = 0.0;
    if (LessOrEqualCustomPrecision(velocity, ANGULAR_VELOCITY_SLOW, 0.01f)) {  // very slow
        px = (Dimension(DISPLAY_CONTROL_RATIO_VERY_SLOW, DimensionUnit::VP) * event.degree).ConvertToPx();
    } else if (LessOrEqualCustomPrecision(velocity, ANGULAR_VELOCITY_MEDIUM, 0.01f)) {  // slow
        px = (Dimension(DISPLAY_CONTROL_RATIO_SLOW, DimensionUnit::VP) * event.degree).ConvertToPx();
    } else if (LessOrEqualCustomPrecision(velocity, ANGULAR_VELOCITY_FAST, 0.01f)) {  // medium
        px = (Dimension(DISPLAY_CONTROL_RATIO_MEDIUM, DimensionUnit::VP) * event.degree).ConvertToPx();
    } else {  // fast
        px = (Dimension(DISPLAY_CONTROL_RATIO_FAST, DimensionUnit::VP) * event.degree).ConvertToPx();
    }
    switch (crownSensitivity_) {
        case CrownSensitivity::LOW:
            px *= CROWN_SENSITIVITY_LOW;
            break;
        case CrownSensitivity::MEDIUM:
            px *= CROWN_SENSITIVITY_MEDIUM;
            break;
        case CrownSensitivity::HIGH:
            px *= CROWN_SENSITIVITY_HIGH;
            break;
        default:
            break;
    }
    return px;
}

void Scrollable::UpdateCrownVelocity(const TimeStamp& timeStamp, double mainDelta, bool end)
{
    if (axis_ == Axis::VERTICAL) {
        accumulativeCrownPx_ += Offset(0, mainDelta);
    } else {
        accumulativeCrownPx_ += Offset(mainDelta, 0);
    }
    crownVelocityTracker_.UpdateTrackerPoint(accumulativeCrownPx_.GetX(), accumulativeCrownPx_.GetY(), timeStamp, end);
}

void Scrollable::HandleCrownEvent(const CrownEvent& event, const OffsetF& center)
{
    DimensionOffset centerDimension(center);
    Offset globalLocation(centerDimension.GetX().ConvertToPx(), centerDimension.GetY().ConvertToPx());

    GestureEvent info;
    info.SetSourceDevice(SourceType::CROWN);
    info.SetSourceTool(SourceTool::UNKNOWN);
    info.SetGlobalLocation(globalLocation);
    double mainDelta = GetCrownRotatePx(event);

    switch (event.action) {
        case CrownAction::BEGIN:
            crownEventNum_ = 0;
            TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "-->BEGIN]");
            HandleCrownActionBegin(event.timeStamp, mainDelta, info);
            break;
        case CrownAction::UPDATE:
            TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "-->UPDATE]");
            HandleCrownActionUpdate(event.timeStamp, mainDelta, info);
            break;
        case CrownAction::END:
            TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "-->END]");
            HandleCrownActionEnd(event.timeStamp, mainDelta, info);
            break;
        default:
            HandleCrownActionCancel(info);
            break;
    }
}

void Scrollable::HandleCrownActionBegin(const TimeStamp& timeStamp, double mainDelta, GestureEvent& info)
{
    if (isDragging_) {
        return;
    }
    accumulativeCrownPx_.Reset();
    crownVelocityTracker_.Reset();
    UpdateCrownVelocity(timeStamp, mainDelta, false);
    info.SetMainDelta(mainDelta);
    info.SetMainVelocity(crownVelocityTracker_.GetMainAxisVelocity());
    isDragging_ = true;
    isCrownEventDragging_ = true;
    isCrownDragging_ = true;
    HandleDragStart(info);
}

void Scrollable::HandleCrownActionUpdate(const TimeStamp& timeStamp, double mainDelta, GestureEvent& info)
{
    if (!isCrownEventDragging_) {
        return;
    }
    UpdateCrownVelocity(timeStamp, mainDelta, false);
    info.SetMainDelta(mainDelta);
    info.SetMainVelocity(crownVelocityTracker_.GetMainAxisVelocity());
    HandleDragUpdate(info);
}

void Scrollable::HandleCrownActionEnd(const TimeStamp& timeStamp, double mainDelta, GestureEvent& info)
{
    if (!isCrownEventDragging_) {
        return;
    }
    if (NearZero(mainDelta)) {
        info.SetMainDelta(crownVelocityTracker_.GetMainAxisDeltaPos());
        info.SetMainVelocity(crownVelocityTracker_.GetMainAxisVelocity());
    } else {
        UpdateCrownVelocity(timeStamp, mainDelta, true);
        info.SetMainDelta(mainDelta);
        info.SetMainVelocity(crownVelocityTracker_.GetMainAxisVelocity());
    }
    HandleDragEnd(info);
    std::for_each(panActionEndEvents_.begin(), panActionEndEvents_.end(),
        [info](GestureEventFunc& event) {
            auto gestureInfo = info;
            event(gestureInfo);
        });
    isDragging_ = false;
    isCrownDragging_ = false;
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    crownTask_.Reset([weak = WeakClaim(this)] {
        auto scrollable = weak.Upgrade();
        if (scrollable) {
            scrollable->SetCrownEventDragging(false);
        }
    });
    taskExecutor.PostDelayedTask(crownTask_, CUSTOM_SPRING_ANIMATION_DURATION, "ArkUIUpdateCrownEventDrag");
}

void Scrollable::HandleCrownActionCancel(GestureEvent& info)
{
    if (!isDragging_ || !isCrownEventDragging_) {
        return;
    }

    if (dragCancelCallback_) {
        dragCancelCallback_();
    }
    info.SetMainDelta(0);
    info.SetMainVelocity(0);
    HandleDragEnd(info);
    std::for_each(panActionEndEvents_.begin(), panActionEndEvents_.end(),
        [info](GestureEventFunc& event) {
            auto gestureInfo = info;
            event(gestureInfo);
        });
    isDragging_ = false;
    isCrownDragging_ = false;
}
#endif

void Scrollable::SetAxis(Axis axis)
{
    axis_ = axis;
    PanDirection panDirection;
    if (axis_ == Axis::NONE) {
        panDirection.type = PanDirection::NONE;
    } else if (axis_ == Axis::VERTICAL) {
        panDirection.type = PanDirection::VERTICAL;
    } else {
        panDirection.type = PanDirection::HORIZONTAL;
    }
    if (panRecognizerNG_) {
        panRecognizerNG_->SetDirection(panDirection);
    }
#ifdef SUPPORT_DIGITAL_CROWN
    crownVelocityTracker_.SetMainAxis(axis_);
#endif
}

void Scrollable::HandleTouchDown(bool fromcrown)
{
    if (!fromcrown) {
        isTouching_ = true;
    }
    // If animation still runs, first stop it.
    ACE_SCOPED_TRACE("HandleTouchDown, panDirection:%u, id:%d, tag:%s", GetPanDirection(), nodeId_, nodeTag_.c_str());
    StopSpringAnimation();
    if (state_ == AnimationState::FRICTION) {
        StopFrictionAnimation();
    } else if (state_ == AnimationState::SNAP) {
        StopSnapAnimation();
    }
}

void Scrollable::HandleTouchUp()
{
    // Two fingers are alternately drag, one finger is released without triggering spring animation.
    ACE_SCOPED_TRACE("HandleTouchUp, isDragging_:%u, nestedScrolling_:%u id:%d, tag:%s", isDragging_, nestedScrolling_,
        nodeId_, nodeTag_.c_str());
    if (isDragging_) {
        return;
    }
    isTouching_ = false;
    if (nestedScrolling_) {
        return;
    }
    if (CanStayOverScroll()) {
        return;
    }
    // outBoundaryCallback_ is only set in ScrollablePattern::SetEdgeEffect and when the edge effect is spring
    if (outBoundaryCallback_ && outBoundaryCallback_()) {
        if (state_ != AnimationState::SPRING && scrollOverCallback_) {
            if (onScrollStartRec_) {
                onScrollStartRec_(static_cast<float>(axis_));
            }
            ProcessScrollOverCallback(0.0);
        }
        return;
    }
    if (state_ != AnimationState::SNAP && startSnapAnimationCallback_) {
        SnapAnimationOptions snapAnimationOptions;
        startSnapAnimationCallback_(snapAnimationOptions);
    }
}

void Scrollable::HandleTouchCancel()
{
    if (isDragging_) {
        return;
    }
    isTouching_ = false;
    ACE_SCOPED_TRACE("HandleTouchCancel, id:%d, tag:%s", nodeId_, nodeTag_.c_str());
    if (state_ != AnimationState::SPRING && scrollOverCallback_) {
        ProcessScrollOverCallback(0.0);
    }
}

bool Scrollable::IsAnimationNotRunning() const
{
    return !isTouching_ && state_ == AnimationState::IDLE;
}

bool Scrollable::Idle() const
{
    return !isTouching_ && state_ == AnimationState::IDLE && !nestedScrolling_ && !isCrownDragging_;
}

bool Scrollable::IsStopped() const
{
    return state_ == AnimationState::IDLE;
}

bool Scrollable::IsSpringStopped() const
{
    return state_ != AnimationState::SPRING;
}

bool Scrollable::IsSnapStopped() const
{
    return state_ != AnimationState::SNAP;
}

void Scrollable::StopScrollable()
{
    if (state_ == AnimationState::FRICTION) {
        StopFrictionAnimation();
    }
    if (state_ == AnimationState::SPRING) {
        StopSpringAnimation();
    }
    if (state_ == AnimationState::SNAP) {
        StopSnapAnimation();
    }
}

void Scrollable::HandleScrollEnd(const std::optional<float>& velocity)
{
    // priority:
    //  1. onScrollEndRec_ (would internally call onScrollEnd)
    //  2. scrollEndCallback_
    if (onScrollEndRec_) {
        onScrollEndRec_(velocity);
        return;
    }
    if (scrollEndCallback_) {
        scrollEndCallback_();
    }
}

void Scrollable::HandleDragStart(const OHOS::Ace::GestureEvent& info)
{
    if (info.GetSourceTool() == SourceTool::TOUCHPAD) {
        HandleTouchDown();
    }
#ifdef SUPPORT_DIGITAL_CROWN
    crownTask_.Cancel();
    if (info.GetSourceDevice() != SourceType::CROWN) {
        isCrownEventDragging_ = false;
    }
    if (isCrownEventDragging_) {
        HandleTouchDown(true);
    }
#endif
    currentVelocity_ = info.GetMainVelocity();
    auto isAxisEvent = IsMouseWheelScroll(info);
    if (!isAxisEvent) {
        ReportToDragFRCScene(currentVelocity_, NG::SceneStatus::START);
    }
    if (continuousDragStatus_) {
        IncreaseContinueDragCount();
        task_.Cancel();
    }
    SetDragStartPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    const double dragPositionInMainAxis =
        axis_ == Axis::VERTICAL ? info.GetGlobalLocation().GetY() : info.GetGlobalLocation().GetX();
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Scroll drag start, id:%{public}d, tag:%{public}s", nodeId_, nodeTag_.c_str());
    skipRestartSpring_ = false; // reset flags. Extract method if more flags need to be reset
#ifdef OHOS_PLATFORM
    // Increase the cpu frequency when sliding start.
    auto currentTime = GetSysTimestamp();
    auto increaseCpuTime = currentTime - startIncreaseTime_;
    if (!moved_ || increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
        startIncreaseTime_ = currentTime;
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().BeginListFling();
        }
    }
#endif
    JankFrameReport::GetInstance().SetFrameJankFlag(JANK_RUNNING_SCROLL);
    ACE_SCOPED_TRACE("HandleDragStart, inputEventType:%d, sourceTool:%d, IsMouseWheelScroll:%u, "
                     "IsAxisAnimationRunning:%u, IsSnapAnimationRunning:%u, id:%d, tag:%s",
        info.GetInputEventType(), info.GetSourceTool(), isAxisEvent, IsAxisAnimationRunning(), IsSnapAnimationRunning(),
        nodeId_, nodeTag_.c_str());
    if (isAxisEvent && !CanStayOverScroll()) {
        if (!IsAxisAnimationRunning() && !IsSnapAnimationRunning()) {
            axisSnapDistance_ = currentPos_;
            snapDirection_ = SnapDirection::NONE;
        }
        return;
    } else if (IsAxisAnimationRunning()) {
        StopAxisAnimation();
    }
    isDragging_ = true;
    if (onScrollStartRec_) {
        onScrollStartRec_(static_cast<float>(dragPositionInMainAxis));
    }
}

ScrollResult Scrollable::HandleScroll(double offset, int32_t source, NestedState state)
{
    if (!handleScrollCallback_) {
        ExecuteScrollBegin(offset);
        canOverScroll_ = false;
        moved_ = UpdateScrollPosition(offset, source);
        return { 0, false };
    }
    // call NestableScrollContainer::HandleScroll
    return handleScrollCallback_(static_cast<float>(offset), source, state);
}

void Scrollable::HandleDragUpdate(const GestureEvent& info)
{
    currentVelocity_ = info.GetMainVelocity();
    ReportToDragFRCScene(currentVelocity_, NG::SceneStatus::RUNNING);
    if (!NearZero(info.GetMainVelocity()) && dragCount_ >= FIRST_THRESHOLD) {
        if (Negative(lastGestureVelocity_ / info.GetMainVelocity())) {
            ResetContinueDragCount();
        }
    }
    if (state_ != AnimationState::IDLE) {
        // If animation still runs, first stop it.
        isDragUpdateStop_ = true;
        StopFrictionAnimation();
        StopSpringAnimation();
        if (!(IsMouseWheelScroll(info) && GetSnapType() != SnapType::NONE_SNAP)) {
            StopSnapAnimation();
            currentPos_ = 0.0;
        }
    }
#ifdef OHOS_PLATFORM
    // Handle the case where you keep sliding past limit time(4s).
    auto currentTime = GetSysTimestamp();
    auto increaseCpuTime = currentTime - startIncreaseTime_;
    if (increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
        startIncreaseTime_ = currentTime;
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().BeginListFling();
        }
    }
#endif
    auto mainDelta = info.GetMainDelta();
    lastMainDelta_ = mainDelta;
    auto isReverse = isReverseCallback_ && isReverseCallback_();
    mainDelta = isReverse ? Round(-mainDelta) : Round(mainDelta);
    JankFrameReport::GetInstance().RecordFrameUpdate();
    auto source = SCROLL_FROM_UPDATE;
    auto isAxisEvent = IsMouseWheelScroll(info);
    if (isAxisEvent) {
        source = SCROLL_FROM_AXIS;
    }
#ifdef SUPPORT_DIGITAL_CROWN
    if (isCrownEventDragging_) {
        source = SCROLL_FROM_CROWN;
    }
#endif
    ACE_SCOPED_TRACE(
        "HandleDragUpdate, mainDelta:%f, source:%d, id:%d, tag:%s", mainDelta, source, nodeId_, nodeTag_.c_str());
    if (isAxisEvent) {
        CHECK_EQUAL_VOID(CanStayOverScroll(), true);
        ProcessAxisUpdateEvent(mainDelta);
        return;
    }
    HandleScroll(mainDelta, source, NestedState::GESTURE);
}

void Scrollable::ProcessAxisUpdateEvent(float mainDelta, bool fromScrollBar)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto currentVsyncTime = context->GetVsyncTime();
    auto snapType = GetSnapType();
    if (snapType != SnapType::NONE_SNAP && startSnapAnimationCallback_) {
        CHECK_NULL_VOID(lastAxisVsyncTime_ != currentVsyncTime);
        lastAxisVsyncTime_ = currentVsyncTime;
        auto snapDelta = 0.f;
        auto snapDirection = SnapDirection::NONE;
        auto isInitScroll = (snapType == SnapType::LIST_SNAP && snapDirection_ == SnapDirection::NONE) ||
                            (snapType == SnapType::SCROLL_SNAP && state_ == AnimationState::IDLE);
        if (isInitScroll) {
            snapDirection = Positive(mainDelta) ? SnapDirection::FORWARD : SnapDirection::BACKWARD;
        } else {
            if (snapDirection_ == SnapDirection::BACKWARD && !Positive(mainDelta)) {
                snapDelta = endPos_ - currentPos_;
                snapDirection = SnapDirection::BACKWARD;
            } else if (snapDirection_ == SnapDirection::FORWARD && Positive(mainDelta)) {
                snapDelta = endPos_ - currentPos_;
                snapDirection = SnapDirection::FORWARD;
            } else if ((snapDirection_ == SnapDirection::BACKWARD && Positive(mainDelta)) ||
                       (snapDirection_ == SnapDirection::FORWARD && !Positive(mainDelta))) {
                snapDelta = 0.f;
                snapDirection = SnapDirection::NONE;
            }
        }
        ACE_SCOPED_TRACE("ProcessAxisUpdateEvent start SnapAnimation, snapDelta:%f, snapDirection:%d, "
                         "lastSnapDirection:%d, id:%d, tag:%s",
            snapDelta, snapDirection, snapDirection_, nodeId_, nodeTag_.c_str());
        SnapAnimationOptions snapAnimationOptions = { .snapDelta = snapDelta, .animationVelocity = currentVelocity_,
            .snapDirection = snapDirection, .fromScrollBar = fromScrollBar };
        startSnapAnimationCallback_(snapAnimationOptions);
        auto isNeedAdjustDirection = (snapType == SnapType::SCROLL_SNAP && snapDirection == SnapDirection::NONE);
        if (isNeedAdjustDirection) {
            snapDirection_ = Positive(mainDelta) ? SnapDirection::FORWARD : SnapDirection::BACKWARD;
        } else {
            snapDirection_ = snapDirection;
        }
        return;
    }
    lastAxisVsyncTime_ = currentVsyncTime;
    if (!axisAnimator_) {
        InitAxisAnimator();
    }
    ACE_SCOPED_TRACE(
        "ProcessAxisUpdateEvent onAxis, IsAxisAnimationRunning:%u, mainDelta:%f, currentPos_:%f, id:%d, tag:%s",
        IsAxisAnimationRunning(), mainDelta, currentPos_, nodeId_, nodeTag_.c_str());
    axisAnimator_->OnAxis(mainDelta, currentPos_);
}

void Scrollable::LayoutDirectionEst(double gestureVelocity, double velocityScale, bool isScrollFromTouchPad)
{
    auto defaultVelocityScale = isSlow_ ? SLOW_VELOCITY_SCALE : velocityScale;
    double ret = SystemProperties::GetSrollableVelocityScale();
    velocityScale = !NearZero(ret) ? ret : defaultVelocityScale;
    velocityScale = isScrollFromTouchPad ? velocityScale * touchPadVelocityScaleRate_ : velocityScale;
    double gain = GetGain(GetDragOffset());
    if (isReverseCallback_ && isReverseCallback_()) {
        currentVelocity_ = -gestureVelocity * velocityScale * gain;
    } else {
        currentVelocity_ = gestureVelocity * velocityScale * gain;
    }
    // Apply max fling velocity limit, it must be calculated after all fling velocity gain.
    currentVelocity_ = std::clamp(currentVelocity_, -maxFlingVelocity_ + slipFactor_, maxFlingVelocity_ - slipFactor_);
    slidInfo_.gestureVelocity = gestureVelocity;
    slidInfo_.velocityScale = velocityScale;
    slidInfo_.gain = gain;
    slidInfo_.maxFlingVelocity = maxFlingVelocity_;
    slidInfo_.slipFactor = slipFactor_;
}

void Scrollable::HandleDragEnd(const GestureEvent& info, bool isFromPanEnd)
{
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Scroll drag end, velocity is %{public}f id:%{public}d, tag:%{public}s, "
        "dragCnt:%{public}d", info.GetMainVelocity(), nodeId_, nodeTag_.c_str(), dragCount_);
    auto isAxisEvent = IsMouseWheelScroll(info);
    if (isAxisEvent) {
        ProcessAxisEndEvent();
        return;
    }
    if (CanStayOverScroll()) {
        SetCanStayOverScroll(false);
    }
    // avoid no render frame when drag end
    if (!isFromPanEnd) {
        if (NearZero(info.GetMainDelta())) {
            auto tempInfo = info;
            tempInfo.SetMainDelta(lastMainDelta_);
            HandleDragUpdate(tempInfo);
        } else {
            HandleDragUpdate(info);
        }
    }
    if (onWillStopDraggingCallback_) {
        onWillStopDraggingCallback_(info.GetMainVelocity());
    }
    ReportToDragFRCScene(info.GetMainVelocity(), NG::SceneStatus::END);
    bool isScrollFromTouchPad = info.GetSourceTool() == SourceTool::TOUCHPAD;
    isDragUpdateStop_ = false;
    scrollPause_ = false;
    lastGestureVelocity_ = GetPanDirection() == Axis::NONE ? 0.0 : info.GetMainVelocity();
    isSlow_ = LessNotEqual(std::abs(lastGestureVelocity_), SLOW_FRICTION_THRESHOLD);
    SetDragEndPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    lastPos_ = GetDragOffset();
    JankFrameReport::GetInstance().ClearFrameJankFlag(JANK_RUNNING_SCROLL);
    double mainPosition = Round(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    if (!moved_ || isAxisEvent) {
        LayoutDirectionEst(lastGestureVelocity_, flingVelocityScale_, isScrollFromTouchPad);
        ResetContinueDragCount();
        if (GetSnapType() == SnapType::SCROLL_SNAP) {
            currentPos_ = mainPosition;
            SnapAnimationOptions snapAnimationOptions = { .animationVelocity = currentVelocity_ };
            if (startSnapAnimationCallback_ && startSnapAnimationCallback_(snapAnimationOptions)) {
                isTouching_ = false;
                return;
            }
        }
        HandleScrollEnd(currentVelocity_);
        currentVelocity_ = 0.f;
#ifdef OHOS_PLATFORM
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndListFling();
        }
#endif
    } else if (canOverScroll_) {
        LayoutDirectionEst(lastGestureVelocity_, springVelocityScale_, isScrollFromTouchPad);
        CalcOverScrollVelocity();
        ResetContinueDragCount();
        HandleOverScroll(currentVelocity_);
    } else {
        LayoutDirectionEst(lastGestureVelocity_, flingVelocityScale_, isScrollFromTouchPad);
        StartScrollAnimation(mainPosition, currentVelocity_, isScrollFromTouchPad);
    }
    ACE_SCOPED_TRACE(
        "HandleDragEnd, mainPosition:%f, getureDelta:%lf, gestureVelocity:%f, currentVelocity:%f, moved_:%u "
        "canOverScroll_:%u, id:%d, tag:%s",
        mainPosition, info.GetMainDelta(), lastGestureVelocity_, currentVelocity_, moved_, canOverScroll_, nodeId_,
        nodeTag_.c_str());
    SetDelayedTask();
    if (dragEndCallback_) {
        dragEndCallback_();
    }
    if (info.GetSourceDevice() != SourceType::CROWN) {
        isTouching_ = false;
    }
    SetDragStartPosition(0.0);
    SetDragEndPosition(0.0);
}

void Scrollable::ProcessAxisEndEvent()
{
    scrollPause_ = false;
    isTouching_ = false;
    isDragUpdateStop_ = false;
    JankFrameReport::GetInstance().ClearFrameJankFlag(JANK_RUNNING_SCROLL);
    if (CanStayOverScroll()) {
        HandleOverScroll(0);
        SetCanStayOverScroll(false);
    }
}

void Scrollable::ReportToDragFRCScene(double velocity, NG::SceneStatus sceneStatus)
{
    CHECK_NULL_VOID(dragFRCSceneCallback_);
    dragFRCSceneCallback_(velocity, sceneStatus);
}

void Scrollable::CalcOverScrollVelocity()
{
    auto gamma = 0.0f;
    if (overScrollOffsetCallback_ && continuousSlidingCallback_) {
        gamma = overScrollOffsetCallback_() / continuousSlidingCallback_();
    }
    gamma = GreatOrEqual(gamma, 1.0) ? 1.0f : gamma;
    currentVelocity_ = currentVelocity_ * exp(-ratio_ * gamma);
}

void Scrollable::StartScrollAnimation(float mainPosition, float correctVelocity, bool isScrollFromTouchPad)
{
    if (state_ == AnimationState::SPRING) {
        StopSpringAnimation();
    }
    if (!frictionOffsetProperty_) {
        GetFrictionProperty();
    }
    StopSnapController();
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "The position of scroll motion is %{public}f, velocity is %{public}f",
        mainPosition, correctVelocity);
    double frictionTmp = friction_;
    if (NearEqual(friction_, -1.0)) {
        auto defaultFriction = isSlow_ ? SLOW_FRICTION : defaultFriction_;
        double ret = SystemProperties::GetSrollableFriction();
        frictionTmp = !NearZero(ret) ? ret : defaultFriction;
    }
    float friction = frictionTmp;
    slidInfo_.friction = friction;
    EventReport::ReportPageSlidInfo(slidInfo_);
    initVelocity_ = correctVelocity;
    finalPosition_ = mainPosition + correctVelocity / (friction * -FRICTION_SCALE);
    if (fixScrollParamCallback_) {
        fixScrollParamCallback_(mainPosition, initVelocity_, finalPosition_);
        correctVelocity = initVelocity_;
        currentVelocity_ = correctVelocity;
    }
    currentPos_ = mainPosition;
    SnapAnimationOptions snapAnimationOptions = {
        .snapDelta = GetFinalPosition() - mainPosition,
        .animationVelocity = correctVelocity,
        .dragDistance = GetDragOffset(),
    };
    if (startSnapAnimationCallback_ && startSnapAnimationCallback_(snapAnimationOptions)) {
        if (GetSnapType() == SnapType::LIST_SNAP) {
            currentVelocity_ = 0.0;
        }
        return;
    }
    float threshold = START_FRICTION_VELOCITY_THRESHOLD;
#ifdef SUPPORT_DIGITAL_CROWN
    threshold = isCrownEventDragging_ ? CROWN_START_FRICTION_VELOCITY_THRESHOLD : threshold;
#endif
    if (NearZero(correctVelocity, threshold)) {
        HandleScrollEnd(correctVelocity);
        currentVelocity_ = 0.0;
#ifdef OHOS_PLATFORM
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndListFling();
        }
#endif
        return;
    }
    TriggerFrictionAnimation(mainPosition, friction, correctVelocity);
}

void Scrollable::TriggerFrictionAnimation(float mainPosition, float friction, float correctVelocity)
{
    // change motion param when list item need to be center of screen on watch
    FixScrollMotion(mainPosition, correctVelocity);
    currentVelocity_ = 0.0;
    lastPosition_ = currentPos_;
    frictionVelocity_ = initVelocity_;
    frictionOffsetProperty_->Set(mainPosition);
    float response = fabs(2 * ACE_PI / (FRICTION_SCALE * friction));
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(response, 1.0f, 0.0f);
    AnimationOption option;
    option.SetCurve(curve);
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    option.SetFinishCallbackType(FinishCallbackType::LOGICALLY);
    frictionOffsetProperty_->SetThresholdType(ThresholdType::LAYOUT);
    frictionOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    ACE_SCOPED_TRACE("Scrollable friction animation start, start:%f, end:%f, vel:%f, id:%d, tag:%s", mainPosition,
        finalPosition_, initVelocity_, nodeId_, nodeTag_.c_str());
    frictionOffsetProperty_->AnimateWithVelocity(
        option, finalPosition_, initVelocity_, [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->state_ = AnimationState::IDLE;
            ACE_SCOPED_TRACE(
                "Scrollable friction animation finish, id:%d, tag:%s", scroll->nodeId_, scroll->nodeTag_.c_str());
            scroll->ProcessScrollMotionStop();
        });
    state_ = AnimationState::FRICTION;
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->RequestFrame();
    lastVsyncTime_ = context->GetVsyncTime();
}

void Scrollable::SetDelayedTask()
{
    SetContinuousDragStatus(true);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    task_.Reset([weak = WeakClaim(this)] {
        auto drag = weak.Upgrade();
        if (drag) {
            drag->ResetContinueDragCount();
            drag->SetContinuousDragStatus(false);
        }
    });
    taskExecutor.PostDelayedTask(task_, DRAG_INTERVAL_TIME, "ArkUIScrollDragInterval");
}

void Scrollable::MarkNeedFlushAnimationStartTime()
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->MarkNeedFlushAnimationStartTime();
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
    if (std::abs(delta) < MULTI_FLING_DISTANCE) {
        ResetContinueDragCount();
        preGain_ = gain;
        return gain;
    }
    if (!continuousSlidingCallback_) {
        preGain_ = gain;
        return gain;
    }
    auto screenHeight = continuousSlidingCallback_();
    if (delta == 0 || screenHeight == 0) {
        preGain_ = gain;
        return gain;
    }
    if (dragCount_ >= FIRST_THRESHOLD && dragCount_ < SECOND_THRESHOLD) {
        if (Negative(lastPos_ / delta)) {
            ResetContinueDragCount();
            preGain_ = gain;
            return gain;
        }
        cap = CAP_COEFFICIENT * (dragCount_ - 1);
        gain = (LessNotEqual(cap, std::abs(delta) / screenHeight * (dragCount_ - 1)))
                   ? preGain_ + cap
                   : preGain_ + std::abs(delta) / screenHeight * (dragCount_ - 1);
    } else if (dragCount_ >= SECOND_THRESHOLD) {
        if (Negative(lastPos_ / delta)) {
            ResetContinueDragCount();
            preGain_ = gain;
            return gain;
        }
        cap = CAP_FIXED_VALUE;
        gain = (LessNotEqual(cap, preGain_ + std::abs(delta) / screenHeight * (dragCount_ - 1)))
                   ? cap
                   : preGain_ + std::abs(delta) / screenHeight * (dragCount_ - 1);
    }
    preGain_ = gain;
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

float Scrollable::GetFrictionVelocityByFinalPosition(
    float final, float position, float friction, float signum, float threshold)
{
    return DEFAULT_THRESHOLD * threshold * signum - (final - position) * friction;
}

void Scrollable::FixScrollMotion(float position, float initVelocity)
{
#ifdef WEARABLE_PRODUCT
    float signum = 0.0;
    if (!NearZero(initVelocity)) {
        signum = GreatNotEqual(initVelocity, 0.0) ? 1.0 : -1.0;
    }
    if (frictionOffsetProperty_ && needCenterFix_ && watchFixCallback_) {
        float finalPosition = watchFixCallback_(GetFinalPosition(), position);
        if (!NearEqual(finalPosition, GetFinalPosition(), DISTANCE_EPSILON)) {
            float friction = friction_;
            float velocity = GetFrictionVelocityByFinalPosition(finalPosition, position, friction, signum);

            // fix again when velocity is less than velocity threshold
            if (!NearEqual(finalPosition, GetFinalPosition(), DISTANCE_EPSILON)) {
                velocity = GetFrictionVelocityByFinalPosition(finalPosition, position, friction, signum, 0.0f);
            }
            initVelocity_ = velocity;
            finalPosition_ = mainPosition + initVelocity_ / (friction * -FRICTION_SCALE);
        }
    }
#endif
}

void Scrollable::StartListSnapAnimation(float predictSnapOffset, float scrollSnapVelocity, bool fromScrollBar)
{
    endPos_ = currentPos_ + predictSnapOffset;
    finalPosition_ = endPos_;
    snapAnimationFromScrollBar_ = fromScrollBar;
    AnimationOption option;
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    if (!snapOffsetProperty_) {
        GetSnapProperty();
    }
    snapOffsetProperty_->Set(currentPos_);
    snapOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    ACE_SCOPED_TRACE("List snap animation start, start:%f, end:%f, vel:%f, id:%d", currentPos_, endPos_,
        scrollSnapVelocity, nodeId_);
    updateSnapAnimationCount_++;
    snapOffsetProperty_->AnimateWithVelocity(
        option, endPos_, scrollSnapVelocity, [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            ACE_SCOPED_TRACE("List snap animation finish, id:%d", scroll->nodeId_);
            scroll->updateSnapAnimationCount_--;
            if (scroll->updateSnapAnimationCount_ == 0) {
                scroll->state_ = AnimationState::IDLE;
                scroll->axisSnapDistance_ = 0.f;
                scroll->ProcessScrollSnapStop();
            }
            scroll->snapAnimationFromScrollBar_ = false;
        });
    state_ = AnimationState::SNAP;
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    lastVsyncTime_ = context->GetVsyncTime();
    MarkNeedFlushAnimationStartTime();
}

void Scrollable::StartScrollSnapAnimation(float scrollSnapDelta, float scrollSnapVelocity, bool fromScrollBar)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE,
        "The snap delta of scroll motion is %{public}f, "
        "The snap velocity of scroll motion is %{public}f",
        scrollSnapDelta, scrollSnapVelocity);
    if (NearZero(scrollSnapDelta)) {
        return;
    }
    endPos_ = currentPos_ + scrollSnapDelta;
    finalPosition_ = endPos_;
    snapAnimationFromScrollBar_ = fromScrollBar;
    ACE_SCOPED_TRACE("Scroll snap animation start, start:%f, end:%f, vel:%f, id:%d", currentPos_, endPos_,
        scrollSnapVelocity, nodeId_);
    AnimationOption option;
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    auto minimumAmplitudeRatio = DEFAULT_MINIMUM_AMPLITUDE_PX / std::abs(scrollSnapDelta);
    minimumAmplitudeRatio = std::min(minimumAmplitudeRatio, RESPONSIVE_SPRING_AMPLITUDE_RATIO);
    if (LessNotEqualCustomPrecision(minimumAmplitudeRatio,
        ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_AMPLITUDE_RATIO)) {
        curve->UpdateMinimumAmplitudeRatio(minimumAmplitudeRatio);
    }
    option.SetCurve(curve);
    if (!snapOffsetProperty_) {
        GetSnapProperty();
    }
    snapOffsetProperty_->Set(currentPos_);
    snapOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    updateSnapAnimationCount_++;
    snapOffsetProperty_->AnimateWithVelocity(
        option, endPos_, scrollSnapVelocity, [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->updateSnapAnimationCount_--;
            if (scroll->updateSnapAnimationCount_ == 0) {
                scroll->state_ = AnimationState::IDLE;
                scroll->nextStep_.reset();
                scroll->axisSnapDistance_ = 0.f;
                scroll->snapDirection_ = SnapDirection::NONE;
                ACE_SCOPED_TRACE("Scroll snap animation finish, id:%d", scroll->nodeId_);
                scroll->ProcessScrollMotionStop();
            }
            scroll->snapAnimationFromScrollBar_ = false;
        });
    state_ = AnimationState::SNAP;
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    lastVsyncTime_ = context->GetVsyncTime();
}

void Scrollable::UpdateScrollSnapStartOffset(double offset)
{
    UpdateScrollSnapEndWithOffset(offset);
}

void Scrollable::ProcessListSnapMotion(double position)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "Current Pos is %{public}f, position is %{public}f", currentPos_, position);
    currentVelocity_ = snapVelocity_;
    auto source = snapAnimationFromScrollBar_ ? SCROLL_FROM_BAR_FLING : SCROLL_FROM_ANIMATION;
    if (NearEqual(currentPos_, position)) {
        UpdateScrollPosition(0.0, source);
    } else {
        auto mainDelta = position - currentPos_;
        HandleScroll(mainDelta, source, NestedState::GESTURE);
        if (!moved_ && state_ == AnimationState::SNAP) {
            StopSnapAnimation();
        }
    }
    if (LessOrEqual(std::abs(currentPos_ - position), 1)) {
        // trace stop at OnScrollStop
        AceAsyncTraceBeginCommercial(
            nodeId_, (TRAILING_ANIMATION + std::to_string(nodeId_) + std::string(" ") + nodeTag_).c_str());
    }
    currentPos_ = position;
    if (canOverScroll_ && state_ == AnimationState::SNAP) {
        if (source != SCROLL_FROM_BAR_FLING) {
            scrollPause_ = true;
            skipRestartSpring_ = true;
            MarkNeedFlushAnimationStartTime();
        }
        StopSnapAnimation();
    }
}

void Scrollable::ProcessScrollSnapStop()
{
    if (scrollPause_) {
        scrollPause_ = false;
        HandleOverScroll(currentVelocity_);
    } else {
        OnAnimateStop();
    }
}

void Scrollable::OnAnimateStop()
{
    HandleScrollEnd(std::nullopt);
    currentVelocity_ = 0.0;
    if (isTouching_ || isDragUpdateStop_) {
        return;
    }
    moved_ = false;
#ifdef OHOS_PLATFORM
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndListFling();
    }
#endif
#if !defined(PREVIEW)
    LayoutInspector::SupportInspector();
#endif
}

void Scrollable::StartSpringMotion(
    double mainPosition, double mainVelocity, const ExtentPair& extent, const ExtentPair& initExtent)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE,
        "position is %{public}f, mainVelocity is %{public}f, minExtent is "
        "%{public}f, maxExtent is %{public}f, initMinExtent is %{public}f, initMaxExtent is %{public}f",
        mainPosition, mainVelocity, extent.Leading(), extent.Trailing(), initExtent.Leading(), initExtent.Trailing());
    if (state_ == AnimationState::SPRING || (skipRestartSpring_ && NearEqual(mainVelocity, 0.0f, 0.001f))) {
        return;
    }
    currentPos_ = mainPosition;
    if (mainPosition > initExtent.Trailing() || NearEqual(mainPosition, initExtent.Trailing(), 0.01f)) {
        finalPosition_ = extent.Trailing();
    } else if (mainPosition < initExtent.Leading() || NearEqual(mainPosition, initExtent.Leading(), 0.01f)) {
        finalPosition_ = extent.Leading();
    } else {
        return;
    }

    if (!springOffsetProperty_) {
        GetSpringProperty();
    }
    springAnimationCount_++;
    if (AnimationUtils::IsImplicitAnimationOpen()) {
        AnimationUtils::ExecuteWithoutAnimation([weak = AceType::WeakClaim(this), mainPosition]() {
            auto scrollable = weak.Upgrade();
            CHECK_NULL_VOID(scrollable);
            scrollable->springOffsetProperty_->Set(mainPosition);
        });
    } else {
        springOffsetProperty_->Set(mainPosition);
    }
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(springResponse_, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    springOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    ACE_SCOPED_TRACE("Scrollable spring animation start, start:%f, end:%f, vel:%f, id:%d, tag:%s", mainPosition,
        finalPosition_, mainVelocity, nodeId_, nodeTag_.c_str());
    lastVsyncTime_ = static_cast<uint64_t>(GetSysTimestamp());
    springOffsetProperty_->AnimateWithVelocity(
        option, finalPosition_, mainVelocity, [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->springAnimationCount_--;
            ACE_SCOPED_TRACE(
                "Scrollable spring animation finish, id:%d, tag:%s", scroll->nodeId_, scroll->nodeTag_.c_str());
            // avoid current animation being interrupted by the prev animation's finish callback
            // and triggering onScrollStop when spring animation turns to friction animation.
            if (scroll->springAnimationCount_ > 0 || scroll->scrollPause_) {
                scroll->scrollPause_ = false;
                return;
            }
            scroll->state_ = AnimationState::IDLE;
            scroll->currentVelocity_ = 0.0;
            scroll->OnAnimateStop();
        });
    state_ = AnimationState::SPRING;
    skipRestartSpring_ = false;
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->RequestFrame();
}

void Scrollable::UpdateSpringMotion(double mainPosition, const ExtentPair& extent, const ExtentPair& initExtent)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE,
        "position is %{public}f, minExtent is "
        "%{public}f, maxExtent is %{public}f, initMinExtent is %{public}f, initMaxExtent is %{public}f",
        mainPosition, extent.Leading(), extent.Trailing(), initExtent.Leading(), initExtent.Trailing());
    if (state_ != AnimationState::SPRING || !springOffsetProperty_) {
        return;
    }
    float finalPosition = 0.0f;
    if (mainPosition > initExtent.Trailing() || NearEqual(mainPosition, initExtent.Trailing())) {
        finalPosition = extent.Trailing();
    } else if (mainPosition < initExtent.Leading() || NearEqual(mainPosition, initExtent.Leading())) {
        finalPosition = extent.Leading();
    } else {
        return;
    }

    finalPosition = finalPosition_ + (finalPosition - mainPosition) - (finalPosition_ - currentPos_);
    if (NearEqual(finalPosition, finalPosition_, SPRING_ACCURACY)) {
        return;
    }
    finalPosition_ = finalPosition;
    springAnimationCount_++;
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    springOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    ACE_SCOPED_TRACE("Scrollable spring animation update, start:%f, end:%f, id:%d, tag:%s", mainPosition,
        finalPosition_, nodeId_, nodeTag_.c_str());
    AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this)]() {
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->springOffsetProperty_->Set(scroll->finalPosition_);
            scroll->state_ = AnimationState::SPRING;
        },
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->springAnimationCount_--;
            // avoid current animation being interrupted by the prev animation's finish callback
            if (scroll->springAnimationCount_ > 0) {
                return;
            }
            ACE_SCOPED_TRACE(
                "Scrollable updated spring animation finish, id:%d, tag:%s", scroll->nodeId_, scroll->nodeTag_.c_str());
            scroll->state_ = AnimationState::IDLE;
            scroll->currentVelocity_ = 0.0;
            scroll->OnAnimateStop();
        });
    state_ = AnimationState::SPRING;
    skipRestartSpring_ = false;
}

void Scrollable::ProcessScrollMotionStop()
{
    if (needScrollSnapChange_ && startSnapAnimationCallback_ && frictionOffsetProperty_) {
        needScrollSnapChange_ = false;
        SnapAnimationOptions snapAnimationOptions = {
            .snapDelta = GetFinalPosition() - currentPos_,
            .animationVelocity = currentVelocity_,
        };
        CHECK_NULL_VOID(!startSnapAnimationCallback_(snapAnimationOptions));
    }
    // spring effect special process
    if (scrollPause_) {
        scrollPause_ = false;
        state_ = AnimationState::TRANSITION;
        HandleOverScroll(currentVelocity_);
        if (state_ == AnimationState::TRANSITION) {
            // didn't trigger spring animation
            state_ = AnimationState::IDLE;
        }
        return;
    }

    if (isDragUpdateStop_) {
        return;
    }
    moved_ = false;
    HandleScrollEnd(std::nullopt);
#ifdef OHOS_PLATFORM
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndListFling();
    }
#endif
    currentVelocity_ = 0.0;
#if !defined(PREVIEW)
    LayoutInspector::SupportInspector();
#endif
}

void Scrollable::ProcessSpringMotion(double position)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "Current Pos is %{public}f, position is %{public}f", currentPos_, position);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    uint64_t currentVsync = context->GetVsyncTime();
    uint64_t diff = currentVsync - lastVsyncTime_;
    if (diff < MAX_VSYNC_DIFF_TIME && diff > MIN_DIFF_VSYNC) {
        currentVelocity_ = (position - currentPos_) / diff * MILLOS_PER_NANO_SECONDS;
    }
    lastVsyncTime_ = currentVsync;
    if (LessOrEqual(std::abs(currentPos_ - position), 1)) {
        // trace stop at OnScrollStop
        if (!isFadingAway_) {
            AceAsyncTraceBeginCommercial(
                nodeId_, (TRAILING_ANIMATION + std::to_string(nodeId_) + std::string(" ") + nodeTag_).c_str());
        } else {
            ACE_SCOPED_TRACE("Spring to same position");
        }
    }
    auto distance = currentPos_ - finalPosition_;
    auto nextDistance = position - finalPosition_;
    isFadingAway_ = GreatNotEqual(std::abs(nextDistance), std::abs(distance));
    auto delta = position - currentPos_;
    if (distance * nextDistance < 0) {
        double currentVelocity = currentVelocity_;
        scrollPause_ = true;
        MarkNeedFlushAnimationStartTime();
        StopSpringAnimation();
        ACE_SCOPED_TRACE("change direction in spring animation and start fling animation, distance:%f, "
                         "nextDistance:%f, nodeId:%d, tag:%s",
            distance, nextDistance, nodeId_, nodeTag_.c_str());
        // only handle offsets that are out of bounds
        delta = finalPosition_ - currentPos_;
        moved_ = UpdateScrollPosition(delta, SCROLL_FROM_ANIMATION_SPRING);
        // remainVelocityCallback_ will pass the velocity to the child component
        if (!remainVelocityCallback_ || !remainVelocityCallback_(currentVelocity)) {
            StartScrollAnimation(position, currentVelocity);
        }
    } else {
        moved_ = UpdateScrollPosition(delta, SCROLL_FROM_ANIMATION_SPRING);
    }
    if (!moved_) {
        StopSpringAnimation();
    }
    currentPos_ = position;
}

double Scrollable::CalcNextStep(double position, double mainDelta)
{
    auto finalDelta = finalPosition_ - currentPos_;
    if (GreatNotEqual(std::abs(finalDelta), SCROLL_SNAP_MIN_STEP_THRESHOLD)) {
        return mainDelta;
    }
    if (LessOrEqual(std::abs(finalDelta), SCROLL_SNAP_MIN_STEP)) {
        return finalDelta;
    }
    if (nextStep_.has_value()) {
        return nextStep_.value();
    }
    if (LessOrEqual(std::abs(mainDelta), SCROLL_SNAP_MIN_STEP)) {
        nextStep_ = Positive(finalDelta) ? SCROLL_SNAP_MIN_STEP : -SCROLL_SNAP_MIN_STEP;
        mainDelta = nextStep_.value();
    }
    return mainDelta;
}

void Scrollable::ProcessScrollMotion(double position, int32_t source)
{
    currentVelocity_ = state_ == AnimationState::SNAP ? snapVelocity_ : frictionVelocity_;
    auto mainDelta = position - currentPos_;
#ifdef SUPPORT_DIGITAL_CROWN
    if (state_ == AnimationState::SNAP) {
        mainDelta = CalcNextStep(position, mainDelta);
        position = currentPos_ + mainDelta;
    }
#endif
    if (needScrollSnapToSideCallback_) {
        needScrollSnapChange_ = needScrollSnapToSideCallback_(mainDelta);
    }
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "position is %{public}f, currentVelocity_ is %{public}f, "
        "currentPos_ is %{public}f, needScrollSnapChange_ is %{public}u", position, currentVelocity_,
        currentPos_, needScrollSnapChange_);
    if (LessOrEqual(std::abs(mainDelta), 1)) {
        // trace stop at OnScrollStop
        AceAsyncTraceBeginCommercial(
            nodeId_, (TRAILING_ANIMATION + std::to_string(nodeId_) + std::string(" ") + nodeTag_).c_str());
    }
    // UpdateScrollPosition return false, means reach to scroll limit.
    source = snapAnimationFromScrollBar_ && state_ == AnimationState::SNAP ? SCROLL_FROM_BAR_FLING : source;
    HandleScroll(mainDelta, source, NestedState::GESTURE);
    if (!moved_) {
        ResetContinueDragCount();
        StopFrictionAnimation();
        StopSnapAnimation();
    }
    currentPos_ = position;
#ifdef SUPPORT_DIGITAL_CROWN
    if (state_ == AnimationState::SNAP && NearEqual(currentPos_, finalPosition_)) {
        StopSnapAnimation();
    }
#endif
    // spring effect special process
    if ((canOverScroll_ && source != SCROLL_FROM_AXIS) || needScrollSnapChange_) {
        ACE_SCOPED_TRACE("scrollPause set true to stop ProcessScrollMotion, canOverScroll:%u, needScrollSnapChange:%u, "
                         "nodeId:%d, tag:%s",
            canOverScroll_, needScrollSnapChange_, nodeId_, nodeTag_.c_str());
        if (source != SCROLL_FROM_BAR_FLING) {
            scrollPause_ = true;
            skipRestartSpring_ = true;
            MarkNeedFlushAnimationStartTime();
        }
        ResetContinueDragCount();
        StopFrictionAnimation();
        StopSnapAnimation();
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
    if (!overScrollCallback_) {
        if (edgeEffect_ == EdgeEffect::SPRING) {
            ProcessScrollOverCallback(velocity);
            return true;
        }
        if (scrollEndCallback_) {
            scrollEndCallback_();
        }
        return false;
    }
    // call NestableScrollContainer::HandleOverScroll
    return overScrollCallback_(velocity);
}

void Scrollable::SetSlipFactor(double SlipFactor)
{
    slipFactor_ = std::clamp(SlipFactor, -ADJUSTABLE_VELOCITY, ADJUSTABLE_VELOCITY);
}

void Scrollable::UpdateScrollSnapEndWithOffset(double offset)
{
    if (state_ == AnimationState::SNAP) {
        MarkNeedFlushAnimationStartTime();
        AnimationOption option;
        option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
        auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
        option.SetCurve(curve);
        if (!snapOffsetProperty_) {
            GetSnapProperty();
        }
        updateSnapAnimationCount_++;
        endPos_ -= offset;
        finalPosition_ = endPos_;
        snapOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
        AnimationUtils::StartAnimation(
            option,
            [weak = AceType::WeakClaim(this)]() {
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                scroll->snapOffsetProperty_->Set(scroll->endPos_);
                scroll->state_ = AnimationState::SNAP;
            },
            [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
                ContainerScope scope(id);
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                scroll->updateSnapAnimationCount_--;
                // avoid current animation being interrupted by the prev animation's finish callback
                if (scroll->updateSnapAnimationCount_ == 0) {
                    scroll->snapDirection_ = SnapDirection::NONE;
                    scroll->state_ = AnimationState::IDLE;
                    scroll->ProcessScrollSnapStop();
                }
            });
        state_ = AnimationState::SNAP;
    }
}

std::optional<float> Scrollable::GetPredictSnapOffset() const
{
    if (state_ == AnimationState::SNAP) {
        return endPos_ - currentPos_;
    }
    return std::nullopt;
}

void Scrollable::AttachAnimatableProperty(const RefPtr<NodeAnimatablePropertyFloat>& property)
{
    auto host = weakHost_.Upgrade();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->AttachNodeAnimatableProperty(property);
}

RefPtr<NodeAnimatablePropertyFloat> Scrollable::GetFrictionProperty()
{
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float position) {
        auto scroll = weak.Upgrade();
        CHECK_NULL_VOID(scroll);
        if (scroll->state_ != AnimationState::FRICTION || scroll->isTouching_) {
            return;
        }
        scroll->ProcessScrollMotion(position);
        if (NearEqual(scroll->finalPosition_, position, 1.0)) {
            scroll->StopFrictionAnimation();
        }
        auto context = scroll->context_.Upgrade();
        CHECK_NULL_VOID(context);
        uint64_t currentVsync = context->GetVsyncTime();
        uint64_t diff = currentVsync - scroll->lastVsyncTime_;
        if (diff < MAX_VSYNC_DIFF_TIME && diff > MIN_DIFF_VSYNC) {
            scroll->frictionVelocity_ = (position - scroll->lastPosition_) / diff * MILLOS_PER_NANO_SECONDS;
            if (NearZero(scroll->frictionVelocity_, FRICTION_VELOCITY_THRESHOLD)) {
                scroll->StopFrictionAnimation();
                ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
            }
        }
        scroll->lastVsyncTime_ = currentVsync;
        scroll->lastPosition_ = position;
    };
    frictionOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    AttachAnimatableProperty(frictionOffsetProperty_);
    return frictionOffsetProperty_;
}

RefPtr<NodeAnimatablePropertyFloat> Scrollable::GetSpringProperty()
{
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float position) {
        auto scroll = weak.Upgrade();
        CHECK_NULL_VOID(scroll);
        if (scroll->state_ != AnimationState::SPRING) {
            return;
        }
        if (!NearEqual(scroll->finalPosition_, position, SPRING_ACCURACY)) {
            scroll->ProcessSpringMotion(position);
            return;
        }
        /*
         * In order to prevent accumulation errors, the current position is re obtained to ensure that
         * the last frame can accurately stop at the top and bottom positions.
         */
        if (scroll->currentPositionCallback_) {
            double currPos = scroll->currentPositionCallback_();
            if (NearEqual(currPos, scroll->currentPos_, 0.5)) {
                scroll->currentPos_ = currPos;
            }
        }
        scroll->StopSpringAnimation(true);
    };
    springOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    AttachAnimatableProperty(springOffsetProperty_);
    return springOffsetProperty_;
}

RefPtr<NodeAnimatablePropertyFloat> Scrollable::GetSnapProperty()
{
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float position) {
        auto scroll = weak.Upgrade();
        CHECK_NULL_VOID(scroll);
        if (scroll->state_ != AnimationState::SNAP) {
            return;
        }
        auto context = scroll->context_.Upgrade();
        CHECK_NULL_VOID(context);
        uint64_t currentVsync = context->GetVsyncTime();
        uint64_t diff = currentVsync - scroll->lastVsyncTime_;
        if (diff < MAX_VSYNC_DIFF_TIME && diff > MIN_DIFF_VSYNC) {
            scroll->snapVelocity_ = (position - scroll->currentPos_) / diff * MILLOS_PER_NANO_SECONDS;
        }
        scroll->lastVsyncTime_ = currentVsync;

        if (NearEqual(scroll->endPos_, position, SPRING_ACCURACY)) {
            if (scroll->GetSnapType() == SnapType::LIST_SNAP) {
                scroll->ProcessListSnapMotion(scroll->endPos_);
            } else if (scroll->GetSnapType() == SnapType::SCROLL_SNAP) {
                scroll->ProcessScrollMotion(scroll->endPos_);
            }
            scroll->StopSnapAnimation();
        } else {
            if (scroll->GetSnapType() == SnapType::LIST_SNAP) {
                scroll->ProcessListSnapMotion(position);
            } else if (scroll->GetSnapType() == SnapType::SCROLL_SNAP) {
                scroll->ProcessScrollMotion(position);
            }
        }
    };
    snapOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    AttachAnimatableProperty(snapOffsetProperty_);
    return snapOffsetProperty_;
}

void Scrollable::StopFrictionAnimation()
{
    if (state_ == AnimationState::FRICTION) {
        ACE_SCOPED_TRACE("StopFrictionAnimation, id:%d, tag:%s", nodeId_, nodeTag_.c_str());
        state_ = AnimationState::IDLE;
        CHECK_NULL_VOID(frictionOffsetProperty_);
        AnimationOption option;
        option.SetCurve(Curves::EASE);
        option.SetDuration(0);
        AnimationUtils::StartAnimation(
            option,
            [weak = AceType::WeakClaim(this)]() {
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                scroll->frictionOffsetProperty_->Set(scroll->currentPos_);
            },
            nullptr);
    }
}

void Scrollable::StopSpringAnimation(bool reachFinalPosition)
{
    if (state_ == AnimationState::SPRING) {
        ACE_SCOPED_TRACE(
            "StopSpringAnimation, reachFinalPosition:%u, id:%d, tag:%s", reachFinalPosition, nodeId_, nodeTag_.c_str());
        state_ = AnimationState::IDLE;
        isFadingAway_ = false;
        CHECK_NULL_VOID(springOffsetProperty_);
        AnimationOption option;
        option.SetCurve(Curves::EASE);
        option.SetDuration(0);
        AnimationUtils::StartAnimation(
            option,
            [weak = AceType::WeakClaim(this), reachFinalPosition]() {
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                if (reachFinalPosition) {
                    // ensure that the spring animation is restored to its final position.
                    scroll->ProcessSpringMotion(scroll->finalPosition_);
                    // use non final position to stop animation, otherwise the animation cannot be stoped.
                    scroll->springOffsetProperty_->Set(scroll->finalPosition_ - 1.f);
                } else {
                    // avoid top edge spring can not stop
                    scroll->springOffsetProperty_->Set(scroll->currentPos_);
                }
            },
            nullptr);
    }
    currentVelocity_ = 0.0;
}

void Scrollable::StopSnapAnimation()
{
    if (state_ == AnimationState::SNAP) {
        ACE_SCOPED_TRACE("StopSnapAnimation, animation state:%d, id:%d, tag:%s", state_, nodeId_, nodeTag_.c_str());
        state_ = AnimationState::IDLE;
        nextStep_.reset();
        CHECK_NULL_VOID(snapOffsetProperty_);
        AnimationOption option;
        option.SetCurve(Curves::EASE);
        option.SetDuration(0);
        AnimationUtils::StartAnimation(
            option,
            [weak = AceType::WeakClaim(this)]() {
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                auto position = NearEqual(scroll->currentPos_, scroll->finalPosition_) ?
                    scroll->finalPosition_ - 1.f : scroll->currentPos_;
                scroll->snapOffsetProperty_->Set(position);
            },
            nullptr);
    }
}

void Scrollable::StopAxisAnimation()
{
    CHECK_NULL_VOID(axisAnimator_);
    axisAnimator_->StopAxisAnimation();
}

inline bool Scrollable::IsMouseWheelScroll(const GestureEvent& info)
{
    return info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() != SourceTool::TOUCHPAD;
}

void Scrollable::OnCollectTouchTarget(TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
{
    if (panRecognizerNG_) {
        panRecognizerNG_->SetNodeId(frameNode->GetId());
        panRecognizerNG_->AttachFrameNode(frameNode);
        panRecognizerNG_->SetTargetComponent(targetComponent);
        panRecognizerNG_->SetIsSystemGesture(true);
        panRecognizerNG_->SetRecognizerType(GestureTypeName::PAN_GESTURE);
        result.emplace_back(panRecognizerNG_);
        responseLinkResult.emplace_back(panRecognizerNG_);
    }
}

void Scrollable::SetMaxFlingVelocity(double max)
{
    double density = PipelineBase::GetCurrentDensity();
    maxFlingVelocity_ = max * density;
}
} // namespace OHOS::Ace::NG
