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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_ARC_LIST_ARC_LIST_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_ARC_LIST_ARC_LIST_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * ArcListTheme defines styles of arc list. ArcListTheme should be built
 * using ArcListTheme::Builder.
 */
class ArcListTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ArcListTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ArcListTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ArcListTheme> theme = AceType::MakeRefPtr<ArcListTheme>();
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ArcListTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_ARC_LIST);
            if (!pattern) {
                LOGW("find pattern of arc list failed");
                return;
            }
            std::string fadingEdge = pattern->GetAttr<std::string>("list_fadeout_enable", "");
            theme->velocity_scale_ = pattern->GetAttr<double>("arclist_velocity_scale", 0.6f);
            theme->fadingEdge_ = (fadingEdge == "true");
        }
    };

    ~ArcListTheme() override = default;

    bool GetFadingEdge() const
    {
        return fadingEdge_;
    }

    float GetVelocityScale() const
    {
        return velocity_scale_;
    }

protected:
    ArcListTheme() = default;

private:
    bool fadingEdge_ = false;
    float velocity_scale_ = 0.6f;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_ARC_LIST_ARC_LIST_THEME_H
