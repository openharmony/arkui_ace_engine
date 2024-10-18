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
    UiSessionManager::GetInstance().GetInspectorTree();
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterClickEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance().SetClickEventRegistered(true);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterRouterChangeEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance().SetRouterChangeEventRegistered(true);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::RegisterSearchEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance().SetSearchEventRegistered(true);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::RegisterComponentChangeEventCallback(const EventCallback& eventCallback)
{
    UiSessionManager::GetInstance().SetComponentChangeEventRegistered(true);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::RegisterWebUnfocusEventCallback(
    const std::function<void(int64_t accessibilityId, const std::string& data)>& eventCallback)
{
    UiSessionManager::GetInstance().NotifyAllWebPattern(true);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterClickEventCallback()
{
    UiSessionManager::GetInstance().SetClickEventRegistered(false);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterSearchEventCallback()
{
    UiSessionManager::GetInstance().SetSearchEventRegistered(false);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterRouterChangeEventCallback()
{
    UiSessionManager::GetInstance().SetRouterChangeEventRegistered(false);
    return NO_ERROR;
}
int32_t UIContentServiceStubImpl::UnregisterComponentChangeEventCallback()
{
    UiSessionManager::GetInstance().SetComponentChangeEventRegistered(false);
    return NO_ERROR;
}

int32_t UIContentServiceStubImpl::UnregisterWebUnfocusEventCallback()
{
    UiSessionManager::GetInstance().NotifyAllWebPattern(false);
    return NO_ERROR;
}

bool UIContentServiceStubImpl::IsConnect()
{
    return false;
}
} // namespace OHOS::Ace
