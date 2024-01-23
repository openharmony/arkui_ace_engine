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
#include "core/common/frontend.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

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

struct RouterPageInfoNG {
    napi_value context;
    int index;
    std::string name;
    std::string path;
    RouterPageState state;

    RouterPageInfoNG(napi_value context, int index, std::string name, std::string path, RouterPageState state)
        : context(context), index(index), name(std::move(name)), path(std::move(path)), state(state)
    {}
};

struct AbilityContextInfo {
    std::string name = "";
    std::string bundleName = "";
    std::string moduleName = "";

    bool IsEqual(AbilityContextInfo& info)
    {
        if (info.name != name) {
            return false;
        }
        if (info.bundleName != bundleName) {
            return false;
        }
        if (info.moduleName != moduleName) {
            return false;
        }
        return true;
    }
};

class ACE_FORCE_EXPORT UIObserverHandler {
public:
    UIObserverHandler() = default;
    ~UIObserverHandler() = default;
    static UIObserverHandler& GetInstance();
    void NotifyNavigationStateChange(const WeakPtr<AceType>& weakPattern, NavDestinationState state);
    void NotifyRouterPageStateChange(const RefPtr<PageInfo>& pageInfo, RouterPageState state);
    std::shared_ptr<NavDestinationInfo> GetNavigationState(const RefPtr<AceType>& node);
    std::shared_ptr<RouterPageInfoNG> GetRouterPageState(const RefPtr<AceType>& node);
    using NavigationHandleFunc = void (*)(const std::string&, const std::string&, NavDestinationState);
    using RouterPageHandleFunc = void (*)(
        AbilityContextInfo&, napi_value, int32_t, const std::string&, const std::string&, RouterPageState);
    void SetHandleNavigationChangeFunc(NavigationHandleFunc func);
    void SetHandleRouterPageChangeFunc(RouterPageHandleFunc func);
private:
    NavigationHandleFunc navigationHandleFunc_ = nullptr;
    RouterPageHandleFunc routerPageHandleFunc_ = nullptr;
    napi_value GetUIContextValue();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H
