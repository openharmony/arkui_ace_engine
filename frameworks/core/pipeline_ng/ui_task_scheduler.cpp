/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/pipeline_ng/ui_task_scheduler.h"

#include <memory>

#include "base/thread/background_task_executor.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

std::unique_ptr<UiTaskScheduler> UiTaskScheduler::instance_ = nullptr;

std::mutex UiTaskScheduler::mutex_ = std::mutex();

UiTaskScheduler* UiTaskScheduler::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lockGuard(mutex_);
        if (!instance_) {
            instance_.reset(new UiTaskScheduler);
        }
    }
    return instance_.get();
}

void UiTaskScheduler::AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty)
{
    CHECK_RUN_ON(JS);
    if (!dirty) {
        LOGW("dirty is null");
        return;
    }
    dirtyLayoutNodes_[dirty->GetRootId()][dirty->GetPageId()].emplace(dirty);
}

void UiTaskScheduler::AddDirtyRenderNode(const RefPtr<FrameNode>& dirty)
{
    CHECK_RUN_ON(JS);
    if (!dirty) {
        LOGW("dirty is null");
        return;
    }
    dirtyRenderNodes_[dirty->GetRootId()][dirty->GetPageId()].emplace(dirty);
}

// Called on Ui Thread.
void UiTaskScheduler::AddDirtyRenderNodeInUiThread(const RefPtr<FrameNode>& dirty)
{
    CHECK_RUN_ON(UI);
    if (!dirty) {
        LOGW("dirty is null");
        return;
    }
    dirtyRenderNodesInUI_[dirty->GetRootId()][dirty->GetPageId()].emplace(dirty);
}

void UiTaskScheduler::FlushLayoutTask()
{
    CHECK_RUN_ON(JS);
    LOGE("FlushLayoutTask");
    auto dirtyLayoutNodes = std::move(dirtyLayoutNodes_);
    // Priority task creation
    for (auto&& rootNodes : dirtyLayoutNodes) {
        std::list<std::shared_ptr<UiLayoutTask>> tasks;
        RefPtr<FrameNode> lastNode = nullptr;
        for (auto&& pageNodes : rootNodes.second) {
            for (auto&& node : pageNodes.second) {
                tasks.emplace_back(node->CreateUiLayoutTask());
                lastNode = node;
            }
        }
        if (lastNode) {
            lastNode->PostUiTask([tasks = std::move(tasks)]() {
                // Priority task exec.
                for (const auto& task : tasks) {
                    (*task)();
                }
            });
        }
    }
}

void UiTaskScheduler::FlushRenderTask()
{
    CHECK_RUN_ON(JS);
    LOGE("FlushRenderTask");
    auto dirtyRenderNodes = std::move(dirtyRenderNodes_);
    // Priority task creation
    for (auto&& rootNodes : dirtyRenderNodes) {
        std::list<std::shared_ptr<UiRenderTask>> tasks;
        RefPtr<FrameNode> lastNode = nullptr;
        for (auto&& pageNodes : rootNodes.second) {
            for (auto&& node : pageNodes.second) {
                tasks.emplace_back(node->CreateUiRenderTask());
                lastNode = node;
            }
        }
        if (lastNode) {
            lastNode->PostUiTask([tasks = std::move(tasks)]() {
                // Priority task exec.
                for (const auto& task : tasks) {
                    (*task)();
                }
            });
        }
    }
}

void UiTaskScheduler::FlushTask()
{
    CHECK_RUN_ON(JS);
    LOGE("FlushTask");
    FlushLayoutTask();
    FlushRenderTask();
}

void UiTaskScheduler::FlushRenderTaskInUiThread()
{
    CHECK_RUN_ON(UI);
    LOGE("FlushRenderTaskInUiThread");
    auto dirtyRenderNodesInUI = std::move(dirtyRenderNodesInUI_);
    // Priority task creation
    for (auto&& rootNodes : dirtyRenderNodesInUI) {
        std::list<std::shared_ptr<UiRenderTask>> tasks;
        for (auto&& pageNodes : rootNodes.second) {
            for (auto&& node : pageNodes.second) {
                tasks.emplace_back(node->CreateUiRenderTask());
            }
        }
        // Priority task exec.
        for (const auto& task : tasks) {
            (*task)();
        }
    }
}

} // namespace OHOS::Ace::NG
