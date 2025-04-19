/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ui_mgr_service_idl.h"

#include "ipc_skeleton.h"
#include "tokenid_kit.h"
#include "ui_service_hilog.h"
#include "ui_service_mgr_errors.h"
#include "ui_service_mgr_xcollie.h"
#include "xcollie/watchdog.h"

namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t UI_MGR_SERVICE_SA_ID = 7001;
constexpr uint32_t WATCHDOG_TIMEVAL = 5000;
constexpr uint32_t UI_MGR_SERVICE_TIMEOUT = 5;
#ifdef UI_SERVICE_WITH_IDL
const bool REGISTER_RESULT =
    SystemAbility::MakeAndRegisterAbility(DelayedSingleton<UIMgrServiceIdl>::GetInstance().get());
#endif
} // namespace

UIMgrServiceIdl::UIMgrServiceIdl()
    : SystemAbility(UI_MGR_SERVICE_SA_ID, true), eventLoop_(nullptr), handler_(nullptr),
      state_(UIServiceRunningState::STATE_NOT_START)
{
    LOGI("Ace UIServcieIdl is created");
}

UIMgrServiceIdl::~UIMgrServiceIdl()
{
    LOGI("Ace UIServcieIdl is destroyed");
    std::lock_guard<std::recursive_mutex> lock(uiMutex_);
    callbackMap_.clear();
}

int32_t UIMgrServiceIdl::Dump(int32_t fd, const std::vector<std::u16string>& args)
{
    std::lock_guard<std::recursive_mutex> lock(uiMutex_);
    dprintf(fd, "total callbacks: %u\n", callbackMap_.size());
    if (!callbackMap_.empty()) {
        dprintf(fd, "callback keys: \n");
    }
    for (const auto& callback : callbackMap_) {
        dprintf(fd, "  %s\n", callback.first.c_str());
    }
    return UI_SERVICE_NO_ERROR;
}

void UIMgrServiceIdl::OnStart()
{
    if (state_ == UIServiceRunningState::STATE_RUNNING) {
        return;
    }
    if (!Init()) {
        return;
    }
    state_ = UIServiceRunningState::STATE_RUNNING;
    eventLoop_->Run();

    /* Publish service maybe failed, so we need call this function at the last,
     * so it can't affect the TDD test program */
    bool ret = Publish(DelayedSingleton<UIMgrServiceIdl>::GetInstance().get());
    if (!ret) {
        return;
    }
    LOGI("Ace UImanager service OnStart");
}

bool UIMgrServiceIdl::Init()
{
    eventLoop_ = AppExecFwk::EventRunner::Create("UIMgrServiceIdl");
    if (eventLoop_ == nullptr) {
        return false;
    }

    handler_ = std::make_shared<AppExecFwk::EventHandler>(eventLoop_);
    if (handler_ == nullptr) {
        return false;
    }

    int32_t ret = HiviewDFX::Watchdog::GetInstance().AddThread("UIMgrServiceIdl", handler_, WATCHDOG_TIMEVAL);
    if (ret != 0) {
        LOGW("Add watchdog thread failed");
    }

    LOGI("Ace UIservice init success");
    return true;
}

void UIMgrServiceIdl::OnStop()
{
    eventLoop_->Stop();
    eventLoop_.reset();
    handler_.reset();
    state_ = UIServiceRunningState::STATE_NOT_START;
    LOGI("Ace UImanager service stop");
}

UIServiceRunningState UIMgrServiceIdl::QueryServiceState() const
{
    return state_;
}

int32_t UIMgrServiceIdl::RegisterCallBack(const AAFwk::Want& want, const sptr<IUIServiceNew>& uiService)
{
    if (uiService == nullptr) {
        return UI_SERVICE_IS_NULL;
    }
    if (handler_ == nullptr) {
        return UI_SERVICE_HANDLER_IS_NULL;
    }
    std::function<void()> registerFunc =
        std::bind(&UIMgrServiceIdl::HandleRegister, shared_from_this(), want, uiService);
    bool ret = handler_->PostTask(registerFunc);
    if (!ret) {
        return UI_SERVICE_POST_TASK_FAILED;
    }
    LOGI("UIServices register CallBack success");
    return NO_ERROR;
}

int32_t UIMgrServiceIdl::UnregisterCallBack(const AAFwk::Want& want)
{
    if (handler_ == nullptr) {
        return UI_SERVICE_HANDLER_IS_NULL;
    }
    std::function<void()> unregisterFunc = std::bind(&UIMgrServiceIdl::HandleUnregister, shared_from_this(), want);
    bool ret = handler_->PostTask(unregisterFunc);
    if (!ret) {
        return UI_SERVICE_POST_TASK_FAILED;
    }
    LOGI("UIServices unregister CallBack success");
    return NO_ERROR;
}

