/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_PATH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_PATH_H

#include <memory>
#include <string>

#include "utils/rect.h"
#include "utils/scalar.h"

namespace OHOS::Ace::Testing {
using scalar = Rosen::Drawing::scalar;
using Rect = Rosen::Drawing::Rect;
enum class TestingPathDirection {
    CW_DIRECTION,
    CCW_DIRECTION,
};

class TestingPath {
public:
    TestingPath() = default;
    ~TestingPath() = default;

    virtual void AddArc(Rect oval, scalar startAngle, scalar sweepAngle) {}
    virtual void AddRect(const Rect& rect, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION) {}
    virtual void AddRect(scalar left, scalar top, scalar right, scalar bottom,
        TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    {}
    virtual void AddRoundRect(
        const Rect& rect, scalar xRadius, scalar yRadius, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    {}

    virtual void MoveTo(scalar x, scalar y) {}
    virtual void LineTo(scalar x, scalar y) {}
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_PATH_H
