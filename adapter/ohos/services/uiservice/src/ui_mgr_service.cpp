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
#include <unistd.h>

#include "hilog_wrapper.h"
#include "if_system_ability_manager.h"
#include "ipc_skeleton.h"
#include "securec.h"

#include "string_ex.h"
#include "system_ability_definition.h"
#include "ui_service_mgr_errors.h"
#include "uiservice_dialog/uiservice_dialog_impl.h"
#include "uiservice_dialog/uiservice_dialog_proxy.h"

namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t UI_MGR_SERVICE_SA_ID = 7001;
constexpr uint32_t UI_SERVICE_FLOGS = 0x10;
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

static std::atomic<int32_t> gDialogId = 0;

AppSpawnMsg* UIMgrService::MakeAppSpawnMsg(const std::string& name, int32_t id)
{
    size_t msgSize = sizeof(AppSpawnMsg) + 1;
    AppSpawnMsg* msg = static_cast<AppSpawnMsg *>(malloc(msgSize));
    if (msg == nullptr) {
        HILOG_ERROR("Ace uiservice failed to malloc!");
        return nullptr;
    }
    if (memset_s(msg, msgSize, 0, msgSize) != EOK) {
        HILOG_ERROR("Ace uiservice failed to memset!");
        return nullptr;
    }
    msg->uid = getuid();
    msg->gid = getgid();
    msg->accessTokenId = IPCSkeleton::GetCallingTokenID();
    std::string proccessName = name + std::to_string(id);
    if (strcpy_s(msg->processName, sizeof(msg->processName), proccessName.c_str()) != EOK) {
        HILOG_ERROR("failed to copy proccess name!");
        return nullptr;
    }

    msg->code = AppOperateType::DEFAULT;
    msg->flags = UI_SERVICE_FLOGS;
    return msg;
}

int32_t UIMgrService::AttachToUiService(const sptr<IRemoteObject>& dialog, int32_t pid)
{
    HILOG_INFO("Ace uiservice AttachToUiService pid: %{public}d", pid);
    if (dialog == nullptr) {
        HILOG_ERROR("Ace dialog is nullptr");
    }
    auto dialogProxy = iface_cast<OHOS::Ace::IUiServiceDialog>(dialog);
    if (dialogProxy == nullptr) {
        HILOG_ERROR("Ace dialogProxy is nullptr");
        return -1;
    }

    if (handler_ == nullptr) {
        HILOG_ERROR("Ace uiservice Show dialog failed! handler is nullptr");
        return UI_SERVICE_HANDLER_IS_NULL;
    }

    auto attachFunc = [ pid, dialogProxy, this ] () {
        dialogMap_.emplace(pid, dialogProxy);
        auto iter = dialogRecords_.find(pid);
        if (iter == dialogRecords_.end()) {
            HILOG_ERROR("Ace no dialog record: %{public}d", pid);
            return;
        }
        auto dialogRecord = iter->second;
        dialogProxy->ShowDialog(
            dialogRecord.name, dialogRecord.params, dialogRecord.windowType,
            dialogRecord.x, dialogRecord.y, dialogRecord.width, dialogRecord.height,
            dialogRecord.id);
    };

    if (!handler_->PostSyncTask(attachFunc)) {
        HILOG_ERROR("Post sync task error");
        return UI_SERVICE_POST_TASK_FAILED;
    }

    return NO_ERROR;
}

