/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "ui_sa_service.h"

#include "ipc_skeleton.h"
#include "iremote_object.h"
#include "string_ex.h"
#include "ui_content_proxy.h"
#include "ui_content_service_interface.h"
#include "window_manager.h"

#include "adapter/ohos/entrance/ui_session/include/ui_session_log.h"

namespace OHOS::Ace {

const bool REGISTER_RESULT = SystemAbility::MakeAndRegisterAbility(&UiSaService::GetInstance());
constexpr int32_t SIMPLIFYTREE_WITH_PARAMCONFIG = 4;
constexpr unsigned long int PARAMS_LENGTH_THREE  = 3;
constexpr unsigned long int PARAMS_LENGTH_TWO  = 2;

std::mutex uiContentRemoteObjMapMtx;

UiSaService::UiSaService() : SystemAbility(UI_SA_ID, true) {}

UiSaService& UiSaService::GetInstance()
{
    static UiSaService instance;
    return instance;
}

void UiSaService::OnStart()
{
    Publish(this);
}

void UiSaService::OnStop() {}

// If the current window ID is not in the corresponding map, clear the original map and insert it again. Otherwise,
// return.
sptr<Ace::IUiContentService> UiSaService::getArkUIService(int32_t windowId)
{
    std::unique_lock<std::mutex> lock(uiContentRemoteObjMapMtx);
    sptr<IRemoteObject> tmpRemoteObj = nullptr;
    sptr<Ace::IUiContentService> service = nullptr;
    if (uiContentRemoteObjMap.find(windowId) != uiContentRemoteObjMap.end()) {
        service = uiContentRemoteObjMap[windowId].second;
        return service;
    }
    auto ret = OHOS::Rosen::WindowManager::GetInstance().GetUIContentRemoteObj(windowId, tmpRemoteObj);
    if (tmpRemoteObj == nullptr) {
        LOGI("through uiSa, tempRemoteObj is null");
        return nullptr;
    }
    // add death callback
    auto uiSaServiceRecipient = new UiSaServiceRecipient([windowId, this]() {
        std::unique_lock<std::mutex> lock(uiContentRemoteObjMapMtx);
        LOGW("through uiSa, agent window dead,windowId:%{public}d", windowId);
        this->uiContentRemoteObjMap.erase(windowId);
    });
    tmpRemoteObj->AddDeathRecipient(uiSaServiceRecipient);
    LOGI("through uiSa, get UIContentRemoteObj. ret=%{public}u", static_cast<uint32_t>(ret));
    service = iface_cast<Ace::IUiContentService>(tmpRemoteObj);
    if (service == nullptr) {
        LOGI("through uiSa, getArkUIService:iface_cast<Ace::IUiContentService>(uiContentRemoteObj) failed.");
        return nullptr;
    }
    uiContentRemoteObjMap[windowId] = std::make_pair(tmpRemoteObj, service);
    return service;
}

int32_t UiSaService::Dump(int32_t fd, const std::vector<std::u16string>& args)
{
    if (fd < 0) {
        return ERR_INVALID_DATA;
    }
    OHOS::Rosen::FocusChangeInfo focusedWindowInfo;
    OHOS::Rosen::WindowManager::GetInstance().GetFocusWindowInfo(focusedWindowInfo);
    int32_t focusedWindowId = focusedWindowInfo.windowId_;
    auto service = getArkUIService(focusedWindowId);
    if (!service->IsConnect()) {
        LOGI("through uiSa, not connected.");
    }
    std::vector<std::string> params;
    for (const auto& arg : args) {
        const auto str = Str16ToStr8(arg);
        params.emplace_back(str);
    }

    if (!params.empty()) {
        if (params[0] == "Connect") {
            auto cb = [](std::string res) {
                LOGI("through uiSa, connect success , foucs window info = %{public}s", res.c_str());
            };
            if (!service->IsConnect()) {
                service->Connect(cb);
            }
        } else if (params[0] == "GetVisibleInspectorTree" && params.size() == SIMPLIFYTREE_WITH_PARAMCONFIG) {
            auto visibleInspectorTreeCallBack = [](const std::string& data, int32_t index, bool isEnd) {
                LOGI("through uiSa, data = %{public}s", data.c_str());
            };
            service->GetVisibleInspectorTree(
                visibleInspectorTreeCallBack, { params[1] == "true", params[2] == "true", params[3] == "true" });
        } else if (params[0] == "GetCurrentPageName") {
            auto getPageNameCallback = [](std::string data) {
                LOGI("through uiSa, currentPageName = %{public}s", data.c_str());
            };
            service->GetCurrentPageName(getPageNameCallback);
        } else if (params[0] == "SendCommand" && params.size() == PARAMS_LENGTH_THREE) {
            int32_t id = std::atoi(params[1].c_str());
            std::string command = params[2];
            service->SendCommand(id, command);
        } else if (params[0] == "SendCommand" && params.size() == PARAMS_LENGTH_TWO) {
            std::string command = params[1];
            service->SendCommand(command);
        } else if (params[0] == "SendCommandAsync" && params.size() == PARAMS_LENGTH_THREE) {
            int32_t id = std::atoi(params[1].c_str());
            std::string command = params[2];
            service->SendCommand(id, command);
            service->SendCommandAsync(id, command);
        }
    }

    return ERR_NONE;
}

void UiSaServiceRecipient::OnRemoteDied(const wptr<IRemoteObject>& remote)
{
    LOGI("through uiSa, uisaservice death notice");
    if (remote == nullptr) {
        LOGW("through uiSa, weak remote is null");
        return;
    }
    if (handler_) {
        handler_();
    }
}

} // namespace OHOS::Ace