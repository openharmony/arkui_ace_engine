/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
/**
 * @tc.name: SequenceRecognizerAxisDirection001
 * @tc.desc: Test GetAxisDirection() of SequenceRecognizer.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, SequenceRecognizerAxisDirection001, TestSize.Level1)
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
     * @tc.steps: step2. Create sequence recognizers.
     * @tc.expected: recognizers is not null and axis direction is correct.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers;
    recognizers.clear();
    recognizers.emplace_back(panHorizontal1);
    recognizers.emplace_back(panHorizontal2);
    auto sequenceDoubleHorizontal = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    ASSERT_NE(sequenceDoubleHorizontal, nullptr);
    EXPECT_EQ(sequenceDoubleHorizontal->GetAxisDirection(), Axis::HORIZONTAL);

    recognizers.clear();
    recognizers.emplace_back(panVertical1);
    recognizers.emplace_back(panVertical2);
    auto sequenceDoubleVertical = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    ASSERT_NE(sequenceDoubleVertical, nullptr);
    EXPECT_EQ(sequenceDoubleVertical->GetAxisDirection(), Axis::VERTICAL);

    recognizers.clear();
    recognizers.emplace_back(panFree1);
    recognizers.emplace_back(panFree2);
    auto sequenceDoubleFree = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    ASSERT_NE(sequenceDoubleFree, nullptr);
    EXPECT_EQ(sequenceDoubleFree->GetAxisDirection(), Axis::FREE);

    recognizers.clear();
    recognizers.emplace_back(panHorizontal1);
    recognizers.emplace_back(panVertical1);
    auto sequenceHorizontalVertical = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    ASSERT_NE(sequenceHorizontalVertical, nullptr);
    EXPECT_EQ(sequenceHorizontalVertical->GetAxisDirection(), Axis::FREE);

    recognizers.clear();
    recognizers.emplace_back(panHorizontal1);
    recognizers.emplace_back(panFree1);
    auto sequenceHorizontalFree = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    ASSERT_NE(sequenceHorizontalFree, nullptr);
    EXPECT_EQ(sequenceHorizontalFree->GetAxisDirection(), Axis::FREE);

    recognizers.clear();
    recognizers.emplace_back(panVertical1);
    recognizers.emplace_back(panFree1);
    auto sequenceVerticalFree = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    ASSERT_NE(sequenceVerticalFree, nullptr);
    EXPECT_EQ(sequenceVerticalFree->GetAxisDirection(), Axis::FREE);
}

/**
 * @tc.name: HasDifferentDirectionGesture001
 * @tc.desc: Test HasDifferentDirectionGesture() of EventManager.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, HasDifferentDirectionGesture001, TestSize.Level1)
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
     * @tc.steps: step2. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchTestResult hitTestResult;

    /**
     * @tc.steps: step3. Add 2 horizontal recognizer to axisTouchTestResults_
     * @tc.expected: axisTouchTestResults_->HasDifferentDirectionGesture() is false.
     */
    hitTestResult.clear();
    eventManager->axisTouchTestResults_.clear();
    hitTestResult.emplace_back(panHorizontal1);
    hitTestResult.emplace_back(panHorizontal2);
    eventManager->axisTouchTestResults_[MOUSE_BASE_ID] = std::move(hitTestResult);
    EXPECT_FALSE(eventManager->HasDifferentDirectionGesture());

    /**
     * @tc.steps: step4. Add 2 vertical recognizer to axisTouchTestResults_
     * @tc.expected: axisTouchTestResults_->HasDifferentDirectionGesture() is false.
     */
    hitTestResult.clear();
    eventManager->axisTouchTestResults_.clear();
    hitTestResult.emplace_back(panVertical1);
    hitTestResult.emplace_back(panVertical2);
    eventManager->axisTouchTestResults_[MOUSE_BASE_ID] = std::move(hitTestResult);
    EXPECT_FALSE(eventManager->HasDifferentDirectionGesture());

    /**
     * @tc.steps: step5. Add horizontal and vertical recognizer to axisTouchTestResults_
     * @tc.expected: axisTouchTestResults_->HasDifferentDirectionGesture() is true.
     */
    hitTestResult.clear();
    eventManager->axisTouchTestResults_.clear();
    hitTestResult.emplace_back(panHorizontal1);
    hitTestResult.emplace_back(panVertical1);
    eventManager->axisTouchTestResults_[MOUSE_BASE_ID] = std::move(hitTestResult);
    EXPECT_TRUE(eventManager->HasDifferentDirectionGesture());

    /**
     * @tc.steps: step6. Add horizontal and free recognizer to axisTouchTestResults_
     * @tc.expected: axisTouchTestResults_->HasDifferentDirectionGesture() is true.
     */
    hitTestResult.clear();
    eventManager->axisTouchTestResults_.clear();
    hitTestResult.emplace_back(panHorizontal1);
    hitTestResult.emplace_back(panFree1);
    eventManager->axisTouchTestResults_[MOUSE_BASE_ID] = std::move(hitTestResult);
    EXPECT_TRUE(eventManager->HasDifferentDirectionGesture());

    /**
     * @tc.steps: step6. Add vertical and free recognizer to axisTouchTestResults_
     * @tc.expected: axisTouchTestResults_->HasDifferentDirectionGesture() is true.
     */
    hitTestResult.clear();
    eventManager->axisTouchTestResults_.clear();
    hitTestResult.emplace_back(panVertical1);
    hitTestResult.emplace_back(panFree1);
    eventManager->axisTouchTestResults_[MOUSE_BASE_ID] = std::move(hitTestResult);
    EXPECT_TRUE(eventManager->HasDifferentDirectionGesture());

    /**
     * @tc.steps: step6. Add free and free recognizer to axisTouchTestResults_
     * @tc.expected: axisTouchTestResults_->HasDifferentDirectionGesture() is true.
     */
    hitTestResult.clear();
    eventManager->axisTouchTestResults_.clear();
    hitTestResult.emplace_back(panFree1);
    hitTestResult.emplace_back(panFree2);
    eventManager->axisTouchTestResults_[MOUSE_BASE_ID] = std::move(hitTestResult);
    EXPECT_TRUE(eventManager->HasDifferentDirectionGesture());
}

