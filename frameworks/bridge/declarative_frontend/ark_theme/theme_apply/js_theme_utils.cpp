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

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"

namespace OHOS::Ace::Framework {

std::shared_mutex JSThemeUtils::themeMutex_;

std::optional<JSTheme> JSThemeUtils::GetTheme()
{
    std::shared_lock<std::shared_mutex> lock(themeMutex_);
    return JSThemeScope::jsCurrentTheme;
}

std::optional<JSThemeColors> JSThemeUtils::GetThemeColors()
{
    std::shared_lock<std::shared_mutex> lock(themeMutex_);
    return (JSThemeScope::jsCurrentTheme) ? std::make_optional(JSThemeScope::jsCurrentTheme->Colors()) : std::nullopt;
}

void JSThemeUtils::SwapCurrentTheme(std::optional<JSTheme>& themeOpt)
{
    std::unique_lock<std::shared_mutex> lock(themeMutex_);
    JSThemeScope::jsCurrentTheme.swap(themeOpt);
}

void JSThemeUtils::SaveTheme(int32_t themeScopeId, const JSThemeColors& colors, const JSThemeColors& darkColors)
{
    std::unique_lock<std::shared_mutex> lock(themeMutex_);
    JSThemeScope::jsThemes[themeScopeId].SetColors(colors);
    JSThemeScope::jsThemes[themeScopeId].SetDarkColors(darkColors);
    if (JSThemeScope::isCurrentThemeDefault || themeScopeId > 0) {
        JSThemeScope::jsCurrentTheme = JSThemeScope::jsThemes[themeScopeId];
    }
}

void JSThemeUtils::SetCurrentThemeByScopeId(int32_t themeScopeId)
{
    std::unique_lock<std::shared_mutex> lock(themeMutex_);
    JSThemeScope::isCurrentThemeDefault = (themeScopeId == 0);
    auto theme = JSThemeScope::jsThemes.find(themeScopeId);
    if (theme != JSThemeScope::jsThemes.end()) {
        JSThemeScope::jsCurrentTheme = theme->second;
    } else {
        JSThemeScope::jsCurrentTheme = std::nullopt;
    }
}

void JSThemeUtils::RemoveTheme(int32_t themeScopeId)
{
    std::unique_lock<std::shared_mutex> lock(themeMutex_);
    JSThemeScope::jsThemes.erase(themeScopeId);
}
} // namespace OHOS::Ace::Framework