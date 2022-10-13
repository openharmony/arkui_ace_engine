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

#include <atomic>

#include "hilog_wrapper.h"
#include "if_system_ability_manager.h"
#include "ipc_skeleton.h"

#include "string_ex.h"
#include "system_ability_definition.h"
#include "ui_service_mgr_errors.h"

namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t UI_MGR_SERVICE_SA_ID = 7001;
const bool REGISTER_RESULT =
    SystemAbility::MakeAndRegisterAbility(DelayedSingleton<UIMgrService>::GetInstance().get());
}

// UiservicePluginDialog UIMgrService::dialogPlugin_;

UIMgrService::UIMgrService()
    : SystemAbility(UI_MGR_SERVICE_SA_ID, true),
      eventLoop_(nullptr),
      handler_(nullptr),
      state_(UIServiceRunningState::STATE_NOT_START)
{
}

UIMgrService::~UIMgrService()
{
    std::lock_guard<std::mutex> lock(uiMutex_);
    callbackMap_.clear();
}

int32_t UIMgrService::Dump(int32_t fd, const std::vector<std::u16string>& args)
{
    std::lock_guard<std::mutex> lock(uiMutex_);
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
    HILOG_INFO("Ace ui manager service OnStart");
    if (state_ == UIServiceRunningState::STATE_RUNNING) {
        HILOG_INFO("Ace ui Manager Service has already started.");
        return;
    }
    HILOG_INFO("Ace ui Manager Service started.");
    if (!Init()) {
        HILOG_ERROR("Ace ui service failed to init service.");
        return;
    }
    state_ = UIServiceRunningState::STATE_RUNNING;
    eventLoop_->Run();

    /* Publish service maybe failed, so we need call this function at the last,
     * so it can't affect the TDD test program */
    bool ret = Publish(DelayedSingleton<UIMgrService>::GetInstance().get());
    if (!ret) {
        HILOG_ERROR("UIMgrService::Init Publish failed!");
        return;
    }

    HILOG_INFO("UIMgrService  start success.");
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

    HILOG_INFO("Ace ui service init success");
    return true;
}

void UIMgrService::OnStop()
{
    HILOG_INFO("stop service");
    eventLoop_->Stop();
    eventLoop_.reset();
    handler_.reset();
    state_ = UIServiceRunningState::STATE_NOT_START;
}

UIServiceRunningState UIMgrService::QueryServiceState() const
{
    return state_;
}

int32_t UIMgrService::RegisterCallBack(const AAFwk::Want& want, const sptr<IUIService>& uiService)
{
    HILOG_INFO("UIMgrService::RegisterCallBack called start");
    if (uiService == nullptr) {
        HILOG_ERROR("UIMgrService::RegisterCallBack failed!. uiService is nullptr");
        return UI_SERVICE_IS_NULL;
    }
    if (handler_ == nullptr) {
        HILOG_ERROR("UIMgrService::RegisterCallBack failed!. handler is nullptr");
        return UI_SERVICE_HANDLER_IS_NULL;
    }
    std::function<void()> registerFunc = std::bind(&UIMgrService::HandleRegister, shared_from_this(), want, uiService);
    bool ret = handler_->PostTask(registerFunc);
    if (!ret) {
        HILOG_ERROR("DataObsMgrService::RegisterCallBack PostTask error");
        return UI_SERVICE_POST_TASK_FAILED;
    }
    HILOG_INFO("UIMgrService::RegisterCallBack called end");
    return NO_ERROR;
}

int32_t UIMgrService::UnregisterCallBack(const AAFwk::Want& want)
{
    HILOG_INFO("UIMgrService::UnregisterCallBack called start");
    if (handler_ == nullptr) {
        HILOG_ERROR("UIMgrService::UnregisterCallBack failed!. handler is nullptr");
        return UI_SERVICE_HANDLER_IS_NULL;
    }
    std::function<void()> unregisterFunc = std::bind(&UIMgrService::HandleUnregister, shared_from_this(), want);
    bool ret = handler_->PostTask(unregisterFunc);
    if (!ret) {
        HILOG_ERROR("DataObsMgrService::UnregisterCallBack PostTask error");
        return UI_SERVICE_POST_TASK_FAILED;
    }
    HILOG_INFO("UIMgrService::UnregisterCallBack called end");
    return NO_ERROR;
}

