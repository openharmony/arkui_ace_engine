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
#include "gtest/gtest.h"
#include "test/unittest/core/event/event_manager_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_window.h"
#include "test/mock/core/common/mock_frontend.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
} // namespace

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
    EXPECT_TRUE(retFlag);
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

    event.type = TouchType::CANCEL;
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

/**
 * @tc.name: EventManagerTest045
 * @tc.desc: Test PostEventFlushTouchEventEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call PostEventFlushTouchEventEnd with TouchType::DOWN.
     * @tc.expected: ret is false.
     */
    TouchEvent event;
    event.type = TouchType::DOWN;
    event.id = 1;
    TouchTestResult hitTestResult;
    eventManager->PostEventFlushTouchEventEnd(event);

    /**
     * @tc.steps: step3. Create pan recognizers.
     * @tc.expected: recognizers is not null and axis direction is correct.
     */
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal1, nullptr);
    hitTestResult.emplace_back(panHorizontal1);
    eventManager->postEventTouchTestResults_[1] = hitTestResult;

    eventManager->PostEventFlushTouchEventEnd(event);
    EXPECT_TRUE(panHorizontal1->isFlushTouchEventsEnd_);
}

/**
 * @tc.name: EventManagerTest046
 * @tc.desc: Test LogTouchTestResultRecognizers function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call LogTouchTestResultRecognizers.
     * @tc.expected: ret is false.
     */
    TouchEvent event;
    event.type = TouchType::DOWN;
    event.id = 1;
    TouchTestResult hitTestResult;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal1, nullptr);
    hitTestResult.emplace_back(panHorizontal1);
    std::list<RefPtr<NGGestureRecognizer>> combined;
    auto exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(std::move(combined));
    auto exclusiveRecognizer1 = AceType::MakeRefPtr<ExclusiveRecognizer>(std::move(combined));
    hitTestResult.emplace_back(exclusiveRecognizer);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    exclusiveRecognizer1->node_ = pageNode;
    hitTestResult.emplace_back(exclusiveRecognizer1);
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    hitTestResult.emplace_back(clickRecognizer);

    eventManager->LogTouchTestResultRecognizers(hitTestResult, 1);
    EXPECT_FALSE(panHorizontal1->isFlushTouchEventsEnd_);
}

