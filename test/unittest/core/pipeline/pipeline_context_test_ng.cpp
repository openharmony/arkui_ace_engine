/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "test/unittest/core/pipeline/pipeline_context_test_ng.h"
// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "test/mock/base/mock_mouse_style.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_window.h"
#include "test/mock/core/pattern/mock_pattern.h"

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace NG {
ElementIdType PipelineContextTestNg::frameNodeId_ = 0;
ElementIdType PipelineContextTestNg::customNodeId_ = 0;
RefPtr<FrameNode> PipelineContextTestNg::frameNode_ = nullptr;
RefPtr<CustomNode> PipelineContextTestNg::customNode_ = nullptr;
RefPtr<PipelineContext> PipelineContextTestNg::context_ = nullptr;

void PipelineContextTestNg::ResetEventFlag(int32_t testFlag)
{
    auto flag = context_->eventManager_->GetInstanceId();
    context_->eventManager_->SetInstanceId(flag & (~testFlag));
}

bool PipelineContextTestNg::GetEventFlag(int32_t testFlag)
{
    auto flag = context_->eventManager_->GetInstanceId();
    return flag & testFlag;
}

void PipelineContextTestNg::SetUpTestSuite()
{
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    customNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    frameNode_ = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    // AddUINode is called in the function.
    customNode_ = CustomNode::CreateCustomNode(customNodeId_, TEST_TAG);
    ElementRegister::GetInstance()->AddUINode(frameNode_);
    auto window = std::make_shared<MockWindow>();
    EXPECT_CALL(*window, RequestFrame()).Times(AnyNumber());
    EXPECT_CALL(*window, FlushTasks()).Times(AnyNumber());
    EXPECT_CALL(*window, OnHide()).Times(AnyNumber());
    EXPECT_CALL(*window, RecordFrameTime(_, _)).Times(AnyNumber());
    EXPECT_CALL(*window, OnShow()).Times(AnyNumber());
    EXPECT_CALL(*window, FlushAnimation(NANO_TIME_STAMP))
        .Times(AtLeast(1))
        .WillOnce(testing::Return(true))
        .WillRepeatedly(testing::Return(false));
    EXPECT_CALL(*window, FlushModifier()).Times(AtLeast(1));
    EXPECT_CALL(*window, SetRootFrameNode(_)).Times(AnyNumber());
    context_ = AceType::MakeRefPtr<PipelineContext>(
        window, AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, nullptr, DEFAULT_INSTANCE_ID);
    context_->SetEventManager(AceType::MakeRefPtr<EventManager>());
    context_->fontManager_ = FontManager::Create();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = context_;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    context_->SetThemeManager(themeManager);
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ContainerModalTheme>()));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void PipelineContextTestNg::TearDownTestSuite()
{
    context_->Destroy();
    context_->window_.reset();
    MockContainer::TearDown();
}

void PipelineContextTestNg::CreateCycleDirtyNode(int cycle, bool& flagUpdate)
{
    if (cycle <= 0) {
        return;
    }
    cycle -= 1;
    auto customNodeTemp = CustomNode::CreateCustomNode(customNodeId_ + cycle + 100, TEST_TAG);
    customNodeTemp->SetUpdateFunction([cycle, &flagUpdate]() {
        PipelineContextTestNg::CreateCycleDirtyNode(cycle, flagUpdate);
        flagUpdate = !flagUpdate;
    });
    context_->AddDirtyCustomNode(customNodeTemp);
}

/**
 * @tc.name: PipelineContextTestNg001
 * @tc.desc: Test the function FlushDirtyNodeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    bool flagUpdate = false;
    customNode_->SetUpdateFunction([&flagUpdate]() { flagUpdate = true; });
    context_->AddDirtyCustomNode(customNode_);

    /**
     * @tc.steps2: Call the function FlushDirtyNodeUpdate.
     * @tc.expected: The flagUpdate is changed to true.
     */
    context_->FlushDirtyNodeUpdate();
    EXPECT_TRUE(flagUpdate);

    /**
     * @tc.steps2: Call the function FlushDirtyNodeUpdate.
     * @tc.expected: The flagUpdate is true.
     * @tc.expected: The dirtyNodes is not empty.
     */
    auto customNode_1 = CustomNode::CreateCustomNode(customNodeId_ + 20, TEST_TAG);
    customNode_1->SetUpdateFunction([&flagUpdate]() { CreateCycleDirtyNode(5, flagUpdate); });
    context_->AddDirtyCustomNode(customNode_1);
    context_->AddDirtyCustomNode(frameNode_);
    context_->FlushDirtyNodeUpdate();
    EXPECT_TRUE(flagUpdate);
    EXPECT_FALSE(context_->dirtyNodes_.empty());
    context_->dirtyNodes_.clear();
}

