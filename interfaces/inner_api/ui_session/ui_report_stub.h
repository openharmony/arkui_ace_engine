/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_UI_REPORT_STUB_H
#define FOUNDATION_ACE_INTERFACE_UI_REPORT_STUB_H

#include <iremote_object.h>
#include <iremote_stub.h>

#include "ui_content_service_interface.h"

#include "base/utils/macros.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT UiReportStub : public IRemoteStub<ReportService> {
public:
    virtual int32_t OnRemoteRequest(
        uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option) override;

    /**
     * @description: receive proxy side communication to execute click callback
     */
    void ReportClickEvent(const std::string& data) override;

    /**
     * @description: receive proxy side communication to execute switch callback
     */
    void ReportRouterChangeEvent(const std::string& data) override;

    /**
     * @description: receive proxy side communication to execute component callback
     */
    void ReportComponentChangeEvent(const std::string& data) override;

    /**
     * @description: receive proxy side communication to execute search callback
     */
    void ReportSearchEvent(const std::string& data) override;

    /**
     * @description: receive proxy side communication to execute text change callback
     */
    void ReportTextChangeEvent(const std::string& data) override;

    /*
    * @description: receive proxy side communication to report scroll value
    */
    void ReportScrollEvent(const std::string& data) override;

    /*
    * @description: receive proxy side communication to report life cycle value
    */
    void ReportLifeCycleEvent(const std::string& data) override;

    /**
     * @description: receive proxy side communication to report select text value
     */
    void ReportSelectTextEvent(const std::string& data) override;

    /**
     * @description: receive proxy side communication to report select text offsets
     */
    void SendSpecifiedContentOffsets(const std::vector<std::pair<float, float>>& offsets) override;

    /**
     * @description: register a callback when click event occurs execute
     * @param eventCallback callback to be performed
     */
    void RegisterClickEventCallback(const EventCallback& eventCallback);

    /**
     * @description: register a callback when page switch event occurs execute
     * @param eventCallback callback to be performed
     */
    void RegisterRouterChangeEventCallback(const EventCallback& eventCallback);

    /**
     * @description: register a callback when text change event occurs execute
     * @param eventCallback callback to be performed
     */
    void RegisterTextChangeEventCallback(const EventCallback& eventCallback);

    /**
     * @description: register a callback when search component do search occurs execute
     * @param eventCallback callback to be performed
     */
    void RegisterSearchEventCallback(const EventCallback& eventCallback);

    /**
     * @description: register a callback when specified component change occurs execute
     * @param eventCallback callback to be performed
     */
    void RegisterComponentChangeEventCallback(const EventCallback& eventCallback);

    /**
     * @description: register a callback when get inspector tree
     * @param eventCallback callback to be performed
     */
    void RegisterGetInspectorTreeCallback(const std::function<void(std::string, int32_t, bool)>& eventCallback);

    /**
     * @description: register a callback when get inspector tree
     * @param eventCallback callback to be performed
     */
    void RegisterWebUnfocusEventCallback(
        const std::function<void(int64_t accessibilityId, const std::string& data)>& eventCallback);

    /**
     * @description: register a callback when get base info
     * @param eventCallback callback to be performed
     */
    void RegisterGetBaseInfoCallback(const EventCallback& eventCallback);

    /**
     * @description: register a callback when get scroll event
     * @param eventCallback callback to be performed
     */
    void RegisterScrollEventCallback(const EventCallback& eventCallback);

    /**
     * @description: register a callback when get life cycle event
     * @param eventCallback callback to be performed
     */
    void RegisterLifeCycleEventCallback(const EventCallback& eventCallback);

    /**
     * @description: register a callback when get select text event
     * @param eventCallback callback to be performed
     */
    void RegisterSelectTextEventCallback(const EventCallback& eventCallback);

    /**
     * @description: register a callback when get select text offsets
     * @param eventCallback callback to be performed
     */
    void RegisterGetSpecifiedContentOffsets(
        const std::function<void(std::vector<std::pair<float, float>>)>& eventCallback);

    /**
     * @description: unregister the click callback last register
     */
    void UnregisterClickEventCallback();

    /**
     * @description: unregister the search callback last register
     */
    void UnregisterSearchEventCallback();

    /**
     * @description: unregister the text change callback last register
     */
    void UnregisterTextChangeEventCallback();

    /**
     * @description: unregister the switch callback last register
     */
    void UnregisterRouterChangeEventCallback();

    /**
     * @description: unregister the component callback last register
     */
    void UnregisterComponentChangeEventCallback();

    /**
     * @description: unregister the web unfocus event callback last register
     */
    void UnregisterWebUnfocusEventCallback();

    /**
     * @description: unregister the scroll event callback last register
     */
    void UnregisterScrollEventCallback();

    /**
     * @description: unregister the life cycle event callback last register
     */
    void UnregisterLifeCycleEventCallback();

    /**
     * @description: unregister the select text event callback last register
     */
    void UnregisterSelectTextEventCallback();

    /**
     * @description: report whole inspectorTree for SA
     */
    void ReportInspectorTreeValue(const std::string& data, int32_t partNum, bool isLastPart) override;

    /**
     * @description: notify stub side to report the information of hit test node
     */
    void ReportHitTestNodeInfos(const std::string& data, int32_t partNum, bool isLastPart) override;

    /**
     * @description: register a callback when get the info of hit test node
     * @param eventCallback callback to be performed
     */
    void RegisterGetHitTestNodeInfoCallback(const std::function<void(std::string, int32_t, bool)>& eventCallback);

    /**
     * @description: report web unfocus value for SA
     */
    void ReportWebUnfocusEvent(int64_t accessibilityId, const std::string& data) override;

    /**
     * @description: report whole inspectorTree for SA
     */
    void SendBaseInfo(const std::string& data) override;
    void RegisterGetShowingImageCallback(
        const std::function<void(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>)>& eventCallback);
    void RegisterGetWebViewCurrentLanguage(const EventCallback& eventCallback);
    void RegisterGetCurrentPageName(const EventCallback& eventCallback);
    void RegisterGetTranslateTextCallback(const std::function<void(int32_t, std::string)>& eventCallback);
    void SendCurrentLanguage(const std::string& data) override;
    void SendCurrentPageName(const std::string& result) override;
    void SendWebText(int32_t nodeId, std::string res) override;
    void SendShowingImage(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> maps) override;
    void RegisterExeAppAIFunction(const std::function<void(uint32_t)>& finishCallback);
    void SendExeAppAIFunctionResult(uint32_t result) override;
    void SendContentChange(ChangeType type, const std::string& simpleTree) override;
    void RegisterContentChangeCallback(
        const std::function<void(ChangeType type, const std::string& simpleTree)> callback);
    void UnregisterContentChangeCallback();
    void RegisterGetStateMgmtInfoCallback(const std::function<void(std::vector<std::string>)>& callback);
    void ReportGetStateMgmtInfo(std::vector<std::string> results) override;

