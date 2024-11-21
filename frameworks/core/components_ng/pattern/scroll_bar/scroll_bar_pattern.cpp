/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BAR_DISAPPEAR_DELAY_DURATION = 2000; // 2000ms
constexpr int32_t BAR_DISAPPEAR_DURATION = 300;        // 300ms
constexpr int32_t BAR_APPEAR_DURATION = 100;           // 100ms
constexpr int32_t BAR_DISAPPEAR_FRAME_RATE = 15;       // 15fps, the expected frame rate of opacity animation
constexpr int32_t BAR_DISAPPEAR_MIN_FRAME_RATE = 0;
constexpr int32_t BAR_DISAPPEAR_MAX_FRAME_RATE = 90;
constexpr int32_t SCROLL_BAR_LAYOUT_INFO_COUNT = 120;
} // namespace

void ScrollBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    host->GetRenderContext()->SetClipToFrame(true);
}

void ScrollBarPattern::SendAccessibilityEvent(AccessibilityEventType eventType)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->OnAccessibilityEvent(eventType);
}

void ScrollBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ScrollBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto oldDisplayMode = displayMode_;
    displayMode_ = layoutProperty->GetDisplayMode().value_or(DisplayMode::AUTO);
    if (oldDisplayMode != displayMode_ && scrollBarProxy_) {
        if (displayMode_ == DisplayMode::ON) {
            StopDisappearAnimator();
        } else if (displayMode_ == DisplayMode::AUTO) {
            StartDisappearAnimator();
        }
    }
    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    if (axis_ == axis && scrollableEvent_) {
        return;
    }

    axis_ = axis;
    // scrollPosition callback
    scrollPositionCallback_ = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (source == SCROLL_FROM_START) {
            pattern->StopDisappearAnimator();
            // AccessibilityEventType::SCROLL_START
            return true;
        }
        return pattern->UpdateCurrentOffset(offset, source);
    };
    scrollEndCallback_ = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->GetDisplayMode() == DisplayMode::AUTO) {
            pattern->StartDisappearAnimator();
        }
        // AccessibilityEventType::SCROLL_END
    };

    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(axis);
    scrollableEvent_->SetInBarRegionCallback([weak = AceType::WeakClaim(this)]
        (const PointF& point, SourceType source) {
            auto scrollBarPattern = weak.Upgrade();
            CHECK_NULL_RETURN(scrollBarPattern, false);
            if (!scrollBarPattern->HasChild()
                && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                auto scrollBar = scrollBarPattern->scrollBar_;
                CHECK_NULL_RETURN(scrollBar, false);
                if (source == SourceType::MOUSE) {
                    return scrollBar->InBarHoverRegion(Point(point.GetX(), point.GetY()));
                }
                return scrollBar->InBarTouchRegion(Point(point.GetX(), point.GetY()));
            } else {
                return scrollBarPattern->childRect_.IsInRegion(point);
            }
        }
    );
    scrollableEvent_->SetBarCollectTouchTargetCallback(
        [weak = AceType::WeakClaim(this)](const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
            TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
            ResponseLinkResult& responseLinkResult) {
            auto scrollBarPattern = weak.Upgrade();
            CHECK_NULL_VOID(scrollBarPattern);
            if (!scrollBarPattern->HasChild()
                && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
                auto scrollBar = scrollBarPattern->scrollBar_;
                CHECK_NULL_VOID(scrollBar);
                scrollBar->OnCollectTouchTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            } else {
                scrollBarPattern->OnCollectTouchTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            }
        });
    gestureHub->AddScrollableEvent(scrollableEvent_);
    SetAccessibilityAction();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        SetScrollBar(DisplayMode::ON);
    }
    if (!panRecognizer_) {
        InitPanRecognizer();
    }
}

void ScrollBarPattern::SetScrollBar(DisplayMode displayMode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (displayMode == DisplayMode::OFF) {
        if (scrollBar_) {
            auto gestureHub = GetGestureHub();
            if (gestureHub) {
                gestureHub->RemoveTouchEvent(scrollBar_->GetTouchEvent());
            }
            scrollBar_.Reset();
            if (scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetOpacity(0);
            }
        }
        return;
    }
    DisplayMode oldDisplayMode = DisplayMode::OFF;
    if (!scrollBar_) {
        scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
        // set the scroll bar style
        if (GetAxis() == Axis::HORIZONTAL) {
            scrollBar_->SetPositionMode(PositionMode::BOTTOM);
            if (scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetPositionMode(PositionMode::BOTTOM);
            }
        }
        RegisterScrollBarEventTask();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        oldDisplayMode = scrollBar_->GetDisplayMode();
    }

    if (oldDisplayMode != displayMode) {
        scrollBar_->SetDisplayMode(displayMode);
        if (scrollBarOverlayModifier_ && scrollBar_->IsScrollable()) {
            scrollBarOverlayModifier_->SetOpacity(UINT8_MAX);
        }
        scrollBar_->ScheduleDisappearDelayTask();
    }
}

