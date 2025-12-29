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
#include "gtest/gtest.h"
#include "core/components_ng/event/focus_event_handler.h"
#include "core/event/focus_axis_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: HasForwardFocusMovementInChildren001
 * @tc.desc: Test the function HasForwardFocusMovementInChildren.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HasForwardFocusMovementInChildren001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent;
    EXCEPT_FALSE(focusHub->HasForwardFocusMovementInChildren());
}

/**
 * @tc.name: ClearFocusMovementFlagsInChildren001
 * @tc.desc: Test the function ClearFocusMovementFlagsInChildren.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, ClearFocusMovementFlagsInChildren001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent;
    EXCEPT_FALSE(focusHub->HasBackwardFocusMovement());
}

/**
 * @tc.name: SetLastWeakFocusToPreviousInFocusView001
 * @tc.desc: Test the function SetLastWeakFocusToPreviousInFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetLastWeakFocusToPreviousInFocusView001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent;
    focusHub->SetLastWeakFocusToPreviousInFocusView();
    EXCEPT_FALSE(focusHub->lastWeakFocusNode_.Upgrade());
}

/**
 * @tc.name: FocusHubFlushChildrenFocusHubTest001
 * @tc.desc: Test the function SetTabStop and IsTabStop
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubSetTabStopTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_EQ(focusHub->IsTabStop(), false);
    focusHub->SetTabStop(true);
    EXPECT_EQ(focusHub->IsTabStop(), true);
    focusHub->SetTabStop(false);
    EXPECT_EQ(focusHub->IsTabStop(), false);
}

/**
 * @tc.name: FocusHubRequestNextFocusOfKeyEnterTest001
 * @tc.desc: Test the function RequestNextFocusOfKeyEnter
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubRequestNextFocusOfKeyEnterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_EQ(focusHub->RequestNextFocusOfKeyEnter(), false);
    focusHub->SetTabStop(true);
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_EQ(focusHub->RequestNextFocusOfKeyEnter(), false);
    focusHub->SetTabStop(true);
    focusHub->focusType_ = FocusType::SCOPE;
    EXPECT_EQ(focusHub->RequestNextFocusOfKeyEnter(), true);
}

/**
 * @tc.name: FocusHubRequestNextFocusOfKeyEscTest001
 * @tc.desc: Test the function RequestNextFocusOfKeyEsc
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubRequestNextFocusOfKeyEscTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
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
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_EQ(focusHub->RequestNextFocusOfKeyEsc(), false);

    focusHub->SetTabStop(true);
    EXPECT_EQ(focusHub->RequestNextFocusOfKeyEsc(), false);

    focusHub->SetTabStop(false);
    RefPtr<EventHub> eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub1->AttachHost(child);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub1)));
    focusHub1->SetTabStop(true);
    EXPECT_EQ(focusHub1->RequestNextFocusOfKeyEsc(), false);
}

/**
 * @tc.name: FocusHubOnFocusAxisEvent001
 * @tc.desc: Test the function OnFocusKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubOnFocusAxisEvent001, TestSize.Level1)
{
    /**
     * @tc.steps1: create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps2: create eventHub and focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    FocusAxisEvent focusAxisEvent;
    focusAxisEvent.absXValue = 0.5;
    focusAxisEvent.absYValue = 0.5;
    focusAxisEvent.absZValue = 0.5;
    focusAxisEvent.absRzValue = 0.5;
    focusAxisEvent.absHat0XValue = 1;
    focusAxisEvent.absHat0YValue = 1;
    focusAxisEvent.absBrakeValue = 0.5;
    focusAxisEvent.absGasValue = 0.5;
    focusAxisEvent.sourceType = SourceType::MOUSE;
    focusAxisEvent.sourceTool = SourceTool::JOYSTICK;
    focusAxisEvent.deviceId = 10;
    std::chrono::microseconds microseconds(GetSysTimestamp());
    TimeStamp time(microseconds);
    focusAxisEvent.time = time;
    focusAxisEvent.pressedCodes.emplace_back(KeyCode::KEY_CTRL_LEFT);

    /**
     * @tc.steps3: call the function OnKeyEvent with FocusType::NODE.
     * @tc.expected: The return value of OnKeyEvent is true.
     */
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->currentFocus_ = true;
    FocusAxisEventInfo axisEventInfo({});
    auto onFocusAxisEventCallback = [&axisEventInfo](FocusAxisEventInfo& eventInfo) {
        eventInfo.SetStopPropagation(true);
        axisEventInfo = eventInfo;
    };
    focusHub->SetOnFocusAxisCallback(std::move(onFocusAxisEventCallback));
    EXPECT_TRUE(focusHub->HandleEvent(focusAxisEvent));
    EXPECT_EQ(axisEventInfo.GetAbsXValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetAbsYValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetAbsZValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetAbsRzValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetAbsHat0XValue(), 1);
    EXPECT_EQ(axisEventInfo.GetAbsHat0YValue(), 1);
    EXPECT_EQ(axisEventInfo.GetAbsBrakeValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetAbsGasValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetSourceDevice(), SourceType::MOUSE);
    EXPECT_EQ(axisEventInfo.GetSourceTool(), SourceTool::JOYSTICK);
    EXPECT_EQ(axisEventInfo.GetDeviceId(), 10);
    EXPECT_EQ(axisEventInfo.GetTimeStamp().time_since_epoch().count(), time.time_since_epoch().count());
    EXPECT_EQ(axisEventInfo.GetPressedKeyCodes().size(), 1);
    EXPECT_EQ(axisEventInfo.IsStopPropagation(), true);
}

