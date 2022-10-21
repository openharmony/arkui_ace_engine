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
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavigationGroupNode : public GroupNode {
    DECLARE_ACE_TYPE(NavigationGroupNode, GroupNode)
public:
    NavigationGroupNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : GroupNode(tag, nodeId, pattern)
    {}
    ~NavigationGroupNode() override = default;
    void AddChildToGroup(const RefPtr<UINode>& child) override;
    static RefPtr<NavigationGroupNode> GetOrCreateGroupNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    bool IsAtomicNode() const override
    {
        return false;
    }

    void SetNavBarNode(const RefPtr<UINode>& navBarNode)
    {
        navBarNode_ = navBarNode;
    }

    const RefPtr<UINode>& GetNavBarNode() const
    {
        return navBarNode_;
    }

    void SetContentNode(const RefPtr<UINode>& contentNode)
    {
        contentNode_ = contentNode;
    }

    const RefPtr<UINode>& GetContentNode() const
    {
        return contentNode_;
    }

    void SetDividerNode(const RefPtr<UINode>& dividerNode)
    {
        dividerNode_ = dividerNode;
    }

    const RefPtr<UINode>& GetDividerNode() const
    {
        return dividerNode_;
    }

private:
    void AddNavDestinationToNavigation(const RefPtr<UINode>& child);
    void BackToPreNavDestination(const RefPtr<UINode>& child);

    RefPtr<UINode> navBarNode_;
    RefPtr<UINode> contentNode_;
    RefPtr<UINode> dividerNode_;
    bool isFirstNavDestination_ = true;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_GROUP_NODE_H