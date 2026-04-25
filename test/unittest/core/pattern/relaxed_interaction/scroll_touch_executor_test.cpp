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

#include "base/geometry/ng/point_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/relaxed_interaction/executors/scroll_touch_executor.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ScrollTouchExecutorTest : public testing::Test {
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

class ScrollTouchExecutorConstructorTest : public ScrollTouchExecutorTest {};
class ScrollTouchExecuteStepTest : public ScrollTouchExecutorTest {};
class ScrollTouchExecuteGetTypeTest : public ScrollTouchExecutorTest {};
class ScrollTouchExecuteGetDescriptionTest : public ScrollTouchExecutorTest {};
class ScrollTouchExecuteIsSingleStepTest : public ScrollTouchExecutorTest {};

HWTEST_F(ScrollTouchExecutorConstructorTest, StrictClickExecutor_Constructor_LargeCoordinates, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 100.0;
    tmpCmd.actionInfo.coordinates.y1 = 100.0;
    tmpCmd.actionInfo.coordinates.x2 = 120.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    ScrollTouchExecutor executor(context, tmpCmd);

    EXPECT_FLOAT_EQ(executor.cmd_.actionInfo.coordinates.x1, 100.0f);
    EXPECT_FLOAT_EQ(executor.cmd_.actionInfo.coordinates.y1, 100.0f);
    EXPECT_FLOAT_EQ(executor.cmd_.actionInfo.coordinates.x2, 120.0f);
    EXPECT_FLOAT_EQ(executor.cmd_.actionInfo.coordinates.y2, 700.0f);
}

HWTEST_F(ScrollTouchExecuteStepTest, ExecuteStep_NullContext_ReturnsFailed, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 0.0;
    tmpCmd.actionInfo.coordinates.y1 = 0.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    ScrollTouchExecutor executor(nullContext, tmpCmd);

    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(ScrollTouchExecuteStepTest, ExecuteStep_NoFrameNodeFound_ReturnsFailed, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 0.0;
    tmpCmd.actionInfo.coordinates.y1 = 0.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
    ScrollTouchExecutor executor(context, tmpCmd);

    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(ScrollTouchExecuteGetTypeTest, GetType_ReturnsStrictClick, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 60.0;
    tmpCmd.actionInfo.coordinates.y1 = 60.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
    ScrollTouchExecutor executor(context, tmpCmd);

    auto type = executor.GetType();
    EXPECT_EQ(type, "scroll_touch");
}

HWTEST_F(ScrollTouchExecuteGetTypeTest, GetType_ReturnsSameValueForDifferentCoordinates, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 60.0;
    tmpCmd.actionInfo.coordinates.y1 = 60.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::BACKWARD;

    Command tmpCmd0;
    tmpCmd0.type = "scroll";
    tmpCmd0.mode = ExecuteMode::TARGET;
    tmpCmd0.actionInfo.distance = 1200.0;
    tmpCmd0.actionInfo.coordinates.x1 = 60.0;
    tmpCmd0.actionInfo.coordinates.y1 = 60.0;
    tmpCmd0.actionInfo.coordinates.x2 = 60.0;
    tmpCmd0.actionInfo.coordinates.y2 = 700.0;
    tmpCmd0.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
    ScrollTouchExecutor executor1(context, tmpCmd);
    ScrollTouchExecutor executor2(context, tmpCmd0);

    EXPECT_EQ(executor1.GetType(), executor2.GetType());
}

HWTEST_F(ScrollTouchExecuteGetDescriptionTest, GetDescription_ReturnsNonEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 60.0;
    tmpCmd.actionInfo.coordinates.y1 = 60.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
    ScrollTouchExecutor executor(context, tmpCmd);

    auto description = executor.GetDescription();
    EXPECT_FALSE(description.empty());
    EXPECT_TRUE(description.find("touch") != std::string::npos);
}

HWTEST_F(ScrollTouchExecuteGetDescriptionTest, GetDescription_ContainsExpectedKeywords, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 60.0;
    tmpCmd.actionInfo.coordinates.y1 = 60.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
    ScrollTouchExecutor executor(context, tmpCmd);

    auto description = executor.GetDescription();
    EXPECT_TRUE(description.find("scroll") != std::string::npos);
    EXPECT_TRUE(description.find("touch") != std::string::npos);
}

HWTEST_F(ScrollTouchExecuteIsSingleStepTest, IsSingleStep_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 60.0;
    tmpCmd.actionInfo.coordinates.y1 = 60.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
    ScrollTouchExecutor executor(context, tmpCmd);

    auto isSingleStep = executor.IsSingleStep();
    EXPECT_TRUE(isSingleStep);
}

HWTEST_F(ScrollTouchExecuteIsSingleStepTest, IsSingleStep_ReturnsTrueForDifferentCoordinates, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);

    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 60.0;
    tmpCmd.actionInfo.coordinates.y1 = 60.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
	
    Command tmpCmd0;
    tmpCmd0.type = "scroll";
    tmpCmd0.mode = ExecuteMode::TARGET;
    tmpCmd0.actionInfo.distance = 1200.0;
    tmpCmd0.actionInfo.coordinates.x1 = 30.0;
    tmpCmd0.actionInfo.coordinates.y1 = 120.0;
    tmpCmd0.actionInfo.coordinates.x2 = 30.0;
    tmpCmd0.actionInfo.coordinates.y2 = 700.0;
    tmpCmd0.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
    ScrollTouchExecutor executor1(context, tmpCmd);
    ScrollTouchExecutor executor2(context, tmpCmd0);

    EXPECT_TRUE(executor1.IsSingleStep());
    EXPECT_TRUE(executor2.IsSingleStep());
}

} // namespace OHOS::Ace::NG
