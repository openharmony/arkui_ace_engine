/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "gtest/gtest.h"
#include "test/unittest/core/gestures/gestures_common_test_ng.h"
#include "ui/base/ace_type.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RecognizerTestNgIssue : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void RecognizerTestNgIssue::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void RecognizerTestNgIssue::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: LongPressRecognizerIssue001
 * @tc.desc: Test LongPressRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerTestNgIssue, LongPressRecognizerIssue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    TouchEvent downEvent;
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::MOUSE);
    longPressRecognizer->HandleTouchDownEvent(downEvent);
    int64_t time = 0;
    auto onAction = [&time](GestureEvent& info) { time = info.GetTimeStamp().time_since_epoch().count(); };
    longPressRecognizer->SetOnAction(onAction);
    longPressRecognizer->OnAccepted();
    EXPECT_NE(time, 0);
}

/**
 * @tc.name: LongPressRecognizerIssue002
 * @tc.desc: Test LongPressRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerTestNgIssue, LongPressRecognizerIssue002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, COUNT, false);

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    TouchEvent downEvent;
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::TOUCH);
    longPressRecognizer->HandleTouchDownEvent(downEvent);
    TouchEvent downFingerOneEvent;
    downFingerOneEvent.SetId(1).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::TOUCH);
    longPressRecognizer->touchPoints_[1] = downFingerOneEvent;
    TouchEvent moveEvent;
    std::chrono::nanoseconds nanoseconds(GetSysTimestamp());
    moveEvent.SetId(0)
        .SetType(TouchType::MOVE)
        .SetX(100.0f)
        .SetY(100.0f)
        .SetSourceType(SourceType::TOUCH)
        .SetTime(TimeStamp(nanoseconds));
    longPressRecognizer->HandleTouchMoveEvent(moveEvent);
    int64_t touchTime = 0;
    int64_t mouseTime = 0;
    auto onAction = [&touchTime, &mouseTime](GestureEvent& info) {
        if (info.GetSourceDevice() == SourceType::MOUSE) {
            mouseTime = info.GetTimeStamp().time_since_epoch().count();
        } else {
            touchTime = info.GetTimeStamp().time_since_epoch().count();
        }
    };
    longPressRecognizer->SetOnAction(onAction);
    longPressRecognizer->OnAccepted();
    longPressRecognizer->ResetStatus();
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::MOUSE);
    longPressRecognizer->HandleTouchDownEvent(downEvent);
    longPressRecognizer->OnAccepted();
    EXPECT_NE(touchTime, mouseTime);
}

/**
 * @tc.name: LongPressRecognizerIssue003
 * @tc.desc: Test LongPressRecognizer callback info
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerTestNgIssue, LongPressRecognizerIssue003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create LongPressRecognizer and set onAction.
     */
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, 1, false);
    GestureEvent eventInfo;
    auto onActionStart = [&eventInfo](GestureEvent& info) { eventInfo = info; };
    longPressRecognizer->SetOnAction(onActionStart);

    /**
     * @tc.steps: step2. DispatchTouchEvent and compare callback info.
     * @tc.expected: step2. result equals.
     */
    TouchEvent downEvent;
    downEvent.SetId(0)
        .SetType(TouchType::DOWN)
        .SetX(100.0f)
        .SetY(100.0f)
        .SetSourceType(SourceType::TOUCH)
        .SetDeviceId(2);
    longPressRecognizer->HandleEvent(downEvent);
    TouchEvent downFingerOneEvent;
    downFingerOneEvent.SetId(1)
        .SetType(TouchType::DOWN)
        .SetX(100.0f)
        .SetY(100.0f)
        .SetSourceType(SourceType::TOUCH)
        .SetDeviceId(2);
    longPressRecognizer->touchPoints_[1] = downFingerOneEvent;
    TouchEvent moveEvent;
    auto moveTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds(moveTime);
    moveEvent.SetId(0)
        .SetType(TouchType::MOVE)
        .SetX(100.0f)
        .SetY(100.0f)
        .SetScreenX(200.0f)
        .SetScreenY(200.0f)
        .SetSourceType(SourceType::TOUCH)
        .SetSourceTool(SourceTool::FINGER)
        .SetTime(TimeStamp(nanoseconds))
        .SetForce(100.0f)
        .SetTiltX(10.0f)
        .SetTiltY(10.0f)
        .SetTargetDisplayId(2);
    longPressRecognizer->HandleEvent(moveEvent);
    longPressRecognizer->OnAccepted();
    EXPECT_EQ(eventInfo.GetTimeStamp().time_since_epoch().count(), moveTime);
    EXPECT_EQ(eventInfo.GetRepeat(), false);
    EXPECT_EQ(eventInfo.GetFingerList().size(), 2);
    EXPECT_EQ(eventInfo.GetSourceDevice(), SourceType::TOUCH);
    EXPECT_EQ(eventInfo.GetDeviceId(), 2);
    EXPECT_EQ(eventInfo.GetGlobalPoint().GetX(), 100.0f);
    EXPECT_EQ(eventInfo.GetGlobalPoint().GetY(), 100.0f);
    EXPECT_EQ(eventInfo.GetScreenLocation().GetX(), 200.0f);
    EXPECT_EQ(eventInfo.GetScreenLocation().GetY(), 200.0f);
    EXPECT_EQ(eventInfo.GetGlobalLocation().GetX(), 100.0f);
    EXPECT_EQ(eventInfo.GetGlobalLocation().GetY(), 100.0f);
    EXPECT_EQ(eventInfo.GetLocalLocation().GetX(), 100.0f);
    EXPECT_EQ(eventInfo.GetLocalLocation().GetY(), 100.0f);
    EXPECT_EQ(eventInfo.GetForce(), 100.0f);
    EXPECT_EQ(eventInfo.GetTiltX(), 10.0f);
    EXPECT_EQ(eventInfo.GetTiltY(), 10.0f);
    EXPECT_EQ(eventInfo.GetSourceTool(), SourceTool::FINGER);
    EXPECT_EQ(eventInfo.GetInputEventType(), InputEventType::TOUCH_SCREEN);
}

