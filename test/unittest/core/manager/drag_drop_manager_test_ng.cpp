/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

void  TestFunction(const DragPointerEvent& event) {}
void DragDropManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DragDropManagerTest001
 * @tc.desc: CreateAndShowItemDragOverlay via pixelMap and gestureEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call CreateAndShowItemDragOverlay
     * @tc.expected: step2. return a dragDropProxy successfully
     *                      DragWindow.DrawPixelMap() will be called
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    GestureEvent gestureEvent;
    RefPtr<EventHub> eventhub;
    auto dragDropProxy = dragDropManager->CreateAndShowItemDragOverlay(pixelMap, gestureEvent, eventhub);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step3. call CreateAndShowItemDragOverlay with null.
     * @tc.expected: step3. return dragDropProxy to false.
     */
    pixelMap = nullptr;
    dragDropProxy = dragDropManager->CreateAndShowItemDragOverlay(pixelMap, gestureEvent, eventhub);
    EXPECT_FALSE(dragDropProxy);
}

/**
 * @tc.name: DragDropManagerTest002
 * @tc.desc: CreateAndShowItemDragOverlay via customNode and gestureEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call CreateAndShowItemDragOverlay
     * @tc.expected: step2. return a dragDropProxy successfully
     *                      DragWindow.DrawFrameNode() will be called
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    RefPtr<EventHub> eventhub;
    auto dragDropProxy = dragDropManager->CreateAndShowItemDragOverlay(customNode, gestureEvent, eventhub);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.expected: step2. the customNode's parent is root
     */
    auto root = customNode->GetParent();
    auto rootTag = root->GetTag();
    EXPECT_EQ(rootTag, ROOT_ETS_TAG);
}

/**
 * @tc.name: DragDropManagerTest003
 * @tc.desc: Test UpdateItemDragPosition
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call CreateAndShowItemDragOverlay
     * @tc.expected: step2. return a dragDropProxy successfully
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    RefPtr<EventHub> eventhub;
    auto dragDropProxy = dragDropManager->CreateAndShowItemDragOverlay(customNode, gestureEvent, eventhub);
    EXPECT_TRUE(dragDropProxy);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 800, 800 }); // 800: window width and height
    /**
     * @tc.steps: step3. call UpdateItemDragPosition
     * @tc.expected: step3. itemDragOverlayNode_'s position is updated to (GLOBAL_X, GLOBAL_Y)
     */
    dragDropManager->UpdateItemDragPosition(GLOBAL_X, GLOBAL_Y);
    auto renderContext = dragDropManager->itemDragOverlayNode_->GetRenderContext();
    EXPECT_EQ(renderContext->GetPosition().value(), OffsetT<Dimension>(Dimension(GLOBAL_X), Dimension(GLOBAL_Y)));
}

/**
 * @tc.name: DragDropManagerTest004
 * @tc.desc: Test Functions relevant to Clipboard
             Call this functions in order (AddDataToClipboard->GetExtraInfoFromClipboard->RestoreClipboardData)
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call AddDataToClipboard
     * @tc.expected: step2. ClipBoard.SetData() & ClipBoard.GetData() will be called with printing logs
     *                      they're defined in "components_ng/test/mock/clipboard/mock_clipboard.cpp"
     */
    dragDropManager->AddDataToClipboard(EXTRA_INFO);

    /**
     * @tc.steps: step3. call GetExtraInfoFromClipboard after calling AddDataToClipboard
     * @tc.expected: step3. get the extraInfo successfully
     *                      ClipBoard.GetData() will be called with printing a log
     *                      it's defined in "components_ng/test/mock/clipboard/mock_clipboard.cpp"
     */
    std::string extraInfo;
    dragDropManager->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, EXTRA_INFO);

    /**
     * @tc.steps: step4. call GetExtraInfoFromClipboard
     * @tc.expected: step4. extraInfo is equal to EXTRA_INFO
     */
    dragDropManager->clipboard_ = nullptr;
    dragDropManager->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, EXTRA_INFO);

    /**
     * @tc.steps: step5. call AddDataToClipboard with empty.
     * @tc.expected: step5. extraInfo is equal to EXTRA_INFO
     */
    dragDropManager->AddDataToClipboard(extraInfo);
    EXPECT_EQ(extraInfo, EXTRA_INFO);
}

/**
 * @tc.name: DragDropManagerTest005
 * @tc.desc: Test Functions relevant to Clipboard
             Call this functions not in order (to test boundary cases)
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step3. call AddDataToClipboard twice
     *                   case: clipboard_ & addDataCallback_ has exited,
     * @tc.expected: step3. EXTRA_INFO_2 will be added
     */
    dragDropManager->AddDataToClipboard(EXTRA_INFO);
    dragDropManager->AddDataToClipboard(EXTRA_INFO_2);
    std::string extraInfo;
    dragDropManager->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, EXTRA_INFO_2);

    /**
     * @tc.steps: step4. call GetExtraInfoFromClipboard twice
     *                   case: clipboard_ & addDataCallback_ has exited
     * @tc.expected: step4. get the extraInfo successfully
     */
    dragDropManager->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, EXTRA_INFO_2);
}

/**
 * @tc.name: DragDropManagerTest006
 * @tc.desc: Test DestroyDragWindow & CheckDragDropProxy
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call DestroyDragWindow without creating dragWindow
     * @tc.expected: step2. no fatal error happens
     */
    dragDropManager->DestroyDragWindow();

    /**
     * @tc.steps: step3. call CheckDragDropProxy without creating dragWindow
     * @tc.expected: step3. currentId is -1 at first
     */
    auto flag = dragDropManager->CheckDragDropProxy(INVALID_CURRENT_ID);
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step4. call CreateFrameworkDragDropProxy
     * @tc.expected: step4. return a dragDropProxy successfully
     */
    auto dragDropProxy = dragDropManager->CreateFrameworkDragDropProxy();
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step5. call CheckDragDropProxy after creating dragWindow
     * @tc.expected: step5. currentId recover to -1
     *                      MockDragWindow.Destroy() will be called
     */
    dragDropManager->DestroyDragWindow();
    flag = dragDropManager->CheckDragDropProxy(INVALID_CURRENT_ID);
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step6. call CheckDragDropProxy (use proxy to create drag window)
     * @tc.expected: step6. currentId recover to -1
     */
    auto dragDropManager2 = AceType::MakeRefPtr<DragDropManager>();
    auto dragDropProxy2 = dragDropManager2->CreateFrameworkDragDropProxy();
    EXPECT_TRUE(dragDropProxy2);
    dragDropManager2->DestroyDragWindow();
    flag = dragDropManager2->CheckDragDropProxy(INVALID_CURRENT_ID);
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: DragDropManagerTest007
 * @tc.desc: Test OnDragStart & onDragCancel & OnItemDragStart & onItemDragCancel
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest007, TestSize.Level1)
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
    ASSERT_TRUE(draggedNode);
    ASSERT_TRUE(preTargetNode);
    auto draggedNodeTag = draggedNode->GetTag();
    auto preTargetNodeTag = preTargetNode->GetTag();
    EXPECT_EQ(draggedNodeTag, NODE_TAG);
    EXPECT_EQ(preTargetNodeTag, NODE_TAG);

    /**
     * @tc.steps: step3. call onDragCancel
     * @tc.expected: step3. draggedFrameNode_ &  preTargetFrameNode_ are assigned to nullptr
     */
    dragDropManager->onDragCancel();
    draggedNode = dragDropManager->draggedFrameNode_;
    preTargetNode = dragDropManager->preTargetFrameNode_;
    EXPECT_FALSE(draggedNode);
    EXPECT_FALSE(preTargetNode);

    /**
     * @tc.steps: step4. call OnItemDragStart
     * @tc.expected: step4. preGridTargetNodeTag is assigned to the gridFrameNode created previously
     */
    auto gridFrameNode = AceType::MakeRefPtr<FrameNode>(GRID_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, gridFrameNode);
    auto preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    ASSERT_TRUE(preGridTargetNode);
    auto preGridTargetNodeTag = preGridTargetNode->GetTag();
    EXPECT_EQ(preGridTargetNodeTag, GRID_TAG);

    /**
     * @tc.steps: step5. call onItemDragCancel
     * @tc.expected: step5. preGridTargetFrameNode_ is assigned to nullptr
     */
    dragDropManager->onItemDragCancel();
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetNode);
}

