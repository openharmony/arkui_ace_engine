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

#include <optional>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/gestures/gesture_group.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/pinch_gesture.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/components_ng/gestures/recognizers/pinch_recognizer.h"
#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"
#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"
#include "core/components_ng/gestures/rotation_gesture.h"
#include "core/components_ng/gestures/swipe_gesture.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/gesture/gesture_model_ng.h"
#include "core/components_ng/test/mock/render/mock_media_player.h"
#include "core/event/axis_event.h"
#include "core/event/key_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t FINGER_NUMBER = 5;
constexpr int32_t FINGER_NUMBER_OVER_MAX = 11;
constexpr int32_t SINGLE_FINGER_NUMBER = 1;
constexpr int32_t COUNT = 2;
constexpr int32_t TAPPED_COUNT = 1;
constexpr int32_t LONG_PRESS_DURATION = 3000;
constexpr double PINCH_GESTURE_DISTANCE = 100.0;
constexpr double ROTATION_GESTURE_ANGLE = 1.0;
constexpr double CLICK_MULTI_TAP_SLOP = 110.0;
constexpr double PI = 360.0;
constexpr double COMMON_VALUE_RANGE_CASE = 101.0;
constexpr double SPECIAL_VALUE_RANGE_CASE1 = 181.0;
constexpr double SPECIAL_VALUE_RANGE_CASE2 = -181.0;
constexpr double SWIPE_SPEED = 10.0;
constexpr double VERTICAL_ANGLE = 90.0;
constexpr double HORIZONTAL_ANGLE = 180.0;
constexpr int32_t DEFAULT_PAN_FINGER = 1;
constexpr Dimension DEFAULT_PAN_DISTANCE = 5.0_vp;
constexpr int32_t DEFAULT_SLIDE_FINGER = DEFAULT_PAN_FINGER;
constexpr double DEFAULT_SLIDE_SPEED = 100.0;
constexpr double PAN_DISTANCE = 1.0;
} // namespace

class GesturesTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineBase::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineBase::TearDown();
    }
};

/**
 * @tc.name: GestureRecognizerTest001
 * @tc.desc: Test ClickRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ClickRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case1: onClick and remoteMessage is no
     * @tc.expected: step2. result equals.
     */
    ClickCallback onClick;
    clickRecognizer.onClick_ = onClick;
    ClickCallback remoteMessage;
    clickRecognizer.remoteMessage_ = remoteMessage;

    clickRecognizer.OnAccepted();
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case2: onClick and remoteMessage is yes, touchPoints is empty
     * @tc.expected: step2. result equals.
     */
    onClick = [](ClickInfo) {};
    clickRecognizer.onClick_ = onClick;
    clickRecognizer.touchPoints_.clear();
    remoteMessage = [](ClickInfo) {};
    clickRecognizer.remoteMessage_ = remoteMessage;

    clickRecognizer.OnAccepted();
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case3: onClick and remoteMessage is yes, touchPoints is not empty
     * @tc.expected: step2. result equals.
     */
    onClick = [](ClickInfo) {};
    clickRecognizer.onClick_ = onClick;
    clickRecognizer.touchPoints_.clear();
    remoteMessage = [](ClickInfo) {};
    clickRecognizer.remoteMessage_ = remoteMessage;
    TouchEvent touchEvent;
    clickRecognizer.touchPoints_[0] = touchEvent;

    clickRecognizer.OnAccepted();
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case4: onClick and remoteMessage is yes, touchPoints has tiltX and tiltY
     * @tc.expected: step2. result equals.
     */
    onClick = [](ClickInfo) {};
    clickRecognizer.onClick_ = onClick;
    clickRecognizer.touchPoints_.clear();
    remoteMessage = [](ClickInfo) {};
    clickRecognizer.remoteMessage_ = remoteMessage;
    touchEvent.tiltX = 0;
    touchEvent.tiltY = 0;
    clickRecognizer.touchPoints_[0] = touchEvent;

    clickRecognizer.OnAccepted();
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    clickRecognizer.OnRejected();
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: GestureRecognizerTest002
 * @tc.desc: Test ClickRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ClickRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case2: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.refereeState_ = RefereeState::SUCCEED;
    clickRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.fingers_ = FINGER_NUMBER_OVER_MAX;
    clickRecognizer.touchPoints_.clear();
    clickRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.disposal_, GestureDisposal::NONE);
}

/**
 * @tc.name: GestureRecognizerTest003
 * @tc.desc: Test ClickRecognizer function: ComputeFocusPoint
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ClickRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.touchPoints_.clear();
    clickRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    auto focusPoint = clickRecognizer.ComputeFocusPoint();
    EXPECT_EQ(focusPoint.GetX(), 0);
    EXPECT_EQ(focusPoint.GetY(), 0);
}

/**
 * @tc.name: GestureRecognizerTest004
 * @tc.desc: Test ClickRecognizer function: ExceedSlop
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ClickRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.steps: case1: not enter
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.touchPoints_.clear();
    clickRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    auto result = clickRecognizer.ExceedSlop();
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.steps: case2: tappedCount_ > 0 && tappedCount_ < count_, distance >= TAP_SLOP
     * @tc.expected: step2. result equals.
     */
    touchEvent.x = CLICK_MULTI_TAP_SLOP;
    touchEvent.y = CLICK_MULTI_TAP_SLOP;
    clickRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer.tappedCount_ = TAPPED_COUNT;
    clickRecognizer.count_ = COUNT;
    result = clickRecognizer.ExceedSlop();
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.steps: case3: tappedCount_ > 0 && tappedCount_ < count_, distance < TAP_SLOP
     * @tc.expected: step2. result equals.
     */
    touchEvent.x = 0;
    touchEvent.y = 0;
    clickRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer.tappedCount_ = TAPPED_COUNT;
    clickRecognizer.count_ = COUNT;
    result = clickRecognizer.ExceedSlop();
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.steps: case4: tappedCount_ = count_ = 0
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.tappedCount_ = 0;
    clickRecognizer.count_ = 0;
    result = clickRecognizer.ExceedSlop();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRecognizerTest005
 * @tc.desc: Test ClickRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ClickRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.touchPoints_.clear();
    clickRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    auto result = clickRecognizer.ReconcileFrom(clickRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = clickRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case3: recognizerPtr count != count
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->count_ = 1;
    clickRecognizer.count_ = 0;
    result = clickRecognizer.ReconcileFrom(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case4: recognizerPtr count same, fingers not same
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->count_ = clickRecognizer.count_;
    clickRecognizerPtr->fingers_ = clickRecognizer.fingers_ + 1;
    result = clickRecognizer.ReconcileFrom(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: recognizerPtr count same, fingers same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->count_ = clickRecognizer.count_;
    clickRecognizerPtr->fingers_ = clickRecognizer.fingers_;
    clickRecognizer.priorityMask_ = GestureMask::End;
    result = clickRecognizer.ReconcileFrom(clickRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRecognizerTest006
 * @tc.desc: Test ClickRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ClickRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.refereeState_ = RefereeState::SUCCEED;
    clickRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: refereeState is PENDING, tappedCount_ = 1, fingers > PointsNum
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizer.fingers_ = FINGER_NUMBER;
    clickRecognizer.tappedCount_ = 1;
    clickRecognizer.currentTouchPointsNum_ = 0;
    clickRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.currentTouchPointsNum_, 1);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: refereeState is PENDING, tappedCount_ = 1, fingers = 1
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizer.fingers_ = 1;
    clickRecognizer.tappedCount_ = 1;
    clickRecognizer.currentTouchPointsNum_ = 0;
    clickRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.equalsToFingers_, true);
}

/**
 * @tc.name: GestureRecognizerTest007
 * @tc.desc: Test ClickRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ClickRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.currentTouchPointsNum_ = 0;
    clickRecognizer.refereeState_ = RefereeState::SUCCEED;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: equalsToFingers = true, currentTouchPointsNum = 1, tap != count
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = 1;
    clickRecognizer.equalsToFingers_ = true;
    clickRecognizer.useCatchMode_ = false;
    clickRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_TRUE(clickRecognizer.equalsToFingers_);
    EXPECT_EQ(clickRecognizer.currentTouchPointsNum_, 1);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = 1;
    clickRecognizer.equalsToFingers_ = true;
    clickRecognizer.useCatchMode_ = false;
    clickRecognizer.tappedCount_ = 0;
    clickRecognizer.count_ = 0;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_TRUE(clickRecognizer.equalsToFingers_);
    EXPECT_EQ(clickRecognizer.currentTouchPointsNum_, 1);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = fingers,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = FINGER_NUMBER;
    clickRecognizer.fingers_ = FINGER_NUMBER;
    clickRecognizer.equalsToFingers_ = true;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.equalsToFingers_, true);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: equalsToFingers = false, currentTouchPointsNum = 1,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = 1;
    clickRecognizer.equalsToFingers_ = false;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case5: equalsToFingers = false, currentTouchPointsNum = 0,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = 0;
    clickRecognizer.equalsToFingers_ = false;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case6: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = 1;
    clickRecognizer.equalsToFingers_ = true;
    clickRecognizer.useCatchMode_ = false;
    clickRecognizer.tappedCount_ = -1;
    clickRecognizer.count_ = 0;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.equalsToFingers_, true);
    EXPECT_EQ(clickRecognizer.currentTouchPointsNum_, 1);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
}

/**
 * @tc.name: GestureRecognizerTest011
 * @tc.desc: Test ClickRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, GestureRecognizerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.currentTouchPointsNum_ = 0;
    clickRecognizer.refereeState_ = RefereeState::SUCCEED;
    clickRecognizer.currentFingers_ = FINGER_NUMBER;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: equalsToFingers = true, currentTouchPointsNum = 1, tap != count
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = 1;
    clickRecognizer.equalsToFingers_ = true;
    clickRecognizer.useCatchMode_ = false;
    clickRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizer.currentFingers_ = FINGER_NUMBER;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = 1;
    clickRecognizer.equalsToFingers_ = true;
    clickRecognizer.useCatchMode_ = false;
    clickRecognizer.tappedCount_ = 0;
    clickRecognizer.count_ = 0;
    clickRecognizer.currentFingers_ = FINGER_NUMBER;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: equalsToFingers = true, currentTouchPointsNum = fingers,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = FINGER_NUMBER;
    clickRecognizer.fingers_ = FINGER_NUMBER;
    clickRecognizer.equalsToFingers_ = true;
    clickRecognizer.currentFingers_ = FINGER_NUMBER;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.equalsToFingers_, true);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: equalsToFingers = false, currentTouchPointsNum = 1,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = 1;
    clickRecognizer.equalsToFingers_ = false;
    clickRecognizer.currentFingers_ = FINGER_NUMBER;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case5: equalsToFingers = false, currentTouchPointsNum = 0,
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = 0;
    clickRecognizer.equalsToFingers_ = false;
    clickRecognizer.currentFingers_ = FINGER_NUMBER;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.equalsToFingers_, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case6: equalsToFingers = true, currentTouchPointsNum = 1,
     * @tc.steps: tap == count, useCatchMode_ = false
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.currentTouchPointsNum_ = 1;
    clickRecognizer.equalsToFingers_ = true;
    clickRecognizer.useCatchMode_ = false;
    clickRecognizer.tappedCount_ = -1;
    clickRecognizer.count_ = 0;
    clickRecognizer.currentFingers_ = FINGER_NUMBER;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
}

/**
 * @tc.name: GestureRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test ClickRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, GestureRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.currentTouchPointsNum_ = 0;
    clickRecognizer.refereeState_ = RefereeState::SUCCEED;
    clickRecognizer.currentFingers_ = FINGER_NUMBER;
    clickRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);
}

/**
 * @tc.name: GestureRecognizerHandleOverdueDeadlineTest001
 * @tc.desc: Test ClickRecognizer function: HandleOverdueDeadline
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, GestureRecognizerHandleOverdueDeadlineTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.currentTouchPointsNum_ = FINGER_NUMBER;
    clickRecognizer.refereeState_ = RefereeState::SUCCEED;
    clickRecognizer.currentFingers_ = FINGER_NUMBER;
    clickRecognizer.tappedCount_ = FINGER_NUMBER;
    clickRecognizer.count_ = FINGER_NUMBER;
    clickRecognizer.HandleOverdueDeadline();
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);
}

/**
 * @tc.name: GestureRecognizerTest008
 * @tc.desc: Test ClickRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ClickRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS,return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.currentTouchPointsNum_ = 0;
    clickRecognizer.refereeState_ = RefereeState::SUCCEED;
    clickRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);

    clickRecognizer.refereeState_ = RefereeState::FAIL;
}

/**
 * @tc.name: GestureRecognizerTest009
 * @tc.desc: Test ClickRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ClickRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    clickRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    clickRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    clickRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    clickRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 1);
}

/**
 * @tc.name: GestureRecognizerTest010
 * @tc.desc: Test ClickRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ClickRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: event.sourceType == TOUCH
     * @tc.expected: step2. result equals.
     */
    clickRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizer.fingers_ = FINGER_NUMBER;
    clickRecognizer.tappedCount_ = 1;
    clickRecognizer.currentTouchPointsNum_ = 0;
    touchEvent.sourceType = SourceType::TOUCH;
    clickRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.currentTouchPointsNum_, 1);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: event.sourceType == MOUSE
     * @tc.expected: step2. result equals.
     */
    touchEvent.sourceType = SourceType::MOUSE;
    clickRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: event.sourceType == TOUCH_PAD
     * @tc.expected: step2. result equals.
     */
    touchEvent.sourceType = SourceType::TOUCH_PAD;
    clickRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.step4: case3: event.sourceType == OTHER
     * @tc.expected: step2. result equals.
     */
    touchEvent.sourceType = SourceType::KEYBOARD;
    clickRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
}

/**
 * @tc.name: ExclusiveRecognizerTest001
 * @tc.desc: Test ExclusiveRecognizer function: OnAccepted OnRejected OnPending OnBlocked
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ExclusiveRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtrNotSame = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case1: no active, no recognizers
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.OnAccepted();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case2: has active, recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    exclusiveRecognizer.OnAccepted();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case3: has active, recognizers has ptr not same
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtrNotSame);
    exclusiveRecognizer.OnAccepted();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case4: has active, recognizers has ptr same
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnAccepted();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.steps: case1: no recognizers
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.steps: case2: recognizers has nullptr
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.steps: case3: recognizers has ptr, referee is not FAIL
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.steps: case4: recognizers has ptr, referee is FAIL
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: ExclusiveRecognizerTest002
 * @tc.desc: Test ExclusiveRecognizer function: HandleEvent OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ExclusiveRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case1: active is nullptr, recognizers is empty
     * @tc.expected: step2. result equals.
     */
    bool result = false;
    TouchEvent touchEvent;
    touchEvent.type = TouchType::MOVE;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
    touchEvent.type = TouchType::DOWN;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
    touchEvent.type = TouchType::UP;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
    touchEvent.type = TouchType::CANCEL;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
    touchEvent.type = TouchType::UNKNOWN;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case2: active is not nullptr, checkTouchId is false
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    touchEvent.type = TouchType::DOWN;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case3: active is not nullptr, checkTouchId is true
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case4: active is nullptr, recognizers have nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case5: active is nullptr, recognizers have ptr, ptr not check
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->touchPoints_.clear();
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.steps: case6: active is nullptr, recognizers have ptr, ptr check
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->touchPoints_.clear();
    clickRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ExclusiveRecognizerTest003
 * @tc.desc: Test ExclusiveRecognizer function: CheckNeedBlocked
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ExclusiveRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    auto result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.steps: case2: recognizers is not empty, child == recognizer
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.steps: case3: recognizers is not empty, child is nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.steps: case3: recognizers is not empty, child is ptr, refeeState not PENDING
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtrNotSame = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtrNotSame->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtrNotSame);
    result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.steps: case4: recognizers is not empty, child is ptr, refeeState PENDING
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtrNotSame->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtrNotSame);
    result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ExclusiveRecognizerTest004
 * @tc.desc: Test ExclusiveRecognizer function: UnBlockGesture
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ExclusiveRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step2. call UnBlockGesture function and compare result.
     * @tc.expected: step2. result equals.
     */
    auto result = exclusiveRecognizer.UnBlockGesture();
    EXPECT_EQ(result, nullptr);

    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.UnBlockGesture();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ExclusiveRecognizerTest005
 * @tc.desc: Test ExclusiveRecognizer function: BatchAdjudicate, and GestureDisposal
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ExclusiveRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case1: refereeState_ is SUCCESS, return
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case2: GestureDisposal::ACCEPT, recognizer is SUCCESS
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case3: GestureDisposal::PENDING, recognizer is PENDING
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    exclusiveRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case4: GestureDisposal::REJECT, recognizer is FAIL
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    exclusiveRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::NONE);
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case4: GestureDisposal::REJECT, recognizer is FAIL
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    exclusiveRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);
}

