/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <cstdint>
#include <unistd.h>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double GESTURE_EVENT_PROPERTY_VALUE = 10.0;
constexpr int32_t CLICK_TEST_RESULT_SIZE_1 = 1;
constexpr int32_t CLICK_TEST_RESULT_SIZE_2 = 2;
constexpr int32_t CLICK_TEST_RESULT_SIZE_3 = 3;
constexpr int32_t CLICK_TEST_RESULT_SIZE_0 = 0;
constexpr uint32_t CLICK_EVENTS_SIZE = 1;
constexpr uint32_t CLICK_EVENTS_SIZE_2 = 2;
const TouchRestrict CLICK_TOUCH_RESTRICT = { TouchRestrict::CLICK };
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 400.0f;
const std::string RESULT_SUCCESS = "success";
const OffsetF COORDINATE_OFFSET(WIDTH, HEIGHT);
} // namespace

class ClickEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void ClickEventTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "ClickEventTestNg SetUpTestCase";
}

void ClickEventTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "ClickEventTestNg TearDownTestCase";
}

void ClickEventTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void ClickEventTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ClickEventTest001
 * @tc.desc: Create ClickEvent and execute its functions.
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventTestNg, ClickEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventFunc as the arguments of the construction of ClickEvent.
     * @tc.expected: clickEvent is not nullptr.
     */
    double unknownPropertyValue = 0.0;
    GestureEventFunc callback = [&unknownPropertyValue](GestureEvent& info) { unknownPropertyValue = info.GetScale(); };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(callback));
    EXPECT_NE(clickEvent, nullptr);

    /**
     * @tc.steps: step2. Get callback function and execute.
     * @tc.expected: Execute ActionUpdateEvent which unknownPropertyValue is assigned in.
     */
    GestureEvent info = GestureEvent();
    info.SetScale(GESTURE_EVENT_PROPERTY_VALUE);
    clickEvent->GetGestureEventFunc()(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
}

/**
 * @tc.name: ClickEventActuatorTest002
 * @tc.desc: Create ClickEventActuator and replace, add and remove clickEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventTestNg, ClickEventActuatorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ClickEventActuator clickEventActuator = ClickEventActuator(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));

    /**
     * @tc.steps: step2. Replace ClickEvent when userCallback_ is not nullptr.
     * @tc.expected: userCallback_ will be reset and Make an new instance.
     */
    GestureEventFunc callback1 = [](GestureEvent& info) {};
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(callback1));
    clickEventActuator.userCallback_ = clickEvent;
    GestureEventFunc callback2 = [](GestureEvent& info) {};
    clickEventActuator.SetUserCallback(std::move(callback2));
    EXPECT_NE(clickEventActuator.userCallback_, nullptr);

    /**
     * @tc.steps: step3. Add click event when clickEvents_ is empty.
     * @tc.expected: Add click event to the list of clickEvents.
     */
    clickEventActuator.AddClickEvent(clickEvent);
    EXPECT_EQ(clickEventActuator.clickEvents_.size(), CLICK_EVENTS_SIZE);

    /**
     * @tc.steps: step4. Add click event when clickEvents_ is not empty.
     * @tc.expected: Add click event to the list of clickEvents when it is not found in the list.
     */
    GestureEventFunc callback3 = [](GestureEvent& info) {};
    auto clickEvent2 = AceType::MakeRefPtr<ClickEvent>(std::move(callback3));
    clickEventActuator.AddClickEvent(clickEvent2);
    EXPECT_EQ(clickEventActuator.clickEvents_.size(), CLICK_EVENTS_SIZE_2);

    /**
     * @tc.steps: step5. Remove click event.
     * @tc.expected: The list of click event size will minus one.
     */
    clickEventActuator.RemoveClickEvent(clickEvent2);
    EXPECT_EQ(clickEventActuator.clickEvents_.size(), CLICK_EVENTS_SIZE);
}