/**
 * @tc.name: PanRecognizerIssue001
 * @tc.desc: Test PanRecognizer: Test the finger information of the current recognizer in the case of setting a single
 *           finger by pressing multiple fingers and lifting them.
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerTestNgIssue, PanRecognizerIssue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    panGestureOption->SetFingers(1);
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    panGestureOption->SetDirection(panDirection);
    panGestureOption->SetDistance(10.0f);
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    /**
     * @tc.steps: step2. DispatchTouchEvent with two different fingers and dispatch two up events.
     * @tc.expected: step2. fingersId_ empty.
     */
    TouchEvent zeroDownEvent;
    zeroDownEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    TouchEvent oneDownEvent;
    oneDownEvent.SetId(1).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    panRecognizer->HandleEvent(zeroDownEvent);
    panRecognizer->HandleEvent(oneDownEvent);
    TouchEvent zeroUpEvent;
    zeroUpEvent.SetId(0).SetType(TouchType::UP).SetX(100.0f).SetY(100.0f);
    TouchEvent oneUpEvent;
    oneUpEvent.SetId(1).SetType(TouchType::UP).SetX(100.0f).SetY(100.0f);
    panRecognizer->HandleEvent(zeroUpEvent);
    panRecognizer->HandleEvent(oneUpEvent);
    EXPECT_TRUE(panRecognizer->fingersId_.empty());
}

