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
#include "test/unittest/core/manager/drag_drop_manager_test_ng.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
void DragDropManagerTestNgCoverage::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
}

void DragDropManagerTestNgCoverage::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    MOCK_DRAG_WINDOW = nullptr;
}

/**
 * @tc.name: DragDropManagerTestNgCoverage001
 * @tc.desc: Test FindTargetInChildNodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>("parent", frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeNull->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    frameNodeNull->SetActive(true);
    auto eventHub = frameNodeNull->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragDrop = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& value) {};
    eventHub->SetOnDrop(std::move(onDragDrop));
    auto childNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNodeNull = AceType::MakeRefPtr<FrameNode>(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, childNodeNullId, AceType::MakeRefPtr<Pattern>());
    childNodeNull->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    childNodeNull->SetActive(true);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(FRAME_SIZE);
    frameNodeNull->SetGeometryNode(geometryNode);
    childNodeNull->SetGeometryNode(geometryNode);
    auto pipelineTmp = NG::PipelineContext::GetCurrentContext();
    auto parentNodeTmp = pipelineTmp->GetRootElement();
    auto parentFrameNodeTmp = AceType::DynamicCast<FrameNode>(parentNodeTmp);
    parentFrameNodeTmp->SetGeometryNode(geometryNode);
    parentFrameNodeTmp->frameChildren_.insert(WeakPtr<NG::FrameNode>(frameNodeNull));
    parentFrameNodeTmp->frameChildren_.insert(WeakPtr<NG::FrameNode>(childNodeNull));
    parentFrameNodeTmp->frameChildren_.insert(WeakPtr<NG::FrameNode>(nullptr));
    dragDropManager->AddGridDragFrameNode(parentFrameNodeTmp->GetId(), parentFrameNodeTmp);
    dragDropManager->AddGridDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    dragDropManager->AddGridDragFrameNode(childNodeNull->GetId(), childNodeNull);
    std::map<int32_t, WeakPtr<FrameNode>> frameNodes = dragDropManager->gridDragFrameNodes_;
    PointF point(GLOBAL_X, GLOBAL_Y);
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    hitFrameNodes.push_back(parentFrameNodeTmp);
    hitFrameNodes.push_back(frameNodeNull);
    hitFrameNodes.push_back(childNodeNull);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetOverlayManager();
    auto parentNode = pipeline->GetRootElement();
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(parentNode);
    auto children = parentFrameNode->GetFrameChildren();
    auto result = dragDropManager->FindTargetInChildNodes(parentNode, hitFrameNodes, true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage002
 * @tc.desc: Test FindTargetInChildNodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat node and generate a node tree.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    const RefPtr<FrameNode> GET_PARENT = FrameNode::CreateFrameNode("parent", 4, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD1 = FrameNode::CreateFrameNode("child1", 5, AceType::MakeRefPtr<Pattern>());
    const RefPtr<FrameNode> GET_CHILD2 = FrameNode::CreateFrameNode("child2", 6, AceType::MakeRefPtr<Pattern>());
    GET_CHILD1->UpdateInspectorId("child1");
    GET_CHILD2->UpdateInspectorId("child2");
    GET_PARENT->frameChildren_.insert(GET_CHILD1);
    GET_PARENT->frameChildren_.insert(GET_CHILD2);
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    hitFrameNodes.push_back(GET_PARENT);
    hitFrameNodes.push_back(GET_CHILD1);
    hitFrameNodes.push_back(GET_CHILD2);
    dragDropManager->AddGridDragFrameNode(GET_PARENT->GetId(), GET_PARENT);

    /**
     * @tc.steps: step2. initialize parentEventHub and set HitTestMode.
     */
    auto parentEventHub = GET_PARENT->GetOrCreateGestureEventHub();
    parentEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto dragResult = dragDropManager->FindTargetInChildNodes(GET_PARENT, hitFrameNodes, true);

    /**
     * @tc.steps: step3. call GetDispatchFrameNode.
     * @tc.expected: expect GetDispatchFrameNode ruturn nullptr.
     */
    EXPECT_EQ(dragResult, nullptr);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage003
 * @tc.desc: Test FindTargetInChildNodes with null child nodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage003, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto parentNode = AceType::MakeRefPtr<FrameNode>(
        NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<GridPattern>());
    for (int i = 0; i < 5; ++i) {
        parentNode->frameChildren_.insert(WeakPtr<NG::FrameNode>(nullptr));
    }
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    hitFrameNodes.push_back(parentNode);
    auto result = dragDropManager->FindTargetInChildNodes(parentNode, hitFrameNodes, true);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage004
 * @tc.desc: Test FindTargetInChildNodes with hit FrameNode having OnDrop event
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage004, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto parentNode = AceType::MakeRefPtr<FrameNode>(
        NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<GridPattern>());
    auto hitFrameNode = AceType::MakeRefPtr<FrameNode>(
        NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<GridPattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto parentEventHub = hitFrameNode->GetOrCreateGestureEventHub();
    parentEventHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    dragDropManager->AddGridDragFrameNode(hitFrameNode->GetId(), hitFrameNode);

    parentNode->frameChildren_.insert(WeakPtr<NG::FrameNode>(hitFrameNode));
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    hitFrameNodes.push_back(hitFrameNode);

    auto result = dragDropManager->FindTargetInChildNodes(parentNode, hitFrameNodes, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage005
 * @tc.desc: Test FindTargetDropNode with null parentNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage005, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    PointF point(0.0, 0.0);
    auto result = dragDropManager->FindTargetDropNode(nullptr, point);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage006
 * @tc.desc: Test FindTargetInChildNodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage006, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>("parent", frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeNull->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    frameNodeNull->SetActive(true);
    auto eventHub = frameNodeNull->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragDrop = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& value) {};
    eventHub->SetOnDrop(std::move(onDragDrop));
    auto childNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNodeNull =
        AceType::MakeRefPtr<FrameNode>(V2::EMBEDDED_COMPONENT_ETS_TAG, childNodeNullId, AceType::MakeRefPtr<Pattern>());
    childNodeNull->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    childNodeNull->SetActive(true);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(FRAME_SIZE);
    frameNodeNull->SetGeometryNode(geometryNode);
    childNodeNull->SetGeometryNode(geometryNode);
    auto pipelineTmp = NG::PipelineContext::GetCurrentContext();
    auto parentNodeTmp = pipelineTmp->GetRootElement();
    auto parentFrameNodeTmp = AceType::DynamicCast<FrameNode>(parentNodeTmp);
    parentFrameNodeTmp->SetGeometryNode(geometryNode);
    parentFrameNodeTmp->frameChildren_.insert(WeakPtr<NG::FrameNode>(frameNodeNull));
    parentFrameNodeTmp->frameChildren_.insert(WeakPtr<NG::FrameNode>(childNodeNull));
    parentFrameNodeTmp->frameChildren_.insert(WeakPtr<NG::FrameNode>(nullptr));
    dragDropManager->AddGridDragFrameNode(parentFrameNodeTmp->GetId(), parentFrameNodeTmp);
    dragDropManager->AddGridDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    dragDropManager->AddGridDragFrameNode(childNodeNull->GetId(), childNodeNull);
    std::map<int32_t, WeakPtr<FrameNode>> frameNodes = dragDropManager->gridDragFrameNodes_;
    PointF point(GLOBAL_X, GLOBAL_Y);
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    hitFrameNodes.push_back(parentFrameNodeTmp);
    hitFrameNodes.push_back(frameNodeNull);
    hitFrameNodes.push_back(childNodeNull);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetOverlayManager();
    auto parentNode = pipeline->GetRootElement();
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(parentNode);
    auto children = parentFrameNode->GetFrameChildren();
    auto result = dragDropManager->FindTargetInChildNodes(parentNode, hitFrameNodes, true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage007
 * @tc.desc: Test FindTargetDropNode with inactive or invisible parentFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage007, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto parentNode = AceType::MakeRefPtr<FrameNode>(
        NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<GridPattern>());
    PointF point(0.0, 0.0);

    parentNode->SetActive(false);
    auto result = dragDropManager->FindTargetDropNode(parentNode, point);
    EXPECT_EQ(result, nullptr);

    parentNode->SetActive(true);
    parentNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    result = dragDropManager->FindTargetDropNode(parentNode, point);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage009
 * @tc.desc: Test FindTargetDropNode with null child nodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage009, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto parentNode = AceType::MakeRefPtr<FrameNode>(
        NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<GridPattern>());
    for (int i = 0; i < 5; ++i) {
        parentNode->frameChildren_.insert(WeakPtr<NG::FrameNode>(nullptr));
    }
    PointF point(0.0, 0.0);
    auto result = dragDropManager->FindTargetDropNode(parentNode, point);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage010
 * @tc.desc: Test FindTargetDropNode with null child nodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage010, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>("parent", frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeNull->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    frameNodeNull->SetActive(true);
    auto eventHub = frameNodeNull->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragDrop = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& value) {};
    eventHub->SetOnDrop(std::move(onDragDrop));
    auto childNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNodeNull =
        AceType::MakeRefPtr<FrameNode>(V2::EMBEDDED_COMPONENT_ETS_TAG, childNodeNullId, AceType::MakeRefPtr<Pattern>());
    childNodeNull->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    childNodeNull->SetActive(true);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(FRAME_SIZE);
    frameNodeNull->SetGeometryNode(geometryNode);
    childNodeNull->SetGeometryNode(geometryNode);
    frameNodeNull->GetRenderContext()->UpdatePaintRect({ 0.0, 0.0, 200.0, 200.0 });
    childNodeNull->GetRenderContext()->UpdatePaintRect({ 0.0, 0.0, 200.0, 200.0 });
    auto pipelineTmp = NG::PipelineContext::GetCurrentContext();
    auto parentNodeTmp = pipelineTmp->GetRootElement();
    auto parentFrameNodeTmp = AceType::DynamicCast<FrameNode>(parentNodeTmp);
    parentFrameNodeTmp->SetGeometryNode(geometryNode);
    parentFrameNodeTmp->GetRenderContext()->UpdatePaintRect({ 0.0, 0.0, 200.0, 200.0 });
    parentFrameNodeTmp->frameChildren_.insert(WeakPtr<NG::FrameNode>(frameNodeNull));
    frameNodeNull->frameChildren_.insert(WeakPtr<NG::FrameNode>(childNodeNull));
    frameNodeNull->frameChildren_.insert(WeakPtr<NG::FrameNode>(nullptr));
    dragDropManager->AddGridDragFrameNode(parentFrameNodeTmp->GetId(), parentFrameNodeTmp);
    dragDropManager->AddGridDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    dragDropManager->AddGridDragFrameNode(childNodeNull->GetId(), childNodeNull);
    std::map<int32_t, WeakPtr<FrameNode>> frameNodes = dragDropManager->gridDragFrameNodes_;
    PointF point(100.0, 100.0);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetOverlayManager();
    auto parentNode = pipeline->GetRootElement();
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(parentNode);
    auto children = parentFrameNode->GetFrameChildren();
    auto result = dragDropManager->FindTargetDropNode(parentNode, point);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage011
 * @tc.desc: Test UpdateDragAllowDrop
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { NODE_TAG };
    frameNode->SetAllowDrop(allowDrop);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    auto childNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, childNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(childNode, nullptr);
    childNode->SetAllowDrop(allowDrop);

    /**
     * @tc.steps: step3. call UpdateDragAllowDrop with frameNode and copy.
     * @tc.expected: dragDropManager->summaryMap_.empty() return a true value.
     */
    dragDropManager->summaryMap_.clear();
    PointF point(100.0, 100.0);
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, childNode);
    dragDropManager->summaryMap_.insert(make_pair(NODE_TAG, frameNodeNullId));
    dragDropManager->UpdateDragAllowDrop(frameNode, DragBehavior::UNKNOWN);
    EXPECT_FALSE(dragDropManager->summaryMap_.empty());

    /**
     * @tc.steps: step3. call UpdateDragAllowDrop with frameNode and copy.
     * @tc.expected: dragDropManager->summaryMap_.empty() return a true value.
     */
    dragDropManager->summaryMap_.clear();
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    dragDropManager->summaryMap_.insert(make_pair(NODE_TAG, frameNodeNullId));
    dragDropManager->UpdateDragAllowDrop(frameNode, DragBehavior::UNKNOWN);
    EXPECT_FALSE(dragDropManager->summaryMap_.empty());

    /**
     * @tc.steps: step4. call UpdateDragAllowDrop with frameNode and copy.
     * @tc.expected: dragDropManager->summaryMap_.empty() return a false value.
     */
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(NODE_TAG, frameNodeNullId));
    dragDropManager->UpdateDragAllowDrop(frameNode, DragBehavior::MOVE);
    EXPECT_FALSE(dragDropManager->summaryMap_.empty());

    /**
     * @tc.steps: step5. call UpdateDragAllowDrop with frameNode and copy.
     * @tc.expected: allowDrop.find(ROOT_ETS_TAG) is equal to allowDrop.end().
     */
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(ROOT_ETS_TAG, frameNodeNullId));
    dragDropManager->UpdateDragAllowDrop(frameNode, static_cast<DragBehavior>(-100));
    EXPECT_TRUE(allowDrop.find(ROOT_ETS_TAG) == allowDrop.end());
}

