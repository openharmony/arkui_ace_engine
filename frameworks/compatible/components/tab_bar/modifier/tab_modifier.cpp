/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "compatible/components/tab_bar/dom/dom_tab_bar.h"
#include "compatible/components/tab_bar/modifier/tab_modifier_api.h"
#include "compatible/components/tab_bar/v2/tabs_helper.h"

#include "base/memory/ace_type.h"
#include "core/components_v2/common/element_proxy.h"
#include "core/pipeline/base/component.h"
#include "core/pipeline/base/element.h"

namespace OHOS::Ace::TabModifier {

void BindToTabs(RefPtr<Framework::DOMNode> targetNode, const RefPtr<Framework::DOMNode>& tabsNode)
{
    if (AceType::InstanceOf<Framework::DOMTabBar>(targetNode)) {
        auto tabBarNode = AceType::DynamicCast<Framework::DOMTabBar>(targetNode);
        // DOMTabBar in navigation bar bind tabs with ID node
        tabBarNode->BindToTabs(tabsNode);
    }
}

bool IsTabsComponent(const RefPtr<Component>& component)
{
    return AceType::DynamicCast<V2::TabsComponent>(component) != nullptr;
}

RefPtr<Component> GetTabContentItemComponent(const RefPtr<Component>& component)
{
    return V2::TabsHelper::TraverseComponentTo<V2::TabContentItemComponent>(component);
}

void RemoveTabBarItemById(const RefPtr<Component>& component)
{
    auto tabContentItemComponent = AceType::DynamicCast<V2::TabContentItemComponent>(component);
    CHECK_NULL_VOID(tabContentItemComponent);
    V2::TabsHelper::RemoveTabBarItemById(tabContentItemComponent->GetBarElementId());
}

RefPtr<Element> GetTabContentProxyElement(const RefPtr<V2::ElementProxyHost>& hostProxy)
{
    CHECK_NULL_RETURN(hostProxy, nullptr);
    return AceType::DynamicCast<V2::TabContentProxyElement>(hostProxy);
}

void DecTabContentRenderCount(const RefPtr<V2::ElementProxyHost>& hostProxy)
{
    CHECK_NULL_VOID(hostProxy);
    auto tabContentProxyElement = AceType::DynamicCast<V2::TabContentProxyElement>(hostProxy);
    CHECK_NULL_VOID(tabContentProxyElement);
    V2::TabsHelper::DecTabContentRenderCount(tabContentProxyElement);
}

bool SetRealElementId(const RefPtr<Component>& component, int32_t elementId)
{
    auto tabContentItemComponent = V2::TabsHelper::TraverseComponentTo<V2::TabContentItemComponent>(component);
    CHECK_NULL_RETURN(tabContentItemComponent, false);
    tabContentItemComponent->SetElementId(elementId);
    return true;
}

bool RestoreElementId(const RefPtr<Component>& component, int32_t elementId)
{
    auto tabContentItemComponent = V2::TabsHelper::TraverseComponentTo<V2::TabContentItemComponent>(component);
    CHECK_NULL_RETURN(tabContentItemComponent, false);
    tabContentItemComponent->SetElementId(elementId);
    return true;
}

bool TryGetTabContentItemElementId(const RefPtr<Component>& component, int32_t& outId)
{
    auto tabContentItemComponent = V2::TabsHelper::TraverseComponentTo<V2::TabContentItemComponent>(component);
    CHECK_NULL_RETURN(tabContentItemComponent, false);
    outId = tabContentItemComponent->GetElementId();
    return true;
}

void AddTabBarItem(
    const WeakPtr<V2::ElementProxyHost>& host, const RefPtr<Element>& element, const RefPtr<Component>& component)
{
    auto hostProxy = host.Upgrade();
    CHECK_NULL_VOID(hostProxy);
    auto tabContentProxyElement = AceType::DynamicCast<V2::TabContentProxyElement>(hostProxy);
    if (tabContentProxyElement && !element) {
        auto tabContentItemComponent = V2::TabsHelper::TraverseComponentTo<V2::TabContentItemComponent>(component);
        V2::TabsHelper::AddTabBarElement(tabContentProxyElement, tabContentItemComponent);
        V2::TabsHelper::IncTabContentRenderCount(tabContentProxyElement);
    }
}

void UpdateTabBarElement(const WeakPtr<V2::ElementProxyHost>& host, const RefPtr<Element>& element,
    const RefPtr<Component>& component, const RefPtr<Component>& inwardWrappingComponent)
{
    auto hostProxy = host.Upgrade();
    CHECK_NULL_VOID(hostProxy);
    auto tabContentProxyElement = AceType::DynamicCast<V2::TabContentProxyElement>(hostProxy);
    CHECK_NULL_VOID(tabContentProxyElement);
    auto tabContentItemComponent =
        V2::TabsHelper::TraverseComponentTo<V2::TabContentItemComponent>(inwardWrappingComponent);
    auto oldComponent = V2::TabsHelper::TraverseComponentTo<V2::TabContentItemComponent>(component);
    CHECK_NULL_VOID(oldComponent);
    tabContentItemComponent->SetBarElementId(oldComponent->GetBarElementId());
    V2::TabsHelper::UpdateTabBarElement(tabContentProxyElement, element, inwardWrappingComponent);
}

void SetTabBarElementIndex(const RefPtr<Element>& element, const RefPtr<Component>& component, size_t index)
{
    V2::TabsHelper::SetTabBarElementIndex(
        element, V2::TabsHelper::TraverseComponentTo<V2::TabContentItemComponent>(component), index);
}

bool IsTabContentItemComponent(const RefPtr<Component>& component)
{
    return V2::TabsHelper::TraverseComponentTo<V2::TabContentItemComponent>(component) != nullptr;
}

RefPtr<Component> GetTabBarComponent(const RefPtr<Component>& component)
{
    return AceType::DynamicCast<TabBarComponent>(component);
}

RefPtr<Component> CreateTabBarItem(const RefPtr<Component>& child)
{
    return AceType::MakeRefPtr<TabBarItemComponent>(child);
}

RefPtr<Component> CreateTabBar(const std::list<RefPtr<Component>>& tabItems, const RefPtr<AceType>& controller)
{
    CHECK_NULL_RETURN(controller, nullptr);
    auto tabController = AceType::DynamicCast<TabController>(controller);
    CHECK_NULL_RETURN(tabController, nullptr);
    return AceType::MakeRefPtr<TabBarComponent>(tabItems, tabController);
}

void InitNavigationBarStyle(const RefPtr<Component>& component)
{
    auto tabBar = AceType::DynamicCast<TabBarComponent>(component);
    CHECK_NULL_VOID(tabBar);
    tabBar->InitNavigationBarStyle();
}

void InitBottomTabStyle(const RefPtr<Component>& component, const RefPtr<TabTheme>& theme)
{
    auto tabBar = AceType::DynamicCast<TabBarComponent>(component);
    CHECK_NULL_VOID(tabBar);
    tabBar->InitBottomTabStyle(theme);
}

RefPtr<AceType> GetController(int32_t controllerId)
{
    return TabController::GetController(controllerId);
}

void SetIndexByController(const RefPtr<AceType>& controller, int32_t index, bool blockEvent = true)
{
    CHECK_NULL_VOID(controller);
    auto tabController = AceType::DynamicCast<TabController>(controller);
    CHECK_NULL_VOID(tabController);
    tabController->SetIndexByController(index, blockEvent);
}

void SetInitialIndex(const RefPtr<AceType>& controller, int32_t index)
{
    CHECK_NULL_VOID(controller);
    auto tabController = AceType::DynamicCast<TabController>(controller);
    CHECK_NULL_VOID(tabController);
    tabController->SetInitialIndex(index);
}

void SetTabBarChangeListener(const RefPtr<AceType>& controller, const TabBarChangeListener& listener)
{
    CHECK_NULL_VOID(controller);
    auto tabController = AceType::DynamicCast<TabController>(controller);
    CHECK_NULL_VOID(tabController);
    tabController->SetTabBarChangeListener(listener);
}

const ArkUIInnerTabsModifier* GetTabsInnerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIInnerTabsModifier impl = {
        .isTabsComponent = IsTabsComponent,
        .getController = GetController,
        .setIndexByController = SetIndexByController,
        .setInitialIndex = SetInitialIndex,
        .setTabBarChangeListener = SetTabBarChangeListener,
    };
    CHECK_INITIALIZED_FIELDS_END(impl, 0, 0, 0); // don't move this line
    return &impl;
}