/**
 * @tc.name: RotationRecognizerIssue001
 * @tc.desc: Test the rotating gesture by pressing two fingers, and when the gesture fails, lift finger number one and
 *           finger number one is cleared from activeFingers_ correctly.
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerTestNgIssue, RotationRecognizerIssue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RotationRecognizer.
     */
    auto rotationRecognizer = AceType::MakeRefPtr<RotationRecognizer>(2, ROTATION_GESTURE_ANGLE);
    /**
     * @tc.steps: step2. DispatchTouchEvent with two different fingers and dispatch two up events.
     * @tc.expected: step2. fingersId_ empty.
     */
    TouchEvent zeroDownEvent;
    zeroDownEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    TouchEvent oneDownEvent;
    oneDownEvent.SetId(1).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    rotationRecognizer->HandleEvent(zeroDownEvent);
    rotationRecognizer->HandleEvent(oneDownEvent);
    TouchEvent oneUpEvent;
    oneUpEvent.SetId(1).SetType(TouchType::UP).SetX(100.0f).SetY(100.0f);
    rotationRecognizer->HandleEvent(oneUpEvent);
    EXPECT_EQ(std::find(rotationRecognizer->activeFingers_.begin(), rotationRecognizer->activeFingers_.end(), 1),
        rotationRecognizer->activeFingers_.end());
    EXPECT_EQ(rotationRecognizer->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: PinchRecognizerIssue001
 * @tc.desc: Test the pinch gesture by pressing two fingers, and when the gesture fails, lift finger number one and
 *           finger number one is cleared from activeFingers_ correctly.
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerTestNgIssue, PinchRecognizerIssue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PinchRecognizer.
     */
    auto pinchRecognizer = AceType::MakeRefPtr<PinchRecognizer>(2, PINCH_GESTURE_DISTANCE);
    /**
     * @tc.steps: step2. DispatchTouchEvent with two different fingers and dispatch two up events.
     * @tc.expected: step2. fingersId_ empty.
     */
    TouchEvent zeroDownEvent;
    zeroDownEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    TouchEvent oneDownEvent;
    oneDownEvent.SetId(1).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    pinchRecognizer->HandleEvent(zeroDownEvent);
    pinchRecognizer->HandleEvent(oneDownEvent);
    TouchEvent oneUpEvent;
    oneUpEvent.SetId(1).SetType(TouchType::UP).SetX(100.0f).SetY(100.0f);
    pinchRecognizer->HandleEvent(oneUpEvent);
    EXPECT_EQ(std::find(pinchRecognizer->activeFingers_.begin(), pinchRecognizer->activeFingers_.end(), 1),
        pinchRecognizer->activeFingers_.end());
    EXPECT_EQ(pinchRecognizer->refereeState_, RefereeState::FAIL);
}

/**
 * @tc.name: TargetDisplayId001
 * @tc.desc: Test SetTargetDisplayId GetTargetDisplayId
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerTestNgIssue, TargetDisplayId001, TestSize.Level1)
{
    RefPtr<LongPressRecognizer> longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, 1, false);
    GestureEvent eventInfo;
    auto onActionStart = [&eventInfo](GestureEvent& info) { eventInfo = info; };
    longPressRecognizer->SetOnAction(onActionStart);

    TouchEvent downEvent;
    downEvent.SetId(0)
        .SetType(TouchType::DOWN)
        .SetX(100.0f)
        .SetY(100.0f)
        .SetSourceType(SourceType::TOUCH)
        .SetDeviceId(2);
    longPressRecognizer->HandleEvent(downEvent);
    TouchEvent downFingerOneEvent;
    downFingerOneEvent.SetId(1)
        .SetType(TouchType::DOWN)
        .SetX(100.0f)
        .SetY(100.0f)
        .SetSourceType(SourceType::TOUCH)
        .SetDeviceId(2);
    longPressRecognizer->touchPoints_[1] = downFingerOneEvent;
    TouchEvent moveEvent;
    auto moveTime = GetSysTimestamp();
    std::chrono::nanoseconds nanoseconds(moveTime);
    moveEvent.SetId(0)
        .SetType(TouchType::MOVE)
        .SetX(100.0f)
        .SetY(100.0f)
        .SetScreenX(200.0f)
        .SetScreenY(200.0f)
        .SetSourceType(SourceType::TOUCH)
        .SetSourceTool(SourceTool::FINGER)
        .SetTime(TimeStamp(nanoseconds))
        .SetForce(100.0f)
        .SetTiltX(10.0f)
        .SetTiltY(10.0f)
        .SetTargetDisplayId(2);
    longPressRecognizer->HandleEvent(moveEvent);
    longPressRecognizer->OnAccepted();
    EXPECT_EQ(eventInfo.GetTargetDisplayId(), 2);
}
} // namespace OHOS::Ace::NG