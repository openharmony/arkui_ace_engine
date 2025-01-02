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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_LIST_LIST_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_LIST_LIST_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * ListTheme defines styles of list. ListTheme should be built
 * using ListTheme::Builder.
 */
class ListTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ListTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ListTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ListTheme> theme = AceType::Claim(new ListTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ListTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_LIST);
            if (!pattern) {
                LOGW("find pattern of list fail");
                return;
            }
            theme->gradientWidth_ = pattern->GetAttr<Dimension>("gradient_width", 0.0_vp);
            theme->backgroundColor_ = pattern->GetAttr<Color>("background_color", Color(0x00FFFFFF));
            theme->scrollDistance_ = pattern->GetAttr<double>("scroll_distance", 50.0f);
            theme->dividerColor_ = pattern->GetAttr<Color>("divider_color", Color(0x08000000));
            theme->chainMinSpace_ = pattern->GetAttr<Dimension>("chain_min_space", 15.0_vp);
            theme->chainMaxSpace_ = pattern->GetAttr<Dimension>("chain_max_space", 40.0_vp);
            theme->chainConductivity_ = pattern->GetAttr<double>("chain_conductivity", 0.7f);
            theme->chainIntensity_ = pattern->GetAttr<double>("chain_intensity", 0.3f);
            theme->chainStiffness_ = pattern->GetAttr<double>("chain_stiffness", 228.0f);
            theme->chainDamping_ = pattern->GetAttr<double>("chain_damping", 30.0f);
            theme->fadingEdge_ = pattern->GetAttr<std::string>("list_fadeout_enable", "") == "true";
        }
    };

    ~ListTheme() override = default;

    const Dimension& GetGradientWidth() const
    {
        return gradientWidth_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetDividerColor() const
    {
        return dividerColor_;
    }

    double GetScrollDistance() const
    {
        return scrollDistance_;
    }

    Dimension GetChainMinSpace() const
    {
        return chainMinSpace_;
    }
    Dimension GetChainMaxSpace() const
    {
        return chainMaxSpace_;
    }
    double GetChainConductivity() const
    {
        return chainConductivity_;
    }
    double GetChainIntensity() const
    {
        return chainIntensity_;
    }
    double GetChainStiffness() const
    {
        return chainStiffness_;
    }
    double GetChainDamping() const
    {
        return chainDamping_;
    }
    bool GetFadingEdge() const
    {
        return fadingEdge_;
    }

protected:
    ListTheme() = default;

private:
    Dimension gradientWidth_;
    Color backgroundColor_;
    Color dividerColor_;
    double scrollDistance_ = 0.0;
    Dimension chainMinSpace_;
    Dimension chainMaxSpace_;
    double chainConductivity_ = 0.0;
    double chainIntensity_ = 0.0;
    double chainStiffness_ = 0.0;
    double chainDamping_ = 0.0;
    bool fadingEdge_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_LIST_LIST_THEME_H
