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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_GROUP_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_GROUP_NODE_H

#include <cstdint>
#include <list>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

using NavDestinationBackButtonEvent = std::function<void(GestureEvent&)>;

class ACE_EXPORT NavDestinationGroupNode : public GroupNode {
    DECLARE_ACE_TYPE(NavDestinationGroupNode, GroupNode)
public:
    NavDestinationGroupNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : GroupNode(tag, nodeId, pattern)
    {}
    ~NavDestinationGroupNode() override = default;
    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    void DeleteChildFromGroup(int32_t slot = DEFAULT_NODE_SLOT) override;
    static RefPtr<NavDestinationGroupNode> GetOrCreateGroupNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

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

    void SetNavDestinationBackButtonEvent(const NavDestinationBackButtonEvent& backButtonEvent)
    {
        backButtonEvent_ = backButtonEvent;
    }

    NavDestinationBackButtonEvent GetNavDestinationBackButtonEvent() const
    {
        return backButtonEvent_;
    }

    // custom node checking
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PrevTitleIsCustom, bool);
    void OnPrevTitleIsCustomUpdate(bool value) {}

    // node operation related
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TitleNodeOperation, ChildNodeOperation);
    void OnTitleNodeOperationUpdate(ChildNodeOperation value) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(SubtitleNodeOperation, ChildNodeOperation);
    void OnSubtitleNodeOperationUpdate(ChildNodeOperation value) {}

    void OnAttachToMainTree(bool recursive) override;

    void OnOffscreenProcess(bool recursive) override;

    void ProcessShallowBuilder();

    void UpdateTitleFontSize(bool showBackButton);

    void SetTransitionType(PageTransitionType type)
    {
        transitionType_ = type;
    }

    PageTransitionType GetTransitionType() const
    {
        return transitionType_;
    }

private:
    RefPtr<UINode> title_;
    RefPtr<UINode> subtitle_;
    RefPtr<UINode> titleBarNode_;
    RefPtr<UINode> contentNode_;
    NavDestinationBackButtonEvent backButtonEvent_;

    PageTransitionType transitionType_ = PageTransitionType::NONE;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_GROUP_NODE_H