int UIMgrService::ShowDialog(
    const std::string& name,
    const std::string& params,
    uint32_t windowType,
    int x,
    int y,
    int width,
    int height,
    const sptr<OHOS::Ace::IDialogCallback>& dialogCallback,
    int* id)
{
    if (OpenAppSpawnConnection() != 0) {
        HILOG_ERROR("Ace ShowDialog ui service failed to open app spawn connection.");
        return UI_SERVICE_HANDLER_IS_NULL;
    }
    HILOG_INFO("Ace uiservice Show dialog name: %{public}s in service start %{public}s", name.c_str(), params.c_str());
    if (handler_ == nullptr) {
        HILOG_ERROR("Ace uiservice Show dialog failed! handler is nullptr");
        return UI_SERVICE_HANDLER_IS_NULL;
    }

    int32_t dialogId = gDialogId.fetch_add(1, std::memory_order_relaxed);
    if (id != nullptr) {
        *id = dialogId;
    }
    HILOG_INFO("Ace uiservice Show dialog id: %{public}d", dialogId);
    DialogParam dialogParams = {
        name, params, static_cast<uint32_t>(windowType), x, y, width, height, dialogId };
    auto showDialogFunc = [dialogId, &name, &dialogParams, dialogCallback, this] () {
        AppSpawnMsg* message = MakeAppSpawnMsg(name, dialogId);
        AppSpawnPidMsg pidMsg;
        auto result = clientSocket_->WriteSocketMessage(message, sizeof(AppSpawnMsg));
        if (result != sizeof(AppSpawnMsg)) {
            HILOG_ERROR("Ace uiservice WriteMessage failed!");
            return;
        }
        result = clientSocket_->ReadSocketMessage(reinterpret_cast<void *>(pidMsg.pidBuf), sizeof(pid_t));
        if (result !=  sizeof(pid_t)) {
            HILOG_ERROR("Ace uiservice ReadMessage failed!");
            return;
        }
        HILOG_INFO("Ace uiservice id: %{public}d", pidMsg.pid);
        dialogIDMap_.emplace(dialogId, pidMsg.pid);
        dialogRecords_.emplace(pidMsg.pid, dialogParams);
        dialogCallbackProxyMap_.emplace(dialogId, dialogCallback);
        return;
    };

    if (!handler_->PostSyncTask(showDialogFunc)) {
        HILOG_ERROR("Post sync task error");
        return UI_SERVICE_POST_TASK_FAILED;
    }

    return NO_ERROR;
}

int UIMgrService::CancelDialog(int id)
{
    HILOG_INFO("Ace CancelDialog id: %{public}d", id);
    auto errorCode = UI_SERVICE_NO_ERROR;
    if (handler_ == nullptr) {
        HILOG_ERROR("Ace uiservice Show dialog failed! handler is nullptr");
        return UI_SERVICE_HANDLER_IS_NULL;
    }

    auto cancelDialogFunc = [ id, this ] () {
        auto pidIter = dialogIDMap_.find(id);
        if (pidIter == dialogIDMap_.end()) {
            HILOG_ERROR("Ace dialog id : %{public}d not found in pid map", id);
            return;
        }
        int32_t pid = pidIter->second;
        auto dialogIter = dialogMap_.find(pid);
        if (dialogIter == dialogMap_.end()) {
            HILOG_ERROR("Ace dialog pid : %{public}d not found in dialog map", pid);
            return;
        }
        dialogIter->second->CancelDialog(id);
    };

    if (!handler_->PostSyncTask(cancelDialogFunc)) {
        errorCode = UI_SERVICE_POST_TASK_FAILED;
    }
    HILOG_INFO("Ace uidialog cancel end");
    return errorCode;
}

int UIMgrService::UpdateDialog(int id, const std::string& data)
{
    HILOG_INFO("Ace UpdateDialog id: %{public}d", id);
    auto errorCode = UI_SERVICE_NO_ERROR;
    if (handler_ == nullptr) {
        HILOG_ERROR("Ace uiservice Show dialog failed! handler is nullptr");
        return UI_SERVICE_HANDLER_IS_NULL;
    }

    auto updateDialogFunc = [ id, data, this] () {
        auto pidIter = dialogIDMap_.find(id);
        if (pidIter == dialogIDMap_.end()) {
            HILOG_ERROR("Ace dialog id : %{public}d not found in pid map", id);
            return;
        }
        int32_t pid = pidIter->second;
        auto dialogIter = dialogMap_.find(pid);
        if (dialogIter == dialogMap_.end()) {
            HILOG_ERROR("Ace dialog pid : %{public}d not found in dialog map", pid);
            return;
        }
        dialogIter->second->UpdateDialog(id, data);
    };

    if (!handler_->PostSyncTask(updateDialogFunc)) {
        errorCode = UI_SERVICE_POST_TASK_FAILED;
    }
    HILOG_INFO("Ace uidialog update end");
    return errorCode;
}

