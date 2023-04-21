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
#include "core/common/flutter/flutter_asset_manager.h"
#include "core/common/flutter/flutter_task_executor.h"
#include "core/common/flutter/flutter_window.h"
#undef private
#undef protected
#include "test/mock/core/common/mock_container.h"
#include "core/components/plugin/file_asset_provider.h"
#include "core/pipeline/base/render_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
    const std::string UITASK = "ui task has executed";
    const std::string UISYNCTASK = "ui sync task has executed";
    const std::string PLATFORMTASK = "platform task has executed";
    const std::string PLATFORMSYNCTASK = "platform sync task has executed";
    const std::string IOTASK = "io task has executed";
    const std::string IOSYNCTASK = "io sync task has executed";
    const std::string GPUTASK = "gpu task has executed";
    const std::string GPUSYNCTASK = "gpu sync task has executed";
    const std::string JSTASK = "js task has executed";
    const std::string JSSYNCTASK = "js sync task has executed";
    const std::string BACKGROUNDTASK = "background task has executed";
    const std::string BACKGROUNDSYNCTASK = "background sync task has executed";
    const std::string LABEL = "task executor";
    const std::string THREADFIRST = "thread_1";
    const std::string THREADSECOND = "thread_2";
    const std::string THREADTHIRD = "thread_3";
    const std::string THREADFOURTH = "thread_4";
    uint64_t g_result = 0;
    int32_t instanceId = 1;
    const std::string RET_TEST = "error";
} // namespace

// namespace
class FlutterTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: CastToFlutterTest001
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object is null.
     * @tc.steps: step2. callback WillRunOnCurrentThread.
     * @tc.expected: step2. The return run thread is false.
     */
    FlutterTaskExecutor object;

    auto test_platform = object.WillRunOnCurrentThread(TaskExecutor::TaskType::PLATFORM);
    EXPECT_FALSE(test_platform);
    auto test_ui = object.WillRunOnCurrentThread(TaskExecutor::TaskType::UI);
    EXPECT_FALSE(test_ui);
    auto test_io = object.WillRunOnCurrentThread(TaskExecutor::TaskType::IO);
    EXPECT_FALSE(test_io);
    auto test_gpu = object.WillRunOnCurrentThread(TaskExecutor::TaskType::GPU);
    EXPECT_FALSE(test_gpu);
    auto test_js = object.WillRunOnCurrentThread(TaskExecutor::TaskType::JS);
    EXPECT_FALSE(test_js);
    auto test_backgroud = object.WillRunOnCurrentThread(TaskExecutor::TaskType::BACKGROUND);
    EXPECT_FALSE(test_backgroud);
    auto test_unknown = object.WillRunOnCurrentThread(TaskExecutor::TaskType::UNKNOWN);
    EXPECT_FALSE(test_unknown);
}

/**
 * @tc.name: CastToFlutterTest002
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest002, TestSize.Level1)
{
    std::string label = LABEL;
    std::unique_ptr<fml::Thread> ThreadFirst = std::make_unique<fml::Thread>(THREADFIRST);
    std::unique_ptr<fml::Thread> ThreadSecond = std::make_unique<fml::Thread>(THREADSECOND);
    std::unique_ptr<fml::Thread> ThreadThird = std::make_unique<fml::Thread>(THREADTHIRD);
    std::unique_ptr<fml::Thread> ThreadFourth = std::make_unique<fml::Thread>(THREADFOURTH);
    fml::RefPtr<fml::TaskRunner> platform = ThreadFirst->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> gpu = ThreadSecond->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> ui = ThreadThird->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> io = ThreadFourth->GetTaskRunner();
    flutter::TaskRunners taskRunner(label, platform, gpu, ui, io);
    RefPtr<FlutterTaskExecutor> taskExecutor = AceType::MakeRefPtr<FlutterTaskExecutor>(taskRunner);

    /**
     * @tc.steps: step1. Build a object is not null.
     * @tc.steps: step2. callback WillRunOnCurrentThread.
     * @tc.expected: step2. The return run thread is task type.
     */
    FlutterTaskExecutor object(taskExecutor);
    auto test_platform = object.WillRunOnCurrentThread(TaskExecutor::TaskType::PLATFORM);
    auto platformRun = object.platformRunner_->RunsTasksOnCurrentThread();
    EXPECT_EQ(test_platform, platformRun);

    auto test_ui = object.WillRunOnCurrentThread(TaskExecutor::TaskType::UI);
    auto uiRun = object.uiRunner_->RunsTasksOnCurrentThread();
    EXPECT_EQ(test_ui, uiRun);

    auto test_io = object.WillRunOnCurrentThread(TaskExecutor::TaskType::IO);
    auto ioRun = object.ioRunner_->RunsTasksOnCurrentThread();
    EXPECT_EQ(test_io, ioRun);

    auto test_gpu = object.WillRunOnCurrentThread(TaskExecutor::TaskType::GPU);
    auto gpuRun = object.gpuRunner_->RunsTasksOnCurrentThread();
    EXPECT_EQ(test_gpu, gpuRun);

    auto test_js = object.WillRunOnCurrentThread(TaskExecutor::TaskType::JS);
    auto jsRun = object.jsRunner_->RunsTasksOnCurrentThread();
    EXPECT_EQ(test_js, jsRun);
}

