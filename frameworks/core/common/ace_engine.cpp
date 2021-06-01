/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include <thread>

#include "base/log/log.h"
#include "core/common/ace_page.h"

namespace OHOS::Ace {

static std::unique_ptr<AceEngine> g_aceEngine;

AceEngine::AceEngine()
{
    watchDog_ = AceType::MakeRefPtr<WatchDog>();
}

AceEngine& AceEngine::Get()
{
    if (!g_aceEngine) {
        LOGI("AceEngine initialized in first time");
        g_aceEngine.reset(new AceEngine());
    }
    return *g_aceEngine;
}

void AceEngine::AddContainer(int32_t instanceId, const RefPtr<Container>& container)
{
    const auto result = containerMap_.try_emplace(instanceId, container);
    if (!result.second) {
        LOGW("already have container of this instance id: %{public}d", instanceId);
    }
}

void AceEngine::RemoveContainer(int32_t instanceId)
{
    auto num = containerMap_.erase(instanceId);
    if (num == 0) {
        LOGW("container not found with instance id: %{public}d", instanceId);
    }
    watchDog_->Unregister(instanceId);
}

void AceEngine::Dump(const std::vector<std::string>& params) const
{
    for (const auto& container : containerMap_) {
        auto pipelineContext = container.second->GetPipelineContext();
        pipelineContext->GetTaskExecutor()->PostSyncTask(
            [params, container = container.second]() { container->Dump(params); }, TaskExecutor::TaskType::UI);
    }
}

RefPtr<Container> AceEngine::GetContainer(int32_t instanceId)
{
    auto container = containerMap_.find(instanceId);
    if (container != containerMap_.end()) {
        return container->second;
    } else {
        return nullptr;
    }
}

void AceEngine::RegisterToWatchDog(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor)
{
    watchDog_->Register(instanceId, taskExecutor);
}

void AceEngine::SetPackageName(const std::string& packageName)
{
    packageName_ = packageName;
}

const std::string& AceEngine::GetPackageName() const
{
    return packageName_;
}

void AceEngine::SetPackagePath(const std::string& packagePath)
{
    packagePath_ = packagePath;
}

const std::string& AceEngine::GetPackagePath() const
{
    return packagePath_;
}

void AceEngine::SetAssetBasePath(const std::string& assetBasePath)
{
    assetBasePathSet_.insert(assetBasePath);
}

const std::set<std::string>& AceEngine::GetAssetBasePath() const
{
    return assetBasePathSet_;
}

RefPtr<Frontend> AceEngine::GetForegroundFrontend() const
{
    for (const auto& [first, second] : containerMap_) {
        auto frontend = second->GetFrontend();
        if (frontend && (frontend->GetType() == FrontendType::JS)) {
            if (frontend->IsForeground()) {
                return frontend;
            }
        }
    }
    LOGW("container not found foreground frontend");
    return nullptr;
}

void AceEngine::SetUid(int32_t uid)
{
    uid_ = uid;
}

int32_t AceEngine::GetUid() const
{
    return uid_;
}

void AceEngine::SetProcessName(const std::string& processName)
{
    processName_ = processName;
}

const std::string& AceEngine::GetProcessName() const
{
    return processName_;
}

} // namespace OHOS::Ace
