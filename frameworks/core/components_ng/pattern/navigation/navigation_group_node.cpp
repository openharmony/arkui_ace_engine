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

#include "core/components_ng/pattern/navigation/navigation_group_node.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<NavigationGroupNode> NavigationGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN_NOLOG(!frameNode, AceType::DynamicCast<NavigationGroupNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto navigationGroupNode = AceType::MakeRefPtr<NavigationGroupNode>(tag, nodeId, pattern);
    navigationGroupNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(navigationGroupNode);
    return navigationGroupNode;
}

void NavigationGroupNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    auto navBar = AceType::DynamicCast<NavBarNode>(GetNavBarNode());
    CHECK_NULL_VOID(navBar);
    auto contentNode = navBar->GetNavBarContentNode();
    if (!contentNode) {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        contentNode = FrameNode::GetOrCreateFrameNode(
            V2::NAVBAR_CONTENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        navBar->SetNavBarContentNode(contentNode);
        auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        navBar->AddChild(contentNode);
    }
    contentNode->AddChild(child);
}

void NavigationGroupNode::AddNavDestinationToNavigation(const RefPtr<UINode>& parent)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    auto navDestinationNodes = pattern->GetAllNavDestinationNodes();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_VOID(navigationNode);
    auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);
    auto navigationStack = pattern->GetNavigationStack();
    for (auto iter = navDestinationNodes.rbegin(); iter != navDestinationNodes.rend(); ++iter) {
        const auto& childNode = *iter;
        auto uiNode = childNode.second;
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(uiNode));
        navigationContentNode->AddChild(navDestination);
    }
}

void NavigationGroupNode::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    FrameNode::ToJsonValue(json);
    auto navBarNode = DynamicCast<NavBarNode>(GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    navBarNode->ToJsonValue(json);
}

RefPtr<UINode> NavigationGroupNode::GetNavDestinationNode(RefPtr<UINode> uiNode)
{
    // create NavDestinationNode from uiNode stored in NavigationStack
    while (uiNode) {
        if (AceType::DynamicCast<FrameNode>(uiNode) && uiNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            // this is a navDesination node
            return AceType::DynamicCast<NavDestinationGroupNode>(uiNode);
        }
        if (AceType::DynamicCast<UINode>(uiNode)) {
            // this is an UINode, go deep further for navDestination node
            auto children = uiNode->GetChildren();
            uiNode = children.front();
            continue;
        }
    }
    // this is an invalid node, just display blank content
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StackPattern>(); });
    auto stackLayoutProperty = frameNode->GetLayoutProperty();
    stackLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    uiNode = AceType::DynamicCast<UINode>(frameNode);
    return uiNode;
}
} // namespace OHOS::Ace::NG
