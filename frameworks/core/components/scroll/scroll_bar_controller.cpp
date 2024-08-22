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

#include "core/components/scroll/scroll_bar_controller.h"

#include "core/common/vibrator/vibrator_proxy.h"
#include "core/components/scroll/render_scroll.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t STOP_DURATION = 2000; // 2000ms
constexpr double FRICTION = 1.0;
constexpr double MIN_VELOCITY = -10000.0;
constexpr double MAX_VELOCITY = 10000.0;

constexpr double KEYTIME_START = 0.0;
constexpr double KEYTIME_MIDDLE = 0.7;
constexpr double KEYTIME_END = 1.0;
constexpr int32_t VIBRATE_DURATION = 100;    // 100ms
constexpr int32_t BAR_EXPAND_DURATION = 150; // 150ms, scroll bar width expands from 4dp to 8dp
constexpr int32_t BAR_SHRINK_DURATION = 250; // 250ms, scroll bar width shrinks from 4dp to 8dp

} // namespace

void ScrollBarController::Initialize(const WeakPtr<PipelineContext>& context, bool isVertical)
{
    context_ = context;
    isVertical_ = isVertical;

    PanDirection panDirection;
    panDirection.type = isVertical ? PanDirection::VERTICAL : PanDirection::HORIZONTAL;
    panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(
        context, DEFAULT_PAN_FINGER, panDirection, DEFAULT_PAN_DISTANCE.ConvertToPx());
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

    // use RawRecognizer to receive next touch down event to stop animation.
    rawRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
    rawRecognizer_->SetOnTouchDown([weakBar = AceType::WeakClaim(this)](const TouchEventInfo&) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleTouchDown();
        }
    });
    rawRecognizer_->SetOnTouchUp([weakBar = AceType::WeakClaim(this)](const TouchEventInfo&) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleTouchUp();
        }
    });

    touchAnimator_ = CREATE_ANIMATOR(context);
    dragEndAnimator_ = CREATE_ANIMATOR(context);
    InitBarEndAnimation(context);

    // when touching down, it need vibrate, last 100ms
    auto vibratorContext = context.Upgrade();
    if (!vibrator_ && vibratorContext) {
        vibrator_ = VibratorProxy::GetInstance().GetVibrator(vibratorContext->GetTaskExecutor());
    }
}

void ScrollBarController::PlayGrowAnimation()
{
    if (!touchDownCallback_) {
        return;
    }
    if (!touchAnimator_->IsStopped()) {
        touchAnimator_->Stop();
    }
    touchAnimator_->ClearInterpolators();
    auto activeWidth = activeWidth_.Value();
    auto inactiveWidth = inactiveWidth_.Value();
    auto pipeline = context_.Upgrade();
    if (pipeline) {
        activeWidth = pipeline->NormalizeToPx(activeWidth_);
        inactiveWidth = pipeline->NormalizeToPx(inactiveWidth_);
    }

    auto animation = AceType::MakeRefPtr<CurveAnimation<double>>(inactiveWidth, activeWidth, Curves::SHARP);
    animation->AddListener([weakBar = AceType::WeakClaim(this)](double value) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar && scrollBar->touchDownCallback_) {
            scrollBar->touchDownCallback_(value);
            scrollBar->MarkScrollRender();
        }
    });
    touchAnimator_->AddInterpolator(animation);
    touchAnimator_->SetDuration(BAR_EXPAND_DURATION);
    touchAnimator_->Play();
    if (barEndCallback_) {
        barEndCallback_(UINT8_MAX);
    }
}

