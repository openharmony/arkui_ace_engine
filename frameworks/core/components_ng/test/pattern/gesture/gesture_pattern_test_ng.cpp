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

#define private public
#define protected public

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/gestures/gesture_group.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/pinch_gesture.h"
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
} // namespace

class GesturePatternTestNg : public testing::Test {
public:
};

/**
 * @tc.name: GestureRecognizerTest001
 * @tc.desc: Test ClickRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, ClickRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
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
HWTEST_F(GesturePatternTestNg, ClickRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
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
HWTEST_F(GesturePatternTestNg, ClickRecognizerTest003, TestSize.Level1)
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
HWTEST_F(GesturePatternTestNg, ClickRecognizerTest004, TestSize.Level1)
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
    auto result = clickRecognizer.ExceedSlop();
    EXPECT_EQ(result, false);

    touchEvent.x = CLICK_MULTI_TAP_SLOP;
    touchEvent.y = CLICK_MULTI_TAP_SLOP;
    clickRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    clickRecognizer.tappedCount_ = TAPPED_COUNT;
    clickRecognizer.count_ = COUNT;
    result = clickRecognizer.ExceedSlop();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GestureRecognizerTest005
 * @tc.desc: Test ClickRecognizer function: ReconcileFrom
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, ClickRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);
    RefPtr<ClickRecognizer> clickRecognizerPtr =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call ComputeFocusPoint function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.touchPoints_.clear();
    clickRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    auto result = clickRecognizer.ReconcileFrom(clickRecognizerPtr);
    EXPECT_EQ(result, true);

    result = clickRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRecognizerTest006
 * @tc.desc: Test ClickRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, ClickRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.refereeState_ = RefereeState::SUCCEED;
    clickRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);

    clickRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizer.fingers_ = FINGER_NUMBER;
    clickRecognizer.currentTouchPointsNum_ = 0;
    clickRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.currentTouchPointsNum_, 1);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
}

/**
 * @tc.name: GestureRecognizerTest007
 * @tc.desc: Test ClickRecognizer function: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, ClickRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ClickRecognizer.
     */
    ClickRecognizer clickRecognizer = ClickRecognizer(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    clickRecognizer.currentTouchPointsNum_ = 0;
    clickRecognizer.refereeState_ = RefereeState::SUCCEED;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.touchPoints_.size(), 0);

    clickRecognizer.currentTouchPointsNum_ = 1;
    clickRecognizer.equalsToFingers_ = true;
    clickRecognizer.useCatchMode_ = false;
    clickRecognizer.refereeState_ = RefereeState::PENDING;
    clickRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(clickRecognizer.currentTouchPointsNum_, 0);
    EXPECT_EQ(clickRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
}

/**
 * @tc.name: ExclusiveRecognizerTest001
 * @tc.desc: Test ExclusiveRecognizer function: OnAccepted OnRejected OnPending OnBlocked
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, ExclusiveRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer.OnAccepted();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED);

    /**
     * @tc.steps: step3. call OnRejected function and compare result.
     * @tc.expected: step3. result equals.
     */
    exclusiveRecognizer.OnRejected();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::FAIL);

    /**
     * @tc.steps: step4. call OnPending function and compare result.
     * @tc.expected: step4. result equals.
     */
    exclusiveRecognizer.OnPending();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING);

    /**
     * @tc.steps: step5. call OnBlocked function and compare result.
     * @tc.expected: step5. result equals.
     */
    exclusiveRecognizer.disposal_ = GestureDisposal::ACCEPT;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::SUCCEED_BLOCKED);
    exclusiveRecognizer.disposal_ = GestureDisposal::PENDING;
    exclusiveRecognizer.OnBlocked();
    EXPECT_EQ(exclusiveRecognizer.refereeState_, RefereeState::PENDING_BLOCKED);
}

/**
 * @tc.name: ExclusiveRecognizerTest002
 * @tc.desc: Test ExclusiveRecognizer function: HandleEvent OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, ExclusiveRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);

    /**
     * @tc.steps: step2. create touchEvent and call HandleEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    bool result;
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

    /**
     * @tc.steps: step3. create axisEvent and call HandleEvent function and compare result.
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
     * @tc.steps: step4. call OnResetStatus function and compare result.
     * @tc.expected: step4. result equals.
     */
    exclusiveRecognizer.OnResetStatus();
    EXPECT_EQ(exclusiveRecognizer.activeRecognizer_, nullptr);
}

