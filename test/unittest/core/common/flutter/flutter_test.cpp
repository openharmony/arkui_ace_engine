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

#define private public
#define protected public
#include "core/common/flutter/flutter_task_executor.h"
#include "core/common/flutter/flutter_window.h"
#include "core/common/flutter/flutter_thread_model.h"

#include "test/mock/core/common/mock_container.h"
#include "core/components/plugin/file_asset_provider.h"
#include "mock_flutter.h"

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
const std::string RET_TEST = "error";
const std::string HAP_PATH = "test";

uint64_t test_result = 2;
int32_t instanceId = 1;
MediaFileInfo FILE_INFO = { .fileName = RET_TEST, .offset = 1, .length = 1, .lastModTime = 1, .lastModDate = 1 };

flutter::TaskRunners MakeTaskRunner()
{
    std::string label = LABEL_TEST;
    std::unique_ptr<fml::Thread> threadFirst = std::make_unique<fml::Thread>(THREAD_FIRST);
    std::unique_ptr<fml::Thread> threadSecond = std::make_unique<fml::Thread>(THREAD_SECOND);
    std::unique_ptr<fml::Thread> threadThird = std::make_unique<fml::Thread>(THREAD_THIRD);
    std::unique_ptr<fml::Thread> threadFourth = std::make_unique<fml::Thread>(THREAD_FOURTH);

    fml::RefPtr<fml::TaskRunner> platform = threadFirst->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> gpu = threadSecond->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> ui = threadThird->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> io = threadFourth->GetTaskRunner();
    flutter::TaskRunners testTaskRunner(label, platform, gpu, ui, io);

    RefPtr<FlutterTaskExecutor> taskExecutor = AceType::MakeRefPtr<FlutterTaskExecutor>(testTaskRunner);
    taskExecutor->InitOtherThreads(testTaskRunner);

    return testTaskRunner;
};

RefPtr<FlutterTaskExecutor> MakeTaskExecutor()
{
    auto taskRunner = MakeTaskRunner();
    RefPtr<FlutterTaskExecutor> taskExecutor = AceType::MakeRefPtr<FlutterTaskExecutor>(taskRunner);

    return taskExecutor;
};
}

class FlutterTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
        auto taskRunner = MakeTaskRunner();
        flutterTaskExecutor_ = AceType::MakeRefPtr<FlutterTaskExecutor>(taskRunner);
    }
    static void TeardownTestSuite()
    {
        MockContainer::TearDown();
    }
    static RefPtr<FlutterTaskExecutor> flutterTaskExecutor_;
};

RefPtr<FlutterTaskExecutor> FlutterTest::flutterTaskExecutor_ = nullptr;

