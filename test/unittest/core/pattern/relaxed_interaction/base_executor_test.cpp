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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/relaxed_interaction/base_executor.h"
#include "core/components_ng/relaxed_interaction/frame_node_finder.h"
#include "core/components_ng/relaxed_interaction/utils/workflow_dumper.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr float ROOT_WIDTH = 720.0f;
constexpr float ROOT_HEIGHT = 1280.0f;
constexpr float TEST_X = 50.0f;
constexpr float TEST_Y = 50.0f;
constexpr float CHILD_WIDTH = 100.0f;
constexpr float CHILD_HEIGHT = 100.0f;
constexpr int32_t FRAME_NODE_ID = 1;
constexpr float ORIGIN_X = 0.0f;
constexpr float ORIGIN_Y = 0.0f;
constexpr int32_t FINGER_COUNT = 1;
constexpr int32_t TAP_COUNT = 1;
const std::string BUTTON_TAG = "Button";
const std::string TEST_EXECUTOR_TYPE = "TestExecutor";
const std::string NO_NODE_FOUND_LOG = "No frame node found";
const std::string FOUND_NODE_LOG = "Found frame node";
} // namespace

class TestExecutor : public BaseExecutor {
public:
    explicit TestExecutor(WeakPtr<PipelineContext> context) : BaseExecutor(context) {}

    ExecutorResult ExecuteStep() override
    {
        return ExecutorResult::SUCCESS;
    }

    std::string GetType() const override
    {
        return TEST_EXECUTOR_TYPE;
    }

    bool IsSingleStep() const override
    {
        return true;
    }
};

class BaseExecutorTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        mockPipelineContext_ = MockPipelineContext::GetCurrent();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
        mockPipelineContext_.Reset();
    }

    void SetUp() override
    {
        WorkflowDumper::GetInstance().logs_.clear();
    }

    void TearDown() override
    {
        WorkflowDumper::GetInstance().logs_.clear();
        auto root = mockPipelineContext_->GetRootElement();
        if (root) {
            root->frameChildren_.clear();
            auto uiChildren = root->GetChildren();
            for (const auto& child : uiChildren) {
                root->RemoveChild(child);
            }
            root->renderContext_ = nullptr;
        }
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_;
};

HWTEST_F(BaseExecutorTest, FindFrameNode_NoNode_LogsNoNodeFound, TestSize.Level1)
{
    TestExecutor executor((WeakPtr<PipelineContext>()));
    auto result = executor.FindFrameNode(TEST_X, TEST_Y, nullptr);

    auto dump = WorkflowDumper::GetInstance().Dump();
    EXPECT_TRUE(dump.find(NO_NODE_FOUND_LOG) != std::string::npos);
    EXPECT_TRUE(dump.find(TEST_EXECUTOR_TYPE) != std::string::npos);
    EXPECT_EQ(result.GetNode(), nullptr);
}

HWTEST_F(BaseExecutorTest, FindFrameNode_WithNode_LogsFoundNode, TestSize.Level1)
{
    mockPipelineContext_->SetupRootElement();
    auto rootNode = mockPipelineContext_->GetRootElement();
    ASSERT_NE(rootNode, nullptr);

    auto rootMockRC = AceType::MakeRefPtr<MockRenderContext>();
    rootNode->renderContext_ = rootMockRC;
    rootMockRC->SetPaintRectWithTransform(RectF(ORIGIN_X, ORIGIN_Y, ROOT_WIDTH, ROOT_HEIGHT));
    EXPECT_CALL(*rootMockRC, GetPointWithTransform(_))
        .WillRepeatedly(DoAll(SetArgReferee<0>(PointF(TEST_X, TEST_Y)), Return()));

    auto childNode = FrameNode::CreateFrameNode(BUTTON_TAG, FRAME_NODE_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(childNode, nullptr);
    childNode->SetActive(true);
    childNode->GetOrCreateGestureEventHub();

    auto childMockRC = AceType::MakeRefPtr<MockRenderContext>();
    childNode->renderContext_ = childMockRC;
    childMockRC->SetPaintRectWithTransform(RectF(ORIGIN_X, ORIGIN_Y, CHILD_WIDTH, CHILD_HEIGHT));
    EXPECT_CALL(*childMockRC, GetPointWithTransform(_))
        .WillRepeatedly(DoAll(SetArgReferee<0>(PointF(TEST_X, TEST_Y)), Return()));

    auto tapGesture = AceType::MakeRefPtr<TapGesture>(FINGER_COUNT, TAP_COUNT);
    auto gestureEventHub = childNode->GetOrCreateGestureEventHub();
    gestureEventHub->AddGesture(tapGesture);
    gestureEventHub->OnModifyDone();

    rootNode->frameChildren_.emplace(childNode);

    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    TestExecutor executor(context);
    ClickRecognizerPred pred;
    auto result = executor.FindFrameNode(TEST_X, TEST_Y, pred);

    auto dump = WorkflowDumper::GetInstance().Dump();
    EXPECT_TRUE(dump.find(FOUND_NODE_LOG) != std::string::npos);
    EXPECT_TRUE(dump.find(TEST_EXECUTOR_TYPE) != std::string::npos);
    EXPECT_NE(result.GetNode(), nullptr);
    ASSERT_NE(result.GetNode(), nullptr);
    EXPECT_EQ(result.GetNode()->GetTag(), BUTTON_TAG);
}

} // namespace OHOS::Ace::NG