/**
 * @tc.name: DragDropManagerTest009
 * @tc.desc: Test OnItemDragMove DragType is Grid
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. construct a frameNode whose tag is Grid set its ItemDragEvent and GeometryNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(GRID_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_TRUE(eventHub);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    auto dragDropProxy = dragDropManager->CreateAndShowItemDragOverlay(customNode, gestureEvent, eventHub);
    EXPECT_TRUE(dragDropProxy);

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
     * @tc.steps: step4. call OnItemDragMove
     *                   case: gridDragFrameNodes_ is empty & preGridTargetFrameNode_ is not null
     * @tc.expected: step4. frameNode's onItemDragLeave_ will be called
     *                      itemInfoLeave will be assigned to ITEM_INFO_LEAVE
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    auto preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    ASSERT_TRUE(preGridTargetNode);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    EXPECT_EQ(itemInfoLeave, ITEM_INFO_LEAVE);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetNode);

    /**
     * @tc.steps: step5. call AddGridDragFrameNode
     *                   after that, gridDragFrameNodes_ is not empty
     */
    dragDropManager->AddGridDragFrameNode(frameNode->GetId(), frameNode);

    /**
     * @tc.steps: step6. call OnItemDragMove
     *                   case: gridDragFrameNodes_ is not empty & preGridTargetFrameNode_ equals the frameNode
     * @tc.expected: step6. frameNode's OnItemDragMove_ will be called
     *                      itemInfoMove will be assigned to ITEM_INFO_MOVE
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_TRUE(preGridTargetNode);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);

    /**
     * @tc.steps: step7. call OnItemDragMove
     *                   case: gridDragFrameNodes_ is not empty & preGridTargetFrameNode_ not equals the frameNode
     * @tc.expected: step7. frameNode's onDragItemEnter_ will be called
     *                      itemInfoEnter will be assigned to ITEM_INFO_ENTER
     *                      preGridTargetFrameNode_'s onDragItemLeave will be called
     *                      leaveExtraInfoNew will be assigned to ITEM_INFO_ENTER
     *                      preGridTargetFrameNode_ is assigned to frameNode
     */
    auto newFrameNode = AceType::MakeRefPtr<FrameNode>(GRID_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, newFrameNode);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_TRUE(preGridTargetNode);
    // Set newFrameNode's onDragLeave callback
    auto eventHubNew = newFrameNode->GetEventHub<GridEventHub>();
    ASSERT_TRUE(eventHubNew);
    std::string itemInfoLeaveNew;
    auto onItemDragLeaveNew = [&itemInfoLeaveNew](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */) {
        itemInfoLeaveNew = ITEM_INFO_ENTER;
    };
    eventHubNew->SetOnItemDragLeave(std::move(onItemDragLeaveNew));
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    EXPECT_EQ(itemInfoLeaveNew, ITEM_INFO_ENTER);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    ASSERT_FALSE(preGridTargetNode);
}

/**
 * @tc.name: DragDropManagerTest010
 * @tc.desc: Test OnItemDragMove DragType is List
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest009, TestSize.Level1)
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
    ASSERT_TRUE(eventHub);

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
    ASSERT_TRUE(preGridTargetNode);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    EXPECT_EQ(itemInfoLeave, ITEM_INFO_LEAVE);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetNode);

    /**
     * @tc.steps: step4. call AddGridDragFrameNode
     *                   after that, listDragFrameNodes_ is not empty
     *                   need adding grid maybe a bug
     */
    dragDropManager->AddGridDragFrameNode(frameNode->GetId(), frameNode);

    /**
     * @tc.steps: step5. call OnItemDragMove
     *                   case: listDragFrameNodes_ is not empty & preGridTargetFrameNode_ equals the frameNode
     * @tc.expected: step5. a gridEventHub is trying to get by the frameNode,
     *                      but it's list type, so will return early(maybe that is a bug)
     *                      itemInfoMove will not be assigned DragWindow.MoveTo() will be called
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_TRUE(preGridTargetNode);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    EXPECT_EQ(itemInfoMove, "");
    // to force call the FireOnItemDragEvent with DragType::LIST and DragEventType::MOVE
    OHOS::Ace::ItemDragInfo itemDragInfo;
    dragDropManager->FireOnItemDragEvent(frameNode, DragType::LIST, itemDragInfo, DragEventType::MOVE, DRAGGED_INDEX);
    EXPECT_EQ(itemInfoMove, ITEM_INFO_MOVE);

    /**
     * @tc.steps: step6. call OnItemDragMove
     *                   case: listDragFrameNodes_ is not empty & preGridTargetFrameNode_ not equals the frameNode
     * @tc.expected: step6. frameNode's onDragItemEnter_ will be called
     *                      itemInfoEnter will be assigned to ITEM_INFO_ENTER
     *                      preGridTargetFrameNode_'s onDragItemLeave will be called
     *                      leaveExtraInfoNew will be assigned to ITEM_INFO_ENTER
     *                      preGridTargetFrameNode_ is assigned to frameNode
     */
    auto newFrameNode = AceType::MakeRefPtr<FrameNode>(LIST_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, newFrameNode);
    EXPECT_TRUE(dragDropManager->preGridTargetFrameNode_);
    // Set newFrameNode's onDragLeave callback
    auto eventHubNew = newFrameNode->GetEventHub<ListEventHub>();
    ASSERT_TRUE(eventHubNew);
    std::string itemInfoLeaveNew;
    auto onItemDragLeaveNew = [&itemInfoLeaveNew](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */) {
        itemInfoLeaveNew = ITEM_INFO_ENTER;
    };
    eventHubNew->SetOnItemDragLeave(std::move(onItemDragLeaveNew));
    EXPECT_EQ(itemInfoEnter, "");
    EXPECT_EQ(itemInfoLeaveNew, "");
    ASSERT_TRUE(dragDropManager->preGridTargetFrameNode_);
    auto preGridTargetNodeTag = dragDropManager->preGridTargetFrameNode_->GetTag();
    EXPECT_EQ(preGridTargetNodeTag, LIST_TAG);

    /**
     * @tc.steps: step7. call OnItemDragMove
     *                   case: listDragFrameNodes_ is not empty & preGridTargetFrameNode_ is null
     * @tc.expected: step7. frameNode's onDragItemEnter_ will be called
     *                      itemInfoEnter will be assigned to ITEM_INFO_ENTER
     */
    dragDropManager->onItemDragCancel();
    EXPECT_FALSE(dragDropManager->preGridTargetFrameNode_);
    itemInfoEnter = "";
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    EXPECT_EQ(itemInfoEnter, "");
}

