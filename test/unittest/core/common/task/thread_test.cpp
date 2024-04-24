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

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"

#include "core/common/task_executor_impl.h"
#include "core/common/task_runner_adapter.h"
#include "core/common/task_runner_adapter_factory.h"
#include "core/common/task_runner_adapter_impl.h"
#include "core/common/task_runners.h"
#include "core/common/thread_container.h"
#include "core/common/thread_model_impl.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const std::string UISYNCTASK = "ui task has executed";
const std::string BACKGROUNDSYNCTASK = "background task has executed";
const std::string LABEL_TEST = "task executor";
const std::string THREAD_FIRST = "thread_first";
const std::string THREAD_SECOND = "thread_second";
const std::string THREAD_THIRD = "thread_third";
const std::string THREAD_FOURTH = "thread_fourth";

TaskRunners MakeTaskRunner()
{
    std::string label = LABEL_TEST;
    RefPtr<TaskRunnerAdapter> platform = TaskRunnerAdapterFactory::Create(false, THREAD_FIRST);
    RefPtr<TaskRunnerAdapter> gpu = TaskRunnerAdapterFactory::Create(false, THREAD_SECOND);
    RefPtr<TaskRunnerAdapter> ui = TaskRunnerAdapterFactory::Create(false, THREAD_THIRD);
    RefPtr<TaskRunnerAdapter> io = TaskRunnerAdapterFactory::Create(false, THREAD_FOURTH);
    TaskRunners testTaskRunner(label, platform, gpu, ui, io);

    RefPtr<TaskExecutorImpl> taskExecutor = AceType::MakeRefPtr<TaskExecutorImpl>(testTaskRunner);
    taskExecutor->InitOtherThreads(testTaskRunner);
    return testTaskRunner;
};

RefPtr<TaskExecutorImpl> MakeTaskExecutor()
{
    auto taskRunner = MakeTaskRunner();
    RefPtr<TaskExecutorImpl> taskExecutor = AceType::MakeRefPtr<TaskExecutorImpl>(taskRunner);

    return taskExecutor;
};
} // namespace

class ThreadTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
        auto taskRunner = MakeTaskRunner();
        taskExecutorImpl_ = AceType::MakeRefPtr<TaskExecutorImpl>(taskRunner);
    }
    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
    }
    static RefPtr<TaskExecutorImpl> taskExecutorImpl_;
};

RefPtr<TaskExecutorImpl> ThreadTest::taskExecutorImpl_ = nullptr;

/**
 * @tc.name: Task_Executor_ImplTest01
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Task_Executor_ImplTest01, TestSize.Level1)
{
    /**
     * @tc.steps1: set the taskType.
     * @tc.steps2: callback WillRunOnCurrentThread.
     * @tc.expected: The return run thread is false.
     */
    for (int32_t id = 0; id < 7; id++) {
        auto taskType = static_cast<TaskExecutor::TaskType>(id);
        auto result = taskExecutorImpl_->WillRunOnCurrentThread(taskType);
        switch (taskType) {
            case TaskExecutor::TaskType::PLATFORM:
            case TaskExecutor::TaskType::UI:
            case TaskExecutor::TaskType::IO:
            case TaskExecutor::TaskType::GPU:
            case TaskExecutor::TaskType::JS:
            case TaskExecutor::TaskType::BACKGROUND:
                EXPECT_FALSE(result);
                break;
            default:
                EXPECT_FALSE(result);
        }
    }
}

/**
 * @tc.name: Task_Executor_ImplTest02
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Task_Executor_ImplTest02, TestSize.Level1)
{
    /**
     * @tc.steps1: set the taskType.
     * @tc.steps2: callback WillRunOnCurrentThread.
     * @tc.expected: The return run thread is task type.
     */
    for (int32_t id = 0; id < 7; id++) {
        auto taskType = static_cast<TaskExecutor::TaskType>(id);
        auto result = taskExecutorImpl_->WillRunOnCurrentThread(taskType);
        switch (taskType) {
            case TaskExecutor::TaskType::PLATFORM:
                EXPECT_EQ(result, taskExecutorImpl_->platformRunner_->RunsTasksOnCurrentThread());
                break;
            case TaskExecutor::TaskType::UI:
                EXPECT_EQ(result, taskExecutorImpl_->uiRunner_->RunsTasksOnCurrentThread());
                break;
            case TaskExecutor::TaskType::IO:
                EXPECT_EQ(result, taskExecutorImpl_->ioRunner_->RunsTasksOnCurrentThread());
                break;
            case TaskExecutor::TaskType::GPU:
                EXPECT_EQ(result, taskExecutorImpl_->gpuRunner_->RunsTasksOnCurrentThread());
                break;
            case TaskExecutor::TaskType::JS:
                EXPECT_EQ(result, taskExecutorImpl_->jsRunner_->RunsTasksOnCurrentThread());
                break;
            case TaskExecutor::TaskType::BACKGROUND:
                EXPECT_FALSE(result);
                break;
            default:
                EXPECT_FALSE(result);
        }
    }
}

