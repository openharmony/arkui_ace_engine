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
#include "observer.h"

#include <list>

#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

namespace OHOS::Ace::NG {
using namespace Framework;
std::list<std::shared_ptr<UIObserverListener>> UIObserver::unspecifiedNavigationListeners_;
std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedCNavigationListeners_;

void UIObserverHandler::NotifyNavigationStateChange(
    const RefPtr<NavDestinationPattern>& pattern, NavDestinationState state)
{
    LOGE("testtest UIObserverHandler NotifyNavigationStateChange");
    std::string navigationId;
    std::string navDestinationName = pattern->GetName();
    for (const auto& listener : UIObserver::unspecifiedNavigationListeners_) {
        listener->OnNavigationStateChange(navigationId, navDestinationName, state);
    }

    if (UIObserver::specifiedCNavigationListeners_.find(navigationId) ==
        UIObserver::specifiedCNavigationListeners_.end()) {
        return;
    }

    auto holder = UIObserver::specifiedCNavigationListeners_[navigationId];

    for (const auto& listener : holder) {
        listener->OnNavigationStateChange(navigationId, navDestinationName, state);
    }
}

std::shared_ptr<NavDestinationInfo> UIObserverHandler::GetNavigationState(const RefPtr<AceType>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto custom = AceType::DynamicCast<UINode>(node);
    auto parent = custom->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::NAVDESTINATION_CONTENT_ETS_TAG) {
            break;
        }
        parent = parent->GetParent();
    }
    CHECK_NULL_RETURN(parent, nullptr);
    auto nav = AceType::DynamicCast<FrameNode>(parent);
    CHECK_NULL_RETURN(nav, nullptr);
    auto pattern = nav->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return std::make_shared<NavDestinationInfo>(
        "", pattern->GetName(), pattern->GetIsOnShow() ? NavDestinationState::ON_SHOW : NavDestinationState::ON_HIDDEN);
}

void UIObserverListener::OnNavigationStateChange(
    std::string navigationId, std::string navDestinationName, NG::NavDestinationState navState)
{
    LOGE("testtest call OnNavigationStateChange %p", &env_);
    if (!env_ || !callback_) {
        LOGE("testtest no env");
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value id = nullptr;
    napi_value name = nullptr;
    napi_value state = nullptr;
    napi_create_string_utf8(env_, navigationId.c_str(), navigationId.length(), &id);
    napi_create_string_utf8(env_, navDestinationName.c_str(), navDestinationName.length(), &name);
    napi_create_int32(env_, static_cast<int32_t>(navState), &state);
    napi_set_named_property(env_, objValue, "navigationId", id);
    napi_set_named_property(env_, objValue, "name", name);
    napi_set_named_property(env_, objValue, "state", state);
    napi_value argv[] = { objValue };
    LOGE("testtest call napi_call_function");
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
}

void UIObserver::RegisterNavigationCallback(const std::shared_ptr<UIObserverListener>& listener)
{
    if (std::find(unspecifiedNavigationListeners_.begin(), unspecifiedNavigationListeners_.end(), listener) !=
        unspecifiedNavigationListeners_.end()) {
        return;
    }
    unspecifiedNavigationListeners_.emplace_back(listener);
}

void UIObserver::RegisterNavigationCallback(
    std::string navigationId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (specifiedCNavigationListeners_.find(navigationId) == specifiedCNavigationListeners_.end()) {
        specifiedCNavigationListeners_[navigationId] = std::list<std::shared_ptr<UIObserverListener>>({ listener });
        return;
    }
    auto holder = specifiedCNavigationListeners_[navigationId];
    if (std::find(holder.begin(), holder.end(), listener) != holder.end()) {
        return;
    }
    holder.emplace_back(listener);
}

void UIObserver::UnRegisterNavigationCallback(const std::shared_ptr<UIObserverListener>& listener)
{
    if (listener == nullptr) {
        unspecifiedNavigationListeners_.clear();
        return;
    }
    unspecifiedNavigationListeners_.erase(
        std::remove_if(unspecifiedNavigationListeners_.begin(), unspecifiedNavigationListeners_.end(),
            [listener](const std::shared_ptr<UIObserverListener>& registeredListener) {
                return registeredListener == listener;
            }),
        unspecifiedNavigationListeners_.end());
}

void UIObserver::UnRegisterNavigationCallback(
    std::string navigationId, const std::shared_ptr<UIObserverListener>& listener)
{
    if (specifiedCNavigationListeners_.find(navigationId) == specifiedCNavigationListeners_.end()) {
        return;
    }
    auto holder = specifiedCNavigationListeners_[navigationId];
    if (listener == nullptr) {
        holder.clear();
        return;
    }
    holder.erase(std::remove_if(holder.begin(), holder.end(),
                     [listener](const std::shared_ptr<UIObserverListener>& registeredListener) {
                         return registeredListener == listener;
                     }),
        holder.end());
}
} // namespace OHOS::Ace::NG
