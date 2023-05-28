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

#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace {

namespace {

using PropertyCallback = std::function<void()>;
using FinishCallback = std::function<void()>;
using RepeatCallback = std::function<void()>;

} // namespace

class AnimationUtils {
public:
    class Animation;

    static void OpenImplicitAnimation(
        const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallback);
    static bool CloseImplicitAnimation();
    static void Animate(const AnimationOption& option, const PropertyCallback& callback,
        const FinishCallback& finishCallback = nullptr, const RepeatCallback& repeatCallback = nullptr);
    static void AddKeyFrame(float fraction, const RefPtr<Curve>& curve, const PropertyCallback& callback);
    static void AddKeyFrame(float fraction, const PropertyCallback& callback);

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
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ANIMATION_UTILS_H