/**
 * @tc.name: FocusHubHandleFocusNavigation001
 * @tc.desc: FocusNavigation
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubHandleFocusNavigation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    focusHub->lastWeakFocusNode_ = nullptr;
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step3. Expect the result is false.
     */
    auto result = focusHub->HandleFocusNavigation(focusEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HasCustomKeyEventDispatch001
 * @tc.desc: Test the function when event.event.eventType is UIInputEventType::KEY
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HasCustomKeyEventDispatch001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusEvent.
     */
    KeyEvent keyEvent;
    keyEvent.eventType = UIInputEventType::KEY;
    keyEvent.isPreIme = true;
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Expect the result is false.
     */
    auto result = focusHub->HasCustomKeyEventDispatch(focusEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HasCustomKeyEventDispatch002
 * @tc.desc: Test the function when event.event.eventType is not UIInputEventType::KEY, keyEvent.isPreIme is false and
 * GetOnKeyEventDispatchCallback is not null
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HasCustomKeyEventDispatch002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusEvent.
     */
    KeyEvent keyEvent;
    keyEvent.eventType = UIInputEventType::KEY;
    keyEvent.isPreIme = false;
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Set the SetOnKeyEventDispatchCallback.
     */
    auto onKeyEventDispatchCallback = [](KeyEventInfo& info) -> bool { return true; };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.steps: step4. Expect the result is true.
     */
    auto result = focusHub->HasCustomKeyEventDispatch(focusEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HasCustomKeyEventDispatch003
 * @tc.desc: Test the function when event.event.eventType is not UIInputEventType::KEY, keyEvent.isPreIme is true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HasCustomKeyEventDispatch003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusEvent.
     */
    KeyEvent keyEvent;
    keyEvent.eventType = UIInputEventType::KEY;
    keyEvent.isPreIme = true;
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Set the SetOnKeyEventDispatchCallback.
     */
    auto onKeyEventDispatchCallback = [](KeyEventInfo& info) -> bool { return true; };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.steps: step4. Expect the result is false.
     */
    auto result = focusHub->HasCustomKeyEventDispatch(focusEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleCustomEventDispatch001
 * @tc.desc: Test the function when onKeyEventDispatchCallback is true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HandleCustomEventDispatch001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusEvent.
     */
    KeyEvent keyEvent;
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Set the SetOnKeyEventDispatchCallback.
     */
    auto onKeyEventDispatchCallback = [](KeyEventInfo& info) -> bool { return true; };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.steps: step4. Expect the result is true.
     */
    auto result = focusHub->HandleCustomEventDispatch(focusEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleCustomEventDispatch002
 * @tc.desc: Test the function when onKeyEventDispatchCallback is false
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HandleCustomEventDispatch002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusEvent.
     */
    KeyEvent keyEvent;
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Set the SetOnKeyEventDispatchCallback.
     */
    auto onKeyEventDispatchCallback = [](KeyEventInfo& info) -> bool { return false; };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.steps: step4. Expect the result is true.
     */
    auto result = focusHub->HandleCustomEventDispatch(focusEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetKeyProcessingMode001
 * @tc.desc: GetKeyProcessingMode
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetKeyProcessingMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step2. Expect the result is static_cast<int32_t>(KeyProcessingMode::FOCUS_NAVIGATION).
     */
    auto result = focusHub->GetKeyProcessingMode();
    EXPECT_EQ(result, static_cast<int32_t>(KeyProcessingMode::FOCUS_NAVIGATION));
}

/**
 * @tc.name: GetKeyProcessingMode002
 * @tc.desc: GetKeyProcessingMode
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetKeyProcessingMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step1. Set keyProcessingMode_.
     */
    ASSERT_NE(focusHub->GetFrameNode(), nullptr);
    ASSERT_NE(focusHub->GetFrameNode()->GetContextRefPtr(), nullptr);
    ASSERT_NE(focusHub->GetFrameNode()->GetContextRefPtr()->GetOrCreateFocusManager(), nullptr);
    focusHub->GetFrameNode()->GetContextRefPtr()->GetOrCreateFocusManager()->keyProcessingMode_ =
        KeyProcessingMode::ANCESTOR_EVENT;

    /**
     * @tc.steps: step3. Expect the result is static_cast<int32_t>(KeyProcessingMode::ANCESTOR_EVENT).
     */
    auto result = focusHub->GetKeyProcessingMode();
    EXPECT_EQ(result, static_cast<int32_t>(KeyProcessingMode::ANCESTOR_EVENT));
}

/**
 * @tc.name: FocusHubPaintColorTest001
 * @tc.desc: Test the function GetPaintColorFromBox
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubPaintColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    Color expectPaintColor;
    Color resultPaintColor;

    /**
     * @tc.steps: step2. Test without anything.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto appTheme = context->GetTheme<AppTheme>();
    appTheme->focusColor_ = Color::GREEN;
    expectPaintColor = Color::GREEN;
    focusHub->GetPaintColorFromBox(resultPaintColor);
    EXPECT_EQ(expectPaintColor, resultPaintColor);

    /**
     * @tc.steps: step3. Test with custom paintColor.
     */
    auto testFocusPaintParams = std::make_unique<FocusPaintParam>();
    testFocusPaintParams->paintColor = Color::BLACK;
    expectPaintColor = Color::BLACK;
    focusHub->focusPaintParamsPtr_ = std::move(testFocusPaintParams);
    focusHub->GetPaintColorFromBox(resultPaintColor);
    EXPECT_EQ(expectPaintColor, resultPaintColor);

    /**
     * @tc.steps: step4. Test with custom paintColor and focusbox.
     */
    FocusBoxStyle style = { Color::RED };
    expectPaintColor = Color::RED;
    focusHub->GetFocusBox().SetStyle(style);
    focusHub->GetPaintColorFromBox(resultPaintColor);
    EXPECT_EQ(expectPaintColor, resultPaintColor);
}

/**
 * @tc.name: FocusHubIsLeafFocusScopeTest001
 * @tc.desc: Test IsLeafFocusScope returns true when focusDepend_ is SELF
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubIsLeafFocusScopeTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a page node and add a button child node.
     */
    auto pageNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::PAGE_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto button1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    button1->GetOrCreateFocusHub();
    pageNode->AddChild(button1);

    /**
     * @tc.steps2: Create EventHub and FocusHub for the page node.
     */
    RefPtr<EventHub> pageEventHub = AceType::MakeRefPtr<EventHub>();
    pageEventHub->AttachHost(pageNode);
    auto pageFocusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(pageEventHub)));

    /**
     * @tc.steps3: Set page visibility to INVISIBLE, set lastWeakFocusNode_ and focusDepend_ to SELF.
     * @tc.expected: IsLeafFocusScope returns true.
     */
    pageNode->layoutProperty_->propVisibility_ = VisibleType::INVISIBLE;
    RefPtr<FocusHub> childFocusHub = button1->GetFocusHub();
    ASSERT_NE(childFocusHub, nullptr);
    pageFocusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(childFocusHub));
    pageFocusHub->focusDepend_ = FocusDependence::SELF;
    bool isLeaf = pageFocusHub->IsLeafFocusScope();
    EXPECT_TRUE(isLeaf);
    EXPECT_EQ(pageFocusHub->lastWeakFocusNode_.Upgrade(), childFocusHub);

    /**
     * @tc.steps4: Set page visibility to VISIBLE, and simulate key event delivery.
     * @tc.expected: Key event is successfully handled.
     */
    pageNode->layoutProperty_->propVisibility_ = VisibleType::VISIBLE;
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.action = KeyAction::DOWN;
    childFocusHub->SetOnKeyEventInternal([](const KeyEvent&) { return true; });
    childFocusHub->currentFocus_ = true;
    pageFocusHub->focusType_ = FocusType::SCOPE;
    pageFocusHub->currentFocus_ = true;
    EXPECT_TRUE(pageFocusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubUpdateFocusViewTest001
 * @tc.desc: Test UpdateFocusView when the current node is not on the main tree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubUpdateFocusViewTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a FrameNode with onMainTree_ set to false.
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, pattern);
    frameNode->onMainTree_ = false;

    /**
     * @tc.steps2: Create EventHub and FocusHub, and set currentFocus_ to true.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps3: Call UpdateFocusView and expect it to return true even if not on main tree.
     * @tc.expected: UpdateFocusView returns true.
     */
    EXPECT_TRUE(focusHub->UpdateFocusView());
}

