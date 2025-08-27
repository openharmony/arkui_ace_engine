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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_RICH_EDITOR_THEME_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_RICH_EDITOR_THEME_WRAPPER_H

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

class RichEditorThemeWrapper : public RichEditorTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(RichEditorThemeWrapper, RichEditorTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<RichEditorThemeWrapper>();
            auto theme = AceType::DynamicCast<RichEditorTheme>(wrapper);
            CHECK_NULL_RETURN(themeConstants, wrapper);
            InitThemeDefaults(themeConstants, theme);
            ParsePattern(themeConstants, theme);
            return wrapper;
        }
    };

    ~RichEditorThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        CHECK_NULL_VOID(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
        if (const auto& colors = theme.Colors(); colors) {
            textStyle_.SetTextColor(colors->FontPrimary());
            textStyle_.SetTextDecorationColor(colors->FontPrimary());
            urlDefaultColor_ = colors->FontEmphasize();
            urlDisabledColor_= urlDefaultColor_.BlendOpacity(urlDisabledOpacity_);
            urlHoverColor_ = colors->InteractiveHover();
            urlPressColor_ = colors->InteractivePressed();
        }
    }

protected:
    RichEditorThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_RICH_EDITOR_THEME_WRAPPER_H
