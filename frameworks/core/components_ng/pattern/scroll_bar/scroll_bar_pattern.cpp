/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components/common/layout/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t STOP_DURATION = 2000; // 2000ms
constexpr float KEY_TIME_START = 0.0f;
constexpr float KEY_TIME_MIDDLE = 0.7f;
constexpr float KEY_TIME_END = 1.0f;
constexpr double FRICTION_VELOCITY_THRESHOLD = 100.0;
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
    if ((oldDisplayMode != displayMode_ || !scrollEndAnimator_)  && scrollBarProxy_) {
        if (displayMode_ == DisplayMode::ON) {
            scrollBarProxy_->StopScrollBarAnimator();
        } else if (displayMode_ == DisplayMode::AUTO || !scrollEndAnimator_) {
            scrollBarProxy_->StartScrollBarAnimator();
        }
    }
    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    if (axis_ == axis && scrollableEvent_) {
        LOGD("Direction not changed, need't resister scroll event again.");
        return;
    }

    axis_ = axis;
    // scrollPosition callback
    scrollPositionCallback_ = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (source == SCROLL_FROM_START) {
            pattern->StopAnimator();
            pattern->SendAccessibilityEvent(AccessibilityEventType::SCROLL_START);
            return true;
        }
        return pattern->UpdateCurrentOffset(offset, source);
    };
    scrollEndCallback_ = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->GetDisplayMode() == DisplayMode::AUTO) {
            pattern->StartAnimator();
        }
        pattern->SendAccessibilityEvent(AccessibilityEventType::SCROLL_END);
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
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_RETURN(scrollBar, false);
            return scrollBar->childRect_.IsInRegion(point);
        }
    );
    scrollableEvent_->SetBarCollectTouchTargetCallback([weak = AceType::WeakClaim(this)]
        (const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->OnCollectTouchTarget(coordinateOffset, getEventTargetImpl, result);
        }
    );
    gestureHub->AddScrollableEvent(scrollableEvent_);
    SetAccessibilityAction();
    if (!panRecognizer_) {
        InitPanRecognizer();
    }
}

bool ScrollBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<ScrollBarLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    scrollableDistance_ = layoutAlgorithm->GetScrollableDistance();
    if (displayMode_ != DisplayMode::OFF) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        if (Positive(controlDistance_) && opacity_ == 0) {
            SetOpacity(UINT8_MAX);
            if (displayMode_ == DisplayMode::AUTO) {
                StartAnimator();
            }
            return true;
        } else if (!Positive(controlDistance_) && opacity_ == UINT8_MAX) {
            SetOpacity(0);
            return true;
        }
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

void ScrollBarPattern::ValidateOffset(int32_t source)
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
    if ((IsAtBottom() && delta > 0.0f) || (IsAtTop() && delta < 0.0f)) {
        return false;
    }

    lastOffset_ = currentOffset_;
    currentOffset_ += delta;
    ValidateOffset(source);
    if (scrollBarProxy_ && lastOffset_ != currentOffset_) {
        scrollBarProxy_->NotifyScrollableNode(-delta, AceType::WeakClaim(this));
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    return true;
}

void ScrollBarPattern::StartAnimator()
{
    if (!Positive(controlDistance_)) {
        return;
    }
    if (scrollEndAnimator_ && !scrollEndAnimator_->IsStopped()) {
        scrollEndAnimator_->Stop();
    }
    if (scrollEndAnimator_) {
        scrollEndAnimator_->Play();
        return;
    }

    scrollEndAnimator_ = CREATE_ANIMATOR(PipelineContext::GetCurrentContext());
    auto hiddenStartKeyframe = AceType::MakeRefPtr<Keyframe<int32_t>>(KEY_TIME_START, UINT8_MAX);
    auto hiddenMiddleKeyframe = AceType::MakeRefPtr<Keyframe<int32_t>>(KEY_TIME_MIDDLE, UINT8_MAX);
    auto hiddenEndKeyframe = AceType::MakeRefPtr<Keyframe<int32_t>>(KEY_TIME_END, 0);
    hiddenMiddleKeyframe->SetCurve(Curves::LINEAR);
    hiddenEndKeyframe->SetCurve(Curves::FRICTION);

    auto animation = AceType::MakeRefPtr<KeyframeAnimation<int32_t>>();
    animation->AddKeyframe(hiddenStartKeyframe);
    animation->AddKeyframe(hiddenMiddleKeyframe);
    animation->AddKeyframe(hiddenEndKeyframe);
    animation->AddListener([weakBar = AceType::WeakClaim(this)](int32_t value) {
        auto scrollBar = weakBar.Upgrade();
        CHECK_NULL_VOID(scrollBar);
        scrollBar->SetOpacity(value);
    });
    scrollEndAnimator_->AddInterpolator(animation);
    scrollEndAnimator_->SetDuration(STOP_DURATION);
    scrollEndAnimator_->Play();
}

void ScrollBarPattern::StopAnimator()
{
    if (!Positive(controlDistance_)) {
        return;
    }
    if (scrollEndAnimator_ && !scrollEndAnimator_->IsStopped()) {
        scrollEndAnimator_->Stop();
    }
    SetOpacity(UINT8_MAX);
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
        auto source = pattern->GetCurrentPosition();
        pattern->UpdateCurrentOffset(pattern->GetChildOffset(), source);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->GetAxis() == Axis::NONE || pattern->GetScrollableDistance() == 0.0f) {
            return;
        }
        auto source = pattern->GetCurrentPosition();
        pattern->UpdateCurrentOffset(-pattern->GetChildOffset(), source);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
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
}

void ScrollBarPattern::HandleDragStart(const GestureEvent& info)
{
    if (frictionController_ && frictionController_->IsRunning()) {
        frictionController_->Stop();
    }
    if (scrollPositionCallback_) {
        if (scrollBarProxy_) {
            scrollBarProxy_->NotifyScrollStart();
        }
        scrollPositionCallback_(0, SCROLL_FROM_START);
    }
}

void ScrollBarPattern::HandleDragUpdate(const GestureEvent& info)
{
    if (scrollPositionCallback_) {
        auto offset = info.GetMainDelta();
        scrollPositionCallback_(offset, SCROLL_FROM_BAR);
    }
}

void ScrollBarPattern::HandleDragEnd(const GestureEvent& info)
{
    auto velocity = info.GetMainVelocity();
    if (NearZero(velocity)) {
        if (scrollEndCallback_) {
            if (scrollBarProxy_) {
                scrollBarProxy_->NotifyScrollStop();
            }
            scrollEndCallback_();
        }
        return;
    }
    frictionPosition_ = 0.0;
    if (frictionMotion_) {
        frictionMotion_->Reset(friction_, 0, velocity, FRICTION_VELOCITY_THRESHOLD);
    } else {
        frictionMotion_ = AceType::MakeRefPtr<FrictionMotion>(friction_, 0, velocity, FRICTION_VELOCITY_THRESHOLD);
        frictionMotion_->AddListener([weakBar = AceType::WeakClaim(this)](double value) {
            auto scrollBar = weakBar.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->ProcessFrictionMotion(value);
        });
    }
    CHECK_NULL_VOID(!scrollBarProxy_ || !scrollBarProxy_->NotifySnapScroll(-(frictionMotion_->GetFinalPosition()),
        velocity, GetScrollableDistance()));
    
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
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
{
    if (panRecognizer_) {
        panRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        panRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        result.emplace_front(panRecognizer_);
    }
}
} // namespace OHOS::Ace::NG
