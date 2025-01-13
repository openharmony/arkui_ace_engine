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

#ifndef TEST_UNITTEST_CORE_GESTURES_PAN_RECOGNIZER_TEST_UTILS_H
#define TEST_UNITTEST_CORE_GESTURES_PAN_RECOGNIZER_TEST_UTILS_H

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t FORTY_FIVE_DEGREES = 45;
constexpr int32_t TWENTY_DEGREES = 20;
constexpr int32_t QUADRANT_COUNT = 8;
constexpr float HALF_CIRCLE = 180.0f;

enum class PanQuadrantDirection {
    QUADRANT_ZERO = 0,
    QUADRANT_ONE = 1,
    QUADRANT_TWO = 2,
    QUADRANT_THREE = 3,
    QUADRANT_FOUR = 4,
    QUADRANT_FIVE = 5,
    QUADRANT_SIX = 6,
    QUADRANT_SEVEN = 7,
    LINE_ZERO = 8,
    LINE_ONE = 9,
    LINE_TWO = 10,
    LINE_THREE = 11,
    LINE_FOUR = 12,
    LINE_FIVE = 13,
    LINE_SIX = 14,
    LINE_SEVEN = 15,
};

} // namespace

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_GESTURES_PAN_RECOGNIZER_TEST_UTILS_H