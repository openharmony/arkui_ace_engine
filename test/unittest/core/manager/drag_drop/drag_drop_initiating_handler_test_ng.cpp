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

#include "gtest/gtest.h"
#include "test/unittest/core/manager/drag_drop/drag_drop_initiating_test_ng.h"
#define private public
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_handler.h"
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string CUSTOM_DRAG_END_EVENT_TYPE = "custom drag end";
const std::string DRAG_END_EVENT_TYPE = "drag end";
} // namespace

void DragDropInitiatingHandlerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropInitiatingHandlerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: IsNeedGatherTestNG001
 * @tc.desc: Test IsNeedGather Function When initiatingFlow_ is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, IsNeedGatherTestNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    dragDropInitiatingHandler->initiatingFlow_ = nullptr;
    EXPECT_FALSE(dragDropInitiatingHandler->IsNeedGather());
    dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
    dragDropInitiatingHandler->initiatingFlow_->GetDragDropInitiatingParams().isNeedGather = true;
    EXPECT_TRUE(dragDropInitiatingHandler->IsNeedGather());
}

/**
 * @tc.name: GetDragDropInitiatingStatusTestNG001
 * @tc.desc: Test GetDragDropInitiatingStatus Function When initiatingFlow_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, GetDragDropInitiatingStatusTestNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    ASSERT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
    EXPECT_EQ(dragDropInitiatingHandler->GetDragDropInitiatingStatus(),
        dragDropInitiatingHandler->initiatingFlow_->GetDragDropInitiatingStatus());
}

/**
 * @tc.name: GetDragDropInitiatingStatusTestNG002
 * @tc.desc: Test GetDragDropInitiatingStatus Function When initiatingFlow_ is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, GetDragDropInitiatingStatusTestNG002, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    dragDropInitiatingHandler->initiatingFlow_ = nullptr;
    EXPECT_EQ(dragDropInitiatingHandler->GetDragDropInitiatingStatus(), DragDropInitiatingStatus::IDLE);
}

/**
 * @tc.name: DragDropInitiatingHandlerTestNG001
 * @tc.desc: Test DragDropInitiatingHandler Function When initiatingFlow_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, DragDropInitiatingHandlerTestNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: SetThumbnailCallbackNG001
 * @tc.desc: Test DragDropInitiatingHandler Function When initiatingFlow_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, SetThumbnailCallbackNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
    dragDropInitiatingHandler->SetThumbnailCallback([](const Offset&) {});
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_->dragDropInitiatingParams_.getTextThumbnailPixelMapCallback,
        nullptr);
}

/**
 * @tc.name: FireCustomerOnDragEndNG001
 * @tc.desc: Test DragDropInitiatingHandler Function When initiatingFlow_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, FireCustomerOnDragEndNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
    auto machine = dragDropInitiatingHandler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    DragDropGlobalController::GetInstance().SetDragStartRequestStatus(DragStartRequestStatus::WAITING);
    DragDropGlobalController::GetInstance().UpdateDragDropInitiatingStatus(frameNode, DragDropInitiatingStatus::MOVING);
    EXPECT_EQ(DragDropGlobalController::GetInstance().currentDragNode_, frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    std::string customerDragEventType;
    std::string dragEventType;
    auto customerOnDragEnd = [&customerDragEventType](const RefPtr<OHOS::Ace::DragEvent>& info) {
        EXPECT_EQ(info->GetResult(), DragRet::DRAG_FAIL);
        customerDragEventType = CUSTOM_DRAG_END_EVENT_TYPE;
    };
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_END, customerOnDragEnd);
    auto onDragEnd = [&dragEventType](const RefPtr<OHOS::Ace::DragEvent>& info) {
        EXPECT_EQ(info->GetResult(), DragRet::DRAG_FAIL);
        dragEventType = DRAG_END_EVENT_TYPE;
    };
    eventHub->SetOnDragEnd(onDragEnd);
    ASSERT_NE(machine->dragDropInitiatingState_[machine->currentState_], nullptr);
    machine->dragDropInitiatingState_[machine->currentState_]->Init(machine->currentState_);
    EXPECT_EQ(DragDropGlobalController::GetInstance().currentDragNode_, nullptr);
    EXPECT_EQ(customerDragEventType, CUSTOM_DRAG_END_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_END_EVENT_TYPE);
}

/**
 * @tc.name: IsAllowedDragNG001
 * @tc.desc: Test DragDropInitiatingHandler Function When initiatingFlow_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, IsAllowedDragNG001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
    auto machine = dragDropInitiatingHandler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    ASSERT_NE(machine->dragDropInitiatingState_[machine->currentState_], nullptr);
    EXPECT_TRUE(machine->dragDropInitiatingState_[machine->currentState_]->IsAllowedDrag());
}

/**
 * @tc.name: NotifyLongPressOnActionTest001
 * @tc.desc: Test NotifyLongPressOnAction function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyLongPressOnActionTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    dragDropInitiatingHandler->NotifyLongPressOnAction(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyLongPressOnActionEndTest001
 * @tc.desc: Test NotifyLongPressOnActionEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyLongPressOnActionEndTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    dragDropInitiatingHandler->NotifyLongPressOnActionEnd(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyLongPressOnActionCancelTest001
 * @tc.desc: Test NotifyLongPressOnActionCancel function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyLongPressOnActionCancelTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    dragDropInitiatingHandler->NotifyLongPressOnActionCancel(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyPreviewLongPressOnActionTest001
 * @tc.desc: Test NotifyPreviewLongPressOnAction function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyPreviewLongPressOnActionTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    dragDropInitiatingHandler->NotifyPreviewLongPressOnAction(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyPanOnActionStartTest001
 * @tc.desc: Test NotifyPanOnActionStart function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyPanOnActionStartTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    info.SetOffsetX(100.0f);
    info.SetOffsetY(200.0f);
    dragDropInitiatingHandler->NotifyPanOnActionStart(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyPanOnActionUpdateTest001
 * @tc.desc: Test NotifyPanOnActionUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyPanOnActionUpdateTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    info.SetOffsetX(150.0f);
    info.SetOffsetY(250.0f);
    dragDropInitiatingHandler->NotifyPanOnActionUpdate(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyPanOnActionEndTest001
 * @tc.desc: Test NotifyPanOnActionEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyPanOnActionEndTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    dragDropInitiatingHandler->NotifyPanOnActionEnd(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyPanOnActionCancelTest001
 * @tc.desc: Test NotifyPanOnActionCancel function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyPanOnActionCancelTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    dragDropInitiatingHandler->NotifyPanOnActionCancel(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyPanOnRejectTest001
 * @tc.desc: Test NotifyPanOnReject function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyPanOnRejectTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    dragDropInitiatingHandler->NotifyPanOnReject();
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifySequenceOnActionCancelTest001
 * @tc.desc: Test NotifySequenceOnActionCancel function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifySequenceOnActionCancelTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    dragDropInitiatingHandler->NotifySequenceOnActionCancel(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyHitTestingTest001
 * @tc.desc: Test NotifyHitTesting function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyHitTestingTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100.0f;
    touchEvent.y = 200.0f;
    dragDropInitiatingHandler->NotifyHitTesting(touchEvent);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyTouchEventTest001
 * @tc.desc: Test NotifyTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyTouchEventTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100.0f;
    touchEvent.y = 200.0f;
    dragDropInitiatingHandler->NotifyTouchEvent(touchEvent);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyPullEventTest001
 * @tc.desc: Test NotifyPullEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyPullEventTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    DragPointerEvent dragPointerEvent;
    dragPointerEvent.x = 100.0f;
    dragPointerEvent.y = 200.0f;
    dragDropInitiatingHandler->NotifyPullEvent(dragPointerEvent);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyReStartDragTest001
 * @tc.desc: Test NotifyReStartDrag function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyReStartDragTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    info.SetOffsetX(100.0f);
    info.SetOffsetY(200.0f);
    dragDropInitiatingHandler->NotifyReStartDrag(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: GetPreScaledPixelMapTest001
 * @tc.desc: Test GetPreScaledPixelMapForDragThroughTouch function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, GetPreScaledPixelMapTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    float preScale = 1.0f;
    auto pixelMap = dragDropInitiatingHandler->GetPreScaledPixelMapForDragThroughTouch(preScale);
    EXPECT_EQ(preScale, 1.0f);
    EXPECT_EQ(pixelMap, nullptr);
}

/**
 * @tc.name: ResetPreScaledPixelMapTest001
 * @tc.desc: Test ResetPreScaledPixelMapForDragThroughTouch function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, ResetPreScaledPixelMapTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    // Set up preScaledPixelMap first
    auto machine = dragDropInitiatingHandler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    auto& params = machine->GetDragDropInitiatingParams();
    params.preScaledPixelMap = PixelMap::CreatePixelMap(static_cast<void*>(new char[0]));
    params.preScaleValue = 1.5f;

    dragDropInitiatingHandler->ResetPreScaledPixelMapForDragThroughTouch();
    EXPECT_EQ(params.preScaledPixelMap, nullptr);
    EXPECT_EQ(params.preScaleValue, 1.0f);
}

/**
 * @tc.name: NotifyDragStartTest001
 * @tc.desc: Test NotifyDragStart function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyDragStartTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    dragDropInitiatingHandler->NotifyDragStart();
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyDragEndTest001
 * @tc.desc: Test NotifyDragEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyDragEndTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    dragDropInitiatingHandler->NotifyDragEnd();
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyTransDragWindowToFwkTest001
 * @tc.desc: Test NotifyTransDragWindowToFwk function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyTransDragWindowToFwkTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    dragDropInitiatingHandler->NotifyTransDragWindowToFwk();
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyMenuShowTest001
 * @tc.desc: Test NotifyMenuShow function with true.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyMenuShowTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    dragDropInitiatingHandler->NotifyMenuShow(true);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyMenuShowTest002
 * @tc.desc: Test NotifyMenuShow function with false.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyMenuShowTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    dragDropInitiatingHandler->NotifyMenuShow(false);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyPreDragStatusTest001
 * @tc.desc: Test NotifyPreDragStatus function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyPreDragStatusTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    dragDropInitiatingHandler->NotifyPreDragStatus(PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyPreviewLongPressOnActionEndTest001
 * @tc.desc: Test NotifyPreviewLongPressOnActionEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyPreviewLongPressOnActionEndTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    dragDropInitiatingHandler->NotifyPreviewLongPressOnActionEnd(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

/**
 * @tc.name: NotifyPreviewLongPressOnActionCancelTest001
 * @tc.desc: Test NotifyPreviewLongPressOnActionCancel function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingHandlerTestNg, NotifyPreviewLongPressOnActionCancelTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto dragDropInitiatingHandler = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    ASSERT_NE(dragDropInitiatingHandler, nullptr);

    GestureEvent info;
    dragDropInitiatingHandler->NotifyPreviewLongPressOnActionCancel(info);
    EXPECT_NE(dragDropInitiatingHandler->initiatingFlow_, nullptr);
}

} // namespace OHOS::Ace::NG