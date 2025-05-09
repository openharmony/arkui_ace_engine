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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_CLOCK_TEXT_CLOCK_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_CLOCK_TEXT_CLOCK_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/text_clock/text_clock_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

class TextClockThemeWrapper : public TextClockTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(TextClockThemeWrapper, TextClockTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() override = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<TextClockThemeWrapper>();
            auto theme = AceType::DynamicCast<TextClockTheme>(wrapper);
            if (!themeConstants) {
                return wrapper;
            }
            InitThemeDefaultsClock(theme);
            ParsePattern(themeConstants, theme);
            return wrapper;
        }
    };

    ~TextClockThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (const auto& colors = theme.Colors(); colors) {
            textStyleClock_.SetTextColor(colors->FontSecondary());
        }
    }

protected:
    TextClockThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_CLOCK_TEXT_CLOCK_THEME_WRAPPER_H
