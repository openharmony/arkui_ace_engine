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

#ifndef FOUNDATION_ACE_INTERFACES_OBSERVER_H
#define FOUNDATION_ACE_INTERFACES_OBSERVER_H

#include <list>
#include <optional>
#include <unordered_map>
#include <string>

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

#include "ui_observer_listener.h"

#include "core/components_ng/base/observer_handler.h"

namespace OHOS::Ace::Napi {
class UIObserver {
public:
    static void RegisterNavigationCallback(const std::shared_ptr<UIObserverListener>& listener);
    static void RegisterNavigationCallback(
        std::string navigationId, const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterNavigationCallback(napi_value cb);
    static void UnRegisterNavigationCallback(std::string navigationId, napi_value cb);
    static void HandleNavigationStateChange(const NG::NavDestinationInfo& info);

    static void RegisterScrollEventCallback(const std::shared_ptr<UIObserverListener>& listener);
    static void RegisterScrollEventCallback(
        const std::string& id, const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterScrollEventCallback(napi_value cb);
    static void UnRegisterScrollEventCallback(const std::string& id, napi_value cb);
    static void HandleScrollEventStateChange(const std::string& id, int32_t uniqueId,
        NG::ScrollEventType eventType, float offset);

    static void RegisterRouterPageCallback(
        napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener);
    static void RegisterRouterPageCallback(
        int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterRouterPageCallback(napi_env env, napi_value uiAbilityContext, napi_value callback);
    static void UnRegisterRouterPageCallback(int32_t uiContextInstanceId, napi_value callback);
    static void HandleRouterPageStateChange(NG::AbilityContextInfo& info, const NG::RouterPageInfoNG& pageInfo);

    static void RegisterDensityCallback(
        int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterDensityCallback(int32_t uiContextInstanceId, napi_value callback);
    static void HandleDensityChange(NG::AbilityContextInfo& info, double density);
    static void RegisterDrawCallback(int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterDrawCallback(int32_t uiContextInstanceId, napi_value callback);
    static void RegisterLayoutCallback(
        int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterLayoutCallback(int32_t uiContextInstanceId, napi_value callback);
    static void HandDrawCommandSendChange();
    static void HandLayoutDoneChange();

    static void RegisterNavDestinationSwitchCallback(
        napi_env env, napi_value uiAbilityContext, const std::optional<std::string>& navigationId,
        const std::shared_ptr<UIObserverListener>& listener);
    static void RegisterNavDestinationSwitchCallback(
        int32_t uiContextInstanceId, const std::optional<std::string>& navigationId,
        const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterNavDestinationSwitchCallback(napi_env env, napi_value uiAbilityContext,
        const std::optional<std::string>& navigationId, napi_value callback);
    static void UnRegisterNavDestinationSwitchCallback(int32_t uiContextInstanceId,
        const std::optional<std::string>& navigationId, napi_value callback);
    static void HandleNavDestinationSwitch(
        const NG::AbilityContextInfo& info, NG::NavDestinationSwitchInfo& switchInfo);

    static void RegisterWillClickCallback(
        napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener);
    static void RegisterWillClickCallback(
        int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterWillClickCallback(napi_env env, napi_value uiAbilityContext, napi_value callback);
    static void UnRegisterWillClickCallback(int32_t uiContextInstanceId, napi_value callback);
    static void HandleWillClick(NG::AbilityContextInfo& info, const GestureEvent& gestureEventInfo,
        const ClickInfo& clickInfo, const RefPtr<NG::FrameNode>& frameNode);
    
    static void RegisterDidClickCallback(
        napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener);
    static void RegisterDidClickCallback(
        int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterDidClickCallback(napi_env env, napi_value uiAbilityContext, napi_value callback);
    static void UnRegisterDidClickCallback(int32_t uiContextInstanceId, napi_value callback);
    static void HandleDidClick(NG::AbilityContextInfo& info, const GestureEvent& gestureEventInfo,
        const ClickInfo& clickInfo, const RefPtr<NG::FrameNode>& frameNode);

    static void RegisterTabContentStateCallback(const std::shared_ptr<UIObserverListener>& listener);
    static void RegisterTabContentStateCallback(
        const std::string& id, const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterTabContentStateCallback(napi_value cb);
    static void UnRegisterTabContentStateCallback(const std::string& id, napi_value cb);
    static void HandleTabContentStateChange(const NG::TabContentInfo& tabContentInfo);

    static bool ParseStringFromNapi(napi_env env, napi_value val, std::string& str);
    static bool MatchValueType(napi_env env, napi_value value, napi_valuetype targetType);
private:
    static void HandleAbilityUIContextNavDestinationSwitch(
        const NG::AbilityContextInfo& info, NG::NavDestinationSwitchInfo& switchInfo);
    static void HandleUIContextNavDestinationSwitch(const NG::NavDestinationSwitchInfo& switchInfo);
    using NavIdAndListenersMap =
        std::unordered_map<std::optional<std::string>, std::list<std::shared_ptr<UIObserverListener>>>;
    static void HandleListenersWithEmptyNavigationId(
        const NavIdAndListenersMap& listenersMap, const NG::NavDestinationSwitchInfo& switchInfo);
    static void HandleListenersWithSpecifiedNavigationId(
        const NavIdAndListenersMap& listenersMap, const NG::NavDestinationSwitchInfo& switchInfo);
    static void GetAbilityInfos(napi_env env, napi_value abilityContext, NG::AbilityContextInfo& info);
    static napi_env GetCurrentNapiEnv();

    static std::list<std::shared_ptr<UIObserverListener>> unspecifiedNavigationListeners_;
    static std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
        specifiedCNavigationListeners_;
    static std::list<std::shared_ptr<UIObserverListener>> scrollEventListeners_;
    static std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
        specifiedScrollEventListeners_;
    static std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
        abilityContextRouterPageListeners_;
    static std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
        specifiedRouterPageListeners_;
    static std::unordered_map<napi_ref, NG::AbilityContextInfo> infosForRouterPage_;
    static std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
        specifiedDensityListeners_;
    static std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>> specifiedDrawListeners_;
    static std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>> specifiedLayoutListeners_;
    static std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
        abilityContextWillClickListeners_;
    static std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
        specifiedWillClickListeners_;
    static std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
        abilityContextDidClickListeners_;
    static std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
        specifiedDidClickListeners_;
    static std::list<std::shared_ptr<UIObserverListener>> tabContentStateListeners_;
    static std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
        specifiedTabContentStateListeners_;

    static std::unordered_map<napi_ref, NavIdAndListenersMap> abilityUIContextNavDesSwitchListeners_;
    static std::unordered_map<int32_t, NavIdAndListenersMap> uiContextNavDesSwitchListeners_;
    static std::unordered_map<napi_ref, NG::AbilityContextInfo> infosForNavDesSwitch_;
    static std::unordered_map<napi_ref, NG::AbilityContextInfo> willClickInfos_;
    static std::unordered_map<napi_ref, NG::AbilityContextInfo> didClickInfos_;
};
} // namespace OHOS::Ace::Napi
#endif // FOUNDATION_ACE_INTERFACES_OBSERVER_H
