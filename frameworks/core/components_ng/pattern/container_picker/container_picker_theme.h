/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_THEME_H

#include <optional>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_attributes.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_style.h"

namespace OHOS::Ace::NG {

class ContainerPickerTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ContainerPickerTheme, Theme);

public:
    ~ContainerPickerTheme() = default;

    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;
        RefPtr<ContainerPickerTheme> Build(const RefPtr<ThemeConstants>& themeConstants)
        {
            RefPtr<ContainerPickerTheme> theme = AceType::MakeRefPtr<ContainerPickerTheme>();
            if (!themeConstants) {
                TAG_LOGE(AceLogTag::ACE_CONTAINER_PICKER, "Build ContainerPickerTheme error, themeConstants is null!");
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }
    };

    const Color& GetIndicatorBackgroundColor() const
    {
        return indicatorBackgroundColor_;
    }

    const Color& GetIndicatorDividerColor() const
    {
        return indicatorDividerColor_;
    }

    const Color& GetFontColor() const
    {
        return fontColor_;
    }

    const Color& GetFocusBorderColor() const
    {
        return focusBorderColor_;
    }

    const Dimension& GetIndicatorBackgroundRadius() const
    {
        return indicatorBackgroundRadius_;
    }

    const Dimension& GetStrokeWidth() const
    {
        return indicatorDividerStrokeWidth_;
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_;
    }

    const Dimension& GetFocusBorderWidth() const
    {
        return focusBorderWidth_;
    }

private:
    ContainerPickerTheme() = default;
    static void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ContainerPickerTheme>& theme)
    {
        RefPtr<ThemeStyle> containerPickerPattern = themeConstants->GetPatternByName(THEME_PATTERN_CONTAINER_PICKER);
        if (!containerPickerPattern) {
            TAG_LOGE(AceLogTag::ACE_CONTAINER_PICKER, "Pattern of container picker is null, please check!");
            return;
        }
        theme->indicatorBackgroundColor_ =
            containerPickerPattern->GetAttr<Color>("picker_view_background_color", Color(0x0c182431));
        theme->indicatorDividerColor_ =
            containerPickerPattern->GetAttr<Color>("picker_view_divider_color", Color(0x33182431));
        theme->fontColor_ = containerPickerPattern->GetAttr<Color>("picker_view_font_primary_color", Color(0xff182431));
        theme->focusBorderColor_ =
            containerPickerPattern->GetAttr<Color>("picker_view_focus_border_color", Color(0xff007dff));
        theme->indicatorBackgroundRadius_ =
            containerPickerPattern->GetAttr<Dimension>("picker_view_background_radius", 12.0_vp);
        theme->indicatorDividerStrokeWidth_ =
            containerPickerPattern->GetAttr<Dimension>("picker_view_divider_width", 2.0_px);
        theme->fontSize_ = containerPickerPattern->GetAttr<Dimension>("picker_view_font_size", 20.0_fp);
        theme->focusBorderWidth_ = containerPickerPattern->GetAttr<Dimension>("picker_view_focus_border_width", 2.0_vp);
    }

    Color indicatorBackgroundColor_;
    Color indicatorDividerColor_;
    Color fontColor_;
    Color focusBorderColor_;
    Dimension indicatorBackgroundRadius_;
    Dimension indicatorDividerStrokeWidth_;
    Dimension fontSize_;
    Dimension focusBorderWidth_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_THEME_H