/**
 * @tc.name: DragDropManagerTest011
 * @tc.desc: Test OnItemDragEnd type is grid
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. construct a frameNode which type is grid and set its GeometryNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_TRUE(eventHub);

    // Set geometry node to make sure (GLOBAL_X, GLOBAL_Y) in geoNode.frameRect_
    auto geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetMarginFrameOffset(FRAME_OFFSET);
    geoNode->SetFrameSize(FRAME_SIZE);
    frameNode->SetGeometryNode(geoNode);

    /**
     * @tc.steps: step3. call OnItemDragEnd
     *                   case: gridDragFrameNodes_ is empty
     * @tc.expected: step3. preGridTargetFrameNode_ is null
     */
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    auto preGridTargetFrameNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetFrameNode);

    // case: gridDragFrameNodes_ is empty & preGridTargetFrameNode_ is not null
    auto preGridTargetNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    auto preGridEvent = preGridTargetNode->GetEventHub<GridEventHub>();
    std::string preGridDropInfo;
    auto onPreGridItemDrop = [&preGridDropInfo](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                                 int32_t /* insertIndex */, bool /* isSuccess */) { preGridDropInfo = EXTRA_INFO; };
    preGridEvent->SetOnItemDrop(std::move(onPreGridItemDrop));
    dragDropManager->preGridTargetFrameNode_ = preGridTargetNode;
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    EXPECT_EQ(preGridDropInfo, "");

    /**
     * @tc.steps: step4. call AddDragFrameNode
     *                   after that, gridDragFrameNodes_ is not empty
     */
    dragDropManager->AddGridDragFrameNode(frameNode->GetId(), frameNode);

    /**
     * @tc.steps: step5. call OnItemDragEnd
     *                   case: eventHub dose not have onDrop_
     * @tc.expected: step5. preGridTargetFrameNode_ is null
     */
    dragDropManager->preGridTargetFrameNode_ = nullptr;
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    preGridTargetFrameNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetFrameNode);

    /**
     * @tc.steps: step6. call OnItemDragEnd
     *                   case: eventHub dose have onDrop_
     * @tc.expected: step6. frameNode's OnDrop_ will be called
     *                      itemDropInfo will be assigned to EXTRA_INFO
     *                      preGridTargetFrameNode_ be assigned to nullptr
     */
    std::string itemDropInfo;
    auto onItemDrop = [&itemDropInfo](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                          int32_t /* insertIndex */, bool /* isSuccess */) { itemDropInfo = EXTRA_INFO; };
    eventHub->SetOnItemDrop(onItemDrop);
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    preGridTargetFrameNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetFrameNode);

    // case: preGridTargetFrameNode_ == dragFrameNode
    dragDropManager->preGridTargetFrameNode_ = frameNode;
    itemDropInfo.clear();
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);

    // case: preGridTargetFrameNode_ != dragFrameNode
    dragDropManager->preGridTargetFrameNode_ = preGridTargetNode;
    itemDropInfo.clear();
    preGridDropInfo.clear();
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    EXPECT_EQ(preGridDropInfo, "");
}

/**
 * @tc.name: DragDropManagerTest012
 * @tc.desc: Test OnItemDragEnd type is list
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. construct a frameNode which type is list and set its GeometryNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    ASSERT_TRUE(eventHub);

    // Set geometry node to make sure (GLOBAL_X, GLOBAL_Y) in geoNode.frameRect_
    auto geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetMarginFrameOffset(FRAME_OFFSET);
    geoNode->SetFrameSize(FRAME_SIZE);
    frameNode->SetGeometryNode(geoNode);

    /**
     * @tc.steps: step3. call OnItemDragEnd
     *                   case: listDragFrameNodes_ is empty
     * @tc.expected: step3. preGridTargetFrameNode_ is null
     */
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    auto preGridTargetFrameNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetFrameNode);

    /**
     * @tc.steps: step4. call AddDragFrameNode
     *                   after that, listDragFrameNodes_ is not empty
     */
    dragDropManager->AddListDragFrameNode(frameNode->GetId(), frameNode);

    /**
     * @tc.steps: step5. call OnItemDragEnd
     * @tc.expected: step5. frameNode's OnDrop_ will be called
     *                      itemDropInfo will be assigned to EXTRA_INFO
     *                      preGridTargetFrameNode_ be assigned to nullptr
     */
    std::string itemDropInfo;
    auto onItemDrop = [&itemDropInfo](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                          int32_t /* insertIndex */, bool /* isSuccess */) { itemDropInfo = EXTRA_INFO; };
    eventHub->SetOnItemDrop(onItemDrop);
    dragDropManager->preGridTargetFrameNode_ = frameNode;
    EXPECT_TRUE(dragDropManager->preGridTargetFrameNode_);
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    preGridTargetFrameNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetFrameNode);
}

/**
 * @tc.name: DragDropManagerTest013
 * @tc.desc: Test corner case
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest013, TestSize.Level1)
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
    DragPointerEvent point;
    TouchEvent event;
    event.x = 1.0f;
    event.y = 2.0f;
    dragDropManager->velocityTracker_.UpdateTouchPoint(event, false);
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::DROP, EXTRA_INFO);
    EXPECT_EQ(onDropInfo, EXTRA_INFO);

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
    dragDropManager->FireOnItemDropEvent(gridNode, DragType::GRID, itemDragInfo, 0, 0, true);
    EXPECT_EQ(onItemDropInfo, EXTRA_INFO);

    auto listNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    auto listEvent = listNode->GetEventHub<ListEventHub>();
    std::string onItemDropInfoList;
    ItemDropFunc onItemDropList = [&onItemDropInfoList](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                                      int32_t /* insertIndex */,
                                      bool /* isSuccess */) { onItemDropInfoList = EXTRA_INFO; };
    listEvent->SetOnItemDrop(std::move(onItemDropList));
    dragDropManager->FireOnItemDropEvent(listNode, DragType::LIST, itemDragInfo, 0, 0, true);
    EXPECT_EQ(onItemDropInfoList, EXTRA_INFO);
}

/**
 * @tc.name: DragDropManagerTest014
 * @tc.desc: Test OnTextDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call OnTextDragEnd.
     * @tc.expected: dragDropManager->currentId_ equals -1.
     */
    float globalX = 20.0f;
    float globalY = 20.0f;
    std::string extraInfo;
    dragDropManager->OnTextDragEnd(globalX, globalY, extraInfo);
    EXPECT_EQ(dragDropManager->currentId_, -1);

    /**
     * @tc.steps: step3. construct TextFrameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(GRID_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step4. updat edragDropManager->textFieldDragFrameNodes_ .
     */
    dragDropManager->textFieldDragFrameNodes_.insert(std::make_pair(100, WeakPtr<NG::FrameNode>(frameNode)));

    /**
     * @tc.steps: step5. call OnTextDragEnd.
     * @tc.expected: dragDropManager->currentId_ equals -1.
     */
    dragDropManager->OnTextDragEnd(globalX, globalY, extraInfo);
    auto dragFrameNode = dragDropManager->FindDragFrameNodeByPosition(globalX, globalY);
    EXPECT_EQ(dragDropManager->currentId_, -1);
}

