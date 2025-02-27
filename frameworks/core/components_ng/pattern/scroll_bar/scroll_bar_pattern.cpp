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

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BAR_DISAPPEAR_DELAY_DURATION = 2000; // 2000ms
constexpr int32_t BAR_DISAPPEAR_DURATION = 300;        // 300ms
constexpr int32_t BAR_APPEAR_DURATION = 100;           // 100ms
constexpr int32_t BAR_DISAPPEAR_FRAME_RATE = 15;       // 15fps, the expected frame rate of opacity animation
constexpr int32_t BAR_DISAPPEAR_MIN_FRAME_RATE = 0;
constexpr int32_t BAR_DISAPPEAR_MAX_FRAME_RATE = 90;
constexpr int32_t LONG_PRESS_PAGE_INTERVAL_MS = 100;
constexpr int32_t LONG_PRESS_TIME_THRESHOLD_MS = 500;
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
    auto axis = axis_;
    axis_ = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        SetScrollBar(DisplayMode::ON);
    }
    if (axis_ == axis && scrollableEvent_) {
        return;
    }
    InitScrollEndCallback();
    AddScrollableEvent();
    SetAccessibilityAction();
    InitMouseEvent();
    // After changing the axis direction, modify the direction of the pan gesture.
    InitPanRecognizer();
    if (!clickRecognizer_) {
        InitClickEvent();
    }
    if (!longPressRecognizer_) {
        InitLongPressEvent();
    }
}

bool ScrollBarPattern::ScrollPositionCallback(double offset, int32_t source, bool isMouseWheelScroll)
{
    if (source == SCROLL_FROM_START) {
        isScrolling_ = true;
        StopDisappearAnimator();
        if (scrollBarProxy_) {
            scrollBarProxy_->NotifyScrollStart();
        }
        // AccessibilityEventType::SCROLL_START
        return true;
    }
    return UpdateCurrentOffset(offset, source, isMouseWheelScroll);
}

void ScrollBarPattern::InitScrollEndCallback()
{
    scrollEndCallback_ = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isScrolling_ = false;
        if (pattern->GetDisplayMode() == DisplayMode::AUTO) {
            pattern->StartDisappearAnimator();
        }
        // AccessibilityEventType::SCROLL_END
    };
}

void ScrollBarPattern::AddScrollableEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(axis_);
    SetInBarRegionCallback();
    SetBarCollectTouchTargetCallback();
    SetBarRectCollectTouchTargetCallback();
    SetBarCollectClickAndLongPressTargetCallback();
    SetInBarRectRegionCallback();
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

void ScrollBarPattern::SetInBarRegionCallback()
{
    CHECK_NULL_VOID(scrollableEvent_);
    scrollableEvent_->SetInBarRegionCallback([weak = AceType::WeakClaim(this)](const PointF& point, SourceType source) {
        auto scrollBarPattern = weak.Upgrade();
        CHECK_NULL_RETURN(scrollBarPattern, false);
        if (scrollBarPattern->UseInnerScrollBar()) {
            auto scrollBar = scrollBarPattern->scrollBar_;
            CHECK_NULL_RETURN(scrollBar, false);
            if (source == SourceType::MOUSE) {
                return scrollBar->InBarHoverRegion(Point(point.GetX(), point.GetY()));
            }
            return scrollBar->InBarTouchRegion(Point(point.GetX(), point.GetY()));
        } else {
            return scrollBarPattern->childRect_.IsInRegion(point);
        }
    });
}

void ScrollBarPattern::SetBarCollectTouchTargetCallback()
{
    CHECK_NULL_VOID(scrollableEvent_);
    scrollableEvent_->SetBarCollectTouchTargetCallback(
        [weak = AceType::WeakClaim(this)](const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
            TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
            ResponseLinkResult& responseLinkResult) {
            auto scrollBarPattern = weak.Upgrade();
            CHECK_NULL_VOID(scrollBarPattern);
            if (scrollBarPattern->UseInnerScrollBar()) {
                auto scrollBar = scrollBarPattern->scrollBar_;
                CHECK_NULL_VOID(scrollBar);
                scrollBar->OnCollectTouchTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            } else {
                scrollBarPattern->OnCollectTouchTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            }
        });
}

