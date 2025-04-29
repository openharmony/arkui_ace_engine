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
     * @description: unregister the click callback last register
     */
    void UnregisterClickEventCallback();

    /**
     * @description: unregister the search callback last register
     */
    void UnregisterSearchEventCallback();

    /**
     * @description: unregister the switch callback last register
     */
    void UnregisterRouterChangeEventCallback();

    /**
     * @description: unregister the component callback last register
     */
    void UnregisterComponentChangeEventCallback();

    /**
     * @description: report whole inspectorTree for SA
     */
    void ReportInspectorTreeValue(const std::string& data, int32_t partNum, bool isLastPart) override;

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
    void ClearAshmem(sptr<Ashmem>& optMem);

private:
    EventCallback clickEventCallback_;
    EventCallback searchEventCallback_;
    EventCallback RouterChangeEventCallback_;
    EventCallback ComponentChangeEventCallback_;
    EventCallback sendBaseInfoCallback_;
    EventCallback getWebViewCurrentLanguageCallback_;
    EventCallback getCurrentPageNameCallback_;
    std::function<void(int32_t, std::string)> getTranslateTextCallback_;
    std::function<void(std::string, int32_t, bool)> inspectorTreeCallback_;
    std::function<void(int64_t accessibilityId, const std::string& data)> unfocusEvent_;
    std::function<void(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>)> getShowingImageCallback_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_REPORT_STUB_H
