/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ANIMATION_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ANIMATION_UTILS_H

#include "core/components_ng/render/animation_utils.h"
namespace OHOS::Ace {
struct AnimationParam {
    std::function<void()> finishCb;
    std::function<void()> repeatCb;
};

class AnimationUtils::Animation {
public:
    Animation() = default;
    Animation(std::set<WeakPtr<NG::PropertyBase>>&& props, AnimationParam&& param, int32_t ticks)
        : params_(std::move(param)), props_(std::move(props)), remainingTicks_(ticks)
    {}

    void Tick();

    bool Finished() const
    {
        return remainingTicks_ <= 0;
    }

private:
    AnimationParam params_;
    std::set<WeakPtr<NG::PropertyBase>> props_;
    int32_t remainingTicks_ = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ANIMATION_UTILS_H
