/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_ANIMATION_PUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_ANIMATION_PUB_H

#include <string>

namespace OHOS::Ace {

// Forever animation
static constexpr int32_t ANIMATION_REPEAT_INFINITE { -1 };

// normalized max duration time.
static constexpr float NORMALIZED_DURATION_MAX { 1.0f };

// normalized min duration time.
static constexpr float NORMALIZED_DURATION_MIN { 0.0f };

enum class FillMode {
    NONE,
    FORWARDS,
    BACKWARDS,
    BOTH,
};

enum class AnimationDirection {
    NORMAL,
    ALTERNATE,
    REVERSE,
    ALTERNATE_REVERSE,
};

enum class AnimationType {
    TRANSLATE,
    TRANSLATE_X,
    TRANSLATE_Y,
    SCALE,
    SCALE_X,
    SCALE_Y,
    ROTATE_Z,
    ROTATE_X,
    ROTATE_Y,
};

enum class TransitionEffect {
    NONE,
    UNFOLD,
};

using ShareId = std::string;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_ANIMATION_PUB_H