/**
 * @tc.name: CastToFlutterTest003
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest003, TestSize.Level1)
{
    std::string label = LABEL;
    std::unique_ptr<fml::Thread> ThreadFirst = std::make_unique<fml::Thread>(THREADFIRST);
    std::unique_ptr<fml::Thread> ThreadSecond = std::make_unique<fml::Thread>(THREADSECOND);
    std::unique_ptr<fml::Thread> ThreadThird = std::make_unique<fml::Thread>(THREADTHIRD);
    std::unique_ptr<fml::Thread> ThreadFourth = std::make_unique<fml::Thread>(THREADFOURTH);
    fml::RefPtr<fml::TaskRunner> platform = ThreadFirst->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> gpu = ThreadSecond->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> ui = ThreadThird->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> io = ThreadFourth->GetTaskRunner();
    flutter::TaskRunners taskRunner(label, platform, gpu, ui, io);
    RefPtr<FlutterTaskExecutor> taskExecutor = AceType::MakeRefPtr<FlutterTaskExecutor>(taskRunner);

    /**
     * @tc.steps: step1. Build a object is not null.
     * @tc.steps: step2. callback InitJsThread.
     * @tc.expected: step2. Return expected results.
     */
    FlutterTaskExecutor object(taskExecutor);
    taskExecutor->InitJsThread(true);
    EXPECT_EQ(object.jsRunner_, object.jsThread_->GetTaskRunner());
    taskExecutor->InitJsThread(false);
    EXPECT_NE(object.jsRunner_, object.uiRunner_);
}

/**
 * @tc.name: CastToFlutterTest004
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest004, TestSize.Level1)
{
    std::string label = LABEL;
    std::unique_ptr<fml::Thread> ThreadFirst = std::make_unique<fml::Thread>(THREADFIRST);
    std::unique_ptr<fml::Thread> ThreadSecond = std::make_unique<fml::Thread>(THREADSECOND);
    std::unique_ptr<fml::Thread> ThreadThird = std::make_unique<fml::Thread>(THREADTHIRD);
    std::unique_ptr<fml::Thread> ThreadFourth = std::make_unique<fml::Thread>(THREADFOURTH);
    fml::RefPtr<fml::TaskRunner> platform = ThreadFirst->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> gpu = ThreadSecond->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> ui = ThreadThird->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> io = ThreadFourth->GetTaskRunner();
    flutter::TaskRunners taskRunner(label, platform, gpu, ui, io);
    RefPtr<FlutterTaskExecutor> taskExecutor = AceType::MakeRefPtr<FlutterTaskExecutor>(taskRunner);

    /**
     * @tc.steps: step1. callback InitPlatformThread.
     * @tc.expected: step1. Return expected results.
     */
    FlutterTaskExecutor object(taskExecutor);
    taskExecutor->InitPlatformThread(true);
    EXPECT_EQ(object.taskTypeTable_.size(), 0);
}

