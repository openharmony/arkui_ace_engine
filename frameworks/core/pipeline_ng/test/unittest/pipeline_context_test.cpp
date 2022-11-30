/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include <cstdint>
#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/test/mock/mock_container.h"
#include "core/pipeline_ng/test/unittest/mock_schedule_task.h"
#include "core/pipeline_ng/test/mock/mock_window.h"
#include "core/pipeline_ng/test/mock/mock_frontend.h"
#include "core/pipeline_ng/test/unittest/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_INSTANCE_ID = 0;
constexpr int32_t DEFAULT_INT1 = 1;
constexpr int32_t DEFAULT_INT10 = 10;
constexpr uint32_t DEFAULT_SIZE1 = 1;
constexpr uint32_t DEFAULT_SIZE2 = 2;
constexpr uint32_t DEFAULT_SIZE3 = 3;
constexpr uint32_t FRAME_COUNT = 10;
constexpr uint64_t NANO_TIME_STAMP = 10;
constexpr double DEFAULT_DOUBLE1 = 1.0;
constexpr double DEFAULT_DOUBLE2 = 2.0;
constexpr double DEFAULT_DOUBLE4 = 4.0;
const std::string TEST_TAG("test");
} // namespace

class PipelineContextTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
private:
    const static ElementIdType frameNodeId_;
    const static ElementIdType customNodeId_;
};

const ElementIdType PipelineContextTest::frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
const ElementIdType PipelineContextTest::customNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();

void PipelineContextTest::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "PipelineContextTest SetUpTestSuite";
}

void PipelineContextTest::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "PipelineContextTest TearDownTestSuite";
}

void PipelineContextTest::SetUp()
{
    GTEST_LOG_(INFO) << "PipelineContextTest SetUp";
}

void PipelineContextTest::TearDown()
{
    GTEST_LOG_(INFO) << "PipelineContextTest TearDown";
}

/**
 * @tc.name: PipelineContextTest001
 * @tc.desc: Test the function FlushDirtyNodeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto customNode = CustomNode::CreateCustomNode(customNodeId_, TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    bool flagUpdate = false;
    customNode->SetUpdateFunction([&flagUpdate]() { flagUpdate = true; });
    auto context = AceType::MakeRefPtr<PipelineContext>(
        std::make_unique<MockWindow>(), nullptr, nullptr, nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);
    context->AddDirtyCustomNode(customNode);

    /**
     * @tc.steps2: Call the function FlushDirtyNodeUpdate.
     * @tc.expected: The flagUpdate is changed to true.
     */
    context->FlushDirtyNodeUpdate();
    EXPECT_TRUE(flagUpdate);
}

/**
 * @tc.name: PipelineContextTest002
 * @tc.desc: Test the function FlushVsync, AddVisibleAreaChangeNode and HandleVisibleAreaChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto mockWindow = std::make_unique<MockWindow>();
    EXPECT_CALL(*mockWindow, FlushCustomAnimation(NANO_TIME_STAMP))
        .Times(AtLeast(1))
        .WillOnce(testing::Return(true))
        .WillRepeatedly(testing::Return(false));
    auto context = AceType::MakeRefPtr<PipelineContext>(
        std::move(mockWindow), nullptr, nullptr, nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    auto customNode = CustomNode::CreateCustomNode(customNodeId_, TEST_TAG);
    ElementRegister::GetInstance()->AddUINode(frameNode);
    ElementRegister::GetInstance()->AddUINode(customNode);
    context->rootNode_ = frameNode;

    /**
     * @tc.steps2: Call the function AddVisibleAreaChangeNode.
     * @tc.expected: The drawDelegate_ is null.
     */
    context->AddVisibleAreaChangeNode(frameNode, DEFAULT_DOUBLE1, nullptr);
    EXPECT_EQ(context->visibleAreaChangeNodes_.size(), DEFAULT_SIZE1);
    context->visibleAreaChangeNodes_[customNode->GetId()] = std::list<VisibleCallbackInfo>();
    context->visibleAreaChangeNodes_[ElementRegister::UndefinedElementId] = std::list<VisibleCallbackInfo>();
    EXPECT_EQ(context->visibleAreaChangeNodes_.size(), DEFAULT_SIZE3);

    /**
     * @tc.steps3: Call the function FlushVsync with isEtsCard=false.
     * @tc.expected: The drawDelegate_ is null.
     */
    context->onShow_ = false;
    context->SetIsEtsCard(false);
    context->FlushVsync(NANO_TIME_STAMP, FRAME_COUNT);
    EXPECT_EQ(context->drawDelegate_, nullptr);

    /**
     * @tc.steps4: Call the function FlushVsync with isEtsCard=false.
     * @tc.expected: The drawDelegate_ is non-null.
     */
    context->onFocus_ = false;
    context->SetDrawDelegate(std::make_unique<DrawDelegate>());
    context->FlushVsync(NANO_TIME_STAMP, FRAME_COUNT);
    EXPECT_NE(context->drawDelegate_, nullptr);
}

