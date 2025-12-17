/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_UI_SESSION_MANAGER_H
#define FOUNDATION_ACE_INTERFACE_UI_SESSION_MANAGER_H
#include <atomic>
#include <cstdint>
#include <functional>
#include <map>
#include <mutex>
#include <shared_mutex>

#include "base/utils/macros.h"

#include "param_config.h"
#include "ui_session_json_util.h"
#include "ui_translate_manager.h"

namespace OHOS {
namespace Media {
class PixelMap;
} // namespace Media
} // namespace OHOS
namespace OHOS::Ace {
class ACE_FORCE_EXPORT UiSessionManager {
public:
    using InspectorFunction = std::function<void(bool onlyNeedVisible, ParamConfig config)>;
    using NotifyAllWebFunction = std::function<void(bool isRegister)>;
    using GetPixelMapFunction = std::function<void()>;
    using NotifySendCommandFunction = std::function<void(int32_t id, const std::string& command)>;
    using NotifySendCommandAsyncFunction = std::function<int32_t(int32_t id, const std::string& command)>;
    using SendCommandFunction = std::function<void(int32_t value)>;
    using GetHitTestInfoFunction = std::function<void(InteractionParamConfig config)>;
    using GetStateMgmtInfoFunction = std::function<void(
        const std::string& componentName, const std::string& propertyName, const std::string& jsonPath)>;
    /**
     * @description: Get ui_manager instance,this object process singleton
     * @return The return value is ui_manager singleton
     */
    static UiSessionManager* GetInstance();

    /**
     * @description: execute click callback when component click event occurs
     */
    virtual void ReportClickEvent(const std::string& data) {};

    /**
     * @description: execute search callback when component search event occurs
     */
    virtual void ReportSearchEvent(const std::string& data) {};

    /**
     * @description: execute text change callback when component text change event occurs
     */
    virtual void ReportTextChangeEvent(const std::string& data) {};

    /**
     * @description: execute switch callback when page switch to another page occurs
     */
    virtual void ReportRouterChangeEvent(const std::string& data) {};

    /**
     * @description: execute click callback when page some component change occurs
     */
    virtual void ReportComponentChangeEvent(const std::string& key, const std::string& value) {};

    /**
     * @description: execute click callback when page some component change occurs
     */
    virtual void ReportComponentChangeEvent(
        int32_t nodeId, const std::string& key, const std::shared_ptr<InspectorJsonValue>& value) {};

    /**
     * @description: execute callback when scroll event occurs
     */
    virtual void ReportScrollEvent(const std::string& data) {};

    /**
     * @description: execute callback when life cycle event occurs
     */
    virtual void ReportLifeCycleEvent(const std::string& data) {};

