/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
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

#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/event/ace_events.h"
#include "core/gestures/gesture_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
struct PanRecognizerDistanceTestCase {
    double originDistance_ = 0.0;
    SourceTool downSourceTool = SourceTool::UNKNOWN;
    double moveDistance = 0.0;
    PanRecognizer::GestureAcceptResult expectedState = PanRecognizer::GestureAcceptResult::ACCEPT;
    PanRecognizerDistanceTestCase(double originDistance, SourceTool downSourceTool, double moveDistance,
        PanRecognizer::GestureAcceptResult expectedState)
        : originDistance_(originDistance), downSourceTool(downSourceTool), moveDistance(moveDistance),
        expectedState(expectedState)
    {}
};

struct PanRecognizerDistanceMapTestCase : public PanRecognizerDistanceTestCase {
    SourceTool createSourceTool = SourceTool::UNKNOWN;
    PanRecognizerDistanceMapTestCase(double originDistance, SourceTool downSourceTool, double moveDistance,
        PanRecognizer::GestureAcceptResult expectedState, SourceTool createSourceTool)
        : PanRecognizerDistanceTestCase(originDistance, downSourceTool, moveDistance, expectedState),
        createSourceTool(createSourceTool)
    {}
};

const std::vector<PanRecognizerDistanceTestCase> PAN_RECOGNIZER_DISTANCE_TEST_CASES = {
    PanRecognizerDistanceTestCase(-1, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING),
    PanRecognizerDistanceTestCase(-1, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING),
    PanRecognizerDistanceTestCase(-1, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(-1, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING),
    PanRecognizerDistanceTestCase(-1, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::DETECTING),
    PanRecognizerDistanceTestCase(-1, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(-1, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING),
    PanRecognizerDistanceTestCase(-1, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING),
    PanRecognizerDistanceTestCase(-1, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::ACCEPT),

    PanRecognizerDistanceTestCase(0, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(0, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(0, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(0, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(0, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(0, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(0, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(0, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(0, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::ACCEPT),

    PanRecognizerDistanceTestCase(1, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING),
    PanRecognizerDistanceTestCase(1, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(1, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(1, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING),
    PanRecognizerDistanceTestCase(1, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(1, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(1, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING),
    PanRecognizerDistanceTestCase(1, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::ACCEPT),
    PanRecognizerDistanceTestCase(1, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::ACCEPT),
};

const std::vector<PanRecognizerDistanceMapTestCase> PAN_RECOGNIZER_DISTANCE_MAP_UNKNOWN_TEST_CASES = {
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),

    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),

    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),

    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::UNKNOWN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::UNKNOWN),
};

const std::vector<PanRecognizerDistanceMapTestCase> PAN_RECOGNIZER_DISTANCE_MAP_FINGER_TEST_CASES = {
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),

    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),

    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),

    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::FINGER),
};

const std::vector<PanRecognizerDistanceMapTestCase> PAN_RECOGNIZER_DISTANCE_MAP_PEN_TEST_CASES = {
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(-1, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),

    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(0, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),

    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(1, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),

    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::UNKNOWN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::FINGER, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 5, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 8, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::PEN, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 0, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 1, PanRecognizer::GestureAcceptResult::DETECTING,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 5, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 8, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
    PanRecognizerDistanceMapTestCase(100, SourceTool::TOUCHPAD, 100, PanRecognizer::GestureAcceptResult::ACCEPT,
        SourceTool::PEN),
};
} // namespace

class PanRecognizerDistanceTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void PanRecognizerDistanceTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void PanRecognizerDistanceTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: PanRecognizerPanDistanceTest001
 * @tc.desc: Test PanRecognizer: APITest
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerDistanceTestNg, PanRecognizerPanDistanceTest001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto &testCase : PAN_RECOGNIZER_DISTANCE_TEST_CASES) {
        /**
         * @tc.steps: step1. create PanRecognizer.
         */
        PanDirection panDirection;
        panDirection.type = PanDirection::ALL;
        RefPtr<PanRecognizer> panRecognizer =
            AceType::MakeRefPtr<PanRecognizer>(1, panDirection, testCase.originDistance_);
        ASSERT_NE(panRecognizer, nullptr);
        panRecognizer->ResetDistanceMap();
        /**
         * @tc.steps: step2. DispatchTouchEvent.
         * @tc.expected: step2. refereeState_ equals.
         */
        Dimension dimension = Dimension(testCase.moveDistance, DimensionUnit::VP);
        panRecognizer->averageDistance_ = Offset(0, dimension.ConvertToPx());
        panRecognizer->deviceTool_ = testCase.downSourceTool;
        PanRecognizer::GestureAcceptResult result;
        result = panRecognizer->IsPanGestureAccept();
        EXPECT_EQ(result, testCase.expectedState);
        caseNum++;
    }
}

/**
 * @tc.name: PanRecognizerPanDistanceMapTest001
 * @tc.desc: Test PanRecognizer: APITest
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerDistanceTestNg, PanRecognizerPanDistanceMapTest001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto &testCase : PAN_RECOGNIZER_DISTANCE_MAP_UNKNOWN_TEST_CASES) {
        PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
            { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
        distanceMap[testCase.createSourceTool] = testCase.originDistance_;
        /**
         * @tc.steps: step1. create PanRecognizer.
         */
        PanDirection panDirection;
        panDirection.type = PanDirection::ALL;
        RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, distanceMap);
        ASSERT_NE(panRecognizer, nullptr);
        panRecognizer->ResetDistanceMap();
        /**
         * @tc.steps: step2. DispatchTouchEvent.
         * @tc.expected: step2. refereeState_ equals.
         */

        Dimension dimension = Dimension(testCase.moveDistance, DimensionUnit::VP);
        panRecognizer->averageDistance_ = Offset(0, dimension.ConvertToPx());
        panRecognizer->deviceTool_ = testCase.downSourceTool;
        PanRecognizer::GestureAcceptResult result;
        result = panRecognizer->IsPanGestureAccept();
        EXPECT_EQ(result, testCase.expectedState);
        caseNum++;
    }
}