/**
 * @tc.name: PipelineContextTestNg002
 * @tc.desc: Test the function FlushVsync, AddVisibleAreaChangeNode, HandleVisibleAreaChangeEvent and .
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps2: Call the function AddOnAreaChangeNode.
     */
    context_->onVisibleAreaChangeNodeIds_.clear();
    context_->AddOnAreaChangeNode(frameNode_->GetId());
    context_->AddOnAreaChangeNode(customNode_->GetId());
    context_->AddOnAreaChangeNode(ElementRegister::UndefinedElementId);

    /**
     * @tc.steps3: Call the function AddVisibleAreaChangeNode.
     * @tc.expected: The drawDelegate_ is null.
     */
    context_->onAreaChangeNodeIds_.clear();
    context_->onAreaChangeNodeIds_.emplace(NOT_REGISTER_ID);
    context_->onAreaChangeNodeIds_.emplace(customNode_->nodeId_);
    context_->AddVisibleAreaChangeNode(frameNode_, { DEFAULT_DOUBLE1 }, nullptr);
    context_->AddVisibleAreaChangeNode(frameNode_, { DEFAULT_DOUBLE1 }, nullptr, false);
    EXPECT_EQ(context_->onVisibleAreaChangeNodeIds_.size(), DEFAULT_SIZE1);
    context_->onVisibleAreaChangeNodeIds_.emplace(customNode_->GetId());
    context_->onVisibleAreaChangeNodeIds_.emplace(ElementRegister::UndefinedElementId);
    EXPECT_EQ(context_->onVisibleAreaChangeNodeIds_.size(), DEFAULT_SIZE3);

    /**
     * @tc.steps4: Call the function FlushVsync with isEtsCard=false.
     * @tc.expected: The drawDelegate_ is null.
     */
    context_->onShow_ = false;
    context_->SetIsFormRender(false);
    context_->FlushVsync(NANO_TIME_STAMP, FRAME_COUNT);
    EXPECT_EQ(context_->drawDelegate_, nullptr);

    /**
     * @tc.steps5: Call the function FlushVsync with isEtsCard=false.
     * @tc.expected: The drawDelegate_ is non-null.
     */
    context_->onFocus_ = false;
    context_->onAreaChangeNodeIds_.clear();
    context_->SetDrawDelegate(std::make_unique<DrawDelegate>());
    context_->FlushVsync(NANO_TIME_STAMP, FRAME_COUNT);
    EXPECT_NE(context_->drawDelegate_, nullptr);
    /**
     * @tc.steps6: Call the function FlushVsync with isEtsCard=false
                    and processName equals to "".
     * @tc.expected: The drawDelegate_ is non-null.
     */
    AceApplicationInfo::GetInstance().processName_ = "";
    context_->onShow_ = true;
    context_->onFocus_ = true;
    context_->FlushVsync(NANO_TIME_STAMP, FRAME_COUNT);
    EXPECT_NE(context_->drawDelegate_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg003
 * @tc.desc: Test the function FlushVsync and functions FlushLayoutTask and FlushRenderTask of the UITaskScheduler.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps2: Add dirty layout and render nodes to taskScheduler_ to test functions
     *             FlushLayoutTask and FlushRenderTask of the UITaskScheduler.
     */
    context_->taskScheduler_->AddDirtyLayoutNode(frameNode_);
    context_->taskScheduler_->AddDirtyRenderNode(frameNode_);
    context_->taskScheduler_->dirtyRenderNodes_[frameNode_->GetPageId()].emplace(nullptr);

    /**
     * @tc.steps3: Call the function FlushVsync with isEtsCard=true.
     * @tc.expected: The drawDelegate_ is null.
     */
    context_->onShow_ = true;
    context_->onFocus_ = false;
    context_->SetIsFormRender(true);
    context_->FlushVsync(NANO_TIME_STAMP, FRAME_COUNT);
    EXPECT_EQ(context_->drawDelegate_, nullptr);

    /**
     * @tc.steps4: Call the function FlushVsync with isEtsCard=true.
     * @tc.expected: The drawDelegate_ is non-null.
     */
    context_->onFocus_ = true;
    context_->SetDrawDelegate(std::make_unique<DrawDelegate>());
    context_->FlushVsync(NANO_TIME_STAMP, FRAME_COUNT);
    EXPECT_EQ(context_->drawDelegate_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg004
 * @tc.desc: Test the function FlushAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    /**
     * @tc.steps2: Call the function FlushAnimation with empty scheduleTasks_.
     * @tc.expected: The scheduleTasks_ is null.
     */
    context_->FlushAnimation(NANO_TIME_STAMP);
    EXPECT_TRUE(context_->scheduleTasks_.empty());

    /**
     * @tc.steps3: Call the function FlushAnimation with unempty scheduleTasks_.
     * @tc.expected: The nanoTimestamp of scheduleTask is equal to NANO_TIME_STAMP.
     */
    auto scheduleTask = AceType::MakeRefPtr<MockScheduleTask>();
    EXPECT_NE(scheduleTask->GetNanoTimestamp(), NANO_TIME_STAMP);
    context_->AddScheduleTask(scheduleTask);
    context_->AddScheduleTask(nullptr);
    context_->FlushAnimation(NANO_TIME_STAMP);
    EXPECT_EQ(scheduleTask->GetNanoTimestamp(), DEFAULT_INT0);
}

/**
 * @tc.name: PipelineContextTestNg005
 * @tc.desc: Test the function FlushFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps2: Call the function FlushFocus.
     * @tc.expected: The dirtyFocusNode_ is changed to nullptr.
     */
    context_->FlushFocus();
    EXPECT_EQ(context_->dirtyFocusNode_.Upgrade(), nullptr);
    /**
     * @tc.steps2: Init a frameNode and SetFocusType with Node, Add dirty focus and call FlushFocus
     * @tc.expected: The dirtyFocusNode_ is changed to nullptr.
     */
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetFocusType(FocusType::NODE);
    context_->AddDirtyFocus(frameNode_);
    auto dirtyFocusNode = context_->dirtyFocusNode_.Upgrade();
    ASSERT_NE(dirtyFocusNode, nullptr);
    EXPECT_EQ(dirtyFocusNode->GetFocusType(), FocusType::NODE);
    context_->FlushFocus();
    EXPECT_EQ(context_->dirtyFocusNode_.Upgrade(), nullptr);
    /**
     * @tc.steps3: Init a new frameNode and SetFocusType with Node.
                    Add dirty focus, free focusHub_ and call FlushFocus
     * @tc.expected: The dirtyFocusNode_ is changed to nullptr.
     */
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    frameNode_ = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    eventHub = frameNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetFocusType(FocusType::NODE);
    context_->AddDirtyFocus(frameNode_);
    dirtyFocusNode = context_->dirtyFocusNode_.Upgrade();
    ASSERT_NE(dirtyFocusNode, nullptr);
    EXPECT_EQ(dirtyFocusNode->GetFocusType(), FocusType::NODE);
    frameNode_->eventHub_->focusHub_ = nullptr;
    context_->FlushFocus();
    EXPECT_EQ(context_->dirtyFocusNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: PipelineContextTestNg006
 * @tc.desc: Test the function FlushBuildFinishCallbacks.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    bool flagCbk = false;
    context_->AddBuildFinishCallBack(nullptr);
    context_->AddBuildFinishCallBack([&flagCbk]() { flagCbk = true; });

    /**
     * @tc.steps2: Call the function FlushBuildFinishCallbacks.
     * @tc.expected: The flagCbk is changed to true.
     */
    context_->FlushBuildFinishCallbacks();
    EXPECT_TRUE(flagCbk);
}

/**
 * @tc.name: PipelineContextTestNg007
 * @tc.desc: Test the function SetupRootElement.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->windowManager_ = AceType::MakeRefPtr<WindowManager>();
    /**
     * @tc.steps2: Call the function SetupRootElement with isJsCard_ = true.
     * @tc.expected: The stageManager_ is non-null.
     */
    context_->SetIsJsCard(true);
    context_->windowModal_ = WindowModal::NORMAL;
    context_->GetContainerModalNode();
    context_->SetupRootElement();
    EXPECT_NE(context_->stageManager_, nullptr);

    /**
     * @tc.steps3: Call the function SetupRootElement with isJsCard_ = false.
     * @tc.expected: The stageManager_ is non-null.
     */
    context_->SetIsJsCard(false);
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->GetContainerModalNode();
    context_->SetupRootElement();
    EXPECT_NE(context_->stageManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg008
 * @tc.desc: Test the function SetupSubRootElement.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    /**
     * @tc.steps2: Call the function SetupSubRootElement with isJsCard_ = true.
     * @tc.expected: The stageManager_ is non-null.
     */
    context_->SetIsJsCard(true);
    context_->SetupSubRootElement();
    EXPECT_NE(context_->stageManager_, nullptr);

    /**
     * @tc.steps3: Call the function SetupSubRootElement with isJsCard_ = false.
     * @tc.expected: The stageManager_ is non-null.
     */
    context_->SetIsJsCard(false);
    context_->SetupSubRootElement();
    EXPECT_NE(context_->stageManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg009
 * @tc.desc: Test the function OnSurfaceChanged.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->rootWidth_ = DEFAULT_INT10;
    context_->rootHeight_ = DEFAULT_INT10;
    bool flagCbk = false;

    /**
     * @tc.steps2: Call the function OnSurfaceChanged with DEFAULT_INT10.
     * @tc.expected: The flagCbk is changed to true.
     */
    context_->SetForegroundCalled(true);
    context_->SetNextFrameLayoutCallback([&flagCbk]() { flagCbk = !flagCbk; });
    context_->OnSurfaceChanged(DEFAULT_INT10, DEFAULT_INT10, WindowSizeChangeReason::CUSTOM_ANIMATION);
    EXPECT_TRUE(flagCbk);

    /**
     * @tc.steps3: Call the function OnSurfaceChanged with width = 1, height = 1 and weakFrontend_ = null.
     * @tc.expected: The flagCbk is not changed.
     */
    context_->OnSurfaceChanged(DEFAULT_INT1, DEFAULT_INT1);
    EXPECT_TRUE(flagCbk);

    /**
     * @tc.steps4: Call the function OnSurfaceDensityChanged with width = 1, height = 1 and weakFrontend_ != null.
     * @tc.expected: The width_ and height_ of frontend is changed to DEFAULT_INT1.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    context_->weakFrontend_ = frontend;
    context_->OnSurfaceChanged(DEFAULT_INT1, DEFAULT_INT1);
    EXPECT_EQ(frontend->GetWidth(), DEFAULT_INT1);
    EXPECT_EQ(frontend->GetHeight(), DEFAULT_INT1);
    context_->weakFrontend_.Reset();
}

/**
 * @tc.name: PipelineContextTestNg010
 * @tc.desc: Test the function OnSurfaceDensityChanged.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->density_ = DEFAULT_DOUBLE1;
    context_->dipScale_ = DEFAULT_DOUBLE1;

    /**
     * @tc.steps2: Call the function OnSurfaceDensityChanged with viewScale_ = 0.0.
     * @tc.expected: The density_ is changed to density.
     */
    context_->viewScale_ = 0.0;
    context_->OnSurfaceDensityChanged(DEFAULT_DOUBLE4);
    EXPECT_DOUBLE_EQ(context_->GetDensity(), DEFAULT_DOUBLE4);
    EXPECT_DOUBLE_EQ(context_->GetDipScale(), DEFAULT_DOUBLE1);

    /**
     * @tc.steps3: Call the function OnSurfaceDensityChanged with viewScale_ = 0.0.
     * @tc.expected: The density_ is changed to density.
     */
    context_->viewScale_ = DEFAULT_DOUBLE2;
    context_->OnSurfaceDensityChanged(DEFAULT_DOUBLE4);
    EXPECT_DOUBLE_EQ(context_->GetDensity(), DEFAULT_DOUBLE4);
    EXPECT_DOUBLE_EQ(context_->GetDipScale(), DEFAULT_DOUBLE2);
}

/**
 * @tc.name: PipelineContextTestNg011
 * @tc.desc: Test the function AddDirtyFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps2: Call the function AddDirtyFocus with FocusType::NODE.
     * @tc.expected: The FocusType of dirtyFocusNode_ is changed to FocusType::NODE.
     */
    focusHub->SetFocusType(FocusType::NODE);
    context_->AddDirtyFocus(frameNode_);
    auto dirtyFocusNode = context_->dirtyFocusNode_.Upgrade();
    ASSERT_NE(dirtyFocusNode, nullptr);
    EXPECT_EQ(dirtyFocusNode->GetFocusType(), FocusType::NODE);

    /**
     * @tc.steps3: Call the function OnSurfaceDensityChanged with FocusType::SCOPE.
     * @tc.expected: The FocusType of dirtyFocusScope_ is changed to FocusType::SCOPE.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    context_->AddDirtyFocus(frameNode_);
    auto dirtyFocusScope = context_->dirtyFocusScope_.Upgrade();
    ASSERT_NE(dirtyFocusScope, nullptr);
    EXPECT_EQ(dirtyFocusScope->GetFocusType(), FocusType::SCOPE);
}

/**
 * @tc.name: PipelineContextTestNg012
 * @tc.desc: Test functions WindowFocus and FlushWindowFocusChangedCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    context_->onWindowFocusChangedCallbacks_.clear();
    context_->AddWindowFocusChangedCallback(ElementRegister::UndefinedElementId);
    context_->AddWindowFocusChangedCallback(frameNodeId_);
    EXPECT_EQ(context_->onWindowFocusChangedCallbacks_.size(), DEFAULT_SIZE2);

    /**
     * @tc.steps2: Call the function WindowFocus with "true" and onShow_ = true.
     * @tc.expected: The onFocus_ is changed to true and the size of onWindowFocusChangedCallbacks_ is change to 1.
     */
    context_->onShow_ = true;
    context_->WindowFocus(true);
    EXPECT_TRUE(context_->onFocus_);
    EXPECT_EQ(context_->onWindowFocusChangedCallbacks_.size(), DEFAULT_SIZE1);

    /**
     * @tc.steps3: Call the function WindowFocus with "true" and onShow_ = false.
     * @tc.expected: The onFocus_ is changed to true and the size of onWindowFocusChangedCallbacks_ is change to 1.
     */
    context_->onShow_ = false;
    context_->WindowFocus(true);
    EXPECT_TRUE(context_->onFocus_);
    EXPECT_EQ(context_->onWindowFocusChangedCallbacks_.size(), DEFAULT_SIZE1);

    /**
     * @tc.steps4: Call the function WindowFocus with "false" and onShow_ = true.
     * @tc.expected: The onFocus_ is changed to false.
     */
    context_->onShow_ = true;
    context_->WindowFocus(false);
    EXPECT_FALSE(context_->onFocus_);
    EXPECT_EQ(context_->onWindowFocusChangedCallbacks_.size(), DEFAULT_SIZE1);

    /**
     * @tc.steps5: Call the function WindowFocus with "false" and onShow_ = false.
     * @tc.expected: The onFocus_ is changed to false.
     */
    context_->onShow_ = false;
    context_->WindowFocus(false);
    EXPECT_FALSE(context_->onFocus_);
    context_->RemoveWindowFocusChangedCallback(0);
    EXPECT_EQ(context_->onWindowFocusChangedCallbacks_.size(), DEFAULT_SIZE1);
}

/**
 * @tc.name: PipelineContextTestNg013
 * @tc.desc: Test the function NotifyMemoryLevel.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->nodesToNotifyMemoryLevel_.clear();
    context_->AddNodesToNotifyMemoryLevel(ElementRegister::UndefinedElementId);
    context_->AddNodesToNotifyMemoryLevel(customNodeId_);
    EXPECT_EQ(context_->nodesToNotifyMemoryLevel_.size(), DEFAULT_SIZE2);

    /**
     * @tc.steps2: Call the function NotifyMemoryLevel with "1".
     * @tc.expected: The size of nodesToNotifyMemoryLevel_ is change to 1.
     */
    context_->NotifyMemoryLevel(DEFAULT_INT1);
    EXPECT_EQ(context_->nodesToNotifyMemoryLevel_.size(), DEFAULT_SIZE1);

    /**
     * @tc.steps3: Call the function NotifyMemoryLevel with "1".
     * @tc.expected: The NOT_REGISTER_ID in nodesToNotifyMemoryLevel_ is erased.
     */
    context_->AddNodesToNotifyMemoryLevel(NOT_REGISTER_ID);
    context_->NotifyMemoryLevel(DEFAULT_INT1);
    auto iter =
        find(context_->nodesToNotifyMemoryLevel_.begin(), context_->nodesToNotifyMemoryLevel_.end(), NOT_REGISTER_ID);
    EXPECT_EQ(iter, context_->nodesToNotifyMemoryLevel_.end());
}

