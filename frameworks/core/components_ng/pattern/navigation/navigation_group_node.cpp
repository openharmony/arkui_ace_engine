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
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<NavigationGroupNode> NavigationGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    if (frameNode) {
        return AceType::DynamicCast<NavigationGroupNode>(frameNode);
    }
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto navigationGroupNode = AceType::MakeRefPtr<NavigationGroupNode>(tag, nodeId, pattern);
    navigationGroupNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(navigationGroupNode);
    return navigationGroupNode;
}

void NavigationGroupNode::AddChildToGroup(const RefPtr<UINode>& child)
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

    auto onDestinationChange = [child = child, navigation = this]() {
        navigation->AddNavDestinationToNavigation(child);
    };
    auto navRouter = AceType::DynamicCast<NavRouterGroupNode>(child);
    CHECK_NULL_VOID(navRouter);
    auto eventHub = navRouter->GetEventHub<NavRouterEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDestinationChange(std::move(onDestinationChange));

    if (isFirstNavDestination_) {
        AddNavDestinationToNavigation(child);
        isFirstNavDestination_ = false;
    }

    // set back button event
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navRouter->GetNavDestinationNode());
    CHECK_NULL_VOID(navDestination);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonEventHub = backButtonNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(backButtonEventHub);
    auto onBackButtonEvent = [navDestination = navDestination, navigation = this](GestureEvent& /*info*/) {
        if (navDestination->GetPreNode()) {
            navigation->BackToPreNavDestination(navDestination->GetPreNode());
        }
    };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(onBackButtonEvent));
    backButtonEventHub->GetOrCreateGestureEventHub()->AddClickEvent(clickEvent);
}

void NavigationGroupNode::AddNavDestinationToNavigation(const RefPtr<UINode>& child)
{
    auto navRouter = AceType::DynamicCast<NavRouterGroupNode>(child);
    CHECK_NULL_VOID(navRouter);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navRouter->GetNavDestinationNode());
    if (navDestination) {
        auto navigationContentNode = GetContentNode();
        if (!navigationContentNode) {
            auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
            navigationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
                nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
            SetContentNode(navigationContentNode);
            auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            AddChild(navigationContentNode);
        }

        const auto& children = navigationContentNode->GetChildren();
        for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
            const auto& childNode = *iter;
            auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(childNode);
            if (navDestinationNode) {
                navDestination->SetPreNode(navDestinationNode);
                break;
            }
        }

        navigationContentNode->Clean();
        navigationContentNode->AddChild(navDestination);
        navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void NavigationGroupNode::BackToPreNavDestination(const RefPtr<UINode>& child)
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(child);
    if (navDestination) {
        auto navigationContentNode = GetContentNode();
        CHECK_NULL_VOID(navigationContentNode);
        navigationContentNode->Clean();
        navigationContentNode->AddChild(navDestination);
        navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

} // namespace OHOS::Ace::NG