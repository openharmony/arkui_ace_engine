/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "core/common/watch_dog.h"
#include "base/test/mock/mock_task_executor.h"
#include "base/thread/task_executor.h"
#include "base/memory/referenced.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const int32_t INSTANCE_ID = 777;
RefPtr<MockTaskExecutor> MOCK_TASK_EXECUTOR;
} // namespace

class WatchDogTest : public testing::Test {
public:
static void SetUpTestCase();
static void TearDownTestCase(){}
void SetUp() {}
void TearDown() {}
};
void WatchDogTest::SetUpTestCase(){
    MOCK_TASK_EXECUTOR = AceType::MakeRefPtr<MockTaskExecutor>();
}

/**
 * @tc.name: Register01
 * @tc.desc: Verify the Register Interface of WatchDog work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(WatchDogTest, Register01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build an WatchDog.
     */
    WatchDog watchDog_;

    /**
     * @tc.steps: step2. Register Executor.
     * @tc.expected: Register Executor success;
     * @tc.steps: step2. Unregister Executor.
     * @tc.expected: Unregister Executor success;
     */
    watchDog_.Register(INSTANCE_ID, MOCK_TASK_EXECUTOR, true);
    EXPECT_EQ(watchDog_.watchMap_[INSTANCE_ID].jsWatcher, nullptr);
    watchDog_.Unregister(INSTANCE_ID);
    watchDog_.Unregister(INSTANCE_ID);
    EXPECT_TRUE(watchDog_.watchMap_.empty());

    /**
     * @tc.steps: step2. Register Executor with useUIAsJSThread = false.
     * @tc.expected: Register Executor success;
     */
    watchDog_.Register(INSTANCE_ID, MOCK_TASK_EXECUTOR, false);
    watchDog_.Register(INSTANCE_ID, MOCK_TASK_EXECUTOR, false);
    EXPECT_NE(watchDog_.watchMap_[INSTANCE_ID].jsWatcher, nullptr);
}

} // namespace OHOS::Ace
