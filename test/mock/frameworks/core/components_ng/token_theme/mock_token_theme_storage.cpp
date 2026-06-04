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

#include "core/components_ng/token_theme/token_theme_storage.h"

namespace OHOS::Ace::NG {
TokenThemeStorage* TokenThemeStorage::GetInstance()
{
    static TokenThemeStorage instance;
    return &instance;
}

TokenThemeStorage::TokenThemeStorage() = default;

void TokenThemeStorage::StoreThemeScope(TokenThemeScopeId themeScopeId, int32_t themeId)
{
    (void)themeScopeId;
    (void)themeId;
}

void TokenThemeStorage::RemoveThemeScope(TokenThemeScopeId themeScopeId, bool removeToken)
{
    (void)themeScopeId;
    (void)removeToken;
}

const RefPtr<TokenTheme>& TokenThemeStorage::GetTheme(TokenThemeScopeId themeScopeId)
{
    (void)themeScopeId;
    static RefPtr<TokenTheme> empty;
    return empty;
}

void TokenThemeStorage::SetDefaultTheme(const RefPtr<TokenTheme>& theme, ColorMode colorMode)
{
    (void)theme;
    (void)colorMode;
}

void TokenThemeStorage::UpdateDefaultThemeBySystemTheme(ColorMode colorMode)
{
    (void)colorMode;
}

const RefPtr<TokenTheme>& TokenThemeStorage::GetDefaultTheme()
{
    static RefPtr<TokenTheme> empty;
    return empty;
}

ColorMode TokenThemeStorage::CheckLocalAndSystemColorMode()
{
    return ColorMode::LIGHT;
}

void TokenThemeStorage::CacheClear() {}

void TokenThemeStorage::ResetThemeColor(int32_t themeId, RefPtr<TokenTheme>& theme,
    RefPtr<TokenTheme>& defaultTheme, ColorMode& colorMode)
{
    (void)themeId;
    (void)theme;
    (void)defaultTheme;
    (void)colorMode;
}

void TokenThemeStorage::CacheResetColor()
{
    (void)0;
}

void TokenThemeStorage::CacheSet(const RefPtr<TokenTheme>& theme)
{
    (void)theme;
}

const RefPtr<TokenTheme>& TokenThemeStorage::CacheGet(int32_t themeId)
{
    (void)themeId;
    static RefPtr<TokenTheme> empty;
    return empty;
}

void TokenThemeStorage::CacheRemove(int32_t themeId)
{
    (void)themeId;
}

RefPtr<TokenTheme> TokenThemeStorage::ObtainSystemTheme(ColorMode themeColorMode)
{
    (void)themeColorMode;
    return nullptr;
}

RefPtr<TokenTheme> TokenThemeStorage::CreateSystemTokenTheme(ColorMode colorMode)
{
    (void)colorMode;
    return nullptr;
}
} // namespace OHOS::Ace::NG
