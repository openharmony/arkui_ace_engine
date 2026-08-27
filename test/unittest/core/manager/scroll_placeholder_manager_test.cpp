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

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

constexpr int64_t FAR_FUTURE_DEADLINE = std::numeric_limits<int64_t>::max();

RefPtr<FrameNode> CreateHostNode(int32_t id)
{
    return FrameNode::CreateFrameNode("List", id, AceType::MakeRefPtr<Pattern>());
}

ScrollPlaceholderManager::RealBuildTaskBody OkBody(int64_t& capturedDuration)
{
    return [&capturedDuration](int64_t& durationNs) -> ScrollPlaceholderCommitResult {
        durationNs = 1000;
        capturedDuration = durationNs;
        return ScrollPlaceholderCommitResult::COMMITTED;
    };
}

} // namespace

class ScrollPlaceholderManagerTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
    void SetUp() override
    {
        manager_ = AceType::MakeRefPtr<ScrollPlaceholderManager>(nullptr);
    }
    RefPtr<ScrollPlaceholderManager> manager_;
};

/**
 * @tc.name: ScrollPlaceholderManagerTest/TemplateRegistryGeneration
 * @tc.desc: Re-registering the same id atomically publishes a new generation.
 */
HWTEST_F(ScrollPlaceholderManagerTest, TemplateRegistryGeneration, TestSize.Level1)
{
    auto gen1 = manager_->RegisterTemplate("tpl", []() -> RefPtr<UINode> { return nullptr; });
    EXPECT_GT(gen1, 0u);
    EXPECT_TRUE(manager_->HasTemplate("tpl"));
    EXPECT_EQ(manager_->GetTemplateGeneration("tpl"), gen1);
    auto gen2 = manager_->RegisterTemplate("tpl", []() -> RefPtr<UINode> { return nullptr; });
    EXPECT_GT(gen2, gen1);
    EXPECT_EQ(manager_->GetTemplateGeneration("tpl"), gen2);
    manager_->UnregisterTemplate("tpl");
    EXPECT_FALSE(manager_->HasTemplate("tpl"));
    EXPECT_EQ(manager_->GetTemplateGeneration("tpl"), 0u);
}

/**
 * @tc.name: ScrollPlaceholderManagerTest/InvalidTemplateRejected
 * @tc.desc: Empty id or null builder is rejected.
 */
HWTEST_F(ScrollPlaceholderManagerTest, InvalidTemplateRejected, TestSize.Level1)
{
    EXPECT_EQ(manager_->RegisterTemplate("", []() -> RefPtr<UINode> { return nullptr; }), 0u);
    EXPECT_EQ(manager_->RegisterTemplate("tpl", nullptr), 0u);
    EXPECT_FALSE(manager_->HasTemplate("tpl"));
}

/**
 * @tc.name: ScrollPlaceholderManagerTest/CommitWhenGenerationMatches
 * @tc.desc: A task with matching generations is executed and committed.
 */
HWTEST_F(ScrollPlaceholderManagerTest, CommitWhenGenerationMatches, TestSize.Level1)
{
    auto host = CreateHostNode(1001);
    manager_->RegisterContainer(host, [](int32_t index) { return std::nullopt; },
        [](const ScrollPlaceholderOptions&) -> RefPtr<FrameNode> { return nullptr; });
    auto gen = manager_->GetContainerGeneration(host->GetId());
    int64_t captured = 0;
    manager_->EnqueueRealBuild(host->GetId(), 3, gen, OkBody(captured));
    EXPECT_TRUE(manager_->HasPendingRealBuild(host->GetId()));
    manager_->FlushRealBuildTasks(FAR_FUTURE_DEADLINE);
    EXPECT_FALSE(manager_->HasPendingRealBuild(host->GetId()));
    EXPECT_EQ(manager_->GetDiagnostics().realBuildCommitted, 1u);
    EXPECT_EQ(manager_->GetDiagnostics().staleDropped, 0u);
    EXPECT_EQ(captured, 1000);
}

/**
 * @tc.name: ScrollPlaceholderManagerTest/StaleDroppedOnDataChange
 * @tc.desc: Data generation bump invalidates pending tasks (never mount stale results).
 */