/**
 * @tc.name: PipelineContextTest003
 * @tc.desc: Test the function FlushVsync and functions FlushLayoutTask and FlushRenderTask of the UITaskScheduler.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ContainerScope scope(DEFAULT_INSTANCE_ID);
    auto context = AceType::MakeRefPtr<PipelineContext>(std::make_unique<MockWindow>(),
        AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, nullptr, DEFAULT_INSTANCE_ID);
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(context);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    ASSERT_NE(context, nullptr);
    context->SetupRootElement();

    /**
     * @tc.steps2: Add dirty layout and render nodes to taskScheduler_ to test functions
     *             FlushLayoutTask and FlushRenderTask of the UITaskScheduler.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    context->taskScheduler_.AddDirtyLayoutNode(frameNode);
    context->taskScheduler_.dirtyLayoutNodes_[frameNode->GetPageId()].emplace(nullptr);
    context->taskScheduler_.AddDirtyRenderNode(frameNode);
    context->taskScheduler_.dirtyRenderNodes_[frameNode->GetPageId()].emplace(nullptr);

    /**
     * @tc.steps3: Call the function FlushVsync with isEtsCard=true.
     * @tc.expected: The drawDelegate_ is null.
     */
    context->onShow_ = true;
    context->onFocus_ = false;
    context->SetIsEtsCard(true);
    context->FlushVsync(NANO_TIME_STAMP, FRAME_COUNT);
    EXPECT_EQ(context->drawDelegate_, nullptr);

    /**
     * @tc.steps4: Call the function FlushVsync with isEtsCard=true.
     * @tc.expected: The drawDelegate_ is non-null.
     */
    context->onFocus_ = true;
    context->SetDrawDelegate(std::make_unique<DrawDelegate>());
    context->FlushVsync(NANO_TIME_STAMP, FRAME_COUNT);
    EXPECT_EQ(context->drawDelegate_, nullptr);
}

/**
 * @tc.name: PipelineContextTest004
 * @tc.desc: Test the function FlushAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto context = AceType::MakeRefPtr<PipelineContext>(
        std::make_unique<MockWindow>(), nullptr, nullptr, nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);

    /**
     * @tc.steps2: Call the function FlushAnimation with empty scheduleTasks_.
     * @tc.expected: The scheduleTasks_ is null.
     */
    context->FlushAnimation(NANO_TIME_STAMP);
    EXPECT_TRUE(context->scheduleTasks_.empty());

    /**
     * @tc.steps3: Call the function FlushAnimation with unempty scheduleTasks_.
     * @tc.expected: The nanoTimestamp of scheduleTask is equal to NANO_TIME_STAMP.
     */
    auto scheduleTask = AceType::MakeRefPtr<MockScheduleTask>();
    EXPECT_NE(scheduleTask->GetNanoTimestamp(), NANO_TIME_STAMP);
    context->AddScheduleTask(scheduleTask);
    context->AddScheduleTask(nullptr);
    context->FlushAnimation(NANO_TIME_STAMP);
    EXPECT_EQ(scheduleTask->GetNanoTimestamp(), NANO_TIME_STAMP);
}

/**
 * @tc.name: PipelineContextTest005
 * @tc.desc: Test the function FlushFocus and RequestDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ContainerScope scope(DEFAULT_INSTANCE_ID);
    auto context = AceType::MakeRefPtr<PipelineContext>(std::make_unique<MockWindow>(),
        AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, nullptr, DEFAULT_INSTANCE_ID);
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(context);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    ASSERT_NE(context, nullptr);
    context->SetupRootElement();

    /**
     * @tc.steps2: Call the function FlushFocus.
     * @tc.expected: The dirtyFocusNode_ is changed to nullptr.
     */
    context->FlushFocus();
    EXPECT_EQ(context->dirtyFocusNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: PipelineContextTest006
 * @tc.desc: Test the function FlushBuildFinishCallbacks.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    bool flagCbk = false;
    auto context = AceType::MakeRefPtr<PipelineContext>(
        std::make_unique<MockWindow>(), nullptr, nullptr, nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);
    context->AddBuildFinishCallBack(nullptr);
    context->AddBuildFinishCallBack([&flagCbk]() { flagCbk = true; });

    /**
     * @tc.steps2: Call the function FlushBuildFinishCallbacks.
     * @tc.expected: The flagCbk is changed to true.
     */
    context->FlushBuildFinishCallbacks();
    EXPECT_TRUE(flagCbk);
}