/**
 * @tc.name: Flutter_Task_ExecutorTest01
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Task_ExecutorTest01, TestSize.Level1)
{
    /**
     * @tc.steps2: callback WillRunOnCurrentThread.
     * @tc.expected: The return run thread is false.
     */
    for (int32_t id = 0; id < 7; id++) {
        auto taskType = static_cast<TaskExecutor::TaskType>(id);
        auto result = flutterTaskExecutor_->WillRunOnCurrentThread(taskType);
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
 * @tc.name: Flutter_Task_ExecutorTest02
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Task_ExecutorTest02, TestSize.Level1)
{
    /**
     * @tc.steps2: callback WillRunOnCurrentThread.
     * @tc.expected: The return run thread is task type.
     */
    for (int32_t id = 0; id < 7; id++) {
        auto taskType = static_cast<TaskExecutor::TaskType>(id);
        auto result = flutterTaskExecutor_->WillRunOnCurrentThread(taskType);
        switch (taskType) {
            case TaskExecutor::TaskType::PLATFORM:
                EXPECT_EQ(result, flutterTaskExecutor_->platformRunner_->RunsTasksOnCurrentThread());
                break;
            case TaskExecutor::TaskType::UI:
                EXPECT_EQ(result, flutterTaskExecutor_->uiRunner_->RunsTasksOnCurrentThread());
                break;
            case TaskExecutor::TaskType::IO:
                EXPECT_EQ(result, flutterTaskExecutor_->ioRunner_->RunsTasksOnCurrentThread());
                break;
            case TaskExecutor::TaskType::GPU:
                EXPECT_EQ(result, flutterTaskExecutor_->gpuRunner_->RunsTasksOnCurrentThread());
                break;
            case TaskExecutor::TaskType::JS:
                EXPECT_EQ(result, flutterTaskExecutor_->jsRunner_->RunsTasksOnCurrentThread());
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
 * @tc.name: Flutter_Task_ExecutorTest03
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Task_ExecutorTest03, TestSize.Level1)
{
    /**
     * @tc.steps2: callback InitJsThread push newThread is true.
     * @tc.expected: Return expected results.
     */
    flutterTaskExecutor_->InitJsThread(true);
    EXPECT_EQ(flutterTaskExecutor_->jsRunner_, flutterTaskExecutor_->jsThread_->GetTaskRunner());

    /**
     * @tc.steps3: callback InitJsThread push newThread is false.
     * @tc.expected: Return expected results.
     */
    flutterTaskExecutor_->InitJsThread(false);
    EXPECT_EQ(flutterTaskExecutor_->jsRunner_, flutterTaskExecutor_->uiRunner_);
}

/**
 * @tc.name: Flutter_Task_ExecutorTest04
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Task_ExecutorTest04, TestSize.Level1)
{
    /**
     * @tc.steps2: callback InitPlatformThread push useCurrentEventRunner is true.
     * @tc.expected: Return expected results.
     */
    flutterTaskExecutor_->InitPlatformThread(true);
    EXPECT_EQ(flutterTaskExecutor_->taskTypeTable_.size(), 2);

    /**
     * @tc.steps3: callback InitOtherThreads.
     * @tc.expected: Return expected results.
     */
    flutter::TaskRunners taskRunner = MakeTaskRunner();
    flutterTaskExecutor_->InitOtherThreads(taskRunner);
    EXPECT_EQ(flutterTaskExecutor_->taskTypeTable_.size(), 2);
    EXPECT_EQ(flutterTaskExecutor_->taskTypeTable_.bucket_count(), 2);
}

/**
 * @tc.name: Flutter_Task_ExecutorTest05
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Task_ExecutorTest05, TestSize.Level1)
{
    /**
     * @tc.steps1: Build a flutterTaskExecutor_ object is not null.
     */
    auto taskExecutor = MakeTaskExecutor();
    FlutterTaskExecutor flutterTaskExecutor(taskExecutor);

    /**
     * @tc.steps2: callback InitOtherThreads push threadModel is null..
     * @tc.expected: Return expected results.
     */
    flutterTaskExecutor.InitOtherThreads(nullptr);
    EXPECT_EQ(flutterTaskExecutor.taskTypeTable_.size(), 0);

    /**
     * @tc.steps3: create a threadHost, taskRunner = MakeTaskRunner().
     */
    flutter::ThreadHost threadHost;
    threadHost.platform_thread = std::make_unique<fml::Thread>(THREAD_FIRST);
    threadHost.ui_thread = std::make_unique<fml::Thread>(THREAD_SECOND);
    threadHost.gpu_thread = std::make_unique<fml::Thread>(THREAD_THIRD);
    threadHost.io_thread = std::make_unique<fml::Thread>(THREAD_FOURTH);
    flutter::TaskRunners taskRunner = MakeTaskRunner();

    /**
     * @tc.steps4: callback InitOtherThreads push threadModel is new value.
     * @tc.expected: Return expected results.
     */
    FlutterThreadModel* threadModel = new FlutterThreadModel(std::move(threadHost), taskRunner);
    flutterTaskExecutor.InitOtherThreads(threadModel);
    EXPECT_EQ(flutterTaskExecutor.uiRunner_, taskRunner.GetUITaskRunner());
    EXPECT_EQ(flutterTaskExecutor.ioRunner_, taskRunner.GetIOTaskRunner());
}

/**
 * @tc.name: Flutter_Task_ExecutorTest06
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Task_ExecutorTest06, TestSize.Level1)
{
    /**
     * @tc.steps2: callback FillTaskTypeTable push weak is null..
     * @tc.expected: Return expected results.
     */
    flutterTaskExecutor_->FillTaskTypeTable(nullptr, TaskExecutor::TaskType::UI);
    EXPECT_EQ(flutterTaskExecutor_->taskTypeTable_.size(), 2);

    /**
     * @tc.steps3: callback FillTaskTypeTable push weak is flutterTaskExecutor_->
     * @tc.expected: Return expected results.
     */
    flutterTaskExecutor_->FillTaskTypeTable(flutterTaskExecutor_, TaskExecutor::TaskType::UI);
    EXPECT_EQ(flutterTaskExecutor_->taskTypeTable_.size(), 3);
    EXPECT_EQ(flutterTaskExecutor_->taskTypeTable_.bucket_count(), 5);
}

