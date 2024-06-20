/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_TABS_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_TABS_HELPER_H

#include "core/components/tab_bar/render_tab_bar.h"
#include "core/components/tab_bar/render_tab_content.h"
#include "core/components/tab_bar/tab_bar_element.h"
#include "core/components/tab_bar/tab_content_element.h"
#include "core/components_v2/tabs/tab_content_item_component.h"
#include "core/components_v2/tabs/tab_content_item_element.h"
#include "core/components_v2/tabs/tab_content_proxy_element.h"
#include "core/components_v2/tabs/tabs_element.h"

namespace OHOS::Ace::V2 {
    /*
    Stucture of Tabs components:

    <Box>
        <TabBar>
            <TabBarIndicator>
            </TabBarIndicator>
        </TabBar>
    </Box>

    // Last child (or first if tab bar is at the end)
    <FlexItem>
        <TabContent>
        </TabContent>
    </FlexItem>

    TabsElement
        FlexItemElement
            TabContentProxyElement
                BoxElement
                    TabContentItemElement


    first child BoxElement
    last  child FlexItemElement

    if TabBar positioned at the .End, order reversed:

    first child FlexItemElement
    last child BoxElement

    */

const int32_t INVALID_TAB_BAR_INDEX = -1;

class TabsHelper {
public:
    template<class T>
    static RefPtr<Element> FindFirstChildOfType(const RefPtr<Element>& parent)
    {
        if (AceType::InstanceOf<T>(parent)) {
            return parent;
        }
        for (const auto& child : parent->GetChildren()) {
            const auto foundTypedChild = FindFirstChildOfType<T>(child);
            if (foundTypedChild) {
                return foundTypedChild;
            }
        }
        return nullptr;
    }

    template<class T>
    static std::tuple<RefPtr<Element>, RefPtr<Element>> FindFirstParentOfType(const RefPtr<Element>& child)
    {
        RefPtr<Element> parentElement = nullptr;
        auto currentElement = child;
        while (currentElement && (parentElement = currentElement->GetElementParent().Upgrade())) {
            if (AceType::InstanceOf<T>(parentElement)) {
                return {parentElement, currentElement};
            }
            currentElement = parentElement;
            parentElement = nullptr;
        }
        return {nullptr, nullptr};
    }

    template<class T>
    static RefPtr<T> TraverseComponentTo(const RefPtr<Component>& component)
    {
        if (!component) {
            LOGE("null component");
            return nullptr;
        }

        if (AceType::InstanceOf<T>(component)) {
            return AceType::DynamicCast<T>(component);
        }

        auto single = AceType::DynamicCast<SingleChild>(component);

        if (single) {
            return TraverseComponentTo<T>(single->GetChild());
        }
        return nullptr;
    }

    static RefPtr<TabsElement> FindTabsElement(const RefPtr<Element>& child)
    {
        return AceType::DynamicCast<TabsElement>(std::get<0>(TabsHelper::FindFirstParentOfType<TabsElement>(child)));
    }

    static RefPtr<TabBarElement> FindTabBarElement(const RefPtr<Element>& child)
    {
        auto tabsElement = FindTabsElement(child);
        if (tabsElement == nullptr) {
            LOGE("nullptr tabsElement");
            return nullptr;
        }
        auto tabBarElement = TabsHelper::FindFirstChildOfType<TabBarElement>(tabsElement);
        return AceType::DynamicCast<TabBarElement>(tabBarElement);
    }

    static RefPtr<TabContentElement> FindTabContentElement(const RefPtr<Element>& child)
    {
        // Go up to the parent to find Tabs
        auto tabsElement = FindTabsElement(child);
        if (tabsElement == nullptr) {
            LOGE("nullptr tabsElement");
            return nullptr;
        }

        // TabsElement
        //    FlexItemElement
        //       TabContentProxyElement
        return AceType::DynamicCast<TabContentElement>(FindFirstChildOfType<TabContentElement>(tabsElement));
    }

    static void RemoveTabBarItemById(ElementIdType id)
    {
        auto tabBarItemChild = ElementRegister::GetInstance()->GetElementById(id);
        if (!tabBarItemChild) {
            return;
        }

        auto parent = FindFirstParentOfType<TabBarElement>(tabBarItemChild);
        if (std::get<0>(parent) && std::get<1>(parent)) {
            auto tabBarElement = std::get<0>(parent);
            auto tabBarItemElement = std::get<1>(parent);

            // Update current focused index
            AceType::DynamicCast<RenderTabBar>(tabBarElement->GetRenderNode())->
                AboutToRemove(tabBarItemElement->GetRenderNode());
            tabBarElement->UpdateChild(tabBarItemElement, nullptr);
        }
    }

