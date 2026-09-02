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

#include <array>
#include <atomic>
#include <cstdint>
#include <deque>
#include <functional>
#include <string>

#include "base/memory/ace_type.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_cost_model.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_template_registry.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_types.h"

namespace OHOS::Ace::NG {

class PipelineContext;

// Prediction request for one real item about to be created inside a scroll container.
struct ScrollPlaceholderPredictParams {
    ScrollPlaceholderComponentType componentType = ScrollPlaceholderComponentType::LIST;
    // Placeholder template the item falls back to; empty means the default placeholder bucket.
    std::string templateId;
    int32_t hostNodeId = -1;
    int32_t index = -1;
    // True when the build is requested by the cache/preload path instead of the visible layout.
    bool cacheBuild = false;
};

// Prediction outcome, kept alongside the inputs of the decision for trace/diagnostics.
struct ScrollPlaceholderPredictResult {
    ScrollPlaceholderDecision decision = ScrollPlaceholderDecision::BUILD_REAL_NOW;
    int64_t estimateNs = 0;
    int64_t remainingBudgetNs = 0;
    // False when no frame anchor was available yet; the decision then keeps the legacy path
    // and must not be read as a budget-based suggestion.
    bool budgetAvailable = false;
};

// Per pipeline scroll placeholder scheduler core (design ADR-1/ADR-4/ADR-6/ADR-9):
// - lazy created by PipelineContext, isolated per container instance;
// - predicts, before the real builder runs, whether the estimated item build cost fits the
//   remaining frame budget anchored to the current vsync period;
// - owns the UI-thread framed real-build queue: priority ordered, budget checked before each
//   item, requeue + request frame once the next estimate exceeds the remaining budget;
// - template registry lifecycle (register/unregister/query + instance LRU) and diagnostics
//   counters are surfaced through this facade.
// Threading: created, called and destroyed on the UI thread only.
class ScrollPlaceholderManager : public virtual AceType {
    DECLARE_ACE_TYPE(ScrollPlaceholderManager, AceType);

public:
    explicit ScrollPlaceholderManager(int32_t instanceId);
    ~ScrollPlaceholderManager() override = default;

    void SetPipelineContext(const WeakPtr<PipelineContext>& pipeline);
    // Frame anchor pushed from PipelineContext::FlushVsync; period <= 0 falls back to 60Hz.
    void NotifyVsync(int64_t vsyncTimestampNs, int64_t vsyncPeriodNs);

    // Template registry facade.
    uint64_t RegisterTemplate(const std::string& templateId, ScrollPlaceholderBuilder&& builder);
    bool UnregisterTemplate(const std::string& templateId);
    bool IsTemplateRegistered(const std::string& templateId) const;
    std::optional<ScrollPlaceholderTemplateSnapshot> LookupTemplateForCreate(const std::string& templateId);
    void CacheTemplateInstance(const std::string& templateId, const RefPtr<UINode>& instance);
    RefPtr<UINode> AcquireTemplateInstance(const std::string& templateId);
    size_t GetCachedInstanceCount(const std::string& templateId) const;
    size_t GetHotTemplateCount() const;

    // Prediction core.
    ScrollPlaceholderPredictResult Predict(const ScrollPlaceholderPredictParams& params, int64_t frameDeadlineNs) const;
    int64_t EstimateRealBuildDuration(const ScrollPlaceholderPredictParams& params) const;
    int64_t GetRemainingFrameBudgetNs(int64_t frameDeadlineNs) const;
    int64_t GetVsyncDerivedFrameDeadlineNs() const;
    void RecordRealBuildDuration(const ScrollPlaceholderPredictParams& params, int64_t durationNs);

    // Framed real-build queue. The task runs on the UI thread and returns whether the real
    // item was built and committed; its wall duration is sampled into the cost model.
    using RealBuildTaskFunc = std::function<bool()>;
    void EnqueueRealBuild(const ScrollPlaceholderPredictParams& params, uint64_t templateGeneration,
        RealBuildTaskFunc&& task, ScrollPlaceholderRealBuildPriority priority);
    void FlushRealBuild(int64_t deadlineNs);
    bool HasPendingRealBuild() const;
    size_t GetPendingRealBuildCount() const;
    void CancelHostRealBuilds(int32_t hostNodeId, ScrollPlaceholderCancelReason reason);

