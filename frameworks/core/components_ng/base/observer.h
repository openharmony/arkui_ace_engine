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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_H

#include <list>
#include <string>
#include <unordered_map>

#include "observer_trigger.h"

#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

class INavigationStateChangeListener {
public:
    virtual void OnNavigationStateChange(std::string, std::string, NG::NavDestinationState) = 0;
};

class ACE_FORCE_EXPORT UIObserverListener final : public AceType, public INavigationStateChangeListener {
    DECLARE_ACE_TYPE(UIObserverListener, AceType);

public:
    UIObserverListener(napi_env env, napi_value callback) : env_(env), callback_(callback) {};
    ~UIObserverListener() = default;
    void OnNavigationStateChange(
        std::string navigationId, std::string navDestinationName, NG::NavDestinationState state) override;

    napi_env env_ = nullptr;
    napi_value callback_ = nullptr;
};

class ACE_FORCE_EXPORT UIObserver {
public:
    static void RegisterNavigationCallback(const RefPtr<UIObserverListener>& listener);
    static void RegisterNavigationCallback(std::string navigationId, const RefPtr<UIObserverListener>& listener);
    static void UnRegisterNavigationCallback(const RefPtr<UIObserverListener>& listener = nullptr);
    static void UnRegisterNavigationCallback(
        std::string navigationId, const RefPtr<UIObserverListener>& listener = nullptr);

private:
    static std::list<RefPtr<UIObserverListener>> unspecifiedNavigationListeners_;
    static std::unordered_map<std::string, std::list<RefPtr<UIObserverListener>>> specifiedCNavigationListeners_;

    friend class UIObserverHandler;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_H
