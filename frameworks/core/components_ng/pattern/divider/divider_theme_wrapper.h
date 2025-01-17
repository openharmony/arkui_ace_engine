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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_THEME_WRAPPER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_THEME_WRAPPER_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/components/divider/divider_theme.h"
#include "core/components_ng/token_theme/token_theme_wrapper.h"

namespace OHOS::Ace::NG {

/**
 * DividerThemeWrapper defines colors and styles for Indicator and DisplayArrows parts of Divider Component
 * basing on TokenTheme's data.
 * DividerThemeWrapper should be built using DividerThemeWrapper::WrapperBuilder.
 */
class DividerThemeWrapper : public DividerTheme, public TokenThemeWrapper {
    DECLARE_ACE_TYPE(DividerThemeWrapper, DividerTheme);

public:
    class WrapperBuilder : public Builder {
    public:
        WrapperBuilder() = default;
        ~WrapperBuilder() = default;

        RefPtr<TokenThemeWrapper> BuildWrapper(const RefPtr<ThemeConstants>& themeConstants) const
        {
            auto wrapper = AceType::Claim(new DividerThemeWrapper());
            if (!themeConstants) {
                return wrapper;
            }

            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_DIVIDER);
            if (pattern) {
                wrapper->color_ = pattern->GetAttr<Color>("divider_color", Color::BLACK);
                wrapper->stokeWidth_ = pattern->GetAttr<Dimension>("divider_stroke_width", 1.0_vp);
            } else {
                LOGW("find pattern of divider fail");
            }
            return wrapper;
        }
    };

    ~DividerThemeWrapper() override = default;

    void ApplyTokenTheme(const TokenTheme& theme) override
    {
        if (const auto& colors = theme.Colors(); colors) {
            color_ = colors->CompDivider();
            return;
        }
    }

protected:
    DividerThemeWrapper() = default;
};

} // namespace
#endif
