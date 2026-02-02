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
#include "core/interfaces/native/implementation/gesture_trigger_info_peer.h"

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

std::unordered_map<int32_t, std::map<int32_t, PanListenerCallback>> UIObserverHandler::beforePanStartCallbackMap_;
std::unordered_map<int32_t, std::map<int32_t, PanListenerCallback>> UIObserverHandler::beforePanEndCallbackMap_;
std::unordered_map<int32_t, std::map<int32_t, PanListenerCallback>> UIObserverHandler::afterPanStartCallbackMap_;
std::unordered_map<int32_t, std::map<int32_t, PanListenerCallback>> UIObserverHandler::afterPanEndCallbackMap_;

std::unordered_map<int32_t, std::map<int32_t, GestureListenerCallback>> UIObserverHandler::willClickCallbackMap_;
std::unordered_map<int32_t, std::map<int32_t, GestureListenerCallback>> UIObserverHandler::didClickCallbackMap_;
std::unordered_map<int32_t, std::map<int32_t, GestureListenerCallback>> UIObserverHandler::willTapCallbackMap_;
std::unordered_map<int32_t, std::map<int32_t, GestureListenerCallback>> UIObserverHandler::didTapCallbackMap_;
GlobalGestureListenerStorage::StorageMap UIObserverHandler::globalGestureListenerMap_;
std::mutex UIObserverHandler::globalGestureMutex_;

UIObserverHandler& UIObserverHandler::GetInstance()
{
    static UIObserverHandler instance;
    return instance;
}

void UIObserverHandler::NotifyNavigationStateChange(const WeakPtr<AceType>& weakPattern, NavDestinationState state)
{
    NotifyNavigationStateChangeForAni(weakPattern, state);
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
    std::shared_ptr<NavPathInfoScope> scope = nullptr;
    scope = pathInfo->Scope();
    NavDestinationInfo info(GetNavigationId(pattern), pattern->GetName(), state, context->GetIndex(),
        pathInfo->GetParamObj(), std::to_string(pattern->GetNavDestinationId()), mode, uniqueId,
        GetNavigationUniqueId(pattern), pattern->GetCurrentNavDestinationSize());
    auto navigationStack = context->GetNavigationStack().Upgrade();
    if (navigationStack && navigationStack->IsStaticStack()) {
        auto navigationStackExtend = navigationStack->GetNavigationStackExtend();
        if (navigationStackExtend) {
            info.interopParam = navigationStackExtend->GetSerializedParamByIndex(context->GetIndex());
        }
    }
    navigationHandleFunc_(info);
}

void UIObserverHandler::NotifyNavigationStateChangeForAni(
    const WeakPtr<AceType>& weakPattern, NavDestinationState state)
{
    CHECK_NULL_VOID(navigationHandleFuncForAni_);
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

    NavDestinationInfo info(GetNavigationId(pattern), pattern->GetName(), state, context->GetIndex(),
        pathInfo->GetParamObj(), std::to_string(pattern->GetNavDestinationId()), mode, uniqueId,
        GetNavigationUniqueId(pattern), pattern->GetCurrentNavDestinationSize());
    auto navigationStack = context->GetNavigationStack().Upgrade();
    if (navigationStack && navigationStack->IsStaticStack()) {
        auto navigationStackExtend = navigationStack->GetNavigationStackExtend();
        if (navigationStackExtend) {
            info.interopParam = navigationStackExtend->GetSerializedParamByIndex(context->GetIndex());
        }
    }
    navigationHandleFuncForAni_(info);
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
    if (scrollEventHandleFunc_) {
        scrollEventHandleFunc_(id, uniqueId, eventType, offset, axis);
    }
    if (scrollEventHandleFuncForAni_) {
        ScrollEventInfo info(id, uniqueId, eventType, offset, axis);
        scrollEventHandleFuncForAni_(info);
    }
}

void UIObserverHandler::NotifyRouterPageStateChangeForAni(
    const RefPtr<PageInfo>& pageInfo, RouterPageState state, const std::optional<SizeF>& size)
{
    CHECK_NULL_VOID(pageInfo);
    CHECK_NULL_VOID(routerPageHandleFuncForAni_);
    auto container = Container::CurrentSafelyWithCheck();
    if (!container) {
        LOGW("notify router event failed, current UI instance invalid");
        return;
    }
    AbilityContextInfo info = {
        AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(),
        container->GetModuleName()
    };
    int32_t index = pageInfo->GetPageIndex();
    std::string name = pageInfo->GetPageUrl();
    std::string path = pageInfo->GetPagePath();
    std::string pageId = std::to_string(pageInfo->GetPageId());
    RouterPageInfoNG routerPageInfo(index, name, path, state, pageId, size);
    routerPageHandleFuncForAni_(info, routerPageInfo);
}

