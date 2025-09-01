/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_ANI_THEME_UTILS_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_ANI_THEME_UTILS_H

#include <optional>
#include <cstdint>

#include "bridge/arkts_frontend/arkts_ani_utils.h"
#include "core/interfaces/native/ani/ani_theme.h"

namespace OHOS::Ace::NG {
class AniThemeUtils {
public:
    static constexpr int32_t DEFAULT_ALPHA = 255;
    static constexpr double DEFAULT_OPACITY = 0.2;

    static std::optional<NG::AniTheme> GetTheme()
    {
        return NG::AniThemeScope::aniCurrentTheme;
    }

    static RefPtr<NG::AniThemeColors> GetThemeColors()
    {
        return (NG::AniThemeScope::aniCurrentTheme) ? NG::AniThemeScope::aniCurrentTheme->Colors() : nullptr;
    }
};
}
#endif //FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_ANI_THEME_UTILS_H