void ScrollBarPattern::SetBarRectCollectTouchTargetCallback()
{
    CHECK_NULL_VOID(scrollableEvent_);
    scrollableEvent_->SetBarRectCollectTouchTargetCallback(
        [weak = AceType::WeakClaim(this)](const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
            TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
            ResponseLinkResult& responseLinkResult) {
            auto scrollBarPattern = weak.Upgrade();
            CHECK_NULL_VOID(scrollBarPattern);
            if (scrollBarPattern->UseInnerScrollBar()) {
                auto scrollBar = scrollBarPattern->scrollBar_;
                CHECK_NULL_VOID(scrollBar);
                scrollBar->OnCollectTouchTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult, true);
            } else {
                scrollBarPattern->OnCollectTouchTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult, true);
            }
        });
}

void ScrollBarPattern::SetBarCollectClickAndLongPressTargetCallback()
{
    CHECK_NULL_VOID(scrollableEvent_);
    scrollableEvent_->SetBarCollectClickAndLongPressTargetCallback(
        [weak = AceType::WeakClaim(this)](const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
            TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
            ResponseLinkResult& responseLinkResult) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->OnCollectClickTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            scrollBar->OnCollectLongPressTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
        });
}

void ScrollBarPattern::SetInBarRectRegionCallback()
{
    CHECK_NULL_VOID(scrollableEvent_);
    scrollableEvent_->SetInBarRectRegionCallback(
        [weak = AceType::WeakClaim(this)](const PointF& point, SourceType source) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_RETURN(scrollBar, false);
            return scrollBar->IsInScrollBar();
        });
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
        scrollBar_ = CreateScrollBar();
        RegisterScrollBarEventTask();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        oldDisplayMode = scrollBar_->GetDisplayMode();
    }

    // set the scroll bar style
    auto positionMode = GetPositionMode();
    scrollBar_->SetPositionMode(positionMode);
    if (scrollBarOverlayModifier_) {
        scrollBarOverlayModifier_->SetPositionMode(positionMode);
    }

    if (oldDisplayMode != displayMode) {
        scrollBar_->SetDisplayMode(displayMode);
        if (scrollBarOverlayModifier_ && scrollBar_->IsScrollable()) {
            scrollBarOverlayModifier_->SetOpacity(UINT8_MAX);
        }
        scrollBar_->ScheduleDisappearDelayTask();
    }
}

PositionMode ScrollBarPattern::GetPositionMode()
{
    if (axis_ == Axis::HORIZONTAL) {
        return PositionMode::BOTTOM;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, PositionMode::RIGHT);
    auto layoutProperty = host->GetLayoutProperty();
    if (layoutProperty && layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL) {
        return PositionMode::LEFT;
    }
    return PositionMode::RIGHT;
}

void ScrollBarPattern::HandleScrollBarOutBoundary(float scrollBarOutBoundaryExtent)
{
    CHECK_NULL_VOID(scrollBar_ && scrollBar_->NeedScrollBar());
    scrollBar_->SetOutBoundary(std::abs(scrollBarOutBoundaryExtent));
}

void ScrollBarPattern::UpdateScrollBarOffset(int32_t scrollSource)
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
        Size(viewSize.Width(), viewSize.Height()), Offset(0.0f, 0.0f), scrollSource);
}

void ScrollBarPattern::UpdateScrollBarRegion(
    float offset, float estimatedHeight, Size viewPort, Offset viewOffset, int32_t scrollSource)
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
        scrollBar_->UpdateScrollBarRegion(viewOffset, viewPort, scrollOffset, estimatedHeight, scrollSource);
        scrollBar_->MarkNeedRender();
    }
}

