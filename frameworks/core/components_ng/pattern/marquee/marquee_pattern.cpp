/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/marquee/marquee_pattern.h"

#include <ctime>
#include <string>
#include <sys/time.h>

#include "base/geometry/ng/offset_t.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/canvas.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace::NG {
namespace {
inline constexpr double DEFAULT_MARQUEE_SCROLL_DELAY = 85.0; // Delay time between each jump.
inline bool IsPlayingAnimation(const RefPtr<Animator>& animatorController_)
{
    return (animatorController_->GetStatus() == Animator::Status::RUNNING);
}
} // namespace

void MarqueePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    InitAnimatorController();
}

float MarqueePattern::GetTextChildOffset() const
{
    float childOffset = 0.0f;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, childOffset);
    auto textChild = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_RETURN(textChild, childOffset);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();

    auto textWidth = textChild->GetGeometryNode()->GetMarginFrameSize().Width();
    auto marqueeWidth = GetHostFrameSize()->Width();
    if (GreatOrEqual(textWidth, marqueeWidth)) {
        return childOffset;
    }

    auto textAlign = textLayoutProperty->GetTextAlign();
    if (textAlign == TextAlign::START) {
        textAlign = TextAlign::LEFT;
    }
    if (textAlign == TextAlign::END) {
        textAlign = TextAlign::RIGHT;
    }

    const static float HALF_DIVIDE = 2.0;
    if (textAlign == TextAlign::CENTER) {
        childOffset = (marqueeWidth - textWidth) / HALF_DIVIDE;
    } else if (textAlign == TextAlign::RIGHT) {
        childOffset = marqueeWidth - textWidth;
    }
    return childOffset;
}

float MarqueePattern::CheckAndAdjustPosition(LayoutWrapper* layoutWrapper)
{
    // Initialize child position.
    auto child = layoutWrapper->GetAllChildrenWithBuild().front();
    isNeedMarquee_ = child->GetGeometryNode()->GetMarginFrameSize().Width() >
                     layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    if (isNeedMarquee_) {
        childOffset_ = (direction_ == MarqueeDirection::LEFT)
                           ? childOffset_ = layoutWrapper->GetGeometryNode()->GetMarginFrameSize().Width()
                           : -(child->GetGeometryNode()->GetMarginFrameSize().Width());
    } else {
        startAfterLayout_ = false;
        StopMarquee();
        childOffset_ = GetTextChildOffset();
    }
    return childOffset_;
}

bool MarqueePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& /*dirty*/, const DirtySwapConfig& /*config*/)
{
    if (startAfterLayout_) {
        startAfterLayout_ = false;
        StartMarquee();
    }
    return false;
}

void MarqueePattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }

    direction_ = GetDirection();
    playStatus_ = GetPlayerStatus();
    if (playStatus_) {
        startAfterLayout_ = true;
    }

    scrollAmount_ = GetScrollAmount();
    if (LessOrEqual(scrollAmount_, 0.0)) {
        scrollAmount_ = DEFAULT_MARQUEE_SCROLL_AMOUNT;
    }

    loop_ = GetLoop();
    if (loop_ <= 0) {
        loop_ = ANIMATION_REPEAT_INFINITE;
    }

    if (playStatus_ && animatorController_->GetStatus() == Animator::Status::PAUSED) {
        StartMarquee();
    } else if (!playStatus_ && IsPlayingAnimation(animatorController_)) {
        StopMarquee();
    } else if (playStatus_ && IsPlayingAnimation(animatorController_)) {
        UpdateAnimation();
    }
}

void MarqueePattern::OnInActive()
{
    if (IsPlayingAnimation(animatorController_)) {
        startAfterShowed_ = true;
        animatorController_->Pause();
    }
    isActive_ = false;
}

void MarqueePattern::OnActive()
{
    if (startAfterShowed_) {
        startAfterShowed_ = false;
        StartMarquee();
    }
    isActive_ = true;
}

void MarqueePattern::InitAnimatorController()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (!animatorController_) {
        animatorController_ = AceType::MakeRefPtr<Animator>(host->GetContext());
        auto weak = AceType::WeakClaim(this);
        animatorController_->AddStartListener(Animator::StatusCallback([weak]() {
            auto marquee = weak.Upgrade();
            if (marquee) {
                marquee->OnStartAnimation();
            }
        }));
        animatorController_->AddStopListener(Animator::StatusCallback([weak]() {
            auto marquee = weak.Upgrade();
            if (marquee) {
                marquee->OnStopAnimation();
            }
        }));
        animatorController_->AddRepeatListener(Animator::StatusCallback([weak]() {
            auto marquee = weak.Upgrade();
            if (marquee) {
                marquee->OnRepeatAnimation();
            }
        }));
    }
}