/**
 * @tc.name: Flutter_Task_ExecutorTest07
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Task_ExecutorTest07, TestSize.Level1)
{
    /**
     * @tc.steps2: Create a callBack task.
     */
    std::string uiTask = "";
    auto callBack = [&uiTask]() {
        uiTask = UISYNCTASK;
    };

    /**
     * @tc.steps3: Set CurrentId_ >= 0.
     * @tc.steps3: call OnPostTask.set asynchronous task.delayTime is 1.
     * @tc.expected: task gets executed.
     */
    for (int32_t id = 0; id < 7; id++) {
        auto taskType = static_cast<TaskExecutor::TaskType>(id);
        auto result = flutterTaskExecutor_->OnPostTask(callBack, taskType, 1, {});
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
 * @tc.name: Flutter_Task_ExecutorTest08
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Task_ExecutorTest08, TestSize.Level1)
{
    /**
     * @tc.steps2: Create a callBack task.
     */
    std::string backgroudTask = "";
    auto callBack = [&backgroudTask]() {
        backgroudTask = BACKGROUNDSYNCTASK;
    };

    /**
     * @tc.steps3: Set CurrentId_ < 0.
     * @tc.steps3: call OnPostTask.set asynchronous task.TaskType is GPU.delayTime is 2.
     * @tc.expected: task gets executed.
     */
    Container::UpdateCurrent(-1);
    flutterTaskExecutor_->OnPostTask(callBack, TaskExecutor::TaskType::BACKGROUND, 2, {});
    EXPECT_EQ(backgroudTask, "");
    sleep(2);
    EXPECT_EQ(backgroudTask, BACKGROUNDSYNCTASK);

    /**
     * @tc.steps4: call WrapTaskWithTraceId.
     * @tc.expected: The return result is true.
     */
    flutterTaskExecutor_->RemoveTaskObserver();
    auto result = flutterTaskExecutor_->WrapTaskWithTraceId(callBack, 1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Flutter_Thread_Model01
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Thread_Model01, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a threadHost, taskRunner = MakeTaskRunner().
     * @tc.steps1: New a threadModel with threadHost and taskRunner.
     */
    flutter::ThreadHost threadHost;
    threadHost.platform_thread = std::make_unique<fml::Thread>(THREAD_FIRST);
    threadHost.ui_thread = std::make_unique<fml::Thread>(THREAD_SECOND);
    threadHost.gpu_thread = std::make_unique<fml::Thread>(THREAD_THIRD);
    threadHost.io_thread = std::make_unique<fml::Thread>(THREAD_FOURTH);
    flutter::TaskRunners taskRunner = MakeTaskRunner();
    FlutterThreadModel* threadModel = new FlutterThreadModel(std::move(threadHost), taskRunner);

    /**
     * @tc.steps2: call CreateThreadModel push hasUiThread is true useGpuThread is false.
     * @tc.expected: return expected results.
     */
    auto test_taskRunner = threadModel->taskRunners_;
    threadModel->CreateThreadModel(true, true, false);
    EXPECT_TRUE(test_taskRunner.GetUITaskRunner());

    /**
     * @tc.steps3: call CreateThreadModel, push hasUiThread is false useGpuThread is true.
     * @tc.expected: return expected results.
     */
    threadModel->CreateThreadModel(true, false, true);
    EXPECT_TRUE(test_taskRunner.GetGPUTaskRunner());
}

/**
 * @tc.name: Flutter_Asset_Manager01
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Asset_Manager01, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a flutterAssetManager.
     */
    auto flutterAssetManager = AceType::MakeRefPtr<FlutterAssetManager>();
    std::vector<std::string> assetList;

    /**
     * @tc.steps2: call GetAsset input assetName is "".
     * @tc.expected: The expected result is null.
     */
    auto result = flutterAssetManager->GetAsset("");
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps3: call PushBack with fileAssetProvider.
     * @tc.steps3: call GetAsset input assetName is RET_TEST.
     * @tc.expected: The expected result is null.
     */
    auto fileAssetProvider = AceType::MakeRefPtr<Plugin::FileAssetProvider>();
    flutterAssetManager->PushBack(std::move(fileAssetProvider));
    auto ass_Result = flutterAssetManager->GetAsset(RET_TEST);
    EXPECT_EQ(ass_Result, nullptr);

    /**
     * @tc.steps4: call GetAssetPath input providers_ is Default value.
     * @tc.expected: The expected result is null.
     */
    std::string path_Result = flutterAssetManager->GetAssetPath(RET_TEST, true);
    EXPECT_EQ(path_Result, "");

    /**
     * @tc.steps5: call GetAssetList input assetName is RET_TEST.
     * @tc.expected: The assetList.empty().
     */
    flutterAssetManager->GetAssetList(RET_TEST, assetList);
    EXPECT_TRUE(assetList.empty());

    /**
     * @tc.steps6: call GetFileInfo input providers_ is Default value.
     * @tc.expected: The expected result is false.
     */
    bool info_Result = flutterAssetManager->GetFileInfo(RET_TEST, FILE_INFO);
    EXPECT_FALSE(info_Result);
    flutterAssetManager->ReloadProvider();
}

