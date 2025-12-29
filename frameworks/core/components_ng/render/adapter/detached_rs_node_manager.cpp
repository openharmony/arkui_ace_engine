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

#include "base/utils/utils.h"

namespace OHOS::Ace {
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
} // namespace OHOS::Ace
