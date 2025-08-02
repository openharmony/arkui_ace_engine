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

#include "test/unittest/core/event/event_manager_test_ng.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
constexpr int TOUCH_ID = 0;

class TouchDelegateTest : public TouchDelegate {
    void DelegateTouchEvent(const TouchEvent& point)
    {
        return;
    }
};
/**
 * @tc.name: ExecuteTouchTestDoneCallbackTest001
 * @tc.desc: Test ExecuteTouchTestDoneCallbackTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchEvent;
    touchEvent.deviceId = 1;
    touchEvent.force = 1.0f;
    touchEvent.pointers.push_back(TouchPoint());

    ResponseLinkResult responseLinkRecognizers;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal1, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    int32_t doneId = 0;
    int32_t doneInnerId = 0;
    auto touchTestDoneFunc = [&doneId](const std::shared_ptr<BaseGestureEvent>& event,
                                 const std::list<RefPtr<NGGestureRecognizer>>& recognizer) { doneId++; };
    auto touchTestDoneForInnerFunc = [&doneInnerId](const std::shared_ptr<BaseGestureEvent>& event,
                                         const std::list<RefPtr<NGGestureRecognizer>>& recognizer) { doneInnerId++; };
    eventHub->SetOnTouchTestDoneCallback(std::move(touchTestDoneFunc));
    eventHub->SetOnTouchTestDoneCallbackForInner(std::move(touchTestDoneForInnerFunc));
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(touchEvent, responseLinkRecognizers);
    EXPECT_NE(doneId, 0);
    EXPECT_NE(doneInnerId, 0);
}

/**
 * @tc.name: ExecuteTouchTestDoneCallbackTest002
 * @tc.desc: Test ExecuteTouchTestDoneCallbackTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest002, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchEvent;
    touchEvent.deviceId = 1;
    touchEvent.force = 1.0f;
    touchEvent.pointers.push_back(TouchPoint());

    ResponseLinkResult responseLinkRecognizers;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    int32_t doneId = 0;
    auto touchTestDoneFunc = [&doneId](const std::shared_ptr<BaseGestureEvent>& event,
                                 const std::list<RefPtr<NGGestureRecognizer>>& recognizer) { doneId++; };
    eventHub->SetOnTouchTestDoneCallback(std::move(touchTestDoneFunc));
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(touchEvent, responseLinkRecognizers);
    EXPECT_NE(doneId, 0);
}

/**
 * @tc.name: ExecuteTouchTestDoneCallbackTest003
 * @tc.desc: Test ExecuteTouchTestDoneCallbackTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest003, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchEvent;
    touchEvent.deviceId = 1;
    touchEvent.force = 1.0f;
    touchEvent.pointers.push_back(TouchPoint());

    ResponseLinkResult responseLinkRecognizers;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    int32_t doneInnerId = 0;
    auto touchTestDoneForInnerFunc = [&doneInnerId](const std::shared_ptr<BaseGestureEvent>& event,
                                         const std::list<RefPtr<NGGestureRecognizer>>& recognizer) { doneInnerId++; };
    eventHub->SetOnTouchTestDoneCallbackForInner(std::move(touchTestDoneForInnerFunc));
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(touchEvent, responseLinkRecognizers);
    EXPECT_NE(doneInnerId, 0);
}

/**
 * @tc.name: ExecuteTouchTestDoneCallbackTest004
 * @tc.desc: Test ExecuteTouchTestDoneCallbackTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest004, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchEvent;
    touchEvent.deviceId = 1;
    touchEvent.force = 1.0f;
    touchEvent.pointers.push_back(TouchPoint());

    ResponseLinkResult responseLinkRecognizers;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(touchEvent, responseLinkRecognizers);
    EXPECT_FALSE(eventManager->onTouchTestDoneFrameNodeList_.empty());
}

/**
 * @tc.name: ExecuteTouchTestDoneCallbackTest005
 * @tc.desc: Test ExecuteTouchTestDoneCallbackTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest005, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AxisEvent axisEvent;
    axisEvent.deviceId = 1;

    ResponseLinkResult responseLinkRecognizers;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    int32_t doneId = 0;
    int32_t doneInnerId = 0;
    auto touchTestDoneFunc = [&doneId](const std::shared_ptr<BaseGestureEvent>& event,
                                 const std::list<RefPtr<NGGestureRecognizer>>& recognizer) { doneId++; };
    auto touchTestDoneForInnerFunc = [&doneInnerId](const std::shared_ptr<BaseGestureEvent>& event,
                                         const std::list<RefPtr<NGGestureRecognizer>>& recognizer) { doneInnerId++; };
    eventHub->SetOnTouchTestDoneCallback(std::move(touchTestDoneFunc));
    eventHub->SetOnTouchTestDoneCallbackForInner(std::move(touchTestDoneForInnerFunc));
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(axisEvent, responseLinkRecognizers);
    EXPECT_NE(doneId, 0);
    EXPECT_NE(doneInnerId, 0);
}

/**
 * @tc.name: ExecuteTouchTestDoneCallbackTest006
 * @tc.desc: Test ExecuteTouchTestDoneCallbackTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest006, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AxisEvent axisEvent;
    axisEvent.deviceId = 1;

    ResponseLinkResult responseLinkRecognizers;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    int32_t doneId = 0;
    auto touchTestDoneFunc = [&doneId](const std::shared_ptr<BaseGestureEvent>& event,
                                 const std::list<RefPtr<NGGestureRecognizer>>& recognizer) { doneId++; };
    eventHub->SetOnTouchTestDoneCallback(std::move(touchTestDoneFunc));
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(axisEvent, responseLinkRecognizers);
    EXPECT_NE(doneId, 0);
}

/**
 * @tc.name: ExecuteTouchTestDoneCallbackTest007
 * @tc.desc: Test ExecuteTouchTestDoneCallbackTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest007, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AxisEvent axisEvent;
    axisEvent.deviceId = 1;

    ResponseLinkResult responseLinkRecognizers;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    int32_t doneInnerId = 0;
    auto touchTestDoneForInnerFunc = [&doneInnerId](const std::shared_ptr<BaseGestureEvent>& event,
                                         const std::list<RefPtr<NGGestureRecognizer>>& recognizer) { doneInnerId++; };
    eventHub->SetOnTouchTestDoneCallbackForInner(std::move(touchTestDoneForInnerFunc));
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(axisEvent, responseLinkRecognizers);
    EXPECT_NE(doneInnerId, 0);
}

/**
 * @tc.name: ExecuteTouchTestDoneCallbackTest008
 * @tc.desc: Test ExecuteTouchTestDoneCallbackTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest008, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AxisEvent axisEvent;
    axisEvent.deviceId = 1;

    ResponseLinkResult responseLinkRecognizers;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(axisEvent, responseLinkRecognizers);
    EXPECT_FALSE(eventManager->onTouchTestDoneFrameNodeList_.empty());
}

/**
 * @tc.name: AddTouchDelegate001
 * @tc.desc: Test AddTouchDelegate function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, AddTouchDelegate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create eventManager, delegate.
     * @tc.expected: recognizers is not null and axis direction is correct.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto delegate = AceType::MakeRefPtr<TouchDelegateTest>();
    ASSERT_NE(delegate, nullptr);

    /**
     * @tc.steps: step2. Call AddTouchDelegate twice.
     * @tc.expected: touchDelegatesMap_ is not empty and size is 2.
     */
    eventManager->AddTouchDelegate(TOUCH_ID, delegate);
    eventManager->AddTouchDelegate(TOUCH_ID, delegate);
    EXPECT_FALSE(eventManager->touchDelegatesMap_.empty());
    EXPECT_EQ(eventManager->touchDelegatesMap_[TOUCH_ID].size(), 2);

    /**
     * @tc.steps: step3. Call UpdateTouchDelegate.
     * @tc.expected: touchDelegatesMap_ is not empty and size is 1.
     */
    eventManager->UpdateTouchDelegate(TOUCH_ID, delegate);
    EXPECT_FALSE(eventManager->touchDelegatesMap_.empty());
    EXPECT_EQ(eventManager->touchDelegatesMap_[TOUCH_ID].size(), 1);

    /**
     * @tc.steps: step4. Call UpdateTouchDelegate when eventManager->touchDelegatesMap_ is empty.
     * @tc.expected: touchDelegatesMap_ is not empty and size is 1.
     */
    eventManager->UnregisterTouchDelegate(TOUCH_ID);
    EXPECT_TRUE(eventManager->touchDelegatesMap_.empty());
    eventManager->UpdateTouchDelegate(TOUCH_ID, delegate);
    EXPECT_FALSE(eventManager->touchDelegatesMap_.empty());
    EXPECT_EQ(eventManager->touchDelegatesMap_[TOUCH_ID].size(), 1);

    /**
     * @tc.steps: step5. Call UpdateTouchDelegate when eventManager->touchDelegatesMap_[TOUCH_ID] is empty.
     * @tc.expected: touchDelegatesMap_ is not empty and size is 1.
     */
    eventManager->touchDelegatesMap_[TOUCH_ID].clear();
    EXPECT_FALSE(eventManager->touchDelegatesMap_.empty());
    EXPECT_TRUE(eventManager->touchDelegatesMap_[TOUCH_ID].empty());
    eventManager->UpdateTouchDelegate(TOUCH_ID, delegate);
    EXPECT_FALSE(eventManager->touchDelegatesMap_.empty());
    EXPECT_EQ(eventManager->touchDelegatesMap_[TOUCH_ID].size(), 1);
}

