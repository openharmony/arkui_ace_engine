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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_MANAGER_H

#include <atomic>
#include <cstdint>
#include <deque>
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_predictor.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_types.h"

namespace OHOS::Ace::NG {

class FrameNode;
class PipelineContext;

/**
 * FEAT-005 (P-01/P-05/P-06): per-pipeline scroll placeholder coordinator.
 *
 * One instance per PipelineContext gives Container/VM-level isolation of the
 * template registry, containers, cost statistics and the UI-thread real-build
 * queue. The accepted design (Option A) centralizes:
 *   - template registry with atomic generation publishing (same id re-register
 *     publishes a new template generation; older results must not mount);
 *   - container registry (List/Grid/WaterFlow hosts with providers);
 *   - per-template EWMA cost statistics + remaining-budget decision;
 *   - placeholder node creation (default layout-only fallback or template);
 *   - the UI-thread frame-splitting real-build queue with generation checks
 *     (five generation kinds: container / data / item / template / task).
 *
 * Threading contract (draft):
 *   - RegisterTemplate() may be called from any thread (mutex-protected);
 *   - all other entry points are UI-thread only, matching the existing layout
 *     and flush paths that call into the manager;
 *   - real business builders always execute on the UI thread (hard rule of the
 *     feature); placeholder template preparation may later be moved to a worker
 *     pool behind PreparePlaceholderTemplate() (see P-05), the draft keeps it
 *     on the UI thread behind a switch to stay within thread-safety PoC scope.
 */
class ACE_EXPORT ScrollPlaceholderManager : public AceType {
    DECLARE_ACE_TYPE(ScrollPlaceholderManager, AceType);

public:
    explicit ScrollPlaceholderManager(const WeakPtr<PipelineContext>& context);
    ~ScrollPlaceholderManager() override = default;

    // ---- Template registry (SR-07 / P-05) ----

    /**
     * Registers (or atomically re-publishes) a placeholder template under [id].
     * Re-registering bumps the template generation: in-flight tasks carrying an
     * older generation are rejected at commit time. Returns the generation.
     */
    uint64_t RegisterTemplate(const std::string& id, ScrollPlaceholderBuilder&& builder);
    void UnregisterTemplate(const std::string& id);

    /** True when [id] is registered (used for fallback-to-default diagnostics). */
    bool HasTemplate(const std::string& id) const;

    /** Current generation of a template id (0 when unregistered); used at commit sites. */
    uint64_t GetTemplateGeneration(const std::string& id) const;

    // ---- Container registry (SR-01/SR-03/SR-04) ----

    /**
     * Registers a scroll container (List/Grid/WaterFlow host) that has the
     * scrollPlaceholder attribute set. [itemFactory] creates the container's
     * item shell (ListItem/GridItem/FlowItem) for placeholders.
     */
    void RegisterContainer(const WeakPtr<FrameNode>& host, ScrollPlaceholderProvider&& provider,
        ScrollPlaceholderItemFactory&& itemFactory);
    void UnregisterContainer(int32_t hostId);
    bool IsContainerRegistered(int32_t hostId) const;

    /** Bumps the data generation of a container: pending results become stale. */
    void NotifyDataChanged(int32_t hostId);

    /** Current generation snapshot of a container (zeros when unknown). */
    ScrollPlaceholderGeneration GetContainerGeneration(int32_t hostId) const;

    /** Weak host node of a registered container (null when unknown). */
    WeakPtr<FrameNode> GetRegisteredHost(int32_t hostId) const;

    // ---- Prediction (SR-01 / P-01) ----

    /** Records a real item build duration for cost prediction. */
    void RecordBuildCost(int32_t hostId, const std::string& templateKey, int64_t durationNs);

    /**
     * Decides whether the real build of item [index] on container [hostId]
     * should be deferred. Returns nullopt when the container is not
     * placeholder-enabled (opt-in rule) or cannot defer.
     */
    std::optional<ScrollPlaceholderDecision> DecideItemBuild(int32_t hostId, int32_t index);

    /** Remaining frame budget in ns, derived from vsync receive time and refresh rate. */
    int64_t GetRemainingFrameBudgetNs() const;

    // ---- Placeholder creation (P-05) ----

    /** Placeholder item creation result. */
    struct PlaceholderItem {
        /** Item shell (ListItem/GridItem/FlowItem) with the visual subtree attached. */
        RefPtr<FrameNode> node;
        /** Resolved template id; empty for the default placeholder. */
        std::string templateId;
        /** Cost-statistics key for this placeholder (template id or per-container default). */
        std::string templateKey;
    };

