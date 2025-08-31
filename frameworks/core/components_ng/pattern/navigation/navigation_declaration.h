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
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<NavigationBarTheme>();
}


inline RefPtr<NavigationBarTheme> NavigationGetTheme(int32_t themeScopeId)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<NavigationBarTheme>(themeScopeId);
}

// TODO：move some items to theme
// title bar back button
constexpr const char* BACK_BUTTON = "Back";
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
constexpr Dimension MAX_TITLE_FONT_SIZE = 30.0_vp;
constexpr Dimension MIN_TITLE_FONT_SIZE = 20.0_vp;
constexpr Dimension MIN_ADAPT_TITLE_FONT_SIZE = 14.0_vp;
constexpr const char* TITLE_MAIN = "MainOnly";
constexpr const char* TITLE_MAIN_WITH_SUB = "MainWithSub";

// subtitle
constexpr Dimension SUBTITLE_FONT_SIZE = 14.0_vp; // ohos_id_text_size_sub_title3
constexpr Dimension SUBTITLE_HEIGHT = 26.0_vp;
constexpr Dimension MIN_ADAPT_SUBTITLE_FONT_SIZE = 10.0_vp;
// back button
constexpr Dimension BACK_BUTTON_SIZE = 48.0_vp;
constexpr Dimension BACK_BUTTON_ICON_SIZE = 24.0_vp;
// title bar
constexpr Dimension TITLEBAR_HEIGHT_MINI = 56.0_vp;
constexpr Dimension TITLEBAR_HEIGHT_WITH_SUBTITLE = 137.0_vp;
constexpr Dimension TITLEBAR_HEIGHT_WITHOUT_SUBTITLE = 112.0_vp;
constexpr uint32_t TITLEBAR_MAX_LINES = 2;
// toolbar item
constexpr Dimension TEXT_FONT_SIZE = 10.0_vp;
constexpr Color TEXT_COLOR = Color(0xE6000000);
constexpr Color ICON_COLOR = Color(0xE6000000);
// toolbar
constexpr Dimension ICON_PADDING = 10.0_vp;
constexpr Dimension TEXT_TOP_PADDING = 2.0_vp;

// divider
constexpr Dimension DIVIDER_WIDTH = 1.0_px;
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
constexpr Dimension NAV_HORIZONTAL_MARGIN_L = 16.0_vp; // ohos_id_elements_margin_horizontal_l
constexpr Dimension NAV_HORIZONTAL_MARGIN_M = 8.0_vp;  // ohos_id_elements_margin_horizontal_m
constexpr Dimension MENU_ITEM_PADDING = 24.0_vp;
constexpr Dimension MENU_ITEM_SIZE = 48.0_vp;
constexpr Dimension BUTTON_PADDING = 12.0_vp;
constexpr Dimension MENU_BUTTON_PADDING = 8.0_vp;
constexpr Dimension BACK_BUTTON_SYMBOL_PADDING = 14.0_vp;
constexpr Dimension BUTTON_RADIUS_SIZE = 5.0_vp;
constexpr Dimension MAX_OVER_DRAG_OFFSET = 180.0_vp;
constexpr Dimension DEFAULT_MIN_NAV_BAR_WIDTH = 240.0_vp;
constexpr Dimension DEFAULT_MAX_NAV_BAR_WIDTH = 432.0_vp;
constexpr Dimension MAX_MENU_CHANGE_SIZE = 600.0_vp;
constexpr int8_t MAX_MENU_NUM_SMALL = 3;
const int8_t MAX_MENU_NUM_LARGE = 5;
constexpr float MAX_NAV_BAR_WIDTH_SCALE = 0.4f;

// more button
constexpr Dimension MORE_BUTTON_CORNER_RADIUS = 8.0_vp;

// maximum number of toolbar items
constexpr uint32_t MAXIMUM_TOOLBAR_ITEMS_IN_BAR = 5;
constexpr uint32_t ONE_TOOLBAR_ITEM = 1;

// navigation page info
constexpr char NAVIGATION_MODULE_NAME[] = "moduleName";
constexpr char NAVIGATION_PAGE_PATH[] = "pagePath";
constexpr char IS_USER_CREATE_STACK[] = "isUserCreateStack";

// navigation/navdestination Field
constexpr const char* NAV_FIELD = "__NavigationField__";
constexpr const char* DES_FIELD = "__NavdestinationField__";

// font scale
constexpr float STANDARD_FONT_SCALE = 1.0f;

constexpr int32_t ROTATION_0 = 0;
constexpr int32_t ROTATION_90 = 90;
constexpr int32_t ROTATION_180 = 180;
constexpr int32_t ROTATION_270 = 270;

