/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "core/common/thread_checker.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class ThreadCheckerTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ThreadCheckerTest::SetUpTestSuite()
{
    MockContainer::SetUp();
}

void ThreadCheckerTest::TearDownTestSuite()
{
    MockContainer::TearDown();
}

/**
 * @tc.name: ThreadCheckerGetThread
 * @tc.desc: Test cast to ThreadCheckerTest
 * @tc.type: FUNC
 */
HWTEST_F(ThreadCheckerTest, ThreadCheckerGetThread, TestSize.Level1)
{
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    EXPECT_FALSE(CheckThread(TaskExecutor::TaskType::PLATFORM));
    EXPECT_TRUE(CheckThread(TaskExecutor::TaskType::UI));
    RefPtr<Container> conainer = Container::Current();
    conainer->SetUseNewPipeline();
    EXPECT_EQ(Container::IsCurrentUseNewPipeline(), true);
    EXPECT_TRUE(CheckThread(TaskExecutor::TaskType::JS));
}
} // namespace OHOS::Ace
