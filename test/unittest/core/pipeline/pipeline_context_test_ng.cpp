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
#include <algorithm>
#include <cstdint>
#include <memory>
#include <type_traits>

#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "common_constants.h"
#include "mock_schedule_task.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_frontend.h"
#include "test/mock/core/common/mock_window.h"

#include "base/json/json_util.h"
#include "base/log/frame_report.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/test/mock/mock_mouse_style.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/common/event_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/text_field/key_event_handler.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/test/mock/pattern/mock_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_INSTANCE_ID = 0;
constexpr int32_t DEFAULT_INT0 = 0;
constexpr int32_t DEFAULT_INT1 = 1;
constexpr int32_t DEFAULT_INT3 = 3;
constexpr int32_t DEFAULT_INT10 = 10;
constexpr int32_t DEFAULT_RESTORE_ID0 = 100;
constexpr int32_t DEFAULT_RESTORE_ID1 = 101;
constexpr int32_t DEFAULT_RESTORE_ID2 = 102;
constexpr int32_t NOT_REGISTER_ID = 307;
constexpr uint32_t DEFAULT_SIZE1 = 1;
constexpr uint32_t DEFAULT_SIZE2 = 2;
constexpr uint32_t DEFAULT_SIZE3 = 3;
constexpr uint32_t FRAME_COUNT = 10;
constexpr uint64_t NANO_TIME_STAMP = 10;
constexpr uint64_t DEFAULT_UINT64_1 = 39;
constexpr uint64_t DEFAULT_UINT64_2 = 41;
constexpr double DEFAULT_DOUBLE0 = 0.0;
constexpr double DEFAULT_DOUBLE1 = 1.0;
constexpr double DEFAULT_DOUBLE2 = 2.0;
constexpr double DEFAULT_DOUBLE4 = 4.0;
const std::string TEST_TAG("test");
const std::string ACCESS_TAG("-accessibility");
} // namespace

class PipelineContextTestNg : public testing::Test {
public:
    static void ResetEventFlag(int32_t testFlag);
    static bool GetEventFlag(int32_t testFlag);
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void CreateCycleDirtyNode(int cycle, bool& flagUpdate);

private:
    static ElementIdType frameNodeId_;
    static ElementIdType customNodeId_;
    static RefPtr<FrameNode> frameNode_;
    static RefPtr<CustomNode> customNode_;
    static RefPtr<PipelineContext> context_;
};

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
    EXPECT_CALL(*window, FlushCustomAnimation(NANO_TIME_STAMP))
        .Times(AtLeast(1))
        .WillOnce(testing::Return(true))
        .WillRepeatedly(testing::Return(false));
    EXPECT_CALL(*window, SetRootFrameNode(_)).Times(AnyNumber());
    context_ = AceType::MakeRefPtr<PipelineContext>(
        window, AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, nullptr, DEFAULT_INSTANCE_ID);
    context_->SetEventManager(AceType::MakeRefPtr<EventManager>());
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = context_;
}

void PipelineContextTestNg::TearDownTestSuite()
{
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
    context_->AddVisibleAreaChangeNode(frameNode_, DEFAULT_DOUBLE1, nullptr);
    context_->AddVisibleAreaChangeNode(frameNode_, DEFAULT_DOUBLE1, nullptr, false);
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
    context_->taskScheduler_.AddDirtyLayoutNode(frameNode_);
    context_->taskScheduler_.dirtyLayoutNodes_[frameNode_->GetPageId()].emplace(nullptr);
    context_->taskScheduler_.AddDirtyRenderNode(frameNode_);
    context_->taskScheduler_.dirtyRenderNodes_[frameNode_->GetPageId()].emplace(nullptr);

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
    EXPECT_EQ(scheduleTask->GetNanoTimestamp(), NANO_TIME_STAMP);
}

