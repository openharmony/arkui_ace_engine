/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/window_scene/scene/host/host_window_extension.h"

#include "session/host/include/extension_session.h"
#include "session_manager/include/extension_session_manager.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/window_scene/scene/container/window_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

HostWindowExtension::HostWindowExtension(const std::string& bundleName, const std::string& abilityName)
{
    sptr<OHOS::IRemoteObject> callerToken = nullptr;
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    CHECK_NULL_VOID(container);
    auto context = container->GetAbilityRuntimeContext();
    if (context != nullptr) {
        callerToken = context->GetToken();
    }

    Rosen::ExtensionSessionManager::GetInstance().Init();
    Rosen::SessionInfo extensionSessionInfo = {
        .bundleName_ = bundleName,
        .abilityName_ = abilityName,
        .callerToken_ = callerToken,
    };
    session_ = Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSession(extensionSessionInfo);
    RegisterLifecycleListener();
    RequestExtensionSessionActivation();
}

HostWindowExtension::~HostWindowExtension()
{
    RequestExtensionSessionDestruction();
}

void HostWindowExtension::OnWindowShow()
{
    RequestExtensionSessionActivation();
}

void HostWindowExtension::OnWindowHide()
{
    RequestExtensionSessionBackground();
}

void HostWindowExtension::RequestExtensionSessionActivation()
{
    CHECK_NULL_VOID(session_);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionActivation(extensionSession);
}

void HostWindowExtension::RequestExtensionSessionBackground()
{
    CHECK_NULL_VOID(session_);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionBackground(extensionSession);
}

void HostWindowExtension::RequestExtensionSessionDestruction()
{
    CHECK_NULL_VOID(session_);
    sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
    Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSessionDestruction(extensionSession);
}

} // namespace OHOS::Ace::NG
