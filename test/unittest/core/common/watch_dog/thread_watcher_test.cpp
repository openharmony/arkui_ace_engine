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
#include "base/test/mock/mock_task_executor.h"
#include "base/thread/task_executor.h"
#include "core/common/watch_dog.h"
#include "base/memory/referenced.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const int32_t INSTANCE_ID = 777;
const TaskExecutor::TaskType TASK_TYPE1 = TaskExecutor::TaskType::JS;
const TaskExecutor::TaskType TASK_TYPE2 = TaskExecutor::TaskType::UI;
const TaskExecutor::TaskType TASK_TYPE = TaskExecutor::TaskType::UNKNOWN;
constexpr char JS_THREAD_NAME[] = "JS";
constexpr char UI_THREAD_NAME[] = "UI";
constexpr char UNKNOWN_THREAD_NAME[] = "unknown thread";
const uint64_t BOMB_ID = 10000;
RefPtr<MockTaskExecutor> MOCK_TASK_EXECUTOR;
} // namespace

class ThreadWatcherTest : public testing::Test {
public:
static void SetUpTestCase();
static void TearDownTestCase(){}
void SetUp() {}
void TearDown() {}
};
void ThreadWatcherTest::SetUpTestCase(){
    MOCK_TASK_EXECUTOR = AceType::MakeRefPtr<MockTaskExecutor>();
};

/**
 * @tc.name: SetTaskExecutor01
 * @tc.desc: Verify the SetTaskExecutor Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, SetTaskExecutor01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_(INSTANCE_ID, TASK_TYPE, false);

    /**
     * @tc.steps: step2. SetTaskExecutor.
     * @tc.expected: SetTaskExecutor success.
     */
    threadWatcher_.SetTaskExecutor(MOCK_TASK_EXECUTOR);
    EXPECT_EQ(threadWatcher_.taskExecutor_, MOCK_TASK_EXECUTOR);
}

/**
 * @tc.name: BuriedBomb01
 * @tc.desc: Verify the BuriedBomb Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, BuriedBomb01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_(INSTANCE_ID, TASK_TYPE, false);

    /**
     * @tc.steps: step2. BuriedBomb.
     * @tc.expected: BuriedBomb success.
     */
    threadWatcher_.BuriedBomb(BOMB_ID);
    EXPECT_EQ(threadWatcher_.inputTaskIds_.back(), BOMB_ID);

    /**
     * @tc.steps: step3. DefusingTopBomb.
     * @tc.expected: DefusingTopBomb success.
     */
    threadWatcher_.DefusingTopBomb();
    EXPECT_TRUE(threadWatcher_.inputTaskIds_.empty());
}

/**
 * @tc.name: InitThreadName01
 * @tc.desc: Verify the InitThreadName Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, InitThreadName01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_1(INSTANCE_ID, TASK_TYPE, false);

    /**
     * @tc.steps: step2. InitThreadName.
     * @tc.expected: InitThreadName success.
     */
    threadWatcher_1.InitThreadName();
    EXPECT_EQ(threadWatcher_1.threadName_, UNKNOWN_THREAD_NAME);

    /**
     * @tc.steps: step3. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_2(INSTANCE_ID, TASK_TYPE1, false);

    /**
     * @tc.steps: step4. InitThreadName.
     * @tc.expected: InitThreadName success.
     */
    threadWatcher_2.InitThreadName();
    EXPECT_EQ(threadWatcher_2.threadName_, JS_THREAD_NAME);

    /**
     * @tc.steps: step5. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_3(INSTANCE_ID, TASK_TYPE2, false);

    /**
     * @tc.steps: step6. InitThreadName.
     * @tc.expected: InitThreadName success.
     */
    threadWatcher_3.InitThreadName();
    EXPECT_EQ(threadWatcher_3.threadName_, UI_THREAD_NAME);
}

/**
 * @tc.name: CheckAndResetIfNeeded01
 * @tc.desc: Verify the CheckAndResetIfNeeded Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, CheckAndResetIfNeeded01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_(INSTANCE_ID, TASK_TYPE, false);
    threadWatcher_.loopTime_ = 10;

    /**
     * @tc.steps: step2. CheckAndResetIfNeeded.
     * @tc.expected: CheckAndResetIfNeeded success.
     */
    threadWatcher_.CheckAndResetIfNeeded();
    EXPECT_EQ(threadWatcher_.loopTime_, 10);

    /**
     * @tc.steps: step3. Set loopTime_ with INT32_MAX.
     * @tc.steps: step3. CheckAndResetIfNeeded.
     * @tc.expected: CheckAndResetIfNeeded success.
     */
    threadWatcher_.loopTime_ = INT32_MAX;
    threadWatcher_.CheckAndResetIfNeeded();
    EXPECT_EQ(threadWatcher_.loopTime_, 0);
}

/**
 * @tc.name: IsThreadStuck01
 * @tc.desc: Verify the IsThreadStuck Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, IsThreadStuck01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_(INSTANCE_ID, TASK_TYPE, false);

    /**
     * @tc.steps: step2. SetTaskExecutor.
     * @tc.steps: step2. IsThreadStuck.
     * @tc.expected: step2 return true.
     */
    threadWatcher_.SetTaskExecutor(MOCK_TASK_EXECUTOR);
    threadWatcher_.loopTime_ = 10;
    threadWatcher_.threadTag_ = 8;
    threadWatcher_.lastLoopTime_ = 9;
    threadWatcher_.lastThreadTag_ = 8;
    threadWatcher_.lastTaskId_ = 10;
    EXPECT_TRUE(threadWatcher_.IsThreadStuck());

    /**
     * @tc.steps: step2. Change lastTaskId.
     * @tc.steps: step2. IsThreadStuck.
     * @tc.expected: step2 return false.
     */
    threadWatcher_.loopTime_ = 10;
    threadWatcher_.threadTag_ = 8;
    threadWatcher_.lastLoopTime_ = 9;
    threadWatcher_.lastThreadTag_ = 8;
    threadWatcher_.lastTaskId_ = 15;
    EXPECT_FALSE(threadWatcher_.IsThreadStuck());
}