/**
 * @tc.name: ExecuteTouchTestDoneCallbackTest009
 * @tc.desc: Test ExecuteTouchTestDoneCallbackTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest009, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchEvent;
    touchEvent.deviceId = 1;
    touchEvent.force = 1.0f;
    touchEvent.tiltX = 1.0f;
    touchEvent.tiltY = 1.0f;
    touchEvent.rollAngle = 1.0f;
    touchEvent.pointers.push_back(TouchPoint());

    ResponseLinkResult responseLinkRecognizers;
    auto panHorizontal1 = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());

    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(touchEvent, responseLinkRecognizers);
    EXPECT_FALSE(eventManager->onTouchTestDoneFrameNodeList_.empty());
}

/**
 * @tc.name: EventManagerTestAxisEvent001
 * @tc.desc: Test TouchTest with FrameNode AxisEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTestAxisEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Create FrameNode and Call TouchTest
     * @tc.expected: touchTestResults_ has the touchPoint.id of instance
     */
    const int nodeId = 10002;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;
    EXPECT_TRUE(eventManager->axisTouchTestResults_.empty());

    std::vector<AxisAction> actionVec = { AxisAction::NONE, AxisAction::BEGIN, AxisAction::UPDATE, AxisAction::END,
        AxisAction::CANCEL };
    for (auto i = 0; i < actionVec.size(); ++i) {
        AxisEvent axisEvent;
        axisEvent.sourceType = SourceType::TOUCH;
        axisEvent.action = actionVec[i];
        eventManager->TouchTest(axisEvent, frameNode, touchRestrict);
    }
    EXPECT_FALSE(eventManager->axisTouchTestResults_.empty());
}

