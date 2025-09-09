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
namespace {
constexpr float POINT_X = 100.0f;
constexpr float POINT_Y = 100.0f;
constexpr float SCALE_NUMBER = 0.95;
}
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

struct HandlePreDragStatusTestCase {
    bool isNeedGather = false;
    bool defaultAnimationBeforeLifting = false;
    PreDragStatus preDragStatus = PreDragStatus::ACTION_DETECTING_STATUS;
    bool exceptResult = false;
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
        DragDropInitiatingStatus::MOVING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleDragStart,
        DragDropInitiatingStatus::MOVING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleDragStart,
        DragDropInitiatingStatus::MOVING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleDragStart,
        DragDropInitiatingStatus::MOVING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransMenuShow,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransMenuShow,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransMenuShow,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransMenuShow,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransDragWindowToFwk,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransDragWindowToFwk,
        DragDropInitiatingStatus::IDLE, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransDragWindowToFwk,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::TransDragWindowToFwk,
        DragDropInitiatingStatus::IDLE, true, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnReject,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePanOnReject,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleSequenceOnActionCancel,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleSequenceOnActionCancel,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandlePullEvent,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleDragEnd,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
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

const std::vector<HandlePreDragStatusTestCase> DRAG_DROP_INITIATING_HANDLE_PRE_DRAG_STATUS_TEST_CASES = {
    { false, false, PreDragStatus::ACTION_DETECTING_STATUS, false },
    { false, false, PreDragStatus::PREVIEW_LIFT_FINISHED, false },
    { false, true, PreDragStatus::ACTION_DETECTING_STATUS, false },
    { false, true, PreDragStatus::PREVIEW_LIFT_FINISHED, false },
    { true, false, PreDragStatus::ACTION_DETECTING_STATUS, false },
    { true, false, PreDragStatus::PREVIEW_LIFT_FINISHED, false },
    { true, true, PreDragStatus::ACTION_DETECTING_STATUS, false },
    { true, true, PreDragStatus::PREVIEW_LIFT_FINISHED, true },
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
    DragDropGlobalController::GetInstance().UpdateMenuShowingStatus(false);
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
        DragDropGlobalController::GetInstance().UpdateMenuShowingStatus(testCase.isMenuShow);
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
        auto dragPreviewOption = frameNode->GetDragPreviewOption();
        dragPreviewOption.isDragPreviewEnabled = testCase.isDragPreviewEnabled;
        frameNode->SetDragPreviewOptions(dragPreviewOption);
        gestureEventHub->bindMenuStatus_.isBindLongPressMenu = testCase.isBindMenu;
        EXPECT_EQ(liftingState->CheckDoShowPreview(frameNode), testCase.exceptResult);
    }
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG004
 * @tc.desc: Test HandlePreDragStatus function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG004, TestSize.Level1)
{
    for (const auto& testCase : DRAG_DROP_INITIATING_HANDLE_PRE_DRAG_STATUS_TEST_CASES) {
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

        auto layoutProperty = frameNode->GetLayoutProperty();
        if (layoutProperty) {
            layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        }
        auto& params = machine->GetDragDropInitiatingParams();
        params.isNeedGather = testCase.isNeedGather;
        auto dragPreviewOption = frameNode->GetDragPreviewOption();
        dragPreviewOption.defaultAnimationBeforeLifting = testCase.defaultAnimationBeforeLifting;
        frameNode->SetDragPreviewOptions(dragPreviewOption);
        liftingState->HandlePreDragStatus(testCase.preDragStatus);
        auto type = frameNode->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE);
        EXPECT_EQ(type == VisibleType::VISIBLE, testCase.exceptResult);
    }
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG005
 * @tc.desc: Test CollectTouchTarget function when frameNode is image.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG005, TestSize.Level1)
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
    auto state = machine->dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::LIFTING)];
    ASSERT_NE(state, nullptr);
    auto liftingState = AceType::DynamicCast<DragDropInitiatingStateLifting>(state);
    ASSERT_NE(liftingState, nullptr);
    gestureEventHub->SetIsTextDraggable(true);

    auto info = GestureEvent();
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::LIFTING);
    info.CopyConvertInfoFrom(ConvertInfo { UIInputEventType::AXIS, UIInputEventType::TOUCH });
    liftingState->HandleReStartDrag(info);
    EXPECT_EQ(static_cast<DragDropInitiatingStatus>(machine->currentState_), DragDropInitiatingStatus::LIFTING);
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG006
 * @tc.desc: Test DoDragDampingAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG006, TestSize.Level1)
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
    auto state = machine->dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::LIFTING)];
    ASSERT_NE(state, nullptr);
    auto liftingState = AceType::DynamicCast<DragDropInitiatingStateLifting>(state);
    ASSERT_NE(liftingState, nullptr);

    /**
     * @tc.steps: step2. set dragDropManager.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    dragDropManager->dampingOverflowCount_ = 1;
    dragDropManager->dragTotalMovePosition_ = OffsetF(1.0f, 1.0f);

    /**
     * @tc.steps: step3. execute DoDragDampingAnimation.
     */
    int32_t pointerId = 1;
    Point point(POINT_X, POINT_Y);

    liftingState->DoDragDampingAnimation(point, pointerId);
    EXPECT_EQ(dragDropManager->dragMovePosition_, OffsetF(0.0f, 0.0f));

    dragDropManager->dragDropState_ = DragDropMgrState::IDLE;
    dragDropManager->currentPointerId_ = pointerId;
    liftingState->DoDragDampingAnimation(point, pointerId);
    EXPECT_NE(dragDropManager->dragMovePosition_, OffsetF(0.0f, 0.0f));

    dragDropManager->dampingOverflowCount_ = 0;
    liftingState->DoDragDampingAnimation(point, pointerId);
    EXPECT_NE(dragDropManager->dragMovePosition_, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG007
 * @tc.desc: Test SetScaleAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG007, TestSize.Level1)
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
    auto state = machine->dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::LIFTING)];
    ASSERT_NE(state, nullptr);
    auto liftingState = AceType::DynamicCast<DragDropInitiatingStateLifting>(state);
    ASSERT_NE(liftingState, nullptr);

    /**
     * @tc.steps: step2. create pixelMapNode.
     */
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode, nullptr);
    auto childNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(childNode, nullptr);
    columnNode->AddChild(childNode);
    manager->pixmapColumnNodeWeak_ = columnNode;
    auto dragDropManager = pipeline->GetDragDropManager();
    dragDropManager->currentPointerId_ = 0;
    dragDropManager->draggingPressedState_ = true;

    /**
     * @tc.steps: step3. execute SetScaleAnimation.
     */
    liftingState->SetScaleAnimation(0);
    EXPECT_EQ(DragDropGlobalController::GetInstance().GetPreDragStatus(), PreDragStatus::ACTION_DETECTING_STATUS);
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG008
 * @tc.desc: Test SetPixelMap.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    ASSERT_NE(pixelMap, nullptr);
    gestureEventHub->SetPixelMap(pixelMap);
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

    /**
     * @tc.steps: step2. create pixelmap.
     */
    gestureEventHub->pixelMap_ = pixelMap;

    /**
     * @tc.steps: step3. execute SetPixelMap.
     */
    liftingState->SetPixelMap();
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    EXPECT_EQ(manager->GetHasPixelMap(), false);
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG009
 * @tc.desc: Test ShowPixelMapAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG009, TestSize.Level1)
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
    frameNode->SetDragPreviewOptions({.defaultAnimationBeforeLifting = true });
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto dragDropEventActuator =
        AceType::MakeRefPtr<DragDropEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
    ASSERT_NE(dragDropEventActuator, nullptr);
    auto handler = dragDropEventActuator->dragDropInitiatingHandler_;
    ASSERT_NE(handler, nullptr);
    auto machine = handler->initiatingFlow_;
    ASSERT_NE(machine, nullptr);
    machine->InitializeState();
    auto& params = machine->GetDragDropInitiatingParams();
    params.isNeedGather = true;
    auto state = machine->dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::LIFTING)];
    ASSERT_NE(state, nullptr);
    auto liftingState = AceType::DynamicCast<DragDropInitiatingStateLifting>(state);
    ASSERT_NE(liftingState, nullptr);

    /**
    * @tc.steps: step2. create imageNode.
    */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    auto imageContext = imageNode->GetRenderContext();
    ASSERT_NE(imageContext, nullptr);
    imageContext->UpdateTransformScale({ 1.0f, 1.0f });
    /**
    * @tc.steps: step3. execute ShowPixelMapAnimation.
    */
    liftingState->ShowPixelMapAnimation(imageNode, frameNode);
    auto scale = imageContext->GetTransformScaleValue({ 1.0f, 1.0f });
    EXPECT_EQ(scale.x, SCALE_NUMBER);
    EXPECT_EQ(scale.y, SCALE_NUMBER);
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG010
 * @tc.desc: Test SetGatherAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG010, TestSize.Level1)
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
    auto& params = machine->GetDragDropInitiatingParams();
    params.isNeedGather = true;
    auto state = machine->dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::LIFTING)];
    ASSERT_NE(state, nullptr);
    auto liftingState = AceType::DynamicCast<DragDropInitiatingStateLifting>(state);
    ASSERT_NE(liftingState, nullptr);

    /**
     * @tc.steps: step2. create pixelMapNode and copyNode.
     */
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode, nullptr);
    auto childNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(childNode, nullptr);
    columnNode->AddChild(childNode);
    manager->pixmapColumnNodeWeak_ = columnNode;

    auto copyNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(copyNode, nullptr);
    manager->dragNodeCopyWeak_ = copyNode;

    /**
     * @tc.steps: step3. execute SetGatherAnimation.
     */
    liftingState->SetGatherAnimation(pipeline);
    auto dragCopyNode = manager->GetDragNodeCopy();
    ASSERT_NE(dragCopyNode, nullptr);
    auto renderContext = dragCopyNode->GetRenderContext();
    auto opacity = renderContext->GetOpacityValue();
    EXPECT_EQ(opacity, 0.0f);
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG011
 * @tc.desc: Test SetTextAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG011, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create DragDropEventActuator.
    */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto frameNode =
        AceType::MakeRefPtr<FrameNode>(V2::SEARCH_Field_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
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
    auto& params = machine->GetDragDropInitiatingParams();
    params.isNeedGather = true;
    auto state = machine->dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::LIFTING)];
    ASSERT_NE(state, nullptr);
    auto liftingState = AceType::DynamicCast<DragDropInitiatingStateLifting>(state);
    ASSERT_NE(liftingState, nullptr);

    /**
     * @tc.steps: step2. execute SetTextAnimation.
     */
    auto pattern = frameNode->GetPattern<TextBase>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->showSelect_, true);

    liftingState->SetTextAnimation();
    EXPECT_EQ(pattern->showSelect_, true);

    auto textBase = frameNode->GetPattern<TextBase>();
    ASSERT_NE(textBase, nullptr);
    textBase->textSelector_.Update(3, 4);
    liftingState->SetTextAnimation();
    EXPECT_EQ(pattern->showSelect_, true);
}

