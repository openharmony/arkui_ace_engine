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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_CHECKBOX_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOX_CHECKBOX_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

/**
 * CheckboxThemeWrapper defines colors and styles for both Checkbox and CheckboxGroup component
 * basing on TokenTheme's data.
 * CheckboxThemeWrapper should be built using CheckboxThemeWrapper::WrapperBuilder.
 */
class CheckboxThemeWrapper : public CheckboxTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(CheckboxThemeWrapper, CheckboxTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::Claim(new CheckboxThemeWrapper());
            if (!themeConstants) {
                return wrapper;
            }
            ParsePattern(themeConstants, AceType::DynamicCast<CheckboxTheme>(wrapper));
            return wrapper;
        }
    };

    ~CheckboxThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            // CheckMarkColor in CheckBoxModel, MarkStyle.strokeColor in TS
            pointColor_ = colors->IconOnPrimary();
            // UnSelectedColor in CheckBoxModel
            inactiveColor_ = colors->IconFourth();
            // SelectedColor in CheckBoxModel
            activeColor_ = colors->CompBackgroundEmphasize();
        }
    }

protected:
    CheckboxThemeWrapper() = default;
};

} // namespace
#endif