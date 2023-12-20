/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#define private public
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "test/mock/base/mock_drag_window.h"
#include "test/mock/core/common/mock_interaction_interface.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/pipeline/base/render_node.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_ETS_TAG("root");
const std::string GRID_TAG("grid");
const std::string LIST_TAG("list");
const std::string NODE_TAG("custom_node");
const std::string NODE_TAG_EX("custom_node_ex");
const std::string NODE_TAG_EX2("custom_node_ex2");
constexpr int32_t GLOBAL_X = 10;
constexpr int32_t GLOBAL_Y = 20;
const std::string EXTRA_INFO("extra info");
const std::string EXTRA_INFO_2("extra info 2");
const std::string EXTRA_INFO_LEAVE("extra info LEAVE");
const std::string EXTRA_INFO_MOVE("extra info MOVE");
const std::string EXTRA_INFO_ENTER("extra info ENTER");
const std::string ITEM_INFO_LEAVE("item info LEAVE");
const std::string ITEM_INFO_MOVE("item info MOVE");
const std::string ITEM_INFO_ENTER("item info ENTER");
constexpr int32_t INVALID_CURRENT_ID = -1;
// before testing CheckDragDropProxy, DragWindow has created 6 times
constexpr int32_t VALID_CURRENT_ID = 6;
const OffsetF FRAME_OFFSET(0.0f, 0.0f);
const SizeF FRAME_SIZE(GLOBAL_X * 10.0f, GLOBAL_Y * 10.0f);
constexpr int32_t DRAGGED_INDEX = 0;
const DragType DRAG_TYPE_GRID = DragType::GRID;
const DragType DRAG_TYPE_LIST = DragType::LIST;
RefPtr<DragWindow> MOCK_DRAG_WINDOW;
} // namespace

class DragDropManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DragDropManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
}

void DragDropManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MOCK_DRAG_WINDOW = nullptr;
}

/**
 * @tc.name: DragDropManagerTest001
 * @tc.desc: CreateAndShowDragWindow via pixelMap and gestureEvent
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
     * @tc.steps: step2. call CreateAndShowDragWindow
     * @tc.expected: step2. return a dragDropProxy successfully
     *                      DragWindow.DrawPixelMap() will be called
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawPixelMap(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(pixelMap, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step3. call CreateAndShowDragWindow with null.
     * @tc.expected: step3. return dragDropProxy to false.
     */
    pixelMap = nullptr;
    dragDropProxy = dragDropManager->CreateAndShowDragWindow(pixelMap, gestureEvent);
    EXPECT_FALSE(dragDropProxy);
}

/**
 * @tc.name: DragDropManagerTest002
 * @tc.desc: CreateAndShowDragWindow via customNode and gestureEvent
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
     * @tc.steps: step2. call CreateAndShowDragWindow
     * @tc.expected: step2. return a dragDropProxy successfully
     *                      DragWindow.DrawFrameNode() will be called
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.expected: step2. the customNode's parent is root
     */
    auto root = customNode->GetParent();
    auto rootTag = root->GetTag();
    EXPECT_EQ(rootTag, ROOT_ETS_TAG);

    /**
     * @tc.steps: step3. call CreateAndShowDragWindow again
     * @tc.expected: step3. return nullptr because dragWindow_ has existed
     */
    RefPtr<UINode> customNode2 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent2;
    auto dragDropProxyNull = dragDropManager->CreateAndShowDragWindow(customNode2, gestureEvent2);
    EXPECT_FALSE(dragDropProxyNull);
}

