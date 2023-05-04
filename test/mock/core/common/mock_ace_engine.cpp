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

AceEngine::AceEngine() {}

AceEngine::~AceEngine() {}
AceEngine& AceEngine::Get()
{
    static AceEngine engine;
    return engine;
}

void AceEngine::InitJsDumpHeadSignal() {}

void AceEngine::AddContainer(int32_t instanceId, const RefPtr<Container>& container) {}

void AceEngine::RemoveContainer(int32_t instanceId) {}

RefPtr<Container> AceEngine::GetContainer(int32_t instanceId)
{
    return nullptr;
}

void AceEngine::RegisterToWatchDog(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor, bool useUIAsJSThread)
{}

void AceEngine::UnRegisterFromWatchDog(int32_t instanceId) {}

void AceEngine::BuriedBomb(int32_t instanceId, uint64_t bombId) {}

void AceEngine::DefusingBomb(int32_t instanceId) {}

void AceEngine::TriggerGarbageCollection() {}

void AceEngine::NotifyContainers(const std::function<void(const RefPtr<Container>&)>& callback) {}

void AceEngine::DumpJsHeap(bool isPrivate) const {}

} // namespace OHOS::Ace
