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

#include "ui_observer.h"

#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/base/node_render_status_monitor.h"

namespace OHOS::Ace::Napi {
std::list<std::shared_ptr<UIObserverListener>> UIObserver::unspecifiedNavigationListeners_;
std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedCNavigationListeners_;
std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedUniqueIdNavigationListeners_;

std::list<std::shared_ptr<UIObserverListener>> UIObserver::scrollEventListeners_;
std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedScrollEventListeners_;

std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::abilityContextRouterPageListeners_;
std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedRouterPageListeners_;
std::unordered_map<napi_ref, NG::AbilityContextInfo> UIObserver::infosForRouterPage_;

std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedDensityListeners_;
std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>> UIObserver::specifiedDrawListeners_;
std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>> UIObserver::specifiedLayoutListeners_;

std::unordered_map<napi_ref, UIObserver::NavIdAndListenersMap> UIObserver::abilityUIContextNavDesSwitchListeners_;
std::unordered_map<int32_t, UIObserver::NavIdAndListenersMap> UIObserver::uiContextNavDesSwitchListeners_;
std::unordered_map<napi_ref, NG::AbilityContextInfo> UIObserver::infosForNavDesSwitch_;

std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::abilityContextWillClickListeners_;
std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedWillClickListeners_;
std::unordered_map<napi_ref, NG::AbilityContextInfo> UIObserver::willClickInfos_;

std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::abilityContextDidClickListeners_;
std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedDidClickListeners_;
std::unordered_map<napi_ref, NG::AbilityContextInfo> UIObserver::didClickInfos_;

std::list<std::shared_ptr<UIObserverListener>> UIObserver::tabContentStateListeners_;
std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedTabContentStateListeners_;

std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::abilityContextBeforePanStartListeners_;
std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedBeforePanStartListeners_;
std::unordered_map<napi_ref, NG::AbilityContextInfo> UIObserver::beforePanStartInfos_;
std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::abilityContextBeforePanEndListeners_;
std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedBeforePanEndListeners_;
std::unordered_map<napi_ref, NG::AbilityContextInfo> UIObserver::beforePanEndInfos_;

std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::abilityContextAfterPanStartListeners_;
std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedAfterPanStartListeners_;
std::unordered_map<napi_ref, NG::AbilityContextInfo> UIObserver::afterPanStartInfos_;
std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::abilityContextAfterPanEndListeners_;
std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedAfterPanEndListeners_;
std::unordered_map<napi_ref, NG::AbilityContextInfo> UIObserver::afterPanEndInfos_;
std::unordered_map<napi_ref, NG::AbilityContextInfo> UIObserver::PanGestureInfos_;

std::unordered_map<NG::FrameNode*, std::shared_ptr<UIObserver::NodeRenderListener>>
    UIObserver::specifiedNodeRenderStateListeners_;

template<typename ListenerList, typename... Args>
void SafeIterateListeners(const ListenerList& listeners, void (UIObserverListener::*callback)(Args...), Args... args)
{
    ListenerList listenersCopy = listeners;
    for (const auto& listener : listenersCopy) {
        (listener.get()->*callback)(std::forward<Args>(args)...);
    }
}

// register a global listener without options
void UIObserver::RegisterNavigationCallback(const std::shared_ptr<UIObserverListener>& listener)
{
    if (std::find(unspecifiedNavigationListeners_.begin(), unspecifiedNavigationListeners_.end(), listener) !=
        unspecifiedNavigationListeners_.end()) {
        return;
    }
    unspecifiedNavigationListeners_.emplace_back(listener);
}

// UIObserver.on(type: "navDestinationUpdate", options, callback)
// register a listener on a specified Navigation
void UIObserver::RegisterNavigationCallback(
    std::string navigationId, const std::shared_ptr<UIObserverListener>& listener)
{
    auto iter = specifiedCNavigationListeners_.find(navigationId);
    if (iter == specifiedCNavigationListeners_.end()) {
        specifiedCNavigationListeners_.emplace(
            navigationId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

// UIObserver.on(type: "navDestinationUpdate", navigationUniqueId, callback)
// register a listener on a specified Navigation
void UIObserver::RegisterNavigationCallback(
    int32_t navigationUniqueId, const std::shared_ptr<UIObserverListener>& listener)
{
    auto iter = specifiedUniqueIdNavigationListeners_.find(navigationUniqueId);
    if (iter == specifiedUniqueIdNavigationListeners_.end()) {
        specifiedUniqueIdNavigationListeners_.emplace(
            navigationUniqueId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

// UIObserver.off(type: "navDestinationUpdate", callback)
void UIObserver::UnRegisterNavigationCallback(napi_value cb)
{
    if (cb == nullptr) {
        unspecifiedNavigationListeners_.clear();
        return;
    }

    unspecifiedNavigationListeners_.erase(
        std::remove_if(
            unspecifiedNavigationListeners_.begin(),
            unspecifiedNavigationListeners_.end(),
            [cb](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(cb);
            }
        ),
        unspecifiedNavigationListeners_.end()
    );
}

// UIObserver.off(type: "navDestinationUpdate", options, callback)
void UIObserver::UnRegisterNavigationCallback(std::string navigationId, napi_value cb)
{
    auto iter = specifiedCNavigationListeners_.find(navigationId);
    if (iter == specifiedCNavigationListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (cb == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [cb](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(cb);
            }
        ),
        holder.end()
    );
}

// UIObserver.off(type: "navDestinationUpdate", navigationUniqueId, callback)
void UIObserver::UnRegisterNavigationCallback(int32_t navigationUniqueId, napi_value cb)
{
    auto iter = specifiedUniqueIdNavigationListeners_.find(navigationUniqueId);
    if (iter == specifiedUniqueIdNavigationListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (cb == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [cb](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(cb);
            }
        ),
        holder.end()
    );
}

void UIObserver::HandleNavigationStateChange(const NG::NavDestinationInfo& info)
{
    auto unspecifiedHolder = unspecifiedNavigationListeners_;
    for (const auto& listener : unspecifiedHolder) {
        listener->OnNavigationStateChange(info);
    }
    auto iter = specifiedCNavigationListeners_.find(info.navigationId);
    if (iter != specifiedCNavigationListeners_.end()) {
        auto holder = iter->second;

        for (const auto& listener : holder) {
            listener->OnNavigationStateChange(info);
        }
    }

    auto navigationdUniqueIdIter = specifiedUniqueIdNavigationListeners_.find(info.navigationUniqueId);
    if (navigationdUniqueIdIter != specifiedUniqueIdNavigationListeners_.end()) {
        auto holder = navigationdUniqueIdIter->second;

        for (const auto& listener : holder) {
            listener->OnNavigationStateChange(info);
        }
    }
}

// UIObserver.on(type: "scrollEvent", callback)
// register a global listener without options
void UIObserver::RegisterScrollEventCallback(const std::shared_ptr<UIObserverListener>& listener)
{
    if (std::find(scrollEventListeners_.begin(), scrollEventListeners_.end(), listener) !=
        scrollEventListeners_.end()) {
        return;
    }
    scrollEventListeners_.emplace_back(listener);
}

// UIObserver.on(type: "scrollEvent", options, callback)
// register a listener on a specified scrollEvent
void UIObserver::RegisterScrollEventCallback(
    const std::string& id, const std::shared_ptr<UIObserverListener>& listener)
{
    auto iter = specifiedScrollEventListeners_.find(id);
    if (iter == specifiedScrollEventListeners_.end()) {
        specifiedScrollEventListeners_.emplace(id, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

// UIObserver.off(type: "scrollEvent", callback)
void UIObserver::UnRegisterScrollEventCallback(napi_value cb)
{
    if (cb == nullptr) {
        scrollEventListeners_.clear();
        return;
    }

    scrollEventListeners_.erase(
        std::remove_if(
            scrollEventListeners_.begin(),
            scrollEventListeners_.end(),
            [cb](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(cb);
            }),
        scrollEventListeners_.end()
    );
}

// UIObserver.off(type: "scrollEvent", options, callback)
void UIObserver::UnRegisterScrollEventCallback(const std::string& id, napi_value cb)
{
    auto iter = specifiedScrollEventListeners_.find(id);
    if (iter == specifiedScrollEventListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (cb == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [cb](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(cb);
            }),
        holder.end()
    );
}

void UIObserver::HandleScrollEventStateChange(const std::string& id, int32_t uniqueId,
    NG::ScrollEventType eventType, float offset, Ace::Axis axis)
{
    // copy value to avoid developer call off while execute callback of on
    auto scrollEventListeners = scrollEventListeners_;
    for (const auto& listener : scrollEventListeners) {
        listener->OnScrollEventStateChange(id, uniqueId, eventType, offset, axis);
    }

    auto iter = specifiedScrollEventListeners_.find(id);
    if (iter == specifiedScrollEventListeners_.end()) {
        return;
    }

    // copy value to avoid developer call off while execute callback of on
    auto holder = iter->second;

    for (const auto& listener : holder) {
        listener->OnScrollEventStateChange(id, uniqueId, eventType, offset, axis);
    }
}

// UIObserver.on(type: "routerPageUpdate", UIAbilityContext, callback)
// register a listener on current page
void UIObserver::RegisterRouterPageCallback(
    napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener)
{
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextRouterPageListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = infosForRouterPage_[ref];
        if (info.IsEqual(localInfo)) {
            auto& holder = abilityContextRouterPageListeners_[ref];
            if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
                return;
            }
            holder.emplace_back(listener);
            return;
        }
    }
    napi_ref newRef = nullptr;
    napi_create_reference(env, uiAbilityContext, 1, &newRef);
    abilityContextRouterPageListeners_[newRef] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
    infosForRouterPage_[newRef] = info;
}

// UIObserver.on(type: "routerPageUpdate", uiContext | null, callback)
// register a listener on current page
void UIObserver::RegisterRouterPageCallback(
    int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedRouterPageListeners_.find(uiContextInstanceId);
    if (iter == specifiedRouterPageListeners_.end()) {
        specifiedRouterPageListeners_.emplace(
            uiContextInstanceId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

// UIObserver.off(type: "routerPageUpdate", uiAbilityContext, callback)
void UIObserver::UnRegisterRouterPageCallback(napi_env env, napi_value uiAbilityContext, napi_value callback)
{
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextRouterPageListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = infosForRouterPage_[ref];
        if (info.IsEqual(localInfo)) {
            auto& holder = abilityContextRouterPageListeners_[listenerPair.first];
            if (callback == nullptr) {
                holder.clear();
            } else {
                holder.erase(
                    std::remove_if(
                        holder.begin(),
                        holder.end(),
                        [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                            return registeredListener->NapiEqual(callback);
                        }),
                    holder.end());
            }
            if (holder.empty()) {
                infosForRouterPage_.erase(ref);
                abilityContextRouterPageListeners_.erase(ref);
                napi_delete_reference(env, ref);
            }
            return;
        }
    }
}

// UIObserver.off(type: "routerPageUpdate", uiContext | null, callback)
void UIObserver::UnRegisterRouterPageCallback(int32_t uiContextInstanceId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedRouterPageListeners_.find(uiContextInstanceId);
    if (iter == specifiedRouterPageListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (callback == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
}

// UIObserver.on(type: "willDraw", uiContext | null, callback)
// register a listener on current page
void UIObserver::RegisterDrawCallback(int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    if (specifiedDrawListeners_.find(uiContextInstanceId) == specifiedDrawListeners_.end()) {
        specifiedDrawListeners_[uiContextInstanceId] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
        return;
    }
    auto& holder = specifiedDrawListeners_[uiContextInstanceId];
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

// UIObserver.off(type: "willDraw", uiContext | null, callback)
void UIObserver::UnRegisterDrawCallback(int32_t uiContextInstanceId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    if (specifiedDrawListeners_.find(uiContextInstanceId) == specifiedDrawListeners_.end()) {
        return;
    }
    auto& holder = specifiedDrawListeners_[uiContextInstanceId];
    if (callback == nullptr) {
        auto container = Container::GetContainer(uiContextInstanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask([&holder]() { holder.clear(); }, TaskExecutor::TaskType::UI, "ArkUIClearListener");
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
}

// UIObserver.on(type: "didLayout", uiContext | null, callback)
// register a listener on current page
void UIObserver::RegisterLayoutCallback(
    int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    if (specifiedLayoutListeners_.find(uiContextInstanceId) == specifiedLayoutListeners_.end()) {
        specifiedLayoutListeners_[uiContextInstanceId] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
        return;
    }
    auto& holder = specifiedLayoutListeners_[uiContextInstanceId];
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

// UIObserver.off(type: "didLayout", uiContext | null, callback)
void UIObserver::UnRegisterLayoutCallback(int32_t uiContextInstanceId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    if (specifiedLayoutListeners_.find(uiContextInstanceId) == specifiedLayoutListeners_.end()) {
        return;
    }
    auto& holder = specifiedLayoutListeners_[uiContextInstanceId];
    if (callback == nullptr) {
        auto container = Container::GetContainer(uiContextInstanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask([&holder]() { holder.clear(); }, TaskExecutor::TaskType::UI, "ArkUIClearListener");
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
}

void UIObserver::HandleRouterPageStateChange(NG::AbilityContextInfo& info, const NG::RouterPageInfoNG& pageInfo)
{
    for (auto listenerPair : abilityContextRouterPageListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = infosForRouterPage_[ref];
        if (info.IsEqual(localInfo)) {
            auto env = GetCurrentNapiEnv();
            napi_value abilityContext = nullptr;
            napi_get_reference_value(env, ref, &abilityContext);

            NG::RouterPageInfoNG abilityPageInfo(
                abilityContext, pageInfo.index, pageInfo.name, pageInfo.path, pageInfo.state, pageInfo.pageId);
            auto holder = abilityContextRouterPageListeners_[ref];
            for (const auto& listener : holder) {
                listener->OnRouterPageStateChange(abilityPageInfo);
            }
            break;
        }
    }

    auto currentId = Container::CurrentId();
    auto iter = specifiedRouterPageListeners_.find(currentId);
    if (iter == specifiedRouterPageListeners_.end()) {
        return;
    }
    auto holder = iter->second;
    for (const auto& listener : holder) {
        listener->OnRouterPageStateChange(pageInfo);
    }
}

// UIObserver.on(type: "densityUpdate", uiContext | null, callback)
// register a listener on current page
void UIObserver::RegisterDensityCallback(
    int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedDensityListeners_.find(uiContextInstanceId);
    if (iter == specifiedDensityListeners_.end()) {
        specifiedDensityListeners_.emplace(
            uiContextInstanceId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

// UIObserver.off(type: "densityUpdate", uiContext | null, callback)
void UIObserver::UnRegisterDensityCallback(int32_t uiContextInstanceId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedDensityListeners_.find(uiContextInstanceId);
    if (iter == specifiedDensityListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (callback == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
}

void UIObserver::HandleDensityChange(NG::AbilityContextInfo& info, double density)
{
    auto currentId = Container::CurrentId();
    auto iter = specifiedDensityListeners_.find(currentId);
    if (iter == specifiedDensityListeners_.end()) {
        return;
    }
    SafeIterateListeners(iter->second, &UIObserverListener::OnDensityChange, density);
}

void UIObserver::HandDrawCommandSendChange()
{
    auto currentId = Container::CurrentId();
    if (specifiedDrawListeners_.find(currentId) == specifiedDrawListeners_.end()) {
        return;
    }
    SafeIterateListeners(specifiedDrawListeners_[currentId], &UIObserverListener::OnDrawOrLayout);
}

void UIObserver::HandLayoutDoneChange()
{
    auto currentId = Container::CurrentId();
    if (specifiedLayoutListeners_.find(currentId) == specifiedLayoutListeners_.end()) {
        return;
    }
    SafeIterateListeners(specifiedLayoutListeners_[currentId], &UIObserverListener::OnDrawOrLayout);
}

/**
 * observer.on('navDestinationSwitch', context: UIAbilityContext, callback)
 * observer.on('navDestinationSwitch', context: UIAbilityContext, { navigationId: navId }, callback)
 */
void UIObserver::RegisterNavDestinationSwitchCallback(napi_env env, napi_value uiAbilityContext,
    const std::optional<std::string>& navigationId, const std::shared_ptr<UIObserverListener>& listener)
{
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto& listenerPair : abilityUIContextNavDesSwitchListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = infosForNavDesSwitch_[ref];
        if (!info.IsEqual(localInfo)) {
            continue;
        }

        auto& listenersMap = listenerPair.second;
        auto it = listenersMap.find(navigationId);
        if (it == listenersMap.end()) {
            listenersMap[navigationId] = std::list<std::shared_ptr<UIObserverListener>>({listener});
            return;
        }
        if (std::find(it->second.begin(), it->second.end(), listener) == it->second.end()) {
            it->second.emplace_back(listener);
        }
        return;
    }
    napi_ref newRef = nullptr;
    napi_create_reference(env, uiAbilityContext, 1, &newRef);
    NavIdAndListenersMap listenersMap;
    listenersMap.emplace(navigationId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
    abilityUIContextNavDesSwitchListeners_[newRef] = listenersMap;
    infosForNavDesSwitch_[newRef] = info;
}

/**
 * UIObserver.on('navDestinationSwitch', { navigationId: navId }, callback)
 * UIObserver.on('navDestinationSwitch', callback)
 * observer.on('navDestinationSwitch', context: UIContext, { navigationId?: navId }, callback)
 */
void UIObserver::RegisterNavDestinationSwitchCallback(int32_t uiContextInstanceId,
    const std::optional<std::string>& navigationId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto listenersMapIter = uiContextNavDesSwitchListeners_.find(uiContextInstanceId);
    if (listenersMapIter == uiContextNavDesSwitchListeners_.end()) {
        NavIdAndListenersMap listenersMap;
        listenersMap.emplace(navigationId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        uiContextNavDesSwitchListeners_[uiContextInstanceId] = listenersMap;
        return;
    }

    auto& listenersMap = listenersMapIter->second;
    auto it = listenersMap.find(navigationId);
    if (it == listenersMap.end()) {
        listenersMap[navigationId] = std::list<std::shared_ptr<UIObserverListener>>({listener});
        return;
    }

    if (std::find(it->second.begin(), it->second.end(), listener) == it->second.end()) {
        it->second.emplace_back(listener);
    }
}

/**
 * observer.off('navDestinationSwitch', context: AbilityUIContext})
 * observer.off('navDestinationSwitch', context: AbilityUIContext, callback })
 * observer.off('navDestinationSwitch', context: AbilityUIContext, { navigationId: navId } })
 * observer.off('navDestinationSwitch', context: AbilityUIContext, { navigationId: navId }, callback })
 */
void UIObserver::UnRegisterNavDestinationSwitchCallback(napi_env env, napi_value uiAbilityContext,
    const std::optional<std::string>& navigationId, napi_value callback)
{
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityUIContextNavDesSwitchListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = infosForNavDesSwitch_[ref];
        if (!info.IsEqual(localInfo)) {
            continue;
        }

        auto& listenersMap = listenerPair.second;
        auto it = listenersMap.find(navigationId);
        if (it == listenersMap.end()) {
            return;
        }
        auto& listeners = it->second;
        if (callback == nullptr) {
            listeners.clear();
        } else {
            listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                    return registeredListener->NapiEqual(callback);
                }), listeners.end());
        }
        if (listeners.empty()) {
            listenersMap.erase(it);
        }
        if (listenersMap.empty()) {
            infosForNavDesSwitch_.erase(ref);
            abilityUIContextNavDesSwitchListeners_.erase(ref);
            napi_delete_reference(env, ref);
        }
        return;
    }
}

/**
 * observer.off('navDestinationSwitch', context: UIContext})
 * observer.off('navDestinationSwitch', context: UIContext, callback })
 * observer.off('navDestinationSwitch', context: UIContext, { navigationId: navId })
 * observer.off('navDestinationSwitch', context: UIContext, { navigationId: navId }, callback )
 * UIObserver.off('navDestinationSwitch')
 * UIObserver.off('navDestinationSwitch', callback)
 * UIObserver.off('navDestinationSwitch', { navigationId: navId })
 * UIObserver.off('navDestinationSwitch', { navigationId: navId }, callback )
 */
void UIObserver::UnRegisterNavDestinationSwitchCallback(int32_t uiContextInstanceId,
    const std::optional<std::string>& navigationId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto listenersMapIter = uiContextNavDesSwitchListeners_.find(uiContextInstanceId);
    if (listenersMapIter == uiContextNavDesSwitchListeners_.end()) {
        return;
    }
    auto& listenersMap = listenersMapIter->second;
    auto it = listenersMap.find(navigationId);
    if (it == listenersMap.end()) {
        return;
    }
    auto& listeners = it->second;
    if (callback == nullptr) {
        listeners.clear();
    } else {
        listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }), listeners.end());
    }
    if (listeners.empty()) {
        listenersMap.erase(it);
    }
    if (listenersMap.empty()) {
        uiContextNavDesSwitchListeners_.erase(listenersMapIter);
    }
}

void UIObserver::HandleNavDestinationSwitch(
    const NG::AbilityContextInfo& info, NG::NavDestinationSwitchInfo& switchInfo)
{
    HandleAbilityUIContextNavDestinationSwitch(info, switchInfo);
    HandleUIContextNavDestinationSwitch(switchInfo);
}

void UIObserver::HandleAbilityUIContextNavDestinationSwitch(
    const NG::AbilityContextInfo& info, NG::NavDestinationSwitchInfo& switchInfo)
{
    napi_value uiContextBackup = switchInfo.context;
    for (auto listenerPair : abilityUIContextNavDesSwitchListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = infosForNavDesSwitch_[ref];
        if (!info.IsEqual(localInfo)) {
            continue;
        }

        auto env = GetCurrentNapiEnv();
        napi_value abilityContext = nullptr;
        napi_get_reference_value(env, ref, &abilityContext);

        switchInfo.context = abilityContext;
        auto listenersMap = listenerPair.second;
        HandleListenersWithEmptyNavigationId(listenersMap, switchInfo);
        HandleListenersWithSpecifiedNavigationId(listenersMap, switchInfo);
        break;
    }
    switchInfo.context = uiContextBackup;
}

void UIObserver::HandleUIContextNavDestinationSwitch(const NG::NavDestinationSwitchInfo& switchInfo)
{
    auto currentId = Container::CurrentId();
    auto listenersMapIter = uiContextNavDesSwitchListeners_.find(currentId);
    if (listenersMapIter == uiContextNavDesSwitchListeners_.end()) {
        return;
    }
    auto listenersMap = listenersMapIter->second;
    HandleListenersWithEmptyNavigationId(listenersMap, switchInfo);
    HandleListenersWithSpecifiedNavigationId(listenersMap, switchInfo);
}

void UIObserver::HandleListenersWithEmptyNavigationId(
    const NavIdAndListenersMap& listenersMap, const NG::NavDestinationSwitchInfo& switchInfo)
{
    std::optional<std::string> navId;
    auto it = listenersMap.find(navId);
    if (it != listenersMap.end()) {
        const auto listeners = it->second;
        for (const auto& listener : listeners) {
            listener->OnNavDestinationSwitch(switchInfo);
        }
    }
}

void UIObserver::HandleListenersWithSpecifiedNavigationId(
    const NavIdAndListenersMap& listenersMap, const NG::NavDestinationSwitchInfo& switchInfo)
{
    std::string navigationId;
    if (switchInfo.from.has_value()) {
        navigationId = switchInfo.from.value().navigationId;
    } else if (switchInfo.to.has_value()) {
        navigationId = switchInfo.to.value().navigationId;
    }
    if (!navigationId.empty()) {
        std::optional<std::string> navId{navigationId};
        auto it = listenersMap.find(navId);
        if (it != listenersMap.end()) {
            const auto listeners = it->second;
            for (const auto& listener : listeners) {
                listener->OnNavDestinationSwitch(switchInfo);
            }
        }
    }
}

void UIObserver::RegisterWillClickCallback(
    napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextWillClickListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = willClickInfos_[ref];
        if (info.IsEqual(localInfo)) {
            auto& holder = abilityContextWillClickListeners_[ref];
            if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
                napi_close_handle_scope(env, scope);
                return;
            }
            holder.emplace_back(listener);
            napi_close_handle_scope(env, scope);
            return;
        }
    }
    napi_ref newRef = nullptr;
    napi_create_reference(env, uiAbilityContext, 1, &newRef);
    abilityContextWillClickListeners_[newRef] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
    willClickInfos_[newRef] = info;
    napi_close_handle_scope(env, scope);
}

void UIObserver::RegisterWillClickCallback(
    int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedWillClickListeners_.find(uiContextInstanceId);
    if (iter == specifiedWillClickListeners_.end()) {
        specifiedWillClickListeners_.emplace(
            uiContextInstanceId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

void UIObserver::UnRegisterWillClickCallback(napi_env env, napi_value uiAbilityContext, napi_value callback)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextWillClickListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = willClickInfos_[ref];
        if (!info.IsEqual(localInfo)) {
            continue;
        }
        auto& holder = abilityContextWillClickListeners_[listenerPair.first];
        if (callback == nullptr) {
            holder.clear();
        } else {
            holder.erase(
                std::remove_if(
                    holder.begin(),
                    holder.end(),
                    [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                        return registeredListener->NapiEqual(callback);
                    }),
                holder.end());
        }
        if (holder.empty()) {
            willClickInfos_.erase(ref);
            abilityContextWillClickListeners_.erase(ref);
            napi_delete_reference(env, ref);
        }
    }
    napi_close_handle_scope(env, scope);
}

void UIObserver::UnRegisterWillClickCallback(int32_t uiContextInstanceId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedWillClickListeners_.find(uiContextInstanceId);
    if (iter == specifiedWillClickListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (callback == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
}

void UIObserver::HandleWillClick(NG::AbilityContextInfo& info, const GestureEvent& gestureEventInfo,
    const ClickInfo& clickInfo, const RefPtr<NG::FrameNode>& frameNode)
{
    auto env = GetCurrentNapiEnv();
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    for (auto listenerPair : abilityContextWillClickListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = willClickInfos_[ref];
        if (info.IsEqual(localInfo)) {
            napi_value abilityContext = nullptr;
            napi_get_reference_value(env, ref, &abilityContext);

            auto& holder = abilityContextWillClickListeners_[ref];
            for (const auto& listener : holder) {
                listener->OnWillClick(gestureEventInfo, clickInfo, frameNode);
            }
            break;
        }
    }

    auto currentId = Container::CurrentId();
    auto iter = specifiedWillClickListeners_.find(currentId);
    if (iter == specifiedWillClickListeners_.end()) {
        napi_close_handle_scope(env, scope);
        return;
    }
    auto holder = iter->second;
    for (const auto& listener : holder) {
        listener->OnWillClick(gestureEventInfo, clickInfo, frameNode);
    }
    napi_close_handle_scope(env, scope);
}

void UIObserver::RegisterDidClickCallback(
    napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextDidClickListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = didClickInfos_[ref];
        if (info.IsEqual(localInfo)) {
            auto& holder = abilityContextDidClickListeners_[ref];
            if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
                napi_close_handle_scope(env, scope);
                return;
            }
            holder.emplace_back(listener);
            napi_close_handle_scope(env, scope);
            return;
        }
    }
    napi_ref newRef = nullptr;
    napi_create_reference(env, uiAbilityContext, 1, &newRef);
    abilityContextDidClickListeners_[newRef] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
    didClickInfos_[newRef] = info;
    napi_close_handle_scope(env, scope);
}

void UIObserver::RegisterDidClickCallback(
    int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedDidClickListeners_.find(uiContextInstanceId);
    if (iter == specifiedDidClickListeners_.end()) {
        specifiedDidClickListeners_.emplace(
            uiContextInstanceId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

void UIObserver::UnRegisterDidClickCallback(napi_env env, napi_value uiAbilityContext, napi_value callback)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextDidClickListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = didClickInfos_[ref];
        if (!info.IsEqual(localInfo)) {
            continue;
        }
        auto& holder = abilityContextDidClickListeners_[listenerPair.first];
        if (callback == nullptr) {
            holder.clear();
        } else {
            holder.erase(
                std::remove_if(
                    holder.begin(),
                    holder.end(),
                    [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                        return registeredListener->NapiEqual(callback);
                    }),
                holder.end());
        }
        if (holder.empty()) {
            didClickInfos_.erase(ref);
            abilityContextDidClickListeners_.erase(ref);
            napi_delete_reference(env, ref);
        }
    }
    napi_close_handle_scope(env, scope);
}

void UIObserver::UnRegisterDidClickCallback(int32_t uiContextInstanceId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedDidClickListeners_.find(uiContextInstanceId);
    if (iter == specifiedDidClickListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (callback == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
}

void UIObserver::HandleDidClick(NG::AbilityContextInfo& info, const GestureEvent& gestureEventInfo,
    const ClickInfo& clickInfo, const RefPtr<NG::FrameNode>& frameNode)
{
    auto env = GetCurrentNapiEnv();
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    for (auto listenerPair : abilityContextDidClickListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = didClickInfos_[ref];
        if (info.IsEqual(localInfo)) {
            napi_value abilityContext = nullptr;
            napi_get_reference_value(env, ref, &abilityContext);

            auto& holder = abilityContextDidClickListeners_[ref];
            for (const auto& listener : holder) {
                listener->OnDidClick(gestureEventInfo, clickInfo, frameNode);
            }
            break;
        }
    }

    auto currentId = Container::CurrentId();
    auto iter = specifiedDidClickListeners_.find(currentId);
    if (iter == specifiedDidClickListeners_.end()) {
        napi_close_handle_scope(env, scope);
        return;
    }
    auto holder = iter->second;
    for (const auto& listener : holder) {
        listener->OnDidClick(gestureEventInfo, clickInfo, frameNode);
    }
    napi_close_handle_scope(env, scope);
}

void UIObserver::RegisterBeforePanStartCallback(
    napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextBeforePanStartListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = beforePanStartInfos_[ref];
        if (info.IsEqual(localInfo)) {
            auto& holder = listenerPair.second;
            if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
                napi_close_handle_scope(env, scope);
                return;
            }
            holder.emplace_back(listener);
            napi_close_handle_scope(env, scope);
            return;
        }
    }
    napi_ref newRef = nullptr;
    napi_create_reference(env, uiAbilityContext, 1, &newRef);
    abilityContextBeforePanStartListeners_[newRef] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
    beforePanStartInfos_[newRef] = info;
    napi_close_handle_scope(env, scope);
}

void UIObserver::RegisterBeforePanStartCallback(
    int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedBeforePanStartListeners_.find(uiContextInstanceId);
    if (iter == specifiedBeforePanStartListeners_.end()) {
        specifiedBeforePanStartListeners_.emplace(
            uiContextInstanceId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

void UIObserver::UnRegisterBeforePanStartCallback(napi_env env, napi_value uiAbilityContext, napi_value callback)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextBeforePanStartListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = beforePanStartInfos_[ref];
        if (!info.IsEqual(localInfo)) {
            continue;
        }
        auto& holder = listenerPair.second;
        if (callback == nullptr) {
            holder.clear();
        } else {
            holder.erase(
                std::remove_if(
                    holder.begin(),
                    holder.end(),
                    [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                        return registeredListener->NapiEqual(callback);
                    }),
                holder.end());
        }
        if (holder.empty()) {
            beforePanStartInfos_.erase(ref);
            abilityContextBeforePanStartListeners_.erase(ref);
            napi_delete_reference(env, ref);
        }
    }
    napi_close_handle_scope(env, scope);
}

void UIObserver::UnRegisterBeforePanStartCallback(int32_t uiContextInstanceId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedBeforePanStartListeners_.find(uiContextInstanceId);
    if (iter == specifiedBeforePanStartListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (callback == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
}

void UIObserver::RegisterBeforePanEndCallback(
    napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextBeforePanEndListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = beforePanEndInfos_[ref];
        if (info.IsEqual(localInfo)) {
            auto& holder = listenerPair.second;
            if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
                napi_close_handle_scope(env, scope);
                return;
            }
            holder.emplace_back(listener);
            napi_close_handle_scope(env, scope);
            return;
        }
    }
    napi_ref newRef = nullptr;
    napi_create_reference(env, uiAbilityContext, 1, &newRef);
    abilityContextBeforePanEndListeners_[newRef] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
    beforePanEndInfos_[newRef] = info;
    napi_close_handle_scope(env, scope);
}

void UIObserver::RegisterBeforePanEndCallback(
    int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedBeforePanEndListeners_.find(uiContextInstanceId);
    if (iter == specifiedBeforePanEndListeners_.end()) {
        specifiedBeforePanEndListeners_.emplace(
            uiContextInstanceId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

void UIObserver::UnRegisterBeforePanEndCallback(napi_env env, napi_value uiAbilityContext, napi_value callback)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextBeforePanEndListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = beforePanEndInfos_[ref];
        if (!info.IsEqual(localInfo)) {
            continue;
        }
        auto& holder = listenerPair.second;
        if (callback == nullptr) {
            holder.clear();
        } else {
            holder.erase(
                std::remove_if(
                    holder.begin(),
                    holder.end(),
                    [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                        return registeredListener->NapiEqual(callback);
                    }),
                holder.end());
        }
        if (holder.empty()) {
            beforePanEndInfos_.erase(ref);
            abilityContextBeforePanEndListeners_.erase(ref);
            napi_delete_reference(env, ref);
        }
    }
    napi_close_handle_scope(env, scope);
}

void UIObserver::UnRegisterBeforePanEndCallback(int32_t uiContextInstanceId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedBeforePanEndListeners_.find(uiContextInstanceId);
    if (iter == specifiedBeforePanEndListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (callback == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
}

void UIObserver::RegisterAfterPanStartCallback(
    napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextAfterPanStartListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = afterPanStartInfos_[ref];
        if (info.IsEqual(localInfo)) {
            auto& holder = listenerPair.second;
            if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
                napi_close_handle_scope(env, scope);
                return;
            }
            holder.emplace_back(listener);
            napi_close_handle_scope(env, scope);
            return;
        }
    }
    napi_ref newRef = nullptr;
    napi_create_reference(env, uiAbilityContext, 1, &newRef);
    abilityContextAfterPanStartListeners_[newRef] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
    afterPanStartInfos_[newRef] = info;
    napi_close_handle_scope(env, scope);
}

void UIObserver::RegisterAfterPanStartCallback(
    int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedAfterPanStartListeners_.find(uiContextInstanceId);
    if (iter == specifiedAfterPanStartListeners_.end()) {
        specifiedAfterPanStartListeners_.emplace(
            uiContextInstanceId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

void UIObserver::UnRegisterAfterPanStartCallback(napi_env env, napi_value uiAbilityContext, napi_value callback)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextAfterPanStartListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = afterPanStartInfos_[ref];
        if (!info.IsEqual(localInfo)) {
            continue;
        }
        auto& holder = listenerPair.second;
        if (callback == nullptr) {
            holder.clear();
        } else {
            holder.erase(
                std::remove_if(
                    holder.begin(),
                    holder.end(),
                    [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                        return registeredListener->NapiEqual(callback);
                    }),
                holder.end());
        }
        if (holder.empty()) {
            afterPanStartInfos_.erase(ref);
            abilityContextAfterPanStartListeners_.erase(ref);
            napi_delete_reference(env, ref);
        }
    }
    napi_close_handle_scope(env, scope);
}

void UIObserver::UnRegisterAfterPanStartCallback(int32_t uiContextInstanceId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedAfterPanStartListeners_.find(uiContextInstanceId);
    if (iter == specifiedAfterPanStartListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (callback == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
}

void UIObserver::RegisterAfterPanEndCallback(
    napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextAfterPanEndListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = afterPanEndInfos_[ref];
        if (info.IsEqual(localInfo)) {
            auto& holder = listenerPair.second;
            if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
                napi_close_handle_scope(env, scope);
                return;
            }
            holder.emplace_back(listener);
            napi_close_handle_scope(env, scope);
            return;
        }
    }
    napi_ref newRef = nullptr;
    napi_create_reference(env, uiAbilityContext, 1, &newRef);
    abilityContextAfterPanEndListeners_[newRef] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
    afterPanEndInfos_[newRef] = info;
    napi_close_handle_scope(env, scope);
}

void UIObserver::RegisterAfterPanEndCallback(
    int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedAfterPanEndListeners_.find(uiContextInstanceId);
    if (iter == specifiedAfterPanEndListeners_.end()) {
        specifiedAfterPanEndListeners_.emplace(
            uiContextInstanceId, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

void UIObserver::UnRegisterAfterPanEndCallback(napi_env env, napi_value uiAbilityContext, napi_value callback)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }
    NG::AbilityContextInfo info;
    GetAbilityInfos(env, uiAbilityContext, info);
    for (auto listenerPair : abilityContextAfterPanEndListeners_) {
        auto ref = listenerPair.first;
        auto localInfo = afterPanEndInfos_[ref];
        if (!info.IsEqual(localInfo)) {
            continue;
        }
        auto& holder = listenerPair.second;
        if (callback == nullptr) {
            holder.clear();
        } else {
            holder.erase(
                std::remove_if(
                    holder.begin(),
                    holder.end(),
                    [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                        return registeredListener->NapiEqual(callback);
                    }),
                holder.end());
        }
        if (holder.empty()) {
            afterPanEndInfos_.erase(ref);
            abilityContextAfterPanEndListeners_.erase(ref);
            napi_delete_reference(env, ref);
        }
    }
    napi_close_handle_scope(env, scope);
}

void UIObserver::UnRegisterAfterPanEndCallback(int32_t uiContextInstanceId, napi_value callback)
{
    if (uiContextInstanceId == 0) {
        uiContextInstanceId = Container::CurrentId();
    }
    auto iter = specifiedAfterPanEndListeners_.find(uiContextInstanceId);
    if (iter == specifiedAfterPanEndListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (callback == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
}

void UIObserver::HandlePanGestureAccept(NG::AbilityContextInfo& info, const GestureEvent& gestureEventInfo,
    const RefPtr<NG::PanRecognizer>& current, const RefPtr<NG::FrameNode>& frameNode,
    const NG::PanGestureInfo& panGestureInfo)
{
    auto env = GetCurrentNapiEnv();
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }

    auto [listeners, specifiedListeners] = GetPanGestureListeners(panGestureInfo);
    if (listeners.empty() && specifiedListeners.empty()) {
        napi_close_handle_scope(env, scope);
        return;
    }
    for (auto& listenerPair : listeners) {
        auto ref = listenerPair.first;
        auto localInfo = PanGestureInfos_[ref];
        if (info.IsEqual(localInfo)) {
            napi_value abilityContext = nullptr;
            napi_get_reference_value(env, ref, &abilityContext);

            auto& holder = listenerPair.second;
            for (const auto& listener : holder) {
                listener->OnPanGestureStateChange(gestureEventInfo, current, frameNode);
            }
            break;
        }
    }

    auto currentId = Container::CurrentId();
    auto iter = specifiedListeners.find(currentId);
    if (iter == specifiedListeners.end()) {
        napi_close_handle_scope(env, scope);
        return;
    }
    auto holder = iter->second;
    for (const auto& listener : holder) {
        listener->OnPanGestureStateChange(gestureEventInfo, current, frameNode);
    }
    napi_close_handle_scope(env, scope);
}

UIObserver::PanGestureListenersPair UIObserver::GetPanGestureListeners(const NG::PanGestureInfo& panGestureInfo)
{
    static std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>> emptyListeners;
    static std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>> emptySpecifiedListeners;
    if (panGestureInfo.callbackState == NG::CurrentCallbackState::START &&
        panGestureInfo.gestureState == NG::PanGestureState::BEFORE) {
        return { abilityContextBeforePanStartListeners_, specifiedBeforePanStartListeners_ };
    } else if (panGestureInfo.callbackState == NG::CurrentCallbackState::END &&
               panGestureInfo.gestureState == NG::PanGestureState::BEFORE) {
        return { abilityContextBeforePanEndListeners_, specifiedBeforePanEndListeners_ };
    } else if (panGestureInfo.callbackState == NG::CurrentCallbackState::START &&
               panGestureInfo.gestureState == NG::PanGestureState::AFTER) {
        return { abilityContextAfterPanStartListeners_, specifiedAfterPanStartListeners_ };
    } else if (panGestureInfo.callbackState == NG::CurrentCallbackState::END &&
               panGestureInfo.gestureState == NG::PanGestureState::AFTER) {
        return { abilityContextAfterPanEndListeners_, specifiedAfterPanEndListeners_ };
    } else {
        return { emptyListeners, emptySpecifiedListeners };
    }
}

void UIObserver::RegisterNodeRenderStateChangeCallback(RefPtr<NG::FrameNode> frameNode,
    const std::shared_ptr<UIObserverListener>& listener, const RefPtr<NG::NodeRenderStatusMonitor>& monitor)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(monitor);
    auto frameNodePtr = AceType::RawPtr(frameNode);

    auto iter = specifiedNodeRenderStateListeners_.find(frameNodePtr);
    if (iter == specifiedNodeRenderStateListeners_.end()) {
        auto nodeRenderStatusHandleFunc = [](NG::FrameNode* frameNode, NG::NodeRenderState state,
                                              NG::RenderMonitorReason reason) {
            CHECK_NULL_VOID(frameNode);
            auto iter = specifiedNodeRenderStateListeners_.find(frameNode);
            if (iter == specifiedNodeRenderStateListeners_.end()) {
                return;
            }
            CHECK_NULL_VOID(iter->second);
            for (const auto& listener : iter->second->listeners) {
                listener->OnNodeRenderStateChange(frameNode, state);
            }
            if (reason == NG::RenderMonitorReason::NODE_RELEASE) {
                specifiedNodeRenderStateListeners_.erase(frameNode);
            }
        };
        auto result = monitor->RegisterNodeRenderStatusListener(
            frameNodePtr, std::move(nodeRenderStatusHandleFunc), NG::MonitorSourceType::OBSERVER);
        if (result.id != NG::MONITOR_INVALID_ID) {
            specifiedNodeRenderStateListeners_.emplace(
                frameNodePtr, std::make_shared<NodeRenderListener>(
                                    result.id, std::list<std::shared_ptr<UIObserverListener>>({ listener })));
        }
        listener->OnNodeRenderStateChange(frameNodePtr, result.state);
        return;
    }
    CHECK_NULL_VOID(iter->second);
    auto& holder = iter->second->listeners;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
    listener->OnNodeRenderStateChange(frameNodePtr, monitor->GetNodeCurrentRenderState(frameNodePtr));
}

void UIObserver::UnRegisterNodeRenderStateChangeCallback(
    RefPtr<NG::FrameNode> frameNode, napi_value callback, const RefPtr<NG::NodeRenderStatusMonitor>& monitor)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(monitor);
    auto frameNodePtr = AceType::RawPtr(frameNode);
    auto iter = specifiedNodeRenderStateListeners_.find(frameNodePtr);
    if (iter == specifiedNodeRenderStateListeners_.end()) {
        return;
    }
    CHECK_NULL_VOID(iter->second);
    auto& holder = iter->second->listeners;
    if (callback == nullptr) {
        holder.clear();
        specifiedNodeRenderStateListeners_.erase(AceType::RawPtr(frameNode));
        monitor->UnRegisterNodeRenderStatusListener(frameNodePtr, iter->second->id);
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(callback);
            }),
        holder.end());
    if (holder.empty()) {
        specifiedNodeRenderStateListeners_.erase(AceType::RawPtr(frameNode));
        monitor->UnRegisterNodeRenderStatusListener(frameNodePtr, iter->second->id);
    }
}

// UIObserver.on(type: "tabContentState", callback)
// register a global listener without options
void UIObserver::RegisterTabContentStateCallback(const std::shared_ptr<UIObserverListener>& listener)
{
    if (std::find(tabContentStateListeners_.begin(), tabContentStateListeners_.end(), listener) !=
        tabContentStateListeners_.end()) {
        return;
    }
    tabContentStateListeners_.emplace_back(listener);
}

// UIObserver.on(type: "tabContentState", options, callback)
// register a listener on a specified tabContentState
void UIObserver::RegisterTabContentStateCallback(
    const std::string& id, const std::shared_ptr<UIObserverListener>& listener)
{
    auto iter = specifiedTabContentStateListeners_.find(id);
    if (iter == specifiedTabContentStateListeners_.end()) {
        specifiedTabContentStateListeners_.emplace(id, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        return;
    }
    auto& holder = iter->second;
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

// UIObserver.off(type: "tabContentState", callback)
void UIObserver::UnRegisterTabContentStateCallback(napi_value cb)
{
    if (cb == nullptr) {
        tabContentStateListeners_.clear();
        return;
    }

    tabContentStateListeners_.erase(
        std::remove_if(
            tabContentStateListeners_.begin(),
            tabContentStateListeners_.end(),
            [cb](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(cb);
            }),
        tabContentStateListeners_.end()
    );
}

// UIObserver.off(type: "tabContentState", options, callback)
void UIObserver::UnRegisterTabContentStateCallback(const std::string& id, napi_value cb)
{
    auto iter = specifiedTabContentStateListeners_.find(id);
    if (iter == specifiedTabContentStateListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    if (cb == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [cb](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener->NapiEqual(cb);
            }),
        holder.end()
    );
}

void UIObserver::HandleTabContentStateChange(const NG::TabContentInfo& tabContentInfo)
{
    for (const auto& listener : tabContentStateListeners_) {
        listener->OnTabContentStateChange(tabContentInfo);
    }

    auto iter = specifiedTabContentStateListeners_.find(tabContentInfo.id);
    if (iter == specifiedTabContentStateListeners_.end()) {
        return;
    }

    auto& holder = iter->second;

    for (const auto& listener : holder) {
        listener->OnTabContentStateChange(tabContentInfo);
    }
}

void UIObserver::GetAbilityInfos(napi_env env, napi_value abilityContext, NG::AbilityContextInfo& info)
{
    if (!env || !abilityContext) {
        return;
    }
    napi_value napiInfo = nullptr;
    napi_get_named_property(env, abilityContext, "abilityInfo", &napiInfo);
    CHECK_NULL_VOID(napiInfo);
    napi_value name = nullptr;
    napi_get_named_property(env, napiInfo, "name", &name);
    ParseStringFromNapi(env, name, info.name);
    napi_get_named_property(env, napiInfo, "bundleName", &name);
    ParseStringFromNapi(env, name, info.bundleName);
    napi_get_named_property(env, napiInfo, "moduleName", &name);
    ParseStringFromNapi(env, name, info.moduleName);
}

bool UIObserver::ParseStringFromNapi(napi_env env, napi_value val, std::string& str)
{
    if (!val || !MatchValueType(env, val, napi_string)) {
        return false;
    }
    size_t len = 0;
    napi_get_value_string_utf8(env, val, nullptr, 0, &len);
    std::unique_ptr<char[]> result = std::make_unique<char[]>(len + 1);
    napi_get_value_string_utf8(env, val, result.get(), len + 1, &len);
    str = result.get();
    return true;
}

bool UIObserver::MatchValueType(napi_env env, napi_value value, napi_valuetype targetType)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    return valueType == targetType;
}

napi_env UIObserver::GetCurrentNapiEnv()
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);
    return reinterpret_cast<napi_env>(nativeEngine);
}
} // namespace OHOS::Ace::Napi
