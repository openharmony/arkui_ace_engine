/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "test/unittest/core/manager/drag_drop_manager_test_ng.h"

#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
void DragDropManagerTestNgPlus::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp(NG::PipelineContext::GetCurrentContext());
}
 
void DragDropManagerTestNgPlus::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}
 
/**
 * @tc.name: DragDropManagerTestNgPlus001
 * @tc.desc: Test FindTargetInChildNodes and CheckFrameNodeCanDrop
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgPlus, DragDropManagerTestNgPlus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager, create DC.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    auto frameNodeDCId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeDC = AceType::MakeRefPtr<FrameNode>(
        V2::DYNAMIC_COMPONENT_ETS_TAG, frameNodeDCId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNodeDC, nullptr);
    frameNodeDC->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    frameNodeDC->SetActive(true);
 
    /**
     * @tc.steps: step2. test function FindTargetInChildNodes.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(FRAME_SIZE);
    frameNodeDC->SetGeometryNode(geometryNode);
    dragDropManager->AddGridDragFrameNode(frameNodeDC->GetId(), frameNodeDC);
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    hitFrameNodes.push_back(frameNodeDC);
    auto result = dragDropManager->FindTargetInChildNodes(frameNodeDC, hitFrameNodes, true);
    EXPECT_NE(result, nullptr);
 
    /**
     * @tc.steps: step3. create isolated component and test function FindTargetInChildNodes.
     */
    auto frameNodeICId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeIC = AceType::MakeRefPtr<FrameNode>(
        V2::ISOLATED_COMPONENT_ETS_TAG, frameNodeICId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNodeIC, nullptr);
    frameNodeIC->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    frameNodeIC->SetActive(true);
    auto eventHubIC = frameNodeIC->GetEventHub<EventHub>();
    ASSERT_TRUE(eventHubIC);
 
    frameNodeIC->SetGeometryNode(geometryNode);
    dragDropManager->AddGridDragFrameNode(frameNodeIC->GetId(), frameNodeIC);
    hitFrameNodes.pop_back();
    hitFrameNodes.push_back(frameNodeIC);
    result = dragDropManager->FindTargetInChildNodes(frameNodeIC, hitFrameNodes, true);
    EXPECT_NE(result, nullptr);
 
    /**
     * @tc.steps: step4. test CheckFrameNodeCanDrop.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        NODE_TAG, frameNodeDCId, AceType::MakeRefPtr<Pattern>());
    auto dropResult = dragDropManager->CheckFrameNodeCanDrop(frameNodeDC);
    EXPECT_TRUE(dropResult);
    
    dropResult = dragDropManager->CheckFrameNodeCanDrop(frameNodeIC);
    EXPECT_TRUE(dropResult);
 
    dropResult = dragDropManager->CheckFrameNodeCanDrop(frameNode);
    EXPECT_FALSE(dropResult);
}
 
/**
 * @tc.name: DragDropManagerTestNgPlus002
 * @tc.desc: Test IsUIExtensionOrDynamicComponent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgPlus, DragDropManagerTestNgPlus002, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    EXPECT_NE(dragDropManager, nullptr);
    auto frameNodeDCId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeDC = AceType::MakeRefPtr<FrameNode>(
        V2::DYNAMIC_COMPONENT_ETS_TAG, frameNodeDCId, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNodeDC, nullptr);
    auto frameNodeICId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeIC = AceType::MakeRefPtr<FrameNode>(
        V2::ISOLATED_COMPONENT_ETS_TAG, frameNodeICId, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNodeIC, nullptr);
    DragPointerEvent point;
    point.x = 1;
    point.y = 1;
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
 
    dragDropManager->HandleOnDragEnd(point, EXTRA_INFO, frameNodeDC);
    EXPECT_NE(DragDropBehaviorReporter::GetInstance().stopResult_, DragStopResult::GET_UDKEY_FAIL);
 
    dragDropManager->HandleOnDragEnd(point, EXTRA_INFO, frameNodeIC);
    EXPECT_NE(DragDropBehaviorReporter::GetInstance().stopResult_, DragStopResult::GET_UDKEY_FAIL);
}
 
/**
 * @tc.name: DragDropManagerTestNgPlus003
 * @tc.desc: Test OnDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgPlus, DragDropManagerTestNgPlus003, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    auto uec = AceType::MakeRefPtr<FrameNode>(V2::DYNAMIC_COMPONENT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(uec, nullptr);
    DragPointerEvent pointerEvent(1, 1);
    Point point = pointerEvent.GetPoint();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->SetIsSceneBoardWindow(false);
    dragDropManager->SetIsDragCancel(false);
    dragDropManager->preTargetFrameNode_ = uec;
    auto dragFrameNode = dragDropManager->FindDragFrameNodeByPosition(static_cast<float>(point.GetX()),
        static_cast<float>(point.GetY()),
        dragDropManager->FilterSubwindowDragRootNode(node));
    dragDropManager->OnDragEnd(pointerEvent, EXTRA_INFO, frameNode);
    dragDropManager->preTargetFrameNode_ = node;
    dragDropManager->OnDragEnd(pointerEvent, EXTRA_INFO, frameNode);
    dragDropManager->preTargetFrameNode_ = nullptr;
    dragDropManager->OnDragEnd(pointerEvent, EXTRA_INFO, frameNode);
    EXPECT_EQ(dragFrameNode, dragDropManager->preTargetFrameNode_);
}
 
/**
 * @tc.name: DragDropManagerTestNgPlus004
 * @tc.desc: Test IsAnyDraggableHit Funcition When iter == touchTestResults.end() Is False AND iter->second.empty() Is
 * Fasle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgPlus, DragDropManagerTestNgPlus004, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto eventManager = pipelineContext->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    TouchTestResult hitTestResult;
    auto scrollNode = AceType::MakeRefPtr<OHOS::Ace::NG::Scrollable>();
    ASSERT_NE(scrollNode, nullptr);
    hitTestResult.emplace_back(scrollNode);
    TouchTestResult hitTestResultDC;
    auto scrollDCNode = AceType::MakeRefPtr<OHOS::Ace::NG::Scrollable>();
    hitTestResultDC.emplace_back(scrollDCNode);
    eventManager->touchTestResults_[0] = hitTestResult;
    eventManager->touchTestResults_[1] = hitTestResultDC;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    scrollNode->AttachFrameNode(WeakPtr<NG::FrameNode>(frameNode));
    bool result = dragDropManager->IsAnyDraggableHit(pipelineContext, 0);
    EXPECT_FALSE(result);
    auto dynamicComponent =
        AceType::MakeRefPtr<FrameNode>(V2::DYNAMIC_COMPONENT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(dynamicComponent, nullptr);
    scrollDCNode->AttachFrameNode(WeakPtr<NG::FrameNode>(dynamicComponent));
    result = dragDropManager->IsAnyDraggableHit(pipelineContext, 1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DragDropManagerTestNgPlus005
 * @tc.desc: Test PostStopDrag Funcition When requestId_ == requestId and requestId_ != requestId.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgPlus, DragDropManagerTestNgPlus005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode and dragEvent.
     */
    auto mockTaskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = mockTaskExecutor;
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(dragEvent, nullptr);
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    DragPointerEvent pointerEvent;

    /**
     * @tc.steps: step1. test PostStopDrag.
     */
    dragEvent->SetRequestIdentify(1);
    DragDropGlobalController::GetInstance().requestId_ = 0;
    DragDropGlobalController::GetInstance().SetIsOnOnDropPhase(true);
    dragDropManager->PostStopDrag(frameNode, pointerEvent, dragEvent, "");
    EXPECT_TRUE(DragDropGlobalController::GetInstance().IsOnOnDropPhase());

    DragDropGlobalController::GetInstance().requestId_ = 1;
    dragDropManager->PostStopDrag(frameNode, pointerEvent, dragEvent, "");
    EXPECT_FALSE(DragDropGlobalController::GetInstance().IsOnOnDropPhase());
}
}