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
void DragDropManagerTestNgNew::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropManagerTestNgNew::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DragDropManagerTest041
 * @tc.desc: Test FindHitFrameNodes in frameNode branchs(IsActive is false)
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct a frameNode and update attributes.
     * @tc.expected: geometryNode is null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    frameNode->SetActive(false);
    frameNode->geometryNode_ = nullptr;

    /**
     * @tc.steps: step3. update nodesForDragNotify_.
     * @tc.expected: nodesForDragNotify_ is not empty.
     */
    dragDropManager->RegisterDragStatusListener(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
    EXPECT_FALSE(dragDropManager->nodesForDragNotify_.empty());

    /**
     * @tc.steps: step4. call FindHitFrameNodes out of geometryNode are false branches.
     * @tc.expected: frameNodeList is empty.
     */
    auto frameNodeList = dragDropManager->FindHitFrameNodes(Point(1.0f, 1.0f));
    EXPECT_TRUE(frameNodeList.empty());
}

/**
 * @tc.name: DragDropManagerFindDragFrameNodeByPositionTest001
 * @tc.desc: Test FindDragFrameNodeByPosition
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFindDragFrameNodeByPositionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull =
        AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    EXPECT_EQ(static_cast<int32_t>(dragDropManager->dragFrameNodes_.size()), 2);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y);
    EXPECT_FALSE(targetFrameNode);
}

/**
 * @tc.name: DragDropManagerPrintDragFrameNodeTest001
 * @tc.desc: Test PrintDragFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerPrintDragFrameNodeTest001, TestSize.Level1)
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
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    dragDropManager->PrintDragFrameNode(point, frameNode);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
    auto draggedNodeTag = draggedNode->GetTag();
    auto preTargetNodeTag = preTargetNode->GetTag();
    EXPECT_EQ(draggedNodeTag, NODE_TAG);
    EXPECT_EQ(preTargetNodeTag, NODE_TAG);
}

/**
 * @tc.name: DragDropManagerFindTargetInChildNodesTest001
 * @tc.desc: Test PrintDragFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFindTargetInChildNodesTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. draggedFrameNode_ &  preTargetFrameNode_ are assigned to the frameNode created previously
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    hitFrameNodes.push_back(frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, true);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerFindTargetInChildNodesTest002
 * @tc.desc: Test FindTargetInChildNodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFindTargetInChildNodesTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. draggedFrameNode_ &  preTargetFrameNode_ are assigned to the frameNode created previously
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    customNode->SetActive(false);
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    hitFrameNodes.push_back(frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, true);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerFindTargetInChildNodesTest003
 * @tc.desc: Test FindTargetInChildNodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFindTargetInChildNodesTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. draggedFrameNode_ &  preTargetFrameNode_ are assigned to the frameNode created previously
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    customNode->SetActive(true);
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    hitFrameNodes.push_back(frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, true);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerFindTargetInChildNodesTest005
 * @tc.desc: Test FindTargetInChildNodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFindTargetInChildNodesTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode1 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode2 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode3 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    std::list<RefPtr<UINode>> child = { customNode1, customNode2, customNode2, nullptr };

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. draggedFrameNode_ &  preTargetFrameNode_ are assigned to the frameNode created previously
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    customNode->SetActive(true);
    customNode->children_ = child;
    std::vector<RefPtr<FrameNode>> hitFrameNodes = { frameNode, frameNode2 };
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, true);
    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, false);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerFindTargetInChildNodesTest006
 * @tc.desc: Test FindTargetInChildNodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFindTargetInChildNodesTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode1 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode2 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode3 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    std::list<RefPtr<UINode>> child = { customNode1, customNode2, customNode2, nullptr };

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. draggedFrameNode_ &  preTargetFrameNode_ are assigned to the frameNode created previously
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    customNode->SetActive(true);
    customNode->children_ = child;

    auto frameNode4 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = frameNode4->GetEventHub<EventHub>();
    std::string onDropInfo;
    auto onDrop = [&onDropInfo](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* info */) {
        onDropInfo = EXTRA_INFO;
    };
    eventHub->SetOnDrop(std::move(onDrop));

    auto frameNode5 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    auto gridEvent = frameNode5->GetEventHub<GridEventHub>();
    std::string onItemDropInfo;
    ItemDropFunc onItemDrop = [&onItemDropInfo](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                                  int32_t /* insertIndex */, bool /* isSuccess */) { onItemDropInfo = EXTRA_INFO; };
    gridEvent->SetOnItemDrop(std::move(onItemDrop));

    std::vector<RefPtr<FrameNode>> hitFrameNodes = { frameNode, frameNode2, frameNode4, frameNode5 };
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;

    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, true);
    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, false);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerFindTargetInChildNodesTest008
 * @tc.desc: Test FindTargetInChildNodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFindTargetInChildNodesTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode1 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode2 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode3 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    std::list<RefPtr<UINode>> child = { customNode1, customNode2, customNode2, nullptr };

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. draggedFrameNode_ &  preTargetFrameNode_ are assigned to the frameNode created previously
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    customNode->SetActive(true);
    customNode->children_ = child;

    auto parentFrameNode = AceType::DynamicCast<FrameNode>(customNode);

    std::vector<RefPtr<FrameNode>> hitFrameNodes = { parentFrameNode };
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;

    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, true);
    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, false);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);

    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, true);
    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, false);
    ASSERT_TRUE(draggedNode);

    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, true);
    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, false);
    ASSERT_TRUE(draggedNode);

    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, true);
    dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, false);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerOnDragMoveTest001
 * @tc.desc: Test OnDragMove
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerOnDragMoveTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    PointerEvent point;

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. draggedFrameNode_ &  preTargetFrameNode_ are assigned to the frameNode created previously
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    dragDropManager->OnDragMove(point, EXTRA_INFO);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerFireOnDragEventTest001
 * @tc.desc: Test FireOnDragEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFireOnDragEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull =
        AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    EXPECT_EQ(static_cast<int32_t>(dragDropManager->dragFrameNodes_.size()), 2);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y);
    EXPECT_FALSE(targetFrameNode);

    /**
     * @tc.steps: step3. call FireOnDragEvent with type=DragEventType::DROP
     * @tc.expected: step3. FireOnDrop will be called
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = frameNode->GetEventHub<EventHub>();
    std::string onDropInfo;
    auto onDrop = [&onDropInfo](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* info */) {
        onDropInfo = EXTRA_INFO;
    };
    eventHub->SetOnDrop(std::move(onDrop));
    PointerEvent point;
    TouchEvent event;
    event.x = 1.0f;
    event.y = 2.0f;
    dragDropManager->velocityTracker_.UpdateTouchPoint(event, false);
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::ENTER, EXTRA_INFO);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::MOVE, EXTRA_INFO);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::LEAVE, EXTRA_INFO);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::START, EXTRA_INFO);
    EXPECT_EQ(onDropInfo, "");
}