/**
 * @tc.name: PipelineContextTestNg014
 * @tc.desc: Test the function OnIdle.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    bool flagCbk = false;

    /**
     * @tc.steps2: Call the function OnIdle.
     * @tc.expected: The value of flagCbk remains unchanged.
     */
    context_->AddPredictTask([&flagCbk](int64_t, bool) { flagCbk = true; });
    context_->OnIdle(0);
    EXPECT_FALSE(flagCbk);

    /**
     * @tc.steps3: Call the function OnIdle.
     * @tc.expected: The flagCbk is changed to true.
     */
    context_->OnIdle(NANO_TIME_STAMP);
    EXPECT_TRUE(flagCbk);
}

/**
 * @tc.name: PipelineContextTestNg015
 * @tc.desc: Test the function Finish.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    bool flagCbk = false;

    /**
     * @tc.steps2: Call the function Finish.
     * @tc.expected: The value of flagCbk remains unchanged.
     */
    context_->SetFinishEventHandler(nullptr);
    context_->Finish(false);
    EXPECT_FALSE(flagCbk);

    /**
     * @tc.steps3: Call the function Finish.
     * @tc.expected: The flagCbk is changed to true.
     */
    context_->SetFinishEventHandler([&flagCbk]() { flagCbk = true; });
    context_->Finish(false);
    EXPECT_TRUE(flagCbk);
}

/**
 * @tc.name: PipelineContextTestNg016
 * @tc.desc: Test functions OnShow, OnHide and FlushWindowStateChangedCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    context_->onWindowStateChangedCallbacks_.clear();
    context_->AddWindowStateChangedCallback(ElementRegister::UndefinedElementId);
    context_->AddWindowStateChangedCallback(customNodeId_);
    EXPECT_EQ(context_->onWindowStateChangedCallbacks_.size(), DEFAULT_SIZE2);

    /**
     * @tc.steps2: Call the function OnShow.
     * @tc.expected: The onShow_ is changed to true and the size of onWindowStateChangedCallbacks_ is change to 1.
     */
    context_->OnShow();
    EXPECT_TRUE(context_->onShow_);
    EXPECT_EQ(context_->onWindowStateChangedCallbacks_.size(), DEFAULT_SIZE1);

    /**
     * @tc.steps3: Call the function OnHide.
     * @tc.expected: The onShow_ is changed to false.
     */
    context_->OnHide();
    EXPECT_FALSE(context_->onShow_);
    EXPECT_EQ(context_->onWindowStateChangedCallbacks_.size(), DEFAULT_SIZE1);
}

/**
 * @tc.name: PipelineContextTestNg017
 * @tc.desc: Test functions OnDragEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    auto manager = context_->GetDragDropManager();
    ASSERT_NE(manager, nullptr);
    auto frameNodeId_017 = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_017, nullptr);
    ASSERT_NE(frameNode, nullptr);
    manager->AddDragFrameNode(frameNode->GetId(), frameNode);

    /**
     * @tc.steps2: Call the function OnDragEvent with isDragged_=true, currentId_=DEFAULT_INT1 and
     * DRAG_EVENT_START_FOR_CONTROLLER.
     * @tc.expected: The currentId_ is equal to DEFAULT_INT1.
     */
    manager->isDragged_ = true;
    manager->currentId_ = DEFAULT_INT1;
    context_->OnDragEvent({ DEFAULT_INT1, DEFAULT_INT1 }, DragEventAction::DRAG_EVENT_START_FOR_CONTROLLER);
    EXPECT_EQ(manager->currentId_, DEFAULT_INT1);

    /**
     * @tc.steps2: Call the function OnDragEvent with isDragged_=true, currentId_=DEFAULT_INT1 and DRAG_EVENT_OUT.
     * @tc.expected: The currentId_ is equal to DEFAULT_INT1.
     */
    manager->isDragged_ = true;
    manager->currentId_ = DEFAULT_INT1;
    context_->OnDragEvent({ DEFAULT_INT1, DEFAULT_INT1 }, DragEventAction::DRAG_EVENT_OUT);
    EXPECT_EQ(manager->currentId_, DEFAULT_INT1);

    /**
     * @tc.steps3: Call the function OnDragEvent with isDragged_=false, currentId_=DEFAULT_INT1 and DRAG_EVENT_START.
     * @tc.expected: The currentId_ is equal to DEFAULT_INT1.
     */
    manager->isDragged_ = false;
    manager->currentId_ = DEFAULT_INT1;
    context_->OnDragEvent({ DEFAULT_INT10, DEFAULT_INT10 }, DragEventAction::DRAG_EVENT_START);
    EXPECT_EQ(manager->currentId_, DEFAULT_INT1);

    /**
     * @tc.steps4: Call the function OnDragEvent with isDragged_=false, currentId_=DEFAULT_INT1 and DRAG_EVENT_END.
     * @tc.expected: The currentId_ is changed to DEFAULT_INT10.
     */
    manager->isDragged_ = false;
    manager->currentId_ = DEFAULT_INT1;
    context_->OnDragEvent({ DEFAULT_INT10, DEFAULT_INT10 }, DragEventAction::DRAG_EVENT_END);
    EXPECT_EQ(manager->currentId_, DEFAULT_INT1);

    /**
     * @tc.steps4: Call the function OnDragEvent with isDragged_=false, currentId_=DEFAULT_INT1 and DRAG_EVENT_MOVE.
     * @tc.expected: The currentId_ is changed to DEFAULT_INT10.
     */
    manager->isDragged_ = false;
    manager->currentId_ = DEFAULT_INT1;
    context_->OnDragEvent({ DEFAULT_INT10, DEFAULT_INT10 }, DragEventAction::DRAG_EVENT_MOVE);
    EXPECT_EQ(manager->currentId_, DEFAULT_INT1);
    MockContainer::Current()->SetIsScenceBoardWindow(true);
    context_->OnDragEvent({ DEFAULT_INT10, DEFAULT_INT10 }, DragEventAction::DRAG_EVENT_MOVE);
    context_->SetIsDragging(false);
    EXPECT_FALSE(context_->IsDragging());
    context_->ResetDragging();
}

