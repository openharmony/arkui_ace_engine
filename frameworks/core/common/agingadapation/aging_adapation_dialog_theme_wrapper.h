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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AGINGADAPATIONDIALOGTHEMEWRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AGINGADAPATIONDIALOGTHEMEWRAPPER_H

#include "core/components/navigation_bar/navigation_bar_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

class AgingAdapationDialogThemeWrapper : public AgingAdapationDialogTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(AgingAdapationDialogThemeWrapper, AgingAdapationDialogTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto theme = AceType::MakeRefPtr<AgingAdapationDialogThemeWrapper>();
            InitTheme(theme, themeConstants);
            return theme;
        }
    };

    ~AgingAdapationDialogThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            SetDialogIconColor(colors->IconPrimary());
            SetDialogFontColor(colors->FontPrimary());
        }
    }

protected:
    AgingAdapationDialogThemeWrapper() = default;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AGINGADAPATIONDIALOGTHEMEWRAPPER_H
