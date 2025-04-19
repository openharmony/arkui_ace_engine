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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ANIMATION_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ANIMATION_UTILS_H

#include "base/utils/macros.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/color.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace {

namespace NG {
class RenderContext;
}

namespace {

using PropertyCallback = std::function<void()>;
using FinishCallback = std::function<void()>;
using RepeatCallback = std::function<void()>;
using InteractiveAnimationCallback = std::function<void()>;
} // namespace

class ACE_FORCE_EXPORT AnimationUtils {
public:
    class Animation;

    class InteractiveAnimation;

    static void OpenImplicitAnimation(
        const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallback);
    static bool CloseImplicitAnimation();
    static bool CloseImplicitCancelAnimation();
    static bool IsImplicitAnimationOpen();
    static void Animate(const AnimationOption& option, const PropertyCallback& callback,
        const FinishCallback& finishCallback = nullptr, const RepeatCallback& repeatCallback = nullptr);
    static void AddKeyFrame(float fraction, const RefPtr<Curve>& curve, const PropertyCallback& callback);
    static void AddKeyFrame(float fraction, const PropertyCallback& callback);
    static void AddDurationKeyFrame(int duration, const RefPtr<Curve>& curve, const PropertyCallback& callback);

    // Similar to Animate, but reuses current options and replaces callback
    static void AnimateWithCurrentOptions(
        const PropertyCallback& callback, const FinishCallback& finishCallback, bool timingSensitive = true);
    // Similar to Animate, but reuses current callback and replaces options
    static void AnimateWithCurrentCallback(const AnimationOption& option, const PropertyCallback& callback);

    static std::shared_ptr<AnimationUtils::Animation> StartAnimation(const AnimationOption& option,
        const PropertyCallback& callback, const FinishCallback& finishCallback = nullptr,
        const RepeatCallback& repeatCallback = nullptr);
    static void StopAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation);
    static void BlendBgColorAnimation(
        RefPtr<NG::RenderContext>& renderContext, const Color& endColor, int32_t duration, const RefPtr<Curve>& curve);
    static void PauseAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation);
    static void ResumeAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation);
    static void ExecuteWithoutAnimation(const PropertyCallback& callback);

    static std::shared_ptr<AnimationUtils::InteractiveAnimation> CreateInteractiveAnimation(
        const InteractiveAnimationCallback& addCallback, const FinishCallback& callback);

    static void UpdateInteractiveAnimation(
        const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation, float progress);

    static void ContinueInteractiveAnimation(
        const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation);

    static int32_t StartInteractiveAnimation(
        const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation);

    static void ReverseInteractiveAnimation(
        const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation);

    static void AddInteractiveAnimation(
        const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation,
        const std::function<void()>& callback);

    static void SetNavGroupNodeTransAnimationCallback();
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ANIMATION_UTILS_H
