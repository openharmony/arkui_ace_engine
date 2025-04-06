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

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_handler.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_press.h"
#include "core/event/touch_event.h"
#include "core/gestures/drag_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct DragDropInitiatingStatePressTestCase : public DragDropInitiatingStateTestCase {
    bool isMenuShow = false;
    bool isGatherWithNode = false;
    bool hasGatherNode = false;
    bool isDragNodeNeedClean = false;
    PreDragStatus preDragStatus = PreDragStatus::ACTION_DETECTING_STATUS;
    SourceType sourceType = SourceType::TOUCH;
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput receivedInput,
        DragDropInitiatingStatus expectStatus, bool isMenuShow, bool isGatherWithNode, bool hasGatherNode,
        bool isDragNodeNeedClean, PreDragStatus preDragStatus, SourceType sourceType)
        : DragDropInitiatingStateTestCase(DragDropInitiatingStatus::PRESS, receivedInput, expectStatus),
          isMenuShow(isMenuShow), isGatherWithNode(isGatherWithNode), hasGatherNode(hasGatherNode),
          isDragNodeNeedClean(isDragNodeNeedClean), preDragStatus(preDragStatus), sourceType(sourceType)
    {}
};

const std::vector<DragDropInitiatingStatePressTestCase> DRAG_DROP_INITIATING_STATE_PRESS_IMAGE_TEST_CASES = {
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::PRESS, false, false, false, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::PRESS, false, false, false, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::PRESS, false, false, false, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::MOUSE),

    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePreviewLongPressOnAction,
        DragDropInitiatingStatus::LIFTING, true, true, false, true, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),

    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandleSequenceOnActionCancel,
        DragDropInitiatingStatus::IDLE, false, true, false, true, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandleSequenceOnActionCancel,
        DragDropInitiatingStatus::PRESS, true, true, false, true, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),

    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::PRESS, false, false, false, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::PRESS, false, false, false, true, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::PRESS, false, false, false, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::MOUSE),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionStart,
        DragDropInitiatingStatus::PRESS, false, false, false, true, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::MOUSE),

    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnReject,
        DragDropInitiatingStatus::PRESS, false, false, false, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnReject,
        DragDropInitiatingStatus::PRESS, false, false, true, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnReject,
        DragDropInitiatingStatus::PRESS, false, true, false, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnReject,
        DragDropInitiatingStatus::PRESS, false, true, true, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnReject,
        DragDropInitiatingStatus::PRESS, false, false, true, false, PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION,
        SourceType::TOUCH),

    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandleTouchEvent,
        DragDropInitiatingStatus::PRESS, false, false, true, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),

    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionEnd,
        DragDropInitiatingStatus::IDLE, true, false, false, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
    DragDropInitiatingStatePressTestCase(DragDropInitiatingReceivedInput::HandlePanOnActionEnd,
        DragDropInitiatingStatus::IDLE, true, false, false, false, PreDragStatus::ACTION_DETECTING_STATUS,
        SourceType::TOUCH),
};

void DragDropInitiatingStatePressTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropInitiatingStatePressTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DragDropInitiatingStatePressTestNG001
 * @tc.desc: Test CollectTouchTarget function when frameNode is image.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStatePressTestNG, DragDropInitiatingStatePressTestNG001, TestSize.Level1)
{
    int32_t caseNum = 0;
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    for (const auto& testCase : DRAG_DROP_INITIATING_STATE_PRESS_IMAGE_TEST_CASES) {
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
        overlayManager->SetIsGatherWithMenu(testCase.isGatherWithNode);
        machine->dragDropInitiatingParams_.hasGatherNode = testCase.hasGatherNode;
        dragDropManager->isDragNodeNeedClean_ = testCase.isDragNodeNeedClean;
        DragDropGlobalController::GetInstance().UpdateMenuShowingStatus(testCase.isMenuShow);
        DragDropGlobalController::GetInstance().SetPreDragStatus(testCase.preDragStatus);
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
} // namespace OHOS::Ace::NG