void ScrollBarPattern::HandleScrollBarOutBoundary(float scrollBarOutBoundaryExtent)
{
    CHECK_NULL_VOID(scrollBar_ && scrollBar_->NeedScrollBar());
    scrollBar_->SetOutBoundary(std::abs(scrollBarOutBoundaryExtent));
}

void ScrollBarPattern::UpdateScrollBarOffset()
{
    CHECK_NULL_VOID(scrollBar_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    auto viewSize = geometryNode->GetFrameSize();
    
    auto layoutProperty = host->GetLayoutProperty<ScrollBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto estimatedHeight = GetControlDistance() + (GetAxis() == Axis::VERTICAL ? viewSize.Height() : viewSize.Width());

    UpdateScrollBarRegion(scrollableNodeOffset_, estimatedHeight,
        Size(viewSize.Width(), viewSize.Height()), Offset(0.0f, 0.0f));
}

void ScrollBarPattern::UpdateScrollBarRegion(float offset, float estimatedHeight, Size viewPort, Offset viewOffset)
{
    // outer scrollbar, viewOffset is padding offset
    if (scrollBar_) {
        auto mainSize = axis_ == Axis::VERTICAL ? viewPort.Height() : viewPort.Width();
        bool scrollable = GreatNotEqual(estimatedHeight, mainSize);
        if (scrollBar_->IsScrollable() != scrollable) {
            scrollBar_->SetScrollable(scrollable);
            if (scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetOpacity(scrollable ? UINT8_MAX : 0);
            }
            if (scrollable) {
                scrollBar_->ScheduleDisappearDelayTask();
            }
        }
        Offset scrollOffset = { offset, offset };
        scrollBar_->SetReverse(IsReverse());
        scrollBar_->UpdateScrollBarRegion(viewOffset, viewPort, scrollOffset, estimatedHeight);
        scrollBar_->MarkNeedRender();
    }
}

void ScrollBarPattern::RegisterScrollBarEventTask()
{
    CHECK_NULL_VOID(scrollBar_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = GetGestureHub();
    auto inputHub = GetInputHub();
    CHECK_NULL_VOID(gestureHub);
    CHECK_NULL_VOID(inputHub);
    scrollBar_->SetGestureEvent();
    scrollBar_->SetMouseEvent();
    scrollBar_->SetHoverEvent();
    scrollBar_->SetMarkNeedRenderFunc([weak = AceType::WeakClaim(AceType::RawPtr(host))]() {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        host->MarkNeedRenderOnly();
    });

    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->scrollBarProxy_->NotifyScrollBarNode(offset, source);
        pattern->scrollPositionCallback_(0.0, SCROLL_FROM_START);
        return true;
    };
    scrollBar_->SetScrollPositionCallback(std::move(scrollCallback));

    auto scrollEnd = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->scrollBarProxy_->NotifyScrollStop();
    };
    scrollBar_->SetScrollEndCallback(std::move(scrollEnd));

    gestureHub->AddTouchEvent(scrollBar_->GetTouchEvent());
    inputHub->AddOnMouseEvent(scrollBar_->GetMouseEvent());
    inputHub->AddOnHoverEvent(scrollBar_->GetHoverEvent());
}

bool ScrollBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    bool updateFlag = false;
    if (!HasChild() && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        updateFlag = true;
    } else {
        auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
        CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
        auto layoutAlgorithm = DynamicCast<ScrollBarLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
        CHECK_NULL_RETURN(layoutAlgorithm, false);
        scrollableDistance_ = layoutAlgorithm->GetScrollableDistance();
    }
    if (displayMode_ != DisplayMode::OFF) {
        updateFlag = UpdateScrollBarDisplay() || updateFlag;
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        updateFlag = CheckChildState() || updateFlag;
    }
    return updateFlag;
}

void ScrollBarPattern::OnColorConfigurationUpdate()
{
    CHECK_NULL_VOID(scrollBar_);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(theme);
    scrollBar_->SetForegroundColor(theme->GetForegroundColor());
    scrollBar_->SetBackgroundColor(theme->GetBackgroundColor());
}

