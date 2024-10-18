/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "test/mock/core/common/mock_container.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace NG {
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
    auto callback = [&flag](int32_t input_1, int32_t input_2, int32_t input_3, int32_t input_4,
                        WindowSizeChangeReason type) { flag = !flag; };
    context_->surfaceChangedCallbackMap_[0] = callback;
    context_->surfaceChangedCallbackMap_[1] = nullptr;
    context_->ExecuteSurfaceChangedCallbacks(0, 0, WindowSizeChangeReason::ROTATION);
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
    EXPECT_EQ(context_->onWindowSizeChangeCallbacks_.size(), 2);
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
    context_->DumpPipelineInfo();
    EXPECT_NE(rt, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg041
 * @tc.desc: Test the function OnLayoutCompleted.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg041, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: frontend-ptr is non-null.
     */
    ContainerScope scope(DEFAULT_INSTANCE_ID);
    ASSERT_NE(context_, nullptr);
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    context_->weakFrontend_ = frontend;

    /**
     * @tc.steps2: test the function OnLayoutCompleted by TEST_TAG.
     * @tc.expected: frontend componentId_ is TEST_TAG
     */
    context_->OnLayoutCompleted(TEST_TAG);
    EXPECT_EQ(frontend->GetComponentId(), TEST_TAG);
    context_->weakFrontend_.Reset();
}

/**
 * @tc.name: PipelineContextTestNg042
 * @tc.desc: Test the function OnDrawCompleted.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg042, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: frontend-ptr is non-null.
     */

    ContainerScope scope(DEFAULT_INSTANCE_ID);
    ASSERT_NE(context_, nullptr);
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    context_->weakFrontend_ = frontend;

    /**
     * @tc.steps4: test the function OnDrawCompleted by TEST_TAG.
     * @tc.expected: frontend componentId_ is TEST_TAG
     */
    context_->OnDrawCompleted(TEST_TAG);
    EXPECT_EQ(frontend->GetComponentId(), TEST_TAG);
    context_->weakFrontend_.Reset();
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
    taskScheduler.AddDirtyLayoutNode(frameNode2);
    taskScheduler.FlushLayoutTask(false);
    EXPECT_EQ(frameInfo.layoutInfos_.size(), 1);

    /**
     * @tc.steps6: add layoutNode again and set isLayoutDirtyMarked_ true  and recall FlushLayoutTask with false .
     * @tc.expected: frame info record true frameInfo.layoutInfos_.size is 2.
     */
    taskScheduler.AddDirtyLayoutNode(frameNode2);
    frameNode2->isLayoutDirtyMarked_ = true;
    taskScheduler.FlushLayoutTask(false);
    EXPECT_EQ(frameInfo.layoutInfos_.size(), 2);

    /**
     * @tc.steps7: add layoutNode again and call FlushLayoutTask with true .
     * @tc.expected: frame info record true frameInfo.layoutInfos_.size is 3.
     */
    taskScheduler.AddDirtyLayoutNode(frameNode2);
    frameNode2->isLayoutDirtyMarked_ = true;
    taskScheduler.FlushLayoutTask(true);
    EXPECT_EQ(frameInfo.layoutInfos_.size(), 3);

    /**
     * @tc.steps8: finish FinishRecordFrameInfo and do step7.
     * @tc.expected: frame info stop record frameInfo.layoutInfos_.size is 3.
     */
    taskScheduler.FinishRecordFrameInfo();
    taskScheduler.AddDirtyLayoutNode(frameNode2);
    frameNode2->isLayoutDirtyMarked_ = true;
    taskScheduler.FlushLayoutTask(true);
    EXPECT_EQ(frameInfo.layoutInfos_.size(), 3);
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
    taskScheduler.AddDirtyLayoutNode(frameNode2);
    EXPECT_FALSE(taskScheduler.NeedAdditionalLayout());

    /**
     * @tc.steps4: Create a appropriate node and recall AddDirtyLayoutNode.
     * @tc.expected: NeedAdditionalLayout return true.
     */
    auto frameNode3 = FrameNode::GetOrCreateFrameNode(TEST_TAG, 3, nullptr);
    auto geometryTransition = AceType::MakeRefPtr<NG::GeometryTransition>("test", frameNode3);
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
    auto pattern = AceType::MakeRefPtr<Pattern>();
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
}

/**
 * @tc.name: UITaskSchedulerTestNg002
 * @tc.desc: Test FlushAfterLayoutTask.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, UITaskSchedulerTestNg006, TestSize.Level1)
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
    taskScheduler.AddPersistAfterLayoutTask([]() {});
    taskScheduler.AddPersistAfterLayoutTask(nullptr);
    EXPECT_EQ(taskScheduler.persistAfterLayoutTasks_.size(), 2);

    /**
     * @tc.steps4: Call FlushTask.
     * @tc.expected: afterLayoutTasks_ in the taskScheduler size is 0.
     */
    taskScheduler.FlushTask();
    EXPECT_EQ(taskScheduler.afterLayoutTasks_.size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg044
 * @tc.desc: Test the function FlushAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg044, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    /**
     * @tc.steps2: Call the function FlushAnimation with unempty scheduleTasks_.
     * @tc.expected: The nanoTimestamp of scheduleTask is equal to NANO_TIME_STAMP.
     */
    auto scheduleTask = AceType::MakeRefPtr<MockScheduleTask>();
    EXPECT_NE(scheduleTask->GetNanoTimestamp(), NANO_TIME_STAMP);

    /**
     * @tc.steps3: Call the function AddScheduleTask.
     * @tc.expected: The scheduleTasks_ has the task id.
     */
    auto id = context_->AddScheduleTask(scheduleTask);
    EXPECT_EQ(context_->scheduleTasks_.count(id), 1);

    /**
     * @tc.steps4: Call the function RemoveScheduleTask.
     * @tc.expected: The scheduleTasks_ does not have the task id.
     */
    context_->RemoveScheduleTask(id);
    EXPECT_EQ(context_->scheduleTasks_.count(id), 0);
}

/**
 * @tc.name: PipelineContextTestNg045
 * @tc.desc: Test the function FlushAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg045, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    ASSERT_TRUE(context_->needRenderNode_.empty());
    /**
     * @tc.steps2: Call the function FlushAnimation with unempty scheduleTasks_.
     * @tc.expected: The nanoTimestamp of scheduleTask is equal to NANO_TIME_STAMP.
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, 3, pattern);
    context_->SetNeedRenderNode(WeakPtr<FrameNode>(frameNode));
    EXPECT_EQ(context_->needRenderNode_.count(WeakPtr<FrameNode>(frameNode)), 1);

    /**
     * @tc.steps3: Call the function FlushPipelineImmediately.
     * @tc.expected: The nanoTimestamp of scheduleTask is equal to NANO_TIME_STAMP.
     */
    context_->FlushPipelineImmediately();
    EXPECT_TRUE(context_->isRebuildFinished_);
}

