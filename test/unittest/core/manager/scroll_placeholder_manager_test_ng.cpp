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

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "base/utils/time_util.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_cost_model.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_INSTANCE_ID = 100;
constexpr int64_t COLD_START_NS = 5000000; // 5ms
constexpr int64_t FRAME_120HZ_NS = 8333333;
constexpr int64_t LARGE_DURATION_NS = 50000000; // 50ms
constexpr int64_t SMALL_DURATION_NS = 500000;   // 0.5ms

ScrollPlaceholderPredictParams MakeParams(
    ScrollPlaceholderComponentType type, const std::string& templateId, int32_t hostNodeId, int32_t index)
{
    ScrollPlaceholderPredictParams params;
    params.componentType = type;
    params.templateId = templateId;
    params.hostNodeId = hostNodeId;
    params.index = index;
    return params;
}
} // namespace

class TestPlaceholderNode : public UINode {
    DECLARE_ACE_TYPE(TestPlaceholderNode, UINode);

public:
    static RefPtr<TestPlaceholderNode> CreateTestNode(int32_t nodeId)
    {
        return MakeRefPtr<TestPlaceholderNode>(nodeId);
    }

    explicit TestPlaceholderNode(int32_t nodeId) : UINode("TestPlaceholderNode", nodeId) {}

    bool IsAtomicNode() const override
    {
        return true;
    }
};

class ScrollPlaceholderManagerTestNg : public testing::Test {
public:
    void SetUp() override
    {
        manager_ = AceType::MakeRefPtr<ScrollPlaceholderManager>(TEST_INSTANCE_ID);
    }
    void TearDown() override
    {
        manager_ = nullptr;
    }

    RefPtr<ScrollPlaceholderManager> manager_;
};