/**
 * @tc.name: ExclusiveRecognizerTest003
 * @tc.desc: Test ExclusiveRecognizer function: CheckNeedBlocked
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, ExclusiveRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    ExclusiveRecognizer exclusiveRecognizer = ExclusiveRecognizer(recognizers);
    
    /**
     * @tc.steps: step2. call CheckNeedBlocked function and compare result.
     * @tc.expected: step2. result equals.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    auto result = exclusiveRecognizer.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ExclusiveRecognizerTest004
 * @tc.desc: Test ExclusiveRecognizer function: UnBlockGesture
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, ExclusiveRecognizerTest004, TestSize.Level1)
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

    RefPtr<ClickRecognizer> clickRecognizerPtr =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizer.recognizers_.push_back(clickRecognizerPtr);
    result = exclusiveRecognizer.UnBlockGesture();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: LongPressRecognizerTest001
 * @tc.desc: Test LongPressRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, LongPressRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer =
        LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call OnAccepted function and compare result.
     * @tc.expected: step2. result equals.
     */
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
HWTEST_F(GesturePatternTestNg, LongPressRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer =
        LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    longPressRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.time_, touchEvent.time);
}

/**
 * @tc.name: LongPressRecognizerTest003
 * @tc.desc: Test LongPressRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, LongPressRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    LongPressRecognizer longPressRecognizer =
        LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call HandleTouchUpEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    touchEvent.sourceType = SourceType::MOUSE;
    longPressRecognizer.isForDrag_ = true;
    longPressRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    longPressRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(longPressRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(longPressRecognizer.globalPoint_.GetY(), touchEvent.y);
}

/**
 * @tc.name: PanRecognizerTest001
 * @tc.desc: Test PanRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, PanRecognizerTest001, TestSize.Level1)
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
HWTEST_F(GesturePatternTestNg, PanRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    PanRecognizer panRecognizer = PanRecognizer(panGestureOption);

    /**
     * @tc.steps: step2. call HandleTouchDown function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(panRecognizer.deviceId_, touchEvent.deviceId);
    EXPECT_EQ(panRecognizer.deviceType_, touchEvent.sourceType);
    EXPECT_EQ(panRecognizer.inputEventType_, InputEventType::TOUCH_SCREEN);

    AxisEvent axisEvent;
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
HWTEST_F(GesturePatternTestNg, PanRecognizerTest003, TestSize.Level1)
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
    TouchEvent touchEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer.lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.HandleTouchUpEvent(axisEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), axisEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), axisEvent.y);
}

/**
 * @tc.name: PanRecognizerTest004
 * @tc.desc: Test PanRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, PanRecognizerTest004, TestSize.Level1)
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
    TouchEvent touchEvent;
    panRecognizer.refereeState_ = RefereeState::SUCCEED;
    panRecognizer.touchPoints_[touchEvent.id] = touchEvent;
    panRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(panRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(panRecognizer.delta_.GetX(), 0);
    EXPECT_EQ(panRecognizer.delta_.GetY(), 0);
}

/**
 * @tc.name: PanRecognizerTest005
 * @tc.desc: Test PanRecognizer function: OnFlushTouchEvents begin end
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, PanRecognizerTest005, TestSize.Level1)
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
HWTEST_F(GesturePatternTestNg, PanRecognizerTest006, TestSize.Level1)
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
HWTEST_F(GesturePatternTestNg, PanRecognizerTest007, TestSize.Level1)
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
 * @tc.name: PinchRecognizerTest001
 * @tc.desc: Test PinchRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, PinchRecognizerTest001, TestSize.Level1)
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
HWTEST_F(GesturePatternTestNg, PinchRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(static_cast<int32_t>(pinchRecognizer.touchPoints_.size()), pinchRecognizer.fingers_);
    EXPECT_EQ(pinchRecognizer.refereeState_, RefereeState::DETECTING);

    AxisEvent axisEvent;
    pinchRecognizer.HandleTouchDownEvent(axisEvent);
    EXPECT_EQ(pinchRecognizer.pinchCenter_.GetX(), axisEvent.x);
    EXPECT_EQ(pinchRecognizer.pinchCenter_.GetY(), axisEvent.y);
    EXPECT_EQ(pinchRecognizer.refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: PinchRecognizerTest003
 * @tc.desc: Test PinchRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, PinchRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    PinchRecognizer pinchRecognizer = PinchRecognizer(SINGLE_FINGER_NUMBER, PINCH_GESTURE_DISTANCE);

    /**
     * @tc.steps: step2. call HandleTouchMoveEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    pinchRecognizer.refereeState_ = RefereeState::SUCCEED;
    pinchRecognizer.HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(pinchRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(pinchRecognizer.lastTouchEvent_.id, touchEvent.id);
}

/**
 * @tc.name: PinchRecognizerTest004
 * @tc.desc: Test PinchRecognizer function: OnFlushTouchEvent begin end
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, PinchRecognizerTest004, TestSize.Level1)
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
HWTEST_F(GesturePatternTestNg, PinchRecognizerTest005, TestSize.Level1)
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
 * @tc.name: RotationRecognizerTest001
 * @tc.desc: Test RotationRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, RotationRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer =
        RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

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
 * @tc.desc: Test RotationRecognizer function: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, RotationRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer =
        RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call HandleTouchDownEvent function and compare result.
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    rotationRecognizer.HandleTouchDownEvent(touchEvent);
    EXPECT_EQ(rotationRecognizer.touchPoints_[touchEvent.id].id, touchEvent.id);
    EXPECT_EQ(rotationRecognizer.refereeState_, RefereeState::DETECTING);
}

/**
 * @tc.name: RotationRecognizerTest003
 * @tc.desc: Test RotationRecognizer function: ChangeValueRange
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, RotationRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer =
        RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

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
HWTEST_F(GesturePatternTestNg, RotationRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer =
        RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

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
HWTEST_F(GesturePatternTestNg, RotationRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    RotationRecognizer rotationRecognizer =
        RotationRecognizer(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);

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
 * @tc.name: SwipeRecognizerTest001
 * @tc.desc: Test SwipeRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, SwipeRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer =
        SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    
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
HWTEST_F(GesturePatternTestNg, SwipeRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer =
        SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    
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
HWTEST_F(GesturePatternTestNg, SwipeRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer =
        SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    
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
 * @tc.name: SwipeRecognizerTest004
 * @tc.desc: Test SwipeRecognizer function: HandleTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, SwipeRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer =
        SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    
    /**
     * @tc.steps: step2. call HandleTouchMove function
     * @tc.expected: step2. result equals.
     */
    TouchEvent touchEvent;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.downEvents_[touchEvent.id] = touchEvent;
    touchEvent.x = 0;
    touchEvent.y = 1;
    swipeRecognizer.HandleTouchUpEvent(touchEvent);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetX(), touchEvent.x);
    EXPECT_EQ(swipeRecognizer.globalPoint_.GetY(), touchEvent.y);
    EXPECT_EQ(swipeRecognizer.lastTouchEvent_.id, touchEvent.id);

    AxisEvent axisEvent;
    swipeRecognizer.refereeState_ = RefereeState::FAIL;
    swipeRecognizer.HandleTouchUpEvent(axisEvent);
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
HWTEST_F(GesturePatternTestNg, SwipeRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer =
        SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    
    /**
     * @tc.steps: step2. call CheckAngle function
     * @tc.expected: step2. result equals.
     */
    swipeRecognizer.prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    auto result = swipeRecognizer.CheckAngle(0);
    EXPECT_EQ(result, false);
    
    swipeRecognizer.prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    result = swipeRecognizer.CheckAngle(VERTICAL_ANGLE);
    EXPECT_EQ(result, true);

    swipeRecognizer.prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    swipeRecognizer.direction_.type = SwipeDirection::HORIZONTAL;
    result = swipeRecognizer.CheckAngle(VERTICAL_ANGLE);
    EXPECT_EQ(result, false);

    swipeRecognizer.prevAngle_ = std::make_optional(VERTICAL_ANGLE);
    swipeRecognizer.direction_.type = SwipeDirection::VERTICAL;
    result = swipeRecognizer.CheckAngle(HORIZONTAL_ANGLE);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: SwipeRecognizerTest006
 * @tc.desc: Test SwipeRecognizer function: OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(GesturePatternTestNg, SwipeRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer =
        SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    
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
HWTEST_F(GesturePatternTestNg, SwipeRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create SwipeRecognizer.
     */
    SwipeDirection swipeDirection;
    SwipeRecognizer swipeRecognizer =
        SwipeRecognizer(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    RefPtr<SwipeRecognizer> swipeRecognizerPtr =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    
    /**
     * @tc.steps: step2. call ReconcileFrom function
     * @tc.expected: step2. result equals.
     */
    auto result = swipeRecognizer.ReconcileFrom(nullptr);
    EXPECT_EQ(result, false);

    result = swipeRecognizer.ReconcileFrom(swipeRecognizerPtr);
    EXPECT_EQ(result, true);

    swipeRecognizer.fingers_ = 1;
    result = swipeRecognizer.ReconcileFrom(swipeRecognizerPtr);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GestureGroupTest001
 * @tc.desc: Test GestureGroup CreateRecognizer function
 */
HWTEST_F(GesturePatternTestNg, GestureGroupTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureGroup.
     */
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: GestureMode::Begin
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Begin;
    auto groupRecognizer =  gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer, nullptr);
    
    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: GestureMode::Sequence
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Sequence;
    groupRecognizer =  gestureGroup.CreateRecognizer();
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
    groupRecognizer =  gestureGroup.CreateRecognizer();
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
    groupRecognizer =  gestureGroup.CreateRecognizer();
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
    groupRecognizer =  gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer, nullptr);
}

/**
 * @tc.name: GestureRefereeTest001
 * @tc.desc: Test GestureReferee Existed function
 */
HWTEST_F(GesturePatternTestNg, GestureRefereeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: expected equal
     */
    auto result = gestureScope.Existed(clickRecognizerPtr);
    EXPECT_EQ(result, true);

    result = gestureScope.Existed(nullptr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GestureRefereeTest002
 * @tc.desc: Test GestureReferee CheckNeedBlocked function
 */
HWTEST_F(GesturePatternTestNg, GestureRefereeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call Existed function and compare result
     * @tc.steps: expected equal
     */
    auto result = gestureScope.CheckNeedBlocked(clickRecognizerPtr);
    EXPECT_EQ(result, false);
    
    RefPtr<ClickRecognizer> clickRecognizerPtrNotInsert =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    result = gestureScope.CheckNeedBlocked(clickRecognizerPtrNotInsert);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GestureRefereeTest003
 * @tc.desc: Test GestureReferee OnAcceptGesture function
 */
HWTEST_F(GesturePatternTestNg, GestureRefereeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call OnAcceptGesture function and compare result
     * @tc.steps: expected equal
     */
    gestureScope.OnAcceptGesture(clickRecognizerPtr);
    EXPECT_EQ(gestureScope.hasGestureAccepted_, true);
}

/**
 * @tc.name: GestureRefereeTest004
 * @tc.desc: Test GestureReferee OnBlockGesture function
 */
HWTEST_F(GesturePatternTestNg, GestureRefereeTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
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
HWTEST_F(GesturePatternTestNg, GestureRefereeTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureScope and clickRecognizer.
     */
    GestureScope gestureScope = GestureScope(0);
    RefPtr<ClickRecognizer> clickRecognizerPtr =
        AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    gestureScope.recognizers_.insert(gestureScope.recognizers_.end(), clickRecognizerPtr);

    /**
     * @tc.steps: step2. call IsPending function and compare result
     * @tc.steps: expected equal
     */
    auto result = gestureScope.IsPending();
    EXPECT_EQ(result, false);

    clickRecognizerPtr->refereeState_ = RefereeState::PENDING;
    result = gestureScope.IsPending();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GestureRefereeTest006
 * @tc.desc: Test GestureReferee AddGestureToScope function
 */
HWTEST_F(GesturePatternTestNg, GestureRefereeTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureReferee.
     */
    GestureReferee gestureReferee;

    /**
     * @tc.steps: step2. call AddGestureToScope function and compare result
     * @tc.steps: expected equal
     */
    TouchTestResult touchTestResult;
    gestureReferee.AddGestureToScope(0, touchTestResult);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 1);
}

/**
 * @tc.name: GestureRefereeTest007
 * @tc.desc: Test GestureReferee CleanGestureScope function
 */
HWTEST_F(GesturePatternTestNg, GestureRefereeTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureReferee.
     */
    GestureReferee gestureReferee;
    
    /**
     * @tc.steps: step2. call CleanGestureScope function and compare result
     * @tc.steps: expected equal
     */
    gestureReferee.CleanGestureScope(0);
    EXPECT_EQ(gestureReferee.gestureScopes_.size(), 0);
}

/**
 * @tc.name: LongPressGestureTest001
 * @tc.desc: Test LongPressGesture CreateRecognizer function
 */
HWTEST_F(GesturePatternTestNg, LongPressGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressGesture.
     */
    LongPressGesture longPressGesture =
        LongPressGesture(FINGER_NUMBER, false, LONG_PRESS_DURATION, false, false);
    EXPECT_EQ(longPressGesture.repeat_, false);
    EXPECT_EQ(longPressGesture.duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressGesture.isForDrag_, false);
    EXPECT_EQ(longPressGesture.isDisableMouseLeft_, false);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     */
    auto longPressRecognizer =
        AceType::DynamicCast<LongPressRecognizer>(longPressGesture.CreateRecognizer());
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_EQ(longPressRecognizer->repeat_, false);
    EXPECT_EQ(longPressRecognizer->duration_, LONG_PRESS_DURATION);
    EXPECT_EQ(longPressRecognizer->isForDrag_, false);
    EXPECT_EQ(longPressRecognizer->isDisableMouseLeft_, false);
}

/**
 * @tc.name: PinchGestureTest001
 * @tc.desc: Test PinchGesture CreateRecognizer function
 */
HWTEST_F(GesturePatternTestNg, PinchGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchGestureGesture.
     */
    PinchGesture pinchGesture = PinchGesture(FINGER_NUMBER, PINCH_GESTURE_DISTANCE);
    EXPECT_EQ(pinchGesture.distance_, PINCH_GESTURE_DISTANCE);
}

/**
 * @tc.name: RotationGestureTest001
 * @tc.desc: Test RotationGesture CreateRecognizer function
 */
HWTEST_F(GesturePatternTestNg, RotationGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationGestureGesture.
     */
    RotationGesture rotationGesture = RotationGesture(FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    EXPECT_EQ(rotationGesture.angle_, ROTATION_GESTURE_ANGLE);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     */
    rotationGesture.priority_ = GesturePriority::Low;
    rotationGesture.gestureMask_ = GestureMask::Normal;
    auto rotationRecognizer =
        AceType::DynamicCast<RotationRecognizer>(rotationGesture.CreateRecognizer());
    EXPECT_NE(rotationRecognizer, nullptr);
    EXPECT_EQ(rotationRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(rotationRecognizer->GetPriorityMask(), GestureMask::Normal);
}

/**
 * @tc.name: TapGestureTest001
 * @tc.desc: Test TapGesture CreateRecognizer function
 */
HWTEST_F(GesturePatternTestNg, TapGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TapGestureGesture.
     */
    TapGesture tapGesture = TapGesture(COUNT, FINGER_NUMBER);
    EXPECT_EQ(tapGesture.count_, COUNT);
    
    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     */
    tapGesture.priority_ = GesturePriority::Low;
    tapGesture.gestureMask_ = GestureMask::Normal;
    auto tapRecognizer =
        AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_NE(tapRecognizer, nullptr);
    EXPECT_EQ(tapRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(tapRecognizer->GetPriorityMask(), GestureMask::Normal);
}
} // namespace OHOS::Ace::NG