/**
 * @tc.name: PipelineContextTestNg046
 * @tc.desc: Test the function AddAnimationClosure and FlushAnimationClosure.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg046, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call AddAnimationClosure.
     * @tc.expected: The animationClosuresList_ has 1 element.
     */
    auto mockAnimation = []() -> void {};
    context_->AddAnimationClosure(mockAnimation);
    EXPECT_EQ(context_->animationClosuresList_.size(), 1);
    /**
     * @tc.steps3: call FlushAnimationClosure.
     * @tc.expected: The animationClosuresList_ has 1 element.
     */
    context_->FlushAnimationClosure();
    EXPECT_TRUE(context_->animationClosuresList_.empty());
}

/**
 * @tc.name: PipelineContextTestNg046
 * @tc.desc: Test the function GetStageManager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg047, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call GetStageManager.
     * @tc.expected: The stageManager is not null.
     */
    context_->SetupRootElement();
    auto stageManager = context_->GetStageManager();
    EXPECT_NE(stageManager, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg048
 * @tc.desc: Test the function GetSelectOverlayManager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg048, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call SetupRootElement.
     * @tc.expected: The selectOverlayManager is not null.
     */
    context_->SetupRootElement();
    auto selectOverlayManager = context_->GetSelectOverlayManager();
    EXPECT_NE(selectOverlayManager, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg049
 * @tc.desc: Test the function GetFullScreenManager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg049, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call GetFullScreenManager.
     * @tc.expected: The fullScreenManager is not null.
     */
    context_->SetupRootElement();
    auto fullScreenManager = context_->GetFullScreenManager();
    EXPECT_NE(fullScreenManager, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg050
 * @tc.desc: Test the function UpdateSystemSafeArea and UpdateCutoutSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg050, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call AddAnimationClosure.
     * @tc.expected: The GetFullScreenManager is not null.
     */
    context_->SetMinPlatformVersion(10);
    SafeAreaInsets::Inset left { 0, 1 };
    SafeAreaInsets::Inset top { 0, 2 };
    SafeAreaInsets::Inset right { 0, 3 };
    SafeAreaInsets::Inset bottom { 0, 4 };
    SafeAreaInsets safeAreaInsets(left, top, right, bottom);
    context_->UpdateSystemSafeArea(safeAreaInsets);
    EXPECT_EQ(context_->safeAreaManager_->systemSafeArea_, safeAreaInsets);

    context_->UpdateCutoutSafeArea(safeAreaInsets);
    EXPECT_NE(context_->safeAreaManager_->cutoutSafeArea_, safeAreaInsets);

    context_->UpdateNavSafeArea(safeAreaInsets);

    EXPECT_EQ(context_->safeAreaManager_->navSafeArea_, safeAreaInsets);

    context_->SetIsLayoutFullScreen(true);
    context_->SetIsLayoutFullScreen(false);
    context_->SetIsNeedAvoidWindow(true);
    context_->SetIsNeedAvoidWindow(false);
    EXPECT_TRUE(context_->IsEnableKeyBoardAvoidMode());
}

/**
 * @tc.name: PipelineContextTestNg051
 * @tc.desc: Test the function SetIgnoreViewSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg051, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call SetIgnoreViewSafeArea.
     * @tc.expected: The ignoreSafeArea_ is true.
     */
    context_->safeAreaManager_->ignoreSafeArea_ = false;
    context_->SetIgnoreViewSafeArea(true);
    EXPECT_TRUE(context_->safeAreaManager_->ignoreSafeArea_);
}

/**
 * @tc.name: PipelineContextTestNg052
 * @tc.desc: Test the function SyncSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg052, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call SyncSafeArea.
     * @tc.expected: The isLayoutDirtyMarked_ is true.
     */
    context_->SetupRootElement();
    auto frameNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId, nullptr);
    context_->safeAreaManager_->AddGeoRestoreNode(frameNode);
    context_->SyncSafeArea(SafeAreaSyncType::SYNC_TYPE_NONE);
    EXPECT_TRUE(frameNode->isLayoutDirtyMarked_);
}

/**
 * @tc.name: PipelineContextTestNg053
 * @tc.desc: Test the function FindNavigationNodeToHandleBack.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg053, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call FindNavigationNodeToHandleBack.
     * @tc.expected: The ret is nullptr.
     */
    context_->SetupRootElement();
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto node = NavigationGroupNode::GetOrCreateGroupNode(
        TEST_TAG, nodeId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    node->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNode = NavigationGroupNode::GetOrCreateGroupNode(
        TEST_TAG, childId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    childNode->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    node->AddChild(childNode);
    context_->GetNavigationController(std::to_string(nodeId));
    context_->AddOrReplaceNavigationNode(std::to_string(childId), AceType::WeakClaim(AceType::RawPtr(childNode)));
    context_->DeleteNavigationNode(std::to_string(childId));
    context_->AddNavigationNode(nodeId, AceType::WeakClaim(AceType::RawPtr(node)));
    context_->RemoveNavigationNode(nodeId, nodeId);
    context_->FirePageChanged(nodeId, false);
    EXPECT_EQ(context_->FindNavigationNodeToHandleBack(node), nullptr);
}

/**
 * @tc.name: PipelineContextTestNg054
 * @tc.desc: Test the function AddAfterLayoutTask and AddAfterRenderTask.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg054, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call AddAfterLayoutTask.
     * @tc.expected: The afterLayoutTasks_ size is 1.
     */
    context_->SetupRootElement();
    context_->AddAfterLayoutTask([]() -> void {});
    EXPECT_EQ(context_->taskScheduler_->afterLayoutTasks_.size(), 1);
    /**
     * @tc.steps3: call AddAfterLayoutTask.
     * @tc.expected: The afterLayoutTasks_ size is 1.
     */
    context_->AddAfterRenderTask([]() -> void {});
    EXPECT_EQ(context_->taskScheduler_->afterRenderTasks_.size(), 1);
}

/**
 * @tc.name: PipelineContextTestNg055
 * @tc.desc: Test the function AddFontNodeNG and RemoveFontNodeNG.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg055, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call AddFontNodeNG.
     * @tc.expected: fontNodesNG_.size() is 1.
     */
    context_->SetupRootElement();
    context_->fontManager_ = AceType::MakeRefPtr<MockFontManager>();
    auto fontNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto fontNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, fontNodeId, nullptr);
    context_->AddFontNodeNG(fontNode);
    EXPECT_EQ(context_->GetFontManager()->fontNodesNG_.size(), 1);
    /**
     * @tc.steps2: call RemoveFontNodeNG.
     * @tc.expected: fontNodesNG_.size() is 0.
     */
    context_->RemoveFontNodeNG(fontNode);
    EXPECT_EQ(context_->GetFontManager()->fontNodesNG_.size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg056
 * @tc.desc: Test the function AddFontNodeNG and RemoveFontNodeNG.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg056, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call IsWindowSceneConsumed.
     * @tc.expected: The return is false.
     */
    context_->SetupRootElement();
    EXPECT_FALSE(context_->IsWindowSceneConsumed());
    /**
     * @tc.steps2: call SetWindowSceneConsumed(true) and IsWindowSceneConsumed.
     * @tc.expected: The return is true.
     */
    context_->SetWindowSceneConsumed(true);
    EXPECT_TRUE(context_->IsWindowSceneConsumed());
}