void UIObserverHandler::NotifyRouterPageStateChange(
    const RefPtr<PageInfo>& pageInfo, RouterPageState state, const std::optional<SizeF>& size)
{
    NotifyRouterPageStateChangeForAni(pageInfo, state, size);
    CHECK_NULL_VOID(pageInfo);
    CHECK_NULL_VOID(routerPageHandleFunc_);
    auto container = Container::Current();
    if (!container) {
        LOGW("notify router event failed, current UI instance invalid");
        return;
    }
    AbilityContextInfo info = {
        AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(),
        container->GetModuleName()
    };
    int32_t index = pageInfo->GetPageIndex();
    std::string name = pageInfo->GetPageUrl();
    std::string path = pageInfo->GetPagePath();
    std::string pageId = std::to_string(pageInfo->GetPageId());
    RouterPageInfoNG routerPageInfo(index, name, path, state, pageId, size);
    routerPageHandleFunc_(info, routerPageInfo);
}

void UIObserverHandler::NotifyDensityChange(double density)
{
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
    if (densityHandleFunc_) {
        densityHandleFunc_(info, density);
    }
    if (densityHandleFuncForAni_) {
        densityHandleFuncForAni_(info, density);
    }
}

void UIObserverHandler::NotifyWillClick(
    const GestureEvent& gestureEventInfo, const ClickInfo& clickInfo, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    AbilityContextInfo info = {
        AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(),
        container->GetModuleName()
    };
    if (willClickHandleFunc_) {
        willClickHandleFunc_(info, gestureEventInfo, clickInfo, frameNode);
    }

    TriggerWillClick(gestureEventInfo, frameNode);
    TriggerWillTap(gestureEventInfo, frameNode);

    if (willClickHandleFuncForAni_) {
        willClickHandleFuncForAni_();
    }
}

void UIObserverHandler::NotifyDidClick(
    const GestureEvent& gestureEventInfo, const ClickInfo& clickInfo, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    AbilityContextInfo info = {
        AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(),
        container->GetModuleName()
    };

    if (didClickHandleFunc_) {
        didClickHandleFunc_(info, gestureEventInfo, clickInfo, frameNode);
    }

    TriggerDidClick(gestureEventInfo, frameNode);
    TriggerDidTap(gestureEventInfo, frameNode);

    if (didClickHandleFuncForAni_) {
        didClickHandleFuncForAni_();
    }
}

void UIObserverHandler::NotifyPanGestureStateChange(const GestureEvent& gestureEventInfo,
    const RefPtr<PanRecognizer>& current, const RefPtr<FrameNode>& frameNode, const PanGestureInfo& panGestureInfo)
{
    CHECK_NULL_VOID(frameNode);
    auto getCurrent = Container::Current();
    CHECK_NULL_VOID(getCurrent);
    AbilityContextInfo info = { AceApplicationInfo::GetInstance().GetAbilityName(),
        AceApplicationInfo::GetInstance().GetProcessName(), getCurrent->GetModuleName() };

    if (panGestureHandleFunc_) {
        panGestureHandleFunc_(info, gestureEventInfo, current, frameNode, panGestureInfo);
    }

    if (panGestureInfo.callbackState == CurrentCallbackState::START) {
        if (panGestureInfo.gestureState == PanGestureState::BEFORE) {
            // beforePanStart
            TriggerBeforePanStart(gestureEventInfo, current, frameNode);
        } else if (panGestureInfo.gestureState == PanGestureState::AFTER) {
            // afterPanStart
            TriggerAfterPanStart(gestureEventInfo, current, frameNode);
        }
    } else if (panGestureInfo.callbackState == CurrentCallbackState::END) {
        if (panGestureInfo.gestureState == PanGestureState::BEFORE) {
            // beforePanEnd
            TriggerBeforePanEnd(gestureEventInfo, current, frameNode);
        } else if (panGestureInfo.gestureState == PanGestureState::AFTER) {
            // afterPanEnd
            TriggerAfterPanEnd(gestureEventInfo, current, frameNode);
        }
    }
}

void UIObserverHandler::NotifyGestureStateChange(NG::GestureListenerType gestureListenerType,
    const GestureEvent& gestureEventInfo, const RefPtr<NGGestureRecognizer>& current,
    const RefPtr<FrameNode>& frameNode, NG::GestureActionPhase phase)
{
    CHECK_NULL_VOID(current);
    CHECK_NULL_VOID(frameNode);

    if (gestureHandleFunc_) {
        gestureHandleFunc_(gestureListenerType, gestureEventInfo, current, frameNode, phase);
    }

    // Create GestureTriggerInfo and trigger global gesture listeners
    GestureTriggerInfo triggerInfo;
    triggerInfo.event = gestureEventInfo;
    triggerInfo.current = current ? OHOS::Ace::AceType::RawPtr(current) : nullptr;
    triggerInfo.currentPhase = static_cast<int32_t>(phase);
    triggerInfo.node = frameNode;

    TriggerGlobalGestureListener(
        gestureListenerType,
        phase,
        triggerInfo);
}

void UIObserverHandler::NotifyTabContentStateUpdate(const TabContentInfo& info)
{
    NotifyTabContentStateUpdateForAni(info);
    CHECK_NULL_VOID(tabContentStateHandleFunc_);
    tabContentStateHandleFunc_(info);
}

