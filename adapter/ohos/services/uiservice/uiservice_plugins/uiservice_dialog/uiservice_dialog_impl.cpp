/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <dlfcn.h>
#include <unistd.h>

#include "ipc_skeleton.h"
#ifdef WITH_SELINUX
#include <policycoreutils.h>
#include <selinux/selinux.h>
#endif

#include "base/log/log.h"
#include "if_system_ability_manager.h"
#include "iservice_registry.h"

#include "system_ability_definition.h"

#include "uiservice_dialog/uiservice_dialog_impl.h"
#include "uiservice_dialog/uiservice_dialog_proxy.h"
#include "ui_service_mgr_interface.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t UI_MGR_SERVICE_SA_ID = 7001;
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_InitDialog()
{
    UiServiceDialogImpl::InitAceDialog();
}

sptr<UiServiceDialogImpl> UiServiceDialogImpl::nowDialog_;

UiServiceDialogImpl::UiServiceDialogImpl()
{
    requestFuncMap_ = {
        { SHOW_DIALOG, &UiServiceDialogImpl::OnShowDialogRequest },
        { UPDATE_DIALOG, &UiServiceDialogImpl::OnUpdateDialogRequest },
        { CANCEL_DIALOG, &UiServiceDialogImpl::OnCancelDialogRequest },
    };
}

UiServiceDialogImpl::~UiServiceDialogImpl()
{
    ClearSharedLib();
}

void* UiServiceDialogImpl::OpenSharedLib(const char* libName)
{
    void* handle = dlopen(libName, RTLD_LAZY);
    if (handle == nullptr) {
        LOGE("Failed to open %{public}s, error: %{public}s", libName, dlerror());
        return nullptr;
    }
    return handle;
}

void* UiServiceDialogImpl::GetFunc(void* libHandle, const char* funName)
{
    if (libHandle == nullptr) {
        LOGE("lib is null, cannot cet func %{public}s", funName);
        return nullptr;
    }
    void* func = dlsym(libHandle, funName);
    if (func == nullptr) {
        LOGE("Failed to get func %{public}s, error: %{public}s", funName, dlerror());
        return nullptr;
    }
    return func;
}

int UiServiceDialogImpl::OnRemoteRequest(
    uint32_t code,
    MessageParcel &data,
    MessageParcel &reply,
    MessageOption &option)
{
    LOGI("UiServiceDialogImpl::OnRemoteRequest, cmd = %{public}d, flags= %{public}d", code, option.GetFlags());
    if (UiServiceDialogImpl::GetDescriptor() != data.ReadInterfaceToken()) {
        LOGI("local descriptor is not equal to remote");
        return -1;
    }
    auto itFunc = requestFuncMap_.find(code);
    if (itFunc != requestFuncMap_.end()) {
        auto requestFunc = itFunc->second;
        if (requestFunc != nullptr) {
            return (this->*requestFunc)(data, reply);
        }
    }
    LOGW("UiServiceDialogStub::OnRemoteRequest, default case, need check.");
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t UiServiceDialogImpl::OnShowDialogRequest(MessageParcel& data, MessageParcel& reply)
{
    LOGI("OnShowDialogRequest called.");
    const std::string& name = data.ReadString();
    const std::string& params = data.ReadString();
    uint32_t windowType = data.ReadUint32();
    int32_t x = data.ReadInt32();
    int32_t y = data.ReadInt32();
    int32_t width = data.ReadInt32();
    int32_t height = data.ReadInt32();
    int32_t id = data.ReadInt32();
    int32_t result = ShowDialog(name, params, windowType, x, y, width, height, id);
    reply.WriteInt32(result);
    return result;
}

int32_t UiServiceDialogImpl::OnUpdateDialogRequest(MessageParcel &data, MessageParcel &reply)
{
    LOGI("OnUpdateDialogRequest called.");
    int32_t id = data.ReadInt32();
    std::string updateData = data.ReadString();
    int32_t result = UpdateDialog(id, updateData);
    reply.WriteInt32(result);
    return result;
}

int32_t UiServiceDialogImpl::OnCancelDialogRequest(MessageParcel& data, MessageParcel& reply)
{
    int32_t id = data.ReadInt32();
    int32_t result = CancelDialog(id);
    reply.WriteInt32(result);
    return result;
}

bool UiServiceDialogImpl::ClearSharedLib()
{
    bool res = true;
    if (dlclose(libHandle_) != 0) {
        LOGE("Failed to close lib, error: %{public}s", dlerror());
        res = false;
    }
    libHandle_ = nullptr;
    return res;
}

void UiServiceDialogImpl::InitAceDialog()
{
    LOGI("UiServiceDialogImpl Init begin");
#ifdef WITH_SELINUX
    setcon("u:r:sa_dialog:s0");
#endif
    nowDialog_ = new UiServiceDialogImpl();
    nowDialog_->Init();
}

bool UiServiceDialogImpl::InitSharedLib()
{
    constexpr char LIB_NAME[] = "libace.z.so";
    constexpr char CREATE_DIALOG_FUNC[] = "OHOS_ACE_CreateDialog";
    LOGI("UiServiceDialogImpl InitSharedLib");
    libHandle_ = OpenSharedLib(LIB_NAME);
    if (libHandle_ == nullptr) {
        return false;
    }
    auto createFunc = reinterpret_cast<void* (*)()>(GetFunc(libHandle_, CREATE_DIALOG_FUNC));
    if (createFunc == nullptr) {
        LOGE("get create dialog func failed.");
        ClearSharedLib();
        return false;
    }
    uidialog_ = reinterpret_cast<UIDialogBase*>(createFunc());
    if (uidialog_ == nullptr) {
        LOGE("create ui dialog failed.");
        ClearSharedLib();
        createFunc = nullptr;
        return false;
    }
    return true;
}

void UiServiceDialogImpl::Init()
{
    LOGI("UiServiceDialogImpl Init(): %{public}p", this);
    if (!InitSharedLib()) {
        return;
    }
    eventRunner_ = OHOS::AppExecFwk::EventRunner::GetMainEventRunner();
    if (eventRunner_ == nullptr) {
        LOGE("eventLoop create failed.");
        return;
    }

    eventHandler_ = std::make_shared<AppExecFwk::EventHandler>(eventRunner_);
    if (eventHandler_ == nullptr) {
        LOGE("handler create failed.");
        return;
    }

    sptr<ISystemAbilityManager> systemManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemManager == nullptr) {
        LOGE("fail to get Registry");
        return;
    }
    auto uiMgrService = systemManager->GetSystemAbility(UI_MGR_SERVICE_SA_ID);
    if (uiMgrService == nullptr) {
        LOGE("fail to connect UIMgrService");
        return;
    }

    sptr<IUIServiceMgr> uiServiceMgrProxy = iface_cast<IUIServiceMgr>(uiMgrService);
    uiServiceMgrProxy->AttachToUiService(nowDialog_->AsObject(), getpid());

    int32_t ret = eventRunner_->Run();
    if (ret != ERR_OK) {
        LOGE("run failed! reason: %{public}d", ret);
    }
}

