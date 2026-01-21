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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_CORNER_MARK_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_CORNER_MARK_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace::NG {

class CornerMarkTheme : public virtual Theme {
    DECLARE_ACE_TYPE(CornerMarkTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<CornerMarkTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<CornerMarkTheme> theme = AceType::Claim(new CornerMarkTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<CornerMarkTheme>& theme) const
        {
            if (!themeConstants) {
                return;
            }
            RefPtr<ThemeStyle> cornerMarkPattern = themeConstants->GetPatternByName(THEME_PATTERN_CORNER_MARK);
            if (!cornerMarkPattern) {
                LOGW("find pattern of corner mark fail");
                return;
            }
            theme->cornerRadius_ = cornerMarkPattern->GetAttr<Dimension>("corner_radius_mark", 4.0_vp);
            theme->fontSize_ = cornerMarkPattern->GetAttr<Dimension>("text_size_body", 14.0_fp);
        }
    };

    ~CornerMarkTheme() override = default;

    const Dimension& GetCornerRadius() const
    {
        return cornerRadius_;
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_;
    }

    const Dimension& GetWidth() const
    {
        return width_;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    const Color& GetFontColor() const
    {
        return fontColor_;
    }

    const Color& GetWhiteThemeBackgroundColor() const
    {
        return whiteThemeBackgroundColor_;
    }

    const Color& GetDarkThemeBackgroundColor() const
    {
        return darkThemeBackgroundColor_;
    }

protected:
    CornerMarkTheme() = default;

private:
    Dimension cornerRadius_;
    Dimension fontSize_;
    Dimension width_ = 24.0_vp;
    Dimension height_ = 24.0_vp;
    Color fontColor_ = Color::WHITE;
    Color whiteThemeBackgroundColor_ = Color::BLACK;
    Color darkThemeBackgroundColor_ = Color(0xff303030);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_CORNER_MARK_THEME_H