void UIObserverHandler::NotifyTabContentStateUpdateForAni(const TabContentInfo& info)
{
    CHECK_NULL_VOID(tabContentHandleFuncForAni_);
    tabContentHandleFuncForAni_(info);
}

void UIObserverHandler::NotifyTabChange(const TabContentInfo& info)
{
    if (tabChangeHandleFunc_) {
        tabChangeHandleFunc_(info);
    }
    if (tabChangeHandleFuncForAni_) {
        tabChangeHandleFuncForAni_(info);
    }
}

void UIObserverHandler::NotifyRouterPageSizeChange(
    const RefPtr<PageInfo>& pageInfo, RouterPageState state, const std::optional<SizeF>& size)
{
    CHECK_NULL_VOID(pageInfo);
    if (!routerPageSizeChangeHandleFunc_ && !routerPageSizeChangeHandleFuncForAni_) {
        return;
    }
    int32_t index = pageInfo->GetPageIndex();
    std::string name = pageInfo->GetPageUrl();
    std::string path = pageInfo->GetPagePath();
    std::string pageId = std::to_string(pageInfo->GetPageId());
    RouterPageInfoNG routerPageInfo(index, name, path, state, pageId, size);
    if (routerPageSizeChangeHandleFunc_) {
        routerPageSizeChangeHandleFunc_(routerPageInfo);
    }
    if (routerPageSizeChangeHandleFuncForAni_) {
        routerPageSizeChangeHandleFuncForAni_(routerPageInfo);
    }
}

void UIObserverHandler::NotifyNavDestinationSizeChange(
    const WeakPtr<AceType>& weakPattern, NavDestinationState state, const std::optional<SizeF>& size)
{
    if (!navDestinationSizeChangeHandleFunc_ && !navDestinationSizeChangeByUniqueIdHandleFunc_ &&
        !navDestinationSizeChangeHandleFuncForAni_ && !navDestinationSizeChangeByUniqueIdHandleFuncForAni_) {
        return;
    }
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
    std::shared_ptr<NavPathInfoScope> scope = nullptr;
    scope = pathInfo->Scope();
    NavDestinationInfo info(GetNavigationId(pattern), pattern->GetName(), state, context->GetIndex(),
        pathInfo->GetParamObj(), std::to_string(pattern->GetNavDestinationId()), mode, uniqueId,
        GetNavigationUniqueId(pattern), size);
    if (navDestinationSizeChangeHandleFunc_) {
        navDestinationSizeChangeHandleFunc_(info);
    }
    if (navDestinationSizeChangeByUniqueIdHandleFunc_) {
        navDestinationSizeChangeByUniqueIdHandleFunc_(info);
    }
    if (navDestinationSizeChangeHandleFuncForAni_) {
        navDestinationSizeChangeHandleFuncForAni_(info);
    }
    if (navDestinationSizeChangeByUniqueIdHandleFuncForAni_) {
        navDestinationSizeChangeByUniqueIdHandleFuncForAni_(info);
    }
}

UIObserverHandler::NavDestinationSwitchHandleFunc UIObserverHandler::GetHandleNavDestinationSwitchFunc()
{
    return navDestinationSwitchHandleFunc_;
}

void UIObserverHandler::SetHandleTabContentUpdateFuncForAni(TabContentHandleFuncForAni func)
{
    tabContentHandleFuncForAni_ = func;
}

UIObserverHandler::NavDestinationSwitchHandleFuncForAni UIObserverHandler::GetHandleNavDestinationSwitchFuncForAni()
{
    return navDestinationSwitchHandleFuncForAni_;
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
    auto infoPtr = std::make_shared<NavDestinationInfo>(
        GetNavigationId(pattern), pattern->GetName(),
        state, host->GetIndex(), pathInfo->GetParamObj(), std::to_string(pattern->GetNavDestinationId()),
        mode, uniqueId);
    auto navigationStack = pattern->GetNavigationStack().Upgrade();
    if (navigationStack && navigationStack->IsStaticStack()) {
        auto navigationStackExtend = navigationStack->GetNavigationStackExtend();
        if (navigationStackExtend) {
            infoPtr->interopParam = navigationStackExtend->GetSerializedParamByIndex(host->GetIndex());
        }
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_THREE)) {
        infoPtr->size = pattern->GetCurrentNavDestinationSize();
    }
    return infoPtr;
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
    for (; current; current = current->GetFirstChild()) {
        if (current->GetTag() != V2::NAVDESTINATION_VIEW_ETS_TAG) {
            continue;
        }
        auto parent = current->GetParent();
        CHECK_NULL_CONTINUE(parent);
        const auto& parentTag = parent->GetTag();
        // NavDestination in stack or home NavDestination in forceSplit mode.
        if (parentTag == V2::NAVIGATION_CONTENT_ETS_TAG || parentTag == V2::PRIMARY_CONTENT_NODE_ETS_TAG) {
            break;
        }
        if (parentTag != V2::NAVIGATION_VIEW_ETS_TAG) {
            continue;
        }
        auto destNode = AceType::DynamicCast<NavDestinationGroupNode>(current);
        CHECK_NULL_CONTINUE(destNode);
        // related NavDestination in forceSplit mode.
        if (destNode->GetNavDestinationType() == NavDestinationType::RELATED) {
            break;
        }
    }
    CHECK_NULL_RETURN(current, nullptr);
    return GetNavDestinationInfo(current);
}

