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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_THEME_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_THEME_WRAPPER_H

#include <memory>

#include "core/components/common/properties/color.h"
#include "core/components/list/list_item_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

/**
 * ListItemThemeWrapper defines color and styles of ListItem basing on TokenTheme's data.
 * ListItemThemeWrapper should be built using ListItemThemeWrapper::WrapperBuilder.
 */
class ListItemThemeWrapper : public ListItemTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(ListItemThemeWrapper, ListItemTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<ListItemThemeWrapper>();
            auto theme = AceType::DynamicCast<ListItemTheme>(wrapper);
            if (!themeConstants) {
                return wrapper;
            }
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return wrapper;
        }
    };

    ~ListItemThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (const auto& colors = theme.Colors(); colors) {
            defaultColor_ = colors->CompBackgroundPrimary();
            itemDefaultColor_ = colors->CompBackgroundPrimary();
            focusBorderColor_ = colors->InteractiveFocus();
            hoverColor_ = colors->InteractiveHover();
            pressColor_ = colors->InteractiveClick();
            selectedColor_ = colors->CompBackgroundEmphasize();
            selectedColorWithAlpha_ = selectedColor_.BlendOpacity(selectedAlpha_);
        }
    }

protected:
    ListItemThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_THEME_WRAPPER_H
