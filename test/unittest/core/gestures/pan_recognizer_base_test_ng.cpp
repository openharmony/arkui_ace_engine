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
namespace {
constexpr int32_t ESCAPE_FINGER_ID_0 = 0;
constexpr int32_t ESCAPE_FINGER_ID_1 = 1;
constexpr int32_t ESCAPE_FINGER_ID_2 = 2;
} // namespace

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

/**
 * @tc.name: PanRecognizerBaseTest005
 * @tc.desc: Test PanRecognizer: Test for TriggerGestureJudgeCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerBaseTest005, TestSize.Level1)
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
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<NG::TargetComponent>();
    auto judgeFunc1 = [](const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NGGestureRecognizer>& current,
                     const std::list<WeakPtr<NGGestureRecognizer>>& others) -> GestureJudgeResult {
        return GestureJudgeResult::REJECT;
    };
    auto judgeFunc2 = [](const RefPtr<GestureInfo>& gestureInfo,
                     const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        return GestureJudgeResult::REJECT;
    };
    targetComponent->SetOnGestureRecognizerJudgeBegin(std::move(judgeFunc1));
    targetComponent->onGestureJudgeBegin_ = judgeFunc2;
    panRecognizer->SetTargetComponent(targetComponent);
    /**
     * @tc.steps: step2. TriggerGestureJudgeCallback with inputEventType::AXIS.
     * @tc.expected: step2. result equals.
     */
    AxisEvent axisEvent;
    panRecognizer->inputEventType_ = InputEventType::AXIS;
    panRecognizer->lastAxisEvent_ = axisEvent;
    EXPECT_EQ(panRecognizer->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);

    /**
     * @tc.steps: step3. TriggerGestureJudgeCallback with inputEventType::TOUCH_SCREEN.
     * @tc.expected: step3. result equals.
     */
    TouchEvent touchEvent;
    panRecognizer->inputEventType_ = InputEventType::TOUCH_SCREEN;
    panRecognizer->lastTouchEvent_ = touchEvent;
    EXPECT_EQ(panRecognizer->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);
}