int32_t UIMgrService::Push(const AAFwk::Want& want, const std::string& name,
    const std::string& jsonPath, const std::string& data, const std::string& extraData)
{
    HILOG_INFO("UIMgrService::Push called start");
    std::lock_guard<std::mutex> lock(uiMutex_);
    for (auto iter = callbackMap_.begin(); iter != callbackMap_.end(); ++iter) {
        sptr<IUIService> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnPushCallBack(want, name, jsonPath, data, extraData);
    }
    HILOG_INFO("UIMgrService::Push called end");
    return NO_ERROR;
}

int32_t UIMgrService::Request(const AAFwk::Want& want, const std::string& name, const std::string& data)
{
    HILOG_INFO("UIMgrService::Request called start");
    std::lock_guard<std::mutex> lock(uiMutex_);
    for (auto iter = callbackMap_.begin(); iter != callbackMap_.end(); ++iter) {
        sptr<IUIService> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnRequestCallBack(want, name, data);
    }
    HILOG_INFO("UIMgrService::Request called end");
    return NO_ERROR;
}

int32_t UIMgrService::ReturnRequest(
    const AAFwk::Want& want, const std::string& source, const std::string& data, const std::string& extraData)
{
    HILOG_INFO("UIMgrService::ReturnRequest called start");
    for (auto iter = callbackMap_.begin(); iter != callbackMap_.end(); ++iter) {
        sptr<IUIService> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnReturnRequest(want, source, data, extraData);
    }
    HILOG_INFO("UIMgrService::ReturnRequest called end");
    return NO_ERROR;
}

int32_t UIMgrService::HandleRegister(const AAFwk::Want& want, const sptr<IUIService>& uiService)
{
    HILOG_INFO("UIMgrService::HandleRegister called start");
    std::lock_guard<std::mutex> lock(uiMutex_);
    std::string keyStr = GetCallBackKeyStr(want);
    HILOG_INFO("UIMgrService::HandleRegister keyStr = %{public}s", keyStr.c_str());
    bool exist = CheckCallBackFromMap(keyStr);
    if (exist) {
        callbackMap_.erase(keyStr);
    }
    callbackMap_.emplace(keyStr, uiService);
    HILOG_INFO("UIMgrService::HandleRegister called end callbackMap_.size() %{public}zu", callbackMap_.size());
    return NO_ERROR;
}

int32_t UIMgrService::HandleUnregister(const AAFwk::Want& want)
{
    HILOG_INFO("UIMgrService::HandleUnregister called start");
    std::lock_guard<std::mutex> lock(uiMutex_);
    std::string keyStr = GetCallBackKeyStr(want);
    bool exist = CheckCallBackFromMap(keyStr);
    if (!exist) {
        HILOG_ERROR("UIMgrService::HandleUnregister there is no keyStr in map.");
        return NO_CALLBACK_FOR_KEY;
    }
    callbackMap_.erase(keyStr);
    HILOG_INFO("UIMgrService::HandleUnregister called end");
    return NO_ERROR;
}

std::string UIMgrService::GetCallBackKeyStr(const AAFwk::Want& want)
{
    HILOG_INFO("UIMgrService::GetCallBackKeyStr called start");
    AppExecFwk::ElementName element =  want.GetElement();
    std::string bundleName = element.GetBundleName();
    std::string keyStr = bundleName;
    HILOG_INFO("UIMgrService::GetCallBackKeyStr called end");
    return keyStr;
}

bool UIMgrService::CheckCallBackFromMap(const std::string& key)
{
    HILOG_INFO("UIMgrService::CheckCallBackFromMap called start");
    auto it = callbackMap_.find(key);
    if (it == callbackMap_.end()) {
        return false;
    }
    HILOG_INFO("UIMgrService::CheckCallBackFromMap called end");
    return true;
}
}  // namespace Ace
}  // namespace OHOS
