/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "ui_service_mgr_client.h"
#include "string_ex.h"
#include "hilog_wrapper.h"
#include "ipc_skeleton.h"
#include "iservice_registry.h"
#include "if_system_ability_manager.h"
#include "system_ability_definition.h"

namespace OHOS {
namespace Ace {
constexpr int UI_MGR_SERVICE_SA_ID = 7001;
std::shared_ptr<UIServiceMgrClient> UIServiceMgrClient::instance_ = nullptr;
std::mutex UIServiceMgrClient::mutex_;

std::shared_ptr<UIServiceMgrClient> UIServiceMgrClient::GetInstance()
{
    if (instance_ == nullptr) {
        std::lock_guard<std::mutex> lock_l(mutex_);
        if (instance_ == nullptr) {
            instance_ = std::make_shared<UIServiceMgrClient>();
        }
    }
    return instance_;
}

UIServiceMgrClient::UIServiceMgrClient()
{}

UIServiceMgrClient::~UIServiceMgrClient()
{}

ErrCode UIServiceMgrClient::RegisterCallBack(const AAFwk::Want& want, const sptr<IUIService>& uiService)
{
    if (remoteObject_ == nullptr) {
        ErrCode err = Connect();
        if (err != ERR_OK) {
            HILOG_ERROR("%{private}s:fail to connect UIMgrService", __func__);
            return UI_SERVICE_NOT_CONNECTED;
        }
    }
    sptr<IUIServiceMgr> doms = iface_cast<IUIServiceMgr>(remoteObject_);
    return doms->RegisterCallBack(want, uiService);
}

ErrCode UIServiceMgrClient::UnregisterCallBack(const AAFwk::Want& want)
{
    if (remoteObject_ == nullptr) {
        ErrCode err = Connect();
        if (err != ERR_OK) {
            HILOG_ERROR("%{private}s:fail to connect UIMgrService", __func__);
            return UI_SERVICE_NOT_CONNECTED;
        }
    }
    sptr<IUIServiceMgr> doms = iface_cast<IUIServiceMgr>(remoteObject_);
    return doms->UnregisterCallBack(want);
}

ErrCode UIServiceMgrClient::Push(const AAFwk::Want& want, const std::string& name, const std::string& jsonPath,
    const std::string& data, const std::string& extraData)
{
    if (remoteObject_ == nullptr) {
        ErrCode err = Connect();
        if (err != ERR_OK) {
            HILOG_ERROR("%{private}s:fail to connect UIMgrService", __func__);
            return UI_SERVICE_NOT_CONNECTED;
        }
    }
    sptr<IUIServiceMgr> doms = iface_cast<IUIServiceMgr>(remoteObject_);
    return doms->Push(want, name, jsonPath, data, extraData);
}

ErrCode UIServiceMgrClient::Request(const AAFwk::Want& want, const std::string& name, const std::string& data)
{
    if (remoteObject_ == nullptr) {
        ErrCode err = Connect();
        if (err != ERR_OK) {
            HILOG_ERROR("%{private}s:fail to connect UIMgrService", __func__);
            return UI_SERVICE_NOT_CONNECTED;
        }
    }
    sptr<IUIServiceMgr> doms = iface_cast<IUIServiceMgr>(remoteObject_);
    return doms->Request(want, name, data);
}

ErrCode UIServiceMgrClient::ReturnRequest(const AAFwk::Want& want, const std::string& source,
    const std::string& data, const std::string& extraData)
{
    if (remoteObject_ == nullptr) {
        ErrCode err = Connect();
        if (err != ERR_OK) {
            HILOG_ERROR("%{private}s:fail to connect UIMgrService", __func__);
            return UI_SERVICE_NOT_CONNECTED;
        }
    }
    sptr<IUIServiceMgr> doms = iface_cast<IUIServiceMgr>(remoteObject_);
    return doms->ReturnRequest(want, source, data, extraData);
}

/**
 * Connect ui_service manager service.
 *
 * @return Returns ERR_OK on success, others on failure.
 */
ErrCode UIServiceMgrClient::Connect()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (remoteObject_ != nullptr) {
        return ERR_OK;
    }
    sptr<ISystemAbilityManager> systemManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemManager == nullptr) {
        HILOG_ERROR("%{private}s:fail to get Registry", __func__);
        return GET_UI_SERVICE_FAILED;
    }
    remoteObject_ = systemManager->GetSystemAbility(UI_MGR_SERVICE_SA_ID);
    if (remoteObject_ == nullptr) {
        HILOG_ERROR("%{private}s:fail to connect UIMgrService", __func__);
        return GET_UI_SERVICE_FAILED;
    }
    HILOG_DEBUG("connect UIMgrService success");
    return ERR_OK;
}
}  // namespace Ace
}  // namespace OHOS