/**
 * @tc.name: FocusEventHandlerOnFocusEventTest001
 * @tc.desc: Test that OnFocusEvent returns false when the node is not focused.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusEventHandlerOnFocusEventTest001, TestSize.Level1)
{
     /**
     * @tc.steps1: Create a FrameNode and attach it to an EventHub.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);

    /**
     * @tc.steps2: Create a FocusHub with no current focus.
     */
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

     /**
     * @tc.steps3: Simulate a SPACE key event and wrap it in a FocusEvent.
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.action = KeyAction::DOWN;
    FocusEvent focusEvent(keyEvent);

     /**
     * @tc.steps4: Call OnFocusEvent when the node is not focused.
     * @tc.expected: The return value is false, indicating no handling.
     */
    EXPECT_FALSE(focusHub->OnFocusEvent(focusEvent));
}

/**
 * @tc.name: FocusHubOnClickOnlyFocusActiveTest001
 * @tc.desc: Test that onClick event only triggers when in FocusActive state.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubOnClickOnlyFocusActiveTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a column node and a button child node.
     */
    auto column = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto button1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub1->AttachHost(button1);
    column->AddChild(button1);

    /**
     * @tc.steps2: Configure the button node with focus properties and onClick callback.
     */
    auto button1Hub = button1->GetOrCreateFocusHub();
    ASSERT_NE(button1Hub, nullptr);
    button1Hub->SetFocusType(FocusType::NODE);
    button1Hub->focusable_ = true;
    button1Hub->currentFocus_ = true;
    bool clicked = false;
    button1Hub->SetOnClickCallback([&clicked](GestureEvent&) { clicked = true; });

    /**
     * @tc.steps3: Simulate a SPACE key down event.
     */
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;

    /**
     * @tc.steps4: Set up focusManager and themeManager, disable focusHandleClick.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    EXPECT_NE(focusManager, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto appTheme = pipeline->GetTheme<AppTheme>();
    appTheme->focusHandleClick_ = false;
    EXPECT_FALSE(appTheme->NeedFocusHandleClick());

    /**
     * @tc.steps5: Set focus state to inactive, expect onClick not triggered.
     * @tc.expected: HandleKeyEvent returns false, clicked is false.
     */
    focusManager->SetIsFocusActive(false);
    EXPECT_FALSE(pipeline->GetIsFocusActive());
    clicked = false;
    EXPECT_FALSE(button1Hub->HandleKeyEvent(keyEvent, FocusIntension::SPACE));
    EXPECT_FALSE(clicked);

    /**
     * @tc.steps6: Set focus state to active, expect onClick triggered.
     * @tc.expected: HandleKeyEvent returns true, clicked is true.
     */
    focusManager->SetIsFocusActive(true);
    EXPECT_TRUE(pipeline->GetIsFocusActive());
    clicked = false;
    EXPECT_TRUE(button1Hub->HandleKeyEvent(keyEvent, FocusIntension::SPACE));
    EXPECT_TRUE(clicked);
}

