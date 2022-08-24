/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>

#define private public
#define protected public
#include "flutter/common/task_runners.h"
#include "flutter/fml/task_runner.h"

#include "base/json/json_util.h"
#include "base/thread/task_executor.h"
#include "core/common/flutter/flutter_task_executor.h"
#include "core/common/frontend.h"
#include "core/common/platform_window.h"
#include "core/common/window.h"
#include "core/components/box/box_component.h"
#include "core/components/test/unittest/mock/mock_render_depend.h"
#include "core/components/touch_listener/touch_listener_component.h"
#include "core/mock/fake_task_executor.h"
#include "core/pipeline/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {

constexpr int32_t TEST_LOGIC_WIDTH = 750;
constexpr int32_t CUSTOM_DESIGN_WIDTH = 800;
constexpr int32_t TEST_SURFACE_WIDTH = 1080;
constexpr int32_t TEST_SURFACE_HEIGHT = 1920;
constexpr double TEST_DENSITY = 1.6;
constexpr int32_t SURFACE_WIDTH = 1080;
constexpr int32_t SURFACE_HEIGHT = 2244;
constexpr int32_t BEFORE_NEXTFRAME_VALUE = 0;
constexpr int32_t AFTER_NEXTFRAME_VALUE = 1;
uint64_t g_runningNano = 0;
const std::string LABEL = "task executor test";
const std::string THREADFIRST = "thread_1";
const std::string THREADSECOND = "thread_2";
const std::string THREADTHIRD = "thread_3";
const std::string THREADFOURTH = "thread_4";

RefPtr<PipelineContext> ConstructContext(const RefPtr<Frontend>& frontend)
{
    auto taskExecutor = Referenced::MakeRefPtr<FakeTaskExecutor>();
    auto platformWindow = PlatformWindow::Create(nullptr);
    auto window = std::make_unique<Window>(std::move(platformWindow));
    auto context = AceType::MakeRefPtr<PipelineContext>(std::move(window), taskExecutor, nullptr, nullptr, frontend, 0);
    context->SetupRootElement();
    return context;
}

RefPtr<PipelineContext> ConstructContextForJs(
    const RefPtr<Frontend>& frontend, const RefPtr<TaskExecutor>& taskExecutor)
{
    auto platformWindow = PlatformWindow::Create(nullptr);
    auto window = std::make_unique<Window>(std::move(platformWindow));
    auto context = AceType::MakeRefPtr<PipelineContext>(std::move(window), taskExecutor, nullptr, nullptr, frontend, 0);
    context->SetupRootElement();
    return context;
}
} // namespace

class MockFrontend : public Frontend {
public:
    MockFrontend() = default;
    ~MockFrontend() override = default;

    bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) override
    {
        return false;
    }

    void Destroy() override {}

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override {}
    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override {}

    RefPtr<AcePage> GetPage(int32_t pageId) const override
    {
        return nullptr;
    }

    RefPtr<AceEventHandler> GetEventHandler() override
    {
        return nullptr;
    }

    void DumpFrontend() const override {}

    WindowConfig& GetWindowConfig() override
    {
        return windowConfig_;
    }

    void SetDesignWidth(double designWidth)
    {
        windowConfig_.designWidth = designWidth;
    }

    void SetAutoDesignWidth(double autoDesignWidth)
    {
        windowConfig_.autoDesignWidth = autoDesignWidth;
    }

    FrontendType GetType() override
    {
        return FrontendType::JS;
    }

    void AddPage(const RefPtr<AcePage>& page) override {}
    void RunPage(int32_t pageId, const std::string& content, const std::string& params) override {}
    void PushPage(const std::string& content, const std::string& params) override {}
    void ReplacePage(const std::string& url, const std::string& params) override {}
    void UpdateState(State state) override {}
    void SendCallbackMessage(const std::string& callbackId, const std::string& data) const override {}
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& transfer) const override {}
    void TransferComponentResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void TransferJsPluginGetError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override {}
    void TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void LoadPluginJsCode(std::string&& jsCode) const override {}
    void LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const override {}
    bool OnBackPressed() override
    {
        return false;
    }
    void OnShow() override {}
    void OnHide() override {}
    void OnActive() override {}
    void OnInactive() override {}
    bool OnStartContinuation() override
    {
        return false;
    }
    void OnCompleteContinuation(int32_t code) override {}
    void OnMemoryLevel(const int32_t level) override {}
    void OnSaveData(std::string& data) override {}
    void OnSaveAbilityState (std::string& data) override {}
    void OnRestoreAbilityState (const std::string& data) override {}
    bool OnRestoreData(const std::string& data) override
    {
        return false;
    }
    void OnRemoteTerminated() override {}
    void OnNewRequest(const std::string& data) override {}
    void OnDialogUpdated(const std::string& data) override {}
    void OnNewWant(const std::string& data) override {}
    void CallRouterBack() override {}
    void OnSurfaceChanged(int32_t width, int32_t height) override {}
    bool IsForeground() override
    {
        return false;
    }
    RefPtr<AccessibilityManager> GetAccessibilityManager() const override
    {
        return nullptr;
    }

