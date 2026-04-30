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
    /**
     * @brief Register an instance for pre-freeze flush.
     * Called in UIContentImpl::Foreground() on the UI thread.
     * Also attempts to register the externalClearCallback to NativeEngine via TryRegisterExternalClearCallback().
     * @param instanceId The instance ID to register.
     */
    void RegisterPreFreezeInstance(int32_t instanceId);

    /**
     * @brief Unregister an instance from pre-freeze flush.
     * Called in UIContentImpl::Background() on the UI thread.
     * Removes the instanceId from registeredInstances_ so ForceFlushVsync won't be called for it.
     * @param instanceId The instance ID to unregister.
     */
    void UnregisterPreFreezeInstance(int32_t instanceId);

    /**
     * @brief Static callback registered to NativeEngine::SetExternalClearCallback.
     * Called by ArkIdleMonitor::NotifyNeedFreeze before ReportDataToRSS(true) to flush rendering commands.
     * Takes a snapshot of registeredInstances_ to avoid holding lock during iteration.
     * For each registered instanceId, posts a VIP-priority PostSyncTask to call ForceFlushVsync.
     * Logs warning if any flush takes longer than 50ms.
     */
    static void PreFreezeFlushForAllContexts();

private:
    static void FlushInstance(uint64_t nanoTimestamp, int32_t instanceId);

    /**
     * @brief Try to register ExternalClearCallback to NativeEngine once per process.
     * Uses bool flag + mutex instead of std::call_once because EngineHelper::GetCurrentEngine()
     * may return nullptr on first call. Subsequent calls will retry until engine becomes available.
     * Early returns if: externalClearRegistered_ is true, engine is null, or nativeEngine is null.
     * Called under registeredMutex_ protection from RegisterPreFreezeInstance.
     */
    void TryRegisterExternalClearCallback();

    std::mutex mutex_;
    std::unordered_set<Rosen::RSUIContext*> rsUIContexts_;
    RefPtr<TaskRunnerAdapter> taskExecutor_ = TaskRunnerAdapterFactory::Create(false, "");

    std::mutex registeredMutex_;
    std::unordered_set<int32_t> registeredInstances_;
    bool externalClearRegistered_ = false;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ROSEN_DETACHED_RS_NODE_MANAGER_H
