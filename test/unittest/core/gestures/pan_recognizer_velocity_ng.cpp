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

#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/event/ace_events.h"
#include "core/gestures/gesture_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t DEFAULT_TOUCH_FINGER_ID = 0;
constexpr int32_t DEFAULT_TOUCH_POINT_SIZE = 5;
constexpr int32_t DEFAULT_MOVE_DISTANCE = 100;
constexpr uint64_t DEFAULT_MOVE_TIME = 100;
} // namespace

class PanRecognizerVelocityTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void PanRecognizerVelocityTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void PanRecognizerVelocityTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: PanRecognizerHandleTouchUpVelocityTest001
 * @tc.desc: Test PanRecognizer HandleTouchUpEvent panVelocity_.Reset.
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerVelocityTestNg, PanRecognizerHandleTouchUpVelocityTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    panRecognizer->panVelocity_.ResetAll();

    /**
     * @tc.steps: step2. update default touch point.
     */
    for (int32_t i = 0; i < DEFAULT_TOUCH_POINT_SIZE; i++) {
        TouchEvent touchEvent;
        touchEvent.id = DEFAULT_TOUCH_FINGER_ID;
        touchEvent.x = DEFAULT_MOVE_DISTANCE * i;
        touchEvent.y = 0;
        touchEvent.time = TimeStamp(std::chrono::nanoseconds(DEFAULT_MOVE_TIME));
        panRecognizer->panVelocity_.UpdateTouchPoint(DEFAULT_TOUCH_FINGER_ID, touchEvent, false);
    }

    /**
     * @tc.steps: step3. update default panRecognizer info.
     */
    TouchEvent triggerTouchEvent;
    triggerTouchEvent.x = DEFAULT_MOVE_DISTANCE * (DEFAULT_TOUCH_POINT_SIZE + 1);
    triggerTouchEvent.type = TouchType::UP;
    panRecognizer->fingersId_.insert(1);
    panRecognizer->refereeState_ = RefereeState::FAIL;

    /**
     * @tc.steps: step4. test panVelocity_.Reset.
     * @tc.expected: if last finger up, not reset finger's velocity.
     */
    panRecognizer->currentFingers_ = 1;
    panRecognizer->fingers_ = 1;
    panRecognizer->HandleTouchUpEvent(triggerTouchEvent);
    EXPECT_EQ(panRecognizer->panVelocity_.trackerMap_[0].xAxis_.GetTrackNum(), 5);

    /**
     * @tc.steps: step5. test panVelocity_.Reset.
     * @tc.expected: if not last finger up, reset finger's velocity.
     */
    panRecognizer->currentFingers_ = 2;
    panRecognizer->fingers_ = 1;
    panRecognizer->HandleTouchUpEvent(triggerTouchEvent);
    EXPECT_EQ(panRecognizer->panVelocity_.trackerMap_[0].xAxis_.GetTrackNum(), 0);

    
    /**
     * @tc.steps: step5. test panVelocity_.Reset.
     * @tc.expected: if not last finger up, reset finger's velocity.
     */
    panRecognizer->refereeState_ = RefereeState::FAIL;
    TouchEvent moveEvent;
    moveEvent.type = TouchType::MOVE;
    EXPECT_EQ(panRecognizer->panVelocity_.trackerMap_[0].xAxis_.GetTrackNum(), 0);
    panRecognizer->HandleTouchMoveEvent(moveEvent);
    EXPECT_EQ(panRecognizer->panVelocity_.trackerMap_[0].xAxis_.GetTrackNum(), 0);
}
} // namespace OHOS::Ace::NG