/**
 * @tc.name: CastToFlutterTest005
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest005, TestSize.Level1)
{
    std::string label = LABEL;
    std::unique_ptr<fml::Thread> ThreadFirst = std::make_unique<fml::Thread>(THREADFIRST);
    std::unique_ptr<fml::Thread> ThreadSecond = std::make_unique<fml::Thread>(THREADSECOND);
    std::unique_ptr<fml::Thread> ThreadThird = std::make_unique<fml::Thread>(THREADTHIRD);
    std::unique_ptr<fml::Thread> ThreadFourth = std::make_unique<fml::Thread>(THREADFOURTH);
    fml::RefPtr<fml::TaskRunner> platform = ThreadFirst->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> gpu = ThreadSecond->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> ui = ThreadThird->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> io = ThreadFourth->GetTaskRunner();
    flutter::TaskRunners taskRunner(label, platform, gpu, ui, io);
    RefPtr<FlutterTaskExecutor> taskExecutor = AceType::MakeRefPtr<FlutterTaskExecutor>(taskRunner);

    /**
     * @tc.steps: step1. callback InitOtherThreads.
     * @tc.expected: step1. Return expected results.
     */
    FlutterTaskExecutor object(taskExecutor);
    taskExecutor->InitOtherThreads(taskRunner);
    EXPECT_EQ(object.taskTypeTable_.size(), 0);
    EXPECT_EQ(object.taskTypeTable_.bucket_count(), 0);

    /**
     * @tc.steps: step2. callback FillTaskTypeTable.
     * @tc.expected: step2. Return expected results.
     */
    object.FillTaskTypeTable(taskExecutor, TaskExecutor::TaskType::UI);
    EXPECT_EQ(object.taskTypeTable_.size(), 0);

    object.FillTaskTypeTable(TaskExecutor::TaskType::UI);
    EXPECT_EQ(object.taskTypeTable_.size(), 1);
    EXPECT_EQ(object.taskTypeTable_.bucket_count(), 2);
    FlutterTaskExecutor::ThreadInfo info = object.taskTypeTable_[TaskExecutor::TaskType::UI];
    EXPECT_EQ(info.threadName, "flutter_test");
}

/**
 * @tc.name: CastToFlutterTest006
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest006, TestSize.Level1)
{
    std::string label = LABEL;
    std::unique_ptr<fml::Thread> ThreadFirst = std::make_unique<fml::Thread>(THREADFIRST);
    std::unique_ptr<fml::Thread> ThreadSecond = std::make_unique<fml::Thread>(THREADSECOND);
    std::unique_ptr<fml::Thread> ThreadThird = std::make_unique<fml::Thread>(THREADTHIRD);
    std::unique_ptr<fml::Thread> ThreadFourth = std::make_unique<fml::Thread>(THREADFOURTH);
    fml::RefPtr<fml::TaskRunner> platform = ThreadFirst->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> gpu = ThreadSecond->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> ui = ThreadThird->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> io = ThreadFourth->GetTaskRunner();
    flutter::TaskRunners taskRunner(label, platform, gpu, ui, io);
    RefPtr<FlutterTaskExecutor> taskExecutor = AceType::MakeRefPtr<FlutterTaskExecutor>(taskRunner);
    FlutterTaskExecutor object(taskExecutor);

    /**
     * @tc.steps: step1. callback OnPostTask.set asynchronous task.TaskType is UI.
     * @tc.expected: step1. task gets executed.
     */
    std::string uiTask;
    bool uiTest = object.OnPostTask([&uiTask]() { uiTask = UISYNCTASK; }, TaskExecutor::TaskType::UI, 2);
    EXPECT_TRUE(uiTest);
    EXPECT_NE(uiTask, UISYNCTASK);
    sleep(2);
    EXPECT_EQ(uiTask, UISYNCTASK);

    /**
     * @tc.steps: step2. set asynchronous task.TaskType is PLATFORM.
     * @tc.expected: step2. task gets executed.
     */
    std::string platformTask;
    bool platformTest = object.OnPostTask([&platformTask]() { platformTask = PLATFORMSYNCTASK; },
        TaskExecutor::TaskType::PLATFORM, 2);
    EXPECT_TRUE(platformTest);
    EXPECT_NE(platformTask, PLATFORMSYNCTASK);
    sleep(2);
    EXPECT_EQ(platformTask, PLATFORMSYNCTASK);

    /**
     * @tc.steps: step3. set asynchronous task.TaskType is IO.
     * @tc.expected: step3. task gets executed.
     */
    std::string ioTask;
    bool ioTest = object.OnPostTask([&ioTask]() { ioTask = IOSYNCTASK; }, TaskExecutor::TaskType::IO, 2);
    EXPECT_TRUE(ioTest);
    EXPECT_NE(ioTask, IOSYNCTASK);
    sleep(2);
    EXPECT_EQ(ioTask, IOSYNCTASK);

    /**
     * @tc.steps: step4. set asynchronous task.TaskType is GPU.
     * @tc.expected: step4. task gets executed.
     */
    std::string gpuTask;
    bool gpuTest = object.OnPostTask([&gpuTask]() { gpuTask = GPUSYNCTASK; }, TaskExecutor::TaskType::GPU, 2);
    EXPECT_TRUE(gpuTest);
    EXPECT_NE(gpuTask, GPUSYNCTASK);
    sleep(2);
    EXPECT_EQ(gpuTask, GPUSYNCTASK);

    /**
     * @tc.steps: step5. set asynchronous task.TaskType is JS.
     * @tc.expected: step5. task gets executed.
     */
    std::string jsTask;
    bool jsTest = object.OnPostTask([&jsTask]() { jsTask = JSSYNCTASK; }, TaskExecutor::TaskType::JS, 2);
    EXPECT_TRUE(jsTest);
    EXPECT_NE(jsTask, JSSYNCTASK);
    sleep(2);
    EXPECT_EQ(jsTask, JSSYNCTASK);

    /**
     * @tc.steps: step6. set asynchronous task.TaskType is UNKNOWN.
     * @tc.expected: step6. The expected result is false.
     */
    bool result = object.OnPostTask([] () {}, TaskExecutor::TaskType::UNKNOWN, 2);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CastToFlutterTest007
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     */
    std::string label = LABEL;
    std::unique_ptr<fml::Thread> ThreadFirst = std::make_unique<fml::Thread>(THREADFIRST);
    std::unique_ptr<fml::Thread> ThreadSecond = std::make_unique<fml::Thread>(THREADSECOND);
    std::unique_ptr<fml::Thread> ThreadThird = std::make_unique<fml::Thread>(THREADTHIRD);
    std::unique_ptr<fml::Thread> ThreadFourth = std::make_unique<fml::Thread>(THREADFOURTH);
    fml::RefPtr<fml::TaskRunner> platform = ThreadFirst->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> gpu = ThreadSecond->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> ui = ThreadThird->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> io = ThreadFourth->GetTaskRunner();
    flutter::TaskRunners taskRunner(label, platform, gpu, ui, io);
    RefPtr<FlutterTaskExecutor> taskExecutor = AceType::MakeRefPtr<FlutterTaskExecutor>(taskRunner);
    FlutterTaskExecutor object(taskExecutor);

    /**
     * @tc.steps: step2. callback RemoveTaskObserver for exception test
     * @tc.expected: step2. expect the function is run ok.
     */
    object.RemoveTaskObserver();

    /**
     * @tc.steps: step3. SetCurrentId(-1).set asynchronous task.
     * @tc.expected: step3. task gets executed.
     */
    std::string uiTask;
    object.OnPostTask([&uiTask]() { uiTask = UISYNCTASK; }, TaskExecutor::TaskType::UI, 2);
    EXPECT_NE(uiTask, UISYNCTASK);
    sleep(2);
    EXPECT_EQ(uiTask, UISYNCTASK);

    /**
     * @tc.steps: step4. set asynchronous task.TaskType is BACKGROUND.
     * @tc.expected: step4. task gets executed.
     */
    std::string backgroudTask;
    bool backgroudTest = object.OnPostTask([&backgroudTask]() { backgroudTask = BACKGROUNDSYNCTASK; },
        TaskExecutor::TaskType::BACKGROUND, 2);
    EXPECT_TRUE(backgroudTest);
    EXPECT_NE(backgroudTask, BACKGROUNDSYNCTASK);
    sleep(2);
    EXPECT_EQ(backgroudTask, BACKGROUNDSYNCTASK);
}