void MarqueePattern::StartMarquee()
{
    if (!isNeedMarquee_) {
        LOGD("Needn't marquee");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textChild = AceType::DynamicCast<FrameNode>(host->GetChildren().front());

    if ((!textChild) || (!animatorController_)) {
        startAfterLayout_ = true;
        LOGD("child Node has not built yet, animation will start after layout.");
        return;
    }
    if (!isActive_) {
        startAfterShowed_ = true;
        LOGD("Marquee is hidden, animation will start when showed.");
        return;
    }
    if (animatorController_->GetStatus() == Animator::Status::PAUSED) {
        animatorController_->Resume();
    } else if (animatorController_->GetStatus() != Animator::Status::RUNNING) {
        LOGD("Start loop.");
        UpdateAnimation(); // Start loop.
        if (needAnimation_) {
            animatorController_->Play();
        }
    } else {
        LOGD("Animation already started.");
    }
}

void MarqueePattern::StopMarquee()
{
    startAfterShowed_ = false;
    if (!animatorController_) {
        LOGD("Animation controller has not initialized.");
        return;
    }
    if (!IsPlayingAnimation(animatorController_)) {
        LOGD("Animation is not playing, status=%{public}d", animatorController_->GetStatus());
        return;
    }
    animatorController_->Pause();
}

void MarqueePattern::OnStartAnimation()
{
    LOGD("OnStart.");
    FireStartEvent();
}

void MarqueePattern::OnRepeatAnimation()
{
    LOGD("OnBounce.");
    FireBounceEvent();
}

void MarqueePattern::OnStopAnimation()
{
    LOGD("OnFinish.");
    FireFinishEvent();
}

void MarqueePattern::UpdateAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textChild = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textChild);
    float start = 0.0;
    float end = 0.0;
    if (direction_ == MarqueeDirection::LEFT) {
        start = GetHostFrameSize()->Width();
        end = -(textChild->GetGeometryNode()->GetMarginFrameSize().Width());
    } else {
        start = -(textChild->GetGeometryNode()->GetMarginFrameSize().Width());
        end = GetHostFrameSize()->Width();
    }

    auto duration = static_cast<int32_t>(std::abs(end - start) * DEFAULT_MARQUEE_SCROLL_DELAY / scrollAmount_);
    if (duration <= 0) {
        needAnimation_ = false;
        LOGD("Animation duration is negative, don't need animation.");
        return;
    }
    needAnimation_ = true;
    if (translate_) {
        animatorController_->RemoveInterpolator(translate_);
    }
    translate_ = MakeRefPtr<CurveAnimation<float>>(start, end, Curves::LINEAR);

    auto weak = WeakClaim(this);
    translate_->AddListener(Animation<float>::ValueCallback([weak](float offset) {
        auto marquee = weak.Upgrade();
        if (marquee) {
            marquee->UpdateChildOffset(offset);
        }
    }));
    LOGD("UpdateAnimation, start:%{public}lf, end:%{public}lf, scrollAmount:%{public}lf, duration:%{public}u, "
         "loop:%{public}d",
        start, end, scrollAmount_, duration, loop_);
    animatorController_->SetDuration(duration);
    animatorController_->SetIteration(loop_);
    animatorController_->AddInterpolator(translate_);
}

void MarqueePattern::UpdateChildOffset(float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    childOffset_ = offset;
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void MarqueePattern::FireStartEvent() const
{
    auto marqueeEventHub = GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(marqueeEventHub);
    marqueeEventHub->FireStartEvent();
}

void MarqueePattern::FireBounceEvent() const
{
    auto marqueeEventHub = GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(marqueeEventHub);
    marqueeEventHub->FireBounceEvent();
}

void MarqueePattern::FireFinishEvent() const
{
    auto marqueeEventHub = GetEventHub<MarqueeEventHub>();
    CHECK_NULL_VOID(marqueeEventHub);
    marqueeEventHub->FireFinishEvent();
}

double MarqueePattern::GetScrollAmount() const
{
    auto marqueeProperty = GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_RETURN(marqueeProperty, DEFAULT_MARQUEE_SCROLL_AMOUNT);
    return marqueeProperty->GetScrollAmount().value_or(DEFAULT_MARQUEE_SCROLL_AMOUNT);
}

int32_t MarqueePattern::GetLoop() const
{
    auto marqueeProperty = GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_RETURN(marqueeProperty, DEFAULT_MARQUEE_LOOP);
    return marqueeProperty->GetLoop().value_or(DEFAULT_MARQUEE_LOOP);
}

bool MarqueePattern::GetPlayerStatus() const
{
    auto marqueeProperty = GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_RETURN(marqueeProperty, false);
    return marqueeProperty->GetPlayerStatus().value_or(false);
}

MarqueeDirection MarqueePattern::GetDirection() const
{
    auto marqueeProperty = GetLayoutProperty<MarqueeLayoutProperty>();
    CHECK_NULL_RETURN(marqueeProperty, MarqueeDirection::LEFT);
    return marqueeProperty->GetDirection().value_or(MarqueeDirection::LEFT);
}
} // namespace OHOS::Ace::NG