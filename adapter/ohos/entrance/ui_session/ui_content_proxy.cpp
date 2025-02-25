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

#include "interfaces/inner_api/ui_session/ui_content_proxy.h"

#include "ipc_skeleton.h"

#include "adapter/ohos/entrance/ui_session/include/ui_service_hilog.h"

namespace OHOS::Ace {

int32_t UIContentServiceProxy::GetInspectorTree(const std::function<void(std::string, int32_t, bool)>& eventCallback)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("GetInspectorTree write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr");
        return FAILED;
    }
    report_->RegisterGetInspectorTreeCallback(eventCallback);
    if (Remote()->SendRequest(UI_CONTENT_SERVICE_GET_TREE, data, reply, option) != ERR_NONE) {
        LOGW("GetInspectorTree send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::Connect(const EventCallback& eventCallback)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("connect write interface token failed");
        return FAILED;
    }
    report_ = new (std::nothrow) UiReportStub();
    processId_ = IPCSkeleton::GetCallingRealPid();
    isConnected = true;
    if (report_ == nullptr) {
        LOGW("connect failed,create reportStub failed");
        return FAILED;
    }
    report_->RegisterGetBaseInfoCallback(eventCallback);
    if (!data.WriteRemoteObject(report_)) {
        LOGW("write reportStub failed");
        return FAILED;
    }
    if (!data.WriteInt32(processId_)) {
        LOGW("write processId failed");
        return FAILED;
    }
    if (Remote()->SendRequest(UI_CONTENT_CONNECT, data, reply, option) != ERR_NONE) {
        LOGW("connect send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::RegisterClickEventCallback(const EventCallback& eventCallback)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("RegisterClickEventCallback write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr");
        return FAILED;
    }
    report_->RegisterClickEventCallback(eventCallback);
    if (Remote()->SendRequest(REGISTER_CLICK_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("RegisterClickEventCallback send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::RegisterSearchEventCallback(const EventCallback& eventCallback)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("RegisterSearchEventCallback write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr");
        return FAILED;
    }
    report_->RegisterSearchEventCallback(eventCallback);
    if (Remote()->SendRequest(REGISTER_SEARCH_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("RegisterSearchEventCallback send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::RegisterRouterChangeEventCallback(const EventCallback& eventCallback)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("RegisterRouterChangeEventCallback write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr");
        return FAILED;
    }
    report_->RegisterRouterChangeEventCallback(eventCallback);
    if (Remote()->SendRequest(REGISTER_ROUTER_CHANGE_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("RegisterRouterChangeEventCallback send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::RegisterComponentChangeEventCallback(const EventCallback& eventCallback)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("RegisterComponentChangeEventCallback write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr");
        return FAILED;
    }
    report_->RegisterComponentChangeEventCallback(eventCallback);
    if (Remote()->SendRequest(REGISTER_COMPONENT_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("RegisterComponentChangeEventCallback send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::RegisterWebUnfocusEventCallback(
    const std::function<void(int64_t accessibilityId, const std::string& data)>& eventCallback)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("RegisterWebUnfocusEventCallback write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr,connect is not execute");
        return FAILED;
    }
    report_->RegisterWebUnfocusEventCallback(eventCallback);
    if (Remote()->SendRequest(REGISTER_WEB_UNFOCUS_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("RegisterWebUnfocusEventCallback send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::UnregisterClickEventCallback()
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("UnregisterClickEventCallback write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr");
        return FAILED;
    }
    report_->UnregisterClickEventCallback();
    if (Remote()->SendRequest(UNREGISTER_CLICK_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("UnregisterClickEventCallback send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::UnregisterSearchEventCallback()
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("UnregisterSearchEventCallback write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr");
        return FAILED;
    }
    report_->UnregisterSearchEventCallback();
    if (Remote()->SendRequest(UNREGISTER_SEARCH_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("UnregisterSearchEventCallback send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::UnregisterRouterChangeEventCallback()
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("UnregisterRouterChangeEventCallback write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr");
        return FAILED;
    }
    report_->UnregisterRouterChangeEventCallback();
    if (Remote()->SendRequest(UNREGISTER_ROUTER_CHANGE_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("UnregisterRouterChangeEventCallback send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::UnregisterComponentChangeEventCallback()
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("UnregisterComponentChangeEventCallback write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr");
        return FAILED;
    }
    report_->UnregisterComponentChangeEventCallback();
    if (Remote()->SendRequest(UNREGISTER_COMPONENT_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("UnregisterComponentChangeEventCallback send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::UnregisterWebUnfocusEventCallback()
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("UnregisterComponentChangeEventCallback write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportStub is nullptr,connect is not execute");
        return FAILED;
    }
    report_->UnregisterComponentChangeEventCallback();
    if (Remote()->SendRequest(UNREGISTER_COMPONENT_EVENT, data, reply, option) != ERR_NONE) {
        LOGW("UnregisterComponentChangeEventCallback send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

bool UIContentServiceProxy::IsConnect()
{
    return isConnected;
}

int32_t UIContentServiceProxy::GetWebViewTranslateText(
    const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback)
{
    MessageParcel value;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!value.WriteInterfaceToken(GetDescriptor())) {
        LOGW("GetWebViewTranslateText write interface token failed");
        return FAILED;
    }

    if (report_ == nullptr) {
        LOGW("GetWebViewTranslateText is nullptr,connect is not execute");
        return FAILED;
    }
    if (!value.WriteString(data)) {
        LOGW("GetWebViewTranslateText write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("GetWebViewTranslateText is nullptr,connect is not execute");
        return FAILED;
    }
    report_->RegisterGetTranslateTextCallback(eventCallback);

    if (Remote()->SendRequest(GET_WEB_TRANSLATE_TEXT, value, reply, option) != ERR_NONE) {
        LOGW("GetWebViewTranslateText send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::ResetTranslateTextAll()
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ResetTranslateTextAll write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("ResetTranslateTextAll is nullptr,connect is not execute");
        return FAILED;
    }
    if (Remote()->SendRequest(RESET_ALL_TEXT, data, reply, option) != ERR_NONE) {
        LOGW("ResetTranslateTextAll send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::ResetTranslateText(int32_t nodeId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ResetTranslateText write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("ResetTranslateText is nullptr,connect is not execute");
        return FAILED;
    }
    if (Remote()->SendRequest(RESET_TEXT_BY_ID, data, reply, option) != ERR_NONE) {
        LOGW("ResetTranslateText send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::GetWebViewCurrentLanguage(const EventCallback& eventCallback)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("GetWebViewCurrentLanguage write interface token failed");
        return FAILED;
    }
    if (!data.WriteInt32(processId_)) {
        LOGW("write processId failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("GetWebViewCurrentLanguage is nullptr,connect is not execute");
        return FAILED;
    }
    report_->RegisterGetWebViewCurrentLanguage(eventCallback);
    if (Remote()->SendRequest(GET_WEB_VIEW_LANGUAGE, data, reply, option) != ERR_NONE) {
        LOGW("GetWebViewCurrentLanguage send request failed");
        return REPLY_ERROR;
    }
    return REPLY_ERROR;
}

int32_t UIContentServiceProxy::GetCurrentPageName(const std::function<void(std::string)>& finishCallback)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("GetCurrentPageName write interface token failed");
        return FAILED;
    }
    if (!data.WriteInt32(processId_)) {
        LOGW("write processId failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("GetCurrentPageName is nullptr,connect is not execute");
        return FAILED;
    }
    report_->RegisterGetCurrentPageName(finishCallback);
    if (Remote()->SendRequest(GET_CURRENT_PAGE_NAME, data, reply, option) != ERR_NONE) {
        LOGW("GetCurrentPageName send request failed");
        return REPLY_ERROR;
    }
    return REPLY_ERROR;
}

int32_t UIContentServiceProxy::StartWebViewTranslate(
    const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback)
{
    MessageParcel value;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!value.WriteInterfaceToken(GetDescriptor())) {
        LOGW("StartWebViewTranslate write interface token failed");
        return FAILED;
    }

    if (report_ == nullptr) {
        LOGW("StartWebViewTranslate is nullptr,connect is not execute");
        return FAILED;
    }
    if (!value.WriteString(data)) {
        LOGW("StartWebViewTranslate write interface token failed");
        return FAILED;
    }
    if (!value.WriteInt32(processId_)) {
        LOGW("write processId failed");
        return FAILED;
    }
    report_->RegisterGetTranslateTextCallback(eventCallback);
    if (Remote()->SendRequest(CONTINUE_GET_WEB_TEXT, value, reply, option) != ERR_NONE) {
        LOGW("StartWebViewTranslate send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::SendTranslateResult(
    int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("SendTranslateResult write interface token failed");
        return FAILED;
    }
    if (!data.WriteInt32(nodeId)) {
        LOGW("SendTranslateResult write interface token failed");
        return FAILED;
    }
    if (!data.WriteStringVector(results)) {
        LOGW("SendTranslateResult WriteStringVector  failed");
        return FAILED;
    }
    if (!data.WriteInt32Vector(ids)) {
        LOGW("SendTranslateResult WriteInt32Vector token failed");
        return FAILED;
    }
    if (Remote()->SendRequest(SEND_TRANSLATE_RESULT, data, reply, option) != ERR_NONE) {
        LOGW("SendTranslateResult send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::EndWebViewTranslate()
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("ResetTranslateTextAll write interface token failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("ResetTranslateTextAll is nullptr,connect is not execute");
        return FAILED;
    }
    if (Remote()->SendRequest(END_WEB_TRANSLATE, data, reply, option) != ERR_NONE) {
        LOGW("ResetTranslateTextAll send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::SendTranslateResult(int32_t nodeId, std::string result)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("SendTranslateResult write interface token failed");
        return FAILED;
    }
    if (!data.WriteInt32(nodeId)) {
        LOGW("SendTranslateResult write interface token failed");
        return FAILED;
    }
    if (!data.WriteString(result)) {
        LOGW("SendTranslateResult WriteStringVector  failed");
        return FAILED;
    }

    if (Remote()->SendRequest(SEND_TRANSLATE_RESULT_STR, data, reply, option) != ERR_NONE) {
        LOGW("SendTranslateResult send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}

int32_t UIContentServiceProxy::GetCurrentImagesShowing(
    const std::function<void(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>)>& finishCallback)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!data.WriteInterfaceToken(GetDescriptor())) {
        LOGW("GetCurrentImagesShowing write interface token failed");
        return FAILED;
    }
    if (!data.WriteInt32(processId_)) {
        LOGW("write processId failed");
        return FAILED;
    }
    if (report_ == nullptr) {
        LOGW("reportServiceStub is nullptr,connect is not execute");
        return FAILED;
    }
    report_->RegisterGetShowingImageCallback(finishCallback);
    if (Remote()->SendRequest(GET_CURRENT_SHOWING_IMAGE, data, reply, option) != ERR_NONE) {
        LOGW("GetCurrentImagesShowing send request failed");
        return REPLY_ERROR;
    }
    return NO_ERROR;
}
} // namespace OHOS::Ace