/**
 * @tc.name: PanRecognizerCanCoexistWithScrollTest001
 * @tc.desc: SetCanCoexistWithScroll / CanCoexistWithScroll round-trip
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerCanCoexistWithScrollTest001, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    EXPECT_FALSE(pan->CanCoexistWithScroll());
    pan->SetCanCoexistWithScroll(true);
    EXPECT_TRUE(pan->CanCoexistWithScroll());
    pan->SetCanCoexistWithScroll(false);
    EXPECT_FALSE(pan->CanCoexistWithScroll());
}

/**
 * @tc.name: PanRecognizerGetCurrentFingerIdsTest001
 * @tc.desc: GetCurrentFingerIds returns ids matching touchPoints_
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerGetCurrentFingerIdsTest001, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    EXPECT_TRUE(pan->GetCurrentFingerIds().empty());

    TouchEvent touch;
    touch.id = ESCAPE_FINGER_ID_0;
    pan->touchPoints_[ESCAPE_FINGER_ID_0] = touch;
    touch.id = ESCAPE_FINGER_ID_1;
    pan->touchPoints_[ESCAPE_FINGER_ID_1] = touch;

    auto ids = pan->GetCurrentFingerIds();
    EXPECT_EQ(ids.size(), 2u);
    EXPECT_NE(ids.find(ESCAPE_FINGER_ID_0), ids.end());
    EXPECT_NE(ids.find(ESCAPE_FINGER_ID_1), ids.end());
}

/**
 * @tc.name: PanRecognizerOnFingerEscapedTest001
 * @tc.desc: OnFingerEscaped removes all per-finger state for the given id
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerOnFingerEscapedTest001, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    TouchEvent touch;
    touch.id = ESCAPE_FINGER_ID_0;
    pan->touchPoints_[ESCAPE_FINGER_ID_0] = touch;
    pan->touchPointsDistance_[ESCAPE_FINGER_ID_0] = Offset();
    pan->fingersId_.insert(ESCAPE_FINGER_ID_0);
    pan->activeFingers_.push_back(ESCAPE_FINGER_ID_0);
    pan->currentFingers_ = 1;

    pan->OnFingerEscaped(ESCAPE_FINGER_ID_0);

    EXPECT_TRUE(pan->touchPoints_.find(ESCAPE_FINGER_ID_0) == pan->touchPoints_.end());
    EXPECT_TRUE(pan->touchPointsDistance_.find(ESCAPE_FINGER_ID_0) == pan->touchPointsDistance_.end());
    EXPECT_TRUE(pan->fingersId_.find(ESCAPE_FINGER_ID_0) == pan->fingersId_.end());
    EXPECT_EQ(pan->currentFingers_, 0);
}

/**
 * @tc.name: PanRecognizerOnFingerEscapedTest002
 * @tc.desc: OnFingerEscaped does not underflow currentFingers_ when already zero
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerOnFingerEscapedTest002, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);
    pan->currentFingers_ = 0;

    pan->OnFingerEscaped(ESCAPE_FINGER_ID_0);

    EXPECT_EQ(pan->currentFingers_, 0);
}

/**
 * @tc.name: PanRecognizerSetEscapeModeForPanTest001
 * @tc.desc: SetEscapeModeForPan marks escape + cleans up tracked fingers + resets aggregated state
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerSetEscapeModeForPanTest001, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    TouchEvent touch;
    touch.id = ESCAPE_FINGER_ID_0;
    pan->touchPoints_[ESCAPE_FINGER_ID_0] = touch;
    pan->fingersId_.insert(ESCAPE_FINGER_ID_0);
    pan->currentFingers_ = 1;
    pan->averageDistance_ = Offset(10.0, 10.0);
    pan->refereeState_ = RefereeState::DETECTING;

    std::unordered_set<int32_t> escaping = { ESCAPE_FINGER_ID_0 };
    pan->SetEscapeModeForPan(escaping);

    EXPECT_TRUE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_0));
    EXPECT_TRUE(pan->touchPoints_.empty());
    EXPECT_TRUE(pan->fingersId_.empty());
    EXPECT_EQ(pan->averageDistance_, Offset());
    EXPECT_EQ(pan->refereeState_, RefereeState::READY);
}

/**
 * @tc.name: PanRecognizerSetEscapeModeForPanTest002
 * @tc.desc: SetEscapeModeForPan does not reset aggregated state when untracked fingers remain
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerSetEscapeModeForPanTest002, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    TouchEvent touch;
    touch.id = ESCAPE_FINGER_ID_1;
    pan->touchPoints_[ESCAPE_FINGER_ID_1] = touch;
    pan->fingersId_.insert(ESCAPE_FINGER_ID_1);
    pan->currentFingers_ = 1;
    pan->refereeState_ = RefereeState::DETECTING;

    // Escape finger 0 only — finger 1 is still tracked.
    std::unordered_set<int32_t> escaping = { ESCAPE_FINGER_ID_0 };
    pan->SetEscapeModeForPan(escaping);

    EXPECT_EQ(pan->refereeState_, RefereeState::DETECTING);
    EXPECT_FALSE(pan->touchPoints_.empty());
}

/**
 * @tc.name: PanRecognizerEscapeModeResetOnResetStatusTest001
 * @tc.desc: OnResetStatus clears escape state and escapeRequested_
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerEscapeModeResetOnResetStatusTest001, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    pan->escapedFingerIds_.insert(ESCAPE_FINGER_ID_0);
    pan->escapeRequested_ = true;

    pan->ResetStatus();

    EXPECT_FALSE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_0));
    EXPECT_FALSE(pan->escapeRequested_);
}

/**
 * @tc.name: PanRecognizerEscapeModeUpEventResetsTest001
 * @tc.desc: escapeRequested_ is cleared once all fingers are lifted
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerEscapeModeUpEventResetsTest001, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);
    pan->SetCanCoexistWithScroll(true);
    pan->escapeRequested_ = true;
    pan->fingersId_.insert(ESCAPE_FINGER_ID_0);

    TouchEvent upEvent;
    upEvent.id = ESCAPE_FINGER_ID_0;
    upEvent.type = TouchType::UP;
    pan->HandleTouchUpEvent(upEvent);

    EXPECT_FALSE(pan->escapeRequested_);
}

/**
 * @tc.name: PanRecognizerFilterCoexistingGestureFingers001
 * @tc.desc: FilterCoexistingGestureFingers is a no-op when referee_ is null and no pipeline context
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerFilterCoexistingGestureFingers001, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);
    pan->SetCanCoexistWithScroll(true);

    TouchEvent touch;
    touch.id = ESCAPE_FINGER_ID_0;
    pan->touchPoints_[ESCAPE_FINGER_ID_0] = touch;
    pan->fingersId_.insert(ESCAPE_FINGER_ID_0);

    // With no referee_ and no pipeline, should not crash.
    pan->FilterCoexistingGestureFingers();

    EXPECT_FALSE(pan->escapeRequested_);
}

/**
 * @tc.name: PanRecognizerFilterCoexistingGestureFingers002
 * @tc.desc: FilterCoexistingGestureFingers is a no-op when escape was already requested
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerFilterCoexistingGestureFingers002, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);
    pan->SetCanCoexistWithScroll(true);
    pan->escapeRequested_ = true;

    // Should return early without touching anything.
    pan->FilterCoexistingGestureFingers();

    EXPECT_TRUE(pan->escapeRequested_);
}

/**
 * @tc.name: PanRecognizerFilterCoexistingGestureFingers003
 * @tc.desc: FilterCoexistingGestureFingers calls SetEscapeModeForPan on peer with opposite coexist flag
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, PanRecognizerFilterCoexistingGestureFingers003, TestSize.Level1)
{
    // coexist Pan (multi-select) ─── peer inside scope
    RefPtr<PanGestureOption> optCoexist = AceType::MakeRefPtr<PanGestureOption>();
    auto coexistPan = AceType::MakeRefPtr<PanRecognizer>(optCoexist);
    coexistPan->SetCanCoexistWithScroll(true);

    // peer Pan (e.g. system scroll pan, canCoexistWithScroll=false)
    RefPtr<PanGestureOption> optPeer = AceType::MakeRefPtr<PanGestureOption>();
    auto peerPan = AceType::MakeRefPtr<PanRecognizer>(optPeer);
    // canCoexistWithScroll stays false by default

    // Set up a GestureScope with both recognizers and wire it to the referee.
    RefPtr<GestureReferee> gestureReferee = AceType::MakeRefPtr<GestureReferee>();
    RefPtr<GestureScope> scope = AceType::MakeRefPtr<GestureScope>(0);
    scope->recognizers_.push_back(coexistPan);
    scope->recognizers_.push_back(peerPan);
    gestureReferee->gestureScopes_[0] = scope;

    // Give coexistPan a tracked finger so GetCurrentFingerIds() is non-empty.
    TouchEvent touch;
    touch.id = ESCAPE_FINGER_ID_2;
    coexistPan->touchPoints_[ESCAPE_FINGER_ID_2] = touch;
    coexistPan->fingersId_.insert(ESCAPE_FINGER_ID_2);
    coexistPan->currentFingers_ = 1;

    // Also give peerPan the same finger so SetEscapeModeForPan cleans it up.
    peerPan->touchPoints_[ESCAPE_FINGER_ID_2] = touch;
    peerPan->fingersId_.insert(ESCAPE_FINGER_ID_2);
    peerPan->currentFingers_ = 1;
    peerPan->refereeState_ = RefereeState::DETECTING;

    coexistPan->referee_ = gestureReferee;

    coexistPan->FilterCoexistingGestureFingers();

    EXPECT_TRUE(peerPan->IsFingerEscaped(ESCAPE_FINGER_ID_2));
    EXPECT_TRUE(coexistPan->escapeRequested_);
}

/**
 * @tc.name: GestureRecognizerEscapeAPITest001
 * @tc.desc: SetEscapeMode / IsFingerEscaped / ResetEscapeMode basic round-trip
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, GestureRecognizerEscapeAPITest001, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    EXPECT_FALSE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_0));

    std::unordered_set<int32_t> fingers = { ESCAPE_FINGER_ID_0, ESCAPE_FINGER_ID_1 };
    pan->SetEscapeMode(fingers);

    EXPECT_TRUE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_0));
    EXPECT_TRUE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_1));
    EXPECT_FALSE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_2));

    pan->ResetEscapeMode();

    EXPECT_FALSE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_0));
    EXPECT_FALSE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_1));
}

/**
 * @tc.name: GestureRecognizerEscapeAPITest002
 * @tc.desc: ResetStatus clears escaped finger ids
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, GestureRecognizerEscapeAPITest002, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    pan->escapedFingerIds_.insert(ESCAPE_FINGER_ID_0);
    EXPECT_TRUE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_0));

    pan->ResetStatus();

    EXPECT_FALSE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_0));
}

/**
 * @tc.name: GestureRecognizerEscapeAPITest003
 * @tc.desc: ResetStatusOnFinish clears escaped finger ids
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, GestureRecognizerEscapeAPITest003, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    pan->escapedFingerIds_.insert(ESCAPE_FINGER_ID_1);
    EXPECT_TRUE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_1));

    pan->ResetStatusOnFinish();

    EXPECT_FALSE(pan->IsFingerEscaped(ESCAPE_FINGER_ID_1));
}

/**
 * @tc.name: GestureRecognizerProcessTouchEventEscapeTest001
 * @tc.desc: ProcessTouchEvent returns true without updating state for an escaped finger
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, GestureRecognizerProcessTouchEventEscapeTest001, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    // Mark finger 0 as escaped.
    pan->escapedFingerIds_.insert(ESCAPE_FINGER_ID_0);

    TouchEvent moveEvent;
    moveEvent.id = ESCAPE_FINGER_ID_0;
    moveEvent.type = TouchType::MOVE;
    moveEvent.x = 100.0f;
    moveEvent.y = 100.0f;

    bool handled = pan->ProcessTouchEvent(moveEvent);

    EXPECT_TRUE(handled);
    EXPECT_EQ(pan->lastTouchEvent_.x, 0.0f);
}

/**
 * @tc.name: GestureRecognizerProcessTouchEventEscapeTest002
 * @tc.desc: ProcessTouchEvent processes normally for a non-escaped finger
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerBaseTestNg, GestureRecognizerProcessTouchEventEscapeTest002, TestSize.Level1)
{
    RefPtr<PanGestureOption> opt = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> pan = AceType::MakeRefPtr<PanRecognizer>(opt);

    // Finger 1 is escaped; finger 0 is not — it should be processed.
    pan->escapedFingerIds_.insert(ESCAPE_FINGER_ID_1);

    TouchEvent downEvent;
    downEvent.id = ESCAPE_FINGER_ID_0;
    downEvent.type = TouchType::DOWN;
    downEvent.x = 50.0f;
    downEvent.y = 60.0f;

    pan->ProcessTouchEvent(downEvent);

    EXPECT_EQ(pan->lastTouchEvent_.id, ESCAPE_FINGER_ID_0);
}
} // namespace OHOS::Ace::NG