/**
 * @tc.name: ClickEventActuatorTest003
 * @tc.desc: Create ClickEventActuator and invoke OnCollectTouchTarget.
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventTestNg, ClickEventActuatorTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ClickEventActuator clickEventActuator = ClickEventActuator(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));

    /**
     * @tc.steps: step2. Invoke OnCollectTouchTarget when clickEvents_ is empty and userCallback_ is nullptr.
     * @tc.expected: OnCollectTouchTarget will return directly and finalResult is empty.
     */
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    EXPECT_NE(getEventTargetImpl, nullptr);
    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    clickEventActuator.OnCollectTouchTarget(
        COORDINATE_OFFSET, CLICK_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    EXPECT_TRUE(finalResult.empty());

    /**
     * @tc.steps: step3. Invoke OnCollectTouchTarget when clickEvents_ is empty and userCallback_ and
     * jsFrameNodeCallback_ are both nullptr.
     * @tc.expected: OnCollectTouchTarget will return directly and finalResult is empty.
     */

    clickEventActuator.jsFrameNodeCallback_ = nullptr;
    clickEventActuator.OnCollectTouchTarget(
        COORDINATE_OFFSET, CLICK_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    EXPECT_TRUE(finalResult.empty());

    /**
     * @tc.steps: step4. Invoke OnCollectTouchTarget when clickEvents_ is empty and userCallback_ is nullptr and
     * jsFrameNodeCallback_ is not nullptr.
     * @tc.expected: OnCollectTouchTarget can't return directly.
     */
    getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    EXPECT_NE(getEventTargetImpl, nullptr);
    GestureEventFunc callback = [](GestureEvent& info) {};
    clickEventActuator.jsFrameNodeCallback_ = AceType::MakeRefPtr<ClickEvent>(std::move(callback));
    clickEventActuator.OnCollectTouchTarget(
        COORDINATE_OFFSET, CLICK_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    EXPECT_FALSE(finalResult.empty());

    /**
     * @tc.steps: step5. Invoke OnCollectTouchTarget when clickEvents_ is not empty but userCallback_ is nullptr.
     * @tc.expected: Add clickRecognizer_ to finalResult, and it's size is equal 2.
     */
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(callback));
    clickEventActuator.AddClickEvent(clickEvent);
    clickEventActuator.AddClickEvent(nullptr);
    clickEventActuator.OnCollectTouchTarget(
        COORDINATE_OFFSET, CLICK_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    EXPECT_EQ(finalResult.size(), CLICK_TEST_RESULT_SIZE_2);

    /**
     * @tc.steps: step6. Execute onAction_ when clickEvents_ has nullptr and userCallback_ and
     * onAccessibilityEventFunc_ are nullptr.
     * @tc.expected: Add clickRecognizer_ to finalResult, and it's size is equal 1.
     */
    GestureEvent info = GestureEvent();
    (*clickEventActuator.clickRecognizer_->onAction_)(info);

    /**
     * @tc.steps: step7. Invoke OnCollectTouchTarget when userCallback_ and clickEvents_ is not empty but
     * clickRecognizer_ is nullptr.
     * @tc.expected: Add clickRecognizer_ to finalResult, and it's size is equal 3.
     */
    clickEventActuator.clickRecognizer_ = nullptr;
    clickEventActuator.userCallback_ = clickEvent;
    const OnAccessibilityEventFunc onAccessibility = [](AccessibilityEventType type) {};
    clickEventActuator.SetOnAccessibility(onAccessibility);
    clickEventActuator.OnCollectTouchTarget(
        COORDINATE_OFFSET, CLICK_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    EXPECT_EQ(finalResult.size(), CLICK_TEST_RESULT_SIZE_3);

    /**
     * @tc.steps: step8. Execute onAction_ when clickEvents_ has nullptr and userCallback_ and
     * onAccessibilityEventFunc_ are not nullptr.
     */
    (*clickEventActuator.clickRecognizer_->onAction_)(info);
}

/**
 * @tc.name: ClickEventActuatorTest004
 * @tc.desc: test clear user callback.
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventTestNg, ClickEventActuatorTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ClickEventActuator clickEventActuator = ClickEventActuator(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));

    /**
     * @tc.steps: step2. Invoke OnCollectTouchTarget when clickEvents_ is empty and userCallback_ is not nullptr.
     * @tc.expected: OnCollectTouchTarget will return directly and finalResult is 1.
     */
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    EXPECT_NE(getEventTargetImpl, nullptr);

    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    std::string result;
    GestureEventFunc callback = [&result](GestureEvent& info) { result = RESULT_SUCCESS; };

    clickEventActuator.SetUserCallback(std::move(callback));
    clickEventActuator.OnCollectTouchTarget(
        COORDINATE_OFFSET, CLICK_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    EXPECT_NE(clickEventActuator.userCallback_->callback_, nullptr);

    GestureEvent info = GestureEvent();
    clickEventActuator.userCallback_->callback_(info);
    EXPECT_EQ(result, RESULT_SUCCESS);
    EXPECT_EQ(finalResult.size(), CLICK_TEST_RESULT_SIZE_1);

    clickEventActuator.ClearUserCallback();
    clickEventActuator.OnCollectTouchTarget(
        COORDINATE_OFFSET, CLICK_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    EXPECT_EQ(clickEventActuator.userCallback_, nullptr);
    EXPECT_EQ(finalResult.size(), CLICK_TEST_RESULT_SIZE_1);
}

/**
 * @tc.name: ClickEventActuatorTest005
 * @tc.desc: test user callback and clickevent are different.
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventTestNg, ClickEventActuatorTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ClickEventActuator clickEventActuator = ClickEventActuator(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));

    /**
     * @tc.steps: step2. test clear callback and add event.
     * @tc.expected: Add clickRecognizer_ to finalResult, and it's size is equal 1.
     */
    auto getEventTargetImpl = eventHub->CreateGetEventTargetImpl();
    EXPECT_NE(getEventTargetImpl, nullptr);
    clickEventActuator.ClearUserCallback();

    GestureEventFunc callback = [](GestureEvent& info) {};
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(callback));
    clickEventActuator.AddClickEvent(clickEvent);

    TouchTestResult finalResult;
    ResponseLinkResult responseLinkResult;
    clickEventActuator.OnCollectTouchTarget(
        COORDINATE_OFFSET, CLICK_TOUCH_RESTRICT, getEventTargetImpl, finalResult, responseLinkResult);
    EXPECT_EQ(finalResult.size(), CLICK_TEST_RESULT_SIZE_1);

    /**
     * @tc.steps: step3. test clear callback again.
     * @tc.expected: Add clickRecognizer_ to finalResult, and it's size is equal 1.
     */
    TouchTestResult finalResultAfterClear;
    clickEventActuator.ClearUserCallback();
    clickEventActuator.OnCollectTouchTarget(
        COORDINATE_OFFSET, CLICK_TOUCH_RESTRICT, getEventTargetImpl, finalResultAfterClear, responseLinkResult);
    EXPECT_EQ(finalResultAfterClear.size(), CLICK_TEST_RESULT_SIZE_1);

    /**
     * @tc.steps: step4. test clear event again.
     * @tc.expected: callback and event are null, and it's size is equal 0.
     */
    clickEventActuator.RemoveClickEvent(clickEvent);
    TouchTestResult finalResultAfterClearEvent;
    clickEventActuator.OnCollectTouchTarget(
        COORDINATE_OFFSET, CLICK_TOUCH_RESTRICT, getEventTargetImpl, finalResultAfterClearEvent, responseLinkResult);
    EXPECT_EQ(finalResultAfterClearEvent.size(), CLICK_TEST_RESULT_SIZE_0);
}
/**
 * @tc.name: ClickEventActuatorTest006
 * @tc.desc: test AddClickAfterEvent and ClearClickAfterEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ClickEventTestNg, ClickEventActuatorTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ClickEventActuator clickEventActuator = ClickEventActuator(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));

    /**
     * @tc.steps: step2. Replace ClickEvent when userCallback_ is not nullptr.
     * @tc.expected: userCallback_ will be reset and Make an new instance.
     */
    GestureEventFunc callback = [](GestureEvent& info) {};
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(callback));
    clickEventActuator.AddClickAfterEvent(clickEvent);
    EXPECT_NE(clickEventActuator.clickAfterEvents_, nullptr);

    clickEventActuator.ClearClickAfterEvent();
    EXPECT_EQ(clickEventActuator.clickAfterEvents_, nullptr);
}
} // namespace OHOS::Ace::NG