private:
    WindowConfig windowConfig_ { .designWidth = TEST_LOGIC_WIDTH, .autoDesignWidth = false };
};

class PipelineContextTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void InitTaskExecutor();
    void SetUp() override;
    void TearDown() override;

    RefPtr<TaskExecutor> taskExecutor_;
    std::string label_ = LABEL;
    std::unique_ptr<fml::Thread> ThreadFirst_ = std::make_unique<fml::Thread>(THREADFIRST);
    std::unique_ptr<fml::Thread> ThreadSecond_ = std::make_unique<fml::Thread>(THREADSECOND);
    std::unique_ptr<fml::Thread> ThreadThird_ = std::make_unique<fml::Thread>(THREADTHIRD);
    std::unique_ptr<fml::Thread> ThreadFourth_ = std::make_unique<fml::Thread>(THREADFOURTH);
    fml::RefPtr<fml::TaskRunner> platform_ = ThreadFirst_->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> gpu_ = ThreadSecond_->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> ui_ = ThreadThird_->GetTaskRunner();
    fml::RefPtr<fml::TaskRunner> io_ = ThreadFourth_->GetTaskRunner();
};

void PipelineContextTest::SetUpTestCase() {}

void PipelineContextTest::TearDownTestCase() {}

void PipelineContextTest::SetUp()
{
    InitTaskExecutor();
}

void PipelineContextTest::TearDown() {}

void PipelineContextTest::InitTaskExecutor()
{
    std::promise<void> promiseInit;
    std::future<void> futureInit = promiseInit.get_future();
    flutter::TaskRunners taskRunner(label_, platform_, gpu_, ui_, io_);
    auto flutterTaskExecutor = Referenced::MakeRefPtr<FlutterTaskExecutor>();

    platform_->PostTask([&promiseInit, flutterTaskExecutor]() {
        flutterTaskExecutor->InitPlatformThread();
        promiseInit.set_value();
    });

    flutterTaskExecutor->InitJsThread();
    flutterTaskExecutor->InitOtherThreads(taskRunner);
    futureInit.wait();

    taskExecutor_ = flutterTaskExecutor;
}

/**
 * @tc.name: RenderConvert001
 * @tc.desc: Verify the logical pixel rendering conversion mechanism.
 * @tc.type: FUNC
 * @tc.require: AR000DACKH
 * @tc.author: huzeqi
 */
HWTEST_F(PipelineContextTest, RenderConvert001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and initialize pipeline context.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    auto context = ConstructContext(frontend);

    /**
     * @tc.steps: step2. input surface size and verify result.
     */
    context->OnSurfaceDensityChanged(TEST_DENSITY);
    context->OnSurfaceChanged(TEST_SURFACE_WIDTH, TEST_SURFACE_HEIGHT);
    ASSERT_TRUE(NearEqual(context->GetDipScale(), TEST_DENSITY * TEST_LOGIC_WIDTH / TEST_SURFACE_WIDTH, 1));
}

