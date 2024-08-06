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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_BAR_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_BAR_THEME_H

#include "core/components/common/properties/scroll_bar.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * ScrollBarTheme defines styles of scrollBar. ScrollBarTheme should be built
 * using ScrollBarTheme::Builder.
 */
class ScrollBarTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ScrollBarTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ScrollBarTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ScrollBarTheme> theme = AceType::Claim(new ScrollBarTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ScrollBarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_SCROLL_BAR);
            if (!pattern) {
                LOGW("find pattern of scroll_bar fail");
                return;
            }
            auto blendOpacity = pattern->GetAttr<double>("scroll_bar_foreground_opacity", 0.4f);
            theme->shapeMode_ = static_cast<ShapeMode>(pattern->GetAttr<double>("scroll_bar_shape_mode", 0.0));
            theme->normalWidth_ = pattern->GetAttr<Dimension>("scroll_bar_normal_width", 0.0_vp);
            theme->activeWidth_ = pattern->GetAttr<Dimension>("scroll_bar_active_width", 0.0_vp);
            theme->minHeight_ = pattern->GetAttr<Dimension>("scroll_bar_min_height", 0.0_vp);
            theme->minDynamicHeight_ = pattern->GetAttr<Dimension>("scroll_bar_min_dynamic_height", 0.0_vp);
            theme->reservedHeight_ = pattern->GetAttr<Dimension>("scroll_bar_reserved_height", 0.0_vp);
            theme->touchWidth_ = pattern->GetAttr<Dimension>("scroll_bar_touch_width", 0.0_vp);
            theme->backgroundColor_ = pattern->GetAttr<Color>("scroll_bar_background_color", Color());
            theme->foregroundColor_ = pattern->GetAttr<Color>(PATTERN_FG_COLOR,
                Color::TRANSPARENT).BlendOpacity(blendOpacity);
            auto padding = pattern->GetAttr<Dimension>("scroll_bar_margin", Dimension(4.0, DimensionUnit::VP));
            theme->padding_ = Edge(padding.Value(), 0.0, padding.Value(), padding.Value(), padding.Unit());
            theme->scrollBarMargin_ = padding;
            theme->defaultWidth_ = pattern->GetAttr<Dimension>("scroll_bar_default_width", 16.0_vp);
            theme->defaultHeight_ = pattern->GetAttr<Dimension>("scroll_bar_default_height", 16.0_vp);
        }
    };

    ~ScrollBarTheme() override = default;

    const Dimension& GetNormalWidth() const
    {
        return normalWidth_;
    }

    const Dimension& GetActiveWidth() const
    {
        return activeWidth_;
    }

    const Dimension& GetMinHeight() const
    {
        return minHeight_;
    }

    const Dimension& GetMinDynamicHeight() const
    {
        return minDynamicHeight_;
    }

    const Dimension& GetReservedHeight() const
    {
        return reservedHeight_;
    }

    const Dimension& GetTouchWidth() const
    {
        return touchWidth_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetForegroundColor() const
    {
        return foregroundColor_;
    }

    ShapeMode GetShapeMode() const
    {
        return shapeMode_;
    }

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const Dimension& GetScrollBarMargin() const
    {
        return scrollBarMargin_;
    }

    const Dimension& GetDefaultWidth() const
    {
        return defaultWidth_;
    }

    const Dimension& GetDefaultHeight() const
    {
        return defaultHeight_;
    }

protected:
    ScrollBarTheme() = default;

private:
    ShapeMode shapeMode_ = ShapeMode::DEFAULT;
    Dimension normalWidth_;
    Dimension activeWidth_;
    Dimension minHeight_;
    Dimension minDynamicHeight_;
    Dimension reservedHeight_;
    Dimension touchWidth_;
    Dimension scrollBarMargin_;
    Dimension defaultWidth_;
    Dimension defaultHeight_;
    Color backgroundColor_;
    Color foregroundColor_;
    Edge padding_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_BAR_THEME_H
