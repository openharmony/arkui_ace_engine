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

#include "core/components_ng/manager/environment/system_env_dispatcher.h"

namespace OHOS::Ace::NG {
namespace {
std::unordered_map<std::string_view, SystemEnvHandler>& GetSystemEnvHandlerIndex()
{
    static std::unordered_map<std::string_view, SystemEnvHandler> handlers;
    return handlers;
}

const SystemEnvHandler* FindSystemEnvHandler(std::string_view key)
{
    auto& handlers = GetSystemEnvHandlerIndex();
    auto iter = handlers.find(key);
    if (iter == handlers.end()) {
        return nullptr;
    }
    return &iter->second;
}
} // namespace

void RegisterSystemEnvHandler(const SystemEnvHandler& handler)
{
    if (handler.key.empty()) {
        return;
    }
    GetSystemEnvHandlerIndex()[handler.key] = handler;
}

SystemEnvImplicitNotifyMode GetSystemEnvImplicitNotifyMode(std::string_view key)
{
    auto handler = FindSystemEnvHandler(key);
    return handler ? handler->implicitNotifyMode : SystemEnvImplicitNotifyMode::NONE;
}

void DispatchImplicitSystemEnvChanged(const SystemEnvDispatchContext& context)
{
    auto handler = FindSystemEnvHandler(context.key);
    if (!handler || !handler->dispatchImplicit) {
        return;
    }
    handler->dispatchImplicit(context);
}

} // namespace OHOS::Ace::NG
