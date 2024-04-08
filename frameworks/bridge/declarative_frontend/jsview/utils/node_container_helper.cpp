/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/utils/node_container_helper.h"

namespace OHOS::Ace::Framework {
std::unordered_map<int32_t, JSRef<JSVal>> NodeContainerHelper::uiContextMap_;
std::shared_mutex NodeContainerHelper::uiContextMapMutex_;

void NodeContainerHelper::AddUIContext(int32_t instanceId, JSRef<JSVal> uiContext)
{
    std::unique_lock<std::shared_mutex> lock(uiContextMapMutex_);
    uiContextMap_.emplace(instanceId, uiContext);
}

void NodeContainerHelper::RemoveUIContext(int32_t instanceId)
{
    std::unique_lock<std::shared_mutex> lock(uiContextMapMutex_);
    uiContextMap_.erase(instanceId);
}

JSRef<JSVal> NodeContainerHelper::GetUIContext(int32_t instanceId)
{
    std::shared_lock<std::shared_mutex> lock(uiContextMapMutex_);
    auto iter = uiContextMap_.find(instanceId);
    if (iter == uiContextMap_.end()) {
        return JSRef<JSVal>::Make();
    }
    return iter->second;
}

bool NodeContainerHelper::HasUIContext(int32_t instanceId)
{
    std::shared_lock<std::shared_mutex> lock(uiContextMapMutex_);
    auto iter = uiContextMap_.find(instanceId);
    return iter != uiContextMap_.end();
}
}