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

#ifndef FRAMEWORKS_COMPATIBLE_COMPONENTS_TAB_BAR_MODIFIER_TAB_MODIFIER_API_H
#define FRAMEWORKS_COMPATIBLE_COMPONENTS_TAB_BAR_MODIFIER_TAB_MODIFIER_API_H

#include <cstdint>
#include <list>

#include "base/memory/ace_type.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace OHOS::Ace {
class Element;
class Component;
class TabController;
class TabTheme;
using TabBarChangeListener = std::function<void(int32_t)>;

namespace Framework {
class DOMNode;
class JSLazyForEachComponent;
} // namespace Framework

namespace V2 {
class ElementProxyHost;
class ElementProxy;
} // namespace V2

struct ArkUIInnerTabsModifier {
    bool (*isTabsComponent)(const RefPtr<Component>& component);
    RefPtr<AceType> (*getController)(int32_t controllerId);
    void (*setIndexByController)(const RefPtr<AceType>& controller, int32_t index, bool blockEvent);
    void (*setInitialIndex)(const RefPtr<AceType>& controller, int32_t index);
    void (*setTabBarChangeListener)(const RefPtr<AceType>& controller, const TabBarChangeListener& listener);
};

struct ArkUIInnerTabBarModifier {
    void (*bindToTabs)(RefPtr<Framework::DOMNode> targetNode, const RefPtr<Framework::DOMNode>& tabsNode);
    RefPtr<Component> (*getTabBarComponent)(const RefPtr<Component>& component);
    RefPtr<Component> (*createTabBarItem)(const RefPtr<Component>& child);
    RefPtr<Component> (*createTabBar)(
        const std::list<RefPtr<Component>>& tabItems, const RefPtr<AceType>& controller);
    void (*initNavigationBarStyle)(const RefPtr<Component>& component);
    void (*initBottomTabStyle)(const RefPtr<Component>& component, const RefPtr<TabTheme>& theme);
};

struct ArkUITabContentModifier {
    RefPtr<Component> (*getTabContentItemComponent)(const RefPtr<Component>& component);
    void (*removeTabBarItemById)(const RefPtr<Component>& component);
    RefPtr<Element> (*getTabContentProxyElement)(const RefPtr<V2::ElementProxyHost>& hostProxy);
    void (*decTabContentRenderCount)(const RefPtr<V2::ElementProxyHost>& hostProxy);
    bool (*setRealElementId)(const RefPtr<Component>& component, int32_t elementId);
    bool (*tryGetTabContentItemElementId)(const RefPtr<Component>& component, int32_t& outId);
    void (*addTabBarItem)(
        const WeakPtr<V2::ElementProxyHost>& host, const RefPtr<Element>& element, const RefPtr<Component>& component);
    void (*updateTabBarElement)(const WeakPtr<V2::ElementProxyHost>& host, const RefPtr<Element>& element,
        const RefPtr<Component>& component, const RefPtr<Component>& inwardWrappingComponent);
    void (*setTabBarElementIndex)(const RefPtr<Element>& element, const RefPtr<Component>& component, size_t index);
    bool (*isTabContentItemComponent)(const RefPtr<Component>& component);
};
} // namespace OHOS::Ace

#ifdef __cplusplus
};
#endif

#endif // FRAMEWORKS_COMPATIBLE_COMPONENTS_TAB_BAR_MODIFIER_TAB_MODIFIER_API_H