/**
 * @tc.name: DragDropManagerTest015
 * @tc.desc: Test RestoreClipboardData
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call CancelItemDrag.
     * @tc.expected: dragDropManager->deleteDataCallback_ is not null.
     */
    dragDropManager->RestoreClipboardData();
    ASSERT_NE(dragDropManager->deleteDataCallback_, nullptr);

    /**
     * @tc.steps: step3. call CancelItemDrag(clipboard_ is null branch).
     * @tc.expected: step3. dragDropManager->deleteDataCallback_ is not null.
     */
    dragDropManager->clipboard_ = nullptr;
    dragDropManager->RestoreClipboardData();
    ASSERT_NE(dragDropManager->deleteDataCallback_, nullptr);

    /**
     * @tc.steps: step4. call CancelItemDrag(deleteDataCallback_ is not null branch).
     * @tc.expected: step4. dragDropManager->deleteDataCallback_ is not null.
     */
    auto callback = [weakManager = AceType::WeakClaim(AceType::RawPtr(dragDropManager))](const std::string& data) {
        auto dragDropManagerPtr = weakManager.Upgrade();
        ASSERT_NE(dragDropManagerPtr, nullptr);
        auto json = JsonUtil::ParseJsonString(data);
        if (json->Contains("preData")) {
            dragDropManagerPtr->clipboard_->SetData(json->GetString("preData"));
        }
    };
    dragDropManager->deleteDataCallback_ = callback;
    dragDropManager->RestoreClipboardData();
    ASSERT_NE(dragDropManager->deleteDataCallback_, nullptr);
}

/**
 * @tc.name: DragDropManagerTest017
 * @tc.desc: Test UpdateDragEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct a OHOS::Ace::DragEvent.
     * @tc.expected: event is not null.
     */
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);

    /**
     * @tc.steps: step3. call UpdateDragEvent.
     * @tc.expected: pipeline is not null.
     */
    dragDropManager->UpdateDragEvent(event, DragPointerEvent(1, 1));
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
}

/**
 * @tc.name: DragDropManagerTest021
 * @tc.desc: Test CreateTextDragDropProxy
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Call CreateTextDragDropProxy.
     * @tc.expected: CreateTextDragDropProxy the returns true value is not null.
     */
    auto textDragDropProxy = dragDropManager->CreateTextDragDropProxy();
    ASSERT_NE(textDragDropProxy, nullptr);
}

/**
 * @tc.name: DragDropManagerTest022
 * @tc.desc: Test FindDragFrameNodeByPosition in default branches
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest022, TestSize.Level1)
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
 * @tc.name: DragDropManagerTest023
 * @tc.desc: Test OnDragStart(Point)
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Call OnDragStart with Point.
     * @tc.expected: dragDropManager->dragDropState_ is equal to DragDropMgrState::DRAGGING.
     */
    dragDropManager->OnDragStart(Point(15.0f, 15.0f));
    EXPECT_EQ(dragDropManager->dragDropState_, DragDropMgrState::DRAGGING);

    /**
     * @tc.steps: step3. Call OnDragStart with Point and FrameNode.
     * @tc.expected: dragDropManager->dragDropState_ is equal to DragDropMgrState::DRAGGING.
     */
    RefPtr<FrameNode> frameNode = nullptr;
    dragDropManager->OnDragStart(Point(15.0f, 15.0f), frameNode);
    EXPECT_EQ(dragDropManager->dragDropState_, DragDropMgrState::DRAGGING);
}

/**
 * @tc.name: DragDropManagerTest024
 * @tc.desc: Test ClearVelocityInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Call ClearVelocityInfo.
     * @tc.expected: dragDropManager->velocityTracker_.isFirstPoint_ is equal to true.
     */
    dragDropManager->UpdateVelocityTrackerPoint(Point(15.0f, 15.0f), true);
    dragDropManager->ClearVelocityInfo();
    EXPECT_EQ(dragDropManager->velocityTracker_.isFirstPoint_, true);
}

/**
 * @tc.name: DragDropManagerTest025
 * @tc.desc: Test OnItemDragEnd out of eventHub is not an empty branche
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct a GridFrameNode.
     * @tc.expected: frameNode is not null.
     */
    auto gridFrameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    ASSERT_TRUE(gridFrameNode);

    /**
     * @tc.steps: step3. Call OnItemDragEnd with DRAG_TYPE_GRID.
     * @tc.expected: dragDropManager->draggedFrameNode_ is false.
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, gridFrameNode);
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    EXPECT_FALSE(dragDropManager->draggedFrameNode_);

    /**
     * @tc.steps: step4. construct a ListFrameNode.
     * @tc.expected: frameNode is not null.
     */
    auto listFrameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    ASSERT_TRUE(listFrameNode);

    /**
     * @tc.steps: step5. Call OnItemDragEnd with DRAG_TYPE_LIST.
     * @tc.expected: dragDropManager->draggedFrameNode_ is false.
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, listFrameNode);
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    EXPECT_FALSE(dragDropManager->draggedFrameNode_);
}

/**
 * @tc.name: DragDropManagerTest026
 * @tc.desc: Test GetExtraInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Call GetExtraInfo.
     * @tc.expected: extraInfo is empty.
     */
    auto extraInfo = dragDropManager->GetExtraInfo();
    EXPECT_TRUE(extraInfo.empty());
}

/**
 * @tc.name: DragDropManagerTest027
 * @tc.desc: Test SetExtraInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Call SetExtraInfo.
     * @tc.expected: dragDropManager->extraInfo_ is equal to "extraInfo".
     */
    dragDropManager->SetExtraInfo("extraInfo");
    EXPECT_EQ(dragDropManager->extraInfo_, "extraInfo");
}

/**
 * @tc.name: DragDropManagerTest028
 * @tc.desc: Test ClearExtraInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Call ClearExtraInfo.
     * @tc.expected: dragDropManager->extraInfo_ is empty.
     */
    dragDropManager->SetExtraInfo("extraInfo");
    dragDropManager->ClearExtraInfo();
    EXPECT_TRUE(dragDropManager->extraInfo_.empty());
}

/**
 * @tc.name: DragDropManagerTest029
 * @tc.desc: Test CancelItemDrag in draggedGridFrameNode branches
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call CancelItemDrag.
     * @tc.expected: dragDropManager->draggedGridFrameNode_ is false.
     */
    dragDropManager->CancelItemDrag();
    EXPECT_FALSE(dragDropManager->draggedGridFrameNode_);

    /**
     * @tc.steps: step3. Create FrameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step4. call CancelItemDrag.
     * @tc.expected: dragDropManager->draggedGridFrameNode_ is true.
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    dragDropManager->CancelItemDrag();
    EXPECT_TRUE(dragDropManager->draggedGridFrameNode_);
}

/**
 * @tc.name: DragDropManagerTest0291
 * @tc.desc: Test CancelItemDrag in listEventHub branches
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest0291, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Create FrameNode.
     * @tc.expected: listFrameNode is not null.
     */
    auto listFrameNode = AceType::MakeRefPtr<FrameNode>(LIST_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listFrameNode, nullptr);

    /**
     * @tc.steps: step3. update draggedGridFrameNode_ with listFrameNode.
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, listFrameNode);

    /**
     * @tc.steps: step4. call CancelItemDrag.
     * * @tc.expected: listEventHub is TRUE.
     */
    dragDropManager->CancelItemDrag();
    auto listEventHub = dragDropManager->draggedGridFrameNode_->GetEventHub<ListEventHub>();
    EXPECT_TRUE(listEventHub);
}

