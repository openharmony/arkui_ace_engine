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
#include "core/common/event_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

// Define RectCallback and RectCallbackListImpl for test access
// These structures are defined in event_manager.cpp and are not exposed in the header
struct RectCallback {
    ~RectCallback() = default;
    std::function<void(std::vector<Rect>&)> rectGetCallback;
    std::function<void()> touchCallback;
    std::function<void()> mouseCallback;
};

struct RectCallbackListImpl {
    std::vector<RectCallback> callbacks;
};

} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
constexpr int TOUCH_ID = 0;
constexpr size_t MAX_HISTORY_TOUCH_INFO_SIZE = 2048;

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
                                 const std::list<WeakPtr<NGGestureRecognizer>>& recognizer) { doneId++; };
    auto touchTestDoneForInnerFunc = [&doneInnerId](const std::shared_ptr<BaseGestureEvent>& event,
                                         const std::list<WeakPtr<NGGestureRecognizer>>& recognizer) { doneInnerId++; };
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
                                 const std::list<WeakPtr<NGGestureRecognizer>>& recognizer) { doneId++; };
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
                                         const std::list<WeakPtr<NGGestureRecognizer>>& recognizer) { doneInnerId++; };
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
                                 const std::list<WeakPtr<NGGestureRecognizer>>& recognizer) { doneId++; };
    auto touchTestDoneForInnerFunc = [&doneInnerId](const std::shared_ptr<BaseGestureEvent>& event,
                                         const std::list<WeakPtr<NGGestureRecognizer>>& recognizer) { doneInnerId++; };
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
                                 const std::list<WeakPtr<NGGestureRecognizer>>& recognizer) { doneId++; };
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
                                         const std::list<WeakPtr<NGGestureRecognizer>>& recognizer) { doneInnerId++; };
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
 * @tc.name: ExecuteTouchTestDoneCallbackTest010
 * @tc.desc: Test touch onTouchTestDone finger current local getter.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest010, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchEvent;
    TouchPoint point;
    point.x = 10.0f;
    point.y = 20.0f;
    point.screenX = 30.0f;
    point.screenY = 40.0f;
    point.globalDisplayX = 50.0f;
    point.globalDisplayY = 60.0f;
    point.originalId = 1;
    touchEvent.pointers.push_back(point);

    ResponseLinkResult responseLinkRecognizers;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    bool hasCurrentLocalGetter = false;
    Offset currentLocal;
    Offset local;
    auto touchTestDoneFunc = [&hasCurrentLocalGetter, &currentLocal, &local](
                                 const std::shared_ptr<BaseGestureEvent>& event,
                                 const std::list<WeakPtr<NGGestureRecognizer>>& recognizer) {
        if (!event || event->GetFingerList().empty()) {
            return;
        }
        const auto& fingerInfo = event->GetFingerList().front();
        hasCurrentLocalGetter = static_cast<bool>(fingerInfo.currentLocalLocation_);
        local = fingerInfo.localLocation_;
        if (fingerInfo.currentLocalLocation_) {
            currentLocal = fingerInfo.currentLocalLocation_();
        }
    };
    eventHub->SetOnTouchTestDoneCallback(std::move(touchTestDoneFunc));
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(touchEvent, responseLinkRecognizers);
    EXPECT_TRUE(hasCurrentLocalGetter);
    EXPECT_DOUBLE_EQ(currentLocal.GetX(), local.GetX());
    EXPECT_DOUBLE_EQ(currentLocal.GetY(), local.GetY());
}

