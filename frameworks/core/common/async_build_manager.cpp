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

#include "core/common/async_build_manager.h"

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
std::unique_ptr<ffrt::queue> aysncUITaskQueue = nullptr;
#endif
}
thread_local bool AsyncBuildManager::isBuildingMultiThreadNode_ = false;
thread_local bool AsyncBuildManager::isMainThread_ = false;

AsyncBuildManager& AsyncBuildManager::GetInstance()
{
    static AsyncBuildManager AsyncBuildManager;
    return AsyncBuildManager;
}

AsyncBuildManager::AsyncBuildManager()
{
    InitAysncUITaskQueue();
}

void AsyncBuildManager::InitAysncUITaskQueue()
{
#ifdef FFRT_SUPPORT
    aysncUITaskQueue = std::make_unique<ffrt::queue>(ffrt::queue_concurrent,
        "ArkUIAsyncUITask", ffrt::queue_attr().max_concurrency(MAX_THREAD_NUM));
#endif
}

bool AsyncBuildManager::IsOnMainThread()
{
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI);
}

bool AsyncBuildManager::CheckOnMainThread()
{
    if (!IsOnMainThread()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "CheckOnMainThread failed");
        return false;
    }
    return true;
}

bool AsyncBuildManager::CheckOperateValid(NG::UINode* node)
{
    if (!node) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "CheckOperateValid failed. node is nullptr");
        return false;
    }
    auto uiNode = AceType::Claim(node);
    if (!uiNode->IsMultiThreadNode() && !AsyncBuildManager::IsOnMainThread()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "CheckOperateValid failed. not multi thread node not run on main thread");
        return false;
    }
    if (uiNode->IsMultiThreadNode() && uiNode->IsOnMainTree() && !AsyncBuildManager::IsOnMainThread()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE,
            "CheckOperateValid failed. multi thread node attached to main tree not run on main thread");
        return false;
    }
    return true;
}

bool AsyncBuildManager::AllowNotifyToNode(const RefPtr<NG::UINode>& node)
{
    return node && (!node->IsMultiThreadNode() || node->IsOnMainTree());
}

void AsyncBuildManager::SetBuildingMultiThreadNode(bool isBuildingMultiThreadNode)
{
    isBuildingMultiThreadNode_ = isBuildingMultiThreadNode;
}

bool AsyncBuildManager::IsBuildingMultiThreadNode()
{
    return isBuildingMultiThreadNode_;
}

bool AsyncBuildManager::IsMultiThreadAPIOnSubThread()
{
    return IsBuildingMultiThreadNode() && !IsOnMainThread();
}

bool AsyncBuildManager::NeedPostUnSafeTask(const RefPtr<NG::UINode>& node)
{
    return IsBuildingMultiThreadNode() && node && node->IsMultiThreadNode() && !node->IsOnMainTree();
}

void AsyncBuildManager::TryExecuteUnSafeTask(const RefPtr<NG::UINode>& node, const std::function<void()>& task)
{
    if (NeedPostUnSafeTask(node)) {
        PostAfterAttachMainTreeTask(node, task);
    } else {
        task();
    }
}

bool AsyncBuildManager::TryPostUnSafeTask(const RefPtr<NG::UINode>& node, const std::function<void()>& task)
{
    if (NeedPostUnSafeTask(node)) {
        PostAfterAttachMainTreeTask(node, task);
        return true;
    }
    return false;
}

void AsyncBuildManager::PostAfterAttachMainTreeTask(const RefPtr<NG::UINode>& node, const std::function<void()>& task)
{
    ACE_SCOPED_TRACE("PostAfterAttachMainTreeTask %d", node->GetId());
    if (node->IsOnMainTree()) {
        return;
    }
    std::lock_guard<std::mutex> lock(taskMutex_);
    AfterAttachMainTreeTask afterAttachMainTreeTask = { Container::CurrentIdSafelyWithCheck(), task };
    auto iter = afterAttachMainTreeTasks_.find(node->GetId());
    if (iter != afterAttachMainTreeTasks_.end()) {
        iter->second.emplace_back(std::move(afterAttachMainTreeTask));
    } else {
        std::vector<AfterAttachMainTreeTask> tasks;
        tasks.emplace_back(std::move(afterAttachMainTreeTask));
        afterAttachMainTreeTasks_[node->GetId()] = std::move(tasks);
    }
}

void AsyncBuildManager::RemoveAfterAttachMainTreeTasks(int32_t nodeId)
{
    std::lock_guard<std::mutex> lock(taskMutex_);
    afterAttachMainTreeTasks_.erase(nodeId);
}

void AsyncBuildManager::ExecuteAfterAttachMainTreeTasks(int32_t nodeId)
{
    std::vector<AfterAttachMainTreeTask> tasks;
    {
        std::lock_guard<std::mutex> lock(taskMutex_);
        auto iter = afterAttachMainTreeTasks_.find(nodeId);
        if (iter == afterAttachMainTreeTasks_.end()) {
            return;
        }
        tasks.swap(iter->second);
        afterAttachMainTreeTasks_.erase(nodeId);
    }
    for (auto& task : tasks) {
        ACE_SCOPED_TRACE("ExecuteAfterAttachMainTreeTask %d", nodeId);
        ContainerScope scope(task.containerId);
        task.taskFunc();
    }
}

bool AsyncBuildManager::PostAsyncUITask(int32_t contextId, const std::function<void()>& asyncUITask,
    const std::function<void()>& onFinishTask)
{
#ifdef FFRT_SUPPORT
    if (!aysncUITaskQueue) {
        return false;
    }
    auto result = aysncUITaskQueue->submit_h([contextId,
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
            }, TaskExecutor::TaskType::UI, "ArkUIAsyncUIOnFinishTask");
    }, ffrt::task_attr().name("ArkUIAsyncUITask").qos(ASYNC_UITASK_QOS));
    return result != nullptr;
#else
    return false;
#endif
}

bool AsyncBuildManager::PostUITask(int32_t contextId, const std::function<void()>& uiTask)
{
    ContainerScope scope(contextId);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->PostTask([contextId, uiTask = std::move(uiTask)]() {
        ContainerScope scope(contextId);
        uiTask();
        }, TaskExecutor::TaskType::UI, "ArkUISyncUITask");
}
} // namespace OHOS::Ace