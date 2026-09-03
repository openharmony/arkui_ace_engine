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
#include <limits>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "base/utils/time_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_cost_model.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_manager.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_observer.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

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

// Captures background clone tasks instead of handing them to the BackgroundTaskExecutor, so
// the pool policy is tested deterministically: the synchronous seed is observed immediately
// and the replenish tasks run only when the test drains them. The per-node copy protocol
// stands in for the compiler restricted factory: a structural TestPlaceholderNode copy with
// a fresh id, counted for traversal assertions.
class TestableScrollPlaceholderManager : public ScrollPlaceholderManager {
public:
    explicit TestableScrollPlaceholderManager(int32_t instanceId) : ScrollPlaceholderManager(instanceId) {}

    void RunCapturedTasks()
    {
        auto tasks = std::move(capturedTasks_);
        capturedTasks_.clear();
        for (auto& task : tasks) {
            task();
        }
    }

    size_t CapturedTaskCount() const
    {
        return capturedTasks_.size();
    }

    uint32_t copiedNodeCount = 0;
    bool copyProtocolEnabled = true;
    bool useDefaultCopyProtocol = false;

protected:
    void SubmitBackgroundCloneTask(std::function<void()> task) override
    {
        capturedTasks_.emplace_back(std::move(task));
    }

    RefPtr<UINode> CreatePlaceholderNodeCopy(const RefPtr<UINode>& node) override
    {
        if (useDefaultCopyProtocol) {
            return ScrollPlaceholderManager::CreatePlaceholderNodeCopy(node);
        }
        if (!copyProtocolEnabled) {
            return nullptr;
        }
        copiedNodeCount++;
        return TestPlaceholderNode::CreateTestNode(node->GetId() + 1000);
    }

private:
    std::vector<std::function<void()>> capturedTasks_;
};

// Builder producing a two-level immutable source subtree for traversal assertions.
ScrollPlaceholderBuilder MakeTreeBuilder(int32_t baseId)
{
    return ScrollPlaceholderBuilder([baseId]() -> RefPtr<UINode> {
        auto root = TestPlaceholderNode::CreateTestNode(baseId);
        root->AddChild(TestPlaceholderNode::CreateTestNode(baseId + 1));
        return root;
    });
}

class ScrollPlaceholderManagerTestNg : public testing::Test {
public:
    void SetUp() override
    {
        manager_ = AceType::MakeRefPtr<TestableScrollPlaceholderManager>(TEST_INSTANCE_ID);
    }
    void TearDown() override
    {
        manager_ = nullptr;
    }

    RefPtr<TestableScrollPlaceholderManager> manager_;
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
    manager_->RegisterTemplate("tpl", MakeTreeBuilder(1));
    auto first = TestPlaceholderNode::CreateTestNode(11);
    auto second = TestPlaceholderNode::CreateTestNode(12);
    manager_->CacheTemplateInstance("tpl", first);
    manager_->CacheTemplateInstance("tpl", second); // over the spare capacity, dropped
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 1u); // spares only; source is resident
    ASSERT_TRUE(manager_->GetTemplateSourceInstance("tpl"));

    auto acquired = manager_->AcquireTemplateInstance("tpl");
    ASSERT_TRUE(acquired);
    EXPECT_EQ(acquired, first);
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 0u);
    // No spare with a working template: acquire never fails, it creates one on the UI thread.
    auto synced = manager_->AcquireTemplateInstance("tpl");
    EXPECT_TRUE(synced);
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 0u); // created for use, not cached
    EXPECT_TRUE(manager_->GetTemplateSourceInstance("tpl")); // source never leaves the pool
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
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl0"), 1u); // single spare slot; source is resident
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
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl1"), 1u); // spare survived; tpl0 evicted
    retained = nullptr;
}