bool ScrollBarPattern::UpdateScrollBarDisplay()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (controlDistanceChanged_) {
        controlDistanceChanged_ = false;
        if (!Positive(controlDistance_)) {
            SetOpacity(0);
            return true;
        }
        SetOpacity(UINT8_MAX);
        if (displayMode_ == DisplayMode::AUTO) {
            StartDisappearAnimator();
        }
        return true;
    }
    if (!Positive(controlDistance_)) {
        SetOpacity(0);
        return true;
    }
    return false;
}

bool ScrollBarPattern::IsAtTop() const
{
    return LessOrEqual(currentOffset_, 0.0);
}

bool ScrollBarPattern::IsAtBottom() const
{
    return GreatOrEqual(currentOffset_, scrollableDistance_);
}

void ScrollBarPattern::ValidateOffset()
{
    if (scrollableDistance_ <= 0.0f) {
        return;
    }
    currentOffset_ = std::clamp(currentOffset_, 0.0f, scrollableDistance_);
}

bool ScrollBarPattern::UpdateCurrentOffset(float delta, int32_t source)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (NearZero(delta) || axis_ == Axis::NONE) {
        return false;
    }

    lastOffset_ = currentOffset_;
    currentOffset_ += delta;
    if (scrollBarProxy_ && lastOffset_ != currentOffset_) {
        scrollBarProxy_->NotifyScrollableNode(-delta, source, AceType::WeakClaim(this));
    }
    AddScrollBarLayoutInfo();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    }
    return true;
}

void ScrollBarPattern::AddScrollBarLayoutInfo()
{
    if (outerScrollBarLayoutInfos_.size() >= SCROLL_BAR_LAYOUT_INFO_COUNT) {
        outerScrollBarLayoutInfos_.pop_front();
    }
    outerScrollBarLayoutInfos_.push_back(OuterScrollBarLayoutInfo({
        .layoutTime_ = GetSysTimestamp(),
        .currentOffset_ = currentOffset_,
        .scrollableNodeOffset_ = scrollableNodeOffset_,
    }));
}

