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

#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
namespace {
std::string GetNavigationId(const RefPtr<NavDestinationPattern>& pattern)
{
    CHECK_NULL_RETURN(pattern, "");
    return pattern->GetNavigationId();
}

int32_t GetNavigationUniqueId(const RefPtr<NavDestinationPattern>& pattern)
{
    auto uniqueId = -1;
    CHECK_NULL_RETURN(pattern, uniqueId);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(pattern->GetNavigationNode());
    CHECK_NULL_RETURN(navigationNode, uniqueId);
    auto navigationUniqueId = navigationNode->GetId();
    return navigationUniqueId;
}
} // namespace

UIObserverHandler& UIObserverHandler::GetInstance()
{
    static UIObserverHandler instance;
    return instance;
}

void UIObserverHandler::NotifyNavigationStateChange(const WeakPtr<AceType>& weakPattern, NavDestinationState state)
{
    CHECK_NULL_VOID(navigationHandleFunc_);
    auto ref = weakPattern.Upgrade();
    CHECK_NULL_VOID(ref);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(ref);
    CHECK_NULL_VOID(pattern);
    auto context = pattern->GetNavDestinationContext();
    CHECK_NULL_VOID(context);
    auto pathInfo = pattern->GetNavPathInfo();
    CHECK_NULL_VOID(pathInfo);
    auto host = AceType::DynamicCast<NavDestinationGroupNode>(pattern->GetHost());
    CHECK_NULL_VOID(host);
    NavDestinationMode mode = host->GetNavDestinationMode();
    auto uniqueId = host->GetId();
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        if (state == NavDestinationState::ON_SHOWN || state == NavDestinationState::ON_HIDDEN) {
            NavDestinationInfo info(GetNavigationId(pattern), pattern->GetName(), state);
            navigationHandleFunc_(info);
        }
        return;
    }
    // api 16 trigger onActive and onInactive observer
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SEVENTEEN) && (
        state == NavDestinationState::ON_ACTIVE || state == NavDestinationState::ON_INACTIVE)) {
        return;
    }
    pathInfo->OpenScope();
    NavDestinationInfo info(GetNavigationId(pattern), pattern->GetName(), state, context->GetIndex(),
        pathInfo->GetParamObj(), std::to_string(pattern->GetNavDestinationId()), mode, uniqueId,
        GetNavigationUniqueId(pattern));
    navigationHandleFunc_(info);
    pathInfo->CloseScope();
}

void UIObserverHandler::NotifyScrollEventStateChange(const WeakPtr<AceType>& weakPattern, ScrollEventType eventType)
{
    auto ref = weakPattern.Upgrade();
    CHECK_NULL_VOID(ref);
    auto pattern = AceType::DynamicCast<ScrollablePattern>(ref);
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    if (eventType == ScrollEventType::SCROLL_START) {
        host->AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_START_SCROLL);
    } else if (eventType == ScrollEventType::SCROLL_STOP) {
        host->AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_END_SCROLL);
    }
    std::string id = host->GetInspectorId().value_or("");
    int32_t uniqueId = host->GetId();
    float offset = pattern->GetTotalOffset();
    Ace::Axis axis = pattern->GetAxis();
    CHECK_NULL_VOID(scrollEventHandleFunc_);
    scrollEventHandleFunc_(id, uniqueId, eventType, offset, axis);
}

void UIObserverHandler::NotifyRouterPageStateChange(const RefPtr<PageInfo>& pageInfo, RouterPageState state)
{
    CHECK_NULL_VOID(pageInfo);
    CHECK_NULL_VOID(routerPageHandleFunc_);
    auto container = Container::Current();
    if (!container) {
        LOGW("notify router event failed, current UI instance invalid");
        return;
    }
    napi_value context = GetUIContextValue();
    AbilityContextInfo info = {
        AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(),
        container->GetModuleName()
    };
    int32_t index = pageInfo->GetPageIndex();
    std::string name = pageInfo->GetPageUrl();
    std::string path = pageInfo->GetPagePath();
    std::string pageId = std::to_string(pageInfo->GetPageId());
    RouterPageInfoNG routerPageInfo(context, index, name, path, state, pageId);
    routerPageHandleFunc_(info, routerPageInfo);
}

void UIObserverHandler::NotifyDensityChange(double density)
{
    CHECK_NULL_VOID(densityHandleFunc_);
    auto container = Container::Current();
    if (!container) {
        LOGW("notify density event failed, current UI instance invalid");
        return;
    }
    AbilityContextInfo info = {
        AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(),
        container->GetModuleName()
    };
    densityHandleFunc_(info, density);
}

