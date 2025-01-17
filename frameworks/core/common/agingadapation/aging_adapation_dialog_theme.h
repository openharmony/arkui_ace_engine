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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AGINGADAPATIONDIALOGTHEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AGINGADAPATIONDIALOGTHEME_H

#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/layout_param.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/radius.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

namespace {
constexpr int32_t GRID_COUNT = 2;
constexpr int32_t MAX_LINES = 6;
}

class AgingAdapationDialogTheme : public virtual Theme {
    DECLARE_ACE_TYPE(AgingAdapationDialogTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<AgingAdapationDialogTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<AgingAdapationDialogTheme> theme = AceType::Claim(new AgingAdapationDialogTheme());
            if (!themeConstants) {
                return theme;
            }
            // init theme from global data
            auto themeStyle = themeConstants->GetThemeStyle();
            if (!themeStyle) {
                return theme;
            }
            RefPtr<ThemeStyle> dialogPattern = themeConstants->GetPatternByName(THEME_PATTERN_AGING_ADAPATION_DIALOG);
            if (!dialogPattern) {
                return theme;
            }
            theme->dialogIconColor_ = dialogPattern->GetAttr<Color>("aging_dialog_icon_primary", Color(0xff182431));
            theme->dialogFontColor_ = dialogPattern->GetAttr<Color>("aging_dialog_font_primary", Color(0xff182431));
            theme->bigFontSizeScale_ = dialogPattern->GetAttr<double>("big_font_size_scale", 0.0);
            theme->largeFontSizeScale_ = dialogPattern->GetAttr<double>("large_font_size_scale", 0.0);
            theme->maxFontSizeScale_ = dialogPattern->GetAttr<double>("max_font_size_scale", 0.0);
            theme->bigDialogWidth_ = dialogPattern->GetAttr<double>("big_dialog_width", 0.0);
            theme->maxDialogWidth_ = dialogPattern->GetAttr<double>("max_dialog_width", 0.0);
            theme->idealSize_ = dialogPattern->GetAttr<Dimension>("ideal_size", 0.0_vp);
            theme->dialogPropertyTop_ = dialogPattern->GetAttr<Dimension>("dialog_property_top", 0.0_vp);
            theme->dialogPropertyBottom_ = dialogPattern->GetAttr<Dimension>("dialog_property_bottom", 0.0_vp);
            theme->textPropertyLeft_ = dialogPattern->GetAttr<Dimension>("text_property_left", 0.0_vp);
            theme->textPropertyBottom_ = dialogPattern->GetAttr<Dimension>("text_property_bottom", 0.0_vp);
            theme->textPropertyRight_ = dialogPattern->GetAttr<Dimension>("text_property_right", 0.0_vp);
            theme->dialogFontSize_ = dialogPattern->GetAttr<Dimension>("dialog_font_size", 0.0_fp);
            theme->gridCount_ = GRID_COUNT;
            theme->maxLines_ = MAX_LINES;
            theme->dialogCornerRadius_ = dialogPattern->GetAttr<Dimension>("dialog_corner_radius_level10", 0.0_vp);
            return theme;
        }
    };

    ~AgingAdapationDialogTheme() override = default;

    const double& GetBigFontSizeScale() const
    {
        return bigFontSizeScale_;
    }

    const double& GetLargeFontSizeScale() const
    {
        return largeFontSizeScale_;
    }

    const double& GetMaxFontSizeScale() const
    {
        return maxFontSizeScale_;
    }

    const double& GetBigDialogWidth() const
    {
        return bigDialogWidth_;
    }

    const double& GetMaxDialogWidth() const
    {
        return maxDialogWidth_;
    }

    const Dimension& GetIdealSize() const
    {
        return idealSize_;
    }

    const Dimension& GetDialogPropertyTop() const
    {
        return dialogPropertyTop_;
    }

    const Dimension& GetDialogPropertyBottom() const
    {
        return dialogPropertyBottom_;
    }

    const Dimension& GetTextPropertyLeft() const
    {
        return textPropertyLeft_;
    }

    const Dimension& GetTextPropertyBottom() const
    {
        return textPropertyBottom_;
    }

    const Dimension& GetTextPropertyRight() const
    {
        return textPropertyRight_;
    }

    const Dimension& GetDialogFontSize() const
    {
        return dialogFontSize_;
    }
    
    const Color& GetDialogIconColor() const
    {
        return dialogIconColor_;
    }

    const Color& GetDialogFontColor() const
    {
        return dialogFontColor_;
    }

    const int32_t& GetGridCount() const
    {
        return gridCount_;
    }

    const int32_t& GetMaxLines() const
    {
        return maxLines_;
    }

    const Dimension& GetDialogCornerRadius() const
    {
        return dialogCornerRadius_;
    }

protected:
    AgingAdapationDialogTheme() = default;

private:
    double bigFontSizeScale_;
    double largeFontSizeScale_;
    double maxFontSizeScale_;
    double bigDialogWidth_;
    double maxDialogWidth_;
    Dimension idealSize_;
    Dimension dialogPropertyTop_;
    Dimension dialogPropertyBottom_;
    Dimension textPropertyLeft_;
    Dimension textPropertyBottom_;
    Dimension textPropertyRight_;
    Dimension dialogFontSize_;
    Dimension dialogCornerRadius_;
    Color dialogIconColor_;
    Color dialogFontColor_;
    int32_t gridCount_;
    int32_t maxLines_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DIALOG_DIALOG_THEME_H
