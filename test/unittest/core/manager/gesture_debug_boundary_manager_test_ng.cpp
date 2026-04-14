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

#ifdef GESTURE_DEBUG_BOUNDARY_SUPPORTED

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
 * @tc.name: HandleGestureAccept001
 * @tc.desc: HandleGestureAccept should return when feature switch is off or node is null.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, HandleGestureAccept001, TestSize.Level1)
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
 * @tc.name: HandleGestureAccept002
 * @tc.desc: HandleGestureAccept should keep existing node states and record new node state.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, HandleGestureAccept002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare manager and two nodes.
     */
    GestureDebugBoundaryManager manager;
    auto node = CreateFrameNode(TEST_NODE_ID);
    auto anotherNode = CreateFrameNode(TEST_NODE_ID_2);
    ASSERT_NE(node, nullptr);
    ASSERT_NE(anotherNode, nullptr);

    /**
     * @tc.steps: step2. enable switch and accept tap on the first node.
     * @tc.expected: step2. tap bit is retained on the first node.
     */
    SystemProperties::gestureDebugBoundaryEnabled_ = true;
    manager.HandleGestureAccept(GestureListenerType::TAP, node);

    auto stateIter = manager.nodeStates_.find(node->GetId());
    ASSERT_NE(stateIter, manager.nodeStates_.end());
    EXPECT_TRUE(stateIter->second.activeGestures.test(0));

    /**
     * @tc.steps: step3. accept another gesture on a different node.
     * @tc.expected: step3. old and new node states are both kept.
     */
    manager.HandleGestureAccept(GestureListenerType::PAN, anotherNode);
    auto firstStateIter = manager.nodeStates_.find(node->GetId());
    ASSERT_NE(firstStateIter, manager.nodeStates_.end());
    EXPECT_TRUE(firstStateIter->second.activeGestures.test(0));
    auto anotherStateIter = manager.nodeStates_.find(anotherNode->GetId());
    ASSERT_NE(anotherStateIter, manager.nodeStates_.end());
    EXPECT_TRUE(anotherStateIter->second.activeGestures.test(2));
}

/**
 * @tc.name: ResetAllGesturesOnNewRound001
 * @tc.desc: ResetAllGesturesOnNewRound should clear all tracked states.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, ResetAllGesturesOnNewRound001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare manager with two tracked nodes.
     */
    GestureDebugBoundaryManager manager;
    auto node = CreateFrameNode(TEST_NODE_ID);
    auto anotherNode = CreateFrameNode(TEST_NODE_ID_2);
    ASSERT_NE(node, nullptr);
    ASSERT_NE(anotherNode, nullptr);

    /**
     * @tc.steps: step2. insert states and reset for a new gesture round.
     * @tc.expected: step2. all node states are removed.
     */
    GestureDebugBoundaryState firstState;
    firstState.node = WeakPtr<FrameNode>(node);
    firstState.activeGestures.set(2);
    manager.nodeStates_[node->GetId()] = firstState;

    GestureDebugBoundaryState secondState;
    secondState.node = WeakPtr<FrameNode>(anotherNode);
    secondState.activeGestures.set(5);
    manager.nodeStates_[anotherNode->GetId()] = secondState;

    manager.ResetAllGesturesOnNewRound();
    EXPECT_TRUE(manager.nodeStates_.empty());
}

/**
 * @tc.name: ClearNode001
 * @tc.desc: ClearNode should cover missing-node and valid-node branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, ClearNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call ClearNode for non-existing node id.
     * @tc.expected: step1. manager state remains empty.
     */
    GestureDebugBoundaryManager manager;
    manager.ClearNode(TEST_NODE_ID);
    EXPECT_TRUE(manager.nodeStates_.empty());

    /**
     * @tc.steps: step2. insert valid node state with one active gesture and clear it.
     * @tc.expected: step2. node state is removed.
     */
    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);
    GestureDebugBoundaryState state;
    state.node = WeakPtr<FrameNode>(node);
    state.activeGestures.set(2);
    manager.nodeStates_[node->GetId()] = state;

    manager.ClearNode(node->GetId());
    EXPECT_EQ(manager.nodeStates_.find(node->GetId()), manager.nodeStates_.end());
}

/**
 * @tc.name: ResetAllGesturesOnNewRound002
 * @tc.desc: ResetAllGesturesOnNewRound should clear expired-node state as well.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, ResetAllGesturesOnNewRound002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare state with an expired weak node.
     */
    GestureDebugBoundaryManager manager;
    GestureDebugBoundaryState state;
    state.activeGestures.set(0);
    manager.nodeStates_[TEST_NODE_ID] = state;

    /**
     * @tc.steps: step2. reset all gestures on a new round.
     * @tc.expected: step2. expired node state is removed.
     */
    manager.ResetAllGesturesOnNewRound();
    EXPECT_EQ(manager.nodeStates_.find(TEST_NODE_ID), manager.nodeStates_.end());
}