/**
 * @tc.name: PipelineContextTest007
 * @tc.desc: Test the function SetupRootElement.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ContainerScope scope(DEFAULT_INSTANCE_ID);
    auto context = AceType::MakeRefPtr<PipelineContext>(std::make_unique<MockWindow>(),
        AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, nullptr, DEFAULT_INSTANCE_ID);
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(context);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    ASSERT_NE(context, nullptr);
    /**
     * @tc.steps2: Call the function SetupRootElement with isJsCard_ = true.
     * @tc.expected: The stageManager_ is non-null.
     */
    context->SetIsJsCard(true);
    context->windowModal_ = WindowModal::NORMAL;
    context->SetupRootElement();
    EXPECT_NE(context->stageManager_, nullptr);

    /**
     * @tc.steps3: Call the function SetupRootElement with isJsCard_ = false.
     * @tc.expected: The stageManager_ is non-null.
     */
    context->SetIsJsCard(false);
    context->windowModal_ = WindowModal::CONTAINER_MODAL;
    context->SetupRootElement();
    EXPECT_NE(context->stageManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTest008
 * @tc.desc: Test the function SetupSubRootElement.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest008, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ContainerScope scope(DEFAULT_INSTANCE_ID);
    auto context = AceType::MakeRefPtr<PipelineContext>(std::make_unique<MockWindow>(),
        AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, nullptr, DEFAULT_INSTANCE_ID);
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(context);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    ASSERT_NE(context, nullptr);

    /**
     * @tc.steps2: Call the function SetupSubRootElement with isJsCard_ = true.
     * @tc.expected: The stageManager_ is non-null.
     */
    context->SetIsJsCard(true);
    context->SetupSubRootElement();
    EXPECT_NE(context->stageManager_, nullptr);

    /**
     * @tc.steps3: Call the function SetupSubRootElement with isJsCard_ = false.
     * @tc.expected: The stageManager_ is non-null.
     */
    context->SetIsJsCard(false);
    context->SetupSubRootElement();
    EXPECT_NE(context->stageManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTest009
 * @tc.desc: Test the function OnSurfaceChanged.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest009, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ContainerScope scope(DEFAULT_INSTANCE_ID);
    auto context = AceType::MakeRefPtr<PipelineContext>(std::make_unique<MockWindow>(),
        AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, AceType::MakeRefPtr<MockFrontend>(), DEFAULT_INSTANCE_ID);
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(context);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    ASSERT_NE(context, nullptr);
    context->rootWidth_ = DEFAULT_INT10;
    context->rootHeight_ = DEFAULT_INT10;
    bool flagCbk = false;

    /**
     * @tc.steps2: Call the function OnSurfaceChanged with DEFAULT_INT10.
     * @tc.expected: The flagCbk is changed to true.
     */
    context->SetForegroundCalled(true);
    context->SetNextFrameLayoutCallback([&flagCbk] () { flagCbk = !flagCbk; });
    context->OnSurfaceChanged(DEFAULT_INT10, DEFAULT_INT10, WindowSizeChangeReason::CUSTOM_ANIMATION);
    EXPECT_TRUE(flagCbk);

    /**
     * @tc.steps3: Call the function OnSurfaceChanged with width = 1, height = 1 and weakFrontend_ = null.
     * @tc.expected: The flagCbk is not changed.
     */
    context->OnSurfaceChanged(DEFAULT_INT1, DEFAULT_INT1);
    EXPECT_TRUE(flagCbk);

    /**
     * @tc.steps4: Call the function OnSurfaceDensityChanged with width = 1, height = 1 and weakFrontend_ != null.
     * @tc.expected: The width_ and height_ of frontend is changed to DEFAULT_INT1.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    context->weakFrontend_ = frontend;
    context->OnSurfaceChanged(DEFAULT_INT1, DEFAULT_INT1);
    EXPECT_EQ(frontend->GetWidth(), DEFAULT_INT1);
    EXPECT_EQ(frontend->GetHeight(), DEFAULT_INT1);
}

/**
 * @tc.name: PipelineContextTest010
 * @tc.desc: Test the function OnSurfaceDensityChanged.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest010, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto context = AceType::MakeRefPtr<PipelineContext>(
        std::make_unique<MockWindow>(), nullptr, nullptr, nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);
    context->density_ = DEFAULT_DOUBLE1;
    context->dipScale_ = DEFAULT_DOUBLE1;

    /**
     * @tc.steps2: Call the function OnSurfaceDensityChanged with viewScale_ = 0.0.
     * @tc.expected: The density_ is changed to density.
     */
    context->viewScale_ = 0.0;
    context->OnSurfaceDensityChanged(DEFAULT_DOUBLE4);
    EXPECT_DOUBLE_EQ(context->GetDensity(), DEFAULT_DOUBLE4);
    EXPECT_DOUBLE_EQ(context->GetDipScale(), DEFAULT_DOUBLE1);

    /**
     * @tc.steps2: Call the function OnSurfaceDensityChanged with viewScale_ = 0.0.
     * @tc.expected: The density_ is changed to density.
     */
    context->viewScale_ = DEFAULT_DOUBLE2;
    context->OnSurfaceDensityChanged(DEFAULT_DOUBLE4);
    EXPECT_DOUBLE_EQ(context->GetDensity(), DEFAULT_DOUBLE4);
    EXPECT_DOUBLE_EQ(context->GetDipScale(), DEFAULT_DOUBLE2);
}

/**
 * @tc.name: PipelineContextTest011
 * @tc.desc: Test the function AddDirtyFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest011, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto context = AceType::MakeRefPtr<PipelineContext>(
        std::make_unique<MockWindow>(), nullptr, nullptr, nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps2: Call the function AddDirtyFocus with FocusType::NODE.
     * @tc.expected: The FocusType of dirtyFocusNode_ is changed to FocusType::NODE.
     */
    focusHub->SetFocusType(FocusType::NODE);
    context->AddDirtyFocus(frameNode);
    auto dirtyFocusNode = context->dirtyFocusNode_.Upgrade();
    ASSERT_NE(dirtyFocusNode, nullptr);
    EXPECT_EQ(dirtyFocusNode->GetFocusType(), FocusType::NODE);

    /**
     * @tc.steps3: Call the function OnSurfaceDensityChanged with FocusType::SCOPE.
     * @tc.expected: The FocusType of dirtyFocusScope_ is changed to FocusType::SCOPE.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    context->AddDirtyFocus(frameNode);
    auto dirtyFocusScope = context->dirtyFocusScope_.Upgrade();
    ASSERT_NE(dirtyFocusScope, nullptr);
    EXPECT_EQ(dirtyFocusScope->GetFocusType(), FocusType::SCOPE);
}

/**
 * @tc.name: PipelineContextTest012
 * @tc.desc: Test functions WindowFocus and FlushWindowFocusChangedCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest012, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ElementRegister::GetInstance()->RemoveItem(customNodeId_);
    ElementRegister::GetInstance()->RemoveItem(frameNodeId_);
    ContainerScope scope(DEFAULT_INSTANCE_ID);
    auto context = AceType::MakeRefPtr<PipelineContext>(std::make_unique<MockWindow>(),
        AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, nullptr, DEFAULT_INSTANCE_ID);
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(context);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    ASSERT_NE(context, nullptr);
    context->SetupRootElement();
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    ASSERT_NE(frameNode, nullptr);
    ElementRegister::GetInstance()->AddUINode(frameNode);
    context->AddWindowFocusChangedCallback(ElementRegister::UndefinedElementId);
    context->AddWindowFocusChangedCallback(frameNodeId_);
    EXPECT_EQ(context->onWindowFocusChangedCallbacks_.size(), DEFAULT_SIZE2);

    /**
     * @tc.steps2: Call the function WindowFocus with "true".
     * @tc.expected: The onFocus_ is changed to true and the size of onWindowFocusChangedCallbacks_ is change to 1.
     */
    context->WindowFocus(true);
    EXPECT_TRUE(context->onFocus_);
    EXPECT_EQ(context->onWindowFocusChangedCallbacks_.size(), DEFAULT_SIZE1);

    /**
     * @tc.steps3: Call the function WindowFocus with "false".
     * @tc.expected: The onFocus_ is changed to false.
     */
    context->WindowFocus(false);
    EXPECT_FALSE(context->onFocus_);
    EXPECT_EQ(context->onWindowFocusChangedCallbacks_.size(), DEFAULT_SIZE1);
}