/**
 * @tc.name: PipelineContextTestNg018
 * @tc.desc: Test the function ShowContainerTitle.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->SetupRootElement();
    ASSERT_NE(context_->rootNode_, nullptr);
    auto containerNode = AceType::DynamicCast<FrameNode>(context_->rootNode_->GetChildren().front());
    ASSERT_NE(containerNode, nullptr);
    auto pattern = containerNode->GetPattern<ContainerModalPattern>();
    ASSERT_NE(containerNode, nullptr);

    /**
     * @tc.steps2: Call the function ShowContainerTitle with windowModal_ = WindowModal::DIALOG_MODAL.
     * @tc.expected: The moveX_ is unchanged.
     */
    pattern->moveX_ = DEFAULT_DOUBLE2;
    context_->windowModal_ = WindowModal::DIALOG_MODAL;
    context_->ShowContainerTitle(true);
    EXPECT_DOUBLE_EQ(pattern->moveX_, DEFAULT_DOUBLE2);

    /**
     * @tc.steps3: Call the function ShowContainerTitle with windowModal_ = WindowModal::CONTAINER_MODAL.
     * @tc.expected: The moveX_ is unchanged.
     */
    pattern->moveX_ = DEFAULT_DOUBLE2;
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->ShowContainerTitle(true);
    EXPECT_DOUBLE_EQ(pattern->moveX_, DEFAULT_DOUBLE2);
}

/**
 * @tc.name: PipelineContextTestNg019
 * @tc.desc: Test the function SetAppTitle.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->SetupRootElement();
    ASSERT_NE(context_->rootNode_, nullptr);
    auto containerNode = AceType::DynamicCast<FrameNode>(context_->rootNode_->GetChildren().front());
    ASSERT_NE(containerNode, nullptr);
    auto pattern = containerNode->GetPattern<ContainerModalPattern>();
    ASSERT_NE(containerNode, nullptr);

    /**
     * @tc.steps2: Call the function ShowContainerTitle with windowModal_ = WindowModal::DIALOG_MODAL.
     * @tc.expected: The moveX_ is unchanged.
     */
    pattern->moveX_ = DEFAULT_DOUBLE2;
    context_->windowModal_ = WindowModal::DIALOG_MODAL;
    context_->SetAppTitle(TEST_TAG);
    EXPECT_DOUBLE_EQ(pattern->moveX_, DEFAULT_DOUBLE2);

    /**
     * @tc.steps3: Call the function ShowContainerTitle with windowModal_ = WindowModal::CONTAINER_MODAL.
     * @tc.expected: The moveX_ is unchanged.
     */
    pattern->moveX_ = DEFAULT_DOUBLE2;
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->SetAppTitle(TEST_TAG);
    EXPECT_DOUBLE_EQ(pattern->moveX_, DEFAULT_DOUBLE2);
}

/**
 * @tc.name: PipelineContextTestNg020
 * @tc.desc: Test the function SetAppIcon.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->SetupRootElement();
    ASSERT_NE(context_->rootNode_, nullptr);
    auto containerNode = AceType::DynamicCast<FrameNode>(context_->rootNode_->GetChildren().front());
    ASSERT_NE(containerNode, nullptr);
    auto pattern = containerNode->GetPattern<ContainerModalPattern>();
    ASSERT_NE(containerNode, nullptr);

    /**
     * @tc.steps2: Call the function SetAppIcon with windowModal_ = WindowModal::DIALOG_MODAL.
     * @tc.expected: The moveX_ is unchanged.
     */
    pattern->moveX_ = DEFAULT_DOUBLE2;
    context_->windowModal_ = WindowModal::DIALOG_MODAL;
    context_->SetAppIcon(nullptr);
    EXPECT_DOUBLE_EQ(pattern->moveX_, DEFAULT_DOUBLE2);

    /**
     * @tc.steps3: Call the function SetAppIcon with windowModal_ = WindowModal::CONTAINER_MODAL.
     * @tc.expected: The moveX_ is unchanged.
     */
    pattern->moveX_ = DEFAULT_DOUBLE2;
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->SetAppIcon(nullptr);
    EXPECT_DOUBLE_EQ(pattern->moveX_, DEFAULT_DOUBLE2);
}

/**
 * @tc.name: PipelineContextTestNg021
 * @tc.desc: Test the function OnAxisEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    AxisEvent event;
    event.x = DEFAULT_DOUBLE1;
    context_->viewScale_ = DEFAULT_DOUBLE1;

    /**
     * @tc.steps2: Call the function OnAxisEvent with action = AxisAction::BEGIN.
     * @tc.expected: The instanceId is changed to 4.
     */
    event.action = AxisAction::BEGIN;
    ResetEventFlag(TOUCH_TEST_FLAG | AXIS_TEST_FLAG);
    context_->OnAxisEvent(event);
    EXPECT_FALSE(GetEventFlag(TOUCH_TEST_FLAG));
    EXPECT_FALSE(GetEventFlag(AXIS_TEST_FLAG));

    /**
     * @tc.steps3: Call the function OnAxisEvent with action = AxisAction::UPDATE.
     * @tc.expected: The instanceId is changed to 3.
     */
    event.action = AxisAction::UPDATE;
    ResetEventFlag(TOUCH_TEST_FLAG | AXIS_TEST_FLAG);
    context_->OnAxisEvent(event);
    EXPECT_FALSE(GetEventFlag(TOUCH_TEST_FLAG));
    EXPECT_FALSE(GetEventFlag(AXIS_TEST_FLAG));

    /**
     * @tc.steps4: Call the function OnAxisEvent with action = AxisAction::END.
     * @tc.expected: The instanceId is changed to 1.
     */
    event.action = AxisAction::END;
    ResetEventFlag(TOUCH_TEST_FLAG | AXIS_TEST_FLAG);
    context_->OnAxisEvent(event);
    EXPECT_FALSE(GetEventFlag(TOUCH_TEST_FLAG));
    EXPECT_FALSE(GetEventFlag(AXIS_TEST_FLAG));
}

/**
 * @tc.name: PipelineContextTestNg022
 * @tc.desc: Test the function OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    auto eventManager = context_->GetDragDropManager();
    ASSERT_NE(eventManager, nullptr);
    auto frameNodeId_022 = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_022, nullptr);
    ASSERT_NE(frameNode, nullptr);
    eventManager->AddDragFrameNode(frameNode->GetId(), frameNode);
    KeyEvent event;

    /**
     * @tc.steps2: Call the function OnKeyEvent with isFocusActive_ = false, action = KeyAction::DOWN and
     #             pressedCodes = { KeyCode::KEY_TAB }.
     * @tc.expected: The return value of OnKeyEvent is true.
     */
    context_->SetIsFocusActive(false);
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    event.pressedCodes = { KeyCode::KEY_TAB };
    EXPECT_FALSE(context_->OnNonPointerEvent(event));
    EXPECT_TRUE(context_->GetIsFocusActive());

    /**
     * @tc.steps3: Call the function OnKeyEvent with isFocusActive_ = false, action = KeyAction::DOWN and
     #             pressedCodes = { KeyCode::KEY_DPAD_UP }.
     * @tc.expected: The return value of OnKeyEvent is true.
     */
    context_->SetIsFocusActive(false);
    event.pressedCodes = { KeyCode::KEY_DPAD_UP };
    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_FALSE(context_->OnNonPointerEvent(event));
    EXPECT_FALSE(context_->GetIsFocusActive());

    /**
     * @tc.steps4: Call the function OnKeyEvent with isFocusActive_ = false, action = KeyAction::UP and
     #             pressedCodes = { KeyCode::KEY_CLEAR }.
     * @tc.expected: The return value of OnKeyEvent is true.
     */
    context_->SetIsFocusActive(false);
    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_CLEAR;
    event.pressedCodes = { KeyCode::KEY_CLEAR };
    EXPECT_FALSE(context_->OnNonPointerEvent(event));
    EXPECT_FALSE(context_->GetIsFocusActive());

    /**
     * @tc.steps4: Call the function OnKeyEvent with isFocusActive_ = true, action = KeyAction::UP and
     #             pressedCodes = { KeyCode::KEY_CLEAR }.
     * @tc.expected: The return value of OnKeyEvent is false.
     */
    context_->SetIsFocusActive(true);
    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_CLEAR;
    event.pressedCodes = { KeyCode::KEY_CLEAR };
    EXPECT_FALSE(context_->OnNonPointerEvent(event));
    EXPECT_TRUE(context_->GetIsFocusActive());

    /**
    * @tc.steps5: Call the function OnKeyEvent with isFocusActive_ = true, action = KeyAction::UP and
    #             pressedCodes = { KeyCode::KEY_CLEAR }.
    * @tc.expected: The return value of OnKeyEvent is false.
    */
    context_->rootNode_.Reset();
    context_->SetIsFocusActive(true);
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_ESCAPE;
    event.pressedCodes = { KeyCode::KEY_ESCAPE };

    auto pageNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto pageNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, pageNodeId, nullptr);
    auto childNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, childNodeId, nullptr);
    pageNode->AddChild(childNode);
    context_->stageManager_->stageNode_ = pageNode;
    context_->ReDispatch(event);
    EXPECT_FALSE(context_->OnNonPointerEvent(event));
    EXPECT_FALSE(context_->dragDropManager_->isDragCancel_);

    event.isPreIme = 1;
    EXPECT_FALSE(context_->OnNonPointerEvent(event));
}