/**
 * @tc.name: EventManagerTest047
 * @tc.desc: Test DispatchMouseHoverAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto animatablePoperties = AceType::MakeRefPtr<OHOS::Ace::AnimatableProperties>();
    auto renderNode = AceType::DynamicCast<RenderNode>(animatablePoperties);
    eventManager->mouseHoverNode_ = renderNode;

    MouseEvent event;
    event.action = MouseAction::PRESS;
    eventManager->DispatchMouseHoverAnimation(event);
    
    event.action = MouseAction::RELEASE;
    eventManager->DispatchMouseHoverAnimation(event);
    
    event.action = MouseAction::WINDOW_ENTER;
    eventManager->DispatchMouseHoverAnimation(event);
    
    event.action = MouseAction::WINDOW_LEAVE;

    eventManager->DispatchMouseHoverAnimation(event);
    auto hoverNodeCur = eventManager->mouseHoverNode_.Upgrade();
    EXPECT_EQ(hoverNodeCur, nullptr);
}

/**
 * @tc.name: EventManagerTest048
 * @tc.desc: Test GetTouchTestIds function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    TouchEvent event;
    event.type = TouchType::DOWN;
    event.id = 1;
    std::vector<std::string> touchTestIds = {"1", "2"};
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal1, nullptr);
    panHorizontal1->getEventTargetImpl_ = std::function<std::optional<EventTarget>()>{};
    
    TouchTestResult hitTestResult;
    hitTestResult.emplace_back(panHorizontal1);
    eventManager->touchTestResults_.emplace(event.id, hitTestResult);
    bool isMousePressAtSelectedNode = false;
    eventManager->GetTouchTestIds(event, touchTestIds, isMousePressAtSelectedNode, 1);
    EXPECT_FALSE(isMousePressAtSelectedNode);

    EXPECT_EQ(touchTestIds.size(), 2);
    auto num = std::stoi(touchTestIds.back());
    eventManager->GetTouchTestIds(event, touchTestIds, isMousePressAtSelectedNode, num);
    EXPECT_FALSE(isMousePressAtSelectedNode);
}

/**
 * @tc.name: EventManagerTest049
 * @tc.desc: Test FlushTouchEventsBegin function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    TouchEvent event;
    event.type = TouchType::DOWN;
    event.id = 1;
    std::list<TouchEvent> touchEvents = {event};
    TouchTestResult hitTestResult;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    hitTestResult.emplace_back(panHorizontal1);
    eventManager->touchTestResults_[2] = hitTestResult;
    eventManager->FlushTouchEventsBegin(touchEvents);
    EXPECT_TRUE(eventManager->touchTestResults_.count(2) == 1);
}

/**
 * @tc.name: EventManagerTest050
 * @tc.desc: Test CheckMouseTestResults function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto mouseEventTarget = AceType::MakeRefPtr<MouseEventTarget>(MOUSE, NODEID);
    std::list<RefPtr<MouseEventTarget>> mouseTestResult = {mouseEventTarget};
    eventManager->currMouseTestResultsMap_[0] = mouseTestResult;

    bool isMousePressAtSelectedNode = false;
    eventManager->CheckMouseTestResults(isMousePressAtSelectedNode, NODEID, 0);
    EXPECT_TRUE(isMousePressAtSelectedNode);
    isMousePressAtSelectedNode = false;
    eventManager->CheckMouseTestResults(isMousePressAtSelectedNode, NODEID + 1, 0);
    EXPECT_FALSE(isMousePressAtSelectedNode);
}

/**
 * @tc.name: EventManagerTest051
 * @tc.desc: Test MouseTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto animatablePoperties = AceType::MakeRefPtr<OHOS::Ace::AnimatableProperties>();
    auto renderNode = AceType::DynamicCast<RenderNode>(animatablePoperties);

    MouseEvent event;
    event.action = MouseAction::WINDOW_LEAVE;
    std::list<WeakPtr<RenderNode>> MouseHoverTestList;
    
    eventManager->MouseTest(event, renderNode);

    event.action = MouseAction::WINDOW_ENTER;
    eventManager->MouseTest(event, renderNode);

    event.action = MouseAction::NONE;
    eventManager->MouseTest(event, renderNode);
    EXPECT_TRUE(eventManager->mouseHoverTestResults_.empty());
}

/**
 * @tc.name: EventManagerTest052
 * @tc.desc: Test DispatchMouseEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto animatablePoperties = AceType::MakeRefPtr<OHOS::Ace::AnimatableProperties>();
    auto renderNode = AceType::DynamicCast<RenderNode>(animatablePoperties);
    std::list<WeakPtr<RenderNode>> mouseHoverTestList = {renderNode};
    MouseEvent event;
    event.action = MouseAction::WINDOW_LEAVE;
    EXPECT_FALSE(eventManager->DispatchMouseEvent(event));

    eventManager->mouseHoverTestResults_ = mouseHoverTestList;
    event.action = MouseAction::MOVE;
    EXPECT_TRUE(eventManager->DispatchMouseEvent(event));
}

/**
 * @tc.name: EventManagerTest053
 * @tc.desc: Test LogPrintMouseTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    SystemProperties::debugEnabled_ = true;

    eventManager->LogPrintMouseTest();
    auto mouseEventTarget = AceType::MakeRefPtr<MouseEventTarget>(MOUSE, NODEID);
    std::list<RefPtr<MouseEventTarget>> MouseTestResult = {};
    eventManager->currMouseTestResultsMap_[0] = MouseTestResult;
    eventManager->LogPrintMouseTest();
    MouseTestResult = {mouseEventTarget};
    eventManager->currMouseTestResultsMap_[0] = MouseTestResult;
    eventManager->LogPrintMouseTest();
    
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(MOUSE, NODEID);
    std::list<RefPtr<HoverEventTarget>> HoverTestResult = {hoverEventTarget};
    eventManager->lastHoverTestResultsMap_[0] = HoverTestResult;
    eventManager->currHoverTestResultsMap_[0] = HoverTestResult;
    eventManager->LogPrintMouseTest();
}

/**
 * @tc.name: EventManagerTest054
 * @tc.desc: Test UpdateHoverNode function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    MouseEvent event;
    auto mouseEventTarget = AceType::MakeRefPtr<MouseEventTarget>(MOUSE, NODEID);
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(MOUSE, NODEID);
    std::list<RefPtr<TouchEventTarget>> testResult = {AceType::MakeRefPtr<MockTouchEventTarget>(),
        mouseEventTarget, hoverEventTarget};
    eventManager->UpdateHoverNode(event, testResult);
    EXPECT_FALSE((eventManager->currMouseTestResultsMap_[0]).empty());
}

/**
 * @tc.name: EventManagerTest055
 * @tc.desc: Test DispatchKeyboardShortcut function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    KeyEvent event;
    event.action = KeyAction::UP;
    EXPECT_FALSE(eventManager->DispatchKeyboardShortcut(event));

    event.action = KeyAction::DOWN;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->isActive_ = false;
    
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto frameNode3 = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    frameNode3->eventHub_ = eventHub;
    eventHub->enabled_ = false;

    std::list<WeakPtr<NG::FrameNode>> keyboardShortcutNode = {nullptr, frameNode, frameNode2, frameNode3};
    eventManager->keyboardShortcutNode_ = keyboardShortcutNode;
    EXPECT_FALSE(eventManager->DispatchKeyboardShortcut(event));
}

/**
 * @tc.name: EventManagerTest056
 * @tc.desc: Test DelKeyboardShortcutNode function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    std::list<WeakPtr<NG::FrameNode>> keyboardShortcutNode = {nullptr, frameNode};
    eventManager->keyboardShortcutNode_ = keyboardShortcutNode;

    eventManager->DelKeyboardShortcutNode(2);
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
}

/**
 * @tc.name: EventManagerTest057
 * @tc.desc: Test AddGestureSnapshot function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    eventManager->AddGestureSnapshot(1, 1, panHorizontal1, EventTreeType::TOUCH);

    auto mouseEventTarget = AceType::MakeRefPtr<MouseEventTarget>(MOUSE, NODEID);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    mouseEventTarget->node_ = frameNode;
    eventManager->AddGestureSnapshot(1, 1, mouseEventTarget, EventTreeType::TOUCH);
    
    eventManager->AddGestureSnapshot(1, 1, nullptr, EventTreeType::TOUCH);
    EXPECT_TRUE(eventManager->eventTree_.eventTreeList.empty());
}

/**
 * @tc.name: EventManagerTest058
 * @tc.desc: Test SetHittedFrameNode function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    auto panHorizontal2 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    std::list<RefPtr<NG::NGGestureRecognizer>> touchTestResults;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    panHorizontal1->node_ = frameNode;
    touchTestResults.emplace_back(panHorizontal1);
    touchTestResults.emplace_back(panHorizontal2);
    eventManager->SetHittedFrameNode(touchTestResults);
    EXPECT_TRUE(eventManager->eventTree_.eventTreeList.empty());
}

/**
 * @tc.name: EventManagerTest059
 * @tc.desc: Test CleanGestureEventHub function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    std::set<WeakPtr<FrameNode>> hittedFrameNode;
    eventManager->hittedFrameNode_ = hittedFrameNode;
    eventManager->CleanGestureEventHub();
    EXPECT_TRUE(eventManager->hittedFrameNode_.empty());

    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    frameNode2->eventHub_ = eventHub;
    hittedFrameNode.insert(frameNode);
    hittedFrameNode.insert(frameNode2);
    hittedFrameNode.insert(nullptr);
    eventManager->hittedFrameNode_ = hittedFrameNode;
    eventManager->CleanGestureEventHub();
    EXPECT_TRUE(eventManager->hittedFrameNode_.empty());
}

/**
 * @tc.name: EventManagerTest060
 * @tc.desc: Test CheckAndLogLastReceivedEventInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest060, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int eventId = 1;
    bool logImmediately = true;
    
    SystemProperties::debugEnabled_ = false;
    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    EXPECT_TRUE(eventManager->lastReceivedEvent_.eventId == -1);

    SystemProperties::debugEnabled_ = true;
    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    EXPECT_TRUE(eventManager->lastReceivedEvent_.eventId == -1);

    logImmediately = false;
    eventManager->lastReceivedEvent_.lastLogTimeStamp = 0;
    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    EXPECT_TRUE(eventManager->lastReceivedEvent_.eventId == 1);

    auto currentTime = GetSysTimestamp();
    auto lastLogTimeStamp = currentTime - 1000 * 1000000 - 1000;
    eventManager->lastReceivedEvent_.lastLogTimeStamp = lastLogTimeStamp;
    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    EXPECT_FALSE(eventManager->lastReceivedEvent_.lastLogTimeStamp > currentTime);

    eventManager->lastReceivedEvent_.lastLogTimeStamp = lastLogTimeStamp - 1;
    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    EXPECT_FALSE(eventManager->lastReceivedEvent_.lastLogTimeStamp == currentTime);

    SystemProperties::debugEnabled_ = false;
    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    EXPECT_FALSE(eventManager->lastReceivedEvent_.lastLogTimeStamp == currentTime);

    eventManager->lastReceivedEvent_.lastLogTimeStamp = lastLogTimeStamp + 20000;
    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    EXPECT_TRUE(eventManager->lastReceivedEvent_.lastLogTimeStamp == lastLogTimeStamp + 20000);
}

/**
 * @tc.name: EventManagerTest061
 * @tc.desc: Test CheckAndLogLastConsumedEventInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest061, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int eventId = 1;
    bool logImmediately = true;

    eventManager->CheckAndLogLastConsumedEventInfo(eventId, logImmediately);

    logImmediately = false;
    eventManager->lastConsumedEvent_.lastLogTimeStamp = 0;
    eventManager->CheckAndLogLastConsumedEventInfo(eventId, logImmediately);
    EXPECT_TRUE(eventManager->lastConsumedEvent_.eventId == 1);

    auto currentTime = GetSysTimestamp();
    auto lastLogTimeStamp = currentTime - 1000 * 1000000 - 1000;
    eventManager->lastConsumedEvent_.lastLogTimeStamp = lastLogTimeStamp;
    eventManager->CheckAndLogLastConsumedEventInfo(eventId, logImmediately);
    EXPECT_FALSE(eventManager->lastConsumedEvent_.lastLogTimeStamp > currentTime);

    eventManager->lastConsumedEvent_.lastLogTimeStamp = lastLogTimeStamp - 1;
    eventManager->CheckAndLogLastConsumedEventInfo(eventId, logImmediately);
    EXPECT_FALSE(eventManager->lastConsumedEvent_.lastLogTimeStamp == currentTime);
    
    eventManager->lastReceivedEvent_.lastLogTimeStamp = lastLogTimeStamp + 20000;
    eventManager->lastConsumedEvent_.lastLogTimeStamp = lastLogTimeStamp + 20000;
    eventManager->CheckAndLogLastConsumedEventInfo(eventId, logImmediately);
    EXPECT_TRUE(eventManager->lastConsumedEvent_.lastLogTimeStamp == lastLogTimeStamp + 20000);
}

/**
 * @tc.name: EventManagerTest062
 * @tc.desc: Test SetResponseLinkRecognizers function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    std::list<RefPtr<TouchEventTarget>> result;
    ResponseLinkResult responseLinkRecognizers;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    panHorizontal1->node_ = frameNode;
    result.emplace_back(panHorizontal1);
    result.emplace_back(nullptr);
    responseLinkRecognizers.emplace_back(panHorizontal1);

    eventManager->SetResponseLinkRecognizers(result, responseLinkRecognizers);
    EXPECT_TRUE(responseLinkRecognizers.size() == 1);
}
} // namespace OHOS::Ace::NG