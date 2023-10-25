/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_THEME_H

#include <cstdint>

#include "core/components/theme/theme.h"
#include "frameworks/base/geometry/dimension.h"

namespace OHOS::Ace::NG {
constexpr Dimension GRADIENT_HEIGHT = Dimension(50, DimensionUnit::VP);

constexpr uint8_t GRADIENT_END_GRADIENT = 255;
constexpr uint32_t DEFAULT_BACKGROUND_COLOR = 0xFFFFFFF;
constexpr uint32_t MENU_MIN_GRID_COUNTS = 2;
constexpr uint32_t MENU_MAX_GRID_COUNTS = 6;

/**
 * MenuTheme defines styles of menu item. MenuTheme should be built
 * using MenuTheme::Builder.
 */
class MenuTheme : public virtual Theme {
    DECLARE_ACE_TYPE(MenuTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<MenuTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<MenuTheme> theme = AceType::Claim(new MenuTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<MenuTheme>& theme) const
        {
            if (!themeStyle) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_SELECT, nullptr);
            if (!pattern) {
                LOGE("Pattern of menu is null, please check!");
                return;
            }
            theme->previewMenuMaskColor_ = pattern->GetAttr<Color>("preview_menu_mask_color", Color(0x33182431));
            theme->filterAnimationDuration_ = 250;
            theme->previewAnimationDuration_ = 300;
            theme->previewBeforeAnimationScale_ = 0.95f;
            theme->previewAfterAnimationScale_ = 1.1f;
            theme->menuAnimationScale_ = 0.4f;
            theme->menuDragAnimationScale_ = 0.95f;
            theme->springMotionResponse_ = 0.416f;
            theme->springMotionDampingFraction_ = 0.73f;
            theme->contextMenuAppearDuration_ = 250;
            theme->disappearDuration_ = 250;
            theme->previewDisappearSpringMotionResponse_ = 0.304f;
            theme->previewDisappearSpringMotionDampingFraction_ = 0.97f;
            theme->filterRadius_ = Dimension(100.0f);
            theme->previewBorderRadius_ = 16.0_vp;
            theme->previewMenuScaleNumber_ = 0.95f;
        }
    };

    ~MenuTheme() override = default;

    int32_t GetFilterAnimationDuration() const
    {
        return filterAnimationDuration_;
    }

    int32_t GetPreviewAnimationDuration() const
    {
        return previewAnimationDuration_;
    }

    float GetPreviewBeforeAnimationScale() const
    {
        return previewBeforeAnimationScale_;
    }

    float GetPreviewAfterAnimationScale() const
    {
        return previewAfterAnimationScale_;
    }

    float GetMenuAnimationScale() const
    {
        return menuAnimationScale_;
    }

    float GetMenuDragAnimationScale() const
    {
        return menuDragAnimationScale_;
    }

    float GetSpringMotionResponse() const
    {
        return springMotionResponse_;
    }

    float GetSpringMotionDampingFraction() const
    {
        return springMotionDampingFraction_;
    }

    int32_t GetContextMenuAppearDuration() const
    {
        return contextMenuAppearDuration_;
    }

    int32_t GetDisappearDuration() const
    {
        return disappearDuration_;
    }

    float GetPreviewDisappearSpringMotionResponse() const
    {
        return previewDisappearSpringMotionResponse_;
    }

    float GetPreviewDisappearSpringMotionDampingFraction() const
    {
        return previewDisappearSpringMotionDampingFraction_;
    }

    float GetPreviewMenuScaleNumber() const
    {
        return previewMenuScaleNumber_;
    }

    Dimension GetFilterRadius() const
    {
        return filterRadius_;
    }

    Dimension GetPreviewBorderRadius() const
    {
        return previewBorderRadius_;
    }

    Color GetPreviewMenuMaskColor() const
    {
        return previewMenuMaskColor_;
    }

protected:
    MenuTheme() = default;

private:
    int32_t filterAnimationDuration_ = 0;
    int32_t previewAnimationDuration_ = 0;
    float previewBeforeAnimationScale_ = 1.0f;
    float previewAfterAnimationScale_ = 1.0f;
    float menuAnimationScale_ = 1.0f;
    float menuDragAnimationScale_ = 1.0f;
    float springMotionResponse_ = 0.0f;
    float springMotionDampingFraction_ = 0.0f;
    int32_t contextMenuAppearDuration_ = 0;
    int32_t disappearDuration_ = 0;
    float previewDisappearSpringMotionResponse_ = 0.0f;
    float previewDisappearSpringMotionDampingFraction_ = 0.0f;
    float previewMenuScaleNumber_ = 0.0f;
    Dimension filterRadius_;
    Dimension previewBorderRadius_;
    Color previewMenuMaskColor_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_THEME_H
