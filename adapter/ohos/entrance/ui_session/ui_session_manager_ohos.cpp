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
    for (const auto& pair : reportObjectMap_) {
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
    for (const auto& pair : reportObjectMap_) {
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
    for (const auto& pair : reportObjectMap_) {
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
    for (const auto& pair : reportObjectMap_) {
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
    for (const auto& pair : reportObjectMap_) {
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
    for (const auto& pair : reportObjectMap_) {
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
    for (const auto& pair : reportObjectMap_) {
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
    for (const auto& pair : reportObjectMap_) {
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
    for (const auto& pair : reportObjectMap_) {
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
    for (const auto& pair : reportObjectMap_) {
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
        auto translateIter = processMap_.find("translate");
        if (translateIter != processMap_.end() && translateIter->second.size() == 1 &&
            *translateIter->second.begin() == processId) {
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
    {
        std::lock_guard<std::mutex> lock(jsonValueMutex_);
        jsonValue_ = InspectorJsonUtil::Create(true);
    }

    InspectorFunction inspectorFunction;
    {
        std::lock_guard<std::mutex> lock(inspectorFunctionMutex_);
        inspectorFunction = inspectorFunction_;
    }
    if (inspectorFunction) {
        inspectorFunction(false, config);
    }
}

void UiSessionManagerOhos::GetVisibleInspectorTree(ParamConfig config)
{
    InspectorFunction inspectorFunction;
    {
        std::lock_guard<std::mutex> lock(inspectorFunctionMutex_);
        inspectorFunction = inspectorFunction_;
    }
    if (inspectorFunction) {
        inspectorFunction(true, config);
    }
}

void UiSessionManagerOhos::SaveInspectorTreeFunction(InspectorFunction&& function)
{
    std::lock_guard<std::mutex> lock(inspectorFunctionMutex_);
    inspectorFunction_ = std::move(function);
}

void UiSessionManagerOhos::AddValueForTree(int32_t id, const std::string& value)
{
    std::lock_guard<std::mutex> lock(jsonValueMutex_);
    if (!jsonValue_) {
        LOGW("AddValueForTree jsonValue is nullptr");
        return;
    }
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
        std::string data;
        {
            std::lock_guard<std::mutex> lock(jsonValueMutex_);
            if (!jsonValue_) {
                LOGW("WebTaskNumsChange jsonValue is nullptr");
                return;
            }
            data = jsonValue_->ToString();
        }
        ReportInspectorTreeValue(data);
    }
}

void UiSessionManagerOhos::ReportInspectorTreeValue(const std::string& data)
{
    UI_SESSION_SCOPED_TRACE("[UiSessionManagerOhos] ReportInspectorTreeValue");
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("getInspectorTree");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("ReportInspectorTreeValue no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            int32_t index = 1;
            reportService->ReportInspectorTreeValue(data, index, true);
        } else {
            LOGW("report inspector tree value failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}

void UiSessionManagerOhos::NotifyAllWebPattern(bool isRegister)
{
    {
        std::lock_guard<std::mutex> lock(webFocusEventRegisteredMutex_);
        webFocusEventRegistered = isRegister;
    }

    NotifyAllWebFunction notifyWebFunction;
    {
        std::lock_guard<std::mutex> lock(notifyWebFunctionMutex_);
        notifyWebFunction = notifyWebFunction_;
    }
    if (notifyWebFunction) {
        notifyWebFunction(isRegister);
    }
}

void UiSessionManagerOhos::NotifySendCommandPattern(int32_t id, const std::string& command)
{
    NotifySendCommandFunction notifySendCommandFunction;
    {
        std::lock_guard<std::mutex> lock(notifySendCommandFunctionMutex_);
        notifySendCommandFunction = notifySendCommandFunction_;
    }
    if (notifySendCommandFunction) {
        notifySendCommandFunction(id, command);
    }
}

int32_t UiSessionManagerOhos::NotifySendCommandAsyncPattern(int32_t id, const std::string& command)
{
    NotifySendCommandAsyncFunction notifySendCommandAsyncFunction;
    {
        std::lock_guard<std::mutex> lock(notifySendCommandAsyncFunctionMutex_);
        notifySendCommandAsyncFunction = notifySendCommandAsyncFunction_;
    }
    if (!notifySendCommandAsyncFunction) {
        return 11; // 11 is the error code for no callback
    }
    return notifySendCommandAsyncFunction(id, command);
}

void UiSessionManagerOhos::SaveRegisterForWebFunction(NotifyAllWebFunction&& function)
{
    std::lock_guard<std::mutex> lock(notifyWebFunctionMutex_);
    notifyWebFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveGetHitTestInfoCallback(GetHitTestInfoFunction&& function)
{
    std::lock_guard<std::mutex> lock(getHitTestInfoFunctionMutex_);
    getHitTestInfoFunction_ = std::move(function);
}

void UiSessionManagerOhos::GetLatestHitTestNodeInfosForTouch(InteractionParamConfig config)
{
    GetHitTestInfoFunction getHitTestInfoFunction;
    {
        std::lock_guard<std::mutex> lock(getHitTestInfoFunctionMutex_);
        getHitTestInfoFunction = getHitTestInfoFunction_;
    }
    if (getHitTestInfoFunction) {
        getHitTestInfoFunction(config);
    }
}

void UiSessionManagerOhos::ReportHitTestNodeInfos(const std::string& data)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
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
    std::lock_guard<std::mutex> lock(notifySendCommandFunctionMutex_);
    notifySendCommandFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveForSendCommandAsyncFunction(NotifySendCommandAsyncFunction&& function)
{
    std::lock_guard<std::mutex> lock(notifySendCommandAsyncFunctionMutex_);
    notifySendCommandAsyncFunction_ = std::move(function);
}

bool UiSessionManagerOhos::GetWebFocusRegistered()
{
    std::lock_guard<std::mutex> lock(webFocusEventRegisteredMutex_);
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
    std::lock_guard<std::mutex> lock(baseInfoMutex_);
    baseInfo_ = info;
}

void UiSessionManagerOhos::SendBaseInfo(int32_t processId)
{
    sptr<IRemoteObject> reportObject;
    {
        std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
        auto reportIter = reportObjectMap_.find(processId);
        if (reportIter != reportObjectMap_.end()) {
            reportObject = reportIter->second;
        }
    }

    auto reportService = iface_cast<ReportService>(reportObject);
    if (reportService != nullptr) {
        std::string baseInfo;
        {
            std::lock_guard<std::mutex> lock(baseInfoMutex_);
            baseInfo = baseInfo_;
        }
        reportService->SendBaseInfo(baseInfo);
    }
}

void UiSessionManagerOhos::SaveGetPixelMapFunction(GetPixelMapFunction&& function)
{
    std::lock_guard<std::mutex> lock(getPixelMapFunctionMutex_);
    getPixelMapFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveGetImagesByIdFunction(GetImagesByIdFunction&& function)
{
    std::lock_guard<std::mutex> lock(getImagesByIdFunctionMutex_);
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
    std::function<int32_t()> getInstanceIdCallback;
    {
        std::shared_lock<std::shared_mutex> lock(getInstanceIdCallbackMutex_);
        getInstanceIdCallback = getInstanceIdCallback_;
    }
    if (!getInstanceIdCallback) {
        return nullptr;
    }

    int32_t instanceId = getInstanceIdCallback();
    std::shared_lock<std::shared_mutex> lock(translateManagerMutex_);
    auto iter = translateManagerMap_.find(instanceId);
    if (iter == translateManagerMap_.end()) {
        return nullptr;
    }

    auto translateManager = iter->second;
    if (translateManager) {
        return translateManager;
    }
    return nullptr;
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
    std::lock_guard<std::mutex> lock(pipelineContextPageNameCallbackMutex_);
    pipelineContextPageNameCallback_ = std::move(callback);
}

void UiSessionManagerOhos::GetCurrentPageName()
{
    std::function<std::string()> pipelineContextPageNameCallback;
    {
        std::lock_guard<std::mutex> lock(pipelineContextPageNameCallbackMutex_);
        pipelineContextPageNameCallback = pipelineContextPageNameCallback_;
    }
    if (pipelineContextPageNameCallback) {
        auto result = pipelineContextPageNameCallback();
        SendCurrentPageName(result);
    }
}

void UiSessionManagerOhos::SendCurrentPageName(const std::string& result)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
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
    std::lock_guard<std::mutex> lock(getSpecifiedContentOffsetsCallbackMutex_);
    getSpecifiedContentOffsetsCallback_ = std::move(callback);
}

void UiSessionManagerOhos::SaveHighlightSpecifiedContentFunction(std::function<void(int32_t id,
    const std::string& content, const std::vector<std::string>& nodeIds, const std::string& configs)>&& callback)
{
    std::lock_guard<std::mutex> lock(highlightSpecifiedContentCallbackMutex_);
    highlightSpecifiedContentCallback_ = std::move(callback);
}

void UiSessionManagerOhos::SaveSelectTextFunction(std::function<void()>&& callback)
{
    std::lock_guard<std::mutex> lock(selectTextCallbackMutex_);
    selectTextCallback_ = std::move(callback);
}

void UiSessionManagerOhos::GetSpecifiedContentOffsets(int32_t id, const std::string& content)
{
    std::function<std::vector<std::pair<float, float>>(int32_t id, const std::string& content)>
        getSpecifiedContentOffsetsCallback;
    {
        std::lock_guard<std::mutex> lock(getSpecifiedContentOffsetsCallbackMutex_);
        getSpecifiedContentOffsetsCallback = getSpecifiedContentOffsetsCallback_;
    }
    if (getSpecifiedContentOffsetsCallback) {
        getSpecifiedContentOffsetsCallback(id, content);
    }
}

void UiSessionManagerOhos::HighlightSpecifiedContent(
    int32_t id, const std::string& content, const std::vector<std::string>& nodeIds, const std::string& configs)
{
    std::function<void(int32_t id, const std::string& content, const std::vector<std::string>& nodeIds,
        const std::string& configs)> highlightSpecifiedContentCallback;
    {
        std::lock_guard<std::mutex> lock(highlightSpecifiedContentCallbackMutex_);
        highlightSpecifiedContentCallback = highlightSpecifiedContentCallback_;
    }
    if (highlightSpecifiedContentCallback) {
        highlightSpecifiedContentCallback(id, content, nodeIds, configs);
    }
}

void UiSessionManagerOhos::ReportSelectText()
{
    std::function<void()> selectTextCallback;
    {
        std::lock_guard<std::mutex> lock(selectTextCallbackMutex_);
        selectTextCallback = selectTextCallback_;
    }
    if (selectTextCallback) {
        selectTextCallback();
    }
}

void UiSessionManagerOhos::SendSpecifiedContentOffsets(const std::vector<std::pair<float, float>>& offsets)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
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
    auto processIter = processMap_.find(key);
    if (processIter == processMap_.end()) {
        return;
    }
    processIter->second.erase(targetPid);
}

void UiSessionManagerOhos::SendCurrentLanguage(std::string result)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::shared_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("translate");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendCurrentLanguage no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendCurrentLanguage(result);
        } else {
            LOGW("Send current language failed, process id:%{public}d", pid);
        }
    }
}

void UiSessionManagerOhos::GetWebTranslateText(std::string extraData, bool isContinued)
{
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
    auto processIter = processMap_.find("translate");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendWebTextToAI no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
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
    GetPixelMapFunction getPixelMapFunction;
    {
        std::lock_guard<std::mutex> lock(getPixelMapFunctionMutex_);
        getPixelMapFunction = getPixelMapFunction_;
    }
    if (getPixelMapFunction) {
        getPixelMapFunction();
    } else {
        LOGW("get pixelMap func is nullptr");
    }
}

void UiSessionManagerOhos::GetMultiImagesById(const std::vector<int32_t>& arkUIIds,
    const std::map<int32_t, std::vector<int32_t>>& arkWebs)
{
    GetImagesByIdFunction getImagesByIdFunction;
    {
        std::lock_guard<std::mutex> lock(getImagesByIdFunctionMutex_);
        getImagesByIdFunction = getImagesByIdFunction_;
    }
    if (getImagesByIdFunction) {
        getImagesByIdFunction(arkUIIds, arkWebs);
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
    auto processIter = processMap_.find("getArkUIImages");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendArkUIImagesById no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendArkUIImagesById(windowId, componentImages, arkUIErrorCode);
        } else {
            LOGW("Send ArkUI Images By Id failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}

void UiSessionManagerOhos::SendArkWebImagesById(int32_t windowId, const std::map<int32_t, std::map<int32_t,
    std::shared_ptr<Media::PixelMap>>>& webImages, MultiImageQueryErrorCode arkWebErrorCode)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("getArkWebImages");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendArkWebImagesById no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendArkWebImagesById(windowId, webImages, arkWebErrorCode);
        } else {
            LOGW("Send ArkWeb Images By Id failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}

void UiSessionManagerOhos::SendPixelMap(const std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>& maps)
{
    auto currentTranslateManager = GetCurrentTranslateManager();
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    if (!currentTranslateManager) {
        LOGW("send pixelMap failed, translateManager is nullptr");
    }
    auto processIter = processMap_.find("pixel");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendPixelMap no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
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
    processIter->second.clear();
}

void UiSessionManagerOhos::SendCommand(const std::string& command)
{
    auto json = InspectorJsonUtil::ParseJsonString(command);
    if (!json || json->IsNull()) {
        LOGW("SendCommand ParseJsonString failed");
        return;
    }

    auto value = json->GetValue("cmd");
    if (sendCommandFunction_ && value && value->IsNumber()) {
        int32_t cmdNumber = value->GetInt();
        sendCommandFunction_(cmdNumber);
    } else if (relaxedCommandFunction_) {
        relaxedCommandFunction_(command);
    } else {
        LOGW("SendCommand failed");
    }
}

void UiSessionManagerOhos::SaveSendCommandFunction(SendCommandFunction&& function)
{
    std::lock_guard<std::mutex> lock(sendCommandFunctionMutex_);
    sendCommandFunction_ = std::move(function);
}

void UiSessionManagerOhos::SaveRelaxedCommandFunction(RelaxedCommandFunction&& function)
{
    relaxedCommandFunction_ = std::move(function);
}

void UiSessionManagerOhos::RegisterPipeLineExeAppAIFunction(
    std::function<uint32_t(const std::string& funcName, const std::string& params)>&& callback)
{
    std::lock_guard<std::mutex> lock(pipelineExeAppAIFunctionCallbackMutex_);
    pipelineExeAppAIFunctionCallback_ = std::move(callback);
}

void UiSessionManagerOhos::ExeAppAIFunction(const std::string& funcName, const std::string& params)
{
    std::function<uint32_t(const std::string& funcName, const std::string& params)> pipelineExeAppAIFunctionCallback;
    {
        std::lock_guard<std::mutex> lock(pipelineExeAppAIFunctionCallbackMutex_);
        pipelineExeAppAIFunctionCallback = pipelineExeAppAIFunctionCallback_;
    }
    if (pipelineExeAppAIFunctionCallback) {
        auto result = pipelineExeAppAIFunctionCallback(funcName, params);
        SendExeAppAIFunctionResult(result);
    }
}

void UiSessionManagerOhos::SendExeAppAIFunctionResult(uint32_t result)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    for (const auto& pair : reportObjectMap_) {
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
    std::function<void(ContentChangeConfig)> startContentChangeDetectCallback;
    {
        std::lock_guard<std::mutex> lock(startContentChangeDetectCallbackMutex_);
        startContentChangeDetectCallback = startContentChangeDetectCallback_;
    }
    if (startContentChangeDetectCallback) {
        startContentChangeDetectCallback(config);
    }
}

void UiSessionManagerOhos::UnregisterContentChangeCallback()
{
    std::function<void()> stopContentChangeDetectCallback;
    {
        std::lock_guard<std::mutex> lock(stopContentChangeDetectCallbackMutex_);
        stopContentChangeDetectCallback = stopContentChangeDetectCallback_;
    }
    if (stopContentChangeDetectCallback) {
        stopContentChangeDetectCallback();
    }
}

void UiSessionManagerOhos::ReportContentChangeEvent(ChangeType type, const std::string& simpleTree)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::shared_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("contentChange");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("ReportContentChangeEvent no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendContentChange(type, simpleTree);
        } else {
            LOGW("Report Content Change Event failed, process id:%{public}d", pid);
        }
    }
}

void UiSessionManagerOhos::SetStartContentChangeDetectCallback(std::function<void(ContentChangeConfig)>&& startCallback)
{
    std::lock_guard<std::mutex> lock(startContentChangeDetectCallbackMutex_);
    if (startContentChangeDetectCallback_) {
        return;
    }
    startContentChangeDetectCallback_ = std::move(startCallback);
}

void UiSessionManagerOhos::SetStopContentChangeDetectCallback(std::function<void()>&& stopCallback)
{
    std::lock_guard<std::mutex> lock(stopContentChangeDetectCallbackMutex_);
    if (stopContentChangeDetectCallback_) {
        return;
    }
    stopContentChangeDetectCallback_ = std::move(stopCallback);
}

void UiSessionManagerOhos::GetStateMgmtInfo(const std::string& componentName, const std::string& propertyName,
    const std::string& jsonPath, bool onlyVisible)
{
    GetStateMgmtInfoFunction getStateMgmtInfoFunction;
    {
        std::lock_guard<std::mutex> lock(getStateMgmtInfoFunctionMutex_);
        getStateMgmtInfoFunction = getStateMgmtInfoFunction_;
    }
    if (getStateMgmtInfoFunction) {
        getStateMgmtInfoFunction(componentName, propertyName, jsonPath, onlyVisible);
    }
}

void UiSessionManagerOhos::SaveGetStateMgmtInfoFunction(GetStateMgmtInfoFunction&& callback)
{
    std::lock_guard<std::mutex> lock(getStateMgmtInfoFunctionMutex_);
    getStateMgmtInfoFunction_ = std::move(callback);
}

void UiSessionManagerOhos::ReportGetStateMgmtInfo(std::vector<std::string> results)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("GetStateMgmtInfo");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("ReportGetStateMgmtInfo no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->ReportGetStateMgmtInfo(results);
        } else {
            LOGW("Report GetStateMgmtInfo failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}

void UiSessionManagerOhos::SaveGetWebInfoByRequestFunction(GetWebInfoByRequestFunction&& callback)
{
    std::lock_guard<std::mutex> lock(getWebInfoByRequestCallbackMutex_);
    getWebInfoByRequestCallback_ = std::move(callback);
}

void UiSessionManagerOhos::GetWebInfoByRequest(int32_t webId, const std::string& request)
{
    GetWebInfoByRequestFunction getWebInfoByRequestCallback;
    {
        std::lock_guard<std::mutex> lock(getWebInfoByRequestCallbackMutex_);
        getWebInfoByRequestCallback = getWebInfoByRequestCallback_;
    }
    if (getWebInfoByRequestCallback) {
        getWebInfoByRequestCallback(webId, request);
    }
}

void UiSessionManagerOhos::SendWebInfoByRequest(uint32_t windowId, int32_t webId, const std::string& request,
        const std::string& result, WebRequestErrorCode errorCode)
{
    std::shared_lock<std::shared_mutex> reportLock(reportObjectMutex_);
    std::unique_lock<std::shared_mutex> processMapLock(processMapMutex_);
    auto processIter = processMap_.find("GetWebInfoByRequest");
    if (processIter == processMap_.end() || processIter->second.empty()) {
        LOGW("SendWebInfoByRequest no report proxy");
        return;
    }
    for (const auto& pid : processIter->second) {
        auto reportIter = reportObjectMap_.find(pid);
        auto reportService =
            (reportIter != reportObjectMap_.end()) ? iface_cast<ReportService>(reportIter->second) : nullptr;
        if (reportService != nullptr) {
            reportService->SendWebInfoRequestResult(windowId, webId, request, result, errorCode);
        } else {
            LOGW("Send WebInfo By Request failed, process id:%{public}d", pid);
        }
    }
    processIter->second.clear();
}


void UiSessionManagerOhos::SaveNotifyComponentPreMakeFunction(NotifyComponentPreMakeFunction&& function)
{
    std::unique_lock<std::mutex> lock(notifyComponentPreMakeFunctionMutex_);
    notifyComponentPreMakeFunction_ = std::move(function);
}

void UiSessionManagerOhos::ExeAppComponentPreMake(int32_t componentType, const std::string& params)
{
    std::unique_lock<std::mutex> lock(notifyComponentPreMakeFunctionMutex_);
    if (notifyComponentPreMakeFunction_) {
        notifyComponentPreMakeFunction_(componentType, params);
    } else {
        LOGW("Execute component premake failed, function is nullptr");
    }
}
} // namespace OHOS::Ace
