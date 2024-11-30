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
RefPtr<FrameNode> CreateFrameNodeGroup(int32_t targetId, size_t childCount)
{
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, targetId, pagePattern);
    for (size_t i = 0; i < childCount; ++i) {
        ++targetId;
        auto childNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, targetId, nullptr);
        childNode->MountToParent(pageNode);
    }
    return pageNode;
}

RefPtr<NG::NGGestureRecognizer> CreateRecognizerGroup(const RefPtr<NG::FrameNode>& parentNode)
{
    CHECK_NULL_RETURN(parentNode, nullptr);
    std::list<RefPtr<NGGestureRecognizer>> recognizers;
    for (const auto& childNode : parentNode->GetChildren()) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(childNode);
        if (childFrameNode) {
            auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
            clickRecognizer->AttachFrameNode(childFrameNode);
            recognizers.emplace_back(clickRecognizer);
        }
    }
    auto recognizerGroup = AceType::MakeRefPtr<NG::ParallelRecognizer>(std::move(recognizers));
    if (recognizerGroup) {
        recognizerGroup->AttachFrameNode(parentNode);
    }
    return recognizerGroup;
}
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
    ASSERT_TRUE(panHorizontal1->isFlushTouchEventsEnd_);
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
    ASSERT_FALSE(panHorizontal1->isFlushTouchEventsEnd_);
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
    ASSERT_EQ(hoverNodeCur, nullptr);
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
    ASSERT_FALSE(isMousePressAtSelectedNode);
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
    ASSERT_TRUE(eventManager->touchTestResults_.count(2) == 1);
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
    eventManager->currMouseTestResults_ = mouseTestResult;

    bool isMousePressAtSelectedNode = false;
    eventManager->CheckMouseTestResults(isMousePressAtSelectedNode, NODEID);
    ASSERT_TRUE(isMousePressAtSelectedNode);
    isMousePressAtSelectedNode = false;
    eventManager->CheckMouseTestResults(isMousePressAtSelectedNode, NODEID + 1);
    ASSERT_FALSE(isMousePressAtSelectedNode);
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
    ASSERT_TRUE(eventManager->mouseHoverTestResults_.empty());
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
    ASSERT_FALSE(eventManager->DispatchMouseEvent(event));

    eventManager->mouseHoverTestResults_ = mouseHoverTestList;
    event.action = MouseAction::MOVE;
    ASSERT_TRUE(eventManager->DispatchMouseEvent(event));
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
    std::list<RefPtr<MouseEventTarget>> MouseTestResult = {mouseEventTarget};
    eventManager->currMouseTestResults_ = MouseTestResult;
    
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(MOUSE, NODEID);
    std::list<RefPtr<HoverEventTarget>> HoverTestResult = {hoverEventTarget};
    eventManager->lastHoverTestResults_ = HoverTestResult;
    eventManager->currHoverTestResults_ = HoverTestResult;
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
    ASSERT_FALSE((eventManager->currMouseTestResults_).empty());
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
    ASSERT_FALSE(eventManager->DispatchKeyboardShortcut(event));

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
    ASSERT_FALSE(eventManager->DispatchKeyboardShortcut(event));
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
    ASSERT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
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
    ASSERT_TRUE(eventManager->eventTree_.eventTreeList.empty());
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
    ASSERT_TRUE(eventManager->eventTree_.eventTreeList.empty());
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
    ASSERT_TRUE(eventManager->hittedFrameNode_.empty());

    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto frameNode2 = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    frameNode2->eventHub_ = eventHub;
    hittedFrameNode.insert(frameNode);
    hittedFrameNode.insert(frameNode2);
    hittedFrameNode.insert(nullptr);
    eventManager->hittedFrameNode_ = hittedFrameNode;
    eventManager->CleanGestureEventHub();
    ASSERT_TRUE(eventManager->hittedFrameNode_.empty());
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

    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    ASSERT_TRUE(eventManager->lastReceivedEvent_.eventId == -1);

    logImmediately = false;
    eventManager->lastReceivedEvent_.lastLogTimeStamp = 0;
    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    ASSERT_TRUE(eventManager->lastReceivedEvent_.eventId == 1);

    auto currentTime = GetSysTimestamp();
    auto lastLogTimeStamp = currentTime - 1000 * 1000000 - 1000;
    eventManager->lastReceivedEvent_.lastLogTimeStamp = lastLogTimeStamp;
    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    ASSERT_TRUE(eventManager->lastReceivedEvent_.lastLogTimeStamp > currentTime);
    
    eventManager->lastReceivedEvent_.lastLogTimeStamp = lastLogTimeStamp + 20000;
    eventManager->CheckAndLogLastReceivedEventInfo(eventId, logImmediately);
    ASSERT_TRUE(eventManager->lastReceivedEvent_.lastLogTimeStamp == lastLogTimeStamp + 20000);
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
    ASSERT_TRUE(eventManager->lastConsumedEvent_.eventId == 1);

    auto currentTime = GetSysTimestamp();
    auto lastLogTimeStamp = currentTime - 1000 * 1000000 - 1000;
    eventManager->lastConsumedEvent_.lastLogTimeStamp = lastLogTimeStamp;
    eventManager->CheckAndLogLastConsumedEventInfo(eventId, logImmediately);
    ASSERT_TRUE(eventManager->lastConsumedEvent_.lastLogTimeStamp > currentTime);
    
    eventManager->lastReceivedEvent_.lastLogTimeStamp = lastLogTimeStamp + 20000;
    eventManager->lastConsumedEvent_.lastLogTimeStamp = lastLogTimeStamp + 20000;
    eventManager->CheckAndLogLastConsumedEventInfo(eventId, logImmediately);
    ASSERT_TRUE(eventManager->lastConsumedEvent_.lastLogTimeStamp == lastLogTimeStamp + 20000);
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
    ASSERT_TRUE(responseLinkRecognizers.size() == 1);
}