int32_t UIMgrService::RemoteDialogCallback(int32_t id, const std::string& event, const std::string& params)
{
    HILOG_INFO("Ace RemoteDialogCallback id: %{public}d", id);
    auto errorCode = UI_SERVICE_NO_ERROR;
    if (handler_ == nullptr) {
        HILOG_ERROR("Ace uiservice Show dialog failed! handler is nullptr");
        return UI_SERVICE_HANDLER_IS_NULL;
    }

    auto remoteDialogCallback = [ id, event, params, this] () {
        auto dialogProxyIter = dialogCallbackProxyMap_.find(id);
        if (dialogProxyIter == dialogCallbackProxyMap_.end()) {
            HILOG_ERROR("Ace no dialog proxy for id: %{public}d", id);
            return;
        }
        dialogProxyIter->second->OnDialogCallback(id, event, params);
    };

    if (!handler_->PostSyncTask(remoteDialogCallback)) {
        errorCode = UI_SERVICE_POST_TASK_FAILED;
    }
    HILOG_INFO("Ace uidialog RemoteDialogCallback end");
    return errorCode;
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

int32_t UIMgrService::OpenAppSpawnConnection()
{
    if (clientSocket_ == nullptr) {
        clientSocket_ = std::make_shared<AppSpawn::ClientSocket>("AppSpawn");
        if (clientSocket_ == nullptr) {
            HILOG_ERROR("Ace ui service create app spawn socket client failed.");
            return -1;
        }
        if (clientSocket_->CreateClient() != ERR_OK) {
            HILOG_ERROR("Ace ui service failed to create socketClient");
            return -1;
        }
        if (clientSocket_->ConnectSocket() != ERR_OK) {
            HILOG_ERROR("Ace ui service failed to connect socket");
            clientSocket_->CloseClient();
            return -1;
        }
        HILOG_INFO("Ace ui service connection has been opened");
    }
    return 0;
}

void UIMgrService::CloseAppSpawnConnection()
{
    if (clientSocket_ != nullptr) {
        clientSocket_->CloseClient();
        HILOG_INFO("Ace ui service connection has been closed");
        return;
    }
    HILOG_INFO("Ace ui service app spawn socket client is null.");
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
    eventLoop_.reset();
    handler_.reset();
    state_ = UIServiceRunningState::STATE_NOT_START;
    CloseAppSpawnConnection();
}

UIServiceRunningState UIMgrService::QueryServiceState() const
{
    return state_;
}

int UIMgrService::RegisterCallBack(const AAFwk::Want& want, const sptr<IUIService>& uiService)
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

int UIMgrService::UnregisterCallBack(const AAFwk::Want& want)
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

int UIMgrService::Push(const AAFwk::Want& want, const std::string& name,
    const std::string& jsonPath, const std::string& data, const std::string& extraData)
{
    HILOG_INFO("UIMgrService::Push called start");
    std::map<std::string, sptr<IUIService>>::iterator iter;
    std::lock_guard<std::mutex> lock(uiMutex_);
    for (iter = callbackMap_.begin(); iter != callbackMap_.end(); ++iter) {
        sptr<IUIService> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnPushCallBack(want, name, jsonPath, data, extraData);
    }
    HILOG_INFO("UIMgrService::Push called end");
    return NO_ERROR;
}

int UIMgrService::Request(const AAFwk::Want& want, const std::string& name, const std::string& data)
{
    HILOG_INFO("UIMgrService::Request called start");
    std::map<std::string, sptr<IUIService>>::iterator iter;
    std::lock_guard<std::mutex> lock(uiMutex_);
    for (iter = callbackMap_.begin(); iter != callbackMap_.end(); ++iter) {
        sptr<IUIService> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnRequestCallBack(want, name, data);
    }
    HILOG_INFO("UIMgrService::Request called end");
    return NO_ERROR;
}

int UIMgrService::ReturnRequest(
    const AAFwk::Want& want, const std::string& source, const std::string& data, const std::string& extraData)
{
    HILOG_INFO("UIMgrService::ReturnRequest called start");
    std::map<std::string, sptr<IUIService>>::iterator iter;
    for (iter = callbackMap_.begin(); iter != callbackMap_.end(); ++iter) {
        sptr<IUIService> uiService = iter->second;
        if (uiService == nullptr) {
            return UI_SERVICE_IS_NULL;
        }
        uiService->OnReturnRequest(want, source, data, extraData);
    }
    HILOG_INFO("UIMgrService::ReturnRequest called end");
    return NO_ERROR;
}
std::shared_ptr<EventHandler> UIMgrService::GetEventHandler()
{
    return handler_;
}

int UIMgrService::HandleRegister(const AAFwk::Want& want, const sptr<IUIService>& uiService)
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

int UIMgrService::HandleUnregister(const AAFwk::Want& want)
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
