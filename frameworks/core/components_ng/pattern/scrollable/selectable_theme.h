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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace::NG {

class SelectableTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SelectableTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<SelectableTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<SelectableTheme> theme = AceType::MakeRefPtr<SelectableTheme>();
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SelectableTheme>& theme) const
        {
            if (!theme) {
                return;
            }
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_SELECTABLE);
            if (!pattern) {
                return;
            }
            theme->editModeCheckBoxHotZoneWidth_ =
                pattern->GetAttr<Dimension>("edit_mode_check_box_hot_zone_width", 36.0_vp);
        }
    };

    ~SelectableTheme() override = default;

    Dimension GetEditModeCheckBoxHotZoneWidth() const
    {
        return editModeCheckBoxHotZoneWidth_;
    }

protected:
    SelectableTheme() = default;

    Dimension editModeCheckBoxHotZoneWidth_ = 36.0_vp;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_THEME_H
