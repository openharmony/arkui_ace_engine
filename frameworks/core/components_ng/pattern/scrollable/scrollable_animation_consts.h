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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_ANIMATION_CONSTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_ANIMATION_CONSTS_H

#include <cstdint>

namespace OHOS::Ace::NG {
inline constexpr float FLING_SCALE_K = 1.5f; // x(t) = [K / (4.2 * γ)] * v₀ * [1 - exp(-γt)]
inline constexpr float FRICTION_SCALE = -4.2f;
inline constexpr uint32_t CUSTOM_SPRING_ANIMATION_DURATION = 1000;
}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_ANIMATION_CONSTS_H