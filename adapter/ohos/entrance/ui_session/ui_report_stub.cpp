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

#include "interfaces/inner_api/ui_session/ui_report_stub.h"

#include "adapter/ohos/entrance/ui_session/include/ui_service_hilog.h"

namespace OHOS::Ace {
int32_t UiReportStub::OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    if (data.ReadInterfaceToken() != GetDescriptor()) {
        LOGW("ui_session InterfaceToken check failed");
        return -1;
    }
    std::string result = data.ReadString();
    switch (code) {
        case REPORT_CLICK_EVENT: {
            ReportClickEvent(result);
            break;
        }
        case REPORT_SWITCH_EVENT: {
            ReportRouterChangeEvent(result);
            break;
        }
        case REPORT_COMPONENT_EVENT: {
            ReportComponentChangeEvent(result);
            break;
        }
        case REPORT_SEARCH_EVENT: {
            ReportSearchEvent(result);
            break;
        }
        case REPORT_INSPECTOR_VALUE: {
            int32_t partNum = data.ReadInt32();
            bool isLastPart = data.ReadBool();
            ReportInspectorTreeValue(result, partNum, isLastPart);
            break;
        }
        case REPORT_WEB_UNFOCUS_EVENT: {
            int64_t accessibilityId = data.ReadInt64();
            ReportWebUnfocusEvent(accessibilityId, result);
            break;
        }
        case SEND_BASE_INFO: {
            SendBaseInfo(result);
            break;
        }
        default: {
            LOGI("ui_session unknown transaction code %{public}d", code);
            return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
        }
    }
    return 0;
}

void UiReportStub::ReportClickEvent(const std::string& data)
{
    if (clickEventCallback_ != nullptr) {
        clickEventCallback_(data);
    }
}

void UiReportStub::ReportRouterChangeEvent(const std::string& data)
{
    if (RouterChangeEventCallback_ != nullptr) {
        RouterChangeEventCallback_(data);
    }
}

void UiReportStub::ReportComponentChangeEvent(const std::string& data)
{
    if (ComponentChangeEventCallback_ != nullptr) {
        ComponentChangeEventCallback_(data);
    }
}

void UiReportStub::ReportSearchEvent(const std::string& data)
{
    if (searchEventCallback_ != nullptr) {
        searchEventCallback_(data);
    }
}

void UiReportStub::ReportInspectorTreeValue(const std::string& data, int32_t partNum, bool isLastPart)
{
    if (inspectorTreeCallback_ != nullptr) {
        inspectorTreeCallback_(data, partNum, isLastPart);
    }
}

void UiReportStub::ReportWebUnfocusEvent(int64_t accessibilityId, const std::string& data)
{
    if (unfocusEvent_ != nullptr) {
        unfocusEvent_(accessibilityId, data);
    }
}

void UiReportStub::SendBaseInfo(const std::string& data)
{
    if (sendBaseInfoCallback_ != nullptr) {
        sendBaseInfoCallback_(data);
    }
}

void UiReportStub::RegisterGetBaseInfoCallback(const EventCallback& eventCallback)
{
    sendBaseInfoCallback_ = std::move(eventCallback);
}

void UiReportStub::RegisterClickEventCallback(const EventCallback& eventCallback)
{
    clickEventCallback_ = std::move(eventCallback);
}

void UiReportStub::RegisterGetInspectorTreeCallback(
    const std::function<void(std::string, int32_t, bool)>& eventCallback)
{
    inspectorTreeCallback_ = std::move(eventCallback);
}

void UiReportStub::RegisterRouterChangeEventCallback(const EventCallback& eventCallback)
{
    RouterChangeEventCallback_ = std::move(eventCallback);
}

void UiReportStub::RegisterSearchEventCallback(const EventCallback& eventCallback)
{
    searchEventCallback_ = std::move(eventCallback);
}

void UiReportStub::RegisterComponentChangeEventCallback(const EventCallback& eventCallback)
{
    ComponentChangeEventCallback_ = std::move(eventCallback);
}

void UiReportStub::RegisterWebUnfocusEventCallback(
    const std::function<void(int64_t accessibilityId, const std::string& data)>& eventCallback)
{
    unfocusEvent_ = std::move(eventCallback);
}

void UiReportStub::UnregisterClickEventCallback()
{
    clickEventCallback_ = nullptr;
}

void UiReportStub::UnregisterSearchEventCallback()
{
    searchEventCallback_ = nullptr;
}

void UiReportStub::UnregisterRouterChangeEventCallback()
{
    RouterChangeEventCallback_ = nullptr;
}

void UiReportStub::UnregisterComponentChangeEventCallback()
{
    ComponentChangeEventCallback_ = nullptr;
}
} // namespace OHOS::Ace