void ScrollBarPattern::RegisterScrollBarEventTask()
{
    CHECK_NULL_VOID(scrollBar_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    scrollBar_->SetMarkNeedRenderFunc([weak = AceType::WeakClaim(AceType::RawPtr(host))]() {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        host->MarkNeedRenderOnly();
    });

    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source, bool isMouseWheelScroll) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->scrollBarProxy_->NotifyScrollBarNode(offset, source, isMouseWheelScroll);
        if (source == SCROLL_FROM_START) {
            pattern->ScrollPositionCallback(0.0, SCROLL_FROM_START);
        }
        return true;
    };
    scrollBar_->SetScrollPositionCallback(std::move(scrollCallback));

    auto scrollEnd = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto scrollEndCallback = pattern->scrollEndCallback_;
        if (scrollEndCallback) {
            scrollEndCallback();
        }
        pattern->scrollBarProxy_->NotifyScrollStop();
    };
    scrollBar_->SetScrollEndCallback(std::move(scrollEnd));
    auto startSnapAnimationCallback = [weak = WeakClaim(this)](SnapAnimationOptions snapAnimationOptions) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->isScrolling_ = false;
        auto scrollBarProxy = pattern->scrollBarProxy_;
        CHECK_NULL_RETURN(scrollBarProxy, false);
        return scrollBarProxy->NotifySnapScrollWithoutChild(snapAnimationOptions);
    };
    scrollBar_->SetStartSnapAnimationCallback(std::move(startSnapAnimationCallback));
    InitScrollBarGestureEvent();
}

void ScrollBarPattern::InitScrollBarGestureEvent()
{
    CHECK_NULL_VOID(scrollBar_);
    auto gestureHub = GetGestureHub();
    auto inputHub = GetInputHub();
    CHECK_NULL_VOID(gestureHub);
    CHECK_NULL_VOID(inputHub);
    scrollBar_->SetGestureEvent();
    scrollBar_->SetMouseEvent();
    scrollBar_->SetHoverEvent();
    gestureHub->AddTouchEvent(scrollBar_->GetTouchEvent());
    inputHub->AddOnMouseEvent(scrollBar_->GetMouseEvent());
    auto onHover = [weak = WeakClaim(this)](bool isHover, HoverInfo&) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->isMousePressed_ || isHover) {
            pattern->StopDisappearAnimator();
        } else {
            if ((pattern->displayMode_) == DisplayMode::AUTO && !(pattern->isScrolling_)) {
                pattern->StartDisappearAnimator();
            }
        }
    };
    auto onHoverFunc = MakeRefPtr<InputEvent>(std::move(onHover));
    inputHub->AddOnHoverEvent(onHoverFunc);
    inputHub->AddOnHoverEvent(scrollBar_->GetHoverEvent());
}

