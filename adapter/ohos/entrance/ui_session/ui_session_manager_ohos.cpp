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
#include "adapter/ohos/entrance/ui_session/include/ui_session_trace.h"

namespace OHOS::Ace {
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
            LOGW("report click event failed, process id:%{public}d", pair.first);
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
            LOGW("report search event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportTextChangeEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportTextChangeEvent(data);
        } else {
            LOGW("report text change event failed, process id:%{public}d", pair.first);
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
            LOGW("report switch event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportComponentChangeEvent(
    const std::string& key, const std::string& value, uint32_t eventType)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetComponentChangeEventRegistered() &&
            NeedComponentChangeTypeReporting(eventType)) {
            auto data = InspectorJsonUtil::Create();
            data->Put(key.data(), value.data());
            reportService->ReportComponentChangeEvent(data->ToString());
        } else {
            LOGW("report component change event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportComponentChangeEvent(
    int32_t nodeId, const std::string& key, const std::shared_ptr<InspectorJsonValue>& value, uint32_t eventType)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetComponentChangeEventRegistered() &&
            NeedComponentChangeTypeReporting(eventType)) {
            auto data = InspectorJsonUtil::Create();
            data->Put("nodeId", nodeId);
            data->Put(key.data(), value->ToString().data());
            reportService->ReportComponentChangeEvent(data->ToString());
        } else {
            LOGW("report component event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportWebInputEvent(
    int64_t accessibilityId, const std::string& data, const std::string& type)
{
    auto jsonValue = InspectorJsonUtil::Create(true);
    jsonValue->Put("id", accessibilityId);
    jsonValue->Put("$type", "web");
    jsonValue->Put("text", data.c_str());
    jsonValue->Put("eventType", type.c_str());
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->ReportWebUnfocusEvent(accessibilityId, jsonValue->ToString());
        } else {
            LOGW("report web input event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportScrollEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetScrollEventRegistered()) {
            reportService->ReportScrollEvent(data);
        } else {
            LOGW("report scroll event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportLifeCycleEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetLifeCycleEventRegistered()) {
            reportService->ReportLifeCycleEvent(data);
        } else {
            LOGW("report life cycle event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::ReportSelectTextEvent(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr && GetSelectTextEventRegistered()) {
            reportService->ReportSelectTextEvent(data);
        } else {
            LOGW("report select text event failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::SaveReportStub(sptr<IRemoteObject> reportStub, int32_t processId)
{
    // add death callback
    auto uiReportProxyRecipient = new UiReportProxyRecipient([processId, this]() {
        std::unique_lock<std::shared_mutex> reportLock(reportObjectMutex_);
        std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
        LOGW("agent process dead,processId:%{public}d", processId);
        if (processMap_.count("translate") && processMap_["translate"].size() == 1 &&
            *processMap_["translate"].begin() == processId) {
            ResetTranslate(-1);
        }
        // reportMap remove this processId
        this->reportObjectMap_.erase(processId);
        // processMap remove this processId
        for (auto& [_, processSet] : processMap_) {
            processSet.erase(processId);
        }
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

void UiSessionManagerOhos::SetTextChangeEventRegistered(bool status)
{
    if (status) {
        textChangeEventRegisterProcesses_.fetch_add(1);
    } else {
        textChangeEventRegisterProcesses_.fetch_sub(1);
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

void UiSessionManagerOhos::SetComponentChangeEventMask(uint32_t mask)
{
    componentChangeEventMask_ = mask;
}

void UiSessionManagerOhos::SetScrollEventRegistered(bool status)
{
    if (status) {
        scrollEventRegisterProcesses_.fetch_add(1);
    } else {
        scrollEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetLifeCycleEventRegistered(bool status)
{
    if (status) {
        lifeCycleEventRegisterProcesses_.fetch_add(1);
    } else {
        lifeCycleEventRegisterProcesses_.fetch_sub(1);
    }
}

void UiSessionManagerOhos::SetSelectTextEventRegistered(bool status)
{
    if (status) {
        selectTextEventRegisterProcesses_.fetch_add(1);
    } else {
        selectTextEventRegisterProcesses_.fetch_sub(1);
    }
    LOGD("SetSelectTextEventRegistered selectTextEventRegisterProcesses_: %{public}d",
        selectTextEventRegisterProcesses_.load());
}

bool UiSessionManagerOhos::GetClickEventRegistered()
{
    return clickEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetSearchEventRegistered()
{
    return searchEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetTextChangeEventRegistered()
{
    return textChangeEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetRouterChangeEventRegistered()
{
    return routerChangeEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetComponentChangeEventRegistered()
{
    return componentChangeEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::NeedComponentChangeTypeReporting(uint32_t eventType)
{
    return (componentChangeEventMask_ & eventType) != 0;
}

bool UiSessionManagerOhos::GetScrollEventRegistered()
{
    return scrollEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetLifeCycleEventRegistered()
{
    return lifeCycleEventRegisterProcesses_.load() > 0 ? true : false;
}

bool UiSessionManagerOhos::GetSelectTextEventRegistered()
{
    return selectTextEventRegisterProcesses_.load() > 0 ? true : false;
}

void UiSessionManagerOhos::GetInspectorTree(ParamConfig config)
{
    webTaskNums_.store(0);
    WebTaskNumsChange(1);
    std::unique_lock<std::mutex> lock(mutex_);
    jsonValue_ = InspectorJsonUtil::Create(true);
    if (inspectorFunction_) {
        inspectorFunction_(false, config);
    }
}

void UiSessionManagerOhos::GetVisibleInspectorTree(ParamConfig config)
{
    if (inspectorFunction_) {
        inspectorFunction_(true, config);
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
    UI_SESSION_SCOPED_TRACE("[UiSessionManagerOhos] ReportInspectorTreeValue");
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!processMap_.count("getInspectorTree") || processMap_["getInspectorTree"].empty()) {
        LOGW("ReportInspectorTreeValue no report proxy");
        return;
    }
    for (const auto& pid : processMap_["getInspectorTree"]) {
        auto reportService = iface_cast<ReportService>(reportObjectMap_[pid]);
        if (reportService != nullptr) {
            int32_t index = 1;
            reportService->ReportInspectorTreeValue(data, index, true);
        } else {
            LOGW("report inspector tree value failed, process id:%{public}d", pid);
        }
    }
    processMap_["getInspectorTree"].clear();
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

void UiSessionManagerOhos::SaveGetHitTestInfoCallback(GetHitTestInfoFunction&& function)
{
    std::unique_lock<std::mutex> lock(mutex_);
    getHitTestInfoFunction_ = std::move(function);
}

void UiSessionManagerOhos::GetLatestHitTestNodeInfosForTouch(InteractionParamConfig config)
{
    std::unique_lock<std::mutex> lock(mutex_);
    if (getHitTestInfoFunction_) {
        getHitTestInfoFunction_(config);
    }
}

void UiSessionManagerOhos::ReportHitTestNodeInfos(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService == nullptr) {
            LOGW("report hitTestNodeInfos failed, process id:%{public}d", pair.first);
            continue;
        }

        size_t partSize = data.size() / ONCE_IPC_SEND_DATA_MAX_SIZE;
        for (size_t i = 0; i <= partSize; i++) {
            if (i != partSize) {
                reportService->ReportHitTestNodeInfos(
                    data.substr(i * ONCE_IPC_SEND_DATA_MAX_SIZE, ONCE_IPC_SEND_DATA_MAX_SIZE), i + 1, false);
            } else {
                reportService->ReportHitTestNodeInfos(data.substr(i * ONCE_IPC_SEND_DATA_MAX_SIZE), i + 1, true);
            }
        }
    }
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

void UiSessionManagerOhos::SaveGetImagesByIdFunction(GetImagesByIdFunction&& function)
{
    getImagesByIdFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveTranslateManager(std::shared_ptr<UiTranslateManager> uiTranslateManager,
    int32_t instanceId)
{
    std::unique_lock<std::shared_mutex> reportLock(translateManagerMutex_);
    translateManagerMap_[instanceId] = uiTranslateManager;
}

void UiSessionManagerOhos::SaveGetCurrentInstanceIdCallback(std::function<int32_t()>&& callback)
{
    std::unique_lock<std::shared_mutex> lock(getInstanceIdCallbackMutex_);
    getInstanceIdCallback_ = std::move(callback);
}

void UiSessionManagerOhos::RemoveSaveGetCurrentInstanceId(int32_t instanceId)
{
    std::unique_lock<std::shared_mutex> lock(translateManagerMutex_);
    translateManagerMap_.erase(instanceId);
}

std::shared_ptr<UiTranslateManager> UiSessionManagerOhos::GetCurrentTranslateManager()
{
    std::shared_ptr<UiTranslateManager> currentTranslateManager = nullptr;
    std::shared_lock<std::shared_mutex> lock(getInstanceIdCallbackMutex_);
    if (getInstanceIdCallback_) {
        int32_t instanceId = getInstanceIdCallback_();
        std::shared_lock<std::shared_mutex> lock(translateManagerMutex_);
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
    auto currentTranslateManager = GetCurrentTranslateManager();
    if (currentTranslateManager) {
        currentTranslateManager->PostToUI([currentTranslateManager]() {
            currentTranslateManager->GetWebViewCurrentLanguage();
        });
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
    std::unique_lock<std::mutex> lock(mutex_);
    if (pipelineContextPageNameCallback_) {
        auto result = pipelineContextPageNameCallback_();
        SendCurrentPageName(result);
    }
}

void UiSessionManagerOhos::SendCurrentPageName(const std::string& result)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->SendCurrentPageName(result);
        } else {
            LOGW("report send current page name failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::SaveGetSpecifiedContentOffsetsFunction(
    std::function<std::vector<std::pair<float, float>>(int32_t id, const std::string& content)>&& callback)
{
    std::unique_lock<std::mutex> lock(mutex_);
    getSpecifiedContentOffsetsCallback_ = std::move(callback);
}

void UiSessionManagerOhos::SaveHighlightSpecifiedContentFunction(std::function<void(int32_t id,
    const std::string& content, const std::vector<std::string>& nodeIds, const std::string& configs)>&& callback)
{
    std::unique_lock<std::mutex> lock(mutex_);
    highlightSpecifiedContentCallback_ = std::move(callback);
}

void UiSessionManagerOhos::SaveSelectTextFunction(std::function<void()>&& callback)
{
    std::unique_lock<std::mutex> lock(mutex_);
    selectTextCallback_ = std::move(callback);
}

void UiSessionManagerOhos::GetSpecifiedContentOffsets(int32_t id, const std::string& content)
{
    if (getSpecifiedContentOffsetsCallback_) {
        getSpecifiedContentOffsetsCallback_(id, content);
    }
}

void UiSessionManagerOhos::HighlightSpecifiedContent(
    int32_t id, const std::string& content, const std::vector<std::string>& nodeIds, const std::string& configs)
{
    if (highlightSpecifiedContentCallback_) {
        highlightSpecifiedContentCallback_(id, content, nodeIds, configs);
    }
}

void UiSessionManagerOhos::ReportSelectText()
{
    if (selectTextCallback_) {
        selectTextCallback_();
    }
}

void UiSessionManagerOhos::SendSpecifiedContentOffsets(const std::vector<std::pair<float, float>>& offsets)
{
    for (auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->SendSpecifiedContentOffsets(offsets);
        } else {
            LOGW("report send specified content offsets failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::SaveProcessId(std::string key, int32_t id)
{
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    processMap_[key].emplace(id);
}

void UiSessionManagerOhos::EraseProcessId(const std::string& key, int32_t targetPid)
{
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!processMap_.count(key)) {
        return;
    }
    processMap_[key].erase(targetPid);
}

void UiSessionManagerOhos::SendCurrentLanguage(std::string result)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::shared_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!processMap_.count("translate") || processMap_["translate"].empty()) {
        LOGW("SendCurrentLanguage no report proxy");
        return;
    }
    for (const auto& pid : processMap_["translate"]) {
        auto reportService = iface_cast<ReportService>(reportObjectMap_[pid]);
        if (reportService != nullptr) {
            reportService->SendCurrentLanguage(result);
        } else {
            LOGW("Send current language failed, process id:%{public}d", pid);
        }
    }
}
void UiSessionManagerOhos::GetWebTranslateText(std::string extraData, bool isContinued)
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);

    auto currentTranslateManager = GetCurrentTranslateManager();
    if (currentTranslateManager) {
        currentTranslateManager->PostToUI([currentTranslateManager, extraData, isContinued]() {
            currentTranslateManager->GetTranslateText(extraData, isContinued);
        });
    } else {
        LOGE("translateManager is nullptr ,translate failed");
    }
}

void UiSessionManagerOhos::SendWebTextToAI(int32_t nodeId, std::string res)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::shared_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!processMap_.count("translate") || processMap_["translate"].empty()) {
        LOGW("SendWebTextToAI no report proxy");
        return;
    }
    for (const auto& pid : processMap_["translate"]) {
        auto reportService = iface_cast<ReportService>(reportObjectMap_[pid]);
        if (reportService != nullptr) {
            reportService->SendWebText(nodeId, res);
        } else {
            LOGW("Send web text to ai failed, process id:%{public}d", pid);
        }
    }
}

void UiSessionManagerOhos::SendTranslateResult(
    int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids)
{
    auto currentTranslateManager = GetCurrentTranslateManager();
    if (currentTranslateManager) {
        currentTranslateManager->PostToUI([currentTranslateManager, nodeId, results, ids]() {
            currentTranslateManager->SendTranslateResult(nodeId, results, ids);
        });
    } else {
        LOGE("translateManager is nullptr ,translate failed");
    }
}

void UiSessionManagerOhos::SendTranslateResult(int32_t nodeId, std::string res)
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);

    auto currentTranslateManager = GetCurrentTranslateManager();
    if (currentTranslateManager) {
        currentTranslateManager->PostToUI([currentTranslateManager, nodeId, res]() {
            currentTranslateManager->SendTranslateResult(nodeId, res);
        });
    } else {
        LOGE("translateManager is nullptr ,translate failed");
    }
}

void UiSessionManagerOhos::ResetTranslate(int32_t nodeId)
{
    std::shared_lock<std::shared_mutex> reportLock(translateManagerMutex_);
    auto currentTranslateManager = GetCurrentTranslateManager();
    if (currentTranslateManager) {
        currentTranslateManager->PostToUI([currentTranslateManager, nodeId]() {
            currentTranslateManager->ResetTranslate(nodeId);
        });
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

void UiSessionManagerOhos::GetMultiImagesById(const std::vector<int32_t>& arkUIIds,
    const std::map<int32_t, std::vector<int32_t>>& arkWebs)
{
    if (getImagesByIdFunction_) {
        getImagesByIdFunction_(arkUIIds, arkWebs);
    } else {
        LOGW("get images by id function is nullptr");
    }
}

void UiSessionManagerOhos::SendArkUIImagesById(int32_t windowId,
    const std::unordered_map<int32_t, std::shared_ptr<Media::PixelMap>>& componentImages,
    MultiImageQueryErrorCode arkUIErrorCode)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!processMap_.count("getArkUIImages") || processMap_["getArkUIImages"].empty()) {
        LOGW("SendArkUIImagesById no report proxy");
        return;
    }
    for (const auto& pid : processMap_["getArkUIImages"]) {
        auto reportService = iface_cast<ReportService>(reportObjectMap_[pid]);
        if (reportService != nullptr) {
            reportService->SendArkUIImagesById(windowId, componentImages, arkUIErrorCode);
        } else {
            LOGW("Send ArkUI Images By Id failed, process id:%{public}d", pid);
        }
    }
    processMap_["getArkUIImages"].clear();
}

void UiSessionManagerOhos::SendArkWebImagesById(int32_t windowId, const std::map<int32_t, std::map<int32_t,
    std::shared_ptr<Media::PixelMap>>>& webImages, MultiImageQueryErrorCode arkWebErrorCode)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!processMap_.count("getArkWebImages") || processMap_["getArkWebImages"].empty()) {
        LOGW("SendArkWebImagesById no report proxy");
        return;
    }
    for (const auto& pid : processMap_["getArkWebImages"]) {
        auto reportService = iface_cast<ReportService>(reportObjectMap_[pid]);
        if (reportService != nullptr) {
            reportService->SendArkWebImagesById(windowId, webImages, arkWebErrorCode);
        } else {
            LOGW("Send ArkWeb Images By Id failed, process id:%{public}d", pid);
        }
    }
    processMap_["getArkWebImages"].clear();
}

void UiSessionManagerOhos::SendPixelMap(const std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>& maps)
{
    auto currentTranslateManager = GetCurrentTranslateManager();
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!currentTranslateManager) {
        LOGW("send pixelMap failed, translateManager is nullptr");
    }
    if (!processMap_.count("pixel") || processMap_["pixel"].empty()) {
        LOGW("SendPixelMap no report proxy");
        return;
    }
    for (const auto& pid : processMap_["pixel"]) {
        auto reportService = iface_cast<ReportService>(reportObjectMap_[pid]);
        if (reportService != nullptr) {
            reportService->SendShowingImage(maps);
        } else {
            LOGW("send pixel maps failed, process id:%{public}d", pid);
        }
    }
    if (currentTranslateManager) {
        currentTranslateManager->PostToUI([currentTranslateManager]() {
            currentTranslateManager->ClearMap();
        });
    }
    processMap_["pixel"].clear();
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
    std::unique_lock<std::mutex> lock(mutex_);
    if (pipelineExeAppAIFunctionCallback_) {
        auto result = pipelineExeAppAIFunctionCallback_(funcName, params);
        SendExeAppAIFunctionResult(result);
    }
}

void UiSessionManagerOhos::SendExeAppAIFunctionResult(uint32_t result)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (auto& pair : reportObjectMap_) {
        auto reportService = iface_cast<ReportService>(pair.second);
        if (reportService != nullptr) {
            reportService->SendExeAppAIFunctionResult(result);
        } else {
            LOGW("report send execute application AI function result failed, process id:%{public}d", pair.first);
        }
    }
}

void UiSessionManagerOhos::RegisterContentChangeCallback(const ContentChangeConfig& config)
{
    std::unique_lock<std::mutex> lock(mutex_);
    if (startContentChangeDetectCallback_) {
        startContentChangeDetectCallback_(config);
    }
}

void UiSessionManagerOhos::UnregisterContentChangeCallback()
{
    std::unique_lock<std::mutex> lock(mutex_);
    if (stopContentChangeDetectCallback_) {
        stopContentChangeDetectCallback_();
    }
}

void UiSessionManagerOhos::ReportContentChangeEvent(ChangeType type, const std::string& simpleTree)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::shared_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!processMap_.count("contentChange") || processMap_["contentChange"].empty()) {
        LOGW("ReportContentChangeEvent no report proxy");
        return;
    }
    for (const auto& pid : processMap_["contentChange"]) {
        auto reportService = iface_cast<ReportService>(reportObjectMap_[pid]);
        if (reportService != nullptr) {
            reportService->SendContentChange(type, simpleTree);
        } else {
            LOGW("Report Content Change Event failed, process id:%{public}d", pid);
        }
    }
}

void UiSessionManagerOhos::SetStartContentChangeDetectCallback(std::function<void(ContentChangeConfig)>&& startCallback)
{
    std::unique_lock<std::mutex> lock(mutex_);
    if (startContentChangeDetectCallback_) {
        return;
    }
    startContentChangeDetectCallback_ = startCallback;
}

void UiSessionManagerOhos::SetStopContentChangeDetectCallback(std::function<void()>&& stopCallback)
{
    std::unique_lock<std::mutex> lock(mutex_);
    if (stopContentChangeDetectCallback_) {
        return;
    }
    stopContentChangeDetectCallback_ = stopCallback;
}

void UiSessionManagerOhos::GetStateMgmtInfo(
    const std::string& componentName, const std::string& propertyName, const std::string& jsonPath)
{
    std::unique_lock<std::mutex> lock(mutex_);
    if (getStateMgmtInfoFunction_) {
        getStateMgmtInfoFunction_(componentName, propertyName, jsonPath);
    }
}

void UiSessionManagerOhos::SaveGetStateMgmtInfoFunction(GetStateMgmtInfoFunction&& callback)
{
    std::unique_lock<std::mutex> lock(mutex_);
    getStateMgmtInfoFunction_ = std::move(callback);
}

void UiSessionManagerOhos::ReportGetStateMgmtInfo(std::vector<std::string> results)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!processMap_.count("GetStateMgmtInfo") || processMap_["GetStateMgmtInfo"].empty()) {
        LOGW("ReportGetStateMgmtInfo no report proxy");
        return;
    }
    for (const auto& pid : processMap_["GetStateMgmtInfo"]) {
        auto reportService = iface_cast<ReportService>(reportObjectMap_[pid]);
        if (reportService != nullptr) {
            reportService->ReportGetStateMgmtInfo(results);
        } else {
            LOGW("Report GetStateMgmtInfo failed, process id:%{public}d", pid);
        }
    }
    processMap_["GetStateMgmtInfo"].clear();
}

void UiSessionManagerOhos::SaveGetWebInfoByRequestFunction(GetWebInfoByRequestFunction&& callback)
{
    std::unique_lock<std::mutex> lock(mutex_);
    getWebInfoByRequestCallback_ = std::move(callback);
}

void UiSessionManagerOhos::GetWebInfoByRequest(int32_t webId, const std::string& request)
{
    std::unique_lock<std::mutex> lock(mutex_);
    if (getWebInfoByRequestCallback_) {
        getWebInfoByRequestCallback_(webId, request);
    }
}

void UiSessionManagerOhos::SendWebInfoByRequest(uint32_t windowId, int32_t webId, const std::string& request,
        const std::string& result, WebRequestErrorCode errorCode)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!processMap_.count("GetWebInfoByRequest") || processMap_["GetWebInfoByRequest"].empty()) {
        LOGW("SendWebInfoByRequest no report proxy");
        return;
    }
    for (const auto& pid : processMap_["GetWebInfoByRequest"]) {
        auto reportService = iface_cast<ReportService>(reportObjectMap_[pid]);
        if (reportService != nullptr) {
            reportService->SendWebInfoRequestResult(windowId, webId, request, result, errorCode);
        } else {
            LOGW("Send WebInfo By Request failed, process id:%{public}d", pid);
        }
    }
    processMap_["GetWebInfoByRequest"].clear();
}
} // namespace OHOS::Ace
