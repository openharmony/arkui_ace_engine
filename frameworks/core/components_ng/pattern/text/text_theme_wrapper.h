/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

/**
 * TextThemeWrapper defines color and styles of TextComponent basing on TokenTheme's data.
 * TextThemeWrapper should be built using TextThemeWrapper::Builder.
 */
class TextThemeWrapper : public TextTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(TextThemeWrapper, TextTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::Claim(new TextThemeWrapper());
            auto theme = AceType::DynamicCast<TextTheme>(wrapper);
            if (!themeConstants) {
                return wrapper;
            }
            InitThemeDefaults(theme);
            ParsePattern(themeConstants, theme);
            return wrapper;
        }
    };

    ~TextThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (const auto& colors = theme.Colors(); colors) {
            textStyle_.SetTextColor(colors->FontPrimary());
        }
    }

protected:
    TextThemeWrapper() = default;
};

} // namespace
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_THEME_WRAPPER_H