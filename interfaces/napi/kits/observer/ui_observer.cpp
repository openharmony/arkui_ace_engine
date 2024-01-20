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

#include <algorithm>

namespace OHOS::Ace::Napi {
std::list<std::shared_ptr<UIObserverListener>> UIObserver::unspecifiedNavigationListeners_;
std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedCNavigationListeners_;

std::unordered_map<napi_ref, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::abilityContextRouterPageListeners_;
std::unordered_map<uint32_t, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedRouterPageListeners_;
std::unordered_map<napi_ref, NG::AbilityContextInfo> UIObserver::infos_;

// UIObserver.on(type: "navDestinationUpdate", callback)
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
    if (specifiedCNavigationListeners_.find(navigationId) == specifiedCNavigationListeners_.end()) {
        specifiedCNavigationListeners_[navigationId] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
        return;
    }
    auto& holder = specifiedCNavigationListeners_[navigationId];
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
    if (specifiedCNavigationListeners_.find(navigationId) == specifiedCNavigationListeners_.end()) {
        return;
    }
    auto& holder = specifiedCNavigationListeners_[navigationId];
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

void UIObserver::HandleNavigationStateChange(std::string navigationId, std::string navDestinationName,
                                             NG::NavDestinationState state)
{
    for (const auto& listener : unspecifiedNavigationListeners_) {
        listener->OnNavigationStateChange(navigationId, navDestinationName, state);
    }

    if (specifiedCNavigationListeners_.find(navigationId) ==
        specifiedCNavigationListeners_.end()) {
        return;
    }

    auto& holder = specifiedCNavigationListeners_[navigationId];

    for (const auto& listener : holder) {
        listener->OnNavigationStateChange(navigationId, navDestinationName, state);
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
} // namespace OHOS::Ace::Napi