bool ScrollBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    bool updateFlag = false;
    if (UseInnerScrollBar()) {
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

bool ScrollBarPattern::IsInScrollBar()
{
    auto scrollBar = GetHost();
    CHECK_NULL_RETURN(scrollBar, false);
    auto scrollBarSize = scrollBar->GetGeometryNode()->GetFrameSize();
    const bool isInVerticalScrollBar = (locationInfo_.GetX() >= 0 && locationInfo_.GetX() <= scrollBarSize.Width()) &&
                                       (locationInfo_.GetY() >= 0 && locationInfo_.GetY() <= scrollBarSize.Height());
    return isInVerticalScrollBar;
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

bool ScrollBarPattern::UpdateCurrentOffset(float delta, int32_t source, bool isMouseWheelScroll)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (NearZero(delta) || axis_ == Axis::NONE || LessOrEqual(scrollableDistance_, 0.0f)) {
        return false;
    }

    lastOffset_ = currentOffset_;
    currentOffset_ += delta;
    if (scrollBarProxy_ && lastOffset_ != currentOffset_) {
        scrollBarProxy_->NotifyScrollableNode(-delta, source, AceType::WeakClaim(this), isMouseWheelScroll);
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
    enableNestedSorll_ ? DumpLog::GetInstance().AddDesc("enableNestedSorll: true")
                       : DumpLog::GetInstance().AddDesc("enableNestedSorll: false");
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
        if (scrollBar->UseInnerScrollBar()) {
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
    if (UseInnerScrollBar()) {
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
    auto context = GetContext();
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
    panRecognizer_->SetOnActionCancel([weakBar = AceType::WeakClaim(this)](const GestureEvent& info) {
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
    if (scrollBarProxy_) {
        scrollBarProxy_->SetScrollSnapTrigger_(true);
    }
    ScrollPositionCallback(0, SCROLL_FROM_START);
}

void ScrollBarPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto offset = info.GetMainDelta();
    if (IsReverse()) {
        offset = -offset;
    }
    // The offset of the mouse wheel and gesture is opposite.
    if (info.GetInputEventType() == InputEventType::AXIS && !NearZero(controlDistance_)) {
        offset = - offset * scrollableDistance_ / controlDistance_;
    }
    ACE_SCOPED_TRACE("outer scrollBar HandleDragUpdate offset:%f", offset);
    auto isMouseWheelScroll =
        info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() != SourceTool::TOUCHPAD;
    ScrollPositionCallback(offset, SCROLL_FROM_BAR, isMouseWheelScroll);
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
    if (scrollBarProxy_ && scrollBarProxy_->NotifySnapScroll(-(frictionMotion_->GetFinalPosition()),
        velocity, GetScrollableDistance(), static_cast<float>(GetDragOffset()))) {
        scrollBarProxy_->SetScrollSnapTrigger_(false);
        return;
    }
    if (!frictionController_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContextRefPtr();
        CHECK_NULL_VOID(context);
        frictionController_ = CREATE_ANIMATOR(context);
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
    auto offset = value - frictionPosition_;
    ScrollPositionCallback(offset, SCROLL_FROM_BAR_FLING);
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
    CHECK_NULL_VOID(scrollBarProxy_);
    scrollBarProxy_->SetScrollSnapTrigger_(false);
}

void ScrollBarPattern::OnCollectTouchTarget(const OffsetF& coordinateOffset,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult, bool inBarRect)
{
    if (panRecognizer_) {
        panRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        panRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        panRecognizer_->SetNodeId(frameNode->GetId());
        panRecognizer_->AttachFrameNode(frameNode);
        panRecognizer_->SetTargetComponent(targetComponent);
        panRecognizer_->SetIsSystemGesture(true);
        panRecognizer_->SetRecognizerType(GestureTypeName::PAN_GESTURE);
        GestureJudgeFunc sysJudge = nullptr;
        if (inBarRect) {
            sysJudge = [](const RefPtr<GestureInfo>& gestureInfo,
                          const std::shared_ptr<BaseGestureEvent>&) -> GestureJudgeResult {
                auto inputEventType = gestureInfo->GetInputEventType();
                return inputEventType == InputEventType::AXIS ? GestureJudgeResult::CONTINUE
                                                              : GestureJudgeResult::REJECT;
            };
        }
        panRecognizer_->SetSysGestureJudge(sysJudge);
        result.emplace_front(panRecognizer_);
        responseLinkResult.emplace_back(panRecognizer_);
    }
}

void ScrollBarPattern::OnCollectClickTarget(const OffsetF& coordinateOffset,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
{
    if (clickRecognizer_) {
        clickRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        clickRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        clickRecognizer_->SetNodeId(frameNode->GetId());
        clickRecognizer_->AttachFrameNode(frameNode);
        clickRecognizer_->SetTargetComponent(targetComponent);
        clickRecognizer_->SetIsSystemGesture(true);
        clickRecognizer_->SetRecognizerType(GestureTypeName::CLICK);
        result.emplace_front(clickRecognizer_);
        responseLinkResult.emplace_back(clickRecognizer_);
    }
}

void ScrollBarPattern::OnCollectLongPressTarget(const OffsetF& coordinateOffset,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
{
    if (longPressRecognizer_) {
        longPressRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        longPressRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        longPressRecognizer_->SetNodeId(frameNode->GetId());
        longPressRecognizer_->AttachFrameNode(frameNode);
        longPressRecognizer_->SetTargetComponent(targetComponent);
        longPressRecognizer_->SetIsSystemGesture(true);
        longPressRecognizer_->SetRecognizerType(GestureTypeName::LONG_PRESS_GESTURE);
        longPressRecognizer_->SetSysGestureJudge([](const RefPtr<GestureInfo>& gestureInfo,
                                                     const std::shared_ptr<BaseGestureEvent>&) -> GestureJudgeResult {
            const auto &inputEventType = gestureInfo->GetInputEventType();
            TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "input event type:%{public}d", inputEventType);
            return inputEventType == InputEventType::MOUSE_BUTTON ? GestureJudgeResult::CONTINUE
                                                                  : GestureJudgeResult::REJECT;
        });
        result.emplace_front(longPressRecognizer_);
        responseLinkResult.emplace_back(longPressRecognizer_);
    }
}

void ScrollBarPattern::InitClickEvent()
{
    clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
    std::set<SourceTool> allowedTypes = { SourceTool::MOUSE };
    auto gestureInfo = MakeRefPtr<GestureInfo>(allowedTypes);
    clickRecognizer_->SetGestureInfo(gestureInfo);
    clickRecognizer_->SetOnClick([weakBar = AceType::WeakClaim(this)](const ClickInfo&) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleClickEvent();
        }
    });
}

void ScrollBarPattern::HandleClickEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto infoOffset = OffsetF(locationInfo_.GetX(), locationInfo_.GetY());
    auto scrollBarTopOffset = OffsetF(childRect_.Left(), childRect_.Top());
    auto scrollBarBottomOffset = OffsetF(childRect_.Right(), childRect_.Bottom());
    if (infoOffset.GetMainOffset(axis_) < scrollBarTopOffset.GetMainOffset(axis_)) {
        scrollBarProxy_->ScrollPage(true, true);
    } else if (infoOffset.GetMainOffset(axis_) > scrollBarBottomOffset.GetMainOffset(axis_)) {
        scrollBarProxy_->ScrollPage(false, true);
    }
}

void ScrollBarPattern::InitLongPressEvent()
{
    longPressRecognizer_ = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_TIME_THRESHOLD_MS, 1, false, false);
    longPressRecognizer_->SetOnAction([weakBar = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleLongPress(true);
        }
    });
}

void ScrollBarPattern::HandleLongPress(bool smooth)
{
    bool reverse = false;
    auto infoOffset = OffsetF(locationInfo_.GetX(), locationInfo_.GetY());
    auto scrollBarTopOffset = OffsetF(childRect_.Left(), childRect_.Top());
    auto scrollBarBottomOffset = OffsetF(childRect_.Right(), childRect_.Bottom());
    if (infoOffset.GetMainOffset(axis_) < scrollBarTopOffset.GetMainOffset(axis_)) {
        reverse = true;
        if (scrollingDown_) {
            return;
        }
        scrollingUp_ = true;
        scrollingDown_ = false;
    } else if (infoOffset.GetMainOffset(axis_) > scrollBarBottomOffset.GetMainOffset(axis_)) {
        reverse = false;
        if (scrollingUp_) {
            return;
        }
        scrollingUp_ = false;
        scrollingDown_ = true;
    } else {
        isMousePressed_ = false;
        scrollingUp_ = false;
        scrollingDown_ = false;
    }
    if (isMousePressed_ && IsInScrollBar()) {
        scrollBarProxy_->ScrollPage(reverse, smooth);
        StartLongPressEventTimer();
    }
}

void ScrollBarPattern::ScheduleCaretLongPress()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    if (!context->GetTaskExecutor()) {
        return;
    }
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleLongPress(true);
        },
        TaskExecutor::TaskType::UI, LONG_PRESS_PAGE_INTERVAL_MS, "ArkUIScrollBarHandleLongPress");
}

