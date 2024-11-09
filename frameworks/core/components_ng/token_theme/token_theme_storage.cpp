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
#include "base/utils/system_properties.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

TokenThemeStorage* TokenThemeStorage::GetInstance()
{
    static TokenThemeStorage instance;
    return &instance;
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
    return CheckLocalAndSystemColorMode() == ColorMode::DARK ? defaultDarkTheme_ : defaultLightTheme_;
}

ColorMode TokenThemeStorage::CheckLocalAndSystemColorMode()
{
    auto sysColorMode = SystemProperties::GetColorMode();
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, sysColorMode);
    auto colorMode = pipelineContext->GetLocalColorMode();
    if (colorMode == ColorMode::COLOR_MODE_UNDEFINED) {
        colorMode = sysColorMode;
    }
    return colorMode;
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
    RefPtr<TokenTheme> theme = nullptr;
    auto colorMode = CheckLocalAndSystemColorMode();
    if (colorMode == ColorMode::DARK) {
        theme = CacheGet(TokenThemeStorage::SYSTEM_THEME_DARK_ID);
    } else {
        theme = CacheGet(TokenThemeStorage::SYSTEM_THEME_LIGHT_ID);
    }
    if (!theme) {
        theme = CreateSystemTokenTheme(colorMode);
        CacheSet(theme);
    }
    return theme;
}

RefPtr<TokenTheme> TokenThemeStorage::CreateSystemTokenTheme(ColorMode colorMode)
{
    auto themeId = colorMode == ColorMode::DARK ?
        TokenThemeStorage::SYSTEM_THEME_DARK_ID : TokenThemeStorage::SYSTEM_THEME_LIGHT_ID;
    auto tokenColors = AceType::MakeRefPtr<TokenColors>();
    auto tokenTheme = AceType::MakeRefPtr<NG::TokenTheme>(themeId);
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