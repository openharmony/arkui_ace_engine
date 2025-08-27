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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_TEXT_KERBOARD_COMMON_TYPE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_TEXT_KERBOARD_COMMON_TYPE_H

#include <cstdint>

namespace OHOS::Ace::NG {

enum class KeyboardGradientMode {
    BEGIN = -1,
    UNSPECIFIED = BEGIN,
    NONE = 0,
    LINEAR_GRADIENT = 1,
    END = LINEAR_GRADIENT,
};

enum class KeyboardFluidLightMode {
    BEGIN = -1,
    UNSPECIFIED = BEGIN,
    NONE = 0,
    BACKGROUND_FLUID_LIGHT = 1,
    END = BACKGROUND_FLUID_LIGHT,
};

struct KeyboardAppearanceConfig {
    KeyboardGradientMode gradientMode;
    KeyboardFluidLightMode fluidLightMode;
};

}; // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_TEXT_KERBOARD_COMMON_TYPE_H