/**
 * @tc.name: PipelineContextTestNg057
 * @tc.desc: Test the function AddFontNodeNG and RemoveFontNodeNG.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg057, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    auto needRenderNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto needRenderNode = FrameNode::GetOrCreateFrameNode(TEST_TAG, needRenderNodeId, nullptr);
    context_->SetNeedRenderNode(WeakPtr<FrameNode>(needRenderNode));
    EXPECT_EQ(context_->needRenderNode_.count(WeakPtr<FrameNode>(needRenderNode)), 1);
    context_->InspectDrew();
    EXPECT_EQ(context_->needRenderNode_.count(WeakPtr<FrameNode>(needRenderNode)), 0);
}

/**
 * @tc.name: PipelineContextTestNg058
 * @tc.desc: Test the function FlushMouseEventG.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg058, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    /**
     * @tc.steps2: Call the function FlushMouseEvent with default action.
     * @tc.expected: The function is called and cover branch mouseAction is not WINDOW_LEAVE.
     */
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>();
    context_->FlushMouseEvent();
    auto result = context_->lastMouseEvent_->action == MouseAction::WINDOW_LEAVE;
    EXPECT_FALSE(result);

    /**
     * @tc.steps3: Call the function FlushMouseEvent with lastMouseEvent_ is nullptr.
     * @tc.expected: The function is called and cover branch lastMouseEvent_ is nullptr.
     */
    context_->lastMouseEvent_ = nullptr;
    context_->FlushMouseEvent();
    EXPECT_EQ(context_->lastMouseEvent_, nullptr);

    /**
     * @tc.steps4: Call the function FlushMouseEvent with mouseAction is  WINDOW_LEAVE.
     * @tc.expected: The function is called and cover branch mouseAction is WINDOW_LEAVE.
     */
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>();
    context_->lastMouseEvent_->action = MouseAction::WINDOW_LEAVE;
    context_->FlushMouseEvent();
    result = context_->lastMouseEvent_->action == MouseAction::WINDOW_LEAVE;
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PipelineContextTestNg059
 * @tc.desc: Test the function OnIdle.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg059, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    /**
     * @tc.steps2: Call the function OnIdle with canUseLongPredictTask_.
     * @tc.expected: called OnIdle and cover branch canUseLongPredictTask_ is true.
     */
    context_->canUseLongPredictTask_ = true;
    context_->OnIdle(1);
    EXPECT_TRUE(context_->touchEvents_.empty());

    /**
     * @tc.steps3: Call the function OnIdle with touchEvents_ is not empty.
     * @tc.expected: The value of flagCbk changed.
     */
    bool flagCbk = false;
    context_->AddPredictTask([&flagCbk](int64_t, bool) { flagCbk = true; });
    TouchEvent event;
    event.id = RENDER_EVENT_ID;
    context_->touchEvents_.push_back(event);
    context_->canUseLongPredictTask_ = true;
    context_->OnIdle(2);
    EXPECT_TRUE(flagCbk);
}

/**
 * @tc.name: PipelineContextTestNg062
 * @tc.desc: Test the function SetCursor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg062, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    ASSERT_NE(context_->GetWindow(), nullptr);
    ASSERT_EQ(context_->GetWindow()->cursor_, MouseFormat::DEFAULT);

    /**
     * @tc.steps2: set cursor with an exceptional value.
     * @tc.expected: context_->cursor_ is MouseFormat::DEFAULT.
     */
    context_->SetCursor(EXCEPTIONAL_CURSOR);
    ASSERT_NE(context_->GetWindow(), nullptr);
    ASSERT_EQ(context_->GetWindow()->cursor_, MouseFormat::DEFAULT);

    /**
     * @tc.steps3: set cursor with a normal value.
     * @tc.expected: context_->cursor_ is correct value.
     */
    context_->SetCursor(static_cast<int32_t>(MouseFormat::EAST));
    ASSERT_NE(context_->GetWindow(), nullptr);
    ASSERT_EQ(context_->GetWindow()->cursor_, MouseFormat::EAST);

    /**
     * @tc.steps4: restore mouse style.
     * @tc.expected: context_->cursor_ is MouseFormat::DEFAULT.
     */
    context_->RestoreDefault();
    ASSERT_NE(context_->GetWindow(), nullptr);
    ASSERT_EQ(context_->GetWindow()->cursor_, MouseFormat::DEFAULT);
}

/**
 * @tc.name: PipelineContextTestNg063
 * @tc.desc: Test the function OpenFrontendAnimation and CloseFrontendAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg063, TestSize.Level1)
{
    decltype(context_->pendingFrontendAnimation_) temp;
    std::swap(context_->pendingFrontendAnimation_, temp);
    /**
     * @tc.steps1: Call CloseFrontAnimation directly.
     * @tc.expected: No animation is generated. The pending flag stack is empty.
     */
    context_->CloseFrontendAnimation();
    EXPECT_EQ(context_->pendingFrontendAnimation_.size(), 0);
    /**
     * @tc.steps2: Call OpenFrontendAnimation.
     * @tc.expected: A pending flag is pushed to the stack.
     */
    AnimationOption option(Curves::EASE, 1000);
    context_->OpenFrontendAnimation(option, option.GetCurve(), nullptr);
    EXPECT_EQ(context_->pendingFrontendAnimation_.size(), 1);
    /**
     * @tc.steps3: Call CloseFrontendAnimation after OpenFrontendAnimation.
     * @tc.expected: The pending flag is out of stack.
     */
    context_->CloseFrontendAnimation();
    EXPECT_EQ(context_->pendingFrontendAnimation_.size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg064
 * @tc.desc: Test history and current.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg064, TestSize.Level1)
{
    /**
     * @tc.steps1: history and current timestamps are equal to nanoTimeStamp
     * @tc.expected: Expect the result to be (0.0, 0.0)
     */
    std::tuple<float, float, uint64_t> history_fs = std::make_tuple(1.0f, 1.0f, 1000);
    std::tuple<float, float, uint64_t> current_fs = std::make_tuple(2.0f, 2.0f, 2000);
    uint64_t nanoTimeStampFs = 1000;
    auto result_fs = context_->LinearInterpolation(history_fs, current_fs, nanoTimeStampFs);
    EXPECT_EQ(result_fs, std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f));

    /**
     * @tc.steps2: history and current timestamps are equal to nanoTimeStamp
     * @tc.expected: Expect the result to be (0.0, 0.0)
     */
    std::tuple<float, float, uint64_t> history_se = std::make_tuple(1.0f, 1.0f, 2000);
    std::tuple<float, float, uint64_t> current_se = std::make_tuple(2.0f, 2.0f, 1000);
    uint64_t nanoTimeStampSe = 1500;
    auto result_se = context_->LinearInterpolation(history_se, current_se, nanoTimeStampSe);
    EXPECT_EQ(result_se, std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f));

    /**
     * @tc.steps3: history and current timestamps are equal to nanoTimeStamp
     * @tc.expected: Expect the result to be (1.75, 1.75)
     */
    std::tuple<float, float, uint64_t> history_th = std::make_tuple(1.0f, 1.0f, 1000);
    std::tuple<float, float, uint64_t> current_th = std::make_tuple(2.0f, 2.0f, 3000);
    uint64_t nanoTimeStampTh = 2500;
    auto result_th = context_->LinearInterpolation(history_th, current_th, nanoTimeStampTh);
    EXPECT_EQ(result_th, std::make_tuple(1.75f, 1.75f, 500000.0f, 500000.0f));

    /**
     * @tc.steps4: nanoTimeStamp is less than history timestamp
     * @tc.expected: Expect the result to be (0.0, 0.0)
     */
    std::tuple<float, float, uint64_t> history_for = std::make_tuple(1.0f, 1.0f, 1000);
    std::tuple<float, float, uint64_t> current_for = std::make_tuple(2.0f, 2.0f, 2000);
    uint64_t nanoTimeStampFor = 500;
    auto result_for = context_->LinearInterpolation(history_for, current_for, nanoTimeStampFor);
    EXPECT_EQ(result_for, std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f));

    /**
     * @tc.steps5: nanoTimeStamp is less than current timestamp
     * @tc.expected: Expect non-zero value
     */
    std::tuple<float, float, uint64_t> history_fie = std::make_tuple(1.0f, 1.0f, 1000);
    std::tuple<float, float, uint64_t> current_fie = std::make_tuple(2.0f, 2.0f, 2000);
    uint64_t nanoTimeStampFie = 1500;
    auto result_fie = context_->LinearInterpolation(history_fie, current_fie, nanoTimeStampFie);
    EXPECT_NE(result_fie, std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f));

    /**
     * @tc.steps6: nanoTimeStamp is greater than current timestamp
     * @tc.expected: Expect non-zero value
     */
    std::tuple<float, float, uint64_t> history_six = std::make_tuple(1.0f, 1.0f, 1000);
    std::tuple<float, float, uint64_t> current_six = std::make_tuple(2.0f, 2.0f, 2000);
    uint64_t nanoTimeStampSix = 2500;
    auto result_six = context_->LinearInterpolation(history_six, current_six, nanoTimeStampSix);
    EXPECT_NE(result_six, std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f));
}

