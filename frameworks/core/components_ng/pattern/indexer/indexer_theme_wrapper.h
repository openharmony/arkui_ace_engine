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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_THEME_WRAPPER_H

#include "core/components/indexer/indexer_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

class IndexerThemeWrapper : public IndexerTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(IndexerThemeWrapper, IndexerTheme, TokenThemeWrapper);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto themeWrapper = AceType::MakeRefPtr<IndexerThemeWrapper>();
            auto theme = AceType::DynamicCast<IndexerTheme>(themeWrapper);
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
            popupSeparateColor_ = colors->CompDivider();

            defaultTextColor_ = colors->FontSecondary();
            selectedTextColor_ = colors->FontEmphasize();
            popupTextColor_ = colors->FontEmphasize();
            selectedBackgroundColor_ = colors->CompEmphasizeSecondary();
            popupSelectedTextColor_ = colors->FontPrimary();
            popupUnselectedTextColor_ = colors->FontPrimary();
            hoverBgAreaColor_ = colors->InteractiveHover();
            slipHoverBackgroundColor_ = colors->InteractiveHover();
            focusBgOutlineColor_ = colors->InteractiveFocus();
            pressedBgAreaColor_ = colors->InteractiveClick();
            slipPressedBackgroundColor_ = colors->InteractiveClick();
            popupClickedBgAreaColor_ = colors->CompBackgroundTertiary();
            popupTitleBackground_ = colors->CompBackgroundTertiary();
        }
    }

protected:
    IndexerThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_INDEXER_INDEXER_THEME_WRAPPER_H