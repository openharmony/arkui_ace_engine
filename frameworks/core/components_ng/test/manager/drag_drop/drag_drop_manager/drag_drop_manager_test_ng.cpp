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

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "frameworks/core/components_ng/pattern/pattern.h"

#define private public
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_ETS_TAG("root");
const std::string GRID_TAG("grid");
const std::string NODE_TAG("custom_node");
constexpr int32_t GLOBAL_X = 10;
constexpr int32_t GLOBAL_Y = 20;
const std::string EXTRA_INFO("extra info");
const std::string EXTRA_INFO_2("extra info 2");
const std::string EXTRA_INFO_LEAVE("extra info LEAVE");
const std::string EXTRA_INFO_MOVE("extra info MOVE");
const std::string EXTRA_INFO_ENTER("extra info ENTER");
const std::string ITEM_INFO_LEAVE("item info LEAVE");
constexpr int32_t INVALID_CURRENT_ID = -1;
// before testing CheckDragDropProxy, DragWindow has created 6 times
constexpr int32_t VALID_CURRENT_ID = 6;
const OffsetF FRAME_OFFSET(0.0f, 0.0f);
const SizeF FRAME_SIZE(GLOBAL_X * 10.0f, GLOBAL_Y * 10.0f);
constexpr int32_t DRAGGED_INDEX = 0;
const DragType DRAG_TYPE_GRID = DragType::GRID;
} // namespace

class DragDropManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

