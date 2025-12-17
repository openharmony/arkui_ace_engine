/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License") override;
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
#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_UI_SESSION_MANAGER_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_UI_SESSION_MANAGER_OHOS_H

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include <map>
#include <shared_mutex>

#include "refbase.h"
#include "iremote_object.h"

#include "ui_report_proxy.h"

#include "adapter/ohos/entrance/ui_session/include/ui_session_log.h"
#include "base/memory/ace_type.h"
namespace OHOS::Ace {
class UiSessionManagerOhos : public UiSessionManager {
public:
    void ReportClickEvent(const std::string& data) override;
    void ReportSearchEvent(const std::string& data) override;
    void ReportTextChangeEvent(const std::string& data) override;
    void ReportRouterChangeEvent(const std::string& data) override;
    void ReportComponentChangeEvent(const std::string& key, const std::string& value) override;
    void ReportComponentChangeEvent(
        int32_t nodeId, const std::string& key, const std::shared_ptr<InspectorJsonValue>& value) override;
    void ReportWebInputEvent(
        int64_t accessibilityId, const std::string& data, const std::string& type = "") override;
    void ReportScrollEvent(const std::string& data) override;
    void ReportLifeCycleEvent(const std::string& data) override;
    void ReportSelectTextEvent(const std::string& data) override;
    void SetClickEventRegistered(bool status) override;
    void SetSearchEventRegistered(bool status) override;
    void SetTextChangeEventRegistered(bool status) override;
    void SetRouterChangeEventRegistered(bool status) override;
    void SetComponentChangeEventRegistered(bool status) override;
    void SetScrollEventRegistered(bool status) override;
    void SetLifeCycleEventRegistered(bool status) override;
    void SetSelectTextEventRegistered(bool status) override;
    bool GetClickEventRegistered() override;
    bool GetSearchEventRegistered() override;
    bool GetTextChangeEventRegistered() override;
    bool GetRouterChangeEventRegistered() override;
    bool GetComponentChangeEventRegistered() override;
    bool GetScrollEventRegistered() override;
    bool GetLifeCycleEventRegistered() override;
    bool GetSelectTextEventRegistered() override;
    void ReportSelectText() override;
    void GetSpecifiedContentOffsets(int32_t id, const std::string& content) override;
    void HighlightSpecifiedContent(int32_t id, const std::string& content, const std::vector<std::string>& nodeIds,
        const std::string& configs) override;
    void SaveGetSpecifiedContentOffsetsFunction(
        std::function<std::vector<std::pair<float, float>>(int32_t id,
            const std::string& content)>&& callback) override;
    void SaveHighlightSpecifiedContentFunction(std::function<void(int32_t id, const std::string& content,
        const std::vector<std::string>& nodeIds, const std::string& configs)>&& callback) override;
    void SaveSelectTextFunction(std::function<void()>&& callback) override;
    void SendSpecifiedContentOffsets(const std::vector<std::pair<float, float>>& offsets) override;
    void GetInspectorTree(ParamConfig config = ParamConfig()) override;
    void SaveInspectorTreeFunction(InspectorFunction&& function) override;
    void AddValueForTree(int32_t id, const std::string& value) override;
    void WebTaskNumsChange(int32_t num) override;
    void ReportInspectorTreeValue(const std::string& data) override;
    void SaveForSendCommandFunction(NotifySendCommandFunction&& function) override;
    void SaveForSendCommandAsyncFunction(NotifySendCommandAsyncFunction&& function) override;
    void NotifyAllWebPattern(bool isRegister) override;
    void NotifySendCommandPattern(int32_t id, const std::string& command) override;
    int32_t NotifySendCommandAsyncPattern(int32_t id, const std::string& command) override;
    void SaveRegisterForWebFunction(NotifyAllWebFunction&& function) override;
    void SaveGetHitTestInfoCallback(GetHitTestInfoFunction&& function) override;
    void GetLatestHitTestNodeInfosForTouch(InteractionParamConfig config) override;
    void ReportHitTestNodeInfos(const std::string& data) override;
    bool GetWebFocusRegistered() override;
    void OnRouterChange(const std::string& path, const std::string& event) override;
    void SaveBaseInfo(const std::string& info) override;
    void SendBaseInfo(int32_t processId) override;
    void SaveGetPixelMapFunction(GetPixelMapFunction&& function) override;
    void SaveTranslateManager(std::shared_ptr<UiTranslateManager> uiTranslateManager,
        int32_t instanceId) override;
    void SaveGetCurrentInstanceIdCallback(std::function<int32_t()>&& callback) override;
    void RemoveSaveGetCurrentInstanceId(int32_t instanceId) override;
    std::shared_ptr<UiTranslateManager> GetCurrentTranslateManager() override;
    void GetWebViewLanguage() override;
    void RegisterPipeLineGetCurrentPageName(std::function<std::string()>&& callback) override;
    void GetCurrentPageName() override;
    void SendCurrentPageName(const std::string& result) override;
    void SaveProcessId(std::string key, int32_t id) override;
    void EraseProcessId(const std::string& key) override;
    void SendCurrentLanguage(std::string result) override;
    void GetWebTranslateText(std::string extraData, bool isContinued) override;
    void SendWebTextToAI(int32_t nodeId, std::string res) override;
    void SendTranslateResult(int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids) override;
    void SendTranslateResult(int32_t nodeId, std::string res) override;
    void ResetTranslate(int32_t nodeId) override;
    void GetPixelMap() override;
    void SendPixelMap(const std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>& maps) override;
    void GetVisibleInspectorTree(ParamConfig config = ParamConfig()) override;
    void SendCommand(const std::string& command) override;
    void SaveSendCommandFunction(SendCommandFunction&& function) override;
    void RegisterPipeLineExeAppAIFunction(
        std::function<uint32_t(const std::string& funcName, const std::string& params)>&& callback) override;
    void ExeAppAIFunction(const std::string& funcName, const std::string& params) override;
    void SendExeAppAIFunctionResult(uint32_t result) override;
    void RegisterContentChangeCallback(const ContentChangeConfig& config) override;
    void UnregisterContentChangeCallback() override;
    void ReportContentChangeEvent(ChangeType type, const std::string& simpleTree) override;
    void SetStartContentChangeDetectCallback(std::function<void(ContentChangeConfig)>&&) override;
    void SetStopContentChangeDetectCallback(std::function<void()>&&) override;
    void GetStateMgmtInfo(
        const std::string& ComponentName, const std::string& propertyName, const std::string& jsonPath) override;
    void SaveGetStateMgmtInfoFunction(GetStateMgmtInfoFunction&& callback) override;
    void ReportGetStateMgmtInfo(std::vector<std::string> results) override;

    void SaveReportStub(sptr<IRemoteObject> reportStub, int32_t processId);

private:
    std::mutex mutex_;
    std::shared_mutex reportObjectMutex_;
    std::map<int32_t, sptr<IRemoteObject>> reportObjectMap_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_UI_SESSION_MANAGER_OHOS_H