void ScrollBarPattern::GetAxisDumpInfo()
{
    switch (axis_) {
        case Axis::NONE: {
            DumpLog::GetInstance().AddDesc("Axis: NONE");
            break;
        }
        case Axis::VERTICAL: {
            DumpLog::GetInstance().AddDesc("Axis: VERTICAL");
            break;
        }
        case Axis::HORIZONTAL: {
            DumpLog::GetInstance().AddDesc("Axis: HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            DumpLog::GetInstance().AddDesc("Axis: FREE");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollBarPattern::GetDisplayModeDumpInfo()
{
    switch (displayMode_) {
        case DisplayMode::OFF: {
            DumpLog::GetInstance().AddDesc("outerScrollBarState: OFF");
            break;
        }
        case DisplayMode::AUTO: {
            DumpLog::GetInstance().AddDesc("outerScrollBarState: AUTO");
            break;
        }
        case DisplayMode::ON: {
            DumpLog::GetInstance().AddDesc("outerScrollBarState: ON");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollBarPattern::GetPanDirectionDumpInfo()
{
    if (panRecognizer_) {
        switch (panRecognizer_->GetAxisDirection()) {
            case Axis::NONE: {
                DumpLog::GetInstance().AddDesc("panDirection: NONE");
                break;
            }
            case Axis::VERTICAL: {
                DumpLog::GetInstance().AddDesc("panDirection: VERTICAL");
                break;
            }
            case Axis::HORIZONTAL: {
                DumpLog::GetInstance().AddDesc("panDirection: HORIZONTAL");
                break;
            }
            case Axis::FREE: {
                DumpLog::GetInstance().AddDesc("panDirection: FREE");
                break;
            }
            default: {
                break;
            }
        }
    } else {
        DumpLog::GetInstance().AddDesc("panDirection is null");
    }
}

void ScrollBarPattern::DumpAdvanceInfo()
{
    GetAxisDumpInfo();
    GetDisplayModeDumpInfo();
    GetPanDirectionDumpInfo();
    hasChild_ ? DumpLog::GetInstance().AddDesc("hasChild: true") : DumpLog::GetInstance().AddDesc("hasChild: false");
    preFrameChildState_ ? DumpLog::GetInstance().AddDesc("preFrameChildState: true")
                        : DumpLog::GetInstance().AddDesc("preFrameChildState: false");
    if (!hasChild_ && scrollBar_) {
        scrollBar_->DumpAdvanceInfo();
    }
    DumpLog::GetInstance().AddDesc(std::string("childRect: ").append(childRect_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("scrollableDistance: ").append(std::to_string(scrollableDistance_)));
    DumpLog::GetInstance().AddDesc(std::string("controlDistance_: ").append(std::to_string(controlDistance_)));
    DumpLog::GetInstance().AddDesc("==========================outerScrollBarLayoutInfos==========================");
    for (const auto& info : outerScrollBarLayoutInfos_) {
        DumpLog::GetInstance().AddDesc(info.ToString());
    }
    DumpLog::GetInstance().AddDesc("==========================outerScrollBarLayoutInfos==========================");
}

void ScrollBarPattern::StartDisappearAnimator()
{
    if (!Positive(controlDistance_)) {
        return;
    }
    if (disapplearDelayTask_) {
        disapplearDelayTask_.Cancel();
    }
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    SetOpacity(UINT8_MAX);
    disapplearDelayTask_.Reset([weak = WeakClaim(this)] {
        auto scrollBar = weak.Upgrade();
        CHECK_NULL_VOID(scrollBar);
        AnimationOption option;
        if (!scrollBar->HasChild()
            && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            option.SetCurve(Curves::SHARP);
        } else {
            option.SetCurve(Curves::FRICTION);
        }
        option.SetDuration(BAR_DISAPPEAR_DURATION);
        option.SetFrameRateRange(AceType::MakeRefPtr<FrameRateRange>(
            BAR_DISAPPEAR_MIN_FRAME_RATE, BAR_DISAPPEAR_MAX_FRAME_RATE, BAR_DISAPPEAR_FRAME_RATE));
        auto disappearAnimation = AnimationUtils::StartAnimation(option, [weak]() {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->SetOpacity(0);
        });
        scrollBar->SetDisappearAnimation(disappearAnimation);
    });
    taskExecutor->PostDelayedTask(disapplearDelayTask_, TaskExecutor::TaskType::UI, BAR_DISAPPEAR_DELAY_DURATION,
        "ArkUIScrollBarDisappearAnimation");
}

void ScrollBarPattern::StopDisappearAnimator()
{
    if (!Positive(controlDistance_)) {
        return;
    }
    if (disapplearDelayTask_) {
        disapplearDelayTask_.Cancel();
    }
    if (disappearAnimation_) {
        AnimationUtils::StopAnimation(disappearAnimation_);
    }
    if (!HasChild()
        && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        AnimationOption option;
        option.SetCurve(Curves::SHARP);
        option.SetDuration(BAR_APPEAR_DURATION);
        option.SetFrameRateRange(AceType::MakeRefPtr<FrameRateRange>(
        BAR_DISAPPEAR_MIN_FRAME_RATE, BAR_DISAPPEAR_MAX_FRAME_RATE, BAR_DISAPPEAR_FRAME_RATE));
        AnimationUtils::StartAnimation(option, [weak = WeakClaim(this)]() {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->SetOpacity(UINT8_MAX);
        });
    } else {
        SetOpacity(UINT8_MAX);
    }
}

void ScrollBarPattern::SetOpacity(uint8_t value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    opacity_ = value;
    renderContext->UpdateOpacity(static_cast<double>(value) / UINT8_MAX);
    host->MarkNeedRenderOnly();
}

void ScrollBarPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->GetAxis() == Axis::NONE || pattern->GetScrollableDistance() == 0.0f) {
            return;
        }
        pattern->UpdateCurrentOffset(pattern->GetChildOffset(), SCROLL_FROM_BAR);
        // AccessibilityEventType::SCROLL_END
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->GetAxis() == Axis::NONE || pattern->GetScrollableDistance() == 0.0f) {
            return;
        }
        pattern->UpdateCurrentOffset(-pattern->GetChildOffset(), SCROLL_FROM_BAR);
        // AccessibilityEventType::SCROLL_END
    });
}

void ScrollBarPattern::InitPanRecognizer()
{
    PanDirection panDirection;
    panDirection.type = axis_ == Axis::HORIZONTAL ? PanDirection::HORIZONTAL : PanDirection::VERTICAL;
    const static int32_t PLATFORM_VERSION_TEN = 10;
    float distance = DEFAULT_PAN_DISTANCE.Value();
    auto context = PipelineContext::GetCurrentContext();
    if (context && (context->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN)) {
        distance = DEFAULT_PAN_DISTANCE.ConvertToPx();
    }
    panRecognizer_ = MakeRefPtr<PanRecognizer>(1, panDirection, distance);
    panRecognizer_->SetOnActionUpdate([weakBar = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleDragUpdate(info);
        }
    });
    panRecognizer_->SetOnActionEnd([weakBar = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleDragEnd(info);
        }
    });
    panRecognizer_->SetOnActionStart([weakBar = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleDragStart(info);
        }
    });
    panRecognizer_->SetOnActionCancel([weakBar = AceType::WeakClaim(this)]() {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            GestureEvent info;
            scrollBar->HandleDragEnd(info);
        }
    });
}