void UIObserverHandler::NotifyWillClick(
    const GestureEvent& gestureEventInfo, const ClickInfo& clickInfo, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(willClickHandleFunc_);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    AbilityContextInfo info = {
        AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(),
        container->GetModuleName()
    };
    willClickHandleFunc_(info, gestureEventInfo, clickInfo, frameNode);
}

void UIObserverHandler::NotifyDidClick(
    const GestureEvent& gestureEventInfo, const ClickInfo& clickInfo, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(didClickHandleFunc_);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    AbilityContextInfo info = {
        AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(),
        container->GetModuleName()
    };
    didClickHandleFunc_(info, gestureEventInfo, clickInfo, frameNode);
}

void UIObserverHandler::NotifyPanGestureStateChange(const GestureEvent& gestureEventInfo,
    const RefPtr<PanRecognizer>& current, const RefPtr<FrameNode>& frameNode, const PanGestureInfo& panGestureInfo)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(panGestureHandleFunc_);
    auto getCurrent = Container::Current();
    CHECK_NULL_VOID(getCurrent);
    AbilityContextInfo info = { AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(), getCurrent->GetModuleName() };

    panGestureHandleFunc_(info, gestureEventInfo, current, frameNode, panGestureInfo);
}

void UIObserverHandler::NotifyGestureStateChange(NG::GestureListenerType gestureListenerType,
    const GestureEvent& gestureEventInfo, const RefPtr<NGGestureRecognizer>& current,
    const RefPtr<FrameNode>& frameNode, NG::GestureActionPhase phase)
{
    CHECK_NULL_VOID(current);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(gestureHandleFunc_);

    gestureHandleFunc_(gestureListenerType, gestureEventInfo, current, frameNode, phase);
}

void UIObserverHandler::NotifyTabContentStateUpdate(const TabContentInfo& info)
{
    CHECK_NULL_VOID(tabContentStateHandleFunc_);
    tabContentStateHandleFunc_(info);
}

UIObserverHandler::NavDestinationSwitchHandleFunc UIObserverHandler::GetHandleNavDestinationSwitchFunc()
{
    return navDestinationSwitchHandleFunc_;
}

std::shared_ptr<NavDestinationInfo> UIObserverHandler::GetNavDestinationInfo(const RefPtr<UINode>& current)
{
    auto nav = AceType::DynamicCast<FrameNode>(current);
    CHECK_NULL_RETURN(nav, nullptr);
    auto pattern = nav->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto host = AceType::DynamicCast<NavDestinationGroupNode>(pattern->GetHost());
    CHECK_NULL_RETURN(host, nullptr);
    auto pathInfo = pattern->GetNavPathInfo();
    CHECK_NULL_RETURN(pathInfo, nullptr);
    NavDestinationState state = NavDestinationState::NONE;
    NavDestinationMode mode = host->GetNavDestinationMode();
    auto uniqueId = host->GetId();
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        state = pattern->GetNavDestinationState();
        if (state == NavDestinationState::NONE) {
            return nullptr;
        }
    } else {
        state = pattern->GetIsOnShow() ? NavDestinationState::ON_SHOWN : NavDestinationState::ON_HIDDEN;
    }
    return std::make_shared<NavDestinationInfo>(
        GetNavigationId(pattern), pattern->GetName(),
        state, host->GetIndex(), pathInfo->GetParamObj(), std::to_string(pattern->GetNavDestinationId()),
        mode, uniqueId);
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
    return GetNavDestinationInfo(current);
}

std::shared_ptr<NavDestinationInfo> UIObserverHandler::GetNavigationInnerState(const RefPtr<AceType>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto current = AceType::DynamicCast<UINode>(node);
    while (current) {
        if (current->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG &&
            current->GetParent()->GetTag() == V2::NAVIGATION_CONTENT_ETS_TAG) {
            break;
        }
        current = current->GetFirstChild();
    }
    CHECK_NULL_RETURN(current, nullptr);
    return GetNavDestinationInfo(current);
}

std::shared_ptr<NavDestinationInfo> UIObserverHandler::GetNavigationOuterState(const RefPtr<AceType>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto current = AceType::DynamicCast<UINode>(node);
    while (current) {
        CHECK_NULL_RETURN(current->GetParent(), nullptr);
        if (current->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG &&
            current->GetParent()->GetTag() == V2::NAVIGATION_CONTENT_ETS_TAG) {
            break;
        }
        current = current->GetParent();
    }
    CHECK_NULL_RETURN(current, nullptr);
    return GetNavDestinationInfo(current);
}