/**
 * @tc.name: EventManagerTest063
 * @tc.desc: Test touchtest
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest063, TestSize.Level1)
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
    touchPoint.id = 1;
    touchPoint.type = TouchType::DOWN;
    touchPoint.sourceType = SourceType::TOUCH;
    auto currentTime = GetSysTimestamp();
    auto lastTime = currentTime - 1000 * 1000000 - 1000;
    TimeStamp lastTimeStamp((std::chrono::milliseconds(lastTime)));
    TimeStamp currentTimeStamp((std::chrono::milliseconds(currentTime)));
    eventManager->lastEventTime_ = lastTimeStamp;
    touchPoint.time = currentTimeStamp;
    const int nodeId = 1;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;
    Offset offset;
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    ASSERT_NE(clickRecognizer, nullptr);
    clickRecognizer->OnRejected();
    auto gestureRefereeNg = eventManager->GetGestureRefereeNG(clickRecognizer);
    ASSERT_NE(gestureRefereeNg, nullptr);
    gestureRefereeNg->CheckSourceTypeChange(SourceType::NONE, true);
    TouchTestResult resultList = { clickRecognizer };
    eventManager->TouchTest(touchPoint, frameNode, touchRestrict, offset, 0, true);
    EXPECT_GT(eventManager->touchTestResults_.count(touchPoint.id), 0);
}

/**
 * @tc.name: EventManagerTest064
 * @tc.desc: Test LogTouchTestResultRecognizers
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest064, TestSize.Level1)
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
    TouchTestResult resultList;
    auto panHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal, nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    panHorizontal->AttachFrameNode(pageNode);
    resultList.emplace_back(panHorizontal);
    eventManager->LogTouchTestResultRecognizers(resultList, 1);
    ASSERT_FALSE(panHorizontal->isFlushTouchEventsEnd_);
}

/**
 * @tc.name: EventManagerTest065
 * @tc.desc: Test HandleGlobalEventNG whith mouse
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest065, TestSize.Level1)
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
    touchPoint.sourceType = SourceType::MOUSE;

    const int nodeId = 10003;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;
    Offset offset;

    auto eventTarget = AceType::MakeRefPtr<MouseEventTarget>(MOUSE_EVENT, nodeId);
    eventManager->currMouseTestResults_.emplace_back(eventTarget);

    /**
     * @tc.steps: step3. Create FrameNode and Call HandleGlobalEventNG.
     * @tc.expected: currMouseTestResults_.size is equal to 1.
     */
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(frameNode);
    NG::OffsetF rootOffset;
    eventManager->HandleGlobalEventNG(touchPoint, selectOverlayManager, rootOffset);
    EXPECT_EQ(eventManager->currMouseTestResults_.size(), 1);
}

