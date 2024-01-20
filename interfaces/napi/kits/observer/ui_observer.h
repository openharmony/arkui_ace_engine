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
    static void HandleNavigationStateChange(
        const std::string& navigationId, const std::string& navDestinationName, NG::NavDestinationState state);

    static void RegisterRouterPageCallback(
        napi_env env, napi_value uiAbilityContext, const std::shared_ptr<UIObserverListener>& listener);
    static void RegisterRouterPageCallback(
        int32_t uiContextInstanceId, const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterRouterPageCallback(napi_env env, napi_value uiAbilityContext, napi_value callback);
    static void UnRegisterRouterPageCallback(int32_t uiContextInstanceId, napi_value callback);
    static void HandleRouterPageStateChange(NG::AbilityContextInfo& info, napi_value context, int32_t index,
        const std::string& name, const std::string& path, NG::RouterPageState state);
    static bool ParseStringFromNapi(napi_env env, napi_value val, std::string& str);
    static bool MatchValueType(napi_env env, napi_value value, napi_valuetype targetType);
private:
    static void GetAbilityInfos(napi_env env, napi_value abilityContext, NG::AbilityContextInfo& info);
    static napi_env GetCurrentNapiEnv();

    static std::list<std::shared_ptr<UIObserverListener>> unspecifiedNavigationListeners_;
    static std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
        specifiedCNavigationListeners_;
    static std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
        abilityContextRouterPageListeners_;
    static std::unordered_map<int32_t, std::list<std::shared_ptr<UIObserverListener>>>
        specifiedRouterPageListeners_;
    static std::unordered_map<napi_ref, NG::AbilityContextInfo> infos_;
};
} // namespace OHOS::Ace::Napi
#endif // FOUNDATION_ACE_INTERFACES_OBSERVER_H