/**
 * @tc.name: TagIncrease01
 * @tc.desc: Verify the TagIncrease Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, TagIncrease01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_(INSTANCE_ID, TASK_TYPE, false);

    /**
     * @tc.steps: step2. TagIncrease.
     * @tc.expected: TagIncrease success.
     */
    threadWatcher_.threadTag_ = 10;
    threadWatcher_.TagIncrease();
    EXPECT_EQ(threadWatcher_.threadTag_, 11);
}

/**
 * @tc.name: Check01
 * @tc.desc: Verify the Check Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, Check01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_(INSTANCE_ID, TASK_TYPE, false);

    /**
     * @tc.steps: step2. SetTaskExecutor.
     * @tc.steps: step2. Check.
     * @tc.expected: Check success.
     */
    threadWatcher_.SetTaskExecutor(MOCK_TASK_EXECUTOR);
    threadWatcher_.loopTime_ = 10;
    threadWatcher_.threadTag_ = 8;
    threadWatcher_.lastLoopTime_ = 9;
    threadWatcher_.lastThreadTag_ = 8;
    threadWatcher_.lastTaskId_ = 15;
    threadWatcher_.Check();
    EXPECT_EQ(threadWatcher_.freezeCount_, 0);
    EXPECT_EQ(threadWatcher_.state_, State::NORMAL);
    EXPECT_TRUE(threadWatcher_.canShowDialog_);
    EXPECT_EQ(threadWatcher_.showDialogCount_, 0);
}

/**
 * @tc.name: Check02
 * @tc.desc: Verify the Check Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, Check02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_(INSTANCE_ID, TASK_TYPE, false);

    /**
     * @tc.steps: step2. SetTaskExecutor.
     * @tc.steps: step2. Check.
     * @tc.expected: Check success.
     */
    threadWatcher_.SetTaskExecutor(MOCK_TASK_EXECUTOR);
    threadWatcher_.loopTime_ = 10;
    threadWatcher_.threadTag_ = 8;
    threadWatcher_.lastLoopTime_ = 9;
    threadWatcher_.lastThreadTag_ = 8;
    threadWatcher_.lastTaskId_ = 10;
    threadWatcher_.state_ = State::NORMAL;
    threadWatcher_.Check();
    EXPECT_EQ(threadWatcher_.state_, State::WARNING);
}

/**
 * @tc.name: Check03
 * @tc.desc: Verify the Check Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, Check03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_(INSTANCE_ID, TASK_TYPE, false);

    /**
     * @tc.steps: step2. SetTaskExecutor.
     * @tc.steps: step2. Check.
     * @tc.expected: Check success.
     */
    threadWatcher_.SetTaskExecutor(MOCK_TASK_EXECUTOR);
    threadWatcher_.loopTime_ = 10;
    threadWatcher_.threadTag_ = 8;
    threadWatcher_.lastLoopTime_ = 9;
    threadWatcher_.lastThreadTag_ = 8;
    threadWatcher_.lastTaskId_ = 10;
    threadWatcher_.state_ = State::WARNING;
    threadWatcher_.Check();
    EXPECT_EQ(threadWatcher_.state_, State::FREEZE);
}

/**
 * @tc.name: Check04
 * @tc.desc: Verify the Check Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, Check04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_(INSTANCE_ID, TASK_TYPE, false);

    /**
     * @tc.steps: step2. SetTaskExecutor.
     * @tc.steps: step2. Check.
     * @tc.expected: Check success.
     */
    threadWatcher_.SetTaskExecutor(MOCK_TASK_EXECUTOR);
    threadWatcher_.loopTime_ = 10;
    threadWatcher_.threadTag_ = 8;
    threadWatcher_.lastLoopTime_ = 9;
    threadWatcher_.lastThreadTag_ = 8;
    threadWatcher_.lastTaskId_ = 10;
    threadWatcher_.state_ = State::FREEZE;
    threadWatcher_.canShowDialog_ = false;
    threadWatcher_.showDialogCount_ = 5;
    threadWatcher_.freezeCount_ = 10;
    threadWatcher_.Check();
    EXPECT_EQ(threadWatcher_.showDialogCount_, 6);
    EXPECT_EQ(threadWatcher_.freezeCount_, 0);
}

/**
 * @tc.name: Check05
 * @tc.desc: Verify the Check Interface of ThreadWatcher work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadWatcherTest, Check05, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a ThreadWatcher.
     */
    ThreadWatcher threadWatcher_(INSTANCE_ID, TASK_TYPE, false);

    /**
     * @tc.steps: step2. SetTaskExecutor.
     * @tc.steps: step2. Check.
     * @tc.expected: Check success.
     */
    threadWatcher_.SetTaskExecutor(MOCK_TASK_EXECUTOR);
    threadWatcher_.loopTime_ = 10;
    threadWatcher_.threadTag_ = 8;
    threadWatcher_.lastLoopTime_ = 9;
    threadWatcher_.lastThreadTag_ = 8;
    threadWatcher_.lastTaskId_ = 10;
    threadWatcher_.state_ = State::FREEZE;
    threadWatcher_.canShowDialog_ = false;
    threadWatcher_.showDialogCount_ = 20;
    threadWatcher_.Check();
    EXPECT_EQ(threadWatcher_.showDialogCount_, 0);
    EXPECT_TRUE(threadWatcher_.canShowDialog_);
}


} // namespace OHOS::Ace
