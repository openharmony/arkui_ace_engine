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

#include "testing_rect.h"

namespace OHOS::Ace::Testing {
enum class TestingPathDirection {
    CW_DIRECTION,
    CCW_DIRECTION,
};

class TestingPath {
public:
    TestingPath() = default;
    ~TestingPath() = default;

    virtual void AddArc(TestingRect oval, float startAngle, float sweepAngle) {}
    virtual void AddRect(const TestingRect& rect, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION) {}

    virtual void AddRect(
        float left, float top, float right, float bottom, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    {}

    virtual void AddRoundRect(const TestingRect& rect, float xRadius, float yRadius,
        TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    {}

    virtual void MoveTo(float xs, float ys) {}
    virtual void LineTo(float xs, float ys) {}
    virtual void AddCircle(
        float dx, float dy, float radius, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    {}
    virtual void Reset() {}
    virtual void Close() {}
    virtual void QuadTo(float ctrlPtX, float ctrlPtY, float endPtX, float endPtY) {}
    virtual void ArcTo(float rx, float ry, float angle, TestingPathDirection direction, float endX, float endY) {}
    virtual void Offset(float dx, float dy) {}
    virtual TestingRect GetBounds()
    {
        return TestingRect();
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_PATH_H
