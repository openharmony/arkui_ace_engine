/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <unistd.h>

#include "gtest/gtest.h"

#define private public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double GESTURE_EVENT_PROPERTY_VALUE = 10.0;
const TouchRestrict LONG_PRESS_TOUCH_RESTRICT = { TouchRestrict::CLICK };
constexpr uint32_t LONG_PRESS_TEST_RESULT_SIZE = 0;
constexpr uint32_t LONG_PRESS_TEST_RESULT_SIZE_1 = 1;
constexpr uint32_t LONG_PRESS_TEST_RESULT_SIZE_2 = 2;
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 400.0f;
const OffsetF COORDINATE_OFFSET(WIDTH, HEIGHT);
} // namespace

class LongPressEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void LongPressEventTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "LongPressEventTestNg SetUpTestCase";
}

void LongPressEventTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "LongPressEventTestNg TearDownTestCase";
}

void LongPressEventTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void LongPressEventTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: LongPressEventTest001
 * @tc.desc: Create LongPressEvent and execute its callback functions.
 * @tc.type: FUNC
 */
HWTEST_F(LongPressEventTestNg, LongPressEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LongPressEvent.
     * @tc.expected: longPressEvent is not nullptr.
     */
    double unknownPropertyValue = 0.0;
    GestureEventFunc callback = [&unknownPropertyValue](GestureEvent& info) { unknownPropertyValue = info.GetScale(); };
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(std::move(callback));
    EXPECT_NE(longPressEvent, nullptr);

    /**
     * @tc.steps: step2. Get and execute LongPressEvent callback function.
     * @tc.expected: Execute callback where unknownPropertyValue is assigned in.
     */
    GestureEvent info = GestureEvent();
    info.SetScale(GESTURE_EVENT_PROPERTY_VALUE);
    longPressEvent->GetGestureEventFunc()(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
}

/**
 * @tc.name: LongPressEventActuatorTest002
 * @tc.desc: Create LongPressEvent and execute its callback functions.
 * @tc.type: FUNC
 */
HWTEST_F(LongPressEventTestNg, LongPressEventActuatorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create longPressEventActuator.
     * @tc.expected: longPressEventActuator is not nullptr.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto longPressEventActuator =
        AceType::MakeRefPtr<LongPressEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)));
    EXPECT_NE(longPressEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke OnCollectTouchTarget when longPressEvent_ is nullptr.
     * @tc. OnCollectTouchTarget return directly
     */
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    longPressEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, LONG_PRESS_TOUCH_RESTRICT, eventHub->CreateGetEventTargetImpl(), result, responseLinkResult);
    EXPECT_EQ(result.size(), LONG_PRESS_TEST_RESULT_SIZE);
    EXPECT_EQ(longPressEventActuator->longPressRecognizer_, nullptr);
    /**
     * @tc.steps: step2.1. Execute callback when longPressEvent_ and onAccessibilityEventFunc_ are nullptr.
     */
    GestureEvent info;
    longPressEventActuator->GetGestureEventFunc()(info);

    /**
     * @tc.steps: step3. Create LongPressEvent.
     * @tc.expected: longPressEvent is not nullptr.
     */
    GestureEventFunc callback = [](GestureEvent& info) {};
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(std::move(callback));
    EXPECT_NE(longPressEvent, nullptr);

    /**
     * @tc.steps: step4. Set LongPressEvent with default value.
     * @tc.expected: Properties were assigned with default value.
     */
    longPressEventActuator->SetLongPressEvent(longPressEvent);
    EXPECT_EQ(longPressEventActuator->isForDrag_, false);
    EXPECT_EQ(longPressEventActuator->isDisableMouseLeft_, false);
    EXPECT_NE(longPressEvent, nullptr);
    /**
     * @tc.steps: step5. Set LongPressEvent.
     * @tc.expected: Properties were assigned with correct value.
     */
    longPressEventActuator->SetLongPressEvent(longPressEvent, true, true);
    EXPECT_EQ(longPressEventActuator->isForDrag_, true);
    EXPECT_EQ(longPressEventActuator->isDisableMouseLeft_, true);

    /**
     * @tc.steps: step6. Invoke OnCollectTouchTarget when longPressEvent_ is not nullptr but longPressRecognizer_ is
     * nullptr.
     * @tc.expected:  TouchTestResult size has been increased one.
     */
    EXPECT_EQ(longPressEventActuator->longPressRecognizer_, nullptr);
    longPressEventActuator->longPressRecognizer_ = nullptr;
    longPressEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, LONG_PRESS_TOUCH_RESTRICT, eventHub->CreateGetEventTargetImpl(), result, responseLinkResult);
    EXPECT_EQ(longPressEventActuator->longPressRecognizer_->GetCoordinateOffset(), Offset(WIDTH, HEIGHT));
    EXPECT_EQ(result.size(), LONG_PRESS_TEST_RESULT_SIZE_1);

    // coverage longPressRecognizer_ is true
    longPressEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, LONG_PRESS_TOUCH_RESTRICT, eventHub->CreateGetEventTargetImpl(), result, responseLinkResult);
    EXPECT_EQ(longPressEventActuator->longPressRecognizer_->GetCoordinateOffset(), Offset(WIDTH, HEIGHT));
    EXPECT_EQ(result.size(), LONG_PRESS_TEST_RESULT_SIZE_2);

    /**
     * @tc.steps: step6.1. Execute callback when longPressEvent_ and onAccessibilityEventFunc_ are not nullptr.
     */
    const OnAccessibilityEventFunc onAccessibility = [](AccessibilityEventType type) {};
    longPressEventActuator->SetOnAccessibility(onAccessibility);
    longPressEventActuator->GetGestureEventFunc()(info);
}
} // namespace OHOS::Ace::NG
