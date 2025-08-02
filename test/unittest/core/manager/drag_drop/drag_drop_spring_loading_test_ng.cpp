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

#include "drag_drop_spring_loading_test_ng.h"

#include <cstdint>

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SEQUENCE_INIT = -1;
constexpr int32_t SEQUENCE_ZERO = 0;
constexpr int32_t SEQUENCE_ONCE = 1;
constexpr int32_t SEQUENCE_FOURTH = 4;
constexpr int32_t DOUBLE = 2;
constexpr uint64_t SHORT_TIME = 100;
constexpr uint64_t LONG_TIME = 10000;
constexpr size_t SM_POOL_SIZE = 5;

const Point FIRST_POINT(50, 50);
const Point SECOND_POINT(60, 50);
const Point THIRD_POINT(50, 60);
} // namespace

void DragSpringLoadingTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragSpringLoadingTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DragSpringLoadingTestNg::SetUp()
{
    detector_ = AceType::MakeRefPtr<DragDropSpringLoadingDetector>();
    dragFrameNode_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(dragFrameNode_, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(FRAME_SIZE);
    dragFrameNode_->SetGeometryNode(geometryNode);
    dropFrameNode_ = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto dropGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(FRAME_SIZE * DOUBLE);
    dropFrameNode_->SetGeometryNode(dropGeometryNode);

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    detector_->stateMachine_->taskExecutor_ =
        SingleTaskExecutor::Make(pipeline->taskExecutor_, TaskExecutor::TaskType::UI);
    auto now = std::chrono::system_clock::now();
    curTimeStamp_ =
        static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());
}