std::shared_ptr<NavDestinationInfo> UIObserverHandler::GetNavigationOuterState(const RefPtr<AceType>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto current = AceType::DynamicCast<UINode>(node);
    for (; current; current = current->GetParent()) {
        if (current->GetTag() != V2::NAVDESTINATION_VIEW_ETS_TAG) {
            continue;
        }
        auto parent = current->GetParent();
        CHECK_NULL_CONTINUE(parent);
        const auto& parentTag = parent->GetTag();
        // NavDestination in stack or home NavDestination in forceSplit mode.
        if (parentTag == V2::NAVIGATION_CONTENT_ETS_TAG || parentTag == V2::PRIMARY_CONTENT_NODE_ETS_TAG) {
            break;
        }
        if (parentTag != V2::NAVIGATION_VIEW_ETS_TAG) {
            continue;
        }
        auto destNode = AceType::DynamicCast<NavDestinationGroupNode>(current);
        CHECK_NULL_CONTINUE(destNode);
        // related NavDestination in forceSplit mode.
        if (destNode->GetNavDestinationType() == NavDestinationType::RELATED) {
            break;
        }
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
    auto info = std::make_shared<RouterPageInfoNG>(
        index,
        name,
        path,
        RouterPageState(pattern->GetPageState()),
        pageId);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_THREE)) {
        info->size = pattern->GetCurrentPageSize();
    }
    return info;
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
    NotifyNavDestinationSwitchForAni(from, to, operation);
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
    NavDestinationSwitchInfo switchInfo(std::forward<std::optional<NavDestinationInfo>>(from),
        std::forward<std::optional<NavDestinationInfo>>(to), operation);
    navDestinationSwitchHandleFunc_(info, switchInfo);
}

void UIObserverHandler::NotifyNavDestinationSwitchForAni(
    std::optional<NavDestinationInfo>& from, std::optional<NavDestinationInfo>& to, NavigationOperation operation)
{
    CHECK_NULL_VOID(navDestinationSwitchHandleFuncForAni_);
    auto container = Container::CurrentSafelyWithCheck();
    if (!container) {
        LOGW("notify destination event failed, current UI instance invalid");
        return;
    }
    NavDestinationSwitchInfo switchInfo(
        std::optional<NavDestinationInfo>(from), std::optional<NavDestinationInfo>(to), operation);
    navDestinationSwitchHandleFuncForAni_(switchInfo);
}

void UIObserverHandler::NotifyTextChangeEvent(const TextChangeEventInfo& info)
{
    CHECK_NULL_VOID(textChangeEventHandleFunc_);
    textChangeEventHandleFunc_(info);
}

void UIObserverHandler::NotifySwiperContentUpdate(const SwiperContentInfo& info)
{
    CHECK_NULL_VOID(swiperContentUpdateHandleFunc_);
    swiperContentUpdateHandleFunc_(info);
}

bool UIObserverHandler::IsSwiperContentObserverEmpty()
{
    CHECK_NULL_RETURN(swiperContentObservrEmptyFunc_, true);
    return swiperContentObservrEmptyFunc_();
}

void UIObserverHandler::NotifyWinSizeLayoutBreakpointChangeFunc(
    int32_t instanceId, const WindowSizeBreakpoint& breakpoint)
{
    if (winSizeLayoutBreakpointHandleFunc_) {
        winSizeLayoutBreakpointHandleFunc_(instanceId, breakpoint);
    }
    if (winSizeLayoutBreakpointHandleFuncAni_) {
        winSizeLayoutBreakpointHandleFuncAni_(instanceId, breakpoint);
    }
}

void UIObserverHandler::SetHandleNavigationChangeFunc(NavigationHandleFunc func)
{
    navigationHandleFunc_ = func;
}

void UIObserverHandler::SetHandleNavigationChangeFuncForAni(NavigationHandleFuncForAni func)
{
    navigationHandleFuncForAni_ = func;
}

void UIObserverHandler::SetHandleScrollEventChangeFunc(ScrollEventHandleFunc func)
{
    scrollEventHandleFunc_ = func;
}

void UIObserverHandler::SetHandleScrollEventChangeFuncForAni(ScrollEventHandleFuncForAni func)
{
    scrollEventHandleFuncForAni_ = func;
}

void UIObserverHandler::SetHandleRouterPageChangeFunc(RouterPageHandleFunc func)
{
    routerPageHandleFunc_ = func;
}

void UIObserverHandler::SetHandleRouterPageChangeFuncForAni(RouterPageHandleFuncForAni func)
{
    routerPageHandleFuncForAni_ = func;
}

void UIObserverHandler::SetHandleDensityChangeFunc(DensityHandleFunc func)
{
    densityHandleFunc_ = func;
}

