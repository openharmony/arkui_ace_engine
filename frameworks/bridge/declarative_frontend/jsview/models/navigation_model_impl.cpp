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

#include "bridge/declarative_frontend/jsview/models/navigation_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void NavigationModelImpl::Create(bool useHomeDestination)
{
    auto navigationContainer = AceType::MakeRefPtr<NavigationContainerComponent>();
    ViewStackProcessor::GetInstance()->Push(navigationContainer);
}

void NavigationModelImpl::SetTitle(const std::string& title, bool hasSubTitle)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    CHECK_NULL_VOID(navigationContainer);
    navigationContainer->GetDeclaration()->title = title;
}

void NavigationModelImpl::SetCustomTitle(const RefPtr<AceType>& customTitle)
{
    auto customTile = AceType::DynamicCast<Component>(customTitle);
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (!navigationContainer) {
    LOGI("component is not navigationContainer.");
    return;
    }
#if defined(PREVIEW)
    auto composedComponent =
        ViewStackProcessor::GetInstance()->CreateInspectorWrapper("NavigationTitle");
    composedComponent->SetChild(customTile);
    navigationContainer->GetDeclaration()->customTitle = composedComponent;
#else
    navigationContainer->GetDeclaration()->customTitle = customTile;
#endif
}

void NavigationModelImpl::SetTitleHeight(const Dimension& height, bool isValid)
{
    return;
}

void NavigationModelImpl::SetTitleMode(NG::NavigationTitleMode mode)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (!navigationContainer) {
        LOGI("component is not navigationContainer.");
        return;
    }
    navigationContainer->GetDeclaration()->titleMode = static_cast<NavigationTitleMode>(mode);
}

void NavigationModelImpl::SetSubtitle(const std::string& subtitle)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (!navigationContainer) {
        LOGI("component is not navigationContainer.");
        return;
    }
    navigationContainer->GetDeclaration()->subTitle = subtitle;
}

void NavigationModelImpl::SetEnableModeChangeAnimation(bool isEnable)
{
    return;
}

void NavigationModelImpl::SetHideTitleBar(bool hideTitleBar, bool animated)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (!navigationContainer) {
        LOGI("component is not navigationContainer.");
        return;
    }
    auto declaration = navigationContainer->GetDeclaration();
    declaration->hideBar = hideTitleBar;
    declaration->animationOption = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
}

void NavigationModelImpl::SetHideNavBar(bool hideNavBar)
{
    return;
}

void NavigationModelImpl::SetBackButtonIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
    const std::string& src, const NG::ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
    const std::vector<std::string>& nameList, bool userDefinedAccessibilityText,
    const std::string& backButtonAccessibilityText)
{
    return;
}

void NavigationModelImpl::SetBackButtonIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
    const RefPtr<ResourceObject>& resObj, const NG::ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
    const std::vector<std::string>& nameList, bool userDefinedAccessibilityText,
    const std::string& backButtonAccessibilityText)
{
    return;
}

void NavigationModelImpl::SetBackButtonIconTextRes(const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
    const std::string& src, const NG::ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
    const std::vector<std::string>& nameList, bool userDefinedAccessibilityText, const RefPtr<ResourceObject>& resObj)
{
    return;
}

void NavigationModelImpl::SetBackButtonIconSrcAndTextRes(
    const std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply,
    const RefPtr<ResourceObject>& backButtonResObj, const NG::ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
    const std::vector<std::string>& nameList, bool userDefinedAccessibilityText,
    const RefPtr<ResourceObject>& backButtonTextResObj)
{
    return;
}

void NavigationModelImpl::UpdateBackButtonIcon(const std::vector<std::string>& nameList,
    NG::FrameNode* frameNode, const RefPtr<ResourceObject>& backButtonIconResObj)
{
    return;
}

void NavigationModelImpl::UpdateBackButtonIconText(bool userDefinedAccessibilityText,
    const RefPtr<NG::TitleBarNode>& titleBarNode, const RefPtr<ResourceObject>& backButtonTextResObj)
{
    return;
}

void NavigationModelImpl::SetHideBackButton(bool hideBackButton)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (!navigationContainer) {
        LOGI("component is not navigationContainer.");
        return;
    }
    navigationContainer->GetDeclaration()->hideBarBackButton = hideBackButton;
}

void NavigationModelImpl::SetHideToolBar(bool hideToolBar, bool animated)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (!navigationContainer) {
        LOGI("component is not navigationContainer.");
        return;
    }
    auto declaration = navigationContainer->GetDeclaration();
    declaration->hideToolbar = hideToolBar;
    declaration->animationOption = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
}

