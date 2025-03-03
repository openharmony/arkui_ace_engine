/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FRAMEWORK_ROUTER_CJ_ROUTER_FFI_H
#define OHOS_ACE_FRAMEWORK_ROUTER_CJ_ROUTER_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"

extern "C" {
using RouterCallback = void (*)(int32_t);
CJ_EXPORT void FfiOHOSAceFrameworkRouterPush(const char* url, const char* param);
CJ_EXPORT void FfiOHOSAceFrameworkRouterBack(const char* url, const char* param);
CJ_EXPORT ExternalString FfiOHOSAceFrameworkRouterGetParams();
CJ_EXPORT void FfiOHOSAceFrameworkRouterBackIndex(int32_t index, const char* param);
CJ_EXPORT void FfiOHOSAceFrameworkRouterPushUrl(
    const char* url, const char* param, int32_t modeValue, RouterCallback callbackRef);
CJ_EXPORT void FfiOHOSAceFrameworkRouterReplaceUrl(
    const char* url, const char* param, int32_t modeValue, RouterCallback callbackRef);
CJ_EXPORT void FfiOHOSAceFrameworkRouterClear();
CJ_EXPORT int32_t FfiOHOSAceFrameworkRouterGetLength();
CJ_EXPORT void FfiOHOSAceFrameworkRouterSetHideAlertBeforeBackPage();
CJ_EXPORT void FfiOHOSAceFrameworkRouterSetShowAlertBeforeBackPage(const char* msg, RouterCallback callbackRef);
CJ_EXPORT void FfiOHOSAceFrameworkRouterGetState(OHOS::Ace::CJPageRouterAbstract::RouterState* info);
CJ_EXPORT void FfiOHOSAceFrameworkRouterGetStateByIndex(OHOS::Ace::CJPageRouterAbstract::RouterState* info);
CJ_EXPORT OHOS::Ace::CJPageRouterAbstract::RouterStateList FfiOHOSAceFrameworkRouterGetStateByUrl(const char* url);
}

#endif // OHOS_ACE_FRAMEWORK_ROUTER_CJ_ROUTER_FFI_H