/**
 * @tc.name: DragDropManagerTest003
 * @tc.desc: Test UpdateDragWindowPosition
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
     * @tc.steps: step2. call CreateAndShowDragWindow
     * @tc.expected: step2. return a dragDropProxy successfully
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step3. call UpdateDragWindowPosition
     * @tc.expected: step3. DragWindow.MoveTo() will be called
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->UpdateDragWindowPosition(GLOBAL_X, GLOBAL_Y);
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
     * @tc.steps: step2. call CreateAndShowDragWindow
     * @tc.expected: step2. return a dragDropProxy successfully
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
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

    /**
     * @tc.steps: step5. call GetExtraInfoFromClipboard
     * @tc.expected: step5. extraInfo is equal to EXTRA_INFO
     */
    dragDropManager->clipboard_ = nullptr;
    dragDropManager->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, EXTRA_INFO);

    /**
     * @tc.steps: step6. call AddDataToClipboard with empty.
     * @tc.expected: step6. extraInfo is equal to EXTRA_INFO
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
     * @tc.steps: step2. call CreateAndShowDragWindow
     * @tc.expected: step2. return a dragDropProxy successfully
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

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
     * @tc.steps: step4. call CreateAndShowDragWindow
     * @tc.expected: step4. return a dragDropProxy successfully
     *                      currentId has incremented by 1 to 1
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);
    flag = dragDropManager->CheckDragDropProxy(VALID_CURRENT_ID);
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step5. call CheckDragDropProxy after creating dragWindow
     * @tc.expected: step5. currentId recover to -1
     *                      MockDragWindow.Destroy() will be called
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), Destroy()).Times(1);
    dragDropManager->DestroyDragWindow();
    flag = dragDropManager->CheckDragDropProxy(INVALID_CURRENT_ID);
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step6. call CheckDragDropProxy when dragWindowRootNode_ is null (use proxy to create drag window)
     * @tc.expected: step6. currentId recover to -1
     *                      MockDragWindow.Destroy() will be called
     */
    auto dragDropManager2 = AceType::MakeRefPtr<DragDropManager>();
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    GestureEvent gestureEvent2;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawPixelMap(_)).Times(1);
    auto dragDropProxy2 = dragDropManager2->CreateAndShowDragWindow(pixelMap, gestureEvent2);
    EXPECT_TRUE(dragDropProxy2);
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager2->dragWindow_)), Destroy()).Times(1);
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
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. call OnItemDragMove
     *                   case: gridDragFrameNodes_ is empty & preTargetFrameNode_ is null
     * @tc.expected: step2. DragWindow.MoveTo() will be called
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);

    /**
     * @tc.steps: step3. construct a frameNode whose tag is Grid set its ItemDragEvent and GeometryNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(GRID_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
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
     * @tc.steps: step4. call OnItemDragMove
     *                   case: gridDragFrameNodes_ is empty & preGridTargetFrameNode_ is not null
     * @tc.expected: step4. frameNode's onItemDragLeave_ will be called
     *                      itemInfoLeave will be assigned to ITEM_INFO_LEAVE
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    auto preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    ASSERT_TRUE(preGridTargetNode);
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
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
     *                      DragWindow.MoveTo() will be called
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_TRUE(preGridTargetNode);
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);

    /**
     * @tc.steps: step7. call OnItemDragMove
     *                   case: gridDragFrameNodes_ is not empty & preGridTargetFrameNode_ not equals the frameNode
     * @tc.expected: step7. frameNode's onDragItemEnter_ will be called
     *                      itemInfoEnter will be assigned to ITEM_INFO_ENTER
     *                      preGridTargetFrameNode_'s onDragItemLeave will be called
     *                      leaveExtraInfoNew will be assigned to ITEM_INFO_ENTER
     *                      preGridTargetFrameNode_ is assigned to frameNode
     *                      DragWindow.MoveTo() will be called
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
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
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
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. call OnItemDragMove
     *                   case: listDragFrameNodes_ is empty & preTargetFrameNode_ is null
     * @tc.expected: step2. DragWindow.MoveTo() will be called
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);

    /**
     * @tc.steps: step3. construct a frameNode whose tag is List set its ItemDragEvent and GeometryNode
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
     * @tc.steps: step4. call OnItemDragMove
     *                   case: listDragFrameNodes_ is empty & preGridTargetFrameNode_ is not null
     * @tc.expected: step4. frameNode's onItemDragLeave_ will be called
     *                      itemInfoLeave will be assigned to ITEM_INFO_LEAVE
     *                      DragWindow.MoveTo() will be called
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    auto preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    ASSERT_TRUE(preGridTargetNode);
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(2);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    EXPECT_EQ(itemInfoLeave, ITEM_INFO_LEAVE);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetNode);

    /**
     * @tc.steps: step5. call AddGridDragFrameNode
     *                   after that, listDragFrameNodes_ is not empty
     *                   need adding grid maybe a bug
     */
    dragDropManager->AddGridDragFrameNode(frameNode->GetId(), frameNode);

    /**
     * @tc.steps: step6. call OnItemDragMove
     *                   case: listDragFrameNodes_ is not empty & preGridTargetFrameNode_ equals the frameNode
     * @tc.expected: step6. a gridEventHub is trying to get by the frameNode,
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
     * @tc.steps: step7. call OnItemDragMove
     *                   case: listDragFrameNodes_ is not empty & preGridTargetFrameNode_ not equals the frameNode
     * @tc.expected: step7. frameNode's onDragItemEnter_ will be called
     *                      itemInfoEnter will be assigned to ITEM_INFO_ENTER
     *                      preGridTargetFrameNode_'s onDragItemLeave will be called
     *                      leaveExtraInfoNew will be assigned to ITEM_INFO_ENTER
     *                      preGridTargetFrameNode_ is assigned to frameNode
     *                      DragWindow.MoveTo() will be called
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
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(0);
    EXPECT_EQ(itemInfoEnter, "");
    EXPECT_EQ(itemInfoLeaveNew, "");
    ASSERT_TRUE(dragDropManager->preGridTargetFrameNode_);
    auto preGridTargetNodeTag = dragDropManager->preGridTargetFrameNode_->GetTag();
    EXPECT_EQ(preGridTargetNodeTag, LIST_TAG);

    /**
     * @tc.steps: step8. call OnItemDragMove
     *                   case: listDragFrameNodes_ is not empty & preGridTargetFrameNode_ is null
     * @tc.expected: step8. frameNode's onDragItemEnter_ will be called
     *                      itemInfoEnter will be assigned to ITEM_INFO_ENTER
     *                      DragWindow.MoveTo() will be called
     */
    dragDropManager->onItemDragCancel();
    EXPECT_FALSE(dragDropManager->preGridTargetFrameNode_);
    itemInfoEnter = "";
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
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
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

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
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

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
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId,
        AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    EXPECT_EQ(static_cast<int32_t>(dragDropManager->dragFrameNodes_.size()), 2);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y, DragType::COMMON, false);
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
    Point point;
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
    EXPECT_EQ(onItemDropInfo, "");

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
    auto dragFrameNode = dragDropManager->FindDragFrameNodeByPosition(globalX, globalY, DragType::TEXT, true);
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
    dragDropManager->UpdateDragEvent(event, Point(1.0f, 1.0f));
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
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

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
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y, DragType(10), false);
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

    Point point;
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
 * @tc.name: DragDropManagerTest036
 * @tc.desc: Test FireOnDragEvent is empty branchsPoint.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. call FireOnDragEvent with DragEventType::ENTER and frameNode.
     * @tc.expected: step2. FireOnItemDropEvent.
     */
    Point point;
    std::string extraInfo;
    dragDropManager->extraInfo_ = EXTRA_INFO;
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::ENTER, extraInfo);
    EXPECT_TRUE(extraInfo.empty());
    
    /**
     * @tc.steps: step3. call FireOnDragEvent with DragEventType::ENTER and frameNode.
     * @tc.expected: step3. frameNode->GetEventHub<EventHub>() returns.
     */
    frameNode->eventHub_ = nullptr;
    dragDropManager->FireOnDragEvent(frameNode, point, DragEventType::ENTER, extraInfo);
    EXPECT_FALSE(frameNode->GetEventHub<EventHub>());
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
 * @tc.desc: Test FindHitFrameNodes in frameNode branchs(IsActive is false)
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFindDragFrameNodeByPositionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId,
        AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    EXPECT_EQ(static_cast<int32_t>(dragDropManager->dragFrameNodes_.size()), 2);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y, DragType::TEXT, false);
    EXPECT_FALSE(targetFrameNode);
}

