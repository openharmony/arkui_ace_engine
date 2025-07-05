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

#ifndef FOUNDATION_ACE_INTERFACE_UI_CONTENT_PROXY_H
#define FOUNDATION_ACE_INTERFACE_UI_CONTENT_PROXY_H

#include "iremote_proxy.h"
#include "ui_content_errors.h"
#include "ui_content_service_interface.h"
#include "ui_report_stub.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT UIContentServiceProxy : public IRemoteProxy<IUiContentService> {
public:
    explicit UIContentServiceProxy(const sptr<IRemoteObject>& impl) : IRemoteProxy<IUiContentService>(impl) {};
    virtual int32_t GetInspectorTree(const std::function<void(std::string, int32_t, bool)>& eventCallback) override;
    virtual int32_t Connect(const EventCallback& eventCallback) override;
    virtual int32_t RegisterClickEventCallback(const EventCallback& eventCallback) override;
    virtual int32_t RegisterRouterChangeEventCallback(const EventCallback& eventCallback) override;
    virtual int32_t RegisterSearchEventCallback(const EventCallback& eventCallback) override;
    virtual int32_t RegisterComponentChangeEventCallback(const EventCallback& eventCallback) override;
    virtual int32_t RegisterWebUnfocusEventCallback(
        const std::function<void(int64_t accessibilityId, const std::string& data)>& eventCallback) override;
    virtual int32_t SendCommand(int32_t id, const std::string& command) override;
    virtual int32_t SendCommandAsync(int32_t id, const std::string& command) override;
    virtual int32_t SendCommand(const std::string command) override;
    virtual int32_t UnregisterClickEventCallback() override;
    virtual int32_t UnregisterSearchEventCallback() override;
    virtual int32_t UnregisterRouterChangeEventCallback() override;
    virtual int32_t UnregisterComponentChangeEventCallback() override;
    virtual int32_t UnregisterWebUnfocusEventCallback() override;
    virtual bool IsConnect() override;
    virtual int32_t GetWebViewTranslateText(
        const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback) override;
    virtual int32_t ResetTranslateTextAll() override;
    virtual int32_t ResetTranslateText(int32_t nodeId) override;
    virtual int32_t GetWebViewCurrentLanguage(const EventCallback& eventCallback) override;
    virtual int32_t GetCurrentPageName(const std::function<void(std::string)>& finishCallback) override;
    virtual int32_t StartWebViewTranslate(
        const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback) override;
    virtual int32_t SendTranslateResult(
        int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids) override;
    virtual int32_t EndWebViewTranslate() override;
    virtual int32_t SendTranslateResult(int32_t nodeId, std::string result) override;
    virtual int32_t GetCurrentImagesShowing(
        const std::function<void(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>)>& finishCallback)
        override;
    virtual int32_t GetVisibleInspectorTree(
        const std::function<void(std::string, int32_t, bool)>& eventCallback) override;
    virtual int32_t ExeAppAIFunction(
        const std::string& funcName, const std::string& params, const std::function<void(uint32_t)>& finishCallback)
        override;

private:
    static inline BrokerDelegator<UIContentServiceProxy> delegator_;
    sptr<UiReportStub> report_ = nullptr;
    int32_t processId_;
    bool isConnected = false;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_CONTENT_PROXY_H
