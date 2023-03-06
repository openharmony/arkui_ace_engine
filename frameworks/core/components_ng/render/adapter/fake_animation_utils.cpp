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
#ifndef ENABLE_ROSEN_BACKEND
void AnimationUtils::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& wrapFinishCallback)
{}

bool AnimationUtils::CloseImplicitAnimation()
{
    return false;
}

void AnimationUtils::Animate(
    const AnimationOption& option, const PropertyCallback& callback, const FinishCallback& finishCallback)
{}

class AnimationUtils::Animation {
};

void AnimationUtils::AddKeyFrame(
    float fraction, const RefPtr<Curve>& curve, const PropertyCallback& callback)
{}

void AnimationUtils::AddKeyFrame(float fraction, const PropertyCallback& callback)
{}

std::shared_ptr<AnimationUtils::Animation> AnimationUtils::StartAnimation(
    const AnimationOption& option, const PropertyCallback& callback, const FinishCallback& finishCallback)
{
    return nullptr;
}

void AnimationUtils::StopAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{}
#endif
} // namespace OHOS::Ace