/**
 * @tc.name: DragDropManagerFireOnItemDragEventTest003
 * @tc.desc: Test FireOnItemDragEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFireOnItemDragEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull =
        AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    EXPECT_EQ(static_cast<int32_t>(dragDropManager->dragFrameNodes_.size()), 2);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y);
    EXPECT_FALSE(targetFrameNode);

    /**
     * @tc.steps: step3. call FireOnDragEvent with type=DragEventType::DROP
     * @tc.expected: step3. FireOnDrop will be called
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = frameNode->GetEventHub<EventHub>();
    std::string onDropInfo;
    auto onDrop = [&onDropInfo](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* info */) {
        onDropInfo = EXTRA_INFO;
    };
    eventHub->SetOnDrop(std::move(onDrop));
    PointerEvent point;
    TouchEvent event;
    event.x = 1.0f;
    event.y = 2.0f;
    dragDropManager->velocityTracker_.UpdateTouchPoint(event, false);
    OHOS::Ace::ItemDragInfo itemDragInfo;
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::ENTER, EXTRA_INFO);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::ENTER, 0, 0);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::MOVE, 0, 0);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::START, 0, 0);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::ENTER, 0, 0);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::START, 0, 0);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::TEXT, itemDragInfo, DragEventType::START, 0, 0);
    EXPECT_EQ(onDropInfo, "");
}

/**
 * @tc.name: DragDropManagerOnItemDragEndTest001
 * @tc.desc: Test OnItemDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerOnItemDragEndTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. draggedFrameNode_ &  preTargetFrameNode_ are assigned to the frameNode created previously
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    dragDropManager->draggedGridFrameNode_ = frameNode;
    dragDropManager->OnItemDragEnd(0.0, 0.0, 0, DragType::COMMON);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
    dragDropManager->OnItemDragEnd(0.0, 0.0, 0, DragType::GRID);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerFireOnItemDragEventTest001
 * @tc.desc: Test FireOnItemDragEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFireOnItemDragEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull =
        AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    EXPECT_EQ(static_cast<int32_t>(dragDropManager->dragFrameNodes_.size()), 2);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y);
    EXPECT_FALSE(targetFrameNode);

    /**
     * @tc.steps: step3. call FireOnDragEvent with type=DragEventType::DROP
     * @tc.expected: step3. FireOnDrop will be called
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = frameNode->GetEventHub<EventHub>();
    std::string onDropInfo;
    auto onDrop = [&onDropInfo](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* info */) {
        onDropInfo = EXTRA_INFO;
    };
    eventHub->SetOnDrop(std::move(onDrop));
    TouchEvent event;
    event.x = 1.0f;
    event.y = 2.0f;
    dragDropManager->velocityTracker_.UpdateTouchPoint(event, false);
    OHOS::Ace::ItemDragInfo itemDragInfo;
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::ENTER, 0, 0);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::MOVE, 0, 0);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::START, 0, 0);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::ENTER, 0, 0);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::START, 0, 0);
    EXPECT_EQ(onDropInfo, "");
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::TEXT, itemDragInfo, DragEventType::START, 0, 0);
    EXPECT_EQ(onDropInfo, "");
}

/**
 * @tc.name: DragDropManagerFireOnItemDragEventTest002
 * @tc.desc: Test FireOnItemDragEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFireOnItemDragEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. construct a frameNode whose tag is List set its ItemDragEvent and GeometryNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(LIST_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    auto eventHub = frameNode->GetEventHub<ListEventHub>();

    // Set OnItemDragLeave callback
    std::string itemInfoLeave;
    auto onItemDragLeave = [&itemInfoLeave](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */) {
        itemInfoLeave = ITEM_INFO_LEAVE;
    };
    eventHub->SetOnItemDragLeave(std::move(onItemDragLeave));

    // Set OnItemDragMove callback
    std::string itemInfoMove;
    auto onItemDragMove = [&itemInfoMove](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                              int32_t /* insertIndex */) { itemInfoMove = ITEM_INFO_MOVE; };
    eventHub->SetOnItemDragMove(std::move(onItemDragMove));

    // Set OnItemDragEnter callback
    std::string itemInfoEnter;
    auto onItemDragEnter = [&itemInfoEnter](const ItemDragInfo& /* dragInfo */) { itemInfoEnter = ITEM_INFO_ENTER; };
    eventHub->SetOnItemDragEnter(std::move(onItemDragEnter));

    // Set geometry node to make sure (GLOBAL_X, GLOBAL_Y) in geoNode.frameRect_
    auto geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetMarginFrameOffset(FRAME_OFFSET);
    geoNode->SetFrameSize(FRAME_SIZE);
    frameNode->SetGeometryNode(geoNode);

    /**
     * @tc.steps: step3. call OnItemDragMove
     *                   case: listDragFrameNodes_ is empty & preGridTargetFrameNode_ is not null
     * @tc.expected: step3. frameNode's onItemDragLeave_ will be called
     *                      itemInfoLeave will be assigned to ITEM_INFO_LEAVE
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    auto preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    dragDropManager->AddGridDragFrameNode(frameNode->GetId(), frameNode);

    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    // to force call the FireOnItemDragEvent with DragType::LIST and DragEventType::MOVE
    OHOS::Ace::ItemDragInfo itemDragInfo;
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::MOVE, DRAGGED_INDEX);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::ENTER, DRAGGED_INDEX);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::START, DRAGGED_INDEX);
    EXPECT_EQ(itemInfoMove, ITEM_INFO_MOVE);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::ENTER, DRAGGED_INDEX);
    EXPECT_EQ(itemInfoMove, ITEM_INFO_MOVE);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::MOVE, DRAGGED_INDEX);
    EXPECT_EQ(itemInfoMove, ITEM_INFO_MOVE);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::START, DRAGGED_INDEX);
    EXPECT_EQ(itemInfoMove, ITEM_INFO_MOVE);
}

/**
 * @tc.name: DragDropManagerFireOnItemDropEventTest001
 * @tc.desc: Test FireOnItemDropEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFireOnItemDropEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. FireOnItemDropEvent
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    dragDropManager->draggedGridFrameNode_ = frameNode;
    dragDropManager->OnItemDragEnd(0.0, 0.0, 0, DragType::COMMON);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
    OHOS::Ace::ItemDragInfo itemDragInfo;
    dragDropManager->FireOnItemDropEvent(frameNode, DragType::TEXT, itemDragInfo, 0, 0, true);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerGetItemIndexTest001
 * @tc.desc: Test GetItemIndex
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerGetItemIndexTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. FireOnItemDropEvent
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;

    dragDropManager->OnItemDragEnd(0.0, 0.0, 0, DragType::COMMON);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
    OHOS::Ace::ItemDragInfo itemDragInfo;
    dragDropManager->GetItemIndex(frameNode, DragType::TEXT, 0.0, 0.0);
    ASSERT_TRUE(draggedNode);
    dragDropManager->GetItemIndex(frameNode, DragType::COMMON, 0.0, 0.0);
    ASSERT_TRUE(draggedNode);
    dragDropManager->GetItemIndex(frameNode, DragType::GRID, 0.0, 0.0);
    ASSERT_TRUE(draggedNode);
    dragDropManager->draggedGridFrameNode_ = frameNode;
    dragDropManager->GetItemIndex(frameNode, DragType::GRID, 0.0, 0.0);
    ASSERT_TRUE(draggedNode);
}
/**
 * @tc.name: DragDropManagerGetItemIndexTest002
 * @tc.desc: Test GetItemIndex
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerGetItemIndexTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull =
        AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y);
    /**
     * @tc.steps: step3. call FireOnDragEvent with type=DragEventType::DROP
     * @tc.expected: step3. FireOnDrop will be called
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = frameNode->GetEventHub<EventHub>();
    std::string onDropInfo;
    auto onDrop = [&onDropInfo](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* info */) {
        onDropInfo = EXTRA_INFO;
    };
    eventHub->SetOnDrop(std::move(onDrop));
    PointerEvent point;
    TouchEvent event;
    event.x = 1.0f;
    event.y = 2.0f;
    dragDropManager->velocityTracker_.UpdateTouchPoint(event, false);
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::DROP, EXTRA_INFO);

    /**
     * @tc.steps: step4. call FireOnItemDropEvent with type=DragEventType::DROP
     * @tc.expected: step4. FireOnItemDrop will be called
     */
    ItemDragInfo itemDragInfo;
    auto gridNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    auto gridEvent = gridNode->GetEventHub<GridEventHub>();
    std::string onItemDropInfo;
    ItemDropFunc onItemDrop = [&onItemDropInfo](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                                  int32_t /* insertIndex */, bool /* isSuccess */) { onItemDropInfo = EXTRA_INFO; };
    gridEvent->SetOnItemDrop(std::move(onItemDrop));
    dragDropManager->GetItemIndex(gridNode, DragType::GRID, 0.0, 0.0);
    auto listNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    auto listEvent = listNode->GetEventHub<ListEventHub>();
    std::string onItemDropInfoList;
    ItemDropFunc onItemDropList = [&onItemDropInfoList](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                                      int32_t /* insertIndex */,
                                      bool /* isSuccess */) { onItemDropInfoList = EXTRA_INFO; };
    listEvent->SetOnItemDrop(std::move(onItemDropList));
    dragDropManager->GetItemIndex(listNode, DragType::GRID, 0.0, 0.0);
    dragDropManager->GetItemIndex(listNode, DragType::COMMON, 0.0, 0.0);
    dragDropManager->GetItemIndex(listNode, DragType::TEXT, 0.0, 0.0);
    dragDropManager->GetItemIndex(listNode, DragType::LIST, 0.0, 0.0);
    EXPECT_EQ(onItemDropInfoList, "");
}

