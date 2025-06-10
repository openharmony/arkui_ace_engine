/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "vector"
#include "base/ressched/ressched_report.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
} // namespace

class ResSchedReportTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
    }
    static void TearDownTestSuite()
    {
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: ResSchedReportTest001
 * @tc.desc: CurrentId
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedReportTest, ResSchedReportTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get currentId from initial env
     * @tc.expected: CurrentId equals the value in initial env
     */
    int32_t scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, INSTANCE_ID_PLATFORM);

    /**
     * @tc.steps: step2. Update currentId and get it
     * @tc.expected: CurrentId equals updated value
     */
    ContainerScope::UpdateCurrent(TEST_INSTANCE_ID_CONTAINER);
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, TEST_INSTANCE_ID_CONTAINER);

    ContainerScope::UpdateCurrent(TEST_INSTANCE_ID_SUB_CONTAINER);
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, TEST_INSTANCE_ID_SUB_CONTAINER);
}
} // namespace OHOS::Ace
