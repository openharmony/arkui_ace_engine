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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_ANIMATABLE_FLOAT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_ANIMATABLE_FLOAT_H

#include "core/animation/animator.h"
#include "core/animation/curve_animation.h"
#include "core/components/common/properties/animation_option.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {

/*
 * AnimatableFloat is a float with AnimationOption and Animator.
 */
class AnimatableFloat final {
public:
    AnimatableFloat() = default;
    explicit AnimatableFloat(float value, const AnimationOption& option = AnimationOption())
        : value_(value), animationOption_(option) {}
    ~AnimatableFloat() = default;
    using RenderNodeAnimationCallback = std::function<void()>;

    void SetContextAndCallback(const WeakPtr<PipelineBase>& context, RenderNodeAnimationCallback&& callback)
    {
        context_ = context;
        animationCallback_ = std::move(callback);
    }

    float GetValue() const
    {
        return value_;
    }

    void SetValue(float value)
    {
        value_ = value;
    }

    AnimationOption GetAnimationOption() const
    {
        return animationOption_;
    }

    void SetAnimationOption(const AnimationOption& option)
    {
        animationOption_ = option;
    }

    bool operator==(const AnimatableFloat& animFloat) const
    {
        return NearEqual(value_, animFloat.GetValue());
    }

    bool operator!=(const AnimatableFloat& animFloat) const
    {
        return !operator==(animFloat);
    }

    AnimatableFloat& operator=(const AnimatableFloat& newValue)
    {
        SetAnimationOption(newValue.GetAnimationOption());
        auto pipelineContext = context_.Upgrade();
        if (NearEqual(value_, std::numeric_limits<float>::max()) || NearEqual(value_, newValue.GetValue())
            || !pipelineContext || !animationCallback_) {
            SetValue(newValue.GetValue());
            return *this;
        }

        AnimationOption explicitAnim;
        if (pipelineContext) {
            explicitAnim = pipelineContext->GetExplicitAnimationOption();
        }

        // Animaiton has started already in previous update call.
        if (NearEqual(animateToEndValue_, newValue.GetValue()) && explicitAnim.IsValid()) {
            LOGW("Previous animateTo end value is same as new value.");
            return *this;
        }

        if (explicitAnim.IsValid()) {
            SetAnimationOption(explicitAnim);
            AnimateTo(newValue.GetValue());
        } else if (animationOption_.IsValid()) {
            AnimateTo(newValue.GetValue());
        } else {
            SetValue(newValue.GetValue());
        }
        return *this;
    }

private:
    void AnimateTo(float endValue)
    {
        animateToEndValue_ = endValue;
        ResetController();
        if (!animationController_) {
            animationController_ = CREATE_ANIMATOR(context_);
        }
        RefPtr<CurveAnimation<float>> animation = AceType::MakeRefPtr<CurveAnimation<float>>(
            GetValue(), endValue, animationOption_.GetCurve());
        animation->AddListener(std::bind(&AnimatableFloat::OnAnimationCallback, this, std::placeholders::_1));

        animationController_->AddInterpolator(animation);
        animationController_->SetDuration(animationOption_.GetDuration());
        animationController_->SetStartDelay(animationOption_.GetDelay());
        animationController_->Play();
    }

    void ResetController()
    {
        if (animationController_) {
            if (!animationController_->IsStopped()) {
                animationController_->Stop();
            }
            animationController_->ClearInterpolators();
            animationController_.Reset();
        }
    }

    void OnAnimationCallback(float value)
    {
        SetValue(value);
        if (animationCallback_) {
            animationCallback_();
        }
    }

private:
    float value_ = std::numeric_limits<float>::max();
    AnimationOption animationOption_;
    RefPtr<Animator> animationController_;
    WeakPtr<PipelineBase> context_;
    RenderNodeAnimationCallback animationCallback_;
    float animateToEndValue_ = -1.0f;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_ANIMATABLE_FLOAT_H