    static void AddTabBarElement(const RefPtr<Element>& host,
        const RefPtr<TabContentItemComponent>& tabContentItemComponent)
    {
        auto tabsElement = FindTabsElement(host);
        if (!tabsElement) {
            LOGE("TabsElement is null");
            return;
        }

        // tabBar is nullptr for initial render if tab tab positioned at the .End
        // In case if tab bar is missing we keep TabBarItemComponent(s) in memory
        // and attach them at the end of TabsElement::PerformBuild execution.
        auto tabBar = TabsHelper::FindTabBarElement(host);

        RefPtr<TabBarItemComponent> newBarItemComponent;

        if (tabContentItemComponent && tabContentItemComponent->HasBarBuilder()) {
            newBarItemComponent = AceType::MakeRefPtr<TabBarItemComponent>(
                tabContentItemComponent->ExecuteBarBuilder());
        } else if (tabContentItemComponent) {
            newBarItemComponent = AceType::MakeRefPtr<TabBarItemComponent>(
                TabBarItemComponent::BuildWithTextIcon(
                    tabContentItemComponent->GetBarText(), tabContentItemComponent->GetBarIcon()));
        }

        // Link tab item and Tab bar item with id
        const auto id = ElementRegister::GetInstance()->MakeUniqueId();
        newBarItemComponent->SetElementId(id);

        if (tabContentItemComponent) {
            tabContentItemComponent->SetBarElementId(id);
        }

        // Add element to TabBar or store component to be added later
        if (tabBar) {
            tabBar->GetTabBarComponent()->UpdateItemStyle(newBarItemComponent);
            tabBar->UpdateChild(nullptr, newBarItemComponent);
        } else {
            tabsElement->AddPendingTabBarItem(newBarItemComponent);
        }
    }

    static void UpdateTabBarElement(const RefPtr<Element>& host, const RefPtr<Element>& contentItemElement,
        const RefPtr<Component>& contentItemComponent)
    {
        auto tabBar = TabsHelper::FindTabBarElement(host);
        if (!tabBar) {
            LOGE("TabBar missing");
            return;
        }

        std::string text;
        std::string icon;
        ElementIdType id;

        auto tabContentItemElement = AceType::DynamicCast<TabContentItemElement>(contentItemElement);
        auto tabContentItemComponent = AceType::DynamicCast<TabContentItemComponent>(contentItemComponent);

        if (tabContentItemElement) {
            text = tabContentItemElement->GetText();
            icon = tabContentItemElement->GetIcon();
            id = tabContentItemElement->GetBarElementId();
        } else if (tabContentItemComponent) {
            text = tabContentItemComponent->GetBarText();
            icon = tabContentItemComponent->GetBarIcon();
            id = tabContentItemComponent->GetBarElementId();
        } else {
            LOGE("Neither Element nor Component provided to build tab menu item");
            return;
        }

        auto newBarItemComponent = AceType::MakeRefPtr<TabBarItemComponent>(
            TabBarItemComponent::BuildWithTextIcon(text, icon));
        tabBar->GetTabBarComponent()->UpdateItemStyle(newBarItemComponent);

        if (tabContentItemComponent && tabContentItemComponent->HasBarBuilder()) {
            newBarItemComponent = AceType::MakeRefPtr<TabBarItemComponent>(
                tabContentItemComponent->ExecuteBarBuilder());
        }

        auto tabBarItemElement = ElementRegister::GetInstance()->GetElementById(id);
        if (!tabBarItemElement) {
            LOGE("tabBarItemElement nullptr");
            return;
        }
        newBarItemComponent->SetElementId(tabBarItemElement->GetElementId());
        tabBar->UpdateChild(tabBarItemElement, newBarItemComponent);
    }

    static void SetTabBarElementIndex(const RefPtr<Element>& contentItemElement,
        const RefPtr<Component>& contentItemComponent, int target)
    {
        ElementIdType elementId = ElementRegister::UndefinedElementId;

        auto tabContentItemElement = AceType::DynamicCast<TabContentItemElement>(contentItemElement);
        auto tabContentItemComponent = AceType::DynamicCast<TabContentItemComponent>(contentItemComponent);

        if (tabContentItemElement) {
            elementId = tabContentItemElement->GetBarElementId();
        } else if (tabContentItemComponent) {
            elementId = tabContentItemComponent->GetBarElementId();
        } else {
            LOGE("Neither Element nor Component provided to build tab menu item");
            return;
        }

        auto tabBarItemElement = ElementRegister::GetInstance()->GetElementById(elementId);
        if (!tabBarItemElement) {
            LOGE("tabBarItemElement is null");
            return;
        }
        auto renderNode = tabBarItemElement->GetRenderNode();
        if (!renderNode) {
            LOGE("renderNode for tabBarItemElement is null");
            return;
        }
        auto renderTabBar = AceType::DynamicCast<RenderTabBar>(renderNode->GetParent().Upgrade());
        if (!renderTabBar) {
            LOGE("renderTabBar is null");
            return;
        }
        renderNode->MovePosition(renderTabBar->FirstItemOffset() + target);
    }