/**
 * @tc.name: PipelineContextTest013
 * @tc.desc: Test the function NotifyMemoryLevel.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest013, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customNode = CustomNode::CreateCustomNode(customNodeId_, TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    ElementRegister::GetInstance()->AddUINode(customNode);
    auto context = AceType::MakeRefPtr<PipelineContext>(
        std::make_unique<MockWindow>(), nullptr, nullptr, nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);
    context->AddNodesToNotifyMemoryLevel(ElementRegister::UndefinedElementId);
    context->AddNodesToNotifyMemoryLevel(customNodeId_);
    EXPECT_EQ(context->nodesToNotifyMemoryLevel_.size(), DEFAULT_SIZE2);

    /**
     * @tc.steps2: Call the function NotifyMemoryLevel with "1".
     * @tc.expected: The size of nodesToNotifyMemoryLevel_ is change to 1.
     */
    context->NotifyMemoryLevel(DEFAULT_INT1);
    EXPECT_EQ(context->nodesToNotifyMemoryLevel_.size(), DEFAULT_SIZE1);
}

/**
 * @tc.name: PipelineContextTest014
 * @tc.desc: Test the function OnIdle.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest014, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    bool flagCbk = false;
    auto context = AceType::MakeRefPtr<PipelineContext>(
        std::make_unique<MockWindow>(), nullptr, nullptr, nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);

    /**
     * @tc.steps2: Call the function OnIdle.
     * @tc.expected: The value of flagCbk remains unchanged.
     */
    context->AddPredictTask([&flagCbk] (int64_t deadline) { flagCbk = true; });
    context->OnIdle(0);
    EXPECT_FALSE(flagCbk);

    /**
     * @tc.steps3: Call the function OnIdle.
     * @tc.expected: The flagCbk is changed to true.
     */
    context->OnIdle(NANO_TIME_STAMP);
    EXPECT_TRUE(flagCbk);
}

