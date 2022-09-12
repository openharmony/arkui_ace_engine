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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_GROUP_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_GROUP_NODE_H

#include <cstdint>
#include <list>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

enum class ChildNodeOperation {
    ADD,
    // remove case only used for back button
    REMOVE,
    REPLACE,
    NONE
};
class ACE_EXPORT NavigationGroupNode : public GroupNode {
    DECLARE_ACE_TYPE(NavigationGroupNode, GroupNode)
public:
    NavigationGroupNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : GroupNode(tag, nodeId, pattern)
    {}
    ~NavigationGroupNode() = default;
    void AddChildToGroup(const RefPtr<UINode>& child) override;
    static RefPtr<NavigationGroupNode> GetOrCreateGroupNode(
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

    void SetTitleBarNode(const RefPtr<UINode>& title)
    {
        titleBarNode_ = title;
    }

    const RefPtr<UINode>& GetTitleBarNode() const
    {
        return titleBarNode_;
    }

    void SetContentNode(const RefPtr<UINode>& contentNode)
    {
        contentNode_ = contentNode;
    }

    const RefPtr<UINode>& GetContentNode() const
    {
        return contentNode_;
    }

    void SetToolBarNode(const RefPtr<UINode>& toolBarNode)
    {
        toolBarNode_ = toolBarNode;
    }

    const RefPtr<UINode>& GetToolBarNode() const
    {
        return toolBarNode_;
    }

    // title bar children
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(BackButtonIndex, int32_t);
    void OnBackButtonIndexUpdate(int32_t value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TitleIndex, int32_t);
    void OnTitleIndexUpdate(int32_t value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(SubtitleIndex, int32_t);
    void OnSubtitleIndexUpdate(int32_t value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(MenuIndex, int32_t);
    void OnMenuIndexUpdate(int32_t value) {}

    // navigation direct children
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TitleBarIndex, int32_t);
    void OnTitleBarIndexUpdate(int32_t value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ContentIndex, int32_t);
    void OnContentIndexUpdate(int32_t value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ToolBarIndex, int32_t);
    void OnToolBarIndexUpdate(int32_t value) {}

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

private:
    RefPtr<UINode> backButton_;
    RefPtr<UINode> title_;
    RefPtr<UINode> subtitle_;
    RefPtr<UINode> menu_;
    RefPtr<UINode> titleBarNode_;
    RefPtr<UINode> contentNode_;
    RefPtr<UINode> toolBarNode_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_GROUP_NODE_H