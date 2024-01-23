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

#ifndef FOUNDATION_ACE_INTERFACES_JS_OBSERVER_H
#define FOUNDATION_ACE_INTERFACES_JS_OBSERVER_H

#include <string>
#include <map>

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {
const std::string NAVDESTINATION_UPDATE = "navDestinationUpdate";
const std::string ROUTERPAGE_UPDATE = "routerPageUpdate";

class ObserverProcess {
public:
    ObserverProcess();
    ~ObserverProcess() = default;
    static ObserverProcess& GetInstance();
    napi_value ProcessRegister(napi_env env, napi_callback_info info);
    napi_value ProcessUnRegister(napi_env env, napi_callback_info info);
private:
    napi_value ProcessNavigationRegister(napi_env env, napi_callback_info info);
    napi_value ProcessNavigationUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessRouterPageRegister(napi_env env, napi_callback_info info);
    napi_value ProcessRouterPageUnRegister(napi_env env, napi_callback_info info);
    using Func = napi_value(ObserverProcess::*)(napi_env, napi_callback_info);
    std::map<std::string, Func> registerProcess_;
    std::map<std::string, Func> unregisterProcess_;
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_JS_OBSERVER_H