    static void SetIndex(const RefPtr<Element>& element, int32_t idx)
    {
        auto tabBarElement = TabsHelper::FindTabBarElement(element);
        if (tabBarElement) {
            tabBarElement->GetTabController()->SetIndex(idx);
            tabBarElement->UpdateIndex(idx);
        }
    }

    static RefPtr<RenderTabBar> GetTabBarRenderNode(const RefPtr<Element>& proxyHostElement)
    {
        auto tabBar = TabsHelper::FindTabBarElement(proxyHostElement);
        if (!tabBar) {
            LOGE("TabBar is missing");
            return nullptr;
        }
        auto renderTabBar = AceType::DynamicCast<RenderTabBar>(tabBar->GetRenderNode());
        if (!renderTabBar) {
            LOGE("RenderTabBar is missing");
            return nullptr;
        }
        return renderTabBar;
    }

    static int32_t GetTabBarFocusedElementIndex(const RefPtr<Element>& proxyHostElement)
    {
        auto renderTabBar = TabsHelper::GetTabBarRenderNode(proxyHostElement);
        if (!renderTabBar) {
            return INVALID_TAB_BAR_INDEX;
        }
        return renderTabBar->GetFocusedTabBarItemIndex();
    }

    static RefPtr<RenderNode> GetTabBarFocusedElement(const RefPtr<Element>& proxyHostElement)
    {
        auto renderTabBar = TabsHelper::GetTabBarRenderNode(proxyHostElement);
        if (!renderTabBar) {
            return nullptr;
        }
        return renderTabBar->GetFocusedTabBarItem();
    }

    static int32_t GetTabBarElementIndex(const RefPtr<Element>& proxyHostElement, const RefPtr<RenderNode>& child)
    {
        auto renderTabBar = TabsHelper::GetTabBarRenderNode(proxyHostElement);
        if (!renderTabBar) {
            return INVALID_TAB_BAR_INDEX;
        }
        auto idx = renderTabBar->GetIndexForTabBarItem(child);
        return idx;
    }

    static void UpdateRenderTabContentCount(const RefPtr<Element>& element, int32_t count)
    {
        // TODO: ContentCount should be managed by render_tab_content itself
        // element is a TabContentItemElement
        auto tabContent = FindTabContentElement(element);
        auto tabContentProxyElement = AceType::DynamicCast<TabContentProxyElement>(tabContent);

        if (!tabContent || !tabContentProxyElement) {
            LOGE("Getting  tabContent or tabContentProxyElement failed");
            return;
        }

        auto controller = tabContent->GetTabController();
        controller->SetTotalCount(controller->GetTotalCount() + count);

        auto tabContentRenderNode = AceType::DynamicCast<RenderTabContent>(tabContentProxyElement->GetRenderNode());
        if (!tabContentRenderNode) {
            LOGE("GetRenderNode failed");
            return;
        }
        tabContentRenderNode->UpdateContentCount(controller->GetTotalCount());
    }

    static void IncTabContentRenderCount(const RefPtr<Element>& element)
    {
        UpdateRenderTabContentCount(element, 1);
    }

    static void DecTabContentRenderCount(const RefPtr<Element>& element)
    {
        UpdateRenderTabContentCount(element, -1);
    }

    static void DumpComponents(const RefPtr<Component>& component, const std::string& header = "",
        int depth = 4, const std::string& shift = "")
    {
        if (depth == 0) {
            return;
        }

        if (!component) {
            LOGE("null component");
            return;
        }
        auto single = AceType::DynamicCast<SingleChild>(component);

        if (single) {
            DumpComponents(single->GetChild(), "", depth -1, shift + "  ");
        } else {
            auto group = AceType::DynamicCast<ComponentGroup>(component);
            if (group) {
                for (const auto& child : group->GetChildren()) {
                    DumpComponents(child, "", depth -1, shift + "  ");
                }
            }
        }
    }

    // Dump Elemens
    static void DumpElements(const RefPtr<Element>& node,
        const std::string& header = "", int depth = 4, const std::string& shift = "")
    {
        if (depth == 0) {
            return;
        }
        if (!node) {
            LOGE("null element");
            return;
        }
        if (!header.empty()) {
            LOGE("Dumping tree for  %{public}s  %{public}s id: %{public}d",
                AceType::TypeName(node), header.c_str(), node->GetElementId());
        }

        for (const auto& child : node->GetChildren()) {
            TabsHelper::DumpElements(child, "", depth -1, shift + "  ");
        }
    }

    static void PrintRenderNodes(const RefPtr<RenderNode>& renderNode, const std::string& text) {}
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_TABS_HELPER_H