/**
 * @tc.name: PipelineContextTest015
 * @tc.desc: Test the function Finish.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest015, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    bool flagCbk = false;
    auto context = AceType::MakeRefPtr<PipelineContext>(
        std::make_unique<MockWindow>(), nullptr, nullptr, nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);

    /**
     * @tc.steps2: Call the function Finish.
     * @tc.expected: The value of flagCbk remains unchanged.
     */
    context->SetFinishEventHandler(nullptr);
    context->Finish(false);
    EXPECT_FALSE(flagCbk);

    /**
     * @tc.steps3: Call the function Finish.
     * @tc.expected: The flagCbk is changed to true.
     */
    context->SetFinishEventHandler([&flagCbk] () { flagCbk = true; });
    context->Finish(false);
    EXPECT_TRUE(flagCbk);
}

/**
 * @tc.name: PipelineContextTest016
 * @tc.desc: Test functions OnShow, OnHide and FlushWindowStateChangedCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTest, PipelineContextTest016, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto customNode = CustomNode::CreateCustomNode(customNodeId_, TEST_TAG);
    ASSERT_NE(customNode, nullptr);
    ElementRegister::GetInstance()->AddUINode(customNode);
    auto context = AceType::MakeRefPtr<PipelineContext>(
        std::make_unique<MockWindow>(), nullptr, nullptr, nullptr, DEFAULT_INSTANCE_ID);
    ASSERT_NE(context, nullptr);
    context->rootNode_ = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    context->AddWindowStateChangedCallback(ElementRegister::UndefinedElementId);
    context->AddWindowStateChangedCallback(customNodeId_);
    EXPECT_EQ(context->onWindowStateChangedCallbacks_.size(), DEFAULT_SIZE2);

    /**
     * @tc.steps2: Call the function OnShow.
     * @tc.expected: The onShow_ is changed to true and the size of onWindowStateChangedCallbacks_ is change to 1.
     */
    context->OnShow();
    EXPECT_TRUE(context->onShow_);
    EXPECT_EQ(context->onWindowStateChangedCallbacks_.size(), DEFAULT_SIZE1);

    /**
     * @tc.steps3: Call the function OnHide.
     * @tc.expected: The onShow_ is changed to false.
     */
    context->OnHide();
    EXPECT_FALSE(context->onShow_);
    EXPECT_EQ(context->onWindowStateChangedCallbacks_.size(), DEFAULT_SIZE1);
}
} // namespace OHOS::Ace::NG