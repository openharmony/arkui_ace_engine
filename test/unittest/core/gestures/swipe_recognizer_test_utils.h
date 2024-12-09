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

#ifndef TEST_UNITTEST_CORE_GESTURES_SWIPE_RECOGNIZER_TEST_UTILS_H
#define TEST_UNITTEST_CORE_GESTURES_SWIPE_RECOGNIZER_TEST_UTILS_H

#include "test/unittest/core/gestures/recognizer_test_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double SWIPE_MOVE_DISTANCE = 500.0;
constexpr double SWIPE_MOVE_STEP = 100.0;

enum class SwipeInputDirection {
    VERTICAL = 0,
    HORIZONTAL,
    VERTICAL_HORIZONTAL,
    HORIZONTAL_VERTICAL,
};

double AdjustSpeed(double speed, ComparationResult compare)
{
    switch (compare) {
        case ComparationResult::LESS:
            return speed /= 2;
        case ComparationResult::GREAT:
            return speed *= 2;
        default:
            return speed;
    }
}

} // namespace

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_GESTURES_PAN_RECOGNIZER_TEST_UTILS_H