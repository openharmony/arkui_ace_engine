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

#ifndef FOUNDATION_ACE_INTERFACES_OBSERVER_LISTENER_H
#define FOUNDATION_ACE_INTERFACES_OBSERVER_LISTENER_H

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

#include "core/components_ng/base/observer_handler.h"

namespace OHOS::Ace::Napi {
class UIObserverListener {
public:
    UIObserverListener(napi_env env, napi_value callback) : env_(env)
    {
        napi_create_reference(env_, callback, 1, &callback_);
    }
    ~UIObserverListener()
    {
        if (callback_) {
            napi_delete_reference(env_, callback_);
        }
    }
    void OnNavigationStateChange(
        std::string navigationId, std::string navDestinationName, NG::NavDestinationState state);
    bool NapiEqual(napi_value cb);

private:
    napi_value GetNapiCallback();
    napi_env env_ = nullptr;
    napi_ref callback_ = nullptr;
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_OBSERVER_LISTENER_H
