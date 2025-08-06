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

#include "core/interfaces/native/ani/ani_theme.h"

#include <cstdint>
#include <vector>

#include "ui/properties/color.h"

#include "base/log/log_wrapper.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG {
std::map<int32_t, AniTheme> AniThemeScope::aniThemes = {};

Color AniThemeColors::ConvertAniValueToColor(AniThemeColorIdentifier identifier) const
{
    auto value = colors_[static_cast<int32_t>(identifier)];
    const auto color = Converter::OptConvert<Color>(value);
    if (!color.has_value()) {
        LOGW("Invalid ani value when convert to color");
        return Color();
    }
    return color.value();
}
} // namespace OHOS::Ace::NG
