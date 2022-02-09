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

#include <csignal>
#include <cstdio>

#include "base/log/dump_log.h"
#include "base/log/log.h"
#include "base/memory/memory_monitor.h"
#include "base/thread/background_task_executor.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_page.h"
#include "core/image/image_cache.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t ELEMENT_ID = 54;
constexpr int32_t RENDER_ID = 55;
constexpr int32_t LAYER_ID = 56;
constexpr int32_t FOCUS_ID = 57;

std::unique_ptr<AceEngine> g_aceEngine;

void HandleSignal(int signo)
{
    LOGI("HandleSignal signal: %{public}d", signo);
    std::vector<std::string> params;
    switch (signo) {
        case ELEMENT_ID:
            params.emplace_back("-element");
            break;
        case RENDER_ID:
            params.emplace_back("-render");
            break;
        case LAYER_ID:
            params.emplace_back("-layer");
            break;
        case FOCUS_ID:
            params.emplace_back("-focus");
            break;
        default:
            return;
    }
    auto dumpFilePath = AceApplicationInfo::GetInstance().GetDataFileDirPath() + "/arkui.dump";
    auto fd = fopen(dumpFilePath.c_str(), "w");
    if (fd == nullptr) {
        LOGE("HandleSignal signal failed due to fd is null, path is %{private}s", dumpFilePath.c_str());
        return;
    }

    DumpLog::DumpFile fp(fd, &fclose);
    DumpLog::GetInstance().SetDumpFile(std::move(fp));
    AceEngine::Get().Dump(params);
}

}

AceEngine::AceEngine()
{
    watchDog_ = AceType::MakeRefPtr<WatchDog>();
    // TODO: Remove it after dump cmd ready.
    signal(ELEMENT_ID, HandleSignal);
    signal(RENDER_ID, HandleSignal);
    signal(LAYER_ID, HandleSignal);
    signal(FOCUS_ID, HandleSignal);
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
    LOGI("AddContainer %{public}d", instanceId);
    std::lock_guard<std::mutex> lock(mutex_);
    const auto result = containerMap_.try_emplace(instanceId, container);
    if (!result.second) {
        LOGW("already have container of this instance id: %{public}d", instanceId);
    }
}

void AceEngine::RemoveContainer(int32_t instanceId)
{
    LOGI("RemoveContainer %{public}d", instanceId);
    size_t num = 0;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        num = containerMap_.erase(instanceId);
    }
    if (num == 0) {
        LOGW("container not found with instance id: %{public}d", instanceId);
    }
    if (watchDog_) {
        watchDog_->Unregister(instanceId);
    }
}

void AceEngine::Dump(const std::vector<std::string>& params) const
{
    std::unordered_map<int32_t, RefPtr<Container>> copied;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        copied = containerMap_;
    }
    for (const auto& container : copied) {
        auto pipelineContext = container.second->GetPipelineContext();
        if (!pipelineContext) {
            LOGW("the pipeline context is nullptr, pa container");
            continue;
        }
        pipelineContext->GetTaskExecutor()->PostSyncTask(
            [params, container = container.second]() { container->Dump(params); }, TaskExecutor::TaskType::UI);
    }
}

RefPtr<Container> AceEngine::GetContainer(int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto container = containerMap_.find(instanceId);
    if (container != containerMap_.end()) {
        return container->second;
    } else {
        return nullptr;
    }
}

void AceEngine::RegisterToWatchDog(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor, bool useUIAsJSThread)
{
    if (watchDog_) {
        watchDog_->Register(instanceId, taskExecutor, useUIAsJSThread);
    }
}

void AceEngine::BuriedBomb(int32_t instanceId, uint64_t bombId)
{
    if (watchDog_) {
        watchDog_->BuriedBomb(instanceId, bombId);
    }
}

void AceEngine::DefusingBomb(int32_t instanceId)
{
    if (watchDog_) {
        watchDog_->DefusingBomb(instanceId);
    }
}

void AceEngine::TriggerGarbageCollection()
{
    std::unordered_map<int32_t, RefPtr<Container>> copied;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (containerMap_.empty()) {
            return;
        }
        copied = containerMap_;
    }

    auto taskExecutor = copied.begin()->second->GetTaskExecutor();
    taskExecutor->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::PLATFORM);
#if defined(OHOS_PLATFORM) && defined(ENABLE_NATIVE_VIEW)
    // GPU and IO thread is shared while enable native view
    taskExecutor->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::GPU);
    taskExecutor->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::IO);
#endif

    for (const auto& container : copied) {
        container.second->TriggerGarbageCollection();
    }

    ImageCache::Purge();
    BackgroundTaskExecutor::GetInstance().TriggerGarbageCollection();
    PurgeMallocCache();
}

void AceEngine::NotifyContainers(const std::function<void(const RefPtr<Container>&)>& callback)
{
    if (!callback) {
        return;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    for (const auto& [first, second] : containerMap_) {
        callback(second);
    }
}

} // namespace OHOS::Ace