/**
 * @tc.name: EventManagerTest038
 * @tc.desc: Test DispatchRotationEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchRotationEvent.
     * @tc.expected: ret is false.
     */
    RotationEvent event;
    event.value = 0.1;
    auto animatablePoperties = AceType::MakeRefPtr<OHOS::Ace::AnimatableProperties>();
    auto renderNode = AceType::DynamicCast<RenderNode>(animatablePoperties);
    const RefPtr<RenderNode> requestNode = nullptr;
    auto ret = eventManager->DispatchRotationEvent(event, renderNode, requestNode);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: EventManagerTest039
 * @tc.desc: Test PostEventDispatchTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(CONTAINER_INSTANCE_ID, MockContainer::container_);

    /**
     * @tc.steps: step2. Call PostEventDispatchTouchEvent with event.
     * @tc.expected: ret is true
     */
    TouchEvent event;
    event.type = TouchType::DOWN;
    TouchTestResult touchTestResults;
    auto eventTarget = AceType::MakeRefPtr<MockTouchEventTarget>();
    touchTestResults.push_back(eventTarget);
    eventManager->postEventTouchTestResults_.emplace(event.id, touchTestResults);
    auto ret = eventManager->PostEventDispatchTouchEvent(event);
    EXPECT_TRUE(ret);

    /**
    * @tc.steps: step3. Call PostEventDispatchTouchEvent event.
    * @tc.expected: ret is true
    */
    event.type = TouchType::UP;
    touchTestResults.push_back(eventTarget);
    eventManager->postEventTouchTestResults_.emplace(event.id, touchTestResults);
    ret = eventManager->PostEventDispatchTouchEvent(event);
    EXPECT_TRUE(ret);

    /**
    * @tc.steps: step4. Call PostEventDispatchTouchEvent event.
    * @tc.expected: ret is true
    */
    event.type = TouchType::CANCEL;
    touchTestResults.push_back(eventTarget);
    eventManager->postEventTouchTestResults_.emplace(event.id, touchTestResults);
    ret = eventManager->PostEventDispatchTouchEvent(event);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: EventManagerTest040
 * @tc.desc: Test DispatchMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseEvent.
     * @tc.expected: retFlag is true.
     */
    MouseEvent event;
    event.action = MouseAction::MOVE;
    bool retFlag = eventManager->DispatchMouseEvent(event);
    ASSERT_TRUE(retFlag);
}