/**
 * @tc.name: PipelineContextTestNg023
 * @tc.desc: Test the function OnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    MouseEvent event;

    /**
     * @tc.steps2: Call the function OnMouseEvent with action = MouseAction::HOVER
     *             and button = MouseButton::BACK_BUTTON.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is not called.
     */
    event.action = MouseAction::HOVER;
    event.button = MouseButton::BACK_BUTTON;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps3: Call the function OnMouseEvent with action = MouseAction::RELEASE
     *             and button = MouseButton::LEFT_BUTTON.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is called.
     */
    event.action = MouseAction::RELEASE;
    event.button = MouseButton::LEFT_BUTTON;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps4: Call the function OnMouseEvent with action = MouseAction::PRESS
     *             and button = MouseButton::LEFT_BUTTON.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is called.
     */
    event.action = MouseAction::PRESS;
    event.button = MouseButton::LEFT_BUTTON;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps5: Call the function OnMouseEvent with action = MouseAction::MOVE
     *             and button = MouseButton::LEFT_BUTTON.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is not called.
     */
    event.action = MouseAction::MOVE;
    event.button = MouseButton::LEFT_BUTTON;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps6: Call the function OnMouseEvent with action = MouseAction::RELEASE
     *             and pressedButtons = MOUSE_PRESS_LEFT.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is called.
     */
    event.button = MouseButton::BACK_BUTTON;
    event.action = MouseAction::RELEASE;
    event.pressedButtons = MOUSE_PRESS_LEFT;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps7: Call the function OnMouseEvent with action = MouseAction::PRESS
     *             and pressedButtons = MOUSE_PRESS_LEFT.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is called.
     */
    event.action = MouseAction::PRESS;
    event.pressedButtons = MOUSE_PRESS_LEFT;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps8: Call the function OnMouseEvent with action = MouseAction::MOVE
     *             and pressedButtons = MOUSE_PRESS_LEFT.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is not called.
     */
    event.action = MouseAction::MOVE;
    event.pressedButtons = MOUSE_PRESS_LEFT;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps9: Call the function OnMouseEvent with action = MouseAction::MOVE
     *             and pressedButtons = MOUSE_PRESS_LEFT.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is not called.
     */
    event.button = MouseButton::RIGHT_BUTTON;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps9: Call the function OnMouseEvent with action = MouseAction::MOVE
     *             and pressedButtons = MOUSE_PRESS_LEFT.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is called.
     */
    event.button = MouseButton::RIGHT_BUTTON;
    event.action = MouseAction::PRESS;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));
}

/**
 * @tc.name: PipelineContextTestNg024
 * @tc.desc: Test the function FlushTouchEvents.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    TouchEvent event;
    context_->touchEvents_.clear();

    /**
     * @tc.steps2: Call the function FlushTouchEvents with empty touchEvents_.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is not called.
     */
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->FlushTouchEvents();
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps3: Call the function FlushTouchEvents with unempty touchEvents_.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is called.
     */
    context_->touchEvents_.push_back(event);
    context_->touchEvents_.push_back(event);
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->FlushTouchEvents();
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps4: Call the function FlushTouchEvents with unempty touchEvents_.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is called.
     */
    TouchEvent event2;
    event2.id = 1;
    context_->touchEvents_.push_back(event);
    context_->touchEvents_.push_back(event2);
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->FlushTouchEvents();
    EXPECT_FALSE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));
}

/**
 * @tc.name: PipelineContextTestNg025
 * @tc.desc: Test the function OnDumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
    /**
     * @tc.steps2: init a vector with some string params and
                call OnDumpInfo with every param array.
     * @tc.expected: The return value is same as the expectation.
     */
    std::vector<std::vector<std::string>> params = { { "-element", "-lastpage" }, { "-element", "non-lastpage" },
        { "-element" }, { "-focus" }, { ACCESS_TAG }, { "-inspector" }, { "-render" }, { "-layer" }, { "-frontend" },
        { "-multimodal" }, { "-rotation", "1", "2", "3" }, { "-animationscale", "1", "2", "3" },
        { "-velocityscale", "1", "2", "3" }, { "-scrollfriction", "1", "2", "3" }, { "-threadstuck", "1", "2", "3" },
        { "-rotation" }, { "-animationscale" }, { "-velocityscale" }, { "-scrollfriction" }, { "-threadstuck" },
        { "test" }, { "-navigation" }, { "-focuswindowscene" }, { "-focusmanager" }, { "-jsdump" }, { "-event" },
        { "-imagecache" }, { "-imagefilecache" }, { "-allelements" }, { "-default" }, { "-overlay" }, { "--stylus" } };
    int turn = 0;
    for (; turn < params.size(); turn++) {
        EXPECT_TRUE(context_->OnDumpInfo(params[turn]));
    }
}

/**
 * @tc.name: PipelineContextTestNg026
 * @tc.desc: Test the function OnBackPressed.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps2: Call the function OnBackPressed with weakFrontend_ is null.
     * @tc.expected: The return value of function is false.
     */
    context_->weakFrontend_.Reset();
    EXPECT_FALSE(context_->OnBackPressed());

    /**
     * @tc.steps3: Call the function OnBackPressed with the return value of
     *             fullScreenManager_->RequestFullScreen is true.
     * @tc.expected: The return value of function is true.
     */
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    EXPECT_CALL(*frontend, OnBackPressed()).WillRepeatedly(testing::Return(true));
    context_->weakFrontend_ = frontend;
    auto frameNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId, nullptr);
    context_->fullScreenManager_->RequestFullScreen(frameNode); // Set the return value of OnBackPressed to true;
    EXPECT_TRUE(context_->OnBackPressed());

    /**
     * @tc.steps4: Call the function OnBackPressed with the return value of
     *             fullScreenManager_->RequestFullScreen is true.
     * @tc.expected: The return value of function is true.
     */
    // Set the return value of OnBackPressed of fullScreenManager_ to true;
    context_->fullScreenManager_->ExitFullScreen(frameNode);
    EXPECT_TRUE(context_->OnBackPressed());

    /**
     * @tc.steps5: Call the function OnBackPressed with the return value of
     *             overlayManager_->RemoveOverlay is true.
     * @tc.expected: The return value of function is true.
     */
    // Set the return value of RemoveOverlay of overlayManager_ to true;
    context_->overlayManager_->CloseDialog(frameNode_);
    EXPECT_TRUE(context_->OnBackPressed());

    /**
     * @tc.steps6: Call the function OnBackPressed with the return value of
     *             overlayManager_->RemoveOverlay is true.
     * @tc.expected: The return value of function is true.
     */
    // Set the return value of RemoveOverlay of overlayManager_ to true;
    context_->overlayManager_->CloseDialog(frameNode);
    EXPECT_TRUE(context_->OnBackPressed());
}

