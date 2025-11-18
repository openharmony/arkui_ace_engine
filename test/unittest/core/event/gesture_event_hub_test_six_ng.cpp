/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "test/unittest/core/event/gesture_event_hub_test_ng.h"

#include "test/mock/base/mock_drag_window.h"
#include "test/mock/base/mock_subwindow.h"
#include "base/subwindow/subwindow_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"

#include "frameworks/core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void GestureEventHubTestSixNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
    GTEST_LOG_(INFO) << "GestureEventHubTestNg SetUpTestCase";
    MOCK_TASK_EXECUTOR = AceType::MakeRefPtr<MockTaskExecutor>();
}

void GestureEventHubTestSixNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MOCK_DRAG_WINDOW = nullptr;
    GTEST_LOG_(INFO) << "GestureEventHubTestNg TearDownTestCase";
}

/**
 * @tc.name: TryDoDragStartAnimation003
 * @tc.desc: Test TryDoDragStartAnimation when all conditions satisfied
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestSixNg, TryDoDragStartAnimation003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("testNode", 101, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->InitDragDropEvent();

    auto event = gestureEventHub->eventHub_.Upgrade();
    event->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));

    RefPtr<PipelineContext> context = AceType::DynamicCast<PipelineContext>(NG::MockPipelineContext::pipeline_);
    frameNode->AttachContext(AceType::RawPtr(context));
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    ASSERT_NE(pipeline, nullptr);

    auto mockContainer = AceType::MakeRefPtr<MockContainer>(context);
    EXPECT_CALL(*mockContainer, GetInstanceId()).WillRepeatedly(Return(INSTANCE_ID));
    MockContainer::container_ = mockContainer;
    Container::UpdateCurrent(INSTANCE_ID);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);

    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    EXPECT_CALL(*mockSubwindow, GetOverlayManager()).WillRepeatedly(Return(pipeline->GetOverlayManager()));
    RefPtr<Subwindow> subWindow = mockSubwindow;
    ASSERT_NE(subWindow, nullptr);
    GestureEvent info;
    PreparedInfoForDrag data;
    data.imageNode = FrameNode::CreateCommonNode("imageNode", 201, false, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(data.imageNode, nullptr);
    auto ret = gestureEventHub->TryDoDragStartAnimation(context, subWindow, info, data);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: GestureEventHubTestGetPixelMapOffset001
 * @tc.desc: Test GetPixelMapOffset covering all branches
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestSixNg, GestureEventHubTestGetPixelMapOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and associated GestureEventHub, set offset and simulate gesture location.
     */
    GestureEvent info;
    PreparedInfoForDrag dragInfoData;
    SizeF size(SIZE_X, SIZE_Y * 2);
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    gestureEventHub->frameNodeOffset_ = OffsetF(FRAME_OFFSET_X, FRAME_OFFSET_Y);
    info.SetGlobalLocation(Offset(GESTURE_GLOBAL_X, GESTURE_GLOBAL_Y));

    /**
     * @tc.steps: step2. Test when innerRect is valid and offset is calculated with scale = 1.0.
     * @tc.expected: X offset should be less than or equal to 0, Y offset greater than or equal to -200.
     */
    RectF innerRect(OffsetF(INNER_OFFSET_X, INNER_OFFSET_Y), SizeF(SIZE_X / 2, SIZE_Y));
    OffsetF offset = gestureEventHub->GetPixelMapOffset(info, size, dragInfoData, DEFAULT_SCALE, innerRect);
    EXPECT_LE(offset.GetX(), 0);
    EXPECT_GE(offset.GetY(), -200);

    /**
     * @tc.steps: step3. Test when frameNodeSize is (0, 0), expect fallback logic.
     * @tc.expected: X offset should be less than 0.
     */
    gestureEventHub->frameNodeSize_ = SizeF(SIZE_ZERO, SIZE_ZERO);
    offset = gestureEventHub->GetPixelMapOffset(info, size, dragInfoData, DEFAULT_SCALE * 2, RectF());
    EXPECT_LT(offset.GetX(), SIZE_ZERO);

    /**
     * @tc.steps: step4. Test when isNeedCreateTiled is true and frameNodeSize is set.
     * @tc.expected: X offset should equal -size.Width() / 2.
     */
    gestureEventHub->frameNodeSize_ = SizeF(SIZE_X, SIZE_Y);
    dragInfoData.isNeedCreateTiled = true;
    offset = gestureEventHub->GetPixelMapOffset(info, size, dragInfoData, DEFAULT_SCALE, RectF());
    EXPECT_FLOAT_EQ(offset.GetX(), -size.Width() / 2);

    /**
     * @tc.steps: step5. Test when touch point calculation is based on final preview and dragPreviewRect is provided.
     * @tc.expected: X offset should be less than 0.
     */
    NG::DragPreviewOption option;
    option.isTouchPointCalculationBasedOnFinalPreviewEnable = true;
    frameNode->SetDragPreviewOptions(option, false);
    dragInfoData.isNeedCreateTiled = false;
    dragInfoData.dragPreviewRect = RectF(OffsetF(DRAG_OFFSET_X, DRAG_OFFSET_Y), SizeF(SIZE_X, SIZE_Y));
    offset = gestureEventHub->GetPixelMapOffset(info, size, dragInfoData, DEFAULT_SCALE, RectF());
    EXPECT_LT(offset.GetX(), SIZE_ZERO);

    /**
     * @tc.steps: step6. Repeat test with same configuration to ensure deterministic behavior.
     * @tc.expected: X offset should be less than 0.
     */
    option.isTouchPointCalculationBasedOnFinalPreviewEnable = true;
    frameNode->SetDragPreviewOptions(option, false);
    offset = gestureEventHub->GetPixelMapOffset(info, size, dragInfoData, DEFAULT_SCALE, RectF());
    EXPECT_LT(offset.GetX(), SIZE_ZERO);
}