/**
 * @tc.name: PipelineContextTestNg005
 * @tc.desc: Test the function FlushFocus and RequestDefaultFocus.
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

     /**
     * @tc.steps5: set stageManager_ and stageNode_, stageNode_'s child,
                create frameNode_1's focusHub and call SetIsDefaultHasFocused with true
     * @tc.expected: RequestDefaultFocus returns false.
     */
    context_->stageManager_->stageNode_ = frameNode_;
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode_1 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    frameNode_->children_.push_back(frameNode_1);
    focusHub = frameNode_1->eventHub_->GetOrCreateFocusHub();
    focusHub->SetIsDefaultHasFocused(true);
    EXPECT_FALSE(context_->RequestDefaultFocus());
    /**
     * @tc.steps6: call SetIsDefaultHasFocused with false and create a new frameNode
                init frameNode_2's focusHub
     * @tc.expected: RequestDefaultFocus returns true while IsFocusableWholePath return true
                    RequestDefaultFocus returns false while IsFocusableWholePath return false.
     */
    focusHub->SetIsDefaultHasFocused(false);
    focusHub->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    auto frameNodeId_2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode_2 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_2, nullptr);
    frameNode_2->parent_ = nullptr;
    auto newFocusHub = frameNode_2->eventHub_->GetOrCreateFocusHub();
    focusHub->focusCallbackEvents_->SetDefaultFocusNode(newFocusHub);
    newFocusHub->SetFocusType(FocusType::NODE);
    frameNode_2->eventHub_->enabled_ = true;
    newFocusHub->focusable_ = true;
    newFocusHub->parentFocusable_ = true;
    EXPECT_TRUE(context_->RequestDefaultFocus());
    newFocusHub->SetFocusType(FocusType::DISABLE);
    EXPECT_FALSE(context_->RequestDefaultFocus());
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
    /**
     * @tc.steps2: Call the function SetupRootElement with isJsCard_ = true.
     * @tc.expected: The stageManager_ is non-null.
     */
    context_->SetIsJsCard(true);
    context_->windowModal_ = WindowModal::NORMAL;
    context_->SetupRootElement();
    EXPECT_NE(context_->stageManager_, nullptr);

    /**
     * @tc.steps3: Call the function SetupRootElement with isJsCard_ = false.
     * @tc.expected: The stageManager_ is non-null.
     */
    context_->SetIsJsCard(false);
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
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

    /**
     * @tc.steps2: Call the function OnDragEvent with isDragged_=true, currentId_=DEFAULT_INT1 and DRAG_EVENT_END.
     * @tc.expected: The currentId_ is equal to DEFAULT_INT1.
     */
    manager->isDragged_ = true;
    manager->currentId_ = DEFAULT_INT1;
    context_->OnDragEvent(DEFAULT_INT1, DEFAULT_INT1, DragEventAction::DRAG_EVENT_END);
    EXPECT_EQ(manager->currentId_, DEFAULT_INT1);

    /**
     * @tc.steps2: Call the function OnDragEvent with isDragged_=true, currentId_=DEFAULT_INT1 and DRAG_EVENT_MOVE.
     * @tc.expected: The currentId_ is equal to DEFAULT_INT1.
     */
    manager->isDragged_ = true;
    manager->currentId_ = DEFAULT_INT1;
    context_->OnDragEvent(DEFAULT_INT1, DEFAULT_INT1, DragEventAction::DRAG_EVENT_MOVE);
    EXPECT_EQ(manager->currentId_, DEFAULT_INT1);

    /**
     * @tc.steps3: Call the function OnDragEvent with isDragged_=false, currentId_=DEFAULT_INT1 and DRAG_EVENT_END.
     * @tc.expected: The currentId_ is equal to DEFAULT_INT1.
     */
    manager->isDragged_ = false;
    manager->currentId_ = DEFAULT_INT1;
    context_->OnDragEvent(DEFAULT_INT10, DEFAULT_INT10, DragEventAction::DRAG_EVENT_END);
    EXPECT_EQ(manager->currentId_, DEFAULT_INT1);

    /**
     * @tc.steps4: Call the function OnDragEvent with isDragged_=false, currentId_=DEFAULT_INT1 and DRAG_EVENT_MOVE.
     * @tc.expected: The currentId_ is changed to DEFAULT_INT10.
     */
    manager->isDragged_ = false;
    manager->currentId_ = DEFAULT_INT1;
    context_->OnDragEvent(DEFAULT_INT10, DEFAULT_INT10, DragEventAction::DRAG_EVENT_MOVE);
    EXPECT_EQ(manager->currentId_, DEFAULT_INT10);
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
    EXPECT_DOUBLE_EQ(pattern->moveX_, DEFAULT_DOUBLE1);
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
    EXPECT_DOUBLE_EQ(pattern->moveX_, DEFAULT_DOUBLE1);
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
    EXPECT_DOUBLE_EQ(pattern->moveX_, DEFAULT_DOUBLE1);
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
    EXPECT_TRUE(GetEventFlag(TOUCH_TEST_FLAG));
    EXPECT_TRUE(GetEventFlag(AXIS_TEST_FLAG));

    /**
     * @tc.steps3: Call the function OnAxisEvent with action = AxisAction::UPDATE.
     * @tc.expected: The instanceId is changed to 3.
     */
    event.action = AxisAction::UPDATE;
    ResetEventFlag(TOUCH_TEST_FLAG | AXIS_TEST_FLAG);
    context_->OnAxisEvent(event);
    EXPECT_FALSE(GetEventFlag(TOUCH_TEST_FLAG));
    EXPECT_TRUE(GetEventFlag(AXIS_TEST_FLAG));

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
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    context_->SetEventManager(eventManager);
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
    EXPECT_TRUE(context_->OnKeyEvent(event));
    EXPECT_TRUE(context_->GetIsFocusActive());

    /**
     * @tc.steps3: Call the function OnKeyEvent with isFocusActive_ = false, action = KeyAction::DOWN and
     #             pressedCodes = { KeyCode::KEY_DPAD_UP }.
     * @tc.expected: The return value of OnKeyEvent is true.
     */
    context_->SetIsFocusActive(false);
    event.pressedCodes = { KeyCode::KEY_DPAD_UP };
    event.code = KeyCode::KEY_DPAD_UP;
    eventManager->SetInstanceId(DEFAULT_INT0);
    EXPECT_TRUE(context_->OnKeyEvent(event));
    EXPECT_FALSE(context_->GetIsFocusActive());

    /**
     * @tc.steps4: Call the function OnKeyEvent with isFocusActive_ = false, action = KeyAction::UP and
     #             pressedCodes = { KeyCode::KEY_CLEAR }.
     * @tc.expected: The return value of OnKeyEvent is true.
     */
    eventManager->SetInstanceId(DEFAULT_INT0);
    context_->SetIsFocusActive(false);
    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_CLEAR;
    event.pressedCodes = { KeyCode::KEY_CLEAR };
    EXPECT_TRUE(context_->OnKeyEvent(event));
    EXPECT_FALSE(context_->GetIsFocusActive());

    /**
     * @tc.steps4: Call the function OnKeyEvent with isFocusActive_ = true, action = KeyAction::UP and
     #             pressedCodes = { KeyCode::KEY_CLEAR }.
     * @tc.expected: The return value of OnKeyEvent is false.
     */
    eventManager->SetInstanceId(DEFAULT_INT1);
    context_->SetIsFocusActive(true);
    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_CLEAR;
    event.pressedCodes = { KeyCode::KEY_CLEAR };
    EXPECT_FALSE(context_->OnKeyEvent(event));
    EXPECT_TRUE(context_->GetIsFocusActive());
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
    EXPECT_TRUE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps4: Call the function OnMouseEvent with action = MouseAction::PRESS
     *             and button = MouseButton::LEFT_BUTTON.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is called.
     */
    event.action = MouseAction::PRESS;
    event.button = MouseButton::LEFT_BUTTON;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_TRUE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

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
    EXPECT_TRUE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

    /**
     * @tc.steps7: Call the function OnMouseEvent with action = MouseAction::PRESS
     *             and pressedButtons = MOUSE_PRESS_LEFT.
     * @tc.expected: The function DispatchTouchEvent of eventManager_ is called.
     */
    event.action = MouseAction::PRESS;
    event.pressedButtons = MOUSE_PRESS_LEFT;
    ResetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG);
    context_->OnMouseEvent(event);
    EXPECT_TRUE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

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
    EXPECT_TRUE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));
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
    EXPECT_TRUE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));

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
    EXPECT_TRUE(GetEventFlag(DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG));
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
        { "test" } };
    int turn = 0;
    int falseInfoNum = 6;
    for (; turn < params.size(); turn++) {
        if (turn < params.size() - falseInfoNum) {
            EXPECT_TRUE(context_->OnDumpInfo(params[turn]));
        } else {
            EXPECT_FALSE(context_->OnDumpInfo(params[turn]));
        }
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
    context_->fullScreenManager_->RequestFullScreen(nullptr); // Set the return value of OnBackPressed to true;
    EXPECT_TRUE(context_->OnBackPressed());

    /**
     * @tc.steps4: Call the function OnBackPressed with the return value of
     *             fullScreenManager_->RequestFullScreen is true.
     * @tc.expected: The return value of function is true.
     */
    // Set the return value of OnBackPressed of fullScreenManager_ to true;
    context_->fullScreenManager_->ExitFullScreen(nullptr);
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
    context_->overlayManager_->CloseDialog(nullptr);
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
    context_->StartWindowSizeChangeAnimate(DEFAULT_INT3, DEFAULT_INT3, WindowSizeChangeReason::ROTATION);
    EXPECT_DOUBLE_EQ(context_->designWidthScale_, DEFAULT_INT3);

    /**
     * @tc.steps5: Call the function StartWindowSizeChangeAnimate with WindowSizeChangeReason::UNDEFINED.
     * @tc.expected: The designWidthScale_ is changed to DEFAULT_INT3.
     */
    context_->designWidthScale_ = DEFAULT_DOUBLE0;
    context_->StartWindowSizeChangeAnimate(DEFAULT_INT3, DEFAULT_INT3, WindowSizeChangeReason::UNDEFINED);
    EXPECT_DOUBLE_EQ(context_->designWidthScale_, DEFAULT_INT3);
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
    EXPECT_DOUBLE_EQ(context_->designWidthScale_, DEFAULT_DOUBLE1);
    EXPECT_EQ(context_->safeAreaManager_->GetKeyboardOffset(), 0);

    /**
     * @tc.steps3: init data and Call the function OnVirtualKeyboardHeightChange
                    when textFieldManager_ is null.
     * @tc.expected: the return is same as expectation.
     */
    context_->textFieldManager_ = nullptr;
    // the first arg is rootHeigth_, the second arg is the parameter of founction,
    // the third arg is the expectation returns
    std::vector<std::vector<int>> params = { { 200, 400, -300 }, { -200, 100, -100 }, { -200, -300, -100 } };
    for (int turn = 0; turn < params.size(); turn++) {
        context_->rootHeight_ = params[turn][0];
        context_->OnVirtualKeyboardHeightChange(params[turn][1]);
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
    // the fifth arg is the parameter of founction, the sixth arg is the expectation returns
    params = { { 10, 100, 300, 0, 50, 0 }, { 10, 100, 300, 100, 100, 100 }, { 30, 100, 300, 100, 50, 100 },
        { 50, 290, 400, 100, 200, -145 }, { -1000, 290, 400, 100, 200, 100 } };
    for (int turn = 0; turn < params.size(); turn++) {
        manager->height_ = params[turn][0];
        manager->position_.deltaY_ = params[turn][1];
        context_->rootHeight_ = params[turn][2];
        context_->rootNode_->geometryNode_->frame_.rect_.y_ = params[turn][3];
        context_->safeAreaManager_->UpdateKeyboardOffset(params[turn][3]);
        context_->OnVirtualKeyboardHeightChange(params[turn][4]);
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
 * @tc.name: PipelineContextTestNg033
 * @tc.desc: Test GetNavDestinationBackButtonNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg033, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and set stageNode_
                set frameNode_'s children
     */
    ASSERT_NE(context_, nullptr);
    context_->stageManager_->stageNode_ = frameNode_;
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode_1 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    frameNode_->children_.push_back(frameNode_1);
    auto navigationGroupNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto navigationGroupNode_1 = NavigationGroupNode::GetOrCreateGroupNode(TEST_TAG, navigationGroupNodeId_, nullptr);
    frameNode_->children_.push_back(navigationGroupNode_1);

    /**
     * @tc.steps1: set frameNode_2 as navigationGroupNode_1's contentNode_,titleBarNode_
                and set frameNode_2's children
     */
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode_2 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    navigationGroupNode_1->contentNode_ = frameNode_2;
    auto navDestinationGroupNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto navDestinationGroupNode_1 =
        NavDestinationGroupNode::GetOrCreateGroupNode(TEST_TAG, navDestinationGroupNodeId_, nullptr);
    frameNode_2->children_.push_back(navDestinationGroupNode_1);
    auto titleBarNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode_ = TitleBarNode::GetOrCreateTitleBarNode(TEST_TAG, titleBarNodeId_, nullptr);
    navDestinationGroupNode_1->titleBarNode_ = titleBarNode_;

    /**
     * @tc.steps1: set frameNode_3 as titleBarNode_'s backButton_
     */
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode_3 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    titleBarNode_->backButton_ = frameNode_3;
    /**
     * @tc.steps2: set layoutProperty_ and call GetNavDestinationBackButtonNode.
     * @tc.expected: rt is nullptr.
     */
    frameNode_3->layoutProperty_ = AceType::MakeRefPtr<ImageLayoutProperty>();
    auto rt = context_->GetNavDestinationBackButtonNode();
    EXPECT_EQ(rt, nullptr);
    /**
     * @tc.steps3: set propVisibility_ equals GONE and call GetNavDestinationBackButtonNode.
     * @tc.expected: rt is nullptr.
     */
    frameNode_3->layoutProperty_->propVisibility_ = VisibleType::GONE;
    rt = context_->GetNavDestinationBackButtonNode();
    EXPECT_EQ(rt, nullptr);
    /**
     * @tc.steps4: set propVisibility_ equals VISIBLE and call GetNavDestinationBackButtonNode.
     * @tc.expected: rt is not nullptr.
     */
    frameNode_3->layoutProperty_->propVisibility_ = VisibleType::VISIBLE;
    rt = context_->GetNavDestinationBackButtonNode();
    EXPECT_NE(rt, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg035
 * @tc.desc: Test ChangeMouseStyle.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg035, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters set mouseStyleNodeId.
     * @tc.expected: ChangePointerStyle will be called.
     * @tc.steps1: call ChangeMouseStyle.
     */
    ASSERT_NE(context_, nullptr);
    context_->onFocus_ = true;
    context_->mouseStyleNodeId_ = 0;
    auto mouseStyle_ = AceType::DynamicCast<MockMouseStyle>(MouseStyle::CreateMouseStyle().rawPtr_);
    EXPECT_CALL(*mouseStyle_, ChangePointerStyle(_, _)).Times(AnyNumber());
    context_->ChangeMouseStyle(0, MouseFormat::DEFAULT);
}

/**
 * @tc.name: PipelineContextTestNg036
 * @tc.desc: Test RequestFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg036, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and make sure pointers are not null.
     */
    ASSERT_NE(context_, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    context_->rootNode_ = frameNode_;
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode_1 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);

    /**
     * @tc.steps2: set host_and call UpdateInspectorId.
     * @tc.expect: focusNode is not null .
     */
    eventHub->host_ = frameNode_1;
    frameNode_1->UpdateInspectorId("123");
    auto focusNode = focusHub->GetChildFocusNodeById("123");
    ASSERT_NE(focusNode, nullptr);

    /**
     * @tc.steps3: change host_,focusType_,enabled_,
                    focusable_,parentFocusable_,currentFocus_
     */
    auto eventHub1 = frameNode_1->GetEventHub<EventHub>();
    eventHub1->host_ = nullptr;
    focusHub->focusType_ = FocusType::NODE;
    eventHub->enabled_ = true;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps4: change isSubPipeline_ and call RequestFocus with empty string
     * @tc.expect: RequestFocus empty string return false.
     */
    context_->isSubPipeline_ = true;
    auto rt = context_->RequestFocus("");
    EXPECT_FALSE(rt);

    /**
     * @tc.steps4: change isSubPipeline_ and call RequestFocus with 123
     * @tc.expect: RequestFocus 123 success.
     */
    context_->isSubPipeline_ = true;
    rt = context_->RequestFocus("123");
    EXPECT_TRUE(rt);

    /**
     * @tc.steps4: change isSubPipeline_ and call RequestFocus with empty string
     * @tc.expect: RequestFocus empty string return false.
     */
    context_->isSubPipeline_ = false;
    rt = context_->RequestFocus("");
    EXPECT_FALSE(rt);

    /**
     * @tc.steps4: change isSubPipeline_ and call RequestFocus with 123
     * @tc.expect: RequestFocus 123 success.
     */
    context_->isSubPipeline_ = false;
    rt = context_->RequestFocus("123");
    EXPECT_TRUE(rt);
}

/**
 * @tc.name: PipelineContextTestNg037
 * @tc.desc: Test ExecuteSurfaceChangedCallbacks.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg037, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and make sure pointers are not null.
                set flag and creat callback then set into surfaceChangedCallbackMap_.
                call ExecuteSurfaceChangedCallbacks.
     * @tc.expect: flag turns true.
     */
    ASSERT_NE(context_, nullptr);
    bool flag = false;
    auto callback = [&flag](int32_t input_1, int32_t input_2, int32_t input_3, int32_t input_4) { flag = !flag; };
    context_->surfaceChangedCallbackMap_[0] = callback;
    context_->surfaceChangedCallbackMap_[1] = nullptr;
    context_->ExecuteSurfaceChangedCallbacks(0, 0);
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: PipelineContextTestNg038
 * @tc.desc: Test FlushWindowSizeChangeCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg038, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and make sure pointers are not null.
                set onWindowSizeChangeCallbacks_.
     * @tc.expect: the value 314 has been erased.
     */
    ASSERT_NE(context_, nullptr);
    context_->onWindowSizeChangeCallbacks_.emplace_back(314);
    ASSERT_NE(frameNode_, nullptr);
    context_->onWindowSizeChangeCallbacks_.emplace_back(frameNode_->GetId());
    context_->FlushWindowSizeChangeCallback(0, 0, WindowSizeChangeReason::UNDEFINED);
    EXPECT_EQ(context_->onWindowSizeChangeCallbacks_.size(), 1);
}

/**
 * @tc.name: PipelineContextTestNg039
 * @tc.desc: Test GetCurrentFrameInfo.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg039, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and make sure pointers are not null.
                set dumpFrameCount_ and dumpFrameInfos_.
     * @tc.expect: the return value of GetCurrentFrameInfo is null.
     */
    ASSERT_NE(context_, nullptr);
    SystemProperties::dumpFrameCount_ = 1;
    context_->dumpFrameInfos_.push_back({});
    auto rt = context_->GetCurrentFrameInfo(DEFAULT_UINT64_1, DEFAULT_UINT64_2);
    EXPECT_NE(rt, nullptr);
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
     * @tc.steps2: call SetContainerButtonHide with params true, true, false.
     * @tc.expected: depends on first param, hideSplitButton value is true.
     */
    context_->SetContainerButtonHide(true, true, false);
    EXPECT_TRUE(containerPattern->hideSplitButton_ == true);
    /**
     * @tc.steps3: call SetContainerButtonHide with params false, true, false.
     * @tc.expected: depends on first param, hideSplitButton value is false.
     */
    context_->SetContainerButtonHide(false, true, false);
    EXPECT_TRUE(containerPattern->hideSplitButton_ == false);
}