/**
 * @tc.name: FocusHubFixRefocusTest001
 * @tc.desc: Test refocus logic and ensure Enter key triggers next focus with correct priority.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubFixRefocusTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a frame node and attach it to an EventHub and FocusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: Set focusHub to SCOPE type, enable tab stop, set focusDepend_ to SELF, isSwitchByEnter_ to true.
     * @tc.expected: IsLeafFocusScope returns false, focusDepend_ updated to AUTO.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    focusHub->SetTabStop(true);
    focusHub->focusDepend_ = FocusDependence::SELF;
    focusHub->isSwitchByEnter_ = true;
    EXPECT_FALSE(focusHub->IsLeafFocusScope());
    EXPECT_EQ(focusHub->focusDepend_, FocusDependence::AUTO);

    /**
     * @tc.steps3: Add a focusable child node to the frame, and set focusHub as currently focused.
     */
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps4: Request focus switch via Enter key.
     * @tc.expected: Child node gains focus successfully.
     */
    EXPECT_TRUE(focusHub->RequestNextFocusOfKeyEnter());
    EXPECT_TRUE(child->GetFocusHub()->IsCurrentFocus());

    /**
     * @tc.steps5: Call OnFocusScope again and verify no redundant focus callback is triggered.
     * @tc.expected: Focus callback count remains 0.
     */
    int32_t callbackCount = 0;
    focusHub->SetOnFocusCallback([&callbackCount]() { callbackCount++; });
    focusHub->OnFocusScope(true);
    EXPECT_EQ(callbackCount, 0);
}

