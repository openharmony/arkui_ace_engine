/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STACK_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STACK_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace::NG {
class StackTheme : public virtual Theme {
    DECLARE_ACE_TYPE(StackTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<StackTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<StackTheme> theme = AceType::Claim(new StackTheme());
            if (!themeConstants) {
                return theme;
            }
            RefPtr<ThemeStyle> stackPattern = themeConstants->GetPatternByName(THEME_PATTERN_STACK);
            if (!stackPattern) {
                LOGW("find pattern of linear layout fail");
                return theme;
            }
            theme->focusBorderColor_ = stackPattern->GetAttr<Color>("stack_focus_border_color", Color(0xFF007DFF));
            theme->focusBorderWidth_ = stackPattern->GetAttr<Dimension>("stack_focus_border_width", 2.0_vp);
            theme->focusBoxGlow_ = static_cast<bool>(stackPattern->GetAttr<double>("stack_focus_effect_type", 0.0));
            return theme;
        }
    };

    bool IsFocusBoxGlow() const
    {
        return focusBoxGlow_;
    }

    const Dimension& GetFocusBorderWidth() const
    {
        return focusBorderWidth_;
    }

    const Color& GetFocusBorderColor() const
    {
        return focusBorderColor_;
    }

protected:
    StackTheme() = default;

private:
    bool focusBoxGlow_ = false;
    Dimension focusBorderWidth_;
    Color focusBorderColor_;
};
} // namespace OHOS::Ace::NG

#endif