/**
 * @tc.name: Task_Executor_ImplTest03
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Task_Executor_ImplTest03, TestSize.Level1)
{
    /**
     * @tc.steps1: callback FillTaskTypeTable push weak is null..
     * @tc.expected: Return expected results.
     */
    taskExecutorImpl_->FillTaskTypeTable(nullptr, TaskExecutor::TaskType::UI);
    EXPECT_EQ(taskExecutorImpl_->taskTypeTable_.size(), 0);
}

/**
 * @tc.name: Task_Executor_ImplTest04
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Task_Executor_ImplTest04, TestSize.Level1)
{
    /**
     * @tc.steps1: callback InitPlatformThread push useCurrentEventRunner is true.
     * @tc.expected: Return expected results.
     */
    taskExecutorImpl_->InitPlatformThread(true);
    EXPECT_EQ(taskExecutorImpl_->taskTypeTable_.size(), 1);
}

/**
 * @tc.name: Task_Executor_ImplTest05
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Task_Executor_ImplTest05, TestSize.Level1)
{
    /**
     * @tc.steps1: taskRunner = MakeTaskRunner().
     * @tc.steps2: callback InitOtherThreads using taskRunner
     * @tc.expected: Return expected results.
     */
    TaskRunners taskRunner = MakeTaskRunner();
    taskExecutorImpl_->InitOtherThreads(taskRunner);
    sleep(1);
    EXPECT_EQ(taskExecutorImpl_->taskTypeTable_.size(), 4);
    EXPECT_EQ(taskExecutorImpl_->taskTypeTable_.bucket_count(), 5);
}

/**
 * @tc.name: Task_Executor_ImplTest06
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Task_Executor_ImplTest06, TestSize.Level1)
{
    /**
     * @tc.steps1: callback InitJsThread push newThread is false.
     * @tc.expected: Return expected results.
     */
    taskExecutorImpl_->InitJsThread(false);
    EXPECT_EQ(taskExecutorImpl_->jsRunner_, taskExecutorImpl_->uiRunner_);
}

/**
 * @tc.name: Task_Executor_ImplTest07
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Task_Executor_ImplTest07, TestSize.Level1)
{
    /**
     * @tc.steps3: callback FillTaskTypeTable push weak is taskExecutorImpl_
     * @tc.expected: Return expected results.
     */
    taskExecutorImpl_->FillTaskTypeTable(taskExecutorImpl_, TaskExecutor::TaskType::UI);
    EXPECT_EQ(taskExecutorImpl_->taskTypeTable_.bucket_count(), 5);
}

/**
 * @tc.name: Task_Executor_ImplTest08
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Task_Executor_ImplTest08, TestSize.Level1)
{
    /**
     * @tc.steps1: Build a taskExecutorImpl_ object is not null.
     */
    auto taskExecutor = MakeTaskExecutor();
    TaskExecutorImpl taskExecutorImpl(taskExecutor);

    /**
     * @tc.steps2: callback InitOtherThreads push threadModel is null..
     * @tc.expected: Return expected results.
     */
    taskExecutorImpl.InitOtherThreads(nullptr);
    EXPECT_EQ(taskExecutorImpl.taskTypeTable_.size(), 0);

    /**
     * @tc.steps3: create a threadContainer, taskRunner = MakeTaskRunner().
     */
    ThreadContainer threadContainer;
    threadContainer.platformThread = TaskRunnerAdapterFactory::Create(false, THREAD_FIRST);
    threadContainer.uiThread = TaskRunnerAdapterFactory::Create(false, THREAD_SECOND);
    threadContainer.gpuThread = TaskRunnerAdapterFactory::Create(false, THREAD_THIRD);
    threadContainer.ioThread = TaskRunnerAdapterFactory::Create(false, THREAD_FOURTH);
    TaskRunners taskRunner = MakeTaskRunner();

    /**
     * @tc.steps4: callback InitOtherThreads push threadModel is new value.
     * @tc.expected: Return expected results.
     */
    ThreadModelImpl* threadModel = new ThreadModelImpl(std::move(threadContainer), taskRunner);
    taskExecutorImpl.InitOtherThreads(threadModel);
    EXPECT_EQ(taskExecutorImpl.uiRunner_, taskRunner.GetUITaskRunner());
    EXPECT_EQ(taskExecutorImpl.ioRunner_, taskRunner.GetIOTaskRunner());
}

