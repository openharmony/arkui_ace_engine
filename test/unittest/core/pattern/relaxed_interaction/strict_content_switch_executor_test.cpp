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

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/relaxed_interaction/executors/strict_content_switch_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class StrictContentSwitchExecutorTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        mockPipelineContext_ = AceType::MakeRefPtr<MockPipelineContext>();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        mockPipelineContext_.Reset();
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_ = nullptr;
};

class StrictContentSwitchExecutorConstructorTest : public StrictContentSwitchExecutorTest {};
class StrictContentSwitchExecutorExecuteStepTest : public StrictContentSwitchExecutorTest {};
class StrictContentSwitchExecutorGetTypeTest : public StrictContentSwitchExecutorTest {};
class StrictContentSwitchExecutorIsSingleStepTest : public StrictContentSwitchExecutorTest {};

HWTEST_F(StrictContentSwitchExecutorConstructorTest, StrictContentSwitchExecutor_Constructor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates(100.0f, 200.0f);
    StrictContentSwitchExecutor executor(context, "target", "forward", 1, coordinates);
    EXPECT_EQ(executor.context_, context);
    EXPECT_FLOAT_EQ(executor.coordinates_.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(executor.coordinates_.GetY(), 200.0f);
}

HWTEST_F(StrictContentSwitchExecutorConstructorTest, StrictContentSwitchExecutor_Constructor_ZeroCoordinates,
    TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates(0.0f, 0.0f);
    StrictContentSwitchExecutor executor(context, "target", "forward", 1, coordinates);
    EXPECT_FLOAT_EQ(executor.coordinates_.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(executor.coordinates_.GetY(), 0.0f);
}

HWTEST_F(StrictContentSwitchExecutorConstructorTest, StrictContentSwitchExecutor_Constructor_NegativeCoordinates,
    TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates(-100.0f, -200.0f);
    StrictContentSwitchExecutor executor(context, "target", "forward", 1, coordinates);
    EXPECT_FLOAT_EQ(executor.coordinates_.GetX(), -100.0f);
    EXPECT_FLOAT_EQ(executor.coordinates_.GetY(), -200.0f);
}

HWTEST_F(StrictContentSwitchExecutorConstructorTest, StrictContentSwitchExecutor_Constructor_LargeCoordinates,
    TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates(10000.0f, 20000.0f);
    StrictContentSwitchExecutor executor(context, "target", "forward", 1, coordinates);
    EXPECT_FLOAT_EQ(executor.coordinates_.GetX(), 10000.0f);
    EXPECT_FLOAT_EQ(executor.coordinates_.GetY(), 20000.0f);
}

HWTEST_F(StrictContentSwitchExecutorExecuteStepTest, ExecuteStep_NullContext_ReturnsFailed, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    PointF coordinates(100.0f, 200.0f);
    StrictContentSwitchExecutor executor(nullContext, "target", "forward", 1, coordinates);

    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(StrictContentSwitchExecutorExecuteStepTest, ExecuteStep_NoFrameNodeFound_ReturnsFailed, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates(100.0f, 200.0f);
    StrictContentSwitchExecutor executor(context, "target", "forward", 1, coordinates);

    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(StrictContentSwitchExecutorGetTypeTest, GetType_ReturnsStrictContentSwitch, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates(100.0f, 200.0f);
    StrictContentSwitchExecutor executor(context, "target", "forward", 1, coordinates);

    auto type = executor.GetType();
    EXPECT_EQ(type, "strict_content_switch");
}

HWTEST_F(StrictContentSwitchExecutorGetTypeTest, GetType_ReturnsSameValueForDifferentCoordinates, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates1(100.0f, 200.0f);
    PointF coordinates2(300.0f, 400.0f);
    StrictContentSwitchExecutor executor1(context, "target", "forward", 1, coordinates1);
    StrictContentSwitchExecutor executor2(context, "target", "forward", 1, coordinates2);

    EXPECT_EQ(executor1.GetType(), executor2.GetType());
}

HWTEST_F(StrictContentSwitchExecutorIsSingleStepTest, IsSingleStep_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates(100.0f, 200.0f);
    StrictContentSwitchExecutor executor(context, "target", "forward", 1, coordinates);

    auto isSingleStep = executor.IsSingleStep();
    EXPECT_TRUE(isSingleStep);
}

HWTEST_F(StrictContentSwitchExecutorIsSingleStepTest, IsSingleStep_ReturnsTrueForDifferentCoordinates, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates1(100.0f, 200.0f);
    PointF coordinates2(300.0f, 400.0f);
    StrictContentSwitchExecutor executor1(context, "target", "forward", 1, coordinates1);
    StrictContentSwitchExecutor executor2(context, "target", "forward", 1, coordinates2);

    EXPECT_TRUE(executor1.IsSingleStep());
    EXPECT_TRUE(executor2.IsSingleStep());
}

HWTEST_F(StrictContentSwitchExecutorExecuteStepTest, ExecuteStep_InvalidMode_ReturnsFailed, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates(100.0f, 200.0f);
    StrictContentSwitchExecutor executor(context, "auto", "forward", 1, coordinates);

    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(StrictContentSwitchExecutorExecuteStepTest, ExecuteStep_InvalidDirection_ReturnsFailed, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates(100.0f, 200.0f);
    StrictContentSwitchExecutor executor(context, "target", "left", 1, coordinates);

    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(StrictContentSwitchExecutorExecuteStepTest, ExecuteStep_InvalidCount_ReturnsFailed, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    PointF coordinates(100.0f, 200.0f);
    StrictContentSwitchExecutor executor(context, "target", "forward", -1, coordinates);

    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}
} // namespace OHOS::Ace::NG