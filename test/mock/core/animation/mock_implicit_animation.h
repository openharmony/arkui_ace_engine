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

#include "base/memory/ace_type.h"
#include "core/components_ng/render/animation_utils.h"
namespace OHOS::Ace {

struct AnimationCallbacks {
    std::function<void()> finishCb;
    std::function<void()> repeatCb;
};
class MockImplicitAnimation : public AceType {
    DECLARE_ACE_TYPE(MockImplicitAnimation, AceType);

public:
    MockImplicitAnimation(WeakPtr<NG::PropertyBase> prop, AnimationCallbacks cbs, int32_t ticks)
        : cbs_(std::move(cbs)), prop_(std::move(prop)), remainingTicks_(ticks)
    {}

    void Update(AnimationCallbacks cbs, int32_t ticks)
    {
        cbs_ = std::move(cbs);
        remainingTicks_ = ticks;
    }

    void Next();

    bool Finished() const
    {
        return remainingTicks_ <= 0;
    }

    void End()
    {
        remainingTicks_ = 0;
    }

private:
    void UpdateProp(const WeakPtr<NG::PropertyBase>& propWk) const;

    AnimationCallbacks cbs_;
    WeakPtr<NG::PropertyBase> prop_;
    int32_t remainingTicks_ = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ANIMATION_UTILS_H