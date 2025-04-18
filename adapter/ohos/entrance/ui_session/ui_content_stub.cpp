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

#include "interfaces/inner_api/ui_session/ui_content_stub.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "ui_content_errors.h"

#include "adapter/ohos/entrance/ui_session/include/ui_service_hilog.h"

namespace OHOS::Ace {
int32_t UiContentStub::OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    if (data.ReadInterfaceToken() != GetDescriptor()) {
        LOGW("ui_session InterfaceToken check failed");
        return -1;
    }
    switch (code) {
        case UI_CONTENT_SERVICE_GET_TREE: {
            GetInspectorTreeInner(data, reply, option);
            break;
        }
        case UI_CONTENT_CONNECT: {
            ConnectInner(data, reply, option);
            break;
        }
        case REGISTER_CLICK_EVENT: {
            RegisterClickEventCallbackInner(data, reply, option);
            break;
        }
        case REGISTER_SEARCH_EVENT: {
            RegisterSearchEventCallbackInner(data, reply, option);
            break;
        }
        case REGISTER_ROUTER_CHANGE_EVENT: {
            RegisterRouterChangeEventCallbackInner(data, reply, option);
            break;
        }
        case REGISTER_COMPONENT_EVENT: {
            RegisterComponentChangeEventCallbackInner(data, reply, option);
            break;
        }
        case SENDCOMMAND_ASYNC_EVENT: {
            SendCommandInnerAsync(data, reply, option);
            break;
        }
        case SENDCOMMAND_EVENT: {
            SendCommandInner(data, reply, option);
            break;
        }
        case UNREGISTER_CLICK_EVENT: {
            UnregisterClickEventCallbackInner(data, reply, option);
            break;
        }
        case UNREGISTER_SEARCH_EVENT: {
            UnregisterSearchEventCallbackInner(data, reply, option);
            break;
        }
        case UNREGISTER_ROUTER_CHANGE_EVENT: {
            UnregisterRouterChangeEventCallbackInner(data, reply, option);
            break;
        }
        case UNREGISTER_COMPONENT_EVENT: {
            UnregisterComponentChangeEventCallbackInner(data, reply, option);
            break;
        }
        case UNREGISTER_WEB_UNFOCUS_EVENT: {
            UnregisterWebUnfocusEventCallbackInner(data, reply, option);
            break;
        }
        case RESET_ALL_TEXT: {
            ResetTranslateTextAllInner(data, reply, option);
            break;
        }
        case RESET_TEXT_BY_ID: {
            ResetTranslateTextInner(data, reply, option);
            break;
        }
        case GET_WEB_VIEW_LANGUAGE: {
            GetWebViewCurrentLanguageInner(data, reply, option);
            break;
        }
        case GET_WEB_TRANSLATE_TEXT: {
            GetWebViewTranslateTextInner(data, reply, option);
            break;
        }
        case CONTINUE_GET_WEB_TEXT: {
            StartWebViewTranslateInner(data, reply, option);
            break;
        }
        case SEND_TRANSLATE_RESULT: {
            SendTranslateResultInner(data, reply, option);
            break;
        }
        case END_WEB_TRANSLATE: {
            EndWebViewTranslateInner(data, reply, option);
            break;
        }
        case SEND_TRANSLATE_RESULT_STR: {
            SendTranslateResultStrInner(data, reply, option);
            break;
        }
        case GET_CURRENT_PAGE_NAME: {
            GetCurrentPageNameInner(data, reply, option);
            break;
        }
        case GET_CURRENT_SHOWING_IMAGE: {
            GetCurrentImagesShowingInner(data, reply, option);
            break;
        }
        case GET_VISIBLE_TREE: {
            GetVisibleInspectorTreeInner(data, reply, option);
            break;
        }
        case SEND_COMMAND: {
            SendCommandKeyCodeInner(data, reply, option);
            break;
        }
        default: {
            LOGI("ui_session unknown transaction code %{public}d", code);
            return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
        }
    }
    return 0;
}

int32_t UiContentStub::GetInspectorTreeInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    GetInspectorTree(nullptr);
    return NO_ERROR;
}

