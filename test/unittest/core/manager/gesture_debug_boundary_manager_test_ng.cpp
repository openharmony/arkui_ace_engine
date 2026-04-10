/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "base/utils/system_properties.h"
#include "core/common/event_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/manager/gesture_debug/gesture_debug_boundary_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/render_context.h"
#undef protected
#undef private

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t TEST_NODE_ID_2 = 200;
constexpr float TEST_VALID_SIZE = 120.0f;
constexpr float TEST_SMALL_SIZE = 1.0f;
constexpr char TEST_TAG[] = "GestureDebugBoundaryTest";

class TestRenderContext final : public RenderContext {
public:
    void PaintGestureDebugBoundary(const std::optional<GestureDebugBoundaryInfo>& info) override
    {
        paintCalled = true;
        lastInfo = info;
    }

    bool paintCalled = false;
    std::optional<GestureDebugBoundaryInfo> lastInfo;
};

RefPtr<FrameNode> CreateFrameNode(int32_t nodeId)
{
    auto node = FrameNode::CreateFrameNode(TEST_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    auto pipeline = MockPipelineContext::GetCurrent();
    if (pipeline) {
        node->AttachToMainTree(false, AceType::RawPtr(pipeline));
    }
    auto geometry = node->GetGeometryNode();
    if (geometry) {
        geometry->SetFrameSize(SizeF(TEST_VALID_SIZE, TEST_VALID_SIZE));
    }
    return node;
}

void ResetEnv()
{
    SystemProperties::gestureDebugBoundaryEnabled_ = false;
}
} // namespace

class GestureDebugBoundaryManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        ResetEnv();
    }

    void TearDown() override
    {
        ResetEnv();
    }
};