/**
 * @tc.name: EventManagerTest041
 * @tc.desc: Test HandleGlobalEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Create FrameNode and Call TouchTest to add touchTestResults_[touchPoint.id].
     * @tc.expected: touchTestResults_ has the touchPoint.id of instance.
     */
    TouchEvent touchPoint;
    touchPoint.id = 1000;
    touchPoint.type = TouchType::DOWN;

    const int nodeId = 10003;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;
    Offset offset;

    eventManager->TouchTest(touchPoint, frameNode, touchRestrict, offset, 0, true);
    EXPECT_GT(eventManager->touchTestResults_.count(touchPoint.id), 0);
    TouchTestResult touchTestResults;
    auto eventTarget = AceType::MakeRefPtr<MockTouchEventTarget>();
    touchTestResults.push_back(eventTarget);
    eventManager->touchTestResults_.emplace(touchPoint.id, touchTestResults);

    /**
     * @tc.steps: step3. Create FrameNode and Call HandleGlobalEventNG.
     * @tc.expected: touchTestResults_.size() is equal to 1.
     */
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(frameNode);
    NG::OffsetF rootOffset;
    eventManager->HandleGlobalEventNG(touchPoint, selectOverlayManager, rootOffset);
    EXPECT_EQ(eventManager->touchTestResults_.size(), 1);
}

/**
 * @tc.name: EventManagerTest042
 * @tc.desc: Test DispatchMouseHoverAnimation in MouseButton::NONE_BUTTON branches
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseHoverAnimation with event.
     * @tc.expected: hoverNodeCur is null.
     */
    MouseEvent event;
    event.button = MouseButton::NONE_BUTTON;
    eventManager->DispatchMouseHoverAnimation(event);
    auto hoverNodeCur = eventManager->mouseHoverNode_.Upgrade();
    EXPECT_EQ(hoverNodeCur, nullptr);
}

/**
 * @tc.name: EventManagerTest043
 * @tc.desc: Test DispatchTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(CONTAINER_INSTANCE_ID, MockContainer::container_);

    /**
     * @tc.steps: step2. Call DispatchTouchEvent with TouchType::DOWN.
     * @tc.expected: ret is false.
     */
    TouchEvent event;
    event.type = TouchType::DOWN;
    auto ret = eventManager->DispatchTouchEvent(event);
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Call DispatchTouchEvent with TouchType::DOWN and
                        touchTestResults_ has element;
     * @tc.expected: ret is true
     */
    TouchTestResult touchTestResults;
    auto eventTarget = AceType::MakeRefPtr<MockTouchEventTarget>();
    touchTestResults.push_back(eventTarget);
    eventManager->touchTestResults_.emplace(event.id, touchTestResults);
    ret = eventManager->DispatchTouchEvent(event);
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step4. Call DispatchTouchEvent with TouchType::PULL_MOVE and
                        touchTestResults_ has element;
     * @tc.expected: ret is true
     */
    event.type = TouchType::PULL_MOVE;
    ret = eventManager->DispatchTouchEvent(event);
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step5. Call DispatchTouchEvent with TouchType::PULL_MOVE and
                        touchTestResults_ has element;
     * @tc.expected: ret is false.
     */
    event.pullType = TouchType::PULL_MOVE;
    ret = eventManager->DispatchTouchEvent(event);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: GetSetPressedKeyCodesTest001
 * @tc.desc: Test GetPressedKeyCodes and SetPressedKeyCodes function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetSetPressedKeyCodesTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Call SetPressedKeyCodes GetPressedKeyCodes with event.
     * @tc.expected: pressedKeyCodes size is 2.
     */
    BaseEventInfo event("test");
    event.SetPressedKeyCodes({KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_CTRL_RIGHT});
    auto pressedKeyCodes = event.GetPressedKeyCodes();
    EXPECT_EQ(pressedKeyCodes.size(), 2);
    EXPECT_EQ(pressedKeyCodes[1], KeyCode::KEY_CTRL_RIGHT);
}
} // namespace OHOS::Ace::NG