/**
 * @tc.name: DragDropManagerGetItemIndexTest003
 * @tc.desc: Test GetItemIndex
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerGetItemIndexTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull =
        AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId, AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y);

    /**
     * @tc.steps: step3. call FireOnDragEvent with type=DragEventType::DROP
     * @tc.expected: step3. FireOnDrop will be called
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = frameNode->GetEventHub<EventHub>();
    std::string onDropInfo;
    auto onDrop = [&onDropInfo](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* info */) {
        onDropInfo = EXTRA_INFO;
    };
    eventHub->SetOnDrop(std::move(onDrop));
    PointerEvent point;
    TouchEvent event;
    event.x = 1.0f;
    event.y = 2.0f;
    dragDropManager->velocityTracker_.UpdateTouchPoint(event, false);
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::DROP, EXTRA_INFO);

    /**
     * @tc.steps: step4. call FireOnItemDropEvent with type=DragEventType::DROP
     * @tc.expected: step4. FireOnItemDrop will be called
     */
    ItemDragInfo itemDragInfo;
    auto gridNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    auto gridEvent = gridNode->GetEventHub<GridEventHub>();
    std::string onItemDropInfo;
    ItemDropFunc onItemDrop = [&onItemDropInfo](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                                  int32_t /* insertIndex */, bool /* isSuccess */) { onItemDropInfo = EXTRA_INFO; };
    gridEvent->SetOnItemDrop(std::move(onItemDrop));
    dragDropManager->draggedGridFrameNode_ = gridNode;
    dragDropManager->GetItemIndex(gridNode, DragType::GRID, 0.0, 0.0);
    auto listNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    auto listEvent = listNode->GetEventHub<ListEventHub>();
    std::string onItemDropInfoList;
    ItemDropFunc onItemDropList = [&onItemDropInfoList](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                                      int32_t /* insertIndex */,
                                      bool /* isSuccess */) { onItemDropInfoList = EXTRA_INFO; };
    listEvent->SetOnItemDrop(std::move(onItemDropList));
    dragDropManager->draggedGridFrameNode_ = gridNode;
    dragDropManager->GetItemIndex(listNode, DragType::GRID, 0.0, 0.0);
    dragDropManager->GetItemIndex(listNode, DragType::GRID, 1.0f, 2.0f);
    EXPECT_EQ(onItemDropInfoList, "");
}

/**
 * @tc.name: DragDropManagerFireOnEditableTextComponent
 * @tc.desc: Test FireOnEditableTextComponent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerFireOnEditableTextComponent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager and create a point.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. Create a normal frameNode which is not a editable text component,
     *  and test FireOnEditableTextComponent.
     * @tc.expected: step2.
     */
    {
        auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::ENTER);
    }

    /**
     * @tc.steps: step3. Create a editable text component, and test FireOnEditableTextComponent.
     * @tc.expected: step3.
     */
    {
        auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXTINPUT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
#ifdef ENABLE_DRAG_FRAMEWORK
        EXPECT_CALL(*(AceType::DynamicCast<MockInteractionInterface>(MockInteractionInterface::GetInstance())),
            EnterTextEditorArea(_))
            .Times(1)
            .WillOnce(::testing::Return(0));
#else
        EXPECT_CALL(*(AceType::DynamicCast<MockInteractionInterface>(MockInteractionInterface::GetInstance())),
            EnterTextEditorArea(_))
            .Times(1);
#endif // ENABLE_DRAG_FRAMEWORK
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::ENTER);
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::ENTER);
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::MOVE);
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::LEAVE);
    }
}

