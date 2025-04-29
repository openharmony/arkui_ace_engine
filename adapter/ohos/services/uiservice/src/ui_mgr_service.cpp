/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "ui_mgr_service.h"

#include "ui_service_mgr_errors.h"
#include "xcollie/watchdog.h"

#include "ui_service_hilog.h"
namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t UI_MGR_SERVICE_SA_ID = 7001;
constexpr uint32_t WATCHDOG_TIMEVAL = 5000;
#ifndef UI_SERVICE_WITH_IDL
const bool REGISTER_RESULT = SystemAbility::MakeAndRegisterAbility(DelayedSingleton<UIMgrService>::GetInstance().get());
#endif
} // namespace

// UiservicePluginDialog UIMgrService::dialogPlugin_;

UIMgrService::UIMgrService()
    : SystemAbility(UI_MGR_SERVICE_SA_ID, true), eventLoop_(nullptr), handler_(nullptr),
      state_(UIServiceRunningState::STATE_NOT_START)
{
    LOGI("Ace UIServcie is created");
}

UIMgrService::~UIMgrService()
{
    LOGI("Ace UIServcie is destroyed");
    std::lock_guard<std::recursive_mutex> lock(uiMutex_);
    callbackMap_.clear();
}

int32_t UIMgrService::Dump(int32_t fd, const std::vector<std::u16string>& args)
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

void UIMgrService::OnStart()
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
    bool ret = Publish(DelayedSingleton<UIMgrService>::GetInstance().get());
    if (!ret) {
        return;
    }
    LOGI("Ace UImanager service OnStart");
}

bool UIMgrService::Init()
{
    eventLoop_ = AppExecFwk::EventRunner::Create("UIMgrService");
    if (eventLoop_ == nullptr) {
        return false;
    }

    handler_ = std::make_shared<AppExecFwk::EventHandler>(eventLoop_);
    if (handler_ == nullptr) {
        return false;
    }

    int32_t ret = HiviewDFX::Watchdog::GetInstance().AddThread("UIMgrService", handler_, WATCHDOG_TIMEVAL);
    if (ret != 0) {
        LOGW("Add watchdog thread failed");
    }

    LOGI("Ace UIservice init success");
    return true;
}

void UIMgrService::OnStop()
{
    eventLoop_->Stop();
    eventLoop_.reset();
    handler_.reset();
    state_ = UIServiceRunningState::STATE_NOT_START;
    LOGI("Ace UImanager service stop");
}

UIServiceRunningState UIMgrService::QueryServiceState() const
{
    return state_;
}

int32_t UIMgrService::RegisterCallBack(const AAFwk::Want& want, const sptr<IUIService>& uiService)
{
    if (uiService == nullptr) {
        return UI_SERVICE_IS_NULL;
    }
    if (handler_ == nullptr) {
        return UI_SERVICE_HANDLER_IS_NULL;
    }
    std::function<void()> registerFunc = std::bind(&UIMgrService::HandleRegister, shared_from_this(), want, uiService);
    bool ret = handler_->PostTask(registerFunc);
    if (!ret) {
        return UI_SERVICE_POST_TASK_FAILED;
    }
    LOGI("UIServices register CallBack success");
    return NO_ERROR;
}

int32_t UIMgrService::UnregisterCallBack(const AAFwk::Want& want)
{
    if (handler_ == nullptr) {
        return UI_SERVICE_HANDLER_IS_NULL;
    }
    std::function<void()> unregisterFunc = std::bind(&UIMgrService::HandleUnregister, shared_from_this(), want);
    bool ret = handler_->PostTask(unregisterFunc);
    if (!ret) {
        return UI_SERVICE_POST_TASK_FAILED;
    }
    LOGI("UIServices unregister CallBack success");
    return NO_ERROR;
}

int32_t UIMgrService::Push(const AAFwk::Want& want, const std::string& name, const std::string& jsonPath,
    const std::string& data, const std::string& extraData)
{
    std::map<std::string, sptr<IUIService>> callbackMap;
    {
        std::lock_guard<std::recursive_mutex> lock(uiMutex_);
        callbackMap = std::map<std::string, sptr<IUIService>>(callbackMap_);
    }
    for (auto iter = callbackMap.begin(); iter != callbackMap.end(); ++iter) {
        sptr<IUIService> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnPushCallBack(want, name, jsonPath, data, extraData);
    }
    return NO_ERROR;
}

int32_t UIMgrService::Request(const AAFwk::Want& want, const std::string& name, const std::string& data)
{
    std::map<std::string, sptr<IUIService>> callbackMap;
    {
        std::lock_guard<std::recursive_mutex> lock(uiMutex_);
        callbackMap = std::map<std::string, sptr<IUIService>>(callbackMap_);
    }
    for (auto iter = callbackMap.begin(); iter != callbackMap.end(); ++iter) {
        sptr<IUIService> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnRequestCallBack(want, name, data);
    }
    return NO_ERROR;
}

int32_t UIMgrService::ReturnRequest(
    const AAFwk::Want& want, const std::string& source, const std::string& data, const std::string& extraData)
{
    std::map<std::string, sptr<IUIService>> callbackMap;
    {
        std::lock_guard<std::recursive_mutex> lock(uiMutex_);
        callbackMap = std::map<std::string, sptr<IUIService>>(callbackMap_);
    }
    for (auto iter = callbackMap.begin(); iter != callbackMap.end(); ++iter) {
        sptr<IUIService> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnReturnRequest(want, source, data, extraData);
    }
    return NO_ERROR;
}

int32_t UIMgrService::HandleRegister(const AAFwk::Want& want, const sptr<IUIService>& uiService)
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

int32_t UIMgrService::HandleUnregister(const AAFwk::Want& want)
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

std::string UIMgrService::GetCallBackKeyStr(const AAFwk::Want& want)
{
    AppExecFwk::ElementName element = want.GetElement();
    std::string bundleName = element.GetBundleName();
    std::string keyStr = bundleName;
    return keyStr;
}

bool UIMgrService::CheckCallBackFromMap(const std::string& key)
{
    std::lock_guard<std::recursive_mutex> lock(uiMutex_);
    auto it = callbackMap_.find(key);
    if (it == callbackMap_.end()) {
        return false;
    }
    return true;
}
} // namespace Ace
} // namespace OHOS