/**
 * @tc.name: PanRecognizerPanDistanceMapTest002
 * @tc.desc: Test PanRecognizer: APITest
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerDistanceTestNg, PanRecognizerPanDistanceMapTest002, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto &testCase : PAN_RECOGNIZER_DISTANCE_MAP_FINGER_TEST_CASES) {
        PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
            { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
        distanceMap[testCase.createSourceTool] = testCase.originDistance_;
        /**
         * @tc.steps: step1. create PanRecognizer.
         */
        PanDirection panDirection;
        panDirection.type = PanDirection::ALL;
        RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, distanceMap);
        ASSERT_NE(panRecognizer, nullptr);
        panRecognizer->ResetDistanceMap();
        /**
         * @tc.steps: step2. DispatchTouchEvent.
         * @tc.expected: step2. refereeState_ equals.
         */
        Dimension dimension = Dimension(testCase.moveDistance, DimensionUnit::VP);
        panRecognizer->averageDistance_ = Offset(0, dimension.ConvertToPx());
        panRecognizer->deviceTool_ = testCase.downSourceTool;
        PanRecognizer::GestureAcceptResult result;
        result = panRecognizer->IsPanGestureAccept();
        EXPECT_EQ(result, testCase.expectedState);
        caseNum++;
    }
}

/**
 * @tc.name: PanRecognizerPanDistanceMapTest003
 * @tc.desc: Test PanRecognizer: APITest
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerDistanceTestNg, PanRecognizerPanDistanceMapTest003, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto &testCase : PAN_RECOGNIZER_DISTANCE_MAP_PEN_TEST_CASES) {
        PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
            { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
        distanceMap[testCase.createSourceTool] = testCase.originDistance_ > 0 ?
            testCase.originDistance_ : DEFAULT_PEN_PAN_DISTANCE.ConvertToPx();
        /**
         * @tc.steps: step1. create PanRecognizer.
         */
        PanDirection panDirection;
        panDirection.type = PanDirection::ALL;
        RefPtr<PanRecognizer> panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, distanceMap);
        ASSERT_NE(panRecognizer, nullptr);
        panRecognizer->ResetDistanceMap();
        /**
         * @tc.steps: step2. DispatchTouchEvent.
         * @tc.expected: step2. refereeState_ equals.
         */
        Dimension dimension = Dimension(testCase.moveDistance, DimensionUnit::VP);
        panRecognizer->averageDistance_ = Offset(0, dimension.ConvertToPx());
        panRecognizer->deviceTool_ = testCase.downSourceTool;
        PanRecognizer::GestureAcceptResult result;
        result = panRecognizer->IsPanGestureAccept();
        EXPECT_EQ(result, testCase.expectedState);
        caseNum++;
    }
}
/**
 * @tc.name: PanRecognizerPanDistanceMapTest004
 * @tc.desc: Test GestureEventHub SetPanEvent Distance
 * @tc.type: FUNC
 */
HWTEST_F(PanRecognizerDistanceTestNg, PanRecognizerPanDistanceMapTest004, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create GestureEventHub.
    */
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    /**
     * @tc.steps: step2. SetPanEvent EVENT_PAN_GESTURE_LEFT|EVENT_PAN_GESTURE_UP
     */
    PanDirection panDirection;
    panDirection.type = PanDirection::RIGHT | PanDirection::UP;
    auto panEvent = AceType::MakeRefPtr<PanEvent>(nullptr, nullptr, nullptr, nullptr);
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, 1 } };
    gestureEventHub->AddPanEvent(panEvent, panDirection, 1, distanceMap);
    /**
     * @tc.steps: step3. Calculate pan recognizer distance.
     */
    auto panEventActuator = gestureEventHub->panEventActuator_;
    ASSERT_NE(panEventActuator, nullptr);
    auto panRecognizer = panEventActuator->panRecognizer_;
    ASSERT_NE(panRecognizer, nullptr);
    EXPECT_EQ(panRecognizer->GetDistance(), 1);
}
} // namespace OHOS::Ace::NG