/**
 * @tc.name: PipelineContextTestNg027
 * @tc.desc: Test functions StartWindowSizeChangeAnimate and SetRootRect.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    EXPECT_CALL(*(MockWindow*)(context_->window_.get()), SetDrawTextAsBitmap(_)).Times(AnyNumber());
    context_->SetupRootElement();
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    auto& windowConfig = frontend->GetWindowConfig();
    windowConfig.designWidth = DEFAULT_INT1;
    context_->weakFrontend_ = frontend;

    /**
     * @tc.steps2: Call the function StartWindowSizeChangeAnimate with WindowSizeChangeReason::RECOVER.
     * @tc.expected: The designWidthScale_ is changed to DEFAULT_INT3.
     */
    context_->designWidthScale_ = DEFAULT_DOUBLE0;
    context_->StartWindowSizeChangeAnimate(DEFAULT_INT3, DEFAULT_INT3, WindowSizeChangeReason::RECOVER);
    EXPECT_DOUBLE_EQ(context_->designWidthScale_, DEFAULT_INT3);

    /**
     * @tc.steps3: Call the function StartWindowSizeChangeAnimate with WindowSizeChangeReason::MAXIMIZE.
     * @tc.expected: The designWidthScale_ is changed to DEFAULT_INT3.
     */
    context_->designWidthScale_ = DEFAULT_DOUBLE0;
    context_->StartWindowSizeChangeAnimate(DEFAULT_INT3, DEFAULT_INT3, WindowSizeChangeReason::MAXIMIZE);
    EXPECT_DOUBLE_EQ(context_->designWidthScale_, DEFAULT_INT3);

    /**
     * @tc.steps4: Call the function StartWindowSizeChangeAnimate with WindowSizeChangeReason::ROTATION.
     * @tc.expected: The designWidthScale_ is changed to DEFAULT_INT3.
     */
    context_->designWidthScale_ = DEFAULT_DOUBLE0;
    auto manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    context_->SetTextFieldManager(manager);
    context_->StartWindowSizeChangeAnimate(DEFAULT_INT3, DEFAULT_INT3, WindowSizeChangeReason::ROTATION);
    EXPECT_DOUBLE_EQ(context_->designWidthScale_, DEFAULT_INT3);

    /**
     * @tc.steps5: Call the function StartWindowSizeChangeAnimate with WindowSizeChangeReason::UNDEFINED.
     * @tc.expected: The designWidthScale_ is changed to DEFAULT_INT3.
     */
    context_->designWidthScale_ = DEFAULT_DOUBLE0;
    context_->StartWindowSizeChangeAnimate(DEFAULT_INT3, DEFAULT_INT3, WindowSizeChangeReason::UNDEFINED);
    EXPECT_DOUBLE_EQ(context_->designWidthScale_, DEFAULT_INT3);

    /**
     * @tc.steps5: Call the function StartWindowSizeChangeAnimate with WindowSizeChangeReason::UNDEFINED.
     * @tc.expected: The designWidthScale_ is changed to DEFAULT_INT3.
     */
    SystemProperties::windowAnimationEnabled_ = false;
    context_->rootNode_->geometryNode_->frame_.rect_.y_ = 3.0;
    context_->StartWindowSizeChangeAnimate(DEFAULT_INT3, DEFAULT_INT3, WindowSizeChangeReason::UNDEFINED);
    EXPECT_EQ(context_->rootNode_->GetGeometryNode()->GetFrameOffset().GetY(), 0);
}

/**
 * @tc.name: PipelineContextTestNg028
 * @tc.desc: Test functions OnVirtualKeyboardHeightChange and SetRootRect.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    auto& windowConfig = frontend->GetWindowConfig();
    windowConfig.designWidth = DEFAULT_INT1;
    context_->weakFrontend_ = frontend;
    context_->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManagerNG>());

    /**
     * @tc.steps2: Call the function OnVirtualKeyboardHeightChange with DEFAULT_DOUBLE1.
     * @tc.expected: The designWidthScale_ is changed to DEFAULT_INT0.
     */
    context_->designWidthScale_ = DEFAULT_DOUBLE1;
    context_->OnVirtualKeyboardHeightChange(DEFAULT_DOUBLE1);
    context_->OnVirtualKeyboardHeightChange(DEFAULT_DOUBLE1, 0, 0);
    EXPECT_DOUBLE_EQ(context_->designWidthScale_, DEFAULT_DOUBLE1);
    EXPECT_EQ(context_->safeAreaManager_->GetKeyboardOffset(), 0);

    /**
     * @tc.steps3: init data and Call the function OnVirtualKeyboardHeightChange
                    when textFieldManager_ is null.
     * @tc.expected: the return is same as expectation.
     */
    context_->textFieldManager_ = nullptr;

    // the first arg is rootHeight_, the second arg is the parameter of function,
    // the third arg is the expectation returns
    std::vector<std::vector<int>> params = { { 200, 400, -300 }, { -200, 100, -100 }, { -200, -300, 300 } };
    for (int turn = 0; turn < params.size(); turn++) {
        context_->rootHeight_ = params[turn][0];
        context_->OnVirtualKeyboardHeightChange(params[turn][1]);
        context_->OnVirtualKeyboardHeightChange(params[turn][1], 0, 0);
        EXPECT_EQ(context_->safeAreaManager_->GetKeyboardOffset(), params[turn][2]);
    }
    /**
     * @tc.steps4: init data and Call the function OnVirtualKeyboardHeightChange
                    when textFieldManager_ is not null.
     * @tc.expected: the return is same as expectation.
     */
    auto manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    context_->textFieldManager_ = manager;
    ASSERT_NE(context_->rootNode_, nullptr);

    // the first arg is manager->height_, the second arg is manager->position_.deltaY_
    // the third arg is rootHeight_, the forth arg is context_->rootNode_->geometryNode_->frame_.rect_.y_
    // the fifth arg is the parameter of function, the sixth arg is the expectation returns
    params = { { 10, 100, 300, 0, 50, 0 }, { 10, 100, 300, 100, 100, 0 }, { 30, 100, 300, 100, 50, 0 },
        { 50, 290, 400, 100, 200, -95 }, { -1000, 290, 400, 100, 200, 100 } };
    for (int turn = 0; turn < params.size(); turn++) {
        manager->height_ = params[turn][0];
        manager->position_.deltaY_ = params[turn][1];
        context_->rootHeight_ = params[turn][2];
        context_->rootNode_->geometryNode_->frame_.rect_.y_ = params[turn][3];
        context_->safeAreaManager_->UpdateKeyboardOffset(params[turn][3]);
        manager->SetClickPositionOffset(params[turn][3]);
        context_->OnVirtualKeyboardHeightChange(params[turn][4]);
        context_->OnVirtualKeyboardHeightChange(params[turn][4], 0, 0);
        EXPECT_EQ(context_->safeAreaManager_->GetKeyboardOffset(), params[turn][5]);
    }
}

/**
 * @tc.name: PipelineContextTestNg029
 * @tc.desc: Test ThemeManager and SharedImageManager multithread.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg029, TestSize.Level1)
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 20; ++i) {
        threads.emplace_back(std::thread([]() { context_->GetOrCreateSharedImageManager(); }));
    }
    for (auto&& thread : threads) {
        thread.join();
    }

    threads.clear();
    for (int i = 0; i < 20; ++i) {
        if (i == 10) {
            context_->SetThemeManager(AceType::MakeRefPtr<MockThemeManager>());
        } else {
            threads.emplace_back(std::thread([]() { context_->GetThemeManager(); }));
        }
    }
    for (auto&& thread : threads) {
        thread.join();
    }
    EXPECT_TRUE(context_->GetThemeManager());
}

/**
 * @tc.name: PipelineContextTestNg030
 * @tc.desc: Test RestoreNodeInfo, GetStoredNodeInfo, StoreNode and GetRestoreInfo.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg030, TestSize.Level1)
{
    /**
     * @tc.steps1: init a mockPattern.
     * @tc.expected: some calls by mockPattern.
     */
    RefPtr<MockPattern> mockPattern_ = AceType::MakeRefPtr<MockPattern>();
    Mock::AllowLeak(mockPattern_.rawPtr_);
    EXPECT_CALL(*mockPattern_, ProvideRestoreInfo())
        .Times(AnyNumber())
        .WillRepeatedly(testing::Return("Default restore info"));
    EXPECT_CALL(*mockPattern_, GetContextParam()).Times(AnyNumber()).WillRepeatedly(testing::Return(std::nullopt));
    EXPECT_CALL(*mockPattern_, CreatePaintProperty())
        .Times(AnyNumber())
        .WillRepeatedly(testing::Return(AceType::MakeRefPtr<PaintProperty>()));
    EXPECT_CALL(*mockPattern_, CreateLayoutProperty())
        .Times(AnyNumber())
        .WillRepeatedly(testing::Return(AceType::MakeRefPtr<LayoutProperty>()));
    EXPECT_CALL(*mockPattern_, CreateEventHub())
        .Times(AnyNumber())
        .WillRepeatedly(testing::Return(AceType::MakeRefPtr<EventHub>()));
    EXPECT_CALL(*mockPattern_, CreateAccessibilityProperty())
        .Times(AnyNumber())
        .WillRepeatedly(testing::Return(AceType::MakeRefPtr<AccessibilityProperty>()));
    EXPECT_CALL(*mockPattern_, OnAttachToFrameNode()).Times(AnyNumber());
    EXPECT_CALL(*mockPattern_, OnDetachFromFrameNode(_)).Times(AnyNumber());

    /**
     * @tc.steps2: init a patternCreator and Create frameNodes and call StoreNode.
     * @tc.expected: StoreNode success.
     */
    auto patternCreator_ = [&mockPattern_]() { return mockPattern_; };
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode_1 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    ASSERT_NE(context_, nullptr);
    context_->StoreNode(DEFAULT_RESTORE_ID0, frameNode_1);
    EXPECT_EQ(context_->storeNode_[DEFAULT_RESTORE_ID0], frameNode_1);
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode_2 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, patternCreator_);
    context_->StoreNode(DEFAULT_RESTORE_ID0, frameNode_2);
    EXPECT_EQ(context_->storeNode_[DEFAULT_RESTORE_ID0], frameNode_2);
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode_3 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    context_->StoreNode(DEFAULT_RESTORE_ID1, frameNode_3);
    EXPECT_EQ(context_->storeNode_[DEFAULT_RESTORE_ID1], frameNode_3);
    context_->storeNode_[DEFAULT_RESTORE_ID2] = nullptr;

    /**
     * @tc.steps3: call RestoreNodeInfo with nullptr.
     * @tc.expected: restoreNodeInfo_ is empty.
     */
    auto jsonNodeInfo = context_->GetStoredNodeInfo();
    context_->RestoreNodeInfo(jsonNodeInfo->GetChild());
    EXPECT_TRUE(context_->restoreNodeInfo_.empty());

    /**
     * @tc.steps4: call GetStoredNodeInfo and RestoreNodeInfo.
     * @tc.expected: restoreNodeInfo_ is not empty.
     */
    context_->RestoreNodeInfo(std::move(jsonNodeInfo));
    EXPECT_FALSE(context_->restoreNodeInfo_.empty());

    /**
     * @tc.steps5: call GetRestoreInfo.
     * @tc.expected: restoreInfo is not "Default restore info".
                    DEFAULT_RESTORE_ID0:"Default restore info" is moved from restoreNodeInfo_.
     */
    std::string restoreInfo;
    auto rt = context_->GetRestoreInfo(DEFAULT_RESTORE_ID0, restoreInfo);
    EXPECT_EQ(restoreInfo, "Default restore info");
    EXPECT_TRUE(rt);
    rt = context_->GetRestoreInfo(DEFAULT_RESTORE_ID0, restoreInfo);
    EXPECT_FALSE(rt);
    auto iter1 = context_->restoreNodeInfo_.find(DEFAULT_RESTORE_ID0);
    EXPECT_EQ(iter1, context_->restoreNodeInfo_.end());
}

