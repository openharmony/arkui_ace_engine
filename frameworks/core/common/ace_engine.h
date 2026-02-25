/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ACE_ENGINE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ACE_ENGINE_H

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"
#include "core/common/frontend.h"
#include "core/common/watch_dog.h"
#include "core/common/window.h"

namespace OHOS::Ace {

class AcePage;

// Cache information for destroyed UIContext instances to enhance error messages
// when ContainerScope fails to find a valid instanceId. This helps developers
// identify which instance was destroyed and when, improving debugging experience.
struct UIContextCacheInfo {
    int32_t instanceId_ = -1;      // The instance ID of the destroyed container
    int64_t createTime_;           // Container creation timestamp (for error messages)
    int64_t destroyTime_;          // Container destruction timestamp
    int32_t windowId_ = -1;        // Associated window ID
    std::string windowName_ = "";  // Associated window name
    std::string ToString() const;  // Format cache info as string for logging
};

class ACE_FORCE_EXPORT AceEngine {
public:
    ~AceEngine();

    void AddContainer(int32_t instanceId, const RefPtr<Container>& container);
    void RemoveContainer(int32_t instanceId);
    RefPtr<Container> GetContainer(int32_t instanceId);
    void RegisterToWatchDog(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor, bool useUIAsJSThread = false);
    void UnRegisterFromWatchDog(int32_t instanceId);
    void BuriedBomb(int32_t instanceId, uint64_t bombId);
    void DefusingBomb(int32_t instanceId);
    static AceEngine& Get();
    static void InitJsDumpHeadSignal();
    void DumpJsHeap(bool isPrivate) const;
    void DestroyHeapProfiler() const;
    void ForceFullGC() const;

    void TriggerGarbageCollection();
    void NotifyContainers(const std::function<void(const RefPtr<Container>&)>& callback);
    void NotifyContainersOrderly(const std::function<void(const RefPtr<Container>&)>& callback);
    bool HasContainer(int32_t containerId) const;

    // Get cached information about a destroyed UIContext by instanceId
    // Returns formatted string with instance details or "not found" message
    std::string GetDestroyedUIContextInfo(int32_t instanceId) const;

    // Build enhanced error message when ContainerScope fails to find a valid instance
    // Combines instanceId, reason description, and cached destroyed context info
    static std::string GetEnhancedContextBNotFoundMessage(InstanceIdGenReason reason, int32_t instanceId = -1);
private:
    AceEngine();

    mutable std::shared_mutex mutex_;
    std::unordered_map<int32_t, RefPtr<Container>> containerMap_;
    // Cache for destroyed UIContext information to enhance error messages
    // Stores up to MAX_DESTROYED_CACHE_SIZE (10) most recently destroyed instances
    std::unordered_map<int32_t, UIContextCacheInfo> destroyedUIContextCache_;
    RefPtr<WatchDog> watchDog_;
    ACE_DISALLOW_COPY_AND_MOVE(AceEngine);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ACE_ENGINE_H