void UiServiceDialogImpl::RemoteDialogCallback(int32_t id, const std::string& event, const std::string& params)
{
    LOGI("UiServiceDialogImpl::RemoteDialogCallback id: %{public}d", id);
    sptr<ISystemAbilityManager> systemManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemManager == nullptr) {
        LOGE("fail to get Registry");
        return;
    }
    auto uiMgrService = systemManager->GetSystemAbility(UI_MGR_SERVICE_SA_ID);
    if (uiMgrService == nullptr) {
        LOGE("fail to connect UIMgrService");
        return;
    }

    sptr<IUIServiceMgr> uiServiceMgrProxy = iface_cast<IUIServiceMgr>(uiMgrService);
    uiServiceMgrProxy->RemoteDialogCallback(id, event, params);
}

int32_t UiServiceDialogImpl::ShowDialog(
    const std::string& name,
    const std::string& params,
    uint32_t windowType,
    int x,
    int y,
    int width,
    int height,
    int32_t dialogId)
{
    LOGI("UiServiceDialogImpl Show Dialog id: %{public}d", dialogId);

    if (eventHandler_ == nullptr) {
        LOGE("UiServiceDialogImpl eventHandler is null");
        return -1;
    }
    if (uidialog_ == nullptr) {
        LOGE("Ui dialog instance not initialized.");
        return -1;
    }

    auto dialogCallback = std::bind(
        &UiServiceDialogImpl::RemoteDialogCallback, this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3);

    auto func = [ uidialog = uidialog_, name, params, windowType, x, y, width, height, dialogCallback, dialogId ]() {
        LOGI("UiServiceDialogImpl ShowDialog begin.");
        uidialog->ShowDialog(name, params, windowType, x, y, width, height, dialogCallback, dialogId);
    };
    eventHandler_->PostSyncTask(func);
    return 0;
}

int32_t UiServiceDialogImpl::CancelDialog(int32_t id)
{
    LOGI("Ace cancel dialog id: %{public}d", id);
    if (eventHandler_ == nullptr) {
        LOGE("UiServiceDialogImpl eventHandler is null");
        return -1;
    }
    if (uidialog_ == nullptr) {
        LOGE("Ui dialog instance not initialized.");
        return -1;
    }
    auto disableCallback = [ this ] () {
        LOGI("stop uidialog");
        eventRunner_->Stop();
        eventHandler_.reset();
        eventRunner_.reset();
    };

    auto func = [ uidialog = uidialog_, id, disableCallback ] () {
        uidialog->CancelDialog(id, disableCallback);
    };

    eventHandler_->PostTask(func);
    return 0;
}

int32_t UiServiceDialogImpl::UpdateDialog(int32_t id, const std::string& data)
{
    LOGI("Ace update dialog id: %{public}d", id);
    if (eventHandler_ == nullptr) {
        LOGE("UiServiceDialogImpl eventHandler is null");
        return -1;
    }
    if (uidialog_ == nullptr) {
        LOGE("Ui dialog instance not initialized.");
        return -1;
    }

    auto func = [ uidialog = uidialog_, id, data ] () {
        uidialog->UpdateDialog(id, data);
    };
    eventHandler_->PostTask(func);
    return 0;
}
}
