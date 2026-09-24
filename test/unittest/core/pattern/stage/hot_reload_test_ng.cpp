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

#include "gtest/gtest.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/root/root_pattern.h"

#define private public
#define protected public

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t g_hotReloadAboutToAppearCallCount = 0;
int32_t g_hotReloadReloadFuncCallCount = 0;
int32_t g_hotReloadCompleteReloadCallCount = 0;

void ResetHotReloadCounters()
{
    g_hotReloadAboutToAppearCallCount = 0;
    g_hotReloadReloadFuncCallCount = 0;
    g_hotReloadCompleteReloadCallCount = 0;
}
} // namespace

class HotReloadTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() override
    {
        ResetHotReloadCounters();
    }
    void TearDown() override
    {
        ResetHotReloadCounters();
    }
};

/**
 * @tc.name: HotReloadTest001
 * @tc.desc: Test StageManager::ReloadStage with fullRebuild=false (ReloadPage path)
 * @tc.type: FUNC
 */
HWTEST_F(HotReloadTestNg, HotReloadTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StageNode and StageManager
     */
    auto stageNode = FrameNode::CreateFrameNode("stage", 1, AceType::MakeRefPtr<StagePattern>());
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step2. Create PageNode with PagePattern and CustomNode
     */
    auto pageInfo = AceType::MakeRefPtr<PageInfo>();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(pageInfo);
    auto pageNode = FrameNode::CreateFrameNode("page", 2, pagePattern);

    /**
     * @tc.steps: step3. Create CustomNode with reloadFunc
     */
    auto customNode = CustomNode::CreateCustomNode(3, "root");
    customNode->SetReloadFunction([](bool deep) {
        g_hotReloadReloadFuncCallCount++;
    });
    customNode->MountToParent(pageNode);

    /**
     * @tc.steps: step4. Mount pageNode to stageNode
     */
    pageNode->MountToParent(stageNode);

    /**
     * @tc.steps: step5. Call ReloadStage with fullRebuild=false
     * @tc.expected: reloadFunc_ should be called, aboutToAppear should NOT be called
     */
    stageManager.ReloadStage(false);

    EXPECT_EQ(g_hotReloadReloadFuncCallCount, 1);
    EXPECT_EQ(g_hotReloadAboutToAppearCallCount, 0);
}

/**
 * @tc.name: HotReloadTest002
 * @tc.desc: Test StageManager::ReloadStage with fullRebuild=true (RebuildPage path)
 * @tc.type: FUNC
 */
HWTEST_F(HotReloadTestNg, HotReloadTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StageNode and StageManager
     */
    auto stageNode = FrameNode::CreateFrameNode("stage", 1, AceType::MakeRefPtr<StagePattern>());
    StageManager stageManager(stageNode);

    /**
     * @tc.steps: step2. Create PageNode with PagePattern and CustomNode
     */
    auto pageInfo = AceType::MakeRefPtr<PageInfo>();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(pageInfo);
    auto pageNode = FrameNode::CreateFrameNode("page", 2, pagePattern);

    /**
     * @tc.steps: step3. Create CustomNode with triggerLifecycleFunc and completeReloadFunc
     */
    auto customNode = CustomNode::CreateCustomNode(3, "root");
    auto child = FrameNode::CreateFrameNode("hotReloadChild", 4, AceType::MakeRefPtr<StagePattern>());
    customNode->SetTriggerLifecycleFunction([](int32_t eventId) -> bool {
        if (eventId == static_cast<int32_t>(CustomNodeBase::LifeCycleEvent::ON_APPEAR)) {
            g_hotReloadAboutToAppearCallCount++;
        }
        return true;
    });
    customNode->SetCompleteReloadFunc([&g_hotReloadCompleteReloadCallCount, child](int64_t, bool&) -> RefPtr<UINode> {
        g_hotReloadCompleteReloadCallCount++;
        return child;
    });
    customNode->MountToParent(pageNode);

    /**
     * @tc.steps: step4. Mount pageNode to stageNode
     */
    pageNode->MountToParent(stageNode);

    /**
     * @tc.steps: step5. Call ReloadStage with fullRebuild=true
     * @tc.expected: both aboutToAppear and completeReloadFunc should be called,
     *               the returned child should be mounted with the correct tag
     */
    stageManager.ReloadStage(true);

    EXPECT_EQ(g_hotReloadAboutToAppearCallCount, 1);
    EXPECT_EQ(g_hotReloadCompleteReloadCallCount, 1);
    ASSERT_NE(customNode->GetFirstChild(), nullptr);
    EXPECT_EQ(customNode->GetFirstChild()->GetTag(), "hotReloadChild");
}

