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

#include "base/memory/referenced.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components_ng/render/animation_utils.h"
#include "ui/animation/animation_constants.h"
#include "ui/animation/curve.h"

namespace OHOS::Ace {
#ifndef ENABLE_ROSEN_BACKEND
void AnimationUtils::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& wrapFinishCallback)
{}

void AnimationUtils::OpenImplicitAnimation(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()>& wrapFinishCallback, const RefPtr<PipelineBase>& context)
{}

bool AnimationUtils::CloseImplicitAnimation()
{
    return false;
}

bool AnimationUtils::CloseImplicitAnimation(const RefPtr<PipelineBase>& context)
{
    return false;
}

bool AnimationUtils::CloseImplicitCancelAnimation()
{
    return true;
}

bool AnimationUtils::CloseImplicitCancelAnimation(const RefPtr<PipelineBase>& context)
{
    return true;
}

CancelAnimationStatus AnimationUtils::CloseImplicitCancelAnimationReturnStatus()
{
    return CancelAnimationStatus::SUCCESS;
}

CancelAnimationStatus AnimationUtils::CloseImplicitCancelAnimationReturnStatus(const RefPtr<PipelineBase>& context)
{
    return CancelAnimationStatus::SUCCESS;
}

bool AnimationUtils::IsImplicitAnimationOpen()
{
    return false;
}

bool AnimationUtils::IsImplicitAnimationOpen(const RefPtr<PipelineBase>& context)
{
    return false;
}

void AnimationUtils::Animate(const AnimationOption& option, const PropertyCallback& callback,
    const FinishCallback& finishCallback, const RepeatCallback& repeatCallback)
{}

void AnimationUtils::Animate(const AnimationOption& option, const PropertyCallback& callback,
    const FinishCallback& finishCallback, const RepeatCallback& repeatCallback, const RefPtr<PipelineBase>& context)
{}

class AnimationUtils::Animation {
};

class AnimationUtils::InteractiveAnimation {
};

void AnimationUtils::AddKeyFrame(float fraction, const RefPtr<Curve>& curve, const PropertyCallback& callback)
{}

void AnimationUtils::AddKeyFrame(float fraction, const RefPtr<Curve>& curve, const PropertyCallback& callback,
    const RefPtr<PipelineBase>& context)
{}

void AnimationUtils::AddKeyFrame(float fraction, const PropertyCallback& callback)
{}

void AnimationUtils::AddKeyFrame(float fraction, const PropertyCallback& callback, const RefPtr<PipelineBase>& context)
{}

void AnimationUtils::AddDurationKeyFrame(
    int duration, const RefPtr<Curve>& curve, const PropertyCallback& callback)
{}

void AnimationUtils::AddDurationKeyFrame(
    int duration, const RefPtr<Curve>& curve, const PropertyCallback& callback, const RefPtr<PipelineBase>& context)
{}

void AnimationUtils::AnimateWithCurrentOptions(
    const PropertyCallback& callback, const FinishCallback& finishCallback)
{}

void AnimationUtils::AnimateWithCurrentOptions(
    const PropertyCallback& callback, const FinishCallback& finishCallback,
    bool timingSensitive, const RefPtr<PipelineBase>& context)
{}

void AnimationUtils::AnimateWithCurrentCallback(
    const AnimationOption& option, const PropertyCallback& callback)
{}

void AnimationUtils::AnimateWithCurrentCallback(
    const AnimationOption& option, const PropertyCallback& callback, const RefPtr<PipelineBase>& context)
{}

std::shared_ptr<AnimationUtils::Animation> AnimationUtils::StartAnimation(const AnimationOption& option,
    const PropertyCallback& callback, const FinishCallback& finishCallback,
    const RepeatCallback& repeatCallback)
{
    return nullptr;
}

std::shared_ptr<AnimationUtils::Animation> AnimationUtils::StartAnimation(
    const AnimationOption& option, const PropertyCallback& callback, const FinishCallback& finishCallback,
    const RepeatCallback& repeatCallback, const RefPtr<PipelineBase>& context)
{
    return nullptr;
}

void AnimationUtils::StopAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{}

void AnimationUtils::BlendBgColorAnimation(
    RefPtr<NG::RenderContext>& renderContext, const Color& endColor, int32_t duration, const RefPtr<Curve>& curve)
{}

void AnimationUtils::PauseAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{}

void AnimationUtils::ResumeAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{}

void AnimationUtils::ReverseAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{}

void AnimationUtils::ExecuteWithoutAnimation(const PropertyCallback& callback)
{}

void AnimationUtils::ExecuteWithoutAnimation(const PropertyCallback& callback, const RefPtr<PipelineBase>& context)
{}

std::shared_ptr<AnimationUtils::InteractiveAnimation> AnimationUtils::CreateInteractiveAnimation(
    const InteractiveAnimationCallback& addCallback, const FinishCallback& callback)
{
    return nullptr;
}

void AnimationUtils::UpdateInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation, float progress)
{}

void AnimationUtils::ContinueInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation)
{}

int32_t AnimationUtils::StartInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation)
{
    return 0;
}

void AnimationUtils::ReverseInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation)
{}

void AnimationUtils::AddInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation,
    const std::function<void()>& callback)
{}

void AnimationUtils::SetNavGroupNodeTransAnimationCallback()
{}

std::shared_ptr<Rosen::RSUIContext> AnimationUtils::GetCurrentRSUIContext(RefPtr<PipelineBase> context)
{
    return nullptr;
}

uint64_t AnimationUtils::GetRSUIContextToken(RefPtr<PipelineBase> context)
{
    return 0;
}
#endif
} // namespace OHOS::Ace
