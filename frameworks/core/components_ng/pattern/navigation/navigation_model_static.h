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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_STATIC_H

#include <string>

#include "base/geometry/dimension.h"
#include "core/components_ng/base/navigation_register.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_options.h"

namespace OHOS::Ace::NG {
using NavigationTransitionEvent = std::function<NG::NavigationTransition(
     RefPtr<NG::NavDestinationContext> from, RefPtr<NG::NavDestinationContext> to, NG::NavigationOperation operation)>;
class ACE_EXPORT NavigationModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetNavBarWidth(FrameNode* frameNode, const Dimension& value);
    static void SetMinNavBarWidth(FrameNode* frameNode, const Dimension& value);
    static void SetMaxNavBarWidth(FrameNode* frameNode, const Dimension& value);
    static void SetNavBarPosition(FrameNode* frameNode, const std::optional<NG::NavBarPosition>& mode);
    static void SetMinContentWidth(FrameNode* frameNode, const Dimension& value);
    static void SetSystemBarStyle(FrameNode* frameNode, const Color& contentColor);
    static void SetUsrNavigationMode(FrameNode* frameNode, const std::optional<NavigationMode>& mode);
    static void SetBackButtonIcon(FrameNode* frameNode, const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
        const std::string& src, const ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
        const std::vector<std::string>& nameList, bool userDefinedAccessibilityText = false,
        const std::string& backButtonAccessibilityText = "");
    static void SetHideNavBar(FrameNode* frameNode, bool hideNavBar);
    static void SetHideTitleBar(FrameNode* frameNode, bool hideTitleBar, bool animated = false);
    static void SetHideBackButton(FrameNode* frameNode, bool hideBackButton);
    static void SetTitleMode(FrameNode* frameNode, NG::NavigationTitleMode mode);
    static void SetMenuItems(FrameNode* frameNode, std::vector<NG::BarItem>&& menuItems);
    static void SetMenuOptions(FrameNode* frameNode, NG::NavigationMenuOptions&& opt);
    static void SetHideToolBar(FrameNode* frameNode, bool hideToolBar, bool animated = false);
    static void SetTitlebarOptions(FrameNode* frameNode, NavigationTitlebarOptions&& opt);

    static void SetToolBarItems(FrameNode* frameNode, std::vector<NG::BarItem>&& toolBarItems);
    static void SetToolbarConfiguration(FrameNode* frameNode, std::vector<NG::BarItem>&& toolBarItems);
    static void SetToolbarOptions(FrameNode* frameNode, NavigationToolbarOptions&& opt);
    static void SetToolbarMorebuttonOptions(FrameNode* frameNode, MoreButtonOptions&& opt);
    static void ParseCommonTitle(
        FrameNode* frameNode, const NG::NavigationTitleInfo& titleInfo, bool ignoreMainTitle = false);
    static void SetIgnoreLayoutSafeArea(FrameNode* frameNode, const NG::IgnoreLayoutSafeAreaOpts& opts);
    static bool CreateBackButtonNode(RefPtr<FrameNode>& backButtonNode);
    static bool UpdateBackButtonProperty(const RefPtr<FrameNode>& backButtonNode);
    static void SetCustomMenu(FrameNode* frameNode, const RefPtr<UINode>& customNode);
    static void SetIsCustomAnimation(FrameNode* frameNode, bool isCustom);
    static void SetCustomTransition(FrameNode* frameNode, NavigationTransitionEvent&& customTransition);
    static void SetCustomTitle(FrameNode* frameNode, const RefPtr<UINode>& customNode);
    static void SetCustomToolBar(FrameNode* frameNode, const RefPtr<UINode>& customNode);
    static void SetTitleHeight(FrameNode* frameNode, const Dimension& height, bool isValid = true);

private:
    static bool navBarWidthDoubleBind_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_STATIC_H