/**
 * @tc.name: UITaskSchedulerTestNg001
 * @tc.desc: Test FlushLayoutTask.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, UITaskSchedulerTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create taskScheduler.
     */
    UITaskScheduler taskScheduler;

    /**
     * @tc.steps2: Create frameInfo and StartRecordFrameInfo.
     */
    FrameInfo frameInfo;
    taskScheduler.StartRecordFrameInfo(&frameInfo);

    /**
     * @tc.steps3: Create some frameNode.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, 1, nullptr);
    frameNode->SetInDestroying();
    auto frameNode2 = FrameNode::GetOrCreateFrameNode(TEST_TAG, 2, nullptr);

    /**
     * @tc.steps4: Calling FlushLayoutTask with no layout.
     * @tc.expected: frame info not record.
     */
    taskScheduler.FlushLayoutTask(false);
    EXPECT_EQ(frameInfo.layoutInfos_.size(), 0);

    /**
     * @tc.steps5: add some layoutNode and recall FlushLayoutTask with false .
     * @tc.expected: frame info not record.
     */
    taskScheduler.AddDirtyLayoutNode(frameNode);
    taskScheduler.dirtyLayoutNodes_[1].emplace(nullptr);
    taskScheduler.AddDirtyLayoutNode(frameNode2);
    taskScheduler.FlushLayoutTask(false);
    EXPECT_EQ(frameInfo.layoutInfos_.size(), 0);

    /**
     * @tc.steps6: add layoutNode again and set isLayoutDirtyMarked_ true  and recall FlushLayoutTask with false .
     * @tc.expected: frame info record true frameInfo.layoutInfos_.size is 1.
     */
    taskScheduler.AddDirtyLayoutNode(frameNode2);
    frameNode2->isLayoutDirtyMarked_ = true;
    taskScheduler.FlushLayoutTask(false);
    EXPECT_EQ(frameInfo.layoutInfos_.size(), 1);

    /**
     * @tc.steps7: add layoutNode again and call FlushLayoutTask with true .
     * @tc.expected: frame info record true frameInfo.layoutInfos_.size is 2.
     */
    taskScheduler.AddDirtyLayoutNode(frameNode2);
    frameNode2->isLayoutDirtyMarked_ = true;
    taskScheduler.FlushLayoutTask(true);
    EXPECT_EQ(frameInfo.layoutInfos_.size(), 2);

    /**
     * @tc.steps8: finish FinishRecordFrameInfo and do step7.
     * @tc.expected: frame info stop record frameInfo.layoutInfos_.size is 2.
     */
    taskScheduler.FinishRecordFrameInfo();
    taskScheduler.AddDirtyLayoutNode(frameNode2);
    frameNode2->isLayoutDirtyMarked_ = true;
    taskScheduler.FlushLayoutTask(true);
    EXPECT_EQ(frameInfo.layoutInfos_.size(), 2);
}

