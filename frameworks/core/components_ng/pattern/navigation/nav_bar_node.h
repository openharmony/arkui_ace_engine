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
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT NavBarNode : public NavDestinationNodeBase {
    DECLARE_ACE_TYPE(NavBarNode, NavDestinationNodeBase)
public:
    NavBarNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : NavDestinationNodeBase(tag, nodeId, pattern) {}
    ~NavBarNode() override = default;
    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    static RefPtr<NavBarNode> GetOrCreateNavBarNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    void InitSystemTransitionPush(bool transitionIn = false) override;
    void EndSystemTransitionPush(bool transitionIn = false) override;
    void InitSystemTransitionPop(bool transitionIn = true) override;
    void EndSystemTransitionPop(bool transitionIn = true) override;
    void FinishSystemTransitionPush();
    bool IsNodeInvisible(const RefPtr<FrameNode>& node) override;
    void FinishSystemTransitionAnimationPush(RefPtr<FrameNode>& preNode, RefPtr<FrameNode>& naviagtionNode,
        bool transitionIn, const int32_t animationId) override;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_NODE_H
