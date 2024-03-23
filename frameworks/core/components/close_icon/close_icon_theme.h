/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CLOSE_ICON_CLOSE_ICON_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CLOSE_ICON_CLOSE_ICON_THEME_H

#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
namespace {
constexpr Dimension PANEL_CLOSE_ICON_WIDTH = 24.0_vp;
constexpr Dimension PANEL_CLOSE_ICON_Height = 24.0_vp;
constexpr Dimension PANEL_CLOSE_ICON_MARGIN_TOP = 20.0_vp;
constexpr Dimension PANEL_CLOSE_ICON_MARGIN_RIGHT = 24.0_vp;
constexpr Dimension PANEL_CLOSE_ICON_RADIUS = 12.0_vp;
} // namespace
class CloseIconTheme : public virtual Theme {
    DECLARE_ACE_TYPE(CloseIconTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<CloseIconTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<CloseIconTheme> theme = AceType::Claim(new CloseIconTheme());
            if (!themeConstants) {
                return theme;
            }
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_CLOSE_ICON);
            if (pattern) {
                theme->closeIconWidth_ = pattern->GetAttr<Dimension>(CLOSE_ICON_WIDTH, PANEL_CLOSE_ICON_WIDTH);
                theme->closeIconHeight_ = pattern->GetAttr<Dimension>(CLOSE_ICON_Height, PANEL_CLOSE_ICON_Height);
                theme->closeIconMarginTop_ =
                    pattern->GetAttr<Dimension>(CLOSE_ICON_MARGIN_TOP, PANEL_CLOSE_ICON_MARGIN_TOP);
                theme->closeIconMarginRight_ =
                    pattern->GetAttr<Dimension>(CLOSE_ICON_MARGIN_RIGHT, PANEL_CLOSE_ICON_MARGIN_RIGHT);
                theme->closeIconRadius_ = pattern->GetAttr<Dimension>(CLOSE_ICON_RADIUS, PANEL_CLOSE_ICON_RADIUS);
            } else {
                LOGW("find pattern of closeIcon fail");
            }
            return theme;
        }
    };
    ~CloseIconTheme() override = default;

    const Dimension& GetCloseIconWidth() const
    {
        return closeIconWidth_;
    }

    const Dimension& GetCloseIconHeight() const
    {
        return closeIconHeight_;
    }

    const Dimension& GetCloseIconMarginRight() const
    {
        return closeIconMarginRight_;
    }

    const Dimension& GetCloseIconMarginTop() const
    {
        return closeIconMarginTop_;
    }

    const Dimension& GetCloseIconRadius() const
    {
        return closeIconRadius_;
    }

protected:
    CloseIconTheme() = default;

private:
    Dimension closeIconMarginRight_;
    Dimension closeIconMarginTop_;
    Dimension closeIconWidth_;
    Dimension closeIconHeight_;
    Dimension closeIconRadius_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CLOSE_ICON_CLOSE_ICON_THEME_H
