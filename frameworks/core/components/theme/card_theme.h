/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_CARD_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_CARD_THEME_H

#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components/theme/theme_manager.h"

namespace OHOS::Ace {

class CardTheme : public virtual Theme {
    DECLARE_ACE_TYPE(CardTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<CardTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<CardTheme> theme = AceType::MakeRefPtr<CardTheme>();
            if (!themeConstants) {
                return theme;
            }
            theme = AceType::MakeRefPtr<CardTheme>();
            ParsePattern(themeConstants, theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<CardTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CARD);
            if (!pattern) {
                LOGW("find pattern of card fail");
                return;
            }
            theme->borderRadius_ = pattern->GetAttr<Dimension>("card_border_radius", 16.0_vp);
            theme->backgroundColor_ = pattern->GetAttr<Color>("card_bg_color", Color(0xff202224));
            theme->blurRadius_ = pattern->GetAttr<Dimension>("card_blur_radius", 10.0_px);
        }
    };

    ~CardTheme() override = default;

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Dimension& GetBorderRadius() const
    {
        return borderRadius_;
    }

    const Dimension& GetBlurRadius() const
    {
        return blurRadius_;
    }

protected:
    CardTheme() = default;

private:
    Dimension borderRadius_;
    Color backgroundColor_;
    Dimension blurRadius_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_CARD_THEME_H
