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
#include "base/test/mock/mock_drag_window.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/pattern.h"

#define private public
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_ETS_TAG("root");
const std::string GRID_TAG("grid");
const std::string LIST_TAG("list");
const std::string NODE_TAG("custom_node");
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
std::string ConvertExtraInfoToJson(const std::string& extraInfo)
{
    auto json = JsonUtil::Create(true);
    if (!extraInfo.empty()) {
        json->Put("extraInfo", extraInfo.c_str());
    }
    return json->ToString();
}
} // namespace

class DragDropManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DragDropManagerTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
}

void DragDropManagerTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
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
     * @tc.steps: step3. call CreateAndShowDragWindow again
     * @tc.expected: step3. return nullptr because dragWindow_ has existed
     */
    void* voidPtr2 = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap2 = PixelMap::CreatePixelMap(voidPtr2);
    GestureEvent gestureEvent2;
    auto dragDropProxyNull = dragDropManager->CreateAndShowDragWindow(pixelMap2, gestureEvent2);
    EXPECT_FALSE(dragDropProxyNull);
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
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(MOCK_DRAG_WINDOW)), DrawFrameNode(_)).Times(1);
    auto dragDropProxy = dragDropManager->CreateAndShowDragWindow(customNode, gestureEvent);
    EXPECT_TRUE(dragDropProxy);

    /**
     * @tc.steps: step2. call OnDragMove
     *                   case: dragFrameNodes_ is empty & preTargetFrameNode_ is null
     * @tc.expected: step2. DragWindow.MoveTo() will be called
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->OnDragMove({ GLOBAL_X, GLOBAL_Y }, EXTRA_INFO);

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
     *                      leaveExtraInfo will be assigned to EXTRA_INFO_LEAVE and
     *                      preTargetFrameNode_ will be assigned to null
     *                      DragWindow.MoveTo() will be called
     */
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    auto preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->OnDragMove({ GLOBAL_X, GLOBAL_Y }, EXTRA_INFO_LEAVE);
    EXPECT_EQ(leaveExtraInfo, ConvertExtraInfoToJson(EXTRA_INFO_LEAVE));
    preTargetNode = dragDropManager->preTargetFrameNode_;
    EXPECT_FALSE(preTargetNode);

    /**
     * @tc.steps: step5. call AddDragFrameNode
     *                   after that, dragFrameNodes_ is not empty
     */
    dragDropManager->AddDragFrameNode(frameNode);

    /**
     * @tc.steps: step6. call OnDragMove
     *                   case: dragFrameNodes_ is not empty & preTargetFrameNode_ equals the frameNode
     * @tc.expected: step6. frameNode's onDragMove_ will be called
     *                      moveExtraInfo will be assigned to EXTRA_INFO_MOVE
     *                      DragWindow.MoveTo() will be called
     */
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    EXPECT_TRUE(preTargetNode);
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->OnDragMove({ GLOBAL_X, GLOBAL_Y }, EXTRA_INFO_MOVE);
    EXPECT_EQ(moveExtraInfo, ConvertExtraInfoToJson(EXTRA_INFO_MOVE));

    /**
     * @tc.steps: step7. call OnDragMove
     *                   case: dragFrameNodes_ is not empty & preTargetFrameNode_ not equals the frameNode
     * @tc.expected: step7. frameNode's onDragEnter_ will be called
     *                      enterExtraInfo will be assigned to EXTRA_INFO_ENTER
     *                      preTargetFrameNode_'s onDragLeave will be called
     *                      leaveExtraInfoNew will be assigned to EXTRA_INFO_ENTER
     *                      preTargetFrameNode_ is assigned to frameNode
     *                      DragWindow.MoveTo() will be called
     */
    auto newFrameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, newFrameNode);
    preTargetNode = dragDropManager->preTargetFrameNode_;
    EXPECT_TRUE(preTargetNode);
    // Set newFrameNode's onDragLeave callback
    auto eventHubNew = newFrameNode->GetEventHub<EventHub>();
    ASSERT_TRUE(eventHubNew);
    std::string leaveExtraInfoNew;
    auto onDragLeaveNew = [&leaveExtraInfoNew](const RefPtr<OHOS::Ace::DragEvent>& /* info */,
                              const std::string& extraParams) { leaveExtraInfoNew = extraParams; };
    eventHubNew->SetOnDragLeave(std::move(onDragLeaveNew));
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->OnDragMove({ GLOBAL_X, GLOBAL_Y }, EXTRA_INFO_ENTER);
    EXPECT_EQ(enterExtraInfo, ConvertExtraInfoToJson(EXTRA_INFO_ENTER));
    EXPECT_EQ(leaveExtraInfoNew, ConvertExtraInfoToJson(EXTRA_INFO_ENTER));
    preTargetNode = dragDropManager->preTargetFrameNode_;
    ASSERT_TRUE(preTargetNode);
    auto preTargetNodeTag = preTargetNode->GetTag();
    EXPECT_EQ(preTargetNodeTag, NODE_TAG);

    /**
     * @tc.steps: step8. call OnDragMove
     *                   case: dragFrameNodes_ is not empty & preTargetFrameNode_ is null
     * @tc.expected: step8. frameNode's onDragEnter_ will be called
     *                      enterExtraInfo will be assigned to EXTRA_INFO_ENTER
     *                      preTargetFrameNode_ is assigned to frameNode
     *                      DragWindow.MoveTo() will be called
     */
    dragDropManager->onDragCancel();
    preTargetNode = dragDropManager->preTargetFrameNode_;
    EXPECT_FALSE(preTargetNode);
    enterExtraInfo = "";
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->OnDragMove({ GLOBAL_X, GLOBAL_Y }, EXTRA_INFO_ENTER);
    EXPECT_EQ(enterExtraInfo, ConvertExtraInfoToJson(EXTRA_INFO_ENTER));
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
    dragDropManager->AddGridDragFrameNode(frameNode);

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
    EXPECT_EQ(itemInfoMove, ITEM_INFO_MOVE);

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
    EXPECT_EQ(itemInfoEnter, ITEM_INFO_ENTER);
    EXPECT_EQ(itemInfoLeaveNew, ITEM_INFO_ENTER);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    ASSERT_TRUE(preGridTargetNode);
    auto preGridTargetNodeTag = preGridTargetNode->GetTag();
    EXPECT_EQ(preGridTargetNodeTag, GRID_TAG);

    /**
     * @tc.steps: step8. call OnItemDragMove
     *                   case: gridDragFrameNodes_ is not empty & preGridTargetFrameNode_ is null
     * @tc.expected: step8. frameNode's onDragItemEnter_ will be called
     *                      itemInfoEnter will be assigned to ITEM_INFO_ENTER
     *                      DragWindow.MoveTo() will be called
     */
    dragDropManager->onItemDragCancel();
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetNode);
    itemInfoEnter = "";
    EXPECT_CALL(*(AceType::DynamicCast<MockDragWindow>(dragDropManager->dragWindow_)), MoveTo(GLOBAL_X, GLOBAL_Y))
        .Times(1);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    EXPECT_EQ(itemInfoEnter, ITEM_INFO_ENTER);
}

