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

#include "test/unittest/core/gestures/gestures_common_test_ng.h"
#include "test/unittest/core/gestures/recognizer_group_test_utils.h"
#include "test/unittest/core/gestures/recognizer_test_utils.h"

#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
enum class RecognizerType {
    SINGLE_FINGER_SINGLE_CLICK = 0,
    SINGLE_FINGER_DOUBLE_CLICK,
    DOUBLE_FINGER_SINGLE_CLICK,
    PAN_RECOGNIZER,
    SWIPE_RECOGNIZER,
    LONG_PRESS_RECOGNIZER,
    PINCH_RECOGNIZER,
    ROTATION_RECOGNIZER,
};

enum class TestInputType {
    SINGLE_FINGER_SINGLE_CLICK = 0,
    SINGLE_FINGER_DOUBLE_CLICK,
    DOUBLE_FINGER_SINGLE_CLICK,
    PAN,
    SWIPE,
    LONG_PRESS,
    PINCH,
    ROTATION,
    SINGLE_DOWN_SINGLE_MOVE
};

struct ExclusiveTestCase {
    RecognizerType recognizerOne;
    RecognizerType recognizerTwo;
    TestInputType inputType;
    RefereeState recognizerOneExpectState;
    RefereeState recognizerTwoExpectState;
    ExclusiveTestCase(RecognizerType recognizerOne, RecognizerType recognizerTwo, TestInputType inputType,
        RefereeState recognizerOneExpectState, RefereeState recognizerTwoExpectState)
        : recognizerOne(recognizerOne), recognizerTwo(recognizerTwo), inputType(inputType),
          recognizerOneExpectState(recognizerOneExpectState), recognizerTwoExpectState(recognizerTwoExpectState)
    {}
};

const std::vector<ExclusiveTestCase> TEST_CASES = {
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::SINGLE_FINGER_SINGLE_CLICK,
        TestInputType::SINGLE_FINGER_SINGLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 0
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::SINGLE_FINGER_DOUBLE_CLICK,
        TestInputType::SINGLE_FINGER_SINGLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 1
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::SINGLE_FINGER_DOUBLE_CLICK,
        TestInputType::SINGLE_FINGER_DOUBLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 2
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::DOUBLE_FINGER_SINGLE_CLICK,
        TestInputType::SINGLE_FINGER_DOUBLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 3
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::DOUBLE_FINGER_SINGLE_CLICK,
        TestInputType::DOUBLE_FINGER_SINGLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 4
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::PAN_RECOGNIZER,
        TestInputType::SINGLE_FINGER_SINGLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 5
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::PAN_RECOGNIZER, TestInputType::PAN,
        RefereeState::FAIL, RefereeState::SUCCEED), // 6
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::SWIPE_RECOGNIZER,
        TestInputType::SINGLE_FINGER_SINGLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 7
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::SWIPE_RECOGNIZER,
        TestInputType::SWIPE, RefereeState::SUCCEED, RefereeState::FAIL), // 8
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::PINCH_RECOGNIZER,
        TestInputType::SINGLE_FINGER_SINGLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 9
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::PINCH_RECOGNIZER,
        TestInputType::PINCH, RefereeState::FAIL, RefereeState::SUCCEED), // 10
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::ROTATION_RECOGNIZER,
        TestInputType::SINGLE_FINGER_SINGLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 11
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_SINGLE_CLICK, RecognizerType::ROTATION_RECOGNIZER,
        TestInputType::ROTATION, RefereeState::FAIL, RefereeState::SUCCEED), // 12
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_DOUBLE_CLICK, RecognizerType::SINGLE_FINGER_SINGLE_CLICK,
        TestInputType::SINGLE_FINGER_DOUBLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 13
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_DOUBLE_CLICK, RecognizerType::SINGLE_FINGER_DOUBLE_CLICK,
        TestInputType::SINGLE_FINGER_DOUBLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 14
    ExclusiveTestCase(RecognizerType::SINGLE_FINGER_DOUBLE_CLICK, RecognizerType::DOUBLE_FINGER_SINGLE_CLICK,
        TestInputType::DOUBLE_FINGER_SINGLE_CLICK, RefereeState::PENDING, RefereeState::SUCCEED_BLOCKED), // 15
    ExclusiveTestCase(RecognizerType::DOUBLE_FINGER_SINGLE_CLICK, RecognizerType::SINGLE_FINGER_SINGLE_CLICK,
        TestInputType::DOUBLE_FINGER_SINGLE_CLICK, RefereeState::SUCCEED, RefereeState::FAIL), // 16
    ExclusiveTestCase(RecognizerType::PAN_RECOGNIZER, RecognizerType::PAN_RECOGNIZER, TestInputType::PAN,
        RefereeState::SUCCEED, RefereeState::FAIL), // 17
    ExclusiveTestCase(RecognizerType::PAN_RECOGNIZER, RecognizerType::PAN_RECOGNIZER,
        TestInputType::SINGLE_DOWN_SINGLE_MOVE, RefereeState::SUCCEED, RefereeState::FAIL), // 18
    ExclusiveTestCase(RecognizerType::PAN_RECOGNIZER, RecognizerType::SWIPE_RECOGNIZER, TestInputType::SWIPE,
        RefereeState::READY, RefereeState::FAIL), // 19
    ExclusiveTestCase(RecognizerType::PAN_RECOGNIZER, RecognizerType::PINCH_RECOGNIZER, TestInputType::PINCH,
        RefereeState::READY, RefereeState::FAIL), // 20
    ExclusiveTestCase(RecognizerType::PAN_RECOGNIZER, RecognizerType::PINCH_RECOGNIZER,
        TestInputType::SINGLE_DOWN_SINGLE_MOVE, RefereeState::SUCCEED, RefereeState::FAIL), // 21
    ExclusiveTestCase(RecognizerType::PAN_RECOGNIZER, RecognizerType::ROTATION_RECOGNIZER, TestInputType::ROTATION,
        RefereeState::READY, RefereeState::FAIL), // 22
    ExclusiveTestCase(RecognizerType::SWIPE_RECOGNIZER, RecognizerType::SINGLE_FINGER_SINGLE_CLICK,
        TestInputType::SWIPE, RefereeState::SUCCEED, RefereeState::FAIL), // 23
    ExclusiveTestCase(RecognizerType::PINCH_RECOGNIZER, RecognizerType::PINCH_RECOGNIZER, TestInputType::PINCH,
        RefereeState::SUCCEED, RefereeState::FAIL), // 24
    ExclusiveTestCase(RecognizerType::PINCH_RECOGNIZER, RecognizerType::ROTATION_RECOGNIZER, TestInputType::PINCH,
        RefereeState::SUCCEED, RefereeState::FAIL), // 25
    ExclusiveTestCase(RecognizerType::PINCH_RECOGNIZER, RecognizerType::ROTATION_RECOGNIZER, TestInputType::ROTATION,
        RefereeState::FAIL, RefereeState::SUCCEED), // 26
};

