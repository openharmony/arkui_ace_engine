/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/modifier_adapter.h"

namespace OHOS::Ace::NG {
void ModifierAdapter::RemoveModifier(int32_t modifierId) {}
template<typename T, typename S>
void NodeAnimatableProperty<T, S>::AnimateWithVelocity(
    const AnimationOption& option, T value, T velocity, const FinishCallback& finishCallback)
{
#ifdef ENHANCED_ANIMATION
    if (!MockAnimationManager::Enabled()) {
        return;
    }
    MockAnimationManager::GetInstance().SetParams(option, { finishCallback, nullptr });
    MockAnimationManager::GetInstance().OpenAnimation();
    Set(value);
    MockAnimationManager::GetInstance().CloseAnimation();
#endif
}

template<typename T, typename S>
void NodeAnimatableProperty<T, S>::SetThresholdType(ThresholdType type)
{}
template<typename T, typename S>
void NodeAnimatableProperty<T, S>::SetPropertyUnit(PropertyUnit unit)
{}

// Explicit template instantiations
template class NodeAnimatableProperty<float, AnimatablePropertyFloat>;
template class NodeAnimatableProperty<OffsetF, AnimatablePropertyOffsetF>;
} // namespace OHOS::Ace::NG