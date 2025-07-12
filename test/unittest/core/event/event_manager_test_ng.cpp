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
void EventManagerTestNg::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = nullptr;
    MOCK_TASK_EXECUTOR = AceType::MakeRefPtr<MockTaskExecutor>();
}

void EventManagerTestNg::TearDownTestSuite()
{
    MockContainer::TearDown();
}

/**
 * @tc.name: EventManagerTest001
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    KeyEvent event;

    /* LAlt + F4 */
    event.code = KeyCode::KEY_F4;
    event.pressedCodes = {KeyCode::KEY_ALT_LEFT};
    bool isSystemKey = eventManager->IsSystemKeyboardShortcut(event);
    EXPECT_FALSE(isSystemKey);

    /* RAlt + F4 */
    event.code = KeyCode::KEY_F4;
    event.pressedCodes = {KeyCode::KEY_ALT_RIGHT};
    isSystemKey = eventManager->IsSystemKeyboardShortcut(event);
    EXPECT_FALSE(isSystemKey);

    /* Ctrl + A */
    event.code = KeyCode::KEY_A;
    event.pressedCodes = {KeyCode::KEY_CTRL_LEFT};
    isSystemKey = eventManager->IsSystemKeyboardShortcut(event);
    EXPECT_FALSE(isSystemKey);
}

/**
 * @tc.name: EventManagerTest003
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest003, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();

    auto frameNodeCtrl = FrameNode::GetOrCreateFrameNode(CTRL, NUM_CTRL_VALUE, nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrl));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrl));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrl));
    auto frameNodeShift = FrameNode::GetOrCreateFrameNode(SHIFT, NUM_SHIFT_VALUE, nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeShift));
    auto frameNodeAlt = FrameNode::GetOrCreateFrameNode(ALT, NUM_ALT_VALUE, nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeAlt));
    auto frameNodeCtrlShift = FrameNode::GetOrCreateFrameNode(CTRLSHIFT, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE), nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrlShift));

    auto eventHubCtrl = frameNodeCtrl->GetOrCreateEventHub<NG::EventHub>();
    auto eventHubShift = frameNodeShift->GetOrCreateEventHub<NG::EventHub>();
    auto eventHubAlt = frameNodeAlt->GetOrCreateEventHub<NG::EventHub>();
    auto eventHubCtrlShift = frameNodeCtrlShift->GetOrCreateEventHub<NG::EventHub>();

    eventHubCtrl->SetKeyboardShortcut(CHARACTER_C, NUM_CTRL_VALUE, []() {});
    eventHubShift->SetKeyboardShortcut(CHARACTER_A, NUM_SHIFT_VALUE, []() {});
    eventHubAlt->SetKeyboardShortcut(CHARACTER_V, NUM_ALT_VALUE, []() {});
    eventHubCtrlShift->SetKeyboardShortcut(CHARACTER_Z, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE), []() {});

    bool isShortcutNodeCtrlC = eventManager->IsSameKeyboardShortcutNode(CHARACTER_C, NUM_CTRL_VALUE);
    EXPECT_TRUE(isShortcutNodeCtrlC);
    bool isShortcutNodeCtrlEIGHT = eventManager->IsSameKeyboardShortcutNode(CHARACTER_EIGHT, NUM_CTRL_VALUE);
    EXPECT_FALSE(isShortcutNodeCtrlEIGHT);
    bool isShortcutNodeShiftC = eventManager->IsSameKeyboardShortcutNode(CHARACTER_C, NUM_SHIFT_VALUE);
    EXPECT_FALSE(isShortcutNodeShiftC);
    bool isShortcutNodeShiftEight = eventManager->IsSameKeyboardShortcutNode(CHARACTER_EIGHT, NUM_SHIFT_VALUE);
    EXPECT_FALSE(isShortcutNodeShiftEight);
    bool isShortcutNodeAltC = eventManager->IsSameKeyboardShortcutNode(CHARACTER_C, NUM_ALT_VALUE);
    EXPECT_FALSE(isShortcutNodeAltC);
    bool isShortcutNodeAltEight = eventManager->IsSameKeyboardShortcutNode(CHARACTER_EIGHT, NUM_ALT_VALUE);
    EXPECT_FALSE(isShortcutNodeAltEight);
    bool isShortcutComposeC = eventManager->IsSameKeyboardShortcutNode(CHARACTER_C, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE));
    EXPECT_FALSE(isShortcutComposeC);
    bool isShortcutComposeEight =
        eventManager->IsSameKeyboardShortcutNode(CHARACTER_EIGHT, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE));
    EXPECT_FALSE(isShortcutComposeEight);
}

/**
 * @tc.name: EventManagerTest004
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest004, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto frameNodeone = FrameNode::GetOrCreateFrameNode(CTRL, NODEID, nullptr);

    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeone));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeone));
    ASSERT_NE(frameNodeone, nullptr);

    auto frameNodetwo = FrameNode::GetOrCreateFrameNode(SHIFT, NODEID, nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodetwo));
    ASSERT_NE(frameNodetwo, nullptr);
}

/**
 * @tc.name: EventManagerTest005
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest005, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto frameNodeone = FrameNode::GetOrCreateFrameNode(CTRL, NODEID, nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeone));

    eventManager->DelKeyboardShortcutNode(frameNodeone->GetId());
    ASSERT_NE(frameNodeone, nullptr);

    auto frameNodetwo = FrameNode::GetOrCreateFrameNode(SHIFT, NODEID, nullptr);
    eventManager->DelKeyboardShortcutNode(frameNodetwo->GetId());
    ASSERT_NE(frameNodetwo, nullptr);
}

/**
 * @tc.name: EventManagerTest006
 * @tc.desc: Test GetKeyboardShortcutKeys
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call GetKeyboardShortcutKeys with keys.size() > KEYS_MAX_VALUE.
     * @tc.expected: Value of ret is 0.
     */
    std::vector<ModifierKey> keys { ModifierKey::ALT, ModifierKey::CTRL, ModifierKey::SHIFT, ModifierKey::SHIFT };
    auto ret = eventManager->GetKeyboardShortcutKeys(keys);
    EXPECT_EQ(ret, 0);

    /**
     * @tc.steps: step3. Call GetKeyboardShortcutKeys with keys CTRL SHIFT ALT.
     * @tc.expected: Value of ret is CTRL | SHIFT | ALT.
     */
    keys.pop_back();
    ret = eventManager->GetKeyboardShortcutKeys(keys);
    uint8_t target = static_cast<uint8_t>(CtrlKeysBit::CTRL) | static_cast<uint8_t>(CtrlKeysBit::SHIFT) |
                     static_cast<uint8_t>(CtrlKeysBit::ALT);
    EXPECT_EQ(ret, target);

    /**
     * @tc.steps: step4. Call GetKeyboardShortcutKeys with keys CTRL CTRL.
     * @tc.expected: Value of ret is 0.
     */
    keys = std::vector<ModifierKey>({ ModifierKey::CTRL, ModifierKey::CTRL });
    ret = eventManager->GetKeyboardShortcutKeys(keys);
    EXPECT_EQ(ret, 0);

    /**
     * @tc.steps: step5. Call GetKeyboardShortcutKeys with keys SHIFT SHIFT.
     * @tc.expected: Value of ret is 0.
     */
    keys = std::vector<ModifierKey>({ ModifierKey::SHIFT, ModifierKey::SHIFT });
    ret = eventManager->GetKeyboardShortcutKeys(keys);
    EXPECT_EQ(ret, 0);

    /**
     * @tc.steps: step6. Call GetKeyboardShortcutKeys with keys SHIFT SHIFT.
     * @tc.expected: Value of ret is 0.
     */
    keys = std::vector<ModifierKey>({ ModifierKey::ALT, ModifierKey::ALT });
    ret = eventManager->GetKeyboardShortcutKeys(keys);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: EventManagerTest009
 * @tc.desc: Test ClearResults
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Add KeyboardShortcutNode
     * @tc.expected: keyboardShortcutNode_.size() > 0.
     */
    auto frameNodeShift = FrameNode::GetOrCreateFrameNode(SHIFT, NUM_SHIFT_VALUE, nullptr);
    frameNodeShift->GetOrCreateEventHub<EventHub>()->SetKeyboardShortcut(
        SHORT_CUT_VALUE_A, static_cast<int>(CtrlKeysBit::SHIFT), []() {});
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeShift));
    EXPECT_GT(eventManager->keyboardShortcutNode_.size(), 0);
}