const ArkUIInnerTabBarModifier* GetTabBarInnerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIInnerTabBarModifier impl = {
        .bindToTabs = BindToTabs,
        .getTabBarComponent = GetTabBarComponent,
        .createTabBarItem = CreateTabBarItem,
        .createTabBar = CreateTabBar,
        .initNavigationBarStyle = InitNavigationBarStyle,
        .initBottomTabStyle = InitBottomTabStyle,
    };
    CHECK_INITIALIZED_FIELDS_END(impl, 0, 0, 0); // don't move this line
    return &impl;
}

const ArkUITabContentModifier* GetTabContentInnerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITabContentModifier impl = {
        .getTabContentItemComponent = GetTabContentItemComponent,
        .removeTabBarItemById = RemoveTabBarItemById,
        .getTabContentProxyElement = GetTabContentProxyElement,
        .decTabContentRenderCount = DecTabContentRenderCount,
        .setRealElementId = SetRealElementId,
        .tryGetTabContentItemElementId = TryGetTabContentItemElementId,
        .addTabBarItem = AddTabBarItem,
        .updateTabBarElement = UpdateTabBarElement,
        .setTabBarElementIndex = SetTabBarElementIndex,
        .isTabContentItemComponent = IsTabContentItemComponent,
    };
    CHECK_INITIALIZED_FIELDS_END(impl, 0, 0, 0); // don't move this line
    return &impl;
}
} // namespace OHOS::Ace::TabModifier