/**
 * @tc.name: DragDropManagerClearVelocityInfoTest001
 * @tc.desc: Test ClearVelocityInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerClearVelocityInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. FireOnItemDropEvent
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;

    dragDropManager->OnItemDragEnd(0.0, 0.0, 0, DragType::COMMON);
    EXPECT_TRUE(draggedNode);
    EXPECT_TRUE(preTargetNode);
    OHOS::Ace::ItemDragInfo itemDragInfo;
    dragDropManager->GetItemIndex(frameNode, DragType::TEXT, 0.0, 0.0);
    EXPECT_TRUE(draggedNode);
    dragDropManager->GetItemIndex(frameNode, DragType::COMMON, 0.0, 0.0);
    EXPECT_TRUE(draggedNode);
    dragDropManager->GetItemIndex(frameNode, DragType::GRID, 0.0, 0.0);
    EXPECT_TRUE(draggedNode);
    dragDropManager->draggedGridFrameNode_ = frameNode;
    dragDropManager->GetItemIndex(frameNode, DragType::GRID, 0.0, 0.0);
    dragDropManager->ClearVelocityInfo();
    EXPECT_TRUE(draggedNode);
}

/**
 * @tc.name: DragDropManagerClearExtraInfoTest001
 * @tc.desc: Test ClearExtraInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerClearExtraInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. FireOnItemDropEvent
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;

    dragDropManager->ClearExtraInfo();
    EXPECT_TRUE(draggedNode);
}

/**
 * @tc.name: DragDropManagerSetExtraInfoTest001
 * @tc.desc: Test SetExtraInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerSetExtraInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: step2. FireOnItemDropEvent
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);

    dragDropManager->SetExtraInfo("ExtraInfo");
    EXPECT_EQ(dragDropManager->GetExtraInfo(), "ExtraInfo");
}

/**
 * @tc.name: DragDropProxyOnDragEndTest002
 * @tc.desc: OnDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropProxyOnDragEndTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call CreateFrameworkDragDropProxy
     * @tc.expected: step2. return a dragDropProxy successfully
     */
    GestureEvent gestureEvent;
    auto dragDropProxy = dragDropManager->CreateFrameworkDragDropProxy();
    dragDropProxy->OnDragEnd(gestureEvent, true);
    EXPECT_TRUE(dragDropProxy);
    dragDropProxy->OnDragEnd(gestureEvent, false);
    EXPECT_TRUE(dragDropProxy);
}

/**
 * @tc.name: DragDropProxyDestroyDragWindowTest001
 * @tc.desc: DestroyDragWindow
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropProxyDestroyDragWindowTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call CreateFrameworkDragDropProxy
     * @tc.expected: step2. return a dragDropProxy successfully
     */
    GestureEvent gestureEvent;
    auto dragDropProxy = dragDropManager->CreateFrameworkDragDropProxy();
    dragDropProxy->DestroyDragWindow();
    EXPECT_TRUE(dragDropProxy);
}

/**
 * @tc.name: DragDropProxyOnDragEndTest003
 * @tc.desc: OnDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropProxyOnDragEndTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call CreateFrameworkDragDropProxy
     * @tc.expected: step2. return a dragDropProxy successfully
     */
    GestureEvent gestureEvent;
    auto dragDropProxy = dragDropManager->CreateFrameworkDragDropProxy();
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step3. call AddDataToClipboard
     * @tc.expected: step3. ClipBoard.SetData() & ClipBoard.GetData() will be called with printing logs
     *                      they're defined in "components_ng/test/mock/clipboard/mock_clipboard.cpp"
     */
    dragDropManager->AddDataToClipboard(EXTRA_INFO);

    /**
     * @tc.steps: step4. call GetExtraInfoFromClipboard after calling AddDataToClipboard
     * @tc.expected: step4. get the extraInfo successfully
     *                      ClipBoard.GetData() will be called with printing a log
     *                      it's defined in "components_ng/test/mock/clipboard/mock_clipboard.cpp"
     */
    std::string extraInfo;
    dragDropManager->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, EXTRA_INFO);
    dragDropProxy->OnDragEnd(gestureEvent, true);
    EXPECT_TRUE(dragDropProxy);
    dragDropProxy->OnDragEnd(gestureEvent, false);
    EXPECT_TRUE(dragDropProxy);
}

/**
 * @tc.name: DragDropManagerTest042
 * @tc.desc: Test DoDragStartAnimation with RefPtr<OverlayManager>& overlayManager and GestureEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Construct frameNode and overlayManager and update the properties.
     * @tc.expected: frameNode and geometryNode are not null.
     */
    RefPtr<UINode> frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(AceType::DynamicCast<FrameNode>(frameNode));
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step3. call DoDragStartAnimation into arguments overlayManager and event.
     * @tc.expected: retFlag is false.
     */
    GestureEvent event;
    dragDropManager->SetIsDragWithContextMenu(true);
    auto frameNode2 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode2, nullptr);
    auto guestureEventHub = frameNode2->GetOrCreateGestureEventHub();
    dragDropManager->DoDragStartAnimation(overlayManager, event, guestureEventHub);
    dragDropManager->TransDragWindowToDragFwk(111);
    bool retFlag = dragDropManager->GetDragPreviewInfo(overlayManager, dragDropManager->info_, guestureEventHub);
    EXPECT_FALSE(retFlag);

    /**
     * @tc.steps: step4. call DoDragStartAnimation into arguments overlayManager and event.
     * @tc.expected: retFlag is true.
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    std::list<RefPtr<UINode>> children = { customNode };
    frameNode->children_ = children;
    overlayManager->hasDragPixelMap_ = true;
    overlayManager->dragPixmapColumnNodeWeak_ = WeakPtr<FrameNode>(AceType::DynamicCast<FrameNode>(frameNode));
    retFlag = dragDropManager->GetDragPreviewInfo(overlayManager, dragDropManager->info_, guestureEventHub);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step5. call DoDragStartAnimation into arguments overlayManager and event.
     * @tc.expected: retFlag is false.
     */
    dragDropManager->info_.scale = -1.0f;
    dragDropManager->DoDragStartAnimation(overlayManager, event, guestureEventHub);
    retFlag = dragDropManager->IsNeedScaleDragPreview();
    EXPECT_FALSE(retFlag);
}
/**
 * @tc.name: DragDropManagerTest043
 * @tc.desc: Test DoDragMoveAnimate
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call DoDragMoveAnimate with pointerEvent.
     * @tc.expected: dragDropManager->IsNeedScaleDragPreview() returns true.
     */
    PointerEvent pointerEvent;
    dragDropManager->info_.scale = 0.5f;
    dragDropManager->DoDragMoveAnimate(pointerEvent);
    EXPECT_TRUE(dragDropManager->IsNeedScaleDragPreview());

    auto subwindow = Subwindow::CreateSubwindow(VALID_CURRENT_ID);
    SubwindowManager::GetInstance()->AddSubwindow(VALID_CURRENT_ID, subwindow);

    /**
     * @tc.steps: step3. call DoDragMoveAnimate with pointerEvent.
     * @tc.expected: overlayManager is null.
     */
    dragDropManager->DoDragMoveAnimate(pointerEvent);
    auto overlayManager = subwindow->GetOverlayManager();
    ASSERT_EQ(overlayManager, nullptr);
}

