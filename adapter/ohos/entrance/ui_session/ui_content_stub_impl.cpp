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

#include "interfaces/inner_api/ui_session/ui_content_stub_impl.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace {

int32_t UIContentServiceStubImpl::GetInspectorTree(
    const std::function<void(std::string, int32_t, bool)>& eventCallback, ParamConfig config)
{
    UiSessionManager::GetInstance()->GetInspectorTree(config);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterClickEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance()->SetClickEventRegistered(true);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterRouterChangeEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance()->SetRouterChangeEventRegistered(true);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::RegisterSearchEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance()->SetSearchEventRegistered(true);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::RegisterTextChangeEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance()->SetTextChangeEventRegistered(true);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::RegisterComponentChangeEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance()->SetComponentChangeEventRegistered(true);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterWebUnfocusEventCallback(
    const std::function<void(int64_t accessibilityId, const std::string& data)>& eventCallback)
{
    UiSessionManager::GetInstance()->NotifyAllWebPattern(true);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterScrollEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance()->SetScrollEventRegistered(true);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterLifeCycleEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance()->SetLifeCycleEventRegistered(true);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterSelectTextEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance()->SetSelectTextEventRegistered(true);
    // first register
    UiSessionManager::GetInstance()->ReportSelectText();
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::SendCommand(int32_t id, const std::string& command)
{
    UiSessionManager::GetInstance()->NotifySendCommandPattern(id, command);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::SendCommandAsync(int32_t id, const std::string& command)
{
    return UiSessionManager::GetInstance()->NotifySendCommandAsyncPattern(id, command);
}

int32_t UIContentServiceStubImpl::SendCommand(const std::string command)
{
    UiSessionManager::GetInstance()->SendCommand(command);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterClickEventCallback()
{
    UiSessionManager::GetInstance()->SetClickEventRegistered(false);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterSearchEventCallback()
{
    UiSessionManager::GetInstance()->SetSearchEventRegistered(false);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterTextChangeEventCallback()
{
    UiSessionManager::GetInstance()->SetTextChangeEventRegistered(false);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterRouterChangeEventCallback()
{
    UiSessionManager::GetInstance()->SetRouterChangeEventRegistered(false);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterComponentChangeEventCallback()
{
    UiSessionManager::GetInstance()->SetComponentChangeEventRegistered(false);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterWebUnfocusEventCallback()
{
    UiSessionManager::GetInstance()->NotifyAllWebPattern(false);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterScrollEventCallback()
{
    UiSessionManager::GetInstance()->SetScrollEventRegistered(false);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterLifeCycleEventCallback()
{
    UiSessionManager::GetInstance()->SetLifeCycleEventRegistered(false);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterSelectTextEventCallback()
{
    UiSessionManager::GetInstance()->SetSelectTextEventRegistered(false);
    return NO_ERROR;
}

bool UIContentServiceStubImpl::IsConnect()
{
    return false;
}

int32_t UIContentServiceStubImpl::ResetTranslateTextAll()
{
    UiSessionManager::GetInstance()->ResetTranslate(-1);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::ResetTranslateText(int32_t nodeId)
{
    UiSessionManager::GetInstance()->ResetTranslate(nodeId);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetWebViewTranslateText(
    const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback)
{
    UiSessionManager::GetInstance()->GetWebTranslateText(data, false);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::StartWebViewTranslate(
    const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback)
{
    UiSessionManager::GetInstance()->GetWebTranslateText(data, true);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetWebViewCurrentLanguage(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance()->GetWebViewLanguage();
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::SendTranslateResult(
    int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids)
{
    UiSessionManager::GetInstance()->SendTranslateResult(nodeId, results, ids);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::EndWebViewTranslate()
{
    UiSessionManager::GetInstance()->ResetTranslate(-1);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::SendTranslateResult(int32_t nodeId, std::string result)
{
    UiSessionManager::GetInstance()->SendTranslateResult(nodeId, result);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetCurrentImagesShowing(
    const std::function<void(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>)>& finishCallback)
{
    UiSessionManager::GetInstance()->GetPixelMap();
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetImagesById(
    const std::vector<int32_t>& arkUIIds,
    const std::function<void(int32_t, const std::unordered_map<int32_t, std::shared_ptr<Media::PixelMap>>&,
        MultiImageQueryErrorCode)>& arkUIfinishCallback,
    const std::map<int32_t, std::vector<int32_t>>& arkWebs,
    const std::function<void(int32_t, const std::map<int32_t, std::map<int32_t,
        std::shared_ptr<Media::PixelMap>>>&, MultiImageQueryErrorCode)>& arkWebfinishCallback)
{
    UiSessionManager::GetInstance()->GetMultiImagesById(arkUIIds, arkWebs);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetCurrentPageName(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance()->GetCurrentPageName();
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetVisibleInspectorTree(
    const std::function<void(std::string, int32_t, bool)>& eventCallback, ParamConfig config)
{
    UiSessionManager::GetInstance()->GetVisibleInspectorTree(config);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetLatestHitTestNodeInfosForTouch(
    const std::function<void(std::string, int32_t, bool)>& eventCallback, InteractionParamConfig config)
{
    UiSessionManager::GetInstance()->GetLatestHitTestNodeInfosForTouch(config);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::ExeAppAIFunction(
    const std::string& funcName, const std::string& params, const std::function<void(uint32_t)>& finishCallback)
{
    UiSessionManager::GetInstance()->ExeAppAIFunction(funcName, params);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterContentChangeCallback(const ContentChangeConfig& config,
    const std::function<void(ChangeType type, const std::string& simpleTree)> callback)
{
    UiSessionManager::GetInstance()->RegisterContentChangeCallback(config);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetSpecifiedContentOffsets(int32_t id, const std::string& content,
    const std::function<void(std::vector<std::pair<float, float>>)>& eventCallback)
{
    UiSessionManager::GetInstance()->GetSpecifiedContentOffsets(id, content);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::HighlightSpecifiedContent(int32_t id, const std::string& content,
    const std::vector<std::string>& nodeIds, const std::string& configs)
{
    UiSessionManager::GetInstance()->HighlightSpecifiedContent(id, content, nodeIds, configs);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterContentChangeCallback()
{
    UiSessionManager::GetInstance()->UnregisterContentChangeCallback();
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetStateMgmtInfo(const std::string& componentName, const std::string& propertyName,
    const std::string& jsonPath, const std::function<void(std::vector<std::string>)>& eventCallback)
{
    UiSessionManager::GetInstance()->GetStateMgmtInfo(componentName, propertyName, jsonPath);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetWebInfoByRequest(
    int32_t webId,
    const std::string& request,
    const GetWebInfoByRequestCallback& finishCallback)
{
    UiSessionManager::GetInstance()->GetWebInfoByRequest(webId, request);
    return NO_ERROR;
}
} // namespace OHOS::Ace
