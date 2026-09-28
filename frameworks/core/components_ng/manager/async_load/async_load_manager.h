/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_ASYNC_LOAD_ASYNC_LOAD_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_ASYNC_LOAD_ASYNC_LOAD_MANAGER_H

#include <cstdint>
#include <functional>
#include <list>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/async_load_config.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {

class PipelineContext;

/**
 * Scheduler for custom components that enabled asynchronous loading.
 *
 * Owned by PipelineContext and created lazily through
 * PipelineContext::GetOrCreateAsyncLoadManager(), the same pattern as
 * ScrollPlaceholderManager. Applications that never call enableAsyncLoad do not
 * create an instance, so the existing synchronous path keeps zero overhead.
 *
 * All state is UI-thread only: no locks, no atomics. "Asynchronous" here means
 * the timing is deferred, not that work moves to another thread.
 */
class ACE_FORCE_EXPORT AsyncLoadManager : public virtual AceType {
    DECLARE_ACE_TYPE(AsyncLoadManager, AceType);

public:
    // Timeout threshold applied when the caller did not specify one (spec AC-1.2).
    static constexpr int32_t DEFAULT_TIMEOUT_MS = 1000;
    // Upper bound of components force-loaded within a single frame (design D2).
    // Kept as an internal constant; it is deliberately not exposed through the API.
    static constexpr int32_t FORCE_LOAD_LIMIT_PER_FRAME = 4;

    // Performs the component's own deferred build. Supplied by CustomNode at
    // registration time so this manager stays free of node-construction details.
    using ForceLoadCallback = std::function<void()>;

    explicit AsyncLoadManager(int32_t instanceId);
    ~AsyncLoadManager() override = default;

    void SetPipelineContext(const WeakPtr<PipelineContext>& pipeline);

    /**
     * Enqueues a component that enabled asynchronous loading. Called from the
     * component's mount path. A node that is already tracked is replaced, so a
     * repeated mount does not leak an entry.
     */
    void Register(int32_t nodeId, const AsyncLoadConfig& config, ForceLoadCallback forceLoad);

    /**
     * Marks the component's build as finished. Removes the entry without
     * force-loading it. Safe to call for untracked nodes.
     */
    void OnLoaded(int32_t nodeId);

    /**
     * Removes the entry on component destruction. Every destruction path must
     * reach this, otherwise the queue keeps a dangling entry (state invariant).
     */
    void OnNodeDestroyed(int32_t nodeId);

    /**
     * Drains expired entries, at most FORCE_LOAD_LIMIT_PER_FRAME per call, so a
     * burst of timeouts cannot itself become a dropped-frame source.
     */
    void OnVsync(int64_t nanoTimestamp, int64_t vsyncPeriod);

    /**
     * Obtains the placeholder node for a configuration, reusing the template registry that
     * ScrollPlaceholderManager already exposes. Returns null in both "not configured" and
     * "configured but empty/unregistered id" cases: neither falls back to a system default
     * placeholder here, which intentionally differs from the scroll-placeholder semantics.
     */
    RefPtr<UINode> CreatePlaceholder(const AsyncLoadConfig& config);

    /**
     * Detaches a placeholder once the real content has been mounted. The content is mounted
     * before this runs, so the swap never crosses a frame boundary even though the two calls
     * are separate. The host is passed explicitly because removal goes through the parent
     * (UINode::RemoveChild).
     */
    void DetachPlaceholder(const RefPtr<UINode>& host, const RefPtr<UINode>& placeholder);

    // Test seams.
    size_t GetPendingCount() const
    {
        return pendingQueue_.size();
    }
    size_t GetExpiredCount() const;

private:
    struct Entry {
        int32_t nodeId = -1;
        AsyncLoadConfig config;
        ForceLoadCallback forceLoad;
        bool expired = false;
        // Guards the delayed task: a timed-out callback whose entry was already
        // removed (loaded or destroyed) must not resurrect it.
        uint64_t generation = 0;
    };

    void ScheduleTimeout(Entry& entry);
    void MarkExpired(int32_t nodeId, uint64_t generation);
    void EraseEntry(int32_t nodeId);

    int32_t instanceId_ = -1;
    WeakPtr<PipelineContext> pipeline_;
    // Insertion-ordered: force-loading drains from the front, which gives the
    // enqueue-order policy the spec leaves undefined a concrete meaning.
    std::list<Entry> pendingQueue_;
    uint64_t nextGeneration_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(AsyncLoadManager);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_ASYNC_LOAD_ASYNC_LOAD_MANAGER_H
