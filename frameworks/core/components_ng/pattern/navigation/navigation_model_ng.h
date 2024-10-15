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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_NG_H

#include "core/components_ng/pattern/navigation/navigation_model.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/base/navigation_register.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT NavigationModelNG : public OHOS::Ace::NavigationModel {
public:
    void Create() override;
    void SetNavigationStack() override;
    void SetNavigationStack(const RefPtr<NG::NavigationStack>& navigationStack) override;
    void SetNavigationStackWithCreatorAndUpdater(std::function<RefPtr<NG::NavigationStack>()> creator,
        std::function<void(RefPtr<NG::NavigationStack>)> updater) override;
    void SetNavigationStackProvided(bool provided) override;
    void SetNavigationPathInfo(const std::string& moduleName, const std::string& pagePath) override;
    bool ParseCommonTitle(bool hasSubTitle, bool hasMainTitle, const std::string& subtitle,
        const std::string& title, bool ignoreMainTitle = false) override;
    void SetTitle(const std::string& title, bool hasSubTitle = false) override;
    void SetTitlebarOptions(NavigationTitlebarOptions&& opt) override;
    void SetCustomTitle(const RefPtr<AceType>& customNode) override;
    void SetTitleHeight(const Dimension& height, bool isValid = true) override;
    void SetTitleMode(NG::NavigationTitleMode mode) override;
    void SetSubtitle(const std::string& subtitle) override;
    void SetHideTitleBar(bool hideTitleBar, bool animated = false) override;
    void SetHideNavBar(bool hideNavBar) override;
    void SetBackButtonIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply, const std::string& src,
        const ImageOption& imageOption, RefPtr<PixelMap>& pixMap, const std::vector<std::string>& nameList) override;
    void SetHideBackButton(bool hideBackButton) override;
    void SetHideToolBar(bool hideToolBar, bool animated = false) override;
    void SetCustomToolBar(const RefPtr<AceType>& customNode) override;
    bool NeedSetItems() override;

    void SetToolBarItems(std::vector<NG::BarItem>&& toolBarItems) override;
    void SetToolbarConfiguration(std::vector<NG::BarItem>&& toolBarItems) override;
    void SetToolbarOptions(NavigationToolbarOptions&& opt) override;
    void SetMenuItems(std::vector<NG::BarItem>&& menuItems) override;
    void SetCustomMenu(const RefPtr<AceType>& customNode) override;
    void SetOnTitleModeChange(std::function<void(NG::NavigationTitleMode)>&& onTitleModeChange,
        std::function<void(const BaseEventInfo* baseInfo)>&& eventInfo) override;
    void SetUsrNavigationMode(NG::NavigationMode mode) override;
    void SetNavBarPosition(NG::NavBarPosition mode) override;
    void SetNavBarWidth(const Dimension& value) override;
    void SetMinNavBarWidth(const Dimension& value) override;
    void SetMaxNavBarWidth(const Dimension& value) override;
    void SetMinContentWidth(const Dimension& value) override;
    void SetOnNavBarStateChange(std::function<void(bool)>&& onNavBarStateChange) override;
    void SetNavigationMode(NG::NavigationMode mode) override;
    void SetNavDestination(std::function<void(std::string)>&& builder) override;
    RefPtr<NG::NavigationStack> GetNavigationStack() override;
    void SetMenuCount(int32_t menuCount) override;
    void SetOnNavigationModeChange(std::function<void(NG::NavigationMode)>&& onModeChange) override;
    void SetCustomTransition(NavigationTransitionEvent&& animationTransition) override;
    void SetIsCustomAnimation(bool isCustom) override;
    void SetRecoverable(bool recoverable) override;
    void SetEnableDragBar(bool enableDragBar) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetNavigationStack(FrameNode* frameNode);
    static void SetHideToolBar(FrameNode* frameNode, bool hideToolBar, bool animated);
    static void SetMinContentWidth(FrameNode* frameNode, const Dimension& value);
    static void SetMinNavBarWidth(FrameNode* frameNode, const Dimension& value);
    static void SetMaxNavBarWidth(FrameNode* frameNode, const Dimension& value);
    static void SetNavBarWidth(FrameNode* frameNode, const Dimension& value);
    static void SetNavBarPosition(FrameNode* frameNode, NG::NavBarPosition mode);
    static void SetUsrNavigationMode(FrameNode* frameNode, NavigationMode mode);
    static void SetBackButtonIcon(FrameNode* frameNode, const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
        const std::string& src, const ImageOption& imageOption, RefPtr<PixelMap>& pixMap);
    static void SetHideNavBar(FrameNode* frameNode, bool hideNavBar);
    static void SetHideTitleBar(FrameNode* frameNode, bool hideTitleBar, bool animated);
    static void SetSubtitle(FrameNode* frameNode, const std::string& subtitle);
    static void SetHideBackButton(FrameNode* frameNode, bool hideBackButton);
    static void SetTitleMode(FrameNode* frameNode, NG::NavigationTitleMode mode);
    static void SetRecoverable(FrameNode* frameNode, bool recoverable);
    static void SetEnableDragBar(FrameNode* frameNode, bool enableDragBar);

    void SetIgnoreLayoutSafeArea(const NG::SafeAreaExpandOpts& opts) override;
    static void SetIgnoreLayoutSafeArea(FrameNode* frameNode, const NG::SafeAreaExpandOpts& opts);
    void SetSystemBarStyle(const RefPtr<SystemBarStyle>& style) override;
    static void ParseCommonTitle(FrameNode* frameNode, const NG::NavigationTitleInfo& titleInfo,
        bool ignoreMainTitle = false);
    static void SetTitlebarOptions(FrameNode* frameNode, NavigationTitlebarOptions&& opt);
    static void SetMenuItems(FrameNode* frameNode, std::vector<NG::BarItem>&& menuItems);
    static void SetMenuItemAction(FrameNode* frameNode, std::function<void()>&& action, uint32_t index);
    static void SetMenuItemSymbol(FrameNode* frameNode,
        std::function<void(WeakPtr<NG::FrameNode>)>&& symbol, uint32_t index);

private:
    bool CreateNavBarNodeIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode);
    bool CreateNavBarNodeChildsIfNeeded(const RefPtr<NavBarNode>& navBarNode);
    bool CreateContentNodeIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode);
    bool CreateDividerNodeIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode);
    static void SetHideNavBarInner(const RefPtr<NavigationGroupNode>& navigationGroupNode, bool hideNavBar);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_NG_H