    /**
     * @description: get current page inspector tree value
     */
    virtual void GetInspectorTree(ParamConfig config = ParamConfig()) {};
    virtual void AddValueForTree(int32_t id, const std::string& value) {};
    virtual void WebTaskNumsChange(int32_t num) {};
    virtual void ReportInspectorTreeValue(const std::string& value) {};
    virtual void SaveForSendCommandFunction(NotifySendCommandFunction&& function) {};
    virtual void SaveForSendCommandAsyncFunction(NotifySendCommandAsyncFunction&& function) {};
    virtual void SaveInspectorTreeFunction(InspectorFunction&& function) {};
    virtual void SaveRegisterForWebFunction(NotifyAllWebFunction&& function) {};
    virtual void SaveGetHitTestInfoCallback(GetHitTestInfoFunction&& function) {};
    virtual void GetLatestHitTestNodeInfosForTouch(InteractionParamConfig config) {};
    virtual void ReportHitTestNodeInfos(const std::string& data) {};
    /**
     * @description: Report web editing area focus/blur/textChange event
     * @param type The type of event (focus, blur, or textChange), defaults to empty string
     */
    virtual void ReportWebInputEvent(
        int64_t accessibilityId, const std::string& data, const std::string& type = "") {};
    virtual void NotifyAllWebPattern(bool isRegister) {};
    virtual void NotifySendCommandPattern(int32_t id, const std::string& command) {};
    virtual int32_t NotifySendCommandAsyncPattern(int32_t id, const std::string& command) { return 11; };
    virtual void SetClickEventRegistered(bool status) {};
    virtual void SetSearchEventRegistered(bool status) {};
    virtual void SetTextChangeEventRegistered(bool status) {};
    virtual void OnRouterChange(const std::string& path, const std::string& event) {};
    virtual void SetRouterChangeEventRegistered(bool status) {};
    virtual void SetComponentChangeEventRegistered(bool status) {};
    virtual void SetScrollEventRegistered(bool status) {};
    virtual void SetLifeCycleEventRegistered(bool status) {};
    virtual bool GetClickEventRegistered()
    {
        return false;
    };
    virtual bool GetSearchEventRegistered()
    {
        return false;
    };
    virtual bool GetTextChangeEventRegistered()
    {
        return false;
    };
    virtual bool GetRouterChangeEventRegistered()
    {
        return false;
    };
    virtual bool GetComponentChangeEventRegistered()
    {
        return false;
    };
    virtual bool GetWebFocusRegistered()
    {
        return false;
    };
    virtual bool GetScrollEventRegistered()
    {
        return false;
    };
    virtual bool GetLifeCycleEventRegistered()
    {
        return false;
    };
    virtual void SaveBaseInfo(const std::string& info) {};
    virtual void SendBaseInfo(int32_t processId) {};
    virtual void SaveGetPixelMapFunction(GetPixelMapFunction&& function) {};
    virtual void SaveTranslateManager(std::shared_ptr<UiTranslateManager> uiTranslateManager,
        int32_t instanceId) {};
    virtual void SaveGetCurrentInstanceIdCallback(std::function<int32_t()>&& callback) {};
    virtual void RemoveSaveGetCurrentInstanceId(int32_t instanceId) {};
    virtual std::shared_ptr<UiTranslateManager> GetCurrentTranslateManager() {
        std::shared_ptr<UiTranslateManager> currentTranslateManager = nullptr;
        return currentTranslateManager;
    };
    virtual void GetWebViewLanguage() {};
    virtual void RegisterPipeLineGetCurrentPageName(std::function<std::string()>&& callback) {};
    virtual void GetCurrentPageName() {};
    virtual void SendCurrentPageName(const std::string& result) {};
    virtual void SendCurrentLanguage(std::string result) {};
    virtual void SaveProcessId(std::string key, int32_t id) {};
    virtual void EraseProcessId(const std::string& key) {};
    virtual void GetWebTranslateText(std::string extraData, bool isContinued) {};
    virtual void GetStateMgmtInfo(
        const std::string& componentName, const std::string& propertyName, const std::string& jsonPath) {};
    virtual void SendWebTextToAI(int32_t nodeId, std::string res) {};
    virtual void SendTranslateResult(int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids) {};
    virtual void SendTranslateResult(int32_t nodeId, std::string result) {};
    virtual void ResetTranslate(int32_t nodeId = -1) {};
    virtual void GetPixelMap() {};
    virtual void SendCommand(const std::string& command) {};
    virtual void SaveSendCommandFunction(SendCommandFunction&& function) {};
    virtual void SaveGetStateMgmtInfoFunction(GetStateMgmtInfoFunction&& callback) {};
    virtual void SendPixelMap(const std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>& maps) {};
    virtual void GetVisibleInspectorTree(ParamConfig config = ParamConfig()) {};
    virtual void RegisterPipeLineExeAppAIFunction(
        std::function<uint32_t(const std::string& funcName, const std::string& params)>&& callback) {};
    virtual void ExeAppAIFunction(const std::string& funcName, const std::string& params) {};
    virtual void SendExeAppAIFunctionResult(uint32_t result) {};
    virtual void RegisterContentChangeCallback(const ContentChangeConfig& config) {};
    virtual void UnregisterContentChangeCallback() {};
    virtual void ReportContentChangeEvent(ChangeType type, const std::string& simpleTree) {};
    virtual void SetStartContentChangeDetectCallback(std::function<void(ContentChangeConfig)>&&) {};
    virtual void SetStopContentChangeDetectCallback(std::function<void()>&&) {};
    virtual void ReportGetStateMgmtInfo(std::vector<std::string> results) {};

protected:
    UiSessionManager() = default;
    virtual ~UiSessionManager() = default;

    std::map<std::string, int32_t> processMap_;
    std::atomic<int32_t> clickEventRegisterProcesses_ = 0;
    std::atomic<int32_t> searchEventRegisterProcesses_ = 0;
    std::atomic<int32_t> textChangeEventRegisterProcesses_ = 0;
    std::atomic<int32_t> routerChangeEventRegisterProcesses_ = 0;
    std::atomic<int32_t> componentChangeEventRegisterProcesses_ = 0;
    std::atomic<int32_t> scrollEventRegisterProcesses_ = 0;
    std::atomic<int32_t> lifeCycleEventRegisterProcesses_ = 0;
    bool webFocusEventRegistered = false;
    InspectorFunction inspectorFunction_ = 0;
    NotifyAllWebFunction notifyWebFunction_ = 0;
    GetPixelMapFunction getPixelMapFunction_ = 0;
    GetHitTestInfoFunction getHitTestInfoFunction_ = 0;
    NotifySendCommandFunction notifySendCommandFunction_ = 0;
    NotifySendCommandAsyncFunction notifySendCommandAsyncFunction_ = 0;
    GetStateMgmtInfoFunction getStateMgmtInfoFunction_ = 0;
    std::shared_ptr<InspectorJsonValue> jsonValue_ = nullptr;
    std::atomic<int32_t> webTaskNums_ = 0;
    std::string baseInfo_;
    std::map<int32_t, std::shared_ptr<UiTranslateManager>> translateManagerMap_;
    std::shared_mutex translateManagerMutex_;
    std::function<int32_t()> getInstanceIdCallback_;
    std::shared_mutex getInstanceIdCallbackMutex_;
    std::function<std::string()> pipelineContextPageNameCallback_;
    SendCommandFunction sendCommandFunction_ = 0;
    std::function<uint32_t(const std::string& funcName, const std::string& params)> pipelineExeAppAIFunctionCallback_;
    std::function<void(ContentChangeConfig)> startContentChangeDetectCallback_;
    std::function<void()> stopContentChangeDetectCallback_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_SESSION_MANAGER_H