/**
 * @tc.name: PlaceholderPoolRegisterSeedAndReplenish001
 * @tc.desc: Registration builds the resident source synchronously on the UI thread; one
 *           background task then traverses and copies it into the single spare slot.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PlaceholderPoolRegisterSeedAndReplenish001, TestSize.Level1)
{
    EXPECT_EQ(manager_->RegisterTemplate("tpl", MakeTreeBuilder(1)), 1u);
    auto source = manager_->GetTemplateSourceInstance("tpl");
    ASSERT_TRUE(source);                       // synchronous source build at registration
    EXPECT_EQ(source->GetChildren().size(), 1u);
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 0u); // no spare yet
    EXPECT_EQ(manager_->GetPendingCloneCount("tpl"), 1u);
    EXPECT_EQ(manager_->CapturedTaskCount(), 1u);

    manager_->RunCapturedTasks();
    EXPECT_EQ(manager_->copiedNodeCount, 2u);  // top-down copy visited root and child
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY - 1);
    EXPECT_EQ(manager_->GetPendingCloneCount("tpl"), 0u);
    EXPECT_EQ(manager_->CapturedTaskCount(), 0u); // no extra tasks once at capacity
    EXPECT_EQ(manager_->GetTemplateSourceInstance("tpl"), source); // source untouched by clones
}

/**
 * @tc.name: PlaceholderPoolAcquireTakesAndReplenishes001
 * @tc.desc: Acquire hands out a spare copy (never the source) and the background clone
 *           refills the spare slot from the resident source.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PlaceholderPoolAcquireTakesAndReplenishes001, TestSize.Level1)
{
    manager_->RegisterTemplate("tpl", MakeTreeBuilder(1));
    manager_->RunCapturedTasks();
    auto source = manager_->GetTemplateSourceInstance("tpl");
    ASSERT_TRUE(source);
    ASSERT_EQ(manager_->GetCachedInstanceCount("tpl"), SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY - 1);

    auto acquired = manager_->AcquireTemplateInstance("tpl");
    ASSERT_TRUE(acquired);
    EXPECT_NE(acquired, source);               // a spare copy, not the resident source
    EXPECT_EQ(acquired->GetChildren().size(), 1u); // structural copy kept the subtree
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 0u);
    EXPECT_EQ(manager_->GetPendingCloneCount("tpl"), 1u);
    manager_->RunCapturedTasks();
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY - 1);
    EXPECT_EQ(manager_->GetPendingCloneCount("tpl"), 0u);
    EXPECT_EQ(manager_->GetTemplateSourceInstance("tpl"), source);
}

/**
 * @tc.name: PlaceholderPoolSyncCreateWhenEmpty001
 * @tc.desc: With no spare the acquire path synchronously builds from the template on the UI
 *           thread; the pending clone refills the spare afterwards.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PlaceholderPoolSyncCreateWhenEmpty001, TestSize.Level1)
{
    manager_->RegisterTemplate("tpl", MakeTreeBuilder(1));
    EXPECT_EQ(manager_->CapturedTaskCount(), 1u); // replenish pending, not run yet

    auto synced = manager_->AcquireTemplateInstance("tpl"); // no spare path
    ASSERT_TRUE(synced);
    EXPECT_EQ(synced->GetChildren().size(), 1u);  // built by the builder on the UI thread
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 0u); // served directly, not cached
    EXPECT_EQ(manager_->CapturedTaskCount(), 1u); // spare slot already in flight
    manager_->RunCapturedTasks();
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY - 1);
    EXPECT_EQ(manager_->GetPendingCloneCount("tpl"), 0u);
}

/**
 * @tc.name: PlaceholderPoolStaleCloneDroppedOnReRegister001
 * @tc.desc: A clone carrying the previous generation is dropped after re-register; the clone
 *           of the current generation still fills the spare slot from the rebuilt source.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PlaceholderPoolStaleCloneDroppedOnReRegister001, TestSize.Level1)
{
    uint64_t first = manager_->RegisterTemplate("tpl", MakeTreeBuilder(1));
    auto firstSource = manager_->GetTemplateSourceInstance("tpl");
    uint64_t second = manager_->RegisterTemplate("tpl", MakeTreeBuilder(2));
    EXPECT_GT(second, first);
    auto secondSource = manager_->GetTemplateSourceInstance("tpl");
    ASSERT_TRUE(secondSource);
    EXPECT_NE(secondSource, firstSource);      // re-register rebuilt the source on the UI thread
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 0u);
    EXPECT_EQ(manager_->CapturedTaskCount(), 2u); // stale clone + current clone

    manager_->RunCapturedTasks();
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY - 1);
    EXPECT_EQ(manager_->GetPendingCloneCount("tpl"), 0u); // late stale release is floor-guarded
}

/**
 * @tc.name: PlaceholderPoolDestroyDropsInFlight001
 * @tc.desc: Destroy drops an in-flight clone without caching and drains its pending slot.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PlaceholderPoolDestroyDropsInFlight001, TestSize.Level1)
{
    manager_->RegisterTemplate("tpl", MakeTreeBuilder(1));
    ASSERT_EQ(manager_->CapturedTaskCount(), 1u);
    manager_->Destroy();
    manager_->RunCapturedTasks();
    EXPECT_FALSE(manager_->GetTemplateSourceInstance("tpl")); // registry cleared
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 0u);
    EXPECT_EQ(manager_->GetPendingCloneCount("tpl"), 0u);
}

/**
 * @tc.name: PlaceholderPoolCloneWithoutProtocolDegrades001
 * @tc.desc: Without a per-node copy protocol the background clone fails harmlessly and the
 *           pool keeps serving through the UI-thread paths.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PlaceholderPoolCloneWithoutProtocolDegrades001, TestSize.Level1)
{
    manager_->copyProtocolEnabled = false;
    manager_->RegisterTemplate("tpl", MakeTreeBuilder(1));
    ASSERT_TRUE(manager_->GetTemplateSourceInstance("tpl"));
    manager_->RunCapturedTasks();
    EXPECT_EQ(manager_->copiedNodeCount, 0u);
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), 0u); // clone dropped
    EXPECT_EQ(manager_->GetPendingCloneCount("tpl"), 0u);   // slot released
    EXPECT_TRUE(manager_->AcquireTemplateInstance("tpl"));  // UI-thread fallback still serves
}

/**
 * @tc.name: PlaceholderPoolDefaultCopyCreatesSameTypeNodes001
 * @tc.desc: The production copy protocol creates a same-type node per visited source node
 *           and copies the layout property over; plain frame node subtrees clone fully.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PlaceholderPoolDefaultCopyCreatesSameTypeNodes001, TestSize.Level1)
{
    manager_->useDefaultCopyProtocol = true;
    auto builder = []() -> RefPtr<UINode> {
        auto root = FrameNode::CreateFrameNode(
            "placeholder_root", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
        auto child = FrameNode::CreateFrameNode(
            "placeholder_child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
        child->GetLayoutProperty()->UpdateAspectRatio(1.5f);
        root->AddChild(child);
        return root;
    };
    manager_->RegisterTemplate("tpl", ScrollPlaceholderBuilder(builder));
    auto source = manager_->GetTemplateSourceInstance("tpl");
    ASSERT_TRUE(source);
    manager_->RunCapturedTasks();
    EXPECT_EQ(manager_->GetCachedInstanceCount("tpl"), SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY - 1);

    auto acquired = manager_->AcquireTemplateInstance("tpl");
    ASSERT_TRUE(acquired);
    EXPECT_NE(acquired, source); // same-type copies, not the resident source
    auto copyRoot = AceType::DynamicCast<FrameNode>(acquired);
    ASSERT_TRUE(copyRoot);
    EXPECT_EQ(copyRoot->GetTag(), "placeholder_root");
    EXPECT_NE(copyRoot->GetId(), AceType::DynamicCast<FrameNode>(source)->GetId());
    const auto& copyChildren = copyRoot->GetChildren();
    ASSERT_EQ(copyChildren.size(), 1u);
    auto copyChild = AceType::DynamicCast<FrameNode>(copyChildren.front());
    ASSERT_TRUE(copyChild);
    EXPECT_EQ(copyChild->GetTag(), "placeholder_child");
    EXPECT_FLOAT_EQ(copyChild->GetLayoutProperty()->GetAspectRatio(), 1.5f); // property copied
}

/**
 * @tc.name: PlaceholderPoolDefaultSubmitterSmoke001
 * @tc.desc: The production submitter path (BackgroundTaskExecutor) registers the source on
 *           the UI thread; the background clone never overfills the pool.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderManagerTestNg, PlaceholderPoolDefaultSubmitterSmoke001, TestSize.Level1)
{
    auto real = AceType::MakeRefPtr<ScrollPlaceholderManager>(TEST_INSTANCE_ID + 2);
    EXPECT_GT(real->RegisterTemplate("tpl", MakeTreeBuilder(1)), 0u);
    EXPECT_TRUE(real->GetTemplateSourceInstance("tpl")); // synchronous source is guaranteed
    EXPECT_LE(real->GetCachedInstanceCount("tpl"), SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY - 1);
    real->Destroy();
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

// Observer scope tests exercise the List/Grid/WaterFlow call point glue: the cache gate that
// keeps already built items out of the observation, and the empty-acquisition skip that keeps
// zero-cost samples away from the cost model. The end-to-end sampling semantics of the
// manager hooks are covered by the cases above.
class ScrollPlaceholderObserverTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

namespace {
RefPtr<FrameNode> CreateObserverHost(int32_t nodeId, bool withChild)
{
    auto host = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    if (withChild) {
        host->AddChild(FrameNode::CreateFrameNode("observer_child", nodeId + 1, AceType::MakeRefPtr<Pattern>()));
    }
    return host;
}

uint64_t CurrentObservedRealBuilds()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, std::numeric_limits<uint64_t>::max());
    const auto& manager = context->GetOrCreateScrollPlaceholderManager();
    CHECK_NULL_RETURN(manager, std::numeric_limits<uint64_t>::max());
    return manager->GetDiagnostics().observedRealBuilds;
}
} // namespace

/**
 * @tc.name: ObserverScopeSkipsBuiltItem001
 * @tc.desc: An index that resolves without running the real builder is not observed at all.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderObserverTestNg, ObserverScopeSkipsBuiltItem001, TestSize.Level1)
{
    auto host = CreateObserverHost(2001, true);
    auto wrapper = host->CreateLayoutWrapper();
    auto before = CurrentObservedRealBuilds();
    {
        ScrollPlaceholderItemBuildScope buildScope(
            ScrollPlaceholderComponentType::LIST, AceType::RawPtr(wrapper), 0, false);
        auto acquired = wrapper->GetOrCreateChildByIndex(0, true, false);
        buildScope.SetAcquiredWrapper(acquired);
        EXPECT_TRUE(acquired); // the built child resolves from the wrapper cache
    }
    EXPECT_EQ(CurrentObservedRealBuilds(), before); // cache gate: no observation
}

/**
 * @tc.name: ObserverScopeSkipsEmptyAcquisition001
 * @tc.desc: A null acquisition result (out of range / empty branch) never samples the model.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderObserverTestNg, ObserverScopeSkipsEmptyAcquisition001, TestSize.Level1)
{
    auto host = CreateObserverHost(2021, false);
    auto wrapper = host->CreateLayoutWrapper();
    auto before = CurrentObservedRealBuilds();
    {
        ScrollPlaceholderItemBuildScope buildScope(
            ScrollPlaceholderComponentType::LIST, AceType::RawPtr(wrapper), 0, false);
        auto acquired = wrapper->GetOrCreateChildByIndex(0, true, false);
        buildScope.SetAcquiredWrapper(acquired);
        EXPECT_FALSE(acquired); // nothing to build for this index
    }
    EXPECT_EQ(CurrentObservedRealBuilds(), before); // no zero-cost sample
}

/**
 * @tc.name: ObserverScopeObservesRealAcquisition001
 * @tc.desc: An unbuilt index with a non-null acquisition result is observed and sampled.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPlaceholderObserverTestNg, ObserverScopeObservesRealAcquisition001, TestSize.Level1)
{
    auto host = CreateObserverHost(2041, false);
    auto wrapper = host->CreateLayoutWrapper();
    // Stand-in wrapper for the item the real builder would produce for the unbuilt index.
    RefPtr<LayoutWrapper> builtElsewhere = CreateObserverHost(2061, false)->CreateLayoutWrapper();
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_TRUE(context);
    const auto& manager = context->GetOrCreateScrollPlaceholderManager();
    ASSERT_TRUE(manager);
    auto before = CurrentObservedRealBuilds();
    {
        ScrollPlaceholderItemBuildScope buildScope(
            ScrollPlaceholderComponentType::LIST, AceType::RawPtr(wrapper), 0, false);
        buildScope.SetAcquiredWrapper(builtElsewhere);
    }
    EXPECT_EQ(CurrentObservedRealBuilds(), before + 1); // sampled through NotifyRealBuildEnd
    // The tiny measured duration replaced the 5ms cold start estimate.
    auto probe = MakeParams(ScrollPlaceholderComponentType::LIST, std::string(), 0, 0);
    EXPECT_LT(manager->EstimateRealBuildDuration(probe), COLD_START_NS);
}
} // namespace OHOS::Ace::NG
