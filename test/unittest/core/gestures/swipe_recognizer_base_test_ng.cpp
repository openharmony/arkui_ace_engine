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
#include "test/unittest/core/gestures/gestures_common_test_ng.h"
#include "test/unittest/core/gestures/recognizer_test_utils.h"
#include "test/unittest/core/gestures/swipe_recognizer_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

struct SwipeInputInfos {
    PointF startPoint;
    int32_t fingerId;
    SwipeInputDirection direction;
    ComparationResult compare;
    SwipeInputInfos(PointF startPoint, int32_t fingerId, SwipeInputDirection direction, ComparationResult compare)
        : startPoint(startPoint), fingerId(fingerId), direction(direction), compare(compare)
    {}
};

struct SwipeTestCase {
    int32_t fingers = 0;
    double speed = 0.0;
    SwipeDirection direction;
    std::vector<SwipeInputInfos> infos;
    RefereeState expectResult;
    SwipeTestCase(int32_t fingers, double speed, SwipeDirection direction, std::vector<SwipeInputInfos> infos,
        RefereeState expectResult)
        : fingers(fingers), speed(speed), direction(direction), infos(std::move(infos)), expectResult(expectResult)
    {}
};

const std::vector<SwipeTestCase> TEST_CASES = {
    SwipeTestCase(1, 100.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::LESS) },
        RefereeState::FAIL), // case 0
    SwipeTestCase(1, 100.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 1
    SwipeTestCase(1, 100.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 2
    SwipeTestCase(1, 100.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(
            PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 3
    SwipeTestCase(1, 100.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 4
    SwipeTestCase(1, 100.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::LESS) },
        RefereeState::FAIL), // case 5
    SwipeTestCase(1, 100.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 6
    SwipeTestCase(1, 100.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 7
    SwipeTestCase(1, 100.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::LESS) },
        RefereeState::FAIL), // case 8
    SwipeTestCase(1, 100.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 9
    SwipeTestCase(1, 100.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 10
    SwipeTestCase(1, 100.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(
            PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 11
    SwipeTestCase(1, 100.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 12
    SwipeTestCase(1, 100.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::LESS) },
        RefereeState::FAIL), // case 13
    SwipeTestCase(1, 100.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 14
    SwipeTestCase(1, 100.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 15
    SwipeTestCase(1, 100.0, { SwipeDirection::ALL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::LESS) },
        RefereeState::DETECTING), // case 16
    SwipeTestCase(1, 100.0, { SwipeDirection::ALL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 17
    SwipeTestCase(1, 100.0, { SwipeDirection::ALL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 18
    SwipeTestCase(1, 100.0, { SwipeDirection::ALL },
        { SwipeInputInfos(
            PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 19
    SwipeTestCase(1, 100.0, { SwipeDirection::ALL },
        { SwipeInputInfos(
            PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 20
    SwipeTestCase(1, 100.0, { SwipeDirection::ALL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 21
    SwipeTestCase(1, 100.0, { SwipeDirection::ALL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 22
    SwipeTestCase(1, 100.0, { SwipeDirection::NONE },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 23
    SwipeTestCase(2, 200.0, { SwipeDirection::VERTICAL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::HORIZONTAL, ComparationResult::LESS),
        },
        RefereeState::FAIL), // case 24
    SwipeTestCase(2, 200.0, { SwipeDirection::VERTICAL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
        },
        RefereeState::SUCCEED), // case 25
    SwipeTestCase(2, 200.0, { SwipeDirection::VERTICAL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
        },
        RefereeState::FAIL), // case 26
    SwipeTestCase(2, 200.0, { SwipeDirection::VERTICAL },
        {
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT),
        },
        RefereeState::FAIL), // case 27
    SwipeTestCase(2, 200.0, { SwipeDirection::VERTICAL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL),
        },
        RefereeState::SUCCEED), // case 28
    SwipeTestCase(2, 200.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::LESS) },
        RefereeState::FAIL), // case 29
    SwipeTestCase(2, 200.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 30
    SwipeTestCase(2, 200.0, { SwipeDirection::VERTICAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 31
    SwipeTestCase(2, 200.0, { SwipeDirection::HORIZONTAL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
        },
        RefereeState::FAIL), // case 32
    SwipeTestCase(2, 200.0, { SwipeDirection::HORIZONTAL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
        },
        RefereeState::FAIL), // case 33
    SwipeTestCase(2, 200.0, { SwipeDirection::HORIZONTAL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
        },
        RefereeState::SUCCEED), // case 34
    SwipeTestCase(2, 200.0, { SwipeDirection::HORIZONTAL },
        {
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT),
        },
        RefereeState::FAIL), // case 35
    SwipeTestCase(2, 200.0, { SwipeDirection::HORIZONTAL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::HORIZONTAL, ComparationResult::EQUAL),
        },
        RefereeState::SUCCEED), // case 36
    SwipeTestCase(2, 200.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::LESS) },
        RefereeState::FAIL), // case 37
    SwipeTestCase(2, 200.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 38
    SwipeTestCase(2, 200.0, { SwipeDirection::HORIZONTAL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 39
    SwipeTestCase(2, 200.0, { SwipeDirection::ALL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
        },
        RefereeState::FAIL), // case 40
    SwipeTestCase(2, 200.0, { SwipeDirection::ALL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
        },
        RefereeState::SUCCEED), // case 41
    SwipeTestCase(2, 200.0, { SwipeDirection::ALL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::HORIZONTAL, ComparationResult::GREAT),
        },
        RefereeState::SUCCEED), // case 42
    SwipeTestCase(2, 200.0, { SwipeDirection::ALL },
        {
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT),
        },
        RefereeState::FAIL), // case 43
    SwipeTestCase(2, 200.0, { SwipeDirection::ALL },
        {
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(
                PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT),
        },
        RefereeState::SUCCEED), // case 44
    SwipeTestCase(2, 200.0, { SwipeDirection::ALL },
        {
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 2, SwipeInputDirection::VERTICAL, ComparationResult::EQUAL),
        },
        RefereeState::SUCCEED), // case 45
    SwipeTestCase(2, 200.0, { SwipeDirection::ALL },
        { SwipeInputInfos(PointF { 100.0f, 100.0f }, 0, SwipeInputDirection::VERTICAL, ComparationResult::GREAT),
            SwipeInputInfos(PointF { 100.0f, 100.0f }, 1, SwipeInputDirection::VERTICAL, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 46
};

namespace {

TouchEvent CreateDownEvent(const SwipeInputInfos& info)
{
    TouchEvent downEvent;
    std::chrono::nanoseconds nanoseconds(1000);
    downEvent.SetId(info.fingerId)
        .SetType(TouchType::DOWN)
        .SetX(info.startPoint.GetX())
        .SetY(info.startPoint.GetY())
        .SetTime(TimeStamp(nanoseconds));
    return downEvent;
}

void CreateMoveAndUpEvents(const SwipeInputInfos& info, double speed,
    std::unordered_map<int32_t, std::vector<TouchEvent>>& moveEvents, std::vector<TouchEvent>& upEvents)
{
    auto timeStep = (SWIPE_MOVE_STEP / speed) * 1000 * 1000 * 1000;
    for (int32_t num = 1; num <= STEP_COUNT; num++) {
        TouchEvent moveEvent;
        std::chrono::nanoseconds moveNanoseconds(static_cast<int64_t>(1000 + num * timeStep));
        moveEvent.SetId(info.fingerId).SetType(TouchType::MOVE).SetTime(TimeStamp(moveNanoseconds));

        float xOffset = 0.0f;
        float yOffset = 0.0f;

        if (info.direction == SwipeInputDirection::HORIZONTAL ||
            info.direction == SwipeInputDirection::HORIZONTAL_VERTICAL) {
            xOffset = SWIPE_MOVE_STEP * num;
        }
        if (info.direction == SwipeInputDirection::VERTICAL ||
            info.direction == SwipeInputDirection::VERTICAL_HORIZONTAL) {
            yOffset = SWIPE_MOVE_STEP * num;
        }
        if (info.direction == SwipeInputDirection::VERTICAL_HORIZONTAL && num > 3) {
            xOffset = SWIPE_MOVE_STEP * (num - 3);
            yOffset = SWIPE_MOVE_STEP * 3;
        } else if (info.direction == SwipeInputDirection::HORIZONTAL_VERTICAL && num > 3) {
            xOffset = SWIPE_MOVE_STEP * 3;
            yOffset = SWIPE_MOVE_STEP * (num - 3);
        }

        moveEvent.SetX(info.startPoint.GetX() + xOffset);
        moveEvent.SetY(info.startPoint.GetY() + yOffset);
        moveEvents[info.fingerId].emplace_back(moveEvent);
    }
    TouchEvent upEvent;
    upEvent.SetId(info.fingerId)
        .SetType(TouchType::UP)
        .SetX(moveEvents[info.fingerId].back().x)
        .SetY(moveEvents[info.fingerId].back().y)
        .SetTime(moveEvents[info.fingerId].back().time);
    upEvents.emplace_back(upEvent);
}

void CreateTouchEvents(const std::vector<SwipeInputInfos>& infos, double speed, std::vector<TouchEvent>& downEvents,
    std::unordered_map<int32_t, std::vector<TouchEvent>>& moveEvents, std::vector<TouchEvent>& upEvents)
{
    for (const auto& info : infos) {
        auto singleFingerSpeed = AdjustSpeed(speed, info.compare);
        TouchEvent downEvent = CreateDownEvent(info);
        downEvents.emplace_back(downEvent);
        CreateMoveAndUpEvents(info, singleFingerSpeed, moveEvents, upEvents);
    }
}

} // namespace

class SwipeRecognizerBaseTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void SwipeRecognizerBaseTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SwipeRecognizerBaseTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: SwipeRecognizerBaseTest001
 * @tc.desc: Test SwipeRecognizer: Basic function test
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerBaseTestNg, SwipeRecognizerBaseTest001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : TEST_CASES) {
        /**
         * @tc.steps: step1. create SwipeRecognizer.
         */
        auto swipeRecognizer =
            AceType::MakeRefPtr<SwipeRecognizer>(testCase.fingers, testCase.direction, testCase.speed);
        /**
         * @tc.steps: step2. DispatchTouchEvent.
         * @tc.expected: step2. refereeState_ equals.
         */
        std::vector<TouchEvent> downEvents;
        std::unordered_map<int32_t, std::vector<TouchEvent>> moveEvents;
        std::vector<TouchEvent> upEvents;
        CreateTouchEvents(testCase.infos, testCase.speed, downEvents, moveEvents, upEvents);
        for (const auto& item : downEvents) {
            swipeRecognizer->HandleEvent(item);
        }
        for (int32_t index = 0; index < STEP_COUNT; index++) {
            for (const auto& item : moveEvents) {
                swipeRecognizer->HandleEvent((item.second)[index]);
            }
        }
        auto eventCount = 0;
        for (const auto& item : upEvents) {
            swipeRecognizer->HandleEvent(item);
            eventCount++;
            if (eventCount == testCase.fingers) {
                break;
            }
        }
        EXPECT_TRUE(IsRecognizerStateEqual(caseNum, swipeRecognizer->refereeState_, testCase.expectResult));
        caseNum++;
    }
}

/**
 * @tc.name: SwipeRecognizerBaseTest002
 * @tc.desc: Test SwipeRecognizer: Test for TriggerGestureJudgeCallback.
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerBaseTestNg, SwipeRecognizerBaseTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swipeRecognizer.
     */
    int32_t fingers = 1;
    SwipeDirection direction = { SwipeDirection::HORIZONTAL };
    double speed = 10.0;
    auto swipeRecognizer = AceType::MakeRefPtr<SwipeRecognizer>(fingers, direction, speed);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<NG::TargetComponent>();
    auto judgeFunc1 = [](const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NGGestureRecognizer>& current,
                          const std::list<RefPtr<NGGestureRecognizer>>& others) -> GestureJudgeResult {
        return GestureJudgeResult::REJECT;
    };
    auto judgeFunc2 = [](const RefPtr<GestureInfo>& gestureInfo,
                          const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        return GestureJudgeResult::REJECT;
    };
    targetComponent->SetOnGestureRecognizerJudgeBegin(std::move(judgeFunc1));
    targetComponent->onGestureJudgeBegin_ = judgeFunc2;
    swipeRecognizer->SetTargetComponent(targetComponent);
    /**
     * @tc.steps: step2. TriggerGestureJudgeCallback with inputEventType::AXIS.
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    swipeRecognizer->inputEventType_ = InputEventType::AXIS;
    swipeRecognizer->lastAxisEvent_ = axisEvent;
    EXPECT_EQ(swipeRecognizer->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);

    /**
     * @tc.steps: step3. TriggerGestureJudgeCallback with inputEventType::TOUCH_SCREEN.
     * @tc.expected: step3. result equals.
     */
    TouchEvent touchEvent;
    swipeRecognizer->inputEventType_ = InputEventType::TOUCH_SCREEN;
    swipeRecognizer->lastTouchEvent_ = touchEvent;
    EXPECT_EQ(swipeRecognizer->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);
}
} // namespace OHOS::Ace::NG