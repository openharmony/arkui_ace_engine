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
 * @tc.desc: Test FindTargetInChildNodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgPlus, DragDropManagerTestNgPlus001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(
        V2::DYNAMIC_COMPONENT_ETS_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeNull->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    frameNodeNull->SetActive(true);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(FRAME_SIZE);
    frameNodeNull->SetGeometryNode(geometryNode);
    dragDropManager->AddGridDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    hitFrameNodes.push_back(frameNodeNull);
    auto result = dragDropManager->FindTargetInChildNodes(frameNodeNull, hitFrameNodes, true);
    EXPECT_NE(result, nullptr);
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
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(
        V2::DYNAMIC_COMPONENT_ETS_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNodeNull, nullptr);
    auto result = dragDropManager->IsUIExtensionOrDynamicComponent(frameNodeNull);
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