/**
 * @tc.name: ExecuteTouchTestDoneCallbackTest011
 * @tc.desc: Test axis onTouchTestDone finger current local getter.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExecuteTouchTestDoneCallbackTest011, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AxisEvent axisEvent;
    axisEvent.x = 11.0f;
    axisEvent.y = 21.0f;
    axisEvent.screenX = 31.0f;
    axisEvent.screenY = 41.0f;
    axisEvent.globalDisplayX = 51.0f;
    axisEvent.globalDisplayY = 61.0f;
    axisEvent.originalId = 2;

    ResponseLinkResult responseLinkRecognizers;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    bool hasCurrentLocalGetter = false;
    Offset currentLocal;
    Offset local;
    auto touchTestDoneFunc = [&hasCurrentLocalGetter, &currentLocal, &local](
                                 const std::shared_ptr<BaseGestureEvent>& event,
                                 const std::list<WeakPtr<NGGestureRecognizer>>& recognizer) {
        if (!event || event->GetFingerList().empty()) {
            return;
        }
        const auto& fingerInfo = event->GetFingerList().front();
        hasCurrentLocalGetter = static_cast<bool>(fingerInfo.currentLocalLocation_);
        local = fingerInfo.localLocation_;
        if (fingerInfo.currentLocalLocation_) {
            currentLocal = fingerInfo.currentLocalLocation_();
        }
    };
    eventHub->SetOnTouchTestDoneCallback(std::move(touchTestDoneFunc));
    eventManager->onTouchTestDoneFrameNodeList_.emplace_back(WeakPtr<NG::FrameNode>(frameNode));
    eventManager->ExecuteTouchTestDoneCallback(axisEvent, responseLinkRecognizers);
    EXPECT_TRUE(hasCurrentLocalGetter);
    EXPECT_DOUBLE_EQ(currentLocal.GetX(), local.GetX());
    EXPECT_DOUBLE_EQ(currentLocal.GetY(), local.GetY());
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
    eventManager->AddRectCallback(
        [rectGetCallback1](std::vector<Rect>& rectList) -> void { rectGetCallback1(rectList); },
        touchCallback, mouseCallback);
    eventManager->AddRectCallback(
        [rectGetCallback2](std::vector<Rect>& rectList) -> void { rectGetCallback2(rectList); },
        touchCallback, mouseCallback);
    eventManager->AddRectCallback(nullptr, touchCallback, mouseCallback);
    eventManager->AddRectCallback(
        [rectGetCallback2](std::vector<Rect>& rectList) -> void { rectGetCallback2(rectList); },
        touchCallback, nullptr);
    ASSERT_NE(eventManager->rectCallbackListImpl_, nullptr);

    /**
     * @tc.steps: step3. Call HandleOutOfRectCallbacks with SourceType::TOUCH
     * @tc.expected: callbacks are processed for touch
     */
    eventManager->HandleOutOfRectCallbacks(point);
    EXPECT_EQ(eventManager->rectCallbackListImpl_->callbacks.size(), 3);

    /**
     * @tc.steps: step4. Call HandleOutOfRectCallbacks with SourceType::MOUSE
     * @tc.expected: remaining callbacks are processed for mouse
     */
    point.SetSourceType(SourceType::MOUSE);
    eventManager->HandleOutOfRectCallbacks(point);
    EXPECT_EQ(eventManager->rectCallbackListImpl_->callbacks.size(), 0);
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
    eventManager->lastMouseEvent_ = event;
    auto eventTarget = AceType::MakeRefPtr<MockTouchEventTarget>();
    touchTestResults.push_back(eventTarget);
    eventManager->mouseTestResults_.emplace(event.id, touchTestResults);
    eventManager->CleanHoverStatusForDragBegin();
    EXPECT_TRUE(eventManager->mouseTestResults_.empty());
    EXPECT_EQ(eventManager->lastMouseEvent_.id, event.id);
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
 * @tc.name: GetResamplePointerEvent001
 * @tc.desc: Test GetResamplePointerEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetResamplePointerEvent001, TestSize.Level1)
{
    std::vector<TouchEvent> events;
    TouchEvent touchEvent1;
    TouchEvent touchEvent2;

    uint64_t resampleTime1 = 0.5 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds1(resampleTime1);
    TimeStamp ts1(nanoseconds1);
    touchEvent1.time = ts1;
    uint64_t resampleTime2 = 3 * 1000 * 1000;
    std::chrono::nanoseconds nanoseconds2(resampleTime2);
    TimeStamp ts2(nanoseconds2);
    touchEvent2.time = ts2;
    events.push_back(touchEvent1);
    events.push_back(touchEvent2);
    TouchEvent resample;
    uint64_t resampleTime = 4 * 1000 * 1000;

    ResamplePoint slope;
    SystemProperties::debugEnabled_ = true;
    bool ret = ResampleAlgo::GetResamplePointerEvent(events, resampleTime, resample, slope);
    EXPECT_TRUE(ret);
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
    dragPointerEvent1.displayId = 1;
    DragPointerEvent dragPointerEvent2;
    dragPointerEvent2.displayId = 2;

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
    dragPointerEvent1.displayId = 1;
    DragPointerEvent dragPointerEvent2;
    dragPointerEvent2.displayId = 2;

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
    dragPointerEvent1.displayId = 1;
    DragPointerEvent dragPointerEvent2;
    dragPointerEvent2.displayId = 1;

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

/**
 * @tc.name: CleanRefereeBeforeTouchTest001
 * @tc.desc: Test CleanRefereeBeforeTouchTest function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, CleanRefereeBeforeTouchTest001, TestSize.Level1)
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
    eventManager->refereeNG_->gestureScopes_.insert(std::make_pair(resultId, scope));
    eventManager->lastDownFingerNumber_ = 0;
    TouchEvent event;
    event.id = resultId;
    event.type = TouchType::UP;
    event.sourceTool = SourceTool::FINGER;
    event.isFalsified = true;

    /**
     * @tc.step3: Call CleanRefereeBeforeTouchTest.
     * @tc.expected: refereeNG_->gestureScopes_.empty() is true.
     */
    eventManager->CleanRefereeBeforeTouchTest(event, true);
    EXPECT_EQ(eventManager->refereeNG_->gestureScopes_.empty(), true);
}