protected:
};

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
     *                      DragWindow.DrawPixelMap() will be called with printing a log
     *                      it's defined in "components_ng/test/mock/drag_window/mock_drag_window.cpp"
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    GestureEvent gestureEvent;
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(pixelMap, gestureEvent);
    EXPECT_TRUE(dragDropProxy);
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
     *                      DragWindow.DrawFrameNode() will be called with printing a log
     *                      it's defined in "components_ng/test/mock/drag_window/mock_drag_window.cpp"
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent gestureEvent;
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
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
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step3. call UpdateDragWindowPosition
     * @tc.expected: step3. DragWindow.MoveTo() will be called with printing a log
     *                      it's defined in "components_ng/test/mock/drag_window/mock_drag_window.cpp"
     */
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
     * @tc.steps: step5. call RestoreClipboardData with no deleteCallback
     * @tc.expected: step5. restore the ClipboardData extraInfo is ""
     *                      ClipBoard.SetData() & ClipBoard.GetData() will be called with printing logs
     *                      they're defined in "components_ng/test/mock/clipboard/mock_clipboard.cpp"
     */
    dragDropManager->RestoreClipboardData();
    dragDropManager->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, "");
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
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step3. call AddDataToClipboard twice
     *                   case: clipboard_ & addDataCallback_ has exited,
     * @tc.expected: step3. EXTRA_INFO_2 will not be added
     */
    dragDropManager->AddDataToClipboard(EXTRA_INFO);
    dragDropManager->AddDataToClipboard(EXTRA_INFO_2);
    std::string extraInfo;
    dragDropManager->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, EXTRA_INFO);

    /**
     * @tc.steps: step4. call GetExtraInfoFromClipboard twice
     *                   case: clipboard_ & addDataCallback_ has exited
     * @tc.expected: step4. get the extraInfo successfully
     */
    dragDropManager->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, EXTRA_INFO);

    /**
     * @tc.steps: step5. call RestoreClipboardData twice
     *                   case: deleteDataCallback_ has exited
     * @tc.expected: step5. restore the ClipboardData, extraInfo is ""
     */
    dragDropManager->RestoreClipboardData();
    dragDropManager->RestoreClipboardData();
    dragDropManager->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, "");

    /**
     * @tc.steps: step6. construct a new DragDropManager and call GetExtraInfoFromClipboard
     *                   case: clipboard_ is null
     * @tc.expected: step6. extraInfo is ""
     */
    auto dragDropManager2 = AceType::MakeRefPtr<DragDropManager>();
    dragDropManager2->GetExtraInfoFromClipboard(extraInfo);
    EXPECT_EQ(extraInfo, "");

    /**
     * @tc.steps: step7. construct a new DragDropManager and call RestoreClipboardData
     *                   case: clipboard_ is null
     * @tc.expected: step7. restore the ClipboardData, extraInfo is ""
     */
    auto dragDropManager3 = AceType::MakeRefPtr<DragDropManager>();
    dragDropManager3->RestoreClipboardData();
    EXPECT_EQ(extraInfo, "");
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
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);
    flag = dragDropManager->CheckDragDropProxy(VALID_CURRENT_ID);
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step5. call CheckDragDropProxy after creating dragWindow
     * @tc.expected: step5. currentId recover to -1
     *                      MockDragWindow.Destroy() will be called with printing a log
     *                      it's defined in "components_ng/test/mock/drag_window/mock_drag_window.cpp"
     */
    dragDropManager->DestroyDragWindow();
    flag = dragDropManager->CheckDragDropProxy(INVALID_CURRENT_ID);
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
    dragDropManager->OnDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
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
 * @tc.name: DragDropManagerTest008
 * @tc.desc: Test OnDragMove
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
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. call OnDragMove
     *                   case: dragFrameNodes_ is empty & preTargetFrameNode_ is null
     * @tc.expected: step2. DragWindow.MoveTo() will be called with printing a log
     */
    dragDropManager->OnDragMove(GLOBAL_X, GLOBAL_Y, EXTRA_INFO);

    /**
     * @tc.steps: step3. construct a frameNode and set its DragEvent and GeometryNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_TRUE(eventHub);

    // Set OnDragLeave callback
    std::string leaveExtraInfo;
    auto onDragLeave = [&leaveExtraInfo](const RefPtr<OHOS::Ace::DragEvent>& /* info */,
                           const std::string& extraParams) { leaveExtraInfo = extraParams; };
    eventHub->SetOnDragLeave(std::move(onDragLeave));

    // Set OnDragMove callback
    std::string moveExtraInfo;
    auto onDragMove = [&moveExtraInfo](const RefPtr<OHOS::Ace::DragEvent>& /* info */, const std::string& extraParams) {
        moveExtraInfo = extraParams;
    };
    eventHub->SetOnDragMove(std::move(onDragMove));

    // Set OnDragEnter callback
    std::string enterExtraInfo;
    auto onDragEnter = [&enterExtraInfo](const RefPtr<OHOS::Ace::DragEvent>& /* info */,
                           const std::string& extraParams) { enterExtraInfo = extraParams; };
    eventHub->SetOnDragEnter(std::move(onDragEnter));

    // Set geometry node to make sure (GLOBAL_X, GLOBAL_Y) in geoNode.frameRect_
    auto geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetMarginFrameOffset(FRAME_OFFSET);
    geoNode->SetFrameSize(FRAME_SIZE);
    frameNode->SetGeometryNode(geoNode);

    /**
     * @tc.steps: step4. call OnDragMove
     *                   case: dragFrameNodes_ is empty & preTargetFrameNode_ is not null
     * @tc.expected: step4. frameNode's onDragLeave_ will be called
     *                      leaveExtraInfo will be assigned to EXTRA_INFO_LEAVE and preTargetFrameNode_ will be assigned
     * to null DragWindow.MoveTo() will be called with printing a log
     */
    dragDropManager->OnDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    dragDropManager->OnDragMove(GLOBAL_X, GLOBAL_Y, EXTRA_INFO_LEAVE);
    EXPECT_EQ(leaveExtraInfo, EXTRA_INFO_LEAVE);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    EXPECT_FALSE(preTargetNode);

    /**
     * @tc.steps: step5. call AddDragFrameNode
     *                   after that, dragFrameNodes_ is not empty
     */
    dragDropManager->AddDragFrameNode(frameNode);

    /**
     * @tc.steps: step5. call OnDragMove
     *                   case: dragFrameNodes_ is not empty & preTargetFrameNode_ equals the frameNode
     * @tc.expected: step5. frameNode's onDragMove_ will be called
     *                      moveExtraInfo will be assigned to EXTRA_INFO_MOVE
     *                      DragWindow.MoveTo() will be called with printing a log
     */
    dragDropManager->OnDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    EXPECT_TRUE(preTargetNode);
    dragDropManager->OnDragMove(GLOBAL_X, GLOBAL_Y, EXTRA_INFO_MOVE);
    EXPECT_EQ(moveExtraInfo, EXTRA_INFO_MOVE);

    /**
     * @tc.steps: step6. call OnDragMove
     *                   case: dragFrameNodes_ is not empty & preTargetFrameNode_ not equals the frameNode
     * @tc.expected: step6. frameNode's onDragEnter_ will be called
     *                      enterExtraInfo will be assigned to EXTRA_INFO_ENTER
     *                      preTargetFrameNode_'s onDragLeave will be called
     *                      leaveExtraInfoNew will be assigned to EXTRA_INFO_ENTER
     *                      preTargetFrameNode_ is assigned to frameNode
     *                      DragWindow.MoveTo() will be called with printing a log
     */
    auto newFrameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart(GLOBAL_X, GLOBAL_Y, newFrameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    EXPECT_TRUE(preTargetNode);
    // Set newFrameNode's onDragLeave callback
    auto eventHubNew = newFrameNode->GetEventHub<EventHub>();
    ASSERT_TRUE(eventHubNew);
    std::string leaveExtraInfoNew;
    auto onDragLeaveNew = [&leaveExtraInfoNew](const RefPtr<OHOS::Ace::DragEvent>& /* info */,
                              const std::string& extraParams) { leaveExtraInfoNew = extraParams; };
    eventHubNew->SetOnDragLeave(std::move(onDragLeaveNew));
    dragDropManager->OnDragMove(GLOBAL_X, GLOBAL_Y, EXTRA_INFO_ENTER);
    EXPECT_EQ(enterExtraInfo, EXTRA_INFO_ENTER);
    EXPECT_EQ(leaveExtraInfoNew, EXTRA_INFO_ENTER);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    auto preTargetNodeTag = preTargetNode->GetTag();
    EXPECT_EQ(preTargetNodeTag, NODE_TAG);

    /**
     * @tc.steps: step7. call OnDragMove
     *                   case: dragFrameNodes_ is not empty & preTargetFrameNode_ is null
     * @tc.expected: step7. frameNode's onDragEnter_ will be called
     *                      enterExtraInfo will be assigned to EXTRA_INFO_ENTER
     *                      preTargetFrameNode_ is assigned to frameNode
     *                      DragWindow.MoveTo() will be called with printing a log
     */
    dragDropManager->onDragCancel();
    preTargetNode = dragDropManager->preTargetFrameNode_;
    EXPECT_FALSE(preTargetNode);
    enterExtraInfo = "";
    dragDropManager->OnDragMove(GLOBAL_X, GLOBAL_Y, EXTRA_INFO_ENTER);
    EXPECT_EQ(enterExtraInfo, EXTRA_INFO_ENTER);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    preTargetNodeTag = preTargetNode->GetTag();
    EXPECT_EQ(preTargetNodeTag, NODE_TAG);
}

