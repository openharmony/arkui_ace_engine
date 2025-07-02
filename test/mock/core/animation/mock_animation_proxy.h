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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ANIMATION_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ANIMATION_PROXY_H
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {
/* mocking RSAnimatableProperty */
template<typename T>
class MockAnimationProxy : public Singleton<MockAnimationProxy<T>> {
private:
    MockAnimationProxy() = default;
    ~MockAnimationProxy() = default;
    friend Singleton<MockAnimationProxy>;
    ACE_DISALLOW_COPY_AND_MOVE(MockAnimationProxy);

public:
    void RegisterProperty(const WeakPtr<AnimatableProperty<T>>& ptr, T value)
    {
        props_[ptr] = { value, value };
    }

    void RecordPropChange(const WeakPtr<AnimatableProperty<T>>& ptr, T targetValue)
    {
        auto& prop = props_[ptr];
        if (!MockAnimationManager::GetInstance().IsAnimationOpen()) {
            prop = { targetValue, targetValue };
            return;
        }

        prop.endValue_ = targetValue;
        MockAnimationManager::GetInstance().AddActiveProp(ptr);
    }

    T GetEndValue(const WeakPtr<AnimatableProperty<T>>& ptr)
    {
        auto it = props_.find(ptr);
        if (it == props_.end()) {
            return {};
        }
        return it->second.endValue_;
    }

    T GetValue(const WeakPtr<AnimatableProperty<T>>& ptr)
    {
        auto it = props_.find(ptr);
        if (it == props_.end()) {
            return {};
        }
        return it->second.value_;
    }

    /* move value by one frame */
    void Next(const WeakPtr<AnimatableProperty<T>>& ptr, int32_t remainingTicks)
    {
        auto it = props_.find(ptr);
        if (it == props_.end() || remainingTicks == 0) {
            return;
        }
        T delta = (it->second.endValue_ - it->second.value_) / remainingTicks;
        it->second.value_ += delta;
    }

    void ForceUpdate(const WeakPtr<AnimatableProperty<T>>& ptr, T delta)
    {
        auto it = props_.find(ptr);
        if (it == props_.end()) {
            return;
        }
        it->second.value_ += delta;
    }

private:
    struct PropertyImpl {
        T value_;
        T endValue_;
    };
    std::map<WeakPtr<AnimatableProperty<T>>, PropertyImpl> props_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ANIMATION_PROXY_H