/**
 *
 * @tc.name: FalsifyCancelEventWithDifferentDeviceId001
 * @tc.desc: Test FalsifyCancelEventWithDifferentDeviceId function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, FalsifyCancelEventWithDifferentDeviceId001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    AxisEvent axisEventFirst;
    eventManager->FalsifyCancelEventWithDifferentDeviceId(axisEventFirst, true);

    std::vector<AxisAction> actionVec = { AxisAction::NONE, AxisAction::BEGIN, AxisAction::UPDATE, AxisAction::END,
        AxisAction::CANCEL };
    const int nodeId = 10004;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;
    ASSERT_NE(frameNode, nullptr);
    for (auto i = 0; i < actionVec.size(); ++i) {
        AxisEvent axisEvent;
        axisEvent.sourceType = SourceType::TOUCH;
        axisEvent.action = actionVec[i];
        eventManager->TouchTest(axisEvent, frameNode, touchRestrict);
    }

    eventManager->FalsifyCancelEventWithDifferentDeviceId(axisEventFirst, true);
    auto result = eventManager->axisTestResultsMap_.find(axisEventFirst.id);
    EXPECT_EQ(result, eventManager->axisTestResultsMap_.end());
}

struct AxisEventTestCase {
    int32_t eventId;
    int32_t deviceId;
    AxisAction action;
    bool result;
};

/**
 *
 * @tc.name: HandleAxisEventWithDifferentDeviceId001
 * @tc.desc: Test HandleAxisEventWithDifferentDeviceId function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, HandleAxisEventWithDifferentDeviceId001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    const int nodeId = 10086;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    std::vector<AxisEventTestCase> testCases = { { 0, 0, AxisAction::BEGIN, false }, { 0, 1, AxisAction::BEGIN, false },
        { 0, 1, AxisAction::UPDATE, false }, { 0, 0, AxisAction::UPDATE, true }, { 1, 0, AxisAction::BEGIN, false },
        { 1, 1, AxisAction::UPDATE, true }, { 0, 1, AxisAction::END, false }, { 0, 1, AxisAction::CANCEL, true },
        { 1, 0, AxisAction::CANCEL, false }, { 1, 0, AxisAction::CANCEL, true } };
    for (auto& testCase : testCases) {
        AxisEvent axisEvent;
        axisEvent.id = testCase.eventId;
        axisEvent.deviceId = testCase.deviceId;
        axisEvent.action = testCase.action;
        EXPECT_EQ(eventManager->HandleAxisEventWithDifferentDeviceId(axisEvent.CreateScaleEvent(0), frameNode),
            testCase.result);
    }
}

/**
 * @tc.name: InitCoastingAxisEventGenerator001
 * @tc.desc: Test InitCoastingAxisEventGenerator function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, InitCoastingAxisEventGenerator001, TestSize.Level1)
{
    /**
     * @tc.step1: Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    eventManager->InitCoastingAxisEventGenerator();
    ASSERT_NE(eventManager->coastingAxisEventGenerator_, nullptr);
    ASSERT_NE(eventManager->coastingAxisEventGenerator_->axisToTouchConverter_, nullptr);
    AxisEvent axisEvent;
    axisEvent.action = AxisAction::BEGIN;
    auto touchEvent = eventManager->coastingAxisEventGenerator_->axisToTouchConverter_(axisEvent);
    EXPECT_EQ(touchEvent.type, TouchType::DOWN);

    eventManager->coastingAxisEventGenerator_ = nullptr;
    eventManager->InitCoastingAxisEventGenerator();
    ASSERT_NE(eventManager->coastingAxisEventGenerator_, nullptr);
}

/**
 * @tc.name: NotifyAxisEvent001
 * @tc.desc: Test NotifyAxisEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, NotifyAxisEvent001, TestSize.Level1)
{
    /**
     * @tc.step1: Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    ASSERT_NE(eventManager->coastingAxisEventGenerator_, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 0, nullptr);
    ASSERT_NE(frameNode, nullptr);
    AxisEvent axisEvent;
    axisEvent.action = AxisAction::UPDATE;
    axisEvent.sourceType = SourceType::MOUSE;
    axisEvent.sourceTool = SourceTool::TOUCHPAD;
    axisEvent.verticalAxis = 30.0;
    axisEvent.horizontalAxis = 40.0;
    eventManager->NotifyAxisEvent(axisEvent, frameNode);
    EXPECT_EQ(eventManager->coastingAxisEventGenerator_->velocityTracker_.GetMainAxisPos(), 50);
}

/**
 * @tc.name: EventManagerTest100
 * @tc.desc: Test HandleGlobalEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    ASSERT_NE(eventManager->coastingAxisEventGenerator_, nullptr);
    eventManager->coastingAxisEventGenerator_->animationHandler_->phase_ = CoastingAxisPhase::BEGIN;

    /**
     * @tc.steps: step2. Create FrameNode and Call TouchTest to add touchTestResults_[touchPoint.id].
     * @tc.expected: touchTestResults_ has the touchPoint.id of instance.
     */
    TouchEvent touchPoint;
    touchPoint.id = 1000;
    touchPoint.type = TouchType::UP;

    const int nodeId = 10003;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;
    Offset offset;

    eventManager->TouchTest(touchPoint, frameNode, touchRestrict, offset, 0, true);
    EXPECT_EQ(eventManager->coastingAxisEventGenerator_->touchId_, -1);

    MouseEvent event;
    event.action = MouseAction::PRESS;
    event.button = MouseButton::RIGHT_BUTTON;
    eventManager->MouseTest(event, frameNode, touchRestrict);
    EXPECT_EQ(eventManager->coastingAxisEventGenerator_->touchId_, -1);

    touchPoint.type = TouchType::DOWN;
    eventManager->coastingAxisEventGenerator_ = nullptr;
    eventManager->TouchTest(touchPoint, frameNode, touchRestrict, offset, 0, true);
    EXPECT_EQ(eventManager->touchTestResults_.size(), 1);

    event.button = MouseButton::LEFT_BUTTON;
    eventManager->MouseTest(event, frameNode, touchRestrict);
    EXPECT_EQ(eventManager->touchTestResults_.size(), 1);
}

