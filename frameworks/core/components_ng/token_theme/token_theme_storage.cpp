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

#include "core/components_ng/token_theme/token_theme_storage.h"

#include <memory>

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

thread_local std::unique_ptr<TokenThemeStorage> TokenThemeStorage::instance_ = nullptr;

TokenThemeStorage* TokenThemeStorage::GetInstance()
{
    if (!instance_) {
        instance_.reset(new TokenThemeStorage);
    }
    return instance_.get();
}

TokenThemeStorage::TokenThemeStorage() = default;

void TokenThemeStorage::StoreThemeScope(TokenThemeScopeId themeScopeId, int32_t themeId)
{
    themeScopeMap_[themeScopeId] = themeId;
}

void TokenThemeStorage::RemoveThemeScope(TokenThemeScopeId themeScopeId, bool removeToken /* = false */)
{
    if (removeToken) {
        CacheRemove(themeScopeMap_[themeScopeId]);
    }
    themeScopeMap_.erase(themeScopeId);
}

const RefPtr<TokenTheme>& TokenThemeStorage::GetTheme(TokenThemeScopeId themeScopeId)
{
    if (themeScopeId == 0) {
        return GetDefaultTheme();
    }
    auto themeId = themeScopeMap_[themeScopeId];
    return CacheGet(themeId);
}

void TokenThemeStorage::SetDefaultTheme(const RefPtr<NG::TokenTheme>& theme, ColorMode colorMode)
{
    (colorMode == ColorMode::DARK ? defaultDarkTheme_ : defaultLightTheme_) = theme;
}

const RefPtr<TokenTheme>& TokenThemeStorage::GetDefaultTheme()
{
    auto colorMode = SystemProperties::GetColorMode();
    return colorMode == ColorMode::DARK ? defaultDarkTheme_ : defaultLightTheme_;
}

void TokenThemeStorage::CacheClear()
{
    themeCache_.clear();
}

void TokenThemeStorage::CacheSet(const RefPtr<TokenTheme>& theme)
{
    CHECK_NULL_VOID(theme);
    themeCache_[theme->GetId()] = theme;
}

const RefPtr<TokenTheme>& TokenThemeStorage::CacheGet(int32_t themeId)
{
    return themeCache_[themeId];
}

void TokenThemeStorage::CacheRemove(int32_t themeId)
{
    themeCache_.erase(themeId);
}

RefPtr<TokenTheme> TokenThemeStorage::ObtainSystemTheme()
{
    RefPtr<TokenTheme> theme = CacheGet(TokenThemeStorage::SYSTEM_THEME_ID);
    if (!theme) {
        theme = CreateSystemTokenTheme();
        CacheSet(theme);
    }
    return theme;
}

RefPtr<TokenTheme> TokenThemeStorage::CreateSystemTokenTheme()
{
    auto tokenColors = AceType::MakeRefPtr<TokenColors>();
    auto tokenTheme = AceType::MakeRefPtr<NG::TokenTheme>(TokenThemeStorage::SYSTEM_THEME_ID);
    tokenTheme->SetColors(tokenColors);

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, tokenTheme);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, tokenTheme);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, tokenTheme);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, tokenTheme);

    std::vector<Color> colors;
    colors.reserve(TokenColors::TOTAL_NUMBER);
    for (size_t resId = 0; resId < TokenColors::TOTAL_NUMBER; ++resId) {
        colors.push_back(themeConstants->GetColor(TokenColors::GetSystemColorResIdByIndex(resId)));
    }
    tokenColors->SetColors(std::move(colors));
    return tokenTheme;
}
} // namespace OHOS::Ace::NG