/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_PATH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_PATH_H

#include <vector>

#include "testing_matrix.h"
#include "testing_point.h"
#include "testing_rect.h"
#include "testing_round_rect.h"

namespace OHOS::Ace::Testing {
enum class TestingPathDirection {
    CW_DIRECTION,
    CCW_DIRECTION,
};

enum class TestingPathFillType {
    WINDING,
    EVENTODD,
    INVERSE_WINDING,
    INVERSE_EVENTODD,
};

enum class TestingPathOp {
    DIFFERENCE,
    INTERSECT,
    UNION,
    XOR,
    REVERSE_DIFFERENCE,
};

enum class PathDirection {
    CW_DIRECTION,
    CCW_DIRECTION,
};
class TestingPath {
public:
    TestingPath() = default;
    virtual ~TestingPath() = default;

    virtual void AddArc(TestingRect oval, float startAngle, float sweepAngle) {}
    virtual void AddRect(const TestingRect& rect, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION) {}

    virtual void AddRect(
        float left, float top, float right, float bottom, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    {}

    virtual void AddRoundRect(const TestingRect& rect, float xRadius, float yRadius,
        TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    {}

    virtual void AddRoundRect(const TestingRoundRect& roundRect, PathDirection dir = PathDirection::CW_DIRECTION) {}

    virtual void AddPath(const TestingPath& src) {}

    virtual void MoveTo(float xs, float ys) {}
    virtual void LineTo(float xs, float ys) {}
    virtual void AddCircle(
        float dx, float dy, float radius, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    {}
    virtual void Reset() {}
    virtual void Close() {}
    virtual void QuadTo(float ctrlPtX, float ctrlPtY, float endPtX, float endPtY) {}
    virtual void ArcTo(float x1, float y1, float x2, float y2, float radius) {}
    virtual void ArcTo(float rx, float ry, float angle, TestingPathDirection direction, float endX, float endY) {}
    virtual void ArcTo(float pt1X, float pt1Y, float pt2X, float pt2Y, float startAngle, float sweepAngle) {}
    virtual void ArcTo(const TestingPoint& pt1, const TestingPoint& pt2, float startAngle, float sweepAngle) {}

    virtual void CubicTo(float ctrlPt1X, float ctrlPt1Y, float ctrlPt2X, float ctrlPt2Y, float endPtX, float endPtY) {}

    virtual void Offset(float dx, float dy) {}
    virtual void AddPoly(const std::vector<TestingPoint>& points, int count, bool close) {}
    virtual bool Op(const TestingPath& path1, TestingPath& path2, TestingPathOp op)
    {
        return true;
    }
    virtual void AddOval(const TestingRect& oval, PathDirection dir = PathDirection::CW_DIRECTION) {}

    virtual bool BuildFromSVGString(const std::string& str)
    {
        return true;
    }

    virtual TestingRect GetBounds()
    {
        return {};
    }
    virtual void SetFillStyle(TestingPathFillType fillStyle) {}

    virtual bool IsValid() const
    {
        return false;
    }

    virtual float GetLength(bool forceClosed) const
    {
        return 0;
    }

    virtual bool GetPositionAndTangent(
        float distance, TestingPoint& position, TestingPoint& tangent, bool forceClosed) const
    {
        return false;
    }

    virtual void Transform(const TestingMatrix& matrix) {}

    virtual std::string ConvertToSVGString()
    {
        return "";
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_PATH_H