/**
 * @tc.name: UITaskSchedulerTestNg002
 * @tc.desc: Test FlushAfterLayoutTask.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, UITaskSchedulerTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps1: Create taskScheduler.
     */
    UITaskScheduler taskScheduler;

    /**
     * @tc.steps2: Call FlushAfterLayoutTask.
     */
    taskScheduler.FlushAfterLayoutTask();

    /**
     * @tc.steps3: Call AddAfterLayoutTask.
     * @tc.expected: afterLayoutTasks_ in the taskScheduler size is 2.
     */
    taskScheduler.AddAfterLayoutTask([]() {});
    taskScheduler.AddAfterLayoutTask(nullptr);
    EXPECT_EQ(taskScheduler.afterLayoutTasks_.size(), 2);

    /**
     * @tc.steps4: Call FlushTask.
     * @tc.expected: afterLayoutTasks_ in the taskScheduler size is 0.
     */
    taskScheduler.FlushTask();
    EXPECT_EQ(taskScheduler.afterLayoutTasks_.size(), 0);
}

/**
 * @tc.name: UITaskSchedulerTestNg003
 * @tc.desc: Test FlushAfterLayoutTask.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, UITaskSchedulerTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps1: Create taskScheduler.
     */
    UITaskScheduler taskScheduler;

    /**
     * @tc.steps2: Call FlushPredictTask.
     */
    taskScheduler.FlushPredictTask(0);

    /**
     * @tc.steps3: Call AddPredictTask.
     * @tc.expected: predictTask_ in the taskScheduler size is 2.
     */
    taskScheduler.AddPredictTask([](int64_t, bool) {});
    taskScheduler.AddPredictTask(nullptr);
    EXPECT_EQ(taskScheduler.predictTask_.size(), 2);

    /**
     * @tc.steps4: Call FlushPredictTask.
     * @tc.expected: predictTask_ in the taskScheduler size is 0.
     */
    taskScheduler.FlushPredictTask(0);
    EXPECT_EQ(taskScheduler.predictTask_.size(), 0);
}

