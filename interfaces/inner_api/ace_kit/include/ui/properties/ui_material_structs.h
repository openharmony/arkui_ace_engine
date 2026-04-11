/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_UI_MATERIAL_STRUCTS_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_UI_MATERIAL_STRUCTS_H

#include <array>

#include "ui/base/macros.h"

// This file is used to define structs composed of simple data.

namespace OHOS::Rosen {
class RSNGFilterBase;
} // namespace OHOS::Rosen

namespace OHOS::Ace {

enum class ColorMode;
enum class UiMaterialLevel;
enum class UiMaterialStyle;
enum class UiMaterialTransparency;

struct FrostedGlassParam {
    using Array2 = std::array<float, 2>;
    using Array3 = std::array<float, 3>;
    using Array4 = std::array<float, 4>;
    Array2 blurParams;
    Array2 weightsEmboss;
    Array2 weightsEdl;
    Array2 bgRates;
    Array3 bgKBS;
    Array3 bgPos;
    Array3 bgNeg;
    float bgAlpha = 1.0f;
    Array3 refractParams;
    Array3 sdParams;
    Array2 sdRates;
    Array3 sdKBS;
    Array3 sdPos;
    Array3 sdNeg;
    Array3 envLightParams;
    Array2 envLightRates;
    Array3 envLightKBS;
    Array3 envLightPos;
    Array3 envLightNeg;
    Array2 edLightParams;
    Array2 edLightAngles;
    Array2 edLightDir;
    Array2 edLightRates;
    Array3 edLightKBS;
    Array3 edLightPos;
    Array3 edLightNeg;
    bool baseVibrancyEnabled = true;
    Array4 materialColor;
    float samplingScale = 1.0f;
    Array2 darkModeBlurParams;
    Array2 darkModeWeightsEmboss;
    Array2 darkModeBgRates;
    Array3 darkModeBgKBS;
    Array3 darkModeBgPos;
    Array3 darkModeBgNeg;
    Array2 darkModeEdLightAngles;
    Array3 darkModeEdLightKBS;
};

struct ArkUIMaterialKeyParams {
    int32_t level;
    int32_t style;
    int32_t transparency;
    int32_t colorMode;
    float dipScale = 1.0f;
};

struct UiMaterialMapKey {
    UiMaterialLevel level;
    UiMaterialStyle style;
    UiMaterialTransparency transparency;
    ColorMode colorMode;

    bool operator==(const UiMaterialMapKey& other) const
    {
        return level == other.level && style == other.style && transparency == other.transparency &&
               colorMode == other.colorMode;
    }
};

struct ACE_FORCE_EXPORT UiMaterialMapKeyHasher {
    static std::size_t GetOpValue(size_t value, int needDigit, int shiftDigit) {
        size_t mask = (static_cast<std::size_t>(1) << needDigit) - 1;
        return ((value & mask) << shiftDigit);
    }
    std::size_t operator()(const UiMaterialMapKey& key) const;
};
}

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_UI_MATERIAL_STRUCTS_H
