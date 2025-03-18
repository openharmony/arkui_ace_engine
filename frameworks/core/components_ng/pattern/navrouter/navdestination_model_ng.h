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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVDESTINATION_NAVDESTINATION_MODEL_NG_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVDESTINATION_NAVDESTINATION_MODEL_NG_H

#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_model.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT NavDestinationModelNG : public OHOS::Ace::NavDestinationModel {
public:
    void Create() override;
    void Create(std::function<void()>&& deepRenderFunc, RefPtr<NG::NavDestinationContext> context = nullptr) override;
    void SetHideTitleBar(bool hideTitleBar, bool animated) override;
    void SetHideBackButton(bool hideBackButton) override;
    void SetTitle(const std::string& title, bool hasSubTitle) override;
    void SetTitlebarOptions(NG::NavigationTitlebarOptions&& opt) override;
    void SetBackButtonIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& iconSymbol, const std::string& src,
        const ImageOption& imageOption, RefPtr<PixelMap>& pixMap, const std::vector<std::string>& nameList,
        bool userDefinedAccessibilityText = false, const std::string& backButtonAccessibilityText = "") override;
    void SetSubtitle(const std::string& subtitle) override;
    void SetCustomTitle(const RefPtr<AceType>& customNode) override;
    void SetTitleHeight(const Dimension& titleHeight, bool isValid = true) override;
    void SetOnShown(std::function<void()>&& onShow) override;
    void SetOnHidden(std::function<void()>&& onHidden) override;
    void SetOnWillAppear(std::function<void()>&& willAppear) override;
    void SetOnWillShow(std::function<void()>&& willShow) override;
    void SetOnWillHide(std::function<void()>&& willHide) override;
    void SetOnWillDisAppear(std::function<void()>&& willDisAppear) override;
    void SetOnActive(std::function<void(int32_t)>&& onActive) override;
    void SetOnInactive(std::function<void(int32_t)>&& onInactive) override;
    void SetOnPop(std::function<void(const RefPtr<NavPathInfo>&)>&& popCallback) override;
    void SetOnBackPressed(std::function<bool()>&& onBackPressed) override;
    void SetHideToolBar(bool hideToolBar, bool animated) override;
    static void SetHideToolBar(FrameNode* frameNode, bool hideToolBar, bool animated);
    void SetToolbarConfiguration(std::vector<NG::BarItem>&& toolBarItems) override;
    void SetCustomToolBar(const RefPtr<AceType>& customNode) override;
    void SetHideItemText(bool isHideItemText) override;
    void SetToolBarOptions(NavigationToolbarOptions&& opt) override;
    void SetToolbarMorebuttonOptions(MoreButtonOptions&& opt) override;
    void SetOnReady(std::function<void(RefPtr<NavDestinationContext>)>&& onReady) override;
    RefPtr<AceType> CreateEmpty() override;
    static void SetHideTitleBar(FrameNode* frameNode, bool hideTitleBar, bool animated);
    static void SetHideBackButton(FrameNode* frameNode, bool hideBackButton);
    static void SetBackgroundColor(FrameNode* frameNode, const Color& color, bool isVaild = true);
    static void SetBackButtonIcon(FrameNode* frameNode, const std::string& src,
        bool noPixMap, RefPtr<PixelMap>& pixMap);
    static void SetNavDestinationMode(FrameNode* frameNode, NavDestinationMode mode);
    static void SetRecoverable(FrameNode* frameNode, bool recoverable);

    void SetNavDestinationMode(NavDestinationMode mode) override;
    void SetRecoverable(bool recoverable) override;
    bool ParseCommonTitle(
        bool hasSubTitle, bool hasMainTitle, const std::string& subtitle, const std::string& title) override;
    void SetMenuItems(std::vector<NG::BarItem>&& menuItems) override;
    void SetCustomMenu(const RefPtr<AceType>& customNode) override;
    void SetMenuOptions(NavigationMenuOptions&& opt) override;
    void SetBackgroundColor(const Color& color, bool isVaild = true) override;
    void SetIgnoreLayoutSafeArea(const SafeAreaExpandOpts& opts) override;
    static void SetIgnoreLayoutSafeArea(FrameNode* frameNode, const SafeAreaExpandOpts& opts);
    void SetNavDestinationPathInfo(const std::string& moduleName, const std::string& pagePath) override;
    void SetSystemBarStyle(const RefPtr<SystemBarStyle>& style) override;
    static void ParseCommonTitle(FrameNode* frameNode, const NG::NavigationTitleInfo& titleInfo);
    static void SetTitlebarOptions(FrameNode* frameNode, NavigationTitlebarOptions&& opt);
    static void SetMenuItems(FrameNode* frameNode, std::vector<NG::BarItem>&& menuItems);
    static void SetMenuItemAction(FrameNode* frameNode, std::function<void()>&& action, uint32_t index);
    static void SetMenuItemSymbol(FrameNode* frameNode,
        std::function<void(WeakPtr<NG::FrameNode>)>&& symbol, uint32_t index);
    void SetSystemTransitionType(NG::NavigationSystemTransitionType type) override;
    static void SetSystemTransitionType(FrameNode* frameNode, NG::NavigationSystemTransitionType type);
    void SetScrollableProcessor(
        const std::function<RefPtr<NG::NavDestinationScrollableProcessor>()>& creator) override;
    void UpdateBindingWithScrollable(
        std::function<void(const RefPtr<NG::NavDestinationScrollableProcessor>& processor)>&& callback) override;
    static void SetCustomTitle(FrameNode* frameNode, const RefPtr<AceType>& customNode);
    static RefPtr<FrameNode> GetCustomTitle(FrameNode* frameNode);
    static void SetTitleHeight(FrameNode* frameNode, const Dimension& titleHeight, bool isValid);
    static void SetOnCoordScrollStartAction(FrameNode* frameNode, std::function<void()>&& onCoordScrollStart);
    static void SetOnCoordScrollUpdateAction(FrameNode* frameNode, std::function<void(float)>&& onCoordScrollUpdate);
    static void SetOnCoordScrollEndAction(FrameNode* frameNode, std::function<void()>&& onCoordScrollEnd);
    static void SetSystemBarStyle(FrameNode* frameNode, const Color& contentColor);
    static void SetOnShown(FrameNode* frameNode, std::function<void()>&& onShow);
    static void SetOnHidden(FrameNode* frameNode, std::function<void()>&& onHidden);
    static void SetCustomBackButtonNode(FrameNode* frameNode, FrameNode* backButtonNode);
    void SetCustomTransition(NG::NavDestinationTransitionDelegate&& transitionDelegate) override;
    void SetOnNewParam(NG::NavDestinationOnNewParamCallback&& onNewParamCallback) override;
    void SetPreferredOrientation(const std::optional<Orientation>& ori) override;
    static void SetPreferredOrientation(FrameNode* frameNode, const std::optional<Orientation>& ori);
    void SetEnableStatusBar(const std::optional<std::pair<bool, bool>>& statusBar) override;
    static void SetEnableStatusBar(
        FrameNode* frameNode, const std::optional<std::pair<bool, bool>>& statusBar);
    void SetEnableNavigationIndicator(const std::optional<bool>& navigationIndicator) override;
    static void SetEnableNavigationIndicator(
        FrameNode* frameNode, const std::optional<bool>& navigationIndicator);

private:
    void CreateBackButton(const RefPtr<NavDestinationGroupNode>& navDestinationNode);
    void CreateImageButton(const RefPtr<NavDestinationGroupNode>& navDestinationNode);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVDESTINATION_NAVDESTINATION_MODEL_NG_H