/**
 * @tc.name: PipelineContextTestNg065
 * @tc.desc: Test history and current.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg065, TestSize.Level1)
{
    /**
     * @tc.steps1: GetResampleCoord illegal value verification
     * @tc.expected: All result is 0.0f.
     */
    std::vector<TouchEvent> emptyHistory;
    std::vector<TouchEvent> emptyCurrent;
    uint64_t nanoTimeStamp = 1234567890;
    bool isScreen = true;
    std::tuple<float, float, float, float> result =
        context_->GetResampleCoord(emptyHistory, emptyCurrent, nanoTimeStamp, isScreen);
    EXPECT_FLOAT_EQ(0.0f, std::get<0>(result));
    EXPECT_FLOAT_EQ(0.0f, std::get<1>(result));
    auto timeStampAce = TimeStamp(std::chrono::nanoseconds(1000));
    emptyHistory.push_back(TouchEvent {}.SetX(100.0f).SetY(200.0f).SetTime(timeStampAce));
    result = context_->GetResampleCoord(emptyHistory, emptyCurrent, nanoTimeStamp, isScreen);
    EXPECT_FLOAT_EQ(0.0f, std::get<0>(result));
    EXPECT_FLOAT_EQ(0.0f, std::get<1>(result));
    emptyHistory.clear();
    auto timeStampTwo = TimeStamp(std::chrono::nanoseconds(2000));
    emptyCurrent.push_back(TouchEvent {}.SetX(200.0f).SetY(300.0f).SetTime(timeStampTwo));
    result = context_->GetResampleCoord(emptyHistory, emptyCurrent, nanoTimeStamp, isScreen);
    EXPECT_FLOAT_EQ(0.0f, std::get<0>(result));
    EXPECT_FLOAT_EQ(0.0f, std::get<1>(result));
}

