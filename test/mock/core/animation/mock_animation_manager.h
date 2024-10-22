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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ANIMATION_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ANIMATION_MANAGER_H
#include "test/mock/core/animation/mock_implicit_animation.h"

#include "core/components_ng/base/modifier.h"
#include "frameworks/base/utils/singleton.h"
namespace OHOS::Ace::NG {

class MockAnimationManager : public Singleton<MockAnimationManager> {
private:
    MockAnimationManager() = default;
    ~MockAnimationManager() override = default;
    friend Singleton<MockAnimationManager>;
    ACE_DISALLOW_COPY_AND_MOVE(MockAnimationManager);

public:
    static void Enable(bool value)
    {
        GetInstance().enabled_ = value;
    }
    static bool Enabled()
    {
        return GetInstance().enabled_;
    }

    void OpenAnimation()
    {
        inScope_ = true;
    }
    std::vector<RefPtr<MockImplicitAnimation>> CloseAnimation();

    bool IsAnimationOpen() const
    {
        return inScope_;
    }

    /**
     * @brief Configure number of ticks for future animations
     */
    void SetTicks(int32_t tick)
    {
        ticks_ = tick;
    }

    struct AnimationParams {
        AnimationCallbacks callbacks;
        AnimationOperation type = AnimationOperation::PLAY;

        void Reset()
        {
            callbacks.finishCb = nullptr;
            callbacks.repeatCb = nullptr;
            type = AnimationOperation::PLAY;
        }
    };

    void SetParams(const AnimationOption& option, AnimationCallbacks&& cbs);

    void AddActiveProp(const WeakPtr<PropertyBase>& prop)
    {
        if (inScope_) {
            activeProps_.insert(prop);
        }
    }

    /**
     * @brief advance all animations by one frame
     *
     */
    void Tick();

    /**
     * @brief Force update animations by @c delta to simulate velocity animation
     *
     */
    void TickByVelocity(float velocity);

    void Reset();

    bool AllFinished();

private:
    void CancelAnimations();

    AnimationParams params_;
    std::list<RefPtr<MockImplicitAnimation>> animations_;
    std::set<WeakPtr<PropertyBase>> activeProps_;
    std::map<WeakPtr<PropertyBase>, WeakPtr<MockImplicitAnimation>> propToAnimation_;

    int32_t ticks_ = 1;
    bool inScope_ = false;
    bool enabled_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ANIMATION_MANAGER_H
