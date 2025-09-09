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

#include "core/common/resource/resource_object.h"
#include "core/components_ng/pattern/navigation/navigation_model.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/base/navigation_register.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT NavigationModelNG : public OHOS::Ace::NavigationModel {
public:
    void Create(bool useHomeDestination = false) override;
    void SetNavigationStack() override;
    void SetNavigationStack(const RefPtr<NG::NavigationStack>& navigationStack) override;
    void SetNavigationStackWithCreatorAndUpdater(std::function<RefPtr<NG::NavigationStack>()> creator,
        std::function<void(RefPtr<NG::NavigationStack>)> updater) override;
    void SetNavigationStackProvided(bool provided) override;
    void SetNavigationPathInfo(const std::string& moduleName, const std::string& pagePath) override;
    bool ParseCommonTitle(bool hasSubTitle, bool hasMainTitle, const std::string& subtitle,
        const std::string& title, bool ignoreMainTitle = false) override;
    bool ParseCommonTitle(bool hasSubTitle, bool hasMainTitle, const RefPtr<ResourceObject>& subResObj,
        const RefPtr<ResourceObject>& mainResObj) override;
    void UpdateMainTitle(
        const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& mainResObj) override;
    void UpdateSubTitle(
        const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& subResObj) override;

    void SetTitle(const std::string& title, bool hasSubTitle = false) override;
    void SetTitlebarOptions(NavigationTitlebarOptions&& opt) override;
    void SetCustomTitle(const RefPtr<AceType>& customNode) override;
    void SetTitleHeight(const Dimension& height, bool isValid = true) override;
    void SetTitleHeight(const Dimension& height, const RefPtr<ResourceObject>& resObj) override;
    void SetTitleMode(NG::NavigationTitleMode mode) override;
    void SetSubtitle(const std::string& subtitle) override;
    void SetEnableModeChangeAnimation(bool isEnable) override;
    void SetSplitPlaceholder(const RefPtr<NG::UINode>& splitPlaceholder) override;
    void SetHideTitleBar(bool hideTitleBar, bool animated = false) override;
    void SetHideNavBar(bool hideNavBar) override;
    void SetBackButtonIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply, const std::string& src,
        const ImageOption& imageOption, RefPtr<PixelMap>& pixMap, const std::vector<std::string>& nameList,
        bool userDefinedAccessibilityText = false, const std::string& backButtonAccessibilityText = "") override;
    void SetBackButtonIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
        const RefPtr<ResourceObject>& resObj, const ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
        const std::vector<std::string>& nameList, bool userDefinedAccessibilityText = false,
        const std::string& backButtonAccessibilityText = "") override;
    void SetBackButtonIconTextRes(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
        const std::string& src, const NG::ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
        const std::vector<std::string>& nameList, bool userDefinedAccessibilityText,
        const RefPtr<ResourceObject>& resObj) override;
    void SetBackButtonIconSrcAndTextRes(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
        const RefPtr<ResourceObject>& backButtonResObj, const ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
        const std::vector<std::string>& nameList, bool userDefinedAccessibilityText,
        const RefPtr<ResourceObject>& backButtonTextResObj) override;
    void UpdateBackButtonIcon(const std::vector<std::string>& nameList,
        NG::FrameNode* frameNode, const RefPtr<ResourceObject>& backButtonIconResObj) override;
    void UpdateBackButtonIconText(bool userDefinedAccessibilityText,
        const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& backButtonTextResObj) override;
    void SetHideBackButton(bool hideBackButton) override;
    void SetHideToolBar(bool hideToolBar, bool animated = false) override;
    void SetCustomToolBar(const RefPtr<AceType>& customNode) override;
    bool NeedSetItems() override;

    void SetToolBarItems(std::vector<NG::BarItem>&& toolBarItems) override;
    void SetToolbarConfiguration(std::vector<NG::BarItem>&& toolBarItems) override;
    void SetToolbarConfiguration(std::vector<NG::BarItem>&& toolBarItems, MoreButtonOptions&& opt) override;
    void SetToolbarOptions(NavigationToolbarOptions&& opt) override;
    void SetHideItemText(bool isHideItemText) override;
    void SetEnableToolBarAdaptation(bool enable) override;
    void SetToolbarMorebuttonOptions(MoreButtonOptions&& opt) override;
    void SetMenuItems(std::vector<NG::BarItem>&& menuItems) override;
    void SetMenuOptions(NG::NavigationMenuOptions&& opt) override;
    void SetCustomMenu(const RefPtr<AceType>& customNode) override;
    void SetOnTitleModeChange(std::function<void(NG::NavigationTitleMode)>&& onTitleModeChange,
        std::function<void(const BaseEventInfo* baseInfo)>&& eventInfo) override;
    void SetUsrNavigationMode(NG::NavigationMode mode) override;
    void SetNavBarPosition(NG::NavBarPosition mode) override;
    void SetNavBarWidth(const Dimension& value, bool isDoubleBind = false) override;
    void SetNavBarWidth(const RefPtr<ResourceObject>& navBarWidthResObj) override;
    void SetMinNavBarWidth(const Dimension& value) override;
    void SetMaxNavBarWidth(const Dimension& value) override;
    void SetMinNavBarWidth(const RefPtr<ResourceObject>& minNavBarWidthResObj) override;
    void SetMaxNavBarWidth(const RefPtr<ResourceObject>& maxNavBarWidthResObj) override;
    void SetMinContentWidth(const Dimension& value) override;
    void SetMinContentWidth(const RefPtr<ResourceObject>& minContentWidthResObj) override;
    void SetOnNavBarStateChange(std::function<void(bool)>&& onNavBarStateChange) override;
    void SetNavigationMode(NG::NavigationMode mode) override;
    void SetNavDestination(std::function<void(std::string)>&& builder) override;
    RefPtr<NG::NavigationStack> GetNavigationStack() override;
    void SetMenuCount(int32_t menuCount) override;
    void SetOnNavigationModeChange(std::function<void(NG::NavigationMode)>&& onModeChange) override;
    void SetOnNavBarWidthChangeEvent(OnNavBarWidthChangeEvent event) override;
    void SetCustomTransition(NavigationTransitionEvent&& animationTransition) override;
    void SetIsCustomAnimation(bool isCustom) override;
    void SetRecoverable(bool recoverable) override;
    void SetEnableDragBar(bool enableDragBar) override;
    void ResetResObj(NavigationPatternType type, const std::string& key) override;
    void ResetSplitPlaceholder() override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetNavigationStack(FrameNode* frameNode);
    static void SetHideToolBar(FrameNode* frameNode, bool hideToolBar, bool animated);
    static void SetEnableModeChangeAnimation(FrameNode* frameNode, bool isEnable);
    static void SetSplitPlaceholder(FrameNode* frameNode, FrameNode* splitPlaceholder);
    static void ResetSplitPlaceholder(FrameNode* frameNode);
    static void SetMinContentWidth(FrameNode* frameNode, const Dimension& value);
    static void SetMinContentWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& minContentWidthResObj);
    static void SetMinNavBarWidth(FrameNode* frameNode, const Dimension& value);
    static void SetMinNavBarWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& minNavBarWidthResObj);
    static void SetMaxNavBarWidth(FrameNode* frameNode, const Dimension& value);
    static void SetMaxNavBarWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& maxNavBarWidthResObj);
    static void SetNavBarWidth(FrameNode* frameNode, const Dimension& value);
    static void SetNavBarWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& navBarWidthResObj);
    static void SetNavBarPosition(FrameNode* frameNode, NG::NavBarPosition mode);
    static void SetUsrNavigationMode(FrameNode* frameNode, NavigationMode mode);
    static void SetBackButtonIcon(FrameNode* frameNode, const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
        const std::string& src, const ImageOption& imageOption, RefPtr<PixelMap>& pixMap);
    static void SetBackButtonIcon(FrameNode* frameNode, const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
        const ImageOption& imageOption, RefPtr<PixelMap>& pixMap, const RefPtr<ResourceObject>& backButtonIconResObj);
    static void SetHideNavBar(FrameNode* frameNode, bool hideNavBar);
    static void SetHideTitleBar(FrameNode* frameNode, bool hideTitleBar, bool animated);
    static void SetSubtitle(FrameNode* frameNode, const std::string& subtitle);
    static void SetHideBackButton(FrameNode* frameNode, bool hideBackButton);
    static void SetTitleMode(FrameNode* frameNode, NG::NavigationTitleMode mode);
    static void SetRecoverable(FrameNode* frameNode, bool recoverable);
    static void SetEnableDragBar(FrameNode* frameNode, bool enableDragBar);
    static void SetEnableToolBarAdaptation(FrameNode* frameNode, bool enable);

    void SetIgnoreLayoutSafeArea(const NG::IgnoreLayoutSafeAreaOpts& opts) override;
    static void SetIgnoreLayoutSafeArea(FrameNode* frameNode, const NG::IgnoreLayoutSafeAreaOpts& opts);
    void SetSystemBarStyle(const RefPtr<SystemBarStyle>& style) override;
    static void ParseCommonTitle(FrameNode* frameNode, const NG::NavigationTitleInfo& titleInfo,
        bool ignoreMainTitle = false);
    static void ParseCommonTitle(
        FrameNode* frameNode, const RefPtr<ResourceObject>& titleResObj, const RefPtr<ResourceObject>& subtitleResObj);
    static void UpdateMainTitleInfo(
        const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& mainResObj);
    static void UpdateSubTitleInfo(
        const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& subResObj);
    static void SetTitlebarOptions(FrameNode* frameNode, NavigationTitlebarOptions&& opt);
    static void SetMenuItems(FrameNode* frameNode, std::vector<NG::BarItem>&& menuItems);
    static void SetMenuItemAction(FrameNode* frameNode, std::function<void()>&& action, uint32_t index);
    static void SetMenuItemSymbol(FrameNode* frameNode,
        std::function<void(WeakPtr<NG::FrameNode>)>&& symbol, uint32_t index);
    static void SetCustomTitle(FrameNode* frameNode, const RefPtr<AceType>& customNode);
    static RefPtr<FrameNode> GetCustomTitle(FrameNode* frameNode);
    static void SetTitleHeight(FrameNode* frameNode, const Dimension& height, bool isValid = true);
    static void SetOnCoordScrollStartAction(FrameNode* frameNode, std::function<void()>&& onCoordScrollStart);
    static void SetOnCoordScrollUpdateAction(
        FrameNode* frameNode, std::function<void(float, float)>&& onCoordScrollUpdate);
    static void SetOnCoordScrollEndAction(FrameNode* frameNode, std::function<void()>&& onCoordScrollEnd);
    static void SetSystemBarStyle(FrameNode* frameNode, const RefPtr<SystemBarStyle>& style);
    static bool IsDoubleBindBlock(const RefPtr<NavigationPattern>& navigationPattern);
    static void SetOnNavigationModeChange(FrameNode* frameNode, std::function<void(NG::NavigationMode)>&& onModeChange);
    static void SetOnTitleModeChange(FrameNode* frameNode,
        std::function<void(NG::NavigationTitleMode)>&& onTitleModeChange,
        std::function<void(const BaseEventInfo* baseInfo)>&& eventInfo);
    static void SetIsCustomAnimation(FrameNode* frameNode, bool isCustom);
    static void SetToolBarItems(FrameNode* frameNode, std::vector<NG::BarItem>&& toolBarItems);
    static RefPtr<NG::NavigationStack> GetNavigationStack(FrameNode* frameNode);
    static void SetOnNavBarStateChange(FrameNode* frameNode, std::function<void(bool)>&& onNavBarStateChange);
    static CalcDimension ParseTitleHeight(
        const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& resObj);
    static void ResetResObj(FrameNode* frameNode, NavigationPatternType type, const std::string& key);
    static void SetIsCustomTitleBarSize(FrameNode* frameNode, bool isCustom);
    static void SetBeforeCreateLayoutWrapperCallBack(
        FrameNode* frameNode, std::function<void()>&& beforeCreateLayoutWrapper);
    virtual bool UseHomeDestination() const override;
    virtual void SetHomePathInfoWithCallback(
        std::function<void(const RefPtr<NavigationStack>&)>&& setHomePathInfoCallback) override;
    void SetEnableShowHideWithContentCover(bool isEnable) override;
    static void SetEnableShowHideWithContentCover(FrameNode* frameNode, bool isEnable);

private:
    bool CreatePrimaryContentIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode);
    bool CreateForceSplitPlaceHolderIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode);
    bool CreateNavBarNodeIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode);
    bool CreateNavBarNodeChildsIfNeeded(const RefPtr<NavBarNode>& navBarNode);
    bool CreateContentNodeIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode);
    bool CreateDividerNodeIfNeeded(const RefPtr<NavigationGroupNode>& navigationGroupNode);
    static void SetHideNavBarInner(const RefPtr<NavigationGroupNode>& navigationGroupNode, bool hideNavBar);
    static bool CreateBackButtonNode(RefPtr<FrameNode>& backButtonNode);
    static bool UpdateBackButtonProperty(const RefPtr<FrameNode>& backButtonNode);
    void SetToolbarNavigationMode(NavigationMode mode); // Only used for the toolbar in 'container_modal' component
    static bool navBarWidthDoubleBind_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_MODEL_NG_H
