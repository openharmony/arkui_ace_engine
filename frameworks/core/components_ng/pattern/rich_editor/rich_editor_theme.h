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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_RICH_EDITOR_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_RICH_EDITOR_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace::NG {
/**
 * TextTheme defines color and styles of ThemeComponent. RichEditorTheme should be built
 * using RichEditorTheme::Builder.
 */
class RichEditorTheme : public virtual Theme {
    DECLARE_ACE_TYPE(RichEditorTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<RichEditorTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<RichEditorTheme> theme = AceType::Claim(new RichEditorTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<RichEditorTheme>& theme) const
        {
            if (!themeStyle || !theme) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_RICH_EDITOR, nullptr);
            if (!pattern) {
                LOGW("find pattern of text fail");
                return;
            }
            auto draggable = pattern->GetAttr<std::string>("draggable", "0");
            theme->draggable_ = StringUtils::StringToInt(draggable);
            theme->defaultCaretHeight_ = pattern->GetAttr<Dimension>("default_caret_height", 18.5_vp);
            theme->disabledAlpha_ = static_cast<float>(pattern->GetAttr<double>("text_color_disabled_alpha", 0.0));
        }
    };

    ~RichEditorTheme() override = default;

    bool GetDraggable() const
    {
        return draggable_;
    }

    const Dimension& GetDefaultCaretHeight() const
    {
        return defaultCaretHeight_;
    }

    float GetDisabledAlpha() const
    {
        return disabledAlpha_;
    }

protected:
    RichEditorTheme() = default;

private:
    float disabledAlpha_ = 0.0f;
    bool draggable_ = false;
    Dimension defaultCaretHeight_ = 18.5_vp;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_RICH_EDITOR_THEME_H