/**
 * @tc.name: PipelineContextTestNg066
 * @tc.desc: Test history and current.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg066, TestSize.Level1)
{
    auto timeStampAce = TimeStamp(std::chrono::nanoseconds(1000));
    auto timeStampTwo = TimeStamp(std::chrono::nanoseconds(2000));
    auto timeStampThree = TimeStamp(std::chrono::nanoseconds(3000));
    auto timeStampFour = TimeStamp(std::chrono::nanoseconds(2000));
    std::vector<TouchEvent> history;
    history.push_back(TouchEvent {}.SetX(100.0f).SetY(200.0f).SetTime(timeStampAce));
    history.push_back(TouchEvent {}.SetX(150.0f).SetY(250.0f).SetTime(timeStampTwo));
    std::vector<TouchEvent> current;
    current.push_back(TouchEvent {}.SetX(200.0f).SetY(300.0f).SetTime(timeStampThree));
    current.push_back(TouchEvent {}.SetX(250.0f).SetY(350.0f).SetTime(timeStampFour));

    auto resampledCoord = context_->GetResampleCoord(history, current, 30000000, true);

    ASSERT_FLOAT_EQ(200.0f, std::get<0>(resampledCoord));
    ASSERT_FLOAT_EQ(300.0f, std::get<1>(resampledCoord));

    SystemProperties::debugEnabled_ = true;
    resampledCoord = context_->GetResampleCoord(history, current, 2500, true);
    ASSERT_FLOAT_EQ(0.0f, std::get<0>(resampledCoord));
    ASSERT_FLOAT_EQ(0.0f, std::get<1>(resampledCoord));
}

/**
 * @tc.name: PipelineContextTestNg068
 * @tc.desc: Test history and current.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg068, TestSize.Level1)
{
    auto timeStampAce = TimeStamp(std::chrono::nanoseconds(1000));
    auto timeStampTwo = TimeStamp(std::chrono::nanoseconds(2000));
    std::vector<TouchEvent> current;
    current.push_back(TouchEvent {}.SetX(100.0f).SetY(200.0f).SetTime(timeStampAce));
    current.push_back(TouchEvent {}.SetX(150.0f).SetY(250.0f).SetTime(timeStampTwo));
    uint64_t nanoTimeStamp = 1500;

    TouchEvent latestPoint = context_->GetLatestPoint(current, nanoTimeStamp);

    ASSERT_FLOAT_EQ(100.0f, latestPoint.x);
    ASSERT_FLOAT_EQ(200.0f, latestPoint.y);
}

/**
 * @tc.name: PipelineContextTestNg069
 * @tc.desc: Test history and current.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg069, TestSize.Level1)
{
    auto timeStampAce = TimeStamp(std::chrono::nanoseconds(1000));
    auto timeStampTwo = TimeStamp(std::chrono::nanoseconds(2000));
    auto timeStampThree = TimeStamp(std::chrono::nanoseconds(3000));
    auto timeStampFour = TimeStamp(std::chrono::nanoseconds(4000));
    std::vector<TouchEvent> history;
    history.push_back(TouchEvent {}.SetX(100.0f).SetY(200.0f).SetTime(timeStampAce));
    history.push_back(TouchEvent {}.SetX(150.0f).SetY(250.0f).SetTime(timeStampTwo));
    std::vector<TouchEvent> current;
    current.push_back(TouchEvent {}.SetX(200.0f).SetY(300.0f).SetTime(timeStampThree));
    current.push_back(TouchEvent {}.SetX(250.0f).SetY(350.0f).SetTime(timeStampFour));
    uint64_t nanoTimeStamp = 2500;

    TouchEvent resampledTouchEvent;
    context_->GetResampleTouchEvent(history, current, nanoTimeStamp, resampledTouchEvent);

    ASSERT_FLOAT_EQ(175.0f, resampledTouchEvent.x);
    ASSERT_FLOAT_EQ(275.0f, resampledTouchEvent.y);
}

/**
 * @tc.name: PipelineContextTestNg070
 * @tc.desc: Test GetLatestPoint.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg070, TestSize.Level1)
{
    std::vector<TouchEvent> events;

    TouchEvent event;
    event.time = TimeStamp(std::chrono::nanoseconds(1000));
    events.push_back(event);

    TouchEvent result = context_->GetLatestPoint(events, 1000);
    ASSERT_EQ(static_cast<uint64_t>(result.time.time_since_epoch().count()), 1000);
}

/**
 * @tc.name: PipelineContextTestNg071
 * @tc.desc: Test GetLatestPoint.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg071, TestSize.Level1)
{
    std::vector<TouchEvent> events;

    TouchEvent eventAce;
    eventAce.time = TimeStamp(std::chrono::nanoseconds(2000));
    events.push_back(eventAce);

    TouchEvent eventTwo;
    eventTwo.time = TimeStamp(std::chrono::nanoseconds(3000));
    events.push_back(eventTwo);

    uint64_t nanoTimeStamp = 1500;

    TouchEvent result = context_->GetLatestPoint(events, nanoTimeStamp);
    ASSERT_GT(static_cast<uint64_t>(result.time.time_since_epoch().count()), nanoTimeStamp);
}

/**
 * @tc.name: PipelineContextTestNg072
 * @tc.desc: Test GetLatestPoint.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg072, TestSize.Level1)
{
    std::vector<TouchEvent> events;

    TouchEvent eventAce;
    eventAce.time = TimeStamp(std::chrono::nanoseconds(500));
    events.push_back(eventAce);

    TouchEvent eventTwo;
    eventTwo.time = TimeStamp(std::chrono::nanoseconds(1000));
    events.push_back(eventTwo);

    uint64_t nanoTimeStamp = 1500;

    TouchEvent result = context_->GetLatestPoint(events, nanoTimeStamp);
    ASSERT_LT(static_cast<uint64_t>(result.time.time_since_epoch().count()), nanoTimeStamp);
}

/**
 * @tc.name: PipelineContextTestNg073
 * @tc.desc: Test the function GetSafeArea and GetSafeAreaWithoutProcess.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg073, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: call UpdateSystemSafeArea and SetIgnoreViewSafeArea, then check the value of GetSafeArea
                and GetSafeAreaWithoutProcess.
     * @tc.expected: The GetSafeArea is empty, and the GetSafeAreaWithoutProcess is systemSafeArea.
     */
    SafeAreaInsets::Inset left { 0, 1 };
    SafeAreaInsets::Inset top { 0, 2 };
    SafeAreaInsets::Inset right { 0, 3 };
    SafeAreaInsets::Inset bottom { 0, 4 };
    SafeAreaInsets safeAreaInsets(left, top, right, bottom);

    SafeAreaInsets::Inset inset {};
    SafeAreaInsets emptySafeAreaInsets(inset, inset, inset, inset);

    context_->UpdateSystemSafeArea(safeAreaInsets);
    context_->SetIgnoreViewSafeArea(true);

    EXPECT_EQ(context_->safeAreaManager_->GetSafeArea(), emptySafeAreaInsets);
}

/**
 * @tc.name: PipelineContextTestNg074
 * @tc.desc: Test the function SetOnceVsyncListener.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg074, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    /**
     * @tc.steps2: Set a non-null function to context.
     * @tc.expected: The onceVsyncListener_ is non-null.
     */
    bool flag = false;
    auto getVsyncFunc = [&flag]() { flag = !flag; };
    context_->SetOnceVsyncListener(getVsyncFunc);
    EXPECT_TRUE(context_->HasOnceVsyncListener());

    /**
     * @tc.steps2: Set a null function to context.
     * @tc.expected: The onceVsyncListener_ is null.
     */
    context_->SetOnceVsyncListener(nullptr);
    EXPECT_FALSE(context_->HasOnceVsyncListener());
}

/**
 * @tc.name: PipelineContextTestNg075
 * @tc.desc: Test the function FlushOnceVsyncTask.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg075, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    /**
     * @tc.steps2: Set a non-null function to context and call FlushOnceVsyncTask.
     * @tc.expected: The onceVsyncListener_ is null and flag changes to true.
     */
    bool flag = false;
    auto getVsyncFunc = [&flag]() { flag = !flag; };
    context_->SetOnceVsyncListener(getVsyncFunc);
    context_->FlushOnceVsyncTask();
    EXPECT_FALSE(context_->HasOnceVsyncListener());
    EXPECT_TRUE(flag);

    /**
     * @tc.steps2: Set a non-null function to context and call FlushOnceVsyncTask.
     * @tc.expected: The onceVsyncListener_ is null and flag is still true.
     */
    context_->SetOnceVsyncListener(nullptr);
    context_->FlushOnceVsyncTask();
    EXPECT_FALSE(context_->HasOnceVsyncListener());
    EXPECT_TRUE(flag);
}

/**
+ * @tc.name: PipelineContextTestNg076
+ * @tc.desc: Test the function GetMainPipelineContext and NeedSoftKeyboard.
+ * @tc.type: FUNC
+ */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg076, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    /**
     * @tc.steps2: Get current pipeline
     * @tc.expected: pipeline is not null.
     */
    auto pipeline = PipelineContext::GetMainPipelineContext();
    EXPECT_NE(pipeline, nullptr);
    EXPECT_FALSE(pipeline->NeedSoftKeyboard());
    auto frameNode = FrameNode::GetOrCreateFrameNode("test", 10, nullptr);
    EXPECT_FALSE(pipeline->NeedSoftKeyboard());

    /**
     * @tc.steps3: Get current pipeline through the Container
     * @tc.expected: pipeline is null.
     */
    pipeline->foldStatusChangedCallbackMap_.emplace(1, [](FoldStatus folderStatus) {});
    pipeline->foldStatusChangedCallbackMap_.emplace(2, nullptr);
    pipeline->foldDisplayModeChangedCallbackMap_.emplace(1, [](FoldDisplayMode foldDisplayMode) {});
    pipeline->foldDisplayModeChangedCallbackMap_.emplace(2, nullptr);
    pipeline->transformHintChangedCallbackMap_.emplace(1, nullptr);
    pipeline->transformHintChangedCallbackMap_.emplace(2, [](uint32_t num) {});
    pipeline->OnFoldStatusChange(FoldStatus::EXPAND);
    pipeline->OnFoldDisplayModeChange(FoldDisplayMode::FULL);
    pipeline->OnTransformHintChanged(0);
    EXPECT_NE(PipelineContext::GetContextByContainerId(0), nullptr);
    pipeline->AddDirtyPropertyNode(frameNode);
    EXPECT_TRUE(pipeline->hasIdleTasks_);
    DelayedTask delayedTask;
    pipeline->delayedTasks_.push_back(delayedTask);
    DelayedTask delayedTask1;
    delayedTask1.timeStamp = GetSysTimestamp();
    delayedTask1.time = 1;
    pipeline->delayedTasks_.push_back(delayedTask1);
    pipeline->ProcessDelayTasks();
    EXPECT_EQ(pipeline->delayedTasks_.size(), 1);
}