/**
 * @tc.name: CastToFlutterTest008
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     */
    std::string label = LABEL;
    std::unique_ptr<fml::Thread> ThreadFirst = std::make_unique<fml::Thread>(THREADFIRST);
    std::unique_ptr<fml::Thread> ThreadSecond = std::make_unique<fml::Thread>(THREADSECOND);
    std::unique_ptr<fml::Thread> ThreadThird = std::make_unique<fml::Thread>(THREADTHIRD);
    std::unique_ptr<fml::Thread> ThreadFourth = std::make_unique<fml::Thread>(THREADFOURTH);
    fml::RefPtr<fml::TaskRunner> platform = ThreadFirst->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> gpu = ThreadSecond->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> ui = ThreadThird->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> io = ThreadFourth->GetTaskRunner();
    flutter::TaskRunners taskRunner(label, platform, gpu, ui, io);
    RefPtr<FlutterTaskExecutor> taskExecutor = AceType::MakeRefPtr<FlutterTaskExecutor>(taskRunner);
    FlutterTaskExecutor object(taskExecutor);

    /**
     * @tc.steps: step2. callback WrapTaskWithTraceId.
     * @tc.expected: step2. Return expected results.
     */
    std::string uiTask;
    auto result = taskExecutor->WrapTaskWithTraceId([&uiTask]() { uiTask = UISYNCTASK; }, 1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CastToFlutterTest009
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetAsset input assetName is null.
     * @tc.expected: step2. The expected result is null.
     */
    FlutterAssetManager object;
    auto result = object.GetAsset("");
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps: step3. callback GetAsset input assetName is not null.
     * @tc.expected: step3. The expected result is null.
     */
    auto assetProvider = AceType::MakeRefPtr<Plugin::FileAssetProvider>();
    object.PushBack(std::move(assetProvider));
    std::string assetName = RET_TEST;
    auto testAsset = object.GetAsset(assetName);
    EXPECT_EQ(testAsset, nullptr);
}

