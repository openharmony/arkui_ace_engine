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

#include "ui/animation/animation_utils.h"

#include "core/components_ng/render/animation_utils.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::Kit {

namespace {
std::function<void()> GetWrappedCallback(const std::function<void()>& callback, const bool flushUITasks)
{
    if (!callback) {
        return nullptr;
    }
    if (!flushUITasks) {
        return callback;
    }

    auto wrappedCallback = [propertyCallback = callback]() {
        propertyCallback();
        auto pipeline = PipelineBase::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    };
    return wrappedCallback;
}
}

class AnimationUtils::Animation {
private:
    std::shared_ptr<OHOS::Ace::AnimationUtils::Animation> animation_;
    friend AnimationUtils;
};

void AnimationUtils::Animate(const AnimationOption& option, const AnimationCallback& callback,
    const AnimationCallback& finishCallback, const AnimationCallback& repeatCallback)
{
    OHOS::Ace::AnimationUtils::Animate(option, callback, finishCallback, repeatCallback);
}

std::shared_ptr<AnimationUtils::Animation> AnimationUtils::StartAnimation(const AnimationOption& option,
    const AnimationCallback& callback, const AnimationCallback& finishCallback,
    const AnimationCallback& repeatCallback, bool flushUITasks)
{
    auto propertyCallback = GetWrappedCallback(callback, flushUITasks);
    std::shared_ptr<AnimationUtils::Animation> animation = std::make_shared<AnimationUtils::Animation>();
    auto animations = OHOS::Ace::AnimationUtils::StartAnimation(option, propertyCallback,
        finishCallback, repeatCallback);
    animation->animation_ = animations;
    return animation;
}

void AnimationUtils::StopAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{
    OHOS::Ace::AnimationUtils::StopAnimation(animation->animation_);
    animation->animation_.reset();
}
} // namespace OHOS::Ace::Kit