/**
 * @tc.name: GestureDebugBoundaryManagerTest001
 * @tc.desc: HandleGestureAccept should return when feature switch is off or node is null.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create manager and node with default switch disabled.
     */
    GestureDebugBoundaryManager manager;
    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps: step2. call HandleGestureAccept when debug switch is off.
     * @tc.expected: step2. node state is not created.
     */
    manager.HandleGestureAccept(GestureListenerType::PAN, node);
    EXPECT_TRUE(manager.nodeStates_.empty());

    /**
     * @tc.steps: step3. enable switch and call HandleGestureAccept with null node.
     * @tc.expected: step3. node state is still empty.
     */
    SystemProperties::gestureDebugBoundaryEnabled_ = true;
    manager.HandleGestureAccept(GestureListenerType::PAN, nullptr);
    EXPECT_TRUE(manager.nodeStates_.empty());
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest002
 * @tc.desc: HandleGestureAccept should set active state and schedule delayed branch for tap.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare manager, node and mock task executor.
     */
    GestureDebugBoundaryManager manager;
    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>(true));

    /**
     * @tc.steps: step2. enable switch and call HandleGestureAccept for tap gesture.
     * @tc.expected: step2. tap bit is set and one delayed reset task is scheduled.
     */
    SystemProperties::gestureDebugBoundaryEnabled_ = true;
    manager.HandleGestureAccept(GestureListenerType::TAP, node);

    auto state = manager.GetNodeState(node->GetId());
    ASSERT_NE(state, nullptr);
    EXPECT_TRUE(state->activeGestures.test(0));
    EXPECT_EQ(state->delayedResetTasks.size(), 1);
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest003
 * @tc.desc: HandleGestureEnd should cover state-miss, erase-all and keep-active branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call HandleGestureEnd on an untracked node.
     * @tc.expected: step1. manager remains empty.
     */
    GestureDebugBoundaryManager manager;
    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    SystemProperties::gestureDebugBoundaryEnabled_ = true;
    manager.HandleGestureEnd(GestureListenerType::PAN, node);
    EXPECT_TRUE(manager.nodeStates_.empty());

    /**
     * @tc.steps: step2. prepare state with one active bit and end this gesture.
     * @tc.expected: step2. node state is erased.
     */
    GestureDebugBoundaryState oneActive;
    oneActive.node = WeakPtr<FrameNode>(node);
    oneActive.activeGestures.set(2);
    manager.nodeStates_[node->GetId()] = oneActive;
    manager.HandleGestureEnd(GestureListenerType::PAN, node);
    EXPECT_EQ(manager.GetNodeState(node->GetId()), nullptr);

    /**
     * @tc.steps: step3. prepare state with two active bits and end only tap.
     * @tc.expected: step3. remaining active bit stays in state.
     */
    GestureDebugBoundaryState twoActive;
    twoActive.node = WeakPtr<FrameNode>(node);
    twoActive.activeGestures.set(0);
    twoActive.activeGestures.set(2);
    manager.nodeStates_[node->GetId()] = twoActive;
    manager.HandleGestureEnd(GestureListenerType::TAP, node);
    auto stateAfterEnd = manager.GetNodeState(node->GetId());
    ASSERT_NE(stateAfterEnd, nullptr);
    EXPECT_TRUE(stateAfterEnd->activeGestures.test(2));
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest004
 * @tc.desc: HandleGestureEnd should keep node when delayed task remains pending.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare node state with one active bit and one pending delayed task.
     */
    GestureDebugBoundaryManager manager;
    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    SystemProperties::gestureDebugBoundaryEnabled_ = true;
    GestureDebugBoundaryState state;
    state.node = WeakPtr<FrameNode>(node);
    state.activeGestures.set(0);
    state.delayedResetTasks[GestureListenerType::SWIPE].Reset([]() {});
    manager.nodeStates_[node->GetId()] = state;

    /**
     * @tc.steps: step2. end tap while delayed task still exists.
     * @tc.expected: step2. node state is kept and active bits become empty.
     */
    manager.HandleGestureEnd(GestureListenerType::TAP, node);
    auto stateAfterEnd = manager.GetNodeState(node->GetId());
    ASSERT_NE(stateAfterEnd, nullptr);
    EXPECT_TRUE(stateAfterEnd->activeGestures.none());
    EXPECT_EQ(stateAfterEnd->delayedResetTasks.size(), 1);
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest005
 * @tc.desc: ClearNode should cover missing-node and valid-node branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ClearNode for non-existing node id.
     * @tc.expected: step1. manager state remains empty.
     */
    GestureDebugBoundaryManager manager;
    manager.ClearNode(TEST_NODE_ID);
    EXPECT_TRUE(manager.nodeStates_.empty());

    /**
     * @tc.steps: step2. insert valid node state with one delayed task and clear it.
     * @tc.expected: step2. node state is removed.
     */
    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);
    GestureDebugBoundaryState state;
    state.node = WeakPtr<FrameNode>(node);
    state.delayedResetTasks[GestureListenerType::PAN].Reset([]() {});
    manager.nodeStates_[node->GetId()] = state;

    manager.ClearNode(node->GetId());
    EXPECT_EQ(manager.GetNodeState(node->GetId()), nullptr);
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest006
 * @tc.desc: ScheduleDelayReset should cover state-miss and state-hit entry branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ScheduleDelayReset without pre-created node state.
     * @tc.expected: step1. function returns at state-miss branch and does not create task/state.
     */
    GestureDebugBoundaryManager manager;
    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>(true));

    manager.ScheduleDelayReset(GestureListenerType::TAP, TEST_NODE_ID, WeakPtr<FrameNode>(node));
    EXPECT_TRUE(manager.nodeStates_.empty());

    /**
     * @tc.steps: step2. pre-create node state, then call ScheduleDelayReset again.
     * @tc.expected: step2. function enters state-hit branch and creates one delayed task.
     */
    GestureDebugBoundaryState state;
    state.node = WeakPtr<FrameNode>(node);
    manager.nodeStates_[node->GetId()] = state;
    manager.ScheduleDelayReset(GestureListenerType::TAP, node->GetId(), WeakPtr<FrameNode>(node));
    auto stateAfterSchedule = manager.GetNodeState(node->GetId());
    ASSERT_NE(stateAfterSchedule, nullptr);
    EXPECT_EQ(stateAfterSchedule->delayedResetTasks.size(), 1);
    EXPECT_NE(stateAfterSchedule->delayedResetTasks.find(GestureListenerType::TAP),
        stateAfterSchedule->delayedResetTasks.end());
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest007
 * @tc.desc: ScheduleDelayReset should return early when pipeline context is null.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. tear down pipeline and call ScheduleDelayReset.
     * @tc.expected: step1. function returns early and no delayed task is created.
     */
    auto oldPipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(oldPipeline, nullptr);

    MockPipelineContext::TearDown();

    GestureDebugBoundaryManager manager;
    GestureDebugBoundaryState state;
    manager.nodeStates_[TEST_NODE_ID] = state;
    manager.ScheduleDelayReset(GestureListenerType::TAP, TEST_NODE_ID, WeakPtr<FrameNode>());
    auto stateAfterSchedule = manager.GetNodeState(TEST_NODE_ID);
    ASSERT_NE(stateAfterSchedule, nullptr);
    EXPECT_TRUE(stateAfterSchedule->delayedResetTasks.empty());

    /**
     * @tc.steps: step2. restore global mock environment.
     */
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest008
 * @tc.desc: ScheduleDelayReset callback should cover node-null, state-null and keep-state branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. schedule delayed reset with empty weak node and execute callback.
     * @tc.expected: step1. callback goes through ClearNode path and erases state.
     */
    auto manager = AceType::MakeRefPtr<GestureDebugBoundaryManager>();
    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>(true));

    GestureDebugBoundaryState eraseState;
    eraseState.node = WeakPtr<FrameNode>(node);
    eraseState.activeGestures.set(0);
    manager->nodeStates_[node->GetId()] = eraseState;
    manager->ScheduleDelayReset(GestureListenerType::TAP, node->GetId(), WeakPtr<FrameNode>());
    auto eraseStateAfterSchedule = manager->GetNodeState(node->GetId());
    ASSERT_NE(eraseStateAfterSchedule, nullptr);
    EXPECT_EQ(eraseStateAfterSchedule->delayedResetTasks.size(), 1);
    auto eraseCallback = eraseStateAfterSchedule->delayedResetTasks[GestureListenerType::TAP];
    eraseCallback();
    EXPECT_EQ(manager->GetNodeState(node->GetId()), nullptr);

    /**
     * @tc.steps: step2. schedule with valid weak node, erase state before callback executes.
     * @tc.expected: step2. callback hits state-null early-return branch and does not recreate state.
     */
    GestureDebugBoundaryState missingStateAfterSchedule;
    missingStateAfterSchedule.node = WeakPtr<FrameNode>(node);
    missingStateAfterSchedule.activeGestures.set(0);
    manager->nodeStates_[node->GetId()] = missingStateAfterSchedule;
    manager->ScheduleDelayReset(GestureListenerType::TAP, node->GetId(), WeakPtr<FrameNode>(node));
    auto stateBeforeErase = manager->GetNodeState(node->GetId());
    ASSERT_NE(stateBeforeErase, nullptr);
    auto stateNullCallback = stateBeforeErase->delayedResetTasks[GestureListenerType::TAP];
    manager->EraseNodeState(node->GetId());
    stateNullCallback();
    EXPECT_EQ(manager->GetNodeState(node->GetId()), nullptr);

    /**
     * @tc.steps: step3. schedule delayed reset with two active bits and valid weak node.
     * @tc.expected: step3. callback clears tap bit and keeps remaining active bit.
     */
    GestureDebugBoundaryState keepState;
    keepState.node = WeakPtr<FrameNode>(node);
    keepState.activeGestures.set(0);
    keepState.activeGestures.set(2);
    manager->nodeStates_[node->GetId()] = keepState;
    manager->ScheduleDelayReset(GestureListenerType::TAP, node->GetId(), WeakPtr<FrameNode>(node));
    auto keepStateAfterSchedule = manager->GetNodeState(node->GetId());
    ASSERT_NE(keepStateAfterSchedule, nullptr);
    auto keepCallback = keepStateAfterSchedule->delayedResetTasks[GestureListenerType::TAP];
    keepCallback();
    auto stateAfterCallback = manager->GetNodeState(node->GetId());
    ASSERT_NE(stateAfterCallback, nullptr);
    EXPECT_TRUE(stateAfterCallback->activeGestures.test(2));
    EXPECT_FALSE(stateAfterCallback->activeGestures.test(0));
    EXPECT_EQ(stateAfterCallback->delayedResetTasks.size(), 0);
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest009
 * @tc.desc: CancelDelayReset, GetNodeState and EraseNodeState should cover map hit/miss branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CancelDelayReset for miss/hit branches on delayed task map.
     * @tc.expected: step1. task map is empty after cancel.
     */
    GestureDebugBoundaryManager manager;
    GestureDebugBoundaryState state;

    manager.CancelDelayReset(GestureListenerType::PAN, state);
    EXPECT_TRUE(state.delayedResetTasks.empty());

    state.delayedResetTasks[GestureListenerType::PAN].Reset([]() {});
    manager.CancelDelayReset(GestureListenerType::PAN, state);
    EXPECT_TRUE(state.delayedResetTasks.empty());

    /**
     * @tc.steps: step2. verify GetNodeState and EraseNodeState on map miss/hit.
     * @tc.expected: step2. state can be found before erase and becomes null after erase.
     */
    EXPECT_EQ(manager.GetNodeState(TEST_NODE_ID), nullptr);
    manager.nodeStates_[TEST_NODE_ID] = GestureDebugBoundaryState {};
    EXPECT_NE(manager.GetNodeState(TEST_NODE_ID), nullptr);
    manager.EraseNodeState(TEST_NODE_ID);
    EXPECT_EQ(manager.GetNodeState(TEST_NODE_ID), nullptr);
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest010
 * @tc.desc: BuildRenderInfo should cover empty, null-node, null-context and threshold branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. verify BuildRenderInfo for empty state and null node with active state.
     * @tc.expected: step1. empty state returns default info, active+null node returns nullopt.
     */
    GestureDebugBoundaryManager manager;
    GestureDebugBoundaryState emptyState;
    auto emptyInfo = manager.BuildRenderInfo(nullptr, emptyState);
    ASSERT_TRUE(emptyInfo.has_value());
    EXPECT_EQ(emptyInfo->gestureMask, 0);

    GestureDebugBoundaryState activeState;
    activeState.activeGestures.set(2);
    auto nullNodeInfo = manager.BuildRenderInfo(nullptr, activeState);
    EXPECT_FALSE(nullNodeInfo.has_value());

    /**
     * @tc.steps: step2. verify null context branch by clearing attached context and current mock context.
     * @tc.expected: step2. BuildRenderInfo returns nullopt.
     */
    auto nodeWithoutContext = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(nodeWithoutContext, nullptr);
    nodeWithoutContext->GetGeometryNode()->SetFrameSize(SizeF(TEST_VALID_SIZE, TEST_VALID_SIZE));
    nodeWithoutContext->context_ = nullptr;

    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    auto nullContextInfo = manager.BuildRenderInfo(nodeWithoutContext, activeState);
    EXPECT_FALSE(nullContextInfo.has_value());

    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    /**
     * @tc.steps: step3. verify minimum size threshold branch.
     * @tc.expected: step3. small frame returns default empty info.
     */
    auto validNode = CreateFrameNode(TEST_NODE_ID_2);
    ASSERT_NE(validNode, nullptr);
    validNode->GetGeometryNode()->SetFrameSize(SizeF(TEST_SMALL_SIZE, TEST_SMALL_SIZE));
    auto smallSizeInfo = manager.BuildRenderInfo(validNode, activeState);
    ASSERT_TRUE(smallSizeInfo.has_value());
    EXPECT_EQ(smallSizeInfo->gestureMask, 0);
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest011
 * @tc.desc: BuildRenderInfo and ResolveGestureColor should cover normal path and fallback branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build render info for node with multiple active gesture bits.
     * @tc.expected: step1. mask matches active bits and color list is generated.
     */
    GestureDebugBoundaryManager manager;
    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    GestureDebugBoundaryState state;
    state.activeGestures.set(2);
    state.activeGestures.set(5);
    auto info = manager.BuildRenderInfo(node, state);
    ASSERT_TRUE(info.has_value());
    EXPECT_EQ(info->gestureMask, static_cast<uint8_t>(state.activeGestures.to_ulong()));
    EXPECT_EQ(info->colors.size(), 2);

    /**
     * @tc.steps: step2. verify ResolveGestureColor fallback for invalid type and null context.
     * @tc.expected: step2. both branches return Color::RED.
     */
    auto fallbackColor = manager.ResolveGestureColor(node, static_cast<GestureListenerType>(100));
    EXPECT_EQ(fallbackColor, Color::RED);

    auto nodeWithoutContext = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID_2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(nodeWithoutContext, nullptr);
    auto noContextColor = manager.ResolveGestureColor(nodeWithoutContext, GestureListenerType::PAN);
    EXPECT_EQ(noContextColor, Color::RED);
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest012
 * @tc.desc: NotifyNodeRefresh should cover null-node, null-render-context and normal branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. cover NotifyNodeRefresh null-node and null-render-context branches.
     */
    GestureDebugBoundaryManager manager;

    manager.NotifyNodeRefresh(nullptr, std::nullopt);

    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);
    auto rawRenderContext = node->renderContext_;
    node->renderContext_.Reset();
    manager.NotifyNodeRefresh(node, std::nullopt);
    node->renderContext_ = rawRenderContext;

    /**
     * @tc.steps: step2. install test render context and notify with valid info.
     * @tc.expected: step2. PaintGestureDebugBoundary is called and info is forwarded.
     */
    auto testRenderContext = AceType::MakeRefPtr<TestRenderContext>();
    testRenderContext->SetHostNode(WeakPtr<FrameNode>(node));
    node->renderContext_ = testRenderContext;

    GestureDebugBoundaryInfo info;
    info.gestureMask = 1;
    manager.NotifyNodeRefresh(node, info);
    EXPECT_TRUE(testRenderContext->paintCalled);
    ASSERT_TRUE(testRenderContext->lastInfo.has_value());
    EXPECT_EQ(testRenderContext->lastInfo->gestureMask, 1);
}