/**
 * @tc.name: CheckDoShowPreviewTestNG001
 * @tc.desc: Test CheckDoShowPreview function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, CheckDoShowPreviewTestNG001, TestSize.Level1)
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
    auto state = machine->dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::LIFTING)];
    ASSERT_NE(state, nullptr);
    auto liftingState = AceType::DynamicCast<DragDropInitiatingStateLifting>(state);
    ASSERT_NE(liftingState, nullptr);

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    dragDropManager->isDragNodeNeedClean_ = true;
    EXPECT_FALSE(liftingState->CheckDoShowPreview(frameNode));
}

/**
 * @tc.name: CheckStatusForPanActionBeginTestNG001
 * @tc.desc: Test CheckStatusForPanActionBegin function expect IsDragNodeNeedClean.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, CheckStatusForPanActionBeginTestNG001, TestSize.Level1)
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
    auto state = machine->dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::LIFTING)];
    ASSERT_NE(state, nullptr);
    auto liftingState = AceType::DynamicCast<DragDropInitiatingStateBase>(state);
    ASSERT_NE(liftingState, nullptr);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    dragDropManager->isDragNodeNeedClean_ = true;
    GestureEvent info;
    EXPECT_FALSE(liftingState->CheckStatusForPanActionBegin(frameNode, info));
}

/**
 * @tc.name: DragDropInitiatingStateLiftingTestNG012
 * @tc.desc: Test Init function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateLiftingTestNG, DragDropInitiatingStateLiftingTestNG012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureEventHub, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
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
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
 
    /**
     * @tc.steps: step2. test lifting state init with IsAllowedDrag is false.
     */
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::IDLE);
    frameNode->SetDraggable(true);
    overlayManager->SetHasPixelMap(false);
    machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::LIFTING));
    EXPECT_EQ(DragDropGlobalController::GetInstance().GetPrepareDragFrameNode().Upgrade(), nullptr);
}
} // namespace OHOS::Ace::NG