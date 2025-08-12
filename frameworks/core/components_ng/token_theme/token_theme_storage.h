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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_TOKEN_THEME_TOKEN_THEME_STORAGE_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_TOKEN_THEME_TOKEN_THEME_STORAGE_H

#include <map>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "base/memory/referenced.h"
#include "core/components_ng/token_theme/token_theme.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TokenThemeStorage final {
public:
    ACE_FORCE_EXPORT static TokenThemeStorage* GetInstance();
    ~TokenThemeStorage() = default;

    // theme map (key: themeScopeId - value: ark theme instance)
    void StoreThemeScope(TokenThemeScopeId themeScopeId, int32_t themeId);
    void RemoveThemeScope(TokenThemeScopeId themeScopeId, bool removeToken = false);
    const RefPtr<TokenTheme>& GetTheme(TokenThemeScopeId themeScopeId);

    // default theme
    void SetDefaultTheme(const RefPtr<TokenTheme>& theme, ColorMode colorMode);
    const RefPtr<TokenTheme>& GetDefaultTheme();
    void UpdateDefaultThemeBySystemTheme(ColorMode colorMode);

    // cache (key: theme id - value: ark theme instance)
    void CacheClear();
    void CacheResetColor();
    void CacheSet(const RefPtr<TokenTheme>& theme);
    const RefPtr<TokenTheme>& CacheGet(int32_t themeId);
    void CacheRemove(int32_t themeId);

    RefPtr<TokenTheme> ObtainSystemTheme();
    
    void SetIsThemeColorAvailable(bool isDark, int32_t index, bool isColorAvailable);

    void SetIsThemeColorSetByUser(int32_t themeId, bool isDark, int32_t index, bool isColorSetByUser);

private:
    static constexpr int32_t SYSTEM_THEME_LIGHT_ID = -1;
    static constexpr int32_t SYSTEM_THEME_DARK_ID = -2;
    bool systemTokenThemeCreated_[3] = {false, false, false}; // 3 means color modes: light, dark, undefined

    TokenThemeStorage();
    RefPtr<TokenTheme> CreateSystemTokenTheme(ColorMode colorMode);
    ColorMode CheckLocalAndSystemColorMode();
    void ResetThemeColor(int32_t themeId, RefPtr<TokenTheme>& theme, RefPtr<TokenTheme>& defaultTheme,
        ColorMode& colorMode);

    // key: scope id, value: theme id
    std::unordered_map<TokenThemeScopeId, int32_t> themeScopeMap_;

    // key: theme id, value: theme instance
    std::map<int32_t, RefPtr<TokenTheme>> themeCache_;
    std::mutex themeCacheMutex_;

    std::vector<bool> darkThemeColorsAvailable_ = std::vector<bool> (TokenColors::TOTAL_NUMBER, false);
    std::vector<bool> lightThemeColorsAvailable_ = std::vector<bool> (TokenColors::TOTAL_NUMBER, false);

    std::unordered_map<int32_t, std::map<bool, std::vector<bool>>> themeColorSetByUser_;

    inline static RefPtr<TokenTheme> defaultLightTheme_ = nullptr;
    inline static RefPtr<TokenTheme> defaultDarkTheme_ = nullptr;
};

} // namespace
#endif
