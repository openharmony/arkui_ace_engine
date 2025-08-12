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

#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/animation/callback_thread_wrapper.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
RefPtr<TaskExecutor> taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
} // namespace

class CallbackThreadWrapperTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: CallbackThreadWrapperTest001
 * @tc.desc: Test once is true
 * @tc.type: FUNC
 */
HWTEST_F(CallbackThreadWrapperTest, CallbackThreadWrapperTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CallbackThreadWrapper whose once param is true.
     */
    int32_t cnt = 0;
    std::function func = [&cnt]() {
        cnt++;
    };
    CallbackThreadWrapper wrapper1(taskExecutor_, func, true);

    /**
     * @tc.steps: step2. Execute () function for the first time.
     * @tc.expected: The wrapped function will be executed.
     */
    wrapper1();
    ASSERT_EQ(cnt, 1);

    /**
     * @tc.steps: step3. Execute () function for the second time.
     * @tc.expected: The wrapped function will not be executed, so the number keeps same.
     */
    wrapper1();
    ASSERT_EQ(cnt, 1);
}

/**
 * @tc.name: CallbackThreadWrapperTest002
 * @tc.desc: Test once is false
 * @tc.type: FUNC
 */
HWTEST_F(CallbackThreadWrapperTest, CallbackThreadWrapperTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CallbackThreadWrapper whose once param is false.
     */
    int32_t cnt = 0;
    std::function func = [&cnt]() {
        cnt++;
    };
    CallbackThreadWrapper wrapper1(taskExecutor_, func, false);

    /**
     * @tc.steps: step2. Execute () function for the first time.
     * @tc.expected: The wrapped function will be executed.
     */
    wrapper1();
    ASSERT_EQ(cnt, 1);

    /**
     * @tc.steps: step3. Execute () function for four times again.
     * @tc.expected: The wrapped function will be executed for four times.
     */
    constexpr int32_t repeatTimes = 4;
    for (int32_t i = 0; i != repeatTimes; ++i) {
        wrapper1();
    }
    ASSERT_EQ(cnt, 1 + repeatTimes);
}

/**
 * @tc.name: CallbackThreadWrapperTest003
 * @tc.desc: Test the struct destruction
 * @tc.type: FUNC
 */
HWTEST_F(CallbackThreadWrapperTest, CallbackThreadWrapperTest003, TestSize.Level1)
{
    int32_t cnt = 0;
    std::function func = [&cnt]() {
        cnt++;
    };
    /**
     * @tc.steps: step1. Create CallbackThreadWrapper and destruct it.
     */
    {
        CallbackThreadWrapper wrapper1(taskExecutor_, func, false);
        CallbackThreadWrapper wrapper2(taskExecutor_, func, true);
    }
    /**
     * @tc.steps: step2. Test the result.
     * @tc.expected: The wrapped function will not be executed when it destructs.
     */
    ASSERT_EQ(cnt, 0);
}
} // namespace OHOS::Ace::NG
