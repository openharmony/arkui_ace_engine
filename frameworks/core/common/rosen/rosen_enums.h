/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_ENUMS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_ENUMS_H

namespace OHOS::Ace {
enum MATERIAL_BLUR_STYLE : int {
    // no material
    NO_MATERIAL            = 0,
    // card blur style
    STYLE_CARD_THIN_LIGHT  = 1,
    STYLE_CARD_LIGHT       = 2,
    STYLE_CARD_THICK_LIGHT = 3,
    STYLE_CARD_THIN_DARK   = 4,
    STYLE_CARD_DARK        = 5,
    STYLE_CARD_THICK_DARK  = 6,

    // background blur style
    STYLE_BACKGROUND_SMALL_LIGHT  = 101,
    STYLE_BACKGROUND_MEDIUM_LIGHT = 102,
    STYLE_BACKGROUND_LARGE_LIGHT  = 103,
    STYLE_BACKGROUND_XLARGE_LIGHT = 104,
    STYLE_BACKGROUND_SMALL_DARK   = 105,
    STYLE_BACKGROUND_MEDIUM_DARK  = 106,
    STYLE_BACKGROUND_LARGE_DARK   = 107,
    STYLE_BACKGROUND_XLARGE_DARK  = 108
};
} // namespace OHOS::Ace
#endif  // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_ENUMS_H