/**
 * @tc.name: EventManagerHandleGlobal001
 * @tc.desc: Test HandleGlobalEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerHandleGlobal001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Do not Call TouchTest to add touchTestResults_[touchPoint.id]
     * @tc.expected: touchTestResults_ has the touchPoint.id of instance
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::DOWN;
    touchPoint.sourceType = SourceType::MOUSE;

    const int nodeId = 10003;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);

    /**
     * @tc.steps: step3. Create FrameNode and Call TouchTest to add touchTestResults_[touchPoint.id]
     * @tc.expected: selectOverlayManager->touchTestResults_ is empty for do not have specific event
     */
    EXPECT_TRUE(eventManager->touchTestResults_.empty());
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(frameNode);
    NG::OffsetF rootOffset;
    eventManager->HandleGlobalEventNG(touchPoint, selectOverlayManager, rootOffset);
    EXPECT_TRUE(selectOverlayManager->touchTestResults_.empty());
}

/**
 * @tc.name: EventManagerHandleOut001
 * @tc.desc: Test HandleOutOfRectCallback
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerHandleOut001, TestSize.Level1)
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

    auto rectGetCallback1 = [](std::vector<Rect>& rectList) -> void { rectList.push_back(Rect()); };
    auto rectGetCallback2 = [](std::vector<Rect>& rectList) -> void { rectList.push_back(Rect(0, 0, 100, 100)); };

    auto touchCallback = []() -> void {};
    auto mouseCallback = []() -> void {};
    std::vector<RectCallback> rectCallbackList {
        RectCallback(rectGetCallback1, touchCallback, mouseCallback),
        RectCallback(rectGetCallback2, touchCallback, mouseCallback),
        RectCallback(nullptr, touchCallback, mouseCallback),
        RectCallback(rectGetCallback2, touchCallback, nullptr)
    };

    /**
     * @tc.steps: step3. Call HandleOutOfRectCallback with SourceType::TOUCH
     * @tc.expected: rectCallbackList.size() is 3
     */
    eventManager->HandleOutOfRectCallback(point, rectCallbackList);
    EXPECT_EQ(rectCallbackList.size(), 3);

    /**
     * @tc.steps: step4. Call HandleOutOfRectCallback with SourceType::MOUSE
     * @tc.expected: rectCallbackList.size() is not empty
     */
    point.SetSourceType(SourceType::MOUSE);
    eventManager->HandleOutOfRectCallback(point, rectCallbackList);
    EXPECT_FALSE(rectCallbackList.empty());
}