void ScrollBarController::PlayShrinkAnimation()
{
    if (!touchUpCallback_) {
        return;
    }
    if (!touchAnimator_->IsStopped()) {
        touchAnimator_->Stop();
    }
    touchAnimator_->ClearInterpolators();
    auto activeWidth = activeWidth_.Value();
    auto inactiveWidth = inactiveWidth_.Value();
    auto pipeline = context_.Upgrade();
    if (pipeline) {
        activeWidth = pipeline->NormalizeToPx(activeWidth_);
        inactiveWidth = pipeline->NormalizeToPx(inactiveWidth_);
    }

    auto animation = AceType::MakeRefPtr<CurveAnimation<double>>(activeWidth, inactiveWidth, Curves::SHARP);
    animation->AddListener([weakBar = AceType::WeakClaim(this)](double value) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar && scrollBar->touchUpCallback_) {
            scrollBar->touchUpCallback_(value);
        }
    });
    touchAnimator_->AddInterpolator(animation);
    touchAnimator_->SetDuration(BAR_SHRINK_DURATION);
    touchAnimator_->Play();
}

void ScrollBarController::HandleTouchDown()
{
    LOGI("handle touch down");
    isPressed_ = true;
    if (CheckScroll()) {
        isActive_ = true;
        if (vibrator_) {
            vibrator_->Vibrate(VIBRATE_DURATION);
        }
        if (!isHover_) {
            PlayGrowAnimation();
        }
    }
}

void ScrollBarController::MarkScrollRender()
{
    auto scroll = AceType::DynamicCast<RenderScroll>(scroll_.Upgrade());
    if (scroll) {
        scroll->MarkNeedRender();
    }
}

void ScrollBarController::HandleTouchUp()
{
    LOGI("handle touch up");
    isPressed_ = false;
    if (!isInBar_) {
        isHover_ = false;
        PlayShrinkAnimation();
    }
    if (isActive_) {
        HandleScrollBarEnd();
    }
    isActive_ = false;
}

void ScrollBarController::HandleDragUpdate(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS) {
        UpdateScrollPosition(info.GetMainDelta(), SCROLL_FROM_AXIS);
    } else {
        UpdateScrollPosition(-info.GetMainDelta(), SCROLL_FROM_BAR);
    }
}

void ScrollBarController::HandleDragEnd(const GestureEvent& info)
{
    LOGI("handle drag end, position is %{public}lf and %{public}lf, velocity is %{public}lf",
        info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY(), info.GetMainVelocity());
    if (scrollEndCallback_) {
        scrollEndCallback_();
    }
    double mainPosition = info.GetGlobalLocation().GetY();
    double correctVelocity = std::clamp(info.GetMainVelocity(), MIN_VELOCITY, MAX_VELOCITY);
    if (dragEndMotion_) {
        dragEndMotion_->Reset(FRICTION, mainPosition, correctVelocity);
    } else {
        dragEndMotion_ = AceType::MakeRefPtr<FrictionMotion>(FRICTION, mainPosition, correctVelocity);
        dragEndMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double value) {
            auto scrollBarController = weakScroll.Upgrade();
            if (scrollBarController) {
                scrollBarController->ProcessScrollMotion(value);
            }
        });
    }

    currentPos_ = mainPosition;
    dragEndAnimator_->ClearStopListeners();
    dragEndAnimator_->AddStopListener([weakScroll = AceType::WeakClaim(this)]() {
        auto scrollBarController = weakScroll.Upgrade();
        if (scrollBarController) {
            scrollBarController->SetActive(false);
        }
    });
    dragEndAnimator_->PlayMotion(dragEndMotion_);
}

void ScrollBarController::ProcessScrollMotion(double position)
{
    if ((NearEqual(currentPos_, position))) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION);
    } else {
        // UpdateScrollPosition return false, means reach to scroll limit.
        if (!UpdateScrollPosition(currentPos_ - position, SCROLL_FROM_BAR)) {
            auto scroll = AceType::DynamicCast<RenderScroll>(scroll_.Upgrade());
            if (scroll) {
                scroll->HandleScrollOverByBar(dragEndMotion_->GetCurrentVelocity());
            }
            dragEndAnimator_->Stop();
        }
    }
    currentPos_ = position;
}