/**
 * @tc.name: EventManagerTest010
 * @tc.desc: Test TouchTest with FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Create FrameNode and Call TouchTest with needAppend false
     * @tc.expected: touchTestResults_ has the touchPoint.id of instance
     */
    TouchEvent touchPoint;
    touchPoint.id = 0;
    touchPoint.type = TouchType::DOWN;

    const int nodeId = 10001;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;
    Offset offset;
    EXPECT_EQ(eventManager->touchTestResults_.count(touchPoint.id), 0);
    eventManager->TouchTest(touchPoint, frameNode, touchRestrict, offset, 0, false);
    EXPECT_GT(eventManager->touchTestResults_.count(touchPoint.id), 0);

    /**
     * @tc.steps: step2. Create FrameNode and Call TouchTest with needAppend true
     * @tc.expected: touchTestResults_ has the touchPoint.id of instance
     */
    eventManager->touchTestResults_.erase(touchPoint.id);
    EXPECT_EQ(eventManager->touchTestResults_.count(touchPoint.id), 0);
    eventManager->TouchTest(touchPoint, frameNode, touchRestrict, offset, 0, true);
    EXPECT_GT(eventManager->touchTestResults_.count(touchPoint.id), 0);

    /**
     * @tc.steps: step3. Create GestureScope.
     * @tc.expected: GestureScope is not null.
     */
    size_t touchId = 100;
    RefPtr<GestureScope> scope = AceType::MakeRefPtr<GestureScope>(touchId);
    ASSERT_NE(scope, nullptr);
    eventManager->refereeNG_->gestureScopes_.insert(std::make_pair(touchId, scope));
    EXPECT_TRUE(eventManager->refereeNG_->QueryAllDone(touchId));
}