/**
 * @tc.name: DesignWidthScale001
 * @tc.desc: Design width can control render scale.
 * @tc.type: FUNC
 * @tc.require: AR000DSSAT
 * @tc.author: liruokun
 */
HWTEST_F(PipelineContextTest, DesignWidthScale001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and initialize pipeline context. Set design width 750.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    frontend->SetDesignWidth(CUSTOM_DESIGN_WIDTH);
    auto context = ConstructContext(frontend);

    /**
     * @tc.steps: step2. Call OnSurfaceDensityChanged and OnSurfaceChanged.
     * @tc.expected: step2. Context has correct dip scale and view scale.
     */
    context->OnSurfaceDensityChanged(TEST_DENSITY);
    context->OnSurfaceChanged(TEST_SURFACE_WIDTH, TEST_SURFACE_HEIGHT);
    ASSERT_TRUE(NearEqual(context->GetDipScale(), TEST_DENSITY * CUSTOM_DESIGN_WIDTH / TEST_SURFACE_WIDTH));
    ASSERT_TRUE(NearEqual(
        context->GetViewScale(), static_cast<float>(TEST_SURFACE_WIDTH) / static_cast<float>(CUSTOM_DESIGN_WIDTH)));
}

/**
 * @tc.name: AutoDesignWidthScale001
 * @tc.desc: Auto design width can control render scale.
 * @tc.type: FUNC
 * @tc.require: AR000DSSAT
 * @tc.author: liruokun
 */
HWTEST_F(PipelineContextTest, AutoDesignWidthScale001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and initialize pipeline context. Set auto design width.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    frontend->SetAutoDesignWidth(true);
    auto context = ConstructContext(frontend);

    /**
     * @tc.steps: step2. Call OnSurfaceDensityChanged and OnSurfaceChanged.
     * @tc.expected: step2. Context has correct dip scale and view scale.
     */
    context->OnSurfaceDensityChanged(TEST_DENSITY);
    context->OnSurfaceChanged(TEST_SURFACE_WIDTH, TEST_SURFACE_HEIGHT);
    ASSERT_TRUE(NearEqual(context->GetDipScale(), 1.0));
    ASSERT_TRUE(NearEqual(context->GetViewScale(), TEST_DENSITY));
}

/**
 * @tc.name: RequestAnimationFrame001
 * @tc.desc: Check to return the correct timestamp.
 * @tc.type: FUNC
 * @tc.require: AR000F3CAB
 * @tc.author: chenlien
 */
HWTEST_F(PipelineContextTest, RequestAnimationFrame001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and initialize pipeline context.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    auto context = ConstructContextForJs(frontend, taskExecutor_);
    context->SetTimeProvider([] { return g_runningNano; });
    context->SetupRootElement();
    context->OnVsyncEvent(g_runningNano, 0);
    context->OnSurfaceChanged(SURFACE_WIDTH, SURFACE_HEIGHT);

    /**
     * @tc.steps: step2. Set timeStamp and mock vsync event.
     * @tc.expected: step2. Callback successfully and get correct timeStamp.
     */
    g_runningNano = 150000;
    auto&& callback = [context]() { ASSERT_TRUE(g_runningNano == context->GetTimeFromExternalTimer()); };
    context->SetAnimationCallback(callback);
    context->OnVsyncEvent(1, 0);
}

/**
 * @tc.name: SetNextFrameLayoutCallback001
 * @tc.desc: Call SetNextFrameLayoutCallback first and then set ForeGroundCalled to true.
 * NextFrameLayoutCallback should be called.
 * @tc.type: FUNC
 * @tc.require: issueI5H6CS
 */
