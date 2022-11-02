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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_VIEW_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/image/image_model.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavigationView {
public:
    static void Create();
    // title bar
    static void SetTitle(const std::string& title, bool hasSubTitle = false);
    static void SetCustomTitle(const RefPtr<UINode>& customTitle);
    static void SetTitleMode(NG::NavigationTitleMode mode);
    static void SetSubtitle(const std::string& subtitle);
    static void SetHideTitleBar(bool hideTitleBar);
    static void SetTitleHeight(const Dimension& height);
    static void SetBackButtonIcon(const std::string& src, bool noPixMap, RefPtr<PixelMap>& pixMap);
    static void SetHideBackButton(bool hideBackButton);
    static void SetCustomMenu(const RefPtr<UINode>& customMenu);
    static void SetMenuItems(std::list<BarItem>&& menuItems);
    // toolbar
    static void SetHideToolBar(bool hideToolBar);
    static void SetToolBarItems(std::list<BarItem>&& customToolBarItems);
    static void SetCustomToolBar(const RefPtr<UINode>& customToolBar);

    static void SetNavigationMode(NG::NavigationMode mode);
    static void SetNavBarWidth(const Dimension& value);
    static void SetNavBarPosition(NG::NavBarPosition mode);
    static void SetHideNavBar(bool hideNavBar);
    static void SetOnTitleModeChange(std::function<void(NavigationTitleMode)>&& onTitleModeChange);
    static void SetOnNavBarStateChange(std::function<void(bool)>&& onNavBarStateChange);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_VIEW_H