void ScrollBarPattern::HandleDragStart(const GestureEvent& info)
{
    StopMotion();
    SetDragStartPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "outer scrollBar drag start");
    ACE_SCOPED_TRACE("outer scrollBar HandleDragStart");
    if (scrollPositionCallback_) {
        if (scrollBarProxy_) {
            scrollBarProxy_->NotifyScrollStart();
            scrollBarProxy_->SetScrollSnapTrigger_(true);
        }
        scrollPositionCallback_(0, SCROLL_FROM_START);
    }
}

void ScrollBarPattern::HandleDragUpdate(const GestureEvent& info)
{
    if (scrollPositionCallback_) {
        auto offset = info.GetMainDelta();
        if (IsReverse()) {
            offset = -offset;
        }
        // The offset of the mouse wheel and gesture is opposite.
        if (info.GetInputEventType() == InputEventType::AXIS && !NearZero(controlDistance_)) {
            offset = - offset * scrollableDistance_ / controlDistance_;
        }
        ACE_SCOPED_TRACE("outer scrollBar HandleDragUpdate offset:%f", offset);
        scrollPositionCallback_(offset, SCROLL_FROM_BAR);
    }
}

void ScrollBarPattern::HandleDragEnd(const GestureEvent& info)
{
    auto velocity = IsReverse() ? -info.GetMainVelocity() : info.GetMainVelocity();
    TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "outer scrollBar drag end, velocity is %{public}f", velocity);
    ACE_SCOPED_TRACE("outer scrollBar HandleDragEnd velocity:%f", velocity);
    SetDragEndPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    if (NearZero(velocity) || info.GetInputEventType() == InputEventType::AXIS) {
        if (scrollEndCallback_) {
            if (scrollBarProxy_) {
                scrollBarProxy_->NotifyScrollStop();
                scrollBarProxy_->SetScrollSnapTrigger_(false);
            }
            scrollEndCallback_();
        }
        return;
    }
    frictionPosition_ = 0.0;
    if (frictionMotion_) {
        frictionMotion_->Reset(friction_, 0, velocity);
    } else {
        frictionMotion_ = AceType::MakeRefPtr<FrictionMotion>(friction_, 0, velocity);
        frictionMotion_->AddListener([weakBar = AceType::WeakClaim(this)](double value) {
            auto scrollBar = weakBar.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->ProcessFrictionMotion(value);
        });
    }
    CHECK_NULL_VOID(!scrollBarProxy_ || !scrollBarProxy_->NotifySnapScroll(-(frictionMotion_->GetFinalPosition()),
        velocity, GetScrollableDistance(), static_cast<float>(GetDragOffset())));
    scrollBarProxy_->SetScrollSnapTrigger_(false);
    if (!frictionController_) {
        frictionController_ = CREATE_ANIMATOR(PipelineContext::GetCurrentContext());
        frictionController_->AddStopListener([weakBar = AceType::WeakClaim(this)]() {
            auto scrollBar = weakBar.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->ProcessFrictionMotionStop();
        });
    }
    frictionController_->PlayMotion(frictionMotion_);
}

void ScrollBarPattern::ProcessFrictionMotion(double value)
{
    if (scrollPositionCallback_) {
        auto offset = value - frictionPosition_;
        scrollPositionCallback_(offset, SCROLL_FROM_BAR_FLING);
    }
    frictionPosition_ = value;
}

void ScrollBarPattern::ProcessFrictionMotionStop()
{
    if (scrollEndCallback_) {
        if (scrollBarProxy_) {
            scrollBarProxy_->NotifyScrollStop();
        }
        scrollEndCallback_();
    }
}

void ScrollBarPattern::OnCollectTouchTarget(const OffsetF& coordinateOffset,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
{
    if (panRecognizer_) {
        panRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        panRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        panRecognizer_->SetNodeId(frameNode->GetId());
        panRecognizer_->AttachFrameNode(frameNode);
        panRecognizer_->SetTargetComponent(targetComponent);
        panRecognizer_->SetIsSystemGesture(true);
        panRecognizer_->SetRecognizerType(GestureTypeName::PAN_GESTURE);
        result.emplace_front(panRecognizer_);
        responseLinkResult.emplace_back(panRecognizer_);
    }
}

bool ScrollBarPattern::IsReverse() const
{
    return isReverse_;
}
 
void ScrollBarPattern::SetReverse(bool reverse)
{
    isReverse_ = reverse;
}
} // namespace OHOS::Ace::NG