/**
 * @tc.name: EventManagerTest011
 * @tc.desc: Test TouchTest with FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest011, TestSize.Level1)
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
    AxisEvent axisEvent;
    axisEvent.sourceType = SourceType::TOUCH;

    const int nodeId = 10002;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;

    EXPECT_EQ(eventManager->axisTouchTestResults_.count(axisEvent.id), 0);
    eventManager->TouchTest(axisEvent, frameNode, touchRestrict);
    EXPECT_GT(eventManager->axisTouchTestResults_.count(axisEvent.id), 0);
}

/**
 * @tc.name: EventManagerTest012
 * @tc.desc: Test HandleGlobalEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Create FrameNode and Call TouchTest to add touchTestResults_[touchPoint.id]
     * @tc.expected: touchTestResults_ has the touchPoint.id of instance
     */
    TouchEvent touchPoint;
    touchPoint.type = TouchType::DOWN;

    const int nodeId = 10003;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;
    Offset offset;

    eventManager->TouchTest(touchPoint, frameNode, touchRestrict, offset, 0, true);
    EXPECT_GT(eventManager->touchTestResults_.count(touchPoint.id), 0);

    /**
     * @tc.steps: step3. Create FrameNode and Call TouchTest to add touchTestResults_[touchPoint.id]
     * @tc.expected: selectOverlayManager->touchTestResults_ is empty for do not have specific event
     */
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(frameNode);
    NG::OffsetF rootOffset;
    eventManager->HandleGlobalEventNG(touchPoint, selectOverlayManager, rootOffset);
    EXPECT_EQ(selectOverlayManager->touchTestResults_.size(), 0);
}

/**
 * @tc.name: EventManagerTest013
 * @tc.desc: Test HandleOutOfRectCallback
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest013, TestSize.Level1)
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
    std::vector<RectCallback> rectCallbackList { RectCallback(rectGetCallback1, touchCallback, mouseCallback),
        RectCallback(rectGetCallback2, touchCallback, mouseCallback) };

    /**
     * @tc.steps: step3. Call HandleOutOfRectCallback with SourceType::TOUCH
     * @tc.expected: rectCallbackList.size() is 1
     */
    eventManager->HandleOutOfRectCallback(point, rectCallbackList);
    EXPECT_EQ(rectCallbackList.size(), 1);

    /**
     * @tc.steps: step4. Call HandleOutOfRectCallback with SourceType::MOUSE
     * @tc.expected: rectCallbackList.size() is 0
     */
    point.SetSourceType(SourceType::MOUSE);
    rectCallbackList = vector<RectCallback>({ RectCallback(rectGetCallback1, touchCallback, mouseCallback) });
    eventManager->HandleOutOfRectCallback(point, rectCallbackList);
    EXPECT_TRUE(rectCallbackList.empty());
}

/**
 * @tc.name: EventManagerTest014
 * @tc.desc: Test DispatchTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Create TouchEvent and Call DispatchTouchEvent
     * @tc.expected: retFlag is false
     */
    AxisEvent event;
    event.action = AxisAction::BEGIN;

    auto retFlag = eventManager->DispatchTouchEvent(event);
    EXPECT_FALSE(retFlag);

    /**
     * @tc.steps: step3. Create FrameNode and Call TouchTest to add axisTouchTestResults_
     * @tc.expected: touchTestResults_ has the touchPoint.id of instance
     */
    event.action = AxisAction::END;

    const int nodeId = 10004;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;

    eventManager->TouchTest(event, frameNode, touchRestrict);
    EXPECT_GT(eventManager->axisTouchTestResults_.count(event.id), 0);

    /**
     * @tc.steps: step4. Call DispatchTouchEvent
     * @tc.expected: touchTestResults_ has the touchPoint.id of instance
     */
    retFlag = eventManager->DispatchTouchEvent(event);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step5. Create AxisEvent and Call DispatchTouchEvent
     * @tc.expected: retFlag is false
     */
    event.action = AxisAction::BEGIN;
    Container::SetCurrentUsePartialUpdate(true);
    AceForwardCompatibility::isNewPipeline_ = true;
    eventManager->DispatchTouchEvent(event);
    auto container = Container::Current();
    container->useNewPipeline_ = true;
    ASSERT_NE(container, nullptr);
    retFlag = Container::IsCurrentUseNewPipeline();
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: EventManagerTest015
 * @tc.desc: Test DispatchTabIndexEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Create frameNodes
     * @tc.expected: retFlag is false
     */
    const int mainNodeId = 10006;
    auto mainNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, mainNodeId, nullptr);

    /**
     * @tc.steps: step3. Call DispatchTabIndexEventNG
     * @tc.expected: retFlag is false
     */
    KeyEvent event;
    auto retFlag = eventManager->DispatchTabIndexEventNG(event, mainNode);
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: EventManagerTest016
 * @tc.desc: Test DispatchKeyEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Create frameNodes
     * @tc.expected: retFlag is false
     */
    const int focusNodeId = 10007;
    auto focusNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, focusNodeId, nullptr);
    focusNode->GetOrCreateEventHub<ButtonEventHub>();
    focusNode->eventHub_->GetOrCreateFocusHub(FocusType::NODE);
    ASSERT_NE(focusNode->GetFocusHub(), nullptr);

    /**
     * @tc.steps: step3. Call DispatchKeyEventNG
     * @tc.expected: retFlag is false
     */
    KeyEvent event;
    auto retFlag = eventManager->DispatchKeyEventNG(event, focusNode);
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: EventManagerTest017
 * @tc.desc: Test MouseTest (frameNode)
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call MouseTest with MouseAction::WINDOW_LEAVE
     * @tc.expected: currHoverTestResultsMap_[event.id] is empty
     */
    MouseEvent event;
    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    TouchRestrict touchRestrict;

    event.action = MouseAction::WINDOW_LEAVE;
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(V2::LOCATION_BUTTON_ETS_TAG, nodeId);
    eventManager->currHoverTestResultsMap_[event.id].push_back(hoverEventTarget);
    EXPECT_FALSE(eventManager->currHoverTestResultsMap_[event.id].empty());
    eventManager->MouseTest(event, frameNode, touchRestrict);
    EXPECT_TRUE(eventManager->currHoverTestResultsMap_[event.id].empty());

    /**
     * @tc.steps: step3. Call MouseTest with MouseAction::WINDOW_ENTER
     * @tc.expected: lastHoverTestResultsMap_[event.id] is empty
     */
    event.action = MouseAction::WINDOW_ENTER;
    eventManager->lastHoverTestResultsMap_[event.id].push_back(hoverEventTarget);
    EXPECT_FALSE(eventManager->lastHoverTestResultsMap_[event.id].empty());
    eventManager->MouseTest(event, frameNode, touchRestrict);
    EXPECT_TRUE(eventManager->lastHoverTestResultsMap_[event.id].empty());

    /**
     * @tc.steps: step4. Call MouseTest with MouseAction::HOVER
     * @tc.expected: lastHoverTestResultsMap_[event.id] is empty and currHoverTestResultsMap_[event.id] is empty
     */
    event.action = MouseAction::HOVER;
    eventManager->lastHoverTestResultsMap_[event.id].push_back(hoverEventTarget);
    eventManager->MouseTest(event, frameNode, touchRestrict);
    EXPECT_TRUE(eventManager->lastHoverTestResultsMap_[event.id].empty());
    EXPECT_TRUE(eventManager->currHoverTestResultsMap_[event.id].empty());
}

