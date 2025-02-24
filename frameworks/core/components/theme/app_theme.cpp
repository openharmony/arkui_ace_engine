/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/theme/app_theme.h"

#include "core/common/resource/resource_manager.h"
namespace OHOS::Ace {
namespace {
constexpr uint64_t FOCUS_COLOR = 125831021;
}

RefPtr<AppTheme> AppTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<AppTheme> theme = AceType::Claim(new AppTheme());
    if (!themeConstants) {
        return theme;
    }
    auto themeStyle = themeConstants->GetThemeStyle();
    if (!themeStyle) {
        return theme;
    }

    theme->backgroundColor_ = themeStyle->GetAttr<Color>(THEME_ATTR_BG_COLOR, Color::WHITE);

    auto color = themeStyle->GetAttr<Color>("focus_color", Color());
    if (color != Color(0xff000000)) {
        theme->focusColor_ = color;
    } else {
        if (SystemProperties::GetResourceDecoupling()) {
            auto resAdapter = ResourceManager::GetInstance().GetResourceAdapter();
            theme->focusColor_ = resAdapter->GetColor(FOCUS_COLOR);
        }
    }

    auto hoverColor = themeStyle->GetAttr<Color>(THEME_ATTR_HOVER_COLOR, Color::FromRGBO(0, 0, 0, 0.05));
    if (hoverColor != Color(0xff000000)) {
        theme->hoverHighlightEnd_ = hoverColor;
    }
    RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_APP);
    if (!pattern) {
        LOGW("find pattern of app_theme fail");
        return theme;
    }
    theme->focusWidthVp_ = pattern->GetAttr<Dimension>("app_theme_focus_width", 2.0_vp);
    theme->focusOutPaddingVp_ = pattern->GetAttr<Dimension>("app_theme_focus_padding", 2.0_vp);
    theme->focusBoxGlow_ = static_cast<bool>(pattern->GetAttr<double>("app_theme_focus_box_glow", 0.0));
    theme->focusActiveByTab_ =
        static_cast<bool>(pattern->GetAttr<double>("app_theme_focus_navigation_active_by_tab_key", 1.0));
    theme->focusHandleClick_ =
        static_cast<bool>(pattern->GetAttr<double>("app_theme_focus_navigation_always_handle_click", 1.0));
    theme->pageTransitionAmplitudeRatio_ =
        themeStyle->GetAttr<double>("page_transition_amplitude_ratio", DEFAULT_AMPLITUDE_RATIO);
    return theme;
}
} // namespace OHOS::Ace
