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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_ANIMATION_UTILS_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_ANIMATION_UTILS_H

#include <functional>
#include <memory>

#include "ui/animation/animation_option.h"
#include "ui/base/macros.h"

namespace OHOS::Ace::Kit {

using AnimationCallback = std::function<void()>;

class ACE_FORCE_EXPORT AnimationUtils {
public:
    class Animation;

    static void Animate(const AnimationOption& option, const AnimationCallback& callback,
        const AnimationCallback& finishCallback = nullptr, const AnimationCallback& repeatCallback = nullptr);
    static std::shared_ptr<AnimationUtils::Animation> StartAnimation(const AnimationOption& option,
        const AnimationCallback& callback, const AnimationCallback& finishCallback = nullptr,
        const AnimationCallback& repeatCallback = nullptr, bool flushUITasks = true);
    static void StopAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation);
};
} // namespace OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_ANIMATION_UTIL_H