/**
 * @tc.name: CalcFrameNodeOffsetAndSize001
 * @tc.desc: Test CalcFrameNodeOffsetAndSize when frameNode is null
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestSixNg, CalcFrameNodeOffsetAndSize001, TestSize.Level1)
{
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::MakeRefPtr<EventHub>());
    ASSERT_NE(gestureEventHub, nullptr);
    EXPECT_TRUE(gestureEventHub);
    gestureEventHub->CalcFrameNodeOffsetAndSize(nullptr, true);
    EXPECT_EQ(gestureEventHub->frameNodeSize_.Width(), SIZE_ZERO);
    EXPECT_EQ(gestureEventHub->frameNodeSize_.Height(), SIZE_ZERO);
}

/**
 * @tc.name: CalcFrameNodeOffsetAndSize002
 * @tc.desc: Test CalcFrameNodeOffsetAndSize frameNode tag is TEXT_ETS_TAG, should use TextDragBase path
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestSixNg, CalcFrameNodeOffsetAndSize002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 101, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, false);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Width(), SIZE_ZERO);
    EXPECT_EQ(guestureEventHub->frameNodeSize_.Height(), SIZE_ZERO);
}

/**
 * @tc.name: CalcFrameNodeOffsetAndSize003
 * @tc.desc: Test CalcFrameNodeOffsetAndSize frameNode tag is not text category, fallback to default path and not WEB
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestSixNg, CalcFrameNodeOffsetAndSize003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 101, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(guestureEventHub, nullptr);
    guestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, false);
    EXPECT_TRUE(guestureEventHub->frameNodeSize_.Width() >= SIZE_ZERO);
}

/**
 * @tc.name: CalcFrameNodeOffsetAndSize004
 * @tc.desc: Test CalcFrameNodeOffsetAndSize where menuPreviewScale is zero (menu not applied)
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestSixNg, CalcFrameNodeOffsetAndSize004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 101, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);

    gestureEventHub->menuPreviewScale_ = SIZE_ZERO;
    gestureEventHub->CalcFrameNodeOffsetAndSize(frameNode, true);
    EXPECT_NE(gestureEventHub->frameNodeSize_, SizeF(SIZE_X, SIZE_Y));
}

/**
 * @tc.name: HandleOnDragStartSetDragStatus001
 * @tc.desc: Verify UpdateDragDropInitiatingStatus sets currentDragNode_ correctly
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestSixNg, HandleOnDragStartSetDragStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());

    /**
     * @tc.steps: step2. Build PixelMap and UINode, and update the properties of DragDropInfo.
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    DragDropInfo dragDropInfo;
    dragDropInfo.customNode = customNode;
    dragDropInfo.pixelMap = pixelMap;
    frameNode->SetDragPreview(dragDropInfo);

    auto hostPattern = frameNode->GetPattern<TextDragBase>();
    EXPECT_TRUE(hostPattern);

    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    auto onDragStart = [&customNode](
                           const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* param */) {
        DragDropInfo dragDropInfo;
        dragDropInfo.customNode = customNode;
        return dragDropInfo;
    };
    eventHub->SetOnDragStart(std::move(onDragStart));

    auto eventManager = AceType::MakeRefPtr<EventManager>();
    EXPECT_TRUE(eventManager);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetEventManager(eventManager);
    eventManager->SetLastMoveBeforeUp(false);

    /**
     * @tc.steps: step3. call HandleOnDragStart with SourceType::NONE and InputEventType::TOUCH_SCREEN.
     * @tc.expected: DragDropGlobalController::currentDragNode_ should be updated to frameNode.
     */
    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(SourceType::NONE);
    gestureEvent.SetInputEventType(InputEventType::TOUCH_SCREEN);
    DragDropGlobalController::GetInstance().SetDragStartRequestStatus(DragStartRequestStatus::WAITING);
    gestureEventHub->HandleOnDragStart(gestureEvent);
    EXPECT_EQ(DragDropGlobalController::GetInstance().currentDragNode_, frameNode);
}

/**
 * @tc.name: FireCustomerOnDragEndResetStatus001
 * @tc.desc: Test FireCustomerOnDragEnd resets currentDragNode_ in DragDropGlobalController
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestSixNg, FireCustomerOnDragEndResetStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set currentDragNode_ in DragDropGlobalController to a known node.
     * @tc.expected: currentDragNode_ is not null before reset.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    DragDropGlobalController::GetInstance().UpdateDragDropInitiatingStatus(frameNode, DragDropInitiatingStatus::MOVING);
    EXPECT_EQ(DragDropGlobalController::GetInstance().currentDragNode_, frameNode);

    /**
     * @tc.steps: step2. Create EventHub and GestureEventHub, attach to frameNode.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step3. Create PipelineContext and bind DragDropManager.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    pipeline->SetEventManager(eventManager);
    ASSERT_NE(eventManager, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Call FireCustomerOnDragEnd.
     * @tc.expected: currentDragNode_ is reset to nullptr.
     */
    WeakPtr<EventHub> hubWeak(eventHub);
    gestureEventHub->FireCustomerOnDragEnd(pipeline, hubWeak);
    EXPECT_EQ(DragDropGlobalController::GetInstance().currentDragNode_, nullptr);
}
} // namespace OHOS::Ace::NG
