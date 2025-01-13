/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_H

#include <functional>
#include <mutex>
#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/system_bar/system_bar_style.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_options.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navigation/navigation_transition_proxy.h"
#include "core/components_ng/pattern/navrouter/navdestination_context.h"

namespace OHOS::Ace {
using NavigationTransitionEvent = std::function<NG::NavigationTransition(
     RefPtr<NG::NavDestinationContext> from, RefPtr<NG::NavDestinationContext> to, NG::NavigationOperation operation)>;
using OnNavBarWidthChangeEvent = std::function<void(const Dimension)>;
class ACE_FORCE_EXPORT NavigationModel {
public:
    static NavigationModel* GetInstance();
    virtual ~NavigationModel() = default;

    virtual void Create() = 0;
    virtual void SetNavigationStack() = 0;
    virtual void SetNavigationStack(const RefPtr<NG::NavigationStack>& navigationStack) = 0;
    virtual void SetNavigationStackWithCreatorAndUpdater(std::function<RefPtr<NG::NavigationStack>()> creator,
        std::function<void(RefPtr<NG::NavigationStack>)> updater) {};
    virtual void SetNavigationPathInfo(const std::string& moduleName, const std::string& pagePath) {};
    virtual void SetNavigationStackProvided(bool provided) = 0;
    virtual bool ParseCommonTitle(bool hasSubTitle, bool hasMainTitle, const std::string& subtitle,
        const std::string& title, bool ignoreMainTitle = false)
    {
        return false;
    }
    virtual void SetTitle(const std::string& title, bool hasSubTitle = false) = 0;
    virtual void SetTitlebarOptions(NG::NavigationTitlebarOptions&& opt) {}
    virtual void SetCustomTitle(const RefPtr<AceType>& customNode) = 0;
    virtual void SetTitleHeight(const Dimension& height, bool isValid = true) = 0;
    virtual void SetTitleMode(NG::NavigationTitleMode mode) = 0;
    virtual void SetSubtitle(const std::string& subtitle) = 0;
    virtual void SetEnableModeChangeAnimation(bool isEnable) = 0;
    virtual void SetHideTitleBar(bool hideTitleBar, bool animated = false) = 0;
    virtual void SetHideNavBar(bool hideNavBar) = 0;
    virtual void SetBackButtonIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
        const std::string& src, const NG::ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
        const std::vector<std::string>& nameList);
    virtual void SetHideBackButton(bool hideBackButton) = 0;
    virtual void SetHideToolBar(bool hideToolBar, bool animated = false) = 0;
    virtual void SetCustomToolBar(const RefPtr<AceType>& customNode) = 0;
    virtual bool NeedSetItems() = 0;
    virtual void SetToolBarItems(std::vector<NG::BarItem>&& toolBarItems) = 0;
    virtual void SetToolbarConfiguration(std::vector<NG::BarItem>&& toolBarItems) = 0;
    virtual void GetToolBarItems(std::list<RefPtr<AceType>>& items) {};
    virtual void SetToolbarOptions(NG::NavigationToolbarOptions&& opt) {}
    virtual void SetMenuItems(std::vector<NG::BarItem>&& menuItems) = 0;
    virtual void GetMenuItems(std::list<RefPtr<AceType>>& items) {};
    virtual void SetCustomMenu(const RefPtr<AceType>& customNode) = 0;
    virtual void SetOnTitleModeChange(std::function<void(NG::NavigationTitleMode)>&& onTitleModeChange,
        std::function<void(const BaseEventInfo* baseInfo)>&& eventInfo) = 0;
    virtual void SetUsrNavigationMode(NG::NavigationMode mode) = 0;
    virtual void SetNavBarPosition(NG::NavBarPosition mode) = 0;
    virtual void SetNavBarWidth(const Dimension& value, bool isDoubleBind = false) = 0;
    virtual void SetMinNavBarWidth(const Dimension& value) = 0;
    virtual void SetMaxNavBarWidth(const Dimension& value) = 0;
    virtual void SetMinContentWidth(const Dimension& value) = 0;
    virtual void SetOnNavBarStateChange(std::function<void(bool)>&& onNavBarStateChange) = 0;
    virtual void SetOnNavigationModeChange(std::function<void(NG::NavigationMode)>&& onNavigationModeChange);
    virtual void SetOnNavBarWidthChangeEvent(OnNavBarWidthChangeEvent event) {};
    virtual void SetNavigationMode(NG::NavigationMode mode) = 0;
    virtual void SetNavDestination(std::function<void(std::string)>&& builder) = 0;
    virtual RefPtr<NG::NavigationStack> GetNavigationStack() = 0;
    virtual void SetMenuCount(int32_t menuCount) = 0;
    virtual void SetCustomTransition(NavigationTransitionEvent&& animationTransition);
    virtual void SetIsCustomAnimation(bool isCustom);
    virtual void SetIgnoreLayoutSafeArea(const NG::SafeAreaExpandOpts& opts) {};
    virtual void SetSystemBarStyle(const RefPtr<SystemBarStyle>& style) {};
    virtual void SetRecoverable(bool recoverable) {}
    virtual void SetEnableDragBar(bool recoverable) {}

private:
    static std::unique_ptr<NavigationModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_H
