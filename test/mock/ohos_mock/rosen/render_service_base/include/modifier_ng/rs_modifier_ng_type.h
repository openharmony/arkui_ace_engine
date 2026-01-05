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

#ifndef RENDER_SERVICE_BASE_MODIFIER_NG_RS_MODIFIER_NG_TYPE_H
#define RENDER_SERVICE_BASE_MODIFIER_NG_RS_MODIFIER_NG_TYPE_H

#include <bitset>
#include <string>
#include <unordered_map>

namespace OHOS::Rosen::ModifierNG {
enum class RSModifierType : uint16_t {
    INVALID = 0,
    BOUNDS = 1,
    FRAME = 2,
    TRANSFORM = 3,
    ALPHA = 4,

    FOREGROUND_COLOR = 5,
    BACKGROUND_COLOR = 6,
    BACKGROUND_SHADER = 7,
    BACKGROUND_IMAGE = 8,

    BORDER = 9,
    OUTLINE = 10,
    CLIP_TO_BOUNDS = 11,
    CLIP_TO_FRAME = 12,
    VISIBILITY = 13,

    DYNAMIC_LIGHT_UP = 14,
    SHADOW = 15,
    MASK = 16,
    PIXEL_STRETCH = 17,
    USE_EFFECT = 18,
    BLENDER = 19,

    POINT_LIGHT = 20,
    PARTICLE_EFFECT = 21,
    COMPOSITING_FILTER = 22,
    BACKGROUND_FILTER = 23,
    FOREGROUND_FILTER = 24,

    TRANSITION_STYLE = 25,
    BACKGROUND_STYLE = 26,
    CONTENT_STYLE = 27,
    FOREGROUND_STYLE = 28,
    OVERLAY_STYLE = 29,
    NODE_MODIFIER = 30,

    ENV_FOREGROUND_COLOR = 31,
    HDR_BRIGHTNESS = 32,
    BEHIND_WINDOW_FILTER = 33,
    BACKGROUND_NG_SHADER = 34,
    FOREGROUND_SHADER = 35,

    CHILDREN, // PLACEHOLDER, no such modifier, but we need a dirty flag

    MAX = CHILDREN + 1,
};

enum class RSPropertyType : uint16_t {
#define X(name) name,
#include "rs_property_ng_type.in"
#undef X
};
} // namespace OHOS::Rosen::ModifierNG
#endif // RENDER_SERVICE_BASE_MODIFIER_NG_RS_MODIFIER_NG_TYPE_H
