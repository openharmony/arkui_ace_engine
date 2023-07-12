/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_NAVIGATION_NAVIGATION_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_NAVIGATION_NAVIGATION_DECLARATION_H

#include <string>

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/declaration/common/declaration.h"
#include "core/components/navigation_bar/navigation_bar_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

inline RefPtr<NavigationBarTheme> NavigationGetTheme()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = pipeline->GetTheme<NavigationBarTheme>();
    return theme;
}

// TODO：move some items to theme
// title bar back button
const std::string BACK_BUTTON = "Back";
constexpr InternalResource::ResourceId BACK_ICON = InternalResource::ResourceId::IC_BACK;
constexpr InternalResource::ResourceId MORE_ICON = InternalResource::ResourceId::IC_MORE;
// title bar and tool bar, bar item
constexpr float BAR_ITEM_WIDTH = 40.0f;
constexpr float BAR_ITEM_HEIGHT = 60.0f;
constexpr float BAR_TEXT_FONT_SIZE = 18.0f;
// title bar title and subtitle
constexpr float TITLE_WIDTH = 100.0f;
// single page maximum width
constexpr float SINGLE_PAGE_MAXIMUM_WIDTH = 720.0f;

// title
constexpr Dimension TITLE_HEIGHT = 56.0_vp;
constexpr Dimension MAX_TITLE_FONT_SIZE = 30.0_vp;
constexpr Dimension MIN_TITLE_FONT_SIZE = 20.0_vp;
// subtitle
constexpr Dimension SUBTITLE_FONT_SIZE = 14.0_vp; // ohos_id_text_size_sub_title3
constexpr Dimension SUBTITLE_HEIGHT = 26.0_vp;
constexpr Color SUBTITLE_COLOR = Color(0x99000000); // ohos_id_alpha_content_secondary
// back button
constexpr Dimension BACK_BUTTON_SIZE = 48.0_vp;
constexpr Dimension BACK_BUTTON_ICON_SIZE = 24.0_vp;
// title bar
constexpr Dimension TITLEBAR_HEIGHT_MINI = 56.0_vp;
constexpr Dimension TITLEBAR_HEIGHT_WITH_SUBTITLE = 137.0_vp;
constexpr Dimension TITLEBAR_HEIGHT_WITHOUT_SUBTITLE = 112.0_vp;
// toolbar item
constexpr Dimension TEXT_FONT_SIZE = 10.0_vp;
constexpr Color TEXT_COLOR = Color(0xE6000000);
constexpr Color ICON_COLOR = Color(0xE6000000);
// toolbar
constexpr Dimension ICON_PADDING = 10.0_vp;
constexpr Dimension TEXT_TOP_PADDING = 2.0_vp;

// divider
constexpr Dimension DIVIDER_WIDTH = 1.0_vp;
constexpr Color DIVIDER_COLOR = Color(0x08000000);
constexpr Dimension DEFAULT_DIVIDER_START_MARGIN = 0.0_vp;
constexpr Dimension DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING = 2.0_vp;
constexpr int32_t DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_NUM = 2;

// navigation content
constexpr Dimension SINGLE_LINE_TITLEBAR_HEIGHT = 56.0_vp;
constexpr Dimension DOUBLE_LINE_TITLEBAR_HEIGHT = 82.0_vp;
constexpr Dimension DEFAULT_MIN_CONTENT_WIDTH = 360.0_vp;

// navBar
constexpr Dimension FULL_SINGLE_LINE_TITLEBAR_HEIGHT = 112.0_vp;
constexpr Dimension FULL_DOUBLE_LINE_TITLEBAR_HEIGHT = 138.0_vp;
constexpr Dimension HORIZONTAL_MARGIN_L = 16.0_vp; // ohos_id_elements_margin_horizontal_l
constexpr Dimension HORIZONTAL_MARGIN_M = 8.0_vp; // ohos_id_elements_margin_horizontal_m
constexpr Dimension MENU_ITEM_PADDING = 24.0_vp;
constexpr Dimension BUTTON_PADDING = 12.0_vp;
constexpr Dimension BUTTON_RADIUS = 5.0_vp;
constexpr Dimension MAX_OVER_DRAG_OFFSET = 180.0_vp;
constexpr Dimension DEFAULT_MIN_NAV_BAR_WIDTH = 240.0_vp;
constexpr Dimension DEFAULT_MAX_NAV_BAR_WIDTH = 432.0_vp;
constexpr float MAX_NAV_BAR_WIDTH_SCALE = 0.4f;

// more button
constexpr Dimension MORE_BUTTON_CORNER_RADIUS = 8.0_vp;

struct BarItem {
    std::optional<std::string> text;
    std::optional<std::string> icon;
    std::function<void()> action;
    std::string ToString() const
    {
        std::string result;
        result.append("text: ");
        result.append(text.value_or("na"));
        result.append(", icon: ");
        result.append(icon.value_or("na"));
        return result;
    }
};

enum class TitleBarChildType {
    TITLE = 0,
    SUBTITLE,
    MENU,
};

enum class NavigationTitleMode {
    FREE = 0,
    FULL,
    MINI,
};

enum class NavigationMode {
    STACK = 0,
    SPLIT,
    AUTO,
};

enum class NavBarPosition {
    START = 0,
    END,
};

enum class ChildNodeOperation {
    ADD,
    // remove case only used for back button
    REMOVE,
    REPLACE,
    NONE
};

enum class TitleHeight {
    MAIN_ONLY,
    MAIN_WITH_SUB
};

enum class TitleBarParentType {
    NAVBAR,
    NAV_DESTINATION
};

enum class NavRouteMode {
    PUSH_WITH_RECREATE = 0,
    PUSH,
    REPLACE,
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_NAVIGATION_NAVIGATION_DECLARATION_H