void ScrollBarPattern::StartLongPressEventTimer()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCaretLongPress();
}

void ScrollBarPattern::InitMouseEvent()
{
    CHECK_NULL_VOID(!mouseEvent_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inputHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseCallback = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetButton() == MouseButton::LEFT_BUTTON && info.GetAction() == MouseAction::PRESS) {
            pattern->isMousePressed_ = true;
        } else {
            pattern->isMousePressed_ = false;
            pattern->scrollingUp_ = false;
            pattern->scrollingDown_ = false;
        }
        pattern->locationInfo_ = info.GetLocalLocation();
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseCallback));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

bool ScrollBarPattern::IsReverse() const
{
    return isReverse_;
}

void ScrollBarPattern::SetReverse(bool reverse)
{
    isReverse_ = reverse;
}

void ScrollBarPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    GetAxisDumpInfo(json);
    GetDisplayModeDumpInfo(json);
    GetPanDirectionDumpInfo(json);
    json->Put("hasChild", hasChild_);
    json->Put("preFrameChildState", preFrameChildState_);
    json->Put("enableNestedSorll", enableNestedSorll_);
    if (!hasChild_ && scrollBar_) {
        scrollBar_->DumpAdvanceInfo(json);
    }
    json->Put("childRect", childRect_.ToString().c_str());
    json->Put("scrollableDistance", std::to_string(scrollableDistance_).c_str());
    json->Put("controlDistance_", std::to_string(controlDistance_).c_str());

    std::unique_ptr<JsonValue> children = JsonUtil::CreateArray(true);
    for (const auto& info : outerScrollBarLayoutInfos_) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        info.ToJson(child);
        children->Put(child);
    }
    json->Put("outerScrollBarLayoutInfos", children);
}