/**
 * @tc.name: AddDumpTouchInfo001
 * @tc.desc: Test AddDumpTouchInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, AddDumpTouchInfo001, TestSize.Level1)
{
    /**
     * @tc.step1: Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    TouchEvent touchEvent;
    TimeStamp timeStamp;
    NG::EventTouchInfoRecord& eventTouchInfoRecord = eventManager->GetEventTouchInfoRecord();
    eventManager->AddDumpTouchInfo(touchEvent);
    EXPECT_EQ(eventTouchInfoRecord.isUseDumpTouchInfo_, false);
    eventManager->SetIsUseDumpTouchInfo(true);
    eventManager->AddDumpTouchInfo(touchEvent);
    EXPECT_EQ(eventTouchInfoRecord.isUseDumpTouchInfo_, true);
    TouchEvent touchEventHistory;
    touchEventHistory.history.push_back(touchEvent);
    touchEventHistory.history.push_back(touchEvent);
    touchEventHistory.history.push_back(touchEvent);
    eventManager->AddDumpTouchInfo(touchEventHistory);
    EXPECT_EQ(eventTouchInfoRecord.isUseDumpTouchInfo_, true);
    for (int i = 0; i < MAX_HISTORY_TOUCH_INFO_SIZE; i++) {
        eventTouchInfoRecord.AddTouchPoint(touchEvent, timeStamp);
    }
    eventTouchInfoRecord.dequeMaxCnt_ = 2;
    eventManager->SetIsUseDumpTouchInfo(true);
    eventManager->AddDumpTouchInfo(touchEvent);
    EXPECT_EQ(eventTouchInfoRecord.isUseDumpTouchInfo_, false);
}

/**
 * @tc.name: AddDumpTouchInfo002
 * @tc.desc: Test AddDumpTouchInfo when touchTimingCallback is null.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, AddDumpTouchInfo002, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.isFalsified = false;
    touchEvent.sensorTime = std::chrono::high_resolution_clock::now();
    touchEvent.processTime = std::chrono::high_resolution_clock::now();

    eventManager->UnregisterTouchTimingCallback();
    EXPECT_EQ(eventManager->touchTimingCallback_, nullptr);

    eventManager->AddDumpTouchInfo(touchEvent);
    EXPECT_EQ(eventManager->touchTimingCallback_, nullptr);
}

/**
 * @tc.name: AddDumpTouchInfo003
 * @tc.desc: Test AddDumpTouchInfo when touchTimingCallback is set but event is falsified.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, AddDumpTouchInfo003, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    bool callbackExecuted = false;
    uint64_t receivedSensorTime = 0;
    uint64_t receivedReceiveTime = 0;
    uint64_t receivedDispatchTime = 0;
    int32_t receivedEventType = 0;

    auto callback = [&](uint64_t sensorTime, uint64_t receiveTime, uint64_t dispatchTime, int32_t eventType) {
        callbackExecuted = true;
        receivedSensorTime = sensorTime;
        receivedReceiveTime = receiveTime;
        receivedDispatchTime = dispatchTime;
        receivedEventType = eventType;
    };

    eventManager->RegisterTouchTimingCallback(std::move(callback));
    EXPECT_NE(eventManager->touchTimingCallback_, nullptr);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.isFalsified = true;
    touchEvent.sensorTime = std::chrono::high_resolution_clock::now();
    touchEvent.processTime = std::chrono::high_resolution_clock::now();

    eventManager->AddDumpTouchInfo(touchEvent);

    EXPECT_FALSE(callbackExecuted);
    EXPECT_EQ(receivedSensorTime, 0);
    EXPECT_EQ(receivedReceiveTime, 0);
    EXPECT_EQ(receivedDispatchTime, 0);
    EXPECT_EQ(receivedEventType, 0);
}

/**
 * @tc.name: AddDumpTouchInfo004
 * @tc.desc: Test AddDumpTouchInfo when touchTimingCallback is set and event is not falsified.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, AddDumpTouchInfo004, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    bool callbackExecuted = false;
    uint64_t receivedSensorTime = 0;
    uint64_t receivedReceiveTime = 0;
    uint64_t receivedDispatchTime = 0;
    int32_t receivedEventType = -1;

    auto callback = [&](uint64_t sensorTime, uint64_t receiveTime, uint64_t dispatchTime, int32_t eventType) {
        callbackExecuted = true;
        receivedSensorTime = sensorTime;
        receivedReceiveTime = receiveTime;
        receivedDispatchTime = dispatchTime;
        receivedEventType = eventType;
    };

    eventManager->RegisterTouchTimingCallback(std::move(callback));
    EXPECT_NE(eventManager->touchTimingCallback_, nullptr);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.isFalsified = false;
    touchEvent.sourceTool = SourceTool::FINGER;
    auto testTime = std::chrono::high_resolution_clock::now();
    touchEvent.sensorTime = testTime;
    touchEvent.processTime = testTime;

    eventManager->AddDumpTouchInfo(touchEvent);

    EXPECT_TRUE(callbackExecuted);
    EXPECT_EQ(receivedSensorTime, static_cast<uint64_t>(testTime.time_since_epoch().count()));
    EXPECT_EQ(receivedReceiveTime, static_cast<uint64_t>(testTime.time_since_epoch().count()));
    EXPECT_GT(receivedDispatchTime, 0);
    EXPECT_EQ(receivedEventType, static_cast<int32_t>(TouchType::DOWN));
}

/**
 * @tc.name: AddDumpTouchInfo005
 * @tc.desc: Test AddDumpTouchInfo when touchTimingCallback is set and event has history points.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, AddDumpTouchInfo005, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    
    int callbackCount = 0;
    std::vector<uint64_t> receivedSensorTimes;
    std::vector<uint64_t> receivedReceiveTimes;
    std::vector<uint64_t> receivedDispatchTimes;
    std::vector<int32_t> receivedEventTypes;
    
    auto callback = [&](uint64_t sensorTime, uint64_t receiveTime, uint64_t dispatchTime, int32_t eventType) {
        callbackCount++;
        receivedSensorTimes.push_back(sensorTime);
        receivedReceiveTimes.push_back(receiveTime);
        receivedDispatchTimes.push_back(dispatchTime);
        receivedEventTypes.push_back(eventType);
    };
    
    eventManager->RegisterTouchTimingCallback(std::move(callback));
    EXPECT_NE(eventManager->touchTimingCallback_, nullptr);
    
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.isFalsified = false;
    touchEvent.sourceTool = SourceTool::FINGER;
    auto testTime1 = std::chrono::high_resolution_clock::now();
    touchEvent.sensorTime = testTime1;
    touchEvent.processTime = testTime1;
    
    TouchEvent historyPoint1;
    historyPoint1.type = TouchType::MOVE;
    historyPoint1.sourceTool = SourceTool::FINGER;
    auto testTime2 = std::chrono::high_resolution_clock::now();
    historyPoint1.sensorTime = testTime2;
    historyPoint1.processTime = testTime2;
    
    TouchEvent historyPoint2;
    historyPoint2.type = TouchType::UP;
    historyPoint2.sourceTool = SourceTool::FINGER;
    auto testTime3 = std::chrono::high_resolution_clock::now();
    historyPoint2.sensorTime = testTime3;
    historyPoint2.processTime = testTime3;
    
    touchEvent.history.push_back(historyPoint1);
    touchEvent.history.push_back(historyPoint2);
    
    eventManager->AddDumpTouchInfo(touchEvent);
    
    EXPECT_EQ(callbackCount, 2);
    EXPECT_EQ(receivedEventTypes.size(), 2);
    EXPECT_EQ(receivedEventTypes[0], static_cast<int32_t>(TouchType::MOVE));
    EXPECT_EQ(receivedEventTypes[1], static_cast<int32_t>(TouchType::UP));
    EXPECT_EQ(receivedSensorTimes[0], static_cast<uint64_t>(testTime2.time_since_epoch().count()));
    EXPECT_EQ(receivedSensorTimes[1], static_cast<uint64_t>(testTime3.time_since_epoch().count()));
    EXPECT_EQ(receivedReceiveTimes[0], static_cast<uint64_t>(testTime2.time_since_epoch().count()));
    EXPECT_EQ(receivedReceiveTimes[1], static_cast<uint64_t>(testTime3.time_since_epoch().count()));
    EXPECT_GT(receivedDispatchTimes[0], 0);
    EXPECT_GT(receivedDispatchTimes[1], 0);
}

/**
 * @tc.name: AddDumpTouchInfo006
 * @tc.desc: Test AddDumpTouchInfo when sourceTool is not FINGER (event.sourceTool == SourceTool::PEN).
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, AddDumpTouchInfo006, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    bool callbackExecuted = false;
    uint64_t receivedSensorTime = 0;
    uint64_t receivedReceiveTime = 0;
    uint64_t receivedDispatchTime = 0;
    int32_t receivedEventType = 0;

    auto callback = [&](uint64_t sensorTime, uint64_t receiveTime, uint64_t dispatchTime, int32_t eventType) {
        callbackExecuted = true;
        receivedSensorTime = sensorTime;
        receivedReceiveTime = receiveTime;
        receivedDispatchTime = dispatchTime;
        receivedEventType = eventType;
    };

    eventManager->RegisterTouchTimingCallback(std::move(callback));
    EXPECT_NE(eventManager->touchTimingCallback_, nullptr);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.isFalsified = false;
    touchEvent.sourceTool = SourceTool::PEN;
    auto testTime = std::chrono::high_resolution_clock::now();
    touchEvent.sensorTime = testTime;
    touchEvent.processTime = testTime;

    eventManager->AddDumpTouchInfo(touchEvent);

    EXPECT_FALSE(callbackExecuted);
    EXPECT_EQ(receivedSensorTime, 0);
    EXPECT_EQ(receivedReceiveTime, 0);
    EXPECT_EQ(receivedDispatchTime, 0);
    EXPECT_EQ(receivedEventType, 0);
}

/**
 * @tc.name: AddDumpTouchInfo007
 * @tc.desc: Test AddDumpTouchInfo when sourceTool is MOUSE (should not execute callback).
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, AddDumpTouchInfo007, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    bool callbackExecuted = false;

    auto callback = [&](uint64_t sensorTime, uint64_t receiveTime, uint64_t dispatchTime, int32_t eventType) {
        callbackExecuted = true;
    };

    eventManager->RegisterTouchTimingCallback(std::move(callback));
    EXPECT_NE(eventManager->touchTimingCallback_, nullptr);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.isFalsified = false;
    touchEvent.sourceTool = SourceTool::MOUSE;
    auto testTime = std::chrono::high_resolution_clock::now();
    touchEvent.sensorTime = testTime;
    touchEvent.processTime = testTime;

    eventManager->AddDumpTouchInfo(touchEvent);

    EXPECT_FALSE(callbackExecuted);
}

/**
 * @tc.name: DumpTouchInfo001
 * @tc.desc: Test DumpTouchInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, DumpTouchInfo001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));

    bool hasJson = false;
    std::string param0 = "-touchmonitor";
    std::string param1 = "-b";
    std::string param2 = "-d";
    std::string param3 = "-c";
    std::string param4 = "-e";
    std::string param5 = "-f";
    TouchEvent touchEvent;
    touchEvent.touchEventId = 0;
    touchEvent.processTime = std::chrono::high_resolution_clock::now();
    touchEvent.time = std::chrono::high_resolution_clock::now();
    NG::EventTouchInfoRecord& eventTouchInfoRecord = eventManager->GetEventTouchInfoRecord();
    TimeStamp timeStamp = std::chrono::high_resolution_clock::now();
    eventTouchInfoRecord.AddTouchPoint(touchEvent, timeStamp);

    std::vector<std::string> params0 = { param0, param4 };
    eventManager->DumpTouchInfo(params0, hasJson);
    EXPECT_EQ(eventTouchInfoRecord.touchHistory_.size(), 0);
    std::vector<std::string> params1 = { param0, param1 };
    eventManager->DumpTouchInfo(params1, hasJson);
    EXPECT_TRUE(eventTouchInfoRecord.isUseDumpTouchInfo_);
    eventTouchInfoRecord.AddTouchPoint(touchEvent, timeStamp);
    std::vector<std::string> params2 = { param0, param2 };
    eventManager->DumpTouchInfo(params2, hasJson);
    EXPECT_EQ(eventTouchInfoRecord.touchHistory_.size(), 0);
    std::vector<std::string> params3 = { param0, param3 };
    eventManager->DumpTouchInfo(params3, hasJson);
    std::vector<std::string> params4 = { param0 };
    eventManager->DumpTouchInfo(params4, hasJson);
    std::vector<std::string> params5 = { param0, param5 };
    eventManager->DumpTouchInfo(params5, hasJson);
    EXPECT_FALSE(hasJson);

    hasJson = true;
    eventTouchInfoRecord.AddTouchPoint(touchEvent, timeStamp);
    eventManager->DumpTouchInfo(params2, hasJson);
    EXPECT_EQ(eventTouchInfoRecord.touchHistory_.size(), 0);
}

/**
 * @tc.name: GetCurrentReferee001
 * @tc.desc: Test GetCurrentReferee function with isNewReferee=false and key=1 (POST_ONCE).
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, GetCurrentReferee001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    constexpr bool IS_NEW_REFEREE = false;
    constexpr int32_t EVENT_HANDLE_ID = 100001;
 
    auto referee = eventManager->GetCurrentReferee(IS_NEW_REFEREE, EVENT_HANDLE_ID);
    ASSERT_NE(referee, nullptr);
}
 
/**
 * @tc.name: UpdateDragInfo001
 * @tc.desc: Test UpdateDragInfo when type is PULL_MOVE.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, UpdateDragInfo001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    TouchEvent touchEvent;
    touchEvent.type = TouchType::PULL_MOVE;
    touchEvent.pullType = TouchType::PULL_MOVE;
 
    eventManager->UpdateDragInfo(touchEvent);
    EXPECT_EQ(touchEvent.type, TouchType::CANCEL);
    EXPECT_EQ(touchEvent.pullType, TouchType::PULL_MOVE);
}
 
/**
 * @tc.name: UpdateDragInfo002
 * @tc.desc: Test UpdateDragInfo when type is PULL_IN_WINDOW.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, UpdateDragInfo002, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    TouchEvent touchEvent;
    touchEvent.type = TouchType::PULL_IN_WINDOW;
    eventManager->UpdateDragInfo(touchEvent);
    EXPECT_EQ(touchEvent.type, TouchType::CANCEL);
}
 
/**
 * @tc.name: UpdateDragInfo003
 * @tc.desc: Test UpdateDragInfo when type is PULL_OUT_WINDOW.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, UpdateDragInfo003, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    TouchEvent touchEvent;
    touchEvent.type = TouchType::PULL_OUT_WINDOW;
    eventManager->UpdateDragInfo(touchEvent);
    EXPECT_EQ(touchEvent.type, TouchType::CANCEL);
}
 
/**
 * @tc.name: UpdateDragInfo004
 * @tc.desc: Test UpdateDragInfo when type is PULL_UP.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, UpdateDragInfo004, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    TouchEvent touchEvent;
    touchEvent.type = TouchType::PULL_UP;
    eventManager->UpdateDragInfo(touchEvent);
    EXPECT_EQ(touchEvent.type, TouchType::UP);
}
 
/**
 * @tc.name: UpdateDragInfo005
 * @tc.desc: Test UpdateDragInfo when type is UP.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, UpdateDragInfo005, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    TouchEvent touchEvent;
    touchEvent.type = TouchType::UP;
    eventManager->UpdateDragInfo(touchEvent);
    EXPECT_EQ(touchEvent.type, TouchType::UP);
}
 
/**
 * @tc.name: FalsifyCancelEventAndDispatch001
 * @tc.desc: Test FalsifyCancelEventAndDispatch with non-empty downFingerIds.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, FalsifyCancelEventAndDispatch001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    eventManager->downFingerIds_[0] = 0;
    eventManager->downFingerIds_[1] = 1;
 
    TouchEvent touchEvent;
    touchEvent.id = 0;
    touchEvent.originalId = 0;
    eventManager->lastTouchEvent_ = touchEvent;
    eventManager->FalsifyCancelEventAndDispatch(touchEvent, true);
}
 
/**
 * @tc.name: SetResponseLinkRecognizers001
 * @tc.desc: Test SetResponseLinkRecognizers with non-post event.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, SetResponseLinkRecognizers001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panRecognizer, nullptr);
 
    TouchTestResult result;
    result.emplace_back(panRecognizer);
 
    ResponseLinkResult responseLinkResult;
    bool isPostEvent = false;
    eventManager->SetResponseLinkRecognizers(result, responseLinkResult, isPostEvent);
}
 
/**
 * @tc.name: SetResponseLinkRecognizers002
 * @tc.desc: Test SetResponseLinkRecognizers with post event.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, SetResponseLinkRecognizers002, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    auto sequenceRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(std::vector<RefPtr<NG::NGGestureRecognizer>>());
    ASSERT_NE(sequenceRecognizer, nullptr);
 
    TouchTestResult result;
    result.emplace_back(sequenceRecognizer);
 
    ResponseLinkResult responseLinkResult;
    bool isPostEvent = true;
    eventManager->SetResponseLinkRecognizers(result, responseLinkResult, isPostEvent);
}
 
/**
 * @tc.name: CleanRefereeBeforeTouchTest001
 * @tc.desc: Test CleanRefereeBeforeTouchTest with eventHandleId=0.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, CleanRefereeBeforeTouchTest001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    TouchEvent touchEvent;
    touchEvent.id = 0;
    touchEvent.eventHandleId = 0;
    touchEvent.sourceType = SourceType::TOUCH;
 
    constexpr bool NEED_APPEND = false;
    eventManager->CleanRefereeBeforeTouchTest(touchEvent, NEED_APPEND);
}

/**
 * @tc.name: CleanRefereeBeforeTouchTest002
 * @tc.desc: Test CleanRefereeBeforeTouchTest when CheckEventTypeChange returns true.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, CleanRefereeBeforeTouchTest002, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    TouchEvent touchEvent;
    touchEvent.id = 0;
    touchEvent.eventHandleId = 0;
    touchEvent.sourceType = SourceType::MOUSE;
 
    auto refereeNG = eventManager->refereeNG_;
    if (refereeNG) {
        refereeNG->CheckEventTypeChange(SourceType::TOUCH);
    }
 
    constexpr bool NEED_APPEND = false;
    eventManager->CleanRefereeBeforeTouchTest(touchEvent, NEED_APPEND);
}
 
/**
 * @tc.name: FlushTouchEventsBegin001
 * @tc.desc: Test FlushTouchEventsBegin with events in touchTestResults.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, FlushTouchEventsBegin001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panRecognizer, nullptr);
 
    TouchTestResult hitTestResult;
    hitTestResult.emplace_back(panRecognizer);
    eventManager->touchTestResults_[0] = hitTestResult;
 
    std::list<TouchEvent> touchEvents;
    TouchEvent event;
    event.id = 0;
    touchEvents.push_back(event);
    eventManager->FlushTouchEventsBegin(touchEvents);
}
 
/**
 * @tc.name: FlushTouchEventsEnd001
 * @tc.desc: Test FlushTouchEventsEnd with resampled events.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, FlushTouchEventsEnd001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panRecognizer, nullptr);
 
    TouchTestResult hitTestResult;
    hitTestResult.emplace_back(panRecognizer);
    eventManager->touchTestResults_[0] = hitTestResult;
 
    std::list<TouchEvent> touchEvents;
    TouchEvent event;
    event.id = 0;
    TouchEvent historyEvent;
    historyEvent.id = 0;
    event.history.push_back(historyEvent);
    touchEvents.push_back(event);
    eventManager->FlushTouchEventsEnd(touchEvents);
}
 
/**
 * @tc.name: DispatchTouchEventToTouchTestResult001
 * @tc.desc: Test DispatchTouchEventToTouchTestResult with passThrough=true.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, DispatchTouchEventToTouchTestResult001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panRecognizer, nullptr);
 
    TouchTestResult touchTestResult;
    touchTestResult.emplace_back(panRecognizer);
 
    TouchEvent touchEvent;
    touchEvent.passThrough = true;
 
    constexpr bool SEND_ON_TOUCH = true;
    eventManager->DispatchTouchEventToTouchTestResult(touchEvent, touchTestResult, SEND_ON_TOUCH);
}
 
/**
 * @tc.name: LogTouchTestRecognizerStates001
 * @tc.desc: Test LogTouchTestRecognizerStates with empty eventTree.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, LogTouchTestRecognizerStates001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    eventManager->eventTree_.eventTreeList.clear();
    eventManager->LogTouchTestRecognizerStates(0);
}
 
/**
 * @tc.name: CleanResults001
 * @tc.desc: Test ClearResults function.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, CleanResults001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
 
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panRecognizer, nullptr);
 
    eventManager->touchTestResults_[0].emplace_back(panRecognizer);
    eventManager->postEventTouchTestResults_[0].emplace_back(panRecognizer);
    eventManager->axisTouchTestResults_[0].emplace_back(panRecognizer);
    eventManager->ClearResults();
    EXPECT_TRUE(eventManager->touchTestResults_.empty());
    EXPECT_TRUE(eventManager->postEventTouchTestResults_.empty());
    EXPECT_TRUE(eventManager->axisTouchTestResults_.empty());
}
} // namespace OHOS::Ace::NG