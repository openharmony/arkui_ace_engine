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

#include "adapter/ohos/entrance/ui_session/ui_session_manager_ohos.h"

namespace OHOS::Ace {
std::mutex UiSessionManager::mutex_;
std::shared_mutex UiSessionManager::reportObjectMutex_;
std::shared_mutex UiSessionManager::translateManagerMutex_;
constexpr int32_t ONCE_IPC_SEND_DATA_MAX_SIZE = 131072;
UiSessionManager* UiSessionManager::GetInstance()
{
    static UiSessionManagerOhos instance;
    return &instance;
}

void UiSessionManagerOhos::ReportClickEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportClickEvent(data);
        } else {
            LOGW("report click event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportSearchEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportSearchEvent(data);
        } else {
            LOGW("report search event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportRouterChangeEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportRouterChangeEvent(data);
        } else {
            LOGW("report switch event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportComponentChangeEvent(const std::string& key, const std::string& value)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetComponentChangeEventRegistered()) {
            auto data = InspectorJsonUtil::Create();
            data->Put(key.data(), value.data());
            reportService->ReportComponentChangeEvent(data->ToString());
        } else {
            LOGW("report component change event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportComponentChangeEvent(
    int32_t nodeId, const std::string& key, const std::shared_ptr<InspectorJsonValue>& value)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetComponentChangeEventRegistered()) {
            auto data = InspectorJsonUtil::Create();
            data->Put("nodeId", nodeId);
            data->Put(key.data(), value->ToString().data());
            reportService->ReportComponentChangeEvent(data->ToString());
        } else {
            LOGW("report component event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportWebUnfocusEvent(int64_t accessibilityId, const std::string& data)
{
    auto jsonValue = InspectorJsonUtil::Create(true);
    jsonValue->Put("id", accessibilityId);
    jsonValue->Put("$type", "web");
    jsonValue->Put("text", data.c_str());
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportWebUnfocusEvent(accessibilityId, jsonValue->ToString());
        } else {
            LOGW("report web unfocus event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::SaveReportStub(sptr<IRemoteObject> reportStub, int32_t processId)
{
    // add death callback
    auto uiReportProxyRecipient = new UiReportProxyRecipient([processId, this]() {
        std::unique_lock<std::shared_mutex> reportLock(reportObjectMutex_);
        LOGW("agent process dead,processId:%{public}d", processId);
        // reportMap remove this processId
        this->reportObjectMap_.erase(processId);
    });
    reportStub->AddDeathRecipient(uiReportProxyRecipient);
    std::unique_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    reportObjectMap_[processId] = reportStub;
}

void UiSessionManagerOhos::SetClickEventRegistered(bool status)
{
    if (status) {
        clickEventRegisterProcesses_.fetch_add(1);
    } else {
        clickEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetSearchEventRegistered(bool status)
{
    if (status) {
        searchEventRegisterProcesses_.fetch_add(1);
    } else {
        searchEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetRouterChangeEventRegistered(bool status)
{
    if (status) {
        routerChangeEventRegisterProcesses_.fetch_add(1);
    } else {
        routerChangeEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetComponentChangeEventRegistered(bool status)
{
    if (status) {
        componentChangeEventRegisterProcesses_.fetch_add(1);
    } else {
        componentChangeEventRegisterProcesses_.fetch_sub(1);
    }
}

bool UiSessionManagerOhos::GetClickEventRegistered()
{
    return clickEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetSearchEventRegistered()
{
    return searchEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetRouterChangeEventRegistered()
{
    return routerChangeEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetComponentChangeEventRegistered()
{
    return componentChangeEventRegisterProcesses_.load() > 0 ? true : false;
}

void UiSessionManagerOhos::GetInspectorTree()
{
    webTaskNums_.store(0);
    WebTaskNumsChange(1);
    std::unique_lock<std::mutex> lock(mutex_);
    jsonValue_ = InspectorJsonUtil::Create(true);
    if (inspectorFunction_) {
        inspectorFunction_(false);
    }
}

void UiSessionManagerOhos::GetVisibleInspectorTree()
{
    if (inspectorFunction_) {
        inspectorFunction_(true);
    }
}

void UiSessionManagerOhos::SaveInspectorTreeFunction(InspectorFunction&& function)
{
    std::unique_lock<std::mutex> lock(mutex_);
    inspectorFunction_ = std::move(function);
}

void UiSessionManagerOhos::AddValueForTree(int32_t id, const std::string& value)
{
    std::unique_lock<std::mutex> lock(mutex_);
    std::string key = std::to_string(id);
    if (jsonValue_->Contains(key)) {
        jsonValue_->Replace(key.c_str(), value.c_str());
    } else {
        jsonValue_->Put(key.c_str(), value.c_str());
    }
}

void UiSessionManagerOhos::WebTaskNumsChange(int32_t num)
{
    webTaskNums_.fetch_add(num);
    if (webTaskNums_.load() == 0) {
        std::unique_lock<std::mutex> lock(mutex_);
        std::string data = jsonValue_->ToString();
        lock.unlock();
        ReportInspectorTreeValue(data);
    }
}

void UiSessionManagerOhos::ReportInspectorTreeValue(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            size_t partSize = data.size() / ONCE_IPC_SEND_DATA_MAX_SIZE;
            for (size_t i = 0; i <= partSize; i++) {
                if (i != partSize) {
                    reportService->ReportInspectorTreeValue(
                        data.substr(i * ONCE_IPC_SEND_DATA_MAX_SIZE, ONCE_IPC_SEND_DATA_MAX_SIZE), i + 1, false);
                } else {
                    reportService->ReportInspectorTreeValue(data.substr(i * ONCE_IPC_SEND_DATA_MAX_SIZE), i + 1, true);
                }
            }
        } else {
            LOGW("report component event failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::NotifyAllWebPattern(bool isRegister)
{
    std::unique_lock<std::mutex> lock(mutex_);
    webFocusEventRegistered = isRegister;
    notifyWebFunction_(isRegister);
}

void UiSessionManagerOhos::NotifySendCommandPattern(int32_t id, const std::string& command)
{
    notifySendCommandFunction_(id, command);
}

int32_t UiSessionManagerOhos::NotifySendCommandAsyncPattern(int32_t id, const std::string& command)
{
    return notifySendCommandAsyncFunction_(id, command);
}

void UiSessionManagerOhos::SaveRegisterForWebFunction(NotifyAllWebFunction&& function)
{
    std::unique_lock<std::mutex> lock(mutex_);
    notifyWebFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveForSendCommandFunction(NotifySendCommandFunction&& function)
{
    notifySendCommandFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveForSendCommandAsyncFunction(NotifySendCommandAsyncFunction&& function)
{
    notifySendCommandAsyncFunction_ = std::move(function);
}

bool UiSessionManagerOhos::GetWebFocusRegistered()
{
    std::unique_lock<std::mutex> lock(mutex_);
    return webFocusEventRegistered;
}

void UiSessionManagerOhos::OnRouterChange(const std::string& path, const std::string& event)
{
    if (GetRouterChangeEventRegistered()) {
        auto value = InspectorJsonUtil::Create(true);
        value->Put("path", path.c_str());
        value->Put("event", event.c_str());
        ReportRouterChangeEvent(value->ToString());
    }
}

void UiSessionManagerOhos::SaveBaseInfo(const std::string& info)
{
    std::unique_lock<std::mutex> lock(mutex_);
    baseInfo_ = info;
}

void UiSessionManagerOhos::SendBaseInfo(int32_t processId)
{
    std::unique_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    auto reportService = iface_cast<ReportService>(reportObjectMap_[processId]);
    reportLock.unlock();
    if (reportService != nullptr) {
        std::unique_lock<std::mutex> lock(mutex_);
        reportService->SendBaseInfo(baseInfo_);
    }
}

void UiSessionManagerOhos::SaveGetPixelMapFunction(GetPixelMapFunction&& function)
{
    getPixelMapFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveTranslateManager(std::shared_ptr<UiTranslateManager> uiTranslateManager,
    int32_t instanceId)
{
    std::unique_lock<std::shared_mutex> reportLock(translateManagerMutex_);
    translateManagerMap_[instanceId] = uiTranslateManager;
}

void UiSessionManagerOhos::SaveGetCurrentInstanceIdCallback(std::function<int32_t()>&& callback)
{
    std::unique_lock<std::mutex> lock(mutex_);
    getInstanceIdCallback_ = std::move(callback);
}

void UiSessionManagerOhos::RemoveSaveGetCurrentInstanceId(int32_t instanceId)
{
    translateManagerMap_.erase(instanceId);
}

std::shared_ptr<UiTranslateManager> UiSessionManagerOhos::GetCurrentTranslateManager()
{
    std::shared_ptr<UiTranslateManager> currentTranslateManager = nullptr;

    if (getInstanceIdCallback_) {
        int32_t instanceId = getInstanceIdCallback_();
        auto iter = translateManagerMap_.find(instanceId);
        if (iter != translateManagerMap_.end()) {
            auto translateManager = iter->second;
            if (translateManager) {
                currentTranslateManager = translateManager;
            }
        }
    }
    return  currentTranslateManager;
}

void UiSessionManagerOhos::GetWebViewLanguage()
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);

    auto  currentTranslateManager = GetCurrentTranslateManager();
    if (currentTranslateManager) {
        currentTranslateManager->GetWebViewCurrentLanguage();
    } else {
        LOGE("translateManager is nullptr ,translate failed");
    }
}

void UiSessionManagerOhos::RegisterPipeLineGetCurrentPageName(std::function<std::string()>&& callback)
{
    std::unique_lock<std::mutex> lock(mutex_);
    pipelineContextPageNameCallback_ = std::move(callback);
}

void UiSessionManagerOhos::GetCurrentPageName()
{
    if (pipelineContextPageNameCallback_) {
        auto result = pipelineContextPageNameCallback_();
        SendCurrentPageName(result);
    }
}

void UiSessionManagerOhos::SendCurrentPageName(const std::string& result)
{
    for (auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->SendCurrentPageName(result);
        } else {
            LOGW("report send current page name failed,process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::SaveProcessId(std::string key, int32_t id)
{
    processMap_[key] = id;
}

void UiSessionManagerOhos::SendCurrentLanguage(std::string result)
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);
    auto reportService = iface_cast<ReportService>(reportObjectMap_[processMap_["translate"]]);
    if (reportService) {
        reportService->SendCurrentLanguage(result);
    } else {
    }
}
void UiSessionManagerOhos::GetWebTranslateText(std::string extraData, bool isContinued)
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);

    auto  currentTranslateManager = GetCurrentTranslateManager();
    if (currentTranslateManager) {
        currentTranslateManager->GetTranslateText(extraData, isContinued);
    } else {
        LOGE("translateManager is nullptr ,translate failed");
    }
}

void UiSessionManagerOhos::SendWebTextToAI(int32_t nodeId, std::string res)
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);
    auto reportService = iface_cast<ReportService>(reportObjectMap_[processMap_["translate"]]);
    if (reportService != nullptr) {
        reportService->SendWebText(nodeId, res);
    } else {
        LOGW("report component event failed,process id:%{public}d", processMap_["translate"]);
    }
}

void UiSessionManagerOhos::SendTranslateResult(
    int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids)
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);

    auto  currentTranslateManager = GetCurrentTranslateManager();
    if (currentTranslateManager) {
        currentTranslateManager->SendTranslateResult(nodeId, results, ids);
    } else {
        LOGE("translateManager is nullptr ,translate failed");
    }
}

void UiSessionManagerOhos::SendTranslateResult(int32_t nodeId, std::string res)
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);

    auto  currentTranslateManager = GetCurrentTranslateManager();
    if (currentTranslateManager) {
        currentTranslateManager->SendTranslateResult(nodeId, res);
    } else {
        LOGE("translateManager is nullptr ,translate failed");
    }
}

void UiSessionManagerOhos::ResetTranslate(int32_t nodeId)
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);

    auto  currentTranslateManager = GetCurrentTranslateManager();
    if (currentTranslateManager) {
        currentTranslateManager->ResetTranslate(nodeId);
    } else {
        LOGE("translateManager is nullptr ,translate failed");
    }
}

void UiSessionManagerOhos::GetPixelMap()
{
    if (getPixelMapFunction_) {
        getPixelMapFunction_();
    } else {
        LOGW("get pixelMap func is nullptr");
    }
}

void UiSessionManagerOhos::SendPixelMap(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> maps)
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);
    std::shared_ptr<UiTranslateManager> translateManager = nullptr;

    auto  currentTranslateManager = GetCurrentTranslateManager();

    if (!currentTranslateManager) {
        LOGW("send pixelMap failed,translateManager is nullptr");
    }
    auto reportService = iface_cast<ReportService>(reportObjectMap_[processMap_["pixel"]]);
    if (reportService != nullptr) {
        reportService->SendShowingImage(maps);
        if (currentTranslateManager) {
            currentTranslateManager->ClearMap();
        }
    } else {
        LOGW("send pixel maps failed,process id:%{public}d", processMap_["pixel"]);
    }
}

bool UiSessionManagerOhos::IsHasReportObject()
{
    return !reportObjectMap_.empty();
}

void UiSessionManagerOhos::SendCommand(const std::string& command)
{
    if (sendCommandFunction_) {
        auto json = InspectorJsonUtil::ParseJsonString(command);
        if (!json || json->IsNull()) {
            LOGW("SendCommand ParseJsonString failed");
            return;
        }

        int32_t value = json->GetInt("cmd");
        sendCommandFunction_(value);
    }
}

void UiSessionManagerOhos::SaveSendCommandFunction(SendCommandFunction&& function)
{
    sendCommandFunction_ = std::move(function);
}

void UiSessionManagerOhos::RegisterPipeLineExeAppAIFunction(
    std::function<uint32_t(const std::string& funcName, const std::string& params)>&& callback)
{
    std::unique_lock<std::mutex> lock(mutex_);
    pipelineExeAppAIFunctionCallback_ = std::move(callback);
}

void UiSessionManagerOhos::ExeAppAIFunction(const std::string& funcName, const std::string& params)
{
    if (pipelineExeAppAIFunctionCallback_) {
        auto result = pipelineExeAppAIFunctionCallback_(funcName, params);
        SendExeAppAIFunctionResult(result);
    }
}

void UiSessionManagerOhos::SendExeAppAIFunctionResult(uint32_t result)
{
    for (auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->SendExeAppAIFunctionResult(result);
        } else {
            LOGW("report send execute application AI function result failed,process id:%{public}d", pair.first);
        }
    }
}
} // namespace OHOS::Ace
