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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_OVERLAY_THEME_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_OVERLAY_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

/**
 * TextOverlayThemeWrapper defines colors and styles for select overlay nodes
 * basing on TokenTheme's data.
 * TextOverlayThemeWrapper should be built using TextOverlayThemeWrapper::WrapperBuilder.
 */
class TextOverlayThemeWrapper : public TextOverlayTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(TextOverlayThemeWrapper, TextOverlayTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<TextOverlayThemeWrapper>();
            auto theme = AceType::DynamicCast<TextOverlayTheme>(wrapper);
            if (!themeConstants) {
                LOGW("Build AppTheme error, themeConstants is null!");
                return wrapper;
            }
            ParseThemeConstants(themeConstants, theme);
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            ParseMenuPattern(themeConstants->GetThemeStyle(), theme);
            ParseAIMenu(themeConstants->GetThemeStyle(), theme);
            return wrapper;
        }
    };

    ~TextOverlayThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto themeColors = theme.Colors(); themeColors) {
            menuButtonTextStyle_.SetTextColor(themeColors->FontPrimary());
            symbolColor_ = themeColors->FontPrimary();
            buttonClickedColor_ = themeColors->InteractivePressed();
            buttonHoverColor_ = themeColors->InteractiveHover();
        }
    }

protected:
    TextOverlayThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_OVERLAY_THEME_WRAPPER_H