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
    void ReportClickEvent(std::string data) override;

    /**
     * @description: receive proxy side communication to execute switch callback
     */
    void ReportRouterChangeEvent(std::string data) override;

    /**
     * @description: receive proxy side communication to execute component callback
     */
    void ReportComponentChangeEvent(std::string data) override;

    /**
     * @description: receive proxy side communication to execute search callback
     */
    void ReportSearchEvent(std::string data) override;

    /**
     * @description: register a callback when click event occurs execute
     * @param eventCallback callback to be performed
     */
    void RegisterClickEventCallback(EventCallback eventCallback);

    /**
     * @description: register a callback when page switch event occurs execute
     * @param eventCallback callback to be performed
     */
    void RegisterRouterChangeEventCallback(EventCallback eventCallback);

    /**
     * @description: register a callback when search component do search occurs execute
     * @param eventCallback callback to be performed
     */
    void RegisterSearchEventCallback(EventCallback eventCallback);
    /**
     * @description: register a callback when specified component change occurs execute
     * @param eventCallback callback to be performed
     */
    void RegisterComponentChangeEventCallback(EventCallback eventCallback);

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

private:
    EventCallback clickEventCallback_;
    EventCallback searchEventCallback_;
    EventCallback RouterChangeEventCallback_;
    EventCallback ComponentChangeEventCallback_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_REPORT_STUB_H
