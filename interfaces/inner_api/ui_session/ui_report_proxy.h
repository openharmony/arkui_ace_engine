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

#ifndef FOUNDATION_ACE_INTERFACE_UI_REPORT_PROXY_H
#define FOUNDATION_ACE_INTERFACE_UI_REPORT_PROXY_H

#include "iremote_proxy.h"
#include "ui_content_errors.h"
#include "ui_content_service_interface.h"

#include "base/utils/macros.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT UiReportProxy : public IRemoteProxy<ReportService> {
public:
    explicit UiReportProxy(const sptr<IRemoteObject>& impl) : IRemoteProxy<ReportService>(impl) {};

    /**
     * @description: notify stub side to execute click callback
     */
    void ReportClickEvent(const std::string& data) override;

    /**
     * @description: notify stub side to execute switch callback
     */
    void ReportRouterChangeEvent(const std::string& data) override;

    /**
     * @description: notify stub side to execute component callback
     */
    void ReportComponentChangeEvent(const std::string& data) override;

    /**
     * @description: notify stub side to execute search callback
     */
    void ReportSearchEvent(const std::string& data) override;

    /**
     * @description: notify stub side to report inspector value
     */
    void ReportInspectorTreeValue(const std::string& data, int32_t partNum, bool isLastPart) override;

    /**
     * @description: notify stub side to report web unfocus value
     */
    void ReportWebUnfocusEvent(int64_t accessibilityId, const std::string& data) override;

    /**
     * @description: notify stub side to report web unfocus value
     */
    void SendBaseInfo(const std::string& data) override;
    void OnComponentChange(const std::string& key, const std::string& value);
    void SendCurrentLanguage(const std::string& data) override;
    void SendCurrentPageName(const std::string& data) override;
    void SendWebText(int32_t nodeId, std::string res) override;
    void SendShowingImage(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> maps) override;
    void ClearAshmem(sptr<Ashmem>& optMem);

private:
    static inline BrokerDelegator<UiReportProxy> delegator_;
};

class ACE_FORCE_EXPORT UiReportProxyRecipient : public IRemoteObject::DeathRecipient {
public:
    using RemoteDiedHandler = std::function<void()>;
    explicit UiReportProxyRecipient(RemoteDiedHandler handler) : handler_(std::move(handler)) {}

    ~UiReportProxyRecipient() override = default;

    void OnRemoteDied(const wptr<IRemoteObject>& remote) override;

private:
    RemoteDiedHandler handler_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_CONTENT_PROXY_H
