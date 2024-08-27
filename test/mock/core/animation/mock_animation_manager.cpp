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

#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {
void MockAnimationManager::CancelAnimations()
{
    for (auto&& prop : activeProps_) {
        auto it = propToAnimation_.find(prop);
        if (it == propToAnimation_.end()) {
            continue;
        }
        auto anim = it->second.Upgrade();
        if (anim) {
            anim->End();
        }
    }
}

std::vector<RefPtr<MockImplicitAnimation>> MockAnimationManager::CloseAnimation()
{
    inScope_ = false;
    if (activeProps_.empty()) {
        return {};
    }
    if (params_.type == AnimationOperation::CANCEL) {
        CancelAnimations();
        return {};
    }
    // capture active props in animation
    std::vector<RefPtr<MockImplicitAnimation>> res;
    for (auto&& prop : activeProps_) {
        auto anim = propToAnimation_[prop].Upgrade();
        if (anim) {
            // update existing animation instead
            anim->Update(params_.callbacks, ticks_);
            continue;
        }
        res.emplace_back(AceType::MakeRefPtr<MockImplicitAnimation>(prop, params_.callbacks, ticks_));
        propToAnimation_[prop] = res.back();
        animations_.emplace_back(res.back());
    }
    activeProps_.clear();
    return res;
}

void MockAnimationManager::Tick()
{
    for (auto it = animations_.begin(); it != animations_.end();) {
        auto&& anim = *it;
        if (!anim || anim->Finished()) {
            it = animations_.erase(it);
        } else {
            anim->Next();
            ++it;
        }
    }
}

void MockAnimationManager::Reset()
{
    propToAnimation_.clear();
    activeProps_.clear();
    animations_.clear();
    params_.callbacks.finishCb = nullptr;
    params_.callbacks.repeatCb = nullptr;
    ticks_ = 1;
    inScope_ = false;
}
} // namespace OHOS::Ace::NG