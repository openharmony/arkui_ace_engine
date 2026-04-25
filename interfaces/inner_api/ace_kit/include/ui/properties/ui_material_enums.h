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
 
#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_UI_MATERIAL_ENUM_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_UI_MATERIAL_ENUM_H

namespace OHOS::Ace {

enum class MaterialType: int32_t {
    NONE = 0,
    SEMI_TRANSPARENT = 1,
    IMMERSIVE = 2,
    MAX = IMMERSIVE,
};

enum class UiMaterialStyle: int32_t {
    ULTRA_THIN = 0,
    THIN = 1,
    REGULAR = 2,
    THICK = 3,
    ULTRA_THICK = 4,
    MAX = ULTRA_THICK,
};

enum class UiMaterialLevel: int32_t {
    EXQUISITE = 0,
    GENTLE = 1,
    SMOOTH = 2,
    DEFAULT = SMOOTH,
    MAX = SMOOTH,
};

enum class UiMaterialTransparency: int32_t {
    NONE = -1,
    THIN = 0,
    NORMAL = 1,
    THICK = 2,
    GENTLE_THIN = 3,
    GENTLE_NORMAL = 4,
    GENTLE_THICK = 5,
};

enum class UiMaterialFilterQuality: int32_t {
    DEFAULT = 0,
    ADAPTIVE = 1,
};

enum class MaterialTransparency: int32_t {
    NONE = -1,
    THIN = 0,
    NORMAL = 1,
    THICK = 2,
    GENTLE_THIN = 3,
    GENTLE_NORMAL = 4,
    GENTLE_THICK = 5,
};

enum class MaterialState {
    DEFAULT = 0,
    ENABLE = 1,
    DISABLE = 2,
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_UI_MATERIAL_ENUM_H
