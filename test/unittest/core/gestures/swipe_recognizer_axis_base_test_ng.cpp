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

#include "core/event/ace_events.h"
#include "core/event/axis_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

struct SwipeAxisInputInfo {
    PointF startPoint;
    SourceTool sourceTool;
    bool isShiftKeyPressed = false;
    SwipeInputDirection direction;
    ComparationResult compare;
    SwipeAxisInputInfo(PointF startPoint, SourceTool sourceTool, bool isShiftKeyPressed, SwipeInputDirection direction,
        ComparationResult compare)
        : startPoint(startPoint), sourceTool(sourceTool), isShiftKeyPressed(isShiftKeyPressed), direction(direction),
          compare(compare)
    {}
};

struct SwipeAxisTestCase {
    double speed = 0.0;
    SwipeDirection direction;
    SwipeAxisInputInfo info;
    RefereeState expectResult;
    SwipeAxisTestCase(double speed, SwipeDirection direction, SwipeAxisInputInfo info, RefereeState expectResult)
        : speed(speed), direction(direction), info(info), expectResult(expectResult)
    {}
};

const std::vector<SwipeAxisTestCase> AXIS_TEST_CASES = {
    SwipeAxisTestCase(100.0, { SwipeDirection::VERTICAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::HORIZONTAL,
            ComparationResult::LESS),
        RefereeState::FAIL), // case 0
    SwipeAxisTestCase(100.0, { SwipeDirection::VERTICAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::VERTICAL,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 1
    SwipeAxisTestCase(100.0, { SwipeDirection::VERTICAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::HORIZONTAL,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 2
    SwipeAxisTestCase(100.0, { SwipeDirection::VERTICAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false,
            SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT),
        RefereeState::FAIL), // case 3
    SwipeAxisTestCase(100.0, { SwipeDirection::VERTICAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::VERTICAL,
            ComparationResult::EQUAL),
        RefereeState::SUCCEED), // case 4
    SwipeAxisTestCase(200.0, { SwipeDirection::VERTICAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, false, SwipeInputDirection::VERTICAL,
            ComparationResult::LESS),
        RefereeState::SUCCEED), // case 5
    SwipeAxisTestCase(200.0, { SwipeDirection::VERTICAL },
        SwipeAxisInputInfo(
            PointF { 100.0f, 100.0f }, SourceTool::MOUSE, true, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
        RefereeState::FAIL), // case 6
    SwipeAxisTestCase(100.0, { SwipeDirection::HORIZONTAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::VERTICAL,
            ComparationResult::LESS),
        RefereeState::FAIL), // case 7
    SwipeAxisTestCase(100.0, { SwipeDirection::HORIZONTAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::VERTICAL,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 8
    SwipeAxisTestCase(100.0, { SwipeDirection::HORIZONTAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::HORIZONTAL,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 9
    SwipeAxisTestCase(100.0, { SwipeDirection::HORIZONTAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false,
            SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT),
        RefereeState::FAIL), // case 10
    SwipeAxisTestCase(100.0, { SwipeDirection::HORIZONTAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::HORIZONTAL,
            ComparationResult::EQUAL),
        RefereeState::SUCCEED), // case 11
    SwipeAxisTestCase(200.0, { SwipeDirection::HORIZONTAL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, false, SwipeInputDirection::VERTICAL,
            ComparationResult::LESS),
        RefereeState::SUCCEED), // case 12
    SwipeAxisTestCase(200.0, { SwipeDirection::HORIZONTAL },
        SwipeAxisInputInfo(
            PointF { 100.0f, 100.0f }, SourceTool::MOUSE, true, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
        RefereeState::SUCCEED), // case 13
    SwipeAxisTestCase(100.0, { SwipeDirection::ALL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::VERTICAL,
            ComparationResult::LESS),
        RefereeState::FAIL), // case 14
    SwipeAxisTestCase(100.0, { SwipeDirection::ALL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::VERTICAL,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 15
    SwipeAxisTestCase(100.0, { SwipeDirection::ALL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::HORIZONTAL,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 16
    SwipeAxisTestCase(100.0, { SwipeDirection::ALL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false,
            SwipeInputDirection::VERTICAL_HORIZONTAL, ComparationResult::GREAT),
        RefereeState::FAIL), // case 17
    SwipeAxisTestCase(100.0, { SwipeDirection::ALL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false,
            SwipeInputDirection::HORIZONTAL_VERTICAL, ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 18
    SwipeAxisTestCase(100.0, { SwipeDirection::ALL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::VERTICAL,
            ComparationResult::EQUAL),
        RefereeState::SUCCEED), // case 19
    SwipeAxisTestCase(200.0, { SwipeDirection::ALL },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, false, SwipeInputDirection::VERTICAL,
            ComparationResult::LESS),
        RefereeState::SUCCEED), // case 20
    SwipeAxisTestCase(200.0, { SwipeDirection::ALL },
        SwipeAxisInputInfo(
            PointF { 100.0f, 100.0f }, SourceTool::MOUSE, true, SwipeInputDirection::VERTICAL, ComparationResult::LESS),
        RefereeState::SUCCEED), // case 21
    SwipeAxisTestCase(100.0, { SwipeDirection::NONE },
        SwipeAxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, false, SwipeInputDirection::HORIZONTAL,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 22
};

namespace {
void CreateAxisEvents(
    const SwipeAxisInputInfo& info, double speed, std::vector<AxisEvent>& moveEvents, AxisEvent& upEvent)
{
    auto inputSpeed = AdjustSpeed(speed, info.compare);
    float step = (info.sourceTool == SourceTool::TOUCHPAD) ? SWIPE_MOVE_STEP : SWIPE_MOVE_STEP / MOUSE_RATIO;
    auto timeStep = (SWIPE_MOVE_STEP / inputSpeed) * 1000 * 1000 * 1000;
    for (int32_t num = 1; num <= STEP_COUNT; num++) {
        AxisEvent moveEvent;
        moveEvent.x = info.startPoint.GetX();
        moveEvent.y = info.startPoint.GetY();
        moveEvent.action = AxisAction::UPDATE;
        moveEvent.time = TimeStamp(std::chrono::nanoseconds(static_cast<int64_t>(1000 + num * timeStep)));
        moveEvent.sourceTool = info.sourceTool;
        if (info.isShiftKeyPressed) {
            moveEvent.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
        }
        if (info.sourceTool == SourceTool::TOUCHPAD) {
            bool isHorizontal = (info.direction == SwipeInputDirection::HORIZONTAL ||
                                 info.direction == SwipeInputDirection::HORIZONTAL_VERTICAL);
            bool isVertical = (info.direction == SwipeInputDirection::VERTICAL ||
                               info.direction == SwipeInputDirection::VERTICAL_HORIZONTAL);
            if (isHorizontal) {
                moveEvent.horizontalAxis = step;
            } else if (isVertical) {
                moveEvent.verticalAxis = step;
            }
            if (info.direction == SwipeInputDirection::HORIZONTAL_VERTICAL && num > 3) {
                moveEvent.verticalAxis = step;
                moveEvent.horizontalAxis = 0.0;
            }
            if (info.direction == SwipeInputDirection::VERTICAL_HORIZONTAL && num > 3) {
                moveEvent.horizontalAxis = step;
                moveEvent.verticalAxis = 0.0;
            }
        } else {
            moveEvent.verticalAxis = step;
        }
        moveEvents.emplace_back(moveEvent);
    }
    upEvent.x = info.startPoint.GetX();
    upEvent.y = info.startPoint.GetY();
    upEvent.action = AxisAction::END;
    upEvent.time = moveEvents.back().time;
    upEvent.sourceTool = info.sourceTool;
}

} // namespace

class SwipeRecognizerAxisBaseTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void SwipeRecognizerAxisBaseTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SwipeRecognizerAxisBaseTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: SwipeRecognizerAxisBaseTest001
 * @tc.desc: Test PanRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(SwipeRecognizerAxisBaseTestNg, SwipeRecognizerAxisBaseTest001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : AXIS_TEST_CASES) {
        /**
         * @tc.steps: step1. create SwipeRecognizer.
         */
        auto swipeRecognizer = AceType::MakeRefPtr<SwipeRecognizer>(1, testCase.direction, testCase.speed);
        /**
         * @tc.steps: step2. DispatchTouchEvent.
         * @tc.expected: step2. refereeState_ equals.
         */
        AxisEvent downEvent;
        downEvent.x = testCase.info.startPoint.GetX();
        downEvent.y = testCase.info.startPoint.GetY();
        downEvent.action = AxisAction::BEGIN;
        downEvent.sourceTool = testCase.info.sourceTool;
        downEvent.time = TimeStamp(std::chrono::nanoseconds(1000));
        downEvent.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
        std::vector<AxisEvent> moveEvents;
        AxisEvent upEvent;
        CreateAxisEvents(testCase.info, testCase.speed, moveEvents, upEvent);
        swipeRecognizer->HandleEvent(downEvent);
        for (const auto& item : moveEvents) {
            swipeRecognizer->HandleEvent(item);
        }
        swipeRecognizer->HandleEvent(upEvent);
        EXPECT_TRUE(IsRecognizerStateEqual(caseNum, swipeRecognizer->refereeState_, testCase.expectResult));
        caseNum++;
    }
}

} // namespace OHOS::Ace::NG