/**
 * @tc.name: FocusHubCalculateRect001
 * @tc.desc: Test that CalculateRect does not return false when childHub is not null.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubCalculateRect001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a FrameNode and attach it to EventHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);

    /**
     * @tc.steps2: Create a parent FocusHub and a child FocusHub sharing the same EventHub.
     */
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    RefPtr<FocusHub> childHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps3: Call CalculateRect with a valid childHub.
     * @tc.expected: Function returns true, indicating rect calculation continues instead of returning false on check.
     */
    RectF rect;
    EXPECT_TRUE(focusHub->CalculateRect(childHub, rect));
}

/**
 * @tc.name: FocusHubPaintFocusStateWithMarginTest001
 * @tc.desc: Test that margin property in focusBox style takes effect when focus style is CUSTOM_REGION.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubPaintFocusStateWithMarginTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a FrameNode and bind it to EventHub and FocusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: Set up pipeline context, theme manager, and get AppTheme.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    EXPECT_NE(focusManager, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto appTheme = pipeline->GetTheme<AppTheme>();

    /**
     * @tc.steps3: Set focus style to CUSTOM_REGION and assign boxStyle with margin.
     */
    focusHub->focusStyleType_ = FocusStyleType::CUSTOM_REGION;
    focusHub->currentFocus_ = true;

    FocusBoxStyle boxStyle;
    boxStyle.margin = Dimension(20.0_vp);
    boxStyle.strokeColor = Color::RED;
    boxStyle.strokeWidth = Dimension(5.0_vp);
    focusHub->box_.paintStyle_ = boxStyle;

    /**
     * @tc.steps4: Activate focus and call PaintInnerFocusState.
     * @tc.expected: Function returns true, indicating margin takes effect successfully.
     */
    focusManager->SetIsFocusActive(true);
    RoundRect rect;
    bool result = focusHub->PaintInnerFocusState(rect, true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubClearFocusStateTest001
 * @tc.desc: Test that ClearFocusState properly triggers or skips callback depending on input flags.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubClearFocusStateTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a FrameNode and attach EventHub and FocusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: Register a focus clear callback to validate invocation.
     */
    bool callbackCalled = false;
    focusHub->SetOnClearFocusStateInternal([&callbackCalled]() { callbackCalled = true; });

    /**
     * @tc.steps3: Test ClearFocusState(true, true), should trigger callback.
     * @tc.expected: callbackCalled is true.
     */
    callbackCalled = false;
    focusHub->ClearFocusState(true, true);
    EXPECT_TRUE(callbackCalled);

    /**
     * @tc.steps4: Test ClearFocusState(true, false), should skip callback.
     * @tc.expected: callbackCalled is false.
     */
    callbackCalled = false;
    focusHub->ClearFocusState(true, false);
    EXPECT_FALSE(callbackCalled);

    /**
     * @tc.steps5: Test ClearFocusState(false, true), should trigger callback.
     * @tc.expected: callbackCalled is true.
     */
    callbackCalled = false;
    focusHub->ClearFocusState(false, true);
    EXPECT_TRUE(callbackCalled);

    /**
     * @tc.steps6: Test ClearFocusState(false, false), should skip callback.
     * @tc.expected: callbackCalled is false.
     */
    callbackCalled = false;
    focusHub->ClearFocusState(false, false);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: FocusEventGetFocusIntensionTest001
 * @tc.desc: Test that various key combinations correctly map to FocusIntension values.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusEventGetFocusIntensionTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Prepare a key event with type KEY, action DOWN, not pre-IME.
     */
    KeyEvent keyEvent;
    keyEvent.eventType = UIInputEventType::KEY;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.isPreIme = false;
    NonPointerEvent& event = keyEvent;

    /**
     * @tc.steps2: Test plain UP key without modifiers.
     * @tc.expected: FocusIntension::UP
     */
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    keyEvent.pressedCodes.clear();
    EXPECT_EQ(FocusEvent::GetFocusIntension(event), FocusIntension::UP);

    /**
     * @tc.steps3: Test UP key with Shift modifier.
     * @tc.expected: FocusIntension::UP
     */
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };
    EXPECT_EQ(FocusEvent::GetFocusIntension(event), FocusIntension::UP);

    /**
     * @tc.steps4: Test DOWN key with Shift modifier.
     * @tc.expected: FocusIntension::DOWN
     */
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };
    EXPECT_EQ(FocusEvent::GetFocusIntension(event), FocusIntension::DOWN);

    /**
     * @tc.steps5: Test LEFT key with Shift modifier.
     * @tc.expected: FocusIntension::LEFT
     */
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };
    EXPECT_EQ(FocusEvent::GetFocusIntension(event), FocusIntension::LEFT);

    /**
     * @tc.steps6: Test RIGHT key with Shift modifier.
     * @tc.expected: FocusIntension::RIGHT
     */
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };
    EXPECT_EQ(FocusEvent::GetFocusIntension(event), FocusIntension::RIGHT);

    /**
     * @tc.steps7: Test Shift + Tab key combination.
     * @tc.expected: FocusIntension::SHIFT_TAB
     */
    keyEvent.code = KeyCode::KEY_TAB;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB };
    EXPECT_EQ(FocusEvent::GetFocusIntension(keyEvent), FocusIntension::SHIFT_TAB);
}