/**
 * @tc.name: EventManagerFlushEnd001
 * @tc.desc: Test FlushTouchEventsEnd
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerFlushEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto resultId = ElementRegister::GetInstance()->MakeUniqueId();
    TouchTestResult touchTestResults;

    touchTestResults.push_back(AceType::MakeRefPtr<MockTouchEventTarget>());
    eventManager->touchTestResults_.emplace(resultId, touchTestResults);

    TouchEvent event {};
    event.id = 1;
    std::list<TouchEvent> touchEvents { event };
    eventManager->FlushTouchEventsEnd(touchEvents);
    EXPECT_EQ(eventManager->touchTestResults_.find(event.id), eventManager->touchTestResults_.end());

    TouchEvent event2 {};
    event2.id = resultId;
    event2.history.push_back(event);
    std::list<TouchEvent> touchEvents2 { event2 };
    eventManager->FlushTouchEventsEnd(touchEvents2);
    EXPECT_NE(eventManager->touchTestResults_.find(event2.id), eventManager->touchTestResults_.end());
}

/**
 * @tc.name: EventManagerClearPenStylus001
 * @tc.desc: Test ClearTouchTestTargetForPenStylus func
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerClearPenStylus001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto resultId = ElementRegister::GetInstance()->MakeUniqueId();
    TouchTestResult touchTestResults;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::NONE }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    touchTestResults.push_back(panRecognizer);
    eventManager->touchTestResults_.emplace(resultId, touchTestResults);
    TouchEvent event;
    event.id = resultId;
    RefPtr<GestureScope> scope = AceType::MakeRefPtr<GestureScope>(resultId);
    ASSERT_NE(scope, nullptr);
    ASSERT_NE(eventManager->refereeNG_, nullptr);
    scope->AddMember(panRecognizer);
    eventManager->refereeNG_->gestureScopes_.insert(std::make_pair(resultId, scope));
    eventManager->referee_->gestureScopes_.insert(std::make_pair(resultId, scope));
    eventManager->downFingerIds_[1] = 1;
    eventManager->ClearTouchTestTargetForPenStylus(event);
    EXPECT_EQ(event.id, 1);
}

/**
 * @tc.name: EventManagerClearHover001
 * @tc.desc: Test CleanHoverStatusForDragBegin.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerClearHover001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    MouseEvent event;
    TouchTestResult touchTestResults;
    auto eventTarget = AceType::MakeRefPtr<MockTouchEventTarget>();
    touchTestResults.push_back(eventTarget);
    eventManager->mouseTestResults_.emplace(event.id, touchTestResults);
    eventManager->CleanHoverStatusForDragBegin();
    EXPECT_TRUE(eventManager->mouseTestResults_.empty());
}

/**
 * @tc.name: EventManagerClearHover002
 * @tc.desc: Test CleanHoverStatusForDragBegin.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerClearHover002, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));

    MouseEvent event;
    TouchTestResult touchTestResults;
    auto eventTarget = AceType::MakeRefPtr<MockTouchEventTarget>();
    touchTestResults.push_back(eventTarget);
    eventManager->mouseTestResults_.emplace(event.id, touchTestResults);
    eventManager->CleanHoverStatusForDragBegin();
    EXPECT_FALSE(eventManager->mouseTestResults_.empty());
}

/**
 * @tc.name: EventManagerUpdateHover001
 * @tc.desc: Test UpdateAccessibilityHoverNode.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerUpdateHover001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int32_t doneId = 0;
    TouchEvent event;
    TouchTestResult touchTestResults;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::NONE }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    touchTestResults.push_back(panRecognizer);
    eventManager->UpdateAccessibilityHoverNode(event, touchTestResults);
    EXPECT_EQ(doneId, 0);

    touchTestResults.clear();
    const int nodeId = 10008;
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    touchTestResults.push_back(hoverEventTarget);
    eventManager->UpdateAccessibilityHoverNode(event, touchTestResults);
    EXPECT_EQ(doneId, 0);

    touchTestResults.clear();
    hoverEventTarget->SetAccessibilityHoverCallback(nullptr);
    touchTestResults.push_back(hoverEventTarget);
    eventManager->UpdateAccessibilityHoverNode(event, touchTestResults);
    EXPECT_EQ(doneId, 0);

    touchTestResults.clear();
    auto OnAccessibilityHoverFunc = [&doneId](bool, AccessibilityHoverInfo& info) { ++doneId; };
    hoverEventTarget->SetAccessibilityHoverCallback(OnAccessibilityHoverFunc);
    touchTestResults.push_back(hoverEventTarget);
    eventManager->UpdateAccessibilityHoverNode(event, touchTestResults);
    EXPECT_EQ(doneId, 0);
}

/**
 * @tc.name: EventManagerDispatchHover001
 * @tc.desc: Test HandleMouseHoverAnimation
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerDispatchHover001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    MouseEvent event;

    eventManager->currHoverNode_ = nullptr;
    eventManager->lastHoverNode_ = nullptr;

    event.action = MouseAction::WINDOW_ENTER;
    eventManager->DispatchMouseHoverAnimationNG(event, true);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);

    event.action = MouseAction::WINDOW_LEAVE;
    eventManager->DispatchMouseHoverAnimationNG(event, true);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);

    eventManager->currHoverNode_ = FrameNode::GetOrCreateFrameNode(CTRL, 0, nullptr);
    eventManager->lastHoverNode_ = FrameNode::GetOrCreateFrameNode(CTRL, 0, nullptr);

    event.action = MouseAction::WINDOW_ENTER;
    eventManager->DispatchMouseHoverAnimationNG(event, true);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);

    event.action = MouseAction::WINDOW_LEAVE;
    eventManager->DispatchMouseHoverAnimationNG(event, true);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: CheckMousePendingRecognizersState001
 * @tc.desc: Test CheckMousePendingRecognizersState function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, CheckMousePendingRecognizersState001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    auto panHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    panHorizontal->refereeState_ = RefereeState::SUCCEED;

    TouchEvent touchEvent;
    touchEvent.sourceType = SourceType::MOUSE;

    eventManager->AddToMousePendingRecognizers(panHorizontal);
    eventManager->CheckMousePendingRecognizersState(touchEvent);
    EXPECT_TRUE(eventManager->mousePendingRecognizers_.empty());

    eventManager->CheckMousePendingRecognizersState(touchEvent);
    EXPECT_TRUE(eventManager->mousePendingRecognizers_.empty());

    panHorizontal->refereeState_ = RefereeState::PENDING;
    eventManager->AddToMousePendingRecognizers(panHorizontal);
    eventManager->CheckMousePendingRecognizersState(touchEvent);
    EXPECT_TRUE(eventManager->mousePendingRecognizers_.empty());

    panHorizontal->refereeState_ = RefereeState::PENDING_BLOCKED;
    eventManager->AddToMousePendingRecognizers(panHorizontal);
    eventManager->CheckMousePendingRecognizersState(touchEvent);
    EXPECT_TRUE(eventManager->mousePendingRecognizers_.empty());

    touchEvent.sourceType = SourceType::TOUCH;
    eventManager->AddToMousePendingRecognizers(panHorizontal);
    eventManager->CheckMousePendingRecognizersState(touchEvent);
    EXPECT_TRUE(eventManager->mousePendingRecognizers_.empty());
}

/**
 * @tc.name: DumpEventWithCount001
 * @tc.desc: Test DumpEventWithCount function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, DumpEventWithCount001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    NG::EventTreeType type = EventTreeType::TOUCH;
    bool hasJson = false;
    std::string param0 = "dump";
    std::string param1 = "-n";
    std::string param2 = "0";
    std::string param3 = "any";
    std::string param4 = "-d";
    std::string param5 = "3";
    std::string param6 = "6";

    std::vector<std::string> params0 = { param0 };
    eventManager->DumpEventWithCount(params0, type, hasJson);
    std::vector<std::string> params1 = { param0, param1 };
    eventManager->DumpEventWithCount(params1, type, hasJson);
    std::vector<std::string> params2 = { param0, param1, param2 };
    eventManager->DumpEventWithCount(params2, type, hasJson);
    std::vector<std::string> params3 = { param0, param1, param2, param3 };
    eventManager->DumpEventWithCount(params3, type, hasJson);
    std::vector<std::string> params4 = { param0, param4, param2, param3 };
    eventManager->DumpEventWithCount(params3, type, hasJson);
    std::vector<std::string> params5 = { param0, param1, param6, param3 };
    eventManager->DumpEventWithCount(params5, type, hasJson);
    std::vector<std::string> params6 = { param0, param1, param5, param3 };
    eventManager->DumpEventWithCount(params6, type, hasJson);
    EXPECT_FALSE(hasJson);
}

/**
 * @tc.name: TouchDelegate002
 * @tc.desc: Test TouchDelegate
 */
