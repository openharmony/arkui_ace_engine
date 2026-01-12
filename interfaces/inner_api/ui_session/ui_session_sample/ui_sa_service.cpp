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

#include <fstream>
#include <sys/time.h>

#include "ipc_skeleton.h"
#include "iremote_object.h"
#include "string_ex.h"
#include "ui_content_proxy.h"
#include "ui_content_service_interface.h"
#include "window_manager.h"

#include "adapter/ohos/entrance/ui_session/include/ui_session_log.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/utils/utils.h"

namespace OHOS::Ace {

const bool REGISTER_RESULT = SystemAbility::MakeAndRegisterAbility(&UiSaService::GetInstance());
const std::string UI_SA_PATH = "/data/service/el1/public/ui_sa/";
constexpr int32_t PARAMS_OFFSET = 1;
constexpr int32_t SIMPLIFYTREE_WITH_PARAMCONFIG = 5;
constexpr int32_t SEND_COMMAND_WITH_NODEID = 3;
constexpr int32_t SEND_COMMAND_WITHOUT_NODEID = 2;
constexpr int32_t COMPONENT_CHANGE_EVENT_WITH_CONFIG = 3;

const std::map<std::string, UiSaService::DumpHandler> UiSaService::DUMP_MAP = {
    { "Connect", &UiSaService::HandleConnect },
    { "GetVisibleInspectorTree", &UiSaService::HandleGetVisibleInspectorTree },
    { "GetCurrentPageName", &UiSaService::HandleGetCurrentPageName },
    { "SendCommand", &UiSaService::HandleSendCommand },
    { "SendCommandAsync", &UiSaService::HandleSendCommandAsync },
    { "RegisterContentChangeCallback", &UiSaService::HandleRegisterContentChangeCallback },
    { "UnregisterContentChangeCallback", &UiSaService::HandleUnregisterContentChangeCallback },
    { "GetCurrentImagesShowing", &UiSaService::HandleGetCurrentImagesShowing },
    { "GetImagesById", &UiSaService::HandleGetImagesById },
};

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

std::string GetCurrentTimestampStr()
{
    constexpr int64_t SEC_TO_MILLISEC = 1000;
    constexpr int64_t MILLISEC_TO_MICROSEC = 1000;
    constexpr int32_t MAX_TIME_STR_LEN = 64;

    struct timeval currentTime;
    gettimeofday(&currentTime, nullptr);
    int64_t timestamp =
        static_cast<int64_t>(currentTime.tv_sec) * SEC_TO_MILLISEC + currentTime.tv_usec / MILLISEC_TO_MICROSEC;

    char timeStr[MAX_TIME_STR_LEN];
    // timestamp is in millisecond unit, divide 1000 to second
    auto t = static_cast<std::time_t>(timestamp / SEC_TO_MILLISEC);
    auto local = std::localtime(&t);
    if (!local) {
        return "";
    }
    std::strftime(timeStr, MAX_TIME_STR_LEN, "%Y-%m-%d %H:%M:%S", local);
    std::stringstream oss;
    // milliseconds in timestr should be 3 characters length
    oss << timeStr << "." << std::setw(3) << std::setfill('0') << (timestamp % SEC_TO_MILLISEC);
    return oss.str();
}

// If the current window ID is not in the corresponding map, clear the original map and insert it again. Otherwise,
// return.
sptr<Ace::IUiContentService> UiSaService::getArkUIService(int32_t windowId)
{
    std::unique_lock<std::mutex> lock(uiContentRemoteObjMapMtx_);
    sptr<IRemoteObject> tmpRemoteObj = nullptr;
    sptr<Ace::IUiContentService> service = nullptr;
    if (uiContentRemoteObjMap_.find(windowId) != uiContentRemoteObjMap_.end()) {
        service = uiContentRemoteObjMap_[windowId].second;
        return service;
    }
    auto ret = OHOS::Rosen::WindowManager::GetInstance().GetUIContentRemoteObj(windowId, tmpRemoteObj);
    if (tmpRemoteObj == nullptr) {
        LOGI("through uiSa, tempRemoteObj is null");
        return nullptr;
    }
    LOGI("through uiSa, get UIContentRemoteObj. ret=%{public}u", static_cast<uint32_t>(ret));
    // add death callback
    auto uiContentProxyRecipient = new UiContentProxyRecipient([windowId, this]() {
        std::unique_lock<std::mutex> lock(uiContentRemoteObjMapMtx_);
        LOGW("through uiSa, agent window dead, windowId:%{public}d", windowId);
        this->uiContentRemoteObjMap_.erase(windowId);
    });
    tmpRemoteObj->AddDeathRecipient(uiContentProxyRecipient);
    service = iface_cast<Ace::IUiContentService>(tmpRemoteObj);
    if (service == nullptr) {
        LOGW("through uiSa, cast to IUiContentService failed.");
        return nullptr;
    }
    uiContentRemoteObjMap_[windowId] = std::make_pair(tmpRemoteObj, service);
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
    CHECK_NULL_RETURN(service, ERR_INVALID_DATA);
    if (!service->IsConnect()) {
        LOGW("through uiSa, not connected.");
    }
    std::vector<std::string> params;
    for (const auto& arg : args) {
        const auto str = Str16ToStr8(arg);
        params.emplace_back(str);
    }

    if (!params.empty()) {
        auto it = DUMP_MAP.find(params[0]);
        if (it == DUMP_MAP.end()) {
            LOGW("through uiSa, invalid function name.");
            return ERR_INVALID_DATA;
        }
        DumpHandler handler = it->second;
        (this->*handler)(service, params);
    }

    return ERR_NONE;
}

void UiSaService::HandleConnect(sptr<IUiContentService> service, std::vector<std::string> params)
{
    auto cb = [](std::string res) {
        LOGI("through uiSa, connect success, foucs window info = %{public}s", res.c_str());
    };
    if (!service->IsConnect()) {
        service->Connect(cb);
    }
}

void UiSaService::HandleGetVisibleInspectorTree(sptr<IUiContentService> service, std::vector<std::string> params)
{
    bool toFile = params.back() == "-tofile";
    auto visibleInspectorTreeCallBack = [toFile, this](const std::string& data, int32_t index, bool isEnd) {
        LOGI("[GetVisibleInspectorTree] index: %{public}d, isEnd: %{public}d, data = %{public}s", index, isEnd,
            data.c_str());
        if (index == 1) {
            this->visibleInspectorTreeInfo_ = data;
        } else {
            this->visibleInspectorTreeInfo_.append(data);
        }
        if (isEnd && toFile) {
            auto filePath = UI_SA_PATH + "arkui_tree_" + GetCurrentTimestampStr() + ".json";
            std::unique_ptr<std::ofstream> ostream = std::make_unique<std::ofstream>(filePath);
            CHECK_NULL_VOID(ostream);
            if (!ostream->is_open()) {
                LOGW("[GetVisibleInspectorTree] filePath is invalid");
                return;
            }
            ostream->write(this->visibleInspectorTreeInfo_.c_str(), this->visibleInspectorTreeInfo_.length());
            LOGI("[GetVisibleInspectorTree] tree is saved to %{public}s", filePath.c_str());
        }
    };
    if (params.size() >= SIMPLIFYTREE_WITH_PARAMCONFIG) {
        service->GetVisibleInspectorTree(visibleInspectorTreeCallBack,
            { params[1] == "true", params[2] == "true", params[3] == "true", params[4] == "true" });
    } else {
        service->GetVisibleInspectorTree(visibleInspectorTreeCallBack);
    }
}

void UiSaService::HandleGetCurrentPageName(sptr<IUiContentService> service, std::vector<std::string> params)
{
    auto getPageNameCallback = [](std::string data) {
        LOGI("[GetCurrentPageName] currentPageName = %{public}s", data.c_str());
    };
    service->GetCurrentPageName(getPageNameCallback);
}

void UiSaService::HandleSendCommand(sptr<IUiContentService> service, std::vector<std::string> params)
{
    if (params.size() == SEND_COMMAND_WITH_NODEID) {
        int32_t id = std::atoi(params[1].c_str());
        std::string command = params[2];
        service->SendCommand(id, command);
    } else if (params.size() == SEND_COMMAND_WITHOUT_NODEID) {
        std::string command = params[1];
        service->SendCommand(command);
    }
}

void UiSaService::HandleSendCommandAsync(sptr<IUiContentService> service, std::vector<std::string> params)
{
    CHECK_EQUAL_VOID(params.size() == SEND_COMMAND_WITH_NODEID, false);
    int32_t id = std::atoi(params[1].c_str());
    std::string command = params[2];
    service->SendCommandAsync(id, command);
}

void UiSaService::HandleRegisterContentChangeCallback(sptr<IUiContentService> service, std::vector<std::string> params)
{
    bool toFile = params.back() == "-tofile";
    auto contentChangeCallback = [toFile](ChangeType type, const std::string& simpleTree) {
        const char* TYPE_DIR[6] = { "PAGE", "SCROLL", "SWIPER", "TABS", "TEXT", "DIALOG" };
        LOGI("[ContentChangeManager] callback type = %{public}d, tree: %{public}s", type,
            simpleTree.substr(0, 50).c_str());
        LOGI("[ContentChangeMgr_json] START Type: %{public}s", TYPE_DIR[(int)type]);
        for (size_t pos = 0; pos < simpleTree.length(); pos += 50) {
            LOGI("[ContentChangeMgr_json] %{public}s", simpleTree.substr(pos, 50).c_str());
        }
        LOGI("[ContentChangeMgr_json] END   Type: %{public}s", TYPE_DIR[(int)type]);
        if (toFile && simpleTree.length()) {
            auto filePath = UI_SA_PATH + "arkui_simpleTree_" + GetCurrentTimestampStr() + ".json";
            std::unique_ptr<std::ofstream> ostream = std::make_unique<std::ofstream>(filePath);
            CHECK_NULL_VOID(ostream);
            if (!ostream->is_open()) {
                LOGW("[ContentChangeManager] filePath is invalid");
                return;
            }
            ostream->write(simpleTree.c_str(), simpleTree.length());
            LOGI("[ContentChangeManager] tree is saved to %{public}s", filePath.c_str());
        }
    };
    ContentChangeConfig config;
    int32_t time = std::atoi((params.size() >= COMPONENT_CHANGE_EVENT_WITH_CONFIG ? params[1] : "100").c_str());
    float ratio = std::atof((params.size() >= COMPONENT_CHANGE_EVENT_WITH_CONFIG ? params[2] : "0.15").c_str());
    config.minReportTime = time;
    config.textContentRatio = ratio;
    service->RegisterContentChangeCallback(config, contentChangeCallback);
    LOGI("[ContentChangeManager] call RegisterContentChangeCallback");
}

void UiSaService::HandleUnregisterContentChangeCallback(
    sptr<IUiContentService> service, std::vector<std::string> params)
{
    service->UnregisterContentChangeCallback();
    LOGI("[ContentChangeManager] call UnregisterContentChangeCallback");
}

void UiSaService::HandleGetCurrentImagesShowing(sptr<IUiContentService> service, std::vector<std::string> params)
{
    auto finishCallback = [](std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> imageList) {
        LOGI("[GetCurrentImagesShowing] images size = %{public}zu", imageList.size());
        for (auto& [id, pixelmap] : imageList) {
            LOGI("[GetCurrentImagesShowing] id=%{public}d, pixelmap=%{public}p", id, pixelmap.get());
        }
    };
    service->GetCurrentImagesShowing(finishCallback);
    LOGI("[GetCurrentImagesShowing] call GetCurrentImagesShowing");
}

void UiSaService::HandleGetImagesById(sptr<IUiContentService> service, std::vector<std::string> params)
{
    int32_t idx = PARAMS_OFFSET;
    int32_t paramSize = static_cast<int32_t>(params.size());

    CHECK_EQUAL_VOID(idx < paramSize, false);
    int32_t arkUISize = std::atoi(params[idx++].c_str());
    CHECK_EQUAL_VOID(idx + arkUISize <= paramSize, false);
    std::vector<int32_t> arkUIIds;
    for (int32_t i = 0; i < arkUISize; i++) {
        arkUIIds.emplace_back(std::atoi(params[idx++].c_str()));
    }
    auto arkUIfinishCallback = [](int32_t winId,
                                   const std::unordered_map<int32_t, std::shared_ptr<Media::PixelMap>>& arkUIRes,
                                   MultiImageQueryErrorCode code) {
        LOGI("[GetImagesById] arkUIfinishCallback winId=%{public}d", winId);
        for (auto& [id, pixelmap] : arkUIRes) {
            LOGI("[GetImagesById] arkUIfinishCallback id=%{public}d, pixelmap=%{public}p", id, pixelmap.get());
        }
        LOGI("[GetImagesById] arkUIfinishCallback code=%{public}d", static_cast<int32_t>(code));
    };

    CHECK_EQUAL_VOID(idx < paramSize, false);
    int32_t arkWebSize = std::atoi(params[idx++].c_str());
    std::map<int32_t, std::vector<int32_t>> arkWebs;
    for (int32_t i = 0; i < arkWebSize; i++) {
        CHECK_EQUAL_VOID(idx < paramSize, false);
        int32_t arkWebId = std::atoi(params[idx++].c_str());
        CHECK_EQUAL_VOID(idx < paramSize, false);
        int32_t arkWebVecSize = std::atoi(params[idx++].c_str());
        CHECK_EQUAL_VOID(idx + arkWebVecSize <= paramSize, false);
        std::vector<int32_t> arkWebVec;
        for (int32_t j = 0; j < arkWebVecSize; j++) {
            arkWebVec.emplace_back(std::atoi(params[idx++].c_str()));
        }
        arkWebs[arkWebId] = arkWebVec;
    }
    auto arkWebfinishCallback =
        [](int32_t winId, const std::map<int32_t, std::map<int32_t, std::shared_ptr<Media::PixelMap>>>& arkWebRes,
            MultiImageQueryErrorCode code) {
            LOGI("[GetImagesById] arkWebfinishCallback winId=%{public}d", winId);
            for (auto& [id, webMap] : arkWebRes) {
                for (auto& [webImgId, pixelmap] : webMap)
                    LOGI("[GetImagesById] arkWebfinishCallback id=%{public}d, webImgId=%{public}d, pixelmap=%{public}p",
                        id, webImgId, pixelmap.get());
            }
            LOGI("[GetImagesById] arkWebfinishCallback code=%{public}d", static_cast<int32_t>(code));
        };

    service->GetImagesById(arkUIIds, arkUIfinishCallback, arkWebs, arkWebfinishCallback);
    LOGI("[GetImagesById] call GetImagesById");
}
} // namespace OHOS::Ace