/**
 * @tc.name: DragDropManagerTest0292
 * @tc.desc: Test CancelItemDrag in gridEventHub branches
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest0292, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Create FrameNode.
     * @tc.expected: gridFrameNode is not null.
     */
    auto gridFrameNode = AceType::MakeRefPtr<FrameNode>(GRID_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    ASSERT_NE(gridFrameNode, nullptr);

    /**
     * @tc.steps: step3. update draggedGridFrameNode_ with gridFrameNode.
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, gridFrameNode);

    /**
     * @tc.steps: step4. call CancelItemDrag.
     * * @tc.expected: gridEventHub is TRUE.
     */
    dragDropManager->CancelItemDrag();
    auto gridEventHub = dragDropManager->draggedGridFrameNode_->GetEventHub<GridEventHub>();
    EXPECT_TRUE(gridEventHub);
}

/**
 * @tc.name: DragDropManagerTest030
 * @tc.desc: Test FireOnItemDragEvent in DragType::GRID branches
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Create FrameNode.
     * @tc.expected: gridFrameNode is not null.
     */
    auto gridFrameNode = AceType::MakeRefPtr<FrameNode>(GRID_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    ASSERT_NE(gridFrameNode, nullptr);

    /**
     * @tc.steps: step3. call FireOnItemDragEvent with DragEventType::ENTER.
     * * @tc.expected: eventHub is TRUE.
     */
    OHOS::Ace::ItemDragInfo itemDragInfo;
    dragDropManager->FireOnItemDragEvent(gridFrameNode, DragType::GRID, itemDragInfo, DragEventType::ENTER, 0, 0);
    auto eventHub = gridFrameNode->GetEventHub<GridEventHub>();
    EXPECT_TRUE(eventHub);

    /**
     * @tc.steps: step4. call FireOnItemDragEvent with DragEventType::MOVE.
     * * @tc.expected: eventHub is TRUE.
     */
    dragDropManager->FireOnItemDragEvent(gridFrameNode, DragType::GRID, itemDragInfo, DragEventType::MOVE, 0, 0);
    EXPECT_TRUE(eventHub);

    /**
     * @tc.steps: step5. call FireOnItemDragEvent with DragEventType::default.
     * * @tc.expected: eventHub is TRUE.
     */
    dragDropManager->FireOnItemDragEvent(gridFrameNode, DragType::GRID, itemDragInfo, DragEventType(10), 0, 0);
    EXPECT_TRUE(eventHub);
}

/**
 * @tc.name: DragDropManagerTest031
 * @tc.desc: Test FindTargetInChildNodes is an empty branch of parentNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call FindTargetInChildNodes(parentNode is empty).
     * @tc.expected: childFindResult is false.
     */
    RefPtr<UINode> customNode = nullptr;
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    auto childFindResult = dragDropManager->FindTargetInChildNodes(customNode, hitFrameNodes, true);
    EXPECT_FALSE(childFindResult);
}

/**
 * @tc.name: DragDropManagerTest033
 * @tc.desc: Test FindTargetInChildNodes
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest033, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<GridPattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(FRAME_SIZE);
    frameNodeNull->SetGeometryNode(geometryNode);
    auto pipelineTmp = NG::PipelineContext::GetCurrentContext();
    auto parentNodeTmp = pipelineTmp->GetRootElement();
    auto parentFrameNodeTmp = AceType::DynamicCast<FrameNode>(parentNodeTmp);
    parentFrameNodeTmp->frameChildren_.insert(WeakPtr<NG::FrameNode>(frameNodeNull));
    dragDropManager->AddGridDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    std::map<int32_t, WeakPtr<FrameNode>> frameNodes = dragDropManager->gridDragFrameNodes_;
    PointF point(GLOBAL_X, GLOBAL_Y);
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    for (auto iterOfFrameNode = frameNodes.begin(); iterOfFrameNode != frameNodes.end(); iterOfFrameNode++) {
        auto frameNode = iterOfFrameNode->second.Upgrade();
        auto geometryNode = frameNode->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }
        auto globalFrameRect = geometryNode->GetFrameRect();
        globalFrameRect.SetOffset(frameNode->GetTransformRelativeOffset());
        if (globalFrameRect.IsInRegion(point)) {
            hitFrameNodes.push_back(frameNode);
        }
    }
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetOverlayManager();
    auto parentNode = pipeline->GetRootElement();
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(parentNode);
    auto children = parentFrameNode->GetFrameChildren();
    EXPECT_FALSE(children.empty());
    for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
        auto child = iter->Upgrade();
        if (child == nullptr) {
            continue;
        }
        auto childNode = AceType::DynamicCast<UINode>(child);
        auto childFindResult = dragDropManager->FindTargetInChildNodes(childNode, hitFrameNodes, true);
        EXPECT_FALSE(childFindResult);
    }
    for (auto iter : hitFrameNodes) {
        EXPECT_NE(parentFrameNode, iter);
    }
    auto result = dragDropManager->FindTargetInChildNodes(parentNode, hitFrameNodes, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DragDropManagerTest034
 * @tc.desc: Test PrintDragFrameNode.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    OHOS::Ace::DragPointerEvent point;
    RefPtr<FrameNode> dragFrameNode = nullptr;
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, dragFrameNode);

    /**
     * @tc.steps: step2. call PrintDragFrameNode with dragFrameNode and point.
     * * @tc.expected: dragDropManager->draggedFrameNode_ is false.
     */
    dragDropManager->PrintDragFrameNode(point, dragFrameNode);
    ASSERT_FALSE(dragDropManager->draggedFrameNode_);
}

/**
 * @tc.name: DragDropManagerTest035
 * @tc.desc: Test FireOnItemDropEvent is empty branchs.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: step2. FireOnItemDropEvent.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto draggedNode = dragDropManager->draggedFrameNode_;
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    OHOS::Ace::ItemDragInfo itemDragInfo;

    /**
     * @tc.steps: step2. call OnDragStart with DragType::GRID and frameNode.
     * @tc.expected: step2. draggedNode is false.
     */
    dragDropManager->FireOnItemDropEvent(frameNode, DragType::GRID, itemDragInfo, 0, 0, true);
    ASSERT_FALSE(draggedNode);

    /**
     * @tc.steps: step2. call OnDragStart with DragType::LIST and frameNode.
     * @tc.expected: step2. raggedNode is false.
     */
    dragDropManager->FireOnItemDropEvent(frameNode, DragType::LIST, itemDragInfo, 0, 0, true);
    ASSERT_FALSE(draggedNode);
}

