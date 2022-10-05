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
#include "core/components_ng/pattern/navigation/navigation_declaration.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavigationView {
public:
    static void Create();
    // title
    static void SetTitle(const std::string& title);
    static void SetCustomTitle(const RefPtr<UINode>& customTitle);
    static void SetTitleMode(NG::NavigationTitleMode mode);
    static void SetSubtitle(const std::string& subtitle);
    static void SetHideTitleBar(bool hideTitleBar);
    // back button
    static void SetHideBackButton(bool hideBackButton);
    // toolbar
    static void SetHideToolBar(bool hideToolBar);
    static void SetToolBarItems(std::list<BarItem>&& customToolBarItems);
    static void SetCustomToolBar(const RefPtr<UINode>& customToolBar);
    // menu
    static void SetCustomMenu(const RefPtr<UINode>& customMenu);
    static void SetMenuItems(std::list<BarItem>&& menuItems);
    // title mode change
    static void SetOnTitleModeChange(std::function<void(NavigationTitleMode)>&& onTitleModeChange);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_VIEW_H