/**
+ * @tc.name: PipelineContextTestNg077
+ * @tc.desc: Test the function HandleFocusNode.
+ * @tc.type: FUNC
+ */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg077, TestSize.Level1)
{
    /**
     * @tc.steps1: Get current pipeline
     * @tc.expected: pipeline is null.
     */
    auto pipeline = PipelineContext::GetMainPipelineContext();
    EXPECT_NE(pipeline, nullptr);

    /**
     * @tc.steps2: Changing node information affects the return results.
     * @tc.expected:return frameNode is not null.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode("test", 5, nullptr);
    auto frameNode1 = FrameNode::GetOrCreateFrameNode("test", 6, nullptr);
    auto frameNode2 = FrameNode::GetOrCreateFrameNode("test", 7, nullptr);
    frameNode->GetOrCreateFocusHub();
    frameNode1->GetOrCreateFocusHub()->currentFocus_ = false;
    frameNode2->GetOrCreateFocusHub()->currentFocus_ = true;
    frameNode1->GetOrCreateFocusHub()->SetFocusType(FocusType::NODE);
    frameNode2->GetOrCreateFocusHub()->SetFocusType(FocusType::NODE);
    frameNode->AddChild(frameNode1);
    frameNode->AddChild(frameNode2);
    pipeline->SetScreenNode(frameNode);
    frameNode1->GetOrCreateFocusHub()->currentFocus_ = true;
    auto frameNode3 = FrameNode::GetOrCreateFrameNode("test", 8, nullptr);
    auto frameNode4 = FrameNode::GetOrCreateFrameNode("test", 9, nullptr);
    frameNode2->AddChild(frameNode3);
    frameNode2->AddChild(frameNode4);
    frameNode2->GetOrCreateFocusHub()->focusable_ = true;
    frameNode3->GetOrCreateFocusHub()->currentFocus_ = false;
    frameNode4->GetOrCreateFocusHub()->currentFocus_ = true;
    frameNode4->GetOrCreateFocusHub()->focusable_ = false;
    frameNode3->GetOrCreateFocusHub()->SetFocusType(FocusType::NODE);
    frameNode4->GetOrCreateFocusHub()->SetFocusType(FocusType::NODE);
}

/**
+ * @tc.name: PipelineContextTestNg078
+ * @tc.desc: Test the function HandleFocusNode.
+ * @tc.type: FUNC
+ */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg078, TestSize.Level1)
{
    /**
     * @tc.steps1: Get current pipeline
     * @tc.expected: pipeline is not null.
     */
    auto pipeline = PipelineContext::GetMainPipelineContext();
    EXPECT_NE(pipeline, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode("test", 5, nullptr);
    pipeline->StartFullToMultWindowAnimation(DEFAULT_INT3, DEFAULT_INT3, WindowSizeChangeReason::RECOVER);
    pipeline->StartFullToMultWindowAnimation(DEFAULT_INT3, DEFAULT_INT3, WindowSizeChangeReason::FULL_TO_FLOATING);
    pipeline->AvoidanceLogic(0.0);
    EXPECT_EQ(pipeline->finishFunctions_.size(), 0);
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    EXPECT_FALSE(pipeline->DumpPageViewData(nullptr, viewDataWrap));
    EXPECT_FALSE(pipeline->DumpPageViewData(frameNode, viewDataWrap));
    EXPECT_FALSE(pipeline->CheckNeedAutoSave());
    pipeline->NotifyFillRequestSuccess(AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET, viewDataWrap);
    pipeline->NotifyFillRequestFailed(frameNode, 101);

    /**
     * @tc.steps2: Partial addition of function execution.
     * @tc.expected:Change the state of the pipeline.
     */
    auto formCallback = [](bool visible) {};
    pipeline->ContainerModalUnFocus();
    pipeline->windowModal_ = WindowModal::NORMAL;
    pipeline->SetContainerModalTitleHeight(0);
    pipeline->UpdateTitleInTargetPos(false, 0);
    pipeline->SetContainerModalTitleVisible(false, true);
    pipeline->SetCloseButtonStatus(false);
    pipeline->GetContainerModalTitleHeight();
    pipeline->windowModal_ = WindowModal::CONTAINER_MODAL;
    pipeline->GetContainerModalTitleHeight();
    pipeline->ContainerModalUnFocus();
    pipeline->UpdateTitleInTargetPos(false, 0);
    pipeline->SetCloseButtonStatus(true);
    pipeline->SetContainerModalTitleVisible(true, false);
    pipeline->SetContainerModalTitleHeight(0);
    pipeline->SetAppBgColor(Color::BLACK);
    auto frameNode1 = FrameNode::GetOrCreateFrameNode("test", 6, nullptr);
    pipeline->activeNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode1));
    pipeline->GetCurrentExtraInfo();
    pipeline->AddIsFocusActiveUpdateEvent(frameNode, formCallback);
    EXPECT_EQ(pipeline->isFocusActiveUpdateEvents_.size(), 1);
    pipeline->RemoveIsFocusActiveUpdateEvent(frameNode);
    EXPECT_EQ(pipeline->isFocusActiveUpdateEvents_.size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg074
 * @tc.desc: Test the function SetFontScale.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg079, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    float fontScale = 1.2f;
    context_->SetFontScale(fontScale);
    ASSERT_EQ(context_->fontScale_, fontScale);
}

/**
 * @tc.name: PipelineContextTestNg075
 * @tc.desc: Test the function SetFontWeightScale.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg080, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);

    float fontWeightScale = 1.2f;
    context_->SetFontWeightScale(fontWeightScale);
    ASSERT_EQ(context_->fontWeightScale_, fontWeightScale);
}

/**
 * @tc.name: PipelineContextTestNg081
 * @tc.desc: Test the function CheckNeedUpdateBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg081, TestSize.Level1)
{
    /**
     * @tc.step1: Set pipelineContext attribute isFormRender_ and renderingMode_.
     * @tc.expected: Render alphaValue is not equal to 75.
     */
    context_->isFormRender_ = false;
    context_->renderingMode_ = RENDERINGMODE_SINGLE_COLOR;
    Color color;
    context_->CheckNeedUpdateBackgroundColor(color);
    uint32_t alphaValue = color.GetAlpha();
    ASSERT_NE(alphaValue, 75);
}

/**
 * @tc.name: PipelineContextTestNg082
 * @tc.desc: Test the function CheckNeedUpdateBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg082, TestSize.Level1)
{
    /**
     * @tc.step1: Set pipelineContext attribute isFormRender_ and renderingMode_.
     * @tc.expected: Render alphaValue is not equal to 75.
     */
    context_->isFormRender_ = true;
    context_->renderingMode_ = RENDERINGMODE_FULL_COLOR;
    Color color;
    context_->CheckNeedUpdateBackgroundColor(color);
    uint32_t alphaValue = color.GetAlpha();
    ASSERT_NE(alphaValue, 75);
}