/**
 * @tc.name: CastToFlutterTest0010
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetAssetPath input assetName is not null.
     * @tc.expected: step2. Return expected results..
     */
    FlutterAssetManager object;
    auto assetProvider = AceType::MakeRefPtr<Plugin::FileAssetProvider>();
    object.PushBack(std::move(assetProvider));
    std::string assetName = RET_TEST;
    std::string result = object.GetAssetPath(assetName, true);
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: CastToFlutterTest0011
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetAssetPath input assetName is not null.
     * @tc.expected: step2. Return expected results..
     */
    FlutterAssetManager object;
    auto assetProvider = AceType::MakeRefPtr<Plugin::FileAssetProvider>();
    std::string hapPath = "/system/app/com.ohos.photos/Photos.hap";
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back("resources/base/profile/");
    assetProvider->Initialize(hapPath, assetBasePaths);
    object.PushBack(std::move(assetProvider));
    std::string assetName = "form_config.json";
    std::string result = object.GetAssetPath(assetName, true);
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: CastToFlutterTest0012
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetAssetList input assetName is not null.
     * @tc.expected: step2. Return expected results..
     */
    FlutterAssetManager object;
    auto assetProvider = AceType::MakeRefPtr<Plugin::FileAssetProvider>();
    object.PushBack(std::move(assetProvider));
    std::string path = RET_TEST;
    std::vector<std::string> assetList;
    object.GetAssetList(path, assetList);
    EXPECT_TRUE(assetList.empty());
}

/**
 * @tc.name: CastToFlutterTest0013
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object.
     * @tc.steps: step2. callback GetFileInfo input assetName is not null.
     * @tc.expected: step2. Return expected results..
     */
    FlutterAssetManager object;
    auto assetProvider = AceType::MakeRefPtr<Plugin::FileAssetProvider>();
    object.PushBack(std::move(assetProvider));
    std::string path = RET_TEST;
    MediaFileInfo fileInfo;
    bool result = object.GetFileInfo(path, fileInfo);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CastToFlutterTest0014
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a flutter window.
     */
    Platform::FlutterWindow flutter(instanceId);

    /**
     * @tc.steps: step2. callback Create.
     * @tc.expected: step2. Return expected results..
     */
    auto result = flutter.Create(nullptr);
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps: step3. callback Destroy.
     * @tc.expected: step3. Return expected results..
     */
    flutter.Destroy();
    EXPECT_EQ(flutter.vsyncCallbacks_.size(), 0);
}

/**
 * @tc.name: CastToFlutterTest0015
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a flutter window.
     */
    Platform::FlutterWindow flutter(instanceId);

    /**
     * @tc.steps: step2. callback RequestFrame.
     * @tc.expected: step2. RequestFrame success.
     */
    flutter.RequestFrame();
    EXPECT_EQ(flutter.instanceId_, 1);

    /**
     * @tc.steps: step3. callback SetRootRenderNode.
     * @tc.expected: step3. SetRootRenderNode success.
     */
    flutter.SetRootRenderNode(nullptr);
}

/**
 * @tc.name: CastToFlutterTest0016
 * @tc.desc: Test cast to flutter.
 * @tc.type: FUNC
 */
HWTEST_F(FlutterTest, CastToFlutterTest0016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a flutter window.
     */
    Platform::FlutterWindow flutter(instanceId);

    /**
     * @tc.steps: step2. callback RegisterVsyncCallback.
     * @tc.expected: step2. Return expected results..
     */
    auto callback = [](uint64_t nanoTimestamp, uint32_t frameCount) {
        g_result = nanoTimestamp;
    };
    flutter.RegisterVsyncCallback(callback);
    EXPECT_EQ(g_result, 0);

    /**
     * @tc.steps: step3. callback OnVsyncCallback.
     * @tc.expected: step3. Return expected results..
     */
    flutter.OnVsyncCallback(10);
    EXPECT_EQ(g_result, 10);
}
} // namespace OHOS::Ace