/**
 * @tc.name: ResetAllGesturesOnNewRound003
 * @tc.desc: ResetAllGesturesOnNewRound should keep manager empty when no state exists.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, ResetAllGesturesOnNewRound003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. reset manager without any tracked state.
     * @tc.expected: step1. manager remains empty.
     */
    GestureDebugBoundaryManager manager;
    manager.ResetAllGesturesOnNewRound();
    EXPECT_TRUE(manager.nodeStates_.empty());
}

/**
 * @tc.name: BuildRenderInfo001
 * @tc.desc: BuildRenderInfo should cover empty, null-node, null-context and threshold branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, BuildRenderInfo001, TestSize.Level1)
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
 * @tc.name: BuildRenderInfoAndResolveGestureColor001
 * @tc.desc: BuildRenderInfo and ResolveGestureColor should cover normal path and fallback branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, BuildRenderInfoAndResolveGestureColor001, TestSize.Level1)
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
 * @tc.name: NotifyNodeRefresh001
 * @tc.desc: NotifyNodeRefresh should cover null-node, null-render-context and normal branches.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, NotifyNodeRefresh001, TestSize.Level1)
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
 * @tc.name: OnDetachFromMainTree001
 * @tc.desc: FrameNode::OnDetachFromMainTree should clear gesture debug node state when switch is enabled.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, OnDetachFromMainTree001, TestSize.Level1)
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
    EXPECT_NE(gestureDebugMgr->nodeStates_.find(node->GetId()), gestureDebugMgr->nodeStates_.end());

    /**
     * @tc.steps: step3. enable switch and call FrameNode::OnDetachFromMainTree.
     * @tc.expected: step3. node state is cleared by gesture debug manager.
     */
    SystemProperties::gestureDebugBoundaryEnabled_ = true;
    node->OnDetachFromMainTree(false, AceType::RawPtr(pipeline));
    EXPECT_EQ(gestureDebugMgr->nodeStates_.find(node->GetId()), gestureDebugMgr->nodeStates_.end());
}

/**
 * @tc.name: EventManagerTouchTestResetGestureDebugBoundary001
 * @tc.desc: EventManager::TouchTest should reset all gesture debug boundaries when down finger count is one.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, EventManagerTouchTestResetGestureDebugBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare EventManager, GestureDebugBoundaryManager and one tracked node state.
     * @tc.expected: step1. one gesture debug boundary state exists before TouchTest.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto eventManager = pipeline->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    auto gestureDebugMgr = eventManager->GetGestureDebugBoundaryManager();
    ASSERT_NE(gestureDebugMgr, nullptr);

    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    GestureDebugBoundaryState state;
    state.node = WeakPtr<FrameNode>(node);
    state.activeGestures.set(2);
    gestureDebugMgr->nodeStates_[node->GetId()] = state;
    ASSERT_FALSE(gestureDebugMgr->nodeStates_.empty());

    /**
     * @tc.steps: step2. enable gesture debug boundary switch and make downFingerIds_ size equal to one.
     * @tc.expected: step2. if-condition in EventManager::TouchTest is satisfied.
     */
    SystemProperties::gestureDebugBoundaryEnabled_ = true;
    eventManager->downFingerIds_.clear();
    eventManager->downFingerIds_[0] = 0;

    TouchEvent touchPoint;
    touchPoint.id = 0;
    touchPoint.type = TouchType::DOWN;
    touchPoint.x = 0.0f;
    touchPoint.y = 0.0f;

    /**
     * @tc.steps: step3. execute EventManager::TouchTest.
     * @tc.expected: step3. ResetAllGesturesOnNewRound is triggered and node states are cleared.
     */
    TouchRestrict touchRestrict;
    Offset offset;
    eventManager->TouchTest(touchPoint, node, touchRestrict, offset, 0.0f, false);
    EXPECT_TRUE(gestureDebugMgr->nodeStates_.empty());
}

/**
 * @tc.name: EventManagerTouchTestResetGestureDebugBoundary002
 * @tc.desc: EventManager::TouchTest should not reset gesture debug boundaries when down finger count is not one.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, EventManagerTouchTestResetGestureDebugBoundary002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare EventManager, GestureDebugBoundaryManager and one tracked node state.
     * @tc.expected: step1. one gesture debug boundary state exists before TouchTest.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto eventManager = pipeline->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    auto gestureDebugMgr = eventManager->GetGestureDebugBoundaryManager();
    ASSERT_NE(gestureDebugMgr, nullptr);

    auto node = CreateFrameNode(TEST_NODE_ID_2);
    ASSERT_NE(node, nullptr);

    GestureDebugBoundaryState state;
    state.node = WeakPtr<FrameNode>(node);
    state.activeGestures.set(2);
    gestureDebugMgr->nodeStates_[node->GetId()] = state;
    ASSERT_FALSE(gestureDebugMgr->nodeStates_.empty());

    /**
     * @tc.steps: step2. enable gesture debug boundary switch and make downFingerIds_ size greater than one.
     * @tc.expected: step2. if-condition in EventManager::TouchTest is not satisfied.
     */
    SystemProperties::gestureDebugBoundaryEnabled_ = true;
    eventManager->downFingerIds_.clear();
    eventManager->downFingerIds_[0] = 0;
    eventManager->downFingerIds_[1] = 1;

    TouchEvent touchPoint;
    touchPoint.id = 0;
    touchPoint.type = TouchType::DOWN;
    touchPoint.x = 0.0f;
    touchPoint.y = 0.0f;

    /**
     * @tc.steps: step3. execute EventManager::TouchTest.
     * @tc.expected: step3. ResetAllGesturesOnNewRound is not triggered and node state is retained.
     */
    TouchRestrict touchRestrict;
    Offset offset;
    eventManager->TouchTest(touchPoint, node, touchRestrict, offset, 0.0f, false);
    EXPECT_NE(gestureDebugMgr->nodeStates_.find(node->GetId()), gestureDebugMgr->nodeStates_.end());
}