/**
 * @tc.name: HotReloadTest003
 * @tc.desc: Test PagePattern::RebuildPage triggers aboutToAppear and completeReloadFunc via FlushReload
 * @tc.type: FUNC
 */
HWTEST_F(HotReloadTestNg, HotReloadTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PagePattern and CustomNode
     */
    auto pageInfo = AceType::MakeRefPtr<PageInfo>();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(pageInfo);
    auto host = FrameNode::CreateFrameNode("page", 2, pagePattern);

    /**
     * @tc.steps: step2. Create CustomNode with lifecycle and complete reload functions.
     *            A sentinel renderFunction is installed first; it must be replaced by the
     *            completeReloadFunc during FlushReload and therefore never be called.
     */
    bool aboutToAppearCalled = false;
    bool completeReloadCalled = false;
    bool sentinelRenderFunctionCalled = false;
    auto customNode = CustomNode::CreateCustomNode(3, "root");
    auto child = FrameNode::CreateFrameNode("hotReloadChild", 4, AceType::MakeRefPtr<StagePattern>());
    customNode->SetTriggerLifecycleFunction([&aboutToAppearCalled](int32_t eventId) -> bool {
        if (eventId == static_cast<int32_t>(CustomNodeBase::LifeCycleEvent::ON_APPEAR)) {
            aboutToAppearCalled = true;
        }
        return true;
    });
    customNode->SetRenderFunction([&sentinelRenderFunctionCalled](int64_t, bool&) -> RefPtr<UINode> {
        sentinelRenderFunctionCalled = true;
        return nullptr;
    });
    customNode->SetCompleteReloadFunc([&completeReloadCalled, child](int64_t, bool&) -> RefPtr<UINode> {
        completeReloadCalled = true;
        return child;
    });
    customNode->MountToParent(host);

    /**
     * @tc.steps: step3. Call RebuildPage
     * @tc.expected: aboutToAppear should be called via Render, completeReloadFunc should be called
     *               instead of the original renderFunction, and the returned child should be
     *               mounted with the correct tag
     */
    pagePattern->RebuildPage();

    EXPECT_TRUE(aboutToAppearCalled);
    EXPECT_TRUE(completeReloadCalled);
    EXPECT_FALSE(sentinelRenderFunctionCalled);
    ASSERT_NE(customNode->GetFirstChild(), nullptr);
    EXPECT_EQ(customNode->GetFirstChild()->GetTag(), "hotReloadChild");
}

/**
 * @tc.name: HotReloadTest004
 * @tc.desc: Test PipelineContext::FlushReload with hotReloadFullRebuild=true
 * @tc.type: FUNC
 */
HWTEST_F(HotReloadTestNg, HotReloadTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create PipelineContext with StageManager
     */
    auto context = AceType::MakeRefPtr<MockPipelineContext>();
    auto rootNode = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    context->rootNode_ = rootNode;
    context->stageManager_ = AceType::MakeRefPtr<StageManager>(rootNode);
    context->onShow_ = false;

    /**
     * @tc.steps: step2. Create page with PagePattern
     */
    auto pageInfo = AceType::MakeRefPtr<PageInfo>();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(pageInfo);
    auto pageNode = FrameNode::CreateFrameNode("page", 2, pagePattern);

    auto customNode = CustomNode::CreateCustomNode(3, "root");
    bool aboutToAppearCalled = false;
    bool completeReloadCalled = false;
    auto child = FrameNode::CreateFrameNode("hotReloadChild", 4, AceType::MakeRefPtr<StagePattern>());
    customNode->SetTriggerLifecycleFunction([&aboutToAppearCalled](int32_t eventId) -> bool {
        if (eventId == static_cast<int32_t>(CustomNodeBase::LifeCycleEvent::ON_APPEAR)) {
            aboutToAppearCalled = true;
        }
        return true;
    });
    customNode->SetCompleteReloadFunc([&completeReloadCalled, child](int64_t, bool&) -> RefPtr<UINode> {
        completeReloadCalled = true;
        return child;
    });
    customNode->MountToParent(pageNode);
    pageNode->MountToParent(rootNode);

    /**
     * @tc.steps: step3. Call FlushReload with hotReloadFullRebuild=true
     */
    ConfigurationChange config;
    config.hotReloadUpdate = true;
    config.hotReloadFullRebuild = true;
    context->FlushReload(config, true);

    /**
     * @tc.expected: aboutToAppear should be triggered and completeReloadFunc should be called via FlushReload,
     *               the returned child should be mounted with the correct tag
     */
    EXPECT_TRUE(aboutToAppearCalled);
    EXPECT_TRUE(completeReloadCalled);
    ASSERT_NE(customNode->GetFirstChild(), nullptr);
    EXPECT_EQ(customNode->GetFirstChild()->GetTag(), "hotReloadChild");
}
} // namespace OHOS::Ace::NG
