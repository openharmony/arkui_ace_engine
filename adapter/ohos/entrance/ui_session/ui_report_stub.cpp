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
            std::string result = data.ReadString();
            ReportClickEvent(result);
            break;
        }
        case REPORT_SWITCH_EVENT: {
            std::string result = data.ReadString();
            ReportRouterChangeEvent(result);
            break;
        }
        case REPORT_COMPONENT_EVENT: {
            std::string result = data.ReadString();
            ReportComponentChangeEvent(result);
            break;
        }
        case REPORT_SEARCH_EVENT: {
            std::string result = data.ReadString();
            ReportSearchEvent(result);
            break;
        }
        case REPORT_INSPECTOR_VALUE: {
            std::string result = data.ReadString();
            int32_t partNum = data.ReadInt32();
            bool isLastPart = data.ReadBool();
            ReportInspectorTreeValue(result, partNum, isLastPart);
            break;
        }
        case REPORT_WEB_UNFOCUS_EVENT: {
            std::string result = data.ReadString();
            int64_t accessibilityId = data.ReadInt64();
            ReportWebUnfocusEvent(accessibilityId, result);
            break;
        }
        case SEND_BASE_INFO: {
            std::string result = data.ReadString();
            SendBaseInfo(result);
            break;
        }
        case SEND_CURRENT_LANGUAGE: {
            std::string result = data.ReadString();

            SendCurrentLanguage(result);
            break;
        }
        case SEND_TEXT: {
            std::string res = data.ReadString();
            int32_t nodeId = data.ReadInt32();
            SendWebText(nodeId, res);
            break;
        }
        case SEND_IMAGES: {
            std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> result;
            int32_t size = data.ReadInt32();
            for (int i = 0; i < size; i++) {
                int32_t nodeId = data.ReadInt32();
                sptr<Ashmem> ashMem = data.ReadAshmem();
                if (ashMem == nullptr) {
                    LOGI("Ashmem is nullptr");
                    return -1;
                }
                if (!ashMem->MapReadOnlyAshmem()) {
                    LOGI("MapReadOnlyAshmem failed");
                    ClearAshmem(ashMem);
                    return -1;
                }
                int32_t ashMemSize = ashMem->GetAshmemSize();
                int32_t offset = 0;
                const uint8_t* ashDataPtr =
                    reinterpret_cast<const uint8_t*>(ashMem->ReadFromAshmem(ashMemSize, offset));
                if (ashDataPtr == nullptr) {
                    LOGI("ashDataPtr is nullptr");
                    ClearAshmem(ashMem);
                    return -1;
                }
                std::vector<uint8_t> mapData(ashDataPtr, ashDataPtr + ashMemSize);
                auto data = std::shared_ptr<Media::PixelMap>(OHOS::Media::PixelMap::DecodeTlv(mapData));
                std::pair<int32_t, std::shared_ptr<Media::PixelMap>> value = { nodeId, data };
                result.push_back(value);
                ClearAshmem(ashMem);
            }
            SendShowingImage(result);
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

void UiReportStub::RegisterGetWebViewCurrentLanguage(const EventCallback& eventCallback)
{
    getWebViewCurrentLanguageCallback_ = std::move(eventCallback);
}

void UiReportStub::RegisterGetTranslateTextCallback(const std::function<void(int32_t, std::string)>& eventCallback)
{
    getTranslateTextCallback_ = std::move(eventCallback);
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

void UiReportStub::SendCurrentLanguage(const std::string& data)
{
    if (getWebViewCurrentLanguageCallback_) {
        getWebViewCurrentLanguageCallback_(data);
    }
}

void UiReportStub::SendWebText(int32_t nodeId, std::string res)
{
    if (getTranslateTextCallback_) {
        getTranslateTextCallback_(nodeId, res);
    }
}

void UiReportStub::RegisterGetShowingImageCallback(
    const std::function<void(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>)>& eventCallback)
{
    getShowingImageCallback_ = std::move(eventCallback);
}

void UiReportStub::SendShowingImage(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> maps)
{
    if (getShowingImageCallback_) {
        getShowingImageCallback_(maps);
    }
}

void UiReportStub::ClearAshmem(sptr<Ashmem>& optMem)
{
    if (optMem != nullptr) {
        optMem->UnmapAshmem();
        optMem->CloseAshmem();
    }
}
} // namespace OHOS::Ace
