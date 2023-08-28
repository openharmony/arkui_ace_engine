/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_NODE_H

#include <cstdint>
#include <list>

#include "core/animation/page_transition_common.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavBarNode : public GroupNode {
    DECLARE_ACE_TYPE(NavBarNode, GroupNode)
public:
    NavBarNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern) : GroupNode(tag, nodeId, pattern)
    {}
    ~NavBarNode() override = default;
    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    static RefPtr<NavBarNode> GetOrCreateNavBarNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    bool IsAtomicNode() const override
    {
        return false;
    }
    void SetBackButton(const RefPtr<UINode>& button)
    {
        backButton_ = button;
    }

    const RefPtr<UINode>& GetBackButton() const
    {
        return backButton_;
    }

    void SetTitle(const RefPtr<UINode>& title)
    {
        title_ = title;
    }

    const RefPtr<UINode>& GetTitle() const
    {
        return title_;
    }

    void SetSubtitle(const RefPtr<UINode>& subtitle)
    {
        subtitle_ = subtitle;
    }

    const RefPtr<UINode>& GetSubtitle() const
    {
        return subtitle_;
    }

    void SetMenu(const RefPtr<UINode>& menu)
    {
        menu_ = menu;
    }

    const RefPtr<UINode>& GetMenu() const
    {
        return menu_;
    }

    void SetToolbarContainer(const RefPtr<UINode>& menu)
    {
        toolbarMenu_ = menu;
    }

    const RefPtr<UINode>& GetToolbarContainer() const
    {
        return toolbarMenu_;
    }

    void SetMenuNode(const RefPtr<UINode>& menuNode)
    {
        moreMenuNode_ = menuNode;
    }

    void SetToolbarMenuNode(const RefPtr<UINode>& menuNode)
    {
        toolbarMoreMenuNode_ = menuNode;
    }

    void SetLandscapeMenuNode(const RefPtr<UINode>& moreLandscapeMenuNode)
    {
        moreLandscapeMenuNode_ = moreLandscapeMenuNode;
    }

    void SetLandscapeMenu(const RefPtr<UINode>& menu)
    {
        landscapeMenu_ = menu;
    }

    const RefPtr<UINode>& GetLandscapeMenu() const
    {
        return landscapeMenu_;
    }

    void SetTitleBarNode(const RefPtr<UINode>& title)
    {
        titleBarNode_ = title;
    }

    const RefPtr<UINode>& GetTitleBarNode() const
    {
        return titleBarNode_;
    }

    void SetNavBarContentNode(const RefPtr<UINode>& navBarContentNode)
    {
        navBarContentNode_ = navBarContentNode;
    }

    const RefPtr<UINode>& GetNavBarContentNode() const
    {
        return navBarContentNode_;
    }

    void SetToolBarNode(const RefPtr<UINode>& toolBarNode)
    {
        toolBarNode_ = toolBarNode;
    }

    const RefPtr<UINode>& GetToolBarNode() const
    {
        return toolBarNode_;
    }

    void SetPreToolBarNode(const RefPtr<UINode>& preToolBarNode)
    {
        preToolBarNode_ = preToolBarNode;
    }

    const RefPtr<UINode>& GetPreToolBarNode() const
    {
        return preToolBarNode_;
    }

    void SetToolBarDividerNode(const RefPtr<UINode>& toolBarDividerNode)
    {
        toolBarDividerNode_ = toolBarDividerNode;
    }

    const RefPtr<UINode>& GetToolBarDividerNode() const
    {
        return toolBarDividerNode_;
    }

    void SetNarBarUseToolbarConfiguration(bool isNewToolbar)
    {
        isNewToolbar_ = isNewToolbar;
    }

    bool IsNavbarUseToolbarConfiguration() const
    {
        return isNewToolbar_;
    }

    void SetIsTitleMenuNodeShowing(const bool isTitleMenuNodeShowing)
    {
        isTitleMenuNodeShowing_ = isTitleMenuNodeShowing;
    }

    bool IsTitleMenuNodeShowing() const
    {
        return isTitleMenuNodeShowing_;
    }

    std::string GetTitleString() const;
    std::string GetSubtitleString() const;
    std::string GetBarItemsString(bool isMenu) const;
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    // custom node checking
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PrevTitleIsCustom, bool);
    void OnPrevTitleIsCustomUpdate(bool value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PrevMenuIsCustom, bool);
    void OnPrevMenuIsCustomUpdate(bool value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PrevToolBarIsCustom, bool);
    void OnPrevToolBarIsCustomUpdate(bool value) {}

    // node operation related
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(BackButtonNodeOperation, ChildNodeOperation);
    void OnBackButtonNodeOperationUpdate(ChildNodeOperation value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TitleNodeOperation, ChildNodeOperation);
    void OnTitleNodeOperationUpdate(ChildNodeOperation value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(SubtitleNodeOperation, ChildNodeOperation);
    void OnSubtitleNodeOperationUpdate(ChildNodeOperation value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(MenuNodeOperation, ChildNodeOperation);
    void OnMenuNodeOperationUpdate(ChildNodeOperation value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ToolBarNodeOperation, ChildNodeOperation);
    void OnToolBarNodeOperationUpdate(ChildNodeOperation value) {}

    void SetTransitionType(PageTransitionType type)
    {
        transitionType_ = type;
    }

    PageTransitionType GetTransitionType() const
    {
        return transitionType_;
    }

private:
    RefPtr<UINode> backButton_;
    RefPtr<UINode> title_;
    RefPtr<UINode> subtitle_;
    RefPtr<UINode> menu_;
    RefPtr<UINode> toolbarMenu_;
    RefPtr<UINode> landscapeMenu_;
    RefPtr<UINode> moreMenuNode_;
    RefPtr<UINode> toolbarMoreMenuNode_;
    RefPtr<UINode> moreLandscapeMenuNode_;
    RefPtr<UINode> titleBarNode_;
    RefPtr<UINode> navBarContentNode_;
    RefPtr<UINode> toolBarNode_;
    RefPtr<UINode> preToolBarNode_;
    RefPtr<UINode> toolBarDividerNode_;
    bool isTitleMenuNodeShowing_ = false;
    bool isNewToolbar_ = false;
    PageTransitionType transitionType_ = PageTransitionType::NONE;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_NODE_H
