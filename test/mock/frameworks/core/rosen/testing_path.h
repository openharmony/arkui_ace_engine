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

    virtual void AddArc(TestingRect oval, float startAngle, float sweepAngle) { hasContent_ = true; }
    virtual void AddRect(const TestingRect& rect, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    { hasContent_ = true; }

    virtual void AddRect(
        float left, float top, float right, float bottom, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    { hasContent_ = true; }

    virtual void AddRoundRect(const TestingRect& rect, float xRadius, float yRadius,
        TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    { hasContent_ = true; }

    virtual void AddRoundRect(const TestingRoundRect& roundRect,
        TestingPathDirection dir = TestingPathDirection::CW_DIRECTION) { hasContent_ = true; }

    virtual void AddPath(const TestingPath& src)
    {
        if (src.IsValid()) hasContent_ = true;
    }

    virtual void MoveTo(float xs, float ys) { hasContent_ = true; }
    virtual void LineTo(float xs, float ys) { hasContent_ = true; }
    virtual void AddCircle(
        float dx, float dy, float radius, TestingPathDirection dir = TestingPathDirection::CW_DIRECTION)
    { hasContent_ = true; }
    virtual void Reset() { hasContent_ = false; }
    virtual void Close() { hasContent_ = true; }
    virtual void QuadTo(float ctrlPtX, float ctrlPtY, float endPtX, float endPtY) { hasContent_ = true; }
    virtual void ArcTo(float x1, float y1, float x2, float y2, float radius) { hasContent_ = true; }
    virtual void ArcTo(float rx, float ry, float angle, TestingPathDirection direction, float endX, float endY)
    { hasContent_ = true; }
    virtual void ArcTo(float pt1X, float pt1Y, float pt2X, float pt2Y, float startAngle, float sweepAngle)
    { hasContent_ = true; }
    virtual void ArcTo(const TestingPoint& pt1, const TestingPoint& pt2, float startAngle, float sweepAngle)
    { hasContent_ = true; }

    virtual void CubicTo(float ctrlPt1X, float ctrlPt1Y, float ctrlPt2X, float ctrlPt2Y, float endPtX, float endPtY)
    { hasContent_ = true; }

    virtual void Offset(float dx, float dy) { hasContent_ = true; }
    virtual void AddPoly(const std::vector<TestingPoint>& points, int count, bool close)
    { if (count > 0) hasContent_ = true; }
    virtual bool Op(const TestingPath& path1, TestingPath& path2, TestingPathOp op)
    {
        if (path1.IsValid() || path2.IsValid()) hasContent_ = true;
        return true;
    }
    virtual void AddOval(const TestingRect& oval, PathDirection dir = PathDirection::CW_DIRECTION)
    { hasContent_ = true; }

    virtual bool BuildFromSVGString(const std::string& str)
    {
        if (!str.empty()) hasContent_ = true;
        return true;
    }

    virtual TestingRect GetBounds()
    {
        return {};
    }
    virtual void SetFillStyle(TestingPathFillType fillStyle) {}

    virtual bool IsValid() const
    {
        return hasContent_;
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

    virtual void TransformWithPerspectiveClip(const TestingMatrix& matrix, TestingPath* dst,
        bool applyPerspectiveClip) {}

    void Dump(std::string& out) const
    {
        return;
    }

private:
    bool hasContent_ = false;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_PATH_H
