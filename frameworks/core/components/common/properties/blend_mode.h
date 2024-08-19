/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BLEND_MODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BLEND_MODE_H

#include <cstdint>

namespace OHOS::Ace {
// A style class indicates the way to render blendMode effect
enum class BlendMode : int16_t {
    NONE = 0, // Note: The NONE blend mode is different from SRC_OVER. When using it with
              // RSColorBlendApplyType::SAVE_LAYER, it does not create an offscreen buffer. However, when using it
              // with RSColorBlendApplyType::FAST, it does not modify the blend mode of subsequent content.

    CLEAR,    // r = 0
    SRC,      // r = s
    DST,      // r = d
    SRC_OVER, // r = s + (1-sa)*d
    DST_OVER, // r = d + (1-da)*s
    SRC_IN,   // r = s * da
    DST_IN,   // r = d * sa
    SRC_OUT,  // r = s * (1-da)
    DST_OUT,  // r = d * (1-sa)
    SRC_ATOP, // r = s*da + d*(1-sa)
    DST_ATOP, // r = d*sa + s*(1-da)
    XOR,      // r = s*(1-da) + d*(1-sa)
    PLUS,     // r = min(s + d, 1)
    MODULATE, // r = s*d
    SCREEN,   // r = s + d - s*d

    OVERLAY,     // multiply or screen, depending on destination
    DARKEN,      // rc = s + d - max(s*da, d*sa), ra = SRC_OVER
    LIGHTEN,     // rc = s + d - min(s*da, d*sa), ra = SRC_OVER
    COLOR_DODGE, // brighten destination to reflect source
    COLOR_BURN,  // darken destination to reflect source
    HARD_LIGHT,  // multiply or screen, depending on source
    SOFT_LIGHT,  // lighten or darken, depending on source
    DIFF,        // rc = s + d - 2*(min(s*da, d*sa)), ra = SRC_OVER
                 // Due to naming conflicts with macro in winuser.h, DIFFERENCE was changed to DIFF
    EXCLUSION,   // rc = s + d - two(s*d), ra = SRC_OVER
    MULTIPLY,    // r = s*(1-da) + d*(1-sa) + s*d

    HUE,        // hue of source with saturation and luminosity of destination
    SATURATION, // saturation of source with hue and luminosity of destination
    COLOR,      // hue and saturation of source with luminosity of destination
    LUMINOSITY, // luminosity of source with hue and saturation of destination

    BACK_COMPAT_SOURCE_IN,
    MAX
};

enum class BlendApplyType : int16_t {
    FAST = 0,    // Apply blending by drawing the content with the blend mode, without using an offscreen buffer

    OFFSCREEN,   // Apply blending by drawing the content onto an offscreen buffer and blend it when drawing it
                 // back to the screen
    MAX
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BLEND_MODE_H
