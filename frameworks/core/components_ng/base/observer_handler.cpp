/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/observer_handler.h"

#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

namespace OHOS::Ace::NG {
namespace {
std::string GetNavigationId(const RefPtr<NavDestinationPattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, "");
    auto navigationNode = pattern->GetNavigationNode();
    std::string navigationId;
    if (navigationNode) {
        navigationId = navigationNode->GetInspectorId().value_or("");
    }
    return navigationId;
}
} // namespace

UIObserverHandler& UIObserverHandler::GetInstance()
{
    static UIObserverHandler instance;
    return instance;
}

void UIObserverHandler::NotifyNavigationStateChange(const WeakPtr<AceType>& weakPattern, NavDestinationState state)
{
    auto ref = weakPattern.Upgrade();
    CHECK_NULL_VOID(ref);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(ref);
    CHECK_NULL_VOID(pattern);
    std::string navigationId = GetNavigationId(pattern);
    std::string navDestinationName = pattern->GetName();
    CHECK_NULL_VOID(navigationHandleFunc_);
    navigationHandleFunc_(navigationId, navDestinationName, state);
}

void UIObserverHandler::NotifyRouterPageStateChange(const RefPtr<PageInfo>& pageInfo, RouterPageState state)
{
    CHECK_NULL_VOID(pageInfo);
    CHECK_NULL_VOID(routerPageHandleFunc_);
    napi_value context = GetUIContextValue();
    AbilityContextInfo info = {
        AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(),
        Container::Current()->GetModuleName()
    };
    std::string name = pageInfo->GetPageUrl();
    std::string path = pageInfo->GetPagePath();
    int32_t index = EngineHelper::GetCurrentDelegate()->GetIndexByUrl(name);
    routerPageHandleFunc_(info, context, index, name, path, state);
}

std::shared_ptr<NavDestinationInfo> UIObserverHandler::GetNavigationState(const RefPtr<AceType>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto current = AceType::DynamicCast<UINode>(node);
    while (current) {
        if (current->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            break;
        }
        current = current->GetParent();
    }
    CHECK_NULL_RETURN(current, nullptr);
    auto nav = AceType::DynamicCast<FrameNode>(current);
    CHECK_NULL_RETURN(nav, nullptr);
    auto pattern = nav->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return std::make_shared<NavDestinationInfo>(
        GetNavigationId(pattern),
        pattern->GetName(),
        pattern->GetIsOnShow() ? NavDestinationState::ON_SHOWN : NavDestinationState::ON_HIDDEN);
}

std::shared_ptr<RouterPageInfoNG> UIObserverHandler::GetRouterPageState(const RefPtr<AceType>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto current = AceType::DynamicCast<UINode>(node);
    while (current) {
        if (current->GetTag() == V2::PAGE_ETS_TAG) {
            break;
        }
        current = current->GetParent();
    }
    CHECK_NULL_RETURN(current, nullptr);
    auto routerPage = AceType::DynamicCast<FrameNode>(current);
    CHECK_NULL_RETURN(routerPage, nullptr);
    auto pattern = routerPage->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto pageInfo = pattern->GetPageInfo();
    std::string name = pageInfo->GetPageUrl();
    std::string path = pageInfo->GetPagePath();
    int32_t index = EngineHelper::GetCurrentDelegate()->GetIndexByUrl(name);
    return std::make_shared<RouterPageInfoNG>(
        GetUIContextValue(),
        index,
        name,
        path,
        RouterPageState(pattern->GetPageState()));
}

void UIObserverHandler::SetHandleNavigationChangeFunc(NavigationHandleFunc func)
{
    navigationHandleFunc_ = func;
}

void UIObserverHandler::SetHandleRouterPageChangeFunc(RouterPageHandleFunc func)
{
    routerPageHandleFunc_ = func;
}

napi_value UIObserverHandler::GetUIContextValue()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, nullptr);
    return frontend->GetContextValue();
}
} // namespace OHOS::Ace::NG
