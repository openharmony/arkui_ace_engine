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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_THEME_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {
class MenuThemeWrapper : public MenuTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(MenuThemeWrapper, MenuTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<MenuThemeWrapper>();
            auto theme = AceType::DynamicCast<MenuTheme>(wrapper);
            if (!themeConstants) {
                return wrapper;
            }
            Parse(themeConstants, theme);
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return wrapper;
        }
    };

    ~MenuThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
    }

protected:
    MenuThemeWrapper() = default;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_THEME_WRAPPER_H