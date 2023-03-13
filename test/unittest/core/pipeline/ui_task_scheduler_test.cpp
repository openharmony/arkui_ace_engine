/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class UITaskSchedulerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void UITaskSchedulerTest::SetUpTestCase()
{
    GTEST_LOG_(INFO) << "UITaskSchedulerTest SetUpTestCase";
}

void UITaskSchedulerTest::TearDownTestCase()
{
    GTEST_LOG_(INFO) << "UITaskSchedulerTest TearDownTestCase";
}

void UITaskSchedulerTest::SetUp()
{
    GTEST_LOG_(INFO) << "UITaskSchedulerTest SetUp";
}

void UITaskSchedulerTest::TearDown()
{
    GTEST_LOG_(INFO) << "UITaskSchedulerTest TearDown";
}

/**
 * @tc.name: UITaskSchedulerTest001
 * @tc.desc: Test the function AddDirtyRenderNode.
 * @tc.type: FUNC
 */
HWTEST_F(UITaskSchedulerTest, UITaskSchedulerTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    UITaskScheduler uiTaskScheduler;
    const std::string testTag("testTag");
    constexpr int32_t testNodeId = 1;
    auto frameNode = FrameNode::GetOrCreateFrameNode(testTag, testNodeId, nullptr);
    ASSERT_NE(frameNode, nullptr);
    int32_t pageId = frameNode->GetPageId();

    /**
     * @tc.steps2: Call the function AddDirtyRenderNode.
     * @tc.expected: The new FrameNode object is added to the map dirtyRenderNodes_ and its size is changed to 1.
     */
    EXPECT_EQ(uiTaskScheduler.dirtyRenderNodes_.find(pageId), uiTaskScheduler.dirtyRenderNodes_.end());
    uiTaskScheduler.AddDirtyRenderNode(frameNode);
    EXPECT_NE(uiTaskScheduler.dirtyRenderNodes_.find(pageId), uiTaskScheduler.dirtyRenderNodes_.end());
    EXPECT_EQ(uiTaskScheduler.dirtyRenderNodes_[pageId].size(), 1);

    /**
     * @tc.steps3: Call the function AddDirtyRenderNode again.
     * @tc.expected: The new FrameNode object is not added to the map dirtyRenderNodes_ and its size is not changed.
     */
    uiTaskScheduler.AddDirtyRenderNode(frameNode);
    EXPECT_EQ(uiTaskScheduler.dirtyRenderNodes_[pageId].size(), 1);
}

/**
 * @tc.name: UITaskSchedulerTest002
 * @tc.desc: Test the function FlushPredictTask.
 * @tc.type: FUNC
 */
HWTEST_F(UITaskSchedulerTest, UITaskSchedulerTest002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    UITaskScheduler uiTaskScheduler;
    constexpr int64_t deadlineVal = 10;
    int64_t flagTask = 0;
    uiTaskScheduler.AddPredictTask(nullptr);
    uiTaskScheduler.AddPredictTask([&flagTask] (int64_t deadline) { flagTask = deadline; });

    /**
     * @tc.steps2: Call the function FlushPredictTask.
     * @tc.expected: The flagTask is set to deadlineVal.
     */
    uiTaskScheduler.FlushPredictTask(deadlineVal);
    EXPECT_EQ(flagTask, deadlineVal);
}
} // namespace OHOS::Ace::NG