std::shared_ptr<ScrollEventInfo> UIObserverHandler::GetScrollEventState(const RefPtr<AceType>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto current = AceType::DynamicCast<UINode>(node);
    while (current) {
        if (current->GetTag() == V2::SCROLL_ETS_TAG) {
            break;
        }
        current = current->GetParent();
    }
    CHECK_NULL_RETURN(current, nullptr);
    auto nav = AceType::DynamicCast<FrameNode>(current);
    CHECK_NULL_RETURN(nav, nullptr);
    std::string id = nav->GetInspectorId().value_or("");
    int32_t uniqueId = nav->GetId();
    auto pattern = nav->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return std::make_shared<ScrollEventInfo>(
        id,
        uniqueId,
        ScrollEventType::SCROLL_START,
        pattern->GetTotalOffset(),
        pattern->GetAxis());
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
    int32_t index = pageInfo->GetPageIndex();
    std::string name = pageInfo->GetPageUrl();
    std::string path = pageInfo->GetPagePath();
    std::string pageId = std::to_string(pageInfo->GetPageId());
    return std::make_shared<RouterPageInfoNG>(
        GetUIContextValue(),
        index,
        name,
        path,
        RouterPageState(pattern->GetPageState()),
        pageId);
}

void UIObserverHandler::HandleDrawCommandSendCallBack()
{
    CHECK_NULL_VOID(drawCommandSendHandleFunc_);
    ACE_LAYOUT_SCOPED_TRACE("drawCommandSend");
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [callback = drawCommandSendHandleFunc_] { callback(); },
        TaskExecutor::TaskType::JS, "ArkUIObserverDrawCommandSend");
}

void UIObserverHandler::HandleLayoutDoneCallBack()
{
    CHECK_NULL_VOID(layoutDoneHandleFunc_);
    ACE_LAYOUT_SCOPED_TRACE("layoutDone");
    layoutDoneHandleFunc_();
}

void UIObserverHandler::NotifyNavDestinationSwitch(std::optional<NavDestinationInfo>&& from,
    std::optional<NavDestinationInfo>&& to, NavigationOperation operation)
{
    CHECK_NULL_VOID(navDestinationSwitchHandleFunc_);
    auto container = Container::Current();
    if (!container) {
        LOGW("notify destination event failed, current UI instance invalid");
        return;
    }
    AbilityContextInfo info = {
        AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(),
        container->GetModuleName()
    };
    NavDestinationSwitchInfo switchInfo(GetUIContextValue(), std::forward<std::optional<NavDestinationInfo>>(from),
        std::forward<std::optional<NavDestinationInfo>>(to), operation);
    navDestinationSwitchHandleFunc_(info, switchInfo);
}

void UIObserverHandler::SetHandleNavigationChangeFunc(NavigationHandleFunc func)
{
    navigationHandleFunc_ = func;
}

void UIObserverHandler::SetHandleScrollEventChangeFunc(ScrollEventHandleFunc func)
{
    scrollEventHandleFunc_ = func;
}

void UIObserverHandler::SetHandleRouterPageChangeFunc(RouterPageHandleFunc func)
{
    routerPageHandleFunc_ = func;
}

void UIObserverHandler::SetHandleDensityChangeFunc(DensityHandleFunc func)
{
    densityHandleFunc_ = func;
}

void UIObserverHandler::SetDrawCommandSendHandleFunc(DrawCommandSendHandleFunc func)
{
    drawCommandSendHandleFunc_ = func;
}

void UIObserverHandler::SetLayoutDoneHandleFunc(LayoutDoneHandleFunc func)
{
    layoutDoneHandleFunc_ = func;
}

void UIObserverHandler::SetHandleNavDestinationSwitchFunc(NavDestinationSwitchHandleFunc func)
{
    navDestinationSwitchHandleFunc_ = func;
}

void UIObserverHandler::SetWillClickFunc(WillClickHandleFunc func)
{
    willClickHandleFunc_ = func;
}

void UIObserverHandler::SetDidClickFunc(DidClickHandleFunc func)
{
    didClickHandleFunc_ = func;
}

void UIObserverHandler::SetPanGestureHandleFunc(PanGestureHandleFunc func)
{
    panGestureHandleFunc_ = func;
}

void UIObserverHandler::SetHandleGestureHandleFunc(GestureHandleFunc func)
{
    gestureHandleFunc_ = func;
}

void UIObserverHandler::SetHandleTabContentStateUpdateFunc(TabContentStateHandleFunc func)
{
    tabContentStateHandleFunc_ = func;
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