/**
 * @tc.name: ExclusiveRecognizerTest006
 * @tc.desc: Test ExclusiveRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ExclusiveRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    auto result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = exclusiveRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case3: recognizerPtr size not same
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case4: recognizerPtr size not same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.priorityMask_ = GestureMask::End;
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: recognizerPtr size same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizerPtr->recognizers_.clear();
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case6: recognizerPtr same, child is nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.priorityMask_ = exclusiveRecognizerPtr->priorityMask_;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    exclusiveRecognizerPtr->recognizers_.clear();
    exclusiveRecognizerPtr->recognizers_.push_back(nullptr);
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case6: recognizerPtr same, child is nullptr
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    exclusiveRecognizer.priorityMask_ = exclusiveRecognizerPtr->priorityMask_;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizerPtr->recognizers_.clear();
    exclusiveRecognizerPtr->recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case6: recognizerPtr same, child is nullptr
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtrNotSame =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER - 1, COUNT - 1);
    exclusiveRecognizer.priorityMask_ = exclusiveRecognizerPtr->priorityMask_;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizerPtr->recognizers_.clear();
    exclusiveRecognizerPtr->recognizers_.push_back(clickRecognizerPtrNotSame);
    result = exclusiveRecognizer.ReconcileFrom(exclusiveRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ExclusiveRecognizerTest007
 * @tc.desc: Test ExclusiveRecognizer function: OnPending OnBlocked
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ExclusiveRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtrNotSame = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.steps: case4: recognizers has ptr, referee is FAIL
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step4. call OnPending function and compare result.
     * @tc.steps: case1: no active
     * @tc.expected: step4. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.OnPending();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step4. call OnPending function and compare result.
     * @tc.steps: case2: has active
     * @tc.expected: step4. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.OnPending();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case1: ACCEPT, no active
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::ACCEPT;
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case2: ACCEPT, active
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::ACCEPT;
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case3: PENDING, no active
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::PENDING;
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case3: PENDING, active
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::REJECT;
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case3: PENDING, active
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::PENDING;
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);
}

/**
 * @tc.name: ExclusiveRecognizerTest008
 * @tc.desc: Test ExclusiveRecognizer function: HandleEvent OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ExclusiveRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    bool result = false;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step3. create axisEvent and call HandleEvent function and compare result.
     * @tc.steps: case1: active is nullptr, recognizers is empty
     * @tc.expected: step3. result equals.
     */
    AxisEvent axisEvent;
    axisEvent.action = AxisAction::BEGIN;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);
    axisEvent.action = AxisAction::UPDATE;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);
    axisEvent.action = AxisAction::END;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);
    axisEvent.action = AxisAction::NONE;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step3. create axisEvent and call HandleEvent function and compare result.
     * @tc.steps: case2: active is ptr
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = clickRecognizerPtr;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step3. create axisEvent and call HandleEvent function and compare result.
     * @tc.steps: case3: active is nullptr, recognizers have nullptr
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step3. create axisEvent and call HandleEvent function and compare result.
     * @tc.steps: case4: active is nullptr, recognizers have ptr
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.activeRecognizer_ = nullptr;
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step4. call OnResetStatus function and compare result.
     * @tc.expected: step4. result equals.
     */
    exclusiveRecognizer.OnResetStatus();
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);
    axisEvent.action = AxisAction::CANCEL;
    result = exclusiveRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GestureRecognizerTest001
 * @tc.desc: Test GestureRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, GestureRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);
    clickRecognizer.refereeState_ = RefereeState::SUCCEED;
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call TouchEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::MOVE;
    clickRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    touchEvent.type = TouchType::DOWN;
    clickRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    touchEvent.type = TouchType::UP;
    clickRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    touchEvent.type = TouchType::CANCEL;
    clickRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    touchEvent.type = TouchType::UNKNOWN;
    clickRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call AxisEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    axisEvent.action = AxisAction::BEGIN;
    clickRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    axisEvent.action = AxisAction::UPDATE;
    clickRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    axisEvent.action = AxisAction::END;
    clickRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);

    axisEvent.action = AxisAction::NONE;
    clickRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: LongPressRecognizerTest001
 * @tc.desc: Test LongPressRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    OnLongPress onLongPress;
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case1: !onLongPress, !empty, repeat
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer.repeat_ = true;
    longPressRecognizer.OnAccepted();
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case2: !onLongPress, empty, !repeat
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.touchPoints_.clear();
    longPressRecognizer.repeat_ = false;
    longPressRecognizer.OnAccepted();
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case3: onLongPress, empty, !repeat
     * @tc.expected: step2. result equals.
     */
    onLongPress = [](LongPressInfo) {};
    longPressRecognizer.onLongPress_ = onLongPress;
    longPressRecognizer.touchPoints_.clear();
    longPressRecognizer.repeat_ = false;
    longPressRecognizer.OnAccepted();
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case4: onLongPress, !empty, !repeat
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.touchPoints_.clear();
    longPressRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer.repeat_ = false;
    longPressRecognizer.OnAccepted();
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    longPressRecognizer.OnRejected();
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: LongPressRecognizerTest002
 * @tc.desc: Test LongPressRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: referee is not SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.time_, touchEvent.time);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: referee is SUCCEED
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.time_, touchEvent.time);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: referee is SUCCEED
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.currentFingers_ = longPressRecognizer.fingers_;
    longPressRecognizer.refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.time_, touchEvent.time);
}

/**
 * @tc.name: LongPressRecognizerTest003
 * @tc.desc: Test LongPressRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case1: pointsCount == fingers, useCatchMode_ is true
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case2: pointsCount == fingers, useCatchMode_ is true
     * @tc.expected: step2. result equals.
     */
    touchEvent.sourceType = SourceType::MOUSE;
    longPressRecognizer.isForDrag_ = true;
    longPressRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer.fingers_ = 1;
    longPressRecognizer.useCatchMode_ = true;
    longPressRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(longPressRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::DETECTING);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case3: pointsCount == fingers, useCatchMode_ is false
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.useCatchMode_ = false;
    longPressRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::DETECTING);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: referee is SUCCEED
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case5: change SourceType to KEYBOARD
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.refereeState_ = RefereeState::PENDING;
    touchEvent.sourceType = SourceType::KEYBOARD;
    longPressRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case6: change isForDrag
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.isForDrag_ = !longPressRecognizer.isForDrag_;
    longPressRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case7: change isDisableMouseLeft_
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.isDisableMouseLeft_ = !longPressRecognizer.isDisableMouseLeft_;
    longPressRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 1);
}

/**
 * @tc.name: LongPressRecognizerTest004
 * @tc.desc: Test LongPressRecognizer function: HandleTouchCancelEvent UpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: refereeState == RefereeState::SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer.refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer.HandleTouchUpEvent(touchEvent);
    longPressRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: refereeState == RefereeState::SUCCEED
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer.currentFingers_ = longPressRecognizer.fingers_;
    longPressRecognizer.HandleTouchUpEvent(touchEvent);
    longPressRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 0);
}

/**
 * @tc.name: LongPressRecognizerDoRepeatTest001
 * @tc.desc: Test LongPressRecognizer function: DoRepeat
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerDoRepeatTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call DoRepeat
     * @tc.steps: refereeState == RefereeState::SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer.refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer.fingers_ = 0;
    longPressRecognizer.DoRepeat();
    longPressRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call DoRepeat
     * @tc.steps: refereeState == RefereeState::SUCCEED
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.refereeState_ = RefereeState::DETECTING;
    longPressRecognizer.currentFingers_ = longPressRecognizer.fingers_;
    longPressRecognizer.fingers_ = 0;
    longPressRecognizer.DoRepeat();
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 0);
}

/**
 * @tc.name: LongPressRecognizerTest005
 * @tc.desc: Test LongPressRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    bool isRepeat = false;

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    longPressRecognizer.SendCallbackMsg(onAction, isRepeat);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    longPressRecognizer.SendCallbackMsg(onAction, isRepeat);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    longPressRecognizer.SendCallbackMsg(onAction, isRepeat);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer.SendCallbackMsg(onAction, isRepeat);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    longPressRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer.SendCallbackMsg(onAction, isRepeat);
    EXPECT_EQ(longPressRecognizer.touchPoints_.size(), 1);
}

/**
 * @tc.name: LongPressRecognizerTest006
 * @tc.desc: Test LongPressRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    RefPtr<LongPressRecognizer> longPressRecognizerPtr =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    auto result = longPressRecognizer.ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = longPressRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case3: recognizerPtr, duration not same
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.duration_ = 0;
    result = longPressRecognizer.ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case4: recognizerPtr, duration same, fingers not same
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.duration_ = longPressRecognizerPtr->duration_;
    longPressRecognizer.fingers_ = longPressRecognizerPtr->fingers_ + 1;
    result = longPressRecognizer.ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: recognizerPtr, fingers same, repeat not same
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.fingers_ = longPressRecognizerPtr->fingers_;
    longPressRecognizer.repeat_ = !longPressRecognizerPtr->repeat_;
    result = longPressRecognizer.ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: recognizerPtr, repeat same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.repeat_ = longPressRecognizerPtr->repeat_;
    longPressRecognizer.priorityMask_ = GestureMask::End;
    result = longPressRecognizer.ReconcileFrom(longPressRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: LongPressRecognizerTestGetLongPressActionFunc001
 * @tc.desc: Test LongPressRecognizer function: GetLongPressActionFunc
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerTestGetLongPressActionFunc001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    bool isCatchMode = false;

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer.HandleOverdueDeadline(isCatchMode);
    longPressRecognizer.DoRepeat();
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::SUCCEED);
    auto result = longPressRecognizer.GetLongPressActionFunc();
}

/**
 * @tc.name: LongPressRecognizerTestGetLongPressActionFunc002
 * @tc.desc: Test LongPressRecognizer function: GetLongPressActionFunc
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerTestGetLongPressActionFunc002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    bool isCatchMode = false;

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer.fingers_ = SINGLE_FINGER_NUMBER;
    longPressRecognizer.HandleOverdueDeadline(isCatchMode);
    longPressRecognizer.DoRepeat();
    auto result = longPressRecognizer.GetLongPressActionFunc();
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.refereeState_ = RefereeState::DETECTING;
    longPressRecognizer.fingers_ = SINGLE_FINGER_NUMBER;
    longPressRecognizer.HandleOverdueDeadline(isCatchMode);
    longPressRecognizer.DoRepeat();
    result = longPressRecognizer.GetLongPressActionFunc();
    EXPECT_NE(longPressRecognizer.refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: LongPressRecognizerConvertPxToVpTest001
 * @tc.desc: Test LongPressRecognizer function: ConvertPxToVp
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerConvertPxToVpTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call ConvertPxToVp function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    double result = longPressRecognizer.ConvertPxToVp(0.0);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: LongPressRecognizerTest007
 * @tc.desc: Test LongPressRecognizer function: HandleOverdueDeadline  DoRepeat
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, LongPressRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);
    bool isCatchMode = false;

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case1: refereeState is SUCCESS, return
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.refereeState_ = RefereeState::SUCCEED;
    longPressRecognizer.HandleOverdueDeadline(isCatchMode);
    longPressRecognizer.DoRepeat();
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case1: refereeState is DETECTING, isCatchMode is false
     * @tc.expected: step2. result equals.
     */
    longPressRecognizer.refereeState_ = RefereeState::DETECTING;
    longPressRecognizer.HandleOverdueDeadline(isCatchMode);
    longPressRecognizer.DoRepeat();
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: PanRecognizerTest001
 * @tc.desc: Test PanRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    panRecognizer.OnAccepted();
    EXPECT_EQ(panRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    panRecognizer.OnRejected();
    EXPECT_EQ(panRecognizer.refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: PanRecognizerTest002
 * @tc.desc: Test PanRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case1: call TouchEvent, refereeState is SUCCEED, return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case2: call TouchEvent, normal case
     * @tc.expected: step2. result equals.
     */
    panRecognizer.refereeState_ = RefereeState::PENDING;
    panRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer.deviceId_, touchEvent.deviceId);
    EXPECT_EQ(panRecognizer.deviceType_, touchEvent.sourceType);
    EXPECT_EQ(panRecognizer.inputEventType_, InputEventType::TOUCH_SCREEN);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case3: call TouchEvent, set fingerNum != fingers_
     * @tc.expected: step2. result equals.
     */
    panRecognizer.fingers_ = FINGER_NUMBER;
    panRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer.refereeState_, RefereeState::DETECTING);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case4: call TouchEvent, set fingerNum = fingers_
     * @tc.expected: step2. result equals.
     */
    panRecognizer.fingers_ = 1;
    panRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer.refereeState_, RefereeState::DETECTING);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case4: call AxisEvent, refereeState is SUCCEED, return
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.touchPoints_.clear();
    panRecognizer.HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case5: call AxisEvent, refereeState is PENDING, normal case
     * @tc.expected: step2. result equals.
     */
    panRecognizer.refereeState_ = RefereeState::PENDING;
    panRecognizer.HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizer.deviceId_, axisEvent.deviceId);
    EXPECT_EQ(panRecognizer.deviceType_, axisEvent.sourceType);
    EXPECT_EQ(panRecognizer.inputEventType_, InputEventType::AXIS);
    EXPECT_EQ(panRecognizer.refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: PanRecognizerHandleTouchDownEventTest001
 * @tc.desc: Test PanRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerHandleTouchDownEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case1: call TouchEvent, refereeState is SUCCEED, return
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.sourceType = SourceType::MOUSE;
    panRecognizer.fingers_ = 1;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case2: call TouchEvent, normal case
     * @tc.expected: step2. result equals.
     */
    panRecognizer.refereeState_ = RefereeState::PENDING;
    panRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer.deviceId_, touchEvent.deviceId);
    EXPECT_EQ(panRecognizer.deviceType_, touchEvent.sourceType);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case3: call TouchEvent, set fingerNum != fingers_
     * @tc.expected: step2. result equals.
     */
    panRecognizer.fingers_ = FINGER_NUMBER;
    panRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer.refereeState_, RefereeState::DETECTING);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case4: call TouchEvent, set fingerNum = fingers_
     * @tc.expected: step2. result equals.
     */
    panRecognizer.fingers_ = 1;
    panRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer.refereeState_, RefereeState::DETECTING);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case4: call AxisEvent, refereeState is SUCCEED, return
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.touchPoints_.clear();
    panRecognizer.HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.steps: case5: call AxisEvent, refereeState is PENDING, normal case
     * @tc.expected: step2. result equals.
     */
    panRecognizer.refereeState_ = RefereeState::PENDING;
    panRecognizer.HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(panRecognizer.deviceId_, axisEvent.deviceId);
    EXPECT_EQ(panRecognizer.deviceType_, axisEvent.sourceType);
    EXPECT_EQ(panRecognizer.inputEventType_, InputEventType::AXIS);
    EXPECT_EQ(panRecognizer.refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: PanRecognizerTest003
 * @tc.desc: Test PanRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case1: refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case2: refereeState is SUCCEED, size > 1
     * @tc.expected: step2. result equals.
     */
    panRecognizer.touchPoints_[0] = touchEvent;
    panRecognizer.touchPoints_[1] = touchEvent;
    panRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case3: refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer.refereeState_ = RefereeState::FAIL;
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step3. call HandleTouchUp function and compare result.
     * @tc.steps: case1: refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), axisEvent.y);

    /**
     * @tc.steps: step3. call HandleTouchUp function and compare result.
     * @tc.steps: case2: refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer.refereeState_ = RefereeState::FAIL;
    panRecognizer.HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), axisEvent.y);
}

/**
 * @tc.name: PanRecognizerHandleTouchUpEventTest001
 * @tc.desc: Test PanRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case1: refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.currentFingers_ = panRecognizer.fingers_;
    panRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case2: refereeState is SUCCEED, size > 1
     * @tc.expected: step2. result equals.
     */
    panRecognizer.touchPoints_[0] = touchEvent;
    panRecognizer.touchPoints_[1] = touchEvent;
    panRecognizer.currentFingers_ = panRecognizer.fingers_;
    panRecognizer.refereeState_ = RefereeState::FAIL;
    panRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer.lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PanRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case1: direction.type is VERTICAL
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    panRecognizer.direction_.type = PanDirection::VERTICAL;
    panRecognizer.isFlushTouchEventsEnd_ = true;
    panRecognizer.currentFingers_ = panRecognizer.fingers_;
    panRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer.delta_.GetX(), 0);
    EXPECT_EQ(panRecognizer.delta_.GetY(), 0);
    EXPECT_EQ(panRecognizer.averageDistance_.GetX(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case2: direction.type is HORIZONTAL
     * @tc.expected: step2. result equals.
     */
    panRecognizer.direction_.type = PanDirection::HORIZONTAL;
    panRecognizer.currentFingers_ = panRecognizer.fingers_;
    panRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer.averageDistance_.GetY(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case3: isFlushTouchEventsEnd_ is false
     * @tc.expected: step2. result equals.
     */
    panRecognizer.isFlushTouchEventsEnd_ = false;
    panRecognizer.currentFingers_ = panRecognizer.fingers_;
    panRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer.averageDistance_.GetY(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case3: isFlushTouchEventsEnd_ is true
     * @tc.expected: step2. result equals.
     */
    panRecognizer.isFlushTouchEventsEnd_ = true;
    panRecognizer.currentFingers_ = panRecognizer.fingers_;
    panRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer.averageDistance_.GetY(), 0);
}

/**
 * @tc.name: PanRecognizerTest004
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case1: direction.type is VERTICAL
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    panRecognizer.direction_.type = PanDirection::VERTICAL;
    panRecognizer.isFlushTouchEventsEnd_ = true;
    panRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer.delta_.GetX(), 0);
    EXPECT_EQ(panRecognizer.delta_.GetY(), 0);
    EXPECT_EQ(panRecognizer.averageDistance_.GetX(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case2: direction.type is HORIZONTAL
     * @tc.expected: step2. result equals.
     */
    panRecognizer.direction_.type = PanDirection::HORIZONTAL;
    panRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer.averageDistance_.GetY(), 0);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.steps: case3: isFlushTouchEventsEnd_ is false
     * @tc.expected: step2. result equals.
     */
    panRecognizer.isFlushTouchEventsEnd_ = false;
    panRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer.averageDistance_.GetY(), 0);
}

