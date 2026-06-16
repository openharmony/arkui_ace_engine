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

#define protected public
#define private public

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_frontend.h"
#include "test/mock/frameworks/core/common/mock_window.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class PipelineContextIsolatedThreadTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        auto window = std::make_shared<MockWindow>();
        EXPECT_CALL(*window, RequestFrame()).Times(AnyNumber());
        EXPECT_CALL(*window, FlushTasks(_)).Times(AnyNumber());
        auto frontend = AceType::MakeRefPtr<testing::NiceMock<MockFrontend>>();
        context_ = AceType::MakeRefPtr<PipelineContext>(
            window, AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, frontend, 0);
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = context_;
    }

    static void TearDownTestSuite()
    {
        if (context_) {
            context_->Destroy();
            context_->window_.reset();
        }
        context_ = nullptr;
        MockContainer::TearDown();
    }

    static RefPtr<PipelineContext> context_;
};

RefPtr<PipelineContext> PipelineContextIsolatedThreadTest::context_ = nullptr;

/**
 * @tc.name: PipelineContextIsolatedThreadTest_FlagDefaultAndGetter001
 * @tc.desc: Test PipelineContext isIsolatedThread_ defaults to false and getter matches
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextIsolatedThreadTest, PipelineContextIsolatedThreadTest_FlagDefaultAndGetter001, TestSize.Level1)
{
    auto pipeline = PipelineContextIsolatedThreadTest::context_;
    ASSERT_NE(pipeline, nullptr);
    EXPECT_FALSE(pipeline->isIsolatedThread_);
    EXPECT_FALSE(pipeline->IsIsolatedThread());
}

/**
 * @tc.name: PipelineContextIsolatedThreadTest_AddDirtyNodesMismatch001
 * @tc.desc: Test all AddDirty*Node methods log warning on mismatch but still process nodes
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextIsolatedThreadTest, PipelineContextIsolatedThreadTest_AddDirtyNodesMismatch001, TestSize.Level1)
{
    auto pipeline = PipelineContextIsolatedThreadTest::context_;
    ASSERT_NE(pipeline, nullptr);
    EXPECT_FALSE(pipeline->isIsolatedThread_);

    auto node = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    node->isIsolatedThread_ = true;

    pipeline->AddDirtyPropertyNode(node);
    EXPECT_EQ(pipeline->dirtyPropertyNodes_.size(), 1);

    node->onMainTree_ = true;
    pipeline->AddDirtyLayoutNode(node);
    EXPECT_FALSE(pipeline->taskScheduler_->dirtyLayoutNodes_.empty());

    pipeline->AddDirtyRenderNode(node);
    EXPECT_FALSE(pipeline->taskScheduler_->dirtyRenderNodes_.empty());

    auto node2 = FrameNode::CreateFrameNode("test2", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node2, nullptr);
    node2->isIsolatedThread_ = true;
    pipeline->AddDirtyFreezeNode(node2.GetRawPtr());
    EXPECT_FALSE(pipeline->dirtyFreezeNode_.empty());

    pipeline->AddDirtyFreezeNode(nullptr);
}

/**
 * @tc.name: PipelineContextIsolatedThreadTest_AddDirtyNodesMatch001
 * @tc.desc: Test AddDirty*Node works normally when pipeline and node flags match (both false or both true)
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextIsolatedThreadTest, PipelineContextIsolatedThreadTest_AddDirtyNodesMatch001, TestSize.Level1)
{
    auto pipeline = PipelineContextIsolatedThreadTest::context_;
    ASSERT_NE(pipeline, nullptr);

    auto node = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->isIsolatedThread_, pipeline->isIsolatedThread_);

    pipeline->AddDirtyPropertyNode(node);
    EXPECT_EQ(pipeline->dirtyPropertyNodes_.size(), 1);

    pipeline->isIsolatedThread_ = true;
    auto node2 = FrameNode::CreateFrameNode("test2", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node2, nullptr);
    node2->isIsolatedThread_ = true;

    pipeline->AddDirtyPropertyNode(node2);
    EXPECT_EQ(pipeline->dirtyPropertyNodes_.size(), 2);
}
} // namespace OHOS::Ace::NG
