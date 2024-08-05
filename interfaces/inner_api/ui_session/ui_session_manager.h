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
#include <cstdint>
#include <iremote_object.h>
#include <map>
#include <mutex>

#include "ui_report_stub.h"
#include "ui_session_json_util.h"

#include "base/utils/macros.h"
namespace OHOS::Ace {
class ACE_FORCE_EXPORT UiSessionManager {
public:
    using InspectorFunction = std::function<void()>;
    using NotifyAllWebFunction = std::function<void(bool isRegister)>;
    /**
     * @description: Get ui_manager instance,this object process singleton
     * @return The return value is ui_manager singleton
     */
    static UiSessionManager& GetInstance();

    /**
     * @description: execute click callback when component click event occurs
     */
    void ReportClickEvent(const std::string& data);

    /**
     * @description: execute search callback when component search event occurs
     */
    void ReportSearchEvent(const std::string& data);

    /**
     * @description: execute switch callback when page switch to another page occurs
     */
    void ReportRouterChangeEvent(const std::string& data);

    /**
     * @description: execute click callback when page some component change occurs
     */
    void ReportComponentChangeEvent(const std::string& key, const std::string& value);

    /**
     * @description: save report communication stub side
     * @param reportStub report communication stub side
     */
    void SaveReportStub(sptr<IRemoteObject> reportStub, int32_t processId);

    /**
     * @description: get current page inspector tree value
     */
    void GetInspectorTree();
    void AddValueForTree(int32_t id, const std::string& value);
    void WebTaskNumsChange(int32_t num);
    void ReportInspectorTreeValue(const std::string& value);
    void SaveInspectorTreeFunction(InspectorFunction&& function);
    void SaveRegisterForWebFunction(NotifyAllWebFunction&& function);
    void ReportWebUnfocusEvent(int64_t accessibilityId, const std::string& data);
    void NotifyAllWebPattern(bool isRegister);
    void SetClickEventRegistered(bool status);
    void SetSearchEventRegistered(bool status);
    void OnRouterChange(const std::string& path, const std::string& event);
    void SetRouterChangeEventRegistered(bool status);
    void SetComponentChangeEventRegistered(bool status);
    bool GetClickEventRegistered();
    bool GetSearchEventRegistered();
    bool GetRouterChangeEventRegistered();
    bool GetComponentChangeEventRegistered();
    bool GetWebFocusRegistered();
    void SaveBaseInfo(const std::string& info);
    void SendBaseInfo(int32_t processId);

private:
    static std::mutex mutex_;
    std::map<int32_t, sptr<IRemoteObject>> reportObjectMap_;
    int32_t clickEventRegisterProcesses_ = 0;
    int32_t searchEventRegisterProcesses_ = 0;
    int32_t routerChangeEventRegisterProcesses_ = 0;
    int32_t componentChangeEventRegisterProcesses_ = 0;
    bool webFocusEventRegistered = false;
    InspectorFunction inspectorFunction_ = 0;
    NotifyAllWebFunction notifyWebFunction_ = 0;
    std::shared_ptr<InspectorJsonValue> jsonValue_ = nullptr;
    int32_t webTaskNums = 0;
    std::string baseInfo_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_SESSION_MANAGER_H
