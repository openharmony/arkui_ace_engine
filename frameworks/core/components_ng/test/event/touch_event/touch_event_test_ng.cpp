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

#include <clocale>
#include <cmath>
#include <cstdint>
#include <unistd.h>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr bool STOP_PROPAGATION_VALUE = true;
constexpr int32_t TOUCH_TEST_RESULT_SIZE_1 = 1;
constexpr uint32_t TOUCH_EVENTS_SIZE = 1;
constexpr uint32_t TOUCH_EVENTS_SIZE_2 = 2;
const TouchRestrict Touch_TOUCH_RESTRICT = { TouchRestrict::LONG_PRESS };
constexpr float TILT_X_VALUE = 400.0f;
constexpr float TILT_Y_VALUE = 400.0f;
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 400.0f;
const OffsetF COORDINATE_OFFSET(WIDTH, HEIGHT);
const std::string TOUCH_EVENT_INFO_TYPE = "onTouchDown";
const std::vector<TouchPoint> POINTERS = { TouchPoint(), TouchPoint(), TouchPoint() };
const std::vector<TouchPoint> POINTERS_2 = { { .tiltX = TILT_X_VALUE, .tiltY = TILT_Y_VALUE } };
} // namespace

class TouchEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void TouchEventTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "TouchEventTestNg SetUpTestCase";
}

void TouchEventTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "TouchEventTestNg TearDownTestCase";
}

void TouchEventTestNg::SetUp()
{
    MockPipelineBase::SetUp();
}

void TouchEventTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: TouchEventCreateTest001
 * @tc.desc: Create TouchEvent and execute its callback functions.
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventTestNg, TouchEventCreateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TouchEvent.
     */
    std::string unknownType;
    TouchEventFunc callback = [&unknownType](TouchEventInfo& info) { unknownType = info.GetType(); };
    const TouchEventImpl touchEvent = TouchEventImpl(std::move(callback));

    /**
     * @tc.steps: step2. Get and execute TouchEvent callback function.
     * @tc.expected: Execute callback where unknownPropertyValue is assigned in.
     */
    TouchEventInfo info(TOUCH_EVENT_INFO_TYPE);
    touchEvent(info);
    EXPECT_EQ(unknownType, TOUCH_EVENT_INFO_TYPE);
}

/**
 * @tc.name: TouchEventActuatorTest002
 * @tc.desc: Create TouchEventActuator and replace, add and remove touchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventTestNg, TouchEventActuatorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TouchEventActuator.
     * @tc.expected: touchEventActuator is not nullptr.
     */
    auto touchEventActuator = AceType::MakeRefPtr<TouchEventActuator>();
    EXPECT_NE(touchEventActuator, nullptr);

    /**
     * @tc.steps: step2. Replace TouchEventFunc when userCallback_ is nullptr.
     * @tc.expected: userCallback_ will be reset and Make an new instance.
     */
    const TouchEventFunc callback = [](TouchEventInfo& info) {};
    TouchEventFunc callback1 = callback;
    touchEventActuator->ReplaceTouchEvent(std::move(callback1));
    EXPECT_NE(touchEventActuator->userCallback_, nullptr);

    /**
     * @tc.steps: step3. Add touch event when touchEvents_ is empty.
     * @tc.expected: Add touch event to the list of touchEvents_.
     */
    TouchEventFunc callback2 = callback;
    auto touchEvent2 = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback2));
    touchEventActuator->AddTouchEvent(touchEvent2);
    EXPECT_EQ(touchEventActuator->touchEvents_.size(), TOUCH_EVENTS_SIZE);

    /**
     * @tc.steps: step4. Add touch event when touchEvents_ is not empty.
     * @tc.expected: Add touch event to the list of touchEvents_ where it is not found in.
     */
    TouchEventFunc callback3 = callback;
    auto touchEvent3 = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback3));
    touchEventActuator->AddTouchEvent(touchEvent3);
    EXPECT_EQ(touchEventActuator->touchEvents_.size(), TOUCH_EVENTS_SIZE_2);

    /**
     * @tc.steps: step5. Remove touch event.
     * @tc.expected: The list of touch event size will minus one.
     */
    touchEventActuator->RemoveTouchEvent(touchEvent3);
    EXPECT_EQ(touchEventActuator->touchEvents_.size(), TOUCH_EVENTS_SIZE);
}

/**
 * @tc.name: TouchEventActuatorOnCollectTouchTargetTest003
 * @tc.desc: Create TouchEventActuator and Invoke OnCollectTouchTarget event.
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventTestNg, TouchEventActuatorOnCollectTouchTargetTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TouchEventActuator.
     * @tc.expected: touchEventActuator is not nullptr.
     */
    auto touchEventActuator = AceType::MakeRefPtr<TouchEventActuator>();
    EXPECT_NE(touchEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke OnCollectTouchTarget.
     * @tc.expected: TouchTestResult size has been increased one.
     */
    TouchTestResult result;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    touchEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, Touch_TOUCH_RESTRICT, eventHub->CreateGetEventTargetImpl(), result);

    EXPECT_EQ(touchEventActuator->coordinateOffset_, Offset(WIDTH, HEIGHT));
    EXPECT_EQ(result.size(), TOUCH_TEST_RESULT_SIZE_1);
}

