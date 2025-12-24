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

#include "compatible/components/tab_bar/tab_loader.h"

#include "compatible/components/tab_bar/dom/dom_tab_bar.h"
#include "compatible/components/tab_bar/dom/dom_tab_content.h"
#include "compatible/components/tab_bar/dom/dom_tabs.h"
#include "compatible/components/tab_bar/models/tab_content_model_impl.h"
#include "compatible/components/tab_bar/models/tabs_model_impl.h"
#include "compatible/components/tab_bar/v2/tab_content_composed_element.h"
#include "compatible/components/tab_bar/v2/tabs_composed_element.h"
#include "compatible/components/tab_bar/modifier/tab_modifier.h"

#include "base/memory/ace_type.h"

namespace OHOS::Ace {

RefPtr<Framework::DOMNode> TabsLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMTabs>(nodeId, nodeName);
}

void* TabsLoader::CreateModel()
{
    return new Framework::TabsModelImpl();
}

RefPtr<V2::InspectorComposedElement> TabsLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::TabsComposedElement>(id);
}

const void* TabsLoader::GetCustomModifier(const std::string& tag)
{
    return TabModifier::GetTabsInnerModifier();
}

RefPtr<Framework::DOMNode> TabBarLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMTabBar>(nodeId, nodeName);
}

void* TabBarLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> TabBarLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

const void* TabBarLoader::GetCustomModifier(const std::string& tag)
{
    return TabModifier::GetTabBarInnerModifier();
}

RefPtr<Framework::DOMNode> TabContentLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMTabContent>(nodeId, nodeName);
}

void* TabContentLoader::CreateModel()
{
    return new Framework::TabContentModelImpl();
}

RefPtr<V2::InspectorComposedElement> TabContentLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::TabContentComposedElement>(id);
}

const void* TabContentLoader::GetCustomModifier(const std::string& tag)
{
    return TabModifier::GetTabContentInnerModifier();
}

} // namespace OHOS::Ace