/**
 * @tc.name: Task_Executor_ImplTest09
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Task_Executor_ImplTest09, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a callBack task.
     */
    std::string uiTask = "";
    auto callBack = [&uiTask]() { uiTask = UISYNCTASK; };

    /**
     * @tc.steps2: Set CurrentId_ >= 0.
     * @tc.steps3: call OnPostTask.set asynchronous task.delayTime is 1.
     * @tc.expected: task gets executed.
     */
    for (int32_t id = 0; id < 7; id++) {
        auto taskType = static_cast<TaskExecutor::TaskType>(id);
        auto result = taskExecutorImpl_->OnPostTask(callBack, taskType, 1, "ArkUITask");
        switch (taskType) {
            case TaskExecutor::TaskType::PLATFORM:
            case TaskExecutor::TaskType::UI:
            case TaskExecutor::TaskType::IO:
            case TaskExecutor::TaskType::GPU:
            case TaskExecutor::TaskType::JS:
            case TaskExecutor::TaskType::BACKGROUND:
                EXPECT_TRUE(result);
                break;
            case TaskExecutor::TaskType::UNKNOWN:
                EXPECT_FALSE(result);
                break;
            default:
                EXPECT_FALSE(result);
        }
    }
}

/**
 * @tc.name: Task_Executor_ImplTest10
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Task_Executor_ImplTest10, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a callBack task.
     */
    std::string backgroudTask = "";
    auto callBack = [&backgroudTask]() { backgroudTask = BACKGROUNDSYNCTASK; };

    /**
     * @tc.steps2: Set CurrentId_ < 0.
     * @tc.steps3: call OnPostTask.set asynchronous task.TaskType is GPU.delayTime is 2.
     * @tc.expected: task gets executed.
     */
    Container::UpdateCurrent(-1);
    taskExecutorImpl_->OnPostTask(callBack, TaskExecutor::TaskType::BACKGROUND, 2, "ArkUITask");
    EXPECT_EQ(backgroudTask, "");
    sleep(2);
    EXPECT_EQ(backgroudTask, BACKGROUNDSYNCTASK);

    /**
     * @tc.steps4: call WrapTaskWithTraceId.
     * @tc.expected: The return result is true.
     */
    taskExecutorImpl_->RemoveTaskObserver();
    auto result = taskExecutorImpl_->WrapTaskWithTraceId(callBack, 1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Thread_Model_Impl01
 * @tc.desc: Test the operation of thread
 * @tc.type: FUNC
 */
HWTEST_F(ThreadTest, Thread_Model_Impl01, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a threadContainer, taskRunner = MakeTaskRunner().
     * @tc.steps2: New a threadModel with threadContainer and taskRunner.
     */
    ThreadContainer threadContainer;
    threadContainer.platformThread = TaskRunnerAdapterFactory::Create(false, THREAD_FIRST);
    threadContainer.uiThread = TaskRunnerAdapterFactory::Create(false, THREAD_SECOND);
    threadContainer.gpuThread = TaskRunnerAdapterFactory::Create(false, THREAD_THIRD);
    threadContainer.ioThread = TaskRunnerAdapterFactory::Create(false, THREAD_FOURTH);
    TaskRunners taskRunner = MakeTaskRunner();
    ThreadModelImpl* threadModel = new ThreadModelImpl(std::move(threadContainer), taskRunner);

    /**
     * @tc.steps3: call CreateThreadModel push hasUiThread is true useGpuThread is false.
     * @tc.expected: return expected results.
     */
    auto test_taskRunner = threadModel->taskRunners_;
    threadModel->CreateThreadModel(true, true, false);
    EXPECT_TRUE(test_taskRunner.GetUITaskRunner());

    /**
     * @tc.steps4: call CreateThreadModel, push hasUiThread is false useGpuThread is true.
     * @tc.expected: return expected results.
     */
    threadModel->CreateThreadModel(true, false, true);
    EXPECT_TRUE(test_taskRunner.GetGPUTaskRunner());
}
} // namespace OHOS::Ace