/**
 * @tc.name: DragDropManagerTest044
 * @tc.desc: Test CalcDragMoveOffset
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call CalcDragMoveOffset with Dimension and DragPreviewInfo.
     * @tc.expected: dragDropManager->IsNeedScaleDragPreview() return a true value.
     */
    Dimension preserverHeight;
    dragDropManager->info_.scale = 0.5f;
    dragDropManager->CalcDragMoveOffset(preserverHeight, 0, 0, dragDropManager->info_);
    EXPECT_TRUE(dragDropManager->IsNeedScaleDragPreview());
}

/**
 * @tc.name: DragDropManagerTest045
 * @tc.desc: Test GetDragPreviewInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Construct frameNode and overlayManager and update the properties.
     * @tc.expected: frameNode and overlayManager are not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(AceType::DynamicCast<FrameNode>(frameNode));
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->pixmapColumnNodeWeak_ = nullptr;
    overlayManager->SetHasPixelMap(true);

    /**
     * @tc.steps: step3. call GetDragPreviewInfo with arguments overlayManager and dragDropManager->info_.
     * @tc.expected: imageNode is null.
     */
    auto frameNode2 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode2, nullptr);
    auto guestureEventHub = frameNode2->GetOrCreateGestureEventHub();
    dragDropManager->GetDragPreviewInfo(overlayManager, dragDropManager->info_, guestureEventHub);
    auto imageNode = overlayManager->GetPixelMapContentNode();
    ASSERT_EQ(imageNode, nullptr);
}

/**
 * @tc.name: DragDropManagerTest046
 * @tc.desc: Test AddDataToClipboard
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call AddDataToClipboard with extraInfo.
     * @tc.expected: extraInfo.empty() returns true value.
     */
    std::string extraInfo;
    dragDropManager->AddDataToClipboard(extraInfo);
    EXPECT_TRUE(extraInfo.empty());
}

/**
 * @tc.name: DragDropManagerTest047
 * @tc.desc: Test OnDragMoveOut
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call OnDragMoveOut with pointerEvent.
     * @tc.expected: container is null.
     */
    PointerEvent pointerEvent;
    dragDropManager->OnDragMoveOut(pointerEvent);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);

    /**
     * @tc.steps: step3. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step4. call OnDragMoveOut with pointerEvent.
     * @tc.expected: dragDropManager->IsNeedScaleDragPreview() the return value is true.
     */
    dragDropManager->OnDragStart(Point(1.0f, 1.0f), frameNode);
    dragDropManager->info_.scale = 0.5f;
    dragDropManager->OnDragMoveOut(pointerEvent);
    EXPECT_TRUE(dragDropManager->IsNeedScaleDragPreview());
}

/**
 * @tc.name: DragDropManagerTest048
 * @tc.desc: Test UpdateDragListener
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and geometryNode and update the properties.
     * @tc.expected: frameNode and geometryNode are not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(frameNode, nullptr);

    geometryNode->SetFrameSize(FRAME_SIZE);
    frameNode->SetActive(true);
    frameNode->SetGeometryNode(geometryNode);
    std::unordered_set<int32_t> frameNodeList;
    frameNodeList.emplace(frameNode->GetId());
    dragDropManager->parentHitNodes_ = std::move(frameNodeList);
    dragDropManager->RegisterDragStatusListener(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step3. call UpdateDragListener with Point.
     * @tc.expected: dragDropManager->FindHitFrameNodes(point).empty() and
     *               dragDropManager->nodesForDragNotify_.empty() return a false value
     */
    Point point(GLOBAL_X, GLOBAL_Y);
    dragDropManager->UpdateDragListener(point);
    EXPECT_FALSE(dragDropManager->FindHitFrameNodes(point).empty());
    EXPECT_FALSE(dragDropManager->nodesForDragNotify_.empty());

    /**
     * @tc.steps: step4. call UpdateDragListener with Point.
     * @tc.expected: dragDropManager->FindHitFrameNodes(point).empty() return a true value.
     */
    dragDropManager->UnRegisterDragStatusListener(frameNode->GetId());
    frameNode->SetActive(false);
    dragDropManager->RegisterDragStatusListener(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
    dragDropManager->UpdateDragListener(point);
    EXPECT_TRUE(dragDropManager->FindHitFrameNodes(point).empty());

    /**
     * @tc.steps: step5. call UpdateDragListener with Point.
     * @tc.expected: dragDropManager->FindHitFrameNodes(point).empty() return a true value.
     */
    dragDropManager->parentHitNodes_.clear();
    dragDropManager->UpdateDragListener(point);
    EXPECT_TRUE(dragDropManager->FindHitFrameNodes(point).empty());

    /**
     * @tc.steps: step6. call UpdateDragListener with Point.
     * @tc.expected: dragDropManager->FindHitFrameNodes(point).empty() return a false value.
     */
    dragDropManager->UnRegisterDragStatusListener(frameNode->GetId());
    frameNode->SetActive(true);
    dragDropManager->RegisterDragStatusListener(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
    dragDropManager->UpdateDragListener(point);
    EXPECT_FALSE(dragDropManager->FindHitFrameNodes(point).empty());
}

/**
 * @tc.name: DragDropManagerTest049
 * @tc.desc: Test UpdateDragAllowDrop
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest049, TestSize.Level1)
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
     * @tc.steps: step3. call UpdateDragAllowDrop with frameNode and copy.
     * @tc.expected: dragDropManager->summaryMap_.empty() return a true value.
     */
    dragDropManager->summaryMap_.clear();
    dragDropManager->UpdateDragAllowDrop(frameNode, DragBehavior::COPY, -1);
    EXPECT_TRUE(dragDropManager->summaryMap_.empty());

    /**
     * @tc.steps: step4. call UpdateDragAllowDrop with frameNode and copy.
     * @tc.expected: dragDropManager->summaryMap_.empty() return a false value.
     */
    dragDropManager->summaryMap_.insert(make_pair(NODE_TAG, frameNodeNullId));
    dragDropManager->UpdateDragAllowDrop(frameNode, DragBehavior::COPY, -1);
    EXPECT_FALSE(dragDropManager->summaryMap_.empty());

    /**
     * @tc.steps: step5. call UpdateDragAllowDrop with frameNode and copy.
     * @tc.expected: allowDrop.find(ROOT_ETS_TAG) is equal to allowDrop.end().
     */
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(ROOT_ETS_TAG, frameNodeNullId));
    dragDropManager->UpdateDragAllowDrop(frameNode, DragBehavior::COPY, -1);
    EXPECT_TRUE(allowDrop.find(ROOT_ETS_TAG) == allowDrop.end());
}