int32_t UIMgrServiceIdl::Push(const AAFwk::Want& want, const std::string& name, const std::string& jsonPath,
    const std::string& data, const std::string& extraData)
{
    std::map<std::string, sptr<IUIServiceNew>> callbackMap;
    {
        std::lock_guard<std::recursive_mutex> lock(uiMutex_);
        callbackMap = std::map<std::string, sptr<IUIServiceNew>>(callbackMap_);
    }
    for (auto iter = callbackMap.begin(); iter != callbackMap.end(); ++iter) {
        sptr<IUIServiceNew> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnPushCallBack(want, name, jsonPath, data, extraData);
    }
    return NO_ERROR;
}

int32_t UIMgrServiceIdl::Request(const AAFwk::Want& want, const std::string& name, const std::string& data)
{
    std::map<std::string, sptr<IUIServiceNew>> callbackMap;
    {
        std::lock_guard<std::recursive_mutex> lock(uiMutex_);
        callbackMap = std::map<std::string, sptr<IUIServiceNew>>(callbackMap_);
    }
    for (auto iter = callbackMap.begin(); iter != callbackMap.end(); ++iter) {
        sptr<IUIServiceNew> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnRequestCallBack(want, name, data);
    }
    return NO_ERROR;
}

int32_t UIMgrServiceIdl::ReturnRequest(
    const AAFwk::Want& want, const std::string& source, const std::string& data, const std::string& extraData)
{
    std::map<std::string, sptr<IUIServiceNew>> callbackMap;
    {
        std::lock_guard<std::recursive_mutex> lock(uiMutex_);
        callbackMap = std::map<std::string, sptr<IUIServiceNew>>(callbackMap_);
    }
    for (auto iter = callbackMap.begin(); iter != callbackMap.end(); ++iter) {
        sptr<IUIServiceNew> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnReturnRequest(want, source, data, extraData);
    }
    return NO_ERROR;
}

int32_t UIMgrServiceIdl::HandleRegister(const AAFwk::Want& want, const sptr<IUIServiceNew>& uiService)
{
    std::lock_guard<std::recursive_mutex> lock(uiMutex_);
    std::string keyStr = GetCallBackKeyStr(want);
    bool exist = CheckCallBackFromMap(keyStr);
    if (exist) {
        callbackMap_.erase(keyStr);
    }
    callbackMap_.emplace(keyStr, uiService);
    return NO_ERROR;
}

int32_t UIMgrServiceIdl::HandleUnregister(const AAFwk::Want& want)
{
    std::lock_guard<std::recursive_mutex> lock(uiMutex_);
    std::string keyStr = GetCallBackKeyStr(want);
    bool exist = CheckCallBackFromMap(keyStr);
    if (!exist) {
        return NO_CALLBACK_FOR_KEY;
    }
    callbackMap_.erase(keyStr);
    return NO_ERROR;
}

std::string UIMgrServiceIdl::GetCallBackKeyStr(const AAFwk::Want& want)
{
    AppExecFwk::ElementName element = want.GetElement();
    std::string bundleName = element.GetBundleName();
    std::string keyStr = bundleName;
    return keyStr;
}

bool UIMgrServiceIdl::CheckCallBackFromMap(const std::string& key)
{
    std::lock_guard<std::recursive_mutex> lock(uiMutex_);
    auto it = callbackMap_.find(key);
    if (it == callbackMap_.end()) {
        return false;
    }
    return true;
}

int32_t UIMgrServiceIdl::OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply,
    MessageOption& option)
{
    UIServiceMgrXCollie uiServiceMgrXCollie(IpcCodeToString(code), UI_MGR_SERVICE_TIMEOUT);
    if (!IsSystemApp()) {
        return ERR_PERMISSION_DENIED;
    }
    auto result = UIServiceMgrNewStub::OnRemoteRequest(code, data, reply, option);
    LOGI("Ace UIServcieIdl OnRemoteRequest res = %{public}d", result);
    return result;
}

const char* UIMgrServiceIdl::IpcCodeToString(uint32_t code)
{
    switch (static_cast<IUIServiceMgrNewIpcCode>(code)) {
        case IUIServiceMgrNewIpcCode::COMMAND_REGISTER_CALL_BACK:
            return "UISERVICE_REGISTER_CALLBACK";
        case IUIServiceMgrNewIpcCode::COMMAND_UNREGISTER_CALL_BACK:
            return "UISERVICE_UNREGISTER_CALLBACK";
        case IUIServiceMgrNewIpcCode::COMMAND_PUSH:
            return "UISERVICE_PUSH";
        case IUIServiceMgrNewIpcCode::COMMAND_REQUEST:
            return "UISERVICE_REQUEST";
        case IUIServiceMgrNewIpcCode::COMMAND_RETURN_REQUEST:
            return "UISERVICE_RETURN_REQUEST";
        default:
            return "UISERVICE_UNKNOWN";
    }
}

bool UIMgrServiceIdl::IsSystemApp()
{
    uint64_t accessTokenIDEx = IPCSkeleton::GetCallingFullTokenID();
    return Security::AccessToken::TokenIdKit::IsSystemAppByFullTokenID(accessTokenIDEx);
}

} // namespace Ace
} // namespace OHOS