/**
 * @tc.name: TouchEventActuatorHandleAndDispatchTest004
 * @tc.desc: Create TouchEventActuator and replace, add and remove touchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventTestNg, TouchEventActuatorHandleAndDispatchTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TouchEventActuator.
     * @tc.expected: touchEventActuator is not nullptr.
     */
    auto touchEventActuator = AceType::MakeRefPtr<TouchEventActuator>();
    EXPECT_NE(touchEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke DispatchEvent.
     * @tc.expected: TouchTestResult size has been increased one.
     */
    const TouchEvent touchEvent { .tiltX = TILT_X_VALUE, .tiltY = TILT_Y_VALUE, .pointers = POINTERS };
    EXPECT_TRUE(touchEventActuator->DispatchEvent(touchEvent));

    /**
     * @tc.steps: step3. Invoke HandleEvent when touchEvents_ and userCallback_ is empty.
     * @tc.expected: HandleEvent will return true directly.
     */
    EXPECT_TRUE(touchEventActuator->HandleEvent(touchEvent));

    /**
     * @tc.steps: step4. Invoke ReplaceTouchEvent to initialize userCallback_.
     */
    double unknownTiltX = 0.0;
    const TouchEventFunc callback = [&unknownTiltX](
                                        TouchEventInfo& info) { unknownTiltX = info.GetTiltX().value_or(0.0); };
    TouchEventFunc callback1 = callback;
    touchEventActuator->ReplaceTouchEvent(std::move(callback1));
    EXPECT_NE(touchEventActuator->userCallback_, nullptr);

    /**
     * @tc.steps: step5. Invoke AddTouchEvent to add touch event to touchEvents_.
     */
    TouchEventFunc callback2 = callback;
    auto touchEvent2 = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback2));
    touchEventActuator->AddTouchEvent(touchEvent2);
    touchEventActuator->AddTouchEvent(nullptr);
    EXPECT_EQ(touchEventActuator->touchEvents_.size(), TOUCH_EVENTS_SIZE_2);

    /**
     * @tc.steps: step6. Invoke HandleEvent when touchEvents_ and userCallback_ is not empty.
     * @tc.expected: HandleEvent will execute touchEvents_ and userCallback_ event where unknownTiltX was assigned the
     * touchPoint value, and the function return true.
     */
    EXPECT_TRUE(touchEventActuator->HandleEvent(touchEvent));
    EXPECT_EQ(unknownTiltX, TILT_X_VALUE);

    /**
     * @tc.steps: step7. Invoke HandleEvent when touchEvents_ and userCallback_ is not empty but the event is
     * stopPropagation_ is true.
     * @tc.expected: HandleEvent return false;
     */
    TouchEventFunc callback3 = [](TouchEventInfo& info) { info.SetStopPropagation(STOP_PROPAGATION_VALUE); };
    touchEventActuator->ReplaceTouchEvent(std::move(callback3));
    EXPECT_FALSE(touchEventActuator->HandleEvent(touchEvent));

    /**
     * @tc.steps: step8. Invoke HandleEvent when touchEvents_ has nullptr event and userCallback_ is nullptr.
     * @tc.expected: HandleEvent return true;
     */
    touchEventActuator->userCallback_ = nullptr;
    const TouchEvent touchEvent3 { .pointers = POINTERS_2 };
    EXPECT_TRUE(touchEventActuator->HandleEvent(touchEvent3));
}

/**
 * @tc.name: TouchEventDisable001
 * @tc.desc: Create TouchEventActuator and test disable.
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventTestNg, TouchEventDisable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TouchEventActuator.
     * @tc.expected: touchEventActuator is not nullptr.
     */
    auto touchEventActuator = AceType::MakeRefPtr<TouchEventActuator>();
    EXPECT_NE(touchEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke DispatchEvent.
     * @tc.expected: TouchTestResult size has been increased one.
     */
    const TouchEvent touchEvent { .tiltX = TILT_X_VALUE, .tiltY = TILT_Y_VALUE, .pointers = POINTERS };
    EXPECT_TRUE(touchEventActuator->DispatchEvent(touchEvent));

    /**
     * @tc.steps: step3. Invoke HandleEvent when touchEvents_ and userCallback_ is empty.
     * @tc.expected: HandleEvent will return true directly.
     */
    EXPECT_TRUE(touchEventActuator->HandleEvent(touchEvent));

    /**
     * @tc.steps: step4. Invoke ReplaceTouchEvent to initialize userCallback_.
     */
    double unknownTiltX = 0.0;
    const TouchEventFunc callback = [&unknownTiltX](
                                        TouchEventInfo& info) { unknownTiltX = info.GetTiltX().value_or(0.0); };
    TouchEventFunc callback1 = callback;
    touchEventActuator->ReplaceTouchEvent(std::move(callback1));
    EXPECT_NE(touchEventActuator->userCallback_, nullptr);

    EXPECT_TRUE(touchEventActuator->HandleEvent(touchEvent));
    EXPECT_EQ(unknownTiltX, TILT_X_VALUE);

    /**
     * @tc.steps: step5. Invoke Clear func to clear userCallback_.
     */
    touchEventActuator->ClearUserCallback();
    EXPECT_EQ(touchEventActuator->userCallback_, nullptr);
    EXPECT_TRUE(touchEventActuator->HandleEvent(touchEvent));
}
} // namespace OHOS::Ace::NG