HWTEST_F(EventManagerTestNg, TouchDelegate002, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    int32_t touchId = -1;
    auto delegater1 = AceType::MakeRefPtr<NG::TouchDelegate>();
    auto delegater2 = AceType::MakeRefPtr<NG::TouchDelegate>();

    auto handler = eventManager->AddTouchDelegate(touchId, delegater1);
    handler = eventManager->UpdateTouchDelegate(touchId, delegater2);
    eventManager->touchDelegatesMap_.clear();
    eventManager->UnregisterTouchDelegate(handler);
    EXPECT_TRUE(eventManager->touchDelegatesMap_.empty());

    handler = eventManager->AddTouchDelegate(touchId, delegater1);
    EXPECT_EQ(eventManager->touchDelegatesMap_[touchId].size(), 1);
    eventManager->UnregisterTouchDelegate(touchId - 1);
    eventManager->UnregisterTouchDelegate(touchId);
    EXPECT_TRUE(eventManager->touchDelegatesMap_.empty());

    TouchEvent touchEvent;
    touchEvent.id = touchId;
    eventManager->DelegateTouchEvent(touchEvent);
}

/**
 * @tc.name: TouchDelegate003
 * @tc.desc: Test TouchDelegate
 */
HWTEST_F(EventManagerTestNg, TouchDelegate003, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    int32_t touchId = 1;
    auto delegater1 = AceType::MakeRefPtr<NG::TouchDelegate>();
    auto delegater2 = AceType::MakeRefPtr<NG::TouchDelegate>();

    auto handler = eventManager->AddTouchDelegate(touchId, delegater1);
    handler = eventManager->UpdateTouchDelegate(touchId, delegater2);
    eventManager->touchDelegatesMap_.clear();
    eventManager->UnregisterTouchDelegate(handler);
    EXPECT_TRUE(eventManager->touchDelegatesMap_.empty());

    handler = eventManager->AddTouchDelegate(touchId, delegater1);
    EXPECT_EQ(eventManager->touchDelegatesMap_[touchId].size(), 1);
    eventManager->UnregisterTouchDelegate(touchId - 1);
    eventManager->UnregisterTouchDelegate(touchId);
    EXPECT_TRUE(eventManager->touchDelegatesMap_.empty());

    TouchEvent touchEvent;
    touchEvent.id = touchId;
    eventManager->DelegateTouchEvent(touchEvent);
}

