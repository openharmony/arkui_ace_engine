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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_CALENDAR_THEME_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_CALENDAR_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace {

class CalendarThemeWrapper : public CalendarTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(CalendarThemeWrapper, CalendarTheme);

public:
    class WrapperBuilder : public CalendarTheme::Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto theme = AceType::MakeRefPtr<CalendarThemeWrapper>();
            InitTheme(theme, themeConstants);
            return theme;
        }
    };

    ~CalendarThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            entryFontColor_ = colors->FontPrimary();
        }
    }

protected:
    CalendarThemeWrapper() = default;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CALENDAR_CALENDAR_THEME_WRAPPER_H
