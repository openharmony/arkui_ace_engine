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
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
#include <iremote_object.h>

#include "ui_report_stub.h"
#endif

#include <map>
#include <mutex>
#include <shared_mutex>

#include "ui_session_json_util.h"
#include "ui_translate_manager.h"

#include "base/utils/macros.h"
namespace OHOS::Ace {
class ACE_FORCE_EXPORT UiSessionManager {
public:
    using InspectorFunction = std::function<void(bool onlyNeedVisible)>;
    using NotifyAllWebFunction = std::function<void(bool isRegister)>;
    using GetPixelMapFunction = std::function<void()>;
    using NotifySendCommandFunction = std::function<void(int32_t id, const std::string& command)>;
    using NotifySendCommandAsyncFunction = std::function<int32_t(int32_t id, const std::string& command)>;
    using SendCommandFunction = std::function<void(int32_t value)>;
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
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    /**
     * @description: save report communication stub side
     * @param reportStub report communication stub side
     */
    virtual void SaveReportStub(sptr<IRemoteObject> reportStub, int32_t processId) {};
#endif
    /**
     * @description: get current page inspector tree value
     */
    virtual void GetInspectorTree() {};
    virtual void AddValueForTree(int32_t id, const std::string& value) {};
    virtual void WebTaskNumsChange(int32_t num) {};
    virtual void ReportInspectorTreeValue(const std::string& value) {};
    virtual void SaveForSendCommandFunction(NotifySendCommandFunction&& function) {};
    virtual void SaveForSendCommandAsyncFunction(NotifySendCommandAsyncFunction&& function) {};
    virtual void SaveInspectorTreeFunction(InspectorFunction&& function) {};
    virtual void SaveRegisterForWebFunction(NotifyAllWebFunction&& function) {};
    virtual void ReportWebUnfocusEvent(int64_t accessibilityId, const std::string& data) {};
    virtual void NotifyAllWebPattern(bool isRegister) {};
    virtual void NotifySendCommandPattern(int32_t id, const std::string& command) {};
    virtual int32_t NotifySendCommandAsyncPattern(int32_t id, const std::string& command) { return 11; };
    virtual void SetClickEventRegistered(bool status) {};
    virtual void SetSearchEventRegistered(bool status) {};
    virtual void OnRouterChange(const std::string& path, const std::string& event) {};
    virtual void SetRouterChangeEventRegistered(bool status) {};
    virtual void SetComponentChangeEventRegistered(bool status) {};
    virtual bool GetClickEventRegistered()
    {
        return false;
    };
    virtual bool GetSearchEventRegistered()
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
    virtual void GetWebTranslateText(std::string extraData, bool isContinued) {};
    virtual void SendWebTextToAI(int32_t nodeId, std::string res) {};
    virtual void SendTranslateResult(int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids) {};
    virtual void SendTranslateResult(int32_t nodeId, std::string result) {};
    virtual void ResetTranslate(int32_t nodeId = -1) {};
    virtual void GetPixelMap() {};
    virtual void SendCommand(const std::string& command) {};
    virtual void SaveSendCommandFunction(SendCommandFunction&& function) {};
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    virtual void SendPixelMap(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> maps) {};
#endif
    virtual void GetVisibleInspectorTree() {};

    virtual bool IsHasReportObject()
    {
        return false;
    };
protected:
    static std::mutex mutex_;
    static std::shared_mutex reportObjectMutex_;
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    std::map<int32_t, sptr<IRemoteObject>> reportObjectMap_;
#endif
    std::map<std::string, int32_t> processMap_;
    std::atomic<int32_t> clickEventRegisterProcesses_ = 0;
    std::atomic<int32_t> searchEventRegisterProcesses_ = 0;
    std::atomic<int32_t> routerChangeEventRegisterProcesses_ = 0;
    std::atomic<int32_t> componentChangeEventRegisterProcesses_ = 0;
    bool webFocusEventRegistered = false;
    InspectorFunction inspectorFunction_ = 0;
    NotifyAllWebFunction notifyWebFunction_ = 0;
    GetPixelMapFunction getPixelMapFunction_ = 0;
    NotifySendCommandFunction notifySendCommandFunction_ = 0;
    NotifySendCommandAsyncFunction notifySendCommandAsyncFunction_ = 0;
    std::shared_ptr<InspectorJsonValue> jsonValue_ = nullptr;
    std::atomic<int32_t> webTaskNums_ = 0;
    std::string baseInfo_;
    std::map<int32_t, std::shared_ptr<UiTranslateManager>> translateManagerMap_;
    std::shared_ptr<UiTranslateManager> translateManager_ = nullptr;
    std::function<int32_t()> getInstanceIdCallback_;
    static std::shared_mutex translateManagerMutex_;
    std::function<std::string()> pipelineContextPageNameCallback_;
    SendCommandFunction sendCommandFunction_ = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_SESSION_MANAGER_H
