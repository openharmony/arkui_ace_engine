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

#include <mutex>
#include <unordered_set>

#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Rosen {
class RSUIContext;
class RSNode;
} // namespace OHOS::Rosen

namespace OHOS::Ace {

class ACE_FORCE_EXPORT DetachedRsNodeManager final {
public:
    static DetachedRsNodeManager& GetInstance()
    {
        static DetachedRsNodeManager instance_;
        return instance_;
    }

    /**
     * @brief Only when the rsNode will be deconstructed with its rsUIContext has been detached form pipeline, post a
     * task to triggger FlushImplicitTransaction and sendCommand to RS.
     * @param rsNode The rsNode will be deconstructed.
     */
    void PostDestructorTask(std::shared_ptr<Rosen::RSNode> rsNode);
    void FlushImplicitTransaction(std::shared_ptr<Rosen::RSUIContext> rsUIContext);
    void RemoveRSUIContext(std::shared_ptr<Rosen::RSUIContext> rsUIContext);

private:
    std::mutex mutex_;
    std::unordered_set<Rosen::RSUIContext*> rsUIContexts_;
    RefPtr<TaskRunnerAdapter> taskExecutor_ = TaskRunnerAdapterFactory::Create(false, "");
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ROSEN_DETACHED_RS_NODE_MANAGER_H