/**
 * @tc.name: TryResampleTouchEvent001
 * @tc.desc: Test TryResampleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, TryResampleTouchEvent001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    std::vector<TouchEvent> history;
    std::vector<TouchEvent> current;
    TouchEvent touchEvent1;
    touchEvent1.SetTargetDisplayId(1);
    TouchEvent touchEvent2;
    touchEvent2.SetTargetDisplayId(1);

    uint64_t resampleTime1 = 0.5 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    touchEvent1.time = ts1;
    uint64_t resampleTime2 = 3 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds2(resampleTime2);
    TimeStamp ts2(nanoseconds2);
    touchEvent2.time = ts2;
    current.push_back(touchEvent1);
    current.push_back(touchEvent2);
    TouchEvent resample;
    uint64_t resampleTime = 4 * 1000 * 1000;

    SystemProperties::debugEnabled_ = true;
    bool ret = eventManager->TryResampleTouchEvent(history, current, resampleTime, resample);
    EXPECT_TRUE(ret);

    SystemProperties::debugEnabled_ = false;
    ret = eventManager->TryResampleTouchEvent(history, current, resampleTime, resample);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TryResampleTouchEvent002
 * @tc.desc: Test TryResampleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, TryResampleTouchEvent002, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    std::vector<TouchEvent> history;
    std::vector<TouchEvent> current;
    TouchEvent resample;
    uint64_t resampleTime = 4 * 1000 * 1000;

    SystemProperties::debugEnabled_ = true;
    bool ret = eventManager->TryResampleTouchEvent(history, current, resampleTime, resample);
    EXPECT_FALSE(ret);

    TouchEvent touchEvent1;
    touchEvent1.SetTargetDisplayId(1);
    TouchEvent touchEvent2;
    touchEvent2.SetTargetDisplayId(2);
    current.push_back(touchEvent1);
    current.push_back(touchEvent2);
    ret = eventManager->TryResampleTouchEvent(history, current, resampleTime, resample);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: GetResampleTouchEvent005
 * @tc.desc: Test GetResampleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetResampleTouchEvent005, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    std::vector<TouchEvent> history;
    std::vector<TouchEvent> current;
    TouchEvent touchEvent1;
    touchEvent1.SetTargetDisplayId(1);
    TouchEvent touchEvent2;
    touchEvent2.SetTargetDisplayId(2);

    uint64_t resampleTime1 = 2 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    touchEvent1.time = ts1;
    touchEvent2.time = ts1;
    current.push_back(touchEvent1);
    current.push_back(touchEvent2);
    TouchEvent newEvent;
    uint64_t resampleTime = 3 * 1000 * 1000;

    SystemProperties::debugEnabled_ = true;
    bool ret = eventManager->GetResampleTouchEvent(history, current, resampleTime, newEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: GetResampleTouchEvent006
 * @tc.desc: Test GetResampleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetResampleTouchEvent006, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    std::vector<TouchEvent> history;
    std::vector<TouchEvent> current;
    TouchEvent touchEvent1;
    touchEvent1.SetTargetDisplayId(1);
    TouchEvent touchEvent2;
    touchEvent2.SetTargetDisplayId(2);

    uint64_t resampleTime1 = 2 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    touchEvent1.time = ts1;
    touchEvent2.time = ts1;
    current.push_back(touchEvent1);
    current.push_back(touchEvent2);
    TouchEvent newEvent;
    uint64_t resampleTime = 1 * 1000 * 1000;

    SystemProperties::debugEnabled_ = true;
    bool ret = eventManager->GetResampleTouchEvent(history, current, resampleTime, newEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: GetResampleMouseEvent005
 * @tc.desc: Test GetResampleMouseEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetResampleMouseEvent005, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    std::vector<MouseEvent> history;
    std::vector<MouseEvent> current;
    MouseEvent mouseEvent1;
    mouseEvent1.targetDisplayId = 1;
    MouseEvent mouseEvent2;
    mouseEvent2.targetDisplayId = 2;

    uint64_t resampleTime1 = 2 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    mouseEvent1.time = ts1;
    mouseEvent2.time = ts1;
    current.push_back(mouseEvent1);
    current.push_back(mouseEvent2);
    uint64_t resampleTime = 3 * 1000 * 1000;

    SystemProperties::debugEnabled_ = true;
    auto mouseEvent = eventManager->GetResampleMouseEvent(history, current, resampleTime);
    EXPECT_EQ(mouseEvent.x, 0.0f);
}

/**
 * @tc.name: GetResampleMouseEvent006
 * @tc.desc: Test GetResampleMouseEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetResampleMouseEvent006, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    std::vector<MouseEvent> history;
    std::vector<MouseEvent> current;
    MouseEvent mouseEvent1;
    mouseEvent1.targetDisplayId = 1;
    MouseEvent mouseEvent2;
    mouseEvent2.targetDisplayId = 2;

    uint64_t resampleTime1 = 2 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    mouseEvent1.time = ts1;
    mouseEvent2.time = ts1;
    current.push_back(mouseEvent1);
    current.push_back(mouseEvent2);
    uint64_t resampleTime = 1 * 1000 * 1000;

    SystemProperties::debugEnabled_ = true;
    auto mouseEvent = eventManager->GetResampleMouseEvent(history, current, resampleTime);
    EXPECT_EQ(mouseEvent.x, 0.0f);
}

/**
 * @tc.name: GetResamplePointerEvent005
 * @tc.desc: Test GetResamplePointerEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetResamplePointerEvent005, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    std::vector<DragPointerEvent> history;
    std::vector<DragPointerEvent> current;
    DragPointerEvent dragPointerEvent1;
    dragPointerEvent1.targetWindowId = 1;
    DragPointerEvent dragPointerEvent2;
    dragPointerEvent2.targetWindowId = 2;

    uint64_t resampleTime1 = 2 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    dragPointerEvent1.time = ts1;
    dragPointerEvent2.time = ts1;
    current.push_back(dragPointerEvent1);
    current.push_back(dragPointerEvent2);
    uint64_t resampleTime = 3 * 1000 * 1000;

    SystemProperties::debugEnabled_ = true;
    auto dragPointerEvent = eventManager->GetResamplePointerEvent(history, current, resampleTime);
    EXPECT_EQ(dragPointerEvent.x, 0.0f);
}

/**
 * @tc.name: GetResamplePointerEvent006
 * @tc.desc: Test GetResamplePointerEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetResamplePointerEvent006, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    std::vector<DragPointerEvent> history;
    std::vector<DragPointerEvent> current;
    DragPointerEvent dragPointerEvent1;
    dragPointerEvent1.targetWindowId = 1;
    DragPointerEvent dragPointerEvent2;
    dragPointerEvent2.targetWindowId = 2;

    uint64_t resampleTime1 = 2 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    dragPointerEvent1.time = ts1;
    dragPointerEvent2.time = ts1;
    current.push_back(dragPointerEvent1);
    current.push_back(dragPointerEvent2);
    uint64_t resampleTime = 1 * 1000 * 1000;

    SystemProperties::debugEnabled_ = true;
    auto dragPointerEvent = eventManager->GetResamplePointerEvent(history, current, resampleTime);
    EXPECT_EQ(dragPointerEvent.x, 0.0f);
}

/**
 * @tc.name: GetResampleTouchEvent0012
 * @tc.desc: Test GetResampleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetResampleTouchEvent0012, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    std::vector<TouchEvent> history;
    std::vector<TouchEvent> current;
    TouchEvent touchEvent1;
    touchEvent1.SetTargetDisplayId(1);
    TouchEvent touchEvent2;
    touchEvent2.SetTargetDisplayId(1);

    uint64_t resampleTime1 = 2 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    touchEvent1.time = ts1;
    touchEvent2.time = ts1;
    history.push_back(touchEvent1);
    
    TouchEvent newEvent;
    uint64_t resampleTime = 3 * 1000 * 1000 + 20 * 1000 * 1000;
    std::vector<std::pair<float, float>> xyVec = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}};
    for (auto xy : xyVec) {
        current.clear();
        touchEvent2.x = xy.first;
        touchEvent2.y = xy.second;
        current.push_back(touchEvent2);

        SystemProperties::debugEnabled_ = true;
        bool ret = eventManager->GetResampleTouchEvent(history, current, resampleTime, newEvent);
        if (xy.first == 1.0f && xy.second == 1.0f) {
            EXPECT_TRUE(ret);
        } else {
            EXPECT_FALSE(ret);
        }

        SystemProperties::debugEnabled_ = false;
        ret = eventManager->GetResampleTouchEvent(history, current, resampleTime, newEvent);
        if (xy.first == 1.0f && xy.second == 1.0f) {
            EXPECT_TRUE(ret);
        } else {
            EXPECT_FALSE(ret);
        }
    }
}

/**
 * @tc.name: GetResampleMouseEvent0012
 * @tc.desc: Test GetResampleMouseEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetResampleMouseEvent0012, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    std::vector<MouseEvent> history;
    std::vector<MouseEvent> current;
    MouseEvent mouseEvent1;
    mouseEvent1.targetDisplayId = 1;
    MouseEvent mouseEvent2;
    mouseEvent2.targetDisplayId = 1;

    uint64_t resampleTime1 = 2 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    mouseEvent1.time = ts1;
    mouseEvent2.time = ts1;
    history.push_back(mouseEvent1);
    uint64_t resampleTime = 3 * 1000 * 1000 + 20 * 1000 * 1000;

    std::vector<std::pair<float, float>> xyVec = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}};
    for (auto xy : xyVec) {
        current.clear();
        mouseEvent2.x = xy.first;
        mouseEvent2.y = xy.second;
        current.push_back(mouseEvent2);

        SystemProperties::debugEnabled_ = true;
        auto mouseEvent = eventManager->GetResampleMouseEvent(history, current, resampleTime);
        EXPECT_EQ(mouseEvent.x, xy.first);

        SystemProperties::debugEnabled_ = false;
        mouseEvent = eventManager->GetResampleMouseEvent(history, current, resampleTime);
        EXPECT_EQ(mouseEvent.x, xy.first);
    }
}

/**
 *
 * @tc.name: GetResamplePointerEvent0012
 * @tc.desc: Test GetResamplePointerEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetResamplePointerEvent0012, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    std::vector<DragPointerEvent> history;
    std::vector<DragPointerEvent> current;
    DragPointerEvent dragPointerEvent1;
    dragPointerEvent1.targetWindowId = 1;
    DragPointerEvent dragPointerEvent2;
    dragPointerEvent2.targetWindowId = 1;

    uint64_t resampleTime1 = 2 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    dragPointerEvent1.time = ts1;
    dragPointerEvent2.time = ts1;
    history.push_back(dragPointerEvent1);
    uint64_t resampleTime = 3 * 1000 * 1000 + 20 * 1000 * 1000;

    std::vector<std::pair<float, float>> xyVec = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}};
    for (auto xy : xyVec) {
        current.clear();
        dragPointerEvent2.x = xy.first;
        dragPointerEvent2.y = xy.second;
        current.push_back(dragPointerEvent2);

        SystemProperties::debugEnabled_ = true;
        auto dragPointerEvent = eventManager->GetResamplePointerEvent(history, current, resampleTime);
        EXPECT_EQ(dragPointerEvent.x, xy.first);

        SystemProperties::debugEnabled_ = false;
        dragPointerEvent = eventManager->GetResamplePointerEvent(history, current, resampleTime);
        EXPECT_EQ(dragPointerEvent.x, xy.first);
    }
}

/**
 * @tc.name: OnNonPointerEvent001
 * @tc.desc: Test OnNonPointerEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, OnNonPointerEvent001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    NonPointerEvent event;
    event.eventType = UIInputEventType::KEY;
    auto ret = eventManager->OnNonPointerEvent(event);
    EXPECT_FALSE(ret);

    NonPointerEvent event2;
    event2.eventType = UIInputEventType::FOCUS_AXIS;
    ret = eventManager->OnNonPointerEvent(event2);
    EXPECT_FALSE(ret);

    NonPointerEvent event3;
    event3.eventType = UIInputEventType::CROWN;
    ret = eventManager->OnNonPointerEvent(event3);
    EXPECT_FALSE(ret);

    NonPointerEvent event4;
    event4.eventType = UIInputEventType::TOUCH;
    ret = eventManager->OnNonPointerEvent(event4);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleMouseHoverAnimation001
 * @tc.desc: Test HandleMouseHoverAnimation
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, HandleMouseHoverAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    MouseEvent event;
    /**
     * @tc.steps: step2. Test mock event.
     * @tc.expected: currHoverNode is not null.
     */
    eventManager->currHoverNode_ = FrameNode::GetOrCreateFrameNode(CTRL, 0, nullptr);
    eventManager->lastHoverNode_ = FrameNode::GetOrCreateFrameNode(CTRL, 1, nullptr);
    event.action = MouseAction::WINDOW_LEAVE;
    eventManager->DispatchMouseHoverAnimationNG(event, true);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);
    eventManager->lastHoverNode_ = nullptr;
    event.action = MouseAction::WINDOW_LEAVE;
    eventManager->DispatchMouseHoverAnimationNG(event, true);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);
    /**
     * @tc.steps: step3. Test normal event.
     * @tc.expected: currHoverNode is not null.
     */
    eventManager->currHoverNode_ = FrameNode::GetOrCreateFrameNode(CTRL, 0, nullptr);
    eventManager->lastHoverNode_ = FrameNode::GetOrCreateFrameNode(CTRL, 1, nullptr);
    event.action = MouseAction::WINDOW_LEAVE;
    eventManager->DispatchMouseHoverAnimationNG(event, false);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);
    eventManager->lastHoverNode_ = nullptr;
    event.action = MouseAction::WINDOW_LEAVE;
    eventManager->DispatchMouseHoverAnimationNG(event, false);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: UpdateInfoWhenFinishDispatch001
 * @tc.desc: Test UpdateInfoWhenFinishDispatch function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, UpdateInfoWhenFinishDispatch001, TestSize.Level1)
{
    /**
     * @tc.step1: Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.step2: Set refereeNG_ and touchTestResults_.
     * @tc.expected: refereeNG_ and touchTestResults_ not null.
     */
    auto resultId = ElementRegister::GetInstance()->MakeUniqueId();
    TouchTestResult touchTestResults;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::NONE }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    panRecognizer->OnPending();
    touchTestResults.push_back(panRecognizer);
    eventManager->touchTestResults_.emplace(resultId, touchTestResults);
    RefPtr<GestureScope> scope = AceType::MakeRefPtr<GestureScope>(resultId);
    ASSERT_NE(scope, nullptr);
    ASSERT_NE(eventManager->refereeNG_, nullptr);
    scope->AddMember(panRecognizer);
    eventManager->refereeNG_->gestureScopes_.insert(std::make_pair(resultId, scope));
    TouchEvent event;
    event.id = resultId;
    event.type = TouchType::UP;
    event.sourceTool = SourceTool::FINGER;
    event.isFalsified = true;

    /**
     * @tc.step3: Set refereeNG_ and touchTestResults_.
     * @tc.expected: refereeNG_ and touchTestResults_ not null.
     */
    eventManager->UpdateInfoWhenFinishDispatch(event, true);
    EXPECT_FALSE(eventManager->touchTestResults_.empty());

    event.type = TouchType::DOWN;
    eventManager->UpdateInfoWhenFinishDispatch(event, true);
    EXPECT_FALSE(eventManager->touchTestResults_.empty());

    event.type = TouchType::CANCEL;
    eventManager->UpdateInfoWhenFinishDispatch(event, true);
    EXPECT_FALSE(eventManager->touchTestResults_.empty());

    event.type = TouchType::UP;
    event.isFalsified = false;
    eventManager->UpdateInfoWhenFinishDispatch(event, true);
    EXPECT_EQ(eventManager->lastSourceTool_, SourceTool::FINGER);

    event.type = TouchType::CANCEL;
    event.isFalsified = false;
    eventManager->lastSourceTool_ = SourceTool::UNKNOWN;
    eventManager->UpdateInfoWhenFinishDispatch(event, true);
    EXPECT_EQ(eventManager->lastSourceTool_, SourceTool::FINGER);
}
} // namespace OHOS::Ace::NG