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

#include <algorithm>

namespace OHOS::Ace::Napi {
std::list<std::shared_ptr<UIObserverListener>> UIObserver::unspecifiedNavigationListeners_;
std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
    UIObserver::specifiedCNavigationListeners_;

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
} // namespace OHOS::Ace::Napi