/**
 * @tc.name: UITaskSchedulerTestNg004
 * @tc.desc: Test NeedAdditionalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, UITaskSchedulerTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps1: Create taskScheduler.
     */
    UITaskScheduler taskScheduler;

    /**
     * @tc.steps2: Create some frameNode and configure the required parameters.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, 1, nullptr);
    frameNode->layoutProperty_ = nullptr;
    auto frameNode2 = FrameNode::GetOrCreateFrameNode(TEST_TAG, 2, nullptr);

    /**
     * @tc.steps3: Call AddDirtyLayoutNode with different parameters.
     * @tc.expected: NeedAdditionalLayout return false.
     */
    taskScheduler.AddDirtyLayoutNode(frameNode);
    taskScheduler.dirtyLayoutNodes_[1].emplace(nullptr);
    taskScheduler.AddDirtyLayoutNode(frameNode2);
    EXPECT_FALSE(taskScheduler.NeedAdditionalLayout());

    /**
     * @tc.steps4: Create a appropriate node and recall AddDirtyLayoutNode.
     * @tc.expected: NeedAdditionalLayout return true.
     */
    auto frameNode3 = FrameNode::GetOrCreateFrameNode(TEST_TAG, 3, nullptr);
    auto geometryTransition = AceType::MakeRefPtr<NG::GeometryTransition>(frameNode3);
    geometryTransition->hasOutAnim_ = true;
    geometryTransition->inNode_ = frameNode2;
    geometryTransition->outNode_ = frameNode3;
    frameNode3->GetLayoutProperty()->geometryTransition_ = geometryTransition;
    taskScheduler.AddDirtyLayoutNode(frameNode3);
    EXPECT_TRUE(taskScheduler.NeedAdditionalLayout());
    taskScheduler.CleanUp();
}