constexpr uint32_t BAR_ITEM_MARGIN_NUM = 2;

enum class NavToolbarItemStatus {
    NORMAL = 0,
    DISABLED,
    ACTIVE,
};

// appbar menu item and toolbar item configuration
struct BarItem {
    std::optional<std::string> text;
    std::optional<std::string> icon;
    std::optional<std::function<void(WeakPtr<NG::FrameNode>)>> iconSymbol;
    std::optional<bool> isEnabled;
    std::function<void()> action;
    NavToolbarItemStatus status;
    std::optional<std::string> activeIcon;
    std::optional<std::function<void(WeakPtr<NG::FrameNode>)>> activeIconSymbol;
    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, BarItem&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;
    std::string ToString() const
    {
        std::string result;
        result.append("text: ");
        result.append(text.value_or("na"));
        result.append(", icon: ");
        result.append(icon.value_or("na"));
        return result;
    }

    void AddResource(const std::string& key, const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, BarItem&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = { resObj, std::move(updateFunc) };
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
        }
    }
};

struct NavigationTitleInfo {
    bool hasSubTitle;
    bool hasMainTitle;
    std::string subtitle;
    std::string title;
};

enum class ToolbarIconStatus {
    INITIAL = 0,
    ACTIVE,
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

enum class NavDestinationMode {
    STANDARD = 0,
    DIALOG,
};

enum class ChildNodeOperation {
    ADD,
    // remove case only used for back button
    REMOVE,
    REPLACE,
    NONE
};

enum class BarStyle {
    STANDARD = 0,
    STACK,
    SAFE_AREA_PADDING,
};

enum class TitleBarParentType { NAVBAR, NAV_DESTINATION };

enum class NavRouteMode {
    PUSH_WITH_RECREATE = 0,
    PUSH,
    REPLACE,
};

enum class NavigationOperation {
    PUSH = 1,
    POP,
    REPLACE,
};

enum NavDestinationLifecycle {
    ON_WILL_APPEAR = 0,
    ON_APPEAR,
    ON_WILL_SHOW,
    ON_SHOW,
    ON_ACTIVE,
    ON_WILL_HIDE,
    ON_INACTIVE,
    ON_HIDE,
    ON_WILL_DISAPPEAR,
    ON_DISAPPEAR
};

enum class NavDestinationActiveReason {
    TRANSITION = 0,
    CONTENT_COVER,
    SHEET,
    DIALOG,
    OVERLAY,
    APP_STATE_CHANGE
};

enum class NavDestVisibilityChangeReason {
    TRANSITION = 0,
    CONTENT_COVER,
    APP_STATE
};

union NavDestLifecycleReason {
    NavDestinationActiveReason activeReason;
    NavDestVisibilityChangeReason visibilityChangeReason;

    NavDestLifecycleReason(NavDestinationActiveReason activeReason) : activeReason(activeReason) {}
    NavDestLifecycleReason(NavDestVisibilityChangeReason visibilityChangeReason)
        : visibilityChangeReason(visibilityChangeReason) {}
};

enum class NavigationSystemTransitionType {
    NONE = 0,
    TITLE = 1,
    CONTENT = 1 << 1,
    DEFAULT = 1 | (1 << 1),
    FADE = 1 << 2,
    EXPLODE = 1 << 3,
    SLIDE_RIGHT = 1 << 4,
    SLIDE_BOTTOM = 1 << 5,
};

enum class NavDestinationType {
    DETAIL = 0,
    HOME = 1,
    PROXY = 2
};

inline NavigationSystemTransitionType operator& (NavigationSystemTransitionType lv, NavigationSystemTransitionType rv)
{
    return static_cast<NavigationSystemTransitionType>(static_cast<uint32_t>(lv) & static_cast<uint32_t>(rv));
}
struct NavSafeArea {
    float top = 0.0f;
    float bottom = 0.0f;
};

struct NavDestinationTransition {
    int32_t delay;
    int32_t duration;
    RefPtr<Curve> curve;
    std::function<void()> event;
    std::function<void()> onTransitionEnd;
};

enum class LaunchMode {
    STANDARD = 0,
    MOVE_TO_TOP_SINGLETON,
    POP_TO_TOP_SINGLETON,
    NEW_INSTANCE,
};

struct NavigationOptions {
    LaunchMode launchMode = LaunchMode::STANDARD;
    bool animated = true;
};

using NavDestinationTransitionDelegate = std::function<std::optional<std::vector<NavDestinationTransition>>(
    NavigationOperation operation, bool isEnter)>;
using NavDestinationOnNewParamCallback = std::function<void(napi_value param)>;

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_NAVIGATION_NAVIGATION_DECLARATION_H
