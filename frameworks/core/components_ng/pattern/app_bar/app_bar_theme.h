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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_APP_BAR_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_APP_BAR_THEME_H

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_attributes.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_style.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class AppBarTheme : public virtual Theme {
    DECLARE_ACE_TYPE(AppBarTheme, Theme);

public:
    ~AppBarTheme() = default;

    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;
        RefPtr<AppBarTheme> Build(const RefPtr<ThemeConstants>& themeConstants)
        {
            RefPtr<AppBarTheme> theme = AceType::Claim(new AppBarTheme());
            if (!themeConstants) {
                LOGE("Build AppBarTheme error, themeConstants is null!");
                return theme;
            }
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }
    };

    const Dimension& GetAppBarHeight() const
    {
        return appBarHeight_;
    }

    const Dimension& GetIconSize() const
    {
        return iconSize_;
    }

    const Dimension& GetIconCornerRadius() const
    {
        return iconCornerRadius_;
    }

    const Dimension& GetFontSize() const
    {
        return appBarFontSize_;
    }

    const Dimension& GetMenuBarMarginLeft() const
    {
        return menuBarMarginLeft_;
    }

    const Dimension& GetMenuBarMarginRight() const
    {
        return menuBarMarginRight_;
    }

    const Dimension& GetMenuBarMarginTop() const
    {
        return menuBarMarginTop_;
    }

    const Dimension& GetMenuBarWidth() const
    {
        return menuBarWidth_;
    }

    const Dimension& GetMenuBarHeight() const
    {
        return menuBarHeight_;
    }

    const Dimension& GetShareMarginLeft() const
    {
        return shareMarginLeft_;
    }

    const Dimension& GetShareMarginRight() const
    {
        return shareMarginRight_;
    }

    const Dimension& GetCloseMarginLeft() const
    {
        return closeMarginLeft_;
    }

    const Dimension& GetCloseMarginRight() const
    {
        return closeMarginRight_;
    }

    const Dimension& GetIconMarginVertical() const
    {
        return iconMarginVertical_;
    }

    const Dimension& GetDividerWidth() const
    {
        return dividerWidth_;
    }

    const Dimension& GetDividerHeight() const
    {
        return dividerHeight_;
    }

    const Dimension& GetIconNewSize() const
    {
        return iconNewSize_;
    }

    const Color& GetTextColor() const
    {
        return textColorPrimary_;
    }

    const Color& GetClickEffectColor() const
    {
        return clickEffectColor_;
    }

    const Color& GetBgColor() const
    {
        return appBarBgColor_;
    }

    const std::string& GetBundleName() const
    {
        return bundleName_;
    }

    const std::string& GetAbilityName() const
    {
        return abilityName_;
    }

    const std::string& GetStageAbilityName() const
    {
        return stageAbilityName_;
    }

    std::optional<RectF> GetAppBarRect() const
    {
        auto pipeline = PipelineContext::GetCurrentContext();
        if (!pipeline || !pipeline->GetInstallationFree()) {
            return std::nullopt;
        }
        Dimension screenWidthByPx(SystemProperties::GetDeviceWidth(), DimensionUnit::PX);
        Dimension screenWidthByVp(screenWidthByPx.ConvertToVp(), DimensionUnit::VP);
        Dimension width = menuBarMarginLeft_ + menuBarWidth_ + menuBarMarginRight_;
        Dimension height = menuBarHeight_;
        Dimension left = screenWidthByVp - width;
        Dimension top = menuBarMarginTop_;
        RectF rect(left.Value(), top.Value(), width.Value(), height.Value());
        return rect;
    }
private:
    AppBarTheme() = default;
    static void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<AppBarTheme>& theme)
    {
        if (!themeStyle) {
            return;
        }
        auto appBarPattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_APP_BAR, nullptr);
        if (!appBarPattern) {
            LOGE("Pattern of app bar is null, please check!");
            return;
        }
        theme->appBarHeight_ = appBarPattern->GetAttr<Dimension>("app_bar_height", 0.0_vp);
        theme->iconSize_ = appBarPattern->GetAttr<Dimension>("icon_size", 0.0_vp);
        theme->iconCornerRadius_ = appBarPattern->GetAttr<Dimension>("icon_corner_radius", 0.0_vp);
        theme->appBarFontSize_ = appBarPattern->GetAttr<Dimension>("app_bar_font_size", 0.0_vp);
        theme->textColorPrimary_ = appBarPattern->GetAttr<Color>("text_color_primary", Color());
        theme->clickEffectColor_ = appBarPattern->GetAttr<Color>("click_effect_color", Color());
        theme->appBarBgColor_ = appBarPattern->GetAttr<Color>("app_bar_bg_color", Color());
        theme->bundleName_ = appBarPattern->GetAttr<std::string>("app_bar_bundle_name", "com.ohos.hag.famanager");
        theme->abilityName_ = appBarPattern->GetAttr<std::string>("app_bar_ability_name", "FaPanelAbility");
        theme->stageAbilityName_ = appBarPattern->GetAttr<std::string>("app_bar_stage_ability_name", "PanelAbility");
        theme->menuBarMarginLeft_ = appBarPattern->GetAttr<Dimension>("menu_bar_margin_left", 12.0_vp);
        theme->menuBarMarginRight_ = appBarPattern->GetAttr<Dimension>("menu_bar_margin_right", 8.0_vp);
        theme->menuBarMarginTop_ = appBarPattern->GetAttr<Dimension>("menu_bar_margin_top", 10.0_vp);
        theme->menuBarWidth_ = appBarPattern->GetAttr<Dimension>("menu_bar_width", 80.0_vp);
        theme->menuBarHeight_ = appBarPattern->GetAttr<Dimension>("menu_bar_height", 36.0_vp);
        theme->shareMarginLeft_ = appBarPattern->GetAttr<Dimension>("share_margin_left", 12.0_vp);
        theme->shareMarginRight_ = appBarPattern->GetAttr<Dimension>("share_margin_right", 8.0_vp);
        theme->closeMarginLeft_ = appBarPattern->GetAttr<Dimension>("close_margin_left", 8.0_vp);
        theme->closeMarginRight_ = appBarPattern->GetAttr<Dimension>("close_margin_right", 12.0_vp);
        theme->iconMarginVertical_ = appBarPattern->GetAttr<Dimension>("icon_margin_vertical", 8.0_vp);
        theme->dividerWidth_ = appBarPattern->GetAttr<Dimension>("divider_width", 1.0_px);
        theme->dividerHeight_ = appBarPattern->GetAttr<Dimension>("divider_height", 16.0_vp);
        theme->iconNewSize_ = appBarPattern->GetAttr<Dimension>("icon_new_size", 20.0_vp);
    }

    Dimension appBarHeight_;
    Dimension iconSize_;
    Dimension iconCornerRadius_;
    Dimension appBarFontSize_;
    Dimension menuBarMarginLeft_;
    Dimension menuBarMarginRight_;
    Dimension menuBarMarginTop_;
    Dimension menuBarWidth_;
    Dimension menuBarHeight_;
    Dimension shareMarginLeft_;
    Dimension shareMarginRight_;
    Dimension closeMarginLeft_;
    Dimension closeMarginRight_;
    Dimension iconMarginVertical_;
    Dimension dividerWidth_;
    Dimension dividerHeight_;
    Dimension iconNewSize_;
    Color textColorPrimary_;
    Color clickEffectColor_;
    Color appBarBgColor_;
    std::string bundleName_;
    std::string abilityName_;
    std::string stageAbilityName_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_APP_BAR_THEME_H