void NavigationModelImpl::SetCustomToolBar(const RefPtr<AceType>& node)
{
    auto customToolBar = AceType::DynamicCast<Component>(node);
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (!navigationContainer) {
        LOGI("component is not navigationContainer.");
        return;
    }
    navigationContainer->GetDeclaration()->toolBarBuilder = customToolBar;
}

bool NavigationModelImpl::NeedSetItems()
{
    return false;
}

void NavigationModelImpl::SetToolBarItems(std::vector<NG::BarItem>&& toolBarItems)
{
    return;
}

void NavigationModelImpl::SetToolbarConfiguration(std::vector<NG::BarItem>&& toolBarItems) {}

void NavigationModelImpl::GetToolBarItems(std::list<RefPtr<AceType>>& items)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    CHECK_NULL_VOID(navigationContainer);
    auto toolbarItems = navigationContainer->GetDeclaration()->toolbarItems;
    items.clear();
    for (auto item : toolbarItems) {
        items.push_back(item);
    }
}

void NavigationModelImpl::SetMenuItems(std::vector<NG::BarItem>&& menuItems)
{
    return;
}

void NavigationModelImpl::GetMenuItems(std::list<RefPtr<AceType>>& items)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    CHECK_NULL_VOID(navigationContainer);
    auto toolbarItems = navigationContainer->GetDeclaration()->menuItems;
    items.clear();
    for (auto item : toolbarItems) {
        items.push_back(item);
    }
}

void NavigationModelImpl::SetCustomMenu(const RefPtr<AceType>& customMenu)
{
    auto customMenus = AceType::DynamicCast<Component>(customMenu);
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (!navigationContainer) {
        LOGI("component is not navigationContainer.");
        return;
    }
#if defined(PREVIEW)
    auto composedComponent = ViewStackProcessor::GetInstance()->CreateInspectorWrapper("NavigationMenus");
    composedComponent->SetChild(customMenus);
    navigationContainer->GetDeclaration()->customMenus = composedComponent;
#else
    navigationContainer->GetDeclaration()->customMenus = customMenus;
#endif
}

void NavigationModelImpl::SetOnTitleModeChange(std::function<void(NG::NavigationTitleMode)>&& onTitleModeChange,
    std::function<void(const BaseEventInfo* baseInfo)>&& eventInfo)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    auto eventMarker = EventMarker(std::move(eventInfo));
    if (navigationContainer) {
        navigationContainer->GetDeclaration()->titleModeChangedEvent = eventMarker;
    }
}

void NavigationModelImpl::SetUsrNavigationMode(NG::NavigationMode mode)
{
    return;
}

void NavigationModelImpl::SetNavBarPosition(NG::NavBarPosition mode)
{
    return;
}

void NavigationModelImpl::SetNavBarWidth(const Dimension& value, bool isDoubleBind)
{
    return;
}

void NavigationModelImpl::SetOnNavBarStateChange(std::function<void(bool)>&& onNavBarStateChange)
{
    return;
}

void NavigationModelImpl::SetOnNavigationModeChange(std::function<void(NG::NavigationMode)>&& onNavigationChange)
{
    return;
}

void NavigationModelImpl::SetNavigationMode(NG::NavigationMode mode)
{
    return;
}

void NavigationModelImpl::SetNavigationStack()
{
    return;
}

void NavigationModelImpl::SetNavigationStack(const RefPtr<NG::NavigationStack>& navigationStack)
{
    return;
}

void NavigationModelImpl::SetNavigationStackProvided(bool provided)
{
    return;
}

void NavigationModelImpl::SetNavDestination(std::function<void(std::string)>&& builder)
{
    return;
}

RefPtr<NG::NavigationStack> NavigationModelImpl::GetNavigationStack()
{
    return nullptr;
}

void NavigationModelImpl::SetMenuCount(int32_t menuCount)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (navigationContainer) {
        navigationContainer->SetMenuCount(menuCount);
    }
}

void NavigationModelImpl::SetCustomTransition(NavigationTransitionEvent&& animationTransition) {}

void NavigationModelImpl::SetIsCustomAnimation(bool isCustom) {}

void NavigationModelImpl::SetIgnoreLayoutSafeArea(const NG::IgnoreLayoutSafeAreaOpts& opts) {}
} // namespace OHOS::Ace::Framework
