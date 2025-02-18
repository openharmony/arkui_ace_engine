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

int32_t UIContentServiceStubImpl::GetInspectorTree(const std::function<void(std::string, int32_t, bool)>& eventCallback)
{
    UiSessionManager::GetInstance()->GetInspectorTree();
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
} // namespace OHOS::Ace
