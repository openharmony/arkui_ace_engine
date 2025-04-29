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

#include "cj_router_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkRouterPush(const char* url, const char* param)
{
    if (Container::CurrentId() < 0) {
        LOGE("RouterPush fail, no current container");
        return;
    }
    auto frontend = Utils::GetCurrentFrontend();
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->PushPage(url, param);
}

void FfiOHOSAceFrameworkRouterBack(const char* url, const char* param)
{
    if (Container::CurrentId() < 0) {
        LOGE("RouterBack fail, no current container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->Back(url, param);
}

ExternalString FfiOHOSAceFrameworkRouterGetParams()
{
    if (Container::CurrentId() < 0) {
        LOGE("RouterGetParams fail, no current container");
        return {};
    }

    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return {};
    }

    return Utils::MallocCString(frontend->GetParams());
}

void FfiOHOSAceFrameworkRouterBackIndex(int32_t index, const char* param)
{
    if (Container::CurrentId() < 0) {
        LOGE("RouterBackIndex fail, no current container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->BackIndex(index, param);
}

void FfiOHOSAceFrameworkRouterPushUrl(const char* url, const char* param, int32_t modeValue, RouterCallback callbackRef)
{
    if (Container::CurrentId() < 0) {
        LOGE("RouterPushUrl fail, no current container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    auto mode = static_cast<CJPageRouterAbstract::RouterMode>(modeValue);
    auto callback = [ffiGetErrcode = CJLambda::Create(callbackRef)](int32_t errorCode) { ffiGetErrcode(errorCode); };
    frontend->PushPageWithCallback(url, param, mode, std::move(callback));
}
void FfiOHOSAceFrameworkRouterReplaceUrl(
    const char* url, const char* param, int32_t modeValue, RouterCallback callbackRef)
{
    if (Container::CurrentId() < 0) {
        LOGE("RouterReplaceUrl fail, no current container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    auto mode = static_cast<CJPageRouterAbstract::RouterMode>(modeValue);
    auto callback = [ffiGetErrcode = CJLambda::Create(callbackRef)](int32_t errorCode) { ffiGetErrcode(errorCode); };
    frontend->ReplacePageWithCallback(url, param, mode, std::move(callback));
}
void FfiOHOSAceFrameworkRouterClear()
{
    if (Container::CurrentId() < 0) {
        LOGE("RouterClear fail, no current container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->Clear();
}
int32_t FfiOHOSAceFrameworkRouterGetLength()
{
    if (Container::CurrentId() < 0) {
        LOGE("RouterGetLength fail, no current container");
        return 0;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return 0;
    }
    return frontend->GetLength();
}
void FfiOHOSAceFrameworkRouterSetHideAlertBeforeBackPage()
{
    if (Container::CurrentId() < 0) {
        LOGE("SetHideAlertBeforeBackPage fail, no current container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->SetHideAlertBeforeBackPage();
}
void FfiOHOSAceFrameworkRouterSetShowAlertBeforeBackPage(const char* msg, RouterCallback callbackRef)
{
    if (Container::CurrentId() < 0) {
        LOGE("SetShowAlertBeforeBackPage fail, no current container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    auto callback = [ffiGetErrcode = CJLambda::Create(callbackRef)](int32_t errorCode) { ffiGetErrcode(errorCode); };
    frontend->SetShowAlertBeforeBackPage(msg, std::move(callback));
}
void FfiOHOSAceFrameworkRouterGetState(OHOS::Ace::CJPageRouterAbstract::RouterState* info)
{
    if (Container::CurrentId() < 0) {
        LOGE("RouterGetState fail, no current container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->GetState(info);
}
void FfiOHOSAceFrameworkRouterGetStateByIndex(OHOS::Ace::CJPageRouterAbstract::RouterState* info)
{
    if (Container::CurrentId() < 0) {
        LOGE("RouterGetStateByIndex fail, no current container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->GetStateByIndex(info);
}
OHOS::Ace::CJPageRouterAbstract::RouterStateList FfiOHOSAceFrameworkRouterGetStateByUrl(const char* url)
{
    OHOS::Ace::CJPageRouterAbstract::RouterStateList ret;
    if (Container::CurrentId() < 0) {
        LOGE("RouterGetStateByUrl fail, no current container");
        return ret;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return ret;
    }
    ret = frontend->GetStateByUrl(url);
    return ret;
}
}
