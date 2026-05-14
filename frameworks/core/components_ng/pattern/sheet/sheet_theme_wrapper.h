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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_SHEET_THEME_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_SHEET_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/overlay/sheet_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {
class SheetThemeWrapper : public SheetTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(SheetThemeWrapper, SheetTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<SheetThemeWrapper>();
            auto theme = AceType::DynamicCast<SheetTheme>(wrapper);
            if (!themeConstants) {
                return wrapper;
            }
            ParsePattern(themeConstants, theme);
            return wrapper;
        }
    };

    ~SheetThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            titleTextFontColor_ = colors->FontPrimary();
            subtitleTextFontColor_ = colors->FontSecondary();
            sheetBackgoundColor_ = colors->CompBackgroundGray();
            dragBarColor_ = colors->IconFourth();
            closeIconColor_ = colors->CompBackgroundTertiary();
            closeIconImageColor_ = colors->IconPrimary();
            closeIconSymbolColor_ = colors->IconPrimary();
        }
    }

protected:
    SheetThemeWrapper() = default;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHEET_SHEET_THEME_WRAPPER_H
