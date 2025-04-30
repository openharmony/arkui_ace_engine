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

#include "core/common/ace_engine.h"

namespace OHOS::Ace {
AceEngine::AceEngine() = default;

AceEngine::~AceEngine() = default;

AceEngine& AceEngine::Get()
{
    static AceEngine engine;
    return engine;
}

void AceEngine::NotifyContainers(const std::function<void(const RefPtr<Container>&)>& callback)
{
    for (const auto& [first, second] : containerMap_) {
        // first = container ID
        ContainerScope scope(first);
        callback(second);
    }
}

RefPtr<Container> AceEngine::GetContainer(int32_t instanceId)
{
    auto container = containerMap_.find(instanceId);
    if (container != containerMap_.end()) {
        return container->second;
    }
    return nullptr;
}

void AceEngine::AddContainer(int32_t instanceId, const RefPtr<Container>& container)
{
    containerMap_.emplace(instanceId, container);
}

void AceEngine::RemoveContainer(int32_t instanceId)
{
    containerMap_.erase(instanceId);
}
} // namespace OHOS::Ace