/**
 * @tc.name: DragDropManagerTestNgCoverage012
 * @tc.desc: Test FindTargetDropNode with null child nodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage012, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>("parent", frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeNull->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    frameNodeNull->SetActive(true);
    auto eventHub = frameNodeNull->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragDrop = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& value) {};
    eventHub->SetOnDrop(std::move(onDragDrop));
    auto childNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNodeNull = AceType::MakeRefPtr<FrameNode>(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, childNodeNullId, AceType::MakeRefPtr<Pattern>());
    childNodeNull->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    childNodeNull->SetActive(true);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(FRAME_SIZE);
    frameNodeNull->SetGeometryNode(geometryNode);
    childNodeNull->SetGeometryNode(geometryNode);
    frameNodeNull->GetRenderContext()->UpdatePaintRect({ 0.0, 0.0, 200.0, 200.0 });
    childNodeNull->GetRenderContext()->UpdatePaintRect({ 0.0, 0.0, 200.0, 200.0 });
    auto pipelineTmp = NG::PipelineContext::GetCurrentContext();
    auto parentNodeTmp = pipelineTmp->GetRootElement();
    auto parentFrameNodeTmp = AceType::DynamicCast<FrameNode>(parentNodeTmp);
    parentFrameNodeTmp->SetGeometryNode(geometryNode);
    parentFrameNodeTmp->GetRenderContext()->UpdatePaintRect({ 0.0, 0.0, 200.0, 200.0 });
    parentFrameNodeTmp->frameChildren_.insert(WeakPtr<NG::FrameNode>(frameNodeNull));
    frameNodeNull->frameChildren_.insert(WeakPtr<NG::FrameNode>(childNodeNull));
    frameNodeNull->frameChildren_.insert(WeakPtr<NG::FrameNode>(nullptr));
    dragDropManager->AddGridDragFrameNode(parentFrameNodeTmp->GetId(), parentFrameNodeTmp);
    dragDropManager->AddGridDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    dragDropManager->AddGridDragFrameNode(childNodeNull->GetId(), childNodeNull);
    std::map<int32_t, WeakPtr<FrameNode>> frameNodes = dragDropManager->gridDragFrameNodes_;
    PointF point(100.0, 100.0);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetOverlayManager();
    auto parentNode = pipeline->GetRootElement();
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(parentNode);
    auto children = parentFrameNode->GetFrameChildren();
    auto resultNode = dragDropManager->FindDragFrameNodeByPosition(point.GetX(), point.GetY());
    EXPECT_TRUE(resultNode);
    auto result = dragDropManager->FindTargetDropNode(parentNode, point);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage013
 * @tc.desc: Test CheckParentVisible out of parent is a true branch.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    RefPtr<NotifyDragEvent> notifyEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    dragDropManager->UpdateNotifyDragEvent(notifyEvent, Point(1.0f, 1.0f), DragEventType::START);
    EXPECT_DOUBLE_EQ(notifyEvent->GetX(), 1.0);
    EXPECT_DOUBLE_EQ(notifyEvent->GetY(), 1.0);

    std::unordered_map<int32_t, WeakPtr<FrameNode>> dragEnterNodes;
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<GridPattern>());
    frameNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE, true);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(true);
    dragEnterNodes[0] = nullptr;
    dragEnterNodes[1] = frameNode;
    dragDropManager->NotifyDragRegisterFrameNode(dragEnterNodes, DragEventType::START, notifyEvent);
    EXPECT_TRUE(frameNode->GetPattern<Pattern>());
}

/**
 * @tc.name: DragDropManagerTestNgCoverage014
 * @tc.desc: Test PrintDragFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    OHOS::Ace::PointerEvent point;

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. draggedFrameNode_ &  preTargetFrameNode_ are assigned to the frameNode created previously
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    dragDropManager->PrintGridDragFrameNode(GLOBAL_X, GLOBAL_Y, frameNode);
    ASSERT_TRUE(preTargetNode);
    dragDropManager->onDragCancel();
    dragDropManager->onItemDragCancel();
    dragDropManager->PrintDragFrameNode(point, frameNode);
    dragDropManager->PrintGridDragFrameNode(GLOBAL_X, GLOBAL_Y, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(draggedNode);
    ASSERT_FALSE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage015
 * @tc.desc: Test PrintDragFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    dragDropManager->TransDragWindowToDragFwk(111);
    dragDropManager->TransDragWindowToDragFwk(111);
    ASSERT_TRUE(dragDropManager->isDragFwkShow_);
}

/**
 * @tc.name: DragDropManagerTestNgCoverage016
 * @tc.desc: Test isDistanceLimited when distance is less than the limit
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage016, TestSize.Level1)
{
    DragDropManager dragDropManager;
    dragDropManager.preMovePoint_ = Point(0, 0);
    Point point(3, 4); // Distance is 5
    EXPECT_TRUE(dragDropManager.isDistanceLimited(point));
}

/**
 * @tc.name: DragDropManagerTestNgCoverage017
 * @tc.desc: Test isDistanceLimited when distance is biger than the limit
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage017, TestSize.Level1)
{
    DragDropManager dragDropManager;
    dragDropManager.preMovePoint_ = Point(0, 0);
    Point point(100 + 1, 0); // Distance is greater than MOVE_DISTANCE_LIMIT
    EXPECT_FALSE(dragDropManager.isDistanceLimited(point));
}

/**
 * @tc.name: DragDropManagerTestNgCoverage018
 * @tc.desc: Test isTimeLimited when time interval is less than the limit
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage018, TestSize.Level1)
{
    DragDropManager dragDropManager;
    dragDropManager.preTimeStamp_ = 1000;
    PointerEvent pointerEvent;
    Point point(0, 0);
    EXPECT_FALSE(dragDropManager.isTimeLimited(pointerEvent, point));
}

/**
 * @tc.name: DragDropManagerTestNgCoverage019
 * @tc.desc: Test isTimeLimited when time interval is equal to the limit
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage019, TestSize.Level1)
{
    DragDropManager dragDropManager;
    dragDropManager.preTimeStamp_ = 1000;
    PointerEvent pointerEvent;
    pointerEvent.time += std::chrono::milliseconds(1000); // 1000ms after preTimeStamp_
    Point point(0, 0);
    EXPECT_FALSE(dragDropManager.isTimeLimited(pointerEvent, point));
}

/**
 * @tc.name: DragDropManagerTestNgCoverage020
 * @tc.desc: Test isTimeLimited when time interval is greater than the limit
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage020, TestSize.Level1)
{
    DragDropManager dragDropManager;
    dragDropManager.preTimeStamp_ = 1000;
    PointerEvent pointerEvent;
    pointerEvent.time += std::chrono::milliseconds(2500); // 1500ms after preTimeStamp_
    Point point(0, 0);
    EXPECT_FALSE(dragDropManager.isTimeLimited(pointerEvent, point));
}

/**
 * @tc.name: DragDropManagerTestNgCoverage021
 * @tc.desc: Test isTimeLimited when time is the same as preTimeStamp
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage021, TestSize.Level1)
{
    DragDropManager dragDropManager;
    dragDropManager.preTimeStamp_ = 1000;
    PointerEvent pointerEvent;
    pointerEvent.time += std::chrono::milliseconds(1000); // Same as preTimeStamp_
    Point point(0, 0);
    EXPECT_FALSE(dragDropManager.isTimeLimited(pointerEvent, point));
}

/**
 * @tc.name: DragDropManagerTestNgCoverage022
 * @tc.desc: Test isTimeLimited when current time is less than preTimeStamp
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage022, TestSize.Level1)
{
    DragDropManager dragDropManager;
    dragDropManager.preTimeStamp_ = 2000;
    PointerEvent pointerEvent;
    pointerEvent.time += std::chrono::milliseconds(1500); // Less than preTimeStamp_
    Point point(0, 0);
    EXPECT_FALSE(dragDropManager.isTimeLimited(pointerEvent, point));
}

/**
 * @tc.name: DragDropManagerTestNgCoverage023
 * @tc.desc: Test ReachMoveLimit when current time is less than preTimeStamp
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage023, TestSize.Level1)
{
    DragDropManager dragDropManager;
    dragDropManager.preTimeStamp_ = 2000;
    PointerEvent pointerEvent;
    pointerEvent.time += std::chrono::milliseconds(2005);
    pointerEvent.sourceTool = SourceTool::MOUSE;
    dragDropManager.preMovePoint_ = Point(0, 0);
    Point point(3, 4); // Distance is 5
    EXPECT_TRUE(dragDropManager.ReachMoveLimit(pointerEvent, point));
}

/**
 * @tc.name: DragDropManagerTestNgCoverage024
 * @tc.desc: Test ReachMoveLimit when current time is less than preTimeStamp
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage024, TestSize.Level1)
{
    DragDropManager dragDropManager;
    dragDropManager.preTimeStamp_ = 2000;
    PointerEvent pointerEvent;
    pointerEvent.time += std::chrono::milliseconds(1000);
    pointerEvent.sourceTool = SourceTool::MOUSE;
    dragDropManager.preMovePoint_ = Point(0, 0);
    Point point(15, 20); // Distance is 25
    EXPECT_FALSE(dragDropManager.ReachMoveLimit(pointerEvent, point));
}

/**
 * @tc.name: DragDropManagerTestNgCoverage025
 * @tc.desc: Test ReachMoveLimit when current time is less than preTimeStamp
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgCoverage, DragDropManagerTestNgCoverage025, TestSize.Level1)
{
    DragDropManager dragDropManager;
    dragDropManager.preTimeStamp_ = 2000;
    PointerEvent pointerEvent;
    pointerEvent.time += std::chrono::milliseconds(2002);
    pointerEvent.sourceTool = SourceTool::MOUSE;
    dragDropManager.preMovePoint_ = Point(0, 0);
    Point point(15, 20); // Distance is 25
    EXPECT_FALSE(dragDropManager.ReachMoveLimit(pointerEvent, point));
}
} // namespace OHOS::Ace::NG