/**
 * @tc.name: Flutter_Asset_Manager02
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Asset_Manager02, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a flutterAssetManager.
     */
    auto flutterAssetManager = AceType::MakeRefPtr<FlutterAssetManager>();

    /**
     * @tc.steps2: Create a MockFileAssetProvider.
     * @tc.steps2: call PushBack with MockFileAssetProvider.
     */
    auto mockAssetProvider = AceType::MakeRefPtr<MockFileAssetProvider>();
    EXPECT_CALL(*mockAssetProvider, IsValid()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*mockAssetProvider, GetAssetPath(RET_TEST, true)).Times(1).WillOnce(Return(HAP_PATH));
    flutterAssetManager->PushBack(std::move(mockAssetProvider));

    /**
     * @tc.steps3: call GetAssetPath input assetName is RET_TEST.
     * @tc.expected: The expected result is HAP_PATH.
     */
    std::string path_Result = flutterAssetManager->GetAssetPath(RET_TEST, true);
    EXPECT_EQ(path_Result, "test");

    /**
     * @tc.steps4: call GetAssetPath input assetName is RET_TEST.
     * @tc.expected: The expected result is true.
     * @tc.steps5: call ReloadProvider.
     */
    bool result = flutterAssetManager->GetFileInfo(RET_TEST, FILE_INFO);
    EXPECT_TRUE(result);
    flutterAssetManager->ReloadProvider();
}

/**
 * @tc.name: Flutter_Asset_Manager03
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_Asset_Manager03, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a flutterAssetManager.
     */
    auto flutterAssetManager = AceType::MakeRefPtr<FlutterAssetManager>();

    /**
     * @tc.steps2: Create a MockFileAssetProvider.
     * @tc.steps2: call PushBack with MockFileAssetProvider.
     */
    auto mockAssetProvider = AceType::MakeRefPtr<MockFileAssetProvider>();
    EXPECT_CALL(*mockAssetProvider, IsValid()).Times(1).WillOnce(Return(true));
    flutterAssetManager->PushBack(std::move(mockAssetProvider));

    /**
     * @tc.steps3: call GetAsset input assetName is RET_TEST.
     * @tc.expected: The expected result is not null.
     * @tc.steps4: call ReloadProvider.
     */
    auto ass_Result = flutterAssetManager->GetAsset(RET_TEST);
    ASSERT_NE(ass_Result, nullptr);
    flutterAssetManager->ReloadProvider();
}

/**
 * @tc.name: Flutter_window01
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_window01, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a flutterWindow object.
     */
    Platform::FlutterWindow flutterWindow(instanceId);
    auto* testview = new FlutterAssetManager();

    /**
     * @tc.steps2: call Create with nullptr.
     * @tc.expected: expected Return result_one is null.
     */
    auto result_one = flutterWindow.Create(nullptr);
    EXPECT_EQ(result_one, nullptr);

    /**
     * @tc.steps3: Create a MockContainer.call GetView Return testview
     * @tc.steps3: Create a nativeView.
     */
    auto container = AceType::MakeRefPtr<MockContainer>();
    EXPECT_CALL(*container, GetView()).Times(1).WillOnce(Return(testview));
    auto nativeView = static_cast<AceView*>(container->GetView());

    /**
     * @tc.steps3: call Create with nativeView.
     * @tc.expected: expected Return result_two is not null.
     */
    auto result_two = flutterWindow.Create(nativeView);
    ASSERT_NE(result_two, nullptr);

    /**
     * @tc.steps3: callback Destroy.
     * @tc.expected: Return expected results..
     */
    flutterWindow.Destroy();
    EXPECT_EQ(flutterWindow.vsyncCallbacks_.size(), 0);
}

/**
 * @tc.name: Flutter_window02
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_window02, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a flutterWindow object.
     */
    Platform::FlutterWindow flutterWindow(instanceId);

    /**
     * @tc.steps2: call RequestFrame and SetRootRenderNode.
     * @tc.expected: Return expected results..
     */
    flutterWindow.RequestFrame();
    flutterWindow.SetRootRenderNode(nullptr);
    EXPECT_EQ(flutterWindow.instanceId_, 1);
}

/**
 * @tc.name: Flutter_window03
 * @tc.desc: Test the operation of flutter
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, Flutter_window03, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a flutterWindow object.
     */
    Platform::FlutterWindow flutterWindow(instanceId);

    /**
     * @tc.steps2: callback RegisterVsyncCallback.
     * @tc.expected: Return expected results..
     */
    auto callback = [](uint64_t timestamp, uint32_t frameCount) {
        test_result = timestamp;
    };
    flutterWindow.RegisterVsyncCallback(callback);
    EXPECT_EQ(test_result, 2);

    /**
     * @tc.steps3: call OnVsyncCallback with 5.
     * @tc.expected: expected results test_result = 5.
     */
    flutterWindow.OnVsyncCallback(5);
    EXPECT_EQ(test_result, 5);
}
} // namespace OHOS::Ace