const std::vector<DragDropSpringLoadingDetectorTestCase> DRAG_DROP_SPRING_LOADING_DETECTOR_TEST_CASES = {
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, false, false,
        false, { false, false }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, false, false,
        false, { true, false }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, false),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::END, SEQUENCE_FOURTH, FIRST_POINT, true, false,
        false, { true, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::END, SEQUENCE_FOURTH, FIRST_POINT, true, false,
        true),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, true, false,
        true, { false, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::END, SEQUENCE_FOURTH, FIRST_POINT, true, true,
        true, { false, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::END, SEQUENCE_INIT, FIRST_POINT, true, true, true,
        { false, false }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::END, SEQUENCE_FOURTH, FIRST_POINT, true, true,
        true, { false, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::END, SEQUENCE_FOURTH, FIRST_POINT, true, true,
        true, { false, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_MOVE,
        DragDropSpringLoadingState::CANCEL, DragDropSpringLoadingState::END, SEQUENCE_FOURTH, FIRST_POINT, true, true,
        true, { false, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_INTERCEPT,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, false, false,
        false, { false, false }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_INTERCEPT,
        DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, false, false,
        true, { false, false }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_INTERCEPT,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, false, false,
        true, { false, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_INTERCEPT,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, true, false,
        true, { true, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_INTERCEPT,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, true, false,
        true, { true, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_INTERCEPT,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, true, false,
        true, { true, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::NOTIFY_INTERCEPT,
        DragDropSpringLoadingState::CANCEL, DragDropSpringLoadingState::CANCEL, SEQUENCE_INIT, FIRST_POINT, true, false,
        true, { true, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::THRESHOLD,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::END, SEQUENCE_INIT, FIRST_POINT, true, false, true,
        { true, true }, { false, false }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::THRESHOLD,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::END, SEQUENCE_INIT, FIRST_POINT, true, false, true,
        { true, true }, { true, false }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::THRESHOLD,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::END, SEQUENCE_INIT, FIRST_POINT, true, false, true,
        { true, true }, { true, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::THRESHOLD,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::END, SEQUENCE_INIT, FIRST_POINT, true, true, true,
        { true, true }, { true, true }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::THRESHOLD,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::END, SEQUENCE_INIT, FIRST_POINT, true, true, true,
        { true, true }, { true, false }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::INTERCEPT,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, true, true, true,
        { true, true }, { true, false }),
    DragDropSpringLoadingDetectorTestCase(DragDropSpringLoadingReceivedInput::INTERCEPT,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::IDLE, SEQUENCE_INIT, FIRST_POINT, false, false,
        false, { true, true }, { true, false }),
};

const std::vector<DragDropSpringLoadingStateHandler> DRAG_DROP_SPRING_LOADING_STATE_HANDLER_TEST_CASES = {
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::IDLE_ON_ENTER,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::END, true, SEQUENCE_FOURTH),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::IDLE_ON_ENTER,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::BEGIN, false, SEQUENCE_INIT),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::BEGIN_ON_ENTER,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::BEGIN, false, SEQUENCE_INIT),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::BEGIN_ON_ENTER,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::BEGIN, true, SEQUENCE_ZERO, false,
        { true, false }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::BEGIN_ON_ENTER,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::IDLE, true, SEQUENCE_INIT, true,
        { true, false }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::BEGIN_ON_ENTER,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::IDLE, true, SEQUENCE_INIT, true,
        { false, false }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::BEGIN_ON_ENTER,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::IDLE, true, SEQUENCE_INIT, true, { true, true }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::BEGIN_ON_ENTER,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::IDLE, true, SEQUENCE_INIT, true,
        { true, false, false }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::BEGIN_ON_ENTER,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::IDLE, true, SEQUENCE_INIT, true,
        { true, false, true }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::BEGIN_ON_ENTER,
        DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::END, true, SEQUENCE_ONCE, false,
        { false, false }, SEQUENCE_ZERO),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::UPDATE_ON_ENTER,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::BEGIN, false, SEQUENCE_INIT),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::UPDATE_ON_ENTER,
        DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::UPDATE, true, SEQUENCE_ZERO, false,
        { true, false }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::UPDATE_ON_ENTER,
        DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::IDLE, true, SEQUENCE_INIT, true,
        { true, false }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::UPDATE_ON_ENTER,
        DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::IDLE, true, SEQUENCE_INIT, true,
        { false, false }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::UPDATE_ON_ENTER,
        DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::END, true, SEQUENCE_ONCE, false,
        { false, false }, SEQUENCE_ZERO),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::UPDATE_ON_ENTER,
        DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::UPDATE, true, SEQUENCE_ZERO, false,
        { true, false }, SEQUENCE_ZERO),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::END_ON_ENTER,
        DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::BEGIN, false, SEQUENCE_INIT),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::UPDATE_ON_ENTER,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::END, true, SEQUENCE_ZERO, false, { true, false }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::UPDATE_ON_ENTER,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::IDLE, true, SEQUENCE_INIT, true, { true, false }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::UPDATE_ON_ENTER,
        DragDropSpringLoadingState::END, DragDropSpringLoadingState::IDLE, true, SEQUENCE_INIT, true, { false, false }),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::CANCEL_ON_ENTER,
        DragDropSpringLoadingState::CANCEL, DragDropSpringLoadingState::CANCEL, false, SEQUENCE_INIT),
    DragDropSpringLoadingStateHandler(DragDropSpringLoadingReceivedInput::CANCEL_ON_ENTER,
        DragDropSpringLoadingState::CANCEL, DragDropSpringLoadingState::IDLE, true, SEQUENCE_INIT, false,
        { false, false }),
};

testing::AssertionResult DragSpringLoadingTestNg::CheckDragDropSpringLoadingStatus(
    int32_t caseNum, DragDropSpringLoadingState currentStatus, DragDropSpringLoadingState expectStatus)
{
    if (currentStatus == expectStatus) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "TestCaseNum: " << caseNum
                                       << ", actual state: " << static_cast<int32_t>(currentStatus)
                                       << ", expect state: " << static_cast<int32_t>(expectStatus);
}

testing::AssertionResult DragSpringLoadingTestNg::CheckDragDropSpringLoadingNotifySequence(
    int32_t caseNum, int32_t notifySequence, int32_t expectNotifySequence)
{
    if (notifySequence == expectNotifySequence) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "TestCaseNum: " << caseNum
                                       << ", actual notifySequence: " << static_cast<int32_t>(notifySequence)
                                       << ", expect notifySequence: " << static_cast<int32_t>(expectNotifySequence);
}