/**
 * @tc.name: EventManagerTest018
 * @tc.desc: Test DispatchMouseEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseEventNG
     * @tc.expected: currHoverTestResultsMap_[event.id] is empty
     */
    MouseEvent event;
    event.action = MouseAction::PRESS;
    event.button = MouseButton::LEFT_BUTTON;
    event.pullAction = MouseAction::MOVE;

    auto mouseEventTarget = AceType::MakeRefPtr<MouseEventTarget>(MOUSE, NODEID);
    eventManager->pressMouseTestResults_.push_back(mouseEventTarget);
    eventManager->currMouseTestResultsMap_[0].push_back(mouseEventTarget);

    auto retFlag = eventManager->DispatchMouseEventNG(event);
    EXPECT_FALSE(retFlag);

    /**
     * @tc.steps: step2. Call DispatchMouseEventNG
     * @tc.expected: currHoverTestResultsMap_[event.id] is empty
     */
    event.action = MouseAction::RELEASE;
    event.button = MouseButton::LEFT_BUTTON;
    event.pullAction = MouseAction::MOVE;
    retFlag = eventManager->DispatchMouseEventNG(event);
    EXPECT_FALSE(retFlag);

    /**
     * @tc.steps: step3. Call DispatchMouseEventNG
     * @tc.expected: currHoverTestResultsMap_[event.id] is empty
     */
    event.action = MouseAction::MOVE;
    event.button = MouseButton::LEFT_BUTTON;
    event.pullAction = MouseAction::PULL_UP;
    retFlag = eventManager->DispatchMouseEventNG(event);
    EXPECT_FALSE(retFlag);

    /**
     * @tc.steps: step4. Call DispatchMouseEventNG
     * @tc.expected: currHoverTestResultsMap_[event.id] not empty
     */
    event.action = MouseAction::MOVE;
    event.button = MouseButton::LEFT_BUTTON;
    event.pullAction = MouseAction::PULL_UP;

    auto mouseTestResult = AceType::MakeRefPtr<MouseEventTarget>(CTRL, NODEID);
    eventManager->currMouseTestResultsMap_[0].push_back(mouseTestResult);

    retFlag = eventManager->DispatchMouseEventNG(event);
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: EventManagerTest019
 * @tc.desc: Test DispatchMouseHoverEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseHoverEventNG with lastHoverTestResults != currHoverTestResults
     * @tc.expected: retFlag is true
     */
    MouseEvent event;
    auto hoverEventTarget = AceType::MakeRefPtr<HoverEventTarget>(MOUSE, NODEID);
    auto hoverEventTarget2 = AceType::MakeRefPtr<HoverEventTarget>(MOUSE_EVENT, NODEID_2);
    auto hoverEventTarget3 = AceType::MakeRefPtr<HoverEventTarget>(MOUSE_EVENT_2, NODEID_3);
    eventManager->lastHoverTestResultsMap_[event.id].push_back(hoverEventTarget);
    eventManager->currHoverTestResultsMap_[event.id].push_back(hoverEventTarget2);
    eventManager->currHoverTestResultsMap_[event.id].push_back(hoverEventTarget3);
    eventManager->currHoverTestResultsMap_[event.id].push_back(hoverEventTarget);
    eventManager->lastHoverDispatchLength_++;

    auto retFlag = eventManager->DispatchMouseHoverEventNG(event);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step2. Call DispatchMouseHoverEventNG with lastHoverTestResults == currHoverTestResults
     * @tc.expected: retFlag is true
     */
    eventManager->lastHoverTestResultsMap_[event.id].clear();
    eventManager->lastHoverTestResultsMap_[event.id].push_back(hoverEventTarget);
    eventManager->currHoverTestResultsMap_[event.id].clear();
    eventManager->currHoverTestResultsMap_[event.id].push_back(hoverEventTarget);

    retFlag = eventManager->DispatchMouseHoverEventNG(event);
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: EventManagerTest020
 * @tc.desc: Test DispatchAxisEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchAxisEventNG with horizontalAxis verticalAxis pinchAxisScale = 0
     * @tc.expected: retFlag is false
     */
    AxisEvent event;
    event.horizontalAxis = 0;
    event.verticalAxis = 0;
    event.pinchAxisScale = 0;
    auto retFlag = eventManager->DispatchAxisEventNG(event);
    EXPECT_FALSE(retFlag);

    /**
     * @tc.steps: step3. Call DispatchAxisEventNG with axisTestResultsMap_[event.id] empty
     * @tc.expected: retFlag is false
     */
    event.horizontalAxis = 1;
    retFlag = eventManager->DispatchAxisEventNG(event);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step4. Call DispatchAxisEventNG with axisTestResultsMap_[event.id] not empty
     * @tc.expected: retFlag is false
     */
    auto axisEventTarget = AceType::MakeRefPtr<AxisEventTarget>();
    auto onAxisCallback = [](AxisInfo&) -> void {};
    axisEventTarget->SetOnAxisCallback(onAxisCallback);

    eventManager->axisTestResultsMap_[event.id].push_back(axisEventTarget);
    retFlag = eventManager->DispatchAxisEventNG(event);
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: EventManagerTest021
 * @tc.desc: Test DispatchAxisEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. AddKeyboardShortcutNode to eventManager
     */
    const int nodeIdCtrlShift = 10010;
    auto frameNodeCtrlShift = FrameNode::GetOrCreateFrameNode(CTRL, nodeIdCtrlShift, nullptr);
    frameNodeCtrlShift->SetActive(true);
    frameNodeCtrlShift->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    const uint8_t ctrlShift = static_cast<uint8_t>(CtrlKeysBit::CTRL) + static_cast<uint8_t>(CtrlKeysBit::SHIFT);
    frameNodeCtrlShift->GetOrCreateEventHub<EventHub>()->SetKeyboardShortcut(CHARACTER_A, ctrlShift, []() {});
    eventManager->AddKeyboardShortcutNode(frameNodeCtrlShift);

    const int nodeIdCtrlAlt = 10011;
    auto frameNodeCtrlAlt = FrameNode::GetOrCreateFrameNode(CTRL, nodeIdCtrlAlt, nullptr);
    frameNodeCtrlAlt->SetActive(true);
    frameNodeCtrlAlt->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    const uint8_t ctrlAlt = static_cast<uint8_t>(CtrlKeysBit::CTRL) + static_cast<uint8_t>(CtrlKeysBit::ALT);
    frameNodeCtrlAlt->GetOrCreateEventHub<EventHub>()->SetKeyboardShortcut(CHARACTER_A, ctrlAlt, []() {});
    eventManager->AddKeyboardShortcutNode(frameNodeCtrlAlt);

    const int nodeIdAltShift = 10012;
    auto frameNodeAltShift = FrameNode::GetOrCreateFrameNode(ALT, nodeIdAltShift, nullptr);
    frameNodeAltShift->SetActive(true);
    frameNodeAltShift->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    const uint8_t altShift = static_cast<uint8_t>(CtrlKeysBit::SHIFT) + static_cast<uint8_t>(CtrlKeysBit::ALT);
    frameNodeAltShift->GetOrCreateEventHub<EventHub>()->SetKeyboardShortcut(CHARACTER_A, altShift, []() {});
    eventManager->AddKeyboardShortcutNode(frameNodeAltShift);

    /**
     * @tc.steps: step3. call DispatchKeyboardShortcut
     * @tc.expected: AddKeyboardShortcutDoubleKeys calls.
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    eventManager->DispatchKeyboardShortcut(event);
    EXPECT_EQ(frameNodeCtrlShift->GetOrCreateEventHub<NG::EventHub>()->GetKeyboardShortcut().back().keys, ctrlShift);
    EXPECT_EQ(frameNodeCtrlAlt->GetOrCreateEventHub<NG::EventHub>()->GetKeyboardShortcut().back().keys, ctrlAlt);
    EXPECT_EQ(frameNodeAltShift->GetOrCreateEventHub<NG::EventHub>()->GetKeyboardShortcut().back().keys, altShift);
}

/**
 * @tc.name: EventManagerTest022
 * @tc.desc: Test DispatchAxisEventNG
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. AddKeyboardShortcutNode to eventManager
     */
    const int nodeIdCtrl = 10013;
    auto frameNodeCtrl = FrameNode::GetOrCreateFrameNode(CTRL, nodeIdCtrl, nullptr);
    frameNodeCtrl->SetActive(true);
    frameNodeCtrl->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    const uint8_t ctrl = static_cast<uint8_t>(CtrlKeysBit::CTRL);
    frameNodeCtrl->GetOrCreateEventHub<EventHub>()->SetKeyboardShortcut(CHARACTER_A, ctrl, []() {});
    eventManager->AddKeyboardShortcutNode(frameNodeCtrl);

    const int nodeIdAlt = 10014;
    auto frameNodeAlt = FrameNode::GetOrCreateFrameNode(ALT, nodeIdAlt, nullptr);
    frameNodeAlt->SetActive(true);
    frameNodeAlt->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    const uint8_t alt = static_cast<uint8_t>(CtrlKeysBit::ALT);
    frameNodeAlt->GetOrCreateEventHub<EventHub>()->SetKeyboardShortcut(CHARACTER_A, alt, []() {});
    eventManager->AddKeyboardShortcutNode(frameNodeAlt);

    const int nodeIdShift = 10015;
    auto frameNodeShift = FrameNode::GetOrCreateFrameNode(SHIFT, nodeIdShift, nullptr);
    frameNodeShift->SetActive(true);
    frameNodeShift->GetOrCreateEventHub<EventHub>()->SetEnabled(true);
    const uint8_t shift = static_cast<uint8_t>(CtrlKeysBit::SHIFT);
    frameNodeShift->GetOrCreateEventHub<EventHub>()->SetKeyboardShortcut(CHARACTER_A, shift, []() {});
    eventManager->AddKeyboardShortcutNode(frameNodeShift);

    /**
     * @tc.steps: step3. call DispatchKeyboardShortcut
     * @tc.expected: AddKeyboardShortcutSingleKey is called.
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    eventManager->DispatchKeyboardShortcut(event);
    EXPECT_EQ(frameNodeCtrl->GetOrCreateEventHub<NG::EventHub>()->GetKeyboardShortcut().back().keys, ctrl);
    EXPECT_EQ(frameNodeAlt->GetOrCreateEventHub<NG::EventHub>()->GetKeyboardShortcut().back().keys, alt);
    EXPECT_EQ(frameNodeShift->GetOrCreateEventHub<NG::EventHub>()->GetKeyboardShortcut().back().keys, shift);
}

/**
 * @tc.name: EventManagerTest023
 * @tc.desc: Test DispatchTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest023, TestSize.Level1)
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
     * @tc.steps: step2. Call DispatchTouchEvent with TouchType::DOWN and
                        touchTestResults_ empty;
     * @tc.expected: ret is false
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
     * @tc.steps: step4. Call DispatchTouchEvent with TouchType::UP and
                        touchTestResults_ has element;
     * @tc.expected: ret is true
     */
    event.type = TouchType::UP;
    ret = eventManager->DispatchTouchEvent(event);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: EventManagerTest024
 * @tc.desc: Test DispatchTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto currentHoverNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto currentHoverNode = FrameNode::GetOrCreateFrameNode(CTRL, currentHoverNodeId, nullptr);
    eventManager->currHoverNode_ = currentHoverNode;
    auto lastHoverNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto lastHoverNode = FrameNode::GetOrCreateFrameNode(SHIFT, lastHoverNodeId, nullptr);
    eventManager->lastHoverNode_ = lastHoverNode;

    /**
     * @tc.steps: step2. Call DispatchMouseHoverAnimationNG with MouseAction::PRESS;
     * @tc.expected: ret is false
     */
    MouseEvent event;
    event.button = MouseButton::NONE_BUTTON;
    event.action = MouseAction::PRESS;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_NE(eventManager->currHoverNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step3. Call DispatchMouseHoverAnimationNG with MouseAction::RELEASE;
     * @tc.expected: ret is false
     */
    event.action = MouseAction::RELEASE;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_NE(eventManager->currHoverNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step4. Call DispatchMouseHoverAnimationNG with MouseAction::MOVE;
     * @tc.expected: ret is false
     */
    event.action = MouseAction::MOVE;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_NE(eventManager->currHoverNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step5. Call DispatchMouseHoverAnimationNG with MouseAction::WINDOW_ENTER;
     * @tc.expected: ret is false
     */
    event.action = MouseAction::WINDOW_ENTER;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_NE(eventManager->currHoverNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step6. Call DispatchMouseHoverAnimationNG with MouseAction::WINDOW_LEAVE;
     * @tc.expected: ret is false
     */
    event.action = MouseAction::WINDOW_LEAVE;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_NE(eventManager->currHoverNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: EventManagerTest025
 * @tc.desc: Test FlushTouchEventsBegin
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest025, TestSize.Level1)
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
    event.id = resultId;
    std::list<TouchEvent> touchEvents { event };
    eventManager->FlushTouchEventsBegin(touchEvents);
    EXPECT_NE(eventManager->touchTestResults_.find(event.id), eventManager->touchTestResults_.end());
}

/**
 * @tc.name: EventManagerTest026
 * @tc.desc: Test FlushTouchEventsBegin
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest026, TestSize.Level1)
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
    event.id = resultId;
    std::list<TouchEvent> touchEvents { event };
    eventManager->FlushTouchEventsEnd(touchEvents);
    EXPECT_NE(eventManager->touchTestResults_.find(event.id), eventManager->touchTestResults_.end());
}

/**
 * @tc.name: EventManagerTest027
 * @tc.desc: Test FlushTouchEventsBegin
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest027, TestSize.Level1)
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
    eventManager->AxisTest(axisEvent, frameNode);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: EventManagerTest028
 * @tc.desc: Test DispatchTouchEvent:hoverNodeCur and hoverNodePre both null
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    eventManager->currHoverNode_ = FrameNode::GetOrCreateFrameNode(CTRL, 0, nullptr);
    eventManager->lastHoverNode_ = FrameNode::GetOrCreateFrameNode(CTRL, 0, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseHoverAnimationNG with MouseAction::PRESS;
     * @tc.expected: ret is false
     */
    MouseEvent event;
    event.button = MouseButton::NONE_BUTTON;
    event.action = MouseAction::PRESS;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step3. Call DispatchMouseHoverAnimationNG with MouseAction::RELEASE;
     * @tc.expected: ret is false
     */
    event.action = MouseAction::RELEASE;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step4. Call DispatchMouseHoverAnimationNG with MouseAction::MOVE;
     * @tc.expected: ret is false
     */
    event.action = MouseAction::MOVE;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step5. Call DispatchMouseHoverAnimationNG with MouseAction::WINDOW_ENTER;
     * @tc.expected: ret is false
     */
    event.action = MouseAction::WINDOW_ENTER;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step6. Call DispatchMouseHoverAnimationNG with MouseAction::WINDOW_LEAVE;
     * @tc.expected: ret is false
     */
    event.action = MouseAction::WINDOW_LEAVE;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step6. Call DispatchMouseHoverAnimationNG with MouseAction::HOVER;
     * @tc.expected: ret is false
     */
    event.action = MouseAction::HOVER;
    eventManager->DispatchMouseHoverAnimationNG(event);
    EXPECT_EQ(eventManager->currHoverNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: EventManagerTest029
 * @tc.desc: Test TouchTest
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    TouchEvent touchPoint;
    touchPoint.id = 100;
    touchPoint.type = TouchType::DOWN;

    TouchRestrict touchRestrict;
    Offset offset;

    /**
     * @tc.steps: step1. Create renderNode.
     * @tc.expected: renderNode is not null.
     */
    auto animatablePoperties = AceType::MakeRefPtr<OHOS::Ace::AnimatableProperties>();
    auto renderNode = AceType::DynamicCast<RenderNode>(animatablePoperties);

    /**
     * @tc.steps: step2. Call TouchTest with MouseAction::PRESS;
     * @tc.expected: ret is false
     */
    eventManager->TouchTest(touchPoint, renderNode, touchRestrict, offset, 0, true);
    auto findIt = eventManager->touchTestResults_.find(touchPoint.id);
    EXPECT_EQ(findIt, eventManager->touchTestResults_.end());
}

/**
 * @tc.name: EventManagerTest032
 * @tc.desc: Test DispatchAxisEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    AxisEvent axisEvent;
    axisEvent.horizontalAxis = 0;
    axisEvent.verticalAxis = 0;
    axisEvent.pinchAxisScale = 1.0f;

    /**
     * @tc.steps: step2. Call AxisTest with SourceType::TOUCH.
     * @tc.expected: eventManager->axisNode_.Upgrade() is not null.
     */
    bool retFlag = eventManager->DispatchAxisEvent(axisEvent);
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: EventManagerTest033
 * @tc.desc: Test DumpEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DumpEvent.
     * @tc.expected: eventManager->axisNode_.Upgrade() is not null.
     */
    eventManager->DumpEvent(EventTreeType::TOUCH);
    std::list<std::pair<int32_t, std::string>> dumpList;
    eventManager->eventTree_.Dump(dumpList, 0);
    EXPECT_TRUE(dumpList.empty());
}

/**
 * @tc.name: EventManagerTest034
 * @tc.desc: Test DispatchMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseEvent.
     * @tc.expected: retFlag is false.
     */
    MouseEvent event;
    event.action = MouseAction::PRESS;
    bool retFlag = eventManager->DispatchMouseEvent(event);
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: EventManagerTest0351
 * @tc.desc: Test DispatchMouseHoverAnimation in MouseAction::PRESS branches
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest0351, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseEvent.
     * @tc.expected: hoverNodeCur is not null.
     */
    MouseEvent event;
    event.action = MouseAction::PRESS;
    eventManager->DispatchMouseHoverAnimation(event);
    auto hoverNodeCur = eventManager->mouseHoverNode_.Upgrade();
    EXPECT_EQ(hoverNodeCur, nullptr);
}

/**
 * @tc.name: EventManagerTest0352
 * @tc.desc: Test DispatchMouseHoverAnimation in MouseAction::RELEASE branches
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest0352, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseEvent.
     * @tc.expected: hoverNodeCur is not null.
     */
    MouseEvent event;
    event.action = MouseAction::RELEASE;
    eventManager->DispatchMouseHoverAnimation(event);
    auto hoverNodeCur = eventManager->mouseHoverNode_.Upgrade();
    EXPECT_EQ(hoverNodeCur, nullptr);
}