    /**
     * Creates the placeholder node for [index] on container [hostId]:
     * item shell from the container's factory + visual subtree from the
     * template (cloned from the immutable snapshot) or the default
     * layout-only fallback. Returns a null node when the container is unknown.
     */
    PlaceholderItem CreatePlaceholderItem(int32_t hostId, int32_t index);

    // ---- Real-build queue (P-06) ----

    /**
     * Body of a real-build task. Executed on the UI thread by
     * FlushRealBuildTasks(). Implementations must build the real item and swap
     * the placeholder only after re-validating generations, then report the
     * outcome (and the build duration) for diagnostics.
     */
    using RealBuildTaskBody = std::function<ScrollPlaceholderCommitResult(int64_t& buildDurationNs)>;

    /**
     * Enqueues a deferred real build. [body] runs on the UI thread inside the
     * per-frame flush when the token is still valid. [gen] is the generation
     * snapshot captured when the decision was made.
     */
    void EnqueueRealBuild(int32_t hostId, int32_t index, const ScrollPlaceholderGeneration& gen,
        RealBuildTaskBody&& body);

    /**
     * Drains the real-build queue for the current frame, bounded by
     * [deadlineNs] (absolute, GetSysTimestamp based). Called from the pipeline
     * vsync flush on the UI thread. Tasks exceeding the deadline are kept for
     * the next frame; stale/cancelled tasks are dropped with diagnostics.
     */
    void FlushRealBuildTasks(int64_t deadlineNs);

    /** Cancels all pending tasks of a container (container about to be destroyed). */
    void CancelContainerTasks(int32_t hostId);

    /** True when no real-build task is pending for the container. */
    bool HasPendingRealBuild(int32_t hostId) const;

    // ---- Layout-algorithm integration (List/Grid/WaterFlow deadline points) ----

    /**
     * Whether a layout loop that hit its response deadline may keep going with
     * placeholder items instead of deferring the whole tail to the next frame.
     * Bounded by a per-frame placeholder cap so a fast fling cannot turn into
     * an unbounded layout pass.
     */
    bool ShouldContinuePlaceholderLayout(int32_t hostId);
    /** Per-frame bookkeeping: called at the start of every flush. */
    void OnFrameStart();

    // ---- Diagnostics (AC-13) ----

    struct Diagnostics {
        uint32_t placeholdersCreated = 0;
        uint32_t realBuildEnqueued = 0;
        uint32_t realBuildCommitted = 0;
        uint32_t staleDropped = 0;
        uint32_t cancelled = 0;
        uint32_t defaultFallbackUsed = 0;
    };
    const Diagnostics& GetDiagnostics() const
    {
        return diagnostics_;
    }

private:
    struct TemplateRecord {
        ScrollPlaceholderBuilder builder;
        uint64_t generation = 1;
    };
    struct ContainerRecord {
        WeakPtr<FrameNode> host;
        ScrollPlaceholderProvider provider;
        ScrollPlaceholderItemFactory itemFactory;
        uint64_t containerGen = 1;
        uint64_t dataGen = 1;
    };
    struct RealBuildTask {
        uint64_t taskId = 0;
        int32_t hostId = -1;
        int32_t index = -1;
        ScrollPlaceholderGeneration gen;
        RealBuildTaskBody body;
    };

    const ContainerRecord* FindContainer(int32_t hostId) const;
    ContainerRecord* FindContainerMutable(int32_t hostId);
    /** Resolves provider options for an index; counts fallback diagnostics. */
    ScrollPlaceholderOptions ResolveOptions(const ContainerRecord& container, int32_t index);
    RefPtr<UINode> BuildTemplateSnapshot(const std::string& id);
    void DropTask(std::deque<RealBuildTask>::iterator& it, ScrollPlaceholderCommitResult reason);

    static constexpr int32_t MAX_REAL_BUILD_PER_FRAME = 8;
    static constexpr int32_t MAX_PLACEHOLDER_PER_FRAME = 32;
    static constexpr int32_t MAX_PENDING_PER_CONTAINER = 256;

    WeakPtr<PipelineContext> context_;
    // Template registry: registration may arrive off the UI thread, guard it.
    mutable std::mutex templateMutex_;
    std::unordered_map<std::string, TemplateRecord> templates_;
    uint64_t nextTemplateGeneration_ = 1;
    // Container registry & queue: UI thread only (documented contract).
    std::unordered_map<int32_t, ContainerRecord> containers_;
    std::deque<RealBuildTask> pendingTasks_;
    uint64_t nextTaskId_ = 1;
    ScrollPlaceholderPredictor predictor_;
    Diagnostics diagnostics_;
    int32_t placeholdersThisFrame_ = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_MANAGER_H