/**
 * @tc.name: PipelineContextTestNg031
 * @tc.desc: Test OnTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    TouchEvent point_;
    /**
     * @tc.steps2: create callback and call OnTouchEvent.
     * @tc.expected: flag is false.
     */
    bool flag = false;
    context_->OnTouchEvent(point_, true);
    EXPECT_FALSE(flag);
    /**
     * @tc.steps3: call OnTouchEvent with second arg is false.
     * @tc.expected: hasIdleTasks_ is true.
     */
    point_.type = TouchType::UNKNOWN;
    context_->OnTouchEvent(point_, false);
    EXPECT_TRUE(context_->hasIdleTasks_);
    /**
     * @tc.steps4: change touch type and call OnTouchEvent with second arg is false.
     * @tc.expected: hasIdleTasks_ is true.
     */
    point_.type = TouchType::UP;
    context_->OnTouchEvent(point_, false);
    EXPECT_TRUE(context_->hasIdleTasks_);
}

/**
 * @tc.name: PipelineContextTestNg032
 * @tc.desc: Test OnSurfacePositionChanged RegisterSurfacePositionChangedCallback
 * UnregisterSurfacePositionChangedCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call RegisterSurfacePositionChangedCallback with null.
     * @tc.expected: rt is 0.
     */
    ASSERT_NE(context_, nullptr);
    int32_t rt = context_->RegisterSurfacePositionChangedCallback(nullptr);
    EXPECT_EQ(rt, 0);
    /**
     * @tc.steps2: init a callback, register it and change map memory.
                then call OnSurfacePositionChanged.
     * @tc.expected: flag is true.
     */
    bool flag = false;
    auto callback_1 = [&flag](int32_t input_1, int32_t input_2) { flag = !flag; };
    rt = context_->RegisterSurfacePositionChangedCallback(std::move(callback_1));
    context_->surfacePositionChangedCallbackMap_[100] = nullptr;
    context_->OnSurfacePositionChanged(0, 0);
    EXPECT_TRUE(flag);
    /**
     * @tc.steps2: call UnregisterSurfacePositionChangedCallback.
                then call OnSurfacePositionChanged.
     * @tc.expected: flag is true.
     */
    context_->UnregisterSurfacePositionChangedCallback(rt);
    context_->OnSurfacePositionChanged(0, 0);
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: PipelineContextTestNg040
 * @tc.desc: Test SetContainerButtonHide function.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg040, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize root node and containerModal node.
     * @tc.expected: root node and containerModal node are not null.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    context_->SetThemeManager(themeManager);
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ContainerModalTheme>()));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));

    ASSERT_NE(context_, nullptr);
    context_->SetWindowModal(WindowModal::CONTAINER_MODAL);
    ASSERT_NE(context_->window_, nullptr);
    context_->SetupRootElement();
    ASSERT_NE(context_->GetRootElement(), nullptr);
    auto containerNode = AceType::DynamicCast<FrameNode>(context_->GetRootElement()->GetChildren().front());
    ASSERT_NE(containerNode, nullptr);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    ASSERT_NE(containerPattern, nullptr);
    /**
     * @tc.steps2: call SetContainerButtonHide with params true, true, false, false.
     * @tc.expected: depends on first param, hideSplitButton value is true.
     */
    context_->SetContainerButtonHide(true, true, false, false);
    EXPECT_TRUE(containerPattern->hideSplitButton_ == true);
    /**
     * @tc.steps3: call SetContainerButtonHide with params false, true, false, false.
     * @tc.expected: depends on first param, hideSplitButton value is false.
     */
    context_->SetContainerButtonHide(false, true, false, false);
    EXPECT_TRUE(containerPattern->hideSplitButton_ == false);

    /**
     * @tc.steps4: call SetContainerButtonHide with params false, true, false, false.
     * @tc.expected: cover branch windowModal_ is not CONTAINER_MODAL
     */
    context_->SetWindowModal(WindowModal::DIALOG_MODAL);
    context_->SetContainerButtonHide(false, true, false, false);
    EXPECT_FALSE(containerPattern->hideSplitButton_);
}

/**
 * @tc.name: PipelineContextTestNg043
 * @tc.desc: Test SetCloseButtonStatus function.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg043, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize root node and containerModal node.
     * @tc.expected: root node and containerModal node are not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetWindowModal(WindowModal::CONTAINER_MODAL);
    ASSERT_NE(context_->window_, nullptr);
    context_->SetupRootElement();
    ASSERT_NE(context_->GetRootElement(), nullptr);
    auto containerNode = AceType::DynamicCast<FrameNode>(context_->GetRootElement()->GetChildren().front());
    ASSERT_NE(containerNode, nullptr);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    ASSERT_NE(containerPattern, nullptr);
    auto columNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().front());
    CHECK_NULL_VOID(columNode);
    auto titleNode = AceType::DynamicCast<FrameNode>(columNode->GetChildren().front());
    CHECK_NULL_VOID(titleNode);
    auto closeButton = AceType::DynamicCast<FrameNode>(titleNode->GetChildAtIndex(CLOSE_BUTTON_INDEX));
    CHECK_NULL_VOID(closeButton);
    auto buttonEvent = closeButton->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEvent);
    /**
     * @tc.steps2: call SetCloseButtonStatus with params true.
     * @tc.expected: CloseButton IsEnabled return true.
     */
    context_->SetCloseButtonStatus(true);
    EXPECT_EQ(buttonEvent->IsEnabled(), true);
    /**
     * @tc.steps3: call SetCloseButtonStatus with params false.
     * @tc.expected: CloseButton IsEnabled return false.
     */
    context_->SetCloseButtonStatus(false);
    EXPECT_EQ(buttonEvent->IsEnabled(), false);
}