/**
 * @tc.name: EventManagerTest0353
 * @tc.desc: Test DispatchMouseHoverAnimation in MouseAction::WINDOW_ENTER branches
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest0353, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseEvent.
     * @tc.expected: hoverNodeCur is not null.
     */
    MouseEvent event;
    event.action = MouseAction::WINDOW_ENTER;
    eventManager->DispatchMouseHoverAnimation(event);
    auto hoverNodeCur = eventManager->mouseHoverNode_.Upgrade();
    EXPECT_EQ(hoverNodeCur, nullptr);
}

/**
 * @tc.name: EventManagerTest0354
 * @tc.desc: Test DispatchMouseHoverAnimation in MouseAction::WINDOW_LEAVE branches
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest0354, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseEvent.
     * @tc.expected: hoverNodeCur is not null.
     */
    MouseEvent event;
    event.action = MouseAction::WINDOW_LEAVE;
    eventManager->DispatchMouseHoverAnimation(event);
    auto hoverNodeCur = eventManager->mouseHoverNode_.Upgrade();
    EXPECT_EQ(hoverNodeCur, nullptr);
}

/**
 * @tc.name: EventManagerTest0355
 * @tc.desc: Test DispatchMouseHoverAnimation in MouseButton::NONE_BUTTON and MouseAction::MOVE branches
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest0355, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseEvent.
     * @tc.expected: hoverNodeCur is not null.
     */
    MouseEvent event;
    event.button = MouseButton::NONE_BUTTON;
    event.action = MouseAction::MOVE;
    eventManager->DispatchMouseHoverAnimation(event);
    auto hoverNodeCur = eventManager->mouseHoverNode_.Upgrade();
    EXPECT_EQ(hoverNodeCur, nullptr);
}

