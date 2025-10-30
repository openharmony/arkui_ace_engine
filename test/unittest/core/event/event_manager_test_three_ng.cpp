/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "test/unittest/core/event/event_manager_test_ng.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
void EventManagerTestThreeNg::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = nullptr;
    MOCK_TASK_EXECUTOR = AceType::MakeRefPtr<MockTaskExecutor>();
}

void EventManagerTestThreeNg::TearDownTestSuite()
{
    MockContainer::TearDown();
}

/**
 * @tc.name: ExclusiveRecognizerAxisDirection001
 * @tc.desc: Test GetAxisDirection() of ExclusiveRecognizer.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, ExclusiveRecognizerAxisDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pan recognizers.
     * @tc.expected: recognizers is not null and axis direction is correct.
     */
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal1, nullptr);
    auto panHorizontal2 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal2, nullptr);

    auto panVertical1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::VERTICAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panVertical1, nullptr);
    auto panVertical2 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::VERTICAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panVertical2, nullptr);

    auto panFree1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::ALL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panFree1, nullptr);
    auto panFree2 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::ALL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panFree2, nullptr);

    /**
     * @tc.steps: step2. Create exclusive recognizers.
     * @tc.expected: recognizers is not null and axis direction is correct.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers;
    recognizers.clear();
    recognizers.emplace_back(panHorizontal1);
    recognizers.emplace_back(panHorizontal2);
    auto exclusiveDoubleHorizontal = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    ASSERT_NE(exclusiveDoubleHorizontal, nullptr);
    EXPECT_EQ(exclusiveDoubleHorizontal->GetAxisDirection(), Axis::HORIZONTAL);

    recognizers.clear();
    recognizers.emplace_back(panVertical1);
    recognizers.emplace_back(panVertical2);
    auto exclusiveDoubleVertical = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    ASSERT_NE(exclusiveDoubleVertical, nullptr);
    EXPECT_EQ(exclusiveDoubleVertical->GetAxisDirection(), Axis::VERTICAL);

    recognizers.clear();
    recognizers.emplace_back(panFree1);
    recognizers.emplace_back(panFree2);
    auto exclusiveDoubleFree = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    ASSERT_NE(exclusiveDoubleFree, nullptr);
    EXPECT_EQ(exclusiveDoubleFree->GetAxisDirection(), Axis::FREE);

    recognizers.clear();
    recognizers.emplace_back(panHorizontal1);
    recognizers.emplace_back(panVertical1);
    auto exclusiveHorizontalVertical = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    ASSERT_NE(exclusiveHorizontalVertical, nullptr);
    EXPECT_EQ(exclusiveHorizontalVertical->GetAxisDirection(), Axis::FREE);

    recognizers.clear();
    recognizers.emplace_back(panHorizontal1);
    recognizers.emplace_back(panFree1);
    auto exclusiveHorizontalFree = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    ASSERT_NE(exclusiveHorizontalFree, nullptr);
    EXPECT_EQ(exclusiveHorizontalFree->GetAxisDirection(), Axis::FREE);

    recognizers.clear();
    recognizers.emplace_back(panVertical1);
    recognizers.emplace_back(panFree1);
    auto exclusiveVerticalFree = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    ASSERT_NE(exclusiveVerticalFree, nullptr);
    EXPECT_EQ(exclusiveVerticalFree->GetAxisDirection(), Axis::FREE);
}

/**
 * @tc.name: ParallelRecognizerAxisDirection001
 * @tc.desc: Test GetAxisDirection() of ParallelRecognizer.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, ParallelRecognizerAxisDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pan recognizers.
     * @tc.expected: recognizers is not null and axis direction is correct.
     */
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal1, nullptr);
    auto panHorizontal2 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal2, nullptr);

    auto panVertical1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::VERTICAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panVertical1, nullptr);
    auto panVertical2 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::VERTICAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panVertical2, nullptr);

    auto panFree1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::ALL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panFree1, nullptr);
    auto panFree2 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::ALL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panFree2, nullptr);

    /**
     * @tc.steps: step2. Create parallel recognizers.
     * @tc.expected: recognizers is not null and axis direction is correct.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers;
    recognizers.clear();
    recognizers.emplace_back(panHorizontal1);
    recognizers.emplace_back(panHorizontal2);
    auto parallelDoubleHorizontal = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    ASSERT_NE(parallelDoubleHorizontal, nullptr);
    EXPECT_EQ(parallelDoubleHorizontal->GetAxisDirection(), Axis::HORIZONTAL);

    recognizers.clear();
    recognizers.emplace_back(panVertical1);
    recognizers.emplace_back(panVertical2);
    auto parallelDoubleVertical = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    ASSERT_NE(parallelDoubleVertical, nullptr);
    EXPECT_EQ(parallelDoubleVertical->GetAxisDirection(), Axis::VERTICAL);

    recognizers.clear();
    recognizers.emplace_back(panFree1);
    recognizers.emplace_back(panFree2);
    auto parallelDoubleFree = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    ASSERT_NE(parallelDoubleFree, nullptr);
    EXPECT_EQ(parallelDoubleFree->GetAxisDirection(), Axis::FREE);

    recognizers.clear();
    recognizers.emplace_back(panHorizontal1);
    recognizers.emplace_back(panVertical1);
    auto parallelHorizontalVertical = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    ASSERT_NE(parallelHorizontalVertical, nullptr);
    EXPECT_EQ(parallelHorizontalVertical->GetAxisDirection(), Axis::FREE);

    recognizers.clear();
    recognizers.emplace_back(panHorizontal1);
    recognizers.emplace_back(panFree1);
    auto parallelHorizontalFree = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    ASSERT_NE(parallelHorizontalFree, nullptr);
    EXPECT_EQ(parallelHorizontalFree->GetAxisDirection(), Axis::FREE);

    recognizers.clear();
    recognizers.emplace_back(panVertical1);
    recognizers.emplace_back(panFree1);
    auto parallelVerticalFree = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    ASSERT_NE(parallelVerticalFree, nullptr);
    EXPECT_EQ(parallelVerticalFree->GetAxisDirection(), Axis::FREE);
}

/**
 * @tc.name: EventManagerTest090
 * @tc.desc: Test DispatchMouseEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, EventManagerTest090, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    MouseEvent event;
    event.mockFlushEvent = true;
    bool result = eventManager->DispatchMouseEventNG(event);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: EventManagerTest091
 * @tc.desc: Test DispatchMouseEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, EventManagerTest091, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    MouseEvent event;
    event.mockFlushEvent = false;
    bool result = eventManager->DispatchMouseEventNG(event);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: EventManagerTest092
 * @tc.desc: Test CheckAndLogLastReceivedTouchEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, EventManagerTest092, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int32_t eventId = 1;
    auto type = TouchType::MOVE;
    eventManager->CheckAndLogLastReceivedTouchEventInfo(eventId, type);
    EXPECT_EQ(eventManager->lastReceivedEvent_.eventId, eventId);
}

/**
 * @tc.name: EventManagerTest093
 * @tc.desc: Test CheckAndLogLastConsumedTouchEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, EventManagerTest093, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int32_t eventId = 1;
    auto type = TouchType::MOVE;
    eventManager->CheckAndLogLastConsumedTouchEventInfo(eventId, type);
    EXPECT_EQ(eventManager->lastConsumedEvent_.eventId, eventId);
}

/**
 * @tc.name: EventManagerTest094
 * @tc.desc: Test CheckAndLogLastReceivedMouseEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, EventManagerTest094, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int32_t eventId = 1;
    auto action = MouseAction::MOVE;
    eventManager->CheckAndLogLastReceivedMouseEventInfo(eventId, action);
    EXPECT_EQ(eventManager->lastReceivedEvent_.eventId, eventId);
}

/**
 * @tc.name: EventManagerTest095
 * @tc.desc: Test CheckAndLogLastConsumedMouseEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, EventManagerTest095, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int32_t eventId = 1;
    auto action = MouseAction::MOVE;
    eventManager->CheckAndLogLastConsumedMouseEventInfo(eventId, action);
    EXPECT_EQ(eventManager->lastConsumedEvent_.eventId, eventId);
}

/**
 * @tc.name: EventManagerTest096
 * @tc.desc: Test CheckAndLogLastReceivedAxisEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, EventManagerTest096, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int32_t eventId = 1;
    auto action = AxisAction::NONE;
    eventManager->CheckAndLogLastReceivedAxisEventInfo(eventId, action);
    EXPECT_EQ(eventManager->lastReceivedEvent_.eventId, eventId);
}

/**
 * @tc.name: EventManagerTest097
 * @tc.desc: Test CheckAndLogLastConsumedAxisEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, EventManagerTest097, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int32_t eventId = 1;
    auto action = AxisAction::NONE;
    eventManager->CheckAndLogLastConsumedAxisEventInfo(eventId, action);
    EXPECT_EQ(eventManager->lastConsumedEvent_.eventId, eventId);
}

/**
 * @tc.name: EventManagerTest098
 * @tc.desc: Test RemoveOverlayByESC
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, EventManagerTest098, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    KeyEvent event;

    event.code = KeyCode::KEY_ESCAPE;
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(eventManager->RemoveOverlayByESC(event));
    event.code = KeyCode::KEY_CTRL_LEFT;
    event.action = KeyAction::UP;
    EXPECT_FALSE(eventManager->RemoveOverlayByESC(event));
    event.code = KeyCode::KEY_ESCAPE;
    event.action = KeyAction::UP;
    EXPECT_FALSE(eventManager->RemoveOverlayByESC(event));
    event.code = KeyCode::KEY_CTRL_LEFT;
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(eventManager->RemoveOverlayByESC(event));

    event.code = KeyCode::KEY_ESCAPE;
    event.action = KeyAction::DOWN;

    MockPipelineContext::SetUp();
    MockContainer::SetUp(NG::PipelineContext::GetCurrentContext());
    auto container = MockContainer::Current();

    container->isSubContainer_ = true;
    container->isDialogContainer_ = true;
    EXPECT_FALSE(eventManager->RemoveOverlayByESC(event));
    container->isSubContainer_ = false;
    container->isDialogContainer_ = false;
    EXPECT_FALSE(eventManager->RemoveOverlayByESC(event));
    container->isSubContainer_ = true;
    container->isDialogContainer_ = false;
    EXPECT_FALSE(eventManager->RemoveOverlayByESC(event));
    container->isSubContainer_ = false;
    container->isDialogContainer_ = true;
    EXPECT_FALSE(eventManager->RemoveOverlayByESC(event));
}

/**
 * @tc.name: EventManagerTest099
 * @tc.desc: Test FlushTouchEventsBegin
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestThreeNg, EventManagerTest099, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    AxisEvent axisEvent;
    axisEvent.x = 1;
    axisEvent.y = 2;
    axisEvent.sourceType = SourceType::TOUCH;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    eventManager->axisTestResultsMap_[axisEvent.id].clear();
    eventManager->AxisTest(axisEvent, frameNode);
    EXPECT_FALSE(eventManager->passThroughResult_);
}
} // namespace OHOS::Ace::NG
