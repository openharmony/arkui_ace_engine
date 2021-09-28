/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_NAVIGATION_CONTAINER_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_NAVIGATION_CONTAINER_COMPONENT_H

#include "core/components/tab_bar/tab_controller.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace {

struct ToolBarItem {
public:
    ToolBarItem() = default;
    ToolBarItem(const std::string& value, const std::string& icon, const EventMarker& action)
        : value(value), icon(icon), action(action)
    {}
    ~ToolBarItem() = default;

    std::string value;
    std::string icon;
    EventMarker action;
};

struct ACE_EXPORT NavigationDeclaration : public virtual AceType {
    DECLARE_ACE_TYPE(NavigationDeclaration, AceType);

public:
    void SetTitle(const std::string& title)
    {
        title_ = title;
    }
    void SetSubTitle(const std::string& subTitle)
    {
        subTitle_ = subTitle;
    }
    void SetHideBar(bool hide)
    {
        hideBar_ = hide ? HIDE::TRUE : HIDE::FALSE;
    }
    void SetHideBarBackButton(bool hide)
    {
        hideBackButton_ = hide ? HIDE::TRUE : HIDE::FALSE;
    }
    void SetHideToolBar(bool hide)
    {
        hideToolbar_ = hide ? HIDE::TRUE : HIDE::FALSE;
    }
    void AddToolBarItem(const ToolBarItem& item)
    {
        if (item.value.empty() && item.icon.empty()) {
            return;
        }
        toolbarItems_.push_back(item);
    }
    const std::string& GetTitle()
    {
        return title_;
    }
    const std::string& GetSubTitle()
    {
        return subTitle_;
    }

    bool HasNavigationBar()
    {
        return hideBar_ != HIDE::TRUE;
    }
    bool HasBackButton()
    {
        return hideBackButton_ != HIDE::TRUE;
    }
    bool HasToolBar()
    {
        return (hideToolbar_ != HIDE::TRUE) && !toolbarItems_.empty();
    }
    const std::list<ToolBarItem>& GetToolBarItems()
    {
        return toolbarItems_;
    }

    void Append(const RefPtr<NavigationDeclaration>& other);

private:
    enum class HIDE {
        FALSE = 0,
        TRUE,
        UNDEFINED,
    };
    std::string title_;
    std::string subTitle_;
    HIDE hideBar_ = HIDE::UNDEFINED;
    HIDE hideBackButton_ = HIDE::UNDEFINED;
    std::list<ToolBarItem> toolbarItems_;
    HIDE hideToolbar_ = HIDE::UNDEFINED;
};

class NavigationDeclarationCollector : public Component {
    DECLARE_ACE_TYPE(NavigationDeclarationCollector, Component);

public:
    RefPtr<Element> CreateElement() override
    {
        return nullptr;
    }
    void CollectTo(const RefPtr<NavigationDeclaration>& declaration)
    {
        declaration->Append(declaration_);
    }
    RefPtr<NavigationDeclaration> GetDeclaration()
    {
        return declaration_;
    }
    void SetDeclaration(const RefPtr<NavigationDeclaration>& declaration)
    {
        declaration_ = declaration;
    }

private:
    RefPtr<NavigationDeclaration> declaration_;
};

class ACE_EXPORT NavigationContainerComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(NavigationContainerComponent, ComponentGroup);

public:
    NavigationContainerComponent() : declaration_(AceType::MakeRefPtr<NavigationDeclaration>()) {}
    NavigationContainerComponent(const RefPtr<Component>& navigationbar, const RefPtr<Component>& content)
        : ComponentGroup()
    {
        ComponentGroup::AppendChild(navigationbar);
        ComponentGroup::AppendChild(content);
    }
    ~NavigationContainerComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    static uint32_t GetGlobalTabControllerId();
    RefPtr<TabController> GetTabController()
    {
        return tabController_;
    }
    RefPtr<NavigationDeclaration> GetDeclaration()
    {
        return declaration_;
    }
    void Build();

private:
    RefPtr<Component> BuildNavigationBar() const;
    RefPtr<Component> BuildTabBar();
    bool NeedSection() const;

    RefPtr<NavigationDeclaration> declaration_;
    RefPtr<TabController> tabController_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_NAVIGATION_CONTAINER_COMPONENT_H