void UIObserverHandler::SetWinSizeLayoutBreakpointChangeFunc(WinSizeLayoutBreakpointHandleFunc func)
{
    winSizeLayoutBreakpointHandleFunc_ = std::move(func);
}

void UIObserverHandler::SetWinSizeLayoutBreakpointChangeFuncAni(WinSizeLayoutBreakpointHandleFuncAni func)
{
    winSizeLayoutBreakpointHandleFuncAni_ = std::move(func);
}

void UIObserverHandler::SetHandleDensityChangeFuncForAni(DensityHandleFuncForAni func)
{
    densityHandleFuncForAni_ = func;
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

void UIObserverHandler::SetHandleNavDestinationSwitchFuncForAni(NavDestinationSwitchHandleFuncForAni func)
{
    navDestinationSwitchHandleFuncForAni_ = func;
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

void UIObserverHandler::SetBeforePanStartHandleFuncForAni(BeforePanStartHandleFuncForAni func)
{
    beforePanStartHandleFuncForAni_ = func;
}

void UIObserverHandler::SetAfterPanStartHandleFuncForAni(AfterPanStartHandleFuncForAni func)
{
    afterPanStartHandleFuncForAni_ = func;
}

void UIObserverHandler::SetBeforePanEndHandleFuncForAni(BeforePanEndHandleFuncForAni func)
{
    beforePanEndHandleFuncForAni_ = func;
}

void UIObserverHandler::SetAfterPanEndHandleFuncForAni(AfterPanEndHandleFuncForAni func)
{
    afterPanEndHandleFuncForAni_ = func;
}

void UIObserverHandler::SetWillClickHandleFuncForAni(WillClickHandleFuncForAni func)
{
    willClickHandleFuncForAni_ = func;
}

void UIObserverHandler::SetDidClickHandleFuncForAni(DidClickHandleFuncForAni func)
{
    didClickHandleFuncForAni_ = func;
}

void UIObserverHandler::SetHandleTabContentStateUpdateFunc(TabContentStateHandleFunc func)
{
    tabContentStateHandleFunc_ = func;
}

void UIObserverHandler::SetHandleTabChangeFunc(TabChangeHandleFunc func)
{
    tabChangeHandleFunc_ = func;
}

void UIObserverHandler::SetHandleTabChangeFuncForAni(TabChangeHandleFuncForAni func)
{
    tabChangeHandleFuncForAni_ = func;
}

void UIObserverHandler::SetHandleTextChangeEventFunc(TextChangeEventHandleFunc&& func)
{
    textChangeEventHandleFunc_ = std::move(func);
}

void UIObserverHandler::SetSwiperContentUpdateHandleFunc(SwiperContentUpdateHandleFunc&& func)
{
    swiperContentUpdateHandleFunc_ = std::move(func);
}

void UIObserverHandler::SetSwiperContentObservrEmptyFunc(SwiperContentObservrEmptyFunc&& func)
{
    swiperContentObservrEmptyFunc_ = std::move(func);
}

void UIObserverHandler::SetRouterPageSizeChangeHandleFunc(RouterPageSizeChangeHandleFunc func)
{
    routerPageSizeChangeHandleFunc_ = func;
}

void UIObserverHandler::SetNavDestinationSizeChangeHandleFunc(NavDestinationSizeChangeHandleFunc func)
{
    navDestinationSizeChangeHandleFunc_ = func;
}

void UIObserverHandler::SetNavDestinationSizeChangeByUniqueIdHandleFunc(
    NavDestinationSizeChangeByUniqueIdHandleFunc func)
{
    navDestinationSizeChangeByUniqueIdHandleFunc_ = func;
}

void UIObserverHandler::SetRouterPageSizeChangeHandleFuncForAni(RouterPageSizeChangeHandleFuncForAni&& func)
{
    routerPageSizeChangeHandleFuncForAni_ = std::move(func);
}

void UIObserverHandler::SetNavDestinationSizeChangeHandleFuncForAni(NavDestinationSizeChangeHandleFuncForAni&& func)
{
    navDestinationSizeChangeHandleFuncForAni_ = std::move(func);
}

void UIObserverHandler::SetNavDestinationSizeChangeByUniqueIdHandleFuncForAni(
    NavDestinationSizeChangeByUniqueIdHandleFuncForAni&& func)
{
    navDestinationSizeChangeByUniqueIdHandleFuncForAni_ = std::move(func);
}

napi_value UIObserverHandler::GetUIContextValue()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, nullptr);
    return frontend->GetContextValue();
}

void UIObserverHandler::AddBeforePanStartListenerCallback(
    int32_t instanceId, int32_t resourceId, PanListenerCallback&& callback)
{
    CHECK_NULL_VOID(callback);
    auto iter = beforePanStartCallbackMap_.find(instanceId);
    if (iter == beforePanStartCallbackMap_.end()) {
        std::map<int32_t, PanListenerCallback> callbackMap;
        callbackMap[resourceId] = std::move(callback);
        beforePanStartCallbackMap_[instanceId] = callbackMap;
    } else {
        iter->second[resourceId] = std::move(callback);
    }
}