/**
 * @tc.name: DragDropManagerTest009
 * @tc.desc: Test OnItemDragMove DragType is Grid
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
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. call OnItemDragMove
     *                   case: gridDragFrameNodes_ is empty & preTargetFrameNode_ is null
     * @tc.expected: step2. DragWindow.MoveTo() will be called with printing a log
     */
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);

    /**
     * @tc.steps: step3. construct a frameNode whose tag is Grid set its ItemDragEvent and GeometryNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(GRID_TAG, -1, AceType::MakeRefPtr<GridPattern>());
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    ASSERT_TRUE(eventHub);
    std::string itemInfoLeave;
    auto onItemDragLeave = [&itemInfoLeave](const ItemDragInfo& /* dragInfo */, int32_t /* itemIndex */) {
        itemInfoLeave = ITEM_INFO_LEAVE;
    };
    eventHub->SetOnItemDragLeave(onItemDragLeave);

    /**
     * @tc.steps: step4. call OnItemDragMove
     *                   case: dragFrameNodes_ is empty & preGridTargetFrameNode_ is not null
     * @tc.expected: step4. frameNode's onItemDragLeave_ will be called
     *                      itemInfoLeave will be assigned to ITEM_INFO_LEAVE
     *                      and preGridTargetFrameNode_ will be assigned to null
     *                      DragWindow.MoveTo() will be called with printing a log
     */
    dragDropManager->OnItemDragStart(GLOBAL_X, GLOBAL_Y, frameNode);
    auto preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    ASSERT_TRUE(preGridTargetNode);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    EXPECT_EQ(itemInfoLeave, ITEM_INFO_LEAVE);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetNode);
}
} // namespace OHOS::Ace::NG
