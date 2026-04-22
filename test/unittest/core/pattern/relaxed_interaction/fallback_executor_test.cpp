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
#include "core/components_ng/relaxed_interaction/executors/fallback_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class FallbackExecutorTest : public testing::Test {
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

class FallbackExecutorConstructorTest : public FallbackExecutorTest {};
class FallbackExecutorExecuteStepTest : public FallbackExecutorTest {};
class FallbackExecutorGetTypeTest : public FallbackExecutorTest {};
class FallbackExecutorIsSingleStepTest : public FallbackExecutorTest {};

HWTEST_F(FallbackExecutorConstructorTest, FallbackExecutor_Constructor_Radio1_True, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    std::string body = "{\"cmd\":\"checked\",\"params\":{\"value\":true}";
    FallbackExecutor executor(context, 69, body);
    EXPECT_EQ(executor.context_, context);
}

HWTEST_F(FallbackExecutorConstructorTest, FallbackExecutor_Constructor_Radio2_True, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    std::string body = "{\"cmd\":\"checked\",\"params\":{\"value\":true}";
    FallbackExecutor executor(context, 70, body);
    EXPECT_EQ(executor.context_, context);
}

HWTEST_F(FallbackExecutorConstructorTest, FallbackExecutor_Constructor_Radio1_False, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    std::string body = "{\"cmd\":\"checked\",\"params\":{\"value\":false}";
    FallbackExecutor executor(context, 69, body);
    EXPECT_EQ(executor.context_, context);
}

HWTEST_F(FallbackExecutorConstructorTest, FallbackExecutorx_Constructor_Radio1_False, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    std::string body = "{\"cmd\":\"checked\",\"params\":{\"value\":false}";
    FallbackExecutor executor(context, 70, body);
    EXPECT_EQ(executor.context_, context);
}

HWTEST_F(FallbackExecutorConstructorTest, FallbackExecutor_Constructor_NullBody, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackExecutor executor(context, 69, "");
    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(FallbackExecutorExecuteStepTest, ExecuteStep_NullContext_ReturnsFailed, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    std::string body = "{\"cmd\":\"checked\",\"params\":{\"value\":false}";
    FallbackExecutor executor(nullContext, 69, body);

    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(FallbackExecutorExecuteStepTest, ExecuteStep_NoFrameNodeFound_ReturnsFailed, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    std::string body = "{\"cmd\":\"checked\",\"params\":{\"value\":false}";
    FallbackExecutor executor(context, 9999, body);

    auto result = executor.ExecuteStep();
    EXPECT_EQ(result, ExecutorResult::FAILED);
}

HWTEST_F(FallbackExecutorGetTypeTest, GetType_ReturnsFallback, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    std::string body = "{\"cmd\":\"checked\",\"params\":{\"value\":false}";
    FallbackExecutor executor(context, 69, body);

    auto type = executor.GetType();
    EXPECT_EQ(type, "fallback");
}

HWTEST_F(FallbackExecutorIsSingleStepTest, IsSingleStep_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    std::string body = "{\"cmd\":\"checked\",\"params\":{\"value\":false}";
    FallbackExecutor executor(context, 69, body);

    auto isSingleStep = executor.IsSingleStep();
    EXPECT_TRUE(isSingleStep);
}

} // namespace OHOS::Ace::NG