void DragSpringLoadingTestNg::HandleMoveInput(const DragDropSpringLoadingDetectorTestCase& testCase)
{
    RefPtr<FrameNode> dropFrameNode = nullptr;
    if (testCase.hasCallback) {
        dropFrameNode_->eventHub_->SetCustomerOnDragSpringLoading(
            [](const RefPtr<DragSpringLoadingContext>& info) { ASSERT_NE(info, nullptr); });
    }
    if (testCase.hasDefaultFrameNode) {
        dragFrameNode_->eventHub_ = AceType::MakeRefPtr<EventHub>();
        detector_->preTargetFrameNode_ = dragFrameNode_;
        if (!testCase.paramsTestCase.hasFrameNode) {
            dropFrameNode = dragFrameNode_;
            dropFrameNode->eventHub_->SetCustomerOnDragSpringLoading(
                [](const RefPtr<DragSpringLoadingContext>& info) { ASSERT_NE(info, nullptr); });
        }
    }
    if (testCase.paramsTestCase.hasFrameNode) {
        dropFrameNode = dropFrameNode_;
        if (!testCase.paramsTestCase.hasEventHub) {
            dropFrameNode->eventHub_ = nullptr;
        }
    }
    if (!testCase.isMovementExceedThreshold) {
        detector_->preMovePoint_ = testCase.movePoint;
        detector_->preTimeStamp_ = curTimeStamp_;
    } else {
        detector_->preMovePoint_ = Point(0, 0);
        detector_->preTimeStamp_ = curTimeStamp_ - SHORT_TIME;
    }
    detector_->NotifyMove({ testCase.movePoint, dropFrameNode, curTimeStamp_, testCase.extraInfo });
}

void DragSpringLoadingTestNg::HandleNotifyInterceptInput(const DragDropSpringLoadingDetectorTestCase& testCase)
{
    if (testCase.hasDefaultFrameNode) {
        detector_->preTargetFrameNode_ = dropFrameNode_;
        if (!testCase.paramsTestCase.hasEventHub) {
            detector_->preTargetFrameNode_->eventHub_ = nullptr;
        } else if (testCase.hasCallback) {
            detector_->preTargetFrameNode_->eventHub_->SetCustomerOnDragSpringLoading(
                [](const RefPtr<DragSpringLoadingContext>& info) { ASSERT_NE(info, nullptr); });
        }
    }
    detector_->NotifyIntercept(testCase.extraInfo);
}

void DragSpringLoadingTestNg::HandleThresholdInput(const DragDropSpringLoadingDetectorTestCase& testCase)
{
    if (!testCase.isMovementExceedThreshold) {
        if (testCase.preInfoTestCase.hasPreTimeStamp) {
            detector_->preTimeStamp_ = curTimeStamp_;
        }
        if (testCase.preInfoTestCase.hasPreMovePoint) {
            detector_->preTimeStamp_ = curTimeStamp_ - LONG_TIME;
        }
    } else {
        if (testCase.preInfoTestCase.hasPreMovePoint) {
            detector_->preMovePoint_ = SECOND_POINT;
        } else {
            detector_->preMovePoint_ = THIRD_POINT;
        }
        detector_->preTimeStamp_ = curTimeStamp_ - SHORT_TIME;
    }
    detector_->IsMovementExceedThreshold(curTimeStamp_, testCase.movePoint);
}

void HandleDragSpringLoadingCallback(
    const RefPtr<DragSpringLoadingContext>& info, const DragDropSpringLoadingStateHandler& testCase)
{
    ASSERT_NE(info, nullptr);
    auto config = info->GetDragSpringLoadingConfiguration();
    ASSERT_NE(config, nullptr);

    config->updateNotifyCount = testCase.updateNotifyCount;
    info->SetDragSpringLoadingConfiguration(config);

    if (testCase.abort) {
        info->SetSpringLoadingAborted();
    }
}

void DragSpringLoadingTestNg::SetupTestCaseConditions(const DragDropSpringLoadingStateHandler& testCase)
{
    auto machine = detector_->stateMachine_;
    if (testCase.hasCallback) {
        dropFrameNode_->eventHub_->SetCustomerOnDragSpringLoading(
            [testCase](
                const RefPtr<DragSpringLoadingContext>& info) { HandleDragSpringLoadingCallback(info, testCase); });
    }
    if ((static_cast<int32_t>(testCase.receivedInput) & DRAG_DROP_SPRING_LOADING_DETECTOR_SET_USERCONFIG) != 0) {
        auto relatedConfigurations = dropFrameNode_->GetOrCreateDragDropRelatedConfigurations();
        ASSERT_NE(relatedConfigurations, nullptr);
        machine->SetUserConfig(relatedConfigurations->GetOrCreateDragSpringLoadingConfiguration());
    }
    if (testCase.springLoadingMachineTestCase.transitionFailed) {
        if (testCase.springLoadingMachineTestCase.isAllowedTransition) {
            machine->stateMachinePool_->states_[DragDropSpringLoadingState::CANCEL].stateHandler = nullptr;
        } else {
            if (testCase.springLoadingMachineTestCase.isAllowedTransitionFind) {
                machine->stateMachinePool_->states_[testCase.originStatus].transitions.clear();
            } else {
                machine->stateMachinePool_->states_.erase(testCase.originStatus);
            }
        }
    } else {
        if (testCase.originStatus == DragDropSpringLoadingState::END) {
            machine->stateMachinePool_->states_[testCase.originStatus].transitions.emplace_back(
                DragDropSpringLoadingState::CANCEL);
        }
    }
}

