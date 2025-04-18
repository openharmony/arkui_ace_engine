/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_THEME_MANAGER_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_THEME_MANAGER_IMPL_H

#include "core/components/theme/resource_adapter.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace {
class ACE_EXPORT ThemeManagerImpl : public ThemeManager {
    DECLARE_ACE_TYPE(ThemeManagerImpl, ThemeManager);

public:
    ThemeManagerImpl();
    explicit ThemeManagerImpl(RefPtr<ResourceAdapter>& resourceAdapter);
    ~ThemeManagerImpl() override = default;

    void InitResource(const ResourceInfo& resourceInfo) override
    {
        themeConstants_->InitResource(resourceInfo);
    }

    void UpdateConfig(const ResourceConfiguration& config) override
    {
        themeConstants_->UpdateConfig(config);
    }

    void SetSystemThemeId(int32_t themeId) override
    {
        currentThemeId_ = themeId;
    }

    void LoadSystemTheme(int32_t themeId) override
    {
        currentThemeId_ = themeId;
        themeConstants_->LoadTheme(themeId);
    }

    int32_t GetSystemTheme() override
    {
        return currentThemeId_;
    }

    void ParseSystemTheme() override
    {
        themeConstants_->ParseTheme();
    }

    void LoadCustomTheme(const RefPtr<AssetManager>& assetManager) override
    {
        themeConstants_->LoadCustomStyle(assetManager);
    }

    /*
     * Color scheme of the whole window, app bg color will be change in transparent scheme.
     */
    void SetColorScheme(ColorScheme colorScheme) override
    {
        themeConstants_->SetColorScheme(colorScheme);
    }

    /*
     * Get color value from AppTheme (if exists) or system theme style.
     * Prebuilt background color will be returned if AppTheme and system theme style both not exists.
     * @return App background color.
     */
    Color GetBackgroundColor() const override;

    RefPtr<ThemeConstants> GetThemeConstants(
        const std::string& bundleName, const std::string& moduleName) const override
    {
        themeConstants_->UpdateThemeConstants(bundleName, moduleName);
        return themeConstants_;
    }

    RefPtr<ThemeConstants> GetThemeConstants() const override
    {
        return GetThemeConstants("", "");
    }

    /*
     * Get target theme, this function will cause construction of the theme if it not exists.
     * @return Target component theme.
     */
    RefPtr<Theme> GetTheme(ThemeType type) override;

    template<typename T>
    RefPtr<T> GetTheme()
    {
        return AceType::DynamicCast<T>(GetTheme(T::TypeId()));
    }

    /*
     * Get the theme and update it according to the TokenTheme, that given in param.
     * @return Target component theme.
     */
    RefPtr<Theme> GetTheme(ThemeType type, int32_t themeScopeId) override;

    template<typename T>
    RefPtr<T> GetTheme(int32_t themeScopeId)
    {
        return AceType::DynamicCast<T>(GetTheme(T::TypeId()), themeScopeId);
    }

    void LoadResourceThemes() override;

    uint32_t GetResourceLimitKeys() const override
    {
        return themeConstants_->GetResourceLimitKeys();
    }

    void RegisterThemeKit(ThemeType type, Ace::Kit::BuildFunc func) override;

    RefPtr<Theme> GetThemeOrigin(ThemeType type);

    RefPtr<Theme> GetThemeKit(ThemeType type);

private:
    using ThemeWrappers = std::unordered_map<ThemeType, RefPtr<NG::TokenThemeWrapper>>;
    std::unordered_map<ThemeType, RefPtr<Theme>> themes_;
    ThemeWrappers themeWrappersLight_;
    ThemeWrappers themeWrappersDark_;

    RefPtr<ThemeConstants> themeConstants_;
    int32_t currentThemeId_ = -1;

    ACE_DISALLOW_COPY_AND_MOVE(ThemeManagerImpl);

    ThemeWrappers& GetThemeWrappers(ColorMode mode);
    ColorMode GetCurrentColorMode() const;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_THEME_MANAGER_H