/**
 * @tc.name: EventManagerTouchTestResetGestureDebugBoundary003
 * @tc.desc: EventManager::TouchTest should not reset gesture debug boundaries when debug switch is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, EventManagerTouchTestResetGestureDebugBoundary003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare EventManager, GestureDebugBoundaryManager and one tracked node state.
     * @tc.expected: step1. one gesture debug boundary state exists before TouchTest.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto eventManager = pipeline->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    auto gestureDebugMgr = eventManager->GetGestureDebugBoundaryManager();
    ASSERT_NE(gestureDebugMgr, nullptr);

    auto node = CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(node, nullptr);

    GestureDebugBoundaryState state;
    state.node = WeakPtr<FrameNode>(node);
    state.activeGestures.set(2);
    gestureDebugMgr->nodeStates_[node->GetId()] = state;
    ASSERT_FALSE(gestureDebugMgr->nodeStates_.empty());

    /**
     * @tc.steps: step2. disable gesture debug boundary switch and keep downFingerIds_ size equal to one.
     * @tc.expected: step2. if-condition in EventManager::TouchTest is not satisfied.
     */
    SystemProperties::gestureDebugBoundaryEnabled_ = false;
    eventManager->downFingerIds_.clear();
    eventManager->downFingerIds_[0] = 0;

    TouchEvent touchPoint;
    touchPoint.id = 0;
    touchPoint.type = TouchType::DOWN;
    touchPoint.x = 0.0f;
    touchPoint.y = 0.0f;

    /**
     * @tc.steps: step3. execute EventManager::TouchTest.
     * @tc.expected: step3. ResetAllGesturesOnNewRound is not triggered and node state is retained.
     */
    TouchRestrict touchRestrict;
    Offset offset;
    eventManager->TouchTest(touchPoint, node, touchRestrict, offset, 0.0f, false);
    EXPECT_NE(gestureDebugMgr->nodeStates_.find(node->GetId()), gestureDebugMgr->nodeStates_.end());
}

/**
 * @tc.name: EventManagerTouchTestResetGestureDebugBoundary004
 * @tc.desc: EventManager::TouchTest should not reset gesture debug boundaries when debug switch is disabled and down
 * finger count is not one.
 * @tc.type: FUNC
 */
HWTEST_F(GestureDebugBoundaryManagerTestNg, EventManagerTouchTestResetGestureDebugBoundary004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare EventManager, GestureDebugBoundaryManager and one tracked node state.
     * @tc.expected: step1. one gesture debug boundary state exists before TouchTest.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto eventManager = pipeline->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    auto gestureDebugMgr = eventManager->GetGestureDebugBoundaryManager();
    ASSERT_NE(gestureDebugMgr, nullptr);

    auto node = CreateFrameNode(TEST_NODE_ID_2);
    ASSERT_NE(node, nullptr);

    GestureDebugBoundaryState state;
    state.node = WeakPtr<FrameNode>(node);
    state.activeGestures.set(2);
    gestureDebugMgr->nodeStates_[node->GetId()] = state;
    ASSERT_FALSE(gestureDebugMgr->nodeStates_.empty());

    /**
     * @tc.steps: step2. disable gesture debug boundary switch and make downFingerIds_ size greater than one.
     * @tc.expected: step2. if-condition in EventManager::TouchTest is not satisfied.
     */
    SystemProperties::gestureDebugBoundaryEnabled_ = false;
    eventManager->downFingerIds_.clear();
    eventManager->downFingerIds_[0] = 0;
    eventManager->downFingerIds_[1] = 1;

    TouchEvent touchPoint;
    touchPoint.id = 0;
    touchPoint.type = TouchType::DOWN;
    touchPoint.x = 0.0f;
    touchPoint.y = 0.0f;

    /**
     * @tc.steps: step3. execute EventManager::TouchTest.
     * @tc.expected: step3. ResetAllGesturesOnNewRound is not triggered and node state is retained.
     */
    TouchRestrict touchRestrict;
    Offset offset;
    eventManager->TouchTest(touchPoint, node, touchRestrict, offset, 0.0f, false);
    EXPECT_NE(gestureDebugMgr->nodeStates_.find(node->GetId()), gestureDebugMgr->nodeStates_.end());
}

} // namespace OHOS::Ace::NG

#endif // GESTURE_DEBUG_BOUNDARY_SUPPORTED