/**
 * @tc.name: DragSpringLoadingTest001
 * @tc.desc: Test State Machine RegisterStateHandler
 * @tc.type: FUNC
 */
HWTEST_F(DragSpringLoadingTestNg, DragSpringLoadingTest001, TestSize.Level1)
{
    ASSERT_NE(detector_, nullptr);
    auto smPool = detector_->stateMachine_->stateMachinePool_;
    ASSERT_TRUE(smPool);
    EXPECT_EQ(smPool->states_.size(), SM_POOL_SIZE);

    EXPECT_TRUE(smPool->IsAllowedTransition(DragDropSpringLoadingState::IDLE, DragDropSpringLoadingState::BEGIN));

    EXPECT_TRUE(smPool->IsAllowedTransition(DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::UPDATE));
    EXPECT_TRUE(smPool->IsAllowedTransition(DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::END));
    EXPECT_TRUE(smPool->IsAllowedTransition(DragDropSpringLoadingState::BEGIN, DragDropSpringLoadingState::CANCEL));

    EXPECT_TRUE(smPool->IsAllowedTransition(DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::UPDATE));
    EXPECT_TRUE(smPool->IsAllowedTransition(DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::END));
    EXPECT_TRUE(smPool->IsAllowedTransition(DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::CANCEL));

    EXPECT_TRUE(smPool->IsAllowedTransition(DragDropSpringLoadingState::END, DragDropSpringLoadingState::IDLE));

    EXPECT_TRUE(smPool->IsAllowedTransition(DragDropSpringLoadingState::CANCEL, DragDropSpringLoadingState::IDLE));
}

/**
 * @tc.name: DragSpringLoadingTest002
 * @tc.desc: Test DragDropSpringLoadingDetector
 * @tc.type: FUNC
 */
HWTEST_F(DragSpringLoadingTestNg, DragSpringLoadingTest002, TestSize.Level1)
{
    ASSERT_NE(detector_, nullptr);
    ASSERT_NE(dropFrameNode_, nullptr);
    ASSERT_NE(dragFrameNode_, nullptr);
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_DROP_SPRING_LOADING_DETECTOR_TEST_CASES) {
        dropFrameNode_->eventHub_ = AceType::MakeRefPtr<EventHub>();
        auto machine = detector_->stateMachine_;
        ASSERT_NE(machine, nullptr);
        machine->ResetMachine();
        detector_->ResetState();
        detector_->preTargetFrameNode_ = nullptr;
        detector_->preMovePoint_ = Point(0, 0);
        detector_->preTimeStamp_ = 0;
        machine->currentState_ = testCase.originStatus;
        if (testCase.originStatus == DragDropSpringLoadingState::IDLE) {
            machine->isWaitingForIdleFinish_ = true;
        }
        if (testCase.receivedInput == DragDropSpringLoadingReceivedInput::NOTIFY_MOVE) {
            HandleMoveInput(testCase);
        } else if (testCase.receivedInput == DragDropSpringLoadingReceivedInput::NOTIFY_INTERCEPT) {
            HandleNotifyInterceptInput(testCase);
        } else if (testCase.receivedInput == DragDropSpringLoadingReceivedInput::THRESHOLD) {
            HandleThresholdInput(testCase);
        } else if (testCase.receivedInput == DragDropSpringLoadingReceivedInput::INTERCEPT) {
            if (machine->IsInSpringLoadingState()) {
                machine->stateMachinePool_->states_[testCase.originStatus].transitions.clear();
            }
            detector_->Intercept(testCase.extraInfo);
        }
        EXPECT_TRUE(DragSpringLoadingTestNg::CheckDragDropSpringLoadingStatus(
            caseNum, machine->currentState_, testCase.expectStatus));
        EXPECT_TRUE(DragSpringLoadingTestNg::CheckDragDropSpringLoadingNotifySequence(
            caseNum, machine->GetCurrentNotifySequence(), testCase.notifySequence));
        caseNum++;
    }
}