    // Lifecycle.
    void Destroy();
    bool IsDestroyed() const;

    // Observation hooks for scroll container item builds (no behavior impact: the real item
    // is still built synchronously; these only sample its cost and let the prediction say,
    // per frame, how many items it would have built now and how many it would defer to
    // placeholders once the feature is enabled by the component adapters).
    ScrollPlaceholderPredictResult NotifyRealBuildStart(const ScrollPlaceholderPredictParams& params);
    void NotifyRealBuildEnd(const ScrollPlaceholderPredictParams& params, int64_t buildStartNs);

    // Aggregated observation of the frame closed by the most recent NotifyVsync.
    struct FrameObservationStats {
        uint32_t observedBuilds = 0;
        uint32_t suggestedReal = 0;
        uint32_t suggestedPlaceholder = 0;
        int64_t totalBuildNs = 0;
        int64_t maxBuildNs = 0;
        int64_t lastRemainingBudgetNs = 0;
    };
    FrameObservationStats GetLastFrameObservation(ScrollPlaceholderComponentType componentType) const;

    // Diagnostics counters (relaxed atomics, snapshot copy for dump/trace).
    static constexpr size_t CANCEL_REASON_COUNT = 8;
    static constexpr size_t COMPONENT_TYPE_COUNT = 3;
    struct Diagnostics {
        uint64_t predictBuildRealNow = 0;
        uint64_t predictUsePlaceholder = 0;
        uint64_t realBuildExecuted = 0;
        uint64_t realBuildRequeued = 0;
        uint64_t realBuildDropped = 0;
        uint64_t registerRejected = 0;
        uint64_t lruEvictedTemplates = 0;
        uint64_t flushRounds = 0;
        uint64_t requestFrameCount = 0;
        uint64_t observedRealBuilds = 0;
        std::array<uint64_t, CANCEL_REASON_COUNT> cancelledByReason = {};
    };
    Diagnostics GetDiagnostics() const;

private:
    struct RealBuildTask {
        ScrollPlaceholderPredictParams params;
        uint64_t templateGeneration = 0;
        uint64_t sequence = 0;
        ScrollPlaceholderRealBuildPriority priority = ScrollPlaceholderRealBuildPriority::VISIBLE;
        RealBuildTaskFunc task;
    };

    ScrollPlaceholderPredictResult PredictCore(const ScrollPlaceholderPredictParams& params, int64_t frameDeadlineNs) const;
    void CloseObservationFrame(int64_t vsyncTimestampNs);
    static size_t ComponentIndex(ScrollPlaceholderComponentType componentType);

    void RequestFrameIfAlive();
    void PurgeTemplateRealBuilds(const std::string& templateId, ScrollPlaceholderCancelReason reason);

    int32_t instanceId_ = -1;
    WeakPtr<PipelineContext> pipeline_;
    ScrollPlaceholderCostModel costModel_;
    ScrollPlaceholderTemplateRegistry registry_;
    std::deque<RealBuildTask> pendingRealBuilds_;
    uint64_t nextTaskSequence_ = 0;
    int64_t lastVsyncTimestampNs_ = 0;
    int64_t vsyncPeriodNs_ = 0;
    bool frameAnchored_ = false;
    std::atomic<bool> destroyed_ = false;
    std::array<FrameObservationStats, COMPONENT_TYPE_COUNT> frameStats_;
    std::array<FrameObservationStats, COMPONENT_TYPE_COUNT> lastFrameStats_;

    mutable std::atomic<uint64_t> predictBuildRealNow_ = 0;
    mutable std::atomic<uint64_t> predictUsePlaceholder_ = 0;
    mutable std::atomic<uint64_t> realBuildExecuted_ = 0;
    mutable std::atomic<uint64_t> realBuildRequeued_ = 0;
    mutable std::atomic<uint64_t> realBuildDropped_ = 0;
    mutable std::atomic<uint64_t> registerRejected_ = 0;
    mutable std::atomic<uint64_t> flushRounds_ = 0;
    mutable std::atomic<uint64_t> requestFrameCount_ = 0;
    mutable std::atomic<uint64_t> observedRealBuilds_ = 0;
    mutable std::array<std::atomic<uint64_t>, CANCEL_REASON_COUNT> cancelledByReason_ = {};
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_MANAGER_H
