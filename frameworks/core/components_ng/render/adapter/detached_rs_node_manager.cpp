/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/detached_rs_node_manager.h"

#include "render_service_client/core/ui/rs_node.h"
#include "render_service_client/core/ui/rs_ui_context.h"
#include "render_service_client/core/ui/rs_ui_director.h"

#include "base/utils/time_util.h"
#include "base/log/ace_trace.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/frontend.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {
constexpr int64_t PRE_FREEZE_FLUSH_SLOW_THRESHOLD_MS = 50;
} // namespace

void DetachedRsNodeManager::PostDestructorTask(std::shared_ptr<Rosen::RSNode> rsNode)
{
    CHECK_NULL_VOID(rsNode);
    auto rsUIContext = rsNode->GetRSUIContext();
    CHECK_NULL_VOID(rsUIContext);
    // pipelineCount is the number of the pipelinecontext which is binded to the rsUIContext.
    auto pipelineCount = rsUIContext->GetUiPiplineNum();
    CHECK_NULL_VOID(pipelineCount == 0 && taskExecutor_);
    {
        std::lock_guard<std::mutex> lock(mutex_);
        CHECK_NULL_VOID(rsUIContexts_.find(rsUIContext.get()) == rsUIContexts_.end());
        rsUIContexts_.emplace(rsUIContext.get());
    }
    LOGD("DetachedRsNodeManager start %{public}" PRIu64 ".", rsUIContext->GetToken());
    taskExecutor_->PostTask(
        [rsUIContext]() {
            DetachedRsNodeManager::GetInstance().FlushImplicitTransaction(rsUIContext);
            LOGD("DetachedRsNodeManager end %{public}" PRIu64 ".", rsUIContext->GetToken());
            DetachedRsNodeManager::GetInstance().RemoveRSUIContext(rsUIContext);
        },
        "DetachedRsNodeManager", PriorityType::LOW);
}

void DetachedRsNodeManager::FlushImplicitTransaction(std::shared_ptr<Rosen::RSUIContext> rsUIContext)
{
    if (!rsUIContext) {
        LOGE("DetachedRsNodeManager fail, rsUIContext is nullptr");
        return;
    }
    auto transition = rsUIContext->GetRSTransaction();
    if (!transition) {
        LOGE("DetachedRsNodeManager fail, transition is nullptr");
        return;
    }
    auto pipelineCount = rsUIContext->GetUiPiplineNum();
    if (pipelineCount == 0) {
        transition->FlushImplicitTransaction();
    } else {
        LOGE("DetachedRsNodeManager fail, pipelineCount is not empty");
    }
}

void DetachedRsNodeManager::RemoveRSUIContext(std::shared_ptr<Rosen::RSUIContext> rsUIContext)
{
    CHECK_NULL_VOID(rsUIContext);
    std::lock_guard<std::mutex> lock(mutex_);
    rsUIContexts_.erase(rsUIContext.get());
}

void DetachedRsNodeManager::PreFreezeFlushForAllContexts()
{
    uint64_t nanoTimestamp = static_cast<uint64_t>(GetSysTimestamp());
    // Snapshot registeredInstances_ to avoid holding lock during iteration and ForceFlushVsync calls.
    std::unordered_set<int32_t> registeredIds;
    {
        std::lock_guard<std::mutex> lock(GetInstance().registeredMutex_);
        registeredIds = GetInstance().registeredInstances_;
    }
    for (auto instanceId : registeredIds) {
        auto container = Container::GetContainer(instanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        int32_t id = instanceId;
        auto task = [nanoTimestamp, id]() {
            FlushInstance(nanoTimestamp, id);
        };
        auto startTime = std::chrono::steady_clock::now();
        taskExecutor->PostSyncTask(task, TaskExecutor::TaskType::UI, "PreFreezeFlush", PriorityType::VIP);
        auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - startTime).count();
        if (durationMs > PRE_FREEZE_FLUSH_SLOW_THRESHOLD_MS) {
            LOGW("PreFreezeFlush slow instanceId:%{public}d duration:%{public}lldms",
                id, static_cast<long long>(durationMs));
        }
    }
}

void DetachedRsNodeManager::FlushInstance(uint64_t nanoTimestamp, int32_t instanceId)
{
    auto container = Container::GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    auto pipelineBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineBase);
    auto window = pipelineBase->GetWindow();
    CHECK_NULL_VOID(window);
    auto startTime = std::chrono::steady_clock::now();
    ACE_SCOPED_TRACE("ForceFlushVsync instanceId:%d", instanceId);
    window->ForceFlushVsync(nanoTimestamp, UINT64_MAX);
    auto durationMs =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
    LOGI("ForceFlushVsync instanceId:%{public}d duration:%{public}lldms", instanceId,
        static_cast<long long>(durationMs));
}

void DetachedRsNodeManager::TryRegisterExternalClearCallback(int32_t instanceId)
{
    if (externalClearRegistered_) {
        return;
    }
    auto container = Container::GetContainer(instanceId);
    if (!container) {
        LOGD("RegisterExternalClearCallback skip, container is null");
        return;
    }
    auto frontend = container->GetFrontend();
    if (!frontend) {
        LOGD("RegisterExternalClearCallback skip, frontend is null");
        return;
    }
    if (frontend->SetExternalClearCallback([]() { PreFreezeFlushForAllContexts(); })) {
        externalClearRegistered_ = true;
    } else {
        LOGW("RegisterExternalClearCallback failed, instanceId:%{public}d, "
             "jsEngine or nativeEngine not available yet, will retry on next Foreground",
            instanceId);
    }
}

void DetachedRsNodeManager::RegisterPreFreezeInstance(int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(registeredMutex_);
    TryRegisterExternalClearCallback(instanceId);
    registeredInstances_.insert(instanceId);
}

void DetachedRsNodeManager::UnregisterPreFreezeInstance(int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(registeredMutex_);
    registeredInstances_.erase(instanceId);
}
} // namespace OHOS::Ace
