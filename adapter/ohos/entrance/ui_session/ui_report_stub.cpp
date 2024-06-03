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
    switch (code) {
        case REPORT_CLICK_EVENT: {
            ReportClickEvent();
            break;
        }
        case REPORT_SWITCH_EVENT: {
            ReportRouterChangeEvent();
            break;
        }
        case REPORT_COMPONENT_EVENT: {
            ReportRouterChangeEvent();
            break;
        }
        case REPORT_SEARCH_EVENT: {
            ReportSearchEvent();
            break;
        }
        default: {
            LOGI("ui_session unknown transaction code %{public}d", code);
            return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
        }
    }
    return 0;
}

void UiReportStub::ReportClickEvent()
{
    clickEventCallback_();
}

void UiReportStub::ReportRouterChangeEvent()
{
    RouterChangeEventCallback_();
}

void UiReportStub::ReportComponentChangeEvent()
{
    ComponentChangeEventCallback_();
}

void UiReportStub::ReportSearchEvent()
{
    searchEventCallback_();
}

void UiReportStub::RegisterClickEventCallback(EventCallback eventCallback)
{
    clickEventCallback_ = std::move(eventCallback);
}

void UiReportStub::RegisterRouterChangeEventCallback(EventCallback eventCallback)
{
    RouterChangeEventCallback_ = std::move(eventCallback);
}

void UiReportStub::RegisterSearchEventCallback(EventCallback eventCallback)
{
    searchEventCallback_ = std::move(eventCallback);
}

void UiReportStub::RegisterComponentChangeEventCallback(EventCallback eventCallback)
{
    ComponentChangeEventCallback_ = std::move(eventCallback);
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
