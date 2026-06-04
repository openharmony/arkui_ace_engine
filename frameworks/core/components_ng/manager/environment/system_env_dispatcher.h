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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_ENVIRONMENT_SYSTEM_ENV_DISPATCHER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_ENVIRONMENT_SYSTEM_ENV_DISPATCHER_H

#include <cstdint>
#include <string_view>
#include <unordered_map>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

class EnvironmentManager;
class FrameNode;
class UINode;

enum class SystemEnvImplicitNotifyMode : uint8_t {
    NONE = 0,
    FULL,
    PRECISE,
};

struct SystemEnvDispatchContext {
    EnvironmentManager& manager;
    RefPtr<UINode> node;
    RefPtr<FrameNode> frameNode;
    std::string_view key;
};

using SystemEnvDispatchCallback = void (*)(const SystemEnvDispatchContext& context);

struct SystemEnvHandler {
    std::string_view key;
    SystemEnvImplicitNotifyMode implicitNotifyMode = SystemEnvImplicitNotifyMode::NONE;
    SystemEnvDispatchCallback dispatchImplicit = nullptr;
};

void RegisterSystemEnvHandler(const SystemEnvHandler& handler);

SystemEnvImplicitNotifyMode GetSystemEnvImplicitNotifyMode(std::string_view key);

void DispatchImplicitSystemEnvChanged(const SystemEnvDispatchContext& context);

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_ENVIRONMENT_SYSTEM_ENV_DISPATCHER_H
