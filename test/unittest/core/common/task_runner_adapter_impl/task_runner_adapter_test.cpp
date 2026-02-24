/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "core/common/task_runner_adapter_impl.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class TaskRunnerAdapterTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: ConvertBarrierOption001
 * @tc.desc: Test ConvertBarrierOption with NO_BARRIER
 * @tc.type: FUNC
 */
HWTEST_F(TaskRunnerAdapterTest, ConvertBarrierOption001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call ConvertBarrierOption with NO_BARRIER
     * @tc.expected: Should return AppExecFwk::VsyncBarrierOption::NO_BARRIER
     */
    auto result = TaskRunnerAdapterImpl::ConvertBarrierOption(VsyncBarrierOption::NO_BARRIER);
    EXPECT_EQ(result, AppExecFwk::VsyncBarrierOption::NO_BARRIER);
}

/**
 * @tc.name: ConvertBarrierOption002
 * @tc.desc: Test ConvertBarrierOption with NEED_BARRIER
 * @tc.type: FUNC
 */
HWTEST_F(TaskRunnerAdapterTest, ConvertBarrierOption002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call ConvertBarrierOption with NEED_BARRIER
     * @tc.expected: Should return AppExecFwk::VsyncBarrierOption::NEED_BARRIER
     */
    auto result = TaskRunnerAdapterImpl::ConvertBarrierOption(VsyncBarrierOption::NEED_BARRIER);
    EXPECT_EQ(result, AppExecFwk::VsyncBarrierOption::NEED_BARRIER);
}

/**
 * @tc.name: ConvertBarrierOption003
 * @tc.desc: Test ConvertBarrierOption with FORCE_BARRIER
 * @tc.type: FUNC
 */
HWTEST_F(TaskRunnerAdapterTest, ConvertBarrierOption003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call ConvertBarrierOption with FORCE_BARRIER
     * @tc.expected: Should return AppExecFwk::VsyncBarrierOption::FORCE_BARRIER
     */
    auto result = TaskRunnerAdapterImpl::ConvertBarrierOption(VsyncBarrierOption::FORCE_BARRIER);
    EXPECT_EQ(result, AppExecFwk::VsyncBarrierOption::FORCE_BARRIER);
}

/**
 * @tc.name: ConvertBarrierOption004
 * @tc.desc: Test that all VsyncBarrierOption enum values map correctly
 * @tc.type: FUNC
 */
HWTEST_F(TaskRunnerAdapterTest, ConvertBarrierOption004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test NO_BARRIER mapping
     * @tc.expected: Should correctly map to AppExecFwk::NO_BARRIER
     */
    EXPECT_EQ(TaskRunnerAdapterImpl::ConvertBarrierOption(VsyncBarrierOption::NO_BARRIER),
              AppExecFwk::VsyncBarrierOption::NO_BARRIER);

    /**
     * @tc.steps: step2. Test NEED_BARRIER mapping
     * @tc.expected: Should correctly map to AppExecFwk::NEED_BARRIER
     */
    EXPECT_EQ(TaskRunnerAdapterImpl::ConvertBarrierOption(VsyncBarrierOption::NEED_BARRIER),
              AppExecFwk::VsyncBarrierOption::NEED_BARRIER);

    /**
     * @tc.steps: step3. Test FORCE_BARRIER mapping
     * @tc.expected: Should correctly map to AppExecFwk::FORCE_BARRIER
     */
    EXPECT_EQ(TaskRunnerAdapterImpl::ConvertBarrierOption(VsyncBarrierOption::FORCE_BARRIER),
              AppExecFwk::VsyncBarrierOption::FORCE_BARRIER);
}

} // namespace OHOS::Ace