bool ScrollBarController::UpdateScrollPosition(const double offset, int32_t source)
{
    bool ret = true;
    if (callback_) {
        auto scroll = AceType::DynamicCast<RenderScroll>(scroll_.Upgrade());
        if (scroll && !NearZero(scroll->GetEstimatedHeight())) {
            double mainSize = isVertical_ ? scroll->GetLayoutSize().Height() : scroll->GetLayoutSize().Width();
            double estimatedHeight = scroll->GetEstimatedHeight();
            double activeHeight = mainSize * mainSize / estimatedHeight;
            if (!NearEqual(mainSize, activeHeight)) {
                double value = offset * (estimatedHeight - mainSize) / (mainSize - activeHeight);
                ret = source == SCROLL_FROM_AXIS ? callback_(offset, source) : callback_(value, source);
            }
        }
    }
    return ret;
}

void ScrollBarController::HandleScrollBarEnd()
{
    isActive_ = false;
    if (!scrollEndAnimator_) {
        LOGE("scrollEndAnimator_ is not exist.");
        return;
    }
    if (!scrollEndAnimator_->IsStopped()) {
        scrollEndAnimator_->Stop();
    }
    scrollEndAnimator_->Play();
}

void ScrollBarController::InitBarEndAnimation(const WeakPtr<PipelineContext>& context)
{
    if (scrollEndAnimator_ && !scrollEndAnimator_->IsStopped()) {
        scrollEndAnimator_->Stop();
    }
    if (scrollEndAnimator_) {
        scrollEndAnimator_->Play();
        return;
    }

    scrollEndAnimator_ = CREATE_ANIMATOR(context);
    auto hiddenStartKeyframe = AceType::MakeRefPtr<Keyframe<int32_t>>(KEYTIME_START, UINT8_MAX);
    auto hiddenMiddleKeyframe = AceType::MakeRefPtr<Keyframe<int32_t>>(KEYTIME_MIDDLE, UINT8_MAX);
    auto hiddenEndKeyframe = AceType::MakeRefPtr<Keyframe<int32_t>>(KEYTIME_END, 0);
    hiddenMiddleKeyframe->SetCurve(Curves::LINEAR);
    hiddenEndKeyframe->SetCurve(Curves::FRICTION);

    auto animation = AceType::MakeRefPtr<KeyframeAnimation<int32_t>>();
    animation->AddKeyframe(hiddenStartKeyframe);
    animation->AddKeyframe(hiddenMiddleKeyframe);
    animation->AddKeyframe(hiddenEndKeyframe);
    animation->AddListener([weakBar = AceType::WeakClaim(this)](int32_t value) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar && scrollBar->barEndCallback_) {
            scrollBar->barEndCallback_(value);
        }
    });
    scrollEndAnimator_->AddInterpolator(animation);
    scrollEndAnimator_->SetDuration(STOP_DURATION);
    scrollEndAnimator_->Play();
}

void ScrollBarController::Reset()
{
    if (scrollEndAnimator_ && !scrollEndAnimator_->IsStopped()) {
        scrollEndAnimator_->Stop();
    }
}

bool ScrollBarController::CheckScroll()
{
    auto scroll = AceType::DynamicCast<RenderScroll>(scroll_.Upgrade());
    return scroll != nullptr;
}

void ScrollBarController::SetIsHover(bool isInBarRegion)
{
    if (isInBar_ == isInBarRegion) {
        return;
    }
    isInBar_ = isInBarRegion;
    if (isPressed_) {
        return;
    }
    isHover_ = isInBar_;
    if (isHover_) {
        isActive_ = true;
        PlayGrowAnimation();
    } else {
        PlayShrinkAnimation();
        if (isActive_) {
            HandleScrollBarEnd();
        }
        isActive_ = false;
    }
}

void ScrollBarController::OnFlushTouchEventsBegin()
{
    if (panRecognizer_) {
        panRecognizer_->OnFlushTouchEventsBegin();
    }
}

void ScrollBarController::OnFlushTouchEventsEnd()
{
    if (panRecognizer_) {
        panRecognizer_->OnFlushTouchEventsEnd();
    }
}

} // namespace OHOS::Ace
