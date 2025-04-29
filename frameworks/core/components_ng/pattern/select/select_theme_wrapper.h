/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_THEME_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {
class SelectThemeWrapper : public SelectTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(SelectThemeWrapper, SelectTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::Claim(new SelectThemeWrapper());
            auto theme = AceType::DynamicCast<SelectTheme>(wrapper);
            if (!themeConstants) {
                return wrapper;
            }
            ParseNewPattern(themeConstants, theme);
            Parse(themeConstants, theme);
            return wrapper;
        }
    };

    ~SelectThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            SetFontColor(colors->FontPrimary());
            SetButtonBackgroundColor(colors->CompBackgroundTertiary());
        }
    }

protected:
    SelectThemeWrapper() = default;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_THEME_WRAPPER_H