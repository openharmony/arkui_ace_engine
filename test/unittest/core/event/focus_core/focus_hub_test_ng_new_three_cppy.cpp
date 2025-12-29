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
#include "test/unittest/core/event/focus_hub_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: FocusHubTestNg0125
 * @tc.desc: Test the function dispatchKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0125, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());

    /**
     * @tc.steps: step2. Create FocusHub and set keyEvent.
     */
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child1);
    frameNode->AddChild(child2);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetFocusType(FocusType::SCOPE);
    RefPtr<EventHub> childEventHub2 = AceType::MakeRefPtr<EventHub>();
    childEventHub2->AttachHost(child2);
    auto childFocusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(childEventHub2)));
    childFocusHub2->SetFocusType(FocusType::NODE);
    focusHub->currentFocus_ = true;

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;
    /**
     * @tc.steps: step3. Binds onKeyEventDispatch callback, executes dipatchKeyEvent to dispatch keyevent to child2.
     */
    auto onKeyEventDispatchCallback = [&childFocusHub2, &keyEvent](KeyEventInfo& eventInfo) -> bool {
        childFocusHub2->currentFocus_ = true;
        return childFocusHub2->HandleEvent(keyEvent);
    };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.expected: The return value of child2 onKeyEvent is false.
     * @tc.steps: step4. call the function onKeyEventDispatch and dipatchKeyEvent.
     */
    auto onKeyEventCallback = [](KeyEventInfo& eventInfo) -> bool { return false; };
    childFocusHub2->SetOnKeyCallback(std::move(onKeyEventCallback));
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg0126
 * @tc.desc: Test the function dispatchKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0126, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());

    /**
     * @tc.steps: step2. Create FocusHub and set keyEvent.
     */
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child1);
    frameNode->AddChild(child2);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetFocusType(FocusType::SCOPE);
    RefPtr<EventHub> childEventHub2 = AceType::MakeRefPtr<EventHub>();
    childEventHub2->AttachHost(child2);
    auto childFocusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(childEventHub2)));
    childFocusHub2->SetFocusType(FocusType::NODE);
    focusHub->currentFocus_ = true;

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;

    /**
     * @tc.steps: step3. Binds onKeyEventDispatch callback, executes dipatchKeyEvent to dispatch keyevent to child2.
     */
    auto onKeyEventDispatchCallback = [&childFocusHub2, &keyEvent](KeyEventInfo& eventInfo) -> bool {
        childFocusHub2->currentFocus_ = true;
        return childFocusHub2->HandleEvent(keyEvent);
    };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.expected: The return value of child2 onKeyEvent SetStopPropagation true.
     * @tc.steps: step6. call the function onKeyEventDispatch and dipatchKeyEvent.
     */
    auto onKeyEventCallback = [](KeyEventInfo& eventInfo) -> bool {
        eventInfo.SetStopPropagation(true);
        return false;
    };
    childFocusHub2->SetOnKeyCallback(std::move(onKeyEventCallback));
    EXPECT_TRUE(focusHub->HandleEvent(keyEvent));
}

