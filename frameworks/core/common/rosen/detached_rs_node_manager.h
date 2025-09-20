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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ROSEN_DETACHED_RS_NODE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ROSEN_DETACHED_RS_NODE_MANAGER_H

#include <memory>
#include <mutex>

#include "render_service_client/core/ui/rs_node.h"
#include "render_service_client/core/ui/rs_ui_context.h"

#include "base/utils/utils.h"
#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT DetachedRsNodeManager final {
public:
    static DetachedRsNodeManager& GetInstance()
    {
        static DetachedRsNodeManager instance_;
        return instance_;
    }

    void PostDestructorTask(std::shared_ptr<Rosen::RSNode> rsNode)
    {
        CHECK_NULL_VOID(rsNode);
        auto rsUIContext = rsNode->GetRSUIContext();
        CHECK_NULL_VOID(rsUIContext);
        bool isDetached = rsUIContext->HasDetachedFromUI();
        CHECK_NULL_VOID(isDetached && taskExecutor_);
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

    void FlushImplicitTransaction(std::shared_ptr<Rosen::RSUIContext> rsUIContext)
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
        transition->FlushImplicitTransaction();
    }

    void RemoveRSUIContext(std::shared_ptr<Rosen::RSUIContext> rsUIContext)
    {
        CHECK_NULL_VOID(rsUIContext);
        std::lock_guard<std::mutex> lock(mutex_);
        rsUIContexts_.erase(rsUIContext.get());
    }

private:
    std::mutex mutex_;
    std::unordered_set<Rosen::RSUIContext*> rsUIContexts_;
    RefPtr<TaskRunnerAdapter> taskExecutor_ = TaskRunnerAdapterFactory::Create(false, "");
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ROSEN_DETACHED_RS_NODE_MANAGER_H
