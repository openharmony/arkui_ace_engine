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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_ANIMATION_OPTION_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_ANIMATION_OPTION_H

#include <functional>
#include <string>
#include <unordered_map>

#include "ui/animation/animation_constants.h"
#include "ui/animation/curve.h"
#include "ui/animation/frame_rate_range.h"

namespace OHOS::Ace {

inline const std::unordered_map<AnimationInterface, std::string> animationTypeToStrMap = {
    { AnimationInterface::ANIMATION, "animation" },
    { AnimationInterface::ANIMATE_TO, "animateTo" },
    { AnimationInterface::ANIMATE_TO_IMMEDIATELY, "animateToImmediately" },
    { AnimationInterface::KEYFRAME_ANIMATE_TO, "keyframeAnimateTo" },
    { AnimationInterface::TRANSITION, "transition" },
    { AnimationInterface::SHARED_TRANSITION, "sharedTransition" },
    { AnimationInterface::PAGE_TRANSITION, "pageTransition" },
    { AnimationInterface::UNKNOWN, "unknown" },
};

class AnimationOption final {
public:
    AnimationOption() = default;
    AnimationOption(const RefPtr<Curve>& curve, int32_t duration) : duration_(duration), curve_(curve) {}
    ~AnimationOption() = default;

    void SetDuration(int32_t duration)
    {
        duration_ = duration;
    }

    int32_t GetDuration() const
    {
        return duration_;
    }

    void SetDelay(int32_t delay)
    {
        delay_ = delay;
    }

    int32_t GetDelay() const
    {
        return delay_;
    }

    void SetCurve(const RefPtr<Curve>& curve)
    {
        if (!curve) {
            return;
        }
        curve_ = curve;
    }

    void SetIteration(int32_t iteration)
    {
        if (iteration < 0 && iteration != ANIMATION_REPEAT_INFINITE) {
            return;
        }
        iteration_ = iteration;
    }

    int32_t GetIteration() const
    {
        return iteration_;
    }

    void SetTempo(float tempo)
    {
        if (tempo < 0.0f) {
            return;
        }
        tempo_ = tempo;
    }

    float GetTempo() const
    {
        return tempo_;
    }

    void SetAnimationDirection(AnimationDirection direction)
    {
        direction_ = direction;
    }

    AnimationDirection GetAnimationDirection() const
    {
        return direction_;
    }

    const RefPtr<Curve>& GetCurve() const
    {
        return curve_;
    }

    void SetFillMode(const FillMode& fillMode)
    {
        fillMode_ = fillMode;
    }

    FillMode GetFillMode() const
    {
        return fillMode_;
    }

    void SetOnFinishEvent(const std::function<void()>& onFinishEvent)
    {
        onFinishEvent_ = onFinishEvent;
    }

    const std::function<void()>& GetOnFinishEvent() const
    {
        return onFinishEvent_;
    }

    bool IsValid() const
    {
        return (GetDuration() > 0 || GetAllowRunningAsynchronously());
    }

    void SetAllowRunningAsynchronously(bool runAsync)
    {
        allowRunningAsynchronously_ = runAsync;
    }

    bool GetAllowRunningAsynchronously() const
    {
        return allowRunningAsynchronously_;
    }

    void SetFinishCallbackType(FinishCallbackType finishCallbackType)
    {
        finishCallbackType_ = finishCallbackType;
    }

    FinishCallbackType GetFinishCallbackType() const
    {
        return finishCallbackType_;
    }

    void SetFrameRateRange(const RefPtr<FrameRateRange>& rateRange)
    {
        rateRange_ = rateRange;
    }

    const RefPtr<FrameRateRange>& GetFrameRateRange() const
    {
        return rateRange_;
    }

    void SetAnimationInterface(AnimationInterface animationInterface)
    {
        animationInterface_ = animationInterface;
    }

    AnimationInterface GetAnimationInterface() const
    {
        return animationInterface_;
    }

    const std::string GetAnimationInterfaceString() const
    {
        auto it = animationTypeToStrMap.find(animationInterface_);
        return it != animationTypeToStrMap.end() ? it->second : "unknown";
    }

    std::string ToString() const
    {
        std::string result = std::string("duration:").append(std::to_string(duration_))
            .append(", curve:").append(curve_ ? curve_->ToString() : "");
        if (iteration_ != 1) {
            result.append(", iteration:").append(std::to_string(iteration_));
        }
        if (delay_) {
            result.append(", delay:").append(std::to_string(delay_));
        }
        if (!NearEqual(tempo_, 1.0f)) {
            result.append(", tempo:").append(std::to_string(tempo_));
        }
        if (direction_ != AnimationDirection::NORMAL) {
            result.append(", playMode:").append(std::to_string(static_cast<int32_t>(direction_)));
        }
        return result;
    }

    std::string ToSimpleString() const
    {
        std::stringstream ss;
        ss << "dur:" << duration_ << ", curve:"
           << (curve_ ? curve_->ToSimpleString() : "");
        if (iteration_ != 1) {
            ss << ", iter:"  << iteration_;
        }
        if (delay_) {
            ss << ", delay:"  << delay_;
        }
        if (!NearEqual(tempo_, 1.0f)) {
            ss << ", tempo:"  << tempo_;
        }
        if (direction_ != AnimationDirection::NORMAL) {
            ss << ", mode:"  << static_cast<int32_t>(direction_);
        }
        return ss.str();
    }

private:
    int32_t duration_ = 0;
    int32_t delay_ = 0;
    int32_t iteration_ = 1;
    float tempo_ = 1.0f;
    FillMode fillMode_ = FillMode::FORWARDS;
    AnimationInterface animationInterface_ = AnimationInterface::UNKNOWN;
    bool allowRunningAsynchronously_ = false;
    RefPtr<Curve> curve_;
    std::function<void()> onFinishEvent_;
    AnimationDirection direction_ = AnimationDirection::NORMAL;
    FinishCallbackType finishCallbackType_ = FinishCallbackType::REMOVED;
    RefPtr<FrameRateRange> rateRange_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_ANIMATION_OPTION_H
