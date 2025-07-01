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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ANI_THEME_MODULE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_ANI_THEME_MODULE_H

#include <cstdint>
#include <vector>

#include "ui/properties/color.h"

#include "base/utils/device_config.h"

namespace OHOS::Ace::NG {
class AniThemeModule final {
public:
    static void UpdateColorMode(int32_t colorMode);
    static void RestoreColorMode();

private:
    static ColorMode MapAniColorModeToColorMode(int32_t aniColorMode);
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    static void UpdateColorModeForThemeConstants(const ColorMode& colorMode);
#endif
};
} // namespace OHOS::Ace::NG

#endif