/**
 * @tc.name: PanRecognizerTest005
 * @tc.desc: Test PanRecognizer function: OnFlushTouchEvents begin end
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchUp function and compare result.
     * @tc.expected: step2. result equals.
     */
    panRecognizer.OnFlushTouchEventsBegin();
    EXPECT_EQ(panRecognizer.isFlushTouchEventsEnd_, false);
    panRecognizer.OnFlushTouchEventsEnd();
    EXPECT_EQ(panRecognizer.isFlushTouchEventsEnd_, true);
}

/**
 * @tc.name: PanRecognizerTest006
 * @tc.desc: Test PanRecognizer function: IsPanGestureAccept
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. case1: PanDirection::ALL, fabs(offset) >= distance_.
     * @tc.expected: step2. return ACCEPT.
     */
    PanRecognizer::GestureAcceptResult result;
    panRecognizer.direction_.type = PanDirection::ALL;
    panRecognizer.distance_ = 0;
    result = panRecognizer.IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case2: PanDirection::ALL, fabs(offset) < distance_.
     * @tc.expected: step2. return DETECTING.
     */
    panRecognizer.direction_.type = PanDirection::ALL;
    panRecognizer.distance_ = 1;
    result = panRecognizer.IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case3: GetX > GetY, GetX < distance, PanDirection::HORIZONTAL.
     * @tc.expected: step2. return DETECTING.
     */
    panRecognizer.direction_.type = PanDirection::HORIZONTAL;
    panRecognizer.averageDistance_ = Offset(0, -1);
    panRecognizer.distance_ = 1;
    result = panRecognizer.IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case4: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::LEFT.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer.direction_.type = PanDirection::LEFT;
    panRecognizer.averageDistance_ = Offset(1, 0);
    panRecognizer.distance_ = 0;
    result = panRecognizer.IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::REJECT);

    /**
     * @tc.steps: step2. case5: GetX > GetY, GetX > 0, GetX > distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer.direction_.type = PanDirection::VERTICAL;
    panRecognizer.averageDistance_ = Offset(1, 0);
    panRecognizer.distance_ = 0;
    result = panRecognizer.IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case6: GetX > GetY, GetX = distance_ = 0, PanDirection::VERTICAL.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer.direction_.type = PanDirection::VERTICAL;
    panRecognizer.averageDistance_ = Offset(0, -1);
    panRecognizer.distance_ = 0;
    result = panRecognizer.IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);
}

/**
 * @tc.name: PanRecognizerTest007
 * @tc.desc: Test PanRecognizer function: IsPanGestureAccept
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. case7: GetX <= GetY, GetY < distance_, PanDirection::VERTICAL.
     * @tc.expected: step2. return DETECTING.
     */
    PanRecognizer::GestureAcceptResult result;
    panRecognizer.direction_.type = PanDirection::VERTICAL;
    panRecognizer.averageDistance_ = Offset(-1, 0);
    panRecognizer.distance_ = 1;
    result = panRecognizer.IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);

    /**
     * @tc.steps: step2. case8: GetX <= GetY, GetY > distance_, GetY < 0, PanDirection::DOWN.
     * @tc.expected: step2. return ACCEPT.
     */
    panRecognizer.direction_.type = PanDirection::DOWN;
    panRecognizer.averageDistance_ = Offset(-1, 1);
    panRecognizer.touchPointsDistance_[0] = Offset(-1, 1);
    panRecognizer.distance_ = 0;
    result = panRecognizer.IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::ACCEPT);

    /**
     * @tc.steps: step2. case9: GetX <= GetY, GetY > distance_, GetY > 0, PanDirection::UP.
     * @tc.expected: step2. return REJECT.
     */
    panRecognizer.direction_.type = PanDirection::UP;
    panRecognizer.averageDistance_ = Offset(-1, 1);
    panRecognizer.distance_ = 0;
    result = panRecognizer.IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::REJECT);

    /**
     * @tc.steps: step2. case10: GetX <= GetY, GetY = distance_ = 0, PanDirection::UP.
     * @tc.expected: step2. return DETECTING.
     */
    panRecognizer.direction_.type = PanDirection::UP;
    panRecognizer.averageDistance_ = Offset(-1, 0);
    panRecognizer.distance_ = 0;
    result = panRecognizer.IsPanGestureAccept();
    EXPECT_EQ(result, PanRecognizer::GestureAcceptResult::DETECTING);
}

/**
 * @tc.name: PanRecognizerTest008
 * @tc.desc: Test PanRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchCancel function and compare result.
     * @tc.steps: case1: Touch, refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchCancel function and compare result.
     * @tc.steps: case2: Touch, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer.refereeState_ = RefereeState::FAIL;
    panRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step3. call HandleTouchCancel function and compare result.
     * @tc.steps: case1: Axis, refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step3. call HandleTouchCancel function and compare result.
     * @tc.steps: case2: Axis, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer.refereeState_ = RefereeState::FAIL;
    panRecognizer.HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);
}

/**
 * @tc.name: PanRecognizerTest009
 * @tc.desc: Test PanRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    panRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    panRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty, type is AXIS
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    panRecognizer.inputEventType_ = InputEventType::AXIS;
    panRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y, type is not AXIS
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer.lastTouchEvent_ = touchEvent;
    panRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    panRecognizer.lastTouchEvent_ = touchEvent;
    panRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);
}

/**
 * @tc.name: PanRecognizerTest010
 * @tc.desc: Test PanRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case1: recognizer is nullptr
     * @tc.expected: step2. result equals.
     */
    auto result = panRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case2: recognizer is normal
     * @tc.expected: step2. result equals.
     */
    result = panRecognizer.ReconcileFrom(panRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case3: fingers not same
     * @tc.expected: step2. result equals.
     */
    panRecognizer.fingers_ = panRecognizerPtr->fingers_ + 1;
    result = panRecognizer.ReconcileFrom(panRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: fingers not same, priority not same
     * @tc.expected: step2. result equals.
     */
    panRecognizer.priorityMask_ = GestureMask::End;
    result = panRecognizer.ReconcileFrom(panRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: fingers same, priority not same
     * @tc.expected: step2. result equals.
     */
    panRecognizer.fingers_ = panRecognizerPtr->fingers_;
    result = panRecognizer.ReconcileFrom(panRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PanRecognizerTest011
 * @tc.desc: Test PanRecognizer function: SetDirection
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
    PanDirection panDirection;

    /**
     * @tc.steps: step2. call SetDirection function
     * @tc.steps: case1: panDirection is VERTICAL
     * @tc.expected: step2. result equals.
     */
    panDirection.type = PanDirection::VERTICAL;
    panRecognizer.SetDirection(panDirection);
    EXPECT_EQ(panRecognizer.velocityTracker_.mainAxis_, Axis::VERTICAL);

    /**
     * @tc.steps: step2. call SetDirection function
     * @tc.steps: case2: panDirection is HORIZONTAL
     * @tc.expected: step2. result equals.
     */
    panDirection.type = PanDirection::HORIZONTAL;
    panRecognizer.SetDirection(panDirection);
    EXPECT_EQ(panRecognizer.velocityTracker_.mainAxis_, Axis::HORIZONTAL);

    /**
     * @tc.steps: step2. call SetDirection function
     * @tc.steps: case2: panDirection is HORIZONTAL
     * @tc.expected: step2. result equals.
     */
    panDirection.type = PanDirection::ALL;
    panRecognizer.SetDirection(panDirection);
    EXPECT_EQ(panRecognizer.velocityTracker_.mainAxis_, Axis::HORIZONTAL);
}

/**
 * @tc.name: PanRecognizerTest012
 * @tc.desc: Test PanRecognizer function: ChangeFingers
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeFingers function
     * @tc.steps: case1: fingers not same
     * @tc.expected: step2. result equals.
     */
    panRecognizer.fingers_ = 0;
    panRecognizer.ChangeFingers(1);
    EXPECT_EQ(panRecognizer.newFingers_, 1);

    /**
     * @tc.steps: step2. call ChangeFingers function
     * @tc.steps: case1: fingers not same
     * @tc.expected: step2. result equals.
     */
    panRecognizer.fingers_ = 1;
    panRecognizer.ChangeFingers(1);
    EXPECT_EQ(panRecognizer.newFingers_, 1);
}

/**
 * @tc.name: PanRecognizerTest013
 * @tc.desc: Test PanRecognizer function: ChangeDirection
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeDirection function
     * @tc.steps: case1: type not same
     * @tc.expected: step2. result equals.
     */
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panRecognizer.direction_.type = PanDirection::HORIZONTAL;
    panRecognizer.ChangeDirection(panDirection);
    EXPECT_EQ(panRecognizer.direction_.type, PanDirection::VERTICAL);
    EXPECT_EQ(panRecognizer.newDirection_.type, PanDirection::VERTICAL);

    /**
     * @tc.steps: step2. call ChangeDirection function
     * @tc.steps: case2: type same
     * @tc.expected: step2. result equals.
     */
    panDirection.type = PanDirection::VERTICAL;
    panRecognizer.direction_.type = PanDirection::VERTICAL;
    panRecognizer.ChangeDirection(panDirection);
    EXPECT_EQ(panRecognizer.direction_.type, PanDirection::VERTICAL);
    EXPECT_EQ(panRecognizer.newDirection_.type, PanDirection::VERTICAL);
}

/**
 * @tc.name: PanRecognizerTest014
 * @tc.desc: Test PanRecognizer function: ChangeDistance
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case1: distance not same, refereeState is READY
     * @tc.expected: step2. result equals.
     */
    panRecognizer.distance_ = 0;
    panRecognizer.ChangeDistance(1);
    panRecognizer.refereeState_ = RefereeState::READY;
    EXPECT_EQ(panRecognizer.distance_, 1);
    EXPECT_EQ(panRecognizer.newDistance_, 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case2: distance not same, refereeState is DETECTING
     * @tc.expected: step2. result equals.
     */
    panRecognizer.distance_ = 0;
    panRecognizer.ChangeDistance(1);
    panRecognizer.refereeState_ = RefereeState::DETECTING;
    EXPECT_EQ(panRecognizer.distance_, 1);
    EXPECT_EQ(panRecognizer.newDistance_, 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case3: distance not same, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer.distance_ = 0;
    panRecognizer.ChangeDistance(1);
    panRecognizer.refereeState_ = RefereeState::FAIL;
    EXPECT_EQ(panRecognizer.distance_, 1);
    EXPECT_EQ(panRecognizer.newDistance_, 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case4: distance same
     * @tc.expected: step2. result equals.
     */
    panRecognizer.distance_ = 0;
    panRecognizer.ChangeDistance(0);
    panRecognizer.refereeState_ = RefereeState::FAIL;
    EXPECT_EQ(panRecognizer.distance_, 0);
    EXPECT_EQ(panRecognizer.newDistance_, 1);
}

/**
 * @tc.name: PanRecognizerChangeDistanceTest001
 * @tc.desc: Test PanRecognizer function: ChangeDistance
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerChangeDistanceTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case1: distance not same, refereeState is READY
     * @tc.expected: step2. result equals.
     */
    panRecognizer.distance_ = 0;
    panRecognizer.refereeState_ = RefereeState::READY;
    panRecognizer.ChangeDistance(1);
    EXPECT_EQ(panRecognizer.distance_, 1);
    EXPECT_EQ(panRecognizer.newDistance_, 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case2: distance not same, refereeState is DETECTING
     * @tc.expected: step2. result equals.
     */
    panRecognizer.distance_ = 0;
    panRecognizer.refereeState_ = RefereeState::DETECTING;
    panRecognizer.ChangeDistance(1);
    EXPECT_EQ(panRecognizer.distance_, 1);
    EXPECT_EQ(panRecognizer.newDistance_, 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case3: distance not same, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    panRecognizer.distance_ = 0;
    panRecognizer.refereeState_ = RefereeState::FAIL;
    panRecognizer.ChangeDistance(1);
    EXPECT_EQ(panRecognizer.newDistance_, 1);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case4: distance same
     * @tc.expected: step2. result equals.
     */
    panRecognizer.distance_ = 0;
    panRecognizer.refereeState_ = RefereeState::FAIL;
    panRecognizer.ChangeDistance(1);
    EXPECT_EQ(panRecognizer.distance_, 0);
    EXPECT_EQ(panRecognizer.newDistance_, 1);
}

/**
 * @tc.name: PanRecognizerTest015
 * @tc.desc: Test PanRecognizer function: GetMainAxisDelta
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case1: directionType is ALL
     * @tc.expected: step2. result equals.
     */
    PanDirection panDirection;
    panRecognizer.direction_ = panDirection;
    panRecognizer.direction_.type = PanDirection::ALL;
    auto result = panRecognizer.GetMainAxisDelta();
    EXPECT_EQ(result, 0);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case2: directionType is HORIZONTAL
     * @tc.expected: step2. result equals.
     */
    panRecognizer.direction_.type = PanDirection::HORIZONTAL;
    result = panRecognizer.GetMainAxisDelta();
    EXPECT_EQ(result, 0);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case3: directionType is VERTICAL
     * @tc.expected: step2. result equals.
     */
    panRecognizer.direction_.type = PanDirection::VERTICAL;
    result = panRecognizer.GetMainAxisDelta();
    EXPECT_EQ(result, 0);

    /**
     * @tc.steps: step2. call ChangeDistance function
     * @tc.steps: case4: directionType is LEFT
     * @tc.expected: step2. result equals.
     */
    panRecognizer.direction_.type = PanDirection::LEFT;
    result = panRecognizer.GetMainAxisDelta();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: PanRecognizerTest016
 * @tc.desc: Test PanRecognizer function: PanRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();

    /**
     * @tc.steps: step2. call PanRecognizer function
     * @tc.steps: case1: 0 <= direction.type <= 15
     * @tc.expected: step2. result equals.
     */
    PanRecognizer panRecognizer1 = PanRecognizer(panGestureOption);
    EXPECT_EQ(panRecognizer1.direction_.type, PanDirection::ALL);

    /**
     * @tc.steps: step2. call PanRecognizer function
     * @tc.steps: case1: 0 > direction.type
     * @tc.expected: step2. result equals.
     */
    panGestureOption->direction_.type = -1;
    PanRecognizer panRecognizer2 = PanRecognizer(panGestureOption);
    EXPECT_EQ(panRecognizer2.direction_.type, PanDirection::ALL);

    /**
     * @tc.steps: step2. call PanRecognizer function
     * @tc.steps: case1: 0 > direction.type
     * @tc.expected: step2. result equals.
     */
    panGestureOption->direction_.type = PanDirection::ALL + 1;
    PanRecognizer panRecognizer3 = PanRecognizer(panGestureOption);
    EXPECT_EQ(panRecognizer3.direction_.type, PanDirection::ALL);
}

/**
 * @tc.name: PanRecognizerTest017
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent(AxisEvent)
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PanRecognizerTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);
    AxisEvent axisEvent;

    /**
     * @tc.steps: step2. call HandleTouchMove function and compare result.
     * @tc.steps: case1: fingers_ is 0, return
     * @tc.expected: step2. result equals.
     */
    panRecognizer.fingers_ = 0;
    panRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call HandleTouchMove function and compare result.
     * @tc.steps: case2: fingers_ is 1, direction is VERTICAL, refereeState is SUCCEED
     * @tc.expected: step2. result equals.
     */
    panRecognizer.fingers_ = 1;
    panRecognizer.direction_.type = PanDirection::VERTICAL;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);
    EXPECT_EQ(panRecognizer.delta_.GetX(), 0);
    EXPECT_EQ(panRecognizer.delta_.GetY(), 0);

    /**
     * @tc.steps: step2. call HandleTouchMove function and compare result.
     * @tc.steps: case3: fingers_ is 1, direction is HORIZONTAL, refereeState is SUCCEED
     * @tc.steps: case3: event.horizontalAxis = 0
     * @tc.expected: step2. result equals.
     */
    panRecognizer.direction_.type = PanDirection::HORIZONTAL;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    axisEvent.horizontalAxis = 0;
    panRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);
    EXPECT_EQ(panRecognizer.delta_.GetX(), 0);
    EXPECT_EQ(panRecognizer.delta_.GetY(), 0);

    /**
     * @tc.steps: step2. call HandleTouchMove function and compare result.
     * @tc.steps: case3: fingers_ is 1, direction is HORIZONTAL, refereeState is PENDING
     * @tc.steps: case3: event.horizontalAxis != 0
     * @tc.expected: step2. result equals.
     */
    panRecognizer.direction_.type = PanDirection::HORIZONTAL;
    panRecognizer.refereeState_ = RefereeState::PENDING;
    axisEvent.horizontalAxis = 1;
    panRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizer.touchPoints_.size(), 0);
}

