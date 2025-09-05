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
#include "core/gestures/drag_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

struct DragDropInitiatingStateMachineTestCase : public DragDropInitiatingStateTestCase {
    bool nextStatusInit = false;
    DragDropInitiatingStateMachineTestCase(DragDropInitiatingStatus originStatus,
        DragDropInitiatingReceivedInput receivedInput, DragDropInitiatingStatus expectStatus, bool nextStatusInit)
        : DragDropInitiatingStateTestCase(originStatus, receivedInput, expectStatus), nextStatusInit(nextStatusInit)
    {}
};

const std::vector<DragDropInitiatingStateMachineTestCase> DRAG_DROP_INITIATING_STATE_MACHINE_IMAGE_TEST_CASES = {
    DragDropInitiatingStateMachineTestCase(DragDropInitiatingStatus::IDLE,
        DragDropInitiatingReceivedInput::HandleLongPressOnAction, DragDropInitiatingStatus::IDLE, true),
    DragDropInitiatingStateMachineTestCase(DragDropInitiatingStatus::IDLE,
        DragDropInitiatingReceivedInput::HandleLongPressOnAction, DragDropInitiatingStatus::IDLE, false),
};

void DragDropInitiatingStateMachineTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragDropInitiatingStateMachineTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DragDropInitiatingStateMachineTestNG001
 * @tc.desc: Test CollectTouchTarget function when frameNode is image.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateMachineTestNG, DragDropInitiatingStateMachineTestNG001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_DROP_INITIATING_STATE_MACHINE_IMAGE_TEST_CASES) {
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
        EXPECT_TRUE(DragDropInitiatingStateTestNG::CheckDragDropInitiatingStatus(
            caseNum, static_cast<DragDropInitiatingStatus>(machine->currentState_), testCase.expectStatus));
        caseNum++;
    }
}

/**
 * @tc.name: DragDropInitiatingStateMachineTestNG002
 * @tc.desc: Test TransMenuShow function when isMenuShow is false.
 * @tc.type: FUNC
 */
HWTEST_F(DragDropInitiatingStateMachineTestNG, DragDropInitiatingStateMachineTestNG002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DragDropEventActuator, get DragDropInitiatingStateMachine.
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
    /**
     * @tc.steps: step2. Set currentState_ to READY and call TransMenuShow with false.
     * @tc.expected: step2. the currentState_ is READY.
     */
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::READY);
    EXPECT_EQ(machine->currentState_, static_cast<int32_t>(DragDropInitiatingStatus::READY));
    machine->TransMenuShow(false);
    EXPECT_EQ(machine->currentState_, static_cast<int32_t>(DragDropInitiatingStatus::READY));
    /**
     * @tc.steps: step3. Set currentState_ to LIFTING and call TransMenuShow with false.
     * @tc.expected: step3. the currentState_ is IDLE.
     */
    machine->currentState_ = static_cast<int32_t>(DragDropInitiatingStatus::LIFTING);
    EXPECT_EQ(machine->currentState_, static_cast<int32_t>(DragDropInitiatingStatus::LIFTING));
    machine->TransMenuShow(false);
    EXPECT_EQ(machine->currentState_, static_cast<int32_t>(DragDropInitiatingStatus::IDLE));
}

} // namespace OHOS::Ace::NG