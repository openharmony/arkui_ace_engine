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

    static void HandleNavigationStateChange(std::string navigationId, std::string navDestinationName,
                                            NG::NavDestinationState state);
private:
    static std::list<std::shared_ptr<UIObserverListener>> unspecifiedNavigationListeners_;
    static std::unordered_map<std::string, std::list<std::shared_ptr<UIObserverListener>>>
        specifiedCNavigationListeners_;
};
} // namespace OHOS::Ace::Napi
#endif // FOUNDATION_ACE_INTERFACES_OBSERVER_H