/**
 * @tc.name: ParallelRecognizerTest001
 * @tc.desc: Test ParallelRecognizer function: OnAccepted OnRejected OnPending OnBlock
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ParallelRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ParallelRecognizer parallelRecognizer = ParallelRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case1: recognizer is nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.currentBatchRecognizer_ = nullptr;
    parallelRecognizer.OnAccepted();
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case2: recognizer is not nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.currentBatchRecognizer_ = clickRecognizerPtr;
    parallelRecognizer.OnAccepted();
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    parallelRecognizer.OnRejected();
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step4. call OnPending function and compare result.
     * @tc.steps: case1: recognizer is nullptr
     * @tc.expected: step4. result equals.
     */
    parallelRecognizer.currentBatchRecognizer_ = nullptr;
    parallelRecognizer.OnPending();
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step4. call OnPending function and compare result.
     * @tc.steps: case2: recognizer is not nullptr
     * @tc.expected: step4. result equals.
     */
    parallelRecognizer.currentBatchRecognizer_ = clickRecognizerPtr;
    parallelRecognizer.OnPending();
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case1: disposal is ACCEPT, current is nullptr
     * @tc.expected: step5. result equals.
     */
    parallelRecognizer.currentBatchRecognizer_ = nullptr;
    parallelRecognizer.disposal_ = GestureDisposal::ACCEPT;
    parallelRecognizer.OnBlocked();
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case2: disposal is ACCEPT, current is not nullptr
     * @tc.expected: step5. result equals.
     */
    parallelRecognizer.currentBatchRecognizer_ = clickRecognizerPtr;
    parallelRecognizer.disposal_ = GestureDisposal::ACCEPT;
    parallelRecognizer.OnBlocked();
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case3: disposal is PENDING, current is nullptr
     * @tc.expected: step5. result equals.
     */
    parallelRecognizer.currentBatchRecognizer_ = nullptr;
    parallelRecognizer.disposal_ = GestureDisposal::PENDING;
    parallelRecognizer.OnBlocked();
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case4: disposal is PENDING, current is not nullptr
     * @tc.expected: step5. result equals.
     */
    parallelRecognizer.currentBatchRecognizer_ = clickRecognizerPtr;
    parallelRecognizer.disposal_ = GestureDisposal::NONE;
    parallelRecognizer.OnBlocked();
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.steps: case4: disposal is PENDING, current is not nullptr
     * @tc.expected: step5. result equals.
     */
    parallelRecognizer.currentBatchRecognizer_ = clickRecognizerPtr;
    parallelRecognizer.disposal_ = GestureDisposal::PENDING;
    parallelRecognizer.OnBlocked();
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);
}

/**
 * @tc.name: ParallelRecognizerTest002
 * @tc.desc: Test ParallelRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ParallelRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ParallelRecognizer parallelRecognizer = ParallelRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: refereeState is READY, recognizers is empty
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.refereeState_ = RefereeState::READY;
    TouchEvent touchEvent;
    auto result = parallelRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::DETECTING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: refereeState is PENDING, recognizers have nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.refereeState_ = RefereeState::PENDING;
    parallelRecognizer.recognizers_.clear();
    parallelRecognizer.recognizers_.push_back(nullptr);
    result = parallelRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: refereeState is PENDING, recognizers have ptr, not check
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.refereeState_ = RefereeState::PENDING;
    parallelRecognizer.recognizers_.clear();
    parallelRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = parallelRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: refereeState is PENDING, recognizers have ptr, check
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    parallelRecognizer.refereeState_ = RefereeState::PENDING;
    parallelRecognizer.recognizers_.clear();
    parallelRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = parallelRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ParallelRecognizerHandleEventTest001
 * @tc.desc: Test ParallelRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ParallelRecognizerHandleEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ParallelRecognizer parallelRecognizer = ParallelRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: refereeState is READY, recognizers is empty
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.refereeState_ = RefereeState::READY;
    TouchEvent touchEvent;
    AxisEvent axisEvent;
    auto result = parallelRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::DETECTING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: refereeState is PENDING, recognizers have nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.refereeState_ = RefereeState::PENDING;
    parallelRecognizer.recognizers_.clear();
    parallelRecognizer.recognizers_.push_back(nullptr);
    result = parallelRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: refereeState is PENDING, recognizers have ptr, not check
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.refereeState_ = RefereeState::PENDING;
    parallelRecognizer.recognizers_.clear();
    parallelRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = parallelRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: refereeState is PENDING, recognizers have ptr, check
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    parallelRecognizer.refereeState_ = RefereeState::PENDING;
    parallelRecognizer.recognizers_.clear();
    parallelRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = parallelRecognizer.HandleEvent(axisEvent);
    EXPECT_EQ(parallelRecognizer.refereeState_, RefereeState::PENDING);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ParallelRecognizerTest003
 * @tc.desc: Test ParallelRecognizer function: BatchAdjudicate
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ParallelRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ParallelRecognizer parallelRecognizer = ParallelRecognizer(recognizers);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: disposal is ACCEPT, refereeState is SUCCEED
     * @tc.expected: step2. expect return
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: disposal is ACCEPT, refereeState is PENDING, refereeState_ is SUCCEED
     * @tc.expected: step2. expect SUCCESS
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer.refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: disposal is ACCEPT, refereeState is PENDING, refereeState_ is PENDING_BLOCKED
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer.refereeState_ = RefereeState::PENDING_BLOCKED;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: disposal is REJECT, refereeState is FAIL
     * @tc.expected: step2. expect FAIL
     */
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    parallelRecognizer.refereeState_ = RefereeState::FAIL;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case5: disposal is PENDING, refereeState is PENDING, refereeState_ is PENDING
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer.refereeState_ = RefereeState::PENDING;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case6: disposal is PENDING, refereeState is READY, refereeState_ is PENDING
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer.refereeState_ = RefereeState::PENDING;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case7: disposal is PENDING, refereeState is READY, refereeState_ is PENDING_BLOCKED
     * @tc.expected: step2. expect PENDING_CLOCKED
     */
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer.refereeState_ = RefereeState::PENDING_BLOCKED;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: ParallelRecognizerBatchAdjudicateTest001
 * @tc.desc: Test ParallelRecognizer function: BatchAdjudicate
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ParallelRecognizerBatchAdjudicateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ParallelRecognizer parallelRecognizer = ParallelRecognizer(recognizers);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: disposal is ACCEPT, refereeState is SUCCEED
     * @tc.expected: step2. expect return
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case2: disposal is ACCEPT, refereeState is PENDING, refereeState_ is SUCCEED
     * @tc.expected: step2. expect SUCCESS
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer.refereeState_ = RefereeState::SUCCEED_BLOCKED;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: disposal is ACCEPT, refereeState is PENDING, refereeState_ is PENDING_BLOCKED
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer.refereeState_ = RefereeState::SUCCEED_BLOCKED;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: disposal is REJECT, refereeState is FAIL
     * @tc.expected: step2. expect FAIL
     */
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    parallelRecognizer.refereeState_ = RefereeState::FAIL;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case5: disposal is PENDING, refereeState is PENDING, refereeState_ is PENDING
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    parallelRecognizer.refereeState_ = RefereeState::SUCCEED_BLOCKED;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case6: disposal is PENDING, refereeState is READY, refereeState_ is PENDING
     * @tc.expected: step2. expect PENDING
     */
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer.refereeState_ = RefereeState::PENDING;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case7: disposal is PENDING, refereeState is READY, refereeState_ is PENDING_BLOCKED
     * @tc.expected: step2. expect PENDING_CLOCKED
     */
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    parallelRecognizer.refereeState_ = RefereeState::PENDING_BLOCKED;
    parallelRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: ParallelRecognizerTest004
 * @tc.desc: Test ParallelRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, ParallelRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ParallelRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ParallelRecognizer parallelRecognizer = ParallelRecognizer(recognizers);
    RefPtr<ParallelRecognizer> parallelRecognizerPtr = AceType::MakeRefPtr<ParallelRecognizer>(recognizers);
    bool result = false;

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    result = parallelRecognizer.ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = parallelRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case3: recognizers_ = {nullptr};
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.recognizers_ = { nullptr };
    result = parallelRecognizer.ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case4: recognizers_ = {};
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.recognizers_ = {};
    result = parallelRecognizer.ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: curr->priorityMask_ != priorityMask_
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.priorityMask_ = GestureMask::Normal;
    parallelRecognizerPtr->priorityMask_ = GestureMask::Begin;
    result = parallelRecognizer.ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case6: size and Mask is same, child is nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.priorityMask_ = parallelRecognizerPtr->priorityMask_;
    parallelRecognizer.recognizers_.clear();
    parallelRecognizerPtr->recognizers_.clear();
    parallelRecognizer.recognizers_.push_back(nullptr);
    parallelRecognizerPtr->recognizers_.push_back(nullptr);
    result = parallelRecognizer.ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case7: size and Mask is same, child is ptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.recognizers_.clear();
    parallelRecognizerPtr->recognizers_.clear();
    parallelRecognizer.recognizers_.push_back(clickRecognizerPtr);
    parallelRecognizerPtr->recognizers_.push_back(clickRecognizerPtr);
    result = parallelRecognizer.ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case8: size and Mask is same, child is ptr and nullptr
     * @tc.expected: step2. result equals.
     */
    parallelRecognizer.recognizers_.clear();
    parallelRecognizerPtr->recognizers_.clear();
    parallelRecognizer.recognizers_.push_back(clickRecognizerPtr);
    parallelRecognizerPtr->recognizers_.push_back(nullptr);
    result = parallelRecognizer.ReconcileFrom(parallelRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PinchRecognizerTest001
 * @tc.desc: Test PinchRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.OnAccepted();
    EXPECT_EQ(pinchRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    pinchRecognizer.OnRejected();
    EXPECT_EQ(pinchRecognizer.refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: PinchRecognizerTest002
 * @tc.desc: Test PinchRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent. refereeState_ is SUCCESS.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer.refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(static_cast<int32_t>(pinchRecognizer.touchPoints_.size()), 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: input is TouchEvent. refereeState_ is PENDING.
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::PENDING;
    pinchRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: input is TouchEvent. refereeState_ is PENDING. fingers_ > size
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::PENDING;
    pinchRecognizer.fingers_ = FINGER_NUMBER;
    pinchRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(static_cast<int32_t>(pinchRecognizer.touchPoints_.size()), 1);
    EXPECT_EQ(pinchRecognizer.refereeState_, RefereeState::PENDING);
}

/**
 * @tc.name: PinchRecognizerTest003
 * @tc.desc: Test PinchRecognizer function: HandleMove HandleUp HandleCancel
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer.refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer.HandleTouchMoveEvent(touchEvent);
    pinchRecognizer.HandleTouchUpEvent(touchEvent);
    pinchRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case2: input is AxisEvent
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    pinchRecognizer.refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case3: input is TouchEvent, isFlushTouchEventsEnd_
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer.isFlushTouchEventsEnd_ = true;
    pinchRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::FAIL;
    pinchRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case5: input is AxisEvent
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::FAIL;
    pinchRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case6: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::FAIL;
    pinchRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PinchRecognizerTest004
 * @tc.desc: Test PinchRecognizer function: OnFlushTouchEvent begin end
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call OnFlushTouchEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.OnFlushTouchEventsBegin();
    EXPECT_EQ(pinchRecognizer.isFlushTouchEventsEnd_, false);
    pinchRecognizer.OnFlushTouchEventsEnd();
    EXPECT_EQ(pinchRecognizer.isFlushTouchEventsEnd_, true);
}

/**
 * @tc.name: PinchRecognizerTest005
 * @tc.desc: Test PinchRecognizer function: ComputeAverageDeviation
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call ComputeAverageDeviation function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    auto result = pinchRecognizer.ComputeAverageDeviation();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: PinchRecognizerComputePinchCenterTest001
 * @tc.desc: Test PinchRecognizer function: ComputePinchCenter
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerComputePinchCenterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call ComputePinchCenter function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    auto result = pinchRecognizer.ComputePinchCenter();
    pinchRecognizer.OnFlushTouchEventsEnd();
    EXPECT_EQ(pinchRecognizer.isFlushTouchEventsEnd_, true);
}

/**
 * @tc.name: PinchRecognizerTest006
 * @tc.desc: Test PinchRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    pinchRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(pinchRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    pinchRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(pinchRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    pinchRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(pinchRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer.lastTouchEvent_ = touchEvent;
    pinchRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(pinchRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    pinchRecognizer.lastTouchEvent_ = touchEvent;
    pinchRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(pinchRecognizer.touchPoints_.size(), 0);
}

/**
 * @tc.name: PinchRecognizerTest007
 * @tc.desc: Test PinchRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    RefPtr<PinchRecognizer> pinchRecognizerPtr =
        AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    bool result = false;

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    result = pinchRecognizer.ReconcileFrom(pinchRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = pinchRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case3: fingers_ != curr->fingers_;
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.fingers_ = 1;
    pinchRecognizerPtr->fingers_ = 0;
    result = pinchRecognizer.ReconcileFrom(pinchRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case4: fingers_ same, distance not same
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.fingers_ = pinchRecognizerPtr->fingers_;
    pinchRecognizer.distance_ = pinchRecognizerPtr->distance_ + 1;
    result = pinchRecognizer.ReconcileFrom(pinchRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case5: fingers_ same, distance same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.fingers_ = pinchRecognizerPtr->fingers_;
    pinchRecognizer.distance_ = pinchRecognizerPtr->distance_;
    pinchRecognizer.priorityMask_ = GestureMask::End;
    result = pinchRecognizer.ReconcileFrom(pinchRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: RecognizerGroupTest001
 * @tc.desc: Test RecognizerGroup function: OnBeginGestureReferee
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RecognizerGroupTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnBeginGestureReferee function and compare result.
     * @tc.steps: case1: needUpdateChild is false
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.OnBeginGestureReferee(0, false);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnBeginGestureReferee function and compare result.
     * @tc.steps: case2: needUpdateChild is true, recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.OnBeginGestureReferee(0, true);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnBeginGestureReferee function and compare result.
     * @tc.steps: case3: needUpdateChild is true, recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    exclusiveRecognizer.OnBeginGestureReferee(0, true);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call OnBeginGestureReferee function and compare result.
     * @tc.steps: case4: needUpdateChild is true, recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnBeginGestureReferee(0, true);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupTest002
 * @tc.desc: Test RecognizerGroup function: OnFinishGestureReferee
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RecognizerGroupTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnFinishGestureReferee function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.OnFinishGestureReferee(0);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnFinishGestureReferee function and compare result.
     * @tc.steps: case2: recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    exclusiveRecognizer.OnFinishGestureReferee(0);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnFinishGestureReferee function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnFinishGestureReferee(0);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);
}

/**
 * @tc.name: RecognizerGroupTest003
 * @tc.desc: Test RecognizerGroup function: AddChildren
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RecognizerGroupTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::list<RefPtr<NGGestureRecognizer>> recognizersInput = {};

    /**
     * @tc.steps: step2. call OnFinishGestureReferee function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.AddChildren(recognizersInput);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnFinishGestureReferee function and compare result.
     * @tc.steps: case2: recognizers is not empty
     * @tc.expected: step2. result equals.
     */
    recognizersInput = { nullptr, clickRecognizerPtr, clickRecognizerPtr };
    exclusiveRecognizer.AddChildren(recognizersInput);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupTest004
 * @tc.desc: Test RecognizerGroup function: Existed
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RecognizerGroupTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Existed function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.Existed(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call Existed function and compare result.
     * @tc.steps: case2: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.Existed(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupTest005
 * @tc.desc: Test RecognizerGroup function: OnFlushTouchEventsBegin End Reset
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RecognizerGroupTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.OnFlushTouchEventsBegin();
    exclusiveRecognizer.OnFlushTouchEventsEnd();
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case2: recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.push_back(nullptr);
    exclusiveRecognizer.OnFlushTouchEventsBegin();
    exclusiveRecognizer.OnFlushTouchEventsEnd();
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnFlushTouchEventsBegin();
    exclusiveRecognizer.OnFlushTouchEventsEnd();
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case4: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.remainChildOnResetStatus_ = true;
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupTest006
 * @tc.desc: Test RecognizerGroup function: GetGroupRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RecognizerGroupTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.OnFlushTouchEventsBegin();
    exclusiveRecognizer.OnFlushTouchEventsEnd();
    exclusiveRecognizer.GetGroupRecognizer();
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);
}

/**
 * @tc.name: RecognizerGroupTest007
 * @tc.desc: Test RecognizerGroup function: ForceReject
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RecognizerGroupTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.OnFlushTouchEventsBegin();
    exclusiveRecognizer.OnFlushTouchEventsEnd();
    exclusiveRecognizer.ForceReject();
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.recognizers_.clear();
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer.OnFlushTouchEventsBegin();
    exclusiveRecognizer.OnFlushTouchEventsEnd();
    exclusiveRecognizer.ForceReject();
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupTest008
 * @tc.desc: Test RecognizerGroup function: CheckAllFailed
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RecognizerGroupTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.OnFlushTouchEventsBegin();
    exclusiveRecognizer.OnFlushTouchEventsEnd();
    bool result = exclusiveRecognizer.CheckAllFailed();
    EXPECT_EQ(exclusiveRecognizer.recognizers_.size(), 0);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: RotationRecognizerTest001
 * @tc.desc: Test RotationRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.OnAccepted();
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    rotationRecognizer.OnRejected();
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: RotationRecognizerTest002
 * @tc.desc: Test RotationRecognizer function: TouchDown TouchUp TouchMove
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    rotationRecognizer.HandleTouchUpEvent(touchEvent);
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    rotationRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER;
    rotationRecognizer.refereeState_ = RefereeState::FAIL;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    rotationRecognizer.HandleTouchUpEvent(touchEvent);
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    rotationRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchDownEventTest001
 * @tc.desc: Test RotationRecognizer function: TouchDown TouchUp TouchMove
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerHandleTouchDownEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer.fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    rotationRecognizer.HandleTouchUpEvent(touchEvent);
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    rotationRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.refereeState_ = RefereeState::FAIL;
    rotationRecognizer.fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    rotationRecognizer.HandleTouchUpEvent(touchEvent);
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    rotationRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchDownEventTest002
 * @tc.desc: Test RotationRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerHandleTouchDownEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer.fingers_ = 0;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.fingers_ = 0;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.refereeState_ = RefereeState::FAIL;
    rotationRecognizer.fingers_ = 0;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchUpEventTest001
 * @tc.desc: Test RotationRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER;
    rotationRecognizer.refereeState_ = RefereeState::FAIL;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test RotationRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER;
    rotationRecognizer.refereeState_ = RefereeState::FAIL;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchMoveEventTest002
 * @tc.desc: Test RotationRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerHandleTouchMoveEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = 0;
    rotationRecognizer.refereeState_ = RefereeState::FAIL;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::FAIL);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerHandleTouchMoveEventTest003
 * @tc.desc: Test RotationRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerHandleTouchMoveEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case1: touchPoints.size == fingers
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case2: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = FINGER_NUMBER_OVER_MAX;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.steps: case3: touchPoints.size < fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = 0;
    rotationRecognizer.refereeState_ = RefereeState::SUCCEED;
    rotationRecognizer.currentFingers_ = rotationRecognizer.fingers_;
    rotationRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0);
}

/**
 * @tc.name: RotationRecognizerTest003
 * @tc.desc: Test RotationRecognizer function: ChangeValueRange
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call ChangeValueRange function and compare result.
     * @tc.expected: step2. result equals.
     */
    auto result = rotationRecognizer.ChangeValueRange(COMMON_VALUE_RANGE_CASE);
    EXPECT_EQ(result, COMMON_VALUE_RANGE_CASE);

    result = rotationRecognizer.ChangeValueRange(SPECIAL_VALUE_RANGE_CASE1);
    EXPECT_EQ(result, SPECIAL_VALUE_RANGE_CASE1 - PI);

    result = rotationRecognizer.ChangeValueRange(SPECIAL_VALUE_RANGE_CASE2);
    EXPECT_EQ(result, SPECIAL_VALUE_RANGE_CASE2 + PI);
}

/**
 * @tc.name: RotationRecognizerTest004
 * @tc.desc: Test RotationRecognizer function: ComputeAngle
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call ComputeAngle function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEventStart;
    touchEventStart.id = 0;
    rotationRecognizer.touchPoints_[0] = touchEventStart;
    TouchEvent touchEventEnd;
    touchEventEnd.id = 1;
    rotationRecognizer.touchPoints_[1] = touchEventEnd;
    auto result = rotationRecognizer.ComputeAngle();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: RotationRecognizerTest005
 * @tc.desc: Test RotationRecognizer function: OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call OnResetStatus function and compare result.
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.OnResetStatus();
    EXPECT_EQ(rotationRecognizer.initialAngle_, 0.0);
    EXPECT_EQ(rotationRecognizer.currentAngle_, 0.0);
    EXPECT_EQ(rotationRecognizer.resultAngle_, 0.0);
}

/**
 * @tc.name: RotationRecognizerTest006
 * @tc.desc: Test RotationRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: onAction is no, *onAction is no
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: onAction is yes, *onAction is no
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>();
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: onAction is yes, *onAction is yes, touchEvent is empty
     * @tc.expected: step2. result equals.
     */
    onAction = std::make_unique<GestureEventFunc>([](GestureEvent) {});
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 1);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: touchEvent is not empty, have no X and Y
     * @tc.expected: step2. result equals.
     */
    touchEvent.tiltX = 0.0f;
    touchEvent.tiltY = 0.0f;
    rotationRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    rotationRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(rotationRecognizer.touchPoints_.size(), 1);
}

