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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_HYPERLINK_HYPERLINK_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_HYPERLINK_HYPERLINK_THEME_H

#include "base/utils/string_utils.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components/theme/theme_manager.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace {
/**
 * HyperlinkTheme defines styles of Hyperlink. HyperlinkTheme should be built
 * using HyperlinkTheme::Builder.
 */
class HyperlinkTheme : public virtual Theme {
    DECLARE_ACE_TYPE(HyperlinkTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<HyperlinkTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<HyperlinkTheme> theme = AceType::Claim(new HyperlinkTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->textSelectedDecoration_ = TextDecoration::UNDERLINE;
            theme->textUnSelectedDecoration_ = TextDecoration::NONE;
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<HyperlinkTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_HYPERLINK);
            if (!pattern) {
                LOGW("find pattern of hyperlink fail");
                return;
            }
            theme->textColor_ = pattern->GetAttr<Color>("text_color", Color(0xff007dff));
            theme->textTouchedColor_ = pattern->GetAttr<Color>("text_touched_color", Color(0x19182431));
            theme->textLinkedColor_ = pattern->GetAttr<Color>("text_linked_color", Color(0x66182431));
            theme->opacity_ = pattern->GetAttr<double>("text_disabled_opacity", 0.0);
            theme->textDisabledColor_ = pattern->GetAttr<Color>("text_color", Color(0xff007dff))
                .BlendOpacity(theme->opacity_);
            theme->textFocusedColor_ = pattern->GetAttr<Color>("text_focused_color", Color(0xff007dff));
            auto draggable = pattern->GetAttr<std::string>("draggable", "0");
            theme->draggable_ = StringUtils::StringToInt(draggable);
        }
    };

    ~HyperlinkTheme() override = default;

    double GetOpacity() const
    {
        return opacity_;
    }

    bool GetDraggable() const
    {
        return draggable_;
    }

    const Color& GetTextColor() const
    {
        return textColor_;
    }

    const Color& GetTextTouchedColor() const
    {
        return textTouchedColor_;
    }

    const Color& GetTextLinkedColor() const
    {
        return textLinkedColor_;
    }

    const Color& GetTextDisabledColor() const
    {
        return textDisabledColor_;
    }

    const Color& GetTextFocusedColor() const
    {
        return textFocusedColor_;
    }

    TextDecoration GetTextSelectedDecoration() const
    {
        return textSelectedDecoration_;
    }

    TextDecoration GetTextUnSelectedDecoration() const
    {
        return textUnSelectedDecoration_;
    }
protected:
    HyperlinkTheme() = default;

private:
    bool draggable_ = false;
    double opacity_;
    Color textColor_;
    Color textTouchedColor_;
    Color textLinkedColor_;
    Color textDisabledColor_;
    Color textFocusedColor_;
    TextDecoration textSelectedDecoration_;
    TextDecoration textUnSelectedDecoration_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_HYPERLINK_HYPERLINK_THEME_H
