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
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_idle.h"
#include "core/event/touch_event.h"
#include "core/gestures/drag_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
testing::AssertionResult DragDropInitiatingStateTestNG::CheckDragDropInitiatingStatus(
    int32_t caseNum, DragDropInitiatingStatus dragStatus, DragDropInitiatingStatus expectStatus)
{
    if (dragStatus == expectStatus) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "TestCaseNum: " << caseNum
                                       << ", actual state: " << static_cast<int32_t>(dragStatus)
                                       << ", expect state: " << static_cast<int32_t>(expectStatus);
}

void DragDropInitiatingStateTestNG::DoMachineAction(
    const RefPtr<DragDropInitiatingStateMachine>& machine, DragDropInitiatingReceivedInput receivedInput)
{
    if (!machine) {
        return;
    }
    switch (receivedInput) {
        case DragDropInitiatingReceivedInput::HandlePanOnReject:
            machine->HandlePanOnReject();
            break;
        case DragDropInitiatingReceivedInput::HandleDragStart:
            machine->HandleDragStart();
            break;
        case DragDropInitiatingReceivedInput::HandleDragEnd:
            machine->HandleDragEnd();
            break;
        case DragDropInitiatingReceivedInput::TransDragWindowToFwk:
            machine->TransDragWindowToFwk();
            break;
        case DragDropInitiatingReceivedInput::TransMenuShow:
            machine->TransMenuShow(DragDropGlobalController::GetInstance().IsMenuShowing());
            break;
        default:
            break;
    }
    return;
}

void DragDropInitiatingStateTestNG::DoMachineAction(const RefPtr<DragDropInitiatingStateMachine>& machine,
    DragDropInitiatingReceivedInput receivedInput, const GestureEvent& info)
{
    if (!machine) {
        return;
    }
    switch (receivedInput) {
        case DragDropInitiatingReceivedInput::HandleLongPressOnAction:
            machine->HandleLongPressOnAction(info);
            break;
        case DragDropInitiatingReceivedInput::HandleLongPressOnActionEnd:
            machine->HandleLongPressOnActionEnd(info);
            break;
        case DragDropInitiatingReceivedInput::HandleLongPressOnActionCancel:
            machine->HandleLongPressOnActionCancel(info);
            break;
        case DragDropInitiatingReceivedInput::HandlePreviewLongPressOnAction:
            machine->HandlePreviewLongPressOnAction(info);
            break;
        case DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionEnd:
            machine->HandlePreviewLongPressOnActionEnd(info);
            break;
        case DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionCancel:
            machine->HandlePreviewLongPressOnActionCancel(info);
            break;
        case DragDropInitiatingReceivedInput::HandlePanOnActionStart:
            machine->HandlePanOnActionStart(info);
            break;
        case DragDropInitiatingReceivedInput::HandlePanOnActionUpdate:
            machine->HandlePanOnActionUpdate(info);
            break;
        case DragDropInitiatingReceivedInput::HandlePanOnActionEnd:
            machine->HandlePanOnActionEnd(info);
            break;
        case DragDropInitiatingReceivedInput::HandlePanOnActionCancel:
            machine->HandlePanOnActionCancel(info);
            break;
        case DragDropInitiatingReceivedInput::HandleSequenceOnActionCancel:
            machine->HandleSequenceOnActionCancel(info);
            break;
        case DragDropInitiatingReceivedInput::HandleReStartDrag:
            machine->HandleReStartDrag(info);
            break;
        default:
            break;
    }
    return;
}

void DragDropInitiatingStateTestNG::DoMachineAction(const RefPtr<DragDropInitiatingStateMachine>& machine,
    DragDropInitiatingReceivedInput receivedInput, const TouchEvent& touchEvent)
{
    if (!machine) {
        return;
    }
    switch (receivedInput) {
        case DragDropInitiatingReceivedInput::HandleHitTesting:
            machine->HandleHitTesting(touchEvent);
            break;
        case DragDropInitiatingReceivedInput::HandleTouchEvent:
            machine->HandleTouchEvent(touchEvent);
            break;
        default:
            break;
    }
    return;
}

