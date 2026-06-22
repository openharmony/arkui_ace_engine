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

#include "base/subwindow/subwindow_manager.h"
#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
int32_t GetParentContainerIdIfNeeded()
{
    auto container = Container::Current();
    if (!container) {
        return -1;
    }
    if (container->IsSubContainer()) {
        return SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    }
    return Container::CurrentId();
}
}

extern "C" {
void FfiOHOSAceFrameworkRouterPush(const char* url, const char* param)
{
    if (url == nullptr) {
        LOGE("RouterPush fail, url is null");
        return;
    }
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterPush fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterPush fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->PushPage(url, param != nullptr ? param : "");
}

void FfiOHOSAceFrameworkRouterBack(const char* url, const char* param)
{
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterBack fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterBack fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->Back(url != nullptr ? url : "", param != nullptr ? param : "");
}

void FfiOHOSAceFrameworkRouterReplace(const char* url, const char* param, int32_t modeValue)
{
    if (url == nullptr) {
        LOGE("RouterReplace fail, url is null");
        return;
    }
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterReplace fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterReplace fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    auto mode = static_cast<CJPageRouterAbstract::RouterMode>(modeValue);
    frontend->Replace(url, param != nullptr ? param : "", mode);
}

ExternalString FfiOHOSAceFrameworkRouterGetParams()
{
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterGetParams fail, no valid container");
        return {};
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterGetParams fail, can not get container");
        return {};
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return {};
    }
    return Utils::MallocCString(frontend->GetParams());
}

void FfiOHOSAceFrameworkRouterBackIndex(int32_t index, const char* param)
{
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterBackIndex fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterBackIndex fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->BackIndex(index, param != nullptr ? param : "");
}

void FfiOHOSAceFrameworkRouterPushUrl(const char* url, const char* param, int32_t modeValue, RouterCallback callbackRef)
{
    if (url == nullptr) {
        LOGE("RouterPushUrl fail, url is null");
        return;
    }
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterPushUrl fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterPushUrl fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    auto mode = static_cast<CJPageRouterAbstract::RouterMode>(modeValue);
    auto callback = [ffiGetErrcode = CJLambda::Create(callbackRef)](int32_t errorCode) { ffiGetErrcode(errorCode); };
    frontend->PushPageWithCallback(url, param != nullptr ? param : "", mode, std::move(callback));
}

void FfiOHOSAceFrameworkRouterReplaceUrl(
    const char* url, const char* param, int32_t modeValue, RouterCallback callbackRef)
{
    if (url == nullptr) {
        LOGE("RouterReplaceUrl fail, url is null");
        return;
    }
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterReplaceUrl fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterReplaceUrl fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    auto mode = static_cast<CJPageRouterAbstract::RouterMode>(modeValue);
    auto callback = [ffiGetErrcode = CJLambda::Create(callbackRef)](int32_t errorCode) { ffiGetErrcode(errorCode); };
    frontend->ReplacePageWithCallback(url, param != nullptr ? param : "", mode, std::move(callback));
}

void FfiOHOSAceFrameworkRouterClear()
{
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterClear fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterClear fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->Clear();
}

int32_t FfiOHOSAceFrameworkRouterGetLength()
{
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterGetLength fail, no valid container");
        return 0;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterGetLength fail, can not get container");
        return 0;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return 0;
    }
    return frontend->GetLength();
}

void FfiOHOSAceFrameworkRouterSetHideAlertBeforeBackPage()
{
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("SetHideAlertBeforeBackPage fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("SetHideAlertBeforeBackPage fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->SetHideAlertBeforeBackPage();
}

void FfiOHOSAceFrameworkRouterSetShowAlertBeforeBackPage(const char* msg, RouterCallback callbackRef)
{
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("SetShowAlertBeforeBackPage fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("SetShowAlertBeforeBackPage fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    auto callback = [ffiGetErrcode = CJLambda::Create(callbackRef)](int32_t errorCode) { ffiGetErrcode(errorCode); };
    frontend->SetShowAlertBeforeBackPage(msg, std::move(callback));
}

void FfiOHOSAceFrameworkRouterGetState(OHOS::Ace::CJPageRouterAbstract::RouterState* info)
{
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterGetState fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterGetState fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->GetState(info);
}

void FfiOHOSAceFrameworkRouterGetStateByIndex(OHOS::Ace::CJPageRouterAbstract::RouterState* info)
{
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterGetStateByIndex fail, no valid container");
        return;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterGetStateByIndex fail, can not get container");
        return;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return;
    }
    frontend->GetStateByIndex(info);
}

OHOS::Ace::CJPageRouterAbstract::RouterStateList FfiOHOSAceFrameworkRouterGetStateByUrl(const char* url)
{
    OHOS::Ace::CJPageRouterAbstract::RouterStateList ret;
    auto containerId = GetParentContainerIdIfNeeded();
    if (containerId < 0) {
        LOGE("RouterGetStateByUrl fail, no valid container");
        return ret;
    }
    ContainerScope scope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    if (!container) {
        LOGE("RouterGetStateByUrl fail, can not get container");
        return ret;
    }
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(container->GetFrontend());
    if (!frontend) {
        LOGE("can not get frontend.");
        return ret;
    }
    ret = frontend->GetStateByUrl(url);
    return ret;
}
}
