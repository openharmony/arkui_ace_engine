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
#include "core/common/event_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/relaxed_interaction/executors/smart_gesture_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SmartGestureExecutorTest : public testing::Test {
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

class SmartGestureExecutorConstructorTest : public SmartGestureExecutorTest {};
class SmartGestureExecutorExecuteStepTest : public SmartGestureExecutorTest {};
class SmartGestureExecutorGetTypeTest : public SmartGestureExecutorTest {};
class SmartGestureExecutorGetDescriptionTest : public SmartGestureExecutorTest {};
class SmartGestureExecutorIsSingleStepTest : public SmartGestureExecutorTest {};

// Constructor tests
HWTEST_F(SmartGestureExecutorConstructorTest, Constructor_TapTrigger, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::TAP);
    EXPECT_EQ(executor.context_, context);
}

HWTEST_F(SmartGestureExecutorConstructorTest, Constructor_SlideForwardTrigger, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::SLIDE_FORWARD);
    EXPECT_EQ(executor.context_, context);
}

HWTEST_F(SmartGestureExecutorConstructorTest, Constructor_WristBackTrigger, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::WRIST_BACK);
    EXPECT_EQ(executor.context_, context);
}

HWTEST_F(SmartGestureExecutorConstructorTest, Constructor_NullContext, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    SmartGestureExecutor executor(nullContext, SmartGestureTrigger::TAP);
    EXPECT_EQ(executor.context_, nullContext);
}

// ExecuteStep tests
HWTEST_F(SmartGestureExecutorExecuteStepTest, ExecuteStep_NullContext_ReturnsFailed, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    SmartGestureExecutor executor(nullContext, SmartGestureTrigger::TAP);
    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(SmartGestureExecutorExecuteStepTest, ExecuteStep_NoSmartGestureManager_ReturnsFailed, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::TAP);
    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

// GetType tests
HWTEST_F(SmartGestureExecutorGetTypeTest, GetType_ReturnsSmartGesture, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::TAP);
    auto type = executor.GetType();
    EXPECT_EQ(type, "smart_gesture");
}

HWTEST_F(SmartGestureExecutorGetTypeTest, GetType_ReturnsSmartGesture_SlideForward, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::SLIDE_FORWARD);
    auto type = executor.GetType();
    EXPECT_EQ(type, "smart_gesture");
}

// GetDescription tests
HWTEST_F(SmartGestureExecutorGetDescriptionTest, GetDescription_ContainsTypeAndSingleStep, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::TAP);
    auto desc = executor.GetDescription();
    EXPECT_TRUE(desc.find("smart_gesture") != std::string::npos);
    EXPECT_TRUE(desc.find("true") != std::string::npos);
}

// IsSingleStep tests
HWTEST_F(SmartGestureExecutorIsSingleStepTest, IsSingleStep_ReturnsTrue_Tap, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::TAP);
    EXPECT_TRUE(executor.IsSingleStep());
}

HWTEST_F(SmartGestureExecutorIsSingleStepTest, IsSingleStep_ReturnsTrue_SlideForward, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::SLIDE_FORWARD);
    EXPECT_TRUE(executor.IsSingleStep());
}

HWTEST_F(SmartGestureExecutorIsSingleStepTest, IsSingleStep_ReturnsTrue_WristBack, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::WRIST_BACK);
    EXPECT_TRUE(executor.IsSingleStep());
}

HWTEST_F(SmartGestureExecutorExecuteStepTest, ExecuteStep_NullEventManager_ReturnsFailed, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    mockPipelineContext_->eventManager_.Reset();
    SmartGestureExecutor executor(context, SmartGestureTrigger::TAP);
    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
    mockPipelineContext_->SetEventManager(AceType::MakeRefPtr<EventManager>());
}

HWTEST_F(SmartGestureExecutorExecuteStepTest, ExecuteStep_SmartGestureManagerNull_ReturnsFailed, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::TAP);
    auto eventManager = mockPipelineContext_->GetEventManager();
    if (eventManager) {
        eventManager->smartGestureManager_.Reset();
    }
    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(SmartGestureExecutorExecuteStepTest, ExecuteStep_HandleTriggerReturnsFalse_ReturnsFailed, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::TAP);
    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(SmartGestureExecutorExecuteStepTest, ExecuteStep_AllTriggers_FailedBranchCoverage, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    SmartGestureExecutor executorTap(nullContext, SmartGestureTrigger::TAP);
    SmartGestureExecutor executorSlide(nullContext, SmartGestureTrigger::SLIDE_FORWARD);
    SmartGestureExecutor executorWrist(nullContext, SmartGestureTrigger::WRIST_BACK);

    EXPECT_EQ(executorTap.ExecuteStep(), ExecutorResult::FAILED);
    EXPECT_EQ(executorSlide.ExecuteStep(), ExecutorResult::FAILED);
    EXPECT_EQ(executorWrist.ExecuteStep(), ExecutorResult::FAILED);
}

HWTEST_F(SmartGestureExecutorConstructorTest, Constructor_TriggerStoredCorrectly, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executorTap(context, SmartGestureTrigger::TAP);
    SmartGestureExecutor executorSlide(context, SmartGestureTrigger::SLIDE_FORWARD);
    SmartGestureExecutor executorWrist(context, SmartGestureTrigger::WRIST_BACK);

    EXPECT_EQ(executorTap.trigger_, SmartGestureTrigger::TAP);
    EXPECT_EQ(executorSlide.trigger_, SmartGestureTrigger::SLIDE_FORWARD);
    EXPECT_EQ(executorWrist.trigger_, SmartGestureTrigger::WRIST_BACK);
}

HWTEST_F(SmartGestureExecutorGetDescriptionTest, GetDescription_ReturnsBaseDescription, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executor(context, SmartGestureTrigger::TAP);
    auto desc = executor.GetDescription();
    EXPECT_TRUE(desc.find("smart_gesture") != std::string::npos);
    EXPECT_TRUE(desc.find("true") != std::string::npos);
}

HWTEST_F(SmartGestureExecutorGetDescriptionTest, GetDescription_DifferentTriggers_ReturnsSameType, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    SmartGestureExecutor executorTap(context, SmartGestureTrigger::TAP);
    SmartGestureExecutor executorSlide(context, SmartGestureTrigger::SLIDE_FORWARD);
    SmartGestureExecutor executorWrist(context, SmartGestureTrigger::WRIST_BACK);

    EXPECT_EQ(executorTap.GetType(), executorSlide.GetType());
    EXPECT_EQ(executorSlide.GetType(), executorWrist.GetType());
}

} // namespace OHOS::Ace::NG
