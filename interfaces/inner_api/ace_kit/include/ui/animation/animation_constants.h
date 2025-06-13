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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_ANIMATION_CONSTANTS_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_ANIMATION_CONSTANTS_H

#include <atomic>
#include <string>
#include <cstdint>

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

enum class AnimationOperation {
    NONE,
    PLAY,
    RUNNING,
    FINISH,
    PAUSE,
    CANCEL,
    REVERSE,
};

enum class AnimationType {
    TRANSLATE,
    TRANSLATE_X,
    TRANSLATE_Y,
    TRANSLATE_Z,
    TRANSLATE_3D,
    SCALE,
    SCALE_X,
    SCALE_Y,
    SCALE_Z,
    SCALE_3D,
    ROTATE_Z,
    ROTATE_X,
    ROTATE_Y,
    ROTATE,
    ROTATE_3D,
    SKEW,
    SKEW_X,
    SKEW_Y,
    MATRIX_3D,
    MATRIX_2D,
    PERSPECTIVE
};

enum class TransitionEffect {
    NONE,
    UNFOLD,
};

enum class TransitionType {
    ALL,
    APPEARING,
    DISAPPEARING
};

enum class FinishCallbackType {
    REMOVED = 0,
    LOGICALLY = 1
};

enum class AnimationInterface : int32_t {
    UNKNOWN = -1,
    ANIMATION,
    ANIMATE_TO,
    ANIMATE_TO_IMMEDIATELY,
    KEYFRAME_ANIMATE_TO,
    TRANSITION,
    SHARED_TRANSITION,
    PAGE_TRANSITION,
};

enum class AnimationPropertyType : int32_t {
    ROTATION = 0,
    TRANSLATION,
    SCALE,
    OPACITY,
};

enum class CancelAnimationStatus : int32_t {
    SUCCESS = 0,
    NULL_ANIMATOR,
    NO_OPEN_CLOSURE,
    INCORRECT_PARAM_TYPE,
    EMPTY_PENDING_SYNC_LIST,
    TASK_EXECUTION_FAILURE,
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_ANIMATION_CONSTANTS_H
