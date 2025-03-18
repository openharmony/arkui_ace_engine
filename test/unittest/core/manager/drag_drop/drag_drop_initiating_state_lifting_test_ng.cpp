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

#include "test/unittest/core/manager/drag_drop/drag_drop_initiating_test_ng.h"

#define private public
#define protected public

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_handler.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_lifting.h"
#include "core/event/touch_event.h"
#include "core/gestures/drag_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct DragDropInitiatingStateLiftingTestCase : public DragDropInitiatingStateTestCase {
    bool isMenuShow = false;
    bool isTextDraggable = false;
    SourceType sourceType = SourceType::TOUCH;
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput receivedInput,
        DragDropInitiatingStatus expectStatus, bool isMenuShow, bool isTextDraggable, SourceType sourceType)
        : DragDropInitiatingStateTestCase(DragDropInitiatingStatus::LIFTING, receivedInput, expectStatus),
          isMenuShow(isMenuShow), isTextDraggable(isTextDraggable), sourceType(sourceType)
    {}
};

struct CheckDoShowPreviewTestCase {
    DragDropMgrState dragDropMgrState = DragDropMgrState::IDLE;
    bool hasPixelMap = false;
    bool isDragNodeNeedClean = false;
    bool isBindMenu = false;
    bool isMenuShow = false;
    bool isDragPreviewEnabled = false;
    bool exceptResult = false;
    CheckDoShowPreviewTestCase(DragDropMgrState dragDropMgrState, bool hasPixelMap, bool isDragNodeNeedClean,
        bool isBindMenu, bool isMenuShow, bool isDragPreviewEnabled, bool exceptResult)
        : dragDropMgrState(dragDropMgrState), hasPixelMap(hasPixelMap), isDragNodeNeedClean(isDragNodeNeedClean),
          isBindMenu(isBindMenu), isMenuShow(isMenuShow), isDragPreviewEnabled(isDragPreviewEnabled),
          exceptResult(exceptResult)
    {}
};

const std::vector<DragDropInitiatingStateLiftingTestCase> DRAG_DROP_INITIATING_STATE_LIFTING_IMAGE_TEST_CASES = {
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionEnd,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionEnd,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionEnd,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionEnd,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionCancel,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionCancel,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionCancel,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionCancel,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::LIFTING, false, true, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::LIFTING, true, true, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionEnd,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionEnd,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionCancel,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionCancel,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionCancel,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionCancel,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleTouchEvent,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleTouchEvent,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleTouchEvent,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleTouchEvent,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleReStartDrag,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleReStartDrag,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleReStartDrag,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleReStartDrag,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleDragStart,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleDragStart,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleDragStart,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleDragStart,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransMenuShow,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransMenuShow,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransMenuShow,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransMenuShow,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransDragWindowToFwk,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransDragWindowToFwk,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransDragWindowToFwk,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransDragWindowToFwk,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnReject,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnReject,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleSequenceOnActionCancel,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleSequenceOnActionCancel,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::MOUSE),
};

const std::vector<CheckDoShowPreviewTestCase> DRAG_DROP_INITIATING_CHECK_DO_SHOW_PREVIEW_TEST_CASES = {
    CheckDoShowPreviewTestCase(DragDropMgrState::IDLE, true, false, false, false, false, false),
    CheckDoShowPreviewTestCase(DragDropMgrState::ABOUT_TO_PREVIEW, false, false, false, false, false, false),
    CheckDoShowPreviewTestCase(DragDropMgrState::ABOUT_TO_PREVIEW, false, true, false, false, false, false),
    CheckDoShowPreviewTestCase(DragDropMgrState::DRAGGING, false, false, false, false, false, false),
    CheckDoShowPreviewTestCase(DragDropMgrState::DRAGGING, false, true, false, false, false, false),
    CheckDoShowPreviewTestCase(DragDropMgrState::IDLE, false, true, false, false, false, false),
    CheckDoShowPreviewTestCase(DragDropMgrState::IDLE, false, false, false, false, false, false),
    CheckDoShowPreviewTestCase(DragDropMgrState::IDLE, false, false, true, false, false, false),
    CheckDoShowPreviewTestCase(DragDropMgrState::IDLE, false, false, false, true, false, false),
    CheckDoShowPreviewTestCase(DragDropMgrState::IDLE, false, false, true, true, false, false),
    CheckDoShowPreviewTestCase(DragDropMgrState::IDLE, false, false, false, false, true, true),
    CheckDoShowPreviewTestCase(DragDropMgrState::IDLE, false, false, false, false, false, false),
};

void DragDropInitiatingStateLiftingTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropInitiatingStateLiftingTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG001
 * @tc.desc: Test CollectTouchTarget function when frameNode is image.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_DROP_INITIATING_STATE_LIFTING_IMAGE_TEST_CASES) {
        /**
         * @tc.steps: step1. create DragDropEventActuator.
         */
        auto eventHub = AceType::MakeRefPtr<EventHub>();
        ASSERT_NE(eventHub, nullptr);
        auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
        ASSERT_NE(gestureEventHub, nullptr);
        auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
        ASSERT_NE(frameNode, nullptr);
        eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
        auto dragDropEventActuator =
            AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
        ASSERT_NE(dragDropEventActuator, nullptr);
        auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
        ASSERT_NE(handler, nullptr);
        auto machine = handler->initiatingFlow_;
        ASSERT_NE(machine, nullptr);
        machine->InitializeState();
        machine->currentState_ = static_cast<int32_t>(testCase.originStatus);
        gestureEventHub->SetIsTextDraggable(testCase.isTextDraggable);
        if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_NONE_ARGS) != 0) {
            DragDropInitiatingStateTestNG::DoMachineAction(machine, testCase.receivedInput);
        } else if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_DRAG_POINTER_EVENT_ARGS) != 0) {
            DragPointerEvent dragPointerEvent;
            DragDropInitiatingStateTestNG::DoMachineAction(machine, testCase.receivedInput, dragPointerEvent);
        } else if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_TOUCH_EVENT_ARGS) != 0) {
            TouchEvent touchEvent;
            touchEvent.type = TouchType::MOVE;
            touchEvent.sourceType = testCase.sourceType;
            DragDropInitiatingStateTestNG::DoMachineAction(machine, testCase.receivedInput, touchEvent);
        } else if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_GESTURE_EVENT_ARGS) != 0) {
            GestureEvent info;
            info.SetSourceDevice(testCase.sourceType);
            DragDropInitiatingStateTestNG::DoMachineAction(machine, testCase.receivedInput, info);
        }
        EXPECT_TRUE(DragDropInitiatingStateTestNG::CheckDragDropInitiatingStatus(
            caseNum, static_cast<DragDropInitiatingStatus>(machine->currentState_), testCase.expectStatus));
        caseNum++;
    }
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG002
 * @tc.desc: Test Init function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dragDropEventActuator =
        AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
    ASSERT_NE(dragDropEventActuator, nullptr);
    auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
    ASSERT_NE(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->dragDropState_ = DragDropMgrState::IDLE;

    /**
     * @tc.steps: step2. test lifting state init for none text drag.
     */
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::LIFTING));
    EXPECT_TRUE(DragDropInitiatingStateTestNG::CheckDragDropInitiatingStatus(
        0, static_cast<DragDropInitiatingStatus>(machine->currentState_), DragDropInitiatingStatus::LIFTING));

    /**
     * @tc.steps: step3. test lifting state init with isLiftingDisabled is true.
     */
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    dragPreviewOption.isLiftingDisabled = false;
    machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::LIFTING));
    EXPECT_TRUE(DragDropInitiatingStateTestNG::CheckDragDropInitiatingStatus(
        0, static_cast<DragDropInitiatingStatus>(machine->currentState_), DragDropInitiatingStatus::LIFTING));

    /**
     * @tc.steps: step4. test lifting state init for text drag.
     */
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    gestureEventHub->SetTextDraggable(true);
    gestureEventHub->SetIsTextDraggable(true);
    machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::LIFTING));
    EXPECT_TRUE(DragDropInitiatingStateTestNG::CheckDragDropInitiatingStatus(
        0, static_cast<DragDropInitiatingStatus>(machine->currentState_), DragDropInitiatingStatus::LIFTING));

    /**
     * @tc.steps: step5. test lifting state init for text drag without isTextDraggable.
     */
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    gestureEventHub->SetIsTextDraggable(false);
    machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::LIFTING));
    EXPECT_TRUE(DragDropInitiatingStateTestNG::CheckDragDropInitiatingStatus(
        0, static_cast<DragDropInitiatingStatus>(machine->currentState_), DragDropInitiatingStatus::LIFTING));
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG003
 * @tc.desc: Test CheckDoShowPreview function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG003, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    for (const auto& testCase : DRAG_DROP_INITIATING_CHECK_DO_SHOW_PREVIEW_TEST_CASES) {
        /**
         * @tc.steps: step1. create DragDropEventActuator.
         */
        auto eventHub = AceType::MakeRefPtr<EventHub>();
        ASSERT_NE(eventHub, nullptr);
        auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
        ASSERT_NE(gestureEventHub, nullptr);
        auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
        ASSERT_NE(frameNode, nullptr);
        eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
        auto dragDropEventActuator =
            AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
        ASSERT_NE(dragDropEventActuator, nullptr);
        auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
        ASSERT_NE(handler, nullptr);
        auto machine = handler->initiatingFlow_;
        ASSERT_NE(machine, nullptr);
        machine->InitializeState();
        auto state = machine->dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::LIFTING)];
        ASSERT_NE(state, nullptr);
        auto liftingState = AceType::DynamicCast<DragDropInitiatingStateLifting>(state);
        ASSERT_NE(liftingState, nullptr);

        overlayManager->SetHasPixelMap(testCase.hasPixelMap);
        dragDropManager->dragDropState_ = testCase.dragDropMgrState;
        dragDropManager->isDragNodeNeedClean_ = testCase.isDragNodeNeedClean;
        DragDropGlobalController::GetInstance().UpdateMenuShowingStatus(testCase.isMenuShow);
        frameNode->previewOption_.isDragPreviewEnabled = testCase.isDragPreviewEnabled;
        gestureEventHub->bindMenuStatus_.isBindLongPressMenu = testCase.isBindMenu;
        EXPECT_EQ(liftingState->CheckDoShowPreview(frameNode), testCase.exceptResult);
    }
}
} // namespace OHOS::Ace::NG