void ScrollBarPattern::GetDisplayModeDumpInfo(std::unique_ptr<JsonValue>& json)
{
    switch (displayMode_) {
        case DisplayMode::OFF: {
            json->Put("outerScrollBarState", "OFF");
            break;
        }
        case DisplayMode::AUTO: {
            json->Put("outerScrollBarState", "AUTO");
            break;
        }
        case DisplayMode::ON: {
            json->Put("outerScrollBarState", "ON");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollBarPattern::GetPanDirectionDumpInfo(std::unique_ptr<JsonValue>& json)
{
    if (panRecognizer_) {
        switch (panRecognizer_->GetAxisDirection()) {
            case Axis::NONE: {
                json->Put("panDirection", "NONE");
                break;
            }
            case Axis::VERTICAL: {
                json->Put("panDirection", "VERTICAL");
                break;
            }
            case Axis::HORIZONTAL: {
                json->Put("panDirection", "HORIZONTAL");
                break;
            }
            case Axis::FREE: {
                json->Put("panDirection", "FREE");
                break;
            }
            default: {
                break;
            }
        }
    } else {
        json->Put("panDirection", "null");
    }
}

void ScrollBarPattern::GetAxisDumpInfo(std::unique_ptr<JsonValue>& json)
{
    switch (axis_) {
        case Axis::NONE: {
            json->Put("Axis", "NONE");
            break;
        }
        case Axis::VERTICAL: {
            json->Put("Axis", "VERTICAL");
            break;
        }
        case Axis::HORIZONTAL: {
            json->Put("Axis", "HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            json->Put("Axis", "FREE");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollBarPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }

    json->PutExtAttr("enableNestedScroll", enableNestedSorll_ ? "true" : "false", filter);
}
} // namespace OHOS::Ace::NG
