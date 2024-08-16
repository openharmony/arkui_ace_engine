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

#include "test/mock/core/render/mock_animation_utils.h"

#include "test/mock/core/render/mock_animation_manager.h"
#include "test/mock/core/render/mock_animation_proxy.h"

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace {
void AnimationUtils::Animation::UpdateProp(const WeakPtr<NG::PropertyBase>& propWk) const
{
#ifdef ENHANCED_ANIMATION
    if (auto prop = AceType::DynamicCast<NG::AnimatablePropertyFloat>(propWk.Upgrade()); prop) {
        NG::MockAnimationProxy<float>::GetInstance().Next(prop, remainingTicks_);
        auto cb = prop->GetUpdateCallback();
        if (cb) {
            cb(NG::MockAnimationProxy<float>::GetInstance().GetStagingValue(prop));
        }
    }
    /* add update code for other types */
#endif
}

void AnimationUtils::Animation::Next()
{
    if (Finished()) {
        return;
    }
    for (const auto& propWk : props_) {
        UpdateProp(propWk);
    }
    if (params_.repeatCb) {
        params_.repeatCb();
    }
    if (--remainingTicks_ <= 0) {
        if (params_.finishCb) {
            params_.finishCb();
        }
    }
}

#ifdef ENHANCED_ANIMATION
using AnimManager = NG::MockAnimationManager;
#endif

class AnimationUtils::InteractiveAnimation {
public:
    FinishCallback finishCallback_;
};

void AnimationUtils::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& wrapFinishCallback)
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().OpenAnimation();
#endif
    if (wrapFinishCallback) {
        wrapFinishCallback();
    }
}

bool AnimationUtils::CloseImplicitAnimation()
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().CloseAnimation();
#endif
    return false;
}

bool AnimationUtils::IsImplicitAnimationOpen()
{
    return false;
}

void AnimationUtils::Animate(const AnimationOption& option, const PropertyCallback& callback,
    const FinishCallback& finishCallback, const RepeatCallback& repeatCallback)
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().SetParams({ finishCallback, repeatCallback });
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

void AnimationUtils::AddKeyFrame(float fraction, const RefPtr<Curve>& curve, const PropertyCallback& callback)
{
    if (callback) {
        callback();
    }
}
void AnimationUtils::AddKeyFrame(float fraction, const PropertyCallback& callback)
{
    if (callback) {
        callback();
    }
}

void AnimationUtils::AnimateWithCurrentOptions(
    const PropertyCallback& callback, const FinishCallback& finishCallback, bool timingSensitive)
{}
void AnimationUtils::AnimateWithCurrentCallback(const AnimationOption& option, const PropertyCallback& callback) {}

std::shared_ptr<AnimationUtils::Animation> AnimationUtils::StartAnimation(const AnimationOption& option,
    const PropertyCallback& callback, const FinishCallback& finishCallback, const RepeatCallback& repeatCallback)
{
#ifdef ENHANCED_ANIMATION
    AnimManager::GetInstance().SetParams({ finishCallback, repeatCallback });
    AnimManager::GetInstance().OpenAnimation();
#endif
    if (callback) {
        callback();
    }
#ifdef ENHANCED_ANIMATION
    auto animation = AnimManager::GetInstance().CloseAnimation();
    if (AnimManager::Enabled()) {
        return animation;
    }
#endif

    if (finishCallback) {
        finishCallback();
    }
    return std::make_shared<AnimationUtils::Animation>();
}

void AnimationUtils::StopAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation) {}

void AnimationUtils::BlendBgColorAnimation(
    RefPtr<NG::RenderContext>& renderContext, const Color& endColor, int32_t duration, const RefPtr<Curve>& curve)
{}

void AnimationUtils::PauseAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation) {}

void AnimationUtils::ResumeAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation) {}

void AnimationUtils::ExecuteWithoutAnimation(const PropertyCallback& callback) {}

std::shared_ptr<AnimationUtils::InteractiveAnimation> AnimationUtils::CreateInteractiveAnimation(
    const InteractiveAnimationCallback& addCallback, const FinishCallback& callback)
{
    addCallback();
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
} // namespace OHOS::Ace