/**
 * @tc.name: EventManagerTest0356
 * @tc.desc: Test DispatchMouseHoverAnimation in MouseAction::MOVE branches
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest0356, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseEvent.
     * @tc.expected: hoverNodeCur is not null.
     */
    MouseEvent event;
    event.action = MouseAction::MOVE;
    eventManager->DispatchMouseHoverAnimation(event);
    auto hoverNodeCur = eventManager->mouseHoverNode_.Upgrade();
    EXPECT_EQ(hoverNodeCur, nullptr);
}

/**
 * @tc.name: EventManagerTest0357
 * @tc.desc: Test DispatchMouseHoverAnimation in MouseButton::NONE_BUTTON branches
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest0357, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseEvent.
     * @tc.expected: hoverNodeCur is not null.
     */
    MouseEvent event;
    event.button = MouseButton::NONE_BUTTON;
    eventManager->DispatchMouseHoverAnimation(event);
    auto hoverNodeCur = eventManager->mouseHoverNode_.Upgrade();
    EXPECT_EQ(hoverNodeCur, nullptr);
}

/**
 * @tc.name: EventManagerTest036
 * @tc.desc: Test DispatchMouseHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    /**
     * @tc.steps: step2. Call DispatchMouseHoverEvent.
     * @tc.expected: retFlag is true.
     */
    MouseEvent event;
    bool retFlag = eventManager->DispatchMouseHoverEvent(event);
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: PanRecognizerAxisDirection001
 * @tc.desc: Test GetAxisDirection() of PanRecognizer.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, PanRecognizerAxisDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pan recognizers.
     * @tc.expected: recognizers is not null and axis direction is correct.
     */
    auto panHorizontal = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::HORIZONTAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panHorizontal, nullptr);
    EXPECT_EQ(panHorizontal->GetAxisDirection(), Axis::HORIZONTAL);

    auto panVertical = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::VERTICAL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panVertical, nullptr);
    EXPECT_EQ(panVertical->GetAxisDirection(), Axis::VERTICAL);

    auto panLeft = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::LEFT }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panLeft, nullptr);
    EXPECT_EQ(panLeft->GetAxisDirection(), Axis::HORIZONTAL);

    auto panRight = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::RIGHT }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panRight, nullptr);
    EXPECT_EQ(panRight->GetAxisDirection(), Axis::HORIZONTAL);

    auto panUp = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::UP }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panUp, nullptr);
    EXPECT_EQ(panUp->GetAxisDirection(), Axis::VERTICAL);

    auto panDown = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::DOWN }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panDown, nullptr);
    EXPECT_EQ(panDown->GetAxisDirection(), Axis::VERTICAL);

    auto panFree = AceType::MakeRefPtr<PanRecognizer>(
        DEFAULT_PAN_FINGER, PanDirection { PanDirection::ALL }, DEFAULT_PAN_DISTANCE.ConvertToPx());
    ASSERT_NE(panFree, nullptr);
    EXPECT_EQ(panFree->GetAxisDirection(), Axis::FREE);
}

