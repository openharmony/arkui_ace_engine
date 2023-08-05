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

#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace {
class AnimationUtils::Animation {};

void AnimationUtils::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& wrapFinishCallback)
{
    if (wrapFinishCallback) {
        wrapFinishCallback();
    }
}

bool AnimationUtils::CloseImplicitAnimation()
{
    return false;
}

void AnimationUtils::Animate(const AnimationOption& option, const PropertyCallback& callback,
    const FinishCallback& finishCallback, const RepeatCallback& repeatCallback)
{
    if (callback) {
        callback();
    }
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
    return std::make_shared<AnimationUtils::Animation>();
}

void AnimationUtils::StopAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation) {}

void AnimationUtils::BlendBgColorAnimation(
    RefPtr<NG::RenderContext>& renderContext, const Color& endColor, int32_t duration, const RefPtr<Curve>& curve)
{}

void AnimationUtils::PauseAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation) {}

void AnimationUtils::ResumeAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation) {}
} // namespace OHOS::Ace
