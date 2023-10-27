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

#include "render_service_client/core/animation/rs_animation.h"
#include "render_service_client/core/ui/rs_node.h"

#include "core/animation/native_curve_helper.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace {

namespace {
Rosen::RSAnimationTimingProtocol OptionToTimingProtocol(const AnimationOption& option)
{
    Rosen::RSAnimationTimingProtocol timingProtocol;
    timingProtocol.SetDuration(option.GetDuration());
    timingProtocol.SetStartDelay(option.GetDelay());
    timingProtocol.SetSpeed(option.GetTempo());
    timingProtocol.SetRepeatCount(option.GetIteration());
    timingProtocol.SetDirection(option.GetAnimationDirection() == AnimationDirection::NORMAL ||
                                option.GetAnimationDirection() == AnimationDirection::ALTERNATE);
    timingProtocol.SetAutoReverse(option.GetAnimationDirection() == AnimationDirection::ALTERNATE ||
                                  option.GetAnimationDirection() == AnimationDirection::ALTERNATE_REVERSE);
    timingProtocol.SetFillMode(static_cast<Rosen::FillMode>(option.GetFillMode()));
    return timingProtocol;
}
} // namespace

class AnimationUtils::Animation {
private:
    std::vector<std::shared_ptr<OHOS::Rosen::RSAnimation>> animations_;

    friend AnimationUtils;
};

void AnimationUtils::OpenImplicitAnimation(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()>& finishCallback)
{
    const auto& timingProtocol = OptionToTimingProtocol(option);
    Rosen::RSNode::OpenImplicitAnimation(timingProtocol, NativeCurveHelper::ToNativeCurve(curve), finishCallback);
}

bool AnimationUtils::CloseImplicitAnimation()
{
    auto animations = Rosen::RSNode::CloseImplicitAnimation();
    return !animations.empty();
}

bool AnimationUtils::IsImplicitAnimationOpen()
{
    return Rosen::RSNode::IsImplicitAnimationOpen();
}

void AnimationUtils::Animate(const AnimationOption& option, const PropertyCallback& callback,
    const FinishCallback& finishCallback, const RepeatCallback& repeatCallback)
{
    const auto& timingProtocol = OptionToTimingProtocol(option);
    Rosen::RSNode::Animate(
        timingProtocol, NativeCurveHelper::ToNativeCurve(option.GetCurve()), callback, finishCallback, repeatCallback);
}

void AnimationUtils::AnimateWithCurrentOptions(
    const PropertyCallback& callback, const FinishCallback& finishCallback, bool timingSensitive)
{
    Rosen::RSNode::AnimateWithCurrentOptions(callback, finishCallback, timingSensitive);
}

void AnimationUtils::AnimateWithCurrentCallback(const AnimationOption& option, const PropertyCallback& callback)
{
    const auto& timingProtocol = OptionToTimingProtocol(option);
    Rosen::RSNode::AnimateWithCurrentCallback(
        timingProtocol, NativeCurveHelper::ToNativeCurve(option.GetCurve()), callback);
}

void AnimationUtils::AddKeyFrame(float fraction, const RefPtr<Curve>& curve, const PropertyCallback& callback)
{
    Rosen::RSNode::AddKeyFrame(fraction, NativeCurveHelper::ToNativeCurve(curve), callback);
}

void AnimationUtils::AddKeyFrame(float fraction, const PropertyCallback& callback)
{
    Rosen::RSNode::AddKeyFrame(fraction, callback);
}

std::shared_ptr<AnimationUtils::Animation> AnimationUtils::StartAnimation(const AnimationOption& option,
    const PropertyCallback& callback, const FinishCallback& finishCallback, const RepeatCallback& repeatCallback)
{
    std::shared_ptr<AnimationUtils::Animation> animation = std::make_shared<AnimationUtils::Animation>();
    CHECK_NULL_RETURN(animation, nullptr);
    const auto& timingProtocol = OptionToTimingProtocol(option);
    animation->animations_ = Rosen::RSNode::Animate(
        timingProtocol, NativeCurveHelper::ToNativeCurve(option.GetCurve()), callback, finishCallback, repeatCallback);
    if (animation->animations_.size()) {
        return animation;
    } else {
        return nullptr;
    }
}

void AnimationUtils::StopAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{
    CHECK_NULL_VOID(animation);
    if (animation->animations_.size()) {
        for (auto& ani : animation->animations_) {
            ani->Finish();
        }
        animation->animations_.clear();
    }
}

void AnimationUtils::BlendBgColorAnimation(
    RefPtr<NG::RenderContext>& renderContext, const Color& endColor, int32_t duration, const RefPtr<Curve>& curve)
{
    AnimationOption option = AnimationOption();
    option.SetCurve(curve);
    option.SetDuration(duration);
    AnimationUtils::Animate(option, [context = renderContext, color = endColor]() { context->BlendBgColor(color); });
}

void AnimationUtils::PauseAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{
    CHECK_NULL_VOID(animation);
    for (auto& ani : animation->animations_) {
        ani->Pause();
    }
}

void AnimationUtils::ResumeAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{
    CHECK_NULL_VOID(animation);
    for (auto& ani : animation->animations_) {
        ani->Resume();
    }
}
} // namespace OHOS::Ace