/**
 * @tc.name: SwipeRecognizerAxisDirection001
 * @tc.desc: Test GetAxisDirection() of SwipeRecognizer.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, SwipeRecognizerAxisDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipe recognizers.
     * @tc.expected: recognizers is not null and axis direction is correct.
     */
    auto swipeHorizontal = AceType::MakeRefPtr<SwipeRecognizer>(1, SwipeDirection { SwipeDirection::HORIZONTAL }, 0.0);
    ASSERT_NE(swipeHorizontal, nullptr);
    EXPECT_EQ(swipeHorizontal->GetAxisDirection(), Axis::HORIZONTAL);

    auto swipeVertical = AceType::MakeRefPtr<SwipeRecognizer>(1, SwipeDirection { SwipeDirection::VERTICAL }, 0.0);
    ASSERT_NE(swipeVertical, nullptr);
    EXPECT_EQ(swipeVertical->GetAxisDirection(), Axis::VERTICAL);

    auto swipeFree = AceType::MakeRefPtr<SwipeRecognizer>(1, SwipeDirection { SwipeDirection::ALL }, 0.0);
    ASSERT_NE(swipeFree, nullptr);
    EXPECT_EQ(swipeFree->GetAxisDirection(), Axis::FREE);
}

/**
 * @tc.name: ExclusiveRecognizerAxisDirection001
 * @tc.desc: Test GetAxisDirection() of ExclusiveRecognizer.
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, ExclusiveRecognizerAxisDirection001, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, ParallelRecognizerAxisDirection001, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, EventManagerTest090, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, EventManagerTest091, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, EventManagerTest092, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, EventManagerTest093, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, EventManagerTest094, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, EventManagerTest095, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, EventManagerTest096, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, EventManagerTest097, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, EventManagerTest098, TestSize.Level1)
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
HWTEST_F(EventManagerTestNg, EventManagerTest099, TestSize.Level1)
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
