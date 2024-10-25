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

#include "adapter/ohos/entrance/ace_container.h"

namespace OHOS::Ace::Platform {
namespace {
constexpr uint32_t DEFAULT_WINDOW_TYPE = 1;
}
sptr<IRemoteObject> AceContainer::GetToken()
{
    return token_;
}

sptr<IRemoteObject> AceContainer::GetParentToken()
{
    return token_;
}

std::shared_ptr<AbilityRuntime::Context> AceContainer::GetAbilityContextByModule(
    const std::string& bundle, const std::string& module)
{
    return nullptr;
}

sptr<OHOS::Rosen::Window> AceContainer::GetUIWindow(int32_t instanceId)
{
    return nullptr;
}

uint32_t AceContainer::GetParentWindowType() const
{
    return DEFAULT_WINDOW_TYPE;
}

uint32_t AceContainer::GetWindowType() const
{
    return DEFAULT_WINDOW_TYPE;
}

Rosen::AvoidArea AceContainer::GetAvoidAreaByType(Rosen::AvoidAreaType type)
{
    return {};
}

RefPtr<AceContainer> AceContainer::GetContainer(int32_t instanceId)
{
    return nullptr;
}

void AceContainer::SetCurPointerEvent(const std::shared_ptr<MMI::PointerEvent>& currentEvent) {}

void AceContainer::UpdateConfiguration(const ParsedConfig& parsedConfig, const std::string& configuration) {}
} // namespace OHOS::Ace::Platform
