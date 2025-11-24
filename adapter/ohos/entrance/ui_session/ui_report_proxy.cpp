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

#include "interfaces/inner_api/ui_session/ui_report_proxy.h"

#include "pixel_map.h"

#include "adapter/ohos/entrance/ui_session/include/ui_session_log.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace {
void UiReportProxy::ReportClickEvent(const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ReportClickEvent write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("ReportClickEvent write data failed");
        return;
    }
    if (Remote()->SendRequest(REPORT_CLICK_EVENT, messageData, reply, option) != ERR_NONE) {
        LOGW("ReportClickEvent send request failed");
    }
}

void UiReportProxy::ReportRouterChangeEvent(const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ReportRouterChangeEvent write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("ReportRouterChangeEvent write data failed");
        return;
    }
    if (Remote()->SendRequest(REPORT_SWITCH_EVENT, messageData, reply, option) != ERR_NONE) {
        LOGW("ReportRouterChangeEvent send request failed");
    }
}

void UiReportProxy::ReportComponentChangeEvent(const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ReportComponentChangeEvent write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("ReportComponentChangeEvent write data failed");
        return;
    }
    if (Remote()->SendRequest(REPORT_COMPONENT_EVENT, messageData, reply, option) != ERR_NONE) {
        LOGW("ReportComponentChangeEvent send request failed");
    }
}

void UiReportProxy::ReportSearchEvent(const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ReportSearchEvent write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("ReportSearchEvent write data failed");
        return;
    }
    if (Remote()->SendRequest(REPORT_SEARCH_EVENT, messageData, reply, option) != ERR_NONE) {
        LOGW("ReportSearchEvent send request failed");
    }
}

void UiReportProxy::ReportTextChangeEvent(const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ReportTextChangeEvent write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("ReportTextChangeEvent write data failed");
        return;
    }
    if (Remote()->SendRequest(REPORT_TEXT_CHANGE_EVENT, messageData, reply, option) != ERR_NONE) {
        LOGW("ReportTextChangeEvent send request failed");
    }
}

void UiReportProxy::ReportInspectorTreeValue(const std::string& data, int32_t partNum, bool isLastPart)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ReportInspectorTreeValue write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("ReportInspectorTreeValue write data  failed");
        return;
    }
    if (!messageData.WriteInt32(partNum)) {
        LOGW("ReportInspectorTreeValue write data  failed");
        return;
    }
    if (!messageData.WriteBool(isLastPart)) {
        LOGW("ReportInspectorTreeValue write data  failed");
        return;
    }
    if (Remote()->SendRequest(REPORT_INSPECTOR_VALUE, messageData, reply, option) != ERR_NONE) {
        LOGW("ReportInspectorTreeValue send request failed");
    }
}

void UiReportProxy::OnComponentChange(const std::string& key, const std::string& value)
{
    if (UiSessionManager::GetInstance()->GetComponentChangeEventRegistered()) {
        auto result = InspectorJsonUtil::Create(true);
        result->Put(key.c_str(), value.c_str());
        ReportComponentChangeEvent(result->ToString());
    }
}

void UiReportProxy::ReportWebUnfocusEvent(int64_t accessibilityId, const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ReportWebUnfocusEvent write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("ReportWebUnfocusEvent write data  failed");
        return;
    }
    if (!messageData.WriteInt64(accessibilityId)) {
        LOGW("ReportWebUnfocusEvent write data  failed");
        return;
    }
    if (Remote()->SendRequest(REPORT_WEB_UNFOCUS_EVENT, messageData, reply, option) != ERR_NONE) {
        LOGW("ReportWebUnfocusEvent send request failed");
    }
}

void UiReportProxy::ReportScrollEvent(const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ReportScrollEvent write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("ReportScrollEvent write data  failed");
        return;
    }
    if (Remote()->SendRequest(REPORT_SCROLL_EVENT, messageData, reply, option) != ERR_NONE) {
        LOGW("ReportScrollEvent send request failed");
    }
}