void UIObserverHandler::AddBeforePanEndListenerCallback(
    int32_t instanceId, int32_t resourceId, PanListenerCallback&& callback)
{
    CHECK_NULL_VOID(callback);
    auto iter = beforePanEndCallbackMap_.find(instanceId);
    if (iter == beforePanEndCallbackMap_.end()) {
        std::map<int32_t, PanListenerCallback> callbackMap;
        callbackMap[resourceId] = std::move(callback);
        beforePanEndCallbackMap_[instanceId] = callbackMap;
    } else {
        iter->second[resourceId] = std::move(callback);
    }
}

void UIObserverHandler::AddAfterPanStartListenerCallback(
    int32_t instanceId, int32_t resourceId, PanListenerCallback&& callback)
{
    CHECK_NULL_VOID(callback);
    auto iter = afterPanStartCallbackMap_.find(instanceId);
    if (iter == afterPanStartCallbackMap_.end()) {
        std::map<int32_t, PanListenerCallback> callbackMap;
        callbackMap[resourceId] = std::move(callback);
        afterPanStartCallbackMap_[instanceId] = callbackMap;
    } else {
        iter->second[resourceId] = std::move(callback);
    }
}

void UIObserverHandler::AddAfterPanEndListenerCallback(
    int32_t instanceId, int32_t resourceId, PanListenerCallback&& callback)
{
    CHECK_NULL_VOID(callback);
    auto iter = afterPanEndCallbackMap_.find(instanceId);
    if (iter == afterPanEndCallbackMap_.end()) {
        std::map<int32_t, PanListenerCallback> callbackMap;
        callbackMap[resourceId] = std::move(callback);
        afterPanEndCallbackMap_[instanceId] = callbackMap;
    } else {
        iter->second[resourceId] = std::move(callback);
    }
}

void UIObserverHandler::RemoveBeforePanStartListenerCallback(int32_t instanceId, int32_t resourceId, bool isRemoveAll)
{
    CHECK_NULL_VOID(!beforePanStartCallbackMap_.empty());
    if (isRemoveAll) {
        beforePanStartCallbackMap_.erase(instanceId);
        return;
    }
    auto iter = beforePanStartCallbackMap_.find(instanceId);
    if (iter != beforePanStartCallbackMap_.end()) {
        iter->second.erase(resourceId);
    }
}

void UIObserverHandler::RemoveBeforePanEndListenerCallback(int32_t instanceId, int32_t resourceId, bool isRemoveAll)
{
    CHECK_NULL_VOID(!beforePanEndCallbackMap_.empty());
    if (isRemoveAll) {
        beforePanEndCallbackMap_.erase(instanceId);
        return;
    }
    auto iter = beforePanEndCallbackMap_.find(instanceId);
    if (iter != beforePanEndCallbackMap_.end()) {
        iter->second.erase(resourceId);
    }
}

void UIObserverHandler::RemoveAfterPanStartListenerCallback(int32_t instanceId, int32_t resourceId, bool isRemoveAll)
{
    CHECK_NULL_VOID(!afterPanStartCallbackMap_.empty());
    if (isRemoveAll) {
        afterPanStartCallbackMap_.erase(instanceId);
        return;
    }
    auto iter = afterPanStartCallbackMap_.find(instanceId);
    if (iter != afterPanStartCallbackMap_.end()) {
        iter->second.erase(resourceId);
    }
}

void UIObserverHandler::RemoveAfterPanEndListenerCallback(int32_t instanceId, int32_t resourceId, bool isRemoveAll)
{
    CHECK_NULL_VOID(!afterPanEndCallbackMap_.empty());
    if (isRemoveAll) {
        afterPanEndCallbackMap_.erase(instanceId);
        return;
    }
    auto iter = afterPanEndCallbackMap_.find(instanceId);
    if (iter != afterPanEndCallbackMap_.end()) {
        iter->second.erase(resourceId);
    }
}

void UIObserverHandler::TriggerBeforePanStart(
    const GestureEvent& gestureEventInfo, const RefPtr<PanRecognizer>& current, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(!beforePanStartCallbackMap_.empty());
    auto currentId = Container::CurrentId();
    auto iter = beforePanStartCallbackMap_.find(currentId);
    if (iter != beforePanStartCallbackMap_.end()) {
        auto callbackMap = iter->second;
        for (auto& pair : callbackMap) {
            if (pair.second) {
                pair.second(gestureEventInfo, current, frameNode);
            }
        }
    }
}

void UIObserverHandler::TriggerBeforePanEnd(
    const GestureEvent& gestureEventInfo, const RefPtr<PanRecognizer>& current, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(!beforePanEndCallbackMap_.empty());
    auto currentId = Container::CurrentId();
    auto iter = beforePanEndCallbackMap_.find(currentId);
    if (iter != beforePanEndCallbackMap_.end()) {
        auto callbackMap = iter->second;
        for (auto& pair : callbackMap) {
            if (pair.second) {
                pair.second(gestureEventInfo, current, frameNode);
            }
        }
    }
}