HWTEST_F(ScrollPlaceholderManagerTest, StaleDroppedOnDataChange, TestSize.Level1)
{
    auto host = CreateHostNode(1002);
    manager_->RegisterContainer(host, [](int32_t index) { return std::nullopt; },
        [](const ScrollPlaceholderOptions&) -> RefPtr<FrameNode> { return nullptr; });
    auto gen = manager_->GetContainerGeneration(host->GetId());
    int64_t captured = 0;
    manager_->EnqueueRealBuild(host->GetId(), 5, gen, OkBody(captured));
    manager_->NotifyDataChanged(host->GetId());
    manager_->FlushRealBuildTasks(FAR_FUTURE_DEADLINE);
    EXPECT_EQ(manager_->GetDiagnostics().realBuildCommitted, 0u);
    EXPECT_EQ(manager_->GetDiagnostics().staleDropped, 1u);
    EXPECT_EQ(captured, 0); // body never ran
}

/**
 * @tc.name: ScrollPlaceholderManagerTest/CancelledOnContainerUnregister
 * @tc.desc: Unregistering the container cancels pending tasks.
 */
HWTEST_F(ScrollPlaceholderManagerTest, CancelledOnContainerUnregister, TestSize.Level1)
{
    auto host = CreateHostNode(1003);
    manager_->RegisterContainer(host, [](int32_t index) { return std::nullopt; },
        [](const ScrollPlaceholderOptions&) -> RefPtr<FrameNode> { return nullptr; });
    auto gen = manager_->GetContainerGeneration(host->GetId());
    int64_t captured = 0;
    manager_->EnqueueRealBuild(host->GetId(), 7, gen, OkBody(captured));
    manager_->UnregisterContainer(host->GetId());
    EXPECT_FALSE(manager_->IsContainerRegistered(host->GetId()));
    manager_->FlushRealBuildTasks(FAR_FUTURE_DEADLINE);
    EXPECT_EQ(manager_->GetDiagnostics().cancelled, 1u);
    EXPECT_EQ(manager_->GetDiagnostics().realBuildCommitted, 0u);
    EXPECT_EQ(captured, 0);
}

/**
 * @tc.name: ScrollPlaceholderManagerTest/GenerationMismatchStale
 * @tc.desc: A task snapshot not matching the container generation is dropped.
 */
HWTEST_F(ScrollPlaceholderManagerTest, GenerationMismatchStale, TestSize.Level1)
{
    auto host = CreateHostNode(1004);
    manager_->RegisterContainer(host, [](int32_t index) { return std::nullopt; },
        [](const ScrollPlaceholderOptions&) -> RefPtr<FrameNode> { return nullptr; });
    ScrollPlaceholderGeneration stale;
    stale.containerGen = 999; // fabricated mismatch
    int64_t captured = 0;
    manager_->EnqueueRealBuild(host->GetId(), 0, stale, OkBody(captured));
    manager_->FlushRealBuildTasks(FAR_FUTURE_DEADLINE);
    EXPECT_EQ(manager_->GetDiagnostics().staleDropped, 1u);
    EXPECT_EQ(captured, 0);
}

/**
 * @tc.name: ScrollPlaceholderManagerTest/PlaceholderLayoutBudget
 * @tc.desc: ShouldContinuePlaceholderLayout is opt-in and capped per frame.
 */
HWTEST_F(ScrollPlaceholderManagerTest, PlaceholderLayoutBudget, TestSize.Level1)
{
    auto host = CreateHostNode(1005);
    EXPECT_FALSE(manager_->ShouldContinuePlaceholderLayout(host->GetId()));
    manager_->RegisterContainer(host, [](int32_t index) { return std::nullopt; },
        [](const ScrollPlaceholderOptions&) -> RefPtr<FrameNode> { return nullptr; });
    EXPECT_TRUE(manager_->ShouldContinuePlaceholderLayout(host->GetId()));
    manager_->OnFrameStart();
    EXPECT_TRUE(manager_->ShouldContinuePlaceholderLayout(host->GetId()));
}

/**
 * @tc.name: ScrollPlaceholderManagerTest/DefaultPlaceholderCreated
 * @tc.desc: A registered container yields a default placeholder item via its factory.
 */
HWTEST_F(ScrollPlaceholderManagerTest, DefaultPlaceholderCreated, TestSize.Level1)
{
    auto host = CreateHostNode(1006);
    manager_->RegisterContainer(host, [](int32_t index) { return ScrollPlaceholderOptions {}; },
        [](const ScrollPlaceholderOptions& options) -> RefPtr<FrameNode> { return CreateHostNode(4242); });
    auto item = manager_->CreatePlaceholderItem(host->GetId(), 0);
    ASSERT_NE(item.node, nullptr);
    EXPECT_TRUE(item.templateId.empty());
    EXPECT_EQ(item.node->GetId(), 4242);
    EXPECT_EQ(manager_->GetDiagnostics().placeholdersCreated, 1u);
    EXPECT_EQ(manager_->GetDiagnostics().defaultFallbackUsed, 1u);
}

} // namespace OHOS::Ace::NG
