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
#include "ui_report_proxy.h"

#include "adapter/ohos/entrance/ui_session/include/ui_service_hilog.h"
#include "base/memory/ace_type.h"
namespace OHOS::Ace {
class UiSessionManagerOhos : public UiSessionManager {
public:
    void ReportClickEvent(const std::string& data) override;
    void ReportSearchEvent(const std::string& data) override;
    void ReportRouterChangeEvent(const std::string& data) override;
    void ReportComponentChangeEvent(const std::string& key, const std::string& value) override;
    void ReportComponentChangeEvent(
    int32_t nodeId, const std::string& key, const std::shared_ptr<InspectorJsonValue>& value) override;
    void ReportWebUnfocusEvent(int64_t accessibilityId, const std::string& data) override;
    void SaveReportStub(sptr<IRemoteObject> reportStub, int32_t processId) override;
    void SetClickEventRegistered(bool status) override;
    void SetSearchEventRegistered(bool status) override;
    void SetRouterChangeEventRegistered(bool status) override;
    void SetComponentChangeEventRegistered(bool status) override;
    bool GetClickEventRegistered() override;
    bool GetSearchEventRegistered() override;
    bool GetRouterChangeEventRegistered() override;
    bool GetComponentChangeEventRegistered() override;
    void GetInspectorTree() override;
    void SaveInspectorTreeFunction(InspectorFunction&& function) override;
    void AddValueForTree(int32_t id, const std::string& value) override;
    void WebTaskNumsChange(int32_t num) override;
    void ReportInspectorTreeValue(const std::string& data) override;
    void NotifyAllWebPattern(bool isRegister) override;
    void SaveRegisterForWebFunction(NotifyAllWebFunction&& function) override;
    bool GetWebFocusRegistered() override;
    void OnRouterChange(const std::string& path, const std::string& event) override;
    void SaveBaseInfo(const std::string& info) override;
    void SendBaseInfo(int32_t processId) override;
    void SaveGetPixelMapFunction(GetPixelMapFunction&& function) override;
    void SaveTranslateManager(std::shared_ptr<UiTranslateManager> uiTranslateManager) override;
    void GetWebViewLanguage() override;
    void SaveProcessId(std::string key, int32_t id) override;
    void SendCurrentLanguage(std::string result) override;
    void GetWebTranslateText(std::string extraData, bool isContinued) override;
    void SendWebTextToAI(int32_t nodeId, std::string res) override;
    void SendTranslateResult(int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids) override;
    void SendTranslateResult(int32_t nodeId, std::string res) override;
    void ResetTranslate(int32_t nodeId) override;
    void GetPixelMap() override;
    void SendPixelMap(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> maps) override;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_UI_SESSION_MANAGER_OHOS_H