/**
 * @tc.name: DragDropManagerTest050
 * @tc.desc: Test FireOnDragEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Construct frameNode and update the properties.
     * @tc.expected: frameNode and geometryNode are not null.
     */
    PointerEvent point;
    std::string extraInfo;
    dragDropManager->extraInfo_ = EXTRA_INFO;
    dragDropManager->isMouseDragged_ = true;

    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    std::string onDropInfo;
    auto onDrop = [&onDropInfo](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* info */) {
        onDropInfo = EXTRA_INFO;
    };
    eventHub->SetOnDrop(std::move(onDrop));
    EXPECT_TRUE(eventHub->HasOnDrop());

    /**
     * @tc.steps: step3. call FireOnDragEvent.
     * @tc.expected: dragDropManager->isMouseDragged_ is true.
     */
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::ENTER, extraInfo);
    EXPECT_TRUE(dragDropManager->isMouseDragged_);

    /**
     * @tc.steps: step4. call FireOnDragEvent.
     * @tc.expected: !dragDropManager->isDragWindowShow_ is false.
     */
    dragDropManager->isDragWindowShow_ = true;
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::ENTER, extraInfo);
    EXPECT_FALSE(!dragDropManager->isDragWindowShow_);
}

/**
 * @tc.name: DragDropManagerTest051
 * @tc.desc: Test OnDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call OnDragEnd with pointerEvent and extraInfo.
     * @tc.expected: dragDropManager->isDragCancel_ is true.
     */
    std::string extraInfo;
    PointerEvent pointerEvent;
    dragDropManager->SetIsDragCancel(true);
    dragDropManager->OnDragEnd(pointerEvent, extraInfo);
    EXPECT_TRUE(dragDropManager->isDragCancel_);
}

/**
 * @tc.name: DragDropManagerTest053
 * @tc.desc: Test CalcDragPreviewDistanceWithPoint
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    frameNode->GetTransformRelativeOffset();
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. call CalcDragPreviewDistanceWithPoint.
     * @tc.expected: pipeline is true.
     */
    Dimension preserverHeight;
    dragDropManager->CalcDragPreviewDistanceWithPoint(preserverHeight, GLOBAL_X, GLOBAL_Y, dragDropManager->info_);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);
}
/**
 * @tc.name: DragDropManagerTest054
 * @tc.desc: Test DragEventStrictReportingEnabled
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest054, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    bool reportingEnabledDefault = dragDropManager->IsEventStrictReportingEnabled();
    dragDropManager->SetEventStrictReportingEnabled(true);
    bool reportingEnabledTrue = dragDropManager->IsEventStrictReportingEnabled();
    dragDropManager->SetEventStrictReportingEnabled(false);
    bool reportingEnabledFalse = dragDropManager->IsEventStrictReportingEnabled();
    ASSERT_FALSE(reportingEnabledDefault);
    ASSERT_TRUE(reportingEnabledTrue);
    ASSERT_FALSE(reportingEnabledFalse);
}

/**
 * @tc.name: DragDropManagerTest055
 * @tc.desc: Test AddDataToClipboard
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call AddDataToClipboard with extraInfo.
     * @tc.expected: extraInfo.empty() returns true value.
     */
    std::string extraInfo;
    dragDropManager->AddDataToClipboard(extraInfo);
    EXPECT_TRUE(extraInfo.empty());
}

/**
 * @tc.name: DragDropManagerTest056
 * @tc.desc: Test ClearExtraInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;

    /**
     * @tc.expected: draggedNode is true.
     */
    dragDropManager->ClearExtraInfo();
    EXPECT_TRUE(draggedNode);
}

/**
 * @tc.name: DragDropManagerTest057
 * @tc.desc: Test SetExtraInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call OnDragStart
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);

    /**
     * @tc.expected: dragDropManager->GetExtraInfo() returns "ExtraInfo".
     */
    dragDropManager->SetExtraInfo("ExtraInfo");
    EXPECT_EQ(dragDropManager->GetExtraInfo(), "ExtraInfo");
}

/**
 * @tc.name: DragDropManagerTest058
 * @tc.desc: Test GetItemIndex
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: FireOnItemDropEvent
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;

    /**
     * @tc.steps: step3. call OnItemDragEnd
     */
    dragDropManager->OnItemDragEnd(0.0, 0.0, 0, DragType::COMMON);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
    OHOS::Ace::ItemDragInfo itemDragInfo;

    /**
     * @tc.steps: step4. call GetItemIndex
     * @tc.expected: draggedNode is true.
     */
    dragDropManager->GetItemIndex(frameNode, DragType::TEXT, 0.0, 0.0);
    ASSERT_TRUE(draggedNode);
    dragDropManager->GetItemIndex(frameNode, DragType::COMMON, 0.0, 0.0);
    ASSERT_TRUE(draggedNode);
    dragDropManager->GetItemIndex(frameNode, DragType::GRID, 0.0, 0.0);
    ASSERT_TRUE(draggedNode);
    dragDropManager->draggedGridFrameNode_ = frameNode;
    dragDropManager->GetItemIndex(frameNode, DragType::GRID, 0.0, 0.0);
    ASSERT_TRUE(draggedNode);
}

/**
 * @tc.name: DragDropManagerTest059
 * @tc.desc: Test FireOnItemDropEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call OnDragStart
     * @tc.expected: FireOnItemDropEvent
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;

    /**
     * @tc.steps: step3. call OnItemDragEnd
     */
    dragDropManager->OnItemDragEnd(0.0, 0.0, 0, DragType::COMMON);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
    OHOS::Ace::ItemDragInfo itemDragInfo;

    /**
     * @tc.steps: step4. call FireOnItemDropEvent
     * @tc.expected: draggedNode and preTargetNode are true.
     */
    dragDropManager->FireOnItemDropEvent(frameNode, DragType::TEXT, itemDragInfo, 0, 0, true);
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
}

