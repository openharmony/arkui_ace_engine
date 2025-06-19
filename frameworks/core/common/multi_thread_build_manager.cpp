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

#include "core/common/multi_thread_build_manager.h"

#ifdef FFRT_SUPPORT
#include "ffrt_inner.h"
#endif
#include "base/log/log_wrapper.h"
#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {
#ifdef FFRT_SUPPORT
constexpr uint32_t MAX_THREAD_NUM = 3;
constexpr uint32_t ASYNC_UITASK_QOS = 5;
std::unique_ptr<ffrt::queue> asyncUITaskQueue = nullptr;
#endif
}
thread_local bool MultiThreadBuildManager::isFreeNodeScope_ = false;
thread_local bool MultiThreadBuildManager::isUIThread_ = false;

MultiThreadBuildManager& MultiThreadBuildManager::GetInstance()
{
    static MultiThreadBuildManager MultiThreadBuildManager;
    return MultiThreadBuildManager;
}

MultiThreadBuildManager::MultiThreadBuildManager()
{
    InitAsyncUITaskQueue();
}

void MultiThreadBuildManager::InitOnUIThread()
{
    isUIThread_ = true;
}

void MultiThreadBuildManager::InitAsyncUITaskQueue()
{
#ifdef FFRT_SUPPORT
    asyncUITaskQueue = std::make_unique<ffrt::queue>(ffrt::queue_concurrent,
        "ArkUIAsyncUITask", ffrt::queue_attr().max_concurrency(MAX_THREAD_NUM));
#endif
}

bool MultiThreadBuildManager::IsOnUIThread()
{
    return isUIThread_;
}

bool MultiThreadBuildManager::CheckOnUIThread()
{
    if (!IsOnUIThread()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "CheckOnUIThread failed");
        return false;
    }
    return true;
}

bool MultiThreadBuildManager::CheckNodeOnValidThread(NG::UINode* node)
{
    if (!node) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "CheckNodeOnValidThread failed. node is nullptr");
        return false;
    }
    if (!node->IsFreeState() && !MultiThreadBuildManager::IsOnUIThread()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "CheckNodeOnValidThread failed. unfree node not run on main thread");
        return false;
    }
    return true;
}

void MultiThreadBuildManager::SetIsFreeNodeScope(bool isFreeNodeScope)
{
    isFreeNodeScope_ = isFreeNodeScope;
}

bool MultiThreadBuildManager::IsFreeNodeScope()
{
    return isFreeNodeScope_;
}

void MultiThreadBuildManager::TryExecuteUnSafeTask(NG::UINode* node, std::function<void()>&& task)
{
    if (node->IsFreeState()) {
        node->PostAfterAttachMainTreeTask(std::move(task));
    } else if (task) {
        task();
    }
}

bool MultiThreadBuildManager::TryPostUnSafeTask(NG::UINode* node, std::function<void()>&& task)
{
    if (node->IsFreeState()) {
        node->PostAfterAttachMainTreeTask(std::move(task));
        return true;
    }
    return false;
}

bool MultiThreadBuildManager::PostAsyncUITask(int32_t contextId, std::function<void()>&& asyncUITask,
    std::function<void()>&& onFinishTask)
{
    ContainerScope scope(contextId);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
#ifdef FFRT_SUPPORT
    if (!asyncUITaskQueue) {
        return false;
    }
    auto result = asyncUITaskQueue->submit_h([contextId,
        asyncUITask = std::move(asyncUITask), onFinishTask = std::move(onFinishTask)]() {
        ContainerScope scope(contextId);
        asyncUITask();
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask([contextId, onFinishTask = std::move(onFinishTask)]() {
            ContainerScope scope(contextId);
            onFinishTask();
            }, TaskExecutor::TaskType::UI, "ArkUIAsyncUIOnFinishTask", PriorityType::IMMEDIATE);
    }, ffrt::task_attr().qos(ASYNC_UITASK_QOS));
    return result != nullptr;
#else
    return taskExecutor->PostTask([contextId,
        asyncUITask = std::move(asyncUITask), onFinishTask = std::move(onFinishTask)]() {
        ContainerScope scope(contextId);
        asyncUITask();
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask([contextId, onFinishTask = std::move(onFinishTask)]() {
            ContainerScope scope(contextId);
            onFinishTask();
            }, TaskExecutor::TaskType::UI, "ArkUIAsyncUIOnFinishTask", PriorityType::IMMEDIATE);
        }, TaskExecutor::TaskType::BACKGROUND, "ArkUIAsyncUITask");
#endif
}

bool MultiThreadBuildManager::PostUITask(int32_t contextId, std::function<void()>&& uiTask)
{
    ContainerScope scope(contextId);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->PostTask([contextId, uiTask = std::move(uiTask)]() {
        ContainerScope scope(contextId);
        uiTask();
        }, TaskExecutor::TaskType::UI, "ArkUISyncUITask", PriorityType::IMMEDIATE);
}

bool MultiThreadBuildManager::PostUITaskAndWait(int32_t contextId, std::function<void()>&& uiTask)
{
    ContainerScope scope(contextId);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->PostSyncTask([contextId, uiTask = std::move(uiTask)]() {
        ContainerScope scope(contextId);
        uiTask();
        }, TaskExecutor::TaskType::UI, "ArkUISyncTaskAndWait", PriorityType::IMMEDIATE);
}
} // namespace OHOS::Ace