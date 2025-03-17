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
    napi_value ProcessScrollEventRegister(napi_env env, napi_callback_info info);
    napi_value ProcessScrollEventUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessRouterPageRegister(napi_env env, napi_callback_info info);
    napi_value ProcessRouterPageUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessDensityRegister(napi_env env, napi_callback_info info);
    using Func = napi_value (ObserverProcess::*)(napi_env, napi_callback_info);
    napi_value ProcessDensityUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessDrawCommandSendRegister(napi_env env, napi_callback_info info);
    napi_value ProcessDrawCommandSendUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessLayoutDoneRegister(napi_env env, napi_callback_info info);
    napi_value ProcessLayoutDoneUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessNavDestinationSwitchRegister(napi_env env, napi_callback_info info);
    napi_value ProcessNavDestinationSwitchUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessWillClickRegister(napi_env env, napi_callback_info info);
    napi_value ProcessWillClickUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessDidClickRegister(napi_env env, napi_callback_info info);
    napi_value ProcessDidClickUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessTabContentStateRegister(napi_env env, napi_callback_info info);
    napi_value ProcessTabContentStateUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessBeforePanStartRegister(napi_env env, napi_callback_info info);
    napi_value ProcessBeforePanStartUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessBeforePanEndRegister(napi_env env, napi_callback_info info);
    napi_value ProcessBeforePanEndUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessAfterPanStartRegister(napi_env env, napi_callback_info info);
    napi_value ProcessAfterPanStartUnRegister(napi_env env, napi_callback_info info);
    napi_value ProcessAfterPanEndRegister(napi_env env, napi_callback_info info);
    napi_value ProcessAfterPanEndUnRegister(napi_env env, napi_callback_info info);
    napi_value AddToScrollEventType(napi_env env);
    napi_value AddToRouterPageState(napi_env env);
    napi_value CreateNavDestinationState(napi_env env);
    bool isNavigationHandleFuncSetted_ = false;
    bool isScrollEventChangeFuncSetted_ = false;
    bool isDensityChangeSetted_ = false;
    bool isDrawCommandSendChangeSetted_ = false;
    bool isLayoutDoneChangeSetted_ = false;
    bool isWillClickFuncSetted_ = false;
    bool isDidClickFuncSetted_ = false;
    bool isPanGestureHandleFuncSetted_ = false;
    bool isTabContentStateUpdateFuncSetted_ = false;
    bool isRouterPageHandleFuncSetted_ = false;
    bool isDestinationSwitchHandleFuncSetted_ = false;
    std::map<std::string, Func> registerProcessMap_;
    std::map<std::string, Func> unregisterProcessMap_;
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_JS_OBSERVER_H
