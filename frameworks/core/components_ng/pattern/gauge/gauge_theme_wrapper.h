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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "base/utils/device_config.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

/**
 * GaugeThemeWrapper defines colors and styles for Gauge Component
 * basing on TokenTheme's data.
 * GaugeThemeWrapper should be built using GaugeThemeWrapper::WrapperBuilder.
 */
class GaugeThemeWrapper : public GaugeTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(GaugeThemeWrapper, GaugeTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() override = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::Claim(new GaugeThemeWrapper());
            ParsePattern(themeConstants, AceType::DynamicCast<GaugeTheme>(wrapper));
            return wrapper;
        }
    };

    ~GaugeThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (auto colors = theme.Colors(); colors) {
            indicatorColor_ = colors->IconPrimary();
            indicatorBorderColor_ = colors->CompBackgroundPrimaryContrary();
        }
    }

protected:
    GaugeThemeWrapper() = default;
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_THEME_WRAPPER_H