/**
 * @tc.name: DragDropManagerPrintDragFrameNodeTest001
 * @tc.desc: Test PrintDragFrameNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerPrintDragFrameNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    Point point;

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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFindTargetInChildNodesTest001, TestSize.Level1)
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFindTargetInChildNodesTest002, TestSize.Level1)
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFindTargetInChildNodesTest003, TestSize.Level1)
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFindTargetInChildNodesTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode1 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode2 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode3 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    std::list<RefPtr<UINode>> child = {customNode1, customNode2, customNode2, nullptr};

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
    std::vector<RefPtr<FrameNode>> hitFrameNodes = {frameNode, frameNode2};
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFindTargetInChildNodesTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode1 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode2 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode3 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    std::list<RefPtr<UINode>> child = {customNode1, customNode2, customNode2, nullptr};

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

    std::vector<RefPtr<FrameNode>> hitFrameNodes = {frameNode, frameNode2, frameNode4, frameNode5};
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFindTargetInChildNodesTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode1 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode2 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<UINode> customNode3 = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    std::list<RefPtr<UINode>> child = {customNode1, customNode2, customNode2, nullptr};

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

    std::vector<RefPtr<FrameNode>> hitFrameNodes = {parentFrameNode};
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerOnDragMoveTest001, TestSize.Level1)
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFireOnDragEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId,
        AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    EXPECT_EQ(static_cast<int32_t>(dragDropManager->dragFrameNodes_.size()), 2);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y, DragType::COMMON, false);
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
    Point point;
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFireOnItemDragEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId,
        AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    EXPECT_EQ(static_cast<int32_t>(dragDropManager->dragFrameNodes_.size()), 2);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y, DragType::COMMON, false);
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
    Point point;
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerOnItemDragEndTest001, TestSize.Level1)
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFireOnItemDragEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId,
        AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    EXPECT_EQ(static_cast<int32_t>(dragDropManager->dragFrameNodes_.size()), 2);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y, DragType::COMMON, false);
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFireOnItemDragEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);

    /**
     * @tc.steps: step2. call OnItemDragMove
     *                   case: listDragFrameNodes_ is empty & preTargetFrameNode_ is null
     * @tc.expected: step2. DragWindow.MoveTo() will be called
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);

    /**
     * @tc.steps: step3. construct a frameNode whose tag is List set its ItemDragEvent and GeometryNode
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
     * @tc.steps: step4. call OnItemDragMove
     *                   case: listDragFrameNodes_ is empty & preGridTargetFrameNode_ is not null
     * @tc.expected: step4. frameNode's onItemDragLeave_ will be called
     *                      itemInfoLeave will be assigned to ITEM_INFO_LEAVE
     *                      DragWindow.MoveTo() will be called
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    auto preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(2);
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFireOnItemDropEventTest001, TestSize.Level1)
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerGetItemIndexTest001, TestSize.Level1)
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerGetItemIndexTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId,
        AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y, DragType::COMMON, false);
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
    Point point;
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerGetItemIndexTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager and create a DragWindow
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);

    /**
     * @tc.steps: step2. call FindDragFrameNodeByPosition with frameNodes contains nullptr
     * @tc.expected: step2.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull->GetId(), frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNodeGeoNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, frameNodeGeoNullId,
        AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull->GetId(), frameNodeGeoNull);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y, DragType::COMMON, false);

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
    Point point;
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerFireOnEditableTextComponent, TestSize.Level1)
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
        EXPECT_CALL(*(AceType::DynamicCast<MockInteractionInterface>(
            MockInteractionInterface::GetInstance())), EnterTextEditorArea(_))
            .Times(1).WillOnce(::testing::Return(0));
#else
        EXPECT_CALL(*(AceType::DynamicCast<MockInteractionInterface>(
            MockInteractionInterface::GetInstance())), EnterTextEditorArea(_))
            .Times(0);
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerClearVelocityInfoTest001, TestSize.Level1)
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerClearExtraInfoTest001, TestSize.Level1)
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
HWTEST_F(DragDropManagerTestNg, DragDropManagerSetExtraInfoTest001, TestSize.Level1)
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
HWTEST_F(DragDropManagerTestNg, DragDropProxyOnDragEndTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call CreateAndShowDragWindow
     * @tc.expected: step2. return a dragDropProxy successfully
     *                      DragWindow.DrawPixelMap() will be called
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawPixelMap(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(pixelMap, gestureEvent);
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
HWTEST_F(DragDropManagerTestNg, DragDropProxyDestroyDragWindowTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call CreateAndShowDragWindow
     * @tc.expected: step2. return a dragDropProxy successfully
     *                      DragWindow.DrawPixelMap() will be called
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawPixelMap(_)).Times(1);

    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(pixelMap, gestureEvent);
    dragDropProxy->DestroyDragWindow();
    EXPECT_TRUE(dragDropProxy);
}

/**
 * @tc.name: DragDropProxyOnDragEndTest003
 * @tc.desc: OnDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropProxyOnDragEndTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();

    /**
     * @tc.steps: step2. call CreateAndShowDragWindow
     * @tc.expected: step2. return a dragDropProxy successfully
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
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
} // namespace OHOS::Ace::NG
