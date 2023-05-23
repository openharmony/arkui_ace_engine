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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVROUTER_GROUP_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVROUTER_GROUP_NODE_H

#include <cstdint>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navrouter/navrouter_pattern.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavRouterGroupNode : public GroupNode {
    DECLARE_ACE_TYPE(NavRouterGroupNode, GroupNode)
public:
    NavRouterGroupNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : GroupNode(tag, nodeId, pattern)
    {}
    ~NavRouterGroupNode() override = default;
    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    void DeleteChildFromGroup(int32_t slot = DEFAULT_NODE_SLOT) override;
    static RefPtr<NavRouterGroupNode> GetOrCreateGroupNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    bool IsAtomicNode() const override
    {
        return false;
    }

    void SetNavDestinationNode(const RefPtr<UINode>& navDestinationNode)
    {
        navDestinationNode_ = navDestinationNode;
    }

    const RefPtr<UINode>& GetNavDestinationNode() const
    {
        // get the NavDestinationNode which is the child of the NavRouter
        return navDestinationNode_;
    }

    void OnDetachFromMainTree(bool recursive) override;
    void OnAttachToMainTree(bool recursive) override;

private:
    void AddNavDestinationToNavigation(const RefPtr<UINode>& parent);
    void SetDestinationChangeEvent(const RefPtr<UINode>& parent);
    void SetBackButtonEvent(const RefPtr<UINode>& parent);
    void SetOnStateChangeFalse(const RefPtr<UINode>& preNavDestination, const RefPtr<UINode>& navDestination,
        const RefPtr<UINode>& navigation, bool isBackButton = false);
    void BackToNavBar(const RefPtr<UINode>& parent);
    void BackToPreNavDestination(const RefPtr<UINode>& preNavDestination, const RefPtr<UINode>& navigation,
        const RefPtr<NavRouterPattern>& navRouterPattern);
    void AddBackButtonIconToNavDestination(const RefPtr<UINode>& parent);
    bool CleanNodeInNavigation(const RefPtr<UINode>& parent);
    void SetBackButtonVisible(const RefPtr<UINode>& navDestination);
    void GetOpsForNavRouteMode(NavRouteMode mode, bool& stackOp, bool& mapOp);

    void NavTransitionInAnimation(const RefPtr<FrameNode>& navigationNode,
        const RefPtr<FrameNode>& transitionOutNode, const RefPtr<FrameNode>& navDestination);
    void NavTransitionOutAnimation(const RefPtr<UINode>& navigationNode, const RefPtr<FrameNode>& navBarNode,
        const RefPtr<FrameNode>& navDestination, const RefPtr<FrameNode>& navigationContentNode);
    void NavTransitionBackToPreAnimation(const RefPtr<UINode>& navigationNode, const RefPtr<FrameNode>& preDestination,
        const RefPtr<FrameNode>& curNavDestination, const RefPtr<FrameNode>& navigationContentNode);
    void TitleTransitionInAnimation(const RefPtr<FrameNode>& navigationNode,
        const RefPtr<FrameNode>& titleBarNode, const RefPtr<FrameNode>& destinationTitleBarNode);
    void TitleTransitionOutAnimation(const RefPtr<FrameNode>& navigationNode,
        const RefPtr<FrameNode>& titleBarNode, const RefPtr<FrameNode>& destinationTitleBarNode);
    void BackButtonAnimation(const RefPtr<FrameNode>& backButtonNode, bool isTransitionIn);
    void MaskAnimation(const RefPtr<RenderContext>& transitionOutNodeContext);
    void TitleOpacityAnimation(const RefPtr<RenderContext>& transitionOutNodeContext);
    RefPtr<UINode> navDestinationNode_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVROUTER_GROUP_NODE_H