/**
 * @tc.name: DragDropManagerTest010
 * @tc.desc: Test OnItemDragMove DragType is List
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest010, TestSize.Level1)
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
        .Times(1);
    dragDropManager->OnItemDragMove(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_LIST);
    EXPECT_EQ(itemInfoLeave, ITEM_INFO_LEAVE);
    preGridTargetNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetNode);

    /**
     * @tc.steps: step5. call AddGridDragFrameNode
     *                   after that, listDragFrameNodes_ is not empty
     *                   need adding grid maybe a bug
     */
    dragDropManager->AddGridDragFrameNode(frameNode);

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
        .Times(1);
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
 * @tc.desc: Test OnDragEnd
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
     * @tc.steps: step2. construct a frameNode and set its GeometryNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_TRUE(eventHub);

    // Set geometry node to make sure (GLOBAL_X, GLOBAL_Y) in geoNode.frameRect_
    auto geoNode = AceType::MakeRefPtr<GeometryNode>();
    geoNode->SetMarginFrameOffset(FRAME_OFFSET);
    geoNode->SetFrameSize(FRAME_SIZE);
    frameNode->SetGeometryNode(geoNode);

    /**
     * @tc.steps: step3. call OnDragEnd
     *                   case: dragFrameNodes_ is empty
     * @tc.expected: step3. preTargetFrameNode_ is null and draggedFrameNode_ is not null
     */
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    dragDropManager->extraInfo_ = EXTRA_INFO;
    dragDropManager->OnDragEnd({ GLOBAL_X, GLOBAL_Y }, EXTRA_INFO);
    auto preTargetFrameNode = dragDropManager->preTargetFrameNode_;
    auto draggedFrameNode = dragDropManager->draggedFrameNode_;
    EXPECT_FALSE(preTargetFrameNode);
    EXPECT_TRUE(draggedFrameNode);

    /**
     * @tc.steps: step4. call AddDragFrameNode
     *                   after that, dragFrameNodes_ is not empty
     */
    dragDropManager->AddDragFrameNode(frameNode);

    /**
     * @tc.steps: step5. call OnDragEnd
     *                   case: eventHub dose not have onDrop_
     * @tc.expected: step5. preTargetFrameNode_ is null and draggedFrameNode_ is not null
     */
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    dragDropManager->OnDragEnd({ GLOBAL_X, GLOBAL_Y }, EXTRA_INFO);
    preTargetFrameNode = dragDropManager->preTargetFrameNode_;
    draggedFrameNode = dragDropManager->draggedFrameNode_;
    EXPECT_FALSE(preTargetFrameNode);
    EXPECT_TRUE(draggedFrameNode);

    /**
     * @tc.steps: step6. call OnDragEnd
     *                   case: eventHub dose have onDrop_, dragFrameNode == draggedFrameNode_
     * @tc.expected: step6. preTargetFrameNode_ is null and draggedFrameNode_ is not null
     */
    std::string extraInfoDrop;
    auto onDrop = [&extraInfoDrop](const RefPtr<OHOS::Ace::DragEvent>& /* info */, const std::string& extraParams) {
        extraInfoDrop = extraParams;
    };
    eventHub->SetOnDrop(std::move(onDrop));
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNode);
    dragDropManager->OnDragEnd({ GLOBAL_X, GLOBAL_Y }, EXTRA_INFO);
    preTargetFrameNode = dragDropManager->preTargetFrameNode_;
    draggedFrameNode = dragDropManager->draggedFrameNode_;
    EXPECT_FALSE(preTargetFrameNode);
    EXPECT_TRUE(draggedFrameNode);

    /**
     * @tc.steps: step7. call OnDragEnd
     *                   case: eventHub dose have onDrop_, dragFrameNode != draggedFrameNode_
     * @tc.expected: step7. frameNode's OnDrop_ will be called
     *                      extraInfoDrop will be assigned to EXTRA_INFO
     *                      preTargetFrameNode_ and draggedFrameNode_ will be assigned to nullptr
     */
    auto frameNodeNew = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->OnDragStart({ GLOBAL_X, GLOBAL_Y }, frameNodeNew);
    dragDropManager->OnDragEnd({ GLOBAL_X, GLOBAL_Y }, EXTRA_INFO);
    EXPECT_EQ(extraInfoDrop, ConvertExtraInfoToJson(EXTRA_INFO));
    preTargetFrameNode = dragDropManager->preTargetFrameNode_;
    draggedFrameNode = dragDropManager->draggedFrameNode_;
    EXPECT_FALSE(preTargetFrameNode);
    EXPECT_TRUE(draggedFrameNode);
}