HWTEST_F(PipelineContextTestNg, PipelineContextTestNg060, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    auto& windowConfig = frontend->GetWindowConfig();
    windowConfig.designWidth = DEFAULT_INT1;
    context_->weakFrontend_ = frontend;
    context_->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManagerNG>());

    /**
     * @tc.steps2: Set EnableAvoidKeyboardMode is true.
     * @tc.expected: get KeyboardSafeAreaEnabled is true.
     */
    context_->SetEnableKeyBoardAvoidMode(KeyBoardAvoidMode::RESIZE);
    EXPECT_TRUE(context_->GetSafeAreaManager()->KeyboardSafeAreaEnabled());

    /**
     * @tc.steps3: set root height and change virtual keyboard height.
     * @tc.expected: Resize the root height after virtual keyboard change.
     */

    auto containerNode = AceType::DynamicCast<FrameNode>(context_->GetRootElement()->GetChildren().front());
    ASSERT_NE(containerNode, nullptr);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    ASSERT_NE(containerPattern, nullptr);
    auto columNode = AceType::DynamicCast<FrameNode>(containerNode->GetChildren().front());
    CHECK_NULL_VOID(columNode);

    std::vector<std::vector<int>> params = { { 100, 400, 100 }, { 300, 100, 300 }, { 400, -300, 400 },
        { 200, 0, 200 } };
    for (int turn = 0; turn < params.size(); turn++) {
        context_->rootHeight_ = params[turn][0];
        context_->OnVirtualKeyboardHeightChange(params[turn][1]);
        EXPECT_EQ(context_->GetRootHeight(), params[turn][2]);
    }
}
/**
 * @tc.name: PipelineContextTestNg061
 * @tc.desc: Test the function WindowUnFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg061, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    ASSERT_NE(context_->rootNode_, nullptr);
    auto containerNode = AceType::DynamicCast<FrameNode>(context_->rootNode_->GetChildren().front());
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();

    /**
     * @tc.steps3: Call the function WindowUnFocus with WindowFocus(true).
     * @tc.expected: containerPattern isFocus_ is true.
     */
    containerPattern->isFocus_ = true;
    containerPattern->OnWindowForceUnfocused();
    EXPECT_TRUE(containerPattern->isFocus_);

    /**
     * @tc.steps2: Call the function WindowUnFocus with WindowFocus(false).
     * @tc.expected: containerPattern isFocus_ is false.
     */
    containerPattern->WindowFocus(false);
    containerPattern->OnWindowForceUnfocused();
    EXPECT_FALSE(containerPattern->isFocus_);
}

/**
 * @tc.name: PipelineContextTestNg088
 * @tc.desc: Test the function FlushRequestFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg088, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps2: Call the function FlushRequestFocus.
     * @tc.expected: The dirtyFocusNode_ is changed to nullptr.
     */
    context_->FlushRequestFocus();
    EXPECT_EQ(context_->dirtyRequestFocusNode_.Upgrade(), nullptr);
    context_->dirtyRequestFocusNode_ = frameNode_;
    EXPECT_NE(context_->dirtyRequestFocusNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: PipelineContextTestNg089
 * @tc.desc: Test the function FlushFocusScroll.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg089, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps2: Call the function FlushRequestFocus.
     * @tc.expected: The dirtyFocusNode_ is changed to nullptr.
     */
    context_->focusManager_.Reset();
    context_->FlushFocusScroll();
    EXPECT_EQ(context_->focusManager_, nullptr);
    context_->GetOrCreateFocusManager();
    EXPECT_NE(context_->focusManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg090
 * @tc.desc: Test the function FlushFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg090, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call FlushFocusView.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    context_->SetupSubRootElement();

    context_->FlushFocusView();
    EXPECT_NE(context_->focusManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg091
 * @tc.desc: Test the function SendEventToAccessibilityWithNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg091, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps2: Call the function FlushRequestFocus.
     * @tc.expected: The dirtyFocusNode_ is changed to nullptr.
     */
    AccessibilityEvent event;
    event.windowChangeTypes = WindowUpdateType::WINDOW_UPDATE_ACTIVE;
    event.type = AccessibilityEventType::PAGE_CHANGE;
    auto frameNodeId_091 = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_091, nullptr);
    CHECK_NULL_VOID(frameNode);
    context_->SendEventToAccessibilityWithNode(event, frameNode);
    bool accessibilityEnabled = AceApplicationInfo::GetInstance().IsAccessibilityEnabled();
    EXPECT_FALSE(accessibilityEnabled);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    context_->SendEventToAccessibilityWithNode(event, frameNode);
    accessibilityEnabled = AceApplicationInfo::GetInstance().IsAccessibilityEnabled();
    EXPECT_TRUE(accessibilityEnabled);
}

/**
 * @tc.name: PipelineContextTestNg092
 * @tc.desc: Test the function GetContainerModalButtonsRect.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg092, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    std::vector<Ace::RectF> rects;
    context_->TriggerOverlayNodePositionsUpdateCallback(rects);
    context_->RegisterOverlayNodePositionsUpdateCallback([](std::vector<Ace::RectF> rect) {});
    context_->TriggerOverlayNodePositionsUpdateCallback(rects);
    context_->windowManager_ = AceType::MakeRefPtr<WindowManager>();
    context_->windowModal_ = WindowModal::NORMAL;
    NG::RectF containerModal;
    NG::RectF buttons;
    context_->GetCustomTitleHeight();
    bool callbackTriggered = false;
    auto callback = [&callbackTriggered](RectF&, RectF&) { callbackTriggered = true; };
    context_->SubscribeContainerModalButtonsRectChange(std::move(callback));
    EXPECT_FALSE(context_->GetContainerModalButtonsRect(containerModal, buttons));
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->SubscribeContainerModalButtonsRectChange(std::move(callback));
    EXPECT_FALSE(context_->GetContainerModalButtonsRect(containerModal, buttons));
}

/**
 * @tc.name: PipelineContextTestNg093
 * @tc.desc: Test the function PrintVsyncInfoIfNeed.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg093, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    ASSERT_NE(context_->GetWindow(), nullptr);
    EXPECT_FALSE(context_->PrintVsyncInfoIfNeed());

    std::list<FrameInfo> dumpFrameInfos;
    FrameInfo frameInfo;
    dumpFrameInfos.push_back(frameInfo);
    context_->dumpFrameInfos_ = dumpFrameInfos;
    EXPECT_FALSE(context_->PrintVsyncInfoIfNeed());
    context_->dumpFrameInfos_.back().frameRecvTime_ = -1;
    EXPECT_FALSE(context_->PrintVsyncInfoIfNeed());
    context_->dumpFrameInfos_.clear();
}

/**
 * @tc.name: PipelineContextTestNg094
 * @tc.desc: Test the function ChangeDarkModeBrightness.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg094, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->windowManager_ = AceType::MakeRefPtr<WindowManager>();

    SystemProperties::SetColorMode(ColorMode::DARK);
    context_->SetAppBgColor(Color::BLACK);
    context_->ChangeDarkModeBrightness();
    context_->SetIsJsCard(true);
    context_->ChangeDarkModeBrightness();
    MockContainer::Current()->SetIsFormRender(true);
    context_->ChangeDarkModeBrightness();
    MockContainer::Current()->SetIsDynamicRender(true);
    context_->ChangeDarkModeBrightness();
    MockContainer::Current()->SetIsUIExtensionWindow(true);
    context_->ChangeDarkModeBrightness();
    context_->SetAppBgColor(Color::BLUE);
    context_->ChangeDarkModeBrightness();
    SystemProperties::SetColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    context_->ChangeDarkModeBrightness();
    EXPECT_NE(context_->stageManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg101
 * @tc.desc: Test the function FlushDirtyPropertyNodes.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg101, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    /**
     * @tc.steps2: Call the function FlushDirtyPropertyNodes.
     * @tc.expected: The dirtyPropertyNodes_ is empty.
     */
    context_->FlushDirtyPropertyNodes();
    EXPECT_TRUE(context_->dirtyPropertyNodes_.empty());
}

/**
 * @tc.name: PipelineContextTestNg102
 * @tc.desc: Test the MouseHover.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg102, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    context_->rootNode_ = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    context_->mouseEvents_.clear();
    ASSERT_NE(context_->rootNode_, nullptr);
    ASSERT_EQ(context_->lastMouseEvent_, nullptr);

    /**
     * @tc.steps2: Call the function FlushMouseEvent.
     */
    MouseEvent event;
    event.x = 12.345f;
    event.y = 12.345f;
    context_->mouseEvents_[context_->rootNode_].emplace_back(event);
    context_->FlushMouseEvent();
    for (const auto& [node, mouseEvents] : context_->mouseEvents_) {
        EXPECT_EQ(mouseEvents.size(), 1);
        EXPECT_EQ(mouseEvents.back().x, 12.345f);
        EXPECT_EQ(mouseEvents.back().y, 12.345f);
    }
    context_->mouseEvents_.clear();

    /**
     * @tc.steps2: Call the function FlushMouseEvent.
     * @param: set lastMouseEvent_ is not null
     */
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>(event);
    context_->lastMouseEvent_->action = MouseAction::MOVE;
    event.x = 54.321f;
    event.y = 54.321f;
    context_->mouseEvents_[context_->rootNode_].emplace_back(event);
    ASSERT_NE(context_->lastMouseEvent_, nullptr);
    ASSERT_NE(static_cast<int>(context_->lastMouseEvent_->action), 5);
    context_->FlushMouseEvent();
    for (const auto& [node, mouseEvents] : context_->mouseEvents_) {
        EXPECT_EQ(mouseEvents.size(), 0);
    }
    context_->mouseEvents_.clear();
}
} // namespace NG
} // namespace OHOS::Ace