void DragDropInitiatingStateTestNG::DoMachineAction(const RefPtr<DragDropInitiatingStateMachine>& machine,
    DragDropInitiatingReceivedInput receivedInput, const DragPointerEvent& dragPointerEvent)
{
    if (!machine) {
        return;
    }
    switch (receivedInput) {
        case DragDropInitiatingReceivedInput::HandlePullEvent:
            machine->HandlePullEvent(dragPointerEvent);
            break;
        default:
            break;
    }
    return;
}

struct DragDropInitiatingStateIdleTestCase : public DragDropInitiatingStateTestCase {
    bool isMenuShow = false;
    bool isTextDraggable = false;
    SourceType sourceType = SourceType::TOUCH;
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput receivedInput,
        DragDropInitiatingStatus expectStatus, bool isMenuShow, bool isTextDraggable, SourceType sourceType)
        : DragDropInitiatingStateTestCase(DragDropInitiatingStatus::IDLE, receivedInput, expectStatus),
          isMenuShow(isMenuShow), isTextDraggable(isTextDraggable), sourceType(sourceType)
    {}
};

const std::vector<DragDropInitiatingStateIdleTestCase> DRAG_DROP_INITIATING_STATE_IDLE_IMAGE_TEST_CASES = {
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, false, SourceType::NONE),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, true, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, true, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, false, SourceType::MOUSE),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, false, SourceType::MOUSE),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, true, SourceType::MOUSE),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, true, SourceType::MOUSE),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleLongPressOnAction,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleLongPressOnActionEnd,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleLongPressOnActionCancel,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnAction,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionEnd,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnActionCancel,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionUpdate,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionEnd,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionCancel,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandlePanOnReject,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleSequenceOnActionCancel,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleTouchEvent,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandlePullEvent,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleReStartDrag,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleDragStart,
        DragDropInitiatingStatus::MOVING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::HandleDragEnd, DragDropInitiatingStatus::IDLE,
        false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::TransDragWindowToFwk,
        DragDropInitiatingStatus::IDLE, false, false, SourceType::TOUCH),
    DragDropInitiatingStateIdleTestCase(DragDropInitiatingReceivedInput::TransMenuShow, DragDropInitiatingStatus::IDLE,
        false, false, SourceType::TOUCH),
};

void DragDropInitiatingStateIdleTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropInitiatingStateIdleTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DragDropInitiatingStateIdleTestNG001
 * @tc.desc: Test CollectTouchTarget function when frameNode is image.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateIdleTestNG, DragDropInitiatingStateIdleTestNG001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_DROP_INITIATING_STATE_IDLE_IMAGE_TEST_CASES) {
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
        gestureEventHub->SetTextDraggable(testCase.isTextDraggable);
        if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_NONE_ARGS) != 0) {
            DragDropInitiatingStateTestNG::DoMachineAction(machine, testCase.receivedInput);
        } else if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_DRAG_POINTER_EVENT_ARGS) != 0) {
            DragPointerEvent dragPointerEvent;
            DragDropInitiatingStateTestNG::DoMachineAction(machine, testCase.receivedInput, dragPointerEvent);
        } else if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_TOUCH_EVENT_ARGS) != 0) {
            TouchEvent touchEvent;
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
 * @tc.name: DragDropInitiatingStateIdleTestNG002
 * @tc.desc: Test HandleHitTesting function.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateIdleTestNG, DragDropInitiatingStateIdleTestNG002, TestSize.Level1)
{
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
    auto state = machine->dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::IDLE)];
    ASSERT_NE(state, nullptr);
    auto idleState = AceType::DynamicCast<DragDropInitiatingStateIdle>(state);
    ASSERT_NE(idleState, nullptr);
    TouchEvent touchEvent;
    touchEvent.sourceType = SourceType::TOUCH;
    idleState->HandleHitTesting(touchEvent);
    EXPECT_EQ(static_cast<DragDropInitiatingStatus>(machine->currentState_), DragDropInitiatingStatus::READY);

    auto onDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) -> DragDropInfo {
        return {};
    };
    eventHub->SetOnDragStart(std::move(onDragStart));
    EXPECT_EQ(static_cast<DragDropInitiatingStatus>(machine->currentState_), DragDropInitiatingStatus::READY);
}
} // namespace OHOS::Ace::NG