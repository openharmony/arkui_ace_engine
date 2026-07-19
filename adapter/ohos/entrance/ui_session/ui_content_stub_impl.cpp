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

#include "ipc_skeleton.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace {

int32_t UIContentServiceStubImpl::GetInspectorTree(
    const std::function<void(std::string, int32_t, bool)>& eventCallback, ParamConfig config,
    [[maybe_unused]] int32_t timeout)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetInspectorTree(config);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterClickEventCallback(const EventCallback& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetClickEventRegistered(true);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterRouterChangeEventCallback(const EventCallback& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetRouterChangeEventRegistered(true);
#endif
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::RegisterSearchEventCallback(const EventCallback& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetSearchEventRegistered(true);
#endif
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::RegisterTextChangeEventCallback(const EventCallback& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetTextChangeEventRegistered(true);
#endif
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::RegisterComponentChangeEventCallback(const EventCallback& eventCallback,
    uint32_t mask)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetComponentChangeEventRegistered(true);
#endif
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetComponentChangeEventMask(mask);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterWebUnfocusEventCallback(
    const std::function<void(int64_t accessibilityId, const std::string& data)>& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->NotifyAllWebPattern(true);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterScrollEventCallback(const EventCallback& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetScrollEventRegistered(true);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterLifeCycleEventCallback(const EventCallback& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetLifeCycleEventRegistered(true);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterSelectTextEventCallback(const EventCallback& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetSelectTextEventRegistered(true);
#endif
    // first register
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->ReportSelectText();
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::SendCommand(int32_t id, const std::string& command)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->NotifySendCommandPattern(id, command);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::SendCommandAsync(int32_t id, const std::string& command)
{
#ifndef CROSS_PLATFORM
    return UiSessionManager::GetInstance()->NotifySendCommandAsyncPattern(id, command);
#else
    return NO_ERROR;
#endif
}

int32_t UIContentServiceStubImpl::SendCommand(const std::string command)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SendCommand(command);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterClickEventCallback()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetClickEventRegistered(false);
#endif
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterSearchEventCallback()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetSearchEventRegistered(false);
#endif
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterTextChangeEventCallback()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetTextChangeEventRegistered(false);
#endif
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterRouterChangeEventCallback()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetRouterChangeEventRegistered(false);
#endif
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterComponentChangeEventCallback()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetComponentChangeEventRegistered(false);
#endif
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetComponentChangeEventMask(ComponentEventType::COMPONENT_EVENT_NONE);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterWebUnfocusEventCallback()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->NotifyAllWebPattern(false);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterScrollEventCallback()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetScrollEventRegistered(false);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterLifeCycleEventCallback()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetLifeCycleEventRegistered(false);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterSelectTextEventCallback()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SetSelectTextEventRegistered(false);
#endif
    return NO_ERROR;
}

bool UIContentServiceStubImpl::IsConnect()
{
    return false;
}

int32_t UIContentServiceStubImpl::ResetTranslateTextAll()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->ResetTranslate(-1);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::ResetTranslateText(int32_t nodeId)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->ResetTranslate(nodeId);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetWebViewTranslateText(
    const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetWebTranslateText(data, false);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::StartWebViewTranslate(
    const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetWebTranslateText(data, true);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetWebViewCurrentLanguage(const EventCallback& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetWebViewLanguage();
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::SendTranslateResult(
    int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SendTranslateResult(nodeId, results, ids);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::EndWebViewTranslate()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->ResetTranslate(-1);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::SendTranslateResult(int32_t nodeId, std::string result)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->SendTranslateResult(nodeId, result);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetPageTranslateText(
    const std::string& request, const PageTranslateTextCallback& eventCallback)
{
    return UiSessionManager::GetInstance()->GetPageTranslateText(request);
}

int32_t UIContentServiceStubImpl::StartPageTranslate(
    const std::string& request, const PageTranslateTextCallback& eventCallback)
{
    return UiSessionManager::GetInstance()->StartPageTranslate(request);
}

int32_t UIContentServiceStubImpl::EndPageTranslate()
{
    UiSessionManager::GetInstance()->EndPageTranslate();
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::ResetPageTranslate(int32_t nodeId)
{
    UiSessionManager::GetInstance()->ResetPageTranslate(nodeId);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::SendPageTranslateResult(const std::string& result)
{
    UiSessionManager::GetInstance()->SendPageTranslateResult(result);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetCurrentAbilityLanguageInfo(std::string& language, std::string& region)
{
    return UiSessionManager::GetInstance()->GetCurrentAbilityLanguageInfo(language, region);
}

int32_t UIContentServiceStubImpl::GetCurrentImagesShowing(
    const std::function<void(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>)>& finishCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetPixelMap();
#endif
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
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetMultiImagesById(arkUIIds, arkWebs);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetCurrentPageName(const EventCallback& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetCurrentPageName();
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetVisibleInspectorTree(
    const std::function<void(std::string, int32_t, bool)>& eventCallback, ParamConfig config,
    [[maybe_unused]] int32_t timeout)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetVisibleInspectorTree(config);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetLatestHitTestNodeInfosForTouch(
    const std::function<void(std::string, int32_t, bool)>& eventCallback, InteractionParamConfig config)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetLatestHitTestNodeInfosForTouch(config);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::ExeAppAIFunction(
    const std::string& funcName, const std::string& params, const sptr<IRemoteObject>& remoteObj, int32_t nodeId,
    const std::function<void(uint32_t, std::string)>& finishCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->ExeAppAIFunction(funcName, params, remoteObj, nodeId);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterContentChangeCallback(const ContentChangeConfig& config,
    const std::function<void(ChangeType type, const std::string& simpleTree)> callback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->RegisterContentChangeCallback(config);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetSpecifiedContentOffsets(int32_t id, const std::string& content,
    const std::function<void(std::vector<std::pair<float, float>>)>& eventCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetSpecifiedContentOffsets(id, content);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::HighlightSpecifiedContent(int32_t id, const std::string& content,
    const std::vector<std::string>& nodeIds, const std::string& configs)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->HighlightSpecifiedContent(id, content, nodeIds, configs);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterContentChangeCallback()
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->UnregisterContentChangeCallback();
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetStateMgmtInfo(const std::string& componentName, const std::string& propertyName,
    const std::string& jsonPath, const std::function<void(std::vector<std::string>)>& eventCallback,
    bool onlyVisible)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetStateMgmtInfo(componentName, propertyName, jsonPath, onlyVisible);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::GetWebInfoByRequest(
    int32_t webId,
    const std::string& request,
    const GetWebInfoByRequestCallback& finishCallback)
{
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->GetWebInfoByRequest(webId, request);
#endif
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterPageSceneRules(
    const std::string& ruleJson, const PageSceneEventCallback& eventCallback)
{
    if (ruleJson.empty()) {
        return PARAM_INVALID;
    }
    int32_t processId = IPCSkeleton::GetCallingRealPid();
    return UiSessionManager::GetInstance()->RegisterPageSceneRules(processId, ruleJson);
}

int32_t UIContentServiceStubImpl::UnregisterPageSceneRules(const std::string& ruleSetId)
{
    if (ruleSetId.empty()) {
        return PARAM_INVALID;
    }
    int32_t processId = IPCSkeleton::GetCallingRealPid();
    return UiSessionManager::GetInstance()->UnregisterPageSceneRules(processId, ruleSetId);
}

int32_t UIContentServiceStubImpl::GetPageScene(
    const std::string& ruleJsonOrRuleSetId, const PageSceneEventCallback& eventCallback)
{
    if (ruleJsonOrRuleSetId.empty()) {
        return PARAM_INVALID;
    }
    int32_t processId = IPCSkeleton::GetCallingRealPid();
    return UiSessionManager::GetInstance()->GetPageScene(processId, ruleJsonOrRuleSetId);
}
} // namespace OHOS::Ace