int32_t UiContentStub::ConnectInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    sptr<IRemoteObject> report = data.ReadRemoteObject();
    if (report == nullptr) {
        LOGW("read reportStub object is nullptr,connect failed");
        return FAILED;
    }
    int32_t processId = data.ReadInt32();
    UiSessionManager::GetInstance()->SaveReportStub(report, processId);
    UiSessionManager::GetInstance()->SendBaseInfo(processId);
    return NO_ERROR;
}

int32_t UiContentStub::RegisterClickEventCallbackInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(RegisterClickEventCallback(nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::RegisterRouterChangeEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(RegisterRouterChangeEventCallback(nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::RegisterSearchEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(RegisterSearchEventCallback(nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::RegisterComponentChangeEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(RegisterComponentChangeEventCallback(nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::RegisterWebUnfocusEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(RegisterWebUnfocusEventCallback(nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::SendCommandInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t id = data.ReadInt32();
    std::string command = data.ReadString();
    reply.WriteInt32(SendCommand(id, command));
    return NO_ERROR;
}

int32_t UiContentStub::SendCommandInnerAsync(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t id = data.ReadInt32();
    return SendCommandAsync(id, data.ReadString());
}

int32_t UiContentStub::SendCommandKeyCodeInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    std::string command = data.ReadString();
    reply.WriteInt32(SendCommand(command));
    return NO_ERROR;
}

int32_t UiContentStub::UnregisterClickEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(UnregisterClickEventCallback());
    return NO_ERROR;
}

int32_t UiContentStub::UnregisterSearchEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(UnregisterSearchEventCallback());
    return NO_ERROR;
}

int32_t UiContentStub::UnregisterRouterChangeEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(UnregisterRouterChangeEventCallback());
    return NO_ERROR;
}

int32_t UiContentStub::UnregisterComponentChangeEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(UnregisterComponentChangeEventCallback());
    return NO_ERROR;
}

int32_t UiContentStub::UnregisterWebUnfocusEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(UnregisterWebUnfocusEventCallback());
    return NO_ERROR;
}

int32_t UiContentStub::ResetTranslateTextAllInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(ResetTranslateTextAll());
    return NO_ERROR;
}

int32_t UiContentStub::ResetTranslateTextInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t nodeId = data.ReadInt32();
    reply.WriteInt32(ResetTranslateText(nodeId));
    return NO_ERROR;
}

int32_t UiContentStub::GetWebViewCurrentLanguageInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t processId = data.ReadInt32();
    UiSessionManager::GetInstance()->SaveProcessId("translate", processId);
    reply.WriteInt32(GetWebViewCurrentLanguage(nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::GetWebViewTranslateTextInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    std::string extraData = data.ReadString();
    reply.WriteInt32(GetWebViewTranslateText(extraData, nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::StartWebViewTranslateInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    std::string extraData = data.ReadString();
    int32_t processId = data.ReadInt32();
    UiSessionManager::GetInstance()->SaveProcessId("translate", processId);
    reply.WriteInt32(StartWebViewTranslate(extraData, nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::SendTranslateResultInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t nodeId = data.ReadInt32();
    std::vector<std::string> results;
    data.ReadStringVector(&results);
    std::vector<int32_t> ids;
    data.ReadInt32Vector(&ids);
    reply.WriteInt32(SendTranslateResult(nodeId, results, ids));
    return NO_ERROR;
}
int32_t UiContentStub::EndWebViewTranslateInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(EndWebViewTranslate());
    return NO_ERROR;
}

int32_t UiContentStub::SendTranslateResultStrInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t nodeId = data.ReadInt32();
    std::string result = data.ReadString();
    reply.WriteInt32(SendTranslateResult(nodeId, result));
    return NO_ERROR;
}

int32_t UiContentStub::GetCurrentPageNameInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(GetCurrentPageName(nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::GetCurrentImagesShowingInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t processId = data.ReadInt32();
    UiSessionManager::GetInstance()->SaveProcessId("pixel", processId);
    reply.WriteInt32(GetCurrentImagesShowing(nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::GetVisibleInspectorTreeInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    GetVisibleInspectorTree(nullptr);
    return NO_ERROR;
}
} // namespace OHOS::Ace