/**
 * @tc.name: DragDropManagerTest061
 * @tc.desc: Test DoDragMoveAnimate
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest061, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call DoDragMoveAnimate with pointerEvent.
     * @tc.expected: dragDropManager->IsNeedScaleDragPreview() returns true.
     */
    PointerEvent pointerEvent;
    dragDropManager->info_.scale = 0.5f;
    dragDropManager->DoDragMoveAnimate(pointerEvent);
    EXPECT_TRUE(dragDropManager->IsNeedScaleDragPreview());

    auto subwindow = Subwindow::CreateSubwindow(VALID_CURRENT_ID);
    SubwindowManager::GetInstance()->AddSubwindow(VALID_CURRENT_ID, subwindow);

    /**
     * @tc.steps: step3. call DoDragMoveAnimate with pointerEvent.
     * @tc.expected: overlayManager is null.
     */
    dragDropManager->DoDragMoveAnimate(pointerEvent);
    auto overlayManager = subwindow->GetOverlayManager();
    ASSERT_EQ(overlayManager, nullptr);
}

/**
 * @tc.name: DragDropManagerTest062
 * @tc.desc: Test FireOnEditableTextComponent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager and create a point.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. Create a normal frameNode which is not a editable text component,
     *  and test FireOnEditableTextComponent.
     * @tc.expected: step2.
     */
    {
        auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::ENTER);
    }

    /**
     * @tc.steps: step3. Create a editable text component, and test FireOnEditableTextComponent.
     * @tc.expected: step3.
     */
    {
        auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXTINPUT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
#ifdef ENABLE_DRAG_FRAMEWORK
        EXPECT_CALL(*(AceType::DynamicCast<MockInteractionInterface>(MockInteractionInterface::GetInstance())),
            EnterTextEditorArea(_))
            .Times(1)
            .WillOnce(::testing::Return(0));
#else
        EXPECT_CALL(*(AceType::DynamicCast<MockInteractionInterface>(MockInteractionInterface::GetInstance())),
            EnterTextEditorArea(_))
            .Times(1);
#endif // ENABLE_DRAG_FRAMEWORK
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::ENTER);
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::ENTER);
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::MOVE);
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::LEAVE);
    }
}
/**
 * @tc.name: DragDropManagerTest063
 * @tc.desc: Test FireOnItemDragEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    GestureEvent gestureEvent;
    auto dragDropProxy = dragDropManager->CreateFrameworkDragDropProxy();
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. construct a frameNode whose tag is List set its ItemDragEvent and GeometryNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(LIST_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    auto eventHub = frameNode->GetEventHub<ListEventHub>();

    // Set OnItemDragLeave callback
    std::string itemInfoLeave;
    auto onItemDragLeave = [&itemInfoLeave](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */) {
        itemInfoLeave = ITEM_INFO_LEAVE;
    };
    eventHub->SetOnItemDragLeave(std::move(onItemDragLeave));

    // Set OnItemDragMove callback
    std::string itemInfoMove;
    auto onItemDragMove = [&itemInfoMove](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                              int32_t /* insertIndex */) { itemInfoMove = ITEM_INFO_MOVE; };
    eventHub->SetOnItemDragMove(std::move(onItemDragMove));

    // Set OnItemDragEnter callback
    std::string itemInfoEnter;
    auto onItemDragEnter = [&itemInfoEnter](const ItemDragInfo& /* dragInfo */) { itemInfoEnter = ITEM_INFO_ENTER; };
    eventHub->SetOnItemDragEnter(std::move(onItemDragEnter));

    // Set geometry node to make sure (GLOBAL_X, GLOBAL_Y) in geoNode.frameRect_
    auto geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetMarginFrameOffset(FRAME_OFFSET);
    geoNode->SetFrameSize(FRAME_SIZE);
    frameNode->SetGeometryNode(geoNode);

    /**
     * @tc.steps: step3. call OnItemDragMove
     *                   case: listDragFrameNodes_ is empty & preGridTargetFrameNode_ is not null
     * @tc.expected: step3. frameNode's onItemDragLeave_ will be called
     *                      itemInfoLeave will be assigned to ITEM_INFO_LEAVE
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    auto preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    dragDropManager->AddGridDragFrameNode(frameNode->GetId(), frameNode);

    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    // to force call the FireOnItemDragEvent with DragType::LIST and DragEventType::MOVE
    OHOS::Ace::ItemDragInfo itemDragInfo;
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::MOVE, DRAGGED_INDEX);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::ENTER, DRAGGED_INDEX);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::START, DRAGGED_INDEX);
    EXPECT_EQ(itemInfoMove, ITEM_INFO_MOVE);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::ENTER, DRAGGED_INDEX);
    EXPECT_EQ(itemInfoMove, ITEM_INFO_MOVE);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::MOVE, DRAGGED_INDEX);
    EXPECT_EQ(itemInfoMove, ITEM_INFO_MOVE);
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::GRID, itemDragInfo, DragEventType::START, DRAGGED_INDEX);
    EXPECT_EQ(itemInfoMove, ITEM_INFO_MOVE);
}
/**
 * @tc.name: DragDropManagerTest064
 * @tc.desc: Test FindTargetInChildNodes with parentNode being nullptr
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest064, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> parentNode = nullptr;
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    bool findDrop = true;
    auto result = dragDropManager->FindTargetInChildNodes(parentNode, hitFrameNodes, findDrop);
    EXPECT_EQ(result, nullptr);
}
/**
 * @tc.name: DragDropManagerTest065
 * @tc.desc: Test FindTargetInChildNodes with matching hitFrameNode having no event hub
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest065, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto parentNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    std::vector<RefPtr<FrameNode>> hitFrameNodes = { parentNode };
    bool findDrop = true;
    auto result = dragDropManager->FindTargetInChildNodes(parentNode, hitFrameNodes, findDrop);
    EXPECT_EQ(result, nullptr);
}

/**
* @tc.name: DragDropManagerTest066
* @tc.desc: Test FindDragFrameNodeByPosition and FindTargetDropNode
* @tc.type: FUNC
* @tc.author:
*/
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest066, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    EXPECT_NE(dragDropManager, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto rootNode = pipeline->GetRootElement();
    EXPECT_NE(rootNode, nullptr);
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(rootNode);
    EXPECT_NE(parentFrameNode, nullptr);
    parentFrameNode->isActive_ = false;
    constexpr float GLOBAL_X = 10.0f;
    constexpr float GLOBAL_Y = 20.0f;
    auto targetDropNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y);
    EXPECT_TRUE(!parentFrameNode->IsActive());
    EXPECT_TRUE(parentFrameNode->IsVisible());
    EXPECT_EQ(targetDropNode, nullptr);

    parentFrameNode->isActive_ = true;
    auto renderContext = parentFrameNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y);
    EXPECT_FALSE(!parentFrameNode->IsActive());
    EXPECT_FALSE(!parentFrameNode->IsVisible());
}

