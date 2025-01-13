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

#ifndef TEST_UNITTEST_CORE_GESTURES_RECOGNIZER_TEST_UTILS_H
#define TEST_UNITTEST_CORE_GESTURES_RECOGNIZER_TEST_UTILS_H

#include "gtest/gtest.h"

#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t STEP_COUNT = 5;
constexpr float MOUSE_RATIO = 1.4f;
enum class ComparationResult {
    LESS = 0,
    EQUAL = 1,
    GREAT = 2,
};

testing::AssertionResult IsRecognizerStateEqual(int caseNum, RefereeState actualState, RefereeState expectState)
{
    if (actualState == expectState) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "TestCaseNum:  " << caseNum << " actual state "
                                       << static_cast<int32_t>(actualState) << " expect state "
                                       << static_cast<int32_t>(expectState);
}

} // namespace

} // namespace OHOS::Ace::NG

#endif // TEST_UNITTEST_CORE_GESTURES_RECOGNIZER_TEST_UTILS_H