/**
 * @tc.name: DragDropManagerTest037
 * @tc.desc: Test GetItemIndex out of eventHub->CheckPostionInGrid is a true branch.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct a GeometryNode,updates MarginFrameOffset and FrameSize.
     * @tc.expected: geometryNode is not null.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetMarginFrameOffset(FRAME_OFFSET);
    geometryNode->SetFrameSize(FRAME_SIZE);

    /**
     * @tc.steps: step3. construct a FrameNode with GeometryNode.
     * @tc.expected: gridNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto gridNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<GridPattern>());
    ASSERT_NE(dragDropManager, nullptr);
    gridNode->SetGeometryNode(geometryNode);

    /**
     * @tc.steps: step4. construct a GridEventHub and updates OnItemDrop and AttachHost.
     */
    ItemDragInfo itemDragInfo;
    auto gridEvent = gridNode->GetEventHub<GridEventHub>();
    std::string onItemDropInfo;
    ItemDropFunc onItemDrop = [&onItemDropInfo](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */,
                                  int32_t /* insertIndex */, bool /* isSuccess */) { onItemDropInfo = EXTRA_INFO; };
    gridEvent->SetOnItemDrop(std::move(onItemDrop));
    gridEvent->AttachHost(WeakPtr<NG::FrameNode>(gridNode));

    /**
     * @tc.steps: step5. call GetItemIndex with DragEventType::GRID and gridNode.
     * @tc.expected: retFlag is true.
     */
    dragDropManager->draggedGridFrameNode_ = gridNode;
    dragDropManager->GetItemIndex(gridNode, DragType::GRID, 0, 0);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    gridNode->renderContext_ = mockRenderContext;
    mockRenderContext->rect_ = { 0.0f, 0.0f, 1.0f, 1.0f };
    bool retFlag = gridEvent->CheckPostionInGrid(0, 0);
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: DragDropManagerTest038
 * @tc.desc: Test GetItemIndex out of itemFrameNode is a true branch.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct a GeometryNode,updates MarginFrameOffset and FrameSize.
     * @tc.expected: geometryNode is not null.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetMarginFrameOffset(FRAME_OFFSET);
    geometryNode->SetFrameSize(FRAME_SIZE);

    /**
     * @tc.steps: step3. construct a FrameNode with GeometryNode.
     * @tc.expected: gridNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto gridNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<GridPattern>());
    ASSERT_NE(gridNode, nullptr);
    gridNode->SetGeometryNode(geometryNode);

    /**
     * @tc.steps: step4. construct a FrameNode.
     */
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, childId, AceType::MakeRefPtr<Pattern>());
    childNode->SetGeometryNode(geometryNode);
    childNode->isActive_ = true;

    /**
     * @tc.steps: step5. gridNode AddChild with childNode.
     */
    gridNode->AddChild(childNode);

    /**
     * @tc.steps: step6. call GetItemIndex with DragEventType::GRID and gridNode.
     * @tc.expected: retFlag is true.
     */
    dragDropManager->draggedGridFrameNode_ = gridNode;
    dragDropManager->GetItemIndex(gridNode, DragType::GRID, 0, 0);
    bool retFlag = gridNode->FindChildByPosition(0, 0);
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: DragDropManagerTest039
 * @tc.desc: Test CheckParentVisible out of parent is a true branch.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct a frameNode and update attributes.
     * IsVisible is false branch
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    frameNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE, true);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(true);

    /**
     * @tc.steps: step3. update nodesForDragNotify_.
     * @tc.expected: nodesForDragNotify_ is not empty.
     */
    dragDropManager->RegisterDragStatusListener(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
    EXPECT_FALSE(dragDropManager->nodesForDragNotify_.empty());

    /**
     * @tc.steps: step4. update NotifyDragEvent.
     * @tc.expected: notifyEvent attributes to be the set value.
     */
    RefPtr<NotifyDragEvent> notifyEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    dragDropManager->UpdateNotifyDragEvent(notifyEvent, Point(1.0f, 1.0f), DragEventType::START);
    EXPECT_DOUBLE_EQ(notifyEvent->GetX(), 1.0);
    EXPECT_DOUBLE_EQ(notifyEvent->GetY(), 1.0);

    /**
     * @tc.steps: step5. call NotifyDragRegisterFrameNode branches of CheckParentVisible out of isVisible.
     * @tc.expected: isVisible is false.
     */
    dragDropManager->NotifyDragRegisterFrameNode(
        dragDropManager->nodesForDragNotify_, DragEventType::START, notifyEvent);
    bool isVisible = frameNode->IsVisible();
    EXPECT_FALSE(isVisible);

    /**
     * @tc.steps: step6. update nodesForDragNotify_.
     * @tc.expected: nodesForDragNotify_ is not empty.
     */
    dragDropManager->UnRegisterDragStatusListener(frameNode->GetId());
    EXPECT_TRUE(dragDropManager->nodesForDragNotify_.empty());
    dragDropManager->RegisterDragStatusListener(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
    EXPECT_FALSE(dragDropManager->nodesForDragNotify_.empty());

    /**
     * @tc.steps: step7. update frameNode attribute.
     * @tc.expected: parent is not null.
     */
    auto customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE, true);
    frameNode->SetParent(WeakPtr<NG::UINode>(customNode));
    auto parent = frameNode->GetParent();
    EXPECT_TRUE(parent);
    parent->SetDepth(32);
    dragDropManager->UpdateNotifyDragEvent(notifyEvent, Point(1.0f, 1.0f), DragEventType::START);

    /**
     * @tc.steps: step8. call NotifyDragRegisterFrameNode branches of CheckParentVisible out of parentFrameNode.
     * @tc.expected: parent->GetDepth() returns a value that is not equal to 1.
     */
    dragDropManager->NotifyDragRegisterFrameNode(
        dragDropManager->nodesForDragNotify_, DragEventType::START, notifyEvent);
    EXPECT_NE(parent->GetDepth(), 1);
}

/**
 * @tc.name: DragDropManagerTest0391
 * @tc.desc: Test CheckParentVisible out of parentFrameNode  is a true branch.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest0391, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct a frameNode and update attributes.
     * IsVisible is false branch
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    auto customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    customNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE, true);
    frameNode->SetParent(WeakPtr<NG::UINode>(customNode));
    auto parent = frameNode->GetParent();
    EXPECT_TRUE(parent);
    parent->SetDepth(32);
    EXPECT_NE(parent->GetDepth(), 1);

    /**
     * @tc.steps: step4. update nodesForDragNotify_ and NotifyDragEvent.
     * @tc.expected: nodesForDragNotify_ is not empty.
     */
    RefPtr<NotifyDragEvent> notifyEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    dragDropManager->RegisterDragStatusListener(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
    EXPECT_FALSE(dragDropManager->nodesForDragNotify_.empty());
    dragDropManager->UpdateNotifyDragEvent(notifyEvent, Point(1.0f, 1.0f), DragEventType::START);

    /**
     * @tc.steps: step5. call NotifyDragRegisterFrameNode branches of CheckParentVisible out of parentFrameNode(is
     * false).
     * @tc.expected: customNode->IsVisible() returns a value that is not equal to false.
     */
    dragDropManager->NotifyDragRegisterFrameNode(
        dragDropManager->nodesForDragNotify_, DragEventType::START, notifyEvent);
    EXPECT_FALSE(customNode->IsVisible());
}