/**
 * @tc.name: DragSpringLoadingTest003
 * @tc.desc: Test DragDropSpringLoadingState Handler
 * @tc.type: FUNC
 */
HWTEST_F(DragSpringLoadingTestNg, DragSpringLoadingTest003, TestSize.Level1)
{
    ASSERT_NE(dropFrameNode_, nullptr);
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_DROP_SPRING_LOADING_STATE_HANDLER_TEST_CASES) {
        detector_ = AceType::MakeRefPtr<DragDropSpringLoadingDetector>();
        auto machine = detector_->stateMachine_;
        ASSERT_NE(machine, nullptr);
        machine->ResetMachine();
        ASSERT_NE(machine->stateMachinePool_, nullptr);
        detector_->ResetState();
        detector_->preTargetFrameNode_ = dropFrameNode_;
        detector_->preMovePoint_ = Point(0, 0);
        detector_->preTimeStamp_ = 0;
        machine->currentState_ = testCase.originStatus;
        dropFrameNode_->eventHub_ = AceType::MakeRefPtr<EventHub>();
        SetupTestCaseConditions(testCase);
        auto handler = machine->stateMachinePool_->GetStateHandler(testCase.originStatus);
        if (testCase.springLoadingMachineTestCase.transitionFailed &&
            !testCase.springLoadingMachineTestCase.isAllowedTransitionFind) {
            ASSERT_EQ(handler, nullptr);
            EXPECT_FALSE(machine->stateMachinePool_->IsAllowedTransition(testCase.originStatus, testCase.expectStatus));
            caseNum++;
            continue;
        }
        ASSERT_NE(handler, nullptr);
        handler->OnEnter(testCase.extraInfo);
        EXPECT_TRUE(DragSpringLoadingTestNg::CheckDragDropSpringLoadingStatus(
            caseNum, machine->currentState_, testCase.expectStatus));
        EXPECT_TRUE(DragSpringLoadingTestNg::CheckDragDropSpringLoadingNotifySequence(
            caseNum, machine->GetCurrentNotifySequence(), testCase.notifySequence));
        caseNum++;
    }
}

/**
 * @tc.name: DragSpringLoadingTest004
 * @tc.desc: Test NotifyMove
 * @tc.type: FUNC
 */
 HWTEST_F(DragSpringLoadingTestNg, DragSpringLoadingTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize detector.
     */
    ASSERT_NE(detector_, nullptr);
    ASSERT_NE(dropFrameNode_, nullptr);
    ASSERT_NE(dragFrameNode_, nullptr);
    dropFrameNode_->eventHub_ = AceType::MakeRefPtr<EventHub>();
    auto machine = detector_->stateMachine_;
    ASSERT_NE(machine, nullptr);
    machine->ResetMachine();
    detector_->ResetState();
    dragFrameNode_->eventHub_ = AceType::MakeRefPtr<EventHub>();
    detector_->preTargetFrameNode_ = dropFrameNode_;
    detector_->preMovePoint_ = Point(0, 0);
    detector_->preTimeStamp_ = 0;
    machine->currentState_ = DragDropSpringLoadingState::BEGIN;

    /**
     * @tc.steps: step2. call NotifyIntercept.
     */
    detector_->NotifyIntercept("");
    EXPECT_EQ(detector_->preTargetFrameNode_, nullptr);

    detector_->preTargetFrameNode_ = dropFrameNode_;
    detector_->preTargetFrameNode_->eventHub_->SetCustomerOnDragSpringLoading(
                            [](const RefPtr<DragSpringLoadingContext>& info) { ASSERT_NE(info, nullptr); });
    machine->stateMachinePool_ = nullptr;
    detector_->NotifyIntercept("");
    EXPECT_EQ(machine->currentState_, DragDropSpringLoadingState::IDLE);

    detector_->preTargetFrameNode_ = dropFrameNode_;
    machine->isWaitingForIdleFinish_ = true;
    detector_->NotifyIntercept("");
    EXPECT_FALSE(machine->isWaitingForIdleFinish_);
}
} // namespace OHOS::Ace::NG