/**
 * @tc.name: RotationRecognizerTest007
 * @tc.desc: Test RotationRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, RotationRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    RotationRecognizer rotationRecognizer = RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    bool result = false;

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case1: recognizerPtr is nullptr
     * @tc.expected: step2. result equals.
     */
    result = rotationRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal, curr->fingers != fingers
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = rotationRecognizerPtr->fingers_ + 1;
    result = rotationRecognizer.ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal, curr->angle != angle
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizer.angle_ = rotationRecognizerPtr->angle_ + 1;
    result = rotationRecognizer.ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal, curr->priorityMask != priorityMask
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizer.angle_ = rotationRecognizerPtr->angle_;
    rotationRecognizer.priorityMask_ = GestureMask::Begin;
    result = rotationRecognizer.ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function and compare result.
     * @tc.steps: case2: recognizerPtr is normal
     * @tc.expected: step2. result equals.
     */
    rotationRecognizer.fingers_ = rotationRecognizerPtr->fingers_;
    rotationRecognizer.angle_ = rotationRecognizerPtr->angle_;
    rotationRecognizer.priorityMask_ = rotationRecognizerPtr->priorityMask_;
    result = rotationRecognizer.ReconcileFrom(rotationRecognizerPtr);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SequencedRecognizerTest001
 * @tc.desc: Test SequencedRecognizer function: OnAccepted
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.OnAccepted();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case2: recognizers_ is not empty, have nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.recognizers_.push_back(nullptr);
    sequencedRecognizer.OnAccepted();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case3: recognizers_ is not empty, have click ptr
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer.OnAccepted();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::SUCCEED);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: SequencedRecognizerTest002
 * @tc.desc: Test SequencedRecognizer function: OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);

    /**
     * @tc.steps: step2. call OnRejected function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.OnRejected();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call OnRejected function and compare result.
     * @tc.steps: case2: recognizers_ is not empty, have nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.currentIndex_ = -1;
    sequencedRecognizer.recognizers_.push_back(nullptr);
    sequencedRecognizer.OnRejected();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.steps: case3: recognizers_ is not empty, have click ptr
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer.currentIndex_ = 0;
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer.OnRejected();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::FAIL);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: SequencedRecognizerTest003
 * @tc.desc: Test SequencedRecognizer function: OnPending
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);

    /**
     * @tc.steps: step2. call OnPending function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.OnPending();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call OnPending function and compare result.
     * @tc.steps: case2: recognizers_ is not empty, have nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.recognizers_.push_back(nullptr);
    sequencedRecognizer.OnPending();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call OnPending function and compare result.
     * @tc.steps: case3: recognizers_ is not empty, have click ptr, ACCEPT
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->disposal_ = GestureDisposal::ACCEPT;
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer.OnPending();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call OnPending function and compare result.
     * @tc.steps: case4: recognizers_ is not empty, have click ptr, PENDING
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->disposal_ = GestureDisposal::PENDING;
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer.OnPending();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);
}

/**
 * @tc.name: SequencedRecognizerTest004
 * @tc.desc: Test SequencedRecognizer function: OnBlocked
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.OnBlocked();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case2: recognizers_ is not empty, have nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.recognizers_.push_back(nullptr);
    sequencedRecognizer.OnBlocked();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::READY);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case3: recognizers_ is not empty, disposal is ACCEPT
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer.disposal_ = GestureDisposal::ACCEPT;
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer.OnBlocked();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case4: recognizers_ is not empty, disposal is PENDING
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.disposal_ = GestureDisposal::PENDING;
    sequencedRecognizer.OnBlocked();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case5: recognizers_ is not empty nullptr, disposal is ACCEPT
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.disposal_ = GestureDisposal::ACCEPT;
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(nullptr);
    sequencedRecognizer.OnBlocked();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::SUCCEED_BLOCKED);

    /**
     * @tc.steps: step2. call OnBlocked function and compare result.
     * @tc.steps: case6: recognizers_ is not empty nullptr, disposal is PENDING
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.disposal_ = GestureDisposal::PENDING;
    sequencedRecognizer.OnBlocked();
    EXPECT_EQ(sequencedRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);
}

/**
 * @tc.name: SequencedRecognizerTest005
 * @tc.desc: Test SequencedRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    bool result = false;
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case1: currentIndex = 0
     * @tc.expected: step2. result equals.
     */
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
    //  * @tc.steps: step2. call HandleEvent function and compare result.
    //  * @tc.steps: case2: currentIndex = 1, prevState = SUCCESS
    //  * @tc.expected: step2. result equals.
    //  */
    sequencedRecognizer.currentIndex_ = 1;
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case3: currentIndex = 1, prevState = READY
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.currentIndex_ = 1;
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SequencedRecognizerTest006
 * @tc.desc: Test SequencedRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    bool result = false;
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case4: point.type = DOWN, size = 1
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::DOWN;
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case5: point.type = MOVE
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::MOVE;
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case6: point.type = UP
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::UP;
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case7: point.type = CANCEL
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::CANCEL;
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SequencedRecognizerTest007
 * @tc.desc: Test SequencedRecognizer function: HandleEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    bool result = false;
    TouchEvent touchEvent;

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case8: point.type = UNKOWN
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::UNKNOWN;
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case9: point.type = UP and refereeState = PENDING
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::UP;
    sequencedRecognizer.refereeState_ = RefereeState::PENDING;
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case10: point.type != UP and refereeState = PENDING
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::DOWN;
    sequencedRecognizer.refereeState_ = RefereeState::PENDING;
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call HandleEvent function and compare result.
     * @tc.steps: case11: point.type = DOWN, size > 1
     * @tc.expected: step2. result equals.
     */
    touchEvent.type = TouchType::DOWN;
    sequencedRecognizer.touchPoints_[0] = touchEvent;
    sequencedRecognizer.touchPoints_[1] = touchEvent;
    result = sequencedRecognizer.HandleEvent(touchEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SequencedRecognizerTest008
 * @tc.desc: Test SequencedRecognizer function: BatchAdjudicate, and GestureDisposal
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case1: disposal: ACCEPT, refereeState: SUCCEED
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    sequencedRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case2: disposal: ACCEPT, refereeState: PENDING, currentIndex = 0
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.currentIndex_ = 0;
    sequencedRecognizer.refereeState_ = RefereeState::PENDING;
    sequencedRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case3: disposal: REJECT, refereeState: FAIL
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    sequencedRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case4: disposal: REJECT, refereeState: SUCCESS, refereeState_ = FAIL
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.refereeState_ = RefereeState::FAIL;
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    sequencedRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case5: disposal: PENDING, refereeState: PENDING
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    sequencedRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step2. call GestureDisposal function and compare result.
     * @tc.steps: case5: disposal: PENDING, refereeState: SUCCESS, refereeState_: PENDING
     * @tc.expected: step2. result equals.
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    sequencedRecognizer.refereeState_ = RefereeState::PENDING;
    sequencedRecognizer.BatchAdjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(clickRecognizerPtr->refereeState_, RefereeState::PENDING);
}

/**
 * @tc.name: SequencedRecognizerHandleOverdueDeadlineTest001
 * @tc.desc: Test SequencedRecognizer function: HandleOverdueDeadline
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerHandleOverdueDeadlineTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call UpdateCurrentIndex function and compare result.
     * @tc.steps: case1: currentIndex != size - 1
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.currentIndex_ = 0;
    sequencedRecognizer.refereeState_ = RefereeState::SUCCEED;
    sequencedRecognizer.HandleOverdueDeadline();
    EXPECT_EQ(sequencedRecognizer.currentIndex_, 0);
}

/**
 * @tc.name: SequencedRecognizerTest009
 * @tc.desc: Test SequencedRecognizer function: UpdateCurrentIndex
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SequencedRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call UpdateCurrentIndex function and compare result.
     * @tc.steps: case1: currentIndex == size - 1
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.currentIndex_ = -1;
    sequencedRecognizer.UpdateCurrentIndex();
    EXPECT_EQ(sequencedRecognizer.currentIndex_, -1);

    /**
     * @tc.steps: step2. call UpdateCurrentIndex function and compare result.
     * @tc.steps: case1: currentIndex != size - 1
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.currentIndex_ = 0;
    sequencedRecognizer.UpdateCurrentIndex();
    EXPECT_EQ(sequencedRecognizer.currentIndex_, 1);
}

/**
 * @tc.name: SequencedRecognizerTest010
 * @tc.desc: Test SequencedRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SequencedRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    SequencedRecognizer sequencedRecognizer = SequencedRecognizer(recognizers);
    RefPtr<SequencedRecognizer> sequencedRecognizerPtr = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    bool result = false;

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case1: recognizer is nullptr
     * @tc.expected: step2. result equals.
     */
    result = sequencedRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case2: size not same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(nullptr);
    sequencedRecognizer.priorityMask_ = GestureMask::Begin;
    result = sequencedRecognizer.ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case3: size not same, priorityMask same
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(nullptr);
    sequencedRecognizer.priorityMask_ = GestureMask::Normal;
    result = sequencedRecognizer.ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: size same, priorityMask not same
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.priorityMask_ = GestureMask::Begin;
    result = sequencedRecognizer.ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: size same, priorityMask same, child is nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(nullptr);
    sequencedRecognizerPtr->recognizers_.clear();
    sequencedRecognizerPtr->recognizers_.push_back(nullptr);
    sequencedRecognizer.priorityMask_ = GestureMask::Normal;
    result = sequencedRecognizer.ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: size same, priorityMask same, child is ptr
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizerPtr->recognizers_.clear();
    sequencedRecognizerPtr->recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizer.priorityMask_ = GestureMask::Normal;
    result = sequencedRecognizer.ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: size same, priorityMask same, child is ptr and nullptr
     * @tc.expected: step2. result equals.
     */
    sequencedRecognizer.recognizers_.clear();
    sequencedRecognizer.recognizers_.push_back(clickRecognizerPtr);
    sequencedRecognizerPtr->recognizers_.clear();
    sequencedRecognizerPtr->recognizers_.push_back(nullptr);
    sequencedRecognizer.priorityMask_ = GestureMask::Normal;
    result = sequencedRecognizer.ReconcileFrom(sequencedRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: SwipeRecognizerTest001
 * @tc.desc: Test SwipeRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.OnAccepted();
    EXPECT_EQ(swipeRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    swipeRecognizer.OnRejected();
    EXPECT_EQ(swipeRecognizer.refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: SwipeRecognizerTest002
 * @tc.desc: Test SwipeRecognizer function: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchDown function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    swipeRecognizer.fingers_ = 1;
    swipeRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);
    EXPECT_EQ(swipeRecognizer.refereeState_, RefereeState::DETECTING);

    AxisEvent axisEvent;
    swipeRecognizer.HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer.axisVerticalTotal_, 0.0);
    EXPECT_EQ(swipeRecognizer.axisHorizontalTotal_, 0.0);
    EXPECT_EQ(swipeRecognizer.refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: SwipeRecognizerTest003
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchUp function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), axisEvent.y);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchUpEventTest001
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchUpEventTest002
 * @tc.desc: Test SwipeRecognizer function: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerHandleTouchUpEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchUp function
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), axisEvent.y);

    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), axisEvent.y);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer.axisVerticalTotal_, 0);
    EXPECT_EQ(swipeRecognizer.axisHorizontalTotal_, 0);
}

