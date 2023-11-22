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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H

#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
enum class NavDestinationState {
    ON_SHOWN = 0,
    ON_HIDDEN = 1,
};

struct NavDestinationInfo {
    std::string navigationId;
    std::string name;
    NavDestinationState state;

    NavDestinationInfo(std::string id, std::string name, NavDestinationState state)
        : navigationId(std::move(id)), name(std::move(name)), state(state)
    {}
};

class ACE_FORCE_EXPORT UIObserverHandler {
public:
    UIObserverHandler() = default;
    ~UIObserverHandler() = default;
    static UIObserverHandler& GetInstance();
    void NotifyNavigationStateChange(const WeakPtr<AceType>& weakPattern, NavDestinationState state);
    std::shared_ptr<NavDestinationInfo> GetNavigationState(const RefPtr<AceType>& node);
    using HandleFunc = void (*)(std::string, std::string, NavDestinationState);
    void SetHandleNavigationChangeFunc(HandleFunc func);
private:
    HandleFunc handleFunc_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H