/**
 * @tc.name: LostFocusToTabstopTest001
 * @tc.desc: Test LostFocusToTabstop.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, LostFocusToTabstopTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: CreateTree.
     */
    auto context = MockPipelineContext::GetCurrent();
    auto focusManager = context->GetOrCreateFocusManager();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    pageNode->onMainTree_ = true;
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    context->rootNode_->AddChild(pageNode);
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto column2 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto column3 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    column->onMainTree_ = true;
    column2->onMainTree_ = true;
    column3->onMainTree_ = true;
    auto columnFocusHub = column->GetOrCreateFocusHub();
    auto columnFocusHub2 = column2->GetOrCreateFocusHub();
    auto columnFocusHub3 = column3->GetOrCreateFocusHub();
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->onMainTree_ = true;
    auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
    pageNode->AddChild(column);
    column->AddChild(column2);
    column2->AddChild(column3);
    column3->AddChild(buttonNode);
    pagePattern->FocusViewShow();
    context->FlushFocusView();
    pagePattern->TriggerFocusMove();
    EXPECT_EQ(buttonFocusHub->IsCurrentFocus(), true);

    /**
     * @tc.steps2: SetTabStop and test RequestNextFocusOfKeyEsc.
     */
    columnFocusHub->SetTabStop(true);
    columnFocusHub2->SetTabStop(true);
    buttonFocusHub->RequestNextFocusOfKeyEsc();
    EXPECT_EQ(columnFocusHub2->IsCurrentFocus(), true);
    EXPECT_EQ(buttonFocusHub->IsCurrentFocus(), false);
    EXPECT_EQ(columnFocusHub3->IsCurrentFocus(), false);
    columnFocusHub2->RequestNextFocusOfKeyEsc();
    EXPECT_EQ(columnFocusHub->IsCurrentFocus(), true);
    EXPECT_EQ(columnFocusHub2->IsCurrentFocus(), false);
    columnFocusHub3->RequestNextFocusOfKeyEsc();
    EXPECT_EQ(columnFocusHub->IsCurrentFocus(), true);
}
} // namespace OHOS::Ace::NG