/**
 * @tc.name: DragDropManagerTest040
 * @tc.desc: Test FindHitFrameNodes in frameNode branchs
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest040, TestSize.Level1)
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
    frameNode->SetActive(true);
    frameNode->geometryNode_ = nullptr;
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_FALSE(geometryNode);

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

    /**
     * @tc.steps: step5. clear nodesForDragNotify_.
     */
    dragDropManager->UnRegisterDragStatusListener(frameNode->GetId());
    EXPECT_TRUE(dragDropManager->nodesForDragNotify_.empty());

    /**
     * @tc.steps: step6. updates frameNode and nodesForDragNotify_.
     */
    frameNode->SetActive(false);
    frameNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE, true);
    dragDropManager->RegisterDragStatusListener(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step7. call FindHitFrameNodes out of IsVisible are false branches.
     * @tc.expected: frameNodeList is empty.
     */
    frameNodeList = dragDropManager->FindHitFrameNodes(Point(1.0f, 1.0f));
    EXPECT_TRUE(frameNodeList.empty());
}

/**
 * @tc.name: DragDropManagerTest041
 * @tc.desc: Test SetDragDampStartPoint and GetDragDampStartPoint
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. create a point, than call SetDragDampStartPoint.
     * @tc.expected: The values of dragDampStartPoint_ and point are equal
     */
    Point point(1.0f, 1.0f);
    dragDropManager->SetDragDampStartPoint(point);
    EXPECT_EQ(dragDropManager->dragDampStartPoint_, point);

    /**
     * @tc.steps: step3. create a point, than call GetDragDampStartPoint.
     * @tc.expected: The return values of dragDampStartPoint_ and point are equal
     */
    Point point2(2.0f, 2.0f);
    dragDropManager->dragDampStartPoint_ = point2;
    auto returnPoint = dragDropManager->GetDragDampStartPoint();
    EXPECT_EQ(returnPoint, point2);
}

/**
 * @tc.name: DragDropManagerTest042
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. create a frameNode, then set preTargetFrameNode_.
     * @tc.expected: The values of preTargetFrameNode_ and frameNode are equal
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    dragDropManager->preTargetFrameNode_ = frameNode;
    ASSERT_EQ(dragDropManager->preTargetFrameNode_, frameNode);
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto instanceId = container->GetInstanceId();
    /**
     * @tc.steps: step3. call ResetPreTargetFrameNode in SceneBoardWindow.
     * @tc.expected: The value of preTargetFrameNode_ is frameNode
     */
    container->isUIExtensionWindow_ = false;
    container->isSceneBoardWindow_ = true;
    dragDropManager->ResetPreTargetFrameNode(instanceId);
    EXPECT_EQ(dragDropManager->preTargetFrameNode_, frameNode);

    /**
     * @tc.steps: step4. call ResetPreTargetFrameNode in UIExtensionWindow.
     * @tc.expected: The value of preTargetFrameNode_ is frameNode
     */
    container->isUIExtensionWindow_ = true;
    container->isSceneBoardWindow_ = false;
    dragDropManager->ResetPreTargetFrameNode(instanceId);
    EXPECT_EQ(dragDropManager->preTargetFrameNode_, frameNode);

    /**
     * @tc.steps: step5. call ResetPreTargetFrameNode.
     * @tc.expected: The value of preTargetFrameNode_ is nullptr
     */
    container->isUIExtensionWindow_ = false;
    container->isSceneBoardWindow_ = false;
    dragDropManager->ResetPreTargetFrameNode(instanceId);
    EXPECT_EQ(dragDropManager->preTargetFrameNode_, nullptr);
}

/**
 * @tc.name: CheckIsFolderSubwindowBoundary001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, CheckIsFolderSubwindowBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    bool result = dragDropManager->CheckIsFolderSubwindowBoundary(0.0f, 0.0f, 0);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleUIExtensionDragEvent001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, HandleUIExtensionDragEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    DragPointerEvent pointerEvent;
    DragEventType type = DragEventType::ENTER;
    dragDropManager->HandleUIExtensionDragEvent(frameNode, pointerEvent, type);
    EXPECT_NE(pointerEvent.action, PointerAction::PULL_IN_WINDOW);
}

/**
 * @tc.name: HandleUIExtensionDragEvent002
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, HandleUIExtensionDragEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    DragPointerEvent pointerEvent;
    DragEventType type = DragEventType::LEAVE;
    dragDropManager->HandleUIExtensionDragEvent(frameNode, pointerEvent, type);
    EXPECT_NE(pointerEvent.action, PointerAction::PULL_OUT_WINDOW);
}

/**
 * @tc.name: HandleUIExtensionDragEvent003
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, HandleUIExtensionDragEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    DragPointerEvent pointerEvent;
    DragEventType type =  DragEventType::PULL_CANCEL;
    dragDropManager->HandleUIExtensionDragEvent(frameNode, pointerEvent, type);
    EXPECT_NE(pointerEvent.action, PointerAction::PULL_CANCEL);
}

/**
 * @tc.name: CalculateScale001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, CalculateScale001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    float with = 100.0f;
    float height = 100.0f;
    float widthLimit = 50.0f;
    float heightLimit = 50.0f;
    auto scaleDataInfo = dragDropManager->CalculateScale(with, height, widthLimit, heightLimit);
    EXPECT_EQ(scaleDataInfo->isNeedScale, true);

    with = 100.0f;
    height = 50.0f;
    widthLimit = 50.0f;
    heightLimit = 50.0f;
    scaleDataInfo = dragDropManager->CalculateScale(with, height, widthLimit, heightLimit);
    EXPECT_EQ(scaleDataInfo->isNeedScale, true);

    with = 0.0f;
    height = 50.0f;
    widthLimit = 50.0f;
    heightLimit = 50.0f;
    scaleDataInfo = dragDropManager->CalculateScale(with, height, widthLimit, heightLimit);
    EXPECT_EQ(scaleDataInfo->isNeedScale, false);

    with = 50.0f;
    height = 0.0f;
    widthLimit = 50.0f;
    heightLimit = 50.0f;
    scaleDataInfo = dragDropManager->CalculateScale(with, height, widthLimit, heightLimit);
    EXPECT_EQ(scaleDataInfo->isNeedScale, false);
}

/**
 * @tc.name: NotifyPullEventListener001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, NotifyPullEventListener001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    DragPointerEvent pointerEvent;
    bool result = false;
    dragDropManager->NotifyPullEventListener(pointerEvent);
    EXPECT_EQ(result, false);

    std::function<void(const DragPointerEvent&)> testFunction;
    dragDropManager->pullEventListener_.insert({2, testFunction});
    dragDropManager->NotifyPullEventListener(pointerEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: UnRegisterPullEventListener001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, UnRegisterPullEventListener001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    const int32_t EXISTING_ID = 100;
    auto testListener = [](const DragPointerEvent&) {};
    dragDropManager->pullEventListener_.emplace(EXISTING_ID, testListener);
    ASSERT_EQ(dragDropManager->pullEventListener_.size(), 1);

    dragDropManager->UnRegisterPullEventListener(EXISTING_ID);
    EXPECT_EQ(dragDropManager->pullEventListener_.size(), 0);
}

/**
 * @tc.name: IsAnyDraggableHit001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, IsAnyDraggableHit001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    RefPtr<PipelineBase> pipeline = NG::MockPipelineContext::pipeline_;
    int32_t pointId = 100;
    dragDropManager->IsAnyDraggableHit(pipeline, pointId);
    EXPECT_EQ(dragDropManager->isAnyDraggableHit_, false);

    dragDropManager->isAnyDraggableHit_ = true;
    dragDropManager->IsAnyDraggableHit(pipeline, pointId);
    EXPECT_EQ(dragDropManager->isAnyDraggableHit_, true);
}

/**
 * @tc.name: IsAnyDraggableHit002
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC 245
 */
