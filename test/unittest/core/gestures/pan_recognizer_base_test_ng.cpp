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

#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/event/ace_events.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline/base/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

struct InputInfos {
    PointF startPoint;
    int32_t fingerId;
    PanQuadrantDirection direction;
    ComparationResult compare;
    InputInfos(PointF startPoint, int32_t fingerId, PanQuadrantDirection direction, ComparationResult compare)
        : startPoint(startPoint), fingerId(fingerId), direction(direction), compare(compare)
    {}
};

struct PanTestCase {
    int32_t fingers = 0;
    float distance = 0.0f;
    PanDirection direction;
    std::vector<InputInfos> infos;
    RefereeState expectResult;
    PanTestCase(int32_t fingers, float distance, PanDirection direction, std::vector<InputInfos> infos,
        RefereeState expectResult)
        : fingers(fingers), distance(distance), direction(direction), infos(std::move(infos)),
          expectResult(expectResult)
    {}
};

const std::vector<PanTestCase> TEST_CASES = {
    PanTestCase(1, 10.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::LESS),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::LESS) },
        RefereeState::DETECTING), // case 0
    PanTestCase(1, 10.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::GREAT) },
        RefereeState::DETECTING), // case 1
    PanTestCase(1, 10.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_FIVE, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_FIVE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 2
    PanTestCase(1, 10.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_ONE, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_ONE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 3
    PanTestCase(1, 10.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::LESS) },
        RefereeState::DETECTING), // case 4
    PanTestCase(1, 10.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::GREAT) },
        RefereeState::DETECTING), // case 5
    PanTestCase(1, 10.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_FIVE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 6
    PanTestCase(1, 10.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_ONE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 7
    PanTestCase(1, 10.0f, { PanDirection::HORIZONTAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT) },
        RefereeState::DETECTING), // case 8
    PanTestCase(1, 10.0f, { PanDirection::HORIZONTAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_SEVEN, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 9
    PanTestCase(1, 10.0f, { PanDirection::HORIZONTAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_SEVEN, ComparationResult::GREAT) },
        RefereeState::DETECTING), // case 10
    PanTestCase(1, 15.0f, { PanDirection::ALL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_THREE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 11
    PanTestCase(1, 15.0f, { PanDirection::ALL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_FOUR, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 12
    PanTestCase(1, 15.0f, { PanDirection::LEFT },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 13
    PanTestCase(1, 15.0f, { PanDirection::LEFT },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_THREE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 14
    PanTestCase(1, 15.0f, { PanDirection::RIGHT },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT) },
        RefereeState::DETECTING), // case 15
    PanTestCase(1, 15.0f, { PanDirection::RIGHT },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_SEVEN, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 16
    PanTestCase(1, 15.0f, { PanDirection::UP },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ONE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 17
    PanTestCase(1, 15.0f, { PanDirection::UP },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_SIX, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 18
    PanTestCase(1, 15.0f, { PanDirection::UP },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_THREE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 19
    PanTestCase(1, 15.0f, { PanDirection::DOWN },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 20
    PanTestCase(1, 15.0f, { PanDirection::DOWN },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_FIVE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 21
    PanTestCase(1, 15.0f, { PanDirection::DOWN },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_FIVE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 22
    PanTestCase(1, 15.0f, { PanDirection::NONE },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ONE, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 23
    PanTestCase(2, 15.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::GREAT) },
        RefereeState::READY), // case 24
    PanTestCase(2, 15.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_SIX, ComparationResult::EQUAL),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_SIX, ComparationResult::EQUAL),
            InputInfos(PointF { 100.0f, 100.0f }, 2, PanQuadrantDirection::LINE_SIX, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 25
    PanTestCase(2, 15.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::LESS),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::LESS) },
        RefereeState::DETECTING), // case 26
    PanTestCase(2, 15.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_FIVE, ComparationResult::LESS),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_FIVE, ComparationResult::LESS) },
        RefereeState::DETECTING), // case 27
    PanTestCase(2, 15.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_ONE, ComparationResult::LESS),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_ONE, ComparationResult::LESS) },
        RefereeState::DETECTING), // case 28
    PanTestCase(2, 15.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 29
    PanTestCase(2, 15.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_SEVEN, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_SEVEN, ComparationResult::GREAT) },
        RefereeState::DETECTING), // case 30
    PanTestCase(2, 15.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_SEVEN, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_SEVEN, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 31
    PanTestCase(2, 15.0f, { PanDirection::VERTICAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_SIX, ComparationResult::EQUAL),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_SIX, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 32
    PanTestCase(2, 15.0f, { PanDirection::HORIZONTAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_FOUR, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_FOUR, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 2, PanQuadrantDirection::LINE_FOUR, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 33
    PanTestCase(2, 15.0f, { PanDirection::HORIZONTAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_ZERO, ComparationResult::EQUAL),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_ZERO, ComparationResult::EQUAL),
            InputInfos(PointF { 100.0f, 100.0f }, 2, PanQuadrantDirection::LINE_ZERO, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 34
    PanTestCase(2, 15.0f, { PanDirection::HORIZONTAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_ZERO, ComparationResult::EQUAL),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_ZERO, ComparationResult::EQUAL) },
        RefereeState::SUCCEED), // case 35
    PanTestCase(2, 15.0f, { PanDirection::HORIZONTAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_TWO, ComparationResult::EQUAL),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_TWO, ComparationResult::EQUAL) },
        RefereeState::DETECTING), // case 36
    PanTestCase(2, 15.0f, { PanDirection::HORIZONTAL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_FOUR, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_FOUR, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 37
    PanTestCase(2, 10.0f, { PanDirection::ALL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ONE, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_ONE, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 2, PanQuadrantDirection::QUADRANT_ONE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 38
    PanTestCase(2, 10.0f, { PanDirection::ALL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_FOUR, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_FOUR, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 2, PanQuadrantDirection::QUADRANT_FOUR, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 39
    PanTestCase(2, 10.0f, { PanDirection::ALL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 40
    PanTestCase(2, 10.0f, { PanDirection::ALL },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_SEVEN, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_SEVEN, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 41
    PanTestCase(2, 10.0f, { PanDirection::LEFT },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_ZERO, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 42
    PanTestCase(2, 10.0f, { PanDirection::LEFT },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_THREE, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_THREE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 43
    PanTestCase(2, 10.0f, { PanDirection::RIGHT },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT) },
        RefereeState::DETECTING), // case 44
    PanTestCase(2, 10.0f, { PanDirection::RIGHT },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_SEVEN, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_SEVEN, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 45
    PanTestCase(2, 10.0f, { PanDirection::UP },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ONE, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_ONE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 46
    PanTestCase(2, 10.0f, { PanDirection::UP },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_SIX, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_SIX, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 47
    PanTestCase(2, 10.0f, { PanDirection::UP },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_THREE, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_THREE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 48
    PanTestCase(2, 10.0f, { PanDirection::DOWN },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_TWO, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 49
    PanTestCase(2, 10.0f, { PanDirection::DOWN },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_FIVE, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_FIVE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 50
    PanTestCase(2, 10.0f, { PanDirection::DOWN },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::LINE_FIVE, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::LINE_FIVE, ComparationResult::GREAT) },
        RefereeState::SUCCEED), // case 51
    PanTestCase(2, 10.0f, { PanDirection::NONE },
        { InputInfos(PointF { 100.0f, 100.0f }, 0, PanQuadrantDirection::QUADRANT_ONE, ComparationResult::GREAT),
            InputInfos(PointF { 100.0f, 100.0f }, 1, PanQuadrantDirection::QUADRANT_ONE, ComparationResult::GREAT) },
        RefereeState::FAIL), // case 52
};

namespace {
float DegreesToRadians(float degrees)
{
    return static_cast<float>(degrees * ACE_PI / HALF_CIRCLE);
}

void CalculateEndPoint(const PointF& startPoint, float distance, float angle, PointF& endPoint)
{
    double radians = DegreesToRadians(angle);
    endPoint.SetX(static_cast<float>(startPoint.GetX() + distance * cos(radians)));
    endPoint.SetY(static_cast<float>(startPoint.GetY() - distance * sin(radians)));
}

float GetAngel(PanQuadrantDirection direction)
{
    switch (direction) {
        case PanQuadrantDirection::QUADRANT_ZERO:
        case PanQuadrantDirection::QUADRANT_ONE:
        case PanQuadrantDirection::QUADRANT_TWO:
        case PanQuadrantDirection::QUADRANT_THREE:
        case PanQuadrantDirection::QUADRANT_FOUR:
        case PanQuadrantDirection::QUADRANT_FIVE:
        case PanQuadrantDirection::QUADRANT_SIX:
        case PanQuadrantDirection::QUADRANT_SEVEN:
            return static_cast<float>(static_cast<int32_t>(direction) * FORTY_FIVE_DEGREES + TWENTY_DEGREES);
        case PanQuadrantDirection::LINE_ZERO:
        case PanQuadrantDirection::LINE_ONE:
        case PanQuadrantDirection::LINE_TWO:
        case PanQuadrantDirection::LINE_THREE:
        case PanQuadrantDirection::LINE_FOUR:
        case PanQuadrantDirection::LINE_FIVE:
        case PanQuadrantDirection::LINE_SIX:
        case PanQuadrantDirection::LINE_SEVEN:
            return static_cast<float>((static_cast<int32_t>(direction) - QUADRANT_COUNT) * FORTY_FIVE_DEGREES);
        default:
            return 0.0f;
    }
}

void CreateTouchEvents(const std::vector<InputInfos>& infos, float distance, std::vector<TouchEvent>& downEvents,
    std::unordered_map<int32_t, std::vector<TouchEvent>>& moveEvents)
{
    for (const auto& info : infos) {
        PointF endPoint;
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
        CalculateEndPoint(info.startPoint, distance, GetAngel(info.direction), endPoint);
        TouchEvent downEvent;
        downEvent.SetId(info.fingerId)
            .SetType(TouchType::DOWN)
            .SetX(info.startPoint.GetX())
            .SetY(info.startPoint.GetY());
        downEvents.emplace_back(downEvent);
        auto stepX = (endPoint.GetX() - info.startPoint.GetX()) / STEP_COUNT;
        auto stepY = (endPoint.GetY() - info.startPoint.GetY()) / STEP_COUNT;
        for (int32_t num = 1; num <= STEP_COUNT; num++) {
            TouchEvent moveEvent;
            moveEvent.SetId(info.fingerId)
                .SetType(TouchType::MOVE)
                .SetX(info.startPoint.GetX() + static_cast<float>(num) * stepX)
                .SetY(info.startPoint.GetY() + static_cast<float>(num) * stepY);
            moveEvents[info.fingerId].emplace_back(moveEvent);
        }
    }
}

void CreateTouchMoveEvents(const PointF& startPoint, float inputDistance, std::vector<TouchEvent>& moveEvents)
{
    PointF endPoint;
    CalculateEndPoint(startPoint, inputDistance, GetAngel(PanQuadrantDirection::LINE_ZERO), endPoint);
    auto stepX = (endPoint.GetX() - startPoint.GetX()) / STEP_COUNT;
    auto stepY = (endPoint.GetY() - startPoint.GetY()) / STEP_COUNT;
    for (int32_t num = 1; num <= STEP_COUNT; num++) {
        TouchEvent moveEvent;
        moveEvent.SetType(TouchType::MOVE)
            .SetX(startPoint.GetX() + static_cast<float>(num) * stepX)
            .SetY(startPoint.GetY() + static_cast<float>(num) * stepY);
        moveEvents.emplace_back(moveEvent);
    }
}

} // namespace

class PanRecognizerBaseTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void PanRecognizerBaseTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void PanRecognizerBaseTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: PanRecognizerBaseTest001
 * @tc.desc: Test PanRecognizer: APITest
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerBaseTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer with illegal fingers.
     * @tc.expected: step1. fingers_ equals.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    panGestureOption->SetFingers(0);
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_EQ(panRecognizer->fingers_, 1);
    panGestureOption->SetFingers(10);
    panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_EQ(panRecognizer->fingers_, 10);
    panGestureOption->SetFingers(100);
    panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_EQ(panRecognizer->fingers_, 1);
    /**
     * @tc.steps: step2. create PanRecognizer with illegal distance.
     * @tc.expected: step2. distance_ equals.
     */
    panGestureOption->SetDistance(-1);
    panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_EQ(panRecognizer->distanceMap_[SourceTool::UNKNOWN].ConvertToPx(), 5);
    /**
     * @tc.steps: step3. create PanRecognizer with illegal direction.
     * @tc.expected: step3. direction_ equals.
     */
    panGestureOption->SetDirection({ 16 });
    panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    EXPECT_EQ(panRecognizer->direction_.type, PanDirection::ALL);
}

/**
 * @tc.name: PanRecognizerBaseTest002
 * @tc.desc: Test PanRecognizer: Basic function test
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerBaseTest002, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : TEST_CASES) {
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
        std::vector<TouchEvent> downEvents;
        std::unordered_map<int32_t, std::vector<TouchEvent>> moveEvents;
        CreateTouchEvents(testCase.infos, testCase.distance, downEvents, moveEvents);
        for (const auto& item : downEvents) {
            panRecognizer->HandleEvent(item);
        }
        for (int32_t index = 0; index < STEP_COUNT; index++) {
            for (const auto& item : moveEvents) {
                panRecognizer->HandleEvent((item.second)[index]);
            }
        }
        EXPECT_TRUE(IsRecognizerStateEqual(caseNum, panRecognizer->refereeState_, testCase.expectResult));
        caseNum++;
    }
}

/**
 * @tc.name: PanRecognizerBaseTest003
 * @tc.desc: Test PanRecognizer: Test for distance 0.
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerBaseTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create PanRecognizer with distance 0.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    panGestureOption->SetFingers(1);
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    panGestureOption->SetDirection(panDirection);
    panGestureOption->SetDistance(0.0f);
    RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    /**
     * @tc.steps: step2. DispatchTouchEvent.
     * @tc.expected: step2. refereeState_ equals.
     */
    TouchEvent downEvent;
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f);
    TouchEvent moveEvent;
    moveEvent.SetId(0).SetType(TouchType::MOVE).SetX(100.0f).SetY(100.0f);
    panRecognizer->HandleEvent(downEvent);
    panRecognizer->HandleEvent(moveEvent);
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::SUCCEED);
}

/**
 * @tc.name: PanRecognizerBaseTest004
 * @tc.desc: Test PanRecognizer: Test for mouseDistance.
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerBaseTest004, TestSize.Level1)
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
    panRecognizer->SetMouseDistance(1.0f);
    /**
     * @tc.steps: step2. DispatchTouchEvent with touch source type.
     * @tc.expected: step2. refereeState_ equals.
     */
    TouchEvent downEvent;
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::TOUCH);
    std::vector<TouchEvent> moveEvents;
    CreateTouchMoveEvents(PointF { 100.0f, 100.0f }, 5.0f, moveEvents);
    panRecognizer->HandleEvent(downEvent);
    for (auto& item : moveEvents) {
        item.sourceType = SourceType::TOUCH;
        panRecognizer->HandleEvent(item);
    }
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::DETECTING);
    /**
     * @tc.steps: step3. Reset and dispatchTouchEvent with touch-pad source type.
     * @tc.expected: step3. refereeState_ equals.
     */
    panRecognizer->OnResetStatus();
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::TOUCH_PAD);
    CreateTouchMoveEvents(PointF { 100.0f, 100.0f }, 5.0f, moveEvents);
    panRecognizer->HandleEvent(downEvent);
    for (auto& item : moveEvents) {
        item.sourceType = SourceType::TOUCH_PAD;
        panRecognizer->HandleEvent(item);
    }
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::DETECTING);
    /**
     * @tc.steps: step4. Reset and dispatchTouchEvent with touch-pad source type.
     * @tc.expected: step4. refereeState_ equals.
     */
    panRecognizer->OnResetStatus();
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::KEYBOARD);
    CreateTouchMoveEvents(PointF { 100.0f, 100.0f }, 5.0f, moveEvents);
    panRecognizer->HandleEvent(downEvent);
    for (auto& item : moveEvents) {
        item.sourceType = SourceType::KEYBOARD;
        panRecognizer->HandleEvent(item);
    }
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::DETECTING);
    /**
     * @tc.steps: step5. Reset and dispatchTouchEvent with none source type.
     * @tc.expected: step5. refereeState_ equals.
     */
    panRecognizer->OnResetStatus();
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f).SetSourceType(SourceType::NONE);
    CreateTouchMoveEvents(PointF { 100.0f, 100.0f }, 5.0f, moveEvents);
    panRecognizer->HandleEvent(downEvent);
    for (auto& item : moveEvents) {
        item.sourceType = SourceType::NONE;
        panRecognizer->HandleEvent(item);
    }
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::DETECTING);
    /**
     * @tc.steps: step5. Reset and dispatchTouchEvent with mouse source type.
     * @tc.expected: step5. refereeState_ equals.
     */
    panRecognizer->OnResetStatus();
    downEvent.SetId(0).SetType(TouchType::DOWN).SetX(100.0f).SetY(100.0f)
        .SetSourceType(SourceType::MOUSE).SetSourceTool(SourceTool::MOUSE);
    CreateTouchMoveEvents(PointF { 100.0f, 100.0f }, 5.0f, moveEvents);
    panRecognizer->HandleEvent(downEvent);
    for (auto& item : moveEvents) {
        item.sourceType = SourceType::MOUSE;
        panRecognizer->HandleEvent(item);
    }
    EXPECT_EQ(panRecognizer->refereeState_, RefereeState::SUCCEED);
}

} // namespace OHOS::Ace::NG