/**
 * @tc.name: GestureDebugBoundaryManagerTest013
 * @tc.desc: FrameNode::OnDetachFromMainTree should clear gesture debug node state when switch is enabled.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, GestureDebugBoundaryManagerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare frame node and pipeline context.
     */
    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. pre-create node state in gesture debug manager.
     * @tc.expected: step2. node state exists before detach.
     */
    auto eventManager = pipeline->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    auto gestureDebugMgr = eventManager->GetGestureDebugBoundaryManager();
    ASSERT_NE(gestureDebugMgr, nullptr);
    GestureDebugBoundaryState state;
    state.node = WeakPtr<FrameNode>(node);
    gestureDebugMgr->nodeStates_[node->GetId()] = state;
    EXPECT_NE(gestureDebugMgr->GetNodeState(node->GetId()), nullptr);

    /**
     * @tc.steps: step3. enable switch and call FrameNode::OnDetachFromMainTree.
     * @tc.expected: step3. node state is cleared by gesture debug manager.
     */
    SystemProperties::gestureDebugBoundaryEnabled_ = true;
    node->OnDetachFromMainTree(false, AceType::RawPtr(pipeline));
    EXPECT_EQ(gestureDebugMgr->GetNodeState(node->GetId()), nullptr);
}

} // namespace OHOS::Ace::NG