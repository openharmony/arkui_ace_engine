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

#include "core/components_ng/pattern/window_scene/scene/host/host_window_extension.h"

#include "extension_session.h"
#include "extension_session_manager.h"

#include "core/components_ng/pattern/window_scene/scene/container/window_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

HostWindowExtension::HostWindowExtension(const std::string& bundleName, const std::string& abilityName)
{
    auto callerToken = nullptr;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto windowPattern = pipelineContext->GetWindowPattern();
    if (windowPattern) {
        // callerToken = windowPattern->GetCallerToken();
    } else {
        LOGD("Current pipeline does not use window scene");
    }

    Rosen::WindowSession::AbilityInfo extensionAbilityInfo = {
        .bundleName_ = bundleName,
        .abilityName_ = abilityName,
        .callerToken_ = callerToken,
        .isExtension_ = true,
    };
    session_ = Rosen::ExtensionSessionManager::GetInstance().RequestExtensionSession(extensionAbilityInfo);
    RegisterLifecycleListener();
    RequestExtensionSessionActivation();
}

HostWindowExtension::~HostWindowExtension()
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