/**
 * @tc.name: EventManagerTest066
 * @tc.desc: Test GetTouchTestIds function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest066, TestSize.Level1)
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
    std::vector<std::string> touchTestIds;
    auto panHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal, nullptr);
    panHorizontal->SetGetEventTargetImpl([]() -> std::optional<EventTarget> {
        struct EventTarget eventTarget = {
            .id = "eventTargetCallback",
            .type = "eventTargetType"
        };
        std::optional<EventTarget> eventTargetCallback = eventTarget;
        return eventTargetCallback;
    });

    TouchTestResult hitTestResult;
    hitTestResult.emplace_back(panHorizontal);
    eventManager->touchTestResults_.insert({event.id, hitTestResult});
    bool isMousePressAtSelectedNode = false;
    eventManager->GetTouchTestIds(event, touchTestIds, isMousePressAtSelectedNode, 1);
    ASSERT_FALSE(isMousePressAtSelectedNode);
    ASSERT_FALSE(touchTestIds.empty());
}

/**
 * @tc.name: EventManagerTest067
 * @tc.desc: Test HandleOutOfRectCallback
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest067, TestSize.Level2)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Create rectCallbackList
     * @tc.expected: touchTestResults_ has the touchPoint.id of instance
     */
    Point point(10, 20);
    point.SetSourceType(SourceType::TOUCH);

    auto rectGetCallback = [](std::vector<Rect>& rectList) -> void { rectList.push_back(Rect()); };

    auto touchCallback = []() -> void {};
    auto mouseCallback = []() -> void {};
    std::vector<RectCallback> rectCallbackList {
        RectCallback(rectGetCallback, touchCallback, nullptr),
        RectCallback(rectGetCallback, nullptr, mouseCallback)
    };

    /**
     * @tc.steps: step3. Call HandleOutOfRectCallback with SourceType::TOUCH
     * @tc.expected: rectCallbackList.size() is 1
     */
    eventManager->HandleOutOfRectCallback(point, rectCallbackList);
    EXPECT_EQ(rectCallbackList.size(), 1);

    /**
     * @tc.steps: step3. Call HandleOutOfRectCallback with SourceType::MOUSE
     * @tc.expected: rectCallbackList is empty
     */
    point.SetSourceType(SourceType::MOUSE);
    eventManager->HandleOutOfRectCallback(point, rectCallbackList);
    EXPECT_TRUE(rectCallbackList.empty());
}

