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
#include "test/unittest/core/gestures/pan_recognizer_test_utils.h"
#include "test/unittest/core/gestures/recognizer_test_utils.h"

#include "core/event/ace_events.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

struct AxisInputInfo {
    PointF startPoint;
    SourceTool sourceTool;
    PanQuadrantDirection direction;
    ComparationResult compare;
    AxisInputInfo(
        PointF startPoint, SourceTool sourceTool, PanQuadrantDirection direction, ComparationResult compare)
        : startPoint(startPoint), sourceTool(sourceTool), direction(direction), compare(compare)
    {}
};

struct PanAxisTestCase {
    int32_t fingers = 0;
    float distance = 0.0f;
    PanDirection direction;
    AxisInputInfo info;
    RefereeState expectResult;
    PanAxisTestCase(
        int32_t fingers, float distance, PanDirection direction, AxisInputInfo info, RefereeState expectResult)
        : fingers(fingers), distance(distance), direction(direction), info(info), expectResult(expectResult)
    {}
};

const std::vector<PanAxisTestCase> AXIS_TEST_CASES = {
    PanAxisTestCase(2, 10.0f, { PanDirection::ALL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_ZERO,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 0
    PanAxisTestCase(1, 10.0f, { PanDirection::VERTICAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_ZERO,
            ComparationResult::LESS),
        RefereeState::DETECTING), // case 1
    PanAxisTestCase(1, 10.0f, { PanDirection::VERTICAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_TWO,
            ComparationResult::LESS),
        RefereeState::DETECTING), // case 2
    PanAxisTestCase(1, 10.0f, { PanDirection::VERTICAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_FOUR,
            ComparationResult::GREAT),
        RefereeState::DETECTING), // case 3
    PanAxisTestCase(1, 10.0f, { PanDirection::VERTICAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_SIX,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 4
    PanAxisTestCase(1, 10.0f, { PanDirection::VERTICAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_TWO,
            ComparationResult::EQUAL),
        RefereeState::SUCCEED), // case 5
    PanAxisTestCase(1, 10.0f, { PanDirection::VERTICAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_FOUR,
            ComparationResult::EQUAL),
        RefereeState::DETECTING), // case 6
    PanAxisTestCase(1, 10.0f, { PanDirection::VERTICAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_TWO,
            ComparationResult::LESS),
        RefereeState::DETECTING), // case 7
    PanAxisTestCase(1, 10.0f, { PanDirection::VERTICAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_SIX,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 8
    PanAxisTestCase(1, 10.0f, { PanDirection::VERTICAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_TWO,
            ComparationResult::EQUAL),
        RefereeState::SUCCEED), // case 9
    PanAxisTestCase(1, 10.0f, { PanDirection::HORIZONTAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_ZERO,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 10
    PanAxisTestCase(1, 10.0f, { PanDirection::HORIZONTAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_TWO,
            ComparationResult::GREAT),
        RefereeState::DETECTING), // case 11
    PanAxisTestCase(1, 10.0f, { PanDirection::HORIZONTAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_TWO,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 12
    PanAxisTestCase(1, 10.0f, { PanDirection::HORIZONTAL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_SIX,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 13
    PanAxisTestCase(1, 10.0f, { PanDirection::ALL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_ZERO,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 14
    PanAxisTestCase(1, 10.0f, { PanDirection::ALL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_TWO,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 15
    PanAxisTestCase(1, 10.0f, { PanDirection::ALL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_FOUR,
            ComparationResult::GREAT),
        RefereeState::DETECTING), // case 16
    PanAxisTestCase(1, 10.0f, { PanDirection::ALL },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_SIX,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 17
    PanAxisTestCase(1, 10.0f, { PanDirection::LEFT },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_ZERO,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 18
    PanAxisTestCase(1, 10.0f, { PanDirection::LEFT },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_FOUR,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 19
    PanAxisTestCase(1, 10.0f, { PanDirection::LEFT },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_TWO,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 20
    PanAxisTestCase(1, 10.0f, { PanDirection::RIGHT },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_ZERO,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 21
    PanAxisTestCase(1, 10.0f, { PanDirection::RIGHT },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_FOUR,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 22
    PanAxisTestCase(1, 10.0f, { PanDirection::RIGHT },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_TWO,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 23
    PanAxisTestCase(1, 10.0f, { PanDirection::UP },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_TWO,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 24
    PanAxisTestCase(1, 10.0f, { PanDirection::UP },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_SIX,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 25
    PanAxisTestCase(1, 10.0f, { PanDirection::UP },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_TWO,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 26
    PanAxisTestCase(1, 10.0f, { PanDirection::UP },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_SIX,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 27
    PanAxisTestCase(1, 10.0f, { PanDirection::DOWN },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_TWO,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 28
    PanAxisTestCase(1, 10.0f, { PanDirection::DOWN },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_SIX,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 29
    PanAxisTestCase(1, 10.0f, { PanDirection::DOWN },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_TWO,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 30
    PanAxisTestCase(1, 10.0f, { PanDirection::DOWN },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_SIX,
            ComparationResult::GREAT),
        RefereeState::SUCCEED), // case 31
    PanAxisTestCase(1, 10.0f, { PanDirection::NONE },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::TOUCHPAD, PanQuadrantDirection::LINE_ZERO,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 32
    PanAxisTestCase(1, 10.0f, { PanDirection::NONE },
        AxisInputInfo(PointF { 100.0f, 100.0f }, SourceTool::MOUSE, PanQuadrantDirection::LINE_TWO,
            ComparationResult::GREAT),
        RefereeState::FAIL), // case 33
};

namespace {
void CalculateAxisValue(
    float distance, PanQuadrantDirection direction, SourceTool sourceTool, float& horizontalAxis, float& verticalAxis)
{
    float step = 0.0f;
    if (sourceTool == SourceTool::TOUCHPAD) {
        step = distance / STEP_COUNT;
    } else {
        step = distance / (MOUSE_RATIO * STEP_COUNT);
    }
    switch (direction) {
        case PanQuadrantDirection::LINE_ZERO:
            horizontalAxis = -step;
            break;
        case PanQuadrantDirection::LINE_TWO:
            verticalAxis = step;
            break;
        case PanQuadrantDirection::LINE_FOUR:
            horizontalAxis = step;
            break;
        case PanQuadrantDirection::LINE_SIX:
            verticalAxis = -step;
            break;
        default:
            break;
    }
}

void CreateAxisEvents(const AxisInputInfo& info, float distance, std::vector<AxisEvent>& moveEvents)
{
    switch (info.compare) {
        case ComparationResult::LESS:
            distance /= 2;
            break;
        case ComparationResult::EQUAL:
            break;
        case ComparationResult::GREAT:
            distance *= 2;
            break;
        default:
            break;
    }
    float horizontalAxis = 0.0f;
    float verticalAxis = 0.0f;
    CalculateAxisValue(distance, info.direction, info.sourceTool, horizontalAxis, verticalAxis);
    for (int32_t num = 1; num <= STEP_COUNT; num++) {
        AxisEvent moveEvent;
        moveEvent.x = info.startPoint.GetX();
        moveEvent.y = info.startPoint.GetY();
        moveEvent.action = AxisAction::UPDATE;
        moveEvent.horizontalAxis = horizontalAxis;
        moveEvent.verticalAxis = verticalAxis;
        moveEvent.sourceTool = info.sourceTool;
        moveEvents.emplace_back(moveEvent);
    }
}

} // namespace

class PanRecognizerAxisBaseTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void PanRecognizerAxisBaseTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void PanRecognizerAxisBaseTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: PanRecognizerAxisBaseTest001
 * @tc.desc: Test PanRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerAxisBaseTestNg, PanRecognizerAxisBaseTest001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : AXIS_TEST_CASES) {
        /**
         * @tc.steps: step1. create PanRecognizer.
         */
        RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
        panGestureOption->SetFingers(testCase.fingers);
        panGestureOption->SetDirection(testCase.direction);
        panGestureOption->SetDistance(testCase.distance);
        RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
        /**
         * @tc.steps: step2. DispatchTouchEvent.
         * @tc.expected: step2. refereeState_ equals.
         */
        AxisEvent downEvent;
        downEvent.action = AxisAction::BEGIN;
        downEvent.x = testCase.info.startPoint.GetX();
        downEvent.y = testCase.info.startPoint.GetY();
        downEvent.sourceTool = testCase.info.sourceTool;
        std::vector<AxisEvent> moveEvents;
        CreateAxisEvents(testCase.info, testCase.distance, moveEvents);
        panRecognizer->HandleEvent(downEvent);
        for (const auto& item : moveEvents) {
            panRecognizer->HandleEvent(item);
        }
        EXPECT_TRUE(IsRecognizerStateEqual(caseNum, panRecognizer->refereeState_, testCase.expectResult));
        caseNum++;
    }
}

} // namespace OHOS::Ace::NG