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
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, FINGER_NUMBER, false);

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    TouchEvent downEvent;
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::MOUSE);
    longPressRecognizer.HandleTouchDownEvent(downEvent);
    int64_t time = 0;
    auto onAction = [&time](GestureEvent& info) { time = info.GetTimeStamp().time_since_epoch().count(); };
    longPressRecognizer.SetOnAction(onAction);
    longPressRecognizer.OnAccepted();
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
    LongPressRecognizer longPressRecognizer = LongPressRecognizer(LONG_PRESS_DURATION, COUNT, false);

    /**
     * @tc.steps: step2. call GetLongPressActionFunc function and compare result.
     * @tc.steps: case1: normal case
     * @tc.expected: step2. result equals.
     */
    TouchEvent downEvent;
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::TOUCH);
    longPressRecognizer.HandleTouchDownEvent(downEvent);
    TouchEvent downFingerOneEvent;
    downFingerOneEvent.SetId(1).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::TOUCH);
    longPressRecognizer.touchPoints_[1] = downFingerOneEvent;
    TouchEvent moveEvent;
    std::chrono::nanoseconds nanoseconds(GetSysTimestamp());
    moveEvent.SetId(0)
        .SetType(TouchType::MOVE)
        .SetX(100.0f)
        .SetY(100.0f)
        .SetSourceType(SourceType::TOUCH)
        .SetTime(TimeStamp(nanoseconds));
    longPressRecognizer.HandleTouchMoveEvent(moveEvent);
    int64_t touchTime = 0;
    int64_t mouseTime = 0;
    auto onAction = [&touchTime, &mouseTime](GestureEvent& info) {
        if (info.GetSourceDevice() == SourceType::MOUSE) {
            mouseTime = info.GetTimeStamp().time_since_epoch().count();
        } else {
            touchTime = info.GetTimeStamp().time_since_epoch().count();
        }
    };
    longPressRecognizer.SetOnAction(onAction);
    longPressRecognizer.OnAccepted();
    longPressRecognizer.ResetStatus();
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::MOUSE);
    longPressRecognizer.HandleTouchDownEvent(downEvent);
    longPressRecognizer.OnAccepted();
    EXPECT_NE(touchTime, mouseTime);
}

} // namespace OHOS::Ace::NG