/**
 * @tc.name: EventManagerTest068
 * @tc.desc: Test DispatchTouchEventToTouchTestResult
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest068, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto panHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal, nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    int64_t deviceId = 20240711;
    TouchEvent event;
    event.type = TouchType::DOWN;
    event.deviceId = deviceId;
    event.sourceType = SourceType::TOUCH;
    panHorizontal->AttachFrameNode(pageNode);

    TouchTestResult resultList;
    resultList.emplace_back(panHorizontal);
    eventManager->DispatchTouchEventToTouchTestResult(event, resultList, false);
    EXPECT_EQ(panHorizontal->deviceId_, deviceId);
    EXPECT_TRUE(panHorizontal->deviceType_ == SourceType::TOUCH);
}

/**
 * @tc.name: EventManagerTest069
 * @tc.desc: Test PostEventDispatchTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest069, TestSize.Level2)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto rawHorizontal = AceType::MakeRefPtr<RawRecognizer>();
    ASSERT_NE(rawHorizontal, nullptr);
    auto panHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal, nullptr);
    TouchEvent event;
    event.id = 1024;
    event.type = TouchType::DOWN;
    event.sourceType = SourceType::TOUCH;
    EXPECT_FALSE(eventManager->PostEventDispatchTouchEvent(event));

    rawHorizontal->SetCatchEventCallback([]() {},
        static_cast<int32_t>(EventStage::CAPTURE), static_cast<int32_t>(EventType::TOUCH_DOWN));
    TouchTestResult resultList;
    resultList.emplace_back(panHorizontal);
    resultList.emplace_back(rawHorizontal);
    eventManager->postEventTouchTestResults_.emplace(event.id, resultList);
    EXPECT_TRUE(eventManager->PostEventDispatchTouchEvent(event));
}

/**
 * @tc.name: EventManagerTest070
 * @tc.desc: Test MouseTest For API12.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest070, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingApiVersion);

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);

    MouseEvent event;
    event.action = MouseAction::MOVE;
    event.button = MouseButton::RIGHT_BUTTON;
    TouchRestrict touchRestrict;
    eventManager->MouseTest(event, pageNode, touchRestrict);
    
    event.action = MouseAction::WINDOW_ENTER;
    eventManager->MouseTest(event, pageNode, touchRestrict);
    EXPECT_TRUE(touchRestrict.touchEvent.isMouseTouchTest);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: EventManagerTest071
 * @tc.desc: Test UpdateHoverNode
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest071, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    MouseEvent event;
    auto hoverEffectTarget = AceType::MakeRefPtr<HoverEffectTarget>(CTRLSHIFT, NODEID);
    std::list<RefPtr<TouchEventTarget>> testResult = { hoverEffectTarget };
    eventManager->UpdateHoverNode(event, testResult);
    EXPECT_TRUE(eventManager->currMouseTestResults_.empty());
}

/**
 * @tc.name: EventManagerTest073
 * @tc.desc: Test AddKeyboardShortcutNode
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest073, TestSize.Level2)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    auto frameNodeCtrl = FrameNode::GetOrCreateFrameNode(CTRL, NODEID, nullptr);
    auto frameNodeCtrlShift = FrameNode::GetOrCreateFrameNode(CTRLSHIFT, NODEID, nullptr);
    frameNodeCtrl->SetActive(true);
    frameNodeCtrlShift->SetActive(true);

    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrl));
    eventManager->AddKeyboardShortcutNode(nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrlShift));
    EXPECT_EQ(eventManager->keyboardShortcutNode_.size(), 1);
}

/**
 * @tc.name: EventManagerTest074
 * @tc.desc: Test DispatchKeyboardShortcut
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest074, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    KeyEvent event;
    auto frameNodeCtrl = FrameNode::GetOrCreateFrameNode(CTRL, NODEID, nullptr);
    auto frameNodeShift = FrameNode::GetOrCreateFrameNode(SHIFT, NODEID, nullptr);
    auto frameNodeAlt = FrameNode::GetOrCreateFrameNode(ALT, NODEID, nullptr);
    auto frameNodeCtrlShift = FrameNode::GetOrCreateFrameNode(CTRLSHIFT, NODEID, nullptr);
    frameNodeCtrl->SetActive(true);
    frameNodeShift->SetActive(true);
    frameNodeAlt->SetActive(true);
    frameNodeCtrlShift->SetActive(true);

    auto eventHubCtrl = frameNodeCtrl->GetEventHub<NG::EventHub>();
    auto eventHubShift = frameNodeShift->GetEventHub<NG::EventHub>();
    auto eventHubAlt = frameNodeAlt->GetEventHub<NG::EventHub>();
    auto eventHubCtrlShift = frameNodeCtrlShift->GetEventHub<NG::EventHub>();

    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrl));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeShift));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeAlt));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrlShift));
    eventHubCtrl->SetKeyboardShortcut(CHARACTER_C, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE + NUM_ALT_VALUE), nullptr);
    event.code = KeyCode::KEY_C;
    event.action = KeyAction::DOWN;
    event.pressedCodes.emplace_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_ALT_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_C);
    eventManager->DispatchKeyboardShortcut(event);
    EXPECT_EQ(event.action, KeyAction::DOWN);
}

/**
 * @tc.name: EventManagerTest075
 * @tc.desc: Test DispatchKeyboardShortcut
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest075, TestSize.Level2)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    KeyEvent event;
    event.action = KeyAction::CLICK;
    EXPECT_FALSE(eventManager->DispatchKeyboardShortcut(event));

    auto frameNodeCtrl = FrameNode::GetOrCreateFrameNode(CTRL, NODEID, nullptr);
    auto eventHubCtrl = frameNodeCtrl->GetEventHub<NG::EventHub>();
    frameNodeCtrl->SetActive(true);

    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrl));
    uint8_t singleKeys = 0;
    eventHubCtrl->SetKeyboardShortcut(CTRL, singleKeys, nullptr);
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_ESCAPE;
    EXPECT_FALSE(eventManager->DispatchKeyboardShortcut(event));

    eventHubCtrl->SetKeyboardShortcut(std::string(), (NUM_CTRL_VALUE + NUM_SHIFT_VALUE), nullptr);
    EXPECT_FALSE(eventManager->DispatchKeyboardShortcut(event));

    eventHubCtrl->SetEnabled(false);
    EXPECT_FALSE(eventManager->DispatchKeyboardShortcut(event));
}

/**
 * @tc.name: EventManagerTest076
 * @tc.desc: Test EventManager constructor fire callBack
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest076, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto referee = eventManager->GetGestureReferee();
    ASSERT_NE(referee, nullptr);
    int32_t touchId = 10;
    ASSERT_NE(referee->queryStateFunc_, nullptr);
    referee->queryStateFunc_(touchId);
    auto gestureRefereeNg = eventManager->GetGestureRefereeNG(AceType::MakeRefPtr<ClickRecognizer>());
    ASSERT_NE(gestureRefereeNg, nullptr);
    ASSERT_NE(gestureRefereeNg->queryStateFunc_, nullptr);
    gestureRefereeNg->queryStateFunc_(touchId);
}

/**
 * @tc.name: EventManagerTest077
 * @tc.desc: Test AddGestureSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest077, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto eventTree = eventManager->GetEventTreeRecord(EventTreeType::TOUCH);
    TouchEvent event;
    event.type = Ace::TouchType::DOWN;
    event.id = 1;
    eventTree.AddTouchPoint(event);
    eventManager->DumpEvent(EventTreeType::TOUCH);

    int32_t finger = 1;
    int32_t depth = 0;
    int32_t nodeId = 16;
    eventManager->AddGestureSnapshot(finger, depth, nullptr, EventTreeType::TOUCH);
    auto parentNode = CreateFrameNodeGroup(nodeId, 3);
    auto recognizerGroup = CreateRecognizerGroup(parentNode);
    eventManager->AddGestureSnapshot(finger, depth, recognizerGroup, EventTreeType::TOUCH);
    EXPECT_FALSE(eventTree.eventTreeList.empty());
}

/**
 * @tc.name: EventManagerTest078
 * @tc.desc: Test SetHittedFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest078, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    int32_t nodeId = 16;
    auto parentNode = CreateFrameNodeGroup(nodeId, 3);
    auto recognizerGroup = CreateRecognizerGroup(parentNode);

    std::list<RefPtr<NG::NGGestureRecognizer>> gestureRecognizers;
    eventManager->SetHittedFrameNode(gestureRecognizers);
    EXPECT_TRUE(eventManager->hittedFrameNode_.empty());

    gestureRecognizers.emplace_back(recognizerGroup);
    eventManager->SetHittedFrameNode(gestureRecognizers);
    EXPECT_FALSE(eventManager->hittedFrameNode_.empty());
}

/**
 * @tc.name: EventManagerTest079
 * @tc.desc: Test CleanGestureEventHub
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest079, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    int32_t nodeId = 16;
    auto parentNode = CreateFrameNodeGroup(nodeId, 3);
    auto recognizerGroup = CreateRecognizerGroup(parentNode);

    std::list<RefPtr<NG::NGGestureRecognizer>> gestureRecognizers;
    gestureRecognizers.emplace_back(recognizerGroup);
    eventManager->SetHittedFrameNode(gestureRecognizers);
    EXPECT_FALSE(eventManager->hittedFrameNode_.empty());
    eventManager->CleanGestureEventHub();
    EXPECT_TRUE(eventManager->hittedFrameNode_.empty());
}

/**
 * @tc.name: EventManagerTest080
 * @tc.desc: Test SetResponseLinkRecognizers
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest080, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    int32_t nodeId = 16;
    auto parentNode = CreateFrameNodeGroup(nodeId, 3);
    auto recognizerGroup = CreateRecognizerGroup(parentNode);
    auto panHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    auto targetLinkHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());

    TouchTestResult resultList;
    ResponseLinkResult responseLinkRecognizers;
    resultList.emplace_back(recognizerGroup);
    resultList.emplace_back(panHorizontal);
    responseLinkRecognizers.emplace_back(targetLinkHorizontal);
    eventManager->SetResponseLinkRecognizers(resultList, responseLinkRecognizers);
    EXPECT_TRUE(responseLinkRecognizers.size() == 1);
}

/**
 * @tc.name: EventManagerTest081
 * @tc.desc: Test FalsifyCancelEventAndDispatch
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest081, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    int32_t nodeId = 32;
    auto parentNode = CreateFrameNodeGroup(nodeId, 3);
    auto recognizerGroup = CreateRecognizerGroup(parentNode);
    auto panHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    TouchTestResult resultList;
    resultList.emplace_back(recognizerGroup);
    resultList.emplace_back(panHorizontal);
    eventManager->axisTouchTestResults_.clear();
    eventManager->axisTouchTestResults_[0] = resultList;
    AxisEvent event;
    eventManager->FalsifyCancelEventAndDispatch(event);
    EXPECT_TRUE(eventManager->axisTouchTestResults_.empty());
}

/**
 * @tc.name: EventManagerAccessibilityHoverTest001
 * @tc.desc: Test MouseTest (frameNode)
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerAccessibilityHoverTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call MouseTest with MouseAction::WINDOW_LEAVE
     * @tc.expected: currHoverTestResults_ is empty
     */
    TouchEvent event;
    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;

    event.type = TouchType::HOVER_EXIT;
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    eventManager->curAccessibilityHoverResults_.push_back(hoverEventTarget);
    ASSERT_FALSE(eventManager->curAccessibilityHoverResults_.empty());
    eventManager->AccessibilityHoverTest(event, frameNode, touchRestrict);
    ASSERT_TRUE(eventManager->curAccessibilityHoverResults_.empty());

    /**
     * @tc.steps: step3. Call MouseTest with MouseAction::WINDOW_ENTER
     * @tc.expected: lastHoverTestResults_ is empty
     */
    event.type = TouchType::HOVER_ENTER;
    eventManager->lastAccessibilityHoverResults_.push_back(hoverEventTarget);
    ASSERT_FALSE(eventManager->lastAccessibilityHoverResults_.empty());
    eventManager->AccessibilityHoverTest(event, frameNode, touchRestrict);
    ASSERT_TRUE(eventManager->lastAccessibilityHoverResults_.empty());

    /**
     * @tc.steps: step4. Call MouseTest with MouseAction::HOVER
     * @tc.expected: lastHoverTestResults_ is empty and currHoverTestResults_ is empty
     */
    event.type = TouchType::HOVER_MOVE;
    eventManager->lastAccessibilityHoverResults_.push_back(hoverEventTarget);
    eventManager->AccessibilityHoverTest(event, frameNode, touchRestrict);
    ASSERT_TRUE(eventManager->lastAccessibilityHoverResults_.empty());
    ASSERT_TRUE(eventManager->curAccessibilityHoverResults_.empty());
}