#ifdef SUPPORT_DIGITAL_CROWN
/**
 * @tc.name: FocusHubTestNg0999
 * @tc.desc: Test the function OnFocusEventNode.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0999, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 120, AceType::MakeRefPtr<ButtonPattern>());
    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);

    /**
     * @tc.steps2: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);
    NonPointerEvent nonPointerEvent;
    nonPointerEvent.sourceType = SourceType::CROWN;
    FocusEvent focusEvent(nonPointerEvent);
    EXPECT_FALSE(focusHub->OnFocusEventNode(focusEvent));

    focusHub->currentFocus_ = true;
    auto focus = focusHub->IsCurrentFocus();
    EXPECT_EQ(focus, true);
}

/**
 * @tc.name: FocusHubTestNg01000
 * @tc.desc: Test the function HandleCrownEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg01000, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 120, AceType::MakeRefPtr<ButtonPattern>());
    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);

    /**
     * @tc.steps2: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);

    CrownEvent event;
    EXPECT_FALSE(focusHub->HandleCrownEvent(event));

    OnCrownCallbackFunc onCrownEventCallback = [](CrownEventInfo& info) {};
    focusHub->SetOnCrownCallback(std::move(onCrownEventCallback));

    EXPECT_FALSE(focusHub->HandleCrownEvent(event));

    focusHub->currentFocus_ = true;
    auto focus = focusHub->IsCurrentFocus();
    EXPECT_EQ(focus, true);
}

/**
 * @tc.name: FocusHubTestNg01001
 * @tc.desc: Test the function ProcessOnCrownEventInternal.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg01001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 120, AceType::MakeRefPtr<ButtonPattern>());
    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);

    /**
     * @tc.steps2: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);

    CrownEvent event;
    EXPECT_FALSE(focusHub->ProcessOnCrownEventInternal(event));

    focusHub->currentFocus_ = true;
    auto focus = focusHub->IsCurrentFocus();
    EXPECT_EQ(focus, true);

    OnCrownEventFunc onCrownEventsInternal = [](const CrownEvent& info) -> bool { return true;};
    focusHub->SetOnCrownEventInternal(std::move(onCrownEventsInternal));
    EXPECT_TRUE(focusHub->ProcessOnCrownEventInternal(event));
}
#endif

/**
 * @tc.name: GetRootFocusHub001
 * @tc.desc: Test the function GetRootFocusHub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetRootFocusHub001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);
}

/**
 * @tc.name: SetFocusable001
 * @tc.desc: Test the function SetFocusable.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetFocusable001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusable_ = true;
    focusHub->implicitFocusable_ = true;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->SetFocusable(true, true);
    focusHub->focusDepend_ = FocusDependence::CHILD;
    focusHub->SetFocusable(true, true);
    EXPECT_NE(focusHub->focusDepend_, FocusDependence::CHILD);
}

/**
 * @tc.name: DumpFocusScopeTree001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, DumpFocusScopeTree001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    int32_t depth = 1;
    focusHub->focusType_ = FocusType::SCOPE;
    auto ss = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(ss));
    DumpLog::GetInstance().description_.push_back("test");
    focusHub->currentFocus_ = false;
    focusHub->SetTabStop(true);
    focusHub->focusable_ = false;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());
}

/**
* @tc.name: DumpFocusNodeTree001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, DumpFocusNodeTree001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    int32_t depth = 1;
    focusHub->focusType_ = FocusType::NODE;
    auto ss = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(ss));
    DumpLog::GetInstance().description_.push_back("test");
    focusHub->currentFocus_ = false;
    focusHub->SetTabStop(true);
    focusHub->focusable_ = false;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());
}

/**
* @tc.name: HandleFocusNavigation001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, HandleFocusNavigation001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent(keyEvent);
    auto ret = focusHub->HandleFocusNavigation(focusEvent);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: HandleFocusTravel001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, HandleFocusTravel001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent(keyEvent);
    focusEvent.intension = FocusIntension::LEFT;
    auto ret = focusHub->HandleFocusTravel(focusEvent);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: DumpFocusTree003
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, DumpFocusTree003, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    int32_t depth = 1;
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    focusHub->focusType_ = FocusType::SCOPE;
    auto stream = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(stream));

    DumpLog::GetInstance().description_.push_back("test");
    focusHub->currentFocus_ = false;
    focusHub->SetTabStop(true);
    focusHub->focusable_ = false;
    focusHub->DumpFocusTree(depth, true);
    EXPECT_NE(DumpLog::GetInstance().description_.empty(), true);

    focusHub->focusType_ = FocusType::NODE;
    DumpLog::GetInstance().description_.push_back("test");
    focusHub->currentFocus_ = false;
    focusHub->SetTabStop(true);
    focusHub->focusable_ = false;
    focusHub->DumpFocusTree(depth, true);
    EXPECT_NE(DumpLog::GetInstance().description_.empty(), true);
}

/**
* @tc.name: LostFocusToTabStop001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, LostFocusToTabStop001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto focusNode = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusNode->SetCurrentFocus(true);
    focusHub->LostFocusToTabStop(focusNode);
    EXPECT_EQ(focusNode->IsCurrentFocus(), true);
}

/**
* @tc.name: LostFocusToTabStop001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, LostFocusToTabStop002, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto focusNode = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusNode->SetCurrentFocus(false);
    focusHub->LostFocusToTabStop(focusNode);
    EXPECT_EQ(focusNode->IsCurrentFocus(), false);
}

/**
* @tc.name: RequestNextFocusByKey001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, RequestNextFocusByKey001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetNextFocus(FocusIntension::SHIFT_TAB, std::string("SHIFT_TAB"));
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent1(keyEvent);
    focusEvent1.intension = FocusIntension::SHIFT_TAB;
    auto ret = focusHub->RequestNextFocusByKey(focusEvent1);
    EXPECT_EQ(ret, false);

    focusHub->ResetNextFocus();
    focusHub->SetNextFocus(FocusIntension::UP, std::string("UP"));
    FocusEvent focusEvent2(keyEvent);
    focusEvent2.intension = FocusIntension::UP;
    ret = focusHub->RequestNextFocusByKey(focusEvent2);
    EXPECT_EQ(ret, false);

    focusHub->ResetNextFocus();
    focusHub->SetNextFocus(FocusIntension::DOWN, std::string("DOWN"));
    FocusEvent focusEvent3(keyEvent);
    focusEvent3.intension = FocusIntension::DOWN;
    ret = focusHub->RequestNextFocusByKey(focusEvent3);
    EXPECT_EQ(ret, false);

    focusHub->ResetNextFocus();
    focusHub->SetNextFocus(FocusIntension::LEFT, std::string("LEFT"));
    FocusEvent focusEvent4(keyEvent);
    focusEvent4.intension = FocusIntension::LEFT;
    ret = focusHub->RequestNextFocusByKey(focusEvent4);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: RequestNextFocusByKey002
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, RequestNextFocusByKey002, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetNextFocus(FocusIntension::SHIFT_TAB, std::string("SHIFT_TAB"));
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);

    focusHub->ResetNextFocus();
    focusHub->SetNextFocus(FocusIntension::RIGHT, std::string("RIGHT"));
    FocusEvent focusEvent1(keyEvent);
    focusEvent1.intension = FocusIntension::RIGHT;
    auto ret = focusHub->RequestNextFocusByKey(focusEvent1);
    EXPECT_EQ(ret, false);

    focusHub->ResetNextFocus();
    focusHub->SetNextFocus(FocusIntension::SELECT, std::string("SELECT"));
    FocusEvent focusEvent2(keyEvent);
    focusEvent2.intension = FocusIntension::SELECT;
    ret = focusHub->RequestNextFocusByKey(focusEvent2);
    EXPECT_EQ(ret, false);

    focusHub->ResetNextFocus();
    focusHub->SetNextFocus(FocusIntension::ESC, std::string("ESC"));
    FocusEvent focusEvent3(keyEvent);
    focusEvent3.intension = FocusIntension::ESC;
    ret = focusHub->RequestNextFocusByKey(focusEvent3);
    EXPECT_EQ(ret, false);

    focusHub->ResetNextFocus();
    focusHub->SetNextFocus(FocusIntension::HOME, std::string("HOME"));
    FocusEvent focusEvent4(keyEvent);
    focusEvent4.intension = FocusIntension::HOME;
    ret = focusHub->RequestNextFocusByKey(focusEvent4);
    EXPECT_EQ(ret, false);

    focusHub->ResetNextFocus();
    focusHub->SetNextFocus(FocusIntension::END, std::string("END"));
    FocusEvent focusEvent5(keyEvent);
    focusEvent5.intension = FocusIntension::END;
    ret = focusHub->RequestNextFocusByKey(focusEvent5);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: GetNextFocusByStep001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, GetNextFocusByStep001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;
    auto ret = focusHub->GetNextFocusByStep(keyEvent);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: RequestUserNextFocus001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, RequestUserNextFocus001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent(keyEvent);
    auto ret = focusHub->RequestUserNextFocus(focusEvent);
    EXPECT_EQ(ret, false);

    focusHub->ResetNextFocus();
    focusHub->SetNextFocus(FocusIntension::END, std::string("END"));
    ret = focusHub->RequestUserNextFocus(focusEvent);
    EXPECT_EQ(ret, false);

    focusHub->ResetNextFocus();
    focusHub->SetNextFocus(FocusIntension::END, std::string("END"));
    focusEvent.intension = FocusIntension::END;
    ret = focusHub->RequestUserNextFocus(focusEvent);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: RequestNextFocusOfKeyTab001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, RequestNextFocusOfKeyTab001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent(keyEvent);
    focusHub->isGroup_ = true;
    EXPECT_EQ(focusHub->IsInFocusGroup(), true);
    auto ret = focusHub->RequestNextFocusOfKeyTab(focusEvent);
    EXPECT_EQ(ret, false);

    focusHub->isGroup_ = false;
    EXPECT_EQ(focusHub->IsInFocusGroup(), false);
    focusEvent.intension = FocusIntension::TAB;
    ret = focusHub->RequestNextFocusOfKeyTab(focusEvent);
    EXPECT_EQ(ret, false);

    focusHub->isGroup_ = false;
    EXPECT_EQ(focusHub->IsInFocusGroup(), false);
    focusEvent.intension = FocusIntension::SHIFT_TAB;
    ret = focusHub->RequestNextFocusOfKeyTab(focusEvent);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: RequestNextFocusByDefaultAlgorithm001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, RequestNextFocusByDefaultAlgorithm001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    FocusStep moveStep = FocusStep::LEFT;
    auto frameOffset = frameNode->GetTransformRelativeOffset();
    auto geometryNode = frameNode->GetGeometryNode();
    RectF frameRect = RectF(frameOffset, geometryNode->GetFrameRect().GetSize());

    focusHub->focusAlgorithm_.scopeType = ScopeType::OTHERS;
    focusHub->focusAlgorithm_.direction = ScopeFocusDirection::VERTICAL;
    focusHub->focusAlgorithm_.isVertical = true;
    auto ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);

    focusHub->focusAlgorithm_.scopeType = ScopeType::OTHERS;
    focusHub->focusAlgorithm_.direction = ScopeFocusDirection::UNIVERSAL;
    ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);

    std::list<RefPtr<FocusHub>> focusNodes;
    focusHub->FlushChildrenFocusHub(focusNodes);
    focusHub->focusAlgorithm_.scopeType = ScopeType::PROJECT_AREA;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*(focusNodes.begin())));
    moveStep = FocusStep::SHIFT_TAB;
    ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: RequestNextFocusByDefaultAlgorithm002
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, RequestNextFocusByDefaultAlgorithm002, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    FocusStep moveStep = FocusStep::LEFT;
    auto frameOffset = frameNode->GetTransformRelativeOffset();
    auto geometryNode = frameNode->GetGeometryNode();
    RectF frameRect = RectF(frameOffset, geometryNode->GetFrameRect().GetSize());

    std::list<RefPtr<FocusHub>> focusNodes;
    focusHub->FlushChildrenFocusHub(focusNodes);
    auto node = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusNodes.push_front(node);
    focusHub->focusAlgorithm_.scopeType = ScopeType::PROJECT_AREA;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*(focusNodes.begin())));
    EXPECT_NE(focusHub->lastWeakFocusNode_.Upgrade(), nullptr);

    auto ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);

    moveStep = FocusStep::SHIFT_TAB;
    ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: RequestNextFocusByDefaultAlgorithm003
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, RequestNextFocusByDefaultAlgorithm003, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    FocusStep moveStep = FocusStep::LEFT;
    auto frameOffset = frameNode->GetTransformRelativeOffset();
    auto geometryNode = frameNode->GetGeometryNode();
    RectF frameRect = RectF(frameOffset, geometryNode->GetFrameRect().GetSize());

    focusHub->focusAlgorithm_.scopeType = ScopeType::OTHERS;
    focusHub->focusAlgorithm_.direction = ScopeFocusDirection::UNIVERSAL;
    focusHub->focusAlgorithm_.isVertical = true;
    auto ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);

    focusHub->focusAlgorithm_.scopeType = ScopeType::OTHERS;
    focusHub->focusAlgorithm_.direction = ScopeFocusDirection::UNIVERSAL;
    focusHub->focusAlgorithm_.isVertical = false;
    ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);

    focusHub->focusAlgorithm_.scopeType = ScopeType::OTHERS;
    focusHub->focusAlgorithm_.direction = ScopeFocusDirection::VERTICAL;
    focusHub->focusAlgorithm_.isVertical = false;
    ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: RequestNextFocusByDefaultAlgorithm004
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, RequestNextFocusByDefaultAlgorithm004, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    FocusStep moveStep = FocusStep::LEFT;
    auto frameOffset = frameNode->GetTransformRelativeOffset();
    auto geometryNode = frameNode->GetGeometryNode();
    RectF frameRect = RectF(frameOffset, geometryNode->GetFrameRect().GetSize());

    moveStep = FocusStep::SHIFT_TAB;
    focusHub->focusAlgorithm_.scopeType = ScopeType::OTHERS;
    focusHub->focusAlgorithm_.direction = ScopeFocusDirection::VERTICAL;
    focusHub->focusAlgorithm_.isVertical = true;
    auto ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);

    moveStep = FocusStep::SHIFT_TAB;
    focusHub->focusAlgorithm_.scopeType = ScopeType::OTHERS;
    focusHub->focusAlgorithm_.direction = ScopeFocusDirection::UNIVERSAL;
    focusHub->focusAlgorithm_.isVertical = true;
    ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);

    moveStep = FocusStep::SHIFT_TAB;
    focusHub->focusAlgorithm_.scopeType = ScopeType::OTHERS;
    focusHub->focusAlgorithm_.direction = ScopeFocusDirection::VERTICAL;
    focusHub->focusAlgorithm_.isVertical =false;
    ret = focusHub->RequestNextFocusByDefaultAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: LostChildFocusToSelf001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, LostChildFocusToSelf001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetCurrentFocus(false);
    focusHub->LostChildFocusToSelf();
    EXPECT_NE(focusHub->IsCurrentFocus(), true);
}

/**
* @tc.name: RequestNextFocusByCustomAlgorithm001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, RequestNextFocusByCustomAlgorithm001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    FocusStep moveStep = FocusStep::LEFT;
    auto frameOffset = frameNode->GetTransformRelativeOffset();
    auto geometryNode = frameNode->GetGeometryNode();
    RectF frameRect = RectF(frameOffset, geometryNode->GetFrameRect().GetSize());

    std::list<RefPtr<FocusHub>> focusNodes;
    focusHub->FlushChildrenFocusHub(focusNodes);
    auto ret = focusHub->RequestNextFocusByCustomAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: IsArrowKeyStepOut001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, IsArrowKeyStepOut001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    FocusStep moveStep = FocusStep::LEFT;
    focusHub->isGroup_ = true;
    focusHub->arrowKeyStepOut_ = false;
    auto ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, true);

    focusHub->isGroup_ = false;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);

    focusHub->arrowKeyStepOut_ = true;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);

    focusHub->isGroup_ = true;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: IsArrowKeyStepOut002
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, IsArrowKeyStepOut002, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    FocusStep moveStep = FocusStep::SHIFT_TAB;
    focusHub->isGroup_ = true;
    focusHub->arrowKeyStepOut_ = false;
    auto ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);

    focusHub->isGroup_ = false;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);

    focusHub->arrowKeyStepOut_ = true;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);

    focusHub->isGroup_ = true;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: IsChildOf001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsChildOf001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto nodeParent = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1,
        AceType::MakeRefPtr<FlexLayoutPattern>());
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);

    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto parentFocusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto ret = focusHub2->IsChildOf(parentFocusHub2);
    EXPECT_EQ(ret, false);

    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->HandleLastFocusNodeInFocusWindow();
    auto parentFocusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ret = focusHub->IsChildOf(parentFocusHub);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: RequestNextFocus001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, RequestNextFocus001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusNode = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    std::list<RefPtr<FocusHub>> focusNodes;
    focusNode->SetCurrentFocus(true);
    focusNodes.push_front(focusNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->FlushChildrenFocusHub(focusNodes);
    focusHub->focusAlgorithm_.scopeType = ScopeType::PROJECT_AREA;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*(focusNodes.begin())));
    FocusStep moveStep = FocusStep::SHIFT_TAB;
    auto ret = focusHub->RequestNextFocus(moveStep);
    EXPECT_EQ(ret, false);
    focusHub->ClearLastFocusNode();
}

/**
 * @tc.name: FocusToHeadOrTailChild001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusToHeadOrTailChild001, TestSize.Level1)
{
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetAllowedLoop(false);
    focusHub->SetCurrentFocus(true);
    auto res = focusHub->FocusToHeadOrTailChild(true);
    EXPECT_FALSE(res);

    focusHub->SetAllowedLoop(false);
    focusHub->SetCurrentFocus(false);
    focusHub->isGroup_ = false;
    focusHub->tabStop_ = true;
    res = focusHub->FocusToHeadOrTailChild(true);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: FocusToHeadOrTailChild002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusToHeadOrTailChild002, TestSize.Level1)
{
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();
    focusHub->focusStyleType_ = FocusStyleType::CUSTOM_REGION;
    focusHub->focusType_ = FocusType::SCOPE;
    frameNode1->parent_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    frameNode->children_.push_back(frameNode1);
    ASSERT_TRUE(focusHub->IsFocusableNode());
    ASSERT_TRUE(focusHub->IsFocusableScope());
    focusHub->tabStop_ = true;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    EXPECT_TRUE(focusHub->FocusToHeadOrTailChild(true));
}

/**
 * @tc.name: FocusToHeadOrTailChild003
 * @tc.desc: Test the function FocusToHeadOrTailChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusToHeadOrTailChild003, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps2: check isFocusingByTab_ is false.
     */
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    EXPECT_FALSE(context->isFocusingByTab_);
    auto res = focusHub->FocusToHeadOrTailChild(true);
    EXPECT_TRUE(res);

    /**
     * @tc.steps3: set tabIndex_ to 0.
     */
    context->isFocusingByTab_ = true;
    focusHub->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub->focusCallbackEvents_->tabIndex_ = 0;
    auto isFocusableByTab = focusHub->IsFocusableByTab();
    EXPECT_TRUE(isFocusableByTab);
    res = focusHub->FocusToHeadOrTailChild(true);
    EXPECT_TRUE(res);

    /**
     * @tc.steps4: set tabIndex_ to -1.
     */
    focusHub->focusCallbackEvents_->tabIndex_ = -1;
    isFocusableByTab = focusHub->IsFocusableByTab();
    EXPECT_FALSE(isFocusableByTab);
    res = focusHub->FocusToHeadOrTailChild(true);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: CalculatePosition001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, CalculatePosition001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    auto frameOffset = frameNode->GetTransformRelativeOffset();
    auto geometryNode = frameNode->GetGeometryNode();
    RectF frameRect = RectF(frameOffset, geometryNode->GetFrameRect().GetSize());

    auto focusNode = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    std::list<RefPtr<FocusHub>> focusNodes;
    focusNode->SetCurrentFocus(true);
    focusNodes.push_front(focusNode);
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*(focusNodes.begin())));
    auto ret = focusHub->CalculatePosition();
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: GetUnfocusableParentFocusNode001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetUnfocusableParentFocusNode001, TestSize.Level1)
{
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();
    focusHub->focusStyleType_ = FocusStyleType::CUSTOM_REGION;
    focusHub->focusType_ = FocusType::SCOPE;
    frameNode1->parent_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    frameNode->children_.push_back(frameNode1);
    auto res = focusHub->GetUnfocusableParentFocusNode();
    WeakPtr<FocusHub> FocusHub2 = nullptr;
    EXPECT_EQ(res, FocusHub2);
}
} // namespace OHOS::Ace::NG