private:
    EventCallback clickEventCallback_;
    EventCallback searchEventCallback_;
    EventCallback textChangeEventCallback_;
    EventCallback RouterChangeEventCallback_;
    EventCallback ComponentChangeEventCallback_;
    EventCallback sendBaseInfoCallback_;
    EventCallback getWebViewCurrentLanguageCallback_;
    EventCallback getCurrentPageNameCallback_;
    EventCallback scrollEventCallback_;
    EventCallback lifeCycleEventCallback_;
    EventCallback selectTextEventCallback_;
    std::function<void(std::vector<std::pair<float, float>>)> getSpecifiedContentOffsets_;
    std::function<void(int32_t, std::string)> getTranslateTextCallback_;
    std::function<void(std::string, int32_t, bool)> inspectorTreeCallback_;
    std::function<void(std::string, int32_t, bool)> getHitTestNodeInfoCallback_;
    std::function<void(int64_t accessibilityId, const std::string& data)> unfocusEvent_;
    std::function<void(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>)> getShowingImageCallback_;
    std::function<void(uint32_t)> exeAppAIFunctionCallback_;
    std::function<void(ChangeType type, const std::string& simpleTree)> contentChangeCallback_;
    std::function<void(std::vector<std::string>)> getStateMgmtInfoCallback_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_REPORT_STUB_H
