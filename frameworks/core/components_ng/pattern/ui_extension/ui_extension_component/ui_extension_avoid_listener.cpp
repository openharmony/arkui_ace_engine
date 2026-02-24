/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_avoid_listener.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {}
UIExtensionAvoidListener::UIExtensionAvoidListener(const WeakPtr<UIExtensionPattern>& pattern) : pattern_(pattern) {}

UIExtensionAvoidListener::~UIExtensionAvoidListener() {}

void UIExtensionAvoidListener::OnAvoidInfoChange(const ContainerModalAvoidInfo& info)
{
    auto uiExtensionPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(uiExtensionPattern);
    auto host = uiExtensionPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
#ifdef WINDOW_SCENE_SUPPORTED
    auto uiExtManager = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtManager);
    auto avoidInfoMgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_VOID(avoidInfoMgr);
    avoidInfoMgr->SetIsUpdateButtonRect(true);
    uiExtManager->NotifyNestedUECProvidersIfNeeded();
#endif
}

void UIExtensionAvoidListener::RegisterAvoidInfoChangeListener(int32_t instanceId)
{
    auto container = Platform::AceContainer::GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    CHECK_EQUAL_VOID(container->IsUIExtensionWindow(), false);
    auto uiExtensionPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(uiExtensionPattern);
    auto host = uiExtensionPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto hostNode = AceType::RawPtr(host);
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto mgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_VOID(mgr);
    mgr->AddAvoidInfoListener(WeakClaim(this));
}

void UIExtensionAvoidListener::UnRegisterAvoidInfoChangeListener()
{
    auto uiExtensionPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(uiExtensionPattern);
    auto host = uiExtensionPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto mgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_VOID(mgr);
    mgr->RemoveAvoidInfoListener(WeakClaim(this));
}
} // namespace OHOS::Ace::NG