void UiReportProxy::ReportLifeCycleEvent(const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ReportLifeCycleEvent write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("ReportLifeCycleEvent write data  failed");
        return;
    }
    if (Remote()->SendRequest(REPORT_LIFE_CYCLE_EVENT, messageData, reply, option) != ERR_NONE) {
        LOGW("ReportLifeCycleEvent send request failed");
    }
}

void UiReportProxy::SendBaseInfo(const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("SendBaseInfo write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("SendBaseInfo write data  failed");
        return;
    }
    if (Remote()->SendRequest(SEND_BASE_INFO, messageData, reply, option) != ERR_NONE) {
        LOGW("SendBaseInfo send request failed");
    }
}

void UiReportProxy::SendCurrentLanguage(const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option;
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("SendCurrentLanguage write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("SendCurrentLanguage write data  failed");
        return;
    }
    if (Remote()->SendRequest(SEND_CURRENT_LANGUAGE, messageData, reply, option) != ERR_NONE) {
        LOGW("SendCurrentLanguage send request failed");
    }
}

void UiReportProxy::SendCurrentPageName(const std::string& data)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("SendCurrentPageName write interface token failed");
        return;
    }
    if (!messageData.WriteString(data)) {
        LOGW("SendCurrentPageName write data  failed");
        return;
    }
    if (Remote()->SendRequest(SEND_CURRENT_PAGE_NAME, messageData, reply, option) != ERR_NONE) {
        LOGW("SendCurrentPageName send request failed");
    }
}

void UiReportProxy::SendWebText(int32_t nodeId, std::string res)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("SendWebText write interface token failed");
        return;
    }
    if (!messageData.WriteString(res)) {
        LOGW("SendWebText write data  failed");
        return;
    }
    if (!messageData.WriteInt32(nodeId)) {
        LOGW("SendWebText write data  failed");
        return;
    }
    if (Remote()->SendRequest(SEND_TEXT, messageData, reply, option) != ERR_NONE) {
        LOGW("SendWebText send request failed");
    }
}

void UiReportProxyRecipient::OnRemoteDied(const wptr<IRemoteObject>& remote)
{
    LOGI("uiproxy death notice");
    if (remote == nullptr) {
        LOGW("weak remote is null");
        return;
    }
    if (handler_) {
        handler_();
    }
}

void UiReportProxy::SendShowingImage(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>> maps)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    LOGI("before send images,collect map size:%{public}zu", maps.size());
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("SendShowingImage write interface token failed");
        return;
    }
    if (!messageData.WriteInt32(maps.size())) {
        LOGW("SendShowingImage write size failed");
        return;
    }
    for (auto& map : maps) {
        if (map.second == nullptr) {
            LOGW("SendShowingImage empty pixelMap");
            continue;
        }
        if (!messageData.WriteInt32(map.first) || !map.second->Marshalling(messageData)) {
            LOGW("SendShowingImage write data failed");
            return;
        }
    }
    if (Remote()->SendRequest(SEND_IMAGES, messageData, reply, option) != ERR_NONE) {
        LOGW("SendShowingImage send request failed");
    }
}

void UiReportProxy::SendExeAppAIFunctionResult(uint32_t result)
{
    MessageParcel messageData;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!messageData.WriteInterfaceToken(GetDescriptor())) {
        LOGW("SendExeAppAIFunctionResult write interface token failed");
        return;
    }
    if (!messageData.WriteUint32(result)) {
        LOGW("SendExeAppAIFunctionResult write result  failed");
        return;
    }
    if (Remote()->SendRequest(SEND_EXE_APP_AI_FUNCTION_RESULT, messageData, reply, option) != ERR_NONE) {
        LOGW("SendExeAppAIFunctionResult send request failed");
    }
}
} // namespace OHOS::Ace
