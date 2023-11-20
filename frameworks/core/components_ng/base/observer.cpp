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

namespace {
std::string GetNavigationId(const RefPtr<NavDestinationPattern> pattern)
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

void UIObserverHandler::NotifyNavigationStateChange(const WeakPtr<AceType>& weakPattern, NavDestinationState state)
{
    auto ref = weakPattern.Upgrade();
    CHECK_NULL_VOID(ref);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(ref);
    CHECK_NULL_VOID(pattern);
    std::string navigationId = GetNavigationId(pattern);
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
        GetNavigationId(pattern),
        pattern->GetName(),
        pattern->GetIsOnShow() ? NavDestinationState::ON_SHOW : NavDestinationState::ON_HIDDEN);
}

void UIObserverListener::OnNavigationStateChange(
    std::string navigationId, std::string navDestinationName, NG::NavDestinationState navState)
{
    if (!env_ || !callback_) {
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
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
}

napi_value UIObserverListener::GetNapiCallback()
{
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    return callback;
}

bool UIObserverListener::NapiEqual(napi_value cb)
{
    bool isEquals = false;
    napi_strict_equals(env_, cb, GetNapiCallback(), &isEquals);
    return isEquals;
}

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
    auto holder = specifiedCNavigationListeners_[navigationId];
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
    auto holder = specifiedCNavigationListeners_[navigationId];
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
} // namespace OHOS::Ace::NG
