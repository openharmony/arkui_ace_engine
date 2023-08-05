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
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<HyperlinkTheme>& theme) const
        {
            if (!themeStyle) {
                LOGI("hyperlink theme style is null");
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_HYPERLINK, nullptr);
            if (!pattern) {
                LOGW("find pattern of hyperlink fail");
                return;
            }
            auto draggable = pattern->GetAttr<std::string>("draggable", "0");
            theme->draggable_ = StringUtils::StringToInt(draggable);
        }
    };

    ~HyperlinkTheme() override = default;

    bool GetDraggable() const
    {
        return draggable_;
    }

protected:
    HyperlinkTheme() = default;

private:
    bool draggable_ = false;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_HYPERLINK_HYPERLINK_THEME_H
