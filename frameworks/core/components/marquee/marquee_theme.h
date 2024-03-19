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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MARQUEE_MARQUEE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MARQUEE_MARQUEE_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
namespace {
    constexpr Dimension MARQUEE_FONT_SIZE = 37.5_px;
}

/**
 * MarqueeTheme defines color and styles of MarqueeComponent. MarqueeTheme should be built
 * using MarqueeTheme::Builder.
 */
class MarqueeTheme : public virtual Theme {
    DECLARE_ACE_TYPE(MarqueeTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<MarqueeTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<MarqueeTheme> theme = AceType::Claim(new MarqueeTheme());
            if (!themeConstants) {
                return theme;
            }

            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_MARQUEE);
            if (pattern) {
                theme->textColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::BLACK);
                theme->fontSize_ = pattern->GetAttr<Dimension>("marquee_font_size", MARQUEE_FONT_SIZE);
            } else {
                LOGW("find pattern of marquee fail");
            }
            return theme;
        }
    };

    ~MarqueeTheme() override = default;

    const Color& GetTextColor() const
    {
        return textColor_;
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_;
    }

protected:
    MarqueeTheme() = default;

private:
    Color textColor_;
    Dimension fontSize_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MARQUEE_MARQUEE_THEME_H
