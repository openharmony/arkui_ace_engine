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

const std::vector<DragDropInitiatingStateLiftingTestCase> DRAG_DROP_INITIATING_STATE_PRESS_IMAGE_TEST_CASES = {
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::TOUCH),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::LIFTING, false, false, SourceType::MOUSE),
    DragDropInitiatingStateLiftingTestCase(DragDropInitiatingReceivedInput::HandleHitTesting,
        DragDropInitiatingStatus::LIFTING, true, false, SourceType::MOUSE),
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
        machine->currentState_ = static_cast<int32_t>(testCase.originStatus);
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
} // namespace OHOS::Ace::NG