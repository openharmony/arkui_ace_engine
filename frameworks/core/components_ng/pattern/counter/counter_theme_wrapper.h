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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "base/utils/device_config.h"
#include "core/components/counter/counter_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

/**
 * CounterThemeWrapper defines colors and styles for Counter Component
 * basing on TokenTheme's data.
 * CounterThemeWrapper should be built using CounterThemeWrapper::WrapperBuilder.
 */
class CounterThemeWrapper : public CounterTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(CounterThemeWrapper, CounterTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() override = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::MakeRefPtr<CounterThemeWrapper>();
            ParsePattern(themeConstants, AceType::DynamicCast<CounterTheme>(wrapper));
            return wrapper;
        }
    };

    ~CounterThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            // update only required attributes by TokenTheme tokens
            contentTextStyle_.SetTextColor(colors->FontPrimary());
        }
    }

protected:
    CounterThemeWrapper() = default;
};

} // namespace
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COUNTER_COUNTER_THEME_WRAPPER_H