/**
 * @tc.name: CostModelColdStartEstimate001
 * @tc.desc: Without any sample the estimate falls back to the cold start constant.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, CostModelColdStartEstimate001, TestSize.Level1)
{
    ScrollPlaceholderCostModel model;
    EXPECT_EQ(model.EstimateRealBuildDuration(ScrollPlaceholderComponentType::LIST, "tpl"), COLD_START_NS);
    EXPECT_EQ(model.EstimateRealBuildDuration(ScrollPlaceholderComponentType::GRID, std::string()), COLD_START_NS);
    EXPECT_EQ(model.GetTemplateBucketSampleCount(ScrollPlaceholderComponentType::LIST, "tpl"), 0u);
    EXPECT_EQ(model.GetComponentSampleCount(ScrollPlaceholderComponentType::LIST), 0u);
}

/**
 * @tc.name: CostModelRecordAndEstimate001
 * @tc.desc: Recording real build durations makes the estimate follow recent samples.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, CostModelRecordAndEstimate001, TestSize.Level1)
{
    ScrollPlaceholderCostModel model;
    model.RecordRealBuildDuration(ScrollPlaceholderComponentType::LIST, "tpl", LARGE_DURATION_NS);
    int64_t estimate = model.EstimateRealBuildDuration(ScrollPlaceholderComponentType::LIST, "tpl");
    EXPECT_GE(estimate, LARGE_DURATION_NS); // mean + deviation never below the first sample here

    for (int i = 0; i < 20; i++) {
        model.RecordRealBuildDuration(ScrollPlaceholderComponentType::LIST, "tpl", SMALL_DURATION_NS);
    }
    estimate = model.EstimateRealBuildDuration(ScrollPlaceholderComponentType::LIST, "tpl");
    EXPECT_LT(estimate, SMALL_DURATION_NS * 2);
    EXPECT_EQ(model.GetTemplateBucketSampleCount(ScrollPlaceholderComponentType::LIST, "tpl"), 21u);
    EXPECT_EQ(model.GetComponentSampleCount(ScrollPlaceholderComponentType::LIST), 21u);
}

/**
 * @tc.name: CostModelComponentFallback001
 * @tc.desc: Unknown templates fall back to the component aggregate, other components stay cold.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, CostModelComponentFallback001, TestSize.Level1)
{
    ScrollPlaceholderCostModel model;
    model.RecordRealBuildDuration(ScrollPlaceholderComponentType::LIST, "tplA", LARGE_DURATION_NS);
    int64_t sameComponent = model.EstimateRealBuildDuration(ScrollPlaceholderComponentType::LIST, "tplB");
    EXPECT_GE(sameComponent, LARGE_DURATION_NS); // component aggregate carries the sample
    int64_t otherComponent = model.EstimateRealBuildDuration(ScrollPlaceholderComponentType::WATER_FLOW, "tplB");
    EXPECT_EQ(otherComponent, COLD_START_NS); // isolated bucket, cold start
}

/**
 * @tc.name: TemplateRegisterAndQuery001
 * @tc.desc: Register/query/lookup a template through the manager facade.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, TemplateRegisterAndQuery001, TestSize.Level1)
{
    bool builderCalled = false;
    uint64_t generation = manager_->RegisterTemplate(
        "tpl", [&builderCalled]() -> RefPtr<UINode> {
            builderCalled = true;
            return TestPlaceholderNode::CreateTestNode(1);
        });
    EXPECT_EQ(generation, 1u);
    EXPECT_TRUE(manager_->IsTemplateRegistered("tpl"));

    auto snapshot = manager_->LookupTemplateForCreate("tpl");
    ASSERT_TRUE(snapshot.has_value());
    EXPECT_EQ(snapshot->generation, 1u);
    ASSERT_TRUE(snapshot->builder);
    auto node = snapshot->builder();
    EXPECT_TRUE(builderCalled);
    ASSERT_TRUE(node);
}

/**
 * @tc.name: TemplateRegisterInvalidRejected001
 * @tc.desc: Empty id or empty builder is rejected with a diagnostics counter bump.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, TemplateRegisterInvalidRejected001, TestSize.Level1)
{
    EXPECT_EQ(manager_->RegisterTemplate(std::string(), []() -> RefPtr<UINode> { return nullptr; }), 0u);
    EXPECT_EQ(manager_->RegisterTemplate("tpl", ScrollPlaceholderBuilder()), 0u);
    EXPECT_FALSE(manager_->IsTemplateRegistered("tpl"));
    auto diagnostics = manager_->GetDiagnostics();
    EXPECT_EQ(diagnostics.registerRejected, 2u);
}

/**
 * @tc.name: TemplateUnregisterIdempotent001
 * @tc.desc: Unregister removes the entry once and is an idempotent no-op afterwards.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, TemplateUnregisterIdempotent001, TestSize.Level1)
{
    manager_->RegisterTemplate("tpl", []() -> RefPtr<UINode> { return TestPlaceholderNode::CreateTestNode(1); });
    EXPECT_TRUE(manager_->UnregisterTemplate("tpl"));
    EXPECT_FALSE(manager_->UnregisterTemplate("tpl"));
    EXPECT_FALSE(manager_->IsTemplateRegistered("tpl"));
    EXPECT_FALSE(manager_->LookupTemplateForCreate("tpl").has_value());
}

/**
 * @tc.name: TemplateGenerationMonotonic001
 * @tc.desc: Re-register and unregister keep the per-id generation monotonically increasing.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, TemplateGenerationMonotonic001, TestSize.Level1)
{
    auto builder = []() -> RefPtr<UINode> { return TestPlaceholderNode::CreateTestNode(1); };
    uint64_t first = manager_->RegisterTemplate("tpl", ScrollPlaceholderBuilder(builder));
    uint64_t second = manager_->RegisterTemplate("tpl", ScrollPlaceholderBuilder(builder));
    EXPECT_GT(second, first);
    EXPECT_TRUE(manager_->UnregisterTemplate("tpl"));
    EXPECT_FALSE(manager_->LookupTemplateForCreate("tpl").has_value());
    uint64_t third = manager_->RegisterTemplate("tpl", ScrollPlaceholderBuilder(builder));
    EXPECT_GT(third, second);
}

/**
 * @tc.name: TemplateInstanceCache001
 * @tc.desc: Built instances are retained per template and handed out on acquire.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, TemplateInstanceCache001, TestSize.Level1)
{
    manager_->RegisterTemplate("tpl", []() -> RefPtr<UINode> { return TestPlaceholderNode::CreateTestNode(1); });
    auto first = TestPlaceholderNode::CreateTestNode(11);
    auto second = TestPlaceholderNode::CreateTestNode(12);
    manager_->CacheTemplateInstance("tpl", first);
    manager_->CacheTemplateInstance("tpl", second);
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 2u);

    auto acquired = manager_->AcquireTemplateInstance("tpl");
    ASSERT_TRUE(acquired);
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 1u);
    EXPECT_TRUE(manager_->AcquireTemplateInstance("tpl"));
    EXPECT_FALSE(manager_->AcquireTemplateInstance("tpl"));
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 0u);
}

/**
 * @tc.name: TemplateLruEvictionAndRebuild001
 * @tc.desc: Registering the 21st hot template evicts the least recently used one and releases
 *           its unmounted instances; the cold entry stays registered and rebuilds on demand.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, TemplateLruEvictionAndRebuild001, TestSize.Level1)
{
    auto builder = []() -> RefPtr<UINode> { return TestPlaceholderNode::CreateTestNode(1); };
    auto evictedInstance = TestPlaceholderNode::CreateTestNode(21);
    WeakPtr<UINode> evictedWeak = evictedInstance;
    for (int i = 0; i < 20; i++) {
        manager_->RegisterTemplate("tpl" + std::to_string(i), ScrollPlaceholderBuilder(builder));
    }
    manager_->CacheTemplateInstance("tpl0", evictedInstance);
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl0"), 1u);
    EXPECT_EQ(manager_->GetHotTemplateCount(), 20u);

    // Promoting tpl19 (the MRU entry) keeps tpl0 at the LRU end; the 21st registration evicts it.
    manager_->LookupTemplateForCreate("tpl19");
    manager_->RegisterTemplate("tpl20", ScrollPlaceholderBuilder(builder));
    EXPECT_EQ(manager_->GetHotTemplateCount(), 20u);
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl0"), 0u);
    evictedInstance = nullptr;
    EXPECT_FALSE(evictedWeak.Upgrade()); // instance released by eviction

    // The evicted entry keeps its registration relation and rebuilds on the next create hit.
    EXPECT_TRUE(manager_->IsTemplateRegistered("tpl0"));
    auto snapshot = manager_->LookupTemplateForCreate("tpl0");
    ASSERT_TRUE(snapshot.has_value());
    EXPECT_EQ(manager_->GetHotTemplateCount(), 20u);
    auto diagnostics = manager_->GetDiagnostics();
    EXPECT_GE(diagnostics.lruEvictedTemplates, 1u);
}

/**
 * @tc.name: TemplateLruQueryDoesNotPromote001
 * @tc.desc: isRegistered is read-only: it never keeps an entry hot.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, TemplateLruQueryDoesNotPromote001, TestSize.Level1)
{
    auto builder = []() -> RefPtr<UINode> { return TestPlaceholderNode::CreateTestNode(1); };
    auto retained = TestPlaceholderNode::CreateTestNode(31);
    for (int i = 0; i < 20; i++) {
        manager_->RegisterTemplate("tpl" + std::to_string(i), ScrollPlaceholderBuilder(builder));
    }
    // tpl0 is the LRU end; querying it must not promote it above tpl1.
    EXPECT_TRUE(manager_->IsTemplateRegistered("tpl0"));
    manager_->CacheTemplateInstance("tpl1", retained);
    manager_->RegisterTemplate("tpl20", ScrollPlaceholderBuilder(builder));
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl1"), 1u); // tpl1 survived, tpl0 was evicted
    retained = nullptr;
}

/**
 * @tc.name: PredictWithoutFrameAnchor001
 * @tc.desc: Without a frame anchor or explicit deadline the legacy synchronous path is kept.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PredictWithoutFrameAnchor001, TestSize.Level1)
{
    auto result = manager_->Predict(MakeParams(ScrollPlaceholderComponentType::LIST, "tpl", 1, 0), 0);
    EXPECT_EQ(result.decision, ScrollPlaceholderDecision::BUILD_REAL_NOW);
    EXPECT_EQ(result.remainingBudgetNs, 0);
}

/**
 * @tc.name: PredictWithVsyncAnchor001
 * @tc.desc: The vsync derived deadline uses the reported period with a 60Hz fallback.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PredictWithVsyncAnchor001, TestSize.Level1)
{
    manager_->NotifyVsync(1000, FRAME_120HZ_NS);
    EXPECT_EQ(manager_->GetVsyncDerivedFrameDeadlineNs(), 1000 + FRAME_120HZ_NS);
    manager_->NotifyVsync(2000, 0);
    EXPECT_EQ(manager_->GetVsyncDerivedFrameDeadlineNs(), 2000 + 16666667);
}

/**
 * @tc.name: PredictDecisionByBudget001
 * @tc.desc: A generous deadline builds synchronously, a tight deadline defers to placeholder.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PredictDecisionByBudget001, TestSize.Level1)
{
    auto params = MakeParams(ScrollPlaceholderComponentType::LIST, std::string(), 1, 0);
    int64_t generous = GetSysTimestamp() + 10 * COLD_START_NS;
    auto allow = manager_->Predict(params, generous);
    EXPECT_EQ(allow.decision, ScrollPlaceholderDecision::BUILD_REAL_NOW);
    EXPECT_GT(allow.remainingBudgetNs, 0);

    int64_t tight = GetSysTimestamp() + 2 * 1000000; // 2ms, below the 5ms cold estimate
    auto defer = manager_->Predict(params, tight);
    EXPECT_EQ(defer.decision, ScrollPlaceholderDecision::USE_PLACEHOLDER);
}

/**
 * @tc.name: PredictAdaptsToSamples001
 * @tc.desc: The decision follows the sampled cost of the bucket.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PredictAdaptsToSamples001, TestSize.Level1)
{
    auto params = MakeParams(ScrollPlaceholderComponentType::LIST, "tpl", 1, 0);
    for (int i = 0; i < 5; i++) {
        manager_->RecordRealBuildDuration(params, LARGE_DURATION_NS);
    }
    int64_t deadline = GetSysTimestamp() + 10 * 1000000; // 10ms
    EXPECT_EQ(manager_->Predict(params, deadline).decision, ScrollPlaceholderDecision::USE_PLACEHOLDER);

    for (int i = 0; i < 30; i++) {
        manager_->RecordRealBuildDuration(params, SMALL_DURATION_NS);
    }
    deadline = GetSysTimestamp() + 10 * 1000000;
    EXPECT_EQ(manager_->Predict(params, deadline).decision, ScrollPlaceholderDecision::BUILD_REAL_NOW);
}

/**
 * @tc.name: RealBuildEnqueueDedup001
 * @tc.desc: Enqueue deduplicates by item identity (host node id + index).
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, RealBuildEnqueueDedup001, TestSize.Level1)
{
    manager_->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, std::string(), 7, 3), 0, []() { return true; },
        ScrollPlaceholderRealBuildPriority::VISIBLE);
    manager_->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, std::string(), 7, 3), 0, []() { return true; },
        ScrollPlaceholderRealBuildPriority::VISIBLE);
    manager_->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, std::string(), 7, 4), 0, []() { return true; },
        ScrollPlaceholderRealBuildPriority::VISIBLE);
    EXPECT_EQ(manager_->GetPendingRealBuildCount(), 2u);
    EXPECT_TRUE(manager_->HasPendingRealBuild());
}

/**
 * @tc.name: RealBuildFlushExecutesAndRecords001
 * @tc.desc: Flush executes tasks within the budget and samples their duration.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, RealBuildFlushExecutesAndRecords001, TestSize.Level1)
{
    uint64_t generation =
        manager_->RegisterTemplate("tpl", []() -> RefPtr<UINode> { return TestPlaceholderNode::CreateTestNode(1); });
    int executed = 0;
    for (int i = 0; i < 3; i++) {
        manager_->EnqueueRealBuild(
            MakeParams(ScrollPlaceholderComponentType::LIST, "tpl", 1, i), generation,
            [&executed]() {
                executed++;
                return true;
            },
            ScrollPlaceholderRealBuildPriority::VISIBLE);
    }
    manager_->FlushRealBuild(GetSysTimestamp() + 100 * 1000000);
    EXPECT_EQ(executed, 3);
    EXPECT_EQ(manager_->GetPendingRealBuildCount(), 0u);
    auto diagnostics = manager_->GetDiagnostics();
    EXPECT_EQ(diagnostics.realBuildExecuted, 3u);
    // Executed durations were sampled into the component bucket.
    auto params = MakeParams(ScrollPlaceholderComponentType::LIST, "tpl", 1, 0);
    EXPECT_LE(manager_->EstimateRealBuildDuration(params), 5 * COLD_START_NS);
}

/**
 * @tc.name: RealBuildFlushStopsOnBudget001
 * @tc.desc: Flush keeps tasks queued and requests another frame when the estimate exceeds the
 *           remaining budget.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, RealBuildFlushStopsOnBudget001, TestSize.Level1)
{
    auto params = MakeParams(ScrollPlaceholderComponentType::LIST, "tpl", 1, 0);
    for (int i = 0; i < 5; i++) {
        manager_->RecordRealBuildDuration(params, LARGE_DURATION_NS);
    }
    int executed = 0;
    for (int i = 0; i < 2; i++) {
        manager_->EnqueueRealBuild(
            MakeParams(ScrollPlaceholderComponentType::LIST, "tpl", 1, i), 0,
            [&executed]() {
                executed++;
                return true;
            },
            ScrollPlaceholderRealBuildPriority::VISIBLE);
    }
    manager_->FlushRealBuild(GetSysTimestamp() + 5 * 1000000); // ~4ms usable, estimate ~50ms
    EXPECT_EQ(executed, 0);
    EXPECT_EQ(manager_->GetPendingRealBuildCount(), 2u);
    auto diagnostics = manager_->GetDiagnostics();
    EXPECT_EQ(diagnostics.realBuildRequeued, 2u);
    EXPECT_GE(diagnostics.requestFrameCount, 1u);
}

/**
 * @tc.name: RealBuildFlushPriorityOrder001
 * @tc.desc: Visible tasks run before cache-only tasks regardless of enqueue order.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, RealBuildFlushPriorityOrder001, TestSize.Level1)
{
    std::vector<int32_t> order;
    manager_->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, std::string(), 1, 5), 0,
        [&order]() {
            order.push_back(5);
            return true;
        },
        ScrollPlaceholderRealBuildPriority::CACHE_ONLY);
    manager_->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, std::string(), 1, 1), 0,
        [&order]() {
            order.push_back(1);
            return true;
        },
        ScrollPlaceholderRealBuildPriority::VISIBLE);
    manager_->FlushRealBuild(GetSysTimestamp() + 100 * 1000000);
    ASSERT_EQ(order.size(), 2u);
    EXPECT_EQ(order[0], 1);
    EXPECT_EQ(order[1], 5);
}

/**
 * @tc.name: RealBuildStaleTemplateGeneration001
 * @tc.desc: Unregister purges pending tasks eagerly; re-register invalidates them at flush.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, RealBuildStaleTemplateGeneration001, TestSize.Level1)
{
    int executed = 0;
    auto builder = []() -> RefPtr<UINode> { return TestPlaceholderNode::CreateTestNode(1); };
    uint64_t generation = manager_->RegisterTemplate("tpl", ScrollPlaceholderBuilder(builder));
    manager_->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, "tpl", 1, 0), generation,
        [&executed]() {
            executed++;
            return true;
        },
        ScrollPlaceholderRealBuildPriority::VISIBLE);
    manager_->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, "tpl", 1, 1), generation,
        [&executed]() {
            executed++;
            return true;
        },
        ScrollPlaceholderRealBuildPriority::VISIBLE);

    // Re-register publishes a new generation: the queued tasks become stale at flush time.
    manager_->RegisterTemplate("tpl", ScrollPlaceholderBuilder(builder));
    manager_->FlushRealBuild(GetSysTimestamp() + 100 * 1000000);
    EXPECT_EQ(executed, 0);
    EXPECT_EQ(manager_->GetPendingRealBuildCount(), 0u);
    auto diagnostics = manager_->GetDiagnostics();
    EXPECT_EQ(diagnostics.realBuildDropped, 2u);

    // Unregister drops matching pending tasks immediately.
    uint64_t latest = manager_->RegisterTemplate("tpl2", ScrollPlaceholderBuilder(builder));
    manager_->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, "tpl2", 2, 0), latest,
        [&executed]() {
            executed++;
            return true;
        },
        ScrollPlaceholderRealBuildPriority::VISIBLE);
    EXPECT_TRUE(manager_->UnregisterTemplate("tpl2"));
    EXPECT_EQ(manager_->GetPendingRealBuildCount(), 0u);
    diagnostics = manager_->GetDiagnostics();
    EXPECT_EQ(diagnostics.cancelledByReason[static_cast<size_t>(ScrollPlaceholderCancelReason::UNREGISTER)], 1u);
}

/**
 * @tc.name: RealBuildCancelHost001
 * @tc.desc: Cancelling a host removes its pending tasks and reports the reason code.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, RealBuildCancelHost001, TestSize.Level1)
{
    int executed = 0;
    for (int i = 0; i < 3; i++) {
        manager_->EnqueueRealBuild(
            MakeParams(ScrollPlaceholderComponentType::GRID, std::string(), i + 1, 0), 0,
            [&executed]() {
                executed++;
                return true;
            },
            ScrollPlaceholderRealBuildPriority::VISIBLE);
    }
    manager_->CancelHostRealBuilds(2, ScrollPlaceholderCancelReason::HOST_RESET);
    EXPECT_EQ(manager_->GetPendingRealBuildCount(), 2u);
    manager_->FlushRealBuild(GetSysTimestamp() + 100 * 1000000);
    EXPECT_EQ(executed, 2);
    auto diagnostics = manager_->GetDiagnostics();
    EXPECT_EQ(diagnostics.cancelledByReason[static_cast<size_t>(ScrollPlaceholderCancelReason::HOST_RESET)], 1u);
}

/**
 * @tc.name: ManagerDestroy001
 * @tc.desc: Destroy drains pending tasks, releases the registry and turns later calls into no-ops.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, ManagerDestroy001, TestSize.Level1)
{
    auto builder = []() -> RefPtr<UINode> { return TestPlaceholderNode::CreateTestNode(1); };
    manager_->RegisterTemplate("tpl", ScrollPlaceholderBuilder(builder));
    manager_->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, "tpl", 1, 0), 1, []() { return true; },
        ScrollPlaceholderRealBuildPriority::VISIBLE);
    manager_->Destroy();
    EXPECT_TRUE(manager_->IsDestroyed());
    EXPECT_EQ(manager_->GetPendingRealBuildCount(), 0u);
    EXPECT_FALSE(manager_->IsTemplateRegistered("tpl"));
    auto diagnostics = manager_->GetDiagnostics();
    EXPECT_EQ(diagnostics.cancelledByReason[static_cast<size_t>(ScrollPlaceholderCancelReason::PIPELINE_DESTROYED)],
        1u);

    manager_->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, "tpl", 1, 0), 1, []() { return true; },
        ScrollPlaceholderRealBuildPriority::VISIBLE);
    EXPECT_EQ(manager_->GetPendingRealBuildCount(), 0u);
    manager_->FlushRealBuild(GetSysTimestamp() + 100 * 1000000);
    manager_->Destroy(); // idempotent
}

/**
 * @tc.name: ManagerIsolation001
 * @tc.desc: Registries and queues are isolated per manager (per container instance).
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, ManagerIsolation001, TestSize.Level1)
{
    auto other = AceType::MakeRefPtr<ScrollPlaceholderManager>(TEST_INSTANCE_ID + 1);
    auto builder = []() -> RefPtr<UINode> { return TestPlaceholderNode::CreateTestNode(1); };
    manager_->RegisterTemplate("tpl", ScrollPlaceholderBuilder(builder));
    EXPECT_FALSE(other->IsTemplateRegistered("tpl"));
    EXPECT_FALSE(other->LookupTemplateForCreate("tpl").has_value());
    EXPECT_EQ(other->GetHotTemplateCount(), 0u);
    EXPECT_EQ(manager_->GetHotTemplateCount(), 1u);

    other->EnqueueRealBuild(
        MakeParams(ScrollPlaceholderComponentType::LIST, std::string(), 1, 0), 0, []() { return true; },
        ScrollPlaceholderRealBuildPriority::VISIBLE);
    EXPECT_EQ(other->GetPendingRealBuildCount(), 1u);
    EXPECT_EQ(manager_->GetPendingRealBuildCount(), 0u);
    other->Destroy();
}

/**
 * @tc.name: PredictDiagnosticsCounters001
 * @tc.desc: Decision counters accumulate for both outcomes.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PredictDiagnosticsCounters001, TestSize.Level1)
{
    auto params = MakeParams(ScrollPlaceholderComponentType::LIST, std::string(), 1, 0);
    manager_->Predict(params, GetSysTimestamp() + 10 * COLD_START_NS);
    manager_->Predict(params, GetSysTimestamp() + 2 * 1000000);
    auto diagnostics = manager_->GetDiagnostics();
    EXPECT_EQ(diagnostics.predictBuildRealNow, 1u);
    EXPECT_EQ(diagnostics.predictUsePlaceholder, 1u);
}

/**
 * @tc.name: ObservationFrameStatsAccumulateAndClose001
 * @tc.desc: Real build observation accumulates per frame and closes on the next vsync; the
 *           suggestion counts follow the anchored budget (build-now vs placeholder).
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, ObservationFrameStatsAccumulateAndClose001, TestSize.Level1)
{
    auto params = MakeParams(ScrollPlaceholderComponentType::LIST, std::string(), 7, 0);

    // Before the first anchor: the build is observed but no budget suggestion is counted.
    manager_->NotifyRealBuildStart(params);
    manager_->NotifyRealBuildEnd(params, GetSysTimestamp() - 1000);
    auto stats = manager_->GetLastFrameObservation(ScrollPlaceholderComponentType::LIST);
    EXPECT_EQ(stats.observedBuilds, 0u); // frame not closed yet

    // Close the (anchorless) frame; anchor the next frame with a generous budget.
    manager_->NotifyVsync(GetSysTimestamp(), FRAME_120HZ_NS);
    stats = manager_->GetLastFrameObservation(ScrollPlaceholderComponentType::LIST);
    EXPECT_EQ(stats.observedBuilds, 1u);
    EXPECT_EQ(stats.suggestedReal, 0u);
    EXPECT_EQ(stats.suggestedPlaceholder, 0u);

    // Anchored frame with ~7ms usable budget above the 5ms cold estimate: suggest real.
    params.index = 1;
    auto result = manager_->NotifyRealBuildStart(params);
    EXPECT_TRUE(result.budgetAvailable);
    EXPECT_EQ(result.decision, ScrollPlaceholderDecision::BUILD_REAL_NOW);
    manager_->NotifyRealBuildEnd(params, GetSysTimestamp() - 50000);
    manager_->NotifyVsync(GetSysTimestamp(), FRAME_120HZ_NS);
    stats = manager_->GetLastFrameObservation(ScrollPlaceholderComponentType::LIST);
    EXPECT_EQ(stats.observedBuilds, 1u);
    EXPECT_EQ(stats.suggestedReal, 1u);
    EXPECT_EQ(stats.suggestedPlaceholder, 0u);
    EXPECT_GT(stats.lastRemainingBudgetNs, 0);
    auto diagnostics = manager_->GetDiagnostics();
    EXPECT_EQ(diagnostics.observedRealBuilds, 2u);

    // Anchored frame whose deadline is already exhausted: suggest placeholder.
    manager_->NotifyVsync(GetSysTimestamp() - FRAME_120HZ_NS, 1);
    params.index = 2;
    result = manager_->NotifyRealBuildStart(params);
    EXPECT_TRUE(result.budgetAvailable);
    EXPECT_EQ(result.decision, ScrollPlaceholderDecision::USE_PLACEHOLDER);
    manager_->NotifyRealBuildEnd(params, GetSysTimestamp() - 1000);
    manager_->NotifyVsync(GetSysTimestamp(), FRAME_120HZ_NS);
    stats = manager_->GetLastFrameObservation(ScrollPlaceholderComponentType::LIST);
    EXPECT_EQ(stats.observedBuilds, 1u);
    EXPECT_EQ(stats.suggestedReal, 0u);
    EXPECT_EQ(stats.suggestedPlaceholder, 1u);
}

/**
 * @tc.name: ObservationFeedsCostModel001
 * @tc.desc: Observed durations are sampled into the component bucket used for estimates.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, ObservationFeedsCostModel001, TestSize.Level1)
{
    auto params = MakeParams(ScrollPlaceholderComponentType::GRID, std::string(), 3, 0);
    for (int i = 0; i < 4; i++) {
        params.index = i;
        manager_->NotifyRealBuildStart(params);
        manager_->NotifyRealBuildEnd(params, GetSysTimestamp() - LARGE_DURATION_NS);
    }
    // Duration sampling reaches the component bucket of the cost model.
    EXPECT_GE(manager_->EstimateRealBuildDuration(params), LARGE_DURATION_NS);
    EXPECT_EQ(manager_->GetDiagnostics().observedRealBuilds, 4u);
}
} // namespace OHOS::Ace::NG
