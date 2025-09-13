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
    };
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
     * @tc.steps: step3. Call ReplaceTouchDelegate.
     * @tc.expected: touchDelegatesMap_ is not empty and size is 1.
     */
    eventManager->ReplaceTouchDelegate(TOUCH_ID, delegate);
    EXPECT_FALSE(eventManager->touchDelegatesMap_.empty());
    EXPECT_EQ(eventManager->touchDelegatesMap_[TOUCH_ID].size(), 1);

    /**
     * @tc.steps: step4. Call ReplaceTouchDelegate when eventManager->touchDelegatesMap_ is empty.
     * @tc.expected: touchDelegatesMap_ is not empty and size is 1.
     */
    eventManager->UnregisterTouchDelegate(TOUCH_ID);
    EXPECT_TRUE(eventManager->touchDelegatesMap_.empty());
    eventManager->ReplaceTouchDelegate(TOUCH_ID, delegate);
    EXPECT_FALSE(eventManager->touchDelegatesMap_.empty());
    EXPECT_EQ(eventManager->touchDelegatesMap_[TOUCH_ID].size(), 1);

    /**
     * @tc.steps: step5. Call ReplaceTouchDelegate when eventManager->touchDelegatesMap_[TOUCH_ID] is empty.
     * @tc.expected: touchDelegatesMap_ is not empty and size is 1.
     */
    eventManager->touchDelegatesMap_[TOUCH_ID].clear();
    EXPECT_FALSE(eventManager->touchDelegatesMap_.empty());
    EXPECT_TRUE(eventManager->touchDelegatesMap_[TOUCH_ID].empty());
    eventManager->ReplaceTouchDelegate(TOUCH_ID, delegate);
    EXPECT_FALSE(eventManager->touchDelegatesMap_.empty());
    EXPECT_EQ(eventManager->touchDelegatesMap_[TOUCH_ID].size(), 1);
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
    EXPECT_TRUE(eventManager->touchTestResults_.empty());
 
    event.type = TouchType::DOWN;
    eventManager->UpdateInfoWhenFinishDispatch(event, true);
    EXPECT_TRUE(eventManager->touchTestResults_.empty());
 
    event.type = TouchType::CANCEL;
    eventManager->UpdateInfoWhenFinishDispatch(event, true);
    EXPECT_TRUE(eventManager->touchTestResults_.empty());
 
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
} // namespace OHOS::Ace::NG