/**
 * @tc.name: PipelineContextTestNg083
 * @tc.desc: Test the function CheckNeedUpdateBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg083, TestSize.Level1)
{
    /**
     * @tc.step1: Set pipelineContext attribute isFormRender_ and renderingMode_.
     * @tc.expected: Render alphaValue is equal to 75.
     */
    context_->isFormRender_ = true;
    context_->renderingMode_ = RENDERINGMODE_SINGLE_COLOR;
    Color color;
    context_->CheckNeedUpdateBackgroundColor(color);
    uint32_t alphaValue = color.GetAlpha();
    ASSERT_EQ(alphaValue, 75);
}

/**
 * @tc.name: PipelineContextTestNg084
 * @tc.desc: Test the function CheckNeedDisableUpdateBackgroundImage.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg084, TestSize.Level1)
{
    /**
     * @tc.step1: Set pipelineContext attribute isFormRender_ and renderingMode_.
     * @tc.expected: No update background image.
     */
    context_->isFormRender_ = false;
    context_->renderingMode_ = RENDERINGMODE_SINGLE_COLOR;
    bool isUpdateBGIamge = context_->CheckNeedDisableUpdateBackgroundImage();
    ASSERT_NE(isUpdateBGIamge, true);
}

/**
 * @tc.name: PipelineContextTestNg085
 * @tc.desc: Test the function CheckNeedDisableUpdateBackgroundImage.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg085, TestSize.Level1)
{
    /**
     * @tc.step1: Set pipelineContext attribute isFormRender_ and renderingMode_.
     * @tc.expected: No update background image.
     */
    context_->isFormRender_ = true;
    context_->renderingMode_ = RENDERINGMODE_FULL_COLOR;
    bool isUpdateBGIamge = context_->CheckNeedDisableUpdateBackgroundImage();
    ASSERT_NE(isUpdateBGIamge, true);
}

/**
 * @tc.name: PipelineContextTestNg086
 * @tc.desc: Test the function CheckNeedDisableUpdateBackgroundImage.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg086, TestSize.Level1)
{
    /**
     * @tc.step1: Set pipelineContext attribute isFormRender_ and renderingMode_.
     * @tc.expected: Update background image.
     */
    context_->isFormRender_ = true;
    context_->renderingMode_ = RENDERINGMODE_SINGLE_COLOR;
    bool isUpdateBGIamge = context_->CheckNeedDisableUpdateBackgroundImage();
    ASSERT_EQ(isUpdateBGIamge, true);
}

/**
 * @tc.name: PipelineContextTestNg087
 * @tc.desc: Test the function ClearNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg087, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->dirtyPropertyNodes_.emplace(frameNode_);
    context_->needRenderNode_.emplace(WeakPtr<FrameNode>(frameNode_));
    context_->dirtyFocusNode_ = frameNode_;
    context_->dirtyFocusScope_ = frameNode_;
    context_->dirtyRequestFocusNode_ = frameNode_;
    context_->activeNode_ = frameNode_;
    context_->focusNode_ = frameNode_;

    /**
     * @tc.step2: detach framenode.
     */
    context_->DetachNode(frameNode_);

    EXPECT_NE(context_->dirtyPropertyNodes_.count(frameNode_), 1);
    EXPECT_NE(context_->needRenderNode_.count(WeakPtr<FrameNode>(frameNode_)), 1);
    EXPECT_NE(context_->dirtyFocusNode_, frameNode_);
    EXPECT_NE(context_->dirtyFocusScope_, frameNode_);
    EXPECT_NE(context_->dirtyRequestFocusNode_, frameNode_);
    EXPECT_NE(context_->activeNode_, frameNode_);
    EXPECT_NE(context_->focusNode_, frameNode_);
}

/**
 * @tc.name: UITaskSchedulerTestNg007
 * @tc.desc: Test AddLayoutNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, UITaskSchedulerTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps1: Create taskScheduler add layoutNode.
     */
    UITaskScheduler taskScheduler;
    auto layoutNode = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>(), false);

    /**
     * @tc.steps2: Call AddLayoutNode.
     * @tc.expected: taskScheduler.layoutNodes_.size() = 1
     */
    taskScheduler.AddLayoutNode(layoutNode);
    EXPECT_EQ(taskScheduler.layoutNodes_.size(), 1);
}

/**
 * @tc.name: UITaskSchedulerTestNg008
 * @tc.desc: Test SetLayoutNodeRect.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, UITaskSchedulerTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps1: Create taskScheduler add layoutNode.
     */
    UITaskScheduler taskScheduler;
    auto layoutNode1 = AceType::MakeRefPtr<FrameNode>("test1", -1, AceType::MakeRefPtr<Pattern>(), false);
    auto layoutNode2 = AceType::MakeRefPtr<FrameNode>("test2", -1, AceType::MakeRefPtr<Pattern>(), false);
    auto layoutNode3 = AceType::MakeRefPtr<FrameNode>("test3", -1, AceType::MakeRefPtr<Pattern>(), false);
    auto layoutNode4 = AceType::MakeRefPtr<FrameNode>("test4", -1, AceType::MakeRefPtr<Pattern>(), false);
    layoutNode3->SetIsFind(true);
    layoutNode2->SetOverlayNode(layoutNode4);
    taskScheduler.AddLayoutNode(layoutNode1);
    taskScheduler.AddLayoutNode(layoutNode2);
    taskScheduler.AddLayoutNode(layoutNode3);

    /**
     * @tc.steps2: Call SetLayoutNodeRect.
     */
    taskScheduler.SetLayoutNodeRect();
}

/**
 * @tc.name: UITaskSchedulerTestNg009
 * @tc.desc: Test FlushPersistAfterLayoutTask/FlushAfterRenderTask/FlushAfterLayoutCallbackInImplicitAnimationTask
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, UITaskSchedulerTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps1: Create taskScheduler add layoutNode.
     */
    UITaskScheduler taskScheduler;
    taskScheduler.AddPersistAfterLayoutTask([]() {});
    taskScheduler.AddPersistAfterLayoutTask(nullptr);
    taskScheduler.AddAfterRenderTask(nullptr);
    taskScheduler.AddAfterRenderTask([]() {});

    /**
     * @tc.steps2: Call FlushPersistAfterLayoutTask/FlushAfterRenderTask/FlushAfterLayoutCallbackInImplicitAnimationTask
     */
    taskScheduler.FlushPersistAfterLayoutTask();
    taskScheduler.FlushAfterRenderTask();
    taskScheduler.FlushAfterLayoutCallbackInImplicitAnimationTask();

    /**
     * @tc.steps3: Call FlushAfterLayoutCallbackInImplicitAnimationTask/FlushTask
     */
    taskScheduler.FlushTask(true);
    taskScheduler.FlushTask(false);
    taskScheduler.AddAfterLayoutTask([]() {}, true);
    taskScheduler.AddAfterLayoutTask(nullptr, true);
    taskScheduler.FlushAfterLayoutCallbackInImplicitAnimationTask();
    taskScheduler.FlushTask(false);
}

