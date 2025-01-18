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

#include "core/common/render_boundary_manager.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
void RenderBoundaryManager::PostTaskRenderBoundary(bool isDebugBoundary, const RefPtr<Container>& container)
{
    std::lock_guard<std::mutex> lock(renderLayoutBoundaryTaskMutex_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (!renderLayoutBoundaryTaskQueue_.empty() && !ResetTaskQueue(isDebugBoundary)) {
        return;
    }

    RenderLayoutBoundaryTask renderTask;
    renderTask.target = isDebugBoundary;
    renderTask.updateTask.Reset(
        [containerWeak = WeakPtr<Container>(container), isDebugBoundary, weak = WeakClaim(this)]() {
            ACE_SCOPED_TRACE("PostTaskRenderBoundary");
            auto renderBoundaryManager = weak.Upgrade();
            CHECK_NULL_VOID(renderBoundaryManager);
            auto container = containerWeak.Upgrade();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
            CHECK_NULL_VOID(ngPipeline);
            auto rootNode = ngPipeline->GetRootElement();
            CHECK_NULL_VOID(rootNode);
            rootNode->PaintDebugBoundaryTreeAll(isDebugBoundary);
            ngPipeline->RequestFrame();
            renderBoundaryManager->RemoveCurrentRenderBoundaryTask();
        });
    renderLayoutBoundaryTaskQueue_.push_back(renderTask);
    taskExecutor->PostTask(renderLayoutBoundaryTaskQueue_.back().updateTask, TaskExecutor::TaskType::UI,
        "ArkUIRenderLayoutBoundary", TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

bool RenderBoundaryManager::ResetTaskQueue(bool isDebugBoundary)
{
    if (renderLayoutBoundaryTaskQueue_.front().target == isDebugBoundary) {
        while (renderLayoutBoundaryTaskQueue_.size() > 1) {
            if (!renderLayoutBoundaryTaskQueue_.back().updateTask.Cancel()) {
                break;
            }
            if (!renderLayoutBoundaryTaskQueue_.empty()) {
                renderLayoutBoundaryTaskQueue_.pop_back();
            }
        }
        if (renderLayoutBoundaryTaskQueue_.size() == 1) {
            return false;
        }
    } else if (renderLayoutBoundaryTaskQueue_.front().updateTask.Cancel()) {
        if (!renderLayoutBoundaryTaskQueue_.empty()) {
            renderLayoutBoundaryTaskQueue_.pop_front();
        }
    }
    return true;
}

void RenderBoundaryManager::RemoveCurrentRenderBoundaryTask()
{
    std::lock_guard<std::mutex> lock(renderLayoutBoundaryTaskMutex_);
    if (!renderLayoutBoundaryTaskQueue_.empty()) {
        renderLayoutBoundaryTaskQueue_.pop_front();
    }
}
} // namespace OHOS::Ace