/**
* @tc.name: DragDropManagerTest067
* @tc.desc: Test UpdateDragAllowDrop
* @tc.type: FUNC
* @tc.author:
*/
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest067, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    EXPECT_NE(dragDropManager, nullptr);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    dragDropManager->summaryMap_.insert(make_pair(NODE_TAG, frameNodeNullId));
    std::set<std::string> allowDrop = { NODE_TAG };
    frameNode->SetAllowDrop(allowDrop);
    const auto& dragFrameNodeAllowDrop = frameNode->GetAllowDrop();
    EXPECT_NE(dragDropManager->draggedFrameNode_, frameNode);
    dragDropManager->UpdateDragAllowDrop(frameNode, DragBehavior::UNKNOWN, -1);
    dragDropManager->UpdateDragAllowDrop(frameNode, DragBehavior::MOVE, -1);
    EXPECT_FALSE(dragFrameNodeAllowDrop.empty());
    EXPECT_FALSE(dragDropManager->summaryMap_.empty());

    dragDropManager->draggedFrameNode_ = frameNode;
    dragDropManager->UpdateDragAllowDrop(frameNode, DragBehavior::UNKNOWN, -1);
    EXPECT_EQ(dragDropManager->draggedFrameNode_, frameNode);
}

/**
* @tc.name: DragDropManagerTest068
* @tc.desc: Test PrintDragFrameNode
* @tc.type: FUNC
* @tc.author:
*/
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest068, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    OHOS::Ace::PointerEvent point;

    /**
     * @tc.steps: step2. Invoke PrintDragFrameNode
     * @tc.expected: dragDropManager->preTargetFrameNode_ is false
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    dragDropManager->preTargetFrameNode_ = nullptr;
    dragDropManager->PrintDragFrameNode(point, frameNode);
    EXPECT_FALSE(dragDropManager->preTargetFrameNode_);
}

/**
* @tc.name: DragDropManagerTest069
* @tc.desc: Test PrintGridDragFrameNode
* @tc.type: FUNC
* @tc.author:
*/
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest069, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. Invoke PrintGridDragFrameNode
     * @tc.expected: dragDropManager->preGridTargetFrameNode_ is false
     */
    auto frameNode1 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode1, nullptr);
    dragDropManager->PrintGridDragFrameNode(GLOBAL_X, GLOBAL_Y, frameNode1);
    EXPECT_FALSE(dragDropManager->preGridTargetFrameNode_);

    /**
     * @tc.steps: step3. Invoke PrintGridDragFrameNode
     * @tc.expected: dragDropManager->preGridTargetFrameNode_ is true
     */
    auto frameNode2 = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode2, nullptr);
    dragDropManager->preGridTargetFrameNode_ = frameNode2;
    dragDropManager->PrintGridDragFrameNode(GLOBAL_X, GLOBAL_Y, frameNode1);
    EXPECT_TRUE(dragDropManager->preGridTargetFrameNode_);
}

/**
* @tc.name: DragDropManagerTest070
* @tc.desc: Test TransDragWindowToDragFwk
* @tc.type: FUNC
* @tc.author:
*/
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest070, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto containerId = Container::CurrentId();

    /**
     * @tc.steps: step2. Invoke TransDragWindowToDragFwk
     * @tc.expected: dragDropManager->isDragFwkShow_ is true
     */
    dragDropManager->isDragFwkShow_ = true;
    dragDropManager->TransDragWindowToDragFwk(containerId);
    EXPECT_TRUE(dragDropManager->isDragFwkShow_);
}

/**
* @tc.name: DragDropManagerTest071
* @tc.desc: Test ReachMoveLimit and isTimeLimited and isDistanceLimited
* @tc.type: FUNC
* @tc.author:
*/
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest071, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. Invoke ReachMoveLimit
     * @tc.expected: isTimeLimited returns false and isDistanceLimited returns true
     */
    PointerEvent pointerEvent;
    auto point = Point(1, 1);
    pointerEvent.sourceTool = SourceTool::MOUSE;
    auto moveLimit = dragDropManager->ReachMoveLimit(pointerEvent, point);
    EXPECT_FALSE(dragDropManager->isTimeLimited(pointerEvent, point));
    EXPECT_TRUE(dragDropManager->isDistanceLimited(point));
    EXPECT_FALSE(moveLimit);

    /**
     * @tc.steps: step3. Invoke ReachMoveLimit
     * @tc.expected: isTimeLimited returns false and isDistanceLimited returns false
     */
    point = Point(100, 100);
    moveLimit = dragDropManager->ReachMoveLimit(pointerEvent, point);
    EXPECT_FALSE(dragDropManager->isTimeLimited(pointerEvent, point));
    EXPECT_FALSE(dragDropManager->isDistanceLimited(point));
    EXPECT_FALSE(moveLimit);
}

/**
* @tc.name: DragDropManagerTest072
* @tc.desc: Test ReachMoveLimit and isTimeLimited and isDistanceLimited
* @tc.type: FUNC
* @tc.author:
*/
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest072, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. Invoke RequestDragSummaryInfoAndPrivilege
     */
    int ret = InteractionInterface::GetInstance()->AddPrivilege();
    dragDropManager->RequestDragSummaryInfoAndPrivilege();
    EXPECT_FALSE(ret != 0);
    EXPECT_FALSE(SystemProperties::GetDebugEnabled());

    /**
     * @tc.steps: step3. Invoke RequestDragSummaryInfoAndPrivilege
     */
    SystemProperties::debugEnabled_ = true;
    dragDropManager->RequestDragSummaryInfoAndPrivilege();
    EXPECT_FALSE(ret != 0);
    EXPECT_TRUE(SystemProperties::GetDebugEnabled());
}

/**
* @tc.name: DragDropManagerTest073
* @tc.desc: Test DoDropAction
* @tc.type: FUNC
* @tc.author:
*/
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest073, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step1. Invoke DoDropAction
     */
    PointerEvent pointerEvent;
    auto dragFrameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    std::string udKey;
    InteractionInterface::GetInstance()->GetUdKey(udKey);
    auto unifiedData = dragDropManager->RequestUDMFDataWithUDKey(udKey);
    dragDropManager->DoDropAction(dragFrameNode, pointerEvent, unifiedData, udKey);
    EXPECT_FALSE(!udKey.empty());
}

/**
* @tc.name: DragDropManagerTest074
* @tc.desc: Test DoDropAction
* @tc.type: FUNC
* @tc.author:
*/
HWTEST_F(DragDropManagerTestNgNew, DragDropManagerTest074, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step1. Invoke DoDropAction
     */
    PointerEvent pointerEvent;
    auto dragFrameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), false);
    std::string udKey;
    InteractionInterface::GetInstance()->GetUdKey(udKey);
    auto unifiedData = dragDropManager->RequestUDMFDataWithUDKey(udKey);
    dragDropManager->DoDropAction(dragFrameNode, pointerEvent, unifiedData, udKey);
    EXPECT_FALSE(!udKey.empty());
}
} // namespace OHOS::Ace::NG