void UIObserverHandler::TriggerAfterPanStart(
    const GestureEvent& gestureEventInfo, const RefPtr<PanRecognizer>& current, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(!afterPanStartCallbackMap_.empty());
    auto currentId = Container::CurrentId();
    auto iter = afterPanStartCallbackMap_.find(currentId);
    if (iter != afterPanStartCallbackMap_.end()) {
        auto callbackMap = iter->second;
        for (auto& pair : callbackMap) {
            if (pair.second) {
                pair.second(gestureEventInfo, current, frameNode);
            }
        }
    }
}

void UIObserverHandler::TriggerAfterPanEnd(
    const GestureEvent& gestureEventInfo, const RefPtr<PanRecognizer>& current, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(!afterPanEndCallbackMap_.empty());
    auto currentId = Container::CurrentId();
    auto iter = afterPanEndCallbackMap_.find(currentId);
    if (iter != afterPanEndCallbackMap_.end()) {
        auto callbackMap = iter->second;
        for (auto& pair : callbackMap) {
            if (pair.second) {
                pair.second(gestureEventInfo, current, frameNode);
            }
        }
    }
}

void UIObserverHandler::AddWillClickListenerCallback(
    int32_t instanceId, int32_t resourceId, GestureListenerCallback&& callback)
{
    CHECK_NULL_VOID(callback);
    auto iter = willClickCallbackMap_.find(instanceId);
    if (iter == willClickCallbackMap_.end()) {
        std::map<int32_t, GestureListenerCallback> callbackMap;
        callbackMap[resourceId] = std::move(callback);
        willClickCallbackMap_[instanceId] = callbackMap;
    } else {
        iter->second[resourceId] = std::move(callback);
    }
}
void UIObserverHandler::AddDidClickListenerCallback(
    int32_t instanceId, int32_t resourceId, GestureListenerCallback&& callback)
{
    CHECK_NULL_VOID(callback);
    auto iter = didClickCallbackMap_.find(instanceId);
    if (iter == didClickCallbackMap_.end()) {
        std::map<int32_t, GestureListenerCallback> callbackMap;
        callbackMap[resourceId] = std::move(callback);
        didClickCallbackMap_[instanceId] = callbackMap;
    } else {
        iter->second[resourceId] = std::move(callback);
    }
}
void UIObserverHandler::AddWillTapListenerCallback(
    int32_t instanceId, int32_t resourceId, GestureListenerCallback&& callback)
{
    CHECK_NULL_VOID(callback);
    auto iter = willTapCallbackMap_.find(instanceId);
    if (iter == willTapCallbackMap_.end()) {
        std::map<int32_t, GestureListenerCallback> callbackMap;
        callbackMap[resourceId] = std::move(callback);
        willTapCallbackMap_[instanceId] = callbackMap;
    } else {
        iter->second[resourceId] = std::move(callback);
    }
}
void UIObserverHandler::AddDidTapListenerCallback(
    int32_t instanceId, int32_t resourceId, GestureListenerCallback&& callback)
{
    CHECK_NULL_VOID(callback);
    auto iter = didTapCallbackMap_.find(instanceId);
    if (iter == didTapCallbackMap_.end()) {
        std::map<int32_t, GestureListenerCallback> callbackMap;
        callbackMap[resourceId] = std::move(callback);
        didTapCallbackMap_[instanceId] = callbackMap;
    } else {
        iter->second[resourceId] = std::move(callback);
    }
}

void UIObserverHandler::RemoveWillClickListenerCallback(int32_t instanceId, int32_t resourceId, bool isRemoveAll)
{
    CHECK_NULL_VOID(!willClickCallbackMap_.empty());
    if (isRemoveAll) {
        willClickCallbackMap_.erase(instanceId);
        return;
    }
    auto iter = willClickCallbackMap_.find(instanceId);
    if (iter != willClickCallbackMap_.end()) {
        iter->second.erase(resourceId);
    }
}
void UIObserverHandler::RemoveDidClickListenerCallback(int32_t instanceId, int32_t resourceId, bool isRemoveAll)
{
    CHECK_NULL_VOID(!didClickCallbackMap_.empty());
    if (isRemoveAll) {
        didClickCallbackMap_.erase(instanceId);
        return;
    }
    auto iter = didClickCallbackMap_.find(instanceId);
    if (iter != didClickCallbackMap_.end()) {
        iter->second.erase(resourceId);
    }
}
void UIObserverHandler::RemoveWillTapListenerCallback(int32_t instanceId, int32_t resourceId, bool isRemoveAll)
{
    CHECK_NULL_VOID(!willTapCallbackMap_.empty());
    if (isRemoveAll) {
        willTapCallbackMap_.erase(instanceId);
        return;
    }
    auto iter = willTapCallbackMap_.find(instanceId);
    if (iter != willTapCallbackMap_.end()) {
        iter->second.erase(resourceId);
    }
}
void UIObserverHandler::RemoveDidTapListenerCallback(int32_t instanceId, int32_t resourceId, bool isRemoveAll)
{
    CHECK_NULL_VOID(!didTapCallbackMap_.empty());
    if (isRemoveAll) {
        didTapCallbackMap_.erase(instanceId);
        return;
    }
    auto iter = didTapCallbackMap_.find(instanceId);
    if (iter != didTapCallbackMap_.end()) {
        iter->second.erase(resourceId);
    }
}

