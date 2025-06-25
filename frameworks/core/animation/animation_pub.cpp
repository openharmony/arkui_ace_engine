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

#include "core/animation/animation_pub.h"

namespace {
const char* g_animationInterfaceNames[4] = {
    "animation",
    "animateTo",
    "animateToImmediately",
    "keyframeAnimateTo",
};
std::atomic<int32_t> g_animationCount = 0;
}

namespace OHOS::Ace {
const char* GetAnimationInterfaceName(AnimationInterface interfaceName)
{
    if (interfaceName < AnimationInterface::ANIMATION
        || interfaceName > AnimationInterface::KEYFRAME_ANIMATE_TO) {
        return nullptr;
    }
    return g_animationInterfaceNames[static_cast<int32_t>(interfaceName)];
}

int32_t GetAnimationFinishCount()
{
    return g_animationCount++;
}
} // namespace OHOS::Ace