namespace {

RefPtr<NGGestureRecognizer> CreateRecognizerWithType(RecognizerType type)
{
    switch (type) {
        case RecognizerType::SINGLE_FINGER_SINGLE_CLICK:
            return CreateClickRecognizerWithParam(1, 1);
        case RecognizerType::SINGLE_FINGER_DOUBLE_CLICK:
            return CreateClickRecognizerWithParam(1, 2);
        case RecognizerType::DOUBLE_FINGER_SINGLE_CLICK:
            return CreateClickRecognizerWithParam(2, 1);
        case RecognizerType::PAN_RECOGNIZER:
            return CreatePanRecognizerWithParam(1, {}, 5.0);
        case RecognizerType::SWIPE_RECOGNIZER:
            return CreateSwipeRecognizerWithParam(1, {}, 100);
        case RecognizerType::LONG_PRESS_RECOGNIZER:
            return CreateLongPressRecognizerWithParam(500, 1, false);
        case RecognizerType::PINCH_RECOGNIZER:
            return CreatePinchRecognizerWithParam(2, 10.0);
        case RecognizerType::ROTATION_RECOGNIZER:
            return CreateRotationRecognizerWithParam(2, 5.0);
        default:
            return nullptr;
    }
}

void DispatchTouchEventWithType(const RefPtr<NGGestureRecognizer>& recognizer, TestInputType type)
{
    switch (type) {
        case TestInputType::SINGLE_FINGER_SINGLE_CLICK:
            DispatchSingleClickEvent(recognizer);
            break;
        case TestInputType::SINGLE_FINGER_DOUBLE_CLICK:
            DispatchSingleClickEvent(recognizer);
            DispatchSingleClickEvent(recognizer);
            break;
        case TestInputType::DOUBLE_FINGER_SINGLE_CLICK:
            DispatchDoubleFingerSingleClickEvent(recognizer);
            break;
        case TestInputType::PAN:
            DispatchPanEvent(recognizer);
            break;
        case TestInputType::SWIPE:
            DispatchSwipeEvent(recognizer);
            break;
        case TestInputType::LONG_PRESS:
            break;
        case TestInputType::PINCH:
            DispatchPinchEvent(recognizer);
            break;
        case TestInputType::ROTATION:
            DispatchRotationEvent(recognizer);
            break;
        case TestInputType::SINGLE_DOWN_SINGLE_MOVE:
            DispatchSingleDownSingleMoveEvent(recognizer);
            break;
    }
}

} // namespace

class ExclusiveRecognizerBaseTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ExclusiveRecognizerBaseTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void ExclusiveRecognizerBaseTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ExclusiveRecognizerBaseTest001
 * @tc.desc: Test ExclusiveRecognizer: Basic function test
 * @tc.type: FUNC
 */
HWTEST_F(ExclusiveRecognizerBaseTestNg, ExclusiveRecognizerBaseTest001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : TEST_CASES) {
        /**
         * @tc.steps: step1. create ExclusiveRecognizer.
         */
        auto recognizerOne = CreateRecognizerWithType(testCase.recognizerOne);
        auto recognizerTwo = CreateRecognizerWithType(testCase.recognizerTwo);
        std::vector<RefPtr<NGGestureRecognizer>> recognizers = { recognizerOne, recognizerTwo };
        auto exclusiveRecognizer = CreateExclusiveRecognizerWithParam(recognizers);
        /**
         * @tc.steps: step2. DispatchTouchEvent.
         * @tc.expected: step2. refereeState_ equals.
         */
        DispatchTouchEventWithType(exclusiveRecognizer, testCase.inputType);
        EXPECT_TRUE(IsRecognizerStateEqual(caseNum, recognizerOne->refereeState_, testCase.recognizerOneExpectState));
        EXPECT_TRUE(IsRecognizerStateEqual(caseNum, recognizerTwo->refereeState_, testCase.recognizerTwoExpectState));
        caseNum++;
    }
}

} // namespace OHOS::Ace::NG