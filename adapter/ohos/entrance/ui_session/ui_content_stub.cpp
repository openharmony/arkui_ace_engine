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

#include "accesstoken_kit.h"
#include "ipc_skeleton.h"

#include "adapter/ohos/entrance/ui_session/ui_session_manager_ohos.h"
#include "ui_content_errors.h"

#include "adapter/ohos/entrance/ui_session/include/ui_session_log.h"
#include "adapter/ohos/entrance/ui_session/content_change_config_impl.h"
#include "adapter/ohos/entrance/ui_session/get_inspector_tree_config_impl.h"

namespace OHOS::Ace {
bool UiContentStub::IsSACalling() const
{
    using namespace Security::AccessToken;
    const auto tokenId = IPCSkeleton::GetCallingTokenID();
    const auto flag = AccessTokenKit::GetTokenTypeFlag(tokenId);
    if (flag == ATokenTypeEnum::TOKEN_NATIVE) {
        LOGD("SA called, tokenId:%{private}u, flag:%{public}u", tokenId, flag);
        return true;
    }
    LOGW("Not SA called, tokenId:%{private}u, flag:%{public}u", tokenId, flag);
    return false;
}

int32_t UiContentStub::OnRemoteRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    if (!IsSACalling()) {
        return -1;
    }
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
        case REGISTER_TEXT_CHANGE_EVENT: {
            RegisterTextChangeEventCallbackInner(data, reply, option);
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
        case REGISTER_SCROLL_EVENT: {
            RegisterScrollEventCallbackInner(data, reply, option);
            break;
        }
        case REGISTER_LIFE_CYCLE_EVENT: {
            RegisterLifeCycleEventCallbackInner(data, reply, option);
            break;
        }
        case REGISTER_SELECT_TEXT_EVENT: {
            RegisterSelectTextEventCallbackInner(data, reply, option);
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
        case UNREGISTER_TEXT_CHANGE_EVENT: {
            UnregisterTextChangeEventCallbackInner(data, reply, option);
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
        case UNREGISTER_SCROLL_EVENT: {
            UnregisterScrollEventCallbackInner(data, reply, option);
            break;
        }
        case UNREGISTER_LIFE_CYCLE_EVENT: {
            UnregisterLifeCycleEventCallbackInner(data, reply, option);
            break;
        }
        case UNREGISTER_SELECT_TEXT_EVENT: {
            UnregisterSelectTextEventCallbackInner(data, reply, option);
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
        case EXE_APP_AI_FUNCTION: {
            ExeAppAIFunctionInner(data, reply, option);
            break;
        }
        case GET_SPECIFIED_CONTENT_OFFSETS: {
            GetSpecifiedContentOffsetsInner(data, reply, option);
            break;
        }
        case HIGHLIGHT_SPECIFIED_CONTENT: {
            HighlightSpecifiedContentInner(data, reply, option);
            break;
        }
        case GET_MULTI_IMAGES_BY_ID: {
            GetMultiImagesByIdInner(data, reply, option);
            break;
        }
        case REGISTER_CONTENT_CHANGE: {
            RegisterContentChangeCallbackInner(data, reply, option);
            break;
        }
        case UNREGISTER_CONTENT_CHANGE: {
            UnregisterContentChangeCallbackInner(data, reply, option);
            break;
        }
        case GET_HIT_TEST_NODE_INFO_FOR_TOUCH: {
            GetHitTestNodeInfoForTouchInner(data, reply, option);
            break;
        }
        case REQUEST_STATE_MGMT_INFO: {
            GetStateMgmtInfoInner(data, reply, option);
            break;
        }
        case GET_WEBINFO_BY_REQUEST: {
            GetWebInfoByRequestInner(data, reply, option);
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
    GetInspectorTreeConfigImpl* configImplPtr = data.ReadParcelable<GetInspectorTreeConfigImpl>();
    if (!configImplPtr) {
        LOGW("GetInspectorTreeInner read GetInspectorTreeConfigImpl failed");
        return FAILED;
    }
    GetInspectorTree(nullptr, configImplPtr->GetConfig());
    delete configImplPtr;
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
    UiSessionManagerOhos* uisession = reinterpret_cast<UiSessionManagerOhos*>(UiSessionManager::GetInstance());
    uisession->SaveReportStub(report, processId);
    uisession->SendBaseInfo(processId);
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

int32_t UiContentStub::RegisterTextChangeEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(RegisterTextChangeEventCallback(nullptr));
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

int32_t UiContentStub::RegisterScrollEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(RegisterScrollEventCallback(nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::RegisterLifeCycleEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(RegisterLifeCycleEventCallback(nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::RegisterSelectTextEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(RegisterSelectTextEventCallback(nullptr));
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

int32_t UiContentStub::UnregisterTextChangeEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(UnregisterTextChangeEventCallback());
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

int32_t UiContentStub::UnregisterScrollEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(UnregisterScrollEventCallback());
    return NO_ERROR;
}
int32_t UiContentStub::UnregisterLifeCycleEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(UnregisterLifeCycleEventCallback());
    return NO_ERROR;
}

int32_t UiContentStub::UnregisterSelectTextEventCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    reply.WriteInt32(UnregisterSelectTextEventCallback());
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

int32_t UiContentStub::GetMultiImagesByIdInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t processId = data.ReadInt32();
    UiSessionManager::GetInstance()->SaveProcessId("getArkUIImages", processId);
    UiSessionManager::GetInstance()->SaveProcessId("getArkWebImages", processId);
    std::vector<int32_t> arkUIIds;
    data.ReadInt32Vector(&arkUIIds);
    std::map<int32_t, std::vector<int32_t>> arkWebs;
    size_t mapSize = data.ReadUint64();
    for (size_t i = 0; i < mapSize; ++i) {
        int32_t webId = data.ReadInt32();
        std::vector<int32_t> webImageIds;
        data.ReadInt32Vector(&webImageIds);
        arkWebs.emplace(webId, std::move(webImageIds));
    }
    reply.WriteInt32(GetImagesById(arkUIIds, nullptr, arkWebs, nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::GetVisibleInspectorTreeInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    GetInspectorTreeConfigImpl* configImplPtr = data.ReadParcelable<GetInspectorTreeConfigImpl>();
    if (!configImplPtr) {
        LOGW("GetVisibleInspectorTreeInner read GetInspectorTreeConfigImpl failed");
        return FAILED;
    }
    GetVisibleInspectorTree(nullptr, configImplPtr->GetConfig());
    delete configImplPtr;
    return NO_ERROR;
}

int32_t UiContentStub::GetHitTestNodeInfoForTouchInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    InteractionParamConfig settedParamConfig = { data.ReadBool() };
    GetLatestHitTestNodeInfosForTouch(nullptr, settedParamConfig);
    return NO_ERROR;
}

int32_t UiContentStub::ExeAppAIFunctionInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    std::string funcName = data.ReadString();
    std::string params = data.ReadString();
    reply.WriteInt32(ExeAppAIFunction(funcName, params, nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::RegisterContentChangeCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t processId = data.ReadInt32();
    UiSessionManager::GetInstance()->SaveProcessId("contentChange", processId);
    ContentChangeConfigImpl* configImplPtr = data.ReadParcelable<ContentChangeConfigImpl>();
    if (!configImplPtr) {
        LOGW("RegisterContentChangeCallbackInner read ContentChangeConfig failed");
        reply.WriteInt32(FAILED);
        return FAILED;
    }

    ContentChangeConfig config = configImplPtr->GetConfig();
    int32_t ret = RegisterContentChangeCallback(config, nullptr);
    delete configImplPtr;

    reply.WriteInt32(ret);
    return NO_ERROR;
}

int32_t UiContentStub::UnregisterContentChangeCallbackInner(
    MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    UiSessionManager::GetInstance()->EraseProcessId("contentChange");
    reply.WriteInt32(UnregisterContentChangeCallback());
    return NO_ERROR;
}

int32_t UiContentStub::GetSpecifiedContentOffsetsInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t id = data.ReadInt32();
    std::string content = data.ReadString();
    reply.WriteInt32(GetSpecifiedContentOffsets(id, content, nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::HighlightSpecifiedContentInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t id = data.ReadInt32();
    std::string content = data.ReadString();
    int32_t size = data.ReadInt32();
    std::string configs = data.ReadString();
    std::vector<std::string> nodeIds;
    for (int32_t i = 0; i < size; i++) {
        nodeIds.push_back(data.ReadString());
    }
    reply.WriteInt32(HighlightSpecifiedContent(id, content, nodeIds, configs));
    return NO_ERROR;
}

int32_t UiContentStub::GetStateMgmtInfoInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t processId = data.ReadInt32();
    UiSessionManager::GetInstance()->SaveProcessId("GetStateMgmtInfo", processId);
    std::string componentName = data.ReadString();
    std::string propertyName = data.ReadString();
    std::string jsonPath = data.ReadString();
    reply.WriteInt32(GetStateMgmtInfo(componentName, propertyName, jsonPath, nullptr));
    return NO_ERROR;
}

int32_t UiContentStub::GetWebInfoByRequestInner(MessageParcel& data, MessageParcel& reply, MessageOption& option)
{
    int32_t processId = data.ReadInt32();
    UiSessionManager::GetInstance()->SaveProcessId("GetWebInfoByRequest", processId);
    int32_t webId = data.ReadInt32();
    std::string request = data.ReadString();
    reply.WriteInt32(GetWebInfoByRequest(webId, request, nullptr));
    return NO_ERROR;
}
} // namespace OHOS::Ace