/**
 * @tc.name: EventManagerTest082
 * @tc.desc: Test CheckDownEvent with FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest082, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    bool result = true;
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchPoint;
    touchPoint.id = 1;
    touchPoint.type = TouchType::DOWN;
    eventManager->CheckDownEvent(touchPoint);
    eventManager->downFingerIds_[1] = 1;
    eventManager->downFingerIds_[2] = 2;
    eventManager->downFingerIds_[3] = 3;
    eventManager->CheckDownEvent(touchPoint);
    touchPoint.type = TouchType::UP;
    eventManager->CheckDownEvent(touchPoint);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventManagerTest083
 * @tc.desc: Test DispatchAccessibilityHoverEventNG with FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest083, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    bool result = true;
    TouchEvent event;
    const int nodeId = 10008;
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    ASSERT_NE(hoverEventTarget, nullptr);
    eventManager->lastAccessibilityHoverResults_.push_back(hoverEventTarget);
    eventManager->DispatchAccessibilityHoverEventNG(event);
    eventManager->curAccessibilityHoverResults_.push_back(hoverEventTarget);
    eventManager->DispatchAccessibilityHoverEventNG(event);
    eventManager->lastAccessibilityHoverDispatchLength_ = 1;
    eventManager->DispatchAccessibilityHoverEventNG(event);
    eventManager->lastAccessibilityHoverDispatchLength_ = 10;
    eventManager->DispatchAccessibilityHoverEventNG(event);
    eventManager->curAccessibilityHoverResults_.clear();
    eventManager->lastAccessibilityHoverResults_.clear();
    eventManager->curAccessibilityHoverResults_.push_front(hoverEventTarget);
    eventManager->DispatchAccessibilityHoverEventNG(event);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: EventManagerTest084
 * @tc.desc: Test DispatchRotationEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest084, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto referee = eventManager->GetGestureReferee();
    ASSERT_NE(referee, nullptr);
    int32_t touchId = 10;
    RefPtr<GestureScope> scope = AceType::MakeRefPtr<GestureScope>(touchId);
    ASSERT_NE(scope, nullptr);
    referee->gestureScopes_.clear();
    referee->gestureScopes_.insert(std::make_pair(touchId, scope));
    auto gestureScope = referee->GetGestureScope();
    ASSERT_NE(referee->queryStateFunc_, nullptr);
    referee->queryStateFunc_(touchId);
    auto gestureRefereeNg = eventManager->GetGestureRefereeNG(AceType::MakeRefPtr<ClickRecognizer>());
    ASSERT_NE(gestureRefereeNg, nullptr);
    ASSERT_NE(gestureRefereeNg->queryStateFunc_, nullptr);
    gestureRefereeNg->queryStateFunc_(touchId);
}

/**
 * @tc.name: EventManagerTest085
 * @tc.desc: Test RecordHitEmptyMessage
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest085, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchPoint;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 1, nullptr);
    MockPipelineContext::SetUp();
    ASSERT_NE(MockPipelineContext::GetCurrentContext(), nullptr);
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    std::string resultInfo = "info";
    eventManager->RecordHitEmptyMessage(touchPoint, resultInfo, frameNode);
    MockPipelineContext::GetCurrentContext()->window_ = std::make_shared<MockWindow>();
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    EXPECT_CALL(*MockContainer::Current(), GetFrontend()).WillRepeatedly(Return(frontend));
    eventManager->RecordHitEmptyMessage(touchPoint, resultInfo, frameNode);
    EXPECT_CALL(*MockContainer::Current(), GetFrontend()).WillRepeatedly(Return(nullptr));
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
    EXPECT_EQ(touchPoint.isFalsified, false);
}

/**
 * @tc.name: EventManagerTest086
 * @tc.desc: Test DispatchTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest086, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AxisEvent touchPoint;
    touchPoint.action = AxisAction::BEGIN;
    touchPoint.id = MOUSE_BASE_ID;
    TouchTestResult hitTestResult;
    hitTestResult.clear();
    eventManager->axisTouchTestResults_.clear();
    auto panHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal, nullptr);
    auto panHorizontals = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontals, nullptr);
    hitTestResult.emplace_back(panHorizontals);
    hitTestResult.emplace_back(panHorizontal);
    eventManager->axisTouchTestResults_[MOUSE_BASE_ID] = std::move(hitTestResult);
    eventManager->DispatchTouchEvent(touchPoint);
    eventManager->refereeNG_ = nullptr;
    eventManager->DispatchTouchEvent(touchPoint);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->useNewPipeline_ = false;
    eventManager->DispatchTouchEvent(touchPoint);
    touchPoint.isRotationEvent = true;
    eventManager->DispatchTouchEvent(touchPoint);
    EXPECT_EQ(touchPoint.isRotationEvent, true);
}

/**
 * @tc.name: EventManagerTest087
 * @tc.desc: Test DispatchKeyboardShortcut
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest087, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    KeyEvent touchPoint;
    auto container = Container::GetContainer(eventManager->instanceId_);
    ASSERT_NE(container, nullptr);
    container->uIContentType_ = UIContentType::SECURITY_UI_EXTENSION;
    eventManager->DispatchKeyboardShortcut(touchPoint);
    EXPECT_EQ(eventManager->DispatchKeyboardShortcut(touchPoint), false);
}

/**
 * @tc.name: EventManagerTest088
 * @tc.desc: Test TouchTest
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest088, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchPoint;
    touchPoint.id = 1000;
    touchPoint.type = TouchType::DOWN;
    const int nodeId = 10003;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;
    Offset offset;
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    ASSERT_NE(hoverEventTarget, nullptr);
    eventManager->curAccessibilityHoverResults_.push_back(hoverEventTarget);
    TouchTestResult hitTestResult;
    hitTestResult.clear();
    eventManager->touchTestResults_.clear();
    auto panHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal, nullptr);
    auto panHorizontals = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontals, nullptr);
    eventManager->TouchTest(touchPoint, frameNode, touchRestrict, offset, 0, true);
    panHorizontals->node_ = frameNode;
    hitTestResult.emplace_back(panHorizontals);
    hitTestResult.emplace_back(panHorizontal);
    eventManager->touchTestResults_[1000] = std::move(hitTestResult);
    eventManager->TouchTest(touchPoint, frameNode, touchRestrict, offset, 0, true);
    EXPECT_EQ(touchPoint.isFalsified, false);
}
} // namespace OHOS::Ace::NG