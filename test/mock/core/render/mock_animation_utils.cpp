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

#ifdef ENHANCED_ANIMATION
#include "test/mock/core/animation/mock_implicit_animation.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#endif

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace {

#ifdef ENHANCED_ANIMATION
using AnimManager = NG::MockAnimationManager;

class AnimationUtils::Animation {
public:
    Animation() = default;
    explicit Animation(std::vector<RefPtr<MockImplicitAnimation>>&& anims) : impls_(anims) {}
    std::vector<RefPtr<MockImplicitAnimation>> impls_;
};
#else
class AnimationUtils::Animation {};
#endif

class AnimationUtils::InteractiveAnimation {
public:
    FinishCallback finishCallback_;
};

void AnimationUtils::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()>& wrapFinishCallback, const RefPtr<PipelineBase>& context)
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().OpenAnimation();
#endif
    if (wrapFinishCallback) {
        wrapFinishCallback();
    }
}

bool AnimationUtils::CloseImplicitAnimation(const RefPtr<PipelineBase>& context)
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().CloseAnimation();
#endif
    return false;
}

bool AnimationUtils::CloseImplicitCancelAnimation(const RefPtr<PipelineBase>& context)
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().CloseAnimation();
#endif
    return true;
}

CancelAnimationStatus AnimationUtils::CloseImplicitCancelAnimationReturnStatus(const RefPtr<PipelineBase>& context)
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().CloseAnimation();
#endif
    return CancelAnimationStatus::SUCCESS;
}

bool AnimationUtils::IsImplicitAnimationOpen(const RefPtr<PipelineBase>& context)
{
    return false;
}

void AnimationUtils::Animate(const AnimationOption& option, const PropertyCallback& callback,
    const FinishCallback& finishCallback, const RepeatCallback& repeatCallback, const RefPtr<PipelineBase>& context)
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().SetParams(option, { finishCallback, repeatCallback });
    AnimManager::GetInstance().OpenAnimation();
#endif
    if (callback) {
        callback();
    }
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().CloseAnimation();
    if (AnimManager::Enabled()) {
        return;
    }
#endif

    if (repeatCallback) {
        repeatCallback();
    }
    if (finishCallback) {
        finishCallback();
    }
    auto finishEvent = option.GetOnFinishEvent();
    if (finishEvent) {
        finishEvent();
    }
}

void AnimationUtils::AddKeyFrame(float fraction, const RefPtr<Curve>& curve,
    const PropertyCallback& callback, const RefPtr<PipelineBase>& context)
{
    if (callback) {
        callback();
    }
}
void AnimationUtils::AddKeyFrame(float fraction, const PropertyCallback& callback,
    const RefPtr<PipelineBase>& context)
{
    if (callback) {
        callback();
    }
}

void AnimationUtils::AnimateWithCurrentOptions(
    const PropertyCallback& callback, const FinishCallback& finishCallback,
    bool timingSensitive, const RefPtr<PipelineBase>& context)
{}

void AnimationUtils::AnimateWithCurrentCallback(
    const AnimationOption& option, const PropertyCallback& callback,
    const RefPtr<PipelineBase>& context)
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().OpenAnimation();
    callback();
    AnimManager::GetInstance().CloseAnimation();
#endif
}

std::shared_ptr<AnimationUtils::Animation> AnimationUtils::StartAnimation(const AnimationOption& option,
    const PropertyCallback& callback, const FinishCallback& finishCallback,
    const RepeatCallback& repeatCallback, const RefPtr<PipelineBase>& context)
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().SetParams(option, { finishCallback, repeatCallback });
    AnimManager::GetInstance().OpenAnimation();
    if (callback) {
        callback();
    }
    auto animations = AnimManager::GetInstance().CloseAnimation();
    if (AnimManager::Enabled()) {
        return std::make_shared<Animation>(std::move(animations));
    }

    if (finishCallback) {
        finishCallback();
    }
    return std::make_shared<AnimationUtils::Animation>();
#else
    if (callback) {
        callback();
    }

    if (finishCallback) {
        finishCallback();
    }
    return std::make_shared<AnimationUtils::Animation>();
#endif
}

/* jump to end value of animation */
void AnimationUtils::StopAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{
#ifdef ENHANCED_ANIMATION
    CHECK_NULL_VOID(animation);
    for (auto&& anim : animation->impls_) {
        anim->JumpToEnd();
    }
#endif
}

void AnimationUtils::BlendBgColorAnimation(
    RefPtr<NG::RenderContext>& renderContext, const Color& endColor, int32_t duration, const RefPtr<Curve>& curve)
{}

void AnimationUtils::PauseAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation) {
#ifdef ENHANCED_ANIMATION
    CHECK_NULL_VOID(animation);
    for (auto&& anim : animation->impls_) {
        anim->Pause();
    }
#endif
}

void AnimationUtils::ResumeAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation) {
#ifdef ENHANCED_ANIMATION
    CHECK_NULL_VOID(animation);
    for (auto&& anim : animation->impls_) {
        anim->Resume();
    }
#endif
}

void AnimationUtils::ExecuteWithoutAnimation(const PropertyCallback& callback,
    const RefPtr<PipelineBase>& context)
{
#ifdef ENHANCED_ANIMATION
    if (AnimManager::GetInstance().IsAnimationOpen()) {
        AnimManager::GetInstance().CloseAnimation();
    }
    callback();
#endif
}

std::shared_ptr<AnimationUtils::InteractiveAnimation> AnimationUtils::CreateInteractiveAnimation(
    const InteractiveAnimationCallback& addCallback, const FinishCallback& callback)
{
    if (addCallback) {
        addCallback();
    }
    std::shared_ptr<AnimationUtils::InteractiveAnimation> interactiveAnimation =
        std::make_shared<AnimationUtils::InteractiveAnimation>();
    CHECK_NULL_RETURN(interactiveAnimation, nullptr);
    interactiveAnimation->finishCallback_ = callback;
    return interactiveAnimation;
}

void AnimationUtils::UpdateInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation, float progress)
{}

void AnimationUtils::ContinueInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation)
{
    CHECK_NULL_VOID(interactiveAnimation);
    CHECK_NULL_VOID(interactiveAnimation->finishCallback_);
    interactiveAnimation->finishCallback_();
}

int32_t AnimationUtils::StartInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation)
{
    return 0;
}

void AnimationUtils::ReverseInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation)
{
    CHECK_NULL_VOID(interactiveAnimation);
    CHECK_NULL_VOID(interactiveAnimation->finishCallback_);
    interactiveAnimation->finishCallback_();
}

void AnimationUtils::AddInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation,
    const std::function<void()>& callback)
{
    CHECK_NULL_VOID(interactiveAnimation);
    if (callback) {
        callback();
    }
}
} // namespace OHOS::Ace
