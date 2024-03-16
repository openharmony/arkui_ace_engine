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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TOOL_BAR_TOOL_BAR_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TOOL_BAR_TOOL_BAR_THEME_H

#include <vector>

#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components/theme/theme_manager.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace {

/**
 * ToolBarTheme defines color and styles of ToolBar. ToolBarTheme should be built
 * using ToolBarTheme::Builder.
 */
class ToolBarTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ToolBarTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ToolBarTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ToolBarTheme> theme = AceType::Claim(new ToolBarTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ToolBarTheme>& theme) const
        {
            RefPtr<ThemeStyle> toolbarPattern = themeConstants->GetPatternByName(THEME_PATTERN_TOOLBAR);
            if (!toolbarPattern) {
                LOGI("ToolbarPattern is null");
                return;
            }
            theme->iconMoreColor_ = toolbarPattern->GetAttr<Color>("more_icon_color", Color());
            theme->textStyle_.SetTextColor(toolbarPattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::BLACK));
            theme->iconColor_ = toolbarPattern->GetAttr<Color>("icon_color", Color());
            theme->toolBarBgColor_ = toolbarPattern->GetAttr<Color>(PATTERN_BG_COLOR, Color());
            theme->toolBarItemBgColor_ = toolbarPattern->GetAttr<Color>("item_bg_color", Color());
            theme->textStyle_.SetFontSize(toolbarPattern->GetAttr<Dimension>("text_fontsize", 10.0_fp));
            theme->textStyle_.SetFontFamilies({ toolbarPattern->GetAttr<std::string>("text_font_family_medium",
                "HwChinese-medium") });
            theme->textStyle_.SetAdaptTextSize(toolbarPattern->GetAttr<Dimension>("text_fontsize", 10.0_fp),
                toolbarPattern->GetAttr<Dimension>("text_min_fontsize", 9.0_vp));
            theme->iconSize_ = Size(toolbarPattern->GetAttr<Dimension>("item_icon_width", 24.0_vp).Value(),
                toolbarPattern->GetAttr<Dimension>("item_icon_height", 24.0_vp).Value());
            theme->imageEdge_ = Edge(toolbarPattern->GetAttr<Dimension>("item_padding_icon_left", 1.0_vp),
                toolbarPattern->GetAttr<Dimension>("item_padding_icon_top", 8.0_vp),
                toolbarPattern->GetAttr<Dimension>("item_padding_icon_right", 1.0_vp),
                toolbarPattern->GetAttr<Dimension>("item_padding_icon_bottom", 1.0_vp));
            theme->textEdge_ = Edge(toolbarPattern->GetAttr<Dimension>("item_padding_text_left", 1.0_vp),
                toolbarPattern->GetAttr<Dimension>("item_padding_text_top", 1.0_vp),
                toolbarPattern->GetAttr<Dimension>("item_padding_text_right", 1.0_vp),
                toolbarPattern->GetAttr<Dimension>("item_padding_text_bottom", 8.0_vp));
            theme->focusColor_ = toolbarPattern->GetAttr<Color>("item_focus_color", Color(0xe6254ff7));
            theme->hoverColor_ = toolbarPattern->GetAttr<Color>("item_hover_color", Color(0x0c000000));
            theme->pressColor_ = toolbarPattern->GetAttr<Color>("control_normal", Color(0x19000000));
            theme->radius_ = toolbarPattern->GetAttr<Dimension>("item_radius", 8.0_vp);
        }
    };

    ~ToolBarTheme() override = default;

    const TextStyle& GetToolBarTextStyle() const
    {
        return textStyle_;
    }

    const Size& GetIconSize() const
    {
        return iconSize_;
    }

    const Edge& GetIconEdge() const
    {
        return imageEdge_;
    }

    const Edge& GetTextEdge() const
    {
        return textEdge_;
    }

    const Color& GetToolBarBgColor() const
    {
        return toolBarBgColor_;
    }

    const Color& GetItemBackgroundColor() const
    {
        return toolBarItemBgColor_;
    }

    const Color& GetIconColor() const
    {
        return iconColor_;
    }

    const Color& GetFocusColor() const
    {
        return focusColor_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetPressColor() const
    {
        return pressColor_;
    }

    const Dimension& GetRadius() const
    {
        return radius_;
    }

    const Color& GetIconMoreColor() const
    {
        return iconMoreColor_;
    }

protected:
    ToolBarTheme() = default;

private:
    Edge imageEdge_;
    Edge textEdge_;
    TextStyle textStyle_;
    Size iconSize_;
    Color toolBarBgColor_;
    Color iconColor_;
    Color focusColor_;
    Color hoverColor_;
    Color toolBarItemBgColor_;
    Color pressColor_;
    Dimension radius_;
    Color iconMoreColor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TOOL_BAR_TOOL_BAR_THEME_H