void UIObserverHandler::AddGlobalGestureListenerCallback(
    GestureListenerType gestureType,
    GestureActionPhase phase,
    int32_t resourceId,
    GlobalGestureListenerCallback&& callback)
{
    CHECK_NULL_VOID(callback);
    std::lock_guard<std::mutex> lock(globalGestureMutex_);

    // Combine gestureType and phase into unique key using bitwise operation
    uint64_t combinedKey = GlobalGestureListenerStorage::CombineKey(gestureType, phase);

    // Store or replace callback with resourceId for this combined key
    GlobalGestureListenerStorage::CallbackInfo callbackInfo;
    callbackInfo.resourceId = resourceId;
    callbackInfo.callback = std::move(callback);
    globalGestureListenerMap_[combinedKey] = std::move(callbackInfo);
}

void UIObserverHandler::RemoveGlobalGestureListenerCallback(
    GestureListenerType gestureType,
    int32_t resourceId)
{
    std::lock_guard<std::mutex> lock(globalGestureMutex_);

    // Remove callbacks matching the gestureType and resourceId
    for (auto iter = globalGestureListenerMap_.begin(); iter != globalGestureListenerMap_.end();) {
        uint64_t combinedKey = iter->first;
        GestureListenerType keyType = static_cast<GestureListenerType>(
            combinedKey >> GlobalGestureListenerStorage::GESTURE_TYPE_SHIFT_BITS);

        if (keyType == gestureType && iter->second.resourceId == resourceId) {
            iter = globalGestureListenerMap_.erase(iter);
        } else {
            ++iter;
        }
    }
}

void UIObserverHandler::RemoveGlobalGestureListenerCallback(
    GestureListenerType gestureType,
    GestureActionPhase phase)
{
    std::lock_guard<std::mutex> lock(globalGestureMutex_);

    // Combine gestureType and phase into unique key
    uint64_t combinedKey = GlobalGestureListenerStorage::CombineKey(gestureType, phase);

    // Remove the callback for this specific gestureType+phase combination
    globalGestureListenerMap_.erase(combinedKey);
}

void UIObserverHandler::TriggerGlobalGestureListener(
    GestureListenerType gestureType,
    GestureActionPhase phase,
    const GestureTriggerInfo& triggerInfo)
{
    std::lock_guard<std::mutex> lock(globalGestureMutex_);

    // Combine gestureType and phase into unique key
    uint64_t combinedKey = GlobalGestureListenerStorage::CombineKey(gestureType, phase);

    auto iter = globalGestureListenerMap_.find(combinedKey);
    if (iter == globalGestureListenerMap_.end()) {
        return;
    }

    // Trigger the single callback for this (gestureType, phase) combination
    const auto& callbackInfo = iter->second;
    if (callbackInfo.callback) {
        callbackInfo.callback(triggerInfo);
    }
}

void UIObserverHandler::TriggerWillClick(const GestureEvent& clickInfo, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(!willClickCallbackMap_.empty());
    auto currentId = Container::CurrentId();
    auto iter = willClickCallbackMap_.find(currentId);
    if (iter != willClickCallbackMap_.end()) {
        auto callbackMap = iter->second;
        for (auto& pair : callbackMap) {
            if (pair.second) {
                pair.second(clickInfo, frameNode);
            }
        }
    }
}
void UIObserverHandler::TriggerDidClick(const GestureEvent& clickInfo, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(!didClickCallbackMap_.empty());
    auto currentId = Container::CurrentId();
    auto iter = didClickCallbackMap_.find(currentId);
    if (iter != didClickCallbackMap_.end()) {
        auto callbackMap = iter->second;
        for (auto& pair : callbackMap) {
            if (pair.second) {
                pair.second(clickInfo, frameNode);
            }
        }
    }
}
void UIObserverHandler::TriggerWillTap(const GestureEvent& gestureEvent, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(!willTapCallbackMap_.empty());
    auto currentId = Container::CurrentId();
    auto iter = willTapCallbackMap_.find(currentId);
    if (iter != willTapCallbackMap_.end()) {
        auto callbackMap = iter->second;
        for (auto& pair : callbackMap) {
            if (pair.second) {
                pair.second(gestureEvent, frameNode);
            }
        }
    }
}
void UIObserverHandler::TriggerDidTap(const GestureEvent& gestureEvent, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(!didTapCallbackMap_.empty());
    auto currentId = Container::CurrentId();
    auto iter = didTapCallbackMap_.find(currentId);
    if (iter != didTapCallbackMap_.end()) {
        auto callbackMap = iter->second;
        for (auto& pair : callbackMap) {
            if (pair.second) {
                pair.second(gestureEvent, frameNode);
            }
        }
    }
}
} // namespace OHOS::Ace::NG