HWTEST_F(DragDropManagerTestNg, IsAnyDraggableHit002, TestSize.Level1)
{
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->OnRejected();
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    TouchTestResult touchTestResults = { clickRecognizer };
    RefPtr<PipelineBase> pipeline = NG::MockPipelineContext::pipeline_;
    pipeline->SetEventManager(AceType::MakeRefPtr<EventManager>());
    pipeline->eventManager_->touchTestResults_[100] = touchTestResults;
    int32_t pointId = 100;
    dragDropManager->IsAnyDraggableHit(pipeline, pointId);
    EXPECT_EQ(dragDropManager->isAnyDraggableHit_, false);
}

/**
 * @tc.name: IsAnyDraggableHit003
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, IsAnyDraggableHit003, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    TouchTestResult touchTestResults;
    RefPtr<PipelineBase> pipeline = NG::MockPipelineContext::pipeline_;
    pipeline->SetEventManager(AceType::MakeRefPtr<EventManager>());
    pipeline->eventManager_->touchTestResults_[100] = touchTestResults;
    int32_t pointId = 100;
    dragDropManager->IsAnyDraggableHit(pipeline, pointId);
    EXPECT_EQ(dragDropManager->isAnyDraggableHit_, false);
}

/**
 * @tc.name: RequireSummaryIfNecessary001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, RequireSummaryIfNecessary001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    DragPointerEvent pointerEvent;
    pointerEvent.pullId = 1;
    dragDropManager->RequireSummaryIfNecessary(pointerEvent);
    EXPECT_EQ(dragDropManager->currentPullId_, 1);

    DragPointerEvent pointerEvent1;
    pointerEvent1.pullId = -1;
    dragDropManager->RequireSummaryIfNecessary(pointerEvent);
    EXPECT_EQ(dragDropManager->currentPullId_, 1);
}

/**
 * @tc.name: DoDragMoveAnimate001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, DoDragMoveAnimate001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    DragPointerEvent pointerEvent;
    bool needDoDragMoveAnimate = false;
    dragDropManager->DoDragMoveAnimate(pointerEvent);
    EXPECT_EQ(needDoDragMoveAnimate, false);
}

/**
 * @tc.name: HandleSyncOnDragStart001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, HandleSyncOnDragStart001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    DragStartRequestStatus dragStartRequestStatus = DragStartRequestStatus::WAITING;
    dragDropManager->HandleSyncOnDragStart(dragStartRequestStatus);
    EXPECT_EQ(dragStartRequestStatus, DragStartRequestStatus::WAITING);

    bool callbackCalled = false;
    auto callback = [&callbackCalled]() { callbackCalled = true; };
    DragDropGlobalController::GetInstance().SetAsyncDragCallback(callback);

    dragStartRequestStatus = DragStartRequestStatus::READY;
    dragDropManager->HandleSyncOnDragStart(dragStartRequestStatus);
    EXPECT_EQ(dragStartRequestStatus, DragStartRequestStatus::READY);
}

/**
 * @tc.name: DoDragMoveAnimate002
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, DoDragMoveAnimate002, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    DragPointerEvent pointerEvent;
    bool needDoDragMoveAnimate = false;
    dragDropManager->isDragWithContextMenu_ = true;
    dragDropManager->isDragFwkShow_ = false;
    dragDropManager->info_.scale = 0.1f;
    Container::UpdateCurrent(MIN_SUBCONTAINER_ID);
    SubwindowManager::GetInstance()->AddParentContainerId(MIN_SUBCONTAINER_ID, 1);
    dragDropManager->info_.imageNode =  AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->DoDragMoveAnimate(pointerEvent);
    EXPECT_EQ(needDoDragMoveAnimate, false);
}

/**
 * @tc.name: HandleSyncOnDragStart002
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, HandleSyncOnDragStart002, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    DragDropGlobalController::GetInstance().SetDragStartRequestStatus(DragStartRequestStatus::READY);
    dragDropManager->HandleSyncOnDragStart(DragStartRequestStatus::WAITING);
    EXPECT_EQ(
        DragDropGlobalController::GetInstance().GetDragStartRequestStatus(),
        DragStartRequestStatus::WAITING);
    
    bool callbackCalled = false;
    auto callback = [&callbackCalled]() { callbackCalled = true; };
    DragDropGlobalController::GetInstance().SetAsyncDragCallback(callback);
    dragDropManager->HandleSyncOnDragStart(DragStartRequestStatus::READY);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(
        DragDropGlobalController::GetInstance().GetDragStartRequestStatus(),
        DragStartRequestStatus::READY);
  
    DragDropGlobalController::GetInstance().SetAsyncDragCallback(nullptr);
    DragDropGlobalController::GetInstance().SetDragStartRequestStatus(DragStartRequestStatus::WAITING);
    dragDropManager->HandleSyncOnDragStart(DragStartRequestStatus::READY);
    EXPECT_EQ(
        DragDropGlobalController::GetInstance().GetDragStartRequestStatus(),
        DragStartRequestStatus::WAITING);

    auto invalidStatus = static_cast<DragStartRequestStatus>(99);
    dragDropManager->HandleSyncOnDragStart(invalidStatus);
    EXPECT_EQ(
        DragDropGlobalController::GetInstance().GetDragStartRequestStatus(),
        DragStartRequestStatus::WAITING);
}

/**
 * @tc.name: GetWindowId001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, GetWindowId001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    int32_t result = dragDropManager->GetWindowId();
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: ResetDraggingStatus001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, ResetDraggingStatus001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    TouchEvent touchPoint;
  
    touchPoint.id = 1;
    dragDropManager->currentPointerId_ = 1;
    dragDropManager->draggingPressedState_ = true;
    dragDropManager->ResetDraggingStatus(touchPoint);

    dragDropManager->dragDropState_ = DragDropMgrState::DRAGGING;
    auto draggedGridFrameNode_ = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->ResetDraggingStatus(touchPoint);
    EXPECT_EQ(dragDropManager->currentPointerId_, 1);
}

/**
 * @tc.name: ResetDraggingStatus002
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, ResetDraggingStatus002, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    TouchEvent touchPoint;
    touchPoint.type = TouchType::CANCEL;
    dragDropManager->ResetDraggingStatus(touchPoint);
    EXPECT_EQ(dragDropManager->dragDropState_, DragDropMgrState::IDLE);
}

/**
 * @tc.name: HandleOnDragEnd001
 * @tc.desc: ResetPreTargetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DragDropManagerTestNg, HandleOnDragEnd001, TestSize.Level1)
{
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);
    DragPointerEvent pointerEvent;
    string extraInfo = "Test";
    auto dragFrameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->HandleOnDragEnd(pointerEvent, extraInfo, dragFrameNode);
    EXPECT_FALSE(dragDropManager->IsDragging());
}
} // namespace OHOS::Ace::NG