/**
 * @tc.name: DragDropManagerTest012
 * @tc.desc: Test OnItemDragEnd type is grid
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
    dragDropManager->AddGridDragFrameNode(frameNode);

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
    EXPECT_EQ(itemDropInfo, EXTRA_INFO);
    preGridTargetFrameNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetFrameNode);

    // case: preGridTargetFrameNode_ == dragFrameNode
    dragDropManager->preGridTargetFrameNode_ = frameNode;
    itemDropInfo.clear();
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    EXPECT_EQ(itemDropInfo, EXTRA_INFO);

    // case: preGridTargetFrameNode_ != dragFrameNode
    dragDropManager->preGridTargetFrameNode_ = preGridTargetNode;
    itemDropInfo.clear();
    preGridDropInfo.clear();
    dragDropManager->OnItemDragEnd(GLOBAL_X, GLOBAL_Y, DRAGGED_INDEX, DRAG_TYPE_GRID);
    EXPECT_EQ(itemDropInfo, EXTRA_INFO);
    EXPECT_EQ(preGridDropInfo, "");
}

/**
 * @tc.name: DragDropManagerTest013
 * @tc.desc: Test OnItemDragEnd type is list
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
    dragDropManager->AddListDragFrameNode(frameNode);

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
    EXPECT_EQ(itemDropInfo, EXTRA_INFO);
    preGridTargetFrameNode = dragDropManager->preGridTargetFrameNode_;
    EXPECT_FALSE(preGridTargetFrameNode);
}

/**
 * @tc.name: DragDropManagerTest014
 * @tc.desc: Test corner case
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropManagerTestNg, DragDropManagerTest014, TestSize.Level1)
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
    auto frameNodeNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    dragDropManager->AddDragFrameNode(frameNodeNull);
    frameNodeNull.Reset();
    auto frameNodeGeoNull = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNodeGeoNull->SetGeometryNode(nullptr);
    dragDropManager->AddDragFrameNode(frameNodeGeoNull);
    EXPECT_EQ(static_cast<int32_t>(dragDropManager->dragFrameNodes_.size()), 2);
    auto targetFrameNode = dragDropManager->FindDragFrameNodeByPosition(GLOBAL_X, GLOBAL_Y, DragType::COMMON);
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
} // namespace OHOS::Ace::NG
