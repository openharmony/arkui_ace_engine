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

#include "core/components_ng/pattern/navigation/navigation_pattern.h"

#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"

namespace OHOS::Ace::NG {

constexpr int32_t NAVIMODE_CHANGE_ANIMATION_DURATION = 250;
constexpr int32_t OPACITY_ANIMATION_DURATION_APPEAR = 150;
constexpr int32_t OPACITY_ANIMATION_DURATION_DISAPPEAR = 250;

namespace {

void MountNavBar(const RefPtr<NavigationGroupNode>& hostNode)
{
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    navBarNode->MarkModifyDone();
}

} // namespace

RefPtr<RenderContext> NavigationPattern::GetTitleBarRenderContext()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto contentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    CHECK_NULL_RETURN(contentNode, nullptr);
    if (layoutProperty->GetDestinationChange().value_or(false) ||
        contentNode->FindChildNodeOfClass<NavDestinationGroupNode>()) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
        CHECK_NULL_RETURN(navBarNode, nullptr);
        auto renderContext = navBarNode->GetRenderContext();
        return renderContext;
    } else {
        auto renderContext = contentNode->GetRenderContext();
        return renderContext;
    }
}

void NavigationPattern::DoAnimation(NavigationMode currentMode)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto usrNavigationMode = layoutProperty->GetUsrNavigationModeValue(NavigationMode::AUTO);

    auto lastMode = navigationMode_;
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    layoutProperty->UpdateUsrNavigationMode(lastMode);
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    AnimationOption option = AnimationOption();
    option.SetDuration(NAVIMODE_CHANGE_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationOption optionAlpha = AnimationOption();
    optionAlpha.SetCurve(Curves::SHARP);
    optionAlpha.SetFillMode(FillMode::FORWARDS);
    auto renderContext = GetTitleBarRenderContext();
    CHECK_NULL_VOID(renderContext);

    context->OpenImplicitAnimation(option, option.GetCurve(), nullptr);
    layoutProperty->UpdateUsrNavigationMode(currentMode);
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    if (currentMode == NavigationMode::STACK || lastMode == NavigationMode::SPLIT) {
        optionAlpha.SetDuration(OPACITY_ANIMATION_DURATION_DISAPPEAR);
        renderContext->OpacityAnimation(optionAlpha, 1, 0);
    } else if (currentMode == NavigationMode::SPLIT || lastMode == NavigationMode::STACK) {
        optionAlpha.SetDuration(OPACITY_ANIMATION_DURATION_APPEAR);
        renderContext->OpacityAnimation(optionAlpha, 0, 1);
    }
    context->CloseImplicitAnimation();
    layoutProperty->UpdateUsrNavigationMode(usrNavigationMode);
}

void NavigationPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    MountNavBar(hostNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    navBarNode->MarkModifyDone();
    auto preTopNavPath = GetTopNavPath();
    if (!navPathList_.empty()) {
        navPathList_.clear();
    }

    auto pathNames = navigationStack_->GetAllPathName();
    for (size_t i = 0; i < pathNames.size(); ++i) {
        auto pathName = pathNames[i];
        RefPtr<UINode> uiNode = navigationStack_->Get(pathName);
        navigationStack_->RemoveInNavPathList(pathName, uiNode);
        if (uiNode) {
            navPathList_.emplace_back(std::make_pair(pathName, uiNode));
            continue;
        }
        if (CheckExistPreStack(pathName)) {
            uiNode = GetNodeAndRemoveByName(pathName);
        } else {
            uiNode = GenerateUINodeByIndex(static_cast<int32_t>(i));
        }

        navPathList_.emplace_back(std::make_pair(pathName, uiNode));
    }

    navigationStack_->SetNavPathList(navPathList_);
    auto contentNode = hostNode->GetContentNode();
    contentNode->Clean();
    hostNode->AddNavDestinationToNavigation();

    auto newTopNavPath = GetTopNavPath();
    if (preTopNavPath != newTopNavPath) {
        // fire onHidden event
        if (preTopNavPath.second != nullptr) {
            auto preTop = preTopNavPath.second;
            auto preTopNavDestination =
                AceType::DynamicCast<NavDestinationGroupNode>(NavigationGroupNode::GetNavDestinationNode(preTop));
            auto eventHub = preTopNavDestination->GetEventHub<NavDestinationEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireOnHiddenEvent();
            auto focusHub = AceType::DynamicCast<FrameNode>(preTopNavDestination)->GetFocusHub();
            CHECK_NULL_VOID(focusHub);
            focusHub->SetParentFocusable(false);
            focusHub->LostFocus();
        }

        // fire onShown event
        if (newTopNavPath.second != nullptr) {
            auto newTop = newTopNavPath.second;
            auto newTopNavDestination =
                AceType::DynamicCast<NavDestinationGroupNode>(NavigationGroupNode::GetNavDestinationNode(newTop));
            auto eventHub = newTopNavDestination->GetEventHub<NavDestinationEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireOnShownEvent();
            auto focusHub = AceType::DynamicCast<FrameNode>(newTopNavDestination)->GetFocusHub();
            CHECK_NULL_VOID(focusHub);
            focusHub->SetParentFocusable(true);
            focusHub->RequestFocus();
        }

        auto navigationLayoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
        CHECK_NULL_VOID(navigationLayoutProperty);
        if (navigationLayoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::STACK &&
            newTopNavPath.second != nullptr) {
            auto preTopNavDestination = navBarNode;
            if (preTopNavPath.second != nullptr) {
                auto preTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
                    NavigationGroupNode::GetNavDestinationNode(preTopNavPath.second));
            }
            auto newTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
                NavigationGroupNode::GetNavDestinationNode(newTopNavPath.second));
            auto curNavTitleBarNode = AceType::DynamicCast<TitleBarNode>(preTopNavDestination->GetTitleBarNode());
            auto destinationTitleBarNode = AceType::DynamicCast<TitleBarNode>(newTopNavDestination->GetTitleBarNode());
            auto backButtonNode = AceType::DynamicCast<FrameNode>(destinationTitleBarNode->GetBackButton());
            if (curNavTitleBarNode || destinationTitleBarNode) {
                hostNode->TitleTransitionInAnimation(curNavTitleBarNode, destinationTitleBarNode);
            }
            if (backButtonNode) {
                hostNode->BackButtonAnimation(backButtonNode, true);
            }
            hostNode->NavTransitionInAnimation(preTopNavDestination, newTopNavDestination);
        }
    }

    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto currentMode = layoutProperty->GetUsrNavigationModeValue(NavigationMode::AUTO);
    if (currentMode != NavigationMode::AUTO && navigationMode_ != currentMode &&
        navigationMode_ != NavigationMode::AUTO) {
        hostNode->SetIsModeChange(true);
        DoAnimation(currentMode);
    }
    preNavPathList_ = navPathList_;
}

bool NavigationPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto navigationLayoutAlgorithm =
        DynamicCast<NavigationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(navigationLayoutAlgorithm, false);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(hostNode->GetLayoutProperty());
    CHECK_NULL_RETURN(navigationLayoutProperty, false);
    if (config.frameSizeChange) {
        if (navigationLayoutProperty->GetUsrNavigationModeValue(NavigationMode::AUTO) == NavigationMode::AUTO) {
            auto currentMode = navigationLayoutAlgorithm->GetNavigationMode();
            if (navigationMode_ != NavigationMode::AUTO && navigationMode_ != currentMode) {
                hostNode->SetIsModeChange(true);
                DoAnimation(currentMode);
            }
            navigationMode_ = currentMode;
        }
    }
    navigationLayoutProperty->UpdateNavigationMode(navigationLayoutAlgorithm->GetNavigationMode());

    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
    CHECK_NULL_RETURN(navBarNode, false);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_RETURN(navBarLayoutProperty, false);
    auto eventHub = hostNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (navigationLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
        eventHub->FireNavBarStateChangeEvent(false);
    } else {
        if (navigationLayoutAlgorithm->GetNavigationMode() == NavigationMode::SPLIT) {
            if (navigationLayoutProperty->GetHideNavBar().value_or(false)) {
                navBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
                eventHub->FireNavBarStateChangeEvent(false);
            } else {
                navBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
                eventHub->FireNavBarStateChangeEvent(true);
            }
        }
    }
    return false;
}

bool NavigationPattern::CheckExistPreStack(const std::string& name)
{
    return std::any_of(preNavPathList_.begin(), preNavPathList_.end(),
        [&](const std::pair<std::string, RefPtr<UINode>>& preNamePair) { return preNamePair.first == name; });
}

RefPtr<UINode> NavigationPattern::GetNodeAndRemoveByName(const std::string& name)
{
    RefPtr<UINode> uiNode;
    // match from bottom to top
    for (auto iter = preNavPathList_.begin(); iter != preNavPathList_.end(); iter++) {
        if (iter->first == name) {
            uiNode = iter->second;
            preNavPathList_.erase(iter);
            break;
        }
    }

    return uiNode;
}

RefPtr<UINode> NavigationPattern::GenerateUINodeByIndex(int32_t index)
{
    return navigationStack_->CreateNodeByIndex(index);
}

} // namespace OHOS::Ace::NG