HWTEST_F(PipelineContextTest, SetNextFrameLayoutCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and initialize pipeline context. create the callback.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    auto context = ConstructContext(frontend);
    int32_t value = BEFORE_NEXTFRAME_VALUE;
    auto callback = [&value]() { value = AFTER_NEXTFRAME_VALUE; };

    /**
     * @tc.steps: step2. set nextFrameLayoutCallback and then set foregroundCalled true.
     */
    context->SetNextFrameLayoutCallback(std::move(callback));
    context->SetForegroundCalled(true);

    /**
     * @tc.steps: step3. try call the callback in pipeline and check value.
     */
    context->TryCallNextFrameLayoutCallback();
    ASSERT_TRUE(value == AFTER_NEXTFRAME_VALUE);
}

/**
 * @tc.name: SetNextFrameLayoutCallback002
 * @tc.desc: Call SetNextFrameLayoutCallback first and then set ForeGroundCalled to false.
 * NextFrameLayoutCallback should not be called.
 * @tc.type: FUNC
 * @tc.require: issueI5H6CS
 */
HWTEST_F(PipelineContextTest, SetNextFrameLayoutCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and initialize pipeline context. create the callback.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    auto context = ConstructContext(frontend);
    int32_t value = BEFORE_NEXTFRAME_VALUE;
    auto callback = [&value]() { value = AFTER_NEXTFRAME_VALUE; };

    /**
     * @tc.steps: step2. set nextFrameLayoutCallback and then set foregroundCalled false.
     */
    context->SetNextFrameLayoutCallback(std::move(callback));
    context->SetForegroundCalled(false);

    /**
     * @tc.steps: step3. try call the callback in pipeline and check value.
     */
    context->TryCallNextFrameLayoutCallback();
    ASSERT_TRUE(value == BEFORE_NEXTFRAME_VALUE);
}

/**
 * @tc.name: SetNextFrameLayoutCallback003
 * @tc.desc: Set ForeGroundCalled to true and then call SetNextFrameLayoutCallback.
 * NextFrameLayoutCallback should be called.
 * @tc.type: FUNC
 * @tc.require: issueI5H6CS
 */
HWTEST_F(PipelineContextTest, SetNextFrameLayoutCallback003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and initialize pipeline context. create the callback.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    auto context = ConstructContext(frontend);
    int32_t value = BEFORE_NEXTFRAME_VALUE;
    auto callback = [&value]() { value = AFTER_NEXTFRAME_VALUE; };

    /**
     * @tc.steps: step2. set foregroundCalled true and then set nextFrameLayoutCallback.
     */
    context->SetForegroundCalled(true);
    context->SetNextFrameLayoutCallback(std::move(callback));

    /**
     * @tc.steps: step3. try call the callback in pipeline and check value.
     */
    context->TryCallNextFrameLayoutCallback();
    ASSERT_TRUE(value == AFTER_NEXTFRAME_VALUE);
}

/**
 * @tc.name: SetNextFrameLayoutCallback004
 * @tc.desc: Set ForeGroundCalled to false first and then call SetNextFrameLayoutCallback.
 * NextFrameLayoutCallback should not be called.
 * @tc.type: FUNC
 * @tc.require: issueI5H6CS
 */
HWTEST_F(PipelineContextTest, SetNextFrameLayoutCallback004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and initialize pipeline context. create the callback.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    auto context = ConstructContext(frontend);
    int32_t value = BEFORE_NEXTFRAME_VALUE;
    auto callback = [&value]() { value = AFTER_NEXTFRAME_VALUE; };

    /**
     * @tc.steps: step2. set foregroundCalled false and then set nextFrameLayoutCallback.
     */
    context->SetForegroundCalled(false);
    context->SetNextFrameLayoutCallback(std::move(callback));

    /**
     * @tc.steps: step3. try call the callback in pipeline and check value.
     */
    context->TryCallNextFrameLayoutCallback();
    ASSERT_TRUE(value == BEFORE_NEXTFRAME_VALUE);
}

} // namespace OHOS::Ace