/**
 * @tc.name: UITaskSchedulerTestNg005
 * @tc.desc: Test FlushRenderTask.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, UITaskSchedulerTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps1: Create taskScheduler.
     */
    UITaskScheduler taskScheduler;

    /**
     * @tc.steps2: Create frameInfo and StartRecordFrameInfo.
     */
    FrameInfo frameInfo;
    taskScheduler.StartRecordFrameInfo(&frameInfo);

    /**
     * @tc.steps3: Create some frameNode.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, 1, nullptr);
    frameNode->SetInDestroying();
    taskScheduler.dirtyRenderNodes_[1].emplace(nullptr);
    auto pattern = AceType::MakeRefPtr<BubblePattern>();
    auto frameNode2 = FrameNode::CreateFrameNode(TEST_TAG, 2, pattern);

    /**
     * @tc.steps4: Calling FlushRenderTask with no layout.
     * @tc.expected: frame info not record.
     */
    taskScheduler.FlushRenderTask(false);

    /**
     * @tc.steps5: add some layoutNode and recall FlushRenderTask with false .
     * @tc.expected: frame info not record.
     */
    taskScheduler.AddDirtyRenderNode(frameNode);
    taskScheduler.AddDirtyRenderNode(frameNode2);
    taskScheduler.FlushRenderTask(false);
    EXPECT_EQ(frameInfo.renderInfos_.size(), 0);

    /**
     * @tc.steps6: add renderNode again and set isRenderDirtyMarked_ true  and recall FlushRenderTask with false.
     * @tc.expected: frame info record true frameInfo.renderInfos_.size is 1.
     */
    frameNode2->isRenderDirtyMarked_ = true;
    pattern->AttachToFrameNode(frameNode2);
    taskScheduler.AddDirtyRenderNode(frameNode2);
    taskScheduler.FlushRenderTask(false);
    EXPECT_EQ(frameInfo.renderInfos_.size(), 1);

    /**
     * @tc.steps7: add layoutNode again and call FlushRenderTask with true and stop record info .
     * @tc.expected: frame info record true frameInfo.renderInfos_.size is 1.
     */
    frameNode2->isRenderDirtyMarked_ = true;
    taskScheduler.AddDirtyRenderNode(frameNode2);
    taskScheduler.FinishRecordFrameInfo();
    taskScheduler.FlushRenderTask(true);
    EXPECT_EQ(frameInfo.renderInfos_.size(), 1);
}
} // namespace OHOS::Ace::NG
