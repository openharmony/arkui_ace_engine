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

#include "ui_service_mgr_client_idl.h"

#include "iservice_registry.h"
#include "ui_service_hilog.h"

namespace OHOS {
namespace Ace {
constexpr int32_t UI_MGR_SERVICE_SA_ID = 7001;
std::mutex UIServiceMgrClientIdl::mutex_;

std::shared_ptr<UIServiceMgrClientIdl> UIServiceMgrClientIdl::GetInstance()
{
    static auto instance = std::make_shared<UIServiceMgrClientIdl>();
    return instance;
}

UIServiceMgrClientIdl::UIServiceMgrClientIdl()
{
    LOGI("UIService Client is created");
}

UIServiceMgrClientIdl::~UIServiceMgrClientIdl()
{
    LOGI("UIService Client is destroyed");
}

ErrCode UIServiceMgrClientIdl::RegisterCallBack(const AAFwk::Want& want, const sptr<IUIServiceNew>& uiService)
{
    if (remoteObject_ == nullptr) {
        ErrCode err = Connect();
        if (err != ERR_OK) {
            LOGW("%{private}s:fail to connect UIMgrService", __func__);
            return UI_SERVICE_NOT_CONNECTED;
        }
    }
    sptr<IUIServiceMgrNew> doms = iface_cast<IUIServiceMgrNew>(remoteObject_);
    return doms->RegisterCallBack(want, uiService);
}

ErrCode UIServiceMgrClientIdl::UnregisterCallBack(const AAFwk::Want& want)
{
    if (remoteObject_ == nullptr) {
        ErrCode err = Connect();
        if (err != ERR_OK) {
            LOGW("%{private}s:fail to connect UIMgrService", __func__);
            return UI_SERVICE_NOT_CONNECTED;
        }
    }
    sptr<IUIServiceMgrNew> doms = iface_cast<IUIServiceMgrNew>(remoteObject_);
    return doms->UnregisterCallBack(want);
}

ErrCode UIServiceMgrClientIdl::Push(const AAFwk::Want& want, const std::string& name, const std::string& jsonPath,
    const std::string& data, const std::string& extraData)
{
    if (remoteObject_ == nullptr) {
        ErrCode err = Connect();
        if (err != ERR_OK) {
            LOGW("%{private}s:fail to connect UIMgrService", __func__);
            return UI_SERVICE_NOT_CONNECTED;
        }
    }
    sptr<IUIServiceMgrNew> doms = iface_cast<IUIServiceMgrNew>(remoteObject_);
    return doms->Push(want, name, jsonPath, data, extraData);
}

ErrCode UIServiceMgrClientIdl::Request(const AAFwk::Want& want, const std::string& name, const std::string& data)
{
    if (remoteObject_ == nullptr) {
        ErrCode err = Connect();
        if (err != ERR_OK) {
            LOGW("%{private}s:fail to connect UIMgrService", __func__);
            return UI_SERVICE_NOT_CONNECTED;
        }
    }
    sptr<IUIServiceMgrNew> doms = iface_cast<IUIServiceMgrNew>(remoteObject_);
    return doms->Request(want, name, data);
}

ErrCode UIServiceMgrClientIdl::ReturnRequest(const AAFwk::Want& want, const std::string& source,
    const std::string& data, const std::string& extraData)
{
    if (remoteObject_ == nullptr) {
        ErrCode err = Connect();
        if (err != ERR_OK) {
            LOGW("%{private}s:fail to connect UIMgrService", __func__);
            return UI_SERVICE_NOT_CONNECTED;
        }
    }
    sptr<IUIServiceMgrNew> doms = iface_cast<IUIServiceMgrNew>(remoteObject_);
    return doms->ReturnRequest(want, source, data, extraData);
}

ErrCode UIServiceMgrClientIdl::ShowDialog(const std::string& name, const std::string& params,
    OHOS::Rosen::WindowType windowType, int32_t x, int32_t y, int32_t width, int32_t height,
    DialogCallback callback, int32_t* id)
{
    return GET_UI_SERVICE_FAILED;
}

ErrCode UIServiceMgrClientIdl::CancelDialog(int32_t id)
{
    return GET_UI_SERVICE_FAILED;
}

ErrCode UIServiceMgrClientIdl::UpdateDialog(int32_t id, const std::string& data)
{
    return GET_UI_SERVICE_FAILED;
}

/**
 * Connect ui_service manager service.
 *
 * @return Returns ERR_OK on success, others on failure.
 */
ErrCode UIServiceMgrClientIdl::Connect()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (remoteObject_ != nullptr) {
        return ERR_OK;
    }
    sptr<ISystemAbilityManager> systemManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemManager == nullptr) {
        LOGW("%{private}s:fail to get Registry", __func__);
        return GET_UI_SERVICE_FAILED;
    }
    remoteObject_ = systemManager->GetSystemAbility(UI_MGR_SERVICE_SA_ID);
    if (remoteObject_ == nullptr) {
        LOGW("%{private}s:fail to connect UIMgrService", __func__);
        return GET_UI_SERVICE_FAILED;
    }
    return ERR_OK;
}
}  // namespace Ace
}  // namespace OHOS