/**
 * @tc.name: PipelineContextTestNg095
 * @tc.desc: Test the function AddDirtyLayoutNode/AddDirtyRenderNode
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg095, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters,destroyed_ is false/true
     */
    auto frameNode1 = FrameNode::GetOrCreateFrameNode("test1", 1, nullptr);
    auto frameNode2 = FrameNode::GetOrCreateFrameNode("test2", 2, nullptr);
    context_->SetPredictNode(frameNode2);
    context_->PipelineContext::AddDirtyLayoutNode(frameNode1);
}

/**
 * @tc.name: PipelineContextTestNg096
 * @tc.desc: Test the function FlushFocusScroll
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg096, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters,isNeedTriggerScroll_ is false
     */
    RefPtr<FocusManager> focusManager = context_->GetOrCreateFocusManager();
    context_->PipelineContext::FlushFocusScroll();

    /**
     * @tc.steps2: initialize parameters,isNeedTriggerScroll_ is true
     */
    focusManager->SetNeedTriggerScroll(true);
    context_->PipelineContext::FlushFocusScroll();
}

/**
 * @tc.name: PipelineContextTestNg097
 * @tc.desc: Test the function RegisterTouchEventListener
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg097, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters,construct changeInfoListeners_
     */
    std::shared_ptr<ITouchEventCallback> touchEventCallback = nullptr;
    context_->RegisterTouchEventListener(touchEventCallback);
    ASSERT_EQ(context_->listenerVector_.size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg098
 * @tc.desc: Test the function AddChangedFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg098, TestSize.Level1)
{
    /**
     * @tc.steps1: AddChangedFrameNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", -1, AceType::MakeRefPtr<Pattern>(), false);
    EXPECT_FALSE(context_->AddChangedFrameNode(frameNode));
    context_->CleanNodeChangeFlag();
    EXPECT_FALSE(context_->AddChangedFrameNode(frameNode));
}

/**
 * @tc.name: PipelineContextTestNg099
 * @tc.desc: Test the function AddFrameNodeChangeListener
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg099, TestSize.Level1)
{
    /**
     * @tc.steps1: AddFrameNodeChangeListener
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", -1, AceType::MakeRefPtr<Pattern>(), false);
    context_->AddFrameNodeChangeListener(frameNode);
    context_->FlushNodeChangeFlag();
    EXPECT_EQ(context_->changeInfoListeners_.size(), 1);
    context_->AddFrameNodeChangeListener(frameNode);
    EXPECT_EQ(context_->changeInfoListeners_.size(), 1);
    context_->RemoveFrameNodeChangeListener(frameNode);
    context_->FlushNodeChangeFlag();
    EXPECT_EQ(context_->changeInfoListeners_.size(), 1);
}

/**
 * @tc.name: PipelineContextTestNg100
 * @tc.desc: Test the function UpdateHalfFoldHoverStatus
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg100, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);
    RefPtr<DisplayInfo> displayInfo = AceType::MakeRefPtr<DisplayInfo>();
    displayInfo->SetWidth(DEFAULT_INT10);
    displayInfo->SetHeight(DEFAULT_INT10);
    displayInfo->SetIsFoldable(true);
    displayInfo->SetFoldStatus(FoldStatus::HALF_FOLD);
    displayInfo->SetRotation(Rotation::ROTATION_90);
    MockContainer::Current()->SetDisplayInfo(displayInfo);
    context_->UpdateHalfFoldHoverStatus(DEFAULT_INT10, DEFAULT_INT10);
    ASSERT_EQ(context_->isHalfFoldHoverStatus_, true);
}

/**
 * @tc.name: MouseEvent01
 * @tc.desc: Test GetResampleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, MouseEvent01, TestSize.Level1)
{
    auto timeStampAce = TimeStamp(std::chrono::nanoseconds(1000));
    auto timeStampTwo = TimeStamp(std::chrono::nanoseconds(2000));
    auto timeStampThree = TimeStamp(std::chrono::nanoseconds(3000));
    auto timeStampFour = TimeStamp(std::chrono::nanoseconds(4000));
    std::vector<MouseEvent> history;
    MouseEvent historyMouseEvent1;
    historyMouseEvent1.x = 100.0f;
    historyMouseEvent1.y = 200.0f;
    historyMouseEvent1.time = timeStampAce;
    history.push_back(historyMouseEvent1);
    MouseEvent historyMouseEvent2;
    historyMouseEvent2.x = 150.0f;
    historyMouseEvent2.y = 250.0f;
    historyMouseEvent2.time = timeStampTwo;
    history.push_back(historyMouseEvent2);
    std::vector<MouseEvent> current;
    MouseEvent currentMouseEvent1;
    currentMouseEvent1.x = 200.0f;
    currentMouseEvent1.y = 300.0f;
    currentMouseEvent1.time = timeStampThree;
    current.push_back(currentMouseEvent1);
    MouseEvent currentMouseEvent2;
    currentMouseEvent2.x = 250.0f;
    currentMouseEvent2.y = 350.0f;
    currentMouseEvent2.time = timeStampFour;
    current.push_back(currentMouseEvent2);
    uint64_t nanoTimeStamp = 2500;

    MouseEvent resampledMouseEvent = context_->GetResampleMouseEvent(history, current, nanoTimeStamp);
    EXPECT_EQ(175.0f, resampledMouseEvent.x);
    EXPECT_EQ(275.0f, resampledMouseEvent.y);
}

/**
 * @tc.name: DragEvent01
 * @tc.desc: Test GetResamplePointerEvent
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, DragEvent01, TestSize.Level1)
{
    auto timeStampAce = TimeStamp(std::chrono::nanoseconds(1000));
    auto timeStampTwo = TimeStamp(std::chrono::nanoseconds(2000));
    auto timeStampThree = TimeStamp(std::chrono::nanoseconds(3000));
    auto timeStampFour = TimeStamp(std::chrono::nanoseconds(4000));

    std::vector<PointerEvent> history;
    PointerEvent historyDrageEvent1;
    historyDrageEvent1.x = 200;
    historyDrageEvent1.y = 300;
    historyDrageEvent1.time = timeStampAce;
    history.push_back(historyDrageEvent1);
    PointerEvent historyDrageEvent2;
    historyDrageEvent2.x = 250;
    historyDrageEvent2.y = 350;
    historyDrageEvent2.time = timeStampTwo;
    history.push_back(historyDrageEvent2);
    std::vector<PointerEvent> current;
    PointerEvent currentDragEvent1;
    currentDragEvent1.x = 300;
    currentDragEvent1.y = 400;
    currentDragEvent1.time = timeStampThree;
    current.push_back(currentDragEvent1);
    PointerEvent currentDragEvent2;
    currentDragEvent2.x = 350;
    currentDragEvent2.y = 450;
    currentDragEvent2.time = timeStampFour;
    current.push_back(currentDragEvent2);
    uint64_t nanoTimeStamp = 3100;

    PointerEvent resampledPointerEvent = context_->GetResamplePointerEvent(history, current, nanoTimeStamp);
    EXPECT_EQ(305, resampledPointerEvent.x);
    EXPECT_EQ(405, resampledPointerEvent.y);
}
} // namespace NG
} // namespace OHOS::Ace
