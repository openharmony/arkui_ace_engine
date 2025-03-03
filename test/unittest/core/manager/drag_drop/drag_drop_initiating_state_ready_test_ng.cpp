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
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_ready.h"
#include "core/event/touch_event.h"
#include "core/gestures/drag_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct DragDropInitiatingStateReadyTestCase : public DragDropInitiatingStateTestCase {
    bool isDragging = false;
    bool isDragNodeNeedClean = false;
    bool isGatherWithMenu = false;
    bool isBindContextMenu = false;
    int32_t dragPointerId = 0;
    SourceType sourceType = SourceType::TOUCH;
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput receivedInput,
        DragDropInitiatingStatus expectStatus, bool isDragging, bool isDragNodeNeedClean, bool isGatherWithMenu,
        bool isBindContextMenu, int32_t dragPointerId, SourceType sourceType)
        : DragDropInitiatingStateTestCase(DragDropInitiatingStatus::READY, receivedInput, expectStatus),
          isDragging(isDragging), isDragNodeNeedClean(isDragNodeNeedClean), isGatherWithMenu(isGatherWithMenu),
          isBindContextMenu(isBindContextMenu), dragPointerId(dragPointerId), sourceType(sourceType)
    {}
};

const std::vector<DragDropInitiatingStateReadyTestCase> DRAG_DROP_INITIATING_STATE_READY_IMAGE_TEST_CASES = {
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, false, false, false, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, false, false, true, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, false, true, false, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, false, true, true, 0, SourceType::TOUCH),

    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, true, false, false, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, true, false, true, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, true, true, false, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, false, true, true, true, 0, SourceType::TOUCH),

    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, false, false, false, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, false, false, true, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, false, true, false, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, false, true, true, 0, SourceType::TOUCH),

    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, true, false, false, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, true, false, true, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, true, true, false, 0, SourceType::TOUCH),
    DragDropInitiatingStateReadyTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::READY, true, true, true, true, 0, SourceType::TOUCH),
};

void DragDropInitiatingStateReadyTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropInitiatingStateReadyTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DragDropInitiatingStateReadyTestNG001
 * @tc.desc: Test DragDropInitiatingStateReady class when frameNode is image.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateReadyTestNG, DragDropInitiatingStateReadyTestNG001, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    pipelineContext->dragDropManager_ = dragDropManager;
    RefPtr<UINode> rootNode = AceType::MakeRefPtr<FrameNode>("root_node", -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(AceType::DynamicCast<FrameNode>(rootNode));
    pipelineContext->overlayManager_ = overlayManager;
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_DROP_INITIATING_STATE_READY_IMAGE_TEST_CASES) {
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

        dragDropManager->ResetDragging(testCase.isDragging ? DragDropMgrState::DRAGGING : DragDropMgrState::IDLE);
        dragDropManager->SetIsDragNodeNeedClean(testCase.isDragNodeNeedClean);
        overlayManager->SetIsGatherWithMenu(testCase.isGatherWithMenu);
        if (testCase.isBindContextMenu) {
            auto focusHub = frameNode->GetOrCreateFocusHub();
            focusHub->SetOnKeyEventInternal([](const KeyEvent& event) { return true; }, OnKeyEventType::CONTEXT_MENU);
        }

        machine->currentState_ = static_cast<int32_t>(testCase.originStatus);
        if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_NONE_ARGS) != 0) {
            DragDropInitiatingStateTestNG::DoMachineAction(machine, testCase.receivedInput);
        } else if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_DRAG_POINTER_EVENT_ARGS) != 0) {
            DragPointerEvent dragPointerEvent;
            dragPointerEvent.pointerId = testCase.dragPointerId;
            DragDropInitiatingStateTestNG::DoMachineAction(machine, testCase.receivedInput, dragPointerEvent);
        } else if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_TOUCH_EVENT_ARGS) != 0) {
            TouchEvent touchEvent;
            touchEvent.id = testCase.dragPointerId;
            touchEvent.sourceType = testCase.sourceType;
            DragDropInitiatingStateTestNG::DoMachineAction(machine, testCase.receivedInput, touchEvent);
        } else if (((static_cast<int32_t>(testCase.receivedInput)) & DRAG_ACTION_GESTURE_EVENT_ARGS) != 0) {
            GestureEvent info;
            info.SetPointerId(testCase.dragPointerId);
            info.SetSourceDevice(testCase.sourceType);
            DragDropInitiatingStateTestNG::DoMachineAction(machine, testCase.receivedInput, info);
        }
        EXPECT_TRUE(DragDropInitiatingStateTestNG::CheckDragDropInitiatingStatus(
            caseNum, static_cast<DragDropInitiatingStatus>(machine->currentState_), testCase.expectStatus));
        caseNum++;
    }
}

} // namespace OHOS::Ace::NG