/**
 * @tc.name: SwipeRecognizerTest004
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.x = 0;
    touchEvent.y = 1;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), 0);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    swipeRecognizer.refereeState_ = RefereeState::DETECTING;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), 0);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer.refereeState_ = RefereeState::DETECTING;
    swipeRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), axisEvent.y);
    EXPECT_EQ(swipeRecognizer.axisVerticalTotal_, 0);
    EXPECT_EQ(swipeRecognizer.axisHorizontalTotal_, 0);
}

/**
 * @tc.name: SwipeRecognizerTest005
 * @tc.desc: Test SwipeRecognizer function: CheckAngle
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case1: prevAngle has value, prevAngle - angle > 45
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    auto result = swipeRecognizer.CheckAngle(0);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case2: prevAngle has value, prevAngle - angle < 45
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    result = swipeRecognizer.CheckAngle(VERTICAL_ANGLE);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case2: prevAngle has no value, direction is HORIZONTAL, angle > 45
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.prevAngle_ = std::optional<double>();
    swipeRecognizer.direction_.type = SwipeDirection::HORIZONTAL;
    result = swipeRecognizer.CheckAngle(VERTICAL_ANGLE);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case3: prevAngle has no value, direction is HORIZONTAL, angle < 45
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.prevAngle_ = std::optional<double>();
    swipeRecognizer.direction_.type = SwipeDirection::HORIZONTAL;
    result = swipeRecognizer.CheckAngle(0);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case4: prevAngle has no value, direction is VERTICAL, angle > 135
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    swipeRecognizer.direction_.type = SwipeDirection::VERTICAL;
    result = swipeRecognizer.CheckAngle(HORIZONTAL_ANGLE);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.steps: case5: prevAngle has no value, direction is VERTICAL, angle < 135
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    swipeRecognizer.direction_.type = SwipeDirection::VERTICAL;
    result = swipeRecognizer.CheckAngle(VERTICAL_ANGLE);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchMoveEventTest002
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerHandleTouchMoveEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.x = 0;
    touchEvent.y = 1;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), 0);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    swipeRecognizer.refereeState_ = RefereeState::DETECTING;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer.axisVerticalTotal_, 0);
    EXPECT_EQ(swipeRecognizer.axisHorizontalTotal_, 0);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchMoveEventTest003
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerHandleTouchMoveEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.x = 0;
    touchEvent.y = -1;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), 0);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), 0);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    swipeRecognizer.refereeState_ = RefereeState::DETECTING;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer.axisVerticalTotal_, 0);
    EXPECT_EQ(swipeRecognizer.axisHorizontalTotal_, 0);
}

/**
 * @tc.name: SwipeRecognizerHandleTouchMoveEventTest004
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerHandleTouchMoveEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.x = -1;
    touchEvent.y = -1;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    swipeRecognizer.refereeState_ = RefereeState::DETECTING;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.currentFingers_ = swipeRecognizer.fingers_;
    swipeRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(swipeRecognizer.axisVerticalTotal_, 0);
    EXPECT_EQ(swipeRecognizer.axisHorizontalTotal_, 0);
}

/**
 * @tc.name: SwipeRecognizerTest006
 * @tc.desc: Test SwipeRecognizer function: OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call OnResetStatus function
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.OnResetStatus();
    EXPECT_EQ(swipeRecognizer.axisHorizontalTotal_, 0.0);
    EXPECT_EQ(swipeRecognizer.axisVerticalTotal_, 0.0);
    EXPECT_EQ(swipeRecognizer.resultSpeed_, 0.0);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), 0.0);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), 0.0);
}

/**
 * @tc.name: SwipeRecognizerTest007
 * @tc.desc: Test SwipeRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    RefPtr<SwipeRecognizer> swipeRecognizerPtr =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case1: input is nullptr
     * @tc.expected: step2. result equals.
     */
    auto result = swipeRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case2: input is same
     * @tc.expected: step2. result equals.
     */
    result = swipeRecognizer.ReconcileFrom(swipeRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case3: curr->fingers != fingers
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.fingers_ = swipeRecognizerPtr->fingers_ + 1;
    result = swipeRecognizer.ReconcileFrom(swipeRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case4: curr->fingers = fingers, direction type not same
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.fingers_ = swipeRecognizerPtr->fingers_;
    swipeRecognizer.direction_.type = SwipeDirection::HORIZONTAL;
    result = swipeRecognizer.ReconcileFrom(swipeRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.steps: case5:direction type is same, speed is not same
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.fingers_ = swipeRecognizerPtr->fingers_;
    swipeRecognizer.direction_.type = swipeRecognizerPtr->direction_.type;
    swipeRecognizer.speed_ = 1;
    result = swipeRecognizer.ReconcileFrom(swipeRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: SwipeRecognizerTest008
 * @tc.desc: Test SwipeRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.refereeState_ = RefereeState::SUCCEED;
    TouchEvent touchEvent;
    swipeRecognizer.HandleTouchCancelEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: SwipeRecognizerTest009
 * @tc.desc: Test SwipeRecognizer function: SendCallbackMsg
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, SwipeRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer = SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case1: callback is null
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.SendCallbackMsg(nullptr);
    EXPECT_EQ(swipeRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case2: callback is ptr, have no tiltX and tileY
     * @tc.expected: step2. result equals.
     */
    std::unique_ptr<GestureEventFunc> onAction;
    TouchEvent touchEvent1;
    swipeRecognizer.deviceType_ = SourceType::MOUSE;
    swipeRecognizer.lastTouchEvent_ = touchEvent1;
    swipeRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(swipeRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case3: callback is ptr, have tiltX and no tileY
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent2;
    touchEvent2.tiltX = 0;
    swipeRecognizer.deviceType_ = SourceType::TOUCH;
    swipeRecognizer.lastTouchEvent_ = touchEvent2;
    swipeRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(swipeRecognizer.touchPoints_.size(), 0);

    /**
     * @tc.steps: step2. call SendCallbackMsg function and compare result.
     * @tc.steps: case4: callback is ptr, have tiltX and tileY
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent3;
    touchEvent3.tiltX = 0;
    touchEvent3.tiltY = 0;
    swipeRecognizer.deviceType_ = SourceType::TOUCH;
    swipeRecognizer.lastTouchEvent_ = touchEvent3;
    swipeRecognizer.prevAngle_ = std::make_optional(0);
    swipeRecognizer.SendCallbackMsg(onAction);
    EXPECT_EQ(swipeRecognizer.touchPoints_.size(), 0);
}

/**
 * @tc.name: GestureGroupTest001
 * @tc.desc: Test GestureGroup CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, GestureGroupTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureGroup.
     */
    GestureGroupModelNG gestureGroupModelNG;
    gestureGroupModelNG.Create(0);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(gestureGroupNG->mode_, GestureMode::Sequence);

    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: GestureMode::Begin
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Begin;
    auto groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: GestureMode::Sequence
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Sequence;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
    EXPECT_EQ(groupRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case3: GestureMode::Parallel
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Parallel;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
    EXPECT_EQ(groupRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case4: GestureMode::Exclusive
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Exclusive;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
    EXPECT_EQ(groupRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case5: GestureMode::End
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::End;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case6: GestureMode::Sequence, have onActionCancelId_
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Sequence;
    std::unique_ptr<GestureEventNoParameter> onActionCancelId;
    gestureGroup.onActionCancelId_ = std::move(onActionCancelId);
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
}

/**
 * @tc.name: GestureGroupCreateRecognizerTest001
 * @tc.desc: Test GestureGroup CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, GestureGroupCreateRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureGroup.
     */
    GestureGroupModelNG gestureGroupModelNG;
    gestureGroupModelNG.Create(0);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(gestureGroupNG->mode_, GestureMode::Sequence);

    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: GestureMode::Begin
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Begin;
    auto groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: GestureMode::Sequence
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Sequence;
    auto onActionCancel = []() { return true; };
    gestureGroup.SetOnActionCancelId(onActionCancel);
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
    EXPECT_EQ(groupRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);
}

/**
 * @tc.name: GestureRefereeTest001
 * @tc.desc: Test GestureReferee Existed function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case1: input is ptr, have input
     * @tc.steps: expected equal
     */
    auto result = gestureScope.Existed(clickRecognizerPtr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case2: input is nullptr
     * @tc.steps: expected equal
     */
    result = gestureScope.Existed(nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case3: recognizers is empty
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    result = gestureScope.Existed(clickRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRefereeTest002
 * @tc.desc: Test GestureReferee CheckNeedBlocked function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case1: member == input
     * @tc.steps: expected equal
     */
    auto result = gestureScope.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case1: member != input, refereeState is PENDING
     * @tc.steps: expected equal
     */
    RefPtr<ClickRecognizer> clickRecognizerPtrNotInsert = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    result = gestureScope.CheckNeedBlocked(clickRecognizerPtrNotInsert);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: case3: recognizers is empty
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    result = gestureScope.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRefereeTest003
 * @tc.desc: Test GestureReferee OnAcceptGesture function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case1: gesture == recognizer
     * @tc.steps: expected equal
     */
    gestureScope.OnAcceptGesture(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case2: gesture != recognizer
     * @tc.steps: expected equal
     */
    RefPtr<ClickRecognizer> clickRecognizerPtrNotInsert = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.OnAcceptGesture(clickRecognizerPtrNotInsert);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case3: recognizers is empty
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    gestureScope.OnAcceptGesture(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case4: recognizers have nullptr
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), nullptr);
    gestureScope.OnAcceptGesture(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);
}

/**
 * @tc.name: GestureRefereeTest004
 * @tc.desc: Test GestureReferee OnBlockGesture function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call UnBlockGesture function and compare result
     * @tc.steps: expected equal
     */
    auto result = gestureScope.UnBlockGesture();
    EXPECT_EQ(result, nullptr);

    clickRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    result = gestureScope.UnBlockGesture();
    EXPECT_EQ(result, clickRecognizerPtr);
}

/**
 * @tc.name: GestureRefereeTest005
 * @tc.desc: Test GestureReferee IsPending function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call IsPending function and compare result
     * @tc.steps: expected equal
     */
    auto result = gestureScope.IsPending(0);
    EXPECT_EQ(result, false);

    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    result = gestureScope.IsPending(0);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GestureRefereeTest006
 * @tc.desc: Test GestureReferee AddGestureToScope function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureReferee.
     */
    GestureReferee gestureReferee;

    /**
     * @tc.steps: step2. call AddGestureToScope function and compare result
     * @tc.steps: case1: cannot find touchId
     * @tc.steps: expected equal
     */
    TouchTestResult touchTestResult;
    gestureReferee.AddGestureToScope(0, touchTestResult);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call AddGestureToScope function and compare result
     * @tc.steps: case2: can find touchId, result is empty
     * @tc.steps: expected equal
     */
    gestureReferee.gestureScopes_.clear();
    gestureReferee.gestureScopes_[0] = AceType::MakeRefPtr<GestureScope>(0);
    gestureReferee.AddGestureToScope(0, touchTestResult);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call AddGestureToScope function and compare result
     * @tc.steps: case3: can find touchId, result have nullptr
     * @tc.steps: expected equal
     */
    touchTestResult.insert(touchTestResult.end(), nullptr);
    gestureReferee.AddGestureToScope(0, touchTestResult);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call AddGestureToScope function and compare result
     * @tc.steps: case4: can find touchId, result have ptr
     * @tc.steps: expected equal
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    touchTestResult.clear();
    touchTestResult.insert(touchTestResult.end(), clickRecognizerPtr);
    gestureReferee.AddGestureToScope(0, touchTestResult);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest007
 * @tc.desc: Test GestureReferee CleanGestureScope function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureReferee.
     */
    GestureReferee gestureReferee;

    /**
     * @tc.steps: step2. call CleanGestureScope function and compare result
     * @tc.steps: case1: gestureScope is empty
     * @tc.steps: expected equal
     */
    gestureReferee.CleanGestureScope(0);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call CleanGestureScope function and compare result
     * @tc.steps: case2: gestureScope is not empty, scope is not PENDING
     * @tc.steps: expected equal
     */
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.CleanGestureScope(0);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call CleanGestureScope function and compare result
     * @tc.steps: case3: gestureScope is not empty, scope is PENDING
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.CleanGestureScope(0);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest008
 * @tc.desc: Test GestureReferee AddMember function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call AddMember function and compare result
     * @tc.steps: case1: is existed
     * @tc.steps: expected equal
     */
    gestureScope.AddMember(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call AddMember function and compare result
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    gestureScope.AddMember(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.recognizers_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest009
 * @tc.desc: Test GestureReferee Close function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call Close function and compare result
     * @tc.steps: case1: have ptr
     * @tc.steps: expected equal
     */
    gestureScope.Close();
    EXPECT_EQ(gestureScope.recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case2: recognizers_ is empty
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    gestureScope.Close();
    EXPECT_EQ(gestureScope.recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: case3: recognizers_ have nullptr
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), nullptr);
    gestureScope.Close();
    EXPECT_EQ(gestureScope.recognizers_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest010
 * @tc.desc: Test GestureReferee Adjudicate function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: disposal is ACCEPT
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.Adjudicate(clickRecognizerPtr, GestureDisposal::ACCEPT);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: disposal is PENDING
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.Adjudicate(clickRecognizerPtr, GestureDisposal::PENDING);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: disposal is REJECT
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.Adjudicate(clickRecognizerPtr, GestureDisposal::REJECT);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case4: disposal is NONE
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.Adjudicate(clickRecognizerPtr, GestureDisposal::NONE);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);
}

/**
 * @tc.name: GestureRefereeTest011
 * @tc.desc: Test GestureReferee HandleAcceptDisposal function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is SUCCEED
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: refereeState is PENDING, gestureScopes_ is empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: refereeState is PENDING, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case4: refereeState is PENDING, gestureScopes_ is not empty, isDelay
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureScope->isDelay_ = true;
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case5: refereeState is PENDING, gestureScopes_ is not empty, !isDelay
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureScope->isDelay_ = false;
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case6: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    gestureReferee.HandleAcceptDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest012
 * @tc.desc: Test GestureReferee HandlePendingDisposal function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is PENDING
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureReferee.HandlePendingDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: refereeState is SUCCEED, gestureScopes_ is empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    gestureReferee.HandlePendingDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: refereeState is SUCCEED, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandlePendingDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest013
 * @tc.desc: Test GestureReferee HandleRejectDisposal function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: refereeState is FAIL
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case2: refereeState is PENDING, gestureScopes_ is empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case3: refereeState is PENDING, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case4: refereeState is PENDING_BLOCKED, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING_BLOCKED;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case5: refereeState is SUCCEED_BLOCKED, gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case6: refereeState is PENDING, gestureScopes_ is not empty, isDelay
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureScope->isDelay_ = true;
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case7: refereeState is PENDING, gestureScopes_ is not empty, isDelay
     * @tc.steps: expected equal
     */
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    gestureScope->recognizers_.clear();
    gestureScope->recognizers_.insert(gestureScope->recognizers_.end(), clickRecognizerPtr);
    gestureScope->isDelay_ = false;
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.HandleRejectDisposal(clickRecognizerPtr);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest014
 * @tc.desc: Test GestureReferee HasGestureAccepted function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    bool result = false;

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: gestureScopes_ is not empty
     * @tc.steps: expected equal
     */
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureReferee.gestureScopes_[0] = gestureScope;
    result = gestureReferee.HasGestureAccepted(0);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call Adjudicate function and compare result
     * @tc.steps: case1: gestureScopes_ is empty
     * @tc.steps: expected equal
     */
    gestureReferee.gestureScopes_.clear();
    result = gestureReferee.HasGestureAccepted(0);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRefereeTest015
 * @tc.desc: Test GestureReferee QueryAllDone function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call QueryAllDone function
     * @tc.steps: expected equal
     */
    gestureScope.AddMember(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.recognizers_.size(), 1);
    gestureScope.QueryAllDone(0);

    /**
     * @tc.steps: step2. call QueryAllDone function
     * @tc.steps: expected equal
     */
    gestureScope.recognizers_.clear();
    gestureScope.AddMember(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.recognizers_.size(), 1);
    gestureScope.QueryAllDone(1);
}

/**
 * @tc.name: GestureRefereeTest016
 * @tc.desc: Test GestureReferee QueryAllDone function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    bool result = false;

    /**
     * @tc.steps: step2. call QueryAllDone function
     * @tc.steps: expected equal
     */
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureReferee.gestureScopes_[0] = gestureScope;
    result = gestureReferee.QueryAllDone(0);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GestureRefereeTest017
 * @tc.desc: Test GestureReferee CleanAll function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;

    /**
     * @tc.steps: step2. call CleanAll() function
     * @tc.steps: expected equal
     */
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureReferee.gestureScopes_[0] = gestureScope;
    gestureReferee.CleanAll();
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);
}

/**
 * @tc.name: GestureRefereeTest018
 * @tc.desc: Test GestureReferee CheckSourceTypeChange function
 */
HWTEST_F(GesturesTestNg, GestureRefereeTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureReferee gestureReferee;
    bool result = false;

    /**
     * @tc.steps: step2. call CheckSourceTypeChange function
     * @tc.steps: expected equal
     */
    RefPtr<GestureScope> gestureScope = AceType::MakeRefPtr<GestureScope>(0);
    gestureReferee.gestureScopes_[0] = gestureScope;
    result = gestureReferee.CheckSourceTypeChange(SourceType::TOUCH, false);
    EXPECT_EQ(result, true);
    result = gestureReferee.CheckSourceTypeChange(SourceType::TOUCH, true);
    EXPECT_EQ(result, true);
    gestureReferee.lastSourceType_ = SourceType::TOUCH;
    result = gestureReferee.CheckSourceTypeChange(SourceType::TOUCH, false);
    EXPECT_EQ(result, true);
    result = gestureReferee.CheckSourceTypeChange(SourceType::TOUCH, true);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: LongPressGestureTest001
 * @tc.desc: Test LongPressGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, LongPressGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressGesture.
     */
    LongPressGestureModelNG longPressGestureModelNG;
    longPressGestureModelNG.Create(FINGER_NUMBER, false, LONG_PRESS_DURATION);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto longPressGestureNG = AceType::DynamicCast<NG::LongPressGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(longPressGestureNG->duration_, LONG_PRESS_DURATION);

    LongPressGesture longPressGesture = LongPressGesture(FINGER_NUMBER, false, LONG_PRESS_DURATION, false, false);
    EXPECT_EQ(longPressGesture.repeat_, false);
    EXPECT_EQ(longPressGesture.duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressGesture.isForDrag_, false);
    EXPECT_EQ(longPressGesture.isDisableMouseLeft_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
    EXPECT_EQ(longPressRecognizer->duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressRecognizer->isForDrag_, false);
    EXPECT_EQ(longPressRecognizer->isDisableMouseLeft_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: onActionId, onActionEndId, onActionCancelId existed
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventNoParameter> onActionCancelId;
    longPressGesture.onActionId_ = std::move(onActionId);
    longPressGesture.onActionEndId_ = std::move(onActionEndId);
    longPressGesture.onActionCancelId_ = std::move(onActionCancelId);
    longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
    EXPECT_EQ(longPressRecognizer->duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressRecognizer->isForDrag_, false);
    EXPECT_EQ(longPressRecognizer->isDisableMouseLeft_, false);
}

/**
 * @tc.name: LongPressGestureCreateRecognizerTest001
 * @tc.desc: Test LongPressGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, LongPressGestureCreateRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressGesture.
     */
    LongPressGestureModelNG longPressGestureModelNG;
    longPressGestureModelNG.Create(FINGER_NUMBER, false, LONG_PRESS_DURATION);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto longPressGestureNG = AceType::DynamicCast<NG::LongPressGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(longPressGestureNG->duration_, LONG_PRESS_DURATION);

    LongPressGesture longPressGesture = LongPressGesture(FINGER_NUMBER, false, LONG_PRESS_DURATION, false, false);
    EXPECT_EQ(longPressGesture.repeat_, false);
    EXPECT_EQ(longPressGesture.duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressGesture.isForDrag_, false);
    EXPECT_EQ(longPressGesture.isDisableMouseLeft_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    longPressGesture.fingers_ = FINGER_NUMBER_OVER_MAX;
    longPressGesture.duration_ = 0;
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    longPressGesture.fingers_ = 0;
    longPressGesture.duration_ = 0;
    longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
}


/**
 * @tc.name: LongPressGestureCreateRecognizerTest002
 * @tc.desc: Test LongPressGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, LongPressGestureCreateRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressGesture.
     */
    LongPressGestureModelNG longPressGestureModelNG;
    longPressGestureModelNG.Create(FINGER_NUMBER, false, LONG_PRESS_DURATION);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto longPressGestureNG = AceType::DynamicCast<NG::LongPressGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(longPressGestureNG->duration_, LONG_PRESS_DURATION);

    LongPressGesture longPressGesture = LongPressGesture(FINGER_NUMBER, false, LONG_PRESS_DURATION, false, false);
    EXPECT_EQ(longPressGesture.repeat_, false);
    EXPECT_EQ(longPressGesture.duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressGesture.isForDrag_, false);
    EXPECT_EQ(longPressGesture.isDisableMouseLeft_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    longPressGesture.fingers_ = FINGER_NUMBER_OVER_MAX;
    longPressGesture.duration_ = 0;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = []() { return true; };
    longPressGesture.SetOnActionId(onActionStart);
    longPressGesture.SetOnActionEndId(onActionEnd);
    longPressGesture.SetOnActionCancelId(onActionCancel);
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    longPressGesture.fingers_ = 0;
    longPressGesture.duration_ = 0;
    longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
}

/**
 * @tc.name: SwipeGestureTest001
 * @tc.desc: Test SwipeGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, SwipeGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeGesture.
     */
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;
    SwipeDirection slideDirection;
    SwipeGestureModelNG swipeGestureModelNG;
    swipeGestureModelNG.Create(fingersNum, slideDirection, speedNum);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto swipeGestureNG = AceType::DynamicCast<NG::SwipeRecognizer>(gestureProcessor->TopGestureNG());

    SwipeGesture swipeGesture = SwipeGesture(fingersNum, slideDirection, speedNum);
    EXPECT_EQ(swipeGesture.speed_, DEFAULT_SLIDE_SPEED);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    auto swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_EQ(swipeGesture.speed_, DEFAULT_SLIDE_SPEED);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: onActionId, onActionEndId, onActionCancelId existed
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventNoParameter> onActionCancelId;
    swipeGesture.onActionId_ = std::move(onActionId);
    swipeGesture.onActionEndId_ = std::move(onActionEndId);
    swipeGesture.onActionCancelId_ = std::move(onActionCancelId);
    swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_EQ(swipeGesture.speed_, DEFAULT_SLIDE_SPEED);
}

/**
 * @tc.name: SwipeGestureCreateRecognizerTest001
 * @tc.desc: Test SwipeGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, SwipeGestureCreateRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeGesture.
     */
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;
    SwipeDirection slideDirection;
    SwipeGestureModelNG swipeGestureModelNG;
    swipeGestureModelNG.Create(fingersNum, slideDirection, speedNum);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto swipeGestureNG = AceType::DynamicCast<NG::SwipeRecognizer>(gestureProcessor->TopGestureNG());

    SwipeGesture swipeGesture = SwipeGesture(fingersNum, slideDirection, speedNum);
    EXPECT_EQ(swipeGesture.speed_, DEFAULT_SLIDE_SPEED);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: onActionId, onActionEndId, onActionCancelId not existed
     */
    auto swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_EQ(swipeGesture.speed_, DEFAULT_SLIDE_SPEED);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: onActionId, onActionEndId, onActionCancelId existed
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventNoParameter> onActionCancelId;
    swipeGesture.onActionId_ = std::move(onActionId);
    swipeGesture.onActionEndId_ = std::move(onActionEndId);
    swipeGesture.onActionCancelId_ = std::move(onActionCancelId);
    auto onActionStart = [](GestureEvent& info) { return true; };
    swipeGesture.SetOnActionId(onActionStart);
    swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(swipeGesture.CreateRecognizer());
    EXPECT_EQ(swipeGesture.speed_, DEFAULT_SLIDE_SPEED);
}

/**
 * @tc.name: PinchGestureTest001
 * @tc.desc: Test PinchGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, PinchGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchGestureGesture.
     */
    PinchGestureModelNG pinchGestureModelNG;
    pinchGestureModelNG.Create(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto pinchGesture = AceType::DynamicCast<NG::PinchGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(pinchGesture->distance_, PINCH_GESTURE_DISTANCE);
}

/**
 * @tc.name: RotationGestureTest001
 * @tc.desc: Test RotationGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, RotationGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationGestureGesture.
     */
    RotationGestureModelNG rotationGestureModelNG;
    rotationGestureModelNG.Create(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto rotationGestureNG = AceType::DynamicCast<NG::RotationGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(rotationGestureNG->angle_, ROTATION_GESTURE_ANGLE);

    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    EXPECT_EQ(rotationGesture.angle_, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: functions are not existed
     */
    rotationGesture.priority_ = GesturePriority::Low;
    rotationGesture.gestureMask_ = GestureMask::Normal;
    auto rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_NE(rotationRecognizer, nullptr);
    EXPECT_EQ(rotationRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(rotationRecognizer->GetPriorityMask(), GestureMask::Normal);

    // /**
    //  * @tc.steps: step2. call CreateRecognizer function and compare result
    //  * @tc.steps: case2: functions are existed
    //  */
    std::unique_ptr<GestureEventFunc> onActionStartId;
    std::unique_ptr<GestureEventFunc> onActionUpdateId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventNoParameter> onActionCancelId;
    rotationGesture.onActionStartId_ = std::move(onActionStartId);
    rotationGesture.onActionUpdateId_ = std::move(onActionUpdateId);
    rotationGesture.onActionEndId_ = std::move(onActionEndId);
    rotationGesture.onActionCancelId_ = std::move(onActionCancelId);
    rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_EQ(rotationRecognizer->priority_, rotationGesture.priority_);
    EXPECT_EQ(rotationRecognizer->priorityMask_, rotationGesture.gestureMask_);
}

/**
 * @tc.name: RotationGestureCreateRecognizerTest001
 * @tc.desc: Test RotationGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, RotationGestureCreateRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationGestureGesture.
     */
    RotationGestureModelNG rotationGestureModelNG;
    rotationGestureModelNG.Create(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto rotationGestureNG = AceType::DynamicCast<NG::RotationGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(rotationGestureNG->angle_, ROTATION_GESTURE_ANGLE);

    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, 0.0);
    EXPECT_EQ(rotationGesture.angle_, ROTATION_GESTURE_ANGLE);
    RotationGesture rotationGestureTwo = RotationGesture(FINGER_NUMBER, -1.0);
    EXPECT_EQ(rotationGestureTwo.angle_, ROTATION_GESTURE_ANGLE);
    RotationGesture rotationGestureThree = RotationGesture(FINGER_NUMBER, 361.0);
    EXPECT_EQ(rotationGestureThree.angle_, ROTATION_GESTURE_ANGLE);
}


/**
 * @tc.name: RotationGestureCreateRecognizerTest002
 * @tc.desc: Test RotationGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, RotationGestureCreateRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationGestureGesture.
     */
    RotationGestureModelNG rotationGestureModelNG;
    rotationGestureModelNG.Create(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto rotationGestureNG = AceType::DynamicCast<NG::RotationGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(rotationGestureNG->angle_, ROTATION_GESTURE_ANGLE);

    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    EXPECT_EQ(rotationGesture.angle_, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: functions are not existed
     */
    rotationGesture.priority_ = GesturePriority::Low;
    rotationGesture.gestureMask_ = GestureMask::Normal;
    auto rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_NE(rotationRecognizer, nullptr);
    EXPECT_EQ(rotationRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(rotationRecognizer->GetPriorityMask(), GestureMask::Normal);

    // /**
    //  * @tc.steps: step2. call CreateRecognizer function and compare result
    //  * @tc.steps: case2: functions are existed
    //  */
    std::unique_ptr<GestureEventFunc> onActionStartId;
    std::unique_ptr<GestureEventFunc> onActionUpdateId;
    std::unique_ptr<GestureEventFunc> onActionEndId;
    std::unique_ptr<GestureEventNoParameter> onActionCancelId;
    rotationGesture.onActionStartId_ = std::move(onActionStartId);
    rotationGesture.onActionUpdateId_ = std::move(onActionUpdateId);
    rotationGesture.onActionEndId_ = std::move(onActionEndId);
    rotationGesture.onActionCancelId_ = std::move(onActionCancelId);
    rotationGesture.priority_ = GesturePriority::Low;
    rotationGesture.gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = []() { return true; };
    rotationGesture.SetOnActionStartId(onActionStart);
    rotationGesture.SetOnActionUpdateId(onActionUpdate);
    rotationGesture.SetOnActionEndId(onActionEnd);
    rotationGesture.SetOnActionCancelId(onActionCancel);
    rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_EQ(rotationRecognizer->priority_, rotationGesture.priority_);
    EXPECT_EQ(rotationRecognizer->priorityMask_, rotationGesture.gestureMask_);
}

/**
 * @tc.name: TapGestureTest001
 * @tc.desc: Test TapGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, TapGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TapGestureGesture.
     */
    TapGestureModelNG tapGestureModelNG;
    tapGestureModelNG.Create(COUNT, FINGER_NUMBER);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGestureNG = AceType::DynamicCast<NG::TapGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(tapGestureNG->count_, COUNT);

    TapGesture tapGesture = TapGesture(COUNT, FINGER_NUMBER);
    EXPECT_EQ(tapGesture.count_, COUNT);
    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: not have onActionId
     */
    tapGesture.priority_ = GesturePriority::Low;
    tapGesture.gestureMask_ = GestureMask::Normal;
    auto tapRecognizer = AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_NE(tapRecognizer, nullptr);
    EXPECT_EQ(tapRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(tapRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: have onActionId
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    tapGesture.onActionId_ = std::move(onActionId);
    tapRecognizer = AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_EQ(tapRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(tapRecognizer->GetPriorityMask(), GestureMask::Normal);
}

/**
 * @tc.name: TapGestureTest002
 * @tc.desc: Test TapGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, TapGestureTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TapGestureGesture.
     */
    TapGestureModelNG tapGestureModelNG;
    tapGestureModelNG.Create(COUNT, FINGER_NUMBER);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGestureNG = AceType::DynamicCast<NG::TapGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(tapGestureNG->count_, COUNT);

    TapGesture tapGesture = TapGesture(COUNT, FINGER_NUMBER);
    EXPECT_EQ(tapGesture.count_, COUNT);
    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: not have onActionId
     */
    tapGesture.priority_ = GesturePriority::Low;
    tapGesture.gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    tapGesture.SetOnActionId(onActionStart);
    auto tapRecognizer = AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_NE(tapRecognizer, nullptr);
    EXPECT_EQ(tapRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(tapRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: have onActionId
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    tapGesture.onActionId_ = std::move(onActionId);
    tapRecognizer = AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_EQ(tapRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(tapRecognizer->GetPriorityMask(), GestureMask::Normal);
}

/**
 * @tc.name: GestureTest001
 * @tc.desc: Test TapGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, GestureTest001, TestSize.Level1)
{
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(0, 0);
    gestureModelNG.Finish();
    gestureModelNG.Pop();

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    EXPECT_EQ(gestureProcessor->priority_, GesturePriority::Low);
    EXPECT_EQ(gestureProcessor->gestureMask_, GestureMask::Normal);

    PanGestureModelNG panGestureModelNG;
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    double distanceNum = DEFAULT_PAN_DISTANCE.ConvertToPx();
    PanDirection panDirection;
    panGestureModelNG.Create(fingersNum, panDirection, distanceNum);
    auto panGestureNG = AceType::DynamicCast<NG::PanGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(panGestureNG->distance_, distanceNum);

    RefPtr<PanGestureOption> refPanGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    panGestureModelNG.SetPanGestureOption(refPanGestureOption);

    TimeoutGestureModelNG timeoutGestureModelNG;
    timeoutGestureModelNG.GetGestureProcessor();

    SwipeGestureModelNG swipeGestureModelNG;
    fingersNum = DEFAULT_SLIDE_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;
    SwipeDirection slideDirection;
    swipeGestureModelNG.Create(fingersNum, slideDirection, speedNum);
    auto swipeGestureNG = AceType::DynamicCast<NG::SwipeGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(swipeGestureNG->speed_, speedNum);
}

/*
 * @tc.name: PanGestureTest001
 * @tc.desc: Test PanGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, PanGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanGesture.
     */
    auto panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    auto panGesture = AceType::MakeRefPtr<PanGesture>(panGestureOption);
    ASSERT_NE(panGesture, nullptr);
    EXPECT_EQ(panGesture->panGestureOption_->fingers_, panGestureOption->fingers_);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result.
     * @tc.expect: panRecognizer create successfully, use the same Option as panGesture.
     */
    panGesture->priority_ = GesturePriority::Low;
    panGesture->gestureMask_ = GestureMask::Normal;
    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(panGesture->CreateRecognizer());
    ASSERT_NE(panRecognizer, nullptr);
    EXPECT_EQ(panRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(panRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(panRecognizer->distance_, DEFAULT_PAN_DISTANCE.ConvertToPx());
}

/**
 * @tc.name: PanGestureTest002
 * @tc.desc: Test PanGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, PanGestureTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanGesture.
     */
    PanDirection panDirection;
    panDirection.type = PanDirection::RIGHT;
    auto panGesture = AceType::MakeRefPtr<PanGesture>(SINGLE_FINGER_NUMBER, panDirection, PAN_DISTANCE);
    ASSERT_NE(panGesture, nullptr);
    EXPECT_EQ(panGesture->fingers_, SINGLE_FINGER_NUMBER);

    /**
     * @tc.steps: step2. create onActionStart, onActionUpdate, onActionEnd, onActionCancel for PanRecognizer.
     * @tc.expect: panRecognizer create successfully with the OnActionCall.
     */
    panGesture->priority_ = GesturePriority::Low;
    panGesture->gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = []() { return true; };
    panGesture->SetOnActionStartId(onActionStart);
    panGesture->SetOnActionUpdateId(onActionUpdate);
    panGesture->SetOnActionEndId(onActionEnd);
    panGesture->SetOnActionCancelId(onActionCancel);
    EXPECT_TRUE(panGesture->onActionStartId_);
    EXPECT_TRUE(panGesture->onActionUpdateId_);
    EXPECT_TRUE(panGesture->onActionEndId_);
    EXPECT_TRUE(panGesture->onActionCancelId_);

    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(panGesture->CreateRecognizer());
    ASSERT_NE(panRecognizer, nullptr);
    EXPECT_EQ(panRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(panRecognizer->GetPriorityMask(), GestureMask::Normal);
}

/**
 * @tc.name: PinchGestureTest002
 * @tc.desc: Test PinchGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, PinchGestureTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchGesture.
     */
    auto pinchGesture = AceType::MakeRefPtr<PinchGesture>(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchGesture, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.expect: pinchRecognizer create successfully, use the same Option as pinchGesture.
     */
    pinchGesture->priority_ = GesturePriority::Low;
    pinchGesture->gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    auto onActionUpdate = [](GestureEvent& info) { return true; };
    auto onActionEnd = [](GestureEvent& info) { return true; };
    auto onActionCancel = []() { return true; };
    pinchGesture->SetOnActionStartId(onActionStart);
    pinchGesture->SetOnActionUpdateId(onActionUpdate);
    pinchGesture->SetOnActionEndId(onActionEnd);
    pinchGesture->SetOnActionCancelId(onActionCancel);
    EXPECT_TRUE(pinchGesture->onActionStartId_);
    EXPECT_TRUE(pinchGesture->onActionUpdateId_);
    EXPECT_TRUE(pinchGesture->onActionEndId_);
    EXPECT_TRUE(pinchGesture->onActionCancelId_);
    auto pinchRecognizer = AceType::DynamicCast<PinchRecognizer>(pinchGesture->CreateRecognizer());
    ASSERT_NE(pinchRecognizer, nullptr);
    EXPECT_EQ(pinchRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(pinchRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(pinchRecognizer->distance_, PINCH_GESTURE_DISTANCE);
}

/**
 * @tc.name: PinchGestureCreateRecognizerTest001
 * @tc.desc: Test PinchGesture CreateRecognizer function
 */
HWTEST_F(GesturesTestNg, PinchGestureCreateRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchGesture.
     */
    auto pinchGesture = AceType::MakeRefPtr<PinchGesture>(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchGesture, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.expect: pinchRecognizer create successfully, use the same Option as pinchGesture.
     */
    pinchGesture->priority_ = GesturePriority::Low;
    pinchGesture->gestureMask_ = GestureMask::Normal;
    auto pinchRecognizer = AceType::DynamicCast<PinchRecognizer>(pinchGesture->CreateRecognizer());
    ASSERT_NE(pinchRecognizer, nullptr);
    EXPECT_EQ(pinchRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(pinchRecognizer->GetPriorityMask(), GestureMask::Normal);
    EXPECT_EQ(pinchRecognizer->distance_, PINCH_GESTURE_DISTANCE);
}

/**
 * @tc.name: PinchRecognizerTest008
 * @tc.desc: Test PinchRecognizer function: IsCtrlBeingPressed
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER,
                                                                                   PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. use IsCtrlBeingPressed with no setting.
     * @tc.expect: IsCtrlBeingPressed return false.
     */
    EXPECT_FALSE(pinchRecognizer->IsCtrlBeingPressed());

    /**
     * @tc.steps: step3. create keyEvent and Set KeyEvent to pipeline.
     * @tc.expect: Set KeyCode KEY_CTRL_LEFT or KEY_CTRL_RIGHT , return True.
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_CTRL_LEFT;
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    std::vector<KeyCode> keyCodes { KeyCode::KEY_CTRL_LEFT };
    eventManager->SetPressedKeyCodes(keyCodes);
    context->SetEventManager(eventManager);
    EXPECT_TRUE(pinchRecognizer->IsCtrlBeingPressed());
    keyEvent.code = KeyCode::KEY_CTRL_RIGHT;
    EXPECT_TRUE(pinchRecognizer->IsCtrlBeingPressed());
}

/**
 * @tc.name: PinchRecognizerTest009
 * @tc.desc: Test PinchRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER,
                                                                                   PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. use fingers_ > MAX_PINCH_FINGERS in HandleTouchDownEvent(TouchEvent).
     * @tc.expect: pinchRecognizer->disposal_ is not equal to GestureDisposal::REJECT.
     */
    TouchEvent touchEvent;
    pinchRecognizer->fingers_ = FINGER_NUMBER_OVER_MAX;
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_NE(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3. test with HandleTouchDownEvent(AxisEvent).
     */
    pinchRecognizer->fingers_ = SINGLE_FINGER_NUMBER;
    AxisEvent axisEvent;

    /**
     * @tc.steps: step3.1. axisEvent NearZero and IsCtrlBeingPressed() is false.
     * @tc.expect: pinchRecognizer.disposal_ is not equal to GestureDisposal::REJECT.
     */
    axisEvent.pinchAxisScale = 0.0;
    pinchRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_TRUE(pinchRecognizer->IsCtrlBeingPressed());
    EXPECT_NE(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. axisEvent not NearZero and IsRefereeFinished() is true.
     * @tc.expect: pinchRecognizer->disposal_ is not equal to GestureDisposal::REJECT.
     */
    axisEvent.pinchAxisScale = 2.0;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_NE(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. axisEvent with refereeState_ = RefereeState::READY.
     * @tc.expect: pinchRecognizer->scale_ is equal to 1.0f.
     */
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->scale_, 1.0);
}

/**
 * @tc.name: PinchRecognizerTest010
 * @tc.desc: Test PinchRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER,
                                                                                   PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. use refereeState_ != RefereeState::SUCCEED and refereeState_ != RefereeState::FAIL.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    TouchEvent touchEvent;
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::NONE);

    /**
     * @tc.steps: step3. test with HandleTouchDownEvent(AxisEvent).
     */
    AxisEvent axisEvent;
    /**
     * @tc.steps: step3.1. test with isPinchEnd_ is true.
     */
    pinchRecognizer->isPinchEnd_ = true;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);

    /**
     * @tc.steps: step3.2. test with refereeState_ != RefereeState::SUCCEED and refereeState_ != RefereeState::FAIL.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. test with refereeState_ != RefereeState::SUCCEED.
     * @tc.expect: pinchRecognizer->isPinchEnd_ is true.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->isPinchEnd_, true);
}

/**
 * @tc.name: PinchRecognizerHandleTouchUpEventTest001
 * @tc.desc: Test PinchRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerHandleTouchUpEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER,
                                                                                   PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. use refereeState_ != RefereeState::SUCCEED and refereeState_ != RefereeState::FAIL.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    TouchEvent touchEvent;
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::FAIL;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    pinchRecognizer->refereeState_ = RefereeState::READY;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::NONE);

    /**
     * @tc.steps: step3. test with HandleTouchDownEvent(AxisEvent).
     */
    AxisEvent axisEvent;
    /**
     * @tc.steps: step3.1. test with isPinchEnd_ is true.
     */
    pinchRecognizer->isPinchEnd_ = true;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);

    /**
     * @tc.steps: step3.2. test with refereeState_ != RefereeState::SUCCEED and refereeState_ != RefereeState::FAIL.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. test with refereeState_ != RefereeState::SUCCEED.
     * @tc.expect: pinchRecognizer->isPinchEnd_ is true.
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->isPinchEnd_, true);
}

/**
 * @tc.name: PinchRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test PinchRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER,
                                                                                   PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. test HandleTouchMoveEvent(TouchEvent).
     */
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    std::vector<TouchEvent> touchEvents;
    for (std::size_t i = 0; i < 5; ++i) {
        TouchEvent touchEvent;
        touchEvent.x = 100.0 * (i + 1);
        touchEvent.y = 100.0 * (i + 1);
        pinchRecognizer->touchPoints_[i] = touchEvent;
    }
    pinchRecognizer->initialDev_ = 1.0;
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;

    /**
     * @tc.steps: step2.1. test HandleTouchMoveEvent(TouchEvent) with fabs(currentDev_ - initialDev_) >= distance_.
     * @tc.expect: scale_ = pinchRecognizer->ComputeAverageDeviation() / initialDev_.
     */
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);

    /**
     * @tc.steps: step2.2. test HandleTouchMoveEvent(TouchEvent) with refereeState_ == RefereeState::SUCCEED.
     * @tc.expect: scale_ = pinchRecognizer->ComputeAverageDeviation() / initialDev_
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->initialDev_ = 2.0;
    pinchRecognizer->OnFlushTouchEventsEnd();
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);

    /**
     * @tc.steps: step3. test HandleTouchMoveEvent(AxisEvent).
     */
    AxisEvent axisEvent;
    pinchRecognizer->isPinchEnd_ = false;

    /**
     * @tc.steps: step3.1. axisEvent NearZero and IsCtrlBeingPressed() is false.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    axisEvent.pinchAxisScale = 0.0;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->eventManager_ = nullptr;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. test with refereeState_ = RefereeState::SUCCEED.
     * @tc.expect: pinchRecognizer->refereeState_ is equal to RefereeState::READY.
     */
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->isPinchEnd_, true);

    /**
     * @tc.steps: step3.3. test with axisEvent not NearZero .
     * @tc.expect: pinchRecognizer->scale_ is equal to axisEvent.pinchAxisScale.
     */
    pinchRecognizer->isPinchEnd_ = false;
    axisEvent.pinchAxisScale = 1.0;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->currentFingers_ = FINGER_NUMBER;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->scale_, axisEvent.pinchAxisScale);
}

/**
 * @tc.name: PinchRecognizerHandleTouchCancelEventTest001
 * @tc.desc: Test PinchRecognizer function: HandleTouchCancelEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerHandleTouchCancelEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    AxisEvent axisEvent;
    axisEvent.pinchAxisScale = 0.0;

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer.refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer.HandleTouchMoveEvent(touchEvent);
    pinchRecognizer.HandleTouchUpEvent(touchEvent);
    pinchRecognizer.HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case2: input is AxisEvent
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case3: input is TouchEvent, isFlushTouchEventsEnd_
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer.isFlushTouchEventsEnd_ = true;
    pinchRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.steps: case4: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::FAIL;
    pinchRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case5: input is AxisEvent
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::FAIL;
    pinchRecognizer.HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case6: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::FAIL;
    pinchRecognizer.HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PinchRecognizerHandleTouchCancelEventTest002
 * @tc.desc: Test PinchRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerHandleTouchCancelEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    AxisEvent axisEvent;
    axisEvent.pinchAxisScale = 0.0;

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.steps: case1: input is TouchEvent
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer.refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer.HandleTouchMoveEvent(touchEvent);
    pinchRecognizer.currentFingers_ = pinchRecognizer.fingers_;
    pinchRecognizer.HandleTouchUpEvent(touchEvent);
    pinchRecognizer.HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case6: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer.isPinchEnd_ = true;
    pinchRecognizer.HandleTouchUpEvent(touchEvent);
    pinchRecognizer.HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);

    /**
     * @tc.steps: step2. call HandleTouchCancelEvent function and compare result.
     * @tc.steps: case6: input is TouchEvent, refereeState is FAIL
     * @tc.expected: step2. result equals.
     */
    pinchRecognizer.refereeState_ = RefereeState::FAIL;
    pinchRecognizer.isPinchEnd_ = false;
    pinchRecognizer.HandleTouchUpEvent(touchEvent);
    pinchRecognizer.HandleTouchCancelEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PinchRecognizerTest011
 * @tc.desc: Test PinchRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturesTestNg, PinchRecognizerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    RefPtr<PinchRecognizer> pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER,
                                                                                   PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizer, nullptr);

    /**
     * @tc.steps: step2. test HandleTouchMoveEvent(TouchEvent).
     */
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    std::vector<TouchEvent> touchEvents;
    for (std::size_t i = 0; i < 5; ++i) {
        TouchEvent touchEvent;
        touchEvent.x = 100.0 * (i + 1);
        touchEvent.y = 100.0 * (i + 1);
        pinchRecognizer->touchPoints_[i] = touchEvent;
    }
    pinchRecognizer->initialDev_ = 1.0;
    TouchEvent touchEvent;
    touchEvent.x = 100.0;
    touchEvent.y = 100.0;

    /**
     * @tc.steps: step2.1. test HandleTouchMoveEvent(TouchEvent) with fabs(currentDev_ - initialDev_) >= distance_.
     * @tc.expect: scale_ = pinchRecognizer->ComputeAverageDeviation() / initialDev_.
     */
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->scale_, 1);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::NONE);
    /**
     * @tc.steps: step2.2. test HandleTouchMoveEvent(TouchEvent) with refereeState_ == RefereeState::SUCCEED.
     * @tc.expect: scale_ = pinchRecognizer->ComputeAverageDeviation() / initialDev_
     */
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->initialDev_ = 2.0;
    pinchRecognizer->OnFlushTouchEventsEnd();
    pinchRecognizer->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer->scale_, 1);

    /**
     * @tc.steps: step3. test HandleTouchMoveEvent(AxisEvent).
     */
    AxisEvent axisEvent;
    pinchRecognizer->isPinchEnd_ = false;

    /**
     * @tc.steps: step3.1. axisEvent NearZero and IsCtrlBeingPressed() is false.
     * @tc.expect: pinchRecognizer->disposal_ is equal to GestureDisposal::REJECT.
     */
    axisEvent.pinchAxisScale = 0.0;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->eventManager_ = nullptr;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step3.2. test with refereeState_ = RefereeState::SUCCEED.
     * @tc.expect: pinchRecognizer->refereeState_ is equal to RefereeState::READY.
     */
    pinchRecognizer->isPinchEnd_ = false;
    pinchRecognizer->refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->refereeState_, RefereeState::READY);
    EXPECT_EQ(pinchRecognizer->isPinchEnd_, true);

    /**
     * @tc.steps: step3.3. test with axisEvent not NearZero .
     * @tc.expect: pinchRecognizer->scale_ is equal to axisEvent.pinchAxisScale.
     */
    pinchRecognizer->isPinchEnd_ = false;
    axisEvent.pinchAxisScale = 1.0;
    pinchRecognizer->refereeState_ = RefereeState::DETECTING;
    pinchRecognizer->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer->scale_, axisEvent.pinchAxisScale);
}

/**
 * @tc.name: GestureAccessibilityEventTest001
 * @tc.desc: Test SetOnAccessibility in ClickRecognizer
 */
HWTEST_F(GesturesTestNg, GestureAccessibilityEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create clickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(SINGLE_FINGER_NUMBER, TAPPED_COUNT);

    /**
     * @tc.steps: step2. set callback function.
     */
    auto onAccessibilityEvent = [](AccessibilityEventType eventType) {};
    clickRecognizer.SetOnAccessibility(onAccessibilityEvent);
    ASSERT_NE(clickRecognizer.onAccessibilityEventFunc_, nullptr);

    /**
     * @tc.steps: step3. call callback function.
     * @tc.expected: refereeState_ is SUCCEED.
     */
    clickRecognizer.OnAccepted();
    EXPECT_EQ(clickRecognizer.refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: GestureAccessibilityEventTest002
 * @tc.desc: Test SetOnAccessibility in LongPressRecognizer
 */
HWTEST_F(GesturesTestNg, GestureAccessibilityEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create longPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. set callback function.
     */
    auto onAccessibilityEvent = [](AccessibilityEventType eventType) {};
    longPressRecognizer.SetOnAccessibility(onAccessibilityEvent);
    ASSERT_NE(longPressRecognizer.onAccessibilityEventFunc_, nullptr);

    /**
     * @tc.steps: step3. call callback function.
     * @tc.expected: refereeState_ is SUCCEED.
     */
    longPressRecognizer.OnAccepted();
    EXPECT_EQ(longPressRecognizer.refereeState_, RefereeState::SUCCEED);
}
} // namespace OHOS::Ace::NG
