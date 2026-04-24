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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_THEME_WRAPPER_H

#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

class SwiperThemeWrapper : public SwiperIndicatorTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(SwiperThemeWrapper, SwiperIndicatorTheme, TokenThemeWrapper);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto themeWrapper = AceType::MakeRefPtr<SwiperThemeWrapper>();
            auto theme = AceType::DynamicCast<SwiperIndicatorTheme>(themeWrapper);
            if (!themeConstants) {
                return themeWrapper;
            }
            ParsePattern(themeConstants, theme);
            return themeWrapper;
        }
    };

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            // not used.
            hotZoneColor_ = colors->InteractiveClick();
            indicatorTextFocusColor_ = colors->InteractiveFocus();

            hoverColor_ = colors->InteractiveHover();
            pressedColor_ = colors->InteractiveClick();
            focusedColor_ = colors->InteractiveFocus();
            digitalIndicatorTextStyle_.SetTextColor(colors->FontPrimary());
            hoverArrowBackgroundColor_ = colors->InteractiveHover();
            clickArrowBackgroundColor_ = colors->InteractiveClick();

            selectedColor_ = colors->CompBackgroundEmphasize();
            color_ = colors->CompBackgroundSecondary();
            smallArrowColor_ = colors->IconPrimary();
            bigArrowColor_ = colors->IconPrimary();
            bigArrowBackgroundColor_ = colors->CompBackgroundSecondary();
        }
    